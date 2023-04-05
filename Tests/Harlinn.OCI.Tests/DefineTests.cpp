#include <HOCI.h>
#include <HCCXml.h>
#include <HCCIO.h>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <OCITestFixture.h>

using namespace Harlinn::Common::Core;
using namespace Harlinn;
using namespace std::string_literals;

template<typename BT>
class TestDataReader : public OCI::DataReader
{
public:
    using Base = OCI::DataReader;
    using BindType = BT;
private:
    BindType* bind_;
public:
    TestDataReader( const OCI::Statement& statement )
        : Base( statement ), bind_(nullptr)
    {
    }

    virtual void InitializeDefines( ) override
    {
        if constexpr ( std::is_same_v<BT, OCI::CStringDefine> )
        {
            bind_ = Define<BindType>( 1, 128 );
        }
        else
        {
            bind_ = Define<BindType>( 1 );
        }
    }
    BindType* GetBind( ) const
    {
        return bind_;
    }
};


template< typename DefineT >
void TestCHAR5Define(const OCI::ServiceContext& serviceContext )
{
    constexpr wchar_t sql[] = L"SELECT NAME FROM HOCIDefineTestTable ORDER BY NAME";

    bool boolValues[] = { true,true };
    Int64 intValues[] = { 10, 20 };
    std::wstring stringValues[] = { L"10"s, L"20"s };

    auto statement = serviceContext.CreateStatement( sql );
    auto reader = statement.ExecuteReader< TestDataReader< DefineT> >( );
    size_t count = 0;
    while ( reader->Read( ) )
    {
        auto boolVal = reader->As<bool>( 0 );
        BOOST_CHECK( boolValues[count] == boolVal );
        auto sbyteVal = reader->As<SByte>( 0 );
        BOOST_CHECK( intValues[count] == static_cast<Int64>( sbyteVal ) );
        auto byteVal = reader->As<Byte>( 0 );
        BOOST_CHECK( intValues[count] == static_cast<Int64>( byteVal ) );
        auto int16Val = reader->As<Int16>( 0 );
        BOOST_CHECK( intValues[count] == static_cast<Int64>( int16Val ) );
        auto uint16Val = reader->As<UInt16>( 0 );
        BOOST_CHECK( intValues[count] == static_cast<Int64>( uint16Val ) );
        auto int32Val = reader->As<Int32>( 0 );
        BOOST_CHECK( intValues[count] == static_cast<Int64>( int32Val ) );
        auto uint32Val = reader->As<UInt32>( 0 );
        BOOST_CHECK( intValues[count] == static_cast<Int64>( uint32Val ) );
        auto int64Val = reader->As<Int64>( 0 );
        BOOST_CHECK( intValues[count] == static_cast<Int64>( int64Val ) );
        auto uint64Val = reader->As<UInt64>( 0 );
        BOOST_CHECK( intValues[count] == static_cast<Int64>( uint64Val ) );

        auto singleVal = reader->As<float>( 0 );
        BOOST_CHECK( intValues[count] == static_cast<Int64>( singleVal ) );
        auto doubleVal = reader->As<double>( 0 );
        BOOST_CHECK( intValues[count] == static_cast<Int64>( doubleVal ) );

        if constexpr ( std::is_same_v<DefineT, OCI::SingleDefine> || 
            std::is_same_v<DefineT, OCI::DoubleDefine> ||  
            std::is_same_v<DefineT, OCI::CStringDefine> )
        {

        }
        else
        {
            auto dateTimeVal = reader->As<DateTime>( 0 );
            BOOST_CHECK( intValues[count] == static_cast<Int64>( dateTimeVal.Ticks( ) ) );
            auto timeSpanVal = reader->As<TimeSpan>( 0 );
            BOOST_CHECK( intValues[count] == static_cast<Int64>( timeSpanVal.Ticks( ) ) );
        }

        if constexpr ( std::is_same_v<DefineT, OCI::SingleDefine> || std::is_same_v<DefineT, OCI::DoubleDefine>  )
        {

        }
        else if constexpr ( std::is_same_v<DefineT, OCI::CStringDefine> )
        {
            std::wstring stringValues[] = { L"10   "s, L"20   "s };
            auto strVal = reader->As<std::wstring>( 0 );
            BOOST_CHECK( stringValues[count] == strVal );
        }
        else
        {
            auto strVal = reader->As<std::wstring>( 0 );
            BOOST_CHECK( stringValues[count] == strVal );
        }

        


        count++;
    }
    BOOST_CHECK( count == 2 );
}



BOOST_FIXTURE_TEST_SUITE( DefineTests, LocalFixture )

// --run_test=DefineTests/CHAR5DefineTest1
BOOST_AUTO_TEST_CASE( CHAR5DefineTest1 )
{
    OCI::EnvironmentOptions options;
    OCI::Environment environment( options );

    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );

    serviceContext.SessionBegin( );

    auto defineTestTableExists = serviceContext.Exists( L"HOCIDefineTestTable", OCI::ParameterType::Table );
    if ( defineTestTableExists )
    {
        serviceContext.ExecuteNonQuery( L"DROP TABLE HOCIDefineTestTable" );
    }
    serviceContext.ExecuteNonQuery( L"CREATE TABLE HOCIDefineTestTable(NAME CHAR(5) NOT NULL PRIMARY KEY )" );
    serviceContext.ExecuteNonQuery( L"INSERT INTO HOCIDefineTestTable(NAME) VALUES(:1)", L"10"s );
    serviceContext.ExecuteNonQuery( L"INSERT INTO HOCIDefineTestTable(NAME) VALUES(:1)", L"20"s );

    TestCHAR5Define<OCI::BooleanDefine>( serviceContext );
    TestCHAR5Define<OCI::SByteDefine>( serviceContext );
    TestCHAR5Define<OCI::ByteDefine>( serviceContext );
    TestCHAR5Define<OCI::Int16Define>( serviceContext );
    TestCHAR5Define<OCI::UInt16Define>( serviceContext );
    TestCHAR5Define<OCI::Int32Define>( serviceContext );
    TestCHAR5Define<OCI::UInt32Define>( serviceContext );
    TestCHAR5Define<OCI::Int64Define>( serviceContext );
    TestCHAR5Define<OCI::UInt64Define>( serviceContext );
    TestCHAR5Define<OCI::SingleDefine>( serviceContext );
    TestCHAR5Define<OCI::DoubleDefine>( serviceContext );
    TestCHAR5Define<OCI::CStringDefine>( serviceContext );
    

    serviceContext.SessionEnd( );
}

// --run_test=DefineTests/NCHAR5DefineTest1
BOOST_AUTO_TEST_CASE( NCHAR5DefineTest1 )
{
    OCI::EnvironmentOptions options;
    OCI::Environment environment( options );

    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );

    serviceContext.SessionBegin( );

    auto defineTestTableExists = serviceContext.Exists( L"HOCIDefineTestTable", OCI::ParameterType::Table );
    if ( defineTestTableExists )
    {
        serviceContext.ExecuteNonQuery( L"DROP TABLE HOCIDefineTestTable" );
    }
    serviceContext.ExecuteNonQuery( L"CREATE TABLE HOCIDefineTestTable(NAME NCHAR(5) NOT NULL PRIMARY KEY )" );
    serviceContext.ExecuteNonQuery( L"INSERT INTO HOCIDefineTestTable(NAME) VALUES(:1)", L"10"s );
    serviceContext.ExecuteNonQuery( L"INSERT INTO HOCIDefineTestTable(NAME) VALUES(:1)", L"20"s );

    TestCHAR5Define<OCI::BooleanDefine>( serviceContext );
    TestCHAR5Define<OCI::SByteDefine>( serviceContext );
    TestCHAR5Define<OCI::ByteDefine>( serviceContext );
    TestCHAR5Define<OCI::Int16Define>( serviceContext );
    TestCHAR5Define<OCI::UInt16Define>( serviceContext );
    TestCHAR5Define<OCI::Int32Define>( serviceContext );
    TestCHAR5Define<OCI::UInt32Define>( serviceContext );
    TestCHAR5Define<OCI::Int64Define>( serviceContext );
    TestCHAR5Define<OCI::UInt64Define>( serviceContext );
    TestCHAR5Define<OCI::SingleDefine>( serviceContext );
    TestCHAR5Define<OCI::DoubleDefine>( serviceContext );
    TestCHAR5Define<OCI::CStringDefine>( serviceContext );


    serviceContext.SessionEnd( );
}



BOOST_AUTO_TEST_SUITE_END( )