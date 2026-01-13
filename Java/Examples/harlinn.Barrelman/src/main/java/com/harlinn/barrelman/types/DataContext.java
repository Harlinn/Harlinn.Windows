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
package com.harlinn.barrelman.types;

import java.util.List;
import java.util.ArrayList;
import com.harlinn.common.io.BinaryReader;
import com.harlinn.common.io.BinaryWriter;
import com.harlinn.common.types.AbstractDataObject;
import com.harlinn.common.util.*;

public interface DataContext {
    Guid getSessionId( );
    // ---------------------------------------------------------------------
    // AircraftType queries
    // ---------------------------------------------------------------------
    AircraftTypeObject getAircraftTypeById( Guid id ) throws Exception;
    List<AircraftTypeObject> getAircraftTypeCollection( ) throws Exception;
    AircraftTypeObject getAircraftTypeByName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // AisDeviceCommand queries
    // ---------------------------------------------------------------------
    AisDeviceCommandObject getAisDeviceCommandById( Guid id ) throws Exception;
    List<AisDeviceCommandObject> getAisDeviceCommandCollection( ) throws Exception;
    List<AisDeviceCommandObject> getAisDeviceCommandCollectionByAisDevice( Guid aisDevice ) throws Exception;
    List<AisDeviceCommandObject> getAisDeviceCommandCollectionByAisDeviceAndTimestamp( Guid aisDevice, DateTime timestamp ) throws Exception;
    List<AisDeviceCommandObject> getAisDeviceCommandCollectionByAisDeviceAtTimestamp( Guid aisDevice, DateTime timestamp ) throws Exception;
    List<AisDeviceCommandObject> getAisDeviceCommandCollectionByAisDeviceFromTimestamp( Guid aisDevice, DateTime timestamp ) throws Exception;
    List<AisDeviceCommandObject> getAisDeviceCommandCollectionByAisDeviceUntilTimestamp( Guid aisDevice, DateTime timestamp ) throws Exception;
    List<AisDeviceCommandObject> getAisDeviceCommandCollectionByAisDeviceOverTimestamp( Guid aisDevice, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<AisDeviceCommandObject> getAisDeviceCommandCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<AisDeviceCommandObject> getAisDeviceCommandCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<AisDeviceCommandObject> getAisDeviceCommandCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<AisDeviceCommandObject> getAisDeviceCommandCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<AisDeviceCommandObject> getAisDeviceCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<AisDeviceCommandObject> getAisDeviceCommandCollectionByReply( Guid reply ) throws Exception;
    List<AisDeviceCommandObject> qetAisDeviceCommandCollectionByReplyIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // AisDeviceCommandReply queries
    // ---------------------------------------------------------------------
    AisDeviceCommandReplyObject getAisDeviceCommandReplyById( Guid id ) throws Exception;
    List<AisDeviceCommandReplyObject> getAisDeviceCommandReplyCollection( ) throws Exception;
    List<AisDeviceCommandReplyObject> getAisDeviceCommandReplyCollectionByAisDevice( Guid aisDevice ) throws Exception;
    List<AisDeviceCommandReplyObject> getAisDeviceCommandReplyCollectionByAisDeviceAndTimestamp( Guid aisDevice, DateTime timestamp ) throws Exception;
    List<AisDeviceCommandReplyObject> getAisDeviceCommandReplyCollectionByAisDeviceAtTimestamp( Guid aisDevice, DateTime timestamp ) throws Exception;
    List<AisDeviceCommandReplyObject> getAisDeviceCommandReplyCollectionByAisDeviceFromTimestamp( Guid aisDevice, DateTime timestamp ) throws Exception;
    List<AisDeviceCommandReplyObject> getAisDeviceCommandReplyCollectionByAisDeviceUntilTimestamp( Guid aisDevice, DateTime timestamp ) throws Exception;
    List<AisDeviceCommandReplyObject> getAisDeviceCommandReplyCollectionByAisDeviceOverTimestamp( Guid aisDevice, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<AisDeviceCommandReplyObject> getAisDeviceCommandReplyCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<AisDeviceCommandReplyObject> getAisDeviceCommandReplyCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<AisDeviceCommandReplyObject> getAisDeviceCommandReplyCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<AisDeviceCommandReplyObject> getAisDeviceCommandReplyCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<AisDeviceCommandReplyObject> getAisDeviceCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    AisDeviceCommandReplyObject getAisDeviceCommandReplyByCommand( Guid command ) throws Exception;
    List<AisDeviceCommandReplyObject> qetAisDeviceCommandReplyCollectionByCommandIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // AisDeviceConfiguration queries
    // ---------------------------------------------------------------------
    AisDeviceConfigurationObject getAisDeviceConfigurationById( Guid id ) throws Exception;
    List<AisDeviceConfigurationObject> getAisDeviceConfigurationCollection( ) throws Exception;
    List<AisDeviceConfigurationObject> getAisDeviceConfigurationCollectionByAisDevice( Guid aisDevice ) throws Exception;
    AisDeviceConfigurationObject getAisDeviceConfigurationByAisDeviceAndTimestamp( Guid aisDevice, DateTime timestamp ) throws Exception;
    AisDeviceConfigurationObject getAisDeviceConfigurationByAisDeviceAtTimestamp( Guid aisDevice, DateTime timestamp ) throws Exception;
    List<AisDeviceConfigurationObject> getAisDeviceConfigurationByAisDeviceFromTimestamp( Guid aisDevice, DateTime timestamp ) throws Exception;
    List<AisDeviceConfigurationObject> getAisDeviceConfigurationByAisDeviceUntilTimestamp( Guid aisDevice, DateTime timestamp ) throws Exception;
    List<AisDeviceConfigurationObject> getAisDeviceConfigurationByAisDeviceOverTimestamp( Guid aisDevice, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<AisDeviceConfigurationObject> getAisDeviceConfigurationCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<AisDeviceConfigurationObject> getAisDeviceConfigurationCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<AisDeviceConfigurationObject> getAisDeviceConfigurationCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<AisDeviceConfigurationObject> getAisDeviceConfigurationCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<AisDeviceConfigurationObject> getAisDeviceConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // AisDeviceRawMessage queries
    // ---------------------------------------------------------------------
    AisDeviceRawMessageObject getAisDeviceRawMessageById( Guid id ) throws Exception;
    List<AisDeviceRawMessageObject> getAisDeviceRawMessageCollection( ) throws Exception;
    List<AisDeviceRawMessageObject> getAisDeviceRawMessageCollectionByAisDevice( Guid aisDevice ) throws Exception;
    List<AisDeviceRawMessageObject> getAisDeviceRawMessageCollectionByAisDeviceAndTimestamp( Guid aisDevice, DateTime timestamp ) throws Exception;
    List<AisDeviceRawMessageObject> getAisDeviceRawMessageCollectionByAisDeviceAtTimestamp( Guid aisDevice, DateTime timestamp ) throws Exception;
    List<AisDeviceRawMessageObject> getAisDeviceRawMessageCollectionByAisDeviceFromTimestamp( Guid aisDevice, DateTime timestamp ) throws Exception;
    List<AisDeviceRawMessageObject> getAisDeviceRawMessageCollectionByAisDeviceUntilTimestamp( Guid aisDevice, DateTime timestamp ) throws Exception;
    List<AisDeviceRawMessageObject> getAisDeviceRawMessageCollectionByAisDeviceOverTimestamp( Guid aisDevice, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<AisDeviceRawMessageObject> getAisDeviceRawMessageCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<AisDeviceRawMessageObject> getAisDeviceRawMessageCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<AisDeviceRawMessageObject> getAisDeviceRawMessageCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<AisDeviceRawMessageObject> getAisDeviceRawMessageCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<AisDeviceRawMessageObject> getAisDeviceRawMessageCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // AisDeviceRawSentence queries
    // ---------------------------------------------------------------------
    AisDeviceRawSentenceObject getAisDeviceRawSentenceById( Guid id ) throws Exception;
    List<AisDeviceRawSentenceObject> getAisDeviceRawSentenceCollection( ) throws Exception;
    List<AisDeviceRawSentenceObject> getAisDeviceRawSentenceCollectionByAisDevice( Guid aisDevice ) throws Exception;
    List<AisDeviceRawSentenceObject> getAisDeviceRawSentenceCollectionByAisDeviceAndTimestamp( Guid aisDevice, DateTime timestamp ) throws Exception;
    List<AisDeviceRawSentenceObject> getAisDeviceRawSentenceCollectionByAisDeviceAtTimestamp( Guid aisDevice, DateTime timestamp ) throws Exception;
    List<AisDeviceRawSentenceObject> getAisDeviceRawSentenceCollectionByAisDeviceFromTimestamp( Guid aisDevice, DateTime timestamp ) throws Exception;
    List<AisDeviceRawSentenceObject> getAisDeviceRawSentenceCollectionByAisDeviceUntilTimestamp( Guid aisDevice, DateTime timestamp ) throws Exception;
    List<AisDeviceRawSentenceObject> getAisDeviceRawSentenceCollectionByAisDeviceOverTimestamp( Guid aisDevice, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<AisDeviceRawSentenceObject> getAisDeviceRawSentenceCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<AisDeviceRawSentenceObject> getAisDeviceRawSentenceCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<AisDeviceRawSentenceObject> getAisDeviceRawSentenceCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<AisDeviceRawSentenceObject> getAisDeviceRawSentenceCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<AisDeviceRawSentenceObject> getAisDeviceRawSentenceCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // AisMessage queries
    // ---------------------------------------------------------------------
    AisMessageObject getAisMessageById( Guid id ) throws Exception;
    List<AisMessageObject> getAisMessageCollection( ) throws Exception;
    List<AisMessageObject> getAisMessageCollectionByAisDevice( Guid aisDevice ) throws Exception;
    AisMessageObject getAisMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    AisMessageObject getAisMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisMessageObject> getAisMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisMessageObject> getAisMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisMessageObject> getAisMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisMessageObject> getAisMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisMessageObject> getAisMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisMessageObject> getAisMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisMessageObject> getAisMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisMessageObject> getAisMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisMessageObject> getAisMessageCollectionByMmsi( Guid mmsi ) throws Exception;
    List<AisMessageObject> qetAisMessageCollectionByMmsiIsNull(  ) throws Exception;
    List<AisMessageObject> getAisMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisMessageObject> qetAisMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber ) throws Exception;
    List<AisMessageObject> getAisMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisMessageObject> getAisMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisMessageObject> getAisMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber ) throws Exception;
    // ---------------------------------------------------------------------
    // AidToNavigationReportMessage queries
    // ---------------------------------------------------------------------
    AidToNavigationReportMessageObject getAidToNavigationReportMessageById( Guid id ) throws Exception;
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageCollection( ) throws Exception;
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageCollectionByAisDevice( Guid aisDevice ) throws Exception;
    AidToNavigationReportMessageObject getAidToNavigationReportMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    AidToNavigationReportMessageObject getAidToNavigationReportMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageCollectionByMmsi( Guid mmsi ) throws Exception;
    List<AidToNavigationReportMessageObject> qetAidToNavigationReportMessageCollectionByMmsiIsNull(  ) throws Exception;
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AidToNavigationReportMessageObject> qetAidToNavigationReportMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber ) throws Exception;
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AidToNavigationReportMessageObject> getAidToNavigationReportMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber ) throws Exception;
    // ---------------------------------------------------------------------
    // AisAddressedSafetyRelatedMessage queries
    // ---------------------------------------------------------------------
    AisAddressedSafetyRelatedMessageObject getAisAddressedSafetyRelatedMessageById( Guid id ) throws Exception;
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollection( ) throws Exception;
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollectionByAisDevice( Guid aisDevice ) throws Exception;
    AisAddressedSafetyRelatedMessageObject getAisAddressedSafetyRelatedMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    AisAddressedSafetyRelatedMessageObject getAisAddressedSafetyRelatedMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollectionByMmsi( Guid mmsi ) throws Exception;
    List<AisAddressedSafetyRelatedMessageObject> qetAisAddressedSafetyRelatedMessageCollectionByMmsiIsNull(  ) throws Exception;
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisAddressedSafetyRelatedMessageObject> qetAisAddressedSafetyRelatedMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber ) throws Exception;
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber ) throws Exception;
    List<AisAddressedSafetyRelatedMessageObject> getAisAddressedSafetyRelatedMessageCollectionByDestinationMmsi( Guid destinationMmsi ) throws Exception;
    List<AisAddressedSafetyRelatedMessageObject> qetAisAddressedSafetyRelatedMessageCollectionByDestinationMmsiIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // AisBaseStationReportMessage queries
    // ---------------------------------------------------------------------
    AisBaseStationReportMessageObject getAisBaseStationReportMessageById( Guid id ) throws Exception;
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageCollection( ) throws Exception;
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageCollectionByAisDevice( Guid aisDevice ) throws Exception;
    AisBaseStationReportMessageObject getAisBaseStationReportMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    AisBaseStationReportMessageObject getAisBaseStationReportMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageCollectionByMmsi( Guid mmsi ) throws Exception;
    List<AisBaseStationReportMessageObject> qetAisBaseStationReportMessageCollectionByMmsiIsNull(  ) throws Exception;
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisBaseStationReportMessageObject> qetAisBaseStationReportMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber ) throws Exception;
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisBaseStationReportMessageObject> getAisBaseStationReportMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber ) throws Exception;
    // ---------------------------------------------------------------------
    // AisBinaryAcknowledgeMessage queries
    // ---------------------------------------------------------------------
    AisBinaryAcknowledgeMessageObject getAisBinaryAcknowledgeMessageById( Guid id ) throws Exception;
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageCollection( ) throws Exception;
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageCollectionByAisDevice( Guid aisDevice ) throws Exception;
    AisBinaryAcknowledgeMessageObject getAisBinaryAcknowledgeMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    AisBinaryAcknowledgeMessageObject getAisBinaryAcknowledgeMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageCollectionByMmsi( Guid mmsi ) throws Exception;
    List<AisBinaryAcknowledgeMessageObject> qetAisBinaryAcknowledgeMessageCollectionByMmsiIsNull(  ) throws Exception;
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisBinaryAcknowledgeMessageObject> qetAisBinaryAcknowledgeMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber ) throws Exception;
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisBinaryAcknowledgeMessageObject> getAisBinaryAcknowledgeMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber ) throws Exception;
    // ---------------------------------------------------------------------
    // AisBinaryAddressedMessage queries
    // ---------------------------------------------------------------------
    AisBinaryAddressedMessageObject getAisBinaryAddressedMessageById( Guid id ) throws Exception;
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollection( ) throws Exception;
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollectionByAisDevice( Guid aisDevice ) throws Exception;
    AisBinaryAddressedMessageObject getAisBinaryAddressedMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    AisBinaryAddressedMessageObject getAisBinaryAddressedMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollectionByMmsi( Guid mmsi ) throws Exception;
    List<AisBinaryAddressedMessageObject> qetAisBinaryAddressedMessageCollectionByMmsiIsNull(  ) throws Exception;
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisBinaryAddressedMessageObject> qetAisBinaryAddressedMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber ) throws Exception;
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber ) throws Exception;
    List<AisBinaryAddressedMessageObject> getAisBinaryAddressedMessageCollectionByDestinationMmsi( Guid destinationMmsi ) throws Exception;
    List<AisBinaryAddressedMessageObject> qetAisBinaryAddressedMessageCollectionByDestinationMmsiIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // AisBinaryBroadcastMessage queries
    // ---------------------------------------------------------------------
    AisBinaryBroadcastMessageObject getAisBinaryBroadcastMessageById( Guid id ) throws Exception;
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageCollection( ) throws Exception;
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageCollectionByAisDevice( Guid aisDevice ) throws Exception;
    AisBinaryBroadcastMessageObject getAisBinaryBroadcastMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    AisBinaryBroadcastMessageObject getAisBinaryBroadcastMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageCollectionByMmsi( Guid mmsi ) throws Exception;
    List<AisBinaryBroadcastMessageObject> qetAisBinaryBroadcastMessageCollectionByMmsiIsNull(  ) throws Exception;
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisBinaryBroadcastMessageObject> qetAisBinaryBroadcastMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber ) throws Exception;
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisBinaryBroadcastMessageObject> getAisBinaryBroadcastMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber ) throws Exception;
    // ---------------------------------------------------------------------
    // AisDataLinkManagementMessage queries
    // ---------------------------------------------------------------------
    AisDataLinkManagementMessageObject getAisDataLinkManagementMessageById( Guid id ) throws Exception;
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageCollection( ) throws Exception;
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageCollectionByAisDevice( Guid aisDevice ) throws Exception;
    AisDataLinkManagementMessageObject getAisDataLinkManagementMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    AisDataLinkManagementMessageObject getAisDataLinkManagementMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageCollectionByMmsi( Guid mmsi ) throws Exception;
    List<AisDataLinkManagementMessageObject> qetAisDataLinkManagementMessageCollectionByMmsiIsNull(  ) throws Exception;
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisDataLinkManagementMessageObject> qetAisDataLinkManagementMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber ) throws Exception;
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisDataLinkManagementMessageObject> getAisDataLinkManagementMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber ) throws Exception;
    // ---------------------------------------------------------------------
    // AisExtendedClassBCsPositionReportMessage queries
    // ---------------------------------------------------------------------
    AisExtendedClassBCsPositionReportMessageObject getAisExtendedClassBCsPositionReportMessageById( Guid id ) throws Exception;
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollection( ) throws Exception;
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollectionByAisDevice( Guid aisDevice ) throws Exception;
    AisExtendedClassBCsPositionReportMessageObject getAisExtendedClassBCsPositionReportMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    AisExtendedClassBCsPositionReportMessageObject getAisExtendedClassBCsPositionReportMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollectionByMmsi( Guid mmsi ) throws Exception;
    List<AisExtendedClassBCsPositionReportMessageObject> qetAisExtendedClassBCsPositionReportMessageCollectionByMmsiIsNull(  ) throws Exception;
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisExtendedClassBCsPositionReportMessageObject> qetAisExtendedClassBCsPositionReportMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber ) throws Exception;
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber ) throws Exception;
    List<AisExtendedClassBCsPositionReportMessageObject> getAisExtendedClassBCsPositionReportMessageCollectionByName( Guid name ) throws Exception;
    List<AisExtendedClassBCsPositionReportMessageObject> qetAisExtendedClassBCsPositionReportMessageCollectionByNameIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // AisInterrogationMessage queries
    // ---------------------------------------------------------------------
    AisInterrogationMessageObject getAisInterrogationMessageById( Guid id ) throws Exception;
    List<AisInterrogationMessageObject> getAisInterrogationMessageCollection( ) throws Exception;
    List<AisInterrogationMessageObject> getAisInterrogationMessageCollectionByAisDevice( Guid aisDevice ) throws Exception;
    AisInterrogationMessageObject getAisInterrogationMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    AisInterrogationMessageObject getAisInterrogationMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisInterrogationMessageObject> getAisInterrogationMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisInterrogationMessageObject> getAisInterrogationMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisInterrogationMessageObject> getAisInterrogationMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisInterrogationMessageObject> getAisInterrogationMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisInterrogationMessageObject> getAisInterrogationMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisInterrogationMessageObject> getAisInterrogationMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisInterrogationMessageObject> getAisInterrogationMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisInterrogationMessageObject> getAisInterrogationMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisInterrogationMessageObject> getAisInterrogationMessageCollectionByMmsi( Guid mmsi ) throws Exception;
    List<AisInterrogationMessageObject> qetAisInterrogationMessageCollectionByMmsiIsNull(  ) throws Exception;
    List<AisInterrogationMessageObject> getAisInterrogationMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisInterrogationMessageObject> qetAisInterrogationMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber ) throws Exception;
    List<AisInterrogationMessageObject> getAisInterrogationMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisInterrogationMessageObject> getAisInterrogationMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisInterrogationMessageObject> getAisInterrogationMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber ) throws Exception;
    // ---------------------------------------------------------------------
    // AisPositionReportClassAMessageBase queries
    // ---------------------------------------------------------------------
    AisPositionReportClassAMessageBaseObject getAisPositionReportClassAMessageBaseById( Guid id ) throws Exception;
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseCollection( ) throws Exception;
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseCollectionByAisDevice( Guid aisDevice ) throws Exception;
    AisPositionReportClassAMessageBaseObject getAisPositionReportClassAMessageBaseByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    AisPositionReportClassAMessageBaseObject getAisPositionReportClassAMessageBaseByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseCollectionByReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseCollectionAtReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseCollectionFromReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseCollectionUntilReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseCollectionByMmsi( Guid mmsi ) throws Exception;
    List<AisPositionReportClassAMessageBaseObject> qetAisPositionReportClassAMessageBaseCollectionByMmsiIsNull(  ) throws Exception;
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisPositionReportClassAMessageBaseObject> qetAisPositionReportClassAMessageBaseCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber ) throws Exception;
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisPositionReportClassAMessageBaseObject> getAisPositionReportClassAMessageBaseCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber ) throws Exception;
    // ---------------------------------------------------------------------
    // AisPositionReportClassAAssignedScheduleMessage queries
    // ---------------------------------------------------------------------
    AisPositionReportClassAAssignedScheduleMessageObject getAisPositionReportClassAAssignedScheduleMessageById( Guid id ) throws Exception;
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageCollection( ) throws Exception;
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageCollectionByAisDevice( Guid aisDevice ) throws Exception;
    AisPositionReportClassAAssignedScheduleMessageObject getAisPositionReportClassAAssignedScheduleMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    AisPositionReportClassAAssignedScheduleMessageObject getAisPositionReportClassAAssignedScheduleMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageCollectionByMmsi( Guid mmsi ) throws Exception;
    List<AisPositionReportClassAAssignedScheduleMessageObject> qetAisPositionReportClassAAssignedScheduleMessageCollectionByMmsiIsNull(  ) throws Exception;
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisPositionReportClassAAssignedScheduleMessageObject> qetAisPositionReportClassAAssignedScheduleMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber ) throws Exception;
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisPositionReportClassAAssignedScheduleMessageObject> getAisPositionReportClassAAssignedScheduleMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber ) throws Exception;
    // ---------------------------------------------------------------------
    // AisPositionReportClassAMessage queries
    // ---------------------------------------------------------------------
    AisPositionReportClassAMessageObject getAisPositionReportClassAMessageById( Guid id ) throws Exception;
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageCollection( ) throws Exception;
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageCollectionByAisDevice( Guid aisDevice ) throws Exception;
    AisPositionReportClassAMessageObject getAisPositionReportClassAMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    AisPositionReportClassAMessageObject getAisPositionReportClassAMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageCollectionByMmsi( Guid mmsi ) throws Exception;
    List<AisPositionReportClassAMessageObject> qetAisPositionReportClassAMessageCollectionByMmsiIsNull(  ) throws Exception;
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisPositionReportClassAMessageObject> qetAisPositionReportClassAMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber ) throws Exception;
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisPositionReportClassAMessageObject> getAisPositionReportClassAMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber ) throws Exception;
    // ---------------------------------------------------------------------
    // AisPositionReportClassAResponseToInterrogationMessage queries
    // ---------------------------------------------------------------------
    AisPositionReportClassAResponseToInterrogationMessageObject getAisPositionReportClassAResponseToInterrogationMessageById( Guid id ) throws Exception;
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageCollection( ) throws Exception;
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageCollectionByAisDevice( Guid aisDevice ) throws Exception;
    AisPositionReportClassAResponseToInterrogationMessageObject getAisPositionReportClassAResponseToInterrogationMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    AisPositionReportClassAResponseToInterrogationMessageObject getAisPositionReportClassAResponseToInterrogationMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsi( Guid mmsi ) throws Exception;
    List<AisPositionReportClassAResponseToInterrogationMessageObject> qetAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsiIsNull(  ) throws Exception;
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisPositionReportClassAResponseToInterrogationMessageObject> qetAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber ) throws Exception;
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisPositionReportClassAResponseToInterrogationMessageObject> getAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber ) throws Exception;
    // ---------------------------------------------------------------------
    // AisPositionReportForLongRangeApplicationsMessage queries
    // ---------------------------------------------------------------------
    AisPositionReportForLongRangeApplicationsMessageObject getAisPositionReportForLongRangeApplicationsMessageById( Guid id ) throws Exception;
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageCollection( ) throws Exception;
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageCollectionByAisDevice( Guid aisDevice ) throws Exception;
    AisPositionReportForLongRangeApplicationsMessageObject getAisPositionReportForLongRangeApplicationsMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    AisPositionReportForLongRangeApplicationsMessageObject getAisPositionReportForLongRangeApplicationsMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageCollectionByMmsi( Guid mmsi ) throws Exception;
    List<AisPositionReportForLongRangeApplicationsMessageObject> qetAisPositionReportForLongRangeApplicationsMessageCollectionByMmsiIsNull(  ) throws Exception;
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisPositionReportForLongRangeApplicationsMessageObject> qetAisPositionReportForLongRangeApplicationsMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber ) throws Exception;
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisPositionReportForLongRangeApplicationsMessageObject> getAisPositionReportForLongRangeApplicationsMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber ) throws Exception;
    // ---------------------------------------------------------------------
    // AisSafetyRelatedAcknowledgmentMessage queries
    // ---------------------------------------------------------------------
    AisSafetyRelatedAcknowledgmentMessageObject getAisSafetyRelatedAcknowledgmentMessageById( Guid id ) throws Exception;
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageCollection( ) throws Exception;
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageCollectionByAisDevice( Guid aisDevice ) throws Exception;
    AisSafetyRelatedAcknowledgmentMessageObject getAisSafetyRelatedAcknowledgmentMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    AisSafetyRelatedAcknowledgmentMessageObject getAisSafetyRelatedAcknowledgmentMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageCollectionByMmsi( Guid mmsi ) throws Exception;
    List<AisSafetyRelatedAcknowledgmentMessageObject> qetAisSafetyRelatedAcknowledgmentMessageCollectionByMmsiIsNull(  ) throws Exception;
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisSafetyRelatedAcknowledgmentMessageObject> qetAisSafetyRelatedAcknowledgmentMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber ) throws Exception;
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisSafetyRelatedAcknowledgmentMessageObject> getAisSafetyRelatedAcknowledgmentMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber ) throws Exception;
    // ---------------------------------------------------------------------
    // AisStandardClassBCsPositionReportMessage queries
    // ---------------------------------------------------------------------
    AisStandardClassBCsPositionReportMessageObject getAisStandardClassBCsPositionReportMessageById( Guid id ) throws Exception;
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageCollection( ) throws Exception;
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageCollectionByAisDevice( Guid aisDevice ) throws Exception;
    AisStandardClassBCsPositionReportMessageObject getAisStandardClassBCsPositionReportMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    AisStandardClassBCsPositionReportMessageObject getAisStandardClassBCsPositionReportMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageCollectionByMmsi( Guid mmsi ) throws Exception;
    List<AisStandardClassBCsPositionReportMessageObject> qetAisStandardClassBCsPositionReportMessageCollectionByMmsiIsNull(  ) throws Exception;
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisStandardClassBCsPositionReportMessageObject> qetAisStandardClassBCsPositionReportMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber ) throws Exception;
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisStandardClassBCsPositionReportMessageObject> getAisStandardClassBCsPositionReportMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber ) throws Exception;
    // ---------------------------------------------------------------------
    // AisStandardSarAircraftPositionReportMessage queries
    // ---------------------------------------------------------------------
    AisStandardSarAircraftPositionReportMessageObject getAisStandardSarAircraftPositionReportMessageById( Guid id ) throws Exception;
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageCollection( ) throws Exception;
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageCollectionByAisDevice( Guid aisDevice ) throws Exception;
    AisStandardSarAircraftPositionReportMessageObject getAisStandardSarAircraftPositionReportMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    AisStandardSarAircraftPositionReportMessageObject getAisStandardSarAircraftPositionReportMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageCollectionByMmsi( Guid mmsi ) throws Exception;
    List<AisStandardSarAircraftPositionReportMessageObject> qetAisStandardSarAircraftPositionReportMessageCollectionByMmsiIsNull(  ) throws Exception;
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisStandardSarAircraftPositionReportMessageObject> qetAisStandardSarAircraftPositionReportMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber ) throws Exception;
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisStandardSarAircraftPositionReportMessageObject> getAisStandardSarAircraftPositionReportMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber ) throws Exception;
    // ---------------------------------------------------------------------
    // AisStaticAndVoyageRelatedDataMessage queries
    // ---------------------------------------------------------------------
    AisStaticAndVoyageRelatedDataMessageObject getAisStaticAndVoyageRelatedDataMessageById( Guid id ) throws Exception;
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollection( ) throws Exception;
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionByAisDevice( Guid aisDevice ) throws Exception;
    AisStaticAndVoyageRelatedDataMessageObject getAisStaticAndVoyageRelatedDataMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    AisStaticAndVoyageRelatedDataMessageObject getAisStaticAndVoyageRelatedDataMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionByMmsi( Guid mmsi ) throws Exception;
    List<AisStaticAndVoyageRelatedDataMessageObject> qetAisStaticAndVoyageRelatedDataMessageCollectionByMmsiIsNull(  ) throws Exception;
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisStaticAndVoyageRelatedDataMessageObject> qetAisStaticAndVoyageRelatedDataMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber ) throws Exception;
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber ) throws Exception;
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionByImoNumber( Guid imoNumber ) throws Exception;
    List<AisStaticAndVoyageRelatedDataMessageObject> qetAisStaticAndVoyageRelatedDataMessageCollectionByImoNumberIsNull(  ) throws Exception;
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionByCallsign( Guid callsign ) throws Exception;
    List<AisStaticAndVoyageRelatedDataMessageObject> qetAisStaticAndVoyageRelatedDataMessageCollectionByCallsignIsNull(  ) throws Exception;
    List<AisStaticAndVoyageRelatedDataMessageObject> getAisStaticAndVoyageRelatedDataMessageCollectionByShipName( Guid shipName ) throws Exception;
    List<AisStaticAndVoyageRelatedDataMessageObject> qetAisStaticAndVoyageRelatedDataMessageCollectionByShipNameIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // AisStaticDataReportMessage queries
    // ---------------------------------------------------------------------
    AisStaticDataReportMessageObject getAisStaticDataReportMessageById( Guid id ) throws Exception;
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageCollection( ) throws Exception;
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageCollectionByAisDevice( Guid aisDevice ) throws Exception;
    AisStaticDataReportMessageObject getAisStaticDataReportMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    AisStaticDataReportMessageObject getAisStaticDataReportMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageCollectionByMmsi( Guid mmsi ) throws Exception;
    List<AisStaticDataReportMessageObject> qetAisStaticDataReportMessageCollectionByMmsiIsNull(  ) throws Exception;
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisStaticDataReportMessageObject> qetAisStaticDataReportMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber ) throws Exception;
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisStaticDataReportMessageObject> getAisStaticDataReportMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber ) throws Exception;
    // ---------------------------------------------------------------------
    // AisStaticDataReportPartAMessage queries
    // ---------------------------------------------------------------------
    AisStaticDataReportPartAMessageObject getAisStaticDataReportPartAMessageById( Guid id ) throws Exception;
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollection( ) throws Exception;
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollectionByAisDevice( Guid aisDevice ) throws Exception;
    AisStaticDataReportPartAMessageObject getAisStaticDataReportPartAMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    AisStaticDataReportPartAMessageObject getAisStaticDataReportPartAMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollectionByMmsi( Guid mmsi ) throws Exception;
    List<AisStaticDataReportPartAMessageObject> qetAisStaticDataReportPartAMessageCollectionByMmsiIsNull(  ) throws Exception;
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisStaticDataReportPartAMessageObject> qetAisStaticDataReportPartAMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber ) throws Exception;
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber ) throws Exception;
    List<AisStaticDataReportPartAMessageObject> getAisStaticDataReportPartAMessageCollectionByShipName( Guid shipName ) throws Exception;
    List<AisStaticDataReportPartAMessageObject> qetAisStaticDataReportPartAMessageCollectionByShipNameIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // AisStaticDataReportPartBMessage queries
    // ---------------------------------------------------------------------
    AisStaticDataReportPartBMessageObject getAisStaticDataReportPartBMessageById( Guid id ) throws Exception;
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollection( ) throws Exception;
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionByAisDevice( Guid aisDevice ) throws Exception;
    AisStaticDataReportPartBMessageObject getAisStaticDataReportPartBMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    AisStaticDataReportPartBMessageObject getAisStaticDataReportPartBMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionByMmsi( Guid mmsi ) throws Exception;
    List<AisStaticDataReportPartBMessageObject> qetAisStaticDataReportPartBMessageCollectionByMmsiIsNull(  ) throws Exception;
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisStaticDataReportPartBMessageObject> qetAisStaticDataReportPartBMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber ) throws Exception;
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber ) throws Exception;
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionByCallsign( Guid callsign ) throws Exception;
    List<AisStaticDataReportPartBMessageObject> qetAisStaticDataReportPartBMessageCollectionByCallsignIsNull(  ) throws Exception;
    List<AisStaticDataReportPartBMessageObject> getAisStaticDataReportPartBMessageCollectionByMothershipMmsi( Guid mothershipMmsi ) throws Exception;
    List<AisStaticDataReportPartBMessageObject> qetAisStaticDataReportPartBMessageCollectionByMothershipMmsiIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // AisUtcAndDateInquiryMessage queries
    // ---------------------------------------------------------------------
    AisUtcAndDateInquiryMessageObject getAisUtcAndDateInquiryMessageById( Guid id ) throws Exception;
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageCollection( ) throws Exception;
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageCollectionByAisDevice( Guid aisDevice ) throws Exception;
    AisUtcAndDateInquiryMessageObject getAisUtcAndDateInquiryMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    AisUtcAndDateInquiryMessageObject getAisUtcAndDateInquiryMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageCollectionByMmsi( Guid mmsi ) throws Exception;
    List<AisUtcAndDateInquiryMessageObject> qetAisUtcAndDateInquiryMessageCollectionByMmsiIsNull(  ) throws Exception;
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisUtcAndDateInquiryMessageObject> qetAisUtcAndDateInquiryMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber ) throws Exception;
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisUtcAndDateInquiryMessageObject> getAisUtcAndDateInquiryMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber ) throws Exception;
    // ---------------------------------------------------------------------
    // AisUtcAndDateResponseMessage queries
    // ---------------------------------------------------------------------
    AisUtcAndDateResponseMessageObject getAisUtcAndDateResponseMessageById( Guid id ) throws Exception;
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageCollection( ) throws Exception;
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageCollectionByAisDevice( Guid aisDevice ) throws Exception;
    AisUtcAndDateResponseMessageObject getAisUtcAndDateResponseMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    AisUtcAndDateResponseMessageObject getAisUtcAndDateResponseMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp ) throws Exception;
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp ) throws Exception;
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp ) throws Exception;
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageCollectionByMmsi( Guid mmsi ) throws Exception;
    List<AisUtcAndDateResponseMessageObject> qetAisUtcAndDateResponseMessageCollectionByMmsiIsNull(  ) throws Exception;
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageCollectionByMmsiAndMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisUtcAndDateResponseMessageObject> qetAisUtcAndDateResponseMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber ) throws Exception;
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageCollectionByMmsiFromMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageCollectionByMmsiUntilMessageSequenceNumber( Guid mmsi, long messageSequenceNumber ) throws Exception;
    List<AisUtcAndDateResponseMessageObject> getAisUtcAndDateResponseMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber ) throws Exception;
    // ---------------------------------------------------------------------
    // AlarmStateChange queries
    // ---------------------------------------------------------------------
    AlarmStateChangeObject getAlarmStateChangeById( Guid id ) throws Exception;
    List<AlarmStateChangeObject> getAlarmStateChangeCollection( ) throws Exception;
    List<AlarmStateChangeObject> getAlarmStateChangeCollectionByAlarm( Guid alarm ) throws Exception;
    AlarmStateChangeObject getAlarmStateChangeByAlarmAndTimestamp( Guid alarm, DateTime timestamp ) throws Exception;
    AlarmStateChangeObject getAlarmStateChangeByAlarmAtTimestamp( Guid alarm, DateTime timestamp ) throws Exception;
    List<AlarmStateChangeObject> getAlarmStateChangeByAlarmFromTimestamp( Guid alarm, DateTime timestamp ) throws Exception;
    List<AlarmStateChangeObject> getAlarmStateChangeByAlarmUntilTimestamp( Guid alarm, DateTime timestamp ) throws Exception;
    List<AlarmStateChangeObject> getAlarmStateChangeByAlarmOverTimestamp( Guid alarm, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<AlarmStateChangeObject> getAlarmStateChangeCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<AlarmStateChangeObject> getAlarmStateChangeCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<AlarmStateChangeObject> getAlarmStateChangeCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<AlarmStateChangeObject> getAlarmStateChangeCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<AlarmStateChangeObject> getAlarmStateChangeCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // BaseStationType queries
    // ---------------------------------------------------------------------
    BaseStationTypeObject getBaseStationTypeById( Guid id ) throws Exception;
    List<BaseStationTypeObject> getBaseStationTypeCollection( ) throws Exception;
    BaseStationTypeObject getBaseStationTypeByName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // BinaryTimeseriesValue queries
    // ---------------------------------------------------------------------
    BinaryTimeseriesValueObject getBinaryTimeseriesValueById( Guid id ) throws Exception;
    List<BinaryTimeseriesValueObject> getBinaryTimeseriesValueCollection( ) throws Exception;
    List<BinaryTimeseriesValueObject> getBinaryTimeseriesValueCollectionByTimeseries( Guid timeseries ) throws Exception;
    BinaryTimeseriesValueObject getBinaryTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    BinaryTimeseriesValueObject getBinaryTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<BinaryTimeseriesValueObject> getBinaryTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<BinaryTimeseriesValueObject> getBinaryTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<BinaryTimeseriesValueObject> getBinaryTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<BinaryTimeseriesValueObject> getBinaryTimeseriesValueCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<BinaryTimeseriesValueObject> getBinaryTimeseriesValueCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<BinaryTimeseriesValueObject> getBinaryTimeseriesValueCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<BinaryTimeseriesValueObject> getBinaryTimeseriesValueCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<BinaryTimeseriesValueObject> getBinaryTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // Bookmark queries
    // ---------------------------------------------------------------------
    BookmarkObject getBookmarkById( Guid id ) throws Exception;
    List<BookmarkObject> getBookmarkCollection( ) throws Exception;
    List<BookmarkObject> getBookmarkCollectionByView( Guid view ) throws Exception;
    // ---------------------------------------------------------------------
    // BooleanTimeseriesValue queries
    // ---------------------------------------------------------------------
    BooleanTimeseriesValueObject getBooleanTimeseriesValueById( Guid id ) throws Exception;
    List<BooleanTimeseriesValueObject> getBooleanTimeseriesValueCollection( ) throws Exception;
    List<BooleanTimeseriesValueObject> getBooleanTimeseriesValueCollectionByTimeseries( Guid timeseries ) throws Exception;
    BooleanTimeseriesValueObject getBooleanTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    BooleanTimeseriesValueObject getBooleanTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<BooleanTimeseriesValueObject> getBooleanTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<BooleanTimeseriesValueObject> getBooleanTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<BooleanTimeseriesValueObject> getBooleanTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<BooleanTimeseriesValueObject> getBooleanTimeseriesValueCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<BooleanTimeseriesValueObject> getBooleanTimeseriesValueCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<BooleanTimeseriesValueObject> getBooleanTimeseriesValueCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<BooleanTimeseriesValueObject> getBooleanTimeseriesValueCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<BooleanTimeseriesValueObject> getBooleanTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // ByteTimeseriesValue queries
    // ---------------------------------------------------------------------
    ByteTimeseriesValueObject getByteTimeseriesValueById( Guid id ) throws Exception;
    List<ByteTimeseriesValueObject> getByteTimeseriesValueCollection( ) throws Exception;
    List<ByteTimeseriesValueObject> getByteTimeseriesValueCollectionByTimeseries( Guid timeseries ) throws Exception;
    ByteTimeseriesValueObject getByteTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    ByteTimeseriesValueObject getByteTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<ByteTimeseriesValueObject> getByteTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<ByteTimeseriesValueObject> getByteTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<ByteTimeseriesValueObject> getByteTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<ByteTimeseriesValueObject> getByteTimeseriesValueCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<ByteTimeseriesValueObject> getByteTimeseriesValueCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<ByteTimeseriesValueObject> getByteTimeseriesValueCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<ByteTimeseriesValueObject> getByteTimeseriesValueCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<ByteTimeseriesValueObject> getByteTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // CameraCommand queries
    // ---------------------------------------------------------------------
    CameraCommandObject getCameraCommandById( Guid id ) throws Exception;
    List<CameraCommandObject> getCameraCommandCollection( ) throws Exception;
    List<CameraCommandObject> getCameraCommandCollectionByCamera( Guid camera ) throws Exception;
    List<CameraCommandObject> getCameraCommandCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandObject> getCameraCommandCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandObject> getCameraCommandCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandObject> getCameraCommandCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandObject> getCameraCommandCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandObject> getCameraCommandCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandObject> getCameraCommandCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandObject> getCameraCommandCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandObject> getCameraCommandCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandObject> getCameraCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandObject> getCameraCommandCollectionByReply( Guid reply ) throws Exception;
    List<CameraCommandObject> qetCameraCommandCollectionByReplyIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // CameraCommandAbsoluteMove queries
    // ---------------------------------------------------------------------
    CameraCommandAbsoluteMoveObject getCameraCommandAbsoluteMoveById( Guid id ) throws Exception;
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollection( ) throws Exception;
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollectionByCamera( Guid camera ) throws Exception;
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandAbsoluteMoveObject> getCameraCommandAbsoluteMoveCollectionByReply( Guid reply ) throws Exception;
    List<CameraCommandAbsoluteMoveObject> qetCameraCommandAbsoluteMoveCollectionByReplyIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // CameraCommandAdjustPanTiltZoom queries
    // ---------------------------------------------------------------------
    CameraCommandAdjustPanTiltZoomObject getCameraCommandAdjustPanTiltZoomById( Guid id ) throws Exception;
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollection( ) throws Exception;
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollectionByCamera( Guid camera ) throws Exception;
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandAdjustPanTiltZoomObject> getCameraCommandAdjustPanTiltZoomCollectionByReply( Guid reply ) throws Exception;
    List<CameraCommandAdjustPanTiltZoomObject> qetCameraCommandAdjustPanTiltZoomCollectionByReplyIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // CameraCommandContinuousMove queries
    // ---------------------------------------------------------------------
    CameraCommandContinuousMoveObject getCameraCommandContinuousMoveById( Guid id ) throws Exception;
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollection( ) throws Exception;
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollectionByCamera( Guid camera ) throws Exception;
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandContinuousMoveObject> getCameraCommandContinuousMoveCollectionByReply( Guid reply ) throws Exception;
    List<CameraCommandContinuousMoveObject> qetCameraCommandContinuousMoveCollectionByReplyIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // CameraCommandGeoMove queries
    // ---------------------------------------------------------------------
    CameraCommandGeoMoveObject getCameraCommandGeoMoveById( Guid id ) throws Exception;
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollection( ) throws Exception;
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollectionByCamera( Guid camera ) throws Exception;
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandGeoMoveObject> getCameraCommandGeoMoveCollectionByReply( Guid reply ) throws Exception;
    List<CameraCommandGeoMoveObject> qetCameraCommandGeoMoveCollectionByReplyIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // CameraCommandRelativeMove queries
    // ---------------------------------------------------------------------
    CameraCommandRelativeMoveObject getCameraCommandRelativeMoveById( Guid id ) throws Exception;
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollection( ) throws Exception;
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollectionByCamera( Guid camera ) throws Exception;
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandRelativeMoveObject> getCameraCommandRelativeMoveCollectionByReply( Guid reply ) throws Exception;
    List<CameraCommandRelativeMoveObject> qetCameraCommandRelativeMoveCollectionByReplyIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // CameraCommandReleasePTZOwnership queries
    // ---------------------------------------------------------------------
    CameraCommandReleasePTZOwnershipObject getCameraCommandReleasePTZOwnershipById( Guid id ) throws Exception;
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollection( ) throws Exception;
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollectionByCamera( Guid camera ) throws Exception;
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandReleasePTZOwnershipObject> getCameraCommandReleasePTZOwnershipCollectionByReply( Guid reply ) throws Exception;
    List<CameraCommandReleasePTZOwnershipObject> qetCameraCommandReleasePTZOwnershipCollectionByReplyIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // CameraCommandRequestPTZOwnership queries
    // ---------------------------------------------------------------------
    CameraCommandRequestPTZOwnershipObject getCameraCommandRequestPTZOwnershipById( Guid id ) throws Exception;
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollection( ) throws Exception;
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollectionByCamera( Guid camera ) throws Exception;
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandRequestPTZOwnershipObject> getCameraCommandRequestPTZOwnershipCollectionByReply( Guid reply ) throws Exception;
    List<CameraCommandRequestPTZOwnershipObject> qetCameraCommandRequestPTZOwnershipCollectionByReplyIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // CameraCommandSetAutoFocus queries
    // ---------------------------------------------------------------------
    CameraCommandSetAutoFocusObject getCameraCommandSetAutoFocusById( Guid id ) throws Exception;
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollection( ) throws Exception;
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollectionByCamera( Guid camera ) throws Exception;
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandSetAutoFocusObject> getCameraCommandSetAutoFocusCollectionByReply( Guid reply ) throws Exception;
    List<CameraCommandSetAutoFocusObject> qetCameraCommandSetAutoFocusCollectionByReplyIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // CameraCommandSetBlackAndWhite queries
    // ---------------------------------------------------------------------
    CameraCommandSetBlackAndWhiteObject getCameraCommandSetBlackAndWhiteById( Guid id ) throws Exception;
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollection( ) throws Exception;
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollectionByCamera( Guid camera ) throws Exception;
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandSetBlackAndWhiteObject> getCameraCommandSetBlackAndWhiteCollectionByReply( Guid reply ) throws Exception;
    List<CameraCommandSetBlackAndWhiteObject> qetCameraCommandSetBlackAndWhiteCollectionByReplyIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // CameraCommandSetFollowed queries
    // ---------------------------------------------------------------------
    CameraCommandSetFollowedObject getCameraCommandSetFollowedById( Guid id ) throws Exception;
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollection( ) throws Exception;
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollectionByCamera( Guid camera ) throws Exception;
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandSetFollowedObject> getCameraCommandSetFollowedCollectionByReply( Guid reply ) throws Exception;
    List<CameraCommandSetFollowedObject> qetCameraCommandSetFollowedCollectionByReplyIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // CameraCommandSetInfraRedLamp queries
    // ---------------------------------------------------------------------
    CameraCommandSetInfraRedLampObject getCameraCommandSetInfraRedLampById( Guid id ) throws Exception;
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollection( ) throws Exception;
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollectionByCamera( Guid camera ) throws Exception;
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandSetInfraRedLampObject> getCameraCommandSetInfraRedLampCollectionByReply( Guid reply ) throws Exception;
    List<CameraCommandSetInfraRedLampObject> qetCameraCommandSetInfraRedLampCollectionByReplyIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // CameraCommandSetWasher queries
    // ---------------------------------------------------------------------
    CameraCommandSetWasherObject getCameraCommandSetWasherById( Guid id ) throws Exception;
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollection( ) throws Exception;
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollectionByCamera( Guid camera ) throws Exception;
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandSetWasherObject> getCameraCommandSetWasherCollectionByReply( Guid reply ) throws Exception;
    List<CameraCommandSetWasherObject> qetCameraCommandSetWasherCollectionByReplyIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // CameraCommandSetWiper queries
    // ---------------------------------------------------------------------
    CameraCommandSetWiperObject getCameraCommandSetWiperById( Guid id ) throws Exception;
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollection( ) throws Exception;
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollectionByCamera( Guid camera ) throws Exception;
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandSetWiperObject> getCameraCommandSetWiperCollectionByReply( Guid reply ) throws Exception;
    List<CameraCommandSetWiperObject> qetCameraCommandSetWiperCollectionByReplyIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // CameraCommandStop queries
    // ---------------------------------------------------------------------
    CameraCommandStopObject getCameraCommandStopById( Guid id ) throws Exception;
    List<CameraCommandStopObject> getCameraCommandStopCollection( ) throws Exception;
    List<CameraCommandStopObject> getCameraCommandStopCollectionByCamera( Guid camera ) throws Exception;
    List<CameraCommandStopObject> getCameraCommandStopCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandStopObject> getCameraCommandStopCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandStopObject> getCameraCommandStopCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandStopObject> getCameraCommandStopCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandStopObject> getCameraCommandStopCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandStopObject> getCameraCommandStopCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandStopObject> getCameraCommandStopCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandStopObject> getCameraCommandStopCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandStopObject> getCameraCommandStopCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandStopObject> getCameraCommandStopCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandStopObject> getCameraCommandStopCollectionByReply( Guid reply ) throws Exception;
    List<CameraCommandStopObject> qetCameraCommandStopCollectionByReplyIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // CameraCommandReply queries
    // ---------------------------------------------------------------------
    CameraCommandReplyObject getCameraCommandReplyById( Guid id ) throws Exception;
    List<CameraCommandReplyObject> getCameraCommandReplyCollection( ) throws Exception;
    List<CameraCommandReplyObject> getCameraCommandReplyCollectionByCamera( Guid camera ) throws Exception;
    List<CameraCommandReplyObject> getCameraCommandReplyCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandReplyObject> getCameraCommandReplyCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandReplyObject> getCameraCommandReplyCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandReplyObject> getCameraCommandReplyCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraCommandReplyObject> getCameraCommandReplyCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraCommandReplyObject> getCameraCommandReplyCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandReplyObject> getCameraCommandReplyCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandReplyObject> getCameraCommandReplyCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandReplyObject> getCameraCommandReplyCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<CameraCommandReplyObject> getCameraCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    CameraCommandReplyObject getCameraCommandReplyByCommand( Guid command ) throws Exception;
    List<CameraCommandReplyObject> qetCameraCommandReplyCollectionByCommandIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // CameraConfiguration queries
    // ---------------------------------------------------------------------
    CameraConfigurationObject getCameraConfigurationById( Guid id ) throws Exception;
    List<CameraConfigurationObject> getCameraConfigurationCollection( ) throws Exception;
    List<CameraConfigurationObject> getCameraConfigurationCollectionByCamera( Guid camera ) throws Exception;
    CameraConfigurationObject getCameraConfigurationByCameraAndTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    CameraConfigurationObject getCameraConfigurationByCameraAtTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraConfigurationObject> getCameraConfigurationByCameraFromTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraConfigurationObject> getCameraConfigurationByCameraUntilTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraConfigurationObject> getCameraConfigurationByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraConfigurationObject> getCameraConfigurationCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<CameraConfigurationObject> getCameraConfigurationCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<CameraConfigurationObject> getCameraConfigurationCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<CameraConfigurationObject> getCameraConfigurationCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<CameraConfigurationObject> getCameraConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // CameraPanCalibration queries
    // ---------------------------------------------------------------------
    CameraPanCalibrationObject getCameraPanCalibrationById( Guid id ) throws Exception;
    List<CameraPanCalibrationObject> getCameraPanCalibrationCollection( ) throws Exception;
    List<CameraPanCalibrationObject> getCameraPanCalibrationCollectionByCamera( Guid camera ) throws Exception;
    CameraPanCalibrationObject getCameraPanCalibrationByCameraAndTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    CameraPanCalibrationObject getCameraPanCalibrationByCameraAtTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraPanCalibrationObject> getCameraPanCalibrationByCameraFromTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraPanCalibrationObject> getCameraPanCalibrationByCameraUntilTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraPanCalibrationObject> getCameraPanCalibrationByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraPanCalibrationObject> getCameraPanCalibrationCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<CameraPanCalibrationObject> getCameraPanCalibrationCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<CameraPanCalibrationObject> getCameraPanCalibrationCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<CameraPanCalibrationObject> getCameraPanCalibrationCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<CameraPanCalibrationObject> getCameraPanCalibrationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // CameraPanCalibrationValue queries
    // ---------------------------------------------------------------------
    CameraPanCalibrationValueObject getCameraPanCalibrationValueById( Guid id ) throws Exception;
    List<CameraPanCalibrationValueObject> getCameraPanCalibrationValueCollection( ) throws Exception;
    List<CameraPanCalibrationValueObject> getCameraPanCalibrationValueCollectionByPanCalibration( Guid panCalibration ) throws Exception;
    CameraPanCalibrationValueObject getCameraPanCalibrationValueByPanCalibrationAndPanAngle( Guid panCalibration, double panAngle ) throws Exception;
    List<CameraPanCalibrationValueObject> getCameraPanCalibrationValueByPanCalibrationFromPanAngle( Guid panCalibration, double panAngle ) throws Exception;
    List<CameraPanCalibrationValueObject> getCameraPanCalibrationValueByPanCalibrationUntilPanAngle( Guid panCalibration, double panAngle ) throws Exception;
    List<CameraPanCalibrationValueObject> getCameraPanCalibrationValueByPanCalibrationOverPanAngle( Guid panCalibration, double fromPanAngle, double untilPanAngle ) throws Exception;
    // ---------------------------------------------------------------------
    // CameraStatus queries
    // ---------------------------------------------------------------------
    CameraStatusObject getCameraStatusById( Guid id ) throws Exception;
    List<CameraStatusObject> getCameraStatusCollection( ) throws Exception;
    List<CameraStatusObject> getCameraStatusCollectionByCamera( Guid camera ) throws Exception;
    CameraStatusObject getCameraStatusByCameraAndTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    CameraStatusObject getCameraStatusByCameraAtTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraStatusObject> getCameraStatusByCameraFromTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraStatusObject> getCameraStatusByCameraUntilTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraStatusObject> getCameraStatusByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraStatusObject> getCameraStatusCollectionByTrack( Guid track ) throws Exception;
    List<CameraStatusObject> qetCameraStatusCollectionByTrackIsNull(  ) throws Exception;
    CameraStatusObject getCameraStatusByTrackAndTimestamp( Guid track, DateTime timestamp ) throws Exception;
    List<CameraStatusObject> qetCameraStatusCollectionByTrackIsNullAndTimestamp( DateTime timestamp ) throws Exception;
    CameraStatusObject getCameraStatusByTrackAtTimestamp( Guid track, DateTime timestamp ) throws Exception;
    List<CameraStatusObject> getCameraStatusByTrackFromTimestamp( Guid track, DateTime timestamp ) throws Exception;
    List<CameraStatusObject> getCameraStatusByTrackUntilTimestamp( Guid track, DateTime timestamp ) throws Exception;
    List<CameraStatusObject> getCameraStatusByTrackOverTimestamp( Guid track, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraStatusObject> getCameraStatusCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<CameraStatusObject> getCameraStatusCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<CameraStatusObject> getCameraStatusCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<CameraStatusObject> getCameraStatusCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<CameraStatusObject> getCameraStatusCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // CameraTiltCalibration queries
    // ---------------------------------------------------------------------
    CameraTiltCalibrationObject getCameraTiltCalibrationById( Guid id ) throws Exception;
    List<CameraTiltCalibrationObject> getCameraTiltCalibrationCollection( ) throws Exception;
    List<CameraTiltCalibrationObject> getCameraTiltCalibrationCollectionByCamera( Guid camera ) throws Exception;
    CameraTiltCalibrationObject getCameraTiltCalibrationByCameraAndTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    CameraTiltCalibrationObject getCameraTiltCalibrationByCameraAtTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraTiltCalibrationObject> getCameraTiltCalibrationByCameraFromTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraTiltCalibrationObject> getCameraTiltCalibrationByCameraUntilTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraTiltCalibrationObject> getCameraTiltCalibrationByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraTiltCalibrationObject> getCameraTiltCalibrationCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<CameraTiltCalibrationObject> getCameraTiltCalibrationCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<CameraTiltCalibrationObject> getCameraTiltCalibrationCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<CameraTiltCalibrationObject> getCameraTiltCalibrationCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<CameraTiltCalibrationObject> getCameraTiltCalibrationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // CameraTiltCalibrationValue queries
    // ---------------------------------------------------------------------
    CameraTiltCalibrationValueObject getCameraTiltCalibrationValueById( Guid id ) throws Exception;
    List<CameraTiltCalibrationValueObject> getCameraTiltCalibrationValueCollection( ) throws Exception;
    List<CameraTiltCalibrationValueObject> getCameraTiltCalibrationValueCollectionByTiltCalibration( Guid tiltCalibration ) throws Exception;
    CameraTiltCalibrationValueObject getCameraTiltCalibrationValueByTiltCalibrationAndPanAngle( Guid tiltCalibration, double panAngle ) throws Exception;
    List<CameraTiltCalibrationValueObject> getCameraTiltCalibrationValueByTiltCalibrationFromPanAngle( Guid tiltCalibration, double panAngle ) throws Exception;
    List<CameraTiltCalibrationValueObject> getCameraTiltCalibrationValueByTiltCalibrationUntilPanAngle( Guid tiltCalibration, double panAngle ) throws Exception;
    List<CameraTiltCalibrationValueObject> getCameraTiltCalibrationValueByTiltCalibrationOverPanAngle( Guid tiltCalibration, double fromPanAngle, double untilPanAngle ) throws Exception;
    // ---------------------------------------------------------------------
    // CameraZoomCalibration queries
    // ---------------------------------------------------------------------
    CameraZoomCalibrationObject getCameraZoomCalibrationById( Guid id ) throws Exception;
    List<CameraZoomCalibrationObject> getCameraZoomCalibrationCollection( ) throws Exception;
    List<CameraZoomCalibrationObject> getCameraZoomCalibrationCollectionByCamera( Guid camera ) throws Exception;
    CameraZoomCalibrationObject getCameraZoomCalibrationByCameraAndTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    CameraZoomCalibrationObject getCameraZoomCalibrationByCameraAtTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraZoomCalibrationObject> getCameraZoomCalibrationByCameraFromTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraZoomCalibrationObject> getCameraZoomCalibrationByCameraUntilTimestamp( Guid camera, DateTime timestamp ) throws Exception;
    List<CameraZoomCalibrationObject> getCameraZoomCalibrationByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<CameraZoomCalibrationObject> getCameraZoomCalibrationCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<CameraZoomCalibrationObject> getCameraZoomCalibrationCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<CameraZoomCalibrationObject> getCameraZoomCalibrationCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<CameraZoomCalibrationObject> getCameraZoomCalibrationCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<CameraZoomCalibrationObject> getCameraZoomCalibrationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // CameraZoomCalibrationValue queries
    // ---------------------------------------------------------------------
    CameraZoomCalibrationValueObject getCameraZoomCalibrationValueById( Guid id ) throws Exception;
    List<CameraZoomCalibrationValueObject> getCameraZoomCalibrationValueCollection( ) throws Exception;
    List<CameraZoomCalibrationValueObject> getCameraZoomCalibrationValueCollectionByZoomCalibration( Guid zoomCalibration ) throws Exception;
    CameraZoomCalibrationValueObject getCameraZoomCalibrationValueByZoomCalibrationAndFocalLength( Guid zoomCalibration, double focalLength ) throws Exception;
    List<CameraZoomCalibrationValueObject> getCameraZoomCalibrationValueByZoomCalibrationFromFocalLength( Guid zoomCalibration, double focalLength ) throws Exception;
    List<CameraZoomCalibrationValueObject> getCameraZoomCalibrationValueByZoomCalibrationUntilFocalLength( Guid zoomCalibration, double focalLength ) throws Exception;
    List<CameraZoomCalibrationValueObject> getCameraZoomCalibrationValueByZoomCalibrationOverFocalLength( Guid zoomCalibration, double fromFocalLength, double untilFocalLength ) throws Exception;
    // ---------------------------------------------------------------------
    // CatalogElement queries
    // ---------------------------------------------------------------------
    CatalogElementObject getCatalogElementById( Guid id ) throws Exception;
    List<CatalogElementObject> getCatalogElementCollection( ) throws Exception;
    List<CatalogElementObject> getCatalogElementCollectionByCatalog( Guid catalog ) throws Exception;
    List<CatalogElementObject> qetCatalogElementCollectionByCatalogIsNull(  ) throws Exception;
    CatalogElementObject getCatalogElementByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<CatalogElementObject> qetCatalogElementCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // Catalog queries
    // ---------------------------------------------------------------------
    CatalogObject getCatalogById( Guid id ) throws Exception;
    List<CatalogObject> getCatalogCollection( ) throws Exception;
    List<CatalogObject> getCatalogCollectionByCatalog( Guid catalog ) throws Exception;
    List<CatalogObject> qetCatalogCollectionByCatalogIsNull(  ) throws Exception;
    CatalogObject getCatalogByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<CatalogObject> qetCatalogCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // Element queries
    // ---------------------------------------------------------------------
    ElementObject getElementById( Guid id ) throws Exception;
    List<ElementObject> getElementCollection( ) throws Exception;
    List<ElementObject> getElementCollectionByCatalog( Guid catalog ) throws Exception;
    List<ElementObject> qetElementCollectionByCatalogIsNull(  ) throws Exception;
    ElementObject getElementByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<ElementObject> qetElementCollectionByCatalogIsNullAndName( String name ) throws Exception;
    List<ElementObject> getElementCollectionByElementType( Guid elementType ) throws Exception;
    List<ElementObject> qetElementCollectionByElementTypeIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // CollectionInfo queries
    // ---------------------------------------------------------------------
    CollectionInfoObject getCollectionInfoById( Guid id ) throws Exception;
    List<CollectionInfoObject> getCollectionInfoCollection( ) throws Exception;
    // ---------------------------------------------------------------------
    // Country queries
    // ---------------------------------------------------------------------
    CountryObject getCountryById( Guid id ) throws Exception;
    List<CountryObject> getCountryCollection( ) throws Exception;
    CountryObject getCountryByName( String name ) throws Exception;
    CountryObject getCountryByCode( int code ) throws Exception;
    List<CountryObject> getCountryFromCode( int code ) throws Exception;
    List<CountryObject> getCountryUntilCode( int code ) throws Exception;
    List<CountryObject> getCountryOverCode( int fromCode, int untilCode ) throws Exception;
    CountryObject getCountryByAlpha2( String alpha2 ) throws Exception;
    CountryObject getCountryByAlpha3( String alpha3 ) throws Exception;
    // ---------------------------------------------------------------------
    // CursorInfo queries
    // ---------------------------------------------------------------------
    CursorInfoObject getCursorInfoById( Guid id ) throws Exception;
    List<CursorInfoObject> getCursorInfoCollection( ) throws Exception;
    // ---------------------------------------------------------------------
    // DateTimeTimeseriesValue queries
    // ---------------------------------------------------------------------
    DateTimeTimeseriesValueObject getDateTimeTimeseriesValueById( Guid id ) throws Exception;
    List<DateTimeTimeseriesValueObject> getDateTimeTimeseriesValueCollection( ) throws Exception;
    List<DateTimeTimeseriesValueObject> getDateTimeTimeseriesValueCollectionByTimeseries( Guid timeseries ) throws Exception;
    DateTimeTimeseriesValueObject getDateTimeTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    DateTimeTimeseriesValueObject getDateTimeTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<DateTimeTimeseriesValueObject> getDateTimeTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<DateTimeTimeseriesValueObject> getDateTimeTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<DateTimeTimeseriesValueObject> getDateTimeTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<DateTimeTimeseriesValueObject> getDateTimeTimeseriesValueCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<DateTimeTimeseriesValueObject> getDateTimeTimeseriesValueCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<DateTimeTimeseriesValueObject> getDateTimeTimeseriesValueCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<DateTimeTimeseriesValueObject> getDateTimeTimeseriesValueCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<DateTimeTimeseriesValueObject> getDateTimeTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // DeviceHost queries
    // ---------------------------------------------------------------------
    DeviceHostObject getDeviceHostById( Guid id ) throws Exception;
    List<DeviceHostObject> getDeviceHostCollection( ) throws Exception;
    DeviceHostObject getDeviceHostByName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // DeviceHostConfiguration queries
    // ---------------------------------------------------------------------
    DeviceHostConfigurationObject getDeviceHostConfigurationById( Guid id ) throws Exception;
    List<DeviceHostConfigurationObject> getDeviceHostConfigurationCollection( ) throws Exception;
    List<DeviceHostConfigurationObject> getDeviceHostConfigurationCollectionByHost( Guid host ) throws Exception;
    DeviceHostConfigurationObject getDeviceHostConfigurationByHostAndTimestamp( Guid host, DateTime timestamp ) throws Exception;
    DeviceHostConfigurationObject getDeviceHostConfigurationByHostAtTimestamp( Guid host, DateTime timestamp ) throws Exception;
    List<DeviceHostConfigurationObject> getDeviceHostConfigurationByHostFromTimestamp( Guid host, DateTime timestamp ) throws Exception;
    List<DeviceHostConfigurationObject> getDeviceHostConfigurationByHostUntilTimestamp( Guid host, DateTime timestamp ) throws Exception;
    List<DeviceHostConfigurationObject> getDeviceHostConfigurationByHostOverTimestamp( Guid host, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<DeviceHostConfigurationObject> getDeviceHostConfigurationCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<DeviceHostConfigurationObject> getDeviceHostConfigurationCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<DeviceHostConfigurationObject> getDeviceHostConfigurationCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<DeviceHostConfigurationObject> getDeviceHostConfigurationCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<DeviceHostConfigurationObject> getDeviceHostConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // DoubleTimeseriesValue queries
    // ---------------------------------------------------------------------
    DoubleTimeseriesValueObject getDoubleTimeseriesValueById( Guid id ) throws Exception;
    List<DoubleTimeseriesValueObject> getDoubleTimeseriesValueCollection( ) throws Exception;
    List<DoubleTimeseriesValueObject> getDoubleTimeseriesValueCollectionByTimeseries( Guid timeseries ) throws Exception;
    DoubleTimeseriesValueObject getDoubleTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    DoubleTimeseriesValueObject getDoubleTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<DoubleTimeseriesValueObject> getDoubleTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<DoubleTimeseriesValueObject> getDoubleTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<DoubleTimeseriesValueObject> getDoubleTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<DoubleTimeseriesValueObject> getDoubleTimeseriesValueCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<DoubleTimeseriesValueObject> getDoubleTimeseriesValueCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<DoubleTimeseriesValueObject> getDoubleTimeseriesValueCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<DoubleTimeseriesValueObject> getDoubleTimeseriesValueCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<DoubleTimeseriesValueObject> getDoubleTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // FacilityType queries
    // ---------------------------------------------------------------------
    FacilityTypeObject getFacilityTypeById( Guid id ) throws Exception;
    List<FacilityTypeObject> getFacilityTypeCollection( ) throws Exception;
    FacilityTypeObject getFacilityTypeByName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // GeoPosition2DTimeseriesValue queries
    // ---------------------------------------------------------------------
    GeoPosition2DTimeseriesValueObject getGeoPosition2DTimeseriesValueById( Guid id ) throws Exception;
    List<GeoPosition2DTimeseriesValueObject> getGeoPosition2DTimeseriesValueCollection( ) throws Exception;
    List<GeoPosition2DTimeseriesValueObject> getGeoPosition2DTimeseriesValueCollectionByTimeseries( Guid timeseries ) throws Exception;
    GeoPosition2DTimeseriesValueObject getGeoPosition2DTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    GeoPosition2DTimeseriesValueObject getGeoPosition2DTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<GeoPosition2DTimeseriesValueObject> getGeoPosition2DTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<GeoPosition2DTimeseriesValueObject> getGeoPosition2DTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<GeoPosition2DTimeseriesValueObject> getGeoPosition2DTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<GeoPosition2DTimeseriesValueObject> getGeoPosition2DTimeseriesValueCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<GeoPosition2DTimeseriesValueObject> getGeoPosition2DTimeseriesValueCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<GeoPosition2DTimeseriesValueObject> getGeoPosition2DTimeseriesValueCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<GeoPosition2DTimeseriesValueObject> getGeoPosition2DTimeseriesValueCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<GeoPosition2DTimeseriesValueObject> getGeoPosition2DTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // GeoPosition3DTimeseriesValue queries
    // ---------------------------------------------------------------------
    GeoPosition3DTimeseriesValueObject getGeoPosition3DTimeseriesValueById( Guid id ) throws Exception;
    List<GeoPosition3DTimeseriesValueObject> getGeoPosition3DTimeseriesValueCollection( ) throws Exception;
    List<GeoPosition3DTimeseriesValueObject> getGeoPosition3DTimeseriesValueCollectionByTimeseries( Guid timeseries ) throws Exception;
    GeoPosition3DTimeseriesValueObject getGeoPosition3DTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    GeoPosition3DTimeseriesValueObject getGeoPosition3DTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<GeoPosition3DTimeseriesValueObject> getGeoPosition3DTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<GeoPosition3DTimeseriesValueObject> getGeoPosition3DTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<GeoPosition3DTimeseriesValueObject> getGeoPosition3DTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<GeoPosition3DTimeseriesValueObject> getGeoPosition3DTimeseriesValueCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<GeoPosition3DTimeseriesValueObject> getGeoPosition3DTimeseriesValueCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<GeoPosition3DTimeseriesValueObject> getGeoPosition3DTimeseriesValueCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<GeoPosition3DTimeseriesValueObject> getGeoPosition3DTimeseriesValueCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<GeoPosition3DTimeseriesValueObject> getGeoPosition3DTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // GNSSDeviceCommand queries
    // ---------------------------------------------------------------------
    GNSSDeviceCommandObject getGNSSDeviceCommandById( Guid id ) throws Exception;
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollection( ) throws Exception;
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollectionByGNSSDevice( Guid gNSSDevice ) throws Exception;
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollectionByGNSSDeviceAndTimestamp( Guid gNSSDevice, DateTime timestamp ) throws Exception;
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollectionByGNSSDeviceAtTimestamp( Guid gNSSDevice, DateTime timestamp ) throws Exception;
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollectionByGNSSDeviceFromTimestamp( Guid gNSSDevice, DateTime timestamp ) throws Exception;
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollectionByGNSSDeviceUntilTimestamp( Guid gNSSDevice, DateTime timestamp ) throws Exception;
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollectionByGNSSDeviceOverTimestamp( Guid gNSSDevice, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<GNSSDeviceCommandObject> getGNSSDeviceCommandCollectionByReply( Guid reply ) throws Exception;
    List<GNSSDeviceCommandObject> qetGNSSDeviceCommandCollectionByReplyIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // GNSSDeviceCommandReply queries
    // ---------------------------------------------------------------------
    GNSSDeviceCommandReplyObject getGNSSDeviceCommandReplyById( Guid id ) throws Exception;
    List<GNSSDeviceCommandReplyObject> getGNSSDeviceCommandReplyCollection( ) throws Exception;
    List<GNSSDeviceCommandReplyObject> getGNSSDeviceCommandReplyCollectionByGNSSDevice( Guid gNSSDevice ) throws Exception;
    List<GNSSDeviceCommandReplyObject> getGNSSDeviceCommandReplyCollectionByGNSSDeviceAndTimestamp( Guid gNSSDevice, DateTime timestamp ) throws Exception;
    List<GNSSDeviceCommandReplyObject> getGNSSDeviceCommandReplyCollectionByGNSSDeviceAtTimestamp( Guid gNSSDevice, DateTime timestamp ) throws Exception;
    List<GNSSDeviceCommandReplyObject> getGNSSDeviceCommandReplyCollectionByGNSSDeviceFromTimestamp( Guid gNSSDevice, DateTime timestamp ) throws Exception;
    List<GNSSDeviceCommandReplyObject> getGNSSDeviceCommandReplyCollectionByGNSSDeviceUntilTimestamp( Guid gNSSDevice, DateTime timestamp ) throws Exception;
    List<GNSSDeviceCommandReplyObject> getGNSSDeviceCommandReplyCollectionByGNSSDeviceOverTimestamp( Guid gNSSDevice, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<GNSSDeviceCommandReplyObject> getGNSSDeviceCommandReplyCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<GNSSDeviceCommandReplyObject> getGNSSDeviceCommandReplyCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<GNSSDeviceCommandReplyObject> getGNSSDeviceCommandReplyCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<GNSSDeviceCommandReplyObject> getGNSSDeviceCommandReplyCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<GNSSDeviceCommandReplyObject> getGNSSDeviceCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    GNSSDeviceCommandReplyObject getGNSSDeviceCommandReplyByCommand( Guid command ) throws Exception;
    List<GNSSDeviceCommandReplyObject> qetGNSSDeviceCommandReplyCollectionByCommandIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // GNSSDeviceConfiguration queries
    // ---------------------------------------------------------------------
    GNSSDeviceConfigurationObject getGNSSDeviceConfigurationById( Guid id ) throws Exception;
    List<GNSSDeviceConfigurationObject> getGNSSDeviceConfigurationCollection( ) throws Exception;
    List<GNSSDeviceConfigurationObject> getGNSSDeviceConfigurationCollectionByGNSSDevice( Guid gNSSDevice ) throws Exception;
    GNSSDeviceConfigurationObject getGNSSDeviceConfigurationByGNSSDeviceAndTimestamp( Guid gNSSDevice, DateTime timestamp ) throws Exception;
    GNSSDeviceConfigurationObject getGNSSDeviceConfigurationByGNSSDeviceAtTimestamp( Guid gNSSDevice, DateTime timestamp ) throws Exception;
    List<GNSSDeviceConfigurationObject> getGNSSDeviceConfigurationByGNSSDeviceFromTimestamp( Guid gNSSDevice, DateTime timestamp ) throws Exception;
    List<GNSSDeviceConfigurationObject> getGNSSDeviceConfigurationByGNSSDeviceUntilTimestamp( Guid gNSSDevice, DateTime timestamp ) throws Exception;
    List<GNSSDeviceConfigurationObject> getGNSSDeviceConfigurationByGNSSDeviceOverTimestamp( Guid gNSSDevice, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<GNSSDeviceConfigurationObject> getGNSSDeviceConfigurationCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<GNSSDeviceConfigurationObject> getGNSSDeviceConfigurationCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<GNSSDeviceConfigurationObject> getGNSSDeviceConfigurationCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<GNSSDeviceConfigurationObject> getGNSSDeviceConfigurationCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<GNSSDeviceConfigurationObject> getGNSSDeviceConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // GuidTimeseriesValue queries
    // ---------------------------------------------------------------------
    GuidTimeseriesValueObject getGuidTimeseriesValueById( Guid id ) throws Exception;
    List<GuidTimeseriesValueObject> getGuidTimeseriesValueCollection( ) throws Exception;
    List<GuidTimeseriesValueObject> getGuidTimeseriesValueCollectionByTimeseries( Guid timeseries ) throws Exception;
    GuidTimeseriesValueObject getGuidTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    GuidTimeseriesValueObject getGuidTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<GuidTimeseriesValueObject> getGuidTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<GuidTimeseriesValueObject> getGuidTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<GuidTimeseriesValueObject> getGuidTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<GuidTimeseriesValueObject> getGuidTimeseriesValueCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<GuidTimeseriesValueObject> getGuidTimeseriesValueCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<GuidTimeseriesValueObject> getGuidTimeseriesValueCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<GuidTimeseriesValueObject> getGuidTimeseriesValueCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<GuidTimeseriesValueObject> getGuidTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // GyroDeviceCommand queries
    // ---------------------------------------------------------------------
    GyroDeviceCommandObject getGyroDeviceCommandById( Guid id ) throws Exception;
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollection( ) throws Exception;
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollectionByGyroDevice( Guid gyroDevice ) throws Exception;
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollectionByGyroDeviceAndTimestamp( Guid gyroDevice, DateTime timestamp ) throws Exception;
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollectionByGyroDeviceAtTimestamp( Guid gyroDevice, DateTime timestamp ) throws Exception;
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollectionByGyroDeviceFromTimestamp( Guid gyroDevice, DateTime timestamp ) throws Exception;
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollectionByGyroDeviceUntilTimestamp( Guid gyroDevice, DateTime timestamp ) throws Exception;
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollectionByGyroDeviceOverTimestamp( Guid gyroDevice, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<GyroDeviceCommandObject> getGyroDeviceCommandCollectionByReply( Guid reply ) throws Exception;
    List<GyroDeviceCommandObject> qetGyroDeviceCommandCollectionByReplyIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // GyroDeviceCommandReply queries
    // ---------------------------------------------------------------------
    GyroDeviceCommandReplyObject getGyroDeviceCommandReplyById( Guid id ) throws Exception;
    List<GyroDeviceCommandReplyObject> getGyroDeviceCommandReplyCollection( ) throws Exception;
    List<GyroDeviceCommandReplyObject> getGyroDeviceCommandReplyCollectionByGyroDevice( Guid gyroDevice ) throws Exception;
    List<GyroDeviceCommandReplyObject> getGyroDeviceCommandReplyCollectionByGyroDeviceAndTimestamp( Guid gyroDevice, DateTime timestamp ) throws Exception;
    List<GyroDeviceCommandReplyObject> getGyroDeviceCommandReplyCollectionByGyroDeviceAtTimestamp( Guid gyroDevice, DateTime timestamp ) throws Exception;
    List<GyroDeviceCommandReplyObject> getGyroDeviceCommandReplyCollectionByGyroDeviceFromTimestamp( Guid gyroDevice, DateTime timestamp ) throws Exception;
    List<GyroDeviceCommandReplyObject> getGyroDeviceCommandReplyCollectionByGyroDeviceUntilTimestamp( Guid gyroDevice, DateTime timestamp ) throws Exception;
    List<GyroDeviceCommandReplyObject> getGyroDeviceCommandReplyCollectionByGyroDeviceOverTimestamp( Guid gyroDevice, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<GyroDeviceCommandReplyObject> getGyroDeviceCommandReplyCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<GyroDeviceCommandReplyObject> getGyroDeviceCommandReplyCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<GyroDeviceCommandReplyObject> getGyroDeviceCommandReplyCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<GyroDeviceCommandReplyObject> getGyroDeviceCommandReplyCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<GyroDeviceCommandReplyObject> getGyroDeviceCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    GyroDeviceCommandReplyObject getGyroDeviceCommandReplyByCommand( Guid command ) throws Exception;
    List<GyroDeviceCommandReplyObject> qetGyroDeviceCommandReplyCollectionByCommandIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // GyroDeviceConfiguration queries
    // ---------------------------------------------------------------------
    GyroDeviceConfigurationObject getGyroDeviceConfigurationById( Guid id ) throws Exception;
    List<GyroDeviceConfigurationObject> getGyroDeviceConfigurationCollection( ) throws Exception;
    List<GyroDeviceConfigurationObject> getGyroDeviceConfigurationCollectionByGyroDevice( Guid gyroDevice ) throws Exception;
    GyroDeviceConfigurationObject getGyroDeviceConfigurationByGyroDeviceAndTimestamp( Guid gyroDevice, DateTime timestamp ) throws Exception;
    GyroDeviceConfigurationObject getGyroDeviceConfigurationByGyroDeviceAtTimestamp( Guid gyroDevice, DateTime timestamp ) throws Exception;
    List<GyroDeviceConfigurationObject> getGyroDeviceConfigurationByGyroDeviceFromTimestamp( Guid gyroDevice, DateTime timestamp ) throws Exception;
    List<GyroDeviceConfigurationObject> getGyroDeviceConfigurationByGyroDeviceUntilTimestamp( Guid gyroDevice, DateTime timestamp ) throws Exception;
    List<GyroDeviceConfigurationObject> getGyroDeviceConfigurationByGyroDeviceOverTimestamp( Guid gyroDevice, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<GyroDeviceConfigurationObject> getGyroDeviceConfigurationCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<GyroDeviceConfigurationObject> getGyroDeviceConfigurationCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<GyroDeviceConfigurationObject> getGyroDeviceConfigurationCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<GyroDeviceConfigurationObject> getGyroDeviceConfigurationCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<GyroDeviceConfigurationObject> getGyroDeviceConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // Identity queries
    // ---------------------------------------------------------------------
    IdentityObject getIdentityById( Guid id ) throws Exception;
    List<IdentityObject> getIdentityCollection( ) throws Exception;
    // ---------------------------------------------------------------------
    // Callsign queries
    // ---------------------------------------------------------------------
    CallsignObject getCallsignById( Guid id ) throws Exception;
    List<CallsignObject> getCallsignCollection( ) throws Exception;
    CallsignObject getCallsignByIdentifier( String identifier ) throws Exception;
    // ---------------------------------------------------------------------
    // InternationalMaritimeOrganizationNumber queries
    // ---------------------------------------------------------------------
    InternationalMaritimeOrganizationNumberObject getInternationalMaritimeOrganizationNumberById( Guid id ) throws Exception;
    List<InternationalMaritimeOrganizationNumberObject> getInternationalMaritimeOrganizationNumberCollection( ) throws Exception;
    InternationalMaritimeOrganizationNumberObject getInternationalMaritimeOrganizationNumberByIdentifier( long identifier ) throws Exception;
    List<InternationalMaritimeOrganizationNumberObject> getInternationalMaritimeOrganizationNumberFromIdentifier( long identifier ) throws Exception;
    List<InternationalMaritimeOrganizationNumberObject> getInternationalMaritimeOrganizationNumberUntilIdentifier( long identifier ) throws Exception;
    List<InternationalMaritimeOrganizationNumberObject> getInternationalMaritimeOrganizationNumberOverIdentifier( long fromIdentifier, long untilIdentifier ) throws Exception;
    // ---------------------------------------------------------------------
    // MaritimeMobileServiceIdentity queries
    // ---------------------------------------------------------------------
    MaritimeMobileServiceIdentityObject getMaritimeMobileServiceIdentityById( Guid id ) throws Exception;
    List<MaritimeMobileServiceIdentityObject> getMaritimeMobileServiceIdentityCollection( ) throws Exception;
    MaritimeMobileServiceIdentityObject getMaritimeMobileServiceIdentityByIdentifier( long identifier ) throws Exception;
    List<MaritimeMobileServiceIdentityObject> getMaritimeMobileServiceIdentityFromIdentifier( long identifier ) throws Exception;
    List<MaritimeMobileServiceIdentityObject> getMaritimeMobileServiceIdentityUntilIdentifier( long identifier ) throws Exception;
    List<MaritimeMobileServiceIdentityObject> getMaritimeMobileServiceIdentityOverIdentifier( long fromIdentifier, long untilIdentifier ) throws Exception;
    // ---------------------------------------------------------------------
    // Name queries
    // ---------------------------------------------------------------------
    NameObject getNameById( Guid id ) throws Exception;
    List<NameObject> getNameCollection( ) throws Exception;
    NameObject getNameByText( String text ) throws Exception;
    // ---------------------------------------------------------------------
    // Int16TimeseriesValue queries
    // ---------------------------------------------------------------------
    Int16TimeseriesValueObject getInt16TimeseriesValueById( Guid id ) throws Exception;
    List<Int16TimeseriesValueObject> getInt16TimeseriesValueCollection( ) throws Exception;
    List<Int16TimeseriesValueObject> getInt16TimeseriesValueCollectionByTimeseries( Guid timeseries ) throws Exception;
    Int16TimeseriesValueObject getInt16TimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    Int16TimeseriesValueObject getInt16TimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<Int16TimeseriesValueObject> getInt16TimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<Int16TimeseriesValueObject> getInt16TimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<Int16TimeseriesValueObject> getInt16TimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<Int16TimeseriesValueObject> getInt16TimeseriesValueCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<Int16TimeseriesValueObject> getInt16TimeseriesValueCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<Int16TimeseriesValueObject> getInt16TimeseriesValueCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<Int16TimeseriesValueObject> getInt16TimeseriesValueCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<Int16TimeseriesValueObject> getInt16TimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // Int32TimeseriesValue queries
    // ---------------------------------------------------------------------
    Int32TimeseriesValueObject getInt32TimeseriesValueById( Guid id ) throws Exception;
    List<Int32TimeseriesValueObject> getInt32TimeseriesValueCollection( ) throws Exception;
    List<Int32TimeseriesValueObject> getInt32TimeseriesValueCollectionByTimeseries( Guid timeseries ) throws Exception;
    Int32TimeseriesValueObject getInt32TimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    Int32TimeseriesValueObject getInt32TimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<Int32TimeseriesValueObject> getInt32TimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<Int32TimeseriesValueObject> getInt32TimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<Int32TimeseriesValueObject> getInt32TimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<Int32TimeseriesValueObject> getInt32TimeseriesValueCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<Int32TimeseriesValueObject> getInt32TimeseriesValueCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<Int32TimeseriesValueObject> getInt32TimeseriesValueCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<Int32TimeseriesValueObject> getInt32TimeseriesValueCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<Int32TimeseriesValueObject> getInt32TimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // Int64TimeseriesValue queries
    // ---------------------------------------------------------------------
    Int64TimeseriesValueObject getInt64TimeseriesValueById( Guid id ) throws Exception;
    List<Int64TimeseriesValueObject> getInt64TimeseriesValueCollection( ) throws Exception;
    List<Int64TimeseriesValueObject> getInt64TimeseriesValueCollectionByTimeseries( Guid timeseries ) throws Exception;
    Int64TimeseriesValueObject getInt64TimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    Int64TimeseriesValueObject getInt64TimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<Int64TimeseriesValueObject> getInt64TimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<Int64TimeseriesValueObject> getInt64TimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<Int64TimeseriesValueObject> getInt64TimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<Int64TimeseriesValueObject> getInt64TimeseriesValueCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<Int64TimeseriesValueObject> getInt64TimeseriesValueCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<Int64TimeseriesValueObject> getInt64TimeseriesValueCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<Int64TimeseriesValueObject> getInt64TimeseriesValueCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<Int64TimeseriesValueObject> getInt64TimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // Item queries
    // ---------------------------------------------------------------------
    ItemObject getItemById( Guid id ) throws Exception;
    List<ItemObject> getItemCollection( ) throws Exception;
    // ---------------------------------------------------------------------
    // BaseStation queries
    // ---------------------------------------------------------------------
    BaseStationObject getBaseStationById( Guid id ) throws Exception;
    List<BaseStationObject> getBaseStationCollection( ) throws Exception;
    BaseStationObject getBaseStationByName( String name ) throws Exception;
    List<BaseStationObject> getBaseStationCollectionByType( Guid type ) throws Exception;
    List<BaseStationObject> qetBaseStationCollectionByTypeIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // Device queries
    // ---------------------------------------------------------------------
    DeviceObject getDeviceById( Guid id ) throws Exception;
    List<DeviceObject> getDeviceCollection( ) throws Exception;
    List<DeviceObject> getDeviceCollectionByHost( Guid host ) throws Exception;
    DeviceObject getDeviceByName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // CameraDevice queries
    // ---------------------------------------------------------------------
    CameraDeviceObject getCameraDeviceById( Guid id ) throws Exception;
    List<CameraDeviceObject> getCameraDeviceCollection( ) throws Exception;
    List<CameraDeviceObject> getCameraDeviceCollectionByHost( Guid host ) throws Exception;
    CameraDeviceObject getCameraDeviceByName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // GNSSDevice queries
    // ---------------------------------------------------------------------
    GNSSDeviceObject getGNSSDeviceById( Guid id ) throws Exception;
    List<GNSSDeviceObject> getGNSSDeviceCollection( ) throws Exception;
    List<GNSSDeviceObject> getGNSSDeviceCollectionByHost( Guid host ) throws Exception;
    GNSSDeviceObject getGNSSDeviceByName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // GyroDevice queries
    // ---------------------------------------------------------------------
    GyroDeviceObject getGyroDeviceById( Guid id ) throws Exception;
    List<GyroDeviceObject> getGyroDeviceCollection( ) throws Exception;
    List<GyroDeviceObject> getGyroDeviceCollectionByHost( Guid host ) throws Exception;
    GyroDeviceObject getGyroDeviceByName( String name ) throws Exception;
    List<GyroDeviceObject> getGyroDeviceCollectionByGNSSDevice( Guid gNSSDevice ) throws Exception;
    List<GyroDeviceObject> qetGyroDeviceCollectionByGNSSDeviceIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // LineInputDevice queries
    // ---------------------------------------------------------------------
    LineInputDeviceObject getLineInputDeviceById( Guid id ) throws Exception;
    List<LineInputDeviceObject> getLineInputDeviceCollection( ) throws Exception;
    List<LineInputDeviceObject> getLineInputDeviceCollectionByHost( Guid host ) throws Exception;
    LineInputDeviceObject getLineInputDeviceByName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // OilSpillDetectorDevice queries
    // ---------------------------------------------------------------------
    OilSpillDetectorDeviceObject getOilSpillDetectorDeviceById( Guid id ) throws Exception;
    List<OilSpillDetectorDeviceObject> getOilSpillDetectorDeviceCollection( ) throws Exception;
    List<OilSpillDetectorDeviceObject> getOilSpillDetectorDeviceCollectionByHost( Guid host ) throws Exception;
    OilSpillDetectorDeviceObject getOilSpillDetectorDeviceByName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadioDevice queries
    // ---------------------------------------------------------------------
    RadioDeviceObject getRadioDeviceById( Guid id ) throws Exception;
    List<RadioDeviceObject> getRadioDeviceCollection( ) throws Exception;
    List<RadioDeviceObject> getRadioDeviceCollectionByHost( Guid host ) throws Exception;
    RadioDeviceObject getRadioDeviceByName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadomeDevice queries
    // ---------------------------------------------------------------------
    RadomeDeviceObject getRadomeDeviceById( Guid id ) throws Exception;
    List<RadomeDeviceObject> getRadomeDeviceCollection( ) throws Exception;
    List<RadomeDeviceObject> getRadomeDeviceCollectionByHost( Guid host ) throws Exception;
    RadomeDeviceObject getRadomeDeviceByName( String name ) throws Exception;
    List<RadomeDeviceObject> getRadomeDeviceCollectionByRadar( Guid radar ) throws Exception;
    List<RadomeDeviceObject> qetRadomeDeviceCollectionByRadarIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // TrackerDevice queries
    // ---------------------------------------------------------------------
    TrackerDeviceObject getTrackerDeviceById( Guid id ) throws Exception;
    List<TrackerDeviceObject> getTrackerDeviceCollection( ) throws Exception;
    List<TrackerDeviceObject> getTrackerDeviceCollectionByHost( Guid host ) throws Exception;
    TrackerDeviceObject getTrackerDeviceByName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // AisDevice queries
    // ---------------------------------------------------------------------
    AisDeviceObject getAisDeviceById( Guid id ) throws Exception;
    List<AisDeviceObject> getAisDeviceCollection( ) throws Exception;
    List<AisDeviceObject> getAisDeviceCollectionByHost( Guid host ) throws Exception;
    AisDeviceObject getAisDeviceByName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarDevice queries
    // ---------------------------------------------------------------------
    RadarDeviceObject getRadarDeviceById( Guid id ) throws Exception;
    List<RadarDeviceObject> getRadarDeviceCollection( ) throws Exception;
    List<RadarDeviceObject> getRadarDeviceCollectionByHost( Guid host ) throws Exception;
    RadarDeviceObject getRadarDeviceByName( String name ) throws Exception;
    List<RadarDeviceObject> getRadarDeviceCollectionByRadome( Guid radome ) throws Exception;
    List<RadarDeviceObject> qetRadarDeviceCollectionByRadomeIsNull(  ) throws Exception;
    List<RadarDeviceObject> getRadarDeviceCollectionByGNSSDevice( Guid gNSSDevice ) throws Exception;
    List<RadarDeviceObject> qetRadarDeviceCollectionByGNSSDeviceIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // WeatherStationDevice queries
    // ---------------------------------------------------------------------
    WeatherStationDeviceObject getWeatherStationDeviceById( Guid id ) throws Exception;
    List<WeatherStationDeviceObject> getWeatherStationDeviceCollection( ) throws Exception;
    List<WeatherStationDeviceObject> getWeatherStationDeviceCollectionByHost( Guid host ) throws Exception;
    WeatherStationDeviceObject getWeatherStationDeviceByName( String name ) throws Exception;
    List<WeatherStationDeviceObject> getWeatherStationDeviceCollectionByGyro( Guid gyro ) throws Exception;
    List<WeatherStationDeviceObject> qetWeatherStationDeviceCollectionByGyroIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // Facility queries
    // ---------------------------------------------------------------------
    FacilityObject getFacilityById( Guid id ) throws Exception;
    List<FacilityObject> getFacilityCollection( ) throws Exception;
    FacilityObject getFacilityByName( String name ) throws Exception;
    List<FacilityObject> getFacilityCollectionByType( Guid type ) throws Exception;
    List<FacilityObject> qetFacilityCollectionByTypeIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // TrackableItem queries
    // ---------------------------------------------------------------------
    TrackableItemObject getTrackableItemById( Guid id ) throws Exception;
    List<TrackableItemObject> getTrackableItemCollection( ) throws Exception;
    // ---------------------------------------------------------------------
    // Aircraft queries
    // ---------------------------------------------------------------------
    AircraftObject getAircraftById( Guid id ) throws Exception;
    List<AircraftObject> getAircraftCollection( ) throws Exception;
    List<AircraftObject> getAircraftCollectionByName( String name ) throws Exception;
    List<AircraftObject> getAircraftCollectionByType( Guid type ) throws Exception;
    List<AircraftObject> qetAircraftCollectionByTypeIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // AisAidToNavigation queries
    // ---------------------------------------------------------------------
    AisAidToNavigationObject getAisAidToNavigationById( Guid id ) throws Exception;
    List<AisAidToNavigationObject> getAisAidToNavigationCollection( ) throws Exception;
    AisAidToNavigationObject getAisAidToNavigationByName( String name ) throws Exception;
    List<AisAidToNavigationObject> getAisAidToNavigationCollectionByMMSI( Guid mMSI ) throws Exception;
    List<AisAidToNavigationObject> qetAisAidToNavigationCollectionByMMSIIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // Vehicle queries
    // ---------------------------------------------------------------------
    VehicleObject getVehicleById( Guid id ) throws Exception;
    List<VehicleObject> getVehicleCollection( ) throws Exception;
    VehicleObject getVehicleByName( String name ) throws Exception;
    List<VehicleObject> getVehicleCollectionByType( Guid type ) throws Exception;
    List<VehicleObject> qetVehicleCollectionByTypeIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // Vessel queries
    // ---------------------------------------------------------------------
    VesselObject getVesselById( Guid id ) throws Exception;
    List<VesselObject> getVesselCollection( ) throws Exception;
    List<VesselObject> getVesselCollectionByName( String name ) throws Exception;
    List<VesselObject> getVesselCollectionByType( Guid type ) throws Exception;
    List<VesselObject> qetVesselCollectionByTypeIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // ItemIdentityLink queries
    // ---------------------------------------------------------------------
    ItemIdentityLinkObject getItemIdentityLinkById( Guid id ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollection( ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByItem( Guid item ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByItemAndStart( Guid item, DateTime start ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByItemAtStart( Guid item, DateTime start ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByItemFromStart( Guid item, DateTime start ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByItemUntilStart( Guid item, DateTime start ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByItemOverStart( Guid item, DateTime fromStart, DateTime untilStart ) throws Exception;
    List<ItemIdentityLinkObject> qetItemIdentityLinkCollectionByItem(  ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByItemAndEnd( Guid item, DateTime end ) throws Exception;
    List<ItemIdentityLinkObject> qetItemIdentityLinkCollectionByItemAndEndIsNull( Guid item ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByItemAtEnd( Guid item, DateTime end ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByItemFromEnd( Guid item, DateTime end ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByItemUntilEnd( Guid item, DateTime end ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByItemOverEnd( Guid item, DateTime fromEnd, DateTime untilEnd ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByIdentity( Guid identity ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByIdentityAndStart( Guid identity, DateTime start ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByIdentityAtStart( Guid identity, DateTime start ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByIdentityFromStart( Guid identity, DateTime start ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByIdentityUntilStart( Guid identity, DateTime start ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByIdentityOverStart( Guid identity, DateTime fromStart, DateTime untilStart ) throws Exception;
    List<ItemIdentityLinkObject> qetItemIdentityLinkCollectionByIdentity(  ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByIdentityAndEnd( Guid identity, DateTime end ) throws Exception;
    List<ItemIdentityLinkObject> qetItemIdentityLinkCollectionByIdentityAndEndIsNull( Guid identity ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByIdentityAtEnd( Guid identity, DateTime end ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByIdentityFromEnd( Guid identity, DateTime end ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByIdentityUntilEnd( Guid identity, DateTime end ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByIdentityOverEnd( Guid identity, DateTime fromEnd, DateTime untilEnd ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByStart( DateTime start ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionAtStart( DateTime start ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionFromStart( DateTime start ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionUntilStart( DateTime start ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionOverStart( DateTime fromStart, DateTime untilStart ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionByEnd( DateTime end ) throws Exception;
    List<ItemIdentityLinkObject> qetItemIdentityLinkCollectionByEndIsNull(  ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionAtEnd( DateTime end ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionFromEnd( DateTime end ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionUntilEnd( DateTime end ) throws Exception;
    List<ItemIdentityLinkObject> getItemIdentityLinkCollectionOverEnd( DateTime fromEnd, DateTime untilEnd ) throws Exception;
    // ---------------------------------------------------------------------
    // ItemParentChildLink queries
    // ---------------------------------------------------------------------
    ItemParentChildLinkObject getItemParentChildLinkById( Guid id ) throws Exception;
    List<ItemParentChildLinkObject> getItemParentChildLinkCollection( ) throws Exception;
    List<ItemParentChildLinkObject> getItemParentChildLinkCollectionByParent( Guid parent ) throws Exception;
    ItemParentChildLinkObject getItemParentChildLinkByParentAndTimestamp( Guid parent, DateTime timestamp ) throws Exception;
    ItemParentChildLinkObject getItemParentChildLinkByParentAtTimestamp( Guid parent, DateTime timestamp ) throws Exception;
    List<ItemParentChildLinkObject> getItemParentChildLinkByParentFromTimestamp( Guid parent, DateTime timestamp ) throws Exception;
    List<ItemParentChildLinkObject> getItemParentChildLinkByParentUntilTimestamp( Guid parent, DateTime timestamp ) throws Exception;
    List<ItemParentChildLinkObject> getItemParentChildLinkByParentOverTimestamp( Guid parent, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<ItemParentChildLinkObject> getItemParentChildLinkCollectionByChild( Guid child ) throws Exception;
    ItemParentChildLinkObject getItemParentChildLinkByChildAndTimestamp( Guid child, DateTime timestamp ) throws Exception;
    ItemParentChildLinkObject getItemParentChildLinkByChildAtTimestamp( Guid child, DateTime timestamp ) throws Exception;
    List<ItemParentChildLinkObject> getItemParentChildLinkByChildFromTimestamp( Guid child, DateTime timestamp ) throws Exception;
    List<ItemParentChildLinkObject> getItemParentChildLinkByChildUntilTimestamp( Guid child, DateTime timestamp ) throws Exception;
    List<ItemParentChildLinkObject> getItemParentChildLinkByChildOverTimestamp( Guid child, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<ItemParentChildLinkObject> getItemParentChildLinkCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<ItemParentChildLinkObject> getItemParentChildLinkCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<ItemParentChildLinkObject> getItemParentChildLinkCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<ItemParentChildLinkObject> getItemParentChildLinkCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<ItemParentChildLinkObject> getItemParentChildLinkCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // LineInputDeviceCommand queries
    // ---------------------------------------------------------------------
    LineInputDeviceCommandObject getLineInputDeviceCommandById( Guid id ) throws Exception;
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollection( ) throws Exception;
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollectionByLineInputDevice( Guid lineInputDevice ) throws Exception;
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollectionByLineInputDeviceAndTimestamp( Guid lineInputDevice, DateTime timestamp ) throws Exception;
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollectionByLineInputDeviceAtTimestamp( Guid lineInputDevice, DateTime timestamp ) throws Exception;
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollectionByLineInputDeviceFromTimestamp( Guid lineInputDevice, DateTime timestamp ) throws Exception;
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollectionByLineInputDeviceUntilTimestamp( Guid lineInputDevice, DateTime timestamp ) throws Exception;
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollectionByLineInputDeviceOverTimestamp( Guid lineInputDevice, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<LineInputDeviceCommandObject> getLineInputDeviceCommandCollectionByReply( Guid reply ) throws Exception;
    List<LineInputDeviceCommandObject> qetLineInputDeviceCommandCollectionByReplyIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // LineInputDeviceCommandReply queries
    // ---------------------------------------------------------------------
    LineInputDeviceCommandReplyObject getLineInputDeviceCommandReplyById( Guid id ) throws Exception;
    List<LineInputDeviceCommandReplyObject> getLineInputDeviceCommandReplyCollection( ) throws Exception;
    List<LineInputDeviceCommandReplyObject> getLineInputDeviceCommandReplyCollectionByLineInputDevice( Guid lineInputDevice ) throws Exception;
    List<LineInputDeviceCommandReplyObject> getLineInputDeviceCommandReplyCollectionByLineInputDeviceAndTimestamp( Guid lineInputDevice, DateTime timestamp ) throws Exception;
    List<LineInputDeviceCommandReplyObject> getLineInputDeviceCommandReplyCollectionByLineInputDeviceAtTimestamp( Guid lineInputDevice, DateTime timestamp ) throws Exception;
    List<LineInputDeviceCommandReplyObject> getLineInputDeviceCommandReplyCollectionByLineInputDeviceFromTimestamp( Guid lineInputDevice, DateTime timestamp ) throws Exception;
    List<LineInputDeviceCommandReplyObject> getLineInputDeviceCommandReplyCollectionByLineInputDeviceUntilTimestamp( Guid lineInputDevice, DateTime timestamp ) throws Exception;
    List<LineInputDeviceCommandReplyObject> getLineInputDeviceCommandReplyCollectionByLineInputDeviceOverTimestamp( Guid lineInputDevice, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<LineInputDeviceCommandReplyObject> getLineInputDeviceCommandReplyCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<LineInputDeviceCommandReplyObject> getLineInputDeviceCommandReplyCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<LineInputDeviceCommandReplyObject> getLineInputDeviceCommandReplyCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<LineInputDeviceCommandReplyObject> getLineInputDeviceCommandReplyCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<LineInputDeviceCommandReplyObject> getLineInputDeviceCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    LineInputDeviceCommandReplyObject getLineInputDeviceCommandReplyByCommand( Guid command ) throws Exception;
    List<LineInputDeviceCommandReplyObject> qetLineInputDeviceCommandReplyCollectionByCommandIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // LineInputDeviceConfiguration queries
    // ---------------------------------------------------------------------
    LineInputDeviceConfigurationObject getLineInputDeviceConfigurationById( Guid id ) throws Exception;
    List<LineInputDeviceConfigurationObject> getLineInputDeviceConfigurationCollection( ) throws Exception;
    List<LineInputDeviceConfigurationObject> getLineInputDeviceConfigurationCollectionByLineInputDevice( Guid lineInputDevice ) throws Exception;
    LineInputDeviceConfigurationObject getLineInputDeviceConfigurationByLineInputDeviceAndTimestamp( Guid lineInputDevice, DateTime timestamp ) throws Exception;
    LineInputDeviceConfigurationObject getLineInputDeviceConfigurationByLineInputDeviceAtTimestamp( Guid lineInputDevice, DateTime timestamp ) throws Exception;
    List<LineInputDeviceConfigurationObject> getLineInputDeviceConfigurationByLineInputDeviceFromTimestamp( Guid lineInputDevice, DateTime timestamp ) throws Exception;
    List<LineInputDeviceConfigurationObject> getLineInputDeviceConfigurationByLineInputDeviceUntilTimestamp( Guid lineInputDevice, DateTime timestamp ) throws Exception;
    List<LineInputDeviceConfigurationObject> getLineInputDeviceConfigurationByLineInputDeviceOverTimestamp( Guid lineInputDevice, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<LineInputDeviceConfigurationObject> getLineInputDeviceConfigurationCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<LineInputDeviceConfigurationObject> getLineInputDeviceConfigurationCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<LineInputDeviceConfigurationObject> getLineInputDeviceConfigurationCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<LineInputDeviceConfigurationObject> getLineInputDeviceConfigurationCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<LineInputDeviceConfigurationObject> getLineInputDeviceConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // LineInputMessageRouting queries
    // ---------------------------------------------------------------------
    LineInputMessageRoutingObject getLineInputMessageRoutingById( Guid id ) throws Exception;
    List<LineInputMessageRoutingObject> getLineInputMessageRoutingCollection( ) throws Exception;
    List<LineInputMessageRoutingObject> getLineInputMessageRoutingCollectionByLineInputDevice( Guid lineInputDevice ) throws Exception;
    LineInputMessageRoutingObject getLineInputMessageRoutingByLineInputDeviceAndType( Guid lineInputDevice, String type ) throws Exception;
    // ---------------------------------------------------------------------
    // LineInputMessageRoutingDestination queries
    // ---------------------------------------------------------------------
    LineInputMessageRoutingDestinationObject getLineInputMessageRoutingDestinationById( Guid id ) throws Exception;
    List<LineInputMessageRoutingDestinationObject> getLineInputMessageRoutingDestinationCollection( ) throws Exception;
    List<LineInputMessageRoutingDestinationObject> getLineInputMessageRoutingDestinationCollectionByRouting( Guid routing ) throws Exception;
    List<LineInputMessageRoutingDestinationObject> qetLineInputMessageRoutingDestinationCollectionByRouting(  ) throws Exception;
    LineInputMessageRoutingDestinationObject getLineInputMessageRoutingDestinationByRoutingAndListener( Guid routing, Guid listener ) throws Exception;
    List<LineInputMessageRoutingDestinationObject> qetLineInputMessageRoutingDestinationCollectionByRoutingAndListenerIsNull( Guid routing ) throws Exception;
    List<LineInputMessageRoutingDestinationObject> getLineInputMessageRoutingDestinationCollectionByListener( Guid listener ) throws Exception;
    List<LineInputMessageRoutingDestinationObject> qetLineInputMessageRoutingDestinationCollectionByListenerIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // LineInputWhiteListEntry queries
    // ---------------------------------------------------------------------
    LineInputWhiteListEntryObject getLineInputWhiteListEntryById( Guid id ) throws Exception;
    List<LineInputWhiteListEntryObject> getLineInputWhiteListEntryCollection( ) throws Exception;
    List<LineInputWhiteListEntryObject> getLineInputWhiteListEntryCollectionByLineInputDevice( Guid lineInputDevice ) throws Exception;
    List<LineInputWhiteListEntryObject> getLineInputWhiteListEntryCollectionByLineInputDeviceAndHostName( Guid lineInputDevice, String hostName ) throws Exception;
    LineInputWhiteListEntryObject getLineInputWhiteListEntryByLineInputDeviceHostNameAndPort( Guid lineInputDevice, String hostName, int port ) throws Exception;
    List<LineInputWhiteListEntryObject> getLineInputWhiteListEntryByLineInputDeviceHostNameFromPort( Guid lineInputDevice, String hostName, int port ) throws Exception;
    List<LineInputWhiteListEntryObject> getLineInputWhiteListEntryByLineInputDeviceHostNameUntilPort( Guid lineInputDevice, String hostName, int port ) throws Exception;
    List<LineInputWhiteListEntryObject> getLineInputWhiteListEntryByLineInputDeviceHostNameOverPort( Guid lineInputDevice, String hostName, int fromPort, int untilPort ) throws Exception;
    // ---------------------------------------------------------------------
    // LogApplication queries
    // ---------------------------------------------------------------------
    LogApplicationObject getLogApplicationById( Guid id ) throws Exception;
    List<LogApplicationObject> getLogApplicationCollection( ) throws Exception;
    LogApplicationObject getLogApplicationByName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // LogApplicationConfiguration queries
    // ---------------------------------------------------------------------
    LogApplicationConfigurationObject getLogApplicationConfigurationById( Guid id ) throws Exception;
    List<LogApplicationConfigurationObject> getLogApplicationConfigurationCollection( ) throws Exception;
    List<LogApplicationConfigurationObject> getLogApplicationConfigurationCollectionByApplication( Guid application ) throws Exception;
    LogApplicationConfigurationObject getLogApplicationConfigurationByApplicationAndTimestamp( Guid application, DateTime timestamp ) throws Exception;
    LogApplicationConfigurationObject getLogApplicationConfigurationByApplicationAtTimestamp( Guid application, DateTime timestamp ) throws Exception;
    List<LogApplicationConfigurationObject> getLogApplicationConfigurationByApplicationFromTimestamp( Guid application, DateTime timestamp ) throws Exception;
    List<LogApplicationConfigurationObject> getLogApplicationConfigurationByApplicationUntilTimestamp( Guid application, DateTime timestamp ) throws Exception;
    List<LogApplicationConfigurationObject> getLogApplicationConfigurationByApplicationOverTimestamp( Guid application, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<LogApplicationConfigurationObject> getLogApplicationConfigurationCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<LogApplicationConfigurationObject> getLogApplicationConfigurationCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<LogApplicationConfigurationObject> getLogApplicationConfigurationCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<LogApplicationConfigurationObject> getLogApplicationConfigurationCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<LogApplicationConfigurationObject> getLogApplicationConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // LogHost queries
    // ---------------------------------------------------------------------
    LogHostObject getLogHostById( Guid id ) throws Exception;
    List<LogHostObject> getLogHostCollection( ) throws Exception;
    LogHostObject getLogHostByComputerName( String computerName ) throws Exception;
    // ---------------------------------------------------------------------
    // LogHostConfiguration queries
    // ---------------------------------------------------------------------
    LogHostConfigurationObject getLogHostConfigurationById( Guid id ) throws Exception;
    List<LogHostConfigurationObject> getLogHostConfigurationCollection( ) throws Exception;
    List<LogHostConfigurationObject> getLogHostConfigurationCollectionByHost( Guid host ) throws Exception;
    LogHostConfigurationObject getLogHostConfigurationByHostAndTimestamp( Guid host, DateTime timestamp ) throws Exception;
    LogHostConfigurationObject getLogHostConfigurationByHostAtTimestamp( Guid host, DateTime timestamp ) throws Exception;
    List<LogHostConfigurationObject> getLogHostConfigurationByHostFromTimestamp( Guid host, DateTime timestamp ) throws Exception;
    List<LogHostConfigurationObject> getLogHostConfigurationByHostUntilTimestamp( Guid host, DateTime timestamp ) throws Exception;
    List<LogHostConfigurationObject> getLogHostConfigurationByHostOverTimestamp( Guid host, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<LogHostConfigurationObject> getLogHostConfigurationCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<LogHostConfigurationObject> getLogHostConfigurationCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<LogHostConfigurationObject> getLogHostConfigurationCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<LogHostConfigurationObject> getLogHostConfigurationCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<LogHostConfigurationObject> getLogHostConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // LogLocation queries
    // ---------------------------------------------------------------------
    LogLocationObject getLogLocationById( Guid id ) throws Exception;
    List<LogLocationObject> getLogLocationCollection( ) throws Exception;
    List<LogLocationObject> getLogLocationCollectionByFileName( String fileName ) throws Exception;
    LogLocationObject getLogLocationByFileNameAndLineNumber( String fileName, int lineNumber ) throws Exception;
    List<LogLocationObject> getLogLocationByFileNameFromLineNumber( String fileName, int lineNumber ) throws Exception;
    List<LogLocationObject> getLogLocationByFileNameUntilLineNumber( String fileName, int lineNumber ) throws Exception;
    List<LogLocationObject> getLogLocationByFileNameOverLineNumber( String fileName, int fromLineNumber, int untilLineNumber ) throws Exception;
    // ---------------------------------------------------------------------
    // LogProcess queries
    // ---------------------------------------------------------------------
    LogProcessObject getLogProcessById( Guid id ) throws Exception;
    List<LogProcessObject> getLogProcessCollection( ) throws Exception;
    List<LogProcessObject> getLogProcessCollectionByApplication( Guid application ) throws Exception;
    List<LogProcessObject> getLogProcessCollectionByApplicationAndStarted( Guid application, DateTime started ) throws Exception;
    List<LogProcessObject> getLogProcessCollectionByApplicationAtStarted( Guid application, DateTime started ) throws Exception;
    List<LogProcessObject> getLogProcessCollectionByApplicationFromStarted( Guid application, DateTime started ) throws Exception;
    List<LogProcessObject> getLogProcessCollectionByApplicationUntilStarted( Guid application, DateTime started ) throws Exception;
    List<LogProcessObject> getLogProcessCollectionByApplicationOverStarted( Guid application, DateTime fromStarted, DateTime untilStarted ) throws Exception;
    List<LogProcessObject> getLogProcessCollectionByHost( Guid host ) throws Exception;
    List<LogProcessObject> qetLogProcessCollectionByHostIsNull(  ) throws Exception;
    List<LogProcessObject> getLogProcessCollectionByHostAndStarted( Guid host, DateTime started ) throws Exception;
    List<LogProcessObject> qetLogProcessCollectionByHostIsNullAndStarted( DateTime started ) throws Exception;
    List<LogProcessObject> getLogProcessCollectionByHostAtStarted( Guid host, DateTime started ) throws Exception;
    List<LogProcessObject> getLogProcessCollectionByHostFromStarted( Guid host, DateTime started ) throws Exception;
    List<LogProcessObject> getLogProcessCollectionByHostUntilStarted( Guid host, DateTime started ) throws Exception;
    List<LogProcessObject> getLogProcessCollectionByHostOverStarted( Guid host, DateTime fromStarted, DateTime untilStarted ) throws Exception;
    List<LogProcessObject> getLogProcessCollectionByStarted( DateTime started ) throws Exception;
    List<LogProcessObject> getLogProcessCollectionAtStarted( DateTime started ) throws Exception;
    List<LogProcessObject> getLogProcessCollectionFromStarted( DateTime started ) throws Exception;
    List<LogProcessObject> getLogProcessCollectionUntilStarted( DateTime started ) throws Exception;
    List<LogProcessObject> getLogProcessCollectionOverStarted( DateTime fromStarted, DateTime untilStarted ) throws Exception;
    // ---------------------------------------------------------------------
    // LogRecord queries
    // ---------------------------------------------------------------------
    LogRecordObject getLogRecordById( Guid id ) throws Exception;
    List<LogRecordObject> getLogRecordCollection( ) throws Exception;
    List<LogRecordObject> getLogRecordCollectionByThread( Guid thread ) throws Exception;
    List<LogRecordObject> getLogRecordCollectionByThreadAndTimestamp( Guid thread, DateTime timestamp ) throws Exception;
    List<LogRecordObject> getLogRecordCollectionByThreadAtTimestamp( Guid thread, DateTime timestamp ) throws Exception;
    List<LogRecordObject> getLogRecordCollectionByThreadFromTimestamp( Guid thread, DateTime timestamp ) throws Exception;
    List<LogRecordObject> getLogRecordCollectionByThreadUntilTimestamp( Guid thread, DateTime timestamp ) throws Exception;
    List<LogRecordObject> getLogRecordCollectionByThreadOverTimestamp( Guid thread, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<LogRecordObject> getLogRecordCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<LogRecordObject> getLogRecordCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<LogRecordObject> getLogRecordCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<LogRecordObject> getLogRecordCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<LogRecordObject> getLogRecordCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<LogRecordObject> getLogRecordCollectionByLocation( Guid location ) throws Exception;
    // ---------------------------------------------------------------------
    // LogThread queries
    // ---------------------------------------------------------------------
    LogThreadObject getLogThreadById( Guid id ) throws Exception;
    List<LogThreadObject> getLogThreadCollection( ) throws Exception;
    List<LogThreadObject> getLogThreadCollectionByProcess( Guid process ) throws Exception;
    List<LogThreadObject> getLogThreadCollectionByProcessAndStarted( Guid process, DateTime started ) throws Exception;
    List<LogThreadObject> getLogThreadCollectionByProcessAtStarted( Guid process, DateTime started ) throws Exception;
    List<LogThreadObject> getLogThreadCollectionByProcessFromStarted( Guid process, DateTime started ) throws Exception;
    List<LogThreadObject> getLogThreadCollectionByProcessUntilStarted( Guid process, DateTime started ) throws Exception;
    List<LogThreadObject> getLogThreadCollectionByProcessOverStarted( Guid process, DateTime fromStarted, DateTime untilStarted ) throws Exception;
    List<LogThreadObject> getLogThreadCollectionByStarted( DateTime started ) throws Exception;
    List<LogThreadObject> getLogThreadCollectionAtStarted( DateTime started ) throws Exception;
    List<LogThreadObject> getLogThreadCollectionFromStarted( DateTime started ) throws Exception;
    List<LogThreadObject> getLogThreadCollectionUntilStarted( DateTime started ) throws Exception;
    List<LogThreadObject> getLogThreadCollectionOverStarted( DateTime fromStarted, DateTime untilStarted ) throws Exception;
    // ---------------------------------------------------------------------
    // LogTraceEntry queries
    // ---------------------------------------------------------------------
    LogTraceEntryObject getLogTraceEntryById( Guid id ) throws Exception;
    List<LogTraceEntryObject> getLogTraceEntryCollection( ) throws Exception;
    List<LogTraceEntryObject> getLogTraceEntryCollectionByThread( Guid thread ) throws Exception;
    List<LogTraceEntryObject> getLogTraceEntryCollectionByThreadAndEntered( Guid thread, DateTime entered ) throws Exception;
    List<LogTraceEntryObject> getLogTraceEntryCollectionByThreadAtEntered( Guid thread, DateTime entered ) throws Exception;
    List<LogTraceEntryObject> getLogTraceEntryCollectionByThreadFromEntered( Guid thread, DateTime entered ) throws Exception;
    List<LogTraceEntryObject> getLogTraceEntryCollectionByThreadUntilEntered( Guid thread, DateTime entered ) throws Exception;
    List<LogTraceEntryObject> getLogTraceEntryCollectionByThreadOverEntered( Guid thread, DateTime fromEntered, DateTime untilEntered ) throws Exception;
    List<LogTraceEntryObject> getLogTraceEntryCollectionByLocation( Guid location ) throws Exception;
    List<LogTraceEntryObject> getLogTraceEntryCollectionByLocationAndEntered( Guid location, DateTime entered ) throws Exception;
    List<LogTraceEntryObject> getLogTraceEntryCollectionByLocationAtEntered( Guid location, DateTime entered ) throws Exception;
    List<LogTraceEntryObject> getLogTraceEntryCollectionByLocationFromEntered( Guid location, DateTime entered ) throws Exception;
    List<LogTraceEntryObject> getLogTraceEntryCollectionByLocationUntilEntered( Guid location, DateTime entered ) throws Exception;
    List<LogTraceEntryObject> getLogTraceEntryCollectionByLocationOverEntered( Guid location, DateTime fromEntered, DateTime untilEntered ) throws Exception;
    List<LogTraceEntryObject> getLogTraceEntryCollectionByEntered( DateTime entered ) throws Exception;
    List<LogTraceEntryObject> getLogTraceEntryCollectionAtEntered( DateTime entered ) throws Exception;
    List<LogTraceEntryObject> getLogTraceEntryCollectionFromEntered( DateTime entered ) throws Exception;
    List<LogTraceEntryObject> getLogTraceEntryCollectionUntilEntered( DateTime entered ) throws Exception;
    List<LogTraceEntryObject> getLogTraceEntryCollectionOverEntered( DateTime fromEntered, DateTime untilEntered ) throws Exception;
    // ---------------------------------------------------------------------
    // MapElement queries
    // ---------------------------------------------------------------------
    MapElementObject getMapElementById( Guid id ) throws Exception;
    List<MapElementObject> getMapElementCollection( ) throws Exception;
    List<MapElementObject> getMapElementCollectionByItem( Guid item ) throws Exception;
    // ---------------------------------------------------------------------
    // MapInfo queries
    // ---------------------------------------------------------------------
    MapInfoObject getMapInfoById( Guid id ) throws Exception;
    List<MapInfoObject> getMapInfoCollection( ) throws Exception;
    // ---------------------------------------------------------------------
    // MapServiceOptions queries
    // ---------------------------------------------------------------------
    MapServiceOptionsObject getMapServiceOptionsById( Guid id ) throws Exception;
    List<MapServiceOptionsObject> getMapServiceOptionsCollection( ) throws Exception;
    MapServiceOptionsObject getMapServiceOptionsByTimestamp( DateTime timestamp ) throws Exception;
    MapServiceOptionsObject getMapServiceOptionsAtTimestamp( DateTime timestamp ) throws Exception;
    List<MapServiceOptionsObject> getMapServiceOptionsFromTimestamp( DateTime timestamp ) throws Exception;
    List<MapServiceOptionsObject> getMapServiceOptionsUntilTimestamp( DateTime timestamp ) throws Exception;
    List<MapServiceOptionsObject> getMapServiceOptionsOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // MaritimeIdentificationDigits queries
    // ---------------------------------------------------------------------
    MaritimeIdentificationDigitsObject getMaritimeIdentificationDigitsById( Guid id ) throws Exception;
    List<MaritimeIdentificationDigitsObject> getMaritimeIdentificationDigitsCollection( ) throws Exception;
    MaritimeIdentificationDigitsObject getMaritimeIdentificationDigitsByCode( int code ) throws Exception;
    List<MaritimeIdentificationDigitsObject> getMaritimeIdentificationDigitsFromCode( int code ) throws Exception;
    List<MaritimeIdentificationDigitsObject> getMaritimeIdentificationDigitsUntilCode( int code ) throws Exception;
    List<MaritimeIdentificationDigitsObject> getMaritimeIdentificationDigitsOverCode( int fromCode, int untilCode ) throws Exception;
    List<MaritimeIdentificationDigitsObject> getMaritimeIdentificationDigitsCollectionByCountry( Guid country ) throws Exception;
    // ---------------------------------------------------------------------
    // MediaProxySession queries
    // ---------------------------------------------------------------------
    MediaProxySessionObject getMediaProxySessionById( Guid id ) throws Exception;
    List<MediaProxySessionObject> getMediaProxySessionCollection( ) throws Exception;
    List<MediaProxySessionObject> getMediaProxySessionCollectionByService( Guid service ) throws Exception;
    MediaProxySessionObject getMediaProxySessionByServiceAndName( Guid service, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // MediaProxySessionFile queries
    // ---------------------------------------------------------------------
    MediaProxySessionFileObject getMediaProxySessionFileById( Guid id ) throws Exception;
    List<MediaProxySessionFileObject> getMediaProxySessionFileCollection( ) throws Exception;
    List<MediaProxySessionFileObject> getMediaProxySessionFileCollectionByProxySession( Guid proxySession ) throws Exception;
    MediaProxySessionFileObject getMediaProxySessionFileByProxySessionAndTimestamp( Guid proxySession, DateTime timestamp ) throws Exception;
    MediaProxySessionFileObject getMediaProxySessionFileByProxySessionAtTimestamp( Guid proxySession, DateTime timestamp ) throws Exception;
    List<MediaProxySessionFileObject> getMediaProxySessionFileByProxySessionFromTimestamp( Guid proxySession, DateTime timestamp ) throws Exception;
    List<MediaProxySessionFileObject> getMediaProxySessionFileByProxySessionUntilTimestamp( Guid proxySession, DateTime timestamp ) throws Exception;
    List<MediaProxySessionFileObject> getMediaProxySessionFileByProxySessionOverTimestamp( Guid proxySession, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // MediaProxySessionOptions queries
    // ---------------------------------------------------------------------
    MediaProxySessionOptionsObject getMediaProxySessionOptionsById( Guid id ) throws Exception;
    List<MediaProxySessionOptionsObject> getMediaProxySessionOptionsCollection( ) throws Exception;
    List<MediaProxySessionOptionsObject> getMediaProxySessionOptionsCollectionByProxySession( Guid proxySession ) throws Exception;
    MediaProxySessionOptionsObject getMediaProxySessionOptionsByProxySessionAndTimestamp( Guid proxySession, DateTime timestamp ) throws Exception;
    MediaProxySessionOptionsObject getMediaProxySessionOptionsByProxySessionAtTimestamp( Guid proxySession, DateTime timestamp ) throws Exception;
    List<MediaProxySessionOptionsObject> getMediaProxySessionOptionsByProxySessionFromTimestamp( Guid proxySession, DateTime timestamp ) throws Exception;
    List<MediaProxySessionOptionsObject> getMediaProxySessionOptionsByProxySessionUntilTimestamp( Guid proxySession, DateTime timestamp ) throws Exception;
    List<MediaProxySessionOptionsObject> getMediaProxySessionOptionsByProxySessionOverTimestamp( Guid proxySession, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // MediaService queries
    // ---------------------------------------------------------------------
    MediaServiceObject getMediaServiceById( Guid id ) throws Exception;
    List<MediaServiceObject> getMediaServiceCollection( ) throws Exception;
    // ---------------------------------------------------------------------
    // MediaServiceOptions queries
    // ---------------------------------------------------------------------
    MediaServiceOptionsObject getMediaServiceOptionsById( Guid id ) throws Exception;
    List<MediaServiceOptionsObject> getMediaServiceOptionsCollection( ) throws Exception;
    List<MediaServiceOptionsObject> getMediaServiceOptionsCollectionByMediaService( Guid mediaService ) throws Exception;
    MediaServiceOptionsObject getMediaServiceOptionsByMediaServiceAndTimestamp( Guid mediaService, DateTime timestamp ) throws Exception;
    MediaServiceOptionsObject getMediaServiceOptionsByMediaServiceAtTimestamp( Guid mediaService, DateTime timestamp ) throws Exception;
    List<MediaServiceOptionsObject> getMediaServiceOptionsByMediaServiceFromTimestamp( Guid mediaService, DateTime timestamp ) throws Exception;
    List<MediaServiceOptionsObject> getMediaServiceOptionsByMediaServiceUntilTimestamp( Guid mediaService, DateTime timestamp ) throws Exception;
    List<MediaServiceOptionsObject> getMediaServiceOptionsByMediaServiceOverTimestamp( Guid mediaService, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // NamespaceElement queries
    // ---------------------------------------------------------------------
    NamespaceElementObject getNamespaceElementById( Guid id ) throws Exception;
    List<NamespaceElementObject> getNamespaceElementCollection( ) throws Exception;
    List<NamespaceElementObject> getNamespaceElementCollectionByNamespace( Guid namespace ) throws Exception;
    NamespaceElementObject getNamespaceElementByNamespaceAndName( Guid namespace, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // ElementType queries
    // ---------------------------------------------------------------------
    ElementTypeObject getElementTypeById( Guid id ) throws Exception;
    List<ElementTypeObject> getElementTypeCollection( ) throws Exception;
    List<ElementTypeObject> getElementTypeCollectionByNamespace( Guid namespace ) throws Exception;
    ElementTypeObject getElementTypeByNamespaceAndName( Guid namespace, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // Namespace queries
    // ---------------------------------------------------------------------
    NamespaceObject getNamespaceById( Guid id ) throws Exception;
    List<NamespaceObject> getNamespaceCollection( ) throws Exception;
    List<NamespaceObject> getNamespaceCollectionByNamespace( Guid namespace ) throws Exception;
    NamespaceObject getNamespaceByNamespaceAndName( Guid namespace, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // OilSpill queries
    // ---------------------------------------------------------------------
    OilSpillObject getOilSpillById( Guid id ) throws Exception;
    List<OilSpillObject> getOilSpillCollection( ) throws Exception;
    List<OilSpillObject> getOilSpillCollectionByOilSpillDetector( Guid oilSpillDetector ) throws Exception;
    List<OilSpillObject> getOilSpillCollectionByOilSpillDetectorAndTimestamp( Guid oilSpillDetector, DateTime timestamp ) throws Exception;
    List<OilSpillObject> getOilSpillCollectionByOilSpillDetectorAtTimestamp( Guid oilSpillDetector, DateTime timestamp ) throws Exception;
    List<OilSpillObject> getOilSpillCollectionByOilSpillDetectorFromTimestamp( Guid oilSpillDetector, DateTime timestamp ) throws Exception;
    List<OilSpillObject> getOilSpillCollectionByOilSpillDetectorUntilTimestamp( Guid oilSpillDetector, DateTime timestamp ) throws Exception;
    List<OilSpillObject> getOilSpillCollectionByOilSpillDetectorOverTimestamp( Guid oilSpillDetector, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<OilSpillObject> getOilSpillCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<OilSpillObject> getOilSpillCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<OilSpillObject> getOilSpillCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<OilSpillObject> getOilSpillCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<OilSpillObject> getOilSpillCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // OilSpillDetectorCommand queries
    // ---------------------------------------------------------------------
    OilSpillDetectorCommandObject getOilSpillDetectorCommandById( Guid id ) throws Exception;
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollection( ) throws Exception;
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollectionByOilSpillDetector( Guid oilSpillDetector ) throws Exception;
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollectionByOilSpillDetectorAndTimestamp( Guid oilSpillDetector, DateTime timestamp ) throws Exception;
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollectionByOilSpillDetectorAtTimestamp( Guid oilSpillDetector, DateTime timestamp ) throws Exception;
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollectionByOilSpillDetectorFromTimestamp( Guid oilSpillDetector, DateTime timestamp ) throws Exception;
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollectionByOilSpillDetectorUntilTimestamp( Guid oilSpillDetector, DateTime timestamp ) throws Exception;
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollectionByOilSpillDetectorOverTimestamp( Guid oilSpillDetector, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<OilSpillDetectorCommandObject> getOilSpillDetectorCommandCollectionByReply( Guid reply ) throws Exception;
    List<OilSpillDetectorCommandObject> qetOilSpillDetectorCommandCollectionByReplyIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // OilSpillDetectorCommandReply queries
    // ---------------------------------------------------------------------
    OilSpillDetectorCommandReplyObject getOilSpillDetectorCommandReplyById( Guid id ) throws Exception;
    List<OilSpillDetectorCommandReplyObject> getOilSpillDetectorCommandReplyCollection( ) throws Exception;
    List<OilSpillDetectorCommandReplyObject> getOilSpillDetectorCommandReplyCollectionByOilSpillDetector( Guid oilSpillDetector ) throws Exception;
    List<OilSpillDetectorCommandReplyObject> getOilSpillDetectorCommandReplyCollectionByOilSpillDetectorAndTimestamp( Guid oilSpillDetector, DateTime timestamp ) throws Exception;
    List<OilSpillDetectorCommandReplyObject> getOilSpillDetectorCommandReplyCollectionByOilSpillDetectorAtTimestamp( Guid oilSpillDetector, DateTime timestamp ) throws Exception;
    List<OilSpillDetectorCommandReplyObject> getOilSpillDetectorCommandReplyCollectionByOilSpillDetectorFromTimestamp( Guid oilSpillDetector, DateTime timestamp ) throws Exception;
    List<OilSpillDetectorCommandReplyObject> getOilSpillDetectorCommandReplyCollectionByOilSpillDetectorUntilTimestamp( Guid oilSpillDetector, DateTime timestamp ) throws Exception;
    List<OilSpillDetectorCommandReplyObject> getOilSpillDetectorCommandReplyCollectionByOilSpillDetectorOverTimestamp( Guid oilSpillDetector, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<OilSpillDetectorCommandReplyObject> getOilSpillDetectorCommandReplyCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<OilSpillDetectorCommandReplyObject> getOilSpillDetectorCommandReplyCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<OilSpillDetectorCommandReplyObject> getOilSpillDetectorCommandReplyCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<OilSpillDetectorCommandReplyObject> getOilSpillDetectorCommandReplyCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<OilSpillDetectorCommandReplyObject> getOilSpillDetectorCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    OilSpillDetectorCommandReplyObject getOilSpillDetectorCommandReplyByCommand( Guid command ) throws Exception;
    List<OilSpillDetectorCommandReplyObject> qetOilSpillDetectorCommandReplyCollectionByCommandIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // OilSpillDetectorConfiguration queries
    // ---------------------------------------------------------------------
    OilSpillDetectorConfigurationObject getOilSpillDetectorConfigurationById( Guid id ) throws Exception;
    List<OilSpillDetectorConfigurationObject> getOilSpillDetectorConfigurationCollection( ) throws Exception;
    List<OilSpillDetectorConfigurationObject> getOilSpillDetectorConfigurationCollectionByOilSpillDetector( Guid oilSpillDetector ) throws Exception;
    OilSpillDetectorConfigurationObject getOilSpillDetectorConfigurationByOilSpillDetectorAndTimestamp( Guid oilSpillDetector, DateTime timestamp ) throws Exception;
    OilSpillDetectorConfigurationObject getOilSpillDetectorConfigurationByOilSpillDetectorAtTimestamp( Guid oilSpillDetector, DateTime timestamp ) throws Exception;
    List<OilSpillDetectorConfigurationObject> getOilSpillDetectorConfigurationByOilSpillDetectorFromTimestamp( Guid oilSpillDetector, DateTime timestamp ) throws Exception;
    List<OilSpillDetectorConfigurationObject> getOilSpillDetectorConfigurationByOilSpillDetectorUntilTimestamp( Guid oilSpillDetector, DateTime timestamp ) throws Exception;
    List<OilSpillDetectorConfigurationObject> getOilSpillDetectorConfigurationByOilSpillDetectorOverTimestamp( Guid oilSpillDetector, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<OilSpillDetectorConfigurationObject> getOilSpillDetectorConfigurationCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<OilSpillDetectorConfigurationObject> getOilSpillDetectorConfigurationCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<OilSpillDetectorConfigurationObject> getOilSpillDetectorConfigurationCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<OilSpillDetectorConfigurationObject> getOilSpillDetectorConfigurationCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<OilSpillDetectorConfigurationObject> getOilSpillDetectorConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<OilSpillDetectorConfigurationObject> getOilSpillDetectorConfigurationCollectionByTargetMMSI( Guid targetMMSI ) throws Exception;
    List<OilSpillDetectorConfigurationObject> qetOilSpillDetectorConfigurationCollectionByTargetMMSIIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // Position2DTimeseriesValue queries
    // ---------------------------------------------------------------------
    Position2DTimeseriesValueObject getPosition2DTimeseriesValueById( Guid id ) throws Exception;
    List<Position2DTimeseriesValueObject> getPosition2DTimeseriesValueCollection( ) throws Exception;
    List<Position2DTimeseriesValueObject> getPosition2DTimeseriesValueCollectionByTimeseries( Guid timeseries ) throws Exception;
    Position2DTimeseriesValueObject getPosition2DTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    Position2DTimeseriesValueObject getPosition2DTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<Position2DTimeseriesValueObject> getPosition2DTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<Position2DTimeseriesValueObject> getPosition2DTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<Position2DTimeseriesValueObject> getPosition2DTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<Position2DTimeseriesValueObject> getPosition2DTimeseriesValueCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<Position2DTimeseriesValueObject> getPosition2DTimeseriesValueCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<Position2DTimeseriesValueObject> getPosition2DTimeseriesValueCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<Position2DTimeseriesValueObject> getPosition2DTimeseriesValueCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<Position2DTimeseriesValueObject> getPosition2DTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // Position3DTimeseriesValue queries
    // ---------------------------------------------------------------------
    Position3DTimeseriesValueObject getPosition3DTimeseriesValueById( Guid id ) throws Exception;
    List<Position3DTimeseriesValueObject> getPosition3DTimeseriesValueCollection( ) throws Exception;
    List<Position3DTimeseriesValueObject> getPosition3DTimeseriesValueCollectionByTimeseries( Guid timeseries ) throws Exception;
    Position3DTimeseriesValueObject getPosition3DTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    Position3DTimeseriesValueObject getPosition3DTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<Position3DTimeseriesValueObject> getPosition3DTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<Position3DTimeseriesValueObject> getPosition3DTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<Position3DTimeseriesValueObject> getPosition3DTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<Position3DTimeseriesValueObject> getPosition3DTimeseriesValueCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<Position3DTimeseriesValueObject> getPosition3DTimeseriesValueCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<Position3DTimeseriesValueObject> getPosition3DTimeseriesValueCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<Position3DTimeseriesValueObject> getPosition3DTimeseriesValueCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<Position3DTimeseriesValueObject> getPosition3DTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // ProcessTrackValueResult queries
    // ---------------------------------------------------------------------
    ProcessTrackValueResultObject getProcessTrackValueResultById( Guid id ) throws Exception;
    List<ProcessTrackValueResultObject> getProcessTrackValueResultCollection( ) throws Exception;
    // ---------------------------------------------------------------------
    // Property queries
    // ---------------------------------------------------------------------
    PropertyObject getPropertyById( Guid id ) throws Exception;
    List<PropertyObject> getPropertyCollection( ) throws Exception;
    List<PropertyObject> getPropertyCollectionByElement( Guid element ) throws Exception;
    PropertyObject getPropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<PropertyObject> getPropertyCollectionByDefinition( Guid definition ) throws Exception;
    // ---------------------------------------------------------------------
    // BinaryProperty queries
    // ---------------------------------------------------------------------
    BinaryPropertyObject getBinaryPropertyById( Guid id ) throws Exception;
    List<BinaryPropertyObject> getBinaryPropertyCollection( ) throws Exception;
    List<BinaryPropertyObject> getBinaryPropertyCollectionByElement( Guid element ) throws Exception;
    BinaryPropertyObject getBinaryPropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<BinaryPropertyObject> getBinaryPropertyCollectionByDefinition( Guid definition ) throws Exception;
    // ---------------------------------------------------------------------
    // BooleanProperty queries
    // ---------------------------------------------------------------------
    BooleanPropertyObject getBooleanPropertyById( Guid id ) throws Exception;
    List<BooleanPropertyObject> getBooleanPropertyCollection( ) throws Exception;
    List<BooleanPropertyObject> getBooleanPropertyCollectionByElement( Guid element ) throws Exception;
    BooleanPropertyObject getBooleanPropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<BooleanPropertyObject> getBooleanPropertyCollectionByDefinition( Guid definition ) throws Exception;
    // ---------------------------------------------------------------------
    // ByteProperty queries
    // ---------------------------------------------------------------------
    BytePropertyObject getBytePropertyById( Guid id ) throws Exception;
    List<BytePropertyObject> getBytePropertyCollection( ) throws Exception;
    List<BytePropertyObject> getBytePropertyCollectionByElement( Guid element ) throws Exception;
    BytePropertyObject getBytePropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<BytePropertyObject> getBytePropertyCollectionByDefinition( Guid definition ) throws Exception;
    // ---------------------------------------------------------------------
    // DateTimeProperty queries
    // ---------------------------------------------------------------------
    DateTimePropertyObject getDateTimePropertyById( Guid id ) throws Exception;
    List<DateTimePropertyObject> getDateTimePropertyCollection( ) throws Exception;
    List<DateTimePropertyObject> getDateTimePropertyCollectionByElement( Guid element ) throws Exception;
    DateTimePropertyObject getDateTimePropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<DateTimePropertyObject> getDateTimePropertyCollectionByDefinition( Guid definition ) throws Exception;
    // ---------------------------------------------------------------------
    // DoubleProperty queries
    // ---------------------------------------------------------------------
    DoublePropertyObject getDoublePropertyById( Guid id ) throws Exception;
    List<DoublePropertyObject> getDoublePropertyCollection( ) throws Exception;
    List<DoublePropertyObject> getDoublePropertyCollectionByElement( Guid element ) throws Exception;
    DoublePropertyObject getDoublePropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<DoublePropertyObject> getDoublePropertyCollectionByDefinition( Guid definition ) throws Exception;
    // ---------------------------------------------------------------------
    // GuidProperty queries
    // ---------------------------------------------------------------------
    GuidPropertyObject getGuidPropertyById( Guid id ) throws Exception;
    List<GuidPropertyObject> getGuidPropertyCollection( ) throws Exception;
    List<GuidPropertyObject> getGuidPropertyCollectionByElement( Guid element ) throws Exception;
    GuidPropertyObject getGuidPropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<GuidPropertyObject> getGuidPropertyCollectionByDefinition( Guid definition ) throws Exception;
    // ---------------------------------------------------------------------
    // Int16Property queries
    // ---------------------------------------------------------------------
    Int16PropertyObject getInt16PropertyById( Guid id ) throws Exception;
    List<Int16PropertyObject> getInt16PropertyCollection( ) throws Exception;
    List<Int16PropertyObject> getInt16PropertyCollectionByElement( Guid element ) throws Exception;
    Int16PropertyObject getInt16PropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<Int16PropertyObject> getInt16PropertyCollectionByDefinition( Guid definition ) throws Exception;
    // ---------------------------------------------------------------------
    // Int32Property queries
    // ---------------------------------------------------------------------
    Int32PropertyObject getInt32PropertyById( Guid id ) throws Exception;
    List<Int32PropertyObject> getInt32PropertyCollection( ) throws Exception;
    List<Int32PropertyObject> getInt32PropertyCollectionByElement( Guid element ) throws Exception;
    Int32PropertyObject getInt32PropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<Int32PropertyObject> getInt32PropertyCollectionByDefinition( Guid definition ) throws Exception;
    // ---------------------------------------------------------------------
    // Int64Property queries
    // ---------------------------------------------------------------------
    Int64PropertyObject getInt64PropertyById( Guid id ) throws Exception;
    List<Int64PropertyObject> getInt64PropertyCollection( ) throws Exception;
    List<Int64PropertyObject> getInt64PropertyCollectionByElement( Guid element ) throws Exception;
    Int64PropertyObject getInt64PropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<Int64PropertyObject> getInt64PropertyCollectionByDefinition( Guid definition ) throws Exception;
    // ---------------------------------------------------------------------
    // ReferenceProperty queries
    // ---------------------------------------------------------------------
    ReferencePropertyObject getReferencePropertyById( Guid id ) throws Exception;
    List<ReferencePropertyObject> getReferencePropertyCollection( ) throws Exception;
    List<ReferencePropertyObject> getReferencePropertyCollectionByElement( Guid element ) throws Exception;
    ReferencePropertyObject getReferencePropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<ReferencePropertyObject> getReferencePropertyCollectionByDefinition( Guid definition ) throws Exception;
    List<ReferencePropertyObject> getReferencePropertyCollectionByValue( Guid value ) throws Exception;
    List<ReferencePropertyObject> qetReferencePropertyCollectionByValueIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // SByteProperty queries
    // ---------------------------------------------------------------------
    SBytePropertyObject getSBytePropertyById( Guid id ) throws Exception;
    List<SBytePropertyObject> getSBytePropertyCollection( ) throws Exception;
    List<SBytePropertyObject> getSBytePropertyCollectionByElement( Guid element ) throws Exception;
    SBytePropertyObject getSBytePropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<SBytePropertyObject> getSBytePropertyCollectionByDefinition( Guid definition ) throws Exception;
    // ---------------------------------------------------------------------
    // SingleProperty queries
    // ---------------------------------------------------------------------
    SinglePropertyObject getSinglePropertyById( Guid id ) throws Exception;
    List<SinglePropertyObject> getSinglePropertyCollection( ) throws Exception;
    List<SinglePropertyObject> getSinglePropertyCollectionByElement( Guid element ) throws Exception;
    SinglePropertyObject getSinglePropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<SinglePropertyObject> getSinglePropertyCollectionByDefinition( Guid definition ) throws Exception;
    // ---------------------------------------------------------------------
    // StringProperty queries
    // ---------------------------------------------------------------------
    StringPropertyObject getStringPropertyById( Guid id ) throws Exception;
    List<StringPropertyObject> getStringPropertyCollection( ) throws Exception;
    List<StringPropertyObject> getStringPropertyCollectionByElement( Guid element ) throws Exception;
    StringPropertyObject getStringPropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<StringPropertyObject> getStringPropertyCollectionByDefinition( Guid definition ) throws Exception;
    // ---------------------------------------------------------------------
    // TimeseriesProperty queries
    // ---------------------------------------------------------------------
    TimeseriesPropertyObject getTimeseriesPropertyById( Guid id ) throws Exception;
    List<TimeseriesPropertyObject> getTimeseriesPropertyCollection( ) throws Exception;
    List<TimeseriesPropertyObject> getTimeseriesPropertyCollectionByElement( Guid element ) throws Exception;
    TimeseriesPropertyObject getTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<TimeseriesPropertyObject> getTimeseriesPropertyCollectionByDefinition( Guid definition ) throws Exception;
    // ---------------------------------------------------------------------
    // BinaryTimeseriesProperty queries
    // ---------------------------------------------------------------------
    BinaryTimeseriesPropertyObject getBinaryTimeseriesPropertyById( Guid id ) throws Exception;
    List<BinaryTimeseriesPropertyObject> getBinaryTimeseriesPropertyCollection( ) throws Exception;
    List<BinaryTimeseriesPropertyObject> getBinaryTimeseriesPropertyCollectionByElement( Guid element ) throws Exception;
    BinaryTimeseriesPropertyObject getBinaryTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<BinaryTimeseriesPropertyObject> getBinaryTimeseriesPropertyCollectionByDefinition( Guid definition ) throws Exception;
    List<BinaryTimeseriesPropertyObject> getBinaryTimeseriesPropertyCollectionByTimeseries( Guid timeseries ) throws Exception;
    List<BinaryTimeseriesPropertyObject> qetBinaryTimeseriesPropertyCollectionByTimeseriesIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // BooleanTimeseriesProperty queries
    // ---------------------------------------------------------------------
    BooleanTimeseriesPropertyObject getBooleanTimeseriesPropertyById( Guid id ) throws Exception;
    List<BooleanTimeseriesPropertyObject> getBooleanTimeseriesPropertyCollection( ) throws Exception;
    List<BooleanTimeseriesPropertyObject> getBooleanTimeseriesPropertyCollectionByElement( Guid element ) throws Exception;
    BooleanTimeseriesPropertyObject getBooleanTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<BooleanTimeseriesPropertyObject> getBooleanTimeseriesPropertyCollectionByDefinition( Guid definition ) throws Exception;
    List<BooleanTimeseriesPropertyObject> getBooleanTimeseriesPropertyCollectionByTimeseries( Guid timeseries ) throws Exception;
    List<BooleanTimeseriesPropertyObject> qetBooleanTimeseriesPropertyCollectionByTimeseriesIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // ByteTimeseriesProperty queries
    // ---------------------------------------------------------------------
    ByteTimeseriesPropertyObject getByteTimeseriesPropertyById( Guid id ) throws Exception;
    List<ByteTimeseriesPropertyObject> getByteTimeseriesPropertyCollection( ) throws Exception;
    List<ByteTimeseriesPropertyObject> getByteTimeseriesPropertyCollectionByElement( Guid element ) throws Exception;
    ByteTimeseriesPropertyObject getByteTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<ByteTimeseriesPropertyObject> getByteTimeseriesPropertyCollectionByDefinition( Guid definition ) throws Exception;
    List<ByteTimeseriesPropertyObject> getByteTimeseriesPropertyCollectionByTimeseries( Guid timeseries ) throws Exception;
    List<ByteTimeseriesPropertyObject> qetByteTimeseriesPropertyCollectionByTimeseriesIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // DateTimeTimeseriesProperty queries
    // ---------------------------------------------------------------------
    DateTimeTimeseriesPropertyObject getDateTimeTimeseriesPropertyById( Guid id ) throws Exception;
    List<DateTimeTimeseriesPropertyObject> getDateTimeTimeseriesPropertyCollection( ) throws Exception;
    List<DateTimeTimeseriesPropertyObject> getDateTimeTimeseriesPropertyCollectionByElement( Guid element ) throws Exception;
    DateTimeTimeseriesPropertyObject getDateTimeTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<DateTimeTimeseriesPropertyObject> getDateTimeTimeseriesPropertyCollectionByDefinition( Guid definition ) throws Exception;
    List<DateTimeTimeseriesPropertyObject> getDateTimeTimeseriesPropertyCollectionByTimeseries( Guid timeseries ) throws Exception;
    List<DateTimeTimeseriesPropertyObject> qetDateTimeTimeseriesPropertyCollectionByTimeseriesIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // DoubleTimeseriesProperty queries
    // ---------------------------------------------------------------------
    DoubleTimeseriesPropertyObject getDoubleTimeseriesPropertyById( Guid id ) throws Exception;
    List<DoubleTimeseriesPropertyObject> getDoubleTimeseriesPropertyCollection( ) throws Exception;
    List<DoubleTimeseriesPropertyObject> getDoubleTimeseriesPropertyCollectionByElement( Guid element ) throws Exception;
    DoubleTimeseriesPropertyObject getDoubleTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<DoubleTimeseriesPropertyObject> getDoubleTimeseriesPropertyCollectionByDefinition( Guid definition ) throws Exception;
    List<DoubleTimeseriesPropertyObject> getDoubleTimeseriesPropertyCollectionByTimeseries( Guid timeseries ) throws Exception;
    List<DoubleTimeseriesPropertyObject> qetDoubleTimeseriesPropertyCollectionByTimeseriesIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // GuidTimeseriesProperty queries
    // ---------------------------------------------------------------------
    GuidTimeseriesPropertyObject getGuidTimeseriesPropertyById( Guid id ) throws Exception;
    List<GuidTimeseriesPropertyObject> getGuidTimeseriesPropertyCollection( ) throws Exception;
    List<GuidTimeseriesPropertyObject> getGuidTimeseriesPropertyCollectionByElement( Guid element ) throws Exception;
    GuidTimeseriesPropertyObject getGuidTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<GuidTimeseriesPropertyObject> getGuidTimeseriesPropertyCollectionByDefinition( Guid definition ) throws Exception;
    List<GuidTimeseriesPropertyObject> getGuidTimeseriesPropertyCollectionByTimeseries( Guid timeseries ) throws Exception;
    List<GuidTimeseriesPropertyObject> qetGuidTimeseriesPropertyCollectionByTimeseriesIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // Int16TimeseriesProperty queries
    // ---------------------------------------------------------------------
    Int16TimeseriesPropertyObject getInt16TimeseriesPropertyById( Guid id ) throws Exception;
    List<Int16TimeseriesPropertyObject> getInt16TimeseriesPropertyCollection( ) throws Exception;
    List<Int16TimeseriesPropertyObject> getInt16TimeseriesPropertyCollectionByElement( Guid element ) throws Exception;
    Int16TimeseriesPropertyObject getInt16TimeseriesPropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<Int16TimeseriesPropertyObject> getInt16TimeseriesPropertyCollectionByDefinition( Guid definition ) throws Exception;
    List<Int16TimeseriesPropertyObject> getInt16TimeseriesPropertyCollectionByTimeseries( Guid timeseries ) throws Exception;
    List<Int16TimeseriesPropertyObject> qetInt16TimeseriesPropertyCollectionByTimeseriesIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // Int32TimeseriesProperty queries
    // ---------------------------------------------------------------------
    Int32TimeseriesPropertyObject getInt32TimeseriesPropertyById( Guid id ) throws Exception;
    List<Int32TimeseriesPropertyObject> getInt32TimeseriesPropertyCollection( ) throws Exception;
    List<Int32TimeseriesPropertyObject> getInt32TimeseriesPropertyCollectionByElement( Guid element ) throws Exception;
    Int32TimeseriesPropertyObject getInt32TimeseriesPropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<Int32TimeseriesPropertyObject> getInt32TimeseriesPropertyCollectionByDefinition( Guid definition ) throws Exception;
    List<Int32TimeseriesPropertyObject> getInt32TimeseriesPropertyCollectionByTimeseries( Guid timeseries ) throws Exception;
    List<Int32TimeseriesPropertyObject> qetInt32TimeseriesPropertyCollectionByTimeseriesIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // Int64TimeseriesProperty queries
    // ---------------------------------------------------------------------
    Int64TimeseriesPropertyObject getInt64TimeseriesPropertyById( Guid id ) throws Exception;
    List<Int64TimeseriesPropertyObject> getInt64TimeseriesPropertyCollection( ) throws Exception;
    List<Int64TimeseriesPropertyObject> getInt64TimeseriesPropertyCollectionByElement( Guid element ) throws Exception;
    Int64TimeseriesPropertyObject getInt64TimeseriesPropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<Int64TimeseriesPropertyObject> getInt64TimeseriesPropertyCollectionByDefinition( Guid definition ) throws Exception;
    List<Int64TimeseriesPropertyObject> getInt64TimeseriesPropertyCollectionByTimeseries( Guid timeseries ) throws Exception;
    List<Int64TimeseriesPropertyObject> qetInt64TimeseriesPropertyCollectionByTimeseriesIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // ReferenceTimeseriesProperty queries
    // ---------------------------------------------------------------------
    ReferenceTimeseriesPropertyObject getReferenceTimeseriesPropertyById( Guid id ) throws Exception;
    List<ReferenceTimeseriesPropertyObject> getReferenceTimeseriesPropertyCollection( ) throws Exception;
    List<ReferenceTimeseriesPropertyObject> getReferenceTimeseriesPropertyCollectionByElement( Guid element ) throws Exception;
    ReferenceTimeseriesPropertyObject getReferenceTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<ReferenceTimeseriesPropertyObject> getReferenceTimeseriesPropertyCollectionByDefinition( Guid definition ) throws Exception;
    List<ReferenceTimeseriesPropertyObject> getReferenceTimeseriesPropertyCollectionByTimeseries( Guid timeseries ) throws Exception;
    List<ReferenceTimeseriesPropertyObject> qetReferenceTimeseriesPropertyCollectionByTimeseriesIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // SByteTimeseriesProperty queries
    // ---------------------------------------------------------------------
    SByteTimeseriesPropertyObject getSByteTimeseriesPropertyById( Guid id ) throws Exception;
    List<SByteTimeseriesPropertyObject> getSByteTimeseriesPropertyCollection( ) throws Exception;
    List<SByteTimeseriesPropertyObject> getSByteTimeseriesPropertyCollectionByElement( Guid element ) throws Exception;
    SByteTimeseriesPropertyObject getSByteTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<SByteTimeseriesPropertyObject> getSByteTimeseriesPropertyCollectionByDefinition( Guid definition ) throws Exception;
    List<SByteTimeseriesPropertyObject> getSByteTimeseriesPropertyCollectionByTimeseries( Guid timeseries ) throws Exception;
    List<SByteTimeseriesPropertyObject> qetSByteTimeseriesPropertyCollectionByTimeseriesIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // SingleTimeseriesProperty queries
    // ---------------------------------------------------------------------
    SingleTimeseriesPropertyObject getSingleTimeseriesPropertyById( Guid id ) throws Exception;
    List<SingleTimeseriesPropertyObject> getSingleTimeseriesPropertyCollection( ) throws Exception;
    List<SingleTimeseriesPropertyObject> getSingleTimeseriesPropertyCollectionByElement( Guid element ) throws Exception;
    SingleTimeseriesPropertyObject getSingleTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<SingleTimeseriesPropertyObject> getSingleTimeseriesPropertyCollectionByDefinition( Guid definition ) throws Exception;
    List<SingleTimeseriesPropertyObject> getSingleTimeseriesPropertyCollectionByTimeseries( Guid timeseries ) throws Exception;
    List<SingleTimeseriesPropertyObject> qetSingleTimeseriesPropertyCollectionByTimeseriesIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // StringTimeseriesProperty queries
    // ---------------------------------------------------------------------
    StringTimeseriesPropertyObject getStringTimeseriesPropertyById( Guid id ) throws Exception;
    List<StringTimeseriesPropertyObject> getStringTimeseriesPropertyCollection( ) throws Exception;
    List<StringTimeseriesPropertyObject> getStringTimeseriesPropertyCollectionByElement( Guid element ) throws Exception;
    StringTimeseriesPropertyObject getStringTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<StringTimeseriesPropertyObject> getStringTimeseriesPropertyCollectionByDefinition( Guid definition ) throws Exception;
    List<StringTimeseriesPropertyObject> getStringTimeseriesPropertyCollectionByTimeseries( Guid timeseries ) throws Exception;
    List<StringTimeseriesPropertyObject> qetStringTimeseriesPropertyCollectionByTimeseriesIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // TimeSpanTimeseriesProperty queries
    // ---------------------------------------------------------------------
    TimeSpanTimeseriesPropertyObject getTimeSpanTimeseriesPropertyById( Guid id ) throws Exception;
    List<TimeSpanTimeseriesPropertyObject> getTimeSpanTimeseriesPropertyCollection( ) throws Exception;
    List<TimeSpanTimeseriesPropertyObject> getTimeSpanTimeseriesPropertyCollectionByElement( Guid element ) throws Exception;
    TimeSpanTimeseriesPropertyObject getTimeSpanTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<TimeSpanTimeseriesPropertyObject> getTimeSpanTimeseriesPropertyCollectionByDefinition( Guid definition ) throws Exception;
    List<TimeSpanTimeseriesPropertyObject> getTimeSpanTimeseriesPropertyCollectionByTimeseries( Guid timeseries ) throws Exception;
    List<TimeSpanTimeseriesPropertyObject> qetTimeSpanTimeseriesPropertyCollectionByTimeseriesIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // UInt16TimeseriesProperty queries
    // ---------------------------------------------------------------------
    UInt16TimeseriesPropertyObject getUInt16TimeseriesPropertyById( Guid id ) throws Exception;
    List<UInt16TimeseriesPropertyObject> getUInt16TimeseriesPropertyCollection( ) throws Exception;
    List<UInt16TimeseriesPropertyObject> getUInt16TimeseriesPropertyCollectionByElement( Guid element ) throws Exception;
    UInt16TimeseriesPropertyObject getUInt16TimeseriesPropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<UInt16TimeseriesPropertyObject> getUInt16TimeseriesPropertyCollectionByDefinition( Guid definition ) throws Exception;
    List<UInt16TimeseriesPropertyObject> getUInt16TimeseriesPropertyCollectionByTimeseries( Guid timeseries ) throws Exception;
    List<UInt16TimeseriesPropertyObject> qetUInt16TimeseriesPropertyCollectionByTimeseriesIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // UInt32TimeseriesProperty queries
    // ---------------------------------------------------------------------
    UInt32TimeseriesPropertyObject getUInt32TimeseriesPropertyById( Guid id ) throws Exception;
    List<UInt32TimeseriesPropertyObject> getUInt32TimeseriesPropertyCollection( ) throws Exception;
    List<UInt32TimeseriesPropertyObject> getUInt32TimeseriesPropertyCollectionByElement( Guid element ) throws Exception;
    UInt32TimeseriesPropertyObject getUInt32TimeseriesPropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<UInt32TimeseriesPropertyObject> getUInt32TimeseriesPropertyCollectionByDefinition( Guid definition ) throws Exception;
    List<UInt32TimeseriesPropertyObject> getUInt32TimeseriesPropertyCollectionByTimeseries( Guid timeseries ) throws Exception;
    List<UInt32TimeseriesPropertyObject> qetUInt32TimeseriesPropertyCollectionByTimeseriesIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // UInt64TimeseriesProperty queries
    // ---------------------------------------------------------------------
    UInt64TimeseriesPropertyObject getUInt64TimeseriesPropertyById( Guid id ) throws Exception;
    List<UInt64TimeseriesPropertyObject> getUInt64TimeseriesPropertyCollection( ) throws Exception;
    List<UInt64TimeseriesPropertyObject> getUInt64TimeseriesPropertyCollectionByElement( Guid element ) throws Exception;
    UInt64TimeseriesPropertyObject getUInt64TimeseriesPropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<UInt64TimeseriesPropertyObject> getUInt64TimeseriesPropertyCollectionByDefinition( Guid definition ) throws Exception;
    List<UInt64TimeseriesPropertyObject> getUInt64TimeseriesPropertyCollectionByTimeseries( Guid timeseries ) throws Exception;
    List<UInt64TimeseriesPropertyObject> qetUInt64TimeseriesPropertyCollectionByTimeseriesIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // TimeSpanProperty queries
    // ---------------------------------------------------------------------
    TimeSpanPropertyObject getTimeSpanPropertyById( Guid id ) throws Exception;
    List<TimeSpanPropertyObject> getTimeSpanPropertyCollection( ) throws Exception;
    List<TimeSpanPropertyObject> getTimeSpanPropertyCollectionByElement( Guid element ) throws Exception;
    TimeSpanPropertyObject getTimeSpanPropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<TimeSpanPropertyObject> getTimeSpanPropertyCollectionByDefinition( Guid definition ) throws Exception;
    // ---------------------------------------------------------------------
    // UInt16Property queries
    // ---------------------------------------------------------------------
    UInt16PropertyObject getUInt16PropertyById( Guid id ) throws Exception;
    List<UInt16PropertyObject> getUInt16PropertyCollection( ) throws Exception;
    List<UInt16PropertyObject> getUInt16PropertyCollectionByElement( Guid element ) throws Exception;
    UInt16PropertyObject getUInt16PropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<UInt16PropertyObject> getUInt16PropertyCollectionByDefinition( Guid definition ) throws Exception;
    // ---------------------------------------------------------------------
    // UInt32Property queries
    // ---------------------------------------------------------------------
    UInt32PropertyObject getUInt32PropertyById( Guid id ) throws Exception;
    List<UInt32PropertyObject> getUInt32PropertyCollection( ) throws Exception;
    List<UInt32PropertyObject> getUInt32PropertyCollectionByElement( Guid element ) throws Exception;
    UInt32PropertyObject getUInt32PropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<UInt32PropertyObject> getUInt32PropertyCollectionByDefinition( Guid definition ) throws Exception;
    // ---------------------------------------------------------------------
    // UInt64Property queries
    // ---------------------------------------------------------------------
    UInt64PropertyObject getUInt64PropertyById( Guid id ) throws Exception;
    List<UInt64PropertyObject> getUInt64PropertyCollection( ) throws Exception;
    List<UInt64PropertyObject> getUInt64PropertyCollectionByElement( Guid element ) throws Exception;
    UInt64PropertyObject getUInt64PropertyByElementAndDefinition( Guid element, Guid definition ) throws Exception;
    List<UInt64PropertyObject> getUInt64PropertyCollectionByDefinition( Guid definition ) throws Exception;
    // ---------------------------------------------------------------------
    // PropertyDefinition queries
    // ---------------------------------------------------------------------
    PropertyDefinitionObject getPropertyDefinitionById( Guid id ) throws Exception;
    List<PropertyDefinitionObject> getPropertyDefinitionCollection( ) throws Exception;
    List<PropertyDefinitionObject> getPropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    PropertyDefinitionObject getPropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // BinaryPropertyDefinition queries
    // ---------------------------------------------------------------------
    BinaryPropertyDefinitionObject getBinaryPropertyDefinitionById( Guid id ) throws Exception;
    List<BinaryPropertyDefinitionObject> getBinaryPropertyDefinitionCollection( ) throws Exception;
    List<BinaryPropertyDefinitionObject> getBinaryPropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    BinaryPropertyDefinitionObject getBinaryPropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // BooleanPropertyDefinition queries
    // ---------------------------------------------------------------------
    BooleanPropertyDefinitionObject getBooleanPropertyDefinitionById( Guid id ) throws Exception;
    List<BooleanPropertyDefinitionObject> getBooleanPropertyDefinitionCollection( ) throws Exception;
    List<BooleanPropertyDefinitionObject> getBooleanPropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    BooleanPropertyDefinitionObject getBooleanPropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // BytePropertyDefinition queries
    // ---------------------------------------------------------------------
    BytePropertyDefinitionObject getBytePropertyDefinitionById( Guid id ) throws Exception;
    List<BytePropertyDefinitionObject> getBytePropertyDefinitionCollection( ) throws Exception;
    List<BytePropertyDefinitionObject> getBytePropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    BytePropertyDefinitionObject getBytePropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // DateTimePropertyDefinition queries
    // ---------------------------------------------------------------------
    DateTimePropertyDefinitionObject getDateTimePropertyDefinitionById( Guid id ) throws Exception;
    List<DateTimePropertyDefinitionObject> getDateTimePropertyDefinitionCollection( ) throws Exception;
    List<DateTimePropertyDefinitionObject> getDateTimePropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    DateTimePropertyDefinitionObject getDateTimePropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // DoublePropertyDefinition queries
    // ---------------------------------------------------------------------
    DoublePropertyDefinitionObject getDoublePropertyDefinitionById( Guid id ) throws Exception;
    List<DoublePropertyDefinitionObject> getDoublePropertyDefinitionCollection( ) throws Exception;
    List<DoublePropertyDefinitionObject> getDoublePropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    DoublePropertyDefinitionObject getDoublePropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // GuidPropertyDefinition queries
    // ---------------------------------------------------------------------
    GuidPropertyDefinitionObject getGuidPropertyDefinitionById( Guid id ) throws Exception;
    List<GuidPropertyDefinitionObject> getGuidPropertyDefinitionCollection( ) throws Exception;
    List<GuidPropertyDefinitionObject> getGuidPropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    GuidPropertyDefinitionObject getGuidPropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // Int16PropertyDefinition queries
    // ---------------------------------------------------------------------
    Int16PropertyDefinitionObject getInt16PropertyDefinitionById( Guid id ) throws Exception;
    List<Int16PropertyDefinitionObject> getInt16PropertyDefinitionCollection( ) throws Exception;
    List<Int16PropertyDefinitionObject> getInt16PropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    Int16PropertyDefinitionObject getInt16PropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // Int32PropertyDefinition queries
    // ---------------------------------------------------------------------
    Int32PropertyDefinitionObject getInt32PropertyDefinitionById( Guid id ) throws Exception;
    List<Int32PropertyDefinitionObject> getInt32PropertyDefinitionCollection( ) throws Exception;
    List<Int32PropertyDefinitionObject> getInt32PropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    Int32PropertyDefinitionObject getInt32PropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // Int64PropertyDefinition queries
    // ---------------------------------------------------------------------
    Int64PropertyDefinitionObject getInt64PropertyDefinitionById( Guid id ) throws Exception;
    List<Int64PropertyDefinitionObject> getInt64PropertyDefinitionCollection( ) throws Exception;
    List<Int64PropertyDefinitionObject> getInt64PropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    Int64PropertyDefinitionObject getInt64PropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // ReferencePropertyDefinition queries
    // ---------------------------------------------------------------------
    ReferencePropertyDefinitionObject getReferencePropertyDefinitionById( Guid id ) throws Exception;
    List<ReferencePropertyDefinitionObject> getReferencePropertyDefinitionCollection( ) throws Exception;
    List<ReferencePropertyDefinitionObject> getReferencePropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    ReferencePropertyDefinitionObject getReferencePropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    List<ReferencePropertyDefinitionObject> getReferencePropertyDefinitionCollectionByDefaultValue( Guid defaultValue ) throws Exception;
    List<ReferencePropertyDefinitionObject> qetReferencePropertyDefinitionCollectionByDefaultValueIsNull(  ) throws Exception;
    List<ReferencePropertyDefinitionObject> getReferencePropertyDefinitionCollectionByReferencedElementType( Guid referencedElementType ) throws Exception;
    List<ReferencePropertyDefinitionObject> qetReferencePropertyDefinitionCollectionByReferencedElementTypeIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // SBytePropertyDefinition queries
    // ---------------------------------------------------------------------
    SBytePropertyDefinitionObject getSBytePropertyDefinitionById( Guid id ) throws Exception;
    List<SBytePropertyDefinitionObject> getSBytePropertyDefinitionCollection( ) throws Exception;
    List<SBytePropertyDefinitionObject> getSBytePropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    SBytePropertyDefinitionObject getSBytePropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // SinglePropertyDefinition queries
    // ---------------------------------------------------------------------
    SinglePropertyDefinitionObject getSinglePropertyDefinitionById( Guid id ) throws Exception;
    List<SinglePropertyDefinitionObject> getSinglePropertyDefinitionCollection( ) throws Exception;
    List<SinglePropertyDefinitionObject> getSinglePropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    SinglePropertyDefinitionObject getSinglePropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // StringPropertyDefinition queries
    // ---------------------------------------------------------------------
    StringPropertyDefinitionObject getStringPropertyDefinitionById( Guid id ) throws Exception;
    List<StringPropertyDefinitionObject> getStringPropertyDefinitionCollection( ) throws Exception;
    List<StringPropertyDefinitionObject> getStringPropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    StringPropertyDefinitionObject getStringPropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // TimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    TimeseriesPropertyDefinitionObject getTimeseriesPropertyDefinitionById( Guid id ) throws Exception;
    List<TimeseriesPropertyDefinitionObject> getTimeseriesPropertyDefinitionCollection( ) throws Exception;
    List<TimeseriesPropertyDefinitionObject> getTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    TimeseriesPropertyDefinitionObject getTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // BinaryTimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    BinaryTimeseriesPropertyDefinitionObject getBinaryTimeseriesPropertyDefinitionById( Guid id ) throws Exception;
    List<BinaryTimeseriesPropertyDefinitionObject> getBinaryTimeseriesPropertyDefinitionCollection( ) throws Exception;
    List<BinaryTimeseriesPropertyDefinitionObject> getBinaryTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    BinaryTimeseriesPropertyDefinitionObject getBinaryTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // BooleanTimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    BooleanTimeseriesPropertyDefinitionObject getBooleanTimeseriesPropertyDefinitionById( Guid id ) throws Exception;
    List<BooleanTimeseriesPropertyDefinitionObject> getBooleanTimeseriesPropertyDefinitionCollection( ) throws Exception;
    List<BooleanTimeseriesPropertyDefinitionObject> getBooleanTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    BooleanTimeseriesPropertyDefinitionObject getBooleanTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // ByteTimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    ByteTimeseriesPropertyDefinitionObject getByteTimeseriesPropertyDefinitionById( Guid id ) throws Exception;
    List<ByteTimeseriesPropertyDefinitionObject> getByteTimeseriesPropertyDefinitionCollection( ) throws Exception;
    List<ByteTimeseriesPropertyDefinitionObject> getByteTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    ByteTimeseriesPropertyDefinitionObject getByteTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // DateTimeTimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    DateTimeTimeseriesPropertyDefinitionObject getDateTimeTimeseriesPropertyDefinitionById( Guid id ) throws Exception;
    List<DateTimeTimeseriesPropertyDefinitionObject> getDateTimeTimeseriesPropertyDefinitionCollection( ) throws Exception;
    List<DateTimeTimeseriesPropertyDefinitionObject> getDateTimeTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    DateTimeTimeseriesPropertyDefinitionObject getDateTimeTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // DoubleTimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    DoubleTimeseriesPropertyDefinitionObject getDoubleTimeseriesPropertyDefinitionById( Guid id ) throws Exception;
    List<DoubleTimeseriesPropertyDefinitionObject> getDoubleTimeseriesPropertyDefinitionCollection( ) throws Exception;
    List<DoubleTimeseriesPropertyDefinitionObject> getDoubleTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    DoubleTimeseriesPropertyDefinitionObject getDoubleTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // GuidTimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    GuidTimeseriesPropertyDefinitionObject getGuidTimeseriesPropertyDefinitionById( Guid id ) throws Exception;
    List<GuidTimeseriesPropertyDefinitionObject> getGuidTimeseriesPropertyDefinitionCollection( ) throws Exception;
    List<GuidTimeseriesPropertyDefinitionObject> getGuidTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    GuidTimeseriesPropertyDefinitionObject getGuidTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // Int16TimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    Int16TimeseriesPropertyDefinitionObject getInt16TimeseriesPropertyDefinitionById( Guid id ) throws Exception;
    List<Int16TimeseriesPropertyDefinitionObject> getInt16TimeseriesPropertyDefinitionCollection( ) throws Exception;
    List<Int16TimeseriesPropertyDefinitionObject> getInt16TimeseriesPropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    Int16TimeseriesPropertyDefinitionObject getInt16TimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // Int32TimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    Int32TimeseriesPropertyDefinitionObject getInt32TimeseriesPropertyDefinitionById( Guid id ) throws Exception;
    List<Int32TimeseriesPropertyDefinitionObject> getInt32TimeseriesPropertyDefinitionCollection( ) throws Exception;
    List<Int32TimeseriesPropertyDefinitionObject> getInt32TimeseriesPropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    Int32TimeseriesPropertyDefinitionObject getInt32TimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // Int64TimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    Int64TimeseriesPropertyDefinitionObject getInt64TimeseriesPropertyDefinitionById( Guid id ) throws Exception;
    List<Int64TimeseriesPropertyDefinitionObject> getInt64TimeseriesPropertyDefinitionCollection( ) throws Exception;
    List<Int64TimeseriesPropertyDefinitionObject> getInt64TimeseriesPropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    Int64TimeseriesPropertyDefinitionObject getInt64TimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // ReferenceTimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    ReferenceTimeseriesPropertyDefinitionObject getReferenceTimeseriesPropertyDefinitionById( Guid id ) throws Exception;
    List<ReferenceTimeseriesPropertyDefinitionObject> getReferenceTimeseriesPropertyDefinitionCollection( ) throws Exception;
    List<ReferenceTimeseriesPropertyDefinitionObject> getReferenceTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    ReferenceTimeseriesPropertyDefinitionObject getReferenceTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    List<ReferenceTimeseriesPropertyDefinitionObject> getReferenceTimeseriesPropertyDefinitionCollectionByReferencedElementType( Guid referencedElementType ) throws Exception;
    List<ReferenceTimeseriesPropertyDefinitionObject> qetReferenceTimeseriesPropertyDefinitionCollectionByReferencedElementTypeIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // SByteTimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    SByteTimeseriesPropertyDefinitionObject getSByteTimeseriesPropertyDefinitionById( Guid id ) throws Exception;
    List<SByteTimeseriesPropertyDefinitionObject> getSByteTimeseriesPropertyDefinitionCollection( ) throws Exception;
    List<SByteTimeseriesPropertyDefinitionObject> getSByteTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    SByteTimeseriesPropertyDefinitionObject getSByteTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // SingleTimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    SingleTimeseriesPropertyDefinitionObject getSingleTimeseriesPropertyDefinitionById( Guid id ) throws Exception;
    List<SingleTimeseriesPropertyDefinitionObject> getSingleTimeseriesPropertyDefinitionCollection( ) throws Exception;
    List<SingleTimeseriesPropertyDefinitionObject> getSingleTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    SingleTimeseriesPropertyDefinitionObject getSingleTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // StringTimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    StringTimeseriesPropertyDefinitionObject getStringTimeseriesPropertyDefinitionById( Guid id ) throws Exception;
    List<StringTimeseriesPropertyDefinitionObject> getStringTimeseriesPropertyDefinitionCollection( ) throws Exception;
    List<StringTimeseriesPropertyDefinitionObject> getStringTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    StringTimeseriesPropertyDefinitionObject getStringTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // TimeSpanTimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    TimeSpanTimeseriesPropertyDefinitionObject getTimeSpanTimeseriesPropertyDefinitionById( Guid id ) throws Exception;
    List<TimeSpanTimeseriesPropertyDefinitionObject> getTimeSpanTimeseriesPropertyDefinitionCollection( ) throws Exception;
    List<TimeSpanTimeseriesPropertyDefinitionObject> getTimeSpanTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    TimeSpanTimeseriesPropertyDefinitionObject getTimeSpanTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // UInt16TimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    UInt16TimeseriesPropertyDefinitionObject getUInt16TimeseriesPropertyDefinitionById( Guid id ) throws Exception;
    List<UInt16TimeseriesPropertyDefinitionObject> getUInt16TimeseriesPropertyDefinitionCollection( ) throws Exception;
    List<UInt16TimeseriesPropertyDefinitionObject> getUInt16TimeseriesPropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    UInt16TimeseriesPropertyDefinitionObject getUInt16TimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // UInt32TimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    UInt32TimeseriesPropertyDefinitionObject getUInt32TimeseriesPropertyDefinitionById( Guid id ) throws Exception;
    List<UInt32TimeseriesPropertyDefinitionObject> getUInt32TimeseriesPropertyDefinitionCollection( ) throws Exception;
    List<UInt32TimeseriesPropertyDefinitionObject> getUInt32TimeseriesPropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    UInt32TimeseriesPropertyDefinitionObject getUInt32TimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // UInt64TimeseriesPropertyDefinition queries
    // ---------------------------------------------------------------------
    UInt64TimeseriesPropertyDefinitionObject getUInt64TimeseriesPropertyDefinitionById( Guid id ) throws Exception;
    List<UInt64TimeseriesPropertyDefinitionObject> getUInt64TimeseriesPropertyDefinitionCollection( ) throws Exception;
    List<UInt64TimeseriesPropertyDefinitionObject> getUInt64TimeseriesPropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    UInt64TimeseriesPropertyDefinitionObject getUInt64TimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // TimeSpanPropertyDefinition queries
    // ---------------------------------------------------------------------
    TimeSpanPropertyDefinitionObject getTimeSpanPropertyDefinitionById( Guid id ) throws Exception;
    List<TimeSpanPropertyDefinitionObject> getTimeSpanPropertyDefinitionCollection( ) throws Exception;
    List<TimeSpanPropertyDefinitionObject> getTimeSpanPropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    TimeSpanPropertyDefinitionObject getTimeSpanPropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // UInt16PropertyDefinition queries
    // ---------------------------------------------------------------------
    UInt16PropertyDefinitionObject getUInt16PropertyDefinitionById( Guid id ) throws Exception;
    List<UInt16PropertyDefinitionObject> getUInt16PropertyDefinitionCollection( ) throws Exception;
    List<UInt16PropertyDefinitionObject> getUInt16PropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    UInt16PropertyDefinitionObject getUInt16PropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // UInt32PropertyDefinition queries
    // ---------------------------------------------------------------------
    UInt32PropertyDefinitionObject getUInt32PropertyDefinitionById( Guid id ) throws Exception;
    List<UInt32PropertyDefinitionObject> getUInt32PropertyDefinitionCollection( ) throws Exception;
    List<UInt32PropertyDefinitionObject> getUInt32PropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    UInt32PropertyDefinitionObject getUInt32PropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // UInt64PropertyDefinition queries
    // ---------------------------------------------------------------------
    UInt64PropertyDefinitionObject getUInt64PropertyDefinitionById( Guid id ) throws Exception;
    List<UInt64PropertyDefinitionObject> getUInt64PropertyDefinitionCollection( ) throws Exception;
    List<UInt64PropertyDefinitionObject> getUInt64PropertyDefinitionCollectionByElementType( Guid elementType ) throws Exception;
    UInt64PropertyDefinitionObject getUInt64PropertyDefinitionByElementTypeAndName( Guid elementType, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarAlarmStatus queries
    // ---------------------------------------------------------------------
    RadarAlarmStatusObject getRadarAlarmStatusById( Guid id ) throws Exception;
    List<RadarAlarmStatusObject> getRadarAlarmStatusCollection( ) throws Exception;
    List<RadarAlarmStatusObject> getRadarAlarmStatusCollectionByRadar( Guid radar ) throws Exception;
    RadarAlarmStatusObject getRadarAlarmStatusByRadarAndTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    RadarAlarmStatusObject getRadarAlarmStatusByRadarAtTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarAlarmStatusObject> getRadarAlarmStatusByRadarFromTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarAlarmStatusObject> getRadarAlarmStatusByRadarUntilTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarAlarmStatusObject> getRadarAlarmStatusByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<RadarAlarmStatusObject> getRadarAlarmStatusCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<RadarAlarmStatusObject> getRadarAlarmStatusCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<RadarAlarmStatusObject> getRadarAlarmStatusCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<RadarAlarmStatusObject> getRadarAlarmStatusCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<RadarAlarmStatusObject> getRadarAlarmStatusCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarCommand queries
    // ---------------------------------------------------------------------
    RadarCommandObject getRadarCommandById( Guid id ) throws Exception;
    List<RadarCommandObject> getRadarCommandCollection( ) throws Exception;
    List<RadarCommandObject> getRadarCommandCollectionByRadar( Guid radar ) throws Exception;
    List<RadarCommandObject> getRadarCommandCollectionByRadarAndTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarCommandObject> getRadarCommandCollectionByRadarAtTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarCommandObject> getRadarCommandCollectionByRadarFromTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarCommandObject> getRadarCommandCollectionByRadarUntilTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarCommandObject> getRadarCommandCollectionByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<RadarCommandObject> getRadarCommandCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<RadarCommandObject> getRadarCommandCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<RadarCommandObject> getRadarCommandCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<RadarCommandObject> getRadarCommandCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<RadarCommandObject> getRadarCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<RadarCommandObject> getRadarCommandCollectionByReply( Guid reply ) throws Exception;
    List<RadarCommandObject> qetRadarCommandCollectionByReplyIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarCommandGetStatus queries
    // ---------------------------------------------------------------------
    RadarCommandGetStatusObject getRadarCommandGetStatusById( Guid id ) throws Exception;
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollection( ) throws Exception;
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollectionByRadar( Guid radar ) throws Exception;
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollectionByRadarAndTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollectionByRadarAtTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollectionByRadarFromTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollectionByRadarUntilTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollectionByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<RadarCommandGetStatusObject> getRadarCommandGetStatusCollectionByReply( Guid reply ) throws Exception;
    List<RadarCommandGetStatusObject> qetRadarCommandGetStatusCollectionByReplyIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarCommandReply queries
    // ---------------------------------------------------------------------
    RadarCommandReplyObject getRadarCommandReplyById( Guid id ) throws Exception;
    List<RadarCommandReplyObject> getRadarCommandReplyCollection( ) throws Exception;
    List<RadarCommandReplyObject> getRadarCommandReplyCollectionByRadar( Guid radar ) throws Exception;
    List<RadarCommandReplyObject> getRadarCommandReplyCollectionByRadarAndTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarCommandReplyObject> getRadarCommandReplyCollectionByRadarAtTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarCommandReplyObject> getRadarCommandReplyCollectionByRadarFromTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarCommandReplyObject> getRadarCommandReplyCollectionByRadarUntilTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarCommandReplyObject> getRadarCommandReplyCollectionByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<RadarCommandReplyObject> getRadarCommandReplyCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<RadarCommandReplyObject> getRadarCommandReplyCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<RadarCommandReplyObject> getRadarCommandReplyCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<RadarCommandReplyObject> getRadarCommandReplyCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<RadarCommandReplyObject> getRadarCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    RadarCommandReplyObject getRadarCommandReplyByCommand( Guid command ) throws Exception;
    List<RadarCommandReplyObject> qetRadarCommandReplyCollectionByCommandIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarCommandReplyGetStatus queries
    // ---------------------------------------------------------------------
    RadarCommandReplyGetStatusObject getRadarCommandReplyGetStatusById( Guid id ) throws Exception;
    List<RadarCommandReplyGetStatusObject> getRadarCommandReplyGetStatusCollection( ) throws Exception;
    List<RadarCommandReplyGetStatusObject> getRadarCommandReplyGetStatusCollectionByRadar( Guid radar ) throws Exception;
    List<RadarCommandReplyGetStatusObject> getRadarCommandReplyGetStatusCollectionByRadarAndTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarCommandReplyGetStatusObject> getRadarCommandReplyGetStatusCollectionByRadarAtTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarCommandReplyGetStatusObject> getRadarCommandReplyGetStatusCollectionByRadarFromTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarCommandReplyGetStatusObject> getRadarCommandReplyGetStatusCollectionByRadarUntilTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarCommandReplyGetStatusObject> getRadarCommandReplyGetStatusCollectionByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<RadarCommandReplyGetStatusObject> getRadarCommandReplyGetStatusCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<RadarCommandReplyGetStatusObject> getRadarCommandReplyGetStatusCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<RadarCommandReplyGetStatusObject> getRadarCommandReplyGetStatusCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<RadarCommandReplyGetStatusObject> getRadarCommandReplyGetStatusCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<RadarCommandReplyGetStatusObject> getRadarCommandReplyGetStatusCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    RadarCommandReplyGetStatusObject getRadarCommandReplyGetStatusByCommand( Guid command ) throws Exception;
    List<RadarCommandReplyGetStatusObject> qetRadarCommandReplyGetStatusCollectionByCommandIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarConfiguration queries
    // ---------------------------------------------------------------------
    RadarConfigurationObject getRadarConfigurationById( Guid id ) throws Exception;
    List<RadarConfigurationObject> getRadarConfigurationCollection( ) throws Exception;
    List<RadarConfigurationObject> getRadarConfigurationCollectionByRadar( Guid radar ) throws Exception;
    RadarConfigurationObject getRadarConfigurationByRadarAndTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    RadarConfigurationObject getRadarConfigurationByRadarAtTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarConfigurationObject> getRadarConfigurationByRadarFromTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarConfigurationObject> getRadarConfigurationByRadarUntilTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarConfigurationObject> getRadarConfigurationByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<RadarConfigurationObject> getRadarConfigurationCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<RadarConfigurationObject> getRadarConfigurationCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<RadarConfigurationObject> getRadarConfigurationCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<RadarConfigurationObject> getRadarConfigurationCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<RadarConfigurationObject> getRadarConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarImage queries
    // ---------------------------------------------------------------------
    RadarImageObject getRadarImageById( Guid id ) throws Exception;
    List<RadarImageObject> getRadarImageCollection( ) throws Exception;
    List<RadarImageObject> getRadarImageCollectionByRadar( Guid radar ) throws Exception;
    RadarImageObject getRadarImageByRadarAndTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    RadarImageObject getRadarImageByRadarAtTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarImageObject> getRadarImageByRadarFromTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarImageObject> getRadarImageByRadarUntilTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarImageObject> getRadarImageByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<RadarImageObject> getRadarImageCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<RadarImageObject> getRadarImageCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<RadarImageObject> getRadarImageCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<RadarImageObject> getRadarImageCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<RadarImageObject> getRadarImageCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarRawTrackTable queries
    // ---------------------------------------------------------------------
    RadarRawTrackTableObject getRadarRawTrackTableById( Guid id ) throws Exception;
    List<RadarRawTrackTableObject> getRadarRawTrackTableCollection( ) throws Exception;
    List<RadarRawTrackTableObject> getRadarRawTrackTableCollectionByRadar( Guid radar ) throws Exception;
    RadarRawTrackTableObject getRadarRawTrackTableByRadarAndTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    RadarRawTrackTableObject getRadarRawTrackTableByRadarAtTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarRawTrackTableObject> getRadarRawTrackTableByRadarFromTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarRawTrackTableObject> getRadarRawTrackTableByRadarUntilTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarRawTrackTableObject> getRadarRawTrackTableByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<RadarRawTrackTableObject> getRadarRawTrackTableCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<RadarRawTrackTableObject> getRadarRawTrackTableCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<RadarRawTrackTableObject> getRadarRawTrackTableCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<RadarRawTrackTableObject> getRadarRawTrackTableCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<RadarRawTrackTableObject> getRadarRawTrackTableCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarStatus queries
    // ---------------------------------------------------------------------
    RadarStatusObject getRadarStatusById( Guid id ) throws Exception;
    List<RadarStatusObject> getRadarStatusCollection( ) throws Exception;
    List<RadarStatusObject> getRadarStatusCollectionByRadar( Guid radar ) throws Exception;
    RadarStatusObject getRadarStatusByRadarAndTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    RadarStatusObject getRadarStatusByRadarAtTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarStatusObject> getRadarStatusByRadarFromTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarStatusObject> getRadarStatusByRadarUntilTimestamp( Guid radar, DateTime timestamp ) throws Exception;
    List<RadarStatusObject> getRadarStatusByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<RadarStatusObject> getRadarStatusCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<RadarStatusObject> getRadarStatusCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<RadarStatusObject> getRadarStatusCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<RadarStatusObject> getRadarStatusCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<RadarStatusObject> getRadarStatusCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // RadioCommand queries
    // ---------------------------------------------------------------------
    RadioCommandObject getRadioCommandById( Guid id ) throws Exception;
    List<RadioCommandObject> getRadioCommandCollection( ) throws Exception;
    List<RadioCommandObject> getRadioCommandCollectionByRadio( Guid radio ) throws Exception;
    List<RadioCommandObject> getRadioCommandCollectionByRadioAndTimestamp( Guid radio, DateTime timestamp ) throws Exception;
    List<RadioCommandObject> getRadioCommandCollectionByRadioAtTimestamp( Guid radio, DateTime timestamp ) throws Exception;
    List<RadioCommandObject> getRadioCommandCollectionByRadioFromTimestamp( Guid radio, DateTime timestamp ) throws Exception;
    List<RadioCommandObject> getRadioCommandCollectionByRadioUntilTimestamp( Guid radio, DateTime timestamp ) throws Exception;
    List<RadioCommandObject> getRadioCommandCollectionByRadioOverTimestamp( Guid radio, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<RadioCommandObject> getRadioCommandCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<RadioCommandObject> getRadioCommandCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<RadioCommandObject> getRadioCommandCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<RadioCommandObject> getRadioCommandCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<RadioCommandObject> getRadioCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<RadioCommandObject> getRadioCommandCollectionByReply( Guid reply ) throws Exception;
    List<RadioCommandObject> qetRadioCommandCollectionByReplyIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // RadioCommandReply queries
    // ---------------------------------------------------------------------
    RadioCommandReplyObject getRadioCommandReplyById( Guid id ) throws Exception;
    List<RadioCommandReplyObject> getRadioCommandReplyCollection( ) throws Exception;
    List<RadioCommandReplyObject> getRadioCommandReplyCollectionByRadio( Guid radio ) throws Exception;
    List<RadioCommandReplyObject> getRadioCommandReplyCollectionByRadioAndTimestamp( Guid radio, DateTime timestamp ) throws Exception;
    List<RadioCommandReplyObject> getRadioCommandReplyCollectionByRadioAtTimestamp( Guid radio, DateTime timestamp ) throws Exception;
    List<RadioCommandReplyObject> getRadioCommandReplyCollectionByRadioFromTimestamp( Guid radio, DateTime timestamp ) throws Exception;
    List<RadioCommandReplyObject> getRadioCommandReplyCollectionByRadioUntilTimestamp( Guid radio, DateTime timestamp ) throws Exception;
    List<RadioCommandReplyObject> getRadioCommandReplyCollectionByRadioOverTimestamp( Guid radio, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<RadioCommandReplyObject> getRadioCommandReplyCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<RadioCommandReplyObject> getRadioCommandReplyCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<RadioCommandReplyObject> getRadioCommandReplyCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<RadioCommandReplyObject> getRadioCommandReplyCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<RadioCommandReplyObject> getRadioCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    RadioCommandReplyObject getRadioCommandReplyByCommand( Guid command ) throws Exception;
    List<RadioCommandReplyObject> qetRadioCommandReplyCollectionByCommandIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // RadioConfiguration queries
    // ---------------------------------------------------------------------
    RadioConfigurationObject getRadioConfigurationById( Guid id ) throws Exception;
    List<RadioConfigurationObject> getRadioConfigurationCollection( ) throws Exception;
    List<RadioConfigurationObject> getRadioConfigurationCollectionByRadio( Guid radio ) throws Exception;
    RadioConfigurationObject getRadioConfigurationByRadioAndTimestamp( Guid radio, DateTime timestamp ) throws Exception;
    RadioConfigurationObject getRadioConfigurationByRadioAtTimestamp( Guid radio, DateTime timestamp ) throws Exception;
    List<RadioConfigurationObject> getRadioConfigurationByRadioFromTimestamp( Guid radio, DateTime timestamp ) throws Exception;
    List<RadioConfigurationObject> getRadioConfigurationByRadioUntilTimestamp( Guid radio, DateTime timestamp ) throws Exception;
    List<RadioConfigurationObject> getRadioConfigurationByRadioOverTimestamp( Guid radio, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<RadioConfigurationObject> getRadioConfigurationCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<RadioConfigurationObject> getRadioConfigurationCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<RadioConfigurationObject> getRadioConfigurationCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<RadioConfigurationObject> getRadioConfigurationCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<RadioConfigurationObject> getRadioConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // RadomeCommand queries
    // ---------------------------------------------------------------------
    RadomeCommandObject getRadomeCommandById( Guid id ) throws Exception;
    List<RadomeCommandObject> getRadomeCommandCollection( ) throws Exception;
    List<RadomeCommandObject> getRadomeCommandCollectionByRadome( Guid radome ) throws Exception;
    List<RadomeCommandObject> getRadomeCommandCollectionByRadomeAndTimestamp( Guid radome, DateTime timestamp ) throws Exception;
    List<RadomeCommandObject> getRadomeCommandCollectionByRadomeAtTimestamp( Guid radome, DateTime timestamp ) throws Exception;
    List<RadomeCommandObject> getRadomeCommandCollectionByRadomeFromTimestamp( Guid radome, DateTime timestamp ) throws Exception;
    List<RadomeCommandObject> getRadomeCommandCollectionByRadomeUntilTimestamp( Guid radome, DateTime timestamp ) throws Exception;
    List<RadomeCommandObject> getRadomeCommandCollectionByRadomeOverTimestamp( Guid radome, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<RadomeCommandObject> getRadomeCommandCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<RadomeCommandObject> getRadomeCommandCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<RadomeCommandObject> getRadomeCommandCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<RadomeCommandObject> getRadomeCommandCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<RadomeCommandObject> getRadomeCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<RadomeCommandObject> getRadomeCommandCollectionByReply( Guid reply ) throws Exception;
    List<RadomeCommandObject> qetRadomeCommandCollectionByReplyIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // RadomeCommandReply queries
    // ---------------------------------------------------------------------
    RadomeCommandReplyObject getRadomeCommandReplyById( Guid id ) throws Exception;
    List<RadomeCommandReplyObject> getRadomeCommandReplyCollection( ) throws Exception;
    List<RadomeCommandReplyObject> getRadomeCommandReplyCollectionByRadome( Guid radome ) throws Exception;
    List<RadomeCommandReplyObject> getRadomeCommandReplyCollectionByRadomeAndTimestamp( Guid radome, DateTime timestamp ) throws Exception;
    List<RadomeCommandReplyObject> getRadomeCommandReplyCollectionByRadomeAtTimestamp( Guid radome, DateTime timestamp ) throws Exception;
    List<RadomeCommandReplyObject> getRadomeCommandReplyCollectionByRadomeFromTimestamp( Guid radome, DateTime timestamp ) throws Exception;
    List<RadomeCommandReplyObject> getRadomeCommandReplyCollectionByRadomeUntilTimestamp( Guid radome, DateTime timestamp ) throws Exception;
    List<RadomeCommandReplyObject> getRadomeCommandReplyCollectionByRadomeOverTimestamp( Guid radome, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<RadomeCommandReplyObject> getRadomeCommandReplyCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<RadomeCommandReplyObject> getRadomeCommandReplyCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<RadomeCommandReplyObject> getRadomeCommandReplyCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<RadomeCommandReplyObject> getRadomeCommandReplyCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<RadomeCommandReplyObject> getRadomeCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    RadomeCommandReplyObject getRadomeCommandReplyByCommand( Guid command ) throws Exception;
    List<RadomeCommandReplyObject> qetRadomeCommandReplyCollectionByCommandIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // RadomeConfiguration queries
    // ---------------------------------------------------------------------
    RadomeConfigurationObject getRadomeConfigurationById( Guid id ) throws Exception;
    List<RadomeConfigurationObject> getRadomeConfigurationCollection( ) throws Exception;
    List<RadomeConfigurationObject> getRadomeConfigurationCollectionByRadome( Guid radome ) throws Exception;
    RadomeConfigurationObject getRadomeConfigurationByRadomeAndTimestamp( Guid radome, DateTime timestamp ) throws Exception;
    RadomeConfigurationObject getRadomeConfigurationByRadomeAtTimestamp( Guid radome, DateTime timestamp ) throws Exception;
    List<RadomeConfigurationObject> getRadomeConfigurationByRadomeFromTimestamp( Guid radome, DateTime timestamp ) throws Exception;
    List<RadomeConfigurationObject> getRadomeConfigurationByRadomeUntilTimestamp( Guid radome, DateTime timestamp ) throws Exception;
    List<RadomeConfigurationObject> getRadomeConfigurationByRadomeOverTimestamp( Guid radome, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<RadomeConfigurationObject> getRadomeConfigurationCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<RadomeConfigurationObject> getRadomeConfigurationCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<RadomeConfigurationObject> getRadomeConfigurationCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<RadomeConfigurationObject> getRadomeConfigurationCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<RadomeConfigurationObject> getRadomeConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // ReferenceTimeseriesValue queries
    // ---------------------------------------------------------------------
    ReferenceTimeseriesValueObject getReferenceTimeseriesValueById( Guid id ) throws Exception;
    List<ReferenceTimeseriesValueObject> getReferenceTimeseriesValueCollection( ) throws Exception;
    List<ReferenceTimeseriesValueObject> getReferenceTimeseriesValueCollectionByTimeseries( Guid timeseries ) throws Exception;
    ReferenceTimeseriesValueObject getReferenceTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    ReferenceTimeseriesValueObject getReferenceTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<ReferenceTimeseriesValueObject> getReferenceTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<ReferenceTimeseriesValueObject> getReferenceTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<ReferenceTimeseriesValueObject> getReferenceTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<ReferenceTimeseriesValueObject> getReferenceTimeseriesValueCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<ReferenceTimeseriesValueObject> getReferenceTimeseriesValueCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<ReferenceTimeseriesValueObject> getReferenceTimeseriesValueCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<ReferenceTimeseriesValueObject> getReferenceTimeseriesValueCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<ReferenceTimeseriesValueObject> getReferenceTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<ReferenceTimeseriesValueObject> getReferenceTimeseriesValueCollectionByValue( Guid value ) throws Exception;
    // ---------------------------------------------------------------------
    // SByteTimeseriesValue queries
    // ---------------------------------------------------------------------
    SByteTimeseriesValueObject getSByteTimeseriesValueById( Guid id ) throws Exception;
    List<SByteTimeseriesValueObject> getSByteTimeseriesValueCollection( ) throws Exception;
    List<SByteTimeseriesValueObject> getSByteTimeseriesValueCollectionByTimeseries( Guid timeseries ) throws Exception;
    SByteTimeseriesValueObject getSByteTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    SByteTimeseriesValueObject getSByteTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<SByteTimeseriesValueObject> getSByteTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<SByteTimeseriesValueObject> getSByteTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<SByteTimeseriesValueObject> getSByteTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<SByteTimeseriesValueObject> getSByteTimeseriesValueCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<SByteTimeseriesValueObject> getSByteTimeseriesValueCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<SByteTimeseriesValueObject> getSByteTimeseriesValueCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<SByteTimeseriesValueObject> getSByteTimeseriesValueCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<SByteTimeseriesValueObject> getSByteTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // SecurityDomain queries
    // ---------------------------------------------------------------------
    SecurityDomainObject getSecurityDomainById( Guid id ) throws Exception;
    List<SecurityDomainObject> getSecurityDomainCollection( ) throws Exception;
    SecurityDomainObject getSecurityDomainByName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // SecurityIdentifier queries
    // ---------------------------------------------------------------------
    SecurityIdentifierObject getSecurityIdentifierById( Guid id ) throws Exception;
    List<SecurityIdentifierObject> getSecurityIdentifierCollection( ) throws Exception;
    List<SecurityIdentifierObject> getSecurityIdentifierCollectionByDomain( Guid domain ) throws Exception;
    SecurityIdentifierObject getSecurityIdentifierByDomainAndIdentity( Guid domain, String identity ) throws Exception;
    // ---------------------------------------------------------------------
    // SecurityLogin queries
    // ---------------------------------------------------------------------
    SecurityLoginObject getSecurityLoginById( Guid id ) throws Exception;
    List<SecurityLoginObject> getSecurityLoginCollection( ) throws Exception;
    List<SecurityLoginObject> getSecurityLoginCollectionByDomain( Guid domain ) throws Exception;
    SecurityLoginObject getSecurityLoginByDomainAndIdentity( Guid domain, String identity ) throws Exception;
    // ---------------------------------------------------------------------
    // SecurityRole queries
    // ---------------------------------------------------------------------
    SecurityRoleObject getSecurityRoleById( Guid id ) throws Exception;
    List<SecurityRoleObject> getSecurityRoleCollection( ) throws Exception;
    List<SecurityRoleObject> getSecurityRoleCollectionByDomain( Guid domain ) throws Exception;
    SecurityRoleObject getSecurityRoleByDomainAndIdentity( Guid domain, String identity ) throws Exception;
    SecurityRoleObject getSecurityRoleByName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // SecurityIdentifierRoleLink queries
    // ---------------------------------------------------------------------
    SecurityIdentifierRoleLinkObject getSecurityIdentifierRoleLinkById( Guid id ) throws Exception;
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollection( ) throws Exception;
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByMember( Guid member ) throws Exception;
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByMemberAndStart( Guid member, DateTime start ) throws Exception;
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByMemberAtStart( Guid member, DateTime start ) throws Exception;
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByMemberFromStart( Guid member, DateTime start ) throws Exception;
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByMemberUntilStart( Guid member, DateTime start ) throws Exception;
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByMemberOverStart( Guid member, DateTime fromStart, DateTime untilStart ) throws Exception;
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByRole( Guid role ) throws Exception;
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByRoleAndStart( Guid role, DateTime start ) throws Exception;
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByRoleAtStart( Guid role, DateTime start ) throws Exception;
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByRoleFromStart( Guid role, DateTime start ) throws Exception;
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByRoleUntilStart( Guid role, DateTime start ) throws Exception;
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByRoleOverStart( Guid role, DateTime fromStart, DateTime untilStart ) throws Exception;
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionByStart( DateTime start ) throws Exception;
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionAtStart( DateTime start ) throws Exception;
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionFromStart( DateTime start ) throws Exception;
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionUntilStart( DateTime start ) throws Exception;
    List<SecurityIdentifierRoleLinkObject> getSecurityIdentifierRoleLinkCollectionOverStart( DateTime fromStart, DateTime untilStart ) throws Exception;
    // ---------------------------------------------------------------------
    // SecurityLoginSession queries
    // ---------------------------------------------------------------------
    SecurityLoginSessionObject getSecurityLoginSessionById( Guid id ) throws Exception;
    List<SecurityLoginSessionObject> getSecurityLoginSessionCollection( ) throws Exception;
    List<SecurityLoginSessionObject> getSecurityLoginSessionCollectionByLogin( Guid login ) throws Exception;
    List<SecurityLoginSessionObject> getSecurityLoginSessionCollectionByLoginAndFromTime( Guid login, DateTime fromTime ) throws Exception;
    List<SecurityLoginSessionObject> getSecurityLoginSessionCollectionByLoginAtFromTime( Guid login, DateTime fromTime ) throws Exception;
    List<SecurityLoginSessionObject> getSecurityLoginSessionCollectionByLoginFromFromTime( Guid login, DateTime fromTime ) throws Exception;
    List<SecurityLoginSessionObject> getSecurityLoginSessionCollectionByLoginUntilFromTime( Guid login, DateTime fromTime ) throws Exception;
    List<SecurityLoginSessionObject> getSecurityLoginSessionCollectionByLoginOverFromTime( Guid login, DateTime fromFromTime, DateTime untilFromTime ) throws Exception;
    List<SecurityLoginSessionObject> getSecurityLoginSessionCollectionByFromTime( DateTime fromTime ) throws Exception;
    List<SecurityLoginSessionObject> getSecurityLoginSessionCollectionAtFromTime( DateTime fromTime ) throws Exception;
    List<SecurityLoginSessionObject> getSecurityLoginSessionCollectionFromFromTime( DateTime fromTime ) throws Exception;
    List<SecurityLoginSessionObject> getSecurityLoginSessionCollectionUntilFromTime( DateTime fromTime ) throws Exception;
    List<SecurityLoginSessionObject> getSecurityLoginSessionCollectionOverFromTime( DateTime fromFromTime, DateTime untilFromTime ) throws Exception;
    // ---------------------------------------------------------------------
    // SecurityPermission queries
    // ---------------------------------------------------------------------
    SecurityPermissionObject getSecurityPermissionById( Guid id ) throws Exception;
    List<SecurityPermissionObject> getSecurityPermissionCollection( ) throws Exception;
    List<SecurityPermissionObject> getSecurityPermissionCollectionByIdentifier( Guid identifier ) throws Exception;
    List<SecurityPermissionObject> getSecurityPermissionCollectionByIdentifierAndTypeCode( Guid identifier, int typeCode ) throws Exception;
    List<SecurityPermissionObject> getSecurityPermissionCollectionByIdentifierFromTypeCode( Guid identifier, int typeCode ) throws Exception;
    List<SecurityPermissionObject> getSecurityPermissionCollectionByIdentifierUntilTypeCode( Guid identifier, int typeCode ) throws Exception;
    List<SecurityPermissionObject> getSecurityPermissionCollectionByIdentifierOverTypeCode( Guid identifier, int fromTypeCode, int untilTypeCode ) throws Exception;
    SecurityPermissionObject getSecurityPermissionByIdentifierTypeCodeAndTimestamp( Guid identifier, int typeCode, DateTime timestamp ) throws Exception;
    SecurityPermissionObject getSecurityPermissionByIdentifierTypeCodeAtTimestamp( Guid identifier, int typeCode, DateTime timestamp ) throws Exception;
    List<SecurityPermissionObject> getSecurityPermissionByIdentifierTypeCodeFromTimestamp( Guid identifier, int typeCode, DateTime timestamp ) throws Exception;
    List<SecurityPermissionObject> getSecurityPermissionByIdentifierTypeCodeUntilTimestamp( Guid identifier, int typeCode, DateTime timestamp ) throws Exception;
    List<SecurityPermissionObject> getSecurityPermissionByIdentifierTypeCodeOverTimestamp( Guid identifier, int typeCode, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<SecurityPermissionObject> getSecurityPermissionCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<SecurityPermissionObject> getSecurityPermissionCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<SecurityPermissionObject> getSecurityPermissionCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<SecurityPermissionObject> getSecurityPermissionCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<SecurityPermissionObject> getSecurityPermissionCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // SingleTimeseriesValue queries
    // ---------------------------------------------------------------------
    SingleTimeseriesValueObject getSingleTimeseriesValueById( Guid id ) throws Exception;
    List<SingleTimeseriesValueObject> getSingleTimeseriesValueCollection( ) throws Exception;
    List<SingleTimeseriesValueObject> getSingleTimeseriesValueCollectionByTimeseries( Guid timeseries ) throws Exception;
    SingleTimeseriesValueObject getSingleTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    SingleTimeseriesValueObject getSingleTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<SingleTimeseriesValueObject> getSingleTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<SingleTimeseriesValueObject> getSingleTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<SingleTimeseriesValueObject> getSingleTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<SingleTimeseriesValueObject> getSingleTimeseriesValueCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<SingleTimeseriesValueObject> getSingleTimeseriesValueCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<SingleTimeseriesValueObject> getSingleTimeseriesValueCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<SingleTimeseriesValueObject> getSingleTimeseriesValueCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<SingleTimeseriesValueObject> getSingleTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // StringTimeseriesValue queries
    // ---------------------------------------------------------------------
    StringTimeseriesValueObject getStringTimeseriesValueById( Guid id ) throws Exception;
    List<StringTimeseriesValueObject> getStringTimeseriesValueCollection( ) throws Exception;
    List<StringTimeseriesValueObject> getStringTimeseriesValueCollectionByTimeseries( Guid timeseries ) throws Exception;
    StringTimeseriesValueObject getStringTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    StringTimeseriesValueObject getStringTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<StringTimeseriesValueObject> getStringTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<StringTimeseriesValueObject> getStringTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<StringTimeseriesValueObject> getStringTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<StringTimeseriesValueObject> getStringTimeseriesValueCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<StringTimeseriesValueObject> getStringTimeseriesValueCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<StringTimeseriesValueObject> getStringTimeseriesValueCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<StringTimeseriesValueObject> getStringTimeseriesValueCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<StringTimeseriesValueObject> getStringTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // TimeseriesCatalogElement queries
    // ---------------------------------------------------------------------
    TimeseriesCatalogElementObject getTimeseriesCatalogElementById( Guid id ) throws Exception;
    List<TimeseriesCatalogElementObject> getTimeseriesCatalogElementCollection( ) throws Exception;
    List<TimeseriesCatalogElementObject> getTimeseriesCatalogElementCollectionByCatalog( Guid catalog ) throws Exception;
    List<TimeseriesCatalogElementObject> qetTimeseriesCatalogElementCollectionByCatalogIsNull(  ) throws Exception;
    TimeseriesCatalogElementObject getTimeseriesCatalogElementByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<TimeseriesCatalogElementObject> qetTimeseriesCatalogElementCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // Timeseries queries
    // ---------------------------------------------------------------------
    TimeseriesObject getTimeseriesById( Guid id ) throws Exception;
    List<TimeseriesObject> getTimeseriesCollection( ) throws Exception;
    List<TimeseriesObject> getTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<TimeseriesObject> qetTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    TimeseriesObject getTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<TimeseriesObject> qetTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // BinaryTimeseries queries
    // ---------------------------------------------------------------------
    BinaryTimeseriesObject getBinaryTimeseriesById( Guid id ) throws Exception;
    List<BinaryTimeseriesObject> getBinaryTimeseriesCollection( ) throws Exception;
    List<BinaryTimeseriesObject> getBinaryTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<BinaryTimeseriesObject> qetBinaryTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    BinaryTimeseriesObject getBinaryTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<BinaryTimeseriesObject> qetBinaryTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // BooleanTimeseries queries
    // ---------------------------------------------------------------------
    BooleanTimeseriesObject getBooleanTimeseriesById( Guid id ) throws Exception;
    List<BooleanTimeseriesObject> getBooleanTimeseriesCollection( ) throws Exception;
    List<BooleanTimeseriesObject> getBooleanTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<BooleanTimeseriesObject> qetBooleanTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    BooleanTimeseriesObject getBooleanTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<BooleanTimeseriesObject> qetBooleanTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // AisAidToNavigationOffPositionTimeseries queries
    // ---------------------------------------------------------------------
    AisAidToNavigationOffPositionTimeseriesObject getAisAidToNavigationOffPositionTimeseriesById( Guid id ) throws Exception;
    List<AisAidToNavigationOffPositionTimeseriesObject> getAisAidToNavigationOffPositionTimeseriesCollection( ) throws Exception;
    List<AisAidToNavigationOffPositionTimeseriesObject> getAisAidToNavigationOffPositionTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<AisAidToNavigationOffPositionTimeseriesObject> qetAisAidToNavigationOffPositionTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    AisAidToNavigationOffPositionTimeseriesObject getAisAidToNavigationOffPositionTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<AisAidToNavigationOffPositionTimeseriesObject> qetAisAidToNavigationOffPositionTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    List<AisAidToNavigationOffPositionTimeseriesObject> getAisAidToNavigationOffPositionTimeseriesCollectionByAidToNavigation( Guid aidToNavigation ) throws Exception;
    List<AisAidToNavigationOffPositionTimeseriesObject> qetAisAidToNavigationOffPositionTimeseriesCollectionByAidToNavigationIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // DeviceEnabledTimeseries queries
    // ---------------------------------------------------------------------
    DeviceEnabledTimeseriesObject getDeviceEnabledTimeseriesById( Guid id ) throws Exception;
    List<DeviceEnabledTimeseriesObject> getDeviceEnabledTimeseriesCollection( ) throws Exception;
    List<DeviceEnabledTimeseriesObject> getDeviceEnabledTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<DeviceEnabledTimeseriesObject> qetDeviceEnabledTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    DeviceEnabledTimeseriesObject getDeviceEnabledTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<DeviceEnabledTimeseriesObject> qetDeviceEnabledTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarAutomaticSensitivityTimeControlTimeseries queries
    // ---------------------------------------------------------------------
    RadarAutomaticSensitivityTimeControlTimeseriesObject getRadarAutomaticSensitivityTimeControlTimeseriesById( Guid id ) throws Exception;
    List<RadarAutomaticSensitivityTimeControlTimeseriesObject> getRadarAutomaticSensitivityTimeControlTimeseriesCollection( ) throws Exception;
    List<RadarAutomaticSensitivityTimeControlTimeseriesObject> getRadarAutomaticSensitivityTimeControlTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<RadarAutomaticSensitivityTimeControlTimeseriesObject> qetRadarAutomaticSensitivityTimeControlTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    RadarAutomaticSensitivityTimeControlTimeseriesObject getRadarAutomaticSensitivityTimeControlTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<RadarAutomaticSensitivityTimeControlTimeseriesObject> qetRadarAutomaticSensitivityTimeControlTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarBlankSector1Timeseries queries
    // ---------------------------------------------------------------------
    RadarBlankSector1TimeseriesObject getRadarBlankSector1TimeseriesById( Guid id ) throws Exception;
    List<RadarBlankSector1TimeseriesObject> getRadarBlankSector1TimeseriesCollection( ) throws Exception;
    List<RadarBlankSector1TimeseriesObject> getRadarBlankSector1TimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<RadarBlankSector1TimeseriesObject> qetRadarBlankSector1TimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    RadarBlankSector1TimeseriesObject getRadarBlankSector1TimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<RadarBlankSector1TimeseriesObject> qetRadarBlankSector1TimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarBlankSector2Timeseries queries
    // ---------------------------------------------------------------------
    RadarBlankSector2TimeseriesObject getRadarBlankSector2TimeseriesById( Guid id ) throws Exception;
    List<RadarBlankSector2TimeseriesObject> getRadarBlankSector2TimeseriesCollection( ) throws Exception;
    List<RadarBlankSector2TimeseriesObject> getRadarBlankSector2TimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<RadarBlankSector2TimeseriesObject> qetRadarBlankSector2TimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    RadarBlankSector2TimeseriesObject getRadarBlankSector2TimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<RadarBlankSector2TimeseriesObject> qetRadarBlankSector2TimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarEnableAutomaticFrequencyControlTimeseries queries
    // ---------------------------------------------------------------------
    RadarEnableAutomaticFrequencyControlTimeseriesObject getRadarEnableAutomaticFrequencyControlTimeseriesById( Guid id ) throws Exception;
    List<RadarEnableAutomaticFrequencyControlTimeseriesObject> getRadarEnableAutomaticFrequencyControlTimeseriesCollection( ) throws Exception;
    List<RadarEnableAutomaticFrequencyControlTimeseriesObject> getRadarEnableAutomaticFrequencyControlTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<RadarEnableAutomaticFrequencyControlTimeseriesObject> qetRadarEnableAutomaticFrequencyControlTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    RadarEnableAutomaticFrequencyControlTimeseriesObject getRadarEnableAutomaticFrequencyControlTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<RadarEnableAutomaticFrequencyControlTimeseriesObject> qetRadarEnableAutomaticFrequencyControlTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarEnableFastTimeConstantTimeseries queries
    // ---------------------------------------------------------------------
    RadarEnableFastTimeConstantTimeseriesObject getRadarEnableFastTimeConstantTimeseriesById( Guid id ) throws Exception;
    List<RadarEnableFastTimeConstantTimeseriesObject> getRadarEnableFastTimeConstantTimeseriesCollection( ) throws Exception;
    List<RadarEnableFastTimeConstantTimeseriesObject> getRadarEnableFastTimeConstantTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<RadarEnableFastTimeConstantTimeseriesObject> qetRadarEnableFastTimeConstantTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    RadarEnableFastTimeConstantTimeseriesObject getRadarEnableFastTimeConstantTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<RadarEnableFastTimeConstantTimeseriesObject> qetRadarEnableFastTimeConstantTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarEnableSensitivityTimeControlTimeseries queries
    // ---------------------------------------------------------------------
    RadarEnableSensitivityTimeControlTimeseriesObject getRadarEnableSensitivityTimeControlTimeseriesById( Guid id ) throws Exception;
    List<RadarEnableSensitivityTimeControlTimeseriesObject> getRadarEnableSensitivityTimeControlTimeseriesCollection( ) throws Exception;
    List<RadarEnableSensitivityTimeControlTimeseriesObject> getRadarEnableSensitivityTimeControlTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<RadarEnableSensitivityTimeControlTimeseriesObject> qetRadarEnableSensitivityTimeControlTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    RadarEnableSensitivityTimeControlTimeseriesObject getRadarEnableSensitivityTimeControlTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<RadarEnableSensitivityTimeControlTimeseriesObject> qetRadarEnableSensitivityTimeControlTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarPowerOnTimeseries queries
    // ---------------------------------------------------------------------
    RadarPowerOnTimeseriesObject getRadarPowerOnTimeseriesById( Guid id ) throws Exception;
    List<RadarPowerOnTimeseriesObject> getRadarPowerOnTimeseriesCollection( ) throws Exception;
    List<RadarPowerOnTimeseriesObject> getRadarPowerOnTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<RadarPowerOnTimeseriesObject> qetRadarPowerOnTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    RadarPowerOnTimeseriesObject getRadarPowerOnTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<RadarPowerOnTimeseriesObject> qetRadarPowerOnTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarSaveSettingsTimeseries queries
    // ---------------------------------------------------------------------
    RadarSaveSettingsTimeseriesObject getRadarSaveSettingsTimeseriesById( Guid id ) throws Exception;
    List<RadarSaveSettingsTimeseriesObject> getRadarSaveSettingsTimeseriesCollection( ) throws Exception;
    List<RadarSaveSettingsTimeseriesObject> getRadarSaveSettingsTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<RadarSaveSettingsTimeseriesObject> qetRadarSaveSettingsTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    RadarSaveSettingsTimeseriesObject getRadarSaveSettingsTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<RadarSaveSettingsTimeseriesObject> qetRadarSaveSettingsTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarTrackingTimeseries queries
    // ---------------------------------------------------------------------
    RadarTrackingTimeseriesObject getRadarTrackingTimeseriesById( Guid id ) throws Exception;
    List<RadarTrackingTimeseriesObject> getRadarTrackingTimeseriesCollection( ) throws Exception;
    List<RadarTrackingTimeseriesObject> getRadarTrackingTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<RadarTrackingTimeseriesObject> qetRadarTrackingTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    RadarTrackingTimeseriesObject getRadarTrackingTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<RadarTrackingTimeseriesObject> qetRadarTrackingTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // MediaProxySessionEnabledTimeseries queries
    // ---------------------------------------------------------------------
    MediaProxySessionEnabledTimeseriesObject getMediaProxySessionEnabledTimeseriesById( Guid id ) throws Exception;
    List<MediaProxySessionEnabledTimeseriesObject> getMediaProxySessionEnabledTimeseriesCollection( ) throws Exception;
    List<MediaProxySessionEnabledTimeseriesObject> getMediaProxySessionEnabledTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<MediaProxySessionEnabledTimeseriesObject> qetMediaProxySessionEnabledTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    MediaProxySessionEnabledTimeseriesObject getMediaProxySessionEnabledTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<MediaProxySessionEnabledTimeseriesObject> qetMediaProxySessionEnabledTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // MediaServiceEnabledTimeseries queries
    // ---------------------------------------------------------------------
    MediaServiceEnabledTimeseriesObject getMediaServiceEnabledTimeseriesById( Guid id ) throws Exception;
    List<MediaServiceEnabledTimeseriesObject> getMediaServiceEnabledTimeseriesCollection( ) throws Exception;
    List<MediaServiceEnabledTimeseriesObject> getMediaServiceEnabledTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<MediaServiceEnabledTimeseriesObject> qetMediaServiceEnabledTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    MediaServiceEnabledTimeseriesObject getMediaServiceEnabledTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<MediaServiceEnabledTimeseriesObject> qetMediaServiceEnabledTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // ByteTimeseries queries
    // ---------------------------------------------------------------------
    ByteTimeseriesObject getByteTimeseriesById( Guid id ) throws Exception;
    List<ByteTimeseriesObject> getByteTimeseriesCollection( ) throws Exception;
    List<ByteTimeseriesObject> getByteTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<ByteTimeseriesObject> qetByteTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    ByteTimeseriesObject getByteTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<ByteTimeseriesObject> qetByteTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // DateTimeTimeseries queries
    // ---------------------------------------------------------------------
    DateTimeTimeseriesObject getDateTimeTimeseriesById( Guid id ) throws Exception;
    List<DateTimeTimeseriesObject> getDateTimeTimeseriesCollection( ) throws Exception;
    List<DateTimeTimeseriesObject> getDateTimeTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<DateTimeTimeseriesObject> qetDateTimeTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    DateTimeTimeseriesObject getDateTimeTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<DateTimeTimeseriesObject> qetDateTimeTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // DoubleTimeseries queries
    // ---------------------------------------------------------------------
    DoubleTimeseriesObject getDoubleTimeseriesById( Guid id ) throws Exception;
    List<DoubleTimeseriesObject> getDoubleTimeseriesCollection( ) throws Exception;
    List<DoubleTimeseriesObject> getDoubleTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<DoubleTimeseriesObject> qetDoubleTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    DoubleTimeseriesObject getDoubleTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<DoubleTimeseriesObject> qetDoubleTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // GNSSAltitudeTimeseries queries
    // ---------------------------------------------------------------------
    GNSSAltitudeTimeseriesObject getGNSSAltitudeTimeseriesById( Guid id ) throws Exception;
    List<GNSSAltitudeTimeseriesObject> getGNSSAltitudeTimeseriesCollection( ) throws Exception;
    List<GNSSAltitudeTimeseriesObject> getGNSSAltitudeTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<GNSSAltitudeTimeseriesObject> qetGNSSAltitudeTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    GNSSAltitudeTimeseriesObject getGNSSAltitudeTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<GNSSAltitudeTimeseriesObject> qetGNSSAltitudeTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // GNSSLatitudeTimeseries queries
    // ---------------------------------------------------------------------
    GNSSLatitudeTimeseriesObject getGNSSLatitudeTimeseriesById( Guid id ) throws Exception;
    List<GNSSLatitudeTimeseriesObject> getGNSSLatitudeTimeseriesCollection( ) throws Exception;
    List<GNSSLatitudeTimeseriesObject> getGNSSLatitudeTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<GNSSLatitudeTimeseriesObject> qetGNSSLatitudeTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    GNSSLatitudeTimeseriesObject getGNSSLatitudeTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<GNSSLatitudeTimeseriesObject> qetGNSSLatitudeTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // GNSSLongitudeTimeseries queries
    // ---------------------------------------------------------------------
    GNSSLongitudeTimeseriesObject getGNSSLongitudeTimeseriesById( Guid id ) throws Exception;
    List<GNSSLongitudeTimeseriesObject> getGNSSLongitudeTimeseriesCollection( ) throws Exception;
    List<GNSSLongitudeTimeseriesObject> getGNSSLongitudeTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<GNSSLongitudeTimeseriesObject> qetGNSSLongitudeTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    GNSSLongitudeTimeseriesObject getGNSSLongitudeTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<GNSSLongitudeTimeseriesObject> qetGNSSLongitudeTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // GyroCourseTimeseries queries
    // ---------------------------------------------------------------------
    GyroCourseTimeseriesObject getGyroCourseTimeseriesById( Guid id ) throws Exception;
    List<GyroCourseTimeseriesObject> getGyroCourseTimeseriesCollection( ) throws Exception;
    List<GyroCourseTimeseriesObject> getGyroCourseTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<GyroCourseTimeseriesObject> qetGyroCourseTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    GyroCourseTimeseriesObject getGyroCourseTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<GyroCourseTimeseriesObject> qetGyroCourseTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    GyroCourseTimeseriesObject getGyroCourseTimeseriesByGyroDevice( Guid gyroDevice ) throws Exception;
    List<GyroCourseTimeseriesObject> qetGyroCourseTimeseriesCollectionByGyroDeviceIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // GyroHeadingMagneticNorthTimeseries queries
    // ---------------------------------------------------------------------
    GyroHeadingMagneticNorthTimeseriesObject getGyroHeadingMagneticNorthTimeseriesById( Guid id ) throws Exception;
    List<GyroHeadingMagneticNorthTimeseriesObject> getGyroHeadingMagneticNorthTimeseriesCollection( ) throws Exception;
    List<GyroHeadingMagneticNorthTimeseriesObject> getGyroHeadingMagneticNorthTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<GyroHeadingMagneticNorthTimeseriesObject> qetGyroHeadingMagneticNorthTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    GyroHeadingMagneticNorthTimeseriesObject getGyroHeadingMagneticNorthTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<GyroHeadingMagneticNorthTimeseriesObject> qetGyroHeadingMagneticNorthTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    GyroHeadingMagneticNorthTimeseriesObject getGyroHeadingMagneticNorthTimeseriesByGyroDevice( Guid gyroDevice ) throws Exception;
    List<GyroHeadingMagneticNorthTimeseriesObject> qetGyroHeadingMagneticNorthTimeseriesCollectionByGyroDeviceIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // GyroHeadingTrueNorthTimeseries queries
    // ---------------------------------------------------------------------
    GyroHeadingTrueNorthTimeseriesObject getGyroHeadingTrueNorthTimeseriesById( Guid id ) throws Exception;
    List<GyroHeadingTrueNorthTimeseriesObject> getGyroHeadingTrueNorthTimeseriesCollection( ) throws Exception;
    List<GyroHeadingTrueNorthTimeseriesObject> getGyroHeadingTrueNorthTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<GyroHeadingTrueNorthTimeseriesObject> qetGyroHeadingTrueNorthTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    GyroHeadingTrueNorthTimeseriesObject getGyroHeadingTrueNorthTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<GyroHeadingTrueNorthTimeseriesObject> qetGyroHeadingTrueNorthTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    GyroHeadingTrueNorthTimeseriesObject getGyroHeadingTrueNorthTimeseriesByGyroDevice( Guid gyroDevice ) throws Exception;
    List<GyroHeadingTrueNorthTimeseriesObject> qetGyroHeadingTrueNorthTimeseriesCollectionByGyroDeviceIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // GyroPitchTimeseries queries
    // ---------------------------------------------------------------------
    GyroPitchTimeseriesObject getGyroPitchTimeseriesById( Guid id ) throws Exception;
    List<GyroPitchTimeseriesObject> getGyroPitchTimeseriesCollection( ) throws Exception;
    List<GyroPitchTimeseriesObject> getGyroPitchTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<GyroPitchTimeseriesObject> qetGyroPitchTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    GyroPitchTimeseriesObject getGyroPitchTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<GyroPitchTimeseriesObject> qetGyroPitchTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    GyroPitchTimeseriesObject getGyroPitchTimeseriesByGyroDevice( Guid gyroDevice ) throws Exception;
    List<GyroPitchTimeseriesObject> qetGyroPitchTimeseriesCollectionByGyroDeviceIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // GyroRateOfTurnTimeseries queries
    // ---------------------------------------------------------------------
    GyroRateOfTurnTimeseriesObject getGyroRateOfTurnTimeseriesById( Guid id ) throws Exception;
    List<GyroRateOfTurnTimeseriesObject> getGyroRateOfTurnTimeseriesCollection( ) throws Exception;
    List<GyroRateOfTurnTimeseriesObject> getGyroRateOfTurnTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<GyroRateOfTurnTimeseriesObject> qetGyroRateOfTurnTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    GyroRateOfTurnTimeseriesObject getGyroRateOfTurnTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<GyroRateOfTurnTimeseriesObject> qetGyroRateOfTurnTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    GyroRateOfTurnTimeseriesObject getGyroRateOfTurnTimeseriesByGyroDevice( Guid gyroDevice ) throws Exception;
    List<GyroRateOfTurnTimeseriesObject> qetGyroRateOfTurnTimeseriesCollectionByGyroDeviceIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // GyroRollTimeseries queries
    // ---------------------------------------------------------------------
    GyroRollTimeseriesObject getGyroRollTimeseriesById( Guid id ) throws Exception;
    List<GyroRollTimeseriesObject> getGyroRollTimeseriesCollection( ) throws Exception;
    List<GyroRollTimeseriesObject> getGyroRollTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<GyroRollTimeseriesObject> qetGyroRollTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    GyroRollTimeseriesObject getGyroRollTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<GyroRollTimeseriesObject> qetGyroRollTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    GyroRollTimeseriesObject getGyroRollTimeseriesByGyroDevice( Guid gyroDevice ) throws Exception;
    List<GyroRollTimeseriesObject> qetGyroRollTimeseriesCollectionByGyroDeviceIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // GyroSpeedTimeseries queries
    // ---------------------------------------------------------------------
    GyroSpeedTimeseriesObject getGyroSpeedTimeseriesById( Guid id ) throws Exception;
    List<GyroSpeedTimeseriesObject> getGyroSpeedTimeseriesCollection( ) throws Exception;
    List<GyroSpeedTimeseriesObject> getGyroSpeedTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<GyroSpeedTimeseriesObject> qetGyroSpeedTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    GyroSpeedTimeseriesObject getGyroSpeedTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<GyroSpeedTimeseriesObject> qetGyroSpeedTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    GyroSpeedTimeseriesObject getGyroSpeedTimeseriesByGyroDevice( Guid gyroDevice ) throws Exception;
    List<GyroSpeedTimeseriesObject> qetGyroSpeedTimeseriesCollectionByGyroDeviceIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarLatitudeTimeseries queries
    // ---------------------------------------------------------------------
    RadarLatitudeTimeseriesObject getRadarLatitudeTimeseriesById( Guid id ) throws Exception;
    List<RadarLatitudeTimeseriesObject> getRadarLatitudeTimeseriesCollection( ) throws Exception;
    List<RadarLatitudeTimeseriesObject> getRadarLatitudeTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<RadarLatitudeTimeseriesObject> qetRadarLatitudeTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    RadarLatitudeTimeseriesObject getRadarLatitudeTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<RadarLatitudeTimeseriesObject> qetRadarLatitudeTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarLongitudeTimeseries queries
    // ---------------------------------------------------------------------
    RadarLongitudeTimeseriesObject getRadarLongitudeTimeseriesById( Guid id ) throws Exception;
    List<RadarLongitudeTimeseriesObject> getRadarLongitudeTimeseriesCollection( ) throws Exception;
    List<RadarLongitudeTimeseriesObject> getRadarLongitudeTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<RadarLongitudeTimeseriesObject> qetRadarLongitudeTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    RadarLongitudeTimeseriesObject getRadarLongitudeTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<RadarLongitudeTimeseriesObject> qetRadarLongitudeTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadomeDewPointTimeseries queries
    // ---------------------------------------------------------------------
    RadomeDewPointTimeseriesObject getRadomeDewPointTimeseriesById( Guid id ) throws Exception;
    List<RadomeDewPointTimeseriesObject> getRadomeDewPointTimeseriesCollection( ) throws Exception;
    List<RadomeDewPointTimeseriesObject> getRadomeDewPointTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<RadomeDewPointTimeseriesObject> qetRadomeDewPointTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    RadomeDewPointTimeseriesObject getRadomeDewPointTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<RadomeDewPointTimeseriesObject> qetRadomeDewPointTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadomePressureTimeseries queries
    // ---------------------------------------------------------------------
    RadomePressureTimeseriesObject getRadomePressureTimeseriesById( Guid id ) throws Exception;
    List<RadomePressureTimeseriesObject> getRadomePressureTimeseriesCollection( ) throws Exception;
    List<RadomePressureTimeseriesObject> getRadomePressureTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<RadomePressureTimeseriesObject> qetRadomePressureTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    RadomePressureTimeseriesObject getRadomePressureTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<RadomePressureTimeseriesObject> qetRadomePressureTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadomeTemperatureTimeseries queries
    // ---------------------------------------------------------------------
    RadomeTemperatureTimeseriesObject getRadomeTemperatureTimeseriesById( Guid id ) throws Exception;
    List<RadomeTemperatureTimeseriesObject> getRadomeTemperatureTimeseriesCollection( ) throws Exception;
    List<RadomeTemperatureTimeseriesObject> getRadomeTemperatureTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<RadomeTemperatureTimeseriesObject> qetRadomeTemperatureTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    RadomeTemperatureTimeseriesObject getRadomeTemperatureTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<RadomeTemperatureTimeseriesObject> qetRadomeTemperatureTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // VesselDraughtTimeseries queries
    // ---------------------------------------------------------------------
    VesselDraughtTimeseriesObject getVesselDraughtTimeseriesById( Guid id ) throws Exception;
    List<VesselDraughtTimeseriesObject> getVesselDraughtTimeseriesCollection( ) throws Exception;
    List<VesselDraughtTimeseriesObject> getVesselDraughtTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<VesselDraughtTimeseriesObject> qetVesselDraughtTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    VesselDraughtTimeseriesObject getVesselDraughtTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<VesselDraughtTimeseriesObject> qetVesselDraughtTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // ViewLatitudeTimeseries queries
    // ---------------------------------------------------------------------
    ViewLatitudeTimeseriesObject getViewLatitudeTimeseriesById( Guid id ) throws Exception;
    List<ViewLatitudeTimeseriesObject> getViewLatitudeTimeseriesCollection( ) throws Exception;
    List<ViewLatitudeTimeseriesObject> getViewLatitudeTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<ViewLatitudeTimeseriesObject> qetViewLatitudeTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    ViewLatitudeTimeseriesObject getViewLatitudeTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<ViewLatitudeTimeseriesObject> qetViewLatitudeTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // ViewLongitudeTimeseries queries
    // ---------------------------------------------------------------------
    ViewLongitudeTimeseriesObject getViewLongitudeTimeseriesById( Guid id ) throws Exception;
    List<ViewLongitudeTimeseriesObject> getViewLongitudeTimeseriesCollection( ) throws Exception;
    List<ViewLongitudeTimeseriesObject> getViewLongitudeTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<ViewLongitudeTimeseriesObject> qetViewLongitudeTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    ViewLongitudeTimeseriesObject getViewLongitudeTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<ViewLongitudeTimeseriesObject> qetViewLongitudeTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // ViewZoomLevelTimeseries queries
    // ---------------------------------------------------------------------
    ViewZoomLevelTimeseriesObject getViewZoomLevelTimeseriesById( Guid id ) throws Exception;
    List<ViewZoomLevelTimeseriesObject> getViewZoomLevelTimeseriesCollection( ) throws Exception;
    List<ViewZoomLevelTimeseriesObject> getViewZoomLevelTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<ViewZoomLevelTimeseriesObject> qetViewZoomLevelTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    ViewZoomLevelTimeseriesObject getViewZoomLevelTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<ViewZoomLevelTimeseriesObject> qetViewZoomLevelTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // WeatherStationAbsoluteHumidityTimeseries queries
    // ---------------------------------------------------------------------
    WeatherStationAbsoluteHumidityTimeseriesObject getWeatherStationAbsoluteHumidityTimeseriesById( Guid id ) throws Exception;
    List<WeatherStationAbsoluteHumidityTimeseriesObject> getWeatherStationAbsoluteHumidityTimeseriesCollection( ) throws Exception;
    List<WeatherStationAbsoluteHumidityTimeseriesObject> getWeatherStationAbsoluteHumidityTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<WeatherStationAbsoluteHumidityTimeseriesObject> qetWeatherStationAbsoluteHumidityTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    WeatherStationAbsoluteHumidityTimeseriesObject getWeatherStationAbsoluteHumidityTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<WeatherStationAbsoluteHumidityTimeseriesObject> qetWeatherStationAbsoluteHumidityTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    WeatherStationAbsoluteHumidityTimeseriesObject getWeatherStationAbsoluteHumidityTimeseriesByWeatherStation( Guid weatherStation ) throws Exception;
    List<WeatherStationAbsoluteHumidityTimeseriesObject> qetWeatherStationAbsoluteHumidityTimeseriesCollectionByWeatherStationIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // WeatherStationAirTemperatureTimeseries queries
    // ---------------------------------------------------------------------
    WeatherStationAirTemperatureTimeseriesObject getWeatherStationAirTemperatureTimeseriesById( Guid id ) throws Exception;
    List<WeatherStationAirTemperatureTimeseriesObject> getWeatherStationAirTemperatureTimeseriesCollection( ) throws Exception;
    List<WeatherStationAirTemperatureTimeseriesObject> getWeatherStationAirTemperatureTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<WeatherStationAirTemperatureTimeseriesObject> qetWeatherStationAirTemperatureTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    WeatherStationAirTemperatureTimeseriesObject getWeatherStationAirTemperatureTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<WeatherStationAirTemperatureTimeseriesObject> qetWeatherStationAirTemperatureTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    WeatherStationAirTemperatureTimeseriesObject getWeatherStationAirTemperatureTimeseriesByWeatherStation( Guid weatherStation ) throws Exception;
    List<WeatherStationAirTemperatureTimeseriesObject> qetWeatherStationAirTemperatureTimeseriesCollectionByWeatherStationIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // WeatherStationBarometricPressureTimeseries queries
    // ---------------------------------------------------------------------
    WeatherStationBarometricPressureTimeseriesObject getWeatherStationBarometricPressureTimeseriesById( Guid id ) throws Exception;
    List<WeatherStationBarometricPressureTimeseriesObject> getWeatherStationBarometricPressureTimeseriesCollection( ) throws Exception;
    List<WeatherStationBarometricPressureTimeseriesObject> getWeatherStationBarometricPressureTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<WeatherStationBarometricPressureTimeseriesObject> qetWeatherStationBarometricPressureTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    WeatherStationBarometricPressureTimeseriesObject getWeatherStationBarometricPressureTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<WeatherStationBarometricPressureTimeseriesObject> qetWeatherStationBarometricPressureTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    WeatherStationBarometricPressureTimeseriesObject getWeatherStationBarometricPressureTimeseriesByWeatherStation( Guid weatherStation ) throws Exception;
    List<WeatherStationBarometricPressureTimeseriesObject> qetWeatherStationBarometricPressureTimeseriesCollectionByWeatherStationIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // WeatherStationDewPointTimeseries queries
    // ---------------------------------------------------------------------
    WeatherStationDewPointTimeseriesObject getWeatherStationDewPointTimeseriesById( Guid id ) throws Exception;
    List<WeatherStationDewPointTimeseriesObject> getWeatherStationDewPointTimeseriesCollection( ) throws Exception;
    List<WeatherStationDewPointTimeseriesObject> getWeatherStationDewPointTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<WeatherStationDewPointTimeseriesObject> qetWeatherStationDewPointTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    WeatherStationDewPointTimeseriesObject getWeatherStationDewPointTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<WeatherStationDewPointTimeseriesObject> qetWeatherStationDewPointTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    WeatherStationDewPointTimeseriesObject getWeatherStationDewPointTimeseriesByWeatherStation( Guid weatherStation ) throws Exception;
    List<WeatherStationDewPointTimeseriesObject> qetWeatherStationDewPointTimeseriesCollectionByWeatherStationIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // WeatherStationRelativeHumidityTimeseries queries
    // ---------------------------------------------------------------------
    WeatherStationRelativeHumidityTimeseriesObject getWeatherStationRelativeHumidityTimeseriesById( Guid id ) throws Exception;
    List<WeatherStationRelativeHumidityTimeseriesObject> getWeatherStationRelativeHumidityTimeseriesCollection( ) throws Exception;
    List<WeatherStationRelativeHumidityTimeseriesObject> getWeatherStationRelativeHumidityTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<WeatherStationRelativeHumidityTimeseriesObject> qetWeatherStationRelativeHumidityTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    WeatherStationRelativeHumidityTimeseriesObject getWeatherStationRelativeHumidityTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<WeatherStationRelativeHumidityTimeseriesObject> qetWeatherStationRelativeHumidityTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    WeatherStationRelativeHumidityTimeseriesObject getWeatherStationRelativeHumidityTimeseriesByWeatherStation( Guid weatherStation ) throws Exception;
    List<WeatherStationRelativeHumidityTimeseriesObject> qetWeatherStationRelativeHumidityTimeseriesCollectionByWeatherStationIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // WeatherStationWaterTemperatureTimeseries queries
    // ---------------------------------------------------------------------
    WeatherStationWaterTemperatureTimeseriesObject getWeatherStationWaterTemperatureTimeseriesById( Guid id ) throws Exception;
    List<WeatherStationWaterTemperatureTimeseriesObject> getWeatherStationWaterTemperatureTimeseriesCollection( ) throws Exception;
    List<WeatherStationWaterTemperatureTimeseriesObject> getWeatherStationWaterTemperatureTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<WeatherStationWaterTemperatureTimeseriesObject> qetWeatherStationWaterTemperatureTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    WeatherStationWaterTemperatureTimeseriesObject getWeatherStationWaterTemperatureTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<WeatherStationWaterTemperatureTimeseriesObject> qetWeatherStationWaterTemperatureTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    WeatherStationWaterTemperatureTimeseriesObject getWeatherStationWaterTemperatureTimeseriesByWeatherStation( Guid weatherStation ) throws Exception;
    List<WeatherStationWaterTemperatureTimeseriesObject> qetWeatherStationWaterTemperatureTimeseriesCollectionByWeatherStationIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // WeatherStationWindDirectionTimeseries queries
    // ---------------------------------------------------------------------
    WeatherStationWindDirectionTimeseriesObject getWeatherStationWindDirectionTimeseriesById( Guid id ) throws Exception;
    List<WeatherStationWindDirectionTimeseriesObject> getWeatherStationWindDirectionTimeseriesCollection( ) throws Exception;
    List<WeatherStationWindDirectionTimeseriesObject> getWeatherStationWindDirectionTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<WeatherStationWindDirectionTimeseriesObject> qetWeatherStationWindDirectionTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    WeatherStationWindDirectionTimeseriesObject getWeatherStationWindDirectionTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<WeatherStationWindDirectionTimeseriesObject> qetWeatherStationWindDirectionTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    WeatherStationWindDirectionTimeseriesObject getWeatherStationWindDirectionTimeseriesByWeatherStation( Guid weatherStation ) throws Exception;
    List<WeatherStationWindDirectionTimeseriesObject> qetWeatherStationWindDirectionTimeseriesCollectionByWeatherStationIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // WeatherStationWindSpeedTimeseries queries
    // ---------------------------------------------------------------------
    WeatherStationWindSpeedTimeseriesObject getWeatherStationWindSpeedTimeseriesById( Guid id ) throws Exception;
    List<WeatherStationWindSpeedTimeseriesObject> getWeatherStationWindSpeedTimeseriesCollection( ) throws Exception;
    List<WeatherStationWindSpeedTimeseriesObject> getWeatherStationWindSpeedTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<WeatherStationWindSpeedTimeseriesObject> qetWeatherStationWindSpeedTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    WeatherStationWindSpeedTimeseriesObject getWeatherStationWindSpeedTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<WeatherStationWindSpeedTimeseriesObject> qetWeatherStationWindSpeedTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    WeatherStationWindSpeedTimeseriesObject getWeatherStationWindSpeedTimeseriesByWeatherStation( Guid weatherStation ) throws Exception;
    List<WeatherStationWindSpeedTimeseriesObject> qetWeatherStationWindSpeedTimeseriesCollectionByWeatherStationIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // GeoPosition2DTimeseries queries
    // ---------------------------------------------------------------------
    GeoPosition2DTimeseriesObject getGeoPosition2DTimeseriesById( Guid id ) throws Exception;
    List<GeoPosition2DTimeseriesObject> getGeoPosition2DTimeseriesCollection( ) throws Exception;
    List<GeoPosition2DTimeseriesObject> getGeoPosition2DTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<GeoPosition2DTimeseriesObject> qetGeoPosition2DTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    GeoPosition2DTimeseriesObject getGeoPosition2DTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<GeoPosition2DTimeseriesObject> qetGeoPosition2DTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // AisAidToNavigationPositionTimeseries queries
    // ---------------------------------------------------------------------
    AisAidToNavigationPositionTimeseriesObject getAisAidToNavigationPositionTimeseriesById( Guid id ) throws Exception;
    List<AisAidToNavigationPositionTimeseriesObject> getAisAidToNavigationPositionTimeseriesCollection( ) throws Exception;
    List<AisAidToNavigationPositionTimeseriesObject> getAisAidToNavigationPositionTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<AisAidToNavigationPositionTimeseriesObject> qetAisAidToNavigationPositionTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    AisAidToNavigationPositionTimeseriesObject getAisAidToNavigationPositionTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<AisAidToNavigationPositionTimeseriesObject> qetAisAidToNavigationPositionTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // GeoPosition3DTimeseries queries
    // ---------------------------------------------------------------------
    GeoPosition3DTimeseriesObject getGeoPosition3DTimeseriesById( Guid id ) throws Exception;
    List<GeoPosition3DTimeseriesObject> getGeoPosition3DTimeseriesCollection( ) throws Exception;
    List<GeoPosition3DTimeseriesObject> getGeoPosition3DTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<GeoPosition3DTimeseriesObject> qetGeoPosition3DTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    GeoPosition3DTimeseriesObject getGeoPosition3DTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<GeoPosition3DTimeseriesObject> qetGeoPosition3DTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // GuidTimeseries queries
    // ---------------------------------------------------------------------
    GuidTimeseriesObject getGuidTimeseriesById( Guid id ) throws Exception;
    List<GuidTimeseriesObject> getGuidTimeseriesCollection( ) throws Exception;
    List<GuidTimeseriesObject> getGuidTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<GuidTimeseriesObject> qetGuidTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    GuidTimeseriesObject getGuidTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<GuidTimeseriesObject> qetGuidTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // Int16Timeseries queries
    // ---------------------------------------------------------------------
    Int16TimeseriesObject getInt16TimeseriesById( Guid id ) throws Exception;
    List<Int16TimeseriesObject> getInt16TimeseriesCollection( ) throws Exception;
    List<Int16TimeseriesObject> getInt16TimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<Int16TimeseriesObject> qetInt16TimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    Int16TimeseriesObject getInt16TimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<Int16TimeseriesObject> qetInt16TimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // Int32Timeseries queries
    // ---------------------------------------------------------------------
    Int32TimeseriesObject getInt32TimeseriesById( Guid id ) throws Exception;
    List<Int32TimeseriesObject> getInt32TimeseriesCollection( ) throws Exception;
    List<Int32TimeseriesObject> getInt32TimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<Int32TimeseriesObject> qetInt32TimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    Int32TimeseriesObject getInt32TimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<Int32TimeseriesObject> qetInt32TimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarAzimuthOffsetTimeseries queries
    // ---------------------------------------------------------------------
    RadarAzimuthOffsetTimeseriesObject getRadarAzimuthOffsetTimeseriesById( Guid id ) throws Exception;
    List<RadarAzimuthOffsetTimeseriesObject> getRadarAzimuthOffsetTimeseriesCollection( ) throws Exception;
    List<RadarAzimuthOffsetTimeseriesObject> getRadarAzimuthOffsetTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<RadarAzimuthOffsetTimeseriesObject> qetRadarAzimuthOffsetTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    RadarAzimuthOffsetTimeseriesObject getRadarAzimuthOffsetTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<RadarAzimuthOffsetTimeseriesObject> qetRadarAzimuthOffsetTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarFastTimeConstantLevelTimeseries queries
    // ---------------------------------------------------------------------
    RadarFastTimeConstantLevelTimeseriesObject getRadarFastTimeConstantLevelTimeseriesById( Guid id ) throws Exception;
    List<RadarFastTimeConstantLevelTimeseriesObject> getRadarFastTimeConstantLevelTimeseriesCollection( ) throws Exception;
    List<RadarFastTimeConstantLevelTimeseriesObject> getRadarFastTimeConstantLevelTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<RadarFastTimeConstantLevelTimeseriesObject> qetRadarFastTimeConstantLevelTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    RadarFastTimeConstantLevelTimeseriesObject getRadarFastTimeConstantLevelTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<RadarFastTimeConstantLevelTimeseriesObject> qetRadarFastTimeConstantLevelTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarFastTimeConstantModeTimeseries queries
    // ---------------------------------------------------------------------
    RadarFastTimeConstantModeTimeseriesObject getRadarFastTimeConstantModeTimeseriesById( Guid id ) throws Exception;
    List<RadarFastTimeConstantModeTimeseriesObject> getRadarFastTimeConstantModeTimeseriesCollection( ) throws Exception;
    List<RadarFastTimeConstantModeTimeseriesObject> getRadarFastTimeConstantModeTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<RadarFastTimeConstantModeTimeseriesObject> qetRadarFastTimeConstantModeTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    RadarFastTimeConstantModeTimeseriesObject getRadarFastTimeConstantModeTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<RadarFastTimeConstantModeTimeseriesObject> qetRadarFastTimeConstantModeTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarPulseTimeseries queries
    // ---------------------------------------------------------------------
    RadarPulseTimeseriesObject getRadarPulseTimeseriesById( Guid id ) throws Exception;
    List<RadarPulseTimeseriesObject> getRadarPulseTimeseriesCollection( ) throws Exception;
    List<RadarPulseTimeseriesObject> getRadarPulseTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<RadarPulseTimeseriesObject> qetRadarPulseTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    RadarPulseTimeseriesObject getRadarPulseTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<RadarPulseTimeseriesObject> qetRadarPulseTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarSector1EndTimeseries queries
    // ---------------------------------------------------------------------
    RadarSector1EndTimeseriesObject getRadarSector1EndTimeseriesById( Guid id ) throws Exception;
    List<RadarSector1EndTimeseriesObject> getRadarSector1EndTimeseriesCollection( ) throws Exception;
    List<RadarSector1EndTimeseriesObject> getRadarSector1EndTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<RadarSector1EndTimeseriesObject> qetRadarSector1EndTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    RadarSector1EndTimeseriesObject getRadarSector1EndTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<RadarSector1EndTimeseriesObject> qetRadarSector1EndTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarSector1StartTimeseries queries
    // ---------------------------------------------------------------------
    RadarSector1StartTimeseriesObject getRadarSector1StartTimeseriesById( Guid id ) throws Exception;
    List<RadarSector1StartTimeseriesObject> getRadarSector1StartTimeseriesCollection( ) throws Exception;
    List<RadarSector1StartTimeseriesObject> getRadarSector1StartTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<RadarSector1StartTimeseriesObject> qetRadarSector1StartTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    RadarSector1StartTimeseriesObject getRadarSector1StartTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<RadarSector1StartTimeseriesObject> qetRadarSector1StartTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarSector2EndTimeseries queries
    // ---------------------------------------------------------------------
    RadarSector2EndTimeseriesObject getRadarSector2EndTimeseriesById( Guid id ) throws Exception;
    List<RadarSector2EndTimeseriesObject> getRadarSector2EndTimeseriesCollection( ) throws Exception;
    List<RadarSector2EndTimeseriesObject> getRadarSector2EndTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<RadarSector2EndTimeseriesObject> qetRadarSector2EndTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    RadarSector2EndTimeseriesObject getRadarSector2EndTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<RadarSector2EndTimeseriesObject> qetRadarSector2EndTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarSector2StartTimeseries queries
    // ---------------------------------------------------------------------
    RadarSector2StartTimeseriesObject getRadarSector2StartTimeseriesById( Guid id ) throws Exception;
    List<RadarSector2StartTimeseriesObject> getRadarSector2StartTimeseriesCollection( ) throws Exception;
    List<RadarSector2StartTimeseriesObject> getRadarSector2StartTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<RadarSector2StartTimeseriesObject> qetRadarSector2StartTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    RadarSector2StartTimeseriesObject getRadarSector2StartTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<RadarSector2StartTimeseriesObject> qetRadarSector2StartTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarSensitivityTimeControlLevelTimeseries queries
    // ---------------------------------------------------------------------
    RadarSensitivityTimeControlLevelTimeseriesObject getRadarSensitivityTimeControlLevelTimeseriesById( Guid id ) throws Exception;
    List<RadarSensitivityTimeControlLevelTimeseriesObject> getRadarSensitivityTimeControlLevelTimeseriesCollection( ) throws Exception;
    List<RadarSensitivityTimeControlLevelTimeseriesObject> getRadarSensitivityTimeControlLevelTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<RadarSensitivityTimeControlLevelTimeseriesObject> qetRadarSensitivityTimeControlLevelTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    RadarSensitivityTimeControlLevelTimeseriesObject getRadarSensitivityTimeControlLevelTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<RadarSensitivityTimeControlLevelTimeseriesObject> qetRadarSensitivityTimeControlLevelTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadarTuningTimeseries queries
    // ---------------------------------------------------------------------
    RadarTuningTimeseriesObject getRadarTuningTimeseriesById( Guid id ) throws Exception;
    List<RadarTuningTimeseriesObject> getRadarTuningTimeseriesCollection( ) throws Exception;
    List<RadarTuningTimeseriesObject> getRadarTuningTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<RadarTuningTimeseriesObject> qetRadarTuningTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    RadarTuningTimeseriesObject getRadarTuningTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<RadarTuningTimeseriesObject> qetRadarTuningTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // VesselPersonsOnBoardTimeseries queries
    // ---------------------------------------------------------------------
    VesselPersonsOnBoardTimeseriesObject getVesselPersonsOnBoardTimeseriesById( Guid id ) throws Exception;
    List<VesselPersonsOnBoardTimeseriesObject> getVesselPersonsOnBoardTimeseriesCollection( ) throws Exception;
    List<VesselPersonsOnBoardTimeseriesObject> getVesselPersonsOnBoardTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<VesselPersonsOnBoardTimeseriesObject> qetVesselPersonsOnBoardTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    VesselPersonsOnBoardTimeseriesObject getVesselPersonsOnBoardTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<VesselPersonsOnBoardTimeseriesObject> qetVesselPersonsOnBoardTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // Int64Timeseries queries
    // ---------------------------------------------------------------------
    Int64TimeseriesObject getInt64TimeseriesById( Guid id ) throws Exception;
    List<Int64TimeseriesObject> getInt64TimeseriesCollection( ) throws Exception;
    List<Int64TimeseriesObject> getInt64TimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<Int64TimeseriesObject> qetInt64TimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    Int64TimeseriesObject getInt64TimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<Int64TimeseriesObject> qetInt64TimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // Position2DTimeseries queries
    // ---------------------------------------------------------------------
    Position2DTimeseriesObject getPosition2DTimeseriesById( Guid id ) throws Exception;
    List<Position2DTimeseriesObject> getPosition2DTimeseriesCollection( ) throws Exception;
    List<Position2DTimeseriesObject> getPosition2DTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<Position2DTimeseriesObject> qetPosition2DTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    Position2DTimeseriesObject getPosition2DTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<Position2DTimeseriesObject> qetPosition2DTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // Position3DTimeseries queries
    // ---------------------------------------------------------------------
    Position3DTimeseriesObject getPosition3DTimeseriesById( Guid id ) throws Exception;
    List<Position3DTimeseriesObject> getPosition3DTimeseriesCollection( ) throws Exception;
    List<Position3DTimeseriesObject> getPosition3DTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<Position3DTimeseriesObject> qetPosition3DTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    Position3DTimeseriesObject getPosition3DTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<Position3DTimeseriesObject> qetPosition3DTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // ReferenceTimeseries queries
    // ---------------------------------------------------------------------
    ReferenceTimeseriesObject getReferenceTimeseriesById( Guid id ) throws Exception;
    List<ReferenceTimeseriesObject> getReferenceTimeseriesCollection( ) throws Exception;
    List<ReferenceTimeseriesObject> getReferenceTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<ReferenceTimeseriesObject> qetReferenceTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    ReferenceTimeseriesObject getReferenceTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<ReferenceTimeseriesObject> qetReferenceTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // SByteTimeseries queries
    // ---------------------------------------------------------------------
    SByteTimeseriesObject getSByteTimeseriesById( Guid id ) throws Exception;
    List<SByteTimeseriesObject> getSByteTimeseriesCollection( ) throws Exception;
    List<SByteTimeseriesObject> getSByteTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<SByteTimeseriesObject> qetSByteTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    SByteTimeseriesObject getSByteTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<SByteTimeseriesObject> qetSByteTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // SingleTimeseries queries
    // ---------------------------------------------------------------------
    SingleTimeseriesObject getSingleTimeseriesById( Guid id ) throws Exception;
    List<SingleTimeseriesObject> getSingleTimeseriesCollection( ) throws Exception;
    List<SingleTimeseriesObject> getSingleTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<SingleTimeseriesObject> qetSingleTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    SingleTimeseriesObject getSingleTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<SingleTimeseriesObject> qetSingleTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // StringTimeseries queries
    // ---------------------------------------------------------------------
    StringTimeseriesObject getStringTimeseriesById( Guid id ) throws Exception;
    List<StringTimeseriesObject> getStringTimeseriesCollection( ) throws Exception;
    List<StringTimeseriesObject> getStringTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<StringTimeseriesObject> qetStringTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    StringTimeseriesObject getStringTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<StringTimeseriesObject> qetStringTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // TimeSpanTimeseries queries
    // ---------------------------------------------------------------------
    TimeSpanTimeseriesObject getTimeSpanTimeseriesById( Guid id ) throws Exception;
    List<TimeSpanTimeseriesObject> getTimeSpanTimeseriesCollection( ) throws Exception;
    List<TimeSpanTimeseriesObject> getTimeSpanTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<TimeSpanTimeseriesObject> qetTimeSpanTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    TimeSpanTimeseriesObject getTimeSpanTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<TimeSpanTimeseriesObject> qetTimeSpanTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // UInt16Timeseries queries
    // ---------------------------------------------------------------------
    UInt16TimeseriesObject getUInt16TimeseriesById( Guid id ) throws Exception;
    List<UInt16TimeseriesObject> getUInt16TimeseriesCollection( ) throws Exception;
    List<UInt16TimeseriesObject> getUInt16TimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<UInt16TimeseriesObject> qetUInt16TimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    UInt16TimeseriesObject getUInt16TimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<UInt16TimeseriesObject> qetUInt16TimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // UInt32Timeseries queries
    // ---------------------------------------------------------------------
    UInt32TimeseriesObject getUInt32TimeseriesById( Guid id ) throws Exception;
    List<UInt32TimeseriesObject> getUInt32TimeseriesCollection( ) throws Exception;
    List<UInt32TimeseriesObject> getUInt32TimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<UInt32TimeseriesObject> qetUInt32TimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    UInt32TimeseriesObject getUInt32TimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<UInt32TimeseriesObject> qetUInt32TimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // RadomeStatusTimeseries queries
    // ---------------------------------------------------------------------
    RadomeStatusTimeseriesObject getRadomeStatusTimeseriesById( Guid id ) throws Exception;
    List<RadomeStatusTimeseriesObject> getRadomeStatusTimeseriesCollection( ) throws Exception;
    List<RadomeStatusTimeseriesObject> getRadomeStatusTimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<RadomeStatusTimeseriesObject> qetRadomeStatusTimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    RadomeStatusTimeseriesObject getRadomeStatusTimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<RadomeStatusTimeseriesObject> qetRadomeStatusTimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // UInt64Timeseries queries
    // ---------------------------------------------------------------------
    UInt64TimeseriesObject getUInt64TimeseriesById( Guid id ) throws Exception;
    List<UInt64TimeseriesObject> getUInt64TimeseriesCollection( ) throws Exception;
    List<UInt64TimeseriesObject> getUInt64TimeseriesCollectionByCatalog( Guid catalog ) throws Exception;
    List<UInt64TimeseriesObject> qetUInt64TimeseriesCollectionByCatalogIsNull(  ) throws Exception;
    UInt64TimeseriesObject getUInt64TimeseriesByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<UInt64TimeseriesObject> qetUInt64TimeseriesCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // TimeseriesCatalog queries
    // ---------------------------------------------------------------------
    TimeseriesCatalogObject getTimeseriesCatalogById( Guid id ) throws Exception;
    List<TimeseriesCatalogObject> getTimeseriesCatalogCollection( ) throws Exception;
    List<TimeseriesCatalogObject> getTimeseriesCatalogCollectionByCatalog( Guid catalog ) throws Exception;
    List<TimeseriesCatalogObject> qetTimeseriesCatalogCollectionByCatalogIsNull(  ) throws Exception;
    TimeseriesCatalogObject getTimeseriesCatalogByCatalogAndName( Guid catalog, String name ) throws Exception;
    List<TimeseriesCatalogObject> qetTimeseriesCatalogCollectionByCatalogIsNullAndName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // TimeseriesInfo queries
    // ---------------------------------------------------------------------
    TimeseriesInfoObject getTimeseriesInfoById( Guid id ) throws Exception;
    List<TimeseriesInfoObject> getTimeseriesInfoCollection( ) throws Exception;
    // ---------------------------------------------------------------------
    // TimeSpanTimeseriesValue queries
    // ---------------------------------------------------------------------
    TimeSpanTimeseriesValueObject getTimeSpanTimeseriesValueById( Guid id ) throws Exception;
    List<TimeSpanTimeseriesValueObject> getTimeSpanTimeseriesValueCollection( ) throws Exception;
    List<TimeSpanTimeseriesValueObject> getTimeSpanTimeseriesValueCollectionByTimeseries( Guid timeseries ) throws Exception;
    TimeSpanTimeseriesValueObject getTimeSpanTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    TimeSpanTimeseriesValueObject getTimeSpanTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<TimeSpanTimeseriesValueObject> getTimeSpanTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<TimeSpanTimeseriesValueObject> getTimeSpanTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<TimeSpanTimeseriesValueObject> getTimeSpanTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<TimeSpanTimeseriesValueObject> getTimeSpanTimeseriesValueCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<TimeSpanTimeseriesValueObject> getTimeSpanTimeseriesValueCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<TimeSpanTimeseriesValueObject> getTimeSpanTimeseriesValueCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<TimeSpanTimeseriesValueObject> getTimeSpanTimeseriesValueCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<TimeSpanTimeseriesValueObject> getTimeSpanTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // TrackableItemTrackLink queries
    // ---------------------------------------------------------------------
    TrackableItemTrackLinkObject getTrackableItemTrackLinkById( Guid id ) throws Exception;
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollection( ) throws Exception;
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByItem( Guid item ) throws Exception;
    TrackableItemTrackLinkObject getTrackableItemTrackLinkByItemAndStart( Guid item, DateTime start ) throws Exception;
    TrackableItemTrackLinkObject getTrackableItemTrackLinkByItemAtStart( Guid item, DateTime start ) throws Exception;
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkByItemFromStart( Guid item, DateTime start ) throws Exception;
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkByItemUntilStart( Guid item, DateTime start ) throws Exception;
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkByItemOverStart( Guid item, DateTime fromStart, DateTime untilStart ) throws Exception;
    List<TrackableItemTrackLinkObject> qetTrackableItemTrackLinkCollectionByItem(  ) throws Exception;
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByItemAndEnd( Guid item, DateTime end ) throws Exception;
    List<TrackableItemTrackLinkObject> qetTrackableItemTrackLinkCollectionByItemAndEndIsNull( Guid item ) throws Exception;
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByItemAtEnd( Guid item, DateTime end ) throws Exception;
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByItemFromEnd( Guid item, DateTime end ) throws Exception;
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByItemUntilEnd( Guid item, DateTime end ) throws Exception;
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByItemOverEnd( Guid item, DateTime fromEnd, DateTime untilEnd ) throws Exception;
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByTrack( Guid track ) throws Exception;
    TrackableItemTrackLinkObject getTrackableItemTrackLinkByTrackAndStart( Guid track, DateTime start ) throws Exception;
    TrackableItemTrackLinkObject getTrackableItemTrackLinkByTrackAtStart( Guid track, DateTime start ) throws Exception;
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkByTrackFromStart( Guid track, DateTime start ) throws Exception;
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkByTrackUntilStart( Guid track, DateTime start ) throws Exception;
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkByTrackOverStart( Guid track, DateTime fromStart, DateTime untilStart ) throws Exception;
    List<TrackableItemTrackLinkObject> qetTrackableItemTrackLinkCollectionByTrack(  ) throws Exception;
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByTrackAndEnd( Guid track, DateTime end ) throws Exception;
    List<TrackableItemTrackLinkObject> qetTrackableItemTrackLinkCollectionByTrackAndEndIsNull( Guid track ) throws Exception;
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByTrackAtEnd( Guid track, DateTime end ) throws Exception;
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByTrackFromEnd( Guid track, DateTime end ) throws Exception;
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByTrackUntilEnd( Guid track, DateTime end ) throws Exception;
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByTrackOverEnd( Guid track, DateTime fromEnd, DateTime untilEnd ) throws Exception;
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionByStart( DateTime start ) throws Exception;
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionAtStart( DateTime start ) throws Exception;
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionFromStart( DateTime start ) throws Exception;
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionUntilStart( DateTime start ) throws Exception;
    List<TrackableItemTrackLinkObject> getTrackableItemTrackLinkCollectionOverStart( DateTime fromStart, DateTime untilStart ) throws Exception;
    // ---------------------------------------------------------------------
    // TrackBase queries
    // ---------------------------------------------------------------------
    TrackBaseObject getTrackBaseById( Guid id ) throws Exception;
    List<TrackBaseObject> getTrackBaseCollection( ) throws Exception;
    List<TrackBaseObject> getTrackBaseCollectionByTracker( Guid tracker ) throws Exception;
    List<TrackBaseObject> getTrackBaseCollectionByTrackerAndTrackNumber( Guid tracker, long trackNumber ) throws Exception;
    List<TrackBaseObject> getTrackBaseCollectionByTrackerFromTrackNumber( Guid tracker, long trackNumber ) throws Exception;
    List<TrackBaseObject> getTrackBaseCollectionByTrackerUntilTrackNumber( Guid tracker, long trackNumber ) throws Exception;
    List<TrackBaseObject> getTrackBaseCollectionByTrackerOverTrackNumber( Guid tracker, long fromTrackNumber, long untilTrackNumber ) throws Exception;
    TrackBaseObject getTrackBaseByTrackerTrackNumberAndTimestamp( Guid tracker, long trackNumber, DateTime timestamp ) throws Exception;
    TrackBaseObject getTrackBaseByTrackerTrackNumberAtTimestamp( Guid tracker, long trackNumber, DateTime timestamp ) throws Exception;
    List<TrackBaseObject> getTrackBaseByTrackerTrackNumberFromTimestamp( Guid tracker, long trackNumber, DateTime timestamp ) throws Exception;
    List<TrackBaseObject> getTrackBaseByTrackerTrackNumberUntilTimestamp( Guid tracker, long trackNumber, DateTime timestamp ) throws Exception;
    List<TrackBaseObject> getTrackBaseByTrackerTrackNumberOverTimestamp( Guid tracker, long trackNumber, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<TrackBaseObject> getTrackBaseCollectionByTrackerAndTimestamp( Guid tracker, DateTime timestamp ) throws Exception;
    List<TrackBaseObject> getTrackBaseCollectionByTrackerAtTimestamp( Guid tracker, DateTime timestamp ) throws Exception;
    List<TrackBaseObject> getTrackBaseCollectionByTrackerFromTimestamp( Guid tracker, DateTime timestamp ) throws Exception;
    List<TrackBaseObject> getTrackBaseCollectionByTrackerUntilTimestamp( Guid tracker, DateTime timestamp ) throws Exception;
    List<TrackBaseObject> getTrackBaseCollectionByTrackerOverTimestamp( Guid tracker, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<TrackBaseObject> getTrackBaseCollectionByTrackNumber( long trackNumber ) throws Exception;
    List<TrackBaseObject> getTrackBaseCollectionFromTrackNumber( long trackNumber ) throws Exception;
    List<TrackBaseObject> getTrackBaseCollectionUntilTrackNumber( long trackNumber ) throws Exception;
    List<TrackBaseObject> getTrackBaseCollectionOverTrackNumber( long fromTrackNumber, long untilTrackNumber ) throws Exception;
    List<TrackBaseObject> getTrackBaseCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<TrackBaseObject> getTrackBaseCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<TrackBaseObject> getTrackBaseCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<TrackBaseObject> getTrackBaseCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<TrackBaseObject> getTrackBaseCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // Track queries
    // ---------------------------------------------------------------------
    TrackObject getTrackById( Guid id ) throws Exception;
    List<TrackObject> getTrackCollection( ) throws Exception;
    List<TrackObject> getTrackCollectionByTracker( Guid tracker ) throws Exception;
    List<TrackObject> getTrackCollectionByTrackerAndTrackNumber( Guid tracker, long trackNumber ) throws Exception;
    List<TrackObject> getTrackCollectionByTrackerFromTrackNumber( Guid tracker, long trackNumber ) throws Exception;
    List<TrackObject> getTrackCollectionByTrackerUntilTrackNumber( Guid tracker, long trackNumber ) throws Exception;
    List<TrackObject> getTrackCollectionByTrackerOverTrackNumber( Guid tracker, long fromTrackNumber, long untilTrackNumber ) throws Exception;
    TrackObject getTrackByTrackerTrackNumberAndTimestamp( Guid tracker, long trackNumber, DateTime timestamp ) throws Exception;
    TrackObject getTrackByTrackerTrackNumberAtTimestamp( Guid tracker, long trackNumber, DateTime timestamp ) throws Exception;
    List<TrackObject> getTrackByTrackerTrackNumberFromTimestamp( Guid tracker, long trackNumber, DateTime timestamp ) throws Exception;
    List<TrackObject> getTrackByTrackerTrackNumberUntilTimestamp( Guid tracker, long trackNumber, DateTime timestamp ) throws Exception;
    List<TrackObject> getTrackByTrackerTrackNumberOverTimestamp( Guid tracker, long trackNumber, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<TrackObject> getTrackCollectionByTrackerAndTimestamp( Guid tracker, DateTime timestamp ) throws Exception;
    List<TrackObject> getTrackCollectionByTrackerAtTimestamp( Guid tracker, DateTime timestamp ) throws Exception;
    List<TrackObject> getTrackCollectionByTrackerFromTimestamp( Guid tracker, DateTime timestamp ) throws Exception;
    List<TrackObject> getTrackCollectionByTrackerUntilTimestamp( Guid tracker, DateTime timestamp ) throws Exception;
    List<TrackObject> getTrackCollectionByTrackerOverTimestamp( Guid tracker, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<TrackObject> getTrackCollectionByTrackNumber( long trackNumber ) throws Exception;
    List<TrackObject> getTrackCollectionFromTrackNumber( long trackNumber ) throws Exception;
    List<TrackObject> getTrackCollectionUntilTrackNumber( long trackNumber ) throws Exception;
    List<TrackObject> getTrackCollectionOverTrackNumber( long fromTrackNumber, long untilTrackNumber ) throws Exception;
    List<TrackObject> getTrackCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<TrackObject> getTrackCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<TrackObject> getTrackCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<TrackObject> getTrackCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<TrackObject> getTrackCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // Track3D queries
    // ---------------------------------------------------------------------
    Track3DObject getTrack3DById( Guid id ) throws Exception;
    List<Track3DObject> getTrack3DCollection( ) throws Exception;
    List<Track3DObject> getTrack3DCollectionByTracker( Guid tracker ) throws Exception;
    List<Track3DObject> getTrack3DCollectionByTrackerAndTrackNumber( Guid tracker, long trackNumber ) throws Exception;
    List<Track3DObject> getTrack3DCollectionByTrackerFromTrackNumber( Guid tracker, long trackNumber ) throws Exception;
    List<Track3DObject> getTrack3DCollectionByTrackerUntilTrackNumber( Guid tracker, long trackNumber ) throws Exception;
    List<Track3DObject> getTrack3DCollectionByTrackerOverTrackNumber( Guid tracker, long fromTrackNumber, long untilTrackNumber ) throws Exception;
    Track3DObject getTrack3DByTrackerTrackNumberAndTimestamp( Guid tracker, long trackNumber, DateTime timestamp ) throws Exception;
    Track3DObject getTrack3DByTrackerTrackNumberAtTimestamp( Guid tracker, long trackNumber, DateTime timestamp ) throws Exception;
    List<Track3DObject> getTrack3DByTrackerTrackNumberFromTimestamp( Guid tracker, long trackNumber, DateTime timestamp ) throws Exception;
    List<Track3DObject> getTrack3DByTrackerTrackNumberUntilTimestamp( Guid tracker, long trackNumber, DateTime timestamp ) throws Exception;
    List<Track3DObject> getTrack3DByTrackerTrackNumberOverTimestamp( Guid tracker, long trackNumber, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<Track3DObject> getTrack3DCollectionByTrackerAndTimestamp( Guid tracker, DateTime timestamp ) throws Exception;
    List<Track3DObject> getTrack3DCollectionByTrackerAtTimestamp( Guid tracker, DateTime timestamp ) throws Exception;
    List<Track3DObject> getTrack3DCollectionByTrackerFromTimestamp( Guid tracker, DateTime timestamp ) throws Exception;
    List<Track3DObject> getTrack3DCollectionByTrackerUntilTimestamp( Guid tracker, DateTime timestamp ) throws Exception;
    List<Track3DObject> getTrack3DCollectionByTrackerOverTimestamp( Guid tracker, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<Track3DObject> getTrack3DCollectionByTrackNumber( long trackNumber ) throws Exception;
    List<Track3DObject> getTrack3DCollectionFromTrackNumber( long trackNumber ) throws Exception;
    List<Track3DObject> getTrack3DCollectionUntilTrackNumber( long trackNumber ) throws Exception;
    List<Track3DObject> getTrack3DCollectionOverTrackNumber( long fromTrackNumber, long untilTrackNumber ) throws Exception;
    List<Track3DObject> getTrack3DCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<Track3DObject> getTrack3DCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<Track3DObject> getTrack3DCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<Track3DObject> getTrack3DCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<Track3DObject> getTrack3DCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // TrackerFilterParameters queries
    // ---------------------------------------------------------------------
    TrackerFilterParametersObject getTrackerFilterParametersById( Guid id ) throws Exception;
    List<TrackerFilterParametersObject> getTrackerFilterParametersCollection( ) throws Exception;
    List<TrackerFilterParametersObject> getTrackerFilterParametersCollectionByTracker( Guid tracker ) throws Exception;
    TrackerFilterParametersObject getTrackerFilterParametersByTrackerAndName( Guid tracker, String name ) throws Exception;
    // ---------------------------------------------------------------------
    // TrackerFilterParametersConfiguration queries
    // ---------------------------------------------------------------------
    TrackerFilterParametersConfigurationObject getTrackerFilterParametersConfigurationById( Guid id ) throws Exception;
    List<TrackerFilterParametersConfigurationObject> getTrackerFilterParametersConfigurationCollection( ) throws Exception;
    List<TrackerFilterParametersConfigurationObject> getTrackerFilterParametersConfigurationCollectionByParameters( Guid parameters ) throws Exception;
    TrackerFilterParametersConfigurationObject getTrackerFilterParametersConfigurationByParametersAndTimestamp( Guid parameters, DateTime timestamp ) throws Exception;
    TrackerFilterParametersConfigurationObject getTrackerFilterParametersConfigurationByParametersAtTimestamp( Guid parameters, DateTime timestamp ) throws Exception;
    List<TrackerFilterParametersConfigurationObject> getTrackerFilterParametersConfigurationByParametersFromTimestamp( Guid parameters, DateTime timestamp ) throws Exception;
    List<TrackerFilterParametersConfigurationObject> getTrackerFilterParametersConfigurationByParametersUntilTimestamp( Guid parameters, DateTime timestamp ) throws Exception;
    List<TrackerFilterParametersConfigurationObject> getTrackerFilterParametersConfigurationByParametersOverTimestamp( Guid parameters, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<TrackerFilterParametersConfigurationObject> getTrackerFilterParametersConfigurationCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<TrackerFilterParametersConfigurationObject> getTrackerFilterParametersConfigurationCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<TrackerFilterParametersConfigurationObject> getTrackerFilterParametersConfigurationCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<TrackerFilterParametersConfigurationObject> getTrackerFilterParametersConfigurationCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<TrackerFilterParametersConfigurationObject> getTrackerFilterParametersConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // TrackInfo queries
    // ---------------------------------------------------------------------
    TrackInfoObject getTrackInfoById( Guid id ) throws Exception;
    List<TrackInfoObject> getTrackInfoCollection( ) throws Exception;
    // ---------------------------------------------------------------------
    // TrackingServiceOptions queries
    // ---------------------------------------------------------------------
    TrackingServiceOptionsObject getTrackingServiceOptionsById( Guid id ) throws Exception;
    List<TrackingServiceOptionsObject> getTrackingServiceOptionsCollection( ) throws Exception;
    TrackingServiceOptionsObject getTrackingServiceOptionsByTimestamp( DateTime timestamp ) throws Exception;
    TrackingServiceOptionsObject getTrackingServiceOptionsAtTimestamp( DateTime timestamp ) throws Exception;
    List<TrackingServiceOptionsObject> getTrackingServiceOptionsFromTimestamp( DateTime timestamp ) throws Exception;
    List<TrackingServiceOptionsObject> getTrackingServiceOptionsUntilTimestamp( DateTime timestamp ) throws Exception;
    List<TrackingServiceOptionsObject> getTrackingServiceOptionsOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // TrackLink queries
    // ---------------------------------------------------------------------
    TrackLinkObject getTrackLinkById( Guid id ) throws Exception;
    List<TrackLinkObject> getTrackLinkCollection( ) throws Exception;
    List<TrackLinkObject> getTrackLinkCollectionByPrimary( Guid primary ) throws Exception;
    List<TrackLinkObject> getTrackLinkCollectionByPrimaryAndStart( Guid primary, DateTime start ) throws Exception;
    List<TrackLinkObject> getTrackLinkCollectionByPrimaryAtStart( Guid primary, DateTime start ) throws Exception;
    List<TrackLinkObject> getTrackLinkCollectionByPrimaryFromStart( Guid primary, DateTime start ) throws Exception;
    List<TrackLinkObject> getTrackLinkCollectionByPrimaryUntilStart( Guid primary, DateTime start ) throws Exception;
    List<TrackLinkObject> getTrackLinkCollectionByPrimaryOverStart( Guid primary, DateTime fromStart, DateTime untilStart ) throws Exception;
    List<TrackLinkObject> getTrackLinkCollectionBySecondary( Guid secondary ) throws Exception;
    List<TrackLinkObject> getTrackLinkCollectionBySecondaryAndStart( Guid secondary, DateTime start ) throws Exception;
    List<TrackLinkObject> getTrackLinkCollectionBySecondaryAtStart( Guid secondary, DateTime start ) throws Exception;
    List<TrackLinkObject> getTrackLinkCollectionBySecondaryFromStart( Guid secondary, DateTime start ) throws Exception;
    List<TrackLinkObject> getTrackLinkCollectionBySecondaryUntilStart( Guid secondary, DateTime start ) throws Exception;
    List<TrackLinkObject> getTrackLinkCollectionBySecondaryOverStart( Guid secondary, DateTime fromStart, DateTime untilStart ) throws Exception;
    List<TrackLinkObject> getTrackLinkCollectionByStart( DateTime start ) throws Exception;
    List<TrackLinkObject> getTrackLinkCollectionAtStart( DateTime start ) throws Exception;
    List<TrackLinkObject> getTrackLinkCollectionFromStart( DateTime start ) throws Exception;
    List<TrackLinkObject> getTrackLinkCollectionUntilStart( DateTime start ) throws Exception;
    List<TrackLinkObject> getTrackLinkCollectionOverStart( DateTime fromStart, DateTime untilStart ) throws Exception;
    // ---------------------------------------------------------------------
    // TrackValue queries
    // ---------------------------------------------------------------------
    TrackValueObject getTrackValueById( Guid id ) throws Exception;
    List<TrackValueObject> getTrackValueCollection( ) throws Exception;
    List<TrackValueObject> getTrackValueCollectionByTrack( Guid track ) throws Exception;
    TrackValueObject getTrackValueByTrackAndTimestamp( Guid track, DateTime timestamp ) throws Exception;
    TrackValueObject getTrackValueByTrackAtTimestamp( Guid track, DateTime timestamp ) throws Exception;
    List<TrackValueObject> getTrackValueByTrackFromTimestamp( Guid track, DateTime timestamp ) throws Exception;
    List<TrackValueObject> getTrackValueByTrackUntilTimestamp( Guid track, DateTime timestamp ) throws Exception;
    List<TrackValueObject> getTrackValueByTrackOverTimestamp( Guid track, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<TrackValueObject> getTrackValueCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<TrackValueObject> getTrackValueCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<TrackValueObject> getTrackValueCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<TrackValueObject> getTrackValueCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<TrackValueObject> getTrackValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // TrackValue3D queries
    // ---------------------------------------------------------------------
    TrackValue3DObject getTrackValue3DById( Guid id ) throws Exception;
    List<TrackValue3DObject> getTrackValue3DCollection( ) throws Exception;
    List<TrackValue3DObject> getTrackValue3DCollectionByTrack( Guid track ) throws Exception;
    TrackValue3DObject getTrackValue3DByTrackAndTimestamp( Guid track, DateTime timestamp ) throws Exception;
    TrackValue3DObject getTrackValue3DByTrackAtTimestamp( Guid track, DateTime timestamp ) throws Exception;
    List<TrackValue3DObject> getTrackValue3DByTrackFromTimestamp( Guid track, DateTime timestamp ) throws Exception;
    List<TrackValue3DObject> getTrackValue3DByTrackUntilTimestamp( Guid track, DateTime timestamp ) throws Exception;
    List<TrackValue3DObject> getTrackValue3DByTrackOverTimestamp( Guid track, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<TrackValue3DObject> getTrackValue3DCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<TrackValue3DObject> getTrackValue3DCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<TrackValue3DObject> getTrackValue3DCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<TrackValue3DObject> getTrackValue3DCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<TrackValue3DObject> getTrackValue3DCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // UInt16TimeseriesValue queries
    // ---------------------------------------------------------------------
    UInt16TimeseriesValueObject getUInt16TimeseriesValueById( Guid id ) throws Exception;
    List<UInt16TimeseriesValueObject> getUInt16TimeseriesValueCollection( ) throws Exception;
    List<UInt16TimeseriesValueObject> getUInt16TimeseriesValueCollectionByTimeseries( Guid timeseries ) throws Exception;
    UInt16TimeseriesValueObject getUInt16TimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    UInt16TimeseriesValueObject getUInt16TimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<UInt16TimeseriesValueObject> getUInt16TimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<UInt16TimeseriesValueObject> getUInt16TimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<UInt16TimeseriesValueObject> getUInt16TimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<UInt16TimeseriesValueObject> getUInt16TimeseriesValueCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<UInt16TimeseriesValueObject> getUInt16TimeseriesValueCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<UInt16TimeseriesValueObject> getUInt16TimeseriesValueCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<UInt16TimeseriesValueObject> getUInt16TimeseriesValueCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<UInt16TimeseriesValueObject> getUInt16TimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // UInt32TimeseriesValue queries
    // ---------------------------------------------------------------------
    UInt32TimeseriesValueObject getUInt32TimeseriesValueById( Guid id ) throws Exception;
    List<UInt32TimeseriesValueObject> getUInt32TimeseriesValueCollection( ) throws Exception;
    List<UInt32TimeseriesValueObject> getUInt32TimeseriesValueCollectionByTimeseries( Guid timeseries ) throws Exception;
    UInt32TimeseriesValueObject getUInt32TimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    UInt32TimeseriesValueObject getUInt32TimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<UInt32TimeseriesValueObject> getUInt32TimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<UInt32TimeseriesValueObject> getUInt32TimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<UInt32TimeseriesValueObject> getUInt32TimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<UInt32TimeseriesValueObject> getUInt32TimeseriesValueCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<UInt32TimeseriesValueObject> getUInt32TimeseriesValueCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<UInt32TimeseriesValueObject> getUInt32TimeseriesValueCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<UInt32TimeseriesValueObject> getUInt32TimeseriesValueCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<UInt32TimeseriesValueObject> getUInt32TimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // UInt64TimeseriesValue queries
    // ---------------------------------------------------------------------
    UInt64TimeseriesValueObject getUInt64TimeseriesValueById( Guid id ) throws Exception;
    List<UInt64TimeseriesValueObject> getUInt64TimeseriesValueCollection( ) throws Exception;
    List<UInt64TimeseriesValueObject> getUInt64TimeseriesValueCollectionByTimeseries( Guid timeseries ) throws Exception;
    UInt64TimeseriesValueObject getUInt64TimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    UInt64TimeseriesValueObject getUInt64TimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<UInt64TimeseriesValueObject> getUInt64TimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<UInt64TimeseriesValueObject> getUInt64TimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp ) throws Exception;
    List<UInt64TimeseriesValueObject> getUInt64TimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<UInt64TimeseriesValueObject> getUInt64TimeseriesValueCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<UInt64TimeseriesValueObject> getUInt64TimeseriesValueCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<UInt64TimeseriesValueObject> getUInt64TimeseriesValueCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<UInt64TimeseriesValueObject> getUInt64TimeseriesValueCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<UInt64TimeseriesValueObject> getUInt64TimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // VehicleType queries
    // ---------------------------------------------------------------------
    VehicleTypeObject getVehicleTypeById( Guid id ) throws Exception;
    List<VehicleTypeObject> getVehicleTypeCollection( ) throws Exception;
    VehicleTypeObject getVehicleTypeByName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // VesselType queries
    // ---------------------------------------------------------------------
    VesselTypeObject getVesselTypeById( Guid id ) throws Exception;
    List<VesselTypeObject> getVesselTypeCollection( ) throws Exception;
    VesselTypeObject getVesselTypeByName( String name ) throws Exception;
    VesselTypeObject getVesselTypeByCode( int code ) throws Exception;
    List<VesselTypeObject> getVesselTypeFromCode( int code ) throws Exception;
    List<VesselTypeObject> getVesselTypeUntilCode( int code ) throws Exception;
    List<VesselTypeObject> getVesselTypeOverCode( int fromCode, int untilCode ) throws Exception;
    // ---------------------------------------------------------------------
    // View queries
    // ---------------------------------------------------------------------
    ViewObject getViewById( Guid id ) throws Exception;
    List<ViewObject> getViewCollection( ) throws Exception;
    ViewObject getViewByName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // ViewCameraLink queries
    // ---------------------------------------------------------------------
    ViewCameraLinkObject getViewCameraLinkById( Guid id ) throws Exception;
    List<ViewCameraLinkObject> getViewCameraLinkCollection( ) throws Exception;
    List<ViewCameraLinkObject> getViewCameraLinkCollectionByView( Guid view ) throws Exception;
    ViewCameraLinkObject getViewCameraLinkByViewAndStart( Guid view, DateTime start ) throws Exception;
    ViewCameraLinkObject getViewCameraLinkByViewAtStart( Guid view, DateTime start ) throws Exception;
    List<ViewCameraLinkObject> getViewCameraLinkByViewFromStart( Guid view, DateTime start ) throws Exception;
    List<ViewCameraLinkObject> getViewCameraLinkByViewUntilStart( Guid view, DateTime start ) throws Exception;
    List<ViewCameraLinkObject> getViewCameraLinkByViewOverStart( Guid view, DateTime fromStart, DateTime untilStart ) throws Exception;
    List<ViewCameraLinkObject> getViewCameraLinkCollectionByCamera( Guid camera ) throws Exception;
    ViewCameraLinkObject getViewCameraLinkByCameraAndStart( Guid camera, DateTime start ) throws Exception;
    ViewCameraLinkObject getViewCameraLinkByCameraAtStart( Guid camera, DateTime start ) throws Exception;
    List<ViewCameraLinkObject> getViewCameraLinkByCameraFromStart( Guid camera, DateTime start ) throws Exception;
    List<ViewCameraLinkObject> getViewCameraLinkByCameraUntilStart( Guid camera, DateTime start ) throws Exception;
    List<ViewCameraLinkObject> getViewCameraLinkByCameraOverStart( Guid camera, DateTime fromStart, DateTime untilStart ) throws Exception;
    List<ViewCameraLinkObject> getViewCameraLinkCollectionByStart( DateTime start ) throws Exception;
    List<ViewCameraLinkObject> getViewCameraLinkCollectionAtStart( DateTime start ) throws Exception;
    List<ViewCameraLinkObject> getViewCameraLinkCollectionFromStart( DateTime start ) throws Exception;
    List<ViewCameraLinkObject> getViewCameraLinkCollectionUntilStart( DateTime start ) throws Exception;
    List<ViewCameraLinkObject> getViewCameraLinkCollectionOverStart( DateTime fromStart, DateTime untilStart ) throws Exception;
    // ---------------------------------------------------------------------
    // ViewTrackerLink queries
    // ---------------------------------------------------------------------
    ViewTrackerLinkObject getViewTrackerLinkById( Guid id ) throws Exception;
    List<ViewTrackerLinkObject> getViewTrackerLinkCollection( ) throws Exception;
    List<ViewTrackerLinkObject> getViewTrackerLinkCollectionByView( Guid view ) throws Exception;
    ViewTrackerLinkObject getViewTrackerLinkByViewAndStart( Guid view, DateTime start ) throws Exception;
    ViewTrackerLinkObject getViewTrackerLinkByViewAtStart( Guid view, DateTime start ) throws Exception;
    List<ViewTrackerLinkObject> getViewTrackerLinkByViewFromStart( Guid view, DateTime start ) throws Exception;
    List<ViewTrackerLinkObject> getViewTrackerLinkByViewUntilStart( Guid view, DateTime start ) throws Exception;
    List<ViewTrackerLinkObject> getViewTrackerLinkByViewOverStart( Guid view, DateTime fromStart, DateTime untilStart ) throws Exception;
    List<ViewTrackerLinkObject> getViewTrackerLinkCollectionByTracker( Guid tracker ) throws Exception;
    ViewTrackerLinkObject getViewTrackerLinkByTrackerAndStart( Guid tracker, DateTime start ) throws Exception;
    ViewTrackerLinkObject getViewTrackerLinkByTrackerAtStart( Guid tracker, DateTime start ) throws Exception;
    List<ViewTrackerLinkObject> getViewTrackerLinkByTrackerFromStart( Guid tracker, DateTime start ) throws Exception;
    List<ViewTrackerLinkObject> getViewTrackerLinkByTrackerUntilStart( Guid tracker, DateTime start ) throws Exception;
    List<ViewTrackerLinkObject> getViewTrackerLinkByTrackerOverStart( Guid tracker, DateTime fromStart, DateTime untilStart ) throws Exception;
    List<ViewTrackerLinkObject> getViewTrackerLinkCollectionByStart( DateTime start ) throws Exception;
    List<ViewTrackerLinkObject> getViewTrackerLinkCollectionAtStart( DateTime start ) throws Exception;
    List<ViewTrackerLinkObject> getViewTrackerLinkCollectionFromStart( DateTime start ) throws Exception;
    List<ViewTrackerLinkObject> getViewTrackerLinkCollectionUntilStart( DateTime start ) throws Exception;
    List<ViewTrackerLinkObject> getViewTrackerLinkCollectionOverStart( DateTime fromStart, DateTime untilStart ) throws Exception;
    // ---------------------------------------------------------------------
    // WeatherStationCommand queries
    // ---------------------------------------------------------------------
    WeatherStationCommandObject getWeatherStationCommandById( Guid id ) throws Exception;
    List<WeatherStationCommandObject> getWeatherStationCommandCollection( ) throws Exception;
    List<WeatherStationCommandObject> getWeatherStationCommandCollectionByWeatherStation( Guid weatherStation ) throws Exception;
    List<WeatherStationCommandObject> getWeatherStationCommandCollectionByWeatherStationAndTimestamp( Guid weatherStation, DateTime timestamp ) throws Exception;
    List<WeatherStationCommandObject> getWeatherStationCommandCollectionByWeatherStationAtTimestamp( Guid weatherStation, DateTime timestamp ) throws Exception;
    List<WeatherStationCommandObject> getWeatherStationCommandCollectionByWeatherStationFromTimestamp( Guid weatherStation, DateTime timestamp ) throws Exception;
    List<WeatherStationCommandObject> getWeatherStationCommandCollectionByWeatherStationUntilTimestamp( Guid weatherStation, DateTime timestamp ) throws Exception;
    List<WeatherStationCommandObject> getWeatherStationCommandCollectionByWeatherStationOverTimestamp( Guid weatherStation, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<WeatherStationCommandObject> getWeatherStationCommandCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<WeatherStationCommandObject> getWeatherStationCommandCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<WeatherStationCommandObject> getWeatherStationCommandCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<WeatherStationCommandObject> getWeatherStationCommandCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<WeatherStationCommandObject> getWeatherStationCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<WeatherStationCommandObject> getWeatherStationCommandCollectionByReply( Guid reply ) throws Exception;
    List<WeatherStationCommandObject> qetWeatherStationCommandCollectionByReplyIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // WeatherStationCommandReply queries
    // ---------------------------------------------------------------------
    WeatherStationCommandReplyObject getWeatherStationCommandReplyById( Guid id ) throws Exception;
    List<WeatherStationCommandReplyObject> getWeatherStationCommandReplyCollection( ) throws Exception;
    List<WeatherStationCommandReplyObject> getWeatherStationCommandReplyCollectionByWeatherStation( Guid weatherStation ) throws Exception;
    List<WeatherStationCommandReplyObject> getWeatherStationCommandReplyCollectionByWeatherStationAndTimestamp( Guid weatherStation, DateTime timestamp ) throws Exception;
    List<WeatherStationCommandReplyObject> getWeatherStationCommandReplyCollectionByWeatherStationAtTimestamp( Guid weatherStation, DateTime timestamp ) throws Exception;
    List<WeatherStationCommandReplyObject> getWeatherStationCommandReplyCollectionByWeatherStationFromTimestamp( Guid weatherStation, DateTime timestamp ) throws Exception;
    List<WeatherStationCommandReplyObject> getWeatherStationCommandReplyCollectionByWeatherStationUntilTimestamp( Guid weatherStation, DateTime timestamp ) throws Exception;
    List<WeatherStationCommandReplyObject> getWeatherStationCommandReplyCollectionByWeatherStationOverTimestamp( Guid weatherStation, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<WeatherStationCommandReplyObject> getWeatherStationCommandReplyCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<WeatherStationCommandReplyObject> getWeatherStationCommandReplyCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<WeatherStationCommandReplyObject> getWeatherStationCommandReplyCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<WeatherStationCommandReplyObject> getWeatherStationCommandReplyCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<WeatherStationCommandReplyObject> getWeatherStationCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    WeatherStationCommandReplyObject getWeatherStationCommandReplyByCommand( Guid command ) throws Exception;
    List<WeatherStationCommandReplyObject> qetWeatherStationCommandReplyCollectionByCommandIsNull(  ) throws Exception;
    // ---------------------------------------------------------------------
    // WeatherStationConfiguration queries
    // ---------------------------------------------------------------------
    WeatherStationConfigurationObject getWeatherStationConfigurationById( Guid id ) throws Exception;
    List<WeatherStationConfigurationObject> getWeatherStationConfigurationCollection( ) throws Exception;
    List<WeatherStationConfigurationObject> getWeatherStationConfigurationCollectionByWeatherStation( Guid weatherStation ) throws Exception;
    WeatherStationConfigurationObject getWeatherStationConfigurationByWeatherStationAndTimestamp( Guid weatherStation, DateTime timestamp ) throws Exception;
    WeatherStationConfigurationObject getWeatherStationConfigurationByWeatherStationAtTimestamp( Guid weatherStation, DateTime timestamp ) throws Exception;
    List<WeatherStationConfigurationObject> getWeatherStationConfigurationByWeatherStationFromTimestamp( Guid weatherStation, DateTime timestamp ) throws Exception;
    List<WeatherStationConfigurationObject> getWeatherStationConfigurationByWeatherStationUntilTimestamp( Guid weatherStation, DateTime timestamp ) throws Exception;
    List<WeatherStationConfigurationObject> getWeatherStationConfigurationByWeatherStationOverTimestamp( Guid weatherStation, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<WeatherStationConfigurationObject> getWeatherStationConfigurationCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<WeatherStationConfigurationObject> getWeatherStationConfigurationCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<WeatherStationConfigurationObject> getWeatherStationConfigurationCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<WeatherStationConfigurationObject> getWeatherStationConfigurationCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<WeatherStationConfigurationObject> getWeatherStationConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // Zone queries
    // ---------------------------------------------------------------------
    ZoneObject getZoneById( Guid id ) throws Exception;
    List<ZoneObject> getZoneCollection( ) throws Exception;
    ZoneObject getZoneByName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // CircularZone queries
    // ---------------------------------------------------------------------
    CircularZoneObject getCircularZoneById( Guid id ) throws Exception;
    List<CircularZoneObject> getCircularZoneCollection( ) throws Exception;
    CircularZoneObject getCircularZoneByName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // PolygonZone queries
    // ---------------------------------------------------------------------
    PolygonZoneObject getPolygonZoneById( Guid id ) throws Exception;
    List<PolygonZoneObject> getPolygonZoneCollection( ) throws Exception;
    PolygonZoneObject getPolygonZoneByName( String name ) throws Exception;
    // ---------------------------------------------------------------------
    // ZoneExceptions queries
    // ---------------------------------------------------------------------
    ZoneExceptionsObject getZoneExceptionsById( Guid id ) throws Exception;
    List<ZoneExceptionsObject> getZoneExceptionsCollection( ) throws Exception;
    List<ZoneExceptionsObject> getZoneExceptionsCollectionByZone( Guid zone ) throws Exception;
    ZoneExceptionsObject getZoneExceptionsByZoneAndTimestamp( Guid zone, DateTime timestamp ) throws Exception;
    ZoneExceptionsObject getZoneExceptionsByZoneAtTimestamp( Guid zone, DateTime timestamp ) throws Exception;
    List<ZoneExceptionsObject> getZoneExceptionsByZoneFromTimestamp( Guid zone, DateTime timestamp ) throws Exception;
    List<ZoneExceptionsObject> getZoneExceptionsByZoneUntilTimestamp( Guid zone, DateTime timestamp ) throws Exception;
    List<ZoneExceptionsObject> getZoneExceptionsByZoneOverTimestamp( Guid zone, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<ZoneExceptionsObject> getZoneExceptionsCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<ZoneExceptionsObject> getZoneExceptionsCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<ZoneExceptionsObject> getZoneExceptionsCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<ZoneExceptionsObject> getZoneExceptionsCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<ZoneExceptionsObject> getZoneExceptionsCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    // ---------------------------------------------------------------------
    // ZoneExceptionsVesselLink queries
    // ---------------------------------------------------------------------
    ZoneExceptionsVesselLinkObject getZoneExceptionsVesselLinkById( Guid id ) throws Exception;
    List<ZoneExceptionsVesselLinkObject> getZoneExceptionsVesselLinkCollection( ) throws Exception;
    List<ZoneExceptionsVesselLinkObject> getZoneExceptionsVesselLinkCollectionByZoneExceptions( Guid zoneExceptions ) throws Exception;
    ZoneExceptionsVesselLinkObject getZoneExceptionsVesselLinkByZoneExceptionsAndVessel( Guid zoneExceptions, Guid vessel ) throws Exception;
    List<ZoneExceptionsVesselLinkObject> getZoneExceptionsVesselLinkCollectionByVessel( Guid vessel ) throws Exception;
    // ---------------------------------------------------------------------
    // ZoneTrackAlarm queries
    // ---------------------------------------------------------------------
    ZoneTrackAlarmObject getZoneTrackAlarmById( Guid id ) throws Exception;
    List<ZoneTrackAlarmObject> getZoneTrackAlarmCollection( ) throws Exception;
    List<ZoneTrackAlarmObject> getZoneTrackAlarmCollectionByTrack( Guid track ) throws Exception;
    ZoneTrackAlarmObject getZoneTrackAlarmByTrackAndTimestamp( Guid track, DateTime timestamp ) throws Exception;
    ZoneTrackAlarmObject getZoneTrackAlarmByTrackAtTimestamp( Guid track, DateTime timestamp ) throws Exception;
    List<ZoneTrackAlarmObject> getZoneTrackAlarmByTrackFromTimestamp( Guid track, DateTime timestamp ) throws Exception;
    List<ZoneTrackAlarmObject> getZoneTrackAlarmByTrackUntilTimestamp( Guid track, DateTime timestamp ) throws Exception;
    List<ZoneTrackAlarmObject> getZoneTrackAlarmByTrackOverTimestamp( Guid track, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<ZoneTrackAlarmObject> getZoneTrackAlarmCollectionByZone( Guid zone ) throws Exception;
    List<ZoneTrackAlarmObject> getZoneTrackAlarmCollectionByZoneAndTrack( Guid zone, Guid track ) throws Exception;
    ZoneTrackAlarmObject getZoneTrackAlarmByZoneTrackAndTimestamp( Guid zone, Guid track, DateTime timestamp ) throws Exception;
    ZoneTrackAlarmObject getZoneTrackAlarmByZoneTrackAtTimestamp( Guid zone, Guid track, DateTime timestamp ) throws Exception;
    List<ZoneTrackAlarmObject> getZoneTrackAlarmByZoneTrackFromTimestamp( Guid zone, Guid track, DateTime timestamp ) throws Exception;
    List<ZoneTrackAlarmObject> getZoneTrackAlarmByZoneTrackUntilTimestamp( Guid zone, Guid track, DateTime timestamp ) throws Exception;
    List<ZoneTrackAlarmObject> getZoneTrackAlarmByZoneTrackOverTimestamp( Guid zone, Guid track, DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
    List<ZoneTrackAlarmObject> getZoneTrackAlarmCollectionByTimestamp( DateTime timestamp ) throws Exception;
    List<ZoneTrackAlarmObject> getZoneTrackAlarmCollectionAtTimestamp( DateTime timestamp ) throws Exception;
    List<ZoneTrackAlarmObject> getZoneTrackAlarmCollectionFromTimestamp( DateTime timestamp ) throws Exception;
    List<ZoneTrackAlarmObject> getZoneTrackAlarmCollectionUntilTimestamp( DateTime timestamp ) throws Exception;
    List<ZoneTrackAlarmObject> getZoneTrackAlarmCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp ) throws Exception;
}
