#pragma once
#ifndef TYPES_IDATACONTEXT_H_
#define TYPES_IDATACONTEXT_H_

#include "DataTypes.h"

namespace Barrelman::Types
{

    class UpdateData
    {
    };

    class UpdateResult
    {
    };

    class IDataContext
    {

        virtual bool Insert( BaseData<Kind, Guid>& data ) = 0;
        virtual bool Update( BaseData<Kind, Guid>& data ) = 0;
        virtual bool Delete( const BaseData<Kind, Guid>& data ) = 0;
        virtual bool Merge( BaseData<Kind, Guid>& data ) = 0;

        virtual bool Update( const UpdateData& data, UpdateResult& result ) = 0;

        // ---------------------------------------------------------------------
        // AircraftType queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AircraftTypeObject> GetAircraftTypeById( const Guid& id ) = 0;
        virtual void GetAircraftTypeCollection( std::vector<std::shared_ptr<AircraftTypeObject>>& result ) = 0;
        virtual std::shared_ptr<AircraftTypeObject> GetAircraftTypeByName( const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // AisDeviceCommand queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisDeviceCommandObject> GetAisDeviceCommandById( const Guid& id ) = 0;
        virtual void GetAisDeviceCommandCollection( std::vector<std::shared_ptr<AisDeviceCommandObject>>& result ) = 0;
        virtual void GetAisDeviceCommandCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisDeviceCommandObject>>& result ) = 0;
        virtual void GetAisDeviceCommandCollectionByAisDeviceAndTimestamp( const Guid& aisDevice, const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceCommandObject>>& result ) = 0;
        virtual void GetAisDeviceCommandCollectionByAisDeviceAtTimestamp( const Guid& aisDevice, const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceCommandObject>>& result ) = 0;
        virtual void GetAisDeviceCommandCollectionByAisDeviceFromTimestamp( const Guid& aisDevice, const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceCommandObject>>& result ) = 0;
        virtual void GetAisDeviceCommandCollectionByAisDeviceUntilTimestamp( const Guid& aisDevice, const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceCommandObject>>& result ) = 0;
        virtual void GetAisDeviceCommandCollectionByAisDeviceOverTimestamp( Guid aisDevice, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<AisDeviceCommandObject>>& result ) = 0;
        virtual void GetAisDeviceCommandCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceCommandObject>>& result ) = 0;
        virtual void GetAisDeviceCommandCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceCommandObject>>& result ) = 0;
        virtual void GetAisDeviceCommandCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceCommandObject>>& result ) = 0;
        virtual void GetAisDeviceCommandCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceCommandObject>>& result ) = 0;
        virtual void GetAisDeviceCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<AisDeviceCommandObject>>& result ) = 0;
        virtual void GetAisDeviceCommandCollectionByReply( const DBGuid& reply, std::vector<std::shared_ptr<AisDeviceCommandObject>>& result ) = 0;
        virtual void GetAisDeviceCommandCollectionByReplyIsNull( std::vector<std::shared_ptr<AisDeviceCommandObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisDeviceCommandReply queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisDeviceCommandReplyObject> GetAisDeviceCommandReplyById( const Guid& id ) = 0;
        virtual void GetAisDeviceCommandReplyCollection( std::vector<std::shared_ptr<AisDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetAisDeviceCommandReplyCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetAisDeviceCommandReplyCollectionByAisDeviceAndTimestamp( const Guid& aisDevice, const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetAisDeviceCommandReplyCollectionByAisDeviceAtTimestamp( const Guid& aisDevice, const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetAisDeviceCommandReplyCollectionByAisDeviceFromTimestamp( const Guid& aisDevice, const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetAisDeviceCommandReplyCollectionByAisDeviceUntilTimestamp( const Guid& aisDevice, const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetAisDeviceCommandReplyCollectionByAisDeviceOverTimestamp( Guid aisDevice, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<AisDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetAisDeviceCommandReplyCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetAisDeviceCommandReplyCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetAisDeviceCommandReplyCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetAisDeviceCommandReplyCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetAisDeviceCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<AisDeviceCommandReplyObject>>& result ) = 0;
        virtual std::shared_ptr<AisDeviceCommandReplyObject> GetAisDeviceCommandReplyByCommand( const DBGuid& command ) = 0;
        virtual void GetAisDeviceCommandReplyCollectionByCommandIsNull( std::vector<std::shared_ptr<AisDeviceCommandReplyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisDeviceConfiguration queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisDeviceConfigurationObject> GetAisDeviceConfigurationById( const Guid& id ) = 0;
        virtual void GetAisDeviceConfigurationCollection( std::vector<std::shared_ptr<AisDeviceConfigurationObject>>& result ) = 0;
        virtual void GetAisDeviceConfigurationCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisDeviceConfigurationObject>>& result ) = 0;
        virtual std::shared_ptr<AisDeviceConfigurationObject> GetAisDeviceConfigurationByAisDeviceAndTimestamp( const Guid& aisDevice, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<AisDeviceConfigurationObject> GetAisDeviceConfigurationByAisDeviceAtTimestamp( const Guid& aisDevice, const DateTime& timestamp ) = 0;
        virtual void GetAisDeviceConfigurationByAisDeviceFromTimestamp( const Guid& aisDevice, const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceConfigurationObject>>& result ) = 0;
        virtual void GetAisDeviceConfigurationByAisDeviceUntilTimestamp( const Guid& aisDevice, const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceConfigurationObject>>& result ) = 0;
        virtual void GetAisDeviceConfigurationByAisDeviceOverTimestamp( Guid aisDevice, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<AisDeviceConfigurationObject>>& result ) = 0;
        virtual void GetAisDeviceConfigurationCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceConfigurationObject>>& result ) = 0;
        virtual void GetAisDeviceConfigurationCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceConfigurationObject>>& result ) = 0;
        virtual void GetAisDeviceConfigurationCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceConfigurationObject>>& result ) = 0;
        virtual void GetAisDeviceConfigurationCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceConfigurationObject>>& result ) = 0;
        virtual void GetAisDeviceConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<AisDeviceConfigurationObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisDeviceRawMessage queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisDeviceRawMessageObject> GetAisDeviceRawMessageById( const Guid& id ) = 0;
        virtual void GetAisDeviceRawMessageCollection( std::vector<std::shared_ptr<AisDeviceRawMessageObject>>& result ) = 0;
        virtual void GetAisDeviceRawMessageCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisDeviceRawMessageObject>>& result ) = 0;
        virtual void GetAisDeviceRawMessageCollectionByAisDeviceAndTimestamp( const Guid& aisDevice, const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceRawMessageObject>>& result ) = 0;
        virtual void GetAisDeviceRawMessageCollectionByAisDeviceAtTimestamp( const Guid& aisDevice, const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceRawMessageObject>>& result ) = 0;
        virtual void GetAisDeviceRawMessageCollectionByAisDeviceFromTimestamp( const Guid& aisDevice, const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceRawMessageObject>>& result ) = 0;
        virtual void GetAisDeviceRawMessageCollectionByAisDeviceUntilTimestamp( const Guid& aisDevice, const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceRawMessageObject>>& result ) = 0;
        virtual void GetAisDeviceRawMessageCollectionByAisDeviceOverTimestamp( Guid aisDevice, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<AisDeviceRawMessageObject>>& result ) = 0;
        virtual void GetAisDeviceRawMessageCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceRawMessageObject>>& result ) = 0;
        virtual void GetAisDeviceRawMessageCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceRawMessageObject>>& result ) = 0;
        virtual void GetAisDeviceRawMessageCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceRawMessageObject>>& result ) = 0;
        virtual void GetAisDeviceRawMessageCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceRawMessageObject>>& result ) = 0;
        virtual void GetAisDeviceRawMessageCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<AisDeviceRawMessageObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisDeviceRawSentence queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisDeviceRawSentenceObject> GetAisDeviceRawSentenceById( const Guid& id ) = 0;
        virtual void GetAisDeviceRawSentenceCollection( std::vector<std::shared_ptr<AisDeviceRawSentenceObject>>& result ) = 0;
        virtual void GetAisDeviceRawSentenceCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisDeviceRawSentenceObject>>& result ) = 0;
        virtual void GetAisDeviceRawSentenceCollectionByAisDeviceAndTimestamp( const Guid& aisDevice, const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceRawSentenceObject>>& result ) = 0;
        virtual void GetAisDeviceRawSentenceCollectionByAisDeviceAtTimestamp( const Guid& aisDevice, const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceRawSentenceObject>>& result ) = 0;
        virtual void GetAisDeviceRawSentenceCollectionByAisDeviceFromTimestamp( const Guid& aisDevice, const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceRawSentenceObject>>& result ) = 0;
        virtual void GetAisDeviceRawSentenceCollectionByAisDeviceUntilTimestamp( const Guid& aisDevice, const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceRawSentenceObject>>& result ) = 0;
        virtual void GetAisDeviceRawSentenceCollectionByAisDeviceOverTimestamp( Guid aisDevice, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<AisDeviceRawSentenceObject>>& result ) = 0;
        virtual void GetAisDeviceRawSentenceCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceRawSentenceObject>>& result ) = 0;
        virtual void GetAisDeviceRawSentenceCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceRawSentenceObject>>& result ) = 0;
        virtual void GetAisDeviceRawSentenceCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceRawSentenceObject>>& result ) = 0;
        virtual void GetAisDeviceRawSentenceCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<AisDeviceRawSentenceObject>>& result ) = 0;
        virtual void GetAisDeviceRawSentenceCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<AisDeviceRawSentenceObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisMessage queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisMessageObject> GetAisMessageById( const Guid& id ) = 0;
        virtual void GetAisMessageCollection( std::vector<std::shared_ptr<AisMessageObject>>& result ) = 0;
        virtual void GetAisMessageCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisMessageObject>>& result ) = 0;
        virtual std::shared_ptr<AisMessageObject> GetAisMessageByAisDeviceAndReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual std::shared_ptr<AisMessageObject> GetAisMessageByAisDeviceAtReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual void GetAisMessageByAisDeviceFromReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisMessageObject>>& result ) = 0;
        virtual void GetAisMessageByAisDeviceUntilReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisMessageObject>>& result ) = 0;
        virtual void GetAisMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisMessageObject>>& result ) = 0;
        virtual void GetAisMessageCollectionByReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisMessageObject>>& result ) = 0;
        virtual void GetAisMessageCollectionAtReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisMessageObject>>& result ) = 0;
        virtual void GetAisMessageCollectionFromReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisMessageObject>>& result ) = 0;
        virtual void GetAisMessageCollectionUntilReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisMessageObject>>& result ) = 0;
        virtual void GetAisMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisMessageObject>>& result ) = 0;
        virtual void GetAisMessageCollectionByMmsi( const DBGuid& mmsi, std::vector<std::shared_ptr<AisMessageObject>>& result ) = 0;
        virtual void GetAisMessageCollectionByMmsiIsNull( std::vector<std::shared_ptr<AisMessageObject>>& result ) = 0;
        virtual void GetAisMessageCollectionByMmsiAndMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisMessageObject>>& result ) = 0;
        virtual void GetAisMessageCollectionByMmsiIsNullAndMessageSequenceNumber( Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisMessageObject>>& result ) = 0;
        virtual void GetAisMessageCollectionByMmsiFromMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisMessageObject>>& result ) = 0;
        virtual void GetAisMessageCollectionByMmsiUntilMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisMessageObject>>& result ) = 0;
        virtual void GetAisMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, Int64 fromMessageSequenceNumber, Int64 untilMessageSequenceNumber, std::vector<std::shared_ptr<AisMessageObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AidToNavigationReportMessage queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AidToNavigationReportMessageObject> GetAidToNavigationReportMessageById( const Guid& id ) = 0;
        virtual void GetAidToNavigationReportMessageCollection( std::vector<std::shared_ptr<AidToNavigationReportMessageObject>>& result ) = 0;
        virtual void GetAidToNavigationReportMessageCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AidToNavigationReportMessageObject>>& result ) = 0;
        virtual std::shared_ptr<AidToNavigationReportMessageObject> GetAidToNavigationReportMessageByAisDeviceAndReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual std::shared_ptr<AidToNavigationReportMessageObject> GetAidToNavigationReportMessageByAisDeviceAtReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual void GetAidToNavigationReportMessageByAisDeviceFromReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AidToNavigationReportMessageObject>>& result ) = 0;
        virtual void GetAidToNavigationReportMessageByAisDeviceUntilReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AidToNavigationReportMessageObject>>& result ) = 0;
        virtual void GetAidToNavigationReportMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AidToNavigationReportMessageObject>>& result ) = 0;
        virtual void GetAidToNavigationReportMessageCollectionByReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AidToNavigationReportMessageObject>>& result ) = 0;
        virtual void GetAidToNavigationReportMessageCollectionAtReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AidToNavigationReportMessageObject>>& result ) = 0;
        virtual void GetAidToNavigationReportMessageCollectionFromReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AidToNavigationReportMessageObject>>& result ) = 0;
        virtual void GetAidToNavigationReportMessageCollectionUntilReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AidToNavigationReportMessageObject>>& result ) = 0;
        virtual void GetAidToNavigationReportMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AidToNavigationReportMessageObject>>& result ) = 0;
        virtual void GetAidToNavigationReportMessageCollectionByMmsi( const DBGuid& mmsi, std::vector<std::shared_ptr<AidToNavigationReportMessageObject>>& result ) = 0;
        virtual void GetAidToNavigationReportMessageCollectionByMmsiIsNull( std::vector<std::shared_ptr<AidToNavigationReportMessageObject>>& result ) = 0;
        virtual void GetAidToNavigationReportMessageCollectionByMmsiAndMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AidToNavigationReportMessageObject>>& result ) = 0;
        virtual void GetAidToNavigationReportMessageCollectionByMmsiIsNullAndMessageSequenceNumber( Int64 messageSequenceNumber, std::vector<std::shared_ptr<AidToNavigationReportMessageObject>>& result ) = 0;
        virtual void GetAidToNavigationReportMessageCollectionByMmsiFromMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AidToNavigationReportMessageObject>>& result ) = 0;
        virtual void GetAidToNavigationReportMessageCollectionByMmsiUntilMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AidToNavigationReportMessageObject>>& result ) = 0;
        virtual void GetAidToNavigationReportMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, Int64 fromMessageSequenceNumber, Int64 untilMessageSequenceNumber, std::vector<std::shared_ptr<AidToNavigationReportMessageObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisAddressedSafetyRelatedMessage queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisAddressedSafetyRelatedMessageObject> GetAisAddressedSafetyRelatedMessageById( const Guid& id ) = 0;
        virtual void GetAisAddressedSafetyRelatedMessageCollection( std::vector<std::shared_ptr<AisAddressedSafetyRelatedMessageObject>>& result ) = 0;
        virtual void GetAisAddressedSafetyRelatedMessageCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisAddressedSafetyRelatedMessageObject>>& result ) = 0;
        virtual std::shared_ptr<AisAddressedSafetyRelatedMessageObject> GetAisAddressedSafetyRelatedMessageByAisDeviceAndReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual std::shared_ptr<AisAddressedSafetyRelatedMessageObject> GetAisAddressedSafetyRelatedMessageByAisDeviceAtReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual void GetAisAddressedSafetyRelatedMessageByAisDeviceFromReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisAddressedSafetyRelatedMessageObject>>& result ) = 0;
        virtual void GetAisAddressedSafetyRelatedMessageByAisDeviceUntilReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisAddressedSafetyRelatedMessageObject>>& result ) = 0;
        virtual void GetAisAddressedSafetyRelatedMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisAddressedSafetyRelatedMessageObject>>& result ) = 0;
        virtual void GetAisAddressedSafetyRelatedMessageCollectionByReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisAddressedSafetyRelatedMessageObject>>& result ) = 0;
        virtual void GetAisAddressedSafetyRelatedMessageCollectionAtReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisAddressedSafetyRelatedMessageObject>>& result ) = 0;
        virtual void GetAisAddressedSafetyRelatedMessageCollectionFromReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisAddressedSafetyRelatedMessageObject>>& result ) = 0;
        virtual void GetAisAddressedSafetyRelatedMessageCollectionUntilReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisAddressedSafetyRelatedMessageObject>>& result ) = 0;
        virtual void GetAisAddressedSafetyRelatedMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisAddressedSafetyRelatedMessageObject>>& result ) = 0;
        virtual void GetAisAddressedSafetyRelatedMessageCollectionByMmsi( const DBGuid& mmsi, std::vector<std::shared_ptr<AisAddressedSafetyRelatedMessageObject>>& result ) = 0;
        virtual void GetAisAddressedSafetyRelatedMessageCollectionByMmsiIsNull( std::vector<std::shared_ptr<AisAddressedSafetyRelatedMessageObject>>& result ) = 0;
        virtual void GetAisAddressedSafetyRelatedMessageCollectionByMmsiAndMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisAddressedSafetyRelatedMessageObject>>& result ) = 0;
        virtual void GetAisAddressedSafetyRelatedMessageCollectionByMmsiIsNullAndMessageSequenceNumber( Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisAddressedSafetyRelatedMessageObject>>& result ) = 0;
        virtual void GetAisAddressedSafetyRelatedMessageCollectionByMmsiFromMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisAddressedSafetyRelatedMessageObject>>& result ) = 0;
        virtual void GetAisAddressedSafetyRelatedMessageCollectionByMmsiUntilMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisAddressedSafetyRelatedMessageObject>>& result ) = 0;
        virtual void GetAisAddressedSafetyRelatedMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, Int64 fromMessageSequenceNumber, Int64 untilMessageSequenceNumber, std::vector<std::shared_ptr<AisAddressedSafetyRelatedMessageObject>>& result ) = 0;
        virtual void GetAisAddressedSafetyRelatedMessageCollectionByDestinationMmsi( const DBGuid& destinationMmsi, std::vector<std::shared_ptr<AisAddressedSafetyRelatedMessageObject>>& result ) = 0;
        virtual void GetAisAddressedSafetyRelatedMessageCollectionByDestinationMmsiIsNull( std::vector<std::shared_ptr<AisAddressedSafetyRelatedMessageObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisBaseStationReportMessage queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisBaseStationReportMessageObject> GetAisBaseStationReportMessageById( const Guid& id ) = 0;
        virtual void GetAisBaseStationReportMessageCollection( std::vector<std::shared_ptr<AisBaseStationReportMessageObject>>& result ) = 0;
        virtual void GetAisBaseStationReportMessageCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisBaseStationReportMessageObject>>& result ) = 0;
        virtual std::shared_ptr<AisBaseStationReportMessageObject> GetAisBaseStationReportMessageByAisDeviceAndReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual std::shared_ptr<AisBaseStationReportMessageObject> GetAisBaseStationReportMessageByAisDeviceAtReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual void GetAisBaseStationReportMessageByAisDeviceFromReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisBaseStationReportMessageObject>>& result ) = 0;
        virtual void GetAisBaseStationReportMessageByAisDeviceUntilReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisBaseStationReportMessageObject>>& result ) = 0;
        virtual void GetAisBaseStationReportMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisBaseStationReportMessageObject>>& result ) = 0;
        virtual void GetAisBaseStationReportMessageCollectionByReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisBaseStationReportMessageObject>>& result ) = 0;
        virtual void GetAisBaseStationReportMessageCollectionAtReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisBaseStationReportMessageObject>>& result ) = 0;
        virtual void GetAisBaseStationReportMessageCollectionFromReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisBaseStationReportMessageObject>>& result ) = 0;
        virtual void GetAisBaseStationReportMessageCollectionUntilReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisBaseStationReportMessageObject>>& result ) = 0;
        virtual void GetAisBaseStationReportMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisBaseStationReportMessageObject>>& result ) = 0;
        virtual void GetAisBaseStationReportMessageCollectionByMmsi( const DBGuid& mmsi, std::vector<std::shared_ptr<AisBaseStationReportMessageObject>>& result ) = 0;
        virtual void GetAisBaseStationReportMessageCollectionByMmsiIsNull( std::vector<std::shared_ptr<AisBaseStationReportMessageObject>>& result ) = 0;
        virtual void GetAisBaseStationReportMessageCollectionByMmsiAndMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisBaseStationReportMessageObject>>& result ) = 0;
        virtual void GetAisBaseStationReportMessageCollectionByMmsiIsNullAndMessageSequenceNumber( Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisBaseStationReportMessageObject>>& result ) = 0;
        virtual void GetAisBaseStationReportMessageCollectionByMmsiFromMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisBaseStationReportMessageObject>>& result ) = 0;
        virtual void GetAisBaseStationReportMessageCollectionByMmsiUntilMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisBaseStationReportMessageObject>>& result ) = 0;
        virtual void GetAisBaseStationReportMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, Int64 fromMessageSequenceNumber, Int64 untilMessageSequenceNumber, std::vector<std::shared_ptr<AisBaseStationReportMessageObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisBinaryAcknowledgeMessage queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisBinaryAcknowledgeMessageObject> GetAisBinaryAcknowledgeMessageById( const Guid& id ) = 0;
        virtual void GetAisBinaryAcknowledgeMessageCollection( std::vector<std::shared_ptr<AisBinaryAcknowledgeMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAcknowledgeMessageCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisBinaryAcknowledgeMessageObject>>& result ) = 0;
        virtual std::shared_ptr<AisBinaryAcknowledgeMessageObject> GetAisBinaryAcknowledgeMessageByAisDeviceAndReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual std::shared_ptr<AisBinaryAcknowledgeMessageObject> GetAisBinaryAcknowledgeMessageByAisDeviceAtReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual void GetAisBinaryAcknowledgeMessageByAisDeviceFromReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisBinaryAcknowledgeMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAcknowledgeMessageByAisDeviceUntilReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisBinaryAcknowledgeMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAcknowledgeMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisBinaryAcknowledgeMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAcknowledgeMessageCollectionByReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisBinaryAcknowledgeMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAcknowledgeMessageCollectionAtReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisBinaryAcknowledgeMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAcknowledgeMessageCollectionFromReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisBinaryAcknowledgeMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAcknowledgeMessageCollectionUntilReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisBinaryAcknowledgeMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAcknowledgeMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisBinaryAcknowledgeMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAcknowledgeMessageCollectionByMmsi( const DBGuid& mmsi, std::vector<std::shared_ptr<AisBinaryAcknowledgeMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAcknowledgeMessageCollectionByMmsiIsNull( std::vector<std::shared_ptr<AisBinaryAcknowledgeMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAcknowledgeMessageCollectionByMmsiAndMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisBinaryAcknowledgeMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAcknowledgeMessageCollectionByMmsiIsNullAndMessageSequenceNumber( Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisBinaryAcknowledgeMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAcknowledgeMessageCollectionByMmsiFromMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisBinaryAcknowledgeMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAcknowledgeMessageCollectionByMmsiUntilMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisBinaryAcknowledgeMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAcknowledgeMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, Int64 fromMessageSequenceNumber, Int64 untilMessageSequenceNumber, std::vector<std::shared_ptr<AisBinaryAcknowledgeMessageObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisBinaryAddressedMessage queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisBinaryAddressedMessageObject> GetAisBinaryAddressedMessageById( const Guid& id ) = 0;
        virtual void GetAisBinaryAddressedMessageCollection( std::vector<std::shared_ptr<AisBinaryAddressedMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAddressedMessageCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisBinaryAddressedMessageObject>>& result ) = 0;
        virtual std::shared_ptr<AisBinaryAddressedMessageObject> GetAisBinaryAddressedMessageByAisDeviceAndReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual std::shared_ptr<AisBinaryAddressedMessageObject> GetAisBinaryAddressedMessageByAisDeviceAtReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual void GetAisBinaryAddressedMessageByAisDeviceFromReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisBinaryAddressedMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAddressedMessageByAisDeviceUntilReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisBinaryAddressedMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAddressedMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisBinaryAddressedMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAddressedMessageCollectionByReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisBinaryAddressedMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAddressedMessageCollectionAtReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisBinaryAddressedMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAddressedMessageCollectionFromReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisBinaryAddressedMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAddressedMessageCollectionUntilReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisBinaryAddressedMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAddressedMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisBinaryAddressedMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAddressedMessageCollectionByMmsi( const DBGuid& mmsi, std::vector<std::shared_ptr<AisBinaryAddressedMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAddressedMessageCollectionByMmsiIsNull( std::vector<std::shared_ptr<AisBinaryAddressedMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAddressedMessageCollectionByMmsiAndMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisBinaryAddressedMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAddressedMessageCollectionByMmsiIsNullAndMessageSequenceNumber( Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisBinaryAddressedMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAddressedMessageCollectionByMmsiFromMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisBinaryAddressedMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAddressedMessageCollectionByMmsiUntilMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisBinaryAddressedMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAddressedMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, Int64 fromMessageSequenceNumber, Int64 untilMessageSequenceNumber, std::vector<std::shared_ptr<AisBinaryAddressedMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAddressedMessageCollectionByDestinationMmsi( const DBGuid& destinationMmsi, std::vector<std::shared_ptr<AisBinaryAddressedMessageObject>>& result ) = 0;
        virtual void GetAisBinaryAddressedMessageCollectionByDestinationMmsiIsNull( std::vector<std::shared_ptr<AisBinaryAddressedMessageObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisBinaryBroadcastMessage queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisBinaryBroadcastMessageObject> GetAisBinaryBroadcastMessageById( const Guid& id ) = 0;
        virtual void GetAisBinaryBroadcastMessageCollection( std::vector<std::shared_ptr<AisBinaryBroadcastMessageObject>>& result ) = 0;
        virtual void GetAisBinaryBroadcastMessageCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisBinaryBroadcastMessageObject>>& result ) = 0;
        virtual std::shared_ptr<AisBinaryBroadcastMessageObject> GetAisBinaryBroadcastMessageByAisDeviceAndReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual std::shared_ptr<AisBinaryBroadcastMessageObject> GetAisBinaryBroadcastMessageByAisDeviceAtReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual void GetAisBinaryBroadcastMessageByAisDeviceFromReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisBinaryBroadcastMessageObject>>& result ) = 0;
        virtual void GetAisBinaryBroadcastMessageByAisDeviceUntilReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisBinaryBroadcastMessageObject>>& result ) = 0;
        virtual void GetAisBinaryBroadcastMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisBinaryBroadcastMessageObject>>& result ) = 0;
        virtual void GetAisBinaryBroadcastMessageCollectionByReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisBinaryBroadcastMessageObject>>& result ) = 0;
        virtual void GetAisBinaryBroadcastMessageCollectionAtReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisBinaryBroadcastMessageObject>>& result ) = 0;
        virtual void GetAisBinaryBroadcastMessageCollectionFromReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisBinaryBroadcastMessageObject>>& result ) = 0;
        virtual void GetAisBinaryBroadcastMessageCollectionUntilReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisBinaryBroadcastMessageObject>>& result ) = 0;
        virtual void GetAisBinaryBroadcastMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisBinaryBroadcastMessageObject>>& result ) = 0;
        virtual void GetAisBinaryBroadcastMessageCollectionByMmsi( const DBGuid& mmsi, std::vector<std::shared_ptr<AisBinaryBroadcastMessageObject>>& result ) = 0;
        virtual void GetAisBinaryBroadcastMessageCollectionByMmsiIsNull( std::vector<std::shared_ptr<AisBinaryBroadcastMessageObject>>& result ) = 0;
        virtual void GetAisBinaryBroadcastMessageCollectionByMmsiAndMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisBinaryBroadcastMessageObject>>& result ) = 0;
        virtual void GetAisBinaryBroadcastMessageCollectionByMmsiIsNullAndMessageSequenceNumber( Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisBinaryBroadcastMessageObject>>& result ) = 0;
        virtual void GetAisBinaryBroadcastMessageCollectionByMmsiFromMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisBinaryBroadcastMessageObject>>& result ) = 0;
        virtual void GetAisBinaryBroadcastMessageCollectionByMmsiUntilMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisBinaryBroadcastMessageObject>>& result ) = 0;
        virtual void GetAisBinaryBroadcastMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, Int64 fromMessageSequenceNumber, Int64 untilMessageSequenceNumber, std::vector<std::shared_ptr<AisBinaryBroadcastMessageObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisDataLinkManagementMessage queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisDataLinkManagementMessageObject> GetAisDataLinkManagementMessageById( const Guid& id ) = 0;
        virtual void GetAisDataLinkManagementMessageCollection( std::vector<std::shared_ptr<AisDataLinkManagementMessageObject>>& result ) = 0;
        virtual void GetAisDataLinkManagementMessageCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisDataLinkManagementMessageObject>>& result ) = 0;
        virtual std::shared_ptr<AisDataLinkManagementMessageObject> GetAisDataLinkManagementMessageByAisDeviceAndReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual std::shared_ptr<AisDataLinkManagementMessageObject> GetAisDataLinkManagementMessageByAisDeviceAtReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual void GetAisDataLinkManagementMessageByAisDeviceFromReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisDataLinkManagementMessageObject>>& result ) = 0;
        virtual void GetAisDataLinkManagementMessageByAisDeviceUntilReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisDataLinkManagementMessageObject>>& result ) = 0;
        virtual void GetAisDataLinkManagementMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisDataLinkManagementMessageObject>>& result ) = 0;
        virtual void GetAisDataLinkManagementMessageCollectionByReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisDataLinkManagementMessageObject>>& result ) = 0;
        virtual void GetAisDataLinkManagementMessageCollectionAtReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisDataLinkManagementMessageObject>>& result ) = 0;
        virtual void GetAisDataLinkManagementMessageCollectionFromReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisDataLinkManagementMessageObject>>& result ) = 0;
        virtual void GetAisDataLinkManagementMessageCollectionUntilReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisDataLinkManagementMessageObject>>& result ) = 0;
        virtual void GetAisDataLinkManagementMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisDataLinkManagementMessageObject>>& result ) = 0;
        virtual void GetAisDataLinkManagementMessageCollectionByMmsi( const DBGuid& mmsi, std::vector<std::shared_ptr<AisDataLinkManagementMessageObject>>& result ) = 0;
        virtual void GetAisDataLinkManagementMessageCollectionByMmsiIsNull( std::vector<std::shared_ptr<AisDataLinkManagementMessageObject>>& result ) = 0;
        virtual void GetAisDataLinkManagementMessageCollectionByMmsiAndMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisDataLinkManagementMessageObject>>& result ) = 0;
        virtual void GetAisDataLinkManagementMessageCollectionByMmsiIsNullAndMessageSequenceNumber( Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisDataLinkManagementMessageObject>>& result ) = 0;
        virtual void GetAisDataLinkManagementMessageCollectionByMmsiFromMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisDataLinkManagementMessageObject>>& result ) = 0;
        virtual void GetAisDataLinkManagementMessageCollectionByMmsiUntilMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisDataLinkManagementMessageObject>>& result ) = 0;
        virtual void GetAisDataLinkManagementMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, Int64 fromMessageSequenceNumber, Int64 untilMessageSequenceNumber, std::vector<std::shared_ptr<AisDataLinkManagementMessageObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisExtendedClassBCsPositionReportMessage queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisExtendedClassBCsPositionReportMessageObject> GetAisExtendedClassBCsPositionReportMessageById( const Guid& id ) = 0;
        virtual void GetAisExtendedClassBCsPositionReportMessageCollection( std::vector<std::shared_ptr<AisExtendedClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisExtendedClassBCsPositionReportMessageCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisExtendedClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual std::shared_ptr<AisExtendedClassBCsPositionReportMessageObject> GetAisExtendedClassBCsPositionReportMessageByAisDeviceAndReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual std::shared_ptr<AisExtendedClassBCsPositionReportMessageObject> GetAisExtendedClassBCsPositionReportMessageByAisDeviceAtReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual void GetAisExtendedClassBCsPositionReportMessageByAisDeviceFromReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisExtendedClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisExtendedClassBCsPositionReportMessageByAisDeviceUntilReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisExtendedClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisExtendedClassBCsPositionReportMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisExtendedClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisExtendedClassBCsPositionReportMessageCollectionByReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisExtendedClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisExtendedClassBCsPositionReportMessageCollectionAtReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisExtendedClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisExtendedClassBCsPositionReportMessageCollectionFromReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisExtendedClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisExtendedClassBCsPositionReportMessageCollectionUntilReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisExtendedClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisExtendedClassBCsPositionReportMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisExtendedClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisExtendedClassBCsPositionReportMessageCollectionByMmsi( const DBGuid& mmsi, std::vector<std::shared_ptr<AisExtendedClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisExtendedClassBCsPositionReportMessageCollectionByMmsiIsNull( std::vector<std::shared_ptr<AisExtendedClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisExtendedClassBCsPositionReportMessageCollectionByMmsiAndMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisExtendedClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisExtendedClassBCsPositionReportMessageCollectionByMmsiIsNullAndMessageSequenceNumber( Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisExtendedClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisExtendedClassBCsPositionReportMessageCollectionByMmsiFromMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisExtendedClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisExtendedClassBCsPositionReportMessageCollectionByMmsiUntilMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisExtendedClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisExtendedClassBCsPositionReportMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, Int64 fromMessageSequenceNumber, Int64 untilMessageSequenceNumber, std::vector<std::shared_ptr<AisExtendedClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisExtendedClassBCsPositionReportMessageCollectionByName( const DBGuid& name, std::vector<std::shared_ptr<AisExtendedClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisExtendedClassBCsPositionReportMessageCollectionByNameIsNull( std::vector<std::shared_ptr<AisExtendedClassBCsPositionReportMessageObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisInterrogationMessage queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisInterrogationMessageObject> GetAisInterrogationMessageById( const Guid& id ) = 0;
        virtual void GetAisInterrogationMessageCollection( std::vector<std::shared_ptr<AisInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisInterrogationMessageCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisInterrogationMessageObject>>& result ) = 0;
        virtual std::shared_ptr<AisInterrogationMessageObject> GetAisInterrogationMessageByAisDeviceAndReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual std::shared_ptr<AisInterrogationMessageObject> GetAisInterrogationMessageByAisDeviceAtReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual void GetAisInterrogationMessageByAisDeviceFromReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisInterrogationMessageByAisDeviceUntilReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisInterrogationMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisInterrogationMessageCollectionByReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisInterrogationMessageCollectionAtReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisInterrogationMessageCollectionFromReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisInterrogationMessageCollectionUntilReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisInterrogationMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisInterrogationMessageCollectionByMmsi( const DBGuid& mmsi, std::vector<std::shared_ptr<AisInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisInterrogationMessageCollectionByMmsiIsNull( std::vector<std::shared_ptr<AisInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisInterrogationMessageCollectionByMmsiAndMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisInterrogationMessageCollectionByMmsiIsNullAndMessageSequenceNumber( Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisInterrogationMessageCollectionByMmsiFromMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisInterrogationMessageCollectionByMmsiUntilMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisInterrogationMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, Int64 fromMessageSequenceNumber, Int64 untilMessageSequenceNumber, std::vector<std::shared_ptr<AisInterrogationMessageObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisPositionReportClassAMessageBase queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisPositionReportClassAMessageBaseObject> GetAisPositionReportClassAMessageBaseById( const Guid& id ) = 0;
        virtual void GetAisPositionReportClassAMessageBaseCollection( std::vector<std::shared_ptr<AisPositionReportClassAMessageBaseObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageBaseCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisPositionReportClassAMessageBaseObject>>& result ) = 0;
        virtual std::shared_ptr<AisPositionReportClassAMessageBaseObject> GetAisPositionReportClassAMessageBaseByAisDeviceAndReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual std::shared_ptr<AisPositionReportClassAMessageBaseObject> GetAisPositionReportClassAMessageBaseByAisDeviceAtReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual void GetAisPositionReportClassAMessageBaseByAisDeviceFromReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAMessageBaseObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageBaseByAisDeviceUntilReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAMessageBaseObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageBaseByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAMessageBaseObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageBaseCollectionByReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAMessageBaseObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageBaseCollectionAtReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAMessageBaseObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageBaseCollectionFromReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAMessageBaseObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageBaseCollectionUntilReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAMessageBaseObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageBaseCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAMessageBaseObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageBaseCollectionByMmsi( const DBGuid& mmsi, std::vector<std::shared_ptr<AisPositionReportClassAMessageBaseObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageBaseCollectionByMmsiIsNull( std::vector<std::shared_ptr<AisPositionReportClassAMessageBaseObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageBaseCollectionByMmsiAndMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisPositionReportClassAMessageBaseObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageBaseCollectionByMmsiIsNullAndMessageSequenceNumber( Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisPositionReportClassAMessageBaseObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageBaseCollectionByMmsiFromMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisPositionReportClassAMessageBaseObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageBaseCollectionByMmsiUntilMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisPositionReportClassAMessageBaseObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageBaseCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, Int64 fromMessageSequenceNumber, Int64 untilMessageSequenceNumber, std::vector<std::shared_ptr<AisPositionReportClassAMessageBaseObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisPositionReportClassAAssignedScheduleMessage queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisPositionReportClassAAssignedScheduleMessageObject> GetAisPositionReportClassAAssignedScheduleMessageById( const Guid& id ) = 0;
        virtual void GetAisPositionReportClassAAssignedScheduleMessageCollection( std::vector<std::shared_ptr<AisPositionReportClassAAssignedScheduleMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAAssignedScheduleMessageCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisPositionReportClassAAssignedScheduleMessageObject>>& result ) = 0;
        virtual std::shared_ptr<AisPositionReportClassAAssignedScheduleMessageObject> GetAisPositionReportClassAAssignedScheduleMessageByAisDeviceAndReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual std::shared_ptr<AisPositionReportClassAAssignedScheduleMessageObject> GetAisPositionReportClassAAssignedScheduleMessageByAisDeviceAtReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual void GetAisPositionReportClassAAssignedScheduleMessageByAisDeviceFromReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAAssignedScheduleMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAAssignedScheduleMessageByAisDeviceUntilReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAAssignedScheduleMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAAssignedScheduleMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAAssignedScheduleMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAAssignedScheduleMessageCollectionByReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAAssignedScheduleMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAAssignedScheduleMessageCollectionAtReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAAssignedScheduleMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAAssignedScheduleMessageCollectionFromReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAAssignedScheduleMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAAssignedScheduleMessageCollectionUntilReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAAssignedScheduleMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAAssignedScheduleMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAAssignedScheduleMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAAssignedScheduleMessageCollectionByMmsi( const DBGuid& mmsi, std::vector<std::shared_ptr<AisPositionReportClassAAssignedScheduleMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAAssignedScheduleMessageCollectionByMmsiIsNull( std::vector<std::shared_ptr<AisPositionReportClassAAssignedScheduleMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAAssignedScheduleMessageCollectionByMmsiAndMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisPositionReportClassAAssignedScheduleMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAAssignedScheduleMessageCollectionByMmsiIsNullAndMessageSequenceNumber( Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisPositionReportClassAAssignedScheduleMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAAssignedScheduleMessageCollectionByMmsiFromMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisPositionReportClassAAssignedScheduleMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAAssignedScheduleMessageCollectionByMmsiUntilMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisPositionReportClassAAssignedScheduleMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAAssignedScheduleMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, Int64 fromMessageSequenceNumber, Int64 untilMessageSequenceNumber, std::vector<std::shared_ptr<AisPositionReportClassAAssignedScheduleMessageObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisPositionReportClassAMessage queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisPositionReportClassAMessageObject> GetAisPositionReportClassAMessageById( const Guid& id ) = 0;
        virtual void GetAisPositionReportClassAMessageCollection( std::vector<std::shared_ptr<AisPositionReportClassAMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisPositionReportClassAMessageObject>>& result ) = 0;
        virtual std::shared_ptr<AisPositionReportClassAMessageObject> GetAisPositionReportClassAMessageByAisDeviceAndReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual std::shared_ptr<AisPositionReportClassAMessageObject> GetAisPositionReportClassAMessageByAisDeviceAtReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual void GetAisPositionReportClassAMessageByAisDeviceFromReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageByAisDeviceUntilReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageCollectionByReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageCollectionAtReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageCollectionFromReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageCollectionUntilReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageCollectionByMmsi( const DBGuid& mmsi, std::vector<std::shared_ptr<AisPositionReportClassAMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageCollectionByMmsiIsNull( std::vector<std::shared_ptr<AisPositionReportClassAMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageCollectionByMmsiAndMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisPositionReportClassAMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageCollectionByMmsiIsNullAndMessageSequenceNumber( Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisPositionReportClassAMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageCollectionByMmsiFromMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisPositionReportClassAMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageCollectionByMmsiUntilMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisPositionReportClassAMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, Int64 fromMessageSequenceNumber, Int64 untilMessageSequenceNumber, std::vector<std::shared_ptr<AisPositionReportClassAMessageObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisPositionReportClassAResponseToInterrogationMessage queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisPositionReportClassAResponseToInterrogationMessageObject> GetAisPositionReportClassAResponseToInterrogationMessageById( const Guid& id ) = 0;
        virtual void GetAisPositionReportClassAResponseToInterrogationMessageCollection( std::vector<std::shared_ptr<AisPositionReportClassAResponseToInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAResponseToInterrogationMessageCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisPositionReportClassAResponseToInterrogationMessageObject>>& result ) = 0;
        virtual std::shared_ptr<AisPositionReportClassAResponseToInterrogationMessageObject> GetAisPositionReportClassAResponseToInterrogationMessageByAisDeviceAndReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual std::shared_ptr<AisPositionReportClassAResponseToInterrogationMessageObject> GetAisPositionReportClassAResponseToInterrogationMessageByAisDeviceAtReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual void GetAisPositionReportClassAResponseToInterrogationMessageByAisDeviceFromReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAResponseToInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAResponseToInterrogationMessageByAisDeviceUntilReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAResponseToInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAResponseToInterrogationMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAResponseToInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAResponseToInterrogationMessageCollectionByReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAResponseToInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAResponseToInterrogationMessageCollectionAtReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAResponseToInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAResponseToInterrogationMessageCollectionFromReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAResponseToInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAResponseToInterrogationMessageCollectionUntilReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAResponseToInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAResponseToInterrogationMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisPositionReportClassAResponseToInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsi( const DBGuid& mmsi, std::vector<std::shared_ptr<AisPositionReportClassAResponseToInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsiIsNull( std::vector<std::shared_ptr<AisPositionReportClassAResponseToInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsiAndMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisPositionReportClassAResponseToInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsiIsNullAndMessageSequenceNumber( Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisPositionReportClassAResponseToInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsiFromMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisPositionReportClassAResponseToInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsiUntilMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisPositionReportClassAResponseToInterrogationMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, Int64 fromMessageSequenceNumber, Int64 untilMessageSequenceNumber, std::vector<std::shared_ptr<AisPositionReportClassAResponseToInterrogationMessageObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisPositionReportForLongRangeApplicationsMessage queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisPositionReportForLongRangeApplicationsMessageObject> GetAisPositionReportForLongRangeApplicationsMessageById( const Guid& id ) = 0;
        virtual void GetAisPositionReportForLongRangeApplicationsMessageCollection( std::vector<std::shared_ptr<AisPositionReportForLongRangeApplicationsMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportForLongRangeApplicationsMessageCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisPositionReportForLongRangeApplicationsMessageObject>>& result ) = 0;
        virtual std::shared_ptr<AisPositionReportForLongRangeApplicationsMessageObject> GetAisPositionReportForLongRangeApplicationsMessageByAisDeviceAndReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual std::shared_ptr<AisPositionReportForLongRangeApplicationsMessageObject> GetAisPositionReportForLongRangeApplicationsMessageByAisDeviceAtReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual void GetAisPositionReportForLongRangeApplicationsMessageByAisDeviceFromReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportForLongRangeApplicationsMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportForLongRangeApplicationsMessageByAisDeviceUntilReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportForLongRangeApplicationsMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportForLongRangeApplicationsMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisPositionReportForLongRangeApplicationsMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportForLongRangeApplicationsMessageCollectionByReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportForLongRangeApplicationsMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportForLongRangeApplicationsMessageCollectionAtReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportForLongRangeApplicationsMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportForLongRangeApplicationsMessageCollectionFromReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportForLongRangeApplicationsMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportForLongRangeApplicationsMessageCollectionUntilReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisPositionReportForLongRangeApplicationsMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportForLongRangeApplicationsMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisPositionReportForLongRangeApplicationsMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportForLongRangeApplicationsMessageCollectionByMmsi( const DBGuid& mmsi, std::vector<std::shared_ptr<AisPositionReportForLongRangeApplicationsMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportForLongRangeApplicationsMessageCollectionByMmsiIsNull( std::vector<std::shared_ptr<AisPositionReportForLongRangeApplicationsMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportForLongRangeApplicationsMessageCollectionByMmsiAndMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisPositionReportForLongRangeApplicationsMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportForLongRangeApplicationsMessageCollectionByMmsiIsNullAndMessageSequenceNumber( Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisPositionReportForLongRangeApplicationsMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportForLongRangeApplicationsMessageCollectionByMmsiFromMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisPositionReportForLongRangeApplicationsMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportForLongRangeApplicationsMessageCollectionByMmsiUntilMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisPositionReportForLongRangeApplicationsMessageObject>>& result ) = 0;
        virtual void GetAisPositionReportForLongRangeApplicationsMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, Int64 fromMessageSequenceNumber, Int64 untilMessageSequenceNumber, std::vector<std::shared_ptr<AisPositionReportForLongRangeApplicationsMessageObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisSafetyRelatedAcknowledgmentMessage queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisSafetyRelatedAcknowledgmentMessageObject> GetAisSafetyRelatedAcknowledgmentMessageById( const Guid& id ) = 0;
        virtual void GetAisSafetyRelatedAcknowledgmentMessageCollection( std::vector<std::shared_ptr<AisSafetyRelatedAcknowledgmentMessageObject>>& result ) = 0;
        virtual void GetAisSafetyRelatedAcknowledgmentMessageCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisSafetyRelatedAcknowledgmentMessageObject>>& result ) = 0;
        virtual std::shared_ptr<AisSafetyRelatedAcknowledgmentMessageObject> GetAisSafetyRelatedAcknowledgmentMessageByAisDeviceAndReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual std::shared_ptr<AisSafetyRelatedAcknowledgmentMessageObject> GetAisSafetyRelatedAcknowledgmentMessageByAisDeviceAtReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual void GetAisSafetyRelatedAcknowledgmentMessageByAisDeviceFromReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisSafetyRelatedAcknowledgmentMessageObject>>& result ) = 0;
        virtual void GetAisSafetyRelatedAcknowledgmentMessageByAisDeviceUntilReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisSafetyRelatedAcknowledgmentMessageObject>>& result ) = 0;
        virtual void GetAisSafetyRelatedAcknowledgmentMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisSafetyRelatedAcknowledgmentMessageObject>>& result ) = 0;
        virtual void GetAisSafetyRelatedAcknowledgmentMessageCollectionByReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisSafetyRelatedAcknowledgmentMessageObject>>& result ) = 0;
        virtual void GetAisSafetyRelatedAcknowledgmentMessageCollectionAtReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisSafetyRelatedAcknowledgmentMessageObject>>& result ) = 0;
        virtual void GetAisSafetyRelatedAcknowledgmentMessageCollectionFromReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisSafetyRelatedAcknowledgmentMessageObject>>& result ) = 0;
        virtual void GetAisSafetyRelatedAcknowledgmentMessageCollectionUntilReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisSafetyRelatedAcknowledgmentMessageObject>>& result ) = 0;
        virtual void GetAisSafetyRelatedAcknowledgmentMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisSafetyRelatedAcknowledgmentMessageObject>>& result ) = 0;
        virtual void GetAisSafetyRelatedAcknowledgmentMessageCollectionByMmsi( const DBGuid& mmsi, std::vector<std::shared_ptr<AisSafetyRelatedAcknowledgmentMessageObject>>& result ) = 0;
        virtual void GetAisSafetyRelatedAcknowledgmentMessageCollectionByMmsiIsNull( std::vector<std::shared_ptr<AisSafetyRelatedAcknowledgmentMessageObject>>& result ) = 0;
        virtual void GetAisSafetyRelatedAcknowledgmentMessageCollectionByMmsiAndMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisSafetyRelatedAcknowledgmentMessageObject>>& result ) = 0;
        virtual void GetAisSafetyRelatedAcknowledgmentMessageCollectionByMmsiIsNullAndMessageSequenceNumber( Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisSafetyRelatedAcknowledgmentMessageObject>>& result ) = 0;
        virtual void GetAisSafetyRelatedAcknowledgmentMessageCollectionByMmsiFromMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisSafetyRelatedAcknowledgmentMessageObject>>& result ) = 0;
        virtual void GetAisSafetyRelatedAcknowledgmentMessageCollectionByMmsiUntilMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisSafetyRelatedAcknowledgmentMessageObject>>& result ) = 0;
        virtual void GetAisSafetyRelatedAcknowledgmentMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, Int64 fromMessageSequenceNumber, Int64 untilMessageSequenceNumber, std::vector<std::shared_ptr<AisSafetyRelatedAcknowledgmentMessageObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisStandardClassBCsPositionReportMessage queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisStandardClassBCsPositionReportMessageObject> GetAisStandardClassBCsPositionReportMessageById( const Guid& id ) = 0;
        virtual void GetAisStandardClassBCsPositionReportMessageCollection( std::vector<std::shared_ptr<AisStandardClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardClassBCsPositionReportMessageCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisStandardClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual std::shared_ptr<AisStandardClassBCsPositionReportMessageObject> GetAisStandardClassBCsPositionReportMessageByAisDeviceAndReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual std::shared_ptr<AisStandardClassBCsPositionReportMessageObject> GetAisStandardClassBCsPositionReportMessageByAisDeviceAtReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual void GetAisStandardClassBCsPositionReportMessageByAisDeviceFromReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStandardClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardClassBCsPositionReportMessageByAisDeviceUntilReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStandardClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardClassBCsPositionReportMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisStandardClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardClassBCsPositionReportMessageCollectionByReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStandardClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardClassBCsPositionReportMessageCollectionAtReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStandardClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardClassBCsPositionReportMessageCollectionFromReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStandardClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardClassBCsPositionReportMessageCollectionUntilReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStandardClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardClassBCsPositionReportMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisStandardClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardClassBCsPositionReportMessageCollectionByMmsi( const DBGuid& mmsi, std::vector<std::shared_ptr<AisStandardClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardClassBCsPositionReportMessageCollectionByMmsiIsNull( std::vector<std::shared_ptr<AisStandardClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardClassBCsPositionReportMessageCollectionByMmsiAndMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisStandardClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardClassBCsPositionReportMessageCollectionByMmsiIsNullAndMessageSequenceNumber( Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisStandardClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardClassBCsPositionReportMessageCollectionByMmsiFromMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisStandardClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardClassBCsPositionReportMessageCollectionByMmsiUntilMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisStandardClassBCsPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardClassBCsPositionReportMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, Int64 fromMessageSequenceNumber, Int64 untilMessageSequenceNumber, std::vector<std::shared_ptr<AisStandardClassBCsPositionReportMessageObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisStandardSarAircraftPositionReportMessage queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisStandardSarAircraftPositionReportMessageObject> GetAisStandardSarAircraftPositionReportMessageById( const Guid& id ) = 0;
        virtual void GetAisStandardSarAircraftPositionReportMessageCollection( std::vector<std::shared_ptr<AisStandardSarAircraftPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardSarAircraftPositionReportMessageCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisStandardSarAircraftPositionReportMessageObject>>& result ) = 0;
        virtual std::shared_ptr<AisStandardSarAircraftPositionReportMessageObject> GetAisStandardSarAircraftPositionReportMessageByAisDeviceAndReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual std::shared_ptr<AisStandardSarAircraftPositionReportMessageObject> GetAisStandardSarAircraftPositionReportMessageByAisDeviceAtReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual void GetAisStandardSarAircraftPositionReportMessageByAisDeviceFromReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStandardSarAircraftPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardSarAircraftPositionReportMessageByAisDeviceUntilReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStandardSarAircraftPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardSarAircraftPositionReportMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisStandardSarAircraftPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardSarAircraftPositionReportMessageCollectionByReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStandardSarAircraftPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardSarAircraftPositionReportMessageCollectionAtReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStandardSarAircraftPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardSarAircraftPositionReportMessageCollectionFromReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStandardSarAircraftPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardSarAircraftPositionReportMessageCollectionUntilReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStandardSarAircraftPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardSarAircraftPositionReportMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisStandardSarAircraftPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardSarAircraftPositionReportMessageCollectionByMmsi( const DBGuid& mmsi, std::vector<std::shared_ptr<AisStandardSarAircraftPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardSarAircraftPositionReportMessageCollectionByMmsiIsNull( std::vector<std::shared_ptr<AisStandardSarAircraftPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardSarAircraftPositionReportMessageCollectionByMmsiAndMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisStandardSarAircraftPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardSarAircraftPositionReportMessageCollectionByMmsiIsNullAndMessageSequenceNumber( Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisStandardSarAircraftPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardSarAircraftPositionReportMessageCollectionByMmsiFromMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisStandardSarAircraftPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardSarAircraftPositionReportMessageCollectionByMmsiUntilMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisStandardSarAircraftPositionReportMessageObject>>& result ) = 0;
        virtual void GetAisStandardSarAircraftPositionReportMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, Int64 fromMessageSequenceNumber, Int64 untilMessageSequenceNumber, std::vector<std::shared_ptr<AisStandardSarAircraftPositionReportMessageObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisStaticAndVoyageRelatedDataMessage queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageById( const Guid& id ) = 0;
        virtual void GetAisStaticAndVoyageRelatedDataMessageCollection( std::vector<std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject>>& result ) = 0;
        virtual void GetAisStaticAndVoyageRelatedDataMessageCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject>>& result ) = 0;
        virtual std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageByAisDeviceAndReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageByAisDeviceAtReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual void GetAisStaticAndVoyageRelatedDataMessageByAisDeviceFromReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject>>& result ) = 0;
        virtual void GetAisStaticAndVoyageRelatedDataMessageByAisDeviceUntilReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject>>& result ) = 0;
        virtual void GetAisStaticAndVoyageRelatedDataMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject>>& result ) = 0;
        virtual void GetAisStaticAndVoyageRelatedDataMessageCollectionByReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject>>& result ) = 0;
        virtual void GetAisStaticAndVoyageRelatedDataMessageCollectionAtReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject>>& result ) = 0;
        virtual void GetAisStaticAndVoyageRelatedDataMessageCollectionFromReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject>>& result ) = 0;
        virtual void GetAisStaticAndVoyageRelatedDataMessageCollectionUntilReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject>>& result ) = 0;
        virtual void GetAisStaticAndVoyageRelatedDataMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject>>& result ) = 0;
        virtual void GetAisStaticAndVoyageRelatedDataMessageCollectionByMmsi( const DBGuid& mmsi, std::vector<std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject>>& result ) = 0;
        virtual void GetAisStaticAndVoyageRelatedDataMessageCollectionByMmsiIsNull( std::vector<std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject>>& result ) = 0;
        virtual void GetAisStaticAndVoyageRelatedDataMessageCollectionByMmsiAndMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject>>& result ) = 0;
        virtual void GetAisStaticAndVoyageRelatedDataMessageCollectionByMmsiIsNullAndMessageSequenceNumber( Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject>>& result ) = 0;
        virtual void GetAisStaticAndVoyageRelatedDataMessageCollectionByMmsiFromMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject>>& result ) = 0;
        virtual void GetAisStaticAndVoyageRelatedDataMessageCollectionByMmsiUntilMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject>>& result ) = 0;
        virtual void GetAisStaticAndVoyageRelatedDataMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, Int64 fromMessageSequenceNumber, Int64 untilMessageSequenceNumber, std::vector<std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject>>& result ) = 0;
        virtual void GetAisStaticAndVoyageRelatedDataMessageCollectionByImoNumber( const DBGuid& imoNumber, std::vector<std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject>>& result ) = 0;
        virtual void GetAisStaticAndVoyageRelatedDataMessageCollectionByImoNumberIsNull( std::vector<std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject>>& result ) = 0;
        virtual void GetAisStaticAndVoyageRelatedDataMessageCollectionByCallsign( const DBGuid& callsign, std::vector<std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject>>& result ) = 0;
        virtual void GetAisStaticAndVoyageRelatedDataMessageCollectionByCallsignIsNull( std::vector<std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject>>& result ) = 0;
        virtual void GetAisStaticAndVoyageRelatedDataMessageCollectionByShipName( const DBGuid& shipName, std::vector<std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject>>& result ) = 0;
        virtual void GetAisStaticAndVoyageRelatedDataMessageCollectionByShipNameIsNull( std::vector<std::shared_ptr<AisStaticAndVoyageRelatedDataMessageObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisStaticDataReportMessage queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisStaticDataReportMessageObject> GetAisStaticDataReportMessageById( const Guid& id ) = 0;
        virtual void GetAisStaticDataReportMessageCollection( std::vector<std::shared_ptr<AisStaticDataReportMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportMessageCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisStaticDataReportMessageObject>>& result ) = 0;
        virtual std::shared_ptr<AisStaticDataReportMessageObject> GetAisStaticDataReportMessageByAisDeviceAndReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual std::shared_ptr<AisStaticDataReportMessageObject> GetAisStaticDataReportMessageByAisDeviceAtReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual void GetAisStaticDataReportMessageByAisDeviceFromReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStaticDataReportMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportMessageByAisDeviceUntilReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStaticDataReportMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisStaticDataReportMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportMessageCollectionByReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStaticDataReportMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportMessageCollectionAtReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStaticDataReportMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportMessageCollectionFromReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStaticDataReportMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportMessageCollectionUntilReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStaticDataReportMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisStaticDataReportMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportMessageCollectionByMmsi( const DBGuid& mmsi, std::vector<std::shared_ptr<AisStaticDataReportMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportMessageCollectionByMmsiIsNull( std::vector<std::shared_ptr<AisStaticDataReportMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportMessageCollectionByMmsiAndMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisStaticDataReportMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportMessageCollectionByMmsiIsNullAndMessageSequenceNumber( Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisStaticDataReportMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportMessageCollectionByMmsiFromMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisStaticDataReportMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportMessageCollectionByMmsiUntilMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisStaticDataReportMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, Int64 fromMessageSequenceNumber, Int64 untilMessageSequenceNumber, std::vector<std::shared_ptr<AisStaticDataReportMessageObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisStaticDataReportPartAMessage queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisStaticDataReportPartAMessageObject> GetAisStaticDataReportPartAMessageById( const Guid& id ) = 0;
        virtual void GetAisStaticDataReportPartAMessageCollection( std::vector<std::shared_ptr<AisStaticDataReportPartAMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartAMessageCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisStaticDataReportPartAMessageObject>>& result ) = 0;
        virtual std::shared_ptr<AisStaticDataReportPartAMessageObject> GetAisStaticDataReportPartAMessageByAisDeviceAndReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual std::shared_ptr<AisStaticDataReportPartAMessageObject> GetAisStaticDataReportPartAMessageByAisDeviceAtReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual void GetAisStaticDataReportPartAMessageByAisDeviceFromReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStaticDataReportPartAMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartAMessageByAisDeviceUntilReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStaticDataReportPartAMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartAMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisStaticDataReportPartAMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartAMessageCollectionByReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStaticDataReportPartAMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartAMessageCollectionAtReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStaticDataReportPartAMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartAMessageCollectionFromReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStaticDataReportPartAMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartAMessageCollectionUntilReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStaticDataReportPartAMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartAMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisStaticDataReportPartAMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartAMessageCollectionByMmsi( const DBGuid& mmsi, std::vector<std::shared_ptr<AisStaticDataReportPartAMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartAMessageCollectionByMmsiIsNull( std::vector<std::shared_ptr<AisStaticDataReportPartAMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartAMessageCollectionByMmsiAndMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisStaticDataReportPartAMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartAMessageCollectionByMmsiIsNullAndMessageSequenceNumber( Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisStaticDataReportPartAMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartAMessageCollectionByMmsiFromMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisStaticDataReportPartAMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartAMessageCollectionByMmsiUntilMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisStaticDataReportPartAMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartAMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, Int64 fromMessageSequenceNumber, Int64 untilMessageSequenceNumber, std::vector<std::shared_ptr<AisStaticDataReportPartAMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartAMessageCollectionByShipName( const DBGuid& shipName, std::vector<std::shared_ptr<AisStaticDataReportPartAMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartAMessageCollectionByShipNameIsNull( std::vector<std::shared_ptr<AisStaticDataReportPartAMessageObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisStaticDataReportPartBMessage queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisStaticDataReportPartBMessageObject> GetAisStaticDataReportPartBMessageById( const Guid& id ) = 0;
        virtual void GetAisStaticDataReportPartBMessageCollection( std::vector<std::shared_ptr<AisStaticDataReportPartBMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartBMessageCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisStaticDataReportPartBMessageObject>>& result ) = 0;
        virtual std::shared_ptr<AisStaticDataReportPartBMessageObject> GetAisStaticDataReportPartBMessageByAisDeviceAndReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual std::shared_ptr<AisStaticDataReportPartBMessageObject> GetAisStaticDataReportPartBMessageByAisDeviceAtReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual void GetAisStaticDataReportPartBMessageByAisDeviceFromReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStaticDataReportPartBMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartBMessageByAisDeviceUntilReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStaticDataReportPartBMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartBMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisStaticDataReportPartBMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartBMessageCollectionByReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStaticDataReportPartBMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartBMessageCollectionAtReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStaticDataReportPartBMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartBMessageCollectionFromReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStaticDataReportPartBMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartBMessageCollectionUntilReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisStaticDataReportPartBMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartBMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisStaticDataReportPartBMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartBMessageCollectionByMmsi( const DBGuid& mmsi, std::vector<std::shared_ptr<AisStaticDataReportPartBMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartBMessageCollectionByMmsiIsNull( std::vector<std::shared_ptr<AisStaticDataReportPartBMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartBMessageCollectionByMmsiAndMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisStaticDataReportPartBMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartBMessageCollectionByMmsiIsNullAndMessageSequenceNumber( Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisStaticDataReportPartBMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartBMessageCollectionByMmsiFromMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisStaticDataReportPartBMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartBMessageCollectionByMmsiUntilMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisStaticDataReportPartBMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartBMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, Int64 fromMessageSequenceNumber, Int64 untilMessageSequenceNumber, std::vector<std::shared_ptr<AisStaticDataReportPartBMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartBMessageCollectionByCallsign( const DBGuid& callsign, std::vector<std::shared_ptr<AisStaticDataReportPartBMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartBMessageCollectionByCallsignIsNull( std::vector<std::shared_ptr<AisStaticDataReportPartBMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartBMessageCollectionByMothershipMmsi( const DBGuid& mothershipMmsi, std::vector<std::shared_ptr<AisStaticDataReportPartBMessageObject>>& result ) = 0;
        virtual void GetAisStaticDataReportPartBMessageCollectionByMothershipMmsiIsNull( std::vector<std::shared_ptr<AisStaticDataReportPartBMessageObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisUtcAndDateInquiryMessage queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisUtcAndDateInquiryMessageObject> GetAisUtcAndDateInquiryMessageById( const Guid& id ) = 0;
        virtual void GetAisUtcAndDateInquiryMessageCollection( std::vector<std::shared_ptr<AisUtcAndDateInquiryMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateInquiryMessageCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisUtcAndDateInquiryMessageObject>>& result ) = 0;
        virtual std::shared_ptr<AisUtcAndDateInquiryMessageObject> GetAisUtcAndDateInquiryMessageByAisDeviceAndReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual std::shared_ptr<AisUtcAndDateInquiryMessageObject> GetAisUtcAndDateInquiryMessageByAisDeviceAtReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual void GetAisUtcAndDateInquiryMessageByAisDeviceFromReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisUtcAndDateInquiryMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateInquiryMessageByAisDeviceUntilReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisUtcAndDateInquiryMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateInquiryMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisUtcAndDateInquiryMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateInquiryMessageCollectionByReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisUtcAndDateInquiryMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateInquiryMessageCollectionAtReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisUtcAndDateInquiryMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateInquiryMessageCollectionFromReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisUtcAndDateInquiryMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateInquiryMessageCollectionUntilReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisUtcAndDateInquiryMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateInquiryMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisUtcAndDateInquiryMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateInquiryMessageCollectionByMmsi( const DBGuid& mmsi, std::vector<std::shared_ptr<AisUtcAndDateInquiryMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateInquiryMessageCollectionByMmsiIsNull( std::vector<std::shared_ptr<AisUtcAndDateInquiryMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateInquiryMessageCollectionByMmsiAndMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisUtcAndDateInquiryMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateInquiryMessageCollectionByMmsiIsNullAndMessageSequenceNumber( Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisUtcAndDateInquiryMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateInquiryMessageCollectionByMmsiFromMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisUtcAndDateInquiryMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateInquiryMessageCollectionByMmsiUntilMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisUtcAndDateInquiryMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateInquiryMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, Int64 fromMessageSequenceNumber, Int64 untilMessageSequenceNumber, std::vector<std::shared_ptr<AisUtcAndDateInquiryMessageObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisUtcAndDateResponseMessage queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisUtcAndDateResponseMessageObject> GetAisUtcAndDateResponseMessageById( const Guid& id ) = 0;
        virtual void GetAisUtcAndDateResponseMessageCollection( std::vector<std::shared_ptr<AisUtcAndDateResponseMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateResponseMessageCollectionByAisDevice( const Guid& aisDevice, std::vector<std::shared_ptr<AisUtcAndDateResponseMessageObject>>& result ) = 0;
        virtual std::shared_ptr<AisUtcAndDateResponseMessageObject> GetAisUtcAndDateResponseMessageByAisDeviceAndReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual std::shared_ptr<AisUtcAndDateResponseMessageObject> GetAisUtcAndDateResponseMessageByAisDeviceAtReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp ) = 0;
        virtual void GetAisUtcAndDateResponseMessageByAisDeviceFromReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisUtcAndDateResponseMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateResponseMessageByAisDeviceUntilReceivedTimestamp( const Guid& aisDevice, const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisUtcAndDateResponseMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateResponseMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisUtcAndDateResponseMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateResponseMessageCollectionByReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisUtcAndDateResponseMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateResponseMessageCollectionAtReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisUtcAndDateResponseMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateResponseMessageCollectionFromReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisUtcAndDateResponseMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateResponseMessageCollectionUntilReceivedTimestamp( const DateTime& receivedTimestamp, std::vector<std::shared_ptr<AisUtcAndDateResponseMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateResponseMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp, std::vector<std::shared_ptr<AisUtcAndDateResponseMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateResponseMessageCollectionByMmsi( const DBGuid& mmsi, std::vector<std::shared_ptr<AisUtcAndDateResponseMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateResponseMessageCollectionByMmsiIsNull( std::vector<std::shared_ptr<AisUtcAndDateResponseMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateResponseMessageCollectionByMmsiAndMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisUtcAndDateResponseMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateResponseMessageCollectionByMmsiIsNullAndMessageSequenceNumber( Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisUtcAndDateResponseMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateResponseMessageCollectionByMmsiFromMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisUtcAndDateResponseMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateResponseMessageCollectionByMmsiUntilMessageSequenceNumber( const DBGuid& mmsi, Int64 messageSequenceNumber, std::vector<std::shared_ptr<AisUtcAndDateResponseMessageObject>>& result ) = 0;
        virtual void GetAisUtcAndDateResponseMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, Int64 fromMessageSequenceNumber, Int64 untilMessageSequenceNumber, std::vector<std::shared_ptr<AisUtcAndDateResponseMessageObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AlarmStateChange queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AlarmStateChangeObject> GetAlarmStateChangeById( const Guid& id ) = 0;
        virtual void GetAlarmStateChangeCollection( std::vector<std::shared_ptr<AlarmStateChangeObject>>& result ) = 0;
        virtual void GetAlarmStateChangeCollectionByAlarm( const Guid& alarm, std::vector<std::shared_ptr<AlarmStateChangeObject>>& result ) = 0;
        virtual std::shared_ptr<AlarmStateChangeObject> GetAlarmStateChangeByAlarmAndTimestamp( const Guid& alarm, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<AlarmStateChangeObject> GetAlarmStateChangeByAlarmAtTimestamp( const Guid& alarm, const DateTime& timestamp ) = 0;
        virtual void GetAlarmStateChangeByAlarmFromTimestamp( const Guid& alarm, const DateTime& timestamp, std::vector<std::shared_ptr<AlarmStateChangeObject>>& result ) = 0;
        virtual void GetAlarmStateChangeByAlarmUntilTimestamp( const Guid& alarm, const DateTime& timestamp, std::vector<std::shared_ptr<AlarmStateChangeObject>>& result ) = 0;
        virtual void GetAlarmStateChangeByAlarmOverTimestamp( Guid alarm, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<AlarmStateChangeObject>>& result ) = 0;
        virtual void GetAlarmStateChangeCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<AlarmStateChangeObject>>& result ) = 0;
        virtual void GetAlarmStateChangeCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<AlarmStateChangeObject>>& result ) = 0;
        virtual void GetAlarmStateChangeCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<AlarmStateChangeObject>>& result ) = 0;
        virtual void GetAlarmStateChangeCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<AlarmStateChangeObject>>& result ) = 0;
        virtual void GetAlarmStateChangeCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<AlarmStateChangeObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // BaseStationType queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<BaseStationTypeObject> GetBaseStationTypeById( const Guid& id ) = 0;
        virtual void GetBaseStationTypeCollection( std::vector<std::shared_ptr<BaseStationTypeObject>>& result ) = 0;
        virtual std::shared_ptr<BaseStationTypeObject> GetBaseStationTypeByName( const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // BinaryTimeseriesValue queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<BinaryTimeseriesValueObject> GetBinaryTimeseriesValueById( const Guid& id ) = 0;
        virtual void GetBinaryTimeseriesValueCollection( std::vector<std::shared_ptr<BinaryTimeseriesValueObject>>& result ) = 0;
        virtual void GetBinaryTimeseriesValueCollectionByTimeseries( const Guid& timeseries, std::vector<std::shared_ptr<BinaryTimeseriesValueObject>>& result ) = 0;
        virtual std::shared_ptr<BinaryTimeseriesValueObject> GetBinaryTimeseriesValueByTimeseriesAndTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<BinaryTimeseriesValueObject> GetBinaryTimeseriesValueByTimeseriesAtTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual void GetBinaryTimeseriesValueByTimeseriesFromTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<BinaryTimeseriesValueObject>>& result ) = 0;
        virtual void GetBinaryTimeseriesValueByTimeseriesUntilTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<BinaryTimeseriesValueObject>>& result ) = 0;
        virtual void GetBinaryTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<BinaryTimeseriesValueObject>>& result ) = 0;
        virtual void GetBinaryTimeseriesValueCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<BinaryTimeseriesValueObject>>& result ) = 0;
        virtual void GetBinaryTimeseriesValueCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<BinaryTimeseriesValueObject>>& result ) = 0;
        virtual void GetBinaryTimeseriesValueCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<BinaryTimeseriesValueObject>>& result ) = 0;
        virtual void GetBinaryTimeseriesValueCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<BinaryTimeseriesValueObject>>& result ) = 0;
        virtual void GetBinaryTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<BinaryTimeseriesValueObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Bookmark queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<BookmarkObject> GetBookmarkById( const Guid& id ) = 0;
        virtual void GetBookmarkCollection( std::vector<std::shared_ptr<BookmarkObject>>& result ) = 0;
        virtual void GetBookmarkCollectionByView( const Guid& view, std::vector<std::shared_ptr<BookmarkObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // BooleanTimeseriesValue queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<BooleanTimeseriesValueObject> GetBooleanTimeseriesValueById( const Guid& id ) = 0;
        virtual void GetBooleanTimeseriesValueCollection( std::vector<std::shared_ptr<BooleanTimeseriesValueObject>>& result ) = 0;
        virtual void GetBooleanTimeseriesValueCollectionByTimeseries( const Guid& timeseries, std::vector<std::shared_ptr<BooleanTimeseriesValueObject>>& result ) = 0;
        virtual std::shared_ptr<BooleanTimeseriesValueObject> GetBooleanTimeseriesValueByTimeseriesAndTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<BooleanTimeseriesValueObject> GetBooleanTimeseriesValueByTimeseriesAtTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual void GetBooleanTimeseriesValueByTimeseriesFromTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<BooleanTimeseriesValueObject>>& result ) = 0;
        virtual void GetBooleanTimeseriesValueByTimeseriesUntilTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<BooleanTimeseriesValueObject>>& result ) = 0;
        virtual void GetBooleanTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<BooleanTimeseriesValueObject>>& result ) = 0;
        virtual void GetBooleanTimeseriesValueCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<BooleanTimeseriesValueObject>>& result ) = 0;
        virtual void GetBooleanTimeseriesValueCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<BooleanTimeseriesValueObject>>& result ) = 0;
        virtual void GetBooleanTimeseriesValueCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<BooleanTimeseriesValueObject>>& result ) = 0;
        virtual void GetBooleanTimeseriesValueCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<BooleanTimeseriesValueObject>>& result ) = 0;
        virtual void GetBooleanTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<BooleanTimeseriesValueObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // ByteTimeseriesValue queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ByteTimeseriesValueObject> GetByteTimeseriesValueById( const Guid& id ) = 0;
        virtual void GetByteTimeseriesValueCollection( std::vector<std::shared_ptr<ByteTimeseriesValueObject>>& result ) = 0;
        virtual void GetByteTimeseriesValueCollectionByTimeseries( const Guid& timeseries, std::vector<std::shared_ptr<ByteTimeseriesValueObject>>& result ) = 0;
        virtual std::shared_ptr<ByteTimeseriesValueObject> GetByteTimeseriesValueByTimeseriesAndTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<ByteTimeseriesValueObject> GetByteTimeseriesValueByTimeseriesAtTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual void GetByteTimeseriesValueByTimeseriesFromTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<ByteTimeseriesValueObject>>& result ) = 0;
        virtual void GetByteTimeseriesValueByTimeseriesUntilTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<ByteTimeseriesValueObject>>& result ) = 0;
        virtual void GetByteTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<ByteTimeseriesValueObject>>& result ) = 0;
        virtual void GetByteTimeseriesValueCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<ByteTimeseriesValueObject>>& result ) = 0;
        virtual void GetByteTimeseriesValueCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<ByteTimeseriesValueObject>>& result ) = 0;
        virtual void GetByteTimeseriesValueCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<ByteTimeseriesValueObject>>& result ) = 0;
        virtual void GetByteTimeseriesValueCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<ByteTimeseriesValueObject>>& result ) = 0;
        virtual void GetByteTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<ByteTimeseriesValueObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CameraCommand queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CameraCommandObject> GetCameraCommandById( const Guid& id ) = 0;
        virtual void GetCameraCommandCollection( std::vector<std::shared_ptr<CameraCommandObject>>& result ) = 0;
        virtual void GetCameraCommandCollectionByCamera( const Guid& camera, std::vector<std::shared_ptr<CameraCommandObject>>& result ) = 0;
        virtual void GetCameraCommandCollectionByCameraAndTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandObject>>& result ) = 0;
        virtual void GetCameraCommandCollectionByCameraAtTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandObject>>& result ) = 0;
        virtual void GetCameraCommandCollectionByCameraFromTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandObject>>& result ) = 0;
        virtual void GetCameraCommandCollectionByCameraUntilTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandObject>>& result ) = 0;
        virtual void GetCameraCommandCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandObject>>& result ) = 0;
        virtual void GetCameraCommandCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandObject>>& result ) = 0;
        virtual void GetCameraCommandCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandObject>>& result ) = 0;
        virtual void GetCameraCommandCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandObject>>& result ) = 0;
        virtual void GetCameraCommandCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandObject>>& result ) = 0;
        virtual void GetCameraCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandObject>>& result ) = 0;
        virtual void GetCameraCommandCollectionByReply( const DBGuid& reply, std::vector<std::shared_ptr<CameraCommandObject>>& result ) = 0;
        virtual void GetCameraCommandCollectionByReplyIsNull( std::vector<std::shared_ptr<CameraCommandObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CameraCommandAbsoluteMove queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CameraCommandAbsoluteMoveObject> GetCameraCommandAbsoluteMoveById( const Guid& id ) = 0;
        virtual void GetCameraCommandAbsoluteMoveCollection( std::vector<std::shared_ptr<CameraCommandAbsoluteMoveObject>>& result ) = 0;
        virtual void GetCameraCommandAbsoluteMoveCollectionByCamera( const Guid& camera, std::vector<std::shared_ptr<CameraCommandAbsoluteMoveObject>>& result ) = 0;
        virtual void GetCameraCommandAbsoluteMoveCollectionByCameraAndTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandAbsoluteMoveObject>>& result ) = 0;
        virtual void GetCameraCommandAbsoluteMoveCollectionByCameraAtTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandAbsoluteMoveObject>>& result ) = 0;
        virtual void GetCameraCommandAbsoluteMoveCollectionByCameraFromTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandAbsoluteMoveObject>>& result ) = 0;
        virtual void GetCameraCommandAbsoluteMoveCollectionByCameraUntilTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandAbsoluteMoveObject>>& result ) = 0;
        virtual void GetCameraCommandAbsoluteMoveCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandAbsoluteMoveObject>>& result ) = 0;
        virtual void GetCameraCommandAbsoluteMoveCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandAbsoluteMoveObject>>& result ) = 0;
        virtual void GetCameraCommandAbsoluteMoveCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandAbsoluteMoveObject>>& result ) = 0;
        virtual void GetCameraCommandAbsoluteMoveCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandAbsoluteMoveObject>>& result ) = 0;
        virtual void GetCameraCommandAbsoluteMoveCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandAbsoluteMoveObject>>& result ) = 0;
        virtual void GetCameraCommandAbsoluteMoveCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandAbsoluteMoveObject>>& result ) = 0;
        virtual void GetCameraCommandAbsoluteMoveCollectionByReply( const DBGuid& reply, std::vector<std::shared_ptr<CameraCommandAbsoluteMoveObject>>& result ) = 0;
        virtual void GetCameraCommandAbsoluteMoveCollectionByReplyIsNull( std::vector<std::shared_ptr<CameraCommandAbsoluteMoveObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CameraCommandAdjustPanTiltZoom queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CameraCommandAdjustPanTiltZoomObject> GetCameraCommandAdjustPanTiltZoomById( const Guid& id ) = 0;
        virtual void GetCameraCommandAdjustPanTiltZoomCollection( std::vector<std::shared_ptr<CameraCommandAdjustPanTiltZoomObject>>& result ) = 0;
        virtual void GetCameraCommandAdjustPanTiltZoomCollectionByCamera( const Guid& camera, std::vector<std::shared_ptr<CameraCommandAdjustPanTiltZoomObject>>& result ) = 0;
        virtual void GetCameraCommandAdjustPanTiltZoomCollectionByCameraAndTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandAdjustPanTiltZoomObject>>& result ) = 0;
        virtual void GetCameraCommandAdjustPanTiltZoomCollectionByCameraAtTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandAdjustPanTiltZoomObject>>& result ) = 0;
        virtual void GetCameraCommandAdjustPanTiltZoomCollectionByCameraFromTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandAdjustPanTiltZoomObject>>& result ) = 0;
        virtual void GetCameraCommandAdjustPanTiltZoomCollectionByCameraUntilTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandAdjustPanTiltZoomObject>>& result ) = 0;
        virtual void GetCameraCommandAdjustPanTiltZoomCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandAdjustPanTiltZoomObject>>& result ) = 0;
        virtual void GetCameraCommandAdjustPanTiltZoomCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandAdjustPanTiltZoomObject>>& result ) = 0;
        virtual void GetCameraCommandAdjustPanTiltZoomCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandAdjustPanTiltZoomObject>>& result ) = 0;
        virtual void GetCameraCommandAdjustPanTiltZoomCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandAdjustPanTiltZoomObject>>& result ) = 0;
        virtual void GetCameraCommandAdjustPanTiltZoomCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandAdjustPanTiltZoomObject>>& result ) = 0;
        virtual void GetCameraCommandAdjustPanTiltZoomCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandAdjustPanTiltZoomObject>>& result ) = 0;
        virtual void GetCameraCommandAdjustPanTiltZoomCollectionByReply( const DBGuid& reply, std::vector<std::shared_ptr<CameraCommandAdjustPanTiltZoomObject>>& result ) = 0;
        virtual void GetCameraCommandAdjustPanTiltZoomCollectionByReplyIsNull( std::vector<std::shared_ptr<CameraCommandAdjustPanTiltZoomObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CameraCommandContinuousMove queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CameraCommandContinuousMoveObject> GetCameraCommandContinuousMoveById( const Guid& id ) = 0;
        virtual void GetCameraCommandContinuousMoveCollection( std::vector<std::shared_ptr<CameraCommandContinuousMoveObject>>& result ) = 0;
        virtual void GetCameraCommandContinuousMoveCollectionByCamera( const Guid& camera, std::vector<std::shared_ptr<CameraCommandContinuousMoveObject>>& result ) = 0;
        virtual void GetCameraCommandContinuousMoveCollectionByCameraAndTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandContinuousMoveObject>>& result ) = 0;
        virtual void GetCameraCommandContinuousMoveCollectionByCameraAtTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandContinuousMoveObject>>& result ) = 0;
        virtual void GetCameraCommandContinuousMoveCollectionByCameraFromTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandContinuousMoveObject>>& result ) = 0;
        virtual void GetCameraCommandContinuousMoveCollectionByCameraUntilTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandContinuousMoveObject>>& result ) = 0;
        virtual void GetCameraCommandContinuousMoveCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandContinuousMoveObject>>& result ) = 0;
        virtual void GetCameraCommandContinuousMoveCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandContinuousMoveObject>>& result ) = 0;
        virtual void GetCameraCommandContinuousMoveCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandContinuousMoveObject>>& result ) = 0;
        virtual void GetCameraCommandContinuousMoveCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandContinuousMoveObject>>& result ) = 0;
        virtual void GetCameraCommandContinuousMoveCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandContinuousMoveObject>>& result ) = 0;
        virtual void GetCameraCommandContinuousMoveCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandContinuousMoveObject>>& result ) = 0;
        virtual void GetCameraCommandContinuousMoveCollectionByReply( const DBGuid& reply, std::vector<std::shared_ptr<CameraCommandContinuousMoveObject>>& result ) = 0;
        virtual void GetCameraCommandContinuousMoveCollectionByReplyIsNull( std::vector<std::shared_ptr<CameraCommandContinuousMoveObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CameraCommandGeoMove queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CameraCommandGeoMoveObject> GetCameraCommandGeoMoveById( const Guid& id ) = 0;
        virtual void GetCameraCommandGeoMoveCollection( std::vector<std::shared_ptr<CameraCommandGeoMoveObject>>& result ) = 0;
        virtual void GetCameraCommandGeoMoveCollectionByCamera( const Guid& camera, std::vector<std::shared_ptr<CameraCommandGeoMoveObject>>& result ) = 0;
        virtual void GetCameraCommandGeoMoveCollectionByCameraAndTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandGeoMoveObject>>& result ) = 0;
        virtual void GetCameraCommandGeoMoveCollectionByCameraAtTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandGeoMoveObject>>& result ) = 0;
        virtual void GetCameraCommandGeoMoveCollectionByCameraFromTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandGeoMoveObject>>& result ) = 0;
        virtual void GetCameraCommandGeoMoveCollectionByCameraUntilTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandGeoMoveObject>>& result ) = 0;
        virtual void GetCameraCommandGeoMoveCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandGeoMoveObject>>& result ) = 0;
        virtual void GetCameraCommandGeoMoveCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandGeoMoveObject>>& result ) = 0;
        virtual void GetCameraCommandGeoMoveCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandGeoMoveObject>>& result ) = 0;
        virtual void GetCameraCommandGeoMoveCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandGeoMoveObject>>& result ) = 0;
        virtual void GetCameraCommandGeoMoveCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandGeoMoveObject>>& result ) = 0;
        virtual void GetCameraCommandGeoMoveCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandGeoMoveObject>>& result ) = 0;
        virtual void GetCameraCommandGeoMoveCollectionByReply( const DBGuid& reply, std::vector<std::shared_ptr<CameraCommandGeoMoveObject>>& result ) = 0;
        virtual void GetCameraCommandGeoMoveCollectionByReplyIsNull( std::vector<std::shared_ptr<CameraCommandGeoMoveObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CameraCommandRelativeMove queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CameraCommandRelativeMoveObject> GetCameraCommandRelativeMoveById( const Guid& id ) = 0;
        virtual void GetCameraCommandRelativeMoveCollection( std::vector<std::shared_ptr<CameraCommandRelativeMoveObject>>& result ) = 0;
        virtual void GetCameraCommandRelativeMoveCollectionByCamera( const Guid& camera, std::vector<std::shared_ptr<CameraCommandRelativeMoveObject>>& result ) = 0;
        virtual void GetCameraCommandRelativeMoveCollectionByCameraAndTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandRelativeMoveObject>>& result ) = 0;
        virtual void GetCameraCommandRelativeMoveCollectionByCameraAtTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandRelativeMoveObject>>& result ) = 0;
        virtual void GetCameraCommandRelativeMoveCollectionByCameraFromTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandRelativeMoveObject>>& result ) = 0;
        virtual void GetCameraCommandRelativeMoveCollectionByCameraUntilTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandRelativeMoveObject>>& result ) = 0;
        virtual void GetCameraCommandRelativeMoveCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandRelativeMoveObject>>& result ) = 0;
        virtual void GetCameraCommandRelativeMoveCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandRelativeMoveObject>>& result ) = 0;
        virtual void GetCameraCommandRelativeMoveCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandRelativeMoveObject>>& result ) = 0;
        virtual void GetCameraCommandRelativeMoveCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandRelativeMoveObject>>& result ) = 0;
        virtual void GetCameraCommandRelativeMoveCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandRelativeMoveObject>>& result ) = 0;
        virtual void GetCameraCommandRelativeMoveCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandRelativeMoveObject>>& result ) = 0;
        virtual void GetCameraCommandRelativeMoveCollectionByReply( const DBGuid& reply, std::vector<std::shared_ptr<CameraCommandRelativeMoveObject>>& result ) = 0;
        virtual void GetCameraCommandRelativeMoveCollectionByReplyIsNull( std::vector<std::shared_ptr<CameraCommandRelativeMoveObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CameraCommandReleasePTZOwnership queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CameraCommandReleasePTZOwnershipObject> GetCameraCommandReleasePTZOwnershipById( const Guid& id ) = 0;
        virtual void GetCameraCommandReleasePTZOwnershipCollection( std::vector<std::shared_ptr<CameraCommandReleasePTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandReleasePTZOwnershipCollectionByCamera( const Guid& camera, std::vector<std::shared_ptr<CameraCommandReleasePTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandReleasePTZOwnershipCollectionByCameraAndTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandReleasePTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandReleasePTZOwnershipCollectionByCameraAtTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandReleasePTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandReleasePTZOwnershipCollectionByCameraFromTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandReleasePTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandReleasePTZOwnershipCollectionByCameraUntilTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandReleasePTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandReleasePTZOwnershipCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandReleasePTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandReleasePTZOwnershipCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandReleasePTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandReleasePTZOwnershipCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandReleasePTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandReleasePTZOwnershipCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandReleasePTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandReleasePTZOwnershipCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandReleasePTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandReleasePTZOwnershipCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandReleasePTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandReleasePTZOwnershipCollectionByReply( const DBGuid& reply, std::vector<std::shared_ptr<CameraCommandReleasePTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandReleasePTZOwnershipCollectionByReplyIsNull( std::vector<std::shared_ptr<CameraCommandReleasePTZOwnershipObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CameraCommandRequestPTZOwnership queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CameraCommandRequestPTZOwnershipObject> GetCameraCommandRequestPTZOwnershipById( const Guid& id ) = 0;
        virtual void GetCameraCommandRequestPTZOwnershipCollection( std::vector<std::shared_ptr<CameraCommandRequestPTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandRequestPTZOwnershipCollectionByCamera( const Guid& camera, std::vector<std::shared_ptr<CameraCommandRequestPTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandRequestPTZOwnershipCollectionByCameraAndTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandRequestPTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandRequestPTZOwnershipCollectionByCameraAtTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandRequestPTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandRequestPTZOwnershipCollectionByCameraFromTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandRequestPTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandRequestPTZOwnershipCollectionByCameraUntilTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandRequestPTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandRequestPTZOwnershipCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandRequestPTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandRequestPTZOwnershipCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandRequestPTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandRequestPTZOwnershipCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandRequestPTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandRequestPTZOwnershipCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandRequestPTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandRequestPTZOwnershipCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandRequestPTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandRequestPTZOwnershipCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandRequestPTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandRequestPTZOwnershipCollectionByReply( const DBGuid& reply, std::vector<std::shared_ptr<CameraCommandRequestPTZOwnershipObject>>& result ) = 0;
        virtual void GetCameraCommandRequestPTZOwnershipCollectionByReplyIsNull( std::vector<std::shared_ptr<CameraCommandRequestPTZOwnershipObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CameraCommandSetAutoFocus queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CameraCommandSetAutoFocusObject> GetCameraCommandSetAutoFocusById( const Guid& id ) = 0;
        virtual void GetCameraCommandSetAutoFocusCollection( std::vector<std::shared_ptr<CameraCommandSetAutoFocusObject>>& result ) = 0;
        virtual void GetCameraCommandSetAutoFocusCollectionByCamera( const Guid& camera, std::vector<std::shared_ptr<CameraCommandSetAutoFocusObject>>& result ) = 0;
        virtual void GetCameraCommandSetAutoFocusCollectionByCameraAndTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetAutoFocusObject>>& result ) = 0;
        virtual void GetCameraCommandSetAutoFocusCollectionByCameraAtTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetAutoFocusObject>>& result ) = 0;
        virtual void GetCameraCommandSetAutoFocusCollectionByCameraFromTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetAutoFocusObject>>& result ) = 0;
        virtual void GetCameraCommandSetAutoFocusCollectionByCameraUntilTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetAutoFocusObject>>& result ) = 0;
        virtual void GetCameraCommandSetAutoFocusCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandSetAutoFocusObject>>& result ) = 0;
        virtual void GetCameraCommandSetAutoFocusCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetAutoFocusObject>>& result ) = 0;
        virtual void GetCameraCommandSetAutoFocusCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetAutoFocusObject>>& result ) = 0;
        virtual void GetCameraCommandSetAutoFocusCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetAutoFocusObject>>& result ) = 0;
        virtual void GetCameraCommandSetAutoFocusCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetAutoFocusObject>>& result ) = 0;
        virtual void GetCameraCommandSetAutoFocusCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandSetAutoFocusObject>>& result ) = 0;
        virtual void GetCameraCommandSetAutoFocusCollectionByReply( const DBGuid& reply, std::vector<std::shared_ptr<CameraCommandSetAutoFocusObject>>& result ) = 0;
        virtual void GetCameraCommandSetAutoFocusCollectionByReplyIsNull( std::vector<std::shared_ptr<CameraCommandSetAutoFocusObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CameraCommandSetBlackAndWhite queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CameraCommandSetBlackAndWhiteObject> GetCameraCommandSetBlackAndWhiteById( const Guid& id ) = 0;
        virtual void GetCameraCommandSetBlackAndWhiteCollection( std::vector<std::shared_ptr<CameraCommandSetBlackAndWhiteObject>>& result ) = 0;
        virtual void GetCameraCommandSetBlackAndWhiteCollectionByCamera( const Guid& camera, std::vector<std::shared_ptr<CameraCommandSetBlackAndWhiteObject>>& result ) = 0;
        virtual void GetCameraCommandSetBlackAndWhiteCollectionByCameraAndTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetBlackAndWhiteObject>>& result ) = 0;
        virtual void GetCameraCommandSetBlackAndWhiteCollectionByCameraAtTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetBlackAndWhiteObject>>& result ) = 0;
        virtual void GetCameraCommandSetBlackAndWhiteCollectionByCameraFromTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetBlackAndWhiteObject>>& result ) = 0;
        virtual void GetCameraCommandSetBlackAndWhiteCollectionByCameraUntilTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetBlackAndWhiteObject>>& result ) = 0;
        virtual void GetCameraCommandSetBlackAndWhiteCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandSetBlackAndWhiteObject>>& result ) = 0;
        virtual void GetCameraCommandSetBlackAndWhiteCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetBlackAndWhiteObject>>& result ) = 0;
        virtual void GetCameraCommandSetBlackAndWhiteCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetBlackAndWhiteObject>>& result ) = 0;
        virtual void GetCameraCommandSetBlackAndWhiteCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetBlackAndWhiteObject>>& result ) = 0;
        virtual void GetCameraCommandSetBlackAndWhiteCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetBlackAndWhiteObject>>& result ) = 0;
        virtual void GetCameraCommandSetBlackAndWhiteCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandSetBlackAndWhiteObject>>& result ) = 0;
        virtual void GetCameraCommandSetBlackAndWhiteCollectionByReply( const DBGuid& reply, std::vector<std::shared_ptr<CameraCommandSetBlackAndWhiteObject>>& result ) = 0;
        virtual void GetCameraCommandSetBlackAndWhiteCollectionByReplyIsNull( std::vector<std::shared_ptr<CameraCommandSetBlackAndWhiteObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CameraCommandSetFollowed queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CameraCommandSetFollowedObject> GetCameraCommandSetFollowedById( const Guid& id ) = 0;
        virtual void GetCameraCommandSetFollowedCollection( std::vector<std::shared_ptr<CameraCommandSetFollowedObject>>& result ) = 0;
        virtual void GetCameraCommandSetFollowedCollectionByCamera( const Guid& camera, std::vector<std::shared_ptr<CameraCommandSetFollowedObject>>& result ) = 0;
        virtual void GetCameraCommandSetFollowedCollectionByCameraAndTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetFollowedObject>>& result ) = 0;
        virtual void GetCameraCommandSetFollowedCollectionByCameraAtTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetFollowedObject>>& result ) = 0;
        virtual void GetCameraCommandSetFollowedCollectionByCameraFromTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetFollowedObject>>& result ) = 0;
        virtual void GetCameraCommandSetFollowedCollectionByCameraUntilTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetFollowedObject>>& result ) = 0;
        virtual void GetCameraCommandSetFollowedCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandSetFollowedObject>>& result ) = 0;
        virtual void GetCameraCommandSetFollowedCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetFollowedObject>>& result ) = 0;
        virtual void GetCameraCommandSetFollowedCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetFollowedObject>>& result ) = 0;
        virtual void GetCameraCommandSetFollowedCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetFollowedObject>>& result ) = 0;
        virtual void GetCameraCommandSetFollowedCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetFollowedObject>>& result ) = 0;
        virtual void GetCameraCommandSetFollowedCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandSetFollowedObject>>& result ) = 0;
        virtual void GetCameraCommandSetFollowedCollectionByReply( const DBGuid& reply, std::vector<std::shared_ptr<CameraCommandSetFollowedObject>>& result ) = 0;
        virtual void GetCameraCommandSetFollowedCollectionByReplyIsNull( std::vector<std::shared_ptr<CameraCommandSetFollowedObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CameraCommandSetInfraRedLamp queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CameraCommandSetInfraRedLampObject> GetCameraCommandSetInfraRedLampById( const Guid& id ) = 0;
        virtual void GetCameraCommandSetInfraRedLampCollection( std::vector<std::shared_ptr<CameraCommandSetInfraRedLampObject>>& result ) = 0;
        virtual void GetCameraCommandSetInfraRedLampCollectionByCamera( const Guid& camera, std::vector<std::shared_ptr<CameraCommandSetInfraRedLampObject>>& result ) = 0;
        virtual void GetCameraCommandSetInfraRedLampCollectionByCameraAndTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetInfraRedLampObject>>& result ) = 0;
        virtual void GetCameraCommandSetInfraRedLampCollectionByCameraAtTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetInfraRedLampObject>>& result ) = 0;
        virtual void GetCameraCommandSetInfraRedLampCollectionByCameraFromTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetInfraRedLampObject>>& result ) = 0;
        virtual void GetCameraCommandSetInfraRedLampCollectionByCameraUntilTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetInfraRedLampObject>>& result ) = 0;
        virtual void GetCameraCommandSetInfraRedLampCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandSetInfraRedLampObject>>& result ) = 0;
        virtual void GetCameraCommandSetInfraRedLampCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetInfraRedLampObject>>& result ) = 0;
        virtual void GetCameraCommandSetInfraRedLampCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetInfraRedLampObject>>& result ) = 0;
        virtual void GetCameraCommandSetInfraRedLampCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetInfraRedLampObject>>& result ) = 0;
        virtual void GetCameraCommandSetInfraRedLampCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetInfraRedLampObject>>& result ) = 0;
        virtual void GetCameraCommandSetInfraRedLampCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandSetInfraRedLampObject>>& result ) = 0;
        virtual void GetCameraCommandSetInfraRedLampCollectionByReply( const DBGuid& reply, std::vector<std::shared_ptr<CameraCommandSetInfraRedLampObject>>& result ) = 0;
        virtual void GetCameraCommandSetInfraRedLampCollectionByReplyIsNull( std::vector<std::shared_ptr<CameraCommandSetInfraRedLampObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CameraCommandSetWasher queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CameraCommandSetWasherObject> GetCameraCommandSetWasherById( const Guid& id ) = 0;
        virtual void GetCameraCommandSetWasherCollection( std::vector<std::shared_ptr<CameraCommandSetWasherObject>>& result ) = 0;
        virtual void GetCameraCommandSetWasherCollectionByCamera( const Guid& camera, std::vector<std::shared_ptr<CameraCommandSetWasherObject>>& result ) = 0;
        virtual void GetCameraCommandSetWasherCollectionByCameraAndTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetWasherObject>>& result ) = 0;
        virtual void GetCameraCommandSetWasherCollectionByCameraAtTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetWasherObject>>& result ) = 0;
        virtual void GetCameraCommandSetWasherCollectionByCameraFromTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetWasherObject>>& result ) = 0;
        virtual void GetCameraCommandSetWasherCollectionByCameraUntilTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetWasherObject>>& result ) = 0;
        virtual void GetCameraCommandSetWasherCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandSetWasherObject>>& result ) = 0;
        virtual void GetCameraCommandSetWasherCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetWasherObject>>& result ) = 0;
        virtual void GetCameraCommandSetWasherCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetWasherObject>>& result ) = 0;
        virtual void GetCameraCommandSetWasherCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetWasherObject>>& result ) = 0;
        virtual void GetCameraCommandSetWasherCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetWasherObject>>& result ) = 0;
        virtual void GetCameraCommandSetWasherCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandSetWasherObject>>& result ) = 0;
        virtual void GetCameraCommandSetWasherCollectionByReply( const DBGuid& reply, std::vector<std::shared_ptr<CameraCommandSetWasherObject>>& result ) = 0;
        virtual void GetCameraCommandSetWasherCollectionByReplyIsNull( std::vector<std::shared_ptr<CameraCommandSetWasherObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CameraCommandSetWiper queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CameraCommandSetWiperObject> GetCameraCommandSetWiperById( const Guid& id ) = 0;
        virtual void GetCameraCommandSetWiperCollection( std::vector<std::shared_ptr<CameraCommandSetWiperObject>>& result ) = 0;
        virtual void GetCameraCommandSetWiperCollectionByCamera( const Guid& camera, std::vector<std::shared_ptr<CameraCommandSetWiperObject>>& result ) = 0;
        virtual void GetCameraCommandSetWiperCollectionByCameraAndTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetWiperObject>>& result ) = 0;
        virtual void GetCameraCommandSetWiperCollectionByCameraAtTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetWiperObject>>& result ) = 0;
        virtual void GetCameraCommandSetWiperCollectionByCameraFromTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetWiperObject>>& result ) = 0;
        virtual void GetCameraCommandSetWiperCollectionByCameraUntilTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetWiperObject>>& result ) = 0;
        virtual void GetCameraCommandSetWiperCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandSetWiperObject>>& result ) = 0;
        virtual void GetCameraCommandSetWiperCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetWiperObject>>& result ) = 0;
        virtual void GetCameraCommandSetWiperCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetWiperObject>>& result ) = 0;
        virtual void GetCameraCommandSetWiperCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetWiperObject>>& result ) = 0;
        virtual void GetCameraCommandSetWiperCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandSetWiperObject>>& result ) = 0;
        virtual void GetCameraCommandSetWiperCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandSetWiperObject>>& result ) = 0;
        virtual void GetCameraCommandSetWiperCollectionByReply( const DBGuid& reply, std::vector<std::shared_ptr<CameraCommandSetWiperObject>>& result ) = 0;
        virtual void GetCameraCommandSetWiperCollectionByReplyIsNull( std::vector<std::shared_ptr<CameraCommandSetWiperObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CameraCommandStop queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CameraCommandStopObject> GetCameraCommandStopById( const Guid& id ) = 0;
        virtual void GetCameraCommandStopCollection( std::vector<std::shared_ptr<CameraCommandStopObject>>& result ) = 0;
        virtual void GetCameraCommandStopCollectionByCamera( const Guid& camera, std::vector<std::shared_ptr<CameraCommandStopObject>>& result ) = 0;
        virtual void GetCameraCommandStopCollectionByCameraAndTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandStopObject>>& result ) = 0;
        virtual void GetCameraCommandStopCollectionByCameraAtTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandStopObject>>& result ) = 0;
        virtual void GetCameraCommandStopCollectionByCameraFromTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandStopObject>>& result ) = 0;
        virtual void GetCameraCommandStopCollectionByCameraUntilTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandStopObject>>& result ) = 0;
        virtual void GetCameraCommandStopCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandStopObject>>& result ) = 0;
        virtual void GetCameraCommandStopCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandStopObject>>& result ) = 0;
        virtual void GetCameraCommandStopCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandStopObject>>& result ) = 0;
        virtual void GetCameraCommandStopCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandStopObject>>& result ) = 0;
        virtual void GetCameraCommandStopCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandStopObject>>& result ) = 0;
        virtual void GetCameraCommandStopCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandStopObject>>& result ) = 0;
        virtual void GetCameraCommandStopCollectionByReply( const DBGuid& reply, std::vector<std::shared_ptr<CameraCommandStopObject>>& result ) = 0;
        virtual void GetCameraCommandStopCollectionByReplyIsNull( std::vector<std::shared_ptr<CameraCommandStopObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CameraCommandReply queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CameraCommandReplyObject> GetCameraCommandReplyById( const Guid& id ) = 0;
        virtual void GetCameraCommandReplyCollection( std::vector<std::shared_ptr<CameraCommandReplyObject>>& result ) = 0;
        virtual void GetCameraCommandReplyCollectionByCamera( const Guid& camera, std::vector<std::shared_ptr<CameraCommandReplyObject>>& result ) = 0;
        virtual void GetCameraCommandReplyCollectionByCameraAndTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandReplyObject>>& result ) = 0;
        virtual void GetCameraCommandReplyCollectionByCameraAtTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandReplyObject>>& result ) = 0;
        virtual void GetCameraCommandReplyCollectionByCameraFromTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandReplyObject>>& result ) = 0;
        virtual void GetCameraCommandReplyCollectionByCameraUntilTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandReplyObject>>& result ) = 0;
        virtual void GetCameraCommandReplyCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandReplyObject>>& result ) = 0;
        virtual void GetCameraCommandReplyCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandReplyObject>>& result ) = 0;
        virtual void GetCameraCommandReplyCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandReplyObject>>& result ) = 0;
        virtual void GetCameraCommandReplyCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandReplyObject>>& result ) = 0;
        virtual void GetCameraCommandReplyCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraCommandReplyObject>>& result ) = 0;
        virtual void GetCameraCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraCommandReplyObject>>& result ) = 0;
        virtual std::shared_ptr<CameraCommandReplyObject> GetCameraCommandReplyByCommand( const DBGuid& command ) = 0;
        virtual void GetCameraCommandReplyCollectionByCommandIsNull( std::vector<std::shared_ptr<CameraCommandReplyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CameraConfiguration queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CameraConfigurationObject> GetCameraConfigurationById( const Guid& id ) = 0;
        virtual void GetCameraConfigurationCollection( std::vector<std::shared_ptr<CameraConfigurationObject>>& result ) = 0;
        virtual void GetCameraConfigurationCollectionByCamera( const Guid& camera, std::vector<std::shared_ptr<CameraConfigurationObject>>& result ) = 0;
        virtual std::shared_ptr<CameraConfigurationObject> GetCameraConfigurationByCameraAndTimestamp( const Guid& camera, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<CameraConfigurationObject> GetCameraConfigurationByCameraAtTimestamp( const Guid& camera, const DateTime& timestamp ) = 0;
        virtual void GetCameraConfigurationByCameraFromTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraConfigurationObject>>& result ) = 0;
        virtual void GetCameraConfigurationByCameraUntilTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraConfigurationObject>>& result ) = 0;
        virtual void GetCameraConfigurationByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraConfigurationObject>>& result ) = 0;
        virtual void GetCameraConfigurationCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraConfigurationObject>>& result ) = 0;
        virtual void GetCameraConfigurationCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraConfigurationObject>>& result ) = 0;
        virtual void GetCameraConfigurationCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraConfigurationObject>>& result ) = 0;
        virtual void GetCameraConfigurationCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraConfigurationObject>>& result ) = 0;
        virtual void GetCameraConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraConfigurationObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CameraPanCalibration queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CameraPanCalibrationObject> GetCameraPanCalibrationById( const Guid& id ) = 0;
        virtual void GetCameraPanCalibrationCollection( std::vector<std::shared_ptr<CameraPanCalibrationObject>>& result ) = 0;
        virtual void GetCameraPanCalibrationCollectionByCamera( const Guid& camera, std::vector<std::shared_ptr<CameraPanCalibrationObject>>& result ) = 0;
        virtual std::shared_ptr<CameraPanCalibrationObject> GetCameraPanCalibrationByCameraAndTimestamp( const Guid& camera, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<CameraPanCalibrationObject> GetCameraPanCalibrationByCameraAtTimestamp( const Guid& camera, const DateTime& timestamp ) = 0;
        virtual void GetCameraPanCalibrationByCameraFromTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraPanCalibrationObject>>& result ) = 0;
        virtual void GetCameraPanCalibrationByCameraUntilTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraPanCalibrationObject>>& result ) = 0;
        virtual void GetCameraPanCalibrationByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraPanCalibrationObject>>& result ) = 0;
        virtual void GetCameraPanCalibrationCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraPanCalibrationObject>>& result ) = 0;
        virtual void GetCameraPanCalibrationCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraPanCalibrationObject>>& result ) = 0;
        virtual void GetCameraPanCalibrationCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraPanCalibrationObject>>& result ) = 0;
        virtual void GetCameraPanCalibrationCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraPanCalibrationObject>>& result ) = 0;
        virtual void GetCameraPanCalibrationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraPanCalibrationObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CameraPanCalibrationValue queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CameraPanCalibrationValueObject> GetCameraPanCalibrationValueById( const Guid& id ) = 0;
        virtual void GetCameraPanCalibrationValueCollection( std::vector<std::shared_ptr<CameraPanCalibrationValueObject>>& result ) = 0;
        virtual void GetCameraPanCalibrationValueCollectionByPanCalibration( const Guid& panCalibration, std::vector<std::shared_ptr<CameraPanCalibrationValueObject>>& result ) = 0;
        virtual std::shared_ptr<CameraPanCalibrationValueObject> GetCameraPanCalibrationValueByPanCalibrationAndPanAngle( const Guid& panCalibration, double panAngle ) = 0;
        virtual void GetCameraPanCalibrationValueByPanCalibrationFromPanAngle( const Guid& panCalibration, double panAngle, std::vector<std::shared_ptr<CameraPanCalibrationValueObject>>& result ) = 0;
        virtual void GetCameraPanCalibrationValueByPanCalibrationUntilPanAngle( const Guid& panCalibration, double panAngle, std::vector<std::shared_ptr<CameraPanCalibrationValueObject>>& result ) = 0;
        virtual void GetCameraPanCalibrationValueByPanCalibrationOverPanAngle( Guid panCalibration, double fromPanAngle, double untilPanAngle, std::vector<std::shared_ptr<CameraPanCalibrationValueObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CameraStatus queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CameraStatusObject> GetCameraStatusById( const Guid& id ) = 0;
        virtual void GetCameraStatusCollection( std::vector<std::shared_ptr<CameraStatusObject>>& result ) = 0;
        virtual void GetCameraStatusCollectionByCamera( const Guid& camera, std::vector<std::shared_ptr<CameraStatusObject>>& result ) = 0;
        virtual std::shared_ptr<CameraStatusObject> GetCameraStatusByCameraAndTimestamp( const Guid& camera, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<CameraStatusObject> GetCameraStatusByCameraAtTimestamp( const Guid& camera, const DateTime& timestamp ) = 0;
        virtual void GetCameraStatusByCameraFromTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraStatusObject>>& result ) = 0;
        virtual void GetCameraStatusByCameraUntilTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraStatusObject>>& result ) = 0;
        virtual void GetCameraStatusByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraStatusObject>>& result ) = 0;
        virtual void GetCameraStatusCollectionByTrack( const DBGuid& track, std::vector<std::shared_ptr<CameraStatusObject>>& result ) = 0;
        virtual void GetCameraStatusCollectionByTrackIsNull( std::vector<std::shared_ptr<CameraStatusObject>>& result ) = 0;
        virtual std::shared_ptr<CameraStatusObject> GetCameraStatusByTrackAndTimestamp( const DBGuid& track, const DateTime& timestamp ) = 0;
        virtual void GetCameraStatusCollectionByTrackIsNullAndTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraStatusObject>>& result ) = 0;
        virtual std::shared_ptr<CameraStatusObject> GetCameraStatusByTrackAtTimestamp( const DBGuid& track, const DateTime& timestamp ) = 0;
        virtual void GetCameraStatusByTrackFromTimestamp( const DBGuid& track, const DateTime& timestamp, std::vector<std::shared_ptr<CameraStatusObject>>& result ) = 0;
        virtual void GetCameraStatusByTrackUntilTimestamp( const DBGuid& track, const DateTime& timestamp, std::vector<std::shared_ptr<CameraStatusObject>>& result ) = 0;
        virtual void GetCameraStatusByTrackOverTimestamp( Guid track, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraStatusObject>>& result ) = 0;
        virtual void GetCameraStatusCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraStatusObject>>& result ) = 0;
        virtual void GetCameraStatusCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraStatusObject>>& result ) = 0;
        virtual void GetCameraStatusCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraStatusObject>>& result ) = 0;
        virtual void GetCameraStatusCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraStatusObject>>& result ) = 0;
        virtual void GetCameraStatusCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraStatusObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CameraTiltCalibration queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CameraTiltCalibrationObject> GetCameraTiltCalibrationById( const Guid& id ) = 0;
        virtual void GetCameraTiltCalibrationCollection( std::vector<std::shared_ptr<CameraTiltCalibrationObject>>& result ) = 0;
        virtual void GetCameraTiltCalibrationCollectionByCamera( const Guid& camera, std::vector<std::shared_ptr<CameraTiltCalibrationObject>>& result ) = 0;
        virtual std::shared_ptr<CameraTiltCalibrationObject> GetCameraTiltCalibrationByCameraAndTimestamp( const Guid& camera, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<CameraTiltCalibrationObject> GetCameraTiltCalibrationByCameraAtTimestamp( const Guid& camera, const DateTime& timestamp ) = 0;
        virtual void GetCameraTiltCalibrationByCameraFromTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraTiltCalibrationObject>>& result ) = 0;
        virtual void GetCameraTiltCalibrationByCameraUntilTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraTiltCalibrationObject>>& result ) = 0;
        virtual void GetCameraTiltCalibrationByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraTiltCalibrationObject>>& result ) = 0;
        virtual void GetCameraTiltCalibrationCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraTiltCalibrationObject>>& result ) = 0;
        virtual void GetCameraTiltCalibrationCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraTiltCalibrationObject>>& result ) = 0;
        virtual void GetCameraTiltCalibrationCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraTiltCalibrationObject>>& result ) = 0;
        virtual void GetCameraTiltCalibrationCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraTiltCalibrationObject>>& result ) = 0;
        virtual void GetCameraTiltCalibrationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraTiltCalibrationObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CameraTiltCalibrationValue queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CameraTiltCalibrationValueObject> GetCameraTiltCalibrationValueById( const Guid& id ) = 0;
        virtual void GetCameraTiltCalibrationValueCollection( std::vector<std::shared_ptr<CameraTiltCalibrationValueObject>>& result ) = 0;
        virtual void GetCameraTiltCalibrationValueCollectionByTiltCalibration( const Guid& tiltCalibration, std::vector<std::shared_ptr<CameraTiltCalibrationValueObject>>& result ) = 0;
        virtual std::shared_ptr<CameraTiltCalibrationValueObject> GetCameraTiltCalibrationValueByTiltCalibrationAndPanAngle( const Guid& tiltCalibration, double panAngle ) = 0;
        virtual void GetCameraTiltCalibrationValueByTiltCalibrationFromPanAngle( const Guid& tiltCalibration, double panAngle, std::vector<std::shared_ptr<CameraTiltCalibrationValueObject>>& result ) = 0;
        virtual void GetCameraTiltCalibrationValueByTiltCalibrationUntilPanAngle( const Guid& tiltCalibration, double panAngle, std::vector<std::shared_ptr<CameraTiltCalibrationValueObject>>& result ) = 0;
        virtual void GetCameraTiltCalibrationValueByTiltCalibrationOverPanAngle( Guid tiltCalibration, double fromPanAngle, double untilPanAngle, std::vector<std::shared_ptr<CameraTiltCalibrationValueObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CameraZoomCalibration queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CameraZoomCalibrationObject> GetCameraZoomCalibrationById( const Guid& id ) = 0;
        virtual void GetCameraZoomCalibrationCollection( std::vector<std::shared_ptr<CameraZoomCalibrationObject>>& result ) = 0;
        virtual void GetCameraZoomCalibrationCollectionByCamera( const Guid& camera, std::vector<std::shared_ptr<CameraZoomCalibrationObject>>& result ) = 0;
        virtual std::shared_ptr<CameraZoomCalibrationObject> GetCameraZoomCalibrationByCameraAndTimestamp( const Guid& camera, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<CameraZoomCalibrationObject> GetCameraZoomCalibrationByCameraAtTimestamp( const Guid& camera, const DateTime& timestamp ) = 0;
        virtual void GetCameraZoomCalibrationByCameraFromTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraZoomCalibrationObject>>& result ) = 0;
        virtual void GetCameraZoomCalibrationByCameraUntilTimestamp( const Guid& camera, const DateTime& timestamp, std::vector<std::shared_ptr<CameraZoomCalibrationObject>>& result ) = 0;
        virtual void GetCameraZoomCalibrationByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraZoomCalibrationObject>>& result ) = 0;
        virtual void GetCameraZoomCalibrationCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraZoomCalibrationObject>>& result ) = 0;
        virtual void GetCameraZoomCalibrationCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraZoomCalibrationObject>>& result ) = 0;
        virtual void GetCameraZoomCalibrationCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraZoomCalibrationObject>>& result ) = 0;
        virtual void GetCameraZoomCalibrationCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<CameraZoomCalibrationObject>>& result ) = 0;
        virtual void GetCameraZoomCalibrationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<CameraZoomCalibrationObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CameraZoomCalibrationValue queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CameraZoomCalibrationValueObject> GetCameraZoomCalibrationValueById( const Guid& id ) = 0;
        virtual void GetCameraZoomCalibrationValueCollection( std::vector<std::shared_ptr<CameraZoomCalibrationValueObject>>& result ) = 0;
        virtual void GetCameraZoomCalibrationValueCollectionByZoomCalibration( const Guid& zoomCalibration, std::vector<std::shared_ptr<CameraZoomCalibrationValueObject>>& result ) = 0;
        virtual std::shared_ptr<CameraZoomCalibrationValueObject> GetCameraZoomCalibrationValueByZoomCalibrationAndFocalLength( const Guid& zoomCalibration, double focalLength ) = 0;
        virtual void GetCameraZoomCalibrationValueByZoomCalibrationFromFocalLength( const Guid& zoomCalibration, double focalLength, std::vector<std::shared_ptr<CameraZoomCalibrationValueObject>>& result ) = 0;
        virtual void GetCameraZoomCalibrationValueByZoomCalibrationUntilFocalLength( const Guid& zoomCalibration, double focalLength, std::vector<std::shared_ptr<CameraZoomCalibrationValueObject>>& result ) = 0;
        virtual void GetCameraZoomCalibrationValueByZoomCalibrationOverFocalLength( Guid zoomCalibration, double fromFocalLength, double untilFocalLength, std::vector<std::shared_ptr<CameraZoomCalibrationValueObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CatalogElement queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CatalogElementObject> GetCatalogElementById( const Guid& id ) = 0;
        virtual void GetCatalogElementCollection( std::vector<std::shared_ptr<CatalogElementObject>>& result ) = 0;
        virtual void GetCatalogElementCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<CatalogElementObject>>& result ) = 0;
        virtual void GetCatalogElementCollectionByCatalogIsNull( std::vector<std::shared_ptr<CatalogElementObject>>& result ) = 0;
        virtual std::shared_ptr<CatalogElementObject> GetCatalogElementByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetCatalogElementCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<CatalogElementObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Catalog queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CatalogObject> GetCatalogById( const Guid& id ) = 0;
        virtual void GetCatalogCollection( std::vector<std::shared_ptr<CatalogObject>>& result ) = 0;
        virtual void GetCatalogCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<CatalogObject>>& result ) = 0;
        virtual void GetCatalogCollectionByCatalogIsNull( std::vector<std::shared_ptr<CatalogObject>>& result ) = 0;
        virtual std::shared_ptr<CatalogObject> GetCatalogByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetCatalogCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<CatalogObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Element queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ElementObject> GetElementById( const Guid& id ) = 0;
        virtual void GetElementCollection( std::vector<std::shared_ptr<ElementObject>>& result ) = 0;
        virtual void GetElementCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<ElementObject>>& result ) = 0;
        virtual void GetElementCollectionByCatalogIsNull( std::vector<std::shared_ptr<ElementObject>>& result ) = 0;
        virtual std::shared_ptr<ElementObject> GetElementByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetElementCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<ElementObject>>& result ) = 0;
        virtual void GetElementCollectionByElementType( const DBGuid& elementType, std::vector<std::shared_ptr<ElementObject>>& result ) = 0;
        virtual void GetElementCollectionByElementTypeIsNull( std::vector<std::shared_ptr<ElementObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // CollectionInfo queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CollectionInfoObject> GetCollectionInfoById( const Guid& id ) = 0;
        virtual void GetCollectionInfoCollection( std::vector<std::shared_ptr<CollectionInfoObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Country queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CountryObject> GetCountryById( const Guid& id ) = 0;
        virtual void GetCountryCollection( std::vector<std::shared_ptr<CountryObject>>& result ) = 0;
        virtual std::shared_ptr<CountryObject> GetCountryByName( const FixedDBWideString<127>& name ) = 0;
        virtual std::shared_ptr<CountryObject> GetCountryByCode( Int32 code ) = 0;
        virtual void GetCountryFromCode( Int32 code, std::vector<std::shared_ptr<CountryObject>>& result ) = 0;
        virtual void GetCountryUntilCode( Int32 code, std::vector<std::shared_ptr<CountryObject>>& result ) = 0;
        virtual void GetCountryOverCode( Int32 fromCode, Int32 untilCode, std::vector<std::shared_ptr<CountryObject>>& result ) = 0;
        virtual std::shared_ptr<CountryObject> GetCountryByAlpha2( const FixedDBWideString<2>& alpha2 ) = 0;
        virtual std::shared_ptr<CountryObject> GetCountryByAlpha3( const FixedDBWideString<3>& alpha3 ) = 0;
        // ---------------------------------------------------------------------
        // CursorInfo queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CursorInfoObject> GetCursorInfoById( const Guid& id ) = 0;
        virtual void GetCursorInfoCollection( std::vector<std::shared_ptr<CursorInfoObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // DateTimeTimeseriesValue queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<DateTimeTimeseriesValueObject> GetDateTimeTimeseriesValueById( const Guid& id ) = 0;
        virtual void GetDateTimeTimeseriesValueCollection( std::vector<std::shared_ptr<DateTimeTimeseriesValueObject>>& result ) = 0;
        virtual void GetDateTimeTimeseriesValueCollectionByTimeseries( const Guid& timeseries, std::vector<std::shared_ptr<DateTimeTimeseriesValueObject>>& result ) = 0;
        virtual std::shared_ptr<DateTimeTimeseriesValueObject> GetDateTimeTimeseriesValueByTimeseriesAndTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<DateTimeTimeseriesValueObject> GetDateTimeTimeseriesValueByTimeseriesAtTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual void GetDateTimeTimeseriesValueByTimeseriesFromTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<DateTimeTimeseriesValueObject>>& result ) = 0;
        virtual void GetDateTimeTimeseriesValueByTimeseriesUntilTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<DateTimeTimeseriesValueObject>>& result ) = 0;
        virtual void GetDateTimeTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<DateTimeTimeseriesValueObject>>& result ) = 0;
        virtual void GetDateTimeTimeseriesValueCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<DateTimeTimeseriesValueObject>>& result ) = 0;
        virtual void GetDateTimeTimeseriesValueCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<DateTimeTimeseriesValueObject>>& result ) = 0;
        virtual void GetDateTimeTimeseriesValueCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<DateTimeTimeseriesValueObject>>& result ) = 0;
        virtual void GetDateTimeTimeseriesValueCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<DateTimeTimeseriesValueObject>>& result ) = 0;
        virtual void GetDateTimeTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<DateTimeTimeseriesValueObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // DeviceHost queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<DeviceHostObject> GetDeviceHostById( const Guid& id ) = 0;
        virtual void GetDeviceHostCollection( std::vector<std::shared_ptr<DeviceHostObject>>& result ) = 0;
        virtual std::shared_ptr<DeviceHostObject> GetDeviceHostByName( const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // DeviceHostConfiguration queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<DeviceHostConfigurationObject> GetDeviceHostConfigurationById( const Guid& id ) = 0;
        virtual void GetDeviceHostConfigurationCollection( std::vector<std::shared_ptr<DeviceHostConfigurationObject>>& result ) = 0;
        virtual void GetDeviceHostConfigurationCollectionByHost( const Guid& host, std::vector<std::shared_ptr<DeviceHostConfigurationObject>>& result ) = 0;
        virtual std::shared_ptr<DeviceHostConfigurationObject> GetDeviceHostConfigurationByHostAndTimestamp( const Guid& host, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<DeviceHostConfigurationObject> GetDeviceHostConfigurationByHostAtTimestamp( const Guid& host, const DateTime& timestamp ) = 0;
        virtual void GetDeviceHostConfigurationByHostFromTimestamp( const Guid& host, const DateTime& timestamp, std::vector<std::shared_ptr<DeviceHostConfigurationObject>>& result ) = 0;
        virtual void GetDeviceHostConfigurationByHostUntilTimestamp( const Guid& host, const DateTime& timestamp, std::vector<std::shared_ptr<DeviceHostConfigurationObject>>& result ) = 0;
        virtual void GetDeviceHostConfigurationByHostOverTimestamp( Guid host, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<DeviceHostConfigurationObject>>& result ) = 0;
        virtual void GetDeviceHostConfigurationCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<DeviceHostConfigurationObject>>& result ) = 0;
        virtual void GetDeviceHostConfigurationCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<DeviceHostConfigurationObject>>& result ) = 0;
        virtual void GetDeviceHostConfigurationCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<DeviceHostConfigurationObject>>& result ) = 0;
        virtual void GetDeviceHostConfigurationCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<DeviceHostConfigurationObject>>& result ) = 0;
        virtual void GetDeviceHostConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<DeviceHostConfigurationObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // DoubleTimeseriesValue queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<DoubleTimeseriesValueObject> GetDoubleTimeseriesValueById( const Guid& id ) = 0;
        virtual void GetDoubleTimeseriesValueCollection( std::vector<std::shared_ptr<DoubleTimeseriesValueObject>>& result ) = 0;
        virtual void GetDoubleTimeseriesValueCollectionByTimeseries( const Guid& timeseries, std::vector<std::shared_ptr<DoubleTimeseriesValueObject>>& result ) = 0;
        virtual std::shared_ptr<DoubleTimeseriesValueObject> GetDoubleTimeseriesValueByTimeseriesAndTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<DoubleTimeseriesValueObject> GetDoubleTimeseriesValueByTimeseriesAtTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual void GetDoubleTimeseriesValueByTimeseriesFromTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<DoubleTimeseriesValueObject>>& result ) = 0;
        virtual void GetDoubleTimeseriesValueByTimeseriesUntilTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<DoubleTimeseriesValueObject>>& result ) = 0;
        virtual void GetDoubleTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<DoubleTimeseriesValueObject>>& result ) = 0;
        virtual void GetDoubleTimeseriesValueCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<DoubleTimeseriesValueObject>>& result ) = 0;
        virtual void GetDoubleTimeseriesValueCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<DoubleTimeseriesValueObject>>& result ) = 0;
        virtual void GetDoubleTimeseriesValueCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<DoubleTimeseriesValueObject>>& result ) = 0;
        virtual void GetDoubleTimeseriesValueCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<DoubleTimeseriesValueObject>>& result ) = 0;
        virtual void GetDoubleTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<DoubleTimeseriesValueObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // FacilityType queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<FacilityTypeObject> GetFacilityTypeById( const Guid& id ) = 0;
        virtual void GetFacilityTypeCollection( std::vector<std::shared_ptr<FacilityTypeObject>>& result ) = 0;
        virtual std::shared_ptr<FacilityTypeObject> GetFacilityTypeByName( const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // GeoPosition2DTimeseriesValue queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GeoPosition2DTimeseriesValueObject> GetGeoPosition2DTimeseriesValueById( const Guid& id ) = 0;
        virtual void GetGeoPosition2DTimeseriesValueCollection( std::vector<std::shared_ptr<GeoPosition2DTimeseriesValueObject>>& result ) = 0;
        virtual void GetGeoPosition2DTimeseriesValueCollectionByTimeseries( const Guid& timeseries, std::vector<std::shared_ptr<GeoPosition2DTimeseriesValueObject>>& result ) = 0;
        virtual std::shared_ptr<GeoPosition2DTimeseriesValueObject> GetGeoPosition2DTimeseriesValueByTimeseriesAndTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<GeoPosition2DTimeseriesValueObject> GetGeoPosition2DTimeseriesValueByTimeseriesAtTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual void GetGeoPosition2DTimeseriesValueByTimeseriesFromTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<GeoPosition2DTimeseriesValueObject>>& result ) = 0;
        virtual void GetGeoPosition2DTimeseriesValueByTimeseriesUntilTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<GeoPosition2DTimeseriesValueObject>>& result ) = 0;
        virtual void GetGeoPosition2DTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<GeoPosition2DTimeseriesValueObject>>& result ) = 0;
        virtual void GetGeoPosition2DTimeseriesValueCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GeoPosition2DTimeseriesValueObject>>& result ) = 0;
        virtual void GetGeoPosition2DTimeseriesValueCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GeoPosition2DTimeseriesValueObject>>& result ) = 0;
        virtual void GetGeoPosition2DTimeseriesValueCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GeoPosition2DTimeseriesValueObject>>& result ) = 0;
        virtual void GetGeoPosition2DTimeseriesValueCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GeoPosition2DTimeseriesValueObject>>& result ) = 0;
        virtual void GetGeoPosition2DTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<GeoPosition2DTimeseriesValueObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // GeoPosition3DTimeseriesValue queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GeoPosition3DTimeseriesValueObject> GetGeoPosition3DTimeseriesValueById( const Guid& id ) = 0;
        virtual void GetGeoPosition3DTimeseriesValueCollection( std::vector<std::shared_ptr<GeoPosition3DTimeseriesValueObject>>& result ) = 0;
        virtual void GetGeoPosition3DTimeseriesValueCollectionByTimeseries( const Guid& timeseries, std::vector<std::shared_ptr<GeoPosition3DTimeseriesValueObject>>& result ) = 0;
        virtual std::shared_ptr<GeoPosition3DTimeseriesValueObject> GetGeoPosition3DTimeseriesValueByTimeseriesAndTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<GeoPosition3DTimeseriesValueObject> GetGeoPosition3DTimeseriesValueByTimeseriesAtTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual void GetGeoPosition3DTimeseriesValueByTimeseriesFromTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<GeoPosition3DTimeseriesValueObject>>& result ) = 0;
        virtual void GetGeoPosition3DTimeseriesValueByTimeseriesUntilTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<GeoPosition3DTimeseriesValueObject>>& result ) = 0;
        virtual void GetGeoPosition3DTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<GeoPosition3DTimeseriesValueObject>>& result ) = 0;
        virtual void GetGeoPosition3DTimeseriesValueCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GeoPosition3DTimeseriesValueObject>>& result ) = 0;
        virtual void GetGeoPosition3DTimeseriesValueCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GeoPosition3DTimeseriesValueObject>>& result ) = 0;
        virtual void GetGeoPosition3DTimeseriesValueCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GeoPosition3DTimeseriesValueObject>>& result ) = 0;
        virtual void GetGeoPosition3DTimeseriesValueCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GeoPosition3DTimeseriesValueObject>>& result ) = 0;
        virtual void GetGeoPosition3DTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<GeoPosition3DTimeseriesValueObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // GNSSDeviceCommand queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GNSSDeviceCommandObject> GetGNSSDeviceCommandById( const Guid& id ) = 0;
        virtual void GetGNSSDeviceCommandCollection( std::vector<std::shared_ptr<GNSSDeviceCommandObject>>& result ) = 0;
        virtual void GetGNSSDeviceCommandCollectionByGNSSDevice( const Guid& gNSSDevice, std::vector<std::shared_ptr<GNSSDeviceCommandObject>>& result ) = 0;
        virtual void GetGNSSDeviceCommandCollectionByGNSSDeviceAndTimestamp( const Guid& gNSSDevice, const DateTime& timestamp, std::vector<std::shared_ptr<GNSSDeviceCommandObject>>& result ) = 0;
        virtual void GetGNSSDeviceCommandCollectionByGNSSDeviceAtTimestamp( const Guid& gNSSDevice, const DateTime& timestamp, std::vector<std::shared_ptr<GNSSDeviceCommandObject>>& result ) = 0;
        virtual void GetGNSSDeviceCommandCollectionByGNSSDeviceFromTimestamp( const Guid& gNSSDevice, const DateTime& timestamp, std::vector<std::shared_ptr<GNSSDeviceCommandObject>>& result ) = 0;
        virtual void GetGNSSDeviceCommandCollectionByGNSSDeviceUntilTimestamp( const Guid& gNSSDevice, const DateTime& timestamp, std::vector<std::shared_ptr<GNSSDeviceCommandObject>>& result ) = 0;
        virtual void GetGNSSDeviceCommandCollectionByGNSSDeviceOverTimestamp( Guid gNSSDevice, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<GNSSDeviceCommandObject>>& result ) = 0;
        virtual void GetGNSSDeviceCommandCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GNSSDeviceCommandObject>>& result ) = 0;
        virtual void GetGNSSDeviceCommandCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GNSSDeviceCommandObject>>& result ) = 0;
        virtual void GetGNSSDeviceCommandCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GNSSDeviceCommandObject>>& result ) = 0;
        virtual void GetGNSSDeviceCommandCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GNSSDeviceCommandObject>>& result ) = 0;
        virtual void GetGNSSDeviceCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<GNSSDeviceCommandObject>>& result ) = 0;
        virtual void GetGNSSDeviceCommandCollectionByReply( const DBGuid& reply, std::vector<std::shared_ptr<GNSSDeviceCommandObject>>& result ) = 0;
        virtual void GetGNSSDeviceCommandCollectionByReplyIsNull( std::vector<std::shared_ptr<GNSSDeviceCommandObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // GNSSDeviceCommandReply queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GNSSDeviceCommandReplyObject> GetGNSSDeviceCommandReplyById( const Guid& id ) = 0;
        virtual void GetGNSSDeviceCommandReplyCollection( std::vector<std::shared_ptr<GNSSDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetGNSSDeviceCommandReplyCollectionByGNSSDevice( const Guid& gNSSDevice, std::vector<std::shared_ptr<GNSSDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetGNSSDeviceCommandReplyCollectionByGNSSDeviceAndTimestamp( const Guid& gNSSDevice, const DateTime& timestamp, std::vector<std::shared_ptr<GNSSDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetGNSSDeviceCommandReplyCollectionByGNSSDeviceAtTimestamp( const Guid& gNSSDevice, const DateTime& timestamp, std::vector<std::shared_ptr<GNSSDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetGNSSDeviceCommandReplyCollectionByGNSSDeviceFromTimestamp( const Guid& gNSSDevice, const DateTime& timestamp, std::vector<std::shared_ptr<GNSSDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetGNSSDeviceCommandReplyCollectionByGNSSDeviceUntilTimestamp( const Guid& gNSSDevice, const DateTime& timestamp, std::vector<std::shared_ptr<GNSSDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetGNSSDeviceCommandReplyCollectionByGNSSDeviceOverTimestamp( Guid gNSSDevice, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<GNSSDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetGNSSDeviceCommandReplyCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GNSSDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetGNSSDeviceCommandReplyCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GNSSDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetGNSSDeviceCommandReplyCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GNSSDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetGNSSDeviceCommandReplyCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GNSSDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetGNSSDeviceCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<GNSSDeviceCommandReplyObject>>& result ) = 0;
        virtual std::shared_ptr<GNSSDeviceCommandReplyObject> GetGNSSDeviceCommandReplyByCommand( const DBGuid& command ) = 0;
        virtual void GetGNSSDeviceCommandReplyCollectionByCommandIsNull( std::vector<std::shared_ptr<GNSSDeviceCommandReplyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // GNSSDeviceConfiguration queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GNSSDeviceConfigurationObject> GetGNSSDeviceConfigurationById( const Guid& id ) = 0;
        virtual void GetGNSSDeviceConfigurationCollection( std::vector<std::shared_ptr<GNSSDeviceConfigurationObject>>& result ) = 0;
        virtual void GetGNSSDeviceConfigurationCollectionByGNSSDevice( const Guid& gNSSDevice, std::vector<std::shared_ptr<GNSSDeviceConfigurationObject>>& result ) = 0;
        virtual std::shared_ptr<GNSSDeviceConfigurationObject> GetGNSSDeviceConfigurationByGNSSDeviceAndTimestamp( const Guid& gNSSDevice, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<GNSSDeviceConfigurationObject> GetGNSSDeviceConfigurationByGNSSDeviceAtTimestamp( const Guid& gNSSDevice, const DateTime& timestamp ) = 0;
        virtual void GetGNSSDeviceConfigurationByGNSSDeviceFromTimestamp( const Guid& gNSSDevice, const DateTime& timestamp, std::vector<std::shared_ptr<GNSSDeviceConfigurationObject>>& result ) = 0;
        virtual void GetGNSSDeviceConfigurationByGNSSDeviceUntilTimestamp( const Guid& gNSSDevice, const DateTime& timestamp, std::vector<std::shared_ptr<GNSSDeviceConfigurationObject>>& result ) = 0;
        virtual void GetGNSSDeviceConfigurationByGNSSDeviceOverTimestamp( Guid gNSSDevice, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<GNSSDeviceConfigurationObject>>& result ) = 0;
        virtual void GetGNSSDeviceConfigurationCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GNSSDeviceConfigurationObject>>& result ) = 0;
        virtual void GetGNSSDeviceConfigurationCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GNSSDeviceConfigurationObject>>& result ) = 0;
        virtual void GetGNSSDeviceConfigurationCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GNSSDeviceConfigurationObject>>& result ) = 0;
        virtual void GetGNSSDeviceConfigurationCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GNSSDeviceConfigurationObject>>& result ) = 0;
        virtual void GetGNSSDeviceConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<GNSSDeviceConfigurationObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // GuidTimeseriesValue queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GuidTimeseriesValueObject> GetGuidTimeseriesValueById( const Guid& id ) = 0;
        virtual void GetGuidTimeseriesValueCollection( std::vector<std::shared_ptr<GuidTimeseriesValueObject>>& result ) = 0;
        virtual void GetGuidTimeseriesValueCollectionByTimeseries( const Guid& timeseries, std::vector<std::shared_ptr<GuidTimeseriesValueObject>>& result ) = 0;
        virtual std::shared_ptr<GuidTimeseriesValueObject> GetGuidTimeseriesValueByTimeseriesAndTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<GuidTimeseriesValueObject> GetGuidTimeseriesValueByTimeseriesAtTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual void GetGuidTimeseriesValueByTimeseriesFromTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<GuidTimeseriesValueObject>>& result ) = 0;
        virtual void GetGuidTimeseriesValueByTimeseriesUntilTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<GuidTimeseriesValueObject>>& result ) = 0;
        virtual void GetGuidTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<GuidTimeseriesValueObject>>& result ) = 0;
        virtual void GetGuidTimeseriesValueCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GuidTimeseriesValueObject>>& result ) = 0;
        virtual void GetGuidTimeseriesValueCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GuidTimeseriesValueObject>>& result ) = 0;
        virtual void GetGuidTimeseriesValueCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GuidTimeseriesValueObject>>& result ) = 0;
        virtual void GetGuidTimeseriesValueCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GuidTimeseriesValueObject>>& result ) = 0;
        virtual void GetGuidTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<GuidTimeseriesValueObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // GyroDeviceCommand queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GyroDeviceCommandObject> GetGyroDeviceCommandById( const Guid& id ) = 0;
        virtual void GetGyroDeviceCommandCollection( std::vector<std::shared_ptr<GyroDeviceCommandObject>>& result ) = 0;
        virtual void GetGyroDeviceCommandCollectionByGyroDevice( const Guid& gyroDevice, std::vector<std::shared_ptr<GyroDeviceCommandObject>>& result ) = 0;
        virtual void GetGyroDeviceCommandCollectionByGyroDeviceAndTimestamp( const Guid& gyroDevice, const DateTime& timestamp, std::vector<std::shared_ptr<GyroDeviceCommandObject>>& result ) = 0;
        virtual void GetGyroDeviceCommandCollectionByGyroDeviceAtTimestamp( const Guid& gyroDevice, const DateTime& timestamp, std::vector<std::shared_ptr<GyroDeviceCommandObject>>& result ) = 0;
        virtual void GetGyroDeviceCommandCollectionByGyroDeviceFromTimestamp( const Guid& gyroDevice, const DateTime& timestamp, std::vector<std::shared_ptr<GyroDeviceCommandObject>>& result ) = 0;
        virtual void GetGyroDeviceCommandCollectionByGyroDeviceUntilTimestamp( const Guid& gyroDevice, const DateTime& timestamp, std::vector<std::shared_ptr<GyroDeviceCommandObject>>& result ) = 0;
        virtual void GetGyroDeviceCommandCollectionByGyroDeviceOverTimestamp( Guid gyroDevice, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<GyroDeviceCommandObject>>& result ) = 0;
        virtual void GetGyroDeviceCommandCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GyroDeviceCommandObject>>& result ) = 0;
        virtual void GetGyroDeviceCommandCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GyroDeviceCommandObject>>& result ) = 0;
        virtual void GetGyroDeviceCommandCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GyroDeviceCommandObject>>& result ) = 0;
        virtual void GetGyroDeviceCommandCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GyroDeviceCommandObject>>& result ) = 0;
        virtual void GetGyroDeviceCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<GyroDeviceCommandObject>>& result ) = 0;
        virtual void GetGyroDeviceCommandCollectionByReply( const DBGuid& reply, std::vector<std::shared_ptr<GyroDeviceCommandObject>>& result ) = 0;
        virtual void GetGyroDeviceCommandCollectionByReplyIsNull( std::vector<std::shared_ptr<GyroDeviceCommandObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // GyroDeviceCommandReply queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GyroDeviceCommandReplyObject> GetGyroDeviceCommandReplyById( const Guid& id ) = 0;
        virtual void GetGyroDeviceCommandReplyCollection( std::vector<std::shared_ptr<GyroDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetGyroDeviceCommandReplyCollectionByGyroDevice( const Guid& gyroDevice, std::vector<std::shared_ptr<GyroDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetGyroDeviceCommandReplyCollectionByGyroDeviceAndTimestamp( const Guid& gyroDevice, const DateTime& timestamp, std::vector<std::shared_ptr<GyroDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetGyroDeviceCommandReplyCollectionByGyroDeviceAtTimestamp( const Guid& gyroDevice, const DateTime& timestamp, std::vector<std::shared_ptr<GyroDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetGyroDeviceCommandReplyCollectionByGyroDeviceFromTimestamp( const Guid& gyroDevice, const DateTime& timestamp, std::vector<std::shared_ptr<GyroDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetGyroDeviceCommandReplyCollectionByGyroDeviceUntilTimestamp( const Guid& gyroDevice, const DateTime& timestamp, std::vector<std::shared_ptr<GyroDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetGyroDeviceCommandReplyCollectionByGyroDeviceOverTimestamp( Guid gyroDevice, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<GyroDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetGyroDeviceCommandReplyCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GyroDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetGyroDeviceCommandReplyCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GyroDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetGyroDeviceCommandReplyCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GyroDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetGyroDeviceCommandReplyCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GyroDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetGyroDeviceCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<GyroDeviceCommandReplyObject>>& result ) = 0;
        virtual std::shared_ptr<GyroDeviceCommandReplyObject> GetGyroDeviceCommandReplyByCommand( const DBGuid& command ) = 0;
        virtual void GetGyroDeviceCommandReplyCollectionByCommandIsNull( std::vector<std::shared_ptr<GyroDeviceCommandReplyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // GyroDeviceConfiguration queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GyroDeviceConfigurationObject> GetGyroDeviceConfigurationById( const Guid& id ) = 0;
        virtual void GetGyroDeviceConfigurationCollection( std::vector<std::shared_ptr<GyroDeviceConfigurationObject>>& result ) = 0;
        virtual void GetGyroDeviceConfigurationCollectionByGyroDevice( const Guid& gyroDevice, std::vector<std::shared_ptr<GyroDeviceConfigurationObject>>& result ) = 0;
        virtual std::shared_ptr<GyroDeviceConfigurationObject> GetGyroDeviceConfigurationByGyroDeviceAndTimestamp( const Guid& gyroDevice, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<GyroDeviceConfigurationObject> GetGyroDeviceConfigurationByGyroDeviceAtTimestamp( const Guid& gyroDevice, const DateTime& timestamp ) = 0;
        virtual void GetGyroDeviceConfigurationByGyroDeviceFromTimestamp( const Guid& gyroDevice, const DateTime& timestamp, std::vector<std::shared_ptr<GyroDeviceConfigurationObject>>& result ) = 0;
        virtual void GetGyroDeviceConfigurationByGyroDeviceUntilTimestamp( const Guid& gyroDevice, const DateTime& timestamp, std::vector<std::shared_ptr<GyroDeviceConfigurationObject>>& result ) = 0;
        virtual void GetGyroDeviceConfigurationByGyroDeviceOverTimestamp( Guid gyroDevice, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<GyroDeviceConfigurationObject>>& result ) = 0;
        virtual void GetGyroDeviceConfigurationCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GyroDeviceConfigurationObject>>& result ) = 0;
        virtual void GetGyroDeviceConfigurationCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GyroDeviceConfigurationObject>>& result ) = 0;
        virtual void GetGyroDeviceConfigurationCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GyroDeviceConfigurationObject>>& result ) = 0;
        virtual void GetGyroDeviceConfigurationCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<GyroDeviceConfigurationObject>>& result ) = 0;
        virtual void GetGyroDeviceConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<GyroDeviceConfigurationObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Identity queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<IdentityObject> GetIdentityById( const Guid& id ) = 0;
        virtual void GetIdentityCollection( std::vector<std::shared_ptr<IdentityObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Callsign queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CallsignObject> GetCallsignById( const Guid& id ) = 0;
        virtual void GetCallsignCollection( std::vector<std::shared_ptr<CallsignObject>>& result ) = 0;
        virtual std::shared_ptr<CallsignObject> GetCallsignByIdentifier( const FixedDBWideString<127>& identifier ) = 0;
        // ---------------------------------------------------------------------
        // InternationalMaritimeOrganizationNumber queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<InternationalMaritimeOrganizationNumberObject> GetInternationalMaritimeOrganizationNumberById( const Guid& id ) = 0;
        virtual void GetInternationalMaritimeOrganizationNumberCollection( std::vector<std::shared_ptr<InternationalMaritimeOrganizationNumberObject>>& result ) = 0;
        virtual std::shared_ptr<InternationalMaritimeOrganizationNumberObject> GetInternationalMaritimeOrganizationNumberByIdentifier( Int64 identifier ) = 0;
        virtual void GetInternationalMaritimeOrganizationNumberFromIdentifier( Int64 identifier, std::vector<std::shared_ptr<InternationalMaritimeOrganizationNumberObject>>& result ) = 0;
        virtual void GetInternationalMaritimeOrganizationNumberUntilIdentifier( Int64 identifier, std::vector<std::shared_ptr<InternationalMaritimeOrganizationNumberObject>>& result ) = 0;
        virtual void GetInternationalMaritimeOrganizationNumberOverIdentifier( Int64 fromIdentifier, Int64 untilIdentifier, std::vector<std::shared_ptr<InternationalMaritimeOrganizationNumberObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // MaritimeMobileServiceIdentity queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<MaritimeMobileServiceIdentityObject> GetMaritimeMobileServiceIdentityById( const Guid& id ) = 0;
        virtual void GetMaritimeMobileServiceIdentityCollection( std::vector<std::shared_ptr<MaritimeMobileServiceIdentityObject>>& result ) = 0;
        virtual std::shared_ptr<MaritimeMobileServiceIdentityObject> GetMaritimeMobileServiceIdentityByIdentifier( Int64 identifier ) = 0;
        virtual void GetMaritimeMobileServiceIdentityFromIdentifier( Int64 identifier, std::vector<std::shared_ptr<MaritimeMobileServiceIdentityObject>>& result ) = 0;
        virtual void GetMaritimeMobileServiceIdentityUntilIdentifier( Int64 identifier, std::vector<std::shared_ptr<MaritimeMobileServiceIdentityObject>>& result ) = 0;
        virtual void GetMaritimeMobileServiceIdentityOverIdentifier( Int64 fromIdentifier, Int64 untilIdentifier, std::vector<std::shared_ptr<MaritimeMobileServiceIdentityObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Name queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<NameObject> GetNameById( const Guid& id ) = 0;
        virtual void GetNameCollection( std::vector<std::shared_ptr<NameObject>>& result ) = 0;
        virtual std::shared_ptr<NameObject> GetNameByText( const FixedDBWideString<127>& text ) = 0;
        // ---------------------------------------------------------------------
        // Int16TimeseriesValue queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<Int16TimeseriesValueObject> GetInt16TimeseriesValueById( const Guid& id ) = 0;
        virtual void GetInt16TimeseriesValueCollection( std::vector<std::shared_ptr<Int16TimeseriesValueObject>>& result ) = 0;
        virtual void GetInt16TimeseriesValueCollectionByTimeseries( const Guid& timeseries, std::vector<std::shared_ptr<Int16TimeseriesValueObject>>& result ) = 0;
        virtual std::shared_ptr<Int16TimeseriesValueObject> GetInt16TimeseriesValueByTimeseriesAndTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<Int16TimeseriesValueObject> GetInt16TimeseriesValueByTimeseriesAtTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual void GetInt16TimeseriesValueByTimeseriesFromTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<Int16TimeseriesValueObject>>& result ) = 0;
        virtual void GetInt16TimeseriesValueByTimeseriesUntilTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<Int16TimeseriesValueObject>>& result ) = 0;
        virtual void GetInt16TimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<Int16TimeseriesValueObject>>& result ) = 0;
        virtual void GetInt16TimeseriesValueCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<Int16TimeseriesValueObject>>& result ) = 0;
        virtual void GetInt16TimeseriesValueCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<Int16TimeseriesValueObject>>& result ) = 0;
        virtual void GetInt16TimeseriesValueCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<Int16TimeseriesValueObject>>& result ) = 0;
        virtual void GetInt16TimeseriesValueCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<Int16TimeseriesValueObject>>& result ) = 0;
        virtual void GetInt16TimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<Int16TimeseriesValueObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Int32TimeseriesValue queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<Int32TimeseriesValueObject> GetInt32TimeseriesValueById( const Guid& id ) = 0;
        virtual void GetInt32TimeseriesValueCollection( std::vector<std::shared_ptr<Int32TimeseriesValueObject>>& result ) = 0;
        virtual void GetInt32TimeseriesValueCollectionByTimeseries( const Guid& timeseries, std::vector<std::shared_ptr<Int32TimeseriesValueObject>>& result ) = 0;
        virtual std::shared_ptr<Int32TimeseriesValueObject> GetInt32TimeseriesValueByTimeseriesAndTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<Int32TimeseriesValueObject> GetInt32TimeseriesValueByTimeseriesAtTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual void GetInt32TimeseriesValueByTimeseriesFromTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<Int32TimeseriesValueObject>>& result ) = 0;
        virtual void GetInt32TimeseriesValueByTimeseriesUntilTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<Int32TimeseriesValueObject>>& result ) = 0;
        virtual void GetInt32TimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<Int32TimeseriesValueObject>>& result ) = 0;
        virtual void GetInt32TimeseriesValueCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<Int32TimeseriesValueObject>>& result ) = 0;
        virtual void GetInt32TimeseriesValueCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<Int32TimeseriesValueObject>>& result ) = 0;
        virtual void GetInt32TimeseriesValueCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<Int32TimeseriesValueObject>>& result ) = 0;
        virtual void GetInt32TimeseriesValueCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<Int32TimeseriesValueObject>>& result ) = 0;
        virtual void GetInt32TimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<Int32TimeseriesValueObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Int64TimeseriesValue queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<Int64TimeseriesValueObject> GetInt64TimeseriesValueById( const Guid& id ) = 0;
        virtual void GetInt64TimeseriesValueCollection( std::vector<std::shared_ptr<Int64TimeseriesValueObject>>& result ) = 0;
        virtual void GetInt64TimeseriesValueCollectionByTimeseries( const Guid& timeseries, std::vector<std::shared_ptr<Int64TimeseriesValueObject>>& result ) = 0;
        virtual std::shared_ptr<Int64TimeseriesValueObject> GetInt64TimeseriesValueByTimeseriesAndTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<Int64TimeseriesValueObject> GetInt64TimeseriesValueByTimeseriesAtTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual void GetInt64TimeseriesValueByTimeseriesFromTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<Int64TimeseriesValueObject>>& result ) = 0;
        virtual void GetInt64TimeseriesValueByTimeseriesUntilTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<Int64TimeseriesValueObject>>& result ) = 0;
        virtual void GetInt64TimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<Int64TimeseriesValueObject>>& result ) = 0;
        virtual void GetInt64TimeseriesValueCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<Int64TimeseriesValueObject>>& result ) = 0;
        virtual void GetInt64TimeseriesValueCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<Int64TimeseriesValueObject>>& result ) = 0;
        virtual void GetInt64TimeseriesValueCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<Int64TimeseriesValueObject>>& result ) = 0;
        virtual void GetInt64TimeseriesValueCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<Int64TimeseriesValueObject>>& result ) = 0;
        virtual void GetInt64TimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<Int64TimeseriesValueObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Item queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ItemObject> GetItemById( const Guid& id ) = 0;
        virtual void GetItemCollection( std::vector<std::shared_ptr<ItemObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // BaseStation queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<BaseStationObject> GetBaseStationById( const Guid& id ) = 0;
        virtual void GetBaseStationCollection( std::vector<std::shared_ptr<BaseStationObject>>& result ) = 0;
        virtual std::shared_ptr<BaseStationObject> GetBaseStationByName( const FixedDBWideString<127>& name ) = 0;
        virtual void GetBaseStationCollectionByType( const DBGuid& type, std::vector<std::shared_ptr<BaseStationObject>>& result ) = 0;
        virtual void GetBaseStationCollectionByTypeIsNull( std::vector<std::shared_ptr<BaseStationObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Device queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<DeviceObject> GetDeviceById( const Guid& id ) = 0;
        virtual void GetDeviceCollection( std::vector<std::shared_ptr<DeviceObject>>& result ) = 0;
        virtual void GetDeviceCollectionByHost( const Guid& host, std::vector<std::shared_ptr<DeviceObject>>& result ) = 0;
        virtual std::shared_ptr<DeviceObject> GetDeviceByName( const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // CameraDevice queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CameraDeviceObject> GetCameraDeviceById( const Guid& id ) = 0;
        virtual void GetCameraDeviceCollection( std::vector<std::shared_ptr<CameraDeviceObject>>& result ) = 0;
        virtual void GetCameraDeviceCollectionByHost( const Guid& host, std::vector<std::shared_ptr<CameraDeviceObject>>& result ) = 0;
        virtual std::shared_ptr<CameraDeviceObject> GetCameraDeviceByName( const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // GNSSDevice queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GNSSDeviceObject> GetGNSSDeviceById( const Guid& id ) = 0;
        virtual void GetGNSSDeviceCollection( std::vector<std::shared_ptr<GNSSDeviceObject>>& result ) = 0;
        virtual void GetGNSSDeviceCollectionByHost( const Guid& host, std::vector<std::shared_ptr<GNSSDeviceObject>>& result ) = 0;
        virtual std::shared_ptr<GNSSDeviceObject> GetGNSSDeviceByName( const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // GyroDevice queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GyroDeviceObject> GetGyroDeviceById( const Guid& id ) = 0;
        virtual void GetGyroDeviceCollection( std::vector<std::shared_ptr<GyroDeviceObject>>& result ) = 0;
        virtual void GetGyroDeviceCollectionByHost( const Guid& host, std::vector<std::shared_ptr<GyroDeviceObject>>& result ) = 0;
        virtual std::shared_ptr<GyroDeviceObject> GetGyroDeviceByName( const FixedDBWideString<127>& name ) = 0;
        virtual void GetGyroDeviceCollectionByGNSSDevice( const DBGuid& gNSSDevice, std::vector<std::shared_ptr<GyroDeviceObject>>& result ) = 0;
        virtual void GetGyroDeviceCollectionByGNSSDeviceIsNull( std::vector<std::shared_ptr<GyroDeviceObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // LineInputDevice queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<LineInputDeviceObject> GetLineInputDeviceById( const Guid& id ) = 0;
        virtual void GetLineInputDeviceCollection( std::vector<std::shared_ptr<LineInputDeviceObject>>& result ) = 0;
        virtual void GetLineInputDeviceCollectionByHost( const Guid& host, std::vector<std::shared_ptr<LineInputDeviceObject>>& result ) = 0;
        virtual std::shared_ptr<LineInputDeviceObject> GetLineInputDeviceByName( const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // OilSpillDetectorDevice queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<OilSpillDetectorDeviceObject> GetOilSpillDetectorDeviceById( const Guid& id ) = 0;
        virtual void GetOilSpillDetectorDeviceCollection( std::vector<std::shared_ptr<OilSpillDetectorDeviceObject>>& result ) = 0;
        virtual void GetOilSpillDetectorDeviceCollectionByHost( const Guid& host, std::vector<std::shared_ptr<OilSpillDetectorDeviceObject>>& result ) = 0;
        virtual std::shared_ptr<OilSpillDetectorDeviceObject> GetOilSpillDetectorDeviceByName( const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // RadioDevice queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadioDeviceObject> GetRadioDeviceById( const Guid& id ) = 0;
        virtual void GetRadioDeviceCollection( std::vector<std::shared_ptr<RadioDeviceObject>>& result ) = 0;
        virtual void GetRadioDeviceCollectionByHost( const Guid& host, std::vector<std::shared_ptr<RadioDeviceObject>>& result ) = 0;
        virtual std::shared_ptr<RadioDeviceObject> GetRadioDeviceByName( const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // RadomeDevice queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadomeDeviceObject> GetRadomeDeviceById( const Guid& id ) = 0;
        virtual void GetRadomeDeviceCollection( std::vector<std::shared_ptr<RadomeDeviceObject>>& result ) = 0;
        virtual void GetRadomeDeviceCollectionByHost( const Guid& host, std::vector<std::shared_ptr<RadomeDeviceObject>>& result ) = 0;
        virtual std::shared_ptr<RadomeDeviceObject> GetRadomeDeviceByName( const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadomeDeviceCollectionByRadar( const DBGuid& radar, std::vector<std::shared_ptr<RadomeDeviceObject>>& result ) = 0;
        virtual void GetRadomeDeviceCollectionByRadarIsNull( std::vector<std::shared_ptr<RadomeDeviceObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // TrackerDevice queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<TrackerDeviceObject> GetTrackerDeviceById( const Guid& id ) = 0;
        virtual void GetTrackerDeviceCollection( std::vector<std::shared_ptr<TrackerDeviceObject>>& result ) = 0;
        virtual void GetTrackerDeviceCollectionByHost( const Guid& host, std::vector<std::shared_ptr<TrackerDeviceObject>>& result ) = 0;
        virtual std::shared_ptr<TrackerDeviceObject> GetTrackerDeviceByName( const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // AisDevice queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisDeviceObject> GetAisDeviceById( const Guid& id ) = 0;
        virtual void GetAisDeviceCollection( std::vector<std::shared_ptr<AisDeviceObject>>& result ) = 0;
        virtual void GetAisDeviceCollectionByHost( const Guid& host, std::vector<std::shared_ptr<AisDeviceObject>>& result ) = 0;
        virtual std::shared_ptr<AisDeviceObject> GetAisDeviceByName( const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // RadarDevice queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarDeviceObject> GetRadarDeviceById( const Guid& id ) = 0;
        virtual void GetRadarDeviceCollection( std::vector<std::shared_ptr<RadarDeviceObject>>& result ) = 0;
        virtual void GetRadarDeviceCollectionByHost( const Guid& host, std::vector<std::shared_ptr<RadarDeviceObject>>& result ) = 0;
        virtual std::shared_ptr<RadarDeviceObject> GetRadarDeviceByName( const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadarDeviceCollectionByRadome( const DBGuid& radome, std::vector<std::shared_ptr<RadarDeviceObject>>& result ) = 0;
        virtual void GetRadarDeviceCollectionByRadomeIsNull( std::vector<std::shared_ptr<RadarDeviceObject>>& result ) = 0;
        virtual void GetRadarDeviceCollectionByGNSSDevice( const DBGuid& gNSSDevice, std::vector<std::shared_ptr<RadarDeviceObject>>& result ) = 0;
        virtual void GetRadarDeviceCollectionByGNSSDeviceIsNull( std::vector<std::shared_ptr<RadarDeviceObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // WeatherStationDevice queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<WeatherStationDeviceObject> GetWeatherStationDeviceById( const Guid& id ) = 0;
        virtual void GetWeatherStationDeviceCollection( std::vector<std::shared_ptr<WeatherStationDeviceObject>>& result ) = 0;
        virtual void GetWeatherStationDeviceCollectionByHost( const Guid& host, std::vector<std::shared_ptr<WeatherStationDeviceObject>>& result ) = 0;
        virtual std::shared_ptr<WeatherStationDeviceObject> GetWeatherStationDeviceByName( const FixedDBWideString<127>& name ) = 0;
        virtual void GetWeatherStationDeviceCollectionByGyro( const DBGuid& gyro, std::vector<std::shared_ptr<WeatherStationDeviceObject>>& result ) = 0;
        virtual void GetWeatherStationDeviceCollectionByGyroIsNull( std::vector<std::shared_ptr<WeatherStationDeviceObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Facility queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<FacilityObject> GetFacilityById( const Guid& id ) = 0;
        virtual void GetFacilityCollection( std::vector<std::shared_ptr<FacilityObject>>& result ) = 0;
        virtual std::shared_ptr<FacilityObject> GetFacilityByName( const FixedDBWideString<127>& name ) = 0;
        virtual void GetFacilityCollectionByType( const DBGuid& type, std::vector<std::shared_ptr<FacilityObject>>& result ) = 0;
        virtual void GetFacilityCollectionByTypeIsNull( std::vector<std::shared_ptr<FacilityObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // TrackableItem queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<TrackableItemObject> GetTrackableItemById( const Guid& id ) = 0;
        virtual void GetTrackableItemCollection( std::vector<std::shared_ptr<TrackableItemObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Aircraft queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AircraftObject> GetAircraftById( const Guid& id ) = 0;
        virtual void GetAircraftCollection( std::vector<std::shared_ptr<AircraftObject>>& result ) = 0;
        virtual void GetAircraftCollectionByName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<AircraftObject>>& result ) = 0;
        virtual void GetAircraftCollectionByType( const DBGuid& type, std::vector<std::shared_ptr<AircraftObject>>& result ) = 0;
        virtual void GetAircraftCollectionByTypeIsNull( std::vector<std::shared_ptr<AircraftObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisAidToNavigation queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisAidToNavigationObject> GetAisAidToNavigationById( const Guid& id ) = 0;
        virtual void GetAisAidToNavigationCollection( std::vector<std::shared_ptr<AisAidToNavigationObject>>& result ) = 0;
        virtual std::shared_ptr<AisAidToNavigationObject> GetAisAidToNavigationByName( const FixedDBWideString<127>& name ) = 0;
        virtual void GetAisAidToNavigationCollectionByMMSI( const DBGuid& mMSI, std::vector<std::shared_ptr<AisAidToNavigationObject>>& result ) = 0;
        virtual void GetAisAidToNavigationCollectionByMMSIIsNull( std::vector<std::shared_ptr<AisAidToNavigationObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Vehicle queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<VehicleObject> GetVehicleById( const Guid& id ) = 0;
        virtual void GetVehicleCollection( std::vector<std::shared_ptr<VehicleObject>>& result ) = 0;
        virtual std::shared_ptr<VehicleObject> GetVehicleByName( const FixedDBWideString<127>& name ) = 0;
        virtual void GetVehicleCollectionByType( const DBGuid& type, std::vector<std::shared_ptr<VehicleObject>>& result ) = 0;
        virtual void GetVehicleCollectionByTypeIsNull( std::vector<std::shared_ptr<VehicleObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Vessel queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<VesselObject> GetVesselById( const Guid& id ) = 0;
        virtual void GetVesselCollection( std::vector<std::shared_ptr<VesselObject>>& result ) = 0;
        virtual void GetVesselCollectionByName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<VesselObject>>& result ) = 0;
        virtual void GetVesselCollectionByType( const DBGuid& type, std::vector<std::shared_ptr<VesselObject>>& result ) = 0;
        virtual void GetVesselCollectionByTypeIsNull( std::vector<std::shared_ptr<VesselObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // ItemIdentityLink queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ItemIdentityLinkObject> GetItemIdentityLinkById( const Guid& id ) = 0;
        virtual void GetItemIdentityLinkCollection( std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByItem( const Guid& item, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByItemAndStart( const Guid& item, const DateTime& start, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByItemAtStart( const Guid& item, const DateTime& start, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByItemFromStart( const Guid& item, const DateTime& start, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByItemUntilStart( const Guid& item, const DateTime& start, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByItemOverStart( Guid item, DateTime fromStart, DateTime untilStart, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByItemAndEnd( const Guid& item, const DBDateTime& end, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByItemAndEndIsNull( const Guid& item, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByItemAtEnd( const Guid& item, const DBDateTime& end, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByItemFromEnd( const Guid& item, const DBDateTime& end, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByItemUntilEnd( const Guid& item, const DBDateTime& end, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByItemOverEnd( Guid item, DateTime fromEnd, DateTime untilEnd, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByIdentity( const Guid& identity, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByIdentityAndStart( const Guid& identity, const DateTime& start, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByIdentityAtStart( const Guid& identity, const DateTime& start, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByIdentityFromStart( const Guid& identity, const DateTime& start, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByIdentityUntilStart( const Guid& identity, const DateTime& start, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByIdentityOverStart( Guid identity, DateTime fromStart, DateTime untilStart, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByIdentityAndEnd( const Guid& identity, const DBDateTime& end, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByIdentityAndEndIsNull( const Guid& identity, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByIdentityAtEnd( const Guid& identity, const DBDateTime& end, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByIdentityFromEnd( const Guid& identity, const DBDateTime& end, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByIdentityUntilEnd( const Guid& identity, const DBDateTime& end, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByIdentityOverEnd( Guid identity, DateTime fromEnd, DateTime untilEnd, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByStart( const DateTime& start, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionAtStart( const DateTime& start, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionFromStart( const DateTime& start, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionUntilStart( const DateTime& start, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionOverStart( DateTime fromStart, DateTime untilStart, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByEnd( const DBDateTime& end, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionByEndIsNull( std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionAtEnd( const DBDateTime& end, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionFromEnd( const DBDateTime& end, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionUntilEnd( const DBDateTime& end, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        virtual void GetItemIdentityLinkCollectionOverEnd( DateTime fromEnd, DateTime untilEnd, std::vector<std::shared_ptr<ItemIdentityLinkObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // ItemParentChildLink queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ItemParentChildLinkObject> GetItemParentChildLinkById( const Guid& id ) = 0;
        virtual void GetItemParentChildLinkCollection( std::vector<std::shared_ptr<ItemParentChildLinkObject>>& result ) = 0;
        virtual void GetItemParentChildLinkCollectionByParent( const Guid& parent, std::vector<std::shared_ptr<ItemParentChildLinkObject>>& result ) = 0;
        virtual std::shared_ptr<ItemParentChildLinkObject> GetItemParentChildLinkByParentAndTimestamp( const Guid& parent, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<ItemParentChildLinkObject> GetItemParentChildLinkByParentAtTimestamp( const Guid& parent, const DateTime& timestamp ) = 0;
        virtual void GetItemParentChildLinkByParentFromTimestamp( const Guid& parent, const DateTime& timestamp, std::vector<std::shared_ptr<ItemParentChildLinkObject>>& result ) = 0;
        virtual void GetItemParentChildLinkByParentUntilTimestamp( const Guid& parent, const DateTime& timestamp, std::vector<std::shared_ptr<ItemParentChildLinkObject>>& result ) = 0;
        virtual void GetItemParentChildLinkByParentOverTimestamp( Guid parent, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<ItemParentChildLinkObject>>& result ) = 0;
        virtual void GetItemParentChildLinkCollectionByChild( const Guid& child, std::vector<std::shared_ptr<ItemParentChildLinkObject>>& result ) = 0;
        virtual std::shared_ptr<ItemParentChildLinkObject> GetItemParentChildLinkByChildAndTimestamp( const Guid& child, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<ItemParentChildLinkObject> GetItemParentChildLinkByChildAtTimestamp( const Guid& child, const DateTime& timestamp ) = 0;
        virtual void GetItemParentChildLinkByChildFromTimestamp( const Guid& child, const DateTime& timestamp, std::vector<std::shared_ptr<ItemParentChildLinkObject>>& result ) = 0;
        virtual void GetItemParentChildLinkByChildUntilTimestamp( const Guid& child, const DateTime& timestamp, std::vector<std::shared_ptr<ItemParentChildLinkObject>>& result ) = 0;
        virtual void GetItemParentChildLinkByChildOverTimestamp( Guid child, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<ItemParentChildLinkObject>>& result ) = 0;
        virtual void GetItemParentChildLinkCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<ItemParentChildLinkObject>>& result ) = 0;
        virtual void GetItemParentChildLinkCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<ItemParentChildLinkObject>>& result ) = 0;
        virtual void GetItemParentChildLinkCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<ItemParentChildLinkObject>>& result ) = 0;
        virtual void GetItemParentChildLinkCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<ItemParentChildLinkObject>>& result ) = 0;
        virtual void GetItemParentChildLinkCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<ItemParentChildLinkObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // LineInputDeviceCommand queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<LineInputDeviceCommandObject> GetLineInputDeviceCommandById( const Guid& id ) = 0;
        virtual void GetLineInputDeviceCommandCollection( std::vector<std::shared_ptr<LineInputDeviceCommandObject>>& result ) = 0;
        virtual void GetLineInputDeviceCommandCollectionByLineInputDevice( const Guid& lineInputDevice, std::vector<std::shared_ptr<LineInputDeviceCommandObject>>& result ) = 0;
        virtual void GetLineInputDeviceCommandCollectionByLineInputDeviceAndTimestamp( const Guid& lineInputDevice, const DateTime& timestamp, std::vector<std::shared_ptr<LineInputDeviceCommandObject>>& result ) = 0;
        virtual void GetLineInputDeviceCommandCollectionByLineInputDeviceAtTimestamp( const Guid& lineInputDevice, const DateTime& timestamp, std::vector<std::shared_ptr<LineInputDeviceCommandObject>>& result ) = 0;
        virtual void GetLineInputDeviceCommandCollectionByLineInputDeviceFromTimestamp( const Guid& lineInputDevice, const DateTime& timestamp, std::vector<std::shared_ptr<LineInputDeviceCommandObject>>& result ) = 0;
        virtual void GetLineInputDeviceCommandCollectionByLineInputDeviceUntilTimestamp( const Guid& lineInputDevice, const DateTime& timestamp, std::vector<std::shared_ptr<LineInputDeviceCommandObject>>& result ) = 0;
        virtual void GetLineInputDeviceCommandCollectionByLineInputDeviceOverTimestamp( Guid lineInputDevice, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<LineInputDeviceCommandObject>>& result ) = 0;
        virtual void GetLineInputDeviceCommandCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<LineInputDeviceCommandObject>>& result ) = 0;
        virtual void GetLineInputDeviceCommandCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<LineInputDeviceCommandObject>>& result ) = 0;
        virtual void GetLineInputDeviceCommandCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<LineInputDeviceCommandObject>>& result ) = 0;
        virtual void GetLineInputDeviceCommandCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<LineInputDeviceCommandObject>>& result ) = 0;
        virtual void GetLineInputDeviceCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<LineInputDeviceCommandObject>>& result ) = 0;
        virtual void GetLineInputDeviceCommandCollectionByReply( const DBGuid& reply, std::vector<std::shared_ptr<LineInputDeviceCommandObject>>& result ) = 0;
        virtual void GetLineInputDeviceCommandCollectionByReplyIsNull( std::vector<std::shared_ptr<LineInputDeviceCommandObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // LineInputDeviceCommandReply queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<LineInputDeviceCommandReplyObject> GetLineInputDeviceCommandReplyById( const Guid& id ) = 0;
        virtual void GetLineInputDeviceCommandReplyCollection( std::vector<std::shared_ptr<LineInputDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetLineInputDeviceCommandReplyCollectionByLineInputDevice( const Guid& lineInputDevice, std::vector<std::shared_ptr<LineInputDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetLineInputDeviceCommandReplyCollectionByLineInputDeviceAndTimestamp( const Guid& lineInputDevice, const DateTime& timestamp, std::vector<std::shared_ptr<LineInputDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetLineInputDeviceCommandReplyCollectionByLineInputDeviceAtTimestamp( const Guid& lineInputDevice, const DateTime& timestamp, std::vector<std::shared_ptr<LineInputDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetLineInputDeviceCommandReplyCollectionByLineInputDeviceFromTimestamp( const Guid& lineInputDevice, const DateTime& timestamp, std::vector<std::shared_ptr<LineInputDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetLineInputDeviceCommandReplyCollectionByLineInputDeviceUntilTimestamp( const Guid& lineInputDevice, const DateTime& timestamp, std::vector<std::shared_ptr<LineInputDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetLineInputDeviceCommandReplyCollectionByLineInputDeviceOverTimestamp( Guid lineInputDevice, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<LineInputDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetLineInputDeviceCommandReplyCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<LineInputDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetLineInputDeviceCommandReplyCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<LineInputDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetLineInputDeviceCommandReplyCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<LineInputDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetLineInputDeviceCommandReplyCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<LineInputDeviceCommandReplyObject>>& result ) = 0;
        virtual void GetLineInputDeviceCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<LineInputDeviceCommandReplyObject>>& result ) = 0;
        virtual std::shared_ptr<LineInputDeviceCommandReplyObject> GetLineInputDeviceCommandReplyByCommand( const DBGuid& command ) = 0;
        virtual void GetLineInputDeviceCommandReplyCollectionByCommandIsNull( std::vector<std::shared_ptr<LineInputDeviceCommandReplyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // LineInputDeviceConfiguration queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<LineInputDeviceConfigurationObject> GetLineInputDeviceConfigurationById( const Guid& id ) = 0;
        virtual void GetLineInputDeviceConfigurationCollection( std::vector<std::shared_ptr<LineInputDeviceConfigurationObject>>& result ) = 0;
        virtual void GetLineInputDeviceConfigurationCollectionByLineInputDevice( const Guid& lineInputDevice, std::vector<std::shared_ptr<LineInputDeviceConfigurationObject>>& result ) = 0;
        virtual std::shared_ptr<LineInputDeviceConfigurationObject> GetLineInputDeviceConfigurationByLineInputDeviceAndTimestamp( const Guid& lineInputDevice, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<LineInputDeviceConfigurationObject> GetLineInputDeviceConfigurationByLineInputDeviceAtTimestamp( const Guid& lineInputDevice, const DateTime& timestamp ) = 0;
        virtual void GetLineInputDeviceConfigurationByLineInputDeviceFromTimestamp( const Guid& lineInputDevice, const DateTime& timestamp, std::vector<std::shared_ptr<LineInputDeviceConfigurationObject>>& result ) = 0;
        virtual void GetLineInputDeviceConfigurationByLineInputDeviceUntilTimestamp( const Guid& lineInputDevice, const DateTime& timestamp, std::vector<std::shared_ptr<LineInputDeviceConfigurationObject>>& result ) = 0;
        virtual void GetLineInputDeviceConfigurationByLineInputDeviceOverTimestamp( Guid lineInputDevice, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<LineInputDeviceConfigurationObject>>& result ) = 0;
        virtual void GetLineInputDeviceConfigurationCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<LineInputDeviceConfigurationObject>>& result ) = 0;
        virtual void GetLineInputDeviceConfigurationCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<LineInputDeviceConfigurationObject>>& result ) = 0;
        virtual void GetLineInputDeviceConfigurationCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<LineInputDeviceConfigurationObject>>& result ) = 0;
        virtual void GetLineInputDeviceConfigurationCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<LineInputDeviceConfigurationObject>>& result ) = 0;
        virtual void GetLineInputDeviceConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<LineInputDeviceConfigurationObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // LineInputMessageRouting queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<LineInputMessageRoutingObject> GetLineInputMessageRoutingById( const Guid& id ) = 0;
        virtual void GetLineInputMessageRoutingCollection( std::vector<std::shared_ptr<LineInputMessageRoutingObject>>& result ) = 0;
        virtual void GetLineInputMessageRoutingCollectionByLineInputDevice( const Guid& lineInputDevice, std::vector<std::shared_ptr<LineInputMessageRoutingObject>>& result ) = 0;
        virtual std::shared_ptr<LineInputMessageRoutingObject> GetLineInputMessageRoutingByLineInputDeviceAndType( const Guid& lineInputDevice, const FixedDBWideString<127>& type ) = 0;
        // ---------------------------------------------------------------------
        // LineInputMessageRoutingDestination queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<LineInputMessageRoutingDestinationObject> GetLineInputMessageRoutingDestinationById( const Guid& id ) = 0;
        virtual void GetLineInputMessageRoutingDestinationCollection( std::vector<std::shared_ptr<LineInputMessageRoutingDestinationObject>>& result ) = 0;
        virtual void GetLineInputMessageRoutingDestinationCollectionByRouting( const Guid& routing, std::vector<std::shared_ptr<LineInputMessageRoutingDestinationObject>>& result ) = 0;
        virtual std::shared_ptr<LineInputMessageRoutingDestinationObject> GetLineInputMessageRoutingDestinationByRoutingAndListener( const Guid& routing, const DBGuid& listener ) = 0;
        virtual void GetLineInputMessageRoutingDestinationCollectionByRoutingAndListenerIsNull( const Guid& routing, std::vector<std::shared_ptr<LineInputMessageRoutingDestinationObject>>& result ) = 0;
        virtual void GetLineInputMessageRoutingDestinationCollectionByListener( const DBGuid& listener, std::vector<std::shared_ptr<LineInputMessageRoutingDestinationObject>>& result ) = 0;
        virtual void GetLineInputMessageRoutingDestinationCollectionByListenerIsNull( std::vector<std::shared_ptr<LineInputMessageRoutingDestinationObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // LineInputWhiteListEntry queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<LineInputWhiteListEntryObject> GetLineInputWhiteListEntryById( const Guid& id ) = 0;
        virtual void GetLineInputWhiteListEntryCollection( std::vector<std::shared_ptr<LineInputWhiteListEntryObject>>& result ) = 0;
        virtual void GetLineInputWhiteListEntryCollectionByLineInputDevice( const Guid& lineInputDevice, std::vector<std::shared_ptr<LineInputWhiteListEntryObject>>& result ) = 0;
        virtual void GetLineInputWhiteListEntryCollectionByLineInputDeviceAndHostName( const Guid& lineInputDevice, const FixedDBWideString<128>& hostName, std::vector<std::shared_ptr<LineInputWhiteListEntryObject>>& result ) = 0;
        virtual std::shared_ptr<LineInputWhiteListEntryObject> GetLineInputWhiteListEntryByLineInputDeviceHostNameAndPort( const Guid& lineInputDevice, const FixedDBWideString<128>& hostName, Int32 port ) = 0;
        virtual void GetLineInputWhiteListEntryByLineInputDeviceHostNameFromPort( const Guid& lineInputDevice, const FixedDBWideString<128>& hostName, Int32 port, std::vector<std::shared_ptr<LineInputWhiteListEntryObject>>& result ) = 0;
        virtual void GetLineInputWhiteListEntryByLineInputDeviceHostNameUntilPort( const Guid& lineInputDevice, const FixedDBWideString<128>& hostName, Int32 port, std::vector<std::shared_ptr<LineInputWhiteListEntryObject>>& result ) = 0;
        virtual void GetLineInputWhiteListEntryByLineInputDeviceHostNameOverPort( Guid lineInputDevice, FixedDBWideString<128> hostName, Int32 fromPort, Int32 untilPort, std::vector<std::shared_ptr<LineInputWhiteListEntryObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // LogApplication queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<LogApplicationObject> GetLogApplicationById( const Guid& id ) = 0;
        virtual void GetLogApplicationCollection( std::vector<std::shared_ptr<LogApplicationObject>>& result ) = 0;
        virtual std::shared_ptr<LogApplicationObject> GetLogApplicationByName( const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // LogApplicationConfiguration queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<LogApplicationConfigurationObject> GetLogApplicationConfigurationById( const Guid& id ) = 0;
        virtual void GetLogApplicationConfigurationCollection( std::vector<std::shared_ptr<LogApplicationConfigurationObject>>& result ) = 0;
        virtual void GetLogApplicationConfigurationCollectionByApplication( const Guid& application, std::vector<std::shared_ptr<LogApplicationConfigurationObject>>& result ) = 0;
        virtual std::shared_ptr<LogApplicationConfigurationObject> GetLogApplicationConfigurationByApplicationAndTimestamp( const Guid& application, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<LogApplicationConfigurationObject> GetLogApplicationConfigurationByApplicationAtTimestamp( const Guid& application, const DateTime& timestamp ) = 0;
        virtual void GetLogApplicationConfigurationByApplicationFromTimestamp( const Guid& application, const DateTime& timestamp, std::vector<std::shared_ptr<LogApplicationConfigurationObject>>& result ) = 0;
        virtual void GetLogApplicationConfigurationByApplicationUntilTimestamp( const Guid& application, const DateTime& timestamp, std::vector<std::shared_ptr<LogApplicationConfigurationObject>>& result ) = 0;
        virtual void GetLogApplicationConfigurationByApplicationOverTimestamp( Guid application, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<LogApplicationConfigurationObject>>& result ) = 0;
        virtual void GetLogApplicationConfigurationCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<LogApplicationConfigurationObject>>& result ) = 0;
        virtual void GetLogApplicationConfigurationCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<LogApplicationConfigurationObject>>& result ) = 0;
        virtual void GetLogApplicationConfigurationCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<LogApplicationConfigurationObject>>& result ) = 0;
        virtual void GetLogApplicationConfigurationCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<LogApplicationConfigurationObject>>& result ) = 0;
        virtual void GetLogApplicationConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<LogApplicationConfigurationObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // LogHost queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<LogHostObject> GetLogHostById( const Guid& id ) = 0;
        virtual void GetLogHostCollection( std::vector<std::shared_ptr<LogHostObject>>& result ) = 0;
        virtual std::shared_ptr<LogHostObject> GetLogHostByComputerName( const FixedDBWideString<127>& computerName ) = 0;
        // ---------------------------------------------------------------------
        // LogHostConfiguration queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<LogHostConfigurationObject> GetLogHostConfigurationById( const Guid& id ) = 0;
        virtual void GetLogHostConfigurationCollection( std::vector<std::shared_ptr<LogHostConfigurationObject>>& result ) = 0;
        virtual void GetLogHostConfigurationCollectionByHost( const Guid& host, std::vector<std::shared_ptr<LogHostConfigurationObject>>& result ) = 0;
        virtual std::shared_ptr<LogHostConfigurationObject> GetLogHostConfigurationByHostAndTimestamp( const Guid& host, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<LogHostConfigurationObject> GetLogHostConfigurationByHostAtTimestamp( const Guid& host, const DateTime& timestamp ) = 0;
        virtual void GetLogHostConfigurationByHostFromTimestamp( const Guid& host, const DateTime& timestamp, std::vector<std::shared_ptr<LogHostConfigurationObject>>& result ) = 0;
        virtual void GetLogHostConfigurationByHostUntilTimestamp( const Guid& host, const DateTime& timestamp, std::vector<std::shared_ptr<LogHostConfigurationObject>>& result ) = 0;
        virtual void GetLogHostConfigurationByHostOverTimestamp( Guid host, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<LogHostConfigurationObject>>& result ) = 0;
        virtual void GetLogHostConfigurationCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<LogHostConfigurationObject>>& result ) = 0;
        virtual void GetLogHostConfigurationCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<LogHostConfigurationObject>>& result ) = 0;
        virtual void GetLogHostConfigurationCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<LogHostConfigurationObject>>& result ) = 0;
        virtual void GetLogHostConfigurationCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<LogHostConfigurationObject>>& result ) = 0;
        virtual void GetLogHostConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<LogHostConfigurationObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // LogLocation queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<LogLocationObject> GetLogLocationById( const Guid& id ) = 0;
        virtual void GetLogLocationCollection( std::vector<std::shared_ptr<LogLocationObject>>& result ) = 0;
        virtual void GetLogLocationCollectionByFileName( const FixedDBWideString<260>& fileName, std::vector<std::shared_ptr<LogLocationObject>>& result ) = 0;
        virtual std::shared_ptr<LogLocationObject> GetLogLocationByFileNameAndLineNumber( const FixedDBWideString<260>& fileName, Int32 lineNumber ) = 0;
        virtual void GetLogLocationByFileNameFromLineNumber( const FixedDBWideString<260>& fileName, Int32 lineNumber, std::vector<std::shared_ptr<LogLocationObject>>& result ) = 0;
        virtual void GetLogLocationByFileNameUntilLineNumber( const FixedDBWideString<260>& fileName, Int32 lineNumber, std::vector<std::shared_ptr<LogLocationObject>>& result ) = 0;
        virtual void GetLogLocationByFileNameOverLineNumber( FixedDBWideString<260> fileName, Int32 fromLineNumber, Int32 untilLineNumber, std::vector<std::shared_ptr<LogLocationObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // LogProcess queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<LogProcessObject> GetLogProcessById( const Guid& id ) = 0;
        virtual void GetLogProcessCollection( std::vector<std::shared_ptr<LogProcessObject>>& result ) = 0;
        virtual void GetLogProcessCollectionByApplication( const Guid& application, std::vector<std::shared_ptr<LogProcessObject>>& result ) = 0;
        virtual void GetLogProcessCollectionByApplicationAndStarted( const Guid& application, const DateTime& started, std::vector<std::shared_ptr<LogProcessObject>>& result ) = 0;
        virtual void GetLogProcessCollectionByApplicationAtStarted( const Guid& application, const DateTime& started, std::vector<std::shared_ptr<LogProcessObject>>& result ) = 0;
        virtual void GetLogProcessCollectionByApplicationFromStarted( const Guid& application, const DateTime& started, std::vector<std::shared_ptr<LogProcessObject>>& result ) = 0;
        virtual void GetLogProcessCollectionByApplicationUntilStarted( const Guid& application, const DateTime& started, std::vector<std::shared_ptr<LogProcessObject>>& result ) = 0;
        virtual void GetLogProcessCollectionByApplicationOverStarted( Guid application, DateTime fromStarted, DateTime untilStarted, std::vector<std::shared_ptr<LogProcessObject>>& result ) = 0;
        virtual void GetLogProcessCollectionByHost( const DBGuid& host, std::vector<std::shared_ptr<LogProcessObject>>& result ) = 0;
        virtual void GetLogProcessCollectionByHostIsNull( std::vector<std::shared_ptr<LogProcessObject>>& result ) = 0;
        virtual void GetLogProcessCollectionByHostAndStarted( const DBGuid& host, const DateTime& started, std::vector<std::shared_ptr<LogProcessObject>>& result ) = 0;
        virtual void GetLogProcessCollectionByHostIsNullAndStarted( const DateTime& started, std::vector<std::shared_ptr<LogProcessObject>>& result ) = 0;
        virtual void GetLogProcessCollectionByHostAtStarted( const DBGuid& host, const DateTime& started, std::vector<std::shared_ptr<LogProcessObject>>& result ) = 0;
        virtual void GetLogProcessCollectionByHostFromStarted( const DBGuid& host, const DateTime& started, std::vector<std::shared_ptr<LogProcessObject>>& result ) = 0;
        virtual void GetLogProcessCollectionByHostUntilStarted( const DBGuid& host, const DateTime& started, std::vector<std::shared_ptr<LogProcessObject>>& result ) = 0;
        virtual void GetLogProcessCollectionByHostOverStarted( Guid host, DateTime fromStarted, DateTime untilStarted, std::vector<std::shared_ptr<LogProcessObject>>& result ) = 0;
        virtual void GetLogProcessCollectionByStarted( const DateTime& started, std::vector<std::shared_ptr<LogProcessObject>>& result ) = 0;
        virtual void GetLogProcessCollectionAtStarted( const DateTime& started, std::vector<std::shared_ptr<LogProcessObject>>& result ) = 0;
        virtual void GetLogProcessCollectionFromStarted( const DateTime& started, std::vector<std::shared_ptr<LogProcessObject>>& result ) = 0;
        virtual void GetLogProcessCollectionUntilStarted( const DateTime& started, std::vector<std::shared_ptr<LogProcessObject>>& result ) = 0;
        virtual void GetLogProcessCollectionOverStarted( DateTime fromStarted, DateTime untilStarted, std::vector<std::shared_ptr<LogProcessObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // LogRecord queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<LogRecordObject> GetLogRecordById( const Guid& id ) = 0;
        virtual void GetLogRecordCollection( std::vector<std::shared_ptr<LogRecordObject>>& result ) = 0;
        virtual void GetLogRecordCollectionByThread( const Guid& thread, std::vector<std::shared_ptr<LogRecordObject>>& result ) = 0;
        virtual void GetLogRecordCollectionByThreadAndTimestamp( const Guid& thread, const DateTime& timestamp, std::vector<std::shared_ptr<LogRecordObject>>& result ) = 0;
        virtual void GetLogRecordCollectionByThreadAtTimestamp( const Guid& thread, const DateTime& timestamp, std::vector<std::shared_ptr<LogRecordObject>>& result ) = 0;
        virtual void GetLogRecordCollectionByThreadFromTimestamp( const Guid& thread, const DateTime& timestamp, std::vector<std::shared_ptr<LogRecordObject>>& result ) = 0;
        virtual void GetLogRecordCollectionByThreadUntilTimestamp( const Guid& thread, const DateTime& timestamp, std::vector<std::shared_ptr<LogRecordObject>>& result ) = 0;
        virtual void GetLogRecordCollectionByThreadOverTimestamp( Guid thread, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<LogRecordObject>>& result ) = 0;
        virtual void GetLogRecordCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<LogRecordObject>>& result ) = 0;
        virtual void GetLogRecordCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<LogRecordObject>>& result ) = 0;
        virtual void GetLogRecordCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<LogRecordObject>>& result ) = 0;
        virtual void GetLogRecordCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<LogRecordObject>>& result ) = 0;
        virtual void GetLogRecordCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<LogRecordObject>>& result ) = 0;
        virtual void GetLogRecordCollectionByLocation( const Guid& location, std::vector<std::shared_ptr<LogRecordObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // LogThread queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<LogThreadObject> GetLogThreadById( const Guid& id ) = 0;
        virtual void GetLogThreadCollection( std::vector<std::shared_ptr<LogThreadObject>>& result ) = 0;
        virtual void GetLogThreadCollectionByProcess( const Guid& process, std::vector<std::shared_ptr<LogThreadObject>>& result ) = 0;
        virtual void GetLogThreadCollectionByProcessAndStarted( const Guid& process, const DateTime& started, std::vector<std::shared_ptr<LogThreadObject>>& result ) = 0;
        virtual void GetLogThreadCollectionByProcessAtStarted( const Guid& process, const DateTime& started, std::vector<std::shared_ptr<LogThreadObject>>& result ) = 0;
        virtual void GetLogThreadCollectionByProcessFromStarted( const Guid& process, const DateTime& started, std::vector<std::shared_ptr<LogThreadObject>>& result ) = 0;
        virtual void GetLogThreadCollectionByProcessUntilStarted( const Guid& process, const DateTime& started, std::vector<std::shared_ptr<LogThreadObject>>& result ) = 0;
        virtual void GetLogThreadCollectionByProcessOverStarted( Guid process, DateTime fromStarted, DateTime untilStarted, std::vector<std::shared_ptr<LogThreadObject>>& result ) = 0;
        virtual void GetLogThreadCollectionByStarted( const DateTime& started, std::vector<std::shared_ptr<LogThreadObject>>& result ) = 0;
        virtual void GetLogThreadCollectionAtStarted( const DateTime& started, std::vector<std::shared_ptr<LogThreadObject>>& result ) = 0;
        virtual void GetLogThreadCollectionFromStarted( const DateTime& started, std::vector<std::shared_ptr<LogThreadObject>>& result ) = 0;
        virtual void GetLogThreadCollectionUntilStarted( const DateTime& started, std::vector<std::shared_ptr<LogThreadObject>>& result ) = 0;
        virtual void GetLogThreadCollectionOverStarted( DateTime fromStarted, DateTime untilStarted, std::vector<std::shared_ptr<LogThreadObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // LogTraceEntry queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<LogTraceEntryObject> GetLogTraceEntryById( const Guid& id ) = 0;
        virtual void GetLogTraceEntryCollection( std::vector<std::shared_ptr<LogTraceEntryObject>>& result ) = 0;
        virtual void GetLogTraceEntryCollectionByThread( const Guid& thread, std::vector<std::shared_ptr<LogTraceEntryObject>>& result ) = 0;
        virtual void GetLogTraceEntryCollectionByThreadAndEntered( const Guid& thread, const DateTime& entered, std::vector<std::shared_ptr<LogTraceEntryObject>>& result ) = 0;
        virtual void GetLogTraceEntryCollectionByThreadAtEntered( const Guid& thread, const DateTime& entered, std::vector<std::shared_ptr<LogTraceEntryObject>>& result ) = 0;
        virtual void GetLogTraceEntryCollectionByThreadFromEntered( const Guid& thread, const DateTime& entered, std::vector<std::shared_ptr<LogTraceEntryObject>>& result ) = 0;
        virtual void GetLogTraceEntryCollectionByThreadUntilEntered( const Guid& thread, const DateTime& entered, std::vector<std::shared_ptr<LogTraceEntryObject>>& result ) = 0;
        virtual void GetLogTraceEntryCollectionByThreadOverEntered( Guid thread, DateTime fromEntered, DateTime untilEntered, std::vector<std::shared_ptr<LogTraceEntryObject>>& result ) = 0;
        virtual void GetLogTraceEntryCollectionByLocation( const Guid& location, std::vector<std::shared_ptr<LogTraceEntryObject>>& result ) = 0;
        virtual void GetLogTraceEntryCollectionByLocationAndEntered( const Guid& location, const DateTime& entered, std::vector<std::shared_ptr<LogTraceEntryObject>>& result ) = 0;
        virtual void GetLogTraceEntryCollectionByLocationAtEntered( const Guid& location, const DateTime& entered, std::vector<std::shared_ptr<LogTraceEntryObject>>& result ) = 0;
        virtual void GetLogTraceEntryCollectionByLocationFromEntered( const Guid& location, const DateTime& entered, std::vector<std::shared_ptr<LogTraceEntryObject>>& result ) = 0;
        virtual void GetLogTraceEntryCollectionByLocationUntilEntered( const Guid& location, const DateTime& entered, std::vector<std::shared_ptr<LogTraceEntryObject>>& result ) = 0;
        virtual void GetLogTraceEntryCollectionByLocationOverEntered( Guid location, DateTime fromEntered, DateTime untilEntered, std::vector<std::shared_ptr<LogTraceEntryObject>>& result ) = 0;
        virtual void GetLogTraceEntryCollectionByEntered( const DateTime& entered, std::vector<std::shared_ptr<LogTraceEntryObject>>& result ) = 0;
        virtual void GetLogTraceEntryCollectionAtEntered( const DateTime& entered, std::vector<std::shared_ptr<LogTraceEntryObject>>& result ) = 0;
        virtual void GetLogTraceEntryCollectionFromEntered( const DateTime& entered, std::vector<std::shared_ptr<LogTraceEntryObject>>& result ) = 0;
        virtual void GetLogTraceEntryCollectionUntilEntered( const DateTime& entered, std::vector<std::shared_ptr<LogTraceEntryObject>>& result ) = 0;
        virtual void GetLogTraceEntryCollectionOverEntered( DateTime fromEntered, DateTime untilEntered, std::vector<std::shared_ptr<LogTraceEntryObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // MapElement queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<MapElementObject> GetMapElementById( const Guid& id ) = 0;
        virtual void GetMapElementCollection( std::vector<std::shared_ptr<MapElementObject>>& result ) = 0;
        virtual void GetMapElementCollectionByItem( const Guid& item, std::vector<std::shared_ptr<MapElementObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // MapInfo queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<MapInfoObject> GetMapInfoById( const Guid& id ) = 0;
        virtual void GetMapInfoCollection( std::vector<std::shared_ptr<MapInfoObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // MapServiceOptions queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<MapServiceOptionsObject> GetMapServiceOptionsById( const Guid& id ) = 0;
        virtual void GetMapServiceOptionsCollection( std::vector<std::shared_ptr<MapServiceOptionsObject>>& result ) = 0;
        virtual std::shared_ptr<MapServiceOptionsObject> GetMapServiceOptionsByTimestamp( const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<MapServiceOptionsObject> GetMapServiceOptionsAtTimestamp( const DateTime& timestamp ) = 0;
        virtual void GetMapServiceOptionsFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<MapServiceOptionsObject>>& result ) = 0;
        virtual void GetMapServiceOptionsUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<MapServiceOptionsObject>>& result ) = 0;
        virtual void GetMapServiceOptionsOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<MapServiceOptionsObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // MaritimeIdentificationDigits queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<MaritimeIdentificationDigitsObject> GetMaritimeIdentificationDigitsById( const Guid& id ) = 0;
        virtual void GetMaritimeIdentificationDigitsCollection( std::vector<std::shared_ptr<MaritimeIdentificationDigitsObject>>& result ) = 0;
        virtual std::shared_ptr<MaritimeIdentificationDigitsObject> GetMaritimeIdentificationDigitsByCode( Int32 code ) = 0;
        virtual void GetMaritimeIdentificationDigitsFromCode( Int32 code, std::vector<std::shared_ptr<MaritimeIdentificationDigitsObject>>& result ) = 0;
        virtual void GetMaritimeIdentificationDigitsUntilCode( Int32 code, std::vector<std::shared_ptr<MaritimeIdentificationDigitsObject>>& result ) = 0;
        virtual void GetMaritimeIdentificationDigitsOverCode( Int32 fromCode, Int32 untilCode, std::vector<std::shared_ptr<MaritimeIdentificationDigitsObject>>& result ) = 0;
        virtual void GetMaritimeIdentificationDigitsCollectionByCountry( const Guid& country, std::vector<std::shared_ptr<MaritimeIdentificationDigitsObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // MediaProxySession queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<MediaProxySessionObject> GetMediaProxySessionById( const Guid& id ) = 0;
        virtual void GetMediaProxySessionCollection( std::vector<std::shared_ptr<MediaProxySessionObject>>& result ) = 0;
        virtual void GetMediaProxySessionCollectionByService( const Guid& service, std::vector<std::shared_ptr<MediaProxySessionObject>>& result ) = 0;
        virtual std::shared_ptr<MediaProxySessionObject> GetMediaProxySessionByServiceAndName( const Guid& service, const FixedDBWideString<128>& name ) = 0;
        // ---------------------------------------------------------------------
        // MediaProxySessionFile queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<MediaProxySessionFileObject> GetMediaProxySessionFileById( const Guid& id ) = 0;
        virtual void GetMediaProxySessionFileCollection( std::vector<std::shared_ptr<MediaProxySessionFileObject>>& result ) = 0;
        virtual void GetMediaProxySessionFileCollectionByProxySession( const Guid& proxySession, std::vector<std::shared_ptr<MediaProxySessionFileObject>>& result ) = 0;
        virtual std::shared_ptr<MediaProxySessionFileObject> GetMediaProxySessionFileByProxySessionAndTimestamp( const Guid& proxySession, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<MediaProxySessionFileObject> GetMediaProxySessionFileByProxySessionAtTimestamp( const Guid& proxySession, const DateTime& timestamp ) = 0;
        virtual void GetMediaProxySessionFileByProxySessionFromTimestamp( const Guid& proxySession, const DateTime& timestamp, std::vector<std::shared_ptr<MediaProxySessionFileObject>>& result ) = 0;
        virtual void GetMediaProxySessionFileByProxySessionUntilTimestamp( const Guid& proxySession, const DateTime& timestamp, std::vector<std::shared_ptr<MediaProxySessionFileObject>>& result ) = 0;
        virtual void GetMediaProxySessionFileByProxySessionOverTimestamp( Guid proxySession, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<MediaProxySessionFileObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // MediaProxySessionOptions queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<MediaProxySessionOptionsObject> GetMediaProxySessionOptionsById( const Guid& id ) = 0;
        virtual void GetMediaProxySessionOptionsCollection( std::vector<std::shared_ptr<MediaProxySessionOptionsObject>>& result ) = 0;
        virtual void GetMediaProxySessionOptionsCollectionByProxySession( const Guid& proxySession, std::vector<std::shared_ptr<MediaProxySessionOptionsObject>>& result ) = 0;
        virtual std::shared_ptr<MediaProxySessionOptionsObject> GetMediaProxySessionOptionsByProxySessionAndTimestamp( const Guid& proxySession, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<MediaProxySessionOptionsObject> GetMediaProxySessionOptionsByProxySessionAtTimestamp( const Guid& proxySession, const DateTime& timestamp ) = 0;
        virtual void GetMediaProxySessionOptionsByProxySessionFromTimestamp( const Guid& proxySession, const DateTime& timestamp, std::vector<std::shared_ptr<MediaProxySessionOptionsObject>>& result ) = 0;
        virtual void GetMediaProxySessionOptionsByProxySessionUntilTimestamp( const Guid& proxySession, const DateTime& timestamp, std::vector<std::shared_ptr<MediaProxySessionOptionsObject>>& result ) = 0;
        virtual void GetMediaProxySessionOptionsByProxySessionOverTimestamp( Guid proxySession, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<MediaProxySessionOptionsObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // MediaService queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<MediaServiceObject> GetMediaServiceById( const Guid& id ) = 0;
        virtual void GetMediaServiceCollection( std::vector<std::shared_ptr<MediaServiceObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // MediaServiceOptions queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<MediaServiceOptionsObject> GetMediaServiceOptionsById( const Guid& id ) = 0;
        virtual void GetMediaServiceOptionsCollection( std::vector<std::shared_ptr<MediaServiceOptionsObject>>& result ) = 0;
        virtual void GetMediaServiceOptionsCollectionByMediaService( const Guid& mediaService, std::vector<std::shared_ptr<MediaServiceOptionsObject>>& result ) = 0;
        virtual std::shared_ptr<MediaServiceOptionsObject> GetMediaServiceOptionsByMediaServiceAndTimestamp( const Guid& mediaService, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<MediaServiceOptionsObject> GetMediaServiceOptionsByMediaServiceAtTimestamp( const Guid& mediaService, const DateTime& timestamp ) = 0;
        virtual void GetMediaServiceOptionsByMediaServiceFromTimestamp( const Guid& mediaService, const DateTime& timestamp, std::vector<std::shared_ptr<MediaServiceOptionsObject>>& result ) = 0;
        virtual void GetMediaServiceOptionsByMediaServiceUntilTimestamp( const Guid& mediaService, const DateTime& timestamp, std::vector<std::shared_ptr<MediaServiceOptionsObject>>& result ) = 0;
        virtual void GetMediaServiceOptionsByMediaServiceOverTimestamp( Guid mediaService, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<MediaServiceOptionsObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // NamespaceElement queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<NamespaceElementObject> GetNamespaceElementById( const Guid& id ) = 0;
        virtual void GetNamespaceElementCollection( std::vector<std::shared_ptr<NamespaceElementObject>>& result ) = 0;
        virtual void GetNamespaceElementCollectionByNamespace( const Guid& namespace__, std::vector<std::shared_ptr<NamespaceElementObject>>& result ) = 0;
        virtual std::shared_ptr<NamespaceElementObject> GetNamespaceElementByNamespaceAndName( const Guid& namespace__, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // ElementType queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ElementTypeObject> GetElementTypeById( const Guid& id ) = 0;
        virtual void GetElementTypeCollection( std::vector<std::shared_ptr<ElementTypeObject>>& result ) = 0;
        virtual void GetElementTypeCollectionByNamespace( const Guid& namespace__, std::vector<std::shared_ptr<ElementTypeObject>>& result ) = 0;
        virtual std::shared_ptr<ElementTypeObject> GetElementTypeByNamespaceAndName( const Guid& namespace__, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // Namespace queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<NamespaceObject> GetNamespaceById( const Guid& id ) = 0;
        virtual void GetNamespaceCollection( std::vector<std::shared_ptr<NamespaceObject>>& result ) = 0;
        virtual void GetNamespaceCollectionByNamespace( const Guid& namespace__, std::vector<std::shared_ptr<NamespaceObject>>& result ) = 0;
        virtual std::shared_ptr<NamespaceObject> GetNamespaceByNamespaceAndName( const Guid& namespace__, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // OilSpill queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<OilSpillObject> GetOilSpillById( const Guid& id ) = 0;
        virtual void GetOilSpillCollection( std::vector<std::shared_ptr<OilSpillObject>>& result ) = 0;
        virtual void GetOilSpillCollectionByOilSpillDetector( const Guid& oilSpillDetector, std::vector<std::shared_ptr<OilSpillObject>>& result ) = 0;
        virtual void GetOilSpillCollectionByOilSpillDetectorAndTimestamp( const Guid& oilSpillDetector, const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillObject>>& result ) = 0;
        virtual void GetOilSpillCollectionByOilSpillDetectorAtTimestamp( const Guid& oilSpillDetector, const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillObject>>& result ) = 0;
        virtual void GetOilSpillCollectionByOilSpillDetectorFromTimestamp( const Guid& oilSpillDetector, const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillObject>>& result ) = 0;
        virtual void GetOilSpillCollectionByOilSpillDetectorUntilTimestamp( const Guid& oilSpillDetector, const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillObject>>& result ) = 0;
        virtual void GetOilSpillCollectionByOilSpillDetectorOverTimestamp( Guid oilSpillDetector, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<OilSpillObject>>& result ) = 0;
        virtual void GetOilSpillCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillObject>>& result ) = 0;
        virtual void GetOilSpillCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillObject>>& result ) = 0;
        virtual void GetOilSpillCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillObject>>& result ) = 0;
        virtual void GetOilSpillCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillObject>>& result ) = 0;
        virtual void GetOilSpillCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<OilSpillObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // OilSpillDetectorCommand queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<OilSpillDetectorCommandObject> GetOilSpillDetectorCommandById( const Guid& id ) = 0;
        virtual void GetOilSpillDetectorCommandCollection( std::vector<std::shared_ptr<OilSpillDetectorCommandObject>>& result ) = 0;
        virtual void GetOilSpillDetectorCommandCollectionByOilSpillDetector( const Guid& oilSpillDetector, std::vector<std::shared_ptr<OilSpillDetectorCommandObject>>& result ) = 0;
        virtual void GetOilSpillDetectorCommandCollectionByOilSpillDetectorAndTimestamp( const Guid& oilSpillDetector, const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillDetectorCommandObject>>& result ) = 0;
        virtual void GetOilSpillDetectorCommandCollectionByOilSpillDetectorAtTimestamp( const Guid& oilSpillDetector, const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillDetectorCommandObject>>& result ) = 0;
        virtual void GetOilSpillDetectorCommandCollectionByOilSpillDetectorFromTimestamp( const Guid& oilSpillDetector, const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillDetectorCommandObject>>& result ) = 0;
        virtual void GetOilSpillDetectorCommandCollectionByOilSpillDetectorUntilTimestamp( const Guid& oilSpillDetector, const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillDetectorCommandObject>>& result ) = 0;
        virtual void GetOilSpillDetectorCommandCollectionByOilSpillDetectorOverTimestamp( Guid oilSpillDetector, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<OilSpillDetectorCommandObject>>& result ) = 0;
        virtual void GetOilSpillDetectorCommandCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillDetectorCommandObject>>& result ) = 0;
        virtual void GetOilSpillDetectorCommandCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillDetectorCommandObject>>& result ) = 0;
        virtual void GetOilSpillDetectorCommandCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillDetectorCommandObject>>& result ) = 0;
        virtual void GetOilSpillDetectorCommandCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillDetectorCommandObject>>& result ) = 0;
        virtual void GetOilSpillDetectorCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<OilSpillDetectorCommandObject>>& result ) = 0;
        virtual void GetOilSpillDetectorCommandCollectionByReply( const DBGuid& reply, std::vector<std::shared_ptr<OilSpillDetectorCommandObject>>& result ) = 0;
        virtual void GetOilSpillDetectorCommandCollectionByReplyIsNull( std::vector<std::shared_ptr<OilSpillDetectorCommandObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // OilSpillDetectorCommandReply queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<OilSpillDetectorCommandReplyObject> GetOilSpillDetectorCommandReplyById( const Guid& id ) = 0;
        virtual void GetOilSpillDetectorCommandReplyCollection( std::vector<std::shared_ptr<OilSpillDetectorCommandReplyObject>>& result ) = 0;
        virtual void GetOilSpillDetectorCommandReplyCollectionByOilSpillDetector( const Guid& oilSpillDetector, std::vector<std::shared_ptr<OilSpillDetectorCommandReplyObject>>& result ) = 0;
        virtual void GetOilSpillDetectorCommandReplyCollectionByOilSpillDetectorAndTimestamp( const Guid& oilSpillDetector, const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillDetectorCommandReplyObject>>& result ) = 0;
        virtual void GetOilSpillDetectorCommandReplyCollectionByOilSpillDetectorAtTimestamp( const Guid& oilSpillDetector, const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillDetectorCommandReplyObject>>& result ) = 0;
        virtual void GetOilSpillDetectorCommandReplyCollectionByOilSpillDetectorFromTimestamp( const Guid& oilSpillDetector, const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillDetectorCommandReplyObject>>& result ) = 0;
        virtual void GetOilSpillDetectorCommandReplyCollectionByOilSpillDetectorUntilTimestamp( const Guid& oilSpillDetector, const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillDetectorCommandReplyObject>>& result ) = 0;
        virtual void GetOilSpillDetectorCommandReplyCollectionByOilSpillDetectorOverTimestamp( Guid oilSpillDetector, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<OilSpillDetectorCommandReplyObject>>& result ) = 0;
        virtual void GetOilSpillDetectorCommandReplyCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillDetectorCommandReplyObject>>& result ) = 0;
        virtual void GetOilSpillDetectorCommandReplyCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillDetectorCommandReplyObject>>& result ) = 0;
        virtual void GetOilSpillDetectorCommandReplyCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillDetectorCommandReplyObject>>& result ) = 0;
        virtual void GetOilSpillDetectorCommandReplyCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillDetectorCommandReplyObject>>& result ) = 0;
        virtual void GetOilSpillDetectorCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<OilSpillDetectorCommandReplyObject>>& result ) = 0;
        virtual std::shared_ptr<OilSpillDetectorCommandReplyObject> GetOilSpillDetectorCommandReplyByCommand( const DBGuid& command ) = 0;
        virtual void GetOilSpillDetectorCommandReplyCollectionByCommandIsNull( std::vector<std::shared_ptr<OilSpillDetectorCommandReplyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // OilSpillDetectorConfiguration queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<OilSpillDetectorConfigurationObject> GetOilSpillDetectorConfigurationById( const Guid& id ) = 0;
        virtual void GetOilSpillDetectorConfigurationCollection( std::vector<std::shared_ptr<OilSpillDetectorConfigurationObject>>& result ) = 0;
        virtual void GetOilSpillDetectorConfigurationCollectionByOilSpillDetector( const Guid& oilSpillDetector, std::vector<std::shared_ptr<OilSpillDetectorConfigurationObject>>& result ) = 0;
        virtual std::shared_ptr<OilSpillDetectorConfigurationObject> GetOilSpillDetectorConfigurationByOilSpillDetectorAndTimestamp( const Guid& oilSpillDetector, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<OilSpillDetectorConfigurationObject> GetOilSpillDetectorConfigurationByOilSpillDetectorAtTimestamp( const Guid& oilSpillDetector, const DateTime& timestamp ) = 0;
        virtual void GetOilSpillDetectorConfigurationByOilSpillDetectorFromTimestamp( const Guid& oilSpillDetector, const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillDetectorConfigurationObject>>& result ) = 0;
        virtual void GetOilSpillDetectorConfigurationByOilSpillDetectorUntilTimestamp( const Guid& oilSpillDetector, const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillDetectorConfigurationObject>>& result ) = 0;
        virtual void GetOilSpillDetectorConfigurationByOilSpillDetectorOverTimestamp( Guid oilSpillDetector, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<OilSpillDetectorConfigurationObject>>& result ) = 0;
        virtual void GetOilSpillDetectorConfigurationCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillDetectorConfigurationObject>>& result ) = 0;
        virtual void GetOilSpillDetectorConfigurationCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillDetectorConfigurationObject>>& result ) = 0;
        virtual void GetOilSpillDetectorConfigurationCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillDetectorConfigurationObject>>& result ) = 0;
        virtual void GetOilSpillDetectorConfigurationCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<OilSpillDetectorConfigurationObject>>& result ) = 0;
        virtual void GetOilSpillDetectorConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<OilSpillDetectorConfigurationObject>>& result ) = 0;
        virtual void GetOilSpillDetectorConfigurationCollectionByTargetMMSI( const DBGuid& targetMMSI, std::vector<std::shared_ptr<OilSpillDetectorConfigurationObject>>& result ) = 0;
        virtual void GetOilSpillDetectorConfigurationCollectionByTargetMMSIIsNull( std::vector<std::shared_ptr<OilSpillDetectorConfigurationObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Position2DTimeseriesValue queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<Position2DTimeseriesValueObject> GetPosition2DTimeseriesValueById( const Guid& id ) = 0;
        virtual void GetPosition2DTimeseriesValueCollection( std::vector<std::shared_ptr<Position2DTimeseriesValueObject>>& result ) = 0;
        virtual void GetPosition2DTimeseriesValueCollectionByTimeseries( const Guid& timeseries, std::vector<std::shared_ptr<Position2DTimeseriesValueObject>>& result ) = 0;
        virtual std::shared_ptr<Position2DTimeseriesValueObject> GetPosition2DTimeseriesValueByTimeseriesAndTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<Position2DTimeseriesValueObject> GetPosition2DTimeseriesValueByTimeseriesAtTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual void GetPosition2DTimeseriesValueByTimeseriesFromTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<Position2DTimeseriesValueObject>>& result ) = 0;
        virtual void GetPosition2DTimeseriesValueByTimeseriesUntilTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<Position2DTimeseriesValueObject>>& result ) = 0;
        virtual void GetPosition2DTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<Position2DTimeseriesValueObject>>& result ) = 0;
        virtual void GetPosition2DTimeseriesValueCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<Position2DTimeseriesValueObject>>& result ) = 0;
        virtual void GetPosition2DTimeseriesValueCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<Position2DTimeseriesValueObject>>& result ) = 0;
        virtual void GetPosition2DTimeseriesValueCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<Position2DTimeseriesValueObject>>& result ) = 0;
        virtual void GetPosition2DTimeseriesValueCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<Position2DTimeseriesValueObject>>& result ) = 0;
        virtual void GetPosition2DTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<Position2DTimeseriesValueObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Position3DTimeseriesValue queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<Position3DTimeseriesValueObject> GetPosition3DTimeseriesValueById( const Guid& id ) = 0;
        virtual void GetPosition3DTimeseriesValueCollection( std::vector<std::shared_ptr<Position3DTimeseriesValueObject>>& result ) = 0;
        virtual void GetPosition3DTimeseriesValueCollectionByTimeseries( const Guid& timeseries, std::vector<std::shared_ptr<Position3DTimeseriesValueObject>>& result ) = 0;
        virtual std::shared_ptr<Position3DTimeseriesValueObject> GetPosition3DTimeseriesValueByTimeseriesAndTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<Position3DTimeseriesValueObject> GetPosition3DTimeseriesValueByTimeseriesAtTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual void GetPosition3DTimeseriesValueByTimeseriesFromTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<Position3DTimeseriesValueObject>>& result ) = 0;
        virtual void GetPosition3DTimeseriesValueByTimeseriesUntilTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<Position3DTimeseriesValueObject>>& result ) = 0;
        virtual void GetPosition3DTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<Position3DTimeseriesValueObject>>& result ) = 0;
        virtual void GetPosition3DTimeseriesValueCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<Position3DTimeseriesValueObject>>& result ) = 0;
        virtual void GetPosition3DTimeseriesValueCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<Position3DTimeseriesValueObject>>& result ) = 0;
        virtual void GetPosition3DTimeseriesValueCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<Position3DTimeseriesValueObject>>& result ) = 0;
        virtual void GetPosition3DTimeseriesValueCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<Position3DTimeseriesValueObject>>& result ) = 0;
        virtual void GetPosition3DTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<Position3DTimeseriesValueObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // ProcessTrackValueResult queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ProcessTrackValueResultObject> GetProcessTrackValueResultById( const Guid& id ) = 0;
        virtual void GetProcessTrackValueResultCollection( std::vector<std::shared_ptr<ProcessTrackValueResultObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Property queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<PropertyObject> GetPropertyById( const Guid& id ) = 0;
        virtual void GetPropertyCollection( std::vector<std::shared_ptr<PropertyObject>>& result ) = 0;
        virtual void GetPropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<PropertyObject>>& result ) = 0;
        virtual std::shared_ptr<PropertyObject> GetPropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetPropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<PropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // BinaryProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<BinaryPropertyObject> GetBinaryPropertyById( const Guid& id ) = 0;
        virtual void GetBinaryPropertyCollection( std::vector<std::shared_ptr<BinaryPropertyObject>>& result ) = 0;
        virtual void GetBinaryPropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<BinaryPropertyObject>>& result ) = 0;
        virtual std::shared_ptr<BinaryPropertyObject> GetBinaryPropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetBinaryPropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<BinaryPropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // BooleanProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<BooleanPropertyObject> GetBooleanPropertyById( const Guid& id ) = 0;
        virtual void GetBooleanPropertyCollection( std::vector<std::shared_ptr<BooleanPropertyObject>>& result ) = 0;
        virtual void GetBooleanPropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<BooleanPropertyObject>>& result ) = 0;
        virtual std::shared_ptr<BooleanPropertyObject> GetBooleanPropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetBooleanPropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<BooleanPropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // ByteProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<BytePropertyObject> GetBytePropertyById( const Guid& id ) = 0;
        virtual void GetBytePropertyCollection( std::vector<std::shared_ptr<BytePropertyObject>>& result ) = 0;
        virtual void GetBytePropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<BytePropertyObject>>& result ) = 0;
        virtual std::shared_ptr<BytePropertyObject> GetBytePropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetBytePropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<BytePropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // DateTimeProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<DateTimePropertyObject> GetDateTimePropertyById( const Guid& id ) = 0;
        virtual void GetDateTimePropertyCollection( std::vector<std::shared_ptr<DateTimePropertyObject>>& result ) = 0;
        virtual void GetDateTimePropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<DateTimePropertyObject>>& result ) = 0;
        virtual std::shared_ptr<DateTimePropertyObject> GetDateTimePropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetDateTimePropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<DateTimePropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // DoubleProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<DoublePropertyObject> GetDoublePropertyById( const Guid& id ) = 0;
        virtual void GetDoublePropertyCollection( std::vector<std::shared_ptr<DoublePropertyObject>>& result ) = 0;
        virtual void GetDoublePropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<DoublePropertyObject>>& result ) = 0;
        virtual std::shared_ptr<DoublePropertyObject> GetDoublePropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetDoublePropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<DoublePropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // GuidProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GuidPropertyObject> GetGuidPropertyById( const Guid& id ) = 0;
        virtual void GetGuidPropertyCollection( std::vector<std::shared_ptr<GuidPropertyObject>>& result ) = 0;
        virtual void GetGuidPropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<GuidPropertyObject>>& result ) = 0;
        virtual std::shared_ptr<GuidPropertyObject> GetGuidPropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetGuidPropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<GuidPropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Int16Property queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<Int16PropertyObject> GetInt16PropertyById( const Guid& id ) = 0;
        virtual void GetInt16PropertyCollection( std::vector<std::shared_ptr<Int16PropertyObject>>& result ) = 0;
        virtual void GetInt16PropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<Int16PropertyObject>>& result ) = 0;
        virtual std::shared_ptr<Int16PropertyObject> GetInt16PropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetInt16PropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<Int16PropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Int32Property queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<Int32PropertyObject> GetInt32PropertyById( const Guid& id ) = 0;
        virtual void GetInt32PropertyCollection( std::vector<std::shared_ptr<Int32PropertyObject>>& result ) = 0;
        virtual void GetInt32PropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<Int32PropertyObject>>& result ) = 0;
        virtual std::shared_ptr<Int32PropertyObject> GetInt32PropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetInt32PropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<Int32PropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Int64Property queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<Int64PropertyObject> GetInt64PropertyById( const Guid& id ) = 0;
        virtual void GetInt64PropertyCollection( std::vector<std::shared_ptr<Int64PropertyObject>>& result ) = 0;
        virtual void GetInt64PropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<Int64PropertyObject>>& result ) = 0;
        virtual std::shared_ptr<Int64PropertyObject> GetInt64PropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetInt64PropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<Int64PropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // ReferenceProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ReferencePropertyObject> GetReferencePropertyById( const Guid& id ) = 0;
        virtual void GetReferencePropertyCollection( std::vector<std::shared_ptr<ReferencePropertyObject>>& result ) = 0;
        virtual void GetReferencePropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<ReferencePropertyObject>>& result ) = 0;
        virtual std::shared_ptr<ReferencePropertyObject> GetReferencePropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetReferencePropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<ReferencePropertyObject>>& result ) = 0;
        virtual void GetReferencePropertyCollectionByValue( const DBGuid& value, std::vector<std::shared_ptr<ReferencePropertyObject>>& result ) = 0;
        virtual void GetReferencePropertyCollectionByValueIsNull( std::vector<std::shared_ptr<ReferencePropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // SByteProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<SBytePropertyObject> GetSBytePropertyById( const Guid& id ) = 0;
        virtual void GetSBytePropertyCollection( std::vector<std::shared_ptr<SBytePropertyObject>>& result ) = 0;
        virtual void GetSBytePropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<SBytePropertyObject>>& result ) = 0;
        virtual std::shared_ptr<SBytePropertyObject> GetSBytePropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetSBytePropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<SBytePropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // SingleProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<SinglePropertyObject> GetSinglePropertyById( const Guid& id ) = 0;
        virtual void GetSinglePropertyCollection( std::vector<std::shared_ptr<SinglePropertyObject>>& result ) = 0;
        virtual void GetSinglePropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<SinglePropertyObject>>& result ) = 0;
        virtual std::shared_ptr<SinglePropertyObject> GetSinglePropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetSinglePropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<SinglePropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // StringProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<StringPropertyObject> GetStringPropertyById( const Guid& id ) = 0;
        virtual void GetStringPropertyCollection( std::vector<std::shared_ptr<StringPropertyObject>>& result ) = 0;
        virtual void GetStringPropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<StringPropertyObject>>& result ) = 0;
        virtual std::shared_ptr<StringPropertyObject> GetStringPropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetStringPropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<StringPropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // TimeseriesProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<TimeseriesPropertyObject> GetTimeseriesPropertyById( const Guid& id ) = 0;
        virtual void GetTimeseriesPropertyCollection( std::vector<std::shared_ptr<TimeseriesPropertyObject>>& result ) = 0;
        virtual void GetTimeseriesPropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<TimeseriesPropertyObject>>& result ) = 0;
        virtual std::shared_ptr<TimeseriesPropertyObject> GetTimeseriesPropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetTimeseriesPropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<TimeseriesPropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // BinaryTimeseriesProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<BinaryTimeseriesPropertyObject> GetBinaryTimeseriesPropertyById( const Guid& id ) = 0;
        virtual void GetBinaryTimeseriesPropertyCollection( std::vector<std::shared_ptr<BinaryTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetBinaryTimeseriesPropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<BinaryTimeseriesPropertyObject>>& result ) = 0;
        virtual std::shared_ptr<BinaryTimeseriesPropertyObject> GetBinaryTimeseriesPropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetBinaryTimeseriesPropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<BinaryTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetBinaryTimeseriesPropertyCollectionByTimeseries( const DBGuid& timeseries, std::vector<std::shared_ptr<BinaryTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetBinaryTimeseriesPropertyCollectionByTimeseriesIsNull( std::vector<std::shared_ptr<BinaryTimeseriesPropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // BooleanTimeseriesProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<BooleanTimeseriesPropertyObject> GetBooleanTimeseriesPropertyById( const Guid& id ) = 0;
        virtual void GetBooleanTimeseriesPropertyCollection( std::vector<std::shared_ptr<BooleanTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetBooleanTimeseriesPropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<BooleanTimeseriesPropertyObject>>& result ) = 0;
        virtual std::shared_ptr<BooleanTimeseriesPropertyObject> GetBooleanTimeseriesPropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetBooleanTimeseriesPropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<BooleanTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetBooleanTimeseriesPropertyCollectionByTimeseries( const DBGuid& timeseries, std::vector<std::shared_ptr<BooleanTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetBooleanTimeseriesPropertyCollectionByTimeseriesIsNull( std::vector<std::shared_ptr<BooleanTimeseriesPropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // ByteTimeseriesProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ByteTimeseriesPropertyObject> GetByteTimeseriesPropertyById( const Guid& id ) = 0;
        virtual void GetByteTimeseriesPropertyCollection( std::vector<std::shared_ptr<ByteTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetByteTimeseriesPropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<ByteTimeseriesPropertyObject>>& result ) = 0;
        virtual std::shared_ptr<ByteTimeseriesPropertyObject> GetByteTimeseriesPropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetByteTimeseriesPropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<ByteTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetByteTimeseriesPropertyCollectionByTimeseries( const DBGuid& timeseries, std::vector<std::shared_ptr<ByteTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetByteTimeseriesPropertyCollectionByTimeseriesIsNull( std::vector<std::shared_ptr<ByteTimeseriesPropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // DateTimeTimeseriesProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<DateTimeTimeseriesPropertyObject> GetDateTimeTimeseriesPropertyById( const Guid& id ) = 0;
        virtual void GetDateTimeTimeseriesPropertyCollection( std::vector<std::shared_ptr<DateTimeTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetDateTimeTimeseriesPropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<DateTimeTimeseriesPropertyObject>>& result ) = 0;
        virtual std::shared_ptr<DateTimeTimeseriesPropertyObject> GetDateTimeTimeseriesPropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetDateTimeTimeseriesPropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<DateTimeTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetDateTimeTimeseriesPropertyCollectionByTimeseries( const DBGuid& timeseries, std::vector<std::shared_ptr<DateTimeTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetDateTimeTimeseriesPropertyCollectionByTimeseriesIsNull( std::vector<std::shared_ptr<DateTimeTimeseriesPropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // DoubleTimeseriesProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<DoubleTimeseriesPropertyObject> GetDoubleTimeseriesPropertyById( const Guid& id ) = 0;
        virtual void GetDoubleTimeseriesPropertyCollection( std::vector<std::shared_ptr<DoubleTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetDoubleTimeseriesPropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<DoubleTimeseriesPropertyObject>>& result ) = 0;
        virtual std::shared_ptr<DoubleTimeseriesPropertyObject> GetDoubleTimeseriesPropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetDoubleTimeseriesPropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<DoubleTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetDoubleTimeseriesPropertyCollectionByTimeseries( const DBGuid& timeseries, std::vector<std::shared_ptr<DoubleTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetDoubleTimeseriesPropertyCollectionByTimeseriesIsNull( std::vector<std::shared_ptr<DoubleTimeseriesPropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // GuidTimeseriesProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GuidTimeseriesPropertyObject> GetGuidTimeseriesPropertyById( const Guid& id ) = 0;
        virtual void GetGuidTimeseriesPropertyCollection( std::vector<std::shared_ptr<GuidTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetGuidTimeseriesPropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<GuidTimeseriesPropertyObject>>& result ) = 0;
        virtual std::shared_ptr<GuidTimeseriesPropertyObject> GetGuidTimeseriesPropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetGuidTimeseriesPropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<GuidTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetGuidTimeseriesPropertyCollectionByTimeseries( const DBGuid& timeseries, std::vector<std::shared_ptr<GuidTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetGuidTimeseriesPropertyCollectionByTimeseriesIsNull( std::vector<std::shared_ptr<GuidTimeseriesPropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Int16TimeseriesProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<Int16TimeseriesPropertyObject> GetInt16TimeseriesPropertyById( const Guid& id ) = 0;
        virtual void GetInt16TimeseriesPropertyCollection( std::vector<std::shared_ptr<Int16TimeseriesPropertyObject>>& result ) = 0;
        virtual void GetInt16TimeseriesPropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<Int16TimeseriesPropertyObject>>& result ) = 0;
        virtual std::shared_ptr<Int16TimeseriesPropertyObject> GetInt16TimeseriesPropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetInt16TimeseriesPropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<Int16TimeseriesPropertyObject>>& result ) = 0;
        virtual void GetInt16TimeseriesPropertyCollectionByTimeseries( const DBGuid& timeseries, std::vector<std::shared_ptr<Int16TimeseriesPropertyObject>>& result ) = 0;
        virtual void GetInt16TimeseriesPropertyCollectionByTimeseriesIsNull( std::vector<std::shared_ptr<Int16TimeseriesPropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Int32TimeseriesProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<Int32TimeseriesPropertyObject> GetInt32TimeseriesPropertyById( const Guid& id ) = 0;
        virtual void GetInt32TimeseriesPropertyCollection( std::vector<std::shared_ptr<Int32TimeseriesPropertyObject>>& result ) = 0;
        virtual void GetInt32TimeseriesPropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<Int32TimeseriesPropertyObject>>& result ) = 0;
        virtual std::shared_ptr<Int32TimeseriesPropertyObject> GetInt32TimeseriesPropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetInt32TimeseriesPropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<Int32TimeseriesPropertyObject>>& result ) = 0;
        virtual void GetInt32TimeseriesPropertyCollectionByTimeseries( const DBGuid& timeseries, std::vector<std::shared_ptr<Int32TimeseriesPropertyObject>>& result ) = 0;
        virtual void GetInt32TimeseriesPropertyCollectionByTimeseriesIsNull( std::vector<std::shared_ptr<Int32TimeseriesPropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Int64TimeseriesProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<Int64TimeseriesPropertyObject> GetInt64TimeseriesPropertyById( const Guid& id ) = 0;
        virtual void GetInt64TimeseriesPropertyCollection( std::vector<std::shared_ptr<Int64TimeseriesPropertyObject>>& result ) = 0;
        virtual void GetInt64TimeseriesPropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<Int64TimeseriesPropertyObject>>& result ) = 0;
        virtual std::shared_ptr<Int64TimeseriesPropertyObject> GetInt64TimeseriesPropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetInt64TimeseriesPropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<Int64TimeseriesPropertyObject>>& result ) = 0;
        virtual void GetInt64TimeseriesPropertyCollectionByTimeseries( const DBGuid& timeseries, std::vector<std::shared_ptr<Int64TimeseriesPropertyObject>>& result ) = 0;
        virtual void GetInt64TimeseriesPropertyCollectionByTimeseriesIsNull( std::vector<std::shared_ptr<Int64TimeseriesPropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // ReferenceTimeseriesProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ReferenceTimeseriesPropertyObject> GetReferenceTimeseriesPropertyById( const Guid& id ) = 0;
        virtual void GetReferenceTimeseriesPropertyCollection( std::vector<std::shared_ptr<ReferenceTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetReferenceTimeseriesPropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<ReferenceTimeseriesPropertyObject>>& result ) = 0;
        virtual std::shared_ptr<ReferenceTimeseriesPropertyObject> GetReferenceTimeseriesPropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetReferenceTimeseriesPropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<ReferenceTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetReferenceTimeseriesPropertyCollectionByTimeseries( const DBGuid& timeseries, std::vector<std::shared_ptr<ReferenceTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetReferenceTimeseriesPropertyCollectionByTimeseriesIsNull( std::vector<std::shared_ptr<ReferenceTimeseriesPropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // SByteTimeseriesProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<SByteTimeseriesPropertyObject> GetSByteTimeseriesPropertyById( const Guid& id ) = 0;
        virtual void GetSByteTimeseriesPropertyCollection( std::vector<std::shared_ptr<SByteTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetSByteTimeseriesPropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<SByteTimeseriesPropertyObject>>& result ) = 0;
        virtual std::shared_ptr<SByteTimeseriesPropertyObject> GetSByteTimeseriesPropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetSByteTimeseriesPropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<SByteTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetSByteTimeseriesPropertyCollectionByTimeseries( const DBGuid& timeseries, std::vector<std::shared_ptr<SByteTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetSByteTimeseriesPropertyCollectionByTimeseriesIsNull( std::vector<std::shared_ptr<SByteTimeseriesPropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // SingleTimeseriesProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<SingleTimeseriesPropertyObject> GetSingleTimeseriesPropertyById( const Guid& id ) = 0;
        virtual void GetSingleTimeseriesPropertyCollection( std::vector<std::shared_ptr<SingleTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetSingleTimeseriesPropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<SingleTimeseriesPropertyObject>>& result ) = 0;
        virtual std::shared_ptr<SingleTimeseriesPropertyObject> GetSingleTimeseriesPropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetSingleTimeseriesPropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<SingleTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetSingleTimeseriesPropertyCollectionByTimeseries( const DBGuid& timeseries, std::vector<std::shared_ptr<SingleTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetSingleTimeseriesPropertyCollectionByTimeseriesIsNull( std::vector<std::shared_ptr<SingleTimeseriesPropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // StringTimeseriesProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<StringTimeseriesPropertyObject> GetStringTimeseriesPropertyById( const Guid& id ) = 0;
        virtual void GetStringTimeseriesPropertyCollection( std::vector<std::shared_ptr<StringTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetStringTimeseriesPropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<StringTimeseriesPropertyObject>>& result ) = 0;
        virtual std::shared_ptr<StringTimeseriesPropertyObject> GetStringTimeseriesPropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetStringTimeseriesPropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<StringTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetStringTimeseriesPropertyCollectionByTimeseries( const DBGuid& timeseries, std::vector<std::shared_ptr<StringTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetStringTimeseriesPropertyCollectionByTimeseriesIsNull( std::vector<std::shared_ptr<StringTimeseriesPropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // TimeSpanTimeseriesProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<TimeSpanTimeseriesPropertyObject> GetTimeSpanTimeseriesPropertyById( const Guid& id ) = 0;
        virtual void GetTimeSpanTimeseriesPropertyCollection( std::vector<std::shared_ptr<TimeSpanTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetTimeSpanTimeseriesPropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<TimeSpanTimeseriesPropertyObject>>& result ) = 0;
        virtual std::shared_ptr<TimeSpanTimeseriesPropertyObject> GetTimeSpanTimeseriesPropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetTimeSpanTimeseriesPropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<TimeSpanTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetTimeSpanTimeseriesPropertyCollectionByTimeseries( const DBGuid& timeseries, std::vector<std::shared_ptr<TimeSpanTimeseriesPropertyObject>>& result ) = 0;
        virtual void GetTimeSpanTimeseriesPropertyCollectionByTimeseriesIsNull( std::vector<std::shared_ptr<TimeSpanTimeseriesPropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // UInt16TimeseriesProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<UInt16TimeseriesPropertyObject> GetUInt16TimeseriesPropertyById( const Guid& id ) = 0;
        virtual void GetUInt16TimeseriesPropertyCollection( std::vector<std::shared_ptr<UInt16TimeseriesPropertyObject>>& result ) = 0;
        virtual void GetUInt16TimeseriesPropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<UInt16TimeseriesPropertyObject>>& result ) = 0;
        virtual std::shared_ptr<UInt16TimeseriesPropertyObject> GetUInt16TimeseriesPropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetUInt16TimeseriesPropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<UInt16TimeseriesPropertyObject>>& result ) = 0;
        virtual void GetUInt16TimeseriesPropertyCollectionByTimeseries( const DBGuid& timeseries, std::vector<std::shared_ptr<UInt16TimeseriesPropertyObject>>& result ) = 0;
        virtual void GetUInt16TimeseriesPropertyCollectionByTimeseriesIsNull( std::vector<std::shared_ptr<UInt16TimeseriesPropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // UInt32TimeseriesProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<UInt32TimeseriesPropertyObject> GetUInt32TimeseriesPropertyById( const Guid& id ) = 0;
        virtual void GetUInt32TimeseriesPropertyCollection( std::vector<std::shared_ptr<UInt32TimeseriesPropertyObject>>& result ) = 0;
        virtual void GetUInt32TimeseriesPropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<UInt32TimeseriesPropertyObject>>& result ) = 0;
        virtual std::shared_ptr<UInt32TimeseriesPropertyObject> GetUInt32TimeseriesPropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetUInt32TimeseriesPropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<UInt32TimeseriesPropertyObject>>& result ) = 0;
        virtual void GetUInt32TimeseriesPropertyCollectionByTimeseries( const DBGuid& timeseries, std::vector<std::shared_ptr<UInt32TimeseriesPropertyObject>>& result ) = 0;
        virtual void GetUInt32TimeseriesPropertyCollectionByTimeseriesIsNull( std::vector<std::shared_ptr<UInt32TimeseriesPropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // UInt64TimeseriesProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<UInt64TimeseriesPropertyObject> GetUInt64TimeseriesPropertyById( const Guid& id ) = 0;
        virtual void GetUInt64TimeseriesPropertyCollection( std::vector<std::shared_ptr<UInt64TimeseriesPropertyObject>>& result ) = 0;
        virtual void GetUInt64TimeseriesPropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<UInt64TimeseriesPropertyObject>>& result ) = 0;
        virtual std::shared_ptr<UInt64TimeseriesPropertyObject> GetUInt64TimeseriesPropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetUInt64TimeseriesPropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<UInt64TimeseriesPropertyObject>>& result ) = 0;
        virtual void GetUInt64TimeseriesPropertyCollectionByTimeseries( const DBGuid& timeseries, std::vector<std::shared_ptr<UInt64TimeseriesPropertyObject>>& result ) = 0;
        virtual void GetUInt64TimeseriesPropertyCollectionByTimeseriesIsNull( std::vector<std::shared_ptr<UInt64TimeseriesPropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // TimeSpanProperty queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<TimeSpanPropertyObject> GetTimeSpanPropertyById( const Guid& id ) = 0;
        virtual void GetTimeSpanPropertyCollection( std::vector<std::shared_ptr<TimeSpanPropertyObject>>& result ) = 0;
        virtual void GetTimeSpanPropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<TimeSpanPropertyObject>>& result ) = 0;
        virtual std::shared_ptr<TimeSpanPropertyObject> GetTimeSpanPropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetTimeSpanPropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<TimeSpanPropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // UInt16Property queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<UInt16PropertyObject> GetUInt16PropertyById( const Guid& id ) = 0;
        virtual void GetUInt16PropertyCollection( std::vector<std::shared_ptr<UInt16PropertyObject>>& result ) = 0;
        virtual void GetUInt16PropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<UInt16PropertyObject>>& result ) = 0;
        virtual std::shared_ptr<UInt16PropertyObject> GetUInt16PropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetUInt16PropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<UInt16PropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // UInt32Property queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<UInt32PropertyObject> GetUInt32PropertyById( const Guid& id ) = 0;
        virtual void GetUInt32PropertyCollection( std::vector<std::shared_ptr<UInt32PropertyObject>>& result ) = 0;
        virtual void GetUInt32PropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<UInt32PropertyObject>>& result ) = 0;
        virtual std::shared_ptr<UInt32PropertyObject> GetUInt32PropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetUInt32PropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<UInt32PropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // UInt64Property queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<UInt64PropertyObject> GetUInt64PropertyById( const Guid& id ) = 0;
        virtual void GetUInt64PropertyCollection( std::vector<std::shared_ptr<UInt64PropertyObject>>& result ) = 0;
        virtual void GetUInt64PropertyCollectionByElement( const Guid& element, std::vector<std::shared_ptr<UInt64PropertyObject>>& result ) = 0;
        virtual std::shared_ptr<UInt64PropertyObject> GetUInt64PropertyByElementAndDefinition( const Guid& element, const Guid& definition ) = 0;
        virtual void GetUInt64PropertyCollectionByDefinition( const Guid& definition, std::vector<std::shared_ptr<UInt64PropertyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // PropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<PropertyDefinitionObject> GetPropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetPropertyDefinitionCollection( std::vector<std::shared_ptr<PropertyDefinitionObject>>& result ) = 0;
        virtual void GetPropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<PropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<PropertyDefinitionObject> GetPropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // BinaryPropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<BinaryPropertyDefinitionObject> GetBinaryPropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetBinaryPropertyDefinitionCollection( std::vector<std::shared_ptr<BinaryPropertyDefinitionObject>>& result ) = 0;
        virtual void GetBinaryPropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<BinaryPropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<BinaryPropertyDefinitionObject> GetBinaryPropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // BooleanPropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<BooleanPropertyDefinitionObject> GetBooleanPropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetBooleanPropertyDefinitionCollection( std::vector<std::shared_ptr<BooleanPropertyDefinitionObject>>& result ) = 0;
        virtual void GetBooleanPropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<BooleanPropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<BooleanPropertyDefinitionObject> GetBooleanPropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // BytePropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<BytePropertyDefinitionObject> GetBytePropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetBytePropertyDefinitionCollection( std::vector<std::shared_ptr<BytePropertyDefinitionObject>>& result ) = 0;
        virtual void GetBytePropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<BytePropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<BytePropertyDefinitionObject> GetBytePropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // DateTimePropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<DateTimePropertyDefinitionObject> GetDateTimePropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetDateTimePropertyDefinitionCollection( std::vector<std::shared_ptr<DateTimePropertyDefinitionObject>>& result ) = 0;
        virtual void GetDateTimePropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<DateTimePropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<DateTimePropertyDefinitionObject> GetDateTimePropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // DoublePropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<DoublePropertyDefinitionObject> GetDoublePropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetDoublePropertyDefinitionCollection( std::vector<std::shared_ptr<DoublePropertyDefinitionObject>>& result ) = 0;
        virtual void GetDoublePropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<DoublePropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<DoublePropertyDefinitionObject> GetDoublePropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // GuidPropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GuidPropertyDefinitionObject> GetGuidPropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetGuidPropertyDefinitionCollection( std::vector<std::shared_ptr<GuidPropertyDefinitionObject>>& result ) = 0;
        virtual void GetGuidPropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<GuidPropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<GuidPropertyDefinitionObject> GetGuidPropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // Int16PropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<Int16PropertyDefinitionObject> GetInt16PropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetInt16PropertyDefinitionCollection( std::vector<std::shared_ptr<Int16PropertyDefinitionObject>>& result ) = 0;
        virtual void GetInt16PropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<Int16PropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<Int16PropertyDefinitionObject> GetInt16PropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // Int32PropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<Int32PropertyDefinitionObject> GetInt32PropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetInt32PropertyDefinitionCollection( std::vector<std::shared_ptr<Int32PropertyDefinitionObject>>& result ) = 0;
        virtual void GetInt32PropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<Int32PropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<Int32PropertyDefinitionObject> GetInt32PropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // Int64PropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<Int64PropertyDefinitionObject> GetInt64PropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetInt64PropertyDefinitionCollection( std::vector<std::shared_ptr<Int64PropertyDefinitionObject>>& result ) = 0;
        virtual void GetInt64PropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<Int64PropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<Int64PropertyDefinitionObject> GetInt64PropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // ReferencePropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ReferencePropertyDefinitionObject> GetReferencePropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetReferencePropertyDefinitionCollection( std::vector<std::shared_ptr<ReferencePropertyDefinitionObject>>& result ) = 0;
        virtual void GetReferencePropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<ReferencePropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<ReferencePropertyDefinitionObject> GetReferencePropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        virtual void GetReferencePropertyDefinitionCollectionByDefaultValue( const DBGuid& defaultValue, std::vector<std::shared_ptr<ReferencePropertyDefinitionObject>>& result ) = 0;
        virtual void GetReferencePropertyDefinitionCollectionByDefaultValueIsNull( std::vector<std::shared_ptr<ReferencePropertyDefinitionObject>>& result ) = 0;
        virtual void GetReferencePropertyDefinitionCollectionByReferencedElementType( const DBGuid& referencedElementType, std::vector<std::shared_ptr<ReferencePropertyDefinitionObject>>& result ) = 0;
        virtual void GetReferencePropertyDefinitionCollectionByReferencedElementTypeIsNull( std::vector<std::shared_ptr<ReferencePropertyDefinitionObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // SBytePropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<SBytePropertyDefinitionObject> GetSBytePropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetSBytePropertyDefinitionCollection( std::vector<std::shared_ptr<SBytePropertyDefinitionObject>>& result ) = 0;
        virtual void GetSBytePropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<SBytePropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<SBytePropertyDefinitionObject> GetSBytePropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // SinglePropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<SinglePropertyDefinitionObject> GetSinglePropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetSinglePropertyDefinitionCollection( std::vector<std::shared_ptr<SinglePropertyDefinitionObject>>& result ) = 0;
        virtual void GetSinglePropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<SinglePropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<SinglePropertyDefinitionObject> GetSinglePropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // StringPropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<StringPropertyDefinitionObject> GetStringPropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetStringPropertyDefinitionCollection( std::vector<std::shared_ptr<StringPropertyDefinitionObject>>& result ) = 0;
        virtual void GetStringPropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<StringPropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<StringPropertyDefinitionObject> GetStringPropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // TimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<TimeseriesPropertyDefinitionObject> GetTimeseriesPropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetTimeseriesPropertyDefinitionCollection( std::vector<std::shared_ptr<TimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual void GetTimeseriesPropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<TimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<TimeseriesPropertyDefinitionObject> GetTimeseriesPropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // BinaryTimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<BinaryTimeseriesPropertyDefinitionObject> GetBinaryTimeseriesPropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetBinaryTimeseriesPropertyDefinitionCollection( std::vector<std::shared_ptr<BinaryTimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual void GetBinaryTimeseriesPropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<BinaryTimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<BinaryTimeseriesPropertyDefinitionObject> GetBinaryTimeseriesPropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // BooleanTimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<BooleanTimeseriesPropertyDefinitionObject> GetBooleanTimeseriesPropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetBooleanTimeseriesPropertyDefinitionCollection( std::vector<std::shared_ptr<BooleanTimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual void GetBooleanTimeseriesPropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<BooleanTimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<BooleanTimeseriesPropertyDefinitionObject> GetBooleanTimeseriesPropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // ByteTimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ByteTimeseriesPropertyDefinitionObject> GetByteTimeseriesPropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetByteTimeseriesPropertyDefinitionCollection( std::vector<std::shared_ptr<ByteTimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual void GetByteTimeseriesPropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<ByteTimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<ByteTimeseriesPropertyDefinitionObject> GetByteTimeseriesPropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // DateTimeTimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<DateTimeTimeseriesPropertyDefinitionObject> GetDateTimeTimeseriesPropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetDateTimeTimeseriesPropertyDefinitionCollection( std::vector<std::shared_ptr<DateTimeTimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual void GetDateTimeTimeseriesPropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<DateTimeTimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<DateTimeTimeseriesPropertyDefinitionObject> GetDateTimeTimeseriesPropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // DoubleTimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<DoubleTimeseriesPropertyDefinitionObject> GetDoubleTimeseriesPropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetDoubleTimeseriesPropertyDefinitionCollection( std::vector<std::shared_ptr<DoubleTimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual void GetDoubleTimeseriesPropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<DoubleTimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<DoubleTimeseriesPropertyDefinitionObject> GetDoubleTimeseriesPropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // GuidTimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GuidTimeseriesPropertyDefinitionObject> GetGuidTimeseriesPropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetGuidTimeseriesPropertyDefinitionCollection( std::vector<std::shared_ptr<GuidTimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual void GetGuidTimeseriesPropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<GuidTimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<GuidTimeseriesPropertyDefinitionObject> GetGuidTimeseriesPropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // Int16TimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<Int16TimeseriesPropertyDefinitionObject> GetInt16TimeseriesPropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetInt16TimeseriesPropertyDefinitionCollection( std::vector<std::shared_ptr<Int16TimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual void GetInt16TimeseriesPropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<Int16TimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<Int16TimeseriesPropertyDefinitionObject> GetInt16TimeseriesPropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // Int32TimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<Int32TimeseriesPropertyDefinitionObject> GetInt32TimeseriesPropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetInt32TimeseriesPropertyDefinitionCollection( std::vector<std::shared_ptr<Int32TimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual void GetInt32TimeseriesPropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<Int32TimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<Int32TimeseriesPropertyDefinitionObject> GetInt32TimeseriesPropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // Int64TimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<Int64TimeseriesPropertyDefinitionObject> GetInt64TimeseriesPropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetInt64TimeseriesPropertyDefinitionCollection( std::vector<std::shared_ptr<Int64TimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual void GetInt64TimeseriesPropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<Int64TimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<Int64TimeseriesPropertyDefinitionObject> GetInt64TimeseriesPropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // ReferenceTimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ReferenceTimeseriesPropertyDefinitionObject> GetReferenceTimeseriesPropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetReferenceTimeseriesPropertyDefinitionCollection( std::vector<std::shared_ptr<ReferenceTimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual void GetReferenceTimeseriesPropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<ReferenceTimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<ReferenceTimeseriesPropertyDefinitionObject> GetReferenceTimeseriesPropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        virtual void GetReferenceTimeseriesPropertyDefinitionCollectionByReferencedElementType( const DBGuid& referencedElementType, std::vector<std::shared_ptr<ReferenceTimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual void GetReferenceTimeseriesPropertyDefinitionCollectionByReferencedElementTypeIsNull( std::vector<std::shared_ptr<ReferenceTimeseriesPropertyDefinitionObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // SByteTimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<SByteTimeseriesPropertyDefinitionObject> GetSByteTimeseriesPropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetSByteTimeseriesPropertyDefinitionCollection( std::vector<std::shared_ptr<SByteTimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual void GetSByteTimeseriesPropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<SByteTimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<SByteTimeseriesPropertyDefinitionObject> GetSByteTimeseriesPropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // SingleTimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<SingleTimeseriesPropertyDefinitionObject> GetSingleTimeseriesPropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetSingleTimeseriesPropertyDefinitionCollection( std::vector<std::shared_ptr<SingleTimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual void GetSingleTimeseriesPropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<SingleTimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<SingleTimeseriesPropertyDefinitionObject> GetSingleTimeseriesPropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // StringTimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<StringTimeseriesPropertyDefinitionObject> GetStringTimeseriesPropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetStringTimeseriesPropertyDefinitionCollection( std::vector<std::shared_ptr<StringTimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual void GetStringTimeseriesPropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<StringTimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<StringTimeseriesPropertyDefinitionObject> GetStringTimeseriesPropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // TimeSpanTimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<TimeSpanTimeseriesPropertyDefinitionObject> GetTimeSpanTimeseriesPropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetTimeSpanTimeseriesPropertyDefinitionCollection( std::vector<std::shared_ptr<TimeSpanTimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual void GetTimeSpanTimeseriesPropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<TimeSpanTimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<TimeSpanTimeseriesPropertyDefinitionObject> GetTimeSpanTimeseriesPropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // UInt16TimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<UInt16TimeseriesPropertyDefinitionObject> GetUInt16TimeseriesPropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetUInt16TimeseriesPropertyDefinitionCollection( std::vector<std::shared_ptr<UInt16TimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual void GetUInt16TimeseriesPropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<UInt16TimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<UInt16TimeseriesPropertyDefinitionObject> GetUInt16TimeseriesPropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // UInt32TimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<UInt32TimeseriesPropertyDefinitionObject> GetUInt32TimeseriesPropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetUInt32TimeseriesPropertyDefinitionCollection( std::vector<std::shared_ptr<UInt32TimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual void GetUInt32TimeseriesPropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<UInt32TimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<UInt32TimeseriesPropertyDefinitionObject> GetUInt32TimeseriesPropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // UInt64TimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<UInt64TimeseriesPropertyDefinitionObject> GetUInt64TimeseriesPropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetUInt64TimeseriesPropertyDefinitionCollection( std::vector<std::shared_ptr<UInt64TimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual void GetUInt64TimeseriesPropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<UInt64TimeseriesPropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<UInt64TimeseriesPropertyDefinitionObject> GetUInt64TimeseriesPropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // TimeSpanPropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<TimeSpanPropertyDefinitionObject> GetTimeSpanPropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetTimeSpanPropertyDefinitionCollection( std::vector<std::shared_ptr<TimeSpanPropertyDefinitionObject>>& result ) = 0;
        virtual void GetTimeSpanPropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<TimeSpanPropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<TimeSpanPropertyDefinitionObject> GetTimeSpanPropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // UInt16PropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<UInt16PropertyDefinitionObject> GetUInt16PropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetUInt16PropertyDefinitionCollection( std::vector<std::shared_ptr<UInt16PropertyDefinitionObject>>& result ) = 0;
        virtual void GetUInt16PropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<UInt16PropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<UInt16PropertyDefinitionObject> GetUInt16PropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // UInt32PropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<UInt32PropertyDefinitionObject> GetUInt32PropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetUInt32PropertyDefinitionCollection( std::vector<std::shared_ptr<UInt32PropertyDefinitionObject>>& result ) = 0;
        virtual void GetUInt32PropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<UInt32PropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<UInt32PropertyDefinitionObject> GetUInt32PropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // UInt64PropertyDefinition queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<UInt64PropertyDefinitionObject> GetUInt64PropertyDefinitionById( const Guid& id ) = 0;
        virtual void GetUInt64PropertyDefinitionCollection( std::vector<std::shared_ptr<UInt64PropertyDefinitionObject>>& result ) = 0;
        virtual void GetUInt64PropertyDefinitionCollectionByElementType( const Guid& elementType, std::vector<std::shared_ptr<UInt64PropertyDefinitionObject>>& result ) = 0;
        virtual std::shared_ptr<UInt64PropertyDefinitionObject> GetUInt64PropertyDefinitionByElementTypeAndName( const Guid& elementType, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // RadarAlarmStatus queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarAlarmStatusObject> GetRadarAlarmStatusById( const Guid& id ) = 0;
        virtual void GetRadarAlarmStatusCollection( std::vector<std::shared_ptr<RadarAlarmStatusObject>>& result ) = 0;
        virtual void GetRadarAlarmStatusCollectionByRadar( const Guid& radar, std::vector<std::shared_ptr<RadarAlarmStatusObject>>& result ) = 0;
        virtual std::shared_ptr<RadarAlarmStatusObject> GetRadarAlarmStatusByRadarAndTimestamp( const Guid& radar, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<RadarAlarmStatusObject> GetRadarAlarmStatusByRadarAtTimestamp( const Guid& radar, const DateTime& timestamp ) = 0;
        virtual void GetRadarAlarmStatusByRadarFromTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarAlarmStatusObject>>& result ) = 0;
        virtual void GetRadarAlarmStatusByRadarUntilTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarAlarmStatusObject>>& result ) = 0;
        virtual void GetRadarAlarmStatusByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadarAlarmStatusObject>>& result ) = 0;
        virtual void GetRadarAlarmStatusCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarAlarmStatusObject>>& result ) = 0;
        virtual void GetRadarAlarmStatusCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarAlarmStatusObject>>& result ) = 0;
        virtual void GetRadarAlarmStatusCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarAlarmStatusObject>>& result ) = 0;
        virtual void GetRadarAlarmStatusCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarAlarmStatusObject>>& result ) = 0;
        virtual void GetRadarAlarmStatusCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadarAlarmStatusObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarCommand queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarCommandObject> GetRadarCommandById( const Guid& id ) = 0;
        virtual void GetRadarCommandCollection( std::vector<std::shared_ptr<RadarCommandObject>>& result ) = 0;
        virtual void GetRadarCommandCollectionByRadar( const Guid& radar, std::vector<std::shared_ptr<RadarCommandObject>>& result ) = 0;
        virtual void GetRadarCommandCollectionByRadarAndTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandObject>>& result ) = 0;
        virtual void GetRadarCommandCollectionByRadarAtTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandObject>>& result ) = 0;
        virtual void GetRadarCommandCollectionByRadarFromTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandObject>>& result ) = 0;
        virtual void GetRadarCommandCollectionByRadarUntilTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandObject>>& result ) = 0;
        virtual void GetRadarCommandCollectionByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadarCommandObject>>& result ) = 0;
        virtual void GetRadarCommandCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandObject>>& result ) = 0;
        virtual void GetRadarCommandCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandObject>>& result ) = 0;
        virtual void GetRadarCommandCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandObject>>& result ) = 0;
        virtual void GetRadarCommandCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandObject>>& result ) = 0;
        virtual void GetRadarCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadarCommandObject>>& result ) = 0;
        virtual void GetRadarCommandCollectionByReply( const DBGuid& reply, std::vector<std::shared_ptr<RadarCommandObject>>& result ) = 0;
        virtual void GetRadarCommandCollectionByReplyIsNull( std::vector<std::shared_ptr<RadarCommandObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarCommandGetStatus queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarCommandGetStatusObject> GetRadarCommandGetStatusById( const Guid& id ) = 0;
        virtual void GetRadarCommandGetStatusCollection( std::vector<std::shared_ptr<RadarCommandGetStatusObject>>& result ) = 0;
        virtual void GetRadarCommandGetStatusCollectionByRadar( const Guid& radar, std::vector<std::shared_ptr<RadarCommandGetStatusObject>>& result ) = 0;
        virtual void GetRadarCommandGetStatusCollectionByRadarAndTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandGetStatusObject>>& result ) = 0;
        virtual void GetRadarCommandGetStatusCollectionByRadarAtTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandGetStatusObject>>& result ) = 0;
        virtual void GetRadarCommandGetStatusCollectionByRadarFromTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandGetStatusObject>>& result ) = 0;
        virtual void GetRadarCommandGetStatusCollectionByRadarUntilTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandGetStatusObject>>& result ) = 0;
        virtual void GetRadarCommandGetStatusCollectionByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadarCommandGetStatusObject>>& result ) = 0;
        virtual void GetRadarCommandGetStatusCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandGetStatusObject>>& result ) = 0;
        virtual void GetRadarCommandGetStatusCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandGetStatusObject>>& result ) = 0;
        virtual void GetRadarCommandGetStatusCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandGetStatusObject>>& result ) = 0;
        virtual void GetRadarCommandGetStatusCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandGetStatusObject>>& result ) = 0;
        virtual void GetRadarCommandGetStatusCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadarCommandGetStatusObject>>& result ) = 0;
        virtual void GetRadarCommandGetStatusCollectionByReply( const DBGuid& reply, std::vector<std::shared_ptr<RadarCommandGetStatusObject>>& result ) = 0;
        virtual void GetRadarCommandGetStatusCollectionByReplyIsNull( std::vector<std::shared_ptr<RadarCommandGetStatusObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarCommandReply queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarCommandReplyObject> GetRadarCommandReplyById( const Guid& id ) = 0;
        virtual void GetRadarCommandReplyCollection( std::vector<std::shared_ptr<RadarCommandReplyObject>>& result ) = 0;
        virtual void GetRadarCommandReplyCollectionByRadar( const Guid& radar, std::vector<std::shared_ptr<RadarCommandReplyObject>>& result ) = 0;
        virtual void GetRadarCommandReplyCollectionByRadarAndTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandReplyObject>>& result ) = 0;
        virtual void GetRadarCommandReplyCollectionByRadarAtTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandReplyObject>>& result ) = 0;
        virtual void GetRadarCommandReplyCollectionByRadarFromTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandReplyObject>>& result ) = 0;
        virtual void GetRadarCommandReplyCollectionByRadarUntilTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandReplyObject>>& result ) = 0;
        virtual void GetRadarCommandReplyCollectionByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadarCommandReplyObject>>& result ) = 0;
        virtual void GetRadarCommandReplyCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandReplyObject>>& result ) = 0;
        virtual void GetRadarCommandReplyCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandReplyObject>>& result ) = 0;
        virtual void GetRadarCommandReplyCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandReplyObject>>& result ) = 0;
        virtual void GetRadarCommandReplyCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandReplyObject>>& result ) = 0;
        virtual void GetRadarCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadarCommandReplyObject>>& result ) = 0;
        virtual std::shared_ptr<RadarCommandReplyObject> GetRadarCommandReplyByCommand( const DBGuid& command ) = 0;
        virtual void GetRadarCommandReplyCollectionByCommandIsNull( std::vector<std::shared_ptr<RadarCommandReplyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarCommandReplyGetStatus queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarCommandReplyGetStatusObject> GetRadarCommandReplyGetStatusById( const Guid& id ) = 0;
        virtual void GetRadarCommandReplyGetStatusCollection( std::vector<std::shared_ptr<RadarCommandReplyGetStatusObject>>& result ) = 0;
        virtual void GetRadarCommandReplyGetStatusCollectionByRadar( const Guid& radar, std::vector<std::shared_ptr<RadarCommandReplyGetStatusObject>>& result ) = 0;
        virtual void GetRadarCommandReplyGetStatusCollectionByRadarAndTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandReplyGetStatusObject>>& result ) = 0;
        virtual void GetRadarCommandReplyGetStatusCollectionByRadarAtTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandReplyGetStatusObject>>& result ) = 0;
        virtual void GetRadarCommandReplyGetStatusCollectionByRadarFromTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandReplyGetStatusObject>>& result ) = 0;
        virtual void GetRadarCommandReplyGetStatusCollectionByRadarUntilTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandReplyGetStatusObject>>& result ) = 0;
        virtual void GetRadarCommandReplyGetStatusCollectionByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadarCommandReplyGetStatusObject>>& result ) = 0;
        virtual void GetRadarCommandReplyGetStatusCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandReplyGetStatusObject>>& result ) = 0;
        virtual void GetRadarCommandReplyGetStatusCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandReplyGetStatusObject>>& result ) = 0;
        virtual void GetRadarCommandReplyGetStatusCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandReplyGetStatusObject>>& result ) = 0;
        virtual void GetRadarCommandReplyGetStatusCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarCommandReplyGetStatusObject>>& result ) = 0;
        virtual void GetRadarCommandReplyGetStatusCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadarCommandReplyGetStatusObject>>& result ) = 0;
        virtual std::shared_ptr<RadarCommandReplyGetStatusObject> GetRadarCommandReplyGetStatusByCommand( const DBGuid& command ) = 0;
        virtual void GetRadarCommandReplyGetStatusCollectionByCommandIsNull( std::vector<std::shared_ptr<RadarCommandReplyGetStatusObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarConfiguration queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarConfigurationObject> GetRadarConfigurationById( const Guid& id ) = 0;
        virtual void GetRadarConfigurationCollection( std::vector<std::shared_ptr<RadarConfigurationObject>>& result ) = 0;
        virtual void GetRadarConfigurationCollectionByRadar( const Guid& radar, std::vector<std::shared_ptr<RadarConfigurationObject>>& result ) = 0;
        virtual std::shared_ptr<RadarConfigurationObject> GetRadarConfigurationByRadarAndTimestamp( const Guid& radar, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<RadarConfigurationObject> GetRadarConfigurationByRadarAtTimestamp( const Guid& radar, const DateTime& timestamp ) = 0;
        virtual void GetRadarConfigurationByRadarFromTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarConfigurationObject>>& result ) = 0;
        virtual void GetRadarConfigurationByRadarUntilTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarConfigurationObject>>& result ) = 0;
        virtual void GetRadarConfigurationByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadarConfigurationObject>>& result ) = 0;
        virtual void GetRadarConfigurationCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarConfigurationObject>>& result ) = 0;
        virtual void GetRadarConfigurationCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarConfigurationObject>>& result ) = 0;
        virtual void GetRadarConfigurationCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarConfigurationObject>>& result ) = 0;
        virtual void GetRadarConfigurationCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarConfigurationObject>>& result ) = 0;
        virtual void GetRadarConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadarConfigurationObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarImage queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarImageObject> GetRadarImageById( const Guid& id ) = 0;
        virtual void GetRadarImageCollection( std::vector<std::shared_ptr<RadarImageObject>>& result ) = 0;
        virtual void GetRadarImageCollectionByRadar( const Guid& radar, std::vector<std::shared_ptr<RadarImageObject>>& result ) = 0;
        virtual std::shared_ptr<RadarImageObject> GetRadarImageByRadarAndTimestamp( const Guid& radar, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<RadarImageObject> GetRadarImageByRadarAtTimestamp( const Guid& radar, const DateTime& timestamp ) = 0;
        virtual void GetRadarImageByRadarFromTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarImageObject>>& result ) = 0;
        virtual void GetRadarImageByRadarUntilTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarImageObject>>& result ) = 0;
        virtual void GetRadarImageByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadarImageObject>>& result ) = 0;
        virtual void GetRadarImageCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarImageObject>>& result ) = 0;
        virtual void GetRadarImageCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarImageObject>>& result ) = 0;
        virtual void GetRadarImageCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarImageObject>>& result ) = 0;
        virtual void GetRadarImageCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarImageObject>>& result ) = 0;
        virtual void GetRadarImageCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadarImageObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarRawTrackTable queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarRawTrackTableObject> GetRadarRawTrackTableById( const Guid& id ) = 0;
        virtual void GetRadarRawTrackTableCollection( std::vector<std::shared_ptr<RadarRawTrackTableObject>>& result ) = 0;
        virtual void GetRadarRawTrackTableCollectionByRadar( const Guid& radar, std::vector<std::shared_ptr<RadarRawTrackTableObject>>& result ) = 0;
        virtual std::shared_ptr<RadarRawTrackTableObject> GetRadarRawTrackTableByRadarAndTimestamp( const Guid& radar, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<RadarRawTrackTableObject> GetRadarRawTrackTableByRadarAtTimestamp( const Guid& radar, const DateTime& timestamp ) = 0;
        virtual void GetRadarRawTrackTableByRadarFromTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarRawTrackTableObject>>& result ) = 0;
        virtual void GetRadarRawTrackTableByRadarUntilTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarRawTrackTableObject>>& result ) = 0;
        virtual void GetRadarRawTrackTableByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadarRawTrackTableObject>>& result ) = 0;
        virtual void GetRadarRawTrackTableCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarRawTrackTableObject>>& result ) = 0;
        virtual void GetRadarRawTrackTableCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarRawTrackTableObject>>& result ) = 0;
        virtual void GetRadarRawTrackTableCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarRawTrackTableObject>>& result ) = 0;
        virtual void GetRadarRawTrackTableCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarRawTrackTableObject>>& result ) = 0;
        virtual void GetRadarRawTrackTableCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadarRawTrackTableObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarStatus queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarStatusObject> GetRadarStatusById( const Guid& id ) = 0;
        virtual void GetRadarStatusCollection( std::vector<std::shared_ptr<RadarStatusObject>>& result ) = 0;
        virtual void GetRadarStatusCollectionByRadar( const Guid& radar, std::vector<std::shared_ptr<RadarStatusObject>>& result ) = 0;
        virtual std::shared_ptr<RadarStatusObject> GetRadarStatusByRadarAndTimestamp( const Guid& radar, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<RadarStatusObject> GetRadarStatusByRadarAtTimestamp( const Guid& radar, const DateTime& timestamp ) = 0;
        virtual void GetRadarStatusByRadarFromTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarStatusObject>>& result ) = 0;
        virtual void GetRadarStatusByRadarUntilTimestamp( const Guid& radar, const DateTime& timestamp, std::vector<std::shared_ptr<RadarStatusObject>>& result ) = 0;
        virtual void GetRadarStatusByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadarStatusObject>>& result ) = 0;
        virtual void GetRadarStatusCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarStatusObject>>& result ) = 0;
        virtual void GetRadarStatusCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarStatusObject>>& result ) = 0;
        virtual void GetRadarStatusCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarStatusObject>>& result ) = 0;
        virtual void GetRadarStatusCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadarStatusObject>>& result ) = 0;
        virtual void GetRadarStatusCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadarStatusObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadioCommand queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadioCommandObject> GetRadioCommandById( const Guid& id ) = 0;
        virtual void GetRadioCommandCollection( std::vector<std::shared_ptr<RadioCommandObject>>& result ) = 0;
        virtual void GetRadioCommandCollectionByRadio( const Guid& radio, std::vector<std::shared_ptr<RadioCommandObject>>& result ) = 0;
        virtual void GetRadioCommandCollectionByRadioAndTimestamp( const Guid& radio, const DateTime& timestamp, std::vector<std::shared_ptr<RadioCommandObject>>& result ) = 0;
        virtual void GetRadioCommandCollectionByRadioAtTimestamp( const Guid& radio, const DateTime& timestamp, std::vector<std::shared_ptr<RadioCommandObject>>& result ) = 0;
        virtual void GetRadioCommandCollectionByRadioFromTimestamp( const Guid& radio, const DateTime& timestamp, std::vector<std::shared_ptr<RadioCommandObject>>& result ) = 0;
        virtual void GetRadioCommandCollectionByRadioUntilTimestamp( const Guid& radio, const DateTime& timestamp, std::vector<std::shared_ptr<RadioCommandObject>>& result ) = 0;
        virtual void GetRadioCommandCollectionByRadioOverTimestamp( Guid radio, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadioCommandObject>>& result ) = 0;
        virtual void GetRadioCommandCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadioCommandObject>>& result ) = 0;
        virtual void GetRadioCommandCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadioCommandObject>>& result ) = 0;
        virtual void GetRadioCommandCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadioCommandObject>>& result ) = 0;
        virtual void GetRadioCommandCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadioCommandObject>>& result ) = 0;
        virtual void GetRadioCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadioCommandObject>>& result ) = 0;
        virtual void GetRadioCommandCollectionByReply( const DBGuid& reply, std::vector<std::shared_ptr<RadioCommandObject>>& result ) = 0;
        virtual void GetRadioCommandCollectionByReplyIsNull( std::vector<std::shared_ptr<RadioCommandObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadioCommandReply queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadioCommandReplyObject> GetRadioCommandReplyById( const Guid& id ) = 0;
        virtual void GetRadioCommandReplyCollection( std::vector<std::shared_ptr<RadioCommandReplyObject>>& result ) = 0;
        virtual void GetRadioCommandReplyCollectionByRadio( const Guid& radio, std::vector<std::shared_ptr<RadioCommandReplyObject>>& result ) = 0;
        virtual void GetRadioCommandReplyCollectionByRadioAndTimestamp( const Guid& radio, const DateTime& timestamp, std::vector<std::shared_ptr<RadioCommandReplyObject>>& result ) = 0;
        virtual void GetRadioCommandReplyCollectionByRadioAtTimestamp( const Guid& radio, const DateTime& timestamp, std::vector<std::shared_ptr<RadioCommandReplyObject>>& result ) = 0;
        virtual void GetRadioCommandReplyCollectionByRadioFromTimestamp( const Guid& radio, const DateTime& timestamp, std::vector<std::shared_ptr<RadioCommandReplyObject>>& result ) = 0;
        virtual void GetRadioCommandReplyCollectionByRadioUntilTimestamp( const Guid& radio, const DateTime& timestamp, std::vector<std::shared_ptr<RadioCommandReplyObject>>& result ) = 0;
        virtual void GetRadioCommandReplyCollectionByRadioOverTimestamp( Guid radio, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadioCommandReplyObject>>& result ) = 0;
        virtual void GetRadioCommandReplyCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadioCommandReplyObject>>& result ) = 0;
        virtual void GetRadioCommandReplyCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadioCommandReplyObject>>& result ) = 0;
        virtual void GetRadioCommandReplyCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadioCommandReplyObject>>& result ) = 0;
        virtual void GetRadioCommandReplyCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadioCommandReplyObject>>& result ) = 0;
        virtual void GetRadioCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadioCommandReplyObject>>& result ) = 0;
        virtual std::shared_ptr<RadioCommandReplyObject> GetRadioCommandReplyByCommand( const DBGuid& command ) = 0;
        virtual void GetRadioCommandReplyCollectionByCommandIsNull( std::vector<std::shared_ptr<RadioCommandReplyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadioConfiguration queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadioConfigurationObject> GetRadioConfigurationById( const Guid& id ) = 0;
        virtual void GetRadioConfigurationCollection( std::vector<std::shared_ptr<RadioConfigurationObject>>& result ) = 0;
        virtual void GetRadioConfigurationCollectionByRadio( const Guid& radio, std::vector<std::shared_ptr<RadioConfigurationObject>>& result ) = 0;
        virtual std::shared_ptr<RadioConfigurationObject> GetRadioConfigurationByRadioAndTimestamp( const Guid& radio, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<RadioConfigurationObject> GetRadioConfigurationByRadioAtTimestamp( const Guid& radio, const DateTime& timestamp ) = 0;
        virtual void GetRadioConfigurationByRadioFromTimestamp( const Guid& radio, const DateTime& timestamp, std::vector<std::shared_ptr<RadioConfigurationObject>>& result ) = 0;
        virtual void GetRadioConfigurationByRadioUntilTimestamp( const Guid& radio, const DateTime& timestamp, std::vector<std::shared_ptr<RadioConfigurationObject>>& result ) = 0;
        virtual void GetRadioConfigurationByRadioOverTimestamp( Guid radio, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadioConfigurationObject>>& result ) = 0;
        virtual void GetRadioConfigurationCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadioConfigurationObject>>& result ) = 0;
        virtual void GetRadioConfigurationCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadioConfigurationObject>>& result ) = 0;
        virtual void GetRadioConfigurationCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadioConfigurationObject>>& result ) = 0;
        virtual void GetRadioConfigurationCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadioConfigurationObject>>& result ) = 0;
        virtual void GetRadioConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadioConfigurationObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadomeCommand queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadomeCommandObject> GetRadomeCommandById( const Guid& id ) = 0;
        virtual void GetRadomeCommandCollection( std::vector<std::shared_ptr<RadomeCommandObject>>& result ) = 0;
        virtual void GetRadomeCommandCollectionByRadome( const Guid& radome, std::vector<std::shared_ptr<RadomeCommandObject>>& result ) = 0;
        virtual void GetRadomeCommandCollectionByRadomeAndTimestamp( const Guid& radome, const DateTime& timestamp, std::vector<std::shared_ptr<RadomeCommandObject>>& result ) = 0;
        virtual void GetRadomeCommandCollectionByRadomeAtTimestamp( const Guid& radome, const DateTime& timestamp, std::vector<std::shared_ptr<RadomeCommandObject>>& result ) = 0;
        virtual void GetRadomeCommandCollectionByRadomeFromTimestamp( const Guid& radome, const DateTime& timestamp, std::vector<std::shared_ptr<RadomeCommandObject>>& result ) = 0;
        virtual void GetRadomeCommandCollectionByRadomeUntilTimestamp( const Guid& radome, const DateTime& timestamp, std::vector<std::shared_ptr<RadomeCommandObject>>& result ) = 0;
        virtual void GetRadomeCommandCollectionByRadomeOverTimestamp( Guid radome, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadomeCommandObject>>& result ) = 0;
        virtual void GetRadomeCommandCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadomeCommandObject>>& result ) = 0;
        virtual void GetRadomeCommandCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadomeCommandObject>>& result ) = 0;
        virtual void GetRadomeCommandCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadomeCommandObject>>& result ) = 0;
        virtual void GetRadomeCommandCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadomeCommandObject>>& result ) = 0;
        virtual void GetRadomeCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadomeCommandObject>>& result ) = 0;
        virtual void GetRadomeCommandCollectionByReply( const DBGuid& reply, std::vector<std::shared_ptr<RadomeCommandObject>>& result ) = 0;
        virtual void GetRadomeCommandCollectionByReplyIsNull( std::vector<std::shared_ptr<RadomeCommandObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadomeCommandReply queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadomeCommandReplyObject> GetRadomeCommandReplyById( const Guid& id ) = 0;
        virtual void GetRadomeCommandReplyCollection( std::vector<std::shared_ptr<RadomeCommandReplyObject>>& result ) = 0;
        virtual void GetRadomeCommandReplyCollectionByRadome( const Guid& radome, std::vector<std::shared_ptr<RadomeCommandReplyObject>>& result ) = 0;
        virtual void GetRadomeCommandReplyCollectionByRadomeAndTimestamp( const Guid& radome, const DateTime& timestamp, std::vector<std::shared_ptr<RadomeCommandReplyObject>>& result ) = 0;
        virtual void GetRadomeCommandReplyCollectionByRadomeAtTimestamp( const Guid& radome, const DateTime& timestamp, std::vector<std::shared_ptr<RadomeCommandReplyObject>>& result ) = 0;
        virtual void GetRadomeCommandReplyCollectionByRadomeFromTimestamp( const Guid& radome, const DateTime& timestamp, std::vector<std::shared_ptr<RadomeCommandReplyObject>>& result ) = 0;
        virtual void GetRadomeCommandReplyCollectionByRadomeUntilTimestamp( const Guid& radome, const DateTime& timestamp, std::vector<std::shared_ptr<RadomeCommandReplyObject>>& result ) = 0;
        virtual void GetRadomeCommandReplyCollectionByRadomeOverTimestamp( Guid radome, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadomeCommandReplyObject>>& result ) = 0;
        virtual void GetRadomeCommandReplyCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadomeCommandReplyObject>>& result ) = 0;
        virtual void GetRadomeCommandReplyCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadomeCommandReplyObject>>& result ) = 0;
        virtual void GetRadomeCommandReplyCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadomeCommandReplyObject>>& result ) = 0;
        virtual void GetRadomeCommandReplyCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadomeCommandReplyObject>>& result ) = 0;
        virtual void GetRadomeCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadomeCommandReplyObject>>& result ) = 0;
        virtual std::shared_ptr<RadomeCommandReplyObject> GetRadomeCommandReplyByCommand( const DBGuid& command ) = 0;
        virtual void GetRadomeCommandReplyCollectionByCommandIsNull( std::vector<std::shared_ptr<RadomeCommandReplyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadomeConfiguration queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadomeConfigurationObject> GetRadomeConfigurationById( const Guid& id ) = 0;
        virtual void GetRadomeConfigurationCollection( std::vector<std::shared_ptr<RadomeConfigurationObject>>& result ) = 0;
        virtual void GetRadomeConfigurationCollectionByRadome( const Guid& radome, std::vector<std::shared_ptr<RadomeConfigurationObject>>& result ) = 0;
        virtual std::shared_ptr<RadomeConfigurationObject> GetRadomeConfigurationByRadomeAndTimestamp( const Guid& radome, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<RadomeConfigurationObject> GetRadomeConfigurationByRadomeAtTimestamp( const Guid& radome, const DateTime& timestamp ) = 0;
        virtual void GetRadomeConfigurationByRadomeFromTimestamp( const Guid& radome, const DateTime& timestamp, std::vector<std::shared_ptr<RadomeConfigurationObject>>& result ) = 0;
        virtual void GetRadomeConfigurationByRadomeUntilTimestamp( const Guid& radome, const DateTime& timestamp, std::vector<std::shared_ptr<RadomeConfigurationObject>>& result ) = 0;
        virtual void GetRadomeConfigurationByRadomeOverTimestamp( Guid radome, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadomeConfigurationObject>>& result ) = 0;
        virtual void GetRadomeConfigurationCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadomeConfigurationObject>>& result ) = 0;
        virtual void GetRadomeConfigurationCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadomeConfigurationObject>>& result ) = 0;
        virtual void GetRadomeConfigurationCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadomeConfigurationObject>>& result ) = 0;
        virtual void GetRadomeConfigurationCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<RadomeConfigurationObject>>& result ) = 0;
        virtual void GetRadomeConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<RadomeConfigurationObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // ReferenceTimeseriesValue queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ReferenceTimeseriesValueObject> GetReferenceTimeseriesValueById( const Guid& id ) = 0;
        virtual void GetReferenceTimeseriesValueCollection( std::vector<std::shared_ptr<ReferenceTimeseriesValueObject>>& result ) = 0;
        virtual void GetReferenceTimeseriesValueCollectionByTimeseries( const Guid& timeseries, std::vector<std::shared_ptr<ReferenceTimeseriesValueObject>>& result ) = 0;
        virtual std::shared_ptr<ReferenceTimeseriesValueObject> GetReferenceTimeseriesValueByTimeseriesAndTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<ReferenceTimeseriesValueObject> GetReferenceTimeseriesValueByTimeseriesAtTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual void GetReferenceTimeseriesValueByTimeseriesFromTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<ReferenceTimeseriesValueObject>>& result ) = 0;
        virtual void GetReferenceTimeseriesValueByTimeseriesUntilTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<ReferenceTimeseriesValueObject>>& result ) = 0;
        virtual void GetReferenceTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<ReferenceTimeseriesValueObject>>& result ) = 0;
        virtual void GetReferenceTimeseriesValueCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<ReferenceTimeseriesValueObject>>& result ) = 0;
        virtual void GetReferenceTimeseriesValueCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<ReferenceTimeseriesValueObject>>& result ) = 0;
        virtual void GetReferenceTimeseriesValueCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<ReferenceTimeseriesValueObject>>& result ) = 0;
        virtual void GetReferenceTimeseriesValueCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<ReferenceTimeseriesValueObject>>& result ) = 0;
        virtual void GetReferenceTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<ReferenceTimeseriesValueObject>>& result ) = 0;
        virtual void GetReferenceTimeseriesValueCollectionByValue( const Guid& value, std::vector<std::shared_ptr<ReferenceTimeseriesValueObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // SByteTimeseriesValue queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<SByteTimeseriesValueObject> GetSByteTimeseriesValueById( const Guid& id ) = 0;
        virtual void GetSByteTimeseriesValueCollection( std::vector<std::shared_ptr<SByteTimeseriesValueObject>>& result ) = 0;
        virtual void GetSByteTimeseriesValueCollectionByTimeseries( const Guid& timeseries, std::vector<std::shared_ptr<SByteTimeseriesValueObject>>& result ) = 0;
        virtual std::shared_ptr<SByteTimeseriesValueObject> GetSByteTimeseriesValueByTimeseriesAndTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<SByteTimeseriesValueObject> GetSByteTimeseriesValueByTimeseriesAtTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual void GetSByteTimeseriesValueByTimeseriesFromTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<SByteTimeseriesValueObject>>& result ) = 0;
        virtual void GetSByteTimeseriesValueByTimeseriesUntilTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<SByteTimeseriesValueObject>>& result ) = 0;
        virtual void GetSByteTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<SByteTimeseriesValueObject>>& result ) = 0;
        virtual void GetSByteTimeseriesValueCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<SByteTimeseriesValueObject>>& result ) = 0;
        virtual void GetSByteTimeseriesValueCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<SByteTimeseriesValueObject>>& result ) = 0;
        virtual void GetSByteTimeseriesValueCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<SByteTimeseriesValueObject>>& result ) = 0;
        virtual void GetSByteTimeseriesValueCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<SByteTimeseriesValueObject>>& result ) = 0;
        virtual void GetSByteTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<SByteTimeseriesValueObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // SecurityDomain queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<SecurityDomainObject> GetSecurityDomainById( const Guid& id ) = 0;
        virtual void GetSecurityDomainCollection( std::vector<std::shared_ptr<SecurityDomainObject>>& result ) = 0;
        virtual std::shared_ptr<SecurityDomainObject> GetSecurityDomainByName( const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // SecurityIdentifier queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<SecurityIdentifierObject> GetSecurityIdentifierById( const Guid& id ) = 0;
        virtual void GetSecurityIdentifierCollection( std::vector<std::shared_ptr<SecurityIdentifierObject>>& result ) = 0;
        virtual void GetSecurityIdentifierCollectionByDomain( const Guid& domain, std::vector<std::shared_ptr<SecurityIdentifierObject>>& result ) = 0;
        virtual std::shared_ptr<SecurityIdentifierObject> GetSecurityIdentifierByDomainAndIdentity( const Guid& domain, const FixedDBWideString<255>& identity ) = 0;
        // ---------------------------------------------------------------------
        // SecurityLogin queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<SecurityLoginObject> GetSecurityLoginById( const Guid& id ) = 0;
        virtual void GetSecurityLoginCollection( std::vector<std::shared_ptr<SecurityLoginObject>>& result ) = 0;
        virtual void GetSecurityLoginCollectionByDomain( const Guid& domain, std::vector<std::shared_ptr<SecurityLoginObject>>& result ) = 0;
        virtual std::shared_ptr<SecurityLoginObject> GetSecurityLoginByDomainAndIdentity( const Guid& domain, const FixedDBWideString<255>& identity ) = 0;
        // ---------------------------------------------------------------------
        // SecurityRole queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<SecurityRoleObject> GetSecurityRoleById( const Guid& id ) = 0;
        virtual void GetSecurityRoleCollection( std::vector<std::shared_ptr<SecurityRoleObject>>& result ) = 0;
        virtual void GetSecurityRoleCollectionByDomain( const Guid& domain, std::vector<std::shared_ptr<SecurityRoleObject>>& result ) = 0;
        virtual std::shared_ptr<SecurityRoleObject> GetSecurityRoleByDomainAndIdentity( const Guid& domain, const FixedDBWideString<255>& identity ) = 0;
        virtual std::shared_ptr<SecurityRoleObject> GetSecurityRoleByName( const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // SecurityIdentifierRoleLink queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<SecurityIdentifierRoleLinkObject> GetSecurityIdentifierRoleLinkById( const Guid& id ) = 0;
        virtual void GetSecurityIdentifierRoleLinkCollection( std::vector<std::shared_ptr<SecurityIdentifierRoleLinkObject>>& result ) = 0;
        virtual void GetSecurityIdentifierRoleLinkCollectionByMember( const Guid& member, std::vector<std::shared_ptr<SecurityIdentifierRoleLinkObject>>& result ) = 0;
        virtual void GetSecurityIdentifierRoleLinkCollectionByMemberAndStart( const Guid& member, const DateTime& start, std::vector<std::shared_ptr<SecurityIdentifierRoleLinkObject>>& result ) = 0;
        virtual void GetSecurityIdentifierRoleLinkCollectionByMemberAtStart( const Guid& member, const DateTime& start, std::vector<std::shared_ptr<SecurityIdentifierRoleLinkObject>>& result ) = 0;
        virtual void GetSecurityIdentifierRoleLinkCollectionByMemberFromStart( const Guid& member, const DateTime& start, std::vector<std::shared_ptr<SecurityIdentifierRoleLinkObject>>& result ) = 0;
        virtual void GetSecurityIdentifierRoleLinkCollectionByMemberUntilStart( const Guid& member, const DateTime& start, std::vector<std::shared_ptr<SecurityIdentifierRoleLinkObject>>& result ) = 0;
        virtual void GetSecurityIdentifierRoleLinkCollectionByMemberOverStart( Guid member, DateTime fromStart, DateTime untilStart, std::vector<std::shared_ptr<SecurityIdentifierRoleLinkObject>>& result ) = 0;
        virtual void GetSecurityIdentifierRoleLinkCollectionByRole( const Guid& role, std::vector<std::shared_ptr<SecurityIdentifierRoleLinkObject>>& result ) = 0;
        virtual void GetSecurityIdentifierRoleLinkCollectionByRoleAndStart( const Guid& role, const DateTime& start, std::vector<std::shared_ptr<SecurityIdentifierRoleLinkObject>>& result ) = 0;
        virtual void GetSecurityIdentifierRoleLinkCollectionByRoleAtStart( const Guid& role, const DateTime& start, std::vector<std::shared_ptr<SecurityIdentifierRoleLinkObject>>& result ) = 0;
        virtual void GetSecurityIdentifierRoleLinkCollectionByRoleFromStart( const Guid& role, const DateTime& start, std::vector<std::shared_ptr<SecurityIdentifierRoleLinkObject>>& result ) = 0;
        virtual void GetSecurityIdentifierRoleLinkCollectionByRoleUntilStart( const Guid& role, const DateTime& start, std::vector<std::shared_ptr<SecurityIdentifierRoleLinkObject>>& result ) = 0;
        virtual void GetSecurityIdentifierRoleLinkCollectionByRoleOverStart( Guid role, DateTime fromStart, DateTime untilStart, std::vector<std::shared_ptr<SecurityIdentifierRoleLinkObject>>& result ) = 0;
        virtual void GetSecurityIdentifierRoleLinkCollectionByStart( const DateTime& start, std::vector<std::shared_ptr<SecurityIdentifierRoleLinkObject>>& result ) = 0;
        virtual void GetSecurityIdentifierRoleLinkCollectionAtStart( const DateTime& start, std::vector<std::shared_ptr<SecurityIdentifierRoleLinkObject>>& result ) = 0;
        virtual void GetSecurityIdentifierRoleLinkCollectionFromStart( const DateTime& start, std::vector<std::shared_ptr<SecurityIdentifierRoleLinkObject>>& result ) = 0;
        virtual void GetSecurityIdentifierRoleLinkCollectionUntilStart( const DateTime& start, std::vector<std::shared_ptr<SecurityIdentifierRoleLinkObject>>& result ) = 0;
        virtual void GetSecurityIdentifierRoleLinkCollectionOverStart( DateTime fromStart, DateTime untilStart, std::vector<std::shared_ptr<SecurityIdentifierRoleLinkObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // SecurityLoginSession queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<SecurityLoginSessionObject> GetSecurityLoginSessionById( const Guid& id ) = 0;
        virtual void GetSecurityLoginSessionCollection( std::vector<std::shared_ptr<SecurityLoginSessionObject>>& result ) = 0;
        virtual void GetSecurityLoginSessionCollectionByLogin( const Guid& login, std::vector<std::shared_ptr<SecurityLoginSessionObject>>& result ) = 0;
        virtual void GetSecurityLoginSessionCollectionByLoginAndFromTime( const Guid& login, const DateTime& fromTime, std::vector<std::shared_ptr<SecurityLoginSessionObject>>& result ) = 0;
        virtual void GetSecurityLoginSessionCollectionByLoginAtFromTime( const Guid& login, const DateTime& fromTime, std::vector<std::shared_ptr<SecurityLoginSessionObject>>& result ) = 0;
        virtual void GetSecurityLoginSessionCollectionByLoginFromFromTime( const Guid& login, const DateTime& fromTime, std::vector<std::shared_ptr<SecurityLoginSessionObject>>& result ) = 0;
        virtual void GetSecurityLoginSessionCollectionByLoginUntilFromTime( const Guid& login, const DateTime& fromTime, std::vector<std::shared_ptr<SecurityLoginSessionObject>>& result ) = 0;
        virtual void GetSecurityLoginSessionCollectionByLoginOverFromTime( Guid login, DateTime fromFromTime, DateTime untilFromTime, std::vector<std::shared_ptr<SecurityLoginSessionObject>>& result ) = 0;
        virtual void GetSecurityLoginSessionCollectionByFromTime( const DateTime& fromTime, std::vector<std::shared_ptr<SecurityLoginSessionObject>>& result ) = 0;
        virtual void GetSecurityLoginSessionCollectionAtFromTime( const DateTime& fromTime, std::vector<std::shared_ptr<SecurityLoginSessionObject>>& result ) = 0;
        virtual void GetSecurityLoginSessionCollectionFromFromTime( const DateTime& fromTime, std::vector<std::shared_ptr<SecurityLoginSessionObject>>& result ) = 0;
        virtual void GetSecurityLoginSessionCollectionUntilFromTime( const DateTime& fromTime, std::vector<std::shared_ptr<SecurityLoginSessionObject>>& result ) = 0;
        virtual void GetSecurityLoginSessionCollectionOverFromTime( DateTime fromFromTime, DateTime untilFromTime, std::vector<std::shared_ptr<SecurityLoginSessionObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // SecurityPermission queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<SecurityPermissionObject> GetSecurityPermissionById( const Guid& id ) = 0;
        virtual void GetSecurityPermissionCollection( std::vector<std::shared_ptr<SecurityPermissionObject>>& result ) = 0;
        virtual void GetSecurityPermissionCollectionByIdentifier( const Guid& identifier, std::vector<std::shared_ptr<SecurityPermissionObject>>& result ) = 0;
        virtual void GetSecurityPermissionCollectionByIdentifierAndTypeCode( const Guid& identifier, Int32 typeCode, std::vector<std::shared_ptr<SecurityPermissionObject>>& result ) = 0;
        virtual void GetSecurityPermissionCollectionByIdentifierFromTypeCode( const Guid& identifier, Int32 typeCode, std::vector<std::shared_ptr<SecurityPermissionObject>>& result ) = 0;
        virtual void GetSecurityPermissionCollectionByIdentifierUntilTypeCode( const Guid& identifier, Int32 typeCode, std::vector<std::shared_ptr<SecurityPermissionObject>>& result ) = 0;
        virtual void GetSecurityPermissionCollectionByIdentifierOverTypeCode( Guid identifier, Int32 fromTypeCode, Int32 untilTypeCode, std::vector<std::shared_ptr<SecurityPermissionObject>>& result ) = 0;
        virtual std::shared_ptr<SecurityPermissionObject> GetSecurityPermissionByIdentifierTypeCodeAndTimestamp( const Guid& identifier, Int32 typeCode, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<SecurityPermissionObject> GetSecurityPermissionByIdentifierTypeCodeAtTimestamp( const Guid& identifier, Int32 typeCode, const DateTime& timestamp ) = 0;
        virtual void GetSecurityPermissionByIdentifierTypeCodeFromTimestamp( const Guid& identifier, Int32 typeCode, const DateTime& timestamp, std::vector<std::shared_ptr<SecurityPermissionObject>>& result ) = 0;
        virtual void GetSecurityPermissionByIdentifierTypeCodeUntilTimestamp( const Guid& identifier, Int32 typeCode, const DateTime& timestamp, std::vector<std::shared_ptr<SecurityPermissionObject>>& result ) = 0;
        virtual void GetSecurityPermissionByIdentifierTypeCodeOverTimestamp( Guid identifier, Int32 typeCode, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<SecurityPermissionObject>>& result ) = 0;
        virtual void GetSecurityPermissionCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<SecurityPermissionObject>>& result ) = 0;
        virtual void GetSecurityPermissionCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<SecurityPermissionObject>>& result ) = 0;
        virtual void GetSecurityPermissionCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<SecurityPermissionObject>>& result ) = 0;
        virtual void GetSecurityPermissionCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<SecurityPermissionObject>>& result ) = 0;
        virtual void GetSecurityPermissionCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<SecurityPermissionObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // SingleTimeseriesValue queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<SingleTimeseriesValueObject> GetSingleTimeseriesValueById( const Guid& id ) = 0;
        virtual void GetSingleTimeseriesValueCollection( std::vector<std::shared_ptr<SingleTimeseriesValueObject>>& result ) = 0;
        virtual void GetSingleTimeseriesValueCollectionByTimeseries( const Guid& timeseries, std::vector<std::shared_ptr<SingleTimeseriesValueObject>>& result ) = 0;
        virtual std::shared_ptr<SingleTimeseriesValueObject> GetSingleTimeseriesValueByTimeseriesAndTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<SingleTimeseriesValueObject> GetSingleTimeseriesValueByTimeseriesAtTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual void GetSingleTimeseriesValueByTimeseriesFromTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<SingleTimeseriesValueObject>>& result ) = 0;
        virtual void GetSingleTimeseriesValueByTimeseriesUntilTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<SingleTimeseriesValueObject>>& result ) = 0;
        virtual void GetSingleTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<SingleTimeseriesValueObject>>& result ) = 0;
        virtual void GetSingleTimeseriesValueCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<SingleTimeseriesValueObject>>& result ) = 0;
        virtual void GetSingleTimeseriesValueCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<SingleTimeseriesValueObject>>& result ) = 0;
        virtual void GetSingleTimeseriesValueCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<SingleTimeseriesValueObject>>& result ) = 0;
        virtual void GetSingleTimeseriesValueCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<SingleTimeseriesValueObject>>& result ) = 0;
        virtual void GetSingleTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<SingleTimeseriesValueObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // StringTimeseriesValue queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<StringTimeseriesValueObject> GetStringTimeseriesValueById( const Guid& id ) = 0;
        virtual void GetStringTimeseriesValueCollection( std::vector<std::shared_ptr<StringTimeseriesValueObject>>& result ) = 0;
        virtual void GetStringTimeseriesValueCollectionByTimeseries( const Guid& timeseries, std::vector<std::shared_ptr<StringTimeseriesValueObject>>& result ) = 0;
        virtual std::shared_ptr<StringTimeseriesValueObject> GetStringTimeseriesValueByTimeseriesAndTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<StringTimeseriesValueObject> GetStringTimeseriesValueByTimeseriesAtTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual void GetStringTimeseriesValueByTimeseriesFromTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<StringTimeseriesValueObject>>& result ) = 0;
        virtual void GetStringTimeseriesValueByTimeseriesUntilTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<StringTimeseriesValueObject>>& result ) = 0;
        virtual void GetStringTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<StringTimeseriesValueObject>>& result ) = 0;
        virtual void GetStringTimeseriesValueCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<StringTimeseriesValueObject>>& result ) = 0;
        virtual void GetStringTimeseriesValueCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<StringTimeseriesValueObject>>& result ) = 0;
        virtual void GetStringTimeseriesValueCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<StringTimeseriesValueObject>>& result ) = 0;
        virtual void GetStringTimeseriesValueCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<StringTimeseriesValueObject>>& result ) = 0;
        virtual void GetStringTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<StringTimeseriesValueObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // TimeseriesCatalogElement queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<TimeseriesCatalogElementObject> GetTimeseriesCatalogElementById( const Guid& id ) = 0;
        virtual void GetTimeseriesCatalogElementCollection( std::vector<std::shared_ptr<TimeseriesCatalogElementObject>>& result ) = 0;
        virtual void GetTimeseriesCatalogElementCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<TimeseriesCatalogElementObject>>& result ) = 0;
        virtual void GetTimeseriesCatalogElementCollectionByCatalogIsNull( std::vector<std::shared_ptr<TimeseriesCatalogElementObject>>& result ) = 0;
        virtual std::shared_ptr<TimeseriesCatalogElementObject> GetTimeseriesCatalogElementByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetTimeseriesCatalogElementCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<TimeseriesCatalogElementObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Timeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<TimeseriesObject> GetTimeseriesById( const Guid& id ) = 0;
        virtual void GetTimeseriesCollection( std::vector<std::shared_ptr<TimeseriesObject>>& result ) = 0;
        virtual void GetTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<TimeseriesObject>>& result ) = 0;
        virtual void GetTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<TimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<TimeseriesObject> GetTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<TimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // BinaryTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<BinaryTimeseriesObject> GetBinaryTimeseriesById( const Guid& id ) = 0;
        virtual void GetBinaryTimeseriesCollection( std::vector<std::shared_ptr<BinaryTimeseriesObject>>& result ) = 0;
        virtual void GetBinaryTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<BinaryTimeseriesObject>>& result ) = 0;
        virtual void GetBinaryTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<BinaryTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<BinaryTimeseriesObject> GetBinaryTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetBinaryTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<BinaryTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // BooleanTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<BooleanTimeseriesObject> GetBooleanTimeseriesById( const Guid& id ) = 0;
        virtual void GetBooleanTimeseriesCollection( std::vector<std::shared_ptr<BooleanTimeseriesObject>>& result ) = 0;
        virtual void GetBooleanTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<BooleanTimeseriesObject>>& result ) = 0;
        virtual void GetBooleanTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<BooleanTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<BooleanTimeseriesObject> GetBooleanTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetBooleanTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<BooleanTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisAidToNavigationOffPositionTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisAidToNavigationOffPositionTimeseriesObject> GetAisAidToNavigationOffPositionTimeseriesById( const Guid& id ) = 0;
        virtual void GetAisAidToNavigationOffPositionTimeseriesCollection( std::vector<std::shared_ptr<AisAidToNavigationOffPositionTimeseriesObject>>& result ) = 0;
        virtual void GetAisAidToNavigationOffPositionTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<AisAidToNavigationOffPositionTimeseriesObject>>& result ) = 0;
        virtual void GetAisAidToNavigationOffPositionTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<AisAidToNavigationOffPositionTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<AisAidToNavigationOffPositionTimeseriesObject> GetAisAidToNavigationOffPositionTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetAisAidToNavigationOffPositionTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<AisAidToNavigationOffPositionTimeseriesObject>>& result ) = 0;
        virtual void GetAisAidToNavigationOffPositionTimeseriesCollectionByAidToNavigation( const DBGuid& aidToNavigation, std::vector<std::shared_ptr<AisAidToNavigationOffPositionTimeseriesObject>>& result ) = 0;
        virtual void GetAisAidToNavigationOffPositionTimeseriesCollectionByAidToNavigationIsNull( std::vector<std::shared_ptr<AisAidToNavigationOffPositionTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // DeviceEnabledTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<DeviceEnabledTimeseriesObject> GetDeviceEnabledTimeseriesById( const Guid& id ) = 0;
        virtual void GetDeviceEnabledTimeseriesCollection( std::vector<std::shared_ptr<DeviceEnabledTimeseriesObject>>& result ) = 0;
        virtual void GetDeviceEnabledTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<DeviceEnabledTimeseriesObject>>& result ) = 0;
        virtual void GetDeviceEnabledTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<DeviceEnabledTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<DeviceEnabledTimeseriesObject> GetDeviceEnabledTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetDeviceEnabledTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<DeviceEnabledTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarAutomaticSensitivityTimeControlTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarAutomaticSensitivityTimeControlTimeseriesObject> GetRadarAutomaticSensitivityTimeControlTimeseriesById( const Guid& id ) = 0;
        virtual void GetRadarAutomaticSensitivityTimeControlTimeseriesCollection( std::vector<std::shared_ptr<RadarAutomaticSensitivityTimeControlTimeseriesObject>>& result ) = 0;
        virtual void GetRadarAutomaticSensitivityTimeControlTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<RadarAutomaticSensitivityTimeControlTimeseriesObject>>& result ) = 0;
        virtual void GetRadarAutomaticSensitivityTimeControlTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<RadarAutomaticSensitivityTimeControlTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<RadarAutomaticSensitivityTimeControlTimeseriesObject> GetRadarAutomaticSensitivityTimeControlTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadarAutomaticSensitivityTimeControlTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<RadarAutomaticSensitivityTimeControlTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarBlankSector1Timeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarBlankSector1TimeseriesObject> GetRadarBlankSector1TimeseriesById( const Guid& id ) = 0;
        virtual void GetRadarBlankSector1TimeseriesCollection( std::vector<std::shared_ptr<RadarBlankSector1TimeseriesObject>>& result ) = 0;
        virtual void GetRadarBlankSector1TimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<RadarBlankSector1TimeseriesObject>>& result ) = 0;
        virtual void GetRadarBlankSector1TimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<RadarBlankSector1TimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<RadarBlankSector1TimeseriesObject> GetRadarBlankSector1TimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadarBlankSector1TimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<RadarBlankSector1TimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarBlankSector2Timeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarBlankSector2TimeseriesObject> GetRadarBlankSector2TimeseriesById( const Guid& id ) = 0;
        virtual void GetRadarBlankSector2TimeseriesCollection( std::vector<std::shared_ptr<RadarBlankSector2TimeseriesObject>>& result ) = 0;
        virtual void GetRadarBlankSector2TimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<RadarBlankSector2TimeseriesObject>>& result ) = 0;
        virtual void GetRadarBlankSector2TimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<RadarBlankSector2TimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<RadarBlankSector2TimeseriesObject> GetRadarBlankSector2TimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadarBlankSector2TimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<RadarBlankSector2TimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarEnableAutomaticFrequencyControlTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarEnableAutomaticFrequencyControlTimeseriesObject> GetRadarEnableAutomaticFrequencyControlTimeseriesById( const Guid& id ) = 0;
        virtual void GetRadarEnableAutomaticFrequencyControlTimeseriesCollection( std::vector<std::shared_ptr<RadarEnableAutomaticFrequencyControlTimeseriesObject>>& result ) = 0;
        virtual void GetRadarEnableAutomaticFrequencyControlTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<RadarEnableAutomaticFrequencyControlTimeseriesObject>>& result ) = 0;
        virtual void GetRadarEnableAutomaticFrequencyControlTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<RadarEnableAutomaticFrequencyControlTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<RadarEnableAutomaticFrequencyControlTimeseriesObject> GetRadarEnableAutomaticFrequencyControlTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadarEnableAutomaticFrequencyControlTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<RadarEnableAutomaticFrequencyControlTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarEnableFastTimeConstantTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarEnableFastTimeConstantTimeseriesObject> GetRadarEnableFastTimeConstantTimeseriesById( const Guid& id ) = 0;
        virtual void GetRadarEnableFastTimeConstantTimeseriesCollection( std::vector<std::shared_ptr<RadarEnableFastTimeConstantTimeseriesObject>>& result ) = 0;
        virtual void GetRadarEnableFastTimeConstantTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<RadarEnableFastTimeConstantTimeseriesObject>>& result ) = 0;
        virtual void GetRadarEnableFastTimeConstantTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<RadarEnableFastTimeConstantTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<RadarEnableFastTimeConstantTimeseriesObject> GetRadarEnableFastTimeConstantTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadarEnableFastTimeConstantTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<RadarEnableFastTimeConstantTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarEnableSensitivityTimeControlTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarEnableSensitivityTimeControlTimeseriesObject> GetRadarEnableSensitivityTimeControlTimeseriesById( const Guid& id ) = 0;
        virtual void GetRadarEnableSensitivityTimeControlTimeseriesCollection( std::vector<std::shared_ptr<RadarEnableSensitivityTimeControlTimeseriesObject>>& result ) = 0;
        virtual void GetRadarEnableSensitivityTimeControlTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<RadarEnableSensitivityTimeControlTimeseriesObject>>& result ) = 0;
        virtual void GetRadarEnableSensitivityTimeControlTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<RadarEnableSensitivityTimeControlTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<RadarEnableSensitivityTimeControlTimeseriesObject> GetRadarEnableSensitivityTimeControlTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadarEnableSensitivityTimeControlTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<RadarEnableSensitivityTimeControlTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarPowerOnTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarPowerOnTimeseriesObject> GetRadarPowerOnTimeseriesById( const Guid& id ) = 0;
        virtual void GetRadarPowerOnTimeseriesCollection( std::vector<std::shared_ptr<RadarPowerOnTimeseriesObject>>& result ) = 0;
        virtual void GetRadarPowerOnTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<RadarPowerOnTimeseriesObject>>& result ) = 0;
        virtual void GetRadarPowerOnTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<RadarPowerOnTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<RadarPowerOnTimeseriesObject> GetRadarPowerOnTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadarPowerOnTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<RadarPowerOnTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarSaveSettingsTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarSaveSettingsTimeseriesObject> GetRadarSaveSettingsTimeseriesById( const Guid& id ) = 0;
        virtual void GetRadarSaveSettingsTimeseriesCollection( std::vector<std::shared_ptr<RadarSaveSettingsTimeseriesObject>>& result ) = 0;
        virtual void GetRadarSaveSettingsTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<RadarSaveSettingsTimeseriesObject>>& result ) = 0;
        virtual void GetRadarSaveSettingsTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<RadarSaveSettingsTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<RadarSaveSettingsTimeseriesObject> GetRadarSaveSettingsTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadarSaveSettingsTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<RadarSaveSettingsTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarTrackingTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarTrackingTimeseriesObject> GetRadarTrackingTimeseriesById( const Guid& id ) = 0;
        virtual void GetRadarTrackingTimeseriesCollection( std::vector<std::shared_ptr<RadarTrackingTimeseriesObject>>& result ) = 0;
        virtual void GetRadarTrackingTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<RadarTrackingTimeseriesObject>>& result ) = 0;
        virtual void GetRadarTrackingTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<RadarTrackingTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<RadarTrackingTimeseriesObject> GetRadarTrackingTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadarTrackingTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<RadarTrackingTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // MediaProxySessionEnabledTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<MediaProxySessionEnabledTimeseriesObject> GetMediaProxySessionEnabledTimeseriesById( const Guid& id ) = 0;
        virtual void GetMediaProxySessionEnabledTimeseriesCollection( std::vector<std::shared_ptr<MediaProxySessionEnabledTimeseriesObject>>& result ) = 0;
        virtual void GetMediaProxySessionEnabledTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<MediaProxySessionEnabledTimeseriesObject>>& result ) = 0;
        virtual void GetMediaProxySessionEnabledTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<MediaProxySessionEnabledTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<MediaProxySessionEnabledTimeseriesObject> GetMediaProxySessionEnabledTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetMediaProxySessionEnabledTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<MediaProxySessionEnabledTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // MediaServiceEnabledTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<MediaServiceEnabledTimeseriesObject> GetMediaServiceEnabledTimeseriesById( const Guid& id ) = 0;
        virtual void GetMediaServiceEnabledTimeseriesCollection( std::vector<std::shared_ptr<MediaServiceEnabledTimeseriesObject>>& result ) = 0;
        virtual void GetMediaServiceEnabledTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<MediaServiceEnabledTimeseriesObject>>& result ) = 0;
        virtual void GetMediaServiceEnabledTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<MediaServiceEnabledTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<MediaServiceEnabledTimeseriesObject> GetMediaServiceEnabledTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetMediaServiceEnabledTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<MediaServiceEnabledTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // ByteTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ByteTimeseriesObject> GetByteTimeseriesById( const Guid& id ) = 0;
        virtual void GetByteTimeseriesCollection( std::vector<std::shared_ptr<ByteTimeseriesObject>>& result ) = 0;
        virtual void GetByteTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<ByteTimeseriesObject>>& result ) = 0;
        virtual void GetByteTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<ByteTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<ByteTimeseriesObject> GetByteTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetByteTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<ByteTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // DateTimeTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<DateTimeTimeseriesObject> GetDateTimeTimeseriesById( const Guid& id ) = 0;
        virtual void GetDateTimeTimeseriesCollection( std::vector<std::shared_ptr<DateTimeTimeseriesObject>>& result ) = 0;
        virtual void GetDateTimeTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<DateTimeTimeseriesObject>>& result ) = 0;
        virtual void GetDateTimeTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<DateTimeTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<DateTimeTimeseriesObject> GetDateTimeTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetDateTimeTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<DateTimeTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // DoubleTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<DoubleTimeseriesObject> GetDoubleTimeseriesById( const Guid& id ) = 0;
        virtual void GetDoubleTimeseriesCollection( std::vector<std::shared_ptr<DoubleTimeseriesObject>>& result ) = 0;
        virtual void GetDoubleTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<DoubleTimeseriesObject>>& result ) = 0;
        virtual void GetDoubleTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<DoubleTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<DoubleTimeseriesObject> GetDoubleTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetDoubleTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<DoubleTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // GNSSAltitudeTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GNSSAltitudeTimeseriesObject> GetGNSSAltitudeTimeseriesById( const Guid& id ) = 0;
        virtual void GetGNSSAltitudeTimeseriesCollection( std::vector<std::shared_ptr<GNSSAltitudeTimeseriesObject>>& result ) = 0;
        virtual void GetGNSSAltitudeTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<GNSSAltitudeTimeseriesObject>>& result ) = 0;
        virtual void GetGNSSAltitudeTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<GNSSAltitudeTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<GNSSAltitudeTimeseriesObject> GetGNSSAltitudeTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetGNSSAltitudeTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<GNSSAltitudeTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // GNSSLatitudeTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GNSSLatitudeTimeseriesObject> GetGNSSLatitudeTimeseriesById( const Guid& id ) = 0;
        virtual void GetGNSSLatitudeTimeseriesCollection( std::vector<std::shared_ptr<GNSSLatitudeTimeseriesObject>>& result ) = 0;
        virtual void GetGNSSLatitudeTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<GNSSLatitudeTimeseriesObject>>& result ) = 0;
        virtual void GetGNSSLatitudeTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<GNSSLatitudeTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<GNSSLatitudeTimeseriesObject> GetGNSSLatitudeTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetGNSSLatitudeTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<GNSSLatitudeTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // GNSSLongitudeTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GNSSLongitudeTimeseriesObject> GetGNSSLongitudeTimeseriesById( const Guid& id ) = 0;
        virtual void GetGNSSLongitudeTimeseriesCollection( std::vector<std::shared_ptr<GNSSLongitudeTimeseriesObject>>& result ) = 0;
        virtual void GetGNSSLongitudeTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<GNSSLongitudeTimeseriesObject>>& result ) = 0;
        virtual void GetGNSSLongitudeTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<GNSSLongitudeTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<GNSSLongitudeTimeseriesObject> GetGNSSLongitudeTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetGNSSLongitudeTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<GNSSLongitudeTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // GyroCourseTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GyroCourseTimeseriesObject> GetGyroCourseTimeseriesById( const Guid& id ) = 0;
        virtual void GetGyroCourseTimeseriesCollection( std::vector<std::shared_ptr<GyroCourseTimeseriesObject>>& result ) = 0;
        virtual void GetGyroCourseTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<GyroCourseTimeseriesObject>>& result ) = 0;
        virtual void GetGyroCourseTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<GyroCourseTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<GyroCourseTimeseriesObject> GetGyroCourseTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetGyroCourseTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<GyroCourseTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<GyroCourseTimeseriesObject> GetGyroCourseTimeseriesByGyroDevice( const DBGuid& gyroDevice ) = 0;
        virtual void GetGyroCourseTimeseriesCollectionByGyroDeviceIsNull( std::vector<std::shared_ptr<GyroCourseTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // GyroHeadingMagneticNorthTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GyroHeadingMagneticNorthTimeseriesObject> GetGyroHeadingMagneticNorthTimeseriesById( const Guid& id ) = 0;
        virtual void GetGyroHeadingMagneticNorthTimeseriesCollection( std::vector<std::shared_ptr<GyroHeadingMagneticNorthTimeseriesObject>>& result ) = 0;
        virtual void GetGyroHeadingMagneticNorthTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<GyroHeadingMagneticNorthTimeseriesObject>>& result ) = 0;
        virtual void GetGyroHeadingMagneticNorthTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<GyroHeadingMagneticNorthTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<GyroHeadingMagneticNorthTimeseriesObject> GetGyroHeadingMagneticNorthTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetGyroHeadingMagneticNorthTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<GyroHeadingMagneticNorthTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<GyroHeadingMagneticNorthTimeseriesObject> GetGyroHeadingMagneticNorthTimeseriesByGyroDevice( const DBGuid& gyroDevice ) = 0;
        virtual void GetGyroHeadingMagneticNorthTimeseriesCollectionByGyroDeviceIsNull( std::vector<std::shared_ptr<GyroHeadingMagneticNorthTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // GyroHeadingTrueNorthTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GyroHeadingTrueNorthTimeseriesObject> GetGyroHeadingTrueNorthTimeseriesById( const Guid& id ) = 0;
        virtual void GetGyroHeadingTrueNorthTimeseriesCollection( std::vector<std::shared_ptr<GyroHeadingTrueNorthTimeseriesObject>>& result ) = 0;
        virtual void GetGyroHeadingTrueNorthTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<GyroHeadingTrueNorthTimeseriesObject>>& result ) = 0;
        virtual void GetGyroHeadingTrueNorthTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<GyroHeadingTrueNorthTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<GyroHeadingTrueNorthTimeseriesObject> GetGyroHeadingTrueNorthTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetGyroHeadingTrueNorthTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<GyroHeadingTrueNorthTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<GyroHeadingTrueNorthTimeseriesObject> GetGyroHeadingTrueNorthTimeseriesByGyroDevice( const DBGuid& gyroDevice ) = 0;
        virtual void GetGyroHeadingTrueNorthTimeseriesCollectionByGyroDeviceIsNull( std::vector<std::shared_ptr<GyroHeadingTrueNorthTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // GyroPitchTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GyroPitchTimeseriesObject> GetGyroPitchTimeseriesById( const Guid& id ) = 0;
        virtual void GetGyroPitchTimeseriesCollection( std::vector<std::shared_ptr<GyroPitchTimeseriesObject>>& result ) = 0;
        virtual void GetGyroPitchTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<GyroPitchTimeseriesObject>>& result ) = 0;
        virtual void GetGyroPitchTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<GyroPitchTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<GyroPitchTimeseriesObject> GetGyroPitchTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetGyroPitchTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<GyroPitchTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<GyroPitchTimeseriesObject> GetGyroPitchTimeseriesByGyroDevice( const DBGuid& gyroDevice ) = 0;
        virtual void GetGyroPitchTimeseriesCollectionByGyroDeviceIsNull( std::vector<std::shared_ptr<GyroPitchTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // GyroRateOfTurnTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GyroRateOfTurnTimeseriesObject> GetGyroRateOfTurnTimeseriesById( const Guid& id ) = 0;
        virtual void GetGyroRateOfTurnTimeseriesCollection( std::vector<std::shared_ptr<GyroRateOfTurnTimeseriesObject>>& result ) = 0;
        virtual void GetGyroRateOfTurnTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<GyroRateOfTurnTimeseriesObject>>& result ) = 0;
        virtual void GetGyroRateOfTurnTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<GyroRateOfTurnTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<GyroRateOfTurnTimeseriesObject> GetGyroRateOfTurnTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetGyroRateOfTurnTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<GyroRateOfTurnTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<GyroRateOfTurnTimeseriesObject> GetGyroRateOfTurnTimeseriesByGyroDevice( const DBGuid& gyroDevice ) = 0;
        virtual void GetGyroRateOfTurnTimeseriesCollectionByGyroDeviceIsNull( std::vector<std::shared_ptr<GyroRateOfTurnTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // GyroRollTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GyroRollTimeseriesObject> GetGyroRollTimeseriesById( const Guid& id ) = 0;
        virtual void GetGyroRollTimeseriesCollection( std::vector<std::shared_ptr<GyroRollTimeseriesObject>>& result ) = 0;
        virtual void GetGyroRollTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<GyroRollTimeseriesObject>>& result ) = 0;
        virtual void GetGyroRollTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<GyroRollTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<GyroRollTimeseriesObject> GetGyroRollTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetGyroRollTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<GyroRollTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<GyroRollTimeseriesObject> GetGyroRollTimeseriesByGyroDevice( const DBGuid& gyroDevice ) = 0;
        virtual void GetGyroRollTimeseriesCollectionByGyroDeviceIsNull( std::vector<std::shared_ptr<GyroRollTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // GyroSpeedTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GyroSpeedTimeseriesObject> GetGyroSpeedTimeseriesById( const Guid& id ) = 0;
        virtual void GetGyroSpeedTimeseriesCollection( std::vector<std::shared_ptr<GyroSpeedTimeseriesObject>>& result ) = 0;
        virtual void GetGyroSpeedTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<GyroSpeedTimeseriesObject>>& result ) = 0;
        virtual void GetGyroSpeedTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<GyroSpeedTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<GyroSpeedTimeseriesObject> GetGyroSpeedTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetGyroSpeedTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<GyroSpeedTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<GyroSpeedTimeseriesObject> GetGyroSpeedTimeseriesByGyroDevice( const DBGuid& gyroDevice ) = 0;
        virtual void GetGyroSpeedTimeseriesCollectionByGyroDeviceIsNull( std::vector<std::shared_ptr<GyroSpeedTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarLatitudeTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarLatitudeTimeseriesObject> GetRadarLatitudeTimeseriesById( const Guid& id ) = 0;
        virtual void GetRadarLatitudeTimeseriesCollection( std::vector<std::shared_ptr<RadarLatitudeTimeseriesObject>>& result ) = 0;
        virtual void GetRadarLatitudeTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<RadarLatitudeTimeseriesObject>>& result ) = 0;
        virtual void GetRadarLatitudeTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<RadarLatitudeTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<RadarLatitudeTimeseriesObject> GetRadarLatitudeTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadarLatitudeTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<RadarLatitudeTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarLongitudeTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarLongitudeTimeseriesObject> GetRadarLongitudeTimeseriesById( const Guid& id ) = 0;
        virtual void GetRadarLongitudeTimeseriesCollection( std::vector<std::shared_ptr<RadarLongitudeTimeseriesObject>>& result ) = 0;
        virtual void GetRadarLongitudeTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<RadarLongitudeTimeseriesObject>>& result ) = 0;
        virtual void GetRadarLongitudeTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<RadarLongitudeTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<RadarLongitudeTimeseriesObject> GetRadarLongitudeTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadarLongitudeTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<RadarLongitudeTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadomeDewPointTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadomeDewPointTimeseriesObject> GetRadomeDewPointTimeseriesById( const Guid& id ) = 0;
        virtual void GetRadomeDewPointTimeseriesCollection( std::vector<std::shared_ptr<RadomeDewPointTimeseriesObject>>& result ) = 0;
        virtual void GetRadomeDewPointTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<RadomeDewPointTimeseriesObject>>& result ) = 0;
        virtual void GetRadomeDewPointTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<RadomeDewPointTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<RadomeDewPointTimeseriesObject> GetRadomeDewPointTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadomeDewPointTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<RadomeDewPointTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadomePressureTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadomePressureTimeseriesObject> GetRadomePressureTimeseriesById( const Guid& id ) = 0;
        virtual void GetRadomePressureTimeseriesCollection( std::vector<std::shared_ptr<RadomePressureTimeseriesObject>>& result ) = 0;
        virtual void GetRadomePressureTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<RadomePressureTimeseriesObject>>& result ) = 0;
        virtual void GetRadomePressureTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<RadomePressureTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<RadomePressureTimeseriesObject> GetRadomePressureTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadomePressureTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<RadomePressureTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadomeTemperatureTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadomeTemperatureTimeseriesObject> GetRadomeTemperatureTimeseriesById( const Guid& id ) = 0;
        virtual void GetRadomeTemperatureTimeseriesCollection( std::vector<std::shared_ptr<RadomeTemperatureTimeseriesObject>>& result ) = 0;
        virtual void GetRadomeTemperatureTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<RadomeTemperatureTimeseriesObject>>& result ) = 0;
        virtual void GetRadomeTemperatureTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<RadomeTemperatureTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<RadomeTemperatureTimeseriesObject> GetRadomeTemperatureTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadomeTemperatureTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<RadomeTemperatureTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // VesselDraughtTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<VesselDraughtTimeseriesObject> GetVesselDraughtTimeseriesById( const Guid& id ) = 0;
        virtual void GetVesselDraughtTimeseriesCollection( std::vector<std::shared_ptr<VesselDraughtTimeseriesObject>>& result ) = 0;
        virtual void GetVesselDraughtTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<VesselDraughtTimeseriesObject>>& result ) = 0;
        virtual void GetVesselDraughtTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<VesselDraughtTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<VesselDraughtTimeseriesObject> GetVesselDraughtTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetVesselDraughtTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<VesselDraughtTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // ViewLatitudeTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ViewLatitudeTimeseriesObject> GetViewLatitudeTimeseriesById( const Guid& id ) = 0;
        virtual void GetViewLatitudeTimeseriesCollection( std::vector<std::shared_ptr<ViewLatitudeTimeseriesObject>>& result ) = 0;
        virtual void GetViewLatitudeTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<ViewLatitudeTimeseriesObject>>& result ) = 0;
        virtual void GetViewLatitudeTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<ViewLatitudeTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<ViewLatitudeTimeseriesObject> GetViewLatitudeTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetViewLatitudeTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<ViewLatitudeTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // ViewLongitudeTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ViewLongitudeTimeseriesObject> GetViewLongitudeTimeseriesById( const Guid& id ) = 0;
        virtual void GetViewLongitudeTimeseriesCollection( std::vector<std::shared_ptr<ViewLongitudeTimeseriesObject>>& result ) = 0;
        virtual void GetViewLongitudeTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<ViewLongitudeTimeseriesObject>>& result ) = 0;
        virtual void GetViewLongitudeTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<ViewLongitudeTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<ViewLongitudeTimeseriesObject> GetViewLongitudeTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetViewLongitudeTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<ViewLongitudeTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // ViewZoomLevelTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ViewZoomLevelTimeseriesObject> GetViewZoomLevelTimeseriesById( const Guid& id ) = 0;
        virtual void GetViewZoomLevelTimeseriesCollection( std::vector<std::shared_ptr<ViewZoomLevelTimeseriesObject>>& result ) = 0;
        virtual void GetViewZoomLevelTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<ViewZoomLevelTimeseriesObject>>& result ) = 0;
        virtual void GetViewZoomLevelTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<ViewZoomLevelTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<ViewZoomLevelTimeseriesObject> GetViewZoomLevelTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetViewZoomLevelTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<ViewZoomLevelTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // WeatherStationAbsoluteHumidityTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<WeatherStationAbsoluteHumidityTimeseriesObject> GetWeatherStationAbsoluteHumidityTimeseriesById( const Guid& id ) = 0;
        virtual void GetWeatherStationAbsoluteHumidityTimeseriesCollection( std::vector<std::shared_ptr<WeatherStationAbsoluteHumidityTimeseriesObject>>& result ) = 0;
        virtual void GetWeatherStationAbsoluteHumidityTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<WeatherStationAbsoluteHumidityTimeseriesObject>>& result ) = 0;
        virtual void GetWeatherStationAbsoluteHumidityTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<WeatherStationAbsoluteHumidityTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<WeatherStationAbsoluteHumidityTimeseriesObject> GetWeatherStationAbsoluteHumidityTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetWeatherStationAbsoluteHumidityTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<WeatherStationAbsoluteHumidityTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<WeatherStationAbsoluteHumidityTimeseriesObject> GetWeatherStationAbsoluteHumidityTimeseriesByWeatherStation( const DBGuid& weatherStation ) = 0;
        virtual void GetWeatherStationAbsoluteHumidityTimeseriesCollectionByWeatherStationIsNull( std::vector<std::shared_ptr<WeatherStationAbsoluteHumidityTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // WeatherStationAirTemperatureTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<WeatherStationAirTemperatureTimeseriesObject> GetWeatherStationAirTemperatureTimeseriesById( const Guid& id ) = 0;
        virtual void GetWeatherStationAirTemperatureTimeseriesCollection( std::vector<std::shared_ptr<WeatherStationAirTemperatureTimeseriesObject>>& result ) = 0;
        virtual void GetWeatherStationAirTemperatureTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<WeatherStationAirTemperatureTimeseriesObject>>& result ) = 0;
        virtual void GetWeatherStationAirTemperatureTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<WeatherStationAirTemperatureTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<WeatherStationAirTemperatureTimeseriesObject> GetWeatherStationAirTemperatureTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetWeatherStationAirTemperatureTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<WeatherStationAirTemperatureTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<WeatherStationAirTemperatureTimeseriesObject> GetWeatherStationAirTemperatureTimeseriesByWeatherStation( const DBGuid& weatherStation ) = 0;
        virtual void GetWeatherStationAirTemperatureTimeseriesCollectionByWeatherStationIsNull( std::vector<std::shared_ptr<WeatherStationAirTemperatureTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // WeatherStationBarometricPressureTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<WeatherStationBarometricPressureTimeseriesObject> GetWeatherStationBarometricPressureTimeseriesById( const Guid& id ) = 0;
        virtual void GetWeatherStationBarometricPressureTimeseriesCollection( std::vector<std::shared_ptr<WeatherStationBarometricPressureTimeseriesObject>>& result ) = 0;
        virtual void GetWeatherStationBarometricPressureTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<WeatherStationBarometricPressureTimeseriesObject>>& result ) = 0;
        virtual void GetWeatherStationBarometricPressureTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<WeatherStationBarometricPressureTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<WeatherStationBarometricPressureTimeseriesObject> GetWeatherStationBarometricPressureTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetWeatherStationBarometricPressureTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<WeatherStationBarometricPressureTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<WeatherStationBarometricPressureTimeseriesObject> GetWeatherStationBarometricPressureTimeseriesByWeatherStation( const DBGuid& weatherStation ) = 0;
        virtual void GetWeatherStationBarometricPressureTimeseriesCollectionByWeatherStationIsNull( std::vector<std::shared_ptr<WeatherStationBarometricPressureTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // WeatherStationDewPointTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<WeatherStationDewPointTimeseriesObject> GetWeatherStationDewPointTimeseriesById( const Guid& id ) = 0;
        virtual void GetWeatherStationDewPointTimeseriesCollection( std::vector<std::shared_ptr<WeatherStationDewPointTimeseriesObject>>& result ) = 0;
        virtual void GetWeatherStationDewPointTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<WeatherStationDewPointTimeseriesObject>>& result ) = 0;
        virtual void GetWeatherStationDewPointTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<WeatherStationDewPointTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<WeatherStationDewPointTimeseriesObject> GetWeatherStationDewPointTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetWeatherStationDewPointTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<WeatherStationDewPointTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<WeatherStationDewPointTimeseriesObject> GetWeatherStationDewPointTimeseriesByWeatherStation( const DBGuid& weatherStation ) = 0;
        virtual void GetWeatherStationDewPointTimeseriesCollectionByWeatherStationIsNull( std::vector<std::shared_ptr<WeatherStationDewPointTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // WeatherStationRelativeHumidityTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<WeatherStationRelativeHumidityTimeseriesObject> GetWeatherStationRelativeHumidityTimeseriesById( const Guid& id ) = 0;
        virtual void GetWeatherStationRelativeHumidityTimeseriesCollection( std::vector<std::shared_ptr<WeatherStationRelativeHumidityTimeseriesObject>>& result ) = 0;
        virtual void GetWeatherStationRelativeHumidityTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<WeatherStationRelativeHumidityTimeseriesObject>>& result ) = 0;
        virtual void GetWeatherStationRelativeHumidityTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<WeatherStationRelativeHumidityTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<WeatherStationRelativeHumidityTimeseriesObject> GetWeatherStationRelativeHumidityTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetWeatherStationRelativeHumidityTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<WeatherStationRelativeHumidityTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<WeatherStationRelativeHumidityTimeseriesObject> GetWeatherStationRelativeHumidityTimeseriesByWeatherStation( const DBGuid& weatherStation ) = 0;
        virtual void GetWeatherStationRelativeHumidityTimeseriesCollectionByWeatherStationIsNull( std::vector<std::shared_ptr<WeatherStationRelativeHumidityTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // WeatherStationWaterTemperatureTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<WeatherStationWaterTemperatureTimeseriesObject> GetWeatherStationWaterTemperatureTimeseriesById( const Guid& id ) = 0;
        virtual void GetWeatherStationWaterTemperatureTimeseriesCollection( std::vector<std::shared_ptr<WeatherStationWaterTemperatureTimeseriesObject>>& result ) = 0;
        virtual void GetWeatherStationWaterTemperatureTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<WeatherStationWaterTemperatureTimeseriesObject>>& result ) = 0;
        virtual void GetWeatherStationWaterTemperatureTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<WeatherStationWaterTemperatureTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<WeatherStationWaterTemperatureTimeseriesObject> GetWeatherStationWaterTemperatureTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetWeatherStationWaterTemperatureTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<WeatherStationWaterTemperatureTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<WeatherStationWaterTemperatureTimeseriesObject> GetWeatherStationWaterTemperatureTimeseriesByWeatherStation( const DBGuid& weatherStation ) = 0;
        virtual void GetWeatherStationWaterTemperatureTimeseriesCollectionByWeatherStationIsNull( std::vector<std::shared_ptr<WeatherStationWaterTemperatureTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // WeatherStationWindDirectionTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<WeatherStationWindDirectionTimeseriesObject> GetWeatherStationWindDirectionTimeseriesById( const Guid& id ) = 0;
        virtual void GetWeatherStationWindDirectionTimeseriesCollection( std::vector<std::shared_ptr<WeatherStationWindDirectionTimeseriesObject>>& result ) = 0;
        virtual void GetWeatherStationWindDirectionTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<WeatherStationWindDirectionTimeseriesObject>>& result ) = 0;
        virtual void GetWeatherStationWindDirectionTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<WeatherStationWindDirectionTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<WeatherStationWindDirectionTimeseriesObject> GetWeatherStationWindDirectionTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetWeatherStationWindDirectionTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<WeatherStationWindDirectionTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<WeatherStationWindDirectionTimeseriesObject> GetWeatherStationWindDirectionTimeseriesByWeatherStation( const DBGuid& weatherStation ) = 0;
        virtual void GetWeatherStationWindDirectionTimeseriesCollectionByWeatherStationIsNull( std::vector<std::shared_ptr<WeatherStationWindDirectionTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // WeatherStationWindSpeedTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<WeatherStationWindSpeedTimeseriesObject> GetWeatherStationWindSpeedTimeseriesById( const Guid& id ) = 0;
        virtual void GetWeatherStationWindSpeedTimeseriesCollection( std::vector<std::shared_ptr<WeatherStationWindSpeedTimeseriesObject>>& result ) = 0;
        virtual void GetWeatherStationWindSpeedTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<WeatherStationWindSpeedTimeseriesObject>>& result ) = 0;
        virtual void GetWeatherStationWindSpeedTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<WeatherStationWindSpeedTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<WeatherStationWindSpeedTimeseriesObject> GetWeatherStationWindSpeedTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetWeatherStationWindSpeedTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<WeatherStationWindSpeedTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<WeatherStationWindSpeedTimeseriesObject> GetWeatherStationWindSpeedTimeseriesByWeatherStation( const DBGuid& weatherStation ) = 0;
        virtual void GetWeatherStationWindSpeedTimeseriesCollectionByWeatherStationIsNull( std::vector<std::shared_ptr<WeatherStationWindSpeedTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // GeoPosition2DTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GeoPosition2DTimeseriesObject> GetGeoPosition2DTimeseriesById( const Guid& id ) = 0;
        virtual void GetGeoPosition2DTimeseriesCollection( std::vector<std::shared_ptr<GeoPosition2DTimeseriesObject>>& result ) = 0;
        virtual void GetGeoPosition2DTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<GeoPosition2DTimeseriesObject>>& result ) = 0;
        virtual void GetGeoPosition2DTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<GeoPosition2DTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<GeoPosition2DTimeseriesObject> GetGeoPosition2DTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetGeoPosition2DTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<GeoPosition2DTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // AisAidToNavigationPositionTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<AisAidToNavigationPositionTimeseriesObject> GetAisAidToNavigationPositionTimeseriesById( const Guid& id ) = 0;
        virtual void GetAisAidToNavigationPositionTimeseriesCollection( std::vector<std::shared_ptr<AisAidToNavigationPositionTimeseriesObject>>& result ) = 0;
        virtual void GetAisAidToNavigationPositionTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<AisAidToNavigationPositionTimeseriesObject>>& result ) = 0;
        virtual void GetAisAidToNavigationPositionTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<AisAidToNavigationPositionTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<AisAidToNavigationPositionTimeseriesObject> GetAisAidToNavigationPositionTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetAisAidToNavigationPositionTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<AisAidToNavigationPositionTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // GeoPosition3DTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GeoPosition3DTimeseriesObject> GetGeoPosition3DTimeseriesById( const Guid& id ) = 0;
        virtual void GetGeoPosition3DTimeseriesCollection( std::vector<std::shared_ptr<GeoPosition3DTimeseriesObject>>& result ) = 0;
        virtual void GetGeoPosition3DTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<GeoPosition3DTimeseriesObject>>& result ) = 0;
        virtual void GetGeoPosition3DTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<GeoPosition3DTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<GeoPosition3DTimeseriesObject> GetGeoPosition3DTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetGeoPosition3DTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<GeoPosition3DTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // GuidTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<GuidTimeseriesObject> GetGuidTimeseriesById( const Guid& id ) = 0;
        virtual void GetGuidTimeseriesCollection( std::vector<std::shared_ptr<GuidTimeseriesObject>>& result ) = 0;
        virtual void GetGuidTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<GuidTimeseriesObject>>& result ) = 0;
        virtual void GetGuidTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<GuidTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<GuidTimeseriesObject> GetGuidTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetGuidTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<GuidTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Int16Timeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<Int16TimeseriesObject> GetInt16TimeseriesById( const Guid& id ) = 0;
        virtual void GetInt16TimeseriesCollection( std::vector<std::shared_ptr<Int16TimeseriesObject>>& result ) = 0;
        virtual void GetInt16TimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<Int16TimeseriesObject>>& result ) = 0;
        virtual void GetInt16TimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<Int16TimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<Int16TimeseriesObject> GetInt16TimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetInt16TimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<Int16TimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Int32Timeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<Int32TimeseriesObject> GetInt32TimeseriesById( const Guid& id ) = 0;
        virtual void GetInt32TimeseriesCollection( std::vector<std::shared_ptr<Int32TimeseriesObject>>& result ) = 0;
        virtual void GetInt32TimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<Int32TimeseriesObject>>& result ) = 0;
        virtual void GetInt32TimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<Int32TimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<Int32TimeseriesObject> GetInt32TimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetInt32TimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<Int32TimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarAzimuthOffsetTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarAzimuthOffsetTimeseriesObject> GetRadarAzimuthOffsetTimeseriesById( const Guid& id ) = 0;
        virtual void GetRadarAzimuthOffsetTimeseriesCollection( std::vector<std::shared_ptr<RadarAzimuthOffsetTimeseriesObject>>& result ) = 0;
        virtual void GetRadarAzimuthOffsetTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<RadarAzimuthOffsetTimeseriesObject>>& result ) = 0;
        virtual void GetRadarAzimuthOffsetTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<RadarAzimuthOffsetTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<RadarAzimuthOffsetTimeseriesObject> GetRadarAzimuthOffsetTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadarAzimuthOffsetTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<RadarAzimuthOffsetTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarFastTimeConstantLevelTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarFastTimeConstantLevelTimeseriesObject> GetRadarFastTimeConstantLevelTimeseriesById( const Guid& id ) = 0;
        virtual void GetRadarFastTimeConstantLevelTimeseriesCollection( std::vector<std::shared_ptr<RadarFastTimeConstantLevelTimeseriesObject>>& result ) = 0;
        virtual void GetRadarFastTimeConstantLevelTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<RadarFastTimeConstantLevelTimeseriesObject>>& result ) = 0;
        virtual void GetRadarFastTimeConstantLevelTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<RadarFastTimeConstantLevelTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<RadarFastTimeConstantLevelTimeseriesObject> GetRadarFastTimeConstantLevelTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadarFastTimeConstantLevelTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<RadarFastTimeConstantLevelTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarFastTimeConstantModeTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarFastTimeConstantModeTimeseriesObject> GetRadarFastTimeConstantModeTimeseriesById( const Guid& id ) = 0;
        virtual void GetRadarFastTimeConstantModeTimeseriesCollection( std::vector<std::shared_ptr<RadarFastTimeConstantModeTimeseriesObject>>& result ) = 0;
        virtual void GetRadarFastTimeConstantModeTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<RadarFastTimeConstantModeTimeseriesObject>>& result ) = 0;
        virtual void GetRadarFastTimeConstantModeTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<RadarFastTimeConstantModeTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<RadarFastTimeConstantModeTimeseriesObject> GetRadarFastTimeConstantModeTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadarFastTimeConstantModeTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<RadarFastTimeConstantModeTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarPulseTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarPulseTimeseriesObject> GetRadarPulseTimeseriesById( const Guid& id ) = 0;
        virtual void GetRadarPulseTimeseriesCollection( std::vector<std::shared_ptr<RadarPulseTimeseriesObject>>& result ) = 0;
        virtual void GetRadarPulseTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<RadarPulseTimeseriesObject>>& result ) = 0;
        virtual void GetRadarPulseTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<RadarPulseTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<RadarPulseTimeseriesObject> GetRadarPulseTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadarPulseTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<RadarPulseTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarSector1EndTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarSector1EndTimeseriesObject> GetRadarSector1EndTimeseriesById( const Guid& id ) = 0;
        virtual void GetRadarSector1EndTimeseriesCollection( std::vector<std::shared_ptr<RadarSector1EndTimeseriesObject>>& result ) = 0;
        virtual void GetRadarSector1EndTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<RadarSector1EndTimeseriesObject>>& result ) = 0;
        virtual void GetRadarSector1EndTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<RadarSector1EndTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<RadarSector1EndTimeseriesObject> GetRadarSector1EndTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadarSector1EndTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<RadarSector1EndTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarSector1StartTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarSector1StartTimeseriesObject> GetRadarSector1StartTimeseriesById( const Guid& id ) = 0;
        virtual void GetRadarSector1StartTimeseriesCollection( std::vector<std::shared_ptr<RadarSector1StartTimeseriesObject>>& result ) = 0;
        virtual void GetRadarSector1StartTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<RadarSector1StartTimeseriesObject>>& result ) = 0;
        virtual void GetRadarSector1StartTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<RadarSector1StartTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<RadarSector1StartTimeseriesObject> GetRadarSector1StartTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadarSector1StartTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<RadarSector1StartTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarSector2EndTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarSector2EndTimeseriesObject> GetRadarSector2EndTimeseriesById( const Guid& id ) = 0;
        virtual void GetRadarSector2EndTimeseriesCollection( std::vector<std::shared_ptr<RadarSector2EndTimeseriesObject>>& result ) = 0;
        virtual void GetRadarSector2EndTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<RadarSector2EndTimeseriesObject>>& result ) = 0;
        virtual void GetRadarSector2EndTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<RadarSector2EndTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<RadarSector2EndTimeseriesObject> GetRadarSector2EndTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadarSector2EndTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<RadarSector2EndTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarSector2StartTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarSector2StartTimeseriesObject> GetRadarSector2StartTimeseriesById( const Guid& id ) = 0;
        virtual void GetRadarSector2StartTimeseriesCollection( std::vector<std::shared_ptr<RadarSector2StartTimeseriesObject>>& result ) = 0;
        virtual void GetRadarSector2StartTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<RadarSector2StartTimeseriesObject>>& result ) = 0;
        virtual void GetRadarSector2StartTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<RadarSector2StartTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<RadarSector2StartTimeseriesObject> GetRadarSector2StartTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadarSector2StartTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<RadarSector2StartTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarSensitivityTimeControlLevelTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarSensitivityTimeControlLevelTimeseriesObject> GetRadarSensitivityTimeControlLevelTimeseriesById( const Guid& id ) = 0;
        virtual void GetRadarSensitivityTimeControlLevelTimeseriesCollection( std::vector<std::shared_ptr<RadarSensitivityTimeControlLevelTimeseriesObject>>& result ) = 0;
        virtual void GetRadarSensitivityTimeControlLevelTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<RadarSensitivityTimeControlLevelTimeseriesObject>>& result ) = 0;
        virtual void GetRadarSensitivityTimeControlLevelTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<RadarSensitivityTimeControlLevelTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<RadarSensitivityTimeControlLevelTimeseriesObject> GetRadarSensitivityTimeControlLevelTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadarSensitivityTimeControlLevelTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<RadarSensitivityTimeControlLevelTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadarTuningTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadarTuningTimeseriesObject> GetRadarTuningTimeseriesById( const Guid& id ) = 0;
        virtual void GetRadarTuningTimeseriesCollection( std::vector<std::shared_ptr<RadarTuningTimeseriesObject>>& result ) = 0;
        virtual void GetRadarTuningTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<RadarTuningTimeseriesObject>>& result ) = 0;
        virtual void GetRadarTuningTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<RadarTuningTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<RadarTuningTimeseriesObject> GetRadarTuningTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadarTuningTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<RadarTuningTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // VesselPersonsOnBoardTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<VesselPersonsOnBoardTimeseriesObject> GetVesselPersonsOnBoardTimeseriesById( const Guid& id ) = 0;
        virtual void GetVesselPersonsOnBoardTimeseriesCollection( std::vector<std::shared_ptr<VesselPersonsOnBoardTimeseriesObject>>& result ) = 0;
        virtual void GetVesselPersonsOnBoardTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<VesselPersonsOnBoardTimeseriesObject>>& result ) = 0;
        virtual void GetVesselPersonsOnBoardTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<VesselPersonsOnBoardTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<VesselPersonsOnBoardTimeseriesObject> GetVesselPersonsOnBoardTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetVesselPersonsOnBoardTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<VesselPersonsOnBoardTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Int64Timeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<Int64TimeseriesObject> GetInt64TimeseriesById( const Guid& id ) = 0;
        virtual void GetInt64TimeseriesCollection( std::vector<std::shared_ptr<Int64TimeseriesObject>>& result ) = 0;
        virtual void GetInt64TimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<Int64TimeseriesObject>>& result ) = 0;
        virtual void GetInt64TimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<Int64TimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<Int64TimeseriesObject> GetInt64TimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetInt64TimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<Int64TimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Position2DTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<Position2DTimeseriesObject> GetPosition2DTimeseriesById( const Guid& id ) = 0;
        virtual void GetPosition2DTimeseriesCollection( std::vector<std::shared_ptr<Position2DTimeseriesObject>>& result ) = 0;
        virtual void GetPosition2DTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<Position2DTimeseriesObject>>& result ) = 0;
        virtual void GetPosition2DTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<Position2DTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<Position2DTimeseriesObject> GetPosition2DTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetPosition2DTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<Position2DTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Position3DTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<Position3DTimeseriesObject> GetPosition3DTimeseriesById( const Guid& id ) = 0;
        virtual void GetPosition3DTimeseriesCollection( std::vector<std::shared_ptr<Position3DTimeseriesObject>>& result ) = 0;
        virtual void GetPosition3DTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<Position3DTimeseriesObject>>& result ) = 0;
        virtual void GetPosition3DTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<Position3DTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<Position3DTimeseriesObject> GetPosition3DTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetPosition3DTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<Position3DTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // ReferenceTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ReferenceTimeseriesObject> GetReferenceTimeseriesById( const Guid& id ) = 0;
        virtual void GetReferenceTimeseriesCollection( std::vector<std::shared_ptr<ReferenceTimeseriesObject>>& result ) = 0;
        virtual void GetReferenceTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<ReferenceTimeseriesObject>>& result ) = 0;
        virtual void GetReferenceTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<ReferenceTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<ReferenceTimeseriesObject> GetReferenceTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetReferenceTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<ReferenceTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // SByteTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<SByteTimeseriesObject> GetSByteTimeseriesById( const Guid& id ) = 0;
        virtual void GetSByteTimeseriesCollection( std::vector<std::shared_ptr<SByteTimeseriesObject>>& result ) = 0;
        virtual void GetSByteTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<SByteTimeseriesObject>>& result ) = 0;
        virtual void GetSByteTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<SByteTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<SByteTimeseriesObject> GetSByteTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetSByteTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<SByteTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // SingleTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<SingleTimeseriesObject> GetSingleTimeseriesById( const Guid& id ) = 0;
        virtual void GetSingleTimeseriesCollection( std::vector<std::shared_ptr<SingleTimeseriesObject>>& result ) = 0;
        virtual void GetSingleTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<SingleTimeseriesObject>>& result ) = 0;
        virtual void GetSingleTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<SingleTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<SingleTimeseriesObject> GetSingleTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetSingleTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<SingleTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // StringTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<StringTimeseriesObject> GetStringTimeseriesById( const Guid& id ) = 0;
        virtual void GetStringTimeseriesCollection( std::vector<std::shared_ptr<StringTimeseriesObject>>& result ) = 0;
        virtual void GetStringTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<StringTimeseriesObject>>& result ) = 0;
        virtual void GetStringTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<StringTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<StringTimeseriesObject> GetStringTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetStringTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<StringTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // TimeSpanTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<TimeSpanTimeseriesObject> GetTimeSpanTimeseriesById( const Guid& id ) = 0;
        virtual void GetTimeSpanTimeseriesCollection( std::vector<std::shared_ptr<TimeSpanTimeseriesObject>>& result ) = 0;
        virtual void GetTimeSpanTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<TimeSpanTimeseriesObject>>& result ) = 0;
        virtual void GetTimeSpanTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<TimeSpanTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<TimeSpanTimeseriesObject> GetTimeSpanTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetTimeSpanTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<TimeSpanTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // UInt16Timeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<UInt16TimeseriesObject> GetUInt16TimeseriesById( const Guid& id ) = 0;
        virtual void GetUInt16TimeseriesCollection( std::vector<std::shared_ptr<UInt16TimeseriesObject>>& result ) = 0;
        virtual void GetUInt16TimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<UInt16TimeseriesObject>>& result ) = 0;
        virtual void GetUInt16TimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<UInt16TimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<UInt16TimeseriesObject> GetUInt16TimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetUInt16TimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<UInt16TimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // UInt32Timeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<UInt32TimeseriesObject> GetUInt32TimeseriesById( const Guid& id ) = 0;
        virtual void GetUInt32TimeseriesCollection( std::vector<std::shared_ptr<UInt32TimeseriesObject>>& result ) = 0;
        virtual void GetUInt32TimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<UInt32TimeseriesObject>>& result ) = 0;
        virtual void GetUInt32TimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<UInt32TimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<UInt32TimeseriesObject> GetUInt32TimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetUInt32TimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<UInt32TimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // RadomeStatusTimeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<RadomeStatusTimeseriesObject> GetRadomeStatusTimeseriesById( const Guid& id ) = 0;
        virtual void GetRadomeStatusTimeseriesCollection( std::vector<std::shared_ptr<RadomeStatusTimeseriesObject>>& result ) = 0;
        virtual void GetRadomeStatusTimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<RadomeStatusTimeseriesObject>>& result ) = 0;
        virtual void GetRadomeStatusTimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<RadomeStatusTimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<RadomeStatusTimeseriesObject> GetRadomeStatusTimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetRadomeStatusTimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<RadomeStatusTimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // UInt64Timeseries queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<UInt64TimeseriesObject> GetUInt64TimeseriesById( const Guid& id ) = 0;
        virtual void GetUInt64TimeseriesCollection( std::vector<std::shared_ptr<UInt64TimeseriesObject>>& result ) = 0;
        virtual void GetUInt64TimeseriesCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<UInt64TimeseriesObject>>& result ) = 0;
        virtual void GetUInt64TimeseriesCollectionByCatalogIsNull( std::vector<std::shared_ptr<UInt64TimeseriesObject>>& result ) = 0;
        virtual std::shared_ptr<UInt64TimeseriesObject> GetUInt64TimeseriesByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetUInt64TimeseriesCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<UInt64TimeseriesObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // TimeseriesCatalog queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<TimeseriesCatalogObject> GetTimeseriesCatalogById( const Guid& id ) = 0;
        virtual void GetTimeseriesCatalogCollection( std::vector<std::shared_ptr<TimeseriesCatalogObject>>& result ) = 0;
        virtual void GetTimeseriesCatalogCollectionByCatalog( const DBGuid& catalog, std::vector<std::shared_ptr<TimeseriesCatalogObject>>& result ) = 0;
        virtual void GetTimeseriesCatalogCollectionByCatalogIsNull( std::vector<std::shared_ptr<TimeseriesCatalogObject>>& result ) = 0;
        virtual std::shared_ptr<TimeseriesCatalogObject> GetTimeseriesCatalogByCatalogAndName( const DBGuid& catalog, const FixedDBWideString<127>& name ) = 0;
        virtual void GetTimeseriesCatalogCollectionByCatalogIsNullAndName( const FixedDBWideString<127>& name, std::vector<std::shared_ptr<TimeseriesCatalogObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // TimeseriesInfo queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<TimeseriesInfoObject> GetTimeseriesInfoById( const Guid& id ) = 0;
        virtual void GetTimeseriesInfoCollection( std::vector<std::shared_ptr<TimeseriesInfoObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // TimeSpanTimeseriesValue queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<TimeSpanTimeseriesValueObject> GetTimeSpanTimeseriesValueById( const Guid& id ) = 0;
        virtual void GetTimeSpanTimeseriesValueCollection( std::vector<std::shared_ptr<TimeSpanTimeseriesValueObject>>& result ) = 0;
        virtual void GetTimeSpanTimeseriesValueCollectionByTimeseries( const Guid& timeseries, std::vector<std::shared_ptr<TimeSpanTimeseriesValueObject>>& result ) = 0;
        virtual std::shared_ptr<TimeSpanTimeseriesValueObject> GetTimeSpanTimeseriesValueByTimeseriesAndTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<TimeSpanTimeseriesValueObject> GetTimeSpanTimeseriesValueByTimeseriesAtTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual void GetTimeSpanTimeseriesValueByTimeseriesFromTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<TimeSpanTimeseriesValueObject>>& result ) = 0;
        virtual void GetTimeSpanTimeseriesValueByTimeseriesUntilTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<TimeSpanTimeseriesValueObject>>& result ) = 0;
        virtual void GetTimeSpanTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<TimeSpanTimeseriesValueObject>>& result ) = 0;
        virtual void GetTimeSpanTimeseriesValueCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TimeSpanTimeseriesValueObject>>& result ) = 0;
        virtual void GetTimeSpanTimeseriesValueCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TimeSpanTimeseriesValueObject>>& result ) = 0;
        virtual void GetTimeSpanTimeseriesValueCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TimeSpanTimeseriesValueObject>>& result ) = 0;
        virtual void GetTimeSpanTimeseriesValueCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TimeSpanTimeseriesValueObject>>& result ) = 0;
        virtual void GetTimeSpanTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<TimeSpanTimeseriesValueObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // TrackableItemTrackLink queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkById( const Guid& id ) = 0;
        virtual void GetTrackableItemTrackLinkCollection( std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        virtual void GetTrackableItemTrackLinkCollectionByItem( const Guid& item, std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        virtual std::shared_ptr<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkByItemAndStart( const Guid& item, const DateTime& start ) = 0;
        virtual std::shared_ptr<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkByItemAtStart( const Guid& item, const DateTime& start ) = 0;
        virtual void GetTrackableItemTrackLinkByItemFromStart( const Guid& item, const DateTime& start, std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        virtual void GetTrackableItemTrackLinkByItemUntilStart( const Guid& item, const DateTime& start, std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        virtual void GetTrackableItemTrackLinkByItemOverStart( Guid item, DateTime fromStart, DateTime untilStart, std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        virtual void GetTrackableItemTrackLinkCollectionByItemAndEnd( const Guid& item, const DBDateTime& end, std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        virtual void GetTrackableItemTrackLinkCollectionByItemAndEndIsNull( const Guid& item, std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        virtual void GetTrackableItemTrackLinkCollectionByItemAtEnd( const Guid& item, const DBDateTime& end, std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        virtual void GetTrackableItemTrackLinkCollectionByItemFromEnd( const Guid& item, const DBDateTime& end, std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        virtual void GetTrackableItemTrackLinkCollectionByItemUntilEnd( const Guid& item, const DBDateTime& end, std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        virtual void GetTrackableItemTrackLinkCollectionByItemOverEnd( Guid item, DateTime fromEnd, DateTime untilEnd, std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        virtual void GetTrackableItemTrackLinkCollectionByTrack( const Guid& track, std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        virtual std::shared_ptr<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkByTrackAndStart( const Guid& track, const DateTime& start ) = 0;
        virtual std::shared_ptr<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkByTrackAtStart( const Guid& track, const DateTime& start ) = 0;
        virtual void GetTrackableItemTrackLinkByTrackFromStart( const Guid& track, const DateTime& start, std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        virtual void GetTrackableItemTrackLinkByTrackUntilStart( const Guid& track, const DateTime& start, std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        virtual void GetTrackableItemTrackLinkByTrackOverStart( Guid track, DateTime fromStart, DateTime untilStart, std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        virtual void GetTrackableItemTrackLinkCollectionByTrackAndEnd( const Guid& track, const DBDateTime& end, std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        virtual void GetTrackableItemTrackLinkCollectionByTrackAndEndIsNull( const Guid& track, std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        virtual void GetTrackableItemTrackLinkCollectionByTrackAtEnd( const Guid& track, const DBDateTime& end, std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        virtual void GetTrackableItemTrackLinkCollectionByTrackFromEnd( const Guid& track, const DBDateTime& end, std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        virtual void GetTrackableItemTrackLinkCollectionByTrackUntilEnd( const Guid& track, const DBDateTime& end, std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        virtual void GetTrackableItemTrackLinkCollectionByTrackOverEnd( Guid track, DateTime fromEnd, DateTime untilEnd, std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        virtual void GetTrackableItemTrackLinkCollectionByStart( const DateTime& start, std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        virtual void GetTrackableItemTrackLinkCollectionAtStart( const DateTime& start, std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        virtual void GetTrackableItemTrackLinkCollectionFromStart( const DateTime& start, std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        virtual void GetTrackableItemTrackLinkCollectionUntilStart( const DateTime& start, std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        virtual void GetTrackableItemTrackLinkCollectionOverStart( DateTime fromStart, DateTime untilStart, std::vector<std::shared_ptr<TrackableItemTrackLinkObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // TrackBase queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<TrackBaseObject> GetTrackBaseById( const Guid& id ) = 0;
        virtual void GetTrackBaseCollection( std::vector<std::shared_ptr<TrackBaseObject>>& result ) = 0;
        virtual void GetTrackBaseCollectionByTracker( const Guid& tracker, std::vector<std::shared_ptr<TrackBaseObject>>& result ) = 0;
        virtual void GetTrackBaseCollectionByTrackerAndTrackNumber( const Guid& tracker, Int64 trackNumber, std::vector<std::shared_ptr<TrackBaseObject>>& result ) = 0;
        virtual void GetTrackBaseCollectionByTrackerFromTrackNumber( const Guid& tracker, Int64 trackNumber, std::vector<std::shared_ptr<TrackBaseObject>>& result ) = 0;
        virtual void GetTrackBaseCollectionByTrackerUntilTrackNumber( const Guid& tracker, Int64 trackNumber, std::vector<std::shared_ptr<TrackBaseObject>>& result ) = 0;
        virtual void GetTrackBaseCollectionByTrackerOverTrackNumber( Guid tracker, Int64 fromTrackNumber, Int64 untilTrackNumber, std::vector<std::shared_ptr<TrackBaseObject>>& result ) = 0;
        virtual std::shared_ptr<TrackBaseObject> GetTrackBaseByTrackerTrackNumberAndTimestamp( const Guid& tracker, Int64 trackNumber, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<TrackBaseObject> GetTrackBaseByTrackerTrackNumberAtTimestamp( const Guid& tracker, Int64 trackNumber, const DateTime& timestamp ) = 0;
        virtual void GetTrackBaseByTrackerTrackNumberFromTimestamp( const Guid& tracker, Int64 trackNumber, const DateTime& timestamp, std::vector<std::shared_ptr<TrackBaseObject>>& result ) = 0;
        virtual void GetTrackBaseByTrackerTrackNumberUntilTimestamp( const Guid& tracker, Int64 trackNumber, const DateTime& timestamp, std::vector<std::shared_ptr<TrackBaseObject>>& result ) = 0;
        virtual void GetTrackBaseByTrackerTrackNumberOverTimestamp( Guid tracker, Int64 trackNumber, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<TrackBaseObject>>& result ) = 0;
        virtual void GetTrackBaseCollectionByTrackerAndTimestamp( const Guid& tracker, const DateTime& timestamp, std::vector<std::shared_ptr<TrackBaseObject>>& result ) = 0;
        virtual void GetTrackBaseCollectionByTrackerAtTimestamp( const Guid& tracker, const DateTime& timestamp, std::vector<std::shared_ptr<TrackBaseObject>>& result ) = 0;
        virtual void GetTrackBaseCollectionByTrackerFromTimestamp( const Guid& tracker, const DateTime& timestamp, std::vector<std::shared_ptr<TrackBaseObject>>& result ) = 0;
        virtual void GetTrackBaseCollectionByTrackerUntilTimestamp( const Guid& tracker, const DateTime& timestamp, std::vector<std::shared_ptr<TrackBaseObject>>& result ) = 0;
        virtual void GetTrackBaseCollectionByTrackerOverTimestamp( Guid tracker, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<TrackBaseObject>>& result ) = 0;
        virtual void GetTrackBaseCollectionByTrackNumber( Int64 trackNumber, std::vector<std::shared_ptr<TrackBaseObject>>& result ) = 0;
        virtual void GetTrackBaseCollectionFromTrackNumber( Int64 trackNumber, std::vector<std::shared_ptr<TrackBaseObject>>& result ) = 0;
        virtual void GetTrackBaseCollectionUntilTrackNumber( Int64 trackNumber, std::vector<std::shared_ptr<TrackBaseObject>>& result ) = 0;
        virtual void GetTrackBaseCollectionOverTrackNumber( Int64 fromTrackNumber, Int64 untilTrackNumber, std::vector<std::shared_ptr<TrackBaseObject>>& result ) = 0;
        virtual void GetTrackBaseCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TrackBaseObject>>& result ) = 0;
        virtual void GetTrackBaseCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TrackBaseObject>>& result ) = 0;
        virtual void GetTrackBaseCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TrackBaseObject>>& result ) = 0;
        virtual void GetTrackBaseCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TrackBaseObject>>& result ) = 0;
        virtual void GetTrackBaseCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<TrackBaseObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Track queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<TrackObject> GetTrackById( const Guid& id ) = 0;
        virtual void GetTrackCollection( std::vector<std::shared_ptr<TrackObject>>& result ) = 0;
        virtual void GetTrackCollectionByTracker( const Guid& tracker, std::vector<std::shared_ptr<TrackObject>>& result ) = 0;
        virtual void GetTrackCollectionByTrackerAndTrackNumber( const Guid& tracker, Int64 trackNumber, std::vector<std::shared_ptr<TrackObject>>& result ) = 0;
        virtual void GetTrackCollectionByTrackerFromTrackNumber( const Guid& tracker, Int64 trackNumber, std::vector<std::shared_ptr<TrackObject>>& result ) = 0;
        virtual void GetTrackCollectionByTrackerUntilTrackNumber( const Guid& tracker, Int64 trackNumber, std::vector<std::shared_ptr<TrackObject>>& result ) = 0;
        virtual void GetTrackCollectionByTrackerOverTrackNumber( Guid tracker, Int64 fromTrackNumber, Int64 untilTrackNumber, std::vector<std::shared_ptr<TrackObject>>& result ) = 0;
        virtual std::shared_ptr<TrackObject> GetTrackByTrackerTrackNumberAndTimestamp( const Guid& tracker, Int64 trackNumber, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<TrackObject> GetTrackByTrackerTrackNumberAtTimestamp( const Guid& tracker, Int64 trackNumber, const DateTime& timestamp ) = 0;
        virtual void GetTrackByTrackerTrackNumberFromTimestamp( const Guid& tracker, Int64 trackNumber, const DateTime& timestamp, std::vector<std::shared_ptr<TrackObject>>& result ) = 0;
        virtual void GetTrackByTrackerTrackNumberUntilTimestamp( const Guid& tracker, Int64 trackNumber, const DateTime& timestamp, std::vector<std::shared_ptr<TrackObject>>& result ) = 0;
        virtual void GetTrackByTrackerTrackNumberOverTimestamp( Guid tracker, Int64 trackNumber, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<TrackObject>>& result ) = 0;
        virtual void GetTrackCollectionByTrackerAndTimestamp( const Guid& tracker, const DateTime& timestamp, std::vector<std::shared_ptr<TrackObject>>& result ) = 0;
        virtual void GetTrackCollectionByTrackerAtTimestamp( const Guid& tracker, const DateTime& timestamp, std::vector<std::shared_ptr<TrackObject>>& result ) = 0;
        virtual void GetTrackCollectionByTrackerFromTimestamp( const Guid& tracker, const DateTime& timestamp, std::vector<std::shared_ptr<TrackObject>>& result ) = 0;
        virtual void GetTrackCollectionByTrackerUntilTimestamp( const Guid& tracker, const DateTime& timestamp, std::vector<std::shared_ptr<TrackObject>>& result ) = 0;
        virtual void GetTrackCollectionByTrackerOverTimestamp( Guid tracker, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<TrackObject>>& result ) = 0;
        virtual void GetTrackCollectionByTrackNumber( Int64 trackNumber, std::vector<std::shared_ptr<TrackObject>>& result ) = 0;
        virtual void GetTrackCollectionFromTrackNumber( Int64 trackNumber, std::vector<std::shared_ptr<TrackObject>>& result ) = 0;
        virtual void GetTrackCollectionUntilTrackNumber( Int64 trackNumber, std::vector<std::shared_ptr<TrackObject>>& result ) = 0;
        virtual void GetTrackCollectionOverTrackNumber( Int64 fromTrackNumber, Int64 untilTrackNumber, std::vector<std::shared_ptr<TrackObject>>& result ) = 0;
        virtual void GetTrackCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TrackObject>>& result ) = 0;
        virtual void GetTrackCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TrackObject>>& result ) = 0;
        virtual void GetTrackCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TrackObject>>& result ) = 0;
        virtual void GetTrackCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TrackObject>>& result ) = 0;
        virtual void GetTrackCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<TrackObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Track3D queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<Track3DObject> GetTrack3DById( const Guid& id ) = 0;
        virtual void GetTrack3DCollection( std::vector<std::shared_ptr<Track3DObject>>& result ) = 0;
        virtual void GetTrack3DCollectionByTracker( const Guid& tracker, std::vector<std::shared_ptr<Track3DObject>>& result ) = 0;
        virtual void GetTrack3DCollectionByTrackerAndTrackNumber( const Guid& tracker, Int64 trackNumber, std::vector<std::shared_ptr<Track3DObject>>& result ) = 0;
        virtual void GetTrack3DCollectionByTrackerFromTrackNumber( const Guid& tracker, Int64 trackNumber, std::vector<std::shared_ptr<Track3DObject>>& result ) = 0;
        virtual void GetTrack3DCollectionByTrackerUntilTrackNumber( const Guid& tracker, Int64 trackNumber, std::vector<std::shared_ptr<Track3DObject>>& result ) = 0;
        virtual void GetTrack3DCollectionByTrackerOverTrackNumber( Guid tracker, Int64 fromTrackNumber, Int64 untilTrackNumber, std::vector<std::shared_ptr<Track3DObject>>& result ) = 0;
        virtual std::shared_ptr<Track3DObject> GetTrack3DByTrackerTrackNumberAndTimestamp( const Guid& tracker, Int64 trackNumber, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<Track3DObject> GetTrack3DByTrackerTrackNumberAtTimestamp( const Guid& tracker, Int64 trackNumber, const DateTime& timestamp ) = 0;
        virtual void GetTrack3DByTrackerTrackNumberFromTimestamp( const Guid& tracker, Int64 trackNumber, const DateTime& timestamp, std::vector<std::shared_ptr<Track3DObject>>& result ) = 0;
        virtual void GetTrack3DByTrackerTrackNumberUntilTimestamp( const Guid& tracker, Int64 trackNumber, const DateTime& timestamp, std::vector<std::shared_ptr<Track3DObject>>& result ) = 0;
        virtual void GetTrack3DByTrackerTrackNumberOverTimestamp( Guid tracker, Int64 trackNumber, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<Track3DObject>>& result ) = 0;
        virtual void GetTrack3DCollectionByTrackerAndTimestamp( const Guid& tracker, const DateTime& timestamp, std::vector<std::shared_ptr<Track3DObject>>& result ) = 0;
        virtual void GetTrack3DCollectionByTrackerAtTimestamp( const Guid& tracker, const DateTime& timestamp, std::vector<std::shared_ptr<Track3DObject>>& result ) = 0;
        virtual void GetTrack3DCollectionByTrackerFromTimestamp( const Guid& tracker, const DateTime& timestamp, std::vector<std::shared_ptr<Track3DObject>>& result ) = 0;
        virtual void GetTrack3DCollectionByTrackerUntilTimestamp( const Guid& tracker, const DateTime& timestamp, std::vector<std::shared_ptr<Track3DObject>>& result ) = 0;
        virtual void GetTrack3DCollectionByTrackerOverTimestamp( Guid tracker, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<Track3DObject>>& result ) = 0;
        virtual void GetTrack3DCollectionByTrackNumber( Int64 trackNumber, std::vector<std::shared_ptr<Track3DObject>>& result ) = 0;
        virtual void GetTrack3DCollectionFromTrackNumber( Int64 trackNumber, std::vector<std::shared_ptr<Track3DObject>>& result ) = 0;
        virtual void GetTrack3DCollectionUntilTrackNumber( Int64 trackNumber, std::vector<std::shared_ptr<Track3DObject>>& result ) = 0;
        virtual void GetTrack3DCollectionOverTrackNumber( Int64 fromTrackNumber, Int64 untilTrackNumber, std::vector<std::shared_ptr<Track3DObject>>& result ) = 0;
        virtual void GetTrack3DCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<Track3DObject>>& result ) = 0;
        virtual void GetTrack3DCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<Track3DObject>>& result ) = 0;
        virtual void GetTrack3DCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<Track3DObject>>& result ) = 0;
        virtual void GetTrack3DCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<Track3DObject>>& result ) = 0;
        virtual void GetTrack3DCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<Track3DObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // TrackerFilterParameters queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<TrackerFilterParametersObject> GetTrackerFilterParametersById( const Guid& id ) = 0;
        virtual void GetTrackerFilterParametersCollection( std::vector<std::shared_ptr<TrackerFilterParametersObject>>& result ) = 0;
        virtual void GetTrackerFilterParametersCollectionByTracker( const Guid& tracker, std::vector<std::shared_ptr<TrackerFilterParametersObject>>& result ) = 0;
        virtual std::shared_ptr<TrackerFilterParametersObject> GetTrackerFilterParametersByTrackerAndName( const Guid& tracker, const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // TrackerFilterParametersConfiguration queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<TrackerFilterParametersConfigurationObject> GetTrackerFilterParametersConfigurationById( const Guid& id ) = 0;
        virtual void GetTrackerFilterParametersConfigurationCollection( std::vector<std::shared_ptr<TrackerFilterParametersConfigurationObject>>& result ) = 0;
        virtual void GetTrackerFilterParametersConfigurationCollectionByParameters( const Guid& parameters, std::vector<std::shared_ptr<TrackerFilterParametersConfigurationObject>>& result ) = 0;
        virtual std::shared_ptr<TrackerFilterParametersConfigurationObject> GetTrackerFilterParametersConfigurationByParametersAndTimestamp( const Guid& parameters, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<TrackerFilterParametersConfigurationObject> GetTrackerFilterParametersConfigurationByParametersAtTimestamp( const Guid& parameters, const DateTime& timestamp ) = 0;
        virtual void GetTrackerFilterParametersConfigurationByParametersFromTimestamp( const Guid& parameters, const DateTime& timestamp, std::vector<std::shared_ptr<TrackerFilterParametersConfigurationObject>>& result ) = 0;
        virtual void GetTrackerFilterParametersConfigurationByParametersUntilTimestamp( const Guid& parameters, const DateTime& timestamp, std::vector<std::shared_ptr<TrackerFilterParametersConfigurationObject>>& result ) = 0;
        virtual void GetTrackerFilterParametersConfigurationByParametersOverTimestamp( Guid parameters, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<TrackerFilterParametersConfigurationObject>>& result ) = 0;
        virtual void GetTrackerFilterParametersConfigurationCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TrackerFilterParametersConfigurationObject>>& result ) = 0;
        virtual void GetTrackerFilterParametersConfigurationCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TrackerFilterParametersConfigurationObject>>& result ) = 0;
        virtual void GetTrackerFilterParametersConfigurationCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TrackerFilterParametersConfigurationObject>>& result ) = 0;
        virtual void GetTrackerFilterParametersConfigurationCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TrackerFilterParametersConfigurationObject>>& result ) = 0;
        virtual void GetTrackerFilterParametersConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<TrackerFilterParametersConfigurationObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // TrackInfo queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<TrackInfoObject> GetTrackInfoById( const Guid& id ) = 0;
        virtual void GetTrackInfoCollection( std::vector<std::shared_ptr<TrackInfoObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // TrackingServiceOptions queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<TrackingServiceOptionsObject> GetTrackingServiceOptionsById( const Guid& id ) = 0;
        virtual void GetTrackingServiceOptionsCollection( std::vector<std::shared_ptr<TrackingServiceOptionsObject>>& result ) = 0;
        virtual std::shared_ptr<TrackingServiceOptionsObject> GetTrackingServiceOptionsByTimestamp( const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<TrackingServiceOptionsObject> GetTrackingServiceOptionsAtTimestamp( const DateTime& timestamp ) = 0;
        virtual void GetTrackingServiceOptionsFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TrackingServiceOptionsObject>>& result ) = 0;
        virtual void GetTrackingServiceOptionsUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TrackingServiceOptionsObject>>& result ) = 0;
        virtual void GetTrackingServiceOptionsOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<TrackingServiceOptionsObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // TrackLink queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<TrackLinkObject> GetTrackLinkById( const Guid& id ) = 0;
        virtual void GetTrackLinkCollection( std::vector<std::shared_ptr<TrackLinkObject>>& result ) = 0;
        virtual void GetTrackLinkCollectionByPrimary( const Guid& primary, std::vector<std::shared_ptr<TrackLinkObject>>& result ) = 0;
        virtual void GetTrackLinkCollectionByPrimaryAndStart( const Guid& primary, const DateTime& start, std::vector<std::shared_ptr<TrackLinkObject>>& result ) = 0;
        virtual void GetTrackLinkCollectionByPrimaryAtStart( const Guid& primary, const DateTime& start, std::vector<std::shared_ptr<TrackLinkObject>>& result ) = 0;
        virtual void GetTrackLinkCollectionByPrimaryFromStart( const Guid& primary, const DateTime& start, std::vector<std::shared_ptr<TrackLinkObject>>& result ) = 0;
        virtual void GetTrackLinkCollectionByPrimaryUntilStart( const Guid& primary, const DateTime& start, std::vector<std::shared_ptr<TrackLinkObject>>& result ) = 0;
        virtual void GetTrackLinkCollectionByPrimaryOverStart( Guid primary, DateTime fromStart, DateTime untilStart, std::vector<std::shared_ptr<TrackLinkObject>>& result ) = 0;
        virtual void GetTrackLinkCollectionBySecondary( const Guid& secondary, std::vector<std::shared_ptr<TrackLinkObject>>& result ) = 0;
        virtual void GetTrackLinkCollectionBySecondaryAndStart( const Guid& secondary, const DateTime& start, std::vector<std::shared_ptr<TrackLinkObject>>& result ) = 0;
        virtual void GetTrackLinkCollectionBySecondaryAtStart( const Guid& secondary, const DateTime& start, std::vector<std::shared_ptr<TrackLinkObject>>& result ) = 0;
        virtual void GetTrackLinkCollectionBySecondaryFromStart( const Guid& secondary, const DateTime& start, std::vector<std::shared_ptr<TrackLinkObject>>& result ) = 0;
        virtual void GetTrackLinkCollectionBySecondaryUntilStart( const Guid& secondary, const DateTime& start, std::vector<std::shared_ptr<TrackLinkObject>>& result ) = 0;
        virtual void GetTrackLinkCollectionBySecondaryOverStart( Guid secondary, DateTime fromStart, DateTime untilStart, std::vector<std::shared_ptr<TrackLinkObject>>& result ) = 0;
        virtual void GetTrackLinkCollectionByStart( const DateTime& start, std::vector<std::shared_ptr<TrackLinkObject>>& result ) = 0;
        virtual void GetTrackLinkCollectionAtStart( const DateTime& start, std::vector<std::shared_ptr<TrackLinkObject>>& result ) = 0;
        virtual void GetTrackLinkCollectionFromStart( const DateTime& start, std::vector<std::shared_ptr<TrackLinkObject>>& result ) = 0;
        virtual void GetTrackLinkCollectionUntilStart( const DateTime& start, std::vector<std::shared_ptr<TrackLinkObject>>& result ) = 0;
        virtual void GetTrackLinkCollectionOverStart( DateTime fromStart, DateTime untilStart, std::vector<std::shared_ptr<TrackLinkObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // TrackValue queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<TrackValueObject> GetTrackValueById( const Guid& id ) = 0;
        virtual void GetTrackValueCollection( std::vector<std::shared_ptr<TrackValueObject>>& result ) = 0;
        virtual void GetTrackValueCollectionByTrack( const Guid& track, std::vector<std::shared_ptr<TrackValueObject>>& result ) = 0;
        virtual std::shared_ptr<TrackValueObject> GetTrackValueByTrackAndTimestamp( const Guid& track, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<TrackValueObject> GetTrackValueByTrackAtTimestamp( const Guid& track, const DateTime& timestamp ) = 0;
        virtual void GetTrackValueByTrackFromTimestamp( const Guid& track, const DateTime& timestamp, std::vector<std::shared_ptr<TrackValueObject>>& result ) = 0;
        virtual void GetTrackValueByTrackUntilTimestamp( const Guid& track, const DateTime& timestamp, std::vector<std::shared_ptr<TrackValueObject>>& result ) = 0;
        virtual void GetTrackValueByTrackOverTimestamp( Guid track, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<TrackValueObject>>& result ) = 0;
        virtual void GetTrackValueCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TrackValueObject>>& result ) = 0;
        virtual void GetTrackValueCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TrackValueObject>>& result ) = 0;
        virtual void GetTrackValueCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TrackValueObject>>& result ) = 0;
        virtual void GetTrackValueCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TrackValueObject>>& result ) = 0;
        virtual void GetTrackValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<TrackValueObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // TrackValue3D queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<TrackValue3DObject> GetTrackValue3DById( const Guid& id ) = 0;
        virtual void GetTrackValue3DCollection( std::vector<std::shared_ptr<TrackValue3DObject>>& result ) = 0;
        virtual void GetTrackValue3DCollectionByTrack( const Guid& track, std::vector<std::shared_ptr<TrackValue3DObject>>& result ) = 0;
        virtual std::shared_ptr<TrackValue3DObject> GetTrackValue3DByTrackAndTimestamp( const Guid& track, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<TrackValue3DObject> GetTrackValue3DByTrackAtTimestamp( const Guid& track, const DateTime& timestamp ) = 0;
        virtual void GetTrackValue3DByTrackFromTimestamp( const Guid& track, const DateTime& timestamp, std::vector<std::shared_ptr<TrackValue3DObject>>& result ) = 0;
        virtual void GetTrackValue3DByTrackUntilTimestamp( const Guid& track, const DateTime& timestamp, std::vector<std::shared_ptr<TrackValue3DObject>>& result ) = 0;
        virtual void GetTrackValue3DByTrackOverTimestamp( Guid track, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<TrackValue3DObject>>& result ) = 0;
        virtual void GetTrackValue3DCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TrackValue3DObject>>& result ) = 0;
        virtual void GetTrackValue3DCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TrackValue3DObject>>& result ) = 0;
        virtual void GetTrackValue3DCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TrackValue3DObject>>& result ) = 0;
        virtual void GetTrackValue3DCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<TrackValue3DObject>>& result ) = 0;
        virtual void GetTrackValue3DCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<TrackValue3DObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // UInt16TimeseriesValue queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<UInt16TimeseriesValueObject> GetUInt16TimeseriesValueById( const Guid& id ) = 0;
        virtual void GetUInt16TimeseriesValueCollection( std::vector<std::shared_ptr<UInt16TimeseriesValueObject>>& result ) = 0;
        virtual void GetUInt16TimeseriesValueCollectionByTimeseries( const Guid& timeseries, std::vector<std::shared_ptr<UInt16TimeseriesValueObject>>& result ) = 0;
        virtual std::shared_ptr<UInt16TimeseriesValueObject> GetUInt16TimeseriesValueByTimeseriesAndTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<UInt16TimeseriesValueObject> GetUInt16TimeseriesValueByTimeseriesAtTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual void GetUInt16TimeseriesValueByTimeseriesFromTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<UInt16TimeseriesValueObject>>& result ) = 0;
        virtual void GetUInt16TimeseriesValueByTimeseriesUntilTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<UInt16TimeseriesValueObject>>& result ) = 0;
        virtual void GetUInt16TimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<UInt16TimeseriesValueObject>>& result ) = 0;
        virtual void GetUInt16TimeseriesValueCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<UInt16TimeseriesValueObject>>& result ) = 0;
        virtual void GetUInt16TimeseriesValueCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<UInt16TimeseriesValueObject>>& result ) = 0;
        virtual void GetUInt16TimeseriesValueCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<UInt16TimeseriesValueObject>>& result ) = 0;
        virtual void GetUInt16TimeseriesValueCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<UInt16TimeseriesValueObject>>& result ) = 0;
        virtual void GetUInt16TimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<UInt16TimeseriesValueObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // UInt32TimeseriesValue queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<UInt32TimeseriesValueObject> GetUInt32TimeseriesValueById( const Guid& id ) = 0;
        virtual void GetUInt32TimeseriesValueCollection( std::vector<std::shared_ptr<UInt32TimeseriesValueObject>>& result ) = 0;
        virtual void GetUInt32TimeseriesValueCollectionByTimeseries( const Guid& timeseries, std::vector<std::shared_ptr<UInt32TimeseriesValueObject>>& result ) = 0;
        virtual std::shared_ptr<UInt32TimeseriesValueObject> GetUInt32TimeseriesValueByTimeseriesAndTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<UInt32TimeseriesValueObject> GetUInt32TimeseriesValueByTimeseriesAtTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual void GetUInt32TimeseriesValueByTimeseriesFromTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<UInt32TimeseriesValueObject>>& result ) = 0;
        virtual void GetUInt32TimeseriesValueByTimeseriesUntilTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<UInt32TimeseriesValueObject>>& result ) = 0;
        virtual void GetUInt32TimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<UInt32TimeseriesValueObject>>& result ) = 0;
        virtual void GetUInt32TimeseriesValueCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<UInt32TimeseriesValueObject>>& result ) = 0;
        virtual void GetUInt32TimeseriesValueCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<UInt32TimeseriesValueObject>>& result ) = 0;
        virtual void GetUInt32TimeseriesValueCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<UInt32TimeseriesValueObject>>& result ) = 0;
        virtual void GetUInt32TimeseriesValueCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<UInt32TimeseriesValueObject>>& result ) = 0;
        virtual void GetUInt32TimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<UInt32TimeseriesValueObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // UInt64TimeseriesValue queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<UInt64TimeseriesValueObject> GetUInt64TimeseriesValueById( const Guid& id ) = 0;
        virtual void GetUInt64TimeseriesValueCollection( std::vector<std::shared_ptr<UInt64TimeseriesValueObject>>& result ) = 0;
        virtual void GetUInt64TimeseriesValueCollectionByTimeseries( const Guid& timeseries, std::vector<std::shared_ptr<UInt64TimeseriesValueObject>>& result ) = 0;
        virtual std::shared_ptr<UInt64TimeseriesValueObject> GetUInt64TimeseriesValueByTimeseriesAndTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<UInt64TimeseriesValueObject> GetUInt64TimeseriesValueByTimeseriesAtTimestamp( const Guid& timeseries, const DateTime& timestamp ) = 0;
        virtual void GetUInt64TimeseriesValueByTimeseriesFromTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<UInt64TimeseriesValueObject>>& result ) = 0;
        virtual void GetUInt64TimeseriesValueByTimeseriesUntilTimestamp( const Guid& timeseries, const DateTime& timestamp, std::vector<std::shared_ptr<UInt64TimeseriesValueObject>>& result ) = 0;
        virtual void GetUInt64TimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<UInt64TimeseriesValueObject>>& result ) = 0;
        virtual void GetUInt64TimeseriesValueCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<UInt64TimeseriesValueObject>>& result ) = 0;
        virtual void GetUInt64TimeseriesValueCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<UInt64TimeseriesValueObject>>& result ) = 0;
        virtual void GetUInt64TimeseriesValueCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<UInt64TimeseriesValueObject>>& result ) = 0;
        virtual void GetUInt64TimeseriesValueCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<UInt64TimeseriesValueObject>>& result ) = 0;
        virtual void GetUInt64TimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<UInt64TimeseriesValueObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // VehicleType queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<VehicleTypeObject> GetVehicleTypeById( const Guid& id ) = 0;
        virtual void GetVehicleTypeCollection( std::vector<std::shared_ptr<VehicleTypeObject>>& result ) = 0;
        virtual std::shared_ptr<VehicleTypeObject> GetVehicleTypeByName( const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // VesselType queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<VesselTypeObject> GetVesselTypeById( const Guid& id ) = 0;
        virtual void GetVesselTypeCollection( std::vector<std::shared_ptr<VesselTypeObject>>& result ) = 0;
        virtual std::shared_ptr<VesselTypeObject> GetVesselTypeByName( const FixedDBWideString<127>& name ) = 0;
        virtual std::shared_ptr<VesselTypeObject> GetVesselTypeByCode( Int32 code ) = 0;
        virtual void GetVesselTypeFromCode( Int32 code, std::vector<std::shared_ptr<VesselTypeObject>>& result ) = 0;
        virtual void GetVesselTypeUntilCode( Int32 code, std::vector<std::shared_ptr<VesselTypeObject>>& result ) = 0;
        virtual void GetVesselTypeOverCode( Int32 fromCode, Int32 untilCode, std::vector<std::shared_ptr<VesselTypeObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // View queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ViewObject> GetViewById( const Guid& id ) = 0;
        virtual void GetViewCollection( std::vector<std::shared_ptr<ViewObject>>& result ) = 0;
        virtual std::shared_ptr<ViewObject> GetViewByName( const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // ViewCameraLink queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ViewCameraLinkObject> GetViewCameraLinkById( const Guid& id ) = 0;
        virtual void GetViewCameraLinkCollection( std::vector<std::shared_ptr<ViewCameraLinkObject>>& result ) = 0;
        virtual void GetViewCameraLinkCollectionByView( const Guid& view, std::vector<std::shared_ptr<ViewCameraLinkObject>>& result ) = 0;
        virtual std::shared_ptr<ViewCameraLinkObject> GetViewCameraLinkByViewAndStart( const Guid& view, const DateTime& start ) = 0;
        virtual std::shared_ptr<ViewCameraLinkObject> GetViewCameraLinkByViewAtStart( const Guid& view, const DateTime& start ) = 0;
        virtual void GetViewCameraLinkByViewFromStart( const Guid& view, const DateTime& start, std::vector<std::shared_ptr<ViewCameraLinkObject>>& result ) = 0;
        virtual void GetViewCameraLinkByViewUntilStart( const Guid& view, const DateTime& start, std::vector<std::shared_ptr<ViewCameraLinkObject>>& result ) = 0;
        virtual void GetViewCameraLinkByViewOverStart( Guid view, DateTime fromStart, DateTime untilStart, std::vector<std::shared_ptr<ViewCameraLinkObject>>& result ) = 0;
        virtual void GetViewCameraLinkCollectionByCamera( const Guid& camera, std::vector<std::shared_ptr<ViewCameraLinkObject>>& result ) = 0;
        virtual std::shared_ptr<ViewCameraLinkObject> GetViewCameraLinkByCameraAndStart( const Guid& camera, const DateTime& start ) = 0;
        virtual std::shared_ptr<ViewCameraLinkObject> GetViewCameraLinkByCameraAtStart( const Guid& camera, const DateTime& start ) = 0;
        virtual void GetViewCameraLinkByCameraFromStart( const Guid& camera, const DateTime& start, std::vector<std::shared_ptr<ViewCameraLinkObject>>& result ) = 0;
        virtual void GetViewCameraLinkByCameraUntilStart( const Guid& camera, const DateTime& start, std::vector<std::shared_ptr<ViewCameraLinkObject>>& result ) = 0;
        virtual void GetViewCameraLinkByCameraOverStart( Guid camera, DateTime fromStart, DateTime untilStart, std::vector<std::shared_ptr<ViewCameraLinkObject>>& result ) = 0;
        virtual void GetViewCameraLinkCollectionByStart( const DateTime& start, std::vector<std::shared_ptr<ViewCameraLinkObject>>& result ) = 0;
        virtual void GetViewCameraLinkCollectionAtStart( const DateTime& start, std::vector<std::shared_ptr<ViewCameraLinkObject>>& result ) = 0;
        virtual void GetViewCameraLinkCollectionFromStart( const DateTime& start, std::vector<std::shared_ptr<ViewCameraLinkObject>>& result ) = 0;
        virtual void GetViewCameraLinkCollectionUntilStart( const DateTime& start, std::vector<std::shared_ptr<ViewCameraLinkObject>>& result ) = 0;
        virtual void GetViewCameraLinkCollectionOverStart( DateTime fromStart, DateTime untilStart, std::vector<std::shared_ptr<ViewCameraLinkObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // ViewTrackerLink queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ViewTrackerLinkObject> GetViewTrackerLinkById( const Guid& id ) = 0;
        virtual void GetViewTrackerLinkCollection( std::vector<std::shared_ptr<ViewTrackerLinkObject>>& result ) = 0;
        virtual void GetViewTrackerLinkCollectionByView( const Guid& view, std::vector<std::shared_ptr<ViewTrackerLinkObject>>& result ) = 0;
        virtual std::shared_ptr<ViewTrackerLinkObject> GetViewTrackerLinkByViewAndStart( const Guid& view, const DateTime& start ) = 0;
        virtual std::shared_ptr<ViewTrackerLinkObject> GetViewTrackerLinkByViewAtStart( const Guid& view, const DateTime& start ) = 0;
        virtual void GetViewTrackerLinkByViewFromStart( const Guid& view, const DateTime& start, std::vector<std::shared_ptr<ViewTrackerLinkObject>>& result ) = 0;
        virtual void GetViewTrackerLinkByViewUntilStart( const Guid& view, const DateTime& start, std::vector<std::shared_ptr<ViewTrackerLinkObject>>& result ) = 0;
        virtual void GetViewTrackerLinkByViewOverStart( Guid view, DateTime fromStart, DateTime untilStart, std::vector<std::shared_ptr<ViewTrackerLinkObject>>& result ) = 0;
        virtual void GetViewTrackerLinkCollectionByTracker( const Guid& tracker, std::vector<std::shared_ptr<ViewTrackerLinkObject>>& result ) = 0;
        virtual std::shared_ptr<ViewTrackerLinkObject> GetViewTrackerLinkByTrackerAndStart( const Guid& tracker, const DateTime& start ) = 0;
        virtual std::shared_ptr<ViewTrackerLinkObject> GetViewTrackerLinkByTrackerAtStart( const Guid& tracker, const DateTime& start ) = 0;
        virtual void GetViewTrackerLinkByTrackerFromStart( const Guid& tracker, const DateTime& start, std::vector<std::shared_ptr<ViewTrackerLinkObject>>& result ) = 0;
        virtual void GetViewTrackerLinkByTrackerUntilStart( const Guid& tracker, const DateTime& start, std::vector<std::shared_ptr<ViewTrackerLinkObject>>& result ) = 0;
        virtual void GetViewTrackerLinkByTrackerOverStart( Guid tracker, DateTime fromStart, DateTime untilStart, std::vector<std::shared_ptr<ViewTrackerLinkObject>>& result ) = 0;
        virtual void GetViewTrackerLinkCollectionByStart( const DateTime& start, std::vector<std::shared_ptr<ViewTrackerLinkObject>>& result ) = 0;
        virtual void GetViewTrackerLinkCollectionAtStart( const DateTime& start, std::vector<std::shared_ptr<ViewTrackerLinkObject>>& result ) = 0;
        virtual void GetViewTrackerLinkCollectionFromStart( const DateTime& start, std::vector<std::shared_ptr<ViewTrackerLinkObject>>& result ) = 0;
        virtual void GetViewTrackerLinkCollectionUntilStart( const DateTime& start, std::vector<std::shared_ptr<ViewTrackerLinkObject>>& result ) = 0;
        virtual void GetViewTrackerLinkCollectionOverStart( DateTime fromStart, DateTime untilStart, std::vector<std::shared_ptr<ViewTrackerLinkObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // WeatherStationCommand queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<WeatherStationCommandObject> GetWeatherStationCommandById( const Guid& id ) = 0;
        virtual void GetWeatherStationCommandCollection( std::vector<std::shared_ptr<WeatherStationCommandObject>>& result ) = 0;
        virtual void GetWeatherStationCommandCollectionByWeatherStation( const Guid& weatherStation, std::vector<std::shared_ptr<WeatherStationCommandObject>>& result ) = 0;
        virtual void GetWeatherStationCommandCollectionByWeatherStationAndTimestamp( const Guid& weatherStation, const DateTime& timestamp, std::vector<std::shared_ptr<WeatherStationCommandObject>>& result ) = 0;
        virtual void GetWeatherStationCommandCollectionByWeatherStationAtTimestamp( const Guid& weatherStation, const DateTime& timestamp, std::vector<std::shared_ptr<WeatherStationCommandObject>>& result ) = 0;
        virtual void GetWeatherStationCommandCollectionByWeatherStationFromTimestamp( const Guid& weatherStation, const DateTime& timestamp, std::vector<std::shared_ptr<WeatherStationCommandObject>>& result ) = 0;
        virtual void GetWeatherStationCommandCollectionByWeatherStationUntilTimestamp( const Guid& weatherStation, const DateTime& timestamp, std::vector<std::shared_ptr<WeatherStationCommandObject>>& result ) = 0;
        virtual void GetWeatherStationCommandCollectionByWeatherStationOverTimestamp( Guid weatherStation, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<WeatherStationCommandObject>>& result ) = 0;
        virtual void GetWeatherStationCommandCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<WeatherStationCommandObject>>& result ) = 0;
        virtual void GetWeatherStationCommandCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<WeatherStationCommandObject>>& result ) = 0;
        virtual void GetWeatherStationCommandCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<WeatherStationCommandObject>>& result ) = 0;
        virtual void GetWeatherStationCommandCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<WeatherStationCommandObject>>& result ) = 0;
        virtual void GetWeatherStationCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<WeatherStationCommandObject>>& result ) = 0;
        virtual void GetWeatherStationCommandCollectionByReply( const DBGuid& reply, std::vector<std::shared_ptr<WeatherStationCommandObject>>& result ) = 0;
        virtual void GetWeatherStationCommandCollectionByReplyIsNull( std::vector<std::shared_ptr<WeatherStationCommandObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // WeatherStationCommandReply queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<WeatherStationCommandReplyObject> GetWeatherStationCommandReplyById( const Guid& id ) = 0;
        virtual void GetWeatherStationCommandReplyCollection( std::vector<std::shared_ptr<WeatherStationCommandReplyObject>>& result ) = 0;
        virtual void GetWeatherStationCommandReplyCollectionByWeatherStation( const Guid& weatherStation, std::vector<std::shared_ptr<WeatherStationCommandReplyObject>>& result ) = 0;
        virtual void GetWeatherStationCommandReplyCollectionByWeatherStationAndTimestamp( const Guid& weatherStation, const DateTime& timestamp, std::vector<std::shared_ptr<WeatherStationCommandReplyObject>>& result ) = 0;
        virtual void GetWeatherStationCommandReplyCollectionByWeatherStationAtTimestamp( const Guid& weatherStation, const DateTime& timestamp, std::vector<std::shared_ptr<WeatherStationCommandReplyObject>>& result ) = 0;
        virtual void GetWeatherStationCommandReplyCollectionByWeatherStationFromTimestamp( const Guid& weatherStation, const DateTime& timestamp, std::vector<std::shared_ptr<WeatherStationCommandReplyObject>>& result ) = 0;
        virtual void GetWeatherStationCommandReplyCollectionByWeatherStationUntilTimestamp( const Guid& weatherStation, const DateTime& timestamp, std::vector<std::shared_ptr<WeatherStationCommandReplyObject>>& result ) = 0;
        virtual void GetWeatherStationCommandReplyCollectionByWeatherStationOverTimestamp( Guid weatherStation, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<WeatherStationCommandReplyObject>>& result ) = 0;
        virtual void GetWeatherStationCommandReplyCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<WeatherStationCommandReplyObject>>& result ) = 0;
        virtual void GetWeatherStationCommandReplyCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<WeatherStationCommandReplyObject>>& result ) = 0;
        virtual void GetWeatherStationCommandReplyCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<WeatherStationCommandReplyObject>>& result ) = 0;
        virtual void GetWeatherStationCommandReplyCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<WeatherStationCommandReplyObject>>& result ) = 0;
        virtual void GetWeatherStationCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<WeatherStationCommandReplyObject>>& result ) = 0;
        virtual std::shared_ptr<WeatherStationCommandReplyObject> GetWeatherStationCommandReplyByCommand( const DBGuid& command ) = 0;
        virtual void GetWeatherStationCommandReplyCollectionByCommandIsNull( std::vector<std::shared_ptr<WeatherStationCommandReplyObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // WeatherStationConfiguration queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<WeatherStationConfigurationObject> GetWeatherStationConfigurationById( const Guid& id ) = 0;
        virtual void GetWeatherStationConfigurationCollection( std::vector<std::shared_ptr<WeatherStationConfigurationObject>>& result ) = 0;
        virtual void GetWeatherStationConfigurationCollectionByWeatherStation( const Guid& weatherStation, std::vector<std::shared_ptr<WeatherStationConfigurationObject>>& result ) = 0;
        virtual std::shared_ptr<WeatherStationConfigurationObject> GetWeatherStationConfigurationByWeatherStationAndTimestamp( const Guid& weatherStation, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<WeatherStationConfigurationObject> GetWeatherStationConfigurationByWeatherStationAtTimestamp( const Guid& weatherStation, const DateTime& timestamp ) = 0;
        virtual void GetWeatherStationConfigurationByWeatherStationFromTimestamp( const Guid& weatherStation, const DateTime& timestamp, std::vector<std::shared_ptr<WeatherStationConfigurationObject>>& result ) = 0;
        virtual void GetWeatherStationConfigurationByWeatherStationUntilTimestamp( const Guid& weatherStation, const DateTime& timestamp, std::vector<std::shared_ptr<WeatherStationConfigurationObject>>& result ) = 0;
        virtual void GetWeatherStationConfigurationByWeatherStationOverTimestamp( Guid weatherStation, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<WeatherStationConfigurationObject>>& result ) = 0;
        virtual void GetWeatherStationConfigurationCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<WeatherStationConfigurationObject>>& result ) = 0;
        virtual void GetWeatherStationConfigurationCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<WeatherStationConfigurationObject>>& result ) = 0;
        virtual void GetWeatherStationConfigurationCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<WeatherStationConfigurationObject>>& result ) = 0;
        virtual void GetWeatherStationConfigurationCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<WeatherStationConfigurationObject>>& result ) = 0;
        virtual void GetWeatherStationConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<WeatherStationConfigurationObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // Zone queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ZoneObject> GetZoneById( const Guid& id ) = 0;
        virtual void GetZoneCollection( std::vector<std::shared_ptr<ZoneObject>>& result ) = 0;
        virtual std::shared_ptr<ZoneObject> GetZoneByName( const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // CircularZone queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<CircularZoneObject> GetCircularZoneById( const Guid& id ) = 0;
        virtual void GetCircularZoneCollection( std::vector<std::shared_ptr<CircularZoneObject>>& result ) = 0;
        virtual std::shared_ptr<CircularZoneObject> GetCircularZoneByName( const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // PolygonZone queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<PolygonZoneObject> GetPolygonZoneById( const Guid& id ) = 0;
        virtual void GetPolygonZoneCollection( std::vector<std::shared_ptr<PolygonZoneObject>>& result ) = 0;
        virtual std::shared_ptr<PolygonZoneObject> GetPolygonZoneByName( const FixedDBWideString<127>& name ) = 0;
        // ---------------------------------------------------------------------
        // ZoneExceptions queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ZoneExceptionsObject> GetZoneExceptionsById( const Guid& id ) = 0;
        virtual void GetZoneExceptionsCollection( std::vector<std::shared_ptr<ZoneExceptionsObject>>& result ) = 0;
        virtual void GetZoneExceptionsCollectionByZone( const Guid& zone, std::vector<std::shared_ptr<ZoneExceptionsObject>>& result ) = 0;
        virtual std::shared_ptr<ZoneExceptionsObject> GetZoneExceptionsByZoneAndTimestamp( const Guid& zone, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<ZoneExceptionsObject> GetZoneExceptionsByZoneAtTimestamp( const Guid& zone, const DateTime& timestamp ) = 0;
        virtual void GetZoneExceptionsByZoneFromTimestamp( const Guid& zone, const DateTime& timestamp, std::vector<std::shared_ptr<ZoneExceptionsObject>>& result ) = 0;
        virtual void GetZoneExceptionsByZoneUntilTimestamp( const Guid& zone, const DateTime& timestamp, std::vector<std::shared_ptr<ZoneExceptionsObject>>& result ) = 0;
        virtual void GetZoneExceptionsByZoneOverTimestamp( Guid zone, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<ZoneExceptionsObject>>& result ) = 0;
        virtual void GetZoneExceptionsCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<ZoneExceptionsObject>>& result ) = 0;
        virtual void GetZoneExceptionsCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<ZoneExceptionsObject>>& result ) = 0;
        virtual void GetZoneExceptionsCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<ZoneExceptionsObject>>& result ) = 0;
        virtual void GetZoneExceptionsCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<ZoneExceptionsObject>>& result ) = 0;
        virtual void GetZoneExceptionsCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<ZoneExceptionsObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // ZoneExceptionsVesselLink queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ZoneExceptionsVesselLinkObject> GetZoneExceptionsVesselLinkById( const Guid& id ) = 0;
        virtual void GetZoneExceptionsVesselLinkCollection( std::vector<std::shared_ptr<ZoneExceptionsVesselLinkObject>>& result ) = 0;
        virtual void GetZoneExceptionsVesselLinkCollectionByZoneExceptions( const Guid& zoneExceptions, std::vector<std::shared_ptr<ZoneExceptionsVesselLinkObject>>& result ) = 0;
        virtual std::shared_ptr<ZoneExceptionsVesselLinkObject> GetZoneExceptionsVesselLinkByZoneExceptionsAndVessel( const Guid& zoneExceptions, const Guid& vessel ) = 0;
        virtual void GetZoneExceptionsVesselLinkCollectionByVessel( const Guid& vessel, std::vector<std::shared_ptr<ZoneExceptionsVesselLinkObject>>& result ) = 0;
        // ---------------------------------------------------------------------
        // ZoneTrackAlarm queries
        // ---------------------------------------------------------------------
        virtual std::shared_ptr<ZoneTrackAlarmObject> GetZoneTrackAlarmById( const Guid& id ) = 0;
        virtual void GetZoneTrackAlarmCollection( std::vector<std::shared_ptr<ZoneTrackAlarmObject>>& result ) = 0;
        virtual void GetZoneTrackAlarmCollectionByTrack( const Guid& track, std::vector<std::shared_ptr<ZoneTrackAlarmObject>>& result ) = 0;
        virtual std::shared_ptr<ZoneTrackAlarmObject> GetZoneTrackAlarmByTrackAndTimestamp( const Guid& track, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<ZoneTrackAlarmObject> GetZoneTrackAlarmByTrackAtTimestamp( const Guid& track, const DateTime& timestamp ) = 0;
        virtual void GetZoneTrackAlarmByTrackFromTimestamp( const Guid& track, const DateTime& timestamp, std::vector<std::shared_ptr<ZoneTrackAlarmObject>>& result ) = 0;
        virtual void GetZoneTrackAlarmByTrackUntilTimestamp( const Guid& track, const DateTime& timestamp, std::vector<std::shared_ptr<ZoneTrackAlarmObject>>& result ) = 0;
        virtual void GetZoneTrackAlarmByTrackOverTimestamp( Guid track, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<ZoneTrackAlarmObject>>& result ) = 0;
        virtual void GetZoneTrackAlarmCollectionByZone( const Guid& zone, std::vector<std::shared_ptr<ZoneTrackAlarmObject>>& result ) = 0;
        virtual void GetZoneTrackAlarmCollectionByZoneAndTrack( const Guid& zone, const Guid& track, std::vector<std::shared_ptr<ZoneTrackAlarmObject>>& result ) = 0;
        virtual std::shared_ptr<ZoneTrackAlarmObject> GetZoneTrackAlarmByZoneTrackAndTimestamp( const Guid& zone, const Guid& track, const DateTime& timestamp ) = 0;
        virtual std::shared_ptr<ZoneTrackAlarmObject> GetZoneTrackAlarmByZoneTrackAtTimestamp( const Guid& zone, const Guid& track, const DateTime& timestamp ) = 0;
        virtual void GetZoneTrackAlarmByZoneTrackFromTimestamp( const Guid& zone, const Guid& track, const DateTime& timestamp, std::vector<std::shared_ptr<ZoneTrackAlarmObject>>& result ) = 0;
        virtual void GetZoneTrackAlarmByZoneTrackUntilTimestamp( const Guid& zone, const Guid& track, const DateTime& timestamp, std::vector<std::shared_ptr<ZoneTrackAlarmObject>>& result ) = 0;
        virtual void GetZoneTrackAlarmByZoneTrackOverTimestamp( Guid zone, Guid track, DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<ZoneTrackAlarmObject>>& result ) = 0;
        virtual void GetZoneTrackAlarmCollectionByTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<ZoneTrackAlarmObject>>& result ) = 0;
        virtual void GetZoneTrackAlarmCollectionAtTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<ZoneTrackAlarmObject>>& result ) = 0;
        virtual void GetZoneTrackAlarmCollectionFromTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<ZoneTrackAlarmObject>>& result ) = 0;
        virtual void GetZoneTrackAlarmCollectionUntilTimestamp( const DateTime& timestamp, std::vector<std::shared_ptr<ZoneTrackAlarmObject>>& result ) = 0;
        virtual void GetZoneTrackAlarmCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp, std::vector<std::shared_ptr<ZoneTrackAlarmObject>>& result ) = 0;
    };
}
#endif
