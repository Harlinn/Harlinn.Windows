using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.IO;
using System.Runtime.CompilerServices;

using Microsoft.Extensions.Logging;

using Harlinn.Common.Core.Net;
using Harlinn.Common.Core.Net.Collections.Generic;
using Harlinn.Common.Core.Net.Entities;

using Barrelman.Data.Types;

namespace Barrelman.Data.Entities.Changes
{
    public class AircraftTypeByNameEntityIndex
    {
        readonly SortedWeakReferenceList<string, AircraftTypeEntity> _entries = new SortedWeakReferenceList<string, AircraftTypeEntity>( );

        public AircraftTypeByNameEntityIndex( )
        {
        }

        public void Add( AircraftTypeEntity entity )
        {
            if( _entries.TryGetValue(entity.Name, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Name, new WeakReference<AircraftTypeEntity>( entity, false ) );
            }
        }

        public bool GetByName( string name, out AircraftTypeEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( name, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( name );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(string key, [DisallowNull] IList<AircraftTypeEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(string key, [DisallowNull] IList<AircraftTypeEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<AircraftTypeEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<AircraftTypeEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class AisDeviceCommandByAisDeviceAndTimestampEntityIndex
    {
        public class ByAisDevice
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AisDeviceCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<AisDeviceCommandEntity>>( );
        }
    }

    public class AisDeviceCommandByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AisDeviceCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<AisDeviceCommandEntity>>( );
        }
    }

    public class AisDeviceCommandByReplyEntityIndex
    {
        public class ByReply
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AisDeviceCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<AisDeviceCommandEntity>>( );
        }
    }

    public class AisDeviceCommandByReplyIsNullEntityIndex
    {
    }

    public class AisDeviceCommandReplyByAisDeviceAndTimestampEntityIndex
    {
        public class ByAisDevice
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AisDeviceCommandReplyEntity>> _entries = new SortedListEx<Guid, WeakReference<AisDeviceCommandReplyEntity>>( );
        }
    }

    public class AisDeviceCommandReplyByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AisDeviceCommandReplyEntity>> _entries = new SortedListEx<Guid, WeakReference<AisDeviceCommandReplyEntity>>( );
        }
    }

    public class AisDeviceCommandReplyByCommandEntityIndex
    {
        readonly SortedWeakReferenceList<Guid, AisDeviceCommandReplyEntity> _entries = new SortedWeakReferenceList<Guid, AisDeviceCommandReplyEntity>( );

        public AisDeviceCommandReplyByCommandEntityIndex( )
        {
        }

        public void Add( AisDeviceCommandReplyEntity entity )
        {
            if ( entity.CommandId is Guid command )
            {
                if ( _entries.TryGetValue( command, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( command, new WeakReference<AisDeviceCommandReplyEntity>( entity, false ) );
                }
            }
            else
            {
                throw new ArgumentException( "entity.CommandId is null.", nameof( entity ) );
            }
        }

        public bool GetByCommandId( Guid command, out AisDeviceCommandReplyEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( command, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( command );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(Guid key, [DisallowNull] IList<AisDeviceCommandReplyEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(Guid key, [DisallowNull] IList<AisDeviceCommandReplyEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<AisDeviceCommandReplyEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<AisDeviceCommandReplyEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class AisDeviceCommandReplyByCommandIsNullEntityIndex
    {
    }

    public class AisDeviceConfigurationByAisDeviceAndTimestampEntityIndex
    {
        public class ByAisDevice
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, AisDeviceConfigurationEntity> _entries = new SortedWeakReferenceList<DateTime, AisDeviceConfigurationEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( AisDeviceConfigurationEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<AisDeviceConfigurationEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out AisDeviceConfigurationEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<AisDeviceConfigurationEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<AisDeviceConfigurationEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<AisDeviceConfigurationEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<AisDeviceConfigurationEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class AisDeviceConfigurationByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AisDeviceConfigurationEntity>> _entries = new SortedListEx<Guid, WeakReference<AisDeviceConfigurationEntity>>( );
        }
    }

    public class AisDeviceRawMessageByAisDeviceAndTimestampEntityIndex
    {
        public class ByAisDevice
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AisDeviceRawMessageEntity>> _entries = new SortedListEx<Guid, WeakReference<AisDeviceRawMessageEntity>>( );
        }
    }

    public class AisDeviceRawMessageByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AisDeviceRawMessageEntity>> _entries = new SortedListEx<Guid, WeakReference<AisDeviceRawMessageEntity>>( );
        }
    }

    public class AisDeviceRawSentenceByAisDeviceAndTimestampEntityIndex
    {
        public class ByAisDevice
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AisDeviceRawSentenceEntity>> _entries = new SortedListEx<Guid, WeakReference<AisDeviceRawSentenceEntity>>( );
        }
    }

    public class AisDeviceRawSentenceByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AisDeviceRawSentenceEntity>> _entries = new SortedListEx<Guid, WeakReference<AisDeviceRawSentenceEntity>>( );
        }
    }

    public class AisMessageByAisDeviceAndReceivedTimestampEntityIndex
    {
        public class ByAisDevice
        {
            readonly SortedListEx<Guid, ByReceivedTimestamp> _entries = new SortedListEx<Guid, ByReceivedTimestamp>( );
        }
        public class ByReceivedTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, AisMessageEntity> _entries = new SortedWeakReferenceList<DateTime, AisMessageEntity>( );

            public ByReceivedTimestamp( )
            {
            }

            public void Add( AisMessageEntity entity )
            {
                if( _entries.TryGetValue(entity.ReceivedTimestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.ReceivedTimestamp, new WeakReference<AisMessageEntity>( entity, false ) );
                }
            }

            public bool GetByReceivedTimestamp( DateTime receivedTimestamp, out AisMessageEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( receivedTimestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( receivedTimestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<AisMessageEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<AisMessageEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<AisMessageEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<AisMessageEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class AisMessageByReceivedTimestampEntityIndex
    {
        public class ByReceivedTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AisMessageEntity>> _entries = new SortedListEx<Guid, WeakReference<AisMessageEntity>>( );
        }
    }

    public class AisMessageByMmsiAndMessageSequenceNumberEntityIndex
    {
        public class ByMmsi
        {
            readonly SortedListEx<Guid, ByMessageSequenceNumber> _entries = new SortedListEx<Guid, ByMessageSequenceNumber>( );
        }
        public class ByMessageSequenceNumber
        {
            readonly SortedListEx<long, ById> _entries = new SortedListEx<long, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AisMessageEntity>> _entries = new SortedListEx<Guid, WeakReference<AisMessageEntity>>( );
        }
    }

    public class AisMessageByMmsiIsNullAndMessageSequenceNumberEntityIndex
    {
    }

    public class AisAddressedSafetyRelatedMessageByDestinationMmsiEntityIndex
    {
        public class ByDestinationMmsi
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AisAddressedSafetyRelatedMessageEntity>> _entries = new SortedListEx<Guid, WeakReference<AisAddressedSafetyRelatedMessageEntity>>( );
        }
    }

    public class AisAddressedSafetyRelatedMessageByDestinationMmsiIsNullEntityIndex
    {
    }

    public class AisBinaryAddressedMessageByDestinationMmsiEntityIndex
    {
        public class ByDestinationMmsi
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AisBinaryAddressedMessageEntity>> _entries = new SortedListEx<Guid, WeakReference<AisBinaryAddressedMessageEntity>>( );
        }
    }

    public class AisBinaryAddressedMessageByDestinationMmsiIsNullEntityIndex
    {
    }

    public class AisExtendedClassBCsPositionReportMessageByNameEntityIndex
    {
        public class ByName
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AisExtendedClassBCsPositionReportMessageEntity>> _entries = new SortedListEx<Guid, WeakReference<AisExtendedClassBCsPositionReportMessageEntity>>( );
        }
    }

    public class AisExtendedClassBCsPositionReportMessageByNameIsNullEntityIndex
    {
    }

    public class AisStaticAndVoyageRelatedDataMessageByImoNumberEntityIndex
    {
        public class ByImoNumber
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AisStaticAndVoyageRelatedDataMessageEntity>> _entries = new SortedListEx<Guid, WeakReference<AisStaticAndVoyageRelatedDataMessageEntity>>( );
        }
    }

    public class AisStaticAndVoyageRelatedDataMessageByImoNumberIsNullEntityIndex
    {
    }

    public class AisStaticAndVoyageRelatedDataMessageByCallsignEntityIndex
    {
        public class ByCallsign
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AisStaticAndVoyageRelatedDataMessageEntity>> _entries = new SortedListEx<Guid, WeakReference<AisStaticAndVoyageRelatedDataMessageEntity>>( );
        }
    }

    public class AisStaticAndVoyageRelatedDataMessageByCallsignIsNullEntityIndex
    {
    }

    public class AisStaticAndVoyageRelatedDataMessageByShipNameEntityIndex
    {
        public class ByShipName
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AisStaticAndVoyageRelatedDataMessageEntity>> _entries = new SortedListEx<Guid, WeakReference<AisStaticAndVoyageRelatedDataMessageEntity>>( );
        }
    }

    public class AisStaticAndVoyageRelatedDataMessageByShipNameIsNullEntityIndex
    {
    }

    public class AisStaticDataReportPartAMessageByShipNameEntityIndex
    {
        public class ByShipName
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AisStaticDataReportPartAMessageEntity>> _entries = new SortedListEx<Guid, WeakReference<AisStaticDataReportPartAMessageEntity>>( );
        }
    }

    public class AisStaticDataReportPartAMessageByShipNameIsNullEntityIndex
    {
    }

    public class AisStaticDataReportPartBMessageByCallsignEntityIndex
    {
        public class ByCallsign
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AisStaticDataReportPartBMessageEntity>> _entries = new SortedListEx<Guid, WeakReference<AisStaticDataReportPartBMessageEntity>>( );
        }
    }

    public class AisStaticDataReportPartBMessageByCallsignIsNullEntityIndex
    {
    }

    public class AisStaticDataReportPartBMessageByMothershipMmsiEntityIndex
    {
        public class ByMothershipMmsi
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AisStaticDataReportPartBMessageEntity>> _entries = new SortedListEx<Guid, WeakReference<AisStaticDataReportPartBMessageEntity>>( );
        }
    }

    public class AisStaticDataReportPartBMessageByMothershipMmsiIsNullEntityIndex
    {
    }

    public class AlarmStateChangeByAlarmAndTimestampEntityIndex
    {
        public class ByAlarm
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, AlarmStateChangeEntity> _entries = new SortedWeakReferenceList<DateTime, AlarmStateChangeEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( AlarmStateChangeEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<AlarmStateChangeEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out AlarmStateChangeEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<AlarmStateChangeEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<AlarmStateChangeEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<AlarmStateChangeEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<AlarmStateChangeEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class AlarmStateChangeByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AlarmStateChangeEntity>> _entries = new SortedListEx<Guid, WeakReference<AlarmStateChangeEntity>>( );
        }
    }

    public class BaseStationTypeByNameEntityIndex
    {
        readonly SortedWeakReferenceList<string, BaseStationTypeEntity> _entries = new SortedWeakReferenceList<string, BaseStationTypeEntity>( );

        public BaseStationTypeByNameEntityIndex( )
        {
        }

        public void Add( BaseStationTypeEntity entity )
        {
            if( _entries.TryGetValue(entity.Name, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Name, new WeakReference<BaseStationTypeEntity>( entity, false ) );
            }
        }

        public bool GetByName( string name, out BaseStationTypeEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( name, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( name );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(string key, [DisallowNull] IList<BaseStationTypeEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(string key, [DisallowNull] IList<BaseStationTypeEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<BaseStationTypeEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<BaseStationTypeEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class BinaryTimeseriesValueByTimeseriesAndTimestampEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, BinaryTimeseriesValueEntity> _entries = new SortedWeakReferenceList<DateTime, BinaryTimeseriesValueEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( BinaryTimeseriesValueEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<BinaryTimeseriesValueEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out BinaryTimeseriesValueEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<BinaryTimeseriesValueEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<BinaryTimeseriesValueEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<BinaryTimeseriesValueEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<BinaryTimeseriesValueEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class BinaryTimeseriesValueByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<BinaryTimeseriesValueEntity>> _entries = new SortedListEx<Guid, WeakReference<BinaryTimeseriesValueEntity>>( );
        }
    }

    public class BookmarkByViewEntityIndex
    {
        public class ByView
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<BookmarkEntity>> _entries = new SortedListEx<Guid, WeakReference<BookmarkEntity>>( );
        }
    }

    public class BooleanTimeseriesValueByTimeseriesAndTimestampEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, BooleanTimeseriesValueEntity> _entries = new SortedWeakReferenceList<DateTime, BooleanTimeseriesValueEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( BooleanTimeseriesValueEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<BooleanTimeseriesValueEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out BooleanTimeseriesValueEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<BooleanTimeseriesValueEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<BooleanTimeseriesValueEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<BooleanTimeseriesValueEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<BooleanTimeseriesValueEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class BooleanTimeseriesValueByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<BooleanTimeseriesValueEntity>> _entries = new SortedListEx<Guid, WeakReference<BooleanTimeseriesValueEntity>>( );
        }
    }

    public class ByteTimeseriesValueByTimeseriesAndTimestampEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, ByteTimeseriesValueEntity> _entries = new SortedWeakReferenceList<DateTime, ByteTimeseriesValueEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( ByteTimeseriesValueEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<ByteTimeseriesValueEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out ByteTimeseriesValueEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<ByteTimeseriesValueEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<ByteTimeseriesValueEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<ByteTimeseriesValueEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<ByteTimeseriesValueEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class ByteTimeseriesValueByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<ByteTimeseriesValueEntity>> _entries = new SortedListEx<Guid, WeakReference<ByteTimeseriesValueEntity>>( );
        }
    }

    public class CameraCommandByCameraAndTimestampEntityIndex
    {
        public class ByCamera
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<CameraCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<CameraCommandEntity>>( );
        }
    }

    public class CameraCommandByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<CameraCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<CameraCommandEntity>>( );
        }
    }

    public class CameraCommandByReplyEntityIndex
    {
        public class ByReply
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<CameraCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<CameraCommandEntity>>( );
        }
    }

    public class CameraCommandByReplyIsNullEntityIndex
    {
    }

    public class CameraCommandReplyByCameraAndTimestampEntityIndex
    {
        public class ByCamera
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<CameraCommandReplyEntity>> _entries = new SortedListEx<Guid, WeakReference<CameraCommandReplyEntity>>( );
        }
    }

    public class CameraCommandReplyByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<CameraCommandReplyEntity>> _entries = new SortedListEx<Guid, WeakReference<CameraCommandReplyEntity>>( );
        }
    }

    public class CameraCommandReplyByCommandEntityIndex
    {
        readonly SortedWeakReferenceList<Guid, CameraCommandReplyEntity> _entries = new SortedWeakReferenceList<Guid, CameraCommandReplyEntity>( );

        public CameraCommandReplyByCommandEntityIndex( )
        {
        }

        public void Add( CameraCommandReplyEntity entity )
        {
            if ( entity.CommandId is Guid command )
            {
                if ( _entries.TryGetValue( command, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( command, new WeakReference<CameraCommandReplyEntity>( entity, false ) );
                }
            }
            else
            {
                throw new ArgumentException( "entity.CommandId is null.", nameof( entity ) );
            }
        }

        public bool GetByCommandId( Guid command, out CameraCommandReplyEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( command, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( command );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(Guid key, [DisallowNull] IList<CameraCommandReplyEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(Guid key, [DisallowNull] IList<CameraCommandReplyEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<CameraCommandReplyEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<CameraCommandReplyEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class CameraCommandReplyByCommandIsNullEntityIndex
    {
    }

    public class CameraConfigurationByCameraAndTimestampEntityIndex
    {
        public class ByCamera
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, CameraConfigurationEntity> _entries = new SortedWeakReferenceList<DateTime, CameraConfigurationEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( CameraConfigurationEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<CameraConfigurationEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out CameraConfigurationEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<CameraConfigurationEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<CameraConfigurationEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<CameraConfigurationEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<CameraConfigurationEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class CameraConfigurationByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<CameraConfigurationEntity>> _entries = new SortedListEx<Guid, WeakReference<CameraConfigurationEntity>>( );
        }
    }

    public class CameraPanCalibrationByCameraAndTimestampEntityIndex
    {
        public class ByCamera
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, CameraPanCalibrationEntity> _entries = new SortedWeakReferenceList<DateTime, CameraPanCalibrationEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( CameraPanCalibrationEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<CameraPanCalibrationEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out CameraPanCalibrationEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<CameraPanCalibrationEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<CameraPanCalibrationEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<CameraPanCalibrationEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<CameraPanCalibrationEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class CameraPanCalibrationByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<CameraPanCalibrationEntity>> _entries = new SortedListEx<Guid, WeakReference<CameraPanCalibrationEntity>>( );
        }
    }

    public class CameraPanCalibrationValueByPanCalibrationAndPanAngleEntityIndex
    {
        public class ByPanCalibration
        {
            readonly SortedListEx<Guid, ByPanAngle> _entries = new SortedListEx<Guid, ByPanAngle>( );
        }
        public class ByPanAngle
        {
            readonly SortedWeakReferenceList<double, CameraPanCalibrationValueEntity> _entries = new SortedWeakReferenceList<double, CameraPanCalibrationValueEntity>( );

            public ByPanAngle( )
            {
            }

            public void Add( CameraPanCalibrationValueEntity entity )
            {
                if( _entries.TryGetValue(entity.PanAngle, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.PanAngle, new WeakReference<CameraPanCalibrationValueEntity>( entity, false ) );
                }
            }

            public bool GetByPanAngle( double panAngle, out CameraPanCalibrationValueEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( panAngle, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( panAngle );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(double key, [DisallowNull] IList<CameraPanCalibrationValueEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(double key, [DisallowNull] IList<CameraPanCalibrationValueEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(double firstKey, double lastKey, [DisallowNull] IList<CameraPanCalibrationValueEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<CameraPanCalibrationValueEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class CameraStatusByCameraAndTimestampEntityIndex
    {
        public class ByCamera
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, CameraStatusEntity> _entries = new SortedWeakReferenceList<DateTime, CameraStatusEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( CameraStatusEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<CameraStatusEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out CameraStatusEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<CameraStatusEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<CameraStatusEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<CameraStatusEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<CameraStatusEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class CameraStatusByTrackAndTimestampEntityIndex
    {
        public class ByTrack
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, CameraStatusEntity> _entries = new SortedWeakReferenceList<DateTime, CameraStatusEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( CameraStatusEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<CameraStatusEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out CameraStatusEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<CameraStatusEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<CameraStatusEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<CameraStatusEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<CameraStatusEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class CameraStatusByTrackIsNullAndTimestampEntityIndex
    {
    }

    public class CameraStatusByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<CameraStatusEntity>> _entries = new SortedListEx<Guid, WeakReference<CameraStatusEntity>>( );
        }
    }

    public class CameraTiltCalibrationByCameraAndTimestampEntityIndex
    {
        public class ByCamera
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, CameraTiltCalibrationEntity> _entries = new SortedWeakReferenceList<DateTime, CameraTiltCalibrationEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( CameraTiltCalibrationEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<CameraTiltCalibrationEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out CameraTiltCalibrationEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<CameraTiltCalibrationEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<CameraTiltCalibrationEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<CameraTiltCalibrationEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<CameraTiltCalibrationEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class CameraTiltCalibrationByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<CameraTiltCalibrationEntity>> _entries = new SortedListEx<Guid, WeakReference<CameraTiltCalibrationEntity>>( );
        }
    }

    public class CameraTiltCalibrationValueByTiltCalibrationAndPanAngleEntityIndex
    {
        public class ByTiltCalibration
        {
            readonly SortedListEx<Guid, ByPanAngle> _entries = new SortedListEx<Guid, ByPanAngle>( );
        }
        public class ByPanAngle
        {
            readonly SortedWeakReferenceList<double, CameraTiltCalibrationValueEntity> _entries = new SortedWeakReferenceList<double, CameraTiltCalibrationValueEntity>( );

            public ByPanAngle( )
            {
            }

            public void Add( CameraTiltCalibrationValueEntity entity )
            {
                if( _entries.TryGetValue(entity.PanAngle, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.PanAngle, new WeakReference<CameraTiltCalibrationValueEntity>( entity, false ) );
                }
            }

            public bool GetByPanAngle( double panAngle, out CameraTiltCalibrationValueEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( panAngle, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( panAngle );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(double key, [DisallowNull] IList<CameraTiltCalibrationValueEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(double key, [DisallowNull] IList<CameraTiltCalibrationValueEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(double firstKey, double lastKey, [DisallowNull] IList<CameraTiltCalibrationValueEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<CameraTiltCalibrationValueEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class CameraZoomCalibrationByCameraAndTimestampEntityIndex
    {
        public class ByCamera
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, CameraZoomCalibrationEntity> _entries = new SortedWeakReferenceList<DateTime, CameraZoomCalibrationEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( CameraZoomCalibrationEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<CameraZoomCalibrationEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out CameraZoomCalibrationEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<CameraZoomCalibrationEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<CameraZoomCalibrationEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<CameraZoomCalibrationEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<CameraZoomCalibrationEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class CameraZoomCalibrationByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<CameraZoomCalibrationEntity>> _entries = new SortedListEx<Guid, WeakReference<CameraZoomCalibrationEntity>>( );
        }
    }

    public class CameraZoomCalibrationValueByZoomCalibrationAndFocalLengthEntityIndex
    {
        public class ByZoomCalibration
        {
            readonly SortedListEx<Guid, ByFocalLength> _entries = new SortedListEx<Guid, ByFocalLength>( );
        }
        public class ByFocalLength
        {
            readonly SortedWeakReferenceList<double, CameraZoomCalibrationValueEntity> _entries = new SortedWeakReferenceList<double, CameraZoomCalibrationValueEntity>( );

            public ByFocalLength( )
            {
            }

            public void Add( CameraZoomCalibrationValueEntity entity )
            {
                if( _entries.TryGetValue(entity.FocalLength, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.FocalLength, new WeakReference<CameraZoomCalibrationValueEntity>( entity, false ) );
                }
            }

            public bool GetByFocalLength( double focalLength, out CameraZoomCalibrationValueEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( focalLength, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( focalLength );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(double key, [DisallowNull] IList<CameraZoomCalibrationValueEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(double key, [DisallowNull] IList<CameraZoomCalibrationValueEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(double firstKey, double lastKey, [DisallowNull] IList<CameraZoomCalibrationValueEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<CameraZoomCalibrationValueEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class CatalogElementByCatalogAndNameEntityIndex
    {
        public class ByCatalog
        {
            readonly SortedListEx<Guid, ByName> _entries = new SortedListEx<Guid, ByName>( );
        }
        public class ByName
        {
            readonly SortedWeakReferenceList<string, CatalogElementEntity> _entries = new SortedWeakReferenceList<string, CatalogElementEntity>( );

            public ByName( )
            {
            }

            public void Add( CatalogElementEntity entity )
            {
                if( _entries.TryGetValue(entity.Name, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Name, new WeakReference<CatalogElementEntity>( entity, false ) );
                }
            }

            public bool GetByName( string name, out CatalogElementEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( name, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( name );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(string key, [DisallowNull] IList<CatalogElementEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(string key, [DisallowNull] IList<CatalogElementEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<CatalogElementEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<CatalogElementEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class CatalogElementByCatalogIsNullAndNameEntityIndex
    {
    }

    public class ElementByElementTypeEntityIndex
    {
        public class ByElementType
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<ElementEntity>> _entries = new SortedListEx<Guid, WeakReference<ElementEntity>>( );
        }
    }

    public class ElementByElementTypeIsNullEntityIndex
    {
    }

    public class CountryByNameEntityIndex
    {
        readonly SortedWeakReferenceList<string, CountryEntity> _entries = new SortedWeakReferenceList<string, CountryEntity>( );

        public CountryByNameEntityIndex( )
        {
        }

        public void Add( CountryEntity entity )
        {
            if( _entries.TryGetValue(entity.Name, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Name, new WeakReference<CountryEntity>( entity, false ) );
            }
        }

        public bool GetByName( string name, out CountryEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( name, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( name );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(string key, [DisallowNull] IList<CountryEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(string key, [DisallowNull] IList<CountryEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<CountryEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<CountryEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class CountryByCodeEntityIndex
    {
        readonly SortedWeakReferenceList<int, CountryEntity> _entries = new SortedWeakReferenceList<int, CountryEntity>( );

        public CountryByCodeEntityIndex( )
        {
        }

        public void Add( CountryEntity entity )
        {
            if( _entries.TryGetValue(entity.Code, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Code, new WeakReference<CountryEntity>( entity, false ) );
            }
        }

        public bool GetByCode( int code, out CountryEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( code, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( code );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(int key, [DisallowNull] IList<CountryEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(int key, [DisallowNull] IList<CountryEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(int firstKey, int lastKey, [DisallowNull] IList<CountryEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<CountryEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class CountryByAlpha2EntityIndex
    {
        readonly SortedWeakReferenceList<string, CountryEntity> _entries = new SortedWeakReferenceList<string, CountryEntity>( );

        public CountryByAlpha2EntityIndex( )
        {
        }

        public void Add( CountryEntity entity )
        {
            if( _entries.TryGetValue(entity.Alpha2, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Alpha2, new WeakReference<CountryEntity>( entity, false ) );
            }
        }

        public bool GetByAlpha2( string alpha2, out CountryEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( alpha2, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( alpha2 );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(string key, [DisallowNull] IList<CountryEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(string key, [DisallowNull] IList<CountryEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<CountryEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<CountryEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class CountryByAlpha3EntityIndex
    {
        readonly SortedWeakReferenceList<string, CountryEntity> _entries = new SortedWeakReferenceList<string, CountryEntity>( );

        public CountryByAlpha3EntityIndex( )
        {
        }

        public void Add( CountryEntity entity )
        {
            if( _entries.TryGetValue(entity.Alpha3, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Alpha3, new WeakReference<CountryEntity>( entity, false ) );
            }
        }

        public bool GetByAlpha3( string alpha3, out CountryEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( alpha3, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( alpha3 );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(string key, [DisallowNull] IList<CountryEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(string key, [DisallowNull] IList<CountryEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<CountryEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<CountryEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class DateTimeTimeseriesValueByTimeseriesAndTimestampEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, DateTimeTimeseriesValueEntity> _entries = new SortedWeakReferenceList<DateTime, DateTimeTimeseriesValueEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( DateTimeTimeseriesValueEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<DateTimeTimeseriesValueEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out DateTimeTimeseriesValueEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<DateTimeTimeseriesValueEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<DateTimeTimeseriesValueEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<DateTimeTimeseriesValueEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<DateTimeTimeseriesValueEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class DateTimeTimeseriesValueByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<DateTimeTimeseriesValueEntity>> _entries = new SortedListEx<Guid, WeakReference<DateTimeTimeseriesValueEntity>>( );
        }
    }

    public class DeviceHostByNameEntityIndex
    {
        readonly SortedWeakReferenceList<string, DeviceHostEntity> _entries = new SortedWeakReferenceList<string, DeviceHostEntity>( );

        public DeviceHostByNameEntityIndex( )
        {
        }

        public void Add( DeviceHostEntity entity )
        {
            if( _entries.TryGetValue(entity.Name, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Name, new WeakReference<DeviceHostEntity>( entity, false ) );
            }
        }

        public bool GetByName( string name, out DeviceHostEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( name, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( name );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(string key, [DisallowNull] IList<DeviceHostEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(string key, [DisallowNull] IList<DeviceHostEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<DeviceHostEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<DeviceHostEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class DeviceHostConfigurationByHostAndTimestampEntityIndex
    {
        public class ByHost
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, DeviceHostConfigurationEntity> _entries = new SortedWeakReferenceList<DateTime, DeviceHostConfigurationEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( DeviceHostConfigurationEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<DeviceHostConfigurationEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out DeviceHostConfigurationEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<DeviceHostConfigurationEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<DeviceHostConfigurationEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<DeviceHostConfigurationEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<DeviceHostConfigurationEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class DeviceHostConfigurationByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<DeviceHostConfigurationEntity>> _entries = new SortedListEx<Guid, WeakReference<DeviceHostConfigurationEntity>>( );
        }
    }

    public class DoubleTimeseriesValueByTimeseriesAndTimestampEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, DoubleTimeseriesValueEntity> _entries = new SortedWeakReferenceList<DateTime, DoubleTimeseriesValueEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( DoubleTimeseriesValueEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<DoubleTimeseriesValueEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out DoubleTimeseriesValueEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<DoubleTimeseriesValueEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<DoubleTimeseriesValueEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<DoubleTimeseriesValueEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<DoubleTimeseriesValueEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class DoubleTimeseriesValueByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<DoubleTimeseriesValueEntity>> _entries = new SortedListEx<Guid, WeakReference<DoubleTimeseriesValueEntity>>( );
        }
    }

    public class FacilityTypeByNameEntityIndex
    {
        readonly SortedWeakReferenceList<string, FacilityTypeEntity> _entries = new SortedWeakReferenceList<string, FacilityTypeEntity>( );

        public FacilityTypeByNameEntityIndex( )
        {
        }

        public void Add( FacilityTypeEntity entity )
        {
            if( _entries.TryGetValue(entity.Name, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Name, new WeakReference<FacilityTypeEntity>( entity, false ) );
            }
        }

        public bool GetByName( string name, out FacilityTypeEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( name, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( name );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(string key, [DisallowNull] IList<FacilityTypeEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(string key, [DisallowNull] IList<FacilityTypeEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<FacilityTypeEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<FacilityTypeEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class GeoPosition2DTimeseriesValueByTimeseriesAndTimestampEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, GeoPosition2DTimeseriesValueEntity> _entries = new SortedWeakReferenceList<DateTime, GeoPosition2DTimeseriesValueEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( GeoPosition2DTimeseriesValueEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<GeoPosition2DTimeseriesValueEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out GeoPosition2DTimeseriesValueEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<GeoPosition2DTimeseriesValueEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<GeoPosition2DTimeseriesValueEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<GeoPosition2DTimeseriesValueEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<GeoPosition2DTimeseriesValueEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class GeoPosition2DTimeseriesValueByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<GeoPosition2DTimeseriesValueEntity>> _entries = new SortedListEx<Guid, WeakReference<GeoPosition2DTimeseriesValueEntity>>( );
        }
    }

    public class GeoPosition3DTimeseriesValueByTimeseriesAndTimestampEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, GeoPosition3DTimeseriesValueEntity> _entries = new SortedWeakReferenceList<DateTime, GeoPosition3DTimeseriesValueEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( GeoPosition3DTimeseriesValueEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<GeoPosition3DTimeseriesValueEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out GeoPosition3DTimeseriesValueEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<GeoPosition3DTimeseriesValueEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<GeoPosition3DTimeseriesValueEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<GeoPosition3DTimeseriesValueEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<GeoPosition3DTimeseriesValueEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class GeoPosition3DTimeseriesValueByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<GeoPosition3DTimeseriesValueEntity>> _entries = new SortedListEx<Guid, WeakReference<GeoPosition3DTimeseriesValueEntity>>( );
        }
    }

    public class GNSSDeviceCommandByGNSSDeviceAndTimestampEntityIndex
    {
        public class ByGNSSDevice
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<GNSSDeviceCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<GNSSDeviceCommandEntity>>( );
        }
    }

    public class GNSSDeviceCommandByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<GNSSDeviceCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<GNSSDeviceCommandEntity>>( );
        }
    }

    public class GNSSDeviceCommandByReplyEntityIndex
    {
        public class ByReply
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<GNSSDeviceCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<GNSSDeviceCommandEntity>>( );
        }
    }

    public class GNSSDeviceCommandByReplyIsNullEntityIndex
    {
    }

    public class GNSSDeviceCommandReplyByGNSSDeviceAndTimestampEntityIndex
    {
        public class ByGNSSDevice
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<GNSSDeviceCommandReplyEntity>> _entries = new SortedListEx<Guid, WeakReference<GNSSDeviceCommandReplyEntity>>( );
        }
    }

    public class GNSSDeviceCommandReplyByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<GNSSDeviceCommandReplyEntity>> _entries = new SortedListEx<Guid, WeakReference<GNSSDeviceCommandReplyEntity>>( );
        }
    }

    public class GNSSDeviceCommandReplyByCommandEntityIndex
    {
        readonly SortedWeakReferenceList<Guid, GNSSDeviceCommandReplyEntity> _entries = new SortedWeakReferenceList<Guid, GNSSDeviceCommandReplyEntity>( );

        public GNSSDeviceCommandReplyByCommandEntityIndex( )
        {
        }

        public void Add( GNSSDeviceCommandReplyEntity entity )
        {
            if ( entity.CommandId is Guid command )
            {
                if ( _entries.TryGetValue( command, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( command, new WeakReference<GNSSDeviceCommandReplyEntity>( entity, false ) );
                }
            }
            else
            {
                throw new ArgumentException( "entity.CommandId is null.", nameof( entity ) );
            }
        }

        public bool GetByCommandId( Guid command, out GNSSDeviceCommandReplyEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( command, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( command );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(Guid key, [DisallowNull] IList<GNSSDeviceCommandReplyEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(Guid key, [DisallowNull] IList<GNSSDeviceCommandReplyEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<GNSSDeviceCommandReplyEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<GNSSDeviceCommandReplyEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class GNSSDeviceCommandReplyByCommandIsNullEntityIndex
    {
    }

    public class GNSSDeviceConfigurationByGNSSDeviceAndTimestampEntityIndex
    {
        public class ByGNSSDevice
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, GNSSDeviceConfigurationEntity> _entries = new SortedWeakReferenceList<DateTime, GNSSDeviceConfigurationEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( GNSSDeviceConfigurationEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<GNSSDeviceConfigurationEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out GNSSDeviceConfigurationEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<GNSSDeviceConfigurationEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<GNSSDeviceConfigurationEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<GNSSDeviceConfigurationEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<GNSSDeviceConfigurationEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class GNSSDeviceConfigurationByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<GNSSDeviceConfigurationEntity>> _entries = new SortedListEx<Guid, WeakReference<GNSSDeviceConfigurationEntity>>( );
        }
    }

    public class GuidTimeseriesValueByTimeseriesAndTimestampEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, GuidTimeseriesValueEntity> _entries = new SortedWeakReferenceList<DateTime, GuidTimeseriesValueEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( GuidTimeseriesValueEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<GuidTimeseriesValueEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out GuidTimeseriesValueEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<GuidTimeseriesValueEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<GuidTimeseriesValueEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<GuidTimeseriesValueEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<GuidTimeseriesValueEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class GuidTimeseriesValueByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<GuidTimeseriesValueEntity>> _entries = new SortedListEx<Guid, WeakReference<GuidTimeseriesValueEntity>>( );
        }
    }

    public class GyroDeviceCommandByGyroDeviceAndTimestampEntityIndex
    {
        public class ByGyroDevice
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<GyroDeviceCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<GyroDeviceCommandEntity>>( );
        }
    }

    public class GyroDeviceCommandByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<GyroDeviceCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<GyroDeviceCommandEntity>>( );
        }
    }

    public class GyroDeviceCommandByReplyEntityIndex
    {
        public class ByReply
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<GyroDeviceCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<GyroDeviceCommandEntity>>( );
        }
    }

    public class GyroDeviceCommandByReplyIsNullEntityIndex
    {
    }

    public class GyroDeviceCommandReplyByGyroDeviceAndTimestampEntityIndex
    {
        public class ByGyroDevice
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<GyroDeviceCommandReplyEntity>> _entries = new SortedListEx<Guid, WeakReference<GyroDeviceCommandReplyEntity>>( );
        }
    }

    public class GyroDeviceCommandReplyByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<GyroDeviceCommandReplyEntity>> _entries = new SortedListEx<Guid, WeakReference<GyroDeviceCommandReplyEntity>>( );
        }
    }

    public class GyroDeviceCommandReplyByCommandEntityIndex
    {
        readonly SortedWeakReferenceList<Guid, GyroDeviceCommandReplyEntity> _entries = new SortedWeakReferenceList<Guid, GyroDeviceCommandReplyEntity>( );

        public GyroDeviceCommandReplyByCommandEntityIndex( )
        {
        }

        public void Add( GyroDeviceCommandReplyEntity entity )
        {
            if ( entity.CommandId is Guid command )
            {
                if ( _entries.TryGetValue( command, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( command, new WeakReference<GyroDeviceCommandReplyEntity>( entity, false ) );
                }
            }
            else
            {
                throw new ArgumentException( "entity.CommandId is null.", nameof( entity ) );
            }
        }

        public bool GetByCommandId( Guid command, out GyroDeviceCommandReplyEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( command, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( command );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(Guid key, [DisallowNull] IList<GyroDeviceCommandReplyEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(Guid key, [DisallowNull] IList<GyroDeviceCommandReplyEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<GyroDeviceCommandReplyEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<GyroDeviceCommandReplyEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class GyroDeviceCommandReplyByCommandIsNullEntityIndex
    {
    }

    public class GyroDeviceConfigurationByGyroDeviceAndTimestampEntityIndex
    {
        public class ByGyroDevice
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, GyroDeviceConfigurationEntity> _entries = new SortedWeakReferenceList<DateTime, GyroDeviceConfigurationEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( GyroDeviceConfigurationEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<GyroDeviceConfigurationEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out GyroDeviceConfigurationEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<GyroDeviceConfigurationEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<GyroDeviceConfigurationEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<GyroDeviceConfigurationEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<GyroDeviceConfigurationEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class GyroDeviceConfigurationByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<GyroDeviceConfigurationEntity>> _entries = new SortedListEx<Guid, WeakReference<GyroDeviceConfigurationEntity>>( );
        }
    }

    public class CallsignByIdentifierEntityIndex
    {
        readonly SortedWeakReferenceList<string, CallsignEntity> _entries = new SortedWeakReferenceList<string, CallsignEntity>( );

        public CallsignByIdentifierEntityIndex( )
        {
        }

        public void Add( CallsignEntity entity )
        {
            if( _entries.TryGetValue(entity.Identifier, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Identifier, new WeakReference<CallsignEntity>( entity, false ) );
            }
        }

        public bool GetByIdentifier( string identifier, out CallsignEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( identifier, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( identifier );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(string key, [DisallowNull] IList<CallsignEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(string key, [DisallowNull] IList<CallsignEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<CallsignEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<CallsignEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class InternationalMaritimeOrganizationNumberByIdentifierEntityIndex
    {
        readonly SortedWeakReferenceList<long, InternationalMaritimeOrganizationNumberEntity> _entries = new SortedWeakReferenceList<long, InternationalMaritimeOrganizationNumberEntity>( );

        public InternationalMaritimeOrganizationNumberByIdentifierEntityIndex( )
        {
        }

        public void Add( InternationalMaritimeOrganizationNumberEntity entity )
        {
            if( _entries.TryGetValue(entity.Identifier, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Identifier, new WeakReference<InternationalMaritimeOrganizationNumberEntity>( entity, false ) );
            }
        }

        public bool GetByIdentifier( long identifier, out InternationalMaritimeOrganizationNumberEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( identifier, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( identifier );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(long key, [DisallowNull] IList<InternationalMaritimeOrganizationNumberEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(long key, [DisallowNull] IList<InternationalMaritimeOrganizationNumberEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(long firstKey, long lastKey, [DisallowNull] IList<InternationalMaritimeOrganizationNumberEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<InternationalMaritimeOrganizationNumberEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class MaritimeMobileServiceIdentityByIdentifierEntityIndex
    {
        readonly SortedWeakReferenceList<long, MaritimeMobileServiceIdentityEntity> _entries = new SortedWeakReferenceList<long, MaritimeMobileServiceIdentityEntity>( );

        public MaritimeMobileServiceIdentityByIdentifierEntityIndex( )
        {
        }

        public void Add( MaritimeMobileServiceIdentityEntity entity )
        {
            if( _entries.TryGetValue(entity.Identifier, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Identifier, new WeakReference<MaritimeMobileServiceIdentityEntity>( entity, false ) );
            }
        }

        public bool GetByIdentifier( long identifier, out MaritimeMobileServiceIdentityEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( identifier, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( identifier );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(long key, [DisallowNull] IList<MaritimeMobileServiceIdentityEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(long key, [DisallowNull] IList<MaritimeMobileServiceIdentityEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(long firstKey, long lastKey, [DisallowNull] IList<MaritimeMobileServiceIdentityEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<MaritimeMobileServiceIdentityEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class NameByTextEntityIndex
    {
        readonly SortedWeakReferenceList<string, NameEntity> _entries = new SortedWeakReferenceList<string, NameEntity>( );

        public NameByTextEntityIndex( )
        {
        }

        public void Add( NameEntity entity )
        {
            if( _entries.TryGetValue(entity.Text, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Text, new WeakReference<NameEntity>( entity, false ) );
            }
        }

        public bool GetByText( string text, out NameEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( text, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( text );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(string key, [DisallowNull] IList<NameEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(string key, [DisallowNull] IList<NameEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<NameEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<NameEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class Int16TimeseriesValueByTimeseriesAndTimestampEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, Int16TimeseriesValueEntity> _entries = new SortedWeakReferenceList<DateTime, Int16TimeseriesValueEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( Int16TimeseriesValueEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<Int16TimeseriesValueEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out Int16TimeseriesValueEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<Int16TimeseriesValueEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<Int16TimeseriesValueEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<Int16TimeseriesValueEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<Int16TimeseriesValueEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class Int16TimeseriesValueByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<Int16TimeseriesValueEntity>> _entries = new SortedListEx<Guid, WeakReference<Int16TimeseriesValueEntity>>( );
        }
    }

    public class Int32TimeseriesValueByTimeseriesAndTimestampEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, Int32TimeseriesValueEntity> _entries = new SortedWeakReferenceList<DateTime, Int32TimeseriesValueEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( Int32TimeseriesValueEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<Int32TimeseriesValueEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out Int32TimeseriesValueEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<Int32TimeseriesValueEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<Int32TimeseriesValueEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<Int32TimeseriesValueEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<Int32TimeseriesValueEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class Int32TimeseriesValueByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<Int32TimeseriesValueEntity>> _entries = new SortedListEx<Guid, WeakReference<Int32TimeseriesValueEntity>>( );
        }
    }

    public class Int64TimeseriesValueByTimeseriesAndTimestampEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, Int64TimeseriesValueEntity> _entries = new SortedWeakReferenceList<DateTime, Int64TimeseriesValueEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( Int64TimeseriesValueEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<Int64TimeseriesValueEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out Int64TimeseriesValueEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<Int64TimeseriesValueEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<Int64TimeseriesValueEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<Int64TimeseriesValueEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<Int64TimeseriesValueEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class Int64TimeseriesValueByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<Int64TimeseriesValueEntity>> _entries = new SortedListEx<Guid, WeakReference<Int64TimeseriesValueEntity>>( );
        }
    }

    public class BaseStationByNameEntityIndex
    {
        readonly SortedWeakReferenceList<string, BaseStationEntity> _entries = new SortedWeakReferenceList<string, BaseStationEntity>( );

        public BaseStationByNameEntityIndex( )
        {
        }

        public void Add( BaseStationEntity entity )
        {
            if( _entries.TryGetValue(entity.Name, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Name, new WeakReference<BaseStationEntity>( entity, false ) );
            }
        }

        public bool GetByName( string name, out BaseStationEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( name, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( name );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(string key, [DisallowNull] IList<BaseStationEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(string key, [DisallowNull] IList<BaseStationEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<BaseStationEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<BaseStationEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class BaseStationByTypeEntityIndex
    {
        public class ByType
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<BaseStationEntity>> _entries = new SortedListEx<Guid, WeakReference<BaseStationEntity>>( );
        }
    }

    public class BaseStationByTypeIsNullEntityIndex
    {
    }

    public class DeviceByHostEntityIndex
    {
        public class ByHost
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<DeviceEntity>> _entries = new SortedListEx<Guid, WeakReference<DeviceEntity>>( );
        }
    }

    public class DeviceByNameEntityIndex
    {
        readonly SortedWeakReferenceList<string, DeviceEntity> _entries = new SortedWeakReferenceList<string, DeviceEntity>( );

        public DeviceByNameEntityIndex( )
        {
        }

        public void Add( DeviceEntity entity )
        {
            if( _entries.TryGetValue(entity.Name, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Name, new WeakReference<DeviceEntity>( entity, false ) );
            }
        }

        public bool GetByName( string name, out DeviceEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( name, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( name );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(string key, [DisallowNull] IList<DeviceEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(string key, [DisallowNull] IList<DeviceEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<DeviceEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<DeviceEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class GyroDeviceByGNSSDeviceEntityIndex
    {
        public class ByGNSSDevice
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<GyroDeviceEntity>> _entries = new SortedListEx<Guid, WeakReference<GyroDeviceEntity>>( );
        }
    }

    public class GyroDeviceByGNSSDeviceIsNullEntityIndex
    {
    }

    public class RadomeDeviceByRadarEntityIndex
    {
        public class ByRadar
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<RadomeDeviceEntity>> _entries = new SortedListEx<Guid, WeakReference<RadomeDeviceEntity>>( );
        }
    }

    public class RadomeDeviceByRadarIsNullEntityIndex
    {
    }

    public class RadarDeviceByRadomeEntityIndex
    {
        public class ByRadome
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<RadarDeviceEntity>> _entries = new SortedListEx<Guid, WeakReference<RadarDeviceEntity>>( );
        }
    }

    public class RadarDeviceByRadomeIsNullEntityIndex
    {
    }

    public class RadarDeviceByGNSSDeviceEntityIndex
    {
        public class ByGNSSDevice
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<RadarDeviceEntity>> _entries = new SortedListEx<Guid, WeakReference<RadarDeviceEntity>>( );
        }
    }

    public class RadarDeviceByGNSSDeviceIsNullEntityIndex
    {
    }

    public class WeatherStationDeviceByGyroEntityIndex
    {
        public class ByGyro
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<WeatherStationDeviceEntity>> _entries = new SortedListEx<Guid, WeakReference<WeatherStationDeviceEntity>>( );
        }
    }

    public class WeatherStationDeviceByGyroIsNullEntityIndex
    {
    }

    public class FacilityByNameEntityIndex
    {
        readonly SortedWeakReferenceList<string, FacilityEntity> _entries = new SortedWeakReferenceList<string, FacilityEntity>( );

        public FacilityByNameEntityIndex( )
        {
        }

        public void Add( FacilityEntity entity )
        {
            if( _entries.TryGetValue(entity.Name, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Name, new WeakReference<FacilityEntity>( entity, false ) );
            }
        }

        public bool GetByName( string name, out FacilityEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( name, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( name );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(string key, [DisallowNull] IList<FacilityEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(string key, [DisallowNull] IList<FacilityEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<FacilityEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<FacilityEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class FacilityByTypeEntityIndex
    {
        public class ByType
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<FacilityEntity>> _entries = new SortedListEx<Guid, WeakReference<FacilityEntity>>( );
        }
    }

    public class FacilityByTypeIsNullEntityIndex
    {
    }

    public class AircraftByNameEntityIndex
    {
        public class ByName
        {
            readonly SortedListEx<string, ById> _entries = new SortedListEx<string, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AircraftEntity>> _entries = new SortedListEx<Guid, WeakReference<AircraftEntity>>( );
        }
    }

    public class AircraftByTypeEntityIndex
    {
        public class ByType
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AircraftEntity>> _entries = new SortedListEx<Guid, WeakReference<AircraftEntity>>( );
        }
    }

    public class AircraftByTypeIsNullEntityIndex
    {
    }

    public class AisAidToNavigationByNameEntityIndex
    {
        readonly SortedWeakReferenceList<string, AisAidToNavigationEntity> _entries = new SortedWeakReferenceList<string, AisAidToNavigationEntity>( );

        public AisAidToNavigationByNameEntityIndex( )
        {
        }

        public void Add( AisAidToNavigationEntity entity )
        {
            if( _entries.TryGetValue(entity.Name, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Name, new WeakReference<AisAidToNavigationEntity>( entity, false ) );
            }
        }

        public bool GetByName( string name, out AisAidToNavigationEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( name, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( name );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(string key, [DisallowNull] IList<AisAidToNavigationEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(string key, [DisallowNull] IList<AisAidToNavigationEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<AisAidToNavigationEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<AisAidToNavigationEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class AisAidToNavigationByMMSIEntityIndex
    {
        public class ByMMSI
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AisAidToNavigationEntity>> _entries = new SortedListEx<Guid, WeakReference<AisAidToNavigationEntity>>( );
        }
    }

    public class AisAidToNavigationByMMSIIsNullEntityIndex
    {
    }

    public class VehicleByNameEntityIndex
    {
        readonly SortedWeakReferenceList<string, VehicleEntity> _entries = new SortedWeakReferenceList<string, VehicleEntity>( );

        public VehicleByNameEntityIndex( )
        {
        }

        public void Add( VehicleEntity entity )
        {
            if( _entries.TryGetValue(entity.Name, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Name, new WeakReference<VehicleEntity>( entity, false ) );
            }
        }

        public bool GetByName( string name, out VehicleEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( name, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( name );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(string key, [DisallowNull] IList<VehicleEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(string key, [DisallowNull] IList<VehicleEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<VehicleEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<VehicleEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class VehicleByTypeEntityIndex
    {
        public class ByType
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<VehicleEntity>> _entries = new SortedListEx<Guid, WeakReference<VehicleEntity>>( );
        }
    }

    public class VehicleByTypeIsNullEntityIndex
    {
    }

    public class VesselByNameEntityIndex
    {
        public class ByName
        {
            readonly SortedListEx<string, ById> _entries = new SortedListEx<string, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<VesselEntity>> _entries = new SortedListEx<Guid, WeakReference<VesselEntity>>( );
        }
    }

    public class VesselByTypeEntityIndex
    {
        public class ByType
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<VesselEntity>> _entries = new SortedListEx<Guid, WeakReference<VesselEntity>>( );
        }
    }

    public class VesselByTypeIsNullEntityIndex
    {
    }

    public class ItemIdentityLinkByItemAndStartEntityIndex
    {
        public class ByItem
        {
            readonly SortedListEx<Guid, ByStart> _entries = new SortedListEx<Guid, ByStart>( );
        }
        public class ByStart
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<ItemIdentityLinkEntity>> _entries = new SortedListEx<Guid, WeakReference<ItemIdentityLinkEntity>>( );
        }
    }

    public class ItemIdentityLinkByItemAndEndEntityIndex
    {
        public class ByItem
        {
            readonly SortedListEx<Guid, ByEnd> _entries = new SortedListEx<Guid, ByEnd>( );
        }
        public class ByEnd
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<ItemIdentityLinkEntity>> _entries = new SortedListEx<Guid, WeakReference<ItemIdentityLinkEntity>>( );
        }
    }

    public class ItemIdentityLinkByItemAndEndIsNullEntityIndex
    {
    }

    public class ItemIdentityLinkByIdentityAndStartEntityIndex
    {
        public class ByIdentity
        {
            readonly SortedListEx<Guid, ByStart> _entries = new SortedListEx<Guid, ByStart>( );
        }
        public class ByStart
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<ItemIdentityLinkEntity>> _entries = new SortedListEx<Guid, WeakReference<ItemIdentityLinkEntity>>( );
        }
    }

    public class ItemIdentityLinkByIdentityAndEndEntityIndex
    {
        public class ByIdentity
        {
            readonly SortedListEx<Guid, ByEnd> _entries = new SortedListEx<Guid, ByEnd>( );
        }
        public class ByEnd
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<ItemIdentityLinkEntity>> _entries = new SortedListEx<Guid, WeakReference<ItemIdentityLinkEntity>>( );
        }
    }

    public class ItemIdentityLinkByIdentityAndEndIsNullEntityIndex
    {
    }

    public class ItemIdentityLinkByStartEntityIndex
    {
        public class ByStart
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<ItemIdentityLinkEntity>> _entries = new SortedListEx<Guid, WeakReference<ItemIdentityLinkEntity>>( );
        }
    }

    public class ItemIdentityLinkByEndEntityIndex
    {
        public class ByEnd
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<ItemIdentityLinkEntity>> _entries = new SortedListEx<Guid, WeakReference<ItemIdentityLinkEntity>>( );
        }
    }

    public class ItemIdentityLinkByEndIsNullEntityIndex
    {
    }

    public class ItemParentChildLinkByParentAndTimestampEntityIndex
    {
        public class ByParent
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, ItemParentChildLinkEntity> _entries = new SortedWeakReferenceList<DateTime, ItemParentChildLinkEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( ItemParentChildLinkEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<ItemParentChildLinkEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out ItemParentChildLinkEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<ItemParentChildLinkEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<ItemParentChildLinkEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<ItemParentChildLinkEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<ItemParentChildLinkEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class ItemParentChildLinkByChildAndTimestampEntityIndex
    {
        public class ByChild
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, ItemParentChildLinkEntity> _entries = new SortedWeakReferenceList<DateTime, ItemParentChildLinkEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( ItemParentChildLinkEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<ItemParentChildLinkEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out ItemParentChildLinkEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<ItemParentChildLinkEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<ItemParentChildLinkEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<ItemParentChildLinkEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<ItemParentChildLinkEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class ItemParentChildLinkByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<ItemParentChildLinkEntity>> _entries = new SortedListEx<Guid, WeakReference<ItemParentChildLinkEntity>>( );
        }
    }

    public class LineInputDeviceCommandByLineInputDeviceAndTimestampEntityIndex
    {
        public class ByLineInputDevice
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<LineInputDeviceCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<LineInputDeviceCommandEntity>>( );
        }
    }

    public class LineInputDeviceCommandByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<LineInputDeviceCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<LineInputDeviceCommandEntity>>( );
        }
    }

    public class LineInputDeviceCommandByReplyEntityIndex
    {
        public class ByReply
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<LineInputDeviceCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<LineInputDeviceCommandEntity>>( );
        }
    }

    public class LineInputDeviceCommandByReplyIsNullEntityIndex
    {
    }

    public class LineInputDeviceCommandReplyByLineInputDeviceAndTimestampEntityIndex
    {
        public class ByLineInputDevice
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<LineInputDeviceCommandReplyEntity>> _entries = new SortedListEx<Guid, WeakReference<LineInputDeviceCommandReplyEntity>>( );
        }
    }

    public class LineInputDeviceCommandReplyByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<LineInputDeviceCommandReplyEntity>> _entries = new SortedListEx<Guid, WeakReference<LineInputDeviceCommandReplyEntity>>( );
        }
    }

    public class LineInputDeviceCommandReplyByCommandEntityIndex
    {
        readonly SortedWeakReferenceList<Guid, LineInputDeviceCommandReplyEntity> _entries = new SortedWeakReferenceList<Guid, LineInputDeviceCommandReplyEntity>( );

        public LineInputDeviceCommandReplyByCommandEntityIndex( )
        {
        }

        public void Add( LineInputDeviceCommandReplyEntity entity )
        {
            if ( entity.CommandId is Guid command )
            {
                if ( _entries.TryGetValue( command, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( command, new WeakReference<LineInputDeviceCommandReplyEntity>( entity, false ) );
                }
            }
            else
            {
                throw new ArgumentException( "entity.CommandId is null.", nameof( entity ) );
            }
        }

        public bool GetByCommandId( Guid command, out LineInputDeviceCommandReplyEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( command, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( command );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(Guid key, [DisallowNull] IList<LineInputDeviceCommandReplyEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(Guid key, [DisallowNull] IList<LineInputDeviceCommandReplyEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<LineInputDeviceCommandReplyEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<LineInputDeviceCommandReplyEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class LineInputDeviceCommandReplyByCommandIsNullEntityIndex
    {
    }

    public class LineInputDeviceConfigurationByLineInputDeviceAndTimestampEntityIndex
    {
        public class ByLineInputDevice
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, LineInputDeviceConfigurationEntity> _entries = new SortedWeakReferenceList<DateTime, LineInputDeviceConfigurationEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( LineInputDeviceConfigurationEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<LineInputDeviceConfigurationEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out LineInputDeviceConfigurationEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<LineInputDeviceConfigurationEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<LineInputDeviceConfigurationEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<LineInputDeviceConfigurationEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<LineInputDeviceConfigurationEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class LineInputDeviceConfigurationByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<LineInputDeviceConfigurationEntity>> _entries = new SortedListEx<Guid, WeakReference<LineInputDeviceConfigurationEntity>>( );
        }
    }

    public class LineInputMessageRoutingByLineInputDeviceAndTypeEntityIndex
    {
        public class ByLineInputDevice
        {
            readonly SortedListEx<Guid, ByType> _entries = new SortedListEx<Guid, ByType>( );
        }
        public class ByType
        {
            readonly SortedWeakReferenceList<string, LineInputMessageRoutingEntity> _entries = new SortedWeakReferenceList<string, LineInputMessageRoutingEntity>( );

            public ByType( )
            {
            }

            public void Add( LineInputMessageRoutingEntity entity )
            {
                if( _entries.TryGetValue(entity.Type, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Type, new WeakReference<LineInputMessageRoutingEntity>( entity, false ) );
                }
            }

            public bool GetByType( string type, out LineInputMessageRoutingEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( type, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( type );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(string key, [DisallowNull] IList<LineInputMessageRoutingEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(string key, [DisallowNull] IList<LineInputMessageRoutingEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<LineInputMessageRoutingEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<LineInputMessageRoutingEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class LineInputMessageRoutingDestinationByRoutingAndListenerEntityIndex
    {
        public class ByRouting
        {
            readonly SortedListEx<Guid, ByListener> _entries = new SortedListEx<Guid, ByListener>( );
        }
        public class ByListener
        {
            readonly SortedWeakReferenceList<Guid, LineInputMessageRoutingDestinationEntity> _entries = new SortedWeakReferenceList<Guid, LineInputMessageRoutingDestinationEntity>( );

            public ByListener( )
            {
            }

            public void Add( LineInputMessageRoutingDestinationEntity entity )
            {
                if ( entity.ListenerId is Guid listener )
                {
                    if ( _entries.TryGetValue( listener, out var weakReference ) )
                    {
                        weakReference.SetTarget( entity );
                    }
                    else
                    {
                        _entries.Add( listener, new WeakReference<LineInputMessageRoutingDestinationEntity>( entity, false ) );
                    }
                }
                else
                {
                    throw new ArgumentException( "entity.ListenerId is null.", nameof( entity ) );
                }
            }

            public bool GetByListenerId( Guid listener, out LineInputMessageRoutingDestinationEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( listener, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( listener );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(Guid key, [DisallowNull] IList<LineInputMessageRoutingDestinationEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(Guid key, [DisallowNull] IList<LineInputMessageRoutingDestinationEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<LineInputMessageRoutingDestinationEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<LineInputMessageRoutingDestinationEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class LineInputMessageRoutingDestinationByRoutingAndListenerIsNullEntityIndex
    {
    }

    public class LineInputMessageRoutingDestinationByListenerEntityIndex
    {
        public class ByListener
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<LineInputMessageRoutingDestinationEntity>> _entries = new SortedListEx<Guid, WeakReference<LineInputMessageRoutingDestinationEntity>>( );
        }
    }

    public class LineInputMessageRoutingDestinationByListenerIsNullEntityIndex
    {
    }

    public class LineInputWhiteListEntryByLineInputDeviceHostNameAndPortEntityIndex
    {
        public class ByLineInputDevice
        {
            readonly SortedListEx<Guid, ByHostName> _entries = new SortedListEx<Guid, ByHostName>( );
        }
        public class ByHostName
        {
            readonly SortedListEx<string, ByPort> _entries = new SortedListEx<string, ByPort>( );
        }
        public class ByPort
        {
            readonly SortedWeakReferenceList<int, LineInputWhiteListEntryEntity> _entries = new SortedWeakReferenceList<int, LineInputWhiteListEntryEntity>( );

            public ByPort( )
            {
            }

            public void Add( LineInputWhiteListEntryEntity entity )
            {
                if( _entries.TryGetValue(entity.Port, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Port, new WeakReference<LineInputWhiteListEntryEntity>( entity, false ) );
                }
            }

            public bool GetByPort( int port, out LineInputWhiteListEntryEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( port, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( port );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(int key, [DisallowNull] IList<LineInputWhiteListEntryEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(int key, [DisallowNull] IList<LineInputWhiteListEntryEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(int firstKey, int lastKey, [DisallowNull] IList<LineInputWhiteListEntryEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<LineInputWhiteListEntryEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class LogApplicationByNameEntityIndex
    {
        readonly SortedWeakReferenceList<string, LogApplicationEntity> _entries = new SortedWeakReferenceList<string, LogApplicationEntity>( );

        public LogApplicationByNameEntityIndex( )
        {
        }

        public void Add( LogApplicationEntity entity )
        {
            if( _entries.TryGetValue(entity.Name, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Name, new WeakReference<LogApplicationEntity>( entity, false ) );
            }
        }

        public bool GetByName( string name, out LogApplicationEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( name, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( name );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(string key, [DisallowNull] IList<LogApplicationEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(string key, [DisallowNull] IList<LogApplicationEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<LogApplicationEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<LogApplicationEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class LogApplicationConfigurationByApplicationAndTimestampEntityIndex
    {
        public class ByApplication
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, LogApplicationConfigurationEntity> _entries = new SortedWeakReferenceList<DateTime, LogApplicationConfigurationEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( LogApplicationConfigurationEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<LogApplicationConfigurationEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out LogApplicationConfigurationEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<LogApplicationConfigurationEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<LogApplicationConfigurationEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<LogApplicationConfigurationEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<LogApplicationConfigurationEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class LogApplicationConfigurationByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<LogApplicationConfigurationEntity>> _entries = new SortedListEx<Guid, WeakReference<LogApplicationConfigurationEntity>>( );
        }
    }

    public class LogHostByComputerNameEntityIndex
    {
        readonly SortedWeakReferenceList<string, LogHostEntity> _entries = new SortedWeakReferenceList<string, LogHostEntity>( );

        public LogHostByComputerNameEntityIndex( )
        {
        }

        public void Add( LogHostEntity entity )
        {
            if( _entries.TryGetValue(entity.ComputerName, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.ComputerName, new WeakReference<LogHostEntity>( entity, false ) );
            }
        }

        public bool GetByComputerName( string computerName, out LogHostEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( computerName, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( computerName );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(string key, [DisallowNull] IList<LogHostEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(string key, [DisallowNull] IList<LogHostEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<LogHostEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<LogHostEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class LogHostConfigurationByHostAndTimestampEntityIndex
    {
        public class ByHost
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, LogHostConfigurationEntity> _entries = new SortedWeakReferenceList<DateTime, LogHostConfigurationEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( LogHostConfigurationEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<LogHostConfigurationEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out LogHostConfigurationEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<LogHostConfigurationEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<LogHostConfigurationEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<LogHostConfigurationEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<LogHostConfigurationEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class LogHostConfigurationByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<LogHostConfigurationEntity>> _entries = new SortedListEx<Guid, WeakReference<LogHostConfigurationEntity>>( );
        }
    }

    public class LogLocationByFileNameAndLineNumberEntityIndex
    {
        public class ByFileName
        {
            readonly SortedListEx<string, ByLineNumber> _entries = new SortedListEx<string, ByLineNumber>( );
        }
        public class ByLineNumber
        {
            readonly SortedWeakReferenceList<int, LogLocationEntity> _entries = new SortedWeakReferenceList<int, LogLocationEntity>( );

            public ByLineNumber( )
            {
            }

            public void Add( LogLocationEntity entity )
            {
                if( _entries.TryGetValue(entity.LineNumber, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.LineNumber, new WeakReference<LogLocationEntity>( entity, false ) );
                }
            }

            public bool GetByLineNumber( int lineNumber, out LogLocationEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( lineNumber, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( lineNumber );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(int key, [DisallowNull] IList<LogLocationEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(int key, [DisallowNull] IList<LogLocationEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(int firstKey, int lastKey, [DisallowNull] IList<LogLocationEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<LogLocationEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class LogProcessByApplicationAndStartedEntityIndex
    {
        public class ByApplication
        {
            readonly SortedListEx<Guid, ByStarted> _entries = new SortedListEx<Guid, ByStarted>( );
        }
        public class ByStarted
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<LogProcessEntity>> _entries = new SortedListEx<Guid, WeakReference<LogProcessEntity>>( );
        }
    }

    public class LogProcessByHostAndStartedEntityIndex
    {
        public class ByHost
        {
            readonly SortedListEx<Guid, ByStarted> _entries = new SortedListEx<Guid, ByStarted>( );
        }
        public class ByStarted
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<LogProcessEntity>> _entries = new SortedListEx<Guid, WeakReference<LogProcessEntity>>( );
        }
    }

    public class LogProcessByHostIsNullAndStartedEntityIndex
    {
    }

    public class LogProcessByStartedEntityIndex
    {
        public class ByStarted
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<LogProcessEntity>> _entries = new SortedListEx<Guid, WeakReference<LogProcessEntity>>( );
        }
    }

    public class LogRecordByThreadAndTimestampEntityIndex
    {
        public class ByThread
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<LogRecordEntity>> _entries = new SortedListEx<Guid, WeakReference<LogRecordEntity>>( );
        }
    }

    public class LogRecordByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<LogRecordEntity>> _entries = new SortedListEx<Guid, WeakReference<LogRecordEntity>>( );
        }
    }

    public class LogRecordByLocationEntityIndex
    {
        public class ByLocation
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<LogRecordEntity>> _entries = new SortedListEx<Guid, WeakReference<LogRecordEntity>>( );
        }
    }

    public class LogThreadByProcessAndStartedEntityIndex
    {
        public class ByProcess
        {
            readonly SortedListEx<Guid, ByStarted> _entries = new SortedListEx<Guid, ByStarted>( );
        }
        public class ByStarted
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<LogThreadEntity>> _entries = new SortedListEx<Guid, WeakReference<LogThreadEntity>>( );
        }
    }

    public class LogThreadByStartedEntityIndex
    {
        public class ByStarted
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<LogThreadEntity>> _entries = new SortedListEx<Guid, WeakReference<LogThreadEntity>>( );
        }
    }

    public class LogTraceEntryByThreadAndEnteredEntityIndex
    {
        public class ByThread
        {
            readonly SortedListEx<Guid, ByEntered> _entries = new SortedListEx<Guid, ByEntered>( );
        }
        public class ByEntered
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<LogTraceEntryEntity>> _entries = new SortedListEx<Guid, WeakReference<LogTraceEntryEntity>>( );
        }
    }

    public class LogTraceEntryByLocationAndEnteredEntityIndex
    {
        public class ByLocation
        {
            readonly SortedListEx<Guid, ByEntered> _entries = new SortedListEx<Guid, ByEntered>( );
        }
        public class ByEntered
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<LogTraceEntryEntity>> _entries = new SortedListEx<Guid, WeakReference<LogTraceEntryEntity>>( );
        }
    }

    public class LogTraceEntryByEnteredEntityIndex
    {
        public class ByEntered
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<LogTraceEntryEntity>> _entries = new SortedListEx<Guid, WeakReference<LogTraceEntryEntity>>( );
        }
    }

    public class MapElementByItemEntityIndex
    {
        public class ByItem
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<MapElementEntity>> _entries = new SortedListEx<Guid, WeakReference<MapElementEntity>>( );
        }
    }

    public class MapServiceOptionsByTimestampEntityIndex
    {
        readonly SortedWeakReferenceList<DateTime, MapServiceOptionsEntity> _entries = new SortedWeakReferenceList<DateTime, MapServiceOptionsEntity>( );

        public MapServiceOptionsByTimestampEntityIndex( )
        {
        }

        public void Add( MapServiceOptionsEntity entity )
        {
            if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Timestamp, new WeakReference<MapServiceOptionsEntity>( entity, false ) );
            }
        }

        public bool GetByTimestamp( DateTime timestamp, out MapServiceOptionsEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( timestamp, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( timestamp );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(DateTime key, [DisallowNull] IList<MapServiceOptionsEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(DateTime key, [DisallowNull] IList<MapServiceOptionsEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<MapServiceOptionsEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<MapServiceOptionsEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class MaritimeIdentificationDigitsByCodeEntityIndex
    {
        readonly SortedWeakReferenceList<int, MaritimeIdentificationDigitsEntity> _entries = new SortedWeakReferenceList<int, MaritimeIdentificationDigitsEntity>( );

        public MaritimeIdentificationDigitsByCodeEntityIndex( )
        {
        }

        public void Add( MaritimeIdentificationDigitsEntity entity )
        {
            if( _entries.TryGetValue(entity.Code, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Code, new WeakReference<MaritimeIdentificationDigitsEntity>( entity, false ) );
            }
        }

        public bool GetByCode( int code, out MaritimeIdentificationDigitsEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( code, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( code );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(int key, [DisallowNull] IList<MaritimeIdentificationDigitsEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(int key, [DisallowNull] IList<MaritimeIdentificationDigitsEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(int firstKey, int lastKey, [DisallowNull] IList<MaritimeIdentificationDigitsEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<MaritimeIdentificationDigitsEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class MaritimeIdentificationDigitsByCountryEntityIndex
    {
        public class ByCountry
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<MaritimeIdentificationDigitsEntity>> _entries = new SortedListEx<Guid, WeakReference<MaritimeIdentificationDigitsEntity>>( );
        }
    }

    public class MediaProxySessionByServiceAndNameEntityIndex
    {
        public class ByService
        {
            readonly SortedListEx<Guid, ByName> _entries = new SortedListEx<Guid, ByName>( );
        }
        public class ByName
        {
            readonly SortedWeakReferenceList<string, MediaProxySessionEntity> _entries = new SortedWeakReferenceList<string, MediaProxySessionEntity>( );

            public ByName( )
            {
            }

            public void Add( MediaProxySessionEntity entity )
            {
                if( _entries.TryGetValue(entity.Name, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Name, new WeakReference<MediaProxySessionEntity>( entity, false ) );
                }
            }

            public bool GetByName( string name, out MediaProxySessionEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( name, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( name );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(string key, [DisallowNull] IList<MediaProxySessionEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(string key, [DisallowNull] IList<MediaProxySessionEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<MediaProxySessionEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<MediaProxySessionEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class MediaProxySessionFileByProxySessionAndTimestampEntityIndex
    {
        public class ByProxySession
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, MediaProxySessionFileEntity> _entries = new SortedWeakReferenceList<DateTime, MediaProxySessionFileEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( MediaProxySessionFileEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<MediaProxySessionFileEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out MediaProxySessionFileEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<MediaProxySessionFileEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<MediaProxySessionFileEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<MediaProxySessionFileEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<MediaProxySessionFileEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class MediaProxySessionOptionsByProxySessionAndTimestampEntityIndex
    {
        public class ByProxySession
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, MediaProxySessionOptionsEntity> _entries = new SortedWeakReferenceList<DateTime, MediaProxySessionOptionsEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( MediaProxySessionOptionsEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<MediaProxySessionOptionsEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out MediaProxySessionOptionsEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<MediaProxySessionOptionsEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<MediaProxySessionOptionsEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<MediaProxySessionOptionsEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<MediaProxySessionOptionsEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class MediaServiceOptionsByMediaServiceAndTimestampEntityIndex
    {
        public class ByMediaService
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, MediaServiceOptionsEntity> _entries = new SortedWeakReferenceList<DateTime, MediaServiceOptionsEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( MediaServiceOptionsEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<MediaServiceOptionsEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out MediaServiceOptionsEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<MediaServiceOptionsEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<MediaServiceOptionsEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<MediaServiceOptionsEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<MediaServiceOptionsEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class NamespaceElementByNamespaceAndNameEntityIndex
    {
        public class ByNamespace
        {
            readonly SortedListEx<Guid, ByName> _entries = new SortedListEx<Guid, ByName>( );
        }
        public class ByName
        {
            readonly SortedWeakReferenceList<string, NamespaceElementEntity> _entries = new SortedWeakReferenceList<string, NamespaceElementEntity>( );

            public ByName( )
            {
            }

            public void Add( NamespaceElementEntity entity )
            {
                if( _entries.TryGetValue(entity.Name, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Name, new WeakReference<NamespaceElementEntity>( entity, false ) );
                }
            }

            public bool GetByName( string name, out NamespaceElementEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( name, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( name );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(string key, [DisallowNull] IList<NamespaceElementEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(string key, [DisallowNull] IList<NamespaceElementEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<NamespaceElementEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<NamespaceElementEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class OilSpillByOilSpillDetectorAndTimestampEntityIndex
    {
        public class ByOilSpillDetector
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<OilSpillEntity>> _entries = new SortedListEx<Guid, WeakReference<OilSpillEntity>>( );
        }
    }

    public class OilSpillByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<OilSpillEntity>> _entries = new SortedListEx<Guid, WeakReference<OilSpillEntity>>( );
        }
    }

    public class OilSpillDetectorCommandByOilSpillDetectorAndTimestampEntityIndex
    {
        public class ByOilSpillDetector
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<OilSpillDetectorCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<OilSpillDetectorCommandEntity>>( );
        }
    }

    public class OilSpillDetectorCommandByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<OilSpillDetectorCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<OilSpillDetectorCommandEntity>>( );
        }
    }

    public class OilSpillDetectorCommandByReplyEntityIndex
    {
        public class ByReply
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<OilSpillDetectorCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<OilSpillDetectorCommandEntity>>( );
        }
    }

    public class OilSpillDetectorCommandByReplyIsNullEntityIndex
    {
    }

    public class OilSpillDetectorCommandReplyByOilSpillDetectorAndTimestampEntityIndex
    {
        public class ByOilSpillDetector
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<OilSpillDetectorCommandReplyEntity>> _entries = new SortedListEx<Guid, WeakReference<OilSpillDetectorCommandReplyEntity>>( );
        }
    }

    public class OilSpillDetectorCommandReplyByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<OilSpillDetectorCommandReplyEntity>> _entries = new SortedListEx<Guid, WeakReference<OilSpillDetectorCommandReplyEntity>>( );
        }
    }

    public class OilSpillDetectorCommandReplyByCommandEntityIndex
    {
        readonly SortedWeakReferenceList<Guid, OilSpillDetectorCommandReplyEntity> _entries = new SortedWeakReferenceList<Guid, OilSpillDetectorCommandReplyEntity>( );

        public OilSpillDetectorCommandReplyByCommandEntityIndex( )
        {
        }

        public void Add( OilSpillDetectorCommandReplyEntity entity )
        {
            if ( entity.CommandId is Guid command )
            {
                if ( _entries.TryGetValue( command, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( command, new WeakReference<OilSpillDetectorCommandReplyEntity>( entity, false ) );
                }
            }
            else
            {
                throw new ArgumentException( "entity.CommandId is null.", nameof( entity ) );
            }
        }

        public bool GetByCommandId( Guid command, out OilSpillDetectorCommandReplyEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( command, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( command );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(Guid key, [DisallowNull] IList<OilSpillDetectorCommandReplyEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(Guid key, [DisallowNull] IList<OilSpillDetectorCommandReplyEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<OilSpillDetectorCommandReplyEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<OilSpillDetectorCommandReplyEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class OilSpillDetectorCommandReplyByCommandIsNullEntityIndex
    {
    }

    public class OilSpillDetectorConfigurationByOilSpillDetectorAndTimestampEntityIndex
    {
        public class ByOilSpillDetector
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, OilSpillDetectorConfigurationEntity> _entries = new SortedWeakReferenceList<DateTime, OilSpillDetectorConfigurationEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( OilSpillDetectorConfigurationEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<OilSpillDetectorConfigurationEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out OilSpillDetectorConfigurationEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<OilSpillDetectorConfigurationEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<OilSpillDetectorConfigurationEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<OilSpillDetectorConfigurationEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<OilSpillDetectorConfigurationEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class OilSpillDetectorConfigurationByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<OilSpillDetectorConfigurationEntity>> _entries = new SortedListEx<Guid, WeakReference<OilSpillDetectorConfigurationEntity>>( );
        }
    }

    public class OilSpillDetectorConfigurationByTargetMMSIEntityIndex
    {
        public class ByTargetMMSI
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<OilSpillDetectorConfigurationEntity>> _entries = new SortedListEx<Guid, WeakReference<OilSpillDetectorConfigurationEntity>>( );
        }
    }

    public class OilSpillDetectorConfigurationByTargetMMSIIsNullEntityIndex
    {
    }

    public class Position2DTimeseriesValueByTimeseriesAndTimestampEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, Position2DTimeseriesValueEntity> _entries = new SortedWeakReferenceList<DateTime, Position2DTimeseriesValueEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( Position2DTimeseriesValueEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<Position2DTimeseriesValueEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out Position2DTimeseriesValueEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<Position2DTimeseriesValueEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<Position2DTimeseriesValueEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<Position2DTimeseriesValueEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<Position2DTimeseriesValueEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class Position2DTimeseriesValueByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<Position2DTimeseriesValueEntity>> _entries = new SortedListEx<Guid, WeakReference<Position2DTimeseriesValueEntity>>( );
        }
    }

    public class Position3DTimeseriesValueByTimeseriesAndTimestampEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, Position3DTimeseriesValueEntity> _entries = new SortedWeakReferenceList<DateTime, Position3DTimeseriesValueEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( Position3DTimeseriesValueEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<Position3DTimeseriesValueEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out Position3DTimeseriesValueEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<Position3DTimeseriesValueEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<Position3DTimeseriesValueEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<Position3DTimeseriesValueEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<Position3DTimeseriesValueEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class Position3DTimeseriesValueByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<Position3DTimeseriesValueEntity>> _entries = new SortedListEx<Guid, WeakReference<Position3DTimeseriesValueEntity>>( );
        }
    }

    public class PropertyByElementAndDefinitionEntityIndex
    {
        public class ByElement
        {
            readonly SortedListEx<Guid, ByDefinition> _entries = new SortedListEx<Guid, ByDefinition>( );
        }
        public class ByDefinition
        {
            readonly SortedWeakReferenceList<Guid, PropertyEntity> _entries = new SortedWeakReferenceList<Guid, PropertyEntity>( );

            public ByDefinition( )
            {
            }

            public void Add( PropertyEntity entity )
            {
                if( _entries.TryGetValue(entity.DefinitionId, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.DefinitionId, new WeakReference<PropertyEntity>( entity, false ) );
                }
            }

            public bool GetByDefinitionId( Guid definition, out PropertyEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( definition, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( definition );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(Guid key, [DisallowNull] IList<PropertyEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(Guid key, [DisallowNull] IList<PropertyEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<PropertyEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<PropertyEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class PropertyByDefinitionEntityIndex
    {
        public class ByDefinition
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<PropertyEntity>> _entries = new SortedListEx<Guid, WeakReference<PropertyEntity>>( );
        }
    }

    public class ReferencePropertyByValueEntityIndex
    {
        public class ByValue
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<ReferencePropertyEntity>> _entries = new SortedListEx<Guid, WeakReference<ReferencePropertyEntity>>( );
        }
    }

    public class ReferencePropertyByValueIsNullEntityIndex
    {
    }

    public class BinaryTimeseriesPropertyByTimeseriesEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<BinaryTimeseriesPropertyEntity>> _entries = new SortedListEx<Guid, WeakReference<BinaryTimeseriesPropertyEntity>>( );
        }
    }

    public class BinaryTimeseriesPropertyByTimeseriesIsNullEntityIndex
    {
    }

    public class BooleanTimeseriesPropertyByTimeseriesEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<BooleanTimeseriesPropertyEntity>> _entries = new SortedListEx<Guid, WeakReference<BooleanTimeseriesPropertyEntity>>( );
        }
    }

    public class BooleanTimeseriesPropertyByTimeseriesIsNullEntityIndex
    {
    }

    public class ByteTimeseriesPropertyByTimeseriesEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<ByteTimeseriesPropertyEntity>> _entries = new SortedListEx<Guid, WeakReference<ByteTimeseriesPropertyEntity>>( );
        }
    }

    public class ByteTimeseriesPropertyByTimeseriesIsNullEntityIndex
    {
    }

    public class DateTimeTimeseriesPropertyByTimeseriesEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<DateTimeTimeseriesPropertyEntity>> _entries = new SortedListEx<Guid, WeakReference<DateTimeTimeseriesPropertyEntity>>( );
        }
    }

    public class DateTimeTimeseriesPropertyByTimeseriesIsNullEntityIndex
    {
    }

    public class DoubleTimeseriesPropertyByTimeseriesEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<DoubleTimeseriesPropertyEntity>> _entries = new SortedListEx<Guid, WeakReference<DoubleTimeseriesPropertyEntity>>( );
        }
    }

    public class DoubleTimeseriesPropertyByTimeseriesIsNullEntityIndex
    {
    }

    public class GuidTimeseriesPropertyByTimeseriesEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<GuidTimeseriesPropertyEntity>> _entries = new SortedListEx<Guid, WeakReference<GuidTimeseriesPropertyEntity>>( );
        }
    }

    public class GuidTimeseriesPropertyByTimeseriesIsNullEntityIndex
    {
    }

    public class Int16TimeseriesPropertyByTimeseriesEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<Int16TimeseriesPropertyEntity>> _entries = new SortedListEx<Guid, WeakReference<Int16TimeseriesPropertyEntity>>( );
        }
    }

    public class Int16TimeseriesPropertyByTimeseriesIsNullEntityIndex
    {
    }

    public class Int32TimeseriesPropertyByTimeseriesEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<Int32TimeseriesPropertyEntity>> _entries = new SortedListEx<Guid, WeakReference<Int32TimeseriesPropertyEntity>>( );
        }
    }

    public class Int32TimeseriesPropertyByTimeseriesIsNullEntityIndex
    {
    }

    public class Int64TimeseriesPropertyByTimeseriesEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<Int64TimeseriesPropertyEntity>> _entries = new SortedListEx<Guid, WeakReference<Int64TimeseriesPropertyEntity>>( );
        }
    }

    public class Int64TimeseriesPropertyByTimeseriesIsNullEntityIndex
    {
    }

    public class ReferenceTimeseriesPropertyByTimeseriesEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<ReferenceTimeseriesPropertyEntity>> _entries = new SortedListEx<Guid, WeakReference<ReferenceTimeseriesPropertyEntity>>( );
        }
    }

    public class ReferenceTimeseriesPropertyByTimeseriesIsNullEntityIndex
    {
    }

    public class SByteTimeseriesPropertyByTimeseriesEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<SByteTimeseriesPropertyEntity>> _entries = new SortedListEx<Guid, WeakReference<SByteTimeseriesPropertyEntity>>( );
        }
    }

    public class SByteTimeseriesPropertyByTimeseriesIsNullEntityIndex
    {
    }

    public class SingleTimeseriesPropertyByTimeseriesEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<SingleTimeseriesPropertyEntity>> _entries = new SortedListEx<Guid, WeakReference<SingleTimeseriesPropertyEntity>>( );
        }
    }

    public class SingleTimeseriesPropertyByTimeseriesIsNullEntityIndex
    {
    }

    public class StringTimeseriesPropertyByTimeseriesEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<StringTimeseriesPropertyEntity>> _entries = new SortedListEx<Guid, WeakReference<StringTimeseriesPropertyEntity>>( );
        }
    }

    public class StringTimeseriesPropertyByTimeseriesIsNullEntityIndex
    {
    }

    public class TimeSpanTimeseriesPropertyByTimeseriesEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<TimeSpanTimeseriesPropertyEntity>> _entries = new SortedListEx<Guid, WeakReference<TimeSpanTimeseriesPropertyEntity>>( );
        }
    }

    public class TimeSpanTimeseriesPropertyByTimeseriesIsNullEntityIndex
    {
    }

    public class UInt16TimeseriesPropertyByTimeseriesEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<UInt16TimeseriesPropertyEntity>> _entries = new SortedListEx<Guid, WeakReference<UInt16TimeseriesPropertyEntity>>( );
        }
    }

    public class UInt16TimeseriesPropertyByTimeseriesIsNullEntityIndex
    {
    }

    public class UInt32TimeseriesPropertyByTimeseriesEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<UInt32TimeseriesPropertyEntity>> _entries = new SortedListEx<Guid, WeakReference<UInt32TimeseriesPropertyEntity>>( );
        }
    }

    public class UInt32TimeseriesPropertyByTimeseriesIsNullEntityIndex
    {
    }

    public class UInt64TimeseriesPropertyByTimeseriesEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<UInt64TimeseriesPropertyEntity>> _entries = new SortedListEx<Guid, WeakReference<UInt64TimeseriesPropertyEntity>>( );
        }
    }

    public class UInt64TimeseriesPropertyByTimeseriesIsNullEntityIndex
    {
    }

    public class PropertyDefinitionByElementTypeAndNameEntityIndex
    {
        public class ByElementType
        {
            readonly SortedListEx<Guid, ByName> _entries = new SortedListEx<Guid, ByName>( );
        }
        public class ByName
        {
            readonly SortedWeakReferenceList<string, PropertyDefinitionEntity> _entries = new SortedWeakReferenceList<string, PropertyDefinitionEntity>( );

            public ByName( )
            {
            }

            public void Add( PropertyDefinitionEntity entity )
            {
                if( _entries.TryGetValue(entity.Name, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Name, new WeakReference<PropertyDefinitionEntity>( entity, false ) );
                }
            }

            public bool GetByName( string name, out PropertyDefinitionEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( name, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( name );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(string key, [DisallowNull] IList<PropertyDefinitionEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(string key, [DisallowNull] IList<PropertyDefinitionEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<PropertyDefinitionEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<PropertyDefinitionEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class ReferencePropertyDefinitionByDefaultValueEntityIndex
    {
        public class ByDefaultValue
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<ReferencePropertyDefinitionEntity>> _entries = new SortedListEx<Guid, WeakReference<ReferencePropertyDefinitionEntity>>( );
        }
    }

    public class ReferencePropertyDefinitionByDefaultValueIsNullEntityIndex
    {
    }

    public class ReferencePropertyDefinitionByReferencedElementTypeEntityIndex
    {
        public class ByReferencedElementType
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<ReferencePropertyDefinitionEntity>> _entries = new SortedListEx<Guid, WeakReference<ReferencePropertyDefinitionEntity>>( );
        }
    }

    public class ReferencePropertyDefinitionByReferencedElementTypeIsNullEntityIndex
    {
    }

    public class ReferenceTimeseriesPropertyDefinitionByReferencedElementTypeEntityIndex
    {
        public class ByReferencedElementType
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<ReferenceTimeseriesPropertyDefinitionEntity>> _entries = new SortedListEx<Guid, WeakReference<ReferenceTimeseriesPropertyDefinitionEntity>>( );
        }
    }

    public class ReferenceTimeseriesPropertyDefinitionByReferencedElementTypeIsNullEntityIndex
    {
    }

    public class RadarAlarmStatusByRadarAndTimestampEntityIndex
    {
        public class ByRadar
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, RadarAlarmStatusEntity> _entries = new SortedWeakReferenceList<DateTime, RadarAlarmStatusEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( RadarAlarmStatusEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<RadarAlarmStatusEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out RadarAlarmStatusEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<RadarAlarmStatusEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<RadarAlarmStatusEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<RadarAlarmStatusEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<RadarAlarmStatusEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class RadarAlarmStatusByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<RadarAlarmStatusEntity>> _entries = new SortedListEx<Guid, WeakReference<RadarAlarmStatusEntity>>( );
        }
    }

    public class RadarCommandByRadarAndTimestampEntityIndex
    {
        public class ByRadar
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<RadarCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<RadarCommandEntity>>( );
        }
    }

    public class RadarCommandByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<RadarCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<RadarCommandEntity>>( );
        }
    }

    public class RadarCommandByReplyEntityIndex
    {
        public class ByReply
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<RadarCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<RadarCommandEntity>>( );
        }
    }

    public class RadarCommandByReplyIsNullEntityIndex
    {
    }

    public class RadarCommandReplyByRadarAndTimestampEntityIndex
    {
        public class ByRadar
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<RadarCommandReplyEntity>> _entries = new SortedListEx<Guid, WeakReference<RadarCommandReplyEntity>>( );
        }
    }

    public class RadarCommandReplyByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<RadarCommandReplyEntity>> _entries = new SortedListEx<Guid, WeakReference<RadarCommandReplyEntity>>( );
        }
    }

    public class RadarCommandReplyByCommandEntityIndex
    {
        readonly SortedWeakReferenceList<Guid, RadarCommandReplyEntity> _entries = new SortedWeakReferenceList<Guid, RadarCommandReplyEntity>( );

        public RadarCommandReplyByCommandEntityIndex( )
        {
        }

        public void Add( RadarCommandReplyEntity entity )
        {
            if ( entity.CommandId is Guid command )
            {
                if ( _entries.TryGetValue( command, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( command, new WeakReference<RadarCommandReplyEntity>( entity, false ) );
                }
            }
            else
            {
                throw new ArgumentException( "entity.CommandId is null.", nameof( entity ) );
            }
        }

        public bool GetByCommandId( Guid command, out RadarCommandReplyEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( command, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( command );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(Guid key, [DisallowNull] IList<RadarCommandReplyEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(Guid key, [DisallowNull] IList<RadarCommandReplyEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<RadarCommandReplyEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<RadarCommandReplyEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class RadarCommandReplyByCommandIsNullEntityIndex
    {
    }

    public class RadarConfigurationByRadarAndTimestampEntityIndex
    {
        public class ByRadar
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, RadarConfigurationEntity> _entries = new SortedWeakReferenceList<DateTime, RadarConfigurationEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( RadarConfigurationEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<RadarConfigurationEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out RadarConfigurationEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<RadarConfigurationEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<RadarConfigurationEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<RadarConfigurationEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<RadarConfigurationEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class RadarConfigurationByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<RadarConfigurationEntity>> _entries = new SortedListEx<Guid, WeakReference<RadarConfigurationEntity>>( );
        }
    }

    public class RadarImageByRadarAndTimestampEntityIndex
    {
        public class ByRadar
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, RadarImageEntity> _entries = new SortedWeakReferenceList<DateTime, RadarImageEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( RadarImageEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<RadarImageEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out RadarImageEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<RadarImageEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<RadarImageEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<RadarImageEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<RadarImageEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class RadarImageByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<RadarImageEntity>> _entries = new SortedListEx<Guid, WeakReference<RadarImageEntity>>( );
        }
    }

    public class RadarRawTrackTableByRadarAndTimestampEntityIndex
    {
        public class ByRadar
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, RadarRawTrackTableEntity> _entries = new SortedWeakReferenceList<DateTime, RadarRawTrackTableEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( RadarRawTrackTableEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<RadarRawTrackTableEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out RadarRawTrackTableEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<RadarRawTrackTableEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<RadarRawTrackTableEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<RadarRawTrackTableEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<RadarRawTrackTableEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class RadarRawTrackTableByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<RadarRawTrackTableEntity>> _entries = new SortedListEx<Guid, WeakReference<RadarRawTrackTableEntity>>( );
        }
    }

    public class RadarStatusByRadarAndTimestampEntityIndex
    {
        public class ByRadar
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, RadarStatusEntity> _entries = new SortedWeakReferenceList<DateTime, RadarStatusEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( RadarStatusEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<RadarStatusEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out RadarStatusEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<RadarStatusEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<RadarStatusEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<RadarStatusEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<RadarStatusEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class RadarStatusByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<RadarStatusEntity>> _entries = new SortedListEx<Guid, WeakReference<RadarStatusEntity>>( );
        }
    }

    public class RadioCommandByRadioAndTimestampEntityIndex
    {
        public class ByRadio
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<RadioCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<RadioCommandEntity>>( );
        }
    }

    public class RadioCommandByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<RadioCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<RadioCommandEntity>>( );
        }
    }

    public class RadioCommandByReplyEntityIndex
    {
        public class ByReply
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<RadioCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<RadioCommandEntity>>( );
        }
    }

    public class RadioCommandByReplyIsNullEntityIndex
    {
    }

    public class RadioCommandReplyByRadioAndTimestampEntityIndex
    {
        public class ByRadio
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<RadioCommandReplyEntity>> _entries = new SortedListEx<Guid, WeakReference<RadioCommandReplyEntity>>( );
        }
    }

    public class RadioCommandReplyByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<RadioCommandReplyEntity>> _entries = new SortedListEx<Guid, WeakReference<RadioCommandReplyEntity>>( );
        }
    }

    public class RadioCommandReplyByCommandEntityIndex
    {
        readonly SortedWeakReferenceList<Guid, RadioCommandReplyEntity> _entries = new SortedWeakReferenceList<Guid, RadioCommandReplyEntity>( );

        public RadioCommandReplyByCommandEntityIndex( )
        {
        }

        public void Add( RadioCommandReplyEntity entity )
        {
            if ( entity.CommandId is Guid command )
            {
                if ( _entries.TryGetValue( command, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( command, new WeakReference<RadioCommandReplyEntity>( entity, false ) );
                }
            }
            else
            {
                throw new ArgumentException( "entity.CommandId is null.", nameof( entity ) );
            }
        }

        public bool GetByCommandId( Guid command, out RadioCommandReplyEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( command, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( command );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(Guid key, [DisallowNull] IList<RadioCommandReplyEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(Guid key, [DisallowNull] IList<RadioCommandReplyEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<RadioCommandReplyEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<RadioCommandReplyEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class RadioCommandReplyByCommandIsNullEntityIndex
    {
    }

    public class RadioConfigurationByRadioAndTimestampEntityIndex
    {
        public class ByRadio
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, RadioConfigurationEntity> _entries = new SortedWeakReferenceList<DateTime, RadioConfigurationEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( RadioConfigurationEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<RadioConfigurationEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out RadioConfigurationEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<RadioConfigurationEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<RadioConfigurationEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<RadioConfigurationEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<RadioConfigurationEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class RadioConfigurationByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<RadioConfigurationEntity>> _entries = new SortedListEx<Guid, WeakReference<RadioConfigurationEntity>>( );
        }
    }

    public class RadomeCommandByRadomeAndTimestampEntityIndex
    {
        public class ByRadome
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<RadomeCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<RadomeCommandEntity>>( );
        }
    }

    public class RadomeCommandByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<RadomeCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<RadomeCommandEntity>>( );
        }
    }

    public class RadomeCommandByReplyEntityIndex
    {
        public class ByReply
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<RadomeCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<RadomeCommandEntity>>( );
        }
    }

    public class RadomeCommandByReplyIsNullEntityIndex
    {
    }

    public class RadomeCommandReplyByRadomeAndTimestampEntityIndex
    {
        public class ByRadome
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<RadomeCommandReplyEntity>> _entries = new SortedListEx<Guid, WeakReference<RadomeCommandReplyEntity>>( );
        }
    }

    public class RadomeCommandReplyByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<RadomeCommandReplyEntity>> _entries = new SortedListEx<Guid, WeakReference<RadomeCommandReplyEntity>>( );
        }
    }

    public class RadomeCommandReplyByCommandEntityIndex
    {
        readonly SortedWeakReferenceList<Guid, RadomeCommandReplyEntity> _entries = new SortedWeakReferenceList<Guid, RadomeCommandReplyEntity>( );

        public RadomeCommandReplyByCommandEntityIndex( )
        {
        }

        public void Add( RadomeCommandReplyEntity entity )
        {
            if ( entity.CommandId is Guid command )
            {
                if ( _entries.TryGetValue( command, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( command, new WeakReference<RadomeCommandReplyEntity>( entity, false ) );
                }
            }
            else
            {
                throw new ArgumentException( "entity.CommandId is null.", nameof( entity ) );
            }
        }

        public bool GetByCommandId( Guid command, out RadomeCommandReplyEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( command, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( command );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(Guid key, [DisallowNull] IList<RadomeCommandReplyEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(Guid key, [DisallowNull] IList<RadomeCommandReplyEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<RadomeCommandReplyEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<RadomeCommandReplyEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class RadomeCommandReplyByCommandIsNullEntityIndex
    {
    }

    public class RadomeConfigurationByRadomeAndTimestampEntityIndex
    {
        public class ByRadome
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, RadomeConfigurationEntity> _entries = new SortedWeakReferenceList<DateTime, RadomeConfigurationEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( RadomeConfigurationEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<RadomeConfigurationEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out RadomeConfigurationEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<RadomeConfigurationEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<RadomeConfigurationEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<RadomeConfigurationEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<RadomeConfigurationEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class RadomeConfigurationByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<RadomeConfigurationEntity>> _entries = new SortedListEx<Guid, WeakReference<RadomeConfigurationEntity>>( );
        }
    }

    public class ReferenceTimeseriesValueByTimeseriesAndTimestampEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, ReferenceTimeseriesValueEntity> _entries = new SortedWeakReferenceList<DateTime, ReferenceTimeseriesValueEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( ReferenceTimeseriesValueEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<ReferenceTimeseriesValueEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out ReferenceTimeseriesValueEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<ReferenceTimeseriesValueEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<ReferenceTimeseriesValueEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<ReferenceTimeseriesValueEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<ReferenceTimeseriesValueEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class ReferenceTimeseriesValueByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<ReferenceTimeseriesValueEntity>> _entries = new SortedListEx<Guid, WeakReference<ReferenceTimeseriesValueEntity>>( );
        }
    }

    public class ReferenceTimeseriesValueByValueEntityIndex
    {
        public class ByValue
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<ReferenceTimeseriesValueEntity>> _entries = new SortedListEx<Guid, WeakReference<ReferenceTimeseriesValueEntity>>( );
        }
    }

    public class SByteTimeseriesValueByTimeseriesAndTimestampEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, SByteTimeseriesValueEntity> _entries = new SortedWeakReferenceList<DateTime, SByteTimeseriesValueEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( SByteTimeseriesValueEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<SByteTimeseriesValueEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out SByteTimeseriesValueEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<SByteTimeseriesValueEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<SByteTimeseriesValueEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<SByteTimeseriesValueEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<SByteTimeseriesValueEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class SByteTimeseriesValueByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<SByteTimeseriesValueEntity>> _entries = new SortedListEx<Guid, WeakReference<SByteTimeseriesValueEntity>>( );
        }
    }

    public class SecurityDomainByNameEntityIndex
    {
        readonly SortedWeakReferenceList<string, SecurityDomainEntity> _entries = new SortedWeakReferenceList<string, SecurityDomainEntity>( );

        public SecurityDomainByNameEntityIndex( )
        {
        }

        public void Add( SecurityDomainEntity entity )
        {
            if( _entries.TryGetValue(entity.Name, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Name, new WeakReference<SecurityDomainEntity>( entity, false ) );
            }
        }

        public bool GetByName( string name, out SecurityDomainEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( name, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( name );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(string key, [DisallowNull] IList<SecurityDomainEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(string key, [DisallowNull] IList<SecurityDomainEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<SecurityDomainEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<SecurityDomainEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class SecurityIdentifierByDomainAndIdentityEntityIndex
    {
        public class ByDomain
        {
            readonly SortedListEx<Guid, ByIdentity> _entries = new SortedListEx<Guid, ByIdentity>( );
        }
        public class ByIdentity
        {
            readonly SortedWeakReferenceList<string, SecurityIdentifierEntity> _entries = new SortedWeakReferenceList<string, SecurityIdentifierEntity>( );

            public ByIdentity( )
            {
            }

            public void Add( SecurityIdentifierEntity entity )
            {
                if( _entries.TryGetValue(entity.Identity, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Identity, new WeakReference<SecurityIdentifierEntity>( entity, false ) );
                }
            }

            public bool GetByIdentity( string identity, out SecurityIdentifierEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( identity, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( identity );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(string key, [DisallowNull] IList<SecurityIdentifierEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(string key, [DisallowNull] IList<SecurityIdentifierEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<SecurityIdentifierEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<SecurityIdentifierEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class SecurityRoleByNameEntityIndex
    {
        readonly SortedWeakReferenceList<string, SecurityRoleEntity> _entries = new SortedWeakReferenceList<string, SecurityRoleEntity>( );

        public SecurityRoleByNameEntityIndex( )
        {
        }

        public void Add( SecurityRoleEntity entity )
        {
            if( _entries.TryGetValue(entity.Name, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Name, new WeakReference<SecurityRoleEntity>( entity, false ) );
            }
        }

        public bool GetByName( string name, out SecurityRoleEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( name, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( name );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(string key, [DisallowNull] IList<SecurityRoleEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(string key, [DisallowNull] IList<SecurityRoleEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<SecurityRoleEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<SecurityRoleEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class SecurityIdentifierRoleLinkByMemberAndStartEntityIndex
    {
        public class ByMember
        {
            readonly SortedListEx<Guid, ByStart> _entries = new SortedListEx<Guid, ByStart>( );
        }
        public class ByStart
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<SecurityIdentifierRoleLinkEntity>> _entries = new SortedListEx<Guid, WeakReference<SecurityIdentifierRoleLinkEntity>>( );
        }
    }

    public class SecurityIdentifierRoleLinkByRoleAndStartEntityIndex
    {
        public class ByRole
        {
            readonly SortedListEx<Guid, ByStart> _entries = new SortedListEx<Guid, ByStart>( );
        }
        public class ByStart
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<SecurityIdentifierRoleLinkEntity>> _entries = new SortedListEx<Guid, WeakReference<SecurityIdentifierRoleLinkEntity>>( );
        }
    }

    public class SecurityIdentifierRoleLinkByStartEntityIndex
    {
        public class ByStart
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<SecurityIdentifierRoleLinkEntity>> _entries = new SortedListEx<Guid, WeakReference<SecurityIdentifierRoleLinkEntity>>( );
        }
    }

    public class SecurityLoginSessionByLoginAndFromTimeEntityIndex
    {
        public class ByLogin
        {
            readonly SortedListEx<Guid, ByFromTime> _entries = new SortedListEx<Guid, ByFromTime>( );
        }
        public class ByFromTime
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<SecurityLoginSessionEntity>> _entries = new SortedListEx<Guid, WeakReference<SecurityLoginSessionEntity>>( );
        }
    }

    public class SecurityLoginSessionByFromTimeEntityIndex
    {
        public class ByFromTime
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<SecurityLoginSessionEntity>> _entries = new SortedListEx<Guid, WeakReference<SecurityLoginSessionEntity>>( );
        }
    }

    public class SecurityPermissionByIdentifierTypeCodeAndTimestampEntityIndex
    {
        public class ByIdentifier
        {
            readonly SortedListEx<Guid, ByTypeCode> _entries = new SortedListEx<Guid, ByTypeCode>( );
        }
        public class ByTypeCode
        {
            readonly SortedListEx<int, ByTimestamp> _entries = new SortedListEx<int, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, SecurityPermissionEntity> _entries = new SortedWeakReferenceList<DateTime, SecurityPermissionEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( SecurityPermissionEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<SecurityPermissionEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out SecurityPermissionEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<SecurityPermissionEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<SecurityPermissionEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<SecurityPermissionEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<SecurityPermissionEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class SecurityPermissionByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<SecurityPermissionEntity>> _entries = new SortedListEx<Guid, WeakReference<SecurityPermissionEntity>>( );
        }
    }

    public class SingleTimeseriesValueByTimeseriesAndTimestampEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, SingleTimeseriesValueEntity> _entries = new SortedWeakReferenceList<DateTime, SingleTimeseriesValueEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( SingleTimeseriesValueEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<SingleTimeseriesValueEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out SingleTimeseriesValueEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<SingleTimeseriesValueEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<SingleTimeseriesValueEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<SingleTimeseriesValueEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<SingleTimeseriesValueEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class SingleTimeseriesValueByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<SingleTimeseriesValueEntity>> _entries = new SortedListEx<Guid, WeakReference<SingleTimeseriesValueEntity>>( );
        }
    }

    public class StringTimeseriesValueByTimeseriesAndTimestampEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, StringTimeseriesValueEntity> _entries = new SortedWeakReferenceList<DateTime, StringTimeseriesValueEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( StringTimeseriesValueEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<StringTimeseriesValueEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out StringTimeseriesValueEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<StringTimeseriesValueEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<StringTimeseriesValueEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<StringTimeseriesValueEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<StringTimeseriesValueEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class StringTimeseriesValueByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<StringTimeseriesValueEntity>> _entries = new SortedListEx<Guid, WeakReference<StringTimeseriesValueEntity>>( );
        }
    }

    public class TimeseriesCatalogElementByCatalogAndNameEntityIndex
    {
        public class ByCatalog
        {
            readonly SortedListEx<Guid, ByName> _entries = new SortedListEx<Guid, ByName>( );
        }
        public class ByName
        {
            readonly SortedWeakReferenceList<string, TimeseriesCatalogElementEntity> _entries = new SortedWeakReferenceList<string, TimeseriesCatalogElementEntity>( );

            public ByName( )
            {
            }

            public void Add( TimeseriesCatalogElementEntity entity )
            {
                if( _entries.TryGetValue(entity.Name, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Name, new WeakReference<TimeseriesCatalogElementEntity>( entity, false ) );
                }
            }

            public bool GetByName( string name, out TimeseriesCatalogElementEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( name, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( name );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(string key, [DisallowNull] IList<TimeseriesCatalogElementEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(string key, [DisallowNull] IList<TimeseriesCatalogElementEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<TimeseriesCatalogElementEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<TimeseriesCatalogElementEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class TimeseriesCatalogElementByCatalogIsNullAndNameEntityIndex
    {
    }

    public class AisAidToNavigationOffPositionTimeseriesByAidToNavigationEntityIndex
    {
        public class ByAidToNavigation
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<AisAidToNavigationOffPositionTimeseriesEntity>> _entries = new SortedListEx<Guid, WeakReference<AisAidToNavigationOffPositionTimeseriesEntity>>( );
        }
    }

    public class AisAidToNavigationOffPositionTimeseriesByAidToNavigationIsNullEntityIndex
    {
    }

    public class GyroCourseTimeseriesByGyroDeviceEntityIndex
    {
        readonly SortedWeakReferenceList<Guid, GyroCourseTimeseriesEntity> _entries = new SortedWeakReferenceList<Guid, GyroCourseTimeseriesEntity>( );

        public GyroCourseTimeseriesByGyroDeviceEntityIndex( )
        {
        }

        public void Add( GyroCourseTimeseriesEntity entity )
        {
            if ( entity.GyroDeviceId is Guid gyroDevice )
            {
                if ( _entries.TryGetValue( gyroDevice, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( gyroDevice, new WeakReference<GyroCourseTimeseriesEntity>( entity, false ) );
                }
            }
            else
            {
                throw new ArgumentException( "entity.GyroDeviceId is null.", nameof( entity ) );
            }
        }

        public bool GetByGyroDeviceId( Guid gyroDevice, out GyroCourseTimeseriesEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( gyroDevice, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( gyroDevice );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(Guid key, [DisallowNull] IList<GyroCourseTimeseriesEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(Guid key, [DisallowNull] IList<GyroCourseTimeseriesEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<GyroCourseTimeseriesEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<GyroCourseTimeseriesEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class GyroCourseTimeseriesByGyroDeviceIsNullEntityIndex
    {
    }

    public class GyroHeadingMagneticNorthTimeseriesByGyroDeviceEntityIndex
    {
        readonly SortedWeakReferenceList<Guid, GyroHeadingMagneticNorthTimeseriesEntity> _entries = new SortedWeakReferenceList<Guid, GyroHeadingMagneticNorthTimeseriesEntity>( );

        public GyroHeadingMagneticNorthTimeseriesByGyroDeviceEntityIndex( )
        {
        }

        public void Add( GyroHeadingMagneticNorthTimeseriesEntity entity )
        {
            if ( entity.GyroDeviceId is Guid gyroDevice )
            {
                if ( _entries.TryGetValue( gyroDevice, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( gyroDevice, new WeakReference<GyroHeadingMagneticNorthTimeseriesEntity>( entity, false ) );
                }
            }
            else
            {
                throw new ArgumentException( "entity.GyroDeviceId is null.", nameof( entity ) );
            }
        }

        public bool GetByGyroDeviceId( Guid gyroDevice, out GyroHeadingMagneticNorthTimeseriesEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( gyroDevice, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( gyroDevice );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(Guid key, [DisallowNull] IList<GyroHeadingMagneticNorthTimeseriesEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(Guid key, [DisallowNull] IList<GyroHeadingMagneticNorthTimeseriesEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<GyroHeadingMagneticNorthTimeseriesEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<GyroHeadingMagneticNorthTimeseriesEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class GyroHeadingMagneticNorthTimeseriesByGyroDeviceIsNullEntityIndex
    {
    }

    public class GyroHeadingTrueNorthTimeseriesByGyroDeviceEntityIndex
    {
        readonly SortedWeakReferenceList<Guid, GyroHeadingTrueNorthTimeseriesEntity> _entries = new SortedWeakReferenceList<Guid, GyroHeadingTrueNorthTimeseriesEntity>( );

        public GyroHeadingTrueNorthTimeseriesByGyroDeviceEntityIndex( )
        {
        }

        public void Add( GyroHeadingTrueNorthTimeseriesEntity entity )
        {
            if ( entity.GyroDeviceId is Guid gyroDevice )
            {
                if ( _entries.TryGetValue( gyroDevice, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( gyroDevice, new WeakReference<GyroHeadingTrueNorthTimeseriesEntity>( entity, false ) );
                }
            }
            else
            {
                throw new ArgumentException( "entity.GyroDeviceId is null.", nameof( entity ) );
            }
        }

        public bool GetByGyroDeviceId( Guid gyroDevice, out GyroHeadingTrueNorthTimeseriesEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( gyroDevice, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( gyroDevice );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(Guid key, [DisallowNull] IList<GyroHeadingTrueNorthTimeseriesEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(Guid key, [DisallowNull] IList<GyroHeadingTrueNorthTimeseriesEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<GyroHeadingTrueNorthTimeseriesEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<GyroHeadingTrueNorthTimeseriesEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class GyroHeadingTrueNorthTimeseriesByGyroDeviceIsNullEntityIndex
    {
    }

    public class GyroPitchTimeseriesByGyroDeviceEntityIndex
    {
        readonly SortedWeakReferenceList<Guid, GyroPitchTimeseriesEntity> _entries = new SortedWeakReferenceList<Guid, GyroPitchTimeseriesEntity>( );

        public GyroPitchTimeseriesByGyroDeviceEntityIndex( )
        {
        }

        public void Add( GyroPitchTimeseriesEntity entity )
        {
            if ( entity.GyroDeviceId is Guid gyroDevice )
            {
                if ( _entries.TryGetValue( gyroDevice, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( gyroDevice, new WeakReference<GyroPitchTimeseriesEntity>( entity, false ) );
                }
            }
            else
            {
                throw new ArgumentException( "entity.GyroDeviceId is null.", nameof( entity ) );
            }
        }

        public bool GetByGyroDeviceId( Guid gyroDevice, out GyroPitchTimeseriesEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( gyroDevice, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( gyroDevice );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(Guid key, [DisallowNull] IList<GyroPitchTimeseriesEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(Guid key, [DisallowNull] IList<GyroPitchTimeseriesEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<GyroPitchTimeseriesEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<GyroPitchTimeseriesEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class GyroPitchTimeseriesByGyroDeviceIsNullEntityIndex
    {
    }

    public class GyroRateOfTurnTimeseriesByGyroDeviceEntityIndex
    {
        readonly SortedWeakReferenceList<Guid, GyroRateOfTurnTimeseriesEntity> _entries = new SortedWeakReferenceList<Guid, GyroRateOfTurnTimeseriesEntity>( );

        public GyroRateOfTurnTimeseriesByGyroDeviceEntityIndex( )
        {
        }

        public void Add( GyroRateOfTurnTimeseriesEntity entity )
        {
            if ( entity.GyroDeviceId is Guid gyroDevice )
            {
                if ( _entries.TryGetValue( gyroDevice, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( gyroDevice, new WeakReference<GyroRateOfTurnTimeseriesEntity>( entity, false ) );
                }
            }
            else
            {
                throw new ArgumentException( "entity.GyroDeviceId is null.", nameof( entity ) );
            }
        }

        public bool GetByGyroDeviceId( Guid gyroDevice, out GyroRateOfTurnTimeseriesEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( gyroDevice, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( gyroDevice );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(Guid key, [DisallowNull] IList<GyroRateOfTurnTimeseriesEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(Guid key, [DisallowNull] IList<GyroRateOfTurnTimeseriesEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<GyroRateOfTurnTimeseriesEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<GyroRateOfTurnTimeseriesEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class GyroRateOfTurnTimeseriesByGyroDeviceIsNullEntityIndex
    {
    }

    public class GyroRollTimeseriesByGyroDeviceEntityIndex
    {
        readonly SortedWeakReferenceList<Guid, GyroRollTimeseriesEntity> _entries = new SortedWeakReferenceList<Guid, GyroRollTimeseriesEntity>( );

        public GyroRollTimeseriesByGyroDeviceEntityIndex( )
        {
        }

        public void Add( GyroRollTimeseriesEntity entity )
        {
            if ( entity.GyroDeviceId is Guid gyroDevice )
            {
                if ( _entries.TryGetValue( gyroDevice, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( gyroDevice, new WeakReference<GyroRollTimeseriesEntity>( entity, false ) );
                }
            }
            else
            {
                throw new ArgumentException( "entity.GyroDeviceId is null.", nameof( entity ) );
            }
        }

        public bool GetByGyroDeviceId( Guid gyroDevice, out GyroRollTimeseriesEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( gyroDevice, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( gyroDevice );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(Guid key, [DisallowNull] IList<GyroRollTimeseriesEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(Guid key, [DisallowNull] IList<GyroRollTimeseriesEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<GyroRollTimeseriesEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<GyroRollTimeseriesEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class GyroRollTimeseriesByGyroDeviceIsNullEntityIndex
    {
    }

    public class GyroSpeedTimeseriesByGyroDeviceEntityIndex
    {
        readonly SortedWeakReferenceList<Guid, GyroSpeedTimeseriesEntity> _entries = new SortedWeakReferenceList<Guid, GyroSpeedTimeseriesEntity>( );

        public GyroSpeedTimeseriesByGyroDeviceEntityIndex( )
        {
        }

        public void Add( GyroSpeedTimeseriesEntity entity )
        {
            if ( entity.GyroDeviceId is Guid gyroDevice )
            {
                if ( _entries.TryGetValue( gyroDevice, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( gyroDevice, new WeakReference<GyroSpeedTimeseriesEntity>( entity, false ) );
                }
            }
            else
            {
                throw new ArgumentException( "entity.GyroDeviceId is null.", nameof( entity ) );
            }
        }

        public bool GetByGyroDeviceId( Guid gyroDevice, out GyroSpeedTimeseriesEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( gyroDevice, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( gyroDevice );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(Guid key, [DisallowNull] IList<GyroSpeedTimeseriesEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(Guid key, [DisallowNull] IList<GyroSpeedTimeseriesEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<GyroSpeedTimeseriesEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<GyroSpeedTimeseriesEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class GyroSpeedTimeseriesByGyroDeviceIsNullEntityIndex
    {
    }

    public class WeatherStationAbsoluteHumidityTimeseriesByWeatherStationEntityIndex
    {
        readonly SortedWeakReferenceList<Guid, WeatherStationAbsoluteHumidityTimeseriesEntity> _entries = new SortedWeakReferenceList<Guid, WeatherStationAbsoluteHumidityTimeseriesEntity>( );

        public WeatherStationAbsoluteHumidityTimeseriesByWeatherStationEntityIndex( )
        {
        }

        public void Add( WeatherStationAbsoluteHumidityTimeseriesEntity entity )
        {
            if ( entity.WeatherStationId is Guid weatherStation )
            {
                if ( _entries.TryGetValue( weatherStation, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( weatherStation, new WeakReference<WeatherStationAbsoluteHumidityTimeseriesEntity>( entity, false ) );
                }
            }
            else
            {
                throw new ArgumentException( "entity.WeatherStationId is null.", nameof( entity ) );
            }
        }

        public bool GetByWeatherStationId( Guid weatherStation, out WeatherStationAbsoluteHumidityTimeseriesEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( weatherStation, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( weatherStation );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(Guid key, [DisallowNull] IList<WeatherStationAbsoluteHumidityTimeseriesEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(Guid key, [DisallowNull] IList<WeatherStationAbsoluteHumidityTimeseriesEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<WeatherStationAbsoluteHumidityTimeseriesEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<WeatherStationAbsoluteHumidityTimeseriesEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class WeatherStationAbsoluteHumidityTimeseriesByWeatherStationIsNullEntityIndex
    {
    }

    public class WeatherStationAirTemperatureTimeseriesByWeatherStationEntityIndex
    {
        readonly SortedWeakReferenceList<Guid, WeatherStationAirTemperatureTimeseriesEntity> _entries = new SortedWeakReferenceList<Guid, WeatherStationAirTemperatureTimeseriesEntity>( );

        public WeatherStationAirTemperatureTimeseriesByWeatherStationEntityIndex( )
        {
        }

        public void Add( WeatherStationAirTemperatureTimeseriesEntity entity )
        {
            if ( entity.WeatherStationId is Guid weatherStation )
            {
                if ( _entries.TryGetValue( weatherStation, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( weatherStation, new WeakReference<WeatherStationAirTemperatureTimeseriesEntity>( entity, false ) );
                }
            }
            else
            {
                throw new ArgumentException( "entity.WeatherStationId is null.", nameof( entity ) );
            }
        }

        public bool GetByWeatherStationId( Guid weatherStation, out WeatherStationAirTemperatureTimeseriesEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( weatherStation, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( weatherStation );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(Guid key, [DisallowNull] IList<WeatherStationAirTemperatureTimeseriesEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(Guid key, [DisallowNull] IList<WeatherStationAirTemperatureTimeseriesEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<WeatherStationAirTemperatureTimeseriesEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<WeatherStationAirTemperatureTimeseriesEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class WeatherStationAirTemperatureTimeseriesByWeatherStationIsNullEntityIndex
    {
    }

    public class WeatherStationBarometricPressureTimeseriesByWeatherStationEntityIndex
    {
        readonly SortedWeakReferenceList<Guid, WeatherStationBarometricPressureTimeseriesEntity> _entries = new SortedWeakReferenceList<Guid, WeatherStationBarometricPressureTimeseriesEntity>( );

        public WeatherStationBarometricPressureTimeseriesByWeatherStationEntityIndex( )
        {
        }

        public void Add( WeatherStationBarometricPressureTimeseriesEntity entity )
        {
            if ( entity.WeatherStationId is Guid weatherStation )
            {
                if ( _entries.TryGetValue( weatherStation, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( weatherStation, new WeakReference<WeatherStationBarometricPressureTimeseriesEntity>( entity, false ) );
                }
            }
            else
            {
                throw new ArgumentException( "entity.WeatherStationId is null.", nameof( entity ) );
            }
        }

        public bool GetByWeatherStationId( Guid weatherStation, out WeatherStationBarometricPressureTimeseriesEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( weatherStation, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( weatherStation );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(Guid key, [DisallowNull] IList<WeatherStationBarometricPressureTimeseriesEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(Guid key, [DisallowNull] IList<WeatherStationBarometricPressureTimeseriesEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<WeatherStationBarometricPressureTimeseriesEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<WeatherStationBarometricPressureTimeseriesEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class WeatherStationBarometricPressureTimeseriesByWeatherStationIsNullEntityIndex
    {
    }

    public class WeatherStationDewPointTimeseriesByWeatherStationEntityIndex
    {
        readonly SortedWeakReferenceList<Guid, WeatherStationDewPointTimeseriesEntity> _entries = new SortedWeakReferenceList<Guid, WeatherStationDewPointTimeseriesEntity>( );

        public WeatherStationDewPointTimeseriesByWeatherStationEntityIndex( )
        {
        }

        public void Add( WeatherStationDewPointTimeseriesEntity entity )
        {
            if ( entity.WeatherStationId is Guid weatherStation )
            {
                if ( _entries.TryGetValue( weatherStation, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( weatherStation, new WeakReference<WeatherStationDewPointTimeseriesEntity>( entity, false ) );
                }
            }
            else
            {
                throw new ArgumentException( "entity.WeatherStationId is null.", nameof( entity ) );
            }
        }

        public bool GetByWeatherStationId( Guid weatherStation, out WeatherStationDewPointTimeseriesEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( weatherStation, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( weatherStation );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(Guid key, [DisallowNull] IList<WeatherStationDewPointTimeseriesEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(Guid key, [DisallowNull] IList<WeatherStationDewPointTimeseriesEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<WeatherStationDewPointTimeseriesEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<WeatherStationDewPointTimeseriesEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class WeatherStationDewPointTimeseriesByWeatherStationIsNullEntityIndex
    {
    }

    public class WeatherStationRelativeHumidityTimeseriesByWeatherStationEntityIndex
    {
        readonly SortedWeakReferenceList<Guid, WeatherStationRelativeHumidityTimeseriesEntity> _entries = new SortedWeakReferenceList<Guid, WeatherStationRelativeHumidityTimeseriesEntity>( );

        public WeatherStationRelativeHumidityTimeseriesByWeatherStationEntityIndex( )
        {
        }

        public void Add( WeatherStationRelativeHumidityTimeseriesEntity entity )
        {
            if ( entity.WeatherStationId is Guid weatherStation )
            {
                if ( _entries.TryGetValue( weatherStation, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( weatherStation, new WeakReference<WeatherStationRelativeHumidityTimeseriesEntity>( entity, false ) );
                }
            }
            else
            {
                throw new ArgumentException( "entity.WeatherStationId is null.", nameof( entity ) );
            }
        }

        public bool GetByWeatherStationId( Guid weatherStation, out WeatherStationRelativeHumidityTimeseriesEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( weatherStation, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( weatherStation );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(Guid key, [DisallowNull] IList<WeatherStationRelativeHumidityTimeseriesEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(Guid key, [DisallowNull] IList<WeatherStationRelativeHumidityTimeseriesEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<WeatherStationRelativeHumidityTimeseriesEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<WeatherStationRelativeHumidityTimeseriesEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class WeatherStationRelativeHumidityTimeseriesByWeatherStationIsNullEntityIndex
    {
    }

    public class WeatherStationWaterTemperatureTimeseriesByWeatherStationEntityIndex
    {
        readonly SortedWeakReferenceList<Guid, WeatherStationWaterTemperatureTimeseriesEntity> _entries = new SortedWeakReferenceList<Guid, WeatherStationWaterTemperatureTimeseriesEntity>( );

        public WeatherStationWaterTemperatureTimeseriesByWeatherStationEntityIndex( )
        {
        }

        public void Add( WeatherStationWaterTemperatureTimeseriesEntity entity )
        {
            if ( entity.WeatherStationId is Guid weatherStation )
            {
                if ( _entries.TryGetValue( weatherStation, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( weatherStation, new WeakReference<WeatherStationWaterTemperatureTimeseriesEntity>( entity, false ) );
                }
            }
            else
            {
                throw new ArgumentException( "entity.WeatherStationId is null.", nameof( entity ) );
            }
        }

        public bool GetByWeatherStationId( Guid weatherStation, out WeatherStationWaterTemperatureTimeseriesEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( weatherStation, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( weatherStation );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(Guid key, [DisallowNull] IList<WeatherStationWaterTemperatureTimeseriesEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(Guid key, [DisallowNull] IList<WeatherStationWaterTemperatureTimeseriesEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<WeatherStationWaterTemperatureTimeseriesEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<WeatherStationWaterTemperatureTimeseriesEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class WeatherStationWaterTemperatureTimeseriesByWeatherStationIsNullEntityIndex
    {
    }

    public class WeatherStationWindDirectionTimeseriesByWeatherStationEntityIndex
    {
        readonly SortedWeakReferenceList<Guid, WeatherStationWindDirectionTimeseriesEntity> _entries = new SortedWeakReferenceList<Guid, WeatherStationWindDirectionTimeseriesEntity>( );

        public WeatherStationWindDirectionTimeseriesByWeatherStationEntityIndex( )
        {
        }

        public void Add( WeatherStationWindDirectionTimeseriesEntity entity )
        {
            if ( entity.WeatherStationId is Guid weatherStation )
            {
                if ( _entries.TryGetValue( weatherStation, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( weatherStation, new WeakReference<WeatherStationWindDirectionTimeseriesEntity>( entity, false ) );
                }
            }
            else
            {
                throw new ArgumentException( "entity.WeatherStationId is null.", nameof( entity ) );
            }
        }

        public bool GetByWeatherStationId( Guid weatherStation, out WeatherStationWindDirectionTimeseriesEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( weatherStation, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( weatherStation );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(Guid key, [DisallowNull] IList<WeatherStationWindDirectionTimeseriesEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(Guid key, [DisallowNull] IList<WeatherStationWindDirectionTimeseriesEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<WeatherStationWindDirectionTimeseriesEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<WeatherStationWindDirectionTimeseriesEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class WeatherStationWindDirectionTimeseriesByWeatherStationIsNullEntityIndex
    {
    }

    public class WeatherStationWindSpeedTimeseriesByWeatherStationEntityIndex
    {
        readonly SortedWeakReferenceList<Guid, WeatherStationWindSpeedTimeseriesEntity> _entries = new SortedWeakReferenceList<Guid, WeatherStationWindSpeedTimeseriesEntity>( );

        public WeatherStationWindSpeedTimeseriesByWeatherStationEntityIndex( )
        {
        }

        public void Add( WeatherStationWindSpeedTimeseriesEntity entity )
        {
            if ( entity.WeatherStationId is Guid weatherStation )
            {
                if ( _entries.TryGetValue( weatherStation, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( weatherStation, new WeakReference<WeatherStationWindSpeedTimeseriesEntity>( entity, false ) );
                }
            }
            else
            {
                throw new ArgumentException( "entity.WeatherStationId is null.", nameof( entity ) );
            }
        }

        public bool GetByWeatherStationId( Guid weatherStation, out WeatherStationWindSpeedTimeseriesEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( weatherStation, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( weatherStation );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(Guid key, [DisallowNull] IList<WeatherStationWindSpeedTimeseriesEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(Guid key, [DisallowNull] IList<WeatherStationWindSpeedTimeseriesEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<WeatherStationWindSpeedTimeseriesEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<WeatherStationWindSpeedTimeseriesEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class WeatherStationWindSpeedTimeseriesByWeatherStationIsNullEntityIndex
    {
    }

    public class TimeSpanTimeseriesValueByTimeseriesAndTimestampEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, TimeSpanTimeseriesValueEntity> _entries = new SortedWeakReferenceList<DateTime, TimeSpanTimeseriesValueEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( TimeSpanTimeseriesValueEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<TimeSpanTimeseriesValueEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out TimeSpanTimeseriesValueEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<TimeSpanTimeseriesValueEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<TimeSpanTimeseriesValueEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<TimeSpanTimeseriesValueEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<TimeSpanTimeseriesValueEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class TimeSpanTimeseriesValueByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<TimeSpanTimeseriesValueEntity>> _entries = new SortedListEx<Guid, WeakReference<TimeSpanTimeseriesValueEntity>>( );
        }
    }

    public class TrackableItemTrackLinkByItemAndStartEntityIndex
    {
        public class ByItem
        {
            readonly SortedListEx<Guid, ByStart> _entries = new SortedListEx<Guid, ByStart>( );
        }
        public class ByStart
        {
            readonly SortedWeakReferenceList<DateTime, TrackableItemTrackLinkEntity> _entries = new SortedWeakReferenceList<DateTime, TrackableItemTrackLinkEntity>( );

            public ByStart( )
            {
            }

            public void Add( TrackableItemTrackLinkEntity entity )
            {
                if( _entries.TryGetValue(entity.Start, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Start, new WeakReference<TrackableItemTrackLinkEntity>( entity, false ) );
                }
            }

            public bool GetByStart( DateTime start, out TrackableItemTrackLinkEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( start, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( start );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<TrackableItemTrackLinkEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<TrackableItemTrackLinkEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<TrackableItemTrackLinkEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<TrackableItemTrackLinkEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class TrackableItemTrackLinkByItemAndEndEntityIndex
    {
        public class ByItem
        {
            readonly SortedListEx<Guid, ByEnd> _entries = new SortedListEx<Guid, ByEnd>( );
        }
        public class ByEnd
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<TrackableItemTrackLinkEntity>> _entries = new SortedListEx<Guid, WeakReference<TrackableItemTrackLinkEntity>>( );
        }
    }

    public class TrackableItemTrackLinkByItemAndEndIsNullEntityIndex
    {
    }

    public class TrackableItemTrackLinkByTrackAndStartEntityIndex
    {
        public class ByTrack
        {
            readonly SortedListEx<Guid, ByStart> _entries = new SortedListEx<Guid, ByStart>( );
        }
        public class ByStart
        {
            readonly SortedWeakReferenceList<DateTime, TrackableItemTrackLinkEntity> _entries = new SortedWeakReferenceList<DateTime, TrackableItemTrackLinkEntity>( );

            public ByStart( )
            {
            }

            public void Add( TrackableItemTrackLinkEntity entity )
            {
                if( _entries.TryGetValue(entity.Start, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Start, new WeakReference<TrackableItemTrackLinkEntity>( entity, false ) );
                }
            }

            public bool GetByStart( DateTime start, out TrackableItemTrackLinkEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( start, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( start );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<TrackableItemTrackLinkEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<TrackableItemTrackLinkEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<TrackableItemTrackLinkEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<TrackableItemTrackLinkEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class TrackableItemTrackLinkByTrackAndEndEntityIndex
    {
        public class ByTrack
        {
            readonly SortedListEx<Guid, ByEnd> _entries = new SortedListEx<Guid, ByEnd>( );
        }
        public class ByEnd
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<TrackableItemTrackLinkEntity>> _entries = new SortedListEx<Guid, WeakReference<TrackableItemTrackLinkEntity>>( );
        }
    }

    public class TrackableItemTrackLinkByTrackAndEndIsNullEntityIndex
    {
    }

    public class TrackableItemTrackLinkByStartEntityIndex
    {
        public class ByStart
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<TrackableItemTrackLinkEntity>> _entries = new SortedListEx<Guid, WeakReference<TrackableItemTrackLinkEntity>>( );
        }
    }

    public class TrackBaseByTrackerTrackNumberAndTimestampEntityIndex
    {
        public class ByTracker
        {
            readonly SortedListEx<Guid, ByTrackNumber> _entries = new SortedListEx<Guid, ByTrackNumber>( );
        }
        public class ByTrackNumber
        {
            readonly SortedListEx<long, ByTimestamp> _entries = new SortedListEx<long, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, TrackBaseEntity> _entries = new SortedWeakReferenceList<DateTime, TrackBaseEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( TrackBaseEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<TrackBaseEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out TrackBaseEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<TrackBaseEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<TrackBaseEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<TrackBaseEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<TrackBaseEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class TrackBaseByTrackerAndTimestampEntityIndex
    {
        public class ByTracker
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<TrackBaseEntity>> _entries = new SortedListEx<Guid, WeakReference<TrackBaseEntity>>( );
        }
    }

    public class TrackBaseByTrackNumberEntityIndex
    {
        public class ByTrackNumber
        {
            readonly SortedListEx<long, ById> _entries = new SortedListEx<long, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<TrackBaseEntity>> _entries = new SortedListEx<Guid, WeakReference<TrackBaseEntity>>( );
        }
    }

    public class TrackBaseByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<TrackBaseEntity>> _entries = new SortedListEx<Guid, WeakReference<TrackBaseEntity>>( );
        }
    }

    public class TrackerFilterParametersByTrackerAndNameEntityIndex
    {
        public class ByTracker
        {
            readonly SortedListEx<Guid, ByName> _entries = new SortedListEx<Guid, ByName>( );
        }
        public class ByName
        {
            readonly SortedWeakReferenceList<string, TrackerFilterParametersEntity> _entries = new SortedWeakReferenceList<string, TrackerFilterParametersEntity>( );

            public ByName( )
            {
            }

            public void Add( TrackerFilterParametersEntity entity )
            {
                if( _entries.TryGetValue(entity.Name, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Name, new WeakReference<TrackerFilterParametersEntity>( entity, false ) );
                }
            }

            public bool GetByName( string name, out TrackerFilterParametersEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( name, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( name );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(string key, [DisallowNull] IList<TrackerFilterParametersEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(string key, [DisallowNull] IList<TrackerFilterParametersEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<TrackerFilterParametersEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<TrackerFilterParametersEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class TrackerFilterParametersConfigurationByParametersAndTimestampEntityIndex
    {
        public class ByParameters
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, TrackerFilterParametersConfigurationEntity> _entries = new SortedWeakReferenceList<DateTime, TrackerFilterParametersConfigurationEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( TrackerFilterParametersConfigurationEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<TrackerFilterParametersConfigurationEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out TrackerFilterParametersConfigurationEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<TrackerFilterParametersConfigurationEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<TrackerFilterParametersConfigurationEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<TrackerFilterParametersConfigurationEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<TrackerFilterParametersConfigurationEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class TrackerFilterParametersConfigurationByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<TrackerFilterParametersConfigurationEntity>> _entries = new SortedListEx<Guid, WeakReference<TrackerFilterParametersConfigurationEntity>>( );
        }
    }

    public class TrackingServiceOptionsByTimestampEntityIndex
    {
        readonly SortedWeakReferenceList<DateTime, TrackingServiceOptionsEntity> _entries = new SortedWeakReferenceList<DateTime, TrackingServiceOptionsEntity>( );

        public TrackingServiceOptionsByTimestampEntityIndex( )
        {
        }

        public void Add( TrackingServiceOptionsEntity entity )
        {
            if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Timestamp, new WeakReference<TrackingServiceOptionsEntity>( entity, false ) );
            }
        }

        public bool GetByTimestamp( DateTime timestamp, out TrackingServiceOptionsEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( timestamp, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( timestamp );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(DateTime key, [DisallowNull] IList<TrackingServiceOptionsEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(DateTime key, [DisallowNull] IList<TrackingServiceOptionsEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<TrackingServiceOptionsEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<TrackingServiceOptionsEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class TrackLinkByPrimaryAndStartEntityIndex
    {
        public class ByPrimary
        {
            readonly SortedListEx<Guid, ByStart> _entries = new SortedListEx<Guid, ByStart>( );
        }
        public class ByStart
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<TrackLinkEntity>> _entries = new SortedListEx<Guid, WeakReference<TrackLinkEntity>>( );
        }
    }

    public class TrackLinkBySecondaryAndStartEntityIndex
    {
        public class BySecondary
        {
            readonly SortedListEx<Guid, ByStart> _entries = new SortedListEx<Guid, ByStart>( );
        }
        public class ByStart
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<TrackLinkEntity>> _entries = new SortedListEx<Guid, WeakReference<TrackLinkEntity>>( );
        }
    }

    public class TrackLinkByStartEntityIndex
    {
        public class ByStart
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<TrackLinkEntity>> _entries = new SortedListEx<Guid, WeakReference<TrackLinkEntity>>( );
        }
    }

    public class TrackValueByTrackAndTimestampEntityIndex
    {
        public class ByTrack
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, TrackValueEntity> _entries = new SortedWeakReferenceList<DateTime, TrackValueEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( TrackValueEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<TrackValueEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out TrackValueEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<TrackValueEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<TrackValueEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<TrackValueEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<TrackValueEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class TrackValueByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<TrackValueEntity>> _entries = new SortedListEx<Guid, WeakReference<TrackValueEntity>>( );
        }
    }

    public class TrackValue3DByTrackAndTimestampEntityIndex
    {
        public class ByTrack
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, TrackValue3DEntity> _entries = new SortedWeakReferenceList<DateTime, TrackValue3DEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( TrackValue3DEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<TrackValue3DEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out TrackValue3DEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<TrackValue3DEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<TrackValue3DEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<TrackValue3DEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<TrackValue3DEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class TrackValue3DByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<TrackValue3DEntity>> _entries = new SortedListEx<Guid, WeakReference<TrackValue3DEntity>>( );
        }
    }

    public class UInt16TimeseriesValueByTimeseriesAndTimestampEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, UInt16TimeseriesValueEntity> _entries = new SortedWeakReferenceList<DateTime, UInt16TimeseriesValueEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( UInt16TimeseriesValueEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<UInt16TimeseriesValueEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out UInt16TimeseriesValueEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<UInt16TimeseriesValueEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<UInt16TimeseriesValueEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<UInt16TimeseriesValueEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<UInt16TimeseriesValueEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class UInt16TimeseriesValueByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<UInt16TimeseriesValueEntity>> _entries = new SortedListEx<Guid, WeakReference<UInt16TimeseriesValueEntity>>( );
        }
    }

    public class UInt32TimeseriesValueByTimeseriesAndTimestampEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, UInt32TimeseriesValueEntity> _entries = new SortedWeakReferenceList<DateTime, UInt32TimeseriesValueEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( UInt32TimeseriesValueEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<UInt32TimeseriesValueEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out UInt32TimeseriesValueEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<UInt32TimeseriesValueEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<UInt32TimeseriesValueEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<UInt32TimeseriesValueEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<UInt32TimeseriesValueEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class UInt32TimeseriesValueByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<UInt32TimeseriesValueEntity>> _entries = new SortedListEx<Guid, WeakReference<UInt32TimeseriesValueEntity>>( );
        }
    }

    public class UInt64TimeseriesValueByTimeseriesAndTimestampEntityIndex
    {
        public class ByTimeseries
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, UInt64TimeseriesValueEntity> _entries = new SortedWeakReferenceList<DateTime, UInt64TimeseriesValueEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( UInt64TimeseriesValueEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<UInt64TimeseriesValueEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out UInt64TimeseriesValueEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<UInt64TimeseriesValueEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<UInt64TimeseriesValueEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<UInt64TimeseriesValueEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<UInt64TimeseriesValueEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class UInt64TimeseriesValueByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<UInt64TimeseriesValueEntity>> _entries = new SortedListEx<Guid, WeakReference<UInt64TimeseriesValueEntity>>( );
        }
    }

    public class VehicleTypeByNameEntityIndex
    {
        readonly SortedWeakReferenceList<string, VehicleTypeEntity> _entries = new SortedWeakReferenceList<string, VehicleTypeEntity>( );

        public VehicleTypeByNameEntityIndex( )
        {
        }

        public void Add( VehicleTypeEntity entity )
        {
            if( _entries.TryGetValue(entity.Name, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Name, new WeakReference<VehicleTypeEntity>( entity, false ) );
            }
        }

        public bool GetByName( string name, out VehicleTypeEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( name, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( name );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(string key, [DisallowNull] IList<VehicleTypeEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(string key, [DisallowNull] IList<VehicleTypeEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<VehicleTypeEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<VehicleTypeEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class VesselTypeByNameEntityIndex
    {
        readonly SortedWeakReferenceList<string, VesselTypeEntity> _entries = new SortedWeakReferenceList<string, VesselTypeEntity>( );

        public VesselTypeByNameEntityIndex( )
        {
        }

        public void Add( VesselTypeEntity entity )
        {
            if( _entries.TryGetValue(entity.Name, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Name, new WeakReference<VesselTypeEntity>( entity, false ) );
            }
        }

        public bool GetByName( string name, out VesselTypeEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( name, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( name );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(string key, [DisallowNull] IList<VesselTypeEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(string key, [DisallowNull] IList<VesselTypeEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<VesselTypeEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<VesselTypeEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class VesselTypeByCodeEntityIndex
    {
        readonly SortedWeakReferenceList<int, VesselTypeEntity> _entries = new SortedWeakReferenceList<int, VesselTypeEntity>( );

        public VesselTypeByCodeEntityIndex( )
        {
        }

        public void Add( VesselTypeEntity entity )
        {
            if( _entries.TryGetValue(entity.Code, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Code, new WeakReference<VesselTypeEntity>( entity, false ) );
            }
        }

        public bool GetByCode( int code, out VesselTypeEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( code, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( code );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(int key, [DisallowNull] IList<VesselTypeEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(int key, [DisallowNull] IList<VesselTypeEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(int firstKey, int lastKey, [DisallowNull] IList<VesselTypeEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<VesselTypeEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class ViewByNameEntityIndex
    {
        readonly SortedWeakReferenceList<string, ViewEntity> _entries = new SortedWeakReferenceList<string, ViewEntity>( );

        public ViewByNameEntityIndex( )
        {
        }

        public void Add( ViewEntity entity )
        {
            if( _entries.TryGetValue(entity.Name, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Name, new WeakReference<ViewEntity>( entity, false ) );
            }
        }

        public bool GetByName( string name, out ViewEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( name, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( name );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(string key, [DisallowNull] IList<ViewEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(string key, [DisallowNull] IList<ViewEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<ViewEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<ViewEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class ViewCameraLinkByViewAndStartEntityIndex
    {
        public class ByView
        {
            readonly SortedListEx<Guid, ByStart> _entries = new SortedListEx<Guid, ByStart>( );
        }
        public class ByStart
        {
            readonly SortedWeakReferenceList<DateTime, ViewCameraLinkEntity> _entries = new SortedWeakReferenceList<DateTime, ViewCameraLinkEntity>( );

            public ByStart( )
            {
            }

            public void Add( ViewCameraLinkEntity entity )
            {
                if( _entries.TryGetValue(entity.Start, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Start, new WeakReference<ViewCameraLinkEntity>( entity, false ) );
                }
            }

            public bool GetByStart( DateTime start, out ViewCameraLinkEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( start, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( start );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<ViewCameraLinkEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<ViewCameraLinkEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<ViewCameraLinkEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<ViewCameraLinkEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class ViewCameraLinkByCameraAndStartEntityIndex
    {
        public class ByCamera
        {
            readonly SortedListEx<Guid, ByStart> _entries = new SortedListEx<Guid, ByStart>( );
        }
        public class ByStart
        {
            readonly SortedWeakReferenceList<DateTime, ViewCameraLinkEntity> _entries = new SortedWeakReferenceList<DateTime, ViewCameraLinkEntity>( );

            public ByStart( )
            {
            }

            public void Add( ViewCameraLinkEntity entity )
            {
                if( _entries.TryGetValue(entity.Start, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Start, new WeakReference<ViewCameraLinkEntity>( entity, false ) );
                }
            }

            public bool GetByStart( DateTime start, out ViewCameraLinkEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( start, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( start );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<ViewCameraLinkEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<ViewCameraLinkEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<ViewCameraLinkEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<ViewCameraLinkEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class ViewCameraLinkByStartEntityIndex
    {
        public class ByStart
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<ViewCameraLinkEntity>> _entries = new SortedListEx<Guid, WeakReference<ViewCameraLinkEntity>>( );
        }
    }

    public class ViewTrackerLinkByViewAndStartEntityIndex
    {
        public class ByView
        {
            readonly SortedListEx<Guid, ByStart> _entries = new SortedListEx<Guid, ByStart>( );
        }
        public class ByStart
        {
            readonly SortedWeakReferenceList<DateTime, ViewTrackerLinkEntity> _entries = new SortedWeakReferenceList<DateTime, ViewTrackerLinkEntity>( );

            public ByStart( )
            {
            }

            public void Add( ViewTrackerLinkEntity entity )
            {
                if( _entries.TryGetValue(entity.Start, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Start, new WeakReference<ViewTrackerLinkEntity>( entity, false ) );
                }
            }

            public bool GetByStart( DateTime start, out ViewTrackerLinkEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( start, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( start );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<ViewTrackerLinkEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<ViewTrackerLinkEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<ViewTrackerLinkEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<ViewTrackerLinkEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class ViewTrackerLinkByTrackerAndStartEntityIndex
    {
        public class ByTracker
        {
            readonly SortedListEx<Guid, ByStart> _entries = new SortedListEx<Guid, ByStart>( );
        }
        public class ByStart
        {
            readonly SortedWeakReferenceList<DateTime, ViewTrackerLinkEntity> _entries = new SortedWeakReferenceList<DateTime, ViewTrackerLinkEntity>( );

            public ByStart( )
            {
            }

            public void Add( ViewTrackerLinkEntity entity )
            {
                if( _entries.TryGetValue(entity.Start, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Start, new WeakReference<ViewTrackerLinkEntity>( entity, false ) );
                }
            }

            public bool GetByStart( DateTime start, out ViewTrackerLinkEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( start, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( start );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<ViewTrackerLinkEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<ViewTrackerLinkEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<ViewTrackerLinkEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<ViewTrackerLinkEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class ViewTrackerLinkByStartEntityIndex
    {
        public class ByStart
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<ViewTrackerLinkEntity>> _entries = new SortedListEx<Guid, WeakReference<ViewTrackerLinkEntity>>( );
        }
    }

    public class WeatherStationCommandByWeatherStationAndTimestampEntityIndex
    {
        public class ByWeatherStation
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<WeatherStationCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<WeatherStationCommandEntity>>( );
        }
    }

    public class WeatherStationCommandByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<WeatherStationCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<WeatherStationCommandEntity>>( );
        }
    }

    public class WeatherStationCommandByReplyEntityIndex
    {
        public class ByReply
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<WeatherStationCommandEntity>> _entries = new SortedListEx<Guid, WeakReference<WeatherStationCommandEntity>>( );
        }
    }

    public class WeatherStationCommandByReplyIsNullEntityIndex
    {
    }

    public class WeatherStationCommandReplyByWeatherStationAndTimestampEntityIndex
    {
        public class ByWeatherStation
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<WeatherStationCommandReplyEntity>> _entries = new SortedListEx<Guid, WeakReference<WeatherStationCommandReplyEntity>>( );
        }
    }

    public class WeatherStationCommandReplyByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<WeatherStationCommandReplyEntity>> _entries = new SortedListEx<Guid, WeakReference<WeatherStationCommandReplyEntity>>( );
        }
    }

    public class WeatherStationCommandReplyByCommandEntityIndex
    {
        readonly SortedWeakReferenceList<Guid, WeatherStationCommandReplyEntity> _entries = new SortedWeakReferenceList<Guid, WeatherStationCommandReplyEntity>( );

        public WeatherStationCommandReplyByCommandEntityIndex( )
        {
        }

        public void Add( WeatherStationCommandReplyEntity entity )
        {
            if ( entity.CommandId is Guid command )
            {
                if ( _entries.TryGetValue( command, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( command, new WeakReference<WeatherStationCommandReplyEntity>( entity, false ) );
                }
            }
            else
            {
                throw new ArgumentException( "entity.CommandId is null.", nameof( entity ) );
            }
        }

        public bool GetByCommandId( Guid command, out WeatherStationCommandReplyEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( command, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( command );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(Guid key, [DisallowNull] IList<WeatherStationCommandReplyEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(Guid key, [DisallowNull] IList<WeatherStationCommandReplyEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<WeatherStationCommandReplyEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<WeatherStationCommandReplyEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class WeatherStationCommandReplyByCommandIsNullEntityIndex
    {
    }

    public class WeatherStationConfigurationByWeatherStationAndTimestampEntityIndex
    {
        public class ByWeatherStation
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, WeatherStationConfigurationEntity> _entries = new SortedWeakReferenceList<DateTime, WeatherStationConfigurationEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( WeatherStationConfigurationEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<WeatherStationConfigurationEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out WeatherStationConfigurationEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<WeatherStationConfigurationEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<WeatherStationConfigurationEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<WeatherStationConfigurationEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<WeatherStationConfigurationEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class WeatherStationConfigurationByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<WeatherStationConfigurationEntity>> _entries = new SortedListEx<Guid, WeakReference<WeatherStationConfigurationEntity>>( );
        }
    }

    public class ZoneByNameEntityIndex
    {
        readonly SortedWeakReferenceList<string, ZoneEntity> _entries = new SortedWeakReferenceList<string, ZoneEntity>( );

        public ZoneByNameEntityIndex( )
        {
        }

        public void Add( ZoneEntity entity )
        {
            if( _entries.TryGetValue(entity.Name, out var weakReference ) )
            {
                weakReference.SetTarget( entity );
            }
            else
            {
                _entries.Add( entity.Name, new WeakReference<ZoneEntity>( entity, false ) );
            }
        }

        public bool GetByName( string name, out ZoneEntity? entity )
        {
            entity = null;
            if ( _entries.TryGetValue( name, out var weakReference ) )
            {
                if ( weakReference.TryGetTarget( out entity ) == false )
                {
                    _entries.Remove( name );
                }
            }
            return _entries.Count > 0;
        }

        public bool GetFrom(string key, [DisallowNull] IList<ZoneEntity> result )
        {
            return _entries.From( key, result );
        }

        public bool GetUntil(string key, [DisallowNull] IList<ZoneEntity> result )
        {
            return _entries.Until( key, result );
        }

        public bool GetOver(string firstKey, string lastKey, [DisallowNull] IList<ZoneEntity> result )
        {
            return _entries.Over( firstKey, lastKey, result );
        }

        public bool GetAll([DisallowNull] IList<ZoneEntity> result )
        {
            return _entries.All( result );
        }


    }
    public class ZoneExceptionsByZoneAndTimestampEntityIndex
    {
        public class ByZone
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, ZoneExceptionsEntity> _entries = new SortedWeakReferenceList<DateTime, ZoneExceptionsEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( ZoneExceptionsEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<ZoneExceptionsEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out ZoneExceptionsEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<ZoneExceptionsEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<ZoneExceptionsEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<ZoneExceptionsEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<ZoneExceptionsEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class ZoneExceptionsByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<ZoneExceptionsEntity>> _entries = new SortedListEx<Guid, WeakReference<ZoneExceptionsEntity>>( );
        }
    }

    public class ZoneExceptionsVesselLinkByZoneExceptionsAndVesselEntityIndex
    {
        public class ByZoneExceptions
        {
            readonly SortedListEx<Guid, ByVessel> _entries = new SortedListEx<Guid, ByVessel>( );
        }
        public class ByVessel
        {
            readonly SortedWeakReferenceList<Guid, ZoneExceptionsVesselLinkEntity> _entries = new SortedWeakReferenceList<Guid, ZoneExceptionsVesselLinkEntity>( );

            public ByVessel( )
            {
            }

            public void Add( ZoneExceptionsVesselLinkEntity entity )
            {
                if( _entries.TryGetValue(entity.VesselId, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.VesselId, new WeakReference<ZoneExceptionsVesselLinkEntity>( entity, false ) );
                }
            }

            public bool GetByVesselId( Guid vessel, out ZoneExceptionsVesselLinkEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( vessel, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( vessel );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(Guid key, [DisallowNull] IList<ZoneExceptionsVesselLinkEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(Guid key, [DisallowNull] IList<ZoneExceptionsVesselLinkEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(Guid firstKey, Guid lastKey, [DisallowNull] IList<ZoneExceptionsVesselLinkEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<ZoneExceptionsVesselLinkEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class ZoneExceptionsVesselLinkByVesselEntityIndex
    {
        public class ByVessel
        {
            readonly SortedListEx<Guid, ById> _entries = new SortedListEx<Guid, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<ZoneExceptionsVesselLinkEntity>> _entries = new SortedListEx<Guid, WeakReference<ZoneExceptionsVesselLinkEntity>>( );
        }
    }

    public class ZoneTrackAlarmByTrackAndTimestampEntityIndex
    {
        public class ByTrack
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, ZoneTrackAlarmEntity> _entries = new SortedWeakReferenceList<DateTime, ZoneTrackAlarmEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( ZoneTrackAlarmEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<ZoneTrackAlarmEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out ZoneTrackAlarmEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<ZoneTrackAlarmEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<ZoneTrackAlarmEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<ZoneTrackAlarmEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<ZoneTrackAlarmEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class ZoneTrackAlarmByZoneTrackAndTimestampEntityIndex
    {
        public class ByZone
        {
            readonly SortedListEx<Guid, ByTrack> _entries = new SortedListEx<Guid, ByTrack>( );
        }
        public class ByTrack
        {
            readonly SortedListEx<Guid, ByTimestamp> _entries = new SortedListEx<Guid, ByTimestamp>( );
        }
        public class ByTimestamp
        {
            readonly SortedWeakReferenceList<DateTime, ZoneTrackAlarmEntity> _entries = new SortedWeakReferenceList<DateTime, ZoneTrackAlarmEntity>( );

            public ByTimestamp( )
            {
            }

            public void Add( ZoneTrackAlarmEntity entity )
            {
                if( _entries.TryGetValue(entity.Timestamp, out var weakReference ) )
                {
                    weakReference.SetTarget( entity );
                }
                else
                {
                    _entries.Add( entity.Timestamp, new WeakReference<ZoneTrackAlarmEntity>( entity, false ) );
                }
            }

            public bool GetByTimestamp( DateTime timestamp, out ZoneTrackAlarmEntity? entity )
            {
                entity = null;
                if ( _entries.TryGetValue( timestamp, out var weakReference ) )
                {
                    if ( weakReference.TryGetTarget( out entity ) == false )
                    {
                        _entries.Remove( timestamp );
                    }
                }
                return _entries.Count > 0;
            }

            public bool GetFrom(DateTime key, [DisallowNull] IList<ZoneTrackAlarmEntity> result )
            {
                return _entries.From( key, result );
            }

            public bool GetUntil(DateTime key, [DisallowNull] IList<ZoneTrackAlarmEntity> result )
            {
                return _entries.Until( key, result );
            }

            public bool GetOver(DateTime firstKey, DateTime lastKey, [DisallowNull] IList<ZoneTrackAlarmEntity> result )
            {
                return _entries.Over( firstKey, lastKey, result );
            }

            public bool GetAll([DisallowNull] IList<ZoneTrackAlarmEntity> result )
            {
                return _entries.All( result );
            }

        }

    }
    public class ZoneTrackAlarmByTimestampEntityIndex
    {
        public class ByTimestamp
        {
            readonly SortedListEx<DateTime, ById> _entries = new SortedListEx<DateTime, ById>( );
        }
        public class ById
        {
            readonly SortedListEx<Guid, WeakReference<ZoneTrackAlarmEntity>> _entries = new SortedListEx<Guid, WeakReference<ZoneTrackAlarmEntity>>( );
        }
    }

    public class EntityChanges
    {
        readonly AircraftTypeByNameEntityIndex _aircraftTypeByNameEntityIndex = new AircraftTypeByNameEntityIndex( );
        readonly AisDeviceCommandByAisDeviceAndTimestampEntityIndex _aisDeviceCommandByAisDeviceAndTimestampEntityIndex = new AisDeviceCommandByAisDeviceAndTimestampEntityIndex( );
        readonly AisDeviceCommandByTimestampEntityIndex _aisDeviceCommandByTimestampEntityIndex = new AisDeviceCommandByTimestampEntityIndex( );
        readonly AisDeviceCommandByReplyEntityIndex _aisDeviceCommandByReplyEntityIndex = new AisDeviceCommandByReplyEntityIndex( );
        readonly AisDeviceCommandByReplyIsNullEntityIndex _aisDeviceCommandByReplyIsNullEntityIndex = new AisDeviceCommandByReplyIsNullEntityIndex( );
        readonly AisDeviceCommandReplyByAisDeviceAndTimestampEntityIndex _aisDeviceCommandReplyByAisDeviceAndTimestampEntityIndex = new AisDeviceCommandReplyByAisDeviceAndTimestampEntityIndex( );
        readonly AisDeviceCommandReplyByTimestampEntityIndex _aisDeviceCommandReplyByTimestampEntityIndex = new AisDeviceCommandReplyByTimestampEntityIndex( );
        readonly AisDeviceCommandReplyByCommandEntityIndex _aisDeviceCommandReplyByCommandEntityIndex = new AisDeviceCommandReplyByCommandEntityIndex( );
        readonly AisDeviceCommandReplyByCommandIsNullEntityIndex _aisDeviceCommandReplyByCommandIsNullEntityIndex = new AisDeviceCommandReplyByCommandIsNullEntityIndex( );
        readonly AisDeviceConfigurationByAisDeviceAndTimestampEntityIndex _aisDeviceConfigurationByAisDeviceAndTimestampEntityIndex = new AisDeviceConfigurationByAisDeviceAndTimestampEntityIndex( );
        readonly AisDeviceConfigurationByTimestampEntityIndex _aisDeviceConfigurationByTimestampEntityIndex = new AisDeviceConfigurationByTimestampEntityIndex( );
        readonly AisDeviceRawMessageByAisDeviceAndTimestampEntityIndex _aisDeviceRawMessageByAisDeviceAndTimestampEntityIndex = new AisDeviceRawMessageByAisDeviceAndTimestampEntityIndex( );
        readonly AisDeviceRawMessageByTimestampEntityIndex _aisDeviceRawMessageByTimestampEntityIndex = new AisDeviceRawMessageByTimestampEntityIndex( );
        readonly AisDeviceRawSentenceByAisDeviceAndTimestampEntityIndex _aisDeviceRawSentenceByAisDeviceAndTimestampEntityIndex = new AisDeviceRawSentenceByAisDeviceAndTimestampEntityIndex( );
        readonly AisDeviceRawSentenceByTimestampEntityIndex _aisDeviceRawSentenceByTimestampEntityIndex = new AisDeviceRawSentenceByTimestampEntityIndex( );
        readonly AisMessageByAisDeviceAndReceivedTimestampEntityIndex _aisMessageByAisDeviceAndReceivedTimestampEntityIndex = new AisMessageByAisDeviceAndReceivedTimestampEntityIndex( );
        readonly AisMessageByReceivedTimestampEntityIndex _aisMessageByReceivedTimestampEntityIndex = new AisMessageByReceivedTimestampEntityIndex( );
        readonly AisMessageByMmsiAndMessageSequenceNumberEntityIndex _aisMessageByMmsiAndMessageSequenceNumberEntityIndex = new AisMessageByMmsiAndMessageSequenceNumberEntityIndex( );
        readonly AisMessageByMmsiIsNullAndMessageSequenceNumberEntityIndex _aisMessageByMmsiIsNullAndMessageSequenceNumberEntityIndex = new AisMessageByMmsiIsNullAndMessageSequenceNumberEntityIndex( );
        readonly AisAddressedSafetyRelatedMessageByDestinationMmsiEntityIndex _aisAddressedSafetyRelatedMessageByDestinationMmsiEntityIndex = new AisAddressedSafetyRelatedMessageByDestinationMmsiEntityIndex( );
        readonly AisAddressedSafetyRelatedMessageByDestinationMmsiIsNullEntityIndex _aisAddressedSafetyRelatedMessageByDestinationMmsiIsNullEntityIndex = new AisAddressedSafetyRelatedMessageByDestinationMmsiIsNullEntityIndex( );
        readonly AisBinaryAddressedMessageByDestinationMmsiEntityIndex _aisBinaryAddressedMessageByDestinationMmsiEntityIndex = new AisBinaryAddressedMessageByDestinationMmsiEntityIndex( );
        readonly AisBinaryAddressedMessageByDestinationMmsiIsNullEntityIndex _aisBinaryAddressedMessageByDestinationMmsiIsNullEntityIndex = new AisBinaryAddressedMessageByDestinationMmsiIsNullEntityIndex( );
        readonly AisExtendedClassBCsPositionReportMessageByNameEntityIndex _aisExtendedClassBCsPositionReportMessageByNameEntityIndex = new AisExtendedClassBCsPositionReportMessageByNameEntityIndex( );
        readonly AisExtendedClassBCsPositionReportMessageByNameIsNullEntityIndex _aisExtendedClassBCsPositionReportMessageByNameIsNullEntityIndex = new AisExtendedClassBCsPositionReportMessageByNameIsNullEntityIndex( );
        readonly AisStaticAndVoyageRelatedDataMessageByImoNumberEntityIndex _aisStaticAndVoyageRelatedDataMessageByImoNumberEntityIndex = new AisStaticAndVoyageRelatedDataMessageByImoNumberEntityIndex( );
        readonly AisStaticAndVoyageRelatedDataMessageByImoNumberIsNullEntityIndex _aisStaticAndVoyageRelatedDataMessageByImoNumberIsNullEntityIndex = new AisStaticAndVoyageRelatedDataMessageByImoNumberIsNullEntityIndex( );
        readonly AisStaticAndVoyageRelatedDataMessageByCallsignEntityIndex _aisStaticAndVoyageRelatedDataMessageByCallsignEntityIndex = new AisStaticAndVoyageRelatedDataMessageByCallsignEntityIndex( );
        readonly AisStaticAndVoyageRelatedDataMessageByCallsignIsNullEntityIndex _aisStaticAndVoyageRelatedDataMessageByCallsignIsNullEntityIndex = new AisStaticAndVoyageRelatedDataMessageByCallsignIsNullEntityIndex( );
        readonly AisStaticAndVoyageRelatedDataMessageByShipNameEntityIndex _aisStaticAndVoyageRelatedDataMessageByShipNameEntityIndex = new AisStaticAndVoyageRelatedDataMessageByShipNameEntityIndex( );
        readonly AisStaticAndVoyageRelatedDataMessageByShipNameIsNullEntityIndex _aisStaticAndVoyageRelatedDataMessageByShipNameIsNullEntityIndex = new AisStaticAndVoyageRelatedDataMessageByShipNameIsNullEntityIndex( );
        readonly AisStaticDataReportPartAMessageByShipNameEntityIndex _aisStaticDataReportPartAMessageByShipNameEntityIndex = new AisStaticDataReportPartAMessageByShipNameEntityIndex( );
        readonly AisStaticDataReportPartAMessageByShipNameIsNullEntityIndex _aisStaticDataReportPartAMessageByShipNameIsNullEntityIndex = new AisStaticDataReportPartAMessageByShipNameIsNullEntityIndex( );
        readonly AisStaticDataReportPartBMessageByCallsignEntityIndex _aisStaticDataReportPartBMessageByCallsignEntityIndex = new AisStaticDataReportPartBMessageByCallsignEntityIndex( );
        readonly AisStaticDataReportPartBMessageByCallsignIsNullEntityIndex _aisStaticDataReportPartBMessageByCallsignIsNullEntityIndex = new AisStaticDataReportPartBMessageByCallsignIsNullEntityIndex( );
        readonly AisStaticDataReportPartBMessageByMothershipMmsiEntityIndex _aisStaticDataReportPartBMessageByMothershipMmsiEntityIndex = new AisStaticDataReportPartBMessageByMothershipMmsiEntityIndex( );
        readonly AisStaticDataReportPartBMessageByMothershipMmsiIsNullEntityIndex _aisStaticDataReportPartBMessageByMothershipMmsiIsNullEntityIndex = new AisStaticDataReportPartBMessageByMothershipMmsiIsNullEntityIndex( );
        readonly AlarmStateChangeByAlarmAndTimestampEntityIndex _alarmStateChangeByAlarmAndTimestampEntityIndex = new AlarmStateChangeByAlarmAndTimestampEntityIndex( );
        readonly AlarmStateChangeByTimestampEntityIndex _alarmStateChangeByTimestampEntityIndex = new AlarmStateChangeByTimestampEntityIndex( );
        readonly BaseStationTypeByNameEntityIndex _baseStationTypeByNameEntityIndex = new BaseStationTypeByNameEntityIndex( );
        readonly BinaryTimeseriesValueByTimeseriesAndTimestampEntityIndex _binaryTimeseriesValueByTimeseriesAndTimestampEntityIndex = new BinaryTimeseriesValueByTimeseriesAndTimestampEntityIndex( );
        readonly BinaryTimeseriesValueByTimestampEntityIndex _binaryTimeseriesValueByTimestampEntityIndex = new BinaryTimeseriesValueByTimestampEntityIndex( );
        readonly BookmarkByViewEntityIndex _bookmarkByViewEntityIndex = new BookmarkByViewEntityIndex( );
        readonly BooleanTimeseriesValueByTimeseriesAndTimestampEntityIndex _booleanTimeseriesValueByTimeseriesAndTimestampEntityIndex = new BooleanTimeseriesValueByTimeseriesAndTimestampEntityIndex( );
        readonly BooleanTimeseriesValueByTimestampEntityIndex _booleanTimeseriesValueByTimestampEntityIndex = new BooleanTimeseriesValueByTimestampEntityIndex( );
        readonly ByteTimeseriesValueByTimeseriesAndTimestampEntityIndex _byteTimeseriesValueByTimeseriesAndTimestampEntityIndex = new ByteTimeseriesValueByTimeseriesAndTimestampEntityIndex( );
        readonly ByteTimeseriesValueByTimestampEntityIndex _byteTimeseriesValueByTimestampEntityIndex = new ByteTimeseriesValueByTimestampEntityIndex( );
        readonly CameraCommandByCameraAndTimestampEntityIndex _cameraCommandByCameraAndTimestampEntityIndex = new CameraCommandByCameraAndTimestampEntityIndex( );
        readonly CameraCommandByTimestampEntityIndex _cameraCommandByTimestampEntityIndex = new CameraCommandByTimestampEntityIndex( );
        readonly CameraCommandByReplyEntityIndex _cameraCommandByReplyEntityIndex = new CameraCommandByReplyEntityIndex( );
        readonly CameraCommandByReplyIsNullEntityIndex _cameraCommandByReplyIsNullEntityIndex = new CameraCommandByReplyIsNullEntityIndex( );
        readonly CameraCommandReplyByCameraAndTimestampEntityIndex _cameraCommandReplyByCameraAndTimestampEntityIndex = new CameraCommandReplyByCameraAndTimestampEntityIndex( );
        readonly CameraCommandReplyByTimestampEntityIndex _cameraCommandReplyByTimestampEntityIndex = new CameraCommandReplyByTimestampEntityIndex( );
        readonly CameraCommandReplyByCommandEntityIndex _cameraCommandReplyByCommandEntityIndex = new CameraCommandReplyByCommandEntityIndex( );
        readonly CameraCommandReplyByCommandIsNullEntityIndex _cameraCommandReplyByCommandIsNullEntityIndex = new CameraCommandReplyByCommandIsNullEntityIndex( );
        readonly CameraConfigurationByCameraAndTimestampEntityIndex _cameraConfigurationByCameraAndTimestampEntityIndex = new CameraConfigurationByCameraAndTimestampEntityIndex( );
        readonly CameraConfigurationByTimestampEntityIndex _cameraConfigurationByTimestampEntityIndex = new CameraConfigurationByTimestampEntityIndex( );
        readonly CameraPanCalibrationByCameraAndTimestampEntityIndex _cameraPanCalibrationByCameraAndTimestampEntityIndex = new CameraPanCalibrationByCameraAndTimestampEntityIndex( );
        readonly CameraPanCalibrationByTimestampEntityIndex _cameraPanCalibrationByTimestampEntityIndex = new CameraPanCalibrationByTimestampEntityIndex( );
        readonly CameraPanCalibrationValueByPanCalibrationAndPanAngleEntityIndex _cameraPanCalibrationValueByPanCalibrationAndPanAngleEntityIndex = new CameraPanCalibrationValueByPanCalibrationAndPanAngleEntityIndex( );
        readonly CameraStatusByCameraAndTimestampEntityIndex _cameraStatusByCameraAndTimestampEntityIndex = new CameraStatusByCameraAndTimestampEntityIndex( );
        readonly CameraStatusByTrackAndTimestampEntityIndex _cameraStatusByTrackAndTimestampEntityIndex = new CameraStatusByTrackAndTimestampEntityIndex( );
        readonly CameraStatusByTrackIsNullAndTimestampEntityIndex _cameraStatusByTrackIsNullAndTimestampEntityIndex = new CameraStatusByTrackIsNullAndTimestampEntityIndex( );
        readonly CameraStatusByTimestampEntityIndex _cameraStatusByTimestampEntityIndex = new CameraStatusByTimestampEntityIndex( );
        readonly CameraTiltCalibrationByCameraAndTimestampEntityIndex _cameraTiltCalibrationByCameraAndTimestampEntityIndex = new CameraTiltCalibrationByCameraAndTimestampEntityIndex( );
        readonly CameraTiltCalibrationByTimestampEntityIndex _cameraTiltCalibrationByTimestampEntityIndex = new CameraTiltCalibrationByTimestampEntityIndex( );
        readonly CameraTiltCalibrationValueByTiltCalibrationAndPanAngleEntityIndex _cameraTiltCalibrationValueByTiltCalibrationAndPanAngleEntityIndex = new CameraTiltCalibrationValueByTiltCalibrationAndPanAngleEntityIndex( );
        readonly CameraZoomCalibrationByCameraAndTimestampEntityIndex _cameraZoomCalibrationByCameraAndTimestampEntityIndex = new CameraZoomCalibrationByCameraAndTimestampEntityIndex( );
        readonly CameraZoomCalibrationByTimestampEntityIndex _cameraZoomCalibrationByTimestampEntityIndex = new CameraZoomCalibrationByTimestampEntityIndex( );
        readonly CameraZoomCalibrationValueByZoomCalibrationAndFocalLengthEntityIndex _cameraZoomCalibrationValueByZoomCalibrationAndFocalLengthEntityIndex = new CameraZoomCalibrationValueByZoomCalibrationAndFocalLengthEntityIndex( );
        readonly CatalogElementByCatalogAndNameEntityIndex _catalogElementByCatalogAndNameEntityIndex = new CatalogElementByCatalogAndNameEntityIndex( );
        readonly CatalogElementByCatalogIsNullAndNameEntityIndex _catalogElementByCatalogIsNullAndNameEntityIndex = new CatalogElementByCatalogIsNullAndNameEntityIndex( );
        readonly ElementByElementTypeEntityIndex _elementByElementTypeEntityIndex = new ElementByElementTypeEntityIndex( );
        readonly ElementByElementTypeIsNullEntityIndex _elementByElementTypeIsNullEntityIndex = new ElementByElementTypeIsNullEntityIndex( );
        readonly CountryByNameEntityIndex _countryByNameEntityIndex = new CountryByNameEntityIndex( );
        readonly CountryByCodeEntityIndex _countryByCodeEntityIndex = new CountryByCodeEntityIndex( );
        readonly CountryByAlpha2EntityIndex _countryByAlpha2EntityIndex = new CountryByAlpha2EntityIndex( );
        readonly CountryByAlpha3EntityIndex _countryByAlpha3EntityIndex = new CountryByAlpha3EntityIndex( );
        readonly DateTimeTimeseriesValueByTimeseriesAndTimestampEntityIndex _dateTimeTimeseriesValueByTimeseriesAndTimestampEntityIndex = new DateTimeTimeseriesValueByTimeseriesAndTimestampEntityIndex( );
        readonly DateTimeTimeseriesValueByTimestampEntityIndex _dateTimeTimeseriesValueByTimestampEntityIndex = new DateTimeTimeseriesValueByTimestampEntityIndex( );
        readonly DeviceHostByNameEntityIndex _deviceHostByNameEntityIndex = new DeviceHostByNameEntityIndex( );
        readonly DeviceHostConfigurationByHostAndTimestampEntityIndex _deviceHostConfigurationByHostAndTimestampEntityIndex = new DeviceHostConfigurationByHostAndTimestampEntityIndex( );
        readonly DeviceHostConfigurationByTimestampEntityIndex _deviceHostConfigurationByTimestampEntityIndex = new DeviceHostConfigurationByTimestampEntityIndex( );
        readonly DoubleTimeseriesValueByTimeseriesAndTimestampEntityIndex _doubleTimeseriesValueByTimeseriesAndTimestampEntityIndex = new DoubleTimeseriesValueByTimeseriesAndTimestampEntityIndex( );
        readonly DoubleTimeseriesValueByTimestampEntityIndex _doubleTimeseriesValueByTimestampEntityIndex = new DoubleTimeseriesValueByTimestampEntityIndex( );
        readonly FacilityTypeByNameEntityIndex _facilityTypeByNameEntityIndex = new FacilityTypeByNameEntityIndex( );
        readonly GeoPosition2DTimeseriesValueByTimeseriesAndTimestampEntityIndex _geoPosition2DTimeseriesValueByTimeseriesAndTimestampEntityIndex = new GeoPosition2DTimeseriesValueByTimeseriesAndTimestampEntityIndex( );
        readonly GeoPosition2DTimeseriesValueByTimestampEntityIndex _geoPosition2DTimeseriesValueByTimestampEntityIndex = new GeoPosition2DTimeseriesValueByTimestampEntityIndex( );
        readonly GeoPosition3DTimeseriesValueByTimeseriesAndTimestampEntityIndex _geoPosition3DTimeseriesValueByTimeseriesAndTimestampEntityIndex = new GeoPosition3DTimeseriesValueByTimeseriesAndTimestampEntityIndex( );
        readonly GeoPosition3DTimeseriesValueByTimestampEntityIndex _geoPosition3DTimeseriesValueByTimestampEntityIndex = new GeoPosition3DTimeseriesValueByTimestampEntityIndex( );
        readonly GNSSDeviceCommandByGNSSDeviceAndTimestampEntityIndex _gNSSDeviceCommandByGNSSDeviceAndTimestampEntityIndex = new GNSSDeviceCommandByGNSSDeviceAndTimestampEntityIndex( );
        readonly GNSSDeviceCommandByTimestampEntityIndex _gNSSDeviceCommandByTimestampEntityIndex = new GNSSDeviceCommandByTimestampEntityIndex( );
        readonly GNSSDeviceCommandByReplyEntityIndex _gNSSDeviceCommandByReplyEntityIndex = new GNSSDeviceCommandByReplyEntityIndex( );
        readonly GNSSDeviceCommandByReplyIsNullEntityIndex _gNSSDeviceCommandByReplyIsNullEntityIndex = new GNSSDeviceCommandByReplyIsNullEntityIndex( );
        readonly GNSSDeviceCommandReplyByGNSSDeviceAndTimestampEntityIndex _gNSSDeviceCommandReplyByGNSSDeviceAndTimestampEntityIndex = new GNSSDeviceCommandReplyByGNSSDeviceAndTimestampEntityIndex( );
        readonly GNSSDeviceCommandReplyByTimestampEntityIndex _gNSSDeviceCommandReplyByTimestampEntityIndex = new GNSSDeviceCommandReplyByTimestampEntityIndex( );
        readonly GNSSDeviceCommandReplyByCommandEntityIndex _gNSSDeviceCommandReplyByCommandEntityIndex = new GNSSDeviceCommandReplyByCommandEntityIndex( );
        readonly GNSSDeviceCommandReplyByCommandIsNullEntityIndex _gNSSDeviceCommandReplyByCommandIsNullEntityIndex = new GNSSDeviceCommandReplyByCommandIsNullEntityIndex( );
        readonly GNSSDeviceConfigurationByGNSSDeviceAndTimestampEntityIndex _gNSSDeviceConfigurationByGNSSDeviceAndTimestampEntityIndex = new GNSSDeviceConfigurationByGNSSDeviceAndTimestampEntityIndex( );
        readonly GNSSDeviceConfigurationByTimestampEntityIndex _gNSSDeviceConfigurationByTimestampEntityIndex = new GNSSDeviceConfigurationByTimestampEntityIndex( );
        readonly GuidTimeseriesValueByTimeseriesAndTimestampEntityIndex _guidTimeseriesValueByTimeseriesAndTimestampEntityIndex = new GuidTimeseriesValueByTimeseriesAndTimestampEntityIndex( );
        readonly GuidTimeseriesValueByTimestampEntityIndex _guidTimeseriesValueByTimestampEntityIndex = new GuidTimeseriesValueByTimestampEntityIndex( );
        readonly GyroDeviceCommandByGyroDeviceAndTimestampEntityIndex _gyroDeviceCommandByGyroDeviceAndTimestampEntityIndex = new GyroDeviceCommandByGyroDeviceAndTimestampEntityIndex( );
        readonly GyroDeviceCommandByTimestampEntityIndex _gyroDeviceCommandByTimestampEntityIndex = new GyroDeviceCommandByTimestampEntityIndex( );
        readonly GyroDeviceCommandByReplyEntityIndex _gyroDeviceCommandByReplyEntityIndex = new GyroDeviceCommandByReplyEntityIndex( );
        readonly GyroDeviceCommandByReplyIsNullEntityIndex _gyroDeviceCommandByReplyIsNullEntityIndex = new GyroDeviceCommandByReplyIsNullEntityIndex( );
        readonly GyroDeviceCommandReplyByGyroDeviceAndTimestampEntityIndex _gyroDeviceCommandReplyByGyroDeviceAndTimestampEntityIndex = new GyroDeviceCommandReplyByGyroDeviceAndTimestampEntityIndex( );
        readonly GyroDeviceCommandReplyByTimestampEntityIndex _gyroDeviceCommandReplyByTimestampEntityIndex = new GyroDeviceCommandReplyByTimestampEntityIndex( );
        readonly GyroDeviceCommandReplyByCommandEntityIndex _gyroDeviceCommandReplyByCommandEntityIndex = new GyroDeviceCommandReplyByCommandEntityIndex( );
        readonly GyroDeviceCommandReplyByCommandIsNullEntityIndex _gyroDeviceCommandReplyByCommandIsNullEntityIndex = new GyroDeviceCommandReplyByCommandIsNullEntityIndex( );
        readonly GyroDeviceConfigurationByGyroDeviceAndTimestampEntityIndex _gyroDeviceConfigurationByGyroDeviceAndTimestampEntityIndex = new GyroDeviceConfigurationByGyroDeviceAndTimestampEntityIndex( );
        readonly GyroDeviceConfigurationByTimestampEntityIndex _gyroDeviceConfigurationByTimestampEntityIndex = new GyroDeviceConfigurationByTimestampEntityIndex( );
        readonly CallsignByIdentifierEntityIndex _callsignByIdentifierEntityIndex = new CallsignByIdentifierEntityIndex( );
        readonly InternationalMaritimeOrganizationNumberByIdentifierEntityIndex _internationalMaritimeOrganizationNumberByIdentifierEntityIndex = new InternationalMaritimeOrganizationNumberByIdentifierEntityIndex( );
        readonly MaritimeMobileServiceIdentityByIdentifierEntityIndex _maritimeMobileServiceIdentityByIdentifierEntityIndex = new MaritimeMobileServiceIdentityByIdentifierEntityIndex( );
        readonly NameByTextEntityIndex _nameByTextEntityIndex = new NameByTextEntityIndex( );
        readonly Int16TimeseriesValueByTimeseriesAndTimestampEntityIndex _int16TimeseriesValueByTimeseriesAndTimestampEntityIndex = new Int16TimeseriesValueByTimeseriesAndTimestampEntityIndex( );
        readonly Int16TimeseriesValueByTimestampEntityIndex _int16TimeseriesValueByTimestampEntityIndex = new Int16TimeseriesValueByTimestampEntityIndex( );
        readonly Int32TimeseriesValueByTimeseriesAndTimestampEntityIndex _int32TimeseriesValueByTimeseriesAndTimestampEntityIndex = new Int32TimeseriesValueByTimeseriesAndTimestampEntityIndex( );
        readonly Int32TimeseriesValueByTimestampEntityIndex _int32TimeseriesValueByTimestampEntityIndex = new Int32TimeseriesValueByTimestampEntityIndex( );
        readonly Int64TimeseriesValueByTimeseriesAndTimestampEntityIndex _int64TimeseriesValueByTimeseriesAndTimestampEntityIndex = new Int64TimeseriesValueByTimeseriesAndTimestampEntityIndex( );
        readonly Int64TimeseriesValueByTimestampEntityIndex _int64TimeseriesValueByTimestampEntityIndex = new Int64TimeseriesValueByTimestampEntityIndex( );
        readonly BaseStationByNameEntityIndex _baseStationByNameEntityIndex = new BaseStationByNameEntityIndex( );
        readonly BaseStationByTypeEntityIndex _baseStationByTypeEntityIndex = new BaseStationByTypeEntityIndex( );
        readonly BaseStationByTypeIsNullEntityIndex _baseStationByTypeIsNullEntityIndex = new BaseStationByTypeIsNullEntityIndex( );
        readonly DeviceByHostEntityIndex _deviceByHostEntityIndex = new DeviceByHostEntityIndex( );
        readonly DeviceByNameEntityIndex _deviceByNameEntityIndex = new DeviceByNameEntityIndex( );
        readonly GyroDeviceByGNSSDeviceEntityIndex _gyroDeviceByGNSSDeviceEntityIndex = new GyroDeviceByGNSSDeviceEntityIndex( );
        readonly GyroDeviceByGNSSDeviceIsNullEntityIndex _gyroDeviceByGNSSDeviceIsNullEntityIndex = new GyroDeviceByGNSSDeviceIsNullEntityIndex( );
        readonly RadomeDeviceByRadarEntityIndex _radomeDeviceByRadarEntityIndex = new RadomeDeviceByRadarEntityIndex( );
        readonly RadomeDeviceByRadarIsNullEntityIndex _radomeDeviceByRadarIsNullEntityIndex = new RadomeDeviceByRadarIsNullEntityIndex( );
        readonly RadarDeviceByRadomeEntityIndex _radarDeviceByRadomeEntityIndex = new RadarDeviceByRadomeEntityIndex( );
        readonly RadarDeviceByRadomeIsNullEntityIndex _radarDeviceByRadomeIsNullEntityIndex = new RadarDeviceByRadomeIsNullEntityIndex( );
        readonly RadarDeviceByGNSSDeviceEntityIndex _radarDeviceByGNSSDeviceEntityIndex = new RadarDeviceByGNSSDeviceEntityIndex( );
        readonly RadarDeviceByGNSSDeviceIsNullEntityIndex _radarDeviceByGNSSDeviceIsNullEntityIndex = new RadarDeviceByGNSSDeviceIsNullEntityIndex( );
        readonly WeatherStationDeviceByGyroEntityIndex _weatherStationDeviceByGyroEntityIndex = new WeatherStationDeviceByGyroEntityIndex( );
        readonly WeatherStationDeviceByGyroIsNullEntityIndex _weatherStationDeviceByGyroIsNullEntityIndex = new WeatherStationDeviceByGyroIsNullEntityIndex( );
        readonly FacilityByNameEntityIndex _facilityByNameEntityIndex = new FacilityByNameEntityIndex( );
        readonly FacilityByTypeEntityIndex _facilityByTypeEntityIndex = new FacilityByTypeEntityIndex( );
        readonly FacilityByTypeIsNullEntityIndex _facilityByTypeIsNullEntityIndex = new FacilityByTypeIsNullEntityIndex( );
        readonly AircraftByNameEntityIndex _aircraftByNameEntityIndex = new AircraftByNameEntityIndex( );
        readonly AircraftByTypeEntityIndex _aircraftByTypeEntityIndex = new AircraftByTypeEntityIndex( );
        readonly AircraftByTypeIsNullEntityIndex _aircraftByTypeIsNullEntityIndex = new AircraftByTypeIsNullEntityIndex( );
        readonly AisAidToNavigationByNameEntityIndex _aisAidToNavigationByNameEntityIndex = new AisAidToNavigationByNameEntityIndex( );
        readonly AisAidToNavigationByMMSIEntityIndex _aisAidToNavigationByMMSIEntityIndex = new AisAidToNavigationByMMSIEntityIndex( );
        readonly AisAidToNavigationByMMSIIsNullEntityIndex _aisAidToNavigationByMMSIIsNullEntityIndex = new AisAidToNavigationByMMSIIsNullEntityIndex( );
        readonly VehicleByNameEntityIndex _vehicleByNameEntityIndex = new VehicleByNameEntityIndex( );
        readonly VehicleByTypeEntityIndex _vehicleByTypeEntityIndex = new VehicleByTypeEntityIndex( );
        readonly VehicleByTypeIsNullEntityIndex _vehicleByTypeIsNullEntityIndex = new VehicleByTypeIsNullEntityIndex( );
        readonly VesselByNameEntityIndex _vesselByNameEntityIndex = new VesselByNameEntityIndex( );
        readonly VesselByTypeEntityIndex _vesselByTypeEntityIndex = new VesselByTypeEntityIndex( );
        readonly VesselByTypeIsNullEntityIndex _vesselByTypeIsNullEntityIndex = new VesselByTypeIsNullEntityIndex( );
        readonly ItemIdentityLinkByItemAndStartEntityIndex _itemIdentityLinkByItemAndStartEntityIndex = new ItemIdentityLinkByItemAndStartEntityIndex( );
        readonly ItemIdentityLinkByItemAndEndEntityIndex _itemIdentityLinkByItemAndEndEntityIndex = new ItemIdentityLinkByItemAndEndEntityIndex( );
        readonly ItemIdentityLinkByItemAndEndIsNullEntityIndex _itemIdentityLinkByItemAndEndIsNullEntityIndex = new ItemIdentityLinkByItemAndEndIsNullEntityIndex( );
        readonly ItemIdentityLinkByIdentityAndStartEntityIndex _itemIdentityLinkByIdentityAndStartEntityIndex = new ItemIdentityLinkByIdentityAndStartEntityIndex( );
        readonly ItemIdentityLinkByIdentityAndEndEntityIndex _itemIdentityLinkByIdentityAndEndEntityIndex = new ItemIdentityLinkByIdentityAndEndEntityIndex( );
        readonly ItemIdentityLinkByIdentityAndEndIsNullEntityIndex _itemIdentityLinkByIdentityAndEndIsNullEntityIndex = new ItemIdentityLinkByIdentityAndEndIsNullEntityIndex( );
        readonly ItemIdentityLinkByStartEntityIndex _itemIdentityLinkByStartEntityIndex = new ItemIdentityLinkByStartEntityIndex( );
        readonly ItemIdentityLinkByEndEntityIndex _itemIdentityLinkByEndEntityIndex = new ItemIdentityLinkByEndEntityIndex( );
        readonly ItemIdentityLinkByEndIsNullEntityIndex _itemIdentityLinkByEndIsNullEntityIndex = new ItemIdentityLinkByEndIsNullEntityIndex( );
        readonly ItemParentChildLinkByParentAndTimestampEntityIndex _itemParentChildLinkByParentAndTimestampEntityIndex = new ItemParentChildLinkByParentAndTimestampEntityIndex( );
        readonly ItemParentChildLinkByChildAndTimestampEntityIndex _itemParentChildLinkByChildAndTimestampEntityIndex = new ItemParentChildLinkByChildAndTimestampEntityIndex( );
        readonly ItemParentChildLinkByTimestampEntityIndex _itemParentChildLinkByTimestampEntityIndex = new ItemParentChildLinkByTimestampEntityIndex( );
        readonly LineInputDeviceCommandByLineInputDeviceAndTimestampEntityIndex _lineInputDeviceCommandByLineInputDeviceAndTimestampEntityIndex = new LineInputDeviceCommandByLineInputDeviceAndTimestampEntityIndex( );
        readonly LineInputDeviceCommandByTimestampEntityIndex _lineInputDeviceCommandByTimestampEntityIndex = new LineInputDeviceCommandByTimestampEntityIndex( );
        readonly LineInputDeviceCommandByReplyEntityIndex _lineInputDeviceCommandByReplyEntityIndex = new LineInputDeviceCommandByReplyEntityIndex( );
        readonly LineInputDeviceCommandByReplyIsNullEntityIndex _lineInputDeviceCommandByReplyIsNullEntityIndex = new LineInputDeviceCommandByReplyIsNullEntityIndex( );
        readonly LineInputDeviceCommandReplyByLineInputDeviceAndTimestampEntityIndex _lineInputDeviceCommandReplyByLineInputDeviceAndTimestampEntityIndex = new LineInputDeviceCommandReplyByLineInputDeviceAndTimestampEntityIndex( );
        readonly LineInputDeviceCommandReplyByTimestampEntityIndex _lineInputDeviceCommandReplyByTimestampEntityIndex = new LineInputDeviceCommandReplyByTimestampEntityIndex( );
        readonly LineInputDeviceCommandReplyByCommandEntityIndex _lineInputDeviceCommandReplyByCommandEntityIndex = new LineInputDeviceCommandReplyByCommandEntityIndex( );
        readonly LineInputDeviceCommandReplyByCommandIsNullEntityIndex _lineInputDeviceCommandReplyByCommandIsNullEntityIndex = new LineInputDeviceCommandReplyByCommandIsNullEntityIndex( );
        readonly LineInputDeviceConfigurationByLineInputDeviceAndTimestampEntityIndex _lineInputDeviceConfigurationByLineInputDeviceAndTimestampEntityIndex = new LineInputDeviceConfigurationByLineInputDeviceAndTimestampEntityIndex( );
        readonly LineInputDeviceConfigurationByTimestampEntityIndex _lineInputDeviceConfigurationByTimestampEntityIndex = new LineInputDeviceConfigurationByTimestampEntityIndex( );
        readonly LineInputMessageRoutingByLineInputDeviceAndTypeEntityIndex _lineInputMessageRoutingByLineInputDeviceAndTypeEntityIndex = new LineInputMessageRoutingByLineInputDeviceAndTypeEntityIndex( );
        readonly LineInputMessageRoutingDestinationByRoutingAndListenerEntityIndex _lineInputMessageRoutingDestinationByRoutingAndListenerEntityIndex = new LineInputMessageRoutingDestinationByRoutingAndListenerEntityIndex( );
        readonly LineInputMessageRoutingDestinationByRoutingAndListenerIsNullEntityIndex _lineInputMessageRoutingDestinationByRoutingAndListenerIsNullEntityIndex = new LineInputMessageRoutingDestinationByRoutingAndListenerIsNullEntityIndex( );
        readonly LineInputMessageRoutingDestinationByListenerEntityIndex _lineInputMessageRoutingDestinationByListenerEntityIndex = new LineInputMessageRoutingDestinationByListenerEntityIndex( );
        readonly LineInputMessageRoutingDestinationByListenerIsNullEntityIndex _lineInputMessageRoutingDestinationByListenerIsNullEntityIndex = new LineInputMessageRoutingDestinationByListenerIsNullEntityIndex( );
        readonly LineInputWhiteListEntryByLineInputDeviceHostNameAndPortEntityIndex _lineInputWhiteListEntryByLineInputDeviceHostNameAndPortEntityIndex = new LineInputWhiteListEntryByLineInputDeviceHostNameAndPortEntityIndex( );
        readonly LogApplicationByNameEntityIndex _logApplicationByNameEntityIndex = new LogApplicationByNameEntityIndex( );
        readonly LogApplicationConfigurationByApplicationAndTimestampEntityIndex _logApplicationConfigurationByApplicationAndTimestampEntityIndex = new LogApplicationConfigurationByApplicationAndTimestampEntityIndex( );
        readonly LogApplicationConfigurationByTimestampEntityIndex _logApplicationConfigurationByTimestampEntityIndex = new LogApplicationConfigurationByTimestampEntityIndex( );
        readonly LogHostByComputerNameEntityIndex _logHostByComputerNameEntityIndex = new LogHostByComputerNameEntityIndex( );
        readonly LogHostConfigurationByHostAndTimestampEntityIndex _logHostConfigurationByHostAndTimestampEntityIndex = new LogHostConfigurationByHostAndTimestampEntityIndex( );
        readonly LogHostConfigurationByTimestampEntityIndex _logHostConfigurationByTimestampEntityIndex = new LogHostConfigurationByTimestampEntityIndex( );
        readonly LogLocationByFileNameAndLineNumberEntityIndex _logLocationByFileNameAndLineNumberEntityIndex = new LogLocationByFileNameAndLineNumberEntityIndex( );
        readonly LogProcessByApplicationAndStartedEntityIndex _logProcessByApplicationAndStartedEntityIndex = new LogProcessByApplicationAndStartedEntityIndex( );
        readonly LogProcessByHostAndStartedEntityIndex _logProcessByHostAndStartedEntityIndex = new LogProcessByHostAndStartedEntityIndex( );
        readonly LogProcessByHostIsNullAndStartedEntityIndex _logProcessByHostIsNullAndStartedEntityIndex = new LogProcessByHostIsNullAndStartedEntityIndex( );
        readonly LogProcessByStartedEntityIndex _logProcessByStartedEntityIndex = new LogProcessByStartedEntityIndex( );
        readonly LogRecordByThreadAndTimestampEntityIndex _logRecordByThreadAndTimestampEntityIndex = new LogRecordByThreadAndTimestampEntityIndex( );
        readonly LogRecordByTimestampEntityIndex _logRecordByTimestampEntityIndex = new LogRecordByTimestampEntityIndex( );
        readonly LogRecordByLocationEntityIndex _logRecordByLocationEntityIndex = new LogRecordByLocationEntityIndex( );
        readonly LogThreadByProcessAndStartedEntityIndex _logThreadByProcessAndStartedEntityIndex = new LogThreadByProcessAndStartedEntityIndex( );
        readonly LogThreadByStartedEntityIndex _logThreadByStartedEntityIndex = new LogThreadByStartedEntityIndex( );
        readonly LogTraceEntryByThreadAndEnteredEntityIndex _logTraceEntryByThreadAndEnteredEntityIndex = new LogTraceEntryByThreadAndEnteredEntityIndex( );
        readonly LogTraceEntryByLocationAndEnteredEntityIndex _logTraceEntryByLocationAndEnteredEntityIndex = new LogTraceEntryByLocationAndEnteredEntityIndex( );
        readonly LogTraceEntryByEnteredEntityIndex _logTraceEntryByEnteredEntityIndex = new LogTraceEntryByEnteredEntityIndex( );
        readonly MapElementByItemEntityIndex _mapElementByItemEntityIndex = new MapElementByItemEntityIndex( );
        readonly MapServiceOptionsByTimestampEntityIndex _mapServiceOptionsByTimestampEntityIndex = new MapServiceOptionsByTimestampEntityIndex( );
        readonly MaritimeIdentificationDigitsByCodeEntityIndex _maritimeIdentificationDigitsByCodeEntityIndex = new MaritimeIdentificationDigitsByCodeEntityIndex( );
        readonly MaritimeIdentificationDigitsByCountryEntityIndex _maritimeIdentificationDigitsByCountryEntityIndex = new MaritimeIdentificationDigitsByCountryEntityIndex( );
        readonly MediaProxySessionByServiceAndNameEntityIndex _mediaProxySessionByServiceAndNameEntityIndex = new MediaProxySessionByServiceAndNameEntityIndex( );
        readonly MediaProxySessionFileByProxySessionAndTimestampEntityIndex _mediaProxySessionFileByProxySessionAndTimestampEntityIndex = new MediaProxySessionFileByProxySessionAndTimestampEntityIndex( );
        readonly MediaProxySessionOptionsByProxySessionAndTimestampEntityIndex _mediaProxySessionOptionsByProxySessionAndTimestampEntityIndex = new MediaProxySessionOptionsByProxySessionAndTimestampEntityIndex( );
        readonly MediaServiceOptionsByMediaServiceAndTimestampEntityIndex _mediaServiceOptionsByMediaServiceAndTimestampEntityIndex = new MediaServiceOptionsByMediaServiceAndTimestampEntityIndex( );
        readonly NamespaceElementByNamespaceAndNameEntityIndex _namespaceElementByNamespaceAndNameEntityIndex = new NamespaceElementByNamespaceAndNameEntityIndex( );
        readonly OilSpillByOilSpillDetectorAndTimestampEntityIndex _oilSpillByOilSpillDetectorAndTimestampEntityIndex = new OilSpillByOilSpillDetectorAndTimestampEntityIndex( );
        readonly OilSpillByTimestampEntityIndex _oilSpillByTimestampEntityIndex = new OilSpillByTimestampEntityIndex( );
        readonly OilSpillDetectorCommandByOilSpillDetectorAndTimestampEntityIndex _oilSpillDetectorCommandByOilSpillDetectorAndTimestampEntityIndex = new OilSpillDetectorCommandByOilSpillDetectorAndTimestampEntityIndex( );
        readonly OilSpillDetectorCommandByTimestampEntityIndex _oilSpillDetectorCommandByTimestampEntityIndex = new OilSpillDetectorCommandByTimestampEntityIndex( );
        readonly OilSpillDetectorCommandByReplyEntityIndex _oilSpillDetectorCommandByReplyEntityIndex = new OilSpillDetectorCommandByReplyEntityIndex( );
        readonly OilSpillDetectorCommandByReplyIsNullEntityIndex _oilSpillDetectorCommandByReplyIsNullEntityIndex = new OilSpillDetectorCommandByReplyIsNullEntityIndex( );
        readonly OilSpillDetectorCommandReplyByOilSpillDetectorAndTimestampEntityIndex _oilSpillDetectorCommandReplyByOilSpillDetectorAndTimestampEntityIndex = new OilSpillDetectorCommandReplyByOilSpillDetectorAndTimestampEntityIndex( );
        readonly OilSpillDetectorCommandReplyByTimestampEntityIndex _oilSpillDetectorCommandReplyByTimestampEntityIndex = new OilSpillDetectorCommandReplyByTimestampEntityIndex( );
        readonly OilSpillDetectorCommandReplyByCommandEntityIndex _oilSpillDetectorCommandReplyByCommandEntityIndex = new OilSpillDetectorCommandReplyByCommandEntityIndex( );
        readonly OilSpillDetectorCommandReplyByCommandIsNullEntityIndex _oilSpillDetectorCommandReplyByCommandIsNullEntityIndex = new OilSpillDetectorCommandReplyByCommandIsNullEntityIndex( );
        readonly OilSpillDetectorConfigurationByOilSpillDetectorAndTimestampEntityIndex _oilSpillDetectorConfigurationByOilSpillDetectorAndTimestampEntityIndex = new OilSpillDetectorConfigurationByOilSpillDetectorAndTimestampEntityIndex( );
        readonly OilSpillDetectorConfigurationByTimestampEntityIndex _oilSpillDetectorConfigurationByTimestampEntityIndex = new OilSpillDetectorConfigurationByTimestampEntityIndex( );
        readonly OilSpillDetectorConfigurationByTargetMMSIEntityIndex _oilSpillDetectorConfigurationByTargetMMSIEntityIndex = new OilSpillDetectorConfigurationByTargetMMSIEntityIndex( );
        readonly OilSpillDetectorConfigurationByTargetMMSIIsNullEntityIndex _oilSpillDetectorConfigurationByTargetMMSIIsNullEntityIndex = new OilSpillDetectorConfigurationByTargetMMSIIsNullEntityIndex( );
        readonly Position2DTimeseriesValueByTimeseriesAndTimestampEntityIndex _position2DTimeseriesValueByTimeseriesAndTimestampEntityIndex = new Position2DTimeseriesValueByTimeseriesAndTimestampEntityIndex( );
        readonly Position2DTimeseriesValueByTimestampEntityIndex _position2DTimeseriesValueByTimestampEntityIndex = new Position2DTimeseriesValueByTimestampEntityIndex( );
        readonly Position3DTimeseriesValueByTimeseriesAndTimestampEntityIndex _position3DTimeseriesValueByTimeseriesAndTimestampEntityIndex = new Position3DTimeseriesValueByTimeseriesAndTimestampEntityIndex( );
        readonly Position3DTimeseriesValueByTimestampEntityIndex _position3DTimeseriesValueByTimestampEntityIndex = new Position3DTimeseriesValueByTimestampEntityIndex( );
        readonly PropertyByElementAndDefinitionEntityIndex _propertyByElementAndDefinitionEntityIndex = new PropertyByElementAndDefinitionEntityIndex( );
        readonly PropertyByDefinitionEntityIndex _propertyByDefinitionEntityIndex = new PropertyByDefinitionEntityIndex( );
        readonly ReferencePropertyByValueEntityIndex _referencePropertyByValueEntityIndex = new ReferencePropertyByValueEntityIndex( );
        readonly ReferencePropertyByValueIsNullEntityIndex _referencePropertyByValueIsNullEntityIndex = new ReferencePropertyByValueIsNullEntityIndex( );
        readonly BinaryTimeseriesPropertyByTimeseriesEntityIndex _binaryTimeseriesPropertyByTimeseriesEntityIndex = new BinaryTimeseriesPropertyByTimeseriesEntityIndex( );
        readonly BinaryTimeseriesPropertyByTimeseriesIsNullEntityIndex _binaryTimeseriesPropertyByTimeseriesIsNullEntityIndex = new BinaryTimeseriesPropertyByTimeseriesIsNullEntityIndex( );
        readonly BooleanTimeseriesPropertyByTimeseriesEntityIndex _booleanTimeseriesPropertyByTimeseriesEntityIndex = new BooleanTimeseriesPropertyByTimeseriesEntityIndex( );
        readonly BooleanTimeseriesPropertyByTimeseriesIsNullEntityIndex _booleanTimeseriesPropertyByTimeseriesIsNullEntityIndex = new BooleanTimeseriesPropertyByTimeseriesIsNullEntityIndex( );
        readonly ByteTimeseriesPropertyByTimeseriesEntityIndex _byteTimeseriesPropertyByTimeseriesEntityIndex = new ByteTimeseriesPropertyByTimeseriesEntityIndex( );
        readonly ByteTimeseriesPropertyByTimeseriesIsNullEntityIndex _byteTimeseriesPropertyByTimeseriesIsNullEntityIndex = new ByteTimeseriesPropertyByTimeseriesIsNullEntityIndex( );
        readonly DateTimeTimeseriesPropertyByTimeseriesEntityIndex _dateTimeTimeseriesPropertyByTimeseriesEntityIndex = new DateTimeTimeseriesPropertyByTimeseriesEntityIndex( );
        readonly DateTimeTimeseriesPropertyByTimeseriesIsNullEntityIndex _dateTimeTimeseriesPropertyByTimeseriesIsNullEntityIndex = new DateTimeTimeseriesPropertyByTimeseriesIsNullEntityIndex( );
        readonly DoubleTimeseriesPropertyByTimeseriesEntityIndex _doubleTimeseriesPropertyByTimeseriesEntityIndex = new DoubleTimeseriesPropertyByTimeseriesEntityIndex( );
        readonly DoubleTimeseriesPropertyByTimeseriesIsNullEntityIndex _doubleTimeseriesPropertyByTimeseriesIsNullEntityIndex = new DoubleTimeseriesPropertyByTimeseriesIsNullEntityIndex( );
        readonly GuidTimeseriesPropertyByTimeseriesEntityIndex _guidTimeseriesPropertyByTimeseriesEntityIndex = new GuidTimeseriesPropertyByTimeseriesEntityIndex( );
        readonly GuidTimeseriesPropertyByTimeseriesIsNullEntityIndex _guidTimeseriesPropertyByTimeseriesIsNullEntityIndex = new GuidTimeseriesPropertyByTimeseriesIsNullEntityIndex( );
        readonly Int16TimeseriesPropertyByTimeseriesEntityIndex _int16TimeseriesPropertyByTimeseriesEntityIndex = new Int16TimeseriesPropertyByTimeseriesEntityIndex( );
        readonly Int16TimeseriesPropertyByTimeseriesIsNullEntityIndex _int16TimeseriesPropertyByTimeseriesIsNullEntityIndex = new Int16TimeseriesPropertyByTimeseriesIsNullEntityIndex( );
        readonly Int32TimeseriesPropertyByTimeseriesEntityIndex _int32TimeseriesPropertyByTimeseriesEntityIndex = new Int32TimeseriesPropertyByTimeseriesEntityIndex( );
        readonly Int32TimeseriesPropertyByTimeseriesIsNullEntityIndex _int32TimeseriesPropertyByTimeseriesIsNullEntityIndex = new Int32TimeseriesPropertyByTimeseriesIsNullEntityIndex( );
        readonly Int64TimeseriesPropertyByTimeseriesEntityIndex _int64TimeseriesPropertyByTimeseriesEntityIndex = new Int64TimeseriesPropertyByTimeseriesEntityIndex( );
        readonly Int64TimeseriesPropertyByTimeseriesIsNullEntityIndex _int64TimeseriesPropertyByTimeseriesIsNullEntityIndex = new Int64TimeseriesPropertyByTimeseriesIsNullEntityIndex( );
        readonly ReferenceTimeseriesPropertyByTimeseriesEntityIndex _referenceTimeseriesPropertyByTimeseriesEntityIndex = new ReferenceTimeseriesPropertyByTimeseriesEntityIndex( );
        readonly ReferenceTimeseriesPropertyByTimeseriesIsNullEntityIndex _referenceTimeseriesPropertyByTimeseriesIsNullEntityIndex = new ReferenceTimeseriesPropertyByTimeseriesIsNullEntityIndex( );
        readonly SByteTimeseriesPropertyByTimeseriesEntityIndex _sByteTimeseriesPropertyByTimeseriesEntityIndex = new SByteTimeseriesPropertyByTimeseriesEntityIndex( );
        readonly SByteTimeseriesPropertyByTimeseriesIsNullEntityIndex _sByteTimeseriesPropertyByTimeseriesIsNullEntityIndex = new SByteTimeseriesPropertyByTimeseriesIsNullEntityIndex( );
        readonly SingleTimeseriesPropertyByTimeseriesEntityIndex _singleTimeseriesPropertyByTimeseriesEntityIndex = new SingleTimeseriesPropertyByTimeseriesEntityIndex( );
        readonly SingleTimeseriesPropertyByTimeseriesIsNullEntityIndex _singleTimeseriesPropertyByTimeseriesIsNullEntityIndex = new SingleTimeseriesPropertyByTimeseriesIsNullEntityIndex( );
        readonly StringTimeseriesPropertyByTimeseriesEntityIndex _stringTimeseriesPropertyByTimeseriesEntityIndex = new StringTimeseriesPropertyByTimeseriesEntityIndex( );
        readonly StringTimeseriesPropertyByTimeseriesIsNullEntityIndex _stringTimeseriesPropertyByTimeseriesIsNullEntityIndex = new StringTimeseriesPropertyByTimeseriesIsNullEntityIndex( );
        readonly TimeSpanTimeseriesPropertyByTimeseriesEntityIndex _timeSpanTimeseriesPropertyByTimeseriesEntityIndex = new TimeSpanTimeseriesPropertyByTimeseriesEntityIndex( );
        readonly TimeSpanTimeseriesPropertyByTimeseriesIsNullEntityIndex _timeSpanTimeseriesPropertyByTimeseriesIsNullEntityIndex = new TimeSpanTimeseriesPropertyByTimeseriesIsNullEntityIndex( );
        readonly UInt16TimeseriesPropertyByTimeseriesEntityIndex _uInt16TimeseriesPropertyByTimeseriesEntityIndex = new UInt16TimeseriesPropertyByTimeseriesEntityIndex( );
        readonly UInt16TimeseriesPropertyByTimeseriesIsNullEntityIndex _uInt16TimeseriesPropertyByTimeseriesIsNullEntityIndex = new UInt16TimeseriesPropertyByTimeseriesIsNullEntityIndex( );
        readonly UInt32TimeseriesPropertyByTimeseriesEntityIndex _uInt32TimeseriesPropertyByTimeseriesEntityIndex = new UInt32TimeseriesPropertyByTimeseriesEntityIndex( );
        readonly UInt32TimeseriesPropertyByTimeseriesIsNullEntityIndex _uInt32TimeseriesPropertyByTimeseriesIsNullEntityIndex = new UInt32TimeseriesPropertyByTimeseriesIsNullEntityIndex( );
        readonly UInt64TimeseriesPropertyByTimeseriesEntityIndex _uInt64TimeseriesPropertyByTimeseriesEntityIndex = new UInt64TimeseriesPropertyByTimeseriesEntityIndex( );
        readonly UInt64TimeseriesPropertyByTimeseriesIsNullEntityIndex _uInt64TimeseriesPropertyByTimeseriesIsNullEntityIndex = new UInt64TimeseriesPropertyByTimeseriesIsNullEntityIndex( );
        readonly PropertyDefinitionByElementTypeAndNameEntityIndex _propertyDefinitionByElementTypeAndNameEntityIndex = new PropertyDefinitionByElementTypeAndNameEntityIndex( );
        readonly ReferencePropertyDefinitionByDefaultValueEntityIndex _referencePropertyDefinitionByDefaultValueEntityIndex = new ReferencePropertyDefinitionByDefaultValueEntityIndex( );
        readonly ReferencePropertyDefinitionByDefaultValueIsNullEntityIndex _referencePropertyDefinitionByDefaultValueIsNullEntityIndex = new ReferencePropertyDefinitionByDefaultValueIsNullEntityIndex( );
        readonly ReferencePropertyDefinitionByReferencedElementTypeEntityIndex _referencePropertyDefinitionByReferencedElementTypeEntityIndex = new ReferencePropertyDefinitionByReferencedElementTypeEntityIndex( );
        readonly ReferencePropertyDefinitionByReferencedElementTypeIsNullEntityIndex _referencePropertyDefinitionByReferencedElementTypeIsNullEntityIndex = new ReferencePropertyDefinitionByReferencedElementTypeIsNullEntityIndex( );
        readonly ReferenceTimeseriesPropertyDefinitionByReferencedElementTypeEntityIndex _referenceTimeseriesPropertyDefinitionByReferencedElementTypeEntityIndex = new ReferenceTimeseriesPropertyDefinitionByReferencedElementTypeEntityIndex( );
        readonly ReferenceTimeseriesPropertyDefinitionByReferencedElementTypeIsNullEntityIndex _referenceTimeseriesPropertyDefinitionByReferencedElementTypeIsNullEntityIndex = new ReferenceTimeseriesPropertyDefinitionByReferencedElementTypeIsNullEntityIndex( );
        readonly RadarAlarmStatusByRadarAndTimestampEntityIndex _radarAlarmStatusByRadarAndTimestampEntityIndex = new RadarAlarmStatusByRadarAndTimestampEntityIndex( );
        readonly RadarAlarmStatusByTimestampEntityIndex _radarAlarmStatusByTimestampEntityIndex = new RadarAlarmStatusByTimestampEntityIndex( );
        readonly RadarCommandByRadarAndTimestampEntityIndex _radarCommandByRadarAndTimestampEntityIndex = new RadarCommandByRadarAndTimestampEntityIndex( );
        readonly RadarCommandByTimestampEntityIndex _radarCommandByTimestampEntityIndex = new RadarCommandByTimestampEntityIndex( );
        readonly RadarCommandByReplyEntityIndex _radarCommandByReplyEntityIndex = new RadarCommandByReplyEntityIndex( );
        readonly RadarCommandByReplyIsNullEntityIndex _radarCommandByReplyIsNullEntityIndex = new RadarCommandByReplyIsNullEntityIndex( );
        readonly RadarCommandReplyByRadarAndTimestampEntityIndex _radarCommandReplyByRadarAndTimestampEntityIndex = new RadarCommandReplyByRadarAndTimestampEntityIndex( );
        readonly RadarCommandReplyByTimestampEntityIndex _radarCommandReplyByTimestampEntityIndex = new RadarCommandReplyByTimestampEntityIndex( );
        readonly RadarCommandReplyByCommandEntityIndex _radarCommandReplyByCommandEntityIndex = new RadarCommandReplyByCommandEntityIndex( );
        readonly RadarCommandReplyByCommandIsNullEntityIndex _radarCommandReplyByCommandIsNullEntityIndex = new RadarCommandReplyByCommandIsNullEntityIndex( );
        readonly RadarConfigurationByRadarAndTimestampEntityIndex _radarConfigurationByRadarAndTimestampEntityIndex = new RadarConfigurationByRadarAndTimestampEntityIndex( );
        readonly RadarConfigurationByTimestampEntityIndex _radarConfigurationByTimestampEntityIndex = new RadarConfigurationByTimestampEntityIndex( );
        readonly RadarImageByRadarAndTimestampEntityIndex _radarImageByRadarAndTimestampEntityIndex = new RadarImageByRadarAndTimestampEntityIndex( );
        readonly RadarImageByTimestampEntityIndex _radarImageByTimestampEntityIndex = new RadarImageByTimestampEntityIndex( );
        readonly RadarRawTrackTableByRadarAndTimestampEntityIndex _radarRawTrackTableByRadarAndTimestampEntityIndex = new RadarRawTrackTableByRadarAndTimestampEntityIndex( );
        readonly RadarRawTrackTableByTimestampEntityIndex _radarRawTrackTableByTimestampEntityIndex = new RadarRawTrackTableByTimestampEntityIndex( );
        readonly RadarStatusByRadarAndTimestampEntityIndex _radarStatusByRadarAndTimestampEntityIndex = new RadarStatusByRadarAndTimestampEntityIndex( );
        readonly RadarStatusByTimestampEntityIndex _radarStatusByTimestampEntityIndex = new RadarStatusByTimestampEntityIndex( );
        readonly RadioCommandByRadioAndTimestampEntityIndex _radioCommandByRadioAndTimestampEntityIndex = new RadioCommandByRadioAndTimestampEntityIndex( );
        readonly RadioCommandByTimestampEntityIndex _radioCommandByTimestampEntityIndex = new RadioCommandByTimestampEntityIndex( );
        readonly RadioCommandByReplyEntityIndex _radioCommandByReplyEntityIndex = new RadioCommandByReplyEntityIndex( );
        readonly RadioCommandByReplyIsNullEntityIndex _radioCommandByReplyIsNullEntityIndex = new RadioCommandByReplyIsNullEntityIndex( );
        readonly RadioCommandReplyByRadioAndTimestampEntityIndex _radioCommandReplyByRadioAndTimestampEntityIndex = new RadioCommandReplyByRadioAndTimestampEntityIndex( );
        readonly RadioCommandReplyByTimestampEntityIndex _radioCommandReplyByTimestampEntityIndex = new RadioCommandReplyByTimestampEntityIndex( );
        readonly RadioCommandReplyByCommandEntityIndex _radioCommandReplyByCommandEntityIndex = new RadioCommandReplyByCommandEntityIndex( );
        readonly RadioCommandReplyByCommandIsNullEntityIndex _radioCommandReplyByCommandIsNullEntityIndex = new RadioCommandReplyByCommandIsNullEntityIndex( );
        readonly RadioConfigurationByRadioAndTimestampEntityIndex _radioConfigurationByRadioAndTimestampEntityIndex = new RadioConfigurationByRadioAndTimestampEntityIndex( );
        readonly RadioConfigurationByTimestampEntityIndex _radioConfigurationByTimestampEntityIndex = new RadioConfigurationByTimestampEntityIndex( );
        readonly RadomeCommandByRadomeAndTimestampEntityIndex _radomeCommandByRadomeAndTimestampEntityIndex = new RadomeCommandByRadomeAndTimestampEntityIndex( );
        readonly RadomeCommandByTimestampEntityIndex _radomeCommandByTimestampEntityIndex = new RadomeCommandByTimestampEntityIndex( );
        readonly RadomeCommandByReplyEntityIndex _radomeCommandByReplyEntityIndex = new RadomeCommandByReplyEntityIndex( );
        readonly RadomeCommandByReplyIsNullEntityIndex _radomeCommandByReplyIsNullEntityIndex = new RadomeCommandByReplyIsNullEntityIndex( );
        readonly RadomeCommandReplyByRadomeAndTimestampEntityIndex _radomeCommandReplyByRadomeAndTimestampEntityIndex = new RadomeCommandReplyByRadomeAndTimestampEntityIndex( );
        readonly RadomeCommandReplyByTimestampEntityIndex _radomeCommandReplyByTimestampEntityIndex = new RadomeCommandReplyByTimestampEntityIndex( );
        readonly RadomeCommandReplyByCommandEntityIndex _radomeCommandReplyByCommandEntityIndex = new RadomeCommandReplyByCommandEntityIndex( );
        readonly RadomeCommandReplyByCommandIsNullEntityIndex _radomeCommandReplyByCommandIsNullEntityIndex = new RadomeCommandReplyByCommandIsNullEntityIndex( );
        readonly RadomeConfigurationByRadomeAndTimestampEntityIndex _radomeConfigurationByRadomeAndTimestampEntityIndex = new RadomeConfigurationByRadomeAndTimestampEntityIndex( );
        readonly RadomeConfigurationByTimestampEntityIndex _radomeConfigurationByTimestampEntityIndex = new RadomeConfigurationByTimestampEntityIndex( );
        readonly ReferenceTimeseriesValueByTimeseriesAndTimestampEntityIndex _referenceTimeseriesValueByTimeseriesAndTimestampEntityIndex = new ReferenceTimeseriesValueByTimeseriesAndTimestampEntityIndex( );
        readonly ReferenceTimeseriesValueByTimestampEntityIndex _referenceTimeseriesValueByTimestampEntityIndex = new ReferenceTimeseriesValueByTimestampEntityIndex( );
        readonly ReferenceTimeseriesValueByValueEntityIndex _referenceTimeseriesValueByValueEntityIndex = new ReferenceTimeseriesValueByValueEntityIndex( );
        readonly SByteTimeseriesValueByTimeseriesAndTimestampEntityIndex _sByteTimeseriesValueByTimeseriesAndTimestampEntityIndex = new SByteTimeseriesValueByTimeseriesAndTimestampEntityIndex( );
        readonly SByteTimeseriesValueByTimestampEntityIndex _sByteTimeseriesValueByTimestampEntityIndex = new SByteTimeseriesValueByTimestampEntityIndex( );
        readonly SecurityDomainByNameEntityIndex _securityDomainByNameEntityIndex = new SecurityDomainByNameEntityIndex( );
        readonly SecurityIdentifierByDomainAndIdentityEntityIndex _securityIdentifierByDomainAndIdentityEntityIndex = new SecurityIdentifierByDomainAndIdentityEntityIndex( );
        readonly SecurityRoleByNameEntityIndex _securityRoleByNameEntityIndex = new SecurityRoleByNameEntityIndex( );
        readonly SecurityIdentifierRoleLinkByMemberAndStartEntityIndex _securityIdentifierRoleLinkByMemberAndStartEntityIndex = new SecurityIdentifierRoleLinkByMemberAndStartEntityIndex( );
        readonly SecurityIdentifierRoleLinkByRoleAndStartEntityIndex _securityIdentifierRoleLinkByRoleAndStartEntityIndex = new SecurityIdentifierRoleLinkByRoleAndStartEntityIndex( );
        readonly SecurityIdentifierRoleLinkByStartEntityIndex _securityIdentifierRoleLinkByStartEntityIndex = new SecurityIdentifierRoleLinkByStartEntityIndex( );
        readonly SecurityLoginSessionByLoginAndFromTimeEntityIndex _securityLoginSessionByLoginAndFromTimeEntityIndex = new SecurityLoginSessionByLoginAndFromTimeEntityIndex( );
        readonly SecurityLoginSessionByFromTimeEntityIndex _securityLoginSessionByFromTimeEntityIndex = new SecurityLoginSessionByFromTimeEntityIndex( );
        readonly SecurityPermissionByIdentifierTypeCodeAndTimestampEntityIndex _securityPermissionByIdentifierTypeCodeAndTimestampEntityIndex = new SecurityPermissionByIdentifierTypeCodeAndTimestampEntityIndex( );
        readonly SecurityPermissionByTimestampEntityIndex _securityPermissionByTimestampEntityIndex = new SecurityPermissionByTimestampEntityIndex( );
        readonly SingleTimeseriesValueByTimeseriesAndTimestampEntityIndex _singleTimeseriesValueByTimeseriesAndTimestampEntityIndex = new SingleTimeseriesValueByTimeseriesAndTimestampEntityIndex( );
        readonly SingleTimeseriesValueByTimestampEntityIndex _singleTimeseriesValueByTimestampEntityIndex = new SingleTimeseriesValueByTimestampEntityIndex( );
        readonly StringTimeseriesValueByTimeseriesAndTimestampEntityIndex _stringTimeseriesValueByTimeseriesAndTimestampEntityIndex = new StringTimeseriesValueByTimeseriesAndTimestampEntityIndex( );
        readonly StringTimeseriesValueByTimestampEntityIndex _stringTimeseriesValueByTimestampEntityIndex = new StringTimeseriesValueByTimestampEntityIndex( );
        readonly TimeseriesCatalogElementByCatalogAndNameEntityIndex _timeseriesCatalogElementByCatalogAndNameEntityIndex = new TimeseriesCatalogElementByCatalogAndNameEntityIndex( );
        readonly TimeseriesCatalogElementByCatalogIsNullAndNameEntityIndex _timeseriesCatalogElementByCatalogIsNullAndNameEntityIndex = new TimeseriesCatalogElementByCatalogIsNullAndNameEntityIndex( );
        readonly AisAidToNavigationOffPositionTimeseriesByAidToNavigationEntityIndex _aisAidToNavigationOffPositionTimeseriesByAidToNavigationEntityIndex = new AisAidToNavigationOffPositionTimeseriesByAidToNavigationEntityIndex( );
        readonly AisAidToNavigationOffPositionTimeseriesByAidToNavigationIsNullEntityIndex _aisAidToNavigationOffPositionTimeseriesByAidToNavigationIsNullEntityIndex = new AisAidToNavigationOffPositionTimeseriesByAidToNavigationIsNullEntityIndex( );
        readonly GyroCourseTimeseriesByGyroDeviceEntityIndex _gyroCourseTimeseriesByGyroDeviceEntityIndex = new GyroCourseTimeseriesByGyroDeviceEntityIndex( );
        readonly GyroCourseTimeseriesByGyroDeviceIsNullEntityIndex _gyroCourseTimeseriesByGyroDeviceIsNullEntityIndex = new GyroCourseTimeseriesByGyroDeviceIsNullEntityIndex( );
        readonly GyroHeadingMagneticNorthTimeseriesByGyroDeviceEntityIndex _gyroHeadingMagneticNorthTimeseriesByGyroDeviceEntityIndex = new GyroHeadingMagneticNorthTimeseriesByGyroDeviceEntityIndex( );
        readonly GyroHeadingMagneticNorthTimeseriesByGyroDeviceIsNullEntityIndex _gyroHeadingMagneticNorthTimeseriesByGyroDeviceIsNullEntityIndex = new GyroHeadingMagneticNorthTimeseriesByGyroDeviceIsNullEntityIndex( );
        readonly GyroHeadingTrueNorthTimeseriesByGyroDeviceEntityIndex _gyroHeadingTrueNorthTimeseriesByGyroDeviceEntityIndex = new GyroHeadingTrueNorthTimeseriesByGyroDeviceEntityIndex( );
        readonly GyroHeadingTrueNorthTimeseriesByGyroDeviceIsNullEntityIndex _gyroHeadingTrueNorthTimeseriesByGyroDeviceIsNullEntityIndex = new GyroHeadingTrueNorthTimeseriesByGyroDeviceIsNullEntityIndex( );
        readonly GyroPitchTimeseriesByGyroDeviceEntityIndex _gyroPitchTimeseriesByGyroDeviceEntityIndex = new GyroPitchTimeseriesByGyroDeviceEntityIndex( );
        readonly GyroPitchTimeseriesByGyroDeviceIsNullEntityIndex _gyroPitchTimeseriesByGyroDeviceIsNullEntityIndex = new GyroPitchTimeseriesByGyroDeviceIsNullEntityIndex( );
        readonly GyroRateOfTurnTimeseriesByGyroDeviceEntityIndex _gyroRateOfTurnTimeseriesByGyroDeviceEntityIndex = new GyroRateOfTurnTimeseriesByGyroDeviceEntityIndex( );
        readonly GyroRateOfTurnTimeseriesByGyroDeviceIsNullEntityIndex _gyroRateOfTurnTimeseriesByGyroDeviceIsNullEntityIndex = new GyroRateOfTurnTimeseriesByGyroDeviceIsNullEntityIndex( );
        readonly GyroRollTimeseriesByGyroDeviceEntityIndex _gyroRollTimeseriesByGyroDeviceEntityIndex = new GyroRollTimeseriesByGyroDeviceEntityIndex( );
        readonly GyroRollTimeseriesByGyroDeviceIsNullEntityIndex _gyroRollTimeseriesByGyroDeviceIsNullEntityIndex = new GyroRollTimeseriesByGyroDeviceIsNullEntityIndex( );
        readonly GyroSpeedTimeseriesByGyroDeviceEntityIndex _gyroSpeedTimeseriesByGyroDeviceEntityIndex = new GyroSpeedTimeseriesByGyroDeviceEntityIndex( );
        readonly GyroSpeedTimeseriesByGyroDeviceIsNullEntityIndex _gyroSpeedTimeseriesByGyroDeviceIsNullEntityIndex = new GyroSpeedTimeseriesByGyroDeviceIsNullEntityIndex( );
        readonly WeatherStationAbsoluteHumidityTimeseriesByWeatherStationEntityIndex _weatherStationAbsoluteHumidityTimeseriesByWeatherStationEntityIndex = new WeatherStationAbsoluteHumidityTimeseriesByWeatherStationEntityIndex( );
        readonly WeatherStationAbsoluteHumidityTimeseriesByWeatherStationIsNullEntityIndex _weatherStationAbsoluteHumidityTimeseriesByWeatherStationIsNullEntityIndex = new WeatherStationAbsoluteHumidityTimeseriesByWeatherStationIsNullEntityIndex( );
        readonly WeatherStationAirTemperatureTimeseriesByWeatherStationEntityIndex _weatherStationAirTemperatureTimeseriesByWeatherStationEntityIndex = new WeatherStationAirTemperatureTimeseriesByWeatherStationEntityIndex( );
        readonly WeatherStationAirTemperatureTimeseriesByWeatherStationIsNullEntityIndex _weatherStationAirTemperatureTimeseriesByWeatherStationIsNullEntityIndex = new WeatherStationAirTemperatureTimeseriesByWeatherStationIsNullEntityIndex( );
        readonly WeatherStationBarometricPressureTimeseriesByWeatherStationEntityIndex _weatherStationBarometricPressureTimeseriesByWeatherStationEntityIndex = new WeatherStationBarometricPressureTimeseriesByWeatherStationEntityIndex( );
        readonly WeatherStationBarometricPressureTimeseriesByWeatherStationIsNullEntityIndex _weatherStationBarometricPressureTimeseriesByWeatherStationIsNullEntityIndex = new WeatherStationBarometricPressureTimeseriesByWeatherStationIsNullEntityIndex( );
        readonly WeatherStationDewPointTimeseriesByWeatherStationEntityIndex _weatherStationDewPointTimeseriesByWeatherStationEntityIndex = new WeatherStationDewPointTimeseriesByWeatherStationEntityIndex( );
        readonly WeatherStationDewPointTimeseriesByWeatherStationIsNullEntityIndex _weatherStationDewPointTimeseriesByWeatherStationIsNullEntityIndex = new WeatherStationDewPointTimeseriesByWeatherStationIsNullEntityIndex( );
        readonly WeatherStationRelativeHumidityTimeseriesByWeatherStationEntityIndex _weatherStationRelativeHumidityTimeseriesByWeatherStationEntityIndex = new WeatherStationRelativeHumidityTimeseriesByWeatherStationEntityIndex( );
        readonly WeatherStationRelativeHumidityTimeseriesByWeatherStationIsNullEntityIndex _weatherStationRelativeHumidityTimeseriesByWeatherStationIsNullEntityIndex = new WeatherStationRelativeHumidityTimeseriesByWeatherStationIsNullEntityIndex( );
        readonly WeatherStationWaterTemperatureTimeseriesByWeatherStationEntityIndex _weatherStationWaterTemperatureTimeseriesByWeatherStationEntityIndex = new WeatherStationWaterTemperatureTimeseriesByWeatherStationEntityIndex( );
        readonly WeatherStationWaterTemperatureTimeseriesByWeatherStationIsNullEntityIndex _weatherStationWaterTemperatureTimeseriesByWeatherStationIsNullEntityIndex = new WeatherStationWaterTemperatureTimeseriesByWeatherStationIsNullEntityIndex( );
        readonly WeatherStationWindDirectionTimeseriesByWeatherStationEntityIndex _weatherStationWindDirectionTimeseriesByWeatherStationEntityIndex = new WeatherStationWindDirectionTimeseriesByWeatherStationEntityIndex( );
        readonly WeatherStationWindDirectionTimeseriesByWeatherStationIsNullEntityIndex _weatherStationWindDirectionTimeseriesByWeatherStationIsNullEntityIndex = new WeatherStationWindDirectionTimeseriesByWeatherStationIsNullEntityIndex( );
        readonly WeatherStationWindSpeedTimeseriesByWeatherStationEntityIndex _weatherStationWindSpeedTimeseriesByWeatherStationEntityIndex = new WeatherStationWindSpeedTimeseriesByWeatherStationEntityIndex( );
        readonly WeatherStationWindSpeedTimeseriesByWeatherStationIsNullEntityIndex _weatherStationWindSpeedTimeseriesByWeatherStationIsNullEntityIndex = new WeatherStationWindSpeedTimeseriesByWeatherStationIsNullEntityIndex( );
        readonly TimeSpanTimeseriesValueByTimeseriesAndTimestampEntityIndex _timeSpanTimeseriesValueByTimeseriesAndTimestampEntityIndex = new TimeSpanTimeseriesValueByTimeseriesAndTimestampEntityIndex( );
        readonly TimeSpanTimeseriesValueByTimestampEntityIndex _timeSpanTimeseriesValueByTimestampEntityIndex = new TimeSpanTimeseriesValueByTimestampEntityIndex( );
        readonly TrackableItemTrackLinkByItemAndStartEntityIndex _trackableItemTrackLinkByItemAndStartEntityIndex = new TrackableItemTrackLinkByItemAndStartEntityIndex( );
        readonly TrackableItemTrackLinkByItemAndEndEntityIndex _trackableItemTrackLinkByItemAndEndEntityIndex = new TrackableItemTrackLinkByItemAndEndEntityIndex( );
        readonly TrackableItemTrackLinkByItemAndEndIsNullEntityIndex _trackableItemTrackLinkByItemAndEndIsNullEntityIndex = new TrackableItemTrackLinkByItemAndEndIsNullEntityIndex( );
        readonly TrackableItemTrackLinkByTrackAndStartEntityIndex _trackableItemTrackLinkByTrackAndStartEntityIndex = new TrackableItemTrackLinkByTrackAndStartEntityIndex( );
        readonly TrackableItemTrackLinkByTrackAndEndEntityIndex _trackableItemTrackLinkByTrackAndEndEntityIndex = new TrackableItemTrackLinkByTrackAndEndEntityIndex( );
        readonly TrackableItemTrackLinkByTrackAndEndIsNullEntityIndex _trackableItemTrackLinkByTrackAndEndIsNullEntityIndex = new TrackableItemTrackLinkByTrackAndEndIsNullEntityIndex( );
        readonly TrackableItemTrackLinkByStartEntityIndex _trackableItemTrackLinkByStartEntityIndex = new TrackableItemTrackLinkByStartEntityIndex( );
        readonly TrackBaseByTrackerTrackNumberAndTimestampEntityIndex _trackBaseByTrackerTrackNumberAndTimestampEntityIndex = new TrackBaseByTrackerTrackNumberAndTimestampEntityIndex( );
        readonly TrackBaseByTrackerAndTimestampEntityIndex _trackBaseByTrackerAndTimestampEntityIndex = new TrackBaseByTrackerAndTimestampEntityIndex( );
        readonly TrackBaseByTrackNumberEntityIndex _trackBaseByTrackNumberEntityIndex = new TrackBaseByTrackNumberEntityIndex( );
        readonly TrackBaseByTimestampEntityIndex _trackBaseByTimestampEntityIndex = new TrackBaseByTimestampEntityIndex( );
        readonly TrackerFilterParametersByTrackerAndNameEntityIndex _trackerFilterParametersByTrackerAndNameEntityIndex = new TrackerFilterParametersByTrackerAndNameEntityIndex( );
        readonly TrackerFilterParametersConfigurationByParametersAndTimestampEntityIndex _trackerFilterParametersConfigurationByParametersAndTimestampEntityIndex = new TrackerFilterParametersConfigurationByParametersAndTimestampEntityIndex( );
        readonly TrackerFilterParametersConfigurationByTimestampEntityIndex _trackerFilterParametersConfigurationByTimestampEntityIndex = new TrackerFilterParametersConfigurationByTimestampEntityIndex( );
        readonly TrackingServiceOptionsByTimestampEntityIndex _trackingServiceOptionsByTimestampEntityIndex = new TrackingServiceOptionsByTimestampEntityIndex( );
        readonly TrackLinkByPrimaryAndStartEntityIndex _trackLinkByPrimaryAndStartEntityIndex = new TrackLinkByPrimaryAndStartEntityIndex( );
        readonly TrackLinkBySecondaryAndStartEntityIndex _trackLinkBySecondaryAndStartEntityIndex = new TrackLinkBySecondaryAndStartEntityIndex( );
        readonly TrackLinkByStartEntityIndex _trackLinkByStartEntityIndex = new TrackLinkByStartEntityIndex( );
        readonly TrackValueByTrackAndTimestampEntityIndex _trackValueByTrackAndTimestampEntityIndex = new TrackValueByTrackAndTimestampEntityIndex( );
        readonly TrackValueByTimestampEntityIndex _trackValueByTimestampEntityIndex = new TrackValueByTimestampEntityIndex( );
        readonly TrackValue3DByTrackAndTimestampEntityIndex _trackValue3DByTrackAndTimestampEntityIndex = new TrackValue3DByTrackAndTimestampEntityIndex( );
        readonly TrackValue3DByTimestampEntityIndex _trackValue3DByTimestampEntityIndex = new TrackValue3DByTimestampEntityIndex( );
        readonly UInt16TimeseriesValueByTimeseriesAndTimestampEntityIndex _uInt16TimeseriesValueByTimeseriesAndTimestampEntityIndex = new UInt16TimeseriesValueByTimeseriesAndTimestampEntityIndex( );
        readonly UInt16TimeseriesValueByTimestampEntityIndex _uInt16TimeseriesValueByTimestampEntityIndex = new UInt16TimeseriesValueByTimestampEntityIndex( );
        readonly UInt32TimeseriesValueByTimeseriesAndTimestampEntityIndex _uInt32TimeseriesValueByTimeseriesAndTimestampEntityIndex = new UInt32TimeseriesValueByTimeseriesAndTimestampEntityIndex( );
        readonly UInt32TimeseriesValueByTimestampEntityIndex _uInt32TimeseriesValueByTimestampEntityIndex = new UInt32TimeseriesValueByTimestampEntityIndex( );
        readonly UInt64TimeseriesValueByTimeseriesAndTimestampEntityIndex _uInt64TimeseriesValueByTimeseriesAndTimestampEntityIndex = new UInt64TimeseriesValueByTimeseriesAndTimestampEntityIndex( );
        readonly UInt64TimeseriesValueByTimestampEntityIndex _uInt64TimeseriesValueByTimestampEntityIndex = new UInt64TimeseriesValueByTimestampEntityIndex( );
        readonly VehicleTypeByNameEntityIndex _vehicleTypeByNameEntityIndex = new VehicleTypeByNameEntityIndex( );
        readonly VesselTypeByNameEntityIndex _vesselTypeByNameEntityIndex = new VesselTypeByNameEntityIndex( );
        readonly VesselTypeByCodeEntityIndex _vesselTypeByCodeEntityIndex = new VesselTypeByCodeEntityIndex( );
        readonly ViewByNameEntityIndex _viewByNameEntityIndex = new ViewByNameEntityIndex( );
        readonly ViewCameraLinkByViewAndStartEntityIndex _viewCameraLinkByViewAndStartEntityIndex = new ViewCameraLinkByViewAndStartEntityIndex( );
        readonly ViewCameraLinkByCameraAndStartEntityIndex _viewCameraLinkByCameraAndStartEntityIndex = new ViewCameraLinkByCameraAndStartEntityIndex( );
        readonly ViewCameraLinkByStartEntityIndex _viewCameraLinkByStartEntityIndex = new ViewCameraLinkByStartEntityIndex( );
        readonly ViewTrackerLinkByViewAndStartEntityIndex _viewTrackerLinkByViewAndStartEntityIndex = new ViewTrackerLinkByViewAndStartEntityIndex( );
        readonly ViewTrackerLinkByTrackerAndStartEntityIndex _viewTrackerLinkByTrackerAndStartEntityIndex = new ViewTrackerLinkByTrackerAndStartEntityIndex( );
        readonly ViewTrackerLinkByStartEntityIndex _viewTrackerLinkByStartEntityIndex = new ViewTrackerLinkByStartEntityIndex( );
        readonly WeatherStationCommandByWeatherStationAndTimestampEntityIndex _weatherStationCommandByWeatherStationAndTimestampEntityIndex = new WeatherStationCommandByWeatherStationAndTimestampEntityIndex( );
        readonly WeatherStationCommandByTimestampEntityIndex _weatherStationCommandByTimestampEntityIndex = new WeatherStationCommandByTimestampEntityIndex( );
        readonly WeatherStationCommandByReplyEntityIndex _weatherStationCommandByReplyEntityIndex = new WeatherStationCommandByReplyEntityIndex( );
        readonly WeatherStationCommandByReplyIsNullEntityIndex _weatherStationCommandByReplyIsNullEntityIndex = new WeatherStationCommandByReplyIsNullEntityIndex( );
        readonly WeatherStationCommandReplyByWeatherStationAndTimestampEntityIndex _weatherStationCommandReplyByWeatherStationAndTimestampEntityIndex = new WeatherStationCommandReplyByWeatherStationAndTimestampEntityIndex( );
        readonly WeatherStationCommandReplyByTimestampEntityIndex _weatherStationCommandReplyByTimestampEntityIndex = new WeatherStationCommandReplyByTimestampEntityIndex( );
        readonly WeatherStationCommandReplyByCommandEntityIndex _weatherStationCommandReplyByCommandEntityIndex = new WeatherStationCommandReplyByCommandEntityIndex( );
        readonly WeatherStationCommandReplyByCommandIsNullEntityIndex _weatherStationCommandReplyByCommandIsNullEntityIndex = new WeatherStationCommandReplyByCommandIsNullEntityIndex( );
        readonly WeatherStationConfigurationByWeatherStationAndTimestampEntityIndex _weatherStationConfigurationByWeatherStationAndTimestampEntityIndex = new WeatherStationConfigurationByWeatherStationAndTimestampEntityIndex( );
        readonly WeatherStationConfigurationByTimestampEntityIndex _weatherStationConfigurationByTimestampEntityIndex = new WeatherStationConfigurationByTimestampEntityIndex( );
        readonly ZoneByNameEntityIndex _zoneByNameEntityIndex = new ZoneByNameEntityIndex( );
        readonly ZoneExceptionsByZoneAndTimestampEntityIndex _zoneExceptionsByZoneAndTimestampEntityIndex = new ZoneExceptionsByZoneAndTimestampEntityIndex( );
        readonly ZoneExceptionsByTimestampEntityIndex _zoneExceptionsByTimestampEntityIndex = new ZoneExceptionsByTimestampEntityIndex( );
        readonly ZoneExceptionsVesselLinkByZoneExceptionsAndVesselEntityIndex _zoneExceptionsVesselLinkByZoneExceptionsAndVesselEntityIndex = new ZoneExceptionsVesselLinkByZoneExceptionsAndVesselEntityIndex( );
        readonly ZoneExceptionsVesselLinkByVesselEntityIndex _zoneExceptionsVesselLinkByVesselEntityIndex = new ZoneExceptionsVesselLinkByVesselEntityIndex( );
        readonly ZoneTrackAlarmByTrackAndTimestampEntityIndex _zoneTrackAlarmByTrackAndTimestampEntityIndex = new ZoneTrackAlarmByTrackAndTimestampEntityIndex( );
        readonly ZoneTrackAlarmByZoneTrackAndTimestampEntityIndex _zoneTrackAlarmByZoneTrackAndTimestampEntityIndex = new ZoneTrackAlarmByZoneTrackAndTimestampEntityIndex( );
        readonly ZoneTrackAlarmByTimestampEntityIndex _zoneTrackAlarmByTimestampEntityIndex = new ZoneTrackAlarmByTimestampEntityIndex( );
    }

}
