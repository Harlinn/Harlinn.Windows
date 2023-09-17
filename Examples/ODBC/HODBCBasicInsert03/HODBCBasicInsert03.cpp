#include <HODBC.h>
#include <HCCApplication.h>

using namespace Harlinn::Common;
using namespace Harlinn::ODBC;
using namespace Harlinn;


struct Track
{
    Core::Guid id_;
    Int64 optimisticLockField_ = 0;
    Core::Guid tracker_;
    Int64 trackNumber_ = 0;
    DateTime timestamp_;
};

struct TrackValue
{
    Core::Guid id_;
    Int64 optimisticLockField_ = 0;
    Core::Guid track_;
    DateTime timestamp_;
    Int32 flags_ = 0;
    Int32 status_ = 0;
    double latitude_ = 0.0;
    double longitude_ = 0.0;
    double speed_ = 0.0;
    double course_ = 0.0;
    double heading_ = 0.0;
};

class TrackDataReader : public DataReaderBase
{
    Track track_;
public:
    static constexpr SQLUSMALLINT ID_ID = 1;
    static constexpr SQLUSMALLINT OPTIMISTICLOCKFIELD_ID = 2;
    static constexpr SQLUSMALLINT TRACKER_ID = 3;
    static constexpr SQLUSMALLINT TRACKNUMBER_ID = 4;
    static constexpr SQLUSMALLINT TIMESTAMP_ID = 5;

    using Base = DataReaderBase;

    static constexpr wchar_t sql_[ ] = L"SELECT [Id], [OptimisticLockField], [Tracker], [TrackNumber], [Timestamp] FROM [dbo].[Track]";
    static constexpr wchar_t lastUpdatedSql_[ ] = L"SELECT [Id], [OptimisticLockField], [Tracker], [TrackNumber], [Timestamp] FROM [dbo].[TrackViewEx]";


    TrackDataReader( const Statement* statement )
        : Base( statement )
    {
        Bind( ID_ID, &track_.id_ );
        Bind( OPTIMISTICLOCKFIELD_ID, &track_.optimisticLockField_ );
        Bind( TRACKER_ID, &track_.tracker_ );
        Bind( TRACKNUMBER_ID, &track_.trackNumber_ );
        Bind( TIMESTAMP_ID, reinterpret_cast<Int64*>( &track_.timestamp_ ) );
    }

    constexpr const Core::Guid& Id( ) const noexcept
    {
        return track_.id_;
    }
    
    constexpr Int64 OptimisticLockField( ) const noexcept
    {
        return track_.optimisticLockField_;
    }
    constexpr const Core::Guid& Tracker( ) const noexcept
    {
        return track_.tracker_;
    }

    constexpr Int64 TrackNumber( ) const noexcept
    {
        return track_.trackNumber_;
    }

    constexpr Core::DateTime Timestamp( ) const noexcept
    {
        return track_.timestamp_;
    }

    void AssignTo( Track& track ) const
    {
        track = track_;
    }

};

class TrackDataWriter 
{
    const Connection& connection_;

    Track track_;

    Statement insertStatement_;
    Statement updateStatement_;
    Statement deleteStatement_;
public:
    static constexpr wchar_t INSERT_[ ] = L"INSERT INTO [dbo].[Track] ([Id], [OptimisticLockField], [Tracker], [TrackNumber], [Timestamp]) VALUES(?,?,?,?,?)";
    static constexpr wchar_t UPDATE_[ ] = L"UPDATE [dbo].[Track] SET [OptimisticLockField] = ?, [Tracker] = ?, [TrackNumber] = ?, [Timestamp] = ? WHERE [Id] = ?";
    static constexpr wchar_t DELETE_[ ] = L"DELETE FROM [dbo].[Track] WHERE [Id] = ?";

    TrackDataWriter( const Connection& connection )
        : connection_( connection )
    {
        CreateAndBindInsert( connection );
        CreateAndBindUpdate( connection );
        CreateAndBindDelete( connection );
    }

    void CreateAndBindInsert( const Connection& connection )
    {
        insertStatement_ = connection.CreateStatement( );
        insertStatement_.Prepare( INSERT_ );

        insertStatement_.BindParameter(1, ParameterDirection::Input, &track_.id_);
        insertStatement_.BindParameter(2, ParameterDirection::Input, &track_.optimisticLockField_);
        insertStatement_.BindParameter(3, ParameterDirection::Input, &track_.tracker_);
        insertStatement_.BindParameter(4, ParameterDirection::Input, &track_.trackNumber_);
        insertStatement_.BindParameter(5, ParameterDirection::Input, reinterpret_cast<Int64*>( &track_.timestamp_) );

    }
    void CreateAndBindUpdate( const Connection& connection )
    {
        updateStatement_ = connection.CreateStatement( );
        updateStatement_.Prepare( UPDATE_ );
        
        updateStatement_.BindParameter( 1, ParameterDirection::Input, &track_.optimisticLockField_ );
        updateStatement_.BindParameter( 2, ParameterDirection::Input, &track_.tracker_ );
        updateStatement_.BindParameter( 3, ParameterDirection::Input, &track_.trackNumber_ );
        updateStatement_.BindParameter( 4, ParameterDirection::Input, reinterpret_cast< Int64* >( &track_.timestamp_ ) );
        updateStatement_.BindParameter( 5, ParameterDirection::Input, &track_.id_ );

    }
    void CreateAndBindDelete( const Connection& connection )
    {
        deleteStatement_ = connection.CreateStatement( );
        deleteStatement_.Prepare( DELETE_ );

        deleteStatement_.BindParameter( 1, ParameterDirection::Input, &track_.id_ );
    }

    ODBC::Result Insert( bool commit = true )
    {
        auto result = insertStatement_.Execute( );
        if ( commit )
        {
            connection_.Commit( );
        }
        return result;
    }

    ODBC::Result Update( bool commit = true )
    {
        auto result = updateStatement_.Execute( );
        if ( commit )
        {
            connection_.Commit( );
        }
        return result;
    }

    ODBC::Result Delete( bool commit = true )
    {
        auto result = deleteStatement_.Execute( );
        if ( commit )
        {
            connection_.Commit( );
        }
        return result;
    }


    void Assign( const Track& track )
    {
        track_ = track;
    }

    constexpr const Core::Guid& Id( ) const noexcept
    {
        return track_.id_;
    }
    void SetId( Core::Guid& id )
    {
        track_.id_ = id;
    }

    constexpr Int64 OptimisticLockField( ) const noexcept
    {
        return track_.optimisticLockField_;
    }
    void SetOptimisticLockField( Int64 optimisticLockField )
    {
        track_.optimisticLockField_ = optimisticLockField;
    }

    constexpr const Core::Guid& Tracker( ) const noexcept
    {
        return track_.tracker_;
    }
    void SetTracker( const Core::Guid& tracker )
    {
        track_.tracker_ = tracker;
    }

    constexpr Int64 TrackNumber( ) const noexcept
    {
        return track_.trackNumber_;
    }
    void SetTrackNumber( Int64 trackNumber )
    {
        track_.trackNumber_ = trackNumber;
    }

    constexpr Core::DateTime Timestamp( ) const noexcept
    {
        return track_.timestamp_;
    }
    void SetTimestamp( Core::DateTime timestamp )
    {
        track_.timestamp_ = timestamp;
    }

};



class TrackValueDataReader : public DataReaderBase
{
    TrackValue trackValue_;
public:
    
    static constexpr SQLUSMALLINT ID_ID = 1;
    static constexpr SQLUSMALLINT OPTIMISTICLOCKFIELD_ID = 2;
    static constexpr SQLUSMALLINT TRACK_ID = 3;
    static constexpr SQLUSMALLINT TIMESTAMP_ID = 4;
    static constexpr SQLUSMALLINT FLAGS_ID = 5;
    static constexpr SQLUSMALLINT STATUS_ID = 6;
    static constexpr SQLUSMALLINT LATITUDE_ID = 7;
    static constexpr SQLUSMALLINT LONGITUDE_ID = 8;
    static constexpr SQLUSMALLINT SPEED_ID = 9;
    static constexpr SQLUSMALLINT COURSE_ID = 10;
    static constexpr SQLUSMALLINT HEADING_ID = 11;

    using Base = DataReaderBase;

    static constexpr wchar_t sql_[] = L"SELECT [Id], [OptimisticLockField], [Track], [Timestamp], [Flags], [Status], [Latitude], [Longitude], [Speed], [Course], [Heading] FROM [dbo].[TrackValues]";

    TrackValueDataReader( const Statement* statement )
        : Base( statement )
    {
        Bind( ID_ID, &trackValue_.id_);
        Bind( OPTIMISTICLOCKFIELD_ID, &trackValue_.optimisticLockField_);
        Bind( TRACK_ID, &trackValue_.track_);
        Bind( TIMESTAMP_ID, reinterpret_cast< Int64* >( &trackValue_.timestamp_ ));
        Bind( FLAGS_ID, &trackValue_.flags_);
        Bind( STATUS_ID, &trackValue_.status_);
        Bind( LATITUDE_ID, &trackValue_.latitude_);
        Bind( LONGITUDE_ID, &trackValue_.longitude_);
        Bind( SPEED_ID, &trackValue_.speed_);
        Bind( COURSE_ID, &trackValue_.course_);
        Bind( HEADING_ID, &trackValue_.heading_);
    }

    void AssignTo( TrackValue& trackValue ) const
    {
        trackValue = trackValue_;
    }

    constexpr const Core::Guid& Id( ) const noexcept
    {
        return trackValue_.id_;
    }

    constexpr Int64 OptimisticLockField( ) const noexcept
    {
        return trackValue_.optimisticLockField_;
    }

    constexpr const Core::Guid& Track( ) const noexcept
    {
        return trackValue_.track_;
    }
    constexpr Core::DateTime Timestamp( ) const noexcept
    {
        return  trackValue_.timestamp_;
    }
    constexpr Int32 Flags( ) const noexcept
    {
        return  trackValue_.flags_;
    }
    constexpr Int32 Status( ) const noexcept
    {
        return  trackValue_.status_;
    }
    constexpr double Latitude( ) const noexcept
    {
        return  trackValue_.latitude_;
    }
    constexpr double Longitude( ) const noexcept
    {
        return  trackValue_.longitude_;
    }
    constexpr double Speed( ) const noexcept
    {
        return  trackValue_.speed_;
    }
    constexpr double Course( ) const noexcept
    {
        return  trackValue_.course_;
    }
    constexpr double Heading( ) const noexcept
    {
        return  trackValue_.heading_;
    }
};


class TrackValueDataWriter
{
    const Connection& connection_;
    TrackValue trackValue_;

    Statement insertStatement_;
    Statement updateStatement_;
    Statement deleteStatement_;
public:
    static constexpr wchar_t INSERT_[ ] = L"INSERT INTO [dbo].[TrackValues] ([Id], [OptimisticLockField], [Track], [Timestamp],[Flags],[Status],[Latitude],[Longitude],[Speed],[Course],[Heading]) VALUES(?,?,?,?,?,?,?,?,?,?,?)";
    static constexpr wchar_t UPDATE_[ ] = L"UPDATE [dbo].[TrackValues] SET [OptimisticLockField] = ?,[Track] = ?,[Timestamp] = ?,[Flags] = ?,[Status] = ?,[Latitude] = ?,[Longitude] = ?,[Speed] = ?,[Course] = ?,[Heading] = ? WHERE [Id] = ?";
    static constexpr wchar_t DELETE_[ ] = L"DELETE FROM [dbo].[TrackValues] WHERE [Id] = ?";

    TrackValueDataWriter( const Connection& connection )
        : connection_( connection )
    {
        CreateAndBindInsert( connection );
        CreateAndBindUpdate( connection );
        CreateAndBindDelete( connection );
    }

    void CreateAndBindInsert( const Connection & connection )
    {
        insertStatement_ = connection.CreateStatement( );
        insertStatement_.Prepare( INSERT_ );

        insertStatement_.BindParameter( 1, ParameterDirection::Input, &trackValue_.id_ );
        insertStatement_.BindParameter( 2, ParameterDirection::Input, &trackValue_.optimisticLockField_ );
        insertStatement_.BindParameter( 3, ParameterDirection::Input, &trackValue_.track_ );
        insertStatement_.BindParameter( 4, ParameterDirection::Input, reinterpret_cast< Int64* >( &trackValue_.timestamp_ ) );
        insertStatement_.BindParameter( 5, ParameterDirection::Input, &trackValue_.flags_ );
        insertStatement_.BindParameter( 6, ParameterDirection::Input, &trackValue_.status_ );
        insertStatement_.BindParameter( 7, ParameterDirection::Input, &trackValue_.latitude_ );
        insertStatement_.BindParameter( 8, ParameterDirection::Input, &trackValue_.longitude_ );
        insertStatement_.BindParameter( 9, ParameterDirection::Input, &trackValue_.speed_ );
        insertStatement_.BindParameter( 10, ParameterDirection::Input, &trackValue_.course_ );
        insertStatement_.BindParameter( 11, ParameterDirection::Input, &trackValue_.heading_ );

    }
    void CreateAndBindUpdate( const Connection & connection )
    {
        updateStatement_ = connection.CreateStatement( );
        updateStatement_.Prepare( UPDATE_ );

        updateStatement_.BindParameter( 1, ParameterDirection::Input, &trackValue_.optimisticLockField_ );
        updateStatement_.BindParameter( 2, ParameterDirection::Input, &trackValue_.track_ );
        updateStatement_.BindParameter( 3, ParameterDirection::Input, reinterpret_cast< Int64* >( &trackValue_.timestamp_ ) );
        updateStatement_.BindParameter( 4, ParameterDirection::Input, &trackValue_.flags_ );
        updateStatement_.BindParameter( 5, ParameterDirection::Input, &trackValue_.status_ );
        updateStatement_.BindParameter( 6, ParameterDirection::Input, &trackValue_.latitude_ );
        updateStatement_.BindParameter( 7, ParameterDirection::Input, &trackValue_.longitude_ );
        updateStatement_.BindParameter( 8, ParameterDirection::Input, &trackValue_.speed_ );
        updateStatement_.BindParameter( 9, ParameterDirection::Input, &trackValue_.course_ );
        updateStatement_.BindParameter( 10, ParameterDirection::Input, &trackValue_.heading_ );

        updateStatement_.BindParameter( 11, ParameterDirection::Input, &trackValue_.id_ );

    }
    void CreateAndBindDelete( const Connection & connection )
    {
        deleteStatement_ = connection.CreateStatement( );
        deleteStatement_.Prepare( DELETE_ );

        deleteStatement_.BindParameter( 1, ParameterDirection::Input, &trackValue_.id_ );
    }

    ODBC::Result Insert( bool commit = true )
    {
        auto result = insertStatement_.Execute( );
        if ( commit )
        {
            connection_.Commit( );
        }
        return result;
    }

    ODBC::Result Update( bool commit = true )
    {
        auto result = updateStatement_.Execute( );
        if ( commit )
        {
            connection_.Commit( );
        }
        return result;
    }

    ODBC::Result Delete( bool commit = true )
    {
        auto result = deleteStatement_.Execute( );
        if ( commit )
        {
            connection_.Commit( );
        }
        return result;
    }


    void Assign( const TrackValue& trackValue )
    {
        trackValue_ = trackValue;
    }

    constexpr const Core::Guid& Id( ) const noexcept
    {
        return trackValue_.id_;
    }

    void SetId( Core::Guid& id )
    {
        trackValue_.id_ = id;
    }

    constexpr Int64 OptimisticLockField( ) const noexcept
    {
        return trackValue_.optimisticLockField_;
    }
    void SetOptimisticLockField( Int64 optimisticLockField )
    {
        trackValue_.optimisticLockField_ = optimisticLockField;
    }

    constexpr const Core::Guid& Track( ) const noexcept
    {
        return trackValue_.track_;
    }
    void SetTrack( const Core::Guid& track )
    {
        trackValue_.track_ = track;
    }

    constexpr Core::DateTime Timestamp( ) const noexcept
    {
        return trackValue_.timestamp_;
    }
    void SetTimestamp( Core::DateTime timestamp )
    {
        trackValue_.timestamp_ = timestamp;
    }

    constexpr Int32 Flags( ) const noexcept
    {
        return trackValue_.flags_;
    }
    void SetFlags( Int32 flags )
    {
        trackValue_.flags_ = flags;
    }

    constexpr Int32 Status( ) const noexcept
    {
        return trackValue_.status_;
    }
    void SetStatus( Int32 status )
    {
        trackValue_.status_ = status;
    }

    constexpr double Latitude( ) const noexcept
    {
        return trackValue_.latitude_;
    }
    void SetLatitude( double latitude )
    {
        trackValue_.latitude_ = latitude;
    }

    constexpr double Longitude( ) const noexcept
    {
        return trackValue_.longitude_;
    }

    void SetLongitude( double longitude )
    {
        trackValue_.longitude_ = longitude;
    }

    constexpr double Speed( ) const noexcept
    {
        return trackValue_.speed_;
    }
    void SetSpeed( double speed )
    {
        trackValue_.speed_ = speed;
    }

    constexpr double Course( ) const noexcept
    {
        return trackValue_.course_;
    }
    void SetCourse( double course )
    {
        trackValue_.course_ = course;
    }

    constexpr double Heading( ) const noexcept
    {
        return trackValue_.heading_;
    }
    void SetHeading( double heading )
    {
        trackValue_.heading_ = heading;
    }


};



class DataContext
{
    const Connection& connection_;
    TrackDataWriter trackDataWriter_;
    TrackValueDataWriter trackValueDataWriter_;
    TimeSpan maxTrackAge_ = TimeSpan::FromSeconds(20);
public:
    DataContext( const Connection& connection )
        : connection_( connection ), trackDataWriter_( connection ), trackValueDataWriter_( connection )
    {

    }

    void Commit( )
    {
        connection_.Commit( );
    }

    static std::wstring SelectTrackSQL( )
    {
        return TrackDataReader::sql_;
    }

    static std::wstring SelectTrackSQL( const std::wstring& constraints )
    {
        return SelectTrackSQL( ) + L" t1 WHERE " + constraints;
    }

    static std::wstring SelectLastUpdatedTrackSQL( )
    {
        return TrackDataReader::lastUpdatedSql_;
    }

    static std::wstring SelectLastUpdatedTrackSQL( const std::wstring& constraints )
    {
        return SelectLastUpdatedTrackSQL( ) + L" t1 WHERE " + constraints;
    }



    static std::wstring SelectTrackValueSQL( )
    {
        return TrackValueDataReader::sql_;
    }

    static std::wstring SelectTrackValueSQL( const std::wstring& constraints )
    {
        return SelectTrackValueSQL( ) + L" tv1 WHERE " + constraints;
    }

    ODBC::Statement CreateStatement( ) const
    {
        return connection_.CreateStatement( );
    }



    bool TryGetTrackAt( Guid tracker, Int64 trackNumber, DateTime timestamp, Track& result )
    {
        auto sql = SelectTrackSQL( L"t1.[Tracker] = ? AND t1.[TrackNumber] = ? AND (t1.[Timestamp] = "\
            "(SELECT MAX(t2.[Timestamp]) "\
                "FROM [dbo].[Track] t2 "\
                "WHERE t2.[Tracker] = ? AND t2.[TrackNumber] = ? AND t2.[Timestamp] <= ? ))" );

        auto statement = connection_.CreateStatement( );
        statement.Prepare( sql.c_str( ) );
        Int64 timestampInTicks = timestamp.Ticks( );

        statement.BindParameter( 1, ParameterDirection::Input, &tracker );
        statement.BindParameter( 2, ParameterDirection::Input, &trackNumber );
        statement.BindParameter( 3, ParameterDirection::Input, &tracker );
        statement.BindParameter( 4, ParameterDirection::Input, &trackNumber );
        statement.BindParameter( 5, ParameterDirection::Input, &timestampInTicks );

        auto reader = statement.ExecuteReader<TrackDataReader>( );
        if ( reader->Read( ) )
        {
            reader->AssignTo( result );
            return true;
        }
        else
        {
            return false;
        }
    }

    bool TryGetTrackValueAt( Guid track, DateTime timestamp, TrackValue& result )
    {
        auto sql = SelectTrackValueSQL( L"tv1.[Track] = ? AND ( tv1.[Timestamp] = "\
            "(SELECT MAX(tv2.[Timestamp]) FROM [dbo].[TrackValues] tv2 WHERE tv2.[Track] = ? AND tv2.[Timestamp] <= ? ))" );

        auto statement = connection_.CreateStatement( );
        statement.Prepare( sql.c_str( ) );
        Int64 timestampInTicks = timestamp.Ticks( );

        statement.BindParameter( 1, ParameterDirection::Input, &track );
        statement.BindParameter( 2, ParameterDirection::Input, &track );
        statement.BindParameter( 3, ParameterDirection::Input, &timestampInTicks );

        auto reader = statement.ExecuteReader<TrackValueDataReader>( );
        if ( reader->Read( ) )
        {
            reader->AssignTo( result );
            return true;
        }
        else
        {
            return false;
        }

    }



    bool TryGetExistingTrack( Guid tracker, Int64 trackNumber, DateTime timestamp, Track& result )
    {
        if ( TryGetTrackAt( tracker, trackNumber, timestamp, result ) )
        {
            TimeSpan age = timestamp - result.timestamp_;
            if ( age > maxTrackAge_ )
            {
                TrackValue trackValue;
                if ( TryGetTrackValueAt( result.id_, timestamp, trackValue ) )
                {
                    age = timestamp - trackValue.timestamp_;
                    if ( age > maxTrackAge_ )
                    {
                        return false;
                    }
                    else
                    {
                        return true;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }


    bool FindTrack( Guid trackId, Track& result )
    {
        auto sql = SelectTrackSQL( L"[Id] = ?" );

        auto statement = connection_.CreateStatement( );
        statement.Prepare( sql.c_str( ) );

        statement.BindParameter( 1, ParameterDirection::Input, &trackId );

        auto reader = statement.ExecuteReader<TrackDataReader>( );

        if ( reader->Read( ) )
        {
            reader->AssignTo( result );
            return true;
        }
        else
        {
            return false;
        }
    }

    Track CreateTrack( bool commit, Guid tracker, Int64 trackNumber, const Core::DateTime& timestamp = Core::DateTime::Now() )
    {
        Track track;
        track.id_ = Guid::New( );
        track.tracker_ = tracker;
        track.trackNumber_ = trackNumber;
        track.timestamp_ = timestamp;
        trackDataWriter_.Assign( track );
        trackDataWriter_.Insert( commit );
        return track;
    }

    void CreateTrackValue( bool commit, Core::Guid track, const Core::DateTime& timestamp = Core::DateTime::Now( ), Int32 flags = 0, Int32 status = 0, double latitude = 0.0, double longitude = 0.0, double speed = 0.0, double course = 0.0, double heading = 0.0)
    {
        TrackValue trackValue;

        trackValue.id_ = Guid::New( );
        trackValue.track_ = track;
        trackValue.timestamp_ = timestamp;
        trackValue.flags_ = flags;
        trackValue.status_ = status;
        trackValue.latitude_ = latitude;
        trackValue.longitude_ = longitude;
        trackValue.speed_ = speed;
        trackValue.course_ = course;
        trackValue.heading_ = heading;

        trackValueDataWriter_.Assign( trackValue );
        trackValueDataWriter_.Insert( commit );
    }

    void ProcessTrackValue( bool commit, Guid tracker, Int64 trackNumber,
        const Core::DateTime& timestamp = Core::DateTime::Now( ), 
        Int32 flags = 0, 
        Int32 status = 0, 
        double latitude = 0.0, 
        double longitude = 0.0, 
        double speed = 0.0, 
        double course = 0.0, 
        double heading = 0.0 )
    {
        Track track;

        if ( TryGetExistingTrack( tracker, trackNumber, timestamp, track ) == false )
        {
            track = CreateTrack( commit, tracker, trackNumber, timestamp );
        }
        CreateTrackValue( commit, track.id_, timestamp, flags, status, latitude, longitude, speed, course, heading );

    }

    


};


class TrackValueTest
{
public:
#ifdef _DEBUG
    static constexpr size_t Iterations1 = 1'000;
    static constexpr size_t TargetsPerTracker2 = 2;
    static constexpr size_t TrackerCount2 = 2;
    static constexpr size_t Iterations2 = 1'000;
#else
    static constexpr size_t Iterations1 = 1'000'000;
    static constexpr size_t TargetsPerTracker2 = 15;
    static constexpr size_t TrackerCount2 = 26;
    static constexpr size_t Iterations2 = 30;
    
#endif
    static constexpr size_t TotalTargets2 = TrackerCount2 * TargetsPerTracker2 * 2;
    
    
    static constexpr size_t TrackValues2 = TotalTargets2 * Iterations2;

    DataContext& dataContext_;
    struct Tracker
    {
        Guid id_ = Guid::New();
        Int64 trackNumber_ = 0;
        std::array<Int64, TargetsPerTracker2> targets_;
        std::array<Int64, TargetsPerTracker2> aisTargets_;

        Tracker( )
        {
            ChangeTargets( );
        }

        void ChangeTargets( )
        {
            for ( auto& target : targets_ )
            {
                target = ++trackNumber_;
            }
            for ( auto& target : aisTargets_ )
            {
                target = ++trackNumber_;
            }
        }

    };

    std::array<Tracker, TrackerCount2> trackers_;

public:
    TrackValueTest( DataContext& dataContext )
        : dataContext_( dataContext )
    {

    }

    void ChangeTargets( )
    {
        for ( auto& tracker : trackers_ )
        {
            tracker.ChangeTargets( );
        }
    }


    
    void Run1( )
    {

        DateTime lastTimestamp( 2020, 1, 1 );
        auto firstTimestamp = lastTimestamp - TimeSpan::FromSeconds( Iterations1 );
        auto oneSecond = TimeSpan::FromSeconds( 1 ).Ticks( );
        auto day = TimeSpan::FromDays( 1 ).Ticks( );

        Core::Guid trackerId = Core::Guid::New( ); 
        Int64 trackNumber = 1;

        Track track;
        track = dataContext_.CreateTrack( true, trackerId, trackNumber, firstTimestamp );


        Stopwatch stopwatch;
        stopwatch.Start( );


        size_t iteration = 0;
        auto timestamp = firstTimestamp;
        while ( timestamp < lastTimestamp )
        {
            dataContext_.CreateTrackValue( false, track.id_, timestamp );
            iteration++;
            if ( ( timestamp.Ticks( ) % day ) == 0 )
            {
                dataContext_.Commit( );
            }

            timestamp = DateTime( timestamp.Ticks( ) + oneSecond );
        }
        dataContext_.Commit( );
        stopwatch.Stop( );
        int count = static_cast<int>( iteration );
        auto duration = stopwatch.TotalSeconds( );
        double perSecond = Iterations1 / duration;
        printf( "Simple insert: Inserted %d rows in %f seconds - %f rows per second.\n", count, duration, perSecond );
        flushall( );


        stopwatch.Reset( );
        stopwatch.Start( );
        int retrieved = 0;
        TrackValue trackValue;
        auto statement = dataContext_.CreateStatement( );
        auto sql = DataContext::SelectTrackValueSQL( );
        auto reader = statement.ExecuteReader<TrackValueDataReader>( sql.c_str( ) );
        while ( reader->Read( ) )
        {
            reader->AssignTo( trackValue );
            retrieved++;
        }
        stopwatch.Stop( );
        duration = stopwatch.TotalSeconds( );
        perSecond = Iterations1 / duration;
        printf( "Simple insert: Retrieved %d rows in %f seconds - %f rows per second.\n", retrieved, duration, perSecond );
        flushall( );

    }



    void Run2( )
    {

        DateTime lastTimestamp( 2020, 1, 1 );
        auto firstTimestamp = lastTimestamp - TimeSpan::FromSeconds( Iterations2 );
        auto oneSecond = TimeSpan::FromSeconds( 1 ).Ticks( );
        auto fifteenMinutes = TimeSpan::FromMinutes( 15 ).Ticks( );

        Stopwatch stopwatch;
        stopwatch.Start( );


        size_t iteration = 0;
        auto timestamp = firstTimestamp;
        while ( timestamp < lastTimestamp )
        {
            iteration++;
            if ( ( timestamp.Ticks( ) % fifteenMinutes ) == 0 )
            {
                ChangeTargets( );
            }
            Run2( timestamp );
            timestamp = DateTime( timestamp.Ticks( ) + oneSecond );
        }
        stopwatch.Stop( );
        int count = TrackValues2;
        auto duration = stopwatch.TotalSeconds( );
        double perSecond = TrackValues2 / duration;
        printf( "Simulating Radar and AIS: Inserted %d rows in %f seconds - %f rows per second.\n", count, duration, perSecond );
        flushall( );

    }

    void Run2( Core::DateTime timestamp )
    {

        size_t trackerNumber = 0;
        for ( auto& tracker : trackers_ )
        {
            size_t targetNumber = 0;
            auto trackerId = tracker.id_;
            for ( auto& target : tracker.targets_ )
            {
                Int64 trackNumber = target;
                dataContext_.ProcessTrackValue( false, trackerId, trackNumber, timestamp );
                targetNumber++;
            }
            dataContext_.Commit( );
            for ( auto& target : tracker.aisTargets_ )
            {
                Int64 trackNumber = target;
                dataContext_.ProcessTrackValue( true, trackerId, trackNumber, timestamp );
                targetNumber++;
            }

            trackerNumber++;
        }


    }


};



int main()
{
    auto applicationOptions = std::make_shared<ApplicationOptions>( );
    applicationOptions->Load( );
    Application application( applicationOptions );
    application.Start( );


    std::wstring DataSource = L"Ajaworks";
    std::wstring DatabaseName = L"AjaworksDev";

    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    connection.SetAutoCommitMode( false );

    auto deleteStatement = connection.CreateStatement( );
    deleteStatement.ExecDirect( L"delete from [dbo].[TrackValues]" );
    connection.Commit( );
    deleteStatement.ExecDirect( L"delete from [dbo].[Track]" );
    connection.Commit( );

    DataContext dataContext( connection );

    TrackValueTest test( dataContext );
    test.Run1( );
    test.Run2( );


    application.Stop( );
}

