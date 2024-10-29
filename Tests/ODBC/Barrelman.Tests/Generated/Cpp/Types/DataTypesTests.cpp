#include <HCCIO.h>
#include "Types/DataTypes.h"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace Harlinn::Common;
using namespace Harlinn::ODBC;
using namespace Harlinn;
using namespace Barrelman;
using namespace Barrelman::Types;

class DataTypesLocalFixture
{
public:
    DataTypesLocalFixture( ) = default;
    ~DataTypesLocalFixture( ) = default;
};

BOOST_FIXTURE_TEST_SUITE( DataTypesTests, DataTypesLocalFixture )

// --run_test=DataTypesTests/AircraftTypeObjectSerializationTest
BOOST_AUTO_TEST_CASE( AircraftTypeObjectSerializationTest )
{
    auto aircraftTypeObject1 = std::make_shared<AircraftTypeObject>( );
    aircraftTypeObject1->SetId( Guid( L"{E0A93EC5-8153-304B-0CD2-81CA07957CA3}" ) );
    aircraftTypeObject1->SetRowVersion( 3480017334325296837LL );
    aircraftTypeObject1->SetName( L"Name" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aircraftTypeObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aircraftTypeObject2 = std::reinterpret_pointer_cast<AircraftTypeObject>( ReadDataFrom( source ) );
    bool equal = aircraftTypeObject2->IsEqualTo( *aircraftTypeObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisDeviceCommandObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisDeviceCommandObjectSerializationTest )
{
    auto aisDeviceCommandObject1 = std::make_shared<AisDeviceCommandObject>( );
    aisDeviceCommandObject1->SetId( Guid( L"{0B1A380B-1F86-8561-A186-F861D0581CD0}" ) );
    aisDeviceCommandObject1->SetRowVersion( -8835746333351856117LL );
    aisDeviceCommandObject1->SetAisDevice( Guid( L"{0B1A380B-1F86-8561-A186-F861D0581CD0}" ) );
    aisDeviceCommandObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisDeviceCommandObject1->SetDeviceCommandSourceType( DeviceCommandSourceType::Source );
    aisDeviceCommandObject1->SetDeviceCommandSourceId( Guid( L"{0B1A380B-1F86-8561-A186-F861D0581CD0}" ) );
    aisDeviceCommandObject1->SetReply( Guid( L"{0B1A380B-1F86-8561-A186-F861D0581CD0}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisDeviceCommandObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisDeviceCommandObject2 = std::reinterpret_pointer_cast<AisDeviceCommandObject>( ReadDataFrom( source ) );
    bool equal = aisDeviceCommandObject2->IsEqualTo( *aisDeviceCommandObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisDeviceCommandReplyObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisDeviceCommandReplyObjectSerializationTest )
{
    auto aisDeviceCommandReplyObject1 = std::make_shared<AisDeviceCommandReplyObject>( );
    aisDeviceCommandReplyObject1->SetId( Guid( L"{B5D95B2D-BBE8-9869-1996-DD17AD9BDAB4}" ) );
    aisDeviceCommandReplyObject1->SetRowVersion( -7464228299232158931LL );
    aisDeviceCommandReplyObject1->SetAisDevice( Guid( L"{B5D95B2D-BBE8-9869-1996-DD17AD9BDAB4}" ) );
    aisDeviceCommandReplyObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisDeviceCommandReplyObject1->SetCommand( Guid( L"{B5D95B2D-BBE8-9869-1996-DD17AD9BDAB4}" ) );
    aisDeviceCommandReplyObject1->SetStatus( DeviceCommandReplyStatus::Ok );
    aisDeviceCommandReplyObject1->SetMessage( L"Message" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisDeviceCommandReplyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisDeviceCommandReplyObject2 = std::reinterpret_pointer_cast<AisDeviceCommandReplyObject>( ReadDataFrom( source ) );
    bool equal = aisDeviceCommandReplyObject2->IsEqualTo( *aisDeviceCommandReplyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisDeviceConfigurationObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisDeviceConfigurationObjectSerializationTest )
{
    auto aisDeviceConfigurationObject1 = std::make_shared<AisDeviceConfigurationObject>( );
    aisDeviceConfigurationObject1->SetId( Guid( L"{1888438C-A8B0-211D-84B8-150D1811C231}" ) );
    aisDeviceConfigurationObject1->SetRowVersion( 2386248851855524748LL );
    aisDeviceConfigurationObject1->SetAisDevice( Guid( L"{1888438C-A8B0-211D-84B8-150D1811C231}" ) );
    aisDeviceConfigurationObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisDeviceConfigurationObject1->SetFilter( false );
    aisDeviceConfigurationObject1->SetNorthWestLatitude( 2386248851855525 );
    aisDeviceConfigurationObject1->SetNorthWestLongitude( 2386248851855525 );
    aisDeviceConfigurationObject1->SetSouthEastLatitude( 2386248851855525 );
    aisDeviceConfigurationObject1->SetSouthEastLongitude( 2386248851855525 );
    aisDeviceConfigurationObject1->SetComPort( L"ComPort" );
    aisDeviceConfigurationObject1->SetBaudRate( 411583372L );
    aisDeviceConfigurationObject1->SetIPAddress( L"IPAddress" );
    aisDeviceConfigurationObject1->SetPort( 411583372L );
    aisDeviceConfigurationObject1->SetUdpPort( 411583372L );
    aisDeviceConfigurationObject1->SetAuthenticate( false );
    aisDeviceConfigurationObject1->SetUserName( L"UserName" );
    aisDeviceConfigurationObject1->SetPassword( L"Password" );
    aisDeviceConfigurationObject1->SetAuthenticationURL( L"AuthenticationURL" );
    aisDeviceConfigurationObject1->SetConnectionType( AisDeviceConnectionType::Unknown );
    aisDeviceConfigurationObject1->SetSourceUpdateRate( 411583372L );
    aisDeviceConfigurationObject1->SetConfigurationURL( L"ConfigurationURL" );
    aisDeviceConfigurationObject1->SetStoreReceivedSentences( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisDeviceConfigurationObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisDeviceConfigurationObject2 = std::reinterpret_pointer_cast<AisDeviceConfigurationObject>( ReadDataFrom( source ) );
    bool equal = aisDeviceConfigurationObject2->IsEqualTo( *aisDeviceConfigurationObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisDeviceRawMessageObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisDeviceRawMessageObjectSerializationTest )
{
    auto aisDeviceRawMessageObject1 = std::make_shared<AisDeviceRawMessageObject>( );
    aisDeviceRawMessageObject1->SetId( Guid( L"{5F78586E-B6FE-19AB-98D5-6D7FFA1E1A76}" ) );
    aisDeviceRawMessageObject1->SetRowVersion( 1849773275605391470LL );
    aisDeviceRawMessageObject1->SetAisDevice( Guid( L"{5F78586E-B6FE-19AB-98D5-6D7FFA1E1A76}" ) );
    aisDeviceRawMessageObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisDeviceRawMessageObject1->SetIsSent( false );
    aisDeviceRawMessageObject1->SetMessage( L"Message" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisDeviceRawMessageObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisDeviceRawMessageObject2 = std::reinterpret_pointer_cast<AisDeviceRawMessageObject>( ReadDataFrom( source ) );
    bool equal = aisDeviceRawMessageObject2->IsEqualTo( *aisDeviceRawMessageObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisDeviceRawSentenceObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisDeviceRawSentenceObjectSerializationTest )
{
    auto aisDeviceRawSentenceObject1 = std::make_shared<AisDeviceRawSentenceObject>( );
    aisDeviceRawSentenceObject1->SetId( Guid( L"{0110FDB4-7CDF-2EE6-7467-3EFB8008BF2D}" ) );
    aisDeviceRawSentenceObject1->SetRowVersion( 3379525867625577908LL );
    aisDeviceRawSentenceObject1->SetAisDevice( Guid( L"{0110FDB4-7CDF-2EE6-7467-3EFB8008BF2D}" ) );
    aisDeviceRawSentenceObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisDeviceRawSentenceObject1->SetSentence( L"Sentence" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisDeviceRawSentenceObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisDeviceRawSentenceObject2 = std::reinterpret_pointer_cast<AisDeviceRawSentenceObject>( ReadDataFrom( source ) );
    bool equal = aisDeviceRawSentenceObject2->IsEqualTo( *aisDeviceRawSentenceObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AidToNavigationReportMessageObjectSerializationTest
BOOST_AUTO_TEST_CASE( AidToNavigationReportMessageObjectSerializationTest )
{
    auto aidToNavigationReportMessageObject1 = std::make_shared<AidToNavigationReportMessageObject>( );
    aidToNavigationReportMessageObject1->SetId( Guid( L"{A8095C85-AF09-1B47-D8E2-F59015903AA1}" ) );
    aidToNavigationReportMessageObject1->SetRowVersion( 1965732218379263109LL );
    aidToNavigationReportMessageObject1->SetAisDevice( Guid( L"{A8095C85-AF09-1B47-D8E2-F59015903AA1}" ) );
    aidToNavigationReportMessageObject1->SetReceivedTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aidToNavigationReportMessageObject1->SetMessageSequenceNumber( 1965732218379263109LL );
    aidToNavigationReportMessageObject1->SetRepeat( -1475781499L );
    aidToNavigationReportMessageObject1->SetMmsi( Guid( L"{A8095C85-AF09-1B47-D8E2-F59015903AA1}" ) );
    aidToNavigationReportMessageObject1->SetNavigationalAidType( NavigationalAidType::LightWithoutSectors );
    aidToNavigationReportMessageObject1->SetName( L"Name" );
    aidToNavigationReportMessageObject1->SetPositionAccuracy( PositionAccuracy::High );
    aidToNavigationReportMessageObject1->SetLongitude( 1965732218379263.2 );
    aidToNavigationReportMessageObject1->SetLatitude( 1965732218379263.2 );
    aidToNavigationReportMessageObject1->SetDimensionToBow( -1475781499L );
    aidToNavigationReportMessageObject1->SetDimensionToStern( -1475781499L );
    aidToNavigationReportMessageObject1->SetDimensionToPort( -1475781499L );
    aidToNavigationReportMessageObject1->SetDimensionToStarboard( -1475781499L );
    aidToNavigationReportMessageObject1->SetPositionFixType( PositionFixType::Undefined2 );
    aidToNavigationReportMessageObject1->SetTimestamp( -1475781499L );
    aidToNavigationReportMessageObject1->SetOffPosition( false );
    aidToNavigationReportMessageObject1->SetRegionalReserved( -1475781499L );
    aidToNavigationReportMessageObject1->SetRaim( Raim::InUse );
    aidToNavigationReportMessageObject1->SetVirtualAid( false );
    aidToNavigationReportMessageObject1->SetAssigned( false );
    aidToNavigationReportMessageObject1->SetSpare( -1475781499L );
    aidToNavigationReportMessageObject1->SetNameExtension( L"NameExtension" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aidToNavigationReportMessageObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aidToNavigationReportMessageObject2 = std::reinterpret_pointer_cast<AidToNavigationReportMessageObject>( ReadDataFrom( source ) );
    bool equal = aidToNavigationReportMessageObject2->IsEqualTo( *aidToNavigationReportMessageObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisAddressedSafetyRelatedMessageObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisAddressedSafetyRelatedMessageObjectSerializationTest )
{
    auto aisAddressedSafetyRelatedMessageObject1 = std::make_shared<AisAddressedSafetyRelatedMessageObject>( );
    aisAddressedSafetyRelatedMessageObject1->SetId( Guid( L"{E6B4FA51-12E6-F131-8F8C-4867672D5F8A}" ) );
    aisAddressedSafetyRelatedMessageObject1->SetRowVersion( -1067050853787698607LL );
    aisAddressedSafetyRelatedMessageObject1->SetAisDevice( Guid( L"{E6B4FA51-12E6-F131-8F8C-4867672D5F8A}" ) );
    aisAddressedSafetyRelatedMessageObject1->SetReceivedTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisAddressedSafetyRelatedMessageObject1->SetMessageSequenceNumber( -1067050853787698607LL );
    aisAddressedSafetyRelatedMessageObject1->SetRepeat( -424347055L );
    aisAddressedSafetyRelatedMessageObject1->SetMmsi( Guid( L"{E6B4FA51-12E6-F131-8F8C-4867672D5F8A}" ) );
    aisAddressedSafetyRelatedMessageObject1->SetSequenceNumber( -424347055L );
    aisAddressedSafetyRelatedMessageObject1->SetDestinationMmsi( Guid( L"{E6B4FA51-12E6-F131-8F8C-4867672D5F8A}" ) );
    aisAddressedSafetyRelatedMessageObject1->SetRetransmitFlag( false );
    aisAddressedSafetyRelatedMessageObject1->SetSpare( -424347055L );
    aisAddressedSafetyRelatedMessageObject1->SetText( L"Text" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisAddressedSafetyRelatedMessageObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisAddressedSafetyRelatedMessageObject2 = std::reinterpret_pointer_cast<AisAddressedSafetyRelatedMessageObject>( ReadDataFrom( source ) );
    bool equal = aisAddressedSafetyRelatedMessageObject2->IsEqualTo( *aisAddressedSafetyRelatedMessageObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisBaseStationReportMessageObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisBaseStationReportMessageObjectSerializationTest )
{
    auto aisBaseStationReportMessageObject1 = std::make_shared<AisBaseStationReportMessageObject>( );
    aisBaseStationReportMessageObject1->SetId( Guid( L"{7D642251-4972-A316-C568-924EBE26448A}" ) );
    aisBaseStationReportMessageObject1->SetRowVersion( -6695083039960849839LL );
    aisBaseStationReportMessageObject1->SetAisDevice( Guid( L"{7D642251-4972-A316-C568-924EBE26448A}" ) );
    aisBaseStationReportMessageObject1->SetReceivedTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisBaseStationReportMessageObject1->SetMessageSequenceNumber( -6695083039960849839LL );
    aisBaseStationReportMessageObject1->SetRepeat( 2103714385L );
    aisBaseStationReportMessageObject1->SetMmsi( Guid( L"{7D642251-4972-A316-C568-924EBE26448A}" ) );
    aisBaseStationReportMessageObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisBaseStationReportMessageObject1->SetPositionAccuracy( PositionAccuracy::High );
    aisBaseStationReportMessageObject1->SetLongitude( 11751661033748702 );
    aisBaseStationReportMessageObject1->SetLatitude( 11751661033748702 );
    aisBaseStationReportMessageObject1->SetPositionFixType( PositionFixType::Surveyed );
    aisBaseStationReportMessageObject1->SetSpare( 2103714385L );
    aisBaseStationReportMessageObject1->SetRaim( Raim::InUse );
    aisBaseStationReportMessageObject1->SetRadioStatus( 2103714385L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisBaseStationReportMessageObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisBaseStationReportMessageObject2 = std::reinterpret_pointer_cast<AisBaseStationReportMessageObject>( ReadDataFrom( source ) );
    bool equal = aisBaseStationReportMessageObject2->IsEqualTo( *aisBaseStationReportMessageObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisBinaryAcknowledgeMessageObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisBinaryAcknowledgeMessageObjectSerializationTest )
{
    auto aisBinaryAcknowledgeMessageObject1 = std::make_shared<AisBinaryAcknowledgeMessageObject>( );
    aisBinaryAcknowledgeMessageObject1->SetId( Guid( L"{7D7D182B-0D08-F217-4FE8-B010BEBE18D4}" ) );
    aisBinaryAcknowledgeMessageObject1->SetRowVersion( -1002318061950396373LL );
    aisBinaryAcknowledgeMessageObject1->SetAisDevice( Guid( L"{7D7D182B-0D08-F217-4FE8-B010BEBE18D4}" ) );
    aisBinaryAcknowledgeMessageObject1->SetReceivedTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisBinaryAcknowledgeMessageObject1->SetMessageSequenceNumber( -1002318061950396373LL );
    aisBinaryAcknowledgeMessageObject1->SetRepeat( 2105350187L );
    aisBinaryAcknowledgeMessageObject1->SetMmsi( Guid( L"{7D7D182B-0D08-F217-4FE8-B010BEBE18D4}" ) );
    aisBinaryAcknowledgeMessageObject1->SetSpare( 2105350187L );
    aisBinaryAcknowledgeMessageObject1->SetSequenceNumber1( 2105350187L );
    aisBinaryAcknowledgeMessageObject1->SetMmsi1( Guid( L"{7D7D182B-0D08-F217-4FE8-B010BEBE18D4}" ) );
    aisBinaryAcknowledgeMessageObject1->SetSequenceNumber2( 2105350187L );
    aisBinaryAcknowledgeMessageObject1->SetMmsi2( Guid( L"{7D7D182B-0D08-F217-4FE8-B010BEBE18D4}" ) );
    aisBinaryAcknowledgeMessageObject1->SetSequenceNumber3( 2105350187L );
    aisBinaryAcknowledgeMessageObject1->SetMmsi3( Guid( L"{7D7D182B-0D08-F217-4FE8-B010BEBE18D4}" ) );
    aisBinaryAcknowledgeMessageObject1->SetSequenceNumber4( 2105350187L );
    aisBinaryAcknowledgeMessageObject1->SetMmsi4( Guid( L"{7D7D182B-0D08-F217-4FE8-B010BEBE18D4}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisBinaryAcknowledgeMessageObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisBinaryAcknowledgeMessageObject2 = std::reinterpret_pointer_cast<AisBinaryAcknowledgeMessageObject>( ReadDataFrom( source ) );
    bool equal = aisBinaryAcknowledgeMessageObject2->IsEqualTo( *aisBinaryAcknowledgeMessageObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisBinaryAddressedMessageObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisBinaryAddressedMessageObjectSerializationTest )
{
    auto aisBinaryAddressedMessageObject1 = std::make_shared<AisBinaryAddressedMessageObject>( );
    aisBinaryAddressedMessageObject1->SetId( Guid( L"{D1FE2C97-3198-60D6-066B-8C198B7F34E9}" ) );
    aisBinaryAddressedMessageObject1->SetRowVersion( 6977819205085047959LL );
    aisBinaryAddressedMessageObject1->SetAisDevice( Guid( L"{D1FE2C97-3198-60D6-066B-8C198B7F34E9}" ) );
    aisBinaryAddressedMessageObject1->SetReceivedTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisBinaryAddressedMessageObject1->SetMessageSequenceNumber( 6977819205085047959LL );
    aisBinaryAddressedMessageObject1->SetRepeat( -771871593L );
    aisBinaryAddressedMessageObject1->SetMmsi( Guid( L"{D1FE2C97-3198-60D6-066B-8C198B7F34E9}" ) );
    aisBinaryAddressedMessageObject1->SetSequenceNumber( -771871593L );
    aisBinaryAddressedMessageObject1->SetDestinationMmsi( Guid( L"{D1FE2C97-3198-60D6-066B-8C198B7F34E9}" ) );
    aisBinaryAddressedMessageObject1->SetRetransmitFlag( false );
    aisBinaryAddressedMessageObject1->SetSpare( -771871593L );
    aisBinaryAddressedMessageObject1->SetDesignatedAreaCode( -771871593L );
    aisBinaryAddressedMessageObject1->SetFunctionalId( -771871593L );
    aisBinaryAddressedMessageObject1->SetData( L"Data" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisBinaryAddressedMessageObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisBinaryAddressedMessageObject2 = std::reinterpret_pointer_cast<AisBinaryAddressedMessageObject>( ReadDataFrom( source ) );
    bool equal = aisBinaryAddressedMessageObject2->IsEqualTo( *aisBinaryAddressedMessageObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisBinaryBroadcastMessageObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisBinaryBroadcastMessageObjectSerializationTest )
{
    auto aisBinaryBroadcastMessageObject1 = std::make_shared<AisBinaryBroadcastMessageObject>( );
    aisBinaryBroadcastMessageObject1->SetId( Guid( L"{F2AD5C24-F9C1-C1D8-831B-9F834FB53A24}" ) );
    aisBinaryBroadcastMessageObject1->SetRowVersion( -4478555218024506332LL );
    aisBinaryBroadcastMessageObject1->SetAisDevice( Guid( L"{F2AD5C24-F9C1-C1D8-831B-9F834FB53A24}" ) );
    aisBinaryBroadcastMessageObject1->SetReceivedTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisBinaryBroadcastMessageObject1->SetMessageSequenceNumber( -4478555218024506332LL );
    aisBinaryBroadcastMessageObject1->SetRepeat( -223519708L );
    aisBinaryBroadcastMessageObject1->SetMmsi( Guid( L"{F2AD5C24-F9C1-C1D8-831B-9F834FB53A24}" ) );
    aisBinaryBroadcastMessageObject1->SetSpare( -223519708L );
    aisBinaryBroadcastMessageObject1->SetDesignatedAreaCode( -223519708L );
    aisBinaryBroadcastMessageObject1->SetFunctionalId( -223519708L );
    aisBinaryBroadcastMessageObject1->SetData( L"Data" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisBinaryBroadcastMessageObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisBinaryBroadcastMessageObject2 = std::reinterpret_pointer_cast<AisBinaryBroadcastMessageObject>( ReadDataFrom( source ) );
    bool equal = aisBinaryBroadcastMessageObject2->IsEqualTo( *aisBinaryBroadcastMessageObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisDataLinkManagementMessageObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisDataLinkManagementMessageObjectSerializationTest )
{
    auto aisDataLinkManagementMessageObject1 = std::make_shared<AisDataLinkManagementMessageObject>( );
    aisDataLinkManagementMessageObject1->SetId( Guid( L"{11F331C0-404D-8BCF-D1F3-02B288CF8C03}" ) );
    aisDataLinkManagementMessageObject1->SetRowVersion( -8372402482500652608LL );
    aisDataLinkManagementMessageObject1->SetAisDevice( Guid( L"{11F331C0-404D-8BCF-D1F3-02B288CF8C03}" ) );
    aisDataLinkManagementMessageObject1->SetReceivedTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisDataLinkManagementMessageObject1->SetMessageSequenceNumber( -8372402482500652608LL );
    aisDataLinkManagementMessageObject1->SetRepeat( 301150656L );
    aisDataLinkManagementMessageObject1->SetMmsi( Guid( L"{11F331C0-404D-8BCF-D1F3-02B288CF8C03}" ) );
    aisDataLinkManagementMessageObject1->SetSpare( 301150656L );
    aisDataLinkManagementMessageObject1->SetOffset1( 301150656L );
    aisDataLinkManagementMessageObject1->SetReservedSlots1( 301150656L );
    aisDataLinkManagementMessageObject1->SetTimeout1( 301150656L );
    aisDataLinkManagementMessageObject1->SetIncrement1( 301150656L );
    aisDataLinkManagementMessageObject1->SetOffset2( 301150656L );
    aisDataLinkManagementMessageObject1->SetReservedSlots2( 301150656L );
    aisDataLinkManagementMessageObject1->SetTimeout2( 301150656L );
    aisDataLinkManagementMessageObject1->SetIncrement2( 301150656L );
    aisDataLinkManagementMessageObject1->SetOffset3( 301150656L );
    aisDataLinkManagementMessageObject1->SetReservedSlots3( 301150656L );
    aisDataLinkManagementMessageObject1->SetTimeout3( 301150656L );
    aisDataLinkManagementMessageObject1->SetIncrement3( 301150656L );
    aisDataLinkManagementMessageObject1->SetOffset4( 301150656L );
    aisDataLinkManagementMessageObject1->SetReservedSlots4( 301150656L );
    aisDataLinkManagementMessageObject1->SetTimeout4( 301150656L );
    aisDataLinkManagementMessageObject1->SetIncrement4( 301150656L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisDataLinkManagementMessageObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisDataLinkManagementMessageObject2 = std::reinterpret_pointer_cast<AisDataLinkManagementMessageObject>( ReadDataFrom( source ) );
    bool equal = aisDataLinkManagementMessageObject2->IsEqualTo( *aisDataLinkManagementMessageObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisExtendedClassBCsPositionReportMessageObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisExtendedClassBCsPositionReportMessageObjectSerializationTest )
{
    auto aisExtendedClassBCsPositionReportMessageObject1 = std::make_shared<AisExtendedClassBCsPositionReportMessageObject>( );
    aisExtendedClassBCsPositionReportMessageObject1->SetId( Guid( L"{3800E00B-53D3-860B-61D0-CACB1C0007D0}" ) );
    aisExtendedClassBCsPositionReportMessageObject1->SetRowVersion( -8787838081240604661LL );
    aisExtendedClassBCsPositionReportMessageObject1->SetAisDevice( Guid( L"{3800E00B-53D3-860B-61D0-CACB1C0007D0}" ) );
    aisExtendedClassBCsPositionReportMessageObject1->SetReceivedTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisExtendedClassBCsPositionReportMessageObject1->SetMessageSequenceNumber( -8787838081240604661LL );
    aisExtendedClassBCsPositionReportMessageObject1->SetRepeat( 939581451L );
    aisExtendedClassBCsPositionReportMessageObject1->SetMmsi( Guid( L"{3800E00B-53D3-860B-61D0-CACB1C0007D0}" ) );
    aisExtendedClassBCsPositionReportMessageObject1->SetReserved( 939581451L );
    aisExtendedClassBCsPositionReportMessageObject1->SetSpeedOverGround( 9658905992468946 );
    aisExtendedClassBCsPositionReportMessageObject1->SetPositionAccuracy( PositionAccuracy::High );
    aisExtendedClassBCsPositionReportMessageObject1->SetLongitude( 9658905992468946 );
    aisExtendedClassBCsPositionReportMessageObject1->SetLatitude( 9658905992468946 );
    aisExtendedClassBCsPositionReportMessageObject1->SetCourseOverGround( 9658905992468946 );
    aisExtendedClassBCsPositionReportMessageObject1->SetTrueHeading( 939581451L );
    aisExtendedClassBCsPositionReportMessageObject1->SetTimestamp( 939581451L );
    aisExtendedClassBCsPositionReportMessageObject1->SetRegionalReserved( 939581451L );
    aisExtendedClassBCsPositionReportMessageObject1->SetName( Guid( L"{3800E00B-53D3-860B-61D0-CACB1C0007D0}" ) );
    aisExtendedClassBCsPositionReportMessageObject1->SetShipType( ShipType::PassengerReserved1 );
    aisExtendedClassBCsPositionReportMessageObject1->SetDimensionToBow( 939581451L );
    aisExtendedClassBCsPositionReportMessageObject1->SetDimensionToStern( 939581451L );
    aisExtendedClassBCsPositionReportMessageObject1->SetDimensionToPort( 939581451L );
    aisExtendedClassBCsPositionReportMessageObject1->SetDimensionToStarboard( 939581451L );
    aisExtendedClassBCsPositionReportMessageObject1->SetPositionFixType( PositionFixType::Chayka );
    aisExtendedClassBCsPositionReportMessageObject1->SetRaim( Raim::InUse );
    aisExtendedClassBCsPositionReportMessageObject1->SetDataTerminalReady( false );
    aisExtendedClassBCsPositionReportMessageObject1->SetAssigned( false );
    aisExtendedClassBCsPositionReportMessageObject1->SetSpare( 939581451L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisExtendedClassBCsPositionReportMessageObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisExtendedClassBCsPositionReportMessageObject2 = std::reinterpret_pointer_cast<AisExtendedClassBCsPositionReportMessageObject>( ReadDataFrom( source ) );
    bool equal = aisExtendedClassBCsPositionReportMessageObject2->IsEqualTo( *aisExtendedClassBCsPositionReportMessageObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisInterrogationMessageObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisInterrogationMessageObjectSerializationTest )
{
    auto aisInterrogationMessageObject1 = std::make_shared<AisInterrogationMessageObject>( );
    aisInterrogationMessageObject1->SetId( Guid( L"{E8E82CCD-52E4-6679-669E-4A27171734B3}" ) );
    aisInterrogationMessageObject1->SetRowVersion( 7384024207164189901LL );
    aisInterrogationMessageObject1->SetAisDevice( Guid( L"{E8E82CCD-52E4-6679-669E-4A27171734B3}" ) );
    aisInterrogationMessageObject1->SetReceivedTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisInterrogationMessageObject1->SetMessageSequenceNumber( 7384024207164189901LL );
    aisInterrogationMessageObject1->SetRepeat( -387437363L );
    aisInterrogationMessageObject1->SetMmsi( Guid( L"{E8E82CCD-52E4-6679-669E-4A27171734B3}" ) );
    aisInterrogationMessageObject1->SetInterrogatedMmsi( Guid( L"{E8E82CCD-52E4-6679-669E-4A27171734B3}" ) );
    aisInterrogationMessageObject1->SetFirstMessageType( AisMessageType::SafetyRelatedBroadcastMessage );
    aisInterrogationMessageObject1->SetFirstSlotOffset( -387437363L );
    aisInterrogationMessageObject1->SetSecondMessageType( AisMessageType::SafetyRelatedBroadcastMessage );
    aisInterrogationMessageObject1->SetSecondSlotOffset( -387437363L );
    aisInterrogationMessageObject1->SetSecondStationInterrogationMmsi( Guid( L"{E8E82CCD-52E4-6679-669E-4A27171734B3}" ) );
    aisInterrogationMessageObject1->SetSecondStationFirstMessageType( AisMessageType::SafetyRelatedBroadcastMessage );
    aisInterrogationMessageObject1->SetSecondStationFirstSlotOffset( -387437363L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisInterrogationMessageObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisInterrogationMessageObject2 = std::reinterpret_pointer_cast<AisInterrogationMessageObject>( ReadDataFrom( source ) );
    bool equal = aisInterrogationMessageObject2->IsEqualTo( *aisInterrogationMessageObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisPositionReportClassAAssignedScheduleMessageObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisPositionReportClassAAssignedScheduleMessageObjectSerializationTest )
{
    auto aisPositionReportClassAAssignedScheduleMessageObject1 = std::make_shared<AisPositionReportClassAAssignedScheduleMessageObject>( );
    aisPositionReportClassAAssignedScheduleMessageObject1->SetId( Guid( L"{CA9F2595-C836-B10F-8DF0-136C53F9A4A9}" ) );
    aisPositionReportClassAAssignedScheduleMessageObject1->SetRowVersion( -5688107666692430443LL );
    aisPositionReportClassAAssignedScheduleMessageObject1->SetAisDevice( Guid( L"{CA9F2595-C836-B10F-8DF0-136C53F9A4A9}" ) );
    aisPositionReportClassAAssignedScheduleMessageObject1->SetReceivedTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisPositionReportClassAAssignedScheduleMessageObject1->SetMessageSequenceNumber( -5688107666692430443LL );
    aisPositionReportClassAAssignedScheduleMessageObject1->SetRepeat( -895539819L );
    aisPositionReportClassAAssignedScheduleMessageObject1->SetMmsi( Guid( L"{CA9F2595-C836-B10F-8DF0-136C53F9A4A9}" ) );
    aisPositionReportClassAAssignedScheduleMessageObject1->SetNavigationStatus( NavigationStatus::Moored );
    aisPositionReportClassAAssignedScheduleMessageObject1->SetRateOfTurn( -895539819L );
    aisPositionReportClassAAssignedScheduleMessageObject1->SetSpeedOverGround( 12758636407017122 );
    aisPositionReportClassAAssignedScheduleMessageObject1->SetPositionAccuracy( PositionAccuracy::High );
    aisPositionReportClassAAssignedScheduleMessageObject1->SetLongitude( 12758636407017122 );
    aisPositionReportClassAAssignedScheduleMessageObject1->SetLatitude( 12758636407017122 );
    aisPositionReportClassAAssignedScheduleMessageObject1->SetCourseOverGround( 12758636407017122 );
    aisPositionReportClassAAssignedScheduleMessageObject1->SetTrueHeading( -895539819L );
    aisPositionReportClassAAssignedScheduleMessageObject1->SetTimestamp( -895539819L );
    aisPositionReportClassAAssignedScheduleMessageObject1->SetManeuverIndicator( ManeuverIndicator::NotAvailable );
    aisPositionReportClassAAssignedScheduleMessageObject1->SetSpare( -895539819L );
    aisPositionReportClassAAssignedScheduleMessageObject1->SetRaim( Raim::InUse );
    aisPositionReportClassAAssignedScheduleMessageObject1->SetRadioStatus( -895539819L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisPositionReportClassAAssignedScheduleMessageObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisPositionReportClassAAssignedScheduleMessageObject2 = std::reinterpret_pointer_cast<AisPositionReportClassAAssignedScheduleMessageObject>( ReadDataFrom( source ) );
    bool equal = aisPositionReportClassAAssignedScheduleMessageObject2->IsEqualTo( *aisPositionReportClassAAssignedScheduleMessageObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisPositionReportClassAMessageObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisPositionReportClassAMessageObjectSerializationTest )
{
    auto aisPositionReportClassAMessageObject1 = std::make_shared<AisPositionReportClassAMessageObject>( );
    aisPositionReportClassAMessageObject1->SetId( Guid( L"{05ACAC97-D62C-C7D9-E39B-6B34A03535E9}" ) );
    aisPositionReportClassAMessageObject1->SetRowVersion( -4045967305653572457LL );
    aisPositionReportClassAMessageObject1->SetAisDevice( Guid( L"{05ACAC97-D62C-C7D9-E39B-6B34A03535E9}" ) );
    aisPositionReportClassAMessageObject1->SetReceivedTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisPositionReportClassAMessageObject1->SetMessageSequenceNumber( -4045967305653572457LL );
    aisPositionReportClassAMessageObject1->SetRepeat( 95202455L );
    aisPositionReportClassAMessageObject1->SetMmsi( Guid( L"{05ACAC97-D62C-C7D9-E39B-6B34A03535E9}" ) );
    aisPositionReportClassAMessageObject1->SetNavigationStatus( NavigationStatus::EngagedInFishing );
    aisPositionReportClassAMessageObject1->SetRateOfTurn( 95202455L );
    aisPositionReportClassAMessageObject1->SetSpeedOverGround( 14400776768055980 );
    aisPositionReportClassAMessageObject1->SetPositionAccuracy( PositionAccuracy::High );
    aisPositionReportClassAMessageObject1->SetLongitude( 14400776768055980 );
    aisPositionReportClassAMessageObject1->SetLatitude( 14400776768055980 );
    aisPositionReportClassAMessageObject1->SetCourseOverGround( 14400776768055980 );
    aisPositionReportClassAMessageObject1->SetTrueHeading( 95202455L );
    aisPositionReportClassAMessageObject1->SetTimestamp( 95202455L );
    aisPositionReportClassAMessageObject1->SetManeuverIndicator( ManeuverIndicator::NoSpecialManeuver );
    aisPositionReportClassAMessageObject1->SetSpare( 95202455L );
    aisPositionReportClassAMessageObject1->SetRaim( Raim::InUse );
    aisPositionReportClassAMessageObject1->SetRadioStatus( 95202455L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisPositionReportClassAMessageObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisPositionReportClassAMessageObject2 = std::reinterpret_pointer_cast<AisPositionReportClassAMessageObject>( ReadDataFrom( source ) );
    bool equal = aisPositionReportClassAMessageObject2->IsEqualTo( *aisPositionReportClassAMessageObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisPositionReportClassAResponseToInterrogationMessageObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisPositionReportClassAResponseToInterrogationMessageObjectSerializationTest )
{
    auto aisPositionReportClassAResponseToInterrogationMessageObject1 = std::make_shared<AisPositionReportClassAResponseToInterrogationMessageObject>( );
    aisPositionReportClassAResponseToInterrogationMessageObject1->SetId( Guid( L"{D9584796-610C-ED40-B702-86309B1AE269}" ) );
    aisPositionReportClassAResponseToInterrogationMessageObject1->SetRowVersion( -1350973180397205610LL );
    aisPositionReportClassAResponseToInterrogationMessageObject1->SetAisDevice( Guid( L"{D9584796-610C-ED40-B702-86309B1AE269}" ) );
    aisPositionReportClassAResponseToInterrogationMessageObject1->SetReceivedTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisPositionReportClassAResponseToInterrogationMessageObject1->SetMessageSequenceNumber( -1350973180397205610LL );
    aisPositionReportClassAResponseToInterrogationMessageObject1->SetRepeat( -648525930L );
    aisPositionReportClassAResponseToInterrogationMessageObject1->SetMmsi( Guid( L"{D9584796-610C-ED40-B702-86309B1AE269}" ) );
    aisPositionReportClassAResponseToInterrogationMessageObject1->SetNavigationStatus( NavigationStatus::Aground );
    aisPositionReportClassAResponseToInterrogationMessageObject1->SetRateOfTurn( -648525930L );
    aisPositionReportClassAResponseToInterrogationMessageObject1->SetSpeedOverGround( 17095770893312346 );
    aisPositionReportClassAResponseToInterrogationMessageObject1->SetPositionAccuracy( PositionAccuracy::Low );
    aisPositionReportClassAResponseToInterrogationMessageObject1->SetLongitude( 17095770893312346 );
    aisPositionReportClassAResponseToInterrogationMessageObject1->SetLatitude( 17095770893312346 );
    aisPositionReportClassAResponseToInterrogationMessageObject1->SetCourseOverGround( 17095770893312346 );
    aisPositionReportClassAResponseToInterrogationMessageObject1->SetTrueHeading( -648525930L );
    aisPositionReportClassAResponseToInterrogationMessageObject1->SetTimestamp( -648525930L );
    aisPositionReportClassAResponseToInterrogationMessageObject1->SetManeuverIndicator( ManeuverIndicator::NotAvailable );
    aisPositionReportClassAResponseToInterrogationMessageObject1->SetSpare( -648525930L );
    aisPositionReportClassAResponseToInterrogationMessageObject1->SetRaim( Raim::NotInUse );
    aisPositionReportClassAResponseToInterrogationMessageObject1->SetRadioStatus( -648525930L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisPositionReportClassAResponseToInterrogationMessageObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisPositionReportClassAResponseToInterrogationMessageObject2 = std::reinterpret_pointer_cast<AisPositionReportClassAResponseToInterrogationMessageObject>( ReadDataFrom( source ) );
    bool equal = aisPositionReportClassAResponseToInterrogationMessageObject2->IsEqualTo( *aisPositionReportClassAResponseToInterrogationMessageObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisPositionReportForLongRangeApplicationsMessageObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisPositionReportForLongRangeApplicationsMessageObjectSerializationTest )
{
    auto aisPositionReportForLongRangeApplicationsMessageObject1 = std::make_shared<AisPositionReportForLongRangeApplicationsMessageObject>( );
    aisPositionReportForLongRangeApplicationsMessageObject1->SetId( Guid( L"{CB0CB752-220B-B92B-9DD4-44D0D330ED4A}" ) );
    aisPositionReportForLongRangeApplicationsMessageObject1->SetRowVersion( -5103948318647732398LL );
    aisPositionReportForLongRangeApplicationsMessageObject1->SetAisDevice( Guid( L"{CB0CB752-220B-B92B-9DD4-44D0D330ED4A}" ) );
    aisPositionReportForLongRangeApplicationsMessageObject1->SetReceivedTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisPositionReportForLongRangeApplicationsMessageObject1->SetMessageSequenceNumber( -5103948318647732398LL );
    aisPositionReportForLongRangeApplicationsMessageObject1->SetRepeat( -888359086L );
    aisPositionReportForLongRangeApplicationsMessageObject1->SetMmsi( Guid( L"{CB0CB752-220B-B92B-9DD4-44D0D330ED4A}" ) );
    aisPositionReportForLongRangeApplicationsMessageObject1->SetPositionAccuracy( PositionAccuracy::Low );
    aisPositionReportForLongRangeApplicationsMessageObject1->SetRaim( Raim::NotInUse );
    aisPositionReportForLongRangeApplicationsMessageObject1->SetNavigationStatus( NavigationStatus::NotUnderCommand );
    aisPositionReportForLongRangeApplicationsMessageObject1->SetLongitude( 13342795755061820 );
    aisPositionReportForLongRangeApplicationsMessageObject1->SetLatitude( 13342795755061820 );
    aisPositionReportForLongRangeApplicationsMessageObject1->SetSpeedOverGround( 13342795755061820 );
    aisPositionReportForLongRangeApplicationsMessageObject1->SetCourseOverGround( 13342795755061820 );
    aisPositionReportForLongRangeApplicationsMessageObject1->SetGnssPositionStatus( GnssPositionStatus::CurrentGnssPosition );
    aisPositionReportForLongRangeApplicationsMessageObject1->SetSpare( -888359086L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisPositionReportForLongRangeApplicationsMessageObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisPositionReportForLongRangeApplicationsMessageObject2 = std::reinterpret_pointer_cast<AisPositionReportForLongRangeApplicationsMessageObject>( ReadDataFrom( source ) );
    bool equal = aisPositionReportForLongRangeApplicationsMessageObject2->IsEqualTo( *aisPositionReportForLongRangeApplicationsMessageObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisSafetyRelatedAcknowledgmentMessageObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisSafetyRelatedAcknowledgmentMessageObjectSerializationTest )
{
    auto aisSafetyRelatedAcknowledgmentMessageObject1 = std::make_shared<AisSafetyRelatedAcknowledgmentMessageObject>( );
    aisSafetyRelatedAcknowledgmentMessageObject1->SetId( Guid( L"{DBA7680C-F9E3-8E3B-71DC-9FC7DBE51630}" ) );
    aisSafetyRelatedAcknowledgmentMessageObject1->SetRowVersion( -8197683939659782132LL );
    aisSafetyRelatedAcknowledgmentMessageObject1->SetAisDevice( Guid( L"{DBA7680C-F9E3-8E3B-71DC-9FC7DBE51630}" ) );
    aisSafetyRelatedAcknowledgmentMessageObject1->SetReceivedTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisSafetyRelatedAcknowledgmentMessageObject1->SetMessageSequenceNumber( -8197683939659782132LL );
    aisSafetyRelatedAcknowledgmentMessageObject1->SetRepeat( -609785844L );
    aisSafetyRelatedAcknowledgmentMessageObject1->SetMmsi( Guid( L"{DBA7680C-F9E3-8E3B-71DC-9FC7DBE51630}" ) );
    aisSafetyRelatedAcknowledgmentMessageObject1->SetSpare( -609785844L );
    aisSafetyRelatedAcknowledgmentMessageObject1->SetSequenceNumber1( -609785844L );
    aisSafetyRelatedAcknowledgmentMessageObject1->SetMmsi1( Guid( L"{DBA7680C-F9E3-8E3B-71DC-9FC7DBE51630}" ) );
    aisSafetyRelatedAcknowledgmentMessageObject1->SetSequenceNumber2( -609785844L );
    aisSafetyRelatedAcknowledgmentMessageObject1->SetMmsi2( Guid( L"{DBA7680C-F9E3-8E3B-71DC-9FC7DBE51630}" ) );
    aisSafetyRelatedAcknowledgmentMessageObject1->SetSequenceNumber3( -609785844L );
    aisSafetyRelatedAcknowledgmentMessageObject1->SetMmsi3( Guid( L"{DBA7680C-F9E3-8E3B-71DC-9FC7DBE51630}" ) );
    aisSafetyRelatedAcknowledgmentMessageObject1->SetSequenceNumber4( -609785844L );
    aisSafetyRelatedAcknowledgmentMessageObject1->SetMmsi4( Guid( L"{DBA7680C-F9E3-8E3B-71DC-9FC7DBE51630}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisSafetyRelatedAcknowledgmentMessageObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisSafetyRelatedAcknowledgmentMessageObject2 = std::reinterpret_pointer_cast<AisSafetyRelatedAcknowledgmentMessageObject>( ReadDataFrom( source ) );
    bool equal = aisSafetyRelatedAcknowledgmentMessageObject2->IsEqualTo( *aisSafetyRelatedAcknowledgmentMessageObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisStandardClassBCsPositionReportMessageObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisStandardClassBCsPositionReportMessageObjectSerializationTest )
{
    auto aisStandardClassBCsPositionReportMessageObject1 = std::make_shared<AisStandardClassBCsPositionReportMessageObject>( );
    aisStandardClassBCsPositionReportMessageObject1->SetId( Guid( L"{DE8F513C-118E-7428-2E14-88717BF18A3C}" ) );
    aisStandardClassBCsPositionReportMessageObject1->SetRowVersion( 8369959212785029436LL );
    aisStandardClassBCsPositionReportMessageObject1->SetAisDevice( Guid( L"{DE8F513C-118E-7428-2E14-88717BF18A3C}" ) );
    aisStandardClassBCsPositionReportMessageObject1->SetReceivedTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisStandardClassBCsPositionReportMessageObject1->SetMessageSequenceNumber( 8369959212785029436LL );
    aisStandardClassBCsPositionReportMessageObject1->SetRepeat( -561032900L );
    aisStandardClassBCsPositionReportMessageObject1->SetMmsi( Guid( L"{DE8F513C-118E-7428-2E14-88717BF18A3C}" ) );
    aisStandardClassBCsPositionReportMessageObject1->SetReserved( -561032900L );
    aisStandardClassBCsPositionReportMessageObject1->SetSpeedOverGround( 8369959212785029 );
    aisStandardClassBCsPositionReportMessageObject1->SetPositionAccuracy( PositionAccuracy::Low );
    aisStandardClassBCsPositionReportMessageObject1->SetLongitude( 8369959212785029 );
    aisStandardClassBCsPositionReportMessageObject1->SetLatitude( 8369959212785029 );
    aisStandardClassBCsPositionReportMessageObject1->SetCourseOverGround( 8369959212785029 );
    aisStandardClassBCsPositionReportMessageObject1->SetTrueHeading( -561032900L );
    aisStandardClassBCsPositionReportMessageObject1->SetTimestamp( -561032900L );
    aisStandardClassBCsPositionReportMessageObject1->SetRegionalReserved( -561032900L );
    aisStandardClassBCsPositionReportMessageObject1->SetIsCsUnit( false );
    aisStandardClassBCsPositionReportMessageObject1->SetHasDisplay( false );
    aisStandardClassBCsPositionReportMessageObject1->SetHasDscCapability( false );
    aisStandardClassBCsPositionReportMessageObject1->SetBand( false );
    aisStandardClassBCsPositionReportMessageObject1->SetCanAcceptMessage22( false );
    aisStandardClassBCsPositionReportMessageObject1->SetAssigned( false );
    aisStandardClassBCsPositionReportMessageObject1->SetRaim( Raim::NotInUse );
    aisStandardClassBCsPositionReportMessageObject1->SetRadioStatus( -561032900L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisStandardClassBCsPositionReportMessageObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisStandardClassBCsPositionReportMessageObject2 = std::reinterpret_pointer_cast<AisStandardClassBCsPositionReportMessageObject>( ReadDataFrom( source ) );
    bool equal = aisStandardClassBCsPositionReportMessageObject2->IsEqualTo( *aisStandardClassBCsPositionReportMessageObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisStandardSarAircraftPositionReportMessageObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisStandardSarAircraftPositionReportMessageObjectSerializationTest )
{
    auto aisStandardSarAircraftPositionReportMessageObject1 = std::make_shared<AisStandardSarAircraftPositionReportMessageObject>( );
    aisStandardSarAircraftPositionReportMessageObject1->SetId( Guid( L"{41467402-F4D5-7EAD-7EB5-2FAB82622E40}" ) );
    aisStandardSarAircraftPositionReportMessageObject1->SetRowVersion( 9128221216510211074LL );
    aisStandardSarAircraftPositionReportMessageObject1->SetAisDevice( Guid( L"{41467402-F4D5-7EAD-7EB5-2FAB82622E40}" ) );
    aisStandardSarAircraftPositionReportMessageObject1->SetReceivedTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisStandardSarAircraftPositionReportMessageObject1->SetMessageSequenceNumber( 9128221216510211074LL );
    aisStandardSarAircraftPositionReportMessageObject1->SetRepeat( 1095136258L );
    aisStandardSarAircraftPositionReportMessageObject1->SetMmsi( Guid( L"{41467402-F4D5-7EAD-7EB5-2FAB82622E40}" ) );
    aisStandardSarAircraftPositionReportMessageObject1->SetAltitude( 1095136258L );
    aisStandardSarAircraftPositionReportMessageObject1->SetSpeedOverGround( 1095136258L );
    aisStandardSarAircraftPositionReportMessageObject1->SetPositionAccuracy( PositionAccuracy::Low );
    aisStandardSarAircraftPositionReportMessageObject1->SetLongitude( 9128221216510212 );
    aisStandardSarAircraftPositionReportMessageObject1->SetLatitude( 9128221216510212 );
    aisStandardSarAircraftPositionReportMessageObject1->SetCourseOverGround( 9128221216510212 );
    aisStandardSarAircraftPositionReportMessageObject1->SetTimestamp( 1095136258L );
    aisStandardSarAircraftPositionReportMessageObject1->SetReserved( 1095136258L );
    aisStandardSarAircraftPositionReportMessageObject1->SetDataTerminalReady( false );
    aisStandardSarAircraftPositionReportMessageObject1->SetSpare( 1095136258L );
    aisStandardSarAircraftPositionReportMessageObject1->SetAssigned( false );
    aisStandardSarAircraftPositionReportMessageObject1->SetRaim( Raim::NotInUse );
    aisStandardSarAircraftPositionReportMessageObject1->SetRadioStatus( 1095136258L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisStandardSarAircraftPositionReportMessageObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisStandardSarAircraftPositionReportMessageObject2 = std::reinterpret_pointer_cast<AisStandardSarAircraftPositionReportMessageObject>( ReadDataFrom( source ) );
    bool equal = aisStandardSarAircraftPositionReportMessageObject2->IsEqualTo( *aisStandardSarAircraftPositionReportMessageObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisStaticAndVoyageRelatedDataMessageObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisStaticAndVoyageRelatedDataMessageObjectSerializationTest )
{
    auto aisStaticAndVoyageRelatedDataMessageObject1 = std::make_shared<AisStaticAndVoyageRelatedDataMessageObject>( );
    aisStaticAndVoyageRelatedDataMessageObject1->SetId( Guid( L"{FE446502-C000-ADA7-B5E5-03007F22A640}" ) );
    aisStaticAndVoyageRelatedDataMessageObject1->SetRowVersion( -5933562873538910974LL );
    aisStaticAndVoyageRelatedDataMessageObject1->SetAisDevice( Guid( L"{FE446502-C000-ADA7-B5E5-03007F22A640}" ) );
    aisStaticAndVoyageRelatedDataMessageObject1->SetReceivedTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisStaticAndVoyageRelatedDataMessageObject1->SetMessageSequenceNumber( -5933562873538910974LL );
    aisStaticAndVoyageRelatedDataMessageObject1->SetRepeat( -29072126L );
    aisStaticAndVoyageRelatedDataMessageObject1->SetMmsi( Guid( L"{FE446502-C000-ADA7-B5E5-03007F22A640}" ) );
    aisStaticAndVoyageRelatedDataMessageObject1->SetAisVersion( -29072126L );
    aisStaticAndVoyageRelatedDataMessageObject1->SetImoNumber( Guid( L"{FE446502-C000-ADA7-B5E5-03007F22A640}" ) );
    aisStaticAndVoyageRelatedDataMessageObject1->SetCallsign( Guid( L"{FE446502-C000-ADA7-B5E5-03007F22A640}" ) );
    aisStaticAndVoyageRelatedDataMessageObject1->SetShipName( Guid( L"{FE446502-C000-ADA7-B5E5-03007F22A640}" ) );
    aisStaticAndVoyageRelatedDataMessageObject1->SetShipType( ShipType::WingInGroundReserved4 );
    aisStaticAndVoyageRelatedDataMessageObject1->SetDimensionToBow( -29072126L );
    aisStaticAndVoyageRelatedDataMessageObject1->SetDimensionToStern( -29072126L );
    aisStaticAndVoyageRelatedDataMessageObject1->SetDimensionToPort( -29072126L );
    aisStaticAndVoyageRelatedDataMessageObject1->SetDimensionToStarboard( -29072126L );
    aisStaticAndVoyageRelatedDataMessageObject1->SetPositionFixType( PositionFixType::Glonass );
    aisStaticAndVoyageRelatedDataMessageObject1->SetEstimatedTimeOfArrival( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisStaticAndVoyageRelatedDataMessageObject1->SetDraught( 12513181200170642 );
    aisStaticAndVoyageRelatedDataMessageObject1->SetDestination( L"Destination" );
    aisStaticAndVoyageRelatedDataMessageObject1->SetDataTerminalReady( false );
    aisStaticAndVoyageRelatedDataMessageObject1->SetSpare( -29072126L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisStaticAndVoyageRelatedDataMessageObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisStaticAndVoyageRelatedDataMessageObject2 = std::reinterpret_pointer_cast<AisStaticAndVoyageRelatedDataMessageObject>( ReadDataFrom( source ) );
    bool equal = aisStaticAndVoyageRelatedDataMessageObject2->IsEqualTo( *aisStaticAndVoyageRelatedDataMessageObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisStaticDataReportMessageObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisStaticDataReportMessageObjectSerializationTest )
{
    auto aisStaticDataReportMessageObject1 = std::make_shared<AisStaticDataReportMessageObject>( );
    aisStaticDataReportMessageObject1->SetId( Guid( L"{69972CB9-08CA-C920-9304-105396E9349D}" ) );
    aisStaticDataReportMessageObject1->SetRowVersion( -3954150807383364423LL );
    aisStaticDataReportMessageObject1->SetAisDevice( Guid( L"{69972CB9-08CA-C920-9304-105396E9349D}" ) );
    aisStaticDataReportMessageObject1->SetReceivedTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisStaticDataReportMessageObject1->SetMessageSequenceNumber( -3954150807383364423LL );
    aisStaticDataReportMessageObject1->SetRepeat( 1771515065L );
    aisStaticDataReportMessageObject1->SetMmsi( Guid( L"{69972CB9-08CA-C920-9304-105396E9349D}" ) );
    aisStaticDataReportMessageObject1->SetPartNumber( 1771515065L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisStaticDataReportMessageObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisStaticDataReportMessageObject2 = std::reinterpret_pointer_cast<AisStaticDataReportMessageObject>( ReadDataFrom( source ) );
    bool equal = aisStaticDataReportMessageObject2->IsEqualTo( *aisStaticDataReportMessageObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisStaticDataReportPartAMessageObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisStaticDataReportPartAMessageObjectSerializationTest )
{
    auto aisStaticDataReportPartAMessageObject1 = std::make_shared<AisStaticDataReportPartAMessageObject>( );
    aisStaticDataReportPartAMessageObject1->SetId( Guid( L"{CA38BF53-B49F-618C-8631-2DF9531CFDCA}" ) );
    aisStaticDataReportPartAMessageObject1->SetRowVersion( 7029191716804018003LL );
    aisStaticDataReportPartAMessageObject1->SetAisDevice( Guid( L"{CA38BF53-B49F-618C-8631-2DF9531CFDCA}" ) );
    aisStaticDataReportPartAMessageObject1->SetReceivedTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisStaticDataReportPartAMessageObject1->SetMessageSequenceNumber( 7029191716804018003LL );
    aisStaticDataReportPartAMessageObject1->SetRepeat( -902250669L );
    aisStaticDataReportPartAMessageObject1->SetMmsi( Guid( L"{CA38BF53-B49F-618C-8631-2DF9531CFDCA}" ) );
    aisStaticDataReportPartAMessageObject1->SetPartNumber( -902250669L );
    aisStaticDataReportPartAMessageObject1->SetShipName( Guid( L"{CA38BF53-B49F-618C-8631-2DF9531CFDCA}" ) );
    aisStaticDataReportPartAMessageObject1->SetSpare( -902250669L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisStaticDataReportPartAMessageObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisStaticDataReportPartAMessageObject2 = std::reinterpret_pointer_cast<AisStaticDataReportPartAMessageObject>( ReadDataFrom( source ) );
    bool equal = aisStaticDataReportPartAMessageObject2->IsEqualTo( *aisStaticDataReportPartAMessageObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisStaticDataReportPartBMessageObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisStaticDataReportPartBMessageObjectSerializationTest )
{
    auto aisStaticDataReportPartBMessageObject1 = std::make_shared<AisStaticDataReportPartBMessageObject>( );
    aisStaticDataReportPartBMessageObject1->SetId( Guid( L"{F5627DB0-8BA6-0BD2-D04B-D165AF46BE0D}" ) );
    aisStaticDataReportPartBMessageObject1->SetRowVersion( 851896828724149680LL );
    aisStaticDataReportPartBMessageObject1->SetAisDevice( Guid( L"{F5627DB0-8BA6-0BD2-D04B-D165AF46BE0D}" ) );
    aisStaticDataReportPartBMessageObject1->SetReceivedTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisStaticDataReportPartBMessageObject1->SetMessageSequenceNumber( 851896828724149680LL );
    aisStaticDataReportPartBMessageObject1->SetRepeat( -178094672L );
    aisStaticDataReportPartBMessageObject1->SetMmsi( Guid( L"{F5627DB0-8BA6-0BD2-D04B-D165AF46BE0D}" ) );
    aisStaticDataReportPartBMessageObject1->SetPartNumber( -178094672L );
    aisStaticDataReportPartBMessageObject1->SetShipType( ShipType::HighSpeedCraftHazardousCategoryC );
    aisStaticDataReportPartBMessageObject1->SetVendorId( L"VendorId" );
    aisStaticDataReportPartBMessageObject1->SetUnitModelCode( -178094672L );
    aisStaticDataReportPartBMessageObject1->SetSerialNumber( -178094672L );
    aisStaticDataReportPartBMessageObject1->SetCallsign( Guid( L"{F5627DB0-8BA6-0BD2-D04B-D165AF46BE0D}" ) );
    aisStaticDataReportPartBMessageObject1->SetDimensionToBow( -178094672L );
    aisStaticDataReportPartBMessageObject1->SetDimensionToStern( -178094672L );
    aisStaticDataReportPartBMessageObject1->SetDimensionToPort( -178094672L );
    aisStaticDataReportPartBMessageObject1->SetDimensionToStarboard( -178094672L );
    aisStaticDataReportPartBMessageObject1->SetMothershipMmsi( Guid( L"{F5627DB0-8BA6-0BD2-D04B-D165AF46BE0D}" ) );
    aisStaticDataReportPartBMessageObject1->SetPositionFixType( PositionFixType::Undefined1 );
    aisStaticDataReportPartBMessageObject1->SetSpare( -178094672L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisStaticDataReportPartBMessageObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisStaticDataReportPartBMessageObject2 = std::reinterpret_pointer_cast<AisStaticDataReportPartBMessageObject>( ReadDataFrom( source ) );
    bool equal = aisStaticDataReportPartBMessageObject2->IsEqualTo( *aisStaticDataReportPartBMessageObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisUtcAndDateInquiryMessageObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisUtcAndDateInquiryMessageObjectSerializationTest )
{
    auto aisUtcAndDateInquiryMessageObject1 = std::make_shared<AisUtcAndDateInquiryMessageObject>( );
    aisUtcAndDateInquiryMessageObject1->SetId( Guid( L"{CA0D5117-9AF8-676C-E636-591F53B08AE8}" ) );
    aisUtcAndDateInquiryMessageObject1->SetRowVersion( 7452501876723765527LL );
    aisUtcAndDateInquiryMessageObject1->SetAisDevice( Guid( L"{CA0D5117-9AF8-676C-E636-591F53B08AE8}" ) );
    aisUtcAndDateInquiryMessageObject1->SetReceivedTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisUtcAndDateInquiryMessageObject1->SetMessageSequenceNumber( 7452501876723765527LL );
    aisUtcAndDateInquiryMessageObject1->SetRepeat( -905096937L );
    aisUtcAndDateInquiryMessageObject1->SetMmsi( Guid( L"{CA0D5117-9AF8-676C-E636-591F53B08AE8}" ) );
    aisUtcAndDateInquiryMessageObject1->SetSpare1( -905096937L );
    aisUtcAndDateInquiryMessageObject1->SetDestinationMmsi( Guid( L"{CA0D5117-9AF8-676C-E636-591F53B08AE8}" ) );
    aisUtcAndDateInquiryMessageObject1->SetSpare2( -905096937L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisUtcAndDateInquiryMessageObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisUtcAndDateInquiryMessageObject2 = std::reinterpret_pointer_cast<AisUtcAndDateInquiryMessageObject>( ReadDataFrom( source ) );
    bool equal = aisUtcAndDateInquiryMessageObject2->IsEqualTo( *aisUtcAndDateInquiryMessageObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisUtcAndDateResponseMessageObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisUtcAndDateResponseMessageObjectSerializationTest )
{
    auto aisUtcAndDateResponseMessageObject1 = std::make_shared<AisUtcAndDateResponseMessageObject>( );
    aisUtcAndDateResponseMessageObject1->SetId( Guid( L"{7ED5439C-5B10-6A85-56A1-DA087EABC239}" ) );
    aisUtcAndDateResponseMessageObject1->SetRowVersion( 7675641266328388508LL );
    aisUtcAndDateResponseMessageObject1->SetAisDevice( Guid( L"{7ED5439C-5B10-6A85-56A1-DA087EABC239}" ) );
    aisUtcAndDateResponseMessageObject1->SetReceivedTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisUtcAndDateResponseMessageObject1->SetMessageSequenceNumber( 7675641266328388508LL );
    aisUtcAndDateResponseMessageObject1->SetRepeat( 2127905692L );
    aisUtcAndDateResponseMessageObject1->SetMmsi( Guid( L"{7ED5439C-5B10-6A85-56A1-DA087EABC239}" ) );
    aisUtcAndDateResponseMessageObject1->SetDatetime( DateTime( 1, 1, 1, 22, 23, 35 ) );
    aisUtcAndDateResponseMessageObject1->SetPositionAccuracy( PositionAccuracy::Low );
    aisUtcAndDateResponseMessageObject1->SetLongitude( 7675641266328389 );
    aisUtcAndDateResponseMessageObject1->SetLatitude( 7675641266328389 );
    aisUtcAndDateResponseMessageObject1->SetPositionFixType( PositionFixType::Galileo );
    aisUtcAndDateResponseMessageObject1->SetSpare( 2127905692L );
    aisUtcAndDateResponseMessageObject1->SetRaim( Raim::NotInUse );
    aisUtcAndDateResponseMessageObject1->SetRadioStatus( 2127905692L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisUtcAndDateResponseMessageObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisUtcAndDateResponseMessageObject2 = std::reinterpret_pointer_cast<AisUtcAndDateResponseMessageObject>( ReadDataFrom( source ) );
    bool equal = aisUtcAndDateResponseMessageObject2->IsEqualTo( *aisUtcAndDateResponseMessageObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AlarmStateChangeObjectSerializationTest
BOOST_AUTO_TEST_CASE( AlarmStateChangeObjectSerializationTest )
{
    auto alarmStateChangeObject1 = std::make_shared<AlarmStateChangeObject>( );
    alarmStateChangeObject1->SetId( Guid( L"{86072ECE-CF2F-0DB4-B02D-F3F461E07473}" ) );
    alarmStateChangeObject1->SetRowVersion( 987642021320011470LL );
    alarmStateChangeObject1->SetAlarm( Guid( L"{86072ECE-CF2F-0DB4-B02D-F3F461E07473}" ) );
    alarmStateChangeObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    alarmStateChangeObject1->SetState( AlarmState::Cleared );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *alarmStateChangeObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto alarmStateChangeObject2 = std::reinterpret_pointer_cast<AlarmStateChangeObject>( ReadDataFrom( source ) );
    bool equal = alarmStateChangeObject2->IsEqualTo( *alarmStateChangeObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BaseStationTypeObjectSerializationTest
BOOST_AUTO_TEST_CASE( BaseStationTypeObjectSerializationTest )
{
    auto baseStationTypeObject1 = std::make_shared<BaseStationTypeObject>( );
    baseStationTypeObject1->SetId( Guid( L"{E461D07A-F7B7-0F84-F021-EFED27860B5E}" ) );
    baseStationTypeObject1->SetRowVersion( 1118290976677417082LL );
    baseStationTypeObject1->SetName( L"Name" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *baseStationTypeObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto baseStationTypeObject2 = std::reinterpret_pointer_cast<BaseStationTypeObject>( ReadDataFrom( source ) );
    bool equal = baseStationTypeObject2->IsEqualTo( *baseStationTypeObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BinaryTimeseriesValueObjectSerializationTest
BOOST_AUTO_TEST_CASE( BinaryTimeseriesValueObjectSerializationTest )
{
    auto binaryTimeseriesValueObject1 = std::make_shared<BinaryTimeseriesValueObject>( );
    binaryTimeseriesValueObject1->SetId( Guid( L"{592D1EA9-0849-9318-C918-10929AB47895}" ) );
    binaryTimeseriesValueObject1->SetRowVersion( -7847513239571325271LL );
    binaryTimeseriesValueObject1->SetTimeseries( Guid( L"{592D1EA9-0849-9318-C918-10929AB47895}" ) );
    binaryTimeseriesValueObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    binaryTimeseriesValueObject1->SetValue( { {'V','a','l','u','e'} } );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *binaryTimeseriesValueObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto binaryTimeseriesValueObject2 = std::reinterpret_pointer_cast<BinaryTimeseriesValueObject>( ReadDataFrom( source ) );
    bool equal = binaryTimeseriesValueObject2->IsEqualTo( *binaryTimeseriesValueObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BookmarkObjectSerializationTest
BOOST_AUTO_TEST_CASE( BookmarkObjectSerializationTest )
{
    auto bookmarkObject1 = std::make_shared<BookmarkObject>( );
    bookmarkObject1->SetId( Guid( L"{652F1D55-1FDD-E0C0-0703-F8BBA6F4B8AA}" ) );
    bookmarkObject1->SetRowVersion( -2251764777939428011LL );
    bookmarkObject1->SetView( Guid( L"{652F1D55-1FDD-E0C0-0703-F8BBA6F4B8AA}" ) );
    bookmarkObject1->SetName( L"Name" );
    bookmarkObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    bookmarkObject1->SetLatitude( 16194979295770124 );
    bookmarkObject1->SetLongitude( 16194979295770124 );
    bookmarkObject1->SetZoomLevel( 16194979295770124 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *bookmarkObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto bookmarkObject2 = std::reinterpret_pointer_cast<BookmarkObject>( ReadDataFrom( source ) );
    bool equal = bookmarkObject2->IsEqualTo( *bookmarkObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BooleanTimeseriesValueObjectSerializationTest
BOOST_AUTO_TEST_CASE( BooleanTimeseriesValueObjectSerializationTest )
{
    auto booleanTimeseriesValueObject1 = std::make_shared<BooleanTimeseriesValueObject>( );
    booleanTimeseriesValueObject1->SetId( Guid( L"{F3919E41-40E5-BAB5-5DAD-02A7CF897982}" ) );
    booleanTimeseriesValueObject1->SetRowVersion( -4993013255492231615LL );
    booleanTimeseriesValueObject1->SetTimeseries( Guid( L"{F3919E41-40E5-BAB5-5DAD-02A7CF897982}" ) );
    booleanTimeseriesValueObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    booleanTimeseriesValueObject1->SetValue( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *booleanTimeseriesValueObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto booleanTimeseriesValueObject2 = std::reinterpret_pointer_cast<BooleanTimeseriesValueObject>( ReadDataFrom( source ) );
    bool equal = booleanTimeseriesValueObject2->IsEqualTo( *booleanTimeseriesValueObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ByteTimeseriesValueObjectSerializationTest
BOOST_AUTO_TEST_CASE( ByteTimeseriesValueObjectSerializationTest )
{
    auto byteTimeseriesValueObject1 = std::make_shared<ByteTimeseriesValueObject>( );
    byteTimeseriesValueObject1->SetId( Guid( L"{E106F150-2900-1D63-B8C6-940087608F0A}" ) );
    byteTimeseriesValueObject1->SetRowVersion( 2117581333546332496LL );
    byteTimeseriesValueObject1->SetTimeseries( Guid( L"{E106F150-2900-1D63-B8C6-940087608F0A}" ) );
    byteTimeseriesValueObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    byteTimeseriesValueObject1->SetValue( 80 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *byteTimeseriesValueObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto byteTimeseriesValueObject2 = std::reinterpret_pointer_cast<ByteTimeseriesValueObject>( ReadDataFrom( source ) );
    bool equal = byteTimeseriesValueObject2->IsEqualTo( *byteTimeseriesValueObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandObjectSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandObjectSerializationTest )
{
    auto cameraCommandObject1 = std::make_shared<CameraCommandObject>( );
    cameraCommandObject1->SetId( Guid( L"{664197EB-56C6-2117-84E8-6A636682E9D7}" ) );
    cameraCommandObject1->SetRowVersion( 2384469937835055083LL );
    cameraCommandObject1->SetCamera( Guid( L"{664197EB-56C6-2117-84E8-6A636682E9D7}" ) );
    cameraCommandObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    cameraCommandObject1->SetDeviceCommandSourceType( DeviceCommandSourceType::Source );
    cameraCommandObject1->SetDeviceCommandSourceId( Guid( L"{664197EB-56C6-2117-84E8-6A636682E9D7}" ) );
    cameraCommandObject1->SetReply( Guid( L"{664197EB-56C6-2117-84E8-6A636682E9D7}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandObject2 = std::reinterpret_pointer_cast<CameraCommandObject>( ReadDataFrom( source ) );
    bool equal = cameraCommandObject2->IsEqualTo( *cameraCommandObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandAbsoluteMoveObjectSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandAbsoluteMoveObjectSerializationTest )
{
    auto cameraCommandAbsoluteMoveObject1 = std::make_shared<CameraCommandAbsoluteMoveObject>( );
    cameraCommandAbsoluteMoveObject1->SetId( Guid( L"{B0F47B16-0F88-634E-C672-F0110D2FDE68}" ) );
    cameraCommandAbsoluteMoveObject1->SetRowVersion( 7155673937697078038LL );
    cameraCommandAbsoluteMoveObject1->SetCamera( Guid( L"{B0F47B16-0F88-634E-C672-F0110D2FDE68}" ) );
    cameraCommandAbsoluteMoveObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    cameraCommandAbsoluteMoveObject1->SetDeviceCommandSourceType( DeviceCommandSourceType::Device );
    cameraCommandAbsoluteMoveObject1->SetDeviceCommandSourceId( Guid( L"{B0F47B16-0F88-634E-C672-F0110D2FDE68}" ) );
    cameraCommandAbsoluteMoveObject1->SetReply( Guid( L"{B0F47B16-0F88-634E-C672-F0110D2FDE68}" ) );
    cameraCommandAbsoluteMoveObject1->SetPositionPanTiltMode( CameraPanTiltMode::Angular );
    cameraCommandAbsoluteMoveObject1->SetPanAngle( 7155673937697078 );
    cameraCommandAbsoluteMoveObject1->SetTiltAngle( 7155673937697078 );
    cameraCommandAbsoluteMoveObject1->SetPositionFocalLengthMode( CameraFocalLengthMode::Millimeter );
    cameraCommandAbsoluteMoveObject1->SetFocalLength( 7155673937697078 );
    cameraCommandAbsoluteMoveObject1->SetSpeedPanTiltMode( CameraPanTiltMode::Angular );
    cameraCommandAbsoluteMoveObject1->SetPanSpeed( 7155673937697078 );
    cameraCommandAbsoluteMoveObject1->SetTiltSpeed( 7155673937697078 );
    cameraCommandAbsoluteMoveObject1->SetSpeedFocalLengthMode( CameraFocalLengthMode::Millimeter );
    cameraCommandAbsoluteMoveObject1->SetZoomSpeed( 7155673937697078 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandAbsoluteMoveObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandAbsoluteMoveObject2 = std::reinterpret_pointer_cast<CameraCommandAbsoluteMoveObject>( ReadDataFrom( source ) );
    bool equal = cameraCommandAbsoluteMoveObject2->IsEqualTo( *cameraCommandAbsoluteMoveObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandAdjustPanTiltZoomObjectSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandAdjustPanTiltZoomObjectSerializationTest )
{
    auto cameraCommandAdjustPanTiltZoomObject1 = std::make_shared<CameraCommandAdjustPanTiltZoomObject>( );
    cameraCommandAdjustPanTiltZoomObject1->SetId( Guid( L"{C14A2079-48BB-058C-A031-12DD8352049E}" ) );
    cameraCommandAdjustPanTiltZoomObject1->SetRowVersion( 399774438168076409LL );
    cameraCommandAdjustPanTiltZoomObject1->SetCamera( Guid( L"{C14A2079-48BB-058C-A031-12DD8352049E}" ) );
    cameraCommandAdjustPanTiltZoomObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    cameraCommandAdjustPanTiltZoomObject1->SetDeviceCommandSourceType( DeviceCommandSourceType::Session );
    cameraCommandAdjustPanTiltZoomObject1->SetDeviceCommandSourceId( Guid( L"{C14A2079-48BB-058C-A031-12DD8352049E}" ) );
    cameraCommandAdjustPanTiltZoomObject1->SetReply( Guid( L"{C14A2079-48BB-058C-A031-12DD8352049E}" ) );
    cameraCommandAdjustPanTiltZoomObject1->SetX( 399774438168076.44 );
    cameraCommandAdjustPanTiltZoomObject1->SetY( 399774438168076.44 );
    cameraCommandAdjustPanTiltZoomObject1->SetZ( 399774438168076.44 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandAdjustPanTiltZoomObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandAdjustPanTiltZoomObject2 = std::reinterpret_pointer_cast<CameraCommandAdjustPanTiltZoomObject>( ReadDataFrom( source ) );
    bool equal = cameraCommandAdjustPanTiltZoomObject2->IsEqualTo( *cameraCommandAdjustPanTiltZoomObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandContinuousMoveObjectSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandContinuousMoveObjectSerializationTest )
{
    auto cameraCommandContinuousMoveObject1 = std::make_shared<CameraCommandContinuousMoveObject>( );
    cameraCommandContinuousMoveObject1->SetId( Guid( L"{2DCEB552-500C-9183-89C1-0A30B473AD4A}" ) );
    cameraCommandContinuousMoveObject1->SetRowVersion( -7961431703022553774LL );
    cameraCommandContinuousMoveObject1->SetCamera( Guid( L"{2DCEB552-500C-9183-89C1-0A30B473AD4A}" ) );
    cameraCommandContinuousMoveObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    cameraCommandContinuousMoveObject1->SetDeviceCommandSourceType( DeviceCommandSourceType::Device );
    cameraCommandContinuousMoveObject1->SetDeviceCommandSourceId( Guid( L"{2DCEB552-500C-9183-89C1-0A30B473AD4A}" ) );
    cameraCommandContinuousMoveObject1->SetReply( Guid( L"{2DCEB552-500C-9183-89C1-0A30B473AD4A}" ) );
    cameraCommandContinuousMoveObject1->SetNormalized( false );
    cameraCommandContinuousMoveObject1->SetPanVelocity( 10485312370686998 );
    cameraCommandContinuousMoveObject1->SetTiltVelocity( 10485312370686998 );
    cameraCommandContinuousMoveObject1->SetZoomVelocity( 10485312370686998 );
    cameraCommandContinuousMoveObject1->SetDuration( TimeSpan( -23022553774LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandContinuousMoveObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandContinuousMoveObject2 = std::reinterpret_pointer_cast<CameraCommandContinuousMoveObject>( ReadDataFrom( source ) );
    bool equal = cameraCommandContinuousMoveObject2->IsEqualTo( *cameraCommandContinuousMoveObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandGeoMoveObjectSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandGeoMoveObjectSerializationTest )
{
    auto cameraCommandGeoMoveObject1 = std::make_shared<CameraCommandGeoMoveObject>( );
    cameraCommandGeoMoveObject1->SetId( Guid( L"{A0BB9958-0341-AD24-B524-C08205DD991A}" ) );
    cameraCommandGeoMoveObject1->SetRowVersion( -5970643625582028456LL );
    cameraCommandGeoMoveObject1->SetCamera( Guid( L"{A0BB9958-0341-AD24-B524-C08205DD991A}" ) );
    cameraCommandGeoMoveObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    cameraCommandGeoMoveObject1->SetDeviceCommandSourceType( DeviceCommandSourceType::Unknown );
    cameraCommandGeoMoveObject1->SetDeviceCommandSourceId( Guid( L"{A0BB9958-0341-AD24-B524-C08205DD991A}" ) );
    cameraCommandGeoMoveObject1->SetReply( Guid( L"{A0BB9958-0341-AD24-B524-C08205DD991A}" ) );
    cameraCommandGeoMoveObject1->SetLatitude( 12476100448127522 );
    cameraCommandGeoMoveObject1->SetLongitude( 12476100448127522 );
    cameraCommandGeoMoveObject1->SetAltitude( 12476100448127522 );
    cameraCommandGeoMoveObject1->SetViewportWidth( 12476100448127522 );
    cameraCommandGeoMoveObject1->SetViewportHeight( 12476100448127522 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandGeoMoveObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandGeoMoveObject2 = std::reinterpret_pointer_cast<CameraCommandGeoMoveObject>( ReadDataFrom( source ) );
    bool equal = cameraCommandGeoMoveObject2->IsEqualTo( *cameraCommandGeoMoveObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandRelativeMoveObjectSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandRelativeMoveObjectSerializationTest )
{
    auto cameraCommandRelativeMoveObject1 = std::make_shared<CameraCommandRelativeMoveObject>( );
    cameraCommandRelativeMoveObject1->SetId( Guid( L"{3B1F2501-F679-705C-0E3A-6F9EDCF8A480}" ) );
    cameraCommandRelativeMoveObject1->SetRowVersion( 8096617230648681729LL );
    cameraCommandRelativeMoveObject1->SetCamera( Guid( L"{3B1F2501-F679-705C-0E3A-6F9EDCF8A480}" ) );
    cameraCommandRelativeMoveObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    cameraCommandRelativeMoveObject1->SetDeviceCommandSourceType( DeviceCommandSourceType::Session );
    cameraCommandRelativeMoveObject1->SetDeviceCommandSourceId( Guid( L"{3B1F2501-F679-705C-0E3A-6F9EDCF8A480}" ) );
    cameraCommandRelativeMoveObject1->SetReply( Guid( L"{3B1F2501-F679-705C-0E3A-6F9EDCF8A480}" ) );
    cameraCommandRelativeMoveObject1->SetNormalized( false );
    cameraCommandRelativeMoveObject1->SetPanAngle( 8096617230648681 );
    cameraCommandRelativeMoveObject1->SetTiltAngle( 8096617230648681 );
    cameraCommandRelativeMoveObject1->SetFocalLength( 8096617230648681 );
    cameraCommandRelativeMoveObject1->SetPanSpeed( 8096617230648681 );
    cameraCommandRelativeMoveObject1->SetTiltSpeed( 8096617230648681 );
    cameraCommandRelativeMoveObject1->SetZoomSpeed( 8096617230648681 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandRelativeMoveObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandRelativeMoveObject2 = std::reinterpret_pointer_cast<CameraCommandRelativeMoveObject>( ReadDataFrom( source ) );
    bool equal = cameraCommandRelativeMoveObject2->IsEqualTo( *cameraCommandRelativeMoveObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandReleasePTZOwnershipObjectSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandReleasePTZOwnershipObjectSerializationTest )
{
    auto cameraCommandReleasePTZOwnershipObject1 = std::make_shared<CameraCommandReleasePTZOwnershipObject>( );
    cameraCommandReleasePTZOwnershipObject1->SetId( Guid( L"{9CDA9BB9-4762-635C-C63A-E246395BD99D}" ) );
    cameraCommandReleasePTZOwnershipObject1->SetRowVersion( 7159675996476185529LL );
    cameraCommandReleasePTZOwnershipObject1->SetCamera( Guid( L"{9CDA9BB9-4762-635C-C63A-E246395BD99D}" ) );
    cameraCommandReleasePTZOwnershipObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    cameraCommandReleasePTZOwnershipObject1->SetDeviceCommandSourceType( DeviceCommandSourceType::Session );
    cameraCommandReleasePTZOwnershipObject1->SetDeviceCommandSourceId( Guid( L"{9CDA9BB9-4762-635C-C63A-E246395BD99D}" ) );
    cameraCommandReleasePTZOwnershipObject1->SetReply( Guid( L"{9CDA9BB9-4762-635C-C63A-E246395BD99D}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandReleasePTZOwnershipObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandReleasePTZOwnershipObject2 = std::reinterpret_pointer_cast<CameraCommandReleasePTZOwnershipObject>( ReadDataFrom( source ) );
    bool equal = cameraCommandReleasePTZOwnershipObject2->IsEqualTo( *cameraCommandReleasePTZOwnershipObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandRequestPTZOwnershipObjectSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandRequestPTZOwnershipObjectSerializationTest )
{
    auto cameraCommandRequestPTZOwnershipObject1 = std::make_shared<CameraCommandRequestPTZOwnershipObject>( );
    cameraCommandRequestPTZOwnershipObject1->SetId( Guid( L"{74450B39-1F6C-F5B8-AF1D-F8362EA2D09C}" ) );
    cameraCommandRequestPTZOwnershipObject1->SetRowVersion( -740807588034835655LL );
    cameraCommandRequestPTZOwnershipObject1->SetCamera( Guid( L"{74450B39-1F6C-F5B8-AF1D-F8362EA2D09C}" ) );
    cameraCommandRequestPTZOwnershipObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    cameraCommandRequestPTZOwnershipObject1->SetDeviceCommandSourceType( DeviceCommandSourceType::Session );
    cameraCommandRequestPTZOwnershipObject1->SetDeviceCommandSourceId( Guid( L"{74450B39-1F6C-F5B8-AF1D-F8362EA2D09C}" ) );
    cameraCommandRequestPTZOwnershipObject1->SetReply( Guid( L"{74450B39-1F6C-F5B8-AF1D-F8362EA2D09C}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandRequestPTZOwnershipObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandRequestPTZOwnershipObject2 = std::reinterpret_pointer_cast<CameraCommandRequestPTZOwnershipObject>( ReadDataFrom( source ) );
    bool equal = cameraCommandRequestPTZOwnershipObject2->IsEqualTo( *cameraCommandRequestPTZOwnershipObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandSetAutoFocusObjectSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandSetAutoFocusObjectSerializationTest )
{
    auto cameraCommandSetAutoFocusObject1 = std::make_shared<CameraCommandSetAutoFocusObject>( );
    cameraCommandSetAutoFocusObject1->SetId( Guid( L"{BFA69A70-BA7F-4100-8200-5DFEFD65590E}" ) );
    cameraCommandSetAutoFocusObject1->SetRowVersion( 4683948670304295536LL );
    cameraCommandSetAutoFocusObject1->SetCamera( Guid( L"{BFA69A70-BA7F-4100-8200-5DFEFD65590E}" ) );
    cameraCommandSetAutoFocusObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    cameraCommandSetAutoFocusObject1->SetDeviceCommandSourceType( DeviceCommandSourceType::Unknown );
    cameraCommandSetAutoFocusObject1->SetDeviceCommandSourceId( Guid( L"{BFA69A70-BA7F-4100-8200-5DFEFD65590E}" ) );
    cameraCommandSetAutoFocusObject1->SetReply( Guid( L"{BFA69A70-BA7F-4100-8200-5DFEFD65590E}" ) );
    cameraCommandSetAutoFocusObject1->SetEnabled( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandSetAutoFocusObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandSetAutoFocusObject2 = std::reinterpret_pointer_cast<CameraCommandSetAutoFocusObject>( ReadDataFrom( source ) );
    bool equal = cameraCommandSetAutoFocusObject2->IsEqualTo( *cameraCommandSetAutoFocusObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandSetBlackAndWhiteObjectSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandSetBlackAndWhiteObjectSerializationTest )
{
    auto cameraCommandSetBlackAndWhiteObject1 = std::make_shared<CameraCommandSetBlackAndWhiteObject>( );
    cameraCommandSetBlackAndWhiteObject1->SetId( Guid( L"{9B072A4D-7597-5B04-DA20-AEE9D9E054B2}" ) );
    cameraCommandSetBlackAndWhiteObject1->SetRowVersion( 6558496251359734349LL );
    cameraCommandSetBlackAndWhiteObject1->SetCamera( Guid( L"{9B072A4D-7597-5B04-DA20-AEE9D9E054B2}" ) );
    cameraCommandSetBlackAndWhiteObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    cameraCommandSetBlackAndWhiteObject1->SetDeviceCommandSourceType( DeviceCommandSourceType::Session );
    cameraCommandSetBlackAndWhiteObject1->SetDeviceCommandSourceId( Guid( L"{9B072A4D-7597-5B04-DA20-AEE9D9E054B2}" ) );
    cameraCommandSetBlackAndWhiteObject1->SetReply( Guid( L"{9B072A4D-7597-5B04-DA20-AEE9D9E054B2}" ) );
    cameraCommandSetBlackAndWhiteObject1->SetEnabled( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandSetBlackAndWhiteObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandSetBlackAndWhiteObject2 = std::reinterpret_pointer_cast<CameraCommandSetBlackAndWhiteObject>( ReadDataFrom( source ) );
    bool equal = cameraCommandSetBlackAndWhiteObject2->IsEqualTo( *cameraCommandSetBlackAndWhiteObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandSetFollowedObjectSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandSetFollowedObjectSerializationTest )
{
    auto cameraCommandSetFollowedObject1 = std::make_shared<CameraCommandSetFollowedObject>( );
    cameraCommandSetFollowedObject1->SetId( Guid( L"{B9DD5ECF-09D5-3BA0-DC05-90AB9DBB7AF3}" ) );
    cameraCommandSetFollowedObject1->SetRowVersion( 4296444858062429903LL );
    cameraCommandSetFollowedObject1->SetCamera( Guid( L"{B9DD5ECF-09D5-3BA0-DC05-90AB9DBB7AF3}" ) );
    cameraCommandSetFollowedObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    cameraCommandSetFollowedObject1->SetDeviceCommandSourceType( DeviceCommandSourceType::Source );
    cameraCommandSetFollowedObject1->SetDeviceCommandSourceId( Guid( L"{B9DD5ECF-09D5-3BA0-DC05-90AB9DBB7AF3}" ) );
    cameraCommandSetFollowedObject1->SetReply( Guid( L"{B9DD5ECF-09D5-3BA0-DC05-90AB9DBB7AF3}" ) );
    cameraCommandSetFollowedObject1->SetTrackId( Guid( L"{B9DD5ECF-09D5-3BA0-DC05-90AB9DBB7AF3}" ) );
    cameraCommandSetFollowedObject1->SetReason( CameraFollowReason::User );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandSetFollowedObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandSetFollowedObject2 = std::reinterpret_pointer_cast<CameraCommandSetFollowedObject>( ReadDataFrom( source ) );
    bool equal = cameraCommandSetFollowedObject2->IsEqualTo( *cameraCommandSetFollowedObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandSetInfraRedLampObjectSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandSetInfraRedLampObjectSerializationTest )
{
    auto cameraCommandSetInfraRedLampObject1 = std::make_shared<CameraCommandSetInfraRedLampObject>( );
    cameraCommandSetInfraRedLampObject1->SetId( Guid( L"{4F4F05AD-B0D5-2BD2-D44B-0DABF2F2A0B5}" ) );
    cameraCommandSetInfraRedLampObject1->SetRowVersion( 3157780718945240493LL );
    cameraCommandSetInfraRedLampObject1->SetCamera( Guid( L"{4F4F05AD-B0D5-2BD2-D44B-0DABF2F2A0B5}" ) );
    cameraCommandSetInfraRedLampObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    cameraCommandSetInfraRedLampObject1->SetDeviceCommandSourceType( DeviceCommandSourceType::Session );
    cameraCommandSetInfraRedLampObject1->SetDeviceCommandSourceId( Guid( L"{4F4F05AD-B0D5-2BD2-D44B-0DABF2F2A0B5}" ) );
    cameraCommandSetInfraRedLampObject1->SetReply( Guid( L"{4F4F05AD-B0D5-2BD2-D44B-0DABF2F2A0B5}" ) );
    cameraCommandSetInfraRedLampObject1->SetEnabled( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandSetInfraRedLampObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandSetInfraRedLampObject2 = std::reinterpret_pointer_cast<CameraCommandSetInfraRedLampObject>( ReadDataFrom( source ) );
    bool equal = cameraCommandSetInfraRedLampObject2->IsEqualTo( *cameraCommandSetInfraRedLampObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandSetWasherObjectSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandSetWasherObjectSerializationTest )
{
    auto cameraCommandSetWasherObject1 = std::make_shared<CameraCommandSetWasherObject>( );
    cameraCommandSetWasherObject1->SetId( Guid( L"{CD63FFAD-F1AD-8424-2124-8FB5B3C6FFB5}" ) );
    cameraCommandSetWasherObject1->SetRowVersion( -8924742832763961427LL );
    cameraCommandSetWasherObject1->SetCamera( Guid( L"{CD63FFAD-F1AD-8424-2124-8FB5B3C6FFB5}" ) );
    cameraCommandSetWasherObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    cameraCommandSetWasherObject1->SetDeviceCommandSourceType( DeviceCommandSourceType::Session );
    cameraCommandSetWasherObject1->SetDeviceCommandSourceId( Guid( L"{CD63FFAD-F1AD-8424-2124-8FB5B3C6FFB5}" ) );
    cameraCommandSetWasherObject1->SetReply( Guid( L"{CD63FFAD-F1AD-8424-2124-8FB5B3C6FFB5}" ) );
    cameraCommandSetWasherObject1->SetEnabled( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandSetWasherObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandSetWasherObject2 = std::reinterpret_pointer_cast<CameraCommandSetWasherObject>( ReadDataFrom( source ) );
    bool equal = cameraCommandSetWasherObject2->IsEqualTo( *cameraCommandSetWasherObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandSetWiperObjectSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandSetWiperObjectSerializationTest )
{
    auto cameraCommandSetWiperObject1 = std::make_shared<CameraCommandSetWiperObject>( );
    cameraCommandSetWiperObject1->SetId( Guid( L"{059133CC-5F0A-B478-2D1E-FA50A089CC33}" ) );
    cameraCommandSetWiperObject1->SetRowVersion( -5442495653029530676LL );
    cameraCommandSetWiperObject1->SetCamera( Guid( L"{059133CC-5F0A-B478-2D1E-FA50A089CC33}" ) );
    cameraCommandSetWiperObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    cameraCommandSetWiperObject1->SetDeviceCommandSourceType( DeviceCommandSourceType::Unknown );
    cameraCommandSetWiperObject1->SetDeviceCommandSourceId( Guid( L"{059133CC-5F0A-B478-2D1E-FA50A089CC33}" ) );
    cameraCommandSetWiperObject1->SetReply( Guid( L"{059133CC-5F0A-B478-2D1E-FA50A089CC33}" ) );
    cameraCommandSetWiperObject1->SetEnabled( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandSetWiperObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandSetWiperObject2 = std::reinterpret_pointer_cast<CameraCommandSetWiperObject>( ReadDataFrom( source ) );
    bool equal = cameraCommandSetWiperObject2->IsEqualTo( *cameraCommandSetWiperObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandStopObjectSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandStopObjectSerializationTest )
{
    auto cameraCommandStopObject1 = std::make_shared<CameraCommandStopObject>( );
    cameraCommandStopObject1->SetId( Guid( L"{F2E01750-4663-2D0A-B450-62C64F07E80A}" ) );
    cameraCommandStopObject1->SetRowVersion( 3245483876564342608LL );
    cameraCommandStopObject1->SetCamera( Guid( L"{F2E01750-4663-2D0A-B450-62C64F07E80A}" ) );
    cameraCommandStopObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    cameraCommandStopObject1->SetDeviceCommandSourceType( DeviceCommandSourceType::Unknown );
    cameraCommandStopObject1->SetDeviceCommandSourceId( Guid( L"{F2E01750-4663-2D0A-B450-62C64F07E80A}" ) );
    cameraCommandStopObject1->SetReply( Guid( L"{F2E01750-4663-2D0A-B450-62C64F07E80A}" ) );
    cameraCommandStopObject1->SetPanTilt( false );
    cameraCommandStopObject1->SetZoom( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandStopObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandStopObject2 = std::reinterpret_pointer_cast<CameraCommandStopObject>( ReadDataFrom( source ) );
    bool equal = cameraCommandStopObject2->IsEqualTo( *cameraCommandStopObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandReplyObjectSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandReplyObjectSerializationTest )
{
    auto cameraCommandReplyObject1 = std::make_shared<CameraCommandReplyObject>( );
    cameraCommandReplyObject1->SetId( Guid( L"{26FFBA0F-E13C-F85B-1FDA-873C64FF5DF0}" ) );
    cameraCommandReplyObject1->SetRowVersion( -550598880954172913LL );
    cameraCommandReplyObject1->SetCamera( Guid( L"{26FFBA0F-E13C-F85B-1FDA-873C64FF5DF0}" ) );
    cameraCommandReplyObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    cameraCommandReplyObject1->SetCommand( Guid( L"{26FFBA0F-E13C-F85B-1FDA-873C64FF5DF0}" ) );
    cameraCommandReplyObject1->SetStatus( DeviceCommandReplyStatus::Error );
    cameraCommandReplyObject1->SetMessage( L"Message" );
    cameraCommandReplyObject1->SetPanAngle( 17896145192755378 );
    cameraCommandReplyObject1->SetTiltAngle( 17896145192755378 );
    cameraCommandReplyObject1->SetFocalLength( 17896145192755378 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandReplyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandReplyObject2 = std::reinterpret_pointer_cast<CameraCommandReplyObject>( ReadDataFrom( source ) );
    bool equal = cameraCommandReplyObject2->IsEqualTo( *cameraCommandReplyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraConfigurationObjectSerializationTest
BOOST_AUTO_TEST_CASE( CameraConfigurationObjectSerializationTest )
{
    auto cameraConfigurationObject1 = std::make_shared<CameraConfigurationObject>( );
    cameraConfigurationObject1->SetId( Guid( L"{328264BE-F096-6BC6-D663-0F694C41267D}" ) );
    cameraConfigurationObject1->SetRowVersion( 7766159135330165950LL );
    cameraConfigurationObject1->SetCamera( Guid( L"{328264BE-F096-6BC6-D663-0F694C41267D}" ) );
    cameraConfigurationObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    cameraConfigurationObject1->SetCameraControlProtocol( CameraControlProtocol::Unknown );
    cameraConfigurationObject1->SetCameraURL( L"CameraURL" );
    cameraConfigurationObject1->SetConfigurationURL( L"ConfigurationURL" );
    cameraConfigurationObject1->SetUserName( L"UserName" );
    cameraConfigurationObject1->SetPassword( L"Password" );
    cameraConfigurationObject1->SetUseRtspUriOverride( false );
    cameraConfigurationObject1->SetRtspUriOverride( L"RtspUriOverride" );
    cameraConfigurationObject1->SetLatitude( 7766159135330166 );
    cameraConfigurationObject1->SetLongitude( 7766159135330166 );
    cameraConfigurationObject1->SetAltitude( 7766159135330166 );
    cameraConfigurationObject1->SetUseRelativePosition( false );
    cameraConfigurationObject1->SetPanTiltMode( CameraPanTiltMode::Normalized );
    cameraConfigurationObject1->SetMinTiltAngle( 7766159135330166 );
    cameraConfigurationObject1->SetMaxTiltAngle( 7766159135330166 );
    cameraConfigurationObject1->SetMinTiltScaleAngle( 7766159135330166 );
    cameraConfigurationObject1->SetMaxTiltScaleAngle( 7766159135330166 );
    cameraConfigurationObject1->SetUseReverseTiltAngle( false );
    cameraConfigurationObject1->SetUseReverseNormalizedTiltAngle( false );
    cameraConfigurationObject1->SetMinTiltVelocity( 7766159135330166 );
    cameraConfigurationObject1->SetMaxTiltVelocity( 7766159135330166 );
    cameraConfigurationObject1->SetMinTiltSpeed( 7766159135330166 );
    cameraConfigurationObject1->SetMaxTiltSpeed( 7766159135330166 );
    cameraConfigurationObject1->SetMinPanAngle( 7766159135330166 );
    cameraConfigurationObject1->SetMaxPanAngle( 7766159135330166 );
    cameraConfigurationObject1->SetMinPanScaleAngle( 7766159135330166 );
    cameraConfigurationObject1->SetMaxPanScaleAngle( 7766159135330166 );
    cameraConfigurationObject1->SetUseReversePanAngle( false );
    cameraConfigurationObject1->SetUseReverseNormalizedPanAngle( false );
    cameraConfigurationObject1->SetMinPanVelocity( 7766159135330166 );
    cameraConfigurationObject1->SetMaxPanVelocity( 7766159135330166 );
    cameraConfigurationObject1->SetMinPanSpeed( 7766159135330166 );
    cameraConfigurationObject1->SetMaxPanSpeed( 7766159135330166 );
    cameraConfigurationObject1->SetFocalLengthMode( CameraFocalLengthMode::Normalized );
    cameraConfigurationObject1->SetMinFocalLength( 7766159135330166 );
    cameraConfigurationObject1->SetMaxFocalLength( 7766159135330166 );
    cameraConfigurationObject1->SetMinFocalLengthScale( 7766159135330166 );
    cameraConfigurationObject1->SetMaxFocalLengthScale( 7766159135330166 );
    cameraConfigurationObject1->SetMinZoomVelocity( 7766159135330166 );
    cameraConfigurationObject1->SetMaxZoomVelocity( 7766159135330166 );
    cameraConfigurationObject1->SetMinZoomSpeed( 7766159135330166 );
    cameraConfigurationObject1->SetMaxZoomSpeed( 7766159135330166 );
    cameraConfigurationObject1->SetImageSensorWidth( 7766159135330166 );
    cameraConfigurationObject1->SetImageSensorHeight( 7766159135330166 );
    cameraConfigurationObject1->SetHomePanAngle( 7766159135330166 );
    cameraConfigurationObject1->SetHomeTiltAngle( 7766159135330166 );
    cameraConfigurationObject1->SetHomeFocalLength( 7766159135330166 );
    cameraConfigurationObject1->SetPanOffset( 7766159135330166 );
    cameraConfigurationObject1->SetTiltOffset( 7766159135330166 );
    cameraConfigurationObject1->SetAimAltitude( 7766159135330166 );
    cameraConfigurationObject1->SetMinimumTargetWidth( 7766159135330166 );
    cameraConfigurationObject1->SetTargetLockTimeout( TimeSpan( 95330165950LL ) );
    cameraConfigurationObject1->SetUpdateStatusInterval( TimeSpan( 95330165950LL ) );
    cameraConfigurationObject1->SetReadTimeout( TimeSpan( 95330165950LL ) );
    cameraConfigurationObject1->SetMoveCommandStatusDelay( TimeSpan( 95330165950LL ) );
    cameraConfigurationObject1->SetPtzProfileName( L"PtzProfileName" );
    cameraConfigurationObject1->SetPtzConfigurationToken( L"PtzConfigurationToken" );
    cameraConfigurationObject1->SetVideoSourceToken( L"VideoSourceToken" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraConfigurationObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraConfigurationObject2 = std::reinterpret_pointer_cast<CameraConfigurationObject>( ReadDataFrom( source ) );
    bool equal = cameraConfigurationObject2->IsEqualTo( *cameraConfigurationObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraPanCalibrationObjectSerializationTest
BOOST_AUTO_TEST_CASE( CameraPanCalibrationObjectSerializationTest )
{
    auto cameraPanCalibrationObject1 = std::make_shared<CameraPanCalibrationObject>( );
    cameraPanCalibrationObject1->SetId( Guid( L"{938FC103-EA2B-A116-8568-57D4C9F183C0}" ) );
    cameraPanCalibrationObject1->SetRowVersion( -6839021511235354365LL );
    cameraPanCalibrationObject1->SetCamera( Guid( L"{938FC103-EA2B-A116-8568-57D4C9F183C0}" ) );
    cameraPanCalibrationObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraPanCalibrationObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraPanCalibrationObject2 = std::reinterpret_pointer_cast<CameraPanCalibrationObject>( ReadDataFrom( source ) );
    bool equal = cameraPanCalibrationObject2->IsEqualTo( *cameraPanCalibrationObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraPanCalibrationValueObjectSerializationTest
BOOST_AUTO_TEST_CASE( CameraPanCalibrationValueObjectSerializationTest )
{
    auto cameraPanCalibrationValueObject1 = std::make_shared<CameraPanCalibrationValueObject>( );
    cameraPanCalibrationValueObject1->SetId( Guid( L"{CE6BFE19-A13B-4144-8222-85DC73D67F98}" ) );
    cameraPanCalibrationValueObject1->SetRowVersion( 4703061189119966745LL );
    cameraPanCalibrationValueObject1->SetPanCalibration( Guid( L"{CE6BFE19-A13B-4144-8222-85DC73D67F98}" ) );
    cameraPanCalibrationValueObject1->SetPanAngle( 4703061189119967 );
    cameraPanCalibrationValueObject1->SetPanOffset( 4703061189119967 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraPanCalibrationValueObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraPanCalibrationValueObject2 = std::reinterpret_pointer_cast<CameraPanCalibrationValueObject>( ReadDataFrom( source ) );
    bool equal = cameraPanCalibrationValueObject2->IsEqualTo( *cameraPanCalibrationValueObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraStatusObjectSerializationTest
BOOST_AUTO_TEST_CASE( CameraStatusObjectSerializationTest )
{
    auto cameraStatusObject1 = std::make_shared<CameraStatusObject>( );
    cameraStatusObject1->SetId( Guid( L"{3632442A-D4AE-2066-0466-2B756C4C2254}" ) );
    cameraStatusObject1->SetRowVersion( 2334787301536842794LL );
    cameraStatusObject1->SetCamera( Guid( L"{3632442A-D4AE-2066-0466-2B756C4C2254}" ) );
    cameraStatusObject1->SetTrack( Guid( L"{3632442A-D4AE-2066-0466-2B756C4C2254}" ) );
    cameraStatusObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    cameraStatusObject1->SetPositionPanTiltMode( CameraPanTiltMode::Angular );
    cameraStatusObject1->SetPanAngle( 2334787301536843 );
    cameraStatusObject1->SetTiltAngle( 2334787301536843 );
    cameraStatusObject1->SetPositionFocalLengthMode( CameraFocalLengthMode::Millimeter );
    cameraStatusObject1->SetFocalLength( 2334787301536843 );
    cameraStatusObject1->SetPanTiltMoveStatus( CameraMoveStatus::Moving );
    cameraStatusObject1->SetZoomMoveStatus( CameraMoveStatus::Moving );
    cameraStatusObject1->SetVelocityPanTiltMode( CameraPanTiltMode::Angular );
    cameraStatusObject1->SetPanVelocity( 2334787301536843 );
    cameraStatusObject1->SetTiltVelocity( 2334787301536843 );
    cameraStatusObject1->SetVelocityFocalLengthMode( CameraFocalLengthMode::Millimeter );
    cameraStatusObject1->SetZoomVelocity( 2334787301536843 );
    cameraStatusObject1->SetActiveFeatures( CameraFeatures::Washer );
    cameraStatusObject1->SetError( L"Error" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraStatusObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraStatusObject2 = std::reinterpret_pointer_cast<CameraStatusObject>( ReadDataFrom( source ) );
    bool equal = cameraStatusObject2->IsEqualTo( *cameraStatusObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraTiltCalibrationObjectSerializationTest
BOOST_AUTO_TEST_CASE( CameraTiltCalibrationObjectSerializationTest )
{
    auto cameraTiltCalibrationObject1 = std::make_shared<CameraTiltCalibrationObject>( );
    cameraTiltCalibrationObject1->SetId( Guid( L"{801E423D-6D9D-ABFC-D53F-B6B9017842BC}" ) );
    cameraTiltCalibrationObject1->SetRowVersion( -6053843275866029507LL );
    cameraTiltCalibrationObject1->SetCamera( Guid( L"{801E423D-6D9D-ABFC-D53F-B6B9017842BC}" ) );
    cameraTiltCalibrationObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraTiltCalibrationObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraTiltCalibrationObject2 = std::reinterpret_pointer_cast<CameraTiltCalibrationObject>( ReadDataFrom( source ) );
    bool equal = cameraTiltCalibrationObject2->IsEqualTo( *cameraTiltCalibrationObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraTiltCalibrationValueObjectSerializationTest
BOOST_AUTO_TEST_CASE( CameraTiltCalibrationValueObjectSerializationTest )
{
    auto cameraTiltCalibrationValueObject1 = std::make_shared<CameraTiltCalibrationValueObject>( );
    cameraTiltCalibrationValueObject1->SetId( Guid( L"{095879C0-8CCC-3747-ECE2-3133901A9E03}" ) );
    cameraTiltCalibrationValueObject1->SetRowVersion( 3983307203390503360LL );
    cameraTiltCalibrationValueObject1->SetTiltCalibration( Guid( L"{095879C0-8CCC-3747-ECE2-3133901A9E03}" ) );
    cameraTiltCalibrationValueObject1->SetPanAngle( 3983307203390503.5 );
    cameraTiltCalibrationValueObject1->SetTiltOffset( 3983307203390503.5 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraTiltCalibrationValueObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraTiltCalibrationValueObject2 = std::reinterpret_pointer_cast<CameraTiltCalibrationValueObject>( ReadDataFrom( source ) );
    bool equal = cameraTiltCalibrationValueObject2->IsEqualTo( *cameraTiltCalibrationValueObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraZoomCalibrationObjectSerializationTest
BOOST_AUTO_TEST_CASE( CameraZoomCalibrationObjectSerializationTest )
{
    auto cameraZoomCalibrationObject1 = std::make_shared<CameraZoomCalibrationObject>( );
    cameraZoomCalibrationObject1->SetId( Guid( L"{E6245A05-1E69-4CFC-323F-789667245AA0}" ) );
    cameraZoomCalibrationObject1->SetRowVersion( 5547342281195149829LL );
    cameraZoomCalibrationObject1->SetCamera( Guid( L"{E6245A05-1E69-4CFC-323F-789667245AA0}" ) );
    cameraZoomCalibrationObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraZoomCalibrationObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraZoomCalibrationObject2 = std::reinterpret_pointer_cast<CameraZoomCalibrationObject>( ReadDataFrom( source ) );
    bool equal = cameraZoomCalibrationObject2->IsEqualTo( *cameraZoomCalibrationObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraZoomCalibrationValueObjectSerializationTest
BOOST_AUTO_TEST_CASE( CameraZoomCalibrationValueObjectSerializationTest )
{
    auto cameraZoomCalibrationValueObject1 = std::make_shared<CameraZoomCalibrationValueObject>( );
    cameraZoomCalibrationValueObject1->SetId( Guid( L"{8F3ECC72-7686-78C6-1E63-6E61F17C334E}" ) );
    cameraZoomCalibrationValueObject1->SetRowVersion( 8702773650241014898LL );
    cameraZoomCalibrationValueObject1->SetZoomCalibration( Guid( L"{8F3ECC72-7686-78C6-1E63-6E61F17C334E}" ) );
    cameraZoomCalibrationValueObject1->SetFocalLength( 8702773650241015 );
    cameraZoomCalibrationValueObject1->SetFocalLengthOffset( 8702773650241015 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraZoomCalibrationValueObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraZoomCalibrationValueObject2 = std::reinterpret_pointer_cast<CameraZoomCalibrationValueObject>( ReadDataFrom( source ) );
    bool equal = cameraZoomCalibrationValueObject2->IsEqualTo( *cameraZoomCalibrationValueObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CatalogObjectSerializationTest
BOOST_AUTO_TEST_CASE( CatalogObjectSerializationTest )
{
    auto catalogObject1 = std::make_shared<CatalogObject>( );
    catalogObject1->SetId( Guid( L"{3F08CFBF-AC44-60BE-067D-3522FC10F3FD}" ) );
    catalogObject1->SetRowVersion( 6971198682331402175LL );
    catalogObject1->SetCatalog( Guid( L"{3F08CFBF-AC44-60BE-067D-3522FC10F3FD}" ) );
    catalogObject1->SetName( L"Name" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *catalogObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto catalogObject2 = std::reinterpret_pointer_cast<CatalogObject>( ReadDataFrom( source ) );
    bool equal = catalogObject2->IsEqualTo( *catalogObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ElementObjectSerializationTest
BOOST_AUTO_TEST_CASE( ElementObjectSerializationTest )
{
    auto elementObject1 = std::make_shared<ElementObject>( );
    elementObject1->SetId( Guid( L"{90C78EFA-4D22-B6DE-6D7B-B24409E3715F}" ) );
    elementObject1->SetRowVersion( -5269689703123677446LL );
    elementObject1->SetCatalog( Guid( L"{90C78EFA-4D22-B6DE-6D7B-B24409E3715F}" ) );
    elementObject1->SetName( L"Name" );
    elementObject1->SetElementType( Guid( L"{90C78EFA-4D22-B6DE-6D7B-B24409E3715F}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *elementObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto elementObject2 = std::reinterpret_pointer_cast<ElementObject>( ReadDataFrom( source ) );
    bool equal = elementObject2->IsEqualTo( *elementObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CollectionInfoObjectSerializationTest
BOOST_AUTO_TEST_CASE( CollectionInfoObjectSerializationTest )
{
    auto collectionInfoObject1 = std::make_shared<CollectionInfoObject>( );
    collectionInfoObject1->SetId( Guid( L"{0335BBA1-A308-DC8F-3BF1-C510C0ACDD85}" ) );
    collectionInfoObject1->SetRowVersion( -2553643208886862943LL );
    collectionInfoObject1->SetCount( -2553643208886862943LL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *collectionInfoObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto collectionInfoObject2 = std::reinterpret_pointer_cast<CollectionInfoObject>( ReadDataFrom( source ) );
    bool equal = collectionInfoObject2->IsEqualTo( *collectionInfoObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CountryObjectSerializationTest
BOOST_AUTO_TEST_CASE( CountryObjectSerializationTest )
{
    auto countryObject1 = std::make_shared<CountryObject>( );
    countryObject1->SetId( Guid( L"{011738F6-F745-C396-C369-EFA280E81C6F}" ) );
    countryObject1->SetRowVersion( -4353020114063902474LL );
    countryObject1->SetName( L"Name" );
    countryObject1->SetCode( 18299126L );
    countryObject1->SetAlpha2( L"Al" );
    countryObject1->SetAlpha3( L"Alp" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *countryObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto countryObject2 = std::reinterpret_pointer_cast<CountryObject>( ReadDataFrom( source ) );
    bool equal = countryObject2->IsEqualTo( *countryObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CursorInfoObjectSerializationTest
BOOST_AUTO_TEST_CASE( CursorInfoObjectSerializationTest )
{
    auto cursorInfoObject1 = std::make_shared<CursorInfoObject>( );
    cursorInfoObject1->SetId( Guid( L"{BFDBAA05-9FB9-E0B1-078D-F99DFDDB55A0}" ) );
    cursorInfoObject1->SetRowVersion( -2255846318199297531LL );
    cursorInfoObject1->SetTypeCode( -1076123131L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cursorInfoObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cursorInfoObject2 = std::reinterpret_pointer_cast<CursorInfoObject>( ReadDataFrom( source ) );
    bool equal = cursorInfoObject2->IsEqualTo( *cursorInfoObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DateTimeTimeseriesValueObjectSerializationTest
BOOST_AUTO_TEST_CASE( DateTimeTimeseriesValueObjectSerializationTest )
{
    auto dateTimeTimeseriesValueObject1 = std::make_shared<DateTimeTimeseriesValueObject>( );
    dateTimeTimeseriesValueObject1->SetId( Guid( L"{4267AABD-DE1A-D545-ABA2-7B5842E655BD}" ) );
    dateTimeTimeseriesValueObject1->SetRowVersion( -3078810565873259843LL );
    dateTimeTimeseriesValueObject1->SetTimeseries( Guid( L"{4267AABD-DE1A-D545-ABA2-7B5842E655BD}" ) );
    dateTimeTimeseriesValueObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    dateTimeTimeseriesValueObject1->SetValue( DateTime( 1, 1, 1, 22, 23, 35 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *dateTimeTimeseriesValueObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto dateTimeTimeseriesValueObject2 = std::reinterpret_pointer_cast<DateTimeTimeseriesValueObject>( ReadDataFrom( source ) );
    bool equal = dateTimeTimeseriesValueObject2->IsEqualTo( *dateTimeTimeseriesValueObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DeviceHostObjectSerializationTest
BOOST_AUTO_TEST_CASE( DeviceHostObjectSerializationTest )
{
    auto deviceHostObject1 = std::make_shared<DeviceHostObject>( );
    deviceHostObject1->SetId( Guid( L"{6CFF9410-05DF-9D07-B9E0-A0FB36FF2908}" ) );
    deviceHostObject1->SetRowVersion( -7131725027753356272LL );
    deviceHostObject1->SetName( L"Name" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *deviceHostObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto deviceHostObject2 = std::reinterpret_pointer_cast<DeviceHostObject>( ReadDataFrom( source ) );
    bool equal = deviceHostObject2->IsEqualTo( *deviceHostObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DeviceHostConfigurationObjectSerializationTest
BOOST_AUTO_TEST_CASE( DeviceHostConfigurationObjectSerializationTest )
{
    auto deviceHostConfigurationObject1 = std::make_shared<DeviceHostConfigurationObject>( );
    deviceHostConfigurationObject1->SetId( Guid( L"{E525AB0B-EC92-D432-2B4C-3749A7A4D5D0}" ) );
    deviceHostConfigurationObject1->SetRowVersion( -3156200273179464949LL );
    deviceHostConfigurationObject1->SetHost( Guid( L"{E525AB0B-EC92-D432-2B4C-3749A7A4D5D0}" ) );
    deviceHostConfigurationObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    deviceHostConfigurationObject1->SetHostname( L"Hostname" );
    deviceHostConfigurationObject1->SetPort( -450516213L );
    deviceHostConfigurationObject1->SetQueueName( L"QueueName" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *deviceHostConfigurationObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto deviceHostConfigurationObject2 = std::reinterpret_pointer_cast<DeviceHostConfigurationObject>( ReadDataFrom( source ) );
    bool equal = deviceHostConfigurationObject2->IsEqualTo( *deviceHostConfigurationObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DoubleTimeseriesValueObjectSerializationTest
BOOST_AUTO_TEST_CASE( DoubleTimeseriesValueObjectSerializationTest )
{
    auto doubleTimeseriesValueObject1 = std::make_shared<DoubleTimeseriesValueObject>( );
    doubleTimeseriesValueObject1->SetId( Guid( L"{C2761332-6A1D-1778-E81E-56B8436EC84C}" ) );
    doubleTimeseriesValueObject1->SetRowVersion( 1691218336126735154LL );
    doubleTimeseriesValueObject1->SetTimeseries( Guid( L"{C2761332-6A1D-1778-E81E-56B8436EC84C}" ) );
    doubleTimeseriesValueObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    doubleTimeseriesValueObject1->SetValue( 1691218336126735 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *doubleTimeseriesValueObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto doubleTimeseriesValueObject2 = std::reinterpret_pointer_cast<DoubleTimeseriesValueObject>( ReadDataFrom( source ) );
    bool equal = doubleTimeseriesValueObject2->IsEqualTo( *doubleTimeseriesValueObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/FacilityTypeObjectSerializationTest
BOOST_AUTO_TEST_CASE( FacilityTypeObjectSerializationTest )
{
    auto facilityTypeObject1 = std::make_shared<FacilityTypeObject>( );
    facilityTypeObject1->SetId( Guid( L"{12C72C65-EDEE-92A1-4985-B77748E334A6}" ) );
    facilityTypeObject1->SetRowVersion( -7880756266148615067LL );
    facilityTypeObject1->SetName( L"Name" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *facilityTypeObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto facilityTypeObject2 = std::reinterpret_pointer_cast<FacilityTypeObject>( ReadDataFrom( source ) );
    bool equal = facilityTypeObject2->IsEqualTo( *facilityTypeObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GeoPosition2DTimeseriesValueObjectSerializationTest
BOOST_AUTO_TEST_CASE( GeoPosition2DTimeseriesValueObjectSerializationTest )
{
    auto geoPosition2DTimeseriesValueObject1 = std::make_shared<GeoPosition2DTimeseriesValueObject>( );
    geoPosition2DTimeseriesValueObject1->SetId( Guid( L"{C715E22D-B55D-0616-6068-ADBAE3A847B4}" ) );
    geoPosition2DTimeseriesValueObject1->SetRowVersion( 438737428091888173LL );
    geoPosition2DTimeseriesValueObject1->SetTimeseries( Guid( L"{C715E22D-B55D-0616-6068-ADBAE3A847B4}" ) );
    geoPosition2DTimeseriesValueObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    geoPosition2DTimeseriesValueObject1->SetLatitude( 438737428091888.2 );
    geoPosition2DTimeseriesValueObject1->SetLongitude( 438737428091888.2 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *geoPosition2DTimeseriesValueObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto geoPosition2DTimeseriesValueObject2 = std::reinterpret_pointer_cast<GeoPosition2DTimeseriesValueObject>( ReadDataFrom( source ) );
    bool equal = geoPosition2DTimeseriesValueObject2->IsEqualTo( *geoPosition2DTimeseriesValueObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GeoPosition3DTimeseriesValueObjectSerializationTest
BOOST_AUTO_TEST_CASE( GeoPosition3DTimeseriesValueObjectSerializationTest )
{
    auto geoPosition3DTimeseriesValueObject1 = std::make_shared<GeoPosition3DTimeseriesValueObject>( );
    geoPosition3DTimeseriesValueObject1->SetId( Guid( L"{9D5BFA33-A3E7-6871-168E-C5E7B9DA5FCC}" ) );
    geoPosition3DTimeseriesValueObject1->SetRowVersion( 7525976667485633075LL );
    geoPosition3DTimeseriesValueObject1->SetTimeseries( Guid( L"{9D5BFA33-A3E7-6871-168E-C5E7B9DA5FCC}" ) );
    geoPosition3DTimeseriesValueObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    geoPosition3DTimeseriesValueObject1->SetLatitude( 7525976667485634 );
    geoPosition3DTimeseriesValueObject1->SetLongitude( 7525976667485634 );
    geoPosition3DTimeseriesValueObject1->SetAltitude( 7525976667485634 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *geoPosition3DTimeseriesValueObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto geoPosition3DTimeseriesValueObject2 = std::reinterpret_pointer_cast<GeoPosition3DTimeseriesValueObject>( ReadDataFrom( source ) );
    bool equal = geoPosition3DTimeseriesValueObject2->IsEqualTo( *geoPosition3DTimeseriesValueObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GNSSDeviceCommandObjectSerializationTest
BOOST_AUTO_TEST_CASE( GNSSDeviceCommandObjectSerializationTest )
{
    auto gNSSDeviceCommandObject1 = std::make_shared<GNSSDeviceCommandObject>( );
    gNSSDeviceCommandObject1->SetId( Guid( L"{16E46657-F2F0-53BB-CADD-4F0F682766EA}" ) );
    gNSSDeviceCommandObject1->SetRowVersion( 6033683238783051351LL );
    gNSSDeviceCommandObject1->SetGNSSDevice( Guid( L"{16E46657-F2F0-53BB-CADD-4F0F682766EA}" ) );
    gNSSDeviceCommandObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    gNSSDeviceCommandObject1->SetDeviceCommandSourceType( DeviceCommandSourceType::Source );
    gNSSDeviceCommandObject1->SetDeviceCommandSourceId( Guid( L"{16E46657-F2F0-53BB-CADD-4F0F682766EA}" ) );
    gNSSDeviceCommandObject1->SetReply( Guid( L"{16E46657-F2F0-53BB-CADD-4F0F682766EA}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gNSSDeviceCommandObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gNSSDeviceCommandObject2 = std::reinterpret_pointer_cast<GNSSDeviceCommandObject>( ReadDataFrom( source ) );
    bool equal = gNSSDeviceCommandObject2->IsEqualTo( *gNSSDeviceCommandObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GNSSDeviceCommandReplyObjectSerializationTest
BOOST_AUTO_TEST_CASE( GNSSDeviceCommandReplyObjectSerializationTest )
{
    auto gNSSDeviceCommandReplyObject1 = std::make_shared<GNSSDeviceCommandReplyObject>( );
    gNSSDeviceCommandReplyObject1->SetId( Guid( L"{351EEA93-C2A0-2E72-744E-4305AC7857C9}" ) );
    gNSSDeviceCommandReplyObject1->SetRowVersion( 3346951466431474323LL );
    gNSSDeviceCommandReplyObject1->SetGNSSDevice( Guid( L"{351EEA93-C2A0-2E72-744E-4305AC7857C9}" ) );
    gNSSDeviceCommandReplyObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    gNSSDeviceCommandReplyObject1->SetCommand( Guid( L"{351EEA93-C2A0-2E72-744E-4305AC7857C9}" ) );
    gNSSDeviceCommandReplyObject1->SetStatus( DeviceCommandReplyStatus::Error );
    gNSSDeviceCommandReplyObject1->SetMessage( L"Message" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gNSSDeviceCommandReplyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gNSSDeviceCommandReplyObject2 = std::reinterpret_pointer_cast<GNSSDeviceCommandReplyObject>( ReadDataFrom( source ) );
    bool equal = gNSSDeviceCommandReplyObject2->IsEqualTo( *gNSSDeviceCommandReplyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GNSSDeviceConfigurationObjectSerializationTest
BOOST_AUTO_TEST_CASE( GNSSDeviceConfigurationObjectSerializationTest )
{
    auto gNSSDeviceConfigurationObject1 = std::make_shared<GNSSDeviceConfigurationObject>( );
    gNSSDeviceConfigurationObject1->SetId( Guid( L"{3ED852BF-D8F3-84AF-21F5-1BCF7C1B4AFD}" ) );
    gNSSDeviceConfigurationObject1->SetRowVersion( -8885645000535682369LL );
    gNSSDeviceConfigurationObject1->SetGNSSDevice( Guid( L"{3ED852BF-D8F3-84AF-21F5-1BCF7C1B4AFD}" ) );
    gNSSDeviceConfigurationObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    gNSSDeviceConfigurationObject1->SetDefaultLatitude( 9561099073173868 );
    gNSSDeviceConfigurationObject1->SetDefaultLongitude( 9561099073173868 );
    gNSSDeviceConfigurationObject1->SetDefaultAltitude( 9561099073173868 );
    gNSSDeviceConfigurationObject1->SetLatitudeOffset( 9561099073173868 );
    gNSSDeviceConfigurationObject1->SetLongitudeOffset( 9561099073173868 );
    gNSSDeviceConfigurationObject1->SetAltitudeOffset( 9561099073173868 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gNSSDeviceConfigurationObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gNSSDeviceConfigurationObject2 = std::reinterpret_pointer_cast<GNSSDeviceConfigurationObject>( ReadDataFrom( source ) );
    bool equal = gNSSDeviceConfigurationObject2->IsEqualTo( *gNSSDeviceConfigurationObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GuidTimeseriesValueObjectSerializationTest
BOOST_AUTO_TEST_CASE( GuidTimeseriesValueObjectSerializationTest )
{
    auto guidTimeseriesValueObject1 = std::make_shared<GuidTimeseriesValueObject>( );
    guidTimeseriesValueObject1->SetId( Guid( L"{46558315-F37B-09FC-903F-CFDE62AAC1A8}" ) );
    guidTimeseriesValueObject1->SetRowVersion( 719717751258972949LL );
    guidTimeseriesValueObject1->SetTimeseries( Guid( L"{46558315-F37B-09FC-903F-CFDE62AAC1A8}" ) );
    guidTimeseriesValueObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    guidTimeseriesValueObject1->SetValue( Guid( L"{46558315-F37B-09FC-903F-CFDE62AAC1A8}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *guidTimeseriesValueObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto guidTimeseriesValueObject2 = std::reinterpret_pointer_cast<GuidTimeseriesValueObject>( ReadDataFrom( source ) );
    bool equal = guidTimeseriesValueObject2->IsEqualTo( *guidTimeseriesValueObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GyroDeviceCommandObjectSerializationTest
BOOST_AUTO_TEST_CASE( GyroDeviceCommandObjectSerializationTest )
{
    auto gyroDeviceCommandObject1 = std::make_shared<GyroDeviceCommandObject>( );
    gyroDeviceCommandObject1->SetId( Guid( L"{0E55A9AC-70F5-F9E6-9F67-0EAF70AA9535}" ) );
    gyroDeviceCommandObject1->SetRowVersion( -439539715812251220LL );
    gyroDeviceCommandObject1->SetGyroDevice( Guid( L"{0E55A9AC-70F5-F9E6-9F67-0EAF70AA9535}" ) );
    gyroDeviceCommandObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    gyroDeviceCommandObject1->SetDeviceCommandSourceType( DeviceCommandSourceType::Unknown );
    gyroDeviceCommandObject1->SetDeviceCommandSourceId( Guid( L"{0E55A9AC-70F5-F9E6-9F67-0EAF70AA9535}" ) );
    gyroDeviceCommandObject1->SetReply( Guid( L"{0E55A9AC-70F5-F9E6-9F67-0EAF70AA9535}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gyroDeviceCommandObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gyroDeviceCommandObject2 = std::reinterpret_pointer_cast<GyroDeviceCommandObject>( ReadDataFrom( source ) );
    bool equal = gyroDeviceCommandObject2->IsEqualTo( *gyroDeviceCommandObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GyroDeviceCommandReplyObjectSerializationTest
BOOST_AUTO_TEST_CASE( GyroDeviceCommandReplyObjectSerializationTest )
{
    auto gyroDeviceCommandReplyObject1 = std::make_shared<GyroDeviceCommandReplyObject>( );
    gyroDeviceCommandReplyObject1->SetId( Guid( L"{FE226ABE-7E8C-EA31-578C-7E317F44567D}" ) );
    gyroDeviceCommandReplyObject1->SetRowVersion( -1571335650951402818LL );
    gyroDeviceCommandReplyObject1->SetGyroDevice( Guid( L"{FE226ABE-7E8C-EA31-578C-7E317F44567D}" ) );
    gyroDeviceCommandReplyObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    gyroDeviceCommandReplyObject1->SetCommand( Guid( L"{FE226ABE-7E8C-EA31-578C-7E317F44567D}" ) );
    gyroDeviceCommandReplyObject1->SetStatus( DeviceCommandReplyStatus::NotImplemented );
    gyroDeviceCommandReplyObject1->SetMessage( L"Message" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gyroDeviceCommandReplyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gyroDeviceCommandReplyObject2 = std::reinterpret_pointer_cast<GyroDeviceCommandReplyObject>( ReadDataFrom( source ) );
    bool equal = gyroDeviceCommandReplyObject2->IsEqualTo( *gyroDeviceCommandReplyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GyroDeviceConfigurationObjectSerializationTest
BOOST_AUTO_TEST_CASE( GyroDeviceConfigurationObjectSerializationTest )
{
    auto gyroDeviceConfigurationObject1 = std::make_shared<GyroDeviceConfigurationObject>( );
    gyroDeviceConfigurationObject1->SetId( Guid( L"{1BECC465-DE53-3C49-3C92-7BCAD83723A6}" ) );
    gyroDeviceConfigurationObject1->SetRowVersion( 4344247764107707493LL );
    gyroDeviceConfigurationObject1->SetGyroDevice( Guid( L"{1BECC465-DE53-3C49-3C92-7BCAD83723A6}" ) );
    gyroDeviceConfigurationObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    gyroDeviceConfigurationObject1->SetDefaultHeadingTrueNorth( 4344247764107707.5 );
    gyroDeviceConfigurationObject1->SetDefaultMagneticTrueNorth( 4344247764107707.5 );
    gyroDeviceConfigurationObject1->SetHeadingTrueNorthOffset( 4344247764107707.5 );
    gyroDeviceConfigurationObject1->SetHeadingMagneticNorthOffset( 4344247764107707.5 );
    gyroDeviceConfigurationObject1->SetPitchTransducerName( L"PitchTransducerName" );
    gyroDeviceConfigurationObject1->SetRollTransducerName( L"RollTransducerName" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gyroDeviceConfigurationObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gyroDeviceConfigurationObject2 = std::reinterpret_pointer_cast<GyroDeviceConfigurationObject>( ReadDataFrom( source ) );
    bool equal = gyroDeviceConfigurationObject2->IsEqualTo( *gyroDeviceConfigurationObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CallsignObjectSerializationTest
BOOST_AUTO_TEST_CASE( CallsignObjectSerializationTest )
{
    auto callsignObject1 = std::make_shared<CallsignObject>( );
    callsignObject1->SetId( Guid( L"{D17786FB-677E-6126-8664-E67E8BEE61DF}" ) );
    callsignObject1->SetRowVersion( 7000396465171826427LL );
    callsignObject1->SetIdentifier( L"Identifier" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *callsignObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto callsignObject2 = std::reinterpret_pointer_cast<CallsignObject>( ReadDataFrom( source ) );
    bool equal = callsignObject2->IsEqualTo( *callsignObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/InternationalMaritimeOrganizationNumberObjectSerializationTest
BOOST_AUTO_TEST_CASE( InternationalMaritimeOrganizationNumberObjectSerializationTest )
{
    auto internationalMaritimeOrganizationNumberObject1 = std::make_shared<InternationalMaritimeOrganizationNumberObject>( );
    internationalMaritimeOrganizationNumberObject1->SetId( Guid( L"{981538E8-05C6-4E9F-72F9-A06319A81C17}" ) );
    internationalMaritimeOrganizationNumberObject1->SetRowVersion( 5665253206768564456LL );
    internationalMaritimeOrganizationNumberObject1->SetIdentifier( 5665253206768564456LL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *internationalMaritimeOrganizationNumberObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto internationalMaritimeOrganizationNumberObject2 = std::reinterpret_pointer_cast<InternationalMaritimeOrganizationNumberObject>( ReadDataFrom( source ) );
    bool equal = internationalMaritimeOrganizationNumberObject2->IsEqualTo( *internationalMaritimeOrganizationNumberObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/MaritimeMobileServiceIdentityObjectSerializationTest
BOOST_AUTO_TEST_CASE( MaritimeMobileServiceIdentityObjectSerializationTest )
{
    auto maritimeMobileServiceIdentityObject1 = std::make_shared<MaritimeMobileServiceIdentityObject>( );
    maritimeMobileServiceIdentityObject1->SetId( Guid( L"{3F5D957C-F33F-B5BB-ADDD-CFFCFCBAA93E}" ) );
    maritimeMobileServiceIdentityObject1->SetRowVersion( -5351416279228115588LL );
    maritimeMobileServiceIdentityObject1->SetIdentifier( -5351416279228115588LL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *maritimeMobileServiceIdentityObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto maritimeMobileServiceIdentityObject2 = std::reinterpret_pointer_cast<MaritimeMobileServiceIdentityObject>( ReadDataFrom( source ) );
    bool equal = maritimeMobileServiceIdentityObject2->IsEqualTo( *maritimeMobileServiceIdentityObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/NameObjectSerializationTest
BOOST_AUTO_TEST_CASE( NameObjectSerializationTest )
{
    auto nameObject1 = std::make_shared<NameObject>( );
    nameObject1->SetId( Guid( L"{5C4D0804-63C5-C4E9-2397-C6A33AB21020}" ) );
    nameObject1->SetRowVersion( -4257762273393833980LL );
    nameObject1->SetText( L"Text" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *nameObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto nameObject2 = std::reinterpret_pointer_cast<NameObject>( ReadDataFrom( source ) );
    bool equal = nameObject2->IsEqualTo( *nameObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int16TimeseriesValueObjectSerializationTest
BOOST_AUTO_TEST_CASE( Int16TimeseriesValueObjectSerializationTest )
{
    auto int16TimeseriesValueObject1 = std::make_shared<Int16TimeseriesValueObject>( );
    int16TimeseriesValueObject1->SetId( Guid( L"{B94AD405-0355-A9BD-95BD-C0AA9D522BA0}" ) );
    int16TimeseriesValueObject1->SetRowVersion( -6215808243985624059LL );
    int16TimeseriesValueObject1->SetTimeseries( Guid( L"{B94AD405-0355-A9BD-95BD-C0AA9D522BA0}" ) );
    int16TimeseriesValueObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    int16TimeseriesValueObject1->SetValue( -11259 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int16TimeseriesValueObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int16TimeseriesValueObject2 = std::reinterpret_pointer_cast<Int16TimeseriesValueObject>( ReadDataFrom( source ) );
    bool equal = int16TimeseriesValueObject2->IsEqualTo( *int16TimeseriesValueObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int32TimeseriesValueObjectSerializationTest
BOOST_AUTO_TEST_CASE( Int32TimeseriesValueObjectSerializationTest )
{
    auto int32TimeseriesValueObject1 = std::make_shared<Int32TimeseriesValueObject>( );
    int32TimeseriesValueObject1->SetId( Guid( L"{38DCBC02-9C28-2570-A40E-39141C3B3D40}" ) );
    int32TimeseriesValueObject1->SetRowVersion( 2697827873361542146LL );
    int32TimeseriesValueObject1->SetTimeseries( Guid( L"{38DCBC02-9C28-2570-A40E-39141C3B3D40}" ) );
    int32TimeseriesValueObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    int32TimeseriesValueObject1->SetValue( 953990146L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int32TimeseriesValueObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int32TimeseriesValueObject2 = std::reinterpret_pointer_cast<Int32TimeseriesValueObject>( ReadDataFrom( source ) );
    bool equal = int32TimeseriesValueObject2->IsEqualTo( *int32TimeseriesValueObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int64TimeseriesValueObjectSerializationTest
BOOST_AUTO_TEST_CASE( Int64TimeseriesValueObjectSerializationTest )
{
    auto int64TimeseriesValueObject1 = std::make_shared<Int64TimeseriesValueObject>( );
    int64TimeseriesValueObject1->SetId( Guid( L"{DD2DE745-E72A-DFD1-FB8B-E754BBB4E7A2}" ) );
    int64TimeseriesValueObject1->SetRowVersion( -2318818161833679035LL );
    int64TimeseriesValueObject1->SetTimeseries( Guid( L"{DD2DE745-E72A-DFD1-FB8B-E754BBB4E7A2}" ) );
    int64TimeseriesValueObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    int64TimeseriesValueObject1->SetValue( -2318818161833679035LL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int64TimeseriesValueObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int64TimeseriesValueObject2 = std::reinterpret_pointer_cast<Int64TimeseriesValueObject>( ReadDataFrom( source ) );
    bool equal = int64TimeseriesValueObject2->IsEqualTo( *int64TimeseriesValueObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BaseStationObjectSerializationTest
BOOST_AUTO_TEST_CASE( BaseStationObjectSerializationTest )
{
    auto baseStationObject1 = std::make_shared<BaseStationObject>( );
    baseStationObject1->SetId( Guid( L"{416FD82E-C84F-09AB-90D5-13F282F61B74}" ) );
    baseStationObject1->SetRowVersion( 696870810084694062LL );
    baseStationObject1->SetName( L"Name" );
    baseStationObject1->SetType( Guid( L"{416FD82E-C84F-09AB-90D5-13F282F61B74}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *baseStationObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto baseStationObject2 = std::reinterpret_pointer_cast<BaseStationObject>( ReadDataFrom( source ) );
    bool equal = baseStationObject2->IsEqualTo( *baseStationObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraDeviceObjectSerializationTest
BOOST_AUTO_TEST_CASE( CameraDeviceObjectSerializationTest )
{
    auto cameraDeviceObject1 = std::make_shared<CameraDeviceObject>( );
    cameraDeviceObject1->SetId( Guid( L"{9A39E4FA-E0AF-4E1A-7258-07F5599C275F}" ) );
    cameraDeviceObject1->SetRowVersion( 5628057729164240122LL );
    cameraDeviceObject1->SetHost( Guid( L"{9A39E4FA-E0AF-4E1A-7258-07F5599C275F}" ) );
    cameraDeviceObject1->SetName( L"Name" );
    cameraDeviceObject1->SetDescription( L"Description" );
    cameraDeviceObject1->SetEnabledTimeseries( Guid( L"{9A39E4FA-E0AF-4E1A-7258-07F5599C275F}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraDeviceObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraDeviceObject2 = std::reinterpret_pointer_cast<CameraDeviceObject>( ReadDataFrom( source ) );
    bool equal = cameraDeviceObject2->IsEqualTo( *cameraDeviceObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GNSSDeviceObjectSerializationTest
BOOST_AUTO_TEST_CASE( GNSSDeviceObjectSerializationTest )
{
    auto gNSSDeviceObject1 = std::make_shared<GNSSDeviceObject>( );
    gNSSDeviceObject1->SetId( Guid( L"{5F25A83C-CA3E-191C-9838-537CFAA4153C}" ) );
    gNSSDeviceObject1->SetRowVersion( 1809543519529183292LL );
    gNSSDeviceObject1->SetHost( Guid( L"{5F25A83C-CA3E-191C-9838-537CFAA4153C}" ) );
    gNSSDeviceObject1->SetName( L"Name" );
    gNSSDeviceObject1->SetDescription( L"Description" );
    gNSSDeviceObject1->SetEnabledTimeseries( Guid( L"{5F25A83C-CA3E-191C-9838-537CFAA4153C}" ) );
    gNSSDeviceObject1->SetLatitudeTimeseries( Guid( L"{5F25A83C-CA3E-191C-9838-537CFAA4153C}" ) );
    gNSSDeviceObject1->SetLongitudeTimeseries( Guid( L"{5F25A83C-CA3E-191C-9838-537CFAA4153C}" ) );
    gNSSDeviceObject1->SetAltitudeTimeseries( Guid( L"{5F25A83C-CA3E-191C-9838-537CFAA4153C}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gNSSDeviceObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gNSSDeviceObject2 = std::reinterpret_pointer_cast<GNSSDeviceObject>( ReadDataFrom( source ) );
    bool equal = gNSSDeviceObject2->IsEqualTo( *gNSSDeviceObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GyroDeviceObjectSerializationTest
BOOST_AUTO_TEST_CASE( GyroDeviceObjectSerializationTest )
{
    auto gyroDeviceObject1 = std::make_shared<GyroDeviceObject>( );
    gyroDeviceObject1->SetId( Guid( L"{90098F8B-0830-813D-81BC-100C0990F1D1}" ) );
    gyroDeviceObject1->SetRowVersion( -9134135464569499765LL );
    gyroDeviceObject1->SetHost( Guid( L"{90098F8B-0830-813D-81BC-100C0990F1D1}" ) );
    gyroDeviceObject1->SetName( L"Name" );
    gyroDeviceObject1->SetDescription( L"Description" );
    gyroDeviceObject1->SetEnabledTimeseries( Guid( L"{90098F8B-0830-813D-81BC-100C0990F1D1}" ) );
    gyroDeviceObject1->SetHeadingTrueNorthTimeseries( Guid( L"{90098F8B-0830-813D-81BC-100C0990F1D1}" ) );
    gyroDeviceObject1->SetHeadingMagneticNorthTimeseries( Guid( L"{90098F8B-0830-813D-81BC-100C0990F1D1}" ) );
    gyroDeviceObject1->SetPitchTimeseries( Guid( L"{90098F8B-0830-813D-81BC-100C0990F1D1}" ) );
    gyroDeviceObject1->SetRateOfTurnTimeseries( Guid( L"{90098F8B-0830-813D-81BC-100C0990F1D1}" ) );
    gyroDeviceObject1->SetRollTimeseries( Guid( L"{90098F8B-0830-813D-81BC-100C0990F1D1}" ) );
    gyroDeviceObject1->SetCourseTimeseries( Guid( L"{90098F8B-0830-813D-81BC-100C0990F1D1}" ) );
    gyroDeviceObject1->SetSpeedTimeseries( Guid( L"{90098F8B-0830-813D-81BC-100C0990F1D1}" ) );
    gyroDeviceObject1->SetGNSSDevice( Guid( L"{90098F8B-0830-813D-81BC-100C0990F1D1}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gyroDeviceObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gyroDeviceObject2 = std::reinterpret_pointer_cast<GyroDeviceObject>( ReadDataFrom( source ) );
    bool equal = gyroDeviceObject2->IsEqualTo( *gyroDeviceObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LineInputDeviceObjectSerializationTest
BOOST_AUTO_TEST_CASE( LineInputDeviceObjectSerializationTest )
{
    auto lineInputDeviceObject1 = std::make_shared<LineInputDeviceObject>( );
    lineInputDeviceObject1->SetId( Guid( L"{67363DC8-DFCA-71BB-8EDD-FB53E66CBC13}" ) );
    lineInputDeviceObject1->SetRowVersion( 8195390007338745288LL );
    lineInputDeviceObject1->SetHost( Guid( L"{67363DC8-DFCA-71BB-8EDD-FB53E66CBC13}" ) );
    lineInputDeviceObject1->SetName( L"Name" );
    lineInputDeviceObject1->SetDescription( L"Description" );
    lineInputDeviceObject1->SetEnabledTimeseries( Guid( L"{67363DC8-DFCA-71BB-8EDD-FB53E66CBC13}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *lineInputDeviceObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto lineInputDeviceObject2 = std::reinterpret_pointer_cast<LineInputDeviceObject>( ReadDataFrom( source ) );
    bool equal = lineInputDeviceObject2->IsEqualTo( *lineInputDeviceObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/OilSpillDetectorDeviceObjectSerializationTest
BOOST_AUTO_TEST_CASE( OilSpillDetectorDeviceObjectSerializationTest )
{
    auto oilSpillDetectorDeviceObject1 = std::make_shared<OilSpillDetectorDeviceObject>( );
    oilSpillDetectorDeviceObject1->SetId( Guid( L"{651E7CA3-C6A3-B291-4D89-63C5A6783EC5}" ) );
    oilSpillDetectorDeviceObject1->SetRowVersion( -5579460058256868189LL );
    oilSpillDetectorDeviceObject1->SetHost( Guid( L"{651E7CA3-C6A3-B291-4D89-63C5A6783EC5}" ) );
    oilSpillDetectorDeviceObject1->SetName( L"Name" );
    oilSpillDetectorDeviceObject1->SetDescription( L"Description" );
    oilSpillDetectorDeviceObject1->SetEnabledTimeseries( Guid( L"{651E7CA3-C6A3-B291-4D89-63C5A6783EC5}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *oilSpillDetectorDeviceObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto oilSpillDetectorDeviceObject2 = std::reinterpret_pointer_cast<OilSpillDetectorDeviceObject>( ReadDataFrom( source ) );
    bool equal = oilSpillDetectorDeviceObject2->IsEqualTo( *oilSpillDetectorDeviceObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadioDeviceObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadioDeviceObjectSerializationTest )
{
    auto radioDeviceObject1 = std::make_shared<RadioDeviceObject>( );
    radioDeviceObject1->SetId( Guid( L"{F40989E1-0C78-211F-84F8-301E2F909187}" ) );
    radioDeviceObject1->SetRowVersion( 2386640041159526881LL );
    radioDeviceObject1->SetHost( Guid( L"{F40989E1-0C78-211F-84F8-301E2F909187}" ) );
    radioDeviceObject1->SetName( L"Name" );
    radioDeviceObject1->SetDescription( L"Description" );
    radioDeviceObject1->SetEnabledTimeseries( Guid( L"{F40989E1-0C78-211F-84F8-301E2F909187}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radioDeviceObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radioDeviceObject2 = std::reinterpret_pointer_cast<RadioDeviceObject>( ReadDataFrom( source ) );
    bool equal = radioDeviceObject2->IsEqualTo( *radioDeviceObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadomeDeviceObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadomeDeviceObjectSerializationTest )
{
    auto radomeDeviceObject1 = std::make_shared<RadomeDeviceObject>( );
    radomeDeviceObject1->SetId( Guid( L"{19C3E223-3605-2098-0419-6CA098C347C4}" ) );
    radomeDeviceObject1->SetRowVersion( 2348686601208717859LL );
    radomeDeviceObject1->SetHost( Guid( L"{19C3E223-3605-2098-0419-6CA098C347C4}" ) );
    radomeDeviceObject1->SetName( L"Name" );
    radomeDeviceObject1->SetDescription( L"Description" );
    radomeDeviceObject1->SetEnabledTimeseries( Guid( L"{19C3E223-3605-2098-0419-6CA098C347C4}" ) );
    radomeDeviceObject1->SetRadar( Guid( L"{19C3E223-3605-2098-0419-6CA098C347C4}" ) );
    radomeDeviceObject1->SetPressureTimeseries( Guid( L"{19C3E223-3605-2098-0419-6CA098C347C4}" ) );
    radomeDeviceObject1->SetTemperatureTimeseries( Guid( L"{19C3E223-3605-2098-0419-6CA098C347C4}" ) );
    radomeDeviceObject1->SetDewPointTimeseries( Guid( L"{19C3E223-3605-2098-0419-6CA098C347C4}" ) );
    radomeDeviceObject1->SetStatusTimeseries( Guid( L"{19C3E223-3605-2098-0419-6CA098C347C4}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radomeDeviceObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radomeDeviceObject2 = std::reinterpret_pointer_cast<RadomeDeviceObject>( ReadDataFrom( source ) );
    bool equal = radomeDeviceObject2->IsEqualTo( *radomeDeviceObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisDeviceObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisDeviceObjectSerializationTest )
{
    auto aisDeviceObject1 = std::make_shared<AisDeviceObject>( );
    aisDeviceObject1->SetId( Guid( L"{549DED19-8FC6-C9C7-93E3-F1632AB9B798}" ) );
    aisDeviceObject1->SetRowVersion( -3906996069734683367LL );
    aisDeviceObject1->SetHost( Guid( L"{549DED19-8FC6-C9C7-93E3-F1632AB9B798}" ) );
    aisDeviceObject1->SetName( L"Name" );
    aisDeviceObject1->SetDescription( L"Description" );
    aisDeviceObject1->SetEnabledTimeseries( Guid( L"{549DED19-8FC6-C9C7-93E3-F1632AB9B798}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisDeviceObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisDeviceObject2 = std::reinterpret_pointer_cast<AisDeviceObject>( ReadDataFrom( source ) );
    bool equal = aisDeviceObject2->IsEqualTo( *aisDeviceObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarDeviceObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarDeviceObjectSerializationTest )
{
    auto radarDeviceObject1 = std::make_shared<RadarDeviceObject>( );
    radarDeviceObject1->SetId( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );
    radarDeviceObject1->SetRowVersion( 7065711710078870894LL );
    radarDeviceObject1->SetHost( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );
    radarDeviceObject1->SetName( L"Name" );
    radarDeviceObject1->SetDescription( L"Description" );
    radarDeviceObject1->SetEnabledTimeseries( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );
    radarDeviceObject1->SetSaveSettingsTimeseries( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );
    radarDeviceObject1->SetPowerOnTimeseries( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );
    radarDeviceObject1->SetTrackingOnTimeseries( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );
    radarDeviceObject1->SetRadarPulseTimeseries( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );
    radarDeviceObject1->SetTuningTimeseries( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );
    radarDeviceObject1->SetBlankSector1Timeseries( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );
    radarDeviceObject1->SetSector1StartTimeseries( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );
    radarDeviceObject1->SetSector1EndTimeseries( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );
    radarDeviceObject1->SetBlankSector2Timeseries( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );
    radarDeviceObject1->SetSector2StartTimeseries( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );
    radarDeviceObject1->SetSector2EndTimeseries( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );
    radarDeviceObject1->SetEnableAutomaticFrequencyControlTimeseries( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );
    radarDeviceObject1->SetAzimuthOffsetTimeseries( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );
    radarDeviceObject1->SetEnableSensitivityTimeControlTimeseries( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );
    radarDeviceObject1->SetAutomaticSensitivityTimeControlTimeseries( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );
    radarDeviceObject1->SetSensitivityTimeControlLevelTimeseries( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );
    radarDeviceObject1->SetEnableFastTimeConstantTimeseries( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );
    radarDeviceObject1->SetFastTimeConstantLevelTimeseries( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );
    radarDeviceObject1->SetFastTimeConstantModeTimeseries( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );
    radarDeviceObject1->SetLatitudeTimeseries( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );
    radarDeviceObject1->SetLongitudeTimeseries( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );
    radarDeviceObject1->SetRadome( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );
    radarDeviceObject1->SetGNSSDevice( Guid( L"{5491A56E-735D-620E-4670-CEBA2A89A576}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarDeviceObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarDeviceObject2 = std::reinterpret_pointer_cast<RadarDeviceObject>( ReadDataFrom( source ) );
    bool equal = radarDeviceObject2->IsEqualTo( *radarDeviceObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/WeatherStationDeviceObjectSerializationTest
BOOST_AUTO_TEST_CASE( WeatherStationDeviceObjectSerializationTest )
{
    auto weatherStationDeviceObject1 = std::make_shared<WeatherStationDeviceObject>( );
    weatherStationDeviceObject1->SetId( Guid( L"{64B16CBA-65D8-4E79-729E-A61B268D365D}" ) );
    weatherStationDeviceObject1->SetRowVersion( 5654662787217059002LL );
    weatherStationDeviceObject1->SetHost( Guid( L"{64B16CBA-65D8-4E79-729E-A61B268D365D}" ) );
    weatherStationDeviceObject1->SetName( L"Name" );
    weatherStationDeviceObject1->SetDescription( L"Description" );
    weatherStationDeviceObject1->SetEnabledTimeseries( Guid( L"{64B16CBA-65D8-4E79-729E-A61B268D365D}" ) );
    weatherStationDeviceObject1->SetBarometricPressureTimeseries( Guid( L"{64B16CBA-65D8-4E79-729E-A61B268D365D}" ) );
    weatherStationDeviceObject1->SetAirTemperatureTimeseries( Guid( L"{64B16CBA-65D8-4E79-729E-A61B268D365D}" ) );
    weatherStationDeviceObject1->SetWaterTemperatureTimeseries( Guid( L"{64B16CBA-65D8-4E79-729E-A61B268D365D}" ) );
    weatherStationDeviceObject1->SetRelativeHumidityTimeseries( Guid( L"{64B16CBA-65D8-4E79-729E-A61B268D365D}" ) );
    weatherStationDeviceObject1->SetAbsoluteHumidityTimeseries( Guid( L"{64B16CBA-65D8-4E79-729E-A61B268D365D}" ) );
    weatherStationDeviceObject1->SetDewPointTimeseries( Guid( L"{64B16CBA-65D8-4E79-729E-A61B268D365D}" ) );
    weatherStationDeviceObject1->SetWindDirectionTimeseries( Guid( L"{64B16CBA-65D8-4E79-729E-A61B268D365D}" ) );
    weatherStationDeviceObject1->SetWindSpeedTimeseries( Guid( L"{64B16CBA-65D8-4E79-729E-A61B268D365D}" ) );
    weatherStationDeviceObject1->SetGyro( Guid( L"{64B16CBA-65D8-4E79-729E-A61B268D365D}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *weatherStationDeviceObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto weatherStationDeviceObject2 = std::reinterpret_pointer_cast<WeatherStationDeviceObject>( ReadDataFrom( source ) );
    bool equal = weatherStationDeviceObject2->IsEqualTo( *weatherStationDeviceObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/FacilityObjectSerializationTest
BOOST_AUTO_TEST_CASE( FacilityObjectSerializationTest )
{
    auto facilityObject1 = std::make_shared<FacilityObject>( );
    facilityObject1->SetId( Guid( L"{E5843450-575C-678E-E671-EA3AA7212C0A}" ) );
    facilityObject1->SetRowVersion( 7461997689098744912LL );
    facilityObject1->SetName( L"Name" );
    facilityObject1->SetType( Guid( L"{E5843450-575C-678E-E671-EA3AA7212C0A}" ) );
    facilityObject1->SetLongitude( 7461997689098745 );
    facilityObject1->SetLatitude( 7461997689098745 );
    facilityObject1->SetAltitude( 7461997689098745 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *facilityObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto facilityObject2 = std::reinterpret_pointer_cast<FacilityObject>( ReadDataFrom( source ) );
    bool equal = facilityObject2->IsEqualTo( *facilityObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AircraftObjectSerializationTest
BOOST_AUTO_TEST_CASE( AircraftObjectSerializationTest )
{
    auto aircraftObject1 = std::make_shared<AircraftObject>( );
    aircraftObject1->SetId( Guid( L"{6166D8B6-B9DA-5EE5-7AA7-9D5B86661B6D}" ) );
    aircraftObject1->SetRowVersion( 6838075956820105398LL );
    aircraftObject1->SetName( L"Name" );
    aircraftObject1->SetType( Guid( L"{6166D8B6-B9DA-5EE5-7AA7-9D5B86661B6D}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aircraftObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aircraftObject2 = std::reinterpret_pointer_cast<AircraftObject>( ReadDataFrom( source ) );
    bool equal = aircraftObject2->IsEqualTo( *aircraftObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisAidToNavigationObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisAidToNavigationObjectSerializationTest )
{
    auto aisAidToNavigationObject1 = std::make_shared<AisAidToNavigationObject>( );
    aisAidToNavigationObject1->SetId( Guid( L"{16DDCFB2-2EE7-3B43-DCC2-74E768BBF34D}" ) );
    aisAidToNavigationObject1->SetRowVersion( 4270308441733320626LL );
    aisAidToNavigationObject1->SetName( L"Name" );
    aisAidToNavigationObject1->SetMMSI( Guid( L"{16DDCFB2-2EE7-3B43-DCC2-74E768BBF34D}" ) );
    aisAidToNavigationObject1->SetNavigationalAidType( NavigationalAidType::BeaconSafeWater );
    aisAidToNavigationObject1->SetPosition( Guid( L"{16DDCFB2-2EE7-3B43-DCC2-74E768BBF34D}" ) );
    aisAidToNavigationObject1->SetIsVirtual( false );
    aisAidToNavigationObject1->SetToBow( 383635378L );
    aisAidToNavigationObject1->SetToStern( 383635378L );
    aisAidToNavigationObject1->SetToPort( 383635378L );
    aisAidToNavigationObject1->SetToStarboard( 383635378L );
    aisAidToNavigationObject1->SetOffPositionTimeseries( Guid( L"{16DDCFB2-2EE7-3B43-DCC2-74E768BBF34D}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisAidToNavigationObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisAidToNavigationObject2 = std::reinterpret_pointer_cast<AisAidToNavigationObject>( ReadDataFrom( source ) );
    bool equal = aisAidToNavigationObject2->IsEqualTo( *aisAidToNavigationObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/VehicleObjectSerializationTest
BOOST_AUTO_TEST_CASE( VehicleObjectSerializationTest )
{
    auto vehicleObject1 = std::make_shared<VehicleObject>( );
    vehicleObject1->SetId( Guid( L"{65C36569-1718-3990-9C09-E818A6C3A696}" ) );
    vehicleObject1->SetRowVersion( 4147840650362185065LL );
    vehicleObject1->SetName( L"Name" );
    vehicleObject1->SetType( Guid( L"{65C36569-1718-3990-9C09-E818A6C3A696}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *vehicleObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto vehicleObject2 = std::reinterpret_pointer_cast<VehicleObject>( ReadDataFrom( source ) );
    bool equal = vehicleObject2->IsEqualTo( *vehicleObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/VesselObjectSerializationTest
BOOST_AUTO_TEST_CASE( VesselObjectSerializationTest )
{
    auto vesselObject1 = std::make_shared<VesselObject>( );
    vesselObject1->SetId( Guid( L"{9DD08333-9688-8B47-D1E2-6911B90BC1CC}" ) );
    vesselObject1->SetRowVersion( -8410588265583705293LL );
    vesselObject1->SetName( L"Name" );
    vesselObject1->SetType( Guid( L"{9DD08333-9688-8B47-D1E2-6911B90BC1CC}" ) );
    vesselObject1->SetToBow( -1647279309L );
    vesselObject1->SetToStern( -1647279309L );
    vesselObject1->SetToPort( -1647279309L );
    vesselObject1->SetToStarboard( -1647279309L );
    vesselObject1->SetDraughtTimeseries( Guid( L"{9DD08333-9688-8B47-D1E2-6911B90BC1CC}" ) );
    vesselObject1->SetPersonsOnBoardTimeseries( Guid( L"{9DD08333-9688-8B47-D1E2-6911B90BC1CC}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *vesselObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto vesselObject2 = std::reinterpret_pointer_cast<VesselObject>( ReadDataFrom( source ) );
    bool equal = vesselObject2->IsEqualTo( *vesselObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ItemIdentityLinkObjectSerializationTest
BOOST_AUTO_TEST_CASE( ItemIdentityLinkObjectSerializationTest )
{
    auto itemIdentityLinkObject1 = std::make_shared<ItemIdentityLinkObject>( );
    itemIdentityLinkObject1->SetId( Guid( L"{7F8E5AF6-1EE2-4720-E204-7847FE715A6F}" ) );
    itemIdentityLinkObject1->SetRowVersion( 5125130334099102454LL );
    itemIdentityLinkObject1->SetItem( Guid( L"{7F8E5AF6-1EE2-4720-E204-7847FE715A6F}" ) );
    itemIdentityLinkObject1->SetIdentity( Guid( L"{7F8E5AF6-1EE2-4720-E204-7847FE715A6F}" ) );
    itemIdentityLinkObject1->SetStart( DateTime( 1, 1, 1, 22, 23, 35 ) );
    itemIdentityLinkObject1->SetEnd( DateTime( 1, 1, 1, 22, 23, 35 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *itemIdentityLinkObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto itemIdentityLinkObject2 = std::reinterpret_pointer_cast<ItemIdentityLinkObject>( ReadDataFrom( source ) );
    bool equal = itemIdentityLinkObject2->IsEqualTo( *itemIdentityLinkObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ItemParentChildLinkObjectSerializationTest
BOOST_AUTO_TEST_CASE( ItemParentChildLinkObjectSerializationTest )
{
    auto itemParentChildLinkObject1 = std::make_shared<ItemParentChildLinkObject>( );
    itemParentChildLinkObject1->SetId( Guid( L"{49E45A37-F96C-0493-20C9-9F3692275AEC}" ) );
    itemParentChildLinkObject1->SetRowVersion( 329881441219664439LL );
    itemParentChildLinkObject1->SetParent( Guid( L"{49E45A37-F96C-0493-20C9-9F3692275AEC}" ) );
    itemParentChildLinkObject1->SetChild( Guid( L"{49E45A37-F96C-0493-20C9-9F3692275AEC}" ) );
    itemParentChildLinkObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *itemParentChildLinkObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto itemParentChildLinkObject2 = std::reinterpret_pointer_cast<ItemParentChildLinkObject>( ReadDataFrom( source ) );
    bool equal = itemParentChildLinkObject2->IsEqualTo( *itemParentChildLinkObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LineInputDeviceCommandObjectSerializationTest
BOOST_AUTO_TEST_CASE( LineInputDeviceCommandObjectSerializationTest )
{
    auto lineInputDeviceCommandObject1 = std::make_shared<LineInputDeviceCommandObject>( );
    lineInputDeviceCommandObject1->SetId( Guid( L"{628CD2DB-52F1-4F5F-F2FA-4A8F46314BDB}" ) );
    lineInputDeviceCommandObject1->SetRowVersion( 5719381248477811419LL );
    lineInputDeviceCommandObject1->SetLineInputDevice( Guid( L"{628CD2DB-52F1-4F5F-F2FA-4A8F46314BDB}" ) );
    lineInputDeviceCommandObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    lineInputDeviceCommandObject1->SetDeviceCommandSourceType( DeviceCommandSourceType::Source );
    lineInputDeviceCommandObject1->SetDeviceCommandSourceId( Guid( L"{628CD2DB-52F1-4F5F-F2FA-4A8F46314BDB}" ) );
    lineInputDeviceCommandObject1->SetReply( Guid( L"{628CD2DB-52F1-4F5F-F2FA-4A8F46314BDB}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *lineInputDeviceCommandObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto lineInputDeviceCommandObject2 = std::reinterpret_pointer_cast<LineInputDeviceCommandObject>( ReadDataFrom( source ) );
    bool equal = lineInputDeviceCommandObject2->IsEqualTo( *lineInputDeviceCommandObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LineInputDeviceCommandReplyObjectSerializationTest
BOOST_AUTO_TEST_CASE( LineInputDeviceCommandReplyObjectSerializationTest )
{
    auto lineInputDeviceCommandReplyObject1 = std::make_shared<LineInputDeviceCommandReplyObject>( );
    lineInputDeviceCommandReplyObject1->SetId( Guid( L"{C1D214AC-9A66-FF50-FF0A-5966834B2835}" ) );
    lineInputDeviceCommandReplyObject1->SetRowVersion( -49369829771963220LL );
    lineInputDeviceCommandReplyObject1->SetLineInputDevice( Guid( L"{C1D214AC-9A66-FF50-FF0A-5966834B2835}" ) );
    lineInputDeviceCommandReplyObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    lineInputDeviceCommandReplyObject1->SetCommand( Guid( L"{C1D214AC-9A66-FF50-FF0A-5966834B2835}" ) );
    lineInputDeviceCommandReplyObject1->SetStatus( DeviceCommandReplyStatus::Unknown );
    lineInputDeviceCommandReplyObject1->SetMessage( L"Message" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *lineInputDeviceCommandReplyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto lineInputDeviceCommandReplyObject2 = std::reinterpret_pointer_cast<LineInputDeviceCommandReplyObject>( ReadDataFrom( source ) );
    bool equal = lineInputDeviceCommandReplyObject2->IsEqualTo( *lineInputDeviceCommandReplyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LineInputDeviceConfigurationObjectSerializationTest
BOOST_AUTO_TEST_CASE( LineInputDeviceConfigurationObjectSerializationTest )
{
    auto lineInputDeviceConfigurationObject1 = std::make_shared<LineInputDeviceConfigurationObject>( );
    lineInputDeviceConfigurationObject1->SetId( Guid( L"{C0009AA8-BD74-CF77-F3EE-BD2E03005915}" ) );
    lineInputDeviceConfigurationObject1->SetRowVersion( -3497118276494779736LL );
    lineInputDeviceConfigurationObject1->SetLineInputDevice( Guid( L"{C0009AA8-BD74-CF77-F3EE-BD2E03005915}" ) );
    lineInputDeviceConfigurationObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    lineInputDeviceConfigurationObject1->SetStoreReceivedSentences( false );
    lineInputDeviceConfigurationObject1->SetStoreSentMessages( false );
    lineInputDeviceConfigurationObject1->SetStoreUnsentMessages( false );
    lineInputDeviceConfigurationObject1->SetNMEA( false );
    lineInputDeviceConfigurationObject1->SetStrictNMEA( false );
    lineInputDeviceConfigurationObject1->SetConnectionType( LineInputDeviceConnectionType::Unknown );
    lineInputDeviceConfigurationObject1->SetUdpReceivePort( -1073702232L );
    lineInputDeviceConfigurationObject1->SetUdpSendHostname( L"UdpSendHostname" );
    lineInputDeviceConfigurationObject1->SetUdpSendPort( -1073702232L );
    lineInputDeviceConfigurationObject1->SetTcpHostname( L"TcpHostname" );
    lineInputDeviceConfigurationObject1->SetTcpPort( -1073702232L );
    lineInputDeviceConfigurationObject1->SetUseHttpLogin( false );
    lineInputDeviceConfigurationObject1->SetLoginHostname( L"LoginHostname" );
    lineInputDeviceConfigurationObject1->SetLoginPort( -1073702232L );
    lineInputDeviceConfigurationObject1->SetUserName( L"UserName" );
    lineInputDeviceConfigurationObject1->SetPassword( L"Password" );
    lineInputDeviceConfigurationObject1->SetComPort( L"ComPort" );
    lineInputDeviceConfigurationObject1->SetBaudRate( -1073702232L );
    lineInputDeviceConfigurationObject1->SetDataBits( -1073702232L );
    lineInputDeviceConfigurationObject1->SetDiscardNull( false );
    lineInputDeviceConfigurationObject1->SetDtrEnable( false );
    lineInputDeviceConfigurationObject1->SetHandshake( Handshake::None );
    lineInputDeviceConfigurationObject1->SetNewLine( L"NewLine" );
    lineInputDeviceConfigurationObject1->SetParity( Parity::None );
    lineInputDeviceConfigurationObject1->SetParityReplace( 168 );
    lineInputDeviceConfigurationObject1->SetReadBufferSize( -1073702232L );
    lineInputDeviceConfigurationObject1->SetReadTimeout( TimeSpan( -516494779736LL ) );
    lineInputDeviceConfigurationObject1->SetReceivedBytesThreshold( -1073702232L );
    lineInputDeviceConfigurationObject1->SetRtsEnable( false );
    lineInputDeviceConfigurationObject1->SetStopBits( StopBits::None );
    lineInputDeviceConfigurationObject1->SetWriteBufferSize( -1073702232L );
    lineInputDeviceConfigurationObject1->SetWriteTimeout( TimeSpan( -516494779736LL ) );
    lineInputDeviceConfigurationObject1->SetPairedComPort( L"PairedComPort" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *lineInputDeviceConfigurationObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto lineInputDeviceConfigurationObject2 = std::reinterpret_pointer_cast<LineInputDeviceConfigurationObject>( ReadDataFrom( source ) );
    bool equal = lineInputDeviceConfigurationObject2->IsEqualTo( *lineInputDeviceConfigurationObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LineInputMessageRoutingObjectSerializationTest
BOOST_AUTO_TEST_CASE( LineInputMessageRoutingObjectSerializationTest )
{
    auto lineInputMessageRoutingObject1 = std::make_shared<LineInputMessageRoutingObject>( );
    lineInputMessageRoutingObject1->SetId( Guid( L"{8BE6CF76-4CDD-BBC9-DD93-32BBD167F36E}" ) );
    lineInputMessageRoutingObject1->SetRowVersion( -4915313003879542922LL );
    lineInputMessageRoutingObject1->SetLineInputDevice( Guid( L"{8BE6CF76-4CDD-BBC9-DD93-32BBD167F36E}" ) );
    lineInputMessageRoutingObject1->SetType( L"Type" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *lineInputMessageRoutingObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto lineInputMessageRoutingObject2 = std::reinterpret_pointer_cast<LineInputMessageRoutingObject>( ReadDataFrom( source ) );
    bool equal = lineInputMessageRoutingObject2->IsEqualTo( *lineInputMessageRoutingObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LineInputMessageRoutingDestinationObjectSerializationTest
BOOST_AUTO_TEST_CASE( LineInputMessageRoutingDestinationObjectSerializationTest )
{
    auto lineInputMessageRoutingDestinationObject1 = std::make_shared<LineInputMessageRoutingDestinationObject>( );
    lineInputMessageRoutingDestinationObject1->SetId( Guid( L"{2EF5AC12-D26D-9FF4-F92F-4BB674AF3548}" ) );
    lineInputMessageRoutingDestinationObject1->SetRowVersion( -6920675360980489198LL );
    lineInputMessageRoutingDestinationObject1->SetRouting( Guid( L"{2EF5AC12-D26D-9FF4-F92F-4BB674AF3548}" ) );
    lineInputMessageRoutingDestinationObject1->SetListener( Guid( L"{2EF5AC12-D26D-9FF4-F92F-4BB674AF3548}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *lineInputMessageRoutingDestinationObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto lineInputMessageRoutingDestinationObject2 = std::reinterpret_pointer_cast<LineInputMessageRoutingDestinationObject>( ReadDataFrom( source ) );
    bool equal = lineInputMessageRoutingDestinationObject2->IsEqualTo( *lineInputMessageRoutingDestinationObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LineInputWhiteListEntryObjectSerializationTest
BOOST_AUTO_TEST_CASE( LineInputWhiteListEntryObjectSerializationTest )
{
    auto lineInputWhiteListEntryObject1 = std::make_shared<LineInputWhiteListEntryObject>( );
    lineInputWhiteListEntryObject1->SetId( Guid( L"{327EA7A3-FFDF-36F9-6C9F-FFFB4C7EE5C5}" ) );
    lineInputWhiteListEntryObject1->SetRowVersion( 3961478681339013027LL );
    lineInputWhiteListEntryObject1->SetLineInputDevice( Guid( L"{327EA7A3-FFDF-36F9-6C9F-FFFB4C7EE5C5}" ) );
    lineInputWhiteListEntryObject1->SetHostName( L"HostName" );
    lineInputWhiteListEntryObject1->SetPort( 847161251L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *lineInputWhiteListEntryObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto lineInputWhiteListEntryObject2 = std::reinterpret_pointer_cast<LineInputWhiteListEntryObject>( ReadDataFrom( source ) );
    bool equal = lineInputWhiteListEntryObject2->IsEqualTo( *lineInputWhiteListEntryObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LogApplicationObjectSerializationTest
BOOST_AUTO_TEST_CASE( LogApplicationObjectSerializationTest )
{
    auto logApplicationObject1 = std::make_shared<LogApplicationObject>( );
    logApplicationObject1->SetId( Guid( L"{6B1912D1-86E8-E10B-87D0-6117D698488B}" ) );
    logApplicationObject1->SetRowVersion( -2230540857644608815LL );
    logApplicationObject1->SetName( L"Name" );
    logApplicationObject1->SetDescription( L"Description" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *logApplicationObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto logApplicationObject2 = std::reinterpret_pointer_cast<LogApplicationObject>( ReadDataFrom( source ) );
    bool equal = logApplicationObject2->IsEqualTo( *logApplicationObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LogApplicationConfigurationObjectSerializationTest
BOOST_AUTO_TEST_CASE( LogApplicationConfigurationObjectSerializationTest )
{
    auto logApplicationConfigurationObject1 = std::make_shared<LogApplicationConfigurationObject>( );
    logApplicationConfigurationObject1->SetId( Guid( L"{CC4F6DA5-6ECC-B5D6-AD6B-763333F2B6A5}" ) );
    logApplicationConfigurationObject1->SetRowVersion( -5343962081948373595LL );
    logApplicationConfigurationObject1->SetApplication( Guid( L"{CC4F6DA5-6ECC-B5D6-AD6B-763333F2B6A5}" ) );
    logApplicationConfigurationObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    logApplicationConfigurationObject1->SetFinest( false );
    logApplicationConfigurationObject1->SetFiner( false );
    logApplicationConfigurationObject1->SetFine( false );
    logApplicationConfigurationObject1->SetInfo( false );
    logApplicationConfigurationObject1->SetNotice( false );
    logApplicationConfigurationObject1->SetWarn( false );
    logApplicationConfigurationObject1->SetError( false );
    logApplicationConfigurationObject1->SetSevere( false );
    logApplicationConfigurationObject1->SetCritical( false );
    logApplicationConfigurationObject1->SetAlert( false );
    logApplicationConfigurationObject1->SetFatal( false );
    logApplicationConfigurationObject1->SetEmergency( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *logApplicationConfigurationObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto logApplicationConfigurationObject2 = std::reinterpret_pointer_cast<LogApplicationConfigurationObject>( ReadDataFrom( source ) );
    bool equal = logApplicationConfigurationObject2->IsEqualTo( *logApplicationConfigurationObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LogHostObjectSerializationTest
BOOST_AUTO_TEST_CASE( LogHostObjectSerializationTest )
{
    auto logHostObject1 = std::make_shared<LogHostObject>( );
    logHostObject1->SetId( Guid( L"{DE9C7421-1369-3D83-BCC1-C8967B392E84}" ) );
    logHostObject1->SetRowVersion( 4432407803689989153LL );
    logHostObject1->SetComputerName( L"ComputerName" );
    logHostObject1->SetDescription( L"Description" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *logHostObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto logHostObject2 = std::reinterpret_pointer_cast<LogHostObject>( ReadDataFrom( source ) );
    bool equal = logHostObject2->IsEqualTo( *logHostObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LogHostConfigurationObjectSerializationTest
BOOST_AUTO_TEST_CASE( LogHostConfigurationObjectSerializationTest )
{
    auto logHostConfigurationObject1 = std::make_shared<LogHostConfigurationObject>( );
    logHostConfigurationObject1->SetId( Guid( L"{417B144E-3AC8-DAA0-5B05-5C1382DE2872}" ) );
    logHostConfigurationObject1->SetRowVersion( -2693087945401101234LL );
    logHostConfigurationObject1->SetHost( Guid( L"{417B144E-3AC8-DAA0-5B05-5C1382DE2872}" ) );
    logHostConfigurationObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    logHostConfigurationObject1->SetFinest( false );
    logHostConfigurationObject1->SetFiner( false );
    logHostConfigurationObject1->SetFine( false );
    logHostConfigurationObject1->SetInfo( false );
    logHostConfigurationObject1->SetNotice( false );
    logHostConfigurationObject1->SetWarn( false );
    logHostConfigurationObject1->SetError( false );
    logHostConfigurationObject1->SetSevere( false );
    logHostConfigurationObject1->SetCritical( false );
    logHostConfigurationObject1->SetAlert( false );
    logHostConfigurationObject1->SetFatal( false );
    logHostConfigurationObject1->SetEmergency( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *logHostConfigurationObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto logHostConfigurationObject2 = std::reinterpret_pointer_cast<LogHostConfigurationObject>( ReadDataFrom( source ) );
    bool equal = logHostConfigurationObject2->IsEqualTo( *logHostConfigurationObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LogLocationObjectSerializationTest
BOOST_AUTO_TEST_CASE( LogLocationObjectSerializationTest )
{
    auto logLocationObject1 = std::make_shared<LogLocationObject>( );
    logLocationObject1->SetId( Guid( L"{BE5DBC0F-C27F-12B7-48ED-43FE7DBA3DF0}" ) );
    logLocationObject1->SetRowVersion( 1348760467331202063LL );
    logLocationObject1->SetFileName( L"FileName" );
    logLocationObject1->SetLineNumber( -1101153265L );
    logLocationObject1->SetNamespace( L"Namespace" );
    logLocationObject1->SetClassName( L"ClassName" );
    logLocationObject1->SetMethodName( L"MethodName" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *logLocationObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto logLocationObject2 = std::reinterpret_pointer_cast<LogLocationObject>( ReadDataFrom( source ) );
    bool equal = logLocationObject2->IsEqualTo( *logLocationObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LogProcessObjectSerializationTest
BOOST_AUTO_TEST_CASE( LogProcessObjectSerializationTest )
{
    auto logProcessObject1 = std::make_shared<LogProcessObject>( );
    logProcessObject1->SetId( Guid( L"{7EC79CED-9256-C54D-A3B2-496A7EE339B7}" ) );
    logProcessObject1->SetRowVersion( -4229563574839173907LL );
    logProcessObject1->SetApplication( Guid( L"{7EC79CED-9256-C54D-A3B2-496A7EE339B7}" ) );
    logProcessObject1->SetHost( Guid( L"{7EC79CED-9256-C54D-A3B2-496A7EE339B7}" ) );
    logProcessObject1->SetStarted( DateTime( 1, 1, 1, 22, 23, 35 ) );
    logProcessObject1->SetStopped( DateTime( 1, 1, 1, 22, 23, 35 ) );
    logProcessObject1->SetProcessId( -4229563574839173907LL );
    logProcessObject1->SetPath( L"Path" );
    logProcessObject1->SetIdentity( L"Identity" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *logProcessObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto logProcessObject2 = std::reinterpret_pointer_cast<LogProcessObject>( ReadDataFrom( source ) );
    bool equal = logProcessObject2->IsEqualTo( *logProcessObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LogRecordObjectSerializationTest
BOOST_AUTO_TEST_CASE( LogRecordObjectSerializationTest )
{
    auto logRecordObject1 = std::make_shared<LogRecordObject>( );
    logRecordObject1->SetId( Guid( L"{28B6F7B7-3766-03C6-C063-EC66146DEFED}" ) );
    logRecordObject1->SetRowVersion( 271965739411765175LL );
    logRecordObject1->SetThread( Guid( L"{28B6F7B7-3766-03C6-C063-EC66146DEFED}" ) );
    logRecordObject1->SetSequenceNumber( 271965739411765175LL );
    logRecordObject1->SetLevel( LogLevel::Warn );
    logRecordObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    logRecordObject1->SetDepth( 683079607L );
    logRecordObject1->SetLocation( Guid( L"{28B6F7B7-3766-03C6-C063-EC66146DEFED}" ) );
    logRecordObject1->SetMessage( L"Message" );
    logRecordObject1->SetExceptionString( L"ExceptionString" );
    logRecordObject1->SetPropertiesData( { {'P','r','o','p','e','r','t','i','e','s','D','a','t','a'} } );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *logRecordObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto logRecordObject2 = std::reinterpret_pointer_cast<LogRecordObject>( ReadDataFrom( source ) );
    bool equal = logRecordObject2->IsEqualTo( *logRecordObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LogThreadObjectSerializationTest
BOOST_AUTO_TEST_CASE( LogThreadObjectSerializationTest )
{
    auto logThreadObject1 = std::make_shared<LogThreadObject>( );
    logThreadObject1->SetId( Guid( L"{04816AF0-B0B9-19C1-9883-0D9D2081560F}" ) );
    logThreadObject1->SetRowVersion( 1855958830144383728LL );
    logThreadObject1->SetProcess( Guid( L"{04816AF0-B0B9-19C1-9883-0D9D2081560F}" ) );
    logThreadObject1->SetStarted( DateTime( 1, 1, 1, 22, 23, 35 ) );
    logThreadObject1->SetStopped( DateTime( 1, 1, 1, 22, 23, 35 ) );
    logThreadObject1->SetThreadId( 1855958830144383728LL );
    logThreadObject1->SetName( L"Name" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *logThreadObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto logThreadObject2 = std::reinterpret_pointer_cast<LogThreadObject>( ReadDataFrom( source ) );
    bool equal = logThreadObject2->IsEqualTo( *logThreadObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LogTraceEntryObjectSerializationTest
BOOST_AUTO_TEST_CASE( LogTraceEntryObjectSerializationTest )
{
    auto logTraceEntryObject1 = std::make_shared<LogTraceEntryObject>( );
    logTraceEntryObject1->SetId( Guid( L"{4BF89F5F-7C98-DBAB-DBD5-3E19D21FF9FA}" ) );
    logTraceEntryObject1->SetRowVersion( -2617861764834353313LL );
    logTraceEntryObject1->SetThread( Guid( L"{4BF89F5F-7C98-DBAB-DBD5-3E19D21FF9FA}" ) );
    logTraceEntryObject1->SetSequenceNumber( -2617861764834353313LL );
    logTraceEntryObject1->SetLocation( Guid( L"{4BF89F5F-7C98-DBAB-DBD5-3E19D21FF9FA}" ) );
    logTraceEntryObject1->SetDepth( 1274584927L );
    logTraceEntryObject1->SetEntered( DateTime( 1, 1, 1, 22, 23, 35 ) );
    logTraceEntryObject1->SetEnded( DateTime( 1, 1, 1, 22, 23, 35 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *logTraceEntryObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto logTraceEntryObject2 = std::reinterpret_pointer_cast<LogTraceEntryObject>( ReadDataFrom( source ) );
    bool equal = logTraceEntryObject2->IsEqualTo( *logTraceEntryObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/MapElementObjectSerializationTest
BOOST_AUTO_TEST_CASE( MapElementObjectSerializationTest )
{
    auto mapElementObject1 = std::make_shared<MapElementObject>( );
    mapElementObject1->SetId( Guid( L"{6E1EB3AF-BD0A-A344-C522-BD507678CDF5}" ) );
    mapElementObject1->SetRowVersion( -6682008094616144977LL );
    mapElementObject1->SetItem( Guid( L"{6E1EB3AF-BD0A-A344-C522-BD507678CDF5}" ) );
    mapElementObject1->SetElementType( MapElementType::Jpeg );
    mapElementObject1->SetLatitude( 11764735979093406 );
    mapElementObject1->SetLongitude( 11764735979093406 );
    mapElementObject1->SetAngle( 11764735979093406 );
    mapElementObject1->SetLeft( 11764735979093406 );
    mapElementObject1->SetTop( 11764735979093406 );
    mapElementObject1->SetWidth( 11764735979093406 );
    mapElementObject1->SetHeight( 11764735979093406 );
    mapElementObject1->SetLabel( L"Label" );
    mapElementObject1->SetData( { {'D','a','t','a'} } );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *mapElementObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto mapElementObject2 = std::reinterpret_pointer_cast<MapElementObject>( ReadDataFrom( source ) );
    bool equal = mapElementObject2->IsEqualTo( *mapElementObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/MapInfoObjectSerializationTest
BOOST_AUTO_TEST_CASE( MapInfoObjectSerializationTest )
{
    auto mapInfoObject1 = std::make_shared<MapInfoObject>( );
    mapInfoObject1->SetId( Guid( L"{EA12A4F5-45A0-1A32-584C-A205574825AF}" ) );
    mapInfoObject1->SetRowVersion( 1887647751245833461LL );
    mapInfoObject1->SetScale( -367876875L );
    mapInfoObject1->SetLatitude( 1887647751245833.5 );
    mapInfoObject1->SetLongitude( 1887647751245833.5 );
    mapInfoObject1->SetNorthWestLatitude( 1887647751245833.5 );
    mapInfoObject1->SetNorthWestLongitude( 1887647751245833.5 );
    mapInfoObject1->SetSouthEastLatitude( 1887647751245833.5 );
    mapInfoObject1->SetSouthEastLongitude( 1887647751245833.5 );
    mapInfoObject1->SetImage( { {'I','m','a','g','e'} } );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *mapInfoObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto mapInfoObject2 = std::reinterpret_pointer_cast<MapInfoObject>( ReadDataFrom( source ) );
    bool equal = mapInfoObject2->IsEqualTo( *mapInfoObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/MapServiceOptionsObjectSerializationTest
BOOST_AUTO_TEST_CASE( MapServiceOptionsObjectSerializationTest )
{
    auto mapServiceOptionsObject1 = std::make_shared<MapServiceOptionsObject>( );
    mapServiceOptionsObject1->SetId( Guid( L"{20E6AB7D-3887-E6FB-67DF-1CE10467D5BE}" ) );
    mapServiceOptionsObject1->SetRowVersion( -1802785072808023171LL );
    mapServiceOptionsObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    mapServiceOptionsObject1->SetIpAddress( L"IpAddress" );
    mapServiceOptionsObject1->SetPort( 551988093L );
    mapServiceOptionsObject1->SetImageScaleFactorX( 16643959000901528 );
    mapServiceOptionsObject1->SetImageOffsetX( 16643959000901528 );
    mapServiceOptionsObject1->SetImageScaleFactorY( 16643959000901528 );
    mapServiceOptionsObject1->SetImageOffsetY( 16643959000901528 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *mapServiceOptionsObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto mapServiceOptionsObject2 = std::reinterpret_pointer_cast<MapServiceOptionsObject>( ReadDataFrom( source ) );
    bool equal = mapServiceOptionsObject2->IsEqualTo( *mapServiceOptionsObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/MaritimeIdentificationDigitsObjectSerializationTest
BOOST_AUTO_TEST_CASE( MaritimeIdentificationDigitsObjectSerializationTest )
{
    auto maritimeIdentificationDigitsObject1 = std::make_shared<MaritimeIdentificationDigitsObject>( );
    maritimeIdentificationDigitsObject1->SetId( Guid( L"{33551387-00CF-4F0D-F2B0-00F3CCAAC8E1}" ) );
    maritimeIdentificationDigitsObject1->SetRowVersion( 5696209993612989319LL );
    maritimeIdentificationDigitsObject1->SetCode( 861213575L );
    maritimeIdentificationDigitsObject1->SetCountry( Guid( L"{33551387-00CF-4F0D-F2B0-00F3CCAAC8E1}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *maritimeIdentificationDigitsObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto maritimeIdentificationDigitsObject2 = std::reinterpret_pointer_cast<MaritimeIdentificationDigitsObject>( ReadDataFrom( source ) );
    bool equal = maritimeIdentificationDigitsObject2->IsEqualTo( *maritimeIdentificationDigitsObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/MediaProxySessionObjectSerializationTest
BOOST_AUTO_TEST_CASE( MediaProxySessionObjectSerializationTest )
{
    auto mediaProxySessionObject1 = std::make_shared<MediaProxySessionObject>( );
    mediaProxySessionObject1->SetId( Guid( L"{F09CC571-97B0-5F8C-FA31-E90D0F39A38E}" ) );
    mediaProxySessionObject1->SetRowVersion( 6885044716549490033LL );
    mediaProxySessionObject1->SetService( Guid( L"{F09CC571-97B0-5F8C-FA31-E90D0F39A38E}" ) );
    mediaProxySessionObject1->SetName( L"Name" );
    mediaProxySessionObject1->SetEnabledTimeseries( Guid( L"{F09CC571-97B0-5F8C-FA31-E90D0F39A38E}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *mediaProxySessionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto mediaProxySessionObject2 = std::reinterpret_pointer_cast<MediaProxySessionObject>( ReadDataFrom( source ) );
    bool equal = mediaProxySessionObject2->IsEqualTo( *mediaProxySessionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/MediaProxySessionFileObjectSerializationTest
BOOST_AUTO_TEST_CASE( MediaProxySessionFileObjectSerializationTest )
{
    auto mediaProxySessionFileObject1 = std::make_shared<MediaProxySessionFileObject>( );
    mediaProxySessionFileObject1->SetId( Guid( L"{8E158396-1682-3D78-BC1E-684171A8C169}" ) );
    mediaProxySessionFileObject1->SetRowVersion( 4429314983504216982LL );
    mediaProxySessionFileObject1->SetProxySession( Guid( L"{8E158396-1682-3D78-BC1E-684171A8C169}" ) );
    mediaProxySessionFileObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    mediaProxySessionFileObject1->SetStreamName( L"StreamName" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *mediaProxySessionFileObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto mediaProxySessionFileObject2 = std::reinterpret_pointer_cast<MediaProxySessionFileObject>( ReadDataFrom( source ) );
    bool equal = mediaProxySessionFileObject2->IsEqualTo( *mediaProxySessionFileObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/MediaProxySessionOptionsObjectSerializationTest
BOOST_AUTO_TEST_CASE( MediaProxySessionOptionsObjectSerializationTest )
{
    auto mediaProxySessionOptionsObject1 = std::make_shared<MediaProxySessionOptionsObject>( );
    mediaProxySessionOptionsObject1->SetId( Guid( L"{EDD260D0-4C90-FC60-3F06-3209B74B060B}" ) );
    mediaProxySessionOptionsObject1->SetRowVersion( -261124593038499632LL );
    mediaProxySessionOptionsObject1->SetProxySession( Guid( L"{EDD260D0-4C90-FC60-3F06-3209B74B060B}" ) );
    mediaProxySessionOptionsObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    mediaProxySessionOptionsObject1->SetSourceStreamUrl( L"SourceStreamUrl" );
    mediaProxySessionOptionsObject1->SetStreamName( L"StreamName" );
    mediaProxySessionOptionsObject1->SetMode( MediaProxySessionMode::Unknown );
    mediaProxySessionOptionsObject1->SetTunnelOverHTTPPortNumber( -304979760L );
    mediaProxySessionOptionsObject1->SetUsername( L"Username" );
    mediaProxySessionOptionsObject1->SetPassword( L"Password" );
    mediaProxySessionOptionsObject1->SetRecorderPortNumber( -304979760L );
    mediaProxySessionOptionsObject1->SetSessionType( MediaProxySessionType::AC3Audio );
    mediaProxySessionOptionsObject1->SetMaxFileTime( TimeSpan( -465038499632LL ) );
    mediaProxySessionOptionsObject1->SetMaxFileRetention( TimeSpan( -465038499632LL ) );
    mediaProxySessionOptionsObject1->SetVideoDirectory( L"VideoDirectory" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *mediaProxySessionOptionsObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto mediaProxySessionOptionsObject2 = std::reinterpret_pointer_cast<MediaProxySessionOptionsObject>( ReadDataFrom( source ) );
    bool equal = mediaProxySessionOptionsObject2->IsEqualTo( *mediaProxySessionOptionsObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/MediaServiceObjectSerializationTest
BOOST_AUTO_TEST_CASE( MediaServiceObjectSerializationTest )
{
    auto mediaServiceObject1 = std::make_shared<MediaServiceObject>( );
    mediaServiceObject1->SetId( Guid( L"{96926964-A9F1-8383-C1C1-958F69499626}" ) );
    mediaServiceObject1->SetRowVersion( -8970139177713505948LL );
    mediaServiceObject1->SetEnabledTimeseries( Guid( L"{96926964-A9F1-8383-C1C1-958F69499626}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *mediaServiceObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto mediaServiceObject2 = std::reinterpret_pointer_cast<MediaServiceObject>( ReadDataFrom( source ) );
    bool equal = mediaServiceObject2->IsEqualTo( *mediaServiceObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/MediaServiceOptionsObjectSerializationTest
BOOST_AUTO_TEST_CASE( MediaServiceOptionsObjectSerializationTest )
{
    auto mediaServiceOptionsObject1 = std::make_shared<MediaServiceOptionsObject>( );
    mediaServiceOptionsObject1->SetId( Guid( L"{0A8CEF15-C6AB-65EC-A637-63D55031F7A8}" ) );
    mediaServiceOptionsObject1->SetRowVersion( 7344463530253152021LL );
    mediaServiceOptionsObject1->SetMediaService( Guid( L"{0A8CEF15-C6AB-65EC-A637-63D55031F7A8}" ) );
    mediaServiceOptionsObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    mediaServiceOptionsObject1->SetRtspPortNumber( 177008405L );
    mediaServiceOptionsObject1->SetHttpPortNumber( 177008405L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *mediaServiceOptionsObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto mediaServiceOptionsObject2 = std::reinterpret_pointer_cast<MediaServiceOptionsObject>( ReadDataFrom( source ) );
    bool equal = mediaServiceOptionsObject2->IsEqualTo( *mediaServiceOptionsObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ElementTypeObjectSerializationTest
BOOST_AUTO_TEST_CASE( ElementTypeObjectSerializationTest )
{
    auto elementTypeObject1 = std::make_shared<ElementTypeObject>( );
    elementTypeObject1->SetId( Guid( L"{7DD5914D-321B-4C6A-3256-4CD8BEAB89B2}" ) );
    elementTypeObject1->SetRowVersion( 5506268588070506829LL );
    elementTypeObject1->SetNamespace( Guid( L"{7DD5914D-321B-4C6A-3256-4CD8BEAB89B2}" ) );
    elementTypeObject1->SetName( L"Name" );
    elementTypeObject1->SetDescription( L"Description" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *elementTypeObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto elementTypeObject2 = std::reinterpret_pointer_cast<ElementTypeObject>( ReadDataFrom( source ) );
    bool equal = elementTypeObject2->IsEqualTo( *elementTypeObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/NamespaceObjectSerializationTest
BOOST_AUTO_TEST_CASE( NamespaceObjectSerializationTest )
{
    auto namespaceObject1 = std::make_shared<NamespaceObject>( );
    namespaceObject1->SetId( Guid( L"{22456B64-FD81-0793-E0C9-BF8144A2D626}" ) );
    namespaceObject1->SetRowVersion( 546058710909545316LL );
    namespaceObject1->SetNamespace( Guid( L"{22456B64-FD81-0793-E0C9-BF8144A2D626}" ) );
    namespaceObject1->SetName( L"Name" );
    namespaceObject1->SetDescription( L"Description" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *namespaceObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto namespaceObject2 = std::reinterpret_pointer_cast<NamespaceObject>( ReadDataFrom( source ) );
    bool equal = namespaceObject2->IsEqualTo( *namespaceObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/OilSpillObjectSerializationTest
BOOST_AUTO_TEST_CASE( OilSpillObjectSerializationTest )
{
    auto oilSpillObject1 = std::make_shared<OilSpillObject>( );
    oilSpillObject1->SetId( Guid( L"{4F2942F2-FB55-83FB-C1DF-DFAAF294424F}" ) );
    oilSpillObject1->SetRowVersion( -8936272691767721230LL );
    oilSpillObject1->SetOilSpillDetector( Guid( L"{4F2942F2-FB55-83FB-C1DF-DFAAF294424F}" ) );
    oilSpillObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    oilSpillObject1->SetOilArea( 9510471381941830 );
    oilSpillObject1->SetShape( { {'S','h','a','p','e'} } );
    oilSpillObject1->SetBSI( { {'B','S','I'} } );
    oilSpillObject1->SetOil( { {'O','i','l'} } );
    oilSpillObject1->SetTrace( { {'T','r','a','c','e'} } );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *oilSpillObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto oilSpillObject2 = std::reinterpret_pointer_cast<OilSpillObject>( ReadDataFrom( source ) );
    bool equal = oilSpillObject2->IsEqualTo( *oilSpillObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/OilSpillDetectorCommandObjectSerializationTest
BOOST_AUTO_TEST_CASE( OilSpillDetectorCommandObjectSerializationTest )
{
    auto oilSpillDetectorCommandObject1 = std::make_shared<OilSpillDetectorCommandObject>( );
    oilSpillDetectorCommandObject1->SetId( Guid( L"{56F5EB57-7713-940A-2950-EEC86AAFD7EA}" ) );
    oilSpillDetectorCommandObject1->SetRowVersion( -7779274481382069417LL );
    oilSpillDetectorCommandObject1->SetOilSpillDetector( Guid( L"{56F5EB57-7713-940A-2950-EEC86AAFD7EA}" ) );
    oilSpillDetectorCommandObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    oilSpillDetectorCommandObject1->SetDeviceCommandSourceType( DeviceCommandSourceType::Source );
    oilSpillDetectorCommandObject1->SetDeviceCommandSourceId( Guid( L"{56F5EB57-7713-940A-2950-EEC86AAFD7EA}" ) );
    oilSpillDetectorCommandObject1->SetReply( Guid( L"{56F5EB57-7713-940A-2950-EEC86AAFD7EA}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *oilSpillDetectorCommandObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto oilSpillDetectorCommandObject2 = std::reinterpret_pointer_cast<OilSpillDetectorCommandObject>( ReadDataFrom( source ) );
    bool equal = oilSpillDetectorCommandObject2->IsEqualTo( *oilSpillDetectorCommandObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/OilSpillDetectorCommandReplyObjectSerializationTest
BOOST_AUTO_TEST_CASE( OilSpillDetectorCommandReplyObjectSerializationTest )
{
    auto oilSpillDetectorCommandReplyObject1 = std::make_shared<OilSpillDetectorCommandReplyObject>( );
    oilSpillDetectorCommandReplyObject1->SetId( Guid( L"{ADEF8281-2DE0-5BF1-DA8F-B407B5F74181}" ) );
    oilSpillDetectorCommandReplyObject1->SetRowVersion( 6625126969852789377LL );
    oilSpillDetectorCommandReplyObject1->SetOilSpillDetector( Guid( L"{ADEF8281-2DE0-5BF1-DA8F-B407B5F74181}" ) );
    oilSpillDetectorCommandReplyObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    oilSpillDetectorCommandReplyObject1->SetCommand( Guid( L"{ADEF8281-2DE0-5BF1-DA8F-B407B5F74181}" ) );
    oilSpillDetectorCommandReplyObject1->SetStatus( DeviceCommandReplyStatus::Ok );
    oilSpillDetectorCommandReplyObject1->SetMessage( L"Message" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *oilSpillDetectorCommandReplyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto oilSpillDetectorCommandReplyObject2 = std::reinterpret_pointer_cast<OilSpillDetectorCommandReplyObject>( ReadDataFrom( source ) );
    bool equal = oilSpillDetectorCommandReplyObject2->IsEqualTo( *oilSpillDetectorCommandReplyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/OilSpillDetectorConfigurationObjectSerializationTest
BOOST_AUTO_TEST_CASE( OilSpillDetectorConfigurationObjectSerializationTest )
{
    auto oilSpillDetectorConfigurationObject1 = std::make_shared<OilSpillDetectorConfigurationObject>( );
    oilSpillDetectorConfigurationObject1->SetId( Guid( L"{4FF652FA-2908-F7CF-EFF3-9410F26F4A5F}" ) );
    oilSpillDetectorConfigurationObject1->SetRowVersion( -590207910484225286LL );
    oilSpillDetectorConfigurationObject1->SetOilSpillDetector( Guid( L"{4FF652FA-2908-F7CF-EFF3-9410F26F4A5F}" ) );
    oilSpillDetectorConfigurationObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    oilSpillDetectorConfigurationObject1->SetRange( 17856536163225326 );
    oilSpillDetectorConfigurationObject1->SetStartAngle( 17856536163225326 );
    oilSpillDetectorConfigurationObject1->SetEndAngle( 17856536163225326 );
    oilSpillDetectorConfigurationObject1->SetStartRange( 17856536163225326 );
    oilSpillDetectorConfigurationObject1->SetEndRange( 17856536163225326 );
    oilSpillDetectorConfigurationObject1->SetUpdateRate( 1341543162L );
    oilSpillDetectorConfigurationObject1->SetStatusSendTime( TimeSpan( -6484225286LL ) );
    oilSpillDetectorConfigurationObject1->SetDrawBorder( false );
    oilSpillDetectorConfigurationObject1->SetColors( { {'C','o','l','o','r','s'} } );
    oilSpillDetectorConfigurationObject1->SetSendToServer( false );
    oilSpillDetectorConfigurationObject1->SetDirectory( L"Directory" );
    oilSpillDetectorConfigurationObject1->SetTransparentWater( false );
    oilSpillDetectorConfigurationObject1->SetSavePictures( false );
    oilSpillDetectorConfigurationObject1->SetSendAsTarget( false );
    oilSpillDetectorConfigurationObject1->SetWriteLog( false );
    oilSpillDetectorConfigurationObject1->SetTargetFilePrefix( L"TargetFilePrefix" );
    oilSpillDetectorConfigurationObject1->SetTargetMMSI( Guid( L"{4FF652FA-2908-F7CF-EFF3-9410F26F4A5F}" ) );
    oilSpillDetectorConfigurationObject1->SetLatitude( 17856536163225326 );
    oilSpillDetectorConfigurationObject1->SetLongitude( 17856536163225326 );
    oilSpillDetectorConfigurationObject1->SetTestSourceEnabled( false );
    oilSpillDetectorConfigurationObject1->SetProxyServer( L"ProxyServer" );
    oilSpillDetectorConfigurationObject1->SetUseProxyServer( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *oilSpillDetectorConfigurationObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto oilSpillDetectorConfigurationObject2 = std::reinterpret_pointer_cast<OilSpillDetectorConfigurationObject>( ReadDataFrom( source ) );
    bool equal = oilSpillDetectorConfigurationObject2->IsEqualTo( *oilSpillDetectorConfigurationObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Position2DTimeseriesValueObjectSerializationTest
BOOST_AUTO_TEST_CASE( Position2DTimeseriesValueObjectSerializationTest )
{
    auto position2DTimeseriesValueObject1 = std::make_shared<Position2DTimeseriesValueObject>( );
    position2DTimeseriesValueObject1->SetId( Guid( L"{0E8E2416-D3F0-2D94-B429-CB0F70712468}" ) );
    position2DTimeseriesValueObject1->SetRowVersion( 3284483056249742358LL );
    position2DTimeseriesValueObject1->SetTimeseries( Guid( L"{0E8E2416-D3F0-2D94-B429-CB0F70712468}" ) );
    position2DTimeseriesValueObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    position2DTimeseriesValueObject1->SetX( 3284483056249742.5 );
    position2DTimeseriesValueObject1->SetY( 3284483056249742.5 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *position2DTimeseriesValueObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto position2DTimeseriesValueObject2 = std::reinterpret_pointer_cast<Position2DTimeseriesValueObject>( ReadDataFrom( source ) );
    bool equal = position2DTimeseriesValueObject2->IsEqualTo( *position2DTimeseriesValueObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Position3DTimeseriesValueObjectSerializationTest
BOOST_AUTO_TEST_CASE( Position3DTimeseriesValueObjectSerializationTest )
{
    auto position3DTimeseriesValueObject1 = std::make_shared<Position3DTimeseriesValueObject>( );
    position3DTimeseriesValueObject1->SetId( Guid( L"{270243BC-C575-4E4D-72B2-A3AEE440C23D}" ) );
    position3DTimeseriesValueObject1->SetRowVersion( 5642383015121404860LL );
    position3DTimeseriesValueObject1->SetTimeseries( Guid( L"{270243BC-C575-4E4D-72B2-A3AEE440C23D}" ) );
    position3DTimeseriesValueObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    position3DTimeseriesValueObject1->SetX( 5642383015121405 );
    position3DTimeseriesValueObject1->SetY( 5642383015121405 );
    position3DTimeseriesValueObject1->SetZ( 5642383015121405 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *position3DTimeseriesValueObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto position3DTimeseriesValueObject2 = std::reinterpret_pointer_cast<Position3DTimeseriesValueObject>( ReadDataFrom( source ) );
    bool equal = position3DTimeseriesValueObject2->IsEqualTo( *position3DTimeseriesValueObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ProcessTrackValueResultObjectSerializationTest
BOOST_AUTO_TEST_CASE( ProcessTrackValueResultObjectSerializationTest )
{
    auto processTrackValueResultObject1 = std::make_shared<ProcessTrackValueResultObject>( );
    processTrackValueResultObject1->SetId( Guid( L"{76103E7F-D776-7399-CE99-EB6E6E087CFE}" ) );
    processTrackValueResultObject1->SetRowVersion( 8329925889585331839LL );
    processTrackValueResultObject1->SetCreatedNewTrack( false );
    processTrackValueResultObject1->SetTrackId( Guid( L"{76103E7F-D776-7399-CE99-EB6E6E087CFE}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *processTrackValueResultObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto processTrackValueResultObject2 = std::reinterpret_pointer_cast<ProcessTrackValueResultObject>( ReadDataFrom( source ) );
    bool equal = processTrackValueResultObject2->IsEqualTo( *processTrackValueResultObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BinaryPropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( BinaryPropertyObjectSerializationTest )
{
    auto binaryPropertyObject1 = std::make_shared<BinaryPropertyObject>( );
    binaryPropertyObject1->SetId( Guid( L"{747B8E31-4658-5C2A-3A54-621A2EDE718C}" ) );
    binaryPropertyObject1->SetRowVersion( 6641197946236538417LL );
    binaryPropertyObject1->SetElement( Guid( L"{747B8E31-4658-5C2A-3A54-621A2EDE718C}" ) );
    binaryPropertyObject1->SetDefinition( Guid( L"{747B8E31-4658-5C2A-3A54-621A2EDE718C}" ) );
    binaryPropertyObject1->SetValue( { {'V','a','l','u','e'} } );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *binaryPropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto binaryPropertyObject2 = std::reinterpret_pointer_cast<BinaryPropertyObject>( ReadDataFrom( source ) );
    bool equal = binaryPropertyObject2->IsEqualTo( *binaryPropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BooleanPropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( BooleanPropertyObjectSerializationTest )
{
    auto booleanPropertyObject1 = std::make_shared<BooleanPropertyObject>( );
    booleanPropertyObject1->SetId( Guid( L"{5164C464-F83B-6804-1620-1FDC8A262326}" ) );
    booleanPropertyObject1->SetRowVersion( 7495388613503665252LL );
    booleanPropertyObject1->SetElement( Guid( L"{5164C464-F83B-6804-1620-1FDC8A262326}" ) );
    booleanPropertyObject1->SetDefinition( Guid( L"{5164C464-F83B-6804-1620-1FDC8A262326}" ) );
    booleanPropertyObject1->SetValue( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *booleanPropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto booleanPropertyObject2 = std::reinterpret_pointer_cast<BooleanPropertyObject>( ReadDataFrom( source ) );
    bool equal = booleanPropertyObject2->IsEqualTo( *booleanPropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BytePropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( BytePropertyObjectSerializationTest )
{
    auto bytePropertyObject1 = std::make_shared<BytePropertyObject>( );
    bytePropertyObject1->SetId( Guid( L"{D8C7B657-C0AD-2F51-F48A-03B51BE36DEA}" ) );
    bytePropertyObject1->SetRowVersion( 3409718245795018327LL );
    bytePropertyObject1->SetElement( Guid( L"{D8C7B657-C0AD-2F51-F48A-03B51BE36DEA}" ) );
    bytePropertyObject1->SetDefinition( Guid( L"{D8C7B657-C0AD-2F51-F48A-03B51BE36DEA}" ) );
    bytePropertyObject1->SetValue( 87 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *bytePropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto bytePropertyObject2 = std::reinterpret_pointer_cast<BytePropertyObject>( ReadDataFrom( source ) );
    bool equal = bytePropertyObject2->IsEqualTo( *bytePropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DateTimePropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( DateTimePropertyObjectSerializationTest )
{
    auto dateTimePropertyObject1 = std::make_shared<DateTimePropertyObject>( );
    dateTimePropertyObject1->SetId( Guid( L"{87260D24-A955-FE46-7F62-95AAE164B024}" ) );
    dateTimePropertyObject1->SetRowVersion( -124225754901377756LL );
    dateTimePropertyObject1->SetElement( Guid( L"{87260D24-A955-FE46-7F62-95AAE164B024}" ) );
    dateTimePropertyObject1->SetDefinition( Guid( L"{87260D24-A955-FE46-7F62-95AAE164B024}" ) );
    dateTimePropertyObject1->SetValue( DateTime( 1, 1, 1, 22, 23, 35 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *dateTimePropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto dateTimePropertyObject2 = std::reinterpret_pointer_cast<DateTimePropertyObject>( ReadDataFrom( source ) );
    bool equal = dateTimePropertyObject2->IsEqualTo( *dateTimePropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DoublePropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( DoublePropertyObjectSerializationTest )
{
    auto doublePropertyObject1 = std::make_shared<DoublePropertyObject>( );
    doublePropertyObject1->SetId( Guid( L"{F3FF9E77-DBCB-C180-8301-DBD3CFFF79EE}" ) );
    doublePropertyObject1->SetRowVersion( -4503357958352036233LL );
    doublePropertyObject1->SetElement( Guid( L"{F3FF9E77-DBCB-C180-8301-DBD3CFFF79EE}" ) );
    doublePropertyObject1->SetDefinition( Guid( L"{F3FF9E77-DBCB-C180-8301-DBD3CFFF79EE}" ) );
    doublePropertyObject1->SetValue( 13943386115357516 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *doublePropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto doublePropertyObject2 = std::reinterpret_pointer_cast<DoublePropertyObject>( ReadDataFrom( source ) );
    bool equal = doublePropertyObject2->IsEqualTo( *doublePropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GuidPropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( GuidPropertyObjectSerializationTest )
{
    auto guidPropertyObject1 = std::make_shared<GuidPropertyObject>( );
    guidPropertyObject1->SetId( Guid( L"{97B3A99D-DD74-2C62-3446-BB2EE9CD95B9}" ) );
    guidPropertyObject1->SetRowVersion( 3198362178217552285LL );
    guidPropertyObject1->SetElement( Guid( L"{97B3A99D-DD74-2C62-3446-BB2EE9CD95B9}" ) );
    guidPropertyObject1->SetDefinition( Guid( L"{97B3A99D-DD74-2C62-3446-BB2EE9CD95B9}" ) );
    guidPropertyObject1->SetValue( Guid( L"{97B3A99D-DD74-2C62-3446-BB2EE9CD95B9}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *guidPropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto guidPropertyObject2 = std::reinterpret_pointer_cast<GuidPropertyObject>( ReadDataFrom( source ) );
    bool equal = guidPropertyObject2->IsEqualTo( *guidPropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int16PropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( Int16PropertyObjectSerializationTest )
{
    auto int16PropertyObject1 = std::make_shared<Int16PropertyObject>( );
    int16PropertyObject1->SetId( Guid( L"{A9634D36-BFAF-58DB-1ADB-FDF595C6B26C}" ) );
    int16PropertyObject1->SetRowVersion( 6402922056419331382LL );
    int16PropertyObject1->SetElement( Guid( L"{A9634D36-BFAF-58DB-1ADB-FDF595C6B26C}" ) );
    int16PropertyObject1->SetDefinition( Guid( L"{A9634D36-BFAF-58DB-1ADB-FDF595C6B26C}" ) );
    int16PropertyObject1->SetValue( 19766 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int16PropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int16PropertyObject2 = std::reinterpret_pointer_cast<Int16PropertyObject>( ReadDataFrom( source ) );
    bool equal = int16PropertyObject2->IsEqualTo( *int16PropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int32PropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( Int32PropertyObjectSerializationTest )
{
    auto int32PropertyObject1 = std::make_shared<Int32PropertyObject>( );
    int32PropertyObject1->SetId( Guid( L"{6590A2E0-72D1-937B-C9DE-4E8BA6094507}" ) );
    int32PropertyObject1->SetRowVersion( -7819530084321025312LL );
    int32PropertyObject1->SetElement( Guid( L"{6590A2E0-72D1-937B-C9DE-4E8BA6094507}" ) );
    int32PropertyObject1->SetDefinition( Guid( L"{6590A2E0-72D1-937B-C9DE-4E8BA6094507}" ) );
    int32PropertyObject1->SetValue( 1703977696L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int32PropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int32PropertyObject2 = std::reinterpret_pointer_cast<Int32PropertyObject>( ReadDataFrom( source ) );
    bool equal = int32PropertyObject2->IsEqualTo( *int32PropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int64PropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( Int64PropertyObjectSerializationTest )
{
    auto int64PropertyObject1 = std::make_shared<Int64PropertyObject>( );
    int64PropertyObject1->SetId( Guid( L"{29A86AC9-09F6-8315-C1A8-906F94155693}" ) );
    int64PropertyObject1->SetRowVersion( -9001277327364560183LL );
    int64PropertyObject1->SetElement( Guid( L"{29A86AC9-09F6-8315-C1A8-906F94155693}" ) );
    int64PropertyObject1->SetDefinition( Guid( L"{29A86AC9-09F6-8315-C1A8-906F94155693}" ) );
    int64PropertyObject1->SetValue( -9001277327364560183LL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int64PropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int64PropertyObject2 = std::reinterpret_pointer_cast<Int64PropertyObject>( ReadDataFrom( source ) );
    bool equal = int64PropertyObject2->IsEqualTo( *int64PropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ReferencePropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( ReferencePropertyObjectSerializationTest )
{
    auto referencePropertyObject1 = std::make_shared<ReferencePropertyObject>( );
    referencePropertyObject1->SetId( Guid( L"{4EFFC952-D252-ACBA-355D-4B4A72FF934A}" ) );
    referencePropertyObject1->SetRowVersion( -6000252302563227310LL );
    referencePropertyObject1->SetElement( Guid( L"{4EFFC952-D252-ACBA-355D-4B4A72FF934A}" ) );
    referencePropertyObject1->SetDefinition( Guid( L"{4EFFC952-D252-ACBA-355D-4B4A72FF934A}" ) );
    referencePropertyObject1->SetValue( Guid( L"{4EFFC952-D252-ACBA-355D-4B4A72FF934A}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *referencePropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto referencePropertyObject2 = std::reinterpret_pointer_cast<ReferencePropertyObject>( ReadDataFrom( source ) );
    bool equal = referencePropertyObject2->IsEqualTo( *referencePropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SBytePropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( SBytePropertyObjectSerializationTest )
{
    auto sBytePropertyObject1 = std::make_shared<SBytePropertyObject>( );
    sBytePropertyObject1->SetId( Guid( L"{1AC6643B-9E67-F251-4F8A-79E6586326DC}" ) );
    sBytePropertyObject1->SetRowVersion( -985832677749398469LL );
    sBytePropertyObject1->SetElement( Guid( L"{1AC6643B-9E67-F251-4F8A-79E6586326DC}" ) );
    sBytePropertyObject1->SetDefinition( Guid( L"{1AC6643B-9E67-F251-4F8A-79E6586326DC}" ) );
    sBytePropertyObject1->SetValue( 59 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *sBytePropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto sBytePropertyObject2 = std::reinterpret_pointer_cast<SBytePropertyObject>( ReadDataFrom( source ) );
    bool equal = sBytePropertyObject2->IsEqualTo( *sBytePropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SinglePropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( SinglePropertyObjectSerializationTest )
{
    auto singlePropertyObject1 = std::make_shared<SinglePropertyObject>( );
    singlePropertyObject1->SetId( Guid( L"{14D2D7C2-DC46-937B-C9DE-3B62284BEB43}" ) );
    singlePropertyObject1->SetRowVersion( -7819414134443550782LL );
    singlePropertyObject1->SetElement( Guid( L"{14D2D7C2-DC46-937B-C9DE-3B62284BEB43}" ) );
    singlePropertyObject1->SetDefinition( Guid( L"{14D2D7C2-DC46-937B-C9DE-3B62284BEB43}" ) );
    singlePropertyObject1->SetValue( 1.062733e+16f );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *singlePropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto singlePropertyObject2 = std::reinterpret_pointer_cast<SinglePropertyObject>( ReadDataFrom( source ) );
    bool equal = singlePropertyObject2->IsEqualTo( *singlePropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/StringPropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( StringPropertyObjectSerializationTest )
{
    auto stringPropertyObject1 = std::make_shared<StringPropertyObject>( );
    stringPropertyObject1->SetId( Guid( L"{1C84C0E4-3981-B9DD-9DBB-9C8138210327}" ) );
    stringPropertyObject1->SetRowVersion( -5053819980147801884LL );
    stringPropertyObject1->SetElement( Guid( L"{1C84C0E4-3981-B9DD-9DBB-9C8138210327}" ) );
    stringPropertyObject1->SetDefinition( Guid( L"{1C84C0E4-3981-B9DD-9DBB-9C8138210327}" ) );
    stringPropertyObject1->SetValue( L"Value" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *stringPropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto stringPropertyObject2 = std::reinterpret_pointer_cast<StringPropertyObject>( ReadDataFrom( source ) );
    bool equal = stringPropertyObject2->IsEqualTo( *stringPropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BinaryTimeseriesPropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( BinaryTimeseriesPropertyObjectSerializationTest )
{
    auto binaryTimeseriesPropertyObject1 = std::make_shared<BinaryTimeseriesPropertyObject>( );
    binaryTimeseriesPropertyObject1->SetId( Guid( L"{0E924FA4-5DBA-985D-19BA-BA5D7049F225}" ) );
    binaryTimeseriesPropertyObject1->SetRowVersion( -7467709553420644444LL );
    binaryTimeseriesPropertyObject1->SetElement( Guid( L"{0E924FA4-5DBA-985D-19BA-BA5D7049F225}" ) );
    binaryTimeseriesPropertyObject1->SetDefinition( Guid( L"{0E924FA4-5DBA-985D-19BA-BA5D7049F225}" ) );
    binaryTimeseriesPropertyObject1->SetTimeseries( Guid( L"{0E924FA4-5DBA-985D-19BA-BA5D7049F225}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *binaryTimeseriesPropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto binaryTimeseriesPropertyObject2 = std::reinterpret_pointer_cast<BinaryTimeseriesPropertyObject>( ReadDataFrom( source ) );
    bool equal = binaryTimeseriesPropertyObject2->IsEqualTo( *binaryTimeseriesPropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BooleanTimeseriesPropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( BooleanTimeseriesPropertyObjectSerializationTest )
{
    auto booleanTimeseriesPropertyObject1 = std::make_shared<BooleanTimeseriesPropertyObject>( );
    booleanTimeseriesPropertyObject1->SetId( Guid( L"{F9FFF0D6-3094-6DE6-B667-0C299FFF0F6B}" ) );
    booleanTimeseriesPropertyObject1->SetRowVersion( 7919070411185189078LL );
    booleanTimeseriesPropertyObject1->SetElement( Guid( L"{F9FFF0D6-3094-6DE6-B667-0C299FFF0F6B}" ) );
    booleanTimeseriesPropertyObject1->SetDefinition( Guid( L"{F9FFF0D6-3094-6DE6-B667-0C299FFF0F6B}" ) );
    booleanTimeseriesPropertyObject1->SetTimeseries( Guid( L"{F9FFF0D6-3094-6DE6-B667-0C299FFF0F6B}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *booleanTimeseriesPropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto booleanTimeseriesPropertyObject2 = std::reinterpret_pointer_cast<BooleanTimeseriesPropertyObject>( ReadDataFrom( source ) );
    bool equal = booleanTimeseriesPropertyObject2->IsEqualTo( *booleanTimeseriesPropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ByteTimeseriesPropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( ByteTimeseriesPropertyObjectSerializationTest )
{
    auto byteTimeseriesPropertyObject1 = std::make_shared<ByteTimeseriesPropertyObject>( );
    byteTimeseriesPropertyObject1->SetId( Guid( L"{13E6E02A-A2C1-9BDF-D9FB-4583C8670754}" ) );
    byteTimeseriesPropertyObject1->SetRowVersion( -7214869127877959638LL );
    byteTimeseriesPropertyObject1->SetElement( Guid( L"{13E6E02A-A2C1-9BDF-D9FB-4583C8670754}" ) );
    byteTimeseriesPropertyObject1->SetDefinition( Guid( L"{13E6E02A-A2C1-9BDF-D9FB-4583C8670754}" ) );
    byteTimeseriesPropertyObject1->SetTimeseries( Guid( L"{13E6E02A-A2C1-9BDF-D9FB-4583C8670754}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *byteTimeseriesPropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto byteTimeseriesPropertyObject2 = std::reinterpret_pointer_cast<ByteTimeseriesPropertyObject>( ReadDataFrom( source ) );
    bool equal = byteTimeseriesPropertyObject2->IsEqualTo( *byteTimeseriesPropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DateTimeTimeseriesPropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( DateTimeTimeseriesPropertyObjectSerializationTest )
{
    auto dateTimeTimeseriesPropertyObject1 = std::make_shared<DateTimeTimeseriesPropertyObject>( );
    dateTimeTimeseriesPropertyObject1->SetId( Guid( L"{C99041E2-152C-25AB-A4D5-A83493098247}" ) );
    dateTimeTimeseriesPropertyObject1->SetRowVersion( 2714286482525274594LL );
    dateTimeTimeseriesPropertyObject1->SetElement( Guid( L"{C99041E2-152C-25AB-A4D5-A83493098247}" ) );
    dateTimeTimeseriesPropertyObject1->SetDefinition( Guid( L"{C99041E2-152C-25AB-A4D5-A83493098247}" ) );
    dateTimeTimeseriesPropertyObject1->SetTimeseries( Guid( L"{C99041E2-152C-25AB-A4D5-A83493098247}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *dateTimeTimeseriesPropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto dateTimeTimeseriesPropertyObject2 = std::reinterpret_pointer_cast<DateTimeTimeseriesPropertyObject>( ReadDataFrom( source ) );
    bool equal = dateTimeTimeseriesPropertyObject2->IsEqualTo( *dateTimeTimeseriesPropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DoubleTimeseriesPropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( DoubleTimeseriesPropertyObjectSerializationTest )
{
    auto doubleTimeseriesPropertyObject1 = std::make_shared<DoubleTimeseriesPropertyObject>( );
    doubleTimeseriesPropertyObject1->SetId( Guid( L"{D612B612-0D2A-902E-0974-B0546B486D48}" ) );
    doubleTimeseriesPropertyObject1->SetRowVersion( -8057488205687900654LL );
    doubleTimeseriesPropertyObject1->SetElement( Guid( L"{D612B612-0D2A-902E-0974-B0546B486D48}" ) );
    doubleTimeseriesPropertyObject1->SetDefinition( Guid( L"{D612B612-0D2A-902E-0974-B0546B486D48}" ) );
    doubleTimeseriesPropertyObject1->SetTimeseries( Guid( L"{D612B612-0D2A-902E-0974-B0546B486D48}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *doubleTimeseriesPropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto doubleTimeseriesPropertyObject2 = std::reinterpret_pointer_cast<DoubleTimeseriesPropertyObject>( ReadDataFrom( source ) );
    bool equal = doubleTimeseriesPropertyObject2->IsEqualTo( *doubleTimeseriesPropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GuidTimeseriesPropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( GuidTimeseriesPropertyObjectSerializationTest )
{
    auto guidTimeseriesPropertyObject1 = std::make_shared<GuidTimeseriesPropertyObject>( );
    guidTimeseriesPropertyObject1->SetId( Guid( L"{EABB70EA-0EF1-9E2E-7974-708F57DD0E57}" ) );
    guidTimeseriesPropertyObject1->SetRowVersion( -7048679934600187670LL );
    guidTimeseriesPropertyObject1->SetElement( Guid( L"{EABB70EA-0EF1-9E2E-7974-708F57DD0E57}" ) );
    guidTimeseriesPropertyObject1->SetDefinition( Guid( L"{EABB70EA-0EF1-9E2E-7974-708F57DD0E57}" ) );
    guidTimeseriesPropertyObject1->SetTimeseries( Guid( L"{EABB70EA-0EF1-9E2E-7974-708F57DD0E57}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *guidTimeseriesPropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto guidTimeseriesPropertyObject2 = std::reinterpret_pointer_cast<GuidTimeseriesPropertyObject>( ReadDataFrom( source ) );
    bool equal = guidTimeseriesPropertyObject2->IsEqualTo( *guidTimeseriesPropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int16TimeseriesPropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( Int16TimeseriesPropertyObjectSerializationTest )
{
    auto int16TimeseriesPropertyObject1 = std::make_shared<Int16TimeseriesPropertyObject>( );
    int16TimeseriesPropertyObject1->SetId( Guid( L"{7B2B5BD8-89DA-816F-81F6-915BDED4DA1B}" ) );
    int16TimeseriesPropertyObject1->SetRowVersion( -9119919148939650088LL );
    int16TimeseriesPropertyObject1->SetElement( Guid( L"{7B2B5BD8-89DA-816F-81F6-915BDED4DA1B}" ) );
    int16TimeseriesPropertyObject1->SetDefinition( Guid( L"{7B2B5BD8-89DA-816F-81F6-915BDED4DA1B}" ) );
    int16TimeseriesPropertyObject1->SetTimeseries( Guid( L"{7B2B5BD8-89DA-816F-81F6-915BDED4DA1B}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int16TimeseriesPropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int16TimeseriesPropertyObject2 = std::reinterpret_pointer_cast<Int16TimeseriesPropertyObject>( ReadDataFrom( source ) );
    bool equal = int16TimeseriesPropertyObject2->IsEqualTo( *int16TimeseriesPropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int32TimeseriesPropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( Int32TimeseriesPropertyObjectSerializationTest )
{
    auto int32TimeseriesPropertyObject1 = std::make_shared<Int32TimeseriesPropertyObject>( );
    int32TimeseriesPropertyObject1->SetId( Guid( L"{9FF1F1C6-7364-251E-A478-CE26F98F8F63}" ) );
    int32TimeseriesPropertyObject1->SetRowVersion( 2674702104722010566LL );
    int32TimeseriesPropertyObject1->SetElement( Guid( L"{9FF1F1C6-7364-251E-A478-CE26F98F8F63}" ) );
    int32TimeseriesPropertyObject1->SetDefinition( Guid( L"{9FF1F1C6-7364-251E-A478-CE26F98F8F63}" ) );
    int32TimeseriesPropertyObject1->SetTimeseries( Guid( L"{9FF1F1C6-7364-251E-A478-CE26F98F8F63}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int32TimeseriesPropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int32TimeseriesPropertyObject2 = std::reinterpret_pointer_cast<Int32TimeseriesPropertyObject>( ReadDataFrom( source ) );
    bool equal = int32TimeseriesPropertyObject2->IsEqualTo( *int32TimeseriesPropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int64TimeseriesPropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( Int64TimeseriesPropertyObjectSerializationTest )
{
    auto int64TimeseriesPropertyObject1 = std::make_shared<Int64TimeseriesPropertyObject>( );
    int64TimeseriesPropertyObject1->SetId( Guid( L"{4DD31704-9B5E-BC84-3D21-D97AB2CBE820}" ) );
    int64TimeseriesPropertyObject1->SetRowVersion( -4862590868318382332LL );
    int64TimeseriesPropertyObject1->SetElement( Guid( L"{4DD31704-9B5E-BC84-3D21-D97AB2CBE820}" ) );
    int64TimeseriesPropertyObject1->SetDefinition( Guid( L"{4DD31704-9B5E-BC84-3D21-D97AB2CBE820}" ) );
    int64TimeseriesPropertyObject1->SetTimeseries( Guid( L"{4DD31704-9B5E-BC84-3D21-D97AB2CBE820}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int64TimeseriesPropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int64TimeseriesPropertyObject2 = std::reinterpret_pointer_cast<Int64TimeseriesPropertyObject>( ReadDataFrom( source ) );
    bool equal = int64TimeseriesPropertyObject2->IsEqualTo( *int64TimeseriesPropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ReferenceTimeseriesPropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( ReferenceTimeseriesPropertyObjectSerializationTest )
{
    auto referenceTimeseriesPropertyObject1 = std::make_shared<ReferenceTimeseriesPropertyObject>( );
    referenceTimeseriesPropertyObject1->SetId( Guid( L"{713F2D3F-7C29-8880-1101-3E948EFCB4FC}" ) );
    referenceTimeseriesPropertyObject1->SetRowVersion( -8610745970096919233LL );
    referenceTimeseriesPropertyObject1->SetElement( Guid( L"{713F2D3F-7C29-8880-1101-3E948EFCB4FC}" ) );
    referenceTimeseriesPropertyObject1->SetDefinition( Guid( L"{713F2D3F-7C29-8880-1101-3E948EFCB4FC}" ) );
    referenceTimeseriesPropertyObject1->SetTimeseries( Guid( L"{713F2D3F-7C29-8880-1101-3E948EFCB4FC}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *referenceTimeseriesPropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto referenceTimeseriesPropertyObject2 = std::reinterpret_pointer_cast<ReferenceTimeseriesPropertyObject>( ReadDataFrom( source ) );
    bool equal = referenceTimeseriesPropertyObject2->IsEqualTo( *referenceTimeseriesPropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SByteTimeseriesPropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( SByteTimeseriesPropertyObjectSerializationTest )
{
    auto sByteTimeseriesPropertyObject1 = std::make_shared<SByteTimeseriesPropertyObject>( );
    sByteTimeseriesPropertyObject1->SetId( Guid( L"{3E0E464A-8641-0E03-70C0-61827C706252}" ) );
    sByteTimeseriesPropertyObject1->SetRowVersion( 1009798356233242186LL );
    sByteTimeseriesPropertyObject1->SetElement( Guid( L"{3E0E464A-8641-0E03-70C0-61827C706252}" ) );
    sByteTimeseriesPropertyObject1->SetDefinition( Guid( L"{3E0E464A-8641-0E03-70C0-61827C706252}" ) );
    sByteTimeseriesPropertyObject1->SetTimeseries( Guid( L"{3E0E464A-8641-0E03-70C0-61827C706252}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *sByteTimeseriesPropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto sByteTimeseriesPropertyObject2 = std::reinterpret_pointer_cast<SByteTimeseriesPropertyObject>( ReadDataFrom( source ) );
    bool equal = sByteTimeseriesPropertyObject2->IsEqualTo( *sByteTimeseriesPropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SingleTimeseriesPropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( SingleTimeseriesPropertyObjectSerializationTest )
{
    auto singleTimeseriesPropertyObject1 = std::make_shared<SingleTimeseriesPropertyObject>( );
    singleTimeseriesPropertyObject1->SetId( Guid( L"{B4491B37-C1C3-440E-2270-83C32D92D8EC}" ) );
    singleTimeseriesPropertyObject1->SetRowVersion( 4904070090540522295LL );
    singleTimeseriesPropertyObject1->SetElement( Guid( L"{B4491B37-C1C3-440E-2270-83C32D92D8EC}" ) );
    singleTimeseriesPropertyObject1->SetDefinition( Guid( L"{B4491B37-C1C3-440E-2270-83C32D92D8EC}" ) );
    singleTimeseriesPropertyObject1->SetTimeseries( Guid( L"{B4491B37-C1C3-440E-2270-83C32D92D8EC}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *singleTimeseriesPropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto singleTimeseriesPropertyObject2 = std::reinterpret_pointer_cast<SingleTimeseriesPropertyObject>( ReadDataFrom( source ) );
    bool equal = singleTimeseriesPropertyObject2->IsEqualTo( *singleTimeseriesPropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/StringTimeseriesPropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( StringTimeseriesPropertyObjectSerializationTest )
{
    auto stringTimeseriesPropertyObject1 = std::make_shared<StringTimeseriesPropertyObject>( );
    stringTimeseriesPropertyObject1->SetId( Guid( L"{695E2407-EFD1-69F5-96AF-F78B967A24E0}" ) );
    stringTimeseriesPropertyObject1->SetRowVersion( 7635272425971524615LL );
    stringTimeseriesPropertyObject1->SetElement( Guid( L"{695E2407-EFD1-69F5-96AF-F78B967A24E0}" ) );
    stringTimeseriesPropertyObject1->SetDefinition( Guid( L"{695E2407-EFD1-69F5-96AF-F78B967A24E0}" ) );
    stringTimeseriesPropertyObject1->SetTimeseries( Guid( L"{695E2407-EFD1-69F5-96AF-F78B967A24E0}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *stringTimeseriesPropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto stringTimeseriesPropertyObject2 = std::reinterpret_pointer_cast<StringTimeseriesPropertyObject>( ReadDataFrom( source ) );
    bool equal = stringTimeseriesPropertyObject2->IsEqualTo( *stringTimeseriesPropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TimeSpanTimeseriesPropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( TimeSpanTimeseriesPropertyObjectSerializationTest )
{
    auto timeSpanTimeseriesPropertyObject1 = std::make_shared<TimeSpanTimeseriesPropertyObject>( );
    timeSpanTimeseriesPropertyObject1->SetId( Guid( L"{E21D31DB-8E76-9B1C-D938-716E47B88CDB}" ) );
    timeSpanTimeseriesPropertyObject1->SetRowVersion( -7269779057231973925LL );
    timeSpanTimeseriesPropertyObject1->SetElement( Guid( L"{E21D31DB-8E76-9B1C-D938-716E47B88CDB}" ) );
    timeSpanTimeseriesPropertyObject1->SetDefinition( Guid( L"{E21D31DB-8E76-9B1C-D938-716E47B88CDB}" ) );
    timeSpanTimeseriesPropertyObject1->SetTimeseries( Guid( L"{E21D31DB-8E76-9B1C-D938-716E47B88CDB}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *timeSpanTimeseriesPropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto timeSpanTimeseriesPropertyObject2 = std::reinterpret_pointer_cast<TimeSpanTimeseriesPropertyObject>( ReadDataFrom( source ) );
    bool equal = timeSpanTimeseriesPropertyObject2->IsEqualTo( *timeSpanTimeseriesPropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt16TimeseriesPropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( UInt16TimeseriesPropertyObjectSerializationTest )
{
    auto uInt16TimeseriesPropertyObject1 = std::make_shared<UInt16TimeseriesPropertyObject>( );
    uInt16TimeseriesPropertyObject1->SetId( Guid( L"{54EBD8DB-1242-E95C-973A-48422AD71BDB}" ) );
    uInt16TimeseriesPropertyObject1->SetRowVersion( -1631408888913078053LL );
    uInt16TimeseriesPropertyObject1->SetElement( Guid( L"{54EBD8DB-1242-E95C-973A-48422AD71BDB}" ) );
    uInt16TimeseriesPropertyObject1->SetDefinition( Guid( L"{54EBD8DB-1242-E95C-973A-48422AD71BDB}" ) );
    uInt16TimeseriesPropertyObject1->SetTimeseries( Guid( L"{54EBD8DB-1242-E95C-973A-48422AD71BDB}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt16TimeseriesPropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt16TimeseriesPropertyObject2 = std::reinterpret_pointer_cast<UInt16TimeseriesPropertyObject>( ReadDataFrom( source ) );
    bool equal = uInt16TimeseriesPropertyObject2->IsEqualTo( *uInt16TimeseriesPropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt32TimeseriesPropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( UInt32TimeseriesPropertyObjectSerializationTest )
{
    auto uInt32TimeseriesPropertyObject1 = std::make_shared<UInt32TimeseriesPropertyObject>( );
    uInt32TimeseriesPropertyObject1->SetId( Guid( L"{11EB998F-D7AF-A24D-45B2-EBF588D799F1}" ) );
    uInt32TimeseriesPropertyObject1->SetRowVersion( -6751503119438603889LL );
    uInt32TimeseriesPropertyObject1->SetElement( Guid( L"{11EB998F-D7AF-A24D-45B2-EBF588D799F1}" ) );
    uInt32TimeseriesPropertyObject1->SetDefinition( Guid( L"{11EB998F-D7AF-A24D-45B2-EBF588D799F1}" ) );
    uInt32TimeseriesPropertyObject1->SetTimeseries( Guid( L"{11EB998F-D7AF-A24D-45B2-EBF588D799F1}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt32TimeseriesPropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt32TimeseriesPropertyObject2 = std::reinterpret_pointer_cast<UInt32TimeseriesPropertyObject>( ReadDataFrom( source ) );
    bool equal = uInt32TimeseriesPropertyObject2->IsEqualTo( *uInt32TimeseriesPropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt64TimeseriesPropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( UInt64TimeseriesPropertyObjectSerializationTest )
{
    auto uInt64TimeseriesPropertyObject1 = std::make_shared<UInt64TimeseriesPropertyObject>( );
    uInt64TimeseriesPropertyObject1->SetId( Guid( L"{A95D5CEA-EE30-A724-E524-770C95BA3A57}" ) );
    uInt64TimeseriesPropertyObject1->SetRowVersion( -6402730877446693654LL );
    uInt64TimeseriesPropertyObject1->SetElement( Guid( L"{A95D5CEA-EE30-A724-E524-770C95BA3A57}" ) );
    uInt64TimeseriesPropertyObject1->SetDefinition( Guid( L"{A95D5CEA-EE30-A724-E524-770C95BA3A57}" ) );
    uInt64TimeseriesPropertyObject1->SetTimeseries( Guid( L"{A95D5CEA-EE30-A724-E524-770C95BA3A57}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt64TimeseriesPropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt64TimeseriesPropertyObject2 = std::reinterpret_pointer_cast<UInt64TimeseriesPropertyObject>( ReadDataFrom( source ) );
    bool equal = uInt64TimeseriesPropertyObject2->IsEqualTo( *uInt64TimeseriesPropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TimeSpanPropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( TimeSpanPropertyObjectSerializationTest )
{
    auto timeSpanPropertyObject1 = std::make_shared<TimeSpanPropertyObject>( );
    timeSpanPropertyObject1->SetId( Guid( L"{1FBB969B-87EE-BF54-FD2A-E177F8DD69D9}" ) );
    timeSpanPropertyObject1->SetRowVersion( -4659950257617267045LL );
    timeSpanPropertyObject1->SetElement( Guid( L"{1FBB969B-87EE-BF54-FD2A-E177F8DD69D9}" ) );
    timeSpanPropertyObject1->SetDefinition( Guid( L"{1FBB969B-87EE-BF54-FD2A-E177F8DD69D9}" ) );
    timeSpanPropertyObject1->SetValue( TimeSpan( -817617267045LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *timeSpanPropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto timeSpanPropertyObject2 = std::reinterpret_pointer_cast<TimeSpanPropertyObject>( ReadDataFrom( source ) );
    bool equal = timeSpanPropertyObject2->IsEqualTo( *timeSpanPropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt16PropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( UInt16PropertyObjectSerializationTest )
{
    auto uInt16PropertyObject1 = std::make_shared<UInt16PropertyObject>( );
    uInt16PropertyObject1->SetId( Guid( L"{DD66D477-E812-FE6E-7F76-1748BB662BEE}" ) );
    uInt16PropertyObject1->SetRowVersion( -112897772916124553LL );
    uInt16PropertyObject1->SetElement( Guid( L"{DD66D477-E812-FE6E-7F76-1748BB662BEE}" ) );
    uInt16PropertyObject1->SetDefinition( Guid( L"{DD66D477-E812-FE6E-7F76-1748BB662BEE}" ) );
    uInt16PropertyObject1->SetValue( 54391 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt16PropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt16PropertyObject2 = std::reinterpret_pointer_cast<UInt16PropertyObject>( ReadDataFrom( source ) );
    bool equal = uInt16PropertyObject2->IsEqualTo( *uInt16PropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt32PropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( UInt32PropertyObjectSerializationTest )
{
    auto uInt32PropertyObject1 = std::make_shared<UInt32PropertyObject>( );
    uInt32PropertyObject1->SetId( Guid( L"{D211E6C7-A461-B9A3-9DC5-25864B8867E3}" ) );
    uInt32PropertyObject1->SetRowVersion( -5070028015445875001LL );
    uInt32PropertyObject1->SetElement( Guid( L"{D211E6C7-A461-B9A3-9DC5-25864B8867E3}" ) );
    uInt32PropertyObject1->SetDefinition( Guid( L"{D211E6C7-A461-B9A3-9DC5-25864B8867E3}" ) );
    uInt32PropertyObject1->SetValue( 3524388551UL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt32PropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt32PropertyObject2 = std::reinterpret_pointer_cast<UInt32PropertyObject>( ReadDataFrom( source ) );
    bool equal = uInt32PropertyObject2->IsEqualTo( *uInt32PropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt64PropertyObjectSerializationTest
BOOST_AUTO_TEST_CASE( UInt64PropertyObjectSerializationTest )
{
    auto uInt64PropertyObject1 = std::make_shared<UInt64PropertyObject>( );
    uInt64PropertyObject1->SetId( Guid( L"{7E04896F-7BB0-1B66-D866-DE0D7E2091F6}" ) );
    uInt64PropertyObject1->SetRowVersion( 1974401484607228271LL );
    uInt64PropertyObject1->SetElement( Guid( L"{7E04896F-7BB0-1B66-D866-DE0D7E2091F6}" ) );
    uInt64PropertyObject1->SetDefinition( Guid( L"{7E04896F-7BB0-1B66-D866-DE0D7E2091F6}" ) );
    uInt64PropertyObject1->SetValue( 1974401484607228271LL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt64PropertyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt64PropertyObject2 = std::reinterpret_pointer_cast<UInt64PropertyObject>( ReadDataFrom( source ) );
    bool equal = uInt64PropertyObject2->IsEqualTo( *uInt64PropertyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BinaryPropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( BinaryPropertyDefinitionObjectSerializationTest )
{
    auto binaryPropertyDefinitionObject1 = std::make_shared<BinaryPropertyDefinitionObject>( );
    binaryPropertyDefinitionObject1->SetId( Guid( L"{1D803290-52D6-19B9-989D-4A6BB8014C09}" ) );
    binaryPropertyDefinitionObject1->SetRowVersion( 1853603801211089552LL );
    binaryPropertyDefinitionObject1->SetElementType( Guid( L"{1D803290-52D6-19B9-989D-4A6BB8014C09}" ) );
    binaryPropertyDefinitionObject1->SetName( L"Name" );
    binaryPropertyDefinitionObject1->SetDescription( L"Description" );
    binaryPropertyDefinitionObject1->SetDefaultValue( { {'D','e','f','a','u','l','t','V','a','l','u','e'} } );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *binaryPropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto binaryPropertyDefinitionObject2 = std::reinterpret_pointer_cast<BinaryPropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = binaryPropertyDefinitionObject2->IsEqualTo( *binaryPropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BooleanPropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( BooleanPropertyDefinitionObjectSerializationTest )
{
    auto booleanPropertyDefinitionObject1 = std::make_shared<BooleanPropertyDefinitionObject>( );
    booleanPropertyDefinitionObject1->SetId( Guid( L"{C5539C12-7E89-E9BE-977D-7E91A3CA3948}" ) );
    booleanPropertyDefinitionObject1->SetRowVersion( -1603705287111107566LL );
    booleanPropertyDefinitionObject1->SetElementType( Guid( L"{C5539C12-7E89-E9BE-977D-7E91A3CA3948}" ) );
    booleanPropertyDefinitionObject1->SetName( L"Name" );
    booleanPropertyDefinitionObject1->SetDescription( L"Description" );
    booleanPropertyDefinitionObject1->SetDefaultValue( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *booleanPropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto booleanPropertyDefinitionObject2 = std::reinterpret_pointer_cast<BooleanPropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = booleanPropertyDefinitionObject2->IsEqualTo( *booleanPropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BytePropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( BytePropertyDefinitionObjectSerializationTest )
{
    auto bytePropertyDefinitionObject1 = std::make_shared<BytePropertyDefinitionObject>( );
    bytePropertyDefinitionObject1->SetId( Guid( L"{F1BB6CC7-ED96-BDD1-BD8B-B7698FDD36E3}" ) );
    bytePropertyDefinitionObject1->SetRowVersion( -4768769297852175161LL );
    bytePropertyDefinitionObject1->SetElementType( Guid( L"{F1BB6CC7-ED96-BDD1-BD8B-B7698FDD36E3}" ) );
    bytePropertyDefinitionObject1->SetName( L"Name" );
    bytePropertyDefinitionObject1->SetDescription( L"Description" );
    bytePropertyDefinitionObject1->SetDefaultValue( 199 );
    bytePropertyDefinitionObject1->SetMinValue( 199 );
    bytePropertyDefinitionObject1->SetMaxValue( 199 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *bytePropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto bytePropertyDefinitionObject2 = std::reinterpret_pointer_cast<BytePropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = bytePropertyDefinitionObject2->IsEqualTo( *bytePropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DateTimePropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( DateTimePropertyDefinitionObjectSerializationTest )
{
    auto dateTimePropertyDefinitionObject1 = std::make_shared<DateTimePropertyDefinitionObject>( );
    dateTimePropertyDefinitionObject1->SetId( Guid( L"{6B2D65C2-50BD-E15F-87FA-0ABDD6B4A643}" ) );
    dateTimePropertyDefinitionObject1->SetRowVersion( -2206956517911075390LL );
    dateTimePropertyDefinitionObject1->SetElementType( Guid( L"{6B2D65C2-50BD-E15F-87FA-0ABDD6B4A643}" ) );
    dateTimePropertyDefinitionObject1->SetName( L"Name" );
    dateTimePropertyDefinitionObject1->SetDescription( L"Description" );
    dateTimePropertyDefinitionObject1->SetDefaultValue( L"DefaultValue" );
    dateTimePropertyDefinitionObject1->SetMinValue( L"MinValue" );
    dateTimePropertyDefinitionObject1->SetMaxValue( L"MaxValue" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *dateTimePropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto dateTimePropertyDefinitionObject2 = std::reinterpret_pointer_cast<DateTimePropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = dateTimePropertyDefinitionObject2->IsEqualTo( *dateTimePropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DoublePropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( DoublePropertyDefinitionObjectSerializationTest )
{
    auto doublePropertyDefinitionObject1 = std::make_shared<DoublePropertyDefinitionObject>( );
    doublePropertyDefinitionObject1->SetId( Guid( L"{EA061AC5-7B6D-83B0-C10D-DEB6576058A3}" ) );
    doublePropertyDefinitionObject1->SetRowVersion( -8957523946831996219LL );
    doublePropertyDefinitionObject1->SetElementType( Guid( L"{EA061AC5-7B6D-83B0-C10D-DEB6576058A3}" ) );
    doublePropertyDefinitionObject1->SetName( L"Name" );
    doublePropertyDefinitionObject1->SetDescription( L"Description" );
    doublePropertyDefinitionObject1->SetDefaultValue( 9489220126877554 );
    doublePropertyDefinitionObject1->SetMinValue( 9489220126877554 );
    doublePropertyDefinitionObject1->SetMaxValue( 9489220126877554 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *doublePropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto doublePropertyDefinitionObject2 = std::reinterpret_pointer_cast<DoublePropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = doublePropertyDefinitionObject2->IsEqualTo( *doublePropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GuidPropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( GuidPropertyDefinitionObjectSerializationTest )
{
    auto guidPropertyDefinitionObject1 = std::make_shared<GuidPropertyDefinitionObject>( );
    guidPropertyDefinitionObject1->SetId( Guid( L"{CE281097-BBE1-0062-0046-DD87731408E9}" ) );
    guidPropertyDefinitionObject1->SetRowVersion( 27791126218412183LL );
    guidPropertyDefinitionObject1->SetElementType( Guid( L"{CE281097-BBE1-0062-0046-DD87731408E9}" ) );
    guidPropertyDefinitionObject1->SetName( L"Name" );
    guidPropertyDefinitionObject1->SetDescription( L"Description" );
    guidPropertyDefinitionObject1->SetDefaultValue( Guid( L"{CE281097-BBE1-0062-0046-DD87731408E9}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *guidPropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto guidPropertyDefinitionObject2 = std::reinterpret_pointer_cast<GuidPropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = guidPropertyDefinitionObject2->IsEqualTo( *guidPropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int16PropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( Int16PropertyDefinitionObjectSerializationTest )
{
    auto int16PropertyDefinitionObject1 = std::make_shared<Int16PropertyDefinitionObject>( );
    int16PropertyDefinitionObject1->SetId( Guid( L"{8116597C-DE9B-0CFB-30DF-7BD981689A3E}" ) );
    int16PropertyDefinitionObject1->SetRowVersion( 935586107076532604LL );
    int16PropertyDefinitionObject1->SetElementType( Guid( L"{8116597C-DE9B-0CFB-30DF-7BD981689A3E}" ) );
    int16PropertyDefinitionObject1->SetName( L"Name" );
    int16PropertyDefinitionObject1->SetDescription( L"Description" );
    int16PropertyDefinitionObject1->SetDefaultValue( 22908 );
    int16PropertyDefinitionObject1->SetMinValue( 22908 );
    int16PropertyDefinitionObject1->SetMaxValue( 22908 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int16PropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int16PropertyDefinitionObject2 = std::reinterpret_pointer_cast<Int16PropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = int16PropertyDefinitionObject2->IsEqualTo( *int16PropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int32PropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( Int32PropertyDefinitionObjectSerializationTest )
{
    auto int32PropertyDefinitionObject1 = std::make_shared<Int32PropertyDefinitionObject>( );
    int32PropertyDefinitionObject1->SetId( Guid( L"{FA7276D6-5345-2973-94CE-CAA25F4E6E6B}" ) );
    int32PropertyDefinitionObject1->SetRowVersion( 2986822537896425174LL );
    int32PropertyDefinitionObject1->SetElementType( Guid( L"{FA7276D6-5345-2973-94CE-CAA25F4E6E6B}" ) );
    int32PropertyDefinitionObject1->SetName( L"Name" );
    int32PropertyDefinitionObject1->SetDescription( L"Description" );
    int32PropertyDefinitionObject1->SetDefaultValue( -93161770L );
    int32PropertyDefinitionObject1->SetMinValue( -93161770L );
    int32PropertyDefinitionObject1->SetMaxValue( -93161770L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int32PropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int32PropertyDefinitionObject2 = std::reinterpret_pointer_cast<Int32PropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = int32PropertyDefinitionObject2->IsEqualTo( *int32PropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int64PropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( Int64PropertyDefinitionObjectSerializationTest )
{
    auto int64PropertyDefinitionObject1 = std::make_shared<Int64PropertyDefinitionObject>( );
    int64PropertyDefinitionObject1->SetId( Guid( L"{25153A4E-9C64-9D7F-B9FE-3926A4A85C72}" ) );
    int64PropertyDefinitionObject1->SetRowVersion( -7097782533779801522LL );
    int64PropertyDefinitionObject1->SetElementType( Guid( L"{25153A4E-9C64-9D7F-B9FE-3926A4A85C72}" ) );
    int64PropertyDefinitionObject1->SetName( L"Name" );
    int64PropertyDefinitionObject1->SetDescription( L"Description" );
    int64PropertyDefinitionObject1->SetDefaultValue( -7097782533779801522LL );
    int64PropertyDefinitionObject1->SetMinValue( -7097782533779801522LL );
    int64PropertyDefinitionObject1->SetMaxValue( -7097782533779801522LL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int64PropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int64PropertyDefinitionObject2 = std::reinterpret_pointer_cast<Int64PropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = int64PropertyDefinitionObject2->IsEqualTo( *int64PropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ReferencePropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( ReferencePropertyDefinitionObjectSerializationTest )
{
    auto referencePropertyDefinitionObject1 = std::make_shared<ReferencePropertyDefinitionObject>( );
    referencePropertyDefinitionObject1->SetId( Guid( L"{24335FD6-6F2B-1A65-58A6-F6D424CCFA6B}" ) );
    referencePropertyDefinitionObject1->SetRowVersion( 1902048648715526102LL );
    referencePropertyDefinitionObject1->SetElementType( Guid( L"{24335FD6-6F2B-1A65-58A6-F6D424CCFA6B}" ) );
    referencePropertyDefinitionObject1->SetName( L"Name" );
    referencePropertyDefinitionObject1->SetDescription( L"Description" );
    referencePropertyDefinitionObject1->SetDefaultValue( Guid( L"{24335FD6-6F2B-1A65-58A6-F6D424CCFA6B}" ) );
    referencePropertyDefinitionObject1->SetReferencedElementType( Guid( L"{24335FD6-6F2B-1A65-58A6-F6D424CCFA6B}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *referencePropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto referencePropertyDefinitionObject2 = std::reinterpret_pointer_cast<ReferencePropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = referencePropertyDefinitionObject2->IsEqualTo( *referencePropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SBytePropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( SBytePropertyDefinitionObjectSerializationTest )
{
    auto sBytePropertyDefinitionObject1 = std::make_shared<SBytePropertyDefinitionObject>( );
    sBytePropertyDefinitionObject1->SetId( Guid( L"{8AA729B7-0195-0AA3-50C5-80A951E594ED}" ) );
    sBytePropertyDefinitionObject1->SetRowVersion( 766458103371082167LL );
    sBytePropertyDefinitionObject1->SetElementType( Guid( L"{8AA729B7-0195-0AA3-50C5-80A951E594ED}" ) );
    sBytePropertyDefinitionObject1->SetName( L"Name" );
    sBytePropertyDefinitionObject1->SetDescription( L"Description" );
    sBytePropertyDefinitionObject1->SetDefaultValue( -73 );
    sBytePropertyDefinitionObject1->SetMinValue( -73 );
    sBytePropertyDefinitionObject1->SetMaxValue( -73 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *sBytePropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto sBytePropertyDefinitionObject2 = std::reinterpret_pointer_cast<SBytePropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = sBytePropertyDefinitionObject2->IsEqualTo( *sBytePropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SinglePropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( SinglePropertyDefinitionObjectSerializationTest )
{
    auto singlePropertyDefinitionObject1 = std::make_shared<SinglePropertyDefinitionObject>( );
    singlePropertyDefinitionObject1->SetId( Guid( L"{DF60F841-AFE1-2C03-34C0-F587FB061F82}" ) );
    singlePropertyDefinitionObject1->SetRowVersion( 3171571947249137729LL );
    singlePropertyDefinitionObject1->SetElementType( Guid( L"{DF60F841-AFE1-2C03-34C0-F587FB061F82}" ) );
    singlePropertyDefinitionObject1->SetName( L"Name" );
    singlePropertyDefinitionObject1->SetDescription( L"Description" );
    singlePropertyDefinitionObject1->SetDefaultValue( 3.1715722e+15f );
    singlePropertyDefinitionObject1->SetMinValue( 3.1715722e+15f );
    singlePropertyDefinitionObject1->SetMaxValue( 3.1715722e+15f );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *singlePropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto singlePropertyDefinitionObject2 = std::reinterpret_pointer_cast<SinglePropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = singlePropertyDefinitionObject2->IsEqualTo( *singlePropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/StringPropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( StringPropertyDefinitionObjectSerializationTest )
{
    auto stringPropertyDefinitionObject1 = std::make_shared<StringPropertyDefinitionObject>( );
    stringPropertyDefinitionObject1->SetId( Guid( L"{FD110D8D-6A34-991A-9958-562CBF88B0B1}" ) );
    stringPropertyDefinitionObject1->SetRowVersion( -7414497060695503475LL );
    stringPropertyDefinitionObject1->SetElementType( Guid( L"{FD110D8D-6A34-991A-9958-562CBF88B0B1}" ) );
    stringPropertyDefinitionObject1->SetName( L"Name" );
    stringPropertyDefinitionObject1->SetDescription( L"Description" );
    stringPropertyDefinitionObject1->SetDefaultValue( L"DefaultValue" );
    stringPropertyDefinitionObject1->SetPattern( L"Pattern" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *stringPropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto stringPropertyDefinitionObject2 = std::reinterpret_pointer_cast<StringPropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = stringPropertyDefinitionObject2->IsEqualTo( *stringPropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BinaryTimeseriesPropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( BinaryTimeseriesPropertyDefinitionObjectSerializationTest )
{
    auto binaryTimeseriesPropertyDefinitionObject1 = std::make_shared<BinaryTimeseriesPropertyDefinitionObject>( );
    binaryTimeseriesPropertyDefinitionObject1->SetId( Guid( L"{6C888CD1-A32E-1237-48EC-C5743611318B}" ) );
    binaryTimeseriesPropertyDefinitionObject1->SetRowVersion( 1312697236186500305LL );
    binaryTimeseriesPropertyDefinitionObject1->SetElementType( Guid( L"{6C888CD1-A32E-1237-48EC-C5743611318B}" ) );
    binaryTimeseriesPropertyDefinitionObject1->SetName( L"Name" );
    binaryTimeseriesPropertyDefinitionObject1->SetDescription( L"Description" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *binaryTimeseriesPropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto binaryTimeseriesPropertyDefinitionObject2 = std::reinterpret_pointer_cast<BinaryTimeseriesPropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = binaryTimeseriesPropertyDefinitionObject2->IsEqualTo( *binaryTimeseriesPropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BooleanTimeseriesPropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( BooleanTimeseriesPropertyDefinitionObjectSerializationTest )
{
    auto booleanTimeseriesPropertyDefinitionObject1 = std::make_shared<BooleanTimeseriesPropertyDefinitionObject>( );
    booleanTimeseriesPropertyDefinitionObject1->SetId( Guid( L"{ADB1A0F7-FF33-FAB2-5F4D-FFCCB58D05EF}" ) );
    booleanTimeseriesPropertyDefinitionObject1->SetRowVersion( -381962420950556425LL );
    booleanTimeseriesPropertyDefinitionObject1->SetElementType( Guid( L"{ADB1A0F7-FF33-FAB2-5F4D-FFCCB58D05EF}" ) );
    booleanTimeseriesPropertyDefinitionObject1->SetName( L"Name" );
    booleanTimeseriesPropertyDefinitionObject1->SetDescription( L"Description" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *booleanTimeseriesPropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto booleanTimeseriesPropertyDefinitionObject2 = std::reinterpret_pointer_cast<BooleanTimeseriesPropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = booleanTimeseriesPropertyDefinitionObject2->IsEqualTo( *booleanTimeseriesPropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ByteTimeseriesPropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( ByteTimeseriesPropertyDefinitionObjectSerializationTest )
{
    auto byteTimeseriesPropertyDefinitionObject1 = std::make_shared<ByteTimeseriesPropertyDefinitionObject>( );
    byteTimeseriesPropertyDefinitionObject1->SetId( Guid( L"{AAD1D4DF-2509-FB3F-DFFC-A490558B2BFB}" ) );
    byteTimeseriesPropertyDefinitionObject1->SetRowVersion( -342514323206056737LL );
    byteTimeseriesPropertyDefinitionObject1->SetElementType( Guid( L"{AAD1D4DF-2509-FB3F-DFFC-A490558B2BFB}" ) );
    byteTimeseriesPropertyDefinitionObject1->SetName( L"Name" );
    byteTimeseriesPropertyDefinitionObject1->SetDescription( L"Description" );
    byteTimeseriesPropertyDefinitionObject1->SetMinValue( 223 );
    byteTimeseriesPropertyDefinitionObject1->SetMaxValue( 223 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *byteTimeseriesPropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto byteTimeseriesPropertyDefinitionObject2 = std::reinterpret_pointer_cast<ByteTimeseriesPropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = byteTimeseriesPropertyDefinitionObject2->IsEqualTo( *byteTimeseriesPropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DateTimeTimeseriesPropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( DateTimeTimeseriesPropertyDefinitionObjectSerializationTest )
{
    auto dateTimeTimeseriesPropertyDefinitionObject1 = std::make_shared<DateTimeTimeseriesPropertyDefinitionObject>( );
    dateTimeTimeseriesPropertyDefinitionObject1->SetId( Guid( L"{9329F71B-727F-9F98-F919-4EFEC994EFD8}" ) );
    dateTimeTimeseriesPropertyDefinitionObject1->SetRowVersion( -6946676532963576037LL );
    dateTimeTimeseriesPropertyDefinitionObject1->SetElementType( Guid( L"{9329F71B-727F-9F98-F919-4EFEC994EFD8}" ) );
    dateTimeTimeseriesPropertyDefinitionObject1->SetName( L"Name" );
    dateTimeTimeseriesPropertyDefinitionObject1->SetDescription( L"Description" );
    dateTimeTimeseriesPropertyDefinitionObject1->SetMinValue( L"MinValue" );
    dateTimeTimeseriesPropertyDefinitionObject1->SetMaxValue( L"MaxValue" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *dateTimeTimeseriesPropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto dateTimeTimeseriesPropertyDefinitionObject2 = std::reinterpret_pointer_cast<DateTimeTimeseriesPropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = dateTimeTimeseriesPropertyDefinitionObject2->IsEqualTo( *dateTimeTimeseriesPropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DoubleTimeseriesPropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( DoubleTimeseriesPropertyDefinitionObjectSerializationTest )
{
    auto doubleTimeseriesPropertyDefinitionObject1 = std::make_shared<DoubleTimeseriesPropertyDefinitionObject>( );
    doubleTimeseriesPropertyDefinitionObject1->SetId( Guid( L"{1C218637-12E0-385B-1CDA-4807388461EC}" ) );
    doubleTimeseriesPropertyDefinitionObject1->SetRowVersion( 4060860242758567479LL );
    doubleTimeseriesPropertyDefinitionObject1->SetElementType( Guid( L"{1C218637-12E0-385B-1CDA-4807388461EC}" ) );
    doubleTimeseriesPropertyDefinitionObject1->SetName( L"Name" );
    doubleTimeseriesPropertyDefinitionObject1->SetDescription( L"Description" );
    doubleTimeseriesPropertyDefinitionObject1->SetMinValue( 4060860242758567.5 );
    doubleTimeseriesPropertyDefinitionObject1->SetMaxValue( 4060860242758567.5 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *doubleTimeseriesPropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto doubleTimeseriesPropertyDefinitionObject2 = std::reinterpret_pointer_cast<DoubleTimeseriesPropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = doubleTimeseriesPropertyDefinitionObject2->IsEqualTo( *doubleTimeseriesPropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GuidTimeseriesPropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( GuidTimeseriesPropertyDefinitionObjectSerializationTest )
{
    auto guidTimeseriesPropertyDefinitionObject1 = std::make_shared<GuidTimeseriesPropertyDefinitionObject>( );
    guidTimeseriesPropertyDefinitionObject1->SetId( Guid( L"{088AD988-3F9D-3CBF-3CFD-FCB910519B11}" ) );
    guidTimeseriesPropertyDefinitionObject1->SetRowVersion( 4377287306513144200LL );
    guidTimeseriesPropertyDefinitionObject1->SetElementType( Guid( L"{088AD988-3F9D-3CBF-3CFD-FCB910519B11}" ) );
    guidTimeseriesPropertyDefinitionObject1->SetName( L"Name" );
    guidTimeseriesPropertyDefinitionObject1->SetDescription( L"Description" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *guidTimeseriesPropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto guidTimeseriesPropertyDefinitionObject2 = std::reinterpret_pointer_cast<GuidTimeseriesPropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = guidTimeseriesPropertyDefinitionObject2->IsEqualTo( *guidTimeseriesPropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int16TimeseriesPropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( Int16TimeseriesPropertyDefinitionObjectSerializationTest )
{
    auto int16TimeseriesPropertyDefinitionObject1 = std::make_shared<Int16TimeseriesPropertyDefinitionObject>( );
    int16TimeseriesPropertyDefinitionObject1->SetId( Guid( L"{6C0E69F3-88CA-5397-CAE9-1153367096CF}" ) );
    int16TimeseriesPropertyDefinitionObject1->SetRowVersion( 6023433429608983027LL );
    int16TimeseriesPropertyDefinitionObject1->SetElementType( Guid( L"{6C0E69F3-88CA-5397-CAE9-1153367096CF}" ) );
    int16TimeseriesPropertyDefinitionObject1->SetName( L"Name" );
    int16TimeseriesPropertyDefinitionObject1->SetDescription( L"Description" );
    int16TimeseriesPropertyDefinitionObject1->SetMinValue( 27123 );
    int16TimeseriesPropertyDefinitionObject1->SetMaxValue( 27123 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int16TimeseriesPropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int16TimeseriesPropertyDefinitionObject2 = std::reinterpret_pointer_cast<Int16TimeseriesPropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = int16TimeseriesPropertyDefinitionObject2->IsEqualTo( *int16TimeseriesPropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int32TimeseriesPropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( Int32TimeseriesPropertyDefinitionObjectSerializationTest )
{
    auto int32TimeseriesPropertyDefinitionObject1 = std::make_shared<Int32TimeseriesPropertyDefinitionObject>( );
    int32TimeseriesPropertyDefinitionObject1->SetId( Guid( L"{DE0CFE79-3172-12E2-4847-8C4E7B307F9E}" ) );
    int32TimeseriesPropertyDefinitionObject1->SetRowVersion( 1360704406840737401LL );
    int32TimeseriesPropertyDefinitionObject1->SetElementType( Guid( L"{DE0CFE79-3172-12E2-4847-8C4E7B307F9E}" ) );
    int32TimeseriesPropertyDefinitionObject1->SetName( L"Name" );
    int32TimeseriesPropertyDefinitionObject1->SetDescription( L"Description" );
    int32TimeseriesPropertyDefinitionObject1->SetMinValue( -569573767L );
    int32TimeseriesPropertyDefinitionObject1->SetMaxValue( -569573767L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int32TimeseriesPropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int32TimeseriesPropertyDefinitionObject2 = std::reinterpret_pointer_cast<Int32TimeseriesPropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = int32TimeseriesPropertyDefinitionObject2->IsEqualTo( *int32TimeseriesPropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int64TimeseriesPropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( Int64TimeseriesPropertyDefinitionObjectSerializationTest )
{
    auto int64TimeseriesPropertyDefinitionObject1 = std::make_shared<Int64TimeseriesPropertyDefinitionObject>( );
    int64TimeseriesPropertyDefinitionObject1->SetId( Guid( L"{8CDFCEF0-E7E4-7D31-BE8C-E72731FB730F}" ) );
    int64TimeseriesPropertyDefinitionObject1->SetRowVersion( 9021246497401851632LL );
    int64TimeseriesPropertyDefinitionObject1->SetElementType( Guid( L"{8CDFCEF0-E7E4-7D31-BE8C-E72731FB730F}" ) );
    int64TimeseriesPropertyDefinitionObject1->SetName( L"Name" );
    int64TimeseriesPropertyDefinitionObject1->SetDescription( L"Description" );
    int64TimeseriesPropertyDefinitionObject1->SetMinValue( 9021246497401851632LL );
    int64TimeseriesPropertyDefinitionObject1->SetMaxValue( 9021246497401851632LL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int64TimeseriesPropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int64TimeseriesPropertyDefinitionObject2 = std::reinterpret_pointer_cast<Int64TimeseriesPropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = int64TimeseriesPropertyDefinitionObject2->IsEqualTo( *int64TimeseriesPropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ReferenceTimeseriesPropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( ReferenceTimeseriesPropertyDefinitionObjectSerializationTest )
{
    auto referenceTimeseriesPropertyDefinitionObject1 = std::make_shared<ReferenceTimeseriesPropertyDefinitionObject>( );
    referenceTimeseriesPropertyDefinitionObject1->SetId( Guid( L"{CDCD2121-BA93-91C1-8983-5DC9B3B38484}" ) );
    referenceTimeseriesPropertyDefinitionObject1->SetRowVersion( -7943863123729112799LL );
    referenceTimeseriesPropertyDefinitionObject1->SetElementType( Guid( L"{CDCD2121-BA93-91C1-8983-5DC9B3B38484}" ) );
    referenceTimeseriesPropertyDefinitionObject1->SetName( L"Name" );
    referenceTimeseriesPropertyDefinitionObject1->SetDescription( L"Description" );
    referenceTimeseriesPropertyDefinitionObject1->SetReferencedElementType( Guid( L"{CDCD2121-BA93-91C1-8983-5DC9B3B38484}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *referenceTimeseriesPropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto referenceTimeseriesPropertyDefinitionObject2 = std::reinterpret_pointer_cast<ReferenceTimeseriesPropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = referenceTimeseriesPropertyDefinitionObject2->IsEqualTo( *referenceTimeseriesPropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SByteTimeseriesPropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( SByteTimeseriesPropertyDefinitionObjectSerializationTest )
{
    auto sByteTimeseriesPropertyDefinitionObject1 = std::make_shared<SByteTimeseriesPropertyDefinitionObject>( );
    sByteTimeseriesPropertyDefinitionObject1->SetId( Guid( L"{B0BAF218-A4E2-B4A4-2D25-25470D5D4F18}" ) );
    sByteTimeseriesPropertyDefinitionObject1->SetRowVersion( -5430033957167369704LL );
    sByteTimeseriesPropertyDefinitionObject1->SetElementType( Guid( L"{B0BAF218-A4E2-B4A4-2D25-25470D5D4F18}" ) );
    sByteTimeseriesPropertyDefinitionObject1->SetName( L"Name" );
    sByteTimeseriesPropertyDefinitionObject1->SetDescription( L"Description" );
    sByteTimeseriesPropertyDefinitionObject1->SetMinValue( 24 );
    sByteTimeseriesPropertyDefinitionObject1->SetMaxValue( 24 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *sByteTimeseriesPropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto sByteTimeseriesPropertyDefinitionObject2 = std::reinterpret_pointer_cast<SByteTimeseriesPropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = sByteTimeseriesPropertyDefinitionObject2->IsEqualTo( *sByteTimeseriesPropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SingleTimeseriesPropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( SingleTimeseriesPropertyDefinitionObjectSerializationTest )
{
    auto singleTimeseriesPropertyDefinitionObject1 = std::make_shared<SingleTimeseriesPropertyDefinitionObject>( );
    singleTimeseriesPropertyDefinitionObject1->SetId( Guid( L"{A67FFEFA-2C3D-83A1-C185-34BC65FE7F5F}" ) );
    singleTimeseriesPropertyDefinitionObject1->SetRowVersion( -8961833140192542982LL );
    singleTimeseriesPropertyDefinitionObject1->SetElementType( Guid( L"{A67FFEFA-2C3D-83A1-C185-34BC65FE7F5F}" ) );
    singleTimeseriesPropertyDefinitionObject1->SetName( L"Name" );
    singleTimeseriesPropertyDefinitionObject1->SetDescription( L"Description" );
    singleTimeseriesPropertyDefinitionObject1->SetMinValue( 9.48491e+15f );
    singleTimeseriesPropertyDefinitionObject1->SetMaxValue( 9.48491e+15f );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *singleTimeseriesPropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto singleTimeseriesPropertyDefinitionObject2 = std::reinterpret_pointer_cast<SingleTimeseriesPropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = singleTimeseriesPropertyDefinitionObject2->IsEqualTo( *singleTimeseriesPropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/StringTimeseriesPropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( StringTimeseriesPropertyDefinitionObjectSerializationTest )
{
    auto stringTimeseriesPropertyDefinitionObject1 = std::make_shared<StringTimeseriesPropertyDefinitionObject>( );
    stringTimeseriesPropertyDefinitionObject1->SetId( Guid( L"{C7C18C82-FC7B-A3D4-C52B-3FDEE3833141}" ) );
    stringTimeseriesPropertyDefinitionObject1->SetRowVersion( -6641405941902111614LL );
    stringTimeseriesPropertyDefinitionObject1->SetElementType( Guid( L"{C7C18C82-FC7B-A3D4-C52B-3FDEE3833141}" ) );
    stringTimeseriesPropertyDefinitionObject1->SetName( L"Name" );
    stringTimeseriesPropertyDefinitionObject1->SetDescription( L"Description" );
    stringTimeseriesPropertyDefinitionObject1->SetPattern( L"Pattern" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *stringTimeseriesPropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto stringTimeseriesPropertyDefinitionObject2 = std::reinterpret_pointer_cast<StringTimeseriesPropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = stringTimeseriesPropertyDefinitionObject2->IsEqualTo( *stringTimeseriesPropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TimeSpanTimeseriesPropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( TimeSpanTimeseriesPropertyDefinitionObjectSerializationTest )
{
    auto timeSpanTimeseriesPropertyDefinitionObject1 = std::make_shared<TimeSpanTimeseriesPropertyDefinitionObject>( );
    timeSpanTimeseriesPropertyDefinitionObject1->SetId( Guid( L"{C866A1C9-1559-99CA-9953-A89A13668593}" ) );
    timeSpanTimeseriesPropertyDefinitionObject1->SetRowVersion( -7365050765252582967LL );
    timeSpanTimeseriesPropertyDefinitionObject1->SetElementType( Guid( L"{C866A1C9-1559-99CA-9953-A89A13668593}" ) );
    timeSpanTimeseriesPropertyDefinitionObject1->SetName( L"Name" );
    timeSpanTimeseriesPropertyDefinitionObject1->SetDescription( L"Description" );
    timeSpanTimeseriesPropertyDefinitionObject1->SetMinValue( TimeSpan( -269252582967LL ) );
    timeSpanTimeseriesPropertyDefinitionObject1->SetMaxValue( TimeSpan( -269252582967LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *timeSpanTimeseriesPropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto timeSpanTimeseriesPropertyDefinitionObject2 = std::reinterpret_pointer_cast<TimeSpanTimeseriesPropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = timeSpanTimeseriesPropertyDefinitionObject2->IsEqualTo( *timeSpanTimeseriesPropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt16TimeseriesPropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( UInt16TimeseriesPropertyDefinitionObjectSerializationTest )
{
    auto uInt16TimeseriesPropertyDefinitionObject1 = std::make_shared<UInt16TimeseriesPropertyDefinitionObject>( );
    uInt16TimeseriesPropertyDefinitionObject1->SetId( Guid( L"{F3BC9551-294D-F34D-CFB2-94B2CF3DA98A}" ) );
    uInt16TimeseriesPropertyDefinitionObject1->SetRowVersion( -915029734507899567LL );
    uInt16TimeseriesPropertyDefinitionObject1->SetElementType( Guid( L"{F3BC9551-294D-F34D-CFB2-94B2CF3DA98A}" ) );
    uInt16TimeseriesPropertyDefinitionObject1->SetName( L"Name" );
    uInt16TimeseriesPropertyDefinitionObject1->SetDescription( L"Description" );
    uInt16TimeseriesPropertyDefinitionObject1->SetMinValue( 38225 );
    uInt16TimeseriesPropertyDefinitionObject1->SetMaxValue( 38225 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt16TimeseriesPropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt16TimeseriesPropertyDefinitionObject2 = std::reinterpret_pointer_cast<UInt16TimeseriesPropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = uInt16TimeseriesPropertyDefinitionObject2->IsEqualTo( *uInt16TimeseriesPropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt32TimeseriesPropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( UInt32TimeseriesPropertyDefinitionObjectSerializationTest )
{
    auto uInt32TimeseriesPropertyDefinitionObject1 = std::make_shared<UInt32TimeseriesPropertyDefinitionObject>( );
    uInt32TimeseriesPropertyDefinitionObject1->SetId( Guid( L"{D8704723-5980-F88B-1FD1-9A011B0EE2C4}" ) );
    uInt32TimeseriesPropertyDefinitionObject1->SetRowVersion( -537237320618719453LL );
    uInt32TimeseriesPropertyDefinitionObject1->SetElementType( Guid( L"{D8704723-5980-F88B-1FD1-9A011B0EE2C4}" ) );
    uInt32TimeseriesPropertyDefinitionObject1->SetName( L"Name" );
    uInt32TimeseriesPropertyDefinitionObject1->SetDescription( L"Description" );
    uInt32TimeseriesPropertyDefinitionObject1->SetMinValue( 3631236899UL );
    uInt32TimeseriesPropertyDefinitionObject1->SetMaxValue( 3631236899UL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt32TimeseriesPropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt32TimeseriesPropertyDefinitionObject2 = std::reinterpret_pointer_cast<UInt32TimeseriesPropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = uInt32TimeseriesPropertyDefinitionObject2->IsEqualTo( *uInt32TimeseriesPropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt64TimeseriesPropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( UInt64TimeseriesPropertyDefinitionObjectSerializationTest )
{
    auto uInt64TimeseriesPropertyDefinitionObject1 = std::make_shared<UInt64TimeseriesPropertyDefinitionObject>( );
    uInt64TimeseriesPropertyDefinitionObject1->SetId( Guid( L"{7229235C-4357-C2CC-4333-C2EA4E94C43A}" ) );
    uInt64TimeseriesPropertyDefinitionObject1->SetRowVersion( -4410075892246043812LL );
    uInt64TimeseriesPropertyDefinitionObject1->SetElementType( Guid( L"{7229235C-4357-C2CC-4333-C2EA4E94C43A}" ) );
    uInt64TimeseriesPropertyDefinitionObject1->SetName( L"Name" );
    uInt64TimeseriesPropertyDefinitionObject1->SetDescription( L"Description" );
    uInt64TimeseriesPropertyDefinitionObject1->SetMinValue( -4410075892246043812LL );
    uInt64TimeseriesPropertyDefinitionObject1->SetMaxValue( -4410075892246043812LL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt64TimeseriesPropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt64TimeseriesPropertyDefinitionObject2 = std::reinterpret_pointer_cast<UInt64TimeseriesPropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = uInt64TimeseriesPropertyDefinitionObject2->IsEqualTo( *uInt64TimeseriesPropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TimeSpanPropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( TimeSpanPropertyDefinitionObjectSerializationTest )
{
    auto timeSpanPropertyDefinitionObject1 = std::make_shared<TimeSpanPropertyDefinitionObject>( );
    timeSpanPropertyDefinitionObject1->SetId( Guid( L"{FB970DDC-44F0-59DE-9A7B-220FDFE9B03B}" ) );
    timeSpanPropertyDefinitionObject1->SetRowVersion( 6475689116009172444LL );
    timeSpanPropertyDefinitionObject1->SetElementType( Guid( L"{FB970DDC-44F0-59DE-9A7B-220FDFE9B03B}" ) );
    timeSpanPropertyDefinitionObject1->SetName( L"Name" );
    timeSpanPropertyDefinitionObject1->SetDescription( L"Description" );
    timeSpanPropertyDefinitionObject1->SetDefaultValue( TimeSpan( 476009172444LL ) );
    timeSpanPropertyDefinitionObject1->SetMinValue( TimeSpan( 476009172444LL ) );
    timeSpanPropertyDefinitionObject1->SetMaxValue( TimeSpan( 476009172444LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *timeSpanPropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto timeSpanPropertyDefinitionObject2 = std::reinterpret_pointer_cast<TimeSpanPropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = timeSpanPropertyDefinitionObject2->IsEqualTo( *timeSpanPropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt16PropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( UInt16PropertyDefinitionObjectSerializationTest )
{
    auto uInt16PropertyDefinitionObject1 = std::make_shared<UInt16PropertyDefinitionObject>( );
    uInt16PropertyDefinitionObject1->SetId( Guid( L"{9F86CE66-6677-86AB-61D5-66EEF9617366}" ) );
    uInt16PropertyDefinitionObject1->SetRowVersion( -8742781587646132634LL );
    uInt16PropertyDefinitionObject1->SetElementType( Guid( L"{9F86CE66-6677-86AB-61D5-66EEF9617366}" ) );
    uInt16PropertyDefinitionObject1->SetName( L"Name" );
    uInt16PropertyDefinitionObject1->SetDescription( L"Description" );
    uInt16PropertyDefinitionObject1->SetDefaultValue( 52838 );
    uInt16PropertyDefinitionObject1->SetMinValue( 52838 );
    uInt16PropertyDefinitionObject1->SetMaxValue( 52838 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt16PropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt16PropertyDefinitionObject2 = std::reinterpret_pointer_cast<UInt16PropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = uInt16PropertyDefinitionObject2->IsEqualTo( *uInt16PropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt32PropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( UInt32PropertyDefinitionObjectSerializationTest )
{
    auto uInt32PropertyDefinitionObject1 = std::make_shared<UInt32PropertyDefinitionObject>( );
    uInt32PropertyDefinitionObject1->SetId( Guid( L"{6B546007-C7C5-E702-E740-E3A3D62A06E0}" ) );
    uInt32PropertyDefinitionObject1->SetRowVersion( -1800657250271600633LL );
    uInt32PropertyDefinitionObject1->SetElementType( Guid( L"{6B546007-C7C5-E702-E740-E3A3D62A06E0}" ) );
    uInt32PropertyDefinitionObject1->SetName( L"Name" );
    uInt32PropertyDefinitionObject1->SetDescription( L"Description" );
    uInt32PropertyDefinitionObject1->SetDefaultValue( 1800691719UL );
    uInt32PropertyDefinitionObject1->SetMinValue( 1800691719UL );
    uInt32PropertyDefinitionObject1->SetMaxValue( 1800691719UL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt32PropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt32PropertyDefinitionObject2 = std::reinterpret_pointer_cast<UInt32PropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = uInt32PropertyDefinitionObject2->IsEqualTo( *uInt32PropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt64PropertyDefinitionObjectSerializationTest
BOOST_AUTO_TEST_CASE( UInt64PropertyDefinitionObjectSerializationTest )
{
    auto uInt64PropertyDefinitionObject1 = std::make_shared<UInt64PropertyDefinitionObject>( );
    uInt64PropertyDefinitionObject1->SetId( Guid( L"{7E8D58B1-7982-8BF7-D1EF-9E417EB11A8D}" ) );
    uInt64PropertyDefinitionObject1->SetRowVersion( -8361080581814134607LL );
    uInt64PropertyDefinitionObject1->SetElementType( Guid( L"{7E8D58B1-7982-8BF7-D1EF-9E417EB11A8D}" ) );
    uInt64PropertyDefinitionObject1->SetName( L"Name" );
    uInt64PropertyDefinitionObject1->SetDescription( L"Description" );
    uInt64PropertyDefinitionObject1->SetDefaultValue( -8361080581814134607LL );
    uInt64PropertyDefinitionObject1->SetMinValue( -8361080581814134607LL );
    uInt64PropertyDefinitionObject1->SetMaxValue( -8361080581814134607LL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt64PropertyDefinitionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt64PropertyDefinitionObject2 = std::reinterpret_pointer_cast<UInt64PropertyDefinitionObject>( ReadDataFrom( source ) );
    bool equal = uInt64PropertyDefinitionObject2->IsEqualTo( *uInt64PropertyDefinitionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarAlarmStatusObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarAlarmStatusObjectSerializationTest )
{
    auto radarAlarmStatusObject1 = std::make_shared<RadarAlarmStatusObject>( );
    radarAlarmStatusObject1->SetId( Guid( L"{6591FD22-1881-3763-ECC6-1881A689BF44}" ) );
    radarAlarmStatusObject1->SetRowVersion( 3991060638814305570LL );
    radarAlarmStatusObject1->SetRadar( Guid( L"{6591FD22-1881-3763-ECC6-1881A689BF44}" ) );
    radarAlarmStatusObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    radarAlarmStatusObject1->SetType( AlarmState::Raised );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarAlarmStatusObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarAlarmStatusObject2 = std::reinterpret_pointer_cast<RadarAlarmStatusObject>( ReadDataFrom( source ) );
    bool equal = radarAlarmStatusObject2->IsEqualTo( *radarAlarmStatusObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarCommandObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarCommandObjectSerializationTest )
{
    auto radarCommandObject1 = std::make_shared<RadarCommandObject>( );
    radarCommandObject1->SetId( Guid( L"{09E2F261-F724-AF90-F509-EF2490474F86}" ) );
    radarCommandObject1->SetRowVersion( -5795860986269076895LL );
    radarCommandObject1->SetRadar( Guid( L"{09E2F261-F724-AF90-F509-EF2490474F86}" ) );
    radarCommandObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    radarCommandObject1->SetDeviceCommandSourceType( DeviceCommandSourceType::Session );
    radarCommandObject1->SetDeviceCommandSourceId( Guid( L"{09E2F261-F724-AF90-F509-EF2490474F86}" ) );
    radarCommandObject1->SetReply( Guid( L"{09E2F261-F724-AF90-F509-EF2490474F86}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarCommandObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarCommandObject2 = std::reinterpret_pointer_cast<RadarCommandObject>( ReadDataFrom( source ) );
    bool equal = radarCommandObject2->IsEqualTo( *radarCommandObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarCommandGetStatusObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarCommandGetStatusObjectSerializationTest )
{
    auto radarCommandGetStatusObject1 = std::make_shared<RadarCommandGetStatusObject>( );
    radarCommandGetStatusObject1->SetId( Guid( L"{15DB63DD-58A5-93F1-C98F-1AA5A8DBC6BB}" ) );
    radarCommandGetStatusObject1->SetRowVersion( -7786344814687329315LL );
    radarCommandGetStatusObject1->SetRadar( Guid( L"{15DB63DD-58A5-93F1-C98F-1AA5A8DBC6BB}" ) );
    radarCommandGetStatusObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    radarCommandGetStatusObject1->SetDeviceCommandSourceType( DeviceCommandSourceType::Session );
    radarCommandGetStatusObject1->SetDeviceCommandSourceId( Guid( L"{15DB63DD-58A5-93F1-C98F-1AA5A8DBC6BB}" ) );
    radarCommandGetStatusObject1->SetReply( Guid( L"{15DB63DD-58A5-93F1-C98F-1AA5A8DBC6BB}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarCommandGetStatusObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarCommandGetStatusObject2 = std::reinterpret_pointer_cast<RadarCommandGetStatusObject>( ReadDataFrom( source ) );
    bool equal = radarCommandGetStatusObject2->IsEqualTo( *radarCommandGetStatusObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarCommandReplyObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarCommandReplyObjectSerializationTest )
{
    auto radarCommandReplyObject1 = std::make_shared<RadarCommandReplyObject>( );
    radarCommandReplyObject1->SetId( Guid( L"{A338B9CF-C23E-6B8E-D671-437CC51C9DF3}" ) );
    radarCommandReplyObject1->SetRowVersion( 7750345583033366991LL );
    radarCommandReplyObject1->SetRadar( Guid( L"{A338B9CF-C23E-6B8E-D671-437CC51C9DF3}" ) );
    radarCommandReplyObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    radarCommandReplyObject1->SetCommand( Guid( L"{A338B9CF-C23E-6B8E-D671-437CC51C9DF3}" ) );
    radarCommandReplyObject1->SetStatus( DeviceCommandReplyStatus::Error );
    radarCommandReplyObject1->SetMessage( L"Message" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarCommandReplyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarCommandReplyObject2 = std::reinterpret_pointer_cast<RadarCommandReplyObject>( ReadDataFrom( source ) );
    bool equal = radarCommandReplyObject2->IsEqualTo( *radarCommandReplyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarCommandReplyGetStatusObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarCommandReplyGetStatusObjectSerializationTest )
{
    auto radarCommandReplyGetStatusObject1 = std::make_shared<RadarCommandReplyGetStatusObject>( );
    radarCommandReplyGetStatusObject1->SetId( Guid( L"{76904A9F-BEF0-E591-A789-7D0F6E0952F9}" ) );
    radarCommandReplyGetStatusObject1->SetRowVersion( -1904531227410412897LL );
    radarCommandReplyGetStatusObject1->SetRadar( Guid( L"{76904A9F-BEF0-E591-A789-7D0F6E0952F9}" ) );
    radarCommandReplyGetStatusObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    radarCommandReplyGetStatusObject1->SetCommand( Guid( L"{76904A9F-BEF0-E591-A789-7D0F6E0952F9}" ) );
    radarCommandReplyGetStatusObject1->SetStatus( DeviceCommandReplyStatus::Error );
    radarCommandReplyGetStatusObject1->SetMessage( L"Message" );
    radarCommandReplyGetStatusObject1->SetAzimuthCount( 1989167775L );
    radarCommandReplyGetStatusObject1->SetTriggerCount( 1989167775L );
    radarCommandReplyGetStatusObject1->SetRotationCount( TimeSpan( -475410412897LL ) );
    radarCommandReplyGetStatusObject1->SetPulse( RadarPulse::Short );
    radarCommandReplyGetStatusObject1->SetTx( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarCommandReplyGetStatusObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarCommandReplyGetStatusObject2 = std::reinterpret_pointer_cast<RadarCommandReplyGetStatusObject>( ReadDataFrom( source ) );
    bool equal = radarCommandReplyGetStatusObject2->IsEqualTo( *radarCommandReplyGetStatusObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarConfigurationObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarConfigurationObjectSerializationTest )
{
    auto radarConfigurationObject1 = std::make_shared<RadarConfigurationObject>( );
    radarConfigurationObject1->SetId( Guid( L"{B52CAF4D-4966-5963-9AC6-9266AD34F5B2}" ) );
    radarConfigurationObject1->SetRowVersion( 6441072597545037645LL );
    radarConfigurationObject1->SetRadar( Guid( L"{B52CAF4D-4966-5963-9AC6-9266AD34F5B2}" ) );
    radarConfigurationObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    radarConfigurationObject1->SetRadarProtocolVersion( -1255362739L );
    radarConfigurationObject1->SetRadarIPAddress( L"RadarIPAddress" );
    radarConfigurationObject1->SetRadarPort( -1255362739L );
    radarConfigurationObject1->SetRadarConfigurationPort( -1255362739L );
    radarConfigurationObject1->SetSkipMagicTimeout( TimeSpan( 117545037645LL ) );
    radarConfigurationObject1->SetReadTimeout( TimeSpan( 117545037645LL ) );
    radarConfigurationObject1->SetSynchronizationInterval( TimeSpan( 117545037645LL ) );
    radarConfigurationObject1->SetTargetsRefreshRate( -1255362739L );
    radarConfigurationObject1->SetRange( -1255362739L );
    radarConfigurationObject1->SetSectorCount( -1255362739L );
    radarConfigurationObject1->SetSectorOffset( -1255362739L );
    radarConfigurationObject1->SetImageColor( 3039604557UL );
    radarConfigurationObject1->SetImageSubstitutionColor( 3039604557UL );
    radarConfigurationObject1->SetTransparentColor( 3039604557UL );
    radarConfigurationObject1->SetImageScaleFactorX( 6441072597545038 );
    radarConfigurationObject1->SetImageOffsetX( 6441072597545038 );
    radarConfigurationObject1->SetImageScaleFactorY( 6441072597545038 );
    radarConfigurationObject1->SetImageOffsetY( 6441072597545038 );
    radarConfigurationObject1->SetRadarImageType( RadarImageType::VideoMask );
    radarConfigurationObject1->SetTrackColor( 3039604557UL );
    radarConfigurationObject1->SetVectorColor( 3039604557UL );
    radarConfigurationObject1->SetEnableNmea( false );
    radarConfigurationObject1->SetNmeaReceiverIPAddress( L"NmeaReceiverIPAddress" );
    radarConfigurationObject1->SetNmeaReceiverPort( -1255362739L );
    radarConfigurationObject1->SetNmeaReceiverSourceId( L"NmeaReceiverSourceId" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarConfigurationObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarConfigurationObject2 = std::reinterpret_pointer_cast<RadarConfigurationObject>( ReadDataFrom( source ) );
    bool equal = radarConfigurationObject2->IsEqualTo( *radarConfigurationObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarImageObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarImageObjectSerializationTest )
{
    auto radarImageObject1 = std::make_shared<RadarImageObject>( );
    radarImageObject1->SetId( Guid( L"{E255597A-EAB9-8A6B-51D6-579D47AA9A5E}" ) );
    radarImageObject1->SetRowVersion( -8472420189880362630LL );
    radarImageObject1->SetRadar( Guid( L"{E255597A-EAB9-8A6B-51D6-579D47AA9A5E}" ) );
    radarImageObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    radarImageObject1->SetDepth( 3797244282UL );
    radarImageObject1->SetResolution( -497723014L );
    radarImageObject1->SetRange( -497723014L );
    radarImageObject1->SetImage( { {'I','m','a','g','e'} } );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarImageObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarImageObject2 = std::reinterpret_pointer_cast<RadarImageObject>( ReadDataFrom( source ) );
    bool equal = radarImageObject2->IsEqualTo( *radarImageObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarRawTrackTableObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarRawTrackTableObjectSerializationTest )
{
    auto radarRawTrackTableObject1 = std::make_shared<RadarRawTrackTableObject>( );
    radarRawTrackTableObject1->SetId( Guid( L"{987A5FFC-22C5-4193-82C9-44A3195EFA3F}" ) );
    radarRawTrackTableObject1->SetRowVersion( 4725158666103840764LL );
    radarRawTrackTableObject1->SetRadar( Guid( L"{987A5FFC-22C5-4193-82C9-44A3195EFA3F}" ) );
    radarRawTrackTableObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    radarRawTrackTableObject1->SetCount( -1736810500L );
    radarRawTrackTableObject1->SetTable( { {'T','a','b','l','e'} } );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarRawTrackTableObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarRawTrackTableObject2 = std::reinterpret_pointer_cast<RadarRawTrackTableObject>( ReadDataFrom( source ) );
    bool equal = radarRawTrackTableObject2->IsEqualTo( *radarRawTrackTableObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarStatusObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarStatusObjectSerializationTest )
{
    auto radarStatusObject1 = std::make_shared<RadarStatusObject>( );
    radarStatusObject1->SetId( Guid( L"{02607B8B-1D3F-7C67-3EE6-B8FC4006DED1}" ) );
    radarStatusObject1->SetRowVersion( 8964165739764284299LL );
    radarStatusObject1->SetRadar( Guid( L"{02607B8B-1D3F-7C67-3EE6-B8FC4006DED1}" ) );
    radarStatusObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    radarStatusObject1->SetAzimuthCount( 39877515L );
    radarStatusObject1->SetTriggerCount( 39877515L );
    radarStatusObject1->SetRotationTime( TimeSpan( 715764284299LL ) );
    radarStatusObject1->SetPulse( RadarPulse::Medium );
    radarStatusObject1->SetTx( false );
    radarStatusObject1->SetTracking( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarStatusObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarStatusObject2 = std::reinterpret_pointer_cast<RadarStatusObject>( ReadDataFrom( source ) );
    bool equal = radarStatusObject2->IsEqualTo( *radarStatusObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadioCommandObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadioCommandObjectSerializationTest )
{
    auto radioCommandObject1 = std::make_shared<RadioCommandObject>( );
    radioCommandObject1->SetId( Guid( L"{2E60CDCD-C816-0913-90C8-13687406B3B3}" ) );
    radioCommandObject1->SetRowVersion( 654086368491785677LL );
    radioCommandObject1->SetRadio( Guid( L"{2E60CDCD-C816-0913-90C8-13687406B3B3}" ) );
    radioCommandObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    radioCommandObject1->SetDeviceCommandSourceType( DeviceCommandSourceType::Session );
    radioCommandObject1->SetDeviceCommandSourceId( Guid( L"{2E60CDCD-C816-0913-90C8-13687406B3B3}" ) );
    radioCommandObject1->SetReply( Guid( L"{2E60CDCD-C816-0913-90C8-13687406B3B3}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radioCommandObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radioCommandObject2 = std::reinterpret_pointer_cast<RadioCommandObject>( ReadDataFrom( source ) );
    bool equal = radioCommandObject2->IsEqualTo( *radioCommandObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadioCommandReplyObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadioCommandReplyObjectSerializationTest )
{
    auto radioCommandReplyObject1 = std::make_shared<RadioCommandReplyObject>( );
    radioCommandReplyObject1->SetId( Guid( L"{4196677A-F28B-98D7-19EB-4FD18269E65E}" ) );
    radioCommandReplyObject1->SetRowVersion( -7433205980036962438LL );
    radioCommandReplyObject1->SetRadio( Guid( L"{4196677A-F28B-98D7-19EB-4FD18269E65E}" ) );
    radioCommandReplyObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    radioCommandReplyObject1->SetCommand( Guid( L"{4196677A-F28B-98D7-19EB-4FD18269E65E}" ) );
    radioCommandReplyObject1->SetStatus( DeviceCommandReplyStatus::NotImplemented );
    radioCommandReplyObject1->SetMessage( L"Message" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radioCommandReplyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radioCommandReplyObject2 = std::reinterpret_pointer_cast<RadioCommandReplyObject>( ReadDataFrom( source ) );
    bool equal = radioCommandReplyObject2->IsEqualTo( *radioCommandReplyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadioConfigurationObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadioConfigurationObjectSerializationTest )
{
    auto radioConfigurationObject1 = std::make_shared<RadioConfigurationObject>( );
    radioConfigurationObject1->SetId( Guid( L"{AB4C66CF-5346-E4F6-276F-CA62D53266F3}" ) );
    radioConfigurationObject1->SetRowVersion( -1948278225804433713LL );
    radioConfigurationObject1->SetRadio( Guid( L"{AB4C66CF-5346-E4F6-276F-CA62D53266F3}" ) );
    radioConfigurationObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    radioConfigurationObject1->SetLongitude( 16498465847905118 );
    radioConfigurationObject1->SetLatitude( 16498465847905118 );
    radioConfigurationObject1->SetPlaybackUrl( L"PlaybackUrl" );
    radioConfigurationObject1->SetRadioIPAddress( L"RadioIPAddress" );
    radioConfigurationObject1->SetRadioPort( -1421056305L );
    radioConfigurationObject1->SetEd137IPAddress( L"Ed137IPAddress" );
    radioConfigurationObject1->SetEd137Port( -1421056305L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radioConfigurationObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radioConfigurationObject2 = std::reinterpret_pointer_cast<RadioConfigurationObject>( ReadDataFrom( source ) );
    bool equal = radioConfigurationObject2->IsEqualTo( *radioConfigurationObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadomeCommandObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadomeCommandObjectSerializationTest )
{
    auto radomeCommandObject1 = std::make_shared<RadomeCommandObject>( );
    radomeCommandObject1->SetId( Guid( L"{3C06BA91-1621-4C7A-325E-68843C605D89}" ) );
    radomeCommandObject1->SetRowVersion( 5510741426038028945LL );
    radomeCommandObject1->SetRadome( Guid( L"{3C06BA91-1621-4C7A-325E-68843C605D89}" ) );
    radomeCommandObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    radomeCommandObject1->SetDeviceCommandSourceType( DeviceCommandSourceType::Session );
    radomeCommandObject1->SetDeviceCommandSourceId( Guid( L"{3C06BA91-1621-4C7A-325E-68843C605D89}" ) );
    radomeCommandObject1->SetReply( Guid( L"{3C06BA91-1621-4C7A-325E-68843C605D89}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radomeCommandObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radomeCommandObject2 = std::reinterpret_pointer_cast<RadomeCommandObject>( ReadDataFrom( source ) );
    bool equal = radomeCommandObject2->IsEqualTo( *radomeCommandObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadomeCommandReplyObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadomeCommandReplyObjectSerializationTest )
{
    auto radomeCommandReplyObject1 = std::make_shared<RadomeCommandReplyObject>( );
    radomeCommandReplyObject1->SetId( Guid( L"{6A296804-C699-97E0-E907-639956941620}" ) );
    radomeCommandReplyObject1->SetRowVersion( -7502778616985851900LL );
    radomeCommandReplyObject1->SetRadome( Guid( L"{6A296804-C699-97E0-E907-639956941620}" ) );
    radomeCommandReplyObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    radomeCommandReplyObject1->SetCommand( Guid( L"{6A296804-C699-97E0-E907-639956941620}" ) );
    radomeCommandReplyObject1->SetStatus( DeviceCommandReplyStatus::Unknown );
    radomeCommandReplyObject1->SetMessage( L"Message" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radomeCommandReplyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radomeCommandReplyObject2 = std::reinterpret_pointer_cast<RadomeCommandReplyObject>( ReadDataFrom( source ) );
    bool equal = radomeCommandReplyObject2->IsEqualTo( *radomeCommandReplyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadomeConfigurationObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadomeConfigurationObjectSerializationTest )
{
    auto radomeConfigurationObject1 = std::make_shared<RadomeConfigurationObject>( );
    radomeConfigurationObject1->SetId( Guid( L"{2F8DD664-7BE7-739B-CED9-DEE7F4B16B26}" ) );
    radomeConfigurationObject1->SetRowVersion( 8330388168617350756LL );
    radomeConfigurationObject1->SetRadome( Guid( L"{2F8DD664-7BE7-739B-CED9-DEE7F4B16B26}" ) );
    radomeConfigurationObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    radomeConfigurationObject1->SetInterval( TimeSpan( 840617350756LL ) );
    radomeConfigurationObject1->SetLowPressureLimit( 8330388168617351 );
    radomeConfigurationObject1->SetHighPressureLimit( 8330388168617351 );
    radomeConfigurationObject1->SetLowTemperatureLimit( 8330388168617351 );
    radomeConfigurationObject1->SetHighTemperatureLimit( 8330388168617351 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radomeConfigurationObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radomeConfigurationObject2 = std::reinterpret_pointer_cast<RadomeConfigurationObject>( ReadDataFrom( source ) );
    bool equal = radomeConfigurationObject2->IsEqualTo( *radomeConfigurationObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ReferenceTimeseriesValueObjectSerializationTest
BOOST_AUTO_TEST_CASE( ReferenceTimeseriesValueObjectSerializationTest )
{
    auto referenceTimeseriesValueObject1 = std::make_shared<ReferenceTimeseriesValueObject>( );
    referenceTimeseriesValueObject1->SetId( Guid( L"{6F4E97CF-FE10-6D89-B691-7F08F672E9F3}" ) );
    referenceTimeseriesValueObject1->SetRowVersion( 7893119168483858383LL );
    referenceTimeseriesValueObject1->SetTimeseries( Guid( L"{6F4E97CF-FE10-6D89-B691-7F08F672E9F3}" ) );
    referenceTimeseriesValueObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    referenceTimeseriesValueObject1->SetValue( Guid( L"{6F4E97CF-FE10-6D89-B691-7F08F672E9F3}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *referenceTimeseriesValueObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto referenceTimeseriesValueObject2 = std::reinterpret_pointer_cast<ReferenceTimeseriesValueObject>( ReadDataFrom( source ) );
    bool equal = referenceTimeseriesValueObject2->IsEqualTo( *referenceTimeseriesValueObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SByteTimeseriesValueObjectSerializationTest
BOOST_AUTO_TEST_CASE( SByteTimeseriesValueObjectSerializationTest )
{
    auto sByteTimeseriesValueObject1 = std::make_shared<SByteTimeseriesValueObject>( );
    sByteTimeseriesValueObject1->SetId( Guid( L"{250A9ACA-1D35-8290-4109-B8ACA4505953}" ) );
    sByteTimeseriesValueObject1->SetRowVersion( -9038692338040661302LL );
    sByteTimeseriesValueObject1->SetTimeseries( Guid( L"{250A9ACA-1D35-8290-4109-B8ACA4505953}" ) );
    sByteTimeseriesValueObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    sByteTimeseriesValueObject1->SetValue( -54 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *sByteTimeseriesValueObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto sByteTimeseriesValueObject2 = std::reinterpret_pointer_cast<SByteTimeseriesValueObject>( ReadDataFrom( source ) );
    bool equal = sByteTimeseriesValueObject2->IsEqualTo( *sByteTimeseriesValueObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SecurityDomainObjectSerializationTest
BOOST_AUTO_TEST_CASE( SecurityDomainObjectSerializationTest )
{
    auto securityDomainObject1 = std::make_shared<SecurityDomainObject>( );
    securityDomainObject1->SetId( Guid( L"{C42DB715-5D41-31B3-8CCD-BA8223B4EDA8}" ) );
    securityDomainObject1->SetRowVersion( 3581308665735264021LL );
    securityDomainObject1->SetName( L"Name" );
    securityDomainObject1->SetDescription( L"Description" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *securityDomainObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto securityDomainObject2 = std::reinterpret_pointer_cast<SecurityDomainObject>( ReadDataFrom( source ) );
    bool equal = securityDomainObject2->IsEqualTo( *securityDomainObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SecurityLoginObjectSerializationTest
BOOST_AUTO_TEST_CASE( SecurityLoginObjectSerializationTest )
{
    auto securityLoginObject1 = std::make_shared<SecurityLoginObject>( );
    securityLoginObject1->SetId( Guid( L"{2E8F8FDB-0425-DED8-7B1B-20A474F1F1DB}" ) );
    securityLoginObject1->SetRowVersion( -2389155044578586661LL );
    securityLoginObject1->SetDomain( Guid( L"{2E8F8FDB-0425-DED8-7B1B-20A474F1F1DB}" ) );
    securityLoginObject1->SetIdentity( L"Identity" );
    securityLoginObject1->SetDescription( L"Description" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *securityLoginObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto securityLoginObject2 = std::reinterpret_pointer_cast<SecurityLoginObject>( ReadDataFrom( source ) );
    bool equal = securityLoginObject2->IsEqualTo( *securityLoginObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SecurityRoleObjectSerializationTest
BOOST_AUTO_TEST_CASE( SecurityRoleObjectSerializationTest )
{
    auto securityRoleObject1 = std::make_shared<SecurityRoleObject>( );
    securityRoleObject1->SetId( Guid( L"{4563987E-AA39-307D-0CBE-559CA2C6197E}" ) );
    securityRoleObject1->SetRowVersion( 3494136048863385726LL );
    securityRoleObject1->SetDomain( Guid( L"{4563987E-AA39-307D-0CBE-559CA2C6197E}" ) );
    securityRoleObject1->SetIdentity( L"Identity" );
    securityRoleObject1->SetDescription( L"Description" );
    securityRoleObject1->SetName( L"Name" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *securityRoleObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto securityRoleObject2 = std::reinterpret_pointer_cast<SecurityRoleObject>( ReadDataFrom( source ) );
    bool equal = securityRoleObject2->IsEqualTo( *securityRoleObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SecurityIdentifierRoleLinkObjectSerializationTest
BOOST_AUTO_TEST_CASE( SecurityIdentifierRoleLinkObjectSerializationTest )
{
    auto securityIdentifierRoleLinkObject1 = std::make_shared<SecurityIdentifierRoleLinkObject>( );
    securityIdentifierRoleLinkObject1->SetId( Guid( L"{08CD1B89-2160-C19D-83B9-840610B3D891}" ) );
    securityIdentifierRoleLinkObject1->SetRowVersion( -4495400156697650295LL );
    securityIdentifierRoleLinkObject1->SetMember( Guid( L"{08CD1B89-2160-C19D-83B9-840610B3D891}" ) );
    securityIdentifierRoleLinkObject1->SetRole( Guid( L"{08CD1B89-2160-C19D-83B9-840610B3D891}" ) );
    securityIdentifierRoleLinkObject1->SetStart( DateTime( 1, 1, 1, 22, 23, 35 ) );
    securityIdentifierRoleLinkObject1->SetEnd( DateTime( 1, 1, 1, 22, 23, 35 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *securityIdentifierRoleLinkObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto securityIdentifierRoleLinkObject2 = std::reinterpret_pointer_cast<SecurityIdentifierRoleLinkObject>( ReadDataFrom( source ) );
    bool equal = securityIdentifierRoleLinkObject2->IsEqualTo( *securityIdentifierRoleLinkObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SecurityLoginSessionObjectSerializationTest
BOOST_AUTO_TEST_CASE( SecurityLoginSessionObjectSerializationTest )
{
    auto securityLoginSessionObject1 = std::make_shared<SecurityLoginSessionObject>( );
    securityLoginSessionObject1->SetId( Guid( L"{1600A37D-D48F-A2D7-45EB-2BF16800C5BE}" ) );
    securityLoginSessionObject1->SetRowVersion( -6712663008557882499LL );
    securityLoginSessionObject1->SetLogin( Guid( L"{1600A37D-D48F-A2D7-45EB-2BF16800C5BE}" ) );
    securityLoginSessionObject1->SetFromTime( DateTime( 1, 1, 1, 22, 23, 35 ) );
    securityLoginSessionObject1->SetThroughTime( DateTime( 1, 1, 1, 22, 23, 35 ) );
    securityLoginSessionObject1->SetClientSession( Guid( L"{1600A37D-D48F-A2D7-45EB-2BF16800C5BE}" ) );
    securityLoginSessionObject1->SetNotificationQueueName( L"NotificationQueueName" );
    securityLoginSessionObject1->SetMessageQueueName( L"MessageQueueName" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *securityLoginSessionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto securityLoginSessionObject2 = std::reinterpret_pointer_cast<SecurityLoginSessionObject>( ReadDataFrom( source ) );
    bool equal = securityLoginSessionObject2->IsEqualTo( *securityLoginSessionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SecurityPermissionObjectSerializationTest
BOOST_AUTO_TEST_CASE( SecurityPermissionObjectSerializationTest )
{
    auto securityPermissionObject1 = std::make_shared<SecurityPermissionObject>( );
    securityPermissionObject1->SetId( Guid( L"{9A65967B-785F-8F6C-F136-1EFA59A669DE}" ) );
    securityPermissionObject1->SetRowVersion( -8111976476793530757LL );
    securityPermissionObject1->SetIdentifier( Guid( L"{9A65967B-785F-8F6C-F136-1EFA59A669DE}" ) );
    securityPermissionObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    securityPermissionObject1->SetTypeCode( -1704618373L );
    securityPermissionObject1->SetCanCreate( false );
    securityPermissionObject1->SetCanRead( false );
    securityPermissionObject1->SetCanUpdate( false );
    securityPermissionObject1->SetCanDelete( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *securityPermissionObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto securityPermissionObject2 = std::reinterpret_pointer_cast<SecurityPermissionObject>( ReadDataFrom( source ) );
    bool equal = securityPermissionObject2->IsEqualTo( *securityPermissionObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SingleTimeseriesValueObjectSerializationTest
BOOST_AUTO_TEST_CASE( SingleTimeseriesValueObjectSerializationTest )
{
    auto singleTimeseriesValueObject1 = std::make_shared<SingleTimeseriesValueObject>( );
    singleTimeseriesValueObject1->SetId( Guid( L"{295C3FB9-5436-1E12-7848-2A6C943AFC9D}" ) );
    singleTimeseriesValueObject1->SetRowVersion( 2166886962317508537LL );
    singleTimeseriesValueObject1->SetTimeseries( Guid( L"{295C3FB9-5436-1E12-7848-2A6C943AFC9D}" ) );
    singleTimeseriesValueObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    singleTimeseriesValueObject1->SetValue( 2.166887e+15f );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *singleTimeseriesValueObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto singleTimeseriesValueObject2 = std::reinterpret_pointer_cast<SingleTimeseriesValueObject>( ReadDataFrom( source ) );
    bool equal = singleTimeseriesValueObject2->IsEqualTo( *singleTimeseriesValueObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/StringTimeseriesValueObjectSerializationTest
BOOST_AUTO_TEST_CASE( StringTimeseriesValueObjectSerializationTest )
{
    auto stringTimeseriesValueObject1 = std::make_shared<StringTimeseriesValueObject>( );
    stringTimeseriesValueObject1->SetId( Guid( L"{8151E4E0-9099-AD75-B5AE-0999818A2707}" ) );
    stringTimeseriesValueObject1->SetRowVersion( -5947688743898848032LL );
    stringTimeseriesValueObject1->SetTimeseries( Guid( L"{8151E4E0-9099-AD75-B5AE-0999818A2707}" ) );
    stringTimeseriesValueObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    stringTimeseriesValueObject1->SetValue( L"Value" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *stringTimeseriesValueObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto stringTimeseriesValueObject2 = std::reinterpret_pointer_cast<StringTimeseriesValueObject>( ReadDataFrom( source ) );
    bool equal = stringTimeseriesValueObject2->IsEqualTo( *stringTimeseriesValueObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BinaryTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( BinaryTimeseriesObjectSerializationTest )
{
    auto binaryTimeseriesObject1 = std::make_shared<BinaryTimeseriesObject>( );
    binaryTimeseriesObject1->SetId( Guid( L"{56BB9C30-67A4-E01F-07F8-E6256ADD390C}" ) );
    binaryTimeseriesObject1->SetRowVersion( -2297003329408230352LL );
    binaryTimeseriesObject1->SetCatalog( Guid( L"{56BB9C30-67A4-E01F-07F8-E6256ADD390C}" ) );
    binaryTimeseriesObject1->SetName( L"Name" );
    binaryTimeseriesObject1->SetMaxRetention( TimeSpan( -577408230352LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *binaryTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto binaryTimeseriesObject2 = std::reinterpret_pointer_cast<BinaryTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = binaryTimeseriesObject2->IsEqualTo( *binaryTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BooleanTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( BooleanTimeseriesObjectSerializationTest )
{
    auto booleanTimeseriesObject1 = std::make_shared<BooleanTimeseriesObject>( );
    booleanTimeseriesObject1->SetId( Guid( L"{02D3DF65-9199-E4BC-273D-899940CBFBA6}" ) );
    booleanTimeseriesObject1->SetRowVersion( -1964535251076915355LL );
    booleanTimeseriesObject1->SetCatalog( Guid( L"{02D3DF65-9199-E4BC-273D-899940CBFBA6}" ) );
    booleanTimeseriesObject1->SetName( L"Name" );
    booleanTimeseriesObject1->SetMaxRetention( TimeSpan( -563076915355LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *booleanTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto booleanTimeseriesObject2 = std::reinterpret_pointer_cast<BooleanTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = booleanTimeseriesObject2->IsEqualTo( *booleanTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisAidToNavigationOffPositionTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisAidToNavigationOffPositionTimeseriesObjectSerializationTest )
{
    auto aisAidToNavigationOffPositionTimeseriesObject1 = std::make_shared<AisAidToNavigationOffPositionTimeseriesObject>( );
    aisAidToNavigationOffPositionTimeseriesObject1->SetId( Guid( L"{89D69A77-42AE-1C8E-3871-4275916B59EE}" ) );
    aisAidToNavigationOffPositionTimeseriesObject1->SetRowVersion( 2057655397159180919LL );
    aisAidToNavigationOffPositionTimeseriesObject1->SetCatalog( Guid( L"{89D69A77-42AE-1C8E-3871-4275916B59EE}" ) );
    aisAidToNavigationOffPositionTimeseriesObject1->SetName( L"Name" );
    aisAidToNavigationOffPositionTimeseriesObject1->SetMaxRetention( TimeSpan( 517159180919LL ) );
    aisAidToNavigationOffPositionTimeseriesObject1->SetAidToNavigation( Guid( L"{89D69A77-42AE-1C8E-3871-4275916B59EE}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisAidToNavigationOffPositionTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisAidToNavigationOffPositionTimeseriesObject2 = std::reinterpret_pointer_cast<AisAidToNavigationOffPositionTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = aisAidToNavigationOffPositionTimeseriesObject2->IsEqualTo( *aisAidToNavigationOffPositionTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DeviceEnabledTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( DeviceEnabledTimeseriesObjectSerializationTest )
{
    auto deviceEnabledTimeseriesObject1 = std::make_shared<DeviceEnabledTimeseriesObject>( );
    deviceEnabledTimeseriesObject1->SetId( Guid( L"{69D0497B-894C-9769-E996-9132960B92DE}" ) );
    deviceEnabledTimeseriesObject1->SetRowVersion( -7536341540142036613LL );
    deviceEnabledTimeseriesObject1->SetCatalog( Guid( L"{69D0497B-894C-9769-E996-9132960B92DE}" ) );
    deviceEnabledTimeseriesObject1->SetName( L"Name" );
    deviceEnabledTimeseriesObject1->SetMaxRetention( TimeSpan( -452142036613LL ) );
    deviceEnabledTimeseriesObject1->SetDevice( Guid( L"{69D0497B-894C-9769-E996-9132960B92DE}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *deviceEnabledTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto deviceEnabledTimeseriesObject2 = std::reinterpret_pointer_cast<DeviceEnabledTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = deviceEnabledTimeseriesObject2->IsEqualTo( *deviceEnabledTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarAutomaticSensitivityTimeControlTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarAutomaticSensitivityTimeControlTimeseriesObjectSerializationTest )
{
    auto radarAutomaticSensitivityTimeControlTimeseriesObject1 = std::make_shared<RadarAutomaticSensitivityTimeControlTimeseriesObject>( );
    radarAutomaticSensitivityTimeControlTimeseriesObject1->SetId( Guid( L"{B14B496D-C720-1CBB-38DD-E3048DD292B6}" ) );
    radarAutomaticSensitivityTimeControlTimeseriesObject1->SetRowVersion( 2070467396934257005LL );
    radarAutomaticSensitivityTimeControlTimeseriesObject1->SetCatalog( Guid( L"{B14B496D-C720-1CBB-38DD-E3048DD292B6}" ) );
    radarAutomaticSensitivityTimeControlTimeseriesObject1->SetName( L"Name" );
    radarAutomaticSensitivityTimeControlTimeseriesObject1->SetMaxRetention( TimeSpan( 260934257005LL ) );
    radarAutomaticSensitivityTimeControlTimeseriesObject1->SetRadar( Guid( L"{B14B496D-C720-1CBB-38DD-E3048DD292B6}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarAutomaticSensitivityTimeControlTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarAutomaticSensitivityTimeControlTimeseriesObject2 = std::reinterpret_pointer_cast<RadarAutomaticSensitivityTimeControlTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = radarAutomaticSensitivityTimeControlTimeseriesObject2->IsEqualTo( *radarAutomaticSensitivityTimeControlTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarBlankSector1TimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarBlankSector1TimeseriesObjectSerializationTest )
{
    auto radarBlankSector1TimeseriesObject1 = std::make_shared<RadarBlankSector1TimeseriesObject>( );
    radarBlankSector1TimeseriesObject1->SetId( Guid( L"{ED364257-A48A-54B4-2A2D-2551B76C42EA}" ) );
    radarBlankSector1TimeseriesObject1->SetRowVersion( 6103684311586062935LL );
    radarBlankSector1TimeseriesObject1->SetCatalog( Guid( L"{ED364257-A48A-54B4-2A2D-2551B76C42EA}" ) );
    radarBlankSector1TimeseriesObject1->SetName( L"Name" );
    radarBlankSector1TimeseriesObject1->SetMaxRetention( TimeSpan( 375586062935LL ) );
    radarBlankSector1TimeseriesObject1->SetRadar( Guid( L"{ED364257-A48A-54B4-2A2D-2551B76C42EA}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarBlankSector1TimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarBlankSector1TimeseriesObject2 = std::reinterpret_pointer_cast<RadarBlankSector1TimeseriesObject>( ReadDataFrom( source ) );
    bool equal = radarBlankSector1TimeseriesObject2->IsEqualTo( *radarBlankSector1TimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarBlankSector2TimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarBlankSector2TimeseriesObjectSerializationTest )
{
    auto radarBlankSector2TimeseriesObject1 = std::make_shared<RadarBlankSector2TimeseriesObject>( );
    radarBlankSector2TimeseriesObject1->SetId( Guid( L"{46A44C6B-B248-E63D-67BC-4D12622532D6}" ) );
    radarBlankSector2TimeseriesObject1->SetRowVersion( -1856131447914214293LL );
    radarBlankSector2TimeseriesObject1->SetCatalog( Guid( L"{46A44C6B-B248-E63D-67BC-4D12622532D6}" ) );
    radarBlankSector2TimeseriesObject1->SetName( L"Name" );
    radarBlankSector2TimeseriesObject1->SetMaxRetention( TimeSpan( -247914214293LL ) );
    radarBlankSector2TimeseriesObject1->SetRadar( Guid( L"{46A44C6B-B248-E63D-67BC-4D12622532D6}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarBlankSector2TimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarBlankSector2TimeseriesObject2 = std::reinterpret_pointer_cast<RadarBlankSector2TimeseriesObject>( ReadDataFrom( source ) );
    bool equal = radarBlankSector2TimeseriesObject2->IsEqualTo( *radarBlankSector2TimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarEnableAutomaticFrequencyControlTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarEnableAutomaticFrequencyControlTimeseriesObjectSerializationTest )
{
    auto radarEnableAutomaticFrequencyControlTimeseriesObject1 = std::make_shared<RadarEnableAutomaticFrequencyControlTimeseriesObject>( );
    radarEnableAutomaticFrequencyControlTimeseriesObject1->SetId( Guid( L"{9DB6213A-0CCE-84B7-21ED-3073B96D845C}" ) );
    radarEnableAutomaticFrequencyControlTimeseriesObject1->SetRowVersion( -8883617658416258758LL );
    radarEnableAutomaticFrequencyControlTimeseriesObject1->SetCatalog( Guid( L"{9DB6213A-0CCE-84B7-21ED-3073B96D845C}" ) );
    radarEnableAutomaticFrequencyControlTimeseriesObject1->SetName( L"Name" );
    radarEnableAutomaticFrequencyControlTimeseriesObject1->SetMaxRetention( TimeSpan( -762416258758LL ) );
    radarEnableAutomaticFrequencyControlTimeseriesObject1->SetRadar( Guid( L"{9DB6213A-0CCE-84B7-21ED-3073B96D845C}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarEnableAutomaticFrequencyControlTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarEnableAutomaticFrequencyControlTimeseriesObject2 = std::reinterpret_pointer_cast<RadarEnableAutomaticFrequencyControlTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = radarEnableAutomaticFrequencyControlTimeseriesObject2->IsEqualTo( *radarEnableAutomaticFrequencyControlTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarEnableFastTimeConstantTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarEnableFastTimeConstantTimeseriesObjectSerializationTest )
{
    auto radarEnableFastTimeConstantTimeseriesObject1 = std::make_shared<RadarEnableFastTimeConstantTimeseriesObject>( );
    radarEnableFastTimeConstantTimeseriesObject1->SetId( Guid( L"{18A7A806-EC65-5F1B-FAD8-37A618E51560}" ) );
    radarEnableFastTimeConstantTimeseriesObject1->SetRowVersion( 6853331176923834374LL );
    radarEnableFastTimeConstantTimeseriesObject1->SetCatalog( Guid( L"{18A7A806-EC65-5F1B-FAD8-37A618E51560}" ) );
    radarEnableFastTimeConstantTimeseriesObject1->SetName( L"Name" );
    radarEnableFastTimeConstantTimeseriesObject1->SetMaxRetention( TimeSpan( 232923834374LL ) );
    radarEnableFastTimeConstantTimeseriesObject1->SetRadar( Guid( L"{18A7A806-EC65-5F1B-FAD8-37A618E51560}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarEnableFastTimeConstantTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarEnableFastTimeConstantTimeseriesObject2 = std::reinterpret_pointer_cast<RadarEnableFastTimeConstantTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = radarEnableFastTimeConstantTimeseriesObject2->IsEqualTo( *radarEnableFastTimeConstantTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarEnableSensitivityTimeControlTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarEnableSensitivityTimeControlTimeseriesObjectSerializationTest )
{
    auto radarEnableSensitivityTimeControlTimeseriesObject1 = std::make_shared<RadarEnableSensitivityTimeControlTimeseriesObject>( );
    radarEnableSensitivityTimeControlTimeseriesObject1->SetId( Guid( L"{494844CA-D6F1-C20E-4370-6B8F92122253}" ) );
    radarEnableSensitivityTimeControlTimeseriesObject1->SetRowVersion( -4463393848872647478LL );
    radarEnableSensitivityTimeControlTimeseriesObject1->SetCatalog( Guid( L"{494844CA-D6F1-C20E-4370-6B8F92122253}" ) );
    radarEnableSensitivityTimeControlTimeseriesObject1->SetName( L"Name" );
    radarEnableSensitivityTimeControlTimeseriesObject1->SetMaxRetention( TimeSpan( -88872647478LL ) );
    radarEnableSensitivityTimeControlTimeseriesObject1->SetRadar( Guid( L"{494844CA-D6F1-C20E-4370-6B8F92122253}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarEnableSensitivityTimeControlTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarEnableSensitivityTimeControlTimeseriesObject2 = std::reinterpret_pointer_cast<RadarEnableSensitivityTimeControlTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = radarEnableSensitivityTimeControlTimeseriesObject2->IsEqualTo( *radarEnableSensitivityTimeControlTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarPowerOnTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarPowerOnTimeseriesObjectSerializationTest )
{
    auto radarPowerOnTimeseriesObject1 = std::make_shared<RadarPowerOnTimeseriesObject>( );
    radarPowerOnTimeseriesObject1->SetId( Guid( L"{4BD37D9F-BB15-752C-AE34-DDA8D2CBBEF9}" ) );
    radarPowerOnTimeseriesObject1->SetRowVersion( 8443329101553696159LL );
    radarPowerOnTimeseriesObject1->SetCatalog( Guid( L"{4BD37D9F-BB15-752C-AE34-DDA8D2CBBEF9}" ) );
    radarPowerOnTimeseriesObject1->SetName( L"Name" );
    radarPowerOnTimeseriesObject1->SetMaxRetention( TimeSpan( 557553696159LL ) );
    radarPowerOnTimeseriesObject1->SetRadar( Guid( L"{4BD37D9F-BB15-752C-AE34-DDA8D2CBBEF9}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarPowerOnTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarPowerOnTimeseriesObject2 = std::reinterpret_pointer_cast<RadarPowerOnTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = radarPowerOnTimeseriesObject2->IsEqualTo( *radarPowerOnTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarSaveSettingsTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarSaveSettingsTimeseriesObjectSerializationTest )
{
    auto radarSaveSettingsTimeseriesObject1 = std::make_shared<RadarSaveSettingsTimeseriesObject>( );
    radarSaveSettingsTimeseriesObject1->SetId( Guid( L"{CA0F64CF-2127-5D4E-BA72-84E453F026F3}" ) );
    radarSaveSettingsTimeseriesObject1->SetRowVersion( 6723347748488176847LL );
    radarSaveSettingsTimeseriesObject1->SetCatalog( Guid( L"{CA0F64CF-2127-5D4E-BA72-84E453F026F3}" ) );
    radarSaveSettingsTimeseriesObject1->SetName( L"Name" );
    radarSaveSettingsTimeseriesObject1->SetMaxRetention( TimeSpan( 420488176847LL ) );
    radarSaveSettingsTimeseriesObject1->SetRadar( Guid( L"{CA0F64CF-2127-5D4E-BA72-84E453F026F3}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarSaveSettingsTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarSaveSettingsTimeseriesObject2 = std::reinterpret_pointer_cast<RadarSaveSettingsTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = radarSaveSettingsTimeseriesObject2->IsEqualTo( *radarSaveSettingsTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarTrackingTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarTrackingTimeseriesObjectSerializationTest )
{
    auto radarTrackingTimeseriesObject1 = std::make_shared<RadarTrackingTimeseriesObject>( );
    radarTrackingTimeseriesObject1->SetId( Guid( L"{693D3626-5AC5-291C-9438-5AA396BC6C64}" ) );
    radarTrackingTimeseriesObject1->SetRowVersion( 2962342458823620134LL );
    radarTrackingTimeseriesObject1->SetCatalog( Guid( L"{693D3626-5AC5-291C-9438-5AA396BC6C64}" ) );
    radarTrackingTimeseriesObject1->SetName( L"Name" );
    radarTrackingTimeseriesObject1->SetMaxRetention( TimeSpan( 90823620134LL ) );
    radarTrackingTimeseriesObject1->SetRadar( Guid( L"{693D3626-5AC5-291C-9438-5AA396BC6C64}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarTrackingTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarTrackingTimeseriesObject2 = std::reinterpret_pointer_cast<RadarTrackingTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = radarTrackingTimeseriesObject2->IsEqualTo( *radarTrackingTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/MediaProxySessionEnabledTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( MediaProxySessionEnabledTimeseriesObjectSerializationTest )
{
    auto mediaProxySessionEnabledTimeseriesObject1 = std::make_shared<MediaProxySessionEnabledTimeseriesObject>( );
    mediaProxySessionEnabledTimeseriesObject1->SetId( Guid( L"{E0C3C0AA-BEA0-3AA5-5CA5-7D0507C30355}" ) );
    mediaProxySessionEnabledTimeseriesObject1->SetRowVersion( 4225993423532048554LL );
    mediaProxySessionEnabledTimeseriesObject1->SetCatalog( Guid( L"{E0C3C0AA-BEA0-3AA5-5CA5-7D0507C30355}" ) );
    mediaProxySessionEnabledTimeseriesObject1->SetName( L"Name" );
    mediaProxySessionEnabledTimeseriesObject1->SetMaxRetention( TimeSpan( 79532048554LL ) );
    mediaProxySessionEnabledTimeseriesObject1->SetProxySession( Guid( L"{E0C3C0AA-BEA0-3AA5-5CA5-7D0507C30355}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *mediaProxySessionEnabledTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto mediaProxySessionEnabledTimeseriesObject2 = std::reinterpret_pointer_cast<MediaProxySessionEnabledTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = mediaProxySessionEnabledTimeseriesObject2->IsEqualTo( *mediaProxySessionEnabledTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/MediaServiceEnabledTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( MediaServiceEnabledTimeseriesObjectSerializationTest )
{
    auto mediaServiceEnabledTimeseriesObject1 = std::make_shared<MediaServiceEnabledTimeseriesObject>( );
    mediaServiceEnabledTimeseriesObject1->SetId( Guid( L"{F813AAEC-3673-460A-6250-6CCE1FC85537}" ) );
    mediaServiceEnabledTimeseriesObject1->SetRowVersion( 5046906204133239532LL );
    mediaServiceEnabledTimeseriesObject1->SetCatalog( Guid( L"{F813AAEC-3673-460A-6250-6CCE1FC85537}" ) );
    mediaServiceEnabledTimeseriesObject1->SetName( L"Name" );
    mediaServiceEnabledTimeseriesObject1->SetMaxRetention( TimeSpan( 540133239532LL ) );
    mediaServiceEnabledTimeseriesObject1->SetService( Guid( L"{F813AAEC-3673-460A-6250-6CCE1FC85537}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *mediaServiceEnabledTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto mediaServiceEnabledTimeseriesObject2 = std::reinterpret_pointer_cast<MediaServiceEnabledTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = mediaServiceEnabledTimeseriesObject2->IsEqualTo( *mediaServiceEnabledTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ByteTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( ByteTimeseriesObjectSerializationTest )
{
    auto byteTimeseriesObject1 = std::make_shared<ByteTimeseriesObject>( );
    byteTimeseriesObject1->SetId( Guid( L"{B4BE0CF7-5AEF-38B0-1C0D-5AF72D7D30EF}" ) );
    byteTimeseriesObject1->SetRowVersion( 4084864847601077495LL );
    byteTimeseriesObject1->SetCatalog( Guid( L"{B4BE0CF7-5AEF-38B0-1C0D-5AF72D7D30EF}" ) );
    byteTimeseriesObject1->SetName( L"Name" );
    byteTimeseriesObject1->SetMaxRetention( TimeSpan( 719601077495LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *byteTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto byteTimeseriesObject2 = std::reinterpret_pointer_cast<ByteTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = byteTimeseriesObject2->IsEqualTo( *byteTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DateTimeTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( DateTimeTimeseriesObjectSerializationTest )
{
    auto dateTimeTimeseriesObject1 = std::make_shared<DateTimeTimeseriesObject>( );
    dateTimeTimeseriesObject1->SetId( Guid( L"{B7AFFEEC-9857-8EE3-71C7-19EAEDF57F37}" ) );
    dateTimeTimeseriesObject1->SetRowVersion( -8150503398099124500LL );
    dateTimeTimeseriesObject1->SetCatalog( Guid( L"{B7AFFEEC-9857-8EE3-71C7-19EAEDF57F37}" ) );
    dateTimeTimeseriesObject1->SetName( L"Name" );
    dateTimeTimeseriesObject1->SetMaxRetention( TimeSpan( -6099124500LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *dateTimeTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto dateTimeTimeseriesObject2 = std::reinterpret_pointer_cast<DateTimeTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = dateTimeTimeseriesObject2->IsEqualTo( *dateTimeTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DoubleTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( DoubleTimeseriesObjectSerializationTest )
{
    auto doubleTimeseriesObject1 = std::make_shared<DoubleTimeseriesObject>( );
    doubleTimeseriesObject1->SetId( Guid( L"{70027D82-38B0-3204-4C20-1C0D0E40BE41}" ) );
    doubleTimeseriesObject1->SetRowVersion( 3604067932247850370LL );
    doubleTimeseriesObject1->SetCatalog( Guid( L"{70027D82-38B0-3204-4C20-1C0D0E40BE41}" ) );
    doubleTimeseriesObject1->SetName( L"Name" );
    doubleTimeseriesObject1->SetMaxRetention( TimeSpan( 796247850370LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *doubleTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto doubleTimeseriesObject2 = std::reinterpret_pointer_cast<DoubleTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = doubleTimeseriesObject2->IsEqualTo( *doubleTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GNSSAltitudeTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( GNSSAltitudeTimeseriesObjectSerializationTest )
{
    auto gNSSAltitudeTimeseriesObject1 = std::make_shared<GNSSAltitudeTimeseriesObject>( );
    gNSSAltitudeTimeseriesObject1->SetId( Guid( L"{C78FE640-FB48-915B-89DA-DF12E3F16702}" ) );
    gNSSAltitudeTimeseriesObject1->SetRowVersion( -7972502425325017536LL );
    gNSSAltitudeTimeseriesObject1->SetCatalog( Guid( L"{C78FE640-FB48-915B-89DA-DF12E3F16702}" ) );
    gNSSAltitudeTimeseriesObject1->SetName( L"Name" );
    gNSSAltitudeTimeseriesObject1->SetMaxRetention( TimeSpan( -313325017536LL ) );
    gNSSAltitudeTimeseriesObject1->SetGNSSDevice( Guid( L"{C78FE640-FB48-915B-89DA-DF12E3F16702}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gNSSAltitudeTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gNSSAltitudeTimeseriesObject2 = std::reinterpret_pointer_cast<GNSSAltitudeTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = gNSSAltitudeTimeseriesObject2->IsEqualTo( *gNSSAltitudeTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GNSSLatitudeTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( GNSSLatitudeTimeseriesObjectSerializationTest )
{
    auto gNSSLatitudeTimeseriesObject1 = std::make_shared<GNSSLatitudeTimeseriesObject>( );
    gNSSLatitudeTimeseriesObject1->SetId( Guid( L"{2B60BC5C-431D-E742-E742-C2B8D4063D3A}" ) );
    gNSSLatitudeTimeseriesObject1->SetRowVersion( -1782788709924422564LL );
    gNSSLatitudeTimeseriesObject1->SetCatalog( Guid( L"{2B60BC5C-431D-E742-E742-C2B8D4063D3A}" ) );
    gNSSLatitudeTimeseriesObject1->SetName( L"Name" );
    gNSSLatitudeTimeseriesObject1->SetMaxRetention( TimeSpan( -741924422564LL ) );
    gNSSLatitudeTimeseriesObject1->SetGNSSDevice( Guid( L"{2B60BC5C-431D-E742-E742-C2B8D4063D3A}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gNSSLatitudeTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gNSSLatitudeTimeseriesObject2 = std::reinterpret_pointer_cast<GNSSLatitudeTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = gNSSLatitudeTimeseriesObject2->IsEqualTo( *gNSSLatitudeTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GNSSLongitudeTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( GNSSLongitudeTimeseriesObjectSerializationTest )
{
    auto gNSSLongitudeTimeseriesObject1 = std::make_shared<GNSSLongitudeTimeseriesObject>( );
    gNSSLongitudeTimeseriesObject1->SetId( Guid( L"{A7B79429-D0D4-80DD-01BB-0B2BE5ED2994}" ) );
    gNSSLongitudeTimeseriesObject1->SetRowVersion( -9160936455236250583LL );
    gNSSLongitudeTimeseriesObject1->SetCatalog( Guid( L"{A7B79429-D0D4-80DD-01BB-0B2BE5ED2994}" ) );
    gNSSLongitudeTimeseriesObject1->SetName( L"Name" );
    gNSSLongitudeTimeseriesObject1->SetMaxRetention( TimeSpan( -615236250583LL ) );
    gNSSLongitudeTimeseriesObject1->SetGNSSDevice( Guid( L"{A7B79429-D0D4-80DD-01BB-0B2BE5ED2994}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gNSSLongitudeTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gNSSLongitudeTimeseriesObject2 = std::reinterpret_pointer_cast<GNSSLongitudeTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = gNSSLongitudeTimeseriesObject2->IsEqualTo( *gNSSLongitudeTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GyroCourseTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( GyroCourseTimeseriesObjectSerializationTest )
{
    auto gyroCourseTimeseriesObject1 = std::make_shared<GyroCourseTimeseriesObject>( );
    gyroCourseTimeseriesObject1->SetId( Guid( L"{99A051A1-D6FF-D1D3-8BCB-6BFF99058A85}" ) );
    gyroCourseTimeseriesObject1->SetRowVersion( -3327079306414239327LL );
    gyroCourseTimeseriesObject1->SetCatalog( Guid( L"{99A051A1-D6FF-D1D3-8BCB-6BFF99058A85}" ) );
    gyroCourseTimeseriesObject1->SetName( L"Name" );
    gyroCourseTimeseriesObject1->SetMaxRetention( TimeSpan( -202414239327LL ) );
    gyroCourseTimeseriesObject1->SetGyroDevice( Guid( L"{99A051A1-D6FF-D1D3-8BCB-6BFF99058A85}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gyroCourseTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gyroCourseTimeseriesObject2 = std::reinterpret_pointer_cast<GyroCourseTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = gyroCourseTimeseriesObject2->IsEqualTo( *gyroCourseTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GyroHeadingMagneticNorthTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( GyroHeadingMagneticNorthTimeseriesObjectSerializationTest )
{
    auto gyroHeadingMagneticNorthTimeseriesObject1 = std::make_shared<GyroHeadingMagneticNorthTimeseriesObject>( );
    gyroHeadingMagneticNorthTimeseriesObject1->SetId( Guid( L"{0BCA07EA-06B3-C122-8344-60CDD053E057}" ) );
    gyroHeadingMagneticNorthTimeseriesObject1->SetRowVersion( -4530050909114595350LL );
    gyroHeadingMagneticNorthTimeseriesObject1->SetCatalog( Guid( L"{0BCA07EA-06B3-C122-8344-60CDD053E057}" ) );
    gyroHeadingMagneticNorthTimeseriesObject1->SetName( L"Name" );
    gyroHeadingMagneticNorthTimeseriesObject1->SetMaxRetention( TimeSpan( -413114595350LL ) );
    gyroHeadingMagneticNorthTimeseriesObject1->SetGyroDevice( Guid( L"{0BCA07EA-06B3-C122-8344-60CDD053E057}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gyroHeadingMagneticNorthTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gyroHeadingMagneticNorthTimeseriesObject2 = std::reinterpret_pointer_cast<GyroHeadingMagneticNorthTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = gyroHeadingMagneticNorthTimeseriesObject2->IsEqualTo( *gyroHeadingMagneticNorthTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GyroHeadingTrueNorthTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( GyroHeadingTrueNorthTimeseriesObjectSerializationTest )
{
    auto gyroHeadingTrueNorthTimeseriesObject1 = std::make_shared<GyroHeadingTrueNorthTimeseriesObject>( );
    gyroHeadingTrueNorthTimeseriesObject1->SetId( Guid( L"{C6DE373C-1957-8742-E142-98EA637BEC3C}" ) );
    gyroHeadingTrueNorthTimeseriesObject1->SetRowVersion( -8700363665337075908LL );
    gyroHeadingTrueNorthTimeseriesObject1->SetCatalog( Guid( L"{C6DE373C-1957-8742-E142-98EA637BEC3C}" ) );
    gyroHeadingTrueNorthTimeseriesObject1->SetName( L"Name" );
    gyroHeadingTrueNorthTimeseriesObject1->SetMaxRetention( TimeSpan( -305337075908LL ) );
    gyroHeadingTrueNorthTimeseriesObject1->SetGyroDevice( Guid( L"{C6DE373C-1957-8742-E142-98EA637BEC3C}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gyroHeadingTrueNorthTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gyroHeadingTrueNorthTimeseriesObject2 = std::reinterpret_pointer_cast<GyroHeadingTrueNorthTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = gyroHeadingTrueNorthTimeseriesObject2->IsEqualTo( *gyroHeadingTrueNorthTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GyroPitchTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( GyroPitchTimeseriesObjectSerializationTest )
{
    auto gyroPitchTimeseriesObject1 = std::make_shared<GyroPitchTimeseriesObject>( );
    gyroPitchTimeseriesObject1->SetId( Guid( L"{D29F7EFA-EF76-E390-C709-F76E4BF97E5F}" ) );
    gyroPitchTimeseriesObject1->SetRowVersion( -2048874536834728198LL );
    gyroPitchTimeseriesObject1->SetCatalog( Guid( L"{D29F7EFA-EF76-E390-C709-F76E4BF97E5F}" ) );
    gyroPitchTimeseriesObject1->SetName( L"Name" );
    gyroPitchTimeseriesObject1->SetMaxRetention( TimeSpan( -488834728198LL ) );
    gyroPitchTimeseriesObject1->SetGyroDevice( Guid( L"{D29F7EFA-EF76-E390-C709-F76E4BF97E5F}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gyroPitchTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gyroPitchTimeseriesObject2 = std::reinterpret_pointer_cast<GyroPitchTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = gyroPitchTimeseriesObject2->IsEqualTo( *gyroPitchTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GyroRateOfTurnTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( GyroRateOfTurnTimeseriesObjectSerializationTest )
{
    auto gyroRateOfTurnTimeseriesObject1 = std::make_shared<GyroRateOfTurnTimeseriesObject>( );
    gyroRateOfTurnTimeseriesObject1->SetId( Guid( L"{9F54111F-5947-76E2-6E47-9AE2F92A88F8}" ) );
    gyroRateOfTurnTimeseriesObject1->SetRowVersion( 8566507605362741535LL );
    gyroRateOfTurnTimeseriesObject1->SetCatalog( Guid( L"{9F54111F-5947-76E2-6E47-9AE2F92A88F8}" ) );
    gyroRateOfTurnTimeseriesObject1->SetName( L"Name" );
    gyroRateOfTurnTimeseriesObject1->SetMaxRetention( TimeSpan( 309362741535LL ) );
    gyroRateOfTurnTimeseriesObject1->SetGyroDevice( Guid( L"{9F54111F-5947-76E2-6E47-9AE2F92A88F8}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gyroRateOfTurnTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gyroRateOfTurnTimeseriesObject2 = std::reinterpret_pointer_cast<GyroRateOfTurnTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = gyroRateOfTurnTimeseriesObject2->IsEqualTo( *gyroRateOfTurnTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GyroRollTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( GyroRollTimeseriesObjectSerializationTest )
{
    auto gyroRollTimeseriesObject1 = std::make_shared<GyroRollTimeseriesObject>( );
    gyroRollTimeseriesObject1->SetId( Guid( L"{B0312AEF-C209-72B9-4E9D-43900D8C54F7}" ) );
    gyroRollTimeseriesObject1->SetRowVersion( 8266851937881762543LL );
    gyroRollTimeseriesObject1->SetCatalog( Guid( L"{B0312AEF-C209-72B9-4E9D-43900D8C54F7}" ) );
    gyroRollTimeseriesObject1->SetName( L"Name" );
    gyroRollTimeseriesObject1->SetMaxRetention( TimeSpan( 577881762543LL ) );
    gyroRollTimeseriesObject1->SetGyroDevice( Guid( L"{B0312AEF-C209-72B9-4E9D-43900D8C54F7}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gyroRollTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gyroRollTimeseriesObject2 = std::reinterpret_pointer_cast<GyroRollTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = gyroRollTimeseriesObject2->IsEqualTo( *gyroRollTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GyroSpeedTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( GyroSpeedTimeseriesObjectSerializationTest )
{
    auto gyroSpeedTimeseriesObject1 = std::make_shared<GyroSpeedTimeseriesObject>( );
    gyroSpeedTimeseriesObject1->SetId( Guid( L"{5F8EC90F-03A1-EC2C-3734-C085FA7193F0}" ) );
    gyroSpeedTimeseriesObject1->SetRowVersion( -1428762990155478769LL );
    gyroSpeedTimeseriesObject1->SetCatalog( Guid( L"{5F8EC90F-03A1-EC2C-3734-C085FA7193F0}" ) );
    gyroSpeedTimeseriesObject1->SetName( L"Name" );
    gyroSpeedTimeseriesObject1->SetMaxRetention( TimeSpan( -750155478769LL ) );
    gyroSpeedTimeseriesObject1->SetGyroDevice( Guid( L"{5F8EC90F-03A1-EC2C-3734-C085FA7193F0}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gyroSpeedTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gyroSpeedTimeseriesObject2 = std::reinterpret_pointer_cast<GyroSpeedTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = gyroSpeedTimeseriesObject2->IsEqualTo( *gyroSpeedTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarLatitudeTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarLatitudeTimeseriesObjectSerializationTest )
{
    auto radarLatitudeTimeseriesObject1 = std::make_shared<RadarLatitudeTimeseriesObject>( );
    radarLatitudeTimeseriesObject1->SetId( Guid( L"{E0E5A360-ADB7-DDEA-BB57-B5ED07A7C506}" ) );
    radarLatitudeTimeseriesObject1->SetRowVersion( -2455959641513417888LL );
    radarLatitudeTimeseriesObject1->SetCatalog( Guid( L"{E0E5A360-ADB7-DDEA-BB57-B5ED07A7C506}" ) );
    radarLatitudeTimeseriesObject1->SetName( L"Name" );
    radarLatitudeTimeseriesObject1->SetMaxRetention( TimeSpan( -761513417888LL ) );
    radarLatitudeTimeseriesObject1->SetRadar( Guid( L"{E0E5A360-ADB7-DDEA-BB57-B5ED07A7C506}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarLatitudeTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarLatitudeTimeseriesObject2 = std::reinterpret_pointer_cast<RadarLatitudeTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = radarLatitudeTimeseriesObject2->IsEqualTo( *radarLatitudeTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarLongitudeTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarLongitudeTimeseriesObjectSerializationTest )
{
    auto radarLongitudeTimeseriesObject1 = std::make_shared<RadarLongitudeTimeseriesObject>( );
    radarLongitudeTimeseriesObject1->SetId( Guid( L"{914F8147-10D7-7E00-7E00-08EB89F281E2}" ) );
    radarLongitudeTimeseriesObject1->SetRowVersion( 9079275366820839751LL );
    radarLongitudeTimeseriesObject1->SetCatalog( Guid( L"{914F8147-10D7-7E00-7E00-08EB89F281E2}" ) );
    radarLongitudeTimeseriesObject1->SetName( L"Name" );
    radarLongitudeTimeseriesObject1->SetMaxRetention( TimeSpan( 486820839751LL ) );
    radarLongitudeTimeseriesObject1->SetRadar( Guid( L"{914F8147-10D7-7E00-7E00-08EB89F281E2}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarLongitudeTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarLongitudeTimeseriesObject2 = std::reinterpret_pointer_cast<RadarLongitudeTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = radarLongitudeTimeseriesObject2->IsEqualTo( *radarLongitudeTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadomeDewPointTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadomeDewPointTimeseriesObjectSerializationTest )
{
    auto radomeDewPointTimeseriesObject1 = std::make_shared<RadomeDewPointTimeseriesObject>( );
    radomeDewPointTimeseriesObject1->SetId( Guid( L"{85244187-C511-65D6-A66B-A388A12482E1}" ) );
    radomeDewPointTimeseriesObject1->SetRowVersion( 7338269321885663623LL );
    radomeDewPointTimeseriesObject1->SetCatalog( Guid( L"{85244187-C511-65D6-A66B-A388A12482E1}" ) );
    radomeDewPointTimeseriesObject1->SetName( L"Name" );
    radomeDewPointTimeseriesObject1->SetMaxRetention( TimeSpan( 233885663623LL ) );
    radomeDewPointTimeseriesObject1->SetRadome( Guid( L"{85244187-C511-65D6-A66B-A388A12482E1}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radomeDewPointTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radomeDewPointTimeseriesObject2 = std::reinterpret_pointer_cast<RadomeDewPointTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = radomeDewPointTimeseriesObject2->IsEqualTo( *radomeDewPointTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadomePressureTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadomePressureTimeseriesObjectSerializationTest )
{
    auto radomePressureTimeseriesObject1 = std::make_shared<RadomePressureTimeseriesObject>( );
    radomePressureTimeseriesObject1->SetId( Guid( L"{58626DEF-4551-0274-402E-A28A1A46B6F7}" ) );
    radomePressureTimeseriesObject1->SetRowVersion( 176842501051805167LL );
    radomePressureTimeseriesObject1->SetCatalog( Guid( L"{58626DEF-4551-0274-402E-A28A1A46B6F7}" ) );
    radomePressureTimeseriesObject1->SetName( L"Name" );
    radomePressureTimeseriesObject1->SetMaxRetention( TimeSpan( 709051805167LL ) );
    radomePressureTimeseriesObject1->SetRadome( Guid( L"{58626DEF-4551-0274-402E-A28A1A46B6F7}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radomePressureTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radomePressureTimeseriesObject2 = std::reinterpret_pointer_cast<RadomePressureTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = radomePressureTimeseriesObject2->IsEqualTo( *radomePressureTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadomeTemperatureTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadomeTemperatureTimeseriesObjectSerializationTest )
{
    auto radomeTemperatureTimeseriesObject1 = std::make_shared<RadomeTemperatureTimeseriesObject>( );
    radomeTemperatureTimeseriesObject1->SetId( Guid( L"{A5335D1F-62CF-F3BA-CF5D-46F3A5CCBAF8}" ) );
    radomeTemperatureTimeseriesObject1->SetRowVersion( -884285732855522017LL );
    radomeTemperatureTimeseriesObject1->SetCatalog( Guid( L"{A5335D1F-62CF-F3BA-CF5D-46F3A5CCBAF8}" ) );
    radomeTemperatureTimeseriesObject1->SetName( L"Name" );
    radomeTemperatureTimeseriesObject1->SetMaxRetention( TimeSpan( -740855522017LL ) );
    radomeTemperatureTimeseriesObject1->SetRadome( Guid( L"{A5335D1F-62CF-F3BA-CF5D-46F3A5CCBAF8}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radomeTemperatureTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radomeTemperatureTimeseriesObject2 = std::reinterpret_pointer_cast<RadomeTemperatureTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = radomeTemperatureTimeseriesObject2->IsEqualTo( *radomeTemperatureTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/VesselDraughtTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( VesselDraughtTimeseriesObjectSerializationTest )
{
    auto vesselDraughtTimeseriesObject1 = std::make_shared<VesselDraughtTimeseriesObject>( );
    vesselDraughtTimeseriesObject1->SetId( Guid( L"{7059B959-548D-760C-6E30-2AB10E9A9D9A}" ) );
    vesselDraughtTimeseriesObject1->SetRowVersion( 8506266762648074585LL );
    vesselDraughtTimeseriesObject1->SetCatalog( Guid( L"{7059B959-548D-760C-6E30-2AB10E9A9D9A}" ) );
    vesselDraughtTimeseriesObject1->SetName( L"Name" );
    vesselDraughtTimeseriesObject1->SetMaxRetention( TimeSpan( 138648074585LL ) );
    vesselDraughtTimeseriesObject1->SetVessel( Guid( L"{7059B959-548D-760C-6E30-2AB10E9A9D9A}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *vesselDraughtTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto vesselDraughtTimeseriesObject2 = std::reinterpret_pointer_cast<VesselDraughtTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = vesselDraughtTimeseriesObject2->IsEqualTo( *vesselDraughtTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ViewLatitudeTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( ViewLatitudeTimeseriesObjectSerializationTest )
{
    auto viewLatitudeTimeseriesObject1 = std::make_shared<ViewLatitudeTimeseriesObject>( );
    viewLatitudeTimeseriesObject1->SetId( Guid( L"{9B05B46B-C262-634F-C6F2-4346D9A02DD6}" ) );
    viewLatitudeTimeseriesObject1->SetRowVersion( 7156152061678433387LL );
    viewLatitudeTimeseriesObject1->SetCatalog( Guid( L"{9B05B46B-C262-634F-C6F2-4346D9A02DD6}" ) );
    viewLatitudeTimeseriesObject1->SetName( L"Name" );
    viewLatitudeTimeseriesObject1->SetMaxRetention( TimeSpan( 349678433387LL ) );
    viewLatitudeTimeseriesObject1->SetView( Guid( L"{9B05B46B-C262-634F-C6F2-4346D9A02DD6}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *viewLatitudeTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto viewLatitudeTimeseriesObject2 = std::reinterpret_pointer_cast<ViewLatitudeTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = viewLatitudeTimeseriesObject2->IsEqualTo( *viewLatitudeTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ViewLongitudeTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( ViewLongitudeTimeseriesObjectSerializationTest )
{
    auto viewLongitudeTimeseriesObject1 = std::make_shared<ViewLongitudeTimeseriesObject>( );
    viewLongitudeTimeseriesObject1->SetId( Guid( L"{4FBBABE3-886C-8E91-7189-1136F2DDD5C7}" ) );
    viewLongitudeTimeseriesObject1->SetRowVersion( -8173601849925194781LL );
    viewLongitudeTimeseriesObject1->SetCatalog( Guid( L"{4FBBABE3-886C-8E91-7189-1136F2DDD5C7}" ) );
    viewLongitudeTimeseriesObject1->SetName( L"Name" );
    viewLongitudeTimeseriesObject1->SetMaxRetention( TimeSpan( -281925194781LL ) );
    viewLongitudeTimeseriesObject1->SetView( Guid( L"{4FBBABE3-886C-8E91-7189-1136F2DDD5C7}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *viewLongitudeTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto viewLongitudeTimeseriesObject2 = std::reinterpret_pointer_cast<ViewLongitudeTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = viewLongitudeTimeseriesObject2->IsEqualTo( *viewLongitudeTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ViewZoomLevelTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( ViewZoomLevelTimeseriesObjectSerializationTest )
{
    auto viewZoomLevelTimeseriesObject1 = std::make_shared<ViewZoomLevelTimeseriesObject>( );
    viewZoomLevelTimeseriesObject1->SetId( Guid( L"{5F2894FB-26D8-7F35-FEAC-641BFA1429DF}" ) );
    viewZoomLevelTimeseriesObject1->SetRowVersion( 9166275327333799163LL );
    viewZoomLevelTimeseriesObject1->SetCatalog( Guid( L"{5F2894FB-26D8-7F35-FEAC-641BFA1429DF}" ) );
    viewZoomLevelTimeseriesObject1->SetName( L"Name" );
    viewZoomLevelTimeseriesObject1->SetMaxRetention( TimeSpan( 831333799163LL ) );
    viewZoomLevelTimeseriesObject1->SetView( Guid( L"{5F2894FB-26D8-7F35-FEAC-641BFA1429DF}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *viewZoomLevelTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto viewZoomLevelTimeseriesObject2 = std::reinterpret_pointer_cast<ViewZoomLevelTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = viewZoomLevelTimeseriesObject2->IsEqualTo( *viewZoomLevelTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/WeatherStationAbsoluteHumidityTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( WeatherStationAbsoluteHumidityTimeseriesObjectSerializationTest )
{
    auto weatherStationAbsoluteHumidityTimeseriesObject1 = std::make_shared<WeatherStationAbsoluteHumidityTimeseriesObject>( );
    weatherStationAbsoluteHumidityTimeseriesObject1->SetId( Guid( L"{9985DBA8-995F-6C2E-3674-99FA99A1DB15}" ) );
    weatherStationAbsoluteHumidityTimeseriesObject1->SetRowVersion( 7795336640901536680LL );
    weatherStationAbsoluteHumidityTimeseriesObject1->SetCatalog( Guid( L"{9985DBA8-995F-6C2E-3674-99FA99A1DB15}" ) );
    weatherStationAbsoluteHumidityTimeseriesObject1->SetName( L"Name" );
    weatherStationAbsoluteHumidityTimeseriesObject1->SetMaxRetention( TimeSpan( 320901536680LL ) );
    weatherStationAbsoluteHumidityTimeseriesObject1->SetWeatherStation( Guid( L"{9985DBA8-995F-6C2E-3674-99FA99A1DB15}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *weatherStationAbsoluteHumidityTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto weatherStationAbsoluteHumidityTimeseriesObject2 = std::reinterpret_pointer_cast<WeatherStationAbsoluteHumidityTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = weatherStationAbsoluteHumidityTimeseriesObject2->IsEqualTo( *weatherStationAbsoluteHumidityTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/WeatherStationAirTemperatureTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( WeatherStationAirTemperatureTimeseriesObjectSerializationTest )
{
    auto weatherStationAirTemperatureTimeseriesObject1 = std::make_shared<WeatherStationAirTemperatureTimeseriesObject>( );
    weatherStationAirTemperatureTimeseriesObject1->SetId( Guid( L"{4CE773F5-DB2A-D088-0B11-DB5432E7CEAF}" ) );
    weatherStationAirTemperatureTimeseriesObject1->SetRowVersion( -3420242942262545419LL );
    weatherStationAirTemperatureTimeseriesObject1->SetCatalog( Guid( L"{4CE773F5-DB2A-D088-0B11-DB5432E7CEAF}" ) );
    weatherStationAirTemperatureTimeseriesObject1->SetName( L"Name" );
    weatherStationAirTemperatureTimeseriesObject1->SetMaxRetention( TimeSpan( -446262545419LL ) );
    weatherStationAirTemperatureTimeseriesObject1->SetWeatherStation( Guid( L"{4CE773F5-DB2A-D088-0B11-DB5432E7CEAF}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *weatherStationAirTemperatureTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto weatherStationAirTemperatureTimeseriesObject2 = std::reinterpret_pointer_cast<WeatherStationAirTemperatureTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = weatherStationAirTemperatureTimeseriesObject2->IsEqualTo( *weatherStationAirTemperatureTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/WeatherStationBarometricPressureTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( WeatherStationBarometricPressureTimeseriesObjectSerializationTest )
{
    auto weatherStationBarometricPressureTimeseriesObject1 = std::make_shared<WeatherStationBarometricPressureTimeseriesObject>( );
    weatherStationBarometricPressureTimeseriesObject1->SetId( Guid( L"{1602DEDA-FCE4-14BE-287D-3F2768407B5B}" ) );
    weatherStationBarometricPressureTimeseriesObject1->SetRowVersion( 1494910182885613274LL );
    weatherStationBarometricPressureTimeseriesObject1->SetCatalog( Guid( L"{1602DEDA-FCE4-14BE-287D-3F2768407B5B}" ) );
    weatherStationBarometricPressureTimeseriesObject1->SetName( L"Name" );
    weatherStationBarometricPressureTimeseriesObject1->SetMaxRetention( TimeSpan( 102885613274LL ) );
    weatherStationBarometricPressureTimeseriesObject1->SetWeatherStation( Guid( L"{1602DEDA-FCE4-14BE-287D-3F2768407B5B}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *weatherStationBarometricPressureTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto weatherStationBarometricPressureTimeseriesObject2 = std::reinterpret_pointer_cast<WeatherStationBarometricPressureTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = weatherStationBarometricPressureTimeseriesObject2->IsEqualTo( *weatherStationBarometricPressureTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/WeatherStationDewPointTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( WeatherStationDewPointTimeseriesObjectSerializationTest )
{
    auto weatherStationDewPointTimeseriesObject1 = std::make_shared<WeatherStationDewPointTimeseriesObject>( );
    weatherStationDewPointTimeseriesObject1->SetId( Guid( L"{A045152B-2A17-8AB9-519D-54E805A2A8D4}" ) );
    weatherStationDewPointTimeseriesObject1->SetRowVersion( -8450676944822528725LL );
    weatherStationDewPointTimeseriesObject1->SetCatalog( Guid( L"{A045152B-2A17-8AB9-519D-54E805A2A8D4}" ) );
    weatherStationDewPointTimeseriesObject1->SetName( L"Name" );
    weatherStationDewPointTimeseriesObject1->SetMaxRetention( TimeSpan( -80822528725LL ) );
    weatherStationDewPointTimeseriesObject1->SetWeatherStation( Guid( L"{A045152B-2A17-8AB9-519D-54E805A2A8D4}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *weatherStationDewPointTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto weatherStationDewPointTimeseriesObject2 = std::reinterpret_pointer_cast<WeatherStationDewPointTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = weatherStationDewPointTimeseriesObject2->IsEqualTo( *weatherStationDewPointTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/WeatherStationRelativeHumidityTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( WeatherStationRelativeHumidityTimeseriesObjectSerializationTest )
{
    auto weatherStationRelativeHumidityTimeseriesObject1 = std::make_shared<WeatherStationRelativeHumidityTimeseriesObject>( );
    weatherStationRelativeHumidityTimeseriesObject1->SetId( Guid( L"{8AC9E291-9E5A-E5FF-A7FF-795A51934789}" ) );
    weatherStationRelativeHumidityTimeseriesObject1->SetRowVersion( -1873604808250105199LL );
    weatherStationRelativeHumidityTimeseriesObject1->SetCatalog( Guid( L"{8AC9E291-9E5A-E5FF-A7FF-795A51934789}" ) );
    weatherStationRelativeHumidityTimeseriesObject1->SetName( L"Name" );
    weatherStationRelativeHumidityTimeseriesObject1->SetMaxRetention( TimeSpan( -72250105199LL ) );
    weatherStationRelativeHumidityTimeseriesObject1->SetWeatherStation( Guid( L"{8AC9E291-9E5A-E5FF-A7FF-795A51934789}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *weatherStationRelativeHumidityTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto weatherStationRelativeHumidityTimeseriesObject2 = std::reinterpret_pointer_cast<WeatherStationRelativeHumidityTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = weatherStationRelativeHumidityTimeseriesObject2->IsEqualTo( *weatherStationRelativeHumidityTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/WeatherStationWaterTemperatureTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( WeatherStationWaterTemperatureTimeseriesObjectSerializationTest )
{
    auto weatherStationWaterTemperatureTimeseriesObject1 = std::make_shared<WeatherStationWaterTemperatureTimeseriesObject>( );
    weatherStationWaterTemperatureTimeseriesObject1->SetId( Guid( L"{DC68964A-59AF-AACA-5553-9AF53B166952}" ) );
    weatherStationWaterTemperatureTimeseriesObject1->SetRowVersion( -6139996530114259382LL );
    weatherStationWaterTemperatureTimeseriesObject1->SetCatalog( Guid( L"{DC68964A-59AF-AACA-5553-9AF53B166952}" ) );
    weatherStationWaterTemperatureTimeseriesObject1->SetName( L"Name" );
    weatherStationWaterTemperatureTimeseriesObject1->SetMaxRetention( TimeSpan( -402114259382LL ) );
    weatherStationWaterTemperatureTimeseriesObject1->SetWeatherStation( Guid( L"{DC68964A-59AF-AACA-5553-9AF53B166952}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *weatherStationWaterTemperatureTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto weatherStationWaterTemperatureTimeseriesObject2 = std::reinterpret_pointer_cast<WeatherStationWaterTemperatureTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = weatherStationWaterTemperatureTimeseriesObject2->IsEqualTo( *weatherStationWaterTemperatureTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/WeatherStationWindDirectionTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( WeatherStationWindDirectionTimeseriesObjectSerializationTest )
{
    auto weatherStationWindDirectionTimeseriesObject1 = std::make_shared<WeatherStationWindDirectionTimeseriesObject>( );
    weatherStationWindDirectionTimeseriesObject1->SetId( Guid( L"{3D5AC399-0BC8-5701-EA80-D013BC5AC399}" ) );
    weatherStationWindDirectionTimeseriesObject1->SetRowVersion( 6269305110927164313LL );
    weatherStationWindDirectionTimeseriesObject1->SetCatalog( Guid( L"{3D5AC399-0BC8-5701-EA80-D013BC5AC399}" ) );
    weatherStationWindDirectionTimeseriesObject1->SetName( L"Name" );
    weatherStationWindDirectionTimeseriesObject1->SetMaxRetention( TimeSpan( 150927164313LL ) );
    weatherStationWindDirectionTimeseriesObject1->SetWeatherStation( Guid( L"{3D5AC399-0BC8-5701-EA80-D013BC5AC399}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *weatherStationWindDirectionTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto weatherStationWindDirectionTimeseriesObject2 = std::reinterpret_pointer_cast<WeatherStationWindDirectionTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = weatherStationWindDirectionTimeseriesObject2->IsEqualTo( *weatherStationWindDirectionTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/WeatherStationWindSpeedTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( WeatherStationWindSpeedTimeseriesObjectSerializationTest )
{
    auto weatherStationWindSpeedTimeseriesObject1 = std::make_shared<WeatherStationWindSpeedTimeseriesObject>( );
    weatherStationWindSpeedTimeseriesObject1->SetId( Guid( L"{9AA40834-C20B-D135-8BAC-43D05925102C}" ) );
    weatherStationWindSpeedTimeseriesObject1->SetRowVersion( -3371575390922078156LL );
    weatherStationWindSpeedTimeseriesObject1->SetCatalog( Guid( L"{9AA40834-C20B-D135-8BAC-43D05925102C}" ) );
    weatherStationWindSpeedTimeseriesObject1->SetName( L"Name" );
    weatherStationWindSpeedTimeseriesObject1->SetMaxRetention( TimeSpan( -286922078156LL ) );
    weatherStationWindSpeedTimeseriesObject1->SetWeatherStation( Guid( L"{9AA40834-C20B-D135-8BAC-43D05925102C}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *weatherStationWindSpeedTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto weatherStationWindSpeedTimeseriesObject2 = std::reinterpret_pointer_cast<WeatherStationWindSpeedTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = weatherStationWindSpeedTimeseriesObject2->IsEqualTo( *weatherStationWindSpeedTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GeoPosition2DTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( GeoPosition2DTimeseriesObjectSerializationTest )
{
    auto geoPosition2DTimeseriesObject1 = std::make_shared<GeoPosition2DTimeseriesObject>( );
    geoPosition2DTimeseriesObject1->SetId( Guid( L"{B940E1F3-65AE-B2C1-4D83-A6759D0287CF}" ) );
    geoPosition2DTimeseriesObject1->SetRowVersion( -5566055863346470413LL );
    geoPosition2DTimeseriesObject1->SetCatalog( Guid( L"{B940E1F3-65AE-B2C1-4D83-A6759D0287CF}" ) );
    geoPosition2DTimeseriesObject1->SetName( L"Name" );
    geoPosition2DTimeseriesObject1->SetMaxRetention( TimeSpan( -247346470413LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *geoPosition2DTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto geoPosition2DTimeseriesObject2 = std::reinterpret_pointer_cast<GeoPosition2DTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = geoPosition2DTimeseriesObject2->IsEqualTo( *geoPosition2DTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisAidToNavigationPositionTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( AisAidToNavigationPositionTimeseriesObjectSerializationTest )
{
    auto aisAidToNavigationPositionTimeseriesObject1 = std::make_shared<AisAidToNavigationPositionTimeseriesObject>( );
    aisAidToNavigationPositionTimeseriesObject1->SetId( Guid( L"{BC96FB00-29D3-F52A-AF54-94CB3D69DF00}" ) );
    aisAidToNavigationPositionTimeseriesObject1->SetRowVersion( -780765596016510208LL );
    aisAidToNavigationPositionTimeseriesObject1->SetCatalog( Guid( L"{BC96FB00-29D3-F52A-AF54-94CB3D69DF00}" ) );
    aisAidToNavigationPositionTimeseriesObject1->SetName( L"Name" );
    aisAidToNavigationPositionTimeseriesObject1->SetMaxRetention( TimeSpan( -764016510208LL ) );
    aisAidToNavigationPositionTimeseriesObject1->SetAidToNavigation( Guid( L"{BC96FB00-29D3-F52A-AF54-94CB3D69DF00}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisAidToNavigationPositionTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisAidToNavigationPositionTimeseriesObject2 = std::reinterpret_pointer_cast<AisAidToNavigationPositionTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = aisAidToNavigationPositionTimeseriesObject2->IsEqualTo( *aisAidToNavigationPositionTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GeoPosition3DTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( GeoPosition3DTimeseriesObjectSerializationTest )
{
    auto geoPosition3DTimeseriesObject1 = std::make_shared<GeoPosition3DTimeseriesObject>( );
    geoPosition3DTimeseriesObject1->SetId( Guid( L"{F956554B-2BC0-1D77-B8EE-D4039F6AAAD2}" ) );
    geoPosition3DTimeseriesObject1->SetRowVersion( 2123213857145378123LL );
    geoPosition3DTimeseriesObject1->SetCatalog( Guid( L"{F956554B-2BC0-1D77-B8EE-D4039F6AAAD2}" ) );
    geoPosition3DTimeseriesObject1->SetName( L"Name" );
    geoPosition3DTimeseriesObject1->SetMaxRetention( TimeSpan( 385145378123LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *geoPosition3DTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto geoPosition3DTimeseriesObject2 = std::reinterpret_pointer_cast<GeoPosition3DTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = geoPosition3DTimeseriesObject2->IsEqualTo( *geoPosition3DTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GuidTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( GuidTimeseriesObjectSerializationTest )
{
    auto guidTimeseriesObject1 = std::make_shared<GuidTimeseriesObject>( );
    guidTimeseriesObject1->SetId( Guid( L"{975C0471-455B-A5A9-A595-A2DAE93A208E}" ) );
    guidTimeseriesObject1->SetRowVersion( -6509595526703610767LL );
    guidTimeseriesObject1->SetCatalog( Guid( L"{975C0471-455B-A5A9-A595-A2DAE93A208E}" ) );
    guidTimeseriesObject1->SetName( L"Name" );
    guidTimeseriesObject1->SetMaxRetention( TimeSpan( -70703610767LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *guidTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto guidTimeseriesObject2 = std::reinterpret_pointer_cast<GuidTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = guidTimeseriesObject2->IsEqualTo( *guidTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int16TimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( Int16TimeseriesObjectSerializationTest )
{
    auto int16TimeseriesObject1 = std::make_shared<Int16TimeseriesObject>( );
    int16TimeseriesObject1->SetId( Guid( L"{6CBDC146-1F86-ACB9-359D-F86136BD8362}" ) );
    int16TimeseriesObject1->SetRowVersion( -6000730366284021434LL );
    int16TimeseriesObject1->SetCatalog( Guid( L"{6CBDC146-1F86-ACB9-359D-F86136BD8362}" ) );
    int16TimeseriesObject1->SetName( L"Name" );
    int16TimeseriesObject1->SetMaxRetention( TimeSpan( -670284021434LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int16TimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int16TimeseriesObject2 = std::reinterpret_pointer_cast<Int16TimeseriesObject>( ReadDataFrom( source ) );
    bool equal = int16TimeseriesObject2->IsEqualTo( *int16TimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int32TimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( Int32TimeseriesObjectSerializationTest )
{
    auto int32TimeseriesObject1 = std::make_shared<Int32TimeseriesObject>( );
    int32TimeseriesObject1->SetId( Guid( L"{BF8A1AA1-9B78-29F8-941F-D91EFD515885}" ) );
    int32TimeseriesObject1->SetRowVersion( 3024338092691167905LL );
    int32TimeseriesObject1->SetCatalog( Guid( L"{BF8A1AA1-9B78-29F8-941F-D91EFD515885}" ) );
    int32TimeseriesObject1->SetName( L"Name" );
    int32TimeseriesObject1->SetMaxRetention( TimeSpan( 268691167905LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int32TimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int32TimeseriesObject2 = std::reinterpret_pointer_cast<Int32TimeseriesObject>( ReadDataFrom( source ) );
    bool equal = int32TimeseriesObject2->IsEqualTo( *int32TimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarAzimuthOffsetTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarAzimuthOffsetTimeseriesObjectSerializationTest )
{
    auto radarAzimuthOffsetTimeseriesObject1 = std::make_shared<RadarAzimuthOffsetTimeseriesObject>( );
    radarAzimuthOffsetTimeseriesObject1->SetId( Guid( L"{5E4E1D3D-1C4C-47B5-E2AD-38327A72B8BC}" ) );
    radarAzimuthOffsetTimeseriesObject1->SetRowVersion( 5167067261802782013LL );
    radarAzimuthOffsetTimeseriesObject1->SetCatalog( Guid( L"{5E4E1D3D-1C4C-47B5-E2AD-38327A72B8BC}" ) );
    radarAzimuthOffsetTimeseriesObject1->SetName( L"Name" );
    radarAzimuthOffsetTimeseriesObject1->SetMaxRetention( TimeSpan( 797802782013LL ) );
    radarAzimuthOffsetTimeseriesObject1->SetRadar( Guid( L"{5E4E1D3D-1C4C-47B5-E2AD-38327A72B8BC}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarAzimuthOffsetTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarAzimuthOffsetTimeseriesObject2 = std::reinterpret_pointer_cast<RadarAzimuthOffsetTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = radarAzimuthOffsetTimeseriesObject2->IsEqualTo( *radarAzimuthOffsetTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarFastTimeConstantLevelTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarFastTimeConstantLevelTimeseriesObjectSerializationTest )
{
    auto radarFastTimeConstantLevelTimeseriesObject1 = std::make_shared<RadarFastTimeConstantLevelTimeseriesObject>( );
    radarFastTimeConstantLevelTimeseriesObject1->SetId( Guid( L"{366E9EC4-3487-7CD6-3E6B-2CE16C767923}" ) );
    radarFastTimeConstantLevelTimeseriesObject1->SetRowVersion( 8995435061057593028LL );
    radarFastTimeConstantLevelTimeseriesObject1->SetCatalog( Guid( L"{366E9EC4-3487-7CD6-3E6B-2CE16C767923}" ) );
    radarFastTimeConstantLevelTimeseriesObject1->SetName( L"Name" );
    radarFastTimeConstantLevelTimeseriesObject1->SetMaxRetention( TimeSpan( 149057593028LL ) );
    radarFastTimeConstantLevelTimeseriesObject1->SetRadar( Guid( L"{366E9EC4-3487-7CD6-3E6B-2CE16C767923}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarFastTimeConstantLevelTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarFastTimeConstantLevelTimeseriesObject2 = std::reinterpret_pointer_cast<RadarFastTimeConstantLevelTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = radarFastTimeConstantLevelTimeseriesObject2->IsEqualTo( *radarFastTimeConstantLevelTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarFastTimeConstantModeTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarFastTimeConstantModeTimeseriesObjectSerializationTest )
{
    auto radarFastTimeConstantModeTimeseriesObject1 = std::make_shared<RadarFastTimeConstantModeTimeseriesObject>( );
    radarFastTimeConstantModeTimeseriesObject1->SetId( Guid( L"{AEF3B2BC-F0DB-016C-8036-0FDB75CF4D3D}" ) );
    radarFastTimeConstantModeTimeseriesObject1->SetRowVersion( 102721717846389436LL );
    radarFastTimeConstantModeTimeseriesObject1->SetCatalog( Guid( L"{AEF3B2BC-F0DB-016C-8036-0FDB75CF4D3D}" ) );
    radarFastTimeConstantModeTimeseriesObject1->SetName( L"Name" );
    radarFastTimeConstantModeTimeseriesObject1->SetMaxRetention( TimeSpan( 757846389436LL ) );
    radarFastTimeConstantModeTimeseriesObject1->SetRadar( Guid( L"{AEF3B2BC-F0DB-016C-8036-0FDB75CF4D3D}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarFastTimeConstantModeTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarFastTimeConstantModeTimeseriesObject2 = std::reinterpret_pointer_cast<RadarFastTimeConstantModeTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = radarFastTimeConstantModeTimeseriesObject2->IsEqualTo( *radarFastTimeConstantModeTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarPulseTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarPulseTimeseriesObjectSerializationTest )
{
    auto radarPulseTimeseriesObject1 = std::make_shared<RadarPulseTimeseriesObject>( );
    radarPulseTimeseriesObject1->SetId( Guid( L"{1E2910A2-C988-2024-0424-931178940845}" ) );
    radarPulseTimeseriesObject1->SetRowVersion( 2316197694834020514LL );
    radarPulseTimeseriesObject1->SetCatalog( Guid( L"{1E2910A2-C988-2024-0424-931178940845}" ) );
    radarPulseTimeseriesObject1->SetName( L"Name" );
    radarPulseTimeseriesObject1->SetMaxRetention( TimeSpan( 318834020514LL ) );
    radarPulseTimeseriesObject1->SetRadar( Guid( L"{1E2910A2-C988-2024-0424-931178940845}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarPulseTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarPulseTimeseriesObject2 = std::reinterpret_pointer_cast<RadarPulseTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = radarPulseTimeseriesObject2->IsEqualTo( *radarPulseTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarSector1EndTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarSector1EndTimeseriesObjectSerializationTest )
{
    auto radarSector1EndTimeseriesObject1 = std::make_shared<RadarSector1EndTimeseriesObject>( );
    radarSector1EndTimeseriesObject1->SetId( Guid( L"{42B1F5DD-BB0D-310E-8C70-DDB0428DAFBB}" ) );
    radarSector1EndTimeseriesObject1->SetRowVersion( 3534968423160346077LL );
    radarSector1EndTimeseriesObject1->SetCatalog( Guid( L"{42B1F5DD-BB0D-310E-8C70-DDB0428DAFBB}" ) );
    radarSector1EndTimeseriesObject1->SetName( L"Name" );
    radarSector1EndTimeseriesObject1->SetMaxRetention( TimeSpan( 551160346077LL ) );
    radarSector1EndTimeseriesObject1->SetRadar( Guid( L"{42B1F5DD-BB0D-310E-8C70-DDB0428DAFBB}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarSector1EndTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarSector1EndTimeseriesObject2 = std::reinterpret_pointer_cast<RadarSector1EndTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = radarSector1EndTimeseriesObject2->IsEqualTo( *radarSector1EndTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarSector1StartTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarSector1StartTimeseriesObjectSerializationTest )
{
    auto radarSector1StartTimeseriesObject1 = std::make_shared<RadarSector1StartTimeseriesObject>( );
    radarSector1StartTimeseriesObject1->SetId( Guid( L"{FB7089D3-826F-D790-EB09-41F6DF0E91CB}" ) );
    radarSector1StartTimeseriesObject1->SetRowVersion( -2913685541437273645LL );
    radarSector1StartTimeseriesObject1->SetCatalog( Guid( L"{FB7089D3-826F-D790-EB09-41F6DF0E91CB}" ) );
    radarSector1StartTimeseriesObject1->SetName( L"Name" );
    radarSector1StartTimeseriesObject1->SetMaxRetention( TimeSpan( -197437273645LL ) );
    radarSector1StartTimeseriesObject1->SetRadar( Guid( L"{FB7089D3-826F-D790-EB09-41F6DF0E91CB}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarSector1StartTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarSector1StartTimeseriesObject2 = std::reinterpret_pointer_cast<RadarSector1StartTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = radarSector1StartTimeseriesObject2->IsEqualTo( *radarSector1StartTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarSector2EndTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarSector2EndTimeseriesObjectSerializationTest )
{
    auto radarSector2EndTimeseriesObject1 = std::make_shared<RadarSector2EndTimeseriesObject>( );
    radarSector2EndTimeseriesObject1->SetId( Guid( L"{469274EE-3468-A02F-05F4-2C1662492E77}" ) );
    radarSector2EndTimeseriesObject1->SetRowVersion( -6904242081270434578LL );
    radarSector2EndTimeseriesObject1->SetCatalog( Guid( L"{469274EE-3468-A02F-05F4-2C1662492E77}" ) );
    radarSector2EndTimeseriesObject1->SetName( L"Name" );
    radarSector2EndTimeseriesObject1->SetMaxRetention( TimeSpan( -801270434578LL ) );
    radarSector2EndTimeseriesObject1->SetRadar( Guid( L"{469274EE-3468-A02F-05F4-2C1662492E77}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarSector2EndTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarSector2EndTimeseriesObject2 = std::reinterpret_pointer_cast<RadarSector2EndTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = radarSector2EndTimeseriesObject2->IsEqualTo( *radarSector2EndTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarSector2StartTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarSector2StartTimeseriesObjectSerializationTest )
{
    auto radarSector2StartTimeseriesObject1 = std::make_shared<RadarSector2StartTimeseriesObject>( );
    radarSector2StartTimeseriesObject1->SetId( Guid( L"{AA794E3C-C797-9FEF-F9F7-E3E9559E723C}" ) );
    radarSector2StartTimeseriesObject1->SetRowVersion( -6922094648031097284LL );
    radarSector2StartTimeseriesObject1->SetCatalog( Guid( L"{AA794E3C-C797-9FEF-F9F7-E3E9559E723C}" ) );
    radarSector2StartTimeseriesObject1->SetName( L"Name" );
    radarSector2StartTimeseriesObject1->SetMaxRetention( TimeSpan( -536031097284LL ) );
    radarSector2StartTimeseriesObject1->SetRadar( Guid( L"{AA794E3C-C797-9FEF-F9F7-E3E9559E723C}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarSector2StartTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarSector2StartTimeseriesObject2 = std::reinterpret_pointer_cast<RadarSector2StartTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = radarSector2StartTimeseriesObject2->IsEqualTo( *radarSector2StartTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarSensitivityTimeControlLevelTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarSensitivityTimeControlLevelTimeseriesObjectSerializationTest )
{
    auto radarSensitivityTimeControlLevelTimeseriesObject1 = std::make_shared<RadarSensitivityTimeControlLevelTimeseriesObject>( );
    radarSensitivityTimeControlLevelTimeseriesObject1->SetId( Guid( L"{99907E01-44A9-8916-9168-229599097E80}" ) );
    radarSensitivityTimeControlLevelTimeseriesObject1->SetRowVersion( -8568585745809244671LL );
    radarSensitivityTimeControlLevelTimeseriesObject1->SetCatalog( Guid( L"{99907E01-44A9-8916-9168-229599097E80}" ) );
    radarSensitivityTimeControlLevelTimeseriesObject1->SetName( L"Name" );
    radarSensitivityTimeControlLevelTimeseriesObject1->SetMaxRetention( TimeSpan( -529809244671LL ) );
    radarSensitivityTimeControlLevelTimeseriesObject1->SetRadar( Guid( L"{99907E01-44A9-8916-9168-229599097E80}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarSensitivityTimeControlLevelTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarSensitivityTimeControlLevelTimeseriesObject2 = std::reinterpret_pointer_cast<RadarSensitivityTimeControlLevelTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = radarSensitivityTimeControlLevelTimeseriesObject2->IsEqualTo( *radarSensitivityTimeControlLevelTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarTuningTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadarTuningTimeseriesObjectSerializationTest )
{
    auto radarTuningTimeseriesObject1 = std::make_shared<RadarTuningTimeseriesObject>( );
    radarTuningTimeseriesObject1->SetId( Guid( L"{2BC44D8C-8D89-F863-1FC6-B191D423B231}" ) );
    radarTuningTimeseriesObject1->SetRowVersion( -548439109324747380LL );
    radarTuningTimeseriesObject1->SetCatalog( Guid( L"{2BC44D8C-8D89-F863-1FC6-B191D423B231}" ) );
    radarTuningTimeseriesObject1->SetName( L"Name" );
    radarTuningTimeseriesObject1->SetMaxRetention( TimeSpan( -421324747380LL ) );
    radarTuningTimeseriesObject1->SetRadar( Guid( L"{2BC44D8C-8D89-F863-1FC6-B191D423B231}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarTuningTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarTuningTimeseriesObject2 = std::reinterpret_pointer_cast<RadarTuningTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = radarTuningTimeseriesObject2->IsEqualTo( *radarTuningTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/VesselPersonsOnBoardTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( VesselPersonsOnBoardTimeseriesObjectSerializationTest )
{
    auto vesselPersonsOnBoardTimeseriesObject1 = std::make_shared<VesselPersonsOnBoardTimeseriesObject>( );
    vesselPersonsOnBoardTimeseriesObject1->SetId( Guid( L"{FEAAF2E4-72D5-E12D-87B4-4EAB7F554F27}" ) );
    vesselPersonsOnBoardTimeseriesObject1->SetRowVersion( -2220992777797569820LL );
    vesselPersonsOnBoardTimeseriesObject1->SetCatalog( Guid( L"{FEAAF2E4-72D5-E12D-87B4-4EAB7F554F27}" ) );
    vesselPersonsOnBoardTimeseriesObject1->SetName( L"Name" );
    vesselPersonsOnBoardTimeseriesObject1->SetMaxRetention( TimeSpan( -425797569820LL ) );
    vesselPersonsOnBoardTimeseriesObject1->SetVessel( Guid( L"{FEAAF2E4-72D5-E12D-87B4-4EAB7F554F27}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *vesselPersonsOnBoardTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto vesselPersonsOnBoardTimeseriesObject2 = std::reinterpret_pointer_cast<VesselPersonsOnBoardTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = vesselPersonsOnBoardTimeseriesObject2->IsEqualTo( *vesselPersonsOnBoardTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int64TimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( Int64TimeseriesObjectSerializationTest )
{
    auto int64TimeseriesObject1 = std::make_shared<Int64TimeseriesObject>( );
    int64TimeseriesObject1->SetId( Guid( L"{031600FF-2473-658D-A6B1-24CEC06800FF}" ) );
    int64TimeseriesObject1->SetRowVersion( 7317545045938536703LL );
    int64TimeseriesObject1->SetCatalog( Guid( L"{031600FF-2473-658D-A6B1-24CEC06800FF}" ) );
    int64TimeseriesObject1->SetName( L"Name" );
    int64TimeseriesObject1->SetMaxRetention( TimeSpan( 725938536703LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int64TimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int64TimeseriesObject2 = std::reinterpret_pointer_cast<Int64TimeseriesObject>( ReadDataFrom( source ) );
    bool equal = int64TimeseriesObject2->IsEqualTo( *int64TimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Position2DTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( Position2DTimeseriesObjectSerializationTest )
{
    auto position2DTimeseriesObject1 = std::make_shared<Position2DTimeseriesObject>( );
    position2DTimeseriesObject1->SetId( Guid( L"{A244E20D-8E28-CF70-F30E-7114452247B0}" ) );
    position2DTimeseriesObject1->SetRowVersion( -3499140605294616051LL );
    position2DTimeseriesObject1->SetCatalog( Guid( L"{A244E20D-8E28-CF70-F30E-7114452247B0}" ) );
    position2DTimeseriesObject1->SetName( L"Name" );
    position2DTimeseriesObject1->SetMaxRetention( TimeSpan( -221294616051LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *position2DTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto position2DTimeseriesObject2 = std::reinterpret_pointer_cast<Position2DTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = position2DTimeseriesObject2->IsEqualTo( *position2DTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Position3DTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( Position3DTimeseriesObjectSerializationTest )
{
    auto position3DTimeseriesObject1 = std::make_shared<Position3DTimeseriesObject>( );
    position3DTimeseriesObject1->SetId( Guid( L"{13DB07D3-1553-8C8C-3131-A8CAC8DBE0CB}" ) );
    position3DTimeseriesObject1->SetRowVersion( -8319250965100558381LL );
    position3DTimeseriesObject1->SetCatalog( Guid( L"{13DB07D3-1553-8C8C-3131-A8CAC8DBE0CB}" ) );
    position3DTimeseriesObject1->SetName( L"Name" );
    position3DTimeseriesObject1->SetMaxRetention( TimeSpan( -597100558381LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *position3DTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto position3DTimeseriesObject2 = std::reinterpret_pointer_cast<Position3DTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = position3DTimeseriesObject2->IsEqualTo( *position3DTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ReferenceTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( ReferenceTimeseriesObjectSerializationTest )
{
    auto referenceTimeseriesObject1 = std::make_shared<ReferenceTimeseriesObject>( );
    referenceTimeseriesObject1->SetId( Guid( L"{2A04F6AE-BC6A-A651-658A-3D5654206F75}" ) );
    referenceTimeseriesObject1->SetRowVersion( -6462176826142427474LL );
    referenceTimeseriesObject1->SetCatalog( Guid( L"{2A04F6AE-BC6A-A651-658A-3D5654206F75}" ) );
    referenceTimeseriesObject1->SetName( L"Name" );
    referenceTimeseriesObject1->SetMaxRetention( TimeSpan( -282142427474LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *referenceTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto referenceTimeseriesObject2 = std::reinterpret_pointer_cast<ReferenceTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = referenceTimeseriesObject2->IsEqualTo( *referenceTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SByteTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( SByteTimeseriesObjectSerializationTest )
{
    auto sByteTimeseriesObject1 = std::make_shared<SByteTimeseriesObject>( );
    sByteTimeseriesObject1->SetId( Guid( L"{1B8C2A12-5A67-DC90-3B09-5AE6D8315448}" ) );
    sByteTimeseriesObject1->SetRowVersion( -2553441589828769262LL );
    sByteTimeseriesObject1->SetCatalog( Guid( L"{1B8C2A12-5A67-DC90-3B09-5AE6D8315448}" ) );
    sByteTimeseriesObject1->SetName( L"Name" );
    sByteTimeseriesObject1->SetMaxRetention( TimeSpan( -181828769262LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *sByteTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto sByteTimeseriesObject2 = std::reinterpret_pointer_cast<SByteTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = sByteTimeseriesObject2->IsEqualTo( *sByteTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SingleTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( SingleTimeseriesObjectSerializationTest )
{
    auto singleTimeseriesObject1 = std::make_shared<SingleTimeseriesObject>( );
    singleTimeseriesObject1->SetId( Guid( L"{92306DBD-F6D7-CC44-3322-6FEB490CB6BD}" ) );
    singleTimeseriesObject1->SetRowVersion( -3727583185824879171LL );
    singleTimeseriesObject1->SetCatalog( Guid( L"{92306DBD-F6D7-CC44-3322-6FEB490CB6BD}" ) );
    singleTimeseriesObject1->SetName( L"Name" );
    singleTimeseriesObject1->SetMaxRetention( TimeSpan( -337824879171LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *singleTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto singleTimeseriesObject2 = std::reinterpret_pointer_cast<SingleTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = singleTimeseriesObject2->IsEqualTo( *singleTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/StringTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( StringTimeseriesObjectSerializationTest )
{
    auto stringTimeseriesObject1 = std::make_shared<StringTimeseriesObject>( );
    stringTimeseriesObject1->SetId( Guid( L"{543F4243-6A6F-6CC7-36E3-56F62AFC42C2}" ) );
    stringTimeseriesObject1->SetRowVersion( 7838350702848983619LL );
    stringTimeseriesObject1->SetCatalog( Guid( L"{543F4243-6A6F-6CC7-36E3-56F62AFC42C2}" ) );
    stringTimeseriesObject1->SetName( L"Name" );
    stringTimeseriesObject1->SetMaxRetention( TimeSpan( 142848983619LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *stringTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto stringTimeseriesObject2 = std::reinterpret_pointer_cast<StringTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = stringTimeseriesObject2->IsEqualTo( *stringTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TimeSpanTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( TimeSpanTimeseriesObjectSerializationTest )
{
    auto timeSpanTimeseriesObject1 = std::make_shared<TimeSpanTimeseriesObject>( );
    timeSpanTimeseriesObject1->SetId( Guid( L"{10BB8F38-4616-F79B-EFD9-626808DDF11C}" ) );
    timeSpanTimeseriesObject1->SetRowVersion( -604812664367247560LL );
    timeSpanTimeseriesObject1->SetCatalog( Guid( L"{10BB8F38-4616-F79B-EFD9-626808DDF11C}" ) );
    timeSpanTimeseriesObject1->SetName( L"Name" );
    timeSpanTimeseriesObject1->SetMaxRetention( TimeSpan( -568367247560LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *timeSpanTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto timeSpanTimeseriesObject2 = std::reinterpret_pointer_cast<TimeSpanTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = timeSpanTimeseriesObject2->IsEqualTo( *timeSpanTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt16TimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( UInt16TimeseriesObjectSerializationTest )
{
    auto uInt16TimeseriesObject1 = std::make_shared<UInt16TimeseriesObject>( );
    uInt16TimeseriesObject1->SetId( Guid( L"{C3004051-5156-9488-2911-8A6AC300028A}" ) );
    uInt16TimeseriesObject1->SetRowVersion( -7743850126182956975LL );
    uInt16TimeseriesObject1->SetCatalog( Guid( L"{C3004051-5156-9488-2911-8A6AC300028A}" ) );
    uInt16TimeseriesObject1->SetName( L"Name" );
    uInt16TimeseriesObject1->SetMaxRetention( TimeSpan( -430182956975LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt16TimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt16TimeseriesObject2 = std::reinterpret_pointer_cast<UInt16TimeseriesObject>( ReadDataFrom( source ) );
    bool equal = uInt16TimeseriesObject2->IsEqualTo( *uInt16TimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt32TimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( UInt32TimeseriesObjectSerializationTest )
{
    auto uInt32TimeseriesObject1 = std::make_shared<UInt32TimeseriesObject>( );
    uInt32TimeseriesObject1->SetId( Guid( L"{1E4F9B7F-3DF1-27F5-E4AF-BC8F78F2D9FE}" ) );
    uInt32TimeseriesObject1->SetRowVersion( 2879275642578246527LL );
    uInt32TimeseriesObject1->SetCatalog( Guid( L"{1E4F9B7F-3DF1-27F5-E4AF-BC8F78F2D9FE}" ) );
    uInt32TimeseriesObject1->SetName( L"Name" );
    uInt32TimeseriesObject1->SetMaxRetention( TimeSpan( 826578246527LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt32TimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt32TimeseriesObject2 = std::reinterpret_pointer_cast<UInt32TimeseriesObject>( ReadDataFrom( source ) );
    bool equal = uInt32TimeseriesObject2->IsEqualTo( *uInt32TimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadomeStatusTimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( RadomeStatusTimeseriesObjectSerializationTest )
{
    auto radomeStatusTimeseriesObject1 = std::make_shared<RadomeStatusTimeseriesObject>( );
    radomeStatusTimeseriesObject1->SetId( Guid( L"{D21766E9-B3DE-8353-C1CA-CD7B4BE86697}" ) );
    radomeStatusTimeseriesObject1->SetRowVersion( -8983639062085146903LL );
    radomeStatusTimeseriesObject1->SetCatalog( Guid( L"{D21766E9-B3DE-8353-C1CA-CD7B4BE86697}" ) );
    radomeStatusTimeseriesObject1->SetName( L"Name" );
    radomeStatusTimeseriesObject1->SetMaxRetention( TimeSpan( -342085146903LL ) );
    radomeStatusTimeseriesObject1->SetRadome( Guid( L"{D21766E9-B3DE-8353-C1CA-CD7B4BE86697}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radomeStatusTimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radomeStatusTimeseriesObject2 = std::reinterpret_pointer_cast<RadomeStatusTimeseriesObject>( ReadDataFrom( source ) );
    bool equal = radomeStatusTimeseriesObject2->IsEqualTo( *radomeStatusTimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt64TimeseriesObjectSerializationTest
BOOST_AUTO_TEST_CASE( UInt64TimeseriesObjectSerializationTest )
{
    auto uInt64TimeseriesObject1 = std::make_shared<UInt64TimeseriesObject>( );
    uInt64TimeseriesObject1->SetId( Guid( L"{EE6B112D-3F61-9C80-3901-FC8677D688B4}" ) );
    uInt64TimeseriesObject1->SetRowVersion( -7169660916929457875LL );
    uInt64TimeseriesObject1->SetCatalog( Guid( L"{EE6B112D-3F61-9C80-3901-FC8677D688B4}" ) );
    uInt64TimeseriesObject1->SetName( L"Name" );
    uInt64TimeseriesObject1->SetMaxRetention( TimeSpan( -564929457875LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt64TimeseriesObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt64TimeseriesObject2 = std::reinterpret_pointer_cast<UInt64TimeseriesObject>( ReadDataFrom( source ) );
    bool equal = uInt64TimeseriesObject2->IsEqualTo( *uInt64TimeseriesObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TimeseriesCatalogObjectSerializationTest
BOOST_AUTO_TEST_CASE( TimeseriesCatalogObjectSerializationTest )
{
    auto timeseriesCatalogObject1 = std::make_shared<TimeseriesCatalogObject>( );
    timeseriesCatalogObject1->SetId( Guid( L"{BD1CA5BF-744B-CF8B-F3D1-2ED2BD38A5FD}" ) );
    timeseriesCatalogObject1->SetRowVersion( -3491569217451547201LL );
    timeseriesCatalogObject1->SetCatalog( Guid( L"{BD1CA5BF-744B-CF8B-F3D1-2ED2BD38A5FD}" ) );
    timeseriesCatalogObject1->SetName( L"Name" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *timeseriesCatalogObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto timeseriesCatalogObject2 = std::reinterpret_pointer_cast<TimeseriesCatalogObject>( ReadDataFrom( source ) );
    bool equal = timeseriesCatalogObject2->IsEqualTo( *timeseriesCatalogObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TimeseriesInfoObjectSerializationTest
BOOST_AUTO_TEST_CASE( TimeseriesInfoObjectSerializationTest )
{
    auto timeseriesInfoObject1 = std::make_shared<TimeseriesInfoObject>( );
    timeseriesInfoObject1->SetId( Guid( L"{7A785D97-FDEA-3E83-7CC1-BF575E1EBAE9}" ) );
    timeseriesInfoObject1->SetRowVersion( 4504723235819511191LL );
    timeseriesInfoObject1->SetFirstTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    timeseriesInfoObject1->SetLastTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    timeseriesInfoObject1->SetCount( 4504723235819511191LL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *timeseriesInfoObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto timeseriesInfoObject2 = std::reinterpret_pointer_cast<TimeseriesInfoObject>( ReadDataFrom( source ) );
    bool equal = timeseriesInfoObject2->IsEqualTo( *timeseriesInfoObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TimeSpanTimeseriesValueObjectSerializationTest
BOOST_AUTO_TEST_CASE( TimeSpanTimeseriesValueObjectSerializationTest )
{
    auto timeSpanTimeseriesValueObject1 = std::make_shared<TimeSpanTimeseriesValueObject>( );
    timeSpanTimeseriesValueObject1->SetId( Guid( L"{B9BB7A7B-A746-EDFF-B7FF-E5629DDD5EDE}" ) );
    timeSpanTimeseriesValueObject1->SetRowVersion( -1297134245453792645LL );
    timeSpanTimeseriesValueObject1->SetTimeseries( Guid( L"{B9BB7A7B-A746-EDFF-B7FF-E5629DDD5EDE}" ) );
    timeSpanTimeseriesValueObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    timeSpanTimeseriesValueObject1->SetValue( TimeSpan( -677453792645LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *timeSpanTimeseriesValueObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto timeSpanTimeseriesValueObject2 = std::reinterpret_pointer_cast<TimeSpanTimeseriesValueObject>( ReadDataFrom( source ) );
    bool equal = timeSpanTimeseriesValueObject2->IsEqualTo( *timeSpanTimeseriesValueObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TrackableItemTrackLinkObjectSerializationTest
BOOST_AUTO_TEST_CASE( TrackableItemTrackLinkObjectSerializationTest )
{
    auto trackableItemTrackLinkObject1 = std::make_shared<TrackableItemTrackLinkObject>( );
    trackableItemTrackLinkObject1->SetId( Guid( L"{008FB1C3-B963-E78F-E7F1-9DC600F18DC3}" ) );
    trackableItemTrackLinkObject1->SetRowVersion( -1760985094416256573LL );
    trackableItemTrackLinkObject1->SetItem( Guid( L"{008FB1C3-B963-E78F-E7F1-9DC600F18DC3}" ) );
    trackableItemTrackLinkObject1->SetTrack( Guid( L"{008FB1C3-B963-E78F-E7F1-9DC600F18DC3}" ) );
    trackableItemTrackLinkObject1->SetStart( DateTime( 1, 1, 1, 22, 23, 35 ) );
    trackableItemTrackLinkObject1->SetEnd( DateTime( 1, 1, 1, 22, 23, 35 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *trackableItemTrackLinkObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto trackableItemTrackLinkObject2 = std::reinterpret_pointer_cast<TrackableItemTrackLinkObject>( ReadDataFrom( source ) );
    bool equal = trackableItemTrackLinkObject2->IsEqualTo( *trackableItemTrackLinkObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TrackObjectSerializationTest
BOOST_AUTO_TEST_CASE( TrackObjectSerializationTest )
{
    auto trackObject1 = std::make_shared<TrackObject>( );
    trackObject1->SetId( Guid( L"{2BF4613E-94F3-88C0-1103-29CFD42F867C}" ) );
    trackObject1->SetRowVersion( -8592704316887506626LL );
    trackObject1->SetTracker( Guid( L"{2BF4613E-94F3-88C0-1103-29CFD42F867C}" ) );
    trackObject1->SetTrackNumber( -8592704316887506626LL );
    trackObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *trackObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto trackObject2 = std::reinterpret_pointer_cast<TrackObject>( ReadDataFrom( source ) );
    bool equal = trackObject2->IsEqualTo( *trackObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Track3DObjectSerializationTest
BOOST_AUTO_TEST_CASE( Track3DObjectSerializationTest )
{
    auto track3DObject1 = std::make_shared<Track3DObject>( );
    track3DObject1->SetId( Guid( L"{FD0A3793-C049-E93F-97FC-0392BF50ECC9}" ) );
    track3DObject1->SetRowVersion( -1639380315329120365LL );
    track3DObject1->SetTracker( Guid( L"{FD0A3793-C049-E93F-97FC-0392BF50ECC9}" ) );
    track3DObject1->SetTrackNumber( -1639380315329120365LL );
    track3DObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *track3DObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto track3DObject2 = std::reinterpret_pointer_cast<Track3DObject>( ReadDataFrom( source ) );
    bool equal = track3DObject2->IsEqualTo( *track3DObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TrackerFilterParametersObjectSerializationTest
BOOST_AUTO_TEST_CASE( TrackerFilterParametersObjectSerializationTest )
{
    auto trackerFilterParametersObject1 = std::make_shared<TrackerFilterParametersObject>( );
    trackerFilterParametersObject1->SetId( Guid( L"{488067B9-69E4-0154-802A-96271201E69D}" ) );
    trackerFilterParametersObject1->SetRowVersion( 95817921271457721LL );
    trackerFilterParametersObject1->SetTracker( Guid( L"{488067B9-69E4-0154-802A-96271201E69D}" ) );
    trackerFilterParametersObject1->SetName( L"Name" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *trackerFilterParametersObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto trackerFilterParametersObject2 = std::reinterpret_pointer_cast<TrackerFilterParametersObject>( ReadDataFrom( source ) );
    bool equal = trackerFilterParametersObject2->IsEqualTo( *trackerFilterParametersObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TrackerFilterParametersConfigurationObjectSerializationTest
BOOST_AUTO_TEST_CASE( TrackerFilterParametersConfigurationObjectSerializationTest )
{
    auto trackerFilterParametersConfigurationObject1 = std::make_shared<TrackerFilterParametersConfigurationObject>( );
    trackerFilterParametersConfigurationObject1->SetId( Guid( L"{060FC360-326B-7108-8E10-4CD660F0C306}" ) );
    trackerFilterParametersConfigurationObject1->SetRowVersion( 8144815361344127840LL );
    trackerFilterParametersConfigurationObject1->SetParameters( Guid( L"{060FC360-326B-7108-8E10-4CD660F0C306}" ) );
    trackerFilterParametersConfigurationObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    trackerFilterParametersConfigurationObject1->SetUseNaivePredictor( false );
    trackerFilterParametersConfigurationObject1->SetNumberOfPoints( 101696352L );
    trackerFilterParametersConfigurationObject1->SetWindowSize( 101696352L );
    trackerFilterParametersConfigurationObject1->SetStabilizeCount( 101696352L );
    trackerFilterParametersConfigurationObject1->SetMaxBadPoints( 101696352L );
    trackerFilterParametersConfigurationObject1->SetModelType( TrackerFilterModelType::Damp2 );
    trackerFilterParametersConfigurationObject1->SetSigmaR( 8144815361344128 );
    trackerFilterParametersConfigurationObject1->SetSigmaAcc( 8144815361344128 );
    trackerFilterParametersConfigurationObject1->SetTauVel( 8144815361344128 );
    trackerFilterParametersConfigurationObject1->SetTauAcc( 8144815361344128 );
    trackerFilterParametersConfigurationObject1->SetDeltaRMin( 8144815361344128 );
    trackerFilterParametersConfigurationObject1->SetDeltaVMax( 8144815361344128 );
    trackerFilterParametersConfigurationObject1->SetDeltaAMax( 8144815361344128 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *trackerFilterParametersConfigurationObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto trackerFilterParametersConfigurationObject2 = std::reinterpret_pointer_cast<TrackerFilterParametersConfigurationObject>( ReadDataFrom( source ) );
    bool equal = trackerFilterParametersConfigurationObject2->IsEqualTo( *trackerFilterParametersConfigurationObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TrackInfoObjectSerializationTest
BOOST_AUTO_TEST_CASE( TrackInfoObjectSerializationTest )
{
    auto trackInfoObject1 = std::make_shared<TrackInfoObject>( );
    trackInfoObject1->SetId( Guid( L"{DDE619C0-47E8-DC84-3B21-E217BB679803}" ) );
    trackInfoObject1->SetRowVersion( -2556839622958769728LL );
    trackInfoObject1->SetFirstTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    trackInfoObject1->SetLastTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    trackInfoObject1->SetCount( -2556839622958769728LL );
    trackInfoObject1->SetNorthWestLatitude( 15889904450750782 );
    trackInfoObject1->SetNorthWestLongitude( 15889904450750782 );
    trackInfoObject1->SetSouthEastLatitude( 15889904450750782 );
    trackInfoObject1->SetSouthEastLongitude( 15889904450750782 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *trackInfoObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto trackInfoObject2 = std::reinterpret_pointer_cast<TrackInfoObject>( ReadDataFrom( source ) );
    bool equal = trackInfoObject2->IsEqualTo( *trackInfoObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TrackingServiceOptionsObjectSerializationTest
BOOST_AUTO_TEST_CASE( TrackingServiceOptionsObjectSerializationTest )
{
    auto trackingServiceOptionsObject1 = std::make_shared<TrackingServiceOptionsObject>( );
    trackingServiceOptionsObject1->SetId( Guid( L"{EBE67FA6-2321-643C-263C-C484D767FE65}" ) );
    trackingServiceOptionsObject1->SetRowVersion( 7222686530994077606LL );
    trackingServiceOptionsObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    trackingServiceOptionsObject1->SetTimerInterval( TimeSpan( 770994077606LL ) );
    trackingServiceOptionsObject1->SetMaxAgeOfCurrentTrackValue( TimeSpan( 770994077606LL ) );
    trackingServiceOptionsObject1->SetFalseThreshold( 7222686530994078 );
    trackingServiceOptionsObject1->SetDistanceThreshold( 7222686530994078 );
    trackingServiceOptionsObject1->SetDistanceUnmergeThreshold( 7222686530994078 );
    trackingServiceOptionsObject1->SetUnmergeLatency( 7222686530994077606LL );
    trackingServiceOptionsObject1->SetKalmanFiltering( false );
    trackingServiceOptionsObject1->SetMaxCourseDeviation( 7222686530994078 );
    trackingServiceOptionsObject1->SetMaxSpeedDeviation( 7222686530994078 );
    trackingServiceOptionsObject1->SetMinimumSpeedThreshold( 7222686530994078 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *trackingServiceOptionsObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto trackingServiceOptionsObject2 = std::reinterpret_pointer_cast<TrackingServiceOptionsObject>( ReadDataFrom( source ) );
    bool equal = trackingServiceOptionsObject2->IsEqualTo( *trackingServiceOptionsObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TrackLinkObjectSerializationTest
BOOST_AUTO_TEST_CASE( TrackLinkObjectSerializationTest )
{
    auto trackLinkObject1 = std::make_shared<TrackLinkObject>( );
    trackLinkObject1->SetId( Guid( L"{2FB7B770-A73D-F8B1-1F8D-E5BCF4EDED0E}" ) );
    trackLinkObject1->SetRowVersion( -526455800190224528LL );
    trackLinkObject1->SetPrimary( Guid( L"{2FB7B770-A73D-F8B1-1F8D-E5BCF4EDED0E}" ) );
    trackLinkObject1->SetSecondary( Guid( L"{2FB7B770-A73D-F8B1-1F8D-E5BCF4EDED0E}" ) );
    trackLinkObject1->SetStart( DateTime( 1, 1, 1, 22, 23, 35 ) );
    trackLinkObject1->SetEnd( DateTime( 1, 1, 1, 22, 23, 35 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *trackLinkObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto trackLinkObject2 = std::reinterpret_pointer_cast<TrackLinkObject>( ReadDataFrom( source ) );
    bool equal = trackLinkObject2->IsEqualTo( *trackLinkObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TrackValueObjectSerializationTest
BOOST_AUTO_TEST_CASE( TrackValueObjectSerializationTest )
{
    auto trackValueObject1 = std::make_shared<TrackValueObject>( );
    trackValueObject1->SetId( Guid( L"{314730E2-D36D-A435-25AC-CBB68CE20C47}" ) );
    trackValueObject1->SetRowVersion( -6614148011792060190LL );
    trackValueObject1->SetTrack( Guid( L"{314730E2-D36D-A435-25AC-CBB68CE20C47}" ) );
    trackValueObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    trackValueObject1->SetFlags( TrackFlags::Course );
    trackValueObject1->SetStatus( TrackStatus::RestrictedManeuverability );
    trackValueObject1->SetLatitude( 11832596061917492 );
    trackValueObject1->SetLongitude( 11832596061917492 );
    trackValueObject1->SetSpeed( 11832596061917492 );
    trackValueObject1->SetCourse( 11832596061917492 );
    trackValueObject1->SetHeading( 11832596061917492 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *trackValueObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto trackValueObject2 = std::reinterpret_pointer_cast<TrackValueObject>( ReadDataFrom( source ) );
    bool equal = trackValueObject2->IsEqualTo( *trackValueObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TrackValue3DObjectSerializationTest
BOOST_AUTO_TEST_CASE( TrackValue3DObjectSerializationTest )
{
    auto trackValue3DObject1 = std::make_shared<TrackValue3DObject>( );
    trackValue3DObject1->SetId( Guid( L"{8B49E8E0-2358-68D7-16EB-C41AD1921707}" ) );
    trackValue3DObject1->SetRowVersion( 7554545763138267360LL );
    trackValue3DObject1->SetTrack( Guid( L"{8B49E8E0-2358-68D7-16EB-C41AD1921707}" ) );
    trackValue3DObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    trackValue3DObject1->SetFlags( TrackFlags3D::None );
    trackValue3DObject1->SetStatus( 2336876768UL );
    trackValue3DObject1->SetLatitude( 7554545763138267 );
    trackValue3DObject1->SetLongitude( 7554545763138267 );
    trackValue3DObject1->SetAltitude( 7554545763138267 );
    trackValue3DObject1->SetSpeed( 7554545763138267 );
    trackValue3DObject1->SetCourse( 7554545763138267 );
    trackValue3DObject1->SetRateOfClimb( 7554545763138267 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *trackValue3DObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto trackValue3DObject2 = std::reinterpret_pointer_cast<TrackValue3DObject>( ReadDataFrom( source ) );
    bool equal = trackValue3DObject2->IsEqualTo( *trackValue3DObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt16TimeseriesValueObjectSerializationTest
BOOST_AUTO_TEST_CASE( UInt16TimeseriesValueObjectSerializationTest )
{
    auto uInt16TimeseriesValueObject1 = std::make_shared<UInt16TimeseriesValueObject>( );
    uInt16TimeseriesValueObject1->SetId( Guid( L"{6136B482-E2B0-C76B-E3D6-470D866C2D41}" ) );
    uInt16TimeseriesValueObject1->SetRowVersion( -4076915790480755582LL );
    uInt16TimeseriesValueObject1->SetTimeseries( Guid( L"{6136B482-E2B0-C76B-E3D6-470D866C2D41}" ) );
    uInt16TimeseriesValueObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    uInt16TimeseriesValueObject1->SetValue( 46210 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt16TimeseriesValueObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt16TimeseriesValueObject2 = std::reinterpret_pointer_cast<UInt16TimeseriesValueObject>( ReadDataFrom( source ) );
    bool equal = uInt16TimeseriesValueObject2->IsEqualTo( *uInt16TimeseriesValueObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt32TimeseriesValueObjectSerializationTest
BOOST_AUTO_TEST_CASE( UInt32TimeseriesValueObjectSerializationTest )
{
    auto uInt32TimeseriesValueObject1 = std::make_shared<UInt32TimeseriesValueObject>( );
    uInt32TimeseriesValueObject1->SetId( Guid( L"{485A0A48-CCBD-4975-92AE-33BD125A5012}" ) );
    uInt32TimeseriesValueObject1->SetRowVersion( 5293362050378631752LL );
    uInt32TimeseriesValueObject1->SetTimeseries( Guid( L"{485A0A48-CCBD-4975-92AE-33BD125A5012}" ) );
    uInt32TimeseriesValueObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    uInt32TimeseriesValueObject1->SetValue( 1213860424UL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt32TimeseriesValueObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt32TimeseriesValueObject2 = std::reinterpret_pointer_cast<UInt32TimeseriesValueObject>( ReadDataFrom( source ) );
    bool equal = uInt32TimeseriesValueObject2->IsEqualTo( *uInt32TimeseriesValueObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt64TimeseriesValueObjectSerializationTest
BOOST_AUTO_TEST_CASE( UInt64TimeseriesValueObjectSerializationTest )
{
    auto uInt64TimeseriesValueObject1 = std::make_shared<UInt64TimeseriesValueObject>( );
    uInt64TimeseriesValueObject1->SetId( Guid( L"{2B846AF0-4E92-0F11-F088-7249D421560F}" ) );
    uInt64TimeseriesValueObject1->SetRowVersion( 1085735374875290352LL );
    uInt64TimeseriesValueObject1->SetTimeseries( Guid( L"{2B846AF0-4E92-0F11-F088-7249D421560F}" ) );
    uInt64TimeseriesValueObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 35 ) );
    uInt64TimeseriesValueObject1->SetValue( 1085735374875290352LL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt64TimeseriesValueObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt64TimeseriesValueObject2 = std::reinterpret_pointer_cast<UInt64TimeseriesValueObject>( ReadDataFrom( source ) );
    bool equal = uInt64TimeseriesValueObject2->IsEqualTo( *uInt64TimeseriesValueObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/VehicleTypeObjectSerializationTest
BOOST_AUTO_TEST_CASE( VehicleTypeObjectSerializationTest )
{
    auto vehicleTypeObject1 = std::make_shared<VehicleTypeObject>( );
    vehicleTypeObject1->SetId( Guid( L"{782DCD85-3771-1ED2-784B-EC8E1EB4B3A1}" ) );
    vehicleTypeObject1->SetRowVersion( 2220898526734175621LL );
    vehicleTypeObject1->SetName( L"Name" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *vehicleTypeObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto vehicleTypeObject2 = std::reinterpret_pointer_cast<VehicleTypeObject>( ReadDataFrom( source ) );
    bool equal = vehicleTypeObject2->IsEqualTo( *vehicleTypeObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/VesselTypeObjectSerializationTest
BOOST_AUTO_TEST_CASE( VesselTypeObjectSerializationTest )
{
    auto vesselTypeObject1 = std::make_shared<VesselTypeObject>( );
    vesselTypeObject1->SetId( Guid( L"{D5182F76-234A-4853-12CA-C452AB18F46E}" ) );
    vesselTypeObject1->SetRowVersion( 5211547998107479926LL );
    vesselTypeObject1->SetName( L"Name" );
    vesselTypeObject1->SetCode( -719835274L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *vesselTypeObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto vesselTypeObject2 = std::reinterpret_pointer_cast<VesselTypeObject>( ReadDataFrom( source ) );
    bool equal = vesselTypeObject2->IsEqualTo( *vesselTypeObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ViewObjectSerializationTest
BOOST_AUTO_TEST_CASE( ViewObjectSerializationTest )
{
    auto viewObject1 = std::make_shared<ViewObject>( );
    viewObject1->SetId( Guid( L"{2019E5C1-3542-B628-6D14-AC420498A783}" ) );
    viewObject1->SetRowVersion( -5320944401615559231LL );
    viewObject1->SetName( L"Name" );
    viewObject1->SetLatitudeTimeseries( Guid( L"{2019E5C1-3542-B628-6D14-AC420498A783}" ) );
    viewObject1->SetLongitudeTimeseries( Guid( L"{2019E5C1-3542-B628-6D14-AC420498A783}" ) );
    viewObject1->SetZoomLevelTimeseries( Guid( L"{2019E5C1-3542-B628-6D14-AC420498A783}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *viewObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto viewObject2 = std::reinterpret_pointer_cast<ViewObject>( ReadDataFrom( source ) );
    bool equal = viewObject2->IsEqualTo( *viewObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ViewCameraLinkObjectSerializationTest
BOOST_AUTO_TEST_CASE( ViewCameraLinkObjectSerializationTest )
{
    auto viewCameraLinkObject1 = std::make_shared<ViewCameraLinkObject>( );
    viewCameraLinkObject1->SetId( Guid( L"{9F75C5E8-84D0-8E5E-717A-210BF9AEA317}" ) );
    viewCameraLinkObject1->SetRowVersion( -8187961040949623320LL );
    viewCameraLinkObject1->SetView( Guid( L"{9F75C5E8-84D0-8E5E-717A-210BF9AEA317}" ) );
    viewCameraLinkObject1->SetCamera( Guid( L"{9F75C5E8-84D0-8E5E-717A-210BF9AEA317}" ) );
    viewCameraLinkObject1->SetStart( DateTime( 1, 1, 1, 22, 23, 36 ) );
    viewCameraLinkObject1->SetEnd( DateTime( 1, 1, 1, 22, 23, 36 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *viewCameraLinkObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto viewCameraLinkObject2 = std::reinterpret_pointer_cast<ViewCameraLinkObject>( ReadDataFrom( source ) );
    bool equal = viewCameraLinkObject2->IsEqualTo( *viewCameraLinkObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ViewTrackerLinkObjectSerializationTest
BOOST_AUTO_TEST_CASE( ViewTrackerLinkObjectSerializationTest )
{
    auto viewTrackerLinkObject1 = std::make_shared<ViewTrackerLinkObject>( );
    viewTrackerLinkObject1->SetId( Guid( L"{4326A801-681C-3499-2C99-1638C2641580}" ) );
    viewTrackerLinkObject1->SetRowVersion( 3790175032003962881LL );
    viewTrackerLinkObject1->SetView( Guid( L"{4326A801-681C-3499-2C99-1638C2641580}" ) );
    viewTrackerLinkObject1->SetTracker( Guid( L"{4326A801-681C-3499-2C99-1638C2641580}" ) );
    viewTrackerLinkObject1->SetStart( DateTime( 1, 1, 1, 22, 23, 36 ) );
    viewTrackerLinkObject1->SetEnd( DateTime( 1, 1, 1, 22, 23, 36 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *viewTrackerLinkObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto viewTrackerLinkObject2 = std::reinterpret_pointer_cast<ViewTrackerLinkObject>( ReadDataFrom( source ) );
    bool equal = viewTrackerLinkObject2->IsEqualTo( *viewTrackerLinkObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/WeatherStationCommandObjectSerializationTest
BOOST_AUTO_TEST_CASE( WeatherStationCommandObjectSerializationTest )
{
    auto weatherStationCommandObject1 = std::make_shared<WeatherStationCommandObject>( );
    weatherStationCommandObject1->SetId( Guid( L"{15A71ED0-61D0-1B4B-D8D2-860BA8E5780B}" ) );
    weatherStationCommandObject1->SetRowVersion( 1966773208621719248LL );
    weatherStationCommandObject1->SetWeatherStation( Guid( L"{15A71ED0-61D0-1B4B-D8D2-860BA8E5780B}" ) );
    weatherStationCommandObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 36 ) );
    weatherStationCommandObject1->SetDeviceCommandSourceType( DeviceCommandSourceType::Unknown );
    weatherStationCommandObject1->SetDeviceCommandSourceId( Guid( L"{15A71ED0-61D0-1B4B-D8D2-860BA8E5780B}" ) );
    weatherStationCommandObject1->SetReply( Guid( L"{15A71ED0-61D0-1B4B-D8D2-860BA8E5780B}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *weatherStationCommandObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto weatherStationCommandObject2 = std::reinterpret_pointer_cast<WeatherStationCommandObject>( ReadDataFrom( source ) );
    bool equal = weatherStationCommandObject2->IsEqualTo( *weatherStationCommandObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/WeatherStationCommandReplyObjectSerializationTest
BOOST_AUTO_TEST_CASE( WeatherStationCommandReplyObjectSerializationTest )
{
    auto weatherStationCommandReplyObject1 = std::make_shared<WeatherStationCommandReplyObject>( );
    weatherStationCommandReplyObject1->SetId( Guid( L"{EB8BB859-93A7-CFCE-F373-C9E5D7D11D9A}" ) );
    weatherStationCommandReplyObject1->SetRowVersion( -3472675913235449767LL );
    weatherStationCommandReplyObject1->SetWeatherStation( Guid( L"{EB8BB859-93A7-CFCE-F373-C9E5D7D11D9A}" ) );
    weatherStationCommandReplyObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 36 ) );
    weatherStationCommandReplyObject1->SetCommand( Guid( L"{EB8BB859-93A7-CFCE-F373-C9E5D7D11D9A}" ) );
    weatherStationCommandReplyObject1->SetStatus( DeviceCommandReplyStatus::Ok );
    weatherStationCommandReplyObject1->SetMessage( L"Message" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *weatherStationCommandReplyObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto weatherStationCommandReplyObject2 = std::reinterpret_pointer_cast<WeatherStationCommandReplyObject>( ReadDataFrom( source ) );
    bool equal = weatherStationCommandReplyObject2->IsEqualTo( *weatherStationCommandReplyObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/WeatherStationConfigurationObjectSerializationTest
BOOST_AUTO_TEST_CASE( WeatherStationConfigurationObjectSerializationTest )
{
    auto weatherStationConfigurationObject1 = std::make_shared<WeatherStationConfigurationObject>( );
    weatherStationConfigurationObject1->SetId( Guid( L"{48131464-C2BB-F6DD-6FBB-43DD12C82826}" ) );
    weatherStationConfigurationObject1->SetRowVersion( -658155860902341532LL );
    weatherStationConfigurationObject1->SetWeatherStation( Guid( L"{48131464-C2BB-F6DD-6FBB-43DD12C82826}" ) );
    weatherStationConfigurationObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 36 ) );
    weatherStationConfigurationObject1->SetNoDataTimeOut( TimeSpan( -404902341532LL ) );
    weatherStationConfigurationObject1->SetSendInterval( TimeSpan( -404902341532LL ) );
    weatherStationConfigurationObject1->SetLatitude( 17788588212807212 );
    weatherStationConfigurationObject1->SetLongitude( 17788588212807212 );
    weatherStationConfigurationObject1->SetGyroOffset( 17788588212807212 );
    weatherStationConfigurationObject1->SetEnableAveraging( false );
    weatherStationConfigurationObject1->SetAveragingInterval( TimeSpan( -404902341532LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *weatherStationConfigurationObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto weatherStationConfigurationObject2 = std::reinterpret_pointer_cast<WeatherStationConfigurationObject>( ReadDataFrom( source ) );
    bool equal = weatherStationConfigurationObject2->IsEqualTo( *weatherStationConfigurationObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CircularZoneObjectSerializationTest
BOOST_AUTO_TEST_CASE( CircularZoneObjectSerializationTest )
{
    auto circularZoneObject1 = std::make_shared<CircularZoneObject>( );
    circularZoneObject1->SetId( Guid( L"{D8FE5507-6CC5-1F7F-F8FE-36A31B7FAAE0}" ) );
    circularZoneObject1->SetRowVersion( 2269652334222923015LL );
    circularZoneObject1->SetName( L"Name" );
    circularZoneObject1->SetLongitude( 2269652334222923 );
    circularZoneObject1->SetLatitude( 2269652334222923 );
    circularZoneObject1->SetAlarmType( ZoneAlarmType::None );
    circularZoneObject1->SetAlarmTime( TimeSpan( 366222923015LL ) );
    circularZoneObject1->SetRadarTrackMinimumLifetime( TimeSpan( 366222923015LL ) );
    circularZoneObject1->SetSpeed( 2269652334222923 );
    circularZoneObject1->SetStrokeColor( 3640546567UL );
    circularZoneObject1->SetFillColor( 3640546567UL );
    circularZoneObject1->SetRadius( 2269652334222923 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *circularZoneObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto circularZoneObject2 = std::reinterpret_pointer_cast<CircularZoneObject>( ReadDataFrom( source ) );
    bool equal = circularZoneObject2->IsEqualTo( *circularZoneObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/PolygonZoneObjectSerializationTest
BOOST_AUTO_TEST_CASE( PolygonZoneObjectSerializationTest )
{
    auto polygonZoneObject1 = std::make_shared<PolygonZoneObject>( );
    polygonZoneObject1->SetId( Guid( L"{3554124C-5386-5304-CA20-CA61AC2A4832}" ) );
    polygonZoneObject1->SetRowVersion( 5981998040940286540LL );
    polygonZoneObject1->SetName( L"Name" );
    polygonZoneObject1->SetLongitude( 5981998040940287 );
    polygonZoneObject1->SetLatitude( 5981998040940287 );
    polygonZoneObject1->SetAlarmType( ZoneAlarmType::None );
    polygonZoneObject1->SetAlarmTime( TimeSpan( 728940286540LL ) );
    polygonZoneObject1->SetRadarTrackMinimumLifetime( TimeSpan( 728940286540LL ) );
    polygonZoneObject1->SetSpeed( 5981998040940287 );
    polygonZoneObject1->SetStrokeColor( 894702156UL );
    polygonZoneObject1->SetFillColor( 894702156UL );
    polygonZoneObject1->SetPolygon( { {'P','o','l','y','g','o','n'} } );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *polygonZoneObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto polygonZoneObject2 = std::reinterpret_pointer_cast<PolygonZoneObject>( ReadDataFrom( source ) );
    bool equal = polygonZoneObject2->IsEqualTo( *polygonZoneObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ZoneExceptionsObjectSerializationTest
BOOST_AUTO_TEST_CASE( ZoneExceptionsObjectSerializationTest )
{
    auto zoneExceptionsObject1 = std::make_shared<ZoneExceptionsObject>( );
    zoneExceptionsObject1->SetId( Guid( L"{B1060A97-736B-DDAC-BB35-CED68D6050E9}" ) );
    zoneExceptionsObject1->SetRowVersion( -2473475188964586857LL );
    zoneExceptionsObject1->SetZone( Guid( L"{B1060A97-736B-DDAC-BB35-CED68D6050E9}" ) );
    zoneExceptionsObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 36 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *zoneExceptionsObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto zoneExceptionsObject2 = std::reinterpret_pointer_cast<ZoneExceptionsObject>( ReadDataFrom( source ) );
    bool equal = zoneExceptionsObject2->IsEqualTo( *zoneExceptionsObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ZoneExceptionsVesselLinkObjectSerializationTest
BOOST_AUTO_TEST_CASE( ZoneExceptionsVesselLinkObjectSerializationTest )
{
    auto zoneExceptionsVesselLinkObject1 = std::make_shared<ZoneExceptionsVesselLinkObject>( );
    zoneExceptionsVesselLinkObject1->SetId( Guid( L"{88FC45CD-DF1D-6687-66E1-FBB8113FA2B3}" ) );
    zoneExceptionsVesselLinkObject1->SetRowVersion( 7388119031669867981LL );
    zoneExceptionsVesselLinkObject1->SetZoneExceptions( Guid( L"{88FC45CD-DF1D-6687-66E1-FBB8113FA2B3}" ) );
    zoneExceptionsVesselLinkObject1->SetVessel( Guid( L"{88FC45CD-DF1D-6687-66E1-FBB8113FA2B3}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *zoneExceptionsVesselLinkObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto zoneExceptionsVesselLinkObject2 = std::reinterpret_pointer_cast<ZoneExceptionsVesselLinkObject>( ReadDataFrom( source ) );
    bool equal = zoneExceptionsVesselLinkObject2->IsEqualTo( *zoneExceptionsVesselLinkObject1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ZoneTrackAlarmObjectSerializationTest
BOOST_AUTO_TEST_CASE( ZoneTrackAlarmObjectSerializationTest )
{
    auto zoneTrackAlarmObject1 = std::make_shared<ZoneTrackAlarmObject>( );
    zoneTrackAlarmObject1->SetId( Guid( L"{0F40BC2F-963C-F3B4-CF2D-693CF0023DF4}" ) );
    zoneTrackAlarmObject1->SetRowVersion( -885918041987040209LL );
    zoneTrackAlarmObject1->SetTrack( Guid( L"{0F40BC2F-963C-F3B4-CF2D-693CF0023DF4}" ) );
    zoneTrackAlarmObject1->SetZone( Guid( L"{0F40BC2F-963C-F3B4-CF2D-693CF0023DF4}" ) );
    zoneTrackAlarmObject1->SetRadarTrack( Guid( L"{0F40BC2F-963C-F3B4-CF2D-693CF0023DF4}" ) );
    zoneTrackAlarmObject1->SetTimestamp( DateTime( 1, 1, 1, 22, 23, 36 ) );
    zoneTrackAlarmObject1->SetLatitude( 17560826031722512 );
    zoneTrackAlarmObject1->SetLongitude( 17560826031722512 );
    zoneTrackAlarmObject1->SetSpeed( 17560826031722512 );
    zoneTrackAlarmObject1->SetCourse( 17560826031722512 );
    zoneTrackAlarmObject1->SetHeading( 17560826031722512 );
    zoneTrackAlarmObject1->SetEnterLatitude( 17560826031722512 );
    zoneTrackAlarmObject1->SetEnterLongitude( 17560826031722512 );
    zoneTrackAlarmObject1->SetLeaveLatitude( 17560826031722512 );
    zoneTrackAlarmObject1->SetLeaveLongitude( 17560826031722512 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *zoneTrackAlarmObject1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto zoneTrackAlarmObject2 = std::reinterpret_pointer_cast<ZoneTrackAlarmObject>( ReadDataFrom( source ) );
    bool equal = zoneTrackAlarmObject2->IsEqualTo( *zoneTrackAlarmObject1 );
    BOOST_CHECK( equal );
}

BOOST_AUTO_TEST_SUITE_END( )
