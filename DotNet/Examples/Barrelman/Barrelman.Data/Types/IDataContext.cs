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
using System;
using System.Diagnostics.CodeAnalysis;
using System.IO;

using Harlinn.Common.Core.Net;
using Harlinn.Common.Core.Net.Data;
using Harlinn.Common.Core.Net.IO;
namespace Barrelman.Data.Types
{
    public interface IDataContext : IDataContextBase<Kind>
    {
        // ---------------------------------------------------------------------
        // AircraftType queries
        // ---------------------------------------------------------------------
        AircraftTypeObject? GetAircraftTypeById( Guid id );
        IList<AircraftTypeObject> GetAircraftTypeCollection( );
        AircraftTypeObject? GetAircraftTypeByName( string name );
        // ---------------------------------------------------------------------
        // AisDeviceCommand queries
        // ---------------------------------------------------------------------
        AisDeviceCommandObject? GetAisDeviceCommandById( Guid id );
        IList<AisDeviceCommandObject> GetAisDeviceCommandCollection( );
        IList<AisDeviceCommandObject> GetAisDeviceCommandCollectionByAisDevice( Guid aisDevice );
        IList<AisDeviceCommandObject> GetAisDeviceCommandCollectionByAisDeviceAndTimestamp( Guid aisDevice, DateTime timestamp );
        IList<AisDeviceCommandObject> GetAisDeviceCommandCollectionByAisDeviceAtTimestamp( Guid aisDevice, DateTime timestamp );
        IList<AisDeviceCommandObject> GetAisDeviceCommandCollectionByAisDeviceFromTimestamp( Guid aisDevice, DateTime timestamp );
        IList<AisDeviceCommandObject> GetAisDeviceCommandCollectionByAisDeviceUntilTimestamp( Guid aisDevice, DateTime timestamp );
        IList<AisDeviceCommandObject> GetAisDeviceCommandCollectionByAisDeviceOverTimestamp( Guid aisDevice, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<AisDeviceCommandObject> GetAisDeviceCommandCollectionByTimestamp( DateTime timestamp );
        IList<AisDeviceCommandObject> GetAisDeviceCommandCollectionAtTimestamp( DateTime timestamp );
        IList<AisDeviceCommandObject> GetAisDeviceCommandCollectionFromTimestamp( DateTime timestamp );
        IList<AisDeviceCommandObject> GetAisDeviceCommandCollectionUntilTimestamp( DateTime timestamp );
        IList<AisDeviceCommandObject> GetAisDeviceCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<AisDeviceCommandObject> GetAisDeviceCommandCollectionByReply( Guid? reply );
        IList<AisDeviceCommandObject> GetAisDeviceCommandCollectionByReplyIsNull(  );
        // ---------------------------------------------------------------------
        // AisDeviceCommandReply queries
        // ---------------------------------------------------------------------
        AisDeviceCommandReplyObject? GetAisDeviceCommandReplyById( Guid id );
        IList<AisDeviceCommandReplyObject> GetAisDeviceCommandReplyCollection( );
        IList<AisDeviceCommandReplyObject> GetAisDeviceCommandReplyCollectionByAisDevice( Guid aisDevice );
        IList<AisDeviceCommandReplyObject> GetAisDeviceCommandReplyCollectionByAisDeviceAndTimestamp( Guid aisDevice, DateTime timestamp );
        IList<AisDeviceCommandReplyObject> GetAisDeviceCommandReplyCollectionByAisDeviceAtTimestamp( Guid aisDevice, DateTime timestamp );
        IList<AisDeviceCommandReplyObject> GetAisDeviceCommandReplyCollectionByAisDeviceFromTimestamp( Guid aisDevice, DateTime timestamp );
        IList<AisDeviceCommandReplyObject> GetAisDeviceCommandReplyCollectionByAisDeviceUntilTimestamp( Guid aisDevice, DateTime timestamp );
        IList<AisDeviceCommandReplyObject> GetAisDeviceCommandReplyCollectionByAisDeviceOverTimestamp( Guid aisDevice, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<AisDeviceCommandReplyObject> GetAisDeviceCommandReplyCollectionByTimestamp( DateTime timestamp );
        IList<AisDeviceCommandReplyObject> GetAisDeviceCommandReplyCollectionAtTimestamp( DateTime timestamp );
        IList<AisDeviceCommandReplyObject> GetAisDeviceCommandReplyCollectionFromTimestamp( DateTime timestamp );
        IList<AisDeviceCommandReplyObject> GetAisDeviceCommandReplyCollectionUntilTimestamp( DateTime timestamp );
        IList<AisDeviceCommandReplyObject> GetAisDeviceCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        AisDeviceCommandReplyObject? GetAisDeviceCommandReplyByCommand( Guid? command );
        IList<AisDeviceCommandReplyObject> GetAisDeviceCommandReplyCollectionByCommandIsNull(  );
        // ---------------------------------------------------------------------
        // AisDeviceConfiguration queries
        // ---------------------------------------------------------------------
        AisDeviceConfigurationObject? GetAisDeviceConfigurationById( Guid id );
        IList<AisDeviceConfigurationObject> GetAisDeviceConfigurationCollection( );
        IList<AisDeviceConfigurationObject> GetAisDeviceConfigurationCollectionByAisDevice( Guid aisDevice );
        AisDeviceConfigurationObject? GetAisDeviceConfigurationByAisDeviceAndTimestamp( Guid aisDevice, DateTime timestamp );
        AisDeviceConfigurationObject? GetAisDeviceConfigurationByAisDeviceAtTimestamp( Guid aisDevice, DateTime timestamp );
        IList<AisDeviceConfigurationObject> GetAisDeviceConfigurationByAisDeviceFromTimestamp( Guid aisDevice, DateTime timestamp );
        IList<AisDeviceConfigurationObject> GetAisDeviceConfigurationByAisDeviceUntilTimestamp( Guid aisDevice, DateTime timestamp );
        IList<AisDeviceConfigurationObject> GetAisDeviceConfigurationByAisDeviceOverTimestamp( Guid aisDevice, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<AisDeviceConfigurationObject> GetAisDeviceConfigurationCollectionByTimestamp( DateTime timestamp );
        IList<AisDeviceConfigurationObject> GetAisDeviceConfigurationCollectionAtTimestamp( DateTime timestamp );
        IList<AisDeviceConfigurationObject> GetAisDeviceConfigurationCollectionFromTimestamp( DateTime timestamp );
        IList<AisDeviceConfigurationObject> GetAisDeviceConfigurationCollectionUntilTimestamp( DateTime timestamp );
        IList<AisDeviceConfigurationObject> GetAisDeviceConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // AisDeviceRawMessage queries
        // ---------------------------------------------------------------------
        AisDeviceRawMessageObject? GetAisDeviceRawMessageById( Guid id );
        IList<AisDeviceRawMessageObject> GetAisDeviceRawMessageCollection( );
        IList<AisDeviceRawMessageObject> GetAisDeviceRawMessageCollectionByAisDevice( Guid aisDevice );
        IList<AisDeviceRawMessageObject> GetAisDeviceRawMessageCollectionByAisDeviceAndTimestamp( Guid aisDevice, DateTime timestamp );
        IList<AisDeviceRawMessageObject> GetAisDeviceRawMessageCollectionByAisDeviceAtTimestamp( Guid aisDevice, DateTime timestamp );
        IList<AisDeviceRawMessageObject> GetAisDeviceRawMessageCollectionByAisDeviceFromTimestamp( Guid aisDevice, DateTime timestamp );
        IList<AisDeviceRawMessageObject> GetAisDeviceRawMessageCollectionByAisDeviceUntilTimestamp( Guid aisDevice, DateTime timestamp );
        IList<AisDeviceRawMessageObject> GetAisDeviceRawMessageCollectionByAisDeviceOverTimestamp( Guid aisDevice, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<AisDeviceRawMessageObject> GetAisDeviceRawMessageCollectionByTimestamp( DateTime timestamp );
        IList<AisDeviceRawMessageObject> GetAisDeviceRawMessageCollectionAtTimestamp( DateTime timestamp );
        IList<AisDeviceRawMessageObject> GetAisDeviceRawMessageCollectionFromTimestamp( DateTime timestamp );
        IList<AisDeviceRawMessageObject> GetAisDeviceRawMessageCollectionUntilTimestamp( DateTime timestamp );
        IList<AisDeviceRawMessageObject> GetAisDeviceRawMessageCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // AisDeviceRawSentence queries
        // ---------------------------------------------------------------------
        AisDeviceRawSentenceObject? GetAisDeviceRawSentenceById( Guid id );
        IList<AisDeviceRawSentenceObject> GetAisDeviceRawSentenceCollection( );
        IList<AisDeviceRawSentenceObject> GetAisDeviceRawSentenceCollectionByAisDevice( Guid aisDevice );
        IList<AisDeviceRawSentenceObject> GetAisDeviceRawSentenceCollectionByAisDeviceAndTimestamp( Guid aisDevice, DateTime timestamp );
        IList<AisDeviceRawSentenceObject> GetAisDeviceRawSentenceCollectionByAisDeviceAtTimestamp( Guid aisDevice, DateTime timestamp );
        IList<AisDeviceRawSentenceObject> GetAisDeviceRawSentenceCollectionByAisDeviceFromTimestamp( Guid aisDevice, DateTime timestamp );
        IList<AisDeviceRawSentenceObject> GetAisDeviceRawSentenceCollectionByAisDeviceUntilTimestamp( Guid aisDevice, DateTime timestamp );
        IList<AisDeviceRawSentenceObject> GetAisDeviceRawSentenceCollectionByAisDeviceOverTimestamp( Guid aisDevice, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<AisDeviceRawSentenceObject> GetAisDeviceRawSentenceCollectionByTimestamp( DateTime timestamp );
        IList<AisDeviceRawSentenceObject> GetAisDeviceRawSentenceCollectionAtTimestamp( DateTime timestamp );
        IList<AisDeviceRawSentenceObject> GetAisDeviceRawSentenceCollectionFromTimestamp( DateTime timestamp );
        IList<AisDeviceRawSentenceObject> GetAisDeviceRawSentenceCollectionUntilTimestamp( DateTime timestamp );
        IList<AisDeviceRawSentenceObject> GetAisDeviceRawSentenceCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // AisMessage queries
        // ---------------------------------------------------------------------
        AisMessageObject? GetAisMessageById( Guid id );
        IList<AisMessageObject> GetAisMessageCollection( );
        IList<AisMessageObject> GetAisMessageCollectionByAisDevice( Guid aisDevice );
        AisMessageObject? GetAisMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        AisMessageObject? GetAisMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisMessageObject> GetAisMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisMessageObject> GetAisMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisMessageObject> GetAisMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisMessageObject> GetAisMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisMessageObject> GetAisMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisMessageObject> GetAisMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisMessageObject> GetAisMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisMessageObject> GetAisMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisMessageObject> GetAisMessageCollectionByMmsi( Guid? mmsi );
        IList<AisMessageObject> GetAisMessageCollectionByMmsiIsNull(  );
        IList<AisMessageObject> GetAisMessageCollectionByMmsiAndMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisMessageObject> GetAisMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
        IList<AisMessageObject> GetAisMessageCollectionByMmsiFromMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisMessageObject> GetAisMessageCollectionByMmsiUntilMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisMessageObject> GetAisMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
        // ---------------------------------------------------------------------
        // AidToNavigationReportMessage queries
        // ---------------------------------------------------------------------
        AidToNavigationReportMessageObject? GetAidToNavigationReportMessageById( Guid id );
        IList<AidToNavigationReportMessageObject> GetAidToNavigationReportMessageCollection( );
        IList<AidToNavigationReportMessageObject> GetAidToNavigationReportMessageCollectionByAisDevice( Guid aisDevice );
        AidToNavigationReportMessageObject? GetAidToNavigationReportMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        AidToNavigationReportMessageObject? GetAidToNavigationReportMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AidToNavigationReportMessageObject> GetAidToNavigationReportMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AidToNavigationReportMessageObject> GetAidToNavigationReportMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AidToNavigationReportMessageObject> GetAidToNavigationReportMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AidToNavigationReportMessageObject> GetAidToNavigationReportMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
        IList<AidToNavigationReportMessageObject> GetAidToNavigationReportMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
        IList<AidToNavigationReportMessageObject> GetAidToNavigationReportMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
        IList<AidToNavigationReportMessageObject> GetAidToNavigationReportMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
        IList<AidToNavigationReportMessageObject> GetAidToNavigationReportMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AidToNavigationReportMessageObject> GetAidToNavigationReportMessageCollectionByMmsi( Guid? mmsi );
        IList<AidToNavigationReportMessageObject> GetAidToNavigationReportMessageCollectionByMmsiIsNull(  );
        IList<AidToNavigationReportMessageObject> GetAidToNavigationReportMessageCollectionByMmsiAndMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AidToNavigationReportMessageObject> GetAidToNavigationReportMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
        IList<AidToNavigationReportMessageObject> GetAidToNavigationReportMessageCollectionByMmsiFromMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AidToNavigationReportMessageObject> GetAidToNavigationReportMessageCollectionByMmsiUntilMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AidToNavigationReportMessageObject> GetAidToNavigationReportMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
        // ---------------------------------------------------------------------
        // AisAddressedSafetyRelatedMessage queries
        // ---------------------------------------------------------------------
        AisAddressedSafetyRelatedMessageObject? GetAisAddressedSafetyRelatedMessageById( Guid id );
        IList<AisAddressedSafetyRelatedMessageObject> GetAisAddressedSafetyRelatedMessageCollection( );
        IList<AisAddressedSafetyRelatedMessageObject> GetAisAddressedSafetyRelatedMessageCollectionByAisDevice( Guid aisDevice );
        AisAddressedSafetyRelatedMessageObject? GetAisAddressedSafetyRelatedMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        AisAddressedSafetyRelatedMessageObject? GetAisAddressedSafetyRelatedMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisAddressedSafetyRelatedMessageObject> GetAisAddressedSafetyRelatedMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisAddressedSafetyRelatedMessageObject> GetAisAddressedSafetyRelatedMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisAddressedSafetyRelatedMessageObject> GetAisAddressedSafetyRelatedMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisAddressedSafetyRelatedMessageObject> GetAisAddressedSafetyRelatedMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisAddressedSafetyRelatedMessageObject> GetAisAddressedSafetyRelatedMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisAddressedSafetyRelatedMessageObject> GetAisAddressedSafetyRelatedMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisAddressedSafetyRelatedMessageObject> GetAisAddressedSafetyRelatedMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisAddressedSafetyRelatedMessageObject> GetAisAddressedSafetyRelatedMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisAddressedSafetyRelatedMessageObject> GetAisAddressedSafetyRelatedMessageCollectionByMmsi( Guid? mmsi );
        IList<AisAddressedSafetyRelatedMessageObject> GetAisAddressedSafetyRelatedMessageCollectionByMmsiIsNull(  );
        IList<AisAddressedSafetyRelatedMessageObject> GetAisAddressedSafetyRelatedMessageCollectionByMmsiAndMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisAddressedSafetyRelatedMessageObject> GetAisAddressedSafetyRelatedMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
        IList<AisAddressedSafetyRelatedMessageObject> GetAisAddressedSafetyRelatedMessageCollectionByMmsiFromMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisAddressedSafetyRelatedMessageObject> GetAisAddressedSafetyRelatedMessageCollectionByMmsiUntilMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisAddressedSafetyRelatedMessageObject> GetAisAddressedSafetyRelatedMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
        IList<AisAddressedSafetyRelatedMessageObject> GetAisAddressedSafetyRelatedMessageCollectionByDestinationMmsi( Guid? destinationMmsi );
        IList<AisAddressedSafetyRelatedMessageObject> GetAisAddressedSafetyRelatedMessageCollectionByDestinationMmsiIsNull(  );
        // ---------------------------------------------------------------------
        // AisBaseStationReportMessage queries
        // ---------------------------------------------------------------------
        AisBaseStationReportMessageObject? GetAisBaseStationReportMessageById( Guid id );
        IList<AisBaseStationReportMessageObject> GetAisBaseStationReportMessageCollection( );
        IList<AisBaseStationReportMessageObject> GetAisBaseStationReportMessageCollectionByAisDevice( Guid aisDevice );
        AisBaseStationReportMessageObject? GetAisBaseStationReportMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        AisBaseStationReportMessageObject? GetAisBaseStationReportMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisBaseStationReportMessageObject> GetAisBaseStationReportMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisBaseStationReportMessageObject> GetAisBaseStationReportMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisBaseStationReportMessageObject> GetAisBaseStationReportMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisBaseStationReportMessageObject> GetAisBaseStationReportMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisBaseStationReportMessageObject> GetAisBaseStationReportMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisBaseStationReportMessageObject> GetAisBaseStationReportMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisBaseStationReportMessageObject> GetAisBaseStationReportMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisBaseStationReportMessageObject> GetAisBaseStationReportMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisBaseStationReportMessageObject> GetAisBaseStationReportMessageCollectionByMmsi( Guid? mmsi );
        IList<AisBaseStationReportMessageObject> GetAisBaseStationReportMessageCollectionByMmsiIsNull(  );
        IList<AisBaseStationReportMessageObject> GetAisBaseStationReportMessageCollectionByMmsiAndMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisBaseStationReportMessageObject> GetAisBaseStationReportMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
        IList<AisBaseStationReportMessageObject> GetAisBaseStationReportMessageCollectionByMmsiFromMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisBaseStationReportMessageObject> GetAisBaseStationReportMessageCollectionByMmsiUntilMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisBaseStationReportMessageObject> GetAisBaseStationReportMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
        // ---------------------------------------------------------------------
        // AisBinaryAcknowledgeMessage queries
        // ---------------------------------------------------------------------
        AisBinaryAcknowledgeMessageObject? GetAisBinaryAcknowledgeMessageById( Guid id );
        IList<AisBinaryAcknowledgeMessageObject> GetAisBinaryAcknowledgeMessageCollection( );
        IList<AisBinaryAcknowledgeMessageObject> GetAisBinaryAcknowledgeMessageCollectionByAisDevice( Guid aisDevice );
        AisBinaryAcknowledgeMessageObject? GetAisBinaryAcknowledgeMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        AisBinaryAcknowledgeMessageObject? GetAisBinaryAcknowledgeMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisBinaryAcknowledgeMessageObject> GetAisBinaryAcknowledgeMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisBinaryAcknowledgeMessageObject> GetAisBinaryAcknowledgeMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisBinaryAcknowledgeMessageObject> GetAisBinaryAcknowledgeMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisBinaryAcknowledgeMessageObject> GetAisBinaryAcknowledgeMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisBinaryAcknowledgeMessageObject> GetAisBinaryAcknowledgeMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisBinaryAcknowledgeMessageObject> GetAisBinaryAcknowledgeMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisBinaryAcknowledgeMessageObject> GetAisBinaryAcknowledgeMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisBinaryAcknowledgeMessageObject> GetAisBinaryAcknowledgeMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisBinaryAcknowledgeMessageObject> GetAisBinaryAcknowledgeMessageCollectionByMmsi( Guid? mmsi );
        IList<AisBinaryAcknowledgeMessageObject> GetAisBinaryAcknowledgeMessageCollectionByMmsiIsNull(  );
        IList<AisBinaryAcknowledgeMessageObject> GetAisBinaryAcknowledgeMessageCollectionByMmsiAndMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisBinaryAcknowledgeMessageObject> GetAisBinaryAcknowledgeMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
        IList<AisBinaryAcknowledgeMessageObject> GetAisBinaryAcknowledgeMessageCollectionByMmsiFromMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisBinaryAcknowledgeMessageObject> GetAisBinaryAcknowledgeMessageCollectionByMmsiUntilMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisBinaryAcknowledgeMessageObject> GetAisBinaryAcknowledgeMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
        // ---------------------------------------------------------------------
        // AisBinaryAddressedMessage queries
        // ---------------------------------------------------------------------
        AisBinaryAddressedMessageObject? GetAisBinaryAddressedMessageById( Guid id );
        IList<AisBinaryAddressedMessageObject> GetAisBinaryAddressedMessageCollection( );
        IList<AisBinaryAddressedMessageObject> GetAisBinaryAddressedMessageCollectionByAisDevice( Guid aisDevice );
        AisBinaryAddressedMessageObject? GetAisBinaryAddressedMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        AisBinaryAddressedMessageObject? GetAisBinaryAddressedMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisBinaryAddressedMessageObject> GetAisBinaryAddressedMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisBinaryAddressedMessageObject> GetAisBinaryAddressedMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisBinaryAddressedMessageObject> GetAisBinaryAddressedMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisBinaryAddressedMessageObject> GetAisBinaryAddressedMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisBinaryAddressedMessageObject> GetAisBinaryAddressedMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisBinaryAddressedMessageObject> GetAisBinaryAddressedMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisBinaryAddressedMessageObject> GetAisBinaryAddressedMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisBinaryAddressedMessageObject> GetAisBinaryAddressedMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisBinaryAddressedMessageObject> GetAisBinaryAddressedMessageCollectionByMmsi( Guid? mmsi );
        IList<AisBinaryAddressedMessageObject> GetAisBinaryAddressedMessageCollectionByMmsiIsNull(  );
        IList<AisBinaryAddressedMessageObject> GetAisBinaryAddressedMessageCollectionByMmsiAndMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisBinaryAddressedMessageObject> GetAisBinaryAddressedMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
        IList<AisBinaryAddressedMessageObject> GetAisBinaryAddressedMessageCollectionByMmsiFromMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisBinaryAddressedMessageObject> GetAisBinaryAddressedMessageCollectionByMmsiUntilMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisBinaryAddressedMessageObject> GetAisBinaryAddressedMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
        IList<AisBinaryAddressedMessageObject> GetAisBinaryAddressedMessageCollectionByDestinationMmsi( Guid? destinationMmsi );
        IList<AisBinaryAddressedMessageObject> GetAisBinaryAddressedMessageCollectionByDestinationMmsiIsNull(  );
        // ---------------------------------------------------------------------
        // AisBinaryBroadcastMessage queries
        // ---------------------------------------------------------------------
        AisBinaryBroadcastMessageObject? GetAisBinaryBroadcastMessageById( Guid id );
        IList<AisBinaryBroadcastMessageObject> GetAisBinaryBroadcastMessageCollection( );
        IList<AisBinaryBroadcastMessageObject> GetAisBinaryBroadcastMessageCollectionByAisDevice( Guid aisDevice );
        AisBinaryBroadcastMessageObject? GetAisBinaryBroadcastMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        AisBinaryBroadcastMessageObject? GetAisBinaryBroadcastMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisBinaryBroadcastMessageObject> GetAisBinaryBroadcastMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisBinaryBroadcastMessageObject> GetAisBinaryBroadcastMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisBinaryBroadcastMessageObject> GetAisBinaryBroadcastMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisBinaryBroadcastMessageObject> GetAisBinaryBroadcastMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisBinaryBroadcastMessageObject> GetAisBinaryBroadcastMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisBinaryBroadcastMessageObject> GetAisBinaryBroadcastMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisBinaryBroadcastMessageObject> GetAisBinaryBroadcastMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisBinaryBroadcastMessageObject> GetAisBinaryBroadcastMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisBinaryBroadcastMessageObject> GetAisBinaryBroadcastMessageCollectionByMmsi( Guid? mmsi );
        IList<AisBinaryBroadcastMessageObject> GetAisBinaryBroadcastMessageCollectionByMmsiIsNull(  );
        IList<AisBinaryBroadcastMessageObject> GetAisBinaryBroadcastMessageCollectionByMmsiAndMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisBinaryBroadcastMessageObject> GetAisBinaryBroadcastMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
        IList<AisBinaryBroadcastMessageObject> GetAisBinaryBroadcastMessageCollectionByMmsiFromMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisBinaryBroadcastMessageObject> GetAisBinaryBroadcastMessageCollectionByMmsiUntilMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisBinaryBroadcastMessageObject> GetAisBinaryBroadcastMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
        // ---------------------------------------------------------------------
        // AisDataLinkManagementMessage queries
        // ---------------------------------------------------------------------
        AisDataLinkManagementMessageObject? GetAisDataLinkManagementMessageById( Guid id );
        IList<AisDataLinkManagementMessageObject> GetAisDataLinkManagementMessageCollection( );
        IList<AisDataLinkManagementMessageObject> GetAisDataLinkManagementMessageCollectionByAisDevice( Guid aisDevice );
        AisDataLinkManagementMessageObject? GetAisDataLinkManagementMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        AisDataLinkManagementMessageObject? GetAisDataLinkManagementMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisDataLinkManagementMessageObject> GetAisDataLinkManagementMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisDataLinkManagementMessageObject> GetAisDataLinkManagementMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisDataLinkManagementMessageObject> GetAisDataLinkManagementMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisDataLinkManagementMessageObject> GetAisDataLinkManagementMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisDataLinkManagementMessageObject> GetAisDataLinkManagementMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisDataLinkManagementMessageObject> GetAisDataLinkManagementMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisDataLinkManagementMessageObject> GetAisDataLinkManagementMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisDataLinkManagementMessageObject> GetAisDataLinkManagementMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisDataLinkManagementMessageObject> GetAisDataLinkManagementMessageCollectionByMmsi( Guid? mmsi );
        IList<AisDataLinkManagementMessageObject> GetAisDataLinkManagementMessageCollectionByMmsiIsNull(  );
        IList<AisDataLinkManagementMessageObject> GetAisDataLinkManagementMessageCollectionByMmsiAndMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisDataLinkManagementMessageObject> GetAisDataLinkManagementMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
        IList<AisDataLinkManagementMessageObject> GetAisDataLinkManagementMessageCollectionByMmsiFromMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisDataLinkManagementMessageObject> GetAisDataLinkManagementMessageCollectionByMmsiUntilMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisDataLinkManagementMessageObject> GetAisDataLinkManagementMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
        // ---------------------------------------------------------------------
        // AisExtendedClassBCsPositionReportMessage queries
        // ---------------------------------------------------------------------
        AisExtendedClassBCsPositionReportMessageObject? GetAisExtendedClassBCsPositionReportMessageById( Guid id );
        IList<AisExtendedClassBCsPositionReportMessageObject> GetAisExtendedClassBCsPositionReportMessageCollection( );
        IList<AisExtendedClassBCsPositionReportMessageObject> GetAisExtendedClassBCsPositionReportMessageCollectionByAisDevice( Guid aisDevice );
        AisExtendedClassBCsPositionReportMessageObject? GetAisExtendedClassBCsPositionReportMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        AisExtendedClassBCsPositionReportMessageObject? GetAisExtendedClassBCsPositionReportMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisExtendedClassBCsPositionReportMessageObject> GetAisExtendedClassBCsPositionReportMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisExtendedClassBCsPositionReportMessageObject> GetAisExtendedClassBCsPositionReportMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisExtendedClassBCsPositionReportMessageObject> GetAisExtendedClassBCsPositionReportMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisExtendedClassBCsPositionReportMessageObject> GetAisExtendedClassBCsPositionReportMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisExtendedClassBCsPositionReportMessageObject> GetAisExtendedClassBCsPositionReportMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisExtendedClassBCsPositionReportMessageObject> GetAisExtendedClassBCsPositionReportMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisExtendedClassBCsPositionReportMessageObject> GetAisExtendedClassBCsPositionReportMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisExtendedClassBCsPositionReportMessageObject> GetAisExtendedClassBCsPositionReportMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisExtendedClassBCsPositionReportMessageObject> GetAisExtendedClassBCsPositionReportMessageCollectionByMmsi( Guid? mmsi );
        IList<AisExtendedClassBCsPositionReportMessageObject> GetAisExtendedClassBCsPositionReportMessageCollectionByMmsiIsNull(  );
        IList<AisExtendedClassBCsPositionReportMessageObject> GetAisExtendedClassBCsPositionReportMessageCollectionByMmsiAndMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisExtendedClassBCsPositionReportMessageObject> GetAisExtendedClassBCsPositionReportMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
        IList<AisExtendedClassBCsPositionReportMessageObject> GetAisExtendedClassBCsPositionReportMessageCollectionByMmsiFromMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisExtendedClassBCsPositionReportMessageObject> GetAisExtendedClassBCsPositionReportMessageCollectionByMmsiUntilMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisExtendedClassBCsPositionReportMessageObject> GetAisExtendedClassBCsPositionReportMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
        IList<AisExtendedClassBCsPositionReportMessageObject> GetAisExtendedClassBCsPositionReportMessageCollectionByName( Guid? name );
        IList<AisExtendedClassBCsPositionReportMessageObject> GetAisExtendedClassBCsPositionReportMessageCollectionByNameIsNull(  );
        // ---------------------------------------------------------------------
        // AisInterrogationMessage queries
        // ---------------------------------------------------------------------
        AisInterrogationMessageObject? GetAisInterrogationMessageById( Guid id );
        IList<AisInterrogationMessageObject> GetAisInterrogationMessageCollection( );
        IList<AisInterrogationMessageObject> GetAisInterrogationMessageCollectionByAisDevice( Guid aisDevice );
        AisInterrogationMessageObject? GetAisInterrogationMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        AisInterrogationMessageObject? GetAisInterrogationMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisInterrogationMessageObject> GetAisInterrogationMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisInterrogationMessageObject> GetAisInterrogationMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisInterrogationMessageObject> GetAisInterrogationMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisInterrogationMessageObject> GetAisInterrogationMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisInterrogationMessageObject> GetAisInterrogationMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisInterrogationMessageObject> GetAisInterrogationMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisInterrogationMessageObject> GetAisInterrogationMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisInterrogationMessageObject> GetAisInterrogationMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisInterrogationMessageObject> GetAisInterrogationMessageCollectionByMmsi( Guid? mmsi );
        IList<AisInterrogationMessageObject> GetAisInterrogationMessageCollectionByMmsiIsNull(  );
        IList<AisInterrogationMessageObject> GetAisInterrogationMessageCollectionByMmsiAndMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisInterrogationMessageObject> GetAisInterrogationMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
        IList<AisInterrogationMessageObject> GetAisInterrogationMessageCollectionByMmsiFromMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisInterrogationMessageObject> GetAisInterrogationMessageCollectionByMmsiUntilMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisInterrogationMessageObject> GetAisInterrogationMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
        // ---------------------------------------------------------------------
        // AisPositionReportClassAMessageBase queries
        // ---------------------------------------------------------------------
        AisPositionReportClassAMessageBaseObject? GetAisPositionReportClassAMessageBaseById( Guid id );
        IList<AisPositionReportClassAMessageBaseObject> GetAisPositionReportClassAMessageBaseCollection( );
        IList<AisPositionReportClassAMessageBaseObject> GetAisPositionReportClassAMessageBaseCollectionByAisDevice( Guid aisDevice );
        AisPositionReportClassAMessageBaseObject? GetAisPositionReportClassAMessageBaseByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        AisPositionReportClassAMessageBaseObject? GetAisPositionReportClassAMessageBaseByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisPositionReportClassAMessageBaseObject> GetAisPositionReportClassAMessageBaseByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisPositionReportClassAMessageBaseObject> GetAisPositionReportClassAMessageBaseByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisPositionReportClassAMessageBaseObject> GetAisPositionReportClassAMessageBaseByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisPositionReportClassAMessageBaseObject> GetAisPositionReportClassAMessageBaseCollectionByReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisPositionReportClassAMessageBaseObject> GetAisPositionReportClassAMessageBaseCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisPositionReportClassAMessageBaseObject> GetAisPositionReportClassAMessageBaseCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisPositionReportClassAMessageBaseObject> GetAisPositionReportClassAMessageBaseCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisPositionReportClassAMessageBaseObject> GetAisPositionReportClassAMessageBaseCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisPositionReportClassAMessageBaseObject> GetAisPositionReportClassAMessageBaseCollectionByMmsi( Guid? mmsi );
        IList<AisPositionReportClassAMessageBaseObject> GetAisPositionReportClassAMessageBaseCollectionByMmsiIsNull(  );
        IList<AisPositionReportClassAMessageBaseObject> GetAisPositionReportClassAMessageBaseCollectionByMmsiAndMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisPositionReportClassAMessageBaseObject> GetAisPositionReportClassAMessageBaseCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
        IList<AisPositionReportClassAMessageBaseObject> GetAisPositionReportClassAMessageBaseCollectionByMmsiFromMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisPositionReportClassAMessageBaseObject> GetAisPositionReportClassAMessageBaseCollectionByMmsiUntilMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisPositionReportClassAMessageBaseObject> GetAisPositionReportClassAMessageBaseCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
        // ---------------------------------------------------------------------
        // AisPositionReportClassAAssignedScheduleMessage queries
        // ---------------------------------------------------------------------
        AisPositionReportClassAAssignedScheduleMessageObject? GetAisPositionReportClassAAssignedScheduleMessageById( Guid id );
        IList<AisPositionReportClassAAssignedScheduleMessageObject> GetAisPositionReportClassAAssignedScheduleMessageCollection( );
        IList<AisPositionReportClassAAssignedScheduleMessageObject> GetAisPositionReportClassAAssignedScheduleMessageCollectionByAisDevice( Guid aisDevice );
        AisPositionReportClassAAssignedScheduleMessageObject? GetAisPositionReportClassAAssignedScheduleMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        AisPositionReportClassAAssignedScheduleMessageObject? GetAisPositionReportClassAAssignedScheduleMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisPositionReportClassAAssignedScheduleMessageObject> GetAisPositionReportClassAAssignedScheduleMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisPositionReportClassAAssignedScheduleMessageObject> GetAisPositionReportClassAAssignedScheduleMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisPositionReportClassAAssignedScheduleMessageObject> GetAisPositionReportClassAAssignedScheduleMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisPositionReportClassAAssignedScheduleMessageObject> GetAisPositionReportClassAAssignedScheduleMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisPositionReportClassAAssignedScheduleMessageObject> GetAisPositionReportClassAAssignedScheduleMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisPositionReportClassAAssignedScheduleMessageObject> GetAisPositionReportClassAAssignedScheduleMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisPositionReportClassAAssignedScheduleMessageObject> GetAisPositionReportClassAAssignedScheduleMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisPositionReportClassAAssignedScheduleMessageObject> GetAisPositionReportClassAAssignedScheduleMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisPositionReportClassAAssignedScheduleMessageObject> GetAisPositionReportClassAAssignedScheduleMessageCollectionByMmsi( Guid? mmsi );
        IList<AisPositionReportClassAAssignedScheduleMessageObject> GetAisPositionReportClassAAssignedScheduleMessageCollectionByMmsiIsNull(  );
        IList<AisPositionReportClassAAssignedScheduleMessageObject> GetAisPositionReportClassAAssignedScheduleMessageCollectionByMmsiAndMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisPositionReportClassAAssignedScheduleMessageObject> GetAisPositionReportClassAAssignedScheduleMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
        IList<AisPositionReportClassAAssignedScheduleMessageObject> GetAisPositionReportClassAAssignedScheduleMessageCollectionByMmsiFromMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisPositionReportClassAAssignedScheduleMessageObject> GetAisPositionReportClassAAssignedScheduleMessageCollectionByMmsiUntilMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisPositionReportClassAAssignedScheduleMessageObject> GetAisPositionReportClassAAssignedScheduleMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
        // ---------------------------------------------------------------------
        // AisPositionReportClassAMessage queries
        // ---------------------------------------------------------------------
        AisPositionReportClassAMessageObject? GetAisPositionReportClassAMessageById( Guid id );
        IList<AisPositionReportClassAMessageObject> GetAisPositionReportClassAMessageCollection( );
        IList<AisPositionReportClassAMessageObject> GetAisPositionReportClassAMessageCollectionByAisDevice( Guid aisDevice );
        AisPositionReportClassAMessageObject? GetAisPositionReportClassAMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        AisPositionReportClassAMessageObject? GetAisPositionReportClassAMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisPositionReportClassAMessageObject> GetAisPositionReportClassAMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisPositionReportClassAMessageObject> GetAisPositionReportClassAMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisPositionReportClassAMessageObject> GetAisPositionReportClassAMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisPositionReportClassAMessageObject> GetAisPositionReportClassAMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisPositionReportClassAMessageObject> GetAisPositionReportClassAMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisPositionReportClassAMessageObject> GetAisPositionReportClassAMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisPositionReportClassAMessageObject> GetAisPositionReportClassAMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisPositionReportClassAMessageObject> GetAisPositionReportClassAMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisPositionReportClassAMessageObject> GetAisPositionReportClassAMessageCollectionByMmsi( Guid? mmsi );
        IList<AisPositionReportClassAMessageObject> GetAisPositionReportClassAMessageCollectionByMmsiIsNull(  );
        IList<AisPositionReportClassAMessageObject> GetAisPositionReportClassAMessageCollectionByMmsiAndMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisPositionReportClassAMessageObject> GetAisPositionReportClassAMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
        IList<AisPositionReportClassAMessageObject> GetAisPositionReportClassAMessageCollectionByMmsiFromMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisPositionReportClassAMessageObject> GetAisPositionReportClassAMessageCollectionByMmsiUntilMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisPositionReportClassAMessageObject> GetAisPositionReportClassAMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
        // ---------------------------------------------------------------------
        // AisPositionReportClassAResponseToInterrogationMessage queries
        // ---------------------------------------------------------------------
        AisPositionReportClassAResponseToInterrogationMessageObject? GetAisPositionReportClassAResponseToInterrogationMessageById( Guid id );
        IList<AisPositionReportClassAResponseToInterrogationMessageObject> GetAisPositionReportClassAResponseToInterrogationMessageCollection( );
        IList<AisPositionReportClassAResponseToInterrogationMessageObject> GetAisPositionReportClassAResponseToInterrogationMessageCollectionByAisDevice( Guid aisDevice );
        AisPositionReportClassAResponseToInterrogationMessageObject? GetAisPositionReportClassAResponseToInterrogationMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        AisPositionReportClassAResponseToInterrogationMessageObject? GetAisPositionReportClassAResponseToInterrogationMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisPositionReportClassAResponseToInterrogationMessageObject> GetAisPositionReportClassAResponseToInterrogationMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisPositionReportClassAResponseToInterrogationMessageObject> GetAisPositionReportClassAResponseToInterrogationMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisPositionReportClassAResponseToInterrogationMessageObject> GetAisPositionReportClassAResponseToInterrogationMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisPositionReportClassAResponseToInterrogationMessageObject> GetAisPositionReportClassAResponseToInterrogationMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisPositionReportClassAResponseToInterrogationMessageObject> GetAisPositionReportClassAResponseToInterrogationMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisPositionReportClassAResponseToInterrogationMessageObject> GetAisPositionReportClassAResponseToInterrogationMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisPositionReportClassAResponseToInterrogationMessageObject> GetAisPositionReportClassAResponseToInterrogationMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisPositionReportClassAResponseToInterrogationMessageObject> GetAisPositionReportClassAResponseToInterrogationMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisPositionReportClassAResponseToInterrogationMessageObject> GetAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsi( Guid? mmsi );
        IList<AisPositionReportClassAResponseToInterrogationMessageObject> GetAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsiIsNull(  );
        IList<AisPositionReportClassAResponseToInterrogationMessageObject> GetAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsiAndMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisPositionReportClassAResponseToInterrogationMessageObject> GetAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
        IList<AisPositionReportClassAResponseToInterrogationMessageObject> GetAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsiFromMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisPositionReportClassAResponseToInterrogationMessageObject> GetAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsiUntilMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisPositionReportClassAResponseToInterrogationMessageObject> GetAisPositionReportClassAResponseToInterrogationMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
        // ---------------------------------------------------------------------
        // AisPositionReportForLongRangeApplicationsMessage queries
        // ---------------------------------------------------------------------
        AisPositionReportForLongRangeApplicationsMessageObject? GetAisPositionReportForLongRangeApplicationsMessageById( Guid id );
        IList<AisPositionReportForLongRangeApplicationsMessageObject> GetAisPositionReportForLongRangeApplicationsMessageCollection( );
        IList<AisPositionReportForLongRangeApplicationsMessageObject> GetAisPositionReportForLongRangeApplicationsMessageCollectionByAisDevice( Guid aisDevice );
        AisPositionReportForLongRangeApplicationsMessageObject? GetAisPositionReportForLongRangeApplicationsMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        AisPositionReportForLongRangeApplicationsMessageObject? GetAisPositionReportForLongRangeApplicationsMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisPositionReportForLongRangeApplicationsMessageObject> GetAisPositionReportForLongRangeApplicationsMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisPositionReportForLongRangeApplicationsMessageObject> GetAisPositionReportForLongRangeApplicationsMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisPositionReportForLongRangeApplicationsMessageObject> GetAisPositionReportForLongRangeApplicationsMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisPositionReportForLongRangeApplicationsMessageObject> GetAisPositionReportForLongRangeApplicationsMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisPositionReportForLongRangeApplicationsMessageObject> GetAisPositionReportForLongRangeApplicationsMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisPositionReportForLongRangeApplicationsMessageObject> GetAisPositionReportForLongRangeApplicationsMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisPositionReportForLongRangeApplicationsMessageObject> GetAisPositionReportForLongRangeApplicationsMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisPositionReportForLongRangeApplicationsMessageObject> GetAisPositionReportForLongRangeApplicationsMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisPositionReportForLongRangeApplicationsMessageObject> GetAisPositionReportForLongRangeApplicationsMessageCollectionByMmsi( Guid? mmsi );
        IList<AisPositionReportForLongRangeApplicationsMessageObject> GetAisPositionReportForLongRangeApplicationsMessageCollectionByMmsiIsNull(  );
        IList<AisPositionReportForLongRangeApplicationsMessageObject> GetAisPositionReportForLongRangeApplicationsMessageCollectionByMmsiAndMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisPositionReportForLongRangeApplicationsMessageObject> GetAisPositionReportForLongRangeApplicationsMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
        IList<AisPositionReportForLongRangeApplicationsMessageObject> GetAisPositionReportForLongRangeApplicationsMessageCollectionByMmsiFromMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisPositionReportForLongRangeApplicationsMessageObject> GetAisPositionReportForLongRangeApplicationsMessageCollectionByMmsiUntilMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisPositionReportForLongRangeApplicationsMessageObject> GetAisPositionReportForLongRangeApplicationsMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
        // ---------------------------------------------------------------------
        // AisSafetyRelatedAcknowledgmentMessage queries
        // ---------------------------------------------------------------------
        AisSafetyRelatedAcknowledgmentMessageObject? GetAisSafetyRelatedAcknowledgmentMessageById( Guid id );
        IList<AisSafetyRelatedAcknowledgmentMessageObject> GetAisSafetyRelatedAcknowledgmentMessageCollection( );
        IList<AisSafetyRelatedAcknowledgmentMessageObject> GetAisSafetyRelatedAcknowledgmentMessageCollectionByAisDevice( Guid aisDevice );
        AisSafetyRelatedAcknowledgmentMessageObject? GetAisSafetyRelatedAcknowledgmentMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        AisSafetyRelatedAcknowledgmentMessageObject? GetAisSafetyRelatedAcknowledgmentMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisSafetyRelatedAcknowledgmentMessageObject> GetAisSafetyRelatedAcknowledgmentMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisSafetyRelatedAcknowledgmentMessageObject> GetAisSafetyRelatedAcknowledgmentMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisSafetyRelatedAcknowledgmentMessageObject> GetAisSafetyRelatedAcknowledgmentMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisSafetyRelatedAcknowledgmentMessageObject> GetAisSafetyRelatedAcknowledgmentMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisSafetyRelatedAcknowledgmentMessageObject> GetAisSafetyRelatedAcknowledgmentMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisSafetyRelatedAcknowledgmentMessageObject> GetAisSafetyRelatedAcknowledgmentMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisSafetyRelatedAcknowledgmentMessageObject> GetAisSafetyRelatedAcknowledgmentMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisSafetyRelatedAcknowledgmentMessageObject> GetAisSafetyRelatedAcknowledgmentMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisSafetyRelatedAcknowledgmentMessageObject> GetAisSafetyRelatedAcknowledgmentMessageCollectionByMmsi( Guid? mmsi );
        IList<AisSafetyRelatedAcknowledgmentMessageObject> GetAisSafetyRelatedAcknowledgmentMessageCollectionByMmsiIsNull(  );
        IList<AisSafetyRelatedAcknowledgmentMessageObject> GetAisSafetyRelatedAcknowledgmentMessageCollectionByMmsiAndMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisSafetyRelatedAcknowledgmentMessageObject> GetAisSafetyRelatedAcknowledgmentMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
        IList<AisSafetyRelatedAcknowledgmentMessageObject> GetAisSafetyRelatedAcknowledgmentMessageCollectionByMmsiFromMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisSafetyRelatedAcknowledgmentMessageObject> GetAisSafetyRelatedAcknowledgmentMessageCollectionByMmsiUntilMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisSafetyRelatedAcknowledgmentMessageObject> GetAisSafetyRelatedAcknowledgmentMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
        // ---------------------------------------------------------------------
        // AisStandardClassBCsPositionReportMessage queries
        // ---------------------------------------------------------------------
        AisStandardClassBCsPositionReportMessageObject? GetAisStandardClassBCsPositionReportMessageById( Guid id );
        IList<AisStandardClassBCsPositionReportMessageObject> GetAisStandardClassBCsPositionReportMessageCollection( );
        IList<AisStandardClassBCsPositionReportMessageObject> GetAisStandardClassBCsPositionReportMessageCollectionByAisDevice( Guid aisDevice );
        AisStandardClassBCsPositionReportMessageObject? GetAisStandardClassBCsPositionReportMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        AisStandardClassBCsPositionReportMessageObject? GetAisStandardClassBCsPositionReportMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisStandardClassBCsPositionReportMessageObject> GetAisStandardClassBCsPositionReportMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisStandardClassBCsPositionReportMessageObject> GetAisStandardClassBCsPositionReportMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisStandardClassBCsPositionReportMessageObject> GetAisStandardClassBCsPositionReportMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisStandardClassBCsPositionReportMessageObject> GetAisStandardClassBCsPositionReportMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisStandardClassBCsPositionReportMessageObject> GetAisStandardClassBCsPositionReportMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisStandardClassBCsPositionReportMessageObject> GetAisStandardClassBCsPositionReportMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisStandardClassBCsPositionReportMessageObject> GetAisStandardClassBCsPositionReportMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisStandardClassBCsPositionReportMessageObject> GetAisStandardClassBCsPositionReportMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisStandardClassBCsPositionReportMessageObject> GetAisStandardClassBCsPositionReportMessageCollectionByMmsi( Guid? mmsi );
        IList<AisStandardClassBCsPositionReportMessageObject> GetAisStandardClassBCsPositionReportMessageCollectionByMmsiIsNull(  );
        IList<AisStandardClassBCsPositionReportMessageObject> GetAisStandardClassBCsPositionReportMessageCollectionByMmsiAndMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisStandardClassBCsPositionReportMessageObject> GetAisStandardClassBCsPositionReportMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
        IList<AisStandardClassBCsPositionReportMessageObject> GetAisStandardClassBCsPositionReportMessageCollectionByMmsiFromMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisStandardClassBCsPositionReportMessageObject> GetAisStandardClassBCsPositionReportMessageCollectionByMmsiUntilMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisStandardClassBCsPositionReportMessageObject> GetAisStandardClassBCsPositionReportMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
        // ---------------------------------------------------------------------
        // AisStandardSarAircraftPositionReportMessage queries
        // ---------------------------------------------------------------------
        AisStandardSarAircraftPositionReportMessageObject? GetAisStandardSarAircraftPositionReportMessageById( Guid id );
        IList<AisStandardSarAircraftPositionReportMessageObject> GetAisStandardSarAircraftPositionReportMessageCollection( );
        IList<AisStandardSarAircraftPositionReportMessageObject> GetAisStandardSarAircraftPositionReportMessageCollectionByAisDevice( Guid aisDevice );
        AisStandardSarAircraftPositionReportMessageObject? GetAisStandardSarAircraftPositionReportMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        AisStandardSarAircraftPositionReportMessageObject? GetAisStandardSarAircraftPositionReportMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisStandardSarAircraftPositionReportMessageObject> GetAisStandardSarAircraftPositionReportMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisStandardSarAircraftPositionReportMessageObject> GetAisStandardSarAircraftPositionReportMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisStandardSarAircraftPositionReportMessageObject> GetAisStandardSarAircraftPositionReportMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisStandardSarAircraftPositionReportMessageObject> GetAisStandardSarAircraftPositionReportMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisStandardSarAircraftPositionReportMessageObject> GetAisStandardSarAircraftPositionReportMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisStandardSarAircraftPositionReportMessageObject> GetAisStandardSarAircraftPositionReportMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisStandardSarAircraftPositionReportMessageObject> GetAisStandardSarAircraftPositionReportMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisStandardSarAircraftPositionReportMessageObject> GetAisStandardSarAircraftPositionReportMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisStandardSarAircraftPositionReportMessageObject> GetAisStandardSarAircraftPositionReportMessageCollectionByMmsi( Guid? mmsi );
        IList<AisStandardSarAircraftPositionReportMessageObject> GetAisStandardSarAircraftPositionReportMessageCollectionByMmsiIsNull(  );
        IList<AisStandardSarAircraftPositionReportMessageObject> GetAisStandardSarAircraftPositionReportMessageCollectionByMmsiAndMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisStandardSarAircraftPositionReportMessageObject> GetAisStandardSarAircraftPositionReportMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
        IList<AisStandardSarAircraftPositionReportMessageObject> GetAisStandardSarAircraftPositionReportMessageCollectionByMmsiFromMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisStandardSarAircraftPositionReportMessageObject> GetAisStandardSarAircraftPositionReportMessageCollectionByMmsiUntilMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisStandardSarAircraftPositionReportMessageObject> GetAisStandardSarAircraftPositionReportMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
        // ---------------------------------------------------------------------
        // AisStaticAndVoyageRelatedDataMessage queries
        // ---------------------------------------------------------------------
        AisStaticAndVoyageRelatedDataMessageObject? GetAisStaticAndVoyageRelatedDataMessageById( Guid id );
        IList<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageCollection( );
        IList<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageCollectionByAisDevice( Guid aisDevice );
        AisStaticAndVoyageRelatedDataMessageObject? GetAisStaticAndVoyageRelatedDataMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        AisStaticAndVoyageRelatedDataMessageObject? GetAisStaticAndVoyageRelatedDataMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageCollectionByMmsi( Guid? mmsi );
        IList<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageCollectionByMmsiIsNull(  );
        IList<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageCollectionByMmsiAndMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
        IList<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageCollectionByMmsiFromMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageCollectionByMmsiUntilMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
        IList<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageCollectionByImoNumber( Guid? imoNumber );
        IList<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageCollectionByImoNumberIsNull(  );
        IList<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageCollectionByCallsign( Guid? callsign );
        IList<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageCollectionByCallsignIsNull(  );
        IList<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageCollectionByShipName( Guid? shipName );
        IList<AisStaticAndVoyageRelatedDataMessageObject> GetAisStaticAndVoyageRelatedDataMessageCollectionByShipNameIsNull(  );
        // ---------------------------------------------------------------------
        // AisStaticDataReportMessage queries
        // ---------------------------------------------------------------------
        AisStaticDataReportMessageObject? GetAisStaticDataReportMessageById( Guid id );
        IList<AisStaticDataReportMessageObject> GetAisStaticDataReportMessageCollection( );
        IList<AisStaticDataReportMessageObject> GetAisStaticDataReportMessageCollectionByAisDevice( Guid aisDevice );
        AisStaticDataReportMessageObject? GetAisStaticDataReportMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        AisStaticDataReportMessageObject? GetAisStaticDataReportMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisStaticDataReportMessageObject> GetAisStaticDataReportMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisStaticDataReportMessageObject> GetAisStaticDataReportMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisStaticDataReportMessageObject> GetAisStaticDataReportMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisStaticDataReportMessageObject> GetAisStaticDataReportMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisStaticDataReportMessageObject> GetAisStaticDataReportMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisStaticDataReportMessageObject> GetAisStaticDataReportMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisStaticDataReportMessageObject> GetAisStaticDataReportMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisStaticDataReportMessageObject> GetAisStaticDataReportMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisStaticDataReportMessageObject> GetAisStaticDataReportMessageCollectionByMmsi( Guid? mmsi );
        IList<AisStaticDataReportMessageObject> GetAisStaticDataReportMessageCollectionByMmsiIsNull(  );
        IList<AisStaticDataReportMessageObject> GetAisStaticDataReportMessageCollectionByMmsiAndMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisStaticDataReportMessageObject> GetAisStaticDataReportMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
        IList<AisStaticDataReportMessageObject> GetAisStaticDataReportMessageCollectionByMmsiFromMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisStaticDataReportMessageObject> GetAisStaticDataReportMessageCollectionByMmsiUntilMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisStaticDataReportMessageObject> GetAisStaticDataReportMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
        // ---------------------------------------------------------------------
        // AisStaticDataReportPartAMessage queries
        // ---------------------------------------------------------------------
        AisStaticDataReportPartAMessageObject? GetAisStaticDataReportPartAMessageById( Guid id );
        IList<AisStaticDataReportPartAMessageObject> GetAisStaticDataReportPartAMessageCollection( );
        IList<AisStaticDataReportPartAMessageObject> GetAisStaticDataReportPartAMessageCollectionByAisDevice( Guid aisDevice );
        AisStaticDataReportPartAMessageObject? GetAisStaticDataReportPartAMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        AisStaticDataReportPartAMessageObject? GetAisStaticDataReportPartAMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisStaticDataReportPartAMessageObject> GetAisStaticDataReportPartAMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisStaticDataReportPartAMessageObject> GetAisStaticDataReportPartAMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisStaticDataReportPartAMessageObject> GetAisStaticDataReportPartAMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisStaticDataReportPartAMessageObject> GetAisStaticDataReportPartAMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisStaticDataReportPartAMessageObject> GetAisStaticDataReportPartAMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisStaticDataReportPartAMessageObject> GetAisStaticDataReportPartAMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisStaticDataReportPartAMessageObject> GetAisStaticDataReportPartAMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisStaticDataReportPartAMessageObject> GetAisStaticDataReportPartAMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisStaticDataReportPartAMessageObject> GetAisStaticDataReportPartAMessageCollectionByMmsi( Guid? mmsi );
        IList<AisStaticDataReportPartAMessageObject> GetAisStaticDataReportPartAMessageCollectionByMmsiIsNull(  );
        IList<AisStaticDataReportPartAMessageObject> GetAisStaticDataReportPartAMessageCollectionByMmsiAndMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisStaticDataReportPartAMessageObject> GetAisStaticDataReportPartAMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
        IList<AisStaticDataReportPartAMessageObject> GetAisStaticDataReportPartAMessageCollectionByMmsiFromMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisStaticDataReportPartAMessageObject> GetAisStaticDataReportPartAMessageCollectionByMmsiUntilMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisStaticDataReportPartAMessageObject> GetAisStaticDataReportPartAMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
        IList<AisStaticDataReportPartAMessageObject> GetAisStaticDataReportPartAMessageCollectionByShipName( Guid? shipName );
        IList<AisStaticDataReportPartAMessageObject> GetAisStaticDataReportPartAMessageCollectionByShipNameIsNull(  );
        // ---------------------------------------------------------------------
        // AisStaticDataReportPartBMessage queries
        // ---------------------------------------------------------------------
        AisStaticDataReportPartBMessageObject? GetAisStaticDataReportPartBMessageById( Guid id );
        IList<AisStaticDataReportPartBMessageObject> GetAisStaticDataReportPartBMessageCollection( );
        IList<AisStaticDataReportPartBMessageObject> GetAisStaticDataReportPartBMessageCollectionByAisDevice( Guid aisDevice );
        AisStaticDataReportPartBMessageObject? GetAisStaticDataReportPartBMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        AisStaticDataReportPartBMessageObject? GetAisStaticDataReportPartBMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisStaticDataReportPartBMessageObject> GetAisStaticDataReportPartBMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisStaticDataReportPartBMessageObject> GetAisStaticDataReportPartBMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisStaticDataReportPartBMessageObject> GetAisStaticDataReportPartBMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisStaticDataReportPartBMessageObject> GetAisStaticDataReportPartBMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisStaticDataReportPartBMessageObject> GetAisStaticDataReportPartBMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisStaticDataReportPartBMessageObject> GetAisStaticDataReportPartBMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisStaticDataReportPartBMessageObject> GetAisStaticDataReportPartBMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisStaticDataReportPartBMessageObject> GetAisStaticDataReportPartBMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisStaticDataReportPartBMessageObject> GetAisStaticDataReportPartBMessageCollectionByMmsi( Guid? mmsi );
        IList<AisStaticDataReportPartBMessageObject> GetAisStaticDataReportPartBMessageCollectionByMmsiIsNull(  );
        IList<AisStaticDataReportPartBMessageObject> GetAisStaticDataReportPartBMessageCollectionByMmsiAndMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisStaticDataReportPartBMessageObject> GetAisStaticDataReportPartBMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
        IList<AisStaticDataReportPartBMessageObject> GetAisStaticDataReportPartBMessageCollectionByMmsiFromMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisStaticDataReportPartBMessageObject> GetAisStaticDataReportPartBMessageCollectionByMmsiUntilMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisStaticDataReportPartBMessageObject> GetAisStaticDataReportPartBMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
        IList<AisStaticDataReportPartBMessageObject> GetAisStaticDataReportPartBMessageCollectionByCallsign( Guid? callsign );
        IList<AisStaticDataReportPartBMessageObject> GetAisStaticDataReportPartBMessageCollectionByCallsignIsNull(  );
        IList<AisStaticDataReportPartBMessageObject> GetAisStaticDataReportPartBMessageCollectionByMothershipMmsi( Guid? mothershipMmsi );
        IList<AisStaticDataReportPartBMessageObject> GetAisStaticDataReportPartBMessageCollectionByMothershipMmsiIsNull(  );
        // ---------------------------------------------------------------------
        // AisUtcAndDateInquiryMessage queries
        // ---------------------------------------------------------------------
        AisUtcAndDateInquiryMessageObject? GetAisUtcAndDateInquiryMessageById( Guid id );
        IList<AisUtcAndDateInquiryMessageObject> GetAisUtcAndDateInquiryMessageCollection( );
        IList<AisUtcAndDateInquiryMessageObject> GetAisUtcAndDateInquiryMessageCollectionByAisDevice( Guid aisDevice );
        AisUtcAndDateInquiryMessageObject? GetAisUtcAndDateInquiryMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        AisUtcAndDateInquiryMessageObject? GetAisUtcAndDateInquiryMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisUtcAndDateInquiryMessageObject> GetAisUtcAndDateInquiryMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisUtcAndDateInquiryMessageObject> GetAisUtcAndDateInquiryMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisUtcAndDateInquiryMessageObject> GetAisUtcAndDateInquiryMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisUtcAndDateInquiryMessageObject> GetAisUtcAndDateInquiryMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisUtcAndDateInquiryMessageObject> GetAisUtcAndDateInquiryMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisUtcAndDateInquiryMessageObject> GetAisUtcAndDateInquiryMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisUtcAndDateInquiryMessageObject> GetAisUtcAndDateInquiryMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisUtcAndDateInquiryMessageObject> GetAisUtcAndDateInquiryMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisUtcAndDateInquiryMessageObject> GetAisUtcAndDateInquiryMessageCollectionByMmsi( Guid? mmsi );
        IList<AisUtcAndDateInquiryMessageObject> GetAisUtcAndDateInquiryMessageCollectionByMmsiIsNull(  );
        IList<AisUtcAndDateInquiryMessageObject> GetAisUtcAndDateInquiryMessageCollectionByMmsiAndMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisUtcAndDateInquiryMessageObject> GetAisUtcAndDateInquiryMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
        IList<AisUtcAndDateInquiryMessageObject> GetAisUtcAndDateInquiryMessageCollectionByMmsiFromMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisUtcAndDateInquiryMessageObject> GetAisUtcAndDateInquiryMessageCollectionByMmsiUntilMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisUtcAndDateInquiryMessageObject> GetAisUtcAndDateInquiryMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
        // ---------------------------------------------------------------------
        // AisUtcAndDateResponseMessage queries
        // ---------------------------------------------------------------------
        AisUtcAndDateResponseMessageObject? GetAisUtcAndDateResponseMessageById( Guid id );
        IList<AisUtcAndDateResponseMessageObject> GetAisUtcAndDateResponseMessageCollection( );
        IList<AisUtcAndDateResponseMessageObject> GetAisUtcAndDateResponseMessageCollectionByAisDevice( Guid aisDevice );
        AisUtcAndDateResponseMessageObject? GetAisUtcAndDateResponseMessageByAisDeviceAndReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        AisUtcAndDateResponseMessageObject? GetAisUtcAndDateResponseMessageByAisDeviceAtReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisUtcAndDateResponseMessageObject> GetAisUtcAndDateResponseMessageByAisDeviceFromReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisUtcAndDateResponseMessageObject> GetAisUtcAndDateResponseMessageByAisDeviceUntilReceivedTimestamp( Guid aisDevice, DateTime receivedTimestamp );
        IList<AisUtcAndDateResponseMessageObject> GetAisUtcAndDateResponseMessageByAisDeviceOverReceivedTimestamp( Guid aisDevice, DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisUtcAndDateResponseMessageObject> GetAisUtcAndDateResponseMessageCollectionByReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisUtcAndDateResponseMessageObject> GetAisUtcAndDateResponseMessageCollectionAtReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisUtcAndDateResponseMessageObject> GetAisUtcAndDateResponseMessageCollectionFromReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisUtcAndDateResponseMessageObject> GetAisUtcAndDateResponseMessageCollectionUntilReceivedTimestamp( DateTime receivedTimestamp );
        IList<AisUtcAndDateResponseMessageObject> GetAisUtcAndDateResponseMessageCollectionOverReceivedTimestamp( DateTime fromReceivedTimestamp, DateTime untilReceivedTimestamp );
        IList<AisUtcAndDateResponseMessageObject> GetAisUtcAndDateResponseMessageCollectionByMmsi( Guid? mmsi );
        IList<AisUtcAndDateResponseMessageObject> GetAisUtcAndDateResponseMessageCollectionByMmsiIsNull(  );
        IList<AisUtcAndDateResponseMessageObject> GetAisUtcAndDateResponseMessageCollectionByMmsiAndMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisUtcAndDateResponseMessageObject> GetAisUtcAndDateResponseMessageCollectionByMmsiIsNullAndMessageSequenceNumber( long messageSequenceNumber );
        IList<AisUtcAndDateResponseMessageObject> GetAisUtcAndDateResponseMessageCollectionByMmsiFromMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisUtcAndDateResponseMessageObject> GetAisUtcAndDateResponseMessageCollectionByMmsiUntilMessageSequenceNumber( Guid? mmsi, long messageSequenceNumber );
        IList<AisUtcAndDateResponseMessageObject> GetAisUtcAndDateResponseMessageCollectionByMmsiOverMessageSequenceNumber( Guid mmsi, long fromMessageSequenceNumber, long untilMessageSequenceNumber );
        // ---------------------------------------------------------------------
        // AlarmStateChange queries
        // ---------------------------------------------------------------------
        AlarmStateChangeObject? GetAlarmStateChangeById( Guid id );
        IList<AlarmStateChangeObject> GetAlarmStateChangeCollection( );
        IList<AlarmStateChangeObject> GetAlarmStateChangeCollectionByAlarm( Guid alarm );
        AlarmStateChangeObject? GetAlarmStateChangeByAlarmAndTimestamp( Guid alarm, DateTime timestamp );
        AlarmStateChangeObject? GetAlarmStateChangeByAlarmAtTimestamp( Guid alarm, DateTime timestamp );
        IList<AlarmStateChangeObject> GetAlarmStateChangeByAlarmFromTimestamp( Guid alarm, DateTime timestamp );
        IList<AlarmStateChangeObject> GetAlarmStateChangeByAlarmUntilTimestamp( Guid alarm, DateTime timestamp );
        IList<AlarmStateChangeObject> GetAlarmStateChangeByAlarmOverTimestamp( Guid alarm, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<AlarmStateChangeObject> GetAlarmStateChangeCollectionByTimestamp( DateTime timestamp );
        IList<AlarmStateChangeObject> GetAlarmStateChangeCollectionAtTimestamp( DateTime timestamp );
        IList<AlarmStateChangeObject> GetAlarmStateChangeCollectionFromTimestamp( DateTime timestamp );
        IList<AlarmStateChangeObject> GetAlarmStateChangeCollectionUntilTimestamp( DateTime timestamp );
        IList<AlarmStateChangeObject> GetAlarmStateChangeCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // BaseStationType queries
        // ---------------------------------------------------------------------
        BaseStationTypeObject? GetBaseStationTypeById( Guid id );
        IList<BaseStationTypeObject> GetBaseStationTypeCollection( );
        BaseStationTypeObject? GetBaseStationTypeByName( string name );
        // ---------------------------------------------------------------------
        // BinaryTimeseriesValue queries
        // ---------------------------------------------------------------------
        BinaryTimeseriesValueObject? GetBinaryTimeseriesValueById( Guid id );
        IList<BinaryTimeseriesValueObject> GetBinaryTimeseriesValueCollection( );
        IList<BinaryTimeseriesValueObject> GetBinaryTimeseriesValueCollectionByTimeseries( Guid timeseries );
        BinaryTimeseriesValueObject? GetBinaryTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
        BinaryTimeseriesValueObject? GetBinaryTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
        IList<BinaryTimeseriesValueObject> GetBinaryTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
        IList<BinaryTimeseriesValueObject> GetBinaryTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
        IList<BinaryTimeseriesValueObject> GetBinaryTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<BinaryTimeseriesValueObject> GetBinaryTimeseriesValueCollectionByTimestamp( DateTime timestamp );
        IList<BinaryTimeseriesValueObject> GetBinaryTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
        IList<BinaryTimeseriesValueObject> GetBinaryTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
        IList<BinaryTimeseriesValueObject> GetBinaryTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
        IList<BinaryTimeseriesValueObject> GetBinaryTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // Bookmark queries
        // ---------------------------------------------------------------------
        BookmarkObject? GetBookmarkById( Guid id );
        IList<BookmarkObject> GetBookmarkCollection( );
        IList<BookmarkObject> GetBookmarkCollectionByView( Guid view );
        // ---------------------------------------------------------------------
        // BooleanTimeseriesValue queries
        // ---------------------------------------------------------------------
        BooleanTimeseriesValueObject? GetBooleanTimeseriesValueById( Guid id );
        IList<BooleanTimeseriesValueObject> GetBooleanTimeseriesValueCollection( );
        IList<BooleanTimeseriesValueObject> GetBooleanTimeseriesValueCollectionByTimeseries( Guid timeseries );
        BooleanTimeseriesValueObject? GetBooleanTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
        BooleanTimeseriesValueObject? GetBooleanTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
        IList<BooleanTimeseriesValueObject> GetBooleanTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
        IList<BooleanTimeseriesValueObject> GetBooleanTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
        IList<BooleanTimeseriesValueObject> GetBooleanTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<BooleanTimeseriesValueObject> GetBooleanTimeseriesValueCollectionByTimestamp( DateTime timestamp );
        IList<BooleanTimeseriesValueObject> GetBooleanTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
        IList<BooleanTimeseriesValueObject> GetBooleanTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
        IList<BooleanTimeseriesValueObject> GetBooleanTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
        IList<BooleanTimeseriesValueObject> GetBooleanTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // ByteTimeseriesValue queries
        // ---------------------------------------------------------------------
        ByteTimeseriesValueObject? GetByteTimeseriesValueById( Guid id );
        IList<ByteTimeseriesValueObject> GetByteTimeseriesValueCollection( );
        IList<ByteTimeseriesValueObject> GetByteTimeseriesValueCollectionByTimeseries( Guid timeseries );
        ByteTimeseriesValueObject? GetByteTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
        ByteTimeseriesValueObject? GetByteTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
        IList<ByteTimeseriesValueObject> GetByteTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
        IList<ByteTimeseriesValueObject> GetByteTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
        IList<ByteTimeseriesValueObject> GetByteTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<ByteTimeseriesValueObject> GetByteTimeseriesValueCollectionByTimestamp( DateTime timestamp );
        IList<ByteTimeseriesValueObject> GetByteTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
        IList<ByteTimeseriesValueObject> GetByteTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
        IList<ByteTimeseriesValueObject> GetByteTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
        IList<ByteTimeseriesValueObject> GetByteTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // CameraCommand queries
        // ---------------------------------------------------------------------
        CameraCommandObject? GetCameraCommandById( Guid id );
        IList<CameraCommandObject> GetCameraCommandCollection( );
        IList<CameraCommandObject> GetCameraCommandCollectionByCamera( Guid camera );
        IList<CameraCommandObject> GetCameraCommandCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandObject> GetCameraCommandCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandObject> GetCameraCommandCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandObject> GetCameraCommandCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandObject> GetCameraCommandCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandObject> GetCameraCommandCollectionByTimestamp( DateTime timestamp );
        IList<CameraCommandObject> GetCameraCommandCollectionAtTimestamp( DateTime timestamp );
        IList<CameraCommandObject> GetCameraCommandCollectionFromTimestamp( DateTime timestamp );
        IList<CameraCommandObject> GetCameraCommandCollectionUntilTimestamp( DateTime timestamp );
        IList<CameraCommandObject> GetCameraCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandObject> GetCameraCommandCollectionByReply( Guid? reply );
        IList<CameraCommandObject> GetCameraCommandCollectionByReplyIsNull(  );
        // ---------------------------------------------------------------------
        // CameraCommandAbsoluteMove queries
        // ---------------------------------------------------------------------
        CameraCommandAbsoluteMoveObject? GetCameraCommandAbsoluteMoveById( Guid id );
        IList<CameraCommandAbsoluteMoveObject> GetCameraCommandAbsoluteMoveCollection( );
        IList<CameraCommandAbsoluteMoveObject> GetCameraCommandAbsoluteMoveCollectionByCamera( Guid camera );
        IList<CameraCommandAbsoluteMoveObject> GetCameraCommandAbsoluteMoveCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandAbsoluteMoveObject> GetCameraCommandAbsoluteMoveCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandAbsoluteMoveObject> GetCameraCommandAbsoluteMoveCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandAbsoluteMoveObject> GetCameraCommandAbsoluteMoveCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandAbsoluteMoveObject> GetCameraCommandAbsoluteMoveCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandAbsoluteMoveObject> GetCameraCommandAbsoluteMoveCollectionByTimestamp( DateTime timestamp );
        IList<CameraCommandAbsoluteMoveObject> GetCameraCommandAbsoluteMoveCollectionAtTimestamp( DateTime timestamp );
        IList<CameraCommandAbsoluteMoveObject> GetCameraCommandAbsoluteMoveCollectionFromTimestamp( DateTime timestamp );
        IList<CameraCommandAbsoluteMoveObject> GetCameraCommandAbsoluteMoveCollectionUntilTimestamp( DateTime timestamp );
        IList<CameraCommandAbsoluteMoveObject> GetCameraCommandAbsoluteMoveCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandAbsoluteMoveObject> GetCameraCommandAbsoluteMoveCollectionByReply( Guid? reply );
        IList<CameraCommandAbsoluteMoveObject> GetCameraCommandAbsoluteMoveCollectionByReplyIsNull(  );
        // ---------------------------------------------------------------------
        // CameraCommandAdjustPanTiltZoom queries
        // ---------------------------------------------------------------------
        CameraCommandAdjustPanTiltZoomObject? GetCameraCommandAdjustPanTiltZoomById( Guid id );
        IList<CameraCommandAdjustPanTiltZoomObject> GetCameraCommandAdjustPanTiltZoomCollection( );
        IList<CameraCommandAdjustPanTiltZoomObject> GetCameraCommandAdjustPanTiltZoomCollectionByCamera( Guid camera );
        IList<CameraCommandAdjustPanTiltZoomObject> GetCameraCommandAdjustPanTiltZoomCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandAdjustPanTiltZoomObject> GetCameraCommandAdjustPanTiltZoomCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandAdjustPanTiltZoomObject> GetCameraCommandAdjustPanTiltZoomCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandAdjustPanTiltZoomObject> GetCameraCommandAdjustPanTiltZoomCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandAdjustPanTiltZoomObject> GetCameraCommandAdjustPanTiltZoomCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandAdjustPanTiltZoomObject> GetCameraCommandAdjustPanTiltZoomCollectionByTimestamp( DateTime timestamp );
        IList<CameraCommandAdjustPanTiltZoomObject> GetCameraCommandAdjustPanTiltZoomCollectionAtTimestamp( DateTime timestamp );
        IList<CameraCommandAdjustPanTiltZoomObject> GetCameraCommandAdjustPanTiltZoomCollectionFromTimestamp( DateTime timestamp );
        IList<CameraCommandAdjustPanTiltZoomObject> GetCameraCommandAdjustPanTiltZoomCollectionUntilTimestamp( DateTime timestamp );
        IList<CameraCommandAdjustPanTiltZoomObject> GetCameraCommandAdjustPanTiltZoomCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandAdjustPanTiltZoomObject> GetCameraCommandAdjustPanTiltZoomCollectionByReply( Guid? reply );
        IList<CameraCommandAdjustPanTiltZoomObject> GetCameraCommandAdjustPanTiltZoomCollectionByReplyIsNull(  );
        // ---------------------------------------------------------------------
        // CameraCommandContinuousMove queries
        // ---------------------------------------------------------------------
        CameraCommandContinuousMoveObject? GetCameraCommandContinuousMoveById( Guid id );
        IList<CameraCommandContinuousMoveObject> GetCameraCommandContinuousMoveCollection( );
        IList<CameraCommandContinuousMoveObject> GetCameraCommandContinuousMoveCollectionByCamera( Guid camera );
        IList<CameraCommandContinuousMoveObject> GetCameraCommandContinuousMoveCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandContinuousMoveObject> GetCameraCommandContinuousMoveCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandContinuousMoveObject> GetCameraCommandContinuousMoveCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandContinuousMoveObject> GetCameraCommandContinuousMoveCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandContinuousMoveObject> GetCameraCommandContinuousMoveCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandContinuousMoveObject> GetCameraCommandContinuousMoveCollectionByTimestamp( DateTime timestamp );
        IList<CameraCommandContinuousMoveObject> GetCameraCommandContinuousMoveCollectionAtTimestamp( DateTime timestamp );
        IList<CameraCommandContinuousMoveObject> GetCameraCommandContinuousMoveCollectionFromTimestamp( DateTime timestamp );
        IList<CameraCommandContinuousMoveObject> GetCameraCommandContinuousMoveCollectionUntilTimestamp( DateTime timestamp );
        IList<CameraCommandContinuousMoveObject> GetCameraCommandContinuousMoveCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandContinuousMoveObject> GetCameraCommandContinuousMoveCollectionByReply( Guid? reply );
        IList<CameraCommandContinuousMoveObject> GetCameraCommandContinuousMoveCollectionByReplyIsNull(  );
        // ---------------------------------------------------------------------
        // CameraCommandGeoMove queries
        // ---------------------------------------------------------------------
        CameraCommandGeoMoveObject? GetCameraCommandGeoMoveById( Guid id );
        IList<CameraCommandGeoMoveObject> GetCameraCommandGeoMoveCollection( );
        IList<CameraCommandGeoMoveObject> GetCameraCommandGeoMoveCollectionByCamera( Guid camera );
        IList<CameraCommandGeoMoveObject> GetCameraCommandGeoMoveCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandGeoMoveObject> GetCameraCommandGeoMoveCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandGeoMoveObject> GetCameraCommandGeoMoveCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandGeoMoveObject> GetCameraCommandGeoMoveCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandGeoMoveObject> GetCameraCommandGeoMoveCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandGeoMoveObject> GetCameraCommandGeoMoveCollectionByTimestamp( DateTime timestamp );
        IList<CameraCommandGeoMoveObject> GetCameraCommandGeoMoveCollectionAtTimestamp( DateTime timestamp );
        IList<CameraCommandGeoMoveObject> GetCameraCommandGeoMoveCollectionFromTimestamp( DateTime timestamp );
        IList<CameraCommandGeoMoveObject> GetCameraCommandGeoMoveCollectionUntilTimestamp( DateTime timestamp );
        IList<CameraCommandGeoMoveObject> GetCameraCommandGeoMoveCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandGeoMoveObject> GetCameraCommandGeoMoveCollectionByReply( Guid? reply );
        IList<CameraCommandGeoMoveObject> GetCameraCommandGeoMoveCollectionByReplyIsNull(  );
        // ---------------------------------------------------------------------
        // CameraCommandRelativeMove queries
        // ---------------------------------------------------------------------
        CameraCommandRelativeMoveObject? GetCameraCommandRelativeMoveById( Guid id );
        IList<CameraCommandRelativeMoveObject> GetCameraCommandRelativeMoveCollection( );
        IList<CameraCommandRelativeMoveObject> GetCameraCommandRelativeMoveCollectionByCamera( Guid camera );
        IList<CameraCommandRelativeMoveObject> GetCameraCommandRelativeMoveCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandRelativeMoveObject> GetCameraCommandRelativeMoveCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandRelativeMoveObject> GetCameraCommandRelativeMoveCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandRelativeMoveObject> GetCameraCommandRelativeMoveCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandRelativeMoveObject> GetCameraCommandRelativeMoveCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandRelativeMoveObject> GetCameraCommandRelativeMoveCollectionByTimestamp( DateTime timestamp );
        IList<CameraCommandRelativeMoveObject> GetCameraCommandRelativeMoveCollectionAtTimestamp( DateTime timestamp );
        IList<CameraCommandRelativeMoveObject> GetCameraCommandRelativeMoveCollectionFromTimestamp( DateTime timestamp );
        IList<CameraCommandRelativeMoveObject> GetCameraCommandRelativeMoveCollectionUntilTimestamp( DateTime timestamp );
        IList<CameraCommandRelativeMoveObject> GetCameraCommandRelativeMoveCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandRelativeMoveObject> GetCameraCommandRelativeMoveCollectionByReply( Guid? reply );
        IList<CameraCommandRelativeMoveObject> GetCameraCommandRelativeMoveCollectionByReplyIsNull(  );
        // ---------------------------------------------------------------------
        // CameraCommandReleasePTZOwnership queries
        // ---------------------------------------------------------------------
        CameraCommandReleasePTZOwnershipObject? GetCameraCommandReleasePTZOwnershipById( Guid id );
        IList<CameraCommandReleasePTZOwnershipObject> GetCameraCommandReleasePTZOwnershipCollection( );
        IList<CameraCommandReleasePTZOwnershipObject> GetCameraCommandReleasePTZOwnershipCollectionByCamera( Guid camera );
        IList<CameraCommandReleasePTZOwnershipObject> GetCameraCommandReleasePTZOwnershipCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandReleasePTZOwnershipObject> GetCameraCommandReleasePTZOwnershipCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandReleasePTZOwnershipObject> GetCameraCommandReleasePTZOwnershipCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandReleasePTZOwnershipObject> GetCameraCommandReleasePTZOwnershipCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandReleasePTZOwnershipObject> GetCameraCommandReleasePTZOwnershipCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandReleasePTZOwnershipObject> GetCameraCommandReleasePTZOwnershipCollectionByTimestamp( DateTime timestamp );
        IList<CameraCommandReleasePTZOwnershipObject> GetCameraCommandReleasePTZOwnershipCollectionAtTimestamp( DateTime timestamp );
        IList<CameraCommandReleasePTZOwnershipObject> GetCameraCommandReleasePTZOwnershipCollectionFromTimestamp( DateTime timestamp );
        IList<CameraCommandReleasePTZOwnershipObject> GetCameraCommandReleasePTZOwnershipCollectionUntilTimestamp( DateTime timestamp );
        IList<CameraCommandReleasePTZOwnershipObject> GetCameraCommandReleasePTZOwnershipCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandReleasePTZOwnershipObject> GetCameraCommandReleasePTZOwnershipCollectionByReply( Guid? reply );
        IList<CameraCommandReleasePTZOwnershipObject> GetCameraCommandReleasePTZOwnershipCollectionByReplyIsNull(  );
        // ---------------------------------------------------------------------
        // CameraCommandRequestPTZOwnership queries
        // ---------------------------------------------------------------------
        CameraCommandRequestPTZOwnershipObject? GetCameraCommandRequestPTZOwnershipById( Guid id );
        IList<CameraCommandRequestPTZOwnershipObject> GetCameraCommandRequestPTZOwnershipCollection( );
        IList<CameraCommandRequestPTZOwnershipObject> GetCameraCommandRequestPTZOwnershipCollectionByCamera( Guid camera );
        IList<CameraCommandRequestPTZOwnershipObject> GetCameraCommandRequestPTZOwnershipCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandRequestPTZOwnershipObject> GetCameraCommandRequestPTZOwnershipCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandRequestPTZOwnershipObject> GetCameraCommandRequestPTZOwnershipCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandRequestPTZOwnershipObject> GetCameraCommandRequestPTZOwnershipCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandRequestPTZOwnershipObject> GetCameraCommandRequestPTZOwnershipCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandRequestPTZOwnershipObject> GetCameraCommandRequestPTZOwnershipCollectionByTimestamp( DateTime timestamp );
        IList<CameraCommandRequestPTZOwnershipObject> GetCameraCommandRequestPTZOwnershipCollectionAtTimestamp( DateTime timestamp );
        IList<CameraCommandRequestPTZOwnershipObject> GetCameraCommandRequestPTZOwnershipCollectionFromTimestamp( DateTime timestamp );
        IList<CameraCommandRequestPTZOwnershipObject> GetCameraCommandRequestPTZOwnershipCollectionUntilTimestamp( DateTime timestamp );
        IList<CameraCommandRequestPTZOwnershipObject> GetCameraCommandRequestPTZOwnershipCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandRequestPTZOwnershipObject> GetCameraCommandRequestPTZOwnershipCollectionByReply( Guid? reply );
        IList<CameraCommandRequestPTZOwnershipObject> GetCameraCommandRequestPTZOwnershipCollectionByReplyIsNull(  );
        // ---------------------------------------------------------------------
        // CameraCommandSetAutoFocus queries
        // ---------------------------------------------------------------------
        CameraCommandSetAutoFocusObject? GetCameraCommandSetAutoFocusById( Guid id );
        IList<CameraCommandSetAutoFocusObject> GetCameraCommandSetAutoFocusCollection( );
        IList<CameraCommandSetAutoFocusObject> GetCameraCommandSetAutoFocusCollectionByCamera( Guid camera );
        IList<CameraCommandSetAutoFocusObject> GetCameraCommandSetAutoFocusCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandSetAutoFocusObject> GetCameraCommandSetAutoFocusCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandSetAutoFocusObject> GetCameraCommandSetAutoFocusCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandSetAutoFocusObject> GetCameraCommandSetAutoFocusCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandSetAutoFocusObject> GetCameraCommandSetAutoFocusCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandSetAutoFocusObject> GetCameraCommandSetAutoFocusCollectionByTimestamp( DateTime timestamp );
        IList<CameraCommandSetAutoFocusObject> GetCameraCommandSetAutoFocusCollectionAtTimestamp( DateTime timestamp );
        IList<CameraCommandSetAutoFocusObject> GetCameraCommandSetAutoFocusCollectionFromTimestamp( DateTime timestamp );
        IList<CameraCommandSetAutoFocusObject> GetCameraCommandSetAutoFocusCollectionUntilTimestamp( DateTime timestamp );
        IList<CameraCommandSetAutoFocusObject> GetCameraCommandSetAutoFocusCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandSetAutoFocusObject> GetCameraCommandSetAutoFocusCollectionByReply( Guid? reply );
        IList<CameraCommandSetAutoFocusObject> GetCameraCommandSetAutoFocusCollectionByReplyIsNull(  );
        // ---------------------------------------------------------------------
        // CameraCommandSetBlackAndWhite queries
        // ---------------------------------------------------------------------
        CameraCommandSetBlackAndWhiteObject? GetCameraCommandSetBlackAndWhiteById( Guid id );
        IList<CameraCommandSetBlackAndWhiteObject> GetCameraCommandSetBlackAndWhiteCollection( );
        IList<CameraCommandSetBlackAndWhiteObject> GetCameraCommandSetBlackAndWhiteCollectionByCamera( Guid camera );
        IList<CameraCommandSetBlackAndWhiteObject> GetCameraCommandSetBlackAndWhiteCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandSetBlackAndWhiteObject> GetCameraCommandSetBlackAndWhiteCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandSetBlackAndWhiteObject> GetCameraCommandSetBlackAndWhiteCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandSetBlackAndWhiteObject> GetCameraCommandSetBlackAndWhiteCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandSetBlackAndWhiteObject> GetCameraCommandSetBlackAndWhiteCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandSetBlackAndWhiteObject> GetCameraCommandSetBlackAndWhiteCollectionByTimestamp( DateTime timestamp );
        IList<CameraCommandSetBlackAndWhiteObject> GetCameraCommandSetBlackAndWhiteCollectionAtTimestamp( DateTime timestamp );
        IList<CameraCommandSetBlackAndWhiteObject> GetCameraCommandSetBlackAndWhiteCollectionFromTimestamp( DateTime timestamp );
        IList<CameraCommandSetBlackAndWhiteObject> GetCameraCommandSetBlackAndWhiteCollectionUntilTimestamp( DateTime timestamp );
        IList<CameraCommandSetBlackAndWhiteObject> GetCameraCommandSetBlackAndWhiteCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandSetBlackAndWhiteObject> GetCameraCommandSetBlackAndWhiteCollectionByReply( Guid? reply );
        IList<CameraCommandSetBlackAndWhiteObject> GetCameraCommandSetBlackAndWhiteCollectionByReplyIsNull(  );
        // ---------------------------------------------------------------------
        // CameraCommandSetFollowed queries
        // ---------------------------------------------------------------------
        CameraCommandSetFollowedObject? GetCameraCommandSetFollowedById( Guid id );
        IList<CameraCommandSetFollowedObject> GetCameraCommandSetFollowedCollection( );
        IList<CameraCommandSetFollowedObject> GetCameraCommandSetFollowedCollectionByCamera( Guid camera );
        IList<CameraCommandSetFollowedObject> GetCameraCommandSetFollowedCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandSetFollowedObject> GetCameraCommandSetFollowedCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandSetFollowedObject> GetCameraCommandSetFollowedCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandSetFollowedObject> GetCameraCommandSetFollowedCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandSetFollowedObject> GetCameraCommandSetFollowedCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandSetFollowedObject> GetCameraCommandSetFollowedCollectionByTimestamp( DateTime timestamp );
        IList<CameraCommandSetFollowedObject> GetCameraCommandSetFollowedCollectionAtTimestamp( DateTime timestamp );
        IList<CameraCommandSetFollowedObject> GetCameraCommandSetFollowedCollectionFromTimestamp( DateTime timestamp );
        IList<CameraCommandSetFollowedObject> GetCameraCommandSetFollowedCollectionUntilTimestamp( DateTime timestamp );
        IList<CameraCommandSetFollowedObject> GetCameraCommandSetFollowedCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandSetFollowedObject> GetCameraCommandSetFollowedCollectionByReply( Guid? reply );
        IList<CameraCommandSetFollowedObject> GetCameraCommandSetFollowedCollectionByReplyIsNull(  );
        // ---------------------------------------------------------------------
        // CameraCommandSetInfraRedLamp queries
        // ---------------------------------------------------------------------
        CameraCommandSetInfraRedLampObject? GetCameraCommandSetInfraRedLampById( Guid id );
        IList<CameraCommandSetInfraRedLampObject> GetCameraCommandSetInfraRedLampCollection( );
        IList<CameraCommandSetInfraRedLampObject> GetCameraCommandSetInfraRedLampCollectionByCamera( Guid camera );
        IList<CameraCommandSetInfraRedLampObject> GetCameraCommandSetInfraRedLampCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandSetInfraRedLampObject> GetCameraCommandSetInfraRedLampCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandSetInfraRedLampObject> GetCameraCommandSetInfraRedLampCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandSetInfraRedLampObject> GetCameraCommandSetInfraRedLampCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandSetInfraRedLampObject> GetCameraCommandSetInfraRedLampCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandSetInfraRedLampObject> GetCameraCommandSetInfraRedLampCollectionByTimestamp( DateTime timestamp );
        IList<CameraCommandSetInfraRedLampObject> GetCameraCommandSetInfraRedLampCollectionAtTimestamp( DateTime timestamp );
        IList<CameraCommandSetInfraRedLampObject> GetCameraCommandSetInfraRedLampCollectionFromTimestamp( DateTime timestamp );
        IList<CameraCommandSetInfraRedLampObject> GetCameraCommandSetInfraRedLampCollectionUntilTimestamp( DateTime timestamp );
        IList<CameraCommandSetInfraRedLampObject> GetCameraCommandSetInfraRedLampCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandSetInfraRedLampObject> GetCameraCommandSetInfraRedLampCollectionByReply( Guid? reply );
        IList<CameraCommandSetInfraRedLampObject> GetCameraCommandSetInfraRedLampCollectionByReplyIsNull(  );
        // ---------------------------------------------------------------------
        // CameraCommandSetWasher queries
        // ---------------------------------------------------------------------
        CameraCommandSetWasherObject? GetCameraCommandSetWasherById( Guid id );
        IList<CameraCommandSetWasherObject> GetCameraCommandSetWasherCollection( );
        IList<CameraCommandSetWasherObject> GetCameraCommandSetWasherCollectionByCamera( Guid camera );
        IList<CameraCommandSetWasherObject> GetCameraCommandSetWasherCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandSetWasherObject> GetCameraCommandSetWasherCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandSetWasherObject> GetCameraCommandSetWasherCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandSetWasherObject> GetCameraCommandSetWasherCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandSetWasherObject> GetCameraCommandSetWasherCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandSetWasherObject> GetCameraCommandSetWasherCollectionByTimestamp( DateTime timestamp );
        IList<CameraCommandSetWasherObject> GetCameraCommandSetWasherCollectionAtTimestamp( DateTime timestamp );
        IList<CameraCommandSetWasherObject> GetCameraCommandSetWasherCollectionFromTimestamp( DateTime timestamp );
        IList<CameraCommandSetWasherObject> GetCameraCommandSetWasherCollectionUntilTimestamp( DateTime timestamp );
        IList<CameraCommandSetWasherObject> GetCameraCommandSetWasherCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandSetWasherObject> GetCameraCommandSetWasherCollectionByReply( Guid? reply );
        IList<CameraCommandSetWasherObject> GetCameraCommandSetWasherCollectionByReplyIsNull(  );
        // ---------------------------------------------------------------------
        // CameraCommandSetWiper queries
        // ---------------------------------------------------------------------
        CameraCommandSetWiperObject? GetCameraCommandSetWiperById( Guid id );
        IList<CameraCommandSetWiperObject> GetCameraCommandSetWiperCollection( );
        IList<CameraCommandSetWiperObject> GetCameraCommandSetWiperCollectionByCamera( Guid camera );
        IList<CameraCommandSetWiperObject> GetCameraCommandSetWiperCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandSetWiperObject> GetCameraCommandSetWiperCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandSetWiperObject> GetCameraCommandSetWiperCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandSetWiperObject> GetCameraCommandSetWiperCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandSetWiperObject> GetCameraCommandSetWiperCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandSetWiperObject> GetCameraCommandSetWiperCollectionByTimestamp( DateTime timestamp );
        IList<CameraCommandSetWiperObject> GetCameraCommandSetWiperCollectionAtTimestamp( DateTime timestamp );
        IList<CameraCommandSetWiperObject> GetCameraCommandSetWiperCollectionFromTimestamp( DateTime timestamp );
        IList<CameraCommandSetWiperObject> GetCameraCommandSetWiperCollectionUntilTimestamp( DateTime timestamp );
        IList<CameraCommandSetWiperObject> GetCameraCommandSetWiperCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandSetWiperObject> GetCameraCommandSetWiperCollectionByReply( Guid? reply );
        IList<CameraCommandSetWiperObject> GetCameraCommandSetWiperCollectionByReplyIsNull(  );
        // ---------------------------------------------------------------------
        // CameraCommandStop queries
        // ---------------------------------------------------------------------
        CameraCommandStopObject? GetCameraCommandStopById( Guid id );
        IList<CameraCommandStopObject> GetCameraCommandStopCollection( );
        IList<CameraCommandStopObject> GetCameraCommandStopCollectionByCamera( Guid camera );
        IList<CameraCommandStopObject> GetCameraCommandStopCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandStopObject> GetCameraCommandStopCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandStopObject> GetCameraCommandStopCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandStopObject> GetCameraCommandStopCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandStopObject> GetCameraCommandStopCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandStopObject> GetCameraCommandStopCollectionByTimestamp( DateTime timestamp );
        IList<CameraCommandStopObject> GetCameraCommandStopCollectionAtTimestamp( DateTime timestamp );
        IList<CameraCommandStopObject> GetCameraCommandStopCollectionFromTimestamp( DateTime timestamp );
        IList<CameraCommandStopObject> GetCameraCommandStopCollectionUntilTimestamp( DateTime timestamp );
        IList<CameraCommandStopObject> GetCameraCommandStopCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandStopObject> GetCameraCommandStopCollectionByReply( Guid? reply );
        IList<CameraCommandStopObject> GetCameraCommandStopCollectionByReplyIsNull(  );
        // ---------------------------------------------------------------------
        // CameraCommandReply queries
        // ---------------------------------------------------------------------
        CameraCommandReplyObject? GetCameraCommandReplyById( Guid id );
        IList<CameraCommandReplyObject> GetCameraCommandReplyCollection( );
        IList<CameraCommandReplyObject> GetCameraCommandReplyCollectionByCamera( Guid camera );
        IList<CameraCommandReplyObject> GetCameraCommandReplyCollectionByCameraAndTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandReplyObject> GetCameraCommandReplyCollectionByCameraAtTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandReplyObject> GetCameraCommandReplyCollectionByCameraFromTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandReplyObject> GetCameraCommandReplyCollectionByCameraUntilTimestamp( Guid camera, DateTime timestamp );
        IList<CameraCommandReplyObject> GetCameraCommandReplyCollectionByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraCommandReplyObject> GetCameraCommandReplyCollectionByTimestamp( DateTime timestamp );
        IList<CameraCommandReplyObject> GetCameraCommandReplyCollectionAtTimestamp( DateTime timestamp );
        IList<CameraCommandReplyObject> GetCameraCommandReplyCollectionFromTimestamp( DateTime timestamp );
        IList<CameraCommandReplyObject> GetCameraCommandReplyCollectionUntilTimestamp( DateTime timestamp );
        IList<CameraCommandReplyObject> GetCameraCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        CameraCommandReplyObject? GetCameraCommandReplyByCommand( Guid? command );
        IList<CameraCommandReplyObject> GetCameraCommandReplyCollectionByCommandIsNull(  );
        // ---------------------------------------------------------------------
        // CameraConfiguration queries
        // ---------------------------------------------------------------------
        CameraConfigurationObject? GetCameraConfigurationById( Guid id );
        IList<CameraConfigurationObject> GetCameraConfigurationCollection( );
        IList<CameraConfigurationObject> GetCameraConfigurationCollectionByCamera( Guid camera );
        CameraConfigurationObject? GetCameraConfigurationByCameraAndTimestamp( Guid camera, DateTime timestamp );
        CameraConfigurationObject? GetCameraConfigurationByCameraAtTimestamp( Guid camera, DateTime timestamp );
        IList<CameraConfigurationObject> GetCameraConfigurationByCameraFromTimestamp( Guid camera, DateTime timestamp );
        IList<CameraConfigurationObject> GetCameraConfigurationByCameraUntilTimestamp( Guid camera, DateTime timestamp );
        IList<CameraConfigurationObject> GetCameraConfigurationByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraConfigurationObject> GetCameraConfigurationCollectionByTimestamp( DateTime timestamp );
        IList<CameraConfigurationObject> GetCameraConfigurationCollectionAtTimestamp( DateTime timestamp );
        IList<CameraConfigurationObject> GetCameraConfigurationCollectionFromTimestamp( DateTime timestamp );
        IList<CameraConfigurationObject> GetCameraConfigurationCollectionUntilTimestamp( DateTime timestamp );
        IList<CameraConfigurationObject> GetCameraConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // CameraPanCalibration queries
        // ---------------------------------------------------------------------
        CameraPanCalibrationObject? GetCameraPanCalibrationById( Guid id );
        IList<CameraPanCalibrationObject> GetCameraPanCalibrationCollection( );
        IList<CameraPanCalibrationObject> GetCameraPanCalibrationCollectionByCamera( Guid camera );
        CameraPanCalibrationObject? GetCameraPanCalibrationByCameraAndTimestamp( Guid camera, DateTime timestamp );
        CameraPanCalibrationObject? GetCameraPanCalibrationByCameraAtTimestamp( Guid camera, DateTime timestamp );
        IList<CameraPanCalibrationObject> GetCameraPanCalibrationByCameraFromTimestamp( Guid camera, DateTime timestamp );
        IList<CameraPanCalibrationObject> GetCameraPanCalibrationByCameraUntilTimestamp( Guid camera, DateTime timestamp );
        IList<CameraPanCalibrationObject> GetCameraPanCalibrationByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraPanCalibrationObject> GetCameraPanCalibrationCollectionByTimestamp( DateTime timestamp );
        IList<CameraPanCalibrationObject> GetCameraPanCalibrationCollectionAtTimestamp( DateTime timestamp );
        IList<CameraPanCalibrationObject> GetCameraPanCalibrationCollectionFromTimestamp( DateTime timestamp );
        IList<CameraPanCalibrationObject> GetCameraPanCalibrationCollectionUntilTimestamp( DateTime timestamp );
        IList<CameraPanCalibrationObject> GetCameraPanCalibrationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // CameraPanCalibrationValue queries
        // ---------------------------------------------------------------------
        CameraPanCalibrationValueObject? GetCameraPanCalibrationValueById( Guid id );
        IList<CameraPanCalibrationValueObject> GetCameraPanCalibrationValueCollection( );
        IList<CameraPanCalibrationValueObject> GetCameraPanCalibrationValueCollectionByPanCalibration( Guid panCalibration );
        CameraPanCalibrationValueObject? GetCameraPanCalibrationValueByPanCalibrationAndPanAngle( Guid panCalibration, double panAngle );
        IList<CameraPanCalibrationValueObject> GetCameraPanCalibrationValueByPanCalibrationFromPanAngle( Guid panCalibration, double panAngle );
        IList<CameraPanCalibrationValueObject> GetCameraPanCalibrationValueByPanCalibrationUntilPanAngle( Guid panCalibration, double panAngle );
        IList<CameraPanCalibrationValueObject> GetCameraPanCalibrationValueByPanCalibrationOverPanAngle( Guid panCalibration, double fromPanAngle, double untilPanAngle );
        // ---------------------------------------------------------------------
        // CameraStatus queries
        // ---------------------------------------------------------------------
        CameraStatusObject? GetCameraStatusById( Guid id );
        IList<CameraStatusObject> GetCameraStatusCollection( );
        IList<CameraStatusObject> GetCameraStatusCollectionByCamera( Guid camera );
        CameraStatusObject? GetCameraStatusByCameraAndTimestamp( Guid camera, DateTime timestamp );
        CameraStatusObject? GetCameraStatusByCameraAtTimestamp( Guid camera, DateTime timestamp );
        IList<CameraStatusObject> GetCameraStatusByCameraFromTimestamp( Guid camera, DateTime timestamp );
        IList<CameraStatusObject> GetCameraStatusByCameraUntilTimestamp( Guid camera, DateTime timestamp );
        IList<CameraStatusObject> GetCameraStatusByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraStatusObject> GetCameraStatusCollectionByTrack( Guid? track );
        IList<CameraStatusObject> GetCameraStatusCollectionByTrackIsNull(  );
        CameraStatusObject? GetCameraStatusByTrackAndTimestamp( Guid? track, DateTime timestamp );
        IList<CameraStatusObject> GetCameraStatusCollectionByTrackIsNullAndTimestamp( DateTime timestamp );
        CameraStatusObject? GetCameraStatusByTrackAtTimestamp( Guid? track, DateTime timestamp );
        IList<CameraStatusObject> GetCameraStatusByTrackFromTimestamp( Guid? track, DateTime timestamp );
        IList<CameraStatusObject> GetCameraStatusByTrackUntilTimestamp( Guid? track, DateTime timestamp );
        IList<CameraStatusObject> GetCameraStatusByTrackOverTimestamp( Guid track, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraStatusObject> GetCameraStatusCollectionByTimestamp( DateTime timestamp );
        IList<CameraStatusObject> GetCameraStatusCollectionAtTimestamp( DateTime timestamp );
        IList<CameraStatusObject> GetCameraStatusCollectionFromTimestamp( DateTime timestamp );
        IList<CameraStatusObject> GetCameraStatusCollectionUntilTimestamp( DateTime timestamp );
        IList<CameraStatusObject> GetCameraStatusCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // CameraTiltCalibration queries
        // ---------------------------------------------------------------------
        CameraTiltCalibrationObject? GetCameraTiltCalibrationById( Guid id );
        IList<CameraTiltCalibrationObject> GetCameraTiltCalibrationCollection( );
        IList<CameraTiltCalibrationObject> GetCameraTiltCalibrationCollectionByCamera( Guid camera );
        CameraTiltCalibrationObject? GetCameraTiltCalibrationByCameraAndTimestamp( Guid camera, DateTime timestamp );
        CameraTiltCalibrationObject? GetCameraTiltCalibrationByCameraAtTimestamp( Guid camera, DateTime timestamp );
        IList<CameraTiltCalibrationObject> GetCameraTiltCalibrationByCameraFromTimestamp( Guid camera, DateTime timestamp );
        IList<CameraTiltCalibrationObject> GetCameraTiltCalibrationByCameraUntilTimestamp( Guid camera, DateTime timestamp );
        IList<CameraTiltCalibrationObject> GetCameraTiltCalibrationByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraTiltCalibrationObject> GetCameraTiltCalibrationCollectionByTimestamp( DateTime timestamp );
        IList<CameraTiltCalibrationObject> GetCameraTiltCalibrationCollectionAtTimestamp( DateTime timestamp );
        IList<CameraTiltCalibrationObject> GetCameraTiltCalibrationCollectionFromTimestamp( DateTime timestamp );
        IList<CameraTiltCalibrationObject> GetCameraTiltCalibrationCollectionUntilTimestamp( DateTime timestamp );
        IList<CameraTiltCalibrationObject> GetCameraTiltCalibrationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // CameraTiltCalibrationValue queries
        // ---------------------------------------------------------------------
        CameraTiltCalibrationValueObject? GetCameraTiltCalibrationValueById( Guid id );
        IList<CameraTiltCalibrationValueObject> GetCameraTiltCalibrationValueCollection( );
        IList<CameraTiltCalibrationValueObject> GetCameraTiltCalibrationValueCollectionByTiltCalibration( Guid tiltCalibration );
        CameraTiltCalibrationValueObject? GetCameraTiltCalibrationValueByTiltCalibrationAndPanAngle( Guid tiltCalibration, double panAngle );
        IList<CameraTiltCalibrationValueObject> GetCameraTiltCalibrationValueByTiltCalibrationFromPanAngle( Guid tiltCalibration, double panAngle );
        IList<CameraTiltCalibrationValueObject> GetCameraTiltCalibrationValueByTiltCalibrationUntilPanAngle( Guid tiltCalibration, double panAngle );
        IList<CameraTiltCalibrationValueObject> GetCameraTiltCalibrationValueByTiltCalibrationOverPanAngle( Guid tiltCalibration, double fromPanAngle, double untilPanAngle );
        // ---------------------------------------------------------------------
        // CameraZoomCalibration queries
        // ---------------------------------------------------------------------
        CameraZoomCalibrationObject? GetCameraZoomCalibrationById( Guid id );
        IList<CameraZoomCalibrationObject> GetCameraZoomCalibrationCollection( );
        IList<CameraZoomCalibrationObject> GetCameraZoomCalibrationCollectionByCamera( Guid camera );
        CameraZoomCalibrationObject? GetCameraZoomCalibrationByCameraAndTimestamp( Guid camera, DateTime timestamp );
        CameraZoomCalibrationObject? GetCameraZoomCalibrationByCameraAtTimestamp( Guid camera, DateTime timestamp );
        IList<CameraZoomCalibrationObject> GetCameraZoomCalibrationByCameraFromTimestamp( Guid camera, DateTime timestamp );
        IList<CameraZoomCalibrationObject> GetCameraZoomCalibrationByCameraUntilTimestamp( Guid camera, DateTime timestamp );
        IList<CameraZoomCalibrationObject> GetCameraZoomCalibrationByCameraOverTimestamp( Guid camera, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<CameraZoomCalibrationObject> GetCameraZoomCalibrationCollectionByTimestamp( DateTime timestamp );
        IList<CameraZoomCalibrationObject> GetCameraZoomCalibrationCollectionAtTimestamp( DateTime timestamp );
        IList<CameraZoomCalibrationObject> GetCameraZoomCalibrationCollectionFromTimestamp( DateTime timestamp );
        IList<CameraZoomCalibrationObject> GetCameraZoomCalibrationCollectionUntilTimestamp( DateTime timestamp );
        IList<CameraZoomCalibrationObject> GetCameraZoomCalibrationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // CameraZoomCalibrationValue queries
        // ---------------------------------------------------------------------
        CameraZoomCalibrationValueObject? GetCameraZoomCalibrationValueById( Guid id );
        IList<CameraZoomCalibrationValueObject> GetCameraZoomCalibrationValueCollection( );
        IList<CameraZoomCalibrationValueObject> GetCameraZoomCalibrationValueCollectionByZoomCalibration( Guid zoomCalibration );
        CameraZoomCalibrationValueObject? GetCameraZoomCalibrationValueByZoomCalibrationAndFocalLength( Guid zoomCalibration, double focalLength );
        IList<CameraZoomCalibrationValueObject> GetCameraZoomCalibrationValueByZoomCalibrationFromFocalLength( Guid zoomCalibration, double focalLength );
        IList<CameraZoomCalibrationValueObject> GetCameraZoomCalibrationValueByZoomCalibrationUntilFocalLength( Guid zoomCalibration, double focalLength );
        IList<CameraZoomCalibrationValueObject> GetCameraZoomCalibrationValueByZoomCalibrationOverFocalLength( Guid zoomCalibration, double fromFocalLength, double untilFocalLength );
        // ---------------------------------------------------------------------
        // CatalogElement queries
        // ---------------------------------------------------------------------
        CatalogElementObject? GetCatalogElementById( Guid id );
        IList<CatalogElementObject> GetCatalogElementCollection( );
        IList<CatalogElementObject> GetCatalogElementCollectionByCatalog( Guid? catalog );
        IList<CatalogElementObject> GetCatalogElementCollectionByCatalogIsNull(  );
        CatalogElementObject? GetCatalogElementByCatalogAndName( Guid? catalog, string name );
        IList<CatalogElementObject> GetCatalogElementCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // Catalog queries
        // ---------------------------------------------------------------------
        CatalogObject? GetCatalogById( Guid id );
        IList<CatalogObject> GetCatalogCollection( );
        IList<CatalogObject> GetCatalogCollectionByCatalog( Guid? catalog );
        IList<CatalogObject> GetCatalogCollectionByCatalogIsNull(  );
        CatalogObject? GetCatalogByCatalogAndName( Guid? catalog, string name );
        IList<CatalogObject> GetCatalogCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // Element queries
        // ---------------------------------------------------------------------
        ElementObject? GetElementById( Guid id );
        IList<ElementObject> GetElementCollection( );
        IList<ElementObject> GetElementCollectionByCatalog( Guid? catalog );
        IList<ElementObject> GetElementCollectionByCatalogIsNull(  );
        ElementObject? GetElementByCatalogAndName( Guid? catalog, string name );
        IList<ElementObject> GetElementCollectionByCatalogIsNullAndName( string name );
        IList<ElementObject> GetElementCollectionByElementType( Guid? elementType );
        IList<ElementObject> GetElementCollectionByElementTypeIsNull(  );
        // ---------------------------------------------------------------------
        // CollectionInfo queries
        // ---------------------------------------------------------------------
        CollectionInfoObject? GetCollectionInfoById( Guid id );
        IList<CollectionInfoObject> GetCollectionInfoCollection( );
        // ---------------------------------------------------------------------
        // Country queries
        // ---------------------------------------------------------------------
        CountryObject? GetCountryById( Guid id );
        IList<CountryObject> GetCountryCollection( );
        CountryObject? GetCountryByName( string name );
        CountryObject? GetCountryByCode( int code );
        IList<CountryObject> GetCountryFromCode( int code );
        IList<CountryObject> GetCountryUntilCode( int code );
        IList<CountryObject> GetCountryOverCode( int fromCode, int untilCode );
        CountryObject? GetCountryByAlpha2( string alpha2 );
        CountryObject? GetCountryByAlpha3( string alpha3 );
        // ---------------------------------------------------------------------
        // CursorInfo queries
        // ---------------------------------------------------------------------
        CursorInfoObject? GetCursorInfoById( Guid id );
        IList<CursorInfoObject> GetCursorInfoCollection( );
        // ---------------------------------------------------------------------
        // DateTimeTimeseriesValue queries
        // ---------------------------------------------------------------------
        DateTimeTimeseriesValueObject? GetDateTimeTimeseriesValueById( Guid id );
        IList<DateTimeTimeseriesValueObject> GetDateTimeTimeseriesValueCollection( );
        IList<DateTimeTimeseriesValueObject> GetDateTimeTimeseriesValueCollectionByTimeseries( Guid timeseries );
        DateTimeTimeseriesValueObject? GetDateTimeTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
        DateTimeTimeseriesValueObject? GetDateTimeTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
        IList<DateTimeTimeseriesValueObject> GetDateTimeTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
        IList<DateTimeTimeseriesValueObject> GetDateTimeTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
        IList<DateTimeTimeseriesValueObject> GetDateTimeTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<DateTimeTimeseriesValueObject> GetDateTimeTimeseriesValueCollectionByTimestamp( DateTime timestamp );
        IList<DateTimeTimeseriesValueObject> GetDateTimeTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
        IList<DateTimeTimeseriesValueObject> GetDateTimeTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
        IList<DateTimeTimeseriesValueObject> GetDateTimeTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
        IList<DateTimeTimeseriesValueObject> GetDateTimeTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // DeviceHost queries
        // ---------------------------------------------------------------------
        DeviceHostObject? GetDeviceHostById( Guid id );
        IList<DeviceHostObject> GetDeviceHostCollection( );
        DeviceHostObject? GetDeviceHostByName( string name );
        // ---------------------------------------------------------------------
        // DeviceHostConfiguration queries
        // ---------------------------------------------------------------------
        DeviceHostConfigurationObject? GetDeviceHostConfigurationById( Guid id );
        IList<DeviceHostConfigurationObject> GetDeviceHostConfigurationCollection( );
        IList<DeviceHostConfigurationObject> GetDeviceHostConfigurationCollectionByHost( Guid host );
        DeviceHostConfigurationObject? GetDeviceHostConfigurationByHostAndTimestamp( Guid host, DateTime timestamp );
        DeviceHostConfigurationObject? GetDeviceHostConfigurationByHostAtTimestamp( Guid host, DateTime timestamp );
        IList<DeviceHostConfigurationObject> GetDeviceHostConfigurationByHostFromTimestamp( Guid host, DateTime timestamp );
        IList<DeviceHostConfigurationObject> GetDeviceHostConfigurationByHostUntilTimestamp( Guid host, DateTime timestamp );
        IList<DeviceHostConfigurationObject> GetDeviceHostConfigurationByHostOverTimestamp( Guid host, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<DeviceHostConfigurationObject> GetDeviceHostConfigurationCollectionByTimestamp( DateTime timestamp );
        IList<DeviceHostConfigurationObject> GetDeviceHostConfigurationCollectionAtTimestamp( DateTime timestamp );
        IList<DeviceHostConfigurationObject> GetDeviceHostConfigurationCollectionFromTimestamp( DateTime timestamp );
        IList<DeviceHostConfigurationObject> GetDeviceHostConfigurationCollectionUntilTimestamp( DateTime timestamp );
        IList<DeviceHostConfigurationObject> GetDeviceHostConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // DoubleTimeseriesValue queries
        // ---------------------------------------------------------------------
        DoubleTimeseriesValueObject? GetDoubleTimeseriesValueById( Guid id );
        IList<DoubleTimeseriesValueObject> GetDoubleTimeseriesValueCollection( );
        IList<DoubleTimeseriesValueObject> GetDoubleTimeseriesValueCollectionByTimeseries( Guid timeseries );
        DoubleTimeseriesValueObject? GetDoubleTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
        DoubleTimeseriesValueObject? GetDoubleTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
        IList<DoubleTimeseriesValueObject> GetDoubleTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
        IList<DoubleTimeseriesValueObject> GetDoubleTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
        IList<DoubleTimeseriesValueObject> GetDoubleTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<DoubleTimeseriesValueObject> GetDoubleTimeseriesValueCollectionByTimestamp( DateTime timestamp );
        IList<DoubleTimeseriesValueObject> GetDoubleTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
        IList<DoubleTimeseriesValueObject> GetDoubleTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
        IList<DoubleTimeseriesValueObject> GetDoubleTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
        IList<DoubleTimeseriesValueObject> GetDoubleTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // FacilityType queries
        // ---------------------------------------------------------------------
        FacilityTypeObject? GetFacilityTypeById( Guid id );
        IList<FacilityTypeObject> GetFacilityTypeCollection( );
        FacilityTypeObject? GetFacilityTypeByName( string name );
        // ---------------------------------------------------------------------
        // GeoPosition2DTimeseriesValue queries
        // ---------------------------------------------------------------------
        GeoPosition2DTimeseriesValueObject? GetGeoPosition2DTimeseriesValueById( Guid id );
        IList<GeoPosition2DTimeseriesValueObject> GetGeoPosition2DTimeseriesValueCollection( );
        IList<GeoPosition2DTimeseriesValueObject> GetGeoPosition2DTimeseriesValueCollectionByTimeseries( Guid timeseries );
        GeoPosition2DTimeseriesValueObject? GetGeoPosition2DTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
        GeoPosition2DTimeseriesValueObject? GetGeoPosition2DTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
        IList<GeoPosition2DTimeseriesValueObject> GetGeoPosition2DTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
        IList<GeoPosition2DTimeseriesValueObject> GetGeoPosition2DTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
        IList<GeoPosition2DTimeseriesValueObject> GetGeoPosition2DTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<GeoPosition2DTimeseriesValueObject> GetGeoPosition2DTimeseriesValueCollectionByTimestamp( DateTime timestamp );
        IList<GeoPosition2DTimeseriesValueObject> GetGeoPosition2DTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
        IList<GeoPosition2DTimeseriesValueObject> GetGeoPosition2DTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
        IList<GeoPosition2DTimeseriesValueObject> GetGeoPosition2DTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
        IList<GeoPosition2DTimeseriesValueObject> GetGeoPosition2DTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // GeoPosition3DTimeseriesValue queries
        // ---------------------------------------------------------------------
        GeoPosition3DTimeseriesValueObject? GetGeoPosition3DTimeseriesValueById( Guid id );
        IList<GeoPosition3DTimeseriesValueObject> GetGeoPosition3DTimeseriesValueCollection( );
        IList<GeoPosition3DTimeseriesValueObject> GetGeoPosition3DTimeseriesValueCollectionByTimeseries( Guid timeseries );
        GeoPosition3DTimeseriesValueObject? GetGeoPosition3DTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
        GeoPosition3DTimeseriesValueObject? GetGeoPosition3DTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
        IList<GeoPosition3DTimeseriesValueObject> GetGeoPosition3DTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
        IList<GeoPosition3DTimeseriesValueObject> GetGeoPosition3DTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
        IList<GeoPosition3DTimeseriesValueObject> GetGeoPosition3DTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<GeoPosition3DTimeseriesValueObject> GetGeoPosition3DTimeseriesValueCollectionByTimestamp( DateTime timestamp );
        IList<GeoPosition3DTimeseriesValueObject> GetGeoPosition3DTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
        IList<GeoPosition3DTimeseriesValueObject> GetGeoPosition3DTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
        IList<GeoPosition3DTimeseriesValueObject> GetGeoPosition3DTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
        IList<GeoPosition3DTimeseriesValueObject> GetGeoPosition3DTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // GNSSDeviceCommand queries
        // ---------------------------------------------------------------------
        GNSSDeviceCommandObject? GetGNSSDeviceCommandById( Guid id );
        IList<GNSSDeviceCommandObject> GetGNSSDeviceCommandCollection( );
        IList<GNSSDeviceCommandObject> GetGNSSDeviceCommandCollectionByGNSSDevice( Guid gNSSDevice );
        IList<GNSSDeviceCommandObject> GetGNSSDeviceCommandCollectionByGNSSDeviceAndTimestamp( Guid gNSSDevice, DateTime timestamp );
        IList<GNSSDeviceCommandObject> GetGNSSDeviceCommandCollectionByGNSSDeviceAtTimestamp( Guid gNSSDevice, DateTime timestamp );
        IList<GNSSDeviceCommandObject> GetGNSSDeviceCommandCollectionByGNSSDeviceFromTimestamp( Guid gNSSDevice, DateTime timestamp );
        IList<GNSSDeviceCommandObject> GetGNSSDeviceCommandCollectionByGNSSDeviceUntilTimestamp( Guid gNSSDevice, DateTime timestamp );
        IList<GNSSDeviceCommandObject> GetGNSSDeviceCommandCollectionByGNSSDeviceOverTimestamp( Guid gNSSDevice, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<GNSSDeviceCommandObject> GetGNSSDeviceCommandCollectionByTimestamp( DateTime timestamp );
        IList<GNSSDeviceCommandObject> GetGNSSDeviceCommandCollectionAtTimestamp( DateTime timestamp );
        IList<GNSSDeviceCommandObject> GetGNSSDeviceCommandCollectionFromTimestamp( DateTime timestamp );
        IList<GNSSDeviceCommandObject> GetGNSSDeviceCommandCollectionUntilTimestamp( DateTime timestamp );
        IList<GNSSDeviceCommandObject> GetGNSSDeviceCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<GNSSDeviceCommandObject> GetGNSSDeviceCommandCollectionByReply( Guid? reply );
        IList<GNSSDeviceCommandObject> GetGNSSDeviceCommandCollectionByReplyIsNull(  );
        // ---------------------------------------------------------------------
        // GNSSDeviceCommandReply queries
        // ---------------------------------------------------------------------
        GNSSDeviceCommandReplyObject? GetGNSSDeviceCommandReplyById( Guid id );
        IList<GNSSDeviceCommandReplyObject> GetGNSSDeviceCommandReplyCollection( );
        IList<GNSSDeviceCommandReplyObject> GetGNSSDeviceCommandReplyCollectionByGNSSDevice( Guid gNSSDevice );
        IList<GNSSDeviceCommandReplyObject> GetGNSSDeviceCommandReplyCollectionByGNSSDeviceAndTimestamp( Guid gNSSDevice, DateTime timestamp );
        IList<GNSSDeviceCommandReplyObject> GetGNSSDeviceCommandReplyCollectionByGNSSDeviceAtTimestamp( Guid gNSSDevice, DateTime timestamp );
        IList<GNSSDeviceCommandReplyObject> GetGNSSDeviceCommandReplyCollectionByGNSSDeviceFromTimestamp( Guid gNSSDevice, DateTime timestamp );
        IList<GNSSDeviceCommandReplyObject> GetGNSSDeviceCommandReplyCollectionByGNSSDeviceUntilTimestamp( Guid gNSSDevice, DateTime timestamp );
        IList<GNSSDeviceCommandReplyObject> GetGNSSDeviceCommandReplyCollectionByGNSSDeviceOverTimestamp( Guid gNSSDevice, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<GNSSDeviceCommandReplyObject> GetGNSSDeviceCommandReplyCollectionByTimestamp( DateTime timestamp );
        IList<GNSSDeviceCommandReplyObject> GetGNSSDeviceCommandReplyCollectionAtTimestamp( DateTime timestamp );
        IList<GNSSDeviceCommandReplyObject> GetGNSSDeviceCommandReplyCollectionFromTimestamp( DateTime timestamp );
        IList<GNSSDeviceCommandReplyObject> GetGNSSDeviceCommandReplyCollectionUntilTimestamp( DateTime timestamp );
        IList<GNSSDeviceCommandReplyObject> GetGNSSDeviceCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        GNSSDeviceCommandReplyObject? GetGNSSDeviceCommandReplyByCommand( Guid? command );
        IList<GNSSDeviceCommandReplyObject> GetGNSSDeviceCommandReplyCollectionByCommandIsNull(  );
        // ---------------------------------------------------------------------
        // GNSSDeviceConfiguration queries
        // ---------------------------------------------------------------------
        GNSSDeviceConfigurationObject? GetGNSSDeviceConfigurationById( Guid id );
        IList<GNSSDeviceConfigurationObject> GetGNSSDeviceConfigurationCollection( );
        IList<GNSSDeviceConfigurationObject> GetGNSSDeviceConfigurationCollectionByGNSSDevice( Guid gNSSDevice );
        GNSSDeviceConfigurationObject? GetGNSSDeviceConfigurationByGNSSDeviceAndTimestamp( Guid gNSSDevice, DateTime timestamp );
        GNSSDeviceConfigurationObject? GetGNSSDeviceConfigurationByGNSSDeviceAtTimestamp( Guid gNSSDevice, DateTime timestamp );
        IList<GNSSDeviceConfigurationObject> GetGNSSDeviceConfigurationByGNSSDeviceFromTimestamp( Guid gNSSDevice, DateTime timestamp );
        IList<GNSSDeviceConfigurationObject> GetGNSSDeviceConfigurationByGNSSDeviceUntilTimestamp( Guid gNSSDevice, DateTime timestamp );
        IList<GNSSDeviceConfigurationObject> GetGNSSDeviceConfigurationByGNSSDeviceOverTimestamp( Guid gNSSDevice, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<GNSSDeviceConfigurationObject> GetGNSSDeviceConfigurationCollectionByTimestamp( DateTime timestamp );
        IList<GNSSDeviceConfigurationObject> GetGNSSDeviceConfigurationCollectionAtTimestamp( DateTime timestamp );
        IList<GNSSDeviceConfigurationObject> GetGNSSDeviceConfigurationCollectionFromTimestamp( DateTime timestamp );
        IList<GNSSDeviceConfigurationObject> GetGNSSDeviceConfigurationCollectionUntilTimestamp( DateTime timestamp );
        IList<GNSSDeviceConfigurationObject> GetGNSSDeviceConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // GuidTimeseriesValue queries
        // ---------------------------------------------------------------------
        GuidTimeseriesValueObject? GetGuidTimeseriesValueById( Guid id );
        IList<GuidTimeseriesValueObject> GetGuidTimeseriesValueCollection( );
        IList<GuidTimeseriesValueObject> GetGuidTimeseriesValueCollectionByTimeseries( Guid timeseries );
        GuidTimeseriesValueObject? GetGuidTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
        GuidTimeseriesValueObject? GetGuidTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
        IList<GuidTimeseriesValueObject> GetGuidTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
        IList<GuidTimeseriesValueObject> GetGuidTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
        IList<GuidTimeseriesValueObject> GetGuidTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<GuidTimeseriesValueObject> GetGuidTimeseriesValueCollectionByTimestamp( DateTime timestamp );
        IList<GuidTimeseriesValueObject> GetGuidTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
        IList<GuidTimeseriesValueObject> GetGuidTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
        IList<GuidTimeseriesValueObject> GetGuidTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
        IList<GuidTimeseriesValueObject> GetGuidTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // GyroDeviceCommand queries
        // ---------------------------------------------------------------------
        GyroDeviceCommandObject? GetGyroDeviceCommandById( Guid id );
        IList<GyroDeviceCommandObject> GetGyroDeviceCommandCollection( );
        IList<GyroDeviceCommandObject> GetGyroDeviceCommandCollectionByGyroDevice( Guid gyroDevice );
        IList<GyroDeviceCommandObject> GetGyroDeviceCommandCollectionByGyroDeviceAndTimestamp( Guid gyroDevice, DateTime timestamp );
        IList<GyroDeviceCommandObject> GetGyroDeviceCommandCollectionByGyroDeviceAtTimestamp( Guid gyroDevice, DateTime timestamp );
        IList<GyroDeviceCommandObject> GetGyroDeviceCommandCollectionByGyroDeviceFromTimestamp( Guid gyroDevice, DateTime timestamp );
        IList<GyroDeviceCommandObject> GetGyroDeviceCommandCollectionByGyroDeviceUntilTimestamp( Guid gyroDevice, DateTime timestamp );
        IList<GyroDeviceCommandObject> GetGyroDeviceCommandCollectionByGyroDeviceOverTimestamp( Guid gyroDevice, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<GyroDeviceCommandObject> GetGyroDeviceCommandCollectionByTimestamp( DateTime timestamp );
        IList<GyroDeviceCommandObject> GetGyroDeviceCommandCollectionAtTimestamp( DateTime timestamp );
        IList<GyroDeviceCommandObject> GetGyroDeviceCommandCollectionFromTimestamp( DateTime timestamp );
        IList<GyroDeviceCommandObject> GetGyroDeviceCommandCollectionUntilTimestamp( DateTime timestamp );
        IList<GyroDeviceCommandObject> GetGyroDeviceCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<GyroDeviceCommandObject> GetGyroDeviceCommandCollectionByReply( Guid? reply );
        IList<GyroDeviceCommandObject> GetGyroDeviceCommandCollectionByReplyIsNull(  );
        // ---------------------------------------------------------------------
        // GyroDeviceCommandReply queries
        // ---------------------------------------------------------------------
        GyroDeviceCommandReplyObject? GetGyroDeviceCommandReplyById( Guid id );
        IList<GyroDeviceCommandReplyObject> GetGyroDeviceCommandReplyCollection( );
        IList<GyroDeviceCommandReplyObject> GetGyroDeviceCommandReplyCollectionByGyroDevice( Guid gyroDevice );
        IList<GyroDeviceCommandReplyObject> GetGyroDeviceCommandReplyCollectionByGyroDeviceAndTimestamp( Guid gyroDevice, DateTime timestamp );
        IList<GyroDeviceCommandReplyObject> GetGyroDeviceCommandReplyCollectionByGyroDeviceAtTimestamp( Guid gyroDevice, DateTime timestamp );
        IList<GyroDeviceCommandReplyObject> GetGyroDeviceCommandReplyCollectionByGyroDeviceFromTimestamp( Guid gyroDevice, DateTime timestamp );
        IList<GyroDeviceCommandReplyObject> GetGyroDeviceCommandReplyCollectionByGyroDeviceUntilTimestamp( Guid gyroDevice, DateTime timestamp );
        IList<GyroDeviceCommandReplyObject> GetGyroDeviceCommandReplyCollectionByGyroDeviceOverTimestamp( Guid gyroDevice, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<GyroDeviceCommandReplyObject> GetGyroDeviceCommandReplyCollectionByTimestamp( DateTime timestamp );
        IList<GyroDeviceCommandReplyObject> GetGyroDeviceCommandReplyCollectionAtTimestamp( DateTime timestamp );
        IList<GyroDeviceCommandReplyObject> GetGyroDeviceCommandReplyCollectionFromTimestamp( DateTime timestamp );
        IList<GyroDeviceCommandReplyObject> GetGyroDeviceCommandReplyCollectionUntilTimestamp( DateTime timestamp );
        IList<GyroDeviceCommandReplyObject> GetGyroDeviceCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        GyroDeviceCommandReplyObject? GetGyroDeviceCommandReplyByCommand( Guid? command );
        IList<GyroDeviceCommandReplyObject> GetGyroDeviceCommandReplyCollectionByCommandIsNull(  );
        // ---------------------------------------------------------------------
        // GyroDeviceConfiguration queries
        // ---------------------------------------------------------------------
        GyroDeviceConfigurationObject? GetGyroDeviceConfigurationById( Guid id );
        IList<GyroDeviceConfigurationObject> GetGyroDeviceConfigurationCollection( );
        IList<GyroDeviceConfigurationObject> GetGyroDeviceConfigurationCollectionByGyroDevice( Guid gyroDevice );
        GyroDeviceConfigurationObject? GetGyroDeviceConfigurationByGyroDeviceAndTimestamp( Guid gyroDevice, DateTime timestamp );
        GyroDeviceConfigurationObject? GetGyroDeviceConfigurationByGyroDeviceAtTimestamp( Guid gyroDevice, DateTime timestamp );
        IList<GyroDeviceConfigurationObject> GetGyroDeviceConfigurationByGyroDeviceFromTimestamp( Guid gyroDevice, DateTime timestamp );
        IList<GyroDeviceConfigurationObject> GetGyroDeviceConfigurationByGyroDeviceUntilTimestamp( Guid gyroDevice, DateTime timestamp );
        IList<GyroDeviceConfigurationObject> GetGyroDeviceConfigurationByGyroDeviceOverTimestamp( Guid gyroDevice, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<GyroDeviceConfigurationObject> GetGyroDeviceConfigurationCollectionByTimestamp( DateTime timestamp );
        IList<GyroDeviceConfigurationObject> GetGyroDeviceConfigurationCollectionAtTimestamp( DateTime timestamp );
        IList<GyroDeviceConfigurationObject> GetGyroDeviceConfigurationCollectionFromTimestamp( DateTime timestamp );
        IList<GyroDeviceConfigurationObject> GetGyroDeviceConfigurationCollectionUntilTimestamp( DateTime timestamp );
        IList<GyroDeviceConfigurationObject> GetGyroDeviceConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // Identity queries
        // ---------------------------------------------------------------------
        IdentityObject? GetIdentityById( Guid id );
        IList<IdentityObject> GetIdentityCollection( );
        // ---------------------------------------------------------------------
        // Callsign queries
        // ---------------------------------------------------------------------
        CallsignObject? GetCallsignById( Guid id );
        IList<CallsignObject> GetCallsignCollection( );
        CallsignObject? GetCallsignByIdentifier( string identifier );
        // ---------------------------------------------------------------------
        // InternationalMaritimeOrganizationNumber queries
        // ---------------------------------------------------------------------
        InternationalMaritimeOrganizationNumberObject? GetInternationalMaritimeOrganizationNumberById( Guid id );
        IList<InternationalMaritimeOrganizationNumberObject> GetInternationalMaritimeOrganizationNumberCollection( );
        InternationalMaritimeOrganizationNumberObject? GetInternationalMaritimeOrganizationNumberByIdentifier( long identifier );
        IList<InternationalMaritimeOrganizationNumberObject> GetInternationalMaritimeOrganizationNumberFromIdentifier( long identifier );
        IList<InternationalMaritimeOrganizationNumberObject> GetInternationalMaritimeOrganizationNumberUntilIdentifier( long identifier );
        IList<InternationalMaritimeOrganizationNumberObject> GetInternationalMaritimeOrganizationNumberOverIdentifier( long fromIdentifier, long untilIdentifier );
        // ---------------------------------------------------------------------
        // MaritimeMobileServiceIdentity queries
        // ---------------------------------------------------------------------
        MaritimeMobileServiceIdentityObject? GetMaritimeMobileServiceIdentityById( Guid id );
        IList<MaritimeMobileServiceIdentityObject> GetMaritimeMobileServiceIdentityCollection( );
        MaritimeMobileServiceIdentityObject? GetMaritimeMobileServiceIdentityByIdentifier( long identifier );
        IList<MaritimeMobileServiceIdentityObject> GetMaritimeMobileServiceIdentityFromIdentifier( long identifier );
        IList<MaritimeMobileServiceIdentityObject> GetMaritimeMobileServiceIdentityUntilIdentifier( long identifier );
        IList<MaritimeMobileServiceIdentityObject> GetMaritimeMobileServiceIdentityOverIdentifier( long fromIdentifier, long untilIdentifier );
        // ---------------------------------------------------------------------
        // Name queries
        // ---------------------------------------------------------------------
        NameObject? GetNameById( Guid id );
        IList<NameObject> GetNameCollection( );
        NameObject? GetNameByText( string text );
        // ---------------------------------------------------------------------
        // Int16TimeseriesValue queries
        // ---------------------------------------------------------------------
        Int16TimeseriesValueObject? GetInt16TimeseriesValueById( Guid id );
        IList<Int16TimeseriesValueObject> GetInt16TimeseriesValueCollection( );
        IList<Int16TimeseriesValueObject> GetInt16TimeseriesValueCollectionByTimeseries( Guid timeseries );
        Int16TimeseriesValueObject? GetInt16TimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
        Int16TimeseriesValueObject? GetInt16TimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
        IList<Int16TimeseriesValueObject> GetInt16TimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
        IList<Int16TimeseriesValueObject> GetInt16TimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
        IList<Int16TimeseriesValueObject> GetInt16TimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<Int16TimeseriesValueObject> GetInt16TimeseriesValueCollectionByTimestamp( DateTime timestamp );
        IList<Int16TimeseriesValueObject> GetInt16TimeseriesValueCollectionAtTimestamp( DateTime timestamp );
        IList<Int16TimeseriesValueObject> GetInt16TimeseriesValueCollectionFromTimestamp( DateTime timestamp );
        IList<Int16TimeseriesValueObject> GetInt16TimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
        IList<Int16TimeseriesValueObject> GetInt16TimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // Int32TimeseriesValue queries
        // ---------------------------------------------------------------------
        Int32TimeseriesValueObject? GetInt32TimeseriesValueById( Guid id );
        IList<Int32TimeseriesValueObject> GetInt32TimeseriesValueCollection( );
        IList<Int32TimeseriesValueObject> GetInt32TimeseriesValueCollectionByTimeseries( Guid timeseries );
        Int32TimeseriesValueObject? GetInt32TimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
        Int32TimeseriesValueObject? GetInt32TimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
        IList<Int32TimeseriesValueObject> GetInt32TimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
        IList<Int32TimeseriesValueObject> GetInt32TimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
        IList<Int32TimeseriesValueObject> GetInt32TimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<Int32TimeseriesValueObject> GetInt32TimeseriesValueCollectionByTimestamp( DateTime timestamp );
        IList<Int32TimeseriesValueObject> GetInt32TimeseriesValueCollectionAtTimestamp( DateTime timestamp );
        IList<Int32TimeseriesValueObject> GetInt32TimeseriesValueCollectionFromTimestamp( DateTime timestamp );
        IList<Int32TimeseriesValueObject> GetInt32TimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
        IList<Int32TimeseriesValueObject> GetInt32TimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // Int64TimeseriesValue queries
        // ---------------------------------------------------------------------
        Int64TimeseriesValueObject? GetInt64TimeseriesValueById( Guid id );
        IList<Int64TimeseriesValueObject> GetInt64TimeseriesValueCollection( );
        IList<Int64TimeseriesValueObject> GetInt64TimeseriesValueCollectionByTimeseries( Guid timeseries );
        Int64TimeseriesValueObject? GetInt64TimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
        Int64TimeseriesValueObject? GetInt64TimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
        IList<Int64TimeseriesValueObject> GetInt64TimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
        IList<Int64TimeseriesValueObject> GetInt64TimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
        IList<Int64TimeseriesValueObject> GetInt64TimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<Int64TimeseriesValueObject> GetInt64TimeseriesValueCollectionByTimestamp( DateTime timestamp );
        IList<Int64TimeseriesValueObject> GetInt64TimeseriesValueCollectionAtTimestamp( DateTime timestamp );
        IList<Int64TimeseriesValueObject> GetInt64TimeseriesValueCollectionFromTimestamp( DateTime timestamp );
        IList<Int64TimeseriesValueObject> GetInt64TimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
        IList<Int64TimeseriesValueObject> GetInt64TimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // Item queries
        // ---------------------------------------------------------------------
        ItemObject? GetItemById( Guid id );
        IList<ItemObject> GetItemCollection( );
        // ---------------------------------------------------------------------
        // BaseStation queries
        // ---------------------------------------------------------------------
        BaseStationObject? GetBaseStationById( Guid id );
        IList<BaseStationObject> GetBaseStationCollection( );
        BaseStationObject? GetBaseStationByName( string name );
        IList<BaseStationObject> GetBaseStationCollectionByType( Guid? type );
        IList<BaseStationObject> GetBaseStationCollectionByTypeIsNull(  );
        // ---------------------------------------------------------------------
        // Device queries
        // ---------------------------------------------------------------------
        DeviceObject? GetDeviceById( Guid id );
        IList<DeviceObject> GetDeviceCollection( );
        IList<DeviceObject> GetDeviceCollectionByHost( Guid host );
        DeviceObject? GetDeviceByName( string name );
        // ---------------------------------------------------------------------
        // CameraDevice queries
        // ---------------------------------------------------------------------
        CameraDeviceObject? GetCameraDeviceById( Guid id );
        IList<CameraDeviceObject> GetCameraDeviceCollection( );
        IList<CameraDeviceObject> GetCameraDeviceCollectionByHost( Guid host );
        CameraDeviceObject? GetCameraDeviceByName( string name );
        // ---------------------------------------------------------------------
        // GNSSDevice queries
        // ---------------------------------------------------------------------
        GNSSDeviceObject? GetGNSSDeviceById( Guid id );
        IList<GNSSDeviceObject> GetGNSSDeviceCollection( );
        IList<GNSSDeviceObject> GetGNSSDeviceCollectionByHost( Guid host );
        GNSSDeviceObject? GetGNSSDeviceByName( string name );
        // ---------------------------------------------------------------------
        // GyroDevice queries
        // ---------------------------------------------------------------------
        GyroDeviceObject? GetGyroDeviceById( Guid id );
        IList<GyroDeviceObject> GetGyroDeviceCollection( );
        IList<GyroDeviceObject> GetGyroDeviceCollectionByHost( Guid host );
        GyroDeviceObject? GetGyroDeviceByName( string name );
        IList<GyroDeviceObject> GetGyroDeviceCollectionByGNSSDevice( Guid? gNSSDevice );
        IList<GyroDeviceObject> GetGyroDeviceCollectionByGNSSDeviceIsNull(  );
        // ---------------------------------------------------------------------
        // LineInputDevice queries
        // ---------------------------------------------------------------------
        LineInputDeviceObject? GetLineInputDeviceById( Guid id );
        IList<LineInputDeviceObject> GetLineInputDeviceCollection( );
        IList<LineInputDeviceObject> GetLineInputDeviceCollectionByHost( Guid host );
        LineInputDeviceObject? GetLineInputDeviceByName( string name );
        // ---------------------------------------------------------------------
        // OilSpillDetectorDevice queries
        // ---------------------------------------------------------------------
        OilSpillDetectorDeviceObject? GetOilSpillDetectorDeviceById( Guid id );
        IList<OilSpillDetectorDeviceObject> GetOilSpillDetectorDeviceCollection( );
        IList<OilSpillDetectorDeviceObject> GetOilSpillDetectorDeviceCollectionByHost( Guid host );
        OilSpillDetectorDeviceObject? GetOilSpillDetectorDeviceByName( string name );
        // ---------------------------------------------------------------------
        // RadioDevice queries
        // ---------------------------------------------------------------------
        RadioDeviceObject? GetRadioDeviceById( Guid id );
        IList<RadioDeviceObject> GetRadioDeviceCollection( );
        IList<RadioDeviceObject> GetRadioDeviceCollectionByHost( Guid host );
        RadioDeviceObject? GetRadioDeviceByName( string name );
        // ---------------------------------------------------------------------
        // RadomeDevice queries
        // ---------------------------------------------------------------------
        RadomeDeviceObject? GetRadomeDeviceById( Guid id );
        IList<RadomeDeviceObject> GetRadomeDeviceCollection( );
        IList<RadomeDeviceObject> GetRadomeDeviceCollectionByHost( Guid host );
        RadomeDeviceObject? GetRadomeDeviceByName( string name );
        IList<RadomeDeviceObject> GetRadomeDeviceCollectionByRadar( Guid? radar );
        IList<RadomeDeviceObject> GetRadomeDeviceCollectionByRadarIsNull(  );
        // ---------------------------------------------------------------------
        // TrackerDevice queries
        // ---------------------------------------------------------------------
        TrackerDeviceObject? GetTrackerDeviceById( Guid id );
        IList<TrackerDeviceObject> GetTrackerDeviceCollection( );
        IList<TrackerDeviceObject> GetTrackerDeviceCollectionByHost( Guid host );
        TrackerDeviceObject? GetTrackerDeviceByName( string name );
        // ---------------------------------------------------------------------
        // AisDevice queries
        // ---------------------------------------------------------------------
        AisDeviceObject? GetAisDeviceById( Guid id );
        IList<AisDeviceObject> GetAisDeviceCollection( );
        IList<AisDeviceObject> GetAisDeviceCollectionByHost( Guid host );
        AisDeviceObject? GetAisDeviceByName( string name );
        // ---------------------------------------------------------------------
        // RadarDevice queries
        // ---------------------------------------------------------------------
        RadarDeviceObject? GetRadarDeviceById( Guid id );
        IList<RadarDeviceObject> GetRadarDeviceCollection( );
        IList<RadarDeviceObject> GetRadarDeviceCollectionByHost( Guid host );
        RadarDeviceObject? GetRadarDeviceByName( string name );
        IList<RadarDeviceObject> GetRadarDeviceCollectionByRadome( Guid? radome );
        IList<RadarDeviceObject> GetRadarDeviceCollectionByRadomeIsNull(  );
        IList<RadarDeviceObject> GetRadarDeviceCollectionByGNSSDevice( Guid? gNSSDevice );
        IList<RadarDeviceObject> GetRadarDeviceCollectionByGNSSDeviceIsNull(  );
        // ---------------------------------------------------------------------
        // WeatherStationDevice queries
        // ---------------------------------------------------------------------
        WeatherStationDeviceObject? GetWeatherStationDeviceById( Guid id );
        IList<WeatherStationDeviceObject> GetWeatherStationDeviceCollection( );
        IList<WeatherStationDeviceObject> GetWeatherStationDeviceCollectionByHost( Guid host );
        WeatherStationDeviceObject? GetWeatherStationDeviceByName( string name );
        IList<WeatherStationDeviceObject> GetWeatherStationDeviceCollectionByGyro( Guid? gyro );
        IList<WeatherStationDeviceObject> GetWeatherStationDeviceCollectionByGyroIsNull(  );
        // ---------------------------------------------------------------------
        // Facility queries
        // ---------------------------------------------------------------------
        FacilityObject? GetFacilityById( Guid id );
        IList<FacilityObject> GetFacilityCollection( );
        FacilityObject? GetFacilityByName( string name );
        IList<FacilityObject> GetFacilityCollectionByType( Guid? type );
        IList<FacilityObject> GetFacilityCollectionByTypeIsNull(  );
        // ---------------------------------------------------------------------
        // TrackableItem queries
        // ---------------------------------------------------------------------
        TrackableItemObject? GetTrackableItemById( Guid id );
        IList<TrackableItemObject> GetTrackableItemCollection( );
        // ---------------------------------------------------------------------
        // Aircraft queries
        // ---------------------------------------------------------------------
        AircraftObject? GetAircraftById( Guid id );
        IList<AircraftObject> GetAircraftCollection( );
        IList<AircraftObject> GetAircraftCollectionByName( string name );
        IList<AircraftObject> GetAircraftCollectionByType( Guid? type );
        IList<AircraftObject> GetAircraftCollectionByTypeIsNull(  );
        // ---------------------------------------------------------------------
        // AisAidToNavigation queries
        // ---------------------------------------------------------------------
        AisAidToNavigationObject? GetAisAidToNavigationById( Guid id );
        IList<AisAidToNavigationObject> GetAisAidToNavigationCollection( );
        AisAidToNavigationObject? GetAisAidToNavigationByName( string name );
        IList<AisAidToNavigationObject> GetAisAidToNavigationCollectionByMMSI( Guid? mMSI );
        IList<AisAidToNavigationObject> GetAisAidToNavigationCollectionByMMSIIsNull(  );
        // ---------------------------------------------------------------------
        // Vehicle queries
        // ---------------------------------------------------------------------
        VehicleObject? GetVehicleById( Guid id );
        IList<VehicleObject> GetVehicleCollection( );
        VehicleObject? GetVehicleByName( string name );
        IList<VehicleObject> GetVehicleCollectionByType( Guid? type );
        IList<VehicleObject> GetVehicleCollectionByTypeIsNull(  );
        // ---------------------------------------------------------------------
        // Vessel queries
        // ---------------------------------------------------------------------
        VesselObject? GetVesselById( Guid id );
        IList<VesselObject> GetVesselCollection( );
        IList<VesselObject> GetVesselCollectionByName( string name );
        IList<VesselObject> GetVesselCollectionByType( Guid? type );
        IList<VesselObject> GetVesselCollectionByTypeIsNull(  );
        // ---------------------------------------------------------------------
        // ItemIdentityLink queries
        // ---------------------------------------------------------------------
        ItemIdentityLinkObject? GetItemIdentityLinkById( Guid id );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollection( );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByItem( Guid item );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByItemAndStart( Guid item, DateTime start );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByItemAtStart( Guid item, DateTime start );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByItemFromStart( Guid item, DateTime start );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByItemUntilStart( Guid item, DateTime start );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByItemOverStart( Guid item, DateTime fromStart, DateTime untilStart );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByItemAndEnd( Guid item, DateTime? end );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByItemAndEndIsNull( Guid item );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByItemAtEnd( Guid item, DateTime? end );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByItemFromEnd( Guid item, DateTime? end );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByItemUntilEnd( Guid item, DateTime? end );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByItemOverEnd( Guid item, DateTime fromEnd, DateTime untilEnd );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByIdentity( Guid identity );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByIdentityAndStart( Guid identity, DateTime start );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByIdentityAtStart( Guid identity, DateTime start );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByIdentityFromStart( Guid identity, DateTime start );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByIdentityUntilStart( Guid identity, DateTime start );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByIdentityOverStart( Guid identity, DateTime fromStart, DateTime untilStart );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByIdentityAndEnd( Guid identity, DateTime? end );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByIdentityAndEndIsNull( Guid identity );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByIdentityAtEnd( Guid identity, DateTime? end );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByIdentityFromEnd( Guid identity, DateTime? end );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByIdentityUntilEnd( Guid identity, DateTime? end );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByIdentityOverEnd( Guid identity, DateTime fromEnd, DateTime untilEnd );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByStart( DateTime start );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionAtStart( DateTime start );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionFromStart( DateTime start );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionUntilStart( DateTime start );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionOverStart( DateTime fromStart, DateTime untilStart );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByEnd( DateTime? end );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionByEndIsNull(  );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionAtEnd( DateTime? end );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionFromEnd( DateTime? end );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionUntilEnd( DateTime? end );
        IList<ItemIdentityLinkObject> GetItemIdentityLinkCollectionOverEnd( DateTime fromEnd, DateTime untilEnd );
        // ---------------------------------------------------------------------
        // ItemParentChildLink queries
        // ---------------------------------------------------------------------
        ItemParentChildLinkObject? GetItemParentChildLinkById( Guid id );
        IList<ItemParentChildLinkObject> GetItemParentChildLinkCollection( );
        IList<ItemParentChildLinkObject> GetItemParentChildLinkCollectionByParent( Guid parent );
        ItemParentChildLinkObject? GetItemParentChildLinkByParentAndTimestamp( Guid parent, DateTime timestamp );
        ItemParentChildLinkObject? GetItemParentChildLinkByParentAtTimestamp( Guid parent, DateTime timestamp );
        IList<ItemParentChildLinkObject> GetItemParentChildLinkByParentFromTimestamp( Guid parent, DateTime timestamp );
        IList<ItemParentChildLinkObject> GetItemParentChildLinkByParentUntilTimestamp( Guid parent, DateTime timestamp );
        IList<ItemParentChildLinkObject> GetItemParentChildLinkByParentOverTimestamp( Guid parent, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<ItemParentChildLinkObject> GetItemParentChildLinkCollectionByChild( Guid child );
        ItemParentChildLinkObject? GetItemParentChildLinkByChildAndTimestamp( Guid child, DateTime timestamp );
        ItemParentChildLinkObject? GetItemParentChildLinkByChildAtTimestamp( Guid child, DateTime timestamp );
        IList<ItemParentChildLinkObject> GetItemParentChildLinkByChildFromTimestamp( Guid child, DateTime timestamp );
        IList<ItemParentChildLinkObject> GetItemParentChildLinkByChildUntilTimestamp( Guid child, DateTime timestamp );
        IList<ItemParentChildLinkObject> GetItemParentChildLinkByChildOverTimestamp( Guid child, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<ItemParentChildLinkObject> GetItemParentChildLinkCollectionByTimestamp( DateTime timestamp );
        IList<ItemParentChildLinkObject> GetItemParentChildLinkCollectionAtTimestamp( DateTime timestamp );
        IList<ItemParentChildLinkObject> GetItemParentChildLinkCollectionFromTimestamp( DateTime timestamp );
        IList<ItemParentChildLinkObject> GetItemParentChildLinkCollectionUntilTimestamp( DateTime timestamp );
        IList<ItemParentChildLinkObject> GetItemParentChildLinkCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // LineInputDeviceCommand queries
        // ---------------------------------------------------------------------
        LineInputDeviceCommandObject? GetLineInputDeviceCommandById( Guid id );
        IList<LineInputDeviceCommandObject> GetLineInputDeviceCommandCollection( );
        IList<LineInputDeviceCommandObject> GetLineInputDeviceCommandCollectionByLineInputDevice( Guid lineInputDevice );
        IList<LineInputDeviceCommandObject> GetLineInputDeviceCommandCollectionByLineInputDeviceAndTimestamp( Guid lineInputDevice, DateTime timestamp );
        IList<LineInputDeviceCommandObject> GetLineInputDeviceCommandCollectionByLineInputDeviceAtTimestamp( Guid lineInputDevice, DateTime timestamp );
        IList<LineInputDeviceCommandObject> GetLineInputDeviceCommandCollectionByLineInputDeviceFromTimestamp( Guid lineInputDevice, DateTime timestamp );
        IList<LineInputDeviceCommandObject> GetLineInputDeviceCommandCollectionByLineInputDeviceUntilTimestamp( Guid lineInputDevice, DateTime timestamp );
        IList<LineInputDeviceCommandObject> GetLineInputDeviceCommandCollectionByLineInputDeviceOverTimestamp( Guid lineInputDevice, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<LineInputDeviceCommandObject> GetLineInputDeviceCommandCollectionByTimestamp( DateTime timestamp );
        IList<LineInputDeviceCommandObject> GetLineInputDeviceCommandCollectionAtTimestamp( DateTime timestamp );
        IList<LineInputDeviceCommandObject> GetLineInputDeviceCommandCollectionFromTimestamp( DateTime timestamp );
        IList<LineInputDeviceCommandObject> GetLineInputDeviceCommandCollectionUntilTimestamp( DateTime timestamp );
        IList<LineInputDeviceCommandObject> GetLineInputDeviceCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<LineInputDeviceCommandObject> GetLineInputDeviceCommandCollectionByReply( Guid? reply );
        IList<LineInputDeviceCommandObject> GetLineInputDeviceCommandCollectionByReplyIsNull(  );
        // ---------------------------------------------------------------------
        // LineInputDeviceCommandReply queries
        // ---------------------------------------------------------------------
        LineInputDeviceCommandReplyObject? GetLineInputDeviceCommandReplyById( Guid id );
        IList<LineInputDeviceCommandReplyObject> GetLineInputDeviceCommandReplyCollection( );
        IList<LineInputDeviceCommandReplyObject> GetLineInputDeviceCommandReplyCollectionByLineInputDevice( Guid lineInputDevice );
        IList<LineInputDeviceCommandReplyObject> GetLineInputDeviceCommandReplyCollectionByLineInputDeviceAndTimestamp( Guid lineInputDevice, DateTime timestamp );
        IList<LineInputDeviceCommandReplyObject> GetLineInputDeviceCommandReplyCollectionByLineInputDeviceAtTimestamp( Guid lineInputDevice, DateTime timestamp );
        IList<LineInputDeviceCommandReplyObject> GetLineInputDeviceCommandReplyCollectionByLineInputDeviceFromTimestamp( Guid lineInputDevice, DateTime timestamp );
        IList<LineInputDeviceCommandReplyObject> GetLineInputDeviceCommandReplyCollectionByLineInputDeviceUntilTimestamp( Guid lineInputDevice, DateTime timestamp );
        IList<LineInputDeviceCommandReplyObject> GetLineInputDeviceCommandReplyCollectionByLineInputDeviceOverTimestamp( Guid lineInputDevice, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<LineInputDeviceCommandReplyObject> GetLineInputDeviceCommandReplyCollectionByTimestamp( DateTime timestamp );
        IList<LineInputDeviceCommandReplyObject> GetLineInputDeviceCommandReplyCollectionAtTimestamp( DateTime timestamp );
        IList<LineInputDeviceCommandReplyObject> GetLineInputDeviceCommandReplyCollectionFromTimestamp( DateTime timestamp );
        IList<LineInputDeviceCommandReplyObject> GetLineInputDeviceCommandReplyCollectionUntilTimestamp( DateTime timestamp );
        IList<LineInputDeviceCommandReplyObject> GetLineInputDeviceCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        LineInputDeviceCommandReplyObject? GetLineInputDeviceCommandReplyByCommand( Guid? command );
        IList<LineInputDeviceCommandReplyObject> GetLineInputDeviceCommandReplyCollectionByCommandIsNull(  );
        // ---------------------------------------------------------------------
        // LineInputDeviceConfiguration queries
        // ---------------------------------------------------------------------
        LineInputDeviceConfigurationObject? GetLineInputDeviceConfigurationById( Guid id );
        IList<LineInputDeviceConfigurationObject> GetLineInputDeviceConfigurationCollection( );
        IList<LineInputDeviceConfigurationObject> GetLineInputDeviceConfigurationCollectionByLineInputDevice( Guid lineInputDevice );
        LineInputDeviceConfigurationObject? GetLineInputDeviceConfigurationByLineInputDeviceAndTimestamp( Guid lineInputDevice, DateTime timestamp );
        LineInputDeviceConfigurationObject? GetLineInputDeviceConfigurationByLineInputDeviceAtTimestamp( Guid lineInputDevice, DateTime timestamp );
        IList<LineInputDeviceConfigurationObject> GetLineInputDeviceConfigurationByLineInputDeviceFromTimestamp( Guid lineInputDevice, DateTime timestamp );
        IList<LineInputDeviceConfigurationObject> GetLineInputDeviceConfigurationByLineInputDeviceUntilTimestamp( Guid lineInputDevice, DateTime timestamp );
        IList<LineInputDeviceConfigurationObject> GetLineInputDeviceConfigurationByLineInputDeviceOverTimestamp( Guid lineInputDevice, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<LineInputDeviceConfigurationObject> GetLineInputDeviceConfigurationCollectionByTimestamp( DateTime timestamp );
        IList<LineInputDeviceConfigurationObject> GetLineInputDeviceConfigurationCollectionAtTimestamp( DateTime timestamp );
        IList<LineInputDeviceConfigurationObject> GetLineInputDeviceConfigurationCollectionFromTimestamp( DateTime timestamp );
        IList<LineInputDeviceConfigurationObject> GetLineInputDeviceConfigurationCollectionUntilTimestamp( DateTime timestamp );
        IList<LineInputDeviceConfigurationObject> GetLineInputDeviceConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // LineInputMessageRouting queries
        // ---------------------------------------------------------------------
        LineInputMessageRoutingObject? GetLineInputMessageRoutingById( Guid id );
        IList<LineInputMessageRoutingObject> GetLineInputMessageRoutingCollection( );
        IList<LineInputMessageRoutingObject> GetLineInputMessageRoutingCollectionByLineInputDevice( Guid lineInputDevice );
        LineInputMessageRoutingObject? GetLineInputMessageRoutingByLineInputDeviceAndType( Guid lineInputDevice, string type );
        // ---------------------------------------------------------------------
        // LineInputMessageRoutingDestination queries
        // ---------------------------------------------------------------------
        LineInputMessageRoutingDestinationObject? GetLineInputMessageRoutingDestinationById( Guid id );
        IList<LineInputMessageRoutingDestinationObject> GetLineInputMessageRoutingDestinationCollection( );
        IList<LineInputMessageRoutingDestinationObject> GetLineInputMessageRoutingDestinationCollectionByRouting( Guid routing );
        LineInputMessageRoutingDestinationObject? GetLineInputMessageRoutingDestinationByRoutingAndListener( Guid routing, Guid? listener );
        IList<LineInputMessageRoutingDestinationObject> GetLineInputMessageRoutingDestinationCollectionByRoutingAndListenerIsNull( Guid routing );
        IList<LineInputMessageRoutingDestinationObject> GetLineInputMessageRoutingDestinationCollectionByListener( Guid? listener );
        IList<LineInputMessageRoutingDestinationObject> GetLineInputMessageRoutingDestinationCollectionByListenerIsNull(  );
        // ---------------------------------------------------------------------
        // LineInputWhiteListEntry queries
        // ---------------------------------------------------------------------
        LineInputWhiteListEntryObject? GetLineInputWhiteListEntryById( Guid id );
        IList<LineInputWhiteListEntryObject> GetLineInputWhiteListEntryCollection( );
        IList<LineInputWhiteListEntryObject> GetLineInputWhiteListEntryCollectionByLineInputDevice( Guid lineInputDevice );
        IList<LineInputWhiteListEntryObject> GetLineInputWhiteListEntryCollectionByLineInputDeviceAndHostName( Guid lineInputDevice, string hostName );
        LineInputWhiteListEntryObject? GetLineInputWhiteListEntryByLineInputDeviceHostNameAndPort( Guid lineInputDevice, string hostName, int port );
        IList<LineInputWhiteListEntryObject> GetLineInputWhiteListEntryByLineInputDeviceHostNameFromPort( Guid lineInputDevice, string hostName, int port );
        IList<LineInputWhiteListEntryObject> GetLineInputWhiteListEntryByLineInputDeviceHostNameUntilPort( Guid lineInputDevice, string hostName, int port );
        IList<LineInputWhiteListEntryObject> GetLineInputWhiteListEntryByLineInputDeviceHostNameOverPort( Guid lineInputDevice, string hostName, int fromPort, int untilPort );
        // ---------------------------------------------------------------------
        // LogApplication queries
        // ---------------------------------------------------------------------
        LogApplicationObject? GetLogApplicationById( Guid id );
        IList<LogApplicationObject> GetLogApplicationCollection( );
        LogApplicationObject? GetLogApplicationByName( string name );
        // ---------------------------------------------------------------------
        // LogApplicationConfiguration queries
        // ---------------------------------------------------------------------
        LogApplicationConfigurationObject? GetLogApplicationConfigurationById( Guid id );
        IList<LogApplicationConfigurationObject> GetLogApplicationConfigurationCollection( );
        IList<LogApplicationConfigurationObject> GetLogApplicationConfigurationCollectionByApplication( Guid application );
        LogApplicationConfigurationObject? GetLogApplicationConfigurationByApplicationAndTimestamp( Guid application, DateTime timestamp );
        LogApplicationConfigurationObject? GetLogApplicationConfigurationByApplicationAtTimestamp( Guid application, DateTime timestamp );
        IList<LogApplicationConfigurationObject> GetLogApplicationConfigurationByApplicationFromTimestamp( Guid application, DateTime timestamp );
        IList<LogApplicationConfigurationObject> GetLogApplicationConfigurationByApplicationUntilTimestamp( Guid application, DateTime timestamp );
        IList<LogApplicationConfigurationObject> GetLogApplicationConfigurationByApplicationOverTimestamp( Guid application, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<LogApplicationConfigurationObject> GetLogApplicationConfigurationCollectionByTimestamp( DateTime timestamp );
        IList<LogApplicationConfigurationObject> GetLogApplicationConfigurationCollectionAtTimestamp( DateTime timestamp );
        IList<LogApplicationConfigurationObject> GetLogApplicationConfigurationCollectionFromTimestamp( DateTime timestamp );
        IList<LogApplicationConfigurationObject> GetLogApplicationConfigurationCollectionUntilTimestamp( DateTime timestamp );
        IList<LogApplicationConfigurationObject> GetLogApplicationConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // LogHost queries
        // ---------------------------------------------------------------------
        LogHostObject? GetLogHostById( Guid id );
        IList<LogHostObject> GetLogHostCollection( );
        LogHostObject? GetLogHostByComputerName( string computerName );
        // ---------------------------------------------------------------------
        // LogHostConfiguration queries
        // ---------------------------------------------------------------------
        LogHostConfigurationObject? GetLogHostConfigurationById( Guid id );
        IList<LogHostConfigurationObject> GetLogHostConfigurationCollection( );
        IList<LogHostConfigurationObject> GetLogHostConfigurationCollectionByHost( Guid host );
        LogHostConfigurationObject? GetLogHostConfigurationByHostAndTimestamp( Guid host, DateTime timestamp );
        LogHostConfigurationObject? GetLogHostConfigurationByHostAtTimestamp( Guid host, DateTime timestamp );
        IList<LogHostConfigurationObject> GetLogHostConfigurationByHostFromTimestamp( Guid host, DateTime timestamp );
        IList<LogHostConfigurationObject> GetLogHostConfigurationByHostUntilTimestamp( Guid host, DateTime timestamp );
        IList<LogHostConfigurationObject> GetLogHostConfigurationByHostOverTimestamp( Guid host, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<LogHostConfigurationObject> GetLogHostConfigurationCollectionByTimestamp( DateTime timestamp );
        IList<LogHostConfigurationObject> GetLogHostConfigurationCollectionAtTimestamp( DateTime timestamp );
        IList<LogHostConfigurationObject> GetLogHostConfigurationCollectionFromTimestamp( DateTime timestamp );
        IList<LogHostConfigurationObject> GetLogHostConfigurationCollectionUntilTimestamp( DateTime timestamp );
        IList<LogHostConfigurationObject> GetLogHostConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // LogLocation queries
        // ---------------------------------------------------------------------
        LogLocationObject? GetLogLocationById( Guid id );
        IList<LogLocationObject> GetLogLocationCollection( );
        IList<LogLocationObject> GetLogLocationCollectionByFileName( string fileName );
        LogLocationObject? GetLogLocationByFileNameAndLineNumber( string fileName, int lineNumber );
        IList<LogLocationObject> GetLogLocationByFileNameFromLineNumber( string fileName, int lineNumber );
        IList<LogLocationObject> GetLogLocationByFileNameUntilLineNumber( string fileName, int lineNumber );
        IList<LogLocationObject> GetLogLocationByFileNameOverLineNumber( string fileName, int fromLineNumber, int untilLineNumber );
        // ---------------------------------------------------------------------
        // LogProcess queries
        // ---------------------------------------------------------------------
        LogProcessObject? GetLogProcessById( Guid id );
        IList<LogProcessObject> GetLogProcessCollection( );
        IList<LogProcessObject> GetLogProcessCollectionByApplication( Guid application );
        IList<LogProcessObject> GetLogProcessCollectionByApplicationAndStarted( Guid application, DateTime started );
        IList<LogProcessObject> GetLogProcessCollectionByApplicationAtStarted( Guid application, DateTime started );
        IList<LogProcessObject> GetLogProcessCollectionByApplicationFromStarted( Guid application, DateTime started );
        IList<LogProcessObject> GetLogProcessCollectionByApplicationUntilStarted( Guid application, DateTime started );
        IList<LogProcessObject> GetLogProcessCollectionByApplicationOverStarted( Guid application, DateTime fromStarted, DateTime untilStarted );
        IList<LogProcessObject> GetLogProcessCollectionByHost( Guid? host );
        IList<LogProcessObject> GetLogProcessCollectionByHostIsNull(  );
        IList<LogProcessObject> GetLogProcessCollectionByHostAndStarted( Guid? host, DateTime started );
        IList<LogProcessObject> GetLogProcessCollectionByHostIsNullAndStarted( DateTime started );
        IList<LogProcessObject> GetLogProcessCollectionByHostAtStarted( Guid? host, DateTime started );
        IList<LogProcessObject> GetLogProcessCollectionByHostFromStarted( Guid? host, DateTime started );
        IList<LogProcessObject> GetLogProcessCollectionByHostUntilStarted( Guid? host, DateTime started );
        IList<LogProcessObject> GetLogProcessCollectionByHostOverStarted( Guid host, DateTime fromStarted, DateTime untilStarted );
        IList<LogProcessObject> GetLogProcessCollectionByStarted( DateTime started );
        IList<LogProcessObject> GetLogProcessCollectionAtStarted( DateTime started );
        IList<LogProcessObject> GetLogProcessCollectionFromStarted( DateTime started );
        IList<LogProcessObject> GetLogProcessCollectionUntilStarted( DateTime started );
        IList<LogProcessObject> GetLogProcessCollectionOverStarted( DateTime fromStarted, DateTime untilStarted );
        // ---------------------------------------------------------------------
        // LogRecord queries
        // ---------------------------------------------------------------------
        LogRecordObject? GetLogRecordById( Guid id );
        IList<LogRecordObject> GetLogRecordCollection( );
        IList<LogRecordObject> GetLogRecordCollectionByThread( Guid thread );
        IList<LogRecordObject> GetLogRecordCollectionByThreadAndTimestamp( Guid thread, DateTime timestamp );
        IList<LogRecordObject> GetLogRecordCollectionByThreadAtTimestamp( Guid thread, DateTime timestamp );
        IList<LogRecordObject> GetLogRecordCollectionByThreadFromTimestamp( Guid thread, DateTime timestamp );
        IList<LogRecordObject> GetLogRecordCollectionByThreadUntilTimestamp( Guid thread, DateTime timestamp );
        IList<LogRecordObject> GetLogRecordCollectionByThreadOverTimestamp( Guid thread, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<LogRecordObject> GetLogRecordCollectionByTimestamp( DateTime timestamp );
        IList<LogRecordObject> GetLogRecordCollectionAtTimestamp( DateTime timestamp );
        IList<LogRecordObject> GetLogRecordCollectionFromTimestamp( DateTime timestamp );
        IList<LogRecordObject> GetLogRecordCollectionUntilTimestamp( DateTime timestamp );
        IList<LogRecordObject> GetLogRecordCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<LogRecordObject> GetLogRecordCollectionByLocation( Guid location );
        // ---------------------------------------------------------------------
        // LogThread queries
        // ---------------------------------------------------------------------
        LogThreadObject? GetLogThreadById( Guid id );
        IList<LogThreadObject> GetLogThreadCollection( );
        IList<LogThreadObject> GetLogThreadCollectionByProcess( Guid process );
        IList<LogThreadObject> GetLogThreadCollectionByProcessAndStarted( Guid process, DateTime started );
        IList<LogThreadObject> GetLogThreadCollectionByProcessAtStarted( Guid process, DateTime started );
        IList<LogThreadObject> GetLogThreadCollectionByProcessFromStarted( Guid process, DateTime started );
        IList<LogThreadObject> GetLogThreadCollectionByProcessUntilStarted( Guid process, DateTime started );
        IList<LogThreadObject> GetLogThreadCollectionByProcessOverStarted( Guid process, DateTime fromStarted, DateTime untilStarted );
        IList<LogThreadObject> GetLogThreadCollectionByStarted( DateTime started );
        IList<LogThreadObject> GetLogThreadCollectionAtStarted( DateTime started );
        IList<LogThreadObject> GetLogThreadCollectionFromStarted( DateTime started );
        IList<LogThreadObject> GetLogThreadCollectionUntilStarted( DateTime started );
        IList<LogThreadObject> GetLogThreadCollectionOverStarted( DateTime fromStarted, DateTime untilStarted );
        // ---------------------------------------------------------------------
        // LogTraceEntry queries
        // ---------------------------------------------------------------------
        LogTraceEntryObject? GetLogTraceEntryById( Guid id );
        IList<LogTraceEntryObject> GetLogTraceEntryCollection( );
        IList<LogTraceEntryObject> GetLogTraceEntryCollectionByThread( Guid thread );
        IList<LogTraceEntryObject> GetLogTraceEntryCollectionByThreadAndEntered( Guid thread, DateTime entered );
        IList<LogTraceEntryObject> GetLogTraceEntryCollectionByThreadAtEntered( Guid thread, DateTime entered );
        IList<LogTraceEntryObject> GetLogTraceEntryCollectionByThreadFromEntered( Guid thread, DateTime entered );
        IList<LogTraceEntryObject> GetLogTraceEntryCollectionByThreadUntilEntered( Guid thread, DateTime entered );
        IList<LogTraceEntryObject> GetLogTraceEntryCollectionByThreadOverEntered( Guid thread, DateTime fromEntered, DateTime untilEntered );
        IList<LogTraceEntryObject> GetLogTraceEntryCollectionByLocation( Guid location );
        IList<LogTraceEntryObject> GetLogTraceEntryCollectionByLocationAndEntered( Guid location, DateTime entered );
        IList<LogTraceEntryObject> GetLogTraceEntryCollectionByLocationAtEntered( Guid location, DateTime entered );
        IList<LogTraceEntryObject> GetLogTraceEntryCollectionByLocationFromEntered( Guid location, DateTime entered );
        IList<LogTraceEntryObject> GetLogTraceEntryCollectionByLocationUntilEntered( Guid location, DateTime entered );
        IList<LogTraceEntryObject> GetLogTraceEntryCollectionByLocationOverEntered( Guid location, DateTime fromEntered, DateTime untilEntered );
        IList<LogTraceEntryObject> GetLogTraceEntryCollectionByEntered( DateTime entered );
        IList<LogTraceEntryObject> GetLogTraceEntryCollectionAtEntered( DateTime entered );
        IList<LogTraceEntryObject> GetLogTraceEntryCollectionFromEntered( DateTime entered );
        IList<LogTraceEntryObject> GetLogTraceEntryCollectionUntilEntered( DateTime entered );
        IList<LogTraceEntryObject> GetLogTraceEntryCollectionOverEntered( DateTime fromEntered, DateTime untilEntered );
        // ---------------------------------------------------------------------
        // MapElement queries
        // ---------------------------------------------------------------------
        MapElementObject? GetMapElementById( Guid id );
        IList<MapElementObject> GetMapElementCollection( );
        IList<MapElementObject> GetMapElementCollectionByItem( Guid item );
        // ---------------------------------------------------------------------
        // MapInfo queries
        // ---------------------------------------------------------------------
        MapInfoObject? GetMapInfoById( Guid id );
        IList<MapInfoObject> GetMapInfoCollection( );
        // ---------------------------------------------------------------------
        // MapServiceOptions queries
        // ---------------------------------------------------------------------
        MapServiceOptionsObject? GetMapServiceOptionsById( Guid id );
        IList<MapServiceOptionsObject> GetMapServiceOptionsCollection( );
        MapServiceOptionsObject? GetMapServiceOptionsByTimestamp( DateTime timestamp );
        MapServiceOptionsObject? GetMapServiceOptionsAtTimestamp( DateTime timestamp );
        IList<MapServiceOptionsObject> GetMapServiceOptionsFromTimestamp( DateTime timestamp );
        IList<MapServiceOptionsObject> GetMapServiceOptionsUntilTimestamp( DateTime timestamp );
        IList<MapServiceOptionsObject> GetMapServiceOptionsOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // MaritimeIdentificationDigits queries
        // ---------------------------------------------------------------------
        MaritimeIdentificationDigitsObject? GetMaritimeIdentificationDigitsById( Guid id );
        IList<MaritimeIdentificationDigitsObject> GetMaritimeIdentificationDigitsCollection( );
        MaritimeIdentificationDigitsObject? GetMaritimeIdentificationDigitsByCode( int code );
        IList<MaritimeIdentificationDigitsObject> GetMaritimeIdentificationDigitsFromCode( int code );
        IList<MaritimeIdentificationDigitsObject> GetMaritimeIdentificationDigitsUntilCode( int code );
        IList<MaritimeIdentificationDigitsObject> GetMaritimeIdentificationDigitsOverCode( int fromCode, int untilCode );
        IList<MaritimeIdentificationDigitsObject> GetMaritimeIdentificationDigitsCollectionByCountry( Guid country );
        // ---------------------------------------------------------------------
        // MediaProxySession queries
        // ---------------------------------------------------------------------
        MediaProxySessionObject? GetMediaProxySessionById( Guid id );
        IList<MediaProxySessionObject> GetMediaProxySessionCollection( );
        IList<MediaProxySessionObject> GetMediaProxySessionCollectionByService( Guid service );
        MediaProxySessionObject? GetMediaProxySessionByServiceAndName( Guid service, string name );
        // ---------------------------------------------------------------------
        // MediaProxySessionFile queries
        // ---------------------------------------------------------------------
        MediaProxySessionFileObject? GetMediaProxySessionFileById( Guid id );
        IList<MediaProxySessionFileObject> GetMediaProxySessionFileCollection( );
        IList<MediaProxySessionFileObject> GetMediaProxySessionFileCollectionByProxySession( Guid proxySession );
        MediaProxySessionFileObject? GetMediaProxySessionFileByProxySessionAndTimestamp( Guid proxySession, DateTime timestamp );
        MediaProxySessionFileObject? GetMediaProxySessionFileByProxySessionAtTimestamp( Guid proxySession, DateTime timestamp );
        IList<MediaProxySessionFileObject> GetMediaProxySessionFileByProxySessionFromTimestamp( Guid proxySession, DateTime timestamp );
        IList<MediaProxySessionFileObject> GetMediaProxySessionFileByProxySessionUntilTimestamp( Guid proxySession, DateTime timestamp );
        IList<MediaProxySessionFileObject> GetMediaProxySessionFileByProxySessionOverTimestamp( Guid proxySession, DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // MediaProxySessionOptions queries
        // ---------------------------------------------------------------------
        MediaProxySessionOptionsObject? GetMediaProxySessionOptionsById( Guid id );
        IList<MediaProxySessionOptionsObject> GetMediaProxySessionOptionsCollection( );
        IList<MediaProxySessionOptionsObject> GetMediaProxySessionOptionsCollectionByProxySession( Guid proxySession );
        MediaProxySessionOptionsObject? GetMediaProxySessionOptionsByProxySessionAndTimestamp( Guid proxySession, DateTime timestamp );
        MediaProxySessionOptionsObject? GetMediaProxySessionOptionsByProxySessionAtTimestamp( Guid proxySession, DateTime timestamp );
        IList<MediaProxySessionOptionsObject> GetMediaProxySessionOptionsByProxySessionFromTimestamp( Guid proxySession, DateTime timestamp );
        IList<MediaProxySessionOptionsObject> GetMediaProxySessionOptionsByProxySessionUntilTimestamp( Guid proxySession, DateTime timestamp );
        IList<MediaProxySessionOptionsObject> GetMediaProxySessionOptionsByProxySessionOverTimestamp( Guid proxySession, DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // MediaService queries
        // ---------------------------------------------------------------------
        MediaServiceObject? GetMediaServiceById( Guid id );
        IList<MediaServiceObject> GetMediaServiceCollection( );
        // ---------------------------------------------------------------------
        // MediaServiceOptions queries
        // ---------------------------------------------------------------------
        MediaServiceOptionsObject? GetMediaServiceOptionsById( Guid id );
        IList<MediaServiceOptionsObject> GetMediaServiceOptionsCollection( );
        IList<MediaServiceOptionsObject> GetMediaServiceOptionsCollectionByMediaService( Guid mediaService );
        MediaServiceOptionsObject? GetMediaServiceOptionsByMediaServiceAndTimestamp( Guid mediaService, DateTime timestamp );
        MediaServiceOptionsObject? GetMediaServiceOptionsByMediaServiceAtTimestamp( Guid mediaService, DateTime timestamp );
        IList<MediaServiceOptionsObject> GetMediaServiceOptionsByMediaServiceFromTimestamp( Guid mediaService, DateTime timestamp );
        IList<MediaServiceOptionsObject> GetMediaServiceOptionsByMediaServiceUntilTimestamp( Guid mediaService, DateTime timestamp );
        IList<MediaServiceOptionsObject> GetMediaServiceOptionsByMediaServiceOverTimestamp( Guid mediaService, DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // NamespaceElement queries
        // ---------------------------------------------------------------------
        NamespaceElementObject? GetNamespaceElementById( Guid id );
        IList<NamespaceElementObject> GetNamespaceElementCollection( );
        IList<NamespaceElementObject> GetNamespaceElementCollectionByNamespace( Guid namespace__ );
        NamespaceElementObject? GetNamespaceElementByNamespaceAndName( Guid namespace__, string name );
        // ---------------------------------------------------------------------
        // ElementType queries
        // ---------------------------------------------------------------------
        ElementTypeObject? GetElementTypeById( Guid id );
        IList<ElementTypeObject> GetElementTypeCollection( );
        IList<ElementTypeObject> GetElementTypeCollectionByNamespace( Guid namespace__ );
        ElementTypeObject? GetElementTypeByNamespaceAndName( Guid namespace__, string name );
        // ---------------------------------------------------------------------
        // Namespace queries
        // ---------------------------------------------------------------------
        NamespaceObject? GetNamespaceById( Guid id );
        IList<NamespaceObject> GetNamespaceCollection( );
        IList<NamespaceObject> GetNamespaceCollectionByNamespace( Guid namespace__ );
        NamespaceObject? GetNamespaceByNamespaceAndName( Guid namespace__, string name );
        // ---------------------------------------------------------------------
        // OilSpill queries
        // ---------------------------------------------------------------------
        OilSpillObject? GetOilSpillById( Guid id );
        IList<OilSpillObject> GetOilSpillCollection( );
        IList<OilSpillObject> GetOilSpillCollectionByOilSpillDetector( Guid oilSpillDetector );
        IList<OilSpillObject> GetOilSpillCollectionByOilSpillDetectorAndTimestamp( Guid oilSpillDetector, DateTime timestamp );
        IList<OilSpillObject> GetOilSpillCollectionByOilSpillDetectorAtTimestamp( Guid oilSpillDetector, DateTime timestamp );
        IList<OilSpillObject> GetOilSpillCollectionByOilSpillDetectorFromTimestamp( Guid oilSpillDetector, DateTime timestamp );
        IList<OilSpillObject> GetOilSpillCollectionByOilSpillDetectorUntilTimestamp( Guid oilSpillDetector, DateTime timestamp );
        IList<OilSpillObject> GetOilSpillCollectionByOilSpillDetectorOverTimestamp( Guid oilSpillDetector, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<OilSpillObject> GetOilSpillCollectionByTimestamp( DateTime timestamp );
        IList<OilSpillObject> GetOilSpillCollectionAtTimestamp( DateTime timestamp );
        IList<OilSpillObject> GetOilSpillCollectionFromTimestamp( DateTime timestamp );
        IList<OilSpillObject> GetOilSpillCollectionUntilTimestamp( DateTime timestamp );
        IList<OilSpillObject> GetOilSpillCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // OilSpillDetectorCommand queries
        // ---------------------------------------------------------------------
        OilSpillDetectorCommandObject? GetOilSpillDetectorCommandById( Guid id );
        IList<OilSpillDetectorCommandObject> GetOilSpillDetectorCommandCollection( );
        IList<OilSpillDetectorCommandObject> GetOilSpillDetectorCommandCollectionByOilSpillDetector( Guid oilSpillDetector );
        IList<OilSpillDetectorCommandObject> GetOilSpillDetectorCommandCollectionByOilSpillDetectorAndTimestamp( Guid oilSpillDetector, DateTime timestamp );
        IList<OilSpillDetectorCommandObject> GetOilSpillDetectorCommandCollectionByOilSpillDetectorAtTimestamp( Guid oilSpillDetector, DateTime timestamp );
        IList<OilSpillDetectorCommandObject> GetOilSpillDetectorCommandCollectionByOilSpillDetectorFromTimestamp( Guid oilSpillDetector, DateTime timestamp );
        IList<OilSpillDetectorCommandObject> GetOilSpillDetectorCommandCollectionByOilSpillDetectorUntilTimestamp( Guid oilSpillDetector, DateTime timestamp );
        IList<OilSpillDetectorCommandObject> GetOilSpillDetectorCommandCollectionByOilSpillDetectorOverTimestamp( Guid oilSpillDetector, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<OilSpillDetectorCommandObject> GetOilSpillDetectorCommandCollectionByTimestamp( DateTime timestamp );
        IList<OilSpillDetectorCommandObject> GetOilSpillDetectorCommandCollectionAtTimestamp( DateTime timestamp );
        IList<OilSpillDetectorCommandObject> GetOilSpillDetectorCommandCollectionFromTimestamp( DateTime timestamp );
        IList<OilSpillDetectorCommandObject> GetOilSpillDetectorCommandCollectionUntilTimestamp( DateTime timestamp );
        IList<OilSpillDetectorCommandObject> GetOilSpillDetectorCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<OilSpillDetectorCommandObject> GetOilSpillDetectorCommandCollectionByReply( Guid? reply );
        IList<OilSpillDetectorCommandObject> GetOilSpillDetectorCommandCollectionByReplyIsNull(  );
        // ---------------------------------------------------------------------
        // OilSpillDetectorCommandReply queries
        // ---------------------------------------------------------------------
        OilSpillDetectorCommandReplyObject? GetOilSpillDetectorCommandReplyById( Guid id );
        IList<OilSpillDetectorCommandReplyObject> GetOilSpillDetectorCommandReplyCollection( );
        IList<OilSpillDetectorCommandReplyObject> GetOilSpillDetectorCommandReplyCollectionByOilSpillDetector( Guid oilSpillDetector );
        IList<OilSpillDetectorCommandReplyObject> GetOilSpillDetectorCommandReplyCollectionByOilSpillDetectorAndTimestamp( Guid oilSpillDetector, DateTime timestamp );
        IList<OilSpillDetectorCommandReplyObject> GetOilSpillDetectorCommandReplyCollectionByOilSpillDetectorAtTimestamp( Guid oilSpillDetector, DateTime timestamp );
        IList<OilSpillDetectorCommandReplyObject> GetOilSpillDetectorCommandReplyCollectionByOilSpillDetectorFromTimestamp( Guid oilSpillDetector, DateTime timestamp );
        IList<OilSpillDetectorCommandReplyObject> GetOilSpillDetectorCommandReplyCollectionByOilSpillDetectorUntilTimestamp( Guid oilSpillDetector, DateTime timestamp );
        IList<OilSpillDetectorCommandReplyObject> GetOilSpillDetectorCommandReplyCollectionByOilSpillDetectorOverTimestamp( Guid oilSpillDetector, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<OilSpillDetectorCommandReplyObject> GetOilSpillDetectorCommandReplyCollectionByTimestamp( DateTime timestamp );
        IList<OilSpillDetectorCommandReplyObject> GetOilSpillDetectorCommandReplyCollectionAtTimestamp( DateTime timestamp );
        IList<OilSpillDetectorCommandReplyObject> GetOilSpillDetectorCommandReplyCollectionFromTimestamp( DateTime timestamp );
        IList<OilSpillDetectorCommandReplyObject> GetOilSpillDetectorCommandReplyCollectionUntilTimestamp( DateTime timestamp );
        IList<OilSpillDetectorCommandReplyObject> GetOilSpillDetectorCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        OilSpillDetectorCommandReplyObject? GetOilSpillDetectorCommandReplyByCommand( Guid? command );
        IList<OilSpillDetectorCommandReplyObject> GetOilSpillDetectorCommandReplyCollectionByCommandIsNull(  );
        // ---------------------------------------------------------------------
        // OilSpillDetectorConfiguration queries
        // ---------------------------------------------------------------------
        OilSpillDetectorConfigurationObject? GetOilSpillDetectorConfigurationById( Guid id );
        IList<OilSpillDetectorConfigurationObject> GetOilSpillDetectorConfigurationCollection( );
        IList<OilSpillDetectorConfigurationObject> GetOilSpillDetectorConfigurationCollectionByOilSpillDetector( Guid oilSpillDetector );
        OilSpillDetectorConfigurationObject? GetOilSpillDetectorConfigurationByOilSpillDetectorAndTimestamp( Guid oilSpillDetector, DateTime timestamp );
        OilSpillDetectorConfigurationObject? GetOilSpillDetectorConfigurationByOilSpillDetectorAtTimestamp( Guid oilSpillDetector, DateTime timestamp );
        IList<OilSpillDetectorConfigurationObject> GetOilSpillDetectorConfigurationByOilSpillDetectorFromTimestamp( Guid oilSpillDetector, DateTime timestamp );
        IList<OilSpillDetectorConfigurationObject> GetOilSpillDetectorConfigurationByOilSpillDetectorUntilTimestamp( Guid oilSpillDetector, DateTime timestamp );
        IList<OilSpillDetectorConfigurationObject> GetOilSpillDetectorConfigurationByOilSpillDetectorOverTimestamp( Guid oilSpillDetector, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<OilSpillDetectorConfigurationObject> GetOilSpillDetectorConfigurationCollectionByTimestamp( DateTime timestamp );
        IList<OilSpillDetectorConfigurationObject> GetOilSpillDetectorConfigurationCollectionAtTimestamp( DateTime timestamp );
        IList<OilSpillDetectorConfigurationObject> GetOilSpillDetectorConfigurationCollectionFromTimestamp( DateTime timestamp );
        IList<OilSpillDetectorConfigurationObject> GetOilSpillDetectorConfigurationCollectionUntilTimestamp( DateTime timestamp );
        IList<OilSpillDetectorConfigurationObject> GetOilSpillDetectorConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<OilSpillDetectorConfigurationObject> GetOilSpillDetectorConfigurationCollectionByTargetMMSI( Guid? targetMMSI );
        IList<OilSpillDetectorConfigurationObject> GetOilSpillDetectorConfigurationCollectionByTargetMMSIIsNull(  );
        // ---------------------------------------------------------------------
        // Position2DTimeseriesValue queries
        // ---------------------------------------------------------------------
        Position2DTimeseriesValueObject? GetPosition2DTimeseriesValueById( Guid id );
        IList<Position2DTimeseriesValueObject> GetPosition2DTimeseriesValueCollection( );
        IList<Position2DTimeseriesValueObject> GetPosition2DTimeseriesValueCollectionByTimeseries( Guid timeseries );
        Position2DTimeseriesValueObject? GetPosition2DTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
        Position2DTimeseriesValueObject? GetPosition2DTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
        IList<Position2DTimeseriesValueObject> GetPosition2DTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
        IList<Position2DTimeseriesValueObject> GetPosition2DTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
        IList<Position2DTimeseriesValueObject> GetPosition2DTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<Position2DTimeseriesValueObject> GetPosition2DTimeseriesValueCollectionByTimestamp( DateTime timestamp );
        IList<Position2DTimeseriesValueObject> GetPosition2DTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
        IList<Position2DTimeseriesValueObject> GetPosition2DTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
        IList<Position2DTimeseriesValueObject> GetPosition2DTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
        IList<Position2DTimeseriesValueObject> GetPosition2DTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // Position3DTimeseriesValue queries
        // ---------------------------------------------------------------------
        Position3DTimeseriesValueObject? GetPosition3DTimeseriesValueById( Guid id );
        IList<Position3DTimeseriesValueObject> GetPosition3DTimeseriesValueCollection( );
        IList<Position3DTimeseriesValueObject> GetPosition3DTimeseriesValueCollectionByTimeseries( Guid timeseries );
        Position3DTimeseriesValueObject? GetPosition3DTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
        Position3DTimeseriesValueObject? GetPosition3DTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
        IList<Position3DTimeseriesValueObject> GetPosition3DTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
        IList<Position3DTimeseriesValueObject> GetPosition3DTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
        IList<Position3DTimeseriesValueObject> GetPosition3DTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<Position3DTimeseriesValueObject> GetPosition3DTimeseriesValueCollectionByTimestamp( DateTime timestamp );
        IList<Position3DTimeseriesValueObject> GetPosition3DTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
        IList<Position3DTimeseriesValueObject> GetPosition3DTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
        IList<Position3DTimeseriesValueObject> GetPosition3DTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
        IList<Position3DTimeseriesValueObject> GetPosition3DTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // ProcessTrackValueResult queries
        // ---------------------------------------------------------------------
        ProcessTrackValueResultObject? GetProcessTrackValueResultById( Guid id );
        IList<ProcessTrackValueResultObject> GetProcessTrackValueResultCollection( );
        // ---------------------------------------------------------------------
        // Property queries
        // ---------------------------------------------------------------------
        PropertyObject? GetPropertyById( Guid id );
        IList<PropertyObject> GetPropertyCollection( );
        IList<PropertyObject> GetPropertyCollectionByElement( Guid element );
        PropertyObject? GetPropertyByElementAndDefinition( Guid element, Guid definition );
        IList<PropertyObject> GetPropertyCollectionByDefinition( Guid definition );
        // ---------------------------------------------------------------------
        // BinaryProperty queries
        // ---------------------------------------------------------------------
        BinaryPropertyObject? GetBinaryPropertyById( Guid id );
        IList<BinaryPropertyObject> GetBinaryPropertyCollection( );
        IList<BinaryPropertyObject> GetBinaryPropertyCollectionByElement( Guid element );
        BinaryPropertyObject? GetBinaryPropertyByElementAndDefinition( Guid element, Guid definition );
        IList<BinaryPropertyObject> GetBinaryPropertyCollectionByDefinition( Guid definition );
        // ---------------------------------------------------------------------
        // BooleanProperty queries
        // ---------------------------------------------------------------------
        BooleanPropertyObject? GetBooleanPropertyById( Guid id );
        IList<BooleanPropertyObject> GetBooleanPropertyCollection( );
        IList<BooleanPropertyObject> GetBooleanPropertyCollectionByElement( Guid element );
        BooleanPropertyObject? GetBooleanPropertyByElementAndDefinition( Guid element, Guid definition );
        IList<BooleanPropertyObject> GetBooleanPropertyCollectionByDefinition( Guid definition );
        // ---------------------------------------------------------------------
        // ByteProperty queries
        // ---------------------------------------------------------------------
        BytePropertyObject? GetBytePropertyById( Guid id );
        IList<BytePropertyObject> GetBytePropertyCollection( );
        IList<BytePropertyObject> GetBytePropertyCollectionByElement( Guid element );
        BytePropertyObject? GetBytePropertyByElementAndDefinition( Guid element, Guid definition );
        IList<BytePropertyObject> GetBytePropertyCollectionByDefinition( Guid definition );
        // ---------------------------------------------------------------------
        // DateTimeProperty queries
        // ---------------------------------------------------------------------
        DateTimePropertyObject? GetDateTimePropertyById( Guid id );
        IList<DateTimePropertyObject> GetDateTimePropertyCollection( );
        IList<DateTimePropertyObject> GetDateTimePropertyCollectionByElement( Guid element );
        DateTimePropertyObject? GetDateTimePropertyByElementAndDefinition( Guid element, Guid definition );
        IList<DateTimePropertyObject> GetDateTimePropertyCollectionByDefinition( Guid definition );
        // ---------------------------------------------------------------------
        // DoubleProperty queries
        // ---------------------------------------------------------------------
        DoublePropertyObject? GetDoublePropertyById( Guid id );
        IList<DoublePropertyObject> GetDoublePropertyCollection( );
        IList<DoublePropertyObject> GetDoublePropertyCollectionByElement( Guid element );
        DoublePropertyObject? GetDoublePropertyByElementAndDefinition( Guid element, Guid definition );
        IList<DoublePropertyObject> GetDoublePropertyCollectionByDefinition( Guid definition );
        // ---------------------------------------------------------------------
        // GuidProperty queries
        // ---------------------------------------------------------------------
        GuidPropertyObject? GetGuidPropertyById( Guid id );
        IList<GuidPropertyObject> GetGuidPropertyCollection( );
        IList<GuidPropertyObject> GetGuidPropertyCollectionByElement( Guid element );
        GuidPropertyObject? GetGuidPropertyByElementAndDefinition( Guid element, Guid definition );
        IList<GuidPropertyObject> GetGuidPropertyCollectionByDefinition( Guid definition );
        // ---------------------------------------------------------------------
        // Int16Property queries
        // ---------------------------------------------------------------------
        Int16PropertyObject? GetInt16PropertyById( Guid id );
        IList<Int16PropertyObject> GetInt16PropertyCollection( );
        IList<Int16PropertyObject> GetInt16PropertyCollectionByElement( Guid element );
        Int16PropertyObject? GetInt16PropertyByElementAndDefinition( Guid element, Guid definition );
        IList<Int16PropertyObject> GetInt16PropertyCollectionByDefinition( Guid definition );
        // ---------------------------------------------------------------------
        // Int32Property queries
        // ---------------------------------------------------------------------
        Int32PropertyObject? GetInt32PropertyById( Guid id );
        IList<Int32PropertyObject> GetInt32PropertyCollection( );
        IList<Int32PropertyObject> GetInt32PropertyCollectionByElement( Guid element );
        Int32PropertyObject? GetInt32PropertyByElementAndDefinition( Guid element, Guid definition );
        IList<Int32PropertyObject> GetInt32PropertyCollectionByDefinition( Guid definition );
        // ---------------------------------------------------------------------
        // Int64Property queries
        // ---------------------------------------------------------------------
        Int64PropertyObject? GetInt64PropertyById( Guid id );
        IList<Int64PropertyObject> GetInt64PropertyCollection( );
        IList<Int64PropertyObject> GetInt64PropertyCollectionByElement( Guid element );
        Int64PropertyObject? GetInt64PropertyByElementAndDefinition( Guid element, Guid definition );
        IList<Int64PropertyObject> GetInt64PropertyCollectionByDefinition( Guid definition );
        // ---------------------------------------------------------------------
        // ReferenceProperty queries
        // ---------------------------------------------------------------------
        ReferencePropertyObject? GetReferencePropertyById( Guid id );
        IList<ReferencePropertyObject> GetReferencePropertyCollection( );
        IList<ReferencePropertyObject> GetReferencePropertyCollectionByElement( Guid element );
        ReferencePropertyObject? GetReferencePropertyByElementAndDefinition( Guid element, Guid definition );
        IList<ReferencePropertyObject> GetReferencePropertyCollectionByDefinition( Guid definition );
        IList<ReferencePropertyObject> GetReferencePropertyCollectionByValue( Guid? value__ );
        IList<ReferencePropertyObject> GetReferencePropertyCollectionByValueIsNull(  );
        // ---------------------------------------------------------------------
        // SByteProperty queries
        // ---------------------------------------------------------------------
        SBytePropertyObject? GetSBytePropertyById( Guid id );
        IList<SBytePropertyObject> GetSBytePropertyCollection( );
        IList<SBytePropertyObject> GetSBytePropertyCollectionByElement( Guid element );
        SBytePropertyObject? GetSBytePropertyByElementAndDefinition( Guid element, Guid definition );
        IList<SBytePropertyObject> GetSBytePropertyCollectionByDefinition( Guid definition );
        // ---------------------------------------------------------------------
        // SingleProperty queries
        // ---------------------------------------------------------------------
        SinglePropertyObject? GetSinglePropertyById( Guid id );
        IList<SinglePropertyObject> GetSinglePropertyCollection( );
        IList<SinglePropertyObject> GetSinglePropertyCollectionByElement( Guid element );
        SinglePropertyObject? GetSinglePropertyByElementAndDefinition( Guid element, Guid definition );
        IList<SinglePropertyObject> GetSinglePropertyCollectionByDefinition( Guid definition );
        // ---------------------------------------------------------------------
        // StringProperty queries
        // ---------------------------------------------------------------------
        StringPropertyObject? GetStringPropertyById( Guid id );
        IList<StringPropertyObject> GetStringPropertyCollection( );
        IList<StringPropertyObject> GetStringPropertyCollectionByElement( Guid element );
        StringPropertyObject? GetStringPropertyByElementAndDefinition( Guid element, Guid definition );
        IList<StringPropertyObject> GetStringPropertyCollectionByDefinition( Guid definition );
        // ---------------------------------------------------------------------
        // TimeseriesProperty queries
        // ---------------------------------------------------------------------
        TimeseriesPropertyObject? GetTimeseriesPropertyById( Guid id );
        IList<TimeseriesPropertyObject> GetTimeseriesPropertyCollection( );
        IList<TimeseriesPropertyObject> GetTimeseriesPropertyCollectionByElement( Guid element );
        TimeseriesPropertyObject? GetTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
        IList<TimeseriesPropertyObject> GetTimeseriesPropertyCollectionByDefinition( Guid definition );
        // ---------------------------------------------------------------------
        // BinaryTimeseriesProperty queries
        // ---------------------------------------------------------------------
        BinaryTimeseriesPropertyObject? GetBinaryTimeseriesPropertyById( Guid id );
        IList<BinaryTimeseriesPropertyObject> GetBinaryTimeseriesPropertyCollection( );
        IList<BinaryTimeseriesPropertyObject> GetBinaryTimeseriesPropertyCollectionByElement( Guid element );
        BinaryTimeseriesPropertyObject? GetBinaryTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
        IList<BinaryTimeseriesPropertyObject> GetBinaryTimeseriesPropertyCollectionByDefinition( Guid definition );
        IList<BinaryTimeseriesPropertyObject> GetBinaryTimeseriesPropertyCollectionByTimeseries( Guid? timeseries );
        IList<BinaryTimeseriesPropertyObject> GetBinaryTimeseriesPropertyCollectionByTimeseriesIsNull(  );
        // ---------------------------------------------------------------------
        // BooleanTimeseriesProperty queries
        // ---------------------------------------------------------------------
        BooleanTimeseriesPropertyObject? GetBooleanTimeseriesPropertyById( Guid id );
        IList<BooleanTimeseriesPropertyObject> GetBooleanTimeseriesPropertyCollection( );
        IList<BooleanTimeseriesPropertyObject> GetBooleanTimeseriesPropertyCollectionByElement( Guid element );
        BooleanTimeseriesPropertyObject? GetBooleanTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
        IList<BooleanTimeseriesPropertyObject> GetBooleanTimeseriesPropertyCollectionByDefinition( Guid definition );
        IList<BooleanTimeseriesPropertyObject> GetBooleanTimeseriesPropertyCollectionByTimeseries( Guid? timeseries );
        IList<BooleanTimeseriesPropertyObject> GetBooleanTimeseriesPropertyCollectionByTimeseriesIsNull(  );
        // ---------------------------------------------------------------------
        // ByteTimeseriesProperty queries
        // ---------------------------------------------------------------------
        ByteTimeseriesPropertyObject? GetByteTimeseriesPropertyById( Guid id );
        IList<ByteTimeseriesPropertyObject> GetByteTimeseriesPropertyCollection( );
        IList<ByteTimeseriesPropertyObject> GetByteTimeseriesPropertyCollectionByElement( Guid element );
        ByteTimeseriesPropertyObject? GetByteTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
        IList<ByteTimeseriesPropertyObject> GetByteTimeseriesPropertyCollectionByDefinition( Guid definition );
        IList<ByteTimeseriesPropertyObject> GetByteTimeseriesPropertyCollectionByTimeseries( Guid? timeseries );
        IList<ByteTimeseriesPropertyObject> GetByteTimeseriesPropertyCollectionByTimeseriesIsNull(  );
        // ---------------------------------------------------------------------
        // DateTimeTimeseriesProperty queries
        // ---------------------------------------------------------------------
        DateTimeTimeseriesPropertyObject? GetDateTimeTimeseriesPropertyById( Guid id );
        IList<DateTimeTimeseriesPropertyObject> GetDateTimeTimeseriesPropertyCollection( );
        IList<DateTimeTimeseriesPropertyObject> GetDateTimeTimeseriesPropertyCollectionByElement( Guid element );
        DateTimeTimeseriesPropertyObject? GetDateTimeTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
        IList<DateTimeTimeseriesPropertyObject> GetDateTimeTimeseriesPropertyCollectionByDefinition( Guid definition );
        IList<DateTimeTimeseriesPropertyObject> GetDateTimeTimeseriesPropertyCollectionByTimeseries( Guid? timeseries );
        IList<DateTimeTimeseriesPropertyObject> GetDateTimeTimeseriesPropertyCollectionByTimeseriesIsNull(  );
        // ---------------------------------------------------------------------
        // DoubleTimeseriesProperty queries
        // ---------------------------------------------------------------------
        DoubleTimeseriesPropertyObject? GetDoubleTimeseriesPropertyById( Guid id );
        IList<DoubleTimeseriesPropertyObject> GetDoubleTimeseriesPropertyCollection( );
        IList<DoubleTimeseriesPropertyObject> GetDoubleTimeseriesPropertyCollectionByElement( Guid element );
        DoubleTimeseriesPropertyObject? GetDoubleTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
        IList<DoubleTimeseriesPropertyObject> GetDoubleTimeseriesPropertyCollectionByDefinition( Guid definition );
        IList<DoubleTimeseriesPropertyObject> GetDoubleTimeseriesPropertyCollectionByTimeseries( Guid? timeseries );
        IList<DoubleTimeseriesPropertyObject> GetDoubleTimeseriesPropertyCollectionByTimeseriesIsNull(  );
        // ---------------------------------------------------------------------
        // GuidTimeseriesProperty queries
        // ---------------------------------------------------------------------
        GuidTimeseriesPropertyObject? GetGuidTimeseriesPropertyById( Guid id );
        IList<GuidTimeseriesPropertyObject> GetGuidTimeseriesPropertyCollection( );
        IList<GuidTimeseriesPropertyObject> GetGuidTimeseriesPropertyCollectionByElement( Guid element );
        GuidTimeseriesPropertyObject? GetGuidTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
        IList<GuidTimeseriesPropertyObject> GetGuidTimeseriesPropertyCollectionByDefinition( Guid definition );
        IList<GuidTimeseriesPropertyObject> GetGuidTimeseriesPropertyCollectionByTimeseries( Guid? timeseries );
        IList<GuidTimeseriesPropertyObject> GetGuidTimeseriesPropertyCollectionByTimeseriesIsNull(  );
        // ---------------------------------------------------------------------
        // Int16TimeseriesProperty queries
        // ---------------------------------------------------------------------
        Int16TimeseriesPropertyObject? GetInt16TimeseriesPropertyById( Guid id );
        IList<Int16TimeseriesPropertyObject> GetInt16TimeseriesPropertyCollection( );
        IList<Int16TimeseriesPropertyObject> GetInt16TimeseriesPropertyCollectionByElement( Guid element );
        Int16TimeseriesPropertyObject? GetInt16TimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
        IList<Int16TimeseriesPropertyObject> GetInt16TimeseriesPropertyCollectionByDefinition( Guid definition );
        IList<Int16TimeseriesPropertyObject> GetInt16TimeseriesPropertyCollectionByTimeseries( Guid? timeseries );
        IList<Int16TimeseriesPropertyObject> GetInt16TimeseriesPropertyCollectionByTimeseriesIsNull(  );
        // ---------------------------------------------------------------------
        // Int32TimeseriesProperty queries
        // ---------------------------------------------------------------------
        Int32TimeseriesPropertyObject? GetInt32TimeseriesPropertyById( Guid id );
        IList<Int32TimeseriesPropertyObject> GetInt32TimeseriesPropertyCollection( );
        IList<Int32TimeseriesPropertyObject> GetInt32TimeseriesPropertyCollectionByElement( Guid element );
        Int32TimeseriesPropertyObject? GetInt32TimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
        IList<Int32TimeseriesPropertyObject> GetInt32TimeseriesPropertyCollectionByDefinition( Guid definition );
        IList<Int32TimeseriesPropertyObject> GetInt32TimeseriesPropertyCollectionByTimeseries( Guid? timeseries );
        IList<Int32TimeseriesPropertyObject> GetInt32TimeseriesPropertyCollectionByTimeseriesIsNull(  );
        // ---------------------------------------------------------------------
        // Int64TimeseriesProperty queries
        // ---------------------------------------------------------------------
        Int64TimeseriesPropertyObject? GetInt64TimeseriesPropertyById( Guid id );
        IList<Int64TimeseriesPropertyObject> GetInt64TimeseriesPropertyCollection( );
        IList<Int64TimeseriesPropertyObject> GetInt64TimeseriesPropertyCollectionByElement( Guid element );
        Int64TimeseriesPropertyObject? GetInt64TimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
        IList<Int64TimeseriesPropertyObject> GetInt64TimeseriesPropertyCollectionByDefinition( Guid definition );
        IList<Int64TimeseriesPropertyObject> GetInt64TimeseriesPropertyCollectionByTimeseries( Guid? timeseries );
        IList<Int64TimeseriesPropertyObject> GetInt64TimeseriesPropertyCollectionByTimeseriesIsNull(  );
        // ---------------------------------------------------------------------
        // ReferenceTimeseriesProperty queries
        // ---------------------------------------------------------------------
        ReferenceTimeseriesPropertyObject? GetReferenceTimeseriesPropertyById( Guid id );
        IList<ReferenceTimeseriesPropertyObject> GetReferenceTimeseriesPropertyCollection( );
        IList<ReferenceTimeseriesPropertyObject> GetReferenceTimeseriesPropertyCollectionByElement( Guid element );
        ReferenceTimeseriesPropertyObject? GetReferenceTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
        IList<ReferenceTimeseriesPropertyObject> GetReferenceTimeseriesPropertyCollectionByDefinition( Guid definition );
        IList<ReferenceTimeseriesPropertyObject> GetReferenceTimeseriesPropertyCollectionByTimeseries( Guid? timeseries );
        IList<ReferenceTimeseriesPropertyObject> GetReferenceTimeseriesPropertyCollectionByTimeseriesIsNull(  );
        // ---------------------------------------------------------------------
        // SByteTimeseriesProperty queries
        // ---------------------------------------------------------------------
        SByteTimeseriesPropertyObject? GetSByteTimeseriesPropertyById( Guid id );
        IList<SByteTimeseriesPropertyObject> GetSByteTimeseriesPropertyCollection( );
        IList<SByteTimeseriesPropertyObject> GetSByteTimeseriesPropertyCollectionByElement( Guid element );
        SByteTimeseriesPropertyObject? GetSByteTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
        IList<SByteTimeseriesPropertyObject> GetSByteTimeseriesPropertyCollectionByDefinition( Guid definition );
        IList<SByteTimeseriesPropertyObject> GetSByteTimeseriesPropertyCollectionByTimeseries( Guid? timeseries );
        IList<SByteTimeseriesPropertyObject> GetSByteTimeseriesPropertyCollectionByTimeseriesIsNull(  );
        // ---------------------------------------------------------------------
        // SingleTimeseriesProperty queries
        // ---------------------------------------------------------------------
        SingleTimeseriesPropertyObject? GetSingleTimeseriesPropertyById( Guid id );
        IList<SingleTimeseriesPropertyObject> GetSingleTimeseriesPropertyCollection( );
        IList<SingleTimeseriesPropertyObject> GetSingleTimeseriesPropertyCollectionByElement( Guid element );
        SingleTimeseriesPropertyObject? GetSingleTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
        IList<SingleTimeseriesPropertyObject> GetSingleTimeseriesPropertyCollectionByDefinition( Guid definition );
        IList<SingleTimeseriesPropertyObject> GetSingleTimeseriesPropertyCollectionByTimeseries( Guid? timeseries );
        IList<SingleTimeseriesPropertyObject> GetSingleTimeseriesPropertyCollectionByTimeseriesIsNull(  );
        // ---------------------------------------------------------------------
        // StringTimeseriesProperty queries
        // ---------------------------------------------------------------------
        StringTimeseriesPropertyObject? GetStringTimeseriesPropertyById( Guid id );
        IList<StringTimeseriesPropertyObject> GetStringTimeseriesPropertyCollection( );
        IList<StringTimeseriesPropertyObject> GetStringTimeseriesPropertyCollectionByElement( Guid element );
        StringTimeseriesPropertyObject? GetStringTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
        IList<StringTimeseriesPropertyObject> GetStringTimeseriesPropertyCollectionByDefinition( Guid definition );
        IList<StringTimeseriesPropertyObject> GetStringTimeseriesPropertyCollectionByTimeseries( Guid? timeseries );
        IList<StringTimeseriesPropertyObject> GetStringTimeseriesPropertyCollectionByTimeseriesIsNull(  );
        // ---------------------------------------------------------------------
        // TimeSpanTimeseriesProperty queries
        // ---------------------------------------------------------------------
        TimeSpanTimeseriesPropertyObject? GetTimeSpanTimeseriesPropertyById( Guid id );
        IList<TimeSpanTimeseriesPropertyObject> GetTimeSpanTimeseriesPropertyCollection( );
        IList<TimeSpanTimeseriesPropertyObject> GetTimeSpanTimeseriesPropertyCollectionByElement( Guid element );
        TimeSpanTimeseriesPropertyObject? GetTimeSpanTimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
        IList<TimeSpanTimeseriesPropertyObject> GetTimeSpanTimeseriesPropertyCollectionByDefinition( Guid definition );
        IList<TimeSpanTimeseriesPropertyObject> GetTimeSpanTimeseriesPropertyCollectionByTimeseries( Guid? timeseries );
        IList<TimeSpanTimeseriesPropertyObject> GetTimeSpanTimeseriesPropertyCollectionByTimeseriesIsNull(  );
        // ---------------------------------------------------------------------
        // UInt16TimeseriesProperty queries
        // ---------------------------------------------------------------------
        UInt16TimeseriesPropertyObject? GetUInt16TimeseriesPropertyById( Guid id );
        IList<UInt16TimeseriesPropertyObject> GetUInt16TimeseriesPropertyCollection( );
        IList<UInt16TimeseriesPropertyObject> GetUInt16TimeseriesPropertyCollectionByElement( Guid element );
        UInt16TimeseriesPropertyObject? GetUInt16TimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
        IList<UInt16TimeseriesPropertyObject> GetUInt16TimeseriesPropertyCollectionByDefinition( Guid definition );
        IList<UInt16TimeseriesPropertyObject> GetUInt16TimeseriesPropertyCollectionByTimeseries( Guid? timeseries );
        IList<UInt16TimeseriesPropertyObject> GetUInt16TimeseriesPropertyCollectionByTimeseriesIsNull(  );
        // ---------------------------------------------------------------------
        // UInt32TimeseriesProperty queries
        // ---------------------------------------------------------------------
        UInt32TimeseriesPropertyObject? GetUInt32TimeseriesPropertyById( Guid id );
        IList<UInt32TimeseriesPropertyObject> GetUInt32TimeseriesPropertyCollection( );
        IList<UInt32TimeseriesPropertyObject> GetUInt32TimeseriesPropertyCollectionByElement( Guid element );
        UInt32TimeseriesPropertyObject? GetUInt32TimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
        IList<UInt32TimeseriesPropertyObject> GetUInt32TimeseriesPropertyCollectionByDefinition( Guid definition );
        IList<UInt32TimeseriesPropertyObject> GetUInt32TimeseriesPropertyCollectionByTimeseries( Guid? timeseries );
        IList<UInt32TimeseriesPropertyObject> GetUInt32TimeseriesPropertyCollectionByTimeseriesIsNull(  );
        // ---------------------------------------------------------------------
        // UInt64TimeseriesProperty queries
        // ---------------------------------------------------------------------
        UInt64TimeseriesPropertyObject? GetUInt64TimeseriesPropertyById( Guid id );
        IList<UInt64TimeseriesPropertyObject> GetUInt64TimeseriesPropertyCollection( );
        IList<UInt64TimeseriesPropertyObject> GetUInt64TimeseriesPropertyCollectionByElement( Guid element );
        UInt64TimeseriesPropertyObject? GetUInt64TimeseriesPropertyByElementAndDefinition( Guid element, Guid definition );
        IList<UInt64TimeseriesPropertyObject> GetUInt64TimeseriesPropertyCollectionByDefinition( Guid definition );
        IList<UInt64TimeseriesPropertyObject> GetUInt64TimeseriesPropertyCollectionByTimeseries( Guid? timeseries );
        IList<UInt64TimeseriesPropertyObject> GetUInt64TimeseriesPropertyCollectionByTimeseriesIsNull(  );
        // ---------------------------------------------------------------------
        // TimeSpanProperty queries
        // ---------------------------------------------------------------------
        TimeSpanPropertyObject? GetTimeSpanPropertyById( Guid id );
        IList<TimeSpanPropertyObject> GetTimeSpanPropertyCollection( );
        IList<TimeSpanPropertyObject> GetTimeSpanPropertyCollectionByElement( Guid element );
        TimeSpanPropertyObject? GetTimeSpanPropertyByElementAndDefinition( Guid element, Guid definition );
        IList<TimeSpanPropertyObject> GetTimeSpanPropertyCollectionByDefinition( Guid definition );
        // ---------------------------------------------------------------------
        // UInt16Property queries
        // ---------------------------------------------------------------------
        UInt16PropertyObject? GetUInt16PropertyById( Guid id );
        IList<UInt16PropertyObject> GetUInt16PropertyCollection( );
        IList<UInt16PropertyObject> GetUInt16PropertyCollectionByElement( Guid element );
        UInt16PropertyObject? GetUInt16PropertyByElementAndDefinition( Guid element, Guid definition );
        IList<UInt16PropertyObject> GetUInt16PropertyCollectionByDefinition( Guid definition );
        // ---------------------------------------------------------------------
        // UInt32Property queries
        // ---------------------------------------------------------------------
        UInt32PropertyObject? GetUInt32PropertyById( Guid id );
        IList<UInt32PropertyObject> GetUInt32PropertyCollection( );
        IList<UInt32PropertyObject> GetUInt32PropertyCollectionByElement( Guid element );
        UInt32PropertyObject? GetUInt32PropertyByElementAndDefinition( Guid element, Guid definition );
        IList<UInt32PropertyObject> GetUInt32PropertyCollectionByDefinition( Guid definition );
        // ---------------------------------------------------------------------
        // UInt64Property queries
        // ---------------------------------------------------------------------
        UInt64PropertyObject? GetUInt64PropertyById( Guid id );
        IList<UInt64PropertyObject> GetUInt64PropertyCollection( );
        IList<UInt64PropertyObject> GetUInt64PropertyCollectionByElement( Guid element );
        UInt64PropertyObject? GetUInt64PropertyByElementAndDefinition( Guid element, Guid definition );
        IList<UInt64PropertyObject> GetUInt64PropertyCollectionByDefinition( Guid definition );
        // ---------------------------------------------------------------------
        // PropertyDefinition queries
        // ---------------------------------------------------------------------
        PropertyDefinitionObject? GetPropertyDefinitionById( Guid id );
        IList<PropertyDefinitionObject> GetPropertyDefinitionCollection( );
        IList<PropertyDefinitionObject> GetPropertyDefinitionCollectionByElementType( Guid elementType );
        PropertyDefinitionObject? GetPropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // BinaryPropertyDefinition queries
        // ---------------------------------------------------------------------
        BinaryPropertyDefinitionObject? GetBinaryPropertyDefinitionById( Guid id );
        IList<BinaryPropertyDefinitionObject> GetBinaryPropertyDefinitionCollection( );
        IList<BinaryPropertyDefinitionObject> GetBinaryPropertyDefinitionCollectionByElementType( Guid elementType );
        BinaryPropertyDefinitionObject? GetBinaryPropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // BooleanPropertyDefinition queries
        // ---------------------------------------------------------------------
        BooleanPropertyDefinitionObject? GetBooleanPropertyDefinitionById( Guid id );
        IList<BooleanPropertyDefinitionObject> GetBooleanPropertyDefinitionCollection( );
        IList<BooleanPropertyDefinitionObject> GetBooleanPropertyDefinitionCollectionByElementType( Guid elementType );
        BooleanPropertyDefinitionObject? GetBooleanPropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // BytePropertyDefinition queries
        // ---------------------------------------------------------------------
        BytePropertyDefinitionObject? GetBytePropertyDefinitionById( Guid id );
        IList<BytePropertyDefinitionObject> GetBytePropertyDefinitionCollection( );
        IList<BytePropertyDefinitionObject> GetBytePropertyDefinitionCollectionByElementType( Guid elementType );
        BytePropertyDefinitionObject? GetBytePropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // DateTimePropertyDefinition queries
        // ---------------------------------------------------------------------
        DateTimePropertyDefinitionObject? GetDateTimePropertyDefinitionById( Guid id );
        IList<DateTimePropertyDefinitionObject> GetDateTimePropertyDefinitionCollection( );
        IList<DateTimePropertyDefinitionObject> GetDateTimePropertyDefinitionCollectionByElementType( Guid elementType );
        DateTimePropertyDefinitionObject? GetDateTimePropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // DoublePropertyDefinition queries
        // ---------------------------------------------------------------------
        DoublePropertyDefinitionObject? GetDoublePropertyDefinitionById( Guid id );
        IList<DoublePropertyDefinitionObject> GetDoublePropertyDefinitionCollection( );
        IList<DoublePropertyDefinitionObject> GetDoublePropertyDefinitionCollectionByElementType( Guid elementType );
        DoublePropertyDefinitionObject? GetDoublePropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // GuidPropertyDefinition queries
        // ---------------------------------------------------------------------
        GuidPropertyDefinitionObject? GetGuidPropertyDefinitionById( Guid id );
        IList<GuidPropertyDefinitionObject> GetGuidPropertyDefinitionCollection( );
        IList<GuidPropertyDefinitionObject> GetGuidPropertyDefinitionCollectionByElementType( Guid elementType );
        GuidPropertyDefinitionObject? GetGuidPropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // Int16PropertyDefinition queries
        // ---------------------------------------------------------------------
        Int16PropertyDefinitionObject? GetInt16PropertyDefinitionById( Guid id );
        IList<Int16PropertyDefinitionObject> GetInt16PropertyDefinitionCollection( );
        IList<Int16PropertyDefinitionObject> GetInt16PropertyDefinitionCollectionByElementType( Guid elementType );
        Int16PropertyDefinitionObject? GetInt16PropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // Int32PropertyDefinition queries
        // ---------------------------------------------------------------------
        Int32PropertyDefinitionObject? GetInt32PropertyDefinitionById( Guid id );
        IList<Int32PropertyDefinitionObject> GetInt32PropertyDefinitionCollection( );
        IList<Int32PropertyDefinitionObject> GetInt32PropertyDefinitionCollectionByElementType( Guid elementType );
        Int32PropertyDefinitionObject? GetInt32PropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // Int64PropertyDefinition queries
        // ---------------------------------------------------------------------
        Int64PropertyDefinitionObject? GetInt64PropertyDefinitionById( Guid id );
        IList<Int64PropertyDefinitionObject> GetInt64PropertyDefinitionCollection( );
        IList<Int64PropertyDefinitionObject> GetInt64PropertyDefinitionCollectionByElementType( Guid elementType );
        Int64PropertyDefinitionObject? GetInt64PropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // ReferencePropertyDefinition queries
        // ---------------------------------------------------------------------
        ReferencePropertyDefinitionObject? GetReferencePropertyDefinitionById( Guid id );
        IList<ReferencePropertyDefinitionObject> GetReferencePropertyDefinitionCollection( );
        IList<ReferencePropertyDefinitionObject> GetReferencePropertyDefinitionCollectionByElementType( Guid elementType );
        ReferencePropertyDefinitionObject? GetReferencePropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        IList<ReferencePropertyDefinitionObject> GetReferencePropertyDefinitionCollectionByDefaultValue( Guid? defaultValue );
        IList<ReferencePropertyDefinitionObject> GetReferencePropertyDefinitionCollectionByDefaultValueIsNull(  );
        IList<ReferencePropertyDefinitionObject> GetReferencePropertyDefinitionCollectionByReferencedElementType( Guid? referencedElementType );
        IList<ReferencePropertyDefinitionObject> GetReferencePropertyDefinitionCollectionByReferencedElementTypeIsNull(  );
        // ---------------------------------------------------------------------
        // SBytePropertyDefinition queries
        // ---------------------------------------------------------------------
        SBytePropertyDefinitionObject? GetSBytePropertyDefinitionById( Guid id );
        IList<SBytePropertyDefinitionObject> GetSBytePropertyDefinitionCollection( );
        IList<SBytePropertyDefinitionObject> GetSBytePropertyDefinitionCollectionByElementType( Guid elementType );
        SBytePropertyDefinitionObject? GetSBytePropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // SinglePropertyDefinition queries
        // ---------------------------------------------------------------------
        SinglePropertyDefinitionObject? GetSinglePropertyDefinitionById( Guid id );
        IList<SinglePropertyDefinitionObject> GetSinglePropertyDefinitionCollection( );
        IList<SinglePropertyDefinitionObject> GetSinglePropertyDefinitionCollectionByElementType( Guid elementType );
        SinglePropertyDefinitionObject? GetSinglePropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // StringPropertyDefinition queries
        // ---------------------------------------------------------------------
        StringPropertyDefinitionObject? GetStringPropertyDefinitionById( Guid id );
        IList<StringPropertyDefinitionObject> GetStringPropertyDefinitionCollection( );
        IList<StringPropertyDefinitionObject> GetStringPropertyDefinitionCollectionByElementType( Guid elementType );
        StringPropertyDefinitionObject? GetStringPropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // TimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        TimeseriesPropertyDefinitionObject? GetTimeseriesPropertyDefinitionById( Guid id );
        IList<TimeseriesPropertyDefinitionObject> GetTimeseriesPropertyDefinitionCollection( );
        IList<TimeseriesPropertyDefinitionObject> GetTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
        TimeseriesPropertyDefinitionObject? GetTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // BinaryTimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        BinaryTimeseriesPropertyDefinitionObject? GetBinaryTimeseriesPropertyDefinitionById( Guid id );
        IList<BinaryTimeseriesPropertyDefinitionObject> GetBinaryTimeseriesPropertyDefinitionCollection( );
        IList<BinaryTimeseriesPropertyDefinitionObject> GetBinaryTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
        BinaryTimeseriesPropertyDefinitionObject? GetBinaryTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // BooleanTimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        BooleanTimeseriesPropertyDefinitionObject? GetBooleanTimeseriesPropertyDefinitionById( Guid id );
        IList<BooleanTimeseriesPropertyDefinitionObject> GetBooleanTimeseriesPropertyDefinitionCollection( );
        IList<BooleanTimeseriesPropertyDefinitionObject> GetBooleanTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
        BooleanTimeseriesPropertyDefinitionObject? GetBooleanTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // ByteTimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        ByteTimeseriesPropertyDefinitionObject? GetByteTimeseriesPropertyDefinitionById( Guid id );
        IList<ByteTimeseriesPropertyDefinitionObject> GetByteTimeseriesPropertyDefinitionCollection( );
        IList<ByteTimeseriesPropertyDefinitionObject> GetByteTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
        ByteTimeseriesPropertyDefinitionObject? GetByteTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // DateTimeTimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        DateTimeTimeseriesPropertyDefinitionObject? GetDateTimeTimeseriesPropertyDefinitionById( Guid id );
        IList<DateTimeTimeseriesPropertyDefinitionObject> GetDateTimeTimeseriesPropertyDefinitionCollection( );
        IList<DateTimeTimeseriesPropertyDefinitionObject> GetDateTimeTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
        DateTimeTimeseriesPropertyDefinitionObject? GetDateTimeTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // DoubleTimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        DoubleTimeseriesPropertyDefinitionObject? GetDoubleTimeseriesPropertyDefinitionById( Guid id );
        IList<DoubleTimeseriesPropertyDefinitionObject> GetDoubleTimeseriesPropertyDefinitionCollection( );
        IList<DoubleTimeseriesPropertyDefinitionObject> GetDoubleTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
        DoubleTimeseriesPropertyDefinitionObject? GetDoubleTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // GuidTimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        GuidTimeseriesPropertyDefinitionObject? GetGuidTimeseriesPropertyDefinitionById( Guid id );
        IList<GuidTimeseriesPropertyDefinitionObject> GetGuidTimeseriesPropertyDefinitionCollection( );
        IList<GuidTimeseriesPropertyDefinitionObject> GetGuidTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
        GuidTimeseriesPropertyDefinitionObject? GetGuidTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // Int16TimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        Int16TimeseriesPropertyDefinitionObject? GetInt16TimeseriesPropertyDefinitionById( Guid id );
        IList<Int16TimeseriesPropertyDefinitionObject> GetInt16TimeseriesPropertyDefinitionCollection( );
        IList<Int16TimeseriesPropertyDefinitionObject> GetInt16TimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
        Int16TimeseriesPropertyDefinitionObject? GetInt16TimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // Int32TimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        Int32TimeseriesPropertyDefinitionObject? GetInt32TimeseriesPropertyDefinitionById( Guid id );
        IList<Int32TimeseriesPropertyDefinitionObject> GetInt32TimeseriesPropertyDefinitionCollection( );
        IList<Int32TimeseriesPropertyDefinitionObject> GetInt32TimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
        Int32TimeseriesPropertyDefinitionObject? GetInt32TimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // Int64TimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        Int64TimeseriesPropertyDefinitionObject? GetInt64TimeseriesPropertyDefinitionById( Guid id );
        IList<Int64TimeseriesPropertyDefinitionObject> GetInt64TimeseriesPropertyDefinitionCollection( );
        IList<Int64TimeseriesPropertyDefinitionObject> GetInt64TimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
        Int64TimeseriesPropertyDefinitionObject? GetInt64TimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // ReferenceTimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        ReferenceTimeseriesPropertyDefinitionObject? GetReferenceTimeseriesPropertyDefinitionById( Guid id );
        IList<ReferenceTimeseriesPropertyDefinitionObject> GetReferenceTimeseriesPropertyDefinitionCollection( );
        IList<ReferenceTimeseriesPropertyDefinitionObject> GetReferenceTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
        ReferenceTimeseriesPropertyDefinitionObject? GetReferenceTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        IList<ReferenceTimeseriesPropertyDefinitionObject> GetReferenceTimeseriesPropertyDefinitionCollectionByReferencedElementType( Guid? referencedElementType );
        IList<ReferenceTimeseriesPropertyDefinitionObject> GetReferenceTimeseriesPropertyDefinitionCollectionByReferencedElementTypeIsNull(  );
        // ---------------------------------------------------------------------
        // SByteTimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        SByteTimeseriesPropertyDefinitionObject? GetSByteTimeseriesPropertyDefinitionById( Guid id );
        IList<SByteTimeseriesPropertyDefinitionObject> GetSByteTimeseriesPropertyDefinitionCollection( );
        IList<SByteTimeseriesPropertyDefinitionObject> GetSByteTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
        SByteTimeseriesPropertyDefinitionObject? GetSByteTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // SingleTimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        SingleTimeseriesPropertyDefinitionObject? GetSingleTimeseriesPropertyDefinitionById( Guid id );
        IList<SingleTimeseriesPropertyDefinitionObject> GetSingleTimeseriesPropertyDefinitionCollection( );
        IList<SingleTimeseriesPropertyDefinitionObject> GetSingleTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
        SingleTimeseriesPropertyDefinitionObject? GetSingleTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // StringTimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        StringTimeseriesPropertyDefinitionObject? GetStringTimeseriesPropertyDefinitionById( Guid id );
        IList<StringTimeseriesPropertyDefinitionObject> GetStringTimeseriesPropertyDefinitionCollection( );
        IList<StringTimeseriesPropertyDefinitionObject> GetStringTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
        StringTimeseriesPropertyDefinitionObject? GetStringTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // TimeSpanTimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        TimeSpanTimeseriesPropertyDefinitionObject? GetTimeSpanTimeseriesPropertyDefinitionById( Guid id );
        IList<TimeSpanTimeseriesPropertyDefinitionObject> GetTimeSpanTimeseriesPropertyDefinitionCollection( );
        IList<TimeSpanTimeseriesPropertyDefinitionObject> GetTimeSpanTimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
        TimeSpanTimeseriesPropertyDefinitionObject? GetTimeSpanTimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // UInt16TimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        UInt16TimeseriesPropertyDefinitionObject? GetUInt16TimeseriesPropertyDefinitionById( Guid id );
        IList<UInt16TimeseriesPropertyDefinitionObject> GetUInt16TimeseriesPropertyDefinitionCollection( );
        IList<UInt16TimeseriesPropertyDefinitionObject> GetUInt16TimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
        UInt16TimeseriesPropertyDefinitionObject? GetUInt16TimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // UInt32TimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        UInt32TimeseriesPropertyDefinitionObject? GetUInt32TimeseriesPropertyDefinitionById( Guid id );
        IList<UInt32TimeseriesPropertyDefinitionObject> GetUInt32TimeseriesPropertyDefinitionCollection( );
        IList<UInt32TimeseriesPropertyDefinitionObject> GetUInt32TimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
        UInt32TimeseriesPropertyDefinitionObject? GetUInt32TimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // UInt64TimeseriesPropertyDefinition queries
        // ---------------------------------------------------------------------
        UInt64TimeseriesPropertyDefinitionObject? GetUInt64TimeseriesPropertyDefinitionById( Guid id );
        IList<UInt64TimeseriesPropertyDefinitionObject> GetUInt64TimeseriesPropertyDefinitionCollection( );
        IList<UInt64TimeseriesPropertyDefinitionObject> GetUInt64TimeseriesPropertyDefinitionCollectionByElementType( Guid elementType );
        UInt64TimeseriesPropertyDefinitionObject? GetUInt64TimeseriesPropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // TimeSpanPropertyDefinition queries
        // ---------------------------------------------------------------------
        TimeSpanPropertyDefinitionObject? GetTimeSpanPropertyDefinitionById( Guid id );
        IList<TimeSpanPropertyDefinitionObject> GetTimeSpanPropertyDefinitionCollection( );
        IList<TimeSpanPropertyDefinitionObject> GetTimeSpanPropertyDefinitionCollectionByElementType( Guid elementType );
        TimeSpanPropertyDefinitionObject? GetTimeSpanPropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // UInt16PropertyDefinition queries
        // ---------------------------------------------------------------------
        UInt16PropertyDefinitionObject? GetUInt16PropertyDefinitionById( Guid id );
        IList<UInt16PropertyDefinitionObject> GetUInt16PropertyDefinitionCollection( );
        IList<UInt16PropertyDefinitionObject> GetUInt16PropertyDefinitionCollectionByElementType( Guid elementType );
        UInt16PropertyDefinitionObject? GetUInt16PropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // UInt32PropertyDefinition queries
        // ---------------------------------------------------------------------
        UInt32PropertyDefinitionObject? GetUInt32PropertyDefinitionById( Guid id );
        IList<UInt32PropertyDefinitionObject> GetUInt32PropertyDefinitionCollection( );
        IList<UInt32PropertyDefinitionObject> GetUInt32PropertyDefinitionCollectionByElementType( Guid elementType );
        UInt32PropertyDefinitionObject? GetUInt32PropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // UInt64PropertyDefinition queries
        // ---------------------------------------------------------------------
        UInt64PropertyDefinitionObject? GetUInt64PropertyDefinitionById( Guid id );
        IList<UInt64PropertyDefinitionObject> GetUInt64PropertyDefinitionCollection( );
        IList<UInt64PropertyDefinitionObject> GetUInt64PropertyDefinitionCollectionByElementType( Guid elementType );
        UInt64PropertyDefinitionObject? GetUInt64PropertyDefinitionByElementTypeAndName( Guid elementType, string name );
        // ---------------------------------------------------------------------
        // RadarAlarmStatus queries
        // ---------------------------------------------------------------------
        RadarAlarmStatusObject? GetRadarAlarmStatusById( Guid id );
        IList<RadarAlarmStatusObject> GetRadarAlarmStatusCollection( );
        IList<RadarAlarmStatusObject> GetRadarAlarmStatusCollectionByRadar( Guid radar );
        RadarAlarmStatusObject? GetRadarAlarmStatusByRadarAndTimestamp( Guid radar, DateTime timestamp );
        RadarAlarmStatusObject? GetRadarAlarmStatusByRadarAtTimestamp( Guid radar, DateTime timestamp );
        IList<RadarAlarmStatusObject> GetRadarAlarmStatusByRadarFromTimestamp( Guid radar, DateTime timestamp );
        IList<RadarAlarmStatusObject> GetRadarAlarmStatusByRadarUntilTimestamp( Guid radar, DateTime timestamp );
        IList<RadarAlarmStatusObject> GetRadarAlarmStatusByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<RadarAlarmStatusObject> GetRadarAlarmStatusCollectionByTimestamp( DateTime timestamp );
        IList<RadarAlarmStatusObject> GetRadarAlarmStatusCollectionAtTimestamp( DateTime timestamp );
        IList<RadarAlarmStatusObject> GetRadarAlarmStatusCollectionFromTimestamp( DateTime timestamp );
        IList<RadarAlarmStatusObject> GetRadarAlarmStatusCollectionUntilTimestamp( DateTime timestamp );
        IList<RadarAlarmStatusObject> GetRadarAlarmStatusCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // RadarCommand queries
        // ---------------------------------------------------------------------
        RadarCommandObject? GetRadarCommandById( Guid id );
        IList<RadarCommandObject> GetRadarCommandCollection( );
        IList<RadarCommandObject> GetRadarCommandCollectionByRadar( Guid radar );
        IList<RadarCommandObject> GetRadarCommandCollectionByRadarAndTimestamp( Guid radar, DateTime timestamp );
        IList<RadarCommandObject> GetRadarCommandCollectionByRadarAtTimestamp( Guid radar, DateTime timestamp );
        IList<RadarCommandObject> GetRadarCommandCollectionByRadarFromTimestamp( Guid radar, DateTime timestamp );
        IList<RadarCommandObject> GetRadarCommandCollectionByRadarUntilTimestamp( Guid radar, DateTime timestamp );
        IList<RadarCommandObject> GetRadarCommandCollectionByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<RadarCommandObject> GetRadarCommandCollectionByTimestamp( DateTime timestamp );
        IList<RadarCommandObject> GetRadarCommandCollectionAtTimestamp( DateTime timestamp );
        IList<RadarCommandObject> GetRadarCommandCollectionFromTimestamp( DateTime timestamp );
        IList<RadarCommandObject> GetRadarCommandCollectionUntilTimestamp( DateTime timestamp );
        IList<RadarCommandObject> GetRadarCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<RadarCommandObject> GetRadarCommandCollectionByReply( Guid? reply );
        IList<RadarCommandObject> GetRadarCommandCollectionByReplyIsNull(  );
        // ---------------------------------------------------------------------
        // RadarCommandGetStatus queries
        // ---------------------------------------------------------------------
        RadarCommandGetStatusObject? GetRadarCommandGetStatusById( Guid id );
        IList<RadarCommandGetStatusObject> GetRadarCommandGetStatusCollection( );
        IList<RadarCommandGetStatusObject> GetRadarCommandGetStatusCollectionByRadar( Guid radar );
        IList<RadarCommandGetStatusObject> GetRadarCommandGetStatusCollectionByRadarAndTimestamp( Guid radar, DateTime timestamp );
        IList<RadarCommandGetStatusObject> GetRadarCommandGetStatusCollectionByRadarAtTimestamp( Guid radar, DateTime timestamp );
        IList<RadarCommandGetStatusObject> GetRadarCommandGetStatusCollectionByRadarFromTimestamp( Guid radar, DateTime timestamp );
        IList<RadarCommandGetStatusObject> GetRadarCommandGetStatusCollectionByRadarUntilTimestamp( Guid radar, DateTime timestamp );
        IList<RadarCommandGetStatusObject> GetRadarCommandGetStatusCollectionByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<RadarCommandGetStatusObject> GetRadarCommandGetStatusCollectionByTimestamp( DateTime timestamp );
        IList<RadarCommandGetStatusObject> GetRadarCommandGetStatusCollectionAtTimestamp( DateTime timestamp );
        IList<RadarCommandGetStatusObject> GetRadarCommandGetStatusCollectionFromTimestamp( DateTime timestamp );
        IList<RadarCommandGetStatusObject> GetRadarCommandGetStatusCollectionUntilTimestamp( DateTime timestamp );
        IList<RadarCommandGetStatusObject> GetRadarCommandGetStatusCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<RadarCommandGetStatusObject> GetRadarCommandGetStatusCollectionByReply( Guid? reply );
        IList<RadarCommandGetStatusObject> GetRadarCommandGetStatusCollectionByReplyIsNull(  );
        // ---------------------------------------------------------------------
        // RadarCommandReply queries
        // ---------------------------------------------------------------------
        RadarCommandReplyObject? GetRadarCommandReplyById( Guid id );
        IList<RadarCommandReplyObject> GetRadarCommandReplyCollection( );
        IList<RadarCommandReplyObject> GetRadarCommandReplyCollectionByRadar( Guid radar );
        IList<RadarCommandReplyObject> GetRadarCommandReplyCollectionByRadarAndTimestamp( Guid radar, DateTime timestamp );
        IList<RadarCommandReplyObject> GetRadarCommandReplyCollectionByRadarAtTimestamp( Guid radar, DateTime timestamp );
        IList<RadarCommandReplyObject> GetRadarCommandReplyCollectionByRadarFromTimestamp( Guid radar, DateTime timestamp );
        IList<RadarCommandReplyObject> GetRadarCommandReplyCollectionByRadarUntilTimestamp( Guid radar, DateTime timestamp );
        IList<RadarCommandReplyObject> GetRadarCommandReplyCollectionByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<RadarCommandReplyObject> GetRadarCommandReplyCollectionByTimestamp( DateTime timestamp );
        IList<RadarCommandReplyObject> GetRadarCommandReplyCollectionAtTimestamp( DateTime timestamp );
        IList<RadarCommandReplyObject> GetRadarCommandReplyCollectionFromTimestamp( DateTime timestamp );
        IList<RadarCommandReplyObject> GetRadarCommandReplyCollectionUntilTimestamp( DateTime timestamp );
        IList<RadarCommandReplyObject> GetRadarCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        RadarCommandReplyObject? GetRadarCommandReplyByCommand( Guid? command );
        IList<RadarCommandReplyObject> GetRadarCommandReplyCollectionByCommandIsNull(  );
        // ---------------------------------------------------------------------
        // RadarCommandReplyGetStatus queries
        // ---------------------------------------------------------------------
        RadarCommandReplyGetStatusObject? GetRadarCommandReplyGetStatusById( Guid id );
        IList<RadarCommandReplyGetStatusObject> GetRadarCommandReplyGetStatusCollection( );
        IList<RadarCommandReplyGetStatusObject> GetRadarCommandReplyGetStatusCollectionByRadar( Guid radar );
        IList<RadarCommandReplyGetStatusObject> GetRadarCommandReplyGetStatusCollectionByRadarAndTimestamp( Guid radar, DateTime timestamp );
        IList<RadarCommandReplyGetStatusObject> GetRadarCommandReplyGetStatusCollectionByRadarAtTimestamp( Guid radar, DateTime timestamp );
        IList<RadarCommandReplyGetStatusObject> GetRadarCommandReplyGetStatusCollectionByRadarFromTimestamp( Guid radar, DateTime timestamp );
        IList<RadarCommandReplyGetStatusObject> GetRadarCommandReplyGetStatusCollectionByRadarUntilTimestamp( Guid radar, DateTime timestamp );
        IList<RadarCommandReplyGetStatusObject> GetRadarCommandReplyGetStatusCollectionByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<RadarCommandReplyGetStatusObject> GetRadarCommandReplyGetStatusCollectionByTimestamp( DateTime timestamp );
        IList<RadarCommandReplyGetStatusObject> GetRadarCommandReplyGetStatusCollectionAtTimestamp( DateTime timestamp );
        IList<RadarCommandReplyGetStatusObject> GetRadarCommandReplyGetStatusCollectionFromTimestamp( DateTime timestamp );
        IList<RadarCommandReplyGetStatusObject> GetRadarCommandReplyGetStatusCollectionUntilTimestamp( DateTime timestamp );
        IList<RadarCommandReplyGetStatusObject> GetRadarCommandReplyGetStatusCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        RadarCommandReplyGetStatusObject? GetRadarCommandReplyGetStatusByCommand( Guid? command );
        IList<RadarCommandReplyGetStatusObject> GetRadarCommandReplyGetStatusCollectionByCommandIsNull(  );
        // ---------------------------------------------------------------------
        // RadarConfiguration queries
        // ---------------------------------------------------------------------
        RadarConfigurationObject? GetRadarConfigurationById( Guid id );
        IList<RadarConfigurationObject> GetRadarConfigurationCollection( );
        IList<RadarConfigurationObject> GetRadarConfigurationCollectionByRadar( Guid radar );
        RadarConfigurationObject? GetRadarConfigurationByRadarAndTimestamp( Guid radar, DateTime timestamp );
        RadarConfigurationObject? GetRadarConfigurationByRadarAtTimestamp( Guid radar, DateTime timestamp );
        IList<RadarConfigurationObject> GetRadarConfigurationByRadarFromTimestamp( Guid radar, DateTime timestamp );
        IList<RadarConfigurationObject> GetRadarConfigurationByRadarUntilTimestamp( Guid radar, DateTime timestamp );
        IList<RadarConfigurationObject> GetRadarConfigurationByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<RadarConfigurationObject> GetRadarConfigurationCollectionByTimestamp( DateTime timestamp );
        IList<RadarConfigurationObject> GetRadarConfigurationCollectionAtTimestamp( DateTime timestamp );
        IList<RadarConfigurationObject> GetRadarConfigurationCollectionFromTimestamp( DateTime timestamp );
        IList<RadarConfigurationObject> GetRadarConfigurationCollectionUntilTimestamp( DateTime timestamp );
        IList<RadarConfigurationObject> GetRadarConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // RadarImage queries
        // ---------------------------------------------------------------------
        RadarImageObject? GetRadarImageById( Guid id );
        IList<RadarImageObject> GetRadarImageCollection( );
        IList<RadarImageObject> GetRadarImageCollectionByRadar( Guid radar );
        RadarImageObject? GetRadarImageByRadarAndTimestamp( Guid radar, DateTime timestamp );
        RadarImageObject? GetRadarImageByRadarAtTimestamp( Guid radar, DateTime timestamp );
        IList<RadarImageObject> GetRadarImageByRadarFromTimestamp( Guid radar, DateTime timestamp );
        IList<RadarImageObject> GetRadarImageByRadarUntilTimestamp( Guid radar, DateTime timestamp );
        IList<RadarImageObject> GetRadarImageByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<RadarImageObject> GetRadarImageCollectionByTimestamp( DateTime timestamp );
        IList<RadarImageObject> GetRadarImageCollectionAtTimestamp( DateTime timestamp );
        IList<RadarImageObject> GetRadarImageCollectionFromTimestamp( DateTime timestamp );
        IList<RadarImageObject> GetRadarImageCollectionUntilTimestamp( DateTime timestamp );
        IList<RadarImageObject> GetRadarImageCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // RadarRawTrackTable queries
        // ---------------------------------------------------------------------
        RadarRawTrackTableObject? GetRadarRawTrackTableById( Guid id );
        IList<RadarRawTrackTableObject> GetRadarRawTrackTableCollection( );
        IList<RadarRawTrackTableObject> GetRadarRawTrackTableCollectionByRadar( Guid radar );
        RadarRawTrackTableObject? GetRadarRawTrackTableByRadarAndTimestamp( Guid radar, DateTime timestamp );
        RadarRawTrackTableObject? GetRadarRawTrackTableByRadarAtTimestamp( Guid radar, DateTime timestamp );
        IList<RadarRawTrackTableObject> GetRadarRawTrackTableByRadarFromTimestamp( Guid radar, DateTime timestamp );
        IList<RadarRawTrackTableObject> GetRadarRawTrackTableByRadarUntilTimestamp( Guid radar, DateTime timestamp );
        IList<RadarRawTrackTableObject> GetRadarRawTrackTableByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<RadarRawTrackTableObject> GetRadarRawTrackTableCollectionByTimestamp( DateTime timestamp );
        IList<RadarRawTrackTableObject> GetRadarRawTrackTableCollectionAtTimestamp( DateTime timestamp );
        IList<RadarRawTrackTableObject> GetRadarRawTrackTableCollectionFromTimestamp( DateTime timestamp );
        IList<RadarRawTrackTableObject> GetRadarRawTrackTableCollectionUntilTimestamp( DateTime timestamp );
        IList<RadarRawTrackTableObject> GetRadarRawTrackTableCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // RadarStatus queries
        // ---------------------------------------------------------------------
        RadarStatusObject? GetRadarStatusById( Guid id );
        IList<RadarStatusObject> GetRadarStatusCollection( );
        IList<RadarStatusObject> GetRadarStatusCollectionByRadar( Guid radar );
        RadarStatusObject? GetRadarStatusByRadarAndTimestamp( Guid radar, DateTime timestamp );
        RadarStatusObject? GetRadarStatusByRadarAtTimestamp( Guid radar, DateTime timestamp );
        IList<RadarStatusObject> GetRadarStatusByRadarFromTimestamp( Guid radar, DateTime timestamp );
        IList<RadarStatusObject> GetRadarStatusByRadarUntilTimestamp( Guid radar, DateTime timestamp );
        IList<RadarStatusObject> GetRadarStatusByRadarOverTimestamp( Guid radar, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<RadarStatusObject> GetRadarStatusCollectionByTimestamp( DateTime timestamp );
        IList<RadarStatusObject> GetRadarStatusCollectionAtTimestamp( DateTime timestamp );
        IList<RadarStatusObject> GetRadarStatusCollectionFromTimestamp( DateTime timestamp );
        IList<RadarStatusObject> GetRadarStatusCollectionUntilTimestamp( DateTime timestamp );
        IList<RadarStatusObject> GetRadarStatusCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // RadioCommand queries
        // ---------------------------------------------------------------------
        RadioCommandObject? GetRadioCommandById( Guid id );
        IList<RadioCommandObject> GetRadioCommandCollection( );
        IList<RadioCommandObject> GetRadioCommandCollectionByRadio( Guid radio );
        IList<RadioCommandObject> GetRadioCommandCollectionByRadioAndTimestamp( Guid radio, DateTime timestamp );
        IList<RadioCommandObject> GetRadioCommandCollectionByRadioAtTimestamp( Guid radio, DateTime timestamp );
        IList<RadioCommandObject> GetRadioCommandCollectionByRadioFromTimestamp( Guid radio, DateTime timestamp );
        IList<RadioCommandObject> GetRadioCommandCollectionByRadioUntilTimestamp( Guid radio, DateTime timestamp );
        IList<RadioCommandObject> GetRadioCommandCollectionByRadioOverTimestamp( Guid radio, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<RadioCommandObject> GetRadioCommandCollectionByTimestamp( DateTime timestamp );
        IList<RadioCommandObject> GetRadioCommandCollectionAtTimestamp( DateTime timestamp );
        IList<RadioCommandObject> GetRadioCommandCollectionFromTimestamp( DateTime timestamp );
        IList<RadioCommandObject> GetRadioCommandCollectionUntilTimestamp( DateTime timestamp );
        IList<RadioCommandObject> GetRadioCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<RadioCommandObject> GetRadioCommandCollectionByReply( Guid? reply );
        IList<RadioCommandObject> GetRadioCommandCollectionByReplyIsNull(  );
        // ---------------------------------------------------------------------
        // RadioCommandReply queries
        // ---------------------------------------------------------------------
        RadioCommandReplyObject? GetRadioCommandReplyById( Guid id );
        IList<RadioCommandReplyObject> GetRadioCommandReplyCollection( );
        IList<RadioCommandReplyObject> GetRadioCommandReplyCollectionByRadio( Guid radio );
        IList<RadioCommandReplyObject> GetRadioCommandReplyCollectionByRadioAndTimestamp( Guid radio, DateTime timestamp );
        IList<RadioCommandReplyObject> GetRadioCommandReplyCollectionByRadioAtTimestamp( Guid radio, DateTime timestamp );
        IList<RadioCommandReplyObject> GetRadioCommandReplyCollectionByRadioFromTimestamp( Guid radio, DateTime timestamp );
        IList<RadioCommandReplyObject> GetRadioCommandReplyCollectionByRadioUntilTimestamp( Guid radio, DateTime timestamp );
        IList<RadioCommandReplyObject> GetRadioCommandReplyCollectionByRadioOverTimestamp( Guid radio, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<RadioCommandReplyObject> GetRadioCommandReplyCollectionByTimestamp( DateTime timestamp );
        IList<RadioCommandReplyObject> GetRadioCommandReplyCollectionAtTimestamp( DateTime timestamp );
        IList<RadioCommandReplyObject> GetRadioCommandReplyCollectionFromTimestamp( DateTime timestamp );
        IList<RadioCommandReplyObject> GetRadioCommandReplyCollectionUntilTimestamp( DateTime timestamp );
        IList<RadioCommandReplyObject> GetRadioCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        RadioCommandReplyObject? GetRadioCommandReplyByCommand( Guid? command );
        IList<RadioCommandReplyObject> GetRadioCommandReplyCollectionByCommandIsNull(  );
        // ---------------------------------------------------------------------
        // RadioConfiguration queries
        // ---------------------------------------------------------------------
        RadioConfigurationObject? GetRadioConfigurationById( Guid id );
        IList<RadioConfigurationObject> GetRadioConfigurationCollection( );
        IList<RadioConfigurationObject> GetRadioConfigurationCollectionByRadio( Guid radio );
        RadioConfigurationObject? GetRadioConfigurationByRadioAndTimestamp( Guid radio, DateTime timestamp );
        RadioConfigurationObject? GetRadioConfigurationByRadioAtTimestamp( Guid radio, DateTime timestamp );
        IList<RadioConfigurationObject> GetRadioConfigurationByRadioFromTimestamp( Guid radio, DateTime timestamp );
        IList<RadioConfigurationObject> GetRadioConfigurationByRadioUntilTimestamp( Guid radio, DateTime timestamp );
        IList<RadioConfigurationObject> GetRadioConfigurationByRadioOverTimestamp( Guid radio, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<RadioConfigurationObject> GetRadioConfigurationCollectionByTimestamp( DateTime timestamp );
        IList<RadioConfigurationObject> GetRadioConfigurationCollectionAtTimestamp( DateTime timestamp );
        IList<RadioConfigurationObject> GetRadioConfigurationCollectionFromTimestamp( DateTime timestamp );
        IList<RadioConfigurationObject> GetRadioConfigurationCollectionUntilTimestamp( DateTime timestamp );
        IList<RadioConfigurationObject> GetRadioConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // RadomeCommand queries
        // ---------------------------------------------------------------------
        RadomeCommandObject? GetRadomeCommandById( Guid id );
        IList<RadomeCommandObject> GetRadomeCommandCollection( );
        IList<RadomeCommandObject> GetRadomeCommandCollectionByRadome( Guid radome );
        IList<RadomeCommandObject> GetRadomeCommandCollectionByRadomeAndTimestamp( Guid radome, DateTime timestamp );
        IList<RadomeCommandObject> GetRadomeCommandCollectionByRadomeAtTimestamp( Guid radome, DateTime timestamp );
        IList<RadomeCommandObject> GetRadomeCommandCollectionByRadomeFromTimestamp( Guid radome, DateTime timestamp );
        IList<RadomeCommandObject> GetRadomeCommandCollectionByRadomeUntilTimestamp( Guid radome, DateTime timestamp );
        IList<RadomeCommandObject> GetRadomeCommandCollectionByRadomeOverTimestamp( Guid radome, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<RadomeCommandObject> GetRadomeCommandCollectionByTimestamp( DateTime timestamp );
        IList<RadomeCommandObject> GetRadomeCommandCollectionAtTimestamp( DateTime timestamp );
        IList<RadomeCommandObject> GetRadomeCommandCollectionFromTimestamp( DateTime timestamp );
        IList<RadomeCommandObject> GetRadomeCommandCollectionUntilTimestamp( DateTime timestamp );
        IList<RadomeCommandObject> GetRadomeCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<RadomeCommandObject> GetRadomeCommandCollectionByReply( Guid? reply );
        IList<RadomeCommandObject> GetRadomeCommandCollectionByReplyIsNull(  );
        // ---------------------------------------------------------------------
        // RadomeCommandReply queries
        // ---------------------------------------------------------------------
        RadomeCommandReplyObject? GetRadomeCommandReplyById( Guid id );
        IList<RadomeCommandReplyObject> GetRadomeCommandReplyCollection( );
        IList<RadomeCommandReplyObject> GetRadomeCommandReplyCollectionByRadome( Guid radome );
        IList<RadomeCommandReplyObject> GetRadomeCommandReplyCollectionByRadomeAndTimestamp( Guid radome, DateTime timestamp );
        IList<RadomeCommandReplyObject> GetRadomeCommandReplyCollectionByRadomeAtTimestamp( Guid radome, DateTime timestamp );
        IList<RadomeCommandReplyObject> GetRadomeCommandReplyCollectionByRadomeFromTimestamp( Guid radome, DateTime timestamp );
        IList<RadomeCommandReplyObject> GetRadomeCommandReplyCollectionByRadomeUntilTimestamp( Guid radome, DateTime timestamp );
        IList<RadomeCommandReplyObject> GetRadomeCommandReplyCollectionByRadomeOverTimestamp( Guid radome, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<RadomeCommandReplyObject> GetRadomeCommandReplyCollectionByTimestamp( DateTime timestamp );
        IList<RadomeCommandReplyObject> GetRadomeCommandReplyCollectionAtTimestamp( DateTime timestamp );
        IList<RadomeCommandReplyObject> GetRadomeCommandReplyCollectionFromTimestamp( DateTime timestamp );
        IList<RadomeCommandReplyObject> GetRadomeCommandReplyCollectionUntilTimestamp( DateTime timestamp );
        IList<RadomeCommandReplyObject> GetRadomeCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        RadomeCommandReplyObject? GetRadomeCommandReplyByCommand( Guid? command );
        IList<RadomeCommandReplyObject> GetRadomeCommandReplyCollectionByCommandIsNull(  );
        // ---------------------------------------------------------------------
        // RadomeConfiguration queries
        // ---------------------------------------------------------------------
        RadomeConfigurationObject? GetRadomeConfigurationById( Guid id );
        IList<RadomeConfigurationObject> GetRadomeConfigurationCollection( );
        IList<RadomeConfigurationObject> GetRadomeConfigurationCollectionByRadome( Guid radome );
        RadomeConfigurationObject? GetRadomeConfigurationByRadomeAndTimestamp( Guid radome, DateTime timestamp );
        RadomeConfigurationObject? GetRadomeConfigurationByRadomeAtTimestamp( Guid radome, DateTime timestamp );
        IList<RadomeConfigurationObject> GetRadomeConfigurationByRadomeFromTimestamp( Guid radome, DateTime timestamp );
        IList<RadomeConfigurationObject> GetRadomeConfigurationByRadomeUntilTimestamp( Guid radome, DateTime timestamp );
        IList<RadomeConfigurationObject> GetRadomeConfigurationByRadomeOverTimestamp( Guid radome, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<RadomeConfigurationObject> GetRadomeConfigurationCollectionByTimestamp( DateTime timestamp );
        IList<RadomeConfigurationObject> GetRadomeConfigurationCollectionAtTimestamp( DateTime timestamp );
        IList<RadomeConfigurationObject> GetRadomeConfigurationCollectionFromTimestamp( DateTime timestamp );
        IList<RadomeConfigurationObject> GetRadomeConfigurationCollectionUntilTimestamp( DateTime timestamp );
        IList<RadomeConfigurationObject> GetRadomeConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // ReferenceTimeseriesValue queries
        // ---------------------------------------------------------------------
        ReferenceTimeseriesValueObject? GetReferenceTimeseriesValueById( Guid id );
        IList<ReferenceTimeseriesValueObject> GetReferenceTimeseriesValueCollection( );
        IList<ReferenceTimeseriesValueObject> GetReferenceTimeseriesValueCollectionByTimeseries( Guid timeseries );
        ReferenceTimeseriesValueObject? GetReferenceTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
        ReferenceTimeseriesValueObject? GetReferenceTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
        IList<ReferenceTimeseriesValueObject> GetReferenceTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
        IList<ReferenceTimeseriesValueObject> GetReferenceTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
        IList<ReferenceTimeseriesValueObject> GetReferenceTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<ReferenceTimeseriesValueObject> GetReferenceTimeseriesValueCollectionByTimestamp( DateTime timestamp );
        IList<ReferenceTimeseriesValueObject> GetReferenceTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
        IList<ReferenceTimeseriesValueObject> GetReferenceTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
        IList<ReferenceTimeseriesValueObject> GetReferenceTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
        IList<ReferenceTimeseriesValueObject> GetReferenceTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<ReferenceTimeseriesValueObject> GetReferenceTimeseriesValueCollectionByValue( Guid value__ );
        // ---------------------------------------------------------------------
        // SByteTimeseriesValue queries
        // ---------------------------------------------------------------------
        SByteTimeseriesValueObject? GetSByteTimeseriesValueById( Guid id );
        IList<SByteTimeseriesValueObject> GetSByteTimeseriesValueCollection( );
        IList<SByteTimeseriesValueObject> GetSByteTimeseriesValueCollectionByTimeseries( Guid timeseries );
        SByteTimeseriesValueObject? GetSByteTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
        SByteTimeseriesValueObject? GetSByteTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
        IList<SByteTimeseriesValueObject> GetSByteTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
        IList<SByteTimeseriesValueObject> GetSByteTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
        IList<SByteTimeseriesValueObject> GetSByteTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<SByteTimeseriesValueObject> GetSByteTimeseriesValueCollectionByTimestamp( DateTime timestamp );
        IList<SByteTimeseriesValueObject> GetSByteTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
        IList<SByteTimeseriesValueObject> GetSByteTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
        IList<SByteTimeseriesValueObject> GetSByteTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
        IList<SByteTimeseriesValueObject> GetSByteTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // SecurityDomain queries
        // ---------------------------------------------------------------------
        SecurityDomainObject? GetSecurityDomainById( Guid id );
        IList<SecurityDomainObject> GetSecurityDomainCollection( );
        SecurityDomainObject? GetSecurityDomainByName( string name );
        // ---------------------------------------------------------------------
        // SecurityIdentifier queries
        // ---------------------------------------------------------------------
        SecurityIdentifierObject? GetSecurityIdentifierById( Guid id );
        IList<SecurityIdentifierObject> GetSecurityIdentifierCollection( );
        IList<SecurityIdentifierObject> GetSecurityIdentifierCollectionByDomain( Guid domain );
        SecurityIdentifierObject? GetSecurityIdentifierByDomainAndIdentity( Guid domain, string identity );
        // ---------------------------------------------------------------------
        // SecurityLogin queries
        // ---------------------------------------------------------------------
        SecurityLoginObject? GetSecurityLoginById( Guid id );
        IList<SecurityLoginObject> GetSecurityLoginCollection( );
        IList<SecurityLoginObject> GetSecurityLoginCollectionByDomain( Guid domain );
        SecurityLoginObject? GetSecurityLoginByDomainAndIdentity( Guid domain, string identity );
        // ---------------------------------------------------------------------
        // SecurityRole queries
        // ---------------------------------------------------------------------
        SecurityRoleObject? GetSecurityRoleById( Guid id );
        IList<SecurityRoleObject> GetSecurityRoleCollection( );
        IList<SecurityRoleObject> GetSecurityRoleCollectionByDomain( Guid domain );
        SecurityRoleObject? GetSecurityRoleByDomainAndIdentity( Guid domain, string identity );
        SecurityRoleObject? GetSecurityRoleByName( string name );
        // ---------------------------------------------------------------------
        // SecurityIdentifierRoleLink queries
        // ---------------------------------------------------------------------
        SecurityIdentifierRoleLinkObject? GetSecurityIdentifierRoleLinkById( Guid id );
        IList<SecurityIdentifierRoleLinkObject> GetSecurityIdentifierRoleLinkCollection( );
        IList<SecurityIdentifierRoleLinkObject> GetSecurityIdentifierRoleLinkCollectionByMember( Guid member );
        IList<SecurityIdentifierRoleLinkObject> GetSecurityIdentifierRoleLinkCollectionByMemberAndStart( Guid member, DateTime start );
        IList<SecurityIdentifierRoleLinkObject> GetSecurityIdentifierRoleLinkCollectionByMemberAtStart( Guid member, DateTime start );
        IList<SecurityIdentifierRoleLinkObject> GetSecurityIdentifierRoleLinkCollectionByMemberFromStart( Guid member, DateTime start );
        IList<SecurityIdentifierRoleLinkObject> GetSecurityIdentifierRoleLinkCollectionByMemberUntilStart( Guid member, DateTime start );
        IList<SecurityIdentifierRoleLinkObject> GetSecurityIdentifierRoleLinkCollectionByMemberOverStart( Guid member, DateTime fromStart, DateTime untilStart );
        IList<SecurityIdentifierRoleLinkObject> GetSecurityIdentifierRoleLinkCollectionByRole( Guid role );
        IList<SecurityIdentifierRoleLinkObject> GetSecurityIdentifierRoleLinkCollectionByRoleAndStart( Guid role, DateTime start );
        IList<SecurityIdentifierRoleLinkObject> GetSecurityIdentifierRoleLinkCollectionByRoleAtStart( Guid role, DateTime start );
        IList<SecurityIdentifierRoleLinkObject> GetSecurityIdentifierRoleLinkCollectionByRoleFromStart( Guid role, DateTime start );
        IList<SecurityIdentifierRoleLinkObject> GetSecurityIdentifierRoleLinkCollectionByRoleUntilStart( Guid role, DateTime start );
        IList<SecurityIdentifierRoleLinkObject> GetSecurityIdentifierRoleLinkCollectionByRoleOverStart( Guid role, DateTime fromStart, DateTime untilStart );
        IList<SecurityIdentifierRoleLinkObject> GetSecurityIdentifierRoleLinkCollectionByStart( DateTime start );
        IList<SecurityIdentifierRoleLinkObject> GetSecurityIdentifierRoleLinkCollectionAtStart( DateTime start );
        IList<SecurityIdentifierRoleLinkObject> GetSecurityIdentifierRoleLinkCollectionFromStart( DateTime start );
        IList<SecurityIdentifierRoleLinkObject> GetSecurityIdentifierRoleLinkCollectionUntilStart( DateTime start );
        IList<SecurityIdentifierRoleLinkObject> GetSecurityIdentifierRoleLinkCollectionOverStart( DateTime fromStart, DateTime untilStart );
        // ---------------------------------------------------------------------
        // SecurityLoginSession queries
        // ---------------------------------------------------------------------
        SecurityLoginSessionObject? GetSecurityLoginSessionById( Guid id );
        IList<SecurityLoginSessionObject> GetSecurityLoginSessionCollection( );
        IList<SecurityLoginSessionObject> GetSecurityLoginSessionCollectionByLogin( Guid login );
        IList<SecurityLoginSessionObject> GetSecurityLoginSessionCollectionByLoginAndFromTime( Guid login, DateTime fromTime );
        IList<SecurityLoginSessionObject> GetSecurityLoginSessionCollectionByLoginAtFromTime( Guid login, DateTime fromTime );
        IList<SecurityLoginSessionObject> GetSecurityLoginSessionCollectionByLoginFromFromTime( Guid login, DateTime fromTime );
        IList<SecurityLoginSessionObject> GetSecurityLoginSessionCollectionByLoginUntilFromTime( Guid login, DateTime fromTime );
        IList<SecurityLoginSessionObject> GetSecurityLoginSessionCollectionByLoginOverFromTime( Guid login, DateTime fromFromTime, DateTime untilFromTime );
        IList<SecurityLoginSessionObject> GetSecurityLoginSessionCollectionByFromTime( DateTime fromTime );
        IList<SecurityLoginSessionObject> GetSecurityLoginSessionCollectionAtFromTime( DateTime fromTime );
        IList<SecurityLoginSessionObject> GetSecurityLoginSessionCollectionFromFromTime( DateTime fromTime );
        IList<SecurityLoginSessionObject> GetSecurityLoginSessionCollectionUntilFromTime( DateTime fromTime );
        IList<SecurityLoginSessionObject> GetSecurityLoginSessionCollectionOverFromTime( DateTime fromFromTime, DateTime untilFromTime );
        // ---------------------------------------------------------------------
        // SecurityPermission queries
        // ---------------------------------------------------------------------
        SecurityPermissionObject? GetSecurityPermissionById( Guid id );
        IList<SecurityPermissionObject> GetSecurityPermissionCollection( );
        IList<SecurityPermissionObject> GetSecurityPermissionCollectionByIdentifier( Guid identifier );
        IList<SecurityPermissionObject> GetSecurityPermissionCollectionByIdentifierAndTypeCode( Guid identifier, int typeCode );
        IList<SecurityPermissionObject> GetSecurityPermissionCollectionByIdentifierFromTypeCode( Guid identifier, int typeCode );
        IList<SecurityPermissionObject> GetSecurityPermissionCollectionByIdentifierUntilTypeCode( Guid identifier, int typeCode );
        IList<SecurityPermissionObject> GetSecurityPermissionCollectionByIdentifierOverTypeCode( Guid identifier, int fromTypeCode, int untilTypeCode );
        SecurityPermissionObject? GetSecurityPermissionByIdentifierTypeCodeAndTimestamp( Guid identifier, int typeCode, DateTime timestamp );
        SecurityPermissionObject? GetSecurityPermissionByIdentifierTypeCodeAtTimestamp( Guid identifier, int typeCode, DateTime timestamp );
        IList<SecurityPermissionObject> GetSecurityPermissionByIdentifierTypeCodeFromTimestamp( Guid identifier, int typeCode, DateTime timestamp );
        IList<SecurityPermissionObject> GetSecurityPermissionByIdentifierTypeCodeUntilTimestamp( Guid identifier, int typeCode, DateTime timestamp );
        IList<SecurityPermissionObject> GetSecurityPermissionByIdentifierTypeCodeOverTimestamp( Guid identifier, int typeCode, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<SecurityPermissionObject> GetSecurityPermissionCollectionByTimestamp( DateTime timestamp );
        IList<SecurityPermissionObject> GetSecurityPermissionCollectionAtTimestamp( DateTime timestamp );
        IList<SecurityPermissionObject> GetSecurityPermissionCollectionFromTimestamp( DateTime timestamp );
        IList<SecurityPermissionObject> GetSecurityPermissionCollectionUntilTimestamp( DateTime timestamp );
        IList<SecurityPermissionObject> GetSecurityPermissionCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // SingleTimeseriesValue queries
        // ---------------------------------------------------------------------
        SingleTimeseriesValueObject? GetSingleTimeseriesValueById( Guid id );
        IList<SingleTimeseriesValueObject> GetSingleTimeseriesValueCollection( );
        IList<SingleTimeseriesValueObject> GetSingleTimeseriesValueCollectionByTimeseries( Guid timeseries );
        SingleTimeseriesValueObject? GetSingleTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
        SingleTimeseriesValueObject? GetSingleTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
        IList<SingleTimeseriesValueObject> GetSingleTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
        IList<SingleTimeseriesValueObject> GetSingleTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
        IList<SingleTimeseriesValueObject> GetSingleTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<SingleTimeseriesValueObject> GetSingleTimeseriesValueCollectionByTimestamp( DateTime timestamp );
        IList<SingleTimeseriesValueObject> GetSingleTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
        IList<SingleTimeseriesValueObject> GetSingleTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
        IList<SingleTimeseriesValueObject> GetSingleTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
        IList<SingleTimeseriesValueObject> GetSingleTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // StringTimeseriesValue queries
        // ---------------------------------------------------------------------
        StringTimeseriesValueObject? GetStringTimeseriesValueById( Guid id );
        IList<StringTimeseriesValueObject> GetStringTimeseriesValueCollection( );
        IList<StringTimeseriesValueObject> GetStringTimeseriesValueCollectionByTimeseries( Guid timeseries );
        StringTimeseriesValueObject? GetStringTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
        StringTimeseriesValueObject? GetStringTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
        IList<StringTimeseriesValueObject> GetStringTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
        IList<StringTimeseriesValueObject> GetStringTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
        IList<StringTimeseriesValueObject> GetStringTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<StringTimeseriesValueObject> GetStringTimeseriesValueCollectionByTimestamp( DateTime timestamp );
        IList<StringTimeseriesValueObject> GetStringTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
        IList<StringTimeseriesValueObject> GetStringTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
        IList<StringTimeseriesValueObject> GetStringTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
        IList<StringTimeseriesValueObject> GetStringTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // TimeseriesCatalogElement queries
        // ---------------------------------------------------------------------
        TimeseriesCatalogElementObject? GetTimeseriesCatalogElementById( Guid id );
        IList<TimeseriesCatalogElementObject> GetTimeseriesCatalogElementCollection( );
        IList<TimeseriesCatalogElementObject> GetTimeseriesCatalogElementCollectionByCatalog( Guid? catalog );
        IList<TimeseriesCatalogElementObject> GetTimeseriesCatalogElementCollectionByCatalogIsNull(  );
        TimeseriesCatalogElementObject? GetTimeseriesCatalogElementByCatalogAndName( Guid? catalog, string name );
        IList<TimeseriesCatalogElementObject> GetTimeseriesCatalogElementCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // Timeseries queries
        // ---------------------------------------------------------------------
        TimeseriesObject? GetTimeseriesById( Guid id );
        IList<TimeseriesObject> GetTimeseriesCollection( );
        IList<TimeseriesObject> GetTimeseriesCollectionByCatalog( Guid? catalog );
        IList<TimeseriesObject> GetTimeseriesCollectionByCatalogIsNull(  );
        TimeseriesObject? GetTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<TimeseriesObject> GetTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // BinaryTimeseries queries
        // ---------------------------------------------------------------------
        BinaryTimeseriesObject? GetBinaryTimeseriesById( Guid id );
        IList<BinaryTimeseriesObject> GetBinaryTimeseriesCollection( );
        IList<BinaryTimeseriesObject> GetBinaryTimeseriesCollectionByCatalog( Guid? catalog );
        IList<BinaryTimeseriesObject> GetBinaryTimeseriesCollectionByCatalogIsNull(  );
        BinaryTimeseriesObject? GetBinaryTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<BinaryTimeseriesObject> GetBinaryTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // BooleanTimeseries queries
        // ---------------------------------------------------------------------
        BooleanTimeseriesObject? GetBooleanTimeseriesById( Guid id );
        IList<BooleanTimeseriesObject> GetBooleanTimeseriesCollection( );
        IList<BooleanTimeseriesObject> GetBooleanTimeseriesCollectionByCatalog( Guid? catalog );
        IList<BooleanTimeseriesObject> GetBooleanTimeseriesCollectionByCatalogIsNull(  );
        BooleanTimeseriesObject? GetBooleanTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<BooleanTimeseriesObject> GetBooleanTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // AisAidToNavigationOffPositionTimeseries queries
        // ---------------------------------------------------------------------
        AisAidToNavigationOffPositionTimeseriesObject? GetAisAidToNavigationOffPositionTimeseriesById( Guid id );
        IList<AisAidToNavigationOffPositionTimeseriesObject> GetAisAidToNavigationOffPositionTimeseriesCollection( );
        IList<AisAidToNavigationOffPositionTimeseriesObject> GetAisAidToNavigationOffPositionTimeseriesCollectionByCatalog( Guid? catalog );
        IList<AisAidToNavigationOffPositionTimeseriesObject> GetAisAidToNavigationOffPositionTimeseriesCollectionByCatalogIsNull(  );
        AisAidToNavigationOffPositionTimeseriesObject? GetAisAidToNavigationOffPositionTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<AisAidToNavigationOffPositionTimeseriesObject> GetAisAidToNavigationOffPositionTimeseriesCollectionByCatalogIsNullAndName( string name );
        IList<AisAidToNavigationOffPositionTimeseriesObject> GetAisAidToNavigationOffPositionTimeseriesCollectionByAidToNavigation( Guid? aidToNavigation );
        IList<AisAidToNavigationOffPositionTimeseriesObject> GetAisAidToNavigationOffPositionTimeseriesCollectionByAidToNavigationIsNull(  );
        // ---------------------------------------------------------------------
        // DeviceEnabledTimeseries queries
        // ---------------------------------------------------------------------
        DeviceEnabledTimeseriesObject? GetDeviceEnabledTimeseriesById( Guid id );
        IList<DeviceEnabledTimeseriesObject> GetDeviceEnabledTimeseriesCollection( );
        IList<DeviceEnabledTimeseriesObject> GetDeviceEnabledTimeseriesCollectionByCatalog( Guid? catalog );
        IList<DeviceEnabledTimeseriesObject> GetDeviceEnabledTimeseriesCollectionByCatalogIsNull(  );
        DeviceEnabledTimeseriesObject? GetDeviceEnabledTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<DeviceEnabledTimeseriesObject> GetDeviceEnabledTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // RadarAutomaticSensitivityTimeControlTimeseries queries
        // ---------------------------------------------------------------------
        RadarAutomaticSensitivityTimeControlTimeseriesObject? GetRadarAutomaticSensitivityTimeControlTimeseriesById( Guid id );
        IList<RadarAutomaticSensitivityTimeControlTimeseriesObject> GetRadarAutomaticSensitivityTimeControlTimeseriesCollection( );
        IList<RadarAutomaticSensitivityTimeControlTimeseriesObject> GetRadarAutomaticSensitivityTimeControlTimeseriesCollectionByCatalog( Guid? catalog );
        IList<RadarAutomaticSensitivityTimeControlTimeseriesObject> GetRadarAutomaticSensitivityTimeControlTimeseriesCollectionByCatalogIsNull(  );
        RadarAutomaticSensitivityTimeControlTimeseriesObject? GetRadarAutomaticSensitivityTimeControlTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<RadarAutomaticSensitivityTimeControlTimeseriesObject> GetRadarAutomaticSensitivityTimeControlTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // RadarBlankSector1Timeseries queries
        // ---------------------------------------------------------------------
        RadarBlankSector1TimeseriesObject? GetRadarBlankSector1TimeseriesById( Guid id );
        IList<RadarBlankSector1TimeseriesObject> GetRadarBlankSector1TimeseriesCollection( );
        IList<RadarBlankSector1TimeseriesObject> GetRadarBlankSector1TimeseriesCollectionByCatalog( Guid? catalog );
        IList<RadarBlankSector1TimeseriesObject> GetRadarBlankSector1TimeseriesCollectionByCatalogIsNull(  );
        RadarBlankSector1TimeseriesObject? GetRadarBlankSector1TimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<RadarBlankSector1TimeseriesObject> GetRadarBlankSector1TimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // RadarBlankSector2Timeseries queries
        // ---------------------------------------------------------------------
        RadarBlankSector2TimeseriesObject? GetRadarBlankSector2TimeseriesById( Guid id );
        IList<RadarBlankSector2TimeseriesObject> GetRadarBlankSector2TimeseriesCollection( );
        IList<RadarBlankSector2TimeseriesObject> GetRadarBlankSector2TimeseriesCollectionByCatalog( Guid? catalog );
        IList<RadarBlankSector2TimeseriesObject> GetRadarBlankSector2TimeseriesCollectionByCatalogIsNull(  );
        RadarBlankSector2TimeseriesObject? GetRadarBlankSector2TimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<RadarBlankSector2TimeseriesObject> GetRadarBlankSector2TimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // RadarEnableAutomaticFrequencyControlTimeseries queries
        // ---------------------------------------------------------------------
        RadarEnableAutomaticFrequencyControlTimeseriesObject? GetRadarEnableAutomaticFrequencyControlTimeseriesById( Guid id );
        IList<RadarEnableAutomaticFrequencyControlTimeseriesObject> GetRadarEnableAutomaticFrequencyControlTimeseriesCollection( );
        IList<RadarEnableAutomaticFrequencyControlTimeseriesObject> GetRadarEnableAutomaticFrequencyControlTimeseriesCollectionByCatalog( Guid? catalog );
        IList<RadarEnableAutomaticFrequencyControlTimeseriesObject> GetRadarEnableAutomaticFrequencyControlTimeseriesCollectionByCatalogIsNull(  );
        RadarEnableAutomaticFrequencyControlTimeseriesObject? GetRadarEnableAutomaticFrequencyControlTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<RadarEnableAutomaticFrequencyControlTimeseriesObject> GetRadarEnableAutomaticFrequencyControlTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // RadarEnableFastTimeConstantTimeseries queries
        // ---------------------------------------------------------------------
        RadarEnableFastTimeConstantTimeseriesObject? GetRadarEnableFastTimeConstantTimeseriesById( Guid id );
        IList<RadarEnableFastTimeConstantTimeseriesObject> GetRadarEnableFastTimeConstantTimeseriesCollection( );
        IList<RadarEnableFastTimeConstantTimeseriesObject> GetRadarEnableFastTimeConstantTimeseriesCollectionByCatalog( Guid? catalog );
        IList<RadarEnableFastTimeConstantTimeseriesObject> GetRadarEnableFastTimeConstantTimeseriesCollectionByCatalogIsNull(  );
        RadarEnableFastTimeConstantTimeseriesObject? GetRadarEnableFastTimeConstantTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<RadarEnableFastTimeConstantTimeseriesObject> GetRadarEnableFastTimeConstantTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // RadarEnableSensitivityTimeControlTimeseries queries
        // ---------------------------------------------------------------------
        RadarEnableSensitivityTimeControlTimeseriesObject? GetRadarEnableSensitivityTimeControlTimeseriesById( Guid id );
        IList<RadarEnableSensitivityTimeControlTimeseriesObject> GetRadarEnableSensitivityTimeControlTimeseriesCollection( );
        IList<RadarEnableSensitivityTimeControlTimeseriesObject> GetRadarEnableSensitivityTimeControlTimeseriesCollectionByCatalog( Guid? catalog );
        IList<RadarEnableSensitivityTimeControlTimeseriesObject> GetRadarEnableSensitivityTimeControlTimeseriesCollectionByCatalogIsNull(  );
        RadarEnableSensitivityTimeControlTimeseriesObject? GetRadarEnableSensitivityTimeControlTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<RadarEnableSensitivityTimeControlTimeseriesObject> GetRadarEnableSensitivityTimeControlTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // RadarPowerOnTimeseries queries
        // ---------------------------------------------------------------------
        RadarPowerOnTimeseriesObject? GetRadarPowerOnTimeseriesById( Guid id );
        IList<RadarPowerOnTimeseriesObject> GetRadarPowerOnTimeseriesCollection( );
        IList<RadarPowerOnTimeseriesObject> GetRadarPowerOnTimeseriesCollectionByCatalog( Guid? catalog );
        IList<RadarPowerOnTimeseriesObject> GetRadarPowerOnTimeseriesCollectionByCatalogIsNull(  );
        RadarPowerOnTimeseriesObject? GetRadarPowerOnTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<RadarPowerOnTimeseriesObject> GetRadarPowerOnTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // RadarSaveSettingsTimeseries queries
        // ---------------------------------------------------------------------
        RadarSaveSettingsTimeseriesObject? GetRadarSaveSettingsTimeseriesById( Guid id );
        IList<RadarSaveSettingsTimeseriesObject> GetRadarSaveSettingsTimeseriesCollection( );
        IList<RadarSaveSettingsTimeseriesObject> GetRadarSaveSettingsTimeseriesCollectionByCatalog( Guid? catalog );
        IList<RadarSaveSettingsTimeseriesObject> GetRadarSaveSettingsTimeseriesCollectionByCatalogIsNull(  );
        RadarSaveSettingsTimeseriesObject? GetRadarSaveSettingsTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<RadarSaveSettingsTimeseriesObject> GetRadarSaveSettingsTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // RadarTrackingTimeseries queries
        // ---------------------------------------------------------------------
        RadarTrackingTimeseriesObject? GetRadarTrackingTimeseriesById( Guid id );
        IList<RadarTrackingTimeseriesObject> GetRadarTrackingTimeseriesCollection( );
        IList<RadarTrackingTimeseriesObject> GetRadarTrackingTimeseriesCollectionByCatalog( Guid? catalog );
        IList<RadarTrackingTimeseriesObject> GetRadarTrackingTimeseriesCollectionByCatalogIsNull(  );
        RadarTrackingTimeseriesObject? GetRadarTrackingTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<RadarTrackingTimeseriesObject> GetRadarTrackingTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // MediaProxySessionEnabledTimeseries queries
        // ---------------------------------------------------------------------
        MediaProxySessionEnabledTimeseriesObject? GetMediaProxySessionEnabledTimeseriesById( Guid id );
        IList<MediaProxySessionEnabledTimeseriesObject> GetMediaProxySessionEnabledTimeseriesCollection( );
        IList<MediaProxySessionEnabledTimeseriesObject> GetMediaProxySessionEnabledTimeseriesCollectionByCatalog( Guid? catalog );
        IList<MediaProxySessionEnabledTimeseriesObject> GetMediaProxySessionEnabledTimeseriesCollectionByCatalogIsNull(  );
        MediaProxySessionEnabledTimeseriesObject? GetMediaProxySessionEnabledTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<MediaProxySessionEnabledTimeseriesObject> GetMediaProxySessionEnabledTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // MediaServiceEnabledTimeseries queries
        // ---------------------------------------------------------------------
        MediaServiceEnabledTimeseriesObject? GetMediaServiceEnabledTimeseriesById( Guid id );
        IList<MediaServiceEnabledTimeseriesObject> GetMediaServiceEnabledTimeseriesCollection( );
        IList<MediaServiceEnabledTimeseriesObject> GetMediaServiceEnabledTimeseriesCollectionByCatalog( Guid? catalog );
        IList<MediaServiceEnabledTimeseriesObject> GetMediaServiceEnabledTimeseriesCollectionByCatalogIsNull(  );
        MediaServiceEnabledTimeseriesObject? GetMediaServiceEnabledTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<MediaServiceEnabledTimeseriesObject> GetMediaServiceEnabledTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // ByteTimeseries queries
        // ---------------------------------------------------------------------
        ByteTimeseriesObject? GetByteTimeseriesById( Guid id );
        IList<ByteTimeseriesObject> GetByteTimeseriesCollection( );
        IList<ByteTimeseriesObject> GetByteTimeseriesCollectionByCatalog( Guid? catalog );
        IList<ByteTimeseriesObject> GetByteTimeseriesCollectionByCatalogIsNull(  );
        ByteTimeseriesObject? GetByteTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<ByteTimeseriesObject> GetByteTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // DateTimeTimeseries queries
        // ---------------------------------------------------------------------
        DateTimeTimeseriesObject? GetDateTimeTimeseriesById( Guid id );
        IList<DateTimeTimeseriesObject> GetDateTimeTimeseriesCollection( );
        IList<DateTimeTimeseriesObject> GetDateTimeTimeseriesCollectionByCatalog( Guid? catalog );
        IList<DateTimeTimeseriesObject> GetDateTimeTimeseriesCollectionByCatalogIsNull(  );
        DateTimeTimeseriesObject? GetDateTimeTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<DateTimeTimeseriesObject> GetDateTimeTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // DoubleTimeseries queries
        // ---------------------------------------------------------------------
        DoubleTimeseriesObject? GetDoubleTimeseriesById( Guid id );
        IList<DoubleTimeseriesObject> GetDoubleTimeseriesCollection( );
        IList<DoubleTimeseriesObject> GetDoubleTimeseriesCollectionByCatalog( Guid? catalog );
        IList<DoubleTimeseriesObject> GetDoubleTimeseriesCollectionByCatalogIsNull(  );
        DoubleTimeseriesObject? GetDoubleTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<DoubleTimeseriesObject> GetDoubleTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // GNSSAltitudeTimeseries queries
        // ---------------------------------------------------------------------
        GNSSAltitudeTimeseriesObject? GetGNSSAltitudeTimeseriesById( Guid id );
        IList<GNSSAltitudeTimeseriesObject> GetGNSSAltitudeTimeseriesCollection( );
        IList<GNSSAltitudeTimeseriesObject> GetGNSSAltitudeTimeseriesCollectionByCatalog( Guid? catalog );
        IList<GNSSAltitudeTimeseriesObject> GetGNSSAltitudeTimeseriesCollectionByCatalogIsNull(  );
        GNSSAltitudeTimeseriesObject? GetGNSSAltitudeTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<GNSSAltitudeTimeseriesObject> GetGNSSAltitudeTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // GNSSLatitudeTimeseries queries
        // ---------------------------------------------------------------------
        GNSSLatitudeTimeseriesObject? GetGNSSLatitudeTimeseriesById( Guid id );
        IList<GNSSLatitudeTimeseriesObject> GetGNSSLatitudeTimeseriesCollection( );
        IList<GNSSLatitudeTimeseriesObject> GetGNSSLatitudeTimeseriesCollectionByCatalog( Guid? catalog );
        IList<GNSSLatitudeTimeseriesObject> GetGNSSLatitudeTimeseriesCollectionByCatalogIsNull(  );
        GNSSLatitudeTimeseriesObject? GetGNSSLatitudeTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<GNSSLatitudeTimeseriesObject> GetGNSSLatitudeTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // GNSSLongitudeTimeseries queries
        // ---------------------------------------------------------------------
        GNSSLongitudeTimeseriesObject? GetGNSSLongitudeTimeseriesById( Guid id );
        IList<GNSSLongitudeTimeseriesObject> GetGNSSLongitudeTimeseriesCollection( );
        IList<GNSSLongitudeTimeseriesObject> GetGNSSLongitudeTimeseriesCollectionByCatalog( Guid? catalog );
        IList<GNSSLongitudeTimeseriesObject> GetGNSSLongitudeTimeseriesCollectionByCatalogIsNull(  );
        GNSSLongitudeTimeseriesObject? GetGNSSLongitudeTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<GNSSLongitudeTimeseriesObject> GetGNSSLongitudeTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // GyroCourseTimeseries queries
        // ---------------------------------------------------------------------
        GyroCourseTimeseriesObject? GetGyroCourseTimeseriesById( Guid id );
        IList<GyroCourseTimeseriesObject> GetGyroCourseTimeseriesCollection( );
        IList<GyroCourseTimeseriesObject> GetGyroCourseTimeseriesCollectionByCatalog( Guid? catalog );
        IList<GyroCourseTimeseriesObject> GetGyroCourseTimeseriesCollectionByCatalogIsNull(  );
        GyroCourseTimeseriesObject? GetGyroCourseTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<GyroCourseTimeseriesObject> GetGyroCourseTimeseriesCollectionByCatalogIsNullAndName( string name );
        GyroCourseTimeseriesObject? GetGyroCourseTimeseriesByGyroDevice( Guid? gyroDevice );
        IList<GyroCourseTimeseriesObject> GetGyroCourseTimeseriesCollectionByGyroDeviceIsNull(  );
        // ---------------------------------------------------------------------
        // GyroHeadingMagneticNorthTimeseries queries
        // ---------------------------------------------------------------------
        GyroHeadingMagneticNorthTimeseriesObject? GetGyroHeadingMagneticNorthTimeseriesById( Guid id );
        IList<GyroHeadingMagneticNorthTimeseriesObject> GetGyroHeadingMagneticNorthTimeseriesCollection( );
        IList<GyroHeadingMagneticNorthTimeseriesObject> GetGyroHeadingMagneticNorthTimeseriesCollectionByCatalog( Guid? catalog );
        IList<GyroHeadingMagneticNorthTimeseriesObject> GetGyroHeadingMagneticNorthTimeseriesCollectionByCatalogIsNull(  );
        GyroHeadingMagneticNorthTimeseriesObject? GetGyroHeadingMagneticNorthTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<GyroHeadingMagneticNorthTimeseriesObject> GetGyroHeadingMagneticNorthTimeseriesCollectionByCatalogIsNullAndName( string name );
        GyroHeadingMagneticNorthTimeseriesObject? GetGyroHeadingMagneticNorthTimeseriesByGyroDevice( Guid? gyroDevice );
        IList<GyroHeadingMagneticNorthTimeseriesObject> GetGyroHeadingMagneticNorthTimeseriesCollectionByGyroDeviceIsNull(  );
        // ---------------------------------------------------------------------
        // GyroHeadingTrueNorthTimeseries queries
        // ---------------------------------------------------------------------
        GyroHeadingTrueNorthTimeseriesObject? GetGyroHeadingTrueNorthTimeseriesById( Guid id );
        IList<GyroHeadingTrueNorthTimeseriesObject> GetGyroHeadingTrueNorthTimeseriesCollection( );
        IList<GyroHeadingTrueNorthTimeseriesObject> GetGyroHeadingTrueNorthTimeseriesCollectionByCatalog( Guid? catalog );
        IList<GyroHeadingTrueNorthTimeseriesObject> GetGyroHeadingTrueNorthTimeseriesCollectionByCatalogIsNull(  );
        GyroHeadingTrueNorthTimeseriesObject? GetGyroHeadingTrueNorthTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<GyroHeadingTrueNorthTimeseriesObject> GetGyroHeadingTrueNorthTimeseriesCollectionByCatalogIsNullAndName( string name );
        GyroHeadingTrueNorthTimeseriesObject? GetGyroHeadingTrueNorthTimeseriesByGyroDevice( Guid? gyroDevice );
        IList<GyroHeadingTrueNorthTimeseriesObject> GetGyroHeadingTrueNorthTimeseriesCollectionByGyroDeviceIsNull(  );
        // ---------------------------------------------------------------------
        // GyroPitchTimeseries queries
        // ---------------------------------------------------------------------
        GyroPitchTimeseriesObject? GetGyroPitchTimeseriesById( Guid id );
        IList<GyroPitchTimeseriesObject> GetGyroPitchTimeseriesCollection( );
        IList<GyroPitchTimeseriesObject> GetGyroPitchTimeseriesCollectionByCatalog( Guid? catalog );
        IList<GyroPitchTimeseriesObject> GetGyroPitchTimeseriesCollectionByCatalogIsNull(  );
        GyroPitchTimeseriesObject? GetGyroPitchTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<GyroPitchTimeseriesObject> GetGyroPitchTimeseriesCollectionByCatalogIsNullAndName( string name );
        GyroPitchTimeseriesObject? GetGyroPitchTimeseriesByGyroDevice( Guid? gyroDevice );
        IList<GyroPitchTimeseriesObject> GetGyroPitchTimeseriesCollectionByGyroDeviceIsNull(  );
        // ---------------------------------------------------------------------
        // GyroRateOfTurnTimeseries queries
        // ---------------------------------------------------------------------
        GyroRateOfTurnTimeseriesObject? GetGyroRateOfTurnTimeseriesById( Guid id );
        IList<GyroRateOfTurnTimeseriesObject> GetGyroRateOfTurnTimeseriesCollection( );
        IList<GyroRateOfTurnTimeseriesObject> GetGyroRateOfTurnTimeseriesCollectionByCatalog( Guid? catalog );
        IList<GyroRateOfTurnTimeseriesObject> GetGyroRateOfTurnTimeseriesCollectionByCatalogIsNull(  );
        GyroRateOfTurnTimeseriesObject? GetGyroRateOfTurnTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<GyroRateOfTurnTimeseriesObject> GetGyroRateOfTurnTimeseriesCollectionByCatalogIsNullAndName( string name );
        GyroRateOfTurnTimeseriesObject? GetGyroRateOfTurnTimeseriesByGyroDevice( Guid? gyroDevice );
        IList<GyroRateOfTurnTimeseriesObject> GetGyroRateOfTurnTimeseriesCollectionByGyroDeviceIsNull(  );
        // ---------------------------------------------------------------------
        // GyroRollTimeseries queries
        // ---------------------------------------------------------------------
        GyroRollTimeseriesObject? GetGyroRollTimeseriesById( Guid id );
        IList<GyroRollTimeseriesObject> GetGyroRollTimeseriesCollection( );
        IList<GyroRollTimeseriesObject> GetGyroRollTimeseriesCollectionByCatalog( Guid? catalog );
        IList<GyroRollTimeseriesObject> GetGyroRollTimeseriesCollectionByCatalogIsNull(  );
        GyroRollTimeseriesObject? GetGyroRollTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<GyroRollTimeseriesObject> GetGyroRollTimeseriesCollectionByCatalogIsNullAndName( string name );
        GyroRollTimeseriesObject? GetGyroRollTimeseriesByGyroDevice( Guid? gyroDevice );
        IList<GyroRollTimeseriesObject> GetGyroRollTimeseriesCollectionByGyroDeviceIsNull(  );
        // ---------------------------------------------------------------------
        // GyroSpeedTimeseries queries
        // ---------------------------------------------------------------------
        GyroSpeedTimeseriesObject? GetGyroSpeedTimeseriesById( Guid id );
        IList<GyroSpeedTimeseriesObject> GetGyroSpeedTimeseriesCollection( );
        IList<GyroSpeedTimeseriesObject> GetGyroSpeedTimeseriesCollectionByCatalog( Guid? catalog );
        IList<GyroSpeedTimeseriesObject> GetGyroSpeedTimeseriesCollectionByCatalogIsNull(  );
        GyroSpeedTimeseriesObject? GetGyroSpeedTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<GyroSpeedTimeseriesObject> GetGyroSpeedTimeseriesCollectionByCatalogIsNullAndName( string name );
        GyroSpeedTimeseriesObject? GetGyroSpeedTimeseriesByGyroDevice( Guid? gyroDevice );
        IList<GyroSpeedTimeseriesObject> GetGyroSpeedTimeseriesCollectionByGyroDeviceIsNull(  );
        // ---------------------------------------------------------------------
        // RadarLatitudeTimeseries queries
        // ---------------------------------------------------------------------
        RadarLatitudeTimeseriesObject? GetRadarLatitudeTimeseriesById( Guid id );
        IList<RadarLatitudeTimeseriesObject> GetRadarLatitudeTimeseriesCollection( );
        IList<RadarLatitudeTimeseriesObject> GetRadarLatitudeTimeseriesCollectionByCatalog( Guid? catalog );
        IList<RadarLatitudeTimeseriesObject> GetRadarLatitudeTimeseriesCollectionByCatalogIsNull(  );
        RadarLatitudeTimeseriesObject? GetRadarLatitudeTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<RadarLatitudeTimeseriesObject> GetRadarLatitudeTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // RadarLongitudeTimeseries queries
        // ---------------------------------------------------------------------
        RadarLongitudeTimeseriesObject? GetRadarLongitudeTimeseriesById( Guid id );
        IList<RadarLongitudeTimeseriesObject> GetRadarLongitudeTimeseriesCollection( );
        IList<RadarLongitudeTimeseriesObject> GetRadarLongitudeTimeseriesCollectionByCatalog( Guid? catalog );
        IList<RadarLongitudeTimeseriesObject> GetRadarLongitudeTimeseriesCollectionByCatalogIsNull(  );
        RadarLongitudeTimeseriesObject? GetRadarLongitudeTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<RadarLongitudeTimeseriesObject> GetRadarLongitudeTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // RadomeDewPointTimeseries queries
        // ---------------------------------------------------------------------
        RadomeDewPointTimeseriesObject? GetRadomeDewPointTimeseriesById( Guid id );
        IList<RadomeDewPointTimeseriesObject> GetRadomeDewPointTimeseriesCollection( );
        IList<RadomeDewPointTimeseriesObject> GetRadomeDewPointTimeseriesCollectionByCatalog( Guid? catalog );
        IList<RadomeDewPointTimeseriesObject> GetRadomeDewPointTimeseriesCollectionByCatalogIsNull(  );
        RadomeDewPointTimeseriesObject? GetRadomeDewPointTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<RadomeDewPointTimeseriesObject> GetRadomeDewPointTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // RadomePressureTimeseries queries
        // ---------------------------------------------------------------------
        RadomePressureTimeseriesObject? GetRadomePressureTimeseriesById( Guid id );
        IList<RadomePressureTimeseriesObject> GetRadomePressureTimeseriesCollection( );
        IList<RadomePressureTimeseriesObject> GetRadomePressureTimeseriesCollectionByCatalog( Guid? catalog );
        IList<RadomePressureTimeseriesObject> GetRadomePressureTimeseriesCollectionByCatalogIsNull(  );
        RadomePressureTimeseriesObject? GetRadomePressureTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<RadomePressureTimeseriesObject> GetRadomePressureTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // RadomeTemperatureTimeseries queries
        // ---------------------------------------------------------------------
        RadomeTemperatureTimeseriesObject? GetRadomeTemperatureTimeseriesById( Guid id );
        IList<RadomeTemperatureTimeseriesObject> GetRadomeTemperatureTimeseriesCollection( );
        IList<RadomeTemperatureTimeseriesObject> GetRadomeTemperatureTimeseriesCollectionByCatalog( Guid? catalog );
        IList<RadomeTemperatureTimeseriesObject> GetRadomeTemperatureTimeseriesCollectionByCatalogIsNull(  );
        RadomeTemperatureTimeseriesObject? GetRadomeTemperatureTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<RadomeTemperatureTimeseriesObject> GetRadomeTemperatureTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // VesselDraughtTimeseries queries
        // ---------------------------------------------------------------------
        VesselDraughtTimeseriesObject? GetVesselDraughtTimeseriesById( Guid id );
        IList<VesselDraughtTimeseriesObject> GetVesselDraughtTimeseriesCollection( );
        IList<VesselDraughtTimeseriesObject> GetVesselDraughtTimeseriesCollectionByCatalog( Guid? catalog );
        IList<VesselDraughtTimeseriesObject> GetVesselDraughtTimeseriesCollectionByCatalogIsNull(  );
        VesselDraughtTimeseriesObject? GetVesselDraughtTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<VesselDraughtTimeseriesObject> GetVesselDraughtTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // ViewLatitudeTimeseries queries
        // ---------------------------------------------------------------------
        ViewLatitudeTimeseriesObject? GetViewLatitudeTimeseriesById( Guid id );
        IList<ViewLatitudeTimeseriesObject> GetViewLatitudeTimeseriesCollection( );
        IList<ViewLatitudeTimeseriesObject> GetViewLatitudeTimeseriesCollectionByCatalog( Guid? catalog );
        IList<ViewLatitudeTimeseriesObject> GetViewLatitudeTimeseriesCollectionByCatalogIsNull(  );
        ViewLatitudeTimeseriesObject? GetViewLatitudeTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<ViewLatitudeTimeseriesObject> GetViewLatitudeTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // ViewLongitudeTimeseries queries
        // ---------------------------------------------------------------------
        ViewLongitudeTimeseriesObject? GetViewLongitudeTimeseriesById( Guid id );
        IList<ViewLongitudeTimeseriesObject> GetViewLongitudeTimeseriesCollection( );
        IList<ViewLongitudeTimeseriesObject> GetViewLongitudeTimeseriesCollectionByCatalog( Guid? catalog );
        IList<ViewLongitudeTimeseriesObject> GetViewLongitudeTimeseriesCollectionByCatalogIsNull(  );
        ViewLongitudeTimeseriesObject? GetViewLongitudeTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<ViewLongitudeTimeseriesObject> GetViewLongitudeTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // ViewZoomLevelTimeseries queries
        // ---------------------------------------------------------------------
        ViewZoomLevelTimeseriesObject? GetViewZoomLevelTimeseriesById( Guid id );
        IList<ViewZoomLevelTimeseriesObject> GetViewZoomLevelTimeseriesCollection( );
        IList<ViewZoomLevelTimeseriesObject> GetViewZoomLevelTimeseriesCollectionByCatalog( Guid? catalog );
        IList<ViewZoomLevelTimeseriesObject> GetViewZoomLevelTimeseriesCollectionByCatalogIsNull(  );
        ViewZoomLevelTimeseriesObject? GetViewZoomLevelTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<ViewZoomLevelTimeseriesObject> GetViewZoomLevelTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // WeatherStationAbsoluteHumidityTimeseries queries
        // ---------------------------------------------------------------------
        WeatherStationAbsoluteHumidityTimeseriesObject? GetWeatherStationAbsoluteHumidityTimeseriesById( Guid id );
        IList<WeatherStationAbsoluteHumidityTimeseriesObject> GetWeatherStationAbsoluteHumidityTimeseriesCollection( );
        IList<WeatherStationAbsoluteHumidityTimeseriesObject> GetWeatherStationAbsoluteHumidityTimeseriesCollectionByCatalog( Guid? catalog );
        IList<WeatherStationAbsoluteHumidityTimeseriesObject> GetWeatherStationAbsoluteHumidityTimeseriesCollectionByCatalogIsNull(  );
        WeatherStationAbsoluteHumidityTimeseriesObject? GetWeatherStationAbsoluteHumidityTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<WeatherStationAbsoluteHumidityTimeseriesObject> GetWeatherStationAbsoluteHumidityTimeseriesCollectionByCatalogIsNullAndName( string name );
        WeatherStationAbsoluteHumidityTimeseriesObject? GetWeatherStationAbsoluteHumidityTimeseriesByWeatherStation( Guid? weatherStation );
        IList<WeatherStationAbsoluteHumidityTimeseriesObject> GetWeatherStationAbsoluteHumidityTimeseriesCollectionByWeatherStationIsNull(  );
        // ---------------------------------------------------------------------
        // WeatherStationAirTemperatureTimeseries queries
        // ---------------------------------------------------------------------
        WeatherStationAirTemperatureTimeseriesObject? GetWeatherStationAirTemperatureTimeseriesById( Guid id );
        IList<WeatherStationAirTemperatureTimeseriesObject> GetWeatherStationAirTemperatureTimeseriesCollection( );
        IList<WeatherStationAirTemperatureTimeseriesObject> GetWeatherStationAirTemperatureTimeseriesCollectionByCatalog( Guid? catalog );
        IList<WeatherStationAirTemperatureTimeseriesObject> GetWeatherStationAirTemperatureTimeseriesCollectionByCatalogIsNull(  );
        WeatherStationAirTemperatureTimeseriesObject? GetWeatherStationAirTemperatureTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<WeatherStationAirTemperatureTimeseriesObject> GetWeatherStationAirTemperatureTimeseriesCollectionByCatalogIsNullAndName( string name );
        WeatherStationAirTemperatureTimeseriesObject? GetWeatherStationAirTemperatureTimeseriesByWeatherStation( Guid? weatherStation );
        IList<WeatherStationAirTemperatureTimeseriesObject> GetWeatherStationAirTemperatureTimeseriesCollectionByWeatherStationIsNull(  );
        // ---------------------------------------------------------------------
        // WeatherStationBarometricPressureTimeseries queries
        // ---------------------------------------------------------------------
        WeatherStationBarometricPressureTimeseriesObject? GetWeatherStationBarometricPressureTimeseriesById( Guid id );
        IList<WeatherStationBarometricPressureTimeseriesObject> GetWeatherStationBarometricPressureTimeseriesCollection( );
        IList<WeatherStationBarometricPressureTimeseriesObject> GetWeatherStationBarometricPressureTimeseriesCollectionByCatalog( Guid? catalog );
        IList<WeatherStationBarometricPressureTimeseriesObject> GetWeatherStationBarometricPressureTimeseriesCollectionByCatalogIsNull(  );
        WeatherStationBarometricPressureTimeseriesObject? GetWeatherStationBarometricPressureTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<WeatherStationBarometricPressureTimeseriesObject> GetWeatherStationBarometricPressureTimeseriesCollectionByCatalogIsNullAndName( string name );
        WeatherStationBarometricPressureTimeseriesObject? GetWeatherStationBarometricPressureTimeseriesByWeatherStation( Guid? weatherStation );
        IList<WeatherStationBarometricPressureTimeseriesObject> GetWeatherStationBarometricPressureTimeseriesCollectionByWeatherStationIsNull(  );
        // ---------------------------------------------------------------------
        // WeatherStationDewPointTimeseries queries
        // ---------------------------------------------------------------------
        WeatherStationDewPointTimeseriesObject? GetWeatherStationDewPointTimeseriesById( Guid id );
        IList<WeatherStationDewPointTimeseriesObject> GetWeatherStationDewPointTimeseriesCollection( );
        IList<WeatherStationDewPointTimeseriesObject> GetWeatherStationDewPointTimeseriesCollectionByCatalog( Guid? catalog );
        IList<WeatherStationDewPointTimeseriesObject> GetWeatherStationDewPointTimeseriesCollectionByCatalogIsNull(  );
        WeatherStationDewPointTimeseriesObject? GetWeatherStationDewPointTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<WeatherStationDewPointTimeseriesObject> GetWeatherStationDewPointTimeseriesCollectionByCatalogIsNullAndName( string name );
        WeatherStationDewPointTimeseriesObject? GetWeatherStationDewPointTimeseriesByWeatherStation( Guid? weatherStation );
        IList<WeatherStationDewPointTimeseriesObject> GetWeatherStationDewPointTimeseriesCollectionByWeatherStationIsNull(  );
        // ---------------------------------------------------------------------
        // WeatherStationRelativeHumidityTimeseries queries
        // ---------------------------------------------------------------------
        WeatherStationRelativeHumidityTimeseriesObject? GetWeatherStationRelativeHumidityTimeseriesById( Guid id );
        IList<WeatherStationRelativeHumidityTimeseriesObject> GetWeatherStationRelativeHumidityTimeseriesCollection( );
        IList<WeatherStationRelativeHumidityTimeseriesObject> GetWeatherStationRelativeHumidityTimeseriesCollectionByCatalog( Guid? catalog );
        IList<WeatherStationRelativeHumidityTimeseriesObject> GetWeatherStationRelativeHumidityTimeseriesCollectionByCatalogIsNull(  );
        WeatherStationRelativeHumidityTimeseriesObject? GetWeatherStationRelativeHumidityTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<WeatherStationRelativeHumidityTimeseriesObject> GetWeatherStationRelativeHumidityTimeseriesCollectionByCatalogIsNullAndName( string name );
        WeatherStationRelativeHumidityTimeseriesObject? GetWeatherStationRelativeHumidityTimeseriesByWeatherStation( Guid? weatherStation );
        IList<WeatherStationRelativeHumidityTimeseriesObject> GetWeatherStationRelativeHumidityTimeseriesCollectionByWeatherStationIsNull(  );
        // ---------------------------------------------------------------------
        // WeatherStationWaterTemperatureTimeseries queries
        // ---------------------------------------------------------------------
        WeatherStationWaterTemperatureTimeseriesObject? GetWeatherStationWaterTemperatureTimeseriesById( Guid id );
        IList<WeatherStationWaterTemperatureTimeseriesObject> GetWeatherStationWaterTemperatureTimeseriesCollection( );
        IList<WeatherStationWaterTemperatureTimeseriesObject> GetWeatherStationWaterTemperatureTimeseriesCollectionByCatalog( Guid? catalog );
        IList<WeatherStationWaterTemperatureTimeseriesObject> GetWeatherStationWaterTemperatureTimeseriesCollectionByCatalogIsNull(  );
        WeatherStationWaterTemperatureTimeseriesObject? GetWeatherStationWaterTemperatureTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<WeatherStationWaterTemperatureTimeseriesObject> GetWeatherStationWaterTemperatureTimeseriesCollectionByCatalogIsNullAndName( string name );
        WeatherStationWaterTemperatureTimeseriesObject? GetWeatherStationWaterTemperatureTimeseriesByWeatherStation( Guid? weatherStation );
        IList<WeatherStationWaterTemperatureTimeseriesObject> GetWeatherStationWaterTemperatureTimeseriesCollectionByWeatherStationIsNull(  );
        // ---------------------------------------------------------------------
        // WeatherStationWindDirectionTimeseries queries
        // ---------------------------------------------------------------------
        WeatherStationWindDirectionTimeseriesObject? GetWeatherStationWindDirectionTimeseriesById( Guid id );
        IList<WeatherStationWindDirectionTimeseriesObject> GetWeatherStationWindDirectionTimeseriesCollection( );
        IList<WeatherStationWindDirectionTimeseriesObject> GetWeatherStationWindDirectionTimeseriesCollectionByCatalog( Guid? catalog );
        IList<WeatherStationWindDirectionTimeseriesObject> GetWeatherStationWindDirectionTimeseriesCollectionByCatalogIsNull(  );
        WeatherStationWindDirectionTimeseriesObject? GetWeatherStationWindDirectionTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<WeatherStationWindDirectionTimeseriesObject> GetWeatherStationWindDirectionTimeseriesCollectionByCatalogIsNullAndName( string name );
        WeatherStationWindDirectionTimeseriesObject? GetWeatherStationWindDirectionTimeseriesByWeatherStation( Guid? weatherStation );
        IList<WeatherStationWindDirectionTimeseriesObject> GetWeatherStationWindDirectionTimeseriesCollectionByWeatherStationIsNull(  );
        // ---------------------------------------------------------------------
        // WeatherStationWindSpeedTimeseries queries
        // ---------------------------------------------------------------------
        WeatherStationWindSpeedTimeseriesObject? GetWeatherStationWindSpeedTimeseriesById( Guid id );
        IList<WeatherStationWindSpeedTimeseriesObject> GetWeatherStationWindSpeedTimeseriesCollection( );
        IList<WeatherStationWindSpeedTimeseriesObject> GetWeatherStationWindSpeedTimeseriesCollectionByCatalog( Guid? catalog );
        IList<WeatherStationWindSpeedTimeseriesObject> GetWeatherStationWindSpeedTimeseriesCollectionByCatalogIsNull(  );
        WeatherStationWindSpeedTimeseriesObject? GetWeatherStationWindSpeedTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<WeatherStationWindSpeedTimeseriesObject> GetWeatherStationWindSpeedTimeseriesCollectionByCatalogIsNullAndName( string name );
        WeatherStationWindSpeedTimeseriesObject? GetWeatherStationWindSpeedTimeseriesByWeatherStation( Guid? weatherStation );
        IList<WeatherStationWindSpeedTimeseriesObject> GetWeatherStationWindSpeedTimeseriesCollectionByWeatherStationIsNull(  );
        // ---------------------------------------------------------------------
        // GeoPosition2DTimeseries queries
        // ---------------------------------------------------------------------
        GeoPosition2DTimeseriesObject? GetGeoPosition2DTimeseriesById( Guid id );
        IList<GeoPosition2DTimeseriesObject> GetGeoPosition2DTimeseriesCollection( );
        IList<GeoPosition2DTimeseriesObject> GetGeoPosition2DTimeseriesCollectionByCatalog( Guid? catalog );
        IList<GeoPosition2DTimeseriesObject> GetGeoPosition2DTimeseriesCollectionByCatalogIsNull(  );
        GeoPosition2DTimeseriesObject? GetGeoPosition2DTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<GeoPosition2DTimeseriesObject> GetGeoPosition2DTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // AisAidToNavigationPositionTimeseries queries
        // ---------------------------------------------------------------------
        AisAidToNavigationPositionTimeseriesObject? GetAisAidToNavigationPositionTimeseriesById( Guid id );
        IList<AisAidToNavigationPositionTimeseriesObject> GetAisAidToNavigationPositionTimeseriesCollection( );
        IList<AisAidToNavigationPositionTimeseriesObject> GetAisAidToNavigationPositionTimeseriesCollectionByCatalog( Guid? catalog );
        IList<AisAidToNavigationPositionTimeseriesObject> GetAisAidToNavigationPositionTimeseriesCollectionByCatalogIsNull(  );
        AisAidToNavigationPositionTimeseriesObject? GetAisAidToNavigationPositionTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<AisAidToNavigationPositionTimeseriesObject> GetAisAidToNavigationPositionTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // GeoPosition3DTimeseries queries
        // ---------------------------------------------------------------------
        GeoPosition3DTimeseriesObject? GetGeoPosition3DTimeseriesById( Guid id );
        IList<GeoPosition3DTimeseriesObject> GetGeoPosition3DTimeseriesCollection( );
        IList<GeoPosition3DTimeseriesObject> GetGeoPosition3DTimeseriesCollectionByCatalog( Guid? catalog );
        IList<GeoPosition3DTimeseriesObject> GetGeoPosition3DTimeseriesCollectionByCatalogIsNull(  );
        GeoPosition3DTimeseriesObject? GetGeoPosition3DTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<GeoPosition3DTimeseriesObject> GetGeoPosition3DTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // GuidTimeseries queries
        // ---------------------------------------------------------------------
        GuidTimeseriesObject? GetGuidTimeseriesById( Guid id );
        IList<GuidTimeseriesObject> GetGuidTimeseriesCollection( );
        IList<GuidTimeseriesObject> GetGuidTimeseriesCollectionByCatalog( Guid? catalog );
        IList<GuidTimeseriesObject> GetGuidTimeseriesCollectionByCatalogIsNull(  );
        GuidTimeseriesObject? GetGuidTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<GuidTimeseriesObject> GetGuidTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // Int16Timeseries queries
        // ---------------------------------------------------------------------
        Int16TimeseriesObject? GetInt16TimeseriesById( Guid id );
        IList<Int16TimeseriesObject> GetInt16TimeseriesCollection( );
        IList<Int16TimeseriesObject> GetInt16TimeseriesCollectionByCatalog( Guid? catalog );
        IList<Int16TimeseriesObject> GetInt16TimeseriesCollectionByCatalogIsNull(  );
        Int16TimeseriesObject? GetInt16TimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<Int16TimeseriesObject> GetInt16TimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // Int32Timeseries queries
        // ---------------------------------------------------------------------
        Int32TimeseriesObject? GetInt32TimeseriesById( Guid id );
        IList<Int32TimeseriesObject> GetInt32TimeseriesCollection( );
        IList<Int32TimeseriesObject> GetInt32TimeseriesCollectionByCatalog( Guid? catalog );
        IList<Int32TimeseriesObject> GetInt32TimeseriesCollectionByCatalogIsNull(  );
        Int32TimeseriesObject? GetInt32TimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<Int32TimeseriesObject> GetInt32TimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // RadarAzimuthOffsetTimeseries queries
        // ---------------------------------------------------------------------
        RadarAzimuthOffsetTimeseriesObject? GetRadarAzimuthOffsetTimeseriesById( Guid id );
        IList<RadarAzimuthOffsetTimeseriesObject> GetRadarAzimuthOffsetTimeseriesCollection( );
        IList<RadarAzimuthOffsetTimeseriesObject> GetRadarAzimuthOffsetTimeseriesCollectionByCatalog( Guid? catalog );
        IList<RadarAzimuthOffsetTimeseriesObject> GetRadarAzimuthOffsetTimeseriesCollectionByCatalogIsNull(  );
        RadarAzimuthOffsetTimeseriesObject? GetRadarAzimuthOffsetTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<RadarAzimuthOffsetTimeseriesObject> GetRadarAzimuthOffsetTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // RadarFastTimeConstantLevelTimeseries queries
        // ---------------------------------------------------------------------
        RadarFastTimeConstantLevelTimeseriesObject? GetRadarFastTimeConstantLevelTimeseriesById( Guid id );
        IList<RadarFastTimeConstantLevelTimeseriesObject> GetRadarFastTimeConstantLevelTimeseriesCollection( );
        IList<RadarFastTimeConstantLevelTimeseriesObject> GetRadarFastTimeConstantLevelTimeseriesCollectionByCatalog( Guid? catalog );
        IList<RadarFastTimeConstantLevelTimeseriesObject> GetRadarFastTimeConstantLevelTimeseriesCollectionByCatalogIsNull(  );
        RadarFastTimeConstantLevelTimeseriesObject? GetRadarFastTimeConstantLevelTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<RadarFastTimeConstantLevelTimeseriesObject> GetRadarFastTimeConstantLevelTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // RadarFastTimeConstantModeTimeseries queries
        // ---------------------------------------------------------------------
        RadarFastTimeConstantModeTimeseriesObject? GetRadarFastTimeConstantModeTimeseriesById( Guid id );
        IList<RadarFastTimeConstantModeTimeseriesObject> GetRadarFastTimeConstantModeTimeseriesCollection( );
        IList<RadarFastTimeConstantModeTimeseriesObject> GetRadarFastTimeConstantModeTimeseriesCollectionByCatalog( Guid? catalog );
        IList<RadarFastTimeConstantModeTimeseriesObject> GetRadarFastTimeConstantModeTimeseriesCollectionByCatalogIsNull(  );
        RadarFastTimeConstantModeTimeseriesObject? GetRadarFastTimeConstantModeTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<RadarFastTimeConstantModeTimeseriesObject> GetRadarFastTimeConstantModeTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // RadarPulseTimeseries queries
        // ---------------------------------------------------------------------
        RadarPulseTimeseriesObject? GetRadarPulseTimeseriesById( Guid id );
        IList<RadarPulseTimeseriesObject> GetRadarPulseTimeseriesCollection( );
        IList<RadarPulseTimeseriesObject> GetRadarPulseTimeseriesCollectionByCatalog( Guid? catalog );
        IList<RadarPulseTimeseriesObject> GetRadarPulseTimeseriesCollectionByCatalogIsNull(  );
        RadarPulseTimeseriesObject? GetRadarPulseTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<RadarPulseTimeseriesObject> GetRadarPulseTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // RadarSector1EndTimeseries queries
        // ---------------------------------------------------------------------
        RadarSector1EndTimeseriesObject? GetRadarSector1EndTimeseriesById( Guid id );
        IList<RadarSector1EndTimeseriesObject> GetRadarSector1EndTimeseriesCollection( );
        IList<RadarSector1EndTimeseriesObject> GetRadarSector1EndTimeseriesCollectionByCatalog( Guid? catalog );
        IList<RadarSector1EndTimeseriesObject> GetRadarSector1EndTimeseriesCollectionByCatalogIsNull(  );
        RadarSector1EndTimeseriesObject? GetRadarSector1EndTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<RadarSector1EndTimeseriesObject> GetRadarSector1EndTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // RadarSector1StartTimeseries queries
        // ---------------------------------------------------------------------
        RadarSector1StartTimeseriesObject? GetRadarSector1StartTimeseriesById( Guid id );
        IList<RadarSector1StartTimeseriesObject> GetRadarSector1StartTimeseriesCollection( );
        IList<RadarSector1StartTimeseriesObject> GetRadarSector1StartTimeseriesCollectionByCatalog( Guid? catalog );
        IList<RadarSector1StartTimeseriesObject> GetRadarSector1StartTimeseriesCollectionByCatalogIsNull(  );
        RadarSector1StartTimeseriesObject? GetRadarSector1StartTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<RadarSector1StartTimeseriesObject> GetRadarSector1StartTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // RadarSector2EndTimeseries queries
        // ---------------------------------------------------------------------
        RadarSector2EndTimeseriesObject? GetRadarSector2EndTimeseriesById( Guid id );
        IList<RadarSector2EndTimeseriesObject> GetRadarSector2EndTimeseriesCollection( );
        IList<RadarSector2EndTimeseriesObject> GetRadarSector2EndTimeseriesCollectionByCatalog( Guid? catalog );
        IList<RadarSector2EndTimeseriesObject> GetRadarSector2EndTimeseriesCollectionByCatalogIsNull(  );
        RadarSector2EndTimeseriesObject? GetRadarSector2EndTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<RadarSector2EndTimeseriesObject> GetRadarSector2EndTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // RadarSector2StartTimeseries queries
        // ---------------------------------------------------------------------
        RadarSector2StartTimeseriesObject? GetRadarSector2StartTimeseriesById( Guid id );
        IList<RadarSector2StartTimeseriesObject> GetRadarSector2StartTimeseriesCollection( );
        IList<RadarSector2StartTimeseriesObject> GetRadarSector2StartTimeseriesCollectionByCatalog( Guid? catalog );
        IList<RadarSector2StartTimeseriesObject> GetRadarSector2StartTimeseriesCollectionByCatalogIsNull(  );
        RadarSector2StartTimeseriesObject? GetRadarSector2StartTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<RadarSector2StartTimeseriesObject> GetRadarSector2StartTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // RadarSensitivityTimeControlLevelTimeseries queries
        // ---------------------------------------------------------------------
        RadarSensitivityTimeControlLevelTimeseriesObject? GetRadarSensitivityTimeControlLevelTimeseriesById( Guid id );
        IList<RadarSensitivityTimeControlLevelTimeseriesObject> GetRadarSensitivityTimeControlLevelTimeseriesCollection( );
        IList<RadarSensitivityTimeControlLevelTimeseriesObject> GetRadarSensitivityTimeControlLevelTimeseriesCollectionByCatalog( Guid? catalog );
        IList<RadarSensitivityTimeControlLevelTimeseriesObject> GetRadarSensitivityTimeControlLevelTimeseriesCollectionByCatalogIsNull(  );
        RadarSensitivityTimeControlLevelTimeseriesObject? GetRadarSensitivityTimeControlLevelTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<RadarSensitivityTimeControlLevelTimeseriesObject> GetRadarSensitivityTimeControlLevelTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // RadarTuningTimeseries queries
        // ---------------------------------------------------------------------
        RadarTuningTimeseriesObject? GetRadarTuningTimeseriesById( Guid id );
        IList<RadarTuningTimeseriesObject> GetRadarTuningTimeseriesCollection( );
        IList<RadarTuningTimeseriesObject> GetRadarTuningTimeseriesCollectionByCatalog( Guid? catalog );
        IList<RadarTuningTimeseriesObject> GetRadarTuningTimeseriesCollectionByCatalogIsNull(  );
        RadarTuningTimeseriesObject? GetRadarTuningTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<RadarTuningTimeseriesObject> GetRadarTuningTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // VesselPersonsOnBoardTimeseries queries
        // ---------------------------------------------------------------------
        VesselPersonsOnBoardTimeseriesObject? GetVesselPersonsOnBoardTimeseriesById( Guid id );
        IList<VesselPersonsOnBoardTimeseriesObject> GetVesselPersonsOnBoardTimeseriesCollection( );
        IList<VesselPersonsOnBoardTimeseriesObject> GetVesselPersonsOnBoardTimeseriesCollectionByCatalog( Guid? catalog );
        IList<VesselPersonsOnBoardTimeseriesObject> GetVesselPersonsOnBoardTimeseriesCollectionByCatalogIsNull(  );
        VesselPersonsOnBoardTimeseriesObject? GetVesselPersonsOnBoardTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<VesselPersonsOnBoardTimeseriesObject> GetVesselPersonsOnBoardTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // Int64Timeseries queries
        // ---------------------------------------------------------------------
        Int64TimeseriesObject? GetInt64TimeseriesById( Guid id );
        IList<Int64TimeseriesObject> GetInt64TimeseriesCollection( );
        IList<Int64TimeseriesObject> GetInt64TimeseriesCollectionByCatalog( Guid? catalog );
        IList<Int64TimeseriesObject> GetInt64TimeseriesCollectionByCatalogIsNull(  );
        Int64TimeseriesObject? GetInt64TimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<Int64TimeseriesObject> GetInt64TimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // Position2DTimeseries queries
        // ---------------------------------------------------------------------
        Position2DTimeseriesObject? GetPosition2DTimeseriesById( Guid id );
        IList<Position2DTimeseriesObject> GetPosition2DTimeseriesCollection( );
        IList<Position2DTimeseriesObject> GetPosition2DTimeseriesCollectionByCatalog( Guid? catalog );
        IList<Position2DTimeseriesObject> GetPosition2DTimeseriesCollectionByCatalogIsNull(  );
        Position2DTimeseriesObject? GetPosition2DTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<Position2DTimeseriesObject> GetPosition2DTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // Position3DTimeseries queries
        // ---------------------------------------------------------------------
        Position3DTimeseriesObject? GetPosition3DTimeseriesById( Guid id );
        IList<Position3DTimeseriesObject> GetPosition3DTimeseriesCollection( );
        IList<Position3DTimeseriesObject> GetPosition3DTimeseriesCollectionByCatalog( Guid? catalog );
        IList<Position3DTimeseriesObject> GetPosition3DTimeseriesCollectionByCatalogIsNull(  );
        Position3DTimeseriesObject? GetPosition3DTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<Position3DTimeseriesObject> GetPosition3DTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // ReferenceTimeseries queries
        // ---------------------------------------------------------------------
        ReferenceTimeseriesObject? GetReferenceTimeseriesById( Guid id );
        IList<ReferenceTimeseriesObject> GetReferenceTimeseriesCollection( );
        IList<ReferenceTimeseriesObject> GetReferenceTimeseriesCollectionByCatalog( Guid? catalog );
        IList<ReferenceTimeseriesObject> GetReferenceTimeseriesCollectionByCatalogIsNull(  );
        ReferenceTimeseriesObject? GetReferenceTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<ReferenceTimeseriesObject> GetReferenceTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // SByteTimeseries queries
        // ---------------------------------------------------------------------
        SByteTimeseriesObject? GetSByteTimeseriesById( Guid id );
        IList<SByteTimeseriesObject> GetSByteTimeseriesCollection( );
        IList<SByteTimeseriesObject> GetSByteTimeseriesCollectionByCatalog( Guid? catalog );
        IList<SByteTimeseriesObject> GetSByteTimeseriesCollectionByCatalogIsNull(  );
        SByteTimeseriesObject? GetSByteTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<SByteTimeseriesObject> GetSByteTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // SingleTimeseries queries
        // ---------------------------------------------------------------------
        SingleTimeseriesObject? GetSingleTimeseriesById( Guid id );
        IList<SingleTimeseriesObject> GetSingleTimeseriesCollection( );
        IList<SingleTimeseriesObject> GetSingleTimeseriesCollectionByCatalog( Guid? catalog );
        IList<SingleTimeseriesObject> GetSingleTimeseriesCollectionByCatalogIsNull(  );
        SingleTimeseriesObject? GetSingleTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<SingleTimeseriesObject> GetSingleTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // StringTimeseries queries
        // ---------------------------------------------------------------------
        StringTimeseriesObject? GetStringTimeseriesById( Guid id );
        IList<StringTimeseriesObject> GetStringTimeseriesCollection( );
        IList<StringTimeseriesObject> GetStringTimeseriesCollectionByCatalog( Guid? catalog );
        IList<StringTimeseriesObject> GetStringTimeseriesCollectionByCatalogIsNull(  );
        StringTimeseriesObject? GetStringTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<StringTimeseriesObject> GetStringTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // TimeSpanTimeseries queries
        // ---------------------------------------------------------------------
        TimeSpanTimeseriesObject? GetTimeSpanTimeseriesById( Guid id );
        IList<TimeSpanTimeseriesObject> GetTimeSpanTimeseriesCollection( );
        IList<TimeSpanTimeseriesObject> GetTimeSpanTimeseriesCollectionByCatalog( Guid? catalog );
        IList<TimeSpanTimeseriesObject> GetTimeSpanTimeseriesCollectionByCatalogIsNull(  );
        TimeSpanTimeseriesObject? GetTimeSpanTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<TimeSpanTimeseriesObject> GetTimeSpanTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // UInt16Timeseries queries
        // ---------------------------------------------------------------------
        UInt16TimeseriesObject? GetUInt16TimeseriesById( Guid id );
        IList<UInt16TimeseriesObject> GetUInt16TimeseriesCollection( );
        IList<UInt16TimeseriesObject> GetUInt16TimeseriesCollectionByCatalog( Guid? catalog );
        IList<UInt16TimeseriesObject> GetUInt16TimeseriesCollectionByCatalogIsNull(  );
        UInt16TimeseriesObject? GetUInt16TimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<UInt16TimeseriesObject> GetUInt16TimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // UInt32Timeseries queries
        // ---------------------------------------------------------------------
        UInt32TimeseriesObject? GetUInt32TimeseriesById( Guid id );
        IList<UInt32TimeseriesObject> GetUInt32TimeseriesCollection( );
        IList<UInt32TimeseriesObject> GetUInt32TimeseriesCollectionByCatalog( Guid? catalog );
        IList<UInt32TimeseriesObject> GetUInt32TimeseriesCollectionByCatalogIsNull(  );
        UInt32TimeseriesObject? GetUInt32TimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<UInt32TimeseriesObject> GetUInt32TimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // RadomeStatusTimeseries queries
        // ---------------------------------------------------------------------
        RadomeStatusTimeseriesObject? GetRadomeStatusTimeseriesById( Guid id );
        IList<RadomeStatusTimeseriesObject> GetRadomeStatusTimeseriesCollection( );
        IList<RadomeStatusTimeseriesObject> GetRadomeStatusTimeseriesCollectionByCatalog( Guid? catalog );
        IList<RadomeStatusTimeseriesObject> GetRadomeStatusTimeseriesCollectionByCatalogIsNull(  );
        RadomeStatusTimeseriesObject? GetRadomeStatusTimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<RadomeStatusTimeseriesObject> GetRadomeStatusTimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // UInt64Timeseries queries
        // ---------------------------------------------------------------------
        UInt64TimeseriesObject? GetUInt64TimeseriesById( Guid id );
        IList<UInt64TimeseriesObject> GetUInt64TimeseriesCollection( );
        IList<UInt64TimeseriesObject> GetUInt64TimeseriesCollectionByCatalog( Guid? catalog );
        IList<UInt64TimeseriesObject> GetUInt64TimeseriesCollectionByCatalogIsNull(  );
        UInt64TimeseriesObject? GetUInt64TimeseriesByCatalogAndName( Guid? catalog, string name );
        IList<UInt64TimeseriesObject> GetUInt64TimeseriesCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // TimeseriesCatalog queries
        // ---------------------------------------------------------------------
        TimeseriesCatalogObject? GetTimeseriesCatalogById( Guid id );
        IList<TimeseriesCatalogObject> GetTimeseriesCatalogCollection( );
        IList<TimeseriesCatalogObject> GetTimeseriesCatalogCollectionByCatalog( Guid? catalog );
        IList<TimeseriesCatalogObject> GetTimeseriesCatalogCollectionByCatalogIsNull(  );
        TimeseriesCatalogObject? GetTimeseriesCatalogByCatalogAndName( Guid? catalog, string name );
        IList<TimeseriesCatalogObject> GetTimeseriesCatalogCollectionByCatalogIsNullAndName( string name );
        // ---------------------------------------------------------------------
        // TimeseriesInfo queries
        // ---------------------------------------------------------------------
        TimeseriesInfoObject? GetTimeseriesInfoById( Guid id );
        IList<TimeseriesInfoObject> GetTimeseriesInfoCollection( );
        // ---------------------------------------------------------------------
        // TimeSpanTimeseriesValue queries
        // ---------------------------------------------------------------------
        TimeSpanTimeseriesValueObject? GetTimeSpanTimeseriesValueById( Guid id );
        IList<TimeSpanTimeseriesValueObject> GetTimeSpanTimeseriesValueCollection( );
        IList<TimeSpanTimeseriesValueObject> GetTimeSpanTimeseriesValueCollectionByTimeseries( Guid timeseries );
        TimeSpanTimeseriesValueObject? GetTimeSpanTimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
        TimeSpanTimeseriesValueObject? GetTimeSpanTimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
        IList<TimeSpanTimeseriesValueObject> GetTimeSpanTimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
        IList<TimeSpanTimeseriesValueObject> GetTimeSpanTimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
        IList<TimeSpanTimeseriesValueObject> GetTimeSpanTimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<TimeSpanTimeseriesValueObject> GetTimeSpanTimeseriesValueCollectionByTimestamp( DateTime timestamp );
        IList<TimeSpanTimeseriesValueObject> GetTimeSpanTimeseriesValueCollectionAtTimestamp( DateTime timestamp );
        IList<TimeSpanTimeseriesValueObject> GetTimeSpanTimeseriesValueCollectionFromTimestamp( DateTime timestamp );
        IList<TimeSpanTimeseriesValueObject> GetTimeSpanTimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
        IList<TimeSpanTimeseriesValueObject> GetTimeSpanTimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // TrackableItemTrackLink queries
        // ---------------------------------------------------------------------
        TrackableItemTrackLinkObject? GetTrackableItemTrackLinkById( Guid id );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkCollection( );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkCollectionByItem( Guid item );
        TrackableItemTrackLinkObject? GetTrackableItemTrackLinkByItemAndStart( Guid item, DateTime start );
        TrackableItemTrackLinkObject? GetTrackableItemTrackLinkByItemAtStart( Guid item, DateTime start );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkByItemFromStart( Guid item, DateTime start );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkByItemUntilStart( Guid item, DateTime start );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkByItemOverStart( Guid item, DateTime fromStart, DateTime untilStart );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkCollectionByItemAndEnd( Guid item, DateTime? end );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkCollectionByItemAndEndIsNull( Guid item );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkCollectionByItemAtEnd( Guid item, DateTime? end );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkCollectionByItemFromEnd( Guid item, DateTime? end );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkCollectionByItemUntilEnd( Guid item, DateTime? end );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkCollectionByItemOverEnd( Guid item, DateTime fromEnd, DateTime untilEnd );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkCollectionByTrack( Guid track );
        TrackableItemTrackLinkObject? GetTrackableItemTrackLinkByTrackAndStart( Guid track, DateTime start );
        TrackableItemTrackLinkObject? GetTrackableItemTrackLinkByTrackAtStart( Guid track, DateTime start );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkByTrackFromStart( Guid track, DateTime start );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkByTrackUntilStart( Guid track, DateTime start );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkByTrackOverStart( Guid track, DateTime fromStart, DateTime untilStart );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkCollectionByTrackAndEnd( Guid track, DateTime? end );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkCollectionByTrackAndEndIsNull( Guid track );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkCollectionByTrackAtEnd( Guid track, DateTime? end );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkCollectionByTrackFromEnd( Guid track, DateTime? end );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkCollectionByTrackUntilEnd( Guid track, DateTime? end );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkCollectionByTrackOverEnd( Guid track, DateTime fromEnd, DateTime untilEnd );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkCollectionByStart( DateTime start );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkCollectionAtStart( DateTime start );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkCollectionFromStart( DateTime start );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkCollectionUntilStart( DateTime start );
        IList<TrackableItemTrackLinkObject> GetTrackableItemTrackLinkCollectionOverStart( DateTime fromStart, DateTime untilStart );
        // ---------------------------------------------------------------------
        // TrackBase queries
        // ---------------------------------------------------------------------
        TrackBaseObject? GetTrackBaseById( Guid id );
        IList<TrackBaseObject> GetTrackBaseCollection( );
        IList<TrackBaseObject> GetTrackBaseCollectionByTracker( Guid tracker );
        IList<TrackBaseObject> GetTrackBaseCollectionByTrackerAndTrackNumber( Guid tracker, long trackNumber );
        IList<TrackBaseObject> GetTrackBaseCollectionByTrackerFromTrackNumber( Guid tracker, long trackNumber );
        IList<TrackBaseObject> GetTrackBaseCollectionByTrackerUntilTrackNumber( Guid tracker, long trackNumber );
        IList<TrackBaseObject> GetTrackBaseCollectionByTrackerOverTrackNumber( Guid tracker, long fromTrackNumber, long untilTrackNumber );
        TrackBaseObject? GetTrackBaseByTrackerTrackNumberAndTimestamp( Guid tracker, long trackNumber, DateTime timestamp );
        TrackBaseObject? GetTrackBaseByTrackerTrackNumberAtTimestamp( Guid tracker, long trackNumber, DateTime timestamp );
        IList<TrackBaseObject> GetTrackBaseByTrackerTrackNumberFromTimestamp( Guid tracker, long trackNumber, DateTime timestamp );
        IList<TrackBaseObject> GetTrackBaseByTrackerTrackNumberUntilTimestamp( Guid tracker, long trackNumber, DateTime timestamp );
        IList<TrackBaseObject> GetTrackBaseByTrackerTrackNumberOverTimestamp( Guid tracker, long trackNumber, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<TrackBaseObject> GetTrackBaseCollectionByTrackerAndTimestamp( Guid tracker, DateTime timestamp );
        IList<TrackBaseObject> GetTrackBaseCollectionByTrackerAtTimestamp( Guid tracker, DateTime timestamp );
        IList<TrackBaseObject> GetTrackBaseCollectionByTrackerFromTimestamp( Guid tracker, DateTime timestamp );
        IList<TrackBaseObject> GetTrackBaseCollectionByTrackerUntilTimestamp( Guid tracker, DateTime timestamp );
        IList<TrackBaseObject> GetTrackBaseCollectionByTrackerOverTimestamp( Guid tracker, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<TrackBaseObject> GetTrackBaseCollectionByTrackNumber( long trackNumber );
        IList<TrackBaseObject> GetTrackBaseCollectionFromTrackNumber( long trackNumber );
        IList<TrackBaseObject> GetTrackBaseCollectionUntilTrackNumber( long trackNumber );
        IList<TrackBaseObject> GetTrackBaseCollectionOverTrackNumber( long fromTrackNumber, long untilTrackNumber );
        IList<TrackBaseObject> GetTrackBaseCollectionByTimestamp( DateTime timestamp );
        IList<TrackBaseObject> GetTrackBaseCollectionAtTimestamp( DateTime timestamp );
        IList<TrackBaseObject> GetTrackBaseCollectionFromTimestamp( DateTime timestamp );
        IList<TrackBaseObject> GetTrackBaseCollectionUntilTimestamp( DateTime timestamp );
        IList<TrackBaseObject> GetTrackBaseCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // Track queries
        // ---------------------------------------------------------------------
        TrackObject? GetTrackById( Guid id );
        IList<TrackObject> GetTrackCollection( );
        IList<TrackObject> GetTrackCollectionByTracker( Guid tracker );
        IList<TrackObject> GetTrackCollectionByTrackerAndTrackNumber( Guid tracker, long trackNumber );
        IList<TrackObject> GetTrackCollectionByTrackerFromTrackNumber( Guid tracker, long trackNumber );
        IList<TrackObject> GetTrackCollectionByTrackerUntilTrackNumber( Guid tracker, long trackNumber );
        IList<TrackObject> GetTrackCollectionByTrackerOverTrackNumber( Guid tracker, long fromTrackNumber, long untilTrackNumber );
        TrackObject? GetTrackByTrackerTrackNumberAndTimestamp( Guid tracker, long trackNumber, DateTime timestamp );
        TrackObject? GetTrackByTrackerTrackNumberAtTimestamp( Guid tracker, long trackNumber, DateTime timestamp );
        IList<TrackObject> GetTrackByTrackerTrackNumberFromTimestamp( Guid tracker, long trackNumber, DateTime timestamp );
        IList<TrackObject> GetTrackByTrackerTrackNumberUntilTimestamp( Guid tracker, long trackNumber, DateTime timestamp );
        IList<TrackObject> GetTrackByTrackerTrackNumberOverTimestamp( Guid tracker, long trackNumber, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<TrackObject> GetTrackCollectionByTrackerAndTimestamp( Guid tracker, DateTime timestamp );
        IList<TrackObject> GetTrackCollectionByTrackerAtTimestamp( Guid tracker, DateTime timestamp );
        IList<TrackObject> GetTrackCollectionByTrackerFromTimestamp( Guid tracker, DateTime timestamp );
        IList<TrackObject> GetTrackCollectionByTrackerUntilTimestamp( Guid tracker, DateTime timestamp );
        IList<TrackObject> GetTrackCollectionByTrackerOverTimestamp( Guid tracker, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<TrackObject> GetTrackCollectionByTrackNumber( long trackNumber );
        IList<TrackObject> GetTrackCollectionFromTrackNumber( long trackNumber );
        IList<TrackObject> GetTrackCollectionUntilTrackNumber( long trackNumber );
        IList<TrackObject> GetTrackCollectionOverTrackNumber( long fromTrackNumber, long untilTrackNumber );
        IList<TrackObject> GetTrackCollectionByTimestamp( DateTime timestamp );
        IList<TrackObject> GetTrackCollectionAtTimestamp( DateTime timestamp );
        IList<TrackObject> GetTrackCollectionFromTimestamp( DateTime timestamp );
        IList<TrackObject> GetTrackCollectionUntilTimestamp( DateTime timestamp );
        IList<TrackObject> GetTrackCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // Track3D queries
        // ---------------------------------------------------------------------
        Track3DObject? GetTrack3DById( Guid id );
        IList<Track3DObject> GetTrack3DCollection( );
        IList<Track3DObject> GetTrack3DCollectionByTracker( Guid tracker );
        IList<Track3DObject> GetTrack3DCollectionByTrackerAndTrackNumber( Guid tracker, long trackNumber );
        IList<Track3DObject> GetTrack3DCollectionByTrackerFromTrackNumber( Guid tracker, long trackNumber );
        IList<Track3DObject> GetTrack3DCollectionByTrackerUntilTrackNumber( Guid tracker, long trackNumber );
        IList<Track3DObject> GetTrack3DCollectionByTrackerOverTrackNumber( Guid tracker, long fromTrackNumber, long untilTrackNumber );
        Track3DObject? GetTrack3DByTrackerTrackNumberAndTimestamp( Guid tracker, long trackNumber, DateTime timestamp );
        Track3DObject? GetTrack3DByTrackerTrackNumberAtTimestamp( Guid tracker, long trackNumber, DateTime timestamp );
        IList<Track3DObject> GetTrack3DByTrackerTrackNumberFromTimestamp( Guid tracker, long trackNumber, DateTime timestamp );
        IList<Track3DObject> GetTrack3DByTrackerTrackNumberUntilTimestamp( Guid tracker, long trackNumber, DateTime timestamp );
        IList<Track3DObject> GetTrack3DByTrackerTrackNumberOverTimestamp( Guid tracker, long trackNumber, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<Track3DObject> GetTrack3DCollectionByTrackerAndTimestamp( Guid tracker, DateTime timestamp );
        IList<Track3DObject> GetTrack3DCollectionByTrackerAtTimestamp( Guid tracker, DateTime timestamp );
        IList<Track3DObject> GetTrack3DCollectionByTrackerFromTimestamp( Guid tracker, DateTime timestamp );
        IList<Track3DObject> GetTrack3DCollectionByTrackerUntilTimestamp( Guid tracker, DateTime timestamp );
        IList<Track3DObject> GetTrack3DCollectionByTrackerOverTimestamp( Guid tracker, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<Track3DObject> GetTrack3DCollectionByTrackNumber( long trackNumber );
        IList<Track3DObject> GetTrack3DCollectionFromTrackNumber( long trackNumber );
        IList<Track3DObject> GetTrack3DCollectionUntilTrackNumber( long trackNumber );
        IList<Track3DObject> GetTrack3DCollectionOverTrackNumber( long fromTrackNumber, long untilTrackNumber );
        IList<Track3DObject> GetTrack3DCollectionByTimestamp( DateTime timestamp );
        IList<Track3DObject> GetTrack3DCollectionAtTimestamp( DateTime timestamp );
        IList<Track3DObject> GetTrack3DCollectionFromTimestamp( DateTime timestamp );
        IList<Track3DObject> GetTrack3DCollectionUntilTimestamp( DateTime timestamp );
        IList<Track3DObject> GetTrack3DCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // TrackerFilterParameters queries
        // ---------------------------------------------------------------------
        TrackerFilterParametersObject? GetTrackerFilterParametersById( Guid id );
        IList<TrackerFilterParametersObject> GetTrackerFilterParametersCollection( );
        IList<TrackerFilterParametersObject> GetTrackerFilterParametersCollectionByTracker( Guid tracker );
        TrackerFilterParametersObject? GetTrackerFilterParametersByTrackerAndName( Guid tracker, string name );
        // ---------------------------------------------------------------------
        // TrackerFilterParametersConfiguration queries
        // ---------------------------------------------------------------------
        TrackerFilterParametersConfigurationObject? GetTrackerFilterParametersConfigurationById( Guid id );
        IList<TrackerFilterParametersConfigurationObject> GetTrackerFilterParametersConfigurationCollection( );
        IList<TrackerFilterParametersConfigurationObject> GetTrackerFilterParametersConfigurationCollectionByParameters( Guid parameters );
        TrackerFilterParametersConfigurationObject? GetTrackerFilterParametersConfigurationByParametersAndTimestamp( Guid parameters, DateTime timestamp );
        TrackerFilterParametersConfigurationObject? GetTrackerFilterParametersConfigurationByParametersAtTimestamp( Guid parameters, DateTime timestamp );
        IList<TrackerFilterParametersConfigurationObject> GetTrackerFilterParametersConfigurationByParametersFromTimestamp( Guid parameters, DateTime timestamp );
        IList<TrackerFilterParametersConfigurationObject> GetTrackerFilterParametersConfigurationByParametersUntilTimestamp( Guid parameters, DateTime timestamp );
        IList<TrackerFilterParametersConfigurationObject> GetTrackerFilterParametersConfigurationByParametersOverTimestamp( Guid parameters, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<TrackerFilterParametersConfigurationObject> GetTrackerFilterParametersConfigurationCollectionByTimestamp( DateTime timestamp );
        IList<TrackerFilterParametersConfigurationObject> GetTrackerFilterParametersConfigurationCollectionAtTimestamp( DateTime timestamp );
        IList<TrackerFilterParametersConfigurationObject> GetTrackerFilterParametersConfigurationCollectionFromTimestamp( DateTime timestamp );
        IList<TrackerFilterParametersConfigurationObject> GetTrackerFilterParametersConfigurationCollectionUntilTimestamp( DateTime timestamp );
        IList<TrackerFilterParametersConfigurationObject> GetTrackerFilterParametersConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // TrackInfo queries
        // ---------------------------------------------------------------------
        TrackInfoObject? GetTrackInfoById( Guid id );
        IList<TrackInfoObject> GetTrackInfoCollection( );
        // ---------------------------------------------------------------------
        // TrackingServiceOptions queries
        // ---------------------------------------------------------------------
        TrackingServiceOptionsObject? GetTrackingServiceOptionsById( Guid id );
        IList<TrackingServiceOptionsObject> GetTrackingServiceOptionsCollection( );
        TrackingServiceOptionsObject? GetTrackingServiceOptionsByTimestamp( DateTime timestamp );
        TrackingServiceOptionsObject? GetTrackingServiceOptionsAtTimestamp( DateTime timestamp );
        IList<TrackingServiceOptionsObject> GetTrackingServiceOptionsFromTimestamp( DateTime timestamp );
        IList<TrackingServiceOptionsObject> GetTrackingServiceOptionsUntilTimestamp( DateTime timestamp );
        IList<TrackingServiceOptionsObject> GetTrackingServiceOptionsOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // TrackLink queries
        // ---------------------------------------------------------------------
        TrackLinkObject? GetTrackLinkById( Guid id );
        IList<TrackLinkObject> GetTrackLinkCollection( );
        IList<TrackLinkObject> GetTrackLinkCollectionByPrimary( Guid primary );
        IList<TrackLinkObject> GetTrackLinkCollectionByPrimaryAndStart( Guid primary, DateTime start );
        IList<TrackLinkObject> GetTrackLinkCollectionByPrimaryAtStart( Guid primary, DateTime start );
        IList<TrackLinkObject> GetTrackLinkCollectionByPrimaryFromStart( Guid primary, DateTime start );
        IList<TrackLinkObject> GetTrackLinkCollectionByPrimaryUntilStart( Guid primary, DateTime start );
        IList<TrackLinkObject> GetTrackLinkCollectionByPrimaryOverStart( Guid primary, DateTime fromStart, DateTime untilStart );
        IList<TrackLinkObject> GetTrackLinkCollectionBySecondary( Guid secondary );
        IList<TrackLinkObject> GetTrackLinkCollectionBySecondaryAndStart( Guid secondary, DateTime start );
        IList<TrackLinkObject> GetTrackLinkCollectionBySecondaryAtStart( Guid secondary, DateTime start );
        IList<TrackLinkObject> GetTrackLinkCollectionBySecondaryFromStart( Guid secondary, DateTime start );
        IList<TrackLinkObject> GetTrackLinkCollectionBySecondaryUntilStart( Guid secondary, DateTime start );
        IList<TrackLinkObject> GetTrackLinkCollectionBySecondaryOverStart( Guid secondary, DateTime fromStart, DateTime untilStart );
        IList<TrackLinkObject> GetTrackLinkCollectionByStart( DateTime start );
        IList<TrackLinkObject> GetTrackLinkCollectionAtStart( DateTime start );
        IList<TrackLinkObject> GetTrackLinkCollectionFromStart( DateTime start );
        IList<TrackLinkObject> GetTrackLinkCollectionUntilStart( DateTime start );
        IList<TrackLinkObject> GetTrackLinkCollectionOverStart( DateTime fromStart, DateTime untilStart );
        // ---------------------------------------------------------------------
        // TrackValue queries
        // ---------------------------------------------------------------------
        TrackValueObject? GetTrackValueById( Guid id );
        IList<TrackValueObject> GetTrackValueCollection( );
        IList<TrackValueObject> GetTrackValueCollectionByTrack( Guid track );
        TrackValueObject? GetTrackValueByTrackAndTimestamp( Guid track, DateTime timestamp );
        TrackValueObject? GetTrackValueByTrackAtTimestamp( Guid track, DateTime timestamp );
        IList<TrackValueObject> GetTrackValueByTrackFromTimestamp( Guid track, DateTime timestamp );
        IList<TrackValueObject> GetTrackValueByTrackUntilTimestamp( Guid track, DateTime timestamp );
        IList<TrackValueObject> GetTrackValueByTrackOverTimestamp( Guid track, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<TrackValueObject> GetTrackValueCollectionByTimestamp( DateTime timestamp );
        IList<TrackValueObject> GetTrackValueCollectionAtTimestamp( DateTime timestamp );
        IList<TrackValueObject> GetTrackValueCollectionFromTimestamp( DateTime timestamp );
        IList<TrackValueObject> GetTrackValueCollectionUntilTimestamp( DateTime timestamp );
        IList<TrackValueObject> GetTrackValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // TrackValue3D queries
        // ---------------------------------------------------------------------
        TrackValue3DObject? GetTrackValue3DById( Guid id );
        IList<TrackValue3DObject> GetTrackValue3DCollection( );
        IList<TrackValue3DObject> GetTrackValue3DCollectionByTrack( Guid track );
        TrackValue3DObject? GetTrackValue3DByTrackAndTimestamp( Guid track, DateTime timestamp );
        TrackValue3DObject? GetTrackValue3DByTrackAtTimestamp( Guid track, DateTime timestamp );
        IList<TrackValue3DObject> GetTrackValue3DByTrackFromTimestamp( Guid track, DateTime timestamp );
        IList<TrackValue3DObject> GetTrackValue3DByTrackUntilTimestamp( Guid track, DateTime timestamp );
        IList<TrackValue3DObject> GetTrackValue3DByTrackOverTimestamp( Guid track, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<TrackValue3DObject> GetTrackValue3DCollectionByTimestamp( DateTime timestamp );
        IList<TrackValue3DObject> GetTrackValue3DCollectionAtTimestamp( DateTime timestamp );
        IList<TrackValue3DObject> GetTrackValue3DCollectionFromTimestamp( DateTime timestamp );
        IList<TrackValue3DObject> GetTrackValue3DCollectionUntilTimestamp( DateTime timestamp );
        IList<TrackValue3DObject> GetTrackValue3DCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // UInt16TimeseriesValue queries
        // ---------------------------------------------------------------------
        UInt16TimeseriesValueObject? GetUInt16TimeseriesValueById( Guid id );
        IList<UInt16TimeseriesValueObject> GetUInt16TimeseriesValueCollection( );
        IList<UInt16TimeseriesValueObject> GetUInt16TimeseriesValueCollectionByTimeseries( Guid timeseries );
        UInt16TimeseriesValueObject? GetUInt16TimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
        UInt16TimeseriesValueObject? GetUInt16TimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
        IList<UInt16TimeseriesValueObject> GetUInt16TimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
        IList<UInt16TimeseriesValueObject> GetUInt16TimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
        IList<UInt16TimeseriesValueObject> GetUInt16TimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<UInt16TimeseriesValueObject> GetUInt16TimeseriesValueCollectionByTimestamp( DateTime timestamp );
        IList<UInt16TimeseriesValueObject> GetUInt16TimeseriesValueCollectionAtTimestamp( DateTime timestamp );
        IList<UInt16TimeseriesValueObject> GetUInt16TimeseriesValueCollectionFromTimestamp( DateTime timestamp );
        IList<UInt16TimeseriesValueObject> GetUInt16TimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
        IList<UInt16TimeseriesValueObject> GetUInt16TimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // UInt32TimeseriesValue queries
        // ---------------------------------------------------------------------
        UInt32TimeseriesValueObject? GetUInt32TimeseriesValueById( Guid id );
        IList<UInt32TimeseriesValueObject> GetUInt32TimeseriesValueCollection( );
        IList<UInt32TimeseriesValueObject> GetUInt32TimeseriesValueCollectionByTimeseries( Guid timeseries );
        UInt32TimeseriesValueObject? GetUInt32TimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
        UInt32TimeseriesValueObject? GetUInt32TimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
        IList<UInt32TimeseriesValueObject> GetUInt32TimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
        IList<UInt32TimeseriesValueObject> GetUInt32TimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
        IList<UInt32TimeseriesValueObject> GetUInt32TimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<UInt32TimeseriesValueObject> GetUInt32TimeseriesValueCollectionByTimestamp( DateTime timestamp );
        IList<UInt32TimeseriesValueObject> GetUInt32TimeseriesValueCollectionAtTimestamp( DateTime timestamp );
        IList<UInt32TimeseriesValueObject> GetUInt32TimeseriesValueCollectionFromTimestamp( DateTime timestamp );
        IList<UInt32TimeseriesValueObject> GetUInt32TimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
        IList<UInt32TimeseriesValueObject> GetUInt32TimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // UInt64TimeseriesValue queries
        // ---------------------------------------------------------------------
        UInt64TimeseriesValueObject? GetUInt64TimeseriesValueById( Guid id );
        IList<UInt64TimeseriesValueObject> GetUInt64TimeseriesValueCollection( );
        IList<UInt64TimeseriesValueObject> GetUInt64TimeseriesValueCollectionByTimeseries( Guid timeseries );
        UInt64TimeseriesValueObject? GetUInt64TimeseriesValueByTimeseriesAndTimestamp( Guid timeseries, DateTime timestamp );
        UInt64TimeseriesValueObject? GetUInt64TimeseriesValueByTimeseriesAtTimestamp( Guid timeseries, DateTime timestamp );
        IList<UInt64TimeseriesValueObject> GetUInt64TimeseriesValueByTimeseriesFromTimestamp( Guid timeseries, DateTime timestamp );
        IList<UInt64TimeseriesValueObject> GetUInt64TimeseriesValueByTimeseriesUntilTimestamp( Guid timeseries, DateTime timestamp );
        IList<UInt64TimeseriesValueObject> GetUInt64TimeseriesValueByTimeseriesOverTimestamp( Guid timeseries, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<UInt64TimeseriesValueObject> GetUInt64TimeseriesValueCollectionByTimestamp( DateTime timestamp );
        IList<UInt64TimeseriesValueObject> GetUInt64TimeseriesValueCollectionAtTimestamp( DateTime timestamp );
        IList<UInt64TimeseriesValueObject> GetUInt64TimeseriesValueCollectionFromTimestamp( DateTime timestamp );
        IList<UInt64TimeseriesValueObject> GetUInt64TimeseriesValueCollectionUntilTimestamp( DateTime timestamp );
        IList<UInt64TimeseriesValueObject> GetUInt64TimeseriesValueCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // VehicleType queries
        // ---------------------------------------------------------------------
        VehicleTypeObject? GetVehicleTypeById( Guid id );
        IList<VehicleTypeObject> GetVehicleTypeCollection( );
        VehicleTypeObject? GetVehicleTypeByName( string name );
        // ---------------------------------------------------------------------
        // VesselType queries
        // ---------------------------------------------------------------------
        VesselTypeObject? GetVesselTypeById( Guid id );
        IList<VesselTypeObject> GetVesselTypeCollection( );
        VesselTypeObject? GetVesselTypeByName( string name );
        VesselTypeObject? GetVesselTypeByCode( int code );
        IList<VesselTypeObject> GetVesselTypeFromCode( int code );
        IList<VesselTypeObject> GetVesselTypeUntilCode( int code );
        IList<VesselTypeObject> GetVesselTypeOverCode( int fromCode, int untilCode );
        // ---------------------------------------------------------------------
        // View queries
        // ---------------------------------------------------------------------
        ViewObject? GetViewById( Guid id );
        IList<ViewObject> GetViewCollection( );
        ViewObject? GetViewByName( string name );
        // ---------------------------------------------------------------------
        // ViewCameraLink queries
        // ---------------------------------------------------------------------
        ViewCameraLinkObject? GetViewCameraLinkById( Guid id );
        IList<ViewCameraLinkObject> GetViewCameraLinkCollection( );
        IList<ViewCameraLinkObject> GetViewCameraLinkCollectionByView( Guid view );
        ViewCameraLinkObject? GetViewCameraLinkByViewAndStart( Guid view, DateTime start );
        ViewCameraLinkObject? GetViewCameraLinkByViewAtStart( Guid view, DateTime start );
        IList<ViewCameraLinkObject> GetViewCameraLinkByViewFromStart( Guid view, DateTime start );
        IList<ViewCameraLinkObject> GetViewCameraLinkByViewUntilStart( Guid view, DateTime start );
        IList<ViewCameraLinkObject> GetViewCameraLinkByViewOverStart( Guid view, DateTime fromStart, DateTime untilStart );
        IList<ViewCameraLinkObject> GetViewCameraLinkCollectionByCamera( Guid camera );
        ViewCameraLinkObject? GetViewCameraLinkByCameraAndStart( Guid camera, DateTime start );
        ViewCameraLinkObject? GetViewCameraLinkByCameraAtStart( Guid camera, DateTime start );
        IList<ViewCameraLinkObject> GetViewCameraLinkByCameraFromStart( Guid camera, DateTime start );
        IList<ViewCameraLinkObject> GetViewCameraLinkByCameraUntilStart( Guid camera, DateTime start );
        IList<ViewCameraLinkObject> GetViewCameraLinkByCameraOverStart( Guid camera, DateTime fromStart, DateTime untilStart );
        IList<ViewCameraLinkObject> GetViewCameraLinkCollectionByStart( DateTime start );
        IList<ViewCameraLinkObject> GetViewCameraLinkCollectionAtStart( DateTime start );
        IList<ViewCameraLinkObject> GetViewCameraLinkCollectionFromStart( DateTime start );
        IList<ViewCameraLinkObject> GetViewCameraLinkCollectionUntilStart( DateTime start );
        IList<ViewCameraLinkObject> GetViewCameraLinkCollectionOverStart( DateTime fromStart, DateTime untilStart );
        // ---------------------------------------------------------------------
        // ViewTrackerLink queries
        // ---------------------------------------------------------------------
        ViewTrackerLinkObject? GetViewTrackerLinkById( Guid id );
        IList<ViewTrackerLinkObject> GetViewTrackerLinkCollection( );
        IList<ViewTrackerLinkObject> GetViewTrackerLinkCollectionByView( Guid view );
        ViewTrackerLinkObject? GetViewTrackerLinkByViewAndStart( Guid view, DateTime start );
        ViewTrackerLinkObject? GetViewTrackerLinkByViewAtStart( Guid view, DateTime start );
        IList<ViewTrackerLinkObject> GetViewTrackerLinkByViewFromStart( Guid view, DateTime start );
        IList<ViewTrackerLinkObject> GetViewTrackerLinkByViewUntilStart( Guid view, DateTime start );
        IList<ViewTrackerLinkObject> GetViewTrackerLinkByViewOverStart( Guid view, DateTime fromStart, DateTime untilStart );
        IList<ViewTrackerLinkObject> GetViewTrackerLinkCollectionByTracker( Guid tracker );
        ViewTrackerLinkObject? GetViewTrackerLinkByTrackerAndStart( Guid tracker, DateTime start );
        ViewTrackerLinkObject? GetViewTrackerLinkByTrackerAtStart( Guid tracker, DateTime start );
        IList<ViewTrackerLinkObject> GetViewTrackerLinkByTrackerFromStart( Guid tracker, DateTime start );
        IList<ViewTrackerLinkObject> GetViewTrackerLinkByTrackerUntilStart( Guid tracker, DateTime start );
        IList<ViewTrackerLinkObject> GetViewTrackerLinkByTrackerOverStart( Guid tracker, DateTime fromStart, DateTime untilStart );
        IList<ViewTrackerLinkObject> GetViewTrackerLinkCollectionByStart( DateTime start );
        IList<ViewTrackerLinkObject> GetViewTrackerLinkCollectionAtStart( DateTime start );
        IList<ViewTrackerLinkObject> GetViewTrackerLinkCollectionFromStart( DateTime start );
        IList<ViewTrackerLinkObject> GetViewTrackerLinkCollectionUntilStart( DateTime start );
        IList<ViewTrackerLinkObject> GetViewTrackerLinkCollectionOverStart( DateTime fromStart, DateTime untilStart );
        // ---------------------------------------------------------------------
        // WeatherStationCommand queries
        // ---------------------------------------------------------------------
        WeatherStationCommandObject? GetWeatherStationCommandById( Guid id );
        IList<WeatherStationCommandObject> GetWeatherStationCommandCollection( );
        IList<WeatherStationCommandObject> GetWeatherStationCommandCollectionByWeatherStation( Guid weatherStation );
        IList<WeatherStationCommandObject> GetWeatherStationCommandCollectionByWeatherStationAndTimestamp( Guid weatherStation, DateTime timestamp );
        IList<WeatherStationCommandObject> GetWeatherStationCommandCollectionByWeatherStationAtTimestamp( Guid weatherStation, DateTime timestamp );
        IList<WeatherStationCommandObject> GetWeatherStationCommandCollectionByWeatherStationFromTimestamp( Guid weatherStation, DateTime timestamp );
        IList<WeatherStationCommandObject> GetWeatherStationCommandCollectionByWeatherStationUntilTimestamp( Guid weatherStation, DateTime timestamp );
        IList<WeatherStationCommandObject> GetWeatherStationCommandCollectionByWeatherStationOverTimestamp( Guid weatherStation, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<WeatherStationCommandObject> GetWeatherStationCommandCollectionByTimestamp( DateTime timestamp );
        IList<WeatherStationCommandObject> GetWeatherStationCommandCollectionAtTimestamp( DateTime timestamp );
        IList<WeatherStationCommandObject> GetWeatherStationCommandCollectionFromTimestamp( DateTime timestamp );
        IList<WeatherStationCommandObject> GetWeatherStationCommandCollectionUntilTimestamp( DateTime timestamp );
        IList<WeatherStationCommandObject> GetWeatherStationCommandCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        IList<WeatherStationCommandObject> GetWeatherStationCommandCollectionByReply( Guid? reply );
        IList<WeatherStationCommandObject> GetWeatherStationCommandCollectionByReplyIsNull(  );
        // ---------------------------------------------------------------------
        // WeatherStationCommandReply queries
        // ---------------------------------------------------------------------
        WeatherStationCommandReplyObject? GetWeatherStationCommandReplyById( Guid id );
        IList<WeatherStationCommandReplyObject> GetWeatherStationCommandReplyCollection( );
        IList<WeatherStationCommandReplyObject> GetWeatherStationCommandReplyCollectionByWeatherStation( Guid weatherStation );
        IList<WeatherStationCommandReplyObject> GetWeatherStationCommandReplyCollectionByWeatherStationAndTimestamp( Guid weatherStation, DateTime timestamp );
        IList<WeatherStationCommandReplyObject> GetWeatherStationCommandReplyCollectionByWeatherStationAtTimestamp( Guid weatherStation, DateTime timestamp );
        IList<WeatherStationCommandReplyObject> GetWeatherStationCommandReplyCollectionByWeatherStationFromTimestamp( Guid weatherStation, DateTime timestamp );
        IList<WeatherStationCommandReplyObject> GetWeatherStationCommandReplyCollectionByWeatherStationUntilTimestamp( Guid weatherStation, DateTime timestamp );
        IList<WeatherStationCommandReplyObject> GetWeatherStationCommandReplyCollectionByWeatherStationOverTimestamp( Guid weatherStation, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<WeatherStationCommandReplyObject> GetWeatherStationCommandReplyCollectionByTimestamp( DateTime timestamp );
        IList<WeatherStationCommandReplyObject> GetWeatherStationCommandReplyCollectionAtTimestamp( DateTime timestamp );
        IList<WeatherStationCommandReplyObject> GetWeatherStationCommandReplyCollectionFromTimestamp( DateTime timestamp );
        IList<WeatherStationCommandReplyObject> GetWeatherStationCommandReplyCollectionUntilTimestamp( DateTime timestamp );
        IList<WeatherStationCommandReplyObject> GetWeatherStationCommandReplyCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        WeatherStationCommandReplyObject? GetWeatherStationCommandReplyByCommand( Guid? command );
        IList<WeatherStationCommandReplyObject> GetWeatherStationCommandReplyCollectionByCommandIsNull(  );
        // ---------------------------------------------------------------------
        // WeatherStationConfiguration queries
        // ---------------------------------------------------------------------
        WeatherStationConfigurationObject? GetWeatherStationConfigurationById( Guid id );
        IList<WeatherStationConfigurationObject> GetWeatherStationConfigurationCollection( );
        IList<WeatherStationConfigurationObject> GetWeatherStationConfigurationCollectionByWeatherStation( Guid weatherStation );
        WeatherStationConfigurationObject? GetWeatherStationConfigurationByWeatherStationAndTimestamp( Guid weatherStation, DateTime timestamp );
        WeatherStationConfigurationObject? GetWeatherStationConfigurationByWeatherStationAtTimestamp( Guid weatherStation, DateTime timestamp );
        IList<WeatherStationConfigurationObject> GetWeatherStationConfigurationByWeatherStationFromTimestamp( Guid weatherStation, DateTime timestamp );
        IList<WeatherStationConfigurationObject> GetWeatherStationConfigurationByWeatherStationUntilTimestamp( Guid weatherStation, DateTime timestamp );
        IList<WeatherStationConfigurationObject> GetWeatherStationConfigurationByWeatherStationOverTimestamp( Guid weatherStation, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<WeatherStationConfigurationObject> GetWeatherStationConfigurationCollectionByTimestamp( DateTime timestamp );
        IList<WeatherStationConfigurationObject> GetWeatherStationConfigurationCollectionAtTimestamp( DateTime timestamp );
        IList<WeatherStationConfigurationObject> GetWeatherStationConfigurationCollectionFromTimestamp( DateTime timestamp );
        IList<WeatherStationConfigurationObject> GetWeatherStationConfigurationCollectionUntilTimestamp( DateTime timestamp );
        IList<WeatherStationConfigurationObject> GetWeatherStationConfigurationCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // Zone queries
        // ---------------------------------------------------------------------
        ZoneObject? GetZoneById( Guid id );
        IList<ZoneObject> GetZoneCollection( );
        ZoneObject? GetZoneByName( string name );
        // ---------------------------------------------------------------------
        // CircularZone queries
        // ---------------------------------------------------------------------
        CircularZoneObject? GetCircularZoneById( Guid id );
        IList<CircularZoneObject> GetCircularZoneCollection( );
        CircularZoneObject? GetCircularZoneByName( string name );
        // ---------------------------------------------------------------------
        // PolygonZone queries
        // ---------------------------------------------------------------------
        PolygonZoneObject? GetPolygonZoneById( Guid id );
        IList<PolygonZoneObject> GetPolygonZoneCollection( );
        PolygonZoneObject? GetPolygonZoneByName( string name );
        // ---------------------------------------------------------------------
        // ZoneExceptions queries
        // ---------------------------------------------------------------------
        ZoneExceptionsObject? GetZoneExceptionsById( Guid id );
        IList<ZoneExceptionsObject> GetZoneExceptionsCollection( );
        IList<ZoneExceptionsObject> GetZoneExceptionsCollectionByZone( Guid zone );
        ZoneExceptionsObject? GetZoneExceptionsByZoneAndTimestamp( Guid zone, DateTime timestamp );
        ZoneExceptionsObject? GetZoneExceptionsByZoneAtTimestamp( Guid zone, DateTime timestamp );
        IList<ZoneExceptionsObject> GetZoneExceptionsByZoneFromTimestamp( Guid zone, DateTime timestamp );
        IList<ZoneExceptionsObject> GetZoneExceptionsByZoneUntilTimestamp( Guid zone, DateTime timestamp );
        IList<ZoneExceptionsObject> GetZoneExceptionsByZoneOverTimestamp( Guid zone, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<ZoneExceptionsObject> GetZoneExceptionsCollectionByTimestamp( DateTime timestamp );
        IList<ZoneExceptionsObject> GetZoneExceptionsCollectionAtTimestamp( DateTime timestamp );
        IList<ZoneExceptionsObject> GetZoneExceptionsCollectionFromTimestamp( DateTime timestamp );
        IList<ZoneExceptionsObject> GetZoneExceptionsCollectionUntilTimestamp( DateTime timestamp );
        IList<ZoneExceptionsObject> GetZoneExceptionsCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
        // ---------------------------------------------------------------------
        // ZoneExceptionsVesselLink queries
        // ---------------------------------------------------------------------
        ZoneExceptionsVesselLinkObject? GetZoneExceptionsVesselLinkById( Guid id );
        IList<ZoneExceptionsVesselLinkObject> GetZoneExceptionsVesselLinkCollection( );
        IList<ZoneExceptionsVesselLinkObject> GetZoneExceptionsVesselLinkCollectionByZoneExceptions( Guid zoneExceptions );
        ZoneExceptionsVesselLinkObject? GetZoneExceptionsVesselLinkByZoneExceptionsAndVessel( Guid zoneExceptions, Guid vessel );
        IList<ZoneExceptionsVesselLinkObject> GetZoneExceptionsVesselLinkCollectionByVessel( Guid vessel );
        // ---------------------------------------------------------------------
        // ZoneTrackAlarm queries
        // ---------------------------------------------------------------------
        ZoneTrackAlarmObject? GetZoneTrackAlarmById( Guid id );
        IList<ZoneTrackAlarmObject> GetZoneTrackAlarmCollection( );
        IList<ZoneTrackAlarmObject> GetZoneTrackAlarmCollectionByTrack( Guid track );
        ZoneTrackAlarmObject? GetZoneTrackAlarmByTrackAndTimestamp( Guid track, DateTime timestamp );
        ZoneTrackAlarmObject? GetZoneTrackAlarmByTrackAtTimestamp( Guid track, DateTime timestamp );
        IList<ZoneTrackAlarmObject> GetZoneTrackAlarmByTrackFromTimestamp( Guid track, DateTime timestamp );
        IList<ZoneTrackAlarmObject> GetZoneTrackAlarmByTrackUntilTimestamp( Guid track, DateTime timestamp );
        IList<ZoneTrackAlarmObject> GetZoneTrackAlarmByTrackOverTimestamp( Guid track, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<ZoneTrackAlarmObject> GetZoneTrackAlarmCollectionByZone( Guid zone );
        IList<ZoneTrackAlarmObject> GetZoneTrackAlarmCollectionByZoneAndTrack( Guid zone, Guid track );
        ZoneTrackAlarmObject? GetZoneTrackAlarmByZoneTrackAndTimestamp( Guid zone, Guid track, DateTime timestamp );
        ZoneTrackAlarmObject? GetZoneTrackAlarmByZoneTrackAtTimestamp( Guid zone, Guid track, DateTime timestamp );
        IList<ZoneTrackAlarmObject> GetZoneTrackAlarmByZoneTrackFromTimestamp( Guid zone, Guid track, DateTime timestamp );
        IList<ZoneTrackAlarmObject> GetZoneTrackAlarmByZoneTrackUntilTimestamp( Guid zone, Guid track, DateTime timestamp );
        IList<ZoneTrackAlarmObject> GetZoneTrackAlarmByZoneTrackOverTimestamp( Guid zone, Guid track, DateTime fromTimestamp, DateTime untilTimestamp );
        IList<ZoneTrackAlarmObject> GetZoneTrackAlarmCollectionByTimestamp( DateTime timestamp );
        IList<ZoneTrackAlarmObject> GetZoneTrackAlarmCollectionAtTimestamp( DateTime timestamp );
        IList<ZoneTrackAlarmObject> GetZoneTrackAlarmCollectionFromTimestamp( DateTime timestamp );
        IList<ZoneTrackAlarmObject> GetZoneTrackAlarmCollectionUntilTimestamp( DateTime timestamp );
        IList<ZoneTrackAlarmObject> GetZoneTrackAlarmCollectionOverTimestamp( DateTime fromTimestamp, DateTime untilTimestamp );
    }
}
