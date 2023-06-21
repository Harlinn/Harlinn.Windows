#include <HOCI.h>
#include <HCCXml.h>
#include <HCCIO.h>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <OCITestFixture.h>
#include <TestEngine.h>
#include <oci.h>

using namespace Harlinn::Common;
using namespace Harlinn::OCI;

BOOST_FIXTURE_TEST_SUITE( StatementTests, LocalFixture )

// --run_test=StatementTests/ExecuteTest1
BOOST_AUTO_TEST_CASE( ExecuteTest1 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );

    serviceContext.SessionBegin( );

    WideString sql =
        L"BEGIN"\
        L" :result := SYSDATE();" \
        L"END;";

    auto statement = serviceContext.CreateStatement( sql );

    auto result = statement.Bind<DateBind>( 1 );

    statement.Execute( 1 );

    auto dateTime = result->AsDateTime( );
    BOOST_CHECK( dateTime.Ticks( ) > 0 );

    serviceContext.SessionEnd( );
}

// --run_test=StatementTests/ExecuteTest1a
BOOST_AUTO_TEST_CASE( ExecuteTest1a )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );

    auto server = environment.CreateServer( );
    server.Attach( Alias );

    auto serviceContext = environment.CreateServiceContext( );
    serviceContext.SetServer( server );
    auto session = environment.CreateSession( );
    session.SetUserName( Username );
    session.SetPassword( Password );

    serviceContext.SetSession( std::move( session ) );
     

    serviceContext.SessionBegin( );

    WideString sql =
        L"BEGIN"\
        L" :result := SYSDATE();" \
        L"END;";

    auto statement = serviceContext.CreateStatement( sql );

    auto result = statement.Bind<DateBind>( 1 );

    statement.Execute( 1 );

    auto dateTime = result->AsDateTime( );
    BOOST_CHECK( dateTime.Ticks( ) > 0 );

    serviceContext.SessionEnd( );
}



// --run_test=StatementTests/ExecuteTest2
BOOST_AUTO_TEST_CASE( ExecuteTest2 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );

    serviceContext.SessionBegin( );

    WideString sql =
        L"BEGIN"\
        L" :result := SYSTIMESTAMP();" \
        L"END;";
    
    auto statement = serviceContext.CreateStatement( sql );

    auto result = statement.Bind<DateTime>( 1 );

    statement.Execute( 1 );

    auto dateTime = result->As<DateTime>( );
    BOOST_CHECK( dateTime.Ticks( ) > 0 );
    
    serviceContext.SessionEnd( );
}

// --run_test=StatementTests/ExecuteTest3
BOOST_AUTO_TEST_CASE( ExecuteTest3 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );

    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );
    serviceContext.SessionBegin( );

    WideString sql =
        L"BEGIN"\
        L" :result := 1;" \
        L"END;";

    auto statement = serviceContext.CreateStatement( sql );
    auto result = statement.Bind<bool>( 1 );

    statement.Execute( 1 );

    auto value = result->As<bool>( );
    BOOST_CHECK( value );

    serviceContext.SessionEnd( );
}

// --run_test=StatementTests/ExecuteTest4
BOOST_AUTO_TEST_CASE( ExecuteTest4 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );

    serviceContext.SessionBegin( );

    WideString sql =
        L"BEGIN"\
        L" :result := 1;" \
        L"END;";

    auto statement = serviceContext.CreateStatement( sql );
    auto result = statement.Bind<SByte>( 1 );

    statement.Execute( 1 );

    auto value = result->As<SByte>( );
    BOOST_CHECK( value == 1 );

    serviceContext.SessionEnd( );
}


// --run_test=StatementTests/ExecuteTest5
BOOST_AUTO_TEST_CASE( ExecuteTest5 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );

    serviceContext.SessionBegin( );

    WideString sql =
        L"BEGIN"\
        L" :result := 1;" \
        L"END;";

    auto statement = serviceContext.CreateStatement( sql );
    auto result = statement.Bind<Byte>( 1 );

    statement.Execute( 1 );

    auto value = result->As<Byte>( );
    BOOST_CHECK( value == 1 );

    serviceContext.SessionEnd( );
}

// --run_test=StatementTests/ExecuteTest6
BOOST_AUTO_TEST_CASE( ExecuteTest6 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );

    serviceContext.SessionBegin( );

    WideString sql =
        L"BEGIN"\
        L" :result := 1;" \
        L"END;";

    auto statement = serviceContext.CreateStatement( sql );
    auto result = statement.Bind<Int16>( 1 );

    statement.Execute( 1 );

    auto value = result->As<Int16>( );
    BOOST_CHECK( value == 1 );

    serviceContext.SessionEnd( );
}

// --run_test=StatementTests/ExecuteTest7
BOOST_AUTO_TEST_CASE( ExecuteTest7 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );

    serviceContext.SessionBegin( );

    WideString sql =
        L"BEGIN"\
        L" :result := 1;" \
        L"END;";

    auto statement = serviceContext.CreateStatement( sql );
    auto result = statement.Bind<UInt16>( 1 );

    statement.Execute( 1 );

    auto value = result->As<UInt16>( );
    BOOST_CHECK( value == 1 );

    serviceContext.SessionEnd( );
}

// --run_test=StatementTests/ExecuteTest8
BOOST_AUTO_TEST_CASE( ExecuteTest8 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );

    serviceContext.SessionBegin( );

    WideString sql =
        L"BEGIN"\
        L" :result := 1;" \
        L"END;";

    auto statement = serviceContext.CreateStatement( sql );
    auto result = statement.Bind<Int32>( 1 );

    statement.Execute( 1 );

    auto value = result->As<Int32>( );
    BOOST_CHECK( value == 1 );

    serviceContext.SessionEnd( );
}

// --run_test=StatementTests/ExecuteTest9
BOOST_AUTO_TEST_CASE( ExecuteTest9 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );

    serviceContext.SessionBegin( );

    WideString sql =
        L"BEGIN"\
        L" :result := 1;" \
        L"END;";

    auto statement = serviceContext.CreateStatement( sql );
    auto result = statement.Bind<UInt32>( 1 );

    statement.Execute( 1 );

    auto value = result->As<UInt32>( );
    BOOST_CHECK( value == 1 );

    serviceContext.SessionEnd( );
}

// --run_test=StatementTests/ExecuteTest10
BOOST_AUTO_TEST_CASE( ExecuteTest10 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );

    serviceContext.SessionBegin( );

    WideString sql =
        L"BEGIN"\
        L" :result := 1;" \
        L"END;";

    auto statement = serviceContext.CreateStatement( sql );
    auto result = statement.Bind<Int64>( 1 );

    statement.Execute( 1 );

    auto value = result->As<Int64>( );
    BOOST_CHECK( value == 1 );

    serviceContext.SessionEnd( );
}

// --run_test=StatementTests/ExecuteTest11
BOOST_AUTO_TEST_CASE( ExecuteTest11 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );

    serviceContext.SessionBegin( );

    WideString sql =
        L"BEGIN"\
        L" :result := 1;" \
        L"END;";

    auto statement = serviceContext.CreateStatement( sql );
    auto result = statement.Bind<UInt64>( 1 );

    statement.Execute( 1 );

    auto value = result->As<UInt64>( );
    BOOST_CHECK( value == 1 );

    serviceContext.SessionEnd( );
}

// --run_test=StatementTests/ExecuteTest12
BOOST_AUTO_TEST_CASE( ExecuteTest12 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );

    serviceContext.SessionBegin( );

    WideString sql =
        L"BEGIN"\
        L" :result := 1;" \
        L"END;";

    auto statement = serviceContext.CreateStatement( sql );
    auto result = statement.Bind<float>( 1 );

    statement.Execute( 1 );

    auto value = result->As<float>( );
    BOOST_CHECK( value == 1 );

    serviceContext.SessionEnd( );
}

// --run_test=StatementTests/ExecuteTest13
BOOST_AUTO_TEST_CASE( ExecuteTest13 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );

    serviceContext.SessionBegin( );

    WideString sql =
        L"BEGIN"\
        L" :result := 1;" \
        L"END;";

    auto statement = serviceContext.CreateStatement( sql );
    auto result = statement.Bind<Double>( 1 );

    statement.Execute( 1 );

    auto value = result->As<Double>( );
    BOOST_CHECK( value == 1 );

    serviceContext.SessionEnd( );
}

// --run_test=StatementTests/ExecuteTest14
BOOST_AUTO_TEST_CASE( ExecuteTest14 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );

    serviceContext.SessionBegin( );

    WideString sql =
        L"BEGIN"\
        L" :result := 1;" \
        L"END;";

    auto statement = serviceContext.CreateStatement( sql );
    auto result = statement.Bind<WideString>( 1 );
    result->Reserve( 5 );

    statement.Execute( 1 );

    auto value = result->As<WideString>( );
    BOOST_CHECK( value == L"1" );

    serviceContext.SessionEnd( );
}

// --run_test=StatementTests/ExecuteTest15
BOOST_AUTO_TEST_CASE( ExecuteTest15 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );

    serviceContext.SessionBegin( );

    WideString sql =
        L"BEGIN"\
        L" :result := 1;" \
        L"END;";

    auto statement = serviceContext.CreateStatement( sql );
    auto result = statement.Bind<StringBind>( 1 );

    statement.Execute( 1 );

    auto value = result->AsString( );
    BOOST_CHECK( value == L"1" );

    serviceContext.SessionEnd( );
}

// --run_test=StatementTests/ExecuteTest16
BOOST_AUTO_TEST_CASE( ExecuteTest16 )
{
    Guid guid( L"{5506E2D6-22FE-4945-8B5B-D136A080649C}" );
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );

    serviceContext.SessionBegin( );

    WideString sql =
        L"BEGIN"\
        L" :result := :value;" \
        L"END;";

    auto statement = serviceContext.CreateStatement( sql );
    auto result = statement.Bind<Guid>( 1 );
    auto input = statement.Bind<Guid>( 2 );
    input->Assign( guid );

    statement.Execute( 1 );

    auto value = result->As<Guid>( );
    BOOST_CHECK( value == guid );

    serviceContext.SessionEnd( );
}


// --run_test=StatementTests/ExecuteReaderTest1a
BOOST_AUTO_TEST_CASE( ExecuteReaderTest1a )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );

    serviceContext.SessionBegin( );

    WideString sql =
        L"SELECT * FROM ALL_USERS WHERE USERNAME<>:1";
    WideString myName( L"ESPEN" );
    auto statement = serviceContext.CreateStatement( sql, myName );
    auto reader = statement.ExecuteReader<DataReader>( );
    while ( reader->Read( ) )
    {
        auto userName = reader->As<WideString>( 0 );
        auto userId = reader->As<Int64>( 1 );
        auto created = reader->As<DateTime>( 2 );
    }
    serviceContext.SessionEnd( );
}


// --run_test=StatementTests/ExecuteReaderTest1
BOOST_AUTO_TEST_CASE( ExecuteReaderTest1 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    BOOST_CHECK( environment.Handle( ) != nullptr );

    auto server = environment.CreateServer( );
    BOOST_CHECK( server.Handle( ) != nullptr );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );
    BOOST_CHECK( serviceContext.Handle( ) != nullptr );

    serviceContext.SessionBegin( );

    WideString sql =
        L"SELECT * FROM ALL_USERS";

    auto statement = serviceContext.CreateStatement( sql );

    auto reader = statement.ExecuteReader<DataReader>();
    size_t count = 0;
    while ( reader->Read( ) )
    {
        count++;
    }
    BOOST_CHECK( count > 0 );

    serviceContext.SessionEnd( );
}


// --run_test=StatementTests/ExecuteArrayReaderTest1
BOOST_AUTO_TEST_CASE( ExecuteArrayReaderTest1 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    BOOST_CHECK( environment.Handle( ) != nullptr );

    auto server = environment.CreateServer( );
    BOOST_CHECK( server.Handle( ) != nullptr );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );
    BOOST_CHECK( serviceContext.Handle( ) != nullptr );

    serviceContext.SessionBegin( );

    WideString sql = L"SELECT * FROM ALL_USERS";

    auto statement = serviceContext.CreateStatement( sql );

    auto reader = statement.ExecuteReader<ArrayDataReader>( );
    size_t count = 0;
    while ( reader->Read( ) )
    {
        count++;
    }
    BOOST_CHECK( count > 0 );

    serviceContext.SessionEnd( );
}

class AllUsersReader : public DataReader
{
public:
    using Base = DataReader;
    constexpr static UInt32 USERNAME = 0;
    constexpr static UInt32 USER_ID = 1;
    constexpr static UInt32 CREATED = 2;
    constexpr static UInt32 COMMON = 3;
    constexpr static UInt32 ORACLE_MAINTAINED = 4;
    constexpr static UInt32 INHERITED = 5;
    constexpr static UInt32 DEFAULT_COLLATION = 6;
    constexpr static UInt32 IMPLICIT = 7;
    constexpr static UInt32 ALL_SHARD = 8;

    constexpr static wchar_t SQL[] = L"SELECT USERNAME, "
        L"USER_ID, CREATED, COMMON, ORACLE_MAINTAINED, "
        L"INHERITED, DEFAULT_COLLATION, IMPLICIT, ALL_SHARD "
        L"FROM ALL_USERS";

private:
    CStringDefine* userName_ = nullptr;
    Int64Define* userId_ = nullptr;
    DateDefine* created_ = nullptr;
    CStringDefine* common_ = nullptr;
    CStringDefine* oracleMaintained_ = nullptr;
    CStringDefine* inherited_ = nullptr;
    CStringDefine* defaultCollation_ = nullptr;
    CStringDefine* implicit_ = nullptr;
    CStringDefine* allShard_ = nullptr;
public:
    AllUsersReader( const OCI::Statement& statement )
        : Base( statement )
    { }


    virtual void InitializeDefines( ) override
    {
        userName_ = Define<CStringDefine>( USERNAME + 1, 128 );
        userId_ = Define<Int64Define>( USER_ID + 1 );
        created_ = Define<DateDefine>( CREATED + 1 );
        common_ = Define<CStringDefine>( COMMON + 1, 3 );
        oracleMaintained_ = Define<CStringDefine>( ORACLE_MAINTAINED + 1, 1 );
        inherited_ = Define<CStringDefine>( INHERITED + 1, 3 );
        defaultCollation_ = Define<CStringDefine>( DEFAULT_COLLATION + 1, 100 );
        implicit_ = Define<CStringDefine>( IMPLICIT + 1, 3 );
        allShard_ = Define<CStringDefine>( ALL_SHARD + 1, 3 );
    }

    WideString UserName( ) const
    {
        return userName_->AsString( );
    }
    Int64 UserId( ) const
    {
        return userId_->AsInt64( );
    }
    DateTime Created( ) const
    {
        return created_->AsDateTime( );
    }

    bool Common( ) const
    {
        return common_->AsString( ) == L"YES";
    }
    bool OracleMaintained( ) const
    {
        return oracleMaintained_->AsString( ) == L"Y";
    }
    bool Inherited( ) const
    {
        return inherited_->AsString( ) == L"YES";
    }
    WideString DefaultCollation( ) const
    {
        return defaultCollation_->AsString( );
    }
    bool Implicit( ) const
    {
        return implicit_->AsString( ) == L"YES";
    }
    bool AllShard( ) const
    {
        return allShard_->AsString( ) == L"YES";
    }
};

// --run_test=StatementTests/ExecuteReaderTest3
BOOST_AUTO_TEST_CASE( ExecuteReaderTest3 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );
    serviceContext.SessionBegin( );

    auto statement = serviceContext.CreateStatement( AllUsersReader::SQL );

    auto reader = statement.ExecuteReader<AllUsersReader>( );
    size_t count = 0;
    while ( reader->Read( ) )
    {
        auto userName = reader->UserName( );
        auto userId = reader->UserId( );
        auto created = reader->Created( );
        count++;
    }
    BOOST_CHECK( count > 0 );

    serviceContext.SessionEnd( );
}


class AllUsersArrayReader : public ArrayDataReader
{
public:
    using Base = ArrayDataReader;
    constexpr static UInt32 USERNAME = 0;
    constexpr static UInt32 USER_ID = 1;
    constexpr static UInt32 CREATED = 2;
    constexpr static UInt32 COMMON = 3;
    constexpr static UInt32 ORACLE_MAINTAINED = 4;
    constexpr static UInt32 INHERITED = 5;
    constexpr static UInt32 DEFAULT_COLLATION = 6;
    constexpr static UInt32 IMPLICIT = 7;
    constexpr static UInt32 ALL_SHARD = 8;

    constexpr static wchar_t SQL[] = L"SELECT USERNAME, USER_ID, CREATED, COMMON, ORACLE_MAINTAINED, INHERITED, DEFAULT_COLLATION, IMPLICIT, ALL_SHARD FROM ALL_USERS";


public:
    AllUsersArrayReader( const OCI::Statement& statement, size_t size )
        : Base( statement, size )
    {
    }


    virtual void InitializeDefines( ) override
    {
        Define<WideString>( USERNAME + 1, 128 );
        Define<Int64>( USER_ID + 1 );
        Define<DateTime>( CREATED + 1 );
        Define<WideString>( COMMON + 1, 3 );
        Define<WideString>( ORACLE_MAINTAINED + 1, 1 );
        Define<WideString>( INHERITED + 1, 3 );
        Define<WideString>( DEFAULT_COLLATION + 1, 100 );
        Define<WideString>( IMPLICIT + 1, 3 );
        Define<WideString>( ALL_SHARD + 1, 3 );
    }

    WideString UserName( ) const
    {
        return GetString( USERNAME );
    }
    Int64 UserId( ) const
    {
        return GetInt64( USER_ID );
    }
    DateTime Created( ) const
    {
        return GetDateTime( CREATED );
    }

    bool Common( ) const
    {
        return GetString( USERNAME ) == L"YES";
    }
    bool OracleMaintained( ) const
    {
        return GetString( ORACLE_MAINTAINED ) == L"Y";
    }
    bool Inherited( ) const
    {
        return GetString( INHERITED ) == L"YES";
    }
    WideString DefaultCollation( ) const
    {
        return GetString( DEFAULT_COLLATION );
    }
    bool Implicit( ) const
    {
        return GetString( IMPLICIT ) == L"YES";
    }
    bool AllShard( ) const
    {
        return GetString( ALL_SHARD ) == L"YES";
    }
};

// --run_test=StatementTests/ExecuteReaderTest4
BOOST_AUTO_TEST_CASE( ExecuteReaderTest4 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );
    serviceContext.SessionBegin( );

    auto statement = serviceContext.CreateStatement( AllUsersArrayReader::SQL );

    auto reader = statement.ExecuteReader<AllUsersArrayReader>( );
    size_t count = 0;
    while ( reader->Read( ) )
    {
        auto userName = reader->UserName( );
        count++;
    }
    BOOST_CHECK( count > 0 );

    serviceContext.SessionEnd( );
}


// --run_test=StatementTests/ExecuteReaderTest5
BOOST_AUTO_TEST_CASE( ExecuteReaderTest5 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );
    serviceContext.SessionBegin( );

    auto statement = serviceContext.CreateStatement( L"SELECT * FROM OwnedObjectType" );

    auto reader = statement.ExecuteReader<DataReader>( );
    size_t count = 0;
    while ( reader->Read( ) )
    {
        auto id = reader->As<Guid>( 0 );
        auto name = reader->As<WideString>( 1 );
        auto optimisticLock = reader->As<Int64>( 2 );
        auto create = reader->As<DateTime>( 3 );
        auto deleted = reader->As<std::optional< DateTime > >( 4 );
        auto description = reader->As< std::optional< WideString >>( 5 );
        count++;
    }
    BOOST_CHECK( count > 0 );

    serviceContext.SessionEnd( );
}



// --run_test=StatementTests/ExecuteScalarTest1
BOOST_AUTO_TEST_CASE( ExecuteScalarTest1 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );
    serviceContext.SessionBegin( );

    WideString sql( L"SELECT 1 FROM DUAL" );

    auto result = serviceContext.ExecuteScalar<bool>( sql );
    BOOST_CHECK( result.has_value( ) );
    BOOST_CHECK( result.value( ) );


    serviceContext.SessionEnd( );
}

// --run_test=StatementTests/ExecuteScalarTest2
BOOST_AUTO_TEST_CASE( ExecuteScalarTest2 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );
    serviceContext.SessionBegin( );

    WideString sql( L"SELECT 1 FROM DUAL" );

    auto result = serviceContext.ExecuteScalar<SByte>( sql );
    BOOST_CHECK( result.has_value( ) );
    BOOST_CHECK( result.value( ) );


    serviceContext.SessionEnd( );
}

// --run_test=StatementTests/ExecuteScalarTest3
BOOST_AUTO_TEST_CASE( ExecuteScalarTest3 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );
    serviceContext.SessionBegin( );

    WideString sql( L"SELECT 1 FROM DUAL" );

    auto result = serviceContext.ExecuteScalar<Byte>( sql );
    BOOST_CHECK( result.has_value( ) );
    BOOST_CHECK( result.value( ) );


    serviceContext.SessionEnd( );
}

// --run_test=StatementTests/ExecuteScalarTest4
BOOST_AUTO_TEST_CASE( ExecuteScalarTest4 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );
    serviceContext.SessionBegin( );

    WideString sql( L"SELECT 1 FROM DUAL" );

    auto result = serviceContext.ExecuteScalar<Int16>( sql );
    BOOST_CHECK( result.has_value( ) );
    BOOST_CHECK( result.value( ) );


    serviceContext.SessionEnd( );
}

// --run_test=StatementTests/ExecuteScalarTest5
BOOST_AUTO_TEST_CASE( ExecuteScalarTest5 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );
    serviceContext.SessionBegin( );

    WideString sql( L"SELECT 1 FROM DUAL" );

    auto result = serviceContext.ExecuteScalar<UInt16>( sql );
    BOOST_CHECK( result.has_value( ) );
    BOOST_CHECK( result.value( ) );


    serviceContext.SessionEnd( );
}

// --run_test=StatementTests/ExecuteScalarTest6
BOOST_AUTO_TEST_CASE( ExecuteScalarTest6 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );
    serviceContext.SessionBegin( );

    WideString sql( L"SELECT 1 FROM DUAL" );

    auto result = serviceContext.ExecuteScalar<Int32>( sql );
    BOOST_CHECK( result.has_value( ) );
    BOOST_CHECK( result.value( ) );


    serviceContext.SessionEnd( );
}

// --run_test=StatementTests/ExecuteScalarTest7
BOOST_AUTO_TEST_CASE( ExecuteScalarTest7 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );
    serviceContext.SessionBegin( );

    WideString sql( L"SELECT 1 FROM DUAL" );

    auto result = serviceContext.ExecuteScalar<UInt32>( sql );
    BOOST_CHECK( result.has_value( ) );
    BOOST_CHECK( result.value( ) );


    serviceContext.SessionEnd( );
}

// --run_test=StatementTests/ExecuteScalarTest8
BOOST_AUTO_TEST_CASE( ExecuteScalarTest8 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );
    serviceContext.SessionBegin( );

    WideString sql( L"SELECT 1 FROM DUAL" );

    auto result = serviceContext.ExecuteScalar<Int64>( sql );
    BOOST_CHECK( result.has_value( ) );
    BOOST_CHECK( result.value( ) );


    serviceContext.SessionEnd( );
}

// --run_test=StatementTests/ExecuteScalarTest9
BOOST_AUTO_TEST_CASE( ExecuteScalarTest9 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );
    serviceContext.SessionBegin( );

    WideString sql( L"SELECT 1 FROM DUAL" );

    auto result = serviceContext.ExecuteScalar<UInt64>( sql );
    BOOST_CHECK( result.has_value( ) );
    BOOST_CHECK( result.value( ) );


    serviceContext.SessionEnd( );
}

// --run_test=StatementTests/ExecuteScalarTest10
BOOST_AUTO_TEST_CASE( ExecuteScalarTest10 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );
    serviceContext.SessionBegin( );

    WideString sql( L"SELECT 1 FROM DUAL" );

    auto result = serviceContext.ExecuteScalar<float>( sql );
    BOOST_CHECK( result.has_value( ) );
    BOOST_CHECK( result.value( ) );


    serviceContext.SessionEnd( );
}

// --run_test=StatementTests/ExecuteScalarTest11
BOOST_AUTO_TEST_CASE( ExecuteScalarTest11 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );
    serviceContext.SessionBegin( );

    WideString sql( L"SELECT 1 FROM DUAL" );

    auto result = serviceContext.ExecuteScalar<Double>( sql );
    BOOST_CHECK( result.has_value( ) );
    BOOST_CHECK( result.value( ) );


    serviceContext.SessionEnd( );
}

// --run_test=StatementTests/ExecuteScalarTest12
BOOST_AUTO_TEST_CASE( ExecuteScalarTest12 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );
    serviceContext.SessionBegin( );

    WideString sql( L"SELECT SYSTIMESTAMP FROM DUAL" );

    auto result = serviceContext.ExecuteScalar<DateTime>( sql );
    BOOST_CHECK( result.has_value( ) );
    BOOST_CHECK( result.value( ) );
    auto& value = result.value( );
    auto valueString = value.ToString( );
    BOOST_CHECK( valueString.length() > 0 );
    


    serviceContext.SessionEnd( );
}


// --run_test=StatementTests/EngineTest1
BOOST_AUTO_TEST_CASE( EngineTest1 )
{
    using namespace OCITest;
    EnvironmentOptions options;
    Engine engine( options );
    auto session = engine.Connect( Username, Password, Alias );
    session.OwnedObjectTypeDelete( );
    session.Commit( );

    OwnedObjectType ownedObjectType( L"Type1", L"Description" );
    session.Insert( ownedObjectType );
    session.Commit( );
    
}







BOOST_AUTO_TEST_SUITE_END( )