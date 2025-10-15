package com.harlinn.barrelman.types;

import java.util.List;
import java.util.ArrayList;
import com.harlinn.common.io.BinaryReader;
import com.harlinn.common.io.BinaryWriter;
import com.harlinn.common.types.AbstractDataObject;
import com.harlinn.common.util.*;

public interface DataContext {
    // ---------------------------------------------------------------------
    // AircraftType queries
    // ---------------------------------------------------------------------
    AircraftTypeObject getAircraftTypeById( Guid id );
    List<AircraftTypeObject> getAircraftTypeCollection( );
    AircraftTypeObject getAircraftTypeByName( String name );
    // ---------------------------------------------------------------------
    // AisDeviceCommand queries
    // ---------------------------------------------------------------------
    AisDeviceCommandObject getAisDeviceCommandById( Guid id );
    List<AisDeviceCommandObject> getAisDeviceCommandCollection( );
    List<AisDeviceCommandObject> getAisDeviceCommandCollectionByAisDevice( Guid aisDevice );
    List<AisDeviceCommandObject> getAisDeviceCommandCollectionByAisDeviceAndTimestamp( Guid aisDevice, DateTime timestamp );
    List<AisDeviceCommandObject> getAisDeviceCommandCollectionByAisDeviceAtTimestamp( Guid aisDevice, DateTime timestamp );
    List<AisDeviceCommandObject> getAisDeviceCommandCollectionByAisDeviceFromTimestamp( Guid aisDevice, DateTime timestamp );
    List<AisDeviceCommandObject> getAisDeviceCommandCollectionByAisDeviceUntilTimestamp( Guid aisDevice, DateTime timestamp );
    List<AisDeviceCommandObject> getAisDeviceCommandCollectionByAisDeviceOverTimestamp( Guid aisDevice, DateTime fromTimestamp, DateTime untilTimestamp );
    List<AisDeviceCommandObject> getAisDeviceCommandCollectionByTimestamp( DateTime timestamp );
    List<AisDeviceCommandObject> getAisDeviceCommandCollectionAtTimestamp( DateTime timestamp );
    List<AisDeviceCommandObject> getAisDeviceCommandCollectionFromTimestamp( DateTime timestamp );
    List<AisDeviceCommandObject> getAisDeviceCommandCollectionUntilTimestamp( DateTime timestamp );
    List<AisDeviceCommandObject> getAisDeviceCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<AisDeviceCommandObject> getAisDeviceCommandCollectionByReply( Guid reply );
    List<AisDeviceCommandObject> qetAisDeviceCommandCollectionByReplyIsNull(  );
    // ---------------------------------------------------------------------
    // AisDeviceCommandReply queries
    // ---------------------------------------------------------------------
    AisDeviceCommandReplyObject getAisDeviceCommandReplyById( Guid id );
    List<AisDeviceCommandReplyObject> getAisDeviceCommandReplyCollection( );
    List<AisDeviceCommandReplyObject> getAisDeviceCommandReplyCollectionByAisDevice( Guid aisDevice );
    List<AisDeviceCommandReplyObject> getAisDeviceCommandReplyCollectionByAisDeviceAndTimestamp( Guid aisDevice, DateTime timestamp );
    List<AisDeviceCommandReplyObject> getAisDeviceCommandReplyCollectionByAisDeviceAtTimestamp( Guid aisDevice, DateTime timestamp );
    List<AisDeviceCommandReplyObject> getAisDeviceCommandReplyCollectionByAisDeviceFromTimestamp( Guid aisDevice, DateTime timestamp );
    List<AisDeviceCommandReplyObject> getAisDeviceCommandReplyCollectionByAisDeviceUntilTimestamp( Guid aisDevice, DateTime timestamp );
    List<AisDeviceCommandReplyObject> getAisDeviceCommandReplyCollectionByAisDeviceOverTimestamp( Guid aisDevice, DateTime fromTimestamp, DateTime untilTimestamp );
    List<AisDeviceCommandReplyObject> getAisDeviceCommandReplyCollectionByTimestamp( DateTime timestamp );
    List<AisDeviceCommandReplyObject> getAisDeviceCommandReplyCollectionAtTimestamp( DateTime timestamp );
    List<AisDeviceCommandReplyObject> getAisDeviceCommandReplyCollectionFromTimestamp( DateTime timestamp );
    List<AisDeviceCommandReplyObject> getAisDeviceCommandReplyCollectionUntilTimestamp( DateTime timestamp );
    List<AisDeviceCommandReplyObject> getAisDeviceCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    AisDeviceCommandReplyObject getAisDeviceCommandReplyByCommand( Guid command );
    List<AisDeviceCommandReplyObject> qetAisDeviceCommandReplyCollectionByCommandIsNull(  );
    // ---------------------------------------------------------------------
    // AisDeviceConfiguration queries
    // ---------------------------------------------------------------------
    AisDeviceConfigurationObject getAisDeviceConfigurationById( Guid id );
    List<AisDeviceConfigurationObject> getAisDeviceConfigurationCollection( );
    List<AisDeviceConfigurationObject> getAisDeviceConfigurationCollectionByAisDevice( Guid aisDevice );
    AisDeviceConfigurationObject getAisDeviceConfigurationByAisDeviceAndTimestamp( Guid aisDevice, DateTime timestamp );
    AisDeviceConfigurationObject getAisDeviceConfigurationByAisDeviceAtTimestamp( Guid aisDevice, DateTime timestamp );
    List<AisDeviceConfigurationObject> getAisDeviceConfigurationByAisDeviceFromTimestamp( Guid aisDevice, DateTime timestamp );
    List<AisDeviceConfigurationObject> getAisDeviceConfigurationByAisDeviceUntilTimestamp( Guid aisDevice, DateTime timestamp );
    List<AisDeviceConfigurationObject> getAisDeviceConfigurationByAisDeviceOverTimestamp( Guid aisDevice, DateTime fromTimestamp, DateTime untilTimestamp );
    List<AisDeviceConfigurationObject> getAisDeviceConfigurationCollectionByTimestamp( DateTime timestamp );
    List<AisDeviceConfigurationObject> getAisDeviceConfigurationCollectionAtTimestamp( DateTime timestamp );
    List<AisDeviceConfigurationObject> getAisDeviceConfigurationCollectionFromTimestamp( DateTime timestamp );
    List<AisDeviceConfigurationObject> getAisDeviceConfigurationCollectionUntilTimestamp( DateTime timestamp );
    List<AisDeviceConfigurationObject> getAisDeviceConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // AisDeviceRawMessage queries
    // ---------------------------------------------------------------------
    AisDeviceRawMessageObject getAisDeviceRawMessageById( Guid id );
    List<AisDeviceRawMessageObject> getAisDeviceRawMessageCollection( );
    List<AisDeviceRawMessageObject> getAisDeviceRawMessageCollectionByAisDevice( Guid aisDevice );
    List<AisDeviceRawMessageObject> getAisDeviceRawMessageCollectionByAisDeviceAndTimestamp( Guid aisDevice, DateTime timestamp );
    List<AisDeviceRawMessageObject> getAisDeviceRawMessageCollectionByAisDeviceAtTimestamp( Guid aisDevice, DateTime timestamp );
    List<AisDeviceRawMessageObject> getAisDeviceRawMessageCollectionByAisDeviceFromTimestamp( Guid aisDevice, DateTime timestamp );
    List<AisDeviceRawMessageObject> getAisDeviceRawMessageCollectionByAisDeviceUntilTimestamp( Guid aisDevice, DateTime timestamp );
    List<AisDeviceRawMessageObject> getAisDeviceRawMessageCollectionByAisDeviceOverTimestamp( Guid aisDevice, DateTime fromTimestamp, DateTime untilTimestamp );
    List<AisDeviceRawMessageObject> getAisDeviceRawMessageCollectionByTimestamp( DateTime timestamp );
    List<AisDeviceRawMessageObject> getAisDeviceRawMessageCollectionAtTimestamp( DateTime timestamp );
    List<AisDeviceRawMessageObject> getAisDeviceRawMessageCollectionFromTimestamp( DateTime timestamp );
    List<AisDeviceRawMessageObject> getAisDeviceRawMessageCollectionUntilTimestamp( DateTime timestamp );
    List<AisDeviceRawMessageObject> getAisDeviceRawMessageCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // AisDeviceRawSentence queries
    // ---------------------------------------------------------------------
    AisDeviceRawSentenceObject getAisDeviceRawSentenceById( Guid id );
    List<AisDeviceRawSentenceObject> getAisDeviceRawSentenceCollection( );
    List<AisDeviceRawSentenceObject> getAisDeviceRawSentenceCollectionByAisDevice( Guid aisDevice );
    List<AisDeviceRawSentenceObject> getAisDeviceRawSentenceCollectionByAisDeviceAndTimestamp( Guid aisDevice, DateTime timestamp );
    List<AisDeviceRawSentenceObject> getAisDeviceRawSentenceCollectionByAisDeviceAtTimestamp( Guid aisDevice, DateTime timestamp );
    List<AisDeviceRawSentenceObject> getAisDeviceRawSentenceCollectionByAisDeviceFromTimestamp( Guid aisDevice, DateTime timestamp );
    List<AisDeviceRawSentenceObject> getAisDeviceRawSentenceCollectionByAisDeviceUntilTimestamp( Guid aisDevice, DateTime timestamp );
    List<AisDeviceRawSentenceObject> getAisDeviceRawSentenceCollectionByAisDeviceOverTimestamp( Guid aisDevice, DateTime fromTimestamp, DateTime untilTimestamp );
    List<AisDeviceRawSentenceObject> getAisDeviceRawSentenceCollectionByTimestamp( DateTime timestamp );
    List<AisDeviceRawSentenceObject> getAisDeviceRawSentenceCollectionAtTimestamp( DateTime timestamp );
    List<AisDeviceRawSentenceObject> getAisDeviceRawSentenceCollectionFromTimestamp( DateTime timestamp );
    List<AisDeviceRawSentenceObject> getAisDeviceRawSentenceCollectionUntilTimestamp( DateTime timestamp );
    List<AisDeviceRawSentenceObject> getAisDeviceRawSentenceCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // AisMessage queries
    // ---------------------------------------------------------------------
    AisMessageObject getAisMessageById( Guid id );
    List<AisMessageObject> getAisMessageCollection( );
    List<AisMessageObject> getAisMessageCollectionByAisDevice( Guid aisDevice );
    AisMessageObject getAisMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    AisMessageObject getAisMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisMessageObject> getAisMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisMessageObject> getAisMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisMessageObject> getAisMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisMessageObject> getAisMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
    List<AisMessageObject> getAisMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
    List<AisMessageObject> getAisMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
    List<AisMessageObject> getAisMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
    List<AisMessageObject> getAisMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisMessageObject> getAisMessageCollectionByMmsi( Guid mmsi );
    List<AisMessageObject> qetAisMessageCollectionByMmsiIsNull(  );
    List<AisMessageObject> getAisMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisMessageObject> qetAisMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
    List<AisMessageObject> getAisMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisMessageObject> getAisMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisMessageObject> getAisMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
    // ---------------------------------------------------------------------
    // AidToNavigationReportMessage queries
    // ---------------------------------------------------------------------
    AidToNavigationReportMessageObject getAidToNavigationReportMessageById( Guid id );
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageCollection( );
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageCollectionByAisDevice( Guid aisDevice );
    AidToNavigationReportMessageObject getAidToNavigationReportMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    AidToNavigationReportMessageObject getAidToNavigationReportMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageCollectionByMmsi( Guid mmsi );
    List<AidToNavigationReportMessageObject> qetAidToNavigationReportMessageCollectionByMmsiIsNull(  );
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AidToNavigationReportMessageObject> qetAidToNavigationReportMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
    // ---------------------------------------------------------------------
    // AisAddressedSafetyRelatedMessage queries
    // ---------------------------------------------------------------------
    AisAddressedSafetyRelatedMessageObject getAisAddressedSafetyRelatedMessageById( Guid id );
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollection( );
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollectionByAisDevice( Guid aisDevice );
    AisAddressedSafetyRelatedMessageObject getAisAddressedSafetyRelatedMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    AisAddressedSafetyRelatedMessageObject getAisAddressedSafetyRelatedMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollectionByMmsi( Guid mmsi );
    List<AisAddressedSafetyRelatedMessageObject> qetAisAddressedSafetyRelatedMessageCollectionByMmsiIsNull(  );
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisAddressedSafetyRelatedMessageObject> qetAisAddressedSafetyRelatedMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollectionByDestinationMmsi( Guid destinationMmsi );
    List<AisAddressedSafetyRelatedMessageObject> qetAisAddressedSafetyRelatedMessageCollectionByDestinationMmsiIsNull(  );
    // ---------------------------------------------------------------------
    // AisBaseStationReportMessage queries
    // ---------------------------------------------------------------------
    AisBaseStationReportMessageObject getAisBaseStationReportMessageById( Guid id );
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageCollection( );
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageCollectionByAisDevice( Guid aisDevice );
    AisBaseStationReportMessageObject getAisBaseStationReportMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    AisBaseStationReportMessageObject getAisBaseStationReportMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageCollectionByMmsi( Guid mmsi );
    List<AisBaseStationReportMessageObject> qetAisBaseStationReportMessageCollectionByMmsiIsNull(  );
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisBaseStationReportMessageObject> qetAisBaseStationReportMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
    // ---------------------------------------------------------------------
    // AisBinaryAcknowledgeMessage queries
    // ---------------------------------------------------------------------
    AisBinaryAcknowledgeMessageObject getAisBinaryAcknowledgeMessageById( Guid id );
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageCollection( );
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageCollectionByAisDevice( Guid aisDevice );
    AisBinaryAcknowledgeMessageObject getAisBinaryAcknowledgeMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    AisBinaryAcknowledgeMessageObject getAisBinaryAcknowledgeMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageCollectionByMmsi( Guid mmsi );
    List<AisBinaryAcknowledgeMessageObject> qetAisBinaryAcknowledgeMessageCollectionByMmsiIsNull(  );
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisBinaryAcknowledgeMessageObject> qetAisBinaryAcknowledgeMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
    // ---------------------------------------------------------------------
    // AisBinaryAddressedMessage queries
    // ---------------------------------------------------------------------
    AisBinaryAddressedMessageObject getAisBinaryAddressedMessageById( Guid id );
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollection( );
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollectionByAisDevice( Guid aisDevice );
    AisBinaryAddressedMessageObject getAisBinaryAddressedMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    AisBinaryAddressedMessageObject getAisBinaryAddressedMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollectionByMmsi( Guid mmsi );
    List<AisBinaryAddressedMessageObject> qetAisBinaryAddressedMessageCollectionByMmsiIsNull(  );
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisBinaryAddressedMessageObject> qetAisBinaryAddressedMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollectionByDestinationMmsi( Guid destinationMmsi );
    List<AisBinaryAddressedMessageObject> qetAisBinaryAddressedMessageCollectionByDestinationMmsiIsNull(  );
    // ---------------------------------------------------------------------
    // AisBinaryBroadcastMessage queries
    // ---------------------------------------------------------------------
    AisBinaryBroadcastMessageObject getAisBinaryBroadcastMessageById( Guid id );
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageCollection( );
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageCollectionByAisDevice( Guid aisDevice );
    AisBinaryBroadcastMessageObject getAisBinaryBroadcastMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    AisBinaryBroadcastMessageObject getAisBinaryBroadcastMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageCollectionByMmsi( Guid mmsi );
    List<AisBinaryBroadcastMessageObject> qetAisBinaryBroadcastMessageCollectionByMmsiIsNull(  );
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisBinaryBroadcastMessageObject> qetAisBinaryBroadcastMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
    // ---------------------------------------------------------------------
    // AisDataLinkManagementMessage queries
    // ---------------------------------------------------------------------
    AisDataLinkManagementMessageObject getAisDataLinkManagementMessageById( Guid id );
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageCollection( );
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageCollectionByAisDevice( Guid aisDevice );
    AisDataLinkManagementMessageObject getAisDataLinkManagementMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    AisDataLinkManagementMessageObject getAisDataLinkManagementMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageCollectionByMmsi( Guid mmsi );
    List<AisDataLinkManagementMessageObject> qetAisDataLinkManagementMessageCollectionByMmsiIsNull(  );
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisDataLinkManagementMessageObject> qetAisDataLinkManagementMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
    // ---------------------------------------------------------------------
    // AisExtendedClassBCsPositionReportMessage queries
    // ---------------------------------------------------------------------
    AisExtendedClassBCsPositionReportMessageObject getAisExtendedClassBCsPositionReportMessageById( Guid id );
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollection( );
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollectionByAisDevice( Guid aisDevice );
    AisExtendedClassBCsPositionReportMessageObject getAisExtendedClassBCsPositionReportMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    AisExtendedClassBCsPositionReportMessageObject getAisExtendedClassBCsPositionReportMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollectionByMmsi( Guid mmsi );
    List<AisExtendedClassBCsPositionReportMessageObject> qetAisExtendedClassBCsPositionReportMessageCollectionByMmsiIsNull(  );
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisExtendedClassBCsPositionReportMessageObject> qetAisExtendedClassBCsPositionReportMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollectionByName( Guid name );
    List<AisExtendedClassBCsPositionReportMessageObject> qetAisExtendedClassBCsPositionReportMessageCollectionByNameIsNull(  );
    // ---------------------------------------------------------------------
    // AisInterrogationMessage queries
    // ---------------------------------------------------------------------
    AisInterrogationMessageObject getAisInterrogationMessageById( Guid id );
    List<AisInterrogationMessageObject> getAisInterrogationMessageCollection( );
    List<AisInterrogationMessageObject> getAisInterrogationMessageCollectionByAisDevice( Guid aisDevice );
    AisInterrogationMessageObject getAisInterrogationMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    AisInterrogationMessageObject getAisInterrogationMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisInterrogationMessageObject> getAisInterrogationMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisInterrogationMessageObject> getAisInterrogationMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisInterrogationMessageObject> getAisInterrogationMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisInterrogationMessageObject> getAisInterrogationMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
    List<AisInterrogationMessageObject> getAisInterrogationMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
    List<AisInterrogationMessageObject> getAisInterrogationMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
    List<AisInterrogationMessageObject> getAisInterrogationMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
    List<AisInterrogationMessageObject> getAisInterrogationMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisInterrogationMessageObject> getAisInterrogationMessageCollectionByMmsi( Guid mmsi );
    List<AisInterrogationMessageObject> qetAisInterrogationMessageCollectionByMmsiIsNull(  );
    List<AisInterrogationMessageObject> getAisInterrogationMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisInterrogationMessageObject> qetAisInterrogationMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
    List<AisInterrogationMessageObject> getAisInterrogationMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisInterrogationMessageObject> getAisInterrogationMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisInterrogationMessageObject> getAisInterrogationMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
    // ---------------------------------------------------------------------
    // AisPositionReportClassAMessageBase queries
    // ---------------------------------------------------------------------
    AisPositionReportClassAMessageBaseObject getAisPositionReportClassAMessageBaseById( Guid id );
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseCollection( );
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseCollectionByAisDevice( Guid aisDevice );
    AisPositionReportClassAMessageBaseObject getAisPositionReportClassAMessageBaseByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    AisPositionReportClassAMessageBaseObject getAisPositionReportClassAMessageBaseByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseCollectionByReceivedTimestamp( DateTime receivedTimestamp );
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseCollectionByMmsi( Guid mmsi );
    List<AisPositionReportClassAMessageBaseObject> qetAisPositionReportClassAMessageBaseCollectionByMmsiIsNull(  );
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisPositionReportClassAMessageBaseObject> qetAisPositionReportClassAMessageBaseCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
    // ---------------------------------------------------------------------
    // AisPositionReportClassAAssignedScheduleMessage queries
    // ---------------------------------------------------------------------
    AisPositionReportClassAAssignedScheduleMessageObject getAisPositionReportClassAAssignedScheduleMessageById( Guid id );
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageCollection( );
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageCollectionByAisDevice( Guid aisDevice );
    AisPositionReportClassAAssignedScheduleMessageObject getAisPositionReportClassAAssignedScheduleMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    AisPositionReportClassAAssignedScheduleMessageObject getAisPositionReportClassAAssignedScheduleMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageCollectionByMmsi( Guid mmsi );
    List<AisPositionReportClassAAssignedScheduleMessageObject> qetAisPositionReportClassAAssignedScheduleMessageCollectionByMmsiIsNull(  );
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisPositionReportClassAAssignedScheduleMessageObject> qetAisPositionReportClassAAssignedScheduleMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
    // ---------------------------------------------------------------------
    // AisPositionReportClassAMessage queries
    // ---------------------------------------------------------------------
    AisPositionReportClassAMessageObject getAisPositionReportClassAMessageById( Guid id );
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageCollection( );
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageCollectionByAisDevice( Guid aisDevice );
    AisPositionReportClassAMessageObject getAisPositionReportClassAMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    AisPositionReportClassAMessageObject getAisPositionReportClassAMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageCollectionByMmsi( Guid mmsi );
    List<AisPositionReportClassAMessageObject> qetAisPositionReportClassAMessageCollectionByMmsiIsNull(  );
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisPositionReportClassAMessageObject> qetAisPositionReportClassAMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
    // ---------------------------------------------------------------------
    // AisPositionReportClassAResponseToInterrogationMessage queries
    // ---------------------------------------------------------------------
    AisPositionReportClassAResponseToInterrogationMessageObject getAisPositionReportClassAResponseToInterrogationMessageById( Guid id );
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageCollection( );
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageCollectionByAisDevice( Guid aisDevice );
    AisPositionReportClassAResponseToInterrogationMessageObject getAisPositionReportClassAResponseToInterrogationMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    AisPositionReportClassAResponseToInterrogationMessageObject getAisPositionReportClassAResponseToInterrogationMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsi( Guid mmsi );
    List<AisPositionReportClassAResponseToInterrogationMessageObject> qetAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsiIsNull(  );
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisPositionReportClassAResponseToInterrogationMessageObject> qetAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
    // ---------------------------------------------------------------------
    // AisPositionReportForLongRangeApplicationsMessage queries
    // ---------------------------------------------------------------------
    AisPositionReportForLongRangeApplicationsMessageObject getAisPositionReportForLongRangeApplicationsMessageById( Guid id );
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageCollection( );
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageCollectionByAisDevice( Guid aisDevice );
    AisPositionReportForLongRangeApplicationsMessageObject getAisPositionReportForLongRangeApplicationsMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    AisPositionReportForLongRangeApplicationsMessageObject getAisPositionReportForLongRangeApplicationsMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageCollectionByMmsi( Guid mmsi );
    List<AisPositionReportForLongRangeApplicationsMessageObject> qetAisPositionReportForLongRangeApplicationsMessageCollectionByMmsiIsNull(  );
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisPositionReportForLongRangeApplicationsMessageObject> qetAisPositionReportForLongRangeApplicationsMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
    // ---------------------------------------------------------------------
    // AisSafetyRelatedAcknowledgmentMessage queries
    // ---------------------------------------------------------------------
    AisSafetyRelatedAcknowledgmentMessageObject getAisSafetyRelatedAcknowledgmentMessageById( Guid id );
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageCollection( );
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageCollectionByAisDevice( Guid aisDevice );
    AisSafetyRelatedAcknowledgmentMessageObject getAisSafetyRelatedAcknowledgmentMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    AisSafetyRelatedAcknowledgmentMessageObject getAisSafetyRelatedAcknowledgmentMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageCollectionByMmsi( Guid mmsi );
    List<AisSafetyRelatedAcknowledgmentMessageObject> qetAisSafetyRelatedAcknowledgmentMessageCollectionByMmsiIsNull(  );
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisSafetyRelatedAcknowledgmentMessageObject> qetAisSafetyRelatedAcknowledgmentMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
    // ---------------------------------------------------------------------
    // AisStandardClassBCsPositionReportMessage queries
    // ---------------------------------------------------------------------
    AisStandardClassBCsPositionReportMessageObject getAisStandardClassBCsPositionReportMessageById( Guid id );
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageCollection( );
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageCollectionByAisDevice( Guid aisDevice );
    AisStandardClassBCsPositionReportMessageObject getAisStandardClassBCsPositionReportMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    AisStandardClassBCsPositionReportMessageObject getAisStandardClassBCsPositionReportMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageCollectionByMmsi( Guid mmsi );
    List<AisStandardClassBCsPositionReportMessageObject> qetAisStandardClassBCsPositionReportMessageCollectionByMmsiIsNull(  );
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisStandardClassBCsPositionReportMessageObject> qetAisStandardClassBCsPositionReportMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
    // ---------------------------------------------------------------------
    // AisStandardSarAircraftPositionReportMessage queries
    // ---------------------------------------------------------------------
    AisStandardSarAircraftPositionReportMessageObject getAisStandardSarAircraftPositionReportMessageById( Guid id );
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageCollection( );
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageCollectionByAisDevice( Guid aisDevice );
    AisStandardSarAircraftPositionReportMessageObject getAisStandardSarAircraftPositionReportMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    AisStandardSarAircraftPositionReportMessageObject getAisStandardSarAircraftPositionReportMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageCollectionByMmsi( Guid mmsi );
    List<AisStandardSarAircraftPositionReportMessageObject> qetAisStandardSarAircraftPositionReportMessageCollectionByMmsiIsNull(  );
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisStandardSarAircraftPositionReportMessageObject> qetAisStandardSarAircraftPositionReportMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
    // ---------------------------------------------------------------------
    // AisStaticAndVoyageRelatedDataMessage queries
    // ---------------------------------------------------------------------
    AisStaticAndVoyageRelatedDataMessageObject getAisStaticAndVoyageRelatedDataMessageById( Guid id );
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollection( );
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionByAisDevice( Guid aisDevice );
    AisStaticAndVoyageRelatedDataMessageObject getAisStaticAndVoyageRelatedDataMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    AisStaticAndVoyageRelatedDataMessageObject getAisStaticAndVoyageRelatedDataMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionByMmsi( Guid mmsi );
    List<AisStaticAndVoyageRelatedDataMessageObject> qetAisStaticAndVoyageRelatedDataMessageCollectionByMmsiIsNull(  );
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisStaticAndVoyageRelatedDataMessageObject> qetAisStaticAndVoyageRelatedDataMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionByImoNumber( Guid imoNumber );
    List<AisStaticAndVoyageRelatedDataMessageObject> qetAisStaticAndVoyageRelatedDataMessageCollectionByImoNumberIsNull(  );
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionByCallsign( Guid callsign );
    List<AisStaticAndVoyageRelatedDataMessageObject> qetAisStaticAndVoyageRelatedDataMessageCollectionByCallsignIsNull(  );
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionByShipName( Guid shipName );
    List<AisStaticAndVoyageRelatedDataMessageObject> qetAisStaticAndVoyageRelatedDataMessageCollectionByShipNameIsNull(  );
    // ---------------------------------------------------------------------
    // AisStaticDataReportMessage queries
    // ---------------------------------------------------------------------
    AisStaticDataReportMessageObject getAisStaticDataReportMessageById( Guid id );
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageCollection( );
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageCollectionByAisDevice( Guid aisDevice );
    AisStaticDataReportMessageObject getAisStaticDataReportMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    AisStaticDataReportMessageObject getAisStaticDataReportMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageCollectionByMmsi( Guid mmsi );
    List<AisStaticDataReportMessageObject> qetAisStaticDataReportMessageCollectionByMmsiIsNull(  );
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisStaticDataReportMessageObject> qetAisStaticDataReportMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
    // ---------------------------------------------------------------------
    // AisStaticDataReportPartAMessage queries
    // ---------------------------------------------------------------------
    AisStaticDataReportPartAMessageObject getAisStaticDataReportPartAMessageById( Guid id );
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollection( );
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollectionByAisDevice( Guid aisDevice );
    AisStaticDataReportPartAMessageObject getAisStaticDataReportPartAMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    AisStaticDataReportPartAMessageObject getAisStaticDataReportPartAMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollectionByMmsi( Guid mmsi );
    List<AisStaticDataReportPartAMessageObject> qetAisStaticDataReportPartAMessageCollectionByMmsiIsNull(  );
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisStaticDataReportPartAMessageObject> qetAisStaticDataReportPartAMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollectionByShipName( Guid shipName );
    List<AisStaticDataReportPartAMessageObject> qetAisStaticDataReportPartAMessageCollectionByShipNameIsNull(  );
    // ---------------------------------------------------------------------
    // AisStaticDataReportPartBMessage queries
    // ---------------------------------------------------------------------
    AisStaticDataReportPartBMessageObject getAisStaticDataReportPartBMessageById( Guid id );
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollection( );
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionByAisDevice( Guid aisDevice );
    AisStaticDataReportPartBMessageObject getAisStaticDataReportPartBMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    AisStaticDataReportPartBMessageObject getAisStaticDataReportPartBMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionByMmsi( Guid mmsi );
    List<AisStaticDataReportPartBMessageObject> qetAisStaticDataReportPartBMessageCollectionByMmsiIsNull(  );
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisStaticDataReportPartBMessageObject> qetAisStaticDataReportPartBMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionByCallsign( Guid callsign );
    List<AisStaticDataReportPartBMessageObject> qetAisStaticDataReportPartBMessageCollectionByCallsignIsNull(  );
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionByMothershipMmsi( Guid mothershipMmsi );
    List<AisStaticDataReportPartBMessageObject> qetAisStaticDataReportPartBMessageCollectionByMothershipMmsiIsNull(  );
    // ---------------------------------------------------------------------
    // AisUtcAndDateInquiryMessage queries
    // ---------------------------------------------------------------------
    AisUtcAndDateInquiryMessageObject getAisUtcAndDateInquiryMessageById( Guid id );
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageCollection( );
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageCollectionByAisDevice( Guid aisDevice );
    AisUtcAndDateInquiryMessageObject getAisUtcAndDateInquiryMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    AisUtcAndDateInquiryMessageObject getAisUtcAndDateInquiryMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageCollectionByMmsi( Guid mmsi );
    List<AisUtcAndDateInquiryMessageObject> qetAisUtcAndDateInquiryMessageCollectionByMmsiIsNull(  );
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisUtcAndDateInquiryMessageObject> qetAisUtcAndDateInquiryMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
    // ---------------------------------------------------------------------
    // AisUtcAndDateResponseMessage queries
    // ---------------------------------------------------------------------
    AisUtcAndDateResponseMessageObject getAisUtcAndDateResponseMessageById( Guid id );
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageCollection( );
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageCollectionByAisDevice( Guid aisDevice );
    AisUtcAndDateResponseMessageObject getAisUtcAndDateResponseMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    AisUtcAndDateResponseMessageObject getAisUtcAndDateResponseMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageCollectionByMmsi( Guid mmsi );
    List<AisUtcAndDateResponseMessageObject> qetAisUtcAndDateResponseMessageCollectionByMmsiIsNull(  );
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisUtcAndDateResponseMessageObject> qetAisUtcAndDateResponseMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber );
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
    // ---------------------------------------------------------------------
    // AlarmStateChange queries
    // ---------------------------------------------------------------------
    AlarmStateChangeObject getAlarmStateChangeById( Guid id );
    List<AlarmStateChangeObject> getAlarmStateChangeCollection( );
    List<AlarmStateChangeObject> getAlarmStateChangeCollectionByAlarm( Guid alarm );
    AlarmStateChangeObject getAlarmStateChangeByAlarmAndTimestamp( Guid alarm, DateTime timestamp );
    AlarmStateChangeObject getAlarmStateChangeByAlarmAtTimestamp( Guid alarm, DateTime timestamp );
    List<AlarmStateChangeObject> getAlarmStateChangeByAlarmFromTimestamp( Guid alarm, DateTime timestamp );
    List<AlarmStateChangeObject> getAlarmStateChangeByAlarmUntilTimestamp( Guid alarm, DateTime timestamp );
    List<AlarmStateChangeObject> getAlarmStateChangeByAlarmOverTimestamp( Guid alarm, DateTime fromTimestamp, DateTime untilTimestamp );
    List<AlarmStateChangeObject> getAlarmStateChangeCollectionByTimestamp( DateTime timestamp );
    List<AlarmStateChangeObject> getAlarmStateChangeCollectionAtTimestamp( DateTime timestamp );
    List<AlarmStateChangeObject> getAlarmStateChangeCollectionFromTimestamp( DateTime timestamp );
    List<AlarmStateChangeObject> getAlarmStateChangeCollectionUntilTimestamp( DateTime timestamp );
    List<AlarmStateChangeObject> getAlarmStateChangeCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // BaseStationType queries
    // ---------------------------------------------------------------------
    BaseStationTypeObject getBaseStationTypeById( Guid id );
    List<BaseStationTypeObject> getBaseStationTypeCollection( );
    BaseStationTypeObject getBaseStationTypeByName( String name );
    // ---------------------------------------------------------------------
    // BinaryTimeseriesValue queries
    // ---------------------------------------------------------------------
    BinaryTimeseriesValueObject getBinaryTimeseriesValueById( Guid id );
    List<BinaryTimeseriesValueObject> getBinaryTimeseriesValueCollection( );
    List<BinaryTimeseriesValueObject> getBinaryTimeseriesValueCollectionByTimeseries( Guid timeseries );
    BinaryTimeseriesValueObject getBinaryTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
    BinaryTimeseriesValueObject getBinaryTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
    List<BinaryTimeseriesValueObject> getBinaryTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
    List<BinaryTimeseriesValueObject> getBinaryTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
    List<BinaryTimeseriesValueObject> getBinaryTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
    List<BinaryTimeseriesValueObject> getBinaryTimeseriesValueCollectionByTimestamp( DateTime timestamp );
    List<BinaryTimeseriesValueObject> getBinaryTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
    List<BinaryTimeseriesValueObject> getBinaryTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
    List<BinaryTimeseriesValueObject> getBinaryTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
    List<BinaryTimeseriesValueObject> getBinaryTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // Bookmark queries
    // ---------------------------------------------------------------------
    BookmarkObject getBookmarkById( Guid id );
    List<BookmarkObject> getBookmarkCollection( );
    List<BookmarkObject> getBookmarkCollectionByView( Guid view );
    // ---------------------------------------------------------------------
    // BooleanTimeseriesValue queries
    // ---------------------------------------------------------------------
    BooleanTimeseriesValueObject getBooleanTimeseriesValueById( Guid id );
    List<BooleanTimeseriesValueObject> getBooleanTimeseriesValueCollection( );
    List<BooleanTimeseriesValueObject> getBooleanTimeseriesValueCollectionByTimeseries( Guid timeseries );
    BooleanTimeseriesValueObject getBooleanTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
    BooleanTimeseriesValueObject getBooleanTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
    List<BooleanTimeseriesValueObject> getBooleanTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
    List<BooleanTimeseriesValueObject> getBooleanTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
    List<BooleanTimeseriesValueObject> getBooleanTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
    List<BooleanTimeseriesValueObject> getBooleanTimeseriesValueCollectionByTimestamp( DateTime timestamp );
    List<BooleanTimeseriesValueObject> getBooleanTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
    List<BooleanTimeseriesValueObject> getBooleanTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
    List<BooleanTimeseriesValueObject> getBooleanTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
    List<BooleanTimeseriesValueObject> getBooleanTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // ByteTimeseriesValue queries
    // ---------------------------------------------------------------------
    ByteTimeseriesValueObject getByteTimeseriesValueById( Guid id );
    List<ByteTimeseriesValueObject> getByteTimeseriesValueCollection( );
    List<ByteTimeseriesValueObject> getByteTimeseriesValueCollectionByTimeseries( Guid timeseries );
    ByteTimeseriesValueObject getByteTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
    ByteTimeseriesValueObject getByteTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
    List<ByteTimeseriesValueObject> getByteTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
    List<ByteTimeseriesValueObject> getByteTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
    List<ByteTimeseriesValueObject> getByteTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
    List<ByteTimeseriesValueObject> getByteTimeseriesValueCollectionByTimestamp( DateTime timestamp );
    List<ByteTimeseriesValueObject> getByteTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
    List<ByteTimeseriesValueObject> getByteTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
    List<ByteTimeseriesValueObject> getByteTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
    List<ByteTimeseriesValueObject> getByteTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // CameraCommand queries
    // ---------------------------------------------------------------------
    CameraCommandObject getCameraCommandById( Guid id );
    List<CameraCommandObject> getCameraCommandCollection( );
    List<CameraCommandObject> getCameraCommandCollectionByCamera( Guid camera );
    List<CameraCommandObject> getCameraCommandCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandObject> getCameraCommandCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandObject> getCameraCommandCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandObject> getCameraCommandCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandObject> getCameraCommandCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandObject> getCameraCommandCollectionByTimestamp( DateTime timestamp );
    List<CameraCommandObject> getCameraCommandCollectionAtTimestamp( DateTime timestamp );
    List<CameraCommandObject> getCameraCommandCollectionFromTimestamp( DateTime timestamp );
    List<CameraCommandObject> getCameraCommandCollectionUntilTimestamp( DateTime timestamp );
    List<CameraCommandObject> getCameraCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandObject> getCameraCommandCollectionByReply( Guid reply );
    List<CameraCommandObject> qetCameraCommandCollectionByReplyIsNull(  );
    // ---------------------------------------------------------------------
    // CameraCommandAbsoluteMove queries
    // ---------------------------------------------------------------------
    CameraCommandAbsoluteMoveObject getCameraCommandAbsoluteMoveById( Guid id );
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollection( );
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollectionByCamera( Guid camera );
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollectionByTimestamp( DateTime timestamp );
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollectionAtTimestamp( DateTime timestamp );
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollectionFromTimestamp( DateTime timestamp );
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollectionUntilTimestamp( DateTime timestamp );
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollectionByReply( Guid reply );
    List<CameraCommandAbsoluteMoveObject> qetCameraCommandAbsoluteMoveCollectionByReplyIsNull(  );
    // ---------------------------------------------------------------------
    // CameraCommandAdjustPanTiltZoom queries
    // ---------------------------------------------------------------------
    CameraCommandAdjustPanTiltZoomObject getCameraCommandAdjustPanTiltZoomById( Guid id );
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollection( );
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollectionByCamera( Guid camera );
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollectionByTimestamp( DateTime timestamp );
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollectionAtTimestamp( DateTime timestamp );
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollectionFromTimestamp( DateTime timestamp );
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollectionUntilTimestamp( DateTime timestamp );
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollectionByReply( Guid reply );
    List<CameraCommandAdjustPanTiltZoomObject> qetCameraCommandAdjustPanTiltZoomCollectionByReplyIsNull(  );
    // ---------------------------------------------------------------------
    // CameraCommandContinuousMove queries
    // ---------------------------------------------------------------------
    CameraCommandContinuousMoveObject getCameraCommandContinuousMoveById( Guid id );
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollection( );
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollectionByCamera( Guid camera );
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollectionByTimestamp( DateTime timestamp );
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollectionAtTimestamp( DateTime timestamp );
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollectionFromTimestamp( DateTime timestamp );
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollectionUntilTimestamp( DateTime timestamp );
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollectionByReply( Guid reply );
    List<CameraCommandContinuousMoveObject> qetCameraCommandContinuousMoveCollectionByReplyIsNull(  );
    // ---------------------------------------------------------------------
    // CameraCommandGeoMove queries
    // ---------------------------------------------------------------------
    CameraCommandGeoMoveObject getCameraCommandGeoMoveById( Guid id );
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollection( );
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollectionByCamera( Guid camera );
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollectionByTimestamp( DateTime timestamp );
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollectionAtTimestamp( DateTime timestamp );
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollectionFromTimestamp( DateTime timestamp );
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollectionUntilTimestamp( DateTime timestamp );
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollectionByReply( Guid reply );
    List<CameraCommandGeoMoveObject> qetCameraCommandGeoMoveCollectionByReplyIsNull(  );
    // ---------------------------------------------------------------------
    // CameraCommandRelativeMove queries
    // ---------------------------------------------------------------------
    CameraCommandRelativeMoveObject getCameraCommandRelativeMoveById( Guid id );
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollection( );
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollectionByCamera( Guid camera );
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollectionByTimestamp( DateTime timestamp );
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollectionAtTimestamp( DateTime timestamp );
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollectionFromTimestamp( DateTime timestamp );
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollectionUntilTimestamp( DateTime timestamp );
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollectionByReply( Guid reply );
    List<CameraCommandRelativeMoveObject> qetCameraCommandRelativeMoveCollectionByReplyIsNull(  );
    // ---------------------------------------------------------------------
    // CameraCommandReleasePTZOwnership queries
    // ---------------------------------------------------------------------
    CameraCommandReleasePTZOwnershipObject getCameraCommandReleasePTZOwnershipById( Guid id );
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollection( );
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollectionByCamera( Guid camera );
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollectionByTimestamp( DateTime timestamp );
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollectionAtTimestamp( DateTime timestamp );
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollectionFromTimestamp( DateTime timestamp );
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollectionUntilTimestamp( DateTime timestamp );
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollectionByReply( Guid reply );
    List<CameraCommandReleasePTZOwnershipObject> qetCameraCommandReleasePTZOwnershipCollectionByReplyIsNull(  );
    // ---------------------------------------------------------------------
    // CameraCommandRequestPTZOwnership queries
    // ---------------------------------------------------------------------
    CameraCommandRequestPTZOwnershipObject getCameraCommandRequestPTZOwnershipById( Guid id );
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollection( );
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollectionByCamera( Guid camera );
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollectionByTimestamp( DateTime timestamp );
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollectionAtTimestamp( DateTime timestamp );
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollectionFromTimestamp( DateTime timestamp );
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollectionUntilTimestamp( DateTime timestamp );
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollectionByReply( Guid reply );
    List<CameraCommandRequestPTZOwnershipObject> qetCameraCommandRequestPTZOwnershipCollectionByReplyIsNull(  );
    // ---------------------------------------------------------------------
    // CameraCommandSetAutoFocus queries
    // ---------------------------------------------------------------------
    CameraCommandSetAutoFocusObject getCameraCommandSetAutoFocusById( Guid id );
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollection( );
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollectionByCamera( Guid camera );
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollectionByTimestamp( DateTime timestamp );
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollectionAtTimestamp( DateTime timestamp );
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollectionFromTimestamp( DateTime timestamp );
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollectionUntilTimestamp( DateTime timestamp );
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollectionByReply( Guid reply );
    List<CameraCommandSetAutoFocusObject> qetCameraCommandSetAutoFocusCollectionByReplyIsNull(  );
    // ---------------------------------------------------------------------
    // CameraCommandSetBlackAndWhite queries
    // ---------------------------------------------------------------------
    CameraCommandSetBlackAndWhiteObject getCameraCommandSetBlackAndWhiteById( Guid id );
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollection( );
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollectionByCamera( Guid camera );
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollectionByTimestamp( DateTime timestamp );
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollectionAtTimestamp( DateTime timestamp );
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollectionFromTimestamp( DateTime timestamp );
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollectionUntilTimestamp( DateTime timestamp );
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollectionByReply( Guid reply );
    List<CameraCommandSetBlackAndWhiteObject> qetCameraCommandSetBlackAndWhiteCollectionByReplyIsNull(  );
    // ---------------------------------------------------------------------
    // CameraCommandSetFollowed queries
    // ---------------------------------------------------------------------
    CameraCommandSetFollowedObject getCameraCommandSetFollowedById( Guid id );
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollection( );
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollectionByCamera( Guid camera );
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollectionByTimestamp( DateTime timestamp );
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollectionAtTimestamp( DateTime timestamp );
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollectionFromTimestamp( DateTime timestamp );
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollectionUntilTimestamp( DateTime timestamp );
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollectionByReply( Guid reply );
    List<CameraCommandSetFollowedObject> qetCameraCommandSetFollowedCollectionByReplyIsNull(  );
    // ---------------------------------------------------------------------
    // CameraCommandSetInfraRedLamp queries
    // ---------------------------------------------------------------------
    CameraCommandSetInfraRedLampObject getCameraCommandSetInfraRedLampById( Guid id );
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollection( );
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollectionByCamera( Guid camera );
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollectionByTimestamp( DateTime timestamp );
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollectionAtTimestamp( DateTime timestamp );
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollectionFromTimestamp( DateTime timestamp );
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollectionUntilTimestamp( DateTime timestamp );
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollectionByReply( Guid reply );
    List<CameraCommandSetInfraRedLampObject> qetCameraCommandSetInfraRedLampCollectionByReplyIsNull(  );
    // ---------------------------------------------------------------------
    // CameraCommandSetWasher queries
    // ---------------------------------------------------------------------
    CameraCommandSetWasherObject getCameraCommandSetWasherById( Guid id );
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollection( );
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollectionByCamera( Guid camera );
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollectionByTimestamp( DateTime timestamp );
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollectionAtTimestamp( DateTime timestamp );
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollectionFromTimestamp( DateTime timestamp );
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollectionUntilTimestamp( DateTime timestamp );
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollectionByReply( Guid reply );
    List<CameraCommandSetWasherObject> qetCameraCommandSetWasherCollectionByReplyIsNull(  );
    // ---------------------------------------------------------------------
    // CameraCommandSetWiper queries
    // ---------------------------------------------------------------------
    CameraCommandSetWiperObject getCameraCommandSetWiperById( Guid id );
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollection( );
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollectionByCamera( Guid camera );
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollectionByTimestamp( DateTime timestamp );
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollectionAtTimestamp( DateTime timestamp );
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollectionFromTimestamp( DateTime timestamp );
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollectionUntilTimestamp( DateTime timestamp );
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollectionByReply( Guid reply );
    List<CameraCommandSetWiperObject> qetCameraCommandSetWiperCollectionByReplyIsNull(  );
    // ---------------------------------------------------------------------
    // CameraCommandStop queries
    // ---------------------------------------------------------------------
    CameraCommandStopObject getCameraCommandStopById( Guid id );
    List<CameraCommandStopObject> getCameraCommandStopCollection( );
    List<CameraCommandStopObject> getCameraCommandStopCollectionByCamera( Guid camera );
    List<CameraCommandStopObject> getCameraCommandStopCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandStopObject> getCameraCommandStopCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandStopObject> getCameraCommandStopCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandStopObject> getCameraCommandStopCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandStopObject> getCameraCommandStopCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandStopObject> getCameraCommandStopCollectionByTimestamp( DateTime timestamp );
    List<CameraCommandStopObject> getCameraCommandStopCollectionAtTimestamp( DateTime timestamp );
    List<CameraCommandStopObject> getCameraCommandStopCollectionFromTimestamp( DateTime timestamp );
    List<CameraCommandStopObject> getCameraCommandStopCollectionUntilTimestamp( DateTime timestamp );
    List<CameraCommandStopObject> getCameraCommandStopCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandStopObject> getCameraCommandStopCollectionByReply( Guid reply );
    List<CameraCommandStopObject> qetCameraCommandStopCollectionByReplyIsNull(  );
    // ---------------------------------------------------------------------
    // CameraCommandReply queries
    // ---------------------------------------------------------------------
    CameraCommandReplyObject getCameraCommandReplyById( Guid id );
    List<CameraCommandReplyObject> getCameraCommandReplyCollection( );
    List<CameraCommandReplyObject> getCameraCommandReplyCollectionByCamera( Guid camera );
    List<CameraCommandReplyObject> getCameraCommandReplyCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandReplyObject> getCameraCommandReplyCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandReplyObject> getCameraCommandReplyCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandReplyObject> getCameraCommandReplyCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
    List<CameraCommandReplyObject> getCameraCommandReplyCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraCommandReplyObject> getCameraCommandReplyCollectionByTimestamp( DateTime timestamp );
    List<CameraCommandReplyObject> getCameraCommandReplyCollectionAtTimestamp( DateTime timestamp );
    List<CameraCommandReplyObject> getCameraCommandReplyCollectionFromTimestamp( DateTime timestamp );
    List<CameraCommandReplyObject> getCameraCommandReplyCollectionUntilTimestamp( DateTime timestamp );
    List<CameraCommandReplyObject> getCameraCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    CameraCommandReplyObject getCameraCommandReplyByCommand( Guid command );
    List<CameraCommandReplyObject> qetCameraCommandReplyCollectionByCommandIsNull(  );
    // ---------------------------------------------------------------------
    // CameraConfiguration queries
    // ---------------------------------------------------------------------
    CameraConfigurationObject getCameraConfigurationById( Guid id );
    List<CameraConfigurationObject> getCameraConfigurationCollection( );
    List<CameraConfigurationObject> getCameraConfigurationCollectionByCamera( Guid camera );
    CameraConfigurationObject getCameraConfigurationByCameraAndTimestamp( Guid camera, DateTime timestamp );
    CameraConfigurationObject getCameraConfigurationByCameraAtTimestamp( Guid camera, DateTime timestamp );
    List<CameraConfigurationObject> getCameraConfigurationByCameraFromTimestamp( Guid camera, DateTime timestamp );
    List<CameraConfigurationObject> getCameraConfigurationByCameraUntilTimestamp( Guid camera, DateTime timestamp );
    List<CameraConfigurationObject> getCameraConfigurationByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraConfigurationObject> getCameraConfigurationCollectionByTimestamp( DateTime timestamp );
    List<CameraConfigurationObject> getCameraConfigurationCollectionAtTimestamp( DateTime timestamp );
    List<CameraConfigurationObject> getCameraConfigurationCollectionFromTimestamp( DateTime timestamp );
    List<CameraConfigurationObject> getCameraConfigurationCollectionUntilTimestamp( DateTime timestamp );
    List<CameraConfigurationObject> getCameraConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // CameraPanCalibration queries
    // ---------------------------------------------------------------------
    CameraPanCalibrationObject getCameraPanCalibrationById( Guid id );
    List<CameraPanCalibrationObject> getCameraPanCalibrationCollection( );
    List<CameraPanCalibrationObject> getCameraPanCalibrationCollectionByCamera( Guid camera );
    CameraPanCalibrationObject getCameraPanCalibrationByCameraAndTimestamp( Guid camera, DateTime timestamp );
    CameraPanCalibrationObject getCameraPanCalibrationByCameraAtTimestamp( Guid camera, DateTime timestamp );
    List<CameraPanCalibrationObject> getCameraPanCalibrationByCameraFromTimestamp( Guid camera, DateTime timestamp );
    List<CameraPanCalibrationObject> getCameraPanCalibrationByCameraUntilTimestamp( Guid camera, DateTime timestamp );
    List<CameraPanCalibrationObject> getCameraPanCalibrationByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraPanCalibrationObject> getCameraPanCalibrationCollectionByTimestamp( DateTime timestamp );
    List<CameraPanCalibrationObject> getCameraPanCalibrationCollectionAtTimestamp( DateTime timestamp );
    List<CameraPanCalibrationObject> getCameraPanCalibrationCollectionFromTimestamp( DateTime timestamp );
    List<CameraPanCalibrationObject> getCameraPanCalibrationCollectionUntilTimestamp( DateTime timestamp );
    List<CameraPanCalibrationObject> getCameraPanCalibrationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // CameraPanCalibrationValue queries
    // ---------------------------------------------------------------------
    CameraPanCalibrationValueObject getCameraPanCalibrationValueById( Guid id );
    List<CameraPanCalibrationValueObject> getCameraPanCalibrationValueCollection( );
    List<CameraPanCalibrationValueObject> getCameraPanCalibrationValueCollectionByPanCalibration( Guid panCalibration );
    CameraPanCalibrationValueObject getCameraPanCalibrationValueByPanCalibrationAndPanAngle( Guid panCalibration, double panAngle );
    List<CameraPanCalibrationValueObject> getCameraPanCalibrationValueByPanCalibrationFromPanAngle( Guid panCalibration, double panAngle );
    List<CameraPanCalibrationValueObject> getCameraPanCalibrationValueByPanCalibrationUntilPanAngle( Guid panCalibration, double panAngle );
    List<CameraPanCalibrationValueObject> getCameraPanCalibrationValueByPanCalibrationOverPanAngle( Guid panCalibration, double fromPanAngle, double untilPanAngle );
    // ---------------------------------------------------------------------
    // CameraStatus queries
    // ---------------------------------------------------------------------
    CameraStatusObject getCameraStatusById( Guid id );
    List<CameraStatusObject> getCameraStatusCollection( );
    List<CameraStatusObject> getCameraStatusCollectionByCamera( Guid camera );
    CameraStatusObject getCameraStatusByCameraAndTimestamp( Guid camera, DateTime timestamp );
    CameraStatusObject getCameraStatusByCameraAtTimestamp( Guid camera, DateTime timestamp );
    List<CameraStatusObject> getCameraStatusByCameraFromTimestamp( Guid camera, DateTime timestamp );
    List<CameraStatusObject> getCameraStatusByCameraUntilTimestamp( Guid camera, DateTime timestamp );
    List<CameraStatusObject> getCameraStatusByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraStatusObject> getCameraStatusCollectionByTrack( Guid track );
    List<CameraStatusObject> qetCameraStatusCollectionByTrackIsNull(  );
    CameraStatusObject getCameraStatusByTrackAndTimestamp( Guid track, DateTime timestamp );
    List<CameraStatusObject> qetCameraStatusCollectionByTrackIsNullAndTimestamp( DateTime timestamp );
    CameraStatusObject getCameraStatusByTrackAtTimestamp( Guid track, DateTime timestamp );
    List<CameraStatusObject> getCameraStatusByTrackFromTimestamp( Guid track, DateTime timestamp );
    List<CameraStatusObject> getCameraStatusByTrackUntilTimestamp( Guid track, DateTime timestamp );
    List<CameraStatusObject> getCameraStatusByTrackOverTimestamp( Guid track, DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraStatusObject> getCameraStatusCollectionByTimestamp( DateTime timestamp );
    List<CameraStatusObject> getCameraStatusCollectionAtTimestamp( DateTime timestamp );
    List<CameraStatusObject> getCameraStatusCollectionFromTimestamp( DateTime timestamp );
    List<CameraStatusObject> getCameraStatusCollectionUntilTimestamp( DateTime timestamp );
    List<CameraStatusObject> getCameraStatusCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // CameraTiltCalibration queries
    // ---------------------------------------------------------------------
    CameraTiltCalibrationObject getCameraTiltCalibrationById( Guid id );
    List<CameraTiltCalibrationObject> getCameraTiltCalibrationCollection( );
    List<CameraTiltCalibrationObject> getCameraTiltCalibrationCollectionByCamera( Guid camera );
    CameraTiltCalibrationObject getCameraTiltCalibrationByCameraAndTimestamp( Guid camera, DateTime timestamp );
    CameraTiltCalibrationObject getCameraTiltCalibrationByCameraAtTimestamp( Guid camera, DateTime timestamp );
    List<CameraTiltCalibrationObject> getCameraTiltCalibrationByCameraFromTimestamp( Guid camera, DateTime timestamp );
    List<CameraTiltCalibrationObject> getCameraTiltCalibrationByCameraUntilTimestamp( Guid camera, DateTime timestamp );
    List<CameraTiltCalibrationObject> getCameraTiltCalibrationByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraTiltCalibrationObject> getCameraTiltCalibrationCollectionByTimestamp( DateTime timestamp );
    List<CameraTiltCalibrationObject> getCameraTiltCalibrationCollectionAtTimestamp( DateTime timestamp );
    List<CameraTiltCalibrationObject> getCameraTiltCalibrationCollectionFromTimestamp( DateTime timestamp );
    List<CameraTiltCalibrationObject> getCameraTiltCalibrationCollectionUntilTimestamp( DateTime timestamp );
    List<CameraTiltCalibrationObject> getCameraTiltCalibrationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // CameraTiltCalibrationValue queries
    // ---------------------------------------------------------------------
    CameraTiltCalibrationValueObject getCameraTiltCalibrationValueById( Guid id );
    List<CameraTiltCalibrationValueObject> getCameraTiltCalibrationValueCollection( );
    List<CameraTiltCalibrationValueObject> getCameraTiltCalibrationValueCollectionByTiltCalibration( Guid tiltCalibration );
    CameraTiltCalibrationValueObject getCameraTiltCalibrationValueByTiltCalibrationAndPanAngle( Guid tiltCalibration, double panAngle );
    List<CameraTiltCalibrationValueObject> getCameraTiltCalibrationValueByTiltCalibrationFromPanAngle( Guid tiltCalibration, double panAngle );
    List<CameraTiltCalibrationValueObject> getCameraTiltCalibrationValueByTiltCalibrationUntilPanAngle( Guid tiltCalibration, double panAngle );
    List<CameraTiltCalibrationValueObject> getCameraTiltCalibrationValueByTiltCalibrationOverPanAngle( Guid tiltCalibration, double fromPanAngle, double untilPanAngle );
    // ---------------------------------------------------------------------
    // CameraZoomCalibration queries
    // ---------------------------------------------------------------------
    CameraZoomCalibrationObject getCameraZoomCalibrationById( Guid id );
    List<CameraZoomCalibrationObject> getCameraZoomCalibrationCollection( );
    List<CameraZoomCalibrationObject> getCameraZoomCalibrationCollectionByCamera( Guid camera );
    CameraZoomCalibrationObject getCameraZoomCalibrationByCameraAndTimestamp( Guid camera, DateTime timestamp );
    CameraZoomCalibrationObject getCameraZoomCalibrationByCameraAtTimestamp( Guid camera, DateTime timestamp );
    List<CameraZoomCalibrationObject> getCameraZoomCalibrationByCameraFromTimestamp( Guid camera, DateTime timestamp );
    List<CameraZoomCalibrationObject> getCameraZoomCalibrationByCameraUntilTimestamp( Guid camera, DateTime timestamp );
    List<CameraZoomCalibrationObject> getCameraZoomCalibrationByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
    List<CameraZoomCalibrationObject> getCameraZoomCalibrationCollectionByTimestamp( DateTime timestamp );
    List<CameraZoomCalibrationObject> getCameraZoomCalibrationCollectionAtTimestamp( DateTime timestamp );
    List<CameraZoomCalibrationObject> getCameraZoomCalibrationCollectionFromTimestamp( DateTime timestamp );
    List<CameraZoomCalibrationObject> getCameraZoomCalibrationCollectionUntilTimestamp( DateTime timestamp );
    List<CameraZoomCalibrationObject> getCameraZoomCalibrationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // CameraZoomCalibrationValue queries
    // ---------------------------------------------------------------------
    CameraZoomCalibrationValueObject getCameraZoomCalibrationValueById( Guid id );
    List<CameraZoomCalibrationValueObject> getCameraZoomCalibrationValueCollection( );
    List<CameraZoomCalibrationValueObject> getCameraZoomCalibrationValueCollectionByZoomCalibration( Guid zoomCalibration );
    CameraZoomCalibrationValueObject getCameraZoomCalibrationValueByZoomCalibrationAndFocalLength( Guid zoomCalibration, double focalLength );
    List<CameraZoomCalibrationValueObject> getCameraZoomCalibrationValueByZoomCalibrationFromFocalLength( Guid zoomCalibration, double focalLength );
    List<CameraZoomCalibrationValueObject> getCameraZoomCalibrationValueByZoomCalibrationUntilFocalLength( Guid zoomCalibration, double focalLength );
    List<CameraZoomCalibrationValueObject> getCameraZoomCalibrationValueByZoomCalibrationOverFocalLength( Guid zoomCalibration, double fromFocalLength, double untilFocalLength );
    // ---------------------------------------------------------------------
    // CatalogElement queries
    // ---------------------------------------------------------------------
    CatalogElementObject getCatalogElementById( Guid id );
    List<CatalogElementObject> getCatalogElementCollection( );
    List<CatalogElementObject> getCatalogElementCollectionByCatalog( Guid catalog );
    List<CatalogElementObject> qetCatalogElementCollectionByCatalogIsNull(  );
    CatalogElementObject getCatalogElementByCatalogAndName( Guid catalog, String name );
    List<CatalogElementObject> qetCatalogElementCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // Catalog queries
    // ---------------------------------------------------------------------
    CatalogObject getCatalogById( Guid id );
    List<CatalogObject> getCatalogCollection( );
    List<CatalogObject> getCatalogCollectionByCatalog( Guid catalog );
    List<CatalogObject> qetCatalogCollectionByCatalogIsNull(  );
    CatalogObject getCatalogByCatalogAndName( Guid catalog, String name );
    List<CatalogObject> qetCatalogCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // Element queries
    // ---------------------------------------------------------------------
    ElementObject getElementById( Guid id );
    List<ElementObject> getElementCollection( );
    List<ElementObject> getElementCollectionByCatalog( Guid catalog );
    List<ElementObject> qetElementCollectionByCatalogIsNull(  );
    ElementObject getElementByCatalogAndName( Guid catalog, String name );
    List<ElementObject> qetElementCollectionByCatalogIsNullAndName( String name );
    List<ElementObject> getElementCollectionByElementType( Guid elementType );
    List<ElementObject> qetElementCollectionByElementTypeIsNull(  );
    // ---------------------------------------------------------------------
    // CollectionInfo queries
    // ---------------------------------------------------------------------
    CollectionInfoObject getCollectionInfoById( Guid id );
    List<CollectionInfoObject> getCollectionInfoCollection( );
    // ---------------------------------------------------------------------
    // Country queries
    // ---------------------------------------------------------------------
    CountryObject getCountryById( Guid id );
    List<CountryObject> getCountryCollection( );
    CountryObject getCountryByName( String name );
    CountryObject getCountryByCode( int code );
    List<CountryObject> getCountryFromCode( int code );
    List<CountryObject> getCountryUntilCode( int code );
    List<CountryObject> getCountryOverCode( int fromCode, int untilCode );
    CountryObject getCountryByAlpha2( String alpha2 );
    CountryObject getCountryByAlpha3( String alpha3 );
    // ---------------------------------------------------------------------
    // CursorInfo queries
    // ---------------------------------------------------------------------
    CursorInfoObject getCursorInfoById( Guid id );
    List<CursorInfoObject> getCursorInfoCollection( );
    // ---------------------------------------------------------------------
    // DateTimeTimeseriesValue queries
    // ---------------------------------------------------------------------
    DateTimeTimeseriesValueObject getDateTimeTimeseriesValueById( Guid id );
    List<DateTimeTimeseriesValueObject> getDateTimeTimeseriesValueCollection( );
    List<DateTimeTimeseriesValueObject> getDateTimeTimeseriesValueCollectionByTimeseries( Guid timeseries );
    DateTimeTimeseriesValueObject getDateTimeTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
    DateTimeTimeseriesValueObject getDateTimeTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
    List<DateTimeTimeseriesValueObject> getDateTimeTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
    List<DateTimeTimeseriesValueObject> getDateTimeTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
    List<DateTimeTimeseriesValueObject> getDateTimeTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
    List<DateTimeTimeseriesValueObject> getDateTimeTimeseriesValueCollectionByTimestamp( DateTime timestamp );
    List<DateTimeTimeseriesValueObject> getDateTimeTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
    List<DateTimeTimeseriesValueObject> getDateTimeTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
    List<DateTimeTimeseriesValueObject> getDateTimeTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
    List<DateTimeTimeseriesValueObject> getDateTimeTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // DeviceHost queries
    // ---------------------------------------------------------------------
    DeviceHostObject getDeviceHostById( Guid id );
    List<DeviceHostObject> getDeviceHostCollection( );
    DeviceHostObject getDeviceHostByName( String name );
    // ---------------------------------------------------------------------
    // DeviceHostConfiguration queries
    // ---------------------------------------------------------------------
    DeviceHostConfigurationObject getDeviceHostConfigurationById( Guid id );
    List<DeviceHostConfigurationObject> getDeviceHostConfigurationCollection( );
    List<DeviceHostConfigurationObject> getDeviceHostConfigurationCollectionByHost( Guid host );
    DeviceHostConfigurationObject getDeviceHostConfigurationByHostAndTimestamp( Guid host, DateTime timestamp );
    DeviceHostConfigurationObject getDeviceHostConfigurationByHostAtTimestamp( Guid host, DateTime timestamp );
    List<DeviceHostConfigurationObject> getDeviceHostConfigurationByHostFromTimestamp( Guid host, DateTime timestamp );
    List<DeviceHostConfigurationObject> getDeviceHostConfigurationByHostUntilTimestamp( Guid host, DateTime timestamp );
    List<DeviceHostConfigurationObject> getDeviceHostConfigurationByHostOverTimestamp( Guid host, DateTime fromTimestamp, DateTime untilTimestamp );
    List<DeviceHostConfigurationObject> getDeviceHostConfigurationCollectionByTimestamp( DateTime timestamp );
    List<DeviceHostConfigurationObject> getDeviceHostConfigurationCollectionAtTimestamp( DateTime timestamp );
    List<DeviceHostConfigurationObject> getDeviceHostConfigurationCollectionFromTimestamp( DateTime timestamp );
    List<DeviceHostConfigurationObject> getDeviceHostConfigurationCollectionUntilTimestamp( DateTime timestamp );
    List<DeviceHostConfigurationObject> getDeviceHostConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // DoubleTimeseriesValue queries
    // ---------------------------------------------------------------------
    DoubleTimeseriesValueObject getDoubleTimeseriesValueById( Guid id );
    List<DoubleTimeseriesValueObject> getDoubleTimeseriesValueCollection( );
    List<DoubleTimeseriesValueObject> getDoubleTimeseriesValueCollectionByTimeseries( Guid timeseries );
    DoubleTimeseriesValueObject getDoubleTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
    DoubleTimeseriesValueObject getDoubleTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
    List<DoubleTimeseriesValueObject> getDoubleTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
    List<DoubleTimeseriesValueObject> getDoubleTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
    List<DoubleTimeseriesValueObject> getDoubleTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
    List<DoubleTimeseriesValueObject> getDoubleTimeseriesValueCollectionByTimestamp( DateTime timestamp );
    List<DoubleTimeseriesValueObject> getDoubleTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
    List<DoubleTimeseriesValueObject> getDoubleTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
    List<DoubleTimeseriesValueObject> getDoubleTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
    List<DoubleTimeseriesValueObject> getDoubleTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // FacilityType queries
    // ---------------------------------------------------------------------
    FacilityTypeObject getFacilityTypeById( Guid id );
    List<FacilityTypeObject> getFacilityTypeCollection( );
    FacilityTypeObject getFacilityTypeByName( String name );
    // ---------------------------------------------------------------------
    // GeoPosition2DTimeseriesValue queries
    // ---------------------------------------------------------------------
    GeoPosition2DTimeseriesValueObject getGeoPosition2DTimeseriesValueById( Guid id );
    List<GeoPosition2DTimeseriesValueObject> getGeoPosition2DTimeseriesValueCollection( );
    List<GeoPosition2DTimeseriesValueObject> getGeoPosition2DTimeseriesValueCollectionByTimeseries( Guid timeseries );
    GeoPosition2DTimeseriesValueObject getGeoPosition2DTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
    GeoPosition2DTimeseriesValueObject getGeoPosition2DTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
    List<GeoPosition2DTimeseriesValueObject> getGeoPosition2DTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
    List<GeoPosition2DTimeseriesValueObject> getGeoPosition2DTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
    List<GeoPosition2DTimeseriesValueObject> getGeoPosition2DTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
    List<GeoPosition2DTimeseriesValueObject> getGeoPosition2DTimeseriesValueCollectionByTimestamp( DateTime timestamp );
    List<GeoPosition2DTimeseriesValueObject> getGeoPosition2DTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
    List<GeoPosition2DTimeseriesValueObject> getGeoPosition2DTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
    List<GeoPosition2DTimeseriesValueObject> getGeoPosition2DTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
    List<GeoPosition2DTimeseriesValueObject> getGeoPosition2DTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // GeoPosition3DTimeseriesValue queries
    // ---------------------------------------------------------------------
    GeoPosition3DTimeseriesValueObject getGeoPosition3DTimeseriesValueById( Guid id );
    List<GeoPosition3DTimeseriesValueObject> getGeoPosition3DTimeseriesValueCollection( );
    List<GeoPosition3DTimeseriesValueObject> getGeoPosition3DTimeseriesValueCollectionByTimeseries( Guid timeseries );
    GeoPosition3DTimeseriesValueObject getGeoPosition3DTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
    GeoPosition3DTimeseriesValueObject getGeoPosition3DTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
    List<GeoPosition3DTimeseriesValueObject> getGeoPosition3DTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
    List<GeoPosition3DTimeseriesValueObject> getGeoPosition3DTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
    List<GeoPosition3DTimeseriesValueObject> getGeoPosition3DTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
    List<GeoPosition3DTimeseriesValueObject> getGeoPosition3DTimeseriesValueCollectionByTimestamp( DateTime timestamp );
    List<GeoPosition3DTimeseriesValueObject> getGeoPosition3DTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
    List<GeoPosition3DTimeseriesValueObject> getGeoPosition3DTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
    List<GeoPosition3DTimeseriesValueObject> getGeoPosition3DTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
    List<GeoPosition3DTimeseriesValueObject> getGeoPosition3DTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // GNSSDeviceCommand queries
    // ---------------------------------------------------------------------
    GNSSDeviceCommandObject getGNSSDeviceCommandById( Guid id );
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollection( );
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollectionByGNSSDevice( Guid gNSSDevice );
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollectionByGNSSDeviceAndTimestamp( Guid gNSSDevice, DateTime timestamp );
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollectionByGNSSDeviceAtTimestamp( Guid gNSSDevice, DateTime timestamp );
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollectionByGNSSDeviceFromTimestamp( Guid gNSSDevice, DateTime timestamp );
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollectionByGNSSDeviceUntilTimestamp( Guid gNSSDevice, DateTime timestamp );
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollectionByGNSSDeviceOverTimestamp( Guid gNSSDevice, DateTime fromTimestamp, DateTime untilTimestamp );
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollectionByTimestamp( DateTime timestamp );
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollectionAtTimestamp( DateTime timestamp );
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollectionFromTimestamp( DateTime timestamp );
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollectionUntilTimestamp( DateTime timestamp );
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollectionByReply( Guid reply );
    List<GNSSDeviceCommandObject> qetGNSSDeviceCommandCollectionByReplyIsNull(  );
    // ---------------------------------------------------------------------
    // GNSSDeviceCommandReply queries
    // ---------------------------------------------------------------------
    GNSSDeviceCommandReplyObject getGNSSDeviceCommandReplyById( Guid id );
    List<GNSSDeviceCommandReplyObject> getGNSSDeviceCommandReplyCollection( );
    List<GNSSDeviceCommandReplyObject> getGNSSDeviceCommandReplyCollectionByGNSSDevice( Guid gNSSDevice );
    List<GNSSDeviceCommandReplyObject> getGNSSDeviceCommandReplyCollectionByGNSSDeviceAndTimestamp( Guid gNSSDevice, DateTime timestamp );
    List<GNSSDeviceCommandReplyObject> getGNSSDeviceCommandReplyCollectionByGNSSDeviceAtTimestamp( Guid gNSSDevice, DateTime timestamp );
    List<GNSSDeviceCommandReplyObject> getGNSSDeviceCommandReplyCollectionByGNSSDeviceFromTimestamp( Guid gNSSDevice, DateTime timestamp );
    List<GNSSDeviceCommandReplyObject> getGNSSDeviceCommandReplyCollectionByGNSSDeviceUntilTimestamp( Guid gNSSDevice, DateTime timestamp );
    List<GNSSDeviceCommandReplyObject> getGNSSDeviceCommandReplyCollectionByGNSSDeviceOverTimestamp( Guid gNSSDevice, DateTime fromTimestamp, DateTime untilTimestamp );
    List<GNSSDeviceCommandReplyObject> getGNSSDeviceCommandReplyCollectionByTimestamp( DateTime timestamp );
    List<GNSSDeviceCommandReplyObject> getGNSSDeviceCommandReplyCollectionAtTimestamp( DateTime timestamp );
    List<GNSSDeviceCommandReplyObject> getGNSSDeviceCommandReplyCollectionFromTimestamp( DateTime timestamp );
    List<GNSSDeviceCommandReplyObject> getGNSSDeviceCommandReplyCollectionUntilTimestamp( DateTime timestamp );
    List<GNSSDeviceCommandReplyObject> getGNSSDeviceCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    GNSSDeviceCommandReplyObject getGNSSDeviceCommandReplyByCommand( Guid command );
    List<GNSSDeviceCommandReplyObject> qetGNSSDeviceCommandReplyCollectionByCommandIsNull(  );
    // ---------------------------------------------------------------------
    // GNSSDeviceConfiguration queries
    // ---------------------------------------------------------------------
    GNSSDeviceConfigurationObject getGNSSDeviceConfigurationById( Guid id );
    List<GNSSDeviceConfigurationObject> getGNSSDeviceConfigurationCollection( );
    List<GNSSDeviceConfigurationObject> getGNSSDeviceConfigurationCollectionByGNSSDevice( Guid gNSSDevice );
    GNSSDeviceConfigurationObject getGNSSDeviceConfigurationByGNSSDeviceAndTimestamp( Guid gNSSDevice, DateTime timestamp );
    GNSSDeviceConfigurationObject getGNSSDeviceConfigurationByGNSSDeviceAtTimestamp( Guid gNSSDevice, DateTime timestamp );
    List<GNSSDeviceConfigurationObject> getGNSSDeviceConfigurationByGNSSDeviceFromTimestamp( Guid gNSSDevice, DateTime timestamp );
    List<GNSSDeviceConfigurationObject> getGNSSDeviceConfigurationByGNSSDeviceUntilTimestamp( Guid gNSSDevice, DateTime timestamp );
    List<GNSSDeviceConfigurationObject> getGNSSDeviceConfigurationByGNSSDeviceOverTimestamp( Guid gNSSDevice, DateTime fromTimestamp, DateTime untilTimestamp );
    List<GNSSDeviceConfigurationObject> getGNSSDeviceConfigurationCollectionByTimestamp( DateTime timestamp );
    List<GNSSDeviceConfigurationObject> getGNSSDeviceConfigurationCollectionAtTimestamp( DateTime timestamp );
    List<GNSSDeviceConfigurationObject> getGNSSDeviceConfigurationCollectionFromTimestamp( DateTime timestamp );
    List<GNSSDeviceConfigurationObject> getGNSSDeviceConfigurationCollectionUntilTimestamp( DateTime timestamp );
    List<GNSSDeviceConfigurationObject> getGNSSDeviceConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // GuidTimeseriesValue queries
    // ---------------------------------------------------------------------
    GuidTimeseriesValueObject getGuidTimeseriesValueById( Guid id );
    List<GuidTimeseriesValueObject> getGuidTimeseriesValueCollection( );
    List<GuidTimeseriesValueObject> getGuidTimeseriesValueCollectionByTimeseries( Guid timeseries );
    GuidTimeseriesValueObject getGuidTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
    GuidTimeseriesValueObject getGuidTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
    List<GuidTimeseriesValueObject> getGuidTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
    List<GuidTimeseriesValueObject> getGuidTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
    List<GuidTimeseriesValueObject> getGuidTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
    List<GuidTimeseriesValueObject> getGuidTimeseriesValueCollectionByTimestamp( DateTime timestamp );
    List<GuidTimeseriesValueObject> getGuidTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
    List<GuidTimeseriesValueObject> getGuidTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
    List<GuidTimeseriesValueObject> getGuidTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
    List<GuidTimeseriesValueObject> getGuidTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // GyroDeviceCommand queries
    // ---------------------------------------------------------------------
    GyroDeviceCommandObject getGyroDeviceCommandById( Guid id );
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollection( );
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollectionByGyroDevice( Guid gyroDevice );
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollectionByGyroDeviceAndTimestamp( Guid gyroDevice, DateTime timestamp );
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollectionByGyroDeviceAtTimestamp( Guid gyroDevice, DateTime timestamp );
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollectionByGyroDeviceFromTimestamp( Guid gyroDevice, DateTime timestamp );
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollectionByGyroDeviceUntilTimestamp( Guid gyroDevice, DateTime timestamp );
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollectionByGyroDeviceOverTimestamp( Guid gyroDevice, DateTime fromTimestamp, DateTime untilTimestamp );
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollectionByTimestamp( DateTime timestamp );
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollectionAtTimestamp( DateTime timestamp );
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollectionFromTimestamp( DateTime timestamp );
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollectionUntilTimestamp( DateTime timestamp );
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollectionByReply( Guid reply );
    List<GyroDeviceCommandObject> qetGyroDeviceCommandCollectionByReplyIsNull(  );
    // ---------------------------------------------------------------------
    // GyroDeviceCommandReply queries
    // ---------------------------------------------------------------------
    GyroDeviceCommandReplyObject getGyroDeviceCommandReplyById( Guid id );
    List<GyroDeviceCommandReplyObject> getGyroDeviceCommandReplyCollection( );
    List<GyroDeviceCommandReplyObject> getGyroDeviceCommandReplyCollectionByGyroDevice( Guid gyroDevice );
    List<GyroDeviceCommandReplyObject> getGyroDeviceCommandReplyCollectionByGyroDeviceAndTimestamp( Guid gyroDevice, DateTime timestamp );
    List<GyroDeviceCommandReplyObject> getGyroDeviceCommandReplyCollectionByGyroDeviceAtTimestamp( Guid gyroDevice, DateTime timestamp );
    List<GyroDeviceCommandReplyObject> getGyroDeviceCommandReplyCollectionByGyroDeviceFromTimestamp( Guid gyroDevice, DateTime timestamp );
    List<GyroDeviceCommandReplyObject> getGyroDeviceCommandReplyCollectionByGyroDeviceUntilTimestamp( Guid gyroDevice, DateTime timestamp );
    List<GyroDeviceCommandReplyObject> getGyroDeviceCommandReplyCollectionByGyroDeviceOverTimestamp( Guid gyroDevice, DateTime fromTimestamp, DateTime untilTimestamp );
    List<GyroDeviceCommandReplyObject> getGyroDeviceCommandReplyCollectionByTimestamp( DateTime timestamp );
    List<GyroDeviceCommandReplyObject> getGyroDeviceCommandReplyCollectionAtTimestamp( DateTime timestamp );
    List<GyroDeviceCommandReplyObject> getGyroDeviceCommandReplyCollectionFromTimestamp( DateTime timestamp );
    List<GyroDeviceCommandReplyObject> getGyroDeviceCommandReplyCollectionUntilTimestamp( DateTime timestamp );
    List<GyroDeviceCommandReplyObject> getGyroDeviceCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    GyroDeviceCommandReplyObject getGyroDeviceCommandReplyByCommand( Guid command );
    List<GyroDeviceCommandReplyObject> qetGyroDeviceCommandReplyCollectionByCommandIsNull(  );
    // ---------------------------------------------------------------------
    // GyroDeviceConfiguration queries
    // ---------------------------------------------------------------------
    GyroDeviceConfigurationObject getGyroDeviceConfigurationById( Guid id );
    List<GyroDeviceConfigurationObject> getGyroDeviceConfigurationCollection( );
    List<GyroDeviceConfigurationObject> getGyroDeviceConfigurationCollectionByGyroDevice( Guid gyroDevice );
    GyroDeviceConfigurationObject getGyroDeviceConfigurationByGyroDeviceAndTimestamp( Guid gyroDevice, DateTime timestamp );
    GyroDeviceConfigurationObject getGyroDeviceConfigurationByGyroDeviceAtTimestamp( Guid gyroDevice, DateTime timestamp );
    List<GyroDeviceConfigurationObject> getGyroDeviceConfigurationByGyroDeviceFromTimestamp( Guid gyroDevice, DateTime timestamp );
    List<GyroDeviceConfigurationObject> getGyroDeviceConfigurationByGyroDeviceUntilTimestamp( Guid gyroDevice, DateTime timestamp );
    List<GyroDeviceConfigurationObject> getGyroDeviceConfigurationByGyroDeviceOverTimestamp( Guid gyroDevice, DateTime fromTimestamp, DateTime untilTimestamp );
    List<GyroDeviceConfigurationObject> getGyroDeviceConfigurationCollectionByTimestamp( DateTime timestamp );
    List<GyroDeviceConfigurationObject> getGyroDeviceConfigurationCollectionAtTimestamp( DateTime timestamp );
    List<GyroDeviceConfigurationObject> getGyroDeviceConfigurationCollectionFromTimestamp( DateTime timestamp );
    List<GyroDeviceConfigurationObject> getGyroDeviceConfigurationCollectionUntilTimestamp( DateTime timestamp );
    List<GyroDeviceConfigurationObject> getGyroDeviceConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // Identity queries
    // ---------------------------------------------------------------------
    IdentityObject getIdentityById( Guid id );
    List<IdentityObject> getIdentityCollection( );
    // ---------------------------------------------------------------------
    // Callsign queries
    // ---------------------------------------------------------------------
    CallsignObject getCallsignById( Guid id );
    List<CallsignObject> getCallsignCollection( );
    CallsignObject getCallsignByIdentifier( String identifier );
    // ---------------------------------------------------------------------
    // InternationalMaritimeOrganizationNumber queries
    // ---------------------------------------------------------------------
    InternationalMaritimeOrganizationNumberObject getInternationalMaritimeOrganizationNumberById( Guid id );
    List<InternationalMaritimeOrganizationNumberObject> getInternationalMaritimeOrganizationNumberCollection( );
    InternationalMaritimeOrganizationNumberObject getInternationalMaritimeOrganizationNumberByIdentifier( long identifier );
    List<InternationalMaritimeOrganizationNumberObject> getInternationalMaritimeOrganizationNumberFromIdentifier( long identifier );
    List<InternationalMaritimeOrganizationNumberObject> getInternationalMaritimeOrganizationNumberUntilIdentifier( long identifier );
    List<InternationalMaritimeOrganizationNumberObject> getInternationalMaritimeOrganizationNumberOverIdentifier( long fromIdentifier, long untilIdentifier );
    // ---------------------------------------------------------------------
    // MaritimeMobileServiceIdentity queries
    // ---------------------------------------------------------------------
    MaritimeMobileServiceIdentityObject getMaritimeMobileServiceIdentityById( Guid id );
    List<MaritimeMobileServiceIdentityObject> getMaritimeMobileServiceIdentityCollection( );
    MaritimeMobileServiceIdentityObject getMaritimeMobileServiceIdentityByIdentifier( long identifier );
    List<MaritimeMobileServiceIdentityObject> getMaritimeMobileServiceIdentityFromIdentifier( long identifier );
    List<MaritimeMobileServiceIdentityObject> getMaritimeMobileServiceIdentityUntilIdentifier( long identifier );
    List<MaritimeMobileServiceIdentityObject> getMaritimeMobileServiceIdentityOverIdentifier( long fromIdentifier, long untilIdentifier );
    // ---------------------------------------------------------------------
    // Name queries
    // ---------------------------------------------------------------------
    NameObject getNameById( Guid id );
    List<NameObject> getNameCollection( );
    NameObject getNameByText( String text );
    // ---------------------------------------------------------------------
    // Int16TimeseriesValue queries
    // ---------------------------------------------------------------------
    Int16TimeseriesValueObject getInt16TimeseriesValueById( Guid id );
    List<Int16TimeseriesValueObject> getInt16TimeseriesValueCollection( );
    List<Int16TimeseriesValueObject> getInt16TimeseriesValueCollectionByTimeseries( Guid timeseries );
    Int16TimeseriesValueObject getInt16TimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
    Int16TimeseriesValueObject getInt16TimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
    List<Int16TimeseriesValueObject> getInt16TimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
    List<Int16TimeseriesValueObject> getInt16TimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
    List<Int16TimeseriesValueObject> getInt16TimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
    List<Int16TimeseriesValueObject> getInt16TimeseriesValueCollectionByTimestamp( DateTime timestamp );
    List<Int16TimeseriesValueObject> getInt16TimeseriesValueCollectionAtTimestamp( DateTime timestamp );
    List<Int16TimeseriesValueObject> getInt16TimeseriesValueCollectionFromTimestamp( DateTime timestamp );
    List<Int16TimeseriesValueObject> getInt16TimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
    List<Int16TimeseriesValueObject> getInt16TimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // Int32TimeseriesValue queries
    // ---------------------------------------------------------------------
    Int32TimeseriesValueObject getInt32TimeseriesValueById( Guid id );
    List<Int32TimeseriesValueObject> getInt32TimeseriesValueCollection( );
    List<Int32TimeseriesValueObject> getInt32TimeseriesValueCollectionByTimeseries( Guid timeseries );
    Int32TimeseriesValueObject getInt32TimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
    Int32TimeseriesValueObject getInt32TimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
    List<Int32TimeseriesValueObject> getInt32TimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
    List<Int32TimeseriesValueObject> getInt32TimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
    List<Int32TimeseriesValueObject> getInt32TimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
    List<Int32TimeseriesValueObject> getInt32TimeseriesValueCollectionByTimestamp( DateTime timestamp );
    List<Int32TimeseriesValueObject> getInt32TimeseriesValueCollectionAtTimestamp( DateTime timestamp );
    List<Int32TimeseriesValueObject> getInt32TimeseriesValueCollectionFromTimestamp( DateTime timestamp );
    List<Int32TimeseriesValueObject> getInt32TimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
    List<Int32TimeseriesValueObject> getInt32TimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // Int64TimeseriesValue queries
    // ---------------------------------------------------------------------
    Int64TimeseriesValueObject getInt64TimeseriesValueById( Guid id );
    List<Int64TimeseriesValueObject> getInt64TimeseriesValueCollection( );
    List<Int64TimeseriesValueObject> getInt64TimeseriesValueCollectionByTimeseries( Guid timeseries );
    Int64TimeseriesValueObject getInt64TimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
    Int64TimeseriesValueObject getInt64TimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
    List<Int64TimeseriesValueObject> getInt64TimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
    List<Int64TimeseriesValueObject> getInt64TimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
    List<Int64TimeseriesValueObject> getInt64TimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
    List<Int64TimeseriesValueObject> getInt64TimeseriesValueCollectionByTimestamp( DateTime timestamp );
    List<Int64TimeseriesValueObject> getInt64TimeseriesValueCollectionAtTimestamp( DateTime timestamp );
    List<Int64TimeseriesValueObject> getInt64TimeseriesValueCollectionFromTimestamp( DateTime timestamp );
    List<Int64TimeseriesValueObject> getInt64TimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
    List<Int64TimeseriesValueObject> getInt64TimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // Item queries
    // ---------------------------------------------------------------------
    ItemObject getItemById( Guid id );
    List<ItemObject> getItemCollection( );
    // ---------------------------------------------------------------------
    // BaseStation queries
    // ---------------------------------------------------------------------
    BaseStationObject getBaseStationById( Guid id );
    List<BaseStationObject> getBaseStationCollection( );
    BaseStationObject getBaseStationByName( String name );
    List<BaseStationObject> getBaseStationCollectionByType( Guid type );
    List<BaseStationObject> qetBaseStationCollectionByTypeIsNull(  );
    // ---------------------------------------------------------------------
    // Device queries
    // ---------------------------------------------------------------------
    DeviceObject getDeviceById( Guid id );
    List<DeviceObject> getDeviceCollection( );
    List<DeviceObject> getDeviceCollectionByHost( Guid host );
    DeviceObject getDeviceByName( String name );
    // ---------------------------------------------------------------------
    // CameraDevice queries
    // ---------------------------------------------------------------------
    CameraDeviceObject getCameraDeviceById( Guid id );
    List<CameraDeviceObject> getCameraDeviceCollection( );
    List<CameraDeviceObject> getCameraDeviceCollectionByHost( Guid host );
    CameraDeviceObject getCameraDeviceByName( String name );
    // ---------------------------------------------------------------------
    // GNSSDevice queries
    // ---------------------------------------------------------------------
    GNSSDeviceObject getGNSSDeviceById( Guid id );
    List<GNSSDeviceObject> getGNSSDeviceCollection( );
    List<GNSSDeviceObject> getGNSSDeviceCollectionByHost( Guid host );
    GNSSDeviceObject getGNSSDeviceByName( String name );
    // ---------------------------------------------------------------------
    // GyroDevice queries
    // ---------------------------------------------------------------------
    GyroDeviceObject getGyroDeviceById( Guid id );
    List<GyroDeviceObject> getGyroDeviceCollection( );
    List<GyroDeviceObject> getGyroDeviceCollectionByHost( Guid host );
    GyroDeviceObject getGyroDeviceByName( String name );
    List<GyroDeviceObject> getGyroDeviceCollectionByGNSSDevice( Guid gNSSDevice );
    List<GyroDeviceObject> qetGyroDeviceCollectionByGNSSDeviceIsNull(  );
    // ---------------------------------------------------------------------
    // LineInputDevice queries
    // ---------------------------------------------------------------------
    LineInputDeviceObject getLineInputDeviceById( Guid id );
    List<LineInputDeviceObject> getLineInputDeviceCollection( );
    List<LineInputDeviceObject> getLineInputDeviceCollectionByHost( Guid host );
    LineInputDeviceObject getLineInputDeviceByName( String name );
    // ---------------------------------------------------------------------
    // OilSpillDetectorDevice queries
    // ---------------------------------------------------------------------
    OilSpillDetectorDeviceObject getOilSpillDetectorDeviceById( Guid id );
    List<OilSpillDetectorDeviceObject> getOilSpillDetectorDeviceCollection( );
    List<OilSpillDetectorDeviceObject> getOilSpillDetectorDeviceCollectionByHost( Guid host );
    OilSpillDetectorDeviceObject getOilSpillDetectorDeviceByName( String name );
    // ---------------------------------------------------------------------
    // RadioDevice queries
    // ---------------------------------------------------------------------
    RadioDeviceObject getRadioDeviceById( Guid id );
    List<RadioDeviceObject> getRadioDeviceCollection( );
    List<RadioDeviceObject> getRadioDeviceCollectionByHost( Guid host );
    RadioDeviceObject getRadioDeviceByName( String name );
    // ---------------------------------------------------------------------
    // RadomeDevice queries
    // ---------------------------------------------------------------------
    RadomeDeviceObject getRadomeDeviceById( Guid id );
    List<RadomeDeviceObject> getRadomeDeviceCollection( );
    List<RadomeDeviceObject> getRadomeDeviceCollectionByHost( Guid host );
    RadomeDeviceObject getRadomeDeviceByName( String name );
    List<RadomeDeviceObject> getRadomeDeviceCollectionByRadar( Guid radar );
    List<RadomeDeviceObject> qetRadomeDeviceCollectionByRadarIsNull(  );
    // ---------------------------------------------------------------------
    // TrackerDevice queries
    // ---------------------------------------------------------------------
    TrackerDeviceObject getTrackerDeviceById( Guid id );
    List<TrackerDeviceObject> getTrackerDeviceCollection( );
    List<TrackerDeviceObject> getTrackerDeviceCollectionByHost( Guid host );
    TrackerDeviceObject getTrackerDeviceByName( String name );
    // ---------------------------------------------------------------------
    // AisDevice queries
    // ---------------------------------------------------------------------
    AisDeviceObject getAisDeviceById( Guid id );
    List<AisDeviceObject> getAisDeviceCollection( );
    List<AisDeviceObject> getAisDeviceCollectionByHost( Guid host );
    AisDeviceObject getAisDeviceByName( String name );
    // ---------------------------------------------------------------------
    // RadarDevice queries
    // ---------------------------------------------------------------------
    RadarDeviceObject getRadarDeviceById( Guid id );
    List<RadarDeviceObject> getRadarDeviceCollection( );
    List<RadarDeviceObject> getRadarDeviceCollectionByHost( Guid host );
    RadarDeviceObject getRadarDeviceByName( String name );
    List<RadarDeviceObject> getRadarDeviceCollectionByRadome( Guid radome );
    List<RadarDeviceObject> qetRadarDeviceCollectionByRadomeIsNull(  );
    List<RadarDeviceObject> getRadarDeviceCollectionByGNSSDevice( Guid gNSSDevice );
    List<RadarDeviceObject> qetRadarDeviceCollectionByGNSSDeviceIsNull(  );
    // ---------------------------------------------------------------------
    // WeatherStationDevice queries
    // ---------------------------------------------------------------------
    WeatherStationDeviceObject getWeatherStationDeviceById( Guid id );
    List<WeatherStationDeviceObject> getWeatherStationDeviceCollection( );
    List<WeatherStationDeviceObject> getWeatherStationDeviceCollectionByHost( Guid host );
    WeatherStationDeviceObject getWeatherStationDeviceByName( String name );
    List<WeatherStationDeviceObject> getWeatherStationDeviceCollectionByGyro( Guid gyro );
    List<WeatherStationDeviceObject> qetWeatherStationDeviceCollectionByGyroIsNull(  );
    // ---------------------------------------------------------------------
    // Facility queries
    // ---------------------------------------------------------------------
    FacilityObject getFacilityById( Guid id );
    List<FacilityObject> getFacilityCollection( );
    FacilityObject getFacilityByName( String name );
    List<FacilityObject> getFacilityCollectionByType( Guid type );
    List<FacilityObject> qetFacilityCollectionByTypeIsNull(  );
    // ---------------------------------------------------------------------
    // TrackableItem queries
    // ---------------------------------------------------------------------
    TrackableItemObject getTrackableItemById( Guid id );
    List<TrackableItemObject> getTrackableItemCollection( );
    // ---------------------------------------------------------------------
    // Aircraft queries
    // ---------------------------------------------------------------------
    AircraftObject getAircraftById( Guid id );
    List<AircraftObject> getAircraftCollection( );
    List<AircraftObject> getAircraftCollectionByName( String name );
    List<AircraftObject> getAircraftCollectionByType( Guid type );
    List<AircraftObject> qetAircraftCollectionByTypeIsNull(  );
    // ---------------------------------------------------------------------
    // AisAidToNavigation queries
    // ---------------------------------------------------------------------
    AisAidToNavigationObject getAisAidToNavigationById( Guid id );
    List<AisAidToNavigationObject> getAisAidToNavigationCollection( );
    AisAidToNavigationObject getAisAidToNavigationByName( String name );
    List<AisAidToNavigationObject> getAisAidToNavigationCollectionByMMSI( Guid mMSI );
    List<AisAidToNavigationObject> qetAisAidToNavigationCollectionByMMSIIsNull(  );
    // ---------------------------------------------------------------------
    // Vehicle queries
    // ---------------------------------------------------------------------
    VehicleObject getVehicleById( Guid id );
    List<VehicleObject> getVehicleCollection( );
    VehicleObject getVehicleByName( String name );
    List<VehicleObject> getVehicleCollectionByType( Guid type );
    List<VehicleObject> qetVehicleCollectionByTypeIsNull(  );
    // ---------------------------------------------------------------------
    // Vessel queries
    // ---------------------------------------------------------------------
    VesselObject getVesselById( Guid id );
    List<VesselObject> getVesselCollection( );
    List<VesselObject> getVesselCollectionByName( String name );
    List<VesselObject> getVesselCollectionByType( Guid type );
    List<VesselObject> qetVesselCollectionByTypeIsNull(  );
    // ---------------------------------------------------------------------
    // ItemIdentityLink queries
    // ---------------------------------------------------------------------
    ItemIdentityLinkObject getItemIdentityLinkById( Guid id );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollection( );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByItem( Guid item );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByItemAndStart( Guid item, DateTime start );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByItemAtStart( Guid item, DateTime start );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByItemFromStart( Guid item, DateTime start );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByItemUntilStart( Guid item, DateTime start );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByItemOverStart( Guid item, DateTime fromStart, DateTime untilStart );
    List<ItemIdentityLinkObject> qetItemIdentityLinkCollectionByItem(  );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByItemAndEnd( Guid item, DateTime end );
    List<ItemIdentityLinkObject> qetItemIdentityLinkCollectionByItemAndEndIsNull( Guid item );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByItemAtEnd( Guid item, DateTime end );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByItemFromEnd( Guid item, DateTime end );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByItemUntilEnd( Guid item, DateTime end );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByItemOverEnd( Guid item, DateTime fromEnd, DateTime untilEnd );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByIdentity( Guid identity );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByIdentityAndStart( Guid identity, DateTime start );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByIdentityAtStart( Guid identity, DateTime start );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByIdentityFromStart( Guid identity, DateTime start );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByIdentityUntilStart( Guid identity, DateTime start );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByIdentityOverStart( Guid identity, DateTime fromStart, DateTime untilStart );
    List<ItemIdentityLinkObject> qetItemIdentityLinkCollectionByIdentity(  );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByIdentityAndEnd( Guid identity, DateTime end );
    List<ItemIdentityLinkObject> qetItemIdentityLinkCollectionByIdentityAndEndIsNull( Guid identity );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByIdentityAtEnd( Guid identity, DateTime end );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByIdentityFromEnd( Guid identity, DateTime end );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByIdentityUntilEnd( Guid identity, DateTime end );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByIdentityOverEnd( Guid identity, DateTime fromEnd, DateTime untilEnd );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByStart( DateTime start );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionAtStart( DateTime start );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionFromStart( DateTime start );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionUntilStart( DateTime start );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionOverStart( DateTime fromStart, DateTime untilStart );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByEnd( DateTime end );
    List<ItemIdentityLinkObject> qetItemIdentityLinkCollectionByEndIsNull(  );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionAtEnd( DateTime end );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionFromEnd( DateTime end );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionUntilEnd( DateTime end );
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionOverEnd( DateTime fromEnd, DateTime untilEnd );
    // ---------------------------------------------------------------------
    // ItemParentChildLink queries
    // ---------------------------------------------------------------------
    ItemParentChildLinkObject getItemParentChildLinkById( Guid id );
    List<ItemParentChildLinkObject> getItemParentChildLinkCollection( );
    List<ItemParentChildLinkObject> getItemParentChildLinkCollectionByParent( Guid parent );
    ItemParentChildLinkObject getItemParentChildLinkByParentAndTimestamp( Guid parent, DateTime timestamp );
    ItemParentChildLinkObject getItemParentChildLinkByParentAtTimestamp( Guid parent, DateTime timestamp );
    List<ItemParentChildLinkObject> getItemParentChildLinkByParentFromTimestamp( Guid parent, DateTime timestamp );
    List<ItemParentChildLinkObject> getItemParentChildLinkByParentUntilTimestamp( Guid parent, DateTime timestamp );
    List<ItemParentChildLinkObject> getItemParentChildLinkByParentOverTimestamp( Guid parent, DateTime fromTimestamp, DateTime untilTimestamp );
    List<ItemParentChildLinkObject> getItemParentChildLinkCollectionByChild( Guid child );
    ItemParentChildLinkObject getItemParentChildLinkByChildAndTimestamp( Guid child, DateTime timestamp );
    ItemParentChildLinkObject getItemParentChildLinkByChildAtTimestamp( Guid child, DateTime timestamp );
    List<ItemParentChildLinkObject> getItemParentChildLinkByChildFromTimestamp( Guid child, DateTime timestamp );
    List<ItemParentChildLinkObject> getItemParentChildLinkByChildUntilTimestamp( Guid child, DateTime timestamp );
    List<ItemParentChildLinkObject> getItemParentChildLinkByChildOverTimestamp( Guid child, DateTime fromTimestamp, DateTime untilTimestamp );
    List<ItemParentChildLinkObject> getItemParentChildLinkCollectionByTimestamp( DateTime timestamp );
    List<ItemParentChildLinkObject> getItemParentChildLinkCollectionAtTimestamp( DateTime timestamp );
    List<ItemParentChildLinkObject> getItemParentChildLinkCollectionFromTimestamp( DateTime timestamp );
    List<ItemParentChildLinkObject> getItemParentChildLinkCollectionUntilTimestamp( DateTime timestamp );
    List<ItemParentChildLinkObject> getItemParentChildLinkCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // LineInputDeviceCommand queries
    // ---------------------------------------------------------------------
    LineInputDeviceCommandObject getLineInputDeviceCommandById( Guid id );
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollection( );
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollectionByLineInputDevice( Guid lineInputDevice );
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollectionByLineInputDeviceAndTimestamp( Guid lineInputDevice, DateTime timestamp );
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollectionByLineInputDeviceAtTimestamp( Guid lineInputDevice, DateTime timestamp );
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollectionByLineInputDeviceFromTimestamp( Guid lineInputDevice, DateTime timestamp );
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollectionByLineInputDeviceUntilTimestamp( Guid lineInputDevice, DateTime timestamp );
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollectionByLineInputDeviceOverTimestamp( Guid lineInputDevice, DateTime fromTimestamp, DateTime untilTimestamp );
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollectionByTimestamp( DateTime timestamp );
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollectionAtTimestamp( DateTime timestamp );
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollectionFromTimestamp( DateTime timestamp );
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollectionUntilTimestamp( DateTime timestamp );
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollectionByReply( Guid reply );
    List<LineInputDeviceCommandObject> qetLineInputDeviceCommandCollectionByReplyIsNull(  );
    // ---------------------------------------------------------------------
    // LineInputDeviceCommandReply queries
    // ---------------------------------------------------------------------
    LineInputDeviceCommandReplyObject getLineInputDeviceCommandReplyById( Guid id );
    List<LineInputDeviceCommandReplyObject> getLineInputDeviceCommandReplyCollection( );
    List<LineInputDeviceCommandReplyObject> getLineInputDeviceCommandReplyCollectionByLineInputDevice( Guid lineInputDevice );
    List<LineInputDeviceCommandReplyObject> getLineInputDeviceCommandReplyCollectionByLineInputDeviceAndTimestamp( Guid lineInputDevice, DateTime timestamp );
    List<LineInputDeviceCommandReplyObject> getLineInputDeviceCommandReplyCollectionByLineInputDeviceAtTimestamp( Guid lineInputDevice, DateTime timestamp );
    List<LineInputDeviceCommandReplyObject> getLineInputDeviceCommandReplyCollectionByLineInputDeviceFromTimestamp( Guid lineInputDevice, DateTime timestamp );
    List<LineInputDeviceCommandReplyObject> getLineInputDeviceCommandReplyCollectionByLineInputDeviceUntilTimestamp( Guid lineInputDevice, DateTime timestamp );
    List<LineInputDeviceCommandReplyObject> getLineInputDeviceCommandReplyCollectionByLineInputDeviceOverTimestamp( Guid lineInputDevice, DateTime fromTimestamp, DateTime untilTimestamp );
    List<LineInputDeviceCommandReplyObject> getLineInputDeviceCommandReplyCollectionByTimestamp( DateTime timestamp );
    List<LineInputDeviceCommandReplyObject> getLineInputDeviceCommandReplyCollectionAtTimestamp( DateTime timestamp );
    List<LineInputDeviceCommandReplyObject> getLineInputDeviceCommandReplyCollectionFromTimestamp( DateTime timestamp );
    List<LineInputDeviceCommandReplyObject> getLineInputDeviceCommandReplyCollectionUntilTimestamp( DateTime timestamp );
    List<LineInputDeviceCommandReplyObject> getLineInputDeviceCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    LineInputDeviceCommandReplyObject getLineInputDeviceCommandReplyByCommand( Guid command );
    List<LineInputDeviceCommandReplyObject> qetLineInputDeviceCommandReplyCollectionByCommandIsNull(  );
    // ---------------------------------------------------------------------
    // LineInputDeviceConfiguration queries
    // ---------------------------------------------------------------------
    LineInputDeviceConfigurationObject getLineInputDeviceConfigurationById( Guid id );
    List<LineInputDeviceConfigurationObject> getLineInputDeviceConfigurationCollection( );
    List<LineInputDeviceConfigurationObject> getLineInputDeviceConfigurationCollectionByLineInputDevice( Guid lineInputDevice );
    LineInputDeviceConfigurationObject getLineInputDeviceConfigurationByLineInputDeviceAndTimestamp( Guid lineInputDevice, DateTime timestamp );
    LineInputDeviceConfigurationObject getLineInputDeviceConfigurationByLineInputDeviceAtTimestamp( Guid lineInputDevice, DateTime timestamp );
    List<LineInputDeviceConfigurationObject> getLineInputDeviceConfigurationByLineInputDeviceFromTimestamp( Guid lineInputDevice, DateTime timestamp );
    List<LineInputDeviceConfigurationObject> getLineInputDeviceConfigurationByLineInputDeviceUntilTimestamp( Guid lineInputDevice, DateTime timestamp );
    List<LineInputDeviceConfigurationObject> getLineInputDeviceConfigurationByLineInputDeviceOverTimestamp( Guid lineInputDevice, DateTime fromTimestamp, DateTime untilTimestamp );
    List<LineInputDeviceConfigurationObject> getLineInputDeviceConfigurationCollectionByTimestamp( DateTime timestamp );
    List<LineInputDeviceConfigurationObject> getLineInputDeviceConfigurationCollectionAtTimestamp( DateTime timestamp );
    List<LineInputDeviceConfigurationObject> getLineInputDeviceConfigurationCollectionFromTimestamp( DateTime timestamp );
    List<LineInputDeviceConfigurationObject> getLineInputDeviceConfigurationCollectionUntilTimestamp( DateTime timestamp );
    List<LineInputDeviceConfigurationObject> getLineInputDeviceConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // LineInputMessageRouting queries
    // ---------------------------------------------------------------------
    LineInputMessageRoutingObject getLineInputMessageRoutingById( Guid id );
    List<LineInputMessageRoutingObject> getLineInputMessageRoutingCollection( );
    List<LineInputMessageRoutingObject> getLineInputMessageRoutingCollectionByLineInputDevice( Guid lineInputDevice );
    LineInputMessageRoutingObject getLineInputMessageRoutingByLineInputDeviceAndType( Guid lineInputDevice, String type );
    // ---------------------------------------------------------------------
    // LineInputMessageRoutingDestination queries
    // ---------------------------------------------------------------------
    LineInputMessageRoutingDestinationObject getLineInputMessageRoutingDestinationById( Guid id );
    List<LineInputMessageRoutingDestinationObject> getLineInputMessageRoutingDestinationCollection( );
    List<LineInputMessageRoutingDestinationObject> getLineInputMessageRoutingDestinationCollectionByRouting( Guid routing );
    List<LineInputMessageRoutingDestinationObject> qetLineInputMessageRoutingDestinationCollectionByRouting(  );
    LineInputMessageRoutingDestinationObject getLineInputMessageRoutingDestinationByRoutingAndListener( Guid routing, Guid listener );
    List<LineInputMessageRoutingDestinationObject> qetLineInputMessageRoutingDestinationCollectionByRoutingAndListenerIsNull( Guid routing );
    List<LineInputMessageRoutingDestinationObject> getLineInputMessageRoutingDestinationCollectionByListener( Guid listener );
    List<LineInputMessageRoutingDestinationObject> qetLineInputMessageRoutingDestinationCollectionByListenerIsNull(  );
    // ---------------------------------------------------------------------
    // LineInputWhiteListEntry queries
    // ---------------------------------------------------------------------
    LineInputWhiteListEntryObject getLineInputWhiteListEntryById( Guid id );
    List<LineInputWhiteListEntryObject> getLineInputWhiteListEntryCollection( );
    List<LineInputWhiteListEntryObject> getLineInputWhiteListEntryCollectionByLineInputDevice( Guid lineInputDevice );
    List<LineInputWhiteListEntryObject> getLineInputWhiteListEntryCollectionByLineInputDeviceAndHostName( Guid lineInputDevice, String hostName );
    LineInputWhiteListEntryObject getLineInputWhiteListEntryByLineInputDeviceHostNameAndPort( Guid lineInputDevice, String hostName, int port );
    List<LineInputWhiteListEntryObject> getLineInputWhiteListEntryByLineInputDeviceHostNameFromPort( Guid lineInputDevice, String hostName, int port );
    List<LineInputWhiteListEntryObject> getLineInputWhiteListEntryByLineInputDeviceHostNameUntilPort( Guid lineInputDevice, String hostName, int port );
    List<LineInputWhiteListEntryObject> getLineInputWhiteListEntryByLineInputDeviceHostNameOverPort( Guid lineInputDevice, String hostName, int fromPort, int untilPort );
    // ---------------------------------------------------------------------
    // LogApplication queries
    // ---------------------------------------------------------------------
    LogApplicationObject getLogApplicationById( Guid id );
    List<LogApplicationObject> getLogApplicationCollection( );
    LogApplicationObject getLogApplicationByName( String name );
    // ---------------------------------------------------------------------
    // LogApplicationConfiguration queries
    // ---------------------------------------------------------------------
    LogApplicationConfigurationObject getLogApplicationConfigurationById( Guid id );
    List<LogApplicationConfigurationObject> getLogApplicationConfigurationCollection( );
    List<LogApplicationConfigurationObject> getLogApplicationConfigurationCollectionByApplication( Guid application );
    LogApplicationConfigurationObject getLogApplicationConfigurationByApplicationAndTimestamp( Guid application, DateTime timestamp );
    LogApplicationConfigurationObject getLogApplicationConfigurationByApplicationAtTimestamp( Guid application, DateTime timestamp );
    List<LogApplicationConfigurationObject> getLogApplicationConfigurationByApplicationFromTimestamp( Guid application, DateTime timestamp );
    List<LogApplicationConfigurationObject> getLogApplicationConfigurationByApplicationUntilTimestamp( Guid application, DateTime timestamp );
    List<LogApplicationConfigurationObject> getLogApplicationConfigurationByApplicationOverTimestamp( Guid application, DateTime fromTimestamp, DateTime untilTimestamp );
    List<LogApplicationConfigurationObject> getLogApplicationConfigurationCollectionByTimestamp( DateTime timestamp );
    List<LogApplicationConfigurationObject> getLogApplicationConfigurationCollectionAtTimestamp( DateTime timestamp );
    List<LogApplicationConfigurationObject> getLogApplicationConfigurationCollectionFromTimestamp( DateTime timestamp );
    List<LogApplicationConfigurationObject> getLogApplicationConfigurationCollectionUntilTimestamp( DateTime timestamp );
    List<LogApplicationConfigurationObject> getLogApplicationConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // LogHost queries
    // ---------------------------------------------------------------------
    LogHostObject getLogHostById( Guid id );
    List<LogHostObject> getLogHostCollection( );
    LogHostObject getLogHostByComputerName( String computerName );
    // ---------------------------------------------------------------------
    // LogHostConfiguration queries
    // ---------------------------------------------------------------------
    LogHostConfigurationObject getLogHostConfigurationById( Guid id );
    List<LogHostConfigurationObject> getLogHostConfigurationCollection( );
    List<LogHostConfigurationObject> getLogHostConfigurationCollectionByHost( Guid host );
    LogHostConfigurationObject getLogHostConfigurationByHostAndTimestamp( Guid host, DateTime timestamp );
    LogHostConfigurationObject getLogHostConfigurationByHostAtTimestamp( Guid host, DateTime timestamp );
    List<LogHostConfigurationObject> getLogHostConfigurationByHostFromTimestamp( Guid host, DateTime timestamp );
    List<LogHostConfigurationObject> getLogHostConfigurationByHostUntilTimestamp( Guid host, DateTime timestamp );
    List<LogHostConfigurationObject> getLogHostConfigurationByHostOverTimestamp( Guid host, DateTime fromTimestamp, DateTime untilTimestamp );
    List<LogHostConfigurationObject> getLogHostConfigurationCollectionByTimestamp( DateTime timestamp );
    List<LogHostConfigurationObject> getLogHostConfigurationCollectionAtTimestamp( DateTime timestamp );
    List<LogHostConfigurationObject> getLogHostConfigurationCollectionFromTimestamp( DateTime timestamp );
    List<LogHostConfigurationObject> getLogHostConfigurationCollectionUntilTimestamp( DateTime timestamp );
    List<LogHostConfigurationObject> getLogHostConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // LogLocation queries
    // ---------------------------------------------------------------------
    LogLocationObject getLogLocationById( Guid id );
    List<LogLocationObject> getLogLocationCollection( );
    List<LogLocationObject> getLogLocationCollectionByFileName( String fileName );
    LogLocationObject getLogLocationByFileNameAndLineNumber( String fileName, int lineNumber );
    List<LogLocationObject> getLogLocationByFileNameFromLineNumber( String fileName, int lineNumber );
    List<LogLocationObject> getLogLocationByFileNameUntilLineNumber( String fileName, int lineNumber );
    List<LogLocationObject> getLogLocationByFileNameOverLineNumber( String fileName, int fromLineNumber, int untilLineNumber );
    // ---------------------------------------------------------------------
    // LogProcess queries
    // ---------------------------------------------------------------------
    LogProcessObject getLogProcessById( Guid id );
    List<LogProcessObject> getLogProcessCollection( );
    List<LogProcessObject> getLogProcessCollectionByApplication( Guid application );
    List<LogProcessObject> getLogProcessCollectionByApplicationAndStarted( Guid application, DateTime started );
    List<LogProcessObject> getLogProcessCollectionByApplicationAtStarted( Guid application, DateTime started );
    List<LogProcessObject> getLogProcessCollectionByApplicationFromStarted( Guid application, DateTime started );
    List<LogProcessObject> getLogProcessCollectionByApplicationUntilStarted( Guid application, DateTime started );
    List<LogProcessObject> getLogProcessCollectionByApplicationOverStarted( Guid application, DateTime fromStarted, DateTime untilStarted );
    List<LogProcessObject> getLogProcessCollectionByHost( Guid host );
    List<LogProcessObject> qetLogProcessCollectionByHostIsNull(  );
    List<LogProcessObject> getLogProcessCollectionByHostAndStarted( Guid host, DateTime started );
    List<LogProcessObject> qetLogProcessCollectionByHostIsNullAndStarted( DateTime started );
    List<LogProcessObject> getLogProcessCollectionByHostAtStarted( Guid host, DateTime started );
    List<LogProcessObject> getLogProcessCollectionByHostFromStarted( Guid host, DateTime started );
    List<LogProcessObject> getLogProcessCollectionByHostUntilStarted( Guid host, DateTime started );
    List<LogProcessObject> getLogProcessCollectionByHostOverStarted( Guid host, DateTime fromStarted, DateTime untilStarted );
    List<LogProcessObject> getLogProcessCollectionByStarted( DateTime started );
    List<LogProcessObject> getLogProcessCollectionAtStarted( DateTime started );
    List<LogProcessObject> getLogProcessCollectionFromStarted( DateTime started );
    List<LogProcessObject> getLogProcessCollectionUntilStarted( DateTime started );
    List<LogProcessObject> getLogProcessCollectionOverStarted( DateTime fromStarted, DateTime untilStarted );
    // ---------------------------------------------------------------------
    // LogRecord queries
    // ---------------------------------------------------------------------
    LogRecordObject getLogRecordById( Guid id );
    List<LogRecordObject> getLogRecordCollection( );
    List<LogRecordObject> getLogRecordCollectionByThread( Guid thread );
    List<LogRecordObject> getLogRecordCollectionByThreadAndTimestamp( Guid thread, DateTime timestamp );
    List<LogRecordObject> getLogRecordCollectionByThreadAtTimestamp( Guid thread, DateTime timestamp );
    List<LogRecordObject> getLogRecordCollectionByThreadFromTimestamp( Guid thread, DateTime timestamp );
    List<LogRecordObject> getLogRecordCollectionByThreadUntilTimestamp( Guid thread, DateTime timestamp );
    List<LogRecordObject> getLogRecordCollectionByThreadOverTimestamp( Guid thread, DateTime fromTimestamp, DateTime untilTimestamp );
    List<LogRecordObject> getLogRecordCollectionByTimestamp( DateTime timestamp );
    List<LogRecordObject> getLogRecordCollectionAtTimestamp( DateTime timestamp );
    List<LogRecordObject> getLogRecordCollectionFromTimestamp( DateTime timestamp );
    List<LogRecordObject> getLogRecordCollectionUntilTimestamp( DateTime timestamp );
    List<LogRecordObject> getLogRecordCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<LogRecordObject> getLogRecordCollectionByLocation( Guid location );
    // ---------------------------------------------------------------------
    // LogThread queries
    // ---------------------------------------------------------------------
    LogThreadObject getLogThreadById( Guid id );
    List<LogThreadObject> getLogThreadCollection( );
    List<LogThreadObject> getLogThreadCollectionByProcess( Guid process );
    List<LogThreadObject> getLogThreadCollectionByProcessAndStarted( Guid process, DateTime started );
    List<LogThreadObject> getLogThreadCollectionByProcessAtStarted( Guid process, DateTime started );
    List<LogThreadObject> getLogThreadCollectionByProcessFromStarted( Guid process, DateTime started );
    List<LogThreadObject> getLogThreadCollectionByProcessUntilStarted( Guid process, DateTime started );
    List<LogThreadObject> getLogThreadCollectionByProcessOverStarted( Guid process, DateTime fromStarted, DateTime untilStarted );
    List<LogThreadObject> getLogThreadCollectionByStarted( DateTime started );
    List<LogThreadObject> getLogThreadCollectionAtStarted( DateTime started );
    List<LogThreadObject> getLogThreadCollectionFromStarted( DateTime started );
    List<LogThreadObject> getLogThreadCollectionUntilStarted( DateTime started );
    List<LogThreadObject> getLogThreadCollectionOverStarted( DateTime fromStarted, DateTime untilStarted );
    // ---------------------------------------------------------------------
    // LogTraceEntry queries
    // ---------------------------------------------------------------------
    LogTraceEntryObject getLogTraceEntryById( Guid id );
    List<LogTraceEntryObject> getLogTraceEntryCollection( );
    List<LogTraceEntryObject> getLogTraceEntryCollectionByThread( Guid thread );
    List<LogTraceEntryObject> getLogTraceEntryCollectionByThreadAndEntered( Guid thread, DateTime entered );
    List<LogTraceEntryObject> getLogTraceEntryCollectionByThreadAtEntered( Guid thread, DateTime entered );
    List<LogTraceEntryObject> getLogTraceEntryCollectionByThreadFromEntered( Guid thread, DateTime entered );
    List<LogTraceEntryObject> getLogTraceEntryCollectionByThreadUntilEntered( Guid thread, DateTime entered );
    List<LogTraceEntryObject> getLogTraceEntryCollectionByThreadOverEntered( Guid thread, DateTime fromEntered, DateTime untilEntered );
    List<LogTraceEntryObject> getLogTraceEntryCollectionByLocation( Guid location );
    List<LogTraceEntryObject> getLogTraceEntryCollectionByLocationAndEntered( Guid location, DateTime entered );
    List<LogTraceEntryObject> getLogTraceEntryCollectionByLocationAtEntered( Guid location, DateTime entered );
    List<LogTraceEntryObject> getLogTraceEntryCollectionByLocationFromEntered( Guid location, DateTime entered );
    List<LogTraceEntryObject> getLogTraceEntryCollectionByLocationUntilEntered( Guid location, DateTime entered );
    List<LogTraceEntryObject> getLogTraceEntryCollectionByLocationOverEntered( Guid location, DateTime fromEntered, DateTime untilEntered );
    List<LogTraceEntryObject> getLogTraceEntryCollectionByEntered( DateTime entered );
    List<LogTraceEntryObject> getLogTraceEntryCollectionAtEntered( DateTime entered );
    List<LogTraceEntryObject> getLogTraceEntryCollectionFromEntered( DateTime entered );
    List<LogTraceEntryObject> getLogTraceEntryCollectionUntilEntered( DateTime entered );
    List<LogTraceEntryObject> getLogTraceEntryCollectionOverEntered( DateTime fromEntered, DateTime untilEntered );
    // ---------------------------------------------------------------------
    // MapElement queries
    // ---------------------------------------------------------------------
    MapElementObject getMapElementById( Guid id );
    List<MapElementObject> getMapElementCollection( );
    List<MapElementObject> getMapElementCollectionByItem( Guid item );
    // ---------------------------------------------------------------------
    // MapInfo queries
    // ---------------------------------------------------------------------
    MapInfoObject getMapInfoById( Guid id );
    List<MapInfoObject> getMapInfoCollection( );
    // ---------------------------------------------------------------------
    // MapServiceOptions queries
    // ---------------------------------------------------------------------
    MapServiceOptionsObject getMapServiceOptionsById( Guid id );
    List<MapServiceOptionsObject> getMapServiceOptionsCollection( );
    MapServiceOptionsObject getMapServiceOptionsByTimestamp( DateTime timestamp );
    MapServiceOptionsObject getMapServiceOptionsAtTimestamp( DateTime timestamp );
    List<MapServiceOptionsObject> getMapServiceOptionsFromTimestamp( DateTime timestamp );
    List<MapServiceOptionsObject> getMapServiceOptionsUntilTimestamp( DateTime timestamp );
    List<MapServiceOptionsObject> getMapServiceOptionsOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // MaritimeIdentificationDigits queries
    // ---------------------------------------------------------------------
    MaritimeIdentificationDigitsObject getMaritimeIdentificationDigitsById( Guid id );
    List<MaritimeIdentificationDigitsObject> getMaritimeIdentificationDigitsCollection( );
    MaritimeIdentificationDigitsObject getMaritimeIdentificationDigitsByCode( int code );
    List<MaritimeIdentificationDigitsObject> getMaritimeIdentificationDigitsFromCode( int code );
    List<MaritimeIdentificationDigitsObject> getMaritimeIdentificationDigitsUntilCode( int code );
    List<MaritimeIdentificationDigitsObject> getMaritimeIdentificationDigitsOverCode( int fromCode, int untilCode );
    List<MaritimeIdentificationDigitsObject> getMaritimeIdentificationDigitsCollectionByCountry( Guid country );
    // ---------------------------------------------------------------------
    // MediaProxySession queries
    // ---------------------------------------------------------------------
    MediaProxySessionObject getMediaProxySessionById( Guid id );
    List<MediaProxySessionObject> getMediaProxySessionCollection( );
    List<MediaProxySessionObject> getMediaProxySessionCollectionByService( Guid service );
    MediaProxySessionObject getMediaProxySessionByServiceAndName( Guid service, String name );
    // ---------------------------------------------------------------------
    // MediaProxySessionFile queries
    // ---------------------------------------------------------------------
    MediaProxySessionFileObject getMediaProxySessionFileById( Guid id );
    List<MediaProxySessionFileObject> getMediaProxySessionFileCollection( );
    List<MediaProxySessionFileObject> getMediaProxySessionFileCollectionByProxySession( Guid proxySession );
    MediaProxySessionFileObject getMediaProxySessionFileByProxySessionAndTimestamp( Guid proxySession, DateTime timestamp );
    MediaProxySessionFileObject getMediaProxySessionFileByProxySessionAtTimestamp( Guid proxySession, DateTime timestamp );
    List<MediaProxySessionFileObject> getMediaProxySessionFileByProxySessionFromTimestamp( Guid proxySession, DateTime timestamp );
    List<MediaProxySessionFileObject> getMediaProxySessionFileByProxySessionUntilTimestamp( Guid proxySession, DateTime timestamp );
    List<MediaProxySessionFileObject> getMediaProxySessionFileByProxySessionOverTimestamp( Guid proxySession, DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // MediaProxySessionOptions queries
    // ---------------------------------------------------------------------
    MediaProxySessionOptionsObject getMediaProxySessionOptionsById( Guid id );
    List<MediaProxySessionOptionsObject> getMediaProxySessionOptionsCollection( );
    List<MediaProxySessionOptionsObject> getMediaProxySessionOptionsCollectionByProxySession( Guid proxySession );
    MediaProxySessionOptionsObject getMediaProxySessionOptionsByProxySessionAndTimestamp( Guid proxySession, DateTime timestamp );
    MediaProxySessionOptionsObject getMediaProxySessionOptionsByProxySessionAtTimestamp( Guid proxySession, DateTime timestamp );
    List<MediaProxySessionOptionsObject> getMediaProxySessionOptionsByProxySessionFromTimestamp( Guid proxySession, DateTime timestamp );
    List<MediaProxySessionOptionsObject> getMediaProxySessionOptionsByProxySessionUntilTimestamp( Guid proxySession, DateTime timestamp );
    List<MediaProxySessionOptionsObject> getMediaProxySessionOptionsByProxySessionOverTimestamp( Guid proxySession, DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // MediaService queries
    // ---------------------------------------------------------------------
    MediaServiceObject getMediaServiceById( Guid id );
    List<MediaServiceObject> getMediaServiceCollection( );
    // ---------------------------------------------------------------------
    // MediaServiceOptions queries
    // ---------------------------------------------------------------------
    MediaServiceOptionsObject getMediaServiceOptionsById( Guid id );
    List<MediaServiceOptionsObject> getMediaServiceOptionsCollection( );
    List<MediaServiceOptionsObject> getMediaServiceOptionsCollectionByMediaService( Guid mediaService );
    MediaServiceOptionsObject getMediaServiceOptionsByMediaServiceAndTimestamp( Guid mediaService, DateTime timestamp );
    MediaServiceOptionsObject getMediaServiceOptionsByMediaServiceAtTimestamp( Guid mediaService, DateTime timestamp );
    List<MediaServiceOptionsObject> getMediaServiceOptionsByMediaServiceFromTimestamp( Guid mediaService, DateTime timestamp );
    List<MediaServiceOptionsObject> getMediaServiceOptionsByMediaServiceUntilTimestamp( Guid mediaService, DateTime timestamp );
    List<MediaServiceOptionsObject> getMediaServiceOptionsByMediaServiceOverTimestamp( Guid mediaService, DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // NamespaceElement queries
    // ---------------------------------------------------------------------
    NamespaceElementObject getNamespaceElementById( Guid id );
    List<NamespaceElementObject> getNamespaceElementCollection( );
    List<NamespaceElementObject> getNamespaceElementCollectionByNamespace( Guid namespace );
    NamespaceElementObject getNamespaceElementByNamespaceAndName( Guid namespace, String name );
    // ---------------------------------------------------------------------
    // ElementType queries
    // ---------------------------------------------------------------------
    ElementTypeObject getElementTypeById( Guid id );
    List<ElementTypeObject> getElementTypeCollection( );
    List<ElementTypeObject> getElementTypeCollectionByNamespace( Guid namespace );
    ElementTypeObject getElementTypeByNamespaceAndName( Guid namespace, String name );
    // ---------------------------------------------------------------------
    // Namespace queries
    // ---------------------------------------------------------------------
    NamespaceObject getNamespaceById( Guid id );
    List<NamespaceObject> getNamespaceCollection( );
    List<NamespaceObject> getNamespaceCollectionByNamespace( Guid namespace );
    NamespaceObject getNamespaceByNamespaceAndName( Guid namespace, String name );
    // ---------------------------------------------------------------------
    // OilSpill queries
    // ---------------------------------------------------------------------
    OilSpillObject getOilSpillById( Guid id );
    List<OilSpillObject> getOilSpillCollection( );
    List<OilSpillObject> getOilSpillCollectionByOilSpillDetector( Guid oilSpillDetector );
    List<OilSpillObject> getOilSpillCollectionByOilSpillDetectorAndTimestamp( Guid oilSpillDetector, DateTime timestamp );
    List<OilSpillObject> getOilSpillCollectionByOilSpillDetectorAtTimestamp( Guid oilSpillDetector, DateTime timestamp );
    List<OilSpillObject> getOilSpillCollectionByOilSpillDetectorFromTimestamp( Guid oilSpillDetector, DateTime timestamp );
    List<OilSpillObject> getOilSpillCollectionByOilSpillDetectorUntilTimestamp( Guid oilSpillDetector, DateTime timestamp );
    List<OilSpillObject> getOilSpillCollectionByOilSpillDetectorOverTimestamp( Guid oilSpillDetector, DateTime fromTimestamp, DateTime untilTimestamp );
    List<OilSpillObject> getOilSpillCollectionByTimestamp( DateTime timestamp );
    List<OilSpillObject> getOilSpillCollectionAtTimestamp( DateTime timestamp );
    List<OilSpillObject> getOilSpillCollectionFromTimestamp( DateTime timestamp );
    List<OilSpillObject> getOilSpillCollectionUntilTimestamp( DateTime timestamp );
    List<OilSpillObject> getOilSpillCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // OilSpillDetectorCommand queries
    // ---------------------------------------------------------------------
    OilSpillDetectorCommandObject getOilSpillDetectorCommandById( Guid id );
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollection( );
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollectionByOilSpillDetector( Guid oilSpillDetector );
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollectionByOilSpillDetectorAndTimestamp( Guid oilSpillDetector, DateTime timestamp );
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollectionByOilSpillDetectorAtTimestamp( Guid oilSpillDetector, DateTime timestamp );
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollectionByOilSpillDetectorFromTimestamp( Guid oilSpillDetector, DateTime timestamp );
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollectionByOilSpillDetectorUntilTimestamp( Guid oilSpillDetector, DateTime timestamp );
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollectionByOilSpillDetectorOverTimestamp( Guid oilSpillDetector, DateTime fromTimestamp, DateTime untilTimestamp );
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollectionByTimestamp( DateTime timestamp );
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollectionAtTimestamp( DateTime timestamp );
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollectionFromTimestamp( DateTime timestamp );
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollectionUntilTimestamp( DateTime timestamp );
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollectionByReply( Guid reply );
    List<OilSpillDetectorCommandObject> qetOilSpillDetectorCommandCollectionByReplyIsNull(  );
    // ---------------------------------------------------------------------
    // OilSpillDetectorCommandReply queries
    // ---------------------------------------------------------------------
    OilSpillDetectorCommandReplyObject getOilSpillDetectorCommandReplyById( Guid id );
    List<OilSpillDetectorCommandReplyObject> getOilSpillDetectorCommandReplyCollection( );
    List<OilSpillDetectorCommandReplyObject> getOilSpillDetectorCommandReplyCollectionByOilSpillDetector( Guid oilSpillDetector );
    List<OilSpillDetectorCommandReplyObject> getOilSpillDetectorCommandReplyCollectionByOilSpillDetectorAndTimestamp( Guid oilSpillDetector, DateTime timestamp );
    List<OilSpillDetectorCommandReplyObject> getOilSpillDetectorCommandReplyCollectionByOilSpillDetectorAtTimestamp( Guid oilSpillDetector, DateTime timestamp );
    List<OilSpillDetectorCommandReplyObject> getOilSpillDetectorCommandReplyCollectionByOilSpillDetectorFromTimestamp( Guid oilSpillDetector, DateTime timestamp );
    List<OilSpillDetectorCommandReplyObject> getOilSpillDetectorCommandReplyCollectionByOilSpillDetectorUntilTimestamp( Guid oilSpillDetector, DateTime timestamp );
    List<OilSpillDetectorCommandReplyObject> getOilSpillDetectorCommandReplyCollectionByOilSpillDetectorOverTimestamp( Guid oilSpillDetector, DateTime fromTimestamp, DateTime untilTimestamp );
    List<OilSpillDetectorCommandReplyObject> getOilSpillDetectorCommandReplyCollectionByTimestamp( DateTime timestamp );
    List<OilSpillDetectorCommandReplyObject> getOilSpillDetectorCommandReplyCollectionAtTimestamp( DateTime timestamp );
    List<OilSpillDetectorCommandReplyObject> getOilSpillDetectorCommandReplyCollectionFromTimestamp( DateTime timestamp );
    List<OilSpillDetectorCommandReplyObject> getOilSpillDetectorCommandReplyCollectionUntilTimestamp( DateTime timestamp );
    List<OilSpillDetectorCommandReplyObject> getOilSpillDetectorCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    OilSpillDetectorCommandReplyObject getOilSpillDetectorCommandReplyByCommand( Guid command );
    List<OilSpillDetectorCommandReplyObject> qetOilSpillDetectorCommandReplyCollectionByCommandIsNull(  );
    // ---------------------------------------------------------------------
    // OilSpillDetectorConfiguration queries
    // ---------------------------------------------------------------------
    OilSpillDetectorConfigurationObject getOilSpillDetectorConfigurationById( Guid id );
    List<OilSpillDetectorConfigurationObject> getOilSpillDetectorConfigurationCollection( );
    List<OilSpillDetectorConfigurationObject> getOilSpillDetectorConfigurationCollectionByOilSpillDetector( Guid oilSpillDetector );
    OilSpillDetectorConfigurationObject getOilSpillDetectorConfigurationByOilSpillDetectorAndTimestamp( Guid oilSpillDetector, DateTime timestamp );
    OilSpillDetectorConfigurationObject getOilSpillDetectorConfigurationByOilSpillDetectorAtTimestamp( Guid oilSpillDetector, DateTime timestamp );
    List<OilSpillDetectorConfigurationObject> getOilSpillDetectorConfigurationByOilSpillDetectorFromTimestamp( Guid oilSpillDetector, DateTime timestamp );
    List<OilSpillDetectorConfigurationObject> getOilSpillDetectorConfigurationByOilSpillDetectorUntilTimestamp( Guid oilSpillDetector, DateTime timestamp );
    List<OilSpillDetectorConfigurationObject> getOilSpillDetectorConfigurationByOilSpillDetectorOverTimestamp( Guid oilSpillDetector, DateTime fromTimestamp, DateTime untilTimestamp );
    List<OilSpillDetectorConfigurationObject> getOilSpillDetectorConfigurationCollectionByTimestamp( DateTime timestamp );
    List<OilSpillDetectorConfigurationObject> getOilSpillDetectorConfigurationCollectionAtTimestamp( DateTime timestamp );
    List<OilSpillDetectorConfigurationObject> getOilSpillDetectorConfigurationCollectionFromTimestamp( DateTime timestamp );
    List<OilSpillDetectorConfigurationObject> getOilSpillDetectorConfigurationCollectionUntilTimestamp( DateTime timestamp );
    List<OilSpillDetectorConfigurationObject> getOilSpillDetectorConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<OilSpillDetectorConfigurationObject> getOilSpillDetectorConfigurationCollectionByTargetMMSI( Guid targetMMSI );
    List<OilSpillDetectorConfigurationObject> qetOilSpillDetectorConfigurationCollectionByTargetMMSIIsNull(  );
    // ---------------------------------------------------------------------
    // Position2DTimeseriesValue queries
    // ---------------------------------------------------------------------
    Position2DTimeseriesValueObject getPosition2DTimeseriesValueById( Guid id );
    List<Position2DTimeseriesValueObject> getPosition2DTimeseriesValueCollection( );
    List<Position2DTimeseriesValueObject> getPosition2DTimeseriesValueCollectionByTimeseries( Guid timeseries );
    Position2DTimeseriesValueObject getPosition2DTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
    Position2DTimeseriesValueObject getPosition2DTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
    List<Position2DTimeseriesValueObject> getPosition2DTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
    List<Position2DTimeseriesValueObject> getPosition2DTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
    List<Position2DTimeseriesValueObject> getPosition2DTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
    List<Position2DTimeseriesValueObject> getPosition2DTimeseriesValueCollectionByTimestamp( DateTime timestamp );
    List<Position2DTimeseriesValueObject> getPosition2DTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
    List<Position2DTimeseriesValueObject> getPosition2DTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
    List<Position2DTimeseriesValueObject> getPosition2DTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
    List<Position2DTimeseriesValueObject> getPosition2DTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // Position3DTimeseriesValue queries
    // ---------------------------------------------------------------------
    Position3DTimeseriesValueObject getPosition3DTimeseriesValueById( Guid id );
    List<Position3DTimeseriesValueObject> getPosition3DTimeseriesValueCollection( );
    List<Position3DTimeseriesValueObject> getPosition3DTimeseriesValueCollectionByTimeseries( Guid timeseries );
    Position3DTimeseriesValueObject getPosition3DTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
    Position3DTimeseriesValueObject getPosition3DTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
    List<Position3DTimeseriesValueObject> getPosition3DTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
    List<Position3DTimeseriesValueObject> getPosition3DTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
    List<Position3DTimeseriesValueObject> getPosition3DTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
    List<Position3DTimeseriesValueObject> getPosition3DTimeseriesValueCollectionByTimestamp( DateTime timestamp );
    List<Position3DTimeseriesValueObject> getPosition3DTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
    List<Position3DTimeseriesValueObject> getPosition3DTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
    List<Position3DTimeseriesValueObject> getPosition3DTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
    List<Position3DTimeseriesValueObject> getPosition3DTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // ProcessTrackValueResult queries
    // ---------------------------------------------------------------------
    ProcessTrackValueResultObject getProcessTrackValueResultById( Guid id );
    List<ProcessTrackValueResultObject> getProcessTrackValueResultCollection( );
    // ---------------------------------------------------------------------
    // Property queries
    // ---------------------------------------------------------------------
    PropertyObject getPropertyById( Guid id );
    List<PropertyObject> getPropertyCollection( );
    List<PropertyObject> getPropertyCollectionByElement( Guid element );
    PropertyObject getPropertyByElementAndDefinition( Guid element, Guid definition );
    List<PropertyObject> getPropertyCollectionByDefinition( Guid definition );
    // ---------------------------------------------------------------------
    // BinaryProperty queries
    // ---------------------------------------------------------------------
    BinaryPropertyObject getBinaryPropertyById( Guid id );
    List<BinaryPropertyObject> getBinaryPropertyCollection( );
    List<BinaryPropertyObject> getBinaryPropertyCollectionByElement( Guid element );
    BinaryPropertyObject getBinaryPropertyByElementAndDefinition( Guid element, Guid definition );
    List<BinaryPropertyObject> getBinaryPropertyCollectionByDefinition( Guid definition );
    // ---------------------------------------------------------------------
    // BooleanProperty queries
    // ---------------------------------------------------------------------
    BooleanPropertyObject getBooleanPropertyById( Guid id );
    List<BooleanPropertyObject> getBooleanPropertyCollection( );
    List<BooleanPropertyObject> getBooleanPropertyCollectionByElement( Guid element );
    BooleanPropertyObject getBooleanPropertyByElementAndDefinition( Guid element, Guid definition );
    List<BooleanPropertyObject> getBooleanPropertyCollectionByDefinition( Guid definition );
    // ---------------------------------------------------------------------
    // ByteProperty queries
    // ---------------------------------------------------------------------
    BytePropertyObject getBytePropertyById( Guid id );
    List<BytePropertyObject> getBytePropertyCollection( );
    List<BytePropertyObject> getBytePropertyCollectionByElement( Guid element );
    BytePropertyObject getBytePropertyByElementAndDefinition( Guid element, Guid definition );
    List<BytePropertyObject> getBytePropertyCollectionByDefinition( Guid definition );
    // ---------------------------------------------------------------------
    // DateTimeProperty queries
    // ---------------------------------------------------------------------
    DateTimePropertyObject getDateTimePropertyById( Guid id );
    List<DateTimePropertyObject> getDateTimePropertyCollection( );
    List<DateTimePropertyObject> getDateTimePropertyCollectionByElement( Guid element );
    DateTimePropertyObject getDateTimePropertyByElementAndDefinition( Guid element, Guid definition );
    List<DateTimePropertyObject> getDateTimePropertyCollectionByDefinition( Guid definition );
    // ---------------------------------------------------------------------
    // DoubleProperty queries
    // ---------------------------------------------------------------------
    DoublePropertyObject getDoublePropertyById( Guid id );
    List<DoublePropertyObject> getDoublePropertyCollection( );
    List<DoublePropertyObject> getDoublePropertyCollectionByElement( Guid element );
    DoublePropertyObject getDoublePropertyByElementAndDefinition( Guid element, Guid definition );
    List<DoublePropertyObject> getDoublePropertyCollectionByDefinition( Guid definition );
    // ---------------------------------------------------------------------
    // GuidProperty queries
    // ---------------------------------------------------------------------
    GuidPropertyObject getGuidPropertyById( Guid id );
    List<GuidPropertyObject> getGuidPropertyCollection( );
    List<GuidPropertyObject> getGuidPropertyCollectionByElement( Guid element );
    GuidPropertyObject getGuidPropertyByElementAndDefinition( Guid element, Guid definition );
    List<GuidPropertyObject> getGuidPropertyCollectionByDefinition( Guid definition );
    // ---------------------------------------------------------------------
    // Int16Property queries
    // ---------------------------------------------------------------------
    Int16PropertyObject getInt16PropertyById( Guid id );
    List<Int16PropertyObject> getInt16PropertyCollection( );
    List<Int16PropertyObject> getInt16PropertyCollectionByElement( Guid element );
    Int16PropertyObject getInt16PropertyByElementAndDefinition( Guid element, Guid definition );
    List<Int16PropertyObject> getInt16PropertyCollectionByDefinition( Guid definition );
    // ---------------------------------------------------------------------
    // Int32Property queries
    // ---------------------------------------------------------------------
    Int32PropertyObject getInt32PropertyById( Guid id );
    List<Int32PropertyObject> getInt32PropertyCollection( );
    List<Int32PropertyObject> getInt32PropertyCollectionByElement( Guid element );
    Int32PropertyObject getInt32PropertyByElementAndDefinition( Guid element, Guid definition );
    List<Int32PropertyObject> getInt32PropertyCollectionByDefinition( Guid definition );
    // ---------------------------------------------------------------------
    // Int64Property queries
    // ---------------------------------------------------------------------
    Int64PropertyObject getInt64PropertyById( Guid id );
    List<Int64PropertyObject> getInt64PropertyCollection( );
    List<Int64PropertyObject> getInt64PropertyCollectionByElement( Guid element );
    Int64PropertyObject getInt64PropertyByElementAndDefinition( Guid element, Guid definition );
    List<Int64PropertyObject> getInt64PropertyCollectionByDefinition( Guid definition );
    // ---------------------------------------------------------------------
    // ReferenceProperty queries
    // ---------------------------------------------------------------------
    ReferencePropertyObject getReferencePropertyById( Guid id );
    List<ReferencePropertyObject> getReferencePropertyCollection( );
    List<ReferencePropertyObject> getReferencePropertyCollectionByElement( Guid element );
    ReferencePropertyObject getReferencePropertyByElementAndDefinition( Guid element, Guid definition );
    List<ReferencePropertyObject> getReferencePropertyCollectionByDefinition( Guid definition );
    List<ReferencePropertyObject> getReferencePropertyCollectionByValue( Guid value );
    List<ReferencePropertyObject> qetReferencePropertyCollectionByValueIsNull(  );
    // ---------------------------------------------------------------------
    // SByteProperty queries
    // ---------------------------------------------------------------------
    SBytePropertyObject getSBytePropertyById( Guid id );
    List<SBytePropertyObject> getSBytePropertyCollection( );
    List<SBytePropertyObject> getSBytePropertyCollectionByElement( Guid element );
    SBytePropertyObject getSBytePropertyByElementAndDefinition( Guid element, Guid definition );
    List<SBytePropertyObject> getSBytePropertyCollectionByDefinition( Guid definition );
    // ---------------------------------------------------------------------
    // SingleProperty queries
    // ---------------------------------------------------------------------
    SinglePropertyObject getSinglePropertyById( Guid id );
    List<SinglePropertyObject> getSinglePropertyCollection( );
    List<SinglePropertyObject> getSinglePropertyCollectionByElement( Guid element );
    SinglePropertyObject getSinglePropertyByElementAndDefinition( Guid element, Guid definition );
    List<SinglePropertyObject> getSinglePropertyCollectionByDefinition( Guid definition );
    // ---------------------------------------------------------------------
    // StringProperty queries
    // ---------------------------------------------------------------------
    StringPropertyObject getStringPropertyById( Guid id );
    List<StringPropertyObject> getStringPropertyCollection( );
    List<StringPropertyObject> getStringPropertyCollectionByElement( Guid element );
    StringPropertyObject getStringPropertyByElementAndDefinition( Guid element, Guid definition );
    List<StringPropertyObject> getStringPropertyCollectionByDefinition( Guid definition );
    // ---------------------------------------------------------------------
    // TimeseriesProperty queries
    // ---------------------------------------------------------------------
    TimeseriesPropertyObject getTimeseriesPropertyById( Guid id );
    List<TimeseriesPropertyObject> getTimeseriesPropertyCollection( );
    List<TimeseriesPropertyObject> getTimeseriesPropertyCollectionByElement( Guid element );
    TimeseriesPropertyObject getTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
    List<TimeseriesPropertyObject> getTimeseriesPropertyCollectionByDefinition( Guid definition );
    // ---------------------------------------------------------------------
    // BinaryTimeseriesProperty queries
    // ---------------------------------------------------------------------
    BinaryTimeseriesPropertyObject getBinaryTimeseriesPropertyById( Guid id );
    List<BinaryTimeseriesPropertyObject> getBinaryTimeseriesPropertyCollection( );
    List<BinaryTimeseriesPropertyObject> getBinaryTimeseriesPropertyCollectionByElement( Guid element );
    BinaryTimeseriesPropertyObject getBinaryTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
    List<BinaryTimeseriesPropertyObject> getBinaryTimeseriesPropertyCollectionByDefinition( Guid definition );
    List<BinaryTimeseriesPropertyObject> getBinaryTimeseriesPropertyCollectionByTimeseries( Guid timeseries );
    List<BinaryTimeseriesPropertyObject> qetBinaryTimeseriesPropertyCollectionByTimeseriesIsNull(  );
    // ---------------------------------------------------------------------
    // BooleanTimeseriesProperty queries
    // ---------------------------------------------------------------------
    BooleanTimeseriesPropertyObject getBooleanTimeseriesPropertyById( Guid id );
    List<BooleanTimeseriesPropertyObject> getBooleanTimeseriesPropertyCollection( );
    List<BooleanTimeseriesPropertyObject> getBooleanTimeseriesPropertyCollectionByElement( Guid element );
    BooleanTimeseriesPropertyObject getBooleanTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
    List<BooleanTimeseriesPropertyObject> getBooleanTimeseriesPropertyCollectionByDefinition( Guid definition );
    List<BooleanTimeseriesPropertyObject> getBooleanTimeseriesPropertyCollectionByTimeseries( Guid timeseries );
    List<BooleanTimeseriesPropertyObject> qetBooleanTimeseriesPropertyCollectionByTimeseriesIsNull(  );
    // ---------------------------------------------------------------------
    // ByteTimeseriesProperty queries
    // ---------------------------------------------------------------------
    ByteTimeseriesPropertyObject getByteTimeseriesPropertyById( Guid id );
    List<ByteTimeseriesPropertyObject> getByteTimeseriesPropertyCollection( );
    List<ByteTimeseriesPropertyObject> getByteTimeseriesPropertyCollectionByElement( Guid element );
    ByteTimeseriesPropertyObject getByteTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
    List<ByteTimeseriesPropertyObject> getByteTimeseriesPropertyCollectionByDefinition( Guid definition );
    List<ByteTimeseriesPropertyObject> getByteTimeseriesPropertyCollectionByTimeseries( Guid timeseries );
    List<ByteTimeseriesPropertyObject> qetByteTimeseriesPropertyCollectionByTimeseriesIsNull(  );
    // ---------------------------------------------------------------------
    // DateTimeTimeseriesProperty queries
    // ---------------------------------------------------------------------
    DateTimeTimeseriesPropertyObject getDateTimeTimeseriesPropertyById( Guid id );
    List<DateTimeTimeseriesPropertyObject> getDateTimeTimeseriesPropertyCollection( );
    List<DateTimeTimeseriesPropertyObject> getDateTimeTimeseriesPropertyCollectionByElement( Guid element );
    DateTimeTimeseriesPropertyObject getDateTimeTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
    List<DateTimeTimeseriesPropertyObject> getDateTimeTimeseriesPropertyCollectionByDefinition( Guid definition );
    List<DateTimeTimeseriesPropertyObject> getDateTimeTimeseriesPropertyCollectionByTimeseries( Guid timeseries );
    List<DateTimeTimeseriesPropertyObject> qetDateTimeTimeseriesPropertyCollectionByTimeseriesIsNull(  );
    // ---------------------------------------------------------------------
    // DoubleTimeseriesProperty queries
    // ---------------------------------------------------------------------
    DoubleTimeseriesPropertyObject getDoubleTimeseriesPropertyById( Guid id );
    List<DoubleTimeseriesPropertyObject> getDoubleTimeseriesPropertyCollection( );
    List<DoubleTimeseriesPropertyObject> getDoubleTimeseriesPropertyCollectionByElement( Guid element );
    DoubleTimeseriesPropertyObject getDoubleTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
    List<DoubleTimeseriesPropertyObject> getDoubleTimeseriesPropertyCollectionByDefinition( Guid definition );
    List<DoubleTimeseriesPropertyObject> getDoubleTimeseriesPropertyCollectionByTimeseries( Guid timeseries );
    List<DoubleTimeseriesPropertyObject> qetDoubleTimeseriesPropertyCollectionByTimeseriesIsNull(  );
    // ---------------------------------------------------------------------
    // GuidTimeseriesProperty queries
    // ---------------------------------------------------------------------
    GuidTimeseriesPropertyObject getGuidTimeseriesPropertyById( Guid id );
    List<GuidTimeseriesPropertyObject> getGuidTimeseriesPropertyCollection( );
    List<GuidTimeseriesPropertyObject> getGuidTimeseriesPropertyCollectionByElement( Guid element );
    GuidTimeseriesPropertyObject getGuidTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
    List<GuidTimeseriesPropertyObject> getGuidTimeseriesPropertyCollectionByDefinition( Guid definition );
    List<GuidTimeseriesPropertyObject> getGuidTimeseriesPropertyCollectionByTimeseries( Guid timeseries );
    List<GuidTimeseriesPropertyObject> qetGuidTimeseriesPropertyCollectionByTimeseriesIsNull(  );
    // ---------------------------------------------------------------------
    // Int16TimeseriesProperty queries
    // ---------------------------------------------------------------------
    Int16TimeseriesPropertyObject getInt16TimeseriesPropertyById( Guid id );
    List<Int16TimeseriesPropertyObject> getInt16TimeseriesPropertyCollection( );
    List<Int16TimeseriesPropertyObject> getInt16TimeseriesPropertyCollectionByElement( Guid element );
    Int16TimeseriesPropertyObject getInt16TimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
    List<Int16TimeseriesPropertyObject> getInt16TimeseriesPropertyCollectionByDefinition( Guid definition );
    List<Int16TimeseriesPropertyObject> getInt16TimeseriesPropertyCollectionByTimeseries( Guid timeseries );
    List<Int16TimeseriesPropertyObject> qetInt16TimeseriesPropertyCollectionByTimeseriesIsNull(  );
    // ---------------------------------------------------------------------
    // Int32TimeseriesProperty queries
    // ---------------------------------------------------------------------
    Int32TimeseriesPropertyObject getInt32TimeseriesPropertyById( Guid id );
    List<Int32TimeseriesPropertyObject> getInt32TimeseriesPropertyCollection( );
    List<Int32TimeseriesPropertyObject> getInt32TimeseriesPropertyCollectionByElement( Guid element );
    Int32TimeseriesPropertyObject getInt32TimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
    List<Int32TimeseriesPropertyObject> getInt32TimeseriesPropertyCollectionByDefinition( Guid definition );
    List<Int32TimeseriesPropertyObject> getInt32TimeseriesPropertyCollectionByTimeseries( Guid timeseries );
    List<Int32TimeseriesPropertyObject> qetInt32TimeseriesPropertyCollectionByTimeseriesIsNull(  );
    // ---------------------------------------------------------------------
    // Int64TimeseriesProperty queries
    // ---------------------------------------------------------------------
    Int64TimeseriesPropertyObject getInt64TimeseriesPropertyById( Guid id );
    List<Int64TimeseriesPropertyObject> getInt64TimeseriesPropertyCollection( );
    List<Int64TimeseriesPropertyObject> getInt64TimeseriesPropertyCollectionByElement( Guid element );
    Int64TimeseriesPropertyObject getInt64TimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
    List<Int64TimeseriesPropertyObject> getInt64TimeseriesPropertyCollectionByDefinition( Guid definition );
    List<Int64TimeseriesPropertyObject> getInt64TimeseriesPropertyCollectionByTimeseries( Guid timeseries );
    List<Int64TimeseriesPropertyObject> qetInt64TimeseriesPropertyCollectionByTimeseriesIsNull(  );
    // ---------------------------------------------------------------------
    // ReferenceTimeseriesProperty queries
    // ---------------------------------------------------------------------
    ReferenceTimeseriesPropertyObject getReferenceTimeseriesPropertyById( Guid id );
    List<ReferenceTimeseriesPropertyObject> getReferenceTimeseriesPropertyCollection( );
    List<ReferenceTimeseriesPropertyObject> getReferenceTimeseriesPropertyCollectionByElement( Guid element );
    ReferenceTimeseriesPropertyObject getReferenceTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
    List<ReferenceTimeseriesPropertyObject> getReferenceTimeseriesPropertyCollectionByDefinition( Guid definition );
    List<ReferenceTimeseriesPropertyObject> getReferenceTimeseriesPropertyCollectionByTimeseries( Guid timeseries );
    List<ReferenceTimeseriesPropertyObject> qetReferenceTimeseriesPropertyCollectionByTimeseriesIsNull(  );
    // ---------------------------------------------------------------------
    // SByteTimeseriesProperty queries
    // ---------------------------------------------------------------------
    SByteTimeseriesPropertyObject getSByteTimeseriesPropertyById( Guid id );
    List<SByteTimeseriesPropertyObject> getSByteTimeseriesPropertyCollection( );
    List<SByteTimeseriesPropertyObject> getSByteTimeseriesPropertyCollectionByElement( Guid element );
    SByteTimeseriesPropertyObject getSByteTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
    List<SByteTimeseriesPropertyObject> getSByteTimeseriesPropertyCollectionByDefinition( Guid definition );
    List<SByteTimeseriesPropertyObject> getSByteTimeseriesPropertyCollectionByTimeseries( Guid timeseries );
    List<SByteTimeseriesPropertyObject> qetSByteTimeseriesPropertyCollectionByTimeseriesIsNull(  );
    // ---------------------------------------------------------------------
    // SingleTimeseriesProperty queries
    // ---------------------------------------------------------------------
    SingleTimeseriesPropertyObject getSingleTimeseriesPropertyById( Guid id );
    List<SingleTimeseriesPropertyObject> getSingleTimeseriesPropertyCollection( );
    List<SingleTimeseriesPropertyObject> getSingleTimeseriesPropertyCollectionByElement( Guid element );
    SingleTimeseriesPropertyObject getSingleTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
    List<SingleTimeseriesPropertyObject> getSingleTimeseriesPropertyCollectionByDefinition( Guid definition );
    List<SingleTimeseriesPropertyObject> getSingleTimeseriesPropertyCollectionByTimeseries( Guid timeseries );
    List<SingleTimeseriesPropertyObject> qetSingleTimeseriesPropertyCollectionByTimeseriesIsNull(  );
    // ---------------------------------------------------------------------
    // StringTimeseriesProperty queries
    // ---------------------------------------------------------------------
    StringTimeseriesPropertyObject getStringTimeseriesPropertyById( Guid id );
    List<StringTimeseriesPropertyObject> getStringTimeseriesPropertyCollection( );
    List<StringTimeseriesPropertyObject> getStringTimeseriesPropertyCollectionByElement( Guid element );
    StringTimeseriesPropertyObject getStringTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
    List<StringTimeseriesPropertyObject> getStringTimeseriesPropertyCollectionByDefinition( Guid definition );
    List<StringTimeseriesPropertyObject> getStringTimeseriesPropertyCollectionByTimeseries( Guid timeseries );
    List<StringTimeseriesPropertyObject> qetStringTimeseriesPropertyCollectionByTimeseriesIsNull(  );
    // ---------------------------------------------------------------------
    // TimeSpanTimeseriesProperty queries
    // ---------------------------------------------------------------------
    TimeSpanTimeseriesPropertyObject getTimeSpanTimeseriesPropertyById( Guid id );
    List<TimeSpanTimeseriesPropertyObject> getTimeSpanTimeseriesPropertyCollection( );
    List<TimeSpanTimeseriesPropertyObject> getTimeSpanTimeseriesPropertyCollectionByElement( Guid element );
    TimeSpanTimeseriesPropertyObject getTimeSpanTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
    List<TimeSpanTimeseriesPropertyObject> getTimeSpanTimeseriesPropertyCollectionByDefinition( Guid definition );
    List<TimeSpanTimeseriesPropertyObject> getTimeSpanTimeseriesPropertyCollectionByTimeseries( Guid timeseries );
    List<TimeSpanTimeseriesPropertyObject> qetTimeSpanTimeseriesPropertyCollectionByTimeseriesIsNull(  );
    // ---------------------------------------------------------------------
    // UInt16TimeseriesProperty queries
    // ---------------------------------------------------------------------
    UInt16TimeseriesPropertyObject getUInt16TimeseriesPropertyById( Guid id );
    List<UInt16TimeseriesPropertyObject> getUInt16TimeseriesPropertyCollection( );
    List<UInt16TimeseriesPropertyObject> getUInt16TimeseriesPropertyCollectionByElement( Guid element );
    UInt16TimeseriesPropertyObject getUInt16TimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
    List<UInt16TimeseriesPropertyObject> getUInt16TimeseriesPropertyCollectionByDefinition( Guid definition );
    List<UInt16TimeseriesPropertyObject> getUInt16TimeseriesPropertyCollectionByTimeseries( Guid timeseries );
    List<UInt16TimeseriesPropertyObject> qetUInt16TimeseriesPropertyCollectionByTimeseriesIsNull(  );
    // ---------------------------------------------------------------------
    // UInt32TimeseriesProperty queries
    // ---------------------------------------------------------------------
    UInt32TimeseriesPropertyObject getUInt32TimeseriesPropertyById( Guid id );
    List<UInt32TimeseriesPropertyObject> getUInt32TimeseriesPropertyCollection( );
    List<UInt32TimeseriesPropertyObject> getUInt32TimeseriesPropertyCollectionByElement( Guid element );
    UInt32TimeseriesPropertyObject getUInt32TimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
    List<UInt32TimeseriesPropertyObject> getUInt32TimeseriesPropertyCollectionByDefinition( Guid definition );
    List<UInt32TimeseriesPropertyObject> getUInt32TimeseriesPropertyCollectionByTimeseries( Guid timeseries );
    List<UInt32TimeseriesPropertyObject> qetUInt32TimeseriesPropertyCollectionByTimeseriesIsNull(  );
    // ---------------------------------------------------------------------
    // UInt64TimeseriesProperty queries
    // ---------------------------------------------------------------------
    UInt64TimeseriesPropertyObject getUInt64TimeseriesPropertyById( Guid id );
    List<UInt64TimeseriesPropertyObject> getUInt64TimeseriesPropertyCollection( );
    List<UInt64TimeseriesPropertyObject> getUInt64TimeseriesPropertyCollectionByElement( Guid element );
    UInt64TimeseriesPropertyObject getUInt64TimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
    List<UInt64TimeseriesPropertyObject> getUInt64TimeseriesPropertyCollectionByDefinition( Guid definition );
    List<UInt64TimeseriesPropertyObject> getUInt64TimeseriesPropertyCollectionByTimeseries( Guid timeseries );
    List<UInt64TimeseriesPropertyObject> qetUInt64TimeseriesPropertyCollectionByTimeseriesIsNull(  );
    // ---------------------------------------------------------------------
    // TimeSpanProperty queries
    // ---------------------------------------------------------------------
    TimeSpanPropertyObject getTimeSpanPropertyById( Guid id );
    List<TimeSpanPropertyObject> getTimeSpanPropertyCollection( );
    List<TimeSpanPropertyObject> getTimeSpanPropertyCollectionByElement( Guid element );
    TimeSpanPropertyObject getTimeSpanPropertyByElementAndDefinition( Guid element, Guid definition );
    List<TimeSpanPropertyObject> getTimeSpanPropertyCollectionByDefinition( Guid definition );
    // ---------------------------------------------------------------------
    // UInt16Property queries
    // ---------------------------------------------------------------------
    UInt16PropertyObject getUInt16PropertyById( Guid id );
    List<UInt16PropertyObject> getUInt16PropertyCollection( );
    List<UInt16PropertyObject> getUInt16PropertyCollectionByElement( Guid element );
    UInt16PropertyObject getUInt16PropertyByElementAndDefinition( Guid element, Guid definition );
    List<UInt16PropertyObject> getUInt16PropertyCollectionByDefinition( Guid definition );
    // ---------------------------------------------------------------------
    // UInt32Property queries
    // ---------------------------------------------------------------------
    UInt32PropertyObject getUInt32PropertyById( Guid id );
    List<UInt32PropertyObject> getUInt32PropertyCollection( );
    List<UInt32PropertyObject> getUInt32PropertyCollectionByElement( Guid element );
    UInt32PropertyObject getUInt32PropertyByElementAndDefinition( Guid element, Guid definition );
    List<UInt32PropertyObject> getUInt32PropertyCollectionByDefinition( Guid definition );
    // ---------------------------------------------------------------------
    // UInt64Property queries
    // ---------------------------------------------------------------------
    UInt64PropertyObject getUInt64PropertyById( Guid id );
    List<UInt64PropertyObject> getUInt64PropertyCollection( );
    List<UInt64PropertyObject> getUInt64PropertyCollectionByElement( Guid element );
    UInt64PropertyObject getUInt64PropertyByElementAndDefinition( Guid element, Guid definition );
    List<UInt64PropertyObject> getUInt64PropertyCollectionByDefinition( Guid definition );
    // ---------------------------------------------------------------------
    // PropertyDefinition queries
    // ---------------------------------------------------------------------
    PropertyDefinitionObject getPropertyDefinitionById( Guid id );
    List<PropertyDefinitionObject> getPropertyDefinitionCollection( );
    List<PropertyDefinitionObject> getPropertyDefinitionCollectionByElementType( Guid elementType );
    PropertyDefinitionObject getPropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // BinaryPropertyDefinition queries
    // ---------------------------------------------------------------------
    BinaryPropertyDefinitionObject getBinaryPropertyDefinitionById( Guid id );
    List<BinaryPropertyDefinitionObject> getBinaryPropertyDefinitionCollection( );
    List<BinaryPropertyDefinitionObject> getBinaryPropertyDefinitionCollectionByElementType( Guid elementType );
    BinaryPropertyDefinitionObject getBinaryPropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // BooleanPropertyDefinition queries
    // ---------------------------------------------------------------------
    BooleanPropertyDefinitionObject getBooleanPropertyDefinitionById( Guid id );
    List<BooleanPropertyDefinitionObject> getBooleanPropertyDefinitionCollection( );
    List<BooleanPropertyDefinitionObject> getBooleanPropertyDefinitionCollectionByElementType( Guid elementType );
    BooleanPropertyDefinitionObject getBooleanPropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // BytePropertyDefinition queries
    // ---------------------------------------------------------------------
    BytePropertyDefinitionObject getBytePropertyDefinitionById( Guid id );
    List<BytePropertyDefinitionObject> getBytePropertyDefinitionCollection( );
    List<BytePropertyDefinitionObject> getBytePropertyDefinitionCollectionByElementType( Guid elementType );
    BytePropertyDefinitionObject getBytePropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // DateTimePropertyDefinition queries
    // ---------------------------------------------------------------------
    DateTimePropertyDefinitionObject getDateTimePropertyDefinitionById( Guid id );
    List<DateTimePropertyDefinitionObject> getDateTimePropertyDefinitionCollection( );
    List<DateTimePropertyDefinitionObject> getDateTimePropertyDefinitionCollectionByElementType( Guid elementType );
    DateTimePropertyDefinitionObject getDateTimePropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // DoublePropertyDefinition queries
    // ---------------------------------------------------------------------
    DoublePropertyDefinitionObject getDoublePropertyDefinitionById( Guid id );
    List<DoublePropertyDefinitionObject> getDoublePropertyDefinitionCollection( );
    List<DoublePropertyDefinitionObject> getDoublePropertyDefinitionCollectionByElementType( Guid elementType );
    DoublePropertyDefinitionObject getDoublePropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // GuidPropertyDefinition queries
    // ---------------------------------------------------------------------
    GuidPropertyDefinitionObject getGuidPropertyDefinitionById( Guid id );
    List<GuidPropertyDefinitionObject> getGuidPropertyDefinitionCollection( );
    List<GuidPropertyDefinitionObject> getGuidPropertyDefinitionCollectionByElementType( Guid elementType );
    GuidPropertyDefinitionObject getGuidPropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // Int16PropertyDefinition queries
    // ---------------------------------------------------------------------
    Int16PropertyDefinitionObject getInt16PropertyDefinitionById( Guid id );
    List<Int16PropertyDefinitionObject> getInt16PropertyDefinitionCollection( );
    List<Int16PropertyDefinitionObject> getInt16PropertyDefinitionCollectionByElementType( Guid elementType );
    Int16PropertyDefinitionObject getInt16PropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // Int32PropertyDefinition queries
    // ---------------------------------------------------------------------
    Int32PropertyDefinitionObject getInt32PropertyDefinitionById( Guid id );
    List<Int32PropertyDefinitionObject> getInt32PropertyDefinitionCollection( );
    List<Int32PropertyDefinitionObject> getInt32PropertyDefinitionCollectionByElementType( Guid elementType );
    Int32PropertyDefinitionObject getInt32PropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // Int64PropertyDefinition queries
    // ---------------------------------------------------------------------
    Int64PropertyDefinitionObject getInt64PropertyDefinitionById( Guid id );
    List<Int64PropertyDefinitionObject> getInt64PropertyDefinitionCollection( );
    List<Int64PropertyDefinitionObject> getInt64PropertyDefinitionCollectionByElementType( Guid elementType );
    Int64PropertyDefinitionObject getInt64PropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // ReferencePropertyDefinition queries
    // ---------------------------------------------------------------------
    ReferencePropertyDefinitionObject getReferencePropertyDefinitionById( Guid id );
    List<ReferencePropertyDefinitionObject> getReferencePropertyDefinitionCollection( );
    List<ReferencePropertyDefinitionObject> getReferencePropertyDefinitionCollectionByElementType( Guid elementType );
    ReferencePropertyDefinitionObject getReferencePropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    List<ReferencePropertyDefinitionObject> getReferencePropertyDefinitionCollectionByDefaultValue( Guid defaultValue );
    List<ReferencePropertyDefinitionObject> qetReferencePropertyDefinitionCollectionByDefaultValueIsNull(  );
    List<ReferencePropertyDefinitionObject> getReferencePropertyDefinitionCollectionByReferencedElementType( Guid referencedElementType );
    List<ReferencePropertyDefinitionObject> qetReferencePropertyDefinitionCollectionByReferencedElementTypeIsNull(  );
    // ---------------------------------------------------------------------
    // SBytePropertyDefinition queries
    // ---------------------------------------------------------------------
    SBytePropertyDefinitionObject getSBytePropertyDefinitionById( Guid id );
    List<SBytePropertyDefinitionObject> getSBytePropertyDefinitionCollection( );
    List<SBytePropertyDefinitionObject> getSBytePropertyDefinitionCollectionByElementType( Guid elementType );
    SBytePropertyDefinitionObject getSBytePropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // SinglePropertyDefinition queries
    // ---------------------------------------------------------------------
    SinglePropertyDefinitionObject getSinglePropertyDefinitionById( Guid id );
    List<SinglePropertyDefinitionObject> getSinglePropertyDefinitionCollection( );
    List<SinglePropertyDefinitionObject> getSinglePropertyDefinitionCollectionByElementType( Guid elementType );
    SinglePropertyDefinitionObject getSinglePropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // StringPropertyDefinition queries
    // ---------------------------------------------------------------------
    StringPropertyDefinitionObject getStringPropertyDefinitionById( Guid id );
    List<StringPropertyDefinitionObject> getStringPropertyDefinitionCollection( );
    List<StringPropertyDefinitionObject> getStringPropertyDefinitionCollectionByElementType( Guid elementType );
    StringPropertyDefinitionObject getStringPropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // TimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    TimeseriesPropertyDefinitionObject getTimeseriesPropertyDefinitionById( Guid id );
    List<TimeseriesPropertyDefinitionObject> getTimeseriesPropertyDefinitionCollection( );
    List<TimeseriesPropertyDefinitionObject> getTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
    TimeseriesPropertyDefinitionObject getTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // BinaryTimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    BinaryTimeseriesPropertyDefinitionObject getBinaryTimeseriesPropertyDefinitionById( Guid id );
    List<BinaryTimeseriesPropertyDefinitionObject> getBinaryTimeseriesPropertyDefinitionCollection( );
    List<BinaryTimeseriesPropertyDefinitionObject> getBinaryTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
    BinaryTimeseriesPropertyDefinitionObject getBinaryTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // BooleanTimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    BooleanTimeseriesPropertyDefinitionObject getBooleanTimeseriesPropertyDefinitionById( Guid id );
    List<BooleanTimeseriesPropertyDefinitionObject> getBooleanTimeseriesPropertyDefinitionCollection( );
    List<BooleanTimeseriesPropertyDefinitionObject> getBooleanTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
    BooleanTimeseriesPropertyDefinitionObject getBooleanTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // ByteTimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    ByteTimeseriesPropertyDefinitionObject getByteTimeseriesPropertyDefinitionById( Guid id );
    List<ByteTimeseriesPropertyDefinitionObject> getByteTimeseriesPropertyDefinitionCollection( );
    List<ByteTimeseriesPropertyDefinitionObject> getByteTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
    ByteTimeseriesPropertyDefinitionObject getByteTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // DateTimeTimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    DateTimeTimeseriesPropertyDefinitionObject getDateTimeTimeseriesPropertyDefinitionById( Guid id );
    List<DateTimeTimeseriesPropertyDefinitionObject> getDateTimeTimeseriesPropertyDefinitionCollection( );
    List<DateTimeTimeseriesPropertyDefinitionObject> getDateTimeTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
    DateTimeTimeseriesPropertyDefinitionObject getDateTimeTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // DoubleTimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    DoubleTimeseriesPropertyDefinitionObject getDoubleTimeseriesPropertyDefinitionById( Guid id );
    List<DoubleTimeseriesPropertyDefinitionObject> getDoubleTimeseriesPropertyDefinitionCollection( );
    List<DoubleTimeseriesPropertyDefinitionObject> getDoubleTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
    DoubleTimeseriesPropertyDefinitionObject getDoubleTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // GuidTimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    GuidTimeseriesPropertyDefinitionObject getGuidTimeseriesPropertyDefinitionById( Guid id );
    List<GuidTimeseriesPropertyDefinitionObject> getGuidTimeseriesPropertyDefinitionCollection( );
    List<GuidTimeseriesPropertyDefinitionObject> getGuidTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
    GuidTimeseriesPropertyDefinitionObject getGuidTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // Int16TimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    Int16TimeseriesPropertyDefinitionObject getInt16TimeseriesPropertyDefinitionById( Guid id );
    List<Int16TimeseriesPropertyDefinitionObject> getInt16TimeseriesPropertyDefinitionCollection( );
    List<Int16TimeseriesPropertyDefinitionObject> getInt16TimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
    Int16TimeseriesPropertyDefinitionObject getInt16TimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // Int32TimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    Int32TimeseriesPropertyDefinitionObject getInt32TimeseriesPropertyDefinitionById( Guid id );
    List<Int32TimeseriesPropertyDefinitionObject> getInt32TimeseriesPropertyDefinitionCollection( );
    List<Int32TimeseriesPropertyDefinitionObject> getInt32TimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
    Int32TimeseriesPropertyDefinitionObject getInt32TimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // Int64TimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    Int64TimeseriesPropertyDefinitionObject getInt64TimeseriesPropertyDefinitionById( Guid id );
    List<Int64TimeseriesPropertyDefinitionObject> getInt64TimeseriesPropertyDefinitionCollection( );
    List<Int64TimeseriesPropertyDefinitionObject> getInt64TimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
    Int64TimeseriesPropertyDefinitionObject getInt64TimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // ReferenceTimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    ReferenceTimeseriesPropertyDefinitionObject getReferenceTimeseriesPropertyDefinitionById( Guid id );
    List<ReferenceTimeseriesPropertyDefinitionObject> getReferenceTimeseriesPropertyDefinitionCollection( );
    List<ReferenceTimeseriesPropertyDefinitionObject> getReferenceTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
    ReferenceTimeseriesPropertyDefinitionObject getReferenceTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    List<ReferenceTimeseriesPropertyDefinitionObject> getReferenceTimeseriesPropertyDefinitionCollectionByReferencedElementType( Guid referencedElementType );
    List<ReferenceTimeseriesPropertyDefinitionObject> qetReferenceTimeseriesPropertyDefinitionCollectionByReferencedElementTypeIsNull(  );
    // ---------------------------------------------------------------------
    // SByteTimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    SByteTimeseriesPropertyDefinitionObject getSByteTimeseriesPropertyDefinitionById( Guid id );
    List<SByteTimeseriesPropertyDefinitionObject> getSByteTimeseriesPropertyDefinitionCollection( );
    List<SByteTimeseriesPropertyDefinitionObject> getSByteTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
    SByteTimeseriesPropertyDefinitionObject getSByteTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // SingleTimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    SingleTimeseriesPropertyDefinitionObject getSingleTimeseriesPropertyDefinitionById( Guid id );
    List<SingleTimeseriesPropertyDefinitionObject> getSingleTimeseriesPropertyDefinitionCollection( );
    List<SingleTimeseriesPropertyDefinitionObject> getSingleTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
    SingleTimeseriesPropertyDefinitionObject getSingleTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // StringTimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    StringTimeseriesPropertyDefinitionObject getStringTimeseriesPropertyDefinitionById( Guid id );
    List<StringTimeseriesPropertyDefinitionObject> getStringTimeseriesPropertyDefinitionCollection( );
    List<StringTimeseriesPropertyDefinitionObject> getStringTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
    StringTimeseriesPropertyDefinitionObject getStringTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // TimeSpanTimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    TimeSpanTimeseriesPropertyDefinitionObject getTimeSpanTimeseriesPropertyDefinitionById( Guid id );
    List<TimeSpanTimeseriesPropertyDefinitionObject> getTimeSpanTimeseriesPropertyDefinitionCollection( );
    List<TimeSpanTimeseriesPropertyDefinitionObject> getTimeSpanTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
    TimeSpanTimeseriesPropertyDefinitionObject getTimeSpanTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // UInt16TimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    UInt16TimeseriesPropertyDefinitionObject getUInt16TimeseriesPropertyDefinitionById( Guid id );
    List<UInt16TimeseriesPropertyDefinitionObject> getUInt16TimeseriesPropertyDefinitionCollection( );
    List<UInt16TimeseriesPropertyDefinitionObject> getUInt16TimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
    UInt16TimeseriesPropertyDefinitionObject getUInt16TimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // UInt32TimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    UInt32TimeseriesPropertyDefinitionObject getUInt32TimeseriesPropertyDefinitionById( Guid id );
    List<UInt32TimeseriesPropertyDefinitionObject> getUInt32TimeseriesPropertyDefinitionCollection( );
    List<UInt32TimeseriesPropertyDefinitionObject> getUInt32TimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
    UInt32TimeseriesPropertyDefinitionObject getUInt32TimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // UInt64TimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    UInt64TimeseriesPropertyDefinitionObject getUInt64TimeseriesPropertyDefinitionById( Guid id );
    List<UInt64TimeseriesPropertyDefinitionObject> getUInt64TimeseriesPropertyDefinitionCollection( );
    List<UInt64TimeseriesPropertyDefinitionObject> getUInt64TimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
    UInt64TimeseriesPropertyDefinitionObject getUInt64TimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // TimeSpanPropertyDefinition queries
    // ---------------------------------------------------------------------
    TimeSpanPropertyDefinitionObject getTimeSpanPropertyDefinitionById( Guid id );
    List<TimeSpanPropertyDefinitionObject> getTimeSpanPropertyDefinitionCollection( );
    List<TimeSpanPropertyDefinitionObject> getTimeSpanPropertyDefinitionCollectionByElementType( Guid elementType );
    TimeSpanPropertyDefinitionObject getTimeSpanPropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // UInt16PropertyDefinition queries
    // ---------------------------------------------------------------------
    UInt16PropertyDefinitionObject getUInt16PropertyDefinitionById( Guid id );
    List<UInt16PropertyDefinitionObject> getUInt16PropertyDefinitionCollection( );
    List<UInt16PropertyDefinitionObject> getUInt16PropertyDefinitionCollectionByElementType( Guid elementType );
    UInt16PropertyDefinitionObject getUInt16PropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // UInt32PropertyDefinition queries
    // ---------------------------------------------------------------------
    UInt32PropertyDefinitionObject getUInt32PropertyDefinitionById( Guid id );
    List<UInt32PropertyDefinitionObject> getUInt32PropertyDefinitionCollection( );
    List<UInt32PropertyDefinitionObject> getUInt32PropertyDefinitionCollectionByElementType( Guid elementType );
    UInt32PropertyDefinitionObject getUInt32PropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // UInt64PropertyDefinition queries
    // ---------------------------------------------------------------------
    UInt64PropertyDefinitionObject getUInt64PropertyDefinitionById( Guid id );
    List<UInt64PropertyDefinitionObject> getUInt64PropertyDefinitionCollection( );
    List<UInt64PropertyDefinitionObject> getUInt64PropertyDefinitionCollectionByElementType( Guid elementType );
    UInt64PropertyDefinitionObject getUInt64PropertyDefinitionByElementTypeAndName( Guid elementType, String name );
    // ---------------------------------------------------------------------
    // RadarAlarmStatus queries
    // ---------------------------------------------------------------------
    RadarAlarmStatusObject getRadarAlarmStatusById( Guid id );
    List<RadarAlarmStatusObject> getRadarAlarmStatusCollection( );
    List<RadarAlarmStatusObject> getRadarAlarmStatusCollectionByRadar( Guid radar );
    RadarAlarmStatusObject getRadarAlarmStatusByRadarAndTimestamp( Guid radar, DateTime timestamp );
    RadarAlarmStatusObject getRadarAlarmStatusByRadarAtTimestamp( Guid radar, DateTime timestamp );
    List<RadarAlarmStatusObject> getRadarAlarmStatusByRadarFromTimestamp( Guid radar, DateTime timestamp );
    List<RadarAlarmStatusObject> getRadarAlarmStatusByRadarUntilTimestamp( Guid radar, DateTime timestamp );
    List<RadarAlarmStatusObject> getRadarAlarmStatusByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp );
    List<RadarAlarmStatusObject> getRadarAlarmStatusCollectionByTimestamp( DateTime timestamp );
    List<RadarAlarmStatusObject> getRadarAlarmStatusCollectionAtTimestamp( DateTime timestamp );
    List<RadarAlarmStatusObject> getRadarAlarmStatusCollectionFromTimestamp( DateTime timestamp );
    List<RadarAlarmStatusObject> getRadarAlarmStatusCollectionUntilTimestamp( DateTime timestamp );
    List<RadarAlarmStatusObject> getRadarAlarmStatusCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // RadarCommand queries
    // ---------------------------------------------------------------------
    RadarCommandObject getRadarCommandById( Guid id );
    List<RadarCommandObject> getRadarCommandCollection( );
    List<RadarCommandObject> getRadarCommandCollectionByRadar( Guid radar );
    List<RadarCommandObject> getRadarCommandCollectionByRadarAndTimestamp( Guid radar, DateTime timestamp );
    List<RadarCommandObject> getRadarCommandCollectionByRadarAtTimestamp( Guid radar, DateTime timestamp );
    List<RadarCommandObject> getRadarCommandCollectionByRadarFromTimestamp( Guid radar, DateTime timestamp );
    List<RadarCommandObject> getRadarCommandCollectionByRadarUntilTimestamp( Guid radar, DateTime timestamp );
    List<RadarCommandObject> getRadarCommandCollectionByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp );
    List<RadarCommandObject> getRadarCommandCollectionByTimestamp( DateTime timestamp );
    List<RadarCommandObject> getRadarCommandCollectionAtTimestamp( DateTime timestamp );
    List<RadarCommandObject> getRadarCommandCollectionFromTimestamp( DateTime timestamp );
    List<RadarCommandObject> getRadarCommandCollectionUntilTimestamp( DateTime timestamp );
    List<RadarCommandObject> getRadarCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<RadarCommandObject> getRadarCommandCollectionByReply( Guid reply );
    List<RadarCommandObject> qetRadarCommandCollectionByReplyIsNull(  );
    // ---------------------------------------------------------------------
    // RadarCommandGetStatus queries
    // ---------------------------------------------------------------------
    RadarCommandGetStatusObject getRadarCommandGetStatusById( Guid id );
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollection( );
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollectionByRadar( Guid radar );
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollectionByRadarAndTimestamp( Guid radar, DateTime timestamp );
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollectionByRadarAtTimestamp( Guid radar, DateTime timestamp );
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollectionByRadarFromTimestamp( Guid radar, DateTime timestamp );
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollectionByRadarUntilTimestamp( Guid radar, DateTime timestamp );
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollectionByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp );
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollectionByTimestamp( DateTime timestamp );
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollectionAtTimestamp( DateTime timestamp );
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollectionFromTimestamp( DateTime timestamp );
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollectionUntilTimestamp( DateTime timestamp );
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollectionByReply( Guid reply );
    List<RadarCommandGetStatusObject> qetRadarCommandGetStatusCollectionByReplyIsNull(  );
    // ---------------------------------------------------------------------
    // RadarCommandReply queries
    // ---------------------------------------------------------------------
    RadarCommandReplyObject getRadarCommandReplyById( Guid id );
    List<RadarCommandReplyObject> getRadarCommandReplyCollection( );
    List<RadarCommandReplyObject> getRadarCommandReplyCollectionByRadar( Guid radar );
    List<RadarCommandReplyObject> getRadarCommandReplyCollectionByRadarAndTimestamp( Guid radar, DateTime timestamp );
    List<RadarCommandReplyObject> getRadarCommandReplyCollectionByRadarAtTimestamp( Guid radar, DateTime timestamp );
    List<RadarCommandReplyObject> getRadarCommandReplyCollectionByRadarFromTimestamp( Guid radar, DateTime timestamp );
    List<RadarCommandReplyObject> getRadarCommandReplyCollectionByRadarUntilTimestamp( Guid radar, DateTime timestamp );
    List<RadarCommandReplyObject> getRadarCommandReplyCollectionByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp );
    List<RadarCommandReplyObject> getRadarCommandReplyCollectionByTimestamp( DateTime timestamp );
    List<RadarCommandReplyObject> getRadarCommandReplyCollectionAtTimestamp( DateTime timestamp );
    List<RadarCommandReplyObject> getRadarCommandReplyCollectionFromTimestamp( DateTime timestamp );
    List<RadarCommandReplyObject> getRadarCommandReplyCollectionUntilTimestamp( DateTime timestamp );
    List<RadarCommandReplyObject> getRadarCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    RadarCommandReplyObject getRadarCommandReplyByCommand( Guid command );
    List<RadarCommandReplyObject> qetRadarCommandReplyCollectionByCommandIsNull(  );
    // ---------------------------------------------------------------------
    // RadarCommandReplyGetStatus queries
    // ---------------------------------------------------------------------
    RadarCommandReplyGetStatusObject getRadarCommandReplyGetStatusById( Guid id );
    List<RadarCommandReplyGetStatusObject> getRadarCommandReplyGetStatusCollection( );
    List<RadarCommandReplyGetStatusObject> getRadarCommandReplyGetStatusCollectionByRadar( Guid radar );
    List<RadarCommandReplyGetStatusObject> getRadarCommandReplyGetStatusCollectionByRadarAndTimestamp( Guid radar, DateTime timestamp );
    List<RadarCommandReplyGetStatusObject> getRadarCommandReplyGetStatusCollectionByRadarAtTimestamp( Guid radar, DateTime timestamp );
    List<RadarCommandReplyGetStatusObject> getRadarCommandReplyGetStatusCollectionByRadarFromTimestamp( Guid radar, DateTime timestamp );
    List<RadarCommandReplyGetStatusObject> getRadarCommandReplyGetStatusCollectionByRadarUntilTimestamp( Guid radar, DateTime timestamp );
    List<RadarCommandReplyGetStatusObject> getRadarCommandReplyGetStatusCollectionByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp );
    List<RadarCommandReplyGetStatusObject> getRadarCommandReplyGetStatusCollectionByTimestamp( DateTime timestamp );
    List<RadarCommandReplyGetStatusObject> getRadarCommandReplyGetStatusCollectionAtTimestamp( DateTime timestamp );
    List<RadarCommandReplyGetStatusObject> getRadarCommandReplyGetStatusCollectionFromTimestamp( DateTime timestamp );
    List<RadarCommandReplyGetStatusObject> getRadarCommandReplyGetStatusCollectionUntilTimestamp( DateTime timestamp );
    List<RadarCommandReplyGetStatusObject> getRadarCommandReplyGetStatusCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    RadarCommandReplyGetStatusObject getRadarCommandReplyGetStatusByCommand( Guid command );
    List<RadarCommandReplyGetStatusObject> qetRadarCommandReplyGetStatusCollectionByCommandIsNull(  );
    // ---------------------------------------------------------------------
    // RadarConfiguration queries
    // ---------------------------------------------------------------------
    RadarConfigurationObject getRadarConfigurationById( Guid id );
    List<RadarConfigurationObject> getRadarConfigurationCollection( );
    List<RadarConfigurationObject> getRadarConfigurationCollectionByRadar( Guid radar );
    RadarConfigurationObject getRadarConfigurationByRadarAndTimestamp( Guid radar, DateTime timestamp );
    RadarConfigurationObject getRadarConfigurationByRadarAtTimestamp( Guid radar, DateTime timestamp );
    List<RadarConfigurationObject> getRadarConfigurationByRadarFromTimestamp( Guid radar, DateTime timestamp );
    List<RadarConfigurationObject> getRadarConfigurationByRadarUntilTimestamp( Guid radar, DateTime timestamp );
    List<RadarConfigurationObject> getRadarConfigurationByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp );
    List<RadarConfigurationObject> getRadarConfigurationCollectionByTimestamp( DateTime timestamp );
    List<RadarConfigurationObject> getRadarConfigurationCollectionAtTimestamp( DateTime timestamp );
    List<RadarConfigurationObject> getRadarConfigurationCollectionFromTimestamp( DateTime timestamp );
    List<RadarConfigurationObject> getRadarConfigurationCollectionUntilTimestamp( DateTime timestamp );
    List<RadarConfigurationObject> getRadarConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // RadarImage queries
    // ---------------------------------------------------------------------
    RadarImageObject getRadarImageById( Guid id );
    List<RadarImageObject> getRadarImageCollection( );
    List<RadarImageObject> getRadarImageCollectionByRadar( Guid radar );
    RadarImageObject getRadarImageByRadarAndTimestamp( Guid radar, DateTime timestamp );
    RadarImageObject getRadarImageByRadarAtTimestamp( Guid radar, DateTime timestamp );
    List<RadarImageObject> getRadarImageByRadarFromTimestamp( Guid radar, DateTime timestamp );
    List<RadarImageObject> getRadarImageByRadarUntilTimestamp( Guid radar, DateTime timestamp );
    List<RadarImageObject> getRadarImageByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp );
    List<RadarImageObject> getRadarImageCollectionByTimestamp( DateTime timestamp );
    List<RadarImageObject> getRadarImageCollectionAtTimestamp( DateTime timestamp );
    List<RadarImageObject> getRadarImageCollectionFromTimestamp( DateTime timestamp );
    List<RadarImageObject> getRadarImageCollectionUntilTimestamp( DateTime timestamp );
    List<RadarImageObject> getRadarImageCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // RadarRawTrackTable queries
    // ---------------------------------------------------------------------
    RadarRawTrackTableObject getRadarRawTrackTableById( Guid id );
    List<RadarRawTrackTableObject> getRadarRawTrackTableCollection( );
    List<RadarRawTrackTableObject> getRadarRawTrackTableCollectionByRadar( Guid radar );
    RadarRawTrackTableObject getRadarRawTrackTableByRadarAndTimestamp( Guid radar, DateTime timestamp );
    RadarRawTrackTableObject getRadarRawTrackTableByRadarAtTimestamp( Guid radar, DateTime timestamp );
    List<RadarRawTrackTableObject> getRadarRawTrackTableByRadarFromTimestamp( Guid radar, DateTime timestamp );
    List<RadarRawTrackTableObject> getRadarRawTrackTableByRadarUntilTimestamp( Guid radar, DateTime timestamp );
    List<RadarRawTrackTableObject> getRadarRawTrackTableByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp );
    List<RadarRawTrackTableObject> getRadarRawTrackTableCollectionByTimestamp( DateTime timestamp );
    List<RadarRawTrackTableObject> getRadarRawTrackTableCollectionAtTimestamp( DateTime timestamp );
    List<RadarRawTrackTableObject> getRadarRawTrackTableCollectionFromTimestamp( DateTime timestamp );
    List<RadarRawTrackTableObject> getRadarRawTrackTableCollectionUntilTimestamp( DateTime timestamp );
    List<RadarRawTrackTableObject> getRadarRawTrackTableCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // RadarStatus queries
    // ---------------------------------------------------------------------
    RadarStatusObject getRadarStatusById( Guid id );
    List<RadarStatusObject> getRadarStatusCollection( );
    List<RadarStatusObject> getRadarStatusCollectionByRadar( Guid radar );
    RadarStatusObject getRadarStatusByRadarAndTimestamp( Guid radar, DateTime timestamp );
    RadarStatusObject getRadarStatusByRadarAtTimestamp( Guid radar, DateTime timestamp );
    List<RadarStatusObject> getRadarStatusByRadarFromTimestamp( Guid radar, DateTime timestamp );
    List<RadarStatusObject> getRadarStatusByRadarUntilTimestamp( Guid radar, DateTime timestamp );
    List<RadarStatusObject> getRadarStatusByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp );
    List<RadarStatusObject> getRadarStatusCollectionByTimestamp( DateTime timestamp );
    List<RadarStatusObject> getRadarStatusCollectionAtTimestamp( DateTime timestamp );
    List<RadarStatusObject> getRadarStatusCollectionFromTimestamp( DateTime timestamp );
    List<RadarStatusObject> getRadarStatusCollectionUntilTimestamp( DateTime timestamp );
    List<RadarStatusObject> getRadarStatusCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // RadioCommand queries
    // ---------------------------------------------------------------------
    RadioCommandObject getRadioCommandById( Guid id );
    List<RadioCommandObject> getRadioCommandCollection( );
    List<RadioCommandObject> getRadioCommandCollectionByRadio( Guid radio );
    List<RadioCommandObject> getRadioCommandCollectionByRadioAndTimestamp( Guid radio, DateTime timestamp );
    List<RadioCommandObject> getRadioCommandCollectionByRadioAtTimestamp( Guid radio, DateTime timestamp );
    List<RadioCommandObject> getRadioCommandCollectionByRadioFromTimestamp( Guid radio, DateTime timestamp );
    List<RadioCommandObject> getRadioCommandCollectionByRadioUntilTimestamp( Guid radio, DateTime timestamp );
    List<RadioCommandObject> getRadioCommandCollectionByRadioOverTimestamp( Guid radio, DateTime fromTimestamp, DateTime untilTimestamp );
    List<RadioCommandObject> getRadioCommandCollectionByTimestamp( DateTime timestamp );
    List<RadioCommandObject> getRadioCommandCollectionAtTimestamp( DateTime timestamp );
    List<RadioCommandObject> getRadioCommandCollectionFromTimestamp( DateTime timestamp );
    List<RadioCommandObject> getRadioCommandCollectionUntilTimestamp( DateTime timestamp );
    List<RadioCommandObject> getRadioCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<RadioCommandObject> getRadioCommandCollectionByReply( Guid reply );
    List<RadioCommandObject> qetRadioCommandCollectionByReplyIsNull(  );
    // ---------------------------------------------------------------------
    // RadioCommandReply queries
    // ---------------------------------------------------------------------
    RadioCommandReplyObject getRadioCommandReplyById( Guid id );
    List<RadioCommandReplyObject> getRadioCommandReplyCollection( );
    List<RadioCommandReplyObject> getRadioCommandReplyCollectionByRadio( Guid radio );
    List<RadioCommandReplyObject> getRadioCommandReplyCollectionByRadioAndTimestamp( Guid radio, DateTime timestamp );
    List<RadioCommandReplyObject> getRadioCommandReplyCollectionByRadioAtTimestamp( Guid radio, DateTime timestamp );
    List<RadioCommandReplyObject> getRadioCommandReplyCollectionByRadioFromTimestamp( Guid radio, DateTime timestamp );
    List<RadioCommandReplyObject> getRadioCommandReplyCollectionByRadioUntilTimestamp( Guid radio, DateTime timestamp );
    List<RadioCommandReplyObject> getRadioCommandReplyCollectionByRadioOverTimestamp( Guid radio, DateTime fromTimestamp, DateTime untilTimestamp );
    List<RadioCommandReplyObject> getRadioCommandReplyCollectionByTimestamp( DateTime timestamp );
    List<RadioCommandReplyObject> getRadioCommandReplyCollectionAtTimestamp( DateTime timestamp );
    List<RadioCommandReplyObject> getRadioCommandReplyCollectionFromTimestamp( DateTime timestamp );
    List<RadioCommandReplyObject> getRadioCommandReplyCollectionUntilTimestamp( DateTime timestamp );
    List<RadioCommandReplyObject> getRadioCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    RadioCommandReplyObject getRadioCommandReplyByCommand( Guid command );
    List<RadioCommandReplyObject> qetRadioCommandReplyCollectionByCommandIsNull(  );
    // ---------------------------------------------------------------------
    // RadioConfiguration queries
    // ---------------------------------------------------------------------
    RadioConfigurationObject getRadioConfigurationById( Guid id );
    List<RadioConfigurationObject> getRadioConfigurationCollection( );
    List<RadioConfigurationObject> getRadioConfigurationCollectionByRadio( Guid radio );
    RadioConfigurationObject getRadioConfigurationByRadioAndTimestamp( Guid radio, DateTime timestamp );
    RadioConfigurationObject getRadioConfigurationByRadioAtTimestamp( Guid radio, DateTime timestamp );
    List<RadioConfigurationObject> getRadioConfigurationByRadioFromTimestamp( Guid radio, DateTime timestamp );
    List<RadioConfigurationObject> getRadioConfigurationByRadioUntilTimestamp( Guid radio, DateTime timestamp );
    List<RadioConfigurationObject> getRadioConfigurationByRadioOverTimestamp( Guid radio, DateTime fromTimestamp, DateTime untilTimestamp );
    List<RadioConfigurationObject> getRadioConfigurationCollectionByTimestamp( DateTime timestamp );
    List<RadioConfigurationObject> getRadioConfigurationCollectionAtTimestamp( DateTime timestamp );
    List<RadioConfigurationObject> getRadioConfigurationCollectionFromTimestamp( DateTime timestamp );
    List<RadioConfigurationObject> getRadioConfigurationCollectionUntilTimestamp( DateTime timestamp );
    List<RadioConfigurationObject> getRadioConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // RadomeCommand queries
    // ---------------------------------------------------------------------
    RadomeCommandObject getRadomeCommandById( Guid id );
    List<RadomeCommandObject> getRadomeCommandCollection( );
    List<RadomeCommandObject> getRadomeCommandCollectionByRadome( Guid radome );
    List<RadomeCommandObject> getRadomeCommandCollectionByRadomeAndTimestamp( Guid radome, DateTime timestamp );
    List<RadomeCommandObject> getRadomeCommandCollectionByRadomeAtTimestamp( Guid radome, DateTime timestamp );
    List<RadomeCommandObject> getRadomeCommandCollectionByRadomeFromTimestamp( Guid radome, DateTime timestamp );
    List<RadomeCommandObject> getRadomeCommandCollectionByRadomeUntilTimestamp( Guid radome, DateTime timestamp );
    List<RadomeCommandObject> getRadomeCommandCollectionByRadomeOverTimestamp( Guid radome, DateTime fromTimestamp, DateTime untilTimestamp );
    List<RadomeCommandObject> getRadomeCommandCollectionByTimestamp( DateTime timestamp );
    List<RadomeCommandObject> getRadomeCommandCollectionAtTimestamp( DateTime timestamp );
    List<RadomeCommandObject> getRadomeCommandCollectionFromTimestamp( DateTime timestamp );
    List<RadomeCommandObject> getRadomeCommandCollectionUntilTimestamp( DateTime timestamp );
    List<RadomeCommandObject> getRadomeCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<RadomeCommandObject> getRadomeCommandCollectionByReply( Guid reply );
    List<RadomeCommandObject> qetRadomeCommandCollectionByReplyIsNull(  );
    // ---------------------------------------------------------------------
    // RadomeCommandReply queries
    // ---------------------------------------------------------------------
    RadomeCommandReplyObject getRadomeCommandReplyById( Guid id );
    List<RadomeCommandReplyObject> getRadomeCommandReplyCollection( );
    List<RadomeCommandReplyObject> getRadomeCommandReplyCollectionByRadome( Guid radome );
    List<RadomeCommandReplyObject> getRadomeCommandReplyCollectionByRadomeAndTimestamp( Guid radome, DateTime timestamp );
    List<RadomeCommandReplyObject> getRadomeCommandReplyCollectionByRadomeAtTimestamp( Guid radome, DateTime timestamp );
    List<RadomeCommandReplyObject> getRadomeCommandReplyCollectionByRadomeFromTimestamp( Guid radome, DateTime timestamp );
    List<RadomeCommandReplyObject> getRadomeCommandReplyCollectionByRadomeUntilTimestamp( Guid radome, DateTime timestamp );
    List<RadomeCommandReplyObject> getRadomeCommandReplyCollectionByRadomeOverTimestamp( Guid radome, DateTime fromTimestamp, DateTime untilTimestamp );
    List<RadomeCommandReplyObject> getRadomeCommandReplyCollectionByTimestamp( DateTime timestamp );
    List<RadomeCommandReplyObject> getRadomeCommandReplyCollectionAtTimestamp( DateTime timestamp );
    List<RadomeCommandReplyObject> getRadomeCommandReplyCollectionFromTimestamp( DateTime timestamp );
    List<RadomeCommandReplyObject> getRadomeCommandReplyCollectionUntilTimestamp( DateTime timestamp );
    List<RadomeCommandReplyObject> getRadomeCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    RadomeCommandReplyObject getRadomeCommandReplyByCommand( Guid command );
    List<RadomeCommandReplyObject> qetRadomeCommandReplyCollectionByCommandIsNull(  );
    // ---------------------------------------------------------------------
    // RadomeConfiguration queries
    // ---------------------------------------------------------------------
    RadomeConfigurationObject getRadomeConfigurationById( Guid id );
    List<RadomeConfigurationObject> getRadomeConfigurationCollection( );
    List<RadomeConfigurationObject> getRadomeConfigurationCollectionByRadome( Guid radome );
    RadomeConfigurationObject getRadomeConfigurationByRadomeAndTimestamp( Guid radome, DateTime timestamp );
    RadomeConfigurationObject getRadomeConfigurationByRadomeAtTimestamp( Guid radome, DateTime timestamp );
    List<RadomeConfigurationObject> getRadomeConfigurationByRadomeFromTimestamp( Guid radome, DateTime timestamp );
    List<RadomeConfigurationObject> getRadomeConfigurationByRadomeUntilTimestamp( Guid radome, DateTime timestamp );
    List<RadomeConfigurationObject> getRadomeConfigurationByRadomeOverTimestamp( Guid radome, DateTime fromTimestamp, DateTime untilTimestamp );
    List<RadomeConfigurationObject> getRadomeConfigurationCollectionByTimestamp( DateTime timestamp );
    List<RadomeConfigurationObject> getRadomeConfigurationCollectionAtTimestamp( DateTime timestamp );
    List<RadomeConfigurationObject> getRadomeConfigurationCollectionFromTimestamp( DateTime timestamp );
    List<RadomeConfigurationObject> getRadomeConfigurationCollectionUntilTimestamp( DateTime timestamp );
    List<RadomeConfigurationObject> getRadomeConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // ReferenceTimeseriesValue queries
    // ---------------------------------------------------------------------
    ReferenceTimeseriesValueObject getReferenceTimeseriesValueById( Guid id );
    List<ReferenceTimeseriesValueObject> getReferenceTimeseriesValueCollection( );
    List<ReferenceTimeseriesValueObject> getReferenceTimeseriesValueCollectionByTimeseries( Guid timeseries );
    ReferenceTimeseriesValueObject getReferenceTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
    ReferenceTimeseriesValueObject getReferenceTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
    List<ReferenceTimeseriesValueObject> getReferenceTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
    List<ReferenceTimeseriesValueObject> getReferenceTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
    List<ReferenceTimeseriesValueObject> getReferenceTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
    List<ReferenceTimeseriesValueObject> getReferenceTimeseriesValueCollectionByTimestamp( DateTime timestamp );
    List<ReferenceTimeseriesValueObject> getReferenceTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
    List<ReferenceTimeseriesValueObject> getReferenceTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
    List<ReferenceTimeseriesValueObject> getReferenceTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
    List<ReferenceTimeseriesValueObject> getReferenceTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<ReferenceTimeseriesValueObject> getReferenceTimeseriesValueCollectionByValue( Guid value );
    // ---------------------------------------------------------------------
    // SByteTimeseriesValue queries
    // ---------------------------------------------------------------------
    SByteTimeseriesValueObject getSByteTimeseriesValueById( Guid id );
    List<SByteTimeseriesValueObject> getSByteTimeseriesValueCollection( );
    List<SByteTimeseriesValueObject> getSByteTimeseriesValueCollectionByTimeseries( Guid timeseries );
    SByteTimeseriesValueObject getSByteTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
    SByteTimeseriesValueObject getSByteTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
    List<SByteTimeseriesValueObject> getSByteTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
    List<SByteTimeseriesValueObject> getSByteTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
    List<SByteTimeseriesValueObject> getSByteTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
    List<SByteTimeseriesValueObject> getSByteTimeseriesValueCollectionByTimestamp( DateTime timestamp );
    List<SByteTimeseriesValueObject> getSByteTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
    List<SByteTimeseriesValueObject> getSByteTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
    List<SByteTimeseriesValueObject> getSByteTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
    List<SByteTimeseriesValueObject> getSByteTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // SecurityDomain queries
    // ---------------------------------------------------------------------
    SecurityDomainObject getSecurityDomainById( Guid id );
    List<SecurityDomainObject> getSecurityDomainCollection( );
    SecurityDomainObject getSecurityDomainByName( String name );
    // ---------------------------------------------------------------------
    // SecurityIdentifier queries
    // ---------------------------------------------------------------------
    SecurityIdentifierObject getSecurityIdentifierById( Guid id );
    List<SecurityIdentifierObject> getSecurityIdentifierCollection( );
    List<SecurityIdentifierObject> getSecurityIdentifierCollectionByDomain( Guid domain );
    SecurityIdentifierObject getSecurityIdentifierByDomainAndIdentity( Guid domain, String identity );
    // ---------------------------------------------------------------------
    // SecurityLogin queries
    // ---------------------------------------------------------------------
    SecurityLoginObject getSecurityLoginById( Guid id );
    List<SecurityLoginObject> getSecurityLoginCollection( );
    List<SecurityLoginObject> getSecurityLoginCollectionByDomain( Guid domain );
    SecurityLoginObject getSecurityLoginByDomainAndIdentity( Guid domain, String identity );
    // ---------------------------------------------------------------------
    // SecurityRole queries
    // ---------------------------------------------------------------------
    SecurityRoleObject getSecurityRoleById( Guid id );
    List<SecurityRoleObject> getSecurityRoleCollection( );
    List<SecurityRoleObject> getSecurityRoleCollectionByDomain( Guid domain );
    SecurityRoleObject getSecurityRoleByDomainAndIdentity( Guid domain, String identity );
    SecurityRoleObject getSecurityRoleByName( String name );
    // ---------------------------------------------------------------------
    // SecurityIdentifierRoleLink queries
    // ---------------------------------------------------------------------
    SecurityIdentifierRoleLinkObject getSecurityIdentifierRoleLinkById( Guid id );
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollection( );
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByMember( Guid member );
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByMemberAndStart( Guid member, DateTime start );
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByMemberAtStart( Guid member, DateTime start );
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByMemberFromStart( Guid member, DateTime start );
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByMemberUntilStart( Guid member, DateTime start );
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByMemberOverStart( Guid member, DateTime fromStart, DateTime untilStart );
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByRole( Guid role );
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByRoleAndStart( Guid role, DateTime start );
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByRoleAtStart( Guid role, DateTime start );
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByRoleFromStart( Guid role, DateTime start );
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByRoleUntilStart( Guid role, DateTime start );
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByRoleOverStart( Guid role, DateTime fromStart, DateTime untilStart );
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByStart( DateTime start );
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionAtStart( DateTime start );
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionFromStart( DateTime start );
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionUntilStart( DateTime start );
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionOverStart( DateTime fromStart, DateTime untilStart );
    // ---------------------------------------------------------------------
    // SecurityLoginSession queries
    // ---------------------------------------------------------------------
    SecurityLoginSessionObject getSecurityLoginSessionById( Guid id );
    List<SecurityLoginSessionObject> getSecurityLoginSessionCollection( );
    List<SecurityLoginSessionObject> getSecurityLoginSessionCollectionByLogin( Guid login );
    List<SecurityLoginSessionObject> getSecurityLoginSessionCollectionByLoginAndFromTime( Guid login, DateTime fromTime );
    List<SecurityLoginSessionObject> getSecurityLoginSessionCollectionByLoginAtFromTime( Guid login, DateTime fromTime );
    List<SecurityLoginSessionObject> getSecurityLoginSessionCollectionByLoginFromFromTime( Guid login, DateTime fromTime );
    List<SecurityLoginSessionObject> getSecurityLoginSessionCollectionByLoginUntilFromTime( Guid login, DateTime fromTime );
    List<SecurityLoginSessionObject> getSecurityLoginSessionCollectionByLoginOverFromTime( Guid login, DateTime fromFromTime, DateTime untilFromTime );
    List<SecurityLoginSessionObject> getSecurityLoginSessionCollectionByFromTime( DateTime fromTime );
    List<SecurityLoginSessionObject> getSecurityLoginSessionCollectionAtFromTime( DateTime fromTime );
    List<SecurityLoginSessionObject> getSecurityLoginSessionCollectionFromFromTime( DateTime fromTime );
    List<SecurityLoginSessionObject> getSecurityLoginSessionCollectionUntilFromTime( DateTime fromTime );
    List<SecurityLoginSessionObject> getSecurityLoginSessionCollectionOverFromTime( DateTime fromFromTime, DateTime untilFromTime );
    // ---------------------------------------------------------------------
    // SecurityPermission queries
    // ---------------------------------------------------------------------
    SecurityPermissionObject getSecurityPermissionById( Guid id );
    List<SecurityPermissionObject> getSecurityPermissionCollection( );
    List<SecurityPermissionObject> getSecurityPermissionCollectionByIdentifier( Guid identifier );
    List<SecurityPermissionObject> getSecurityPermissionCollectionByIdentifierAndTypeCode( Guid identifier, int typeCode );
    List<SecurityPermissionObject> getSecurityPermissionCollectionByIdentifierFromTypeCode( Guid identifier, int typeCode );
    List<SecurityPermissionObject> getSecurityPermissionCollectionByIdentifierUntilTypeCode( Guid identifier, int typeCode );
    List<SecurityPermissionObject> getSecurityPermissionCollectionByIdentifierOverTypeCode( Guid identifier, int fromTypeCode, int untilTypeCode );
    SecurityPermissionObject getSecurityPermissionByIdentifierTypeCodeAndTimestamp( Guid identifier, int typeCode, DateTime timestamp );
    SecurityPermissionObject getSecurityPermissionByIdentifierTypeCodeAtTimestamp( Guid identifier, int typeCode, DateTime timestamp );
    List<SecurityPermissionObject> getSecurityPermissionByIdentifierTypeCodeFromTimestamp( Guid identifier, int typeCode, DateTime timestamp );
    List<SecurityPermissionObject> getSecurityPermissionByIdentifierTypeCodeUntilTimestamp( Guid identifier, int typeCode, DateTime timestamp );
    List<SecurityPermissionObject> getSecurityPermissionByIdentifierTypeCodeOverTimestamp( Guid identifier, int typeCode, DateTime fromTimestamp, DateTime untilTimestamp );
    List<SecurityPermissionObject> getSecurityPermissionCollectionByTimestamp( DateTime timestamp );
    List<SecurityPermissionObject> getSecurityPermissionCollectionAtTimestamp( DateTime timestamp );
    List<SecurityPermissionObject> getSecurityPermissionCollectionFromTimestamp( DateTime timestamp );
    List<SecurityPermissionObject> getSecurityPermissionCollectionUntilTimestamp( DateTime timestamp );
    List<SecurityPermissionObject> getSecurityPermissionCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // SingleTimeseriesValue queries
    // ---------------------------------------------------------------------
    SingleTimeseriesValueObject getSingleTimeseriesValueById( Guid id );
    List<SingleTimeseriesValueObject> getSingleTimeseriesValueCollection( );
    List<SingleTimeseriesValueObject> getSingleTimeseriesValueCollectionByTimeseries( Guid timeseries );
    SingleTimeseriesValueObject getSingleTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
    SingleTimeseriesValueObject getSingleTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
    List<SingleTimeseriesValueObject> getSingleTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
    List<SingleTimeseriesValueObject> getSingleTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
    List<SingleTimeseriesValueObject> getSingleTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
    List<SingleTimeseriesValueObject> getSingleTimeseriesValueCollectionByTimestamp( DateTime timestamp );
    List<SingleTimeseriesValueObject> getSingleTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
    List<SingleTimeseriesValueObject> getSingleTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
    List<SingleTimeseriesValueObject> getSingleTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
    List<SingleTimeseriesValueObject> getSingleTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // StringTimeseriesValue queries
    // ---------------------------------------------------------------------
    StringTimeseriesValueObject getStringTimeseriesValueById( Guid id );
    List<StringTimeseriesValueObject> getStringTimeseriesValueCollection( );
    List<StringTimeseriesValueObject> getStringTimeseriesValueCollectionByTimeseries( Guid timeseries );
    StringTimeseriesValueObject getStringTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
    StringTimeseriesValueObject getStringTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
    List<StringTimeseriesValueObject> getStringTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
    List<StringTimeseriesValueObject> getStringTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
    List<StringTimeseriesValueObject> getStringTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
    List<StringTimeseriesValueObject> getStringTimeseriesValueCollectionByTimestamp( DateTime timestamp );
    List<StringTimeseriesValueObject> getStringTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
    List<StringTimeseriesValueObject> getStringTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
    List<StringTimeseriesValueObject> getStringTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
    List<StringTimeseriesValueObject> getStringTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // TimeseriesCatalogElement queries
    // ---------------------------------------------------------------------
    TimeseriesCatalogElementObject getTimeseriesCatalogElementById( Guid id );
    List<TimeseriesCatalogElementObject> getTimeseriesCatalogElementCollection( );
    List<TimeseriesCatalogElementObject> getTimeseriesCatalogElementCollectionByCatalog( Guid catalog );
    List<TimeseriesCatalogElementObject> qetTimeseriesCatalogElementCollectionByCatalogIsNull(  );
    TimeseriesCatalogElementObject getTimeseriesCatalogElementByCatalogAndName( Guid catalog, String name );
    List<TimeseriesCatalogElementObject> qetTimeseriesCatalogElementCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // Timeseries queries
    // ---------------------------------------------------------------------
    TimeseriesObject getTimeseriesById( Guid id );
    List<TimeseriesObject> getTimeseriesCollection( );
    List<TimeseriesObject> getTimeseriesCollectionByCatalog( Guid catalog );
    List<TimeseriesObject> qetTimeseriesCollectionByCatalogIsNull(  );
    TimeseriesObject getTimeseriesByCatalogAndName( Guid catalog, String name );
    List<TimeseriesObject> qetTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // BinaryTimeseries queries
    // ---------------------------------------------------------------------
    BinaryTimeseriesObject getBinaryTimeseriesById( Guid id );
    List<BinaryTimeseriesObject> getBinaryTimeseriesCollection( );
    List<BinaryTimeseriesObject> getBinaryTimeseriesCollectionByCatalog( Guid catalog );
    List<BinaryTimeseriesObject> qetBinaryTimeseriesCollectionByCatalogIsNull(  );
    BinaryTimeseriesObject getBinaryTimeseriesByCatalogAndName( Guid catalog, String name );
    List<BinaryTimeseriesObject> qetBinaryTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // BooleanTimeseries queries
    // ---------------------------------------------------------------------
    BooleanTimeseriesObject getBooleanTimeseriesById( Guid id );
    List<BooleanTimeseriesObject> getBooleanTimeseriesCollection( );
    List<BooleanTimeseriesObject> getBooleanTimeseriesCollectionByCatalog( Guid catalog );
    List<BooleanTimeseriesObject> qetBooleanTimeseriesCollectionByCatalogIsNull(  );
    BooleanTimeseriesObject getBooleanTimeseriesByCatalogAndName( Guid catalog, String name );
    List<BooleanTimeseriesObject> qetBooleanTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // AisAidToNavigationOffPositionTimeseries queries
    // ---------------------------------------------------------------------
    AisAidToNavigationOffPositionTimeseriesObject getAisAidToNavigationOffPositionTimeseriesById( Guid id );
    List<AisAidToNavigationOffPositionTimeseriesObject> getAisAidToNavigationOffPositionTimeseriesCollection( );
    List<AisAidToNavigationOffPositionTimeseriesObject> getAisAidToNavigationOffPositionTimeseriesCollectionByCatalog( Guid catalog );
    List<AisAidToNavigationOffPositionTimeseriesObject> qetAisAidToNavigationOffPositionTimeseriesCollectionByCatalogIsNull(  );
    AisAidToNavigationOffPositionTimeseriesObject getAisAidToNavigationOffPositionTimeseriesByCatalogAndName( Guid catalog, String name );
    List<AisAidToNavigationOffPositionTimeseriesObject> qetAisAidToNavigationOffPositionTimeseriesCollectionByCatalogIsNullAndName( String name );
    List<AisAidToNavigationOffPositionTimeseriesObject> getAisAidToNavigationOffPositionTimeseriesCollectionByAidToNavigation( Guid aidToNavigation );
    List<AisAidToNavigationOffPositionTimeseriesObject> qetAisAidToNavigationOffPositionTimeseriesCollectionByAidToNavigationIsNull(  );
    // ---------------------------------------------------------------------
    // DeviceEnabledTimeseries queries
    // ---------------------------------------------------------------------
    DeviceEnabledTimeseriesObject getDeviceEnabledTimeseriesById( Guid id );
    List<DeviceEnabledTimeseriesObject> getDeviceEnabledTimeseriesCollection( );
    List<DeviceEnabledTimeseriesObject> getDeviceEnabledTimeseriesCollectionByCatalog( Guid catalog );
    List<DeviceEnabledTimeseriesObject> qetDeviceEnabledTimeseriesCollectionByCatalogIsNull(  );
    DeviceEnabledTimeseriesObject getDeviceEnabledTimeseriesByCatalogAndName( Guid catalog, String name );
    List<DeviceEnabledTimeseriesObject> qetDeviceEnabledTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // RadarAutomaticSensitivityTimeControlTimeseries queries
    // ---------------------------------------------------------------------
    RadarAutomaticSensitivityTimeControlTimeseriesObject getRadarAutomaticSensitivityTimeControlTimeseriesById( Guid id );
    List<RadarAutomaticSensitivityTimeControlTimeseriesObject> getRadarAutomaticSensitivityTimeControlTimeseriesCollection( );
    List<RadarAutomaticSensitivityTimeControlTimeseriesObject> getRadarAutomaticSensitivityTimeControlTimeseriesCollectionByCatalog( Guid catalog );
    List<RadarAutomaticSensitivityTimeControlTimeseriesObject> qetRadarAutomaticSensitivityTimeControlTimeseriesCollectionByCatalogIsNull(  );
    RadarAutomaticSensitivityTimeControlTimeseriesObject getRadarAutomaticSensitivityTimeControlTimeseriesByCatalogAndName( Guid catalog, String name );
    List<RadarAutomaticSensitivityTimeControlTimeseriesObject> qetRadarAutomaticSensitivityTimeControlTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // RadarBlankSector1Timeseries queries
    // ---------------------------------------------------------------------
    RadarBlankSector1TimeseriesObject getRadarBlankSector1TimeseriesById( Guid id );
    List<RadarBlankSector1TimeseriesObject> getRadarBlankSector1TimeseriesCollection( );
    List<RadarBlankSector1TimeseriesObject> getRadarBlankSector1TimeseriesCollectionByCatalog( Guid catalog );
    List<RadarBlankSector1TimeseriesObject> qetRadarBlankSector1TimeseriesCollectionByCatalogIsNull(  );
    RadarBlankSector1TimeseriesObject getRadarBlankSector1TimeseriesByCatalogAndName( Guid catalog, String name );
    List<RadarBlankSector1TimeseriesObject> qetRadarBlankSector1TimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // RadarBlankSector2Timeseries queries
    // ---------------------------------------------------------------------
    RadarBlankSector2TimeseriesObject getRadarBlankSector2TimeseriesById( Guid id );
    List<RadarBlankSector2TimeseriesObject> getRadarBlankSector2TimeseriesCollection( );
    List<RadarBlankSector2TimeseriesObject> getRadarBlankSector2TimeseriesCollectionByCatalog( Guid catalog );
    List<RadarBlankSector2TimeseriesObject> qetRadarBlankSector2TimeseriesCollectionByCatalogIsNull(  );
    RadarBlankSector2TimeseriesObject getRadarBlankSector2TimeseriesByCatalogAndName( Guid catalog, String name );
    List<RadarBlankSector2TimeseriesObject> qetRadarBlankSector2TimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // RadarEnableAutomaticFrequencyControlTimeseries queries
    // ---------------------------------------------------------------------
    RadarEnableAutomaticFrequencyControlTimeseriesObject getRadarEnableAutomaticFrequencyControlTimeseriesById( Guid id );
    List<RadarEnableAutomaticFrequencyControlTimeseriesObject> getRadarEnableAutomaticFrequencyControlTimeseriesCollection( );
    List<RadarEnableAutomaticFrequencyControlTimeseriesObject> getRadarEnableAutomaticFrequencyControlTimeseriesCollectionByCatalog( Guid catalog );
    List<RadarEnableAutomaticFrequencyControlTimeseriesObject> qetRadarEnableAutomaticFrequencyControlTimeseriesCollectionByCatalogIsNull(  );
    RadarEnableAutomaticFrequencyControlTimeseriesObject getRadarEnableAutomaticFrequencyControlTimeseriesByCatalogAndName( Guid catalog, String name );
    List<RadarEnableAutomaticFrequencyControlTimeseriesObject> qetRadarEnableAutomaticFrequencyControlTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // RadarEnableFastTimeConstantTimeseries queries
    // ---------------------------------------------------------------------
    RadarEnableFastTimeConstantTimeseriesObject getRadarEnableFastTimeConstantTimeseriesById( Guid id );
    List<RadarEnableFastTimeConstantTimeseriesObject> getRadarEnableFastTimeConstantTimeseriesCollection( );
    List<RadarEnableFastTimeConstantTimeseriesObject> getRadarEnableFastTimeConstantTimeseriesCollectionByCatalog( Guid catalog );
    List<RadarEnableFastTimeConstantTimeseriesObject> qetRadarEnableFastTimeConstantTimeseriesCollectionByCatalogIsNull(  );
    RadarEnableFastTimeConstantTimeseriesObject getRadarEnableFastTimeConstantTimeseriesByCatalogAndName( Guid catalog, String name );
    List<RadarEnableFastTimeConstantTimeseriesObject> qetRadarEnableFastTimeConstantTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // RadarEnableSensitivityTimeControlTimeseries queries
    // ---------------------------------------------------------------------
    RadarEnableSensitivityTimeControlTimeseriesObject getRadarEnableSensitivityTimeControlTimeseriesById( Guid id );
    List<RadarEnableSensitivityTimeControlTimeseriesObject> getRadarEnableSensitivityTimeControlTimeseriesCollection( );
    List<RadarEnableSensitivityTimeControlTimeseriesObject> getRadarEnableSensitivityTimeControlTimeseriesCollectionByCatalog( Guid catalog );
    List<RadarEnableSensitivityTimeControlTimeseriesObject> qetRadarEnableSensitivityTimeControlTimeseriesCollectionByCatalogIsNull(  );
    RadarEnableSensitivityTimeControlTimeseriesObject getRadarEnableSensitivityTimeControlTimeseriesByCatalogAndName( Guid catalog, String name );
    List<RadarEnableSensitivityTimeControlTimeseriesObject> qetRadarEnableSensitivityTimeControlTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // RadarPowerOnTimeseries queries
    // ---------------------------------------------------------------------
    RadarPowerOnTimeseriesObject getRadarPowerOnTimeseriesById( Guid id );
    List<RadarPowerOnTimeseriesObject> getRadarPowerOnTimeseriesCollection( );
    List<RadarPowerOnTimeseriesObject> getRadarPowerOnTimeseriesCollectionByCatalog( Guid catalog );
    List<RadarPowerOnTimeseriesObject> qetRadarPowerOnTimeseriesCollectionByCatalogIsNull(  );
    RadarPowerOnTimeseriesObject getRadarPowerOnTimeseriesByCatalogAndName( Guid catalog, String name );
    List<RadarPowerOnTimeseriesObject> qetRadarPowerOnTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // RadarSaveSettingsTimeseries queries
    // ---------------------------------------------------------------------
    RadarSaveSettingsTimeseriesObject getRadarSaveSettingsTimeseriesById( Guid id );
    List<RadarSaveSettingsTimeseriesObject> getRadarSaveSettingsTimeseriesCollection( );
    List<RadarSaveSettingsTimeseriesObject> getRadarSaveSettingsTimeseriesCollectionByCatalog( Guid catalog );
    List<RadarSaveSettingsTimeseriesObject> qetRadarSaveSettingsTimeseriesCollectionByCatalogIsNull(  );
    RadarSaveSettingsTimeseriesObject getRadarSaveSettingsTimeseriesByCatalogAndName( Guid catalog, String name );
    List<RadarSaveSettingsTimeseriesObject> qetRadarSaveSettingsTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // RadarTrackingTimeseries queries
    // ---------------------------------------------------------------------
    RadarTrackingTimeseriesObject getRadarTrackingTimeseriesById( Guid id );
    List<RadarTrackingTimeseriesObject> getRadarTrackingTimeseriesCollection( );
    List<RadarTrackingTimeseriesObject> getRadarTrackingTimeseriesCollectionByCatalog( Guid catalog );
    List<RadarTrackingTimeseriesObject> qetRadarTrackingTimeseriesCollectionByCatalogIsNull(  );
    RadarTrackingTimeseriesObject getRadarTrackingTimeseriesByCatalogAndName( Guid catalog, String name );
    List<RadarTrackingTimeseriesObject> qetRadarTrackingTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // MediaProxySessionEnabledTimeseries queries
    // ---------------------------------------------------------------------
    MediaProxySessionEnabledTimeseriesObject getMediaProxySessionEnabledTimeseriesById( Guid id );
    List<MediaProxySessionEnabledTimeseriesObject> getMediaProxySessionEnabledTimeseriesCollection( );
    List<MediaProxySessionEnabledTimeseriesObject> getMediaProxySessionEnabledTimeseriesCollectionByCatalog( Guid catalog );
    List<MediaProxySessionEnabledTimeseriesObject> qetMediaProxySessionEnabledTimeseriesCollectionByCatalogIsNull(  );
    MediaProxySessionEnabledTimeseriesObject getMediaProxySessionEnabledTimeseriesByCatalogAndName( Guid catalog, String name );
    List<MediaProxySessionEnabledTimeseriesObject> qetMediaProxySessionEnabledTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // MediaServiceEnabledTimeseries queries
    // ---------------------------------------------------------------------
    MediaServiceEnabledTimeseriesObject getMediaServiceEnabledTimeseriesById( Guid id );
    List<MediaServiceEnabledTimeseriesObject> getMediaServiceEnabledTimeseriesCollection( );
    List<MediaServiceEnabledTimeseriesObject> getMediaServiceEnabledTimeseriesCollectionByCatalog( Guid catalog );
    List<MediaServiceEnabledTimeseriesObject> qetMediaServiceEnabledTimeseriesCollectionByCatalogIsNull(  );
    MediaServiceEnabledTimeseriesObject getMediaServiceEnabledTimeseriesByCatalogAndName( Guid catalog, String name );
    List<MediaServiceEnabledTimeseriesObject> qetMediaServiceEnabledTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // ByteTimeseries queries
    // ---------------------------------------------------------------------
    ByteTimeseriesObject getByteTimeseriesById( Guid id );
    List<ByteTimeseriesObject> getByteTimeseriesCollection( );
    List<ByteTimeseriesObject> getByteTimeseriesCollectionByCatalog( Guid catalog );
    List<ByteTimeseriesObject> qetByteTimeseriesCollectionByCatalogIsNull(  );
    ByteTimeseriesObject getByteTimeseriesByCatalogAndName( Guid catalog, String name );
    List<ByteTimeseriesObject> qetByteTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // DateTimeTimeseries queries
    // ---------------------------------------------------------------------
    DateTimeTimeseriesObject getDateTimeTimeseriesById( Guid id );
    List<DateTimeTimeseriesObject> getDateTimeTimeseriesCollection( );
    List<DateTimeTimeseriesObject> getDateTimeTimeseriesCollectionByCatalog( Guid catalog );
    List<DateTimeTimeseriesObject> qetDateTimeTimeseriesCollectionByCatalogIsNull(  );
    DateTimeTimeseriesObject getDateTimeTimeseriesByCatalogAndName( Guid catalog, String name );
    List<DateTimeTimeseriesObject> qetDateTimeTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // DoubleTimeseries queries
    // ---------------------------------------------------------------------
    DoubleTimeseriesObject getDoubleTimeseriesById( Guid id );
    List<DoubleTimeseriesObject> getDoubleTimeseriesCollection( );
    List<DoubleTimeseriesObject> getDoubleTimeseriesCollectionByCatalog( Guid catalog );
    List<DoubleTimeseriesObject> qetDoubleTimeseriesCollectionByCatalogIsNull(  );
    DoubleTimeseriesObject getDoubleTimeseriesByCatalogAndName( Guid catalog, String name );
    List<DoubleTimeseriesObject> qetDoubleTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // GNSSAltitudeTimeseries queries
    // ---------------------------------------------------------------------
    GNSSAltitudeTimeseriesObject getGNSSAltitudeTimeseriesById( Guid id );
    List<GNSSAltitudeTimeseriesObject> getGNSSAltitudeTimeseriesCollection( );
    List<GNSSAltitudeTimeseriesObject> getGNSSAltitudeTimeseriesCollectionByCatalog( Guid catalog );
    List<GNSSAltitudeTimeseriesObject> qetGNSSAltitudeTimeseriesCollectionByCatalogIsNull(  );
    GNSSAltitudeTimeseriesObject getGNSSAltitudeTimeseriesByCatalogAndName( Guid catalog, String name );
    List<GNSSAltitudeTimeseriesObject> qetGNSSAltitudeTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // GNSSLatitudeTimeseries queries
    // ---------------------------------------------------------------------
    GNSSLatitudeTimeseriesObject getGNSSLatitudeTimeseriesById( Guid id );
    List<GNSSLatitudeTimeseriesObject> getGNSSLatitudeTimeseriesCollection( );
    List<GNSSLatitudeTimeseriesObject> getGNSSLatitudeTimeseriesCollectionByCatalog( Guid catalog );
    List<GNSSLatitudeTimeseriesObject> qetGNSSLatitudeTimeseriesCollectionByCatalogIsNull(  );
    GNSSLatitudeTimeseriesObject getGNSSLatitudeTimeseriesByCatalogAndName( Guid catalog, String name );
    List<GNSSLatitudeTimeseriesObject> qetGNSSLatitudeTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // GNSSLongitudeTimeseries queries
    // ---------------------------------------------------------------------
    GNSSLongitudeTimeseriesObject getGNSSLongitudeTimeseriesById( Guid id );
    List<GNSSLongitudeTimeseriesObject> getGNSSLongitudeTimeseriesCollection( );
    List<GNSSLongitudeTimeseriesObject> getGNSSLongitudeTimeseriesCollectionByCatalog( Guid catalog );
    List<GNSSLongitudeTimeseriesObject> qetGNSSLongitudeTimeseriesCollectionByCatalogIsNull(  );
    GNSSLongitudeTimeseriesObject getGNSSLongitudeTimeseriesByCatalogAndName( Guid catalog, String name );
    List<GNSSLongitudeTimeseriesObject> qetGNSSLongitudeTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // GyroCourseTimeseries queries
    // ---------------------------------------------------------------------
    GyroCourseTimeseriesObject getGyroCourseTimeseriesById( Guid id );
    List<GyroCourseTimeseriesObject> getGyroCourseTimeseriesCollection( );
    List<GyroCourseTimeseriesObject> getGyroCourseTimeseriesCollectionByCatalog( Guid catalog );
    List<GyroCourseTimeseriesObject> qetGyroCourseTimeseriesCollectionByCatalogIsNull(  );
    GyroCourseTimeseriesObject getGyroCourseTimeseriesByCatalogAndName( Guid catalog, String name );
    List<GyroCourseTimeseriesObject> qetGyroCourseTimeseriesCollectionByCatalogIsNullAndName( String name );
    GyroCourseTimeseriesObject getGyroCourseTimeseriesByGyroDevice( Guid gyroDevice );
    List<GyroCourseTimeseriesObject> qetGyroCourseTimeseriesCollectionByGyroDeviceIsNull(  );
    // ---------------------------------------------------------------------
    // GyroHeadingMagneticNorthTimeseries queries
    // ---------------------------------------------------------------------
    GyroHeadingMagneticNorthTimeseriesObject getGyroHeadingMagneticNorthTimeseriesById( Guid id );
    List<GyroHeadingMagneticNorthTimeseriesObject> getGyroHeadingMagneticNorthTimeseriesCollection( );
    List<GyroHeadingMagneticNorthTimeseriesObject> getGyroHeadingMagneticNorthTimeseriesCollectionByCatalog( Guid catalog );
    List<GyroHeadingMagneticNorthTimeseriesObject> qetGyroHeadingMagneticNorthTimeseriesCollectionByCatalogIsNull(  );
    GyroHeadingMagneticNorthTimeseriesObject getGyroHeadingMagneticNorthTimeseriesByCatalogAndName( Guid catalog, String name );
    List<GyroHeadingMagneticNorthTimeseriesObject> qetGyroHeadingMagneticNorthTimeseriesCollectionByCatalogIsNullAndName( String name );
    GyroHeadingMagneticNorthTimeseriesObject getGyroHeadingMagneticNorthTimeseriesByGyroDevice( Guid gyroDevice );
    List<GyroHeadingMagneticNorthTimeseriesObject> qetGyroHeadingMagneticNorthTimeseriesCollectionByGyroDeviceIsNull(  );
    // ---------------------------------------------------------------------
    // GyroHeadingTrueNorthTimeseries queries
    // ---------------------------------------------------------------------
    GyroHeadingTrueNorthTimeseriesObject getGyroHeadingTrueNorthTimeseriesById( Guid id );
    List<GyroHeadingTrueNorthTimeseriesObject> getGyroHeadingTrueNorthTimeseriesCollection( );
    List<GyroHeadingTrueNorthTimeseriesObject> getGyroHeadingTrueNorthTimeseriesCollectionByCatalog( Guid catalog );
    List<GyroHeadingTrueNorthTimeseriesObject> qetGyroHeadingTrueNorthTimeseriesCollectionByCatalogIsNull(  );
    GyroHeadingTrueNorthTimeseriesObject getGyroHeadingTrueNorthTimeseriesByCatalogAndName( Guid catalog, String name );
    List<GyroHeadingTrueNorthTimeseriesObject> qetGyroHeadingTrueNorthTimeseriesCollectionByCatalogIsNullAndName( String name );
    GyroHeadingTrueNorthTimeseriesObject getGyroHeadingTrueNorthTimeseriesByGyroDevice( Guid gyroDevice );
    List<GyroHeadingTrueNorthTimeseriesObject> qetGyroHeadingTrueNorthTimeseriesCollectionByGyroDeviceIsNull(  );
    // ---------------------------------------------------------------------
    // GyroPitchTimeseries queries
    // ---------------------------------------------------------------------
    GyroPitchTimeseriesObject getGyroPitchTimeseriesById( Guid id );
    List<GyroPitchTimeseriesObject> getGyroPitchTimeseriesCollection( );
    List<GyroPitchTimeseriesObject> getGyroPitchTimeseriesCollectionByCatalog( Guid catalog );
    List<GyroPitchTimeseriesObject> qetGyroPitchTimeseriesCollectionByCatalogIsNull(  );
    GyroPitchTimeseriesObject getGyroPitchTimeseriesByCatalogAndName( Guid catalog, String name );
    List<GyroPitchTimeseriesObject> qetGyroPitchTimeseriesCollectionByCatalogIsNullAndName( String name );
    GyroPitchTimeseriesObject getGyroPitchTimeseriesByGyroDevice( Guid gyroDevice );
    List<GyroPitchTimeseriesObject> qetGyroPitchTimeseriesCollectionByGyroDeviceIsNull(  );
    // ---------------------------------------------------------------------
    // GyroRateOfTurnTimeseries queries
    // ---------------------------------------------------------------------
    GyroRateOfTurnTimeseriesObject getGyroRateOfTurnTimeseriesById( Guid id );
    List<GyroRateOfTurnTimeseriesObject> getGyroRateOfTurnTimeseriesCollection( );
    List<GyroRateOfTurnTimeseriesObject> getGyroRateOfTurnTimeseriesCollectionByCatalog( Guid catalog );
    List<GyroRateOfTurnTimeseriesObject> qetGyroRateOfTurnTimeseriesCollectionByCatalogIsNull(  );
    GyroRateOfTurnTimeseriesObject getGyroRateOfTurnTimeseriesByCatalogAndName( Guid catalog, String name );
    List<GyroRateOfTurnTimeseriesObject> qetGyroRateOfTurnTimeseriesCollectionByCatalogIsNullAndName( String name );
    GyroRateOfTurnTimeseriesObject getGyroRateOfTurnTimeseriesByGyroDevice( Guid gyroDevice );
    List<GyroRateOfTurnTimeseriesObject> qetGyroRateOfTurnTimeseriesCollectionByGyroDeviceIsNull(  );
    // ---------------------------------------------------------------------
    // GyroRollTimeseries queries
    // ---------------------------------------------------------------------
    GyroRollTimeseriesObject getGyroRollTimeseriesById( Guid id );
    List<GyroRollTimeseriesObject> getGyroRollTimeseriesCollection( );
    List<GyroRollTimeseriesObject> getGyroRollTimeseriesCollectionByCatalog( Guid catalog );
    List<GyroRollTimeseriesObject> qetGyroRollTimeseriesCollectionByCatalogIsNull(  );
    GyroRollTimeseriesObject getGyroRollTimeseriesByCatalogAndName( Guid catalog, String name );
    List<GyroRollTimeseriesObject> qetGyroRollTimeseriesCollectionByCatalogIsNullAndName( String name );
    GyroRollTimeseriesObject getGyroRollTimeseriesByGyroDevice( Guid gyroDevice );
    List<GyroRollTimeseriesObject> qetGyroRollTimeseriesCollectionByGyroDeviceIsNull(  );
    // ---------------------------------------------------------------------
    // GyroSpeedTimeseries queries
    // ---------------------------------------------------------------------
    GyroSpeedTimeseriesObject getGyroSpeedTimeseriesById( Guid id );
    List<GyroSpeedTimeseriesObject> getGyroSpeedTimeseriesCollection( );
    List<GyroSpeedTimeseriesObject> getGyroSpeedTimeseriesCollectionByCatalog( Guid catalog );
    List<GyroSpeedTimeseriesObject> qetGyroSpeedTimeseriesCollectionByCatalogIsNull(  );
    GyroSpeedTimeseriesObject getGyroSpeedTimeseriesByCatalogAndName( Guid catalog, String name );
    List<GyroSpeedTimeseriesObject> qetGyroSpeedTimeseriesCollectionByCatalogIsNullAndName( String name );
    GyroSpeedTimeseriesObject getGyroSpeedTimeseriesByGyroDevice( Guid gyroDevice );
    List<GyroSpeedTimeseriesObject> qetGyroSpeedTimeseriesCollectionByGyroDeviceIsNull(  );
    // ---------------------------------------------------------------------
    // RadarLatitudeTimeseries queries
    // ---------------------------------------------------------------------
    RadarLatitudeTimeseriesObject getRadarLatitudeTimeseriesById( Guid id );
    List<RadarLatitudeTimeseriesObject> getRadarLatitudeTimeseriesCollection( );
    List<RadarLatitudeTimeseriesObject> getRadarLatitudeTimeseriesCollectionByCatalog( Guid catalog );
    List<RadarLatitudeTimeseriesObject> qetRadarLatitudeTimeseriesCollectionByCatalogIsNull(  );
    RadarLatitudeTimeseriesObject getRadarLatitudeTimeseriesByCatalogAndName( Guid catalog, String name );
    List<RadarLatitudeTimeseriesObject> qetRadarLatitudeTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // RadarLongitudeTimeseries queries
    // ---------------------------------------------------------------------
    RadarLongitudeTimeseriesObject getRadarLongitudeTimeseriesById( Guid id );
    List<RadarLongitudeTimeseriesObject> getRadarLongitudeTimeseriesCollection( );
    List<RadarLongitudeTimeseriesObject> getRadarLongitudeTimeseriesCollectionByCatalog( Guid catalog );
    List<RadarLongitudeTimeseriesObject> qetRadarLongitudeTimeseriesCollectionByCatalogIsNull(  );
    RadarLongitudeTimeseriesObject getRadarLongitudeTimeseriesByCatalogAndName( Guid catalog, String name );
    List<RadarLongitudeTimeseriesObject> qetRadarLongitudeTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // RadomeDewPointTimeseries queries
    // ---------------------------------------------------------------------
    RadomeDewPointTimeseriesObject getRadomeDewPointTimeseriesById( Guid id );
    List<RadomeDewPointTimeseriesObject> getRadomeDewPointTimeseriesCollection( );
    List<RadomeDewPointTimeseriesObject> getRadomeDewPointTimeseriesCollectionByCatalog( Guid catalog );
    List<RadomeDewPointTimeseriesObject> qetRadomeDewPointTimeseriesCollectionByCatalogIsNull(  );
    RadomeDewPointTimeseriesObject getRadomeDewPointTimeseriesByCatalogAndName( Guid catalog, String name );
    List<RadomeDewPointTimeseriesObject> qetRadomeDewPointTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // RadomePressureTimeseries queries
    // ---------------------------------------------------------------------
    RadomePressureTimeseriesObject getRadomePressureTimeseriesById( Guid id );
    List<RadomePressureTimeseriesObject> getRadomePressureTimeseriesCollection( );
    List<RadomePressureTimeseriesObject> getRadomePressureTimeseriesCollectionByCatalog( Guid catalog );
    List<RadomePressureTimeseriesObject> qetRadomePressureTimeseriesCollectionByCatalogIsNull(  );
    RadomePressureTimeseriesObject getRadomePressureTimeseriesByCatalogAndName( Guid catalog, String name );
    List<RadomePressureTimeseriesObject> qetRadomePressureTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // RadomeTemperatureTimeseries queries
    // ---------------------------------------------------------------------
    RadomeTemperatureTimeseriesObject getRadomeTemperatureTimeseriesById( Guid id );
    List<RadomeTemperatureTimeseriesObject> getRadomeTemperatureTimeseriesCollection( );
    List<RadomeTemperatureTimeseriesObject> getRadomeTemperatureTimeseriesCollectionByCatalog( Guid catalog );
    List<RadomeTemperatureTimeseriesObject> qetRadomeTemperatureTimeseriesCollectionByCatalogIsNull(  );
    RadomeTemperatureTimeseriesObject getRadomeTemperatureTimeseriesByCatalogAndName( Guid catalog, String name );
    List<RadomeTemperatureTimeseriesObject> qetRadomeTemperatureTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // VesselDraughtTimeseries queries
    // ---------------------------------------------------------------------
    VesselDraughtTimeseriesObject getVesselDraughtTimeseriesById( Guid id );
    List<VesselDraughtTimeseriesObject> getVesselDraughtTimeseriesCollection( );
    List<VesselDraughtTimeseriesObject> getVesselDraughtTimeseriesCollectionByCatalog( Guid catalog );
    List<VesselDraughtTimeseriesObject> qetVesselDraughtTimeseriesCollectionByCatalogIsNull(  );
    VesselDraughtTimeseriesObject getVesselDraughtTimeseriesByCatalogAndName( Guid catalog, String name );
    List<VesselDraughtTimeseriesObject> qetVesselDraughtTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // ViewLatitudeTimeseries queries
    // ---------------------------------------------------------------------
    ViewLatitudeTimeseriesObject getViewLatitudeTimeseriesById( Guid id );
    List<ViewLatitudeTimeseriesObject> getViewLatitudeTimeseriesCollection( );
    List<ViewLatitudeTimeseriesObject> getViewLatitudeTimeseriesCollectionByCatalog( Guid catalog );
    List<ViewLatitudeTimeseriesObject> qetViewLatitudeTimeseriesCollectionByCatalogIsNull(  );
    ViewLatitudeTimeseriesObject getViewLatitudeTimeseriesByCatalogAndName( Guid catalog, String name );
    List<ViewLatitudeTimeseriesObject> qetViewLatitudeTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // ViewLongitudeTimeseries queries
    // ---------------------------------------------------------------------
    ViewLongitudeTimeseriesObject getViewLongitudeTimeseriesById( Guid id );
    List<ViewLongitudeTimeseriesObject> getViewLongitudeTimeseriesCollection( );
    List<ViewLongitudeTimeseriesObject> getViewLongitudeTimeseriesCollectionByCatalog( Guid catalog );
    List<ViewLongitudeTimeseriesObject> qetViewLongitudeTimeseriesCollectionByCatalogIsNull(  );
    ViewLongitudeTimeseriesObject getViewLongitudeTimeseriesByCatalogAndName( Guid catalog, String name );
    List<ViewLongitudeTimeseriesObject> qetViewLongitudeTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // ViewZoomLevelTimeseries queries
    // ---------------------------------------------------------------------
    ViewZoomLevelTimeseriesObject getViewZoomLevelTimeseriesById( Guid id );
    List<ViewZoomLevelTimeseriesObject> getViewZoomLevelTimeseriesCollection( );
    List<ViewZoomLevelTimeseriesObject> getViewZoomLevelTimeseriesCollectionByCatalog( Guid catalog );
    List<ViewZoomLevelTimeseriesObject> qetViewZoomLevelTimeseriesCollectionByCatalogIsNull(  );
    ViewZoomLevelTimeseriesObject getViewZoomLevelTimeseriesByCatalogAndName( Guid catalog, String name );
    List<ViewZoomLevelTimeseriesObject> qetViewZoomLevelTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // WeatherStationAbsoluteHumidityTimeseries queries
    // ---------------------------------------------------------------------
    WeatherStationAbsoluteHumidityTimeseriesObject getWeatherStationAbsoluteHumidityTimeseriesById( Guid id );
    List<WeatherStationAbsoluteHumidityTimeseriesObject> getWeatherStationAbsoluteHumidityTimeseriesCollection( );
    List<WeatherStationAbsoluteHumidityTimeseriesObject> getWeatherStationAbsoluteHumidityTimeseriesCollectionByCatalog( Guid catalog );
    List<WeatherStationAbsoluteHumidityTimeseriesObject> qetWeatherStationAbsoluteHumidityTimeseriesCollectionByCatalogIsNull(  );
    WeatherStationAbsoluteHumidityTimeseriesObject getWeatherStationAbsoluteHumidityTimeseriesByCatalogAndName( Guid catalog, String name );
    List<WeatherStationAbsoluteHumidityTimeseriesObject> qetWeatherStationAbsoluteHumidityTimeseriesCollectionByCatalogIsNullAndName( String name );
    WeatherStationAbsoluteHumidityTimeseriesObject getWeatherStationAbsoluteHumidityTimeseriesByWeatherStation( Guid weatherStation );
    List<WeatherStationAbsoluteHumidityTimeseriesObject> qetWeatherStationAbsoluteHumidityTimeseriesCollectionByWeatherStationIsNull(  );
    // ---------------------------------------------------------------------
    // WeatherStationAirTemperatureTimeseries queries
    // ---------------------------------------------------------------------
    WeatherStationAirTemperatureTimeseriesObject getWeatherStationAirTemperatureTimeseriesById( Guid id );
    List<WeatherStationAirTemperatureTimeseriesObject> getWeatherStationAirTemperatureTimeseriesCollection( );
    List<WeatherStationAirTemperatureTimeseriesObject> getWeatherStationAirTemperatureTimeseriesCollectionByCatalog( Guid catalog );
    List<WeatherStationAirTemperatureTimeseriesObject> qetWeatherStationAirTemperatureTimeseriesCollectionByCatalogIsNull(  );
    WeatherStationAirTemperatureTimeseriesObject getWeatherStationAirTemperatureTimeseriesByCatalogAndName( Guid catalog, String name );
    List<WeatherStationAirTemperatureTimeseriesObject> qetWeatherStationAirTemperatureTimeseriesCollectionByCatalogIsNullAndName( String name );
    WeatherStationAirTemperatureTimeseriesObject getWeatherStationAirTemperatureTimeseriesByWeatherStation( Guid weatherStation );
    List<WeatherStationAirTemperatureTimeseriesObject> qetWeatherStationAirTemperatureTimeseriesCollectionByWeatherStationIsNull(  );
    // ---------------------------------------------------------------------
    // WeatherStationBarometricPressureTimeseries queries
    // ---------------------------------------------------------------------
    WeatherStationBarometricPressureTimeseriesObject getWeatherStationBarometricPressureTimeseriesById( Guid id );
    List<WeatherStationBarometricPressureTimeseriesObject> getWeatherStationBarometricPressureTimeseriesCollection( );
    List<WeatherStationBarometricPressureTimeseriesObject> getWeatherStationBarometricPressureTimeseriesCollectionByCatalog( Guid catalog );
    List<WeatherStationBarometricPressureTimeseriesObject> qetWeatherStationBarometricPressureTimeseriesCollectionByCatalogIsNull(  );
    WeatherStationBarometricPressureTimeseriesObject getWeatherStationBarometricPressureTimeseriesByCatalogAndName( Guid catalog, String name );
    List<WeatherStationBarometricPressureTimeseriesObject> qetWeatherStationBarometricPressureTimeseriesCollectionByCatalogIsNullAndName( String name );
    WeatherStationBarometricPressureTimeseriesObject getWeatherStationBarometricPressureTimeseriesByWeatherStation( Guid weatherStation );
    List<WeatherStationBarometricPressureTimeseriesObject> qetWeatherStationBarometricPressureTimeseriesCollectionByWeatherStationIsNull(  );
    // ---------------------------------------------------------------------
    // WeatherStationDewPointTimeseries queries
    // ---------------------------------------------------------------------
    WeatherStationDewPointTimeseriesObject getWeatherStationDewPointTimeseriesById( Guid id );
    List<WeatherStationDewPointTimeseriesObject> getWeatherStationDewPointTimeseriesCollection( );
    List<WeatherStationDewPointTimeseriesObject> getWeatherStationDewPointTimeseriesCollectionByCatalog( Guid catalog );
    List<WeatherStationDewPointTimeseriesObject> qetWeatherStationDewPointTimeseriesCollectionByCatalogIsNull(  );
    WeatherStationDewPointTimeseriesObject getWeatherStationDewPointTimeseriesByCatalogAndName( Guid catalog, String name );
    List<WeatherStationDewPointTimeseriesObject> qetWeatherStationDewPointTimeseriesCollectionByCatalogIsNullAndName( String name );
    WeatherStationDewPointTimeseriesObject getWeatherStationDewPointTimeseriesByWeatherStation( Guid weatherStation );
    List<WeatherStationDewPointTimeseriesObject> qetWeatherStationDewPointTimeseriesCollectionByWeatherStationIsNull(  );
    // ---------------------------------------------------------------------
    // WeatherStationRelativeHumidityTimeseries queries
    // ---------------------------------------------------------------------
    WeatherStationRelativeHumidityTimeseriesObject getWeatherStationRelativeHumidityTimeseriesById( Guid id );
    List<WeatherStationRelativeHumidityTimeseriesObject> getWeatherStationRelativeHumidityTimeseriesCollection( );
    List<WeatherStationRelativeHumidityTimeseriesObject> getWeatherStationRelativeHumidityTimeseriesCollectionByCatalog( Guid catalog );
    List<WeatherStationRelativeHumidityTimeseriesObject> qetWeatherStationRelativeHumidityTimeseriesCollectionByCatalogIsNull(  );
    WeatherStationRelativeHumidityTimeseriesObject getWeatherStationRelativeHumidityTimeseriesByCatalogAndName( Guid catalog, String name );
    List<WeatherStationRelativeHumidityTimeseriesObject> qetWeatherStationRelativeHumidityTimeseriesCollectionByCatalogIsNullAndName( String name );
    WeatherStationRelativeHumidityTimeseriesObject getWeatherStationRelativeHumidityTimeseriesByWeatherStation( Guid weatherStation );
    List<WeatherStationRelativeHumidityTimeseriesObject> qetWeatherStationRelativeHumidityTimeseriesCollectionByWeatherStationIsNull(  );
    // ---------------------------------------------------------------------
    // WeatherStationWaterTemperatureTimeseries queries
    // ---------------------------------------------------------------------
    WeatherStationWaterTemperatureTimeseriesObject getWeatherStationWaterTemperatureTimeseriesById( Guid id );
    List<WeatherStationWaterTemperatureTimeseriesObject> getWeatherStationWaterTemperatureTimeseriesCollection( );
    List<WeatherStationWaterTemperatureTimeseriesObject> getWeatherStationWaterTemperatureTimeseriesCollectionByCatalog( Guid catalog );
    List<WeatherStationWaterTemperatureTimeseriesObject> qetWeatherStationWaterTemperatureTimeseriesCollectionByCatalogIsNull(  );
    WeatherStationWaterTemperatureTimeseriesObject getWeatherStationWaterTemperatureTimeseriesByCatalogAndName( Guid catalog, String name );
    List<WeatherStationWaterTemperatureTimeseriesObject> qetWeatherStationWaterTemperatureTimeseriesCollectionByCatalogIsNullAndName( String name );
    WeatherStationWaterTemperatureTimeseriesObject getWeatherStationWaterTemperatureTimeseriesByWeatherStation( Guid weatherStation );
    List<WeatherStationWaterTemperatureTimeseriesObject> qetWeatherStationWaterTemperatureTimeseriesCollectionByWeatherStationIsNull(  );
    // ---------------------------------------------------------------------
    // WeatherStationWindDirectionTimeseries queries
    // ---------------------------------------------------------------------
    WeatherStationWindDirectionTimeseriesObject getWeatherStationWindDirectionTimeseriesById( Guid id );
    List<WeatherStationWindDirectionTimeseriesObject> getWeatherStationWindDirectionTimeseriesCollection( );
    List<WeatherStationWindDirectionTimeseriesObject> getWeatherStationWindDirectionTimeseriesCollectionByCatalog( Guid catalog );
    List<WeatherStationWindDirectionTimeseriesObject> qetWeatherStationWindDirectionTimeseriesCollectionByCatalogIsNull(  );
    WeatherStationWindDirectionTimeseriesObject getWeatherStationWindDirectionTimeseriesByCatalogAndName( Guid catalog, String name );
    List<WeatherStationWindDirectionTimeseriesObject> qetWeatherStationWindDirectionTimeseriesCollectionByCatalogIsNullAndName( String name );
    WeatherStationWindDirectionTimeseriesObject getWeatherStationWindDirectionTimeseriesByWeatherStation( Guid weatherStation );
    List<WeatherStationWindDirectionTimeseriesObject> qetWeatherStationWindDirectionTimeseriesCollectionByWeatherStationIsNull(  );
    // ---------------------------------------------------------------------
    // WeatherStationWindSpeedTimeseries queries
    // ---------------------------------------------------------------------
    WeatherStationWindSpeedTimeseriesObject getWeatherStationWindSpeedTimeseriesById( Guid id );
    List<WeatherStationWindSpeedTimeseriesObject> getWeatherStationWindSpeedTimeseriesCollection( );
    List<WeatherStationWindSpeedTimeseriesObject> getWeatherStationWindSpeedTimeseriesCollectionByCatalog( Guid catalog );
    List<WeatherStationWindSpeedTimeseriesObject> qetWeatherStationWindSpeedTimeseriesCollectionByCatalogIsNull(  );
    WeatherStationWindSpeedTimeseriesObject getWeatherStationWindSpeedTimeseriesByCatalogAndName( Guid catalog, String name );
    List<WeatherStationWindSpeedTimeseriesObject> qetWeatherStationWindSpeedTimeseriesCollectionByCatalogIsNullAndName( String name );
    WeatherStationWindSpeedTimeseriesObject getWeatherStationWindSpeedTimeseriesByWeatherStation( Guid weatherStation );
    List<WeatherStationWindSpeedTimeseriesObject> qetWeatherStationWindSpeedTimeseriesCollectionByWeatherStationIsNull(  );
    // ---------------------------------------------------------------------
    // GeoPosition2DTimeseries queries
    // ---------------------------------------------------------------------
    GeoPosition2DTimeseriesObject getGeoPosition2DTimeseriesById( Guid id );
    List<GeoPosition2DTimeseriesObject> getGeoPosition2DTimeseriesCollection( );
    List<GeoPosition2DTimeseriesObject> getGeoPosition2DTimeseriesCollectionByCatalog( Guid catalog );
    List<GeoPosition2DTimeseriesObject> qetGeoPosition2DTimeseriesCollectionByCatalogIsNull(  );
    GeoPosition2DTimeseriesObject getGeoPosition2DTimeseriesByCatalogAndName( Guid catalog, String name );
    List<GeoPosition2DTimeseriesObject> qetGeoPosition2DTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // AisAidToNavigationPositionTimeseries queries
    // ---------------------------------------------------------------------
    AisAidToNavigationPositionTimeseriesObject getAisAidToNavigationPositionTimeseriesById( Guid id );
    List<AisAidToNavigationPositionTimeseriesObject> getAisAidToNavigationPositionTimeseriesCollection( );
    List<AisAidToNavigationPositionTimeseriesObject> getAisAidToNavigationPositionTimeseriesCollectionByCatalog( Guid catalog );
    List<AisAidToNavigationPositionTimeseriesObject> qetAisAidToNavigationPositionTimeseriesCollectionByCatalogIsNull(  );
    AisAidToNavigationPositionTimeseriesObject getAisAidToNavigationPositionTimeseriesByCatalogAndName( Guid catalog, String name );
    List<AisAidToNavigationPositionTimeseriesObject> qetAisAidToNavigationPositionTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // GeoPosition3DTimeseries queries
    // ---------------------------------------------------------------------
    GeoPosition3DTimeseriesObject getGeoPosition3DTimeseriesById( Guid id );
    List<GeoPosition3DTimeseriesObject> getGeoPosition3DTimeseriesCollection( );
    List<GeoPosition3DTimeseriesObject> getGeoPosition3DTimeseriesCollectionByCatalog( Guid catalog );
    List<GeoPosition3DTimeseriesObject> qetGeoPosition3DTimeseriesCollectionByCatalogIsNull(  );
    GeoPosition3DTimeseriesObject getGeoPosition3DTimeseriesByCatalogAndName( Guid catalog, String name );
    List<GeoPosition3DTimeseriesObject> qetGeoPosition3DTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // GuidTimeseries queries
    // ---------------------------------------------------------------------
    GuidTimeseriesObject getGuidTimeseriesById( Guid id );
    List<GuidTimeseriesObject> getGuidTimeseriesCollection( );
    List<GuidTimeseriesObject> getGuidTimeseriesCollectionByCatalog( Guid catalog );
    List<GuidTimeseriesObject> qetGuidTimeseriesCollectionByCatalogIsNull(  );
    GuidTimeseriesObject getGuidTimeseriesByCatalogAndName( Guid catalog, String name );
    List<GuidTimeseriesObject> qetGuidTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // Int16Timeseries queries
    // ---------------------------------------------------------------------
    Int16TimeseriesObject getInt16TimeseriesById( Guid id );
    List<Int16TimeseriesObject> getInt16TimeseriesCollection( );
    List<Int16TimeseriesObject> getInt16TimeseriesCollectionByCatalog( Guid catalog );
    List<Int16TimeseriesObject> qetInt16TimeseriesCollectionByCatalogIsNull(  );
    Int16TimeseriesObject getInt16TimeseriesByCatalogAndName( Guid catalog, String name );
    List<Int16TimeseriesObject> qetInt16TimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // Int32Timeseries queries
    // ---------------------------------------------------------------------
    Int32TimeseriesObject getInt32TimeseriesById( Guid id );
    List<Int32TimeseriesObject> getInt32TimeseriesCollection( );
    List<Int32TimeseriesObject> getInt32TimeseriesCollectionByCatalog( Guid catalog );
    List<Int32TimeseriesObject> qetInt32TimeseriesCollectionByCatalogIsNull(  );
    Int32TimeseriesObject getInt32TimeseriesByCatalogAndName( Guid catalog, String name );
    List<Int32TimeseriesObject> qetInt32TimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // RadarAzimuthOffsetTimeseries queries
    // ---------------------------------------------------------------------
    RadarAzimuthOffsetTimeseriesObject getRadarAzimuthOffsetTimeseriesById( Guid id );
    List<RadarAzimuthOffsetTimeseriesObject> getRadarAzimuthOffsetTimeseriesCollection( );
    List<RadarAzimuthOffsetTimeseriesObject> getRadarAzimuthOffsetTimeseriesCollectionByCatalog( Guid catalog );
    List<RadarAzimuthOffsetTimeseriesObject> qetRadarAzimuthOffsetTimeseriesCollectionByCatalogIsNull(  );
    RadarAzimuthOffsetTimeseriesObject getRadarAzimuthOffsetTimeseriesByCatalogAndName( Guid catalog, String name );
    List<RadarAzimuthOffsetTimeseriesObject> qetRadarAzimuthOffsetTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // RadarFastTimeConstantLevelTimeseries queries
    // ---------------------------------------------------------------------
    RadarFastTimeConstantLevelTimeseriesObject getRadarFastTimeConstantLevelTimeseriesById( Guid id );
    List<RadarFastTimeConstantLevelTimeseriesObject> getRadarFastTimeConstantLevelTimeseriesCollection( );
    List<RadarFastTimeConstantLevelTimeseriesObject> getRadarFastTimeConstantLevelTimeseriesCollectionByCatalog( Guid catalog );
    List<RadarFastTimeConstantLevelTimeseriesObject> qetRadarFastTimeConstantLevelTimeseriesCollectionByCatalogIsNull(  );
    RadarFastTimeConstantLevelTimeseriesObject getRadarFastTimeConstantLevelTimeseriesByCatalogAndName( Guid catalog, String name );
    List<RadarFastTimeConstantLevelTimeseriesObject> qetRadarFastTimeConstantLevelTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // RadarFastTimeConstantModeTimeseries queries
    // ---------------------------------------------------------------------
    RadarFastTimeConstantModeTimeseriesObject getRadarFastTimeConstantModeTimeseriesById( Guid id );
    List<RadarFastTimeConstantModeTimeseriesObject> getRadarFastTimeConstantModeTimeseriesCollection( );
    List<RadarFastTimeConstantModeTimeseriesObject> getRadarFastTimeConstantModeTimeseriesCollectionByCatalog( Guid catalog );
    List<RadarFastTimeConstantModeTimeseriesObject> qetRadarFastTimeConstantModeTimeseriesCollectionByCatalogIsNull(  );
    RadarFastTimeConstantModeTimeseriesObject getRadarFastTimeConstantModeTimeseriesByCatalogAndName( Guid catalog, String name );
    List<RadarFastTimeConstantModeTimeseriesObject> qetRadarFastTimeConstantModeTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // RadarPulseTimeseries queries
    // ---------------------------------------------------------------------
    RadarPulseTimeseriesObject getRadarPulseTimeseriesById( Guid id );
    List<RadarPulseTimeseriesObject> getRadarPulseTimeseriesCollection( );
    List<RadarPulseTimeseriesObject> getRadarPulseTimeseriesCollectionByCatalog( Guid catalog );
    List<RadarPulseTimeseriesObject> qetRadarPulseTimeseriesCollectionByCatalogIsNull(  );
    RadarPulseTimeseriesObject getRadarPulseTimeseriesByCatalogAndName( Guid catalog, String name );
    List<RadarPulseTimeseriesObject> qetRadarPulseTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // RadarSector1EndTimeseries queries
    // ---------------------------------------------------------------------
    RadarSector1EndTimeseriesObject getRadarSector1EndTimeseriesById( Guid id );
    List<RadarSector1EndTimeseriesObject> getRadarSector1EndTimeseriesCollection( );
    List<RadarSector1EndTimeseriesObject> getRadarSector1EndTimeseriesCollectionByCatalog( Guid catalog );
    List<RadarSector1EndTimeseriesObject> qetRadarSector1EndTimeseriesCollectionByCatalogIsNull(  );
    RadarSector1EndTimeseriesObject getRadarSector1EndTimeseriesByCatalogAndName( Guid catalog, String name );
    List<RadarSector1EndTimeseriesObject> qetRadarSector1EndTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // RadarSector1StartTimeseries queries
    // ---------------------------------------------------------------------
    RadarSector1StartTimeseriesObject getRadarSector1StartTimeseriesById( Guid id );
    List<RadarSector1StartTimeseriesObject> getRadarSector1StartTimeseriesCollection( );
    List<RadarSector1StartTimeseriesObject> getRadarSector1StartTimeseriesCollectionByCatalog( Guid catalog );
    List<RadarSector1StartTimeseriesObject> qetRadarSector1StartTimeseriesCollectionByCatalogIsNull(  );
    RadarSector1StartTimeseriesObject getRadarSector1StartTimeseriesByCatalogAndName( Guid catalog, String name );
    List<RadarSector1StartTimeseriesObject> qetRadarSector1StartTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // RadarSector2EndTimeseries queries
    // ---------------------------------------------------------------------
    RadarSector2EndTimeseriesObject getRadarSector2EndTimeseriesById( Guid id );
    List<RadarSector2EndTimeseriesObject> getRadarSector2EndTimeseriesCollection( );
    List<RadarSector2EndTimeseriesObject> getRadarSector2EndTimeseriesCollectionByCatalog( Guid catalog );
    List<RadarSector2EndTimeseriesObject> qetRadarSector2EndTimeseriesCollectionByCatalogIsNull(  );
    RadarSector2EndTimeseriesObject getRadarSector2EndTimeseriesByCatalogAndName( Guid catalog, String name );
    List<RadarSector2EndTimeseriesObject> qetRadarSector2EndTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // RadarSector2StartTimeseries queries
    // ---------------------------------------------------------------------
    RadarSector2StartTimeseriesObject getRadarSector2StartTimeseriesById( Guid id );
    List<RadarSector2StartTimeseriesObject> getRadarSector2StartTimeseriesCollection( );
    List<RadarSector2StartTimeseriesObject> getRadarSector2StartTimeseriesCollectionByCatalog( Guid catalog );
    List<RadarSector2StartTimeseriesObject> qetRadarSector2StartTimeseriesCollectionByCatalogIsNull(  );
    RadarSector2StartTimeseriesObject getRadarSector2StartTimeseriesByCatalogAndName( Guid catalog, String name );
    List<RadarSector2StartTimeseriesObject> qetRadarSector2StartTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // RadarSensitivityTimeControlLevelTimeseries queries
    // ---------------------------------------------------------------------
    RadarSensitivityTimeControlLevelTimeseriesObject getRadarSensitivityTimeControlLevelTimeseriesById( Guid id );
    List<RadarSensitivityTimeControlLevelTimeseriesObject> getRadarSensitivityTimeControlLevelTimeseriesCollection( );
    List<RadarSensitivityTimeControlLevelTimeseriesObject> getRadarSensitivityTimeControlLevelTimeseriesCollectionByCatalog( Guid catalog );
    List<RadarSensitivityTimeControlLevelTimeseriesObject> qetRadarSensitivityTimeControlLevelTimeseriesCollectionByCatalogIsNull(  );
    RadarSensitivityTimeControlLevelTimeseriesObject getRadarSensitivityTimeControlLevelTimeseriesByCatalogAndName( Guid catalog, String name );
    List<RadarSensitivityTimeControlLevelTimeseriesObject> qetRadarSensitivityTimeControlLevelTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // RadarTuningTimeseries queries
    // ---------------------------------------------------------------------
    RadarTuningTimeseriesObject getRadarTuningTimeseriesById( Guid id );
    List<RadarTuningTimeseriesObject> getRadarTuningTimeseriesCollection( );
    List<RadarTuningTimeseriesObject> getRadarTuningTimeseriesCollectionByCatalog( Guid catalog );
    List<RadarTuningTimeseriesObject> qetRadarTuningTimeseriesCollectionByCatalogIsNull(  );
    RadarTuningTimeseriesObject getRadarTuningTimeseriesByCatalogAndName( Guid catalog, String name );
    List<RadarTuningTimeseriesObject> qetRadarTuningTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // VesselPersonsOnBoardTimeseries queries
    // ---------------------------------------------------------------------
    VesselPersonsOnBoardTimeseriesObject getVesselPersonsOnBoardTimeseriesById( Guid id );
    List<VesselPersonsOnBoardTimeseriesObject> getVesselPersonsOnBoardTimeseriesCollection( );
    List<VesselPersonsOnBoardTimeseriesObject> getVesselPersonsOnBoardTimeseriesCollectionByCatalog( Guid catalog );
    List<VesselPersonsOnBoardTimeseriesObject> qetVesselPersonsOnBoardTimeseriesCollectionByCatalogIsNull(  );
    VesselPersonsOnBoardTimeseriesObject getVesselPersonsOnBoardTimeseriesByCatalogAndName( Guid catalog, String name );
    List<VesselPersonsOnBoardTimeseriesObject> qetVesselPersonsOnBoardTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // Int64Timeseries queries
    // ---------------------------------------------------------------------
    Int64TimeseriesObject getInt64TimeseriesById( Guid id );
    List<Int64TimeseriesObject> getInt64TimeseriesCollection( );
    List<Int64TimeseriesObject> getInt64TimeseriesCollectionByCatalog( Guid catalog );
    List<Int64TimeseriesObject> qetInt64TimeseriesCollectionByCatalogIsNull(  );
    Int64TimeseriesObject getInt64TimeseriesByCatalogAndName( Guid catalog, String name );
    List<Int64TimeseriesObject> qetInt64TimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // Position2DTimeseries queries
    // ---------------------------------------------------------------------
    Position2DTimeseriesObject getPosition2DTimeseriesById( Guid id );
    List<Position2DTimeseriesObject> getPosition2DTimeseriesCollection( );
    List<Position2DTimeseriesObject> getPosition2DTimeseriesCollectionByCatalog( Guid catalog );
    List<Position2DTimeseriesObject> qetPosition2DTimeseriesCollectionByCatalogIsNull(  );
    Position2DTimeseriesObject getPosition2DTimeseriesByCatalogAndName( Guid catalog, String name );
    List<Position2DTimeseriesObject> qetPosition2DTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // Position3DTimeseries queries
    // ---------------------------------------------------------------------
    Position3DTimeseriesObject getPosition3DTimeseriesById( Guid id );
    List<Position3DTimeseriesObject> getPosition3DTimeseriesCollection( );
    List<Position3DTimeseriesObject> getPosition3DTimeseriesCollectionByCatalog( Guid catalog );
    List<Position3DTimeseriesObject> qetPosition3DTimeseriesCollectionByCatalogIsNull(  );
    Position3DTimeseriesObject getPosition3DTimeseriesByCatalogAndName( Guid catalog, String name );
    List<Position3DTimeseriesObject> qetPosition3DTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // ReferenceTimeseries queries
    // ---------------------------------------------------------------------
    ReferenceTimeseriesObject getReferenceTimeseriesById( Guid id );
    List<ReferenceTimeseriesObject> getReferenceTimeseriesCollection( );
    List<ReferenceTimeseriesObject> getReferenceTimeseriesCollectionByCatalog( Guid catalog );
    List<ReferenceTimeseriesObject> qetReferenceTimeseriesCollectionByCatalogIsNull(  );
    ReferenceTimeseriesObject getReferenceTimeseriesByCatalogAndName( Guid catalog, String name );
    List<ReferenceTimeseriesObject> qetReferenceTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // SByteTimeseries queries
    // ---------------------------------------------------------------------
    SByteTimeseriesObject getSByteTimeseriesById( Guid id );
    List<SByteTimeseriesObject> getSByteTimeseriesCollection( );
    List<SByteTimeseriesObject> getSByteTimeseriesCollectionByCatalog( Guid catalog );
    List<SByteTimeseriesObject> qetSByteTimeseriesCollectionByCatalogIsNull(  );
    SByteTimeseriesObject getSByteTimeseriesByCatalogAndName( Guid catalog, String name );
    List<SByteTimeseriesObject> qetSByteTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // SingleTimeseries queries
    // ---------------------------------------------------------------------
    SingleTimeseriesObject getSingleTimeseriesById( Guid id );
    List<SingleTimeseriesObject> getSingleTimeseriesCollection( );
    List<SingleTimeseriesObject> getSingleTimeseriesCollectionByCatalog( Guid catalog );
    List<SingleTimeseriesObject> qetSingleTimeseriesCollectionByCatalogIsNull(  );
    SingleTimeseriesObject getSingleTimeseriesByCatalogAndName( Guid catalog, String name );
    List<SingleTimeseriesObject> qetSingleTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // StringTimeseries queries
    // ---------------------------------------------------------------------
    StringTimeseriesObject getStringTimeseriesById( Guid id );
    List<StringTimeseriesObject> getStringTimeseriesCollection( );
    List<StringTimeseriesObject> getStringTimeseriesCollectionByCatalog( Guid catalog );
    List<StringTimeseriesObject> qetStringTimeseriesCollectionByCatalogIsNull(  );
    StringTimeseriesObject getStringTimeseriesByCatalogAndName( Guid catalog, String name );
    List<StringTimeseriesObject> qetStringTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // TimeSpanTimeseries queries
    // ---------------------------------------------------------------------
    TimeSpanTimeseriesObject getTimeSpanTimeseriesById( Guid id );
    List<TimeSpanTimeseriesObject> getTimeSpanTimeseriesCollection( );
    List<TimeSpanTimeseriesObject> getTimeSpanTimeseriesCollectionByCatalog( Guid catalog );
    List<TimeSpanTimeseriesObject> qetTimeSpanTimeseriesCollectionByCatalogIsNull(  );
    TimeSpanTimeseriesObject getTimeSpanTimeseriesByCatalogAndName( Guid catalog, String name );
    List<TimeSpanTimeseriesObject> qetTimeSpanTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // UInt16Timeseries queries
    // ---------------------------------------------------------------------
    UInt16TimeseriesObject getUInt16TimeseriesById( Guid id );
    List<UInt16TimeseriesObject> getUInt16TimeseriesCollection( );
    List<UInt16TimeseriesObject> getUInt16TimeseriesCollectionByCatalog( Guid catalog );
    List<UInt16TimeseriesObject> qetUInt16TimeseriesCollectionByCatalogIsNull(  );
    UInt16TimeseriesObject getUInt16TimeseriesByCatalogAndName( Guid catalog, String name );
    List<UInt16TimeseriesObject> qetUInt16TimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // UInt32Timeseries queries
    // ---------------------------------------------------------------------
    UInt32TimeseriesObject getUInt32TimeseriesById( Guid id );
    List<UInt32TimeseriesObject> getUInt32TimeseriesCollection( );
    List<UInt32TimeseriesObject> getUInt32TimeseriesCollectionByCatalog( Guid catalog );
    List<UInt32TimeseriesObject> qetUInt32TimeseriesCollectionByCatalogIsNull(  );
    UInt32TimeseriesObject getUInt32TimeseriesByCatalogAndName( Guid catalog, String name );
    List<UInt32TimeseriesObject> qetUInt32TimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // RadomeStatusTimeseries queries
    // ---------------------------------------------------------------------
    RadomeStatusTimeseriesObject getRadomeStatusTimeseriesById( Guid id );
    List<RadomeStatusTimeseriesObject> getRadomeStatusTimeseriesCollection( );
    List<RadomeStatusTimeseriesObject> getRadomeStatusTimeseriesCollectionByCatalog( Guid catalog );
    List<RadomeStatusTimeseriesObject> qetRadomeStatusTimeseriesCollectionByCatalogIsNull(  );
    RadomeStatusTimeseriesObject getRadomeStatusTimeseriesByCatalogAndName( Guid catalog, String name );
    List<RadomeStatusTimeseriesObject> qetRadomeStatusTimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // UInt64Timeseries queries
    // ---------------------------------------------------------------------
    UInt64TimeseriesObject getUInt64TimeseriesById( Guid id );
    List<UInt64TimeseriesObject> getUInt64TimeseriesCollection( );
    List<UInt64TimeseriesObject> getUInt64TimeseriesCollectionByCatalog( Guid catalog );
    List<UInt64TimeseriesObject> qetUInt64TimeseriesCollectionByCatalogIsNull(  );
    UInt64TimeseriesObject getUInt64TimeseriesByCatalogAndName( Guid catalog, String name );
    List<UInt64TimeseriesObject> qetUInt64TimeseriesCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // TimeseriesCatalog queries
    // ---------------------------------------------------------------------
    TimeseriesCatalogObject getTimeseriesCatalogById( Guid id );
    List<TimeseriesCatalogObject> getTimeseriesCatalogCollection( );
    List<TimeseriesCatalogObject> getTimeseriesCatalogCollectionByCatalog( Guid catalog );
    List<TimeseriesCatalogObject> qetTimeseriesCatalogCollectionByCatalogIsNull(  );
    TimeseriesCatalogObject getTimeseriesCatalogByCatalogAndName( Guid catalog, String name );
    List<TimeseriesCatalogObject> qetTimeseriesCatalogCollectionByCatalogIsNullAndName( String name );
    // ---------------------------------------------------------------------
    // TimeseriesInfo queries
    // ---------------------------------------------------------------------
    TimeseriesInfoObject getTimeseriesInfoById( Guid id );
    List<TimeseriesInfoObject> getTimeseriesInfoCollection( );
    // ---------------------------------------------------------------------
    // TimeSpanTimeseriesValue queries
    // ---------------------------------------------------------------------
    TimeSpanTimeseriesValueObject getTimeSpanTimeseriesValueById( Guid id );
    List<TimeSpanTimeseriesValueObject> getTimeSpanTimeseriesValueCollection( );
    List<TimeSpanTimeseriesValueObject> getTimeSpanTimeseriesValueCollectionByTimeseries( Guid timeseries );
    TimeSpanTimeseriesValueObject getTimeSpanTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
    TimeSpanTimeseriesValueObject getTimeSpanTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
    List<TimeSpanTimeseriesValueObject> getTimeSpanTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
    List<TimeSpanTimeseriesValueObject> getTimeSpanTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
    List<TimeSpanTimeseriesValueObject> getTimeSpanTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
    List<TimeSpanTimeseriesValueObject> getTimeSpanTimeseriesValueCollectionByTimestamp( DateTime timestamp );
    List<TimeSpanTimeseriesValueObject> getTimeSpanTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
    List<TimeSpanTimeseriesValueObject> getTimeSpanTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
    List<TimeSpanTimeseriesValueObject> getTimeSpanTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
    List<TimeSpanTimeseriesValueObject> getTimeSpanTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // TrackableItemTrackLink queries
    // ---------------------------------------------------------------------
    TrackableItemTrackLinkObject getTrackableItemTrackLinkById( Guid id );
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollection( );
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByItem( Guid item );
    TrackableItemTrackLinkObject getTrackableItemTrackLinkByItemAndStart( Guid item, DateTime start );
    TrackableItemTrackLinkObject getTrackableItemTrackLinkByItemAtStart( Guid item, DateTime start );
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkByItemFromStart( Guid item, DateTime start );
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkByItemUntilStart( Guid item, DateTime start );
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkByItemOverStart( Guid item, DateTime fromStart, DateTime untilStart );
    List<TrackableItemTrackLinkObject> qetTrackableItemTrackLinkCollectionByItem(  );
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByItemAndEnd( Guid item, DateTime end );
    List<TrackableItemTrackLinkObject> qetTrackableItemTrackLinkCollectionByItemAndEndIsNull( Guid item );
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByItemAtEnd( Guid item, DateTime end );
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByItemFromEnd( Guid item, DateTime end );
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByItemUntilEnd( Guid item, DateTime end );
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByItemOverEnd( Guid item, DateTime fromEnd, DateTime untilEnd );
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByTrack( Guid track );
    TrackableItemTrackLinkObject getTrackableItemTrackLinkByTrackAndStart( Guid track, DateTime start );
    TrackableItemTrackLinkObject getTrackableItemTrackLinkByTrackAtStart( Guid track, DateTime start );
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkByTrackFromStart( Guid track, DateTime start );
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkByTrackUntilStart( Guid track, DateTime start );
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkByTrackOverStart( Guid track, DateTime fromStart, DateTime untilStart );
    List<TrackableItemTrackLinkObject> qetTrackableItemTrackLinkCollectionByTrack(  );
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByTrackAndEnd( Guid track, DateTime end );
    List<TrackableItemTrackLinkObject> qetTrackableItemTrackLinkCollectionByTrackAndEndIsNull( Guid track );
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByTrackAtEnd( Guid track, DateTime end );
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByTrackFromEnd( Guid track, DateTime end );
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByTrackUntilEnd( Guid track, DateTime end );
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByTrackOverEnd( Guid track, DateTime fromEnd, DateTime untilEnd );
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByStart( DateTime start );
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionAtStart( DateTime start );
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionFromStart( DateTime start );
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionUntilStart( DateTime start );
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionOverStart( DateTime fromStart, DateTime untilStart );
    // ---------------------------------------------------------------------
    // TrackBase queries
    // ---------------------------------------------------------------------
    TrackBaseObject getTrackBaseById( Guid id );
    List<TrackBaseObject> getTrackBaseCollection( );
    List<TrackBaseObject> getTrackBaseCollectionByTracker( Guid tracker );
    List<TrackBaseObject> getTrackBaseCollectionByTrackerAndTrackNumber( Guid tracker, long trackNumber );
    List<TrackBaseObject> getTrackBaseCollectionByTrackerFromTrackNumber( Guid tracker, long trackNumber );
    List<TrackBaseObject> getTrackBaseCollectionByTrackerUntilTrackNumber( Guid tracker, long trackNumber );
    List<TrackBaseObject> getTrackBaseCollectionByTrackerOverTrackNumber( Guid tracker, long fromTrackNumber, long untilTrackNumber );
    TrackBaseObject getTrackBaseByTrackerTrackNumberAndTimestamp( Guid tracker, long trackNumber, DateTime timestamp );
    TrackBaseObject getTrackBaseByTrackerTrackNumberAtTimestamp( Guid tracker, long trackNumber, DateTime timestamp );
    List<TrackBaseObject> getTrackBaseByTrackerTrackNumberFromTimestamp( Guid tracker, long trackNumber, DateTime timestamp );
    List<TrackBaseObject> getTrackBaseByTrackerTrackNumberUntilTimestamp( Guid tracker, long trackNumber, DateTime timestamp );
    List<TrackBaseObject> getTrackBaseByTrackerTrackNumberOverTimestamp( Guid tracker, long trackNumber, DateTime fromTimestamp, DateTime untilTimestamp );
    List<TrackBaseObject> getTrackBaseCollectionByTrackerAndTimestamp( Guid tracker, DateTime timestamp );
    List<TrackBaseObject> getTrackBaseCollectionByTrackerAtTimestamp( Guid tracker, DateTime timestamp );
    List<TrackBaseObject> getTrackBaseCollectionByTrackerFromTimestamp( Guid tracker, DateTime timestamp );
    List<TrackBaseObject> getTrackBaseCollectionByTrackerUntilTimestamp( Guid tracker, DateTime timestamp );
    List<TrackBaseObject> getTrackBaseCollectionByTrackerOverTimestamp( Guid tracker, DateTime fromTimestamp, DateTime untilTimestamp );
    List<TrackBaseObject> getTrackBaseCollectionByTrackNumber( long trackNumber );
    List<TrackBaseObject> getTrackBaseCollectionFromTrackNumber( long trackNumber );
    List<TrackBaseObject> getTrackBaseCollectionUntilTrackNumber( long trackNumber );
    List<TrackBaseObject> getTrackBaseCollectionOverTrackNumber( long fromTrackNumber, long untilTrackNumber );
    List<TrackBaseObject> getTrackBaseCollectionByTimestamp( DateTime timestamp );
    List<TrackBaseObject> getTrackBaseCollectionAtTimestamp( DateTime timestamp );
    List<TrackBaseObject> getTrackBaseCollectionFromTimestamp( DateTime timestamp );
    List<TrackBaseObject> getTrackBaseCollectionUntilTimestamp( DateTime timestamp );
    List<TrackBaseObject> getTrackBaseCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // Track queries
    // ---------------------------------------------------------------------
    TrackObject getTrackById( Guid id );
    List<TrackObject> getTrackCollection( );
    List<TrackObject> getTrackCollectionByTracker( Guid tracker );
    List<TrackObject> getTrackCollectionByTrackerAndTrackNumber( Guid tracker, long trackNumber );
    List<TrackObject> getTrackCollectionByTrackerFromTrackNumber( Guid tracker, long trackNumber );
    List<TrackObject> getTrackCollectionByTrackerUntilTrackNumber( Guid tracker, long trackNumber );
    List<TrackObject> getTrackCollectionByTrackerOverTrackNumber( Guid tracker, long fromTrackNumber, long untilTrackNumber );
    TrackObject getTrackByTrackerTrackNumberAndTimestamp( Guid tracker, long trackNumber, DateTime timestamp );
    TrackObject getTrackByTrackerTrackNumberAtTimestamp( Guid tracker, long trackNumber, DateTime timestamp );
    List<TrackObject> getTrackByTrackerTrackNumberFromTimestamp( Guid tracker, long trackNumber, DateTime timestamp );
    List<TrackObject> getTrackByTrackerTrackNumberUntilTimestamp( Guid tracker, long trackNumber, DateTime timestamp );
    List<TrackObject> getTrackByTrackerTrackNumberOverTimestamp( Guid tracker, long trackNumber, DateTime fromTimestamp, DateTime untilTimestamp );
    List<TrackObject> getTrackCollectionByTrackerAndTimestamp( Guid tracker, DateTime timestamp );
    List<TrackObject> getTrackCollectionByTrackerAtTimestamp( Guid tracker, DateTime timestamp );
    List<TrackObject> getTrackCollectionByTrackerFromTimestamp( Guid tracker, DateTime timestamp );
    List<TrackObject> getTrackCollectionByTrackerUntilTimestamp( Guid tracker, DateTime timestamp );
    List<TrackObject> getTrackCollectionByTrackerOverTimestamp( Guid tracker, DateTime fromTimestamp, DateTime untilTimestamp );
    List<TrackObject> getTrackCollectionByTrackNumber( long trackNumber );
    List<TrackObject> getTrackCollectionFromTrackNumber( long trackNumber );
    List<TrackObject> getTrackCollectionUntilTrackNumber( long trackNumber );
    List<TrackObject> getTrackCollectionOverTrackNumber( long fromTrackNumber, long untilTrackNumber );
    List<TrackObject> getTrackCollectionByTimestamp( DateTime timestamp );
    List<TrackObject> getTrackCollectionAtTimestamp( DateTime timestamp );
    List<TrackObject> getTrackCollectionFromTimestamp( DateTime timestamp );
    List<TrackObject> getTrackCollectionUntilTimestamp( DateTime timestamp );
    List<TrackObject> getTrackCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // Track3D queries
    // ---------------------------------------------------------------------
    Track3DObject getTrack3DById( Guid id );
    List<Track3DObject> getTrack3DCollection( );
    List<Track3DObject> getTrack3DCollectionByTracker( Guid tracker );
    List<Track3DObject> getTrack3DCollectionByTrackerAndTrackNumber( Guid tracker, long trackNumber );
    List<Track3DObject> getTrack3DCollectionByTrackerFromTrackNumber( Guid tracker, long trackNumber );
    List<Track3DObject> getTrack3DCollectionByTrackerUntilTrackNumber( Guid tracker, long trackNumber );
    List<Track3DObject> getTrack3DCollectionByTrackerOverTrackNumber( Guid tracker, long fromTrackNumber, long untilTrackNumber );
    Track3DObject getTrack3DByTrackerTrackNumberAndTimestamp( Guid tracker, long trackNumber, DateTime timestamp );
    Track3DObject getTrack3DByTrackerTrackNumberAtTimestamp( Guid tracker, long trackNumber, DateTime timestamp );
    List<Track3DObject> getTrack3DByTrackerTrackNumberFromTimestamp( Guid tracker, long trackNumber, DateTime timestamp );
    List<Track3DObject> getTrack3DByTrackerTrackNumberUntilTimestamp( Guid tracker, long trackNumber, DateTime timestamp );
    List<Track3DObject> getTrack3DByTrackerTrackNumberOverTimestamp( Guid tracker, long trackNumber, DateTime fromTimestamp, DateTime untilTimestamp );
    List<Track3DObject> getTrack3DCollectionByTrackerAndTimestamp( Guid tracker, DateTime timestamp );
    List<Track3DObject> getTrack3DCollectionByTrackerAtTimestamp( Guid tracker, DateTime timestamp );
    List<Track3DObject> getTrack3DCollectionByTrackerFromTimestamp( Guid tracker, DateTime timestamp );
    List<Track3DObject> getTrack3DCollectionByTrackerUntilTimestamp( Guid tracker, DateTime timestamp );
    List<Track3DObject> getTrack3DCollectionByTrackerOverTimestamp( Guid tracker, DateTime fromTimestamp, DateTime untilTimestamp );
    List<Track3DObject> getTrack3DCollectionByTrackNumber( long trackNumber );
    List<Track3DObject> getTrack3DCollectionFromTrackNumber( long trackNumber );
    List<Track3DObject> getTrack3DCollectionUntilTrackNumber( long trackNumber );
    List<Track3DObject> getTrack3DCollectionOverTrackNumber( long fromTrackNumber, long untilTrackNumber );
    List<Track3DObject> getTrack3DCollectionByTimestamp( DateTime timestamp );
    List<Track3DObject> getTrack3DCollectionAtTimestamp( DateTime timestamp );
    List<Track3DObject> getTrack3DCollectionFromTimestamp( DateTime timestamp );
    List<Track3DObject> getTrack3DCollectionUntilTimestamp( DateTime timestamp );
    List<Track3DObject> getTrack3DCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // TrackerFilterParameters queries
    // ---------------------------------------------------------------------
    TrackerFilterParametersObject getTrackerFilterParametersById( Guid id );
    List<TrackerFilterParametersObject> getTrackerFilterParametersCollection( );
    List<TrackerFilterParametersObject> getTrackerFilterParametersCollectionByTracker( Guid tracker );
    TrackerFilterParametersObject getTrackerFilterParametersByTrackerAndName( Guid tracker, String name );
    // ---------------------------------------------------------------------
    // TrackerFilterParametersConfiguration queries
    // ---------------------------------------------------------------------
    TrackerFilterParametersConfigurationObject getTrackerFilterParametersConfigurationById( Guid id );
    List<TrackerFilterParametersConfigurationObject> getTrackerFilterParametersConfigurationCollection( );
    List<TrackerFilterParametersConfigurationObject> getTrackerFilterParametersConfigurationCollectionByParameters( Guid parameters );
    TrackerFilterParametersConfigurationObject getTrackerFilterParametersConfigurationByParametersAndTimestamp( Guid parameters, DateTime timestamp );
    TrackerFilterParametersConfigurationObject getTrackerFilterParametersConfigurationByParametersAtTimestamp( Guid parameters, DateTime timestamp );
    List<TrackerFilterParametersConfigurationObject> getTrackerFilterParametersConfigurationByParametersFromTimestamp( Guid parameters, DateTime timestamp );
    List<TrackerFilterParametersConfigurationObject> getTrackerFilterParametersConfigurationByParametersUntilTimestamp( Guid parameters, DateTime timestamp );
    List<TrackerFilterParametersConfigurationObject> getTrackerFilterParametersConfigurationByParametersOverTimestamp( Guid parameters, DateTime fromTimestamp, DateTime untilTimestamp );
    List<TrackerFilterParametersConfigurationObject> getTrackerFilterParametersConfigurationCollectionByTimestamp( DateTime timestamp );
    List<TrackerFilterParametersConfigurationObject> getTrackerFilterParametersConfigurationCollectionAtTimestamp( DateTime timestamp );
    List<TrackerFilterParametersConfigurationObject> getTrackerFilterParametersConfigurationCollectionFromTimestamp( DateTime timestamp );
    List<TrackerFilterParametersConfigurationObject> getTrackerFilterParametersConfigurationCollectionUntilTimestamp( DateTime timestamp );
    List<TrackerFilterParametersConfigurationObject> getTrackerFilterParametersConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // TrackInfo queries
    // ---------------------------------------------------------------------
    TrackInfoObject getTrackInfoById( Guid id );
    List<TrackInfoObject> getTrackInfoCollection( );
    // ---------------------------------------------------------------------
    // TrackingServiceOptions queries
    // ---------------------------------------------------------------------
    TrackingServiceOptionsObject getTrackingServiceOptionsById( Guid id );
    List<TrackingServiceOptionsObject> getTrackingServiceOptionsCollection( );
    TrackingServiceOptionsObject getTrackingServiceOptionsByTimestamp( DateTime timestamp );
    TrackingServiceOptionsObject getTrackingServiceOptionsAtTimestamp( DateTime timestamp );
    List<TrackingServiceOptionsObject> getTrackingServiceOptionsFromTimestamp( DateTime timestamp );
    List<TrackingServiceOptionsObject> getTrackingServiceOptionsUntilTimestamp( DateTime timestamp );
    List<TrackingServiceOptionsObject> getTrackingServiceOptionsOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // TrackLink queries
    // ---------------------------------------------------------------------
    TrackLinkObject getTrackLinkById( Guid id );
    List<TrackLinkObject> getTrackLinkCollection( );
    List<TrackLinkObject> getTrackLinkCollectionByPrimary( Guid primary );
    List<TrackLinkObject> getTrackLinkCollectionByPrimaryAndStart( Guid primary, DateTime start );
    List<TrackLinkObject> getTrackLinkCollectionByPrimaryAtStart( Guid primary, DateTime start );
    List<TrackLinkObject> getTrackLinkCollectionByPrimaryFromStart( Guid primary, DateTime start );
    List<TrackLinkObject> getTrackLinkCollectionByPrimaryUntilStart( Guid primary, DateTime start );
    List<TrackLinkObject> getTrackLinkCollectionByPrimaryOverStart( Guid primary, DateTime fromStart, DateTime untilStart );
    List<TrackLinkObject> getTrackLinkCollectionBySecondary( Guid secondary );
    List<TrackLinkObject> getTrackLinkCollectionBySecondaryAndStart( Guid secondary, DateTime start );
    List<TrackLinkObject> getTrackLinkCollectionBySecondaryAtStart( Guid secondary, DateTime start );
    List<TrackLinkObject> getTrackLinkCollectionBySecondaryFromStart( Guid secondary, DateTime start );
    List<TrackLinkObject> getTrackLinkCollectionBySecondaryUntilStart( Guid secondary, DateTime start );
    List<TrackLinkObject> getTrackLinkCollectionBySecondaryOverStart( Guid secondary, DateTime fromStart, DateTime untilStart );
    List<TrackLinkObject> getTrackLinkCollectionByStart( DateTime start );
    List<TrackLinkObject> getTrackLinkCollectionAtStart( DateTime start );
    List<TrackLinkObject> getTrackLinkCollectionFromStart( DateTime start );
    List<TrackLinkObject> getTrackLinkCollectionUntilStart( DateTime start );
    List<TrackLinkObject> getTrackLinkCollectionOverStart( DateTime fromStart, DateTime untilStart );
    // ---------------------------------------------------------------------
    // TrackValue queries
    // ---------------------------------------------------------------------
    TrackValueObject getTrackValueById( Guid id );
    List<TrackValueObject> getTrackValueCollection( );
    List<TrackValueObject> getTrackValueCollectionByTrack( Guid track );
    TrackValueObject getTrackValueByTrackAndTimestamp( Guid track, DateTime timestamp );
    TrackValueObject getTrackValueByTrackAtTimestamp( Guid track, DateTime timestamp );
    List<TrackValueObject> getTrackValueByTrackFromTimestamp( Guid track, DateTime timestamp );
    List<TrackValueObject> getTrackValueByTrackUntilTimestamp( Guid track, DateTime timestamp );
    List<TrackValueObject> getTrackValueByTrackOverTimestamp( Guid track, DateTime fromTimestamp, DateTime untilTimestamp );
    List<TrackValueObject> getTrackValueCollectionByTimestamp( DateTime timestamp );
    List<TrackValueObject> getTrackValueCollectionAtTimestamp( DateTime timestamp );
    List<TrackValueObject> getTrackValueCollectionFromTimestamp( DateTime timestamp );
    List<TrackValueObject> getTrackValueCollectionUntilTimestamp( DateTime timestamp );
    List<TrackValueObject> getTrackValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // TrackValue3D queries
    // ---------------------------------------------------------------------
    TrackValue3DObject getTrackValue3DById( Guid id );
    List<TrackValue3DObject> getTrackValue3DCollection( );
    List<TrackValue3DObject> getTrackValue3DCollectionByTrack( Guid track );
    TrackValue3DObject getTrackValue3DByTrackAndTimestamp( Guid track, DateTime timestamp );
    TrackValue3DObject getTrackValue3DByTrackAtTimestamp( Guid track, DateTime timestamp );
    List<TrackValue3DObject> getTrackValue3DByTrackFromTimestamp( Guid track, DateTime timestamp );
    List<TrackValue3DObject> getTrackValue3DByTrackUntilTimestamp( Guid track, DateTime timestamp );
    List<TrackValue3DObject> getTrackValue3DByTrackOverTimestamp( Guid track, DateTime fromTimestamp, DateTime untilTimestamp );
    List<TrackValue3DObject> getTrackValue3DCollectionByTimestamp( DateTime timestamp );
    List<TrackValue3DObject> getTrackValue3DCollectionAtTimestamp( DateTime timestamp );
    List<TrackValue3DObject> getTrackValue3DCollectionFromTimestamp( DateTime timestamp );
    List<TrackValue3DObject> getTrackValue3DCollectionUntilTimestamp( DateTime timestamp );
    List<TrackValue3DObject> getTrackValue3DCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // UInt16TimeseriesValue queries
    // ---------------------------------------------------------------------
    UInt16TimeseriesValueObject getUInt16TimeseriesValueById( Guid id );
    List<UInt16TimeseriesValueObject> getUInt16TimeseriesValueCollection( );
    List<UInt16TimeseriesValueObject> getUInt16TimeseriesValueCollectionByTimeseries( Guid timeseries );
    UInt16TimeseriesValueObject getUInt16TimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
    UInt16TimeseriesValueObject getUInt16TimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
    List<UInt16TimeseriesValueObject> getUInt16TimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
    List<UInt16TimeseriesValueObject> getUInt16TimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
    List<UInt16TimeseriesValueObject> getUInt16TimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
    List<UInt16TimeseriesValueObject> getUInt16TimeseriesValueCollectionByTimestamp( DateTime timestamp );
    List<UInt16TimeseriesValueObject> getUInt16TimeseriesValueCollectionAtTimestamp( DateTime timestamp );
    List<UInt16TimeseriesValueObject> getUInt16TimeseriesValueCollectionFromTimestamp( DateTime timestamp );
    List<UInt16TimeseriesValueObject> getUInt16TimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
    List<UInt16TimeseriesValueObject> getUInt16TimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // UInt32TimeseriesValue queries
    // ---------------------------------------------------------------------
    UInt32TimeseriesValueObject getUInt32TimeseriesValueById( Guid id );
    List<UInt32TimeseriesValueObject> getUInt32TimeseriesValueCollection( );
    List<UInt32TimeseriesValueObject> getUInt32TimeseriesValueCollectionByTimeseries( Guid timeseries );
    UInt32TimeseriesValueObject getUInt32TimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
    UInt32TimeseriesValueObject getUInt32TimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
    List<UInt32TimeseriesValueObject> getUInt32TimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
    List<UInt32TimeseriesValueObject> getUInt32TimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
    List<UInt32TimeseriesValueObject> getUInt32TimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
    List<UInt32TimeseriesValueObject> getUInt32TimeseriesValueCollectionByTimestamp( DateTime timestamp );
    List<UInt32TimeseriesValueObject> getUInt32TimeseriesValueCollectionAtTimestamp( DateTime timestamp );
    List<UInt32TimeseriesValueObject> getUInt32TimeseriesValueCollectionFromTimestamp( DateTime timestamp );
    List<UInt32TimeseriesValueObject> getUInt32TimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
    List<UInt32TimeseriesValueObject> getUInt32TimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // UInt64TimeseriesValue queries
    // ---------------------------------------------------------------------
    UInt64TimeseriesValueObject getUInt64TimeseriesValueById( Guid id );
    List<UInt64TimeseriesValueObject> getUInt64TimeseriesValueCollection( );
    List<UInt64TimeseriesValueObject> getUInt64TimeseriesValueCollectionByTimeseries( Guid timeseries );
    UInt64TimeseriesValueObject getUInt64TimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
    UInt64TimeseriesValueObject getUInt64TimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
    List<UInt64TimeseriesValueObject> getUInt64TimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
    List<UInt64TimeseriesValueObject> getUInt64TimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
    List<UInt64TimeseriesValueObject> getUInt64TimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
    List<UInt64TimeseriesValueObject> getUInt64TimeseriesValueCollectionByTimestamp( DateTime timestamp );
    List<UInt64TimeseriesValueObject> getUInt64TimeseriesValueCollectionAtTimestamp( DateTime timestamp );
    List<UInt64TimeseriesValueObject> getUInt64TimeseriesValueCollectionFromTimestamp( DateTime timestamp );
    List<UInt64TimeseriesValueObject> getUInt64TimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
    List<UInt64TimeseriesValueObject> getUInt64TimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // VehicleType queries
    // ---------------------------------------------------------------------
    VehicleTypeObject getVehicleTypeById( Guid id );
    List<VehicleTypeObject> getVehicleTypeCollection( );
    VehicleTypeObject getVehicleTypeByName( String name );
    // ---------------------------------------------------------------------
    // VesselType queries
    // ---------------------------------------------------------------------
    VesselTypeObject getVesselTypeById( Guid id );
    List<VesselTypeObject> getVesselTypeCollection( );
    VesselTypeObject getVesselTypeByName( String name );
    VesselTypeObject getVesselTypeByCode( int code );
    List<VesselTypeObject> getVesselTypeFromCode( int code );
    List<VesselTypeObject> getVesselTypeUntilCode( int code );
    List<VesselTypeObject> getVesselTypeOverCode( int fromCode, int untilCode );
    // ---------------------------------------------------------------------
    // View queries
    // ---------------------------------------------------------------------
    ViewObject getViewById( Guid id );
    List<ViewObject> getViewCollection( );
    ViewObject getViewByName( String name );
    // ---------------------------------------------------------------------
    // ViewCameraLink queries
    // ---------------------------------------------------------------------
    ViewCameraLinkObject getViewCameraLinkById( Guid id );
    List<ViewCameraLinkObject> getViewCameraLinkCollection( );
    List<ViewCameraLinkObject> getViewCameraLinkCollectionByView( Guid view );
    ViewCameraLinkObject getViewCameraLinkByViewAndStart( Guid view, DateTime start );
    ViewCameraLinkObject getViewCameraLinkByViewAtStart( Guid view, DateTime start );
    List<ViewCameraLinkObject> getViewCameraLinkByViewFromStart( Guid view, DateTime start );
    List<ViewCameraLinkObject> getViewCameraLinkByViewUntilStart( Guid view, DateTime start );
    List<ViewCameraLinkObject> getViewCameraLinkByViewOverStart( Guid view, DateTime fromStart, DateTime untilStart );
    List<ViewCameraLinkObject> getViewCameraLinkCollectionByCamera( Guid camera );
    ViewCameraLinkObject getViewCameraLinkByCameraAndStart( Guid camera, DateTime start );
    ViewCameraLinkObject getViewCameraLinkByCameraAtStart( Guid camera, DateTime start );
    List<ViewCameraLinkObject> getViewCameraLinkByCameraFromStart( Guid camera, DateTime start );
    List<ViewCameraLinkObject> getViewCameraLinkByCameraUntilStart( Guid camera, DateTime start );
    List<ViewCameraLinkObject> getViewCameraLinkByCameraOverStart( Guid camera, DateTime fromStart, DateTime untilStart );
    List<ViewCameraLinkObject> getViewCameraLinkCollectionByStart( DateTime start );
    List<ViewCameraLinkObject> getViewCameraLinkCollectionAtStart( DateTime start );
    List<ViewCameraLinkObject> getViewCameraLinkCollectionFromStart( DateTime start );
    List<ViewCameraLinkObject> getViewCameraLinkCollectionUntilStart( DateTime start );
    List<ViewCameraLinkObject> getViewCameraLinkCollectionOverStart( DateTime fromStart, DateTime untilStart );
    // ---------------------------------------------------------------------
    // ViewTrackerLink queries
    // ---------------------------------------------------------------------
    ViewTrackerLinkObject getViewTrackerLinkById( Guid id );
    List<ViewTrackerLinkObject> getViewTrackerLinkCollection( );
    List<ViewTrackerLinkObject> getViewTrackerLinkCollectionByView( Guid view );
    ViewTrackerLinkObject getViewTrackerLinkByViewAndStart( Guid view, DateTime start );
    ViewTrackerLinkObject getViewTrackerLinkByViewAtStart( Guid view, DateTime start );
    List<ViewTrackerLinkObject> getViewTrackerLinkByViewFromStart( Guid view, DateTime start );
    List<ViewTrackerLinkObject> getViewTrackerLinkByViewUntilStart( Guid view, DateTime start );
    List<ViewTrackerLinkObject> getViewTrackerLinkByViewOverStart( Guid view, DateTime fromStart, DateTime untilStart );
    List<ViewTrackerLinkObject> getViewTrackerLinkCollectionByTracker( Guid tracker );
    ViewTrackerLinkObject getViewTrackerLinkByTrackerAndStart( Guid tracker, DateTime start );
    ViewTrackerLinkObject getViewTrackerLinkByTrackerAtStart( Guid tracker, DateTime start );
    List<ViewTrackerLinkObject> getViewTrackerLinkByTrackerFromStart( Guid tracker, DateTime start );
    List<ViewTrackerLinkObject> getViewTrackerLinkByTrackerUntilStart( Guid tracker, DateTime start );
    List<ViewTrackerLinkObject> getViewTrackerLinkByTrackerOverStart( Guid tracker, DateTime fromStart, DateTime untilStart );
    List<ViewTrackerLinkObject> getViewTrackerLinkCollectionByStart( DateTime start );
    List<ViewTrackerLinkObject> getViewTrackerLinkCollectionAtStart( DateTime start );
    List<ViewTrackerLinkObject> getViewTrackerLinkCollectionFromStart( DateTime start );
    List<ViewTrackerLinkObject> getViewTrackerLinkCollectionUntilStart( DateTime start );
    List<ViewTrackerLinkObject> getViewTrackerLinkCollectionOverStart( DateTime fromStart, DateTime untilStart );
    // ---------------------------------------------------------------------
    // WeatherStationCommand queries
    // ---------------------------------------------------------------------
    WeatherStationCommandObject getWeatherStationCommandById( Guid id );
    List<WeatherStationCommandObject> getWeatherStationCommandCollection( );
    List<WeatherStationCommandObject> getWeatherStationCommandCollectionByWeatherStation( Guid weatherStation );
    List<WeatherStationCommandObject> getWeatherStationCommandCollectionByWeatherStationAndTimestamp( Guid weatherStation, DateTime timestamp );
    List<WeatherStationCommandObject> getWeatherStationCommandCollectionByWeatherStationAtTimestamp( Guid weatherStation, DateTime timestamp );
    List<WeatherStationCommandObject> getWeatherStationCommandCollectionByWeatherStationFromTimestamp( Guid weatherStation, DateTime timestamp );
    List<WeatherStationCommandObject> getWeatherStationCommandCollectionByWeatherStationUntilTimestamp( Guid weatherStation, DateTime timestamp );
    List<WeatherStationCommandObject> getWeatherStationCommandCollectionByWeatherStationOverTimestamp( Guid weatherStation, DateTime fromTimestamp, DateTime untilTimestamp );
    List<WeatherStationCommandObject> getWeatherStationCommandCollectionByTimestamp( DateTime timestamp );
    List<WeatherStationCommandObject> getWeatherStationCommandCollectionAtTimestamp( DateTime timestamp );
    List<WeatherStationCommandObject> getWeatherStationCommandCollectionFromTimestamp( DateTime timestamp );
    List<WeatherStationCommandObject> getWeatherStationCommandCollectionUntilTimestamp( DateTime timestamp );
    List<WeatherStationCommandObject> getWeatherStationCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    List<WeatherStationCommandObject> getWeatherStationCommandCollectionByReply( Guid reply );
    List<WeatherStationCommandObject> qetWeatherStationCommandCollectionByReplyIsNull(  );
    // ---------------------------------------------------------------------
    // WeatherStationCommandReply queries
    // ---------------------------------------------------------------------
    WeatherStationCommandReplyObject getWeatherStationCommandReplyById( Guid id );
    List<WeatherStationCommandReplyObject> getWeatherStationCommandReplyCollection( );
    List<WeatherStationCommandReplyObject> getWeatherStationCommandReplyCollectionByWeatherStation( Guid weatherStation );
    List<WeatherStationCommandReplyObject> getWeatherStationCommandReplyCollectionByWeatherStationAndTimestamp( Guid weatherStation, DateTime timestamp );
    List<WeatherStationCommandReplyObject> getWeatherStationCommandReplyCollectionByWeatherStationAtTimestamp( Guid weatherStation, DateTime timestamp );
    List<WeatherStationCommandReplyObject> getWeatherStationCommandReplyCollectionByWeatherStationFromTimestamp( Guid weatherStation, DateTime timestamp );
    List<WeatherStationCommandReplyObject> getWeatherStationCommandReplyCollectionByWeatherStationUntilTimestamp( Guid weatherStation, DateTime timestamp );
    List<WeatherStationCommandReplyObject> getWeatherStationCommandReplyCollectionByWeatherStationOverTimestamp( Guid weatherStation, DateTime fromTimestamp, DateTime untilTimestamp );
    List<WeatherStationCommandReplyObject> getWeatherStationCommandReplyCollectionByTimestamp( DateTime timestamp );
    List<WeatherStationCommandReplyObject> getWeatherStationCommandReplyCollectionAtTimestamp( DateTime timestamp );
    List<WeatherStationCommandReplyObject> getWeatherStationCommandReplyCollectionFromTimestamp( DateTime timestamp );
    List<WeatherStationCommandReplyObject> getWeatherStationCommandReplyCollectionUntilTimestamp( DateTime timestamp );
    List<WeatherStationCommandReplyObject> getWeatherStationCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    WeatherStationCommandReplyObject getWeatherStationCommandReplyByCommand( Guid command );
    List<WeatherStationCommandReplyObject> qetWeatherStationCommandReplyCollectionByCommandIsNull(  );
    // ---------------------------------------------------------------------
    // WeatherStationConfiguration queries
    // ---------------------------------------------------------------------
    WeatherStationConfigurationObject getWeatherStationConfigurationById( Guid id );
    List<WeatherStationConfigurationObject> getWeatherStationConfigurationCollection( );
    List<WeatherStationConfigurationObject> getWeatherStationConfigurationCollectionByWeatherStation( Guid weatherStation );
    WeatherStationConfigurationObject getWeatherStationConfigurationByWeatherStationAndTimestamp( Guid weatherStation, DateTime timestamp );
    WeatherStationConfigurationObject getWeatherStationConfigurationByWeatherStationAtTimestamp( Guid weatherStation, DateTime timestamp );
    List<WeatherStationConfigurationObject> getWeatherStationConfigurationByWeatherStationFromTimestamp( Guid weatherStation, DateTime timestamp );
    List<WeatherStationConfigurationObject> getWeatherStationConfigurationByWeatherStationUntilTimestamp( Guid weatherStation, DateTime timestamp );
    List<WeatherStationConfigurationObject> getWeatherStationConfigurationByWeatherStationOverTimestamp( Guid weatherStation, DateTime fromTimestamp, DateTime untilTimestamp );
    List<WeatherStationConfigurationObject> getWeatherStationConfigurationCollectionByTimestamp( DateTime timestamp );
    List<WeatherStationConfigurationObject> getWeatherStationConfigurationCollectionAtTimestamp( DateTime timestamp );
    List<WeatherStationConfigurationObject> getWeatherStationConfigurationCollectionFromTimestamp( DateTime timestamp );
    List<WeatherStationConfigurationObject> getWeatherStationConfigurationCollectionUntilTimestamp( DateTime timestamp );
    List<WeatherStationConfigurationObject> getWeatherStationConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // Zone queries
    // ---------------------------------------------------------------------
    ZoneObject getZoneById( Guid id );
    List<ZoneObject> getZoneCollection( );
    ZoneObject getZoneByName( String name );
    // ---------------------------------------------------------------------
    // CircularZone queries
    // ---------------------------------------------------------------------
    CircularZoneObject getCircularZoneById( Guid id );
    List<CircularZoneObject> getCircularZoneCollection( );
    CircularZoneObject getCircularZoneByName( String name );
    // ---------------------------------------------------------------------
    // PolygonZone queries
    // ---------------------------------------------------------------------
    PolygonZoneObject getPolygonZoneById( Guid id );
    List<PolygonZoneObject> getPolygonZoneCollection( );
    PolygonZoneObject getPolygonZoneByName( String name );
    // ---------------------------------------------------------------------
    // ZoneExceptions queries
    // ---------------------------------------------------------------------
    ZoneExceptionsObject getZoneExceptionsById( Guid id );
    List<ZoneExceptionsObject> getZoneExceptionsCollection( );
    List<ZoneExceptionsObject> getZoneExceptionsCollectionByZone( Guid zone );
    ZoneExceptionsObject getZoneExceptionsByZoneAndTimestamp( Guid zone, DateTime timestamp );
    ZoneExceptionsObject getZoneExceptionsByZoneAtTimestamp( Guid zone, DateTime timestamp );
    List<ZoneExceptionsObject> getZoneExceptionsByZoneFromTimestamp( Guid zone, DateTime timestamp );
    List<ZoneExceptionsObject> getZoneExceptionsByZoneUntilTimestamp( Guid zone, DateTime timestamp );
    List<ZoneExceptionsObject> getZoneExceptionsByZoneOverTimestamp( Guid zone, DateTime fromTimestamp, DateTime untilTimestamp );
    List<ZoneExceptionsObject> getZoneExceptionsCollectionByTimestamp( DateTime timestamp );
    List<ZoneExceptionsObject> getZoneExceptionsCollectionAtTimestamp( DateTime timestamp );
    List<ZoneExceptionsObject> getZoneExceptionsCollectionFromTimestamp( DateTime timestamp );
    List<ZoneExceptionsObject> getZoneExceptionsCollectionUntilTimestamp( DateTime timestamp );
    List<ZoneExceptionsObject> getZoneExceptionsCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    // ---------------------------------------------------------------------
    // ZoneExceptionsVesselLink queries
    // ---------------------------------------------------------------------
    ZoneExceptionsVesselLinkObject getZoneExceptionsVesselLinkById( Guid id );
    List<ZoneExceptionsVesselLinkObject> getZoneExceptionsVesselLinkCollection( );
    List<ZoneExceptionsVesselLinkObject> getZoneExceptionsVesselLinkCollectionByZoneExceptions( Guid zoneExceptions );
    ZoneExceptionsVesselLinkObject getZoneExceptionsVesselLinkByZoneExceptionsAndVessel( Guid zoneExceptions, Guid vessel );
    List<ZoneExceptionsVesselLinkObject> getZoneExceptionsVesselLinkCollectionByVessel( Guid vessel );
    // ---------------------------------------------------------------------
    // ZoneTrackAlarm queries
    // ---------------------------------------------------------------------
    ZoneTrackAlarmObject getZoneTrackAlarmById( Guid id );
    List<ZoneTrackAlarmObject> getZoneTrackAlarmCollection( );
    List<ZoneTrackAlarmObject> getZoneTrackAlarmCollectionByTrack( Guid track );
    ZoneTrackAlarmObject getZoneTrackAlarmByTrackAndTimestamp( Guid track, DateTime timestamp );
    ZoneTrackAlarmObject getZoneTrackAlarmByTrackAtTimestamp( Guid track, DateTime timestamp );
    List<ZoneTrackAlarmObject> getZoneTrackAlarmByTrackFromTimestamp( Guid track, DateTime timestamp );
    List<ZoneTrackAlarmObject> getZoneTrackAlarmByTrackUntilTimestamp( Guid track, DateTime timestamp );
    List<ZoneTrackAlarmObject> getZoneTrackAlarmByTrackOverTimestamp( Guid track, DateTime fromTimestamp, DateTime untilTimestamp );
    List<ZoneTrackAlarmObject> getZoneTrackAlarmCollectionByZone( Guid zone );
    List<ZoneTrackAlarmObject> getZoneTrackAlarmCollectionByZoneAndTrack( Guid zone, Guid track );
    ZoneTrackAlarmObject getZoneTrackAlarmByZoneTrackAndTimestamp( Guid zone, Guid track, DateTime timestamp );
    ZoneTrackAlarmObject getZoneTrackAlarmByZoneTrackAtTimestamp( Guid zone, Guid track, DateTime timestamp );
    List<ZoneTrackAlarmObject> getZoneTrackAlarmByZoneTrackFromTimestamp( Guid zone, Guid track, DateTime timestamp );
    List<ZoneTrackAlarmObject> getZoneTrackAlarmByZoneTrackUntilTimestamp( Guid zone, Guid track, DateTime timestamp );
    List<ZoneTrackAlarmObject> getZoneTrackAlarmByZoneTrackOverTimestamp( Guid zone, Guid track, DateTime fromTimestamp, DateTime untilTimestamp );
    List<ZoneTrackAlarmObject> getZoneTrackAlarmCollectionByTimestamp( DateTime timestamp );
    List<ZoneTrackAlarmObject> getZoneTrackAlarmCollectionAtTimestamp( DateTime timestamp );
    List<ZoneTrackAlarmObject> getZoneTrackAlarmCollectionFromTimestamp( DateTime timestamp );
    List<ZoneTrackAlarmObject> getZoneTrackAlarmCollectionUntilTimestamp( DateTime timestamp );
    List<ZoneTrackAlarmObject> getZoneTrackAlarmCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
}
