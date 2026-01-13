#pragma once
#ifndef HARLINN_COMMON_CORE_HCCDATA_H_
#define HARLINN_COMMON_CORE_HCCDATA_H_

/*
   Copyright 2024-2026 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "HCCDef.h"
#include "HCCBinaryReader.h"
#include "HCCBinaryWriter.h"

namespace Harlinn::Common::Core::Data
{
    enum class ObjectState : Byte
    {
        Unknown,
        New,
        Stored,
        Changed,
        Deleted,
        ConcurrencyConflict
    };

    template<typename ObjectT,typename KeyT>
        requires std::is_enum_v<ObjectT>
    class BaseData : public std::enable_shared_from_this<BaseData<ObjectT, KeyT>>
    {
    public:
        using Base = std::enable_shared_from_this<BaseData<ObjectT, KeyT>>;
        using ObjectType = ObjectT;
        using KeyType = KeyT;
        static constexpr ObjectType KIND = {};
    private:
        KeyType id_;
        ObjectState objectState_ = ObjectState::Unknown;
    public:
        constexpr BaseData( ) = default;
        virtual ~BaseData( ) = default;
    protected:
        void OnPropertyChanged( )
        {
            if ( objectState_ == ObjectState::Stored || objectState_ == ObjectState::ConcurrencyConflict )
            {
                objectState_ = ObjectState::Changed;
            }
        }
    public:
        template<IO::StreamWriter StreamT>
        void WriteTo( IO::BinaryWriter<StreamT>& destination ) const
        {
            auto typeCode = GetObjectType( );
            destination.Write( typeCode );
            destination.Write( objectState_ );
            destination.Write( id_ );
        }

        template<IO::StreamReader StreamT>
        static ObjectType ReadObjectType( IO::BinaryReader<StreamT>& source )
        {
            return source.Read<ObjectType>( );
        }

        template<IO::StreamReader StreamT>
        void ReadFrom( IO::BinaryReader<StreamT>& source )
        {
            objectState_ = source.Read<Data::ObjectState>( );
            id_ = source.Read<KeyType>( );
        }


        virtual [[nodiscard]] ObjectType GetObjectType( ) const noexcept = 0;

        virtual [[nodiscard]] bool IsOfType( ObjectType objectType ) const noexcept
        {
            return objectType == KIND;
        }

        constexpr [[nodiscard]] Data::ObjectState ObjectState( ) const noexcept
        {
            return objectState_;
        }

        constexpr void SetObjectState( Data::ObjectState value ) noexcept
        {
            if ( objectState_ != value )
            {
                objectState_ = value;
            }
        }


        constexpr [[nodiscard]] const KeyType& Id( ) const noexcept
        {
            return id_;
        }
        void SetId( const KeyType& value ) noexcept
        {
            if ( id_ != value )
            {
                id_ = value;
            }
        }

        virtual [[nodiscard]] std::shared_ptr<BaseData> Create( ) const = 0;

        virtual [[nodiscard]] std::shared_ptr<BaseData> Clone( ) const
        {
            auto result = this->Create( );
            this->AssignTo( *result );
            return result;
        }

        virtual void AssignTo( BaseData& target ) const
        {
            target.objectState_ = objectState_;
            target.id_ = id_;
        }

        virtual [[nodiscard]] bool IsEqualTo( const BaseData& other ) const
        {
            return other.id_ == id_;
        }
    };

#define HCC_BOOLEAN_DATA_PROPERTY(propertyName,backingField) \
    bool propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( bool value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_SBYTE_DATA_PROPERTY(propertyName,backingField) \
    SByte propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( SByte value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_BYTE_DATA_PROPERTY(propertyName,backingField) \
    Byte propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( Byte value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_INT16_DATA_PROPERTY(propertyName,backingField) \
    Int16 propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( Int16 value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_UINT16_DATA_PROPERTY(propertyName,backingField) \
    UInt16 propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( UInt16 value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_INT32_DATA_PROPERTY(propertyName,backingField) \
    Int32 propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( Int32 value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_UINT32_DATA_PROPERTY(propertyName,backingField) \
    UInt32 propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( UInt32 value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }


#define HCC_INT64_DATA_PROPERTY(propertyName,backingField) \
    Int64 propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( Int64 value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_UINT64_DATA_PROPERTY(propertyName,backingField) \
    UInt64 propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( UInt64 value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }


#define HCC_ENUM_DATA_PROPERTY(propertyName,backingField) \
    decltype(backingField) propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( decltype(backingField) value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_SINGLE_DATA_PROPERTY(propertyName,backingField) \
    float propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( float value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_DOUBLE_DATA_PROPERTY(propertyName,backingField) \
    double propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( double value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_CURRENCY_DATA_PROPERTY(propertyName,backingField) \
    const Currency& propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( const Currency& value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_DATETIME_DATA_PROPERTY(propertyName,backingField) \
    const DateTime& propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( const DateTime& value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_TIMESPAN_DATA_PROPERTY(propertyName,backingField) \
    const TimeSpan& propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( const TimeSpan& value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_GUID_DATA_PROPERTY(propertyName,backingField) \
    const Guid& propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( const Guid& value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_STRING_DATA_PROPERTY(propertyName,backingField) \
    const WideString& propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( const WideString& value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_BINARY_DATA_PROPERTY(propertyName,backingField) \
    const std::vector<Byte>& propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( const std::vector<Byte>& value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }


#define HCC_ROWVERSION_DATA_PROPERTY(propertyName,backingField) \
    Int64 propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( Int64 value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }


#define HCC_REFERENCE_DATA_PROPERTY(propertyName,backingField) \
    const Guid& propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( const Guid& value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

#define HCC_TIMESERIES_DATA_PROPERTY(propertyName,backingField) \
    const Guid& propertyName( ) const noexcept \
    { \
        return backingField; \
    } \
    void Set##propertyName( const Guid& value ) \
    { \
        if ( value != backingField ) \
        { \
            backingField = value; \
            OnPropertyChanged( ); \
        } \
    }

    
    template<typename ObjectT, typename KeyT>
        requires std::is_enum_v<ObjectT>
    class DeletedData 
    {
    public:
        using ObjectType = ObjectT;
        using KeyType = KeyT;
    private:
        ObjectType type_ = {};
        KeyType key_ = {};
        Int64 rowVersion_ = 0;
    public:
        DeletedData()
        { }
        DeletedData( ObjectType type, KeyType key, Int64 rowVersion )
            : type_( type ), key_( key ), rowVersion_( rowVersion )
        {
        }

        ObjectType Type( ) const
        {
            return type_;
        }

        void SetType( ObjectType type )
        {
            type_ = type;
        }

        
        const KeyType& Key( ) const
        {
            return key_;
        }
        void SetKey( const KeyType& key )
        {
            key_ = key;
        }

        Int64 RowVersion( ) const
        {
            return rowVersion_;
        }
        void SetRowVersion( Int64 rowVersion )
        {
            rowVersion_ = rowVersion;
        }

        template<IO::StreamWriter StreamT>
        void WriteTo( IO::BinaryWriter<StreamT>& destination ) const
        {
            destination.Write( type_ );
            destination.Write( key_ );
            destination.Write( rowVersion_ );
        }

        template<IO::StreamReader StreamT>
        void ReadFrom( IO::BinaryReader<StreamT>& source )
        {
            type_ = source.Read<ObjectType>( );
            key_ = source.Read<KeyType>( );
            rowVersion_ = source.Read<Int64>( );
        }

    };



    enum DeleteTimeseriesRangeType : Byte
    {
        Unknown = 0,
        Clear,
        From,
        Until,
        Over
    };

    template<typename TKind>
    class DeleteTimeseriesRangeData : public std::enable_shared_from_this< DeleteTimeseriesRangeData<TKind> >
    {
        DeleteTimeseriesRangeType rangeType_ = DeleteTimeseriesRangeType::Unknown;
        Guid timeseriesId_;
        TKind timeseriesType_ = {};
    
    protected: 
        DeleteTimeseriesRangeData( DeleteTimeseriesRangeType rangeType )
        {
            rangeType_ = rangeType;
        }
    public:
        DeleteTimeseriesRangeData( DeleteTimeseriesRangeType rangeType, Guid id, TKind timeseriesType )
        {
            rangeType_ = rangeType;
            timeseriesId_ = id;
            timeseriesType_ = timeseriesType;
        }

        DeleteTimeseriesRangeType RangeType( ) const
        { 
            return rangeType_; 
        }

        Guid TimeseriesId( ) const
        {
            return timeseriesId_;
        }
        void SetTimeseriesId(const Guid& timeseriesId )
        {
            timeseriesId_ = timeseriesId;
        }
        TKind TimeseriesType( ) const
        {
            return timeseriesType_;
        }
        void SetTimeseriesType( TKind timeseriesType ) 
        {
            timeseriesType_ = timeseriesType;

        }

        template<IO::StreamWriter StreamT>
        void WriteTo( IO::BinaryWriter<StreamT>& destination ) const
        {
            destination.Write( static_cast<Byte>(rangeType_) );
            destination.Write( timeseriesId_ );
            destination.Write( timeseriesType_ );
        }

        template<IO::StreamReader StreamT>
        static DeleteTimeseriesRangeType ReadRangeType( IO::BinaryReader<StreamT>& source )
        {
            auto result = ( DeleteTimeseriesRangeType )source.ReadByte( );
            return result;
        }

        template<IO::StreamReader StreamT>
        void ReadFrom( IO::BinaryReader<StreamT>& source )
        {
            timeseriesId_ = source.Read<Guid>( );
            timeseriesType_ = source.Read<TKind>( );
        }
    };

    template<typename TKind>
    class DeleteClearTimeseriesRangeData : public DeleteTimeseriesRangeData<TKind>
    {
    public: 
        using Base = DeleteTimeseriesRangeData<TKind>;
        DeleteClearTimeseriesRangeData( )
            : Base( DeleteTimeseriesRangeType::Clear )
        {
        }
        DeleteClearTimeseriesRangeData( Guid id, TKind timeseriesType )
            : Base( DeleteTimeseriesRangeType::Clear, id, timeseriesType )
        {
        }
    };

    template<typename TKind>
    class DeleteFromTimeseriesRangeData : public DeleteTimeseriesRangeData<TKind>
    {
        DateTime from_;
    public:
        using Base = DeleteTimeseriesRangeData<TKind>;
        DeleteFromTimeseriesRangeData( )
            : Base( DeleteTimeseriesRangeType::From )
        {
        }
        DeleteFromTimeseriesRangeData( const Guid& id, TKind timeseriesType )
            : Base( DeleteTimeseriesRangeType::From, id, timeseriesType )
        {
        }

        DeleteFromTimeseriesRangeData( const Guid& id, TKind timeseriesType, const DateTime& from )
            : Base( DeleteTimeseriesRangeType::From, id, timeseriesType ), from_( from )
        {
        }

        DateTime From( ) const
        {
            return from_;
        }
        void SetFrom( const DateTime& from )
        {
            from_ = from;
        }

        template<IO::StreamWriter StreamT>
        void WriteTo( IO::BinaryWriter<StreamT>& destination ) const
        {
            Base::WriteTo( destination );
            destination.Write( from_ );
        }

        template<IO::StreamReader StreamT>
        void ReadFrom( IO::BinaryReader<StreamT>& source )
        {
            Base::ReadFrom( source );
            from_ = source.Read<DateTime>( );
            
        }
    };

    template<typename TKind>
    class DeleteUntilTimeseriesRangeData : public DeleteTimeseriesRangeData<TKind>
    {
        DateTime until_;
    public:
        using Base = DeleteTimeseriesRangeData<TKind>;
        DeleteUntilTimeseriesRangeData( )
            : Base( DeleteTimeseriesRangeType::Until )
        {
        }
        DeleteUntilTimeseriesRangeData( const Guid& id, TKind timeseriesType )
            : Base( DeleteTimeseriesRangeType::Until, id, timeseriesType )
        {
        }

        DeleteUntilTimeseriesRangeData( const Guid& id, TKind timeseriesType, const DateTime& until )
            : Base( DeleteTimeseriesRangeType::Until, id, timeseriesType ), until_( until )
        {
        }

        DateTime Until( ) const
        {
            return until_;
        }
        void SetUntil( const DateTime& until )
        {
            until_ = until;
        }

        template<IO::StreamWriter StreamT>
        void WriteTo( IO::BinaryWriter<StreamT>& destination ) const
        {
            Base::WriteTo( destination );
            destination.Write( until_ );
        }

        template<IO::StreamReader StreamT>
        void ReadFrom( IO::BinaryReader<StreamT>& source )
        {
            Base::ReadFrom( source );
            until_ = source.Read<DateTime>( );
        }
    };

    template<typename TKind>
    class DeleteOverTimeseriesRangeData : public DeleteTimeseriesRangeData<TKind>
    {
        DateTime from_;
        DateTime until_;
    public:
        using Base = DeleteTimeseriesRangeData<TKind>;
        DeleteOverTimeseriesRangeData( )
            : Base( DeleteTimeseriesRangeType::Over )
        {
        }
        DeleteOverTimeseriesRangeData( const Guid& id, TKind timeseriesType )
            : Base( DeleteTimeseriesRangeType::Over, id, timeseriesType )
        {
        }

        DeleteOverTimeseriesRangeData( const Guid& id, TKind timeseriesType, const DateTime& from, const DateTime& until )
            : Base( DeleteTimeseriesRangeType::Over, id, timeseriesType ), from_( from ), until_( until )
        {
        }

        DateTime From( ) const
        {
            return from_;
        }
        void SetFrom( const DateTime& from )
        {
            from_ = from;
        }

        DateTime Until( ) const
        {
            return until_;
        }
        void SetUntil( const DateTime& until )
        {
            until_ = until;
        }

        template<IO::StreamWriter StreamT>
        void WriteTo( IO::BinaryWriter<StreamT>& destination ) const
        {
            Base::WriteTo( destination );
            destination.Write( from_ );
            destination.Write( until_ );
        }

        template<IO::StreamReader StreamT>
        void ReadFrom( IO::BinaryReader<StreamT>& source )
        {
            Base::ReadFrom( source );
            from_ = source.Read<DateTime>( );
            until_ = source.Read<DateTime>( );
        }
    };

    template<typename TKind>
    class DeleteTimeseriesRangeFactory
    {
    public:
        static std::shared_ptr<DeleteTimeseriesRangeData<TKind>> Create( DeleteTimeseriesRangeType rangeType )
        {
            std::shared_ptr<DeleteTimeseriesRangeData<TKind>> result;
            switch ( rangeType )
            {
                case DeleteTimeseriesRangeType::Clear:
                {
                    result = std::make_shared<DeleteClearTimeseriesRangeData<TKind>>( );
                }
                break;
                case DeleteTimeseriesRangeType::From:
                {
                    result = std::make_shared<DeleteFromTimeseriesRangeData<TKind>>( );
                }
                break;
                case DeleteTimeseriesRangeType::Until:
                {
                    result = std::make_shared<DeleteUntilTimeseriesRangeData<TKind>>( );
                }
                break;
                case DeleteTimeseriesRangeType::Over:
                {
                    result = std::make_shared<DeleteOverTimeseriesRangeData<TKind>>( );
                }
                break;
            }
            return result;
        }
    };

    template<typename TKind>
    class DeleteTimeseriesRangeSerializer
    {
    public:
        template<IO::StreamWriter StreamT>
        static void WriteTo( const DeleteTimeseriesRangeData<TKind>& data, IO::BinaryWriter<StreamT>& destination )
        {
            auto rangeType = data.RangeType( );
            switch ( rangeType )
            {
                case DeleteTimeseriesRangeType::Clear:
                {
                    const auto& deleteClearTimeseriesRangeData = static_cast<const DeleteClearTimeseriesRangeData<TKind>&>( data );
                    deleteClearTimeseriesRangeData.WriteTo( destination );
                }
                break;
                case DeleteTimeseriesRangeType::From:
                {
                    const auto& deleteFromTimeseriesRangeData = static_cast< const DeleteFromTimeseriesRangeData<TKind>& >( data );
                    deleteFromTimeseriesRangeData.WriteTo( destination );
                }
                break;
                case DeleteTimeseriesRangeType::Until:
                {
                    const auto& deleteUntilTimeseriesRangeData = static_cast< const DeleteUntilTimeseriesRangeData<TKind>& >( data );
                    deleteUntilTimeseriesRangeData.WriteTo( destination );
                }
                break;
                case DeleteTimeseriesRangeType::Over:
                {
                    const auto& deleteOverTimeseriesRangeData = static_cast< const DeleteOverTimeseriesRangeData<TKind>& >( data );
                    deleteOverTimeseriesRangeData.WriteTo( destination );
                }
                break;
            }
        }
        template<IO::StreamReader StreamT>
        static std::shared_ptr<DeleteTimeseriesRangeData<TKind>> ReadFrom( IO::BinaryReader<StreamT>& source )
        {
            auto rangeType = DeleteTimeseriesRangeData<TKind>::ReadRangeType( source );
            switch ( rangeType )
            {
                case DeleteTimeseriesRangeType::Clear:
                {
                    auto result = std::make_shared<DeleteClearTimeseriesRangeData<TKind>>( );
                    result->ReadFrom( source );
                    return result;
                }
                break;
                case DeleteTimeseriesRangeType::From:
                {
                    auto result = std::make_shared<DeleteFromTimeseriesRangeData<TKind>>( );
                    result->ReadFrom( source );
                    return result;
                }
                break;
                case DeleteTimeseriesRangeType::Until:
                {
                    auto result = std::make_shared<DeleteUntilTimeseriesRangeData<TKind>>( );
                    result->ReadFrom( source );
                    return result;
                }
                break;
                case DeleteTimeseriesRangeType::Over:
                {
                    auto result = std::make_shared<DeleteOverTimeseriesRangeData<TKind>>( );
                    result->ReadFrom( source );
                    return result;
                }
                break;
            }
            return {};
        }

    };


}


#endif
