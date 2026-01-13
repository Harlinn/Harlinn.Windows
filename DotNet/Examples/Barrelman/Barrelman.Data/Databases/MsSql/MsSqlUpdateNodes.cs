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
using System.Runtime.CompilerServices;

using Microsoft.Extensions.Logging;

using Harlinn.Common.Core.Net;
using Harlinn.Common.Core.Net.Data;
using Harlinn.Common.Core.Net.Data.Updates;
using Harlinn.Common.Core.Net.Entities;
using Harlinn.Common.Core.Net.IO;

using Barrelman.Data.Types;

namespace Barrelman.Data.Databases.MsSql
{
    public class AircraftTypeUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AircraftTypeUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AircraftTypeObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AircraftTypeObject GetData( ) { return (AircraftTypeObject)_GetData( ); }

        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAircraftType( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAircraftType( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAircraftType( dataObject );
        }
    }
    public class AisDeviceCommandUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisDeviceCommandUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisDeviceCommandObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisDeviceCommandObject GetData( ) { return (AisDeviceCommandObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Reply is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisDeviceCommand( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisDeviceCommand( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisDeviceCommand( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisDeviceCommand( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisDeviceCommand( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisDeviceCommand( dataObject );
        }
    }
    public class AisDeviceCommandReplyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisDeviceCommandReplyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisDeviceCommandReplyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisDeviceCommandReplyObject GetData( ) { return (AisDeviceCommandReplyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Command is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisDeviceCommandReply( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisDeviceCommandReply( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisDeviceCommandReply( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisDeviceCommandReply( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisDeviceCommandReply( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisDeviceCommandReply( dataObject );
        }
    }
    public class AisDeviceConfigurationUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisDeviceConfigurationUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisDeviceConfigurationObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisDeviceConfigurationObject GetData( ) { return (AisDeviceConfigurationObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisDeviceConfiguration( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisDeviceConfiguration( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisDeviceConfiguration( dataObject );
        }
    }
    public class AisDeviceRawMessageUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisDeviceRawMessageUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisDeviceRawMessageObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisDeviceRawMessageObject GetData( ) { return (AisDeviceRawMessageObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisDeviceRawMessage( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisDeviceRawMessage( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisDeviceRawMessage( dataObject );
        }
    }
    public class AisDeviceRawSentenceUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisDeviceRawSentenceUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisDeviceRawSentenceObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisDeviceRawSentenceObject GetData( ) { return (AisDeviceRawSentenceObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisDeviceRawSentence( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisDeviceRawSentence( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisDeviceRawSentence( dataObject );
        }
    }
    public class AidToNavigationReportMessageUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AidToNavigationReportMessageUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AidToNavigationReportMessageObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AidToNavigationReportMessageObject GetData( ) { return (AidToNavigationReportMessageObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Mmsi is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAidToNavigationReportMessage( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AidToNavigationReportMessage( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAidToNavigationReportMessage( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AidToNavigationReportMessage( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AidToNavigationReportMessage( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAidToNavigationReportMessage( dataObject );
        }
    }
    public class AisAddressedSafetyRelatedMessageUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisAddressedSafetyRelatedMessageUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisAddressedSafetyRelatedMessageObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisAddressedSafetyRelatedMessageObject GetData( ) { return (AisAddressedSafetyRelatedMessageObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Mmsi is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }
            if( dataObject.DestinationMmsi is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisAddressedSafetyRelatedMessage( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisAddressedSafetyRelatedMessage( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisAddressedSafetyRelatedMessage( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisAddressedSafetyRelatedMessage( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisAddressedSafetyRelatedMessage( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisAddressedSafetyRelatedMessage( dataObject );
        }
    }
    public class AisBaseStationReportMessageUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisBaseStationReportMessageUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisBaseStationReportMessageObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisBaseStationReportMessageObject GetData( ) { return (AisBaseStationReportMessageObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Mmsi is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisBaseStationReportMessage( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisBaseStationReportMessage( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisBaseStationReportMessage( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisBaseStationReportMessage( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisBaseStationReportMessage( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisBaseStationReportMessage( dataObject );
        }
    }
    public class AisBinaryAcknowledgeMessageUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisBinaryAcknowledgeMessageUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisBinaryAcknowledgeMessageObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisBinaryAcknowledgeMessageObject GetData( ) { return (AisBinaryAcknowledgeMessageObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Mmsi is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }
            if( dataObject.Mmsi1 is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }
            if( dataObject.Mmsi2 is Guid referencedId4 )
            {
                if( updateNodes.TryGetValue( referencedId4, out var otherNode4 ) )
                {
                    if( otherNode4.IsNew )
                    {
                        AddDependency( otherNode4 );
                    }
                }
            }
            if( dataObject.Mmsi3 is Guid referencedId5 )
            {
                if( updateNodes.TryGetValue( referencedId5, out var otherNode5 ) )
                {
                    if( otherNode5.IsNew )
                    {
                        AddDependency( otherNode5 );
                    }
                }
            }
            if( dataObject.Mmsi4 is Guid referencedId6 )
            {
                if( updateNodes.TryGetValue( referencedId6, out var otherNode6 ) )
                {
                    if( otherNode6.IsNew )
                    {
                        AddDependency( otherNode6 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisBinaryAcknowledgeMessage( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisBinaryAcknowledgeMessage( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisBinaryAcknowledgeMessage( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisBinaryAcknowledgeMessage( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisBinaryAcknowledgeMessage( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisBinaryAcknowledgeMessage( dataObject );
        }
    }
    public class AisBinaryAddressedMessageUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisBinaryAddressedMessageUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisBinaryAddressedMessageObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisBinaryAddressedMessageObject GetData( ) { return (AisBinaryAddressedMessageObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Mmsi is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }
            if( dataObject.DestinationMmsi is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisBinaryAddressedMessage( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisBinaryAddressedMessage( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisBinaryAddressedMessage( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisBinaryAddressedMessage( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisBinaryAddressedMessage( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisBinaryAddressedMessage( dataObject );
        }
    }
    public class AisBinaryBroadcastMessageUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisBinaryBroadcastMessageUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisBinaryBroadcastMessageObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisBinaryBroadcastMessageObject GetData( ) { return (AisBinaryBroadcastMessageObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Mmsi is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisBinaryBroadcastMessage( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisBinaryBroadcastMessage( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisBinaryBroadcastMessage( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisBinaryBroadcastMessage( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisBinaryBroadcastMessage( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisBinaryBroadcastMessage( dataObject );
        }
    }
    public class AisDataLinkManagementMessageUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisDataLinkManagementMessageUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisDataLinkManagementMessageObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisDataLinkManagementMessageObject GetData( ) { return (AisDataLinkManagementMessageObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Mmsi is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisDataLinkManagementMessage( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisDataLinkManagementMessage( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisDataLinkManagementMessage( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisDataLinkManagementMessage( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisDataLinkManagementMessage( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisDataLinkManagementMessage( dataObject );
        }
    }
    public class AisExtendedClassBCsPositionReportMessageUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisExtendedClassBCsPositionReportMessageUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisExtendedClassBCsPositionReportMessageObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisExtendedClassBCsPositionReportMessageObject GetData( ) { return (AisExtendedClassBCsPositionReportMessageObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Mmsi is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }
            if( dataObject.Name is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisExtendedClassBCsPositionReportMessage( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisExtendedClassBCsPositionReportMessage( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisExtendedClassBCsPositionReportMessage( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisExtendedClassBCsPositionReportMessage( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisExtendedClassBCsPositionReportMessage( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisExtendedClassBCsPositionReportMessage( dataObject );
        }
    }
    public class AisInterrogationMessageUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisInterrogationMessageUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisInterrogationMessageObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisInterrogationMessageObject GetData( ) { return (AisInterrogationMessageObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Mmsi is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }
            if( dataObject.InterrogatedMmsi is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }
            if( dataObject.SecondStationInterrogationMmsi is Guid referencedId4 )
            {
                if( updateNodes.TryGetValue( referencedId4, out var otherNode4 ) )
                {
                    if( otherNode4.IsNew )
                    {
                        AddDependency( otherNode4 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisInterrogationMessage( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisInterrogationMessage( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisInterrogationMessage( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisInterrogationMessage( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisInterrogationMessage( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisInterrogationMessage( dataObject );
        }
    }
    public class AisPositionReportClassAAssignedScheduleMessageUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisPositionReportClassAAssignedScheduleMessageUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisPositionReportClassAAssignedScheduleMessageObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisPositionReportClassAAssignedScheduleMessageObject GetData( ) { return (AisPositionReportClassAAssignedScheduleMessageObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Mmsi is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisPositionReportClassAAssignedScheduleMessage( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisPositionReportClassAAssignedScheduleMessage( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisPositionReportClassAAssignedScheduleMessage( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisPositionReportClassAAssignedScheduleMessage( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisPositionReportClassAAssignedScheduleMessage( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisPositionReportClassAAssignedScheduleMessage( dataObject );
        }
    }
    public class AisPositionReportClassAMessageUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisPositionReportClassAMessageUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisPositionReportClassAMessageObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisPositionReportClassAMessageObject GetData( ) { return (AisPositionReportClassAMessageObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Mmsi is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisPositionReportClassAMessage( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisPositionReportClassAMessage( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisPositionReportClassAMessage( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisPositionReportClassAMessage( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisPositionReportClassAMessage( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisPositionReportClassAMessage( dataObject );
        }
    }
    public class AisPositionReportClassAResponseToInterrogationMessageUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisPositionReportClassAResponseToInterrogationMessageUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisPositionReportClassAResponseToInterrogationMessageObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisPositionReportClassAResponseToInterrogationMessageObject GetData( ) { return (AisPositionReportClassAResponseToInterrogationMessageObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Mmsi is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisPositionReportClassAResponseToInterrogationMessage( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisPositionReportClassAResponseToInterrogationMessage( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisPositionReportClassAResponseToInterrogationMessage( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisPositionReportClassAResponseToInterrogationMessage( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisPositionReportClassAResponseToInterrogationMessage( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisPositionReportClassAResponseToInterrogationMessage( dataObject );
        }
    }
    public class AisPositionReportForLongRangeApplicationsMessageUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisPositionReportForLongRangeApplicationsMessageUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisPositionReportForLongRangeApplicationsMessageObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisPositionReportForLongRangeApplicationsMessageObject GetData( ) { return (AisPositionReportForLongRangeApplicationsMessageObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Mmsi is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisPositionReportForLongRangeApplicationsMessage( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisPositionReportForLongRangeApplicationsMessage( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisPositionReportForLongRangeApplicationsMessage( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisPositionReportForLongRangeApplicationsMessage( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisPositionReportForLongRangeApplicationsMessage( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisPositionReportForLongRangeApplicationsMessage( dataObject );
        }
    }
    public class AisSafetyRelatedAcknowledgmentMessageUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisSafetyRelatedAcknowledgmentMessageUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisSafetyRelatedAcknowledgmentMessageObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisSafetyRelatedAcknowledgmentMessageObject GetData( ) { return (AisSafetyRelatedAcknowledgmentMessageObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Mmsi is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }
            if( dataObject.Mmsi1 is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }
            if( dataObject.Mmsi2 is Guid referencedId4 )
            {
                if( updateNodes.TryGetValue( referencedId4, out var otherNode4 ) )
                {
                    if( otherNode4.IsNew )
                    {
                        AddDependency( otherNode4 );
                    }
                }
            }
            if( dataObject.Mmsi3 is Guid referencedId5 )
            {
                if( updateNodes.TryGetValue( referencedId5, out var otherNode5 ) )
                {
                    if( otherNode5.IsNew )
                    {
                        AddDependency( otherNode5 );
                    }
                }
            }
            if( dataObject.Mmsi4 is Guid referencedId6 )
            {
                if( updateNodes.TryGetValue( referencedId6, out var otherNode6 ) )
                {
                    if( otherNode6.IsNew )
                    {
                        AddDependency( otherNode6 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisSafetyRelatedAcknowledgmentMessage( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisSafetyRelatedAcknowledgmentMessage( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisSafetyRelatedAcknowledgmentMessage( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisSafetyRelatedAcknowledgmentMessage( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisSafetyRelatedAcknowledgmentMessage( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisSafetyRelatedAcknowledgmentMessage( dataObject );
        }
    }
    public class AisStandardClassBCsPositionReportMessageUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisStandardClassBCsPositionReportMessageUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisStandardClassBCsPositionReportMessageObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisStandardClassBCsPositionReportMessageObject GetData( ) { return (AisStandardClassBCsPositionReportMessageObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Mmsi is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisStandardClassBCsPositionReportMessage( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisStandardClassBCsPositionReportMessage( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisStandardClassBCsPositionReportMessage( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisStandardClassBCsPositionReportMessage( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisStandardClassBCsPositionReportMessage( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisStandardClassBCsPositionReportMessage( dataObject );
        }
    }
    public class AisStandardSarAircraftPositionReportMessageUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisStandardSarAircraftPositionReportMessageUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisStandardSarAircraftPositionReportMessageObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisStandardSarAircraftPositionReportMessageObject GetData( ) { return (AisStandardSarAircraftPositionReportMessageObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Mmsi is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisStandardSarAircraftPositionReportMessage( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisStandardSarAircraftPositionReportMessage( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisStandardSarAircraftPositionReportMessage( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisStandardSarAircraftPositionReportMessage( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisStandardSarAircraftPositionReportMessage( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisStandardSarAircraftPositionReportMessage( dataObject );
        }
    }
    public class AisStaticAndVoyageRelatedDataMessageUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisStaticAndVoyageRelatedDataMessageUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisStaticAndVoyageRelatedDataMessageObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisStaticAndVoyageRelatedDataMessageObject GetData( ) { return (AisStaticAndVoyageRelatedDataMessageObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Mmsi is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }
            if( dataObject.ImoNumber is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }
            if( dataObject.Callsign is Guid referencedId4 )
            {
                if( updateNodes.TryGetValue( referencedId4, out var otherNode4 ) )
                {
                    if( otherNode4.IsNew )
                    {
                        AddDependency( otherNode4 );
                    }
                }
            }
            if( dataObject.ShipName is Guid referencedId5 )
            {
                if( updateNodes.TryGetValue( referencedId5, out var otherNode5 ) )
                {
                    if( otherNode5.IsNew )
                    {
                        AddDependency( otherNode5 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisStaticAndVoyageRelatedDataMessage( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisStaticAndVoyageRelatedDataMessage( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisStaticAndVoyageRelatedDataMessage( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisStaticAndVoyageRelatedDataMessage( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisStaticAndVoyageRelatedDataMessage( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisStaticAndVoyageRelatedDataMessage( dataObject );
        }
    }
    public class AisStaticDataReportMessageUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisStaticDataReportMessageUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisStaticDataReportMessageObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisStaticDataReportMessageObject GetData( ) { return (AisStaticDataReportMessageObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Mmsi is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisStaticDataReportMessage( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisStaticDataReportMessage( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisStaticDataReportMessage( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisStaticDataReportMessage( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisStaticDataReportMessage( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisStaticDataReportMessage( dataObject );
        }
    }
    public class AisStaticDataReportPartAMessageUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisStaticDataReportPartAMessageUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisStaticDataReportPartAMessageObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisStaticDataReportPartAMessageObject GetData( ) { return (AisStaticDataReportPartAMessageObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Mmsi is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }
            if( dataObject.ShipName is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisStaticDataReportPartAMessage( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisStaticDataReportPartAMessage( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisStaticDataReportPartAMessage( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisStaticDataReportPartAMessage( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisStaticDataReportPartAMessage( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisStaticDataReportPartAMessage( dataObject );
        }
    }
    public class AisStaticDataReportPartBMessageUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisStaticDataReportPartBMessageUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisStaticDataReportPartBMessageObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisStaticDataReportPartBMessageObject GetData( ) { return (AisStaticDataReportPartBMessageObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Mmsi is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }
            if( dataObject.Callsign is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }
            if( dataObject.MothershipMmsi is Guid referencedId4 )
            {
                if( updateNodes.TryGetValue( referencedId4, out var otherNode4 ) )
                {
                    if( otherNode4.IsNew )
                    {
                        AddDependency( otherNode4 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisStaticDataReportPartBMessage( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisStaticDataReportPartBMessage( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisStaticDataReportPartBMessage( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisStaticDataReportPartBMessage( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisStaticDataReportPartBMessage( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisStaticDataReportPartBMessage( dataObject );
        }
    }
    public class AisUtcAndDateInquiryMessageUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisUtcAndDateInquiryMessageUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisUtcAndDateInquiryMessageObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisUtcAndDateInquiryMessageObject GetData( ) { return (AisUtcAndDateInquiryMessageObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Mmsi is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }
            if( dataObject.DestinationMmsi is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisUtcAndDateInquiryMessage( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisUtcAndDateInquiryMessage( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisUtcAndDateInquiryMessage( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisUtcAndDateInquiryMessage( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisUtcAndDateInquiryMessage( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisUtcAndDateInquiryMessage( dataObject );
        }
    }
    public class AisUtcAndDateResponseMessageUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisUtcAndDateResponseMessageUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisUtcAndDateResponseMessageObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisUtcAndDateResponseMessageObject GetData( ) { return (AisUtcAndDateResponseMessageObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.AisDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Mmsi is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisUtcAndDateResponseMessage( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisUtcAndDateResponseMessage( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisUtcAndDateResponseMessage( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisUtcAndDateResponseMessage( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisUtcAndDateResponseMessage( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisUtcAndDateResponseMessage( dataObject );
        }
    }
    public class AlarmStateChangeUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AlarmStateChangeUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AlarmStateChangeObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AlarmStateChangeObject GetData( ) { return (AlarmStateChangeObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Alarm, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAlarmStateChange( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAlarmStateChange( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAlarmStateChange( dataObject );
        }
    }
    public class BaseStationTypeUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public BaseStationTypeUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] BaseStationTypeObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        BaseStationTypeObject GetData( ) { return (BaseStationTypeObject)_GetData( ); }

        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertBaseStationType( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateBaseStationType( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteBaseStationType( dataObject );
        }
    }
    public class BinaryTimeseriesValueUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public BinaryTimeseriesValueUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] BinaryTimeseriesValueObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        BinaryTimeseriesValueObject GetData( ) { return (BinaryTimeseriesValueObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Timeseries, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertBinaryTimeseriesValue( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateBinaryTimeseriesValue( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteBinaryTimeseriesValue( dataObject );
        }
    }
    public class BookmarkUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public BookmarkUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] BookmarkObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        BookmarkObject GetData( ) { return (BookmarkObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.View, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertBookmark( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateBookmark( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteBookmark( dataObject );
        }
    }
    public class BooleanTimeseriesValueUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public BooleanTimeseriesValueUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] BooleanTimeseriesValueObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        BooleanTimeseriesValueObject GetData( ) { return (BooleanTimeseriesValueObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Timeseries, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertBooleanTimeseriesValue( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateBooleanTimeseriesValue( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteBooleanTimeseriesValue( dataObject );
        }
    }
    public class ByteTimeseriesValueUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public ByteTimeseriesValueUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] ByteTimeseriesValueObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        ByteTimeseriesValueObject GetData( ) { return (ByteTimeseriesValueObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Timeseries, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertByteTimeseriesValue( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateByteTimeseriesValue( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteByteTimeseriesValue( dataObject );
        }
    }
    public class CameraCommandUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CameraCommandUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CameraCommandObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CameraCommandObject GetData( ) { return (CameraCommandObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Camera, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Reply is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCameraCommand( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1CameraCommand( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCameraCommand( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1CameraCommand( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2CameraCommand( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCameraCommand( dataObject );
        }
    }
    public class CameraCommandAbsoluteMoveUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CameraCommandAbsoluteMoveUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CameraCommandAbsoluteMoveObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CameraCommandAbsoluteMoveObject GetData( ) { return (CameraCommandAbsoluteMoveObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Camera, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Reply is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCameraCommandAbsoluteMove( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1CameraCommandAbsoluteMove( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCameraCommandAbsoluteMove( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1CameraCommandAbsoluteMove( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2CameraCommandAbsoluteMove( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCameraCommandAbsoluteMove( dataObject );
        }
    }
    public class CameraCommandAdjustPanTiltZoomUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CameraCommandAdjustPanTiltZoomUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CameraCommandAdjustPanTiltZoomObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CameraCommandAdjustPanTiltZoomObject GetData( ) { return (CameraCommandAdjustPanTiltZoomObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Camera, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Reply is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCameraCommandAdjustPanTiltZoom( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1CameraCommandAdjustPanTiltZoom( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCameraCommandAdjustPanTiltZoom( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1CameraCommandAdjustPanTiltZoom( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2CameraCommandAdjustPanTiltZoom( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCameraCommandAdjustPanTiltZoom( dataObject );
        }
    }
    public class CameraCommandContinuousMoveUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CameraCommandContinuousMoveUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CameraCommandContinuousMoveObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CameraCommandContinuousMoveObject GetData( ) { return (CameraCommandContinuousMoveObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Camera, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Reply is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCameraCommandContinuousMove( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1CameraCommandContinuousMove( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCameraCommandContinuousMove( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1CameraCommandContinuousMove( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2CameraCommandContinuousMove( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCameraCommandContinuousMove( dataObject );
        }
    }
    public class CameraCommandGeoMoveUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CameraCommandGeoMoveUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CameraCommandGeoMoveObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CameraCommandGeoMoveObject GetData( ) { return (CameraCommandGeoMoveObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Camera, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Reply is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCameraCommandGeoMove( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1CameraCommandGeoMove( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCameraCommandGeoMove( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1CameraCommandGeoMove( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2CameraCommandGeoMove( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCameraCommandGeoMove( dataObject );
        }
    }
    public class CameraCommandRelativeMoveUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CameraCommandRelativeMoveUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CameraCommandRelativeMoveObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CameraCommandRelativeMoveObject GetData( ) { return (CameraCommandRelativeMoveObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Camera, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Reply is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCameraCommandRelativeMove( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1CameraCommandRelativeMove( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCameraCommandRelativeMove( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1CameraCommandRelativeMove( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2CameraCommandRelativeMove( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCameraCommandRelativeMove( dataObject );
        }
    }
    public class CameraCommandReleasePTZOwnershipUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CameraCommandReleasePTZOwnershipUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CameraCommandReleasePTZOwnershipObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CameraCommandReleasePTZOwnershipObject GetData( ) { return (CameraCommandReleasePTZOwnershipObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Camera, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Reply is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCameraCommandReleasePTZOwnership( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1CameraCommandReleasePTZOwnership( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCameraCommandReleasePTZOwnership( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1CameraCommandReleasePTZOwnership( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2CameraCommandReleasePTZOwnership( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCameraCommandReleasePTZOwnership( dataObject );
        }
    }
    public class CameraCommandRequestPTZOwnershipUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CameraCommandRequestPTZOwnershipUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CameraCommandRequestPTZOwnershipObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CameraCommandRequestPTZOwnershipObject GetData( ) { return (CameraCommandRequestPTZOwnershipObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Camera, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Reply is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCameraCommandRequestPTZOwnership( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1CameraCommandRequestPTZOwnership( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCameraCommandRequestPTZOwnership( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1CameraCommandRequestPTZOwnership( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2CameraCommandRequestPTZOwnership( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCameraCommandRequestPTZOwnership( dataObject );
        }
    }
    public class CameraCommandSetAutoFocusUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CameraCommandSetAutoFocusUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CameraCommandSetAutoFocusObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CameraCommandSetAutoFocusObject GetData( ) { return (CameraCommandSetAutoFocusObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Camera, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Reply is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCameraCommandSetAutoFocus( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1CameraCommandSetAutoFocus( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCameraCommandSetAutoFocus( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1CameraCommandSetAutoFocus( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2CameraCommandSetAutoFocus( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCameraCommandSetAutoFocus( dataObject );
        }
    }
    public class CameraCommandSetBlackAndWhiteUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CameraCommandSetBlackAndWhiteUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CameraCommandSetBlackAndWhiteObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CameraCommandSetBlackAndWhiteObject GetData( ) { return (CameraCommandSetBlackAndWhiteObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Camera, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Reply is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCameraCommandSetBlackAndWhite( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1CameraCommandSetBlackAndWhite( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCameraCommandSetBlackAndWhite( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1CameraCommandSetBlackAndWhite( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2CameraCommandSetBlackAndWhite( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCameraCommandSetBlackAndWhite( dataObject );
        }
    }
    public class CameraCommandSetFollowedUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CameraCommandSetFollowedUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CameraCommandSetFollowedObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CameraCommandSetFollowedObject GetData( ) { return (CameraCommandSetFollowedObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Camera, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Reply is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCameraCommandSetFollowed( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1CameraCommandSetFollowed( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCameraCommandSetFollowed( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1CameraCommandSetFollowed( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2CameraCommandSetFollowed( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCameraCommandSetFollowed( dataObject );
        }
    }
    public class CameraCommandSetInfraRedLampUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CameraCommandSetInfraRedLampUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CameraCommandSetInfraRedLampObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CameraCommandSetInfraRedLampObject GetData( ) { return (CameraCommandSetInfraRedLampObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Camera, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Reply is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCameraCommandSetInfraRedLamp( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1CameraCommandSetInfraRedLamp( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCameraCommandSetInfraRedLamp( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1CameraCommandSetInfraRedLamp( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2CameraCommandSetInfraRedLamp( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCameraCommandSetInfraRedLamp( dataObject );
        }
    }
    public class CameraCommandSetWasherUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CameraCommandSetWasherUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CameraCommandSetWasherObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CameraCommandSetWasherObject GetData( ) { return (CameraCommandSetWasherObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Camera, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Reply is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCameraCommandSetWasher( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1CameraCommandSetWasher( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCameraCommandSetWasher( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1CameraCommandSetWasher( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2CameraCommandSetWasher( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCameraCommandSetWasher( dataObject );
        }
    }
    public class CameraCommandSetWiperUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CameraCommandSetWiperUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CameraCommandSetWiperObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CameraCommandSetWiperObject GetData( ) { return (CameraCommandSetWiperObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Camera, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Reply is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCameraCommandSetWiper( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1CameraCommandSetWiper( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCameraCommandSetWiper( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1CameraCommandSetWiper( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2CameraCommandSetWiper( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCameraCommandSetWiper( dataObject );
        }
    }
    public class CameraCommandStopUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CameraCommandStopUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CameraCommandStopObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CameraCommandStopObject GetData( ) { return (CameraCommandStopObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Camera, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Reply is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCameraCommandStop( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1CameraCommandStop( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCameraCommandStop( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1CameraCommandStop( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2CameraCommandStop( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCameraCommandStop( dataObject );
        }
    }
    public class CameraCommandReplyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CameraCommandReplyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CameraCommandReplyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CameraCommandReplyObject GetData( ) { return (CameraCommandReplyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Camera, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Command is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCameraCommandReply( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1CameraCommandReply( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCameraCommandReply( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1CameraCommandReply( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2CameraCommandReply( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCameraCommandReply( dataObject );
        }
    }
    public class CameraConfigurationUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CameraConfigurationUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CameraConfigurationObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CameraConfigurationObject GetData( ) { return (CameraConfigurationObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Camera, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCameraConfiguration( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCameraConfiguration( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCameraConfiguration( dataObject );
        }
    }
    public class CameraPanCalibrationUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CameraPanCalibrationUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CameraPanCalibrationObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CameraPanCalibrationObject GetData( ) { return (CameraPanCalibrationObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Camera, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCameraPanCalibration( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCameraPanCalibration( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCameraPanCalibration( dataObject );
        }
    }
    public class CameraPanCalibrationValueUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CameraPanCalibrationValueUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CameraPanCalibrationValueObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CameraPanCalibrationValueObject GetData( ) { return (CameraPanCalibrationValueObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.PanCalibration, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCameraPanCalibrationValue( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCameraPanCalibrationValue( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCameraPanCalibrationValue( dataObject );
        }
    }
    public class CameraStatusUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CameraStatusUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CameraStatusObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CameraStatusObject GetData( ) { return (CameraStatusObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Camera, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Track is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCameraStatus( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1CameraStatus( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCameraStatus( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1CameraStatus( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2CameraStatus( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCameraStatus( dataObject );
        }
    }
    public class CameraTiltCalibrationUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CameraTiltCalibrationUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CameraTiltCalibrationObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CameraTiltCalibrationObject GetData( ) { return (CameraTiltCalibrationObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Camera, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCameraTiltCalibration( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCameraTiltCalibration( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCameraTiltCalibration( dataObject );
        }
    }
    public class CameraTiltCalibrationValueUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CameraTiltCalibrationValueUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CameraTiltCalibrationValueObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CameraTiltCalibrationValueObject GetData( ) { return (CameraTiltCalibrationValueObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.TiltCalibration, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCameraTiltCalibrationValue( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCameraTiltCalibrationValue( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCameraTiltCalibrationValue( dataObject );
        }
    }
    public class CameraZoomCalibrationUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CameraZoomCalibrationUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CameraZoomCalibrationObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CameraZoomCalibrationObject GetData( ) { return (CameraZoomCalibrationObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Camera, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCameraZoomCalibration( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCameraZoomCalibration( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCameraZoomCalibration( dataObject );
        }
    }
    public class CameraZoomCalibrationValueUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CameraZoomCalibrationValueUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CameraZoomCalibrationValueObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CameraZoomCalibrationValueObject GetData( ) { return (CameraZoomCalibrationValueObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ZoomCalibration, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCameraZoomCalibrationValue( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCameraZoomCalibrationValue( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCameraZoomCalibrationValue( dataObject );
        }
    }
    public class CatalogUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CatalogUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CatalogObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CatalogObject GetData( ) { return (CatalogObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCatalog( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1Catalog( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCatalog( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1Catalog( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2Catalog( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCatalog( dataObject );
        }
    }
    public class ElementUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public ElementUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] ElementObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        ElementObject GetData( ) { return (ElementObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.ElementType is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertElement( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1Element( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateElement( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1Element( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2Element( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteElement( dataObject );
        }
    }
    public class CollectionInfoUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CollectionInfoUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CollectionInfoObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CollectionInfoObject GetData( ) { return (CollectionInfoObject)_GetData( ); }

        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCollectionInfo( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCollectionInfo( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCollectionInfo( dataObject );
        }
    }
    public class CountryUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CountryUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CountryObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CountryObject GetData( ) { return (CountryObject)_GetData( ); }

        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCountry( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCountry( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCountry( dataObject );
        }
    }
    public class CursorInfoUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CursorInfoUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CursorInfoObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CursorInfoObject GetData( ) { return (CursorInfoObject)_GetData( ); }

        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCursorInfo( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCursorInfo( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCursorInfo( dataObject );
        }
    }
    public class DateTimeTimeseriesValueUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public DateTimeTimeseriesValueUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] DateTimeTimeseriesValueObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        DateTimeTimeseriesValueObject GetData( ) { return (DateTimeTimeseriesValueObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Timeseries, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertDateTimeTimeseriesValue( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateDateTimeTimeseriesValue( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteDateTimeTimeseriesValue( dataObject );
        }
    }
    public class DeviceHostUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public DeviceHostUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] DeviceHostObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        DeviceHostObject GetData( ) { return (DeviceHostObject)_GetData( ); }

        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertDeviceHost( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateDeviceHost( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteDeviceHost( dataObject );
        }
    }
    public class DeviceHostConfigurationUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public DeviceHostConfigurationUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] DeviceHostConfigurationObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        DeviceHostConfigurationObject GetData( ) { return (DeviceHostConfigurationObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Host, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertDeviceHostConfiguration( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateDeviceHostConfiguration( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteDeviceHostConfiguration( dataObject );
        }
    }
    public class DoubleTimeseriesValueUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public DoubleTimeseriesValueUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] DoubleTimeseriesValueObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        DoubleTimeseriesValueObject GetData( ) { return (DoubleTimeseriesValueObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Timeseries, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertDoubleTimeseriesValue( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateDoubleTimeseriesValue( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteDoubleTimeseriesValue( dataObject );
        }
    }
    public class FacilityTypeUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public FacilityTypeUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] FacilityTypeObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        FacilityTypeObject GetData( ) { return (FacilityTypeObject)_GetData( ); }

        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertFacilityType( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateFacilityType( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteFacilityType( dataObject );
        }
    }
    public class GeoPosition2DTimeseriesValueUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GeoPosition2DTimeseriesValueUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GeoPosition2DTimeseriesValueObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GeoPosition2DTimeseriesValueObject GetData( ) { return (GeoPosition2DTimeseriesValueObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Timeseries, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGeoPosition2DTimeseriesValue( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGeoPosition2DTimeseriesValue( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGeoPosition2DTimeseriesValue( dataObject );
        }
    }
    public class GeoPosition3DTimeseriesValueUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GeoPosition3DTimeseriesValueUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GeoPosition3DTimeseriesValueObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GeoPosition3DTimeseriesValueObject GetData( ) { return (GeoPosition3DTimeseriesValueObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Timeseries, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGeoPosition3DTimeseriesValue( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGeoPosition3DTimeseriesValue( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGeoPosition3DTimeseriesValue( dataObject );
        }
    }
    public class GNSSDeviceCommandUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GNSSDeviceCommandUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GNSSDeviceCommandObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GNSSDeviceCommandObject GetData( ) { return (GNSSDeviceCommandObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.GNSSDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Reply is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGNSSDeviceCommand( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1GNSSDeviceCommand( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGNSSDeviceCommand( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1GNSSDeviceCommand( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2GNSSDeviceCommand( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGNSSDeviceCommand( dataObject );
        }
    }
    public class GNSSDeviceCommandReplyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GNSSDeviceCommandReplyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GNSSDeviceCommandReplyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GNSSDeviceCommandReplyObject GetData( ) { return (GNSSDeviceCommandReplyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.GNSSDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Command is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGNSSDeviceCommandReply( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1GNSSDeviceCommandReply( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGNSSDeviceCommandReply( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1GNSSDeviceCommandReply( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2GNSSDeviceCommandReply( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGNSSDeviceCommandReply( dataObject );
        }
    }
    public class GNSSDeviceConfigurationUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GNSSDeviceConfigurationUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GNSSDeviceConfigurationObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GNSSDeviceConfigurationObject GetData( ) { return (GNSSDeviceConfigurationObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.GNSSDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGNSSDeviceConfiguration( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGNSSDeviceConfiguration( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGNSSDeviceConfiguration( dataObject );
        }
    }
    public class GuidTimeseriesValueUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GuidTimeseriesValueUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GuidTimeseriesValueObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GuidTimeseriesValueObject GetData( ) { return (GuidTimeseriesValueObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Timeseries, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGuidTimeseriesValue( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGuidTimeseriesValue( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGuidTimeseriesValue( dataObject );
        }
    }
    public class GyroDeviceCommandUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GyroDeviceCommandUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GyroDeviceCommandObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GyroDeviceCommandObject GetData( ) { return (GyroDeviceCommandObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.GyroDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Reply is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGyroDeviceCommand( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1GyroDeviceCommand( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGyroDeviceCommand( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1GyroDeviceCommand( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2GyroDeviceCommand( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGyroDeviceCommand( dataObject );
        }
    }
    public class GyroDeviceCommandReplyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GyroDeviceCommandReplyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GyroDeviceCommandReplyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GyroDeviceCommandReplyObject GetData( ) { return (GyroDeviceCommandReplyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.GyroDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Command is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGyroDeviceCommandReply( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1GyroDeviceCommandReply( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGyroDeviceCommandReply( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1GyroDeviceCommandReply( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2GyroDeviceCommandReply( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGyroDeviceCommandReply( dataObject );
        }
    }
    public class GyroDeviceConfigurationUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GyroDeviceConfigurationUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GyroDeviceConfigurationObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GyroDeviceConfigurationObject GetData( ) { return (GyroDeviceConfigurationObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.GyroDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGyroDeviceConfiguration( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGyroDeviceConfiguration( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGyroDeviceConfiguration( dataObject );
        }
    }
    public class CallsignUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CallsignUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CallsignObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CallsignObject GetData( ) { return (CallsignObject)_GetData( ); }

        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCallsign( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCallsign( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCallsign( dataObject );
        }
    }
    public class InternationalMaritimeOrganizationNumberUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public InternationalMaritimeOrganizationNumberUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] InternationalMaritimeOrganizationNumberObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        InternationalMaritimeOrganizationNumberObject GetData( ) { return (InternationalMaritimeOrganizationNumberObject)_GetData( ); }

        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertInternationalMaritimeOrganizationNumber( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateInternationalMaritimeOrganizationNumber( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteInternationalMaritimeOrganizationNumber( dataObject );
        }
    }
    public class MaritimeMobileServiceIdentityUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public MaritimeMobileServiceIdentityUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] MaritimeMobileServiceIdentityObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        MaritimeMobileServiceIdentityObject GetData( ) { return (MaritimeMobileServiceIdentityObject)_GetData( ); }

        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertMaritimeMobileServiceIdentity( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateMaritimeMobileServiceIdentity( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteMaritimeMobileServiceIdentity( dataObject );
        }
    }
    public class NameUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public NameUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] NameObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        NameObject GetData( ) { return (NameObject)_GetData( ); }

        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertName( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateName( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteName( dataObject );
        }
    }
    public class Int16TimeseriesValueUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public Int16TimeseriesValueUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] Int16TimeseriesValueObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        Int16TimeseriesValueObject GetData( ) { return (Int16TimeseriesValueObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Timeseries, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertInt16TimeseriesValue( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateInt16TimeseriesValue( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteInt16TimeseriesValue( dataObject );
        }
    }
    public class Int32TimeseriesValueUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public Int32TimeseriesValueUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] Int32TimeseriesValueObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        Int32TimeseriesValueObject GetData( ) { return (Int32TimeseriesValueObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Timeseries, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertInt32TimeseriesValue( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateInt32TimeseriesValue( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteInt32TimeseriesValue( dataObject );
        }
    }
    public class Int64TimeseriesValueUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public Int64TimeseriesValueUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] Int64TimeseriesValueObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        Int64TimeseriesValueObject GetData( ) { return (Int64TimeseriesValueObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Timeseries, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertInt64TimeseriesValue( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateInt64TimeseriesValue( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteInt64TimeseriesValue( dataObject );
        }
    }
    public class BaseStationUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public BaseStationUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] BaseStationObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        BaseStationObject GetData( ) { return (BaseStationObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Type is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertBaseStation( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1BaseStation( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateBaseStation( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1BaseStation( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2BaseStation( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteBaseStation( dataObject );
        }
    }
    public class CameraDeviceUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CameraDeviceUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CameraDeviceObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CameraDeviceObject GetData( ) { return (CameraDeviceObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Host, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.EnabledTimeseries is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCameraDevice( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1CameraDevice( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCameraDevice( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1CameraDevice( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2CameraDevice( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCameraDevice( dataObject );
        }
    }
    public class GNSSDeviceUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GNSSDeviceUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GNSSDeviceObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GNSSDeviceObject GetData( ) { return (GNSSDeviceObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Host, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.EnabledTimeseries is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.LatitudeTimeseries is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.LongitudeTimeseries is Guid referencedId4 )
            {
                if( updateNodes.TryGetValue( referencedId4, out var otherNode4 ) )
                {
                    if( otherNode4.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.AltitudeTimeseries is Guid referencedId5 )
            {
                if( updateNodes.TryGetValue( referencedId5, out var otherNode5 ) )
                {
                    if( otherNode5.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGNSSDevice( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1GNSSDevice( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGNSSDevice( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1GNSSDevice( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2GNSSDevice( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGNSSDevice( dataObject );
        }
    }
    public class GyroDeviceUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GyroDeviceUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GyroDeviceObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GyroDeviceObject GetData( ) { return (GyroDeviceObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Host, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.EnabledTimeseries is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.HeadingTrueNorthTimeseries is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.HeadingMagneticNorthTimeseries is Guid referencedId4 )
            {
                if( updateNodes.TryGetValue( referencedId4, out var otherNode4 ) )
                {
                    if( otherNode4.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.PitchTimeseries is Guid referencedId5 )
            {
                if( updateNodes.TryGetValue( referencedId5, out var otherNode5 ) )
                {
                    if( otherNode5.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.RateOfTurnTimeseries is Guid referencedId6 )
            {
                if( updateNodes.TryGetValue( referencedId6, out var otherNode6 ) )
                {
                    if( otherNode6.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.RollTimeseries is Guid referencedId7 )
            {
                if( updateNodes.TryGetValue( referencedId7, out var otherNode7 ) )
                {
                    if( otherNode7.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.CourseTimeseries is Guid referencedId8 )
            {
                if( updateNodes.TryGetValue( referencedId8, out var otherNode8 ) )
                {
                    if( otherNode8.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.SpeedTimeseries is Guid referencedId9 )
            {
                if( updateNodes.TryGetValue( referencedId9, out var otherNode9 ) )
                {
                    if( otherNode9.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.GNSSDevice is Guid referencedId10 )
            {
                if( updateNodes.TryGetValue( referencedId10, out var otherNode10 ) )
                {
                    if( otherNode10.IsNew )
                    {
                        AddDependency( otherNode10 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGyroDevice( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1GyroDevice( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGyroDevice( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1GyroDevice( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2GyroDevice( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGyroDevice( dataObject );
        }
    }
    public class LineInputDeviceUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public LineInputDeviceUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] LineInputDeviceObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        LineInputDeviceObject GetData( ) { return (LineInputDeviceObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Host, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.EnabledTimeseries is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertLineInputDevice( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1LineInputDevice( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateLineInputDevice( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1LineInputDevice( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2LineInputDevice( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteLineInputDevice( dataObject );
        }
    }
    public class OilSpillDetectorDeviceUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public OilSpillDetectorDeviceUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] OilSpillDetectorDeviceObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        OilSpillDetectorDeviceObject GetData( ) { return (OilSpillDetectorDeviceObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Host, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.EnabledTimeseries is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertOilSpillDetectorDevice( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1OilSpillDetectorDevice( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateOilSpillDetectorDevice( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1OilSpillDetectorDevice( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2OilSpillDetectorDevice( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteOilSpillDetectorDevice( dataObject );
        }
    }
    public class RadioDeviceUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadioDeviceUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadioDeviceObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadioDeviceObject GetData( ) { return (RadioDeviceObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Host, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.EnabledTimeseries is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadioDevice( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadioDevice( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadioDevice( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadioDevice( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadioDevice( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadioDevice( dataObject );
        }
    }
    public class RadomeDeviceUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadomeDeviceUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadomeDeviceObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadomeDeviceObject GetData( ) { return (RadomeDeviceObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Host, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.EnabledTimeseries is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.Radar is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.PressureTimeseries is Guid referencedId4 )
            {
                if( updateNodes.TryGetValue( referencedId4, out var otherNode4 ) )
                {
                    if( otherNode4.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.TemperatureTimeseries is Guid referencedId5 )
            {
                if( updateNodes.TryGetValue( referencedId5, out var otherNode5 ) )
                {
                    if( otherNode5.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.DewPointTimeseries is Guid referencedId6 )
            {
                if( updateNodes.TryGetValue( referencedId6, out var otherNode6 ) )
                {
                    if( otherNode6.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.StatusTimeseries is Guid referencedId7 )
            {
                if( updateNodes.TryGetValue( referencedId7, out var otherNode7 ) )
                {
                    if( otherNode7.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadomeDevice( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadomeDevice( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadomeDevice( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadomeDevice( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadomeDevice( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadomeDevice( dataObject );
        }
    }
    public class AisDeviceUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisDeviceUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisDeviceObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisDeviceObject GetData( ) { return (AisDeviceObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Host, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.EnabledTimeseries is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisDevice( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisDevice( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisDevice( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisDevice( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisDevice( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisDevice( dataObject );
        }
    }
    public class RadarDeviceUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarDeviceUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarDeviceObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarDeviceObject GetData( ) { return (RadarDeviceObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Host, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.EnabledTimeseries is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.SaveSettingsTimeseries is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.PowerOnTimeseries is Guid referencedId4 )
            {
                if( updateNodes.TryGetValue( referencedId4, out var otherNode4 ) )
                {
                    if( otherNode4.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.TrackingOnTimeseries is Guid referencedId5 )
            {
                if( updateNodes.TryGetValue( referencedId5, out var otherNode5 ) )
                {
                    if( otherNode5.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.RadarPulseTimeseries is Guid referencedId6 )
            {
                if( updateNodes.TryGetValue( referencedId6, out var otherNode6 ) )
                {
                    if( otherNode6.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.TuningTimeseries is Guid referencedId7 )
            {
                if( updateNodes.TryGetValue( referencedId7, out var otherNode7 ) )
                {
                    if( otherNode7.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.BlankSector1Timeseries is Guid referencedId8 )
            {
                if( updateNodes.TryGetValue( referencedId8, out var otherNode8 ) )
                {
                    if( otherNode8.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.Sector1StartTimeseries is Guid referencedId9 )
            {
                if( updateNodes.TryGetValue( referencedId9, out var otherNode9 ) )
                {
                    if( otherNode9.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.Sector1EndTimeseries is Guid referencedId10 )
            {
                if( updateNodes.TryGetValue( referencedId10, out var otherNode10 ) )
                {
                    if( otherNode10.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.BlankSector2Timeseries is Guid referencedId11 )
            {
                if( updateNodes.TryGetValue( referencedId11, out var otherNode11 ) )
                {
                    if( otherNode11.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.Sector2StartTimeseries is Guid referencedId12 )
            {
                if( updateNodes.TryGetValue( referencedId12, out var otherNode12 ) )
                {
                    if( otherNode12.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.Sector2EndTimeseries is Guid referencedId13 )
            {
                if( updateNodes.TryGetValue( referencedId13, out var otherNode13 ) )
                {
                    if( otherNode13.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.EnableAutomaticFrequencyControlTimeseries is Guid referencedId14 )
            {
                if( updateNodes.TryGetValue( referencedId14, out var otherNode14 ) )
                {
                    if( otherNode14.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.AzimuthOffsetTimeseries is Guid referencedId15 )
            {
                if( updateNodes.TryGetValue( referencedId15, out var otherNode15 ) )
                {
                    if( otherNode15.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.EnableSensitivityTimeControlTimeseries is Guid referencedId16 )
            {
                if( updateNodes.TryGetValue( referencedId16, out var otherNode16 ) )
                {
                    if( otherNode16.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.AutomaticSensitivityTimeControlTimeseries is Guid referencedId17 )
            {
                if( updateNodes.TryGetValue( referencedId17, out var otherNode17 ) )
                {
                    if( otherNode17.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.SensitivityTimeControlLevelTimeseries is Guid referencedId18 )
            {
                if( updateNodes.TryGetValue( referencedId18, out var otherNode18 ) )
                {
                    if( otherNode18.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.EnableFastTimeConstantTimeseries is Guid referencedId19 )
            {
                if( updateNodes.TryGetValue( referencedId19, out var otherNode19 ) )
                {
                    if( otherNode19.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.FastTimeConstantLevelTimeseries is Guid referencedId20 )
            {
                if( updateNodes.TryGetValue( referencedId20, out var otherNode20 ) )
                {
                    if( otherNode20.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.FastTimeConstantModeTimeseries is Guid referencedId21 )
            {
                if( updateNodes.TryGetValue( referencedId21, out var otherNode21 ) )
                {
                    if( otherNode21.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.LatitudeTimeseries is Guid referencedId22 )
            {
                if( updateNodes.TryGetValue( referencedId22, out var otherNode22 ) )
                {
                    if( otherNode22.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.LongitudeTimeseries is Guid referencedId23 )
            {
                if( updateNodes.TryGetValue( referencedId23, out var otherNode23 ) )
                {
                    if( otherNode23.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.Radome is Guid referencedId24 )
            {
                if( updateNodes.TryGetValue( referencedId24, out var otherNode24 ) )
                {
                    if( otherNode24.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.GNSSDevice is Guid referencedId25 )
            {
                if( updateNodes.TryGetValue( referencedId25, out var otherNode25 ) )
                {
                    if( otherNode25.IsNew )
                    {
                        AddDependency( otherNode25 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarDevice( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarDevice( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarDevice( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarDevice( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarDevice( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarDevice( dataObject );
        }
    }
    public class WeatherStationDeviceUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public WeatherStationDeviceUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] WeatherStationDeviceObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        WeatherStationDeviceObject GetData( ) { return (WeatherStationDeviceObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Host, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.EnabledTimeseries is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.BarometricPressureTimeseries is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.AirTemperatureTimeseries is Guid referencedId4 )
            {
                if( updateNodes.TryGetValue( referencedId4, out var otherNode4 ) )
                {
                    if( otherNode4.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.WaterTemperatureTimeseries is Guid referencedId5 )
            {
                if( updateNodes.TryGetValue( referencedId5, out var otherNode5 ) )
                {
                    if( otherNode5.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.RelativeHumidityTimeseries is Guid referencedId6 )
            {
                if( updateNodes.TryGetValue( referencedId6, out var otherNode6 ) )
                {
                    if( otherNode6.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.AbsoluteHumidityTimeseries is Guid referencedId7 )
            {
                if( updateNodes.TryGetValue( referencedId7, out var otherNode7 ) )
                {
                    if( otherNode7.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.DewPointTimeseries is Guid referencedId8 )
            {
                if( updateNodes.TryGetValue( referencedId8, out var otherNode8 ) )
                {
                    if( otherNode8.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.WindDirectionTimeseries is Guid referencedId9 )
            {
                if( updateNodes.TryGetValue( referencedId9, out var otherNode9 ) )
                {
                    if( otherNode9.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.WindSpeedTimeseries is Guid referencedId10 )
            {
                if( updateNodes.TryGetValue( referencedId10, out var otherNode10 ) )
                {
                    if( otherNode10.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.Gyro is Guid referencedId11 )
            {
                if( updateNodes.TryGetValue( referencedId11, out var otherNode11 ) )
                {
                    if( otherNode11.IsNew )
                    {
                        AddDependency( otherNode11 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertWeatherStationDevice( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1WeatherStationDevice( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateWeatherStationDevice( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1WeatherStationDevice( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2WeatherStationDevice( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteWeatherStationDevice( dataObject );
        }
    }
    public class FacilityUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public FacilityUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] FacilityObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        FacilityObject GetData( ) { return (FacilityObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Type is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertFacility( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1Facility( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateFacility( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1Facility( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2Facility( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteFacility( dataObject );
        }
    }
    public class AircraftUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AircraftUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AircraftObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AircraftObject GetData( ) { return (AircraftObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Type is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAircraft( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1Aircraft( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAircraft( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1Aircraft( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2Aircraft( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAircraft( dataObject );
        }
    }
    public class AisAidToNavigationUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisAidToNavigationUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisAidToNavigationObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisAidToNavigationObject GetData( ) { return (AisAidToNavigationObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.MMSI is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Position is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.OffPositionTimeseries is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisAidToNavigation( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisAidToNavigation( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisAidToNavigation( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisAidToNavigation( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisAidToNavigation( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisAidToNavigation( dataObject );
        }
    }
    public class VehicleUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public VehicleUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] VehicleObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        VehicleObject GetData( ) { return (VehicleObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Type is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertVehicle( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1Vehicle( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateVehicle( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1Vehicle( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2Vehicle( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteVehicle( dataObject );
        }
    }
    public class VesselUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public VesselUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] VesselObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        VesselObject GetData( ) { return (VesselObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Type is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.DraughtTimeseries is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.PersonsOnBoardTimeseries is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertVessel( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1Vessel( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateVessel( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1Vessel( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2Vessel( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteVessel( dataObject );
        }
    }
    public class ItemIdentityLinkUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public ItemIdentityLinkUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] ItemIdentityLinkObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        ItemIdentityLinkObject GetData( ) { return (ItemIdentityLinkObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Item, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Identity, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertItemIdentityLink( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateItemIdentityLink( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteItemIdentityLink( dataObject );
        }
    }
    public class ItemParentChildLinkUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public ItemParentChildLinkUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] ItemParentChildLinkObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        ItemParentChildLinkObject GetData( ) { return (ItemParentChildLinkObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Parent, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Child, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertItemParentChildLink( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateItemParentChildLink( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteItemParentChildLink( dataObject );
        }
    }
    public class LineInputDeviceCommandUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public LineInputDeviceCommandUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] LineInputDeviceCommandObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        LineInputDeviceCommandObject GetData( ) { return (LineInputDeviceCommandObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.LineInputDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Reply is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertLineInputDeviceCommand( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1LineInputDeviceCommand( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateLineInputDeviceCommand( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1LineInputDeviceCommand( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2LineInputDeviceCommand( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteLineInputDeviceCommand( dataObject );
        }
    }
    public class LineInputDeviceCommandReplyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public LineInputDeviceCommandReplyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] LineInputDeviceCommandReplyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        LineInputDeviceCommandReplyObject GetData( ) { return (LineInputDeviceCommandReplyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.LineInputDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Command is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertLineInputDeviceCommandReply( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1LineInputDeviceCommandReply( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateLineInputDeviceCommandReply( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1LineInputDeviceCommandReply( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2LineInputDeviceCommandReply( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteLineInputDeviceCommandReply( dataObject );
        }
    }
    public class LineInputDeviceConfigurationUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public LineInputDeviceConfigurationUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] LineInputDeviceConfigurationObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        LineInputDeviceConfigurationObject GetData( ) { return (LineInputDeviceConfigurationObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.LineInputDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertLineInputDeviceConfiguration( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateLineInputDeviceConfiguration( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteLineInputDeviceConfiguration( dataObject );
        }
    }
    public class LineInputMessageRoutingUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public LineInputMessageRoutingUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] LineInputMessageRoutingObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        LineInputMessageRoutingObject GetData( ) { return (LineInputMessageRoutingObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.LineInputDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertLineInputMessageRouting( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateLineInputMessageRouting( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteLineInputMessageRouting( dataObject );
        }
    }
    public class LineInputMessageRoutingDestinationUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public LineInputMessageRoutingDestinationUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] LineInputMessageRoutingDestinationObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        LineInputMessageRoutingDestinationObject GetData( ) { return (LineInputMessageRoutingDestinationObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Routing, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Listener is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertLineInputMessageRoutingDestination( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1LineInputMessageRoutingDestination( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateLineInputMessageRoutingDestination( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1LineInputMessageRoutingDestination( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2LineInputMessageRoutingDestination( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteLineInputMessageRoutingDestination( dataObject );
        }
    }
    public class LineInputWhiteListEntryUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public LineInputWhiteListEntryUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] LineInputWhiteListEntryObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        LineInputWhiteListEntryObject GetData( ) { return (LineInputWhiteListEntryObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.LineInputDevice, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertLineInputWhiteListEntry( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateLineInputWhiteListEntry( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteLineInputWhiteListEntry( dataObject );
        }
    }
    public class LogApplicationUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public LogApplicationUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] LogApplicationObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        LogApplicationObject GetData( ) { return (LogApplicationObject)_GetData( ); }

        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertLogApplication( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateLogApplication( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteLogApplication( dataObject );
        }
    }
    public class LogApplicationConfigurationUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public LogApplicationConfigurationUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] LogApplicationConfigurationObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        LogApplicationConfigurationObject GetData( ) { return (LogApplicationConfigurationObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Application, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertLogApplicationConfiguration( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateLogApplicationConfiguration( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteLogApplicationConfiguration( dataObject );
        }
    }
    public class LogHostUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public LogHostUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] LogHostObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        LogHostObject GetData( ) { return (LogHostObject)_GetData( ); }

        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertLogHost( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateLogHost( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteLogHost( dataObject );
        }
    }
    public class LogHostConfigurationUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public LogHostConfigurationUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] LogHostConfigurationObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        LogHostConfigurationObject GetData( ) { return (LogHostConfigurationObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Host, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertLogHostConfiguration( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateLogHostConfiguration( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteLogHostConfiguration( dataObject );
        }
    }
    public class LogLocationUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public LogLocationUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] LogLocationObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        LogLocationObject GetData( ) { return (LogLocationObject)_GetData( ); }

        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertLogLocation( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateLogLocation( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteLogLocation( dataObject );
        }
    }
    public class LogProcessUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public LogProcessUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] LogProcessObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        LogProcessObject GetData( ) { return (LogProcessObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Application, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Host is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertLogProcess( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1LogProcess( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateLogProcess( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1LogProcess( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2LogProcess( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteLogProcess( dataObject );
        }
    }
    public class LogRecordUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public LogRecordUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] LogRecordObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        LogRecordObject GetData( ) { return (LogRecordObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Thread, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Location, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertLogRecord( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateLogRecord( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteLogRecord( dataObject );
        }
    }
    public class LogThreadUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public LogThreadUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] LogThreadObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        LogThreadObject GetData( ) { return (LogThreadObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Process, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertLogThread( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateLogThread( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteLogThread( dataObject );
        }
    }
    public class LogTraceEntryUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public LogTraceEntryUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] LogTraceEntryObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        LogTraceEntryObject GetData( ) { return (LogTraceEntryObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Thread, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Location, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertLogTraceEntry( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateLogTraceEntry( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteLogTraceEntry( dataObject );
        }
    }
    public class MapElementUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public MapElementUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] MapElementObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        MapElementObject GetData( ) { return (MapElementObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Item, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertMapElement( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateMapElement( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteMapElement( dataObject );
        }
    }
    public class MapInfoUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public MapInfoUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] MapInfoObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        MapInfoObject GetData( ) { return (MapInfoObject)_GetData( ); }

        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertMapInfo( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateMapInfo( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteMapInfo( dataObject );
        }
    }
    public class MapServiceOptionsUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public MapServiceOptionsUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] MapServiceOptionsObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        MapServiceOptionsObject GetData( ) { return (MapServiceOptionsObject)_GetData( ); }

        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertMapServiceOptions( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateMapServiceOptions( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteMapServiceOptions( dataObject );
        }
    }
    public class MaritimeIdentificationDigitsUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public MaritimeIdentificationDigitsUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] MaritimeIdentificationDigitsObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        MaritimeIdentificationDigitsObject GetData( ) { return (MaritimeIdentificationDigitsObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Country, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertMaritimeIdentificationDigits( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateMaritimeIdentificationDigits( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteMaritimeIdentificationDigits( dataObject );
        }
    }
    public class MediaProxySessionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public MediaProxySessionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] MediaProxySessionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        MediaProxySessionObject GetData( ) { return (MediaProxySessionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Service, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.EnabledTimeseries is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertMediaProxySession( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1MediaProxySession( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateMediaProxySession( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1MediaProxySession( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2MediaProxySession( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteMediaProxySession( dataObject );
        }
    }
    public class MediaProxySessionFileUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public MediaProxySessionFileUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] MediaProxySessionFileObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        MediaProxySessionFileObject GetData( ) { return (MediaProxySessionFileObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ProxySession, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertMediaProxySessionFile( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateMediaProxySessionFile( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteMediaProxySessionFile( dataObject );
        }
    }
    public class MediaProxySessionOptionsUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public MediaProxySessionOptionsUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] MediaProxySessionOptionsObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        MediaProxySessionOptionsObject GetData( ) { return (MediaProxySessionOptionsObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ProxySession, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertMediaProxySessionOptions( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateMediaProxySessionOptions( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteMediaProxySessionOptions( dataObject );
        }
    }
    public class MediaServiceUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public MediaServiceUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] MediaServiceObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        MediaServiceObject GetData( ) { return (MediaServiceObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.EnabledTimeseries is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertMediaService( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1MediaService( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateMediaService( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1MediaService( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2MediaService( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteMediaService( dataObject );
        }
    }
    public class MediaServiceOptionsUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public MediaServiceOptionsUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] MediaServiceOptionsObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        MediaServiceOptionsObject GetData( ) { return (MediaServiceOptionsObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.MediaService, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertMediaServiceOptions( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateMediaServiceOptions( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteMediaServiceOptions( dataObject );
        }
    }
    public class ElementTypeUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public ElementTypeUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] ElementTypeObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        ElementTypeObject GetData( ) { return (ElementTypeObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Namespace, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertElementType( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateElementType( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteElementType( dataObject );
        }
    }
    public class NamespaceUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public NamespaceUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] NamespaceObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        NamespaceObject GetData( ) { return (NamespaceObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Namespace, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertNamespace( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateNamespace( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteNamespace( dataObject );
        }
    }
    public class OilSpillUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public OilSpillUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] OilSpillObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        OilSpillObject GetData( ) { return (OilSpillObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.OilSpillDetector, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertOilSpill( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateOilSpill( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteOilSpill( dataObject );
        }
    }
    public class OilSpillDetectorCommandUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public OilSpillDetectorCommandUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] OilSpillDetectorCommandObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        OilSpillDetectorCommandObject GetData( ) { return (OilSpillDetectorCommandObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.OilSpillDetector, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Reply is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertOilSpillDetectorCommand( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1OilSpillDetectorCommand( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateOilSpillDetectorCommand( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1OilSpillDetectorCommand( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2OilSpillDetectorCommand( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteOilSpillDetectorCommand( dataObject );
        }
    }
    public class OilSpillDetectorCommandReplyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public OilSpillDetectorCommandReplyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] OilSpillDetectorCommandReplyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        OilSpillDetectorCommandReplyObject GetData( ) { return (OilSpillDetectorCommandReplyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.OilSpillDetector, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Command is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertOilSpillDetectorCommandReply( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1OilSpillDetectorCommandReply( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateOilSpillDetectorCommandReply( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1OilSpillDetectorCommandReply( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2OilSpillDetectorCommandReply( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteOilSpillDetectorCommandReply( dataObject );
        }
    }
    public class OilSpillDetectorConfigurationUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public OilSpillDetectorConfigurationUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] OilSpillDetectorConfigurationObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        OilSpillDetectorConfigurationObject GetData( ) { return (OilSpillDetectorConfigurationObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.OilSpillDetector, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.TargetMMSI is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertOilSpillDetectorConfiguration( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1OilSpillDetectorConfiguration( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateOilSpillDetectorConfiguration( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1OilSpillDetectorConfiguration( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2OilSpillDetectorConfiguration( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteOilSpillDetectorConfiguration( dataObject );
        }
    }
    public class Position2DTimeseriesValueUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public Position2DTimeseriesValueUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] Position2DTimeseriesValueObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        Position2DTimeseriesValueObject GetData( ) { return (Position2DTimeseriesValueObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Timeseries, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertPosition2DTimeseriesValue( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdatePosition2DTimeseriesValue( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeletePosition2DTimeseriesValue( dataObject );
        }
    }
    public class Position3DTimeseriesValueUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public Position3DTimeseriesValueUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] Position3DTimeseriesValueObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        Position3DTimeseriesValueObject GetData( ) { return (Position3DTimeseriesValueObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Timeseries, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertPosition3DTimeseriesValue( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdatePosition3DTimeseriesValue( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeletePosition3DTimeseriesValue( dataObject );
        }
    }
    public class ProcessTrackValueResultUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public ProcessTrackValueResultUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] ProcessTrackValueResultObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        ProcessTrackValueResultObject GetData( ) { return (ProcessTrackValueResultObject)_GetData( ); }

        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertProcessTrackValueResult( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateProcessTrackValueResult( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteProcessTrackValueResult( dataObject );
        }
    }
    public class BinaryPropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public BinaryPropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] BinaryPropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        BinaryPropertyObject GetData( ) { return (BinaryPropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertBinaryProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateBinaryProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteBinaryProperty( dataObject );
        }
    }
    public class BooleanPropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public BooleanPropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] BooleanPropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        BooleanPropertyObject GetData( ) { return (BooleanPropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertBooleanProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateBooleanProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteBooleanProperty( dataObject );
        }
    }
    public class BytePropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public BytePropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] BytePropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        BytePropertyObject GetData( ) { return (BytePropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertByteProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateByteProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteByteProperty( dataObject );
        }
    }
    public class DateTimePropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public DateTimePropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] DateTimePropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        DateTimePropertyObject GetData( ) { return (DateTimePropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertDateTimeProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateDateTimeProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteDateTimeProperty( dataObject );
        }
    }
    public class DoublePropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public DoublePropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] DoublePropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        DoublePropertyObject GetData( ) { return (DoublePropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertDoubleProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateDoubleProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteDoubleProperty( dataObject );
        }
    }
    public class GuidPropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GuidPropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GuidPropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GuidPropertyObject GetData( ) { return (GuidPropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGuidProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGuidProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGuidProperty( dataObject );
        }
    }
    public class Int16PropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public Int16PropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] Int16PropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        Int16PropertyObject GetData( ) { return (Int16PropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertInt16Property( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateInt16Property( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteInt16Property( dataObject );
        }
    }
    public class Int32PropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public Int32PropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] Int32PropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        Int32PropertyObject GetData( ) { return (Int32PropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertInt32Property( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateInt32Property( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteInt32Property( dataObject );
        }
    }
    public class Int64PropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public Int64PropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] Int64PropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        Int64PropertyObject GetData( ) { return (Int64PropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertInt64Property( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateInt64Property( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteInt64Property( dataObject );
        }
    }
    public class ReferencePropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public ReferencePropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] ReferencePropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        ReferencePropertyObject GetData( ) { return (ReferencePropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }
            if( dataObject.Value is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertReferenceProperty( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1ReferenceProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateReferenceProperty( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1ReferenceProperty( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2ReferenceProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteReferenceProperty( dataObject );
        }
    }
    public class SBytePropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public SBytePropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] SBytePropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        SBytePropertyObject GetData( ) { return (SBytePropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertSByteProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateSByteProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteSByteProperty( dataObject );
        }
    }
    public class SinglePropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public SinglePropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] SinglePropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        SinglePropertyObject GetData( ) { return (SinglePropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertSingleProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateSingleProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteSingleProperty( dataObject );
        }
    }
    public class StringPropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public StringPropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] StringPropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        StringPropertyObject GetData( ) { return (StringPropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertStringProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateStringProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteStringProperty( dataObject );
        }
    }
    public class BinaryTimeseriesPropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public BinaryTimeseriesPropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] BinaryTimeseriesPropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        BinaryTimeseriesPropertyObject GetData( ) { return (BinaryTimeseriesPropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }
            if( dataObject.Timeseries is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertBinaryTimeseriesProperty( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1BinaryTimeseriesProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateBinaryTimeseriesProperty( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1BinaryTimeseriesProperty( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2BinaryTimeseriesProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteBinaryTimeseriesProperty( dataObject );
        }
    }
    public class BooleanTimeseriesPropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public BooleanTimeseriesPropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] BooleanTimeseriesPropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        BooleanTimeseriesPropertyObject GetData( ) { return (BooleanTimeseriesPropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }
            if( dataObject.Timeseries is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertBooleanTimeseriesProperty( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1BooleanTimeseriesProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateBooleanTimeseriesProperty( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1BooleanTimeseriesProperty( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2BooleanTimeseriesProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteBooleanTimeseriesProperty( dataObject );
        }
    }
    public class ByteTimeseriesPropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public ByteTimeseriesPropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] ByteTimeseriesPropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        ByteTimeseriesPropertyObject GetData( ) { return (ByteTimeseriesPropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }
            if( dataObject.Timeseries is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertByteTimeseriesProperty( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1ByteTimeseriesProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateByteTimeseriesProperty( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1ByteTimeseriesProperty( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2ByteTimeseriesProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteByteTimeseriesProperty( dataObject );
        }
    }
    public class DateTimeTimeseriesPropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public DateTimeTimeseriesPropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] DateTimeTimeseriesPropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        DateTimeTimeseriesPropertyObject GetData( ) { return (DateTimeTimeseriesPropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }
            if( dataObject.Timeseries is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertDateTimeTimeseriesProperty( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1DateTimeTimeseriesProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateDateTimeTimeseriesProperty( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1DateTimeTimeseriesProperty( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2DateTimeTimeseriesProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteDateTimeTimeseriesProperty( dataObject );
        }
    }
    public class DoubleTimeseriesPropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public DoubleTimeseriesPropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] DoubleTimeseriesPropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        DoubleTimeseriesPropertyObject GetData( ) { return (DoubleTimeseriesPropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }
            if( dataObject.Timeseries is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertDoubleTimeseriesProperty( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1DoubleTimeseriesProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateDoubleTimeseriesProperty( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1DoubleTimeseriesProperty( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2DoubleTimeseriesProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteDoubleTimeseriesProperty( dataObject );
        }
    }
    public class GuidTimeseriesPropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GuidTimeseriesPropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GuidTimeseriesPropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GuidTimeseriesPropertyObject GetData( ) { return (GuidTimeseriesPropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }
            if( dataObject.Timeseries is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGuidTimeseriesProperty( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1GuidTimeseriesProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGuidTimeseriesProperty( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1GuidTimeseriesProperty( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2GuidTimeseriesProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGuidTimeseriesProperty( dataObject );
        }
    }
    public class Int16TimeseriesPropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public Int16TimeseriesPropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] Int16TimeseriesPropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        Int16TimeseriesPropertyObject GetData( ) { return (Int16TimeseriesPropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }
            if( dataObject.Timeseries is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertInt16TimeseriesProperty( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1Int16TimeseriesProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateInt16TimeseriesProperty( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1Int16TimeseriesProperty( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2Int16TimeseriesProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteInt16TimeseriesProperty( dataObject );
        }
    }
    public class Int32TimeseriesPropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public Int32TimeseriesPropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] Int32TimeseriesPropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        Int32TimeseriesPropertyObject GetData( ) { return (Int32TimeseriesPropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }
            if( dataObject.Timeseries is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertInt32TimeseriesProperty( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1Int32TimeseriesProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateInt32TimeseriesProperty( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1Int32TimeseriesProperty( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2Int32TimeseriesProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteInt32TimeseriesProperty( dataObject );
        }
    }
    public class Int64TimeseriesPropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public Int64TimeseriesPropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] Int64TimeseriesPropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        Int64TimeseriesPropertyObject GetData( ) { return (Int64TimeseriesPropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }
            if( dataObject.Timeseries is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertInt64TimeseriesProperty( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1Int64TimeseriesProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateInt64TimeseriesProperty( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1Int64TimeseriesProperty( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2Int64TimeseriesProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteInt64TimeseriesProperty( dataObject );
        }
    }
    public class ReferenceTimeseriesPropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public ReferenceTimeseriesPropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] ReferenceTimeseriesPropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        ReferenceTimeseriesPropertyObject GetData( ) { return (ReferenceTimeseriesPropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }
            if( dataObject.Timeseries is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertReferenceTimeseriesProperty( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1ReferenceTimeseriesProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateReferenceTimeseriesProperty( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1ReferenceTimeseriesProperty( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2ReferenceTimeseriesProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteReferenceTimeseriesProperty( dataObject );
        }
    }
    public class SByteTimeseriesPropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public SByteTimeseriesPropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] SByteTimeseriesPropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        SByteTimeseriesPropertyObject GetData( ) { return (SByteTimeseriesPropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }
            if( dataObject.Timeseries is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertSByteTimeseriesProperty( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1SByteTimeseriesProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateSByteTimeseriesProperty( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1SByteTimeseriesProperty( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2SByteTimeseriesProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteSByteTimeseriesProperty( dataObject );
        }
    }
    public class SingleTimeseriesPropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public SingleTimeseriesPropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] SingleTimeseriesPropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        SingleTimeseriesPropertyObject GetData( ) { return (SingleTimeseriesPropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }
            if( dataObject.Timeseries is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertSingleTimeseriesProperty( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1SingleTimeseriesProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateSingleTimeseriesProperty( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1SingleTimeseriesProperty( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2SingleTimeseriesProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteSingleTimeseriesProperty( dataObject );
        }
    }
    public class StringTimeseriesPropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public StringTimeseriesPropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] StringTimeseriesPropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        StringTimeseriesPropertyObject GetData( ) { return (StringTimeseriesPropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }
            if( dataObject.Timeseries is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertStringTimeseriesProperty( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1StringTimeseriesProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateStringTimeseriesProperty( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1StringTimeseriesProperty( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2StringTimeseriesProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteStringTimeseriesProperty( dataObject );
        }
    }
    public class TimeSpanTimeseriesPropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public TimeSpanTimeseriesPropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] TimeSpanTimeseriesPropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        TimeSpanTimeseriesPropertyObject GetData( ) { return (TimeSpanTimeseriesPropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }
            if( dataObject.Timeseries is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertTimeSpanTimeseriesProperty( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1TimeSpanTimeseriesProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateTimeSpanTimeseriesProperty( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1TimeSpanTimeseriesProperty( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2TimeSpanTimeseriesProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteTimeSpanTimeseriesProperty( dataObject );
        }
    }
    public class UInt16TimeseriesPropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public UInt16TimeseriesPropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] UInt16TimeseriesPropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        UInt16TimeseriesPropertyObject GetData( ) { return (UInt16TimeseriesPropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }
            if( dataObject.Timeseries is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertUInt16TimeseriesProperty( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1UInt16TimeseriesProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateUInt16TimeseriesProperty( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1UInt16TimeseriesProperty( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2UInt16TimeseriesProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteUInt16TimeseriesProperty( dataObject );
        }
    }
    public class UInt32TimeseriesPropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public UInt32TimeseriesPropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] UInt32TimeseriesPropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        UInt32TimeseriesPropertyObject GetData( ) { return (UInt32TimeseriesPropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }
            if( dataObject.Timeseries is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertUInt32TimeseriesProperty( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1UInt32TimeseriesProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateUInt32TimeseriesProperty( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1UInt32TimeseriesProperty( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2UInt32TimeseriesProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteUInt32TimeseriesProperty( dataObject );
        }
    }
    public class UInt64TimeseriesPropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public UInt64TimeseriesPropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] UInt64TimeseriesPropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        UInt64TimeseriesPropertyObject GetData( ) { return (UInt64TimeseriesPropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }
            if( dataObject.Timeseries is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertUInt64TimeseriesProperty( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1UInt64TimeseriesProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateUInt64TimeseriesProperty( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1UInt64TimeseriesProperty( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2UInt64TimeseriesProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteUInt64TimeseriesProperty( dataObject );
        }
    }
    public class TimeSpanPropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public TimeSpanPropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] TimeSpanPropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        TimeSpanPropertyObject GetData( ) { return (TimeSpanPropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertTimeSpanProperty( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateTimeSpanProperty( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteTimeSpanProperty( dataObject );
        }
    }
    public class UInt16PropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public UInt16PropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] UInt16PropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        UInt16PropertyObject GetData( ) { return (UInt16PropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertUInt16Property( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateUInt16Property( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteUInt16Property( dataObject );
        }
    }
    public class UInt32PropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public UInt32PropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] UInt32PropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        UInt32PropertyObject GetData( ) { return (UInt32PropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertUInt32Property( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateUInt32Property( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteUInt32Property( dataObject );
        }
    }
    public class UInt64PropertyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public UInt64PropertyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] UInt64PropertyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        UInt64PropertyObject GetData( ) { return (UInt64PropertyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Element, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Definition, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertUInt64Property( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateUInt64Property( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteUInt64Property( dataObject );
        }
    }
    public class BinaryPropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public BinaryPropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] BinaryPropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        BinaryPropertyDefinitionObject GetData( ) { return (BinaryPropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertBinaryPropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateBinaryPropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteBinaryPropertyDefinition( dataObject );
        }
    }
    public class BooleanPropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public BooleanPropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] BooleanPropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        BooleanPropertyDefinitionObject GetData( ) { return (BooleanPropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertBooleanPropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateBooleanPropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteBooleanPropertyDefinition( dataObject );
        }
    }
    public class BytePropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public BytePropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] BytePropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        BytePropertyDefinitionObject GetData( ) { return (BytePropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertBytePropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateBytePropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteBytePropertyDefinition( dataObject );
        }
    }
    public class DateTimePropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public DateTimePropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] DateTimePropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        DateTimePropertyDefinitionObject GetData( ) { return (DateTimePropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertDateTimePropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateDateTimePropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteDateTimePropertyDefinition( dataObject );
        }
    }
    public class DoublePropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public DoublePropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] DoublePropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        DoublePropertyDefinitionObject GetData( ) { return (DoublePropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertDoublePropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateDoublePropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteDoublePropertyDefinition( dataObject );
        }
    }
    public class GuidPropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GuidPropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GuidPropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GuidPropertyDefinitionObject GetData( ) { return (GuidPropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGuidPropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGuidPropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGuidPropertyDefinition( dataObject );
        }
    }
    public class Int16PropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public Int16PropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] Int16PropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        Int16PropertyDefinitionObject GetData( ) { return (Int16PropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertInt16PropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateInt16PropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteInt16PropertyDefinition( dataObject );
        }
    }
    public class Int32PropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public Int32PropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] Int32PropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        Int32PropertyDefinitionObject GetData( ) { return (Int32PropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertInt32PropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateInt32PropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteInt32PropertyDefinition( dataObject );
        }
    }
    public class Int64PropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public Int64PropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] Int64PropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        Int64PropertyDefinitionObject GetData( ) { return (Int64PropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertInt64PropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateInt64PropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteInt64PropertyDefinition( dataObject );
        }
    }
    public class ReferencePropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public ReferencePropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] ReferencePropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        ReferencePropertyDefinitionObject GetData( ) { return (ReferencePropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.DefaultValue is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }
            if( dataObject.ReferencedElementType is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertReferencePropertyDefinition( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1ReferencePropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateReferencePropertyDefinition( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1ReferencePropertyDefinition( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2ReferencePropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteReferencePropertyDefinition( dataObject );
        }
    }
    public class SBytePropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public SBytePropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] SBytePropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        SBytePropertyDefinitionObject GetData( ) { return (SBytePropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertSBytePropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateSBytePropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteSBytePropertyDefinition( dataObject );
        }
    }
    public class SinglePropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public SinglePropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] SinglePropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        SinglePropertyDefinitionObject GetData( ) { return (SinglePropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertSinglePropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateSinglePropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteSinglePropertyDefinition( dataObject );
        }
    }
    public class StringPropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public StringPropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] StringPropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        StringPropertyDefinitionObject GetData( ) { return (StringPropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertStringPropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateStringPropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteStringPropertyDefinition( dataObject );
        }
    }
    public class BinaryTimeseriesPropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public BinaryTimeseriesPropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] BinaryTimeseriesPropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        BinaryTimeseriesPropertyDefinitionObject GetData( ) { return (BinaryTimeseriesPropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertBinaryTimeseriesPropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateBinaryTimeseriesPropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteBinaryTimeseriesPropertyDefinition( dataObject );
        }
    }
    public class BooleanTimeseriesPropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public BooleanTimeseriesPropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] BooleanTimeseriesPropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        BooleanTimeseriesPropertyDefinitionObject GetData( ) { return (BooleanTimeseriesPropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertBooleanTimeseriesPropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateBooleanTimeseriesPropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteBooleanTimeseriesPropertyDefinition( dataObject );
        }
    }
    public class ByteTimeseriesPropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public ByteTimeseriesPropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] ByteTimeseriesPropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        ByteTimeseriesPropertyDefinitionObject GetData( ) { return (ByteTimeseriesPropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertByteTimeseriesPropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateByteTimeseriesPropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteByteTimeseriesPropertyDefinition( dataObject );
        }
    }
    public class DateTimeTimeseriesPropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public DateTimeTimeseriesPropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] DateTimeTimeseriesPropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        DateTimeTimeseriesPropertyDefinitionObject GetData( ) { return (DateTimeTimeseriesPropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertDateTimeTimeseriesPropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateDateTimeTimeseriesPropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteDateTimeTimeseriesPropertyDefinition( dataObject );
        }
    }
    public class DoubleTimeseriesPropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public DoubleTimeseriesPropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] DoubleTimeseriesPropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        DoubleTimeseriesPropertyDefinitionObject GetData( ) { return (DoubleTimeseriesPropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertDoubleTimeseriesPropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateDoubleTimeseriesPropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteDoubleTimeseriesPropertyDefinition( dataObject );
        }
    }
    public class GuidTimeseriesPropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GuidTimeseriesPropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GuidTimeseriesPropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GuidTimeseriesPropertyDefinitionObject GetData( ) { return (GuidTimeseriesPropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGuidTimeseriesPropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGuidTimeseriesPropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGuidTimeseriesPropertyDefinition( dataObject );
        }
    }
    public class Int16TimeseriesPropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public Int16TimeseriesPropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] Int16TimeseriesPropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        Int16TimeseriesPropertyDefinitionObject GetData( ) { return (Int16TimeseriesPropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertInt16TimeseriesPropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateInt16TimeseriesPropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteInt16TimeseriesPropertyDefinition( dataObject );
        }
    }
    public class Int32TimeseriesPropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public Int32TimeseriesPropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] Int32TimeseriesPropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        Int32TimeseriesPropertyDefinitionObject GetData( ) { return (Int32TimeseriesPropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertInt32TimeseriesPropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateInt32TimeseriesPropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteInt32TimeseriesPropertyDefinition( dataObject );
        }
    }
    public class Int64TimeseriesPropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public Int64TimeseriesPropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] Int64TimeseriesPropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        Int64TimeseriesPropertyDefinitionObject GetData( ) { return (Int64TimeseriesPropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertInt64TimeseriesPropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateInt64TimeseriesPropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteInt64TimeseriesPropertyDefinition( dataObject );
        }
    }
    public class ReferenceTimeseriesPropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public ReferenceTimeseriesPropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] ReferenceTimeseriesPropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        ReferenceTimeseriesPropertyDefinitionObject GetData( ) { return (ReferenceTimeseriesPropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.ReferencedElementType is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        AddDependency( otherNode2 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertReferenceTimeseriesPropertyDefinition( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1ReferenceTimeseriesPropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateReferenceTimeseriesPropertyDefinition( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1ReferenceTimeseriesPropertyDefinition( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2ReferenceTimeseriesPropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteReferenceTimeseriesPropertyDefinition( dataObject );
        }
    }
    public class SByteTimeseriesPropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public SByteTimeseriesPropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] SByteTimeseriesPropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        SByteTimeseriesPropertyDefinitionObject GetData( ) { return (SByteTimeseriesPropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertSByteTimeseriesPropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateSByteTimeseriesPropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteSByteTimeseriesPropertyDefinition( dataObject );
        }
    }
    public class SingleTimeseriesPropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public SingleTimeseriesPropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] SingleTimeseriesPropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        SingleTimeseriesPropertyDefinitionObject GetData( ) { return (SingleTimeseriesPropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertSingleTimeseriesPropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateSingleTimeseriesPropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteSingleTimeseriesPropertyDefinition( dataObject );
        }
    }
    public class StringTimeseriesPropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public StringTimeseriesPropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] StringTimeseriesPropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        StringTimeseriesPropertyDefinitionObject GetData( ) { return (StringTimeseriesPropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertStringTimeseriesPropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateStringTimeseriesPropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteStringTimeseriesPropertyDefinition( dataObject );
        }
    }
    public class TimeSpanTimeseriesPropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public TimeSpanTimeseriesPropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] TimeSpanTimeseriesPropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        TimeSpanTimeseriesPropertyDefinitionObject GetData( ) { return (TimeSpanTimeseriesPropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertTimeSpanTimeseriesPropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateTimeSpanTimeseriesPropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteTimeSpanTimeseriesPropertyDefinition( dataObject );
        }
    }
    public class UInt16TimeseriesPropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public UInt16TimeseriesPropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] UInt16TimeseriesPropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        UInt16TimeseriesPropertyDefinitionObject GetData( ) { return (UInt16TimeseriesPropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertUInt16TimeseriesPropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateUInt16TimeseriesPropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteUInt16TimeseriesPropertyDefinition( dataObject );
        }
    }
    public class UInt32TimeseriesPropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public UInt32TimeseriesPropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] UInt32TimeseriesPropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        UInt32TimeseriesPropertyDefinitionObject GetData( ) { return (UInt32TimeseriesPropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertUInt32TimeseriesPropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateUInt32TimeseriesPropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteUInt32TimeseriesPropertyDefinition( dataObject );
        }
    }
    public class UInt64TimeseriesPropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public UInt64TimeseriesPropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] UInt64TimeseriesPropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        UInt64TimeseriesPropertyDefinitionObject GetData( ) { return (UInt64TimeseriesPropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertUInt64TimeseriesPropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateUInt64TimeseriesPropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteUInt64TimeseriesPropertyDefinition( dataObject );
        }
    }
    public class TimeSpanPropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public TimeSpanPropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] TimeSpanPropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        TimeSpanPropertyDefinitionObject GetData( ) { return (TimeSpanPropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertTimeSpanPropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateTimeSpanPropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteTimeSpanPropertyDefinition( dataObject );
        }
    }
    public class UInt16PropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public UInt16PropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] UInt16PropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        UInt16PropertyDefinitionObject GetData( ) { return (UInt16PropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertUInt16PropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateUInt16PropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteUInt16PropertyDefinition( dataObject );
        }
    }
    public class UInt32PropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public UInt32PropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] UInt32PropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        UInt32PropertyDefinitionObject GetData( ) { return (UInt32PropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertUInt32PropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateUInt32PropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteUInt32PropertyDefinition( dataObject );
        }
    }
    public class UInt64PropertyDefinitionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public UInt64PropertyDefinitionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] UInt64PropertyDefinitionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        UInt64PropertyDefinitionObject GetData( ) { return (UInt64PropertyDefinitionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ElementType, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertUInt64PropertyDefinition( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateUInt64PropertyDefinition( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteUInt64PropertyDefinition( dataObject );
        }
    }
    public class RadarAlarmStatusUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarAlarmStatusUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarAlarmStatusObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarAlarmStatusObject GetData( ) { return (RadarAlarmStatusObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Radar, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarAlarmStatus( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarAlarmStatus( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarAlarmStatus( dataObject );
        }
    }
    public class RadarCommandUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarCommandUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarCommandObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarCommandObject GetData( ) { return (RadarCommandObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Radar, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Reply is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarCommand( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarCommand( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarCommand( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarCommand( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarCommand( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarCommand( dataObject );
        }
    }
    public class RadarCommandGetStatusUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarCommandGetStatusUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarCommandGetStatusObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarCommandGetStatusObject GetData( ) { return (RadarCommandGetStatusObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Radar, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Reply is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarCommandGetStatus( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarCommandGetStatus( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarCommandGetStatus( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarCommandGetStatus( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarCommandGetStatus( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarCommandGetStatus( dataObject );
        }
    }
    public class RadarCommandReplyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarCommandReplyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarCommandReplyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarCommandReplyObject GetData( ) { return (RadarCommandReplyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Radar, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Command is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarCommandReply( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarCommandReply( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarCommandReply( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarCommandReply( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarCommandReply( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarCommandReply( dataObject );
        }
    }
    public class RadarCommandReplyGetStatusUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarCommandReplyGetStatusUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarCommandReplyGetStatusObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarCommandReplyGetStatusObject GetData( ) { return (RadarCommandReplyGetStatusObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Radar, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Command is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarCommandReplyGetStatus( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarCommandReplyGetStatus( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarCommandReplyGetStatus( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarCommandReplyGetStatus( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarCommandReplyGetStatus( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarCommandReplyGetStatus( dataObject );
        }
    }
    public class RadarConfigurationUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarConfigurationUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarConfigurationObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarConfigurationObject GetData( ) { return (RadarConfigurationObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Radar, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarConfiguration( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarConfiguration( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarConfiguration( dataObject );
        }
    }
    public class RadarImageUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarImageUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarImageObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarImageObject GetData( ) { return (RadarImageObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Radar, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarImage( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarImage( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarImage( dataObject );
        }
    }
    public class RadarRawTrackTableUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarRawTrackTableUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarRawTrackTableObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarRawTrackTableObject GetData( ) { return (RadarRawTrackTableObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Radar, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarRawTrackTable( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarRawTrackTable( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarRawTrackTable( dataObject );
        }
    }
    public class RadarStatusUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarStatusUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarStatusObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarStatusObject GetData( ) { return (RadarStatusObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Radar, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarStatus( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarStatus( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarStatus( dataObject );
        }
    }
    public class RadioCommandUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadioCommandUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadioCommandObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadioCommandObject GetData( ) { return (RadioCommandObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Radio, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Reply is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadioCommand( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadioCommand( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadioCommand( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadioCommand( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadioCommand( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadioCommand( dataObject );
        }
    }
    public class RadioCommandReplyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadioCommandReplyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadioCommandReplyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadioCommandReplyObject GetData( ) { return (RadioCommandReplyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Radio, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Command is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadioCommandReply( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadioCommandReply( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadioCommandReply( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadioCommandReply( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadioCommandReply( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadioCommandReply( dataObject );
        }
    }
    public class RadioConfigurationUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadioConfigurationUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadioConfigurationObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadioConfigurationObject GetData( ) { return (RadioConfigurationObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Radio, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadioConfiguration( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadioConfiguration( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadioConfiguration( dataObject );
        }
    }
    public class RadomeCommandUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadomeCommandUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadomeCommandObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadomeCommandObject GetData( ) { return (RadomeCommandObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Radome, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Reply is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadomeCommand( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadomeCommand( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadomeCommand( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadomeCommand( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadomeCommand( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadomeCommand( dataObject );
        }
    }
    public class RadomeCommandReplyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadomeCommandReplyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadomeCommandReplyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadomeCommandReplyObject GetData( ) { return (RadomeCommandReplyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Radome, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Command is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadomeCommandReply( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadomeCommandReply( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadomeCommandReply( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadomeCommandReply( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadomeCommandReply( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadomeCommandReply( dataObject );
        }
    }
    public class RadomeConfigurationUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadomeConfigurationUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadomeConfigurationObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadomeConfigurationObject GetData( ) { return (RadomeConfigurationObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Radome, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadomeConfiguration( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadomeConfiguration( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadomeConfiguration( dataObject );
        }
    }
    public class ReferenceTimeseriesValueUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public ReferenceTimeseriesValueUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] ReferenceTimeseriesValueObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        ReferenceTimeseriesValueObject GetData( ) { return (ReferenceTimeseriesValueObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Timeseries, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Value, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertReferenceTimeseriesValue( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateReferenceTimeseriesValue( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteReferenceTimeseriesValue( dataObject );
        }
    }
    public class SByteTimeseriesValueUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public SByteTimeseriesValueUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] SByteTimeseriesValueObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        SByteTimeseriesValueObject GetData( ) { return (SByteTimeseriesValueObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Timeseries, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertSByteTimeseriesValue( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateSByteTimeseriesValue( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteSByteTimeseriesValue( dataObject );
        }
    }
    public class SecurityDomainUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public SecurityDomainUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] SecurityDomainObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        SecurityDomainObject GetData( ) { return (SecurityDomainObject)_GetData( ); }

        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertSecurityDomain( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateSecurityDomain( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteSecurityDomain( dataObject );
        }
    }
    public class SecurityLoginUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public SecurityLoginUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] SecurityLoginObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        SecurityLoginObject GetData( ) { return (SecurityLoginObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Domain, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertSecurityLogin( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateSecurityLogin( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteSecurityLogin( dataObject );
        }
    }
    public class SecurityRoleUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public SecurityRoleUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] SecurityRoleObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        SecurityRoleObject GetData( ) { return (SecurityRoleObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Domain, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertSecurityRole( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateSecurityRole( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteSecurityRole( dataObject );
        }
    }
    public class SecurityIdentifierRoleLinkUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public SecurityIdentifierRoleLinkUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] SecurityIdentifierRoleLinkObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        SecurityIdentifierRoleLinkObject GetData( ) { return (SecurityIdentifierRoleLinkObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Member, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Role, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertSecurityIdentifierRoleLink( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateSecurityIdentifierRoleLink( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteSecurityIdentifierRoleLink( dataObject );
        }
    }
    public class SecurityLoginSessionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public SecurityLoginSessionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] SecurityLoginSessionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        SecurityLoginSessionObject GetData( ) { return (SecurityLoginSessionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Login, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertSecurityLoginSession( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateSecurityLoginSession( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteSecurityLoginSession( dataObject );
        }
    }
    public class SecurityPermissionUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public SecurityPermissionUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] SecurityPermissionObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        SecurityPermissionObject GetData( ) { return (SecurityPermissionObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Identifier, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertSecurityPermission( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateSecurityPermission( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteSecurityPermission( dataObject );
        }
    }
    public class SingleTimeseriesValueUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public SingleTimeseriesValueUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] SingleTimeseriesValueObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        SingleTimeseriesValueObject GetData( ) { return (SingleTimeseriesValueObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Timeseries, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertSingleTimeseriesValue( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateSingleTimeseriesValue( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteSingleTimeseriesValue( dataObject );
        }
    }
    public class StringTimeseriesValueUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public StringTimeseriesValueUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] StringTimeseriesValueObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        StringTimeseriesValueObject GetData( ) { return (StringTimeseriesValueObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Timeseries, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertStringTimeseriesValue( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateStringTimeseriesValue( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteStringTimeseriesValue( dataObject );
        }
    }
    public class BinaryTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public BinaryTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] BinaryTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        BinaryTimeseriesObject GetData( ) { return (BinaryTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertBinaryTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1BinaryTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateBinaryTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1BinaryTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2BinaryTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteBinaryTimeseries( dataObject );
        }
    }
    public class BooleanTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public BooleanTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] BooleanTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        BooleanTimeseriesObject GetData( ) { return (BooleanTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertBooleanTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1BooleanTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateBooleanTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1BooleanTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2BooleanTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteBooleanTimeseries( dataObject );
        }
    }
    public class AisAidToNavigationOffPositionTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisAidToNavigationOffPositionTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisAidToNavigationOffPositionTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisAidToNavigationOffPositionTimeseriesObject GetData( ) { return (AisAidToNavigationOffPositionTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.AidToNavigation is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisAidToNavigationOffPositionTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisAidToNavigationOffPositionTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisAidToNavigationOffPositionTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisAidToNavigationOffPositionTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisAidToNavigationOffPositionTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisAidToNavigationOffPositionTimeseries( dataObject );
        }
    }
    public class DeviceEnabledTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public DeviceEnabledTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] DeviceEnabledTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        DeviceEnabledTimeseriesObject GetData( ) { return (DeviceEnabledTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Device is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertDeviceEnabledTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1DeviceEnabledTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateDeviceEnabledTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1DeviceEnabledTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2DeviceEnabledTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteDeviceEnabledTimeseries( dataObject );
        }
    }
    public class RadarAutomaticSensitivityTimeControlTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarAutomaticSensitivityTimeControlTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarAutomaticSensitivityTimeControlTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarAutomaticSensitivityTimeControlTimeseriesObject GetData( ) { return (RadarAutomaticSensitivityTimeControlTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Radar is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarAutomaticSensitivityTimeControlTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarAutomaticSensitivityTimeControlTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarAutomaticSensitivityTimeControlTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarAutomaticSensitivityTimeControlTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarAutomaticSensitivityTimeControlTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarAutomaticSensitivityTimeControlTimeseries( dataObject );
        }
    }
    public class RadarBlankSector1TimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarBlankSector1TimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarBlankSector1TimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarBlankSector1TimeseriesObject GetData( ) { return (RadarBlankSector1TimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Radar is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarBlankSector1Timeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarBlankSector1Timeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarBlankSector1Timeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarBlankSector1Timeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarBlankSector1Timeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarBlankSector1Timeseries( dataObject );
        }
    }
    public class RadarBlankSector2TimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarBlankSector2TimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarBlankSector2TimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarBlankSector2TimeseriesObject GetData( ) { return (RadarBlankSector2TimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Radar is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarBlankSector2Timeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarBlankSector2Timeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarBlankSector2Timeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarBlankSector2Timeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarBlankSector2Timeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarBlankSector2Timeseries( dataObject );
        }
    }
    public class RadarEnableAutomaticFrequencyControlTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarEnableAutomaticFrequencyControlTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarEnableAutomaticFrequencyControlTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarEnableAutomaticFrequencyControlTimeseriesObject GetData( ) { return (RadarEnableAutomaticFrequencyControlTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Radar is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarEnableAutomaticFrequencyControlTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarEnableAutomaticFrequencyControlTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarEnableAutomaticFrequencyControlTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarEnableAutomaticFrequencyControlTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarEnableAutomaticFrequencyControlTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarEnableAutomaticFrequencyControlTimeseries( dataObject );
        }
    }
    public class RadarEnableFastTimeConstantTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarEnableFastTimeConstantTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarEnableFastTimeConstantTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarEnableFastTimeConstantTimeseriesObject GetData( ) { return (RadarEnableFastTimeConstantTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Radar is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarEnableFastTimeConstantTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarEnableFastTimeConstantTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarEnableFastTimeConstantTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarEnableFastTimeConstantTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarEnableFastTimeConstantTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarEnableFastTimeConstantTimeseries( dataObject );
        }
    }
    public class RadarEnableSensitivityTimeControlTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarEnableSensitivityTimeControlTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarEnableSensitivityTimeControlTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarEnableSensitivityTimeControlTimeseriesObject GetData( ) { return (RadarEnableSensitivityTimeControlTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Radar is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarEnableSensitivityTimeControlTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarEnableSensitivityTimeControlTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarEnableSensitivityTimeControlTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarEnableSensitivityTimeControlTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarEnableSensitivityTimeControlTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarEnableSensitivityTimeControlTimeseries( dataObject );
        }
    }
    public class RadarPowerOnTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarPowerOnTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarPowerOnTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarPowerOnTimeseriesObject GetData( ) { return (RadarPowerOnTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Radar is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarPowerOnTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarPowerOnTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarPowerOnTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarPowerOnTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarPowerOnTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarPowerOnTimeseries( dataObject );
        }
    }
    public class RadarSaveSettingsTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarSaveSettingsTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarSaveSettingsTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarSaveSettingsTimeseriesObject GetData( ) { return (RadarSaveSettingsTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Radar is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarSaveSettingsTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarSaveSettingsTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarSaveSettingsTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarSaveSettingsTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarSaveSettingsTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarSaveSettingsTimeseries( dataObject );
        }
    }
    public class RadarTrackingTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarTrackingTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarTrackingTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarTrackingTimeseriesObject GetData( ) { return (RadarTrackingTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Radar is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarTrackingTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarTrackingTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarTrackingTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarTrackingTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarTrackingTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarTrackingTimeseries( dataObject );
        }
    }
    public class MediaProxySessionEnabledTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public MediaProxySessionEnabledTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] MediaProxySessionEnabledTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        MediaProxySessionEnabledTimeseriesObject GetData( ) { return (MediaProxySessionEnabledTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.ProxySession is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertMediaProxySessionEnabledTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1MediaProxySessionEnabledTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateMediaProxySessionEnabledTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1MediaProxySessionEnabledTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2MediaProxySessionEnabledTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteMediaProxySessionEnabledTimeseries( dataObject );
        }
    }
    public class MediaServiceEnabledTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public MediaServiceEnabledTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] MediaServiceEnabledTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        MediaServiceEnabledTimeseriesObject GetData( ) { return (MediaServiceEnabledTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Service is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertMediaServiceEnabledTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1MediaServiceEnabledTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateMediaServiceEnabledTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1MediaServiceEnabledTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2MediaServiceEnabledTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteMediaServiceEnabledTimeseries( dataObject );
        }
    }
    public class ByteTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public ByteTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] ByteTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        ByteTimeseriesObject GetData( ) { return (ByteTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertByteTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1ByteTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateByteTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1ByteTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2ByteTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteByteTimeseries( dataObject );
        }
    }
    public class DateTimeTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public DateTimeTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] DateTimeTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        DateTimeTimeseriesObject GetData( ) { return (DateTimeTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertDateTimeTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1DateTimeTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateDateTimeTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1DateTimeTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2DateTimeTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteDateTimeTimeseries( dataObject );
        }
    }
    public class DoubleTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public DoubleTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] DoubleTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        DoubleTimeseriesObject GetData( ) { return (DoubleTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertDoubleTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1DoubleTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateDoubleTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1DoubleTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2DoubleTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteDoubleTimeseries( dataObject );
        }
    }
    public class GNSSAltitudeTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GNSSAltitudeTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GNSSAltitudeTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GNSSAltitudeTimeseriesObject GetData( ) { return (GNSSAltitudeTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.GNSSDevice is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGNSSAltitudeTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1GNSSAltitudeTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGNSSAltitudeTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1GNSSAltitudeTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2GNSSAltitudeTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGNSSAltitudeTimeseries( dataObject );
        }
    }
    public class GNSSLatitudeTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GNSSLatitudeTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GNSSLatitudeTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GNSSLatitudeTimeseriesObject GetData( ) { return (GNSSLatitudeTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.GNSSDevice is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGNSSLatitudeTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1GNSSLatitudeTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGNSSLatitudeTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1GNSSLatitudeTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2GNSSLatitudeTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGNSSLatitudeTimeseries( dataObject );
        }
    }
    public class GNSSLongitudeTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GNSSLongitudeTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GNSSLongitudeTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GNSSLongitudeTimeseriesObject GetData( ) { return (GNSSLongitudeTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.GNSSDevice is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGNSSLongitudeTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1GNSSLongitudeTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGNSSLongitudeTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1GNSSLongitudeTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2GNSSLongitudeTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGNSSLongitudeTimeseries( dataObject );
        }
    }
    public class GyroCourseTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GyroCourseTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GyroCourseTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GyroCourseTimeseriesObject GetData( ) { return (GyroCourseTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.GyroDevice is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGyroCourseTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1GyroCourseTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGyroCourseTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1GyroCourseTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2GyroCourseTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGyroCourseTimeseries( dataObject );
        }
    }
    public class GyroHeadingMagneticNorthTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GyroHeadingMagneticNorthTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GyroHeadingMagneticNorthTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GyroHeadingMagneticNorthTimeseriesObject GetData( ) { return (GyroHeadingMagneticNorthTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.GyroDevice is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGyroHeadingMagneticNorthTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1GyroHeadingMagneticNorthTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGyroHeadingMagneticNorthTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1GyroHeadingMagneticNorthTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2GyroHeadingMagneticNorthTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGyroHeadingMagneticNorthTimeseries( dataObject );
        }
    }
    public class GyroHeadingTrueNorthTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GyroHeadingTrueNorthTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GyroHeadingTrueNorthTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GyroHeadingTrueNorthTimeseriesObject GetData( ) { return (GyroHeadingTrueNorthTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.GyroDevice is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGyroHeadingTrueNorthTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1GyroHeadingTrueNorthTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGyroHeadingTrueNorthTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1GyroHeadingTrueNorthTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2GyroHeadingTrueNorthTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGyroHeadingTrueNorthTimeseries( dataObject );
        }
    }
    public class GyroPitchTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GyroPitchTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GyroPitchTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GyroPitchTimeseriesObject GetData( ) { return (GyroPitchTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.GyroDevice is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGyroPitchTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1GyroPitchTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGyroPitchTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1GyroPitchTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2GyroPitchTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGyroPitchTimeseries( dataObject );
        }
    }
    public class GyroRateOfTurnTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GyroRateOfTurnTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GyroRateOfTurnTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GyroRateOfTurnTimeseriesObject GetData( ) { return (GyroRateOfTurnTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.GyroDevice is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGyroRateOfTurnTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1GyroRateOfTurnTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGyroRateOfTurnTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1GyroRateOfTurnTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2GyroRateOfTurnTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGyroRateOfTurnTimeseries( dataObject );
        }
    }
    public class GyroRollTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GyroRollTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GyroRollTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GyroRollTimeseriesObject GetData( ) { return (GyroRollTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.GyroDevice is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGyroRollTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1GyroRollTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGyroRollTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1GyroRollTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2GyroRollTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGyroRollTimeseries( dataObject );
        }
    }
    public class GyroSpeedTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GyroSpeedTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GyroSpeedTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GyroSpeedTimeseriesObject GetData( ) { return (GyroSpeedTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.GyroDevice is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGyroSpeedTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1GyroSpeedTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGyroSpeedTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1GyroSpeedTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2GyroSpeedTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGyroSpeedTimeseries( dataObject );
        }
    }
    public class RadarLatitudeTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarLatitudeTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarLatitudeTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarLatitudeTimeseriesObject GetData( ) { return (RadarLatitudeTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Radar is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarLatitudeTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarLatitudeTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarLatitudeTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarLatitudeTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarLatitudeTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarLatitudeTimeseries( dataObject );
        }
    }
    public class RadarLongitudeTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarLongitudeTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarLongitudeTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarLongitudeTimeseriesObject GetData( ) { return (RadarLongitudeTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Radar is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarLongitudeTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarLongitudeTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarLongitudeTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarLongitudeTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarLongitudeTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarLongitudeTimeseries( dataObject );
        }
    }
    public class RadomeDewPointTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadomeDewPointTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadomeDewPointTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadomeDewPointTimeseriesObject GetData( ) { return (RadomeDewPointTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Radome is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadomeDewPointTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadomeDewPointTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadomeDewPointTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadomeDewPointTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadomeDewPointTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadomeDewPointTimeseries( dataObject );
        }
    }
    public class RadomePressureTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadomePressureTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadomePressureTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadomePressureTimeseriesObject GetData( ) { return (RadomePressureTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Radome is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadomePressureTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadomePressureTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadomePressureTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadomePressureTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadomePressureTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadomePressureTimeseries( dataObject );
        }
    }
    public class RadomeTemperatureTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadomeTemperatureTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadomeTemperatureTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadomeTemperatureTimeseriesObject GetData( ) { return (RadomeTemperatureTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Radome is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadomeTemperatureTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadomeTemperatureTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadomeTemperatureTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadomeTemperatureTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadomeTemperatureTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadomeTemperatureTimeseries( dataObject );
        }
    }
    public class VesselDraughtTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public VesselDraughtTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] VesselDraughtTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        VesselDraughtTimeseriesObject GetData( ) { return (VesselDraughtTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Vessel is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertVesselDraughtTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1VesselDraughtTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateVesselDraughtTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1VesselDraughtTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2VesselDraughtTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteVesselDraughtTimeseries( dataObject );
        }
    }
    public class ViewLatitudeTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public ViewLatitudeTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] ViewLatitudeTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        ViewLatitudeTimeseriesObject GetData( ) { return (ViewLatitudeTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.View is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertViewLatitudeTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1ViewLatitudeTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateViewLatitudeTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1ViewLatitudeTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2ViewLatitudeTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteViewLatitudeTimeseries( dataObject );
        }
    }
    public class ViewLongitudeTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public ViewLongitudeTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] ViewLongitudeTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        ViewLongitudeTimeseriesObject GetData( ) { return (ViewLongitudeTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.View is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertViewLongitudeTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1ViewLongitudeTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateViewLongitudeTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1ViewLongitudeTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2ViewLongitudeTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteViewLongitudeTimeseries( dataObject );
        }
    }
    public class ViewZoomLevelTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public ViewZoomLevelTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] ViewZoomLevelTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        ViewZoomLevelTimeseriesObject GetData( ) { return (ViewZoomLevelTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.View is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertViewZoomLevelTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1ViewZoomLevelTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateViewZoomLevelTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1ViewZoomLevelTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2ViewZoomLevelTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteViewZoomLevelTimeseries( dataObject );
        }
    }
    public class WeatherStationAbsoluteHumidityTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public WeatherStationAbsoluteHumidityTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] WeatherStationAbsoluteHumidityTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        WeatherStationAbsoluteHumidityTimeseriesObject GetData( ) { return (WeatherStationAbsoluteHumidityTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.WeatherStation is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertWeatherStationAbsoluteHumidityTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1WeatherStationAbsoluteHumidityTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateWeatherStationAbsoluteHumidityTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1WeatherStationAbsoluteHumidityTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2WeatherStationAbsoluteHumidityTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteWeatherStationAbsoluteHumidityTimeseries( dataObject );
        }
    }
    public class WeatherStationAirTemperatureTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public WeatherStationAirTemperatureTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] WeatherStationAirTemperatureTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        WeatherStationAirTemperatureTimeseriesObject GetData( ) { return (WeatherStationAirTemperatureTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.WeatherStation is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertWeatherStationAirTemperatureTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1WeatherStationAirTemperatureTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateWeatherStationAirTemperatureTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1WeatherStationAirTemperatureTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2WeatherStationAirTemperatureTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteWeatherStationAirTemperatureTimeseries( dataObject );
        }
    }
    public class WeatherStationBarometricPressureTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public WeatherStationBarometricPressureTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] WeatherStationBarometricPressureTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        WeatherStationBarometricPressureTimeseriesObject GetData( ) { return (WeatherStationBarometricPressureTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.WeatherStation is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertWeatherStationBarometricPressureTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1WeatherStationBarometricPressureTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateWeatherStationBarometricPressureTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1WeatherStationBarometricPressureTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2WeatherStationBarometricPressureTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteWeatherStationBarometricPressureTimeseries( dataObject );
        }
    }
    public class WeatherStationDewPointTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public WeatherStationDewPointTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] WeatherStationDewPointTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        WeatherStationDewPointTimeseriesObject GetData( ) { return (WeatherStationDewPointTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.WeatherStation is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertWeatherStationDewPointTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1WeatherStationDewPointTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateWeatherStationDewPointTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1WeatherStationDewPointTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2WeatherStationDewPointTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteWeatherStationDewPointTimeseries( dataObject );
        }
    }
    public class WeatherStationRelativeHumidityTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public WeatherStationRelativeHumidityTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] WeatherStationRelativeHumidityTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        WeatherStationRelativeHumidityTimeseriesObject GetData( ) { return (WeatherStationRelativeHumidityTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.WeatherStation is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertWeatherStationRelativeHumidityTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1WeatherStationRelativeHumidityTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateWeatherStationRelativeHumidityTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1WeatherStationRelativeHumidityTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2WeatherStationRelativeHumidityTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteWeatherStationRelativeHumidityTimeseries( dataObject );
        }
    }
    public class WeatherStationWaterTemperatureTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public WeatherStationWaterTemperatureTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] WeatherStationWaterTemperatureTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        WeatherStationWaterTemperatureTimeseriesObject GetData( ) { return (WeatherStationWaterTemperatureTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.WeatherStation is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertWeatherStationWaterTemperatureTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1WeatherStationWaterTemperatureTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateWeatherStationWaterTemperatureTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1WeatherStationWaterTemperatureTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2WeatherStationWaterTemperatureTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteWeatherStationWaterTemperatureTimeseries( dataObject );
        }
    }
    public class WeatherStationWindDirectionTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public WeatherStationWindDirectionTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] WeatherStationWindDirectionTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        WeatherStationWindDirectionTimeseriesObject GetData( ) { return (WeatherStationWindDirectionTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.WeatherStation is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertWeatherStationWindDirectionTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1WeatherStationWindDirectionTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateWeatherStationWindDirectionTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1WeatherStationWindDirectionTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2WeatherStationWindDirectionTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteWeatherStationWindDirectionTimeseries( dataObject );
        }
    }
    public class WeatherStationWindSpeedTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public WeatherStationWindSpeedTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] WeatherStationWindSpeedTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        WeatherStationWindSpeedTimeseriesObject GetData( ) { return (WeatherStationWindSpeedTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.WeatherStation is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertWeatherStationWindSpeedTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1WeatherStationWindSpeedTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateWeatherStationWindSpeedTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1WeatherStationWindSpeedTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2WeatherStationWindSpeedTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteWeatherStationWindSpeedTimeseries( dataObject );
        }
    }
    public class GeoPosition2DTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GeoPosition2DTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GeoPosition2DTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GeoPosition2DTimeseriesObject GetData( ) { return (GeoPosition2DTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGeoPosition2DTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1GeoPosition2DTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGeoPosition2DTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1GeoPosition2DTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2GeoPosition2DTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGeoPosition2DTimeseries( dataObject );
        }
    }
    public class AisAidToNavigationPositionTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public AisAidToNavigationPositionTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] AisAidToNavigationPositionTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        AisAidToNavigationPositionTimeseriesObject GetData( ) { return (AisAidToNavigationPositionTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.AidToNavigation is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertAisAidToNavigationPositionTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1AisAidToNavigationPositionTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateAisAidToNavigationPositionTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1AisAidToNavigationPositionTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2AisAidToNavigationPositionTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteAisAidToNavigationPositionTimeseries( dataObject );
        }
    }
    public class GeoPosition3DTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GeoPosition3DTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GeoPosition3DTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GeoPosition3DTimeseriesObject GetData( ) { return (GeoPosition3DTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGeoPosition3DTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1GeoPosition3DTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGeoPosition3DTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1GeoPosition3DTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2GeoPosition3DTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGeoPosition3DTimeseries( dataObject );
        }
    }
    public class GuidTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public GuidTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] GuidTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        GuidTimeseriesObject GetData( ) { return (GuidTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertGuidTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1GuidTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateGuidTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1GuidTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2GuidTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteGuidTimeseries( dataObject );
        }
    }
    public class Int16TimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public Int16TimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] Int16TimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        Int16TimeseriesObject GetData( ) { return (Int16TimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertInt16Timeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1Int16Timeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateInt16Timeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1Int16Timeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2Int16Timeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteInt16Timeseries( dataObject );
        }
    }
    public class Int32TimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public Int32TimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] Int32TimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        Int32TimeseriesObject GetData( ) { return (Int32TimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertInt32Timeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1Int32Timeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateInt32Timeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1Int32Timeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2Int32Timeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteInt32Timeseries( dataObject );
        }
    }
    public class RadarAzimuthOffsetTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarAzimuthOffsetTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarAzimuthOffsetTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarAzimuthOffsetTimeseriesObject GetData( ) { return (RadarAzimuthOffsetTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Radar is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarAzimuthOffsetTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarAzimuthOffsetTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarAzimuthOffsetTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarAzimuthOffsetTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarAzimuthOffsetTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarAzimuthOffsetTimeseries( dataObject );
        }
    }
    public class RadarFastTimeConstantLevelTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarFastTimeConstantLevelTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarFastTimeConstantLevelTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarFastTimeConstantLevelTimeseriesObject GetData( ) { return (RadarFastTimeConstantLevelTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Radar is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarFastTimeConstantLevelTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarFastTimeConstantLevelTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarFastTimeConstantLevelTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarFastTimeConstantLevelTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarFastTimeConstantLevelTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarFastTimeConstantLevelTimeseries( dataObject );
        }
    }
    public class RadarFastTimeConstantModeTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarFastTimeConstantModeTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarFastTimeConstantModeTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarFastTimeConstantModeTimeseriesObject GetData( ) { return (RadarFastTimeConstantModeTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Radar is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarFastTimeConstantModeTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarFastTimeConstantModeTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarFastTimeConstantModeTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarFastTimeConstantModeTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarFastTimeConstantModeTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarFastTimeConstantModeTimeseries( dataObject );
        }
    }
    public class RadarPulseTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarPulseTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarPulseTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarPulseTimeseriesObject GetData( ) { return (RadarPulseTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Radar is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarPulseTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarPulseTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarPulseTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarPulseTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarPulseTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarPulseTimeseries( dataObject );
        }
    }
    public class RadarSector1EndTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarSector1EndTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarSector1EndTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarSector1EndTimeseriesObject GetData( ) { return (RadarSector1EndTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Radar is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarSector1EndTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarSector1EndTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarSector1EndTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarSector1EndTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarSector1EndTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarSector1EndTimeseries( dataObject );
        }
    }
    public class RadarSector1StartTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarSector1StartTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarSector1StartTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarSector1StartTimeseriesObject GetData( ) { return (RadarSector1StartTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Radar is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarSector1StartTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarSector1StartTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarSector1StartTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarSector1StartTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarSector1StartTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarSector1StartTimeseries( dataObject );
        }
    }
    public class RadarSector2EndTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarSector2EndTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarSector2EndTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarSector2EndTimeseriesObject GetData( ) { return (RadarSector2EndTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Radar is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarSector2EndTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarSector2EndTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarSector2EndTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarSector2EndTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarSector2EndTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarSector2EndTimeseries( dataObject );
        }
    }
    public class RadarSector2StartTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarSector2StartTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarSector2StartTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarSector2StartTimeseriesObject GetData( ) { return (RadarSector2StartTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Radar is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarSector2StartTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarSector2StartTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarSector2StartTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarSector2StartTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarSector2StartTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarSector2StartTimeseries( dataObject );
        }
    }
    public class RadarSensitivityTimeControlLevelTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarSensitivityTimeControlLevelTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarSensitivityTimeControlLevelTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarSensitivityTimeControlLevelTimeseriesObject GetData( ) { return (RadarSensitivityTimeControlLevelTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Radar is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarSensitivityTimeControlLevelTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarSensitivityTimeControlLevelTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarSensitivityTimeControlLevelTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarSensitivityTimeControlLevelTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarSensitivityTimeControlLevelTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarSensitivityTimeControlLevelTimeseries( dataObject );
        }
    }
    public class RadarTuningTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadarTuningTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadarTuningTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadarTuningTimeseriesObject GetData( ) { return (RadarTuningTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Radar is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadarTuningTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadarTuningTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadarTuningTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadarTuningTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadarTuningTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadarTuningTimeseries( dataObject );
        }
    }
    public class VesselPersonsOnBoardTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public VesselPersonsOnBoardTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] VesselPersonsOnBoardTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        VesselPersonsOnBoardTimeseriesObject GetData( ) { return (VesselPersonsOnBoardTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Vessel is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertVesselPersonsOnBoardTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1VesselPersonsOnBoardTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateVesselPersonsOnBoardTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1VesselPersonsOnBoardTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2VesselPersonsOnBoardTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteVesselPersonsOnBoardTimeseries( dataObject );
        }
    }
    public class Int64TimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public Int64TimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] Int64TimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        Int64TimeseriesObject GetData( ) { return (Int64TimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertInt64Timeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1Int64Timeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateInt64Timeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1Int64Timeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2Int64Timeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteInt64Timeseries( dataObject );
        }
    }
    public class Position2DTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public Position2DTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] Position2DTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        Position2DTimeseriesObject GetData( ) { return (Position2DTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertPosition2DTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1Position2DTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdatePosition2DTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1Position2DTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2Position2DTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeletePosition2DTimeseries( dataObject );
        }
    }
    public class Position3DTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public Position3DTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] Position3DTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        Position3DTimeseriesObject GetData( ) { return (Position3DTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertPosition3DTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1Position3DTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdatePosition3DTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1Position3DTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2Position3DTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeletePosition3DTimeseries( dataObject );
        }
    }
    public class ReferenceTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public ReferenceTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] ReferenceTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        ReferenceTimeseriesObject GetData( ) { return (ReferenceTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertReferenceTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1ReferenceTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateReferenceTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1ReferenceTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2ReferenceTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteReferenceTimeseries( dataObject );
        }
    }
    public class SByteTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public SByteTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] SByteTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        SByteTimeseriesObject GetData( ) { return (SByteTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertSByteTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1SByteTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateSByteTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1SByteTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2SByteTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteSByteTimeseries( dataObject );
        }
    }
    public class SingleTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public SingleTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] SingleTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        SingleTimeseriesObject GetData( ) { return (SingleTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertSingleTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1SingleTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateSingleTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1SingleTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2SingleTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteSingleTimeseries( dataObject );
        }
    }
    public class StringTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public StringTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] StringTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        StringTimeseriesObject GetData( ) { return (StringTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertStringTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1StringTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateStringTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1StringTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2StringTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteStringTimeseries( dataObject );
        }
    }
    public class TimeSpanTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public TimeSpanTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] TimeSpanTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        TimeSpanTimeseriesObject GetData( ) { return (TimeSpanTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertTimeSpanTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1TimeSpanTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateTimeSpanTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1TimeSpanTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2TimeSpanTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteTimeSpanTimeseries( dataObject );
        }
    }
    public class UInt16TimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public UInt16TimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] UInt16TimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        UInt16TimeseriesObject GetData( ) { return (UInt16TimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertUInt16Timeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1UInt16Timeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateUInt16Timeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1UInt16Timeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2UInt16Timeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteUInt16Timeseries( dataObject );
        }
    }
    public class UInt32TimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public UInt32TimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] UInt32TimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        UInt32TimeseriesObject GetData( ) { return (UInt32TimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertUInt32Timeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1UInt32Timeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateUInt32Timeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1UInt32Timeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2UInt32Timeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteUInt32Timeseries( dataObject );
        }
    }
    public class RadomeStatusTimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public RadomeStatusTimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] RadomeStatusTimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        RadomeStatusTimeseriesObject GetData( ) { return (RadomeStatusTimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }
            if( dataObject.Radome is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertRadomeStatusTimeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1RadomeStatusTimeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateRadomeStatusTimeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1RadomeStatusTimeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2RadomeStatusTimeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteRadomeStatusTimeseries( dataObject );
        }
    }
    public class UInt64TimeseriesUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public UInt64TimeseriesUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] UInt64TimeseriesObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        UInt64TimeseriesObject GetData( ) { return (UInt64TimeseriesObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertUInt64Timeseries( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1UInt64Timeseries( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateUInt64Timeseries( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1UInt64Timeseries( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2UInt64Timeseries( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteUInt64Timeseries( dataObject );
        }
    }
    public class TimeseriesCatalogUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public TimeseriesCatalogUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] TimeseriesCatalogObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        TimeseriesCatalogObject GetData( ) { return (TimeseriesCatalogObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.Catalog is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        AddDependency( otherNode1 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertTimeseriesCatalog( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1TimeseriesCatalog( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateTimeseriesCatalog( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1TimeseriesCatalog( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2TimeseriesCatalog( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteTimeseriesCatalog( dataObject );
        }
    }
    public class TimeseriesInfoUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public TimeseriesInfoUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] TimeseriesInfoObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        TimeseriesInfoObject GetData( ) { return (TimeseriesInfoObject)_GetData( ); }

        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertTimeseriesInfo( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateTimeseriesInfo( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteTimeseriesInfo( dataObject );
        }
    }
    public class TimeSpanTimeseriesValueUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public TimeSpanTimeseriesValueUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] TimeSpanTimeseriesValueObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        TimeSpanTimeseriesValueObject GetData( ) { return (TimeSpanTimeseriesValueObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Timeseries, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertTimeSpanTimeseriesValue( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateTimeSpanTimeseriesValue( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteTimeSpanTimeseriesValue( dataObject );
        }
    }
    public class TrackableItemTrackLinkUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public TrackableItemTrackLinkUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] TrackableItemTrackLinkObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        TrackableItemTrackLinkObject GetData( ) { return (TrackableItemTrackLinkObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Item, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Track, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertTrackableItemTrackLink( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateTrackableItemTrackLink( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteTrackableItemTrackLink( dataObject );
        }
    }
    public class TrackUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public TrackUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] TrackObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        TrackObject GetData( ) { return (TrackObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Tracker, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertTrack( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateTrack( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteTrack( dataObject );
        }
    }
    public class Track3DUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public Track3DUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] Track3DObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        Track3DObject GetData( ) { return (Track3DObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Tracker, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertTrack3D( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateTrack3D( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteTrack3D( dataObject );
        }
    }
    public class TrackerFilterParametersUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public TrackerFilterParametersUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] TrackerFilterParametersObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        TrackerFilterParametersObject GetData( ) { return (TrackerFilterParametersObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Tracker, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertTrackerFilterParameters( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateTrackerFilterParameters( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteTrackerFilterParameters( dataObject );
        }
    }
    public class TrackerFilterParametersConfigurationUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public TrackerFilterParametersConfigurationUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] TrackerFilterParametersConfigurationObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        TrackerFilterParametersConfigurationObject GetData( ) { return (TrackerFilterParametersConfigurationObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Parameters, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertTrackerFilterParametersConfiguration( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateTrackerFilterParametersConfiguration( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteTrackerFilterParametersConfiguration( dataObject );
        }
    }
    public class TrackInfoUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public TrackInfoUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] TrackInfoObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        TrackInfoObject GetData( ) { return (TrackInfoObject)_GetData( ); }

        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertTrackInfo( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateTrackInfo( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteTrackInfo( dataObject );
        }
    }
    public class TrackingServiceOptionsUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public TrackingServiceOptionsUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] TrackingServiceOptionsObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        TrackingServiceOptionsObject GetData( ) { return (TrackingServiceOptionsObject)_GetData( ); }

        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertTrackingServiceOptions( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateTrackingServiceOptions( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteTrackingServiceOptions( dataObject );
        }
    }
    public class TrackLinkUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public TrackLinkUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] TrackLinkObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        TrackLinkObject GetData( ) { return (TrackLinkObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Primary, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Secondary, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertTrackLink( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateTrackLink( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteTrackLink( dataObject );
        }
    }
    public class TrackValueUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public TrackValueUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] TrackValueObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        TrackValueObject GetData( ) { return (TrackValueObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Track, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertTrackValue( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateTrackValue( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteTrackValue( dataObject );
        }
    }
    public class TrackValue3DUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public TrackValue3DUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] TrackValue3DObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        TrackValue3DObject GetData( ) { return (TrackValue3DObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Track, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertTrackValue3D( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateTrackValue3D( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteTrackValue3D( dataObject );
        }
    }
    public class UInt16TimeseriesValueUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public UInt16TimeseriesValueUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] UInt16TimeseriesValueObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        UInt16TimeseriesValueObject GetData( ) { return (UInt16TimeseriesValueObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Timeseries, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertUInt16TimeseriesValue( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateUInt16TimeseriesValue( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteUInt16TimeseriesValue( dataObject );
        }
    }
    public class UInt32TimeseriesValueUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public UInt32TimeseriesValueUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] UInt32TimeseriesValueObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        UInt32TimeseriesValueObject GetData( ) { return (UInt32TimeseriesValueObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Timeseries, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertUInt32TimeseriesValue( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateUInt32TimeseriesValue( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteUInt32TimeseriesValue( dataObject );
        }
    }
    public class UInt64TimeseriesValueUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public UInt64TimeseriesValueUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] UInt64TimeseriesValueObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        UInt64TimeseriesValueObject GetData( ) { return (UInt64TimeseriesValueObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Timeseries, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertUInt64TimeseriesValue( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateUInt64TimeseriesValue( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteUInt64TimeseriesValue( dataObject );
        }
    }
    public class VehicleTypeUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public VehicleTypeUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] VehicleTypeObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        VehicleTypeObject GetData( ) { return (VehicleTypeObject)_GetData( ); }

        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertVehicleType( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateVehicleType( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteVehicleType( dataObject );
        }
    }
    public class VesselTypeUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public VesselTypeUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] VesselTypeObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        VesselTypeObject GetData( ) { return (VesselTypeObject)_GetData( ); }

        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertVesselType( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateVesselType( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteVesselType( dataObject );
        }
    }
    public class ViewUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public ViewUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] ViewObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        ViewObject GetData( ) { return (ViewObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( dataObject.LatitudeTimeseries is Guid referencedId1 )
            {
                if( updateNodes.TryGetValue( referencedId1, out var otherNode1 ) )
                {
                    if( otherNode1.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.LongitudeTimeseries is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }
            if( dataObject.ZoomLevelTimeseries is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertView( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1View( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateView( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1View( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2View( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteView( dataObject );
        }
    }
    public class ViewCameraLinkUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public ViewCameraLinkUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] ViewCameraLinkObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        ViewCameraLinkObject GetData( ) { return (ViewCameraLinkObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.View, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Camera, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertViewCameraLink( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateViewCameraLink( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteViewCameraLink( dataObject );
        }
    }
    public class ViewTrackerLinkUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public ViewTrackerLinkUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] ViewTrackerLinkObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        ViewTrackerLinkObject GetData( ) { return (ViewTrackerLinkObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.View, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Tracker, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertViewTrackerLink( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateViewTrackerLink( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteViewTrackerLink( dataObject );
        }
    }
    public class WeatherStationCommandUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public WeatherStationCommandUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] WeatherStationCommandObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        WeatherStationCommandObject GetData( ) { return (WeatherStationCommandObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.WeatherStation, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Reply is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertWeatherStationCommand( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1WeatherStationCommand( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateWeatherStationCommand( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1WeatherStationCommand( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2WeatherStationCommand( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteWeatherStationCommand( dataObject );
        }
    }
    public class WeatherStationCommandReplyUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public WeatherStationCommandReplyUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] WeatherStationCommandReplyObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        WeatherStationCommandReplyObject GetData( ) { return (WeatherStationCommandReplyObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.WeatherStation, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( dataObject.Command is Guid referencedId2 )
            {
                if( updateNodes.TryGetValue( referencedId2, out var otherNode2 ) )
                {
                    if( otherNode2.IsNew )
                    {
                        RequiresUpdate2 = true;
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertWeatherStationCommandReply( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1WeatherStationCommandReply( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateWeatherStationCommandReply( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1WeatherStationCommandReply( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2WeatherStationCommandReply( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteWeatherStationCommandReply( dataObject );
        }
    }
    public class WeatherStationConfigurationUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public WeatherStationConfigurationUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] WeatherStationConfigurationObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        WeatherStationConfigurationObject GetData( ) { return (WeatherStationConfigurationObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.WeatherStation, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertWeatherStationConfiguration( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateWeatherStationConfiguration( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteWeatherStationConfiguration( dataObject );
        }
    }
    public class CircularZoneUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public CircularZoneUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] CircularZoneObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        CircularZoneObject GetData( ) { return (CircularZoneObject)_GetData( ); }

        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertCircularZone( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateCircularZone( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteCircularZone( dataObject );
        }
    }
    public class PolygonZoneUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public PolygonZoneUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] PolygonZoneObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        PolygonZoneObject GetData( ) { return (PolygonZoneObject)_GetData( ); }

        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertPolygonZone( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdatePolygonZone( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeletePolygonZone( dataObject );
        }
    }
    public class ZoneExceptionsUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public ZoneExceptionsUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] ZoneExceptionsObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        ZoneExceptionsObject GetData( ) { return (ZoneExceptionsObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Zone, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertZoneExceptions( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateZoneExceptions( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteZoneExceptions( dataObject );
        }
    }
    public class ZoneExceptionsVesselLinkUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public ZoneExceptionsVesselLinkUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] ZoneExceptionsVesselLinkObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        ZoneExceptionsVesselLinkObject GetData( ) { return (ZoneExceptionsVesselLinkObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.ZoneExceptions, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Vessel, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertZoneExceptionsVesselLink( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateZoneExceptionsVesselLink( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteZoneExceptionsVesselLink( dataObject );
        }
    }
    public class ZoneTrackAlarmUpdateNode : SqlServerUpdateNodeBase<Kind>
    {
        public ZoneTrackAlarmUpdateNode( [DisallowNull] SqlServerUpdateHandler updateHandler, [DisallowNull] ZoneTrackAlarmObject dataObject )
            : base(updateHandler, dataObject)
        {
        }

        StoredProcedures StoredProcedures => (StoredProcedures)Handler.StoredProcedures;

        ZoneTrackAlarmObject GetData( ) { return (ZoneTrackAlarmObject)_GetData( ); }

        public override void CollectDependencies( )
        {
            var dataObject = GetData( );
            var updateNodes = UpdateNodes;
            if( updateNodes.TryGetValue( dataObject.Track, out var otherNode1 ) )
            {
                if( otherNode1.IsNew )
                {
                    AddDependency( otherNode1 );
                }
            }
            if( updateNodes.TryGetValue( dataObject.Zone, out var otherNode2 ) )
            {
                if( otherNode2.IsNew )
                {
                    AddDependency( otherNode2 );
                }
            }
            if( dataObject.RadarTrack is Guid referencedId3 )
            {
                if( updateNodes.TryGetValue( referencedId3, out var otherNode3 ) )
                {
                    if( otherNode3.IsNew )
                    {
                        AddDependency( otherNode3 );
                    }
                }
            }

        }
        public override void Insert( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.InsertZoneTrackAlarm( dataObject );
        }
        public override void Insert1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Insert1ZoneTrackAlarm( dataObject );
        }
        public override void Update( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.UpdateZoneTrackAlarm( dataObject );
        }
        public override void Update1( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update1ZoneTrackAlarm( dataObject );
        }
        public override void Update2( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.Update2ZoneTrackAlarm( dataObject );
        }
        public override void Delete( )
        {
            var storedProcedures = StoredProcedures;
            var dataObject = GetData( );
            storedProcedures.DeleteZoneTrackAlarm( dataObject );
        }
    }
    public class SqlServerUpdateNodeFactory : IUpdateNodeFactory<Kind>
    {
        public SqlServerUpdateNodeFactory()
        {
        }
        public SqlServerUpdateNodeBase<Kind> Create([DisallowNull] SqlServerUpdateHandlerBase<Kind> updateHandlerBase, [DisallowNull] BaseDataGuid<Kind> data)
        {
            var updateHandler = (SqlServerUpdateHandler)updateHandlerBase;
            var kind = data.GetObjectType();
            switch (kind)
            {
                case Kind.AircraftType:
                {
                    return new AircraftTypeUpdateNode( updateHandler, (AircraftTypeObject)data );
                }
                case Kind.AisDeviceCommand:
                {
                    return new AisDeviceCommandUpdateNode( updateHandler, (AisDeviceCommandObject)data );
                }
                case Kind.AisDeviceCommandReply:
                {
                    return new AisDeviceCommandReplyUpdateNode( updateHandler, (AisDeviceCommandReplyObject)data );
                }
                case Kind.AisDeviceConfiguration:
                {
                    return new AisDeviceConfigurationUpdateNode( updateHandler, (AisDeviceConfigurationObject)data );
                }
                case Kind.AisDeviceRawMessage:
                {
                    return new AisDeviceRawMessageUpdateNode( updateHandler, (AisDeviceRawMessageObject)data );
                }
                case Kind.AisDeviceRawSentence:
                {
                    return new AisDeviceRawSentenceUpdateNode( updateHandler, (AisDeviceRawSentenceObject)data );
                }
                case Kind.AidToNavigationReportMessage:
                {
                    return new AidToNavigationReportMessageUpdateNode( updateHandler, (AidToNavigationReportMessageObject)data );
                }
                case Kind.AisAddressedSafetyRelatedMessage:
                {
                    return new AisAddressedSafetyRelatedMessageUpdateNode( updateHandler, (AisAddressedSafetyRelatedMessageObject)data );
                }
                case Kind.AisBaseStationReportMessage:
                {
                    return new AisBaseStationReportMessageUpdateNode( updateHandler, (AisBaseStationReportMessageObject)data );
                }
                case Kind.AisBinaryAcknowledgeMessage:
                {
                    return new AisBinaryAcknowledgeMessageUpdateNode( updateHandler, (AisBinaryAcknowledgeMessageObject)data );
                }
                case Kind.AisBinaryAddressedMessage:
                {
                    return new AisBinaryAddressedMessageUpdateNode( updateHandler, (AisBinaryAddressedMessageObject)data );
                }
                case Kind.AisBinaryBroadcastMessage:
                {
                    return new AisBinaryBroadcastMessageUpdateNode( updateHandler, (AisBinaryBroadcastMessageObject)data );
                }
                case Kind.AisDataLinkManagementMessage:
                {
                    return new AisDataLinkManagementMessageUpdateNode( updateHandler, (AisDataLinkManagementMessageObject)data );
                }
                case Kind.AisExtendedClassBCsPositionReportMessage:
                {
                    return new AisExtendedClassBCsPositionReportMessageUpdateNode( updateHandler, (AisExtendedClassBCsPositionReportMessageObject)data );
                }
                case Kind.AisInterrogationMessage:
                {
                    return new AisInterrogationMessageUpdateNode( updateHandler, (AisInterrogationMessageObject)data );
                }
                case Kind.AisPositionReportClassAAssignedScheduleMessage:
                {
                    return new AisPositionReportClassAAssignedScheduleMessageUpdateNode( updateHandler, (AisPositionReportClassAAssignedScheduleMessageObject)data );
                }
                case Kind.AisPositionReportClassAMessage:
                {
                    return new AisPositionReportClassAMessageUpdateNode( updateHandler, (AisPositionReportClassAMessageObject)data );
                }
                case Kind.AisPositionReportClassAResponseToInterrogationMessage:
                {
                    return new AisPositionReportClassAResponseToInterrogationMessageUpdateNode( updateHandler, (AisPositionReportClassAResponseToInterrogationMessageObject)data );
                }
                case Kind.AisPositionReportForLongRangeApplicationsMessage:
                {
                    return new AisPositionReportForLongRangeApplicationsMessageUpdateNode( updateHandler, (AisPositionReportForLongRangeApplicationsMessageObject)data );
                }
                case Kind.AisSafetyRelatedAcknowledgmentMessage:
                {
                    return new AisSafetyRelatedAcknowledgmentMessageUpdateNode( updateHandler, (AisSafetyRelatedAcknowledgmentMessageObject)data );
                }
                case Kind.AisStandardClassBCsPositionReportMessage:
                {
                    return new AisStandardClassBCsPositionReportMessageUpdateNode( updateHandler, (AisStandardClassBCsPositionReportMessageObject)data );
                }
                case Kind.AisStandardSarAircraftPositionReportMessage:
                {
                    return new AisStandardSarAircraftPositionReportMessageUpdateNode( updateHandler, (AisStandardSarAircraftPositionReportMessageObject)data );
                }
                case Kind.AisStaticAndVoyageRelatedDataMessage:
                {
                    return new AisStaticAndVoyageRelatedDataMessageUpdateNode( updateHandler, (AisStaticAndVoyageRelatedDataMessageObject)data );
                }
                case Kind.AisStaticDataReportMessage:
                {
                    return new AisStaticDataReportMessageUpdateNode( updateHandler, (AisStaticDataReportMessageObject)data );
                }
                case Kind.AisStaticDataReportPartAMessage:
                {
                    return new AisStaticDataReportPartAMessageUpdateNode( updateHandler, (AisStaticDataReportPartAMessageObject)data );
                }
                case Kind.AisStaticDataReportPartBMessage:
                {
                    return new AisStaticDataReportPartBMessageUpdateNode( updateHandler, (AisStaticDataReportPartBMessageObject)data );
                }
                case Kind.AisUtcAndDateInquiryMessage:
                {
                    return new AisUtcAndDateInquiryMessageUpdateNode( updateHandler, (AisUtcAndDateInquiryMessageObject)data );
                }
                case Kind.AisUtcAndDateResponseMessage:
                {
                    return new AisUtcAndDateResponseMessageUpdateNode( updateHandler, (AisUtcAndDateResponseMessageObject)data );
                }
                case Kind.AlarmStateChange:
                {
                    return new AlarmStateChangeUpdateNode( updateHandler, (AlarmStateChangeObject)data );
                }
                case Kind.BaseStationType:
                {
                    return new BaseStationTypeUpdateNode( updateHandler, (BaseStationTypeObject)data );
                }
                case Kind.BinaryTimeseriesValue:
                {
                    return new BinaryTimeseriesValueUpdateNode( updateHandler, (BinaryTimeseriesValueObject)data );
                }
                case Kind.Bookmark:
                {
                    return new BookmarkUpdateNode( updateHandler, (BookmarkObject)data );
                }
                case Kind.BooleanTimeseriesValue:
                {
                    return new BooleanTimeseriesValueUpdateNode( updateHandler, (BooleanTimeseriesValueObject)data );
                }
                case Kind.ByteTimeseriesValue:
                {
                    return new ByteTimeseriesValueUpdateNode( updateHandler, (ByteTimeseriesValueObject)data );
                }
                case Kind.CameraCommand:
                {
                    return new CameraCommandUpdateNode( updateHandler, (CameraCommandObject)data );
                }
                case Kind.CameraCommandAbsoluteMove:
                {
                    return new CameraCommandAbsoluteMoveUpdateNode( updateHandler, (CameraCommandAbsoluteMoveObject)data );
                }
                case Kind.CameraCommandAdjustPanTiltZoom:
                {
                    return new CameraCommandAdjustPanTiltZoomUpdateNode( updateHandler, (CameraCommandAdjustPanTiltZoomObject)data );
                }
                case Kind.CameraCommandContinuousMove:
                {
                    return new CameraCommandContinuousMoveUpdateNode( updateHandler, (CameraCommandContinuousMoveObject)data );
                }
                case Kind.CameraCommandGeoMove:
                {
                    return new CameraCommandGeoMoveUpdateNode( updateHandler, (CameraCommandGeoMoveObject)data );
                }
                case Kind.CameraCommandRelativeMove:
                {
                    return new CameraCommandRelativeMoveUpdateNode( updateHandler, (CameraCommandRelativeMoveObject)data );
                }
                case Kind.CameraCommandReleasePTZOwnership:
                {
                    return new CameraCommandReleasePTZOwnershipUpdateNode( updateHandler, (CameraCommandReleasePTZOwnershipObject)data );
                }
                case Kind.CameraCommandRequestPTZOwnership:
                {
                    return new CameraCommandRequestPTZOwnershipUpdateNode( updateHandler, (CameraCommandRequestPTZOwnershipObject)data );
                }
                case Kind.CameraCommandSetAutoFocus:
                {
                    return new CameraCommandSetAutoFocusUpdateNode( updateHandler, (CameraCommandSetAutoFocusObject)data );
                }
                case Kind.CameraCommandSetBlackAndWhite:
                {
                    return new CameraCommandSetBlackAndWhiteUpdateNode( updateHandler, (CameraCommandSetBlackAndWhiteObject)data );
                }
                case Kind.CameraCommandSetFollowed:
                {
                    return new CameraCommandSetFollowedUpdateNode( updateHandler, (CameraCommandSetFollowedObject)data );
                }
                case Kind.CameraCommandSetInfraRedLamp:
                {
                    return new CameraCommandSetInfraRedLampUpdateNode( updateHandler, (CameraCommandSetInfraRedLampObject)data );
                }
                case Kind.CameraCommandSetWasher:
                {
                    return new CameraCommandSetWasherUpdateNode( updateHandler, (CameraCommandSetWasherObject)data );
                }
                case Kind.CameraCommandSetWiper:
                {
                    return new CameraCommandSetWiperUpdateNode( updateHandler, (CameraCommandSetWiperObject)data );
                }
                case Kind.CameraCommandStop:
                {
                    return new CameraCommandStopUpdateNode( updateHandler, (CameraCommandStopObject)data );
                }
                case Kind.CameraCommandReply:
                {
                    return new CameraCommandReplyUpdateNode( updateHandler, (CameraCommandReplyObject)data );
                }
                case Kind.CameraConfiguration:
                {
                    return new CameraConfigurationUpdateNode( updateHandler, (CameraConfigurationObject)data );
                }
                case Kind.CameraPanCalibration:
                {
                    return new CameraPanCalibrationUpdateNode( updateHandler, (CameraPanCalibrationObject)data );
                }
                case Kind.CameraPanCalibrationValue:
                {
                    return new CameraPanCalibrationValueUpdateNode( updateHandler, (CameraPanCalibrationValueObject)data );
                }
                case Kind.CameraStatus:
                {
                    return new CameraStatusUpdateNode( updateHandler, (CameraStatusObject)data );
                }
                case Kind.CameraTiltCalibration:
                {
                    return new CameraTiltCalibrationUpdateNode( updateHandler, (CameraTiltCalibrationObject)data );
                }
                case Kind.CameraTiltCalibrationValue:
                {
                    return new CameraTiltCalibrationValueUpdateNode( updateHandler, (CameraTiltCalibrationValueObject)data );
                }
                case Kind.CameraZoomCalibration:
                {
                    return new CameraZoomCalibrationUpdateNode( updateHandler, (CameraZoomCalibrationObject)data );
                }
                case Kind.CameraZoomCalibrationValue:
                {
                    return new CameraZoomCalibrationValueUpdateNode( updateHandler, (CameraZoomCalibrationValueObject)data );
                }
                case Kind.Catalog:
                {
                    return new CatalogUpdateNode( updateHandler, (CatalogObject)data );
                }
                case Kind.Element:
                {
                    return new ElementUpdateNode( updateHandler, (ElementObject)data );
                }
                case Kind.CollectionInfo:
                {
                    return new CollectionInfoUpdateNode( updateHandler, (CollectionInfoObject)data );
                }
                case Kind.Country:
                {
                    return new CountryUpdateNode( updateHandler, (CountryObject)data );
                }
                case Kind.CursorInfo:
                {
                    return new CursorInfoUpdateNode( updateHandler, (CursorInfoObject)data );
                }
                case Kind.DateTimeTimeseriesValue:
                {
                    return new DateTimeTimeseriesValueUpdateNode( updateHandler, (DateTimeTimeseriesValueObject)data );
                }
                case Kind.DeviceHost:
                {
                    return new DeviceHostUpdateNode( updateHandler, (DeviceHostObject)data );
                }
                case Kind.DeviceHostConfiguration:
                {
                    return new DeviceHostConfigurationUpdateNode( updateHandler, (DeviceHostConfigurationObject)data );
                }
                case Kind.DoubleTimeseriesValue:
                {
                    return new DoubleTimeseriesValueUpdateNode( updateHandler, (DoubleTimeseriesValueObject)data );
                }
                case Kind.FacilityType:
                {
                    return new FacilityTypeUpdateNode( updateHandler, (FacilityTypeObject)data );
                }
                case Kind.GeoPosition2DTimeseriesValue:
                {
                    return new GeoPosition2DTimeseriesValueUpdateNode( updateHandler, (GeoPosition2DTimeseriesValueObject)data );
                }
                case Kind.GeoPosition3DTimeseriesValue:
                {
                    return new GeoPosition3DTimeseriesValueUpdateNode( updateHandler, (GeoPosition3DTimeseriesValueObject)data );
                }
                case Kind.GNSSDeviceCommand:
                {
                    return new GNSSDeviceCommandUpdateNode( updateHandler, (GNSSDeviceCommandObject)data );
                }
                case Kind.GNSSDeviceCommandReply:
                {
                    return new GNSSDeviceCommandReplyUpdateNode( updateHandler, (GNSSDeviceCommandReplyObject)data );
                }
                case Kind.GNSSDeviceConfiguration:
                {
                    return new GNSSDeviceConfigurationUpdateNode( updateHandler, (GNSSDeviceConfigurationObject)data );
                }
                case Kind.GuidTimeseriesValue:
                {
                    return new GuidTimeseriesValueUpdateNode( updateHandler, (GuidTimeseriesValueObject)data );
                }
                case Kind.GyroDeviceCommand:
                {
                    return new GyroDeviceCommandUpdateNode( updateHandler, (GyroDeviceCommandObject)data );
                }
                case Kind.GyroDeviceCommandReply:
                {
                    return new GyroDeviceCommandReplyUpdateNode( updateHandler, (GyroDeviceCommandReplyObject)data );
                }
                case Kind.GyroDeviceConfiguration:
                {
                    return new GyroDeviceConfigurationUpdateNode( updateHandler, (GyroDeviceConfigurationObject)data );
                }
                case Kind.Callsign:
                {
                    return new CallsignUpdateNode( updateHandler, (CallsignObject)data );
                }
                case Kind.InternationalMaritimeOrganizationNumber:
                {
                    return new InternationalMaritimeOrganizationNumberUpdateNode( updateHandler, (InternationalMaritimeOrganizationNumberObject)data );
                }
                case Kind.MaritimeMobileServiceIdentity:
                {
                    return new MaritimeMobileServiceIdentityUpdateNode( updateHandler, (MaritimeMobileServiceIdentityObject)data );
                }
                case Kind.Name:
                {
                    return new NameUpdateNode( updateHandler, (NameObject)data );
                }
                case Kind.Int16TimeseriesValue:
                {
                    return new Int16TimeseriesValueUpdateNode( updateHandler, (Int16TimeseriesValueObject)data );
                }
                case Kind.Int32TimeseriesValue:
                {
                    return new Int32TimeseriesValueUpdateNode( updateHandler, (Int32TimeseriesValueObject)data );
                }
                case Kind.Int64TimeseriesValue:
                {
                    return new Int64TimeseriesValueUpdateNode( updateHandler, (Int64TimeseriesValueObject)data );
                }
                case Kind.BaseStation:
                {
                    return new BaseStationUpdateNode( updateHandler, (BaseStationObject)data );
                }
                case Kind.CameraDevice:
                {
                    return new CameraDeviceUpdateNode( updateHandler, (CameraDeviceObject)data );
                }
                case Kind.GNSSDevice:
                {
                    return new GNSSDeviceUpdateNode( updateHandler, (GNSSDeviceObject)data );
                }
                case Kind.GyroDevice:
                {
                    return new GyroDeviceUpdateNode( updateHandler, (GyroDeviceObject)data );
                }
                case Kind.LineInputDevice:
                {
                    return new LineInputDeviceUpdateNode( updateHandler, (LineInputDeviceObject)data );
                }
                case Kind.OilSpillDetectorDevice:
                {
                    return new OilSpillDetectorDeviceUpdateNode( updateHandler, (OilSpillDetectorDeviceObject)data );
                }
                case Kind.RadioDevice:
                {
                    return new RadioDeviceUpdateNode( updateHandler, (RadioDeviceObject)data );
                }
                case Kind.RadomeDevice:
                {
                    return new RadomeDeviceUpdateNode( updateHandler, (RadomeDeviceObject)data );
                }
                case Kind.AisDevice:
                {
                    return new AisDeviceUpdateNode( updateHandler, (AisDeviceObject)data );
                }
                case Kind.RadarDevice:
                {
                    return new RadarDeviceUpdateNode( updateHandler, (RadarDeviceObject)data );
                }
                case Kind.WeatherStationDevice:
                {
                    return new WeatherStationDeviceUpdateNode( updateHandler, (WeatherStationDeviceObject)data );
                }
                case Kind.Facility:
                {
                    return new FacilityUpdateNode( updateHandler, (FacilityObject)data );
                }
                case Kind.Aircraft:
                {
                    return new AircraftUpdateNode( updateHandler, (AircraftObject)data );
                }
                case Kind.AisAidToNavigation:
                {
                    return new AisAidToNavigationUpdateNode( updateHandler, (AisAidToNavigationObject)data );
                }
                case Kind.Vehicle:
                {
                    return new VehicleUpdateNode( updateHandler, (VehicleObject)data );
                }
                case Kind.Vessel:
                {
                    return new VesselUpdateNode( updateHandler, (VesselObject)data );
                }
                case Kind.ItemIdentityLink:
                {
                    return new ItemIdentityLinkUpdateNode( updateHandler, (ItemIdentityLinkObject)data );
                }
                case Kind.ItemParentChildLink:
                {
                    return new ItemParentChildLinkUpdateNode( updateHandler, (ItemParentChildLinkObject)data );
                }
                case Kind.LineInputDeviceCommand:
                {
                    return new LineInputDeviceCommandUpdateNode( updateHandler, (LineInputDeviceCommandObject)data );
                }
                case Kind.LineInputDeviceCommandReply:
                {
                    return new LineInputDeviceCommandReplyUpdateNode( updateHandler, (LineInputDeviceCommandReplyObject)data );
                }
                case Kind.LineInputDeviceConfiguration:
                {
                    return new LineInputDeviceConfigurationUpdateNode( updateHandler, (LineInputDeviceConfigurationObject)data );
                }
                case Kind.LineInputMessageRouting:
                {
                    return new LineInputMessageRoutingUpdateNode( updateHandler, (LineInputMessageRoutingObject)data );
                }
                case Kind.LineInputMessageRoutingDestination:
                {
                    return new LineInputMessageRoutingDestinationUpdateNode( updateHandler, (LineInputMessageRoutingDestinationObject)data );
                }
                case Kind.LineInputWhiteListEntry:
                {
                    return new LineInputWhiteListEntryUpdateNode( updateHandler, (LineInputWhiteListEntryObject)data );
                }
                case Kind.LogApplication:
                {
                    return new LogApplicationUpdateNode( updateHandler, (LogApplicationObject)data );
                }
                case Kind.LogApplicationConfiguration:
                {
                    return new LogApplicationConfigurationUpdateNode( updateHandler, (LogApplicationConfigurationObject)data );
                }
                case Kind.LogHost:
                {
                    return new LogHostUpdateNode( updateHandler, (LogHostObject)data );
                }
                case Kind.LogHostConfiguration:
                {
                    return new LogHostConfigurationUpdateNode( updateHandler, (LogHostConfigurationObject)data );
                }
                case Kind.LogLocation:
                {
                    return new LogLocationUpdateNode( updateHandler, (LogLocationObject)data );
                }
                case Kind.LogProcess:
                {
                    return new LogProcessUpdateNode( updateHandler, (LogProcessObject)data );
                }
                case Kind.LogRecord:
                {
                    return new LogRecordUpdateNode( updateHandler, (LogRecordObject)data );
                }
                case Kind.LogThread:
                {
                    return new LogThreadUpdateNode( updateHandler, (LogThreadObject)data );
                }
                case Kind.LogTraceEntry:
                {
                    return new LogTraceEntryUpdateNode( updateHandler, (LogTraceEntryObject)data );
                }
                case Kind.MapElement:
                {
                    return new MapElementUpdateNode( updateHandler, (MapElementObject)data );
                }
                case Kind.MapInfo:
                {
                    return new MapInfoUpdateNode( updateHandler, (MapInfoObject)data );
                }
                case Kind.MapServiceOptions:
                {
                    return new MapServiceOptionsUpdateNode( updateHandler, (MapServiceOptionsObject)data );
                }
                case Kind.MaritimeIdentificationDigits:
                {
                    return new MaritimeIdentificationDigitsUpdateNode( updateHandler, (MaritimeIdentificationDigitsObject)data );
                }
                case Kind.MediaProxySession:
                {
                    return new MediaProxySessionUpdateNode( updateHandler, (MediaProxySessionObject)data );
                }
                case Kind.MediaProxySessionFile:
                {
                    return new MediaProxySessionFileUpdateNode( updateHandler, (MediaProxySessionFileObject)data );
                }
                case Kind.MediaProxySessionOptions:
                {
                    return new MediaProxySessionOptionsUpdateNode( updateHandler, (MediaProxySessionOptionsObject)data );
                }
                case Kind.MediaService:
                {
                    return new MediaServiceUpdateNode( updateHandler, (MediaServiceObject)data );
                }
                case Kind.MediaServiceOptions:
                {
                    return new MediaServiceOptionsUpdateNode( updateHandler, (MediaServiceOptionsObject)data );
                }
                case Kind.ElementType:
                {
                    return new ElementTypeUpdateNode( updateHandler, (ElementTypeObject)data );
                }
                case Kind.Namespace:
                {
                    return new NamespaceUpdateNode( updateHandler, (NamespaceObject)data );
                }
                case Kind.OilSpill:
                {
                    return new OilSpillUpdateNode( updateHandler, (OilSpillObject)data );
                }
                case Kind.OilSpillDetectorCommand:
                {
                    return new OilSpillDetectorCommandUpdateNode( updateHandler, (OilSpillDetectorCommandObject)data );
                }
                case Kind.OilSpillDetectorCommandReply:
                {
                    return new OilSpillDetectorCommandReplyUpdateNode( updateHandler, (OilSpillDetectorCommandReplyObject)data );
                }
                case Kind.OilSpillDetectorConfiguration:
                {
                    return new OilSpillDetectorConfigurationUpdateNode( updateHandler, (OilSpillDetectorConfigurationObject)data );
                }
                case Kind.Position2DTimeseriesValue:
                {
                    return new Position2DTimeseriesValueUpdateNode( updateHandler, (Position2DTimeseriesValueObject)data );
                }
                case Kind.Position3DTimeseriesValue:
                {
                    return new Position3DTimeseriesValueUpdateNode( updateHandler, (Position3DTimeseriesValueObject)data );
                }
                case Kind.ProcessTrackValueResult:
                {
                    return new ProcessTrackValueResultUpdateNode( updateHandler, (ProcessTrackValueResultObject)data );
                }
                case Kind.BinaryProperty:
                {
                    return new BinaryPropertyUpdateNode( updateHandler, (BinaryPropertyObject)data );
                }
                case Kind.BooleanProperty:
                {
                    return new BooleanPropertyUpdateNode( updateHandler, (BooleanPropertyObject)data );
                }
                case Kind.ByteProperty:
                {
                    return new BytePropertyUpdateNode( updateHandler, (BytePropertyObject)data );
                }
                case Kind.DateTimeProperty:
                {
                    return new DateTimePropertyUpdateNode( updateHandler, (DateTimePropertyObject)data );
                }
                case Kind.DoubleProperty:
                {
                    return new DoublePropertyUpdateNode( updateHandler, (DoublePropertyObject)data );
                }
                case Kind.GuidProperty:
                {
                    return new GuidPropertyUpdateNode( updateHandler, (GuidPropertyObject)data );
                }
                case Kind.Int16Property:
                {
                    return new Int16PropertyUpdateNode( updateHandler, (Int16PropertyObject)data );
                }
                case Kind.Int32Property:
                {
                    return new Int32PropertyUpdateNode( updateHandler, (Int32PropertyObject)data );
                }
                case Kind.Int64Property:
                {
                    return new Int64PropertyUpdateNode( updateHandler, (Int64PropertyObject)data );
                }
                case Kind.ReferenceProperty:
                {
                    return new ReferencePropertyUpdateNode( updateHandler, (ReferencePropertyObject)data );
                }
                case Kind.SByteProperty:
                {
                    return new SBytePropertyUpdateNode( updateHandler, (SBytePropertyObject)data );
                }
                case Kind.SingleProperty:
                {
                    return new SinglePropertyUpdateNode( updateHandler, (SinglePropertyObject)data );
                }
                case Kind.StringProperty:
                {
                    return new StringPropertyUpdateNode( updateHandler, (StringPropertyObject)data );
                }
                case Kind.BinaryTimeseriesProperty:
                {
                    return new BinaryTimeseriesPropertyUpdateNode( updateHandler, (BinaryTimeseriesPropertyObject)data );
                }
                case Kind.BooleanTimeseriesProperty:
                {
                    return new BooleanTimeseriesPropertyUpdateNode( updateHandler, (BooleanTimeseriesPropertyObject)data );
                }
                case Kind.ByteTimeseriesProperty:
                {
                    return new ByteTimeseriesPropertyUpdateNode( updateHandler, (ByteTimeseriesPropertyObject)data );
                }
                case Kind.DateTimeTimeseriesProperty:
                {
                    return new DateTimeTimeseriesPropertyUpdateNode( updateHandler, (DateTimeTimeseriesPropertyObject)data );
                }
                case Kind.DoubleTimeseriesProperty:
                {
                    return new DoubleTimeseriesPropertyUpdateNode( updateHandler, (DoubleTimeseriesPropertyObject)data );
                }
                case Kind.GuidTimeseriesProperty:
                {
                    return new GuidTimeseriesPropertyUpdateNode( updateHandler, (GuidTimeseriesPropertyObject)data );
                }
                case Kind.Int16TimeseriesProperty:
                {
                    return new Int16TimeseriesPropertyUpdateNode( updateHandler, (Int16TimeseriesPropertyObject)data );
                }
                case Kind.Int32TimeseriesProperty:
                {
                    return new Int32TimeseriesPropertyUpdateNode( updateHandler, (Int32TimeseriesPropertyObject)data );
                }
                case Kind.Int64TimeseriesProperty:
                {
                    return new Int64TimeseriesPropertyUpdateNode( updateHandler, (Int64TimeseriesPropertyObject)data );
                }
                case Kind.ReferenceTimeseriesProperty:
                {
                    return new ReferenceTimeseriesPropertyUpdateNode( updateHandler, (ReferenceTimeseriesPropertyObject)data );
                }
                case Kind.SByteTimeseriesProperty:
                {
                    return new SByteTimeseriesPropertyUpdateNode( updateHandler, (SByteTimeseriesPropertyObject)data );
                }
                case Kind.SingleTimeseriesProperty:
                {
                    return new SingleTimeseriesPropertyUpdateNode( updateHandler, (SingleTimeseriesPropertyObject)data );
                }
                case Kind.StringTimeseriesProperty:
                {
                    return new StringTimeseriesPropertyUpdateNode( updateHandler, (StringTimeseriesPropertyObject)data );
                }
                case Kind.TimeSpanTimeseriesProperty:
                {
                    return new TimeSpanTimeseriesPropertyUpdateNode( updateHandler, (TimeSpanTimeseriesPropertyObject)data );
                }
                case Kind.UInt16TimeseriesProperty:
                {
                    return new UInt16TimeseriesPropertyUpdateNode( updateHandler, (UInt16TimeseriesPropertyObject)data );
                }
                case Kind.UInt32TimeseriesProperty:
                {
                    return new UInt32TimeseriesPropertyUpdateNode( updateHandler, (UInt32TimeseriesPropertyObject)data );
                }
                case Kind.UInt64TimeseriesProperty:
                {
                    return new UInt64TimeseriesPropertyUpdateNode( updateHandler, (UInt64TimeseriesPropertyObject)data );
                }
                case Kind.TimeSpanProperty:
                {
                    return new TimeSpanPropertyUpdateNode( updateHandler, (TimeSpanPropertyObject)data );
                }
                case Kind.UInt16Property:
                {
                    return new UInt16PropertyUpdateNode( updateHandler, (UInt16PropertyObject)data );
                }
                case Kind.UInt32Property:
                {
                    return new UInt32PropertyUpdateNode( updateHandler, (UInt32PropertyObject)data );
                }
                case Kind.UInt64Property:
                {
                    return new UInt64PropertyUpdateNode( updateHandler, (UInt64PropertyObject)data );
                }
                case Kind.BinaryPropertyDefinition:
                {
                    return new BinaryPropertyDefinitionUpdateNode( updateHandler, (BinaryPropertyDefinitionObject)data );
                }
                case Kind.BooleanPropertyDefinition:
                {
                    return new BooleanPropertyDefinitionUpdateNode( updateHandler, (BooleanPropertyDefinitionObject)data );
                }
                case Kind.BytePropertyDefinition:
                {
                    return new BytePropertyDefinitionUpdateNode( updateHandler, (BytePropertyDefinitionObject)data );
                }
                case Kind.DateTimePropertyDefinition:
                {
                    return new DateTimePropertyDefinitionUpdateNode( updateHandler, (DateTimePropertyDefinitionObject)data );
                }
                case Kind.DoublePropertyDefinition:
                {
                    return new DoublePropertyDefinitionUpdateNode( updateHandler, (DoublePropertyDefinitionObject)data );
                }
                case Kind.GuidPropertyDefinition:
                {
                    return new GuidPropertyDefinitionUpdateNode( updateHandler, (GuidPropertyDefinitionObject)data );
                }
                case Kind.Int16PropertyDefinition:
                {
                    return new Int16PropertyDefinitionUpdateNode( updateHandler, (Int16PropertyDefinitionObject)data );
                }
                case Kind.Int32PropertyDefinition:
                {
                    return new Int32PropertyDefinitionUpdateNode( updateHandler, (Int32PropertyDefinitionObject)data );
                }
                case Kind.Int64PropertyDefinition:
                {
                    return new Int64PropertyDefinitionUpdateNode( updateHandler, (Int64PropertyDefinitionObject)data );
                }
                case Kind.ReferencePropertyDefinition:
                {
                    return new ReferencePropertyDefinitionUpdateNode( updateHandler, (ReferencePropertyDefinitionObject)data );
                }
                case Kind.SBytePropertyDefinition:
                {
                    return new SBytePropertyDefinitionUpdateNode( updateHandler, (SBytePropertyDefinitionObject)data );
                }
                case Kind.SinglePropertyDefinition:
                {
                    return new SinglePropertyDefinitionUpdateNode( updateHandler, (SinglePropertyDefinitionObject)data );
                }
                case Kind.StringPropertyDefinition:
                {
                    return new StringPropertyDefinitionUpdateNode( updateHandler, (StringPropertyDefinitionObject)data );
                }
                case Kind.BinaryTimeseriesPropertyDefinition:
                {
                    return new BinaryTimeseriesPropertyDefinitionUpdateNode( updateHandler, (BinaryTimeseriesPropertyDefinitionObject)data );
                }
                case Kind.BooleanTimeseriesPropertyDefinition:
                {
                    return new BooleanTimeseriesPropertyDefinitionUpdateNode( updateHandler, (BooleanTimeseriesPropertyDefinitionObject)data );
                }
                case Kind.ByteTimeseriesPropertyDefinition:
                {
                    return new ByteTimeseriesPropertyDefinitionUpdateNode( updateHandler, (ByteTimeseriesPropertyDefinitionObject)data );
                }
                case Kind.DateTimeTimeseriesPropertyDefinition:
                {
                    return new DateTimeTimeseriesPropertyDefinitionUpdateNode( updateHandler, (DateTimeTimeseriesPropertyDefinitionObject)data );
                }
                case Kind.DoubleTimeseriesPropertyDefinition:
                {
                    return new DoubleTimeseriesPropertyDefinitionUpdateNode( updateHandler, (DoubleTimeseriesPropertyDefinitionObject)data );
                }
                case Kind.GuidTimeseriesPropertyDefinition:
                {
                    return new GuidTimeseriesPropertyDefinitionUpdateNode( updateHandler, (GuidTimeseriesPropertyDefinitionObject)data );
                }
                case Kind.Int16TimeseriesPropertyDefinition:
                {
                    return new Int16TimeseriesPropertyDefinitionUpdateNode( updateHandler, (Int16TimeseriesPropertyDefinitionObject)data );
                }
                case Kind.Int32TimeseriesPropertyDefinition:
                {
                    return new Int32TimeseriesPropertyDefinitionUpdateNode( updateHandler, (Int32TimeseriesPropertyDefinitionObject)data );
                }
                case Kind.Int64TimeseriesPropertyDefinition:
                {
                    return new Int64TimeseriesPropertyDefinitionUpdateNode( updateHandler, (Int64TimeseriesPropertyDefinitionObject)data );
                }
                case Kind.ReferenceTimeseriesPropertyDefinition:
                {
                    return new ReferenceTimeseriesPropertyDefinitionUpdateNode( updateHandler, (ReferenceTimeseriesPropertyDefinitionObject)data );
                }
                case Kind.SByteTimeseriesPropertyDefinition:
                {
                    return new SByteTimeseriesPropertyDefinitionUpdateNode( updateHandler, (SByteTimeseriesPropertyDefinitionObject)data );
                }
                case Kind.SingleTimeseriesPropertyDefinition:
                {
                    return new SingleTimeseriesPropertyDefinitionUpdateNode( updateHandler, (SingleTimeseriesPropertyDefinitionObject)data );
                }
                case Kind.StringTimeseriesPropertyDefinition:
                {
                    return new StringTimeseriesPropertyDefinitionUpdateNode( updateHandler, (StringTimeseriesPropertyDefinitionObject)data );
                }
                case Kind.TimeSpanTimeseriesPropertyDefinition:
                {
                    return new TimeSpanTimeseriesPropertyDefinitionUpdateNode( updateHandler, (TimeSpanTimeseriesPropertyDefinitionObject)data );
                }
                case Kind.UInt16TimeseriesPropertyDefinition:
                {
                    return new UInt16TimeseriesPropertyDefinitionUpdateNode( updateHandler, (UInt16TimeseriesPropertyDefinitionObject)data );
                }
                case Kind.UInt32TimeseriesPropertyDefinition:
                {
                    return new UInt32TimeseriesPropertyDefinitionUpdateNode( updateHandler, (UInt32TimeseriesPropertyDefinitionObject)data );
                }
                case Kind.UInt64TimeseriesPropertyDefinition:
                {
                    return new UInt64TimeseriesPropertyDefinitionUpdateNode( updateHandler, (UInt64TimeseriesPropertyDefinitionObject)data );
                }
                case Kind.TimeSpanPropertyDefinition:
                {
                    return new TimeSpanPropertyDefinitionUpdateNode( updateHandler, (TimeSpanPropertyDefinitionObject)data );
                }
                case Kind.UInt16PropertyDefinition:
                {
                    return new UInt16PropertyDefinitionUpdateNode( updateHandler, (UInt16PropertyDefinitionObject)data );
                }
                case Kind.UInt32PropertyDefinition:
                {
                    return new UInt32PropertyDefinitionUpdateNode( updateHandler, (UInt32PropertyDefinitionObject)data );
                }
                case Kind.UInt64PropertyDefinition:
                {
                    return new UInt64PropertyDefinitionUpdateNode( updateHandler, (UInt64PropertyDefinitionObject)data );
                }
                case Kind.RadarAlarmStatus:
                {
                    return new RadarAlarmStatusUpdateNode( updateHandler, (RadarAlarmStatusObject)data );
                }
                case Kind.RadarCommand:
                {
                    return new RadarCommandUpdateNode( updateHandler, (RadarCommandObject)data );
                }
                case Kind.RadarCommandGetStatus:
                {
                    return new RadarCommandGetStatusUpdateNode( updateHandler, (RadarCommandGetStatusObject)data );
                }
                case Kind.RadarCommandReply:
                {
                    return new RadarCommandReplyUpdateNode( updateHandler, (RadarCommandReplyObject)data );
                }
                case Kind.RadarCommandReplyGetStatus:
                {
                    return new RadarCommandReplyGetStatusUpdateNode( updateHandler, (RadarCommandReplyGetStatusObject)data );
                }
                case Kind.RadarConfiguration:
                {
                    return new RadarConfigurationUpdateNode( updateHandler, (RadarConfigurationObject)data );
                }
                case Kind.RadarImage:
                {
                    return new RadarImageUpdateNode( updateHandler, (RadarImageObject)data );
                }
                case Kind.RadarRawTrackTable:
                {
                    return new RadarRawTrackTableUpdateNode( updateHandler, (RadarRawTrackTableObject)data );
                }
                case Kind.RadarStatus:
                {
                    return new RadarStatusUpdateNode( updateHandler, (RadarStatusObject)data );
                }
                case Kind.RadioCommand:
                {
                    return new RadioCommandUpdateNode( updateHandler, (RadioCommandObject)data );
                }
                case Kind.RadioCommandReply:
                {
                    return new RadioCommandReplyUpdateNode( updateHandler, (RadioCommandReplyObject)data );
                }
                case Kind.RadioConfiguration:
                {
                    return new RadioConfigurationUpdateNode( updateHandler, (RadioConfigurationObject)data );
                }
                case Kind.RadomeCommand:
                {
                    return new RadomeCommandUpdateNode( updateHandler, (RadomeCommandObject)data );
                }
                case Kind.RadomeCommandReply:
                {
                    return new RadomeCommandReplyUpdateNode( updateHandler, (RadomeCommandReplyObject)data );
                }
                case Kind.RadomeConfiguration:
                {
                    return new RadomeConfigurationUpdateNode( updateHandler, (RadomeConfigurationObject)data );
                }
                case Kind.ReferenceTimeseriesValue:
                {
                    return new ReferenceTimeseriesValueUpdateNode( updateHandler, (ReferenceTimeseriesValueObject)data );
                }
                case Kind.SByteTimeseriesValue:
                {
                    return new SByteTimeseriesValueUpdateNode( updateHandler, (SByteTimeseriesValueObject)data );
                }
                case Kind.SecurityDomain:
                {
                    return new SecurityDomainUpdateNode( updateHandler, (SecurityDomainObject)data );
                }
                case Kind.SecurityLogin:
                {
                    return new SecurityLoginUpdateNode( updateHandler, (SecurityLoginObject)data );
                }
                case Kind.SecurityRole:
                {
                    return new SecurityRoleUpdateNode( updateHandler, (SecurityRoleObject)data );
                }
                case Kind.SecurityIdentifierRoleLink:
                {
                    return new SecurityIdentifierRoleLinkUpdateNode( updateHandler, (SecurityIdentifierRoleLinkObject)data );
                }
                case Kind.SecurityLoginSession:
                {
                    return new SecurityLoginSessionUpdateNode( updateHandler, (SecurityLoginSessionObject)data );
                }
                case Kind.SecurityPermission:
                {
                    return new SecurityPermissionUpdateNode( updateHandler, (SecurityPermissionObject)data );
                }
                case Kind.SingleTimeseriesValue:
                {
                    return new SingleTimeseriesValueUpdateNode( updateHandler, (SingleTimeseriesValueObject)data );
                }
                case Kind.StringTimeseriesValue:
                {
                    return new StringTimeseriesValueUpdateNode( updateHandler, (StringTimeseriesValueObject)data );
                }
                case Kind.BinaryTimeseries:
                {
                    return new BinaryTimeseriesUpdateNode( updateHandler, (BinaryTimeseriesObject)data );
                }
                case Kind.BooleanTimeseries:
                {
                    return new BooleanTimeseriesUpdateNode( updateHandler, (BooleanTimeseriesObject)data );
                }
                case Kind.AisAidToNavigationOffPositionTimeseries:
                {
                    return new AisAidToNavigationOffPositionTimeseriesUpdateNode( updateHandler, (AisAidToNavigationOffPositionTimeseriesObject)data );
                }
                case Kind.DeviceEnabledTimeseries:
                {
                    return new DeviceEnabledTimeseriesUpdateNode( updateHandler, (DeviceEnabledTimeseriesObject)data );
                }
                case Kind.RadarAutomaticSensitivityTimeControlTimeseries:
                {
                    return new RadarAutomaticSensitivityTimeControlTimeseriesUpdateNode( updateHandler, (RadarAutomaticSensitivityTimeControlTimeseriesObject)data );
                }
                case Kind.RadarBlankSector1Timeseries:
                {
                    return new RadarBlankSector1TimeseriesUpdateNode( updateHandler, (RadarBlankSector1TimeseriesObject)data );
                }
                case Kind.RadarBlankSector2Timeseries:
                {
                    return new RadarBlankSector2TimeseriesUpdateNode( updateHandler, (RadarBlankSector2TimeseriesObject)data );
                }
                case Kind.RadarEnableAutomaticFrequencyControlTimeseries:
                {
                    return new RadarEnableAutomaticFrequencyControlTimeseriesUpdateNode( updateHandler, (RadarEnableAutomaticFrequencyControlTimeseriesObject)data );
                }
                case Kind.RadarEnableFastTimeConstantTimeseries:
                {
                    return new RadarEnableFastTimeConstantTimeseriesUpdateNode( updateHandler, (RadarEnableFastTimeConstantTimeseriesObject)data );
                }
                case Kind.RadarEnableSensitivityTimeControlTimeseries:
                {
                    return new RadarEnableSensitivityTimeControlTimeseriesUpdateNode( updateHandler, (RadarEnableSensitivityTimeControlTimeseriesObject)data );
                }
                case Kind.RadarPowerOnTimeseries:
                {
                    return new RadarPowerOnTimeseriesUpdateNode( updateHandler, (RadarPowerOnTimeseriesObject)data );
                }
                case Kind.RadarSaveSettingsTimeseries:
                {
                    return new RadarSaveSettingsTimeseriesUpdateNode( updateHandler, (RadarSaveSettingsTimeseriesObject)data );
                }
                case Kind.RadarTrackingTimeseries:
                {
                    return new RadarTrackingTimeseriesUpdateNode( updateHandler, (RadarTrackingTimeseriesObject)data );
                }
                case Kind.MediaProxySessionEnabledTimeseries:
                {
                    return new MediaProxySessionEnabledTimeseriesUpdateNode( updateHandler, (MediaProxySessionEnabledTimeseriesObject)data );
                }
                case Kind.MediaServiceEnabledTimeseries:
                {
                    return new MediaServiceEnabledTimeseriesUpdateNode( updateHandler, (MediaServiceEnabledTimeseriesObject)data );
                }
                case Kind.ByteTimeseries:
                {
                    return new ByteTimeseriesUpdateNode( updateHandler, (ByteTimeseriesObject)data );
                }
                case Kind.DateTimeTimeseries:
                {
                    return new DateTimeTimeseriesUpdateNode( updateHandler, (DateTimeTimeseriesObject)data );
                }
                case Kind.DoubleTimeseries:
                {
                    return new DoubleTimeseriesUpdateNode( updateHandler, (DoubleTimeseriesObject)data );
                }
                case Kind.GNSSAltitudeTimeseries:
                {
                    return new GNSSAltitudeTimeseriesUpdateNode( updateHandler, (GNSSAltitudeTimeseriesObject)data );
                }
                case Kind.GNSSLatitudeTimeseries:
                {
                    return new GNSSLatitudeTimeseriesUpdateNode( updateHandler, (GNSSLatitudeTimeseriesObject)data );
                }
                case Kind.GNSSLongitudeTimeseries:
                {
                    return new GNSSLongitudeTimeseriesUpdateNode( updateHandler, (GNSSLongitudeTimeseriesObject)data );
                }
                case Kind.GyroCourseTimeseries:
                {
                    return new GyroCourseTimeseriesUpdateNode( updateHandler, (GyroCourseTimeseriesObject)data );
                }
                case Kind.GyroHeadingMagneticNorthTimeseries:
                {
                    return new GyroHeadingMagneticNorthTimeseriesUpdateNode( updateHandler, (GyroHeadingMagneticNorthTimeseriesObject)data );
                }
                case Kind.GyroHeadingTrueNorthTimeseries:
                {
                    return new GyroHeadingTrueNorthTimeseriesUpdateNode( updateHandler, (GyroHeadingTrueNorthTimeseriesObject)data );
                }
                case Kind.GyroPitchTimeseries:
                {
                    return new GyroPitchTimeseriesUpdateNode( updateHandler, (GyroPitchTimeseriesObject)data );
                }
                case Kind.GyroRateOfTurnTimeseries:
                {
                    return new GyroRateOfTurnTimeseriesUpdateNode( updateHandler, (GyroRateOfTurnTimeseriesObject)data );
                }
                case Kind.GyroRollTimeseries:
                {
                    return new GyroRollTimeseriesUpdateNode( updateHandler, (GyroRollTimeseriesObject)data );
                }
                case Kind.GyroSpeedTimeseries:
                {
                    return new GyroSpeedTimeseriesUpdateNode( updateHandler, (GyroSpeedTimeseriesObject)data );
                }
                case Kind.RadarLatitudeTimeseries:
                {
                    return new RadarLatitudeTimeseriesUpdateNode( updateHandler, (RadarLatitudeTimeseriesObject)data );
                }
                case Kind.RadarLongitudeTimeseries:
                {
                    return new RadarLongitudeTimeseriesUpdateNode( updateHandler, (RadarLongitudeTimeseriesObject)data );
                }
                case Kind.RadomeDewPointTimeseries:
                {
                    return new RadomeDewPointTimeseriesUpdateNode( updateHandler, (RadomeDewPointTimeseriesObject)data );
                }
                case Kind.RadomePressureTimeseries:
                {
                    return new RadomePressureTimeseriesUpdateNode( updateHandler, (RadomePressureTimeseriesObject)data );
                }
                case Kind.RadomeTemperatureTimeseries:
                {
                    return new RadomeTemperatureTimeseriesUpdateNode( updateHandler, (RadomeTemperatureTimeseriesObject)data );
                }
                case Kind.VesselDraughtTimeseries:
                {
                    return new VesselDraughtTimeseriesUpdateNode( updateHandler, (VesselDraughtTimeseriesObject)data );
                }
                case Kind.ViewLatitudeTimeseries:
                {
                    return new ViewLatitudeTimeseriesUpdateNode( updateHandler, (ViewLatitudeTimeseriesObject)data );
                }
                case Kind.ViewLongitudeTimeseries:
                {
                    return new ViewLongitudeTimeseriesUpdateNode( updateHandler, (ViewLongitudeTimeseriesObject)data );
                }
                case Kind.ViewZoomLevelTimeseries:
                {
                    return new ViewZoomLevelTimeseriesUpdateNode( updateHandler, (ViewZoomLevelTimeseriesObject)data );
                }
                case Kind.WeatherStationAbsoluteHumidityTimeseries:
                {
                    return new WeatherStationAbsoluteHumidityTimeseriesUpdateNode( updateHandler, (WeatherStationAbsoluteHumidityTimeseriesObject)data );
                }
                case Kind.WeatherStationAirTemperatureTimeseries:
                {
                    return new WeatherStationAirTemperatureTimeseriesUpdateNode( updateHandler, (WeatherStationAirTemperatureTimeseriesObject)data );
                }
                case Kind.WeatherStationBarometricPressureTimeseries:
                {
                    return new WeatherStationBarometricPressureTimeseriesUpdateNode( updateHandler, (WeatherStationBarometricPressureTimeseriesObject)data );
                }
                case Kind.WeatherStationDewPointTimeseries:
                {
                    return new WeatherStationDewPointTimeseriesUpdateNode( updateHandler, (WeatherStationDewPointTimeseriesObject)data );
                }
                case Kind.WeatherStationRelativeHumidityTimeseries:
                {
                    return new WeatherStationRelativeHumidityTimeseriesUpdateNode( updateHandler, (WeatherStationRelativeHumidityTimeseriesObject)data );
                }
                case Kind.WeatherStationWaterTemperatureTimeseries:
                {
                    return new WeatherStationWaterTemperatureTimeseriesUpdateNode( updateHandler, (WeatherStationWaterTemperatureTimeseriesObject)data );
                }
                case Kind.WeatherStationWindDirectionTimeseries:
                {
                    return new WeatherStationWindDirectionTimeseriesUpdateNode( updateHandler, (WeatherStationWindDirectionTimeseriesObject)data );
                }
                case Kind.WeatherStationWindSpeedTimeseries:
                {
                    return new WeatherStationWindSpeedTimeseriesUpdateNode( updateHandler, (WeatherStationWindSpeedTimeseriesObject)data );
                }
                case Kind.GeoPosition2DTimeseries:
                {
                    return new GeoPosition2DTimeseriesUpdateNode( updateHandler, (GeoPosition2DTimeseriesObject)data );
                }
                case Kind.AisAidToNavigationPositionTimeseries:
                {
                    return new AisAidToNavigationPositionTimeseriesUpdateNode( updateHandler, (AisAidToNavigationPositionTimeseriesObject)data );
                }
                case Kind.GeoPosition3DTimeseries:
                {
                    return new GeoPosition3DTimeseriesUpdateNode( updateHandler, (GeoPosition3DTimeseriesObject)data );
                }
                case Kind.GuidTimeseries:
                {
                    return new GuidTimeseriesUpdateNode( updateHandler, (GuidTimeseriesObject)data );
                }
                case Kind.Int16Timeseries:
                {
                    return new Int16TimeseriesUpdateNode( updateHandler, (Int16TimeseriesObject)data );
                }
                case Kind.Int32Timeseries:
                {
                    return new Int32TimeseriesUpdateNode( updateHandler, (Int32TimeseriesObject)data );
                }
                case Kind.RadarAzimuthOffsetTimeseries:
                {
                    return new RadarAzimuthOffsetTimeseriesUpdateNode( updateHandler, (RadarAzimuthOffsetTimeseriesObject)data );
                }
                case Kind.RadarFastTimeConstantLevelTimeseries:
                {
                    return new RadarFastTimeConstantLevelTimeseriesUpdateNode( updateHandler, (RadarFastTimeConstantLevelTimeseriesObject)data );
                }
                case Kind.RadarFastTimeConstantModeTimeseries:
                {
                    return new RadarFastTimeConstantModeTimeseriesUpdateNode( updateHandler, (RadarFastTimeConstantModeTimeseriesObject)data );
                }
                case Kind.RadarPulseTimeseries:
                {
                    return new RadarPulseTimeseriesUpdateNode( updateHandler, (RadarPulseTimeseriesObject)data );
                }
                case Kind.RadarSector1EndTimeseries:
                {
                    return new RadarSector1EndTimeseriesUpdateNode( updateHandler, (RadarSector1EndTimeseriesObject)data );
                }
                case Kind.RadarSector1StartTimeseries:
                {
                    return new RadarSector1StartTimeseriesUpdateNode( updateHandler, (RadarSector1StartTimeseriesObject)data );
                }
                case Kind.RadarSector2EndTimeseries:
                {
                    return new RadarSector2EndTimeseriesUpdateNode( updateHandler, (RadarSector2EndTimeseriesObject)data );
                }
                case Kind.RadarSector2StartTimeseries:
                {
                    return new RadarSector2StartTimeseriesUpdateNode( updateHandler, (RadarSector2StartTimeseriesObject)data );
                }
                case Kind.RadarSensitivityTimeControlLevelTimeseries:
                {
                    return new RadarSensitivityTimeControlLevelTimeseriesUpdateNode( updateHandler, (RadarSensitivityTimeControlLevelTimeseriesObject)data );
                }
                case Kind.RadarTuningTimeseries:
                {
                    return new RadarTuningTimeseriesUpdateNode( updateHandler, (RadarTuningTimeseriesObject)data );
                }
                case Kind.VesselPersonsOnBoardTimeseries:
                {
                    return new VesselPersonsOnBoardTimeseriesUpdateNode( updateHandler, (VesselPersonsOnBoardTimeseriesObject)data );
                }
                case Kind.Int64Timeseries:
                {
                    return new Int64TimeseriesUpdateNode( updateHandler, (Int64TimeseriesObject)data );
                }
                case Kind.Position2DTimeseries:
                {
                    return new Position2DTimeseriesUpdateNode( updateHandler, (Position2DTimeseriesObject)data );
                }
                case Kind.Position3DTimeseries:
                {
                    return new Position3DTimeseriesUpdateNode( updateHandler, (Position3DTimeseriesObject)data );
                }
                case Kind.ReferenceTimeseries:
                {
                    return new ReferenceTimeseriesUpdateNode( updateHandler, (ReferenceTimeseriesObject)data );
                }
                case Kind.SByteTimeseries:
                {
                    return new SByteTimeseriesUpdateNode( updateHandler, (SByteTimeseriesObject)data );
                }
                case Kind.SingleTimeseries:
                {
                    return new SingleTimeseriesUpdateNode( updateHandler, (SingleTimeseriesObject)data );
                }
                case Kind.StringTimeseries:
                {
                    return new StringTimeseriesUpdateNode( updateHandler, (StringTimeseriesObject)data );
                }
                case Kind.TimeSpanTimeseries:
                {
                    return new TimeSpanTimeseriesUpdateNode( updateHandler, (TimeSpanTimeseriesObject)data );
                }
                case Kind.UInt16Timeseries:
                {
                    return new UInt16TimeseriesUpdateNode( updateHandler, (UInt16TimeseriesObject)data );
                }
                case Kind.UInt32Timeseries:
                {
                    return new UInt32TimeseriesUpdateNode( updateHandler, (UInt32TimeseriesObject)data );
                }
                case Kind.RadomeStatusTimeseries:
                {
                    return new RadomeStatusTimeseriesUpdateNode( updateHandler, (RadomeStatusTimeseriesObject)data );
                }
                case Kind.UInt64Timeseries:
                {
                    return new UInt64TimeseriesUpdateNode( updateHandler, (UInt64TimeseriesObject)data );
                }
                case Kind.TimeseriesCatalog:
                {
                    return new TimeseriesCatalogUpdateNode( updateHandler, (TimeseriesCatalogObject)data );
                }
                case Kind.TimeseriesInfo:
                {
                    return new TimeseriesInfoUpdateNode( updateHandler, (TimeseriesInfoObject)data );
                }
                case Kind.TimeSpanTimeseriesValue:
                {
                    return new TimeSpanTimeseriesValueUpdateNode( updateHandler, (TimeSpanTimeseriesValueObject)data );
                }
                case Kind.TrackableItemTrackLink:
                {
                    return new TrackableItemTrackLinkUpdateNode( updateHandler, (TrackableItemTrackLinkObject)data );
                }
                case Kind.Track:
                {
                    return new TrackUpdateNode( updateHandler, (TrackObject)data );
                }
                case Kind.Track3D:
                {
                    return new Track3DUpdateNode( updateHandler, (Track3DObject)data );
                }
                case Kind.TrackerFilterParameters:
                {
                    return new TrackerFilterParametersUpdateNode( updateHandler, (TrackerFilterParametersObject)data );
                }
                case Kind.TrackerFilterParametersConfiguration:
                {
                    return new TrackerFilterParametersConfigurationUpdateNode( updateHandler, (TrackerFilterParametersConfigurationObject)data );
                }
                case Kind.TrackInfo:
                {
                    return new TrackInfoUpdateNode( updateHandler, (TrackInfoObject)data );
                }
                case Kind.TrackingServiceOptions:
                {
                    return new TrackingServiceOptionsUpdateNode( updateHandler, (TrackingServiceOptionsObject)data );
                }
                case Kind.TrackLink:
                {
                    return new TrackLinkUpdateNode( updateHandler, (TrackLinkObject)data );
                }
                case Kind.TrackValue:
                {
                    return new TrackValueUpdateNode( updateHandler, (TrackValueObject)data );
                }
                case Kind.TrackValue3D:
                {
                    return new TrackValue3DUpdateNode( updateHandler, (TrackValue3DObject)data );
                }
                case Kind.UInt16TimeseriesValue:
                {
                    return new UInt16TimeseriesValueUpdateNode( updateHandler, (UInt16TimeseriesValueObject)data );
                }
                case Kind.UInt32TimeseriesValue:
                {
                    return new UInt32TimeseriesValueUpdateNode( updateHandler, (UInt32TimeseriesValueObject)data );
                }
                case Kind.UInt64TimeseriesValue:
                {
                    return new UInt64TimeseriesValueUpdateNode( updateHandler, (UInt64TimeseriesValueObject)data );
                }
                case Kind.VehicleType:
                {
                    return new VehicleTypeUpdateNode( updateHandler, (VehicleTypeObject)data );
                }
                case Kind.VesselType:
                {
                    return new VesselTypeUpdateNode( updateHandler, (VesselTypeObject)data );
                }
                case Kind.View:
                {
                    return new ViewUpdateNode( updateHandler, (ViewObject)data );
                }
                case Kind.ViewCameraLink:
                {
                    return new ViewCameraLinkUpdateNode( updateHandler, (ViewCameraLinkObject)data );
                }
                case Kind.ViewTrackerLink:
                {
                    return new ViewTrackerLinkUpdateNode( updateHandler, (ViewTrackerLinkObject)data );
                }
                case Kind.WeatherStationCommand:
                {
                    return new WeatherStationCommandUpdateNode( updateHandler, (WeatherStationCommandObject)data );
                }
                case Kind.WeatherStationCommandReply:
                {
                    return new WeatherStationCommandReplyUpdateNode( updateHandler, (WeatherStationCommandReplyObject)data );
                }
                case Kind.WeatherStationConfiguration:
                {
                    return new WeatherStationConfigurationUpdateNode( updateHandler, (WeatherStationConfigurationObject)data );
                }
                case Kind.CircularZone:
                {
                    return new CircularZoneUpdateNode( updateHandler, (CircularZoneObject)data );
                }
                case Kind.PolygonZone:
                {
                    return new PolygonZoneUpdateNode( updateHandler, (PolygonZoneObject)data );
                }
                case Kind.ZoneExceptions:
                {
                    return new ZoneExceptionsUpdateNode( updateHandler, (ZoneExceptionsObject)data );
                }
                case Kind.ZoneExceptionsVesselLink:
                {
                    return new ZoneExceptionsVesselLinkUpdateNode( updateHandler, (ZoneExceptionsVesselLinkObject)data );
                }
                case Kind.ZoneTrackAlarm:
                {
                    return new ZoneTrackAlarmUpdateNode( updateHandler, (ZoneTrackAlarmObject)data );
                }
                default:
                {
                    throw new ArgumentException($"Cannot create an update node for kind={kind}.", "kind");
                }
            }
        }
    }
    public class SqlServerUpdateHandler : SqlServerUpdateHandlerBase<Kind>
    {
        public SqlServerUpdateHandler([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] StoredProcedures storedProcedures, [DisallowNull] UpdateData<Kind> updateData, [DisallowNull] SqlServerUpdateNodeFactory updateNodeFactory)
            : base( loggerFactory, storedProcedures, updateData, updateNodeFactory )
        {
        }
    }
}
