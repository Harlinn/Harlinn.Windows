#include <HCCIO.h>
#include "Data/DataTypes.h"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace Harlinn::Common;
using namespace Harlinn::ODBC;
using namespace Harlinn;
using namespace Barrelman;
using namespace Barrelman::Data;

class DataTypesLocalFixture
{
public:
    DataTypesLocalFixture( ) = default;
    ~DataTypesLocalFixture( ) = default;
};

BOOST_FIXTURE_TEST_SUITE( DataTypesTests, DataTypesLocalFixture )

// --run_test=DataTypesTests/AircraftTypeDataSerializationTest
BOOST_AUTO_TEST_CASE( AircraftTypeDataSerializationTest )
{
    auto aircraftTypeData1 = std::make_shared<AircraftTypeData>( );
    aircraftTypeData1->SetId( Guid( L"{E0A93EC5-8153-304B-0CD2-81CA07957CA3}" ) );
    aircraftTypeData1->SetRowVersion( 3480017334325296837LL );
    aircraftTypeData1->SetName( L"Name" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aircraftTypeData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aircraftTypeData2 = std::reinterpret_pointer_cast<AircraftTypeData>( ReadDataFrom( source ) );
    bool equal = aircraftTypeData2->IsEqualTo( *aircraftTypeData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AidToNavigationReportMessageDataSerializationTest
BOOST_AUTO_TEST_CASE( AidToNavigationReportMessageDataSerializationTest )
{
    auto aidToNavigationReportMessageData1 = std::make_shared<AidToNavigationReportMessageData>( );
    aidToNavigationReportMessageData1->SetId( Guid( L"{A8095C85-AF09-1B47-D8E2-F59015903AA1}" ) );
    aidToNavigationReportMessageData1->SetRowVersion( 1965732218379263109LL );
    aidToNavigationReportMessageData1->SetAisTransceiver( Guid( L"{A8095C85-AF09-1B47-D8E2-F59015903AA1}" ) );
    aidToNavigationReportMessageData1->SetReceivedTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aidToNavigationReportMessageData1->SetMessageSequenceNumber( 1965732218379263109LL );
    aidToNavigationReportMessageData1->SetRepeat( -1475781499L );
    aidToNavigationReportMessageData1->SetMmsi( Guid( L"{A8095C85-AF09-1B47-D8E2-F59015903AA1}" ) );
    aidToNavigationReportMessageData1->SetNavigationalAidType( NavigationalAidType::LightWithoutSectors );
    aidToNavigationReportMessageData1->SetName( L"Name" );
    aidToNavigationReportMessageData1->SetPositionAccuracy( PositionAccuracy::High );
    aidToNavigationReportMessageData1->SetLongitude( 1965732218379263.2 );
    aidToNavigationReportMessageData1->SetLatitude( 1965732218379263.2 );
    aidToNavigationReportMessageData1->SetDimensionToBow( -1475781499L );
    aidToNavigationReportMessageData1->SetDimensionToStern( -1475781499L );
    aidToNavigationReportMessageData1->SetDimensionToPort( -1475781499L );
    aidToNavigationReportMessageData1->SetDimensionToStarboard( -1475781499L );
    aidToNavigationReportMessageData1->SetPositionFixType( PositionFixType::Undefined2 );
    aidToNavigationReportMessageData1->SetTimestamp( -1475781499L );
    aidToNavigationReportMessageData1->SetOffPosition( false );
    aidToNavigationReportMessageData1->SetRegionalReserved( -1475781499L );
    aidToNavigationReportMessageData1->SetRaim( Raim::InUse );
    aidToNavigationReportMessageData1->SetVirtualAid( false );
    aidToNavigationReportMessageData1->SetAssigned( false );
    aidToNavigationReportMessageData1->SetSpare( -1475781499L );
    aidToNavigationReportMessageData1->SetNameExtension( L"NameExtension" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aidToNavigationReportMessageData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aidToNavigationReportMessageData2 = std::reinterpret_pointer_cast<AidToNavigationReportMessageData>( ReadDataFrom( source ) );
    bool equal = aidToNavigationReportMessageData2->IsEqualTo( *aidToNavigationReportMessageData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisAddressedSafetyRelatedMessageDataSerializationTest
BOOST_AUTO_TEST_CASE( AisAddressedSafetyRelatedMessageDataSerializationTest )
{
    auto aisAddressedSafetyRelatedMessageData1 = std::make_shared<AisAddressedSafetyRelatedMessageData>( );
    aisAddressedSafetyRelatedMessageData1->SetId( Guid( L"{E6B4FA51-12E6-F131-8F8C-4867672D5F8A}" ) );
    aisAddressedSafetyRelatedMessageData1->SetRowVersion( -1067050853787698607LL );
    aisAddressedSafetyRelatedMessageData1->SetAisTransceiver( Guid( L"{E6B4FA51-12E6-F131-8F8C-4867672D5F8A}" ) );
    aisAddressedSafetyRelatedMessageData1->SetReceivedTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisAddressedSafetyRelatedMessageData1->SetMessageSequenceNumber( -1067050853787698607LL );
    aisAddressedSafetyRelatedMessageData1->SetRepeat( -424347055L );
    aisAddressedSafetyRelatedMessageData1->SetMmsi( Guid( L"{E6B4FA51-12E6-F131-8F8C-4867672D5F8A}" ) );
    aisAddressedSafetyRelatedMessageData1->SetSequenceNumber( -424347055L );
    aisAddressedSafetyRelatedMessageData1->SetDestinationMmsi( Guid( L"{E6B4FA51-12E6-F131-8F8C-4867672D5F8A}" ) );
    aisAddressedSafetyRelatedMessageData1->SetRetransmitFlag( false );
    aisAddressedSafetyRelatedMessageData1->SetSpare( -424347055L );
    aisAddressedSafetyRelatedMessageData1->SetText( L"Text" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisAddressedSafetyRelatedMessageData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisAddressedSafetyRelatedMessageData2 = std::reinterpret_pointer_cast<AisAddressedSafetyRelatedMessageData>( ReadDataFrom( source ) );
    bool equal = aisAddressedSafetyRelatedMessageData2->IsEqualTo( *aisAddressedSafetyRelatedMessageData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisBaseStationReportMessageDataSerializationTest
BOOST_AUTO_TEST_CASE( AisBaseStationReportMessageDataSerializationTest )
{
    auto aisBaseStationReportMessageData1 = std::make_shared<AisBaseStationReportMessageData>( );
    aisBaseStationReportMessageData1->SetId( Guid( L"{7D642251-4972-A316-C568-924EBE26448A}" ) );
    aisBaseStationReportMessageData1->SetRowVersion( -6695083039960849839LL );
    aisBaseStationReportMessageData1->SetAisTransceiver( Guid( L"{7D642251-4972-A316-C568-924EBE26448A}" ) );
    aisBaseStationReportMessageData1->SetReceivedTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisBaseStationReportMessageData1->SetMessageSequenceNumber( -6695083039960849839LL );
    aisBaseStationReportMessageData1->SetRepeat( 2103714385L );
    aisBaseStationReportMessageData1->SetMmsi( Guid( L"{7D642251-4972-A316-C568-924EBE26448A}" ) );
    aisBaseStationReportMessageData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisBaseStationReportMessageData1->SetPositionAccuracy( PositionAccuracy::High );
    aisBaseStationReportMessageData1->SetLongitude( 11751661033748702 );
    aisBaseStationReportMessageData1->SetLatitude( 11751661033748702 );
    aisBaseStationReportMessageData1->SetPositionFixType( PositionFixType::Surveyed );
    aisBaseStationReportMessageData1->SetSpare( 2103714385L );
    aisBaseStationReportMessageData1->SetRaim( Raim::InUse );
    aisBaseStationReportMessageData1->SetRadioStatus( 2103714385L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisBaseStationReportMessageData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisBaseStationReportMessageData2 = std::reinterpret_pointer_cast<AisBaseStationReportMessageData>( ReadDataFrom( source ) );
    bool equal = aisBaseStationReportMessageData2->IsEqualTo( *aisBaseStationReportMessageData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisBinaryAcknowledgeMessageDataSerializationTest
BOOST_AUTO_TEST_CASE( AisBinaryAcknowledgeMessageDataSerializationTest )
{
    auto aisBinaryAcknowledgeMessageData1 = std::make_shared<AisBinaryAcknowledgeMessageData>( );
    aisBinaryAcknowledgeMessageData1->SetId( Guid( L"{7D7D182B-0D08-F217-4FE8-B010BEBE18D4}" ) );
    aisBinaryAcknowledgeMessageData1->SetRowVersion( -1002318061950396373LL );
    aisBinaryAcknowledgeMessageData1->SetAisTransceiver( Guid( L"{7D7D182B-0D08-F217-4FE8-B010BEBE18D4}" ) );
    aisBinaryAcknowledgeMessageData1->SetReceivedTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisBinaryAcknowledgeMessageData1->SetMessageSequenceNumber( -1002318061950396373LL );
    aisBinaryAcknowledgeMessageData1->SetRepeat( 2105350187L );
    aisBinaryAcknowledgeMessageData1->SetMmsi( Guid( L"{7D7D182B-0D08-F217-4FE8-B010BEBE18D4}" ) );
    aisBinaryAcknowledgeMessageData1->SetSpare( 2105350187L );
    aisBinaryAcknowledgeMessageData1->SetSequenceNumber1( 2105350187L );
    aisBinaryAcknowledgeMessageData1->SetMmsi1( Guid( L"{7D7D182B-0D08-F217-4FE8-B010BEBE18D4}" ) );
    aisBinaryAcknowledgeMessageData1->SetSequenceNumber2( 2105350187L );
    aisBinaryAcknowledgeMessageData1->SetMmsi2( Guid( L"{7D7D182B-0D08-F217-4FE8-B010BEBE18D4}" ) );
    aisBinaryAcknowledgeMessageData1->SetSequenceNumber3( 2105350187L );
    aisBinaryAcknowledgeMessageData1->SetMmsi3( Guid( L"{7D7D182B-0D08-F217-4FE8-B010BEBE18D4}" ) );
    aisBinaryAcknowledgeMessageData1->SetSequenceNumber4( 2105350187L );
    aisBinaryAcknowledgeMessageData1->SetMmsi4( Guid( L"{7D7D182B-0D08-F217-4FE8-B010BEBE18D4}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisBinaryAcknowledgeMessageData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisBinaryAcknowledgeMessageData2 = std::reinterpret_pointer_cast<AisBinaryAcknowledgeMessageData>( ReadDataFrom( source ) );
    bool equal = aisBinaryAcknowledgeMessageData2->IsEqualTo( *aisBinaryAcknowledgeMessageData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisBinaryAddressedMessageDataSerializationTest
BOOST_AUTO_TEST_CASE( AisBinaryAddressedMessageDataSerializationTest )
{
    auto aisBinaryAddressedMessageData1 = std::make_shared<AisBinaryAddressedMessageData>( );
    aisBinaryAddressedMessageData1->SetId( Guid( L"{D1FE2C97-3198-60D6-066B-8C198B7F34E9}" ) );
    aisBinaryAddressedMessageData1->SetRowVersion( 6977819205085047959LL );
    aisBinaryAddressedMessageData1->SetAisTransceiver( Guid( L"{D1FE2C97-3198-60D6-066B-8C198B7F34E9}" ) );
    aisBinaryAddressedMessageData1->SetReceivedTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisBinaryAddressedMessageData1->SetMessageSequenceNumber( 6977819205085047959LL );
    aisBinaryAddressedMessageData1->SetRepeat( -771871593L );
    aisBinaryAddressedMessageData1->SetMmsi( Guid( L"{D1FE2C97-3198-60D6-066B-8C198B7F34E9}" ) );
    aisBinaryAddressedMessageData1->SetSequenceNumber( -771871593L );
    aisBinaryAddressedMessageData1->SetDestinationMmsi( Guid( L"{D1FE2C97-3198-60D6-066B-8C198B7F34E9}" ) );
    aisBinaryAddressedMessageData1->SetRetransmitFlag( false );
    aisBinaryAddressedMessageData1->SetSpare( -771871593L );
    aisBinaryAddressedMessageData1->SetDesignatedAreaCode( -771871593L );
    aisBinaryAddressedMessageData1->SetFunctionalId( -771871593L );
    aisBinaryAddressedMessageData1->SetData( L"Data" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisBinaryAddressedMessageData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisBinaryAddressedMessageData2 = std::reinterpret_pointer_cast<AisBinaryAddressedMessageData>( ReadDataFrom( source ) );
    bool equal = aisBinaryAddressedMessageData2->IsEqualTo( *aisBinaryAddressedMessageData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisBinaryBroadcastMessageDataSerializationTest
BOOST_AUTO_TEST_CASE( AisBinaryBroadcastMessageDataSerializationTest )
{
    auto aisBinaryBroadcastMessageData1 = std::make_shared<AisBinaryBroadcastMessageData>( );
    aisBinaryBroadcastMessageData1->SetId( Guid( L"{F2AD5C24-F9C1-C1D8-831B-9F834FB53A24}" ) );
    aisBinaryBroadcastMessageData1->SetRowVersion( -4478555218024506332LL );
    aisBinaryBroadcastMessageData1->SetAisTransceiver( Guid( L"{F2AD5C24-F9C1-C1D8-831B-9F834FB53A24}" ) );
    aisBinaryBroadcastMessageData1->SetReceivedTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisBinaryBroadcastMessageData1->SetMessageSequenceNumber( -4478555218024506332LL );
    aisBinaryBroadcastMessageData1->SetRepeat( -223519708L );
    aisBinaryBroadcastMessageData1->SetMmsi( Guid( L"{F2AD5C24-F9C1-C1D8-831B-9F834FB53A24}" ) );
    aisBinaryBroadcastMessageData1->SetSpare( -223519708L );
    aisBinaryBroadcastMessageData1->SetDesignatedAreaCode( -223519708L );
    aisBinaryBroadcastMessageData1->SetFunctionalId( -223519708L );
    aisBinaryBroadcastMessageData1->SetData( L"Data" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisBinaryBroadcastMessageData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisBinaryBroadcastMessageData2 = std::reinterpret_pointer_cast<AisBinaryBroadcastMessageData>( ReadDataFrom( source ) );
    bool equal = aisBinaryBroadcastMessageData2->IsEqualTo( *aisBinaryBroadcastMessageData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisDataLinkManagementMessageDataSerializationTest
BOOST_AUTO_TEST_CASE( AisDataLinkManagementMessageDataSerializationTest )
{
    auto aisDataLinkManagementMessageData1 = std::make_shared<AisDataLinkManagementMessageData>( );
    aisDataLinkManagementMessageData1->SetId( Guid( L"{11F331C0-404D-8BCF-D1F3-02B288CF8C03}" ) );
    aisDataLinkManagementMessageData1->SetRowVersion( -8372402482500652608LL );
    aisDataLinkManagementMessageData1->SetAisTransceiver( Guid( L"{11F331C0-404D-8BCF-D1F3-02B288CF8C03}" ) );
    aisDataLinkManagementMessageData1->SetReceivedTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisDataLinkManagementMessageData1->SetMessageSequenceNumber( -8372402482500652608LL );
    aisDataLinkManagementMessageData1->SetRepeat( 301150656L );
    aisDataLinkManagementMessageData1->SetMmsi( Guid( L"{11F331C0-404D-8BCF-D1F3-02B288CF8C03}" ) );
    aisDataLinkManagementMessageData1->SetSpare( 301150656L );
    aisDataLinkManagementMessageData1->SetOffset1( 301150656L );
    aisDataLinkManagementMessageData1->SetReservedSlots1( 301150656L );
    aisDataLinkManagementMessageData1->SetTimeout1( 301150656L );
    aisDataLinkManagementMessageData1->SetIncrement1( 301150656L );
    aisDataLinkManagementMessageData1->SetOffset2( 301150656L );
    aisDataLinkManagementMessageData1->SetReservedSlots2( 301150656L );
    aisDataLinkManagementMessageData1->SetTimeout2( 301150656L );
    aisDataLinkManagementMessageData1->SetIncrement2( 301150656L );
    aisDataLinkManagementMessageData1->SetOffset3( 301150656L );
    aisDataLinkManagementMessageData1->SetReservedSlots3( 301150656L );
    aisDataLinkManagementMessageData1->SetTimeout3( 301150656L );
    aisDataLinkManagementMessageData1->SetIncrement3( 301150656L );
    aisDataLinkManagementMessageData1->SetOffset4( 301150656L );
    aisDataLinkManagementMessageData1->SetReservedSlots4( 301150656L );
    aisDataLinkManagementMessageData1->SetTimeout4( 301150656L );
    aisDataLinkManagementMessageData1->SetIncrement4( 301150656L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisDataLinkManagementMessageData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisDataLinkManagementMessageData2 = std::reinterpret_pointer_cast<AisDataLinkManagementMessageData>( ReadDataFrom( source ) );
    bool equal = aisDataLinkManagementMessageData2->IsEqualTo( *aisDataLinkManagementMessageData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisExtendedClassBCsPositionReportMessageDataSerializationTest
BOOST_AUTO_TEST_CASE( AisExtendedClassBCsPositionReportMessageDataSerializationTest )
{
    auto aisExtendedClassBCsPositionReportMessageData1 = std::make_shared<AisExtendedClassBCsPositionReportMessageData>( );
    aisExtendedClassBCsPositionReportMessageData1->SetId( Guid( L"{3800E00B-53D3-860B-61D0-CACB1C0007D0}" ) );
    aisExtendedClassBCsPositionReportMessageData1->SetRowVersion( -8787838081240604661LL );
    aisExtendedClassBCsPositionReportMessageData1->SetAisTransceiver( Guid( L"{3800E00B-53D3-860B-61D0-CACB1C0007D0}" ) );
    aisExtendedClassBCsPositionReportMessageData1->SetReceivedTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisExtendedClassBCsPositionReportMessageData1->SetMessageSequenceNumber( -8787838081240604661LL );
    aisExtendedClassBCsPositionReportMessageData1->SetRepeat( 939581451L );
    aisExtendedClassBCsPositionReportMessageData1->SetMmsi( Guid( L"{3800E00B-53D3-860B-61D0-CACB1C0007D0}" ) );
    aisExtendedClassBCsPositionReportMessageData1->SetReserved( 939581451L );
    aisExtendedClassBCsPositionReportMessageData1->SetSpeedOverGround( 9658905992468946 );
    aisExtendedClassBCsPositionReportMessageData1->SetPositionAccuracy( PositionAccuracy::High );
    aisExtendedClassBCsPositionReportMessageData1->SetLongitude( 9658905992468946 );
    aisExtendedClassBCsPositionReportMessageData1->SetLatitude( 9658905992468946 );
    aisExtendedClassBCsPositionReportMessageData1->SetCourseOverGround( 9658905992468946 );
    aisExtendedClassBCsPositionReportMessageData1->SetTrueHeading( 939581451L );
    aisExtendedClassBCsPositionReportMessageData1->SetTimestamp( 939581451L );
    aisExtendedClassBCsPositionReportMessageData1->SetRegionalReserved( 939581451L );
    aisExtendedClassBCsPositionReportMessageData1->SetName( Guid( L"{3800E00B-53D3-860B-61D0-CACB1C0007D0}" ) );
    aisExtendedClassBCsPositionReportMessageData1->SetShipType( ShipType::PassengerReserved1 );
    aisExtendedClassBCsPositionReportMessageData1->SetDimensionToBow( 939581451L );
    aisExtendedClassBCsPositionReportMessageData1->SetDimensionToStern( 939581451L );
    aisExtendedClassBCsPositionReportMessageData1->SetDimensionToPort( 939581451L );
    aisExtendedClassBCsPositionReportMessageData1->SetDimensionToStarboard( 939581451L );
    aisExtendedClassBCsPositionReportMessageData1->SetPositionFixType( PositionFixType::Chayka );
    aisExtendedClassBCsPositionReportMessageData1->SetRaim( Raim::InUse );
    aisExtendedClassBCsPositionReportMessageData1->SetDataTerminalReady( false );
    aisExtendedClassBCsPositionReportMessageData1->SetAssigned( false );
    aisExtendedClassBCsPositionReportMessageData1->SetSpare( 939581451L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisExtendedClassBCsPositionReportMessageData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisExtendedClassBCsPositionReportMessageData2 = std::reinterpret_pointer_cast<AisExtendedClassBCsPositionReportMessageData>( ReadDataFrom( source ) );
    bool equal = aisExtendedClassBCsPositionReportMessageData2->IsEqualTo( *aisExtendedClassBCsPositionReportMessageData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisInterrogationMessageDataSerializationTest
BOOST_AUTO_TEST_CASE( AisInterrogationMessageDataSerializationTest )
{
    auto aisInterrogationMessageData1 = std::make_shared<AisInterrogationMessageData>( );
    aisInterrogationMessageData1->SetId( Guid( L"{E8E82CCD-52E4-6679-669E-4A27171734B3}" ) );
    aisInterrogationMessageData1->SetRowVersion( 7384024207164189901LL );
    aisInterrogationMessageData1->SetAisTransceiver( Guid( L"{E8E82CCD-52E4-6679-669E-4A27171734B3}" ) );
    aisInterrogationMessageData1->SetReceivedTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisInterrogationMessageData1->SetMessageSequenceNumber( 7384024207164189901LL );
    aisInterrogationMessageData1->SetRepeat( -387437363L );
    aisInterrogationMessageData1->SetMmsi( Guid( L"{E8E82CCD-52E4-6679-669E-4A27171734B3}" ) );
    aisInterrogationMessageData1->SetInterrogatedMmsi( Guid( L"{E8E82CCD-52E4-6679-669E-4A27171734B3}" ) );
    aisInterrogationMessageData1->SetFirstMessageType( AisMessageType::SafetyRelatedBroadcastMessage );
    aisInterrogationMessageData1->SetFirstSlotOffset( -387437363L );
    aisInterrogationMessageData1->SetSecondMessageType( AisMessageType::SafetyRelatedBroadcastMessage );
    aisInterrogationMessageData1->SetSecondSlotOffset( -387437363L );
    aisInterrogationMessageData1->SetSecondStationInterrogationMmsi( Guid( L"{E8E82CCD-52E4-6679-669E-4A27171734B3}" ) );
    aisInterrogationMessageData1->SetSecondStationFirstMessageType( AisMessageType::SafetyRelatedBroadcastMessage );
    aisInterrogationMessageData1->SetSecondStationFirstSlotOffset( -387437363L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisInterrogationMessageData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisInterrogationMessageData2 = std::reinterpret_pointer_cast<AisInterrogationMessageData>( ReadDataFrom( source ) );
    bool equal = aisInterrogationMessageData2->IsEqualTo( *aisInterrogationMessageData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisPositionReportClassAAssignedScheduleMessageDataSerializationTest
BOOST_AUTO_TEST_CASE( AisPositionReportClassAAssignedScheduleMessageDataSerializationTest )
{
    auto aisPositionReportClassAAssignedScheduleMessageData1 = std::make_shared<AisPositionReportClassAAssignedScheduleMessageData>( );
    aisPositionReportClassAAssignedScheduleMessageData1->SetId( Guid( L"{CA9F2595-C836-B10F-8DF0-136C53F9A4A9}" ) );
    aisPositionReportClassAAssignedScheduleMessageData1->SetRowVersion( -5688107666692430443LL );
    aisPositionReportClassAAssignedScheduleMessageData1->SetAisTransceiver( Guid( L"{CA9F2595-C836-B10F-8DF0-136C53F9A4A9}" ) );
    aisPositionReportClassAAssignedScheduleMessageData1->SetReceivedTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisPositionReportClassAAssignedScheduleMessageData1->SetMessageSequenceNumber( -5688107666692430443LL );
    aisPositionReportClassAAssignedScheduleMessageData1->SetRepeat( -895539819L );
    aisPositionReportClassAAssignedScheduleMessageData1->SetMmsi( Guid( L"{CA9F2595-C836-B10F-8DF0-136C53F9A4A9}" ) );
    aisPositionReportClassAAssignedScheduleMessageData1->SetNavigationStatus( NavigationStatus::Moored );
    aisPositionReportClassAAssignedScheduleMessageData1->SetRateOfTurn( -895539819L );
    aisPositionReportClassAAssignedScheduleMessageData1->SetSpeedOverGround( 12758636407017122 );
    aisPositionReportClassAAssignedScheduleMessageData1->SetPositionAccuracy( PositionAccuracy::High );
    aisPositionReportClassAAssignedScheduleMessageData1->SetLongitude( 12758636407017122 );
    aisPositionReportClassAAssignedScheduleMessageData1->SetLatitude( 12758636407017122 );
    aisPositionReportClassAAssignedScheduleMessageData1->SetCourseOverGround( 12758636407017122 );
    aisPositionReportClassAAssignedScheduleMessageData1->SetTrueHeading( -895539819L );
    aisPositionReportClassAAssignedScheduleMessageData1->SetTimestamp( -895539819L );
    aisPositionReportClassAAssignedScheduleMessageData1->SetManeuverIndicator( ManeuverIndicator::NotAvailable );
    aisPositionReportClassAAssignedScheduleMessageData1->SetSpare( -895539819L );
    aisPositionReportClassAAssignedScheduleMessageData1->SetRaim( Raim::InUse );
    aisPositionReportClassAAssignedScheduleMessageData1->SetRadioStatus( -895539819L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisPositionReportClassAAssignedScheduleMessageData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisPositionReportClassAAssignedScheduleMessageData2 = std::reinterpret_pointer_cast<AisPositionReportClassAAssignedScheduleMessageData>( ReadDataFrom( source ) );
    bool equal = aisPositionReportClassAAssignedScheduleMessageData2->IsEqualTo( *aisPositionReportClassAAssignedScheduleMessageData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisPositionReportClassAMessageDataSerializationTest
BOOST_AUTO_TEST_CASE( AisPositionReportClassAMessageDataSerializationTest )
{
    auto aisPositionReportClassAMessageData1 = std::make_shared<AisPositionReportClassAMessageData>( );
    aisPositionReportClassAMessageData1->SetId( Guid( L"{05ACAC97-D62C-C7D9-E39B-6B34A03535E9}" ) );
    aisPositionReportClassAMessageData1->SetRowVersion( -4045967305653572457LL );
    aisPositionReportClassAMessageData1->SetAisTransceiver( Guid( L"{05ACAC97-D62C-C7D9-E39B-6B34A03535E9}" ) );
    aisPositionReportClassAMessageData1->SetReceivedTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisPositionReportClassAMessageData1->SetMessageSequenceNumber( -4045967305653572457LL );
    aisPositionReportClassAMessageData1->SetRepeat( 95202455L );
    aisPositionReportClassAMessageData1->SetMmsi( Guid( L"{05ACAC97-D62C-C7D9-E39B-6B34A03535E9}" ) );
    aisPositionReportClassAMessageData1->SetNavigationStatus( NavigationStatus::EngagedInFishing );
    aisPositionReportClassAMessageData1->SetRateOfTurn( 95202455L );
    aisPositionReportClassAMessageData1->SetSpeedOverGround( 14400776768055980 );
    aisPositionReportClassAMessageData1->SetPositionAccuracy( PositionAccuracy::High );
    aisPositionReportClassAMessageData1->SetLongitude( 14400776768055980 );
    aisPositionReportClassAMessageData1->SetLatitude( 14400776768055980 );
    aisPositionReportClassAMessageData1->SetCourseOverGround( 14400776768055980 );
    aisPositionReportClassAMessageData1->SetTrueHeading( 95202455L );
    aisPositionReportClassAMessageData1->SetTimestamp( 95202455L );
    aisPositionReportClassAMessageData1->SetManeuverIndicator( ManeuverIndicator::NoSpecialManeuver );
    aisPositionReportClassAMessageData1->SetSpare( 95202455L );
    aisPositionReportClassAMessageData1->SetRaim( Raim::InUse );
    aisPositionReportClassAMessageData1->SetRadioStatus( 95202455L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisPositionReportClassAMessageData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisPositionReportClassAMessageData2 = std::reinterpret_pointer_cast<AisPositionReportClassAMessageData>( ReadDataFrom( source ) );
    bool equal = aisPositionReportClassAMessageData2->IsEqualTo( *aisPositionReportClassAMessageData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisPositionReportClassAResponseToInterrogationMessageDataSerializationTest
BOOST_AUTO_TEST_CASE( AisPositionReportClassAResponseToInterrogationMessageDataSerializationTest )
{
    auto aisPositionReportClassAResponseToInterrogationMessageData1 = std::make_shared<AisPositionReportClassAResponseToInterrogationMessageData>( );
    aisPositionReportClassAResponseToInterrogationMessageData1->SetId( Guid( L"{D9584796-610C-ED40-B702-86309B1AE269}" ) );
    aisPositionReportClassAResponseToInterrogationMessageData1->SetRowVersion( -1350973180397205610LL );
    aisPositionReportClassAResponseToInterrogationMessageData1->SetAisTransceiver( Guid( L"{D9584796-610C-ED40-B702-86309B1AE269}" ) );
    aisPositionReportClassAResponseToInterrogationMessageData1->SetReceivedTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisPositionReportClassAResponseToInterrogationMessageData1->SetMessageSequenceNumber( -1350973180397205610LL );
    aisPositionReportClassAResponseToInterrogationMessageData1->SetRepeat( -648525930L );
    aisPositionReportClassAResponseToInterrogationMessageData1->SetMmsi( Guid( L"{D9584796-610C-ED40-B702-86309B1AE269}" ) );
    aisPositionReportClassAResponseToInterrogationMessageData1->SetNavigationStatus( NavigationStatus::Aground );
    aisPositionReportClassAResponseToInterrogationMessageData1->SetRateOfTurn( -648525930L );
    aisPositionReportClassAResponseToInterrogationMessageData1->SetSpeedOverGround( 17095770893312346 );
    aisPositionReportClassAResponseToInterrogationMessageData1->SetPositionAccuracy( PositionAccuracy::Low );
    aisPositionReportClassAResponseToInterrogationMessageData1->SetLongitude( 17095770893312346 );
    aisPositionReportClassAResponseToInterrogationMessageData1->SetLatitude( 17095770893312346 );
    aisPositionReportClassAResponseToInterrogationMessageData1->SetCourseOverGround( 17095770893312346 );
    aisPositionReportClassAResponseToInterrogationMessageData1->SetTrueHeading( -648525930L );
    aisPositionReportClassAResponseToInterrogationMessageData1->SetTimestamp( -648525930L );
    aisPositionReportClassAResponseToInterrogationMessageData1->SetManeuverIndicator( ManeuverIndicator::NotAvailable );
    aisPositionReportClassAResponseToInterrogationMessageData1->SetSpare( -648525930L );
    aisPositionReportClassAResponseToInterrogationMessageData1->SetRaim( Raim::NotInUse );
    aisPositionReportClassAResponseToInterrogationMessageData1->SetRadioStatus( -648525930L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisPositionReportClassAResponseToInterrogationMessageData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisPositionReportClassAResponseToInterrogationMessageData2 = std::reinterpret_pointer_cast<AisPositionReportClassAResponseToInterrogationMessageData>( ReadDataFrom( source ) );
    bool equal = aisPositionReportClassAResponseToInterrogationMessageData2->IsEqualTo( *aisPositionReportClassAResponseToInterrogationMessageData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisPositionReportForLongRangeApplicationsMessageDataSerializationTest
BOOST_AUTO_TEST_CASE( AisPositionReportForLongRangeApplicationsMessageDataSerializationTest )
{
    auto aisPositionReportForLongRangeApplicationsMessageData1 = std::make_shared<AisPositionReportForLongRangeApplicationsMessageData>( );
    aisPositionReportForLongRangeApplicationsMessageData1->SetId( Guid( L"{CB0CB752-220B-B92B-9DD4-44D0D330ED4A}" ) );
    aisPositionReportForLongRangeApplicationsMessageData1->SetRowVersion( -5103948318647732398LL );
    aisPositionReportForLongRangeApplicationsMessageData1->SetAisTransceiver( Guid( L"{CB0CB752-220B-B92B-9DD4-44D0D330ED4A}" ) );
    aisPositionReportForLongRangeApplicationsMessageData1->SetReceivedTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisPositionReportForLongRangeApplicationsMessageData1->SetMessageSequenceNumber( -5103948318647732398LL );
    aisPositionReportForLongRangeApplicationsMessageData1->SetRepeat( -888359086L );
    aisPositionReportForLongRangeApplicationsMessageData1->SetMmsi( Guid( L"{CB0CB752-220B-B92B-9DD4-44D0D330ED4A}" ) );
    aisPositionReportForLongRangeApplicationsMessageData1->SetPositionAccuracy( PositionAccuracy::Low );
    aisPositionReportForLongRangeApplicationsMessageData1->SetRaim( Raim::NotInUse );
    aisPositionReportForLongRangeApplicationsMessageData1->SetNavigationStatus( NavigationStatus::NotUnderCommand );
    aisPositionReportForLongRangeApplicationsMessageData1->SetLongitude( 13342795755061820 );
    aisPositionReportForLongRangeApplicationsMessageData1->SetLatitude( 13342795755061820 );
    aisPositionReportForLongRangeApplicationsMessageData1->SetSpeedOverGround( 13342795755061820 );
    aisPositionReportForLongRangeApplicationsMessageData1->SetCourseOverGround( 13342795755061820 );
    aisPositionReportForLongRangeApplicationsMessageData1->SetGnssPositionStatus( GnssPositionStatus::CurrentGnssPosition );
    aisPositionReportForLongRangeApplicationsMessageData1->SetSpare( -888359086L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisPositionReportForLongRangeApplicationsMessageData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisPositionReportForLongRangeApplicationsMessageData2 = std::reinterpret_pointer_cast<AisPositionReportForLongRangeApplicationsMessageData>( ReadDataFrom( source ) );
    bool equal = aisPositionReportForLongRangeApplicationsMessageData2->IsEqualTo( *aisPositionReportForLongRangeApplicationsMessageData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisSafetyRelatedAcknowledgmentMessageDataSerializationTest
BOOST_AUTO_TEST_CASE( AisSafetyRelatedAcknowledgmentMessageDataSerializationTest )
{
    auto aisSafetyRelatedAcknowledgmentMessageData1 = std::make_shared<AisSafetyRelatedAcknowledgmentMessageData>( );
    aisSafetyRelatedAcknowledgmentMessageData1->SetId( Guid( L"{DBA7680C-F9E3-8E3B-71DC-9FC7DBE51630}" ) );
    aisSafetyRelatedAcknowledgmentMessageData1->SetRowVersion( -8197683939659782132LL );
    aisSafetyRelatedAcknowledgmentMessageData1->SetAisTransceiver( Guid( L"{DBA7680C-F9E3-8E3B-71DC-9FC7DBE51630}" ) );
    aisSafetyRelatedAcknowledgmentMessageData1->SetReceivedTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisSafetyRelatedAcknowledgmentMessageData1->SetMessageSequenceNumber( -8197683939659782132LL );
    aisSafetyRelatedAcknowledgmentMessageData1->SetRepeat( -609785844L );
    aisSafetyRelatedAcknowledgmentMessageData1->SetMmsi( Guid( L"{DBA7680C-F9E3-8E3B-71DC-9FC7DBE51630}" ) );
    aisSafetyRelatedAcknowledgmentMessageData1->SetSpare( -609785844L );
    aisSafetyRelatedAcknowledgmentMessageData1->SetSequenceNumber1( -609785844L );
    aisSafetyRelatedAcknowledgmentMessageData1->SetMmsi1( Guid( L"{DBA7680C-F9E3-8E3B-71DC-9FC7DBE51630}" ) );
    aisSafetyRelatedAcknowledgmentMessageData1->SetSequenceNumber2( -609785844L );
    aisSafetyRelatedAcknowledgmentMessageData1->SetMmsi2( Guid( L"{DBA7680C-F9E3-8E3B-71DC-9FC7DBE51630}" ) );
    aisSafetyRelatedAcknowledgmentMessageData1->SetSequenceNumber3( -609785844L );
    aisSafetyRelatedAcknowledgmentMessageData1->SetMmsi3( Guid( L"{DBA7680C-F9E3-8E3B-71DC-9FC7DBE51630}" ) );
    aisSafetyRelatedAcknowledgmentMessageData1->SetSequenceNumber4( -609785844L );
    aisSafetyRelatedAcknowledgmentMessageData1->SetMmsi4( Guid( L"{DBA7680C-F9E3-8E3B-71DC-9FC7DBE51630}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisSafetyRelatedAcknowledgmentMessageData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisSafetyRelatedAcknowledgmentMessageData2 = std::reinterpret_pointer_cast<AisSafetyRelatedAcknowledgmentMessageData>( ReadDataFrom( source ) );
    bool equal = aisSafetyRelatedAcknowledgmentMessageData2->IsEqualTo( *aisSafetyRelatedAcknowledgmentMessageData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisStandardClassBCsPositionReportMessageDataSerializationTest
BOOST_AUTO_TEST_CASE( AisStandardClassBCsPositionReportMessageDataSerializationTest )
{
    auto aisStandardClassBCsPositionReportMessageData1 = std::make_shared<AisStandardClassBCsPositionReportMessageData>( );
    aisStandardClassBCsPositionReportMessageData1->SetId( Guid( L"{DE8F513C-118E-7428-2E14-88717BF18A3C}" ) );
    aisStandardClassBCsPositionReportMessageData1->SetRowVersion( 8369959212785029436LL );
    aisStandardClassBCsPositionReportMessageData1->SetAisTransceiver( Guid( L"{DE8F513C-118E-7428-2E14-88717BF18A3C}" ) );
    aisStandardClassBCsPositionReportMessageData1->SetReceivedTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisStandardClassBCsPositionReportMessageData1->SetMessageSequenceNumber( 8369959212785029436LL );
    aisStandardClassBCsPositionReportMessageData1->SetRepeat( -561032900L );
    aisStandardClassBCsPositionReportMessageData1->SetMmsi( Guid( L"{DE8F513C-118E-7428-2E14-88717BF18A3C}" ) );
    aisStandardClassBCsPositionReportMessageData1->SetReserved( -561032900L );
    aisStandardClassBCsPositionReportMessageData1->SetSpeedOverGround( 8369959212785029 );
    aisStandardClassBCsPositionReportMessageData1->SetPositionAccuracy( PositionAccuracy::Low );
    aisStandardClassBCsPositionReportMessageData1->SetLongitude( 8369959212785029 );
    aisStandardClassBCsPositionReportMessageData1->SetLatitude( 8369959212785029 );
    aisStandardClassBCsPositionReportMessageData1->SetCourseOverGround( 8369959212785029 );
    aisStandardClassBCsPositionReportMessageData1->SetTrueHeading( -561032900L );
    aisStandardClassBCsPositionReportMessageData1->SetTimestamp( -561032900L );
    aisStandardClassBCsPositionReportMessageData1->SetRegionalReserved( -561032900L );
    aisStandardClassBCsPositionReportMessageData1->SetIsCsUnit( false );
    aisStandardClassBCsPositionReportMessageData1->SetHasDisplay( false );
    aisStandardClassBCsPositionReportMessageData1->SetHasDscCapability( false );
    aisStandardClassBCsPositionReportMessageData1->SetBand( false );
    aisStandardClassBCsPositionReportMessageData1->SetCanAcceptMessage22( false );
    aisStandardClassBCsPositionReportMessageData1->SetAssigned( false );
    aisStandardClassBCsPositionReportMessageData1->SetRaim( Raim::NotInUse );
    aisStandardClassBCsPositionReportMessageData1->SetRadioStatus( -561032900L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisStandardClassBCsPositionReportMessageData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisStandardClassBCsPositionReportMessageData2 = std::reinterpret_pointer_cast<AisStandardClassBCsPositionReportMessageData>( ReadDataFrom( source ) );
    bool equal = aisStandardClassBCsPositionReportMessageData2->IsEqualTo( *aisStandardClassBCsPositionReportMessageData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisStandardSarAircraftPositionReportMessageDataSerializationTest
BOOST_AUTO_TEST_CASE( AisStandardSarAircraftPositionReportMessageDataSerializationTest )
{
    auto aisStandardSarAircraftPositionReportMessageData1 = std::make_shared<AisStandardSarAircraftPositionReportMessageData>( );
    aisStandardSarAircraftPositionReportMessageData1->SetId( Guid( L"{41467402-F4D5-7EAD-7EB5-2FAB82622E40}" ) );
    aisStandardSarAircraftPositionReportMessageData1->SetRowVersion( 9128221216510211074LL );
    aisStandardSarAircraftPositionReportMessageData1->SetAisTransceiver( Guid( L"{41467402-F4D5-7EAD-7EB5-2FAB82622E40}" ) );
    aisStandardSarAircraftPositionReportMessageData1->SetReceivedTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisStandardSarAircraftPositionReportMessageData1->SetMessageSequenceNumber( 9128221216510211074LL );
    aisStandardSarAircraftPositionReportMessageData1->SetRepeat( 1095136258L );
    aisStandardSarAircraftPositionReportMessageData1->SetMmsi( Guid( L"{41467402-F4D5-7EAD-7EB5-2FAB82622E40}" ) );
    aisStandardSarAircraftPositionReportMessageData1->SetAltitude( 1095136258L );
    aisStandardSarAircraftPositionReportMessageData1->SetSpeedOverGround( 1095136258L );
    aisStandardSarAircraftPositionReportMessageData1->SetPositionAccuracy( PositionAccuracy::Low );
    aisStandardSarAircraftPositionReportMessageData1->SetLongitude( 9128221216510212 );
    aisStandardSarAircraftPositionReportMessageData1->SetLatitude( 9128221216510212 );
    aisStandardSarAircraftPositionReportMessageData1->SetCourseOverGround( 9128221216510212 );
    aisStandardSarAircraftPositionReportMessageData1->SetTimestamp( 1095136258L );
    aisStandardSarAircraftPositionReportMessageData1->SetReserved( 1095136258L );
    aisStandardSarAircraftPositionReportMessageData1->SetDataTerminalReady( false );
    aisStandardSarAircraftPositionReportMessageData1->SetSpare( 1095136258L );
    aisStandardSarAircraftPositionReportMessageData1->SetAssigned( false );
    aisStandardSarAircraftPositionReportMessageData1->SetRaim( Raim::NotInUse );
    aisStandardSarAircraftPositionReportMessageData1->SetRadioStatus( 1095136258L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisStandardSarAircraftPositionReportMessageData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisStandardSarAircraftPositionReportMessageData2 = std::reinterpret_pointer_cast<AisStandardSarAircraftPositionReportMessageData>( ReadDataFrom( source ) );
    bool equal = aisStandardSarAircraftPositionReportMessageData2->IsEqualTo( *aisStandardSarAircraftPositionReportMessageData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisStaticAndVoyageRelatedDataMessageDataSerializationTest
BOOST_AUTO_TEST_CASE( AisStaticAndVoyageRelatedDataMessageDataSerializationTest )
{
    auto aisStaticAndVoyageRelatedDataMessageData1 = std::make_shared<AisStaticAndVoyageRelatedDataMessageData>( );
    aisStaticAndVoyageRelatedDataMessageData1->SetId( Guid( L"{FE446502-C000-ADA7-B5E5-03007F22A640}" ) );
    aisStaticAndVoyageRelatedDataMessageData1->SetRowVersion( -5933562873538910974LL );
    aisStaticAndVoyageRelatedDataMessageData1->SetAisTransceiver( Guid( L"{FE446502-C000-ADA7-B5E5-03007F22A640}" ) );
    aisStaticAndVoyageRelatedDataMessageData1->SetReceivedTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisStaticAndVoyageRelatedDataMessageData1->SetMessageSequenceNumber( -5933562873538910974LL );
    aisStaticAndVoyageRelatedDataMessageData1->SetRepeat( -29072126L );
    aisStaticAndVoyageRelatedDataMessageData1->SetMmsi( Guid( L"{FE446502-C000-ADA7-B5E5-03007F22A640}" ) );
    aisStaticAndVoyageRelatedDataMessageData1->SetAisVersion( -29072126L );
    aisStaticAndVoyageRelatedDataMessageData1->SetImoNumber( Guid( L"{FE446502-C000-ADA7-B5E5-03007F22A640}" ) );
    aisStaticAndVoyageRelatedDataMessageData1->SetCallsign( Guid( L"{FE446502-C000-ADA7-B5E5-03007F22A640}" ) );
    aisStaticAndVoyageRelatedDataMessageData1->SetShipName( Guid( L"{FE446502-C000-ADA7-B5E5-03007F22A640}" ) );
    aisStaticAndVoyageRelatedDataMessageData1->SetShipType( ShipType::WingInGroundReserved4 );
    aisStaticAndVoyageRelatedDataMessageData1->SetDimensionToBow( -29072126L );
    aisStaticAndVoyageRelatedDataMessageData1->SetDimensionToStern( -29072126L );
    aisStaticAndVoyageRelatedDataMessageData1->SetDimensionToPort( -29072126L );
    aisStaticAndVoyageRelatedDataMessageData1->SetDimensionToStarboard( -29072126L );
    aisStaticAndVoyageRelatedDataMessageData1->SetPositionFixType( PositionFixType::Glonass );
    aisStaticAndVoyageRelatedDataMessageData1->SetEstimatedTimeOfArrival( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisStaticAndVoyageRelatedDataMessageData1->SetDraught( 12513181200170642 );
    aisStaticAndVoyageRelatedDataMessageData1->SetDestination( L"Destination" );
    aisStaticAndVoyageRelatedDataMessageData1->SetDataTerminalReady( false );
    aisStaticAndVoyageRelatedDataMessageData1->SetSpare( -29072126L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisStaticAndVoyageRelatedDataMessageData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisStaticAndVoyageRelatedDataMessageData2 = std::reinterpret_pointer_cast<AisStaticAndVoyageRelatedDataMessageData>( ReadDataFrom( source ) );
    bool equal = aisStaticAndVoyageRelatedDataMessageData2->IsEqualTo( *aisStaticAndVoyageRelatedDataMessageData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisStaticDataReportMessageDataSerializationTest
BOOST_AUTO_TEST_CASE( AisStaticDataReportMessageDataSerializationTest )
{
    auto aisStaticDataReportMessageData1 = std::make_shared<AisStaticDataReportMessageData>( );
    aisStaticDataReportMessageData1->SetId( Guid( L"{69972CB9-08CA-C920-9304-105396E9349D}" ) );
    aisStaticDataReportMessageData1->SetRowVersion( -3954150807383364423LL );
    aisStaticDataReportMessageData1->SetAisTransceiver( Guid( L"{69972CB9-08CA-C920-9304-105396E9349D}" ) );
    aisStaticDataReportMessageData1->SetReceivedTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisStaticDataReportMessageData1->SetMessageSequenceNumber( -3954150807383364423LL );
    aisStaticDataReportMessageData1->SetRepeat( 1771515065L );
    aisStaticDataReportMessageData1->SetMmsi( Guid( L"{69972CB9-08CA-C920-9304-105396E9349D}" ) );
    aisStaticDataReportMessageData1->SetPartNumber( 1771515065L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisStaticDataReportMessageData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisStaticDataReportMessageData2 = std::reinterpret_pointer_cast<AisStaticDataReportMessageData>( ReadDataFrom( source ) );
    bool equal = aisStaticDataReportMessageData2->IsEqualTo( *aisStaticDataReportMessageData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisStaticDataReportPartAMessageDataSerializationTest
BOOST_AUTO_TEST_CASE( AisStaticDataReportPartAMessageDataSerializationTest )
{
    auto aisStaticDataReportPartAMessageData1 = std::make_shared<AisStaticDataReportPartAMessageData>( );
    aisStaticDataReportPartAMessageData1->SetId( Guid( L"{CA38BF53-B49F-618C-8631-2DF9531CFDCA}" ) );
    aisStaticDataReportPartAMessageData1->SetRowVersion( 7029191716804018003LL );
    aisStaticDataReportPartAMessageData1->SetAisTransceiver( Guid( L"{CA38BF53-B49F-618C-8631-2DF9531CFDCA}" ) );
    aisStaticDataReportPartAMessageData1->SetReceivedTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisStaticDataReportPartAMessageData1->SetMessageSequenceNumber( 7029191716804018003LL );
    aisStaticDataReportPartAMessageData1->SetRepeat( -902250669L );
    aisStaticDataReportPartAMessageData1->SetMmsi( Guid( L"{CA38BF53-B49F-618C-8631-2DF9531CFDCA}" ) );
    aisStaticDataReportPartAMessageData1->SetPartNumber( -902250669L );
    aisStaticDataReportPartAMessageData1->SetShipName( Guid( L"{CA38BF53-B49F-618C-8631-2DF9531CFDCA}" ) );
    aisStaticDataReportPartAMessageData1->SetSpare( -902250669L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisStaticDataReportPartAMessageData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisStaticDataReportPartAMessageData2 = std::reinterpret_pointer_cast<AisStaticDataReportPartAMessageData>( ReadDataFrom( source ) );
    bool equal = aisStaticDataReportPartAMessageData2->IsEqualTo( *aisStaticDataReportPartAMessageData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisStaticDataReportPartBMessageDataSerializationTest
BOOST_AUTO_TEST_CASE( AisStaticDataReportPartBMessageDataSerializationTest )
{
    auto aisStaticDataReportPartBMessageData1 = std::make_shared<AisStaticDataReportPartBMessageData>( );
    aisStaticDataReportPartBMessageData1->SetId( Guid( L"{F5627DB0-8BA6-0BD2-D04B-D165AF46BE0D}" ) );
    aisStaticDataReportPartBMessageData1->SetRowVersion( 851896828724149680LL );
    aisStaticDataReportPartBMessageData1->SetAisTransceiver( Guid( L"{F5627DB0-8BA6-0BD2-D04B-D165AF46BE0D}" ) );
    aisStaticDataReportPartBMessageData1->SetReceivedTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisStaticDataReportPartBMessageData1->SetMessageSequenceNumber( 851896828724149680LL );
    aisStaticDataReportPartBMessageData1->SetRepeat( -178094672L );
    aisStaticDataReportPartBMessageData1->SetMmsi( Guid( L"{F5627DB0-8BA6-0BD2-D04B-D165AF46BE0D}" ) );
    aisStaticDataReportPartBMessageData1->SetPartNumber( -178094672L );
    aisStaticDataReportPartBMessageData1->SetShipType( ShipType::HighSpeedCraftHazardousCategoryC );
    aisStaticDataReportPartBMessageData1->SetVendorId( L"VendorId" );
    aisStaticDataReportPartBMessageData1->SetUnitModelCode( -178094672L );
    aisStaticDataReportPartBMessageData1->SetSerialNumber( -178094672L );
    aisStaticDataReportPartBMessageData1->SetCallsign( Guid( L"{F5627DB0-8BA6-0BD2-D04B-D165AF46BE0D}" ) );
    aisStaticDataReportPartBMessageData1->SetDimensionToBow( -178094672L );
    aisStaticDataReportPartBMessageData1->SetDimensionToStern( -178094672L );
    aisStaticDataReportPartBMessageData1->SetDimensionToPort( -178094672L );
    aisStaticDataReportPartBMessageData1->SetDimensionToStarboard( -178094672L );
    aisStaticDataReportPartBMessageData1->SetMothershipMmsi( Guid( L"{F5627DB0-8BA6-0BD2-D04B-D165AF46BE0D}" ) );
    aisStaticDataReportPartBMessageData1->SetPositionFixType( PositionFixType::Undefined1 );
    aisStaticDataReportPartBMessageData1->SetSpare( -178094672L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisStaticDataReportPartBMessageData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisStaticDataReportPartBMessageData2 = std::reinterpret_pointer_cast<AisStaticDataReportPartBMessageData>( ReadDataFrom( source ) );
    bool equal = aisStaticDataReportPartBMessageData2->IsEqualTo( *aisStaticDataReportPartBMessageData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisUtcAndDateInquiryMessageDataSerializationTest
BOOST_AUTO_TEST_CASE( AisUtcAndDateInquiryMessageDataSerializationTest )
{
    auto aisUtcAndDateInquiryMessageData1 = std::make_shared<AisUtcAndDateInquiryMessageData>( );
    aisUtcAndDateInquiryMessageData1->SetId( Guid( L"{CA0D5117-9AF8-676C-E636-591F53B08AE8}" ) );
    aisUtcAndDateInquiryMessageData1->SetRowVersion( 7452501876723765527LL );
    aisUtcAndDateInquiryMessageData1->SetAisTransceiver( Guid( L"{CA0D5117-9AF8-676C-E636-591F53B08AE8}" ) );
    aisUtcAndDateInquiryMessageData1->SetReceivedTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisUtcAndDateInquiryMessageData1->SetMessageSequenceNumber( 7452501876723765527LL );
    aisUtcAndDateInquiryMessageData1->SetRepeat( -905096937L );
    aisUtcAndDateInquiryMessageData1->SetMmsi( Guid( L"{CA0D5117-9AF8-676C-E636-591F53B08AE8}" ) );
    aisUtcAndDateInquiryMessageData1->SetSpare1( -905096937L );
    aisUtcAndDateInquiryMessageData1->SetDestinationMmsi( -905096937L );
    aisUtcAndDateInquiryMessageData1->SetSpare2( -905096937L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisUtcAndDateInquiryMessageData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisUtcAndDateInquiryMessageData2 = std::reinterpret_pointer_cast<AisUtcAndDateInquiryMessageData>( ReadDataFrom( source ) );
    bool equal = aisUtcAndDateInquiryMessageData2->IsEqualTo( *aisUtcAndDateInquiryMessageData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisUtcAndDateResponseMessageDataSerializationTest
BOOST_AUTO_TEST_CASE( AisUtcAndDateResponseMessageDataSerializationTest )
{
    auto aisUtcAndDateResponseMessageData1 = std::make_shared<AisUtcAndDateResponseMessageData>( );
    aisUtcAndDateResponseMessageData1->SetId( Guid( L"{7ED5439C-5B10-6A85-56A1-DA087EABC239}" ) );
    aisUtcAndDateResponseMessageData1->SetRowVersion( 7675641266328388508LL );
    aisUtcAndDateResponseMessageData1->SetAisTransceiver( Guid( L"{7ED5439C-5B10-6A85-56A1-DA087EABC239}" ) );
    aisUtcAndDateResponseMessageData1->SetReceivedTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisUtcAndDateResponseMessageData1->SetMessageSequenceNumber( 7675641266328388508LL );
    aisUtcAndDateResponseMessageData1->SetRepeat( 2127905692L );
    aisUtcAndDateResponseMessageData1->SetMmsi( Guid( L"{7ED5439C-5B10-6A85-56A1-DA087EABC239}" ) );
    aisUtcAndDateResponseMessageData1->SetDatetime( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisUtcAndDateResponseMessageData1->SetPositionAccuracy( PositionAccuracy::Low );
    aisUtcAndDateResponseMessageData1->SetLongitude( 7675641266328389 );
    aisUtcAndDateResponseMessageData1->SetLatitude( 7675641266328389 );
    aisUtcAndDateResponseMessageData1->SetPositionFixType( PositionFixType::Galileo );
    aisUtcAndDateResponseMessageData1->SetSpare( 2127905692L );
    aisUtcAndDateResponseMessageData1->SetRaim( Raim::NotInUse );
    aisUtcAndDateResponseMessageData1->SetRadioStatus( 2127905692L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisUtcAndDateResponseMessageData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisUtcAndDateResponseMessageData2 = std::reinterpret_pointer_cast<AisUtcAndDateResponseMessageData>( ReadDataFrom( source ) );
    bool equal = aisUtcAndDateResponseMessageData2->IsEqualTo( *aisUtcAndDateResponseMessageData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisTransceiverCommandDataSerializationTest
BOOST_AUTO_TEST_CASE( AisTransceiverCommandDataSerializationTest )
{
    auto aisTransceiverCommandData1 = std::make_shared<AisTransceiverCommandData>( );
    aisTransceiverCommandData1->SetId( Guid( L"{35262C23-D4CA-1A35-58AC-2B53AC6434C4}" ) );
    aisTransceiverCommandData1->SetRowVersion( 1888649583691967523LL );
    aisTransceiverCommandData1->SetAisTransceiver( Guid( L"{35262C23-D4CA-1A35-58AC-2B53AC6434C4}" ) );
    aisTransceiverCommandData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisTransceiverCommandData1->SetDeviceCommandSourceType( DeviceCommandSourceType::Source );
    aisTransceiverCommandData1->SetDeviceCommandSourceId( Guid( L"{35262C23-D4CA-1A35-58AC-2B53AC6434C4}" ) );
    aisTransceiverCommandData1->SetReply( Guid( L"{35262C23-D4CA-1A35-58AC-2B53AC6434C4}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisTransceiverCommandData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisTransceiverCommandData2 = std::reinterpret_pointer_cast<AisTransceiverCommandData>( ReadDataFrom( source ) );
    bool equal = aisTransceiverCommandData2->IsEqualTo( *aisTransceiverCommandData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisTransceiverCommandReplyDataSerializationTest
BOOST_AUTO_TEST_CASE( AisTransceiverCommandReplyDataSerializationTest )
{
    auto aisTransceiverCommandReplyData1 = std::make_shared<AisTransceiverCommandReplyData>( );
    aisTransceiverCommandReplyData1->SetId( Guid( L"{559D54D3-E231-2699-6499-478CAAB92ACB}" ) );
    aisTransceiverCommandReplyData1->SetRowVersion( 2781502946395641043LL );
    aisTransceiverCommandReplyData1->SetAisTransceiver( Guid( L"{559D54D3-E231-2699-6499-478CAAB92ACB}" ) );
    aisTransceiverCommandReplyData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisTransceiverCommandReplyData1->SetCommand( Guid( L"{559D54D3-E231-2699-6499-478CAAB92ACB}" ) );
    aisTransceiverCommandReplyData1->SetStatus( DeviceCommandReplyStatus::Error );
    aisTransceiverCommandReplyData1->SetMessage( L"Message" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisTransceiverCommandReplyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisTransceiverCommandReplyData2 = std::reinterpret_pointer_cast<AisTransceiverCommandReplyData>( ReadDataFrom( source ) );
    bool equal = aisTransceiverCommandReplyData2->IsEqualTo( *aisTransceiverCommandReplyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisTransceiverConfigurationDataSerializationTest
BOOST_AUTO_TEST_CASE( AisTransceiverConfigurationDataSerializationTest )
{
    auto aisTransceiverConfigurationData1 = std::make_shared<AisTransceiverConfigurationData>( );
    aisTransceiverConfigurationData1->SetId( Guid( L"{3954E528-AC3F-B3E1-CD87-35FC9C2AA714}" ) );
    aisTransceiverConfigurationData1->SetRowVersion( -5484913483615771352LL );
    aisTransceiverConfigurationData1->SetAisTransceiver( Guid( L"{3954E528-AC3F-B3E1-CD87-35FC9C2AA714}" ) );
    aisTransceiverConfigurationData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisTransceiverConfigurationData1->SetUserName( L"UserName" );
    aisTransceiverConfigurationData1->SetPassword( L"Password" );
    aisTransceiverConfigurationData1->SetLatitude( 12961830590093780 );
    aisTransceiverConfigurationData1->SetLongitude( 12961830590093780 );
    aisTransceiverConfigurationData1->SetAisProviderLoginURL( L"AisProviderLoginURL" );
    aisTransceiverConfigurationData1->SetComPort( L"ComPort" );
    aisTransceiverConfigurationData1->SetBaudRate( 961865000L );
    aisTransceiverConfigurationData1->SetFilterByArea( false );
    aisTransceiverConfigurationData1->SetUpperLeftCornerLatitude( 12961830590093780 );
    aisTransceiverConfigurationData1->SetUpperLeftCornerLongitude( 12961830590093780 );
    aisTransceiverConfigurationData1->SetBottomRightCornerLatitude( 12961830590093780 );
    aisTransceiverConfigurationData1->SetBottomRightCornerLongitude( 12961830590093780 );
    aisTransceiverConfigurationData1->SetAisProviderIPAddress( L"AisProviderIPAddress" );
    aisTransceiverConfigurationData1->SetAisProviderPort( 961865000L );
    aisTransceiverConfigurationData1->SetUseLogin( false );
    aisTransceiverConfigurationData1->SetAisProviderLoginPort( 961865000L );
    aisTransceiverConfigurationData1->SetCanSendAISMessage( false );
    aisTransceiverConfigurationData1->SetTextMessageHeader( L"TextMessageHeader" );
    aisTransceiverConfigurationData1->SetUrls( L"Urls" );
    aisTransceiverConfigurationData1->SetUdpPort( 961865000L );
    aisTransceiverConfigurationData1->SetConnectionType( AisTransceiverConnectionType::Unknown );
    aisTransceiverConfigurationData1->SetEnableRefreshAidToNavigationIn30sec( false );
    aisTransceiverConfigurationData1->SetEnableAidToNavigationFromFile( false );
    aisTransceiverConfigurationData1->SetAidToNavigationHeader( L"AidToNavigationHeader" );
    aisTransceiverConfigurationData1->SetSendingMMSI( false );
    aisTransceiverConfigurationData1->SetSourceUpdateRate( 961865000L );
    aisTransceiverConfigurationData1->SetEnableRefreshStayingStillTargetIn30sec( false );
    aisTransceiverConfigurationData1->SetExcludeSendAisBaseStation( L"ExcludeSendAisBaseStation" );
    aisTransceiverConfigurationData1->SetExcludeSendAisA( L"ExcludeSendAisA" );
    aisTransceiverConfigurationData1->SetEnableSendBaseStationAlarms( false );
    aisTransceiverConfigurationData1->SetAisWebConfig( L"AisWebConfig" );
    aisTransceiverConfigurationData1->SetStoreReceivedSentences( false );
    aisTransceiverConfigurationData1->SetStoreSentMessages( false );
    aisTransceiverConfigurationData1->SetStoreUnsentMessages( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisTransceiverConfigurationData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisTransceiverConfigurationData2 = std::reinterpret_pointer_cast<AisTransceiverConfigurationData>( ReadDataFrom( source ) );
    bool equal = aisTransceiverConfigurationData2->IsEqualTo( *aisTransceiverConfigurationData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisTransceiverRawMessageDataSerializationTest
BOOST_AUTO_TEST_CASE( AisTransceiverRawMessageDataSerializationTest )
{
    auto aisTransceiverRawMessageData1 = std::make_shared<AisTransceiverRawMessageData>( );
    aisTransceiverRawMessageData1->SetId( Guid( L"{087208FB-B700-5AA6-5A65-ED00104E10DF}" ) );
    aisTransceiverRawMessageData1->SetRowVersion( 6532109520317057275LL );
    aisTransceiverRawMessageData1->SetAisTransceiver( Guid( L"{087208FB-B700-5AA6-5A65-ED00104E10DF}" ) );
    aisTransceiverRawMessageData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisTransceiverRawMessageData1->SetIsSent( false );
    aisTransceiverRawMessageData1->SetMessage( L"Message" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisTransceiverRawMessageData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisTransceiverRawMessageData2 = std::reinterpret_pointer_cast<AisTransceiverRawMessageData>( ReadDataFrom( source ) );
    bool equal = aisTransceiverRawMessageData2->IsEqualTo( *aisTransceiverRawMessageData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisTransceiverRawSentenceDataSerializationTest
BOOST_AUTO_TEST_CASE( AisTransceiverRawSentenceDataSerializationTest )
{
    auto aisTransceiverRawSentenceData1 = std::make_shared<AisTransceiverRawSentenceData>( );
    aisTransceiverRawSentenceData1->SetId( Guid( L"{886FF70A-E2E9-BCCB-3DD3-479711F6EF50}" ) );
    aisTransceiverRawSentenceData1->SetRowVersion( -4842527481662540022LL );
    aisTransceiverRawSentenceData1->SetAisTransceiver( Guid( L"{886FF70A-E2E9-BCCB-3DD3-479711F6EF50}" ) );
    aisTransceiverRawSentenceData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    aisTransceiverRawSentenceData1->SetSentence( L"Sentence" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisTransceiverRawSentenceData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisTransceiverRawSentenceData2 = std::reinterpret_pointer_cast<AisTransceiverRawSentenceData>( ReadDataFrom( source ) );
    bool equal = aisTransceiverRawSentenceData2->IsEqualTo( *aisTransceiverRawSentenceData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AlarmStateChangeDataSerializationTest
BOOST_AUTO_TEST_CASE( AlarmStateChangeDataSerializationTest )
{
    auto alarmStateChangeData1 = std::make_shared<AlarmStateChangeData>( );
    alarmStateChangeData1->SetId( Guid( L"{86072ECE-CF2F-0DB4-B02D-F3F461E07473}" ) );
    alarmStateChangeData1->SetRowVersion( 987642021320011470LL );
    alarmStateChangeData1->SetAlarm( Guid( L"{86072ECE-CF2F-0DB4-B02D-F3F461E07473}" ) );
    alarmStateChangeData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    alarmStateChangeData1->SetState( AlarmState::Cleared );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *alarmStateChangeData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto alarmStateChangeData2 = std::reinterpret_pointer_cast<AlarmStateChangeData>( ReadDataFrom( source ) );
    bool equal = alarmStateChangeData2->IsEqualTo( *alarmStateChangeData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BaseStationTypeDataSerializationTest
BOOST_AUTO_TEST_CASE( BaseStationTypeDataSerializationTest )
{
    auto baseStationTypeData1 = std::make_shared<BaseStationTypeData>( );
    baseStationTypeData1->SetId( Guid( L"{E461D07A-F7B7-0F84-F021-EFED27860B5E}" ) );
    baseStationTypeData1->SetRowVersion( 1118290976677417082LL );
    baseStationTypeData1->SetName( L"Name" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *baseStationTypeData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto baseStationTypeData2 = std::reinterpret_pointer_cast<BaseStationTypeData>( ReadDataFrom( source ) );
    bool equal = baseStationTypeData2->IsEqualTo( *baseStationTypeData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BinaryTimeseriesValueDataSerializationTest
BOOST_AUTO_TEST_CASE( BinaryTimeseriesValueDataSerializationTest )
{
    auto binaryTimeseriesValueData1 = std::make_shared<BinaryTimeseriesValueData>( );
    binaryTimeseriesValueData1->SetId( Guid( L"{592D1EA9-0849-9318-C918-10929AB47895}" ) );
    binaryTimeseriesValueData1->SetRowVersion( -7847513239571325271LL );
    binaryTimeseriesValueData1->SetTimeseries( Guid( L"{592D1EA9-0849-9318-C918-10929AB47895}" ) );
    binaryTimeseriesValueData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    binaryTimeseriesValueData1->SetValue( { {'V','a','l','u','e'} } );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *binaryTimeseriesValueData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto binaryTimeseriesValueData2 = std::reinterpret_pointer_cast<BinaryTimeseriesValueData>( ReadDataFrom( source ) );
    bool equal = binaryTimeseriesValueData2->IsEqualTo( *binaryTimeseriesValueData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BookmarkDataSerializationTest
BOOST_AUTO_TEST_CASE( BookmarkDataSerializationTest )
{
    auto bookmarkData1 = std::make_shared<BookmarkData>( );
    bookmarkData1->SetId( Guid( L"{652F1D55-1FDD-E0C0-0703-F8BBA6F4B8AA}" ) );
    bookmarkData1->SetRowVersion( -2251764777939428011LL );
    bookmarkData1->SetView( Guid( L"{652F1D55-1FDD-E0C0-0703-F8BBA6F4B8AA}" ) );
    bookmarkData1->SetName( L"Name" );
    bookmarkData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    bookmarkData1->SetLatitude( 16194979295770124 );
    bookmarkData1->SetLongitude( 16194979295770124 );
    bookmarkData1->SetZoomLevel( 16194979295770124 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *bookmarkData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto bookmarkData2 = std::reinterpret_pointer_cast<BookmarkData>( ReadDataFrom( source ) );
    bool equal = bookmarkData2->IsEqualTo( *bookmarkData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BooleanTimeseriesValueDataSerializationTest
BOOST_AUTO_TEST_CASE( BooleanTimeseriesValueDataSerializationTest )
{
    auto booleanTimeseriesValueData1 = std::make_shared<BooleanTimeseriesValueData>( );
    booleanTimeseriesValueData1->SetId( Guid( L"{F3919E41-40E5-BAB5-5DAD-02A7CF897982}" ) );
    booleanTimeseriesValueData1->SetRowVersion( -4993013255492231615LL );
    booleanTimeseriesValueData1->SetTimeseries( Guid( L"{F3919E41-40E5-BAB5-5DAD-02A7CF897982}" ) );
    booleanTimeseriesValueData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    booleanTimeseriesValueData1->SetValue( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *booleanTimeseriesValueData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto booleanTimeseriesValueData2 = std::reinterpret_pointer_cast<BooleanTimeseriesValueData>( ReadDataFrom( source ) );
    bool equal = booleanTimeseriesValueData2->IsEqualTo( *booleanTimeseriesValueData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ByteTimeseriesValueDataSerializationTest
BOOST_AUTO_TEST_CASE( ByteTimeseriesValueDataSerializationTest )
{
    auto byteTimeseriesValueData1 = std::make_shared<ByteTimeseriesValueData>( );
    byteTimeseriesValueData1->SetId( Guid( L"{E106F150-2900-1D63-B8C6-940087608F0A}" ) );
    byteTimeseriesValueData1->SetRowVersion( 2117581333546332496LL );
    byteTimeseriesValueData1->SetTimeseries( Guid( L"{E106F150-2900-1D63-B8C6-940087608F0A}" ) );
    byteTimeseriesValueData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    byteTimeseriesValueData1->SetValue( 80 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *byteTimeseriesValueData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto byteTimeseriesValueData2 = std::reinterpret_pointer_cast<ByteTimeseriesValueData>( ReadDataFrom( source ) );
    bool equal = byteTimeseriesValueData2->IsEqualTo( *byteTimeseriesValueData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandDataSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandDataSerializationTest )
{
    auto cameraCommandData1 = std::make_shared<CameraCommandData>( );
    cameraCommandData1->SetId( Guid( L"{664197EB-56C6-2117-84E8-6A636682E9D7}" ) );
    cameraCommandData1->SetRowVersion( 2384469937835055083LL );
    cameraCommandData1->SetCamera( Guid( L"{664197EB-56C6-2117-84E8-6A636682E9D7}" ) );
    cameraCommandData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    cameraCommandData1->SetDeviceCommandSourceType( DeviceCommandSourceType::Source );
    cameraCommandData1->SetDeviceCommandSourceId( Guid( L"{664197EB-56C6-2117-84E8-6A636682E9D7}" ) );
    cameraCommandData1->SetReply( Guid( L"{664197EB-56C6-2117-84E8-6A636682E9D7}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandData2 = std::reinterpret_pointer_cast<CameraCommandData>( ReadDataFrom( source ) );
    bool equal = cameraCommandData2->IsEqualTo( *cameraCommandData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandAbsoluteMoveDataSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandAbsoluteMoveDataSerializationTest )
{
    auto cameraCommandAbsoluteMoveData1 = std::make_shared<CameraCommandAbsoluteMoveData>( );
    cameraCommandAbsoluteMoveData1->SetId( Guid( L"{B0F47B16-0F88-634E-C672-F0110D2FDE68}" ) );
    cameraCommandAbsoluteMoveData1->SetRowVersion( 7155673937697078038LL );
    cameraCommandAbsoluteMoveData1->SetCamera( Guid( L"{B0F47B16-0F88-634E-C672-F0110D2FDE68}" ) );
    cameraCommandAbsoluteMoveData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    cameraCommandAbsoluteMoveData1->SetDeviceCommandSourceType( DeviceCommandSourceType::Device );
    cameraCommandAbsoluteMoveData1->SetDeviceCommandSourceId( Guid( L"{B0F47B16-0F88-634E-C672-F0110D2FDE68}" ) );
    cameraCommandAbsoluteMoveData1->SetReply( Guid( L"{B0F47B16-0F88-634E-C672-F0110D2FDE68}" ) );
    cameraCommandAbsoluteMoveData1->SetPositionPanTiltMode( CameraPanTiltMode::Angular );
    cameraCommandAbsoluteMoveData1->SetPanAngle( 7155673937697078 );
    cameraCommandAbsoluteMoveData1->SetTiltAngle( 7155673937697078 );
    cameraCommandAbsoluteMoveData1->SetPositionFocalLengthMode( CameraFocalLengthMode::Millimeter );
    cameraCommandAbsoluteMoveData1->SetFocalLength( 7155673937697078 );
    cameraCommandAbsoluteMoveData1->SetSpeedPanTiltMode( CameraPanTiltMode::Angular );
    cameraCommandAbsoluteMoveData1->SetPanSpeed( 7155673937697078 );
    cameraCommandAbsoluteMoveData1->SetTiltSpeed( 7155673937697078 );
    cameraCommandAbsoluteMoveData1->SetSpeedFocalLengthMode( CameraFocalLengthMode::Millimeter );
    cameraCommandAbsoluteMoveData1->SetZoomSpeed( 7155673937697078 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandAbsoluteMoveData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandAbsoluteMoveData2 = std::reinterpret_pointer_cast<CameraCommandAbsoluteMoveData>( ReadDataFrom( source ) );
    bool equal = cameraCommandAbsoluteMoveData2->IsEqualTo( *cameraCommandAbsoluteMoveData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandAdjustPanTiltZoomDataSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandAdjustPanTiltZoomDataSerializationTest )
{
    auto cameraCommandAdjustPanTiltZoomData1 = std::make_shared<CameraCommandAdjustPanTiltZoomData>( );
    cameraCommandAdjustPanTiltZoomData1->SetId( Guid( L"{C14A2079-48BB-058C-A031-12DD8352049E}" ) );
    cameraCommandAdjustPanTiltZoomData1->SetRowVersion( 399774438168076409LL );
    cameraCommandAdjustPanTiltZoomData1->SetCamera( Guid( L"{C14A2079-48BB-058C-A031-12DD8352049E}" ) );
    cameraCommandAdjustPanTiltZoomData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    cameraCommandAdjustPanTiltZoomData1->SetDeviceCommandSourceType( DeviceCommandSourceType::Session );
    cameraCommandAdjustPanTiltZoomData1->SetDeviceCommandSourceId( Guid( L"{C14A2079-48BB-058C-A031-12DD8352049E}" ) );
    cameraCommandAdjustPanTiltZoomData1->SetReply( Guid( L"{C14A2079-48BB-058C-A031-12DD8352049E}" ) );
    cameraCommandAdjustPanTiltZoomData1->SetX( 399774438168076.44 );
    cameraCommandAdjustPanTiltZoomData1->SetY( 399774438168076.44 );
    cameraCommandAdjustPanTiltZoomData1->SetZ( 399774438168076.44 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandAdjustPanTiltZoomData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandAdjustPanTiltZoomData2 = std::reinterpret_pointer_cast<CameraCommandAdjustPanTiltZoomData>( ReadDataFrom( source ) );
    bool equal = cameraCommandAdjustPanTiltZoomData2->IsEqualTo( *cameraCommandAdjustPanTiltZoomData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandContinuousMoveDataSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandContinuousMoveDataSerializationTest )
{
    auto cameraCommandContinuousMoveData1 = std::make_shared<CameraCommandContinuousMoveData>( );
    cameraCommandContinuousMoveData1->SetId( Guid( L"{2DCEB552-500C-9183-89C1-0A30B473AD4A}" ) );
    cameraCommandContinuousMoveData1->SetRowVersion( -7961431703022553774LL );
    cameraCommandContinuousMoveData1->SetCamera( Guid( L"{2DCEB552-500C-9183-89C1-0A30B473AD4A}" ) );
    cameraCommandContinuousMoveData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    cameraCommandContinuousMoveData1->SetDeviceCommandSourceType( DeviceCommandSourceType::Device );
    cameraCommandContinuousMoveData1->SetDeviceCommandSourceId( Guid( L"{2DCEB552-500C-9183-89C1-0A30B473AD4A}" ) );
    cameraCommandContinuousMoveData1->SetReply( Guid( L"{2DCEB552-500C-9183-89C1-0A30B473AD4A}" ) );
    cameraCommandContinuousMoveData1->SetNormalized( false );
    cameraCommandContinuousMoveData1->SetPanVelocity( 10485312370686998 );
    cameraCommandContinuousMoveData1->SetTiltVelocity( 10485312370686998 );
    cameraCommandContinuousMoveData1->SetZoomVelocity( 10485312370686998 );
    cameraCommandContinuousMoveData1->SetDuration( TimeSpan( -23022553774LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandContinuousMoveData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandContinuousMoveData2 = std::reinterpret_pointer_cast<CameraCommandContinuousMoveData>( ReadDataFrom( source ) );
    bool equal = cameraCommandContinuousMoveData2->IsEqualTo( *cameraCommandContinuousMoveData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandGeoMoveDataSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandGeoMoveDataSerializationTest )
{
    auto cameraCommandGeoMoveData1 = std::make_shared<CameraCommandGeoMoveData>( );
    cameraCommandGeoMoveData1->SetId( Guid( L"{A0BB9958-0341-AD24-B524-C08205DD991A}" ) );
    cameraCommandGeoMoveData1->SetRowVersion( -5970643625582028456LL );
    cameraCommandGeoMoveData1->SetCamera( Guid( L"{A0BB9958-0341-AD24-B524-C08205DD991A}" ) );
    cameraCommandGeoMoveData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    cameraCommandGeoMoveData1->SetDeviceCommandSourceType( DeviceCommandSourceType::Unknown );
    cameraCommandGeoMoveData1->SetDeviceCommandSourceId( Guid( L"{A0BB9958-0341-AD24-B524-C08205DD991A}" ) );
    cameraCommandGeoMoveData1->SetReply( Guid( L"{A0BB9958-0341-AD24-B524-C08205DD991A}" ) );
    cameraCommandGeoMoveData1->SetLatitude( 12476100448127522 );
    cameraCommandGeoMoveData1->SetLongitude( 12476100448127522 );
    cameraCommandGeoMoveData1->SetAltitude( 12476100448127522 );
    cameraCommandGeoMoveData1->SetViewportWidth( 12476100448127522 );
    cameraCommandGeoMoveData1->SetViewportHeight( 12476100448127522 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandGeoMoveData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandGeoMoveData2 = std::reinterpret_pointer_cast<CameraCommandGeoMoveData>( ReadDataFrom( source ) );
    bool equal = cameraCommandGeoMoveData2->IsEqualTo( *cameraCommandGeoMoveData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandRelativeMoveDataSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandRelativeMoveDataSerializationTest )
{
    auto cameraCommandRelativeMoveData1 = std::make_shared<CameraCommandRelativeMoveData>( );
    cameraCommandRelativeMoveData1->SetId( Guid( L"{3B1F2501-F679-705C-0E3A-6F9EDCF8A480}" ) );
    cameraCommandRelativeMoveData1->SetRowVersion( 8096617230648681729LL );
    cameraCommandRelativeMoveData1->SetCamera( Guid( L"{3B1F2501-F679-705C-0E3A-6F9EDCF8A480}" ) );
    cameraCommandRelativeMoveData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    cameraCommandRelativeMoveData1->SetDeviceCommandSourceType( DeviceCommandSourceType::Session );
    cameraCommandRelativeMoveData1->SetDeviceCommandSourceId( Guid( L"{3B1F2501-F679-705C-0E3A-6F9EDCF8A480}" ) );
    cameraCommandRelativeMoveData1->SetReply( Guid( L"{3B1F2501-F679-705C-0E3A-6F9EDCF8A480}" ) );
    cameraCommandRelativeMoveData1->SetNormalized( false );
    cameraCommandRelativeMoveData1->SetPanAngle( 8096617230648681 );
    cameraCommandRelativeMoveData1->SetTiltAngle( 8096617230648681 );
    cameraCommandRelativeMoveData1->SetFocalLength( 8096617230648681 );
    cameraCommandRelativeMoveData1->SetPanSpeed( 8096617230648681 );
    cameraCommandRelativeMoveData1->SetTiltSpeed( 8096617230648681 );
    cameraCommandRelativeMoveData1->SetZoomSpeed( 8096617230648681 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandRelativeMoveData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandRelativeMoveData2 = std::reinterpret_pointer_cast<CameraCommandRelativeMoveData>( ReadDataFrom( source ) );
    bool equal = cameraCommandRelativeMoveData2->IsEqualTo( *cameraCommandRelativeMoveData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandReleasePTZOwnershipDataSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandReleasePTZOwnershipDataSerializationTest )
{
    auto cameraCommandReleasePTZOwnershipData1 = std::make_shared<CameraCommandReleasePTZOwnershipData>( );
    cameraCommandReleasePTZOwnershipData1->SetId( Guid( L"{9CDA9BB9-4762-635C-C63A-E246395BD99D}" ) );
    cameraCommandReleasePTZOwnershipData1->SetRowVersion( 7159675996476185529LL );
    cameraCommandReleasePTZOwnershipData1->SetCamera( Guid( L"{9CDA9BB9-4762-635C-C63A-E246395BD99D}" ) );
    cameraCommandReleasePTZOwnershipData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    cameraCommandReleasePTZOwnershipData1->SetDeviceCommandSourceType( DeviceCommandSourceType::Session );
    cameraCommandReleasePTZOwnershipData1->SetDeviceCommandSourceId( Guid( L"{9CDA9BB9-4762-635C-C63A-E246395BD99D}" ) );
    cameraCommandReleasePTZOwnershipData1->SetReply( Guid( L"{9CDA9BB9-4762-635C-C63A-E246395BD99D}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandReleasePTZOwnershipData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandReleasePTZOwnershipData2 = std::reinterpret_pointer_cast<CameraCommandReleasePTZOwnershipData>( ReadDataFrom( source ) );
    bool equal = cameraCommandReleasePTZOwnershipData2->IsEqualTo( *cameraCommandReleasePTZOwnershipData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandRequestPTZOwnershipDataSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandRequestPTZOwnershipDataSerializationTest )
{
    auto cameraCommandRequestPTZOwnershipData1 = std::make_shared<CameraCommandRequestPTZOwnershipData>( );
    cameraCommandRequestPTZOwnershipData1->SetId( Guid( L"{74450B39-1F6C-F5B8-AF1D-F8362EA2D09C}" ) );
    cameraCommandRequestPTZOwnershipData1->SetRowVersion( -740807588034835655LL );
    cameraCommandRequestPTZOwnershipData1->SetCamera( Guid( L"{74450B39-1F6C-F5B8-AF1D-F8362EA2D09C}" ) );
    cameraCommandRequestPTZOwnershipData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    cameraCommandRequestPTZOwnershipData1->SetDeviceCommandSourceType( DeviceCommandSourceType::Session );
    cameraCommandRequestPTZOwnershipData1->SetDeviceCommandSourceId( Guid( L"{74450B39-1F6C-F5B8-AF1D-F8362EA2D09C}" ) );
    cameraCommandRequestPTZOwnershipData1->SetReply( Guid( L"{74450B39-1F6C-F5B8-AF1D-F8362EA2D09C}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandRequestPTZOwnershipData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandRequestPTZOwnershipData2 = std::reinterpret_pointer_cast<CameraCommandRequestPTZOwnershipData>( ReadDataFrom( source ) );
    bool equal = cameraCommandRequestPTZOwnershipData2->IsEqualTo( *cameraCommandRequestPTZOwnershipData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandSetAutoFocusDataSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandSetAutoFocusDataSerializationTest )
{
    auto cameraCommandSetAutoFocusData1 = std::make_shared<CameraCommandSetAutoFocusData>( );
    cameraCommandSetAutoFocusData1->SetId( Guid( L"{BFA69A70-BA7F-4100-8200-5DFEFD65590E}" ) );
    cameraCommandSetAutoFocusData1->SetRowVersion( 4683948670304295536LL );
    cameraCommandSetAutoFocusData1->SetCamera( Guid( L"{BFA69A70-BA7F-4100-8200-5DFEFD65590E}" ) );
    cameraCommandSetAutoFocusData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    cameraCommandSetAutoFocusData1->SetDeviceCommandSourceType( DeviceCommandSourceType::Unknown );
    cameraCommandSetAutoFocusData1->SetDeviceCommandSourceId( Guid( L"{BFA69A70-BA7F-4100-8200-5DFEFD65590E}" ) );
    cameraCommandSetAutoFocusData1->SetReply( Guid( L"{BFA69A70-BA7F-4100-8200-5DFEFD65590E}" ) );
    cameraCommandSetAutoFocusData1->SetEnabled( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandSetAutoFocusData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandSetAutoFocusData2 = std::reinterpret_pointer_cast<CameraCommandSetAutoFocusData>( ReadDataFrom( source ) );
    bool equal = cameraCommandSetAutoFocusData2->IsEqualTo( *cameraCommandSetAutoFocusData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandSetBlackAndWhiteDataSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandSetBlackAndWhiteDataSerializationTest )
{
    auto cameraCommandSetBlackAndWhiteData1 = std::make_shared<CameraCommandSetBlackAndWhiteData>( );
    cameraCommandSetBlackAndWhiteData1->SetId( Guid( L"{9B072A4D-7597-5B04-DA20-AEE9D9E054B2}" ) );
    cameraCommandSetBlackAndWhiteData1->SetRowVersion( 6558496251359734349LL );
    cameraCommandSetBlackAndWhiteData1->SetCamera( Guid( L"{9B072A4D-7597-5B04-DA20-AEE9D9E054B2}" ) );
    cameraCommandSetBlackAndWhiteData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    cameraCommandSetBlackAndWhiteData1->SetDeviceCommandSourceType( DeviceCommandSourceType::Session );
    cameraCommandSetBlackAndWhiteData1->SetDeviceCommandSourceId( Guid( L"{9B072A4D-7597-5B04-DA20-AEE9D9E054B2}" ) );
    cameraCommandSetBlackAndWhiteData1->SetReply( Guid( L"{9B072A4D-7597-5B04-DA20-AEE9D9E054B2}" ) );
    cameraCommandSetBlackAndWhiteData1->SetEnabled( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandSetBlackAndWhiteData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandSetBlackAndWhiteData2 = std::reinterpret_pointer_cast<CameraCommandSetBlackAndWhiteData>( ReadDataFrom( source ) );
    bool equal = cameraCommandSetBlackAndWhiteData2->IsEqualTo( *cameraCommandSetBlackAndWhiteData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandSetFollowedDataSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandSetFollowedDataSerializationTest )
{
    auto cameraCommandSetFollowedData1 = std::make_shared<CameraCommandSetFollowedData>( );
    cameraCommandSetFollowedData1->SetId( Guid( L"{B9DD5ECF-09D5-3BA0-DC05-90AB9DBB7AF3}" ) );
    cameraCommandSetFollowedData1->SetRowVersion( 4296444858062429903LL );
    cameraCommandSetFollowedData1->SetCamera( Guid( L"{B9DD5ECF-09D5-3BA0-DC05-90AB9DBB7AF3}" ) );
    cameraCommandSetFollowedData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    cameraCommandSetFollowedData1->SetDeviceCommandSourceType( DeviceCommandSourceType::Source );
    cameraCommandSetFollowedData1->SetDeviceCommandSourceId( Guid( L"{B9DD5ECF-09D5-3BA0-DC05-90AB9DBB7AF3}" ) );
    cameraCommandSetFollowedData1->SetReply( Guid( L"{B9DD5ECF-09D5-3BA0-DC05-90AB9DBB7AF3}" ) );
    cameraCommandSetFollowedData1->SetTrackId( Guid( L"{B9DD5ECF-09D5-3BA0-DC05-90AB9DBB7AF3}" ) );
    cameraCommandSetFollowedData1->SetReason( CameraFollowReason::User );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandSetFollowedData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandSetFollowedData2 = std::reinterpret_pointer_cast<CameraCommandSetFollowedData>( ReadDataFrom( source ) );
    bool equal = cameraCommandSetFollowedData2->IsEqualTo( *cameraCommandSetFollowedData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandSetInfraRedLampDataSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandSetInfraRedLampDataSerializationTest )
{
    auto cameraCommandSetInfraRedLampData1 = std::make_shared<CameraCommandSetInfraRedLampData>( );
    cameraCommandSetInfraRedLampData1->SetId( Guid( L"{4F4F05AD-B0D5-2BD2-D44B-0DABF2F2A0B5}" ) );
    cameraCommandSetInfraRedLampData1->SetRowVersion( 3157780718945240493LL );
    cameraCommandSetInfraRedLampData1->SetCamera( Guid( L"{4F4F05AD-B0D5-2BD2-D44B-0DABF2F2A0B5}" ) );
    cameraCommandSetInfraRedLampData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    cameraCommandSetInfraRedLampData1->SetDeviceCommandSourceType( DeviceCommandSourceType::Session );
    cameraCommandSetInfraRedLampData1->SetDeviceCommandSourceId( Guid( L"{4F4F05AD-B0D5-2BD2-D44B-0DABF2F2A0B5}" ) );
    cameraCommandSetInfraRedLampData1->SetReply( Guid( L"{4F4F05AD-B0D5-2BD2-D44B-0DABF2F2A0B5}" ) );
    cameraCommandSetInfraRedLampData1->SetEnabled( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandSetInfraRedLampData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandSetInfraRedLampData2 = std::reinterpret_pointer_cast<CameraCommandSetInfraRedLampData>( ReadDataFrom( source ) );
    bool equal = cameraCommandSetInfraRedLampData2->IsEqualTo( *cameraCommandSetInfraRedLampData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandSetWasherDataSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandSetWasherDataSerializationTest )
{
    auto cameraCommandSetWasherData1 = std::make_shared<CameraCommandSetWasherData>( );
    cameraCommandSetWasherData1->SetId( Guid( L"{CD63FFAD-F1AD-8424-2124-8FB5B3C6FFB5}" ) );
    cameraCommandSetWasherData1->SetRowVersion( -8924742832763961427LL );
    cameraCommandSetWasherData1->SetCamera( Guid( L"{CD63FFAD-F1AD-8424-2124-8FB5B3C6FFB5}" ) );
    cameraCommandSetWasherData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    cameraCommandSetWasherData1->SetDeviceCommandSourceType( DeviceCommandSourceType::Session );
    cameraCommandSetWasherData1->SetDeviceCommandSourceId( Guid( L"{CD63FFAD-F1AD-8424-2124-8FB5B3C6FFB5}" ) );
    cameraCommandSetWasherData1->SetReply( Guid( L"{CD63FFAD-F1AD-8424-2124-8FB5B3C6FFB5}" ) );
    cameraCommandSetWasherData1->SetEnabled( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandSetWasherData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandSetWasherData2 = std::reinterpret_pointer_cast<CameraCommandSetWasherData>( ReadDataFrom( source ) );
    bool equal = cameraCommandSetWasherData2->IsEqualTo( *cameraCommandSetWasherData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandSetWiperDataSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandSetWiperDataSerializationTest )
{
    auto cameraCommandSetWiperData1 = std::make_shared<CameraCommandSetWiperData>( );
    cameraCommandSetWiperData1->SetId( Guid( L"{059133CC-5F0A-B478-2D1E-FA50A089CC33}" ) );
    cameraCommandSetWiperData1->SetRowVersion( -5442495653029530676LL );
    cameraCommandSetWiperData1->SetCamera( Guid( L"{059133CC-5F0A-B478-2D1E-FA50A089CC33}" ) );
    cameraCommandSetWiperData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    cameraCommandSetWiperData1->SetDeviceCommandSourceType( DeviceCommandSourceType::Unknown );
    cameraCommandSetWiperData1->SetDeviceCommandSourceId( Guid( L"{059133CC-5F0A-B478-2D1E-FA50A089CC33}" ) );
    cameraCommandSetWiperData1->SetReply( Guid( L"{059133CC-5F0A-B478-2D1E-FA50A089CC33}" ) );
    cameraCommandSetWiperData1->SetEnabled( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandSetWiperData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandSetWiperData2 = std::reinterpret_pointer_cast<CameraCommandSetWiperData>( ReadDataFrom( source ) );
    bool equal = cameraCommandSetWiperData2->IsEqualTo( *cameraCommandSetWiperData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandStopDataSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandStopDataSerializationTest )
{
    auto cameraCommandStopData1 = std::make_shared<CameraCommandStopData>( );
    cameraCommandStopData1->SetId( Guid( L"{F2E01750-4663-2D0A-B450-62C64F07E80A}" ) );
    cameraCommandStopData1->SetRowVersion( 3245483876564342608LL );
    cameraCommandStopData1->SetCamera( Guid( L"{F2E01750-4663-2D0A-B450-62C64F07E80A}" ) );
    cameraCommandStopData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    cameraCommandStopData1->SetDeviceCommandSourceType( DeviceCommandSourceType::Unknown );
    cameraCommandStopData1->SetDeviceCommandSourceId( Guid( L"{F2E01750-4663-2D0A-B450-62C64F07E80A}" ) );
    cameraCommandStopData1->SetReply( Guid( L"{F2E01750-4663-2D0A-B450-62C64F07E80A}" ) );
    cameraCommandStopData1->SetPanTilt( false );
    cameraCommandStopData1->SetZoom( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandStopData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandStopData2 = std::reinterpret_pointer_cast<CameraCommandStopData>( ReadDataFrom( source ) );
    bool equal = cameraCommandStopData2->IsEqualTo( *cameraCommandStopData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraCommandReplyDataSerializationTest
BOOST_AUTO_TEST_CASE( CameraCommandReplyDataSerializationTest )
{
    auto cameraCommandReplyData1 = std::make_shared<CameraCommandReplyData>( );
    cameraCommandReplyData1->SetId( Guid( L"{26FFBA0F-E13C-F85B-1FDA-873C64FF5DF0}" ) );
    cameraCommandReplyData1->SetRowVersion( -550598880954172913LL );
    cameraCommandReplyData1->SetCamera( Guid( L"{26FFBA0F-E13C-F85B-1FDA-873C64FF5DF0}" ) );
    cameraCommandReplyData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    cameraCommandReplyData1->SetCommand( Guid( L"{26FFBA0F-E13C-F85B-1FDA-873C64FF5DF0}" ) );
    cameraCommandReplyData1->SetStatus( DeviceCommandReplyStatus::Error );
    cameraCommandReplyData1->SetMessage( L"Message" );
    cameraCommandReplyData1->SetPanAngle( 17896145192755378 );
    cameraCommandReplyData1->SetTiltAngle( 17896145192755378 );
    cameraCommandReplyData1->SetFocalLength( 17896145192755378 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraCommandReplyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraCommandReplyData2 = std::reinterpret_pointer_cast<CameraCommandReplyData>( ReadDataFrom( source ) );
    bool equal = cameraCommandReplyData2->IsEqualTo( *cameraCommandReplyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraConfigurationDataSerializationTest
BOOST_AUTO_TEST_CASE( CameraConfigurationDataSerializationTest )
{
    auto cameraConfigurationData1 = std::make_shared<CameraConfigurationData>( );
    cameraConfigurationData1->SetId( Guid( L"{328264BE-F096-6BC6-D663-0F694C41267D}" ) );
    cameraConfigurationData1->SetRowVersion( 7766159135330165950LL );
    cameraConfigurationData1->SetCamera( Guid( L"{328264BE-F096-6BC6-D663-0F694C41267D}" ) );
    cameraConfigurationData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    cameraConfigurationData1->SetCameraControlProtocol( CameraControlProtocol::Unknown );
    cameraConfigurationData1->SetCameraAddress( L"CameraAddress" );
    cameraConfigurationData1->SetCameraPort( 847406270L );
    cameraConfigurationData1->SetCameraControlAddress( L"CameraControlAddress" );
    cameraConfigurationData1->SetCameraControlPort( 847406270L );
    cameraConfigurationData1->SetCameraUserName( L"CameraUserName" );
    cameraConfigurationData1->SetCameraPassword( L"CameraPassword" );
    cameraConfigurationData1->SetUseRtspUriOverride( false );
    cameraConfigurationData1->SetRtspUriOverride( L"RtspUriOverride" );
    cameraConfigurationData1->SetLatitude( 7766159135330166 );
    cameraConfigurationData1->SetLongitude( 7766159135330166 );
    cameraConfigurationData1->SetAltitude( 7766159135330166 );
    cameraConfigurationData1->SetUseRelativePosition( false );
    cameraConfigurationData1->SetAzimuthFromGPS( 7766159135330166 );
    cameraConfigurationData1->SetDistanceFromGPS( 7766159135330166 );
    cameraConfigurationData1->SetPanTiltMode( CameraPanTiltMode::Normalized );
    cameraConfigurationData1->SetMinTiltAngle( 7766159135330166 );
    cameraConfigurationData1->SetMaxTiltAngle( 7766159135330166 );
    cameraConfigurationData1->SetMinTiltScaleAngle( 7766159135330166 );
    cameraConfigurationData1->SetMaxTiltScaleAngle( 7766159135330166 );
    cameraConfigurationData1->SetUseReverseTiltAngle( false );
    cameraConfigurationData1->SetUseReverseNormalizedTiltAngle( false );
    cameraConfigurationData1->SetMinTiltVelocity( 7766159135330166 );
    cameraConfigurationData1->SetMaxTiltVelocity( 7766159135330166 );
    cameraConfigurationData1->SetMinTiltSpeed( 7766159135330166 );
    cameraConfigurationData1->SetMaxTiltSpeed( 7766159135330166 );
    cameraConfigurationData1->SetMinPanAngle( 7766159135330166 );
    cameraConfigurationData1->SetMaxPanAngle( 7766159135330166 );
    cameraConfigurationData1->SetMinPanScaleAngle( 7766159135330166 );
    cameraConfigurationData1->SetMaxPanScaleAngle( 7766159135330166 );
    cameraConfigurationData1->SetUseReversePanAngle( false );
    cameraConfigurationData1->SetUseReverseNormalizedPanAngle( false );
    cameraConfigurationData1->SetMinPanVelocity( 7766159135330166 );
    cameraConfigurationData1->SetMaxPanVelocity( 7766159135330166 );
    cameraConfigurationData1->SetMinPanSpeed( 7766159135330166 );
    cameraConfigurationData1->SetMaxPanSpeed( 7766159135330166 );
    cameraConfigurationData1->SetFocalLengthMode( CameraFocalLengthMode::Normalized );
    cameraConfigurationData1->SetMinFocalLength( 7766159135330166 );
    cameraConfigurationData1->SetMaxFocalLength( 7766159135330166 );
    cameraConfigurationData1->SetMinFocalLengthScale( 7766159135330166 );
    cameraConfigurationData1->SetMaxFocalLengthScale( 7766159135330166 );
    cameraConfigurationData1->SetMinZoomVelocity( 7766159135330166 );
    cameraConfigurationData1->SetMaxZoomVelocity( 7766159135330166 );
    cameraConfigurationData1->SetMinZoomSpeed( 7766159135330166 );
    cameraConfigurationData1->SetMaxZoomSpeed( 7766159135330166 );
    cameraConfigurationData1->SetImageSensorWidth( 7766159135330166 );
    cameraConfigurationData1->SetImageSensorHeight( 7766159135330166 );
    cameraConfigurationData1->SetHomePanAngle( 7766159135330166 );
    cameraConfigurationData1->SetHomeTiltAngle( 7766159135330166 );
    cameraConfigurationData1->SetHomeFocalLength( 7766159135330166 );
    cameraConfigurationData1->SetPanOffset( 7766159135330166 );
    cameraConfigurationData1->SetTiltOffset( 7766159135330166 );
    cameraConfigurationData1->SetAimAltitude( 7766159135330166 );
    cameraConfigurationData1->SetMinimumTargetWidth( 7766159135330166 );
    cameraConfigurationData1->SetTargetLockTimeout( TimeSpan( 95330165950LL ) );
    cameraConfigurationData1->SetUpdateStatusInterval( TimeSpan( 95330165950LL ) );
    cameraConfigurationData1->SetReadTimeout( TimeSpan( 95330165950LL ) );
    cameraConfigurationData1->SetMoveCommandStatusDelay( TimeSpan( 95330165950LL ) );
    cameraConfigurationData1->SetPtzProfileName( L"PtzProfileName" );
    cameraConfigurationData1->SetPtzConfigurationToken( L"PtzConfigurationToken" );
    cameraConfigurationData1->SetVideoSourceToken( L"VideoSourceToken" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraConfigurationData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraConfigurationData2 = std::reinterpret_pointer_cast<CameraConfigurationData>( ReadDataFrom( source ) );
    bool equal = cameraConfigurationData2->IsEqualTo( *cameraConfigurationData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraPanCalibrationDataSerializationTest
BOOST_AUTO_TEST_CASE( CameraPanCalibrationDataSerializationTest )
{
    auto cameraPanCalibrationData1 = std::make_shared<CameraPanCalibrationData>( );
    cameraPanCalibrationData1->SetId( Guid( L"{938FC103-EA2B-A116-8568-57D4C9F183C0}" ) );
    cameraPanCalibrationData1->SetRowVersion( -6839021511235354365LL );
    cameraPanCalibrationData1->SetCamera( Guid( L"{938FC103-EA2B-A116-8568-57D4C9F183C0}" ) );
    cameraPanCalibrationData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraPanCalibrationData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraPanCalibrationData2 = std::reinterpret_pointer_cast<CameraPanCalibrationData>( ReadDataFrom( source ) );
    bool equal = cameraPanCalibrationData2->IsEqualTo( *cameraPanCalibrationData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraPanCalibrationValueDataSerializationTest
BOOST_AUTO_TEST_CASE( CameraPanCalibrationValueDataSerializationTest )
{
    auto cameraPanCalibrationValueData1 = std::make_shared<CameraPanCalibrationValueData>( );
    cameraPanCalibrationValueData1->SetId( Guid( L"{CE6BFE19-A13B-4144-8222-85DC73D67F98}" ) );
    cameraPanCalibrationValueData1->SetRowVersion( 4703061189119966745LL );
    cameraPanCalibrationValueData1->SetPanCalibration( Guid( L"{CE6BFE19-A13B-4144-8222-85DC73D67F98}" ) );
    cameraPanCalibrationValueData1->SetPanAngle( 4703061189119967 );
    cameraPanCalibrationValueData1->SetPanOffset( 4703061189119967 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraPanCalibrationValueData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraPanCalibrationValueData2 = std::reinterpret_pointer_cast<CameraPanCalibrationValueData>( ReadDataFrom( source ) );
    bool equal = cameraPanCalibrationValueData2->IsEqualTo( *cameraPanCalibrationValueData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraStatusDataSerializationTest
BOOST_AUTO_TEST_CASE( CameraStatusDataSerializationTest )
{
    auto cameraStatusData1 = std::make_shared<CameraStatusData>( );
    cameraStatusData1->SetId( Guid( L"{3632442A-D4AE-2066-0466-2B756C4C2254}" ) );
    cameraStatusData1->SetRowVersion( 2334787301536842794LL );
    cameraStatusData1->SetCamera( Guid( L"{3632442A-D4AE-2066-0466-2B756C4C2254}" ) );
    cameraStatusData1->SetTrack( Guid( L"{3632442A-D4AE-2066-0466-2B756C4C2254}" ) );
    cameraStatusData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    cameraStatusData1->SetPositionPanTiltMode( CameraPanTiltMode::Angular );
    cameraStatusData1->SetPanAngle( 2334787301536843 );
    cameraStatusData1->SetTiltAngle( 2334787301536843 );
    cameraStatusData1->SetPositionFocalLengthMode( CameraFocalLengthMode::Millimeter );
    cameraStatusData1->SetFocalLength( 2334787301536843 );
    cameraStatusData1->SetPanTiltMoveStatus( CameraMoveStatus::Moving );
    cameraStatusData1->SetZoomMoveStatus( CameraMoveStatus::Moving );
    cameraStatusData1->SetVelocityPanTiltMode( CameraPanTiltMode::Angular );
    cameraStatusData1->SetPanVelocity( 2334787301536843 );
    cameraStatusData1->SetTiltVelocity( 2334787301536843 );
    cameraStatusData1->SetVelocityFocalLengthMode( CameraFocalLengthMode::Millimeter );
    cameraStatusData1->SetZoomVelocity( 2334787301536843 );
    cameraStatusData1->SetActiveFeatures( CameraFeatures::Washer );
    cameraStatusData1->SetError( L"Error" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraStatusData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraStatusData2 = std::reinterpret_pointer_cast<CameraStatusData>( ReadDataFrom( source ) );
    bool equal = cameraStatusData2->IsEqualTo( *cameraStatusData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraTiltCalibrationDataSerializationTest
BOOST_AUTO_TEST_CASE( CameraTiltCalibrationDataSerializationTest )
{
    auto cameraTiltCalibrationData1 = std::make_shared<CameraTiltCalibrationData>( );
    cameraTiltCalibrationData1->SetId( Guid( L"{801E423D-6D9D-ABFC-D53F-B6B9017842BC}" ) );
    cameraTiltCalibrationData1->SetRowVersion( -6053843275866029507LL );
    cameraTiltCalibrationData1->SetCamera( Guid( L"{801E423D-6D9D-ABFC-D53F-B6B9017842BC}" ) );
    cameraTiltCalibrationData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraTiltCalibrationData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraTiltCalibrationData2 = std::reinterpret_pointer_cast<CameraTiltCalibrationData>( ReadDataFrom( source ) );
    bool equal = cameraTiltCalibrationData2->IsEqualTo( *cameraTiltCalibrationData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraTiltCalibrationValueDataSerializationTest
BOOST_AUTO_TEST_CASE( CameraTiltCalibrationValueDataSerializationTest )
{
    auto cameraTiltCalibrationValueData1 = std::make_shared<CameraTiltCalibrationValueData>( );
    cameraTiltCalibrationValueData1->SetId( Guid( L"{095879C0-8CCC-3747-ECE2-3133901A9E03}" ) );
    cameraTiltCalibrationValueData1->SetRowVersion( 3983307203390503360LL );
    cameraTiltCalibrationValueData1->SetTiltCalibration( Guid( L"{095879C0-8CCC-3747-ECE2-3133901A9E03}" ) );
    cameraTiltCalibrationValueData1->SetPanAngle( 3983307203390503.5 );
    cameraTiltCalibrationValueData1->SetTiltOffset( 3983307203390503.5 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraTiltCalibrationValueData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraTiltCalibrationValueData2 = std::reinterpret_pointer_cast<CameraTiltCalibrationValueData>( ReadDataFrom( source ) );
    bool equal = cameraTiltCalibrationValueData2->IsEqualTo( *cameraTiltCalibrationValueData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraZoomCalibrationDataSerializationTest
BOOST_AUTO_TEST_CASE( CameraZoomCalibrationDataSerializationTest )
{
    auto cameraZoomCalibrationData1 = std::make_shared<CameraZoomCalibrationData>( );
    cameraZoomCalibrationData1->SetId( Guid( L"{E6245A05-1E69-4CFC-323F-789667245AA0}" ) );
    cameraZoomCalibrationData1->SetRowVersion( 5547342281195149829LL );
    cameraZoomCalibrationData1->SetCamera( Guid( L"{E6245A05-1E69-4CFC-323F-789667245AA0}" ) );
    cameraZoomCalibrationData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraZoomCalibrationData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraZoomCalibrationData2 = std::reinterpret_pointer_cast<CameraZoomCalibrationData>( ReadDataFrom( source ) );
    bool equal = cameraZoomCalibrationData2->IsEqualTo( *cameraZoomCalibrationData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraZoomCalibrationValueDataSerializationTest
BOOST_AUTO_TEST_CASE( CameraZoomCalibrationValueDataSerializationTest )
{
    auto cameraZoomCalibrationValueData1 = std::make_shared<CameraZoomCalibrationValueData>( );
    cameraZoomCalibrationValueData1->SetId( Guid( L"{8F3ECC72-7686-78C6-1E63-6E61F17C334E}" ) );
    cameraZoomCalibrationValueData1->SetRowVersion( 8702773650241014898LL );
    cameraZoomCalibrationValueData1->SetZoomCalibration( Guid( L"{8F3ECC72-7686-78C6-1E63-6E61F17C334E}" ) );
    cameraZoomCalibrationValueData1->SetFocalLength( 8702773650241015 );
    cameraZoomCalibrationValueData1->SetFocalLengthOffset( 8702773650241015 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraZoomCalibrationValueData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraZoomCalibrationValueData2 = std::reinterpret_pointer_cast<CameraZoomCalibrationValueData>( ReadDataFrom( source ) );
    bool equal = cameraZoomCalibrationValueData2->IsEqualTo( *cameraZoomCalibrationValueData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CatalogDataSerializationTest
BOOST_AUTO_TEST_CASE( CatalogDataSerializationTest )
{
    auto catalogData1 = std::make_shared<CatalogData>( );
    catalogData1->SetId( Guid( L"{3F08CFBF-AC44-60BE-067D-3522FC10F3FD}" ) );
    catalogData1->SetRowVersion( 6971198682331402175LL );
    catalogData1->SetCatalog( Guid( L"{3F08CFBF-AC44-60BE-067D-3522FC10F3FD}" ) );
    catalogData1->SetName( L"Name" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *catalogData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto catalogData2 = std::reinterpret_pointer_cast<CatalogData>( ReadDataFrom( source ) );
    bool equal = catalogData2->IsEqualTo( *catalogData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ElementDataSerializationTest
BOOST_AUTO_TEST_CASE( ElementDataSerializationTest )
{
    auto elementData1 = std::make_shared<ElementData>( );
    elementData1->SetId( Guid( L"{90C78EFA-4D22-B6DE-6D7B-B24409E3715F}" ) );
    elementData1->SetRowVersion( -5269689703123677446LL );
    elementData1->SetCatalog( Guid( L"{90C78EFA-4D22-B6DE-6D7B-B24409E3715F}" ) );
    elementData1->SetName( L"Name" );
    elementData1->SetElementType( Guid( L"{90C78EFA-4D22-B6DE-6D7B-B24409E3715F}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *elementData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto elementData2 = std::reinterpret_pointer_cast<ElementData>( ReadDataFrom( source ) );
    bool equal = elementData2->IsEqualTo( *elementData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CollectionInfoDataSerializationTest
BOOST_AUTO_TEST_CASE( CollectionInfoDataSerializationTest )
{
    auto collectionInfoData1 = std::make_shared<CollectionInfoData>( );
    collectionInfoData1->SetId( Guid( L"{0335BBA1-A308-DC8F-3BF1-C510C0ACDD85}" ) );
    collectionInfoData1->SetRowVersion( -2553643208886862943LL );
    collectionInfoData1->SetCount( -2553643208886862943LL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *collectionInfoData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto collectionInfoData2 = std::reinterpret_pointer_cast<CollectionInfoData>( ReadDataFrom( source ) );
    bool equal = collectionInfoData2->IsEqualTo( *collectionInfoData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CountryDataSerializationTest
BOOST_AUTO_TEST_CASE( CountryDataSerializationTest )
{
    auto countryData1 = std::make_shared<CountryData>( );
    countryData1->SetId( Guid( L"{011738F6-F745-C396-C369-EFA280E81C6F}" ) );
    countryData1->SetRowVersion( -4353020114063902474LL );
    countryData1->SetName( L"Name" );
    countryData1->SetCode( 18299126L );
    countryData1->SetAlpha2( L"Al" );
    countryData1->SetAlpha3( L"Alp" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *countryData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto countryData2 = std::reinterpret_pointer_cast<CountryData>( ReadDataFrom( source ) );
    bool equal = countryData2->IsEqualTo( *countryData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CursorInfoDataSerializationTest
BOOST_AUTO_TEST_CASE( CursorInfoDataSerializationTest )
{
    auto cursorInfoData1 = std::make_shared<CursorInfoData>( );
    cursorInfoData1->SetId( Guid( L"{BFDBAA05-9FB9-E0B1-078D-F99DFDDB55A0}" ) );
    cursorInfoData1->SetRowVersion( -2255846318199297531LL );
    cursorInfoData1->SetTypeCode( -1076123131L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cursorInfoData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cursorInfoData2 = std::reinterpret_pointer_cast<CursorInfoData>( ReadDataFrom( source ) );
    bool equal = cursorInfoData2->IsEqualTo( *cursorInfoData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DateTimeTimeseriesValueDataSerializationTest
BOOST_AUTO_TEST_CASE( DateTimeTimeseriesValueDataSerializationTest )
{
    auto dateTimeTimeseriesValueData1 = std::make_shared<DateTimeTimeseriesValueData>( );
    dateTimeTimeseriesValueData1->SetId( Guid( L"{4267AABD-DE1A-D545-ABA2-7B5842E655BD}" ) );
    dateTimeTimeseriesValueData1->SetRowVersion( -3078810565873259843LL );
    dateTimeTimeseriesValueData1->SetTimeseries( Guid( L"{4267AABD-DE1A-D545-ABA2-7B5842E655BD}" ) );
    dateTimeTimeseriesValueData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    dateTimeTimeseriesValueData1->SetValue( DateTime( 1, 1, 1, 14, 37, 6 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *dateTimeTimeseriesValueData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto dateTimeTimeseriesValueData2 = std::reinterpret_pointer_cast<DateTimeTimeseriesValueData>( ReadDataFrom( source ) );
    bool equal = dateTimeTimeseriesValueData2->IsEqualTo( *dateTimeTimeseriesValueData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DeviceHostDataSerializationTest
BOOST_AUTO_TEST_CASE( DeviceHostDataSerializationTest )
{
    auto deviceHostData1 = std::make_shared<DeviceHostData>( );
    deviceHostData1->SetId( Guid( L"{6CFF9410-05DF-9D07-B9E0-A0FB36FF2908}" ) );
    deviceHostData1->SetRowVersion( -7131725027753356272LL );
    deviceHostData1->SetName( L"Name" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *deviceHostData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto deviceHostData2 = std::reinterpret_pointer_cast<DeviceHostData>( ReadDataFrom( source ) );
    bool equal = deviceHostData2->IsEqualTo( *deviceHostData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DeviceHostConfigurationDataSerializationTest
BOOST_AUTO_TEST_CASE( DeviceHostConfigurationDataSerializationTest )
{
    auto deviceHostConfigurationData1 = std::make_shared<DeviceHostConfigurationData>( );
    deviceHostConfigurationData1->SetId( Guid( L"{E525AB0B-EC92-D432-2B4C-3749A7A4D5D0}" ) );
    deviceHostConfigurationData1->SetRowVersion( -3156200273179464949LL );
    deviceHostConfigurationData1->SetHost( Guid( L"{E525AB0B-EC92-D432-2B4C-3749A7A4D5D0}" ) );
    deviceHostConfigurationData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    deviceHostConfigurationData1->SetHostname( L"Hostname" );
    deviceHostConfigurationData1->SetPort( -450516213L );
    deviceHostConfigurationData1->SetQueueName( L"QueueName" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *deviceHostConfigurationData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto deviceHostConfigurationData2 = std::reinterpret_pointer_cast<DeviceHostConfigurationData>( ReadDataFrom( source ) );
    bool equal = deviceHostConfigurationData2->IsEqualTo( *deviceHostConfigurationData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DoubleTimeseriesValueDataSerializationTest
BOOST_AUTO_TEST_CASE( DoubleTimeseriesValueDataSerializationTest )
{
    auto doubleTimeseriesValueData1 = std::make_shared<DoubleTimeseriesValueData>( );
    doubleTimeseriesValueData1->SetId( Guid( L"{C2761332-6A1D-1778-E81E-56B8436EC84C}" ) );
    doubleTimeseriesValueData1->SetRowVersion( 1691218336126735154LL );
    doubleTimeseriesValueData1->SetTimeseries( Guid( L"{C2761332-6A1D-1778-E81E-56B8436EC84C}" ) );
    doubleTimeseriesValueData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    doubleTimeseriesValueData1->SetValue( 1691218336126735 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *doubleTimeseriesValueData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto doubleTimeseriesValueData2 = std::reinterpret_pointer_cast<DoubleTimeseriesValueData>( ReadDataFrom( source ) );
    bool equal = doubleTimeseriesValueData2->IsEqualTo( *doubleTimeseriesValueData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/FacilityTypeDataSerializationTest
BOOST_AUTO_TEST_CASE( FacilityTypeDataSerializationTest )
{
    auto facilityTypeData1 = std::make_shared<FacilityTypeData>( );
    facilityTypeData1->SetId( Guid( L"{12C72C65-EDEE-92A1-4985-B77748E334A6}" ) );
    facilityTypeData1->SetRowVersion( -7880756266148615067LL );
    facilityTypeData1->SetName( L"Name" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *facilityTypeData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto facilityTypeData2 = std::reinterpret_pointer_cast<FacilityTypeData>( ReadDataFrom( source ) );
    bool equal = facilityTypeData2->IsEqualTo( *facilityTypeData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GeoPosition2DTimeseriesValueDataSerializationTest
BOOST_AUTO_TEST_CASE( GeoPosition2DTimeseriesValueDataSerializationTest )
{
    auto geoPosition2DTimeseriesValueData1 = std::make_shared<GeoPosition2DTimeseriesValueData>( );
    geoPosition2DTimeseriesValueData1->SetId( Guid( L"{C715E22D-B55D-0616-6068-ADBAE3A847B4}" ) );
    geoPosition2DTimeseriesValueData1->SetRowVersion( 438737428091888173LL );
    geoPosition2DTimeseriesValueData1->SetTimeseries( Guid( L"{C715E22D-B55D-0616-6068-ADBAE3A847B4}" ) );
    geoPosition2DTimeseriesValueData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    geoPosition2DTimeseriesValueData1->SetLatitude( 438737428091888.2 );
    geoPosition2DTimeseriesValueData1->SetLongitude( 438737428091888.2 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *geoPosition2DTimeseriesValueData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto geoPosition2DTimeseriesValueData2 = std::reinterpret_pointer_cast<GeoPosition2DTimeseriesValueData>( ReadDataFrom( source ) );
    bool equal = geoPosition2DTimeseriesValueData2->IsEqualTo( *geoPosition2DTimeseriesValueData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GeoPosition3DTimeseriesValueDataSerializationTest
BOOST_AUTO_TEST_CASE( GeoPosition3DTimeseriesValueDataSerializationTest )
{
    auto geoPosition3DTimeseriesValueData1 = std::make_shared<GeoPosition3DTimeseriesValueData>( );
    geoPosition3DTimeseriesValueData1->SetId( Guid( L"{9D5BFA33-A3E7-6871-168E-C5E7B9DA5FCC}" ) );
    geoPosition3DTimeseriesValueData1->SetRowVersion( 7525976667485633075LL );
    geoPosition3DTimeseriesValueData1->SetTimeseries( Guid( L"{9D5BFA33-A3E7-6871-168E-C5E7B9DA5FCC}" ) );
    geoPosition3DTimeseriesValueData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    geoPosition3DTimeseriesValueData1->SetLatitude( 7525976667485634 );
    geoPosition3DTimeseriesValueData1->SetLongitude( 7525976667485634 );
    geoPosition3DTimeseriesValueData1->SetAltitude( 7525976667485634 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *geoPosition3DTimeseriesValueData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto geoPosition3DTimeseriesValueData2 = std::reinterpret_pointer_cast<GeoPosition3DTimeseriesValueData>( ReadDataFrom( source ) );
    bool equal = geoPosition3DTimeseriesValueData2->IsEqualTo( *geoPosition3DTimeseriesValueData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GNSSDeviceCommandDataSerializationTest
BOOST_AUTO_TEST_CASE( GNSSDeviceCommandDataSerializationTest )
{
    auto gNSSDeviceCommandData1 = std::make_shared<GNSSDeviceCommandData>( );
    gNSSDeviceCommandData1->SetId( Guid( L"{16E46657-F2F0-53BB-CADD-4F0F682766EA}" ) );
    gNSSDeviceCommandData1->SetRowVersion( 6033683238783051351LL );
    gNSSDeviceCommandData1->SetGNSSDevice( Guid( L"{16E46657-F2F0-53BB-CADD-4F0F682766EA}" ) );
    gNSSDeviceCommandData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    gNSSDeviceCommandData1->SetDeviceCommandSourceType( DeviceCommandSourceType::Source );
    gNSSDeviceCommandData1->SetDeviceCommandSourceId( Guid( L"{16E46657-F2F0-53BB-CADD-4F0F682766EA}" ) );
    gNSSDeviceCommandData1->SetReply( Guid( L"{16E46657-F2F0-53BB-CADD-4F0F682766EA}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gNSSDeviceCommandData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gNSSDeviceCommandData2 = std::reinterpret_pointer_cast<GNSSDeviceCommandData>( ReadDataFrom( source ) );
    bool equal = gNSSDeviceCommandData2->IsEqualTo( *gNSSDeviceCommandData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GNSSDeviceCommandReplyDataSerializationTest
BOOST_AUTO_TEST_CASE( GNSSDeviceCommandReplyDataSerializationTest )
{
    auto gNSSDeviceCommandReplyData1 = std::make_shared<GNSSDeviceCommandReplyData>( );
    gNSSDeviceCommandReplyData1->SetId( Guid( L"{351EEA93-C2A0-2E72-744E-4305AC7857C9}" ) );
    gNSSDeviceCommandReplyData1->SetRowVersion( 3346951466431474323LL );
    gNSSDeviceCommandReplyData1->SetGNSSDevice( Guid( L"{351EEA93-C2A0-2E72-744E-4305AC7857C9}" ) );
    gNSSDeviceCommandReplyData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    gNSSDeviceCommandReplyData1->SetCommand( Guid( L"{351EEA93-C2A0-2E72-744E-4305AC7857C9}" ) );
    gNSSDeviceCommandReplyData1->SetStatus( DeviceCommandReplyStatus::Error );
    gNSSDeviceCommandReplyData1->SetMessage( L"Message" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gNSSDeviceCommandReplyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gNSSDeviceCommandReplyData2 = std::reinterpret_pointer_cast<GNSSDeviceCommandReplyData>( ReadDataFrom( source ) );
    bool equal = gNSSDeviceCommandReplyData2->IsEqualTo( *gNSSDeviceCommandReplyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GNSSDeviceConfigurationDataSerializationTest
BOOST_AUTO_TEST_CASE( GNSSDeviceConfigurationDataSerializationTest )
{
    auto gNSSDeviceConfigurationData1 = std::make_shared<GNSSDeviceConfigurationData>( );
    gNSSDeviceConfigurationData1->SetId( Guid( L"{3ED852BF-D8F3-84AF-21F5-1BCF7C1B4AFD}" ) );
    gNSSDeviceConfigurationData1->SetRowVersion( -8885645000535682369LL );
    gNSSDeviceConfigurationData1->SetGNSSDevice( Guid( L"{3ED852BF-D8F3-84AF-21F5-1BCF7C1B4AFD}" ) );
    gNSSDeviceConfigurationData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    gNSSDeviceConfigurationData1->SetDefaultLatitude( 9561099073173868 );
    gNSSDeviceConfigurationData1->SetDefaultLongitude( 9561099073173868 );
    gNSSDeviceConfigurationData1->SetDefaultAltitude( 9561099073173868 );
    gNSSDeviceConfigurationData1->SetLatitudeOffset( 9561099073173868 );
    gNSSDeviceConfigurationData1->SetLongitudeOffset( 9561099073173868 );
    gNSSDeviceConfigurationData1->SetAltitudeOffset( 9561099073173868 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gNSSDeviceConfigurationData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gNSSDeviceConfigurationData2 = std::reinterpret_pointer_cast<GNSSDeviceConfigurationData>( ReadDataFrom( source ) );
    bool equal = gNSSDeviceConfigurationData2->IsEqualTo( *gNSSDeviceConfigurationData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GuidTimeseriesValueDataSerializationTest
BOOST_AUTO_TEST_CASE( GuidTimeseriesValueDataSerializationTest )
{
    auto guidTimeseriesValueData1 = std::make_shared<GuidTimeseriesValueData>( );
    guidTimeseriesValueData1->SetId( Guid( L"{46558315-F37B-09FC-903F-CFDE62AAC1A8}" ) );
    guidTimeseriesValueData1->SetRowVersion( 719717751258972949LL );
    guidTimeseriesValueData1->SetTimeseries( Guid( L"{46558315-F37B-09FC-903F-CFDE62AAC1A8}" ) );
    guidTimeseriesValueData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    guidTimeseriesValueData1->SetValue( Guid( L"{46558315-F37B-09FC-903F-CFDE62AAC1A8}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *guidTimeseriesValueData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto guidTimeseriesValueData2 = std::reinterpret_pointer_cast<GuidTimeseriesValueData>( ReadDataFrom( source ) );
    bool equal = guidTimeseriesValueData2->IsEqualTo( *guidTimeseriesValueData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GyroDeviceCommandDataSerializationTest
BOOST_AUTO_TEST_CASE( GyroDeviceCommandDataSerializationTest )
{
    auto gyroDeviceCommandData1 = std::make_shared<GyroDeviceCommandData>( );
    gyroDeviceCommandData1->SetId( Guid( L"{0E55A9AC-70F5-F9E6-9F67-0EAF70AA9535}" ) );
    gyroDeviceCommandData1->SetRowVersion( -439539715812251220LL );
    gyroDeviceCommandData1->SetGyroDevice( Guid( L"{0E55A9AC-70F5-F9E6-9F67-0EAF70AA9535}" ) );
    gyroDeviceCommandData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    gyroDeviceCommandData1->SetDeviceCommandSourceType( DeviceCommandSourceType::Unknown );
    gyroDeviceCommandData1->SetDeviceCommandSourceId( Guid( L"{0E55A9AC-70F5-F9E6-9F67-0EAF70AA9535}" ) );
    gyroDeviceCommandData1->SetReply( Guid( L"{0E55A9AC-70F5-F9E6-9F67-0EAF70AA9535}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gyroDeviceCommandData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gyroDeviceCommandData2 = std::reinterpret_pointer_cast<GyroDeviceCommandData>( ReadDataFrom( source ) );
    bool equal = gyroDeviceCommandData2->IsEqualTo( *gyroDeviceCommandData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GyroDeviceCommandReplyDataSerializationTest
BOOST_AUTO_TEST_CASE( GyroDeviceCommandReplyDataSerializationTest )
{
    auto gyroDeviceCommandReplyData1 = std::make_shared<GyroDeviceCommandReplyData>( );
    gyroDeviceCommandReplyData1->SetId( Guid( L"{FE226ABE-7E8C-EA31-578C-7E317F44567D}" ) );
    gyroDeviceCommandReplyData1->SetRowVersion( -1571335650951402818LL );
    gyroDeviceCommandReplyData1->SetGyroDevice( Guid( L"{FE226ABE-7E8C-EA31-578C-7E317F44567D}" ) );
    gyroDeviceCommandReplyData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    gyroDeviceCommandReplyData1->SetCommand( Guid( L"{FE226ABE-7E8C-EA31-578C-7E317F44567D}" ) );
    gyroDeviceCommandReplyData1->SetStatus( DeviceCommandReplyStatus::NotImplemented );
    gyroDeviceCommandReplyData1->SetMessage( L"Message" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gyroDeviceCommandReplyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gyroDeviceCommandReplyData2 = std::reinterpret_pointer_cast<GyroDeviceCommandReplyData>( ReadDataFrom( source ) );
    bool equal = gyroDeviceCommandReplyData2->IsEqualTo( *gyroDeviceCommandReplyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GyroDeviceConfigurationDataSerializationTest
BOOST_AUTO_TEST_CASE( GyroDeviceConfigurationDataSerializationTest )
{
    auto gyroDeviceConfigurationData1 = std::make_shared<GyroDeviceConfigurationData>( );
    gyroDeviceConfigurationData1->SetId( Guid( L"{1BECC465-DE53-3C49-3C92-7BCAD83723A6}" ) );
    gyroDeviceConfigurationData1->SetRowVersion( 4344247764107707493LL );
    gyroDeviceConfigurationData1->SetGyroDevice( Guid( L"{1BECC465-DE53-3C49-3C92-7BCAD83723A6}" ) );
    gyroDeviceConfigurationData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    gyroDeviceConfigurationData1->SetDefaultHeadingTrueNorth( 4344247764107707.5 );
    gyroDeviceConfigurationData1->SetDefaultMagneticTrueNorth( 4344247764107707.5 );
    gyroDeviceConfigurationData1->SetHeadingTrueNorthOffset( 4344247764107707.5 );
    gyroDeviceConfigurationData1->SetHeadingMagneticNorthOffset( 4344247764107707.5 );
    gyroDeviceConfigurationData1->SetPitchTransducerName( L"PitchTransducerName" );
    gyroDeviceConfigurationData1->SetRollTransducerName( L"RollTransducerName" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gyroDeviceConfigurationData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gyroDeviceConfigurationData2 = std::reinterpret_pointer_cast<GyroDeviceConfigurationData>( ReadDataFrom( source ) );
    bool equal = gyroDeviceConfigurationData2->IsEqualTo( *gyroDeviceConfigurationData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CallsignDataSerializationTest
BOOST_AUTO_TEST_CASE( CallsignDataSerializationTest )
{
    auto callsignData1 = std::make_shared<CallsignData>( );
    callsignData1->SetId( Guid( L"{D17786FB-677E-6126-8664-E67E8BEE61DF}" ) );
    callsignData1->SetRowVersion( 7000396465171826427LL );
    callsignData1->SetIdentifier( L"Identifier" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *callsignData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto callsignData2 = std::reinterpret_pointer_cast<CallsignData>( ReadDataFrom( source ) );
    bool equal = callsignData2->IsEqualTo( *callsignData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/InternationalMaritimeOrganizationNumberDataSerializationTest
BOOST_AUTO_TEST_CASE( InternationalMaritimeOrganizationNumberDataSerializationTest )
{
    auto internationalMaritimeOrganizationNumberData1 = std::make_shared<InternationalMaritimeOrganizationNumberData>( );
    internationalMaritimeOrganizationNumberData1->SetId( Guid( L"{981538E8-05C6-4E9F-72F9-A06319A81C17}" ) );
    internationalMaritimeOrganizationNumberData1->SetRowVersion( 5665253206768564456LL );
    internationalMaritimeOrganizationNumberData1->SetIdentifier( 5665253206768564456LL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *internationalMaritimeOrganizationNumberData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto internationalMaritimeOrganizationNumberData2 = std::reinterpret_pointer_cast<InternationalMaritimeOrganizationNumberData>( ReadDataFrom( source ) );
    bool equal = internationalMaritimeOrganizationNumberData2->IsEqualTo( *internationalMaritimeOrganizationNumberData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/MaritimeMobileServiceIdentityDataSerializationTest
BOOST_AUTO_TEST_CASE( MaritimeMobileServiceIdentityDataSerializationTest )
{
    auto maritimeMobileServiceIdentityData1 = std::make_shared<MaritimeMobileServiceIdentityData>( );
    maritimeMobileServiceIdentityData1->SetId( Guid( L"{3F5D957C-F33F-B5BB-ADDD-CFFCFCBAA93E}" ) );
    maritimeMobileServiceIdentityData1->SetRowVersion( -5351416279228115588LL );
    maritimeMobileServiceIdentityData1->SetIdentifier( -5351416279228115588LL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *maritimeMobileServiceIdentityData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto maritimeMobileServiceIdentityData2 = std::reinterpret_pointer_cast<MaritimeMobileServiceIdentityData>( ReadDataFrom( source ) );
    bool equal = maritimeMobileServiceIdentityData2->IsEqualTo( *maritimeMobileServiceIdentityData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/NameDataSerializationTest
BOOST_AUTO_TEST_CASE( NameDataSerializationTest )
{
    auto nameData1 = std::make_shared<NameData>( );
    nameData1->SetId( Guid( L"{5C4D0804-63C5-C4E9-2397-C6A33AB21020}" ) );
    nameData1->SetRowVersion( -4257762273393833980LL );
    nameData1->SetText( L"Text" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *nameData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto nameData2 = std::reinterpret_pointer_cast<NameData>( ReadDataFrom( source ) );
    bool equal = nameData2->IsEqualTo( *nameData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int16TimeseriesValueDataSerializationTest
BOOST_AUTO_TEST_CASE( Int16TimeseriesValueDataSerializationTest )
{
    auto int16TimeseriesValueData1 = std::make_shared<Int16TimeseriesValueData>( );
    int16TimeseriesValueData1->SetId( Guid( L"{B94AD405-0355-A9BD-95BD-C0AA9D522BA0}" ) );
    int16TimeseriesValueData1->SetRowVersion( -6215808243985624059LL );
    int16TimeseriesValueData1->SetTimeseries( Guid( L"{B94AD405-0355-A9BD-95BD-C0AA9D522BA0}" ) );
    int16TimeseriesValueData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    int16TimeseriesValueData1->SetValue( -11259 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int16TimeseriesValueData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int16TimeseriesValueData2 = std::reinterpret_pointer_cast<Int16TimeseriesValueData>( ReadDataFrom( source ) );
    bool equal = int16TimeseriesValueData2->IsEqualTo( *int16TimeseriesValueData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int32TimeseriesValueDataSerializationTest
BOOST_AUTO_TEST_CASE( Int32TimeseriesValueDataSerializationTest )
{
    auto int32TimeseriesValueData1 = std::make_shared<Int32TimeseriesValueData>( );
    int32TimeseriesValueData1->SetId( Guid( L"{38DCBC02-9C28-2570-A40E-39141C3B3D40}" ) );
    int32TimeseriesValueData1->SetRowVersion( 2697827873361542146LL );
    int32TimeseriesValueData1->SetTimeseries( Guid( L"{38DCBC02-9C28-2570-A40E-39141C3B3D40}" ) );
    int32TimeseriesValueData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    int32TimeseriesValueData1->SetValue( 953990146L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int32TimeseriesValueData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int32TimeseriesValueData2 = std::reinterpret_pointer_cast<Int32TimeseriesValueData>( ReadDataFrom( source ) );
    bool equal = int32TimeseriesValueData2->IsEqualTo( *int32TimeseriesValueData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int64TimeseriesValueDataSerializationTest
BOOST_AUTO_TEST_CASE( Int64TimeseriesValueDataSerializationTest )
{
    auto int64TimeseriesValueData1 = std::make_shared<Int64TimeseriesValueData>( );
    int64TimeseriesValueData1->SetId( Guid( L"{DD2DE745-E72A-DFD1-FB8B-E754BBB4E7A2}" ) );
    int64TimeseriesValueData1->SetRowVersion( -2318818161833679035LL );
    int64TimeseriesValueData1->SetTimeseries( Guid( L"{DD2DE745-E72A-DFD1-FB8B-E754BBB4E7A2}" ) );
    int64TimeseriesValueData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    int64TimeseriesValueData1->SetValue( -2318818161833679035LL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int64TimeseriesValueData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int64TimeseriesValueData2 = std::reinterpret_pointer_cast<Int64TimeseriesValueData>( ReadDataFrom( source ) );
    bool equal = int64TimeseriesValueData2->IsEqualTo( *int64TimeseriesValueData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BaseStationDataSerializationTest
BOOST_AUTO_TEST_CASE( BaseStationDataSerializationTest )
{
    auto baseStationData1 = std::make_shared<BaseStationData>( );
    baseStationData1->SetId( Guid( L"{416FD82E-C84F-09AB-90D5-13F282F61B74}" ) );
    baseStationData1->SetRowVersion( 696870810084694062LL );
    baseStationData1->SetName( L"Name" );
    baseStationData1->SetType( Guid( L"{416FD82E-C84F-09AB-90D5-13F282F61B74}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *baseStationData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto baseStationData2 = std::reinterpret_pointer_cast<BaseStationData>( ReadDataFrom( source ) );
    bool equal = baseStationData2->IsEqualTo( *baseStationData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CameraDataSerializationTest
BOOST_AUTO_TEST_CASE( CameraDataSerializationTest )
{
    auto cameraData1 = std::make_shared<CameraData>( );
    cameraData1->SetId( Guid( L"{347C29F0-9117-BC0B-3DD0-89E82C3E940F}" ) );
    cameraData1->SetRowVersion( -4896660640984454672LL );
    cameraData1->SetHost( Guid( L"{347C29F0-9117-BC0B-3DD0-89E82C3E940F}" ) );
    cameraData1->SetName( L"Name" );
    cameraData1->SetDescription( L"Description" );
    cameraData1->SetEnabledTimeseries( Guid( L"{347C29F0-9117-BC0B-3DD0-89E82C3E940F}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *cameraData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto cameraData2 = std::reinterpret_pointer_cast<CameraData>( ReadDataFrom( source ) );
    bool equal = cameraData2->IsEqualTo( *cameraData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GNSSDeviceDataSerializationTest
BOOST_AUTO_TEST_CASE( GNSSDeviceDataSerializationTest )
{
    auto gNSSDeviceData1 = std::make_shared<GNSSDeviceData>( );
    gNSSDeviceData1->SetId( Guid( L"{5F25A83C-CA3E-191C-9838-537CFAA4153C}" ) );
    gNSSDeviceData1->SetRowVersion( 1809543519529183292LL );
    gNSSDeviceData1->SetHost( Guid( L"{5F25A83C-CA3E-191C-9838-537CFAA4153C}" ) );
    gNSSDeviceData1->SetName( L"Name" );
    gNSSDeviceData1->SetDescription( L"Description" );
    gNSSDeviceData1->SetEnabledTimeseries( Guid( L"{5F25A83C-CA3E-191C-9838-537CFAA4153C}" ) );
    gNSSDeviceData1->SetLatitudeTimeseries( Guid( L"{5F25A83C-CA3E-191C-9838-537CFAA4153C}" ) );
    gNSSDeviceData1->SetLongitudeTimeseries( Guid( L"{5F25A83C-CA3E-191C-9838-537CFAA4153C}" ) );
    gNSSDeviceData1->SetAltitudeTimeseries( Guid( L"{5F25A83C-CA3E-191C-9838-537CFAA4153C}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gNSSDeviceData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gNSSDeviceData2 = std::reinterpret_pointer_cast<GNSSDeviceData>( ReadDataFrom( source ) );
    bool equal = gNSSDeviceData2->IsEqualTo( *gNSSDeviceData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GyroDeviceDataSerializationTest
BOOST_AUTO_TEST_CASE( GyroDeviceDataSerializationTest )
{
    auto gyroDeviceData1 = std::make_shared<GyroDeviceData>( );
    gyroDeviceData1->SetId( Guid( L"{90098F8B-0830-813D-81BC-100C0990F1D1}" ) );
    gyroDeviceData1->SetRowVersion( -9134135464569499765LL );
    gyroDeviceData1->SetHost( Guid( L"{90098F8B-0830-813D-81BC-100C0990F1D1}" ) );
    gyroDeviceData1->SetName( L"Name" );
    gyroDeviceData1->SetDescription( L"Description" );
    gyroDeviceData1->SetEnabledTimeseries( Guid( L"{90098F8B-0830-813D-81BC-100C0990F1D1}" ) );
    gyroDeviceData1->SetHeadingTrueNorthTimeseries( Guid( L"{90098F8B-0830-813D-81BC-100C0990F1D1}" ) );
    gyroDeviceData1->SetHeadingMagneticNorthTimeseries( Guid( L"{90098F8B-0830-813D-81BC-100C0990F1D1}" ) );
    gyroDeviceData1->SetPitchTimeseries( Guid( L"{90098F8B-0830-813D-81BC-100C0990F1D1}" ) );
    gyroDeviceData1->SetRateOfTurnTimeseries( Guid( L"{90098F8B-0830-813D-81BC-100C0990F1D1}" ) );
    gyroDeviceData1->SetRollTimeseries( Guid( L"{90098F8B-0830-813D-81BC-100C0990F1D1}" ) );
    gyroDeviceData1->SetCourseTimeseries( Guid( L"{90098F8B-0830-813D-81BC-100C0990F1D1}" ) );
    gyroDeviceData1->SetSpeedTimeseries( Guid( L"{90098F8B-0830-813D-81BC-100C0990F1D1}" ) );
    gyroDeviceData1->SetGNSSDevice( Guid( L"{90098F8B-0830-813D-81BC-100C0990F1D1}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gyroDeviceData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gyroDeviceData2 = std::reinterpret_pointer_cast<GyroDeviceData>( ReadDataFrom( source ) );
    bool equal = gyroDeviceData2->IsEqualTo( *gyroDeviceData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LineInputDeviceDataSerializationTest
BOOST_AUTO_TEST_CASE( LineInputDeviceDataSerializationTest )
{
    auto lineInputDeviceData1 = std::make_shared<LineInputDeviceData>( );
    lineInputDeviceData1->SetId( Guid( L"{67363DC8-DFCA-71BB-8EDD-FB53E66CBC13}" ) );
    lineInputDeviceData1->SetRowVersion( 8195390007338745288LL );
    lineInputDeviceData1->SetHost( Guid( L"{67363DC8-DFCA-71BB-8EDD-FB53E66CBC13}" ) );
    lineInputDeviceData1->SetName( L"Name" );
    lineInputDeviceData1->SetDescription( L"Description" );
    lineInputDeviceData1->SetEnabledTimeseries( Guid( L"{67363DC8-DFCA-71BB-8EDD-FB53E66CBC13}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *lineInputDeviceData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto lineInputDeviceData2 = std::reinterpret_pointer_cast<LineInputDeviceData>( ReadDataFrom( source ) );
    bool equal = lineInputDeviceData2->IsEqualTo( *lineInputDeviceData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/OilspillDetectorDataSerializationTest
BOOST_AUTO_TEST_CASE( OilspillDetectorDataSerializationTest )
{
    auto oilspillDetectorData1 = std::make_shared<OilspillDetectorData>( );
    oilspillDetectorData1->SetId( Guid( L"{6762EAC2-C40D-4745-E2A2-23B0E6465743}" ) );
    oilspillDetectorData1->SetRowVersion( 5135726511934073538LL );
    oilspillDetectorData1->SetHost( Guid( L"{6762EAC2-C40D-4745-E2A2-23B0E6465743}" ) );
    oilspillDetectorData1->SetName( L"Name" );
    oilspillDetectorData1->SetDescription( L"Description" );
    oilspillDetectorData1->SetEnabledTimeseries( Guid( L"{6762EAC2-C40D-4745-E2A2-23B0E6465743}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *oilspillDetectorData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto oilspillDetectorData2 = std::reinterpret_pointer_cast<OilspillDetectorData>( ReadDataFrom( source ) );
    bool equal = oilspillDetectorData2->IsEqualTo( *oilspillDetectorData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadioDataSerializationTest
BOOST_AUTO_TEST_CASE( RadioDataSerializationTest )
{
    auto radioData1 = std::make_shared<RadioData>( );
    radioData1->SetId( Guid( L"{1F1F0C51-46A7-93C3-C9C3-62E5F8F8308A}" ) );
    radioData1->SetRowVersion( -7799312446079955887LL );
    radioData1->SetHost( Guid( L"{1F1F0C51-46A7-93C3-C9C3-62E5F8F8308A}" ) );
    radioData1->SetName( L"Name" );
    radioData1->SetDescription( L"Description" );
    radioData1->SetEnabledTimeseries( Guid( L"{1F1F0C51-46A7-93C3-C9C3-62E5F8F8308A}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radioData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radioData2 = std::reinterpret_pointer_cast<RadioData>( ReadDataFrom( source ) );
    bool equal = radioData2->IsEqualTo( *radioData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadomeDataSerializationTest
BOOST_AUTO_TEST_CASE( RadomeDataSerializationTest )
{
    auto radomeData1 = std::make_shared<RadomeData>( );
    radomeData1->SetId( Guid( L"{C90238B6-481B-8EAD-71B5-12D893401C6D}" ) );
    radomeData1->SetRowVersion( -8165791265179158346LL );
    radomeData1->SetHost( Guid( L"{C90238B6-481B-8EAD-71B5-12D893401C6D}" ) );
    radomeData1->SetName( L"Name" );
    radomeData1->SetDescription( L"Description" );
    radomeData1->SetEnabledTimeseries( Guid( L"{C90238B6-481B-8EAD-71B5-12D893401C6D}" ) );
    radomeData1->SetRadar( Guid( L"{C90238B6-481B-8EAD-71B5-12D893401C6D}" ) );
    radomeData1->SetPressureTimeseries( Guid( L"{C90238B6-481B-8EAD-71B5-12D893401C6D}" ) );
    radomeData1->SetTemperatureTimeseries( Guid( L"{C90238B6-481B-8EAD-71B5-12D893401C6D}" ) );
    radomeData1->SetDewPointTimeseries( Guid( L"{C90238B6-481B-8EAD-71B5-12D893401C6D}" ) );
    radomeData1->SetStatusTimeseries( Guid( L"{C90238B6-481B-8EAD-71B5-12D893401C6D}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radomeData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radomeData2 = std::reinterpret_pointer_cast<RadomeData>( ReadDataFrom( source ) );
    bool equal = radomeData2->IsEqualTo( *radomeData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisTransceiverDataSerializationTest
BOOST_AUTO_TEST_CASE( AisTransceiverDataSerializationTest )
{
    auto aisTransceiverData1 = std::make_shared<AisTransceiverData>( );
    aisTransceiverData1->SetId( Guid( L"{0E1554DF-9523-44BD-22BD-A9C470A82AFB}" ) );
    aisTransceiverData1->SetRowVersion( 4953279142970086623LL );
    aisTransceiverData1->SetHost( Guid( L"{0E1554DF-9523-44BD-22BD-A9C470A82AFB}" ) );
    aisTransceiverData1->SetName( L"Name" );
    aisTransceiverData1->SetDescription( L"Description" );
    aisTransceiverData1->SetEnabledTimeseries( Guid( L"{0E1554DF-9523-44BD-22BD-A9C470A82AFB}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisTransceiverData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisTransceiverData2 = std::reinterpret_pointer_cast<AisTransceiverData>( ReadDataFrom( source ) );
    bool equal = aisTransceiverData2->IsEqualTo( *aisTransceiverData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarDataSerializationTest )
{
    auto radarData1 = std::make_shared<RadarData>( );
    radarData1->SetId( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );
    radarData1->SetRowVersion( 4778241506108406668LL );
    radarData1->SetHost( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );
    radarData1->SetName( L"Name" );
    radarData1->SetDescription( L"Description" );
    radarData1->SetEnabledTimeseries( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );
    radarData1->SetSaveSettingsTimeseries( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );
    radarData1->SetPowerOnTimeseries( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );
    radarData1->SetTrackingOnTimeseries( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );
    radarData1->SetRadarPulseTimeseries( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );
    radarData1->SetTuningTimeseries( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );
    radarData1->SetBlankSector1Timeseries( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );
    radarData1->SetSector1StartTimeseries( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );
    radarData1->SetSector1EndTimeseries( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );
    radarData1->SetBlankSector2Timeseries( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );
    radarData1->SetSector2StartTimeseries( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );
    radarData1->SetSector2EndTimeseries( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );
    radarData1->SetEnableAutomaticFrequencyControlTimeseries( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );
    radarData1->SetAzimuthOffsetTimeseries( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );
    radarData1->SetEnableSensitivityTimeControlTimeseries( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );
    radarData1->SetAutomaticSensitivityTimeControlTimeseries( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );
    radarData1->SetSensitivityTimeControlLevelTimeseries( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );
    radarData1->SetEnableFastTimeConstantTimeseries( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );
    radarData1->SetFastTimeConstantLevelTimeseries( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );
    radarData1->SetFastTimeConstantModeTimeseries( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );
    radarData1->SetLatitudeTimeseries( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );
    radarData1->SetLongitudeTimeseries( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );
    radarData1->SetRadome( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );
    radarData1->SetGNSSDevice( Guid( L"{669E7B8C-B955-424F-42F2-9DAA6679DE31}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarData2 = std::reinterpret_pointer_cast<RadarData>( ReadDataFrom( source ) );
    bool equal = radarData2->IsEqualTo( *radarData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/WeatherStationDataSerializationTest
BOOST_AUTO_TEST_CASE( WeatherStationDataSerializationTest )
{
    auto weatherStationData1 = std::make_shared<WeatherStationData>( );
    weatherStationData1->SetId( Guid( L"{AA00879C-AA90-E1F7-87EF-55095500E139}" ) );
    weatherStationData1->SetRowVersion( -2164073557624060004LL );
    weatherStationData1->SetHost( Guid( L"{AA00879C-AA90-E1F7-87EF-55095500E139}" ) );
    weatherStationData1->SetName( L"Name" );
    weatherStationData1->SetDescription( L"Description" );
    weatherStationData1->SetEnabledTimeseries( Guid( L"{AA00879C-AA90-E1F7-87EF-55095500E139}" ) );
    weatherStationData1->SetBarometricPressureTimeseries( Guid( L"{AA00879C-AA90-E1F7-87EF-55095500E139}" ) );
    weatherStationData1->SetAirTemperatureTimeseries( Guid( L"{AA00879C-AA90-E1F7-87EF-55095500E139}" ) );
    weatherStationData1->SetWaterTemperatureTimeseries( Guid( L"{AA00879C-AA90-E1F7-87EF-55095500E139}" ) );
    weatherStationData1->SetRelativeHumidityTimeseries( Guid( L"{AA00879C-AA90-E1F7-87EF-55095500E139}" ) );
    weatherStationData1->SetAbsoluteHumidityTimeseries( Guid( L"{AA00879C-AA90-E1F7-87EF-55095500E139}" ) );
    weatherStationData1->SetDewPointTimeseries( Guid( L"{AA00879C-AA90-E1F7-87EF-55095500E139}" ) );
    weatherStationData1->SetWindDirectionTimeseries( Guid( L"{AA00879C-AA90-E1F7-87EF-55095500E139}" ) );
    weatherStationData1->SetWindSpeedTimeseries( Guid( L"{AA00879C-AA90-E1F7-87EF-55095500E139}" ) );
    weatherStationData1->SetGyro( Guid( L"{AA00879C-AA90-E1F7-87EF-55095500E139}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *weatherStationData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto weatherStationData2 = std::reinterpret_pointer_cast<WeatherStationData>( ReadDataFrom( source ) );
    bool equal = weatherStationData2->IsEqualTo( *weatherStationData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/FacilityDataSerializationTest
BOOST_AUTO_TEST_CASE( FacilityDataSerializationTest )
{
    auto facilityData1 = std::make_shared<FacilityData>( );
    facilityData1->SetId( Guid( L"{E5843450-575C-678E-E671-EA3AA7212C0A}" ) );
    facilityData1->SetRowVersion( 7461997689098744912LL );
    facilityData1->SetName( L"Name" );
    facilityData1->SetType( Guid( L"{E5843450-575C-678E-E671-EA3AA7212C0A}" ) );
    facilityData1->SetLongitude( 7461997689098745 );
    facilityData1->SetLatitude( 7461997689098745 );
    facilityData1->SetAltitude( 7461997689098745 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *facilityData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto facilityData2 = std::reinterpret_pointer_cast<FacilityData>( ReadDataFrom( source ) );
    bool equal = facilityData2->IsEqualTo( *facilityData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AircraftDataSerializationTest
BOOST_AUTO_TEST_CASE( AircraftDataSerializationTest )
{
    auto aircraftData1 = std::make_shared<AircraftData>( );
    aircraftData1->SetId( Guid( L"{6166D8B6-B9DA-5EE5-7AA7-9D5B86661B6D}" ) );
    aircraftData1->SetRowVersion( 6838075956820105398LL );
    aircraftData1->SetName( L"Name" );
    aircraftData1->SetType( Guid( L"{6166D8B6-B9DA-5EE5-7AA7-9D5B86661B6D}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aircraftData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aircraftData2 = std::reinterpret_pointer_cast<AircraftData>( ReadDataFrom( source ) );
    bool equal = aircraftData2->IsEqualTo( *aircraftData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisAidToNavigationDataSerializationTest
BOOST_AUTO_TEST_CASE( AisAidToNavigationDataSerializationTest )
{
    auto aisAidToNavigationData1 = std::make_shared<AisAidToNavigationData>( );
    aisAidToNavigationData1->SetId( Guid( L"{16DDCFB2-2EE7-3B43-DCC2-74E768BBF34D}" ) );
    aisAidToNavigationData1->SetRowVersion( 4270308441733320626LL );
    aisAidToNavigationData1->SetName( L"Name" );
    aisAidToNavigationData1->SetMMSI( Guid( L"{16DDCFB2-2EE7-3B43-DCC2-74E768BBF34D}" ) );
    aisAidToNavigationData1->SetNavigationalAidType( NavigationalAidType::BeaconSafeWater );
    aisAidToNavigationData1->SetPosition( Guid( L"{16DDCFB2-2EE7-3B43-DCC2-74E768BBF34D}" ) );
    aisAidToNavigationData1->SetIsVirtual( false );
    aisAidToNavigationData1->SetToBow( 383635378L );
    aisAidToNavigationData1->SetToStern( 383635378L );
    aisAidToNavigationData1->SetToPort( 383635378L );
    aisAidToNavigationData1->SetToStarboard( 383635378L );
    aisAidToNavigationData1->SetOffPositionTimeseries( Guid( L"{16DDCFB2-2EE7-3B43-DCC2-74E768BBF34D}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisAidToNavigationData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisAidToNavigationData2 = std::reinterpret_pointer_cast<AisAidToNavigationData>( ReadDataFrom( source ) );
    bool equal = aisAidToNavigationData2->IsEqualTo( *aisAidToNavigationData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/VehicleDataSerializationTest
BOOST_AUTO_TEST_CASE( VehicleDataSerializationTest )
{
    auto vehicleData1 = std::make_shared<VehicleData>( );
    vehicleData1->SetId( Guid( L"{65C36569-1718-3990-9C09-E818A6C3A696}" ) );
    vehicleData1->SetRowVersion( 4147840650362185065LL );
    vehicleData1->SetName( L"Name" );
    vehicleData1->SetType( Guid( L"{65C36569-1718-3990-9C09-E818A6C3A696}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *vehicleData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto vehicleData2 = std::reinterpret_pointer_cast<VehicleData>( ReadDataFrom( source ) );
    bool equal = vehicleData2->IsEqualTo( *vehicleData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/VesselDataSerializationTest
BOOST_AUTO_TEST_CASE( VesselDataSerializationTest )
{
    auto vesselData1 = std::make_shared<VesselData>( );
    vesselData1->SetId( Guid( L"{9DD08333-9688-8B47-D1E2-6911B90BC1CC}" ) );
    vesselData1->SetRowVersion( -8410588265583705293LL );
    vesselData1->SetName( L"Name" );
    vesselData1->SetType( Guid( L"{9DD08333-9688-8B47-D1E2-6911B90BC1CC}" ) );
    vesselData1->SetToBow( -1647279309L );
    vesselData1->SetToStern( -1647279309L );
    vesselData1->SetToPort( -1647279309L );
    vesselData1->SetToStarboard( -1647279309L );
    vesselData1->SetDraughtTimeseries( Guid( L"{9DD08333-9688-8B47-D1E2-6911B90BC1CC}" ) );
    vesselData1->SetPersonsOnBoardTimeseries( Guid( L"{9DD08333-9688-8B47-D1E2-6911B90BC1CC}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *vesselData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto vesselData2 = std::reinterpret_pointer_cast<VesselData>( ReadDataFrom( source ) );
    bool equal = vesselData2->IsEqualTo( *vesselData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ItemIdentityLinkDataSerializationTest
BOOST_AUTO_TEST_CASE( ItemIdentityLinkDataSerializationTest )
{
    auto itemIdentityLinkData1 = std::make_shared<ItemIdentityLinkData>( );
    itemIdentityLinkData1->SetId( Guid( L"{7F8E5AF6-1EE2-4720-E204-7847FE715A6F}" ) );
    itemIdentityLinkData1->SetRowVersion( 5125130334099102454LL );
    itemIdentityLinkData1->SetItem( Guid( L"{7F8E5AF6-1EE2-4720-E204-7847FE715A6F}" ) );
    itemIdentityLinkData1->SetIdentity( Guid( L"{7F8E5AF6-1EE2-4720-E204-7847FE715A6F}" ) );
    itemIdentityLinkData1->SetStart( DateTime( 1, 1, 1, 14, 37, 6 ) );
    itemIdentityLinkData1->SetEnd( DateTime( 1, 1, 1, 14, 37, 6 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *itemIdentityLinkData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto itemIdentityLinkData2 = std::reinterpret_pointer_cast<ItemIdentityLinkData>( ReadDataFrom( source ) );
    bool equal = itemIdentityLinkData2->IsEqualTo( *itemIdentityLinkData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ItemParentChildLinkDataSerializationTest
BOOST_AUTO_TEST_CASE( ItemParentChildLinkDataSerializationTest )
{
    auto itemParentChildLinkData1 = std::make_shared<ItemParentChildLinkData>( );
    itemParentChildLinkData1->SetId( Guid( L"{49E45A37-F96C-0493-20C9-9F3692275AEC}" ) );
    itemParentChildLinkData1->SetRowVersion( 329881441219664439LL );
    itemParentChildLinkData1->SetParent( Guid( L"{49E45A37-F96C-0493-20C9-9F3692275AEC}" ) );
    itemParentChildLinkData1->SetChild( Guid( L"{49E45A37-F96C-0493-20C9-9F3692275AEC}" ) );
    itemParentChildLinkData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *itemParentChildLinkData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto itemParentChildLinkData2 = std::reinterpret_pointer_cast<ItemParentChildLinkData>( ReadDataFrom( source ) );
    bool equal = itemParentChildLinkData2->IsEqualTo( *itemParentChildLinkData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LineInputDeviceCommandDataSerializationTest
BOOST_AUTO_TEST_CASE( LineInputDeviceCommandDataSerializationTest )
{
    auto lineInputDeviceCommandData1 = std::make_shared<LineInputDeviceCommandData>( );
    lineInputDeviceCommandData1->SetId( Guid( L"{628CD2DB-52F1-4F5F-F2FA-4A8F46314BDB}" ) );
    lineInputDeviceCommandData1->SetRowVersion( 5719381248477811419LL );
    lineInputDeviceCommandData1->SetLineInputDevice( Guid( L"{628CD2DB-52F1-4F5F-F2FA-4A8F46314BDB}" ) );
    lineInputDeviceCommandData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    lineInputDeviceCommandData1->SetDeviceCommandSourceType( DeviceCommandSourceType::Source );
    lineInputDeviceCommandData1->SetDeviceCommandSourceId( Guid( L"{628CD2DB-52F1-4F5F-F2FA-4A8F46314BDB}" ) );
    lineInputDeviceCommandData1->SetReply( Guid( L"{628CD2DB-52F1-4F5F-F2FA-4A8F46314BDB}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *lineInputDeviceCommandData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto lineInputDeviceCommandData2 = std::reinterpret_pointer_cast<LineInputDeviceCommandData>( ReadDataFrom( source ) );
    bool equal = lineInputDeviceCommandData2->IsEqualTo( *lineInputDeviceCommandData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LineInputDeviceCommandReplyDataSerializationTest
BOOST_AUTO_TEST_CASE( LineInputDeviceCommandReplyDataSerializationTest )
{
    auto lineInputDeviceCommandReplyData1 = std::make_shared<LineInputDeviceCommandReplyData>( );
    lineInputDeviceCommandReplyData1->SetId( Guid( L"{C1D214AC-9A66-FF50-FF0A-5966834B2835}" ) );
    lineInputDeviceCommandReplyData1->SetRowVersion( -49369829771963220LL );
    lineInputDeviceCommandReplyData1->SetLineInputDevice( Guid( L"{C1D214AC-9A66-FF50-FF0A-5966834B2835}" ) );
    lineInputDeviceCommandReplyData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    lineInputDeviceCommandReplyData1->SetCommand( Guid( L"{C1D214AC-9A66-FF50-FF0A-5966834B2835}" ) );
    lineInputDeviceCommandReplyData1->SetStatus( DeviceCommandReplyStatus::Unknown );
    lineInputDeviceCommandReplyData1->SetMessage( L"Message" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *lineInputDeviceCommandReplyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto lineInputDeviceCommandReplyData2 = std::reinterpret_pointer_cast<LineInputDeviceCommandReplyData>( ReadDataFrom( source ) );
    bool equal = lineInputDeviceCommandReplyData2->IsEqualTo( *lineInputDeviceCommandReplyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LineInputDeviceConfigurationDataSerializationTest
BOOST_AUTO_TEST_CASE( LineInputDeviceConfigurationDataSerializationTest )
{
    auto lineInputDeviceConfigurationData1 = std::make_shared<LineInputDeviceConfigurationData>( );
    lineInputDeviceConfigurationData1->SetId( Guid( L"{C0009AA8-BD74-CF77-F3EE-BD2E03005915}" ) );
    lineInputDeviceConfigurationData1->SetRowVersion( -3497118276494779736LL );
    lineInputDeviceConfigurationData1->SetLineInputDevice( Guid( L"{C0009AA8-BD74-CF77-F3EE-BD2E03005915}" ) );
    lineInputDeviceConfigurationData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    lineInputDeviceConfigurationData1->SetStoreReceivedSentences( false );
    lineInputDeviceConfigurationData1->SetStoreSentMessages( false );
    lineInputDeviceConfigurationData1->SetStoreUnsentMessages( false );
    lineInputDeviceConfigurationData1->SetNMEA( false );
    lineInputDeviceConfigurationData1->SetStrictNMEA( false );
    lineInputDeviceConfigurationData1->SetConnectionType( LineInputDeviceConnectionType::Unknown );
    lineInputDeviceConfigurationData1->SetUdpReceivePort( -1073702232L );
    lineInputDeviceConfigurationData1->SetUdpSendHostname( L"UdpSendHostname" );
    lineInputDeviceConfigurationData1->SetUdpSendPort( -1073702232L );
    lineInputDeviceConfigurationData1->SetTcpHostname( L"TcpHostname" );
    lineInputDeviceConfigurationData1->SetTcpPort( -1073702232L );
    lineInputDeviceConfigurationData1->SetUseHttpLogin( false );
    lineInputDeviceConfigurationData1->SetLoginHostname( L"LoginHostname" );
    lineInputDeviceConfigurationData1->SetLoginPort( -1073702232L );
    lineInputDeviceConfigurationData1->SetUserName( L"UserName" );
    lineInputDeviceConfigurationData1->SetPassword( L"Password" );
    lineInputDeviceConfigurationData1->SetComPort( L"ComPort" );
    lineInputDeviceConfigurationData1->SetBaudRate( -1073702232L );
    lineInputDeviceConfigurationData1->SetDataBits( -1073702232L );
    lineInputDeviceConfigurationData1->SetDiscardNull( false );
    lineInputDeviceConfigurationData1->SetDtrEnable( false );
    lineInputDeviceConfigurationData1->SetHandshake( Handshake::None );
    lineInputDeviceConfigurationData1->SetNewLine( L"NewLine" );
    lineInputDeviceConfigurationData1->SetParity( Parity::None );
    lineInputDeviceConfigurationData1->SetParityReplace( 168 );
    lineInputDeviceConfigurationData1->SetReadBufferSize( -1073702232L );
    lineInputDeviceConfigurationData1->SetReadTimeout( TimeSpan( -516494779736LL ) );
    lineInputDeviceConfigurationData1->SetReceivedBytesThreshold( -1073702232L );
    lineInputDeviceConfigurationData1->SetRtsEnable( false );
    lineInputDeviceConfigurationData1->SetStopBits( StopBits::None );
    lineInputDeviceConfigurationData1->SetWriteBufferSize( -1073702232L );
    lineInputDeviceConfigurationData1->SetWriteTimeout( TimeSpan( -516494779736LL ) );
    lineInputDeviceConfigurationData1->SetPairedComPort( L"PairedComPort" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *lineInputDeviceConfigurationData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto lineInputDeviceConfigurationData2 = std::reinterpret_pointer_cast<LineInputDeviceConfigurationData>( ReadDataFrom( source ) );
    bool equal = lineInputDeviceConfigurationData2->IsEqualTo( *lineInputDeviceConfigurationData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LineInputMessageRoutingDataSerializationTest
BOOST_AUTO_TEST_CASE( LineInputMessageRoutingDataSerializationTest )
{
    auto lineInputMessageRoutingData1 = std::make_shared<LineInputMessageRoutingData>( );
    lineInputMessageRoutingData1->SetId( Guid( L"{8BE6CF76-4CDD-BBC9-DD93-32BBD167F36E}" ) );
    lineInputMessageRoutingData1->SetRowVersion( -4915313003879542922LL );
    lineInputMessageRoutingData1->SetLineInputDevice( Guid( L"{8BE6CF76-4CDD-BBC9-DD93-32BBD167F36E}" ) );
    lineInputMessageRoutingData1->SetType( L"Type" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *lineInputMessageRoutingData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto lineInputMessageRoutingData2 = std::reinterpret_pointer_cast<LineInputMessageRoutingData>( ReadDataFrom( source ) );
    bool equal = lineInputMessageRoutingData2->IsEqualTo( *lineInputMessageRoutingData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LineInputMessageRoutingDestinationDataSerializationTest
BOOST_AUTO_TEST_CASE( LineInputMessageRoutingDestinationDataSerializationTest )
{
    auto lineInputMessageRoutingDestinationData1 = std::make_shared<LineInputMessageRoutingDestinationData>( );
    lineInputMessageRoutingDestinationData1->SetId( Guid( L"{2EF5AC12-D26D-9FF4-F92F-4BB674AF3548}" ) );
    lineInputMessageRoutingDestinationData1->SetRowVersion( -6920675360980489198LL );
    lineInputMessageRoutingDestinationData1->SetRouting( Guid( L"{2EF5AC12-D26D-9FF4-F92F-4BB674AF3548}" ) );
    lineInputMessageRoutingDestinationData1->SetListener( Guid( L"{2EF5AC12-D26D-9FF4-F92F-4BB674AF3548}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *lineInputMessageRoutingDestinationData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto lineInputMessageRoutingDestinationData2 = std::reinterpret_pointer_cast<LineInputMessageRoutingDestinationData>( ReadDataFrom( source ) );
    bool equal = lineInputMessageRoutingDestinationData2->IsEqualTo( *lineInputMessageRoutingDestinationData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LineInputWhiteListEntryDataSerializationTest
BOOST_AUTO_TEST_CASE( LineInputWhiteListEntryDataSerializationTest )
{
    auto lineInputWhiteListEntryData1 = std::make_shared<LineInputWhiteListEntryData>( );
    lineInputWhiteListEntryData1->SetId( Guid( L"{327EA7A3-FFDF-36F9-6C9F-FFFB4C7EE5C5}" ) );
    lineInputWhiteListEntryData1->SetRowVersion( 3961478681339013027LL );
    lineInputWhiteListEntryData1->SetLineInputDevice( Guid( L"{327EA7A3-FFDF-36F9-6C9F-FFFB4C7EE5C5}" ) );
    lineInputWhiteListEntryData1->SetHostName( L"HostName" );
    lineInputWhiteListEntryData1->SetPort( 847161251L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *lineInputWhiteListEntryData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto lineInputWhiteListEntryData2 = std::reinterpret_pointer_cast<LineInputWhiteListEntryData>( ReadDataFrom( source ) );
    bool equal = lineInputWhiteListEntryData2->IsEqualTo( *lineInputWhiteListEntryData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LogApplicationDataSerializationTest
BOOST_AUTO_TEST_CASE( LogApplicationDataSerializationTest )
{
    auto logApplicationData1 = std::make_shared<LogApplicationData>( );
    logApplicationData1->SetId( Guid( L"{6B1912D1-86E8-E10B-87D0-6117D698488B}" ) );
    logApplicationData1->SetRowVersion( -2230540857644608815LL );
    logApplicationData1->SetName( L"Name" );
    logApplicationData1->SetDescription( L"Description" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *logApplicationData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto logApplicationData2 = std::reinterpret_pointer_cast<LogApplicationData>( ReadDataFrom( source ) );
    bool equal = logApplicationData2->IsEqualTo( *logApplicationData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LogApplicationConfigurationDataSerializationTest
BOOST_AUTO_TEST_CASE( LogApplicationConfigurationDataSerializationTest )
{
    auto logApplicationConfigurationData1 = std::make_shared<LogApplicationConfigurationData>( );
    logApplicationConfigurationData1->SetId( Guid( L"{CC4F6DA5-6ECC-B5D6-AD6B-763333F2B6A5}" ) );
    logApplicationConfigurationData1->SetRowVersion( -5343962081948373595LL );
    logApplicationConfigurationData1->SetApplication( Guid( L"{CC4F6DA5-6ECC-B5D6-AD6B-763333F2B6A5}" ) );
    logApplicationConfigurationData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    logApplicationConfigurationData1->SetFinest( false );
    logApplicationConfigurationData1->SetFiner( false );
    logApplicationConfigurationData1->SetFine( false );
    logApplicationConfigurationData1->SetInfo( false );
    logApplicationConfigurationData1->SetNotice( false );
    logApplicationConfigurationData1->SetWarn( false );
    logApplicationConfigurationData1->SetError( false );
    logApplicationConfigurationData1->SetSevere( false );
    logApplicationConfigurationData1->SetCritical( false );
    logApplicationConfigurationData1->SetAlert( false );
    logApplicationConfigurationData1->SetFatal( false );
    logApplicationConfigurationData1->SetEmergency( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *logApplicationConfigurationData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto logApplicationConfigurationData2 = std::reinterpret_pointer_cast<LogApplicationConfigurationData>( ReadDataFrom( source ) );
    bool equal = logApplicationConfigurationData2->IsEqualTo( *logApplicationConfigurationData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LogHostDataSerializationTest
BOOST_AUTO_TEST_CASE( LogHostDataSerializationTest )
{
    auto logHostData1 = std::make_shared<LogHostData>( );
    logHostData1->SetId( Guid( L"{DE9C7421-1369-3D83-BCC1-C8967B392E84}" ) );
    logHostData1->SetRowVersion( 4432407803689989153LL );
    logHostData1->SetComputerName( L"ComputerName" );
    logHostData1->SetDescription( L"Description" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *logHostData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto logHostData2 = std::reinterpret_pointer_cast<LogHostData>( ReadDataFrom( source ) );
    bool equal = logHostData2->IsEqualTo( *logHostData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LogHostConfigurationDataSerializationTest
BOOST_AUTO_TEST_CASE( LogHostConfigurationDataSerializationTest )
{
    auto logHostConfigurationData1 = std::make_shared<LogHostConfigurationData>( );
    logHostConfigurationData1->SetId( Guid( L"{417B144E-3AC8-DAA0-5B05-5C1382DE2872}" ) );
    logHostConfigurationData1->SetRowVersion( -2693087945401101234LL );
    logHostConfigurationData1->SetHost( Guid( L"{417B144E-3AC8-DAA0-5B05-5C1382DE2872}" ) );
    logHostConfigurationData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    logHostConfigurationData1->SetFinest( false );
    logHostConfigurationData1->SetFiner( false );
    logHostConfigurationData1->SetFine( false );
    logHostConfigurationData1->SetInfo( false );
    logHostConfigurationData1->SetNotice( false );
    logHostConfigurationData1->SetWarn( false );
    logHostConfigurationData1->SetError( false );
    logHostConfigurationData1->SetSevere( false );
    logHostConfigurationData1->SetCritical( false );
    logHostConfigurationData1->SetAlert( false );
    logHostConfigurationData1->SetFatal( false );
    logHostConfigurationData1->SetEmergency( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *logHostConfigurationData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto logHostConfigurationData2 = std::reinterpret_pointer_cast<LogHostConfigurationData>( ReadDataFrom( source ) );
    bool equal = logHostConfigurationData2->IsEqualTo( *logHostConfigurationData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LogLocationDataSerializationTest
BOOST_AUTO_TEST_CASE( LogLocationDataSerializationTest )
{
    auto logLocationData1 = std::make_shared<LogLocationData>( );
    logLocationData1->SetId( Guid( L"{BE5DBC0F-C27F-12B7-48ED-43FE7DBA3DF0}" ) );
    logLocationData1->SetRowVersion( 1348760467331202063LL );
    logLocationData1->SetFileName( L"FileName" );
    logLocationData1->SetLineNumber( -1101153265L );
    logLocationData1->SetNamespace( L"Namespace" );
    logLocationData1->SetClassName( L"ClassName" );
    logLocationData1->SetMethodName( L"MethodName" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *logLocationData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto logLocationData2 = std::reinterpret_pointer_cast<LogLocationData>( ReadDataFrom( source ) );
    bool equal = logLocationData2->IsEqualTo( *logLocationData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LogProcessDataSerializationTest
BOOST_AUTO_TEST_CASE( LogProcessDataSerializationTest )
{
    auto logProcessData1 = std::make_shared<LogProcessData>( );
    logProcessData1->SetId( Guid( L"{7EC79CED-9256-C54D-A3B2-496A7EE339B7}" ) );
    logProcessData1->SetRowVersion( -4229563574839173907LL );
    logProcessData1->SetApplication( Guid( L"{7EC79CED-9256-C54D-A3B2-496A7EE339B7}" ) );
    logProcessData1->SetHost( Guid( L"{7EC79CED-9256-C54D-A3B2-496A7EE339B7}" ) );
    logProcessData1->SetStarted( DateTime( 1, 1, 1, 14, 37, 6 ) );
    logProcessData1->SetStopped( DateTime( 1, 1, 1, 14, 37, 6 ) );
    logProcessData1->SetProcessId( -4229563574839173907LL );
    logProcessData1->SetPath( L"Path" );
    logProcessData1->SetIdentity( L"Identity" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *logProcessData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto logProcessData2 = std::reinterpret_pointer_cast<LogProcessData>( ReadDataFrom( source ) );
    bool equal = logProcessData2->IsEqualTo( *logProcessData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LogRecordDataSerializationTest
BOOST_AUTO_TEST_CASE( LogRecordDataSerializationTest )
{
    auto logRecordData1 = std::make_shared<LogRecordData>( );
    logRecordData1->SetId( Guid( L"{28B6F7B7-3766-03C6-C063-EC66146DEFED}" ) );
    logRecordData1->SetRowVersion( 271965739411765175LL );
    logRecordData1->SetThread( Guid( L"{28B6F7B7-3766-03C6-C063-EC66146DEFED}" ) );
    logRecordData1->SetSequenceNumber( 271965739411765175LL );
    logRecordData1->SetLevel( LogLevel::Warn );
    logRecordData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    logRecordData1->SetDepth( 683079607L );
    logRecordData1->SetLocation( Guid( L"{28B6F7B7-3766-03C6-C063-EC66146DEFED}" ) );
    logRecordData1->SetMessage( L"Message" );
    logRecordData1->SetExceptionString( L"ExceptionString" );
    logRecordData1->SetPropertiesData( { {'P','r','o','p','e','r','t','i','e','s','D','a','t','a'} } );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *logRecordData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto logRecordData2 = std::reinterpret_pointer_cast<LogRecordData>( ReadDataFrom( source ) );
    bool equal = logRecordData2->IsEqualTo( *logRecordData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LogThreadDataSerializationTest
BOOST_AUTO_TEST_CASE( LogThreadDataSerializationTest )
{
    auto logThreadData1 = std::make_shared<LogThreadData>( );
    logThreadData1->SetId( Guid( L"{04816AF0-B0B9-19C1-9883-0D9D2081560F}" ) );
    logThreadData1->SetRowVersion( 1855958830144383728LL );
    logThreadData1->SetProcess( Guid( L"{04816AF0-B0B9-19C1-9883-0D9D2081560F}" ) );
    logThreadData1->SetStarted( DateTime( 1, 1, 1, 14, 37, 6 ) );
    logThreadData1->SetStopped( DateTime( 1, 1, 1, 14, 37, 6 ) );
    logThreadData1->SetThreadId( 1855958830144383728LL );
    logThreadData1->SetName( L"Name" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *logThreadData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto logThreadData2 = std::reinterpret_pointer_cast<LogThreadData>( ReadDataFrom( source ) );
    bool equal = logThreadData2->IsEqualTo( *logThreadData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/LogTraceEntryDataSerializationTest
BOOST_AUTO_TEST_CASE( LogTraceEntryDataSerializationTest )
{
    auto logTraceEntryData1 = std::make_shared<LogTraceEntryData>( );
    logTraceEntryData1->SetId( Guid( L"{4BF89F5F-7C98-DBAB-DBD5-3E19D21FF9FA}" ) );
    logTraceEntryData1->SetRowVersion( -2617861764834353313LL );
    logTraceEntryData1->SetThread( Guid( L"{4BF89F5F-7C98-DBAB-DBD5-3E19D21FF9FA}" ) );
    logTraceEntryData1->SetSequenceNumber( -2617861764834353313LL );
    logTraceEntryData1->SetLocation( Guid( L"{4BF89F5F-7C98-DBAB-DBD5-3E19D21FF9FA}" ) );
    logTraceEntryData1->SetDepth( 1274584927L );
    logTraceEntryData1->SetEntered( DateTime( 1, 1, 1, 14, 37, 6 ) );
    logTraceEntryData1->SetEnded( DateTime( 1, 1, 1, 14, 37, 6 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *logTraceEntryData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto logTraceEntryData2 = std::reinterpret_pointer_cast<LogTraceEntryData>( ReadDataFrom( source ) );
    bool equal = logTraceEntryData2->IsEqualTo( *logTraceEntryData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/MapElementDataSerializationTest
BOOST_AUTO_TEST_CASE( MapElementDataSerializationTest )
{
    auto mapElementData1 = std::make_shared<MapElementData>( );
    mapElementData1->SetId( Guid( L"{6E1EB3AF-BD0A-A344-C522-BD507678CDF5}" ) );
    mapElementData1->SetRowVersion( -6682008094616144977LL );
    mapElementData1->SetItem( Guid( L"{6E1EB3AF-BD0A-A344-C522-BD507678CDF5}" ) );
    mapElementData1->SetElementType( MapElementType::Jpeg );
    mapElementData1->SetLatitude( 11764735979093406 );
    mapElementData1->SetLongitude( 11764735979093406 );
    mapElementData1->SetAngle( 11764735979093406 );
    mapElementData1->SetLeft( 11764735979093406 );
    mapElementData1->SetTop( 11764735979093406 );
    mapElementData1->SetWidth( 11764735979093406 );
    mapElementData1->SetHeight( 11764735979093406 );
    mapElementData1->SetLabel( L"Label" );
    mapElementData1->SetData( { {'D','a','t','a'} } );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *mapElementData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto mapElementData2 = std::reinterpret_pointer_cast<MapElementData>( ReadDataFrom( source ) );
    bool equal = mapElementData2->IsEqualTo( *mapElementData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/MapInfoDataSerializationTest
BOOST_AUTO_TEST_CASE( MapInfoDataSerializationTest )
{
    auto mapInfoData1 = std::make_shared<MapInfoData>( );
    mapInfoData1->SetId( Guid( L"{EA12A4F5-45A0-1A32-584C-A205574825AF}" ) );
    mapInfoData1->SetRowVersion( 1887647751245833461LL );
    mapInfoData1->SetScale( -367876875L );
    mapInfoData1->SetLatitude( 1887647751245833.5 );
    mapInfoData1->SetLongitude( 1887647751245833.5 );
    mapInfoData1->SetNorthWestLatitude( 1887647751245833.5 );
    mapInfoData1->SetNorthWestLongitude( 1887647751245833.5 );
    mapInfoData1->SetSouthEastLatitude( 1887647751245833.5 );
    mapInfoData1->SetSouthEastLongitude( 1887647751245833.5 );
    mapInfoData1->SetImage( { {'I','m','a','g','e'} } );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *mapInfoData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto mapInfoData2 = std::reinterpret_pointer_cast<MapInfoData>( ReadDataFrom( source ) );
    bool equal = mapInfoData2->IsEqualTo( *mapInfoData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/MapServiceOptionsDataSerializationTest
BOOST_AUTO_TEST_CASE( MapServiceOptionsDataSerializationTest )
{
    auto mapServiceOptionsData1 = std::make_shared<MapServiceOptionsData>( );
    mapServiceOptionsData1->SetId( Guid( L"{20E6AB7D-3887-E6FB-67DF-1CE10467D5BE}" ) );
    mapServiceOptionsData1->SetRowVersion( -1802785072808023171LL );
    mapServiceOptionsData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    mapServiceOptionsData1->SetIpAddress( L"IpAddress" );
    mapServiceOptionsData1->SetPort( 551988093L );
    mapServiceOptionsData1->SetImageScaleFactorX( 16643959000901528 );
    mapServiceOptionsData1->SetImageOffsetX( 16643959000901528 );
    mapServiceOptionsData1->SetImageScaleFactorY( 16643959000901528 );
    mapServiceOptionsData1->SetImageOffsetY( 16643959000901528 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *mapServiceOptionsData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto mapServiceOptionsData2 = std::reinterpret_pointer_cast<MapServiceOptionsData>( ReadDataFrom( source ) );
    bool equal = mapServiceOptionsData2->IsEqualTo( *mapServiceOptionsData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/MaritimeIdentificationDigitsDataSerializationTest
BOOST_AUTO_TEST_CASE( MaritimeIdentificationDigitsDataSerializationTest )
{
    auto maritimeIdentificationDigitsData1 = std::make_shared<MaritimeIdentificationDigitsData>( );
    maritimeIdentificationDigitsData1->SetId( Guid( L"{33551387-00CF-4F0D-F2B0-00F3CCAAC8E1}" ) );
    maritimeIdentificationDigitsData1->SetRowVersion( 5696209993612989319LL );
    maritimeIdentificationDigitsData1->SetCode( 861213575L );
    maritimeIdentificationDigitsData1->SetCountry( Guid( L"{33551387-00CF-4F0D-F2B0-00F3CCAAC8E1}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *maritimeIdentificationDigitsData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto maritimeIdentificationDigitsData2 = std::reinterpret_pointer_cast<MaritimeIdentificationDigitsData>( ReadDataFrom( source ) );
    bool equal = maritimeIdentificationDigitsData2->IsEqualTo( *maritimeIdentificationDigitsData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/MediaProxySessionDataSerializationTest
BOOST_AUTO_TEST_CASE( MediaProxySessionDataSerializationTest )
{
    auto mediaProxySessionData1 = std::make_shared<MediaProxySessionData>( );
    mediaProxySessionData1->SetId( Guid( L"{F09CC571-97B0-5F8C-FA31-E90D0F39A38E}" ) );
    mediaProxySessionData1->SetRowVersion( 6885044716549490033LL );
    mediaProxySessionData1->SetService( Guid( L"{F09CC571-97B0-5F8C-FA31-E90D0F39A38E}" ) );
    mediaProxySessionData1->SetName( L"Name" );
    mediaProxySessionData1->SetEnabledTimeseries( Guid( L"{F09CC571-97B0-5F8C-FA31-E90D0F39A38E}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *mediaProxySessionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto mediaProxySessionData2 = std::reinterpret_pointer_cast<MediaProxySessionData>( ReadDataFrom( source ) );
    bool equal = mediaProxySessionData2->IsEqualTo( *mediaProxySessionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/MediaProxySessionFileDataSerializationTest
BOOST_AUTO_TEST_CASE( MediaProxySessionFileDataSerializationTest )
{
    auto mediaProxySessionFileData1 = std::make_shared<MediaProxySessionFileData>( );
    mediaProxySessionFileData1->SetId( Guid( L"{8E158396-1682-3D78-BC1E-684171A8C169}" ) );
    mediaProxySessionFileData1->SetRowVersion( 4429314983504216982LL );
    mediaProxySessionFileData1->SetProxySession( Guid( L"{8E158396-1682-3D78-BC1E-684171A8C169}" ) );
    mediaProxySessionFileData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    mediaProxySessionFileData1->SetStreamName( L"StreamName" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *mediaProxySessionFileData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto mediaProxySessionFileData2 = std::reinterpret_pointer_cast<MediaProxySessionFileData>( ReadDataFrom( source ) );
    bool equal = mediaProxySessionFileData2->IsEqualTo( *mediaProxySessionFileData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/MediaProxySessionOptionsDataSerializationTest
BOOST_AUTO_TEST_CASE( MediaProxySessionOptionsDataSerializationTest )
{
    auto mediaProxySessionOptionsData1 = std::make_shared<MediaProxySessionOptionsData>( );
    mediaProxySessionOptionsData1->SetId( Guid( L"{EDD260D0-4C90-FC60-3F06-3209B74B060B}" ) );
    mediaProxySessionOptionsData1->SetRowVersion( -261124593038499632LL );
    mediaProxySessionOptionsData1->SetProxySession( Guid( L"{EDD260D0-4C90-FC60-3F06-3209B74B060B}" ) );
    mediaProxySessionOptionsData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    mediaProxySessionOptionsData1->SetSourceStreamUrl( L"SourceStreamUrl" );
    mediaProxySessionOptionsData1->SetStreamName( L"StreamName" );
    mediaProxySessionOptionsData1->SetMode( MediaProxySessionMode::Unknown );
    mediaProxySessionOptionsData1->SetTunnelOverHTTPPortNumber( -304979760L );
    mediaProxySessionOptionsData1->SetUsername( L"Username" );
    mediaProxySessionOptionsData1->SetPassword( L"Password" );
    mediaProxySessionOptionsData1->SetRecorderPortNumber( -304979760L );
    mediaProxySessionOptionsData1->SetSessionType( MediaProxySessionType::AC3Audio );
    mediaProxySessionOptionsData1->SetMaxFileTime( TimeSpan( -465038499632LL ) );
    mediaProxySessionOptionsData1->SetMaxFileRetention( TimeSpan( -465038499632LL ) );
    mediaProxySessionOptionsData1->SetVideoDirectory( L"VideoDirectory" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *mediaProxySessionOptionsData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto mediaProxySessionOptionsData2 = std::reinterpret_pointer_cast<MediaProxySessionOptionsData>( ReadDataFrom( source ) );
    bool equal = mediaProxySessionOptionsData2->IsEqualTo( *mediaProxySessionOptionsData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/MediaServiceDataSerializationTest
BOOST_AUTO_TEST_CASE( MediaServiceDataSerializationTest )
{
    auto mediaServiceData1 = std::make_shared<MediaServiceData>( );
    mediaServiceData1->SetId( Guid( L"{96926964-A9F1-8383-C1C1-958F69499626}" ) );
    mediaServiceData1->SetRowVersion( -8970139177713505948LL );
    mediaServiceData1->SetEnabledTimeseries( Guid( L"{96926964-A9F1-8383-C1C1-958F69499626}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *mediaServiceData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto mediaServiceData2 = std::reinterpret_pointer_cast<MediaServiceData>( ReadDataFrom( source ) );
    bool equal = mediaServiceData2->IsEqualTo( *mediaServiceData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/MediaServiceOptionsDataSerializationTest
BOOST_AUTO_TEST_CASE( MediaServiceOptionsDataSerializationTest )
{
    auto mediaServiceOptionsData1 = std::make_shared<MediaServiceOptionsData>( );
    mediaServiceOptionsData1->SetId( Guid( L"{0A8CEF15-C6AB-65EC-A637-63D55031F7A8}" ) );
    mediaServiceOptionsData1->SetRowVersion( 7344463530253152021LL );
    mediaServiceOptionsData1->SetMediaService( Guid( L"{0A8CEF15-C6AB-65EC-A637-63D55031F7A8}" ) );
    mediaServiceOptionsData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    mediaServiceOptionsData1->SetRtspPortNumber( 177008405L );
    mediaServiceOptionsData1->SetHttpPortNumber( 177008405L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *mediaServiceOptionsData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto mediaServiceOptionsData2 = std::reinterpret_pointer_cast<MediaServiceOptionsData>( ReadDataFrom( source ) );
    bool equal = mediaServiceOptionsData2->IsEqualTo( *mediaServiceOptionsData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ElementTypeDataSerializationTest
BOOST_AUTO_TEST_CASE( ElementTypeDataSerializationTest )
{
    auto elementTypeData1 = std::make_shared<ElementTypeData>( );
    elementTypeData1->SetId( Guid( L"{7DD5914D-321B-4C6A-3256-4CD8BEAB89B2}" ) );
    elementTypeData1->SetRowVersion( 5506268588070506829LL );
    elementTypeData1->SetNamespace( Guid( L"{7DD5914D-321B-4C6A-3256-4CD8BEAB89B2}" ) );
    elementTypeData1->SetName( L"Name" );
    elementTypeData1->SetDescription( L"Description" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *elementTypeData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto elementTypeData2 = std::reinterpret_pointer_cast<ElementTypeData>( ReadDataFrom( source ) );
    bool equal = elementTypeData2->IsEqualTo( *elementTypeData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/NamespaceDataSerializationTest
BOOST_AUTO_TEST_CASE( NamespaceDataSerializationTest )
{
    auto namespaceData1 = std::make_shared<NamespaceData>( );
    namespaceData1->SetId( Guid( L"{22456B64-FD81-0793-E0C9-BF8144A2D626}" ) );
    namespaceData1->SetRowVersion( 546058710909545316LL );
    namespaceData1->SetNamespace( Guid( L"{22456B64-FD81-0793-E0C9-BF8144A2D626}" ) );
    namespaceData1->SetName( L"Name" );
    namespaceData1->SetDescription( L"Description" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *namespaceData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto namespaceData2 = std::reinterpret_pointer_cast<NamespaceData>( ReadDataFrom( source ) );
    bool equal = namespaceData2->IsEqualTo( *namespaceData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/OilspillDataSerializationTest
BOOST_AUTO_TEST_CASE( OilspillDataSerializationTest )
{
    auto oilspillData1 = std::make_shared<OilspillData>( );
    oilspillData1->SetId( Guid( L"{26B499A1-6E33-9B82-D941-76CC642D9985}" ) );
    oilspillData1->SetRowVersion( -7241104084886578783LL );
    oilspillData1->SetOilSpillDetector( Guid( L"{26B499A1-6E33-9B82-D941-76CC642D9985}" ) );
    oilspillData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    oilspillData1->SetOilArea( 11205639988822972 );
    oilspillData1->SetShape( { {'S','h','a','p','e'} } );
    oilspillData1->SetBSI( { {'B','S','I'} } );
    oilspillData1->SetOil( { {'O','i','l'} } );
    oilspillData1->SetTrace( { {'T','r','a','c','e'} } );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *oilspillData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto oilspillData2 = std::reinterpret_pointer_cast<OilspillData>( ReadDataFrom( source ) );
    bool equal = oilspillData2->IsEqualTo( *oilspillData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/OilspillDetectorCommandDataSerializationTest
BOOST_AUTO_TEST_CASE( OilspillDetectorCommandDataSerializationTest )
{
    auto oilspillDetectorCommandData1 = std::make_shared<OilspillDetectorCommandData>( );
    oilspillDetectorCommandData1->SetId( Guid( L"{8A1149DB-D849-B2A1-4D85-1B92518892DB}" ) );
    oilspillDetectorCommandData1->SetRowVersion( -5574937053347362341LL );
    oilspillDetectorCommandData1->SetOilSpillDetector( Guid( L"{8A1149DB-D849-B2A1-4D85-1B92518892DB}" ) );
    oilspillDetectorCommandData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    oilspillDetectorCommandData1->SetDeviceCommandSourceType( DeviceCommandSourceType::Source );
    oilspillDetectorCommandData1->SetDeviceCommandSourceId( Guid( L"{8A1149DB-D849-B2A1-4D85-1B92518892DB}" ) );
    oilspillDetectorCommandData1->SetReply( Guid( L"{8A1149DB-D849-B2A1-4D85-1B92518892DB}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *oilspillDetectorCommandData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto oilspillDetectorCommandData2 = std::reinterpret_pointer_cast<OilspillDetectorCommandData>( ReadDataFrom( source ) );
    bool equal = oilspillDetectorCommandData2->IsEqualTo( *oilspillDetectorCommandData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/OilspillDetectorCommandReplyDataSerializationTest
BOOST_AUTO_TEST_CASE( OilspillDetectorCommandReplyDataSerializationTest )
{
    auto oilspillDetectorCommandReplyData1 = std::make_shared<OilspillDetectorCommandReplyData>( );
    oilspillDetectorCommandReplyData1->SetId( Guid( L"{D6B67409-ED21-4C98-3219-B7846B6D2E90}" ) );
    oilspillDetectorCommandReplyData1->SetRowVersion( 5519422072934528009LL );
    oilspillDetectorCommandReplyData1->SetOilSpillDetector( Guid( L"{D6B67409-ED21-4C98-3219-B7846B6D2E90}" ) );
    oilspillDetectorCommandReplyData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    oilspillDetectorCommandReplyData1->SetCommand( Guid( L"{D6B67409-ED21-4C98-3219-B7846B6D2E90}" ) );
    oilspillDetectorCommandReplyData1->SetStatus( DeviceCommandReplyStatus::Ok );
    oilspillDetectorCommandReplyData1->SetMessage( L"Message" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *oilspillDetectorCommandReplyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto oilspillDetectorCommandReplyData2 = std::reinterpret_pointer_cast<OilspillDetectorCommandReplyData>( ReadDataFrom( source ) );
    bool equal = oilspillDetectorCommandReplyData2->IsEqualTo( *oilspillDetectorCommandReplyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/OilspillDetectorConfigurationDataSerializationTest
BOOST_AUTO_TEST_CASE( OilspillDetectorConfigurationDataSerializationTest )
{
    auto oilspillDetectorConfigurationData1 = std::make_shared<OilspillDetectorConfigurationData>( );
    oilspillDetectorConfigurationData1->SetId( Guid( L"{DD33DEEC-EF80-070C-E030-F701BBCC7B37}" ) );
    oilspillDetectorConfigurationData1->SetRowVersion( 508044194732039916LL );
    oilspillDetectorConfigurationData1->SetOilSpillDetector( Guid( L"{DD33DEEC-EF80-070C-E030-F701BBCC7B37}" ) );
    oilspillDetectorConfigurationData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    oilspillDetectorConfigurationData1->SetRange( 508044194732039.94 );
    oilspillDetectorConfigurationData1->SetStartAngle( 508044194732039.94 );
    oilspillDetectorConfigurationData1->SetEndAngle( 508044194732039.94 );
    oilspillDetectorConfigurationData1->SetStartRange( 508044194732039.94 );
    oilspillDetectorConfigurationData1->SetEndRange( 508044194732039.94 );
    oilspillDetectorConfigurationData1->SetUpdateRate( -583803156L );
    oilspillDetectorConfigurationData1->SetStatusSendTime( TimeSpan( 98732039916LL ) );
    oilspillDetectorConfigurationData1->SetDrawBorder( false );
    oilspillDetectorConfigurationData1->SetColors( { {'C','o','l','o','r','s'} } );
    oilspillDetectorConfigurationData1->SetSendToServer( false );
    oilspillDetectorConfigurationData1->SetDirectory( L"Directory" );
    oilspillDetectorConfigurationData1->SetTransparentWater( false );
    oilspillDetectorConfigurationData1->SetSavePictures( false );
    oilspillDetectorConfigurationData1->SetSendAsTarget( false );
    oilspillDetectorConfigurationData1->SetWriteLog( false );
    oilspillDetectorConfigurationData1->SetTargetFilePrefix( L"TargetFilePrefix" );
    oilspillDetectorConfigurationData1->SetTargetMMSI( Guid( L"{DD33DEEC-EF80-070C-E030-F701BBCC7B37}" ) );
    oilspillDetectorConfigurationData1->SetLatitude( 508044194732039.94 );
    oilspillDetectorConfigurationData1->SetLongitude( 508044194732039.94 );
    oilspillDetectorConfigurationData1->SetTestSourceEnabled( false );
    oilspillDetectorConfigurationData1->SetProxyServer( L"ProxyServer" );
    oilspillDetectorConfigurationData1->SetUseProxyServer( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *oilspillDetectorConfigurationData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto oilspillDetectorConfigurationData2 = std::reinterpret_pointer_cast<OilspillDetectorConfigurationData>( ReadDataFrom( source ) );
    bool equal = oilspillDetectorConfigurationData2->IsEqualTo( *oilspillDetectorConfigurationData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Position2DTimeseriesValueDataSerializationTest
BOOST_AUTO_TEST_CASE( Position2DTimeseriesValueDataSerializationTest )
{
    auto position2DTimeseriesValueData1 = std::make_shared<Position2DTimeseriesValueData>( );
    position2DTimeseriesValueData1->SetId( Guid( L"{0E8E2416-D3F0-2D94-B429-CB0F70712468}" ) );
    position2DTimeseriesValueData1->SetRowVersion( 3284483056249742358LL );
    position2DTimeseriesValueData1->SetTimeseries( Guid( L"{0E8E2416-D3F0-2D94-B429-CB0F70712468}" ) );
    position2DTimeseriesValueData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    position2DTimeseriesValueData1->SetX( 3284483056249742.5 );
    position2DTimeseriesValueData1->SetY( 3284483056249742.5 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *position2DTimeseriesValueData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto position2DTimeseriesValueData2 = std::reinterpret_pointer_cast<Position2DTimeseriesValueData>( ReadDataFrom( source ) );
    bool equal = position2DTimeseriesValueData2->IsEqualTo( *position2DTimeseriesValueData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Position3DTimeseriesValueDataSerializationTest
BOOST_AUTO_TEST_CASE( Position3DTimeseriesValueDataSerializationTest )
{
    auto position3DTimeseriesValueData1 = std::make_shared<Position3DTimeseriesValueData>( );
    position3DTimeseriesValueData1->SetId( Guid( L"{270243BC-C575-4E4D-72B2-A3AEE440C23D}" ) );
    position3DTimeseriesValueData1->SetRowVersion( 5642383015121404860LL );
    position3DTimeseriesValueData1->SetTimeseries( Guid( L"{270243BC-C575-4E4D-72B2-A3AEE440C23D}" ) );
    position3DTimeseriesValueData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    position3DTimeseriesValueData1->SetX( 5642383015121405 );
    position3DTimeseriesValueData1->SetY( 5642383015121405 );
    position3DTimeseriesValueData1->SetZ( 5642383015121405 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *position3DTimeseriesValueData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto position3DTimeseriesValueData2 = std::reinterpret_pointer_cast<Position3DTimeseriesValueData>( ReadDataFrom( source ) );
    bool equal = position3DTimeseriesValueData2->IsEqualTo( *position3DTimeseriesValueData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ProcessTrackValueResultDataSerializationTest
BOOST_AUTO_TEST_CASE( ProcessTrackValueResultDataSerializationTest )
{
    auto processTrackValueResultData1 = std::make_shared<ProcessTrackValueResultData>( );
    processTrackValueResultData1->SetId( Guid( L"{76103E7F-D776-7399-CE99-EB6E6E087CFE}" ) );
    processTrackValueResultData1->SetRowVersion( 8329925889585331839LL );
    processTrackValueResultData1->SetCreatedNewTrack( false );
    processTrackValueResultData1->SetTrackId( Guid( L"{76103E7F-D776-7399-CE99-EB6E6E087CFE}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *processTrackValueResultData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto processTrackValueResultData2 = std::reinterpret_pointer_cast<ProcessTrackValueResultData>( ReadDataFrom( source ) );
    bool equal = processTrackValueResultData2->IsEqualTo( *processTrackValueResultData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BinaryPropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( BinaryPropertyDataSerializationTest )
{
    auto binaryPropertyData1 = std::make_shared<BinaryPropertyData>( );
    binaryPropertyData1->SetId( Guid( L"{747B8E31-4658-5C2A-3A54-621A2EDE718C}" ) );
    binaryPropertyData1->SetRowVersion( 6641197946236538417LL );
    binaryPropertyData1->SetElement( Guid( L"{747B8E31-4658-5C2A-3A54-621A2EDE718C}" ) );
    binaryPropertyData1->SetDefinition( Guid( L"{747B8E31-4658-5C2A-3A54-621A2EDE718C}" ) );
    binaryPropertyData1->SetValue( { {'V','a','l','u','e'} } );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *binaryPropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto binaryPropertyData2 = std::reinterpret_pointer_cast<BinaryPropertyData>( ReadDataFrom( source ) );
    bool equal = binaryPropertyData2->IsEqualTo( *binaryPropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BooleanPropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( BooleanPropertyDataSerializationTest )
{
    auto booleanPropertyData1 = std::make_shared<BooleanPropertyData>( );
    booleanPropertyData1->SetId( Guid( L"{5164C464-F83B-6804-1620-1FDC8A262326}" ) );
    booleanPropertyData1->SetRowVersion( 7495388613503665252LL );
    booleanPropertyData1->SetElement( Guid( L"{5164C464-F83B-6804-1620-1FDC8A262326}" ) );
    booleanPropertyData1->SetDefinition( Guid( L"{5164C464-F83B-6804-1620-1FDC8A262326}" ) );
    booleanPropertyData1->SetValue( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *booleanPropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto booleanPropertyData2 = std::reinterpret_pointer_cast<BooleanPropertyData>( ReadDataFrom( source ) );
    bool equal = booleanPropertyData2->IsEqualTo( *booleanPropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BytePropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( BytePropertyDataSerializationTest )
{
    auto bytePropertyData1 = std::make_shared<BytePropertyData>( );
    bytePropertyData1->SetId( Guid( L"{D8C7B657-C0AD-2F51-F48A-03B51BE36DEA}" ) );
    bytePropertyData1->SetRowVersion( 3409718245795018327LL );
    bytePropertyData1->SetElement( Guid( L"{D8C7B657-C0AD-2F51-F48A-03B51BE36DEA}" ) );
    bytePropertyData1->SetDefinition( Guid( L"{D8C7B657-C0AD-2F51-F48A-03B51BE36DEA}" ) );
    bytePropertyData1->SetValue( 87 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *bytePropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto bytePropertyData2 = std::reinterpret_pointer_cast<BytePropertyData>( ReadDataFrom( source ) );
    bool equal = bytePropertyData2->IsEqualTo( *bytePropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DateTimePropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( DateTimePropertyDataSerializationTest )
{
    auto dateTimePropertyData1 = std::make_shared<DateTimePropertyData>( );
    dateTimePropertyData1->SetId( Guid( L"{87260D24-A955-FE46-7F62-95AAE164B024}" ) );
    dateTimePropertyData1->SetRowVersion( -124225754901377756LL );
    dateTimePropertyData1->SetElement( Guid( L"{87260D24-A955-FE46-7F62-95AAE164B024}" ) );
    dateTimePropertyData1->SetDefinition( Guid( L"{87260D24-A955-FE46-7F62-95AAE164B024}" ) );
    dateTimePropertyData1->SetValue( DateTime( 1, 1, 1, 14, 37, 6 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *dateTimePropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto dateTimePropertyData2 = std::reinterpret_pointer_cast<DateTimePropertyData>( ReadDataFrom( source ) );
    bool equal = dateTimePropertyData2->IsEqualTo( *dateTimePropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DoublePropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( DoublePropertyDataSerializationTest )
{
    auto doublePropertyData1 = std::make_shared<DoublePropertyData>( );
    doublePropertyData1->SetId( Guid( L"{F3FF9E77-DBCB-C180-8301-DBD3CFFF79EE}" ) );
    doublePropertyData1->SetRowVersion( -4503357958352036233LL );
    doublePropertyData1->SetElement( Guid( L"{F3FF9E77-DBCB-C180-8301-DBD3CFFF79EE}" ) );
    doublePropertyData1->SetDefinition( Guid( L"{F3FF9E77-DBCB-C180-8301-DBD3CFFF79EE}" ) );
    doublePropertyData1->SetValue( 13943386115357516 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *doublePropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto doublePropertyData2 = std::reinterpret_pointer_cast<DoublePropertyData>( ReadDataFrom( source ) );
    bool equal = doublePropertyData2->IsEqualTo( *doublePropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GuidPropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( GuidPropertyDataSerializationTest )
{
    auto guidPropertyData1 = std::make_shared<GuidPropertyData>( );
    guidPropertyData1->SetId( Guid( L"{97B3A99D-DD74-2C62-3446-BB2EE9CD95B9}" ) );
    guidPropertyData1->SetRowVersion( 3198362178217552285LL );
    guidPropertyData1->SetElement( Guid( L"{97B3A99D-DD74-2C62-3446-BB2EE9CD95B9}" ) );
    guidPropertyData1->SetDefinition( Guid( L"{97B3A99D-DD74-2C62-3446-BB2EE9CD95B9}" ) );
    guidPropertyData1->SetValue( Guid( L"{97B3A99D-DD74-2C62-3446-BB2EE9CD95B9}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *guidPropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto guidPropertyData2 = std::reinterpret_pointer_cast<GuidPropertyData>( ReadDataFrom( source ) );
    bool equal = guidPropertyData2->IsEqualTo( *guidPropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int16PropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( Int16PropertyDataSerializationTest )
{
    auto int16PropertyData1 = std::make_shared<Int16PropertyData>( );
    int16PropertyData1->SetId( Guid( L"{A9634D36-BFAF-58DB-1ADB-FDF595C6B26C}" ) );
    int16PropertyData1->SetRowVersion( 6402922056419331382LL );
    int16PropertyData1->SetElement( Guid( L"{A9634D36-BFAF-58DB-1ADB-FDF595C6B26C}" ) );
    int16PropertyData1->SetDefinition( Guid( L"{A9634D36-BFAF-58DB-1ADB-FDF595C6B26C}" ) );
    int16PropertyData1->SetValue( 19766 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int16PropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int16PropertyData2 = std::reinterpret_pointer_cast<Int16PropertyData>( ReadDataFrom( source ) );
    bool equal = int16PropertyData2->IsEqualTo( *int16PropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int32PropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( Int32PropertyDataSerializationTest )
{
    auto int32PropertyData1 = std::make_shared<Int32PropertyData>( );
    int32PropertyData1->SetId( Guid( L"{6590A2E0-72D1-937B-C9DE-4E8BA6094507}" ) );
    int32PropertyData1->SetRowVersion( -7819530084321025312LL );
    int32PropertyData1->SetElement( Guid( L"{6590A2E0-72D1-937B-C9DE-4E8BA6094507}" ) );
    int32PropertyData1->SetDefinition( Guid( L"{6590A2E0-72D1-937B-C9DE-4E8BA6094507}" ) );
    int32PropertyData1->SetValue( 1703977696L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int32PropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int32PropertyData2 = std::reinterpret_pointer_cast<Int32PropertyData>( ReadDataFrom( source ) );
    bool equal = int32PropertyData2->IsEqualTo( *int32PropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int64PropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( Int64PropertyDataSerializationTest )
{
    auto int64PropertyData1 = std::make_shared<Int64PropertyData>( );
    int64PropertyData1->SetId( Guid( L"{29A86AC9-09F6-8315-C1A8-906F94155693}" ) );
    int64PropertyData1->SetRowVersion( -9001277327364560183LL );
    int64PropertyData1->SetElement( Guid( L"{29A86AC9-09F6-8315-C1A8-906F94155693}" ) );
    int64PropertyData1->SetDefinition( Guid( L"{29A86AC9-09F6-8315-C1A8-906F94155693}" ) );
    int64PropertyData1->SetValue( -9001277327364560183LL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int64PropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int64PropertyData2 = std::reinterpret_pointer_cast<Int64PropertyData>( ReadDataFrom( source ) );
    bool equal = int64PropertyData2->IsEqualTo( *int64PropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ReferencePropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( ReferencePropertyDataSerializationTest )
{
    auto referencePropertyData1 = std::make_shared<ReferencePropertyData>( );
    referencePropertyData1->SetId( Guid( L"{4EFFC952-D252-ACBA-355D-4B4A72FF934A}" ) );
    referencePropertyData1->SetRowVersion( -6000252302563227310LL );
    referencePropertyData1->SetElement( Guid( L"{4EFFC952-D252-ACBA-355D-4B4A72FF934A}" ) );
    referencePropertyData1->SetDefinition( Guid( L"{4EFFC952-D252-ACBA-355D-4B4A72FF934A}" ) );
    referencePropertyData1->SetValue( Guid( L"{4EFFC952-D252-ACBA-355D-4B4A72FF934A}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *referencePropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto referencePropertyData2 = std::reinterpret_pointer_cast<ReferencePropertyData>( ReadDataFrom( source ) );
    bool equal = referencePropertyData2->IsEqualTo( *referencePropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SBytePropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( SBytePropertyDataSerializationTest )
{
    auto sBytePropertyData1 = std::make_shared<SBytePropertyData>( );
    sBytePropertyData1->SetId( Guid( L"{1AC6643B-9E67-F251-4F8A-79E6586326DC}" ) );
    sBytePropertyData1->SetRowVersion( -985832677749398469LL );
    sBytePropertyData1->SetElement( Guid( L"{1AC6643B-9E67-F251-4F8A-79E6586326DC}" ) );
    sBytePropertyData1->SetDefinition( Guid( L"{1AC6643B-9E67-F251-4F8A-79E6586326DC}" ) );
    sBytePropertyData1->SetValue( 59 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *sBytePropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto sBytePropertyData2 = std::reinterpret_pointer_cast<SBytePropertyData>( ReadDataFrom( source ) );
    bool equal = sBytePropertyData2->IsEqualTo( *sBytePropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SinglePropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( SinglePropertyDataSerializationTest )
{
    auto singlePropertyData1 = std::make_shared<SinglePropertyData>( );
    singlePropertyData1->SetId( Guid( L"{14D2D7C2-DC46-937B-C9DE-3B62284BEB43}" ) );
    singlePropertyData1->SetRowVersion( -7819414134443550782LL );
    singlePropertyData1->SetElement( Guid( L"{14D2D7C2-DC46-937B-C9DE-3B62284BEB43}" ) );
    singlePropertyData1->SetDefinition( Guid( L"{14D2D7C2-DC46-937B-C9DE-3B62284BEB43}" ) );
    singlePropertyData1->SetValue( 1.062733e+16f );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *singlePropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto singlePropertyData2 = std::reinterpret_pointer_cast<SinglePropertyData>( ReadDataFrom( source ) );
    bool equal = singlePropertyData2->IsEqualTo( *singlePropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/StringPropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( StringPropertyDataSerializationTest )
{
    auto stringPropertyData1 = std::make_shared<StringPropertyData>( );
    stringPropertyData1->SetId( Guid( L"{1C84C0E4-3981-B9DD-9DBB-9C8138210327}" ) );
    stringPropertyData1->SetRowVersion( -5053819980147801884LL );
    stringPropertyData1->SetElement( Guid( L"{1C84C0E4-3981-B9DD-9DBB-9C8138210327}" ) );
    stringPropertyData1->SetDefinition( Guid( L"{1C84C0E4-3981-B9DD-9DBB-9C8138210327}" ) );
    stringPropertyData1->SetValue( L"Value" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *stringPropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto stringPropertyData2 = std::reinterpret_pointer_cast<StringPropertyData>( ReadDataFrom( source ) );
    bool equal = stringPropertyData2->IsEqualTo( *stringPropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BinaryTimeseriesPropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( BinaryTimeseriesPropertyDataSerializationTest )
{
    auto binaryTimeseriesPropertyData1 = std::make_shared<BinaryTimeseriesPropertyData>( );
    binaryTimeseriesPropertyData1->SetId( Guid( L"{0E924FA4-5DBA-985D-19BA-BA5D7049F225}" ) );
    binaryTimeseriesPropertyData1->SetRowVersion( -7467709553420644444LL );
    binaryTimeseriesPropertyData1->SetElement( Guid( L"{0E924FA4-5DBA-985D-19BA-BA5D7049F225}" ) );
    binaryTimeseriesPropertyData1->SetDefinition( Guid( L"{0E924FA4-5DBA-985D-19BA-BA5D7049F225}" ) );
    binaryTimeseriesPropertyData1->SetTimeseries( Guid( L"{0E924FA4-5DBA-985D-19BA-BA5D7049F225}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *binaryTimeseriesPropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto binaryTimeseriesPropertyData2 = std::reinterpret_pointer_cast<BinaryTimeseriesPropertyData>( ReadDataFrom( source ) );
    bool equal = binaryTimeseriesPropertyData2->IsEqualTo( *binaryTimeseriesPropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BooleanTimeseriesPropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( BooleanTimeseriesPropertyDataSerializationTest )
{
    auto booleanTimeseriesPropertyData1 = std::make_shared<BooleanTimeseriesPropertyData>( );
    booleanTimeseriesPropertyData1->SetId( Guid( L"{F9FFF0D6-3094-6DE6-B667-0C299FFF0F6B}" ) );
    booleanTimeseriesPropertyData1->SetRowVersion( 7919070411185189078LL );
    booleanTimeseriesPropertyData1->SetElement( Guid( L"{F9FFF0D6-3094-6DE6-B667-0C299FFF0F6B}" ) );
    booleanTimeseriesPropertyData1->SetDefinition( Guid( L"{F9FFF0D6-3094-6DE6-B667-0C299FFF0F6B}" ) );
    booleanTimeseriesPropertyData1->SetTimeseries( Guid( L"{F9FFF0D6-3094-6DE6-B667-0C299FFF0F6B}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *booleanTimeseriesPropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto booleanTimeseriesPropertyData2 = std::reinterpret_pointer_cast<BooleanTimeseriesPropertyData>( ReadDataFrom( source ) );
    bool equal = booleanTimeseriesPropertyData2->IsEqualTo( *booleanTimeseriesPropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ByteTimeseriesPropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( ByteTimeseriesPropertyDataSerializationTest )
{
    auto byteTimeseriesPropertyData1 = std::make_shared<ByteTimeseriesPropertyData>( );
    byteTimeseriesPropertyData1->SetId( Guid( L"{13E6E02A-A2C1-9BDF-D9FB-4583C8670754}" ) );
    byteTimeseriesPropertyData1->SetRowVersion( -7214869127877959638LL );
    byteTimeseriesPropertyData1->SetElement( Guid( L"{13E6E02A-A2C1-9BDF-D9FB-4583C8670754}" ) );
    byteTimeseriesPropertyData1->SetDefinition( Guid( L"{13E6E02A-A2C1-9BDF-D9FB-4583C8670754}" ) );
    byteTimeseriesPropertyData1->SetTimeseries( Guid( L"{13E6E02A-A2C1-9BDF-D9FB-4583C8670754}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *byteTimeseriesPropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto byteTimeseriesPropertyData2 = std::reinterpret_pointer_cast<ByteTimeseriesPropertyData>( ReadDataFrom( source ) );
    bool equal = byteTimeseriesPropertyData2->IsEqualTo( *byteTimeseriesPropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DateTimeTimeseriesPropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( DateTimeTimeseriesPropertyDataSerializationTest )
{
    auto dateTimeTimeseriesPropertyData1 = std::make_shared<DateTimeTimeseriesPropertyData>( );
    dateTimeTimeseriesPropertyData1->SetId( Guid( L"{C99041E2-152C-25AB-A4D5-A83493098247}" ) );
    dateTimeTimeseriesPropertyData1->SetRowVersion( 2714286482525274594LL );
    dateTimeTimeseriesPropertyData1->SetElement( Guid( L"{C99041E2-152C-25AB-A4D5-A83493098247}" ) );
    dateTimeTimeseriesPropertyData1->SetDefinition( Guid( L"{C99041E2-152C-25AB-A4D5-A83493098247}" ) );
    dateTimeTimeseriesPropertyData1->SetTimeseries( Guid( L"{C99041E2-152C-25AB-A4D5-A83493098247}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *dateTimeTimeseriesPropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto dateTimeTimeseriesPropertyData2 = std::reinterpret_pointer_cast<DateTimeTimeseriesPropertyData>( ReadDataFrom( source ) );
    bool equal = dateTimeTimeseriesPropertyData2->IsEqualTo( *dateTimeTimeseriesPropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DoubleTimeseriesPropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( DoubleTimeseriesPropertyDataSerializationTest )
{
    auto doubleTimeseriesPropertyData1 = std::make_shared<DoubleTimeseriesPropertyData>( );
    doubleTimeseriesPropertyData1->SetId( Guid( L"{D612B612-0D2A-902E-0974-B0546B486D48}" ) );
    doubleTimeseriesPropertyData1->SetRowVersion( -8057488205687900654LL );
    doubleTimeseriesPropertyData1->SetElement( Guid( L"{D612B612-0D2A-902E-0974-B0546B486D48}" ) );
    doubleTimeseriesPropertyData1->SetDefinition( Guid( L"{D612B612-0D2A-902E-0974-B0546B486D48}" ) );
    doubleTimeseriesPropertyData1->SetTimeseries( Guid( L"{D612B612-0D2A-902E-0974-B0546B486D48}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *doubleTimeseriesPropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto doubleTimeseriesPropertyData2 = std::reinterpret_pointer_cast<DoubleTimeseriesPropertyData>( ReadDataFrom( source ) );
    bool equal = doubleTimeseriesPropertyData2->IsEqualTo( *doubleTimeseriesPropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GuidTimeseriesPropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( GuidTimeseriesPropertyDataSerializationTest )
{
    auto guidTimeseriesPropertyData1 = std::make_shared<GuidTimeseriesPropertyData>( );
    guidTimeseriesPropertyData1->SetId( Guid( L"{EABB70EA-0EF1-9E2E-7974-708F57DD0E57}" ) );
    guidTimeseriesPropertyData1->SetRowVersion( -7048679934600187670LL );
    guidTimeseriesPropertyData1->SetElement( Guid( L"{EABB70EA-0EF1-9E2E-7974-708F57DD0E57}" ) );
    guidTimeseriesPropertyData1->SetDefinition( Guid( L"{EABB70EA-0EF1-9E2E-7974-708F57DD0E57}" ) );
    guidTimeseriesPropertyData1->SetTimeseries( Guid( L"{EABB70EA-0EF1-9E2E-7974-708F57DD0E57}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *guidTimeseriesPropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto guidTimeseriesPropertyData2 = std::reinterpret_pointer_cast<GuidTimeseriesPropertyData>( ReadDataFrom( source ) );
    bool equal = guidTimeseriesPropertyData2->IsEqualTo( *guidTimeseriesPropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int16TimeseriesPropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( Int16TimeseriesPropertyDataSerializationTest )
{
    auto int16TimeseriesPropertyData1 = std::make_shared<Int16TimeseriesPropertyData>( );
    int16TimeseriesPropertyData1->SetId( Guid( L"{7B2B5BD8-89DA-816F-81F6-915BDED4DA1B}" ) );
    int16TimeseriesPropertyData1->SetRowVersion( -9119919148939650088LL );
    int16TimeseriesPropertyData1->SetElement( Guid( L"{7B2B5BD8-89DA-816F-81F6-915BDED4DA1B}" ) );
    int16TimeseriesPropertyData1->SetDefinition( Guid( L"{7B2B5BD8-89DA-816F-81F6-915BDED4DA1B}" ) );
    int16TimeseriesPropertyData1->SetTimeseries( Guid( L"{7B2B5BD8-89DA-816F-81F6-915BDED4DA1B}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int16TimeseriesPropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int16TimeseriesPropertyData2 = std::reinterpret_pointer_cast<Int16TimeseriesPropertyData>( ReadDataFrom( source ) );
    bool equal = int16TimeseriesPropertyData2->IsEqualTo( *int16TimeseriesPropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int32TimeseriesPropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( Int32TimeseriesPropertyDataSerializationTest )
{
    auto int32TimeseriesPropertyData1 = std::make_shared<Int32TimeseriesPropertyData>( );
    int32TimeseriesPropertyData1->SetId( Guid( L"{9FF1F1C6-7364-251E-A478-CE26F98F8F63}" ) );
    int32TimeseriesPropertyData1->SetRowVersion( 2674702104722010566LL );
    int32TimeseriesPropertyData1->SetElement( Guid( L"{9FF1F1C6-7364-251E-A478-CE26F98F8F63}" ) );
    int32TimeseriesPropertyData1->SetDefinition( Guid( L"{9FF1F1C6-7364-251E-A478-CE26F98F8F63}" ) );
    int32TimeseriesPropertyData1->SetTimeseries( Guid( L"{9FF1F1C6-7364-251E-A478-CE26F98F8F63}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int32TimeseriesPropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int32TimeseriesPropertyData2 = std::reinterpret_pointer_cast<Int32TimeseriesPropertyData>( ReadDataFrom( source ) );
    bool equal = int32TimeseriesPropertyData2->IsEqualTo( *int32TimeseriesPropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int64TimeseriesPropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( Int64TimeseriesPropertyDataSerializationTest )
{
    auto int64TimeseriesPropertyData1 = std::make_shared<Int64TimeseriesPropertyData>( );
    int64TimeseriesPropertyData1->SetId( Guid( L"{4DD31704-9B5E-BC84-3D21-D97AB2CBE820}" ) );
    int64TimeseriesPropertyData1->SetRowVersion( -4862590868318382332LL );
    int64TimeseriesPropertyData1->SetElement( Guid( L"{4DD31704-9B5E-BC84-3D21-D97AB2CBE820}" ) );
    int64TimeseriesPropertyData1->SetDefinition( Guid( L"{4DD31704-9B5E-BC84-3D21-D97AB2CBE820}" ) );
    int64TimeseriesPropertyData1->SetTimeseries( Guid( L"{4DD31704-9B5E-BC84-3D21-D97AB2CBE820}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int64TimeseriesPropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int64TimeseriesPropertyData2 = std::reinterpret_pointer_cast<Int64TimeseriesPropertyData>( ReadDataFrom( source ) );
    bool equal = int64TimeseriesPropertyData2->IsEqualTo( *int64TimeseriesPropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ReferenceTimeseriesPropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( ReferenceTimeseriesPropertyDataSerializationTest )
{
    auto referenceTimeseriesPropertyData1 = std::make_shared<ReferenceTimeseriesPropertyData>( );
    referenceTimeseriesPropertyData1->SetId( Guid( L"{713F2D3F-7C29-8880-1101-3E948EFCB4FC}" ) );
    referenceTimeseriesPropertyData1->SetRowVersion( -8610745970096919233LL );
    referenceTimeseriesPropertyData1->SetElement( Guid( L"{713F2D3F-7C29-8880-1101-3E948EFCB4FC}" ) );
    referenceTimeseriesPropertyData1->SetDefinition( Guid( L"{713F2D3F-7C29-8880-1101-3E948EFCB4FC}" ) );
    referenceTimeseriesPropertyData1->SetTimeseries( Guid( L"{713F2D3F-7C29-8880-1101-3E948EFCB4FC}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *referenceTimeseriesPropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto referenceTimeseriesPropertyData2 = std::reinterpret_pointer_cast<ReferenceTimeseriesPropertyData>( ReadDataFrom( source ) );
    bool equal = referenceTimeseriesPropertyData2->IsEqualTo( *referenceTimeseriesPropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SByteTimeseriesPropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( SByteTimeseriesPropertyDataSerializationTest )
{
    auto sByteTimeseriesPropertyData1 = std::make_shared<SByteTimeseriesPropertyData>( );
    sByteTimeseriesPropertyData1->SetId( Guid( L"{3E0E464A-8641-0E03-70C0-61827C706252}" ) );
    sByteTimeseriesPropertyData1->SetRowVersion( 1009798356233242186LL );
    sByteTimeseriesPropertyData1->SetElement( Guid( L"{3E0E464A-8641-0E03-70C0-61827C706252}" ) );
    sByteTimeseriesPropertyData1->SetDefinition( Guid( L"{3E0E464A-8641-0E03-70C0-61827C706252}" ) );
    sByteTimeseriesPropertyData1->SetTimeseries( Guid( L"{3E0E464A-8641-0E03-70C0-61827C706252}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *sByteTimeseriesPropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto sByteTimeseriesPropertyData2 = std::reinterpret_pointer_cast<SByteTimeseriesPropertyData>( ReadDataFrom( source ) );
    bool equal = sByteTimeseriesPropertyData2->IsEqualTo( *sByteTimeseriesPropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SingleTimeseriesPropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( SingleTimeseriesPropertyDataSerializationTest )
{
    auto singleTimeseriesPropertyData1 = std::make_shared<SingleTimeseriesPropertyData>( );
    singleTimeseriesPropertyData1->SetId( Guid( L"{B4491B37-C1C3-440E-2270-83C32D92D8EC}" ) );
    singleTimeseriesPropertyData1->SetRowVersion( 4904070090540522295LL );
    singleTimeseriesPropertyData1->SetElement( Guid( L"{B4491B37-C1C3-440E-2270-83C32D92D8EC}" ) );
    singleTimeseriesPropertyData1->SetDefinition( Guid( L"{B4491B37-C1C3-440E-2270-83C32D92D8EC}" ) );
    singleTimeseriesPropertyData1->SetTimeseries( Guid( L"{B4491B37-C1C3-440E-2270-83C32D92D8EC}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *singleTimeseriesPropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto singleTimeseriesPropertyData2 = std::reinterpret_pointer_cast<SingleTimeseriesPropertyData>( ReadDataFrom( source ) );
    bool equal = singleTimeseriesPropertyData2->IsEqualTo( *singleTimeseriesPropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/StringTimeseriesPropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( StringTimeseriesPropertyDataSerializationTest )
{
    auto stringTimeseriesPropertyData1 = std::make_shared<StringTimeseriesPropertyData>( );
    stringTimeseriesPropertyData1->SetId( Guid( L"{695E2407-EFD1-69F5-96AF-F78B967A24E0}" ) );
    stringTimeseriesPropertyData1->SetRowVersion( 7635272425971524615LL );
    stringTimeseriesPropertyData1->SetElement( Guid( L"{695E2407-EFD1-69F5-96AF-F78B967A24E0}" ) );
    stringTimeseriesPropertyData1->SetDefinition( Guid( L"{695E2407-EFD1-69F5-96AF-F78B967A24E0}" ) );
    stringTimeseriesPropertyData1->SetTimeseries( Guid( L"{695E2407-EFD1-69F5-96AF-F78B967A24E0}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *stringTimeseriesPropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto stringTimeseriesPropertyData2 = std::reinterpret_pointer_cast<StringTimeseriesPropertyData>( ReadDataFrom( source ) );
    bool equal = stringTimeseriesPropertyData2->IsEqualTo( *stringTimeseriesPropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TimeSpanTimeseriesPropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( TimeSpanTimeseriesPropertyDataSerializationTest )
{
    auto timeSpanTimeseriesPropertyData1 = std::make_shared<TimeSpanTimeseriesPropertyData>( );
    timeSpanTimeseriesPropertyData1->SetId( Guid( L"{E21D31DB-8E76-9B1C-D938-716E47B88CDB}" ) );
    timeSpanTimeseriesPropertyData1->SetRowVersion( -7269779057231973925LL );
    timeSpanTimeseriesPropertyData1->SetElement( Guid( L"{E21D31DB-8E76-9B1C-D938-716E47B88CDB}" ) );
    timeSpanTimeseriesPropertyData1->SetDefinition( Guid( L"{E21D31DB-8E76-9B1C-D938-716E47B88CDB}" ) );
    timeSpanTimeseriesPropertyData1->SetTimeseries( Guid( L"{E21D31DB-8E76-9B1C-D938-716E47B88CDB}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *timeSpanTimeseriesPropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto timeSpanTimeseriesPropertyData2 = std::reinterpret_pointer_cast<TimeSpanTimeseriesPropertyData>( ReadDataFrom( source ) );
    bool equal = timeSpanTimeseriesPropertyData2->IsEqualTo( *timeSpanTimeseriesPropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt16TimeseriesPropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( UInt16TimeseriesPropertyDataSerializationTest )
{
    auto uInt16TimeseriesPropertyData1 = std::make_shared<UInt16TimeseriesPropertyData>( );
    uInt16TimeseriesPropertyData1->SetId( Guid( L"{54EBD8DB-1242-E95C-973A-48422AD71BDB}" ) );
    uInt16TimeseriesPropertyData1->SetRowVersion( -1631408888913078053LL );
    uInt16TimeseriesPropertyData1->SetElement( Guid( L"{54EBD8DB-1242-E95C-973A-48422AD71BDB}" ) );
    uInt16TimeseriesPropertyData1->SetDefinition( Guid( L"{54EBD8DB-1242-E95C-973A-48422AD71BDB}" ) );
    uInt16TimeseriesPropertyData1->SetTimeseries( Guid( L"{54EBD8DB-1242-E95C-973A-48422AD71BDB}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt16TimeseriesPropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt16TimeseriesPropertyData2 = std::reinterpret_pointer_cast<UInt16TimeseriesPropertyData>( ReadDataFrom( source ) );
    bool equal = uInt16TimeseriesPropertyData2->IsEqualTo( *uInt16TimeseriesPropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt32TimeseriesPropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( UInt32TimeseriesPropertyDataSerializationTest )
{
    auto uInt32TimeseriesPropertyData1 = std::make_shared<UInt32TimeseriesPropertyData>( );
    uInt32TimeseriesPropertyData1->SetId( Guid( L"{11EB998F-D7AF-A24D-45B2-EBF588D799F1}" ) );
    uInt32TimeseriesPropertyData1->SetRowVersion( -6751503119438603889LL );
    uInt32TimeseriesPropertyData1->SetElement( Guid( L"{11EB998F-D7AF-A24D-45B2-EBF588D799F1}" ) );
    uInt32TimeseriesPropertyData1->SetDefinition( Guid( L"{11EB998F-D7AF-A24D-45B2-EBF588D799F1}" ) );
    uInt32TimeseriesPropertyData1->SetTimeseries( Guid( L"{11EB998F-D7AF-A24D-45B2-EBF588D799F1}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt32TimeseriesPropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt32TimeseriesPropertyData2 = std::reinterpret_pointer_cast<UInt32TimeseriesPropertyData>( ReadDataFrom( source ) );
    bool equal = uInt32TimeseriesPropertyData2->IsEqualTo( *uInt32TimeseriesPropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt64TimeseriesPropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( UInt64TimeseriesPropertyDataSerializationTest )
{
    auto uInt64TimeseriesPropertyData1 = std::make_shared<UInt64TimeseriesPropertyData>( );
    uInt64TimeseriesPropertyData1->SetId( Guid( L"{A95D5CEA-EE30-A724-E524-770C95BA3A57}" ) );
    uInt64TimeseriesPropertyData1->SetRowVersion( -6402730877446693654LL );
    uInt64TimeseriesPropertyData1->SetElement( Guid( L"{A95D5CEA-EE30-A724-E524-770C95BA3A57}" ) );
    uInt64TimeseriesPropertyData1->SetDefinition( Guid( L"{A95D5CEA-EE30-A724-E524-770C95BA3A57}" ) );
    uInt64TimeseriesPropertyData1->SetTimeseries( Guid( L"{A95D5CEA-EE30-A724-E524-770C95BA3A57}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt64TimeseriesPropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt64TimeseriesPropertyData2 = std::reinterpret_pointer_cast<UInt64TimeseriesPropertyData>( ReadDataFrom( source ) );
    bool equal = uInt64TimeseriesPropertyData2->IsEqualTo( *uInt64TimeseriesPropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TimeSpanPropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( TimeSpanPropertyDataSerializationTest )
{
    auto timeSpanPropertyData1 = std::make_shared<TimeSpanPropertyData>( );
    timeSpanPropertyData1->SetId( Guid( L"{1FBB969B-87EE-BF54-FD2A-E177F8DD69D9}" ) );
    timeSpanPropertyData1->SetRowVersion( -4659950257617267045LL );
    timeSpanPropertyData1->SetElement( Guid( L"{1FBB969B-87EE-BF54-FD2A-E177F8DD69D9}" ) );
    timeSpanPropertyData1->SetDefinition( Guid( L"{1FBB969B-87EE-BF54-FD2A-E177F8DD69D9}" ) );
    timeSpanPropertyData1->SetValue( TimeSpan( -817617267045LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *timeSpanPropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto timeSpanPropertyData2 = std::reinterpret_pointer_cast<TimeSpanPropertyData>( ReadDataFrom( source ) );
    bool equal = timeSpanPropertyData2->IsEqualTo( *timeSpanPropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt16PropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( UInt16PropertyDataSerializationTest )
{
    auto uInt16PropertyData1 = std::make_shared<UInt16PropertyData>( );
    uInt16PropertyData1->SetId( Guid( L"{DD66D477-E812-FE6E-7F76-1748BB662BEE}" ) );
    uInt16PropertyData1->SetRowVersion( -112897772916124553LL );
    uInt16PropertyData1->SetElement( Guid( L"{DD66D477-E812-FE6E-7F76-1748BB662BEE}" ) );
    uInt16PropertyData1->SetDefinition( Guid( L"{DD66D477-E812-FE6E-7F76-1748BB662BEE}" ) );
    uInt16PropertyData1->SetValue( 54391 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt16PropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt16PropertyData2 = std::reinterpret_pointer_cast<UInt16PropertyData>( ReadDataFrom( source ) );
    bool equal = uInt16PropertyData2->IsEqualTo( *uInt16PropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt32PropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( UInt32PropertyDataSerializationTest )
{
    auto uInt32PropertyData1 = std::make_shared<UInt32PropertyData>( );
    uInt32PropertyData1->SetId( Guid( L"{D211E6C7-A461-B9A3-9DC5-25864B8867E3}" ) );
    uInt32PropertyData1->SetRowVersion( -5070028015445875001LL );
    uInt32PropertyData1->SetElement( Guid( L"{D211E6C7-A461-B9A3-9DC5-25864B8867E3}" ) );
    uInt32PropertyData1->SetDefinition( Guid( L"{D211E6C7-A461-B9A3-9DC5-25864B8867E3}" ) );
    uInt32PropertyData1->SetValue( 3524388551UL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt32PropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt32PropertyData2 = std::reinterpret_pointer_cast<UInt32PropertyData>( ReadDataFrom( source ) );
    bool equal = uInt32PropertyData2->IsEqualTo( *uInt32PropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt64PropertyDataSerializationTest
BOOST_AUTO_TEST_CASE( UInt64PropertyDataSerializationTest )
{
    auto uInt64PropertyData1 = std::make_shared<UInt64PropertyData>( );
    uInt64PropertyData1->SetId( Guid( L"{7E04896F-7BB0-1B66-D866-DE0D7E2091F6}" ) );
    uInt64PropertyData1->SetRowVersion( 1974401484607228271LL );
    uInt64PropertyData1->SetElement( Guid( L"{7E04896F-7BB0-1B66-D866-DE0D7E2091F6}" ) );
    uInt64PropertyData1->SetDefinition( Guid( L"{7E04896F-7BB0-1B66-D866-DE0D7E2091F6}" ) );
    uInt64PropertyData1->SetValue( 1974401484607228271LL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt64PropertyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt64PropertyData2 = std::reinterpret_pointer_cast<UInt64PropertyData>( ReadDataFrom( source ) );
    bool equal = uInt64PropertyData2->IsEqualTo( *uInt64PropertyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BinaryPropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( BinaryPropertyDefinitionDataSerializationTest )
{
    auto binaryPropertyDefinitionData1 = std::make_shared<BinaryPropertyDefinitionData>( );
    binaryPropertyDefinitionData1->SetId( Guid( L"{1D803290-52D6-19B9-989D-4A6BB8014C09}" ) );
    binaryPropertyDefinitionData1->SetRowVersion( 1853603801211089552LL );
    binaryPropertyDefinitionData1->SetElementType( Guid( L"{1D803290-52D6-19B9-989D-4A6BB8014C09}" ) );
    binaryPropertyDefinitionData1->SetName( L"Name" );
    binaryPropertyDefinitionData1->SetDescription( L"Description" );
    binaryPropertyDefinitionData1->SetDefaultValue( { {'D','e','f','a','u','l','t','V','a','l','u','e'} } );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *binaryPropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto binaryPropertyDefinitionData2 = std::reinterpret_pointer_cast<BinaryPropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = binaryPropertyDefinitionData2->IsEqualTo( *binaryPropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BooleanPropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( BooleanPropertyDefinitionDataSerializationTest )
{
    auto booleanPropertyDefinitionData1 = std::make_shared<BooleanPropertyDefinitionData>( );
    booleanPropertyDefinitionData1->SetId( Guid( L"{C5539C12-7E89-E9BE-977D-7E91A3CA3948}" ) );
    booleanPropertyDefinitionData1->SetRowVersion( -1603705287111107566LL );
    booleanPropertyDefinitionData1->SetElementType( Guid( L"{C5539C12-7E89-E9BE-977D-7E91A3CA3948}" ) );
    booleanPropertyDefinitionData1->SetName( L"Name" );
    booleanPropertyDefinitionData1->SetDescription( L"Description" );
    booleanPropertyDefinitionData1->SetDefaultValue( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *booleanPropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto booleanPropertyDefinitionData2 = std::reinterpret_pointer_cast<BooleanPropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = booleanPropertyDefinitionData2->IsEqualTo( *booleanPropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BytePropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( BytePropertyDefinitionDataSerializationTest )
{
    auto bytePropertyDefinitionData1 = std::make_shared<BytePropertyDefinitionData>( );
    bytePropertyDefinitionData1->SetId( Guid( L"{F1BB6CC7-ED96-BDD1-BD8B-B7698FDD36E3}" ) );
    bytePropertyDefinitionData1->SetRowVersion( -4768769297852175161LL );
    bytePropertyDefinitionData1->SetElementType( Guid( L"{F1BB6CC7-ED96-BDD1-BD8B-B7698FDD36E3}" ) );
    bytePropertyDefinitionData1->SetName( L"Name" );
    bytePropertyDefinitionData1->SetDescription( L"Description" );
    bytePropertyDefinitionData1->SetDefaultValue( 199 );
    bytePropertyDefinitionData1->SetMinValue( 199 );
    bytePropertyDefinitionData1->SetMaxValue( 199 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *bytePropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto bytePropertyDefinitionData2 = std::reinterpret_pointer_cast<BytePropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = bytePropertyDefinitionData2->IsEqualTo( *bytePropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DateTimePropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( DateTimePropertyDefinitionDataSerializationTest )
{
    auto dateTimePropertyDefinitionData1 = std::make_shared<DateTimePropertyDefinitionData>( );
    dateTimePropertyDefinitionData1->SetId( Guid( L"{6B2D65C2-50BD-E15F-87FA-0ABDD6B4A643}" ) );
    dateTimePropertyDefinitionData1->SetRowVersion( -2206956517911075390LL );
    dateTimePropertyDefinitionData1->SetElementType( Guid( L"{6B2D65C2-50BD-E15F-87FA-0ABDD6B4A643}" ) );
    dateTimePropertyDefinitionData1->SetName( L"Name" );
    dateTimePropertyDefinitionData1->SetDescription( L"Description" );
    dateTimePropertyDefinitionData1->SetDefaultValue( L"DefaultValue" );
    dateTimePropertyDefinitionData1->SetMinValue( L"MinValue" );
    dateTimePropertyDefinitionData1->SetMaxValue( L"MaxValue" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *dateTimePropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto dateTimePropertyDefinitionData2 = std::reinterpret_pointer_cast<DateTimePropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = dateTimePropertyDefinitionData2->IsEqualTo( *dateTimePropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DoublePropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( DoublePropertyDefinitionDataSerializationTest )
{
    auto doublePropertyDefinitionData1 = std::make_shared<DoublePropertyDefinitionData>( );
    doublePropertyDefinitionData1->SetId( Guid( L"{EA061AC5-7B6D-83B0-C10D-DEB6576058A3}" ) );
    doublePropertyDefinitionData1->SetRowVersion( -8957523946831996219LL );
    doublePropertyDefinitionData1->SetElementType( Guid( L"{EA061AC5-7B6D-83B0-C10D-DEB6576058A3}" ) );
    doublePropertyDefinitionData1->SetName( L"Name" );
    doublePropertyDefinitionData1->SetDescription( L"Description" );
    doublePropertyDefinitionData1->SetDefaultValue( 9489220126877554 );
    doublePropertyDefinitionData1->SetMinValue( 9489220126877554 );
    doublePropertyDefinitionData1->SetMaxValue( 9489220126877554 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *doublePropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto doublePropertyDefinitionData2 = std::reinterpret_pointer_cast<DoublePropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = doublePropertyDefinitionData2->IsEqualTo( *doublePropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GuidPropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( GuidPropertyDefinitionDataSerializationTest )
{
    auto guidPropertyDefinitionData1 = std::make_shared<GuidPropertyDefinitionData>( );
    guidPropertyDefinitionData1->SetId( Guid( L"{CE281097-BBE1-0062-0046-DD87731408E9}" ) );
    guidPropertyDefinitionData1->SetRowVersion( 27791126218412183LL );
    guidPropertyDefinitionData1->SetElementType( Guid( L"{CE281097-BBE1-0062-0046-DD87731408E9}" ) );
    guidPropertyDefinitionData1->SetName( L"Name" );
    guidPropertyDefinitionData1->SetDescription( L"Description" );
    guidPropertyDefinitionData1->SetDefaultValue( Guid( L"{CE281097-BBE1-0062-0046-DD87731408E9}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *guidPropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto guidPropertyDefinitionData2 = std::reinterpret_pointer_cast<GuidPropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = guidPropertyDefinitionData2->IsEqualTo( *guidPropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int16PropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( Int16PropertyDefinitionDataSerializationTest )
{
    auto int16PropertyDefinitionData1 = std::make_shared<Int16PropertyDefinitionData>( );
    int16PropertyDefinitionData1->SetId( Guid( L"{8116597C-DE9B-0CFB-30DF-7BD981689A3E}" ) );
    int16PropertyDefinitionData1->SetRowVersion( 935586107076532604LL );
    int16PropertyDefinitionData1->SetElementType( Guid( L"{8116597C-DE9B-0CFB-30DF-7BD981689A3E}" ) );
    int16PropertyDefinitionData1->SetName( L"Name" );
    int16PropertyDefinitionData1->SetDescription( L"Description" );
    int16PropertyDefinitionData1->SetDefaultValue( 22908 );
    int16PropertyDefinitionData1->SetMinValue( 22908 );
    int16PropertyDefinitionData1->SetMaxValue( 22908 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int16PropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int16PropertyDefinitionData2 = std::reinterpret_pointer_cast<Int16PropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = int16PropertyDefinitionData2->IsEqualTo( *int16PropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int32PropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( Int32PropertyDefinitionDataSerializationTest )
{
    auto int32PropertyDefinitionData1 = std::make_shared<Int32PropertyDefinitionData>( );
    int32PropertyDefinitionData1->SetId( Guid( L"{FA7276D6-5345-2973-94CE-CAA25F4E6E6B}" ) );
    int32PropertyDefinitionData1->SetRowVersion( 2986822537896425174LL );
    int32PropertyDefinitionData1->SetElementType( Guid( L"{FA7276D6-5345-2973-94CE-CAA25F4E6E6B}" ) );
    int32PropertyDefinitionData1->SetName( L"Name" );
    int32PropertyDefinitionData1->SetDescription( L"Description" );
    int32PropertyDefinitionData1->SetDefaultValue( -93161770L );
    int32PropertyDefinitionData1->SetMinValue( -93161770L );
    int32PropertyDefinitionData1->SetMaxValue( -93161770L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int32PropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int32PropertyDefinitionData2 = std::reinterpret_pointer_cast<Int32PropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = int32PropertyDefinitionData2->IsEqualTo( *int32PropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int64PropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( Int64PropertyDefinitionDataSerializationTest )
{
    auto int64PropertyDefinitionData1 = std::make_shared<Int64PropertyDefinitionData>( );
    int64PropertyDefinitionData1->SetId( Guid( L"{25153A4E-9C64-9D7F-B9FE-3926A4A85C72}" ) );
    int64PropertyDefinitionData1->SetRowVersion( -7097782533779801522LL );
    int64PropertyDefinitionData1->SetElementType( Guid( L"{25153A4E-9C64-9D7F-B9FE-3926A4A85C72}" ) );
    int64PropertyDefinitionData1->SetName( L"Name" );
    int64PropertyDefinitionData1->SetDescription( L"Description" );
    int64PropertyDefinitionData1->SetDefaultValue( -7097782533779801522LL );
    int64PropertyDefinitionData1->SetMinValue( -7097782533779801522LL );
    int64PropertyDefinitionData1->SetMaxValue( -7097782533779801522LL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int64PropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int64PropertyDefinitionData2 = std::reinterpret_pointer_cast<Int64PropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = int64PropertyDefinitionData2->IsEqualTo( *int64PropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ReferencePropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( ReferencePropertyDefinitionDataSerializationTest )
{
    auto referencePropertyDefinitionData1 = std::make_shared<ReferencePropertyDefinitionData>( );
    referencePropertyDefinitionData1->SetId( Guid( L"{24335FD6-6F2B-1A65-58A6-F6D424CCFA6B}" ) );
    referencePropertyDefinitionData1->SetRowVersion( 1902048648715526102LL );
    referencePropertyDefinitionData1->SetElementType( Guid( L"{24335FD6-6F2B-1A65-58A6-F6D424CCFA6B}" ) );
    referencePropertyDefinitionData1->SetName( L"Name" );
    referencePropertyDefinitionData1->SetDescription( L"Description" );
    referencePropertyDefinitionData1->SetDefaultValue( Guid( L"{24335FD6-6F2B-1A65-58A6-F6D424CCFA6B}" ) );
    referencePropertyDefinitionData1->SetReferencedElementType( Guid( L"{24335FD6-6F2B-1A65-58A6-F6D424CCFA6B}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *referencePropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto referencePropertyDefinitionData2 = std::reinterpret_pointer_cast<ReferencePropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = referencePropertyDefinitionData2->IsEqualTo( *referencePropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SBytePropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( SBytePropertyDefinitionDataSerializationTest )
{
    auto sBytePropertyDefinitionData1 = std::make_shared<SBytePropertyDefinitionData>( );
    sBytePropertyDefinitionData1->SetId( Guid( L"{8AA729B7-0195-0AA3-50C5-80A951E594ED}" ) );
    sBytePropertyDefinitionData1->SetRowVersion( 766458103371082167LL );
    sBytePropertyDefinitionData1->SetElementType( Guid( L"{8AA729B7-0195-0AA3-50C5-80A951E594ED}" ) );
    sBytePropertyDefinitionData1->SetName( L"Name" );
    sBytePropertyDefinitionData1->SetDescription( L"Description" );
    sBytePropertyDefinitionData1->SetDefaultValue( -73 );
    sBytePropertyDefinitionData1->SetMinValue( -73 );
    sBytePropertyDefinitionData1->SetMaxValue( -73 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *sBytePropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto sBytePropertyDefinitionData2 = std::reinterpret_pointer_cast<SBytePropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = sBytePropertyDefinitionData2->IsEqualTo( *sBytePropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SinglePropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( SinglePropertyDefinitionDataSerializationTest )
{
    auto singlePropertyDefinitionData1 = std::make_shared<SinglePropertyDefinitionData>( );
    singlePropertyDefinitionData1->SetId( Guid( L"{DF60F841-AFE1-2C03-34C0-F587FB061F82}" ) );
    singlePropertyDefinitionData1->SetRowVersion( 3171571947249137729LL );
    singlePropertyDefinitionData1->SetElementType( Guid( L"{DF60F841-AFE1-2C03-34C0-F587FB061F82}" ) );
    singlePropertyDefinitionData1->SetName( L"Name" );
    singlePropertyDefinitionData1->SetDescription( L"Description" );
    singlePropertyDefinitionData1->SetDefaultValue( 3.1715722e+15f );
    singlePropertyDefinitionData1->SetMinValue( 3.1715722e+15f );
    singlePropertyDefinitionData1->SetMaxValue( 3.1715722e+15f );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *singlePropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto singlePropertyDefinitionData2 = std::reinterpret_pointer_cast<SinglePropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = singlePropertyDefinitionData2->IsEqualTo( *singlePropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/StringPropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( StringPropertyDefinitionDataSerializationTest )
{
    auto stringPropertyDefinitionData1 = std::make_shared<StringPropertyDefinitionData>( );
    stringPropertyDefinitionData1->SetId( Guid( L"{FD110D8D-6A34-991A-9958-562CBF88B0B1}" ) );
    stringPropertyDefinitionData1->SetRowVersion( -7414497060695503475LL );
    stringPropertyDefinitionData1->SetElementType( Guid( L"{FD110D8D-6A34-991A-9958-562CBF88B0B1}" ) );
    stringPropertyDefinitionData1->SetName( L"Name" );
    stringPropertyDefinitionData1->SetDescription( L"Description" );
    stringPropertyDefinitionData1->SetDefaultValue( L"DefaultValue" );
    stringPropertyDefinitionData1->SetPattern( L"Pattern" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *stringPropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto stringPropertyDefinitionData2 = std::reinterpret_pointer_cast<StringPropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = stringPropertyDefinitionData2->IsEqualTo( *stringPropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BinaryTimeseriesPropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( BinaryTimeseriesPropertyDefinitionDataSerializationTest )
{
    auto binaryTimeseriesPropertyDefinitionData1 = std::make_shared<BinaryTimeseriesPropertyDefinitionData>( );
    binaryTimeseriesPropertyDefinitionData1->SetId( Guid( L"{6C888CD1-A32E-1237-48EC-C5743611318B}" ) );
    binaryTimeseriesPropertyDefinitionData1->SetRowVersion( 1312697236186500305LL );
    binaryTimeseriesPropertyDefinitionData1->SetElementType( Guid( L"{6C888CD1-A32E-1237-48EC-C5743611318B}" ) );
    binaryTimeseriesPropertyDefinitionData1->SetName( L"Name" );
    binaryTimeseriesPropertyDefinitionData1->SetDescription( L"Description" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *binaryTimeseriesPropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto binaryTimeseriesPropertyDefinitionData2 = std::reinterpret_pointer_cast<BinaryTimeseriesPropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = binaryTimeseriesPropertyDefinitionData2->IsEqualTo( *binaryTimeseriesPropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BooleanTimeseriesPropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( BooleanTimeseriesPropertyDefinitionDataSerializationTest )
{
    auto booleanTimeseriesPropertyDefinitionData1 = std::make_shared<BooleanTimeseriesPropertyDefinitionData>( );
    booleanTimeseriesPropertyDefinitionData1->SetId( Guid( L"{ADB1A0F7-FF33-FAB2-5F4D-FFCCB58D05EF}" ) );
    booleanTimeseriesPropertyDefinitionData1->SetRowVersion( -381962420950556425LL );
    booleanTimeseriesPropertyDefinitionData1->SetElementType( Guid( L"{ADB1A0F7-FF33-FAB2-5F4D-FFCCB58D05EF}" ) );
    booleanTimeseriesPropertyDefinitionData1->SetName( L"Name" );
    booleanTimeseriesPropertyDefinitionData1->SetDescription( L"Description" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *booleanTimeseriesPropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto booleanTimeseriesPropertyDefinitionData2 = std::reinterpret_pointer_cast<BooleanTimeseriesPropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = booleanTimeseriesPropertyDefinitionData2->IsEqualTo( *booleanTimeseriesPropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ByteTimeseriesPropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( ByteTimeseriesPropertyDefinitionDataSerializationTest )
{
    auto byteTimeseriesPropertyDefinitionData1 = std::make_shared<ByteTimeseriesPropertyDefinitionData>( );
    byteTimeseriesPropertyDefinitionData1->SetId( Guid( L"{AAD1D4DF-2509-FB3F-DFFC-A490558B2BFB}" ) );
    byteTimeseriesPropertyDefinitionData1->SetRowVersion( -342514323206056737LL );
    byteTimeseriesPropertyDefinitionData1->SetElementType( Guid( L"{AAD1D4DF-2509-FB3F-DFFC-A490558B2BFB}" ) );
    byteTimeseriesPropertyDefinitionData1->SetName( L"Name" );
    byteTimeseriesPropertyDefinitionData1->SetDescription( L"Description" );
    byteTimeseriesPropertyDefinitionData1->SetMinValue( 223 );
    byteTimeseriesPropertyDefinitionData1->SetMaxValue( 223 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *byteTimeseriesPropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto byteTimeseriesPropertyDefinitionData2 = std::reinterpret_pointer_cast<ByteTimeseriesPropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = byteTimeseriesPropertyDefinitionData2->IsEqualTo( *byteTimeseriesPropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DateTimeTimeseriesPropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( DateTimeTimeseriesPropertyDefinitionDataSerializationTest )
{
    auto dateTimeTimeseriesPropertyDefinitionData1 = std::make_shared<DateTimeTimeseriesPropertyDefinitionData>( );
    dateTimeTimeseriesPropertyDefinitionData1->SetId( Guid( L"{9329F71B-727F-9F98-F919-4EFEC994EFD8}" ) );
    dateTimeTimeseriesPropertyDefinitionData1->SetRowVersion( -6946676532963576037LL );
    dateTimeTimeseriesPropertyDefinitionData1->SetElementType( Guid( L"{9329F71B-727F-9F98-F919-4EFEC994EFD8}" ) );
    dateTimeTimeseriesPropertyDefinitionData1->SetName( L"Name" );
    dateTimeTimeseriesPropertyDefinitionData1->SetDescription( L"Description" );
    dateTimeTimeseriesPropertyDefinitionData1->SetMinValue( L"MinValue" );
    dateTimeTimeseriesPropertyDefinitionData1->SetMaxValue( L"MaxValue" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *dateTimeTimeseriesPropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto dateTimeTimeseriesPropertyDefinitionData2 = std::reinterpret_pointer_cast<DateTimeTimeseriesPropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = dateTimeTimeseriesPropertyDefinitionData2->IsEqualTo( *dateTimeTimeseriesPropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DoubleTimeseriesPropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( DoubleTimeseriesPropertyDefinitionDataSerializationTest )
{
    auto doubleTimeseriesPropertyDefinitionData1 = std::make_shared<DoubleTimeseriesPropertyDefinitionData>( );
    doubleTimeseriesPropertyDefinitionData1->SetId( Guid( L"{1C218637-12E0-385B-1CDA-4807388461EC}" ) );
    doubleTimeseriesPropertyDefinitionData1->SetRowVersion( 4060860242758567479LL );
    doubleTimeseriesPropertyDefinitionData1->SetElementType( Guid( L"{1C218637-12E0-385B-1CDA-4807388461EC}" ) );
    doubleTimeseriesPropertyDefinitionData1->SetName( L"Name" );
    doubleTimeseriesPropertyDefinitionData1->SetDescription( L"Description" );
    doubleTimeseriesPropertyDefinitionData1->SetMinValue( 4060860242758567.5 );
    doubleTimeseriesPropertyDefinitionData1->SetMaxValue( 4060860242758567.5 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *doubleTimeseriesPropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto doubleTimeseriesPropertyDefinitionData2 = std::reinterpret_pointer_cast<DoubleTimeseriesPropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = doubleTimeseriesPropertyDefinitionData2->IsEqualTo( *doubleTimeseriesPropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GuidTimeseriesPropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( GuidTimeseriesPropertyDefinitionDataSerializationTest )
{
    auto guidTimeseriesPropertyDefinitionData1 = std::make_shared<GuidTimeseriesPropertyDefinitionData>( );
    guidTimeseriesPropertyDefinitionData1->SetId( Guid( L"{088AD988-3F9D-3CBF-3CFD-FCB910519B11}" ) );
    guidTimeseriesPropertyDefinitionData1->SetRowVersion( 4377287306513144200LL );
    guidTimeseriesPropertyDefinitionData1->SetElementType( Guid( L"{088AD988-3F9D-3CBF-3CFD-FCB910519B11}" ) );
    guidTimeseriesPropertyDefinitionData1->SetName( L"Name" );
    guidTimeseriesPropertyDefinitionData1->SetDescription( L"Description" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *guidTimeseriesPropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto guidTimeseriesPropertyDefinitionData2 = std::reinterpret_pointer_cast<GuidTimeseriesPropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = guidTimeseriesPropertyDefinitionData2->IsEqualTo( *guidTimeseriesPropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int16TimeseriesPropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( Int16TimeseriesPropertyDefinitionDataSerializationTest )
{
    auto int16TimeseriesPropertyDefinitionData1 = std::make_shared<Int16TimeseriesPropertyDefinitionData>( );
    int16TimeseriesPropertyDefinitionData1->SetId( Guid( L"{6C0E69F3-88CA-5397-CAE9-1153367096CF}" ) );
    int16TimeseriesPropertyDefinitionData1->SetRowVersion( 6023433429608983027LL );
    int16TimeseriesPropertyDefinitionData1->SetElementType( Guid( L"{6C0E69F3-88CA-5397-CAE9-1153367096CF}" ) );
    int16TimeseriesPropertyDefinitionData1->SetName( L"Name" );
    int16TimeseriesPropertyDefinitionData1->SetDescription( L"Description" );
    int16TimeseriesPropertyDefinitionData1->SetMinValue( 27123 );
    int16TimeseriesPropertyDefinitionData1->SetMaxValue( 27123 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int16TimeseriesPropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int16TimeseriesPropertyDefinitionData2 = std::reinterpret_pointer_cast<Int16TimeseriesPropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = int16TimeseriesPropertyDefinitionData2->IsEqualTo( *int16TimeseriesPropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int32TimeseriesPropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( Int32TimeseriesPropertyDefinitionDataSerializationTest )
{
    auto int32TimeseriesPropertyDefinitionData1 = std::make_shared<Int32TimeseriesPropertyDefinitionData>( );
    int32TimeseriesPropertyDefinitionData1->SetId( Guid( L"{DE0CFE79-3172-12E2-4847-8C4E7B307F9E}" ) );
    int32TimeseriesPropertyDefinitionData1->SetRowVersion( 1360704406840737401LL );
    int32TimeseriesPropertyDefinitionData1->SetElementType( Guid( L"{DE0CFE79-3172-12E2-4847-8C4E7B307F9E}" ) );
    int32TimeseriesPropertyDefinitionData1->SetName( L"Name" );
    int32TimeseriesPropertyDefinitionData1->SetDescription( L"Description" );
    int32TimeseriesPropertyDefinitionData1->SetMinValue( -569573767L );
    int32TimeseriesPropertyDefinitionData1->SetMaxValue( -569573767L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int32TimeseriesPropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int32TimeseriesPropertyDefinitionData2 = std::reinterpret_pointer_cast<Int32TimeseriesPropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = int32TimeseriesPropertyDefinitionData2->IsEqualTo( *int32TimeseriesPropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int64TimeseriesPropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( Int64TimeseriesPropertyDefinitionDataSerializationTest )
{
    auto int64TimeseriesPropertyDefinitionData1 = std::make_shared<Int64TimeseriesPropertyDefinitionData>( );
    int64TimeseriesPropertyDefinitionData1->SetId( Guid( L"{8CDFCEF0-E7E4-7D31-BE8C-E72731FB730F}" ) );
    int64TimeseriesPropertyDefinitionData1->SetRowVersion( 9021246497401851632LL );
    int64TimeseriesPropertyDefinitionData1->SetElementType( Guid( L"{8CDFCEF0-E7E4-7D31-BE8C-E72731FB730F}" ) );
    int64TimeseriesPropertyDefinitionData1->SetName( L"Name" );
    int64TimeseriesPropertyDefinitionData1->SetDescription( L"Description" );
    int64TimeseriesPropertyDefinitionData1->SetMinValue( 9021246497401851632LL );
    int64TimeseriesPropertyDefinitionData1->SetMaxValue( 9021246497401851632LL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int64TimeseriesPropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int64TimeseriesPropertyDefinitionData2 = std::reinterpret_pointer_cast<Int64TimeseriesPropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = int64TimeseriesPropertyDefinitionData2->IsEqualTo( *int64TimeseriesPropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ReferenceTimeseriesPropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( ReferenceTimeseriesPropertyDefinitionDataSerializationTest )
{
    auto referenceTimeseriesPropertyDefinitionData1 = std::make_shared<ReferenceTimeseriesPropertyDefinitionData>( );
    referenceTimeseriesPropertyDefinitionData1->SetId( Guid( L"{CDCD2121-BA93-91C1-8983-5DC9B3B38484}" ) );
    referenceTimeseriesPropertyDefinitionData1->SetRowVersion( -7943863123729112799LL );
    referenceTimeseriesPropertyDefinitionData1->SetElementType( Guid( L"{CDCD2121-BA93-91C1-8983-5DC9B3B38484}" ) );
    referenceTimeseriesPropertyDefinitionData1->SetName( L"Name" );
    referenceTimeseriesPropertyDefinitionData1->SetDescription( L"Description" );
    referenceTimeseriesPropertyDefinitionData1->SetReferencedElementType( Guid( L"{CDCD2121-BA93-91C1-8983-5DC9B3B38484}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *referenceTimeseriesPropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto referenceTimeseriesPropertyDefinitionData2 = std::reinterpret_pointer_cast<ReferenceTimeseriesPropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = referenceTimeseriesPropertyDefinitionData2->IsEqualTo( *referenceTimeseriesPropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SByteTimeseriesPropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( SByteTimeseriesPropertyDefinitionDataSerializationTest )
{
    auto sByteTimeseriesPropertyDefinitionData1 = std::make_shared<SByteTimeseriesPropertyDefinitionData>( );
    sByteTimeseriesPropertyDefinitionData1->SetId( Guid( L"{B0BAF218-A4E2-B4A4-2D25-25470D5D4F18}" ) );
    sByteTimeseriesPropertyDefinitionData1->SetRowVersion( -5430033957167369704LL );
    sByteTimeseriesPropertyDefinitionData1->SetElementType( Guid( L"{B0BAF218-A4E2-B4A4-2D25-25470D5D4F18}" ) );
    sByteTimeseriesPropertyDefinitionData1->SetName( L"Name" );
    sByteTimeseriesPropertyDefinitionData1->SetDescription( L"Description" );
    sByteTimeseriesPropertyDefinitionData1->SetMinValue( 24 );
    sByteTimeseriesPropertyDefinitionData1->SetMaxValue( 24 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *sByteTimeseriesPropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto sByteTimeseriesPropertyDefinitionData2 = std::reinterpret_pointer_cast<SByteTimeseriesPropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = sByteTimeseriesPropertyDefinitionData2->IsEqualTo( *sByteTimeseriesPropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SingleTimeseriesPropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( SingleTimeseriesPropertyDefinitionDataSerializationTest )
{
    auto singleTimeseriesPropertyDefinitionData1 = std::make_shared<SingleTimeseriesPropertyDefinitionData>( );
    singleTimeseriesPropertyDefinitionData1->SetId( Guid( L"{A67FFEFA-2C3D-83A1-C185-34BC65FE7F5F}" ) );
    singleTimeseriesPropertyDefinitionData1->SetRowVersion( -8961833140192542982LL );
    singleTimeseriesPropertyDefinitionData1->SetElementType( Guid( L"{A67FFEFA-2C3D-83A1-C185-34BC65FE7F5F}" ) );
    singleTimeseriesPropertyDefinitionData1->SetName( L"Name" );
    singleTimeseriesPropertyDefinitionData1->SetDescription( L"Description" );
    singleTimeseriesPropertyDefinitionData1->SetMinValue( 9.48491e+15f );
    singleTimeseriesPropertyDefinitionData1->SetMaxValue( 9.48491e+15f );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *singleTimeseriesPropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto singleTimeseriesPropertyDefinitionData2 = std::reinterpret_pointer_cast<SingleTimeseriesPropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = singleTimeseriesPropertyDefinitionData2->IsEqualTo( *singleTimeseriesPropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/StringTimeseriesPropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( StringTimeseriesPropertyDefinitionDataSerializationTest )
{
    auto stringTimeseriesPropertyDefinitionData1 = std::make_shared<StringTimeseriesPropertyDefinitionData>( );
    stringTimeseriesPropertyDefinitionData1->SetId( Guid( L"{C7C18C82-FC7B-A3D4-C52B-3FDEE3833141}" ) );
    stringTimeseriesPropertyDefinitionData1->SetRowVersion( -6641405941902111614LL );
    stringTimeseriesPropertyDefinitionData1->SetElementType( Guid( L"{C7C18C82-FC7B-A3D4-C52B-3FDEE3833141}" ) );
    stringTimeseriesPropertyDefinitionData1->SetName( L"Name" );
    stringTimeseriesPropertyDefinitionData1->SetDescription( L"Description" );
    stringTimeseriesPropertyDefinitionData1->SetPattern( L"Pattern" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *stringTimeseriesPropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto stringTimeseriesPropertyDefinitionData2 = std::reinterpret_pointer_cast<StringTimeseriesPropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = stringTimeseriesPropertyDefinitionData2->IsEqualTo( *stringTimeseriesPropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TimeSpanTimeseriesPropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( TimeSpanTimeseriesPropertyDefinitionDataSerializationTest )
{
    auto timeSpanTimeseriesPropertyDefinitionData1 = std::make_shared<TimeSpanTimeseriesPropertyDefinitionData>( );
    timeSpanTimeseriesPropertyDefinitionData1->SetId( Guid( L"{C866A1C9-1559-99CA-9953-A89A13668593}" ) );
    timeSpanTimeseriesPropertyDefinitionData1->SetRowVersion( -7365050765252582967LL );
    timeSpanTimeseriesPropertyDefinitionData1->SetElementType( Guid( L"{C866A1C9-1559-99CA-9953-A89A13668593}" ) );
    timeSpanTimeseriesPropertyDefinitionData1->SetName( L"Name" );
    timeSpanTimeseriesPropertyDefinitionData1->SetDescription( L"Description" );
    timeSpanTimeseriesPropertyDefinitionData1->SetMinValue( TimeSpan( -269252582967LL ) );
    timeSpanTimeseriesPropertyDefinitionData1->SetMaxValue( TimeSpan( -269252582967LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *timeSpanTimeseriesPropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto timeSpanTimeseriesPropertyDefinitionData2 = std::reinterpret_pointer_cast<TimeSpanTimeseriesPropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = timeSpanTimeseriesPropertyDefinitionData2->IsEqualTo( *timeSpanTimeseriesPropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt16TimeseriesPropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( UInt16TimeseriesPropertyDefinitionDataSerializationTest )
{
    auto uInt16TimeseriesPropertyDefinitionData1 = std::make_shared<UInt16TimeseriesPropertyDefinitionData>( );
    uInt16TimeseriesPropertyDefinitionData1->SetId( Guid( L"{F3BC9551-294D-F34D-CFB2-94B2CF3DA98A}" ) );
    uInt16TimeseriesPropertyDefinitionData1->SetRowVersion( -915029734507899567LL );
    uInt16TimeseriesPropertyDefinitionData1->SetElementType( Guid( L"{F3BC9551-294D-F34D-CFB2-94B2CF3DA98A}" ) );
    uInt16TimeseriesPropertyDefinitionData1->SetName( L"Name" );
    uInt16TimeseriesPropertyDefinitionData1->SetDescription( L"Description" );
    uInt16TimeseriesPropertyDefinitionData1->SetMinValue( 38225 );
    uInt16TimeseriesPropertyDefinitionData1->SetMaxValue( 38225 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt16TimeseriesPropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt16TimeseriesPropertyDefinitionData2 = std::reinterpret_pointer_cast<UInt16TimeseriesPropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = uInt16TimeseriesPropertyDefinitionData2->IsEqualTo( *uInt16TimeseriesPropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt32TimeseriesPropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( UInt32TimeseriesPropertyDefinitionDataSerializationTest )
{
    auto uInt32TimeseriesPropertyDefinitionData1 = std::make_shared<UInt32TimeseriesPropertyDefinitionData>( );
    uInt32TimeseriesPropertyDefinitionData1->SetId( Guid( L"{D8704723-5980-F88B-1FD1-9A011B0EE2C4}" ) );
    uInt32TimeseriesPropertyDefinitionData1->SetRowVersion( -537237320618719453LL );
    uInt32TimeseriesPropertyDefinitionData1->SetElementType( Guid( L"{D8704723-5980-F88B-1FD1-9A011B0EE2C4}" ) );
    uInt32TimeseriesPropertyDefinitionData1->SetName( L"Name" );
    uInt32TimeseriesPropertyDefinitionData1->SetDescription( L"Description" );
    uInt32TimeseriesPropertyDefinitionData1->SetMinValue( 3631236899UL );
    uInt32TimeseriesPropertyDefinitionData1->SetMaxValue( 3631236899UL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt32TimeseriesPropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt32TimeseriesPropertyDefinitionData2 = std::reinterpret_pointer_cast<UInt32TimeseriesPropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = uInt32TimeseriesPropertyDefinitionData2->IsEqualTo( *uInt32TimeseriesPropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt64TimeseriesPropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( UInt64TimeseriesPropertyDefinitionDataSerializationTest )
{
    auto uInt64TimeseriesPropertyDefinitionData1 = std::make_shared<UInt64TimeseriesPropertyDefinitionData>( );
    uInt64TimeseriesPropertyDefinitionData1->SetId( Guid( L"{7229235C-4357-C2CC-4333-C2EA4E94C43A}" ) );
    uInt64TimeseriesPropertyDefinitionData1->SetRowVersion( -4410075892246043812LL );
    uInt64TimeseriesPropertyDefinitionData1->SetElementType( Guid( L"{7229235C-4357-C2CC-4333-C2EA4E94C43A}" ) );
    uInt64TimeseriesPropertyDefinitionData1->SetName( L"Name" );
    uInt64TimeseriesPropertyDefinitionData1->SetDescription( L"Description" );
    uInt64TimeseriesPropertyDefinitionData1->SetMinValue( -4410075892246043812LL );
    uInt64TimeseriesPropertyDefinitionData1->SetMaxValue( -4410075892246043812LL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt64TimeseriesPropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt64TimeseriesPropertyDefinitionData2 = std::reinterpret_pointer_cast<UInt64TimeseriesPropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = uInt64TimeseriesPropertyDefinitionData2->IsEqualTo( *uInt64TimeseriesPropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TimeSpanPropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( TimeSpanPropertyDefinitionDataSerializationTest )
{
    auto timeSpanPropertyDefinitionData1 = std::make_shared<TimeSpanPropertyDefinitionData>( );
    timeSpanPropertyDefinitionData1->SetId( Guid( L"{FB970DDC-44F0-59DE-9A7B-220FDFE9B03B}" ) );
    timeSpanPropertyDefinitionData1->SetRowVersion( 6475689116009172444LL );
    timeSpanPropertyDefinitionData1->SetElementType( Guid( L"{FB970DDC-44F0-59DE-9A7B-220FDFE9B03B}" ) );
    timeSpanPropertyDefinitionData1->SetName( L"Name" );
    timeSpanPropertyDefinitionData1->SetDescription( L"Description" );
    timeSpanPropertyDefinitionData1->SetDefaultValue( TimeSpan( 476009172444LL ) );
    timeSpanPropertyDefinitionData1->SetMinValue( TimeSpan( 476009172444LL ) );
    timeSpanPropertyDefinitionData1->SetMaxValue( TimeSpan( 476009172444LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *timeSpanPropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto timeSpanPropertyDefinitionData2 = std::reinterpret_pointer_cast<TimeSpanPropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = timeSpanPropertyDefinitionData2->IsEqualTo( *timeSpanPropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt16PropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( UInt16PropertyDefinitionDataSerializationTest )
{
    auto uInt16PropertyDefinitionData1 = std::make_shared<UInt16PropertyDefinitionData>( );
    uInt16PropertyDefinitionData1->SetId( Guid( L"{9F86CE66-6677-86AB-61D5-66EEF9617366}" ) );
    uInt16PropertyDefinitionData1->SetRowVersion( -8742781587646132634LL );
    uInt16PropertyDefinitionData1->SetElementType( Guid( L"{9F86CE66-6677-86AB-61D5-66EEF9617366}" ) );
    uInt16PropertyDefinitionData1->SetName( L"Name" );
    uInt16PropertyDefinitionData1->SetDescription( L"Description" );
    uInt16PropertyDefinitionData1->SetDefaultValue( 52838 );
    uInt16PropertyDefinitionData1->SetMinValue( 52838 );
    uInt16PropertyDefinitionData1->SetMaxValue( 52838 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt16PropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt16PropertyDefinitionData2 = std::reinterpret_pointer_cast<UInt16PropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = uInt16PropertyDefinitionData2->IsEqualTo( *uInt16PropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt32PropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( UInt32PropertyDefinitionDataSerializationTest )
{
    auto uInt32PropertyDefinitionData1 = std::make_shared<UInt32PropertyDefinitionData>( );
    uInt32PropertyDefinitionData1->SetId( Guid( L"{6B546007-C7C5-E702-E740-E3A3D62A06E0}" ) );
    uInt32PropertyDefinitionData1->SetRowVersion( -1800657250271600633LL );
    uInt32PropertyDefinitionData1->SetElementType( Guid( L"{6B546007-C7C5-E702-E740-E3A3D62A06E0}" ) );
    uInt32PropertyDefinitionData1->SetName( L"Name" );
    uInt32PropertyDefinitionData1->SetDescription( L"Description" );
    uInt32PropertyDefinitionData1->SetDefaultValue( 1800691719UL );
    uInt32PropertyDefinitionData1->SetMinValue( 1800691719UL );
    uInt32PropertyDefinitionData1->SetMaxValue( 1800691719UL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt32PropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt32PropertyDefinitionData2 = std::reinterpret_pointer_cast<UInt32PropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = uInt32PropertyDefinitionData2->IsEqualTo( *uInt32PropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt64PropertyDefinitionDataSerializationTest
BOOST_AUTO_TEST_CASE( UInt64PropertyDefinitionDataSerializationTest )
{
    auto uInt64PropertyDefinitionData1 = std::make_shared<UInt64PropertyDefinitionData>( );
    uInt64PropertyDefinitionData1->SetId( Guid( L"{7E8D58B1-7982-8BF7-D1EF-9E417EB11A8D}" ) );
    uInt64PropertyDefinitionData1->SetRowVersion( -8361080581814134607LL );
    uInt64PropertyDefinitionData1->SetElementType( Guid( L"{7E8D58B1-7982-8BF7-D1EF-9E417EB11A8D}" ) );
    uInt64PropertyDefinitionData1->SetName( L"Name" );
    uInt64PropertyDefinitionData1->SetDescription( L"Description" );
    uInt64PropertyDefinitionData1->SetDefaultValue( -8361080581814134607LL );
    uInt64PropertyDefinitionData1->SetMinValue( -8361080581814134607LL );
    uInt64PropertyDefinitionData1->SetMaxValue( -8361080581814134607LL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt64PropertyDefinitionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt64PropertyDefinitionData2 = std::reinterpret_pointer_cast<UInt64PropertyDefinitionData>( ReadDataFrom( source ) );
    bool equal = uInt64PropertyDefinitionData2->IsEqualTo( *uInt64PropertyDefinitionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarAlarmStatusDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarAlarmStatusDataSerializationTest )
{
    auto radarAlarmStatusData1 = std::make_shared<RadarAlarmStatusData>( );
    radarAlarmStatusData1->SetId( Guid( L"{6591FD22-1881-3763-ECC6-1881A689BF44}" ) );
    radarAlarmStatusData1->SetRowVersion( 3991060638814305570LL );
    radarAlarmStatusData1->SetRadar( Guid( L"{6591FD22-1881-3763-ECC6-1881A689BF44}" ) );
    radarAlarmStatusData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    radarAlarmStatusData1->SetType( AlarmState::Raised );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarAlarmStatusData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarAlarmStatusData2 = std::reinterpret_pointer_cast<RadarAlarmStatusData>( ReadDataFrom( source ) );
    bool equal = radarAlarmStatusData2->IsEqualTo( *radarAlarmStatusData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarCommandDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarCommandDataSerializationTest )
{
    auto radarCommandData1 = std::make_shared<RadarCommandData>( );
    radarCommandData1->SetId( Guid( L"{09E2F261-F724-AF90-F509-EF2490474F86}" ) );
    radarCommandData1->SetRowVersion( -5795860986269076895LL );
    radarCommandData1->SetRadar( Guid( L"{09E2F261-F724-AF90-F509-EF2490474F86}" ) );
    radarCommandData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    radarCommandData1->SetDeviceCommandSourceType( DeviceCommandSourceType::Session );
    radarCommandData1->SetDeviceCommandSourceId( Guid( L"{09E2F261-F724-AF90-F509-EF2490474F86}" ) );
    radarCommandData1->SetReply( Guid( L"{09E2F261-F724-AF90-F509-EF2490474F86}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarCommandData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarCommandData2 = std::reinterpret_pointer_cast<RadarCommandData>( ReadDataFrom( source ) );
    bool equal = radarCommandData2->IsEqualTo( *radarCommandData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarCommandGetStatusDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarCommandGetStatusDataSerializationTest )
{
    auto radarCommandGetStatusData1 = std::make_shared<RadarCommandGetStatusData>( );
    radarCommandGetStatusData1->SetId( Guid( L"{15DB63DD-58A5-93F1-C98F-1AA5A8DBC6BB}" ) );
    radarCommandGetStatusData1->SetRowVersion( -7786344814687329315LL );
    radarCommandGetStatusData1->SetRadar( Guid( L"{15DB63DD-58A5-93F1-C98F-1AA5A8DBC6BB}" ) );
    radarCommandGetStatusData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    radarCommandGetStatusData1->SetDeviceCommandSourceType( DeviceCommandSourceType::Session );
    radarCommandGetStatusData1->SetDeviceCommandSourceId( Guid( L"{15DB63DD-58A5-93F1-C98F-1AA5A8DBC6BB}" ) );
    radarCommandGetStatusData1->SetReply( Guid( L"{15DB63DD-58A5-93F1-C98F-1AA5A8DBC6BB}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarCommandGetStatusData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarCommandGetStatusData2 = std::reinterpret_pointer_cast<RadarCommandGetStatusData>( ReadDataFrom( source ) );
    bool equal = radarCommandGetStatusData2->IsEqualTo( *radarCommandGetStatusData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarCommandReplyDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarCommandReplyDataSerializationTest )
{
    auto radarCommandReplyData1 = std::make_shared<RadarCommandReplyData>( );
    radarCommandReplyData1->SetId( Guid( L"{A338B9CF-C23E-6B8E-D671-437CC51C9DF3}" ) );
    radarCommandReplyData1->SetRowVersion( 7750345583033366991LL );
    radarCommandReplyData1->SetRadar( Guid( L"{A338B9CF-C23E-6B8E-D671-437CC51C9DF3}" ) );
    radarCommandReplyData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    radarCommandReplyData1->SetCommand( Guid( L"{A338B9CF-C23E-6B8E-D671-437CC51C9DF3}" ) );
    radarCommandReplyData1->SetStatus( DeviceCommandReplyStatus::Error );
    radarCommandReplyData1->SetMessage( L"Message" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarCommandReplyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarCommandReplyData2 = std::reinterpret_pointer_cast<RadarCommandReplyData>( ReadDataFrom( source ) );
    bool equal = radarCommandReplyData2->IsEqualTo( *radarCommandReplyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarCommandReplyGetStatusDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarCommandReplyGetStatusDataSerializationTest )
{
    auto radarCommandReplyGetStatusData1 = std::make_shared<RadarCommandReplyGetStatusData>( );
    radarCommandReplyGetStatusData1->SetId( Guid( L"{76904A9F-BEF0-E591-A789-7D0F6E0952F9}" ) );
    radarCommandReplyGetStatusData1->SetRowVersion( -1904531227410412897LL );
    radarCommandReplyGetStatusData1->SetRadar( Guid( L"{76904A9F-BEF0-E591-A789-7D0F6E0952F9}" ) );
    radarCommandReplyGetStatusData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    radarCommandReplyGetStatusData1->SetCommand( Guid( L"{76904A9F-BEF0-E591-A789-7D0F6E0952F9}" ) );
    radarCommandReplyGetStatusData1->SetStatus( DeviceCommandReplyStatus::Error );
    radarCommandReplyGetStatusData1->SetMessage( L"Message" );
    radarCommandReplyGetStatusData1->SetAzimuthCount( 1989167775L );
    radarCommandReplyGetStatusData1->SetTriggerCount( 1989167775L );
    radarCommandReplyGetStatusData1->SetRotationCount( TimeSpan( -475410412897LL ) );
    radarCommandReplyGetStatusData1->SetPulse( RadarPulse::Short );
    radarCommandReplyGetStatusData1->SetTx( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarCommandReplyGetStatusData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarCommandReplyGetStatusData2 = std::reinterpret_pointer_cast<RadarCommandReplyGetStatusData>( ReadDataFrom( source ) );
    bool equal = radarCommandReplyGetStatusData2->IsEqualTo( *radarCommandReplyGetStatusData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarConfigurationDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarConfigurationDataSerializationTest )
{
    auto radarConfigurationData1 = std::make_shared<RadarConfigurationData>( );
    radarConfigurationData1->SetId( Guid( L"{B52CAF4D-4966-5963-9AC6-9266AD34F5B2}" ) );
    radarConfigurationData1->SetRowVersion( 6441072597545037645LL );
    radarConfigurationData1->SetRadar( Guid( L"{B52CAF4D-4966-5963-9AC6-9266AD34F5B2}" ) );
    radarConfigurationData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    radarConfigurationData1->SetRadarProtocolVersion( -1255362739L );
    radarConfigurationData1->SetRadarIPAddress( L"RadarIPAddress" );
    radarConfigurationData1->SetRadarPort( -1255362739L );
    radarConfigurationData1->SetRadarConfigurationPort( -1255362739L );
    radarConfigurationData1->SetSkipMagicTimeout( TimeSpan( 117545037645LL ) );
    radarConfigurationData1->SetReadTimeout( TimeSpan( 117545037645LL ) );
    radarConfigurationData1->SetSynchronizationInterval( TimeSpan( 117545037645LL ) );
    radarConfigurationData1->SetTargetsRefreshRate( -1255362739L );
    radarConfigurationData1->SetRange( -1255362739L );
    radarConfigurationData1->SetSectorCount( -1255362739L );
    radarConfigurationData1->SetSectorOffset( -1255362739L );
    radarConfigurationData1->SetImageColor( 3039604557UL );
    radarConfigurationData1->SetImageSubstitutionColor( 3039604557UL );
    radarConfigurationData1->SetTransparentColor( 3039604557UL );
    radarConfigurationData1->SetImageScaleFactorX( 6441072597545038 );
    radarConfigurationData1->SetImageOffsetX( 6441072597545038 );
    radarConfigurationData1->SetImageScaleFactorY( 6441072597545038 );
    radarConfigurationData1->SetImageOffsetY( 6441072597545038 );
    radarConfigurationData1->SetRadarImageType( RadarImageType::VideoMask );
    radarConfigurationData1->SetTrackColor( 3039604557UL );
    radarConfigurationData1->SetVectorColor( 3039604557UL );
    radarConfigurationData1->SetEnableNmea( false );
    radarConfigurationData1->SetNmeaReceiverIPAddress( L"NmeaReceiverIPAddress" );
    radarConfigurationData1->SetNmeaReceiverPort( -1255362739L );
    radarConfigurationData1->SetNmeaReceiverSourceId( L"NmeaReceiverSourceId" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarConfigurationData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarConfigurationData2 = std::reinterpret_pointer_cast<RadarConfigurationData>( ReadDataFrom( source ) );
    bool equal = radarConfigurationData2->IsEqualTo( *radarConfigurationData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarImageDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarImageDataSerializationTest )
{
    auto radarImageData1 = std::make_shared<RadarImageData>( );
    radarImageData1->SetId( Guid( L"{E255597A-EAB9-8A6B-51D6-579D47AA9A5E}" ) );
    radarImageData1->SetRowVersion( -8472420189880362630LL );
    radarImageData1->SetRadar( Guid( L"{E255597A-EAB9-8A6B-51D6-579D47AA9A5E}" ) );
    radarImageData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    radarImageData1->SetDepth( 3797244282UL );
    radarImageData1->SetResolution( -497723014L );
    radarImageData1->SetRange( -497723014L );
    radarImageData1->SetImage( { {'I','m','a','g','e'} } );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarImageData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarImageData2 = std::reinterpret_pointer_cast<RadarImageData>( ReadDataFrom( source ) );
    bool equal = radarImageData2->IsEqualTo( *radarImageData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarRawTrackTableDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarRawTrackTableDataSerializationTest )
{
    auto radarRawTrackTableData1 = std::make_shared<RadarRawTrackTableData>( );
    radarRawTrackTableData1->SetId( Guid( L"{987A5FFC-22C5-4193-82C9-44A3195EFA3F}" ) );
    radarRawTrackTableData1->SetRowVersion( 4725158666103840764LL );
    radarRawTrackTableData1->SetRadar( Guid( L"{987A5FFC-22C5-4193-82C9-44A3195EFA3F}" ) );
    radarRawTrackTableData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    radarRawTrackTableData1->SetCount( -1736810500L );
    radarRawTrackTableData1->SetTable( { {'T','a','b','l','e'} } );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarRawTrackTableData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarRawTrackTableData2 = std::reinterpret_pointer_cast<RadarRawTrackTableData>( ReadDataFrom( source ) );
    bool equal = radarRawTrackTableData2->IsEqualTo( *radarRawTrackTableData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarStatusDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarStatusDataSerializationTest )
{
    auto radarStatusData1 = std::make_shared<RadarStatusData>( );
    radarStatusData1->SetId( Guid( L"{02607B8B-1D3F-7C67-3EE6-B8FC4006DED1}" ) );
    radarStatusData1->SetRowVersion( 8964165739764284299LL );
    radarStatusData1->SetRadar( Guid( L"{02607B8B-1D3F-7C67-3EE6-B8FC4006DED1}" ) );
    radarStatusData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    radarStatusData1->SetAzimuthCount( 39877515L );
    radarStatusData1->SetTriggerCount( 39877515L );
    radarStatusData1->SetRotationTime( TimeSpan( 715764284299LL ) );
    radarStatusData1->SetPulse( RadarPulse::Medium );
    radarStatusData1->SetTx( false );
    radarStatusData1->SetTracking( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarStatusData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarStatusData2 = std::reinterpret_pointer_cast<RadarStatusData>( ReadDataFrom( source ) );
    bool equal = radarStatusData2->IsEqualTo( *radarStatusData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadioCommandDataSerializationTest
BOOST_AUTO_TEST_CASE( RadioCommandDataSerializationTest )
{
    auto radioCommandData1 = std::make_shared<RadioCommandData>( );
    radioCommandData1->SetId( Guid( L"{2E60CDCD-C816-0913-90C8-13687406B3B3}" ) );
    radioCommandData1->SetRowVersion( 654086368491785677LL );
    radioCommandData1->SetRadio( Guid( L"{2E60CDCD-C816-0913-90C8-13687406B3B3}" ) );
    radioCommandData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    radioCommandData1->SetDeviceCommandSourceType( DeviceCommandSourceType::Session );
    radioCommandData1->SetDeviceCommandSourceId( Guid( L"{2E60CDCD-C816-0913-90C8-13687406B3B3}" ) );
    radioCommandData1->SetReply( Guid( L"{2E60CDCD-C816-0913-90C8-13687406B3B3}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radioCommandData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radioCommandData2 = std::reinterpret_pointer_cast<RadioCommandData>( ReadDataFrom( source ) );
    bool equal = radioCommandData2->IsEqualTo( *radioCommandData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadioCommandReplyDataSerializationTest
BOOST_AUTO_TEST_CASE( RadioCommandReplyDataSerializationTest )
{
    auto radioCommandReplyData1 = std::make_shared<RadioCommandReplyData>( );
    radioCommandReplyData1->SetId( Guid( L"{4196677A-F28B-98D7-19EB-4FD18269E65E}" ) );
    radioCommandReplyData1->SetRowVersion( -7433205980036962438LL );
    radioCommandReplyData1->SetRadio( Guid( L"{4196677A-F28B-98D7-19EB-4FD18269E65E}" ) );
    radioCommandReplyData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    radioCommandReplyData1->SetCommand( Guid( L"{4196677A-F28B-98D7-19EB-4FD18269E65E}" ) );
    radioCommandReplyData1->SetStatus( DeviceCommandReplyStatus::NotImplemented );
    radioCommandReplyData1->SetMessage( L"Message" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radioCommandReplyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radioCommandReplyData2 = std::reinterpret_pointer_cast<RadioCommandReplyData>( ReadDataFrom( source ) );
    bool equal = radioCommandReplyData2->IsEqualTo( *radioCommandReplyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadioConfigurationDataSerializationTest
BOOST_AUTO_TEST_CASE( RadioConfigurationDataSerializationTest )
{
    auto radioConfigurationData1 = std::make_shared<RadioConfigurationData>( );
    radioConfigurationData1->SetId( Guid( L"{AB4C66CF-5346-E4F6-276F-CA62D53266F3}" ) );
    radioConfigurationData1->SetRowVersion( -1948278225804433713LL );
    radioConfigurationData1->SetRadio( Guid( L"{AB4C66CF-5346-E4F6-276F-CA62D53266F3}" ) );
    radioConfigurationData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    radioConfigurationData1->SetLongitude( 16498465847905118 );
    radioConfigurationData1->SetLatitude( 16498465847905118 );
    radioConfigurationData1->SetPlaybackUrl( L"PlaybackUrl" );
    radioConfigurationData1->SetRadioIPAddress( L"RadioIPAddress" );
    radioConfigurationData1->SetRadioPort( -1421056305L );
    radioConfigurationData1->SetEd137IPAddress( L"Ed137IPAddress" );
    radioConfigurationData1->SetEd137Port( -1421056305L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radioConfigurationData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radioConfigurationData2 = std::reinterpret_pointer_cast<RadioConfigurationData>( ReadDataFrom( source ) );
    bool equal = radioConfigurationData2->IsEqualTo( *radioConfigurationData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadomeCommandDataSerializationTest
BOOST_AUTO_TEST_CASE( RadomeCommandDataSerializationTest )
{
    auto radomeCommandData1 = std::make_shared<RadomeCommandData>( );
    radomeCommandData1->SetId( Guid( L"{3C06BA91-1621-4C7A-325E-68843C605D89}" ) );
    radomeCommandData1->SetRowVersion( 5510741426038028945LL );
    radomeCommandData1->SetRadome( Guid( L"{3C06BA91-1621-4C7A-325E-68843C605D89}" ) );
    radomeCommandData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    radomeCommandData1->SetDeviceCommandSourceType( DeviceCommandSourceType::Session );
    radomeCommandData1->SetDeviceCommandSourceId( Guid( L"{3C06BA91-1621-4C7A-325E-68843C605D89}" ) );
    radomeCommandData1->SetReply( Guid( L"{3C06BA91-1621-4C7A-325E-68843C605D89}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radomeCommandData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radomeCommandData2 = std::reinterpret_pointer_cast<RadomeCommandData>( ReadDataFrom( source ) );
    bool equal = radomeCommandData2->IsEqualTo( *radomeCommandData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadomeCommandReplyDataSerializationTest
BOOST_AUTO_TEST_CASE( RadomeCommandReplyDataSerializationTest )
{
    auto radomeCommandReplyData1 = std::make_shared<RadomeCommandReplyData>( );
    radomeCommandReplyData1->SetId( Guid( L"{6A296804-C699-97E0-E907-639956941620}" ) );
    radomeCommandReplyData1->SetRowVersion( -7502778616985851900LL );
    radomeCommandReplyData1->SetRadome( Guid( L"{6A296804-C699-97E0-E907-639956941620}" ) );
    radomeCommandReplyData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    radomeCommandReplyData1->SetCommand( Guid( L"{6A296804-C699-97E0-E907-639956941620}" ) );
    radomeCommandReplyData1->SetStatus( DeviceCommandReplyStatus::Unknown );
    radomeCommandReplyData1->SetMessage( L"Message" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radomeCommandReplyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radomeCommandReplyData2 = std::reinterpret_pointer_cast<RadomeCommandReplyData>( ReadDataFrom( source ) );
    bool equal = radomeCommandReplyData2->IsEqualTo( *radomeCommandReplyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadomeConfigurationDataSerializationTest
BOOST_AUTO_TEST_CASE( RadomeConfigurationDataSerializationTest )
{
    auto radomeConfigurationData1 = std::make_shared<RadomeConfigurationData>( );
    radomeConfigurationData1->SetId( Guid( L"{2F8DD664-7BE7-739B-CED9-DEE7F4B16B26}" ) );
    radomeConfigurationData1->SetRowVersion( 8330388168617350756LL );
    radomeConfigurationData1->SetRadome( Guid( L"{2F8DD664-7BE7-739B-CED9-DEE7F4B16B26}" ) );
    radomeConfigurationData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    radomeConfigurationData1->SetInterval( TimeSpan( 840617350756LL ) );
    radomeConfigurationData1->SetLowPressureLimit( 8330388168617351 );
    radomeConfigurationData1->SetHighPressureLimit( 8330388168617351 );
    radomeConfigurationData1->SetLowTemperatureLimit( 8330388168617351 );
    radomeConfigurationData1->SetHighTemperatureLimit( 8330388168617351 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radomeConfigurationData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radomeConfigurationData2 = std::reinterpret_pointer_cast<RadomeConfigurationData>( ReadDataFrom( source ) );
    bool equal = radomeConfigurationData2->IsEqualTo( *radomeConfigurationData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ReferenceTimeseriesValueDataSerializationTest
BOOST_AUTO_TEST_CASE( ReferenceTimeseriesValueDataSerializationTest )
{
    auto referenceTimeseriesValueData1 = std::make_shared<ReferenceTimeseriesValueData>( );
    referenceTimeseriesValueData1->SetId( Guid( L"{6F4E97CF-FE10-6D89-B691-7F08F672E9F3}" ) );
    referenceTimeseriesValueData1->SetRowVersion( 7893119168483858383LL );
    referenceTimeseriesValueData1->SetTimeseries( Guid( L"{6F4E97CF-FE10-6D89-B691-7F08F672E9F3}" ) );
    referenceTimeseriesValueData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    referenceTimeseriesValueData1->SetValue( Guid( L"{6F4E97CF-FE10-6D89-B691-7F08F672E9F3}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *referenceTimeseriesValueData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto referenceTimeseriesValueData2 = std::reinterpret_pointer_cast<ReferenceTimeseriesValueData>( ReadDataFrom( source ) );
    bool equal = referenceTimeseriesValueData2->IsEqualTo( *referenceTimeseriesValueData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SByteTimeseriesValueDataSerializationTest
BOOST_AUTO_TEST_CASE( SByteTimeseriesValueDataSerializationTest )
{
    auto sByteTimeseriesValueData1 = std::make_shared<SByteTimeseriesValueData>( );
    sByteTimeseriesValueData1->SetId( Guid( L"{250A9ACA-1D35-8290-4109-B8ACA4505953}" ) );
    sByteTimeseriesValueData1->SetRowVersion( -9038692338040661302LL );
    sByteTimeseriesValueData1->SetTimeseries( Guid( L"{250A9ACA-1D35-8290-4109-B8ACA4505953}" ) );
    sByteTimeseriesValueData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    sByteTimeseriesValueData1->SetValue( -54 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *sByteTimeseriesValueData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto sByteTimeseriesValueData2 = std::reinterpret_pointer_cast<SByteTimeseriesValueData>( ReadDataFrom( source ) );
    bool equal = sByteTimeseriesValueData2->IsEqualTo( *sByteTimeseriesValueData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SecurityDomainDataSerializationTest
BOOST_AUTO_TEST_CASE( SecurityDomainDataSerializationTest )
{
    auto securityDomainData1 = std::make_shared<SecurityDomainData>( );
    securityDomainData1->SetId( Guid( L"{C42DB715-5D41-31B3-8CCD-BA8223B4EDA8}" ) );
    securityDomainData1->SetRowVersion( 3581308665735264021LL );
    securityDomainData1->SetName( L"Name" );
    securityDomainData1->SetDescription( L"Description" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *securityDomainData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto securityDomainData2 = std::reinterpret_pointer_cast<SecurityDomainData>( ReadDataFrom( source ) );
    bool equal = securityDomainData2->IsEqualTo( *securityDomainData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SecurityLoginDataSerializationTest
BOOST_AUTO_TEST_CASE( SecurityLoginDataSerializationTest )
{
    auto securityLoginData1 = std::make_shared<SecurityLoginData>( );
    securityLoginData1->SetId( Guid( L"{2E8F8FDB-0425-DED8-7B1B-20A474F1F1DB}" ) );
    securityLoginData1->SetRowVersion( -2389155044578586661LL );
    securityLoginData1->SetDomain( Guid( L"{2E8F8FDB-0425-DED8-7B1B-20A474F1F1DB}" ) );
    securityLoginData1->SetIdentity( L"Identity" );
    securityLoginData1->SetDescription( L"Description" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *securityLoginData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto securityLoginData2 = std::reinterpret_pointer_cast<SecurityLoginData>( ReadDataFrom( source ) );
    bool equal = securityLoginData2->IsEqualTo( *securityLoginData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SecurityRoleDataSerializationTest
BOOST_AUTO_TEST_CASE( SecurityRoleDataSerializationTest )
{
    auto securityRoleData1 = std::make_shared<SecurityRoleData>( );
    securityRoleData1->SetId( Guid( L"{4563987E-AA39-307D-0CBE-559CA2C6197E}" ) );
    securityRoleData1->SetRowVersion( 3494136048863385726LL );
    securityRoleData1->SetDomain( Guid( L"{4563987E-AA39-307D-0CBE-559CA2C6197E}" ) );
    securityRoleData1->SetIdentity( L"Identity" );
    securityRoleData1->SetDescription( L"Description" );
    securityRoleData1->SetName( L"Name" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *securityRoleData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto securityRoleData2 = std::reinterpret_pointer_cast<SecurityRoleData>( ReadDataFrom( source ) );
    bool equal = securityRoleData2->IsEqualTo( *securityRoleData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SecurityIdentifierRoleLinkDataSerializationTest
BOOST_AUTO_TEST_CASE( SecurityIdentifierRoleLinkDataSerializationTest )
{
    auto securityIdentifierRoleLinkData1 = std::make_shared<SecurityIdentifierRoleLinkData>( );
    securityIdentifierRoleLinkData1->SetId( Guid( L"{08CD1B89-2160-C19D-83B9-840610B3D891}" ) );
    securityIdentifierRoleLinkData1->SetRowVersion( -4495400156697650295LL );
    securityIdentifierRoleLinkData1->SetMember( Guid( L"{08CD1B89-2160-C19D-83B9-840610B3D891}" ) );
    securityIdentifierRoleLinkData1->SetRole( Guid( L"{08CD1B89-2160-C19D-83B9-840610B3D891}" ) );
    securityIdentifierRoleLinkData1->SetStart( DateTime( 1, 1, 1, 14, 37, 6 ) );
    securityIdentifierRoleLinkData1->SetEnd( DateTime( 1, 1, 1, 14, 37, 6 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *securityIdentifierRoleLinkData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto securityIdentifierRoleLinkData2 = std::reinterpret_pointer_cast<SecurityIdentifierRoleLinkData>( ReadDataFrom( source ) );
    bool equal = securityIdentifierRoleLinkData2->IsEqualTo( *securityIdentifierRoleLinkData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SecurityLoginSessionDataSerializationTest
BOOST_AUTO_TEST_CASE( SecurityLoginSessionDataSerializationTest )
{
    auto securityLoginSessionData1 = std::make_shared<SecurityLoginSessionData>( );
    securityLoginSessionData1->SetId( Guid( L"{1600A37D-D48F-A2D7-45EB-2BF16800C5BE}" ) );
    securityLoginSessionData1->SetRowVersion( -6712663008557882499LL );
    securityLoginSessionData1->SetLogin( Guid( L"{1600A37D-D48F-A2D7-45EB-2BF16800C5BE}" ) );
    securityLoginSessionData1->SetFromTime( DateTime( 1, 1, 1, 14, 37, 6 ) );
    securityLoginSessionData1->SetThroughTime( DateTime( 1, 1, 1, 14, 37, 6 ) );
    securityLoginSessionData1->SetClientSession( Guid( L"{1600A37D-D48F-A2D7-45EB-2BF16800C5BE}" ) );
    securityLoginSessionData1->SetNotificationQueueName( L"NotificationQueueName" );
    securityLoginSessionData1->SetMessageQueueName( L"MessageQueueName" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *securityLoginSessionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto securityLoginSessionData2 = std::reinterpret_pointer_cast<SecurityLoginSessionData>( ReadDataFrom( source ) );
    bool equal = securityLoginSessionData2->IsEqualTo( *securityLoginSessionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SecurityPermissionDataSerializationTest
BOOST_AUTO_TEST_CASE( SecurityPermissionDataSerializationTest )
{
    auto securityPermissionData1 = std::make_shared<SecurityPermissionData>( );
    securityPermissionData1->SetId( Guid( L"{9A65967B-785F-8F6C-F136-1EFA59A669DE}" ) );
    securityPermissionData1->SetRowVersion( -8111976476793530757LL );
    securityPermissionData1->SetIdentifier( Guid( L"{9A65967B-785F-8F6C-F136-1EFA59A669DE}" ) );
    securityPermissionData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    securityPermissionData1->SetTypeCode( -1704618373L );
    securityPermissionData1->SetCanCreate( false );
    securityPermissionData1->SetCanRead( false );
    securityPermissionData1->SetCanUpdate( false );
    securityPermissionData1->SetCanDelete( false );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *securityPermissionData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto securityPermissionData2 = std::reinterpret_pointer_cast<SecurityPermissionData>( ReadDataFrom( source ) );
    bool equal = securityPermissionData2->IsEqualTo( *securityPermissionData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SingleTimeseriesValueDataSerializationTest
BOOST_AUTO_TEST_CASE( SingleTimeseriesValueDataSerializationTest )
{
    auto singleTimeseriesValueData1 = std::make_shared<SingleTimeseriesValueData>( );
    singleTimeseriesValueData1->SetId( Guid( L"{295C3FB9-5436-1E12-7848-2A6C943AFC9D}" ) );
    singleTimeseriesValueData1->SetRowVersion( 2166886962317508537LL );
    singleTimeseriesValueData1->SetTimeseries( Guid( L"{295C3FB9-5436-1E12-7848-2A6C943AFC9D}" ) );
    singleTimeseriesValueData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    singleTimeseriesValueData1->SetValue( 2.166887e+15f );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *singleTimeseriesValueData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto singleTimeseriesValueData2 = std::reinterpret_pointer_cast<SingleTimeseriesValueData>( ReadDataFrom( source ) );
    bool equal = singleTimeseriesValueData2->IsEqualTo( *singleTimeseriesValueData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/StringTimeseriesValueDataSerializationTest
BOOST_AUTO_TEST_CASE( StringTimeseriesValueDataSerializationTest )
{
    auto stringTimeseriesValueData1 = std::make_shared<StringTimeseriesValueData>( );
    stringTimeseriesValueData1->SetId( Guid( L"{8151E4E0-9099-AD75-B5AE-0999818A2707}" ) );
    stringTimeseriesValueData1->SetRowVersion( -5947688743898848032LL );
    stringTimeseriesValueData1->SetTimeseries( Guid( L"{8151E4E0-9099-AD75-B5AE-0999818A2707}" ) );
    stringTimeseriesValueData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    stringTimeseriesValueData1->SetValue( L"Value" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *stringTimeseriesValueData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto stringTimeseriesValueData2 = std::reinterpret_pointer_cast<StringTimeseriesValueData>( ReadDataFrom( source ) );
    bool equal = stringTimeseriesValueData2->IsEqualTo( *stringTimeseriesValueData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BinaryTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( BinaryTimeseriesDataSerializationTest )
{
    auto binaryTimeseriesData1 = std::make_shared<BinaryTimeseriesData>( );
    binaryTimeseriesData1->SetId( Guid( L"{56BB9C30-67A4-E01F-07F8-E6256ADD390C}" ) );
    binaryTimeseriesData1->SetRowVersion( -2297003329408230352LL );
    binaryTimeseriesData1->SetCatalog( Guid( L"{56BB9C30-67A4-E01F-07F8-E6256ADD390C}" ) );
    binaryTimeseriesData1->SetName( L"Name" );
    binaryTimeseriesData1->SetMaxRetention( TimeSpan( -577408230352LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *binaryTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto binaryTimeseriesData2 = std::reinterpret_pointer_cast<BinaryTimeseriesData>( ReadDataFrom( source ) );
    bool equal = binaryTimeseriesData2->IsEqualTo( *binaryTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/BooleanTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( BooleanTimeseriesDataSerializationTest )
{
    auto booleanTimeseriesData1 = std::make_shared<BooleanTimeseriesData>( );
    booleanTimeseriesData1->SetId( Guid( L"{02D3DF65-9199-E4BC-273D-899940CBFBA6}" ) );
    booleanTimeseriesData1->SetRowVersion( -1964535251076915355LL );
    booleanTimeseriesData1->SetCatalog( Guid( L"{02D3DF65-9199-E4BC-273D-899940CBFBA6}" ) );
    booleanTimeseriesData1->SetName( L"Name" );
    booleanTimeseriesData1->SetMaxRetention( TimeSpan( -563076915355LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *booleanTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto booleanTimeseriesData2 = std::reinterpret_pointer_cast<BooleanTimeseriesData>( ReadDataFrom( source ) );
    bool equal = booleanTimeseriesData2->IsEqualTo( *booleanTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisAidToNavigationOffPositionTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( AisAidToNavigationOffPositionTimeseriesDataSerializationTest )
{
    auto aisAidToNavigationOffPositionTimeseriesData1 = std::make_shared<AisAidToNavigationOffPositionTimeseriesData>( );
    aisAidToNavigationOffPositionTimeseriesData1->SetId( Guid( L"{89D69A77-42AE-1C8E-3871-4275916B59EE}" ) );
    aisAidToNavigationOffPositionTimeseriesData1->SetRowVersion( 2057655397159180919LL );
    aisAidToNavigationOffPositionTimeseriesData1->SetCatalog( Guid( L"{89D69A77-42AE-1C8E-3871-4275916B59EE}" ) );
    aisAidToNavigationOffPositionTimeseriesData1->SetName( L"Name" );
    aisAidToNavigationOffPositionTimeseriesData1->SetMaxRetention( TimeSpan( 517159180919LL ) );
    aisAidToNavigationOffPositionTimeseriesData1->SetAidToNavigation( Guid( L"{89D69A77-42AE-1C8E-3871-4275916B59EE}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisAidToNavigationOffPositionTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisAidToNavigationOffPositionTimeseriesData2 = std::reinterpret_pointer_cast<AisAidToNavigationOffPositionTimeseriesData>( ReadDataFrom( source ) );
    bool equal = aisAidToNavigationOffPositionTimeseriesData2->IsEqualTo( *aisAidToNavigationOffPositionTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DeviceEnabledTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( DeviceEnabledTimeseriesDataSerializationTest )
{
    auto deviceEnabledTimeseriesData1 = std::make_shared<DeviceEnabledTimeseriesData>( );
    deviceEnabledTimeseriesData1->SetId( Guid( L"{69D0497B-894C-9769-E996-9132960B92DE}" ) );
    deviceEnabledTimeseriesData1->SetRowVersion( -7536341540142036613LL );
    deviceEnabledTimeseriesData1->SetCatalog( Guid( L"{69D0497B-894C-9769-E996-9132960B92DE}" ) );
    deviceEnabledTimeseriesData1->SetName( L"Name" );
    deviceEnabledTimeseriesData1->SetMaxRetention( TimeSpan( -452142036613LL ) );
    deviceEnabledTimeseriesData1->SetDevice( Guid( L"{69D0497B-894C-9769-E996-9132960B92DE}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *deviceEnabledTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto deviceEnabledTimeseriesData2 = std::reinterpret_pointer_cast<DeviceEnabledTimeseriesData>( ReadDataFrom( source ) );
    bool equal = deviceEnabledTimeseriesData2->IsEqualTo( *deviceEnabledTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarAutomaticSensitivityTimeControlTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarAutomaticSensitivityTimeControlTimeseriesDataSerializationTest )
{
    auto radarAutomaticSensitivityTimeControlTimeseriesData1 = std::make_shared<RadarAutomaticSensitivityTimeControlTimeseriesData>( );
    radarAutomaticSensitivityTimeControlTimeseriesData1->SetId( Guid( L"{B14B496D-C720-1CBB-38DD-E3048DD292B6}" ) );
    radarAutomaticSensitivityTimeControlTimeseriesData1->SetRowVersion( 2070467396934257005LL );
    radarAutomaticSensitivityTimeControlTimeseriesData1->SetCatalog( Guid( L"{B14B496D-C720-1CBB-38DD-E3048DD292B6}" ) );
    radarAutomaticSensitivityTimeControlTimeseriesData1->SetName( L"Name" );
    radarAutomaticSensitivityTimeControlTimeseriesData1->SetMaxRetention( TimeSpan( 260934257005LL ) );
    radarAutomaticSensitivityTimeControlTimeseriesData1->SetRadar( Guid( L"{B14B496D-C720-1CBB-38DD-E3048DD292B6}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarAutomaticSensitivityTimeControlTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarAutomaticSensitivityTimeControlTimeseriesData2 = std::reinterpret_pointer_cast<RadarAutomaticSensitivityTimeControlTimeseriesData>( ReadDataFrom( source ) );
    bool equal = radarAutomaticSensitivityTimeControlTimeseriesData2->IsEqualTo( *radarAutomaticSensitivityTimeControlTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarBlankSector1TimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarBlankSector1TimeseriesDataSerializationTest )
{
    auto radarBlankSector1TimeseriesData1 = std::make_shared<RadarBlankSector1TimeseriesData>( );
    radarBlankSector1TimeseriesData1->SetId( Guid( L"{ED364257-A48A-54B4-2A2D-2551B76C42EA}" ) );
    radarBlankSector1TimeseriesData1->SetRowVersion( 6103684311586062935LL );
    radarBlankSector1TimeseriesData1->SetCatalog( Guid( L"{ED364257-A48A-54B4-2A2D-2551B76C42EA}" ) );
    radarBlankSector1TimeseriesData1->SetName( L"Name" );
    radarBlankSector1TimeseriesData1->SetMaxRetention( TimeSpan( 375586062935LL ) );
    radarBlankSector1TimeseriesData1->SetRadar( Guid( L"{ED364257-A48A-54B4-2A2D-2551B76C42EA}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarBlankSector1TimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarBlankSector1TimeseriesData2 = std::reinterpret_pointer_cast<RadarBlankSector1TimeseriesData>( ReadDataFrom( source ) );
    bool equal = radarBlankSector1TimeseriesData2->IsEqualTo( *radarBlankSector1TimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarBlankSector2TimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarBlankSector2TimeseriesDataSerializationTest )
{
    auto radarBlankSector2TimeseriesData1 = std::make_shared<RadarBlankSector2TimeseriesData>( );
    radarBlankSector2TimeseriesData1->SetId( Guid( L"{46A44C6B-B248-E63D-67BC-4D12622532D6}" ) );
    radarBlankSector2TimeseriesData1->SetRowVersion( -1856131447914214293LL );
    radarBlankSector2TimeseriesData1->SetCatalog( Guid( L"{46A44C6B-B248-E63D-67BC-4D12622532D6}" ) );
    radarBlankSector2TimeseriesData1->SetName( L"Name" );
    radarBlankSector2TimeseriesData1->SetMaxRetention( TimeSpan( -247914214293LL ) );
    radarBlankSector2TimeseriesData1->SetRadar( Guid( L"{46A44C6B-B248-E63D-67BC-4D12622532D6}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarBlankSector2TimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarBlankSector2TimeseriesData2 = std::reinterpret_pointer_cast<RadarBlankSector2TimeseriesData>( ReadDataFrom( source ) );
    bool equal = radarBlankSector2TimeseriesData2->IsEqualTo( *radarBlankSector2TimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarEnableAutomaticFrequencyControlTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarEnableAutomaticFrequencyControlTimeseriesDataSerializationTest )
{
    auto radarEnableAutomaticFrequencyControlTimeseriesData1 = std::make_shared<RadarEnableAutomaticFrequencyControlTimeseriesData>( );
    radarEnableAutomaticFrequencyControlTimeseriesData1->SetId( Guid( L"{9DB6213A-0CCE-84B7-21ED-3073B96D845C}" ) );
    radarEnableAutomaticFrequencyControlTimeseriesData1->SetRowVersion( -8883617658416258758LL );
    radarEnableAutomaticFrequencyControlTimeseriesData1->SetCatalog( Guid( L"{9DB6213A-0CCE-84B7-21ED-3073B96D845C}" ) );
    radarEnableAutomaticFrequencyControlTimeseriesData1->SetName( L"Name" );
    radarEnableAutomaticFrequencyControlTimeseriesData1->SetMaxRetention( TimeSpan( -762416258758LL ) );
    radarEnableAutomaticFrequencyControlTimeseriesData1->SetRadar( Guid( L"{9DB6213A-0CCE-84B7-21ED-3073B96D845C}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarEnableAutomaticFrequencyControlTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarEnableAutomaticFrequencyControlTimeseriesData2 = std::reinterpret_pointer_cast<RadarEnableAutomaticFrequencyControlTimeseriesData>( ReadDataFrom( source ) );
    bool equal = radarEnableAutomaticFrequencyControlTimeseriesData2->IsEqualTo( *radarEnableAutomaticFrequencyControlTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarEnableFastTimeConstantTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarEnableFastTimeConstantTimeseriesDataSerializationTest )
{
    auto radarEnableFastTimeConstantTimeseriesData1 = std::make_shared<RadarEnableFastTimeConstantTimeseriesData>( );
    radarEnableFastTimeConstantTimeseriesData1->SetId( Guid( L"{18A7A806-EC65-5F1B-FAD8-37A618E51560}" ) );
    radarEnableFastTimeConstantTimeseriesData1->SetRowVersion( 6853331176923834374LL );
    radarEnableFastTimeConstantTimeseriesData1->SetCatalog( Guid( L"{18A7A806-EC65-5F1B-FAD8-37A618E51560}" ) );
    radarEnableFastTimeConstantTimeseriesData1->SetName( L"Name" );
    radarEnableFastTimeConstantTimeseriesData1->SetMaxRetention( TimeSpan( 232923834374LL ) );
    radarEnableFastTimeConstantTimeseriesData1->SetRadar( Guid( L"{18A7A806-EC65-5F1B-FAD8-37A618E51560}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarEnableFastTimeConstantTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarEnableFastTimeConstantTimeseriesData2 = std::reinterpret_pointer_cast<RadarEnableFastTimeConstantTimeseriesData>( ReadDataFrom( source ) );
    bool equal = radarEnableFastTimeConstantTimeseriesData2->IsEqualTo( *radarEnableFastTimeConstantTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarEnableSensitivityTimeControlTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarEnableSensitivityTimeControlTimeseriesDataSerializationTest )
{
    auto radarEnableSensitivityTimeControlTimeseriesData1 = std::make_shared<RadarEnableSensitivityTimeControlTimeseriesData>( );
    radarEnableSensitivityTimeControlTimeseriesData1->SetId( Guid( L"{494844CA-D6F1-C20E-4370-6B8F92122253}" ) );
    radarEnableSensitivityTimeControlTimeseriesData1->SetRowVersion( -4463393848872647478LL );
    radarEnableSensitivityTimeControlTimeseriesData1->SetCatalog( Guid( L"{494844CA-D6F1-C20E-4370-6B8F92122253}" ) );
    radarEnableSensitivityTimeControlTimeseriesData1->SetName( L"Name" );
    radarEnableSensitivityTimeControlTimeseriesData1->SetMaxRetention( TimeSpan( -88872647478LL ) );
    radarEnableSensitivityTimeControlTimeseriesData1->SetRadar( Guid( L"{494844CA-D6F1-C20E-4370-6B8F92122253}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarEnableSensitivityTimeControlTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarEnableSensitivityTimeControlTimeseriesData2 = std::reinterpret_pointer_cast<RadarEnableSensitivityTimeControlTimeseriesData>( ReadDataFrom( source ) );
    bool equal = radarEnableSensitivityTimeControlTimeseriesData2->IsEqualTo( *radarEnableSensitivityTimeControlTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarPowerOnTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarPowerOnTimeseriesDataSerializationTest )
{
    auto radarPowerOnTimeseriesData1 = std::make_shared<RadarPowerOnTimeseriesData>( );
    radarPowerOnTimeseriesData1->SetId( Guid( L"{4BD37D9F-BB15-752C-AE34-DDA8D2CBBEF9}" ) );
    radarPowerOnTimeseriesData1->SetRowVersion( 8443329101553696159LL );
    radarPowerOnTimeseriesData1->SetCatalog( Guid( L"{4BD37D9F-BB15-752C-AE34-DDA8D2CBBEF9}" ) );
    radarPowerOnTimeseriesData1->SetName( L"Name" );
    radarPowerOnTimeseriesData1->SetMaxRetention( TimeSpan( 557553696159LL ) );
    radarPowerOnTimeseriesData1->SetRadar( Guid( L"{4BD37D9F-BB15-752C-AE34-DDA8D2CBBEF9}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarPowerOnTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarPowerOnTimeseriesData2 = std::reinterpret_pointer_cast<RadarPowerOnTimeseriesData>( ReadDataFrom( source ) );
    bool equal = radarPowerOnTimeseriesData2->IsEqualTo( *radarPowerOnTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarSaveSettingsTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarSaveSettingsTimeseriesDataSerializationTest )
{
    auto radarSaveSettingsTimeseriesData1 = std::make_shared<RadarSaveSettingsTimeseriesData>( );
    radarSaveSettingsTimeseriesData1->SetId( Guid( L"{CA0F64CF-2127-5D4E-BA72-84E453F026F3}" ) );
    radarSaveSettingsTimeseriesData1->SetRowVersion( 6723347748488176847LL );
    radarSaveSettingsTimeseriesData1->SetCatalog( Guid( L"{CA0F64CF-2127-5D4E-BA72-84E453F026F3}" ) );
    radarSaveSettingsTimeseriesData1->SetName( L"Name" );
    radarSaveSettingsTimeseriesData1->SetMaxRetention( TimeSpan( 420488176847LL ) );
    radarSaveSettingsTimeseriesData1->SetRadar( Guid( L"{CA0F64CF-2127-5D4E-BA72-84E453F026F3}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarSaveSettingsTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarSaveSettingsTimeseriesData2 = std::reinterpret_pointer_cast<RadarSaveSettingsTimeseriesData>( ReadDataFrom( source ) );
    bool equal = radarSaveSettingsTimeseriesData2->IsEqualTo( *radarSaveSettingsTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarTrackingTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarTrackingTimeseriesDataSerializationTest )
{
    auto radarTrackingTimeseriesData1 = std::make_shared<RadarTrackingTimeseriesData>( );
    radarTrackingTimeseriesData1->SetId( Guid( L"{693D3626-5AC5-291C-9438-5AA396BC6C64}" ) );
    radarTrackingTimeseriesData1->SetRowVersion( 2962342458823620134LL );
    radarTrackingTimeseriesData1->SetCatalog( Guid( L"{693D3626-5AC5-291C-9438-5AA396BC6C64}" ) );
    radarTrackingTimeseriesData1->SetName( L"Name" );
    radarTrackingTimeseriesData1->SetMaxRetention( TimeSpan( 90823620134LL ) );
    radarTrackingTimeseriesData1->SetRadar( Guid( L"{693D3626-5AC5-291C-9438-5AA396BC6C64}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarTrackingTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarTrackingTimeseriesData2 = std::reinterpret_pointer_cast<RadarTrackingTimeseriesData>( ReadDataFrom( source ) );
    bool equal = radarTrackingTimeseriesData2->IsEqualTo( *radarTrackingTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/MediaProxySessionEnabledTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( MediaProxySessionEnabledTimeseriesDataSerializationTest )
{
    auto mediaProxySessionEnabledTimeseriesData1 = std::make_shared<MediaProxySessionEnabledTimeseriesData>( );
    mediaProxySessionEnabledTimeseriesData1->SetId( Guid( L"{E0C3C0AA-BEA0-3AA5-5CA5-7D0507C30355}" ) );
    mediaProxySessionEnabledTimeseriesData1->SetRowVersion( 4225993423532048554LL );
    mediaProxySessionEnabledTimeseriesData1->SetCatalog( Guid( L"{E0C3C0AA-BEA0-3AA5-5CA5-7D0507C30355}" ) );
    mediaProxySessionEnabledTimeseriesData1->SetName( L"Name" );
    mediaProxySessionEnabledTimeseriesData1->SetMaxRetention( TimeSpan( 79532048554LL ) );
    mediaProxySessionEnabledTimeseriesData1->SetProxySession( Guid( L"{E0C3C0AA-BEA0-3AA5-5CA5-7D0507C30355}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *mediaProxySessionEnabledTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto mediaProxySessionEnabledTimeseriesData2 = std::reinterpret_pointer_cast<MediaProxySessionEnabledTimeseriesData>( ReadDataFrom( source ) );
    bool equal = mediaProxySessionEnabledTimeseriesData2->IsEqualTo( *mediaProxySessionEnabledTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/MediaServiceEnabledTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( MediaServiceEnabledTimeseriesDataSerializationTest )
{
    auto mediaServiceEnabledTimeseriesData1 = std::make_shared<MediaServiceEnabledTimeseriesData>( );
    mediaServiceEnabledTimeseriesData1->SetId( Guid( L"{F813AAEC-3673-460A-6250-6CCE1FC85537}" ) );
    mediaServiceEnabledTimeseriesData1->SetRowVersion( 5046906204133239532LL );
    mediaServiceEnabledTimeseriesData1->SetCatalog( Guid( L"{F813AAEC-3673-460A-6250-6CCE1FC85537}" ) );
    mediaServiceEnabledTimeseriesData1->SetName( L"Name" );
    mediaServiceEnabledTimeseriesData1->SetMaxRetention( TimeSpan( 540133239532LL ) );
    mediaServiceEnabledTimeseriesData1->SetService( Guid( L"{F813AAEC-3673-460A-6250-6CCE1FC85537}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *mediaServiceEnabledTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto mediaServiceEnabledTimeseriesData2 = std::reinterpret_pointer_cast<MediaServiceEnabledTimeseriesData>( ReadDataFrom( source ) );
    bool equal = mediaServiceEnabledTimeseriesData2->IsEqualTo( *mediaServiceEnabledTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ByteTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( ByteTimeseriesDataSerializationTest )
{
    auto byteTimeseriesData1 = std::make_shared<ByteTimeseriesData>( );
    byteTimeseriesData1->SetId( Guid( L"{B4BE0CF7-5AEF-38B0-1C0D-5AF72D7D30EF}" ) );
    byteTimeseriesData1->SetRowVersion( 4084864847601077495LL );
    byteTimeseriesData1->SetCatalog( Guid( L"{B4BE0CF7-5AEF-38B0-1C0D-5AF72D7D30EF}" ) );
    byteTimeseriesData1->SetName( L"Name" );
    byteTimeseriesData1->SetMaxRetention( TimeSpan( 719601077495LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *byteTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto byteTimeseriesData2 = std::reinterpret_pointer_cast<ByteTimeseriesData>( ReadDataFrom( source ) );
    bool equal = byteTimeseriesData2->IsEqualTo( *byteTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DateTimeTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( DateTimeTimeseriesDataSerializationTest )
{
    auto dateTimeTimeseriesData1 = std::make_shared<DateTimeTimeseriesData>( );
    dateTimeTimeseriesData1->SetId( Guid( L"{B7AFFEEC-9857-8EE3-71C7-19EAEDF57F37}" ) );
    dateTimeTimeseriesData1->SetRowVersion( -8150503398099124500LL );
    dateTimeTimeseriesData1->SetCatalog( Guid( L"{B7AFFEEC-9857-8EE3-71C7-19EAEDF57F37}" ) );
    dateTimeTimeseriesData1->SetName( L"Name" );
    dateTimeTimeseriesData1->SetMaxRetention( TimeSpan( -6099124500LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *dateTimeTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto dateTimeTimeseriesData2 = std::reinterpret_pointer_cast<DateTimeTimeseriesData>( ReadDataFrom( source ) );
    bool equal = dateTimeTimeseriesData2->IsEqualTo( *dateTimeTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/DoubleTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( DoubleTimeseriesDataSerializationTest )
{
    auto doubleTimeseriesData1 = std::make_shared<DoubleTimeseriesData>( );
    doubleTimeseriesData1->SetId( Guid( L"{70027D82-38B0-3204-4C20-1C0D0E40BE41}" ) );
    doubleTimeseriesData1->SetRowVersion( 3604067932247850370LL );
    doubleTimeseriesData1->SetCatalog( Guid( L"{70027D82-38B0-3204-4C20-1C0D0E40BE41}" ) );
    doubleTimeseriesData1->SetName( L"Name" );
    doubleTimeseriesData1->SetMaxRetention( TimeSpan( 796247850370LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *doubleTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto doubleTimeseriesData2 = std::reinterpret_pointer_cast<DoubleTimeseriesData>( ReadDataFrom( source ) );
    bool equal = doubleTimeseriesData2->IsEqualTo( *doubleTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GNSSAltitudeTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( GNSSAltitudeTimeseriesDataSerializationTest )
{
    auto gNSSAltitudeTimeseriesData1 = std::make_shared<GNSSAltitudeTimeseriesData>( );
    gNSSAltitudeTimeseriesData1->SetId( Guid( L"{C78FE640-FB48-915B-89DA-DF12E3F16702}" ) );
    gNSSAltitudeTimeseriesData1->SetRowVersion( -7972502425325017536LL );
    gNSSAltitudeTimeseriesData1->SetCatalog( Guid( L"{C78FE640-FB48-915B-89DA-DF12E3F16702}" ) );
    gNSSAltitudeTimeseriesData1->SetName( L"Name" );
    gNSSAltitudeTimeseriesData1->SetMaxRetention( TimeSpan( -313325017536LL ) );
    gNSSAltitudeTimeseriesData1->SetGNSSDevice( Guid( L"{C78FE640-FB48-915B-89DA-DF12E3F16702}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gNSSAltitudeTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gNSSAltitudeTimeseriesData2 = std::reinterpret_pointer_cast<GNSSAltitudeTimeseriesData>( ReadDataFrom( source ) );
    bool equal = gNSSAltitudeTimeseriesData2->IsEqualTo( *gNSSAltitudeTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GNSSLatitudeTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( GNSSLatitudeTimeseriesDataSerializationTest )
{
    auto gNSSLatitudeTimeseriesData1 = std::make_shared<GNSSLatitudeTimeseriesData>( );
    gNSSLatitudeTimeseriesData1->SetId( Guid( L"{2B60BC5C-431D-E742-E742-C2B8D4063D3A}" ) );
    gNSSLatitudeTimeseriesData1->SetRowVersion( -1782788709924422564LL );
    gNSSLatitudeTimeseriesData1->SetCatalog( Guid( L"{2B60BC5C-431D-E742-E742-C2B8D4063D3A}" ) );
    gNSSLatitudeTimeseriesData1->SetName( L"Name" );
    gNSSLatitudeTimeseriesData1->SetMaxRetention( TimeSpan( -741924422564LL ) );
    gNSSLatitudeTimeseriesData1->SetGNSSDevice( Guid( L"{2B60BC5C-431D-E742-E742-C2B8D4063D3A}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gNSSLatitudeTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gNSSLatitudeTimeseriesData2 = std::reinterpret_pointer_cast<GNSSLatitudeTimeseriesData>( ReadDataFrom( source ) );
    bool equal = gNSSLatitudeTimeseriesData2->IsEqualTo( *gNSSLatitudeTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GNSSLongitudeTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( GNSSLongitudeTimeseriesDataSerializationTest )
{
    auto gNSSLongitudeTimeseriesData1 = std::make_shared<GNSSLongitudeTimeseriesData>( );
    gNSSLongitudeTimeseriesData1->SetId( Guid( L"{A7B79429-D0D4-80DD-01BB-0B2BE5ED2994}" ) );
    gNSSLongitudeTimeseriesData1->SetRowVersion( -9160936455236250583LL );
    gNSSLongitudeTimeseriesData1->SetCatalog( Guid( L"{A7B79429-D0D4-80DD-01BB-0B2BE5ED2994}" ) );
    gNSSLongitudeTimeseriesData1->SetName( L"Name" );
    gNSSLongitudeTimeseriesData1->SetMaxRetention( TimeSpan( -615236250583LL ) );
    gNSSLongitudeTimeseriesData1->SetGNSSDevice( Guid( L"{A7B79429-D0D4-80DD-01BB-0B2BE5ED2994}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gNSSLongitudeTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gNSSLongitudeTimeseriesData2 = std::reinterpret_pointer_cast<GNSSLongitudeTimeseriesData>( ReadDataFrom( source ) );
    bool equal = gNSSLongitudeTimeseriesData2->IsEqualTo( *gNSSLongitudeTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GyroCourseTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( GyroCourseTimeseriesDataSerializationTest )
{
    auto gyroCourseTimeseriesData1 = std::make_shared<GyroCourseTimeseriesData>( );
    gyroCourseTimeseriesData1->SetId( Guid( L"{99A051A1-D6FF-D1D3-8BCB-6BFF99058A85}" ) );
    gyroCourseTimeseriesData1->SetRowVersion( -3327079306414239327LL );
    gyroCourseTimeseriesData1->SetCatalog( Guid( L"{99A051A1-D6FF-D1D3-8BCB-6BFF99058A85}" ) );
    gyroCourseTimeseriesData1->SetName( L"Name" );
    gyroCourseTimeseriesData1->SetMaxRetention( TimeSpan( -202414239327LL ) );
    gyroCourseTimeseriesData1->SetGyroDevice( Guid( L"{99A051A1-D6FF-D1D3-8BCB-6BFF99058A85}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gyroCourseTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gyroCourseTimeseriesData2 = std::reinterpret_pointer_cast<GyroCourseTimeseriesData>( ReadDataFrom( source ) );
    bool equal = gyroCourseTimeseriesData2->IsEqualTo( *gyroCourseTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GyroHeadingMagneticNorthTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( GyroHeadingMagneticNorthTimeseriesDataSerializationTest )
{
    auto gyroHeadingMagneticNorthTimeseriesData1 = std::make_shared<GyroHeadingMagneticNorthTimeseriesData>( );
    gyroHeadingMagneticNorthTimeseriesData1->SetId( Guid( L"{0BCA07EA-06B3-C122-8344-60CDD053E057}" ) );
    gyroHeadingMagneticNorthTimeseriesData1->SetRowVersion( -4530050909114595350LL );
    gyroHeadingMagneticNorthTimeseriesData1->SetCatalog( Guid( L"{0BCA07EA-06B3-C122-8344-60CDD053E057}" ) );
    gyroHeadingMagneticNorthTimeseriesData1->SetName( L"Name" );
    gyroHeadingMagneticNorthTimeseriesData1->SetMaxRetention( TimeSpan( -413114595350LL ) );
    gyroHeadingMagneticNorthTimeseriesData1->SetGyroDevice( Guid( L"{0BCA07EA-06B3-C122-8344-60CDD053E057}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gyroHeadingMagneticNorthTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gyroHeadingMagneticNorthTimeseriesData2 = std::reinterpret_pointer_cast<GyroHeadingMagneticNorthTimeseriesData>( ReadDataFrom( source ) );
    bool equal = gyroHeadingMagneticNorthTimeseriesData2->IsEqualTo( *gyroHeadingMagneticNorthTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GyroHeadingTrueNorthTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( GyroHeadingTrueNorthTimeseriesDataSerializationTest )
{
    auto gyroHeadingTrueNorthTimeseriesData1 = std::make_shared<GyroHeadingTrueNorthTimeseriesData>( );
    gyroHeadingTrueNorthTimeseriesData1->SetId( Guid( L"{C6DE373C-1957-8742-E142-98EA637BEC3C}" ) );
    gyroHeadingTrueNorthTimeseriesData1->SetRowVersion( -8700363665337075908LL );
    gyroHeadingTrueNorthTimeseriesData1->SetCatalog( Guid( L"{C6DE373C-1957-8742-E142-98EA637BEC3C}" ) );
    gyroHeadingTrueNorthTimeseriesData1->SetName( L"Name" );
    gyroHeadingTrueNorthTimeseriesData1->SetMaxRetention( TimeSpan( -305337075908LL ) );
    gyroHeadingTrueNorthTimeseriesData1->SetGyroDevice( Guid( L"{C6DE373C-1957-8742-E142-98EA637BEC3C}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gyroHeadingTrueNorthTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gyroHeadingTrueNorthTimeseriesData2 = std::reinterpret_pointer_cast<GyroHeadingTrueNorthTimeseriesData>( ReadDataFrom( source ) );
    bool equal = gyroHeadingTrueNorthTimeseriesData2->IsEqualTo( *gyroHeadingTrueNorthTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GyroPitchTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( GyroPitchTimeseriesDataSerializationTest )
{
    auto gyroPitchTimeseriesData1 = std::make_shared<GyroPitchTimeseriesData>( );
    gyroPitchTimeseriesData1->SetId( Guid( L"{D29F7EFA-EF76-E390-C709-F76E4BF97E5F}" ) );
    gyroPitchTimeseriesData1->SetRowVersion( -2048874536834728198LL );
    gyroPitchTimeseriesData1->SetCatalog( Guid( L"{D29F7EFA-EF76-E390-C709-F76E4BF97E5F}" ) );
    gyroPitchTimeseriesData1->SetName( L"Name" );
    gyroPitchTimeseriesData1->SetMaxRetention( TimeSpan( -488834728198LL ) );
    gyroPitchTimeseriesData1->SetGyroDevice( Guid( L"{D29F7EFA-EF76-E390-C709-F76E4BF97E5F}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gyroPitchTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gyroPitchTimeseriesData2 = std::reinterpret_pointer_cast<GyroPitchTimeseriesData>( ReadDataFrom( source ) );
    bool equal = gyroPitchTimeseriesData2->IsEqualTo( *gyroPitchTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GyroRateOfTurnTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( GyroRateOfTurnTimeseriesDataSerializationTest )
{
    auto gyroRateOfTurnTimeseriesData1 = std::make_shared<GyroRateOfTurnTimeseriesData>( );
    gyroRateOfTurnTimeseriesData1->SetId( Guid( L"{9F54111F-5947-76E2-6E47-9AE2F92A88F8}" ) );
    gyroRateOfTurnTimeseriesData1->SetRowVersion( 8566507605362741535LL );
    gyroRateOfTurnTimeseriesData1->SetCatalog( Guid( L"{9F54111F-5947-76E2-6E47-9AE2F92A88F8}" ) );
    gyroRateOfTurnTimeseriesData1->SetName( L"Name" );
    gyroRateOfTurnTimeseriesData1->SetMaxRetention( TimeSpan( 309362741535LL ) );
    gyroRateOfTurnTimeseriesData1->SetGyroDevice( Guid( L"{9F54111F-5947-76E2-6E47-9AE2F92A88F8}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gyroRateOfTurnTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gyroRateOfTurnTimeseriesData2 = std::reinterpret_pointer_cast<GyroRateOfTurnTimeseriesData>( ReadDataFrom( source ) );
    bool equal = gyroRateOfTurnTimeseriesData2->IsEqualTo( *gyroRateOfTurnTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GyroRollTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( GyroRollTimeseriesDataSerializationTest )
{
    auto gyroRollTimeseriesData1 = std::make_shared<GyroRollTimeseriesData>( );
    gyroRollTimeseriesData1->SetId( Guid( L"{B0312AEF-C209-72B9-4E9D-43900D8C54F7}" ) );
    gyroRollTimeseriesData1->SetRowVersion( 8266851937881762543LL );
    gyroRollTimeseriesData1->SetCatalog( Guid( L"{B0312AEF-C209-72B9-4E9D-43900D8C54F7}" ) );
    gyroRollTimeseriesData1->SetName( L"Name" );
    gyroRollTimeseriesData1->SetMaxRetention( TimeSpan( 577881762543LL ) );
    gyroRollTimeseriesData1->SetGyroDevice( Guid( L"{B0312AEF-C209-72B9-4E9D-43900D8C54F7}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gyroRollTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gyroRollTimeseriesData2 = std::reinterpret_pointer_cast<GyroRollTimeseriesData>( ReadDataFrom( source ) );
    bool equal = gyroRollTimeseriesData2->IsEqualTo( *gyroRollTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GyroSpeedTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( GyroSpeedTimeseriesDataSerializationTest )
{
    auto gyroSpeedTimeseriesData1 = std::make_shared<GyroSpeedTimeseriesData>( );
    gyroSpeedTimeseriesData1->SetId( Guid( L"{5F8EC90F-03A1-EC2C-3734-C085FA7193F0}" ) );
    gyroSpeedTimeseriesData1->SetRowVersion( -1428762990155478769LL );
    gyroSpeedTimeseriesData1->SetCatalog( Guid( L"{5F8EC90F-03A1-EC2C-3734-C085FA7193F0}" ) );
    gyroSpeedTimeseriesData1->SetName( L"Name" );
    gyroSpeedTimeseriesData1->SetMaxRetention( TimeSpan( -750155478769LL ) );
    gyroSpeedTimeseriesData1->SetGyroDevice( Guid( L"{5F8EC90F-03A1-EC2C-3734-C085FA7193F0}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *gyroSpeedTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto gyroSpeedTimeseriesData2 = std::reinterpret_pointer_cast<GyroSpeedTimeseriesData>( ReadDataFrom( source ) );
    bool equal = gyroSpeedTimeseriesData2->IsEqualTo( *gyroSpeedTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarLatitudeTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarLatitudeTimeseriesDataSerializationTest )
{
    auto radarLatitudeTimeseriesData1 = std::make_shared<RadarLatitudeTimeseriesData>( );
    radarLatitudeTimeseriesData1->SetId( Guid( L"{E0E5A360-ADB7-DDEA-BB57-B5ED07A7C506}" ) );
    radarLatitudeTimeseriesData1->SetRowVersion( -2455959641513417888LL );
    radarLatitudeTimeseriesData1->SetCatalog( Guid( L"{E0E5A360-ADB7-DDEA-BB57-B5ED07A7C506}" ) );
    radarLatitudeTimeseriesData1->SetName( L"Name" );
    radarLatitudeTimeseriesData1->SetMaxRetention( TimeSpan( -761513417888LL ) );
    radarLatitudeTimeseriesData1->SetRadar( Guid( L"{E0E5A360-ADB7-DDEA-BB57-B5ED07A7C506}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarLatitudeTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarLatitudeTimeseriesData2 = std::reinterpret_pointer_cast<RadarLatitudeTimeseriesData>( ReadDataFrom( source ) );
    bool equal = radarLatitudeTimeseriesData2->IsEqualTo( *radarLatitudeTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarLongitudeTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarLongitudeTimeseriesDataSerializationTest )
{
    auto radarLongitudeTimeseriesData1 = std::make_shared<RadarLongitudeTimeseriesData>( );
    radarLongitudeTimeseriesData1->SetId( Guid( L"{914F8147-10D7-7E00-7E00-08EB89F281E2}" ) );
    radarLongitudeTimeseriesData1->SetRowVersion( 9079275366820839751LL );
    radarLongitudeTimeseriesData1->SetCatalog( Guid( L"{914F8147-10D7-7E00-7E00-08EB89F281E2}" ) );
    radarLongitudeTimeseriesData1->SetName( L"Name" );
    radarLongitudeTimeseriesData1->SetMaxRetention( TimeSpan( 486820839751LL ) );
    radarLongitudeTimeseriesData1->SetRadar( Guid( L"{914F8147-10D7-7E00-7E00-08EB89F281E2}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarLongitudeTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarLongitudeTimeseriesData2 = std::reinterpret_pointer_cast<RadarLongitudeTimeseriesData>( ReadDataFrom( source ) );
    bool equal = radarLongitudeTimeseriesData2->IsEqualTo( *radarLongitudeTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadomeDewPointTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( RadomeDewPointTimeseriesDataSerializationTest )
{
    auto radomeDewPointTimeseriesData1 = std::make_shared<RadomeDewPointTimeseriesData>( );
    radomeDewPointTimeseriesData1->SetId( Guid( L"{85244187-C511-65D6-A66B-A388A12482E1}" ) );
    radomeDewPointTimeseriesData1->SetRowVersion( 7338269321885663623LL );
    radomeDewPointTimeseriesData1->SetCatalog( Guid( L"{85244187-C511-65D6-A66B-A388A12482E1}" ) );
    radomeDewPointTimeseriesData1->SetName( L"Name" );
    radomeDewPointTimeseriesData1->SetMaxRetention( TimeSpan( 233885663623LL ) );
    radomeDewPointTimeseriesData1->SetRadome( Guid( L"{85244187-C511-65D6-A66B-A388A12482E1}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radomeDewPointTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radomeDewPointTimeseriesData2 = std::reinterpret_pointer_cast<RadomeDewPointTimeseriesData>( ReadDataFrom( source ) );
    bool equal = radomeDewPointTimeseriesData2->IsEqualTo( *radomeDewPointTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadomePressureTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( RadomePressureTimeseriesDataSerializationTest )
{
    auto radomePressureTimeseriesData1 = std::make_shared<RadomePressureTimeseriesData>( );
    radomePressureTimeseriesData1->SetId( Guid( L"{58626DEF-4551-0274-402E-A28A1A46B6F7}" ) );
    radomePressureTimeseriesData1->SetRowVersion( 176842501051805167LL );
    radomePressureTimeseriesData1->SetCatalog( Guid( L"{58626DEF-4551-0274-402E-A28A1A46B6F7}" ) );
    radomePressureTimeseriesData1->SetName( L"Name" );
    radomePressureTimeseriesData1->SetMaxRetention( TimeSpan( 709051805167LL ) );
    radomePressureTimeseriesData1->SetRadome( Guid( L"{58626DEF-4551-0274-402E-A28A1A46B6F7}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radomePressureTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radomePressureTimeseriesData2 = std::reinterpret_pointer_cast<RadomePressureTimeseriesData>( ReadDataFrom( source ) );
    bool equal = radomePressureTimeseriesData2->IsEqualTo( *radomePressureTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadomeTemperatureTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( RadomeTemperatureTimeseriesDataSerializationTest )
{
    auto radomeTemperatureTimeseriesData1 = std::make_shared<RadomeTemperatureTimeseriesData>( );
    radomeTemperatureTimeseriesData1->SetId( Guid( L"{A5335D1F-62CF-F3BA-CF5D-46F3A5CCBAF8}" ) );
    radomeTemperatureTimeseriesData1->SetRowVersion( -884285732855522017LL );
    radomeTemperatureTimeseriesData1->SetCatalog( Guid( L"{A5335D1F-62CF-F3BA-CF5D-46F3A5CCBAF8}" ) );
    radomeTemperatureTimeseriesData1->SetName( L"Name" );
    radomeTemperatureTimeseriesData1->SetMaxRetention( TimeSpan( -740855522017LL ) );
    radomeTemperatureTimeseriesData1->SetRadome( Guid( L"{A5335D1F-62CF-F3BA-CF5D-46F3A5CCBAF8}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radomeTemperatureTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radomeTemperatureTimeseriesData2 = std::reinterpret_pointer_cast<RadomeTemperatureTimeseriesData>( ReadDataFrom( source ) );
    bool equal = radomeTemperatureTimeseriesData2->IsEqualTo( *radomeTemperatureTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/VesselDraughtTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( VesselDraughtTimeseriesDataSerializationTest )
{
    auto vesselDraughtTimeseriesData1 = std::make_shared<VesselDraughtTimeseriesData>( );
    vesselDraughtTimeseriesData1->SetId( Guid( L"{7059B959-548D-760C-6E30-2AB10E9A9D9A}" ) );
    vesselDraughtTimeseriesData1->SetRowVersion( 8506266762648074585LL );
    vesselDraughtTimeseriesData1->SetCatalog( Guid( L"{7059B959-548D-760C-6E30-2AB10E9A9D9A}" ) );
    vesselDraughtTimeseriesData1->SetName( L"Name" );
    vesselDraughtTimeseriesData1->SetMaxRetention( TimeSpan( 138648074585LL ) );
    vesselDraughtTimeseriesData1->SetVessel( Guid( L"{7059B959-548D-760C-6E30-2AB10E9A9D9A}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *vesselDraughtTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto vesselDraughtTimeseriesData2 = std::reinterpret_pointer_cast<VesselDraughtTimeseriesData>( ReadDataFrom( source ) );
    bool equal = vesselDraughtTimeseriesData2->IsEqualTo( *vesselDraughtTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ViewLatitudeTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( ViewLatitudeTimeseriesDataSerializationTest )
{
    auto viewLatitudeTimeseriesData1 = std::make_shared<ViewLatitudeTimeseriesData>( );
    viewLatitudeTimeseriesData1->SetId( Guid( L"{9B05B46B-C262-634F-C6F2-4346D9A02DD6}" ) );
    viewLatitudeTimeseriesData1->SetRowVersion( 7156152061678433387LL );
    viewLatitudeTimeseriesData1->SetCatalog( Guid( L"{9B05B46B-C262-634F-C6F2-4346D9A02DD6}" ) );
    viewLatitudeTimeseriesData1->SetName( L"Name" );
    viewLatitudeTimeseriesData1->SetMaxRetention( TimeSpan( 349678433387LL ) );
    viewLatitudeTimeseriesData1->SetView( Guid( L"{9B05B46B-C262-634F-C6F2-4346D9A02DD6}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *viewLatitudeTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto viewLatitudeTimeseriesData2 = std::reinterpret_pointer_cast<ViewLatitudeTimeseriesData>( ReadDataFrom( source ) );
    bool equal = viewLatitudeTimeseriesData2->IsEqualTo( *viewLatitudeTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ViewLongitudeTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( ViewLongitudeTimeseriesDataSerializationTest )
{
    auto viewLongitudeTimeseriesData1 = std::make_shared<ViewLongitudeTimeseriesData>( );
    viewLongitudeTimeseriesData1->SetId( Guid( L"{4FBBABE3-886C-8E91-7189-1136F2DDD5C7}" ) );
    viewLongitudeTimeseriesData1->SetRowVersion( -8173601849925194781LL );
    viewLongitudeTimeseriesData1->SetCatalog( Guid( L"{4FBBABE3-886C-8E91-7189-1136F2DDD5C7}" ) );
    viewLongitudeTimeseriesData1->SetName( L"Name" );
    viewLongitudeTimeseriesData1->SetMaxRetention( TimeSpan( -281925194781LL ) );
    viewLongitudeTimeseriesData1->SetView( Guid( L"{4FBBABE3-886C-8E91-7189-1136F2DDD5C7}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *viewLongitudeTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto viewLongitudeTimeseriesData2 = std::reinterpret_pointer_cast<ViewLongitudeTimeseriesData>( ReadDataFrom( source ) );
    bool equal = viewLongitudeTimeseriesData2->IsEqualTo( *viewLongitudeTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ViewZoomLevelTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( ViewZoomLevelTimeseriesDataSerializationTest )
{
    auto viewZoomLevelTimeseriesData1 = std::make_shared<ViewZoomLevelTimeseriesData>( );
    viewZoomLevelTimeseriesData1->SetId( Guid( L"{5F2894FB-26D8-7F35-FEAC-641BFA1429DF}" ) );
    viewZoomLevelTimeseriesData1->SetRowVersion( 9166275327333799163LL );
    viewZoomLevelTimeseriesData1->SetCatalog( Guid( L"{5F2894FB-26D8-7F35-FEAC-641BFA1429DF}" ) );
    viewZoomLevelTimeseriesData1->SetName( L"Name" );
    viewZoomLevelTimeseriesData1->SetMaxRetention( TimeSpan( 831333799163LL ) );
    viewZoomLevelTimeseriesData1->SetView( Guid( L"{5F2894FB-26D8-7F35-FEAC-641BFA1429DF}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *viewZoomLevelTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto viewZoomLevelTimeseriesData2 = std::reinterpret_pointer_cast<ViewZoomLevelTimeseriesData>( ReadDataFrom( source ) );
    bool equal = viewZoomLevelTimeseriesData2->IsEqualTo( *viewZoomLevelTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/WeatherStationAbsoluteHumidityTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( WeatherStationAbsoluteHumidityTimeseriesDataSerializationTest )
{
    auto weatherStationAbsoluteHumidityTimeseriesData1 = std::make_shared<WeatherStationAbsoluteHumidityTimeseriesData>( );
    weatherStationAbsoluteHumidityTimeseriesData1->SetId( Guid( L"{9985DBA8-995F-6C2E-3674-99FA99A1DB15}" ) );
    weatherStationAbsoluteHumidityTimeseriesData1->SetRowVersion( 7795336640901536680LL );
    weatherStationAbsoluteHumidityTimeseriesData1->SetCatalog( Guid( L"{9985DBA8-995F-6C2E-3674-99FA99A1DB15}" ) );
    weatherStationAbsoluteHumidityTimeseriesData1->SetName( L"Name" );
    weatherStationAbsoluteHumidityTimeseriesData1->SetMaxRetention( TimeSpan( 320901536680LL ) );
    weatherStationAbsoluteHumidityTimeseriesData1->SetWeatherStation( Guid( L"{9985DBA8-995F-6C2E-3674-99FA99A1DB15}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *weatherStationAbsoluteHumidityTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto weatherStationAbsoluteHumidityTimeseriesData2 = std::reinterpret_pointer_cast<WeatherStationAbsoluteHumidityTimeseriesData>( ReadDataFrom( source ) );
    bool equal = weatherStationAbsoluteHumidityTimeseriesData2->IsEqualTo( *weatherStationAbsoluteHumidityTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/WeatherStationAirTemperatureTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( WeatherStationAirTemperatureTimeseriesDataSerializationTest )
{
    auto weatherStationAirTemperatureTimeseriesData1 = std::make_shared<WeatherStationAirTemperatureTimeseriesData>( );
    weatherStationAirTemperatureTimeseriesData1->SetId( Guid( L"{4CE773F5-DB2A-D088-0B11-DB5432E7CEAF}" ) );
    weatherStationAirTemperatureTimeseriesData1->SetRowVersion( -3420242942262545419LL );
    weatherStationAirTemperatureTimeseriesData1->SetCatalog( Guid( L"{4CE773F5-DB2A-D088-0B11-DB5432E7CEAF}" ) );
    weatherStationAirTemperatureTimeseriesData1->SetName( L"Name" );
    weatherStationAirTemperatureTimeseriesData1->SetMaxRetention( TimeSpan( -446262545419LL ) );
    weatherStationAirTemperatureTimeseriesData1->SetWeatherStation( Guid( L"{4CE773F5-DB2A-D088-0B11-DB5432E7CEAF}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *weatherStationAirTemperatureTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto weatherStationAirTemperatureTimeseriesData2 = std::reinterpret_pointer_cast<WeatherStationAirTemperatureTimeseriesData>( ReadDataFrom( source ) );
    bool equal = weatherStationAirTemperatureTimeseriesData2->IsEqualTo( *weatherStationAirTemperatureTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/WeatherStationBarometricPressureTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( WeatherStationBarometricPressureTimeseriesDataSerializationTest )
{
    auto weatherStationBarometricPressureTimeseriesData1 = std::make_shared<WeatherStationBarometricPressureTimeseriesData>( );
    weatherStationBarometricPressureTimeseriesData1->SetId( Guid( L"{1602DEDA-FCE4-14BE-287D-3F2768407B5B}" ) );
    weatherStationBarometricPressureTimeseriesData1->SetRowVersion( 1494910182885613274LL );
    weatherStationBarometricPressureTimeseriesData1->SetCatalog( Guid( L"{1602DEDA-FCE4-14BE-287D-3F2768407B5B}" ) );
    weatherStationBarometricPressureTimeseriesData1->SetName( L"Name" );
    weatherStationBarometricPressureTimeseriesData1->SetMaxRetention( TimeSpan( 102885613274LL ) );
    weatherStationBarometricPressureTimeseriesData1->SetWeatherStation( Guid( L"{1602DEDA-FCE4-14BE-287D-3F2768407B5B}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *weatherStationBarometricPressureTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto weatherStationBarometricPressureTimeseriesData2 = std::reinterpret_pointer_cast<WeatherStationBarometricPressureTimeseriesData>( ReadDataFrom( source ) );
    bool equal = weatherStationBarometricPressureTimeseriesData2->IsEqualTo( *weatherStationBarometricPressureTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/WeatherStationDewPointTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( WeatherStationDewPointTimeseriesDataSerializationTest )
{
    auto weatherStationDewPointTimeseriesData1 = std::make_shared<WeatherStationDewPointTimeseriesData>( );
    weatherStationDewPointTimeseriesData1->SetId( Guid( L"{A045152B-2A17-8AB9-519D-54E805A2A8D4}" ) );
    weatherStationDewPointTimeseriesData1->SetRowVersion( -8450676944822528725LL );
    weatherStationDewPointTimeseriesData1->SetCatalog( Guid( L"{A045152B-2A17-8AB9-519D-54E805A2A8D4}" ) );
    weatherStationDewPointTimeseriesData1->SetName( L"Name" );
    weatherStationDewPointTimeseriesData1->SetMaxRetention( TimeSpan( -80822528725LL ) );
    weatherStationDewPointTimeseriesData1->SetWeatherStation( Guid( L"{A045152B-2A17-8AB9-519D-54E805A2A8D4}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *weatherStationDewPointTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto weatherStationDewPointTimeseriesData2 = std::reinterpret_pointer_cast<WeatherStationDewPointTimeseriesData>( ReadDataFrom( source ) );
    bool equal = weatherStationDewPointTimeseriesData2->IsEqualTo( *weatherStationDewPointTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/WeatherStationRelativeHumidityTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( WeatherStationRelativeHumidityTimeseriesDataSerializationTest )
{
    auto weatherStationRelativeHumidityTimeseriesData1 = std::make_shared<WeatherStationRelativeHumidityTimeseriesData>( );
    weatherStationRelativeHumidityTimeseriesData1->SetId( Guid( L"{8AC9E291-9E5A-E5FF-A7FF-795A51934789}" ) );
    weatherStationRelativeHumidityTimeseriesData1->SetRowVersion( -1873604808250105199LL );
    weatherStationRelativeHumidityTimeseriesData1->SetCatalog( Guid( L"{8AC9E291-9E5A-E5FF-A7FF-795A51934789}" ) );
    weatherStationRelativeHumidityTimeseriesData1->SetName( L"Name" );
    weatherStationRelativeHumidityTimeseriesData1->SetMaxRetention( TimeSpan( -72250105199LL ) );
    weatherStationRelativeHumidityTimeseriesData1->SetWeatherStation( Guid( L"{8AC9E291-9E5A-E5FF-A7FF-795A51934789}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *weatherStationRelativeHumidityTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto weatherStationRelativeHumidityTimeseriesData2 = std::reinterpret_pointer_cast<WeatherStationRelativeHumidityTimeseriesData>( ReadDataFrom( source ) );
    bool equal = weatherStationRelativeHumidityTimeseriesData2->IsEqualTo( *weatherStationRelativeHumidityTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/WeatherStationWaterTemperatureTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( WeatherStationWaterTemperatureTimeseriesDataSerializationTest )
{
    auto weatherStationWaterTemperatureTimeseriesData1 = std::make_shared<WeatherStationWaterTemperatureTimeseriesData>( );
    weatherStationWaterTemperatureTimeseriesData1->SetId( Guid( L"{DC68964A-59AF-AACA-5553-9AF53B166952}" ) );
    weatherStationWaterTemperatureTimeseriesData1->SetRowVersion( -6139996530114259382LL );
    weatherStationWaterTemperatureTimeseriesData1->SetCatalog( Guid( L"{DC68964A-59AF-AACA-5553-9AF53B166952}" ) );
    weatherStationWaterTemperatureTimeseriesData1->SetName( L"Name" );
    weatherStationWaterTemperatureTimeseriesData1->SetMaxRetention( TimeSpan( -402114259382LL ) );
    weatherStationWaterTemperatureTimeseriesData1->SetWeatherStation( Guid( L"{DC68964A-59AF-AACA-5553-9AF53B166952}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *weatherStationWaterTemperatureTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto weatherStationWaterTemperatureTimeseriesData2 = std::reinterpret_pointer_cast<WeatherStationWaterTemperatureTimeseriesData>( ReadDataFrom( source ) );
    bool equal = weatherStationWaterTemperatureTimeseriesData2->IsEqualTo( *weatherStationWaterTemperatureTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/WeatherStationWindDirectionTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( WeatherStationWindDirectionTimeseriesDataSerializationTest )
{
    auto weatherStationWindDirectionTimeseriesData1 = std::make_shared<WeatherStationWindDirectionTimeseriesData>( );
    weatherStationWindDirectionTimeseriesData1->SetId( Guid( L"{3D5AC399-0BC8-5701-EA80-D013BC5AC399}" ) );
    weatherStationWindDirectionTimeseriesData1->SetRowVersion( 6269305110927164313LL );
    weatherStationWindDirectionTimeseriesData1->SetCatalog( Guid( L"{3D5AC399-0BC8-5701-EA80-D013BC5AC399}" ) );
    weatherStationWindDirectionTimeseriesData1->SetName( L"Name" );
    weatherStationWindDirectionTimeseriesData1->SetMaxRetention( TimeSpan( 150927164313LL ) );
    weatherStationWindDirectionTimeseriesData1->SetWeatherStation( Guid( L"{3D5AC399-0BC8-5701-EA80-D013BC5AC399}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *weatherStationWindDirectionTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto weatherStationWindDirectionTimeseriesData2 = std::reinterpret_pointer_cast<WeatherStationWindDirectionTimeseriesData>( ReadDataFrom( source ) );
    bool equal = weatherStationWindDirectionTimeseriesData2->IsEqualTo( *weatherStationWindDirectionTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/WeatherStationWindSpeedTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( WeatherStationWindSpeedTimeseriesDataSerializationTest )
{
    auto weatherStationWindSpeedTimeseriesData1 = std::make_shared<WeatherStationWindSpeedTimeseriesData>( );
    weatherStationWindSpeedTimeseriesData1->SetId( Guid( L"{9AA40834-C20B-D135-8BAC-43D05925102C}" ) );
    weatherStationWindSpeedTimeseriesData1->SetRowVersion( -3371575390922078156LL );
    weatherStationWindSpeedTimeseriesData1->SetCatalog( Guid( L"{9AA40834-C20B-D135-8BAC-43D05925102C}" ) );
    weatherStationWindSpeedTimeseriesData1->SetName( L"Name" );
    weatherStationWindSpeedTimeseriesData1->SetMaxRetention( TimeSpan( -286922078156LL ) );
    weatherStationWindSpeedTimeseriesData1->SetWeatherStation( Guid( L"{9AA40834-C20B-D135-8BAC-43D05925102C}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *weatherStationWindSpeedTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto weatherStationWindSpeedTimeseriesData2 = std::reinterpret_pointer_cast<WeatherStationWindSpeedTimeseriesData>( ReadDataFrom( source ) );
    bool equal = weatherStationWindSpeedTimeseriesData2->IsEqualTo( *weatherStationWindSpeedTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GeoPosition2DTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( GeoPosition2DTimeseriesDataSerializationTest )
{
    auto geoPosition2DTimeseriesData1 = std::make_shared<GeoPosition2DTimeseriesData>( );
    geoPosition2DTimeseriesData1->SetId( Guid( L"{B940E1F3-65AE-B2C1-4D83-A6759D0287CF}" ) );
    geoPosition2DTimeseriesData1->SetRowVersion( -5566055863346470413LL );
    geoPosition2DTimeseriesData1->SetCatalog( Guid( L"{B940E1F3-65AE-B2C1-4D83-A6759D0287CF}" ) );
    geoPosition2DTimeseriesData1->SetName( L"Name" );
    geoPosition2DTimeseriesData1->SetMaxRetention( TimeSpan( -247346470413LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *geoPosition2DTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto geoPosition2DTimeseriesData2 = std::reinterpret_pointer_cast<GeoPosition2DTimeseriesData>( ReadDataFrom( source ) );
    bool equal = geoPosition2DTimeseriesData2->IsEqualTo( *geoPosition2DTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/AisAidToNavigationPositionTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( AisAidToNavigationPositionTimeseriesDataSerializationTest )
{
    auto aisAidToNavigationPositionTimeseriesData1 = std::make_shared<AisAidToNavigationPositionTimeseriesData>( );
    aisAidToNavigationPositionTimeseriesData1->SetId( Guid( L"{BC96FB00-29D3-F52A-AF54-94CB3D69DF00}" ) );
    aisAidToNavigationPositionTimeseriesData1->SetRowVersion( -780765596016510208LL );
    aisAidToNavigationPositionTimeseriesData1->SetCatalog( Guid( L"{BC96FB00-29D3-F52A-AF54-94CB3D69DF00}" ) );
    aisAidToNavigationPositionTimeseriesData1->SetName( L"Name" );
    aisAidToNavigationPositionTimeseriesData1->SetMaxRetention( TimeSpan( -764016510208LL ) );
    aisAidToNavigationPositionTimeseriesData1->SetAidToNavigation( Guid( L"{BC96FB00-29D3-F52A-AF54-94CB3D69DF00}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *aisAidToNavigationPositionTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto aisAidToNavigationPositionTimeseriesData2 = std::reinterpret_pointer_cast<AisAidToNavigationPositionTimeseriesData>( ReadDataFrom( source ) );
    bool equal = aisAidToNavigationPositionTimeseriesData2->IsEqualTo( *aisAidToNavigationPositionTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GeoPosition3DTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( GeoPosition3DTimeseriesDataSerializationTest )
{
    auto geoPosition3DTimeseriesData1 = std::make_shared<GeoPosition3DTimeseriesData>( );
    geoPosition3DTimeseriesData1->SetId( Guid( L"{F956554B-2BC0-1D77-B8EE-D4039F6AAAD2}" ) );
    geoPosition3DTimeseriesData1->SetRowVersion( 2123213857145378123LL );
    geoPosition3DTimeseriesData1->SetCatalog( Guid( L"{F956554B-2BC0-1D77-B8EE-D4039F6AAAD2}" ) );
    geoPosition3DTimeseriesData1->SetName( L"Name" );
    geoPosition3DTimeseriesData1->SetMaxRetention( TimeSpan( 385145378123LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *geoPosition3DTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto geoPosition3DTimeseriesData2 = std::reinterpret_pointer_cast<GeoPosition3DTimeseriesData>( ReadDataFrom( source ) );
    bool equal = geoPosition3DTimeseriesData2->IsEqualTo( *geoPosition3DTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/GuidTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( GuidTimeseriesDataSerializationTest )
{
    auto guidTimeseriesData1 = std::make_shared<GuidTimeseriesData>( );
    guidTimeseriesData1->SetId( Guid( L"{975C0471-455B-A5A9-A595-A2DAE93A208E}" ) );
    guidTimeseriesData1->SetRowVersion( -6509595526703610767LL );
    guidTimeseriesData1->SetCatalog( Guid( L"{975C0471-455B-A5A9-A595-A2DAE93A208E}" ) );
    guidTimeseriesData1->SetName( L"Name" );
    guidTimeseriesData1->SetMaxRetention( TimeSpan( -70703610767LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *guidTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto guidTimeseriesData2 = std::reinterpret_pointer_cast<GuidTimeseriesData>( ReadDataFrom( source ) );
    bool equal = guidTimeseriesData2->IsEqualTo( *guidTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int16TimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( Int16TimeseriesDataSerializationTest )
{
    auto int16TimeseriesData1 = std::make_shared<Int16TimeseriesData>( );
    int16TimeseriesData1->SetId( Guid( L"{6CBDC146-1F86-ACB9-359D-F86136BD8362}" ) );
    int16TimeseriesData1->SetRowVersion( -6000730366284021434LL );
    int16TimeseriesData1->SetCatalog( Guid( L"{6CBDC146-1F86-ACB9-359D-F86136BD8362}" ) );
    int16TimeseriesData1->SetName( L"Name" );
    int16TimeseriesData1->SetMaxRetention( TimeSpan( -670284021434LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int16TimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int16TimeseriesData2 = std::reinterpret_pointer_cast<Int16TimeseriesData>( ReadDataFrom( source ) );
    bool equal = int16TimeseriesData2->IsEqualTo( *int16TimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int32TimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( Int32TimeseriesDataSerializationTest )
{
    auto int32TimeseriesData1 = std::make_shared<Int32TimeseriesData>( );
    int32TimeseriesData1->SetId( Guid( L"{BF8A1AA1-9B78-29F8-941F-D91EFD515885}" ) );
    int32TimeseriesData1->SetRowVersion( 3024338092691167905LL );
    int32TimeseriesData1->SetCatalog( Guid( L"{BF8A1AA1-9B78-29F8-941F-D91EFD515885}" ) );
    int32TimeseriesData1->SetName( L"Name" );
    int32TimeseriesData1->SetMaxRetention( TimeSpan( 268691167905LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int32TimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int32TimeseriesData2 = std::reinterpret_pointer_cast<Int32TimeseriesData>( ReadDataFrom( source ) );
    bool equal = int32TimeseriesData2->IsEqualTo( *int32TimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarAzimuthOffsetTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarAzimuthOffsetTimeseriesDataSerializationTest )
{
    auto radarAzimuthOffsetTimeseriesData1 = std::make_shared<RadarAzimuthOffsetTimeseriesData>( );
    radarAzimuthOffsetTimeseriesData1->SetId( Guid( L"{5E4E1D3D-1C4C-47B5-E2AD-38327A72B8BC}" ) );
    radarAzimuthOffsetTimeseriesData1->SetRowVersion( 5167067261802782013LL );
    radarAzimuthOffsetTimeseriesData1->SetCatalog( Guid( L"{5E4E1D3D-1C4C-47B5-E2AD-38327A72B8BC}" ) );
    radarAzimuthOffsetTimeseriesData1->SetName( L"Name" );
    radarAzimuthOffsetTimeseriesData1->SetMaxRetention( TimeSpan( 797802782013LL ) );
    radarAzimuthOffsetTimeseriesData1->SetRadar( Guid( L"{5E4E1D3D-1C4C-47B5-E2AD-38327A72B8BC}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarAzimuthOffsetTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarAzimuthOffsetTimeseriesData2 = std::reinterpret_pointer_cast<RadarAzimuthOffsetTimeseriesData>( ReadDataFrom( source ) );
    bool equal = radarAzimuthOffsetTimeseriesData2->IsEqualTo( *radarAzimuthOffsetTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarFastTimeConstantLevelTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarFastTimeConstantLevelTimeseriesDataSerializationTest )
{
    auto radarFastTimeConstantLevelTimeseriesData1 = std::make_shared<RadarFastTimeConstantLevelTimeseriesData>( );
    radarFastTimeConstantLevelTimeseriesData1->SetId( Guid( L"{366E9EC4-3487-7CD6-3E6B-2CE16C767923}" ) );
    radarFastTimeConstantLevelTimeseriesData1->SetRowVersion( 8995435061057593028LL );
    radarFastTimeConstantLevelTimeseriesData1->SetCatalog( Guid( L"{366E9EC4-3487-7CD6-3E6B-2CE16C767923}" ) );
    radarFastTimeConstantLevelTimeseriesData1->SetName( L"Name" );
    radarFastTimeConstantLevelTimeseriesData1->SetMaxRetention( TimeSpan( 149057593028LL ) );
    radarFastTimeConstantLevelTimeseriesData1->SetRadar( Guid( L"{366E9EC4-3487-7CD6-3E6B-2CE16C767923}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarFastTimeConstantLevelTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarFastTimeConstantLevelTimeseriesData2 = std::reinterpret_pointer_cast<RadarFastTimeConstantLevelTimeseriesData>( ReadDataFrom( source ) );
    bool equal = radarFastTimeConstantLevelTimeseriesData2->IsEqualTo( *radarFastTimeConstantLevelTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarFastTimeConstantModeTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarFastTimeConstantModeTimeseriesDataSerializationTest )
{
    auto radarFastTimeConstantModeTimeseriesData1 = std::make_shared<RadarFastTimeConstantModeTimeseriesData>( );
    radarFastTimeConstantModeTimeseriesData1->SetId( Guid( L"{AEF3B2BC-F0DB-016C-8036-0FDB75CF4D3D}" ) );
    radarFastTimeConstantModeTimeseriesData1->SetRowVersion( 102721717846389436LL );
    radarFastTimeConstantModeTimeseriesData1->SetCatalog( Guid( L"{AEF3B2BC-F0DB-016C-8036-0FDB75CF4D3D}" ) );
    radarFastTimeConstantModeTimeseriesData1->SetName( L"Name" );
    radarFastTimeConstantModeTimeseriesData1->SetMaxRetention( TimeSpan( 757846389436LL ) );
    radarFastTimeConstantModeTimeseriesData1->SetRadar( Guid( L"{AEF3B2BC-F0DB-016C-8036-0FDB75CF4D3D}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarFastTimeConstantModeTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarFastTimeConstantModeTimeseriesData2 = std::reinterpret_pointer_cast<RadarFastTimeConstantModeTimeseriesData>( ReadDataFrom( source ) );
    bool equal = radarFastTimeConstantModeTimeseriesData2->IsEqualTo( *radarFastTimeConstantModeTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarPulseTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarPulseTimeseriesDataSerializationTest )
{
    auto radarPulseTimeseriesData1 = std::make_shared<RadarPulseTimeseriesData>( );
    radarPulseTimeseriesData1->SetId( Guid( L"{1E2910A2-C988-2024-0424-931178940845}" ) );
    radarPulseTimeseriesData1->SetRowVersion( 2316197694834020514LL );
    radarPulseTimeseriesData1->SetCatalog( Guid( L"{1E2910A2-C988-2024-0424-931178940845}" ) );
    radarPulseTimeseriesData1->SetName( L"Name" );
    radarPulseTimeseriesData1->SetMaxRetention( TimeSpan( 318834020514LL ) );
    radarPulseTimeseriesData1->SetRadar( Guid( L"{1E2910A2-C988-2024-0424-931178940845}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarPulseTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarPulseTimeseriesData2 = std::reinterpret_pointer_cast<RadarPulseTimeseriesData>( ReadDataFrom( source ) );
    bool equal = radarPulseTimeseriesData2->IsEqualTo( *radarPulseTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarSector1EndTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarSector1EndTimeseriesDataSerializationTest )
{
    auto radarSector1EndTimeseriesData1 = std::make_shared<RadarSector1EndTimeseriesData>( );
    radarSector1EndTimeseriesData1->SetId( Guid( L"{42B1F5DD-BB0D-310E-8C70-DDB0428DAFBB}" ) );
    radarSector1EndTimeseriesData1->SetRowVersion( 3534968423160346077LL );
    radarSector1EndTimeseriesData1->SetCatalog( Guid( L"{42B1F5DD-BB0D-310E-8C70-DDB0428DAFBB}" ) );
    radarSector1EndTimeseriesData1->SetName( L"Name" );
    radarSector1EndTimeseriesData1->SetMaxRetention( TimeSpan( 551160346077LL ) );
    radarSector1EndTimeseriesData1->SetRadar( Guid( L"{42B1F5DD-BB0D-310E-8C70-DDB0428DAFBB}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarSector1EndTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarSector1EndTimeseriesData2 = std::reinterpret_pointer_cast<RadarSector1EndTimeseriesData>( ReadDataFrom( source ) );
    bool equal = radarSector1EndTimeseriesData2->IsEqualTo( *radarSector1EndTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarSector1StartTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarSector1StartTimeseriesDataSerializationTest )
{
    auto radarSector1StartTimeseriesData1 = std::make_shared<RadarSector1StartTimeseriesData>( );
    radarSector1StartTimeseriesData1->SetId( Guid( L"{FB7089D3-826F-D790-EB09-41F6DF0E91CB}" ) );
    radarSector1StartTimeseriesData1->SetRowVersion( -2913685541437273645LL );
    radarSector1StartTimeseriesData1->SetCatalog( Guid( L"{FB7089D3-826F-D790-EB09-41F6DF0E91CB}" ) );
    radarSector1StartTimeseriesData1->SetName( L"Name" );
    radarSector1StartTimeseriesData1->SetMaxRetention( TimeSpan( -197437273645LL ) );
    radarSector1StartTimeseriesData1->SetRadar( Guid( L"{FB7089D3-826F-D790-EB09-41F6DF0E91CB}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarSector1StartTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarSector1StartTimeseriesData2 = std::reinterpret_pointer_cast<RadarSector1StartTimeseriesData>( ReadDataFrom( source ) );
    bool equal = radarSector1StartTimeseriesData2->IsEqualTo( *radarSector1StartTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarSector2EndTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarSector2EndTimeseriesDataSerializationTest )
{
    auto radarSector2EndTimeseriesData1 = std::make_shared<RadarSector2EndTimeseriesData>( );
    radarSector2EndTimeseriesData1->SetId( Guid( L"{469274EE-3468-A02F-05F4-2C1662492E77}" ) );
    radarSector2EndTimeseriesData1->SetRowVersion( -6904242081270434578LL );
    radarSector2EndTimeseriesData1->SetCatalog( Guid( L"{469274EE-3468-A02F-05F4-2C1662492E77}" ) );
    radarSector2EndTimeseriesData1->SetName( L"Name" );
    radarSector2EndTimeseriesData1->SetMaxRetention( TimeSpan( -801270434578LL ) );
    radarSector2EndTimeseriesData1->SetRadar( Guid( L"{469274EE-3468-A02F-05F4-2C1662492E77}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarSector2EndTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarSector2EndTimeseriesData2 = std::reinterpret_pointer_cast<RadarSector2EndTimeseriesData>( ReadDataFrom( source ) );
    bool equal = radarSector2EndTimeseriesData2->IsEqualTo( *radarSector2EndTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarSector2StartTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarSector2StartTimeseriesDataSerializationTest )
{
    auto radarSector2StartTimeseriesData1 = std::make_shared<RadarSector2StartTimeseriesData>( );
    radarSector2StartTimeseriesData1->SetId( Guid( L"{AA794E3C-C797-9FEF-F9F7-E3E9559E723C}" ) );
    radarSector2StartTimeseriesData1->SetRowVersion( -6922094648031097284LL );
    radarSector2StartTimeseriesData1->SetCatalog( Guid( L"{AA794E3C-C797-9FEF-F9F7-E3E9559E723C}" ) );
    radarSector2StartTimeseriesData1->SetName( L"Name" );
    radarSector2StartTimeseriesData1->SetMaxRetention( TimeSpan( -536031097284LL ) );
    radarSector2StartTimeseriesData1->SetRadar( Guid( L"{AA794E3C-C797-9FEF-F9F7-E3E9559E723C}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarSector2StartTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarSector2StartTimeseriesData2 = std::reinterpret_pointer_cast<RadarSector2StartTimeseriesData>( ReadDataFrom( source ) );
    bool equal = radarSector2StartTimeseriesData2->IsEqualTo( *radarSector2StartTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarSensitivityTimeControlLevelTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarSensitivityTimeControlLevelTimeseriesDataSerializationTest )
{
    auto radarSensitivityTimeControlLevelTimeseriesData1 = std::make_shared<RadarSensitivityTimeControlLevelTimeseriesData>( );
    radarSensitivityTimeControlLevelTimeseriesData1->SetId( Guid( L"{99907E01-44A9-8916-9168-229599097E80}" ) );
    radarSensitivityTimeControlLevelTimeseriesData1->SetRowVersion( -8568585745809244671LL );
    radarSensitivityTimeControlLevelTimeseriesData1->SetCatalog( Guid( L"{99907E01-44A9-8916-9168-229599097E80}" ) );
    radarSensitivityTimeControlLevelTimeseriesData1->SetName( L"Name" );
    radarSensitivityTimeControlLevelTimeseriesData1->SetMaxRetention( TimeSpan( -529809244671LL ) );
    radarSensitivityTimeControlLevelTimeseriesData1->SetRadar( Guid( L"{99907E01-44A9-8916-9168-229599097E80}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarSensitivityTimeControlLevelTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarSensitivityTimeControlLevelTimeseriesData2 = std::reinterpret_pointer_cast<RadarSensitivityTimeControlLevelTimeseriesData>( ReadDataFrom( source ) );
    bool equal = radarSensitivityTimeControlLevelTimeseriesData2->IsEqualTo( *radarSensitivityTimeControlLevelTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadarTuningTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( RadarTuningTimeseriesDataSerializationTest )
{
    auto radarTuningTimeseriesData1 = std::make_shared<RadarTuningTimeseriesData>( );
    radarTuningTimeseriesData1->SetId( Guid( L"{2BC44D8C-8D89-F863-1FC6-B191D423B231}" ) );
    radarTuningTimeseriesData1->SetRowVersion( -548439109324747380LL );
    radarTuningTimeseriesData1->SetCatalog( Guid( L"{2BC44D8C-8D89-F863-1FC6-B191D423B231}" ) );
    radarTuningTimeseriesData1->SetName( L"Name" );
    radarTuningTimeseriesData1->SetMaxRetention( TimeSpan( -421324747380LL ) );
    radarTuningTimeseriesData1->SetRadar( Guid( L"{2BC44D8C-8D89-F863-1FC6-B191D423B231}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radarTuningTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radarTuningTimeseriesData2 = std::reinterpret_pointer_cast<RadarTuningTimeseriesData>( ReadDataFrom( source ) );
    bool equal = radarTuningTimeseriesData2->IsEqualTo( *radarTuningTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/VesselPersonsOnBoardTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( VesselPersonsOnBoardTimeseriesDataSerializationTest )
{
    auto vesselPersonsOnBoardTimeseriesData1 = std::make_shared<VesselPersonsOnBoardTimeseriesData>( );
    vesselPersonsOnBoardTimeseriesData1->SetId( Guid( L"{FEAAF2E4-72D5-E12D-87B4-4EAB7F554F27}" ) );
    vesselPersonsOnBoardTimeseriesData1->SetRowVersion( -2220992777797569820LL );
    vesselPersonsOnBoardTimeseriesData1->SetCatalog( Guid( L"{FEAAF2E4-72D5-E12D-87B4-4EAB7F554F27}" ) );
    vesselPersonsOnBoardTimeseriesData1->SetName( L"Name" );
    vesselPersonsOnBoardTimeseriesData1->SetMaxRetention( TimeSpan( -425797569820LL ) );
    vesselPersonsOnBoardTimeseriesData1->SetVessel( Guid( L"{FEAAF2E4-72D5-E12D-87B4-4EAB7F554F27}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *vesselPersonsOnBoardTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto vesselPersonsOnBoardTimeseriesData2 = std::reinterpret_pointer_cast<VesselPersonsOnBoardTimeseriesData>( ReadDataFrom( source ) );
    bool equal = vesselPersonsOnBoardTimeseriesData2->IsEqualTo( *vesselPersonsOnBoardTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Int64TimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( Int64TimeseriesDataSerializationTest )
{
    auto int64TimeseriesData1 = std::make_shared<Int64TimeseriesData>( );
    int64TimeseriesData1->SetId( Guid( L"{031600FF-2473-658D-A6B1-24CEC06800FF}" ) );
    int64TimeseriesData1->SetRowVersion( 7317545045938536703LL );
    int64TimeseriesData1->SetCatalog( Guid( L"{031600FF-2473-658D-A6B1-24CEC06800FF}" ) );
    int64TimeseriesData1->SetName( L"Name" );
    int64TimeseriesData1->SetMaxRetention( TimeSpan( 725938536703LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *int64TimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto int64TimeseriesData2 = std::reinterpret_pointer_cast<Int64TimeseriesData>( ReadDataFrom( source ) );
    bool equal = int64TimeseriesData2->IsEqualTo( *int64TimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Position2DTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( Position2DTimeseriesDataSerializationTest )
{
    auto position2DTimeseriesData1 = std::make_shared<Position2DTimeseriesData>( );
    position2DTimeseriesData1->SetId( Guid( L"{A244E20D-8E28-CF70-F30E-7114452247B0}" ) );
    position2DTimeseriesData1->SetRowVersion( -3499140605294616051LL );
    position2DTimeseriesData1->SetCatalog( Guid( L"{A244E20D-8E28-CF70-F30E-7114452247B0}" ) );
    position2DTimeseriesData1->SetName( L"Name" );
    position2DTimeseriesData1->SetMaxRetention( TimeSpan( -221294616051LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *position2DTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto position2DTimeseriesData2 = std::reinterpret_pointer_cast<Position2DTimeseriesData>( ReadDataFrom( source ) );
    bool equal = position2DTimeseriesData2->IsEqualTo( *position2DTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Position3DTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( Position3DTimeseriesDataSerializationTest )
{
    auto position3DTimeseriesData1 = std::make_shared<Position3DTimeseriesData>( );
    position3DTimeseriesData1->SetId( Guid( L"{13DB07D3-1553-8C8C-3131-A8CAC8DBE0CB}" ) );
    position3DTimeseriesData1->SetRowVersion( -8319250965100558381LL );
    position3DTimeseriesData1->SetCatalog( Guid( L"{13DB07D3-1553-8C8C-3131-A8CAC8DBE0CB}" ) );
    position3DTimeseriesData1->SetName( L"Name" );
    position3DTimeseriesData1->SetMaxRetention( TimeSpan( -597100558381LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *position3DTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto position3DTimeseriesData2 = std::reinterpret_pointer_cast<Position3DTimeseriesData>( ReadDataFrom( source ) );
    bool equal = position3DTimeseriesData2->IsEqualTo( *position3DTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ReferenceTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( ReferenceTimeseriesDataSerializationTest )
{
    auto referenceTimeseriesData1 = std::make_shared<ReferenceTimeseriesData>( );
    referenceTimeseriesData1->SetId( Guid( L"{2A04F6AE-BC6A-A651-658A-3D5654206F75}" ) );
    referenceTimeseriesData1->SetRowVersion( -6462176826142427474LL );
    referenceTimeseriesData1->SetCatalog( Guid( L"{2A04F6AE-BC6A-A651-658A-3D5654206F75}" ) );
    referenceTimeseriesData1->SetName( L"Name" );
    referenceTimeseriesData1->SetMaxRetention( TimeSpan( -282142427474LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *referenceTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto referenceTimeseriesData2 = std::reinterpret_pointer_cast<ReferenceTimeseriesData>( ReadDataFrom( source ) );
    bool equal = referenceTimeseriesData2->IsEqualTo( *referenceTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SByteTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( SByteTimeseriesDataSerializationTest )
{
    auto sByteTimeseriesData1 = std::make_shared<SByteTimeseriesData>( );
    sByteTimeseriesData1->SetId( Guid( L"{1B8C2A12-5A67-DC90-3B09-5AE6D8315448}" ) );
    sByteTimeseriesData1->SetRowVersion( -2553441589828769262LL );
    sByteTimeseriesData1->SetCatalog( Guid( L"{1B8C2A12-5A67-DC90-3B09-5AE6D8315448}" ) );
    sByteTimeseriesData1->SetName( L"Name" );
    sByteTimeseriesData1->SetMaxRetention( TimeSpan( -181828769262LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *sByteTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto sByteTimeseriesData2 = std::reinterpret_pointer_cast<SByteTimeseriesData>( ReadDataFrom( source ) );
    bool equal = sByteTimeseriesData2->IsEqualTo( *sByteTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/SingleTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( SingleTimeseriesDataSerializationTest )
{
    auto singleTimeseriesData1 = std::make_shared<SingleTimeseriesData>( );
    singleTimeseriesData1->SetId( Guid( L"{92306DBD-F6D7-CC44-3322-6FEB490CB6BD}" ) );
    singleTimeseriesData1->SetRowVersion( -3727583185824879171LL );
    singleTimeseriesData1->SetCatalog( Guid( L"{92306DBD-F6D7-CC44-3322-6FEB490CB6BD}" ) );
    singleTimeseriesData1->SetName( L"Name" );
    singleTimeseriesData1->SetMaxRetention( TimeSpan( -337824879171LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *singleTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto singleTimeseriesData2 = std::reinterpret_pointer_cast<SingleTimeseriesData>( ReadDataFrom( source ) );
    bool equal = singleTimeseriesData2->IsEqualTo( *singleTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/StringTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( StringTimeseriesDataSerializationTest )
{
    auto stringTimeseriesData1 = std::make_shared<StringTimeseriesData>( );
    stringTimeseriesData1->SetId( Guid( L"{543F4243-6A6F-6CC7-36E3-56F62AFC42C2}" ) );
    stringTimeseriesData1->SetRowVersion( 7838350702848983619LL );
    stringTimeseriesData1->SetCatalog( Guid( L"{543F4243-6A6F-6CC7-36E3-56F62AFC42C2}" ) );
    stringTimeseriesData1->SetName( L"Name" );
    stringTimeseriesData1->SetMaxRetention( TimeSpan( 142848983619LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *stringTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto stringTimeseriesData2 = std::reinterpret_pointer_cast<StringTimeseriesData>( ReadDataFrom( source ) );
    bool equal = stringTimeseriesData2->IsEqualTo( *stringTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TimeSpanTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( TimeSpanTimeseriesDataSerializationTest )
{
    auto timeSpanTimeseriesData1 = std::make_shared<TimeSpanTimeseriesData>( );
    timeSpanTimeseriesData1->SetId( Guid( L"{10BB8F38-4616-F79B-EFD9-626808DDF11C}" ) );
    timeSpanTimeseriesData1->SetRowVersion( -604812664367247560LL );
    timeSpanTimeseriesData1->SetCatalog( Guid( L"{10BB8F38-4616-F79B-EFD9-626808DDF11C}" ) );
    timeSpanTimeseriesData1->SetName( L"Name" );
    timeSpanTimeseriesData1->SetMaxRetention( TimeSpan( -568367247560LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *timeSpanTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto timeSpanTimeseriesData2 = std::reinterpret_pointer_cast<TimeSpanTimeseriesData>( ReadDataFrom( source ) );
    bool equal = timeSpanTimeseriesData2->IsEqualTo( *timeSpanTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt16TimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( UInt16TimeseriesDataSerializationTest )
{
    auto uInt16TimeseriesData1 = std::make_shared<UInt16TimeseriesData>( );
    uInt16TimeseriesData1->SetId( Guid( L"{C3004051-5156-9488-2911-8A6AC300028A}" ) );
    uInt16TimeseriesData1->SetRowVersion( -7743850126182956975LL );
    uInt16TimeseriesData1->SetCatalog( Guid( L"{C3004051-5156-9488-2911-8A6AC300028A}" ) );
    uInt16TimeseriesData1->SetName( L"Name" );
    uInt16TimeseriesData1->SetMaxRetention( TimeSpan( -430182956975LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt16TimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt16TimeseriesData2 = std::reinterpret_pointer_cast<UInt16TimeseriesData>( ReadDataFrom( source ) );
    bool equal = uInt16TimeseriesData2->IsEqualTo( *uInt16TimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt32TimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( UInt32TimeseriesDataSerializationTest )
{
    auto uInt32TimeseriesData1 = std::make_shared<UInt32TimeseriesData>( );
    uInt32TimeseriesData1->SetId( Guid( L"{1E4F9B7F-3DF1-27F5-E4AF-BC8F78F2D9FE}" ) );
    uInt32TimeseriesData1->SetRowVersion( 2879275642578246527LL );
    uInt32TimeseriesData1->SetCatalog( Guid( L"{1E4F9B7F-3DF1-27F5-E4AF-BC8F78F2D9FE}" ) );
    uInt32TimeseriesData1->SetName( L"Name" );
    uInt32TimeseriesData1->SetMaxRetention( TimeSpan( 826578246527LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt32TimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt32TimeseriesData2 = std::reinterpret_pointer_cast<UInt32TimeseriesData>( ReadDataFrom( source ) );
    bool equal = uInt32TimeseriesData2->IsEqualTo( *uInt32TimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/RadomeStatusTimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( RadomeStatusTimeseriesDataSerializationTest )
{
    auto radomeStatusTimeseriesData1 = std::make_shared<RadomeStatusTimeseriesData>( );
    radomeStatusTimeseriesData1->SetId( Guid( L"{D21766E9-B3DE-8353-C1CA-CD7B4BE86697}" ) );
    radomeStatusTimeseriesData1->SetRowVersion( -8983639062085146903LL );
    radomeStatusTimeseriesData1->SetCatalog( Guid( L"{D21766E9-B3DE-8353-C1CA-CD7B4BE86697}" ) );
    radomeStatusTimeseriesData1->SetName( L"Name" );
    radomeStatusTimeseriesData1->SetMaxRetention( TimeSpan( -342085146903LL ) );
    radomeStatusTimeseriesData1->SetRadome( Guid( L"{D21766E9-B3DE-8353-C1CA-CD7B4BE86697}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *radomeStatusTimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto radomeStatusTimeseriesData2 = std::reinterpret_pointer_cast<RadomeStatusTimeseriesData>( ReadDataFrom( source ) );
    bool equal = radomeStatusTimeseriesData2->IsEqualTo( *radomeStatusTimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt64TimeseriesDataSerializationTest
BOOST_AUTO_TEST_CASE( UInt64TimeseriesDataSerializationTest )
{
    auto uInt64TimeseriesData1 = std::make_shared<UInt64TimeseriesData>( );
    uInt64TimeseriesData1->SetId( Guid( L"{EE6B112D-3F61-9C80-3901-FC8677D688B4}" ) );
    uInt64TimeseriesData1->SetRowVersion( -7169660916929457875LL );
    uInt64TimeseriesData1->SetCatalog( Guid( L"{EE6B112D-3F61-9C80-3901-FC8677D688B4}" ) );
    uInt64TimeseriesData1->SetName( L"Name" );
    uInt64TimeseriesData1->SetMaxRetention( TimeSpan( -564929457875LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt64TimeseriesData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt64TimeseriesData2 = std::reinterpret_pointer_cast<UInt64TimeseriesData>( ReadDataFrom( source ) );
    bool equal = uInt64TimeseriesData2->IsEqualTo( *uInt64TimeseriesData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TimeseriesCatalogDataSerializationTest
BOOST_AUTO_TEST_CASE( TimeseriesCatalogDataSerializationTest )
{
    auto timeseriesCatalogData1 = std::make_shared<TimeseriesCatalogData>( );
    timeseriesCatalogData1->SetId( Guid( L"{BD1CA5BF-744B-CF8B-F3D1-2ED2BD38A5FD}" ) );
    timeseriesCatalogData1->SetRowVersion( -3491569217451547201LL );
    timeseriesCatalogData1->SetCatalog( Guid( L"{BD1CA5BF-744B-CF8B-F3D1-2ED2BD38A5FD}" ) );
    timeseriesCatalogData1->SetName( L"Name" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *timeseriesCatalogData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto timeseriesCatalogData2 = std::reinterpret_pointer_cast<TimeseriesCatalogData>( ReadDataFrom( source ) );
    bool equal = timeseriesCatalogData2->IsEqualTo( *timeseriesCatalogData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TimeseriesInfoDataSerializationTest
BOOST_AUTO_TEST_CASE( TimeseriesInfoDataSerializationTest )
{
    auto timeseriesInfoData1 = std::make_shared<TimeseriesInfoData>( );
    timeseriesInfoData1->SetId( Guid( L"{7A785D97-FDEA-3E83-7CC1-BF575E1EBAE9}" ) );
    timeseriesInfoData1->SetRowVersion( 4504723235819511191LL );
    timeseriesInfoData1->SetFirstTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    timeseriesInfoData1->SetLastTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    timeseriesInfoData1->SetCount( 4504723235819511191LL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *timeseriesInfoData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto timeseriesInfoData2 = std::reinterpret_pointer_cast<TimeseriesInfoData>( ReadDataFrom( source ) );
    bool equal = timeseriesInfoData2->IsEqualTo( *timeseriesInfoData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TimeSpanTimeseriesValueDataSerializationTest
BOOST_AUTO_TEST_CASE( TimeSpanTimeseriesValueDataSerializationTest )
{
    auto timeSpanTimeseriesValueData1 = std::make_shared<TimeSpanTimeseriesValueData>( );
    timeSpanTimeseriesValueData1->SetId( Guid( L"{B9BB7A7B-A746-EDFF-B7FF-E5629DDD5EDE}" ) );
    timeSpanTimeseriesValueData1->SetRowVersion( -1297134245453792645LL );
    timeSpanTimeseriesValueData1->SetTimeseries( Guid( L"{B9BB7A7B-A746-EDFF-B7FF-E5629DDD5EDE}" ) );
    timeSpanTimeseriesValueData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    timeSpanTimeseriesValueData1->SetValue( TimeSpan( -677453792645LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *timeSpanTimeseriesValueData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto timeSpanTimeseriesValueData2 = std::reinterpret_pointer_cast<TimeSpanTimeseriesValueData>( ReadDataFrom( source ) );
    bool equal = timeSpanTimeseriesValueData2->IsEqualTo( *timeSpanTimeseriesValueData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TrackableItemTrackLinkDataSerializationTest
BOOST_AUTO_TEST_CASE( TrackableItemTrackLinkDataSerializationTest )
{
    auto trackableItemTrackLinkData1 = std::make_shared<TrackableItemTrackLinkData>( );
    trackableItemTrackLinkData1->SetId( Guid( L"{008FB1C3-B963-E78F-E7F1-9DC600F18DC3}" ) );
    trackableItemTrackLinkData1->SetRowVersion( -1760985094416256573LL );
    trackableItemTrackLinkData1->SetItem( Guid( L"{008FB1C3-B963-E78F-E7F1-9DC600F18DC3}" ) );
    trackableItemTrackLinkData1->SetTrack( Guid( L"{008FB1C3-B963-E78F-E7F1-9DC600F18DC3}" ) );
    trackableItemTrackLinkData1->SetStart( DateTime( 1, 1, 1, 14, 37, 6 ) );
    trackableItemTrackLinkData1->SetEnd( DateTime( 1, 1, 1, 14, 37, 6 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *trackableItemTrackLinkData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto trackableItemTrackLinkData2 = std::reinterpret_pointer_cast<TrackableItemTrackLinkData>( ReadDataFrom( source ) );
    bool equal = trackableItemTrackLinkData2->IsEqualTo( *trackableItemTrackLinkData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TrackDataSerializationTest
BOOST_AUTO_TEST_CASE( TrackDataSerializationTest )
{
    auto trackData1 = std::make_shared<TrackData>( );
    trackData1->SetId( Guid( L"{2BF4613E-94F3-88C0-1103-29CFD42F867C}" ) );
    trackData1->SetRowVersion( -8592704316887506626LL );
    trackData1->SetTracker( Guid( L"{2BF4613E-94F3-88C0-1103-29CFD42F867C}" ) );
    trackData1->SetTrackNumber( -8592704316887506626LL );
    trackData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *trackData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto trackData2 = std::reinterpret_pointer_cast<TrackData>( ReadDataFrom( source ) );
    bool equal = trackData2->IsEqualTo( *trackData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/Track3DDataSerializationTest
BOOST_AUTO_TEST_CASE( Track3DDataSerializationTest )
{
    auto track3DData1 = std::make_shared<Track3DData>( );
    track3DData1->SetId( Guid( L"{FD0A3793-C049-E93F-97FC-0392BF50ECC9}" ) );
    track3DData1->SetRowVersion( -1639380315329120365LL );
    track3DData1->SetTracker( Guid( L"{FD0A3793-C049-E93F-97FC-0392BF50ECC9}" ) );
    track3DData1->SetTrackNumber( -1639380315329120365LL );
    track3DData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *track3DData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto track3DData2 = std::reinterpret_pointer_cast<Track3DData>( ReadDataFrom( source ) );
    bool equal = track3DData2->IsEqualTo( *track3DData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TrackerFilterParametersDataSerializationTest
BOOST_AUTO_TEST_CASE( TrackerFilterParametersDataSerializationTest )
{
    auto trackerFilterParametersData1 = std::make_shared<TrackerFilterParametersData>( );
    trackerFilterParametersData1->SetId( Guid( L"{488067B9-69E4-0154-802A-96271201E69D}" ) );
    trackerFilterParametersData1->SetRowVersion( 95817921271457721LL );
    trackerFilterParametersData1->SetTracker( Guid( L"{488067B9-69E4-0154-802A-96271201E69D}" ) );
    trackerFilterParametersData1->SetName( L"Name" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *trackerFilterParametersData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto trackerFilterParametersData2 = std::reinterpret_pointer_cast<TrackerFilterParametersData>( ReadDataFrom( source ) );
    bool equal = trackerFilterParametersData2->IsEqualTo( *trackerFilterParametersData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TrackerFilterParametersConfigurationDataSerializationTest
BOOST_AUTO_TEST_CASE( TrackerFilterParametersConfigurationDataSerializationTest )
{
    auto trackerFilterParametersConfigurationData1 = std::make_shared<TrackerFilterParametersConfigurationData>( );
    trackerFilterParametersConfigurationData1->SetId( Guid( L"{060FC360-326B-7108-8E10-4CD660F0C306}" ) );
    trackerFilterParametersConfigurationData1->SetRowVersion( 8144815361344127840LL );
    trackerFilterParametersConfigurationData1->SetParameters( Guid( L"{060FC360-326B-7108-8E10-4CD660F0C306}" ) );
    trackerFilterParametersConfigurationData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    trackerFilterParametersConfigurationData1->SetUseNaivePredictor( false );
    trackerFilterParametersConfigurationData1->SetNumberOfPoints( 101696352L );
    trackerFilterParametersConfigurationData1->SetWindowSize( 101696352L );
    trackerFilterParametersConfigurationData1->SetStabilizeCount( 101696352L );
    trackerFilterParametersConfigurationData1->SetMaxBadPoints( 101696352L );
    trackerFilterParametersConfigurationData1->SetModelType( TrackerFilterModelType::Damp2 );
    trackerFilterParametersConfigurationData1->SetSigmaR( 8144815361344128 );
    trackerFilterParametersConfigurationData1->SetSigmaAcc( 8144815361344128 );
    trackerFilterParametersConfigurationData1->SetTauVel( 8144815361344128 );
    trackerFilterParametersConfigurationData1->SetTauAcc( 8144815361344128 );
    trackerFilterParametersConfigurationData1->SetDeltaRMin( 8144815361344128 );
    trackerFilterParametersConfigurationData1->SetDeltaVMax( 8144815361344128 );
    trackerFilterParametersConfigurationData1->SetDeltaAMax( 8144815361344128 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *trackerFilterParametersConfigurationData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto trackerFilterParametersConfigurationData2 = std::reinterpret_pointer_cast<TrackerFilterParametersConfigurationData>( ReadDataFrom( source ) );
    bool equal = trackerFilterParametersConfigurationData2->IsEqualTo( *trackerFilterParametersConfigurationData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TrackInfoDataSerializationTest
BOOST_AUTO_TEST_CASE( TrackInfoDataSerializationTest )
{
    auto trackInfoData1 = std::make_shared<TrackInfoData>( );
    trackInfoData1->SetId( Guid( L"{DDE619C0-47E8-DC84-3B21-E217BB679803}" ) );
    trackInfoData1->SetRowVersion( -2556839622958769728LL );
    trackInfoData1->SetFirstTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    trackInfoData1->SetLastTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    trackInfoData1->SetCount( -2556839622958769728LL );
    trackInfoData1->SetNorthWestLatitude( 15889904450750782 );
    trackInfoData1->SetNorthWestLongitude( 15889904450750782 );
    trackInfoData1->SetSouthEastLatitude( 15889904450750782 );
    trackInfoData1->SetSouthEastLongitude( 15889904450750782 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *trackInfoData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto trackInfoData2 = std::reinterpret_pointer_cast<TrackInfoData>( ReadDataFrom( source ) );
    bool equal = trackInfoData2->IsEqualTo( *trackInfoData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TrackingServiceOptionsDataSerializationTest
BOOST_AUTO_TEST_CASE( TrackingServiceOptionsDataSerializationTest )
{
    auto trackingServiceOptionsData1 = std::make_shared<TrackingServiceOptionsData>( );
    trackingServiceOptionsData1->SetId( Guid( L"{EBE67FA6-2321-643C-263C-C484D767FE65}" ) );
    trackingServiceOptionsData1->SetRowVersion( 7222686530994077606LL );
    trackingServiceOptionsData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    trackingServiceOptionsData1->SetTimerInterval( TimeSpan( 770994077606LL ) );
    trackingServiceOptionsData1->SetMaxAgeOfCurrentTrackValue( TimeSpan( 770994077606LL ) );
    trackingServiceOptionsData1->SetFalseThreshold( 7222686530994078 );
    trackingServiceOptionsData1->SetDistanceThreshold( 7222686530994078 );
    trackingServiceOptionsData1->SetDistanceUnmergeThreshold( 7222686530994078 );
    trackingServiceOptionsData1->SetUnmergeLatency( 7222686530994077606LL );
    trackingServiceOptionsData1->SetKalmanFiltering( false );
    trackingServiceOptionsData1->SetMaxCourseDeviation( 7222686530994078 );
    trackingServiceOptionsData1->SetMaxSpeedDeviation( 7222686530994078 );
    trackingServiceOptionsData1->SetMinimumSpeedThreshold( 7222686530994078 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *trackingServiceOptionsData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto trackingServiceOptionsData2 = std::reinterpret_pointer_cast<TrackingServiceOptionsData>( ReadDataFrom( source ) );
    bool equal = trackingServiceOptionsData2->IsEqualTo( *trackingServiceOptionsData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TrackLinkDataSerializationTest
BOOST_AUTO_TEST_CASE( TrackLinkDataSerializationTest )
{
    auto trackLinkData1 = std::make_shared<TrackLinkData>( );
    trackLinkData1->SetId( Guid( L"{2FB7B770-A73D-F8B1-1F8D-E5BCF4EDED0E}" ) );
    trackLinkData1->SetRowVersion( -526455800190224528LL );
    trackLinkData1->SetPrimary( Guid( L"{2FB7B770-A73D-F8B1-1F8D-E5BCF4EDED0E}" ) );
    trackLinkData1->SetSecondary( Guid( L"{2FB7B770-A73D-F8B1-1F8D-E5BCF4EDED0E}" ) );
    trackLinkData1->SetStart( DateTime( 1, 1, 1, 14, 37, 6 ) );
    trackLinkData1->SetEnd( DateTime( 1, 1, 1, 14, 37, 6 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *trackLinkData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto trackLinkData2 = std::reinterpret_pointer_cast<TrackLinkData>( ReadDataFrom( source ) );
    bool equal = trackLinkData2->IsEqualTo( *trackLinkData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TrackValueDataSerializationTest
BOOST_AUTO_TEST_CASE( TrackValueDataSerializationTest )
{
    auto trackValueData1 = std::make_shared<TrackValueData>( );
    trackValueData1->SetId( Guid( L"{314730E2-D36D-A435-25AC-CBB68CE20C47}" ) );
    trackValueData1->SetRowVersion( -6614148011792060190LL );
    trackValueData1->SetTrack( Guid( L"{314730E2-D36D-A435-25AC-CBB68CE20C47}" ) );
    trackValueData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    trackValueData1->SetFlags( TrackFlags::Course );
    trackValueData1->SetStatus( TrackStatus::RestrictedManeuverability );
    trackValueData1->SetLatitude( 11832596061917492 );
    trackValueData1->SetLongitude( 11832596061917492 );
    trackValueData1->SetSpeed( 11832596061917492 );
    trackValueData1->SetCourse( 11832596061917492 );
    trackValueData1->SetHeading( 11832596061917492 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *trackValueData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto trackValueData2 = std::reinterpret_pointer_cast<TrackValueData>( ReadDataFrom( source ) );
    bool equal = trackValueData2->IsEqualTo( *trackValueData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/TrackValue3DDataSerializationTest
BOOST_AUTO_TEST_CASE( TrackValue3DDataSerializationTest )
{
    auto trackValue3DData1 = std::make_shared<TrackValue3DData>( );
    trackValue3DData1->SetId( Guid( L"{8B49E8E0-2358-68D7-16EB-C41AD1921707}" ) );
    trackValue3DData1->SetRowVersion( 7554545763138267360LL );
    trackValue3DData1->SetTrack( Guid( L"{8B49E8E0-2358-68D7-16EB-C41AD1921707}" ) );
    trackValue3DData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    trackValue3DData1->SetFlags( TrackFlags3D::None );
    trackValue3DData1->SetStatus( 2336876768UL );
    trackValue3DData1->SetLatitude( 7554545763138267 );
    trackValue3DData1->SetLongitude( 7554545763138267 );
    trackValue3DData1->SetAltitude( 7554545763138267 );
    trackValue3DData1->SetSpeed( 7554545763138267 );
    trackValue3DData1->SetCourse( 7554545763138267 );
    trackValue3DData1->SetRateOfClimb( 7554545763138267 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *trackValue3DData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto trackValue3DData2 = std::reinterpret_pointer_cast<TrackValue3DData>( ReadDataFrom( source ) );
    bool equal = trackValue3DData2->IsEqualTo( *trackValue3DData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt16TimeseriesValueDataSerializationTest
BOOST_AUTO_TEST_CASE( UInt16TimeseriesValueDataSerializationTest )
{
    auto uInt16TimeseriesValueData1 = std::make_shared<UInt16TimeseriesValueData>( );
    uInt16TimeseriesValueData1->SetId( Guid( L"{6136B482-E2B0-C76B-E3D6-470D866C2D41}" ) );
    uInt16TimeseriesValueData1->SetRowVersion( -4076915790480755582LL );
    uInt16TimeseriesValueData1->SetTimeseries( Guid( L"{6136B482-E2B0-C76B-E3D6-470D866C2D41}" ) );
    uInt16TimeseriesValueData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    uInt16TimeseriesValueData1->SetValue( 46210 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt16TimeseriesValueData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt16TimeseriesValueData2 = std::reinterpret_pointer_cast<UInt16TimeseriesValueData>( ReadDataFrom( source ) );
    bool equal = uInt16TimeseriesValueData2->IsEqualTo( *uInt16TimeseriesValueData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt32TimeseriesValueDataSerializationTest
BOOST_AUTO_TEST_CASE( UInt32TimeseriesValueDataSerializationTest )
{
    auto uInt32TimeseriesValueData1 = std::make_shared<UInt32TimeseriesValueData>( );
    uInt32TimeseriesValueData1->SetId( Guid( L"{485A0A48-CCBD-4975-92AE-33BD125A5012}" ) );
    uInt32TimeseriesValueData1->SetRowVersion( 5293362050378631752LL );
    uInt32TimeseriesValueData1->SetTimeseries( Guid( L"{485A0A48-CCBD-4975-92AE-33BD125A5012}" ) );
    uInt32TimeseriesValueData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    uInt32TimeseriesValueData1->SetValue( 1213860424UL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt32TimeseriesValueData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt32TimeseriesValueData2 = std::reinterpret_pointer_cast<UInt32TimeseriesValueData>( ReadDataFrom( source ) );
    bool equal = uInt32TimeseriesValueData2->IsEqualTo( *uInt32TimeseriesValueData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/UInt64TimeseriesValueDataSerializationTest
BOOST_AUTO_TEST_CASE( UInt64TimeseriesValueDataSerializationTest )
{
    auto uInt64TimeseriesValueData1 = std::make_shared<UInt64TimeseriesValueData>( );
    uInt64TimeseriesValueData1->SetId( Guid( L"{2B846AF0-4E92-0F11-F088-7249D421560F}" ) );
    uInt64TimeseriesValueData1->SetRowVersion( 1085735374875290352LL );
    uInt64TimeseriesValueData1->SetTimeseries( Guid( L"{2B846AF0-4E92-0F11-F088-7249D421560F}" ) );
    uInt64TimeseriesValueData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    uInt64TimeseriesValueData1->SetValue( 1085735374875290352LL );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *uInt64TimeseriesValueData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto uInt64TimeseriesValueData2 = std::reinterpret_pointer_cast<UInt64TimeseriesValueData>( ReadDataFrom( source ) );
    bool equal = uInt64TimeseriesValueData2->IsEqualTo( *uInt64TimeseriesValueData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/VehicleTypeDataSerializationTest
BOOST_AUTO_TEST_CASE( VehicleTypeDataSerializationTest )
{
    auto vehicleTypeData1 = std::make_shared<VehicleTypeData>( );
    vehicleTypeData1->SetId( Guid( L"{782DCD85-3771-1ED2-784B-EC8E1EB4B3A1}" ) );
    vehicleTypeData1->SetRowVersion( 2220898526734175621LL );
    vehicleTypeData1->SetName( L"Name" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *vehicleTypeData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto vehicleTypeData2 = std::reinterpret_pointer_cast<VehicleTypeData>( ReadDataFrom( source ) );
    bool equal = vehicleTypeData2->IsEqualTo( *vehicleTypeData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/VesselTypeDataSerializationTest
BOOST_AUTO_TEST_CASE( VesselTypeDataSerializationTest )
{
    auto vesselTypeData1 = std::make_shared<VesselTypeData>( );
    vesselTypeData1->SetId( Guid( L"{D5182F76-234A-4853-12CA-C452AB18F46E}" ) );
    vesselTypeData1->SetRowVersion( 5211547998107479926LL );
    vesselTypeData1->SetName( L"Name" );
    vesselTypeData1->SetCode( -719835274L );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *vesselTypeData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto vesselTypeData2 = std::reinterpret_pointer_cast<VesselTypeData>( ReadDataFrom( source ) );
    bool equal = vesselTypeData2->IsEqualTo( *vesselTypeData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ViewDataSerializationTest
BOOST_AUTO_TEST_CASE( ViewDataSerializationTest )
{
    auto viewData1 = std::make_shared<ViewData>( );
    viewData1->SetId( Guid( L"{2019E5C1-3542-B628-6D14-AC420498A783}" ) );
    viewData1->SetRowVersion( -5320944401615559231LL );
    viewData1->SetName( L"Name" );
    viewData1->SetLatitudeTimeseries( Guid( L"{2019E5C1-3542-B628-6D14-AC420498A783}" ) );
    viewData1->SetLongitudeTimeseries( Guid( L"{2019E5C1-3542-B628-6D14-AC420498A783}" ) );
    viewData1->SetZoomLevelTimeseries( Guid( L"{2019E5C1-3542-B628-6D14-AC420498A783}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *viewData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto viewData2 = std::reinterpret_pointer_cast<ViewData>( ReadDataFrom( source ) );
    bool equal = viewData2->IsEqualTo( *viewData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ViewCameraLinkDataSerializationTest
BOOST_AUTO_TEST_CASE( ViewCameraLinkDataSerializationTest )
{
    auto viewCameraLinkData1 = std::make_shared<ViewCameraLinkData>( );
    viewCameraLinkData1->SetId( Guid( L"{9F75C5E8-84D0-8E5E-717A-210BF9AEA317}" ) );
    viewCameraLinkData1->SetRowVersion( -8187961040949623320LL );
    viewCameraLinkData1->SetView( Guid( L"{9F75C5E8-84D0-8E5E-717A-210BF9AEA317}" ) );
    viewCameraLinkData1->SetCamera( Guid( L"{9F75C5E8-84D0-8E5E-717A-210BF9AEA317}" ) );
    viewCameraLinkData1->SetStart( DateTime( 1, 1, 1, 14, 37, 6 ) );
    viewCameraLinkData1->SetEnd( DateTime( 1, 1, 1, 14, 37, 6 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *viewCameraLinkData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto viewCameraLinkData2 = std::reinterpret_pointer_cast<ViewCameraLinkData>( ReadDataFrom( source ) );
    bool equal = viewCameraLinkData2->IsEqualTo( *viewCameraLinkData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ViewTrackerLinkDataSerializationTest
BOOST_AUTO_TEST_CASE( ViewTrackerLinkDataSerializationTest )
{
    auto viewTrackerLinkData1 = std::make_shared<ViewTrackerLinkData>( );
    viewTrackerLinkData1->SetId( Guid( L"{4326A801-681C-3499-2C99-1638C2641580}" ) );
    viewTrackerLinkData1->SetRowVersion( 3790175032003962881LL );
    viewTrackerLinkData1->SetView( Guid( L"{4326A801-681C-3499-2C99-1638C2641580}" ) );
    viewTrackerLinkData1->SetTracker( Guid( L"{4326A801-681C-3499-2C99-1638C2641580}" ) );
    viewTrackerLinkData1->SetStart( DateTime( 1, 1, 1, 14, 37, 6 ) );
    viewTrackerLinkData1->SetEnd( DateTime( 1, 1, 1, 14, 37, 6 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *viewTrackerLinkData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto viewTrackerLinkData2 = std::reinterpret_pointer_cast<ViewTrackerLinkData>( ReadDataFrom( source ) );
    bool equal = viewTrackerLinkData2->IsEqualTo( *viewTrackerLinkData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/WeatherStationCommandDataSerializationTest
BOOST_AUTO_TEST_CASE( WeatherStationCommandDataSerializationTest )
{
    auto weatherStationCommandData1 = std::make_shared<WeatherStationCommandData>( );
    weatherStationCommandData1->SetId( Guid( L"{15A71ED0-61D0-1B4B-D8D2-860BA8E5780B}" ) );
    weatherStationCommandData1->SetRowVersion( 1966773208621719248LL );
    weatherStationCommandData1->SetWeatherStation( Guid( L"{15A71ED0-61D0-1B4B-D8D2-860BA8E5780B}" ) );
    weatherStationCommandData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    weatherStationCommandData1->SetDeviceCommandSourceType( DeviceCommandSourceType::Unknown );
    weatherStationCommandData1->SetDeviceCommandSourceId( Guid( L"{15A71ED0-61D0-1B4B-D8D2-860BA8E5780B}" ) );
    weatherStationCommandData1->SetReply( Guid( L"{15A71ED0-61D0-1B4B-D8D2-860BA8E5780B}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *weatherStationCommandData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto weatherStationCommandData2 = std::reinterpret_pointer_cast<WeatherStationCommandData>( ReadDataFrom( source ) );
    bool equal = weatherStationCommandData2->IsEqualTo( *weatherStationCommandData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/WeatherStationCommandReplyDataSerializationTest
BOOST_AUTO_TEST_CASE( WeatherStationCommandReplyDataSerializationTest )
{
    auto weatherStationCommandReplyData1 = std::make_shared<WeatherStationCommandReplyData>( );
    weatherStationCommandReplyData1->SetId( Guid( L"{EB8BB859-93A7-CFCE-F373-C9E5D7D11D9A}" ) );
    weatherStationCommandReplyData1->SetRowVersion( -3472675913235449767LL );
    weatherStationCommandReplyData1->SetWeatherStation( Guid( L"{EB8BB859-93A7-CFCE-F373-C9E5D7D11D9A}" ) );
    weatherStationCommandReplyData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    weatherStationCommandReplyData1->SetCommand( Guid( L"{EB8BB859-93A7-CFCE-F373-C9E5D7D11D9A}" ) );
    weatherStationCommandReplyData1->SetStatus( DeviceCommandReplyStatus::Ok );
    weatherStationCommandReplyData1->SetMessage( L"Message" );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *weatherStationCommandReplyData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto weatherStationCommandReplyData2 = std::reinterpret_pointer_cast<WeatherStationCommandReplyData>( ReadDataFrom( source ) );
    bool equal = weatherStationCommandReplyData2->IsEqualTo( *weatherStationCommandReplyData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/WeatherStationConfigurationDataSerializationTest
BOOST_AUTO_TEST_CASE( WeatherStationConfigurationDataSerializationTest )
{
    auto weatherStationConfigurationData1 = std::make_shared<WeatherStationConfigurationData>( );
    weatherStationConfigurationData1->SetId( Guid( L"{48131464-C2BB-F6DD-6FBB-43DD12C82826}" ) );
    weatherStationConfigurationData1->SetRowVersion( -658155860902341532LL );
    weatherStationConfigurationData1->SetWeatherStation( Guid( L"{48131464-C2BB-F6DD-6FBB-43DD12C82826}" ) );
    weatherStationConfigurationData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    weatherStationConfigurationData1->SetNoDataTimeOut( TimeSpan( -404902341532LL ) );
    weatherStationConfigurationData1->SetSendInterval( TimeSpan( -404902341532LL ) );
    weatherStationConfigurationData1->SetLatitude( 17788588212807212 );
    weatherStationConfigurationData1->SetLongitude( 17788588212807212 );
    weatherStationConfigurationData1->SetGyroOffset( 17788588212807212 );
    weatherStationConfigurationData1->SetEnableAveraging( false );
    weatherStationConfigurationData1->SetAveragingInterval( TimeSpan( -404902341532LL ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *weatherStationConfigurationData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto weatherStationConfigurationData2 = std::reinterpret_pointer_cast<WeatherStationConfigurationData>( ReadDataFrom( source ) );
    bool equal = weatherStationConfigurationData2->IsEqualTo( *weatherStationConfigurationData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/CircularZoneDataSerializationTest
BOOST_AUTO_TEST_CASE( CircularZoneDataSerializationTest )
{
    auto circularZoneData1 = std::make_shared<CircularZoneData>( );
    circularZoneData1->SetId( Guid( L"{D8FE5507-6CC5-1F7F-F8FE-36A31B7FAAE0}" ) );
    circularZoneData1->SetRowVersion( 2269652334222923015LL );
    circularZoneData1->SetName( L"Name" );
    circularZoneData1->SetLongitude( 2269652334222923 );
    circularZoneData1->SetLatitude( 2269652334222923 );
    circularZoneData1->SetAlarmType( ZoneAlarmType::None );
    circularZoneData1->SetAlarmTime( TimeSpan( 366222923015LL ) );
    circularZoneData1->SetRadarTrackMinimumLifetime( TimeSpan( 366222923015LL ) );
    circularZoneData1->SetSpeed( 2269652334222923 );
    circularZoneData1->SetStrokeColor( 3640546567UL );
    circularZoneData1->SetFillColor( 3640546567UL );
    circularZoneData1->SetRadius( 2269652334222923 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *circularZoneData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto circularZoneData2 = std::reinterpret_pointer_cast<CircularZoneData>( ReadDataFrom( source ) );
    bool equal = circularZoneData2->IsEqualTo( *circularZoneData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/PolygonZoneDataSerializationTest
BOOST_AUTO_TEST_CASE( PolygonZoneDataSerializationTest )
{
    auto polygonZoneData1 = std::make_shared<PolygonZoneData>( );
    polygonZoneData1->SetId( Guid( L"{3554124C-5386-5304-CA20-CA61AC2A4832}" ) );
    polygonZoneData1->SetRowVersion( 5981998040940286540LL );
    polygonZoneData1->SetName( L"Name" );
    polygonZoneData1->SetLongitude( 5981998040940287 );
    polygonZoneData1->SetLatitude( 5981998040940287 );
    polygonZoneData1->SetAlarmType( ZoneAlarmType::None );
    polygonZoneData1->SetAlarmTime( TimeSpan( 728940286540LL ) );
    polygonZoneData1->SetRadarTrackMinimumLifetime( TimeSpan( 728940286540LL ) );
    polygonZoneData1->SetSpeed( 5981998040940287 );
    polygonZoneData1->SetStrokeColor( 894702156UL );
    polygonZoneData1->SetFillColor( 894702156UL );
    polygonZoneData1->SetPolygon( { {'P','o','l','y','g','o','n'} } );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *polygonZoneData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto polygonZoneData2 = std::reinterpret_pointer_cast<PolygonZoneData>( ReadDataFrom( source ) );
    bool equal = polygonZoneData2->IsEqualTo( *polygonZoneData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ZoneExceptionsDataSerializationTest
BOOST_AUTO_TEST_CASE( ZoneExceptionsDataSerializationTest )
{
    auto zoneExceptionsData1 = std::make_shared<ZoneExceptionsData>( );
    zoneExceptionsData1->SetId( Guid( L"{B1060A97-736B-DDAC-BB35-CED68D6050E9}" ) );
    zoneExceptionsData1->SetRowVersion( -2473475188964586857LL );
    zoneExceptionsData1->SetZone( Guid( L"{B1060A97-736B-DDAC-BB35-CED68D6050E9}" ) );
    zoneExceptionsData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *zoneExceptionsData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto zoneExceptionsData2 = std::reinterpret_pointer_cast<ZoneExceptionsData>( ReadDataFrom( source ) );
    bool equal = zoneExceptionsData2->IsEqualTo( *zoneExceptionsData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ZoneExceptionsVesselLinkDataSerializationTest
BOOST_AUTO_TEST_CASE( ZoneExceptionsVesselLinkDataSerializationTest )
{
    auto zoneExceptionsVesselLinkData1 = std::make_shared<ZoneExceptionsVesselLinkData>( );
    zoneExceptionsVesselLinkData1->SetId( Guid( L"{88FC45CD-DF1D-6687-66E1-FBB8113FA2B3}" ) );
    zoneExceptionsVesselLinkData1->SetRowVersion( 7388119031669867981LL );
    zoneExceptionsVesselLinkData1->SetZoneExceptions( Guid( L"{88FC45CD-DF1D-6687-66E1-FBB8113FA2B3}" ) );
    zoneExceptionsVesselLinkData1->SetVessel( Guid( L"{88FC45CD-DF1D-6687-66E1-FBB8113FA2B3}" ) );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *zoneExceptionsVesselLinkData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto zoneExceptionsVesselLinkData2 = std::reinterpret_pointer_cast<ZoneExceptionsVesselLinkData>( ReadDataFrom( source ) );
    bool equal = zoneExceptionsVesselLinkData2->IsEqualTo( *zoneExceptionsVesselLinkData1 );
    BOOST_CHECK( equal );
}

// --run_test=DataTypesTests/ZoneTrackAlarmDataSerializationTest
BOOST_AUTO_TEST_CASE( ZoneTrackAlarmDataSerializationTest )
{
    auto zoneTrackAlarmData1 = std::make_shared<ZoneTrackAlarmData>( );
    zoneTrackAlarmData1->SetId( Guid( L"{0F40BC2F-963C-F3B4-CF2D-693CF0023DF4}" ) );
    zoneTrackAlarmData1->SetRowVersion( -885918041987040209LL );
    zoneTrackAlarmData1->SetTrack( Guid( L"{0F40BC2F-963C-F3B4-CF2D-693CF0023DF4}" ) );
    zoneTrackAlarmData1->SetZone( Guid( L"{0F40BC2F-963C-F3B4-CF2D-693CF0023DF4}" ) );
    zoneTrackAlarmData1->SetRadarTrack( Guid( L"{0F40BC2F-963C-F3B4-CF2D-693CF0023DF4}" ) );
    zoneTrackAlarmData1->SetTimestamp( DateTime( 1, 1, 1, 14, 37, 6 ) );
    zoneTrackAlarmData1->SetLatitude( 17560826031722512 );
    zoneTrackAlarmData1->SetLongitude( 17560826031722512 );
    zoneTrackAlarmData1->SetSpeed( 17560826031722512 );
    zoneTrackAlarmData1->SetCourse( 17560826031722512 );
    zoneTrackAlarmData1->SetHeading( 17560826031722512 );
    zoneTrackAlarmData1->SetEnterLatitude( 17560826031722512 );
    zoneTrackAlarmData1->SetEnterLongitude( 17560826031722512 );
    zoneTrackAlarmData1->SetLeaveLatitude( 17560826031722512 );
    zoneTrackAlarmData1->SetLeaveLongitude( 17560826031722512 );

    IO::MemoryStream stream;
    IO::BinaryWriter destination( stream );
    WriteDataTo( *zoneTrackAlarmData1, destination );
    stream.SetPosition( 0 );
    IO::BinaryReader source( stream );

    auto zoneTrackAlarmData2 = std::reinterpret_pointer_cast<ZoneTrackAlarmData>( ReadDataFrom( source ) );
    bool equal = zoneTrackAlarmData2->IsEqualTo( *zoneTrackAlarmData1 );
    BOOST_CHECK( equal );
}

BOOST_AUTO_TEST_SUITE_END( )
