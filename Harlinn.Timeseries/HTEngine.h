#pragma once

#ifndef __HTENGINE_H__
#define __HTENGINE_H__

#include <HTDef.h>
#include <HCCLMDB.h>
#include <HCCString.h>

#include <HTSegment.h>
#include <HTTimeseriesPoint.h>


namespace Harlinn::Timeseries
{

    template <PointType TP, size_t segmentSize>
    class Transaction;
    template<PointType TP, size_t segmentSize>
    class Engine;

    enum class TimeseriesCursorState
    {
        /// <summary>
        /// The timeseries cursor is uninitialized
        /// </summary>
        Unknown,
        /// <summary>
        /// The timeseries cursor is open and has an invalid position 
        /// </summary>
        Open,
        /// <summary>
        /// The timeseries cursor has a valid position 
        /// </summary>
        Positioned,
        /// <summary>
        /// The segment is loaded into the modification buffer
        /// </summary>
        Loaded,
        /// <summary>
        /// This is a new timeseries, and no data is yet stored in the database
        /// </summary>
        New,
        /// <summary>
        /// The cursor is positioned beyond the end of the timeseries
        /// </summary>
        End
    };


    namespace Internal
    {

        template<PointType TP, size_t segmentSize>
        class TimeseriesInfo
        {
        public:
            using SegmentType = Segment< TP, segmentSize>;
        private:
            //size_t position_ = 0;
            //TimeseriesCursorState state_ = TimeseriesCursorState::Unknown;
            DateTime minTimestamp_;
            DateTime maxTimestamp_;
            SegmentType modificationBuffer_;
            size_t changes_ = 0;
            std::optional<DateTime> lastSegmentTimestamp_;
            DateTime loadedTimestamp_;
            Guid id_;
        public:

            TimeseriesInfo( const Guid& id )
                : id_( id ), minTimestamp_( DateTime::MaxValue( ) )
            {

            }

            TimeseriesInfo( const Guid& id, const DateTime& minTimestamp, const DateTime& maxTimestamp, const std::optional<DateTime>& lastSegmentTimestamp )
                : id_( id ), minTimestamp_( minTimestamp ), maxTimestamp_( maxTimestamp ), lastSegmentTimestamp_( lastSegmentTimestamp )
            {

            }

            const Guid& Id( ) const noexcept
            {
                return id_;
            }
            void SetId( const Guid& id )
            {
                id_ = id;
            }

            const DateTime& MaxTimestamp( ) const noexcept
            {
                return maxTimestamp_;
            }
            void SetMaxTimestamp( const DateTime& maxTimestamp ) noexcept
            {
                maxTimestamp_ = maxTimestamp;
            }

            const DateTime& MinTimestamp( ) const noexcept
            {
                return minTimestamp_;
            }
            void SetMinTimestamp( const DateTime& minTimestamp ) noexcept
            {
                minTimestamp_ = minTimestamp;
            }

            size_t Changes( ) const noexcept
            {
                return changes_;
            }
            void SetChanges( size_t changes ) noexcept
            {
                changes_ = changes;
            }
            void AddChange( ) noexcept
            {
                ++changes_;
            }

            bool IsNew( ) const noexcept
            {
                return lastSegmentTimestamp_.has_value( ) == false;
            }
            bool IsLastSegmentInModificationBuffer( ) const noexcept
            {
                if ( modificationBuffer_.empty( ) == false )
                {
                    return modificationBuffer_.back( ).Timestamp( ) == maxTimestamp_;
                }
                else
                {
                    return IsNew( );
                }
            }


            const std::optional<DateTime>& LastSegmentTimestamp( ) const noexcept
            {
                return lastSegmentTimestamp_;
            }
            void SetLastSegmentTimestamp( const std::optional<DateTime>& lastSegmentTimestamp ) noexcept
            {
                lastSegmentTimestamp_ = lastSegmentTimestamp;
            }

            const DateTime& LoadedTimestamp( ) const noexcept
            {
                return loadedTimestamp_;
            }

            void SetLoadedTimestamp( const DateTime& loadedTimestamp ) noexcept
            {
                loadedTimestamp_ = loadedTimestamp;
            }

            SegmentType* ModificationBuffer( )
            {
                return &modificationBuffer_;
            }
        };
    }


    constexpr size_t TimeseriesCursorSegmentSize = 8100;

    template<PointType TP = TimeseriesPoint, size_t segmentSize = TimeseriesCursorSegmentSize>
    class TimeseriesCursor : public SegmentContainer<TimeseriesCursor<TP, segmentSize>, Guid, TP, segmentSize>
    {
    public:
        static constexpr size_t SegmentSize = segmentSize;
        using Base = SegmentContainer<TimeseriesCursor<TP, segmentSize>, Guid, TP, segmentSize>;
        using Point = typename Base::Point;
        using Overflow = std::optional<Point>;
        using SegmentType = typename Base::DataType;
        using KeyData = typename Base::KeyType;
        using EngineType = Engine<TP, segmentSize>;
        using TransactionType = Transaction<TP, segmentSize>;
    private:
        using TimeseriesInfoType = Internal::TimeseriesInfo<TP, segmentSize>;
        // Rules:
        //  1.  There must be no empty segments in the database
        //  2.  All segments, except the last one, must be full 
        //  3a. A timeseries is empty if maxTimestamp_ < minTimestamp_
        //  3b. A timeseries has a single value if maxTimestamp_ == minTimestamp_
        //  3c. A timeseries has multiple values if maxTimestamp_ < minTimestamp_
        //  3d. If any values are stored for a timeseries then minTimestamp_ matches
        //      the timestamp part of the key for the first segment in the database
        //  4.  keyData_.Timestamp() == currentSegmentData_->front().Timestamp()
        size_t position_ = 0;
        TimeseriesCursorState state_ = TimeseriesCursorState::Unknown;
        TimeseriesInfoType* timeseriesInfo_;
        SegmentType* currentSegmentData_;
        LMDB::Cursor cursor_;
        TransactionType* transaction_;

    public:
        TimeseriesCursor( )
            : transaction_( nullptr ),
            timeseriesInfo_( nullptr ),
            currentSegmentData_( nullptr )
        {
        }

        TimeseriesCursor( TransactionType* transaction, const Guid& timeseries, LMDB::Cursor&& cursor )
            : transaction_( transaction ),
            timeseriesInfo_( nullptr ),
            currentSegmentData_( nullptr ),
            cursor_( std::move( cursor ) )
        {
            InitCursor( timeseries );
        }

        TimeseriesCursor( const TimeseriesCursor& other ) = delete;
        TimeseriesCursor( TimeseriesCursor&& other ) noexcept
            : position_( other.position_ ),
            state_( other.state_ ),
            transaction_( other.transaction_ ),
            timeseriesInfo_( other.timeseriesInfo_ ),
            currentSegmentData_( other.currentSegmentData_ ),
            cursor_( std::move( other.cursor_ ) )
        {
            other.transaction_ = nullptr;
            other.timeseriesInfo_ = nullptr;
            other.currentSegmentData_ = nullptr;
        }

        TimeseriesCursor& operator = ( const TimeseriesCursor& other ) = delete;
        TimeseriesCursor& operator = ( TimeseriesCursor&& other ) noexcept
        {
            if ( this != &other )
            {
                position_ = other.position_;
                state_ = other.state_;
                transaction_ = other.transaction_;
                timeseriesInfo_ = other.timeseriesInfo_;
                currentSegmentData_ = other.currentSegmentData_;
                cursor_.swap( other.cursor_ );
                other.position_ = 0;
                other.state_ = TimeseriesCursorState::Unknown;
                other.transaction_ = nullptr;
                other.timeseriesInfo_ = nullptr;
                other.currentSegmentData_ = nullptr;
            }
            return *this;
        }


        void Close( )
        {
            Flush( );
            cursor_.Close( );
            state_ = TimeseriesCursorState::Unknown;
        }
    private:
        void Reset( const Guid& timeseriesId )
        {
            if ( timeseriesInfo_ )
            {
                if ( timeseriesId != timeseriesInfo_->Id( ) )
                {
                    if ( timeseriesInfo_->ModificationBuffer( )->full( ) )
                    {
                        Flush( );
                    }
                }
            }
            currentSegmentData_ = nullptr;
            InitCursor( timeseriesId );
        }
    public:

        void ChangeTimeseries( const Guid& timeseries )
        {
            Reset( timeseries );
        }
        const Guid& Timeseries( ) const noexcept
        {
            return timeseriesInfo_->Id( );
        }



    private:
        TimeseriesInfoType* GetTimeseriesInfo( const Guid& timeseriesId );

        void FullInitCursor( )
        {
            const auto& timeseriesId = timeseriesInfo_->Id( );
            KeyData firstKeyData( timeseriesId );
            if ( cursor_.Search( firstKeyData ) )
            {
                const auto& firstCursorKeyData = cursor_.Key<KeyData>( );
                if ( firstCursorKeyData == timeseriesId )
                {
                    SetState( TimeseriesCursorState::Positioned );
                    currentSegmentData_ = GetCursorSegment( );
                    timeseriesInfo_->SetMinTimestamp( firstCursorKeyData.Timestamp( ) );
                    timeseriesInfo_->SetMaxTimestamp( currentSegmentData_->back( ).Timestamp( ) );

                    KeyData beyondLastKeyData( timeseriesId, DateTime( MAXINT64 ) );
                    if ( cursor_.Search( beyondLastKeyData ) )
                    {
                        if ( cursor_.MovePrevious( ) )
                        {
                            const auto& lastCursorKeyData = cursor_.Key<KeyData>( );
                            if ( lastCursorKeyData != timeseriesId )
                            {
                                // At this point we know that there is at least one previous segment
                                // for the timeseries - the first one
                                throw Exception( "Unable to move the cursor to the last segment." );
                            }
                            currentSegmentData_ = GetCursorSegment( );
                            timeseriesInfo_->SetMaxTimestamp( currentSegmentData_->back( ).Timestamp( ) );
                            timeseriesInfo_->SetLastSegmentTimestamp( lastCursorKeyData.Timestamp( ) );

                        }
                        else
                        {
                            if ( cursor_.MoveTo( firstCursorKeyData ) == false )
                            {
                                // At this point we know this should be possible
                                throw Exception( "Unable to move the cursor to the first segment." );
                            }
                        }
                    }
                    else if ( cursor_.MoveLast( ) )
                    {
                        const auto& lastCursorKeyData = cursor_.Key<KeyData>( );
                        if ( lastCursorKeyData == timeseriesId )
                        {
                            currentSegmentData_ = GetCursorSegment( );
                            timeseriesInfo_->SetMaxTimestamp( currentSegmentData_->back( ).Timestamp( ) );
                            timeseriesInfo_->SetLastSegmentTimestamp( lastCursorKeyData.Timestamp( ) );
                        }
                    }
                    return;
                }
            }
            SetState( TimeseriesCursorState::New );
            timeseriesInfo_->SetMinTimestamp( DateTime::MaxValue( ) );
            currentSegmentData_ = timeseriesInfo_->ModificationBuffer( );
        }

        void InitCursor( const Guid& timeseriesId )
        {
            timeseriesInfo_ = GetTimeseriesInfo( timeseriesId );

            if ( timeseriesInfo_->MinTimestamp( ) <= timeseriesInfo_->MaxTimestamp( ) )
            {

                if ( timeseriesInfo_->IsNew( ) )
                {
                    position_ = timeseriesInfo_->ModificationBuffer( )->size( ) + 1;
                    currentSegmentData_ = timeseriesInfo_->ModificationBuffer( );
                    SetState( TimeseriesCursorState::New );
                }
                else if ( timeseriesInfo_->Changes( ) )
                {
                    position_ = timeseriesInfo_->ModificationBuffer( )->size( ) + 1;
                    currentSegmentData_ = timeseriesInfo_->ModificationBuffer( );
                    if ( timeseriesInfo_->IsLastSegmentInModificationBuffer( ) )
                    {
                        SetState( TimeseriesCursorState::End );
                    }
                    else
                    {
                        SetState( TimeseriesCursorState::Loaded );
                    }
                }
                else
                {
                    MoveLast( );
                }
            }
            else
            {
                FullInitCursor( );
            }
        }


        void Load( )
        {
            if ( cursor_.IsPositioned( ) )
            {
                const auto& segmentTimestamp = cursor_.Key<KeyData>( ).Timestamp( );
                const auto& loadedTimestamp = timeseriesInfo_->LoadedTimestamp( );
                if ( segmentTimestamp != loadedTimestamp )
                {
                    timeseriesInfo_->SetLoadedTimestamp( cursor_.Key<KeyData>( ).Timestamp( ) );
                    timeseriesInfo_->ModificationBuffer( )->Assign( cursor_.Value<SegmentType>( ) );
                }
                if ( timeseriesInfo_->IsNew( ) )
                {
                    SetState( TimeseriesCursorState::New );
                }
                else if ( timeseriesInfo_->IsLastSegmentInModificationBuffer( ) )
                {
                    SetState( TimeseriesCursorState::End );
                }
                else
                {
                    SetState( TimeseriesCursorState::Loaded );
                }
            }
        }
        void Write( )
        {
            auto changes = timeseriesInfo_->Changes( );
            if ( changes )
            {
                timeseriesInfo_->SetChanges( 0 );
                auto* modificationBuffer = timeseriesInfo_->ModificationBuffer( );
                if ( modificationBuffer->size( ) )
                {
                    auto& timeseriesId = timeseriesInfo_->Id( );
                    auto& loadedTimestamp = timeseriesInfo_->LoadedTimestamp( );
                    auto& first = modificationBuffer->front( );
                    if ( loadedTimestamp && ( loadedTimestamp != first.Timestamp( ) ) )
                    {
                        // The key changed, so delete previously stored segment
                        KeyData deleteKey( timeseriesId, loadedTimestamp );
                        if ( cursor_.MoveTo( deleteKey ) )
                        {
                            cursor_.Delete( );
                        }
                    }

                    KeyData keyData( timeseriesId, first );
                    cursor_.Write( keyData, *modificationBuffer );
                    timeseriesInfo_->SetLoadedTimestamp( first.Timestamp( ) );
                    if ( timeseriesInfo_->IsLastSegmentInModificationBuffer( ) )
                    {
                        timeseriesInfo_->SetLastSegmentTimestamp( first.Timestamp( ) );
                        SetState( TimeseriesCursorState::End );
                    }
                    else
                    {
                        SetState( TimeseriesCursorState::Loaded );
                    }
                }
                else
                {
                    throw Exception( "There are changes, but the modification buffer is empty" );
                }
            }
        }

        bool IsCursorPositioned( ) const noexcept
        {
            return cursor_.IsPositioned( );
        }

        TimeseriesCursorState State( ) const noexcept
        {
            return state_;
        }
        void SetState( TimeseriesCursorState state ) noexcept
        {
            state_ = state;
        }

        size_t Position( ) const noexcept
        {
            return position_;
        }
        void SetPosition( size_t position ) noexcept
        {
            position_ = position;
        }
        size_t IncrementPosition( ) noexcept
        {
            return ++position_;
        }


        const DateTime& MaxTimestamp( ) const noexcept
        {
            return timeseriesInfo_->MaxTimestamp( );
        }
        void SetMaxTimestamp( const DateTime& maxTimestamp ) noexcept
        {
            timeseriesInfo_->SetMaxTimestamp( maxTimestamp );
        }

        const DateTime& MinTimestamp( ) const noexcept
        {
            return timeseriesInfo_->MinTimestamp( );
        }
        void SetMinTimestamp( const DateTime& minTimestamp ) noexcept
        {
            timeseriesInfo_->SetMinTimestamp( minTimestamp );
        }

        size_t Changes( ) const
        {
            return timeseriesInfo_->Changes( );
        }
        void SetChanges( size_t changes )
        {
            timeseriesInfo_->SetChanges( changes );
        }

        void AddChange( ) noexcept
        {
            timeseriesInfo_->AddChange( );
        }


        const std::optional<DateTime>& LastSegmentTimestamp( ) const noexcept
        {
            return timeseriesInfo_->LastSegmentTimestamp( );
        }
        void SetLastSegmentTimestamp( const std::optional<DateTime>& lastSegmentTimestamp ) noexcept
        {
            timeseriesInfo_->SetLastSegmentTimestamp( lastSegmentTimestamp );
        }

        const DateTime& LoadedTimestamp( ) const noexcept
        {
            return timeseriesInfo_->LoadedTimestamp( );
        }

        void SetLoadedTimestamp( const DateTime& loadedTimestamp ) noexcept
        {
            timeseriesInfo_->SetLoadedTimestamp( loadedTimestamp );
        }

        SegmentType* ModificationBuffer( ) const
        {
            return timeseriesInfo_->ModificationBuffer( );
        }


        bool IsPositioned( ) const noexcept
        {
            return State( ) == TimeseriesCursorState::Positioned;
        }

        bool IsNew( ) const noexcept
        {
            return State( ) == TimeseriesCursorState::New;
        }
        bool IsAtEnd( ) const noexcept
        {
            return State( ) == TimeseriesCursorState::End;
        }
        bool IsNewOrAtEnd( ) const noexcept
        {
            return IsNew( ) || IsAtEnd( );
        }


        bool IsLoaded( ) const noexcept
        {
            return State( ) == TimeseriesCursorState::Loaded;
        }

        SegmentType* GetCursorSegment( ) noexcept
        {
            auto& value = cursor_.Value( );
            return (SegmentType*)value.mv_data;
        }

    private:
        /// <summary>
        /// !!This function must only be called from CursorSearchForInsert!!
        /// Check if the previous segment is the correct segment to 
        /// insert/overwrite a timeseries point with the given timestamp
        /// </summary>
        /// <param name="timestamp">The timestamp of the timeseries point to insert or overwrite</param>
        /// <returns>true if the cursor is positoned on the correct segment</returns>
        bool CheckPreviousForInsert( const DateTime& timestamp )
        {
            const auto& timeseriesId = Timeseries( );
            if ( cursor_.MovePrevious( ) )
            {
                const auto& foundKey1 = cursor_.Key<KeyData>( );
                if ( foundKey1 == timeseriesId )
                {
                    if ( foundKey1.Timestamp( ) < timestamp )
                    {
                        const auto& foundSegement1 = cursor_.Value<SegmentType>( );
                        if ( foundSegement1.full( ) )
                        {
                            if ( foundSegement1.back( ).Timestamp( ) < timestamp )
                            {
                                // The segment is full and the argument timestamp is greater 
                                // than the lasttimestamp in the segment. This will happen 
                                // when we want to insert a timeseries point with a timestamp 
                                // earlier than the first timestamp in the next segment, but 
                                // later than the last timestamp of this segment
                                if ( cursor_.MoveNext( ) )
                                {
                                    const auto& foundKey2 = cursor_.Key<KeyData>( );
                                    // return true if the cursor is positioned on the
                                    // next segment for the current timeseries
                                    return foundKey2 == timeseriesId;
                                }
                                else
                                {
                                    // This should not happen, as we just moved to a previous 
                                    // segment after positioning the cursor using cursor_.MoveLast()
                                    // cursor_.Search(...)
                                    throw Exception( "Unable to restore cursor position" );
                                }
                            }
                            else
                            {
                                // The timestamp "belongs" to this segment
                                return true;
                            }
                        }
                        else
                        {
                            // This is the last segment of the timeseries, 
                            // This can happen when the search in CursorSearchForInsert
                            // moved the cursor to the next timeseries
                            return true;
                        }
                    }
                    else
                    {
                        // We should not manage to get here, as the initial search
                        // should cover this case
                        throw Exception( "Unexpected: Initial search should have found a record" );
                    }
                }
                else
                {
                    // The cursor was moved to the last segment of the previous
                    // timeseries, or there are no stored segments for the
                    // current timeseries
                    if ( cursor_.MoveNext( ) )
                    {
                        const auto& foundKey = cursor_.Key<KeyData>( );
                        // return true if the cursor is positioned on the
                        // correct timeseries
                        if ( foundKey == timeseriesId )
                        {
                            return true;
                        }
                        else
                        {
#ifdef _DEBUG
                            // check state_
                            if ( State( ) != TimeseriesCursorState::New )
                            {
                                throw Exception( "Unexpected: state_ is not New and no data was found in the database" );
                            }
#endif
                            return false;
                        }
                    }
                    else
                    {
                        // This should not happen, as we just moved to a previous 
                        // segment after positioning the cursor using cursor_.MoveLast()
                        // cursor_.Search(...)
                        throw Exception( "Unable to restore cursor position" );
                    }
                }
            }
            else
            {
                // Restore the positioned state of the cursor
                if ( cursor_.MoveFirst( ) )
                {
                    const auto& foundKey = cursor_.Key<KeyData>( );
                    return foundKey == timeseriesId;
                }
                else
                {
                    // This function should not be called unless there
                    // is at least one segment in the database
                    throw Exception( "Unable to move to the first segment" );
                }
            }
        }
        bool CursorSearchForInsert( const DateTime& timestamp )
        {
            const auto& timeseriesId = Timeseries( );
            KeyData key( timeseriesId, timestamp );
            if ( cursor_.Search( key ) )
            {
                const auto& foundKey1 = cursor_.Key<KeyData>( );
                if ( foundKey1 == timeseriesId &&
                    foundKey1.Timestamp( ) == timestamp )
                {
                    return true;
                }
                else
                {
                    return CheckPreviousForInsert( timestamp );
                }
            }
            else if ( cursor_.MoveLast( ) )
            {
                const auto& foundKey1 = cursor_.Key<KeyData>( );
                if ( foundKey1 == timeseriesId &&
                    foundKey1.Timestamp( ) < timestamp )
                {
                    return true;
                }
                else
                {
                    return CheckPreviousForInsert( timestamp );
                }
            }
            else
            {
                return false;
            }
        }


        bool CheckPrevious( )
        {
            const auto& timeseriesId = Timeseries( );
            if ( cursor_.MovePrevious( ) )
            {
                const auto& foundKey1 = cursor_.Key<KeyData>( );
                if ( foundKey1 == timeseriesId )
                {
                    return true;
                }
                else
                {
                    if ( cursor_.MoveNext( ) )
                    {
                        const auto& foundKey = cursor_.Key<KeyData>( );
                        return foundKey == timeseriesId;
                    }
                    else
                    {
                        throw Exception( "Unable to restore cursor position" );
                    }
                }
            }
            else
            {
                if ( cursor_.MoveFirst( ) )
                {
                    const auto& foundKey = cursor_.Key<KeyData>( );
                    return foundKey == timeseriesId;
                }
                else
                {
                    return false;
                }
            }
        }

        SearchResult CursorSearch( const DateTime& timestamp )
        {
            Flush( );
            const auto& timeseriesId = Timeseries( );
            KeyData key( timeseriesId, timestamp );
            if ( cursor_.Search( key ) )
            {
                const auto& foundKey1 = cursor_.Key<KeyData>( );
                if ( foundKey1 == timeseriesId &&
                    foundKey1.Timestamp( ) == timestamp )
                {
                    currentSegmentData_ = GetCursorSegment( );
                    SetState( TimeseriesCursorState::Positioned );
                    SetPosition( 1 );
                    return SearchResult( CompareResult::Equal, 0 );
                }
                else
                {
                    if ( CheckPrevious( ) )
                    {
                        currentSegmentData_ = GetCursorSegment( );
                        SetState( TimeseriesCursorState::Positioned );
                        auto searchResult = currentSegmentData_->Search( timestamp );
                        SetPosition( searchResult.Index( ) + 1 );
                        return searchResult;
                    }
                }
            }
            else if ( cursor_.MoveLast( ) )
            {
                const auto& foundKey1 = cursor_.Key<KeyData>( );
                if ( foundKey1 == timeseriesId &&
                    foundKey1.Timestamp( ) < timestamp )
                {
                    currentSegmentData_ = GetCursorSegment( );
                    SetState( TimeseriesCursorState::Positioned );
                    SetPosition( 1 );
                    return SearchResult( CompareResult::Less, 0 );
                }
                else
                {
                    if ( CheckPrevious( ) )
                    {
                        currentSegmentData_ = GetCursorSegment( );
                        SetState( TimeseriesCursorState::Positioned );
                        auto searchResult = currentSegmentData_->Search( timestamp );
                        SetPosition( searchResult.Index( ) + 1 );
                        return searchResult;
                    }
                }
            }
            return SearchResult( CompareResult::Empty, 0 );
        }


        void CursorMoveFirst( )
        {
            auto& timeseriesId = Timeseries( );
            SetPosition( 0 );
            if ( State( ) != TimeseriesCursorState::New )
            {
                KeyData keyData( timeseriesId, DateTime( 0LL ) );
                LMDB::Value kv( keyData );
                if ( cursor_.Search( kv ) )
                {
                    const auto& cursorKeyData = cursor_.Key<KeyData>( );
                    if ( cursorKeyData == timeseriesId )
                    {
                        SetState( TimeseriesCursorState::Positioned );
                        currentSegmentData_ = GetCursorSegment( );
                        return;
                    }
                }
                throw Exception( "CursorMoveFirst: Unable to find a record for the timeseries" );
            }
        }



        void CursorMoveLast( )
        {
            const auto& timeseriesId = Timeseries( );
            if ( State( ) != TimeseriesCursorState::New )
            {
                auto lastSegmentTimestamp = timeseriesInfo_->LastSegmentTimestamp( );
                if ( lastSegmentTimestamp.has_value( ) )
                {
                    KeyData keyData( timeseriesId, lastSegmentTimestamp.value( ) );
                    if ( cursor_.MoveTo( keyData ) )
                    {
                        SetState( TimeseriesCursorState::Positioned );
                        currentSegmentData_ = GetCursorSegment( );
                        SetPosition( currentSegmentData_->size( ) + 1 );
                        return;
                    }
                }
                KeyData keyData2( timeseriesId, DateTime( MAXINT64 ) );
                if ( cursor_.Search( keyData2 ) )
                {
                    // The search positioned the cursor on the next timeseries
                    // (since the timestamp is greater than anything possible) 
                    if ( cursor_.MovePrevious( ) )
                    {
                        const auto& cursorKeyData = cursor_.Key<KeyData>( );
                        if ( cursorKeyData == timeseriesId )
                        {
                            SetState( TimeseriesCursorState::Positioned );
                            currentSegmentData_ = GetCursorSegment( );
                            SetPosition( currentSegmentData_->size( ) + 1 );
                            return;
                        }
                    }
                    throw Exception( "CursorMoveLast: Unable to move to the previous record, which should be the last record for the timeseries" );
                }
                else
                {
                    if ( cursor_.MoveLast( ) )
                    {
                        const auto& cursorKeyData = cursor_.Key<KeyData>( );
                        if ( cursorKeyData == timeseriesId )
                        {
                            SetState( TimeseriesCursorState::Positioned );
                            currentSegmentData_ = GetCursorSegment( );
                            SetPosition( currentSegmentData_->size( ) + 1 );
                            return;
                        }
                    }
                    throw Exception( "CursorMoveLast: Unable to move to last record, which should be the last record for the timeseries" );
                }
            }
            else
            {
                SetPosition( ModificationBuffer( )->size( ) + 1 );
            }

        }


        bool CursorMoveNext( )
        {
            const auto& timeseriesId = Timeseries( );
            SetPosition( 0 );
            if ( State( ) != TimeseriesCursorState::New )
            {
                if ( cursor_.MoveNext( ) )
                {
                    const auto& cursorKeyData = cursor_.Key<KeyData>( );
                    if ( cursorKeyData == timeseriesId )
                    {
                        SetState( TimeseriesCursorState::Positioned );
                        currentSegmentData_ = GetCursorSegment( );
                        return true;
                    }
                }
                SetState( TimeseriesCursorState::End );
                currentSegmentData_ = ModificationBuffer( );
            }
            return false;
        }

        bool CursorMovePrevious( )
        {
            const auto& timeseriesId = Timeseries( );
            SetPosition( 0 );
            if ( State( ) != TimeseriesCursorState::New )
            {
                if ( cursor_.MovePrevious( ) )
                {
                    const auto& cursorKeyData = cursor_.Key<KeyData>( );
                    if ( cursorKeyData == timeseriesId )
                    {
                        SetState( TimeseriesCursorState::Positioned );
                        currentSegmentData_ = GetCursorSegment( );
                        SetPosition( currentSegmentData_->size( ) + 1 );
                        return true;
                    }
                }
                else if ( cursor_.IsPositioned( ) )
                {
                    const auto& cursorKeyData = cursor_.Key<KeyData>( );
                    if ( cursorKeyData == timeseriesId )
                    {
                        SetState( TimeseriesCursorState::Positioned );
                        currentSegmentData_ = GetCursorSegment( );
                        SetPosition( currentSegmentData_->size( ) + 1 );
                        return true;
                    }
                }
            }
            CursorMoveFirst( );
            return IsPositioned( );
        }

        bool NextInSegment( )
        {
            return currentSegmentData_ ? Position( ) < currentSegmentData_->size( ) : false;
        }

        bool PreviousInSegment( )
        {
            if ( Position( ) > 1 && currentSegmentData_ )
            {
                return currentSegmentData_->size( ) > 0;
            }
            return false;
        }

    public:
        __forceinline const Point& Current( ) const noexcept
        {
            return ( *currentSegmentData_ )[Position( ) - 1];
        }


        void Flush( )
        {
            Write( );
        }

    private:
        AnsiString ToString( const Point& point ) requires ( SegmentSize <= 10 )
        {
            auto result = Format( "[{}, {}]", point.Timestamp( ).Ticks( ), point.Value( ).Value( ) );
            return result;
        }

        void Dump( const KeyData& keyData, const SegmentType& segmentData ) requires ( SegmentSize <= 10 )
        {
            AnsiString tmp;
            for ( size_t i = 0; i < segmentData.size( ); ++i )
            {
                if ( i == 0 )
                {
                    tmp += Format( "{:04d}", segmentData[i].Timestamp( ).Ticks( ) );
                }
                else
                {
                    tmp += Format( ",{:04d}", segmentData[i].Timestamp( ).Ticks( ) );
                }

            }
            printf( "\t%04lld %2zu:[%s]\n", keyData.Timestamp( ).Ticks( ), segmentData.size( ), tmp.c_str( ) );

        }
    public:
        void Dump( ) requires ( SegmentSize <= 10 )
        {
#ifdef _DEBUG
            printf( "  Min: %04lld, Max %04lld\n", MinTimestamp( ).Ticks( ), MaxTimestamp( ).Ticks( ) );
            switch ( State( ) )
            {
                case TimeseriesCursorState::Unknown:
                    puts( "  State: Unknown" );
                    break;
                case TimeseriesCursorState::Positioned:
                    puts( "  State: Positioned" );
                    break;
                case TimeseriesCursorState::Loaded:
                    puts( "  State: Loaded" );
                    break;
                case TimeseriesCursorState::New:
                    puts( "  State: New" );
                    break;
                case TimeseriesCursorState::End:
                    puts( "  State: End" );
                    break;
            }
            puts( "  Current buffer: " );
            auto* modificationBuffer = ModificationBuffer( );
            Dump( KeyData( Timeseries( ), LoadedTimestamp( ) ), *modificationBuffer );

            puts( "  Storage: " );
            auto transaction = cursor_.Transaction( );
            auto database = cursor_.Database( );

            auto cursor = transaction->OpenCursor( database );
            if ( cursor.Search( KeyData( Timeseries( ) ) ) )
            {
                do
                {
                    const auto& key = cursor.Key<KeyData>( );
                    if ( key != Timeseries( ) )
                    {
                        break;
                    }
                    const auto& value = cursor.Value<SegmentType>( );
                    Dump( key, value );
                } while ( cursor.MoveNext( ) );
            }
            cursor.Close( );

#endif
        }
        void Dump( ) requires ( SegmentSize > 10 )
        {

        }

    private:


        void HandleComplexOwerflow( const Point& overflowPoint )
        {
            const auto& timeseriesId = Timeseries( );
            Overflow overflow = overflowPoint;
            auto transaction = cursor_.Transaction( );
            auto database = cursor_.Database( );
            auto cursor = transaction->OpenCursor( database );

            SegmentType tempdata;
            do
            {
                Point point = overflow.value( );
                overflow.reset( );
                KeyData newKey( timeseriesId, point );
                bool found = cursor.Search( newKey );

                if ( found && cursor.Key<KeyData>( ) == timeseriesId )
                {
                    tempdata.Assign( cursor.Value<SegmentType>( ) );
                    tempdata.insert( point, overflow );
                    cursor.Delete( );
                    cursor.Write( newKey, tempdata, LMDB::WriteFlags::NoOverwrite );

                }
                else
                {
                    tempdata.reset( );
                    tempdata.insert( point );
                    timeseriesInfo_->SetLastSegmentTimestamp( point.Timestamp( ) );
                    cursor.Write( newKey, tempdata, LMDB::WriteFlags::NoOverwrite );
                }
            } while ( overflow.has_value( ) );
        }

        bool IsCurrentlyLoadedSegmentTheLastSegment( )
        {
            return ModificationBuffer( )->back( ).Timestamp( ) == MaxTimestamp( );
        }


        void ResetAndAppend( const Point& point )
        {
            SetLoadedTimestamp( DateTime( 0LL ) );
            auto* modificationBuffer = ModificationBuffer( );
            modificationBuffer->reset( );
            modificationBuffer->Append( point );
            SetMaxTimestamp( point.Timestamp( ) );
            SetState( TimeseriesCursorState::End );
            AddChange( );
        }

        // The new point will be the last in the series
        __forceinline void Append( const Point& point )
        {
            auto* modificationBuffer = ModificationBuffer( );
            if ( modificationBuffer->full( ) == false )
            {
                modificationBuffer->Append( point );
                SetMaxTimestamp( point.Timestamp( ) );
                SetMinTimestamp( std::min( MinTimestamp( ), point.Timestamp( ) ) );
                AddChange( );
            }
            else
            {
                Write( );
                ResetAndAppend( point );
            }
        }

        // There is at least one point in the modification buffer
        // The buffer may contain the entire series
        void NewOrAtEndInsert( const Point& point )
        {
#ifdef _DEBUG
            if ( IsLastSegmentInModificationBuffer( ) == false )
            {
                throw Exception( "Not the last buffer" );
            }
#endif
            auto* modificationBuffer = ModificationBuffer( );
            // The modification buffer has not yet been written
            // to the database
            if ( modificationBuffer->full( ) == false )
            {
                modificationBuffer->insert( point );
                SetMinTimestamp( std::min( MinTimestamp( ), point.Timestamp( ) ) );
                AddChange( );
            }
            else
            {
                auto it = modificationBuffer->find( point.Timestamp( ) );
                // no need to check for "it == modificationBuffer_->end()"
                // as that should be handled be the fast path above
                if ( it->Timestamp( ) == point.Timestamp( ) )
                {
                    // overwrite will not overflow
                    modificationBuffer->insert( point );
                    AddChange( );
                }
                else
                {
                    // will overflow
                    Overflow overflow;
                    modificationBuffer->insert( point, overflow );
                    SetMinTimestamp( std::min( MinTimestamp( ), point.Timestamp( ) ) );
                    AddChange( );
                    SegmentType tempSegmentData;
                    const Point& overflowPoint = overflow.value( );
                    tempSegmentData.insert( overflowPoint );

                    // Write without moving the cursor
                    KeyData tempKeyData( Timeseries( ), overflowPoint );
                    auto transaction = cursor_.Transaction( );
                    auto database = cursor_.Database( );
                    transaction->Write( database, tempKeyData, tempSegmentData, LMDB::WriteFlags::NoOverwrite );
                    SetState( TimeseriesCursorState::Loaded );
                }
            }
        }

        // point is within current buffer or this is the first buffer, and point
        // is for an earlier time
        void CurrentBufferInsert( const Point& point )
        {
            auto* modificationBuffer = ModificationBuffer( );
#ifdef _DEBUG
            auto itNewPoint = modificationBuffer->find( point.Timestamp( ) );
            if ( itNewPoint == modificationBuffer->end( ) )
            {
                throw Exception( "New point is after end of modification buffer" );
            }
#endif


            // Modification buffer is full
            auto it = modificationBuffer->find( point.Timestamp( ) );
            if ( it->Timestamp( ) == point.Timestamp( ) )
            {
                // overwrite will not overflow
                modificationBuffer->insert( point );
                AddChange( );
            }
            else
            {
                // will overflow
                Overflow overflow;
                modificationBuffer->insert( point, overflow );
                SetMinTimestamp( std::min( MinTimestamp( ), point.Timestamp( ) ) );
                AddChange( );
                HandleComplexOwerflow( overflow.value( ) );
            }
        }

        void OtherBufferInsert( const Point& point )
        {
            Write( );
            const auto& timeseriesId = Timeseries( );
            KeyData newKey( timeseriesId, point );
            auto found = CursorSearchForInsert( point.Timestamp( ) );
            if ( found && cursor_.Key<KeyData>( ) == timeseriesId )
            {
                Load( );
                auto* modificationBuffer = ModificationBuffer( );
                const auto& foundKey = cursor_.Key<KeyData>( );
                if ( modificationBuffer->full( ) == false )
                {
                    modificationBuffer->insert( point );
                    SetMinTimestamp( std::min( MinTimestamp( ), point.Timestamp( ) ) );
                    SetMaxTimestamp( std::max( MaxTimestamp( ), point.Timestamp( ) ) );
                    AddChange( );
                    SetState( TimeseriesCursorState::End );
                }
                else
                {
                    auto it = modificationBuffer->find( point.Timestamp( ) );
                    if ( it == modificationBuffer->end( ) )
                    {
                        // we should be at the end, and we are appending
                        if ( IsLastSegmentInModificationBuffer( ) == false )
                        {
                            throw Exception( "Not the last buffer" );
                        }
                        ResetAndAppend( point );
                    }
                    else if ( it->Timestamp( ) == point.Timestamp( ) )
                    {
                        // overwrite will not overflow
                        modificationBuffer->insert( point );
                        AddChange( );
                    }
                    else
                    {
                        // will overflow
                        Overflow overflow;
                        modificationBuffer->insert( point, overflow );
                        SetMinTimestamp( std::min( MinTimestamp( ), point.Timestamp( ) ) );
                        SetMaxTimestamp( std::max( MaxTimestamp( ), point.Timestamp( ) ) );
                        AddChange( );
                        HandleComplexOwerflow( overflow.value( ) );
                    }
                }
            }
            else
            {
                throw Exception( "Timeseries not found" );
            }
        }

        bool IsLastSegmentInModificationBuffer( ) const noexcept
        {
            auto minTimestamp = MinTimestamp( );
            auto maxTimestamp = MaxTimestamp( );
            auto* modificationBuffer = ModificationBuffer( );
            if ( modificationBuffer->size( ) )
            {
                return maxTimestamp >= minTimestamp ?
                    modificationBuffer->back( ).Timestamp( ) == maxTimestamp :
                    true;
            }
            else
            {
                return false;
            }
        }

        bool IsFirstSegmentInModificationBuffer( ) const noexcept
        {
            auto minTimestamp = MinTimestamp( );
            auto maxTimestamp = MaxTimestamp( );
            auto* modificationBuffer = ModificationBuffer( );
            if ( modificationBuffer->size( ) )
            {
                return maxTimestamp >= minTimestamp ?
                    modificationBuffer->front( ).Timestamp( ) == minTimestamp :
                    true;
            }
            else
            {
                return false;
            }
        }



    public:

        void Insert( const Point& point )
        {
            // Do we have a fast path?
            auto maxTimestamp = MaxTimestamp( );
            if ( point.Timestamp( ) > maxTimestamp )
            {
                if ( IsNewOrAtEnd( ) || ( IsLastSegmentInModificationBuffer( ) ) )
                {
                    Append( point );
                }
                else
                {
                    if ( IsPositioned( ) && currentSegmentData_->back( ).Timestamp( ) == maxTimestamp )
                    {
                        Load( );
                        Append( point );
                    }
                    else
                    {
                        Flush( );
                        CursorMoveLast( );
                        Load( );
                        Append( point );
                    }
                }
            }
            else
            {
                // Things to do if current modification buffer is relevant

                // The modification buffer should never be empty at this point
                // since it should be impossible to have an empty series and not
                // go through the fast path above

                auto minTimestamp = MinTimestamp( );
                auto* modificationBuffer = ModificationBuffer( );
                if ( IsNewOrAtEnd( ) &&
                    ( point.Timestamp( ) >= modificationBuffer->front( ).Timestamp( ) ||
                        ( point.Timestamp( ) < minTimestamp && IsFirstSegmentInModificationBuffer( ) ) ) )
                {
                    NewOrAtEndInsert( point );
                }
                else if ( IsLoaded( ) &&
                    ( modificationBuffer->IntervalContains( point ) ||
                        ( IsFirstSegmentInModificationBuffer( ) && point.Timestamp( ) < minTimestamp ) ) )
                {
                    CurrentBufferInsert( point );
                }
                else
                {

                    OtherBufferInsert( point );
                }
            }
#ifdef _DEBUG
            Dump( );
#endif
        }

        template<typename ...Args>
        requires( std::is_constructible_v<Point, Args> && !std::is_same_v<Point, Args> )
            void Insert( Args&&... args )
        {
            Insert( Point( std::forward<Args>( args )... ) );
        }

    private:
        bool IsPositionedOnLastSegment( )
        {
            auto maxTimestamp = MaxTimestamp( );
            return maxTimestamp == currentSegmentData_->back( ).Timestamp( );
        }
        bool IsPositionedOnFirstSegment( )
        {
            auto minTimestamp = MinTimestamp( );
            return minTimestamp == currentSegmentData_->front( ).Timestamp( );
        }
    public:

        SearchResult Search( const DateTime& timestamp )
        {
            if ( IsNewOrAtEnd( ) || IsLoaded( ) )
            {
                auto* modificationBuffer = ModificationBuffer( );
                if ( ( IsLastSegmentInModificationBuffer( ) && timestamp >= modificationBuffer->front( ).Timestamp( ) ) ||
                    ( IsFirstSegmentInModificationBuffer( ) && timestamp <= modificationBuffer->back( ).Timestamp( ) ) ||
                    modificationBuffer->IntervalContains( timestamp ) )
                {
                    auto result = modificationBuffer->Search( timestamp );
                    SetPosition( result.Index( ) + 1 );
                    return result;
                }
            }
            else if ( IsPositioned( ) && currentSegmentData_ )
            {
                if ( ( IsPositionedOnLastSegment( ) && timestamp >= currentSegmentData_->front( ).Timestamp( ) ) ||
                    ( IsPositionedOnFirstSegment( ) && timestamp <= currentSegmentData_->back( ).Timestamp( ) ) ||
                    currentSegmentData_->IntervalContains( timestamp ) )
                {
                    auto result = currentSegmentData_->Search( timestamp );
                    SetPosition( result.Index( ) + 1 );
                    return result;
                }
            }

            auto searchResult = CursorSearch( timestamp );
            if ( searchResult )
            {
                SetPosition( searchResult.Index( ) + 1 );
            }
            return searchResult;

        }


        bool MoveFirst( )
        {
            Flush( );
            CursorMoveFirst( );
            SetPosition( 1 );
            return currentSegmentData_->size( ) >= 1;
        }

        bool MoveLast( )
        {
            Flush( );
            CursorMoveLast( );
            auto position = Position( );
            if ( position )
            {
                SetPosition( position - 1 );
                return position > 1;
            }
            else
            {
                return false;
            }
        }

        bool MoveNext( )
        {
            auto position = IncrementPosition( );
            if ( currentSegmentData_ && position <= currentSegmentData_->size( ) )
            {
                return true;
            }
            else
            {
                Flush( );
                if ( CursorMoveNext( ) )
                {
                    IncrementPosition( );
                    return currentSegmentData_->size( ) > 0;
                }
            }
            return false;
        }

        bool MovePrevious( )
        {
            if ( PreviousInSegment( ) )
            {
                auto position = Position( );
                SetPosition( position - 1 );
                return true;
            }
            else
            {
                Flush( );
                if ( CursorMovePrevious( ) )
                {
                    auto position = Position( );
                    SetPosition( position - 1 );
                    return position > 1;
                }
            }
            return false;
        }

        template<typename Func, typename ...Args>
        requires std::is_invocable_v<Func, const Point&, Args>
            __forceinline size_t ForEach( Func&& func, Args&& ...args )
        {
            size_t result = 0;
            if ( MoveFirst( ) )
            {
                do
                {
                    result += currentSegmentData_->ForEach( std::forward<Func>( func ), std::forward<Args>( args )... );
                } while ( CursorMoveNext( ) );
            }
            return result;
        }

        template<typename Func, typename ...Args>
        requires std::is_invocable_v<Func, const Point&, Args>
            __forceinline size_t ForEach( const DateTime& start, Func&& func, Args&& ...args )
        {
            size_t result = 0;
            auto searchResult = Search( start );
            if ( searchResult )
            {
                result += currentSegmentData_->ForEach1st( searchResult.Index( ), std::forward<Func>( func ), std::forward<Args>( args )... );
                if ( CursorMoveNext( ) )
                {
                    do
                    {
                        result += currentSegmentData_->ForEach( std::forward<Func>( func ), std::forward<Args>( args )... );
                    } while ( CursorMoveNext( ) );
                }
            }
            return result;
        }

        template<typename Func, typename ...Args>
        requires std::is_invocable_v<Func, const Point&, Args>
            __forceinline size_t ForEach( const DateTime& start, const DateTime& end, Func&& func, Args&& ...args )
        {
            size_t result = 0;
            auto searchResult = Search( start );
            if ( searchResult )
            {
                result += currentSegmentData_->ForEach1st( searchResult.Index( ), end, std::forward<Func>( func ), std::forward<Args>( args )... );
                if ( CursorMoveNext( ) )
                {
                    do
                    {
                        result += currentSegmentData_->ForEach( end, std::forward<Func>( func ), std::forward<Args>( args )... );
                    } while ( CursorMoveNext( ) );
                }
            }
            return result;
        }


    };


    template <PointType TP, size_t segmentSize>
    class Transaction
    {
        friend class TimeseriesCursor<TP, segmentSize>;
    public:
        using EngineType = Engine<TP, segmentSize>;
        using KeyData = typename TimeseriesCursor<TP, segmentSize>::KeyData;
    private:
        using TimeseriesInfoType = Internal::TimeseriesInfo<TP, segmentSize>;
        EngineType* engine_;
        LMDB::Transaction lmdbTransaction_;
        std::unordered_map<Guid, std::unique_ptr<TimeseriesInfoType>> timeseriesMap_;
    public:
        Transaction( EngineType* engine, LMDB::Transaction&& lmdbTransaction ) noexcept
            : engine_( engine ), lmdbTransaction_( std::move( lmdbTransaction ) )
        {
        }


        Transaction( const Transaction& other ) = delete;
        Transaction( Transaction&& other ) noexcept
            : engine_( other.engine_ ),
            lmdbTransaction_( std::move( other.lmdbTransaction_ ) ),
            timeseriesMap_( std::move( other.timeseriesMap_ ) )
        {

        }

        Transaction& operator = ( const Transaction& other ) = delete;
        Transaction& operator = ( Transaction&& other ) noexcept
        {
            if ( this != &other )
            {
                engine_ = other.engine_;
                lmdbTransaction_.swap( other.lmdbTransaction_ );
                std::swap( timeseriesMap_, other.timeseriesMap_ );
            }
            return *this;
        }


    private:
        const LMDB::Table& ObjectTable( ) const noexcept;
        const LMDB::Table& TimeseriesDataTable( ) const noexcept;

        TimeseriesInfoType* GetTimeseriesInfo( const Guid& timeseries )
        {
            auto it = timeseriesMap_.find( timeseries );
            if ( it != timeseriesMap_.end( ) )
            {
                return it->second.get( );
            }
            else
            {
                auto timeseriesInfo = std::make_unique<TimeseriesInfoType>( timeseries );
                auto* result = timeseriesInfo.get( );
                timeseriesMap_.emplace( timeseries, std::move( timeseriesInfo ) );
                return result;
            }
        }

        void SaveCachedUpdates( )
        {
            auto database = TimeseriesDataTable( );
            for ( auto& entry : timeseriesMap_ )
            {
                TimeseriesInfoType* timeseriesInfo = entry.second.get( );
                if ( timeseriesInfo->Changes( ) )
                {
                    timeseriesInfo->SetChanges( 0 );
                    auto modificationBuffer = timeseriesInfo->ModificationBuffer( );
                    const auto& timeseries = timeseriesInfo->Id( );
                    auto loadedTimestamp = timeseriesInfo->LoadedTimestamp( );
                    auto& first = modificationBuffer->front( );
                    if ( loadedTimestamp && ( loadedTimestamp != first.Timestamp( ) ) )
                    {
                        // The key changed, so delete previously stored segment
                        KeyData deleteKey( timeseries, loadedTimestamp );
                        lmdbTransaction_.Delete( database, deleteKey );
                    }
                    KeyData keyData( timeseries, first );
                    lmdbTransaction_.Write( database, keyData, *modificationBuffer );
                    timeseriesInfo->SetLoadedTimestamp( first.Timestamp( ) );
                }
            }
        }

    public:

        size_t Id( ) const noexcept
        {
            return lmdbTransaction_.Id( );
        }

        void Close( ) noexcept
        {
            lmdbTransaction_.Close( );
            timeseriesMap_.clear( );
        }
        void Abort( ) noexcept
        {
            lmdbTransaction_.Close( );
            timeseriesMap_.clear( );
        }

        void Commit( )
        {
            SaveCachedUpdates( );
            lmdbTransaction_.Commit( );
            timeseriesMap_.clear( );
        }

        void Reset( ) noexcept
        {
            lmdbTransaction_.Reset( );
            timeseriesMap_.clear( );
        }

        void Renew( )
        {
            lmdbTransaction_.Renew( );
        }


        LMDB::Database OpenDatabase( const char* name, LMDB::DatabaseFlags databaseFlags = LMDB::DatabaseFlags::None )
        {
            return lmdbTransaction_.OpenDatabase( name, databaseFlags );
        }

        LMDB::Database OpenDatabase( LMDB::DatabaseFlags databaseFlags = LMDB::DatabaseFlags::None )
        {
            return lmdbTransaction_.OpenDatabase( databaseFlags );
        }

        void Truncate( const LMDB::Database& database )
        {
            lmdbTransaction_.Truncate( database );
        }

        void Drop( const LMDB::Database& database )
        {
            lmdbTransaction_.Drop( database );
        }

        int Write( const LMDB::Database& database, const MDB_val& key, const MDB_val& value, LMDB::WriteFlags writeFlags )
        {
            return lmdbTransaction_.Write( database, key, value, writeFlags );
        }

        int Write( const LMDB::Database& database, const LMDB::Value& key, const LMDB::Value& value, LMDB::WriteFlags writeFlags )
        {
            return lmdbTransaction_.Write( database, key, value, writeFlags );
        }

        template<typename KeyType, typename ValueType>
        requires ( std::is_base_of_v<MDB_val, KeyType> == false
            && std::is_base_of_v<MDB_val, ValueType> == false )
            int Write( const LMDB::Database& database, const KeyType& key, const ValueType& value, LMDB::WriteFlags writeFlags )
        {
            LMDB::Value kv( key );
            LMDB::Value dv( value );
            return Write( database, kv, dv, writeFlags );
        }

        LMDB::Cursor OpenCursor( const LMDB::Database& database ) const
        {
            return lmdbTransaction_.OpenCursor( database );
        }

        void SetCompare( const LMDB::Database& database, MDB_cmp_func* cmp )
        {
            lmdbTransaction_.SetCompare( database, cmp );
        }

        TimeseriesCursor<TP, segmentSize> OpenTimeseries( const Guid& timeseriesId )
        {
            auto cursor = lmdbTransaction_.OpenCursor( TimeseriesDataTable( ) );
            TimeseriesCursor<TP, segmentSize> result( this, timeseriesId, std::move( cursor ) );
            return result;
        }

    };

    template<PointType TP, size_t segmentSize>
    inline typename TimeseriesCursor<TP, segmentSize>::TimeseriesInfoType* TimeseriesCursor<TP, segmentSize>::GetTimeseriesInfo( const Guid& timeseriesId )
    {
        return transaction_->GetTimeseriesInfo( timeseriesId );
    }


    struct EngineOptions
    {
        constexpr static size_t DefaultMaxDatabaseSize = 500ull * 1024ull * 1024ull * 1024ull;
        AnsiString DatabaseDirectory;
        bool Create = false;
        size_t MaxDatabaseSize = DefaultMaxDatabaseSize;

        EngineOptions( )
        {
        }

        EngineOptions( const AnsiString& databaseDirectory, bool create, size_t maxDatabaseSize = DefaultMaxDatabaseSize )
            : DatabaseDirectory( databaseDirectory ), Create( create ), MaxDatabaseSize( maxDatabaseSize )
        {
        }
    };




    template<PointType TP = TimeseriesPoint,
        size_t segmentSize = TimeseriesCursorSegmentSize>
        class Engine
    {
        friend class Transaction<TP, segmentSize>;

        constexpr static size_t MaxDatabases = 2;
        constexpr static char objectTableName[] = "o";
        constexpr static char timeseriesDataTableName[] = "t";
        const EngineOptions& options_;
        LMDB::Environment environment_;
        LMDB::Table objectTable_;
        LMDB::Table timeseriesDataTable_;

    public:
        using TimeseriesCursor = TimeseriesCursor<TP, segmentSize>;
        using KeyData = typename TimeseriesCursor::KeyData;
        using SegmentType = typename TimeseriesCursor::SegmentType;
        using Point = TP;
        constexpr static size_t SegmentMaxSize = SegmentType::MaxSize;
        Engine( const EngineOptions& options )
            : options_( options ),
            environment_( options_.DatabaseDirectory,
                options_.MaxDatabaseSize,
                MaxDatabases,
                LMDB::EnvironmentFlags::WriteMemMap )
        {
            if ( options_.Create )
            {
                CreateEnvironment( );
            }
            else
            {
                OpenEnvironment( );
            }
        }

        ~Engine( )
        {
            environment_.CloseDatabase( objectTable_ );
            environment_.CloseDatabase( timeseriesDataTable_ );
            environment_.Close( );
        }
    private:
        void CreateEnvironment( )
        {
            bool dropped = false;
            auto transaction = BeginTransaction( );
            auto objectTable = transaction.OpenDatabase( objectTableName, LMDB::DatabaseFlags::None );
            if ( objectTable )
            {
                transaction.SetCompare( objectTable, ObjectCompare );
                transaction.Drop( objectTable );
                dropped = true;
            }
            auto timeseriesTable = transaction.OpenDatabase( timeseriesDataTableName, LMDB::DatabaseFlags::None );
            if ( timeseriesTable )
            {
                transaction.SetCompare( timeseriesTable, TimeseriesCompare );
                transaction.Drop( timeseriesTable );
                dropped = true;
            }
            if ( dropped )
            {
                transaction.Commit( );
                transaction = BeginTransaction( );
            }
            objectTable_ = transaction.OpenDatabase( objectTableName, LMDB::DatabaseFlags::Create );
            transaction.SetCompare( objectTable_, ObjectCompare );
            timeseriesDataTable_ = transaction.OpenDatabase( timeseriesDataTableName, LMDB::DatabaseFlags::Create );
            transaction.SetCompare( timeseriesDataTable_, TimeseriesCompare );
            transaction.Commit( );
        }
        void OpenEnvironment( )
        {
            auto transaction = BeginTransaction( );
            objectTable_ = transaction.OpenDatabase( objectTableName, LMDB::DatabaseFlags::None );
            if ( !objectTable_ )
            {
                throw Exception( "Unable to open object table" );
            }
            transaction.SetCompare( objectTable_, ObjectCompare );
            timeseriesDataTable_ = transaction.OpenDatabase( timeseriesDataTableName, LMDB::DatabaseFlags::None );
            if ( !timeseriesDataTable_ )
            {
                throw Exception( "Unable to open timeseries table" );
            }
            transaction.SetCompare( timeseriesDataTable_, TimeseriesCompare );
            transaction.Commit( );
        }


    public:
        using TransactionFlags = LMDB::TransactionFlags;
        Transaction<TP, segmentSize> BeginTransaction( TransactionFlags transactionFlags = TransactionFlags::None ) const
        {
            auto lmdbTransaction = environment_.BeginTransaction( transactionFlags );
            Transaction<TP, segmentSize> result( const_cast<Engine*>( this ), std::move( lmdbTransaction ) );
            return result;
        }
    private:
        const LMDB::Table& ObjectTable( ) const noexcept
        {
            return objectTable_;
        }
        const LMDB::Table& TimeseriesDataTable( ) const noexcept
        {
            return timeseriesDataTable_;
        }




    private:
        static int TimeseriesCompare( const MDB_val* a, const MDB_val* b )
        {
            KeyData& first = *(KeyData*)a->mv_data;
            KeyData& second = *(KeyData*)b->mv_data;
            auto rc = first.Timeseries( ).CompareTo( second.Timeseries( ) );
            if ( !rc )
            {
                rc = first.Timestamp( ).CompareTo( second.Timestamp( ) );
            }
            return rc;
        }
        static int ObjectCompare( const MDB_val* a, const MDB_val* b )
        {
            Guid& first = *(Guid*)a->mv_data;
            Guid& second = *(Guid*)b->mv_data;
            auto rc = first.CompareTo( second );
            return rc;
        }
    };

    template <PointType TP, size_t segmentSize>
    inline const LMDB::Table& Transaction<TP, segmentSize>::ObjectTable( ) const noexcept
    {
        return engine_->ObjectTable( );
    }
    template <PointType TP, size_t segmentSize>
    inline const LMDB::Table& Transaction<TP, segmentSize>::TimeseriesDataTable( ) const noexcept
    {
        return engine_->TimeseriesDataTable( );
    }

    using TimeseriesEngine = Engine<>;
    using TimeseriesEngineOptions = EngineOptions;

}



#endif

