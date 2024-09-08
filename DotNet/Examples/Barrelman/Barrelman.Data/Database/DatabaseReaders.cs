using System;
using System.Diagnostics.CodeAnalysis;
using System.IO;

using Microsoft.Data.SqlClient;
using Microsoft.Extensions.Logging;

using Harlinn.Common.Core.Net;
using Harlinn.Common.Core.Net.Data;
using Harlinn.Common.Core.Net.Data.SqlClient;
using Harlinn.Common.Core.Net.IO;

using Barrelman.Data.Types;

namespace Barrelman.Data.Database
{
    public class SimpleAircraftTypeDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  at.[Id], \r\n" +
            "  at.[RowVersion], \r\n" +
            "  at.[Name] \r\n" +
            "FROM [AircraftTypeView] at \r\n";

        public const string BaseViewName = "AircraftTypeView";
        public const string ViewAliasName = "at";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int NAME_FIELD_ID = 2;

        public SimpleAircraftTypeDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
    }

    public class SimpleAisDeviceCommandDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  adc.[Id], \r\n" +
            "  adc.[RowVersion], \r\n" +
            "  adc.[AisDevice], \r\n" +
            "  adc.[Timestamp], \r\n" +
            "  adc.[DeviceCommandSourceType], \r\n" +
            "  adc.[DeviceCommandSourceId], \r\n" +
            "  adc.[Reply] \r\n" +
            "FROM [AisDeviceCommandView] adc \r\n";

        public const string BaseViewName = "AisDeviceCommandView";
        public const string ViewAliasName = "adc";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int AISDEVICE_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int DEVICECOMMANDSOURCETYPE_FIELD_ID = 4;
        public const int DEVICECOMMANDSOURCEID_FIELD_ID = 5;
        public const int REPLY_FIELD_ID = 6;

        public SimpleAisDeviceCommandDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid AisDevice
        {
            get
            {
                return GetGuid( AISDEVICE_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Types.DeviceCommandSourceType DeviceCommandSourceType
        {
            get
            {
                return GetEnum<Types.DeviceCommandSourceType>( DEVICECOMMANDSOURCETYPE_FIELD_ID );
            }
        }
        public Guid DeviceCommandSourceId
        {
            get
            {
                return GetGuid( DEVICECOMMANDSOURCEID_FIELD_ID );
            }
        }
        public Guid? Reply
        {
            get
            {
                return GetNullableGuid( REPLY_FIELD_ID );
            }
        }
    }

    public class SimpleAisDeviceCommandReplyDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  adcr.[Id], \r\n" +
            "  adcr.[RowVersion], \r\n" +
            "  adcr.[AisDevice], \r\n" +
            "  adcr.[Timestamp], \r\n" +
            "  adcr.[Command], \r\n" +
            "  adcr.[Status], \r\n" +
            "  adcr.[Message] \r\n" +
            "FROM [AisDeviceCommandReplyView] adcr \r\n";

        public const string BaseViewName = "AisDeviceCommandReplyView";
        public const string ViewAliasName = "adcr";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int AISDEVICE_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int COMMAND_FIELD_ID = 4;
        public const int STATUS_FIELD_ID = 5;
        public const int MESSAGE_FIELD_ID = 6;

        public SimpleAisDeviceCommandReplyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid AisDevice
        {
            get
            {
                return GetGuid( AISDEVICE_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Guid Command
        {
            get
            {
                return GetGuid( COMMAND_FIELD_ID );
            }
        }
        public Types.DeviceCommandReplyStatus Status
        {
            get
            {
                return GetEnum<Types.DeviceCommandReplyStatus>( STATUS_FIELD_ID );
            }
        }
        public string Message
        {
            get
            {
                return GetString( MESSAGE_FIELD_ID );
            }
        }
    }

    public class SimpleAisDeviceConfigurationDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  adc.[Id], \r\n" +
            "  adc.[RowVersion], \r\n" +
            "  adc.[AisDevice], \r\n" +
            "  adc.[Timestamp], \r\n" +
            "  adc.[Filter], \r\n" +
            "  adc.[NorthWestLatitude], \r\n" +
            "  adc.[NorthWestLongitude], \r\n" +
            "  adc.[SouthEastLatitude], \r\n" +
            "  adc.[SouthEastLongitude], \r\n" +
            "  adc.[ComPort], \r\n" +
            "  adc.[BaudRate], \r\n" +
            "  adc.[IPAddress], \r\n" +
            "  adc.[Port], \r\n" +
            "  adc.[UdpPort], \r\n" +
            "  adc.[Authenticate], \r\n" +
            "  adc.[UserName], \r\n" +
            "  adc.[Password], \r\n" +
            "  adc.[AuthenticationURL], \r\n" +
            "  adc.[ConnectionType], \r\n" +
            "  adc.[SourceUpdateRate], \r\n" +
            "  adc.[ConfigurationURL], \r\n" +
            "  adc.[StoreReceivedSentences] \r\n" +
            "FROM [AisDeviceConfigurationView] adc \r\n";

        public const string BaseViewName = "AisDeviceConfigurationView";
        public const string ViewAliasName = "adc";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int AISDEVICE_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int FILTER_FIELD_ID = 4;
        public const int NORTHWESTLATITUDE_FIELD_ID = 5;
        public const int NORTHWESTLONGITUDE_FIELD_ID = 6;
        public const int SOUTHEASTLATITUDE_FIELD_ID = 7;
        public const int SOUTHEASTLONGITUDE_FIELD_ID = 8;
        public const int COMPORT_FIELD_ID = 9;
        public const int BAUDRATE_FIELD_ID = 10;
        public const int IPADDRESS_FIELD_ID = 11;
        public const int PORT_FIELD_ID = 12;
        public const int UDPPORT_FIELD_ID = 13;
        public const int AUTHENTICATE_FIELD_ID = 14;
        public const int USERNAME_FIELD_ID = 15;
        public const int PASSWORD_FIELD_ID = 16;
        public const int AUTHENTICATIONURL_FIELD_ID = 17;
        public const int CONNECTIONTYPE_FIELD_ID = 18;
        public const int SOURCEUPDATERATE_FIELD_ID = 19;
        public const int CONFIGURATIONURL_FIELD_ID = 20;
        public const int STORERECEIVEDSENTENCES_FIELD_ID = 21;

        public SimpleAisDeviceConfigurationDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid AisDevice
        {
            get
            {
                return GetGuid( AISDEVICE_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public bool Filter
        {
            get
            {
                return GetBoolean( FILTER_FIELD_ID );
            }
        }
        public double NorthWestLatitude
        {
            get
            {
                return GetDouble( NORTHWESTLATITUDE_FIELD_ID );
            }
        }
        public double NorthWestLongitude
        {
            get
            {
                return GetDouble( NORTHWESTLONGITUDE_FIELD_ID );
            }
        }
        public double SouthEastLatitude
        {
            get
            {
                return GetDouble( SOUTHEASTLATITUDE_FIELD_ID );
            }
        }
        public double SouthEastLongitude
        {
            get
            {
                return GetDouble( SOUTHEASTLONGITUDE_FIELD_ID );
            }
        }
        public string ComPort
        {
            get
            {
                return GetString( COMPORT_FIELD_ID );
            }
        }
        public int BaudRate
        {
            get
            {
                return GetInt32( BAUDRATE_FIELD_ID );
            }
        }
        public string IPAddress
        {
            get
            {
                return GetString( IPADDRESS_FIELD_ID );
            }
        }
        public int Port
        {
            get
            {
                return GetInt32( PORT_FIELD_ID );
            }
        }
        public int UdpPort
        {
            get
            {
                return GetInt32( UDPPORT_FIELD_ID );
            }
        }
        public bool Authenticate
        {
            get
            {
                return GetBoolean( AUTHENTICATE_FIELD_ID );
            }
        }
        public string UserName
        {
            get
            {
                return GetString( USERNAME_FIELD_ID );
            }
        }
        public string Password
        {
            get
            {
                return GetString( PASSWORD_FIELD_ID );
            }
        }
        public string AuthenticationURL
        {
            get
            {
                return GetString( AUTHENTICATIONURL_FIELD_ID );
            }
        }
        public Types.AisDeviceConnectionType ConnectionType
        {
            get
            {
                return GetEnum<Types.AisDeviceConnectionType>( CONNECTIONTYPE_FIELD_ID );
            }
        }
        public int SourceUpdateRate
        {
            get
            {
                return GetInt32( SOURCEUPDATERATE_FIELD_ID );
            }
        }
        public string ConfigurationURL
        {
            get
            {
                return GetString( CONFIGURATIONURL_FIELD_ID );
            }
        }
        public bool StoreReceivedSentences
        {
            get
            {
                return GetBoolean( STORERECEIVEDSENTENCES_FIELD_ID );
            }
        }
    }

    public class SimpleAisDeviceRawMessageDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  adrm.[Id], \r\n" +
            "  adrm.[RowVersion], \r\n" +
            "  adrm.[AisDevice], \r\n" +
            "  adrm.[Timestamp], \r\n" +
            "  adrm.[IsSent], \r\n" +
            "  adrm.[Message] \r\n" +
            "FROM [AisDeviceRawMessageView] adrm \r\n";

        public const string BaseViewName = "AisDeviceRawMessageView";
        public const string ViewAliasName = "adrm";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int AISDEVICE_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int ISSENT_FIELD_ID = 4;
        public const int MESSAGE_FIELD_ID = 5;

        public SimpleAisDeviceRawMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid AisDevice
        {
            get
            {
                return GetGuid( AISDEVICE_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public bool IsSent
        {
            get
            {
                return GetBoolean( ISSENT_FIELD_ID );
            }
        }
        public string Message
        {
            get
            {
                return GetString( MESSAGE_FIELD_ID );
            }
        }
    }

    public class SimpleAisDeviceRawSentenceDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  adrs.[Id], \r\n" +
            "  adrs.[RowVersion], \r\n" +
            "  adrs.[AisDevice], \r\n" +
            "  adrs.[Timestamp], \r\n" +
            "  adrs.[Sentence] \r\n" +
            "FROM [AisDeviceRawSentenceView] adrs \r\n";

        public const string BaseViewName = "AisDeviceRawSentenceView";
        public const string ViewAliasName = "adrs";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int AISDEVICE_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int SENTENCE_FIELD_ID = 4;

        public SimpleAisDeviceRawSentenceDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid AisDevice
        {
            get
            {
                return GetGuid( AISDEVICE_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public string Sentence
        {
            get
            {
                return GetString( SENTENCE_FIELD_ID );
            }
        }
    }

    public class SimpleAisMessageDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  am.[Id], \r\n" +
            "  am.[EntityType], \r\n" +
            "  am.[RowVersion], \r\n" +
            "  am.[AisDevice], \r\n" +
            "  am.[ReceivedTimestamp], \r\n" +
            "  am.[MessageSequenceNumber], \r\n" +
            "  am.[Repeat], \r\n" +
            "  am.[Mmsi] \r\n" +
            "FROM [AisMessageView] am \r\n";

        public const string BaseViewName = "AisMessageView";
        public const string ViewAliasName = "am";

        public const int ID_FIELD_ID = 0;
        public const int ENTITYTYPE_FIELD_ID = 1;
        public const int ROWVERSION_FIELD_ID = 2;
        public const int AISDEVICE_FIELD_ID = 3;
        public const int RECEIVEDTIMESTAMP_FIELD_ID = 4;
        public const int MESSAGESEQUENCENUMBER_FIELD_ID = 5;
        public const int REPEAT_FIELD_ID = 6;
        public const int MMSI_FIELD_ID = 7;

        public SimpleAisMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public Types.Kind EntityType
        {
            get
            {
                return GetEnum<Types.Kind>( ENTITYTYPE_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid AisDevice
        {
            get
            {
                return GetGuid( AISDEVICE_FIELD_ID );
            }
        }
        public DateTime ReceivedTimestamp
        {
            get
            {
                return new DateTime( GetInt64( RECEIVEDTIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public long MessageSequenceNumber
        {
            get
            {
                return GetInt64( MESSAGESEQUENCENUMBER_FIELD_ID );
            }
        }
        public int Repeat
        {
            get
            {
                return GetInt32( REPEAT_FIELD_ID );
            }
        }
        public Guid Mmsi
        {
            get
            {
                return GetGuid( MMSI_FIELD_ID );
            }
        }
    }

    public class SimpleAidToNavigationReportMessageDataReader : SimpleAisMessageDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  atnrm.[Id], \r\n" +
            "  atnrm.[EntityType], \r\n" +
            "  atnrm.[RowVersion], \r\n" +
            "  atnrm.[AisDevice], \r\n" +
            "  atnrm.[ReceivedTimestamp], \r\n" +
            "  atnrm.[MessageSequenceNumber], \r\n" +
            "  atnrm.[Repeat], \r\n" +
            "  atnrm.[Mmsi], \r\n" +
            "  atnrm.[NavigationalAidType], \r\n" +
            "  atnrm.[Name], \r\n" +
            "  atnrm.[PositionAccuracy], \r\n" +
            "  atnrm.[Longitude], \r\n" +
            "  atnrm.[Latitude], \r\n" +
            "  atnrm.[DimensionToBow], \r\n" +
            "  atnrm.[DimensionToStern], \r\n" +
            "  atnrm.[DimensionToPort], \r\n" +
            "  atnrm.[DimensionToStarboard], \r\n" +
            "  atnrm.[PositionFixType], \r\n" +
            "  atnrm.[Timestamp], \r\n" +
            "  atnrm.[OffPosition], \r\n" +
            "  atnrm.[RegionalReserved], \r\n" +
            "  atnrm.[Raim], \r\n" +
            "  atnrm.[VirtualAid], \r\n" +
            "  atnrm.[Assigned], \r\n" +
            "  atnrm.[Spare], \r\n" +
            "  atnrm.[NameExtension] \r\n" +
            "FROM [AidToNavigationReportMessageView] atnrm \r\n";

        public new const string BaseViewName = "AidToNavigationReportMessageView";
        public new const string ViewAliasName = "atnrm";

        public const int NAVIGATIONALAIDTYPE_FIELD_ID = 7;
        public const int NAME_FIELD_ID = 8;
        public const int POSITIONACCURACY_FIELD_ID = 9;
        public const int LONGITUDE_FIELD_ID = 10;
        public const int LATITUDE_FIELD_ID = 11;
        public const int DIMENSIONTOBOW_FIELD_ID = 12;
        public const int DIMENSIONTOSTERN_FIELD_ID = 13;
        public const int DIMENSIONTOPORT_FIELD_ID = 14;
        public const int DIMENSIONTOSTARBOARD_FIELD_ID = 15;
        public const int POSITIONFIXTYPE_FIELD_ID = 16;
        public const int TIMESTAMP_FIELD_ID = 17;
        public const int OFFPOSITION_FIELD_ID = 18;
        public const int REGIONALRESERVED_FIELD_ID = 19;
        public const int RAIM_FIELD_ID = 20;
        public const int VIRTUALAID_FIELD_ID = 21;
        public const int ASSIGNED_FIELD_ID = 22;
        public const int SPARE_FIELD_ID = 23;
        public const int NAMEEXTENSION_FIELD_ID = 24;

        public SimpleAidToNavigationReportMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Types.NavigationalAidType NavigationalAidType
        {
            get
            {
                return GetEnum<Types.NavigationalAidType>( NAVIGATIONALAIDTYPE_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
        public Types.PositionAccuracy PositionAccuracy
        {
            get
            {
                return GetEnum<Types.PositionAccuracy>( POSITIONACCURACY_FIELD_ID );
            }
        }
        public double Longitude
        {
            get
            {
                return GetDouble( LONGITUDE_FIELD_ID );
            }
        }
        public double Latitude
        {
            get
            {
                return GetDouble( LATITUDE_FIELD_ID );
            }
        }
        public int DimensionToBow
        {
            get
            {
                return GetInt32( DIMENSIONTOBOW_FIELD_ID );
            }
        }
        public int DimensionToStern
        {
            get
            {
                return GetInt32( DIMENSIONTOSTERN_FIELD_ID );
            }
        }
        public int DimensionToPort
        {
            get
            {
                return GetInt32( DIMENSIONTOPORT_FIELD_ID );
            }
        }
        public int DimensionToStarboard
        {
            get
            {
                return GetInt32( DIMENSIONTOSTARBOARD_FIELD_ID );
            }
        }
        public Types.PositionFixType PositionFixType
        {
            get
            {
                return GetEnum<Types.PositionFixType>( POSITIONFIXTYPE_FIELD_ID );
            }
        }
        public int Timestamp
        {
            get
            {
                return GetInt32( TIMESTAMP_FIELD_ID );
            }
        }
        public bool OffPosition
        {
            get
            {
                return GetBoolean( OFFPOSITION_FIELD_ID );
            }
        }
        public int RegionalReserved
        {
            get
            {
                return GetInt32( REGIONALRESERVED_FIELD_ID );
            }
        }
        public Types.Raim Raim
        {
            get
            {
                return GetEnum<Types.Raim>( RAIM_FIELD_ID );
            }
        }
        public bool VirtualAid
        {
            get
            {
                return GetBoolean( VIRTUALAID_FIELD_ID );
            }
        }
        public bool Assigned
        {
            get
            {
                return GetBoolean( ASSIGNED_FIELD_ID );
            }
        }
        public int Spare
        {
            get
            {
                return GetInt32( SPARE_FIELD_ID );
            }
        }
        public string NameExtension
        {
            get
            {
                return GetString( NAMEEXTENSION_FIELD_ID );
            }
        }
    }

    public class SimpleAisAddressedSafetyRelatedMessageDataReader : SimpleAisMessageDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  aasrm.[Id], \r\n" +
            "  aasrm.[EntityType], \r\n" +
            "  aasrm.[RowVersion], \r\n" +
            "  aasrm.[AisDevice], \r\n" +
            "  aasrm.[ReceivedTimestamp], \r\n" +
            "  aasrm.[MessageSequenceNumber], \r\n" +
            "  aasrm.[Repeat], \r\n" +
            "  aasrm.[Mmsi], \r\n" +
            "  aasrm.[SequenceNumber], \r\n" +
            "  aasrm.[DestinationMmsi], \r\n" +
            "  aasrm.[RetransmitFlag], \r\n" +
            "  aasrm.[Spare], \r\n" +
            "  aasrm.[Text] \r\n" +
            "FROM [AisAddressedSafetyRelatedMessageView] aasrm \r\n";

        public new const string BaseViewName = "AisAddressedSafetyRelatedMessageView";
        public new const string ViewAliasName = "aasrm";

        public const int SEQUENCENUMBER_FIELD_ID = 7;
        public const int DESTINATIONMMSI_FIELD_ID = 8;
        public const int RETRANSMITFLAG_FIELD_ID = 9;
        public const int SPARE_FIELD_ID = 10;
        public const int TEXT_FIELD_ID = 11;

        public SimpleAisAddressedSafetyRelatedMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public int SequenceNumber
        {
            get
            {
                return GetInt32( SEQUENCENUMBER_FIELD_ID );
            }
        }
        public Guid DestinationMmsi
        {
            get
            {
                return GetGuid( DESTINATIONMMSI_FIELD_ID );
            }
        }
        public bool RetransmitFlag
        {
            get
            {
                return GetBoolean( RETRANSMITFLAG_FIELD_ID );
            }
        }
        public int Spare
        {
            get
            {
                return GetInt32( SPARE_FIELD_ID );
            }
        }
        public string Text
        {
            get
            {
                return GetString( TEXT_FIELD_ID );
            }
        }
    }

    public class SimpleAisBaseStationReportMessageDataReader : SimpleAisMessageDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  absrm.[Id], \r\n" +
            "  absrm.[EntityType], \r\n" +
            "  absrm.[RowVersion], \r\n" +
            "  absrm.[AisDevice], \r\n" +
            "  absrm.[ReceivedTimestamp], \r\n" +
            "  absrm.[MessageSequenceNumber], \r\n" +
            "  absrm.[Repeat], \r\n" +
            "  absrm.[Mmsi], \r\n" +
            "  absrm.[Timestamp], \r\n" +
            "  absrm.[PositionAccuracy], \r\n" +
            "  absrm.[Longitude], \r\n" +
            "  absrm.[Latitude], \r\n" +
            "  absrm.[PositionFixType], \r\n" +
            "  absrm.[Spare], \r\n" +
            "  absrm.[Raim], \r\n" +
            "  absrm.[RadioStatus] \r\n" +
            "FROM [AisBaseStationReportMessageView] absrm \r\n";

        public new const string BaseViewName = "AisBaseStationReportMessageView";
        public new const string ViewAliasName = "absrm";

        public const int TIMESTAMP_FIELD_ID = 7;
        public const int POSITIONACCURACY_FIELD_ID = 8;
        public const int LONGITUDE_FIELD_ID = 9;
        public const int LATITUDE_FIELD_ID = 10;
        public const int POSITIONFIXTYPE_FIELD_ID = 11;
        public const int SPARE_FIELD_ID = 12;
        public const int RAIM_FIELD_ID = 13;
        public const int RADIOSTATUS_FIELD_ID = 14;

        public SimpleAisBaseStationReportMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Types.PositionAccuracy PositionAccuracy
        {
            get
            {
                return GetEnum<Types.PositionAccuracy>( POSITIONACCURACY_FIELD_ID );
            }
        }
        public double Longitude
        {
            get
            {
                return GetDouble( LONGITUDE_FIELD_ID );
            }
        }
        public double Latitude
        {
            get
            {
                return GetDouble( LATITUDE_FIELD_ID );
            }
        }
        public Types.PositionFixType PositionFixType
        {
            get
            {
                return GetEnum<Types.PositionFixType>( POSITIONFIXTYPE_FIELD_ID );
            }
        }
        public int Spare
        {
            get
            {
                return GetInt32( SPARE_FIELD_ID );
            }
        }
        public Types.Raim Raim
        {
            get
            {
                return GetEnum<Types.Raim>( RAIM_FIELD_ID );
            }
        }
        public int RadioStatus
        {
            get
            {
                return GetInt32( RADIOSTATUS_FIELD_ID );
            }
        }
    }

    public class SimpleAisBinaryAcknowledgeMessageDataReader : SimpleAisMessageDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  abac.[Id], \r\n" +
            "  abac.[EntityType], \r\n" +
            "  abac.[RowVersion], \r\n" +
            "  abac.[AisDevice], \r\n" +
            "  abac.[ReceivedTimestamp], \r\n" +
            "  abac.[MessageSequenceNumber], \r\n" +
            "  abac.[Repeat], \r\n" +
            "  abac.[Mmsi], \r\n" +
            "  abac.[Spare], \r\n" +
            "  abac.[SequenceNumber1], \r\n" +
            "  abac.[Mmsi1], \r\n" +
            "  abac.[SequenceNumber2], \r\n" +
            "  abac.[Mmsi2], \r\n" +
            "  abac.[SequenceNumber3], \r\n" +
            "  abac.[Mmsi3], \r\n" +
            "  abac.[SequenceNumber4], \r\n" +
            "  abac.[Mmsi4] \r\n" +
            "FROM [AisBinaryAcknowledgeMessageView] abac \r\n";

        public new const string BaseViewName = "AisBinaryAcknowledgeMessageView";
        public new const string ViewAliasName = "abac";

        public const int SPARE_FIELD_ID = 7;
        public const int SEQUENCENUMBER1_FIELD_ID = 8;
        public const int MMSI1_FIELD_ID = 9;
        public const int SEQUENCENUMBER2_FIELD_ID = 10;
        public const int MMSI2_FIELD_ID = 11;
        public const int SEQUENCENUMBER3_FIELD_ID = 12;
        public const int MMSI3_FIELD_ID = 13;
        public const int SEQUENCENUMBER4_FIELD_ID = 14;
        public const int MMSI4_FIELD_ID = 15;

        public SimpleAisBinaryAcknowledgeMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public int Spare
        {
            get
            {
                return GetInt32( SPARE_FIELD_ID );
            }
        }
        public int SequenceNumber1
        {
            get
            {
                return GetInt32( SEQUENCENUMBER1_FIELD_ID );
            }
        }
        public Guid Mmsi1
        {
            get
            {
                return GetGuid( MMSI1_FIELD_ID );
            }
        }
        public int? SequenceNumber2
        {
            get
            {
                return GetNullableInt32( SEQUENCENUMBER2_FIELD_ID );
            }
        }
        public Guid? Mmsi2
        {
            get
            {
                return GetNullableGuid( MMSI2_FIELD_ID );
            }
        }
        public int? SequenceNumber3
        {
            get
            {
                return GetNullableInt32( SEQUENCENUMBER3_FIELD_ID );
            }
        }
        public Guid? Mmsi3
        {
            get
            {
                return GetNullableGuid( MMSI3_FIELD_ID );
            }
        }
        public int? SequenceNumber4
        {
            get
            {
                return GetNullableInt32( SEQUENCENUMBER4_FIELD_ID );
            }
        }
        public Guid? Mmsi4
        {
            get
            {
                return GetNullableGuid( MMSI4_FIELD_ID );
            }
        }
    }

    public class SimpleAisBinaryAddressedMessageDataReader : SimpleAisMessageDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  abam.[Id], \r\n" +
            "  abam.[EntityType], \r\n" +
            "  abam.[RowVersion], \r\n" +
            "  abam.[AisDevice], \r\n" +
            "  abam.[ReceivedTimestamp], \r\n" +
            "  abam.[MessageSequenceNumber], \r\n" +
            "  abam.[Repeat], \r\n" +
            "  abam.[Mmsi], \r\n" +
            "  abam.[SequenceNumber], \r\n" +
            "  abam.[DestinationMmsi], \r\n" +
            "  abam.[RetransmitFlag], \r\n" +
            "  abam.[Spare], \r\n" +
            "  abam.[DesignatedAreaCode], \r\n" +
            "  abam.[FunctionalId], \r\n" +
            "  abam.[Data] \r\n" +
            "FROM [AisBinaryAddressedMessageView] abam \r\n";

        public new const string BaseViewName = "AisBinaryAddressedMessageView";
        public new const string ViewAliasName = "abam";

        public const int SEQUENCENUMBER_FIELD_ID = 7;
        public const int DESTINATIONMMSI_FIELD_ID = 8;
        public const int RETRANSMITFLAG_FIELD_ID = 9;
        public const int SPARE_FIELD_ID = 10;
        public const int DESIGNATEDAREACODE_FIELD_ID = 11;
        public const int FUNCTIONALID_FIELD_ID = 12;
        public const int DATA_FIELD_ID = 13;

        public SimpleAisBinaryAddressedMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public int SequenceNumber
        {
            get
            {
                return GetInt32( SEQUENCENUMBER_FIELD_ID );
            }
        }
        public Guid DestinationMmsi
        {
            get
            {
                return GetGuid( DESTINATIONMMSI_FIELD_ID );
            }
        }
        public bool RetransmitFlag
        {
            get
            {
                return GetBoolean( RETRANSMITFLAG_FIELD_ID );
            }
        }
        public int Spare
        {
            get
            {
                return GetInt32( SPARE_FIELD_ID );
            }
        }
        public int DesignatedAreaCode
        {
            get
            {
                return GetInt32( DESIGNATEDAREACODE_FIELD_ID );
            }
        }
        public int FunctionalId
        {
            get
            {
                return GetInt32( FUNCTIONALID_FIELD_ID );
            }
        }
        public string Data
        {
            get
            {
                return GetString( DATA_FIELD_ID );
            }
        }
    }

    public class SimpleAisBinaryBroadcastMessageDataReader : SimpleAisMessageDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  abbm.[Id], \r\n" +
            "  abbm.[EntityType], \r\n" +
            "  abbm.[RowVersion], \r\n" +
            "  abbm.[AisDevice], \r\n" +
            "  abbm.[ReceivedTimestamp], \r\n" +
            "  abbm.[MessageSequenceNumber], \r\n" +
            "  abbm.[Repeat], \r\n" +
            "  abbm.[Mmsi], \r\n" +
            "  abbm.[Spare], \r\n" +
            "  abbm.[DesignatedAreaCode], \r\n" +
            "  abbm.[FunctionalId], \r\n" +
            "  abbm.[Data] \r\n" +
            "FROM [AisBinaryBroadcastMessageView] abbm \r\n";

        public new const string BaseViewName = "AisBinaryBroadcastMessageView";
        public new const string ViewAliasName = "abbm";

        public const int SPARE_FIELD_ID = 7;
        public const int DESIGNATEDAREACODE_FIELD_ID = 8;
        public const int FUNCTIONALID_FIELD_ID = 9;
        public const int DATA_FIELD_ID = 10;

        public SimpleAisBinaryBroadcastMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public int Spare
        {
            get
            {
                return GetInt32( SPARE_FIELD_ID );
            }
        }
        public int DesignatedAreaCode
        {
            get
            {
                return GetInt32( DESIGNATEDAREACODE_FIELD_ID );
            }
        }
        public int FunctionalId
        {
            get
            {
                return GetInt32( FUNCTIONALID_FIELD_ID );
            }
        }
        public string Data
        {
            get
            {
                return GetString( DATA_FIELD_ID );
            }
        }
    }

    public class SimpleAisDataLinkManagementMessageDataReader : SimpleAisMessageDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  adlmm.[Id], \r\n" +
            "  adlmm.[EntityType], \r\n" +
            "  adlmm.[RowVersion], \r\n" +
            "  adlmm.[AisDevice], \r\n" +
            "  adlmm.[ReceivedTimestamp], \r\n" +
            "  adlmm.[MessageSequenceNumber], \r\n" +
            "  adlmm.[Repeat], \r\n" +
            "  adlmm.[Mmsi], \r\n" +
            "  adlmm.[Spare], \r\n" +
            "  adlmm.[Offset1], \r\n" +
            "  adlmm.[ReservedSlots1], \r\n" +
            "  adlmm.[Timeout1], \r\n" +
            "  adlmm.[Increment1], \r\n" +
            "  adlmm.[Offset2], \r\n" +
            "  adlmm.[ReservedSlots2], \r\n" +
            "  adlmm.[Timeout2], \r\n" +
            "  adlmm.[Increment2], \r\n" +
            "  adlmm.[Offset3], \r\n" +
            "  adlmm.[ReservedSlots3], \r\n" +
            "  adlmm.[Timeout3], \r\n" +
            "  adlmm.[Increment3], \r\n" +
            "  adlmm.[Offset4], \r\n" +
            "  adlmm.[ReservedSlots4], \r\n" +
            "  adlmm.[Timeout4], \r\n" +
            "  adlmm.[Increment4] \r\n" +
            "FROM [AisDataLinkManagementMessageView] adlmm \r\n";

        public new const string BaseViewName = "AisDataLinkManagementMessageView";
        public new const string ViewAliasName = "adlmm";

        public const int SPARE_FIELD_ID = 7;
        public const int OFFSET1_FIELD_ID = 8;
        public const int RESERVEDSLOTS1_FIELD_ID = 9;
        public const int TIMEOUT1_FIELD_ID = 10;
        public const int INCREMENT1_FIELD_ID = 11;
        public const int OFFSET2_FIELD_ID = 12;
        public const int RESERVEDSLOTS2_FIELD_ID = 13;
        public const int TIMEOUT2_FIELD_ID = 14;
        public const int INCREMENT2_FIELD_ID = 15;
        public const int OFFSET3_FIELD_ID = 16;
        public const int RESERVEDSLOTS3_FIELD_ID = 17;
        public const int TIMEOUT3_FIELD_ID = 18;
        public const int INCREMENT3_FIELD_ID = 19;
        public const int OFFSET4_FIELD_ID = 20;
        public const int RESERVEDSLOTS4_FIELD_ID = 21;
        public const int TIMEOUT4_FIELD_ID = 22;
        public const int INCREMENT4_FIELD_ID = 23;

        public SimpleAisDataLinkManagementMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public int Spare
        {
            get
            {
                return GetInt32( SPARE_FIELD_ID );
            }
        }
        public int Offset1
        {
            get
            {
                return GetInt32( OFFSET1_FIELD_ID );
            }
        }
        public int ReservedSlots1
        {
            get
            {
                return GetInt32( RESERVEDSLOTS1_FIELD_ID );
            }
        }
        public int Timeout1
        {
            get
            {
                return GetInt32( TIMEOUT1_FIELD_ID );
            }
        }
        public int Increment1
        {
            get
            {
                return GetInt32( INCREMENT1_FIELD_ID );
            }
        }
        public int? Offset2
        {
            get
            {
                return GetNullableInt32( OFFSET2_FIELD_ID );
            }
        }
        public int? ReservedSlots2
        {
            get
            {
                return GetNullableInt32( RESERVEDSLOTS2_FIELD_ID );
            }
        }
        public int? Timeout2
        {
            get
            {
                return GetNullableInt32( TIMEOUT2_FIELD_ID );
            }
        }
        public int? Increment2
        {
            get
            {
                return GetNullableInt32( INCREMENT2_FIELD_ID );
            }
        }
        public int? Offset3
        {
            get
            {
                return GetNullableInt32( OFFSET3_FIELD_ID );
            }
        }
        public int? ReservedSlots3
        {
            get
            {
                return GetNullableInt32( RESERVEDSLOTS3_FIELD_ID );
            }
        }
        public int? Timeout3
        {
            get
            {
                return GetNullableInt32( TIMEOUT3_FIELD_ID );
            }
        }
        public int? Increment3
        {
            get
            {
                return GetNullableInt32( INCREMENT3_FIELD_ID );
            }
        }
        public int? Offset4
        {
            get
            {
                return GetNullableInt32( OFFSET4_FIELD_ID );
            }
        }
        public int? ReservedSlots4
        {
            get
            {
                return GetNullableInt32( RESERVEDSLOTS4_FIELD_ID );
            }
        }
        public int? Timeout4
        {
            get
            {
                return GetNullableInt32( TIMEOUT4_FIELD_ID );
            }
        }
        public int? Increment4
        {
            get
            {
                return GetNullableInt32( INCREMENT4_FIELD_ID );
            }
        }
    }

    public class SimpleAisExtendedClassBCsPositionReportMessageDataReader : SimpleAisMessageDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  aecbprm.[Id], \r\n" +
            "  aecbprm.[EntityType], \r\n" +
            "  aecbprm.[RowVersion], \r\n" +
            "  aecbprm.[AisDevice], \r\n" +
            "  aecbprm.[ReceivedTimestamp], \r\n" +
            "  aecbprm.[MessageSequenceNumber], \r\n" +
            "  aecbprm.[Repeat], \r\n" +
            "  aecbprm.[Mmsi], \r\n" +
            "  aecbprm.[Reserved], \r\n" +
            "  aecbprm.[SpeedOverGround], \r\n" +
            "  aecbprm.[PositionAccuracy], \r\n" +
            "  aecbprm.[Longitude], \r\n" +
            "  aecbprm.[Latitude], \r\n" +
            "  aecbprm.[CourseOverGround], \r\n" +
            "  aecbprm.[TrueHeading], \r\n" +
            "  aecbprm.[Timestamp], \r\n" +
            "  aecbprm.[RegionalReserved], \r\n" +
            "  aecbprm.[Name], \r\n" +
            "  aecbprm.[ShipType], \r\n" +
            "  aecbprm.[DimensionToBow], \r\n" +
            "  aecbprm.[DimensionToStern], \r\n" +
            "  aecbprm.[DimensionToPort], \r\n" +
            "  aecbprm.[DimensionToStarboard], \r\n" +
            "  aecbprm.[PositionFixType], \r\n" +
            "  aecbprm.[Raim], \r\n" +
            "  aecbprm.[DataTerminalReady], \r\n" +
            "  aecbprm.[Assigned], \r\n" +
            "  aecbprm.[Spare] \r\n" +
            "FROM [AisExtendedClassBCsPositionReportMessageView] aecbprm \r\n";

        public new const string BaseViewName = "AisExtendedClassBCsPositionReportMessageView";
        public new const string ViewAliasName = "aecbprm";

        public const int RESERVED_FIELD_ID = 7;
        public const int SPEEDOVERGROUND_FIELD_ID = 8;
        public const int POSITIONACCURACY_FIELD_ID = 9;
        public const int LONGITUDE_FIELD_ID = 10;
        public const int LATITUDE_FIELD_ID = 11;
        public const int COURSEOVERGROUND_FIELD_ID = 12;
        public const int TRUEHEADING_FIELD_ID = 13;
        public const int TIMESTAMP_FIELD_ID = 14;
        public const int REGIONALRESERVED_FIELD_ID = 15;
        public const int NAME_FIELD_ID = 16;
        public const int SHIPTYPE_FIELD_ID = 17;
        public const int DIMENSIONTOBOW_FIELD_ID = 18;
        public const int DIMENSIONTOSTERN_FIELD_ID = 19;
        public const int DIMENSIONTOPORT_FIELD_ID = 20;
        public const int DIMENSIONTOSTARBOARD_FIELD_ID = 21;
        public const int POSITIONFIXTYPE_FIELD_ID = 22;
        public const int RAIM_FIELD_ID = 23;
        public const int DATATERMINALREADY_FIELD_ID = 24;
        public const int ASSIGNED_FIELD_ID = 25;
        public const int SPARE_FIELD_ID = 26;

        public SimpleAisExtendedClassBCsPositionReportMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public int Reserved
        {
            get
            {
                return GetInt32( RESERVED_FIELD_ID );
            }
        }
        public double SpeedOverGround
        {
            get
            {
                return GetDouble( SPEEDOVERGROUND_FIELD_ID );
            }
        }
        public Types.PositionAccuracy PositionAccuracy
        {
            get
            {
                return GetEnum<Types.PositionAccuracy>( POSITIONACCURACY_FIELD_ID );
            }
        }
        public double Longitude
        {
            get
            {
                return GetDouble( LONGITUDE_FIELD_ID );
            }
        }
        public double Latitude
        {
            get
            {
                return GetDouble( LATITUDE_FIELD_ID );
            }
        }
        public double CourseOverGround
        {
            get
            {
                return GetDouble( COURSEOVERGROUND_FIELD_ID );
            }
        }
        public int? TrueHeading
        {
            get
            {
                return GetNullableInt32( TRUEHEADING_FIELD_ID );
            }
        }
        public int Timestamp
        {
            get
            {
                return GetInt32( TIMESTAMP_FIELD_ID );
            }
        }
        public int RegionalReserved
        {
            get
            {
                return GetInt32( REGIONALRESERVED_FIELD_ID );
            }
        }
        public Guid Name
        {
            get
            {
                return GetGuid( NAME_FIELD_ID );
            }
        }
        public Types.ShipType ShipType
        {
            get
            {
                return GetEnum<Types.ShipType>( SHIPTYPE_FIELD_ID );
            }
        }
        public int DimensionToBow
        {
            get
            {
                return GetInt32( DIMENSIONTOBOW_FIELD_ID );
            }
        }
        public int DimensionToStern
        {
            get
            {
                return GetInt32( DIMENSIONTOSTERN_FIELD_ID );
            }
        }
        public int DimensionToPort
        {
            get
            {
                return GetInt32( DIMENSIONTOPORT_FIELD_ID );
            }
        }
        public int DimensionToStarboard
        {
            get
            {
                return GetInt32( DIMENSIONTOSTARBOARD_FIELD_ID );
            }
        }
        public Types.PositionFixType PositionFixType
        {
            get
            {
                return GetEnum<Types.PositionFixType>( POSITIONFIXTYPE_FIELD_ID );
            }
        }
        public Types.Raim Raim
        {
            get
            {
                return GetEnum<Types.Raim>( RAIM_FIELD_ID );
            }
        }
        public bool DataTerminalReady
        {
            get
            {
                return GetBoolean( DATATERMINALREADY_FIELD_ID );
            }
        }
        public bool Assigned
        {
            get
            {
                return GetBoolean( ASSIGNED_FIELD_ID );
            }
        }
        public int Spare
        {
            get
            {
                return GetInt32( SPARE_FIELD_ID );
            }
        }
    }

    public class SimpleAisInterrogationMessageDataReader : SimpleAisMessageDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  aim.[Id], \r\n" +
            "  aim.[EntityType], \r\n" +
            "  aim.[RowVersion], \r\n" +
            "  aim.[AisDevice], \r\n" +
            "  aim.[ReceivedTimestamp], \r\n" +
            "  aim.[MessageSequenceNumber], \r\n" +
            "  aim.[Repeat], \r\n" +
            "  aim.[Mmsi], \r\n" +
            "  aim.[InterrogatedMmsi], \r\n" +
            "  aim.[FirstMessageType], \r\n" +
            "  aim.[FirstSlotOffset], \r\n" +
            "  aim.[SecondMessageType], \r\n" +
            "  aim.[SecondSlotOffset], \r\n" +
            "  aim.[SecondStationInterrogationMmsi], \r\n" +
            "  aim.[SecondStationFirstMessageType], \r\n" +
            "  aim.[SecondStationFirstSlotOffset] \r\n" +
            "FROM [AisInterrogationMessageView] aim \r\n";

        public new const string BaseViewName = "AisInterrogationMessageView";
        public new const string ViewAliasName = "aim";

        public const int INTERROGATEDMMSI_FIELD_ID = 7;
        public const int FIRSTMESSAGETYPE_FIELD_ID = 8;
        public const int FIRSTSLOTOFFSET_FIELD_ID = 9;
        public const int SECONDMESSAGETYPE_FIELD_ID = 10;
        public const int SECONDSLOTOFFSET_FIELD_ID = 11;
        public const int SECONDSTATIONINTERROGATIONMMSI_FIELD_ID = 12;
        public const int SECONDSTATIONFIRSTMESSAGETYPE_FIELD_ID = 13;
        public const int SECONDSTATIONFIRSTSLOTOFFSET_FIELD_ID = 14;

        public SimpleAisInterrogationMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid InterrogatedMmsi
        {
            get
            {
                return GetGuid( INTERROGATEDMMSI_FIELD_ID );
            }
        }
        public Types.AisMessageType FirstMessageType
        {
            get
            {
                return GetEnum<Types.AisMessageType>( FIRSTMESSAGETYPE_FIELD_ID );
            }
        }
        public int FirstSlotOffset
        {
            get
            {
                return GetInt32( FIRSTSLOTOFFSET_FIELD_ID );
            }
        }
        public Types.AisMessageType? SecondMessageType
        {
            get
            {
                return GetNullableEnum<Types.AisMessageType>( SECONDMESSAGETYPE_FIELD_ID );
            }
        }
        public int? SecondSlotOffset
        {
            get
            {
                return GetNullableInt32( SECONDSLOTOFFSET_FIELD_ID );
            }
        }
        public Guid? SecondStationInterrogationMmsi
        {
            get
            {
                return GetNullableGuid( SECONDSTATIONINTERROGATIONMMSI_FIELD_ID );
            }
        }
        public Types.AisMessageType? SecondStationFirstMessageType
        {
            get
            {
                return GetNullableEnum<Types.AisMessageType>( SECONDSTATIONFIRSTMESSAGETYPE_FIELD_ID );
            }
        }
        public int? SecondStationFirstSlotOffset
        {
            get
            {
                return GetNullableInt32( SECONDSTATIONFIRSTSLOTOFFSET_FIELD_ID );
            }
        }
    }

    public class SimpleAisPositionReportClassAMessageBaseDataReader : SimpleAisMessageDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  aprcab.[Id], \r\n" +
            "  aprcab.[EntityType], \r\n" +
            "  aprcab.[RowVersion], \r\n" +
            "  aprcab.[AisDevice], \r\n" +
            "  aprcab.[ReceivedTimestamp], \r\n" +
            "  aprcab.[MessageSequenceNumber], \r\n" +
            "  aprcab.[Repeat], \r\n" +
            "  aprcab.[Mmsi], \r\n" +
            "  aprcab.[NavigationStatus], \r\n" +
            "  aprcab.[RateOfTurn], \r\n" +
            "  aprcab.[SpeedOverGround], \r\n" +
            "  aprcab.[PositionAccuracy], \r\n" +
            "  aprcab.[Longitude], \r\n" +
            "  aprcab.[Latitude], \r\n" +
            "  aprcab.[CourseOverGround], \r\n" +
            "  aprcab.[TrueHeading], \r\n" +
            "  aprcab.[Timestamp], \r\n" +
            "  aprcab.[ManeuverIndicator], \r\n" +
            "  aprcab.[Spare], \r\n" +
            "  aprcab.[Raim], \r\n" +
            "  aprcab.[RadioStatus] \r\n" +
            "FROM [AisPositionReportClassAMessageBaseView] aprcab \r\n";

        public new const string BaseViewName = "AisPositionReportClassAMessageBaseView";
        public new const string ViewAliasName = "aprcab";

        public const int NAVIGATIONSTATUS_FIELD_ID = 7;
        public const int RATEOFTURN_FIELD_ID = 8;
        public const int SPEEDOVERGROUND_FIELD_ID = 9;
        public const int POSITIONACCURACY_FIELD_ID = 10;
        public const int LONGITUDE_FIELD_ID = 11;
        public const int LATITUDE_FIELD_ID = 12;
        public const int COURSEOVERGROUND_FIELD_ID = 13;
        public const int TRUEHEADING_FIELD_ID = 14;
        public const int TIMESTAMP_FIELD_ID = 15;
        public const int MANEUVERINDICATOR_FIELD_ID = 16;
        public const int SPARE_FIELD_ID = 17;
        public const int RAIM_FIELD_ID = 18;
        public const int RADIOSTATUS_FIELD_ID = 19;

        public SimpleAisPositionReportClassAMessageBaseDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Types.NavigationStatus NavigationStatus
        {
            get
            {
                return GetEnum<Types.NavigationStatus>( NAVIGATIONSTATUS_FIELD_ID );
            }
        }
        public int? RateOfTurn
        {
            get
            {
                return GetNullableInt32( RATEOFTURN_FIELD_ID );
            }
        }
        public double SpeedOverGround
        {
            get
            {
                return GetDouble( SPEEDOVERGROUND_FIELD_ID );
            }
        }
        public Types.PositionAccuracy PositionAccuracy
        {
            get
            {
                return GetEnum<Types.PositionAccuracy>( POSITIONACCURACY_FIELD_ID );
            }
        }
        public double Longitude
        {
            get
            {
                return GetDouble( LONGITUDE_FIELD_ID );
            }
        }
        public double Latitude
        {
            get
            {
                return GetDouble( LATITUDE_FIELD_ID );
            }
        }
        public double CourseOverGround
        {
            get
            {
                return GetDouble( COURSEOVERGROUND_FIELD_ID );
            }
        }
        public int? TrueHeading
        {
            get
            {
                return GetNullableInt32( TRUEHEADING_FIELD_ID );
            }
        }
        public int Timestamp
        {
            get
            {
                return GetInt32( TIMESTAMP_FIELD_ID );
            }
        }
        public Types.ManeuverIndicator ManeuverIndicator
        {
            get
            {
                return GetEnum<Types.ManeuverIndicator>( MANEUVERINDICATOR_FIELD_ID );
            }
        }
        public int Spare
        {
            get
            {
                return GetInt32( SPARE_FIELD_ID );
            }
        }
        public Types.Raim Raim
        {
            get
            {
                return GetEnum<Types.Raim>( RAIM_FIELD_ID );
            }
        }
        public int RadioStatus
        {
            get
            {
                return GetInt32( RADIOSTATUS_FIELD_ID );
            }
        }
    }

    public class SimpleAisPositionReportClassAAssignedScheduleMessageDataReader : SimpleAisPositionReportClassAMessageBaseDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  aprcasm.[Id], \r\n" +
            "  aprcasm.[EntityType], \r\n" +
            "  aprcasm.[RowVersion], \r\n" +
            "  aprcasm.[AisDevice], \r\n" +
            "  aprcasm.[ReceivedTimestamp], \r\n" +
            "  aprcasm.[MessageSequenceNumber], \r\n" +
            "  aprcasm.[Repeat], \r\n" +
            "  aprcasm.[Mmsi], \r\n" +
            "  aprcasm.[NavigationStatus], \r\n" +
            "  aprcasm.[RateOfTurn], \r\n" +
            "  aprcasm.[SpeedOverGround], \r\n" +
            "  aprcasm.[PositionAccuracy], \r\n" +
            "  aprcasm.[Longitude], \r\n" +
            "  aprcasm.[Latitude], \r\n" +
            "  aprcasm.[CourseOverGround], \r\n" +
            "  aprcasm.[TrueHeading], \r\n" +
            "  aprcasm.[Timestamp], \r\n" +
            "  aprcasm.[ManeuverIndicator], \r\n" +
            "  aprcasm.[Spare], \r\n" +
            "  aprcasm.[Raim], \r\n" +
            "  aprcasm.[RadioStatus] \r\n" +
            "FROM [AisPositionReportClassAAssignedScheduleMessageView] aprcasm \r\n";

        public new const string BaseViewName = "AisPositionReportClassAAssignedScheduleMessageView";
        public new const string ViewAliasName = "aprcasm";

        public SimpleAisPositionReportClassAAssignedScheduleMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleAisPositionReportClassAMessageDataReader : SimpleAisPositionReportClassAMessageBaseDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  aprca.[Id], \r\n" +
            "  aprca.[EntityType], \r\n" +
            "  aprca.[RowVersion], \r\n" +
            "  aprca.[AisDevice], \r\n" +
            "  aprca.[ReceivedTimestamp], \r\n" +
            "  aprca.[MessageSequenceNumber], \r\n" +
            "  aprca.[Repeat], \r\n" +
            "  aprca.[Mmsi], \r\n" +
            "  aprca.[NavigationStatus], \r\n" +
            "  aprca.[RateOfTurn], \r\n" +
            "  aprca.[SpeedOverGround], \r\n" +
            "  aprca.[PositionAccuracy], \r\n" +
            "  aprca.[Longitude], \r\n" +
            "  aprca.[Latitude], \r\n" +
            "  aprca.[CourseOverGround], \r\n" +
            "  aprca.[TrueHeading], \r\n" +
            "  aprca.[Timestamp], \r\n" +
            "  aprca.[ManeuverIndicator], \r\n" +
            "  aprca.[Spare], \r\n" +
            "  aprca.[Raim], \r\n" +
            "  aprca.[RadioStatus] \r\n" +
            "FROM [AisPositionReportClassAMessageView] aprca \r\n";

        public new const string BaseViewName = "AisPositionReportClassAMessageView";
        public new const string ViewAliasName = "aprca";

        public SimpleAisPositionReportClassAMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleAisPositionReportClassAResponseToInterrogationMessageDataReader : SimpleAisPositionReportClassAMessageBaseDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  aprcatim.[Id], \r\n" +
            "  aprcatim.[EntityType], \r\n" +
            "  aprcatim.[RowVersion], \r\n" +
            "  aprcatim.[AisDevice], \r\n" +
            "  aprcatim.[ReceivedTimestamp], \r\n" +
            "  aprcatim.[MessageSequenceNumber], \r\n" +
            "  aprcatim.[Repeat], \r\n" +
            "  aprcatim.[Mmsi], \r\n" +
            "  aprcatim.[NavigationStatus], \r\n" +
            "  aprcatim.[RateOfTurn], \r\n" +
            "  aprcatim.[SpeedOverGround], \r\n" +
            "  aprcatim.[PositionAccuracy], \r\n" +
            "  aprcatim.[Longitude], \r\n" +
            "  aprcatim.[Latitude], \r\n" +
            "  aprcatim.[CourseOverGround], \r\n" +
            "  aprcatim.[TrueHeading], \r\n" +
            "  aprcatim.[Timestamp], \r\n" +
            "  aprcatim.[ManeuverIndicator], \r\n" +
            "  aprcatim.[Spare], \r\n" +
            "  aprcatim.[Raim], \r\n" +
            "  aprcatim.[RadioStatus] \r\n" +
            "FROM [AisPositionReportClassAResponseToInterrogationMessageView] aprcatim \r\n";

        public new const string BaseViewName = "AisPositionReportClassAResponseToInterrogationMessageView";
        public new const string ViewAliasName = "aprcatim";

        public SimpleAisPositionReportClassAResponseToInterrogationMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleAisPositionReportForLongRangeApplicationsMessageDataReader : SimpleAisMessageDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  aprflram.[Id], \r\n" +
            "  aprflram.[EntityType], \r\n" +
            "  aprflram.[RowVersion], \r\n" +
            "  aprflram.[AisDevice], \r\n" +
            "  aprflram.[ReceivedTimestamp], \r\n" +
            "  aprflram.[MessageSequenceNumber], \r\n" +
            "  aprflram.[Repeat], \r\n" +
            "  aprflram.[Mmsi], \r\n" +
            "  aprflram.[PositionAccuracy], \r\n" +
            "  aprflram.[Raim], \r\n" +
            "  aprflram.[NavigationStatus], \r\n" +
            "  aprflram.[Longitude], \r\n" +
            "  aprflram.[Latitude], \r\n" +
            "  aprflram.[SpeedOverGround], \r\n" +
            "  aprflram.[CourseOverGround], \r\n" +
            "  aprflram.[GnssPositionStatus], \r\n" +
            "  aprflram.[Spare] \r\n" +
            "FROM [AisPositionReportForLongRangeApplicationsMessageView] aprflram \r\n";

        public new const string BaseViewName = "AisPositionReportForLongRangeApplicationsMessageView";
        public new const string ViewAliasName = "aprflram";

        public const int POSITIONACCURACY_FIELD_ID = 7;
        public const int RAIM_FIELD_ID = 8;
        public const int NAVIGATIONSTATUS_FIELD_ID = 9;
        public const int LONGITUDE_FIELD_ID = 10;
        public const int LATITUDE_FIELD_ID = 11;
        public const int SPEEDOVERGROUND_FIELD_ID = 12;
        public const int COURSEOVERGROUND_FIELD_ID = 13;
        public const int GNSSPOSITIONSTATUS_FIELD_ID = 14;
        public const int SPARE_FIELD_ID = 15;

        public SimpleAisPositionReportForLongRangeApplicationsMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Types.PositionAccuracy PositionAccuracy
        {
            get
            {
                return GetEnum<Types.PositionAccuracy>( POSITIONACCURACY_FIELD_ID );
            }
        }
        public Types.Raim Raim
        {
            get
            {
                return GetEnum<Types.Raim>( RAIM_FIELD_ID );
            }
        }
        public Types.NavigationStatus NavigationStatus
        {
            get
            {
                return GetEnum<Types.NavigationStatus>( NAVIGATIONSTATUS_FIELD_ID );
            }
        }
        public double Longitude
        {
            get
            {
                return GetDouble( LONGITUDE_FIELD_ID );
            }
        }
        public double Latitude
        {
            get
            {
                return GetDouble( LATITUDE_FIELD_ID );
            }
        }
        public double SpeedOverGround
        {
            get
            {
                return GetDouble( SPEEDOVERGROUND_FIELD_ID );
            }
        }
        public double CourseOverGround
        {
            get
            {
                return GetDouble( COURSEOVERGROUND_FIELD_ID );
            }
        }
        public Types.GnssPositionStatus GnssPositionStatus
        {
            get
            {
                return GetEnum<Types.GnssPositionStatus>( GNSSPOSITIONSTATUS_FIELD_ID );
            }
        }
        public int Spare
        {
            get
            {
                return GetInt32( SPARE_FIELD_ID );
            }
        }
    }

    public class SimpleAisSafetyRelatedAcknowledgmentMessageDataReader : SimpleAisMessageDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  asram.[Id], \r\n" +
            "  asram.[EntityType], \r\n" +
            "  asram.[RowVersion], \r\n" +
            "  asram.[AisDevice], \r\n" +
            "  asram.[ReceivedTimestamp], \r\n" +
            "  asram.[MessageSequenceNumber], \r\n" +
            "  asram.[Repeat], \r\n" +
            "  asram.[Mmsi], \r\n" +
            "  asram.[Spare], \r\n" +
            "  asram.[SequenceNumber1], \r\n" +
            "  asram.[Mmsi1], \r\n" +
            "  asram.[SequenceNumber2], \r\n" +
            "  asram.[Mmsi2], \r\n" +
            "  asram.[SequenceNumber3], \r\n" +
            "  asram.[Mmsi3], \r\n" +
            "  asram.[SequenceNumber4], \r\n" +
            "  asram.[Mmsi4] \r\n" +
            "FROM [AisSafetyRelatedAcknowledgmentMessageView] asram \r\n";

        public new const string BaseViewName = "AisSafetyRelatedAcknowledgmentMessageView";
        public new const string ViewAliasName = "asram";

        public const int SPARE_FIELD_ID = 7;
        public const int SEQUENCENUMBER1_FIELD_ID = 8;
        public const int MMSI1_FIELD_ID = 9;
        public const int SEQUENCENUMBER2_FIELD_ID = 10;
        public const int MMSI2_FIELD_ID = 11;
        public const int SEQUENCENUMBER3_FIELD_ID = 12;
        public const int MMSI3_FIELD_ID = 13;
        public const int SEQUENCENUMBER4_FIELD_ID = 14;
        public const int MMSI4_FIELD_ID = 15;

        public SimpleAisSafetyRelatedAcknowledgmentMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public int Spare
        {
            get
            {
                return GetInt32( SPARE_FIELD_ID );
            }
        }
        public int SequenceNumber1
        {
            get
            {
                return GetInt32( SEQUENCENUMBER1_FIELD_ID );
            }
        }
        public Guid Mmsi1
        {
            get
            {
                return GetGuid( MMSI1_FIELD_ID );
            }
        }
        public int? SequenceNumber2
        {
            get
            {
                return GetNullableInt32( SEQUENCENUMBER2_FIELD_ID );
            }
        }
        public Guid? Mmsi2
        {
            get
            {
                return GetNullableGuid( MMSI2_FIELD_ID );
            }
        }
        public int? SequenceNumber3
        {
            get
            {
                return GetNullableInt32( SEQUENCENUMBER3_FIELD_ID );
            }
        }
        public Guid? Mmsi3
        {
            get
            {
                return GetNullableGuid( MMSI3_FIELD_ID );
            }
        }
        public int? SequenceNumber4
        {
            get
            {
                return GetNullableInt32( SEQUENCENUMBER4_FIELD_ID );
            }
        }
        public Guid? Mmsi4
        {
            get
            {
                return GetNullableGuid( MMSI4_FIELD_ID );
            }
        }
    }

    public class SimpleAisStandardClassBCsPositionReportMessageDataReader : SimpleAisMessageDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  ascbprm.[Id], \r\n" +
            "  ascbprm.[EntityType], \r\n" +
            "  ascbprm.[RowVersion], \r\n" +
            "  ascbprm.[AisDevice], \r\n" +
            "  ascbprm.[ReceivedTimestamp], \r\n" +
            "  ascbprm.[MessageSequenceNumber], \r\n" +
            "  ascbprm.[Repeat], \r\n" +
            "  ascbprm.[Mmsi], \r\n" +
            "  ascbprm.[Reserved], \r\n" +
            "  ascbprm.[SpeedOverGround], \r\n" +
            "  ascbprm.[PositionAccuracy], \r\n" +
            "  ascbprm.[Longitude], \r\n" +
            "  ascbprm.[Latitude], \r\n" +
            "  ascbprm.[CourseOverGround], \r\n" +
            "  ascbprm.[TrueHeading], \r\n" +
            "  ascbprm.[Timestamp], \r\n" +
            "  ascbprm.[RegionalReserved], \r\n" +
            "  ascbprm.[IsCsUnit], \r\n" +
            "  ascbprm.[HasDisplay], \r\n" +
            "  ascbprm.[HasDscCapability], \r\n" +
            "  ascbprm.[Band], \r\n" +
            "  ascbprm.[CanAcceptMessage22], \r\n" +
            "  ascbprm.[Assigned], \r\n" +
            "  ascbprm.[Raim], \r\n" +
            "  ascbprm.[RadioStatus] \r\n" +
            "FROM [AisStandardClassBCsPositionReportMessageView] ascbprm \r\n";

        public new const string BaseViewName = "AisStandardClassBCsPositionReportMessageView";
        public new const string ViewAliasName = "ascbprm";

        public const int RESERVED_FIELD_ID = 7;
        public const int SPEEDOVERGROUND_FIELD_ID = 8;
        public const int POSITIONACCURACY_FIELD_ID = 9;
        public const int LONGITUDE_FIELD_ID = 10;
        public const int LATITUDE_FIELD_ID = 11;
        public const int COURSEOVERGROUND_FIELD_ID = 12;
        public const int TRUEHEADING_FIELD_ID = 13;
        public const int TIMESTAMP_FIELD_ID = 14;
        public const int REGIONALRESERVED_FIELD_ID = 15;
        public const int ISCSUNIT_FIELD_ID = 16;
        public const int HASDISPLAY_FIELD_ID = 17;
        public const int HASDSCCAPABILITY_FIELD_ID = 18;
        public const int BAND_FIELD_ID = 19;
        public const int CANACCEPTMESSAGE22_FIELD_ID = 20;
        public const int ASSIGNED_FIELD_ID = 21;
        public const int RAIM_FIELD_ID = 22;
        public const int RADIOSTATUS_FIELD_ID = 23;

        public SimpleAisStandardClassBCsPositionReportMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public int Reserved
        {
            get
            {
                return GetInt32( RESERVED_FIELD_ID );
            }
        }
        public double SpeedOverGround
        {
            get
            {
                return GetDouble( SPEEDOVERGROUND_FIELD_ID );
            }
        }
        public Types.PositionAccuracy PositionAccuracy
        {
            get
            {
                return GetEnum<Types.PositionAccuracy>( POSITIONACCURACY_FIELD_ID );
            }
        }
        public double Longitude
        {
            get
            {
                return GetDouble( LONGITUDE_FIELD_ID );
            }
        }
        public double Latitude
        {
            get
            {
                return GetDouble( LATITUDE_FIELD_ID );
            }
        }
        public double CourseOverGround
        {
            get
            {
                return GetDouble( COURSEOVERGROUND_FIELD_ID );
            }
        }
        public int? TrueHeading
        {
            get
            {
                return GetNullableInt32( TRUEHEADING_FIELD_ID );
            }
        }
        public int Timestamp
        {
            get
            {
                return GetInt32( TIMESTAMP_FIELD_ID );
            }
        }
        public int RegionalReserved
        {
            get
            {
                return GetInt32( REGIONALRESERVED_FIELD_ID );
            }
        }
        public bool IsCsUnit
        {
            get
            {
                return GetBoolean( ISCSUNIT_FIELD_ID );
            }
        }
        public bool HasDisplay
        {
            get
            {
                return GetBoolean( HASDISPLAY_FIELD_ID );
            }
        }
        public bool HasDscCapability
        {
            get
            {
                return GetBoolean( HASDSCCAPABILITY_FIELD_ID );
            }
        }
        public bool Band
        {
            get
            {
                return GetBoolean( BAND_FIELD_ID );
            }
        }
        public bool CanAcceptMessage22
        {
            get
            {
                return GetBoolean( CANACCEPTMESSAGE22_FIELD_ID );
            }
        }
        public bool Assigned
        {
            get
            {
                return GetBoolean( ASSIGNED_FIELD_ID );
            }
        }
        public Types.Raim Raim
        {
            get
            {
                return GetEnum<Types.Raim>( RAIM_FIELD_ID );
            }
        }
        public int RadioStatus
        {
            get
            {
                return GetInt32( RADIOSTATUS_FIELD_ID );
            }
        }
    }

    public class SimpleAisStandardSarAircraftPositionReportMessageDataReader : SimpleAisMessageDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  assaprm.[Id], \r\n" +
            "  assaprm.[EntityType], \r\n" +
            "  assaprm.[RowVersion], \r\n" +
            "  assaprm.[AisDevice], \r\n" +
            "  assaprm.[ReceivedTimestamp], \r\n" +
            "  assaprm.[MessageSequenceNumber], \r\n" +
            "  assaprm.[Repeat], \r\n" +
            "  assaprm.[Mmsi], \r\n" +
            "  assaprm.[Altitude], \r\n" +
            "  assaprm.[SpeedOverGround], \r\n" +
            "  assaprm.[PositionAccuracy], \r\n" +
            "  assaprm.[Longitude], \r\n" +
            "  assaprm.[Latitude], \r\n" +
            "  assaprm.[CourseOverGround], \r\n" +
            "  assaprm.[Timestamp], \r\n" +
            "  assaprm.[Reserved], \r\n" +
            "  assaprm.[DataTerminalReady], \r\n" +
            "  assaprm.[Spare], \r\n" +
            "  assaprm.[Assigned], \r\n" +
            "  assaprm.[Raim], \r\n" +
            "  assaprm.[RadioStatus] \r\n" +
            "FROM [AisStandardSarAircraftPositionReportMessageView] assaprm \r\n";

        public new const string BaseViewName = "AisStandardSarAircraftPositionReportMessageView";
        public new const string ViewAliasName = "assaprm";

        public const int ALTITUDE_FIELD_ID = 7;
        public const int SPEEDOVERGROUND_FIELD_ID = 8;
        public const int POSITIONACCURACY_FIELD_ID = 9;
        public const int LONGITUDE_FIELD_ID = 10;
        public const int LATITUDE_FIELD_ID = 11;
        public const int COURSEOVERGROUND_FIELD_ID = 12;
        public const int TIMESTAMP_FIELD_ID = 13;
        public const int RESERVED_FIELD_ID = 14;
        public const int DATATERMINALREADY_FIELD_ID = 15;
        public const int SPARE_FIELD_ID = 16;
        public const int ASSIGNED_FIELD_ID = 17;
        public const int RAIM_FIELD_ID = 18;
        public const int RADIOSTATUS_FIELD_ID = 19;

        public SimpleAisStandardSarAircraftPositionReportMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public int Altitude
        {
            get
            {
                return GetInt32( ALTITUDE_FIELD_ID );
            }
        }
        public int SpeedOverGround
        {
            get
            {
                return GetInt32( SPEEDOVERGROUND_FIELD_ID );
            }
        }
        public Types.PositionAccuracy PositionAccuracy
        {
            get
            {
                return GetEnum<Types.PositionAccuracy>( POSITIONACCURACY_FIELD_ID );
            }
        }
        public double Longitude
        {
            get
            {
                return GetDouble( LONGITUDE_FIELD_ID );
            }
        }
        public double Latitude
        {
            get
            {
                return GetDouble( LATITUDE_FIELD_ID );
            }
        }
        public double CourseOverGround
        {
            get
            {
                return GetDouble( COURSEOVERGROUND_FIELD_ID );
            }
        }
        public int Timestamp
        {
            get
            {
                return GetInt32( TIMESTAMP_FIELD_ID );
            }
        }
        public int Reserved
        {
            get
            {
                return GetInt32( RESERVED_FIELD_ID );
            }
        }
        public bool DataTerminalReady
        {
            get
            {
                return GetBoolean( DATATERMINALREADY_FIELD_ID );
            }
        }
        public int Spare
        {
            get
            {
                return GetInt32( SPARE_FIELD_ID );
            }
        }
        public bool Assigned
        {
            get
            {
                return GetBoolean( ASSIGNED_FIELD_ID );
            }
        }
        public Types.Raim Raim
        {
            get
            {
                return GetEnum<Types.Raim>( RAIM_FIELD_ID );
            }
        }
        public int RadioStatus
        {
            get
            {
                return GetInt32( RADIOSTATUS_FIELD_ID );
            }
        }
    }

    public class SimpleAisStaticAndVoyageRelatedDataMessageDataReader : SimpleAisMessageDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  asavrdm.[Id], \r\n" +
            "  asavrdm.[EntityType], \r\n" +
            "  asavrdm.[RowVersion], \r\n" +
            "  asavrdm.[AisDevice], \r\n" +
            "  asavrdm.[ReceivedTimestamp], \r\n" +
            "  asavrdm.[MessageSequenceNumber], \r\n" +
            "  asavrdm.[Repeat], \r\n" +
            "  asavrdm.[Mmsi], \r\n" +
            "  asavrdm.[AisVersion], \r\n" +
            "  asavrdm.[ImoNumber], \r\n" +
            "  asavrdm.[Callsign], \r\n" +
            "  asavrdm.[ShipName], \r\n" +
            "  asavrdm.[ShipType], \r\n" +
            "  asavrdm.[DimensionToBow], \r\n" +
            "  asavrdm.[DimensionToStern], \r\n" +
            "  asavrdm.[DimensionToPort], \r\n" +
            "  asavrdm.[DimensionToStarboard], \r\n" +
            "  asavrdm.[PositionFixType], \r\n" +
            "  asavrdm.[EstimatedTimeOfArrival], \r\n" +
            "  asavrdm.[Draught], \r\n" +
            "  asavrdm.[Destination], \r\n" +
            "  asavrdm.[DataTerminalReady], \r\n" +
            "  asavrdm.[Spare] \r\n" +
            "FROM [AisStaticAndVoyageRelatedDataMessageView] asavrdm \r\n";

        public new const string BaseViewName = "AisStaticAndVoyageRelatedDataMessageView";
        public new const string ViewAliasName = "asavrdm";

        public const int AISVERSION_FIELD_ID = 7;
        public const int IMONUMBER_FIELD_ID = 8;
        public const int CALLSIGN_FIELD_ID = 9;
        public const int SHIPNAME_FIELD_ID = 10;
        public const int SHIPTYPE_FIELD_ID = 11;
        public const int DIMENSIONTOBOW_FIELD_ID = 12;
        public const int DIMENSIONTOSTERN_FIELD_ID = 13;
        public const int DIMENSIONTOPORT_FIELD_ID = 14;
        public const int DIMENSIONTOSTARBOARD_FIELD_ID = 15;
        public const int POSITIONFIXTYPE_FIELD_ID = 16;
        public const int ESTIMATEDTIMEOFARRIVAL_FIELD_ID = 17;
        public const int DRAUGHT_FIELD_ID = 18;
        public const int DESTINATION_FIELD_ID = 19;
        public const int DATATERMINALREADY_FIELD_ID = 20;
        public const int SPARE_FIELD_ID = 21;

        public SimpleAisStaticAndVoyageRelatedDataMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public int AisVersion
        {
            get
            {
                return GetInt32( AISVERSION_FIELD_ID );
            }
        }
        public Guid ImoNumber
        {
            get
            {
                return GetGuid( IMONUMBER_FIELD_ID );
            }
        }
        public Guid Callsign
        {
            get
            {
                return GetGuid( CALLSIGN_FIELD_ID );
            }
        }
        public Guid ShipName
        {
            get
            {
                return GetGuid( SHIPNAME_FIELD_ID );
            }
        }
        public Types.ShipType ShipType
        {
            get
            {
                return GetEnum<Types.ShipType>( SHIPTYPE_FIELD_ID );
            }
        }
        public int DimensionToBow
        {
            get
            {
                return GetInt32( DIMENSIONTOBOW_FIELD_ID );
            }
        }
        public int DimensionToStern
        {
            get
            {
                return GetInt32( DIMENSIONTOSTERN_FIELD_ID );
            }
        }
        public int DimensionToPort
        {
            get
            {
                return GetInt32( DIMENSIONTOPORT_FIELD_ID );
            }
        }
        public int DimensionToStarboard
        {
            get
            {
                return GetInt32( DIMENSIONTOSTARBOARD_FIELD_ID );
            }
        }
        public Types.PositionFixType PositionFixType
        {
            get
            {
                return GetEnum<Types.PositionFixType>( POSITIONFIXTYPE_FIELD_ID );
            }
        }
        public DateTime? EstimatedTimeOfArrival
        {
            get
            {
                var v = GetNullableInt64( ESTIMATEDTIMEOFARRIVAL_FIELD_ID );
                if( v is long value )
                {
                    return new DateTime( value , DateTimeKind.Utc );
                }
                return null;
            }
        }
        public double Draught
        {
            get
            {
                return GetDouble( DRAUGHT_FIELD_ID );
            }
        }
        public string Destination
        {
            get
            {
                return GetString( DESTINATION_FIELD_ID );
            }
        }
        public bool DataTerminalReady
        {
            get
            {
                return GetBoolean( DATATERMINALREADY_FIELD_ID );
            }
        }
        public int Spare
        {
            get
            {
                return GetInt32( SPARE_FIELD_ID );
            }
        }
    }

    public class SimpleAisStaticDataReportMessageDataReader : SimpleAisMessageDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  asdrm.[Id], \r\n" +
            "  asdrm.[EntityType], \r\n" +
            "  asdrm.[RowVersion], \r\n" +
            "  asdrm.[AisDevice], \r\n" +
            "  asdrm.[ReceivedTimestamp], \r\n" +
            "  asdrm.[MessageSequenceNumber], \r\n" +
            "  asdrm.[Repeat], \r\n" +
            "  asdrm.[Mmsi], \r\n" +
            "  asdrm.[PartNumber] \r\n" +
            "FROM [AisStaticDataReportMessageView] asdrm \r\n";

        public new const string BaseViewName = "AisStaticDataReportMessageView";
        public new const string ViewAliasName = "asdrm";

        public const int PARTNUMBER_FIELD_ID = 7;

        public SimpleAisStaticDataReportMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public int PartNumber
        {
            get
            {
                return GetInt32( PARTNUMBER_FIELD_ID );
            }
        }
    }

    public class SimpleAisStaticDataReportPartAMessageDataReader : SimpleAisStaticDataReportMessageDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  asdrpa.[Id], \r\n" +
            "  asdrpa.[EntityType], \r\n" +
            "  asdrpa.[RowVersion], \r\n" +
            "  asdrpa.[AisDevice], \r\n" +
            "  asdrpa.[ReceivedTimestamp], \r\n" +
            "  asdrpa.[MessageSequenceNumber], \r\n" +
            "  asdrpa.[Repeat], \r\n" +
            "  asdrpa.[Mmsi], \r\n" +
            "  asdrpa.[PartNumber], \r\n" +
            "  asdrpa.[ShipName], \r\n" +
            "  asdrpa.[Spare] \r\n" +
            "FROM [AisStaticDataReportPartAMessageView] asdrpa \r\n";

        public new const string BaseViewName = "AisStaticDataReportPartAMessageView";
        public new const string ViewAliasName = "asdrpa";

        public const int SHIPNAME_FIELD_ID = 8;
        public const int SPARE_FIELD_ID = 9;

        public SimpleAisStaticDataReportPartAMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid ShipName
        {
            get
            {
                return GetGuid( SHIPNAME_FIELD_ID );
            }
        }
        public int Spare
        {
            get
            {
                return GetInt32( SPARE_FIELD_ID );
            }
        }
    }

    public class SimpleAisStaticDataReportPartBMessageDataReader : SimpleAisStaticDataReportMessageDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  asdrpb.[Id], \r\n" +
            "  asdrpb.[EntityType], \r\n" +
            "  asdrpb.[RowVersion], \r\n" +
            "  asdrpb.[AisDevice], \r\n" +
            "  asdrpb.[ReceivedTimestamp], \r\n" +
            "  asdrpb.[MessageSequenceNumber], \r\n" +
            "  asdrpb.[Repeat], \r\n" +
            "  asdrpb.[Mmsi], \r\n" +
            "  asdrpb.[PartNumber], \r\n" +
            "  asdrpb.[ShipType], \r\n" +
            "  asdrpb.[VendorId], \r\n" +
            "  asdrpb.[UnitModelCode], \r\n" +
            "  asdrpb.[SerialNumber], \r\n" +
            "  asdrpb.[Callsign], \r\n" +
            "  asdrpb.[DimensionToBow], \r\n" +
            "  asdrpb.[DimensionToStern], \r\n" +
            "  asdrpb.[DimensionToPort], \r\n" +
            "  asdrpb.[DimensionToStarboard], \r\n" +
            "  asdrpb.[MothershipMmsi], \r\n" +
            "  asdrpb.[PositionFixType], \r\n" +
            "  asdrpb.[Spare] \r\n" +
            "FROM [AisStaticDataReportPartBMessageView] asdrpb \r\n";

        public new const string BaseViewName = "AisStaticDataReportPartBMessageView";
        public new const string ViewAliasName = "asdrpb";

        public const int SHIPTYPE_FIELD_ID = 8;
        public const int VENDORID_FIELD_ID = 9;
        public const int UNITMODELCODE_FIELD_ID = 10;
        public const int SERIALNUMBER_FIELD_ID = 11;
        public const int CALLSIGN_FIELD_ID = 12;
        public const int DIMENSIONTOBOW_FIELD_ID = 13;
        public const int DIMENSIONTOSTERN_FIELD_ID = 14;
        public const int DIMENSIONTOPORT_FIELD_ID = 15;
        public const int DIMENSIONTOSTARBOARD_FIELD_ID = 16;
        public const int MOTHERSHIPMMSI_FIELD_ID = 17;
        public const int POSITIONFIXTYPE_FIELD_ID = 18;
        public const int SPARE_FIELD_ID = 19;

        public SimpleAisStaticDataReportPartBMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Types.ShipType ShipType
        {
            get
            {
                return GetEnum<Types.ShipType>( SHIPTYPE_FIELD_ID );
            }
        }
        public string VendorId
        {
            get
            {
                return GetString( VENDORID_FIELD_ID );
            }
        }
        public int UnitModelCode
        {
            get
            {
                return GetInt32( UNITMODELCODE_FIELD_ID );
            }
        }
        public int SerialNumber
        {
            get
            {
                return GetInt32( SERIALNUMBER_FIELD_ID );
            }
        }
        public Guid Callsign
        {
            get
            {
                return GetGuid( CALLSIGN_FIELD_ID );
            }
        }
        public int DimensionToBow
        {
            get
            {
                return GetInt32( DIMENSIONTOBOW_FIELD_ID );
            }
        }
        public int DimensionToStern
        {
            get
            {
                return GetInt32( DIMENSIONTOSTERN_FIELD_ID );
            }
        }
        public int DimensionToPort
        {
            get
            {
                return GetInt32( DIMENSIONTOPORT_FIELD_ID );
            }
        }
        public int DimensionToStarboard
        {
            get
            {
                return GetInt32( DIMENSIONTOSTARBOARD_FIELD_ID );
            }
        }
        public Guid? MothershipMmsi
        {
            get
            {
                return GetNullableGuid( MOTHERSHIPMMSI_FIELD_ID );
            }
        }
        public Types.PositionFixType PositionFixType
        {
            get
            {
                return GetEnum<Types.PositionFixType>( POSITIONFIXTYPE_FIELD_ID );
            }
        }
        public int Spare
        {
            get
            {
                return GetInt32( SPARE_FIELD_ID );
            }
        }
    }

    public class SimpleAisUtcAndDateInquiryMessageDataReader : SimpleAisMessageDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  auadim.[Id], \r\n" +
            "  auadim.[EntityType], \r\n" +
            "  auadim.[RowVersion], \r\n" +
            "  auadim.[AisDevice], \r\n" +
            "  auadim.[ReceivedTimestamp], \r\n" +
            "  auadim.[MessageSequenceNumber], \r\n" +
            "  auadim.[Repeat], \r\n" +
            "  auadim.[Mmsi], \r\n" +
            "  auadim.[Spare1], \r\n" +
            "  auadim.[DestinationMmsi], \r\n" +
            "  auadim.[Spare2] \r\n" +
            "FROM [AisUtcAndDateInquiryMessageView] auadim \r\n";

        public new const string BaseViewName = "AisUtcAndDateInquiryMessageView";
        public new const string ViewAliasName = "auadim";

        public const int SPARE1_FIELD_ID = 7;
        public const int DESTINATIONMMSI_FIELD_ID = 8;
        public const int SPARE2_FIELD_ID = 9;

        public SimpleAisUtcAndDateInquiryMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public int Spare1
        {
            get
            {
                return GetInt32( SPARE1_FIELD_ID );
            }
        }
        public int DestinationMmsi
        {
            get
            {
                return GetInt32( DESTINATIONMMSI_FIELD_ID );
            }
        }
        public int Spare2
        {
            get
            {
                return GetInt32( SPARE2_FIELD_ID );
            }
        }
    }

    public class SimpleAisUtcAndDateResponseMessageDataReader : SimpleAisMessageDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  auadrm.[Id], \r\n" +
            "  auadrm.[EntityType], \r\n" +
            "  auadrm.[RowVersion], \r\n" +
            "  auadrm.[AisDevice], \r\n" +
            "  auadrm.[ReceivedTimestamp], \r\n" +
            "  auadrm.[MessageSequenceNumber], \r\n" +
            "  auadrm.[Repeat], \r\n" +
            "  auadrm.[Mmsi], \r\n" +
            "  auadrm.[Datetime], \r\n" +
            "  auadrm.[PositionAccuracy], \r\n" +
            "  auadrm.[Longitude], \r\n" +
            "  auadrm.[Latitude], \r\n" +
            "  auadrm.[PositionFixType], \r\n" +
            "  auadrm.[Spare], \r\n" +
            "  auadrm.[Raim], \r\n" +
            "  auadrm.[RadioStatus] \r\n" +
            "FROM [AisUtcAndDateResponseMessageView] auadrm \r\n";

        public new const string BaseViewName = "AisUtcAndDateResponseMessageView";
        public new const string ViewAliasName = "auadrm";

        public const int DATETIME_FIELD_ID = 7;
        public const int POSITIONACCURACY_FIELD_ID = 8;
        public const int LONGITUDE_FIELD_ID = 9;
        public const int LATITUDE_FIELD_ID = 10;
        public const int POSITIONFIXTYPE_FIELD_ID = 11;
        public const int SPARE_FIELD_ID = 12;
        public const int RAIM_FIELD_ID = 13;
        public const int RADIOSTATUS_FIELD_ID = 14;

        public SimpleAisUtcAndDateResponseMessageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public DateTime Datetime
        {
            get
            {
                return new DateTime( GetInt64( DATETIME_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Types.PositionAccuracy PositionAccuracy
        {
            get
            {
                return GetEnum<Types.PositionAccuracy>( POSITIONACCURACY_FIELD_ID );
            }
        }
        public double Longitude
        {
            get
            {
                return GetDouble( LONGITUDE_FIELD_ID );
            }
        }
        public double Latitude
        {
            get
            {
                return GetDouble( LATITUDE_FIELD_ID );
            }
        }
        public Types.PositionFixType PositionFixType
        {
            get
            {
                return GetEnum<Types.PositionFixType>( POSITIONFIXTYPE_FIELD_ID );
            }
        }
        public int Spare
        {
            get
            {
                return GetInt32( SPARE_FIELD_ID );
            }
        }
        public Types.Raim Raim
        {
            get
            {
                return GetEnum<Types.Raim>( RAIM_FIELD_ID );
            }
        }
        public int RadioStatus
        {
            get
            {
                return GetInt32( RADIOSTATUS_FIELD_ID );
            }
        }
    }

    public class SimpleAlarmStateChangeDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  asc.[Id], \r\n" +
            "  asc.[RowVersion], \r\n" +
            "  asc.[Alarm], \r\n" +
            "  asc.[Timestamp], \r\n" +
            "  asc.[State] \r\n" +
            "FROM [AlarmStateChangeView] asc \r\n";

        public const string BaseViewName = "AlarmStateChangeView";
        public const string ViewAliasName = "asc";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int ALARM_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int STATE_FIELD_ID = 4;

        public SimpleAlarmStateChangeDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Alarm
        {
            get
            {
                return GetGuid( ALARM_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Types.AlarmState State
        {
            get
            {
                return GetEnum<Types.AlarmState>( STATE_FIELD_ID );
            }
        }
    }

    public class SimpleBaseStationTypeDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  bst.[Id], \r\n" +
            "  bst.[RowVersion], \r\n" +
            "  bst.[Name] \r\n" +
            "FROM [BaseStationTypeView] bst \r\n";

        public const string BaseViewName = "BaseStationTypeView";
        public const string ViewAliasName = "bst";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int NAME_FIELD_ID = 2;

        public SimpleBaseStationTypeDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
    }

    public class SimpleBinaryTimeseriesValueDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  btv.[Id], \r\n" +
            "  btv.[RowVersion], \r\n" +
            "  btv.[Timeseries], \r\n" +
            "  btv.[Timestamp], \r\n" +
            "  btv.[Value] \r\n" +
            "FROM [BinaryTimeseriesValueView] btv \r\n";

        public const string BaseViewName = "BinaryTimeseriesValueView";
        public const string ViewAliasName = "btv";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TIMESERIES_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int VALUE_FIELD_ID = 4;

        public SimpleBinaryTimeseriesValueDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public byte[] Value
        {
            get
            {
                return GetBytes( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleBookmarkDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  b.[Id], \r\n" +
            "  b.[RowVersion], \r\n" +
            "  b.[View], \r\n" +
            "  b.[Name], \r\n" +
            "  b.[Timestamp], \r\n" +
            "  b.[Latitude], \r\n" +
            "  b.[Longitude], \r\n" +
            "  b.[ZoomLevel] \r\n" +
            "FROM [BookmarkView] b \r\n";

        public const string BaseViewName = "BookmarkView";
        public const string ViewAliasName = "b";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int VIEW_FIELD_ID = 2;
        public const int NAME_FIELD_ID = 3;
        public const int TIMESTAMP_FIELD_ID = 4;
        public const int LATITUDE_FIELD_ID = 5;
        public const int LONGITUDE_FIELD_ID = 6;
        public const int ZOOMLEVEL_FIELD_ID = 7;

        public SimpleBookmarkDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid View
        {
            get
            {
                return GetGuid( VIEW_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
        public DateTime? Timestamp
        {
            get
            {
                var v = GetNullableInt64( TIMESTAMP_FIELD_ID );
                if( v is long value )
                {
                    return new DateTime( value , DateTimeKind.Utc );
                }
                return null;
            }
        }
        public double Latitude
        {
            get
            {
                return GetDouble( LATITUDE_FIELD_ID );
            }
        }
        public double Longitude
        {
            get
            {
                return GetDouble( LONGITUDE_FIELD_ID );
            }
        }
        public double ZoomLevel
        {
            get
            {
                return GetDouble( ZOOMLEVEL_FIELD_ID );
            }
        }
    }

    public class SimpleBooleanTimeseriesValueDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  btv.[Id], \r\n" +
            "  btv.[RowVersion], \r\n" +
            "  btv.[Timeseries], \r\n" +
            "  btv.[Timestamp], \r\n" +
            "  btv.[Value] \r\n" +
            "FROM [BooleanTimeseriesValueView] btv \r\n";

        public const string BaseViewName = "BooleanTimeseriesValueView";
        public const string ViewAliasName = "btv";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TIMESERIES_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int VALUE_FIELD_ID = 4;

        public SimpleBooleanTimeseriesValueDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public bool? Value
        {
            get
            {
                return GetNullableBoolean( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleByteTimeseriesValueDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  btv.[Id], \r\n" +
            "  btv.[RowVersion], \r\n" +
            "  btv.[Timeseries], \r\n" +
            "  btv.[Timestamp], \r\n" +
            "  btv.[Value] \r\n" +
            "FROM [ByteTimeseriesValueView] btv \r\n";

        public const string BaseViewName = "ByteTimeseriesValueView";
        public const string ViewAliasName = "btv";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TIMESERIES_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int VALUE_FIELD_ID = 4;

        public SimpleByteTimeseriesValueDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public byte? Value
        {
            get
            {
                return GetNullableByte( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleCameraCommandDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  cc.[Id], \r\n" +
            "  cc.[EntityType], \r\n" +
            "  cc.[RowVersion], \r\n" +
            "  cc.[Camera], \r\n" +
            "  cc.[Timestamp], \r\n" +
            "  cc.[DeviceCommandSourceType], \r\n" +
            "  cc.[DeviceCommandSourceId], \r\n" +
            "  cc.[Reply] \r\n" +
            "FROM [CameraCommandView] cc \r\n";

        public const string BaseViewName = "CameraCommandView";
        public const string ViewAliasName = "cc";

        public const int ID_FIELD_ID = 0;
        public const int ENTITYTYPE_FIELD_ID = 1;
        public const int ROWVERSION_FIELD_ID = 2;
        public const int CAMERA_FIELD_ID = 3;
        public const int TIMESTAMP_FIELD_ID = 4;
        public const int DEVICECOMMANDSOURCETYPE_FIELD_ID = 5;
        public const int DEVICECOMMANDSOURCEID_FIELD_ID = 6;
        public const int REPLY_FIELD_ID = 7;

        public SimpleCameraCommandDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public Types.Kind EntityType
        {
            get
            {
                return GetEnum<Types.Kind>( ENTITYTYPE_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Camera
        {
            get
            {
                return GetGuid( CAMERA_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Types.DeviceCommandSourceType DeviceCommandSourceType
        {
            get
            {
                return GetEnum<Types.DeviceCommandSourceType>( DEVICECOMMANDSOURCETYPE_FIELD_ID );
            }
        }
        public Guid DeviceCommandSourceId
        {
            get
            {
                return GetGuid( DEVICECOMMANDSOURCEID_FIELD_ID );
            }
        }
        public Guid Reply
        {
            get
            {
                return GetGuid( REPLY_FIELD_ID );
            }
        }
    }

    public class SimpleCameraCommandAbsoluteMoveDataReader : SimpleCameraCommandDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  ccam.[Id], \r\n" +
            "  ccam.[EntityType], \r\n" +
            "  ccam.[RowVersion], \r\n" +
            "  ccam.[Camera], \r\n" +
            "  ccam.[Timestamp], \r\n" +
            "  ccam.[DeviceCommandSourceType], \r\n" +
            "  ccam.[DeviceCommandSourceId], \r\n" +
            "  ccam.[Reply], \r\n" +
            "  ccam.[PositionPanTiltMode], \r\n" +
            "  ccam.[PanAngle], \r\n" +
            "  ccam.[TiltAngle], \r\n" +
            "  ccam.[PositionFocalLengthMode], \r\n" +
            "  ccam.[FocalLength], \r\n" +
            "  ccam.[SpeedPanTiltMode], \r\n" +
            "  ccam.[PanSpeed], \r\n" +
            "  ccam.[TiltSpeed], \r\n" +
            "  ccam.[SpeedFocalLengthMode], \r\n" +
            "  ccam.[ZoomSpeed] \r\n" +
            "FROM [CameraCommandAbsoluteMoveView] ccam \r\n";

        public new const string BaseViewName = "CameraCommandAbsoluteMoveView";
        public new const string ViewAliasName = "ccam";

        public const int POSITIONPANTILTMODE_FIELD_ID = 7;
        public const int PANANGLE_FIELD_ID = 8;
        public const int TILTANGLE_FIELD_ID = 9;
        public const int POSITIONFOCALLENGTHMODE_FIELD_ID = 10;
        public const int FOCALLENGTH_FIELD_ID = 11;
        public const int SPEEDPANTILTMODE_FIELD_ID = 12;
        public const int PANSPEED_FIELD_ID = 13;
        public const int TILTSPEED_FIELD_ID = 14;
        public const int SPEEDFOCALLENGTHMODE_FIELD_ID = 15;
        public const int ZOOMSPEED_FIELD_ID = 16;

        public SimpleCameraCommandAbsoluteMoveDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Types.CameraPanTiltMode PositionPanTiltMode
        {
            get
            {
                return GetEnum<Types.CameraPanTiltMode>( POSITIONPANTILTMODE_FIELD_ID );
            }
        }
        public double? PanAngle
        {
            get
            {
                return GetNullableDouble( PANANGLE_FIELD_ID );
            }
        }
        public double? TiltAngle
        {
            get
            {
                return GetNullableDouble( TILTANGLE_FIELD_ID );
            }
        }
        public Types.CameraFocalLengthMode PositionFocalLengthMode
        {
            get
            {
                return GetEnum<Types.CameraFocalLengthMode>( POSITIONFOCALLENGTHMODE_FIELD_ID );
            }
        }
        public double? FocalLength
        {
            get
            {
                return GetNullableDouble( FOCALLENGTH_FIELD_ID );
            }
        }
        public Types.CameraPanTiltMode SpeedPanTiltMode
        {
            get
            {
                return GetEnum<Types.CameraPanTiltMode>( SPEEDPANTILTMODE_FIELD_ID );
            }
        }
        public double? PanSpeed
        {
            get
            {
                return GetNullableDouble( PANSPEED_FIELD_ID );
            }
        }
        public double? TiltSpeed
        {
            get
            {
                return GetNullableDouble( TILTSPEED_FIELD_ID );
            }
        }
        public Types.CameraFocalLengthMode SpeedFocalLengthMode
        {
            get
            {
                return GetEnum<Types.CameraFocalLengthMode>( SPEEDFOCALLENGTHMODE_FIELD_ID );
            }
        }
        public double? ZoomSpeed
        {
            get
            {
                return GetNullableDouble( ZOOMSPEED_FIELD_ID );
            }
        }
    }

    public class SimpleCameraCommandAdjustPanTiltZoomDataReader : SimpleCameraCommandDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  ccaptz.[Id], \r\n" +
            "  ccaptz.[EntityType], \r\n" +
            "  ccaptz.[RowVersion], \r\n" +
            "  ccaptz.[Camera], \r\n" +
            "  ccaptz.[Timestamp], \r\n" +
            "  ccaptz.[DeviceCommandSourceType], \r\n" +
            "  ccaptz.[DeviceCommandSourceId], \r\n" +
            "  ccaptz.[Reply], \r\n" +
            "  ccaptz.[X], \r\n" +
            "  ccaptz.[Y], \r\n" +
            "  ccaptz.[Z] \r\n" +
            "FROM [CameraCommandAdjustPanTiltZoomView] ccaptz \r\n";

        public new const string BaseViewName = "CameraCommandAdjustPanTiltZoomView";
        public new const string ViewAliasName = "ccaptz";

        public const int X_FIELD_ID = 7;
        public const int Y_FIELD_ID = 8;
        public const int Z_FIELD_ID = 9;

        public SimpleCameraCommandAdjustPanTiltZoomDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public double? X
        {
            get
            {
                return GetNullableDouble( X_FIELD_ID );
            }
        }
        public double? Y
        {
            get
            {
                return GetNullableDouble( Y_FIELD_ID );
            }
        }
        public double? Z
        {
            get
            {
                return GetNullableDouble( Z_FIELD_ID );
            }
        }
    }

    public class SimpleCameraCommandContinuousMoveDataReader : SimpleCameraCommandDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  cccm.[Id], \r\n" +
            "  cccm.[EntityType], \r\n" +
            "  cccm.[RowVersion], \r\n" +
            "  cccm.[Camera], \r\n" +
            "  cccm.[Timestamp], \r\n" +
            "  cccm.[DeviceCommandSourceType], \r\n" +
            "  cccm.[DeviceCommandSourceId], \r\n" +
            "  cccm.[Reply], \r\n" +
            "  cccm.[Normalized], \r\n" +
            "  cccm.[PanVelocity], \r\n" +
            "  cccm.[TiltVelocity], \r\n" +
            "  cccm.[ZoomVelocity], \r\n" +
            "  cccm.[Duration] \r\n" +
            "FROM [CameraCommandContinuousMoveView] cccm \r\n";

        public new const string BaseViewName = "CameraCommandContinuousMoveView";
        public new const string ViewAliasName = "cccm";

        public const int NORMALIZED_FIELD_ID = 7;
        public const int PANVELOCITY_FIELD_ID = 8;
        public const int TILTVELOCITY_FIELD_ID = 9;
        public const int ZOOMVELOCITY_FIELD_ID = 10;
        public const int DURATION_FIELD_ID = 11;

        public SimpleCameraCommandContinuousMoveDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public bool Normalized
        {
            get
            {
                return GetBoolean( NORMALIZED_FIELD_ID );
            }
        }
        public double? PanVelocity
        {
            get
            {
                return GetNullableDouble( PANVELOCITY_FIELD_ID );
            }
        }
        public double? TiltVelocity
        {
            get
            {
                return GetNullableDouble( TILTVELOCITY_FIELD_ID );
            }
        }
        public double? ZoomVelocity
        {
            get
            {
                return GetNullableDouble( ZOOMVELOCITY_FIELD_ID );
            }
        }
        public TimeSpan? Duration
        {
            get
            {
                var v = GetNullableInt64( DURATION_FIELD_ID );
                if( v is long value )
                {
                    return new TimeSpan( value );
                }
                return null;
            }
        }
    }

    public class SimpleCameraCommandGeoMoveDataReader : SimpleCameraCommandDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  ccgm.[Id], \r\n" +
            "  ccgm.[EntityType], \r\n" +
            "  ccgm.[RowVersion], \r\n" +
            "  ccgm.[Camera], \r\n" +
            "  ccgm.[Timestamp], \r\n" +
            "  ccgm.[DeviceCommandSourceType], \r\n" +
            "  ccgm.[DeviceCommandSourceId], \r\n" +
            "  ccgm.[Reply], \r\n" +
            "  ccgm.[Latitude], \r\n" +
            "  ccgm.[Longitude], \r\n" +
            "  ccgm.[Altitude], \r\n" +
            "  ccgm.[ViewportWidth], \r\n" +
            "  ccgm.[ViewportHeight] \r\n" +
            "FROM [CameraCommandGeoMoveView] ccgm \r\n";

        public new const string BaseViewName = "CameraCommandGeoMoveView";
        public new const string ViewAliasName = "ccgm";

        public const int LATITUDE_FIELD_ID = 7;
        public const int LONGITUDE_FIELD_ID = 8;
        public const int ALTITUDE_FIELD_ID = 9;
        public const int VIEWPORTWIDTH_FIELD_ID = 10;
        public const int VIEWPORTHEIGHT_FIELD_ID = 11;

        public SimpleCameraCommandGeoMoveDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public double Latitude
        {
            get
            {
                return GetDouble( LATITUDE_FIELD_ID );
            }
        }
        public double Longitude
        {
            get
            {
                return GetDouble( LONGITUDE_FIELD_ID );
            }
        }
        public double? Altitude
        {
            get
            {
                return GetNullableDouble( ALTITUDE_FIELD_ID );
            }
        }
        public double? ViewportWidth
        {
            get
            {
                return GetNullableDouble( VIEWPORTWIDTH_FIELD_ID );
            }
        }
        public double? ViewportHeight
        {
            get
            {
                return GetNullableDouble( VIEWPORTHEIGHT_FIELD_ID );
            }
        }
    }

    public class SimpleCameraCommandRelativeMoveDataReader : SimpleCameraCommandDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  ccrm.[Id], \r\n" +
            "  ccrm.[EntityType], \r\n" +
            "  ccrm.[RowVersion], \r\n" +
            "  ccrm.[Camera], \r\n" +
            "  ccrm.[Timestamp], \r\n" +
            "  ccrm.[DeviceCommandSourceType], \r\n" +
            "  ccrm.[DeviceCommandSourceId], \r\n" +
            "  ccrm.[Reply], \r\n" +
            "  ccrm.[Normalized], \r\n" +
            "  ccrm.[PanAngle], \r\n" +
            "  ccrm.[TiltAngle], \r\n" +
            "  ccrm.[FocalLength], \r\n" +
            "  ccrm.[PanSpeed], \r\n" +
            "  ccrm.[TiltSpeed], \r\n" +
            "  ccrm.[ZoomSpeed] \r\n" +
            "FROM [CameraCommandRelativeMoveView] ccrm \r\n";

        public new const string BaseViewName = "CameraCommandRelativeMoveView";
        public new const string ViewAliasName = "ccrm";

        public const int NORMALIZED_FIELD_ID = 7;
        public const int PANANGLE_FIELD_ID = 8;
        public const int TILTANGLE_FIELD_ID = 9;
        public const int FOCALLENGTH_FIELD_ID = 10;
        public const int PANSPEED_FIELD_ID = 11;
        public const int TILTSPEED_FIELD_ID = 12;
        public const int ZOOMSPEED_FIELD_ID = 13;

        public SimpleCameraCommandRelativeMoveDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public bool Normalized
        {
            get
            {
                return GetBoolean( NORMALIZED_FIELD_ID );
            }
        }
        public double? PanAngle
        {
            get
            {
                return GetNullableDouble( PANANGLE_FIELD_ID );
            }
        }
        public double? TiltAngle
        {
            get
            {
                return GetNullableDouble( TILTANGLE_FIELD_ID );
            }
        }
        public double? FocalLength
        {
            get
            {
                return GetNullableDouble( FOCALLENGTH_FIELD_ID );
            }
        }
        public double? PanSpeed
        {
            get
            {
                return GetNullableDouble( PANSPEED_FIELD_ID );
            }
        }
        public double? TiltSpeed
        {
            get
            {
                return GetNullableDouble( TILTSPEED_FIELD_ID );
            }
        }
        public double? ZoomSpeed
        {
            get
            {
                return GetNullableDouble( ZOOMSPEED_FIELD_ID );
            }
        }
    }

    public class SimpleCameraCommandReleasePTZOwnershipDataReader : SimpleCameraCommandDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  crlp.[Id], \r\n" +
            "  crlp.[EntityType], \r\n" +
            "  crlp.[RowVersion], \r\n" +
            "  crlp.[Camera], \r\n" +
            "  crlp.[Timestamp], \r\n" +
            "  crlp.[DeviceCommandSourceType], \r\n" +
            "  crlp.[DeviceCommandSourceId], \r\n" +
            "  crlp.[Reply] \r\n" +
            "FROM [CameraCommandReleasePTZOwnershipView] crlp \r\n";

        public new const string BaseViewName = "CameraCommandReleasePTZOwnershipView";
        public new const string ViewAliasName = "crlp";

        public SimpleCameraCommandReleasePTZOwnershipDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleCameraCommandRequestPTZOwnershipDataReader : SimpleCameraCommandDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  crqp.[Id], \r\n" +
            "  crqp.[EntityType], \r\n" +
            "  crqp.[RowVersion], \r\n" +
            "  crqp.[Camera], \r\n" +
            "  crqp.[Timestamp], \r\n" +
            "  crqp.[DeviceCommandSourceType], \r\n" +
            "  crqp.[DeviceCommandSourceId], \r\n" +
            "  crqp.[Reply] \r\n" +
            "FROM [CameraCommandRequestPTZOwnershipView] crqp \r\n";

        public new const string BaseViewName = "CameraCommandRequestPTZOwnershipView";
        public new const string ViewAliasName = "crqp";

        public SimpleCameraCommandRequestPTZOwnershipDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleCameraCommandSetAutoFocusDataReader : SimpleCameraCommandDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  ccsaf.[Id], \r\n" +
            "  ccsaf.[EntityType], \r\n" +
            "  ccsaf.[RowVersion], \r\n" +
            "  ccsaf.[Camera], \r\n" +
            "  ccsaf.[Timestamp], \r\n" +
            "  ccsaf.[DeviceCommandSourceType], \r\n" +
            "  ccsaf.[DeviceCommandSourceId], \r\n" +
            "  ccsaf.[Reply], \r\n" +
            "  ccsaf.[Enabled] \r\n" +
            "FROM [CameraCommandSetAutoFocusView] ccsaf \r\n";

        public new const string BaseViewName = "CameraCommandSetAutoFocusView";
        public new const string ViewAliasName = "ccsaf";

        public const int ENABLED_FIELD_ID = 7;

        public SimpleCameraCommandSetAutoFocusDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public bool Enabled
        {
            get
            {
                return GetBoolean( ENABLED_FIELD_ID );
            }
        }
    }

    public class SimpleCameraCommandSetBlackAndWhiteDataReader : SimpleCameraCommandDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  ccsbaw.[Id], \r\n" +
            "  ccsbaw.[EntityType], \r\n" +
            "  ccsbaw.[RowVersion], \r\n" +
            "  ccsbaw.[Camera], \r\n" +
            "  ccsbaw.[Timestamp], \r\n" +
            "  ccsbaw.[DeviceCommandSourceType], \r\n" +
            "  ccsbaw.[DeviceCommandSourceId], \r\n" +
            "  ccsbaw.[Reply], \r\n" +
            "  ccsbaw.[Enabled] \r\n" +
            "FROM [CameraCommandSetBlackAndWhiteView] ccsbaw \r\n";

        public new const string BaseViewName = "CameraCommandSetBlackAndWhiteView";
        public new const string ViewAliasName = "ccsbaw";

        public const int ENABLED_FIELD_ID = 7;

        public SimpleCameraCommandSetBlackAndWhiteDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public bool Enabled
        {
            get
            {
                return GetBoolean( ENABLED_FIELD_ID );
            }
        }
    }

    public class SimpleCameraCommandSetFollowedDataReader : SimpleCameraCommandDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  ccsf.[Id], \r\n" +
            "  ccsf.[EntityType], \r\n" +
            "  ccsf.[RowVersion], \r\n" +
            "  ccsf.[Camera], \r\n" +
            "  ccsf.[Timestamp], \r\n" +
            "  ccsf.[DeviceCommandSourceType], \r\n" +
            "  ccsf.[DeviceCommandSourceId], \r\n" +
            "  ccsf.[Reply], \r\n" +
            "  ccsf.[TrackId], \r\n" +
            "  ccsf.[Reason] \r\n" +
            "FROM [CameraCommandSetFollowedView] ccsf \r\n";

        public new const string BaseViewName = "CameraCommandSetFollowedView";
        public new const string ViewAliasName = "ccsf";

        public const int TRACKID_FIELD_ID = 7;
        public const int REASON_FIELD_ID = 8;

        public SimpleCameraCommandSetFollowedDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid TrackId
        {
            get
            {
                return GetGuid( TRACKID_FIELD_ID );
            }
        }
        public Types.CameraFollowReason Reason
        {
            get
            {
                return GetEnum<Types.CameraFollowReason>( REASON_FIELD_ID );
            }
        }
    }

    public class SimpleCameraCommandSetInfraRedLampDataReader : SimpleCameraCommandDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  ccsirl.[Id], \r\n" +
            "  ccsirl.[EntityType], \r\n" +
            "  ccsirl.[RowVersion], \r\n" +
            "  ccsirl.[Camera], \r\n" +
            "  ccsirl.[Timestamp], \r\n" +
            "  ccsirl.[DeviceCommandSourceType], \r\n" +
            "  ccsirl.[DeviceCommandSourceId], \r\n" +
            "  ccsirl.[Reply], \r\n" +
            "  ccsirl.[Enabled] \r\n" +
            "FROM [CameraCommandSetInfraRedLampView] ccsirl \r\n";

        public new const string BaseViewName = "CameraCommandSetInfraRedLampView";
        public new const string ViewAliasName = "ccsirl";

        public const int ENABLED_FIELD_ID = 7;

        public SimpleCameraCommandSetInfraRedLampDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public bool Enabled
        {
            get
            {
                return GetBoolean( ENABLED_FIELD_ID );
            }
        }
    }

    public class SimpleCameraCommandSetWasherDataReader : SimpleCameraCommandDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  cwa.[Id], \r\n" +
            "  cwa.[EntityType], \r\n" +
            "  cwa.[RowVersion], \r\n" +
            "  cwa.[Camera], \r\n" +
            "  cwa.[Timestamp], \r\n" +
            "  cwa.[DeviceCommandSourceType], \r\n" +
            "  cwa.[DeviceCommandSourceId], \r\n" +
            "  cwa.[Reply], \r\n" +
            "  cwa.[Enabled] \r\n" +
            "FROM [CameraCommandSetWasherView] cwa \r\n";

        public new const string BaseViewName = "CameraCommandSetWasherView";
        public new const string ViewAliasName = "cwa";

        public const int ENABLED_FIELD_ID = 7;

        public SimpleCameraCommandSetWasherDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public bool Enabled
        {
            get
            {
                return GetBoolean( ENABLED_FIELD_ID );
            }
        }
    }

    public class SimpleCameraCommandSetWiperDataReader : SimpleCameraCommandDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  cwi.[Id], \r\n" +
            "  cwi.[EntityType], \r\n" +
            "  cwi.[RowVersion], \r\n" +
            "  cwi.[Camera], \r\n" +
            "  cwi.[Timestamp], \r\n" +
            "  cwi.[DeviceCommandSourceType], \r\n" +
            "  cwi.[DeviceCommandSourceId], \r\n" +
            "  cwi.[Reply], \r\n" +
            "  cwi.[Enabled] \r\n" +
            "FROM [CameraCommandSetWiperView] cwi \r\n";

        public new const string BaseViewName = "CameraCommandSetWiperView";
        public new const string ViewAliasName = "cwi";

        public const int ENABLED_FIELD_ID = 7;

        public SimpleCameraCommandSetWiperDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public bool Enabled
        {
            get
            {
                return GetBoolean( ENABLED_FIELD_ID );
            }
        }
    }

    public class SimpleCameraCommandStopDataReader : SimpleCameraCommandDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  ccs.[Id], \r\n" +
            "  ccs.[EntityType], \r\n" +
            "  ccs.[RowVersion], \r\n" +
            "  ccs.[Camera], \r\n" +
            "  ccs.[Timestamp], \r\n" +
            "  ccs.[DeviceCommandSourceType], \r\n" +
            "  ccs.[DeviceCommandSourceId], \r\n" +
            "  ccs.[Reply], \r\n" +
            "  ccs.[PanTilt], \r\n" +
            "  ccs.[Zoom] \r\n" +
            "FROM [CameraCommandStopView] ccs \r\n";

        public new const string BaseViewName = "CameraCommandStopView";
        public new const string ViewAliasName = "ccs";

        public const int PANTILT_FIELD_ID = 7;
        public const int ZOOM_FIELD_ID = 8;

        public SimpleCameraCommandStopDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public bool PanTilt
        {
            get
            {
                return GetBoolean( PANTILT_FIELD_ID );
            }
        }
        public bool Zoom
        {
            get
            {
                return GetBoolean( ZOOM_FIELD_ID );
            }
        }
    }

    public class SimpleCameraCommandReplyDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  ccr.[Id], \r\n" +
            "  ccr.[RowVersion], \r\n" +
            "  ccr.[Camera], \r\n" +
            "  ccr.[Timestamp], \r\n" +
            "  ccr.[Command], \r\n" +
            "  ccr.[Status], \r\n" +
            "  ccr.[Message], \r\n" +
            "  ccr.[PanAngle], \r\n" +
            "  ccr.[TiltAngle], \r\n" +
            "  ccr.[FocalLength] \r\n" +
            "FROM [CameraCommandReplyView] ccr \r\n";

        public const string BaseViewName = "CameraCommandReplyView";
        public const string ViewAliasName = "ccr";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int CAMERA_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int COMMAND_FIELD_ID = 4;
        public const int STATUS_FIELD_ID = 5;
        public const int MESSAGE_FIELD_ID = 6;
        public const int PANANGLE_FIELD_ID = 7;
        public const int TILTANGLE_FIELD_ID = 8;
        public const int FOCALLENGTH_FIELD_ID = 9;

        public SimpleCameraCommandReplyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Camera
        {
            get
            {
                return GetGuid( CAMERA_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Guid Command
        {
            get
            {
                return GetGuid( COMMAND_FIELD_ID );
            }
        }
        public Types.DeviceCommandReplyStatus Status
        {
            get
            {
                return GetEnum<Types.DeviceCommandReplyStatus>( STATUS_FIELD_ID );
            }
        }
        public string Message
        {
            get
            {
                return GetString( MESSAGE_FIELD_ID );
            }
        }
        public double PanAngle
        {
            get
            {
                return GetDouble( PANANGLE_FIELD_ID );
            }
        }
        public double TiltAngle
        {
            get
            {
                return GetDouble( TILTANGLE_FIELD_ID );
            }
        }
        public double FocalLength
        {
            get
            {
                return GetDouble( FOCALLENGTH_FIELD_ID );
            }
        }
    }

    public class SimpleCameraConfigurationDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  cc.[Id], \r\n" +
            "  cc.[RowVersion], \r\n" +
            "  cc.[Camera], \r\n" +
            "  cc.[Timestamp], \r\n" +
            "  cc.[CameraControlProtocol], \r\n" +
            "  cc.[CameraURL], \r\n" +
            "  cc.[ConfigurationURL], \r\n" +
            "  cc.[UserName], \r\n" +
            "  cc.[Password], \r\n" +
            "  cc.[UseRtspUriOverride], \r\n" +
            "  cc.[RtspUriOverride], \r\n" +
            "  cc.[Latitude], \r\n" +
            "  cc.[Longitude], \r\n" +
            "  cc.[Altitude], \r\n" +
            "  cc.[UseRelativePosition], \r\n" +
            "  cc.[PanTiltMode], \r\n" +
            "  cc.[MinTiltAngle], \r\n" +
            "  cc.[MaxTiltAngle], \r\n" +
            "  cc.[MinTiltScaleAngle], \r\n" +
            "  cc.[MaxTiltScaleAngle], \r\n" +
            "  cc.[UseReverseTiltAngle], \r\n" +
            "  cc.[UseReverseNormalizedTiltAngle], \r\n" +
            "  cc.[MinTiltVelocity], \r\n" +
            "  cc.[MaxTiltVelocity], \r\n" +
            "  cc.[MinTiltSpeed], \r\n" +
            "  cc.[MaxTiltSpeed], \r\n" +
            "  cc.[MinPanAngle], \r\n" +
            "  cc.[MaxPanAngle], \r\n" +
            "  cc.[MinPanScaleAngle], \r\n" +
            "  cc.[MaxPanScaleAngle], \r\n" +
            "  cc.[UseReversePanAngle], \r\n" +
            "  cc.[UseReverseNormalizedPanAngle], \r\n" +
            "  cc.[MinPanVelocity], \r\n" +
            "  cc.[MaxPanVelocity], \r\n" +
            "  cc.[MinPanSpeed], \r\n" +
            "  cc.[MaxPanSpeed], \r\n" +
            "  cc.[FocalLengthMode], \r\n" +
            "  cc.[MinFocalLength], \r\n" +
            "  cc.[MaxFocalLength], \r\n" +
            "  cc.[MinFocalLengthScale], \r\n" +
            "  cc.[MaxFocalLengthScale], \r\n" +
            "  cc.[MinZoomVelocity], \r\n" +
            "  cc.[MaxZoomVelocity], \r\n" +
            "  cc.[MinZoomSpeed], \r\n" +
            "  cc.[MaxZoomSpeed], \r\n" +
            "  cc.[ImageSensorWidth], \r\n" +
            "  cc.[ImageSensorHeight], \r\n" +
            "  cc.[HomePanAngle], \r\n" +
            "  cc.[HomeTiltAngle], \r\n" +
            "  cc.[HomeFocalLength], \r\n" +
            "  cc.[PanOffset], \r\n" +
            "  cc.[TiltOffset], \r\n" +
            "  cc.[AimAltitude], \r\n" +
            "  cc.[MinimumTargetWidth], \r\n" +
            "  cc.[TargetLockTimeout], \r\n" +
            "  cc.[UpdateStatusInterval], \r\n" +
            "  cc.[ReadTimeout], \r\n" +
            "  cc.[MoveCommandStatusDelay], \r\n" +
            "  cc.[PtzProfileName], \r\n" +
            "  cc.[PtzConfigurationToken], \r\n" +
            "  cc.[VideoSourceToken] \r\n" +
            "FROM [CameraConfigurationView] cc \r\n";

        public const string BaseViewName = "CameraConfigurationView";
        public const string ViewAliasName = "cc";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int CAMERA_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int CAMERACONTROLPROTOCOL_FIELD_ID = 4;
        public const int CAMERAURL_FIELD_ID = 5;
        public const int CONFIGURATIONURL_FIELD_ID = 6;
        public const int USERNAME_FIELD_ID = 7;
        public const int PASSWORD_FIELD_ID = 8;
        public const int USERTSPURIOVERRIDE_FIELD_ID = 9;
        public const int RTSPURIOVERRIDE_FIELD_ID = 10;
        public const int LATITUDE_FIELD_ID = 11;
        public const int LONGITUDE_FIELD_ID = 12;
        public const int ALTITUDE_FIELD_ID = 13;
        public const int USERELATIVEPOSITION_FIELD_ID = 14;
        public const int PANTILTMODE_FIELD_ID = 15;
        public const int MINTILTANGLE_FIELD_ID = 16;
        public const int MAXTILTANGLE_FIELD_ID = 17;
        public const int MINTILTSCALEANGLE_FIELD_ID = 18;
        public const int MAXTILTSCALEANGLE_FIELD_ID = 19;
        public const int USEREVERSETILTANGLE_FIELD_ID = 20;
        public const int USEREVERSENORMALIZEDTILTANGLE_FIELD_ID = 21;
        public const int MINTILTVELOCITY_FIELD_ID = 22;
        public const int MAXTILTVELOCITY_FIELD_ID = 23;
        public const int MINTILTSPEED_FIELD_ID = 24;
        public const int MAXTILTSPEED_FIELD_ID = 25;
        public const int MINPANANGLE_FIELD_ID = 26;
        public const int MAXPANANGLE_FIELD_ID = 27;
        public const int MINPANSCALEANGLE_FIELD_ID = 28;
        public const int MAXPANSCALEANGLE_FIELD_ID = 29;
        public const int USEREVERSEPANANGLE_FIELD_ID = 30;
        public const int USEREVERSENORMALIZEDPANANGLE_FIELD_ID = 31;
        public const int MINPANVELOCITY_FIELD_ID = 32;
        public const int MAXPANVELOCITY_FIELD_ID = 33;
        public const int MINPANSPEED_FIELD_ID = 34;
        public const int MAXPANSPEED_FIELD_ID = 35;
        public const int FOCALLENGTHMODE_FIELD_ID = 36;
        public const int MINFOCALLENGTH_FIELD_ID = 37;
        public const int MAXFOCALLENGTH_FIELD_ID = 38;
        public const int MINFOCALLENGTHSCALE_FIELD_ID = 39;
        public const int MAXFOCALLENGTHSCALE_FIELD_ID = 40;
        public const int MINZOOMVELOCITY_FIELD_ID = 41;
        public const int MAXZOOMVELOCITY_FIELD_ID = 42;
        public const int MINZOOMSPEED_FIELD_ID = 43;
        public const int MAXZOOMSPEED_FIELD_ID = 44;
        public const int IMAGESENSORWIDTH_FIELD_ID = 45;
        public const int IMAGESENSORHEIGHT_FIELD_ID = 46;
        public const int HOMEPANANGLE_FIELD_ID = 47;
        public const int HOMETILTANGLE_FIELD_ID = 48;
        public const int HOMEFOCALLENGTH_FIELD_ID = 49;
        public const int PANOFFSET_FIELD_ID = 50;
        public const int TILTOFFSET_FIELD_ID = 51;
        public const int AIMALTITUDE_FIELD_ID = 52;
        public const int MINIMUMTARGETWIDTH_FIELD_ID = 53;
        public const int TARGETLOCKTIMEOUT_FIELD_ID = 54;
        public const int UPDATESTATUSINTERVAL_FIELD_ID = 55;
        public const int READTIMEOUT_FIELD_ID = 56;
        public const int MOVECOMMANDSTATUSDELAY_FIELD_ID = 57;
        public const int PTZPROFILENAME_FIELD_ID = 58;
        public const int PTZCONFIGURATIONTOKEN_FIELD_ID = 59;
        public const int VIDEOSOURCETOKEN_FIELD_ID = 60;

        public SimpleCameraConfigurationDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Camera
        {
            get
            {
                return GetGuid( CAMERA_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Types.CameraControlProtocol CameraControlProtocol
        {
            get
            {
                return GetEnum<Types.CameraControlProtocol>( CAMERACONTROLPROTOCOL_FIELD_ID );
            }
        }
        public string CameraURL
        {
            get
            {
                return GetString( CAMERAURL_FIELD_ID );
            }
        }
        public string ConfigurationURL
        {
            get
            {
                return GetString( CONFIGURATIONURL_FIELD_ID );
            }
        }
        public string UserName
        {
            get
            {
                return GetString( USERNAME_FIELD_ID );
            }
        }
        public string Password
        {
            get
            {
                return GetString( PASSWORD_FIELD_ID );
            }
        }
        public bool UseRtspUriOverride
        {
            get
            {
                return GetBoolean( USERTSPURIOVERRIDE_FIELD_ID );
            }
        }
        public string RtspUriOverride
        {
            get
            {
                return GetString( RTSPURIOVERRIDE_FIELD_ID );
            }
        }
        public double Latitude
        {
            get
            {
                return GetDouble( LATITUDE_FIELD_ID );
            }
        }
        public double Longitude
        {
            get
            {
                return GetDouble( LONGITUDE_FIELD_ID );
            }
        }
        public double Altitude
        {
            get
            {
                return GetDouble( ALTITUDE_FIELD_ID );
            }
        }
        public bool UseRelativePosition
        {
            get
            {
                return GetBoolean( USERELATIVEPOSITION_FIELD_ID );
            }
        }
        public Types.CameraPanTiltMode PanTiltMode
        {
            get
            {
                return GetEnum<Types.CameraPanTiltMode>( PANTILTMODE_FIELD_ID );
            }
        }
        public double MinTiltAngle
        {
            get
            {
                return GetDouble( MINTILTANGLE_FIELD_ID );
            }
        }
        public double MaxTiltAngle
        {
            get
            {
                return GetDouble( MAXTILTANGLE_FIELD_ID );
            }
        }
        public double MinTiltScaleAngle
        {
            get
            {
                return GetDouble( MINTILTSCALEANGLE_FIELD_ID );
            }
        }
        public double MaxTiltScaleAngle
        {
            get
            {
                return GetDouble( MAXTILTSCALEANGLE_FIELD_ID );
            }
        }
        public bool UseReverseTiltAngle
        {
            get
            {
                return GetBoolean( USEREVERSETILTANGLE_FIELD_ID );
            }
        }
        public bool UseReverseNormalizedTiltAngle
        {
            get
            {
                return GetBoolean( USEREVERSENORMALIZEDTILTANGLE_FIELD_ID );
            }
        }
        public double MinTiltVelocity
        {
            get
            {
                return GetDouble( MINTILTVELOCITY_FIELD_ID );
            }
        }
        public double MaxTiltVelocity
        {
            get
            {
                return GetDouble( MAXTILTVELOCITY_FIELD_ID );
            }
        }
        public double MinTiltSpeed
        {
            get
            {
                return GetDouble( MINTILTSPEED_FIELD_ID );
            }
        }
        public double MaxTiltSpeed
        {
            get
            {
                return GetDouble( MAXTILTSPEED_FIELD_ID );
            }
        }
        public double MinPanAngle
        {
            get
            {
                return GetDouble( MINPANANGLE_FIELD_ID );
            }
        }
        public double MaxPanAngle
        {
            get
            {
                return GetDouble( MAXPANANGLE_FIELD_ID );
            }
        }
        public double MinPanScaleAngle
        {
            get
            {
                return GetDouble( MINPANSCALEANGLE_FIELD_ID );
            }
        }
        public double MaxPanScaleAngle
        {
            get
            {
                return GetDouble( MAXPANSCALEANGLE_FIELD_ID );
            }
        }
        public bool UseReversePanAngle
        {
            get
            {
                return GetBoolean( USEREVERSEPANANGLE_FIELD_ID );
            }
        }
        public bool UseReverseNormalizedPanAngle
        {
            get
            {
                return GetBoolean( USEREVERSENORMALIZEDPANANGLE_FIELD_ID );
            }
        }
        public double MinPanVelocity
        {
            get
            {
                return GetDouble( MINPANVELOCITY_FIELD_ID );
            }
        }
        public double MaxPanVelocity
        {
            get
            {
                return GetDouble( MAXPANVELOCITY_FIELD_ID );
            }
        }
        public double MinPanSpeed
        {
            get
            {
                return GetDouble( MINPANSPEED_FIELD_ID );
            }
        }
        public double MaxPanSpeed
        {
            get
            {
                return GetDouble( MAXPANSPEED_FIELD_ID );
            }
        }
        public Types.CameraFocalLengthMode FocalLengthMode
        {
            get
            {
                return GetEnum<Types.CameraFocalLengthMode>( FOCALLENGTHMODE_FIELD_ID );
            }
        }
        public double MinFocalLength
        {
            get
            {
                return GetDouble( MINFOCALLENGTH_FIELD_ID );
            }
        }
        public double MaxFocalLength
        {
            get
            {
                return GetDouble( MAXFOCALLENGTH_FIELD_ID );
            }
        }
        public double MinFocalLengthScale
        {
            get
            {
                return GetDouble( MINFOCALLENGTHSCALE_FIELD_ID );
            }
        }
        public double MaxFocalLengthScale
        {
            get
            {
                return GetDouble( MAXFOCALLENGTHSCALE_FIELD_ID );
            }
        }
        public double MinZoomVelocity
        {
            get
            {
                return GetDouble( MINZOOMVELOCITY_FIELD_ID );
            }
        }
        public double MaxZoomVelocity
        {
            get
            {
                return GetDouble( MAXZOOMVELOCITY_FIELD_ID );
            }
        }
        public double MinZoomSpeed
        {
            get
            {
                return GetDouble( MINZOOMSPEED_FIELD_ID );
            }
        }
        public double MaxZoomSpeed
        {
            get
            {
                return GetDouble( MAXZOOMSPEED_FIELD_ID );
            }
        }
        public double ImageSensorWidth
        {
            get
            {
                return GetDouble( IMAGESENSORWIDTH_FIELD_ID );
            }
        }
        public double ImageSensorHeight
        {
            get
            {
                return GetDouble( IMAGESENSORHEIGHT_FIELD_ID );
            }
        }
        public double HomePanAngle
        {
            get
            {
                return GetDouble( HOMEPANANGLE_FIELD_ID );
            }
        }
        public double HomeTiltAngle
        {
            get
            {
                return GetDouble( HOMETILTANGLE_FIELD_ID );
            }
        }
        public double HomeFocalLength
        {
            get
            {
                return GetDouble( HOMEFOCALLENGTH_FIELD_ID );
            }
        }
        public double PanOffset
        {
            get
            {
                return GetDouble( PANOFFSET_FIELD_ID );
            }
        }
        public double TiltOffset
        {
            get
            {
                return GetDouble( TILTOFFSET_FIELD_ID );
            }
        }
        public double AimAltitude
        {
            get
            {
                return GetDouble( AIMALTITUDE_FIELD_ID );
            }
        }
        public double MinimumTargetWidth
        {
            get
            {
                return GetDouble( MINIMUMTARGETWIDTH_FIELD_ID );
            }
        }
        public TimeSpan TargetLockTimeout
        {
            get
            {
                return new TimeSpan( GetInt64( TARGETLOCKTIMEOUT_FIELD_ID ) );
            }
        }
        public TimeSpan UpdateStatusInterval
        {
            get
            {
                return new TimeSpan( GetInt64( UPDATESTATUSINTERVAL_FIELD_ID ) );
            }
        }
        public TimeSpan ReadTimeout
        {
            get
            {
                return new TimeSpan( GetInt64( READTIMEOUT_FIELD_ID ) );
            }
        }
        public TimeSpan MoveCommandStatusDelay
        {
            get
            {
                return new TimeSpan( GetInt64( MOVECOMMANDSTATUSDELAY_FIELD_ID ) );
            }
        }
        public string PtzProfileName
        {
            get
            {
                return GetString( PTZPROFILENAME_FIELD_ID );
            }
        }
        public string PtzConfigurationToken
        {
            get
            {
                return GetString( PTZCONFIGURATIONTOKEN_FIELD_ID );
            }
        }
        public string VideoSourceToken
        {
            get
            {
                return GetString( VIDEOSOURCETOKEN_FIELD_ID );
            }
        }
    }

    public class SimpleCameraPanCalibrationDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  cpc.[Id], \r\n" +
            "  cpc.[RowVersion], \r\n" +
            "  cpc.[Camera], \r\n" +
            "  cpc.[Timestamp] \r\n" +
            "FROM [CameraPanCalibrationView] cpc \r\n";

        public const string BaseViewName = "CameraPanCalibrationView";
        public const string ViewAliasName = "cpc";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int CAMERA_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;

        public SimpleCameraPanCalibrationDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Camera
        {
            get
            {
                return GetGuid( CAMERA_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
    }

    public class SimpleCameraPanCalibrationValueDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  cpcv.[Id], \r\n" +
            "  cpcv.[RowVersion], \r\n" +
            "  cpcv.[PanCalibration], \r\n" +
            "  cpcv.[PanAngle], \r\n" +
            "  cpcv.[PanOffset] \r\n" +
            "FROM [CameraPanCalibrationValueView] cpcv \r\n";

        public const string BaseViewName = "CameraPanCalibrationValueView";
        public const string ViewAliasName = "cpcv";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int PANCALIBRATION_FIELD_ID = 2;
        public const int PANANGLE_FIELD_ID = 3;
        public const int PANOFFSET_FIELD_ID = 4;

        public SimpleCameraPanCalibrationValueDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid PanCalibration
        {
            get
            {
                return GetGuid( PANCALIBRATION_FIELD_ID );
            }
        }
        public double PanAngle
        {
            get
            {
                return GetDouble( PANANGLE_FIELD_ID );
            }
        }
        public double PanOffset
        {
            get
            {
                return GetDouble( PANOFFSET_FIELD_ID );
            }
        }
    }

    public class SimpleCameraStatusDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  cs.[Id], \r\n" +
            "  cs.[RowVersion], \r\n" +
            "  cs.[Camera], \r\n" +
            "  cs.[Track], \r\n" +
            "  cs.[Timestamp], \r\n" +
            "  cs.[PositionPanTiltMode], \r\n" +
            "  cs.[PanAngle], \r\n" +
            "  cs.[TiltAngle], \r\n" +
            "  cs.[PositionFocalLengthMode], \r\n" +
            "  cs.[FocalLength], \r\n" +
            "  cs.[PanTiltMoveStatus], \r\n" +
            "  cs.[ZoomMoveStatus], \r\n" +
            "  cs.[VelocityPanTiltMode], \r\n" +
            "  cs.[PanVelocity], \r\n" +
            "  cs.[TiltVelocity], \r\n" +
            "  cs.[VelocityFocalLengthMode], \r\n" +
            "  cs.[ZoomVelocity], \r\n" +
            "  cs.[ActiveFeatures], \r\n" +
            "  cs.[Error] \r\n" +
            "FROM [CameraStatusView] cs \r\n";

        public const string BaseViewName = "CameraStatusView";
        public const string ViewAliasName = "cs";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int CAMERA_FIELD_ID = 2;
        public const int TRACK_FIELD_ID = 3;
        public const int TIMESTAMP_FIELD_ID = 4;
        public const int POSITIONPANTILTMODE_FIELD_ID = 5;
        public const int PANANGLE_FIELD_ID = 6;
        public const int TILTANGLE_FIELD_ID = 7;
        public const int POSITIONFOCALLENGTHMODE_FIELD_ID = 8;
        public const int FOCALLENGTH_FIELD_ID = 9;
        public const int PANTILTMOVESTATUS_FIELD_ID = 10;
        public const int ZOOMMOVESTATUS_FIELD_ID = 11;
        public const int VELOCITYPANTILTMODE_FIELD_ID = 12;
        public const int PANVELOCITY_FIELD_ID = 13;
        public const int TILTVELOCITY_FIELD_ID = 14;
        public const int VELOCITYFOCALLENGTHMODE_FIELD_ID = 15;
        public const int ZOOMVELOCITY_FIELD_ID = 16;
        public const int ACTIVEFEATURES_FIELD_ID = 17;
        public const int ERROR_FIELD_ID = 18;

        public SimpleCameraStatusDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Camera
        {
            get
            {
                return GetGuid( CAMERA_FIELD_ID );
            }
        }
        public Guid Track
        {
            get
            {
                return GetGuid( TRACK_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Types.CameraPanTiltMode PositionPanTiltMode
        {
            get
            {
                return GetEnum<Types.CameraPanTiltMode>( POSITIONPANTILTMODE_FIELD_ID );
            }
        }
        public double PanAngle
        {
            get
            {
                return GetDouble( PANANGLE_FIELD_ID );
            }
        }
        public double TiltAngle
        {
            get
            {
                return GetDouble( TILTANGLE_FIELD_ID );
            }
        }
        public Types.CameraFocalLengthMode PositionFocalLengthMode
        {
            get
            {
                return GetEnum<Types.CameraFocalLengthMode>( POSITIONFOCALLENGTHMODE_FIELD_ID );
            }
        }
        public double FocalLength
        {
            get
            {
                return GetDouble( FOCALLENGTH_FIELD_ID );
            }
        }
        public Types.CameraMoveStatus PanTiltMoveStatus
        {
            get
            {
                return GetEnum<Types.CameraMoveStatus>( PANTILTMOVESTATUS_FIELD_ID );
            }
        }
        public Types.CameraMoveStatus ZoomMoveStatus
        {
            get
            {
                return GetEnum<Types.CameraMoveStatus>( ZOOMMOVESTATUS_FIELD_ID );
            }
        }
        public Types.CameraPanTiltMode VelocityPanTiltMode
        {
            get
            {
                return GetEnum<Types.CameraPanTiltMode>( VELOCITYPANTILTMODE_FIELD_ID );
            }
        }
        public double? PanVelocity
        {
            get
            {
                return GetNullableDouble( PANVELOCITY_FIELD_ID );
            }
        }
        public double? TiltVelocity
        {
            get
            {
                return GetNullableDouble( TILTVELOCITY_FIELD_ID );
            }
        }
        public Types.CameraFocalLengthMode VelocityFocalLengthMode
        {
            get
            {
                return GetEnum<Types.CameraFocalLengthMode>( VELOCITYFOCALLENGTHMODE_FIELD_ID );
            }
        }
        public double? ZoomVelocity
        {
            get
            {
                return GetNullableDouble( ZOOMVELOCITY_FIELD_ID );
            }
        }
        public Types.CameraFeatures ActiveFeatures
        {
            get
            {
                return GetEnum<Types.CameraFeatures>( ACTIVEFEATURES_FIELD_ID );
            }
        }
        public string Error
        {
            get
            {
                return GetString( ERROR_FIELD_ID );
            }
        }
    }

    public class SimpleCameraTiltCalibrationDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  ctc.[Id], \r\n" +
            "  ctc.[RowVersion], \r\n" +
            "  ctc.[Camera], \r\n" +
            "  ctc.[Timestamp] \r\n" +
            "FROM [CameraTiltCalibrationView] ctc \r\n";

        public const string BaseViewName = "CameraTiltCalibrationView";
        public const string ViewAliasName = "ctc";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int CAMERA_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;

        public SimpleCameraTiltCalibrationDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Camera
        {
            get
            {
                return GetGuid( CAMERA_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
    }

    public class SimpleCameraTiltCalibrationValueDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  ctcv.[Id], \r\n" +
            "  ctcv.[RowVersion], \r\n" +
            "  ctcv.[TiltCalibration], \r\n" +
            "  ctcv.[PanAngle], \r\n" +
            "  ctcv.[TiltOffset] \r\n" +
            "FROM [CameraTiltCalibrationValueView] ctcv \r\n";

        public const string BaseViewName = "CameraTiltCalibrationValueView";
        public const string ViewAliasName = "ctcv";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TILTCALIBRATION_FIELD_ID = 2;
        public const int PANANGLE_FIELD_ID = 3;
        public const int TILTOFFSET_FIELD_ID = 4;

        public SimpleCameraTiltCalibrationValueDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid TiltCalibration
        {
            get
            {
                return GetGuid( TILTCALIBRATION_FIELD_ID );
            }
        }
        public double PanAngle
        {
            get
            {
                return GetDouble( PANANGLE_FIELD_ID );
            }
        }
        public double TiltOffset
        {
            get
            {
                return GetDouble( TILTOFFSET_FIELD_ID );
            }
        }
    }

    public class SimpleCameraZoomCalibrationDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  czc.[Id], \r\n" +
            "  czc.[RowVersion], \r\n" +
            "  czc.[Camera], \r\n" +
            "  czc.[Timestamp] \r\n" +
            "FROM [CameraZoomCalibrationView] czc \r\n";

        public const string BaseViewName = "CameraZoomCalibrationView";
        public const string ViewAliasName = "czc";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int CAMERA_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;

        public SimpleCameraZoomCalibrationDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Camera
        {
            get
            {
                return GetGuid( CAMERA_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
    }

    public class SimpleCameraZoomCalibrationValueDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  czcv.[Id], \r\n" +
            "  czcv.[RowVersion], \r\n" +
            "  czcv.[ZoomCalibration], \r\n" +
            "  czcv.[FocalLength], \r\n" +
            "  czcv.[FocalLengthOffset] \r\n" +
            "FROM [CameraZoomCalibrationValueView] czcv \r\n";

        public const string BaseViewName = "CameraZoomCalibrationValueView";
        public const string ViewAliasName = "czcv";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int ZOOMCALIBRATION_FIELD_ID = 2;
        public const int FOCALLENGTH_FIELD_ID = 3;
        public const int FOCALLENGTHOFFSET_FIELD_ID = 4;

        public SimpleCameraZoomCalibrationValueDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid ZoomCalibration
        {
            get
            {
                return GetGuid( ZOOMCALIBRATION_FIELD_ID );
            }
        }
        public double FocalLength
        {
            get
            {
                return GetDouble( FOCALLENGTH_FIELD_ID );
            }
        }
        public double FocalLengthOffset
        {
            get
            {
                return GetDouble( FOCALLENGTHOFFSET_FIELD_ID );
            }
        }
    }

    public class SimpleCatalogElementDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  ce.[Id], \r\n" +
            "  ce.[EntityType], \r\n" +
            "  ce.[RowVersion], \r\n" +
            "  ce.[Catalog], \r\n" +
            "  ce.[Name] \r\n" +
            "FROM [CatalogElementView] ce \r\n";

        public const string BaseViewName = "CatalogElementView";
        public const string ViewAliasName = "ce";

        public const int ID_FIELD_ID = 0;
        public const int ENTITYTYPE_FIELD_ID = 1;
        public const int ROWVERSION_FIELD_ID = 2;
        public const int CATALOG_FIELD_ID = 3;
        public const int NAME_FIELD_ID = 4;

        public SimpleCatalogElementDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public Types.Kind EntityType
        {
            get
            {
                return GetEnum<Types.Kind>( ENTITYTYPE_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Catalog
        {
            get
            {
                return GetGuid( CATALOG_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
    }

    public class SimpleCatalogDataReader : SimpleCatalogElementDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  c.[Id], \r\n" +
            "  c.[EntityType], \r\n" +
            "  c.[RowVersion], \r\n" +
            "  c.[Catalog], \r\n" +
            "  c.[Name] \r\n" +
            "FROM [CatalogView] c \r\n";

        public new const string BaseViewName = "CatalogView";
        public new const string ViewAliasName = "c";

        public SimpleCatalogDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleElementDataReader : SimpleCatalogElementDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  e.[Id], \r\n" +
            "  e.[EntityType], \r\n" +
            "  e.[RowVersion], \r\n" +
            "  e.[Catalog], \r\n" +
            "  e.[Name], \r\n" +
            "  e.[ElementType] \r\n" +
            "FROM [ElementView] e \r\n";

        public new const string BaseViewName = "ElementView";
        public new const string ViewAliasName = "e";

        public const int ELEMENTTYPE_FIELD_ID = 4;

        public SimpleElementDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid ElementType
        {
            get
            {
                return GetGuid( ELEMENTTYPE_FIELD_ID );
            }
        }
    }

    public class SimpleCollectionInfoDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  ci.[Id], \r\n" +
            "  ci.[RowVersion], \r\n" +
            "  ci.[Count] \r\n" +
            "FROM [CollectionInfoView] ci \r\n";

        public const string BaseViewName = "CollectionInfoView";
        public const string ViewAliasName = "ci";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int COUNT_FIELD_ID = 2;

        public SimpleCollectionInfoDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public long Count
        {
            get
            {
                return GetInt64( COUNT_FIELD_ID );
            }
        }
    }

    public class SimpleCountryDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  c.[Id], \r\n" +
            "  c.[RowVersion], \r\n" +
            "  c.[Name], \r\n" +
            "  c.[Code], \r\n" +
            "  c.[Alpha2], \r\n" +
            "  c.[Alpha3] \r\n" +
            "FROM [CountryView] c \r\n";

        public const string BaseViewName = "CountryView";
        public const string ViewAliasName = "c";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int NAME_FIELD_ID = 2;
        public const int CODE_FIELD_ID = 3;
        public const int ALPHA2_FIELD_ID = 4;
        public const int ALPHA3_FIELD_ID = 5;

        public SimpleCountryDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
        public int Code
        {
            get
            {
                return GetInt32( CODE_FIELD_ID );
            }
        }
        public string Alpha2
        {
            get
            {
                return GetString( ALPHA2_FIELD_ID );
            }
        }
        public string Alpha3
        {
            get
            {
                return GetString( ALPHA3_FIELD_ID );
            }
        }
    }

    public class SimpleCursorInfoDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  ci.[Id], \r\n" +
            "  ci.[RowVersion], \r\n" +
            "  ci.[TypeCode] \r\n" +
            "FROM [CursorInfoView] ci \r\n";

        public const string BaseViewName = "CursorInfoView";
        public const string ViewAliasName = "ci";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TYPECODE_FIELD_ID = 2;

        public SimpleCursorInfoDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public int TypeCode
        {
            get
            {
                return GetInt32( TYPECODE_FIELD_ID );
            }
        }
    }

    public class SimpleDateTimeTimeseriesValueDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  dttv.[Id], \r\n" +
            "  dttv.[RowVersion], \r\n" +
            "  dttv.[Timeseries], \r\n" +
            "  dttv.[Timestamp], \r\n" +
            "  dttv.[Value] \r\n" +
            "FROM [DateTimeTimeseriesValueView] dttv \r\n";

        public const string BaseViewName = "DateTimeTimeseriesValueView";
        public const string ViewAliasName = "dttv";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TIMESERIES_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int VALUE_FIELD_ID = 4;

        public SimpleDateTimeTimeseriesValueDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public DateTime? Value
        {
            get
            {
                var v = GetNullableInt64( VALUE_FIELD_ID );
                if( v is long value )
                {
                    return new DateTime( value , DateTimeKind.Utc );
                }
                return null;
            }
        }
    }

    public class SimpleDeviceHostDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  dh.[Id], \r\n" +
            "  dh.[RowVersion], \r\n" +
            "  dh.[Name] \r\n" +
            "FROM [DeviceHostView] dh \r\n";

        public const string BaseViewName = "DeviceHostView";
        public const string ViewAliasName = "dh";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int NAME_FIELD_ID = 2;

        public SimpleDeviceHostDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
    }

    public class SimpleDeviceHostConfigurationDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  dhc.[Id], \r\n" +
            "  dhc.[RowVersion], \r\n" +
            "  dhc.[Host], \r\n" +
            "  dhc.[Timestamp], \r\n" +
            "  dhc.[Hostname], \r\n" +
            "  dhc.[Port], \r\n" +
            "  dhc.[QueueName] \r\n" +
            "FROM [DeviceHostConfigurationView] dhc \r\n";

        public const string BaseViewName = "DeviceHostConfigurationView";
        public const string ViewAliasName = "dhc";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int HOST_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int HOSTNAME_FIELD_ID = 4;
        public const int PORT_FIELD_ID = 5;
        public const int QUEUENAME_FIELD_ID = 6;

        public SimpleDeviceHostConfigurationDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Host
        {
            get
            {
                return GetGuid( HOST_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public string Hostname
        {
            get
            {
                return GetString( HOSTNAME_FIELD_ID );
            }
        }
        public int Port
        {
            get
            {
                return GetInt32( PORT_FIELD_ID );
            }
        }
        public string QueueName
        {
            get
            {
                return GetString( QUEUENAME_FIELD_ID );
            }
        }
    }

    public class SimpleDoubleTimeseriesValueDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  dtv.[Id], \r\n" +
            "  dtv.[RowVersion], \r\n" +
            "  dtv.[Timeseries], \r\n" +
            "  dtv.[Timestamp], \r\n" +
            "  dtv.[Value] \r\n" +
            "FROM [DoubleTimeseriesValueView] dtv \r\n";

        public const string BaseViewName = "DoubleTimeseriesValueView";
        public const string ViewAliasName = "dtv";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TIMESERIES_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int VALUE_FIELD_ID = 4;

        public SimpleDoubleTimeseriesValueDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public double? Value
        {
            get
            {
                return GetNullableDouble( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleFacilityTypeDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  ft.[Id], \r\n" +
            "  ft.[RowVersion], \r\n" +
            "  ft.[Name] \r\n" +
            "FROM [FacilityTypeView] ft \r\n";

        public const string BaseViewName = "FacilityTypeView";
        public const string ViewAliasName = "ft";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int NAME_FIELD_ID = 2;

        public SimpleFacilityTypeDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
    }

    public class SimpleGeoPosition2DTimeseriesValueDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  gp2dv.[Id], \r\n" +
            "  gp2dv.[RowVersion], \r\n" +
            "  gp2dv.[Timeseries], \r\n" +
            "  gp2dv.[Timestamp], \r\n" +
            "  gp2dv.[Latitude], \r\n" +
            "  gp2dv.[Longitude] \r\n" +
            "FROM [GeoPosition2DTimeseriesValueView] gp2dv \r\n";

        public const string BaseViewName = "GeoPosition2DTimeseriesValueView";
        public const string ViewAliasName = "gp2dv";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TIMESERIES_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int LATITUDE_FIELD_ID = 4;
        public const int LONGITUDE_FIELD_ID = 5;

        public SimpleGeoPosition2DTimeseriesValueDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public double? Latitude
        {
            get
            {
                return GetNullableDouble( LATITUDE_FIELD_ID );
            }
        }
        public double? Longitude
        {
            get
            {
                return GetNullableDouble( LONGITUDE_FIELD_ID );
            }
        }
    }

    public class SimpleGeoPosition3DTimeseriesValueDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  gp3dv.[Id], \r\n" +
            "  gp3dv.[RowVersion], \r\n" +
            "  gp3dv.[Timeseries], \r\n" +
            "  gp3dv.[Timestamp], \r\n" +
            "  gp3dv.[Latitude], \r\n" +
            "  gp3dv.[Longitude], \r\n" +
            "  gp3dv.[Altitude] \r\n" +
            "FROM [GeoPosition3DTimeseriesValueView] gp3dv \r\n";

        public const string BaseViewName = "GeoPosition3DTimeseriesValueView";
        public const string ViewAliasName = "gp3dv";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TIMESERIES_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int LATITUDE_FIELD_ID = 4;
        public const int LONGITUDE_FIELD_ID = 5;
        public const int ALTITUDE_FIELD_ID = 6;

        public SimpleGeoPosition3DTimeseriesValueDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public double? Latitude
        {
            get
            {
                return GetNullableDouble( LATITUDE_FIELD_ID );
            }
        }
        public double? Longitude
        {
            get
            {
                return GetNullableDouble( LONGITUDE_FIELD_ID );
            }
        }
        public double? Altitude
        {
            get
            {
                return GetNullableDouble( ALTITUDE_FIELD_ID );
            }
        }
    }

    public class SimpleGNSSDeviceCommandDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  gc.[Id], \r\n" +
            "  gc.[RowVersion], \r\n" +
            "  gc.[GNSSDevice], \r\n" +
            "  gc.[Timestamp], \r\n" +
            "  gc.[DeviceCommandSourceType], \r\n" +
            "  gc.[DeviceCommandSourceId], \r\n" +
            "  gc.[Reply] \r\n" +
            "FROM [GNSSDeviceCommandView] gc \r\n";

        public const string BaseViewName = "GNSSDeviceCommandView";
        public const string ViewAliasName = "gc";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int GNSSDEVICE_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int DEVICECOMMANDSOURCETYPE_FIELD_ID = 4;
        public const int DEVICECOMMANDSOURCEID_FIELD_ID = 5;
        public const int REPLY_FIELD_ID = 6;

        public SimpleGNSSDeviceCommandDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid GNSSDevice
        {
            get
            {
                return GetGuid( GNSSDEVICE_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Types.DeviceCommandSourceType DeviceCommandSourceType
        {
            get
            {
                return GetEnum<Types.DeviceCommandSourceType>( DEVICECOMMANDSOURCETYPE_FIELD_ID );
            }
        }
        public Guid DeviceCommandSourceId
        {
            get
            {
                return GetGuid( DEVICECOMMANDSOURCEID_FIELD_ID );
            }
        }
        public Guid Reply
        {
            get
            {
                return GetGuid( REPLY_FIELD_ID );
            }
        }
    }

    public class SimpleGNSSDeviceCommandReplyDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  gcr.[Id], \r\n" +
            "  gcr.[RowVersion], \r\n" +
            "  gcr.[GNSSDevice], \r\n" +
            "  gcr.[Timestamp], \r\n" +
            "  gcr.[Command], \r\n" +
            "  gcr.[Status], \r\n" +
            "  gcr.[Message] \r\n" +
            "FROM [GNSSDeviceCommandReplyView] gcr \r\n";

        public const string BaseViewName = "GNSSDeviceCommandReplyView";
        public const string ViewAliasName = "gcr";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int GNSSDEVICE_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int COMMAND_FIELD_ID = 4;
        public const int STATUS_FIELD_ID = 5;
        public const int MESSAGE_FIELD_ID = 6;

        public SimpleGNSSDeviceCommandReplyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid GNSSDevice
        {
            get
            {
                return GetGuid( GNSSDEVICE_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Guid Command
        {
            get
            {
                return GetGuid( COMMAND_FIELD_ID );
            }
        }
        public Types.DeviceCommandReplyStatus Status
        {
            get
            {
                return GetEnum<Types.DeviceCommandReplyStatus>( STATUS_FIELD_ID );
            }
        }
        public string Message
        {
            get
            {
                return GetString( MESSAGE_FIELD_ID );
            }
        }
    }

    public class SimpleGNSSDeviceConfigurationDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  gc.[Id], \r\n" +
            "  gc.[RowVersion], \r\n" +
            "  gc.[GNSSDevice], \r\n" +
            "  gc.[Timestamp], \r\n" +
            "  gc.[DefaultLatitude], \r\n" +
            "  gc.[DefaultLongitude], \r\n" +
            "  gc.[DefaultAltitude], \r\n" +
            "  gc.[LatitudeOffset], \r\n" +
            "  gc.[LongitudeOffset], \r\n" +
            "  gc.[AltitudeOffset] \r\n" +
            "FROM [GNSSDeviceConfigurationView] gc \r\n";

        public const string BaseViewName = "GNSSDeviceConfigurationView";
        public const string ViewAliasName = "gc";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int GNSSDEVICE_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int DEFAULTLATITUDE_FIELD_ID = 4;
        public const int DEFAULTLONGITUDE_FIELD_ID = 5;
        public const int DEFAULTALTITUDE_FIELD_ID = 6;
        public const int LATITUDEOFFSET_FIELD_ID = 7;
        public const int LONGITUDEOFFSET_FIELD_ID = 8;
        public const int ALTITUDEOFFSET_FIELD_ID = 9;

        public SimpleGNSSDeviceConfigurationDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid GNSSDevice
        {
            get
            {
                return GetGuid( GNSSDEVICE_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public double DefaultLatitude
        {
            get
            {
                return GetDouble( DEFAULTLATITUDE_FIELD_ID );
            }
        }
        public double DefaultLongitude
        {
            get
            {
                return GetDouble( DEFAULTLONGITUDE_FIELD_ID );
            }
        }
        public double DefaultAltitude
        {
            get
            {
                return GetDouble( DEFAULTALTITUDE_FIELD_ID );
            }
        }
        public double LatitudeOffset
        {
            get
            {
                return GetDouble( LATITUDEOFFSET_FIELD_ID );
            }
        }
        public double LongitudeOffset
        {
            get
            {
                return GetDouble( LONGITUDEOFFSET_FIELD_ID );
            }
        }
        public double AltitudeOffset
        {
            get
            {
                return GetDouble( ALTITUDEOFFSET_FIELD_ID );
            }
        }
    }

    public class SimpleGuidTimeseriesValueDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  gtv.[Id], \r\n" +
            "  gtv.[RowVersion], \r\n" +
            "  gtv.[Timeseries], \r\n" +
            "  gtv.[Timestamp], \r\n" +
            "  gtv.[Value] \r\n" +
            "FROM [GuidTimeseriesValueView] gtv \r\n";

        public const string BaseViewName = "GuidTimeseriesValueView";
        public const string ViewAliasName = "gtv";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TIMESERIES_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int VALUE_FIELD_ID = 4;

        public SimpleGuidTimeseriesValueDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Guid? Value
        {
            get
            {
                return GetNullableGuid( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleGyroDeviceCommandDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  gdc.[Id], \r\n" +
            "  gdc.[RowVersion], \r\n" +
            "  gdc.[GyroDevice], \r\n" +
            "  gdc.[Timestamp], \r\n" +
            "  gdc.[DeviceCommandSourceType], \r\n" +
            "  gdc.[DeviceCommandSourceId], \r\n" +
            "  gdc.[Reply] \r\n" +
            "FROM [GyroDeviceCommandView] gdc \r\n";

        public const string BaseViewName = "GyroDeviceCommandView";
        public const string ViewAliasName = "gdc";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int GYRODEVICE_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int DEVICECOMMANDSOURCETYPE_FIELD_ID = 4;
        public const int DEVICECOMMANDSOURCEID_FIELD_ID = 5;
        public const int REPLY_FIELD_ID = 6;

        public SimpleGyroDeviceCommandDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid GyroDevice
        {
            get
            {
                return GetGuid( GYRODEVICE_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Types.DeviceCommandSourceType DeviceCommandSourceType
        {
            get
            {
                return GetEnum<Types.DeviceCommandSourceType>( DEVICECOMMANDSOURCETYPE_FIELD_ID );
            }
        }
        public Guid DeviceCommandSourceId
        {
            get
            {
                return GetGuid( DEVICECOMMANDSOURCEID_FIELD_ID );
            }
        }
        public Guid Reply
        {
            get
            {
                return GetGuid( REPLY_FIELD_ID );
            }
        }
    }

    public class SimpleGyroDeviceCommandReplyDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  gdcr.[Id], \r\n" +
            "  gdcr.[RowVersion], \r\n" +
            "  gdcr.[GyroDevice], \r\n" +
            "  gdcr.[Timestamp], \r\n" +
            "  gdcr.[Command], \r\n" +
            "  gdcr.[Status], \r\n" +
            "  gdcr.[Message] \r\n" +
            "FROM [GyroDeviceCommandReplyView] gdcr \r\n";

        public const string BaseViewName = "GyroDeviceCommandReplyView";
        public const string ViewAliasName = "gdcr";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int GYRODEVICE_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int COMMAND_FIELD_ID = 4;
        public const int STATUS_FIELD_ID = 5;
        public const int MESSAGE_FIELD_ID = 6;

        public SimpleGyroDeviceCommandReplyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid GyroDevice
        {
            get
            {
                return GetGuid( GYRODEVICE_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Guid Command
        {
            get
            {
                return GetGuid( COMMAND_FIELD_ID );
            }
        }
        public Types.DeviceCommandReplyStatus Status
        {
            get
            {
                return GetEnum<Types.DeviceCommandReplyStatus>( STATUS_FIELD_ID );
            }
        }
        public string Message
        {
            get
            {
                return GetString( MESSAGE_FIELD_ID );
            }
        }
    }

    public class SimpleGyroDeviceConfigurationDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  gdc.[Id], \r\n" +
            "  gdc.[RowVersion], \r\n" +
            "  gdc.[GyroDevice], \r\n" +
            "  gdc.[Timestamp], \r\n" +
            "  gdc.[DefaultHeadingTrueNorth], \r\n" +
            "  gdc.[DefaultMagneticTrueNorth], \r\n" +
            "  gdc.[HeadingTrueNorthOffset], \r\n" +
            "  gdc.[HeadingMagneticNorthOffset], \r\n" +
            "  gdc.[PitchTransducerName], \r\n" +
            "  gdc.[RollTransducerName] \r\n" +
            "FROM [GyroDeviceConfigurationView] gdc \r\n";

        public const string BaseViewName = "GyroDeviceConfigurationView";
        public const string ViewAliasName = "gdc";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int GYRODEVICE_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int DEFAULTHEADINGTRUENORTH_FIELD_ID = 4;
        public const int DEFAULTMAGNETICTRUENORTH_FIELD_ID = 5;
        public const int HEADINGTRUENORTHOFFSET_FIELD_ID = 6;
        public const int HEADINGMAGNETICNORTHOFFSET_FIELD_ID = 7;
        public const int PITCHTRANSDUCERNAME_FIELD_ID = 8;
        public const int ROLLTRANSDUCERNAME_FIELD_ID = 9;

        public SimpleGyroDeviceConfigurationDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid GyroDevice
        {
            get
            {
                return GetGuid( GYRODEVICE_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public double DefaultHeadingTrueNorth
        {
            get
            {
                return GetDouble( DEFAULTHEADINGTRUENORTH_FIELD_ID );
            }
        }
        public double DefaultMagneticTrueNorth
        {
            get
            {
                return GetDouble( DEFAULTMAGNETICTRUENORTH_FIELD_ID );
            }
        }
        public double HeadingTrueNorthOffset
        {
            get
            {
                return GetDouble( HEADINGTRUENORTHOFFSET_FIELD_ID );
            }
        }
        public double HeadingMagneticNorthOffset
        {
            get
            {
                return GetDouble( HEADINGMAGNETICNORTHOFFSET_FIELD_ID );
            }
        }
        public string PitchTransducerName
        {
            get
            {
                return GetString( PITCHTRANSDUCERNAME_FIELD_ID );
            }
        }
        public string RollTransducerName
        {
            get
            {
                return GetString( ROLLTRANSDUCERNAME_FIELD_ID );
            }
        }
    }

    public class SimpleIdentityDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  i.[Id], \r\n" +
            "  i.[EntityType], \r\n" +
            "  i.[RowVersion] \r\n" +
            "FROM [IdentityView] i \r\n";

        public const string BaseViewName = "IdentityView";
        public const string ViewAliasName = "i";

        public const int ID_FIELD_ID = 0;
        public const int ENTITYTYPE_FIELD_ID = 1;
        public const int ROWVERSION_FIELD_ID = 2;

        public SimpleIdentityDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public Types.Kind EntityType
        {
            get
            {
                return GetEnum<Types.Kind>( ENTITYTYPE_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
    }

    public class SimpleCallsignDataReader : SimpleIdentityDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  c.[Id], \r\n" +
            "  c.[EntityType], \r\n" +
            "  c.[RowVersion], \r\n" +
            "  c.[Identifier] \r\n" +
            "FROM [CallsignView] c \r\n";

        public new const string BaseViewName = "CallsignView";
        public new const string ViewAliasName = "c";

        public const int IDENTIFIER_FIELD_ID = 2;

        public SimpleCallsignDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public string Identifier
        {
            get
            {
                return GetString( IDENTIFIER_FIELD_ID );
            }
        }
    }

    public class SimpleInternationalMaritimeOrganizationNumberDataReader : SimpleIdentityDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  imon.[Id], \r\n" +
            "  imon.[EntityType], \r\n" +
            "  imon.[RowVersion], \r\n" +
            "  imon.[Identifier] \r\n" +
            "FROM [InternationalMaritimeOrganizationNumberView] imon \r\n";

        public new const string BaseViewName = "InternationalMaritimeOrganizationNumberView";
        public new const string ViewAliasName = "imon";

        public const int IDENTIFIER_FIELD_ID = 2;

        public SimpleInternationalMaritimeOrganizationNumberDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public long Identifier
        {
            get
            {
                return GetInt64( IDENTIFIER_FIELD_ID );
            }
        }
    }

    public class SimpleMaritimeMobileServiceIdentityDataReader : SimpleIdentityDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  mmsi.[Id], \r\n" +
            "  mmsi.[EntityType], \r\n" +
            "  mmsi.[RowVersion], \r\n" +
            "  mmsi.[Identifier] \r\n" +
            "FROM [MaritimeMobileServiceIdentityView] mmsi \r\n";

        public new const string BaseViewName = "MaritimeMobileServiceIdentityView";
        public new const string ViewAliasName = "mmsi";

        public const int IDENTIFIER_FIELD_ID = 2;

        public SimpleMaritimeMobileServiceIdentityDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public long Identifier
        {
            get
            {
                return GetInt64( IDENTIFIER_FIELD_ID );
            }
        }
    }

    public class SimpleNameDataReader : SimpleIdentityDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  n.[Id], \r\n" +
            "  n.[EntityType], \r\n" +
            "  n.[RowVersion], \r\n" +
            "  n.[Text] \r\n" +
            "FROM [NameView] n \r\n";

        public new const string BaseViewName = "NameView";
        public new const string ViewAliasName = "n";

        public const int TEXT_FIELD_ID = 2;

        public SimpleNameDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public string Text
        {
            get
            {
                return GetString( TEXT_FIELD_ID );
            }
        }
    }

    public class SimpleInt16TimeseriesValueDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  i16tv.[Id], \r\n" +
            "  i16tv.[RowVersion], \r\n" +
            "  i16tv.[Timeseries], \r\n" +
            "  i16tv.[Timestamp], \r\n" +
            "  i16tv.[Value] \r\n" +
            "FROM [Int16TimeseriesValueView] i16tv \r\n";

        public const string BaseViewName = "Int16TimeseriesValueView";
        public const string ViewAliasName = "i16tv";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TIMESERIES_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int VALUE_FIELD_ID = 4;

        public SimpleInt16TimeseriesValueDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public short? Value
        {
            get
            {
                return GetNullableInt16( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleInt32TimeseriesValueDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  i32tv.[Id], \r\n" +
            "  i32tv.[RowVersion], \r\n" +
            "  i32tv.[Timeseries], \r\n" +
            "  i32tv.[Timestamp], \r\n" +
            "  i32tv.[Value] \r\n" +
            "FROM [Int32TimeseriesValueView] i32tv \r\n";

        public const string BaseViewName = "Int32TimeseriesValueView";
        public const string ViewAliasName = "i32tv";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TIMESERIES_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int VALUE_FIELD_ID = 4;

        public SimpleInt32TimeseriesValueDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public int? Value
        {
            get
            {
                return GetNullableInt32( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleInt64TimeseriesValueDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  i64tv.[Id], \r\n" +
            "  i64tv.[RowVersion], \r\n" +
            "  i64tv.[Timeseries], \r\n" +
            "  i64tv.[Timestamp], \r\n" +
            "  i64tv.[Value] \r\n" +
            "FROM [Int64TimeseriesValueView] i64tv \r\n";

        public const string BaseViewName = "Int64TimeseriesValueView";
        public const string ViewAliasName = "i64tv";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TIMESERIES_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int VALUE_FIELD_ID = 4;

        public SimpleInt64TimeseriesValueDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public long? Value
        {
            get
            {
                return GetNullableInt64( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleItemDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  i.[Id], \r\n" +
            "  i.[EntityType], \r\n" +
            "  i.[RowVersion] \r\n" +
            "FROM [ItemView] i \r\n";

        public const string BaseViewName = "ItemView";
        public const string ViewAliasName = "i";

        public const int ID_FIELD_ID = 0;
        public const int ENTITYTYPE_FIELD_ID = 1;
        public const int ROWVERSION_FIELD_ID = 2;

        public SimpleItemDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public Types.Kind EntityType
        {
            get
            {
                return GetEnum<Types.Kind>( ENTITYTYPE_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
    }

    public class SimpleBaseStationDataReader : SimpleItemDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  bs.[Id], \r\n" +
            "  bs.[EntityType], \r\n" +
            "  bs.[RowVersion], \r\n" +
            "  bs.[Name], \r\n" +
            "  bs.[Type] \r\n" +
            "FROM [BaseStationView] bs \r\n";

        public new const string BaseViewName = "BaseStationView";
        public new const string ViewAliasName = "bs";

        public const int NAME_FIELD_ID = 2;
        public const int TYPE_FIELD_ID = 3;

        public SimpleBaseStationDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
        public Guid Type
        {
            get
            {
                return GetGuid( TYPE_FIELD_ID );
            }
        }
    }

    public class SimpleDeviceDataReader : SimpleItemDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  d.[Id], \r\n" +
            "  d.[EntityType], \r\n" +
            "  d.[RowVersion], \r\n" +
            "  d.[Host], \r\n" +
            "  d.[Name], \r\n" +
            "  d.[Description], \r\n" +
            "  d.[EnabledTimeseries] \r\n" +
            "FROM [DeviceView] d \r\n";

        public new const string BaseViewName = "DeviceView";
        public new const string ViewAliasName = "d";

        public const int HOST_FIELD_ID = 2;
        public const int NAME_FIELD_ID = 3;
        public const int DESCRIPTION_FIELD_ID = 4;
        public const int ENABLEDTIMESERIES_FIELD_ID = 5;

        public SimpleDeviceDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Host
        {
            get
            {
                return GetGuid( HOST_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
        public string Description
        {
            get
            {
                return GetString( DESCRIPTION_FIELD_ID );
            }
        }
        public Guid EnabledTimeseries
        {
            get
            {
                return GetGuid( ENABLEDTIMESERIES_FIELD_ID );
            }
        }
    }

    public class SimpleCameraDeviceDataReader : SimpleDeviceDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  cd.[Id], \r\n" +
            "  cd.[EntityType], \r\n" +
            "  cd.[RowVersion], \r\n" +
            "  cd.[Host], \r\n" +
            "  cd.[Name], \r\n" +
            "  cd.[Description], \r\n" +
            "  cd.[EnabledTimeseries] \r\n" +
            "FROM [CameraDeviceView] cd \r\n";

        public new const string BaseViewName = "CameraDeviceView";
        public new const string ViewAliasName = "cd";

        public SimpleCameraDeviceDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleGNSSDeviceDataReader : SimpleDeviceDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  g.[Id], \r\n" +
            "  g.[EntityType], \r\n" +
            "  g.[RowVersion], \r\n" +
            "  g.[Host], \r\n" +
            "  g.[Name], \r\n" +
            "  g.[Description], \r\n" +
            "  g.[EnabledTimeseries], \r\n" +
            "  g.[LatitudeTimeseries], \r\n" +
            "  g.[LongitudeTimeseries], \r\n" +
            "  g.[AltitudeTimeseries] \r\n" +
            "FROM [GNSSDeviceView] g \r\n";

        public new const string BaseViewName = "GNSSDeviceView";
        public new const string ViewAliasName = "g";

        public const int LATITUDETIMESERIES_FIELD_ID = 6;
        public const int LONGITUDETIMESERIES_FIELD_ID = 7;
        public const int ALTITUDETIMESERIES_FIELD_ID = 8;

        public SimpleGNSSDeviceDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid LatitudeTimeseries
        {
            get
            {
                return GetGuid( LATITUDETIMESERIES_FIELD_ID );
            }
        }
        public Guid LongitudeTimeseries
        {
            get
            {
                return GetGuid( LONGITUDETIMESERIES_FIELD_ID );
            }
        }
        public Guid AltitudeTimeseries
        {
            get
            {
                return GetGuid( ALTITUDETIMESERIES_FIELD_ID );
            }
        }
    }

    public class SimpleGyroDeviceDataReader : SimpleDeviceDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  gd.[Id], \r\n" +
            "  gd.[EntityType], \r\n" +
            "  gd.[RowVersion], \r\n" +
            "  gd.[Host], \r\n" +
            "  gd.[Name], \r\n" +
            "  gd.[Description], \r\n" +
            "  gd.[EnabledTimeseries], \r\n" +
            "  gd.[HeadingTrueNorthTimeseries], \r\n" +
            "  gd.[HeadingMagneticNorthTimeseries], \r\n" +
            "  gd.[PitchTimeseries], \r\n" +
            "  gd.[RateOfTurnTimeseries], \r\n" +
            "  gd.[RollTimeseries], \r\n" +
            "  gd.[CourseTimeseries], \r\n" +
            "  gd.[SpeedTimeseries], \r\n" +
            "  gd.[GNSSDevice] \r\n" +
            "FROM [GyroDeviceView] gd \r\n";

        public new const string BaseViewName = "GyroDeviceView";
        public new const string ViewAliasName = "gd";

        public const int HEADINGTRUENORTHTIMESERIES_FIELD_ID = 6;
        public const int HEADINGMAGNETICNORTHTIMESERIES_FIELD_ID = 7;
        public const int PITCHTIMESERIES_FIELD_ID = 8;
        public const int RATEOFTURNTIMESERIES_FIELD_ID = 9;
        public const int ROLLTIMESERIES_FIELD_ID = 10;
        public const int COURSETIMESERIES_FIELD_ID = 11;
        public const int SPEEDTIMESERIES_FIELD_ID = 12;
        public const int GNSSDEVICE_FIELD_ID = 13;

        public SimpleGyroDeviceDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid HeadingTrueNorthTimeseries
        {
            get
            {
                return GetGuid( HEADINGTRUENORTHTIMESERIES_FIELD_ID );
            }
        }
        public Guid HeadingMagneticNorthTimeseries
        {
            get
            {
                return GetGuid( HEADINGMAGNETICNORTHTIMESERIES_FIELD_ID );
            }
        }
        public Guid PitchTimeseries
        {
            get
            {
                return GetGuid( PITCHTIMESERIES_FIELD_ID );
            }
        }
        public Guid RateOfTurnTimeseries
        {
            get
            {
                return GetGuid( RATEOFTURNTIMESERIES_FIELD_ID );
            }
        }
        public Guid RollTimeseries
        {
            get
            {
                return GetGuid( ROLLTIMESERIES_FIELD_ID );
            }
        }
        public Guid CourseTimeseries
        {
            get
            {
                return GetGuid( COURSETIMESERIES_FIELD_ID );
            }
        }
        public Guid SpeedTimeseries
        {
            get
            {
                return GetGuid( SPEEDTIMESERIES_FIELD_ID );
            }
        }
        public Guid GNSSDevice
        {
            get
            {
                return GetGuid( GNSSDEVICE_FIELD_ID );
            }
        }
    }

    public class SimpleLineInputDeviceDataReader : SimpleDeviceDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  lid.[Id], \r\n" +
            "  lid.[EntityType], \r\n" +
            "  lid.[RowVersion], \r\n" +
            "  lid.[Host], \r\n" +
            "  lid.[Name], \r\n" +
            "  lid.[Description], \r\n" +
            "  lid.[EnabledTimeseries] \r\n" +
            "FROM [LineInputDeviceView] lid \r\n";

        public new const string BaseViewName = "LineInputDeviceView";
        public new const string ViewAliasName = "lid";

        public SimpleLineInputDeviceDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleOilSpillDetectorDeviceDataReader : SimpleDeviceDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  osdd.[Id], \r\n" +
            "  osdd.[EntityType], \r\n" +
            "  osdd.[RowVersion], \r\n" +
            "  osdd.[Host], \r\n" +
            "  osdd.[Name], \r\n" +
            "  osdd.[Description], \r\n" +
            "  osdd.[EnabledTimeseries] \r\n" +
            "FROM [OilSpillDetectorDeviceView] osdd \r\n";

        public new const string BaseViewName = "OilSpillDetectorDeviceView";
        public new const string ViewAliasName = "osdd";

        public SimpleOilSpillDetectorDeviceDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleRadioDeviceDataReader : SimpleDeviceDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rdi.[Id], \r\n" +
            "  rdi.[EntityType], \r\n" +
            "  rdi.[RowVersion], \r\n" +
            "  rdi.[Host], \r\n" +
            "  rdi.[Name], \r\n" +
            "  rdi.[Description], \r\n" +
            "  rdi.[EnabledTimeseries] \r\n" +
            "FROM [RadioDeviceView] rdi \r\n";

        public new const string BaseViewName = "RadioDeviceView";
        public new const string ViewAliasName = "rdi";

        public SimpleRadioDeviceDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleRadomeDeviceDataReader : SimpleDeviceDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rdo.[Id], \r\n" +
            "  rdo.[EntityType], \r\n" +
            "  rdo.[RowVersion], \r\n" +
            "  rdo.[Host], \r\n" +
            "  rdo.[Name], \r\n" +
            "  rdo.[Description], \r\n" +
            "  rdo.[EnabledTimeseries], \r\n" +
            "  rdo.[Radar], \r\n" +
            "  rdo.[PressureTimeseries], \r\n" +
            "  rdo.[TemperatureTimeseries], \r\n" +
            "  rdo.[DewPointTimeseries], \r\n" +
            "  rdo.[StatusTimeseries] \r\n" +
            "FROM [RadomeDeviceView] rdo \r\n";

        public new const string BaseViewName = "RadomeDeviceView";
        public new const string ViewAliasName = "rdo";

        public const int RADAR_FIELD_ID = 6;
        public const int PRESSURETIMESERIES_FIELD_ID = 7;
        public const int TEMPERATURETIMESERIES_FIELD_ID = 8;
        public const int DEWPOINTTIMESERIES_FIELD_ID = 9;
        public const int STATUSTIMESERIES_FIELD_ID = 10;

        public SimpleRadomeDeviceDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid? Radar
        {
            get
            {
                return GetNullableGuid( RADAR_FIELD_ID );
            }
        }
        public Guid PressureTimeseries
        {
            get
            {
                return GetGuid( PRESSURETIMESERIES_FIELD_ID );
            }
        }
        public Guid TemperatureTimeseries
        {
            get
            {
                return GetGuid( TEMPERATURETIMESERIES_FIELD_ID );
            }
        }
        public Guid DewPointTimeseries
        {
            get
            {
                return GetGuid( DEWPOINTTIMESERIES_FIELD_ID );
            }
        }
        public Guid StatusTimeseries
        {
            get
            {
                return GetGuid( STATUSTIMESERIES_FIELD_ID );
            }
        }
    }

    public class SimpleTrackerDeviceDataReader : SimpleDeviceDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  td.[Id], \r\n" +
            "  td.[EntityType], \r\n" +
            "  td.[RowVersion], \r\n" +
            "  td.[Host], \r\n" +
            "  td.[Name], \r\n" +
            "  td.[Description], \r\n" +
            "  td.[EnabledTimeseries] \r\n" +
            "FROM [TrackerDeviceView] td \r\n";

        public new const string BaseViewName = "TrackerDeviceView";
        public new const string ViewAliasName = "td";

        public SimpleTrackerDeviceDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleAisDeviceDataReader : SimpleTrackerDeviceDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  ad.[Id], \r\n" +
            "  ad.[EntityType], \r\n" +
            "  ad.[RowVersion], \r\n" +
            "  ad.[Host], \r\n" +
            "  ad.[Name], \r\n" +
            "  ad.[Description], \r\n" +
            "  ad.[EnabledTimeseries] \r\n" +
            "FROM [AisDeviceView] ad \r\n";

        public new const string BaseViewName = "AisDeviceView";
        public new const string ViewAliasName = "ad";

        public SimpleAisDeviceDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleRadarDeviceDataReader : SimpleTrackerDeviceDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rd.[Id], \r\n" +
            "  rd.[EntityType], \r\n" +
            "  rd.[RowVersion], \r\n" +
            "  rd.[Host], \r\n" +
            "  rd.[Name], \r\n" +
            "  rd.[Description], \r\n" +
            "  rd.[EnabledTimeseries], \r\n" +
            "  rd.[SaveSettingsTimeseries], \r\n" +
            "  rd.[PowerOnTimeseries], \r\n" +
            "  rd.[TrackingOnTimeseries], \r\n" +
            "  rd.[RadarPulseTimeseries], \r\n" +
            "  rd.[TuningTimeseries], \r\n" +
            "  rd.[BlankSector1Timeseries], \r\n" +
            "  rd.[Sector1StartTimeseries], \r\n" +
            "  rd.[Sector1EndTimeseries], \r\n" +
            "  rd.[BlankSector2Timeseries], \r\n" +
            "  rd.[Sector2StartTimeseries], \r\n" +
            "  rd.[Sector2EndTimeseries], \r\n" +
            "  rd.[EnableAutomaticFrequencyControlTimeseries], \r\n" +
            "  rd.[AzimuthOffsetTimeseries], \r\n" +
            "  rd.[EnableSensitivityTimeControlTimeseries], \r\n" +
            "  rd.[AutomaticSensitivityTimeControlTimeseries], \r\n" +
            "  rd.[SensitivityTimeControlLevelTimeseries], \r\n" +
            "  rd.[EnableFastTimeConstantTimeseries], \r\n" +
            "  rd.[FastTimeConstantLevelTimeseries], \r\n" +
            "  rd.[FastTimeConstantModeTimeseries], \r\n" +
            "  rd.[LatitudeTimeseries], \r\n" +
            "  rd.[LongitudeTimeseries], \r\n" +
            "  rd.[Radome], \r\n" +
            "  rd.[GNSSDevice] \r\n" +
            "FROM [RadarDeviceView] rd \r\n";

        public new const string BaseViewName = "RadarDeviceView";
        public new const string ViewAliasName = "rd";

        public const int SAVESETTINGSTIMESERIES_FIELD_ID = 6;
        public const int POWERONTIMESERIES_FIELD_ID = 7;
        public const int TRACKINGONTIMESERIES_FIELD_ID = 8;
        public const int RADARPULSETIMESERIES_FIELD_ID = 9;
        public const int TUNINGTIMESERIES_FIELD_ID = 10;
        public const int BLANKSECTOR1TIMESERIES_FIELD_ID = 11;
        public const int SECTOR1STARTTIMESERIES_FIELD_ID = 12;
        public const int SECTOR1ENDTIMESERIES_FIELD_ID = 13;
        public const int BLANKSECTOR2TIMESERIES_FIELD_ID = 14;
        public const int SECTOR2STARTTIMESERIES_FIELD_ID = 15;
        public const int SECTOR2ENDTIMESERIES_FIELD_ID = 16;
        public const int ENABLEAUTOMATICFREQUENCYCONTROLTIMESERIES_FIELD_ID = 17;
        public const int AZIMUTHOFFSETTIMESERIES_FIELD_ID = 18;
        public const int ENABLESENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID = 19;
        public const int AUTOMATICSENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID = 20;
        public const int SENSITIVITYTIMECONTROLLEVELTIMESERIES_FIELD_ID = 21;
        public const int ENABLEFASTTIMECONSTANTTIMESERIES_FIELD_ID = 22;
        public const int FASTTIMECONSTANTLEVELTIMESERIES_FIELD_ID = 23;
        public const int FASTTIMECONSTANTMODETIMESERIES_FIELD_ID = 24;
        public const int LATITUDETIMESERIES_FIELD_ID = 25;
        public const int LONGITUDETIMESERIES_FIELD_ID = 26;
        public const int RADOME_FIELD_ID = 27;
        public const int GNSSDEVICE_FIELD_ID = 28;

        public SimpleRadarDeviceDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid SaveSettingsTimeseries
        {
            get
            {
                return GetGuid( SAVESETTINGSTIMESERIES_FIELD_ID );
            }
        }
        public Guid PowerOnTimeseries
        {
            get
            {
                return GetGuid( POWERONTIMESERIES_FIELD_ID );
            }
        }
        public Guid TrackingOnTimeseries
        {
            get
            {
                return GetGuid( TRACKINGONTIMESERIES_FIELD_ID );
            }
        }
        public Guid RadarPulseTimeseries
        {
            get
            {
                return GetGuid( RADARPULSETIMESERIES_FIELD_ID );
            }
        }
        public Guid TuningTimeseries
        {
            get
            {
                return GetGuid( TUNINGTIMESERIES_FIELD_ID );
            }
        }
        public Guid BlankSector1Timeseries
        {
            get
            {
                return GetGuid( BLANKSECTOR1TIMESERIES_FIELD_ID );
            }
        }
        public Guid Sector1StartTimeseries
        {
            get
            {
                return GetGuid( SECTOR1STARTTIMESERIES_FIELD_ID );
            }
        }
        public Guid Sector1EndTimeseries
        {
            get
            {
                return GetGuid( SECTOR1ENDTIMESERIES_FIELD_ID );
            }
        }
        public Guid BlankSector2Timeseries
        {
            get
            {
                return GetGuid( BLANKSECTOR2TIMESERIES_FIELD_ID );
            }
        }
        public Guid Sector2StartTimeseries
        {
            get
            {
                return GetGuid( SECTOR2STARTTIMESERIES_FIELD_ID );
            }
        }
        public Guid Sector2EndTimeseries
        {
            get
            {
                return GetGuid( SECTOR2ENDTIMESERIES_FIELD_ID );
            }
        }
        public Guid EnableAutomaticFrequencyControlTimeseries
        {
            get
            {
                return GetGuid( ENABLEAUTOMATICFREQUENCYCONTROLTIMESERIES_FIELD_ID );
            }
        }
        public Guid AzimuthOffsetTimeseries
        {
            get
            {
                return GetGuid( AZIMUTHOFFSETTIMESERIES_FIELD_ID );
            }
        }
        public Guid EnableSensitivityTimeControlTimeseries
        {
            get
            {
                return GetGuid( ENABLESENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID );
            }
        }
        public Guid AutomaticSensitivityTimeControlTimeseries
        {
            get
            {
                return GetGuid( AUTOMATICSENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID );
            }
        }
        public Guid SensitivityTimeControlLevelTimeseries
        {
            get
            {
                return GetGuid( SENSITIVITYTIMECONTROLLEVELTIMESERIES_FIELD_ID );
            }
        }
        public Guid EnableFastTimeConstantTimeseries
        {
            get
            {
                return GetGuid( ENABLEFASTTIMECONSTANTTIMESERIES_FIELD_ID );
            }
        }
        public Guid FastTimeConstantLevelTimeseries
        {
            get
            {
                return GetGuid( FASTTIMECONSTANTLEVELTIMESERIES_FIELD_ID );
            }
        }
        public Guid FastTimeConstantModeTimeseries
        {
            get
            {
                return GetGuid( FASTTIMECONSTANTMODETIMESERIES_FIELD_ID );
            }
        }
        public Guid LatitudeTimeseries
        {
            get
            {
                return GetGuid( LATITUDETIMESERIES_FIELD_ID );
            }
        }
        public Guid LongitudeTimeseries
        {
            get
            {
                return GetGuid( LONGITUDETIMESERIES_FIELD_ID );
            }
        }
        public Guid? Radome
        {
            get
            {
                return GetNullableGuid( RADOME_FIELD_ID );
            }
        }
        public Guid? GNSSDevice
        {
            get
            {
                return GetNullableGuid( GNSSDEVICE_FIELD_ID );
            }
        }
    }

    public class SimpleWeatherStationDeviceDataReader : SimpleDeviceDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  wsd.[Id], \r\n" +
            "  wsd.[EntityType], \r\n" +
            "  wsd.[RowVersion], \r\n" +
            "  wsd.[Host], \r\n" +
            "  wsd.[Name], \r\n" +
            "  wsd.[Description], \r\n" +
            "  wsd.[EnabledTimeseries], \r\n" +
            "  wsd.[BarometricPressureTimeseries], \r\n" +
            "  wsd.[AirTemperatureTimeseries], \r\n" +
            "  wsd.[WaterTemperatureTimeseries], \r\n" +
            "  wsd.[RelativeHumidityTimeseries], \r\n" +
            "  wsd.[AbsoluteHumidityTimeseries], \r\n" +
            "  wsd.[DewPointTimeseries], \r\n" +
            "  wsd.[WindDirectionTimeseries], \r\n" +
            "  wsd.[WindSpeedTimeseries], \r\n" +
            "  wsd.[Gyro] \r\n" +
            "FROM [WeatherStationDeviceView] wsd \r\n";

        public new const string BaseViewName = "WeatherStationDeviceView";
        public new const string ViewAliasName = "wsd";

        public const int BAROMETRICPRESSURETIMESERIES_FIELD_ID = 6;
        public const int AIRTEMPERATURETIMESERIES_FIELD_ID = 7;
        public const int WATERTEMPERATURETIMESERIES_FIELD_ID = 8;
        public const int RELATIVEHUMIDITYTIMESERIES_FIELD_ID = 9;
        public const int ABSOLUTEHUMIDITYTIMESERIES_FIELD_ID = 10;
        public const int DEWPOINTTIMESERIES_FIELD_ID = 11;
        public const int WINDDIRECTIONTIMESERIES_FIELD_ID = 12;
        public const int WINDSPEEDTIMESERIES_FIELD_ID = 13;
        public const int GYRO_FIELD_ID = 14;

        public SimpleWeatherStationDeviceDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid BarometricPressureTimeseries
        {
            get
            {
                return GetGuid( BAROMETRICPRESSURETIMESERIES_FIELD_ID );
            }
        }
        public Guid AirTemperatureTimeseries
        {
            get
            {
                return GetGuid( AIRTEMPERATURETIMESERIES_FIELD_ID );
            }
        }
        public Guid WaterTemperatureTimeseries
        {
            get
            {
                return GetGuid( WATERTEMPERATURETIMESERIES_FIELD_ID );
            }
        }
        public Guid RelativeHumidityTimeseries
        {
            get
            {
                return GetGuid( RELATIVEHUMIDITYTIMESERIES_FIELD_ID );
            }
        }
        public Guid AbsoluteHumidityTimeseries
        {
            get
            {
                return GetGuid( ABSOLUTEHUMIDITYTIMESERIES_FIELD_ID );
            }
        }
        public Guid DewPointTimeseries
        {
            get
            {
                return GetGuid( DEWPOINTTIMESERIES_FIELD_ID );
            }
        }
        public Guid WindDirectionTimeseries
        {
            get
            {
                return GetGuid( WINDDIRECTIONTIMESERIES_FIELD_ID );
            }
        }
        public Guid WindSpeedTimeseries
        {
            get
            {
                return GetGuid( WINDSPEEDTIMESERIES_FIELD_ID );
            }
        }
        public Guid Gyro
        {
            get
            {
                return GetGuid( GYRO_FIELD_ID );
            }
        }
    }

    public class SimpleFacilityDataReader : SimpleItemDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  f.[Id], \r\n" +
            "  f.[EntityType], \r\n" +
            "  f.[RowVersion], \r\n" +
            "  f.[Name], \r\n" +
            "  f.[Type], \r\n" +
            "  f.[Longitude], \r\n" +
            "  f.[Latitude], \r\n" +
            "  f.[Altitude] \r\n" +
            "FROM [FacilityView] f \r\n";

        public new const string BaseViewName = "FacilityView";
        public new const string ViewAliasName = "f";

        public const int NAME_FIELD_ID = 2;
        public const int TYPE_FIELD_ID = 3;
        public const int LONGITUDE_FIELD_ID = 4;
        public const int LATITUDE_FIELD_ID = 5;
        public const int ALTITUDE_FIELD_ID = 6;

        public SimpleFacilityDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
        public Guid Type
        {
            get
            {
                return GetGuid( TYPE_FIELD_ID );
            }
        }
        public double Longitude
        {
            get
            {
                return GetDouble( LONGITUDE_FIELD_ID );
            }
        }
        public double Latitude
        {
            get
            {
                return GetDouble( LATITUDE_FIELD_ID );
            }
        }
        public double Altitude
        {
            get
            {
                return GetDouble( ALTITUDE_FIELD_ID );
            }
        }
    }

    public class SimpleTrackableItemDataReader : SimpleItemDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  ti.[Id], \r\n" +
            "  ti.[EntityType], \r\n" +
            "  ti.[RowVersion] \r\n" +
            "FROM [TrackableItemView] ti \r\n";

        public new const string BaseViewName = "TrackableItemView";
        public new const string ViewAliasName = "ti";

        public SimpleTrackableItemDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleAircraftDataReader : SimpleTrackableItemDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  a.[Id], \r\n" +
            "  a.[EntityType], \r\n" +
            "  a.[RowVersion], \r\n" +
            "  a.[Name], \r\n" +
            "  a.[Type] \r\n" +
            "FROM [AircraftView] a \r\n";

        public new const string BaseViewName = "AircraftView";
        public new const string ViewAliasName = "a";

        public const int NAME_FIELD_ID = 2;
        public const int TYPE_FIELD_ID = 3;

        public SimpleAircraftDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
        public Guid Type
        {
            get
            {
                return GetGuid( TYPE_FIELD_ID );
            }
        }
    }

    public class SimpleAisAidToNavigationDataReader : SimpleTrackableItemDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  aatn.[Id], \r\n" +
            "  aatn.[EntityType], \r\n" +
            "  aatn.[RowVersion], \r\n" +
            "  aatn.[Name], \r\n" +
            "  aatn.[MMSI], \r\n" +
            "  aatn.[NavigationalAidType], \r\n" +
            "  aatn.[Position], \r\n" +
            "  aatn.[IsVirtual], \r\n" +
            "  aatn.[ToBow], \r\n" +
            "  aatn.[ToStern], \r\n" +
            "  aatn.[ToPort], \r\n" +
            "  aatn.[ToStarboard], \r\n" +
            "  aatn.[OffPositionTimeseries] \r\n" +
            "FROM [AisAidToNavigationView] aatn \r\n";

        public new const string BaseViewName = "AisAidToNavigationView";
        public new const string ViewAliasName = "aatn";

        public const int NAME_FIELD_ID = 2;
        public const int MMSI_FIELD_ID = 3;
        public const int NAVIGATIONALAIDTYPE_FIELD_ID = 4;
        public const int POSITION_FIELD_ID = 5;
        public const int ISVIRTUAL_FIELD_ID = 6;
        public const int TOBOW_FIELD_ID = 7;
        public const int TOSTERN_FIELD_ID = 8;
        public const int TOPORT_FIELD_ID = 9;
        public const int TOSTARBOARD_FIELD_ID = 10;
        public const int OFFPOSITIONTIMESERIES_FIELD_ID = 11;

        public SimpleAisAidToNavigationDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
        public Guid MMSI
        {
            get
            {
                return GetGuid( MMSI_FIELD_ID );
            }
        }
        public Types.NavigationalAidType NavigationalAidType
        {
            get
            {
                return GetEnum<Types.NavigationalAidType>( NAVIGATIONALAIDTYPE_FIELD_ID );
            }
        }
        public Guid Position
        {
            get
            {
                return GetGuid( POSITION_FIELD_ID );
            }
        }
        public bool IsVirtual
        {
            get
            {
                return GetBoolean( ISVIRTUAL_FIELD_ID );
            }
        }
        public int ToBow
        {
            get
            {
                return GetInt32( TOBOW_FIELD_ID );
            }
        }
        public int ToStern
        {
            get
            {
                return GetInt32( TOSTERN_FIELD_ID );
            }
        }
        public int ToPort
        {
            get
            {
                return GetInt32( TOPORT_FIELD_ID );
            }
        }
        public int ToStarboard
        {
            get
            {
                return GetInt32( TOSTARBOARD_FIELD_ID );
            }
        }
        public Guid OffPositionTimeseries
        {
            get
            {
                return GetGuid( OFFPOSITIONTIMESERIES_FIELD_ID );
            }
        }
    }

    public class SimpleVehicleDataReader : SimpleTrackableItemDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  v.[Id], \r\n" +
            "  v.[EntityType], \r\n" +
            "  v.[RowVersion], \r\n" +
            "  v.[Name], \r\n" +
            "  v.[Type] \r\n" +
            "FROM [VehicleView] v \r\n";

        public new const string BaseViewName = "VehicleView";
        public new const string ViewAliasName = "v";

        public const int NAME_FIELD_ID = 2;
        public const int TYPE_FIELD_ID = 3;

        public SimpleVehicleDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
        public Guid Type
        {
            get
            {
                return GetGuid( TYPE_FIELD_ID );
            }
        }
    }

    public class SimpleVesselDataReader : SimpleTrackableItemDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  vsl.[Id], \r\n" +
            "  vsl.[EntityType], \r\n" +
            "  vsl.[RowVersion], \r\n" +
            "  vsl.[Name], \r\n" +
            "  vsl.[Type], \r\n" +
            "  vsl.[ToBow], \r\n" +
            "  vsl.[ToStern], \r\n" +
            "  vsl.[ToPort], \r\n" +
            "  vsl.[ToStarboard], \r\n" +
            "  vsl.[DraughtTimeseries], \r\n" +
            "  vsl.[PersonsOnBoardTimeseries] \r\n" +
            "FROM [VesselView] vsl \r\n";

        public new const string BaseViewName = "VesselView";
        public new const string ViewAliasName = "vsl";

        public const int NAME_FIELD_ID = 2;
        public const int TYPE_FIELD_ID = 3;
        public const int TOBOW_FIELD_ID = 4;
        public const int TOSTERN_FIELD_ID = 5;
        public const int TOPORT_FIELD_ID = 6;
        public const int TOSTARBOARD_FIELD_ID = 7;
        public const int DRAUGHTTIMESERIES_FIELD_ID = 8;
        public const int PERSONSONBOARDTIMESERIES_FIELD_ID = 9;

        public SimpleVesselDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
        public Guid Type
        {
            get
            {
                return GetGuid( TYPE_FIELD_ID );
            }
        }
        public int ToBow
        {
            get
            {
                return GetInt32( TOBOW_FIELD_ID );
            }
        }
        public int ToStern
        {
            get
            {
                return GetInt32( TOSTERN_FIELD_ID );
            }
        }
        public int ToPort
        {
            get
            {
                return GetInt32( TOPORT_FIELD_ID );
            }
        }
        public int ToStarboard
        {
            get
            {
                return GetInt32( TOSTARBOARD_FIELD_ID );
            }
        }
        public Guid DraughtTimeseries
        {
            get
            {
                return GetGuid( DRAUGHTTIMESERIES_FIELD_ID );
            }
        }
        public Guid PersonsOnBoardTimeseries
        {
            get
            {
                return GetGuid( PERSONSONBOARDTIMESERIES_FIELD_ID );
            }
        }
    }

    public class SimpleItemIdentityLinkDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  iil.[Id], \r\n" +
            "  iil.[RowVersion], \r\n" +
            "  iil.[Item], \r\n" +
            "  iil.[Identity], \r\n" +
            "  iil.[Start], \r\n" +
            "  iil.[End] \r\n" +
            "FROM [ItemIdentityLinkView] iil \r\n";

        public const string BaseViewName = "ItemIdentityLinkView";
        public const string ViewAliasName = "iil";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int ITEM_FIELD_ID = 2;
        public const int IDENTITY_FIELD_ID = 3;
        public const int START_FIELD_ID = 4;
        public const int END_FIELD_ID = 5;

        public SimpleItemIdentityLinkDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Item
        {
            get
            {
                return GetGuid( ITEM_FIELD_ID );
            }
        }
        public Guid Identity
        {
            get
            {
                return GetGuid( IDENTITY_FIELD_ID );
            }
        }
        public DateTime Start
        {
            get
            {
                return new DateTime( GetInt64( START_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public DateTime? End
        {
            get
            {
                var v = GetNullableInt64( END_FIELD_ID );
                if( v is long value )
                {
                    return new DateTime( value , DateTimeKind.Utc );
                }
                return null;
            }
        }
    }

    public class SimpleItemParentChildLinkDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  ipcl.[Id], \r\n" +
            "  ipcl.[RowVersion], \r\n" +
            "  ipcl.[Parent], \r\n" +
            "  ipcl.[Child], \r\n" +
            "  ipcl.[Timestamp] \r\n" +
            "FROM [ItemParentChildLinkView] ipcl \r\n";

        public const string BaseViewName = "ItemParentChildLinkView";
        public const string ViewAliasName = "ipcl";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int PARENT_FIELD_ID = 2;
        public const int CHILD_FIELD_ID = 3;
        public const int TIMESTAMP_FIELD_ID = 4;

        public SimpleItemParentChildLinkDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Parent
        {
            get
            {
                return GetGuid( PARENT_FIELD_ID );
            }
        }
        public Guid Child
        {
            get
            {
                return GetGuid( CHILD_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
    }

    public class SimpleLineInputDeviceCommandDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  lidc.[Id], \r\n" +
            "  lidc.[RowVersion], \r\n" +
            "  lidc.[LineInputDevice], \r\n" +
            "  lidc.[Timestamp], \r\n" +
            "  lidc.[DeviceCommandSourceType], \r\n" +
            "  lidc.[DeviceCommandSourceId], \r\n" +
            "  lidc.[Reply] \r\n" +
            "FROM [LineInputDeviceCommandView] lidc \r\n";

        public const string BaseViewName = "LineInputDeviceCommandView";
        public const string ViewAliasName = "lidc";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int LINEINPUTDEVICE_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int DEVICECOMMANDSOURCETYPE_FIELD_ID = 4;
        public const int DEVICECOMMANDSOURCEID_FIELD_ID = 5;
        public const int REPLY_FIELD_ID = 6;

        public SimpleLineInputDeviceCommandDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid LineInputDevice
        {
            get
            {
                return GetGuid( LINEINPUTDEVICE_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Types.DeviceCommandSourceType DeviceCommandSourceType
        {
            get
            {
                return GetEnum<Types.DeviceCommandSourceType>( DEVICECOMMANDSOURCETYPE_FIELD_ID );
            }
        }
        public Guid DeviceCommandSourceId
        {
            get
            {
                return GetGuid( DEVICECOMMANDSOURCEID_FIELD_ID );
            }
        }
        public Guid Reply
        {
            get
            {
                return GetGuid( REPLY_FIELD_ID );
            }
        }
    }

    public class SimpleLineInputDeviceCommandReplyDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  lidcr.[Id], \r\n" +
            "  lidcr.[RowVersion], \r\n" +
            "  lidcr.[LineInputDevice], \r\n" +
            "  lidcr.[Timestamp], \r\n" +
            "  lidcr.[Command], \r\n" +
            "  lidcr.[Status], \r\n" +
            "  lidcr.[Message] \r\n" +
            "FROM [LineInputDeviceCommandReplyView] lidcr \r\n";

        public const string BaseViewName = "LineInputDeviceCommandReplyView";
        public const string ViewAliasName = "lidcr";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int LINEINPUTDEVICE_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int COMMAND_FIELD_ID = 4;
        public const int STATUS_FIELD_ID = 5;
        public const int MESSAGE_FIELD_ID = 6;

        public SimpleLineInputDeviceCommandReplyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid LineInputDevice
        {
            get
            {
                return GetGuid( LINEINPUTDEVICE_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Guid Command
        {
            get
            {
                return GetGuid( COMMAND_FIELD_ID );
            }
        }
        public Types.DeviceCommandReplyStatus Status
        {
            get
            {
                return GetEnum<Types.DeviceCommandReplyStatus>( STATUS_FIELD_ID );
            }
        }
        public string Message
        {
            get
            {
                return GetString( MESSAGE_FIELD_ID );
            }
        }
    }

    public class SimpleLineInputDeviceConfigurationDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  lidc.[Id], \r\n" +
            "  lidc.[RowVersion], \r\n" +
            "  lidc.[LineInputDevice], \r\n" +
            "  lidc.[Timestamp], \r\n" +
            "  lidc.[StoreReceivedSentences], \r\n" +
            "  lidc.[StoreSentMessages], \r\n" +
            "  lidc.[StoreUnsentMessages], \r\n" +
            "  lidc.[NMEA], \r\n" +
            "  lidc.[StrictNMEA], \r\n" +
            "  lidc.[ConnectionType], \r\n" +
            "  lidc.[UdpReceivePort], \r\n" +
            "  lidc.[UdpSendHostname], \r\n" +
            "  lidc.[UdpSendPort], \r\n" +
            "  lidc.[TcpHostname], \r\n" +
            "  lidc.[TcpPort], \r\n" +
            "  lidc.[UseHttpLogin], \r\n" +
            "  lidc.[LoginHostname], \r\n" +
            "  lidc.[LoginPort], \r\n" +
            "  lidc.[UserName], \r\n" +
            "  lidc.[Password], \r\n" +
            "  lidc.[ComPort], \r\n" +
            "  lidc.[BaudRate], \r\n" +
            "  lidc.[DataBits], \r\n" +
            "  lidc.[DiscardNull], \r\n" +
            "  lidc.[DtrEnable], \r\n" +
            "  lidc.[Handshake], \r\n" +
            "  lidc.[NewLine], \r\n" +
            "  lidc.[Parity], \r\n" +
            "  lidc.[ParityReplace], \r\n" +
            "  lidc.[ReadBufferSize], \r\n" +
            "  lidc.[ReadTimeout], \r\n" +
            "  lidc.[ReceivedBytesThreshold], \r\n" +
            "  lidc.[RtsEnable], \r\n" +
            "  lidc.[StopBits], \r\n" +
            "  lidc.[WriteBufferSize], \r\n" +
            "  lidc.[WriteTimeout], \r\n" +
            "  lidc.[PairedComPort] \r\n" +
            "FROM [LineInputDeviceConfigurationView] lidc \r\n";

        public const string BaseViewName = "LineInputDeviceConfigurationView";
        public const string ViewAliasName = "lidc";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int LINEINPUTDEVICE_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int STORERECEIVEDSENTENCES_FIELD_ID = 4;
        public const int STORESENTMESSAGES_FIELD_ID = 5;
        public const int STOREUNSENTMESSAGES_FIELD_ID = 6;
        public const int NMEA_FIELD_ID = 7;
        public const int STRICTNMEA_FIELD_ID = 8;
        public const int CONNECTIONTYPE_FIELD_ID = 9;
        public const int UDPRECEIVEPORT_FIELD_ID = 10;
        public const int UDPSENDHOSTNAME_FIELD_ID = 11;
        public const int UDPSENDPORT_FIELD_ID = 12;
        public const int TCPHOSTNAME_FIELD_ID = 13;
        public const int TCPPORT_FIELD_ID = 14;
        public const int USEHTTPLOGIN_FIELD_ID = 15;
        public const int LOGINHOSTNAME_FIELD_ID = 16;
        public const int LOGINPORT_FIELD_ID = 17;
        public const int USERNAME_FIELD_ID = 18;
        public const int PASSWORD_FIELD_ID = 19;
        public const int COMPORT_FIELD_ID = 20;
        public const int BAUDRATE_FIELD_ID = 21;
        public const int DATABITS_FIELD_ID = 22;
        public const int DISCARDNULL_FIELD_ID = 23;
        public const int DTRENABLE_FIELD_ID = 24;
        public const int HANDSHAKE_FIELD_ID = 25;
        public const int NEWLINE_FIELD_ID = 26;
        public const int PARITY_FIELD_ID = 27;
        public const int PARITYREPLACE_FIELD_ID = 28;
        public const int READBUFFERSIZE_FIELD_ID = 29;
        public const int READTIMEOUT_FIELD_ID = 30;
        public const int RECEIVEDBYTESTHRESHOLD_FIELD_ID = 31;
        public const int RTSENABLE_FIELD_ID = 32;
        public const int STOPBITS_FIELD_ID = 33;
        public const int WRITEBUFFERSIZE_FIELD_ID = 34;
        public const int WRITETIMEOUT_FIELD_ID = 35;
        public const int PAIREDCOMPORT_FIELD_ID = 36;

        public SimpleLineInputDeviceConfigurationDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid LineInputDevice
        {
            get
            {
                return GetGuid( LINEINPUTDEVICE_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public bool StoreReceivedSentences
        {
            get
            {
                return GetBoolean( STORERECEIVEDSENTENCES_FIELD_ID );
            }
        }
        public bool StoreSentMessages
        {
            get
            {
                return GetBoolean( STORESENTMESSAGES_FIELD_ID );
            }
        }
        public bool StoreUnsentMessages
        {
            get
            {
                return GetBoolean( STOREUNSENTMESSAGES_FIELD_ID );
            }
        }
        public bool NMEA
        {
            get
            {
                return GetBoolean( NMEA_FIELD_ID );
            }
        }
        public bool StrictNMEA
        {
            get
            {
                return GetBoolean( STRICTNMEA_FIELD_ID );
            }
        }
        public Types.LineInputDeviceConnectionType ConnectionType
        {
            get
            {
                return GetEnum<Types.LineInputDeviceConnectionType>( CONNECTIONTYPE_FIELD_ID );
            }
        }
        public int UdpReceivePort
        {
            get
            {
                return GetInt32( UDPRECEIVEPORT_FIELD_ID );
            }
        }
        public string UdpSendHostname
        {
            get
            {
                return GetString( UDPSENDHOSTNAME_FIELD_ID );
            }
        }
        public int UdpSendPort
        {
            get
            {
                return GetInt32( UDPSENDPORT_FIELD_ID );
            }
        }
        public string TcpHostname
        {
            get
            {
                return GetString( TCPHOSTNAME_FIELD_ID );
            }
        }
        public int TcpPort
        {
            get
            {
                return GetInt32( TCPPORT_FIELD_ID );
            }
        }
        public bool UseHttpLogin
        {
            get
            {
                return GetBoolean( USEHTTPLOGIN_FIELD_ID );
            }
        }
        public string LoginHostname
        {
            get
            {
                return GetString( LOGINHOSTNAME_FIELD_ID );
            }
        }
        public int LoginPort
        {
            get
            {
                return GetInt32( LOGINPORT_FIELD_ID );
            }
        }
        public string UserName
        {
            get
            {
                return GetString( USERNAME_FIELD_ID );
            }
        }
        public string Password
        {
            get
            {
                return GetString( PASSWORD_FIELD_ID );
            }
        }
        public string ComPort
        {
            get
            {
                return GetString( COMPORT_FIELD_ID );
            }
        }
        public int BaudRate
        {
            get
            {
                return GetInt32( BAUDRATE_FIELD_ID );
            }
        }
        public int DataBits
        {
            get
            {
                return GetInt32( DATABITS_FIELD_ID );
            }
        }
        public bool DiscardNull
        {
            get
            {
                return GetBoolean( DISCARDNULL_FIELD_ID );
            }
        }
        public bool DtrEnable
        {
            get
            {
                return GetBoolean( DTRENABLE_FIELD_ID );
            }
        }
        public Types.Handshake Handshake
        {
            get
            {
                return GetEnum<Types.Handshake>( HANDSHAKE_FIELD_ID );
            }
        }
        public string NewLine
        {
            get
            {
                return GetString( NEWLINE_FIELD_ID );
            }
        }
        public Types.Parity Parity
        {
            get
            {
                return GetEnum<Types.Parity>( PARITY_FIELD_ID );
            }
        }
        public byte ParityReplace
        {
            get
            {
                return GetByte( PARITYREPLACE_FIELD_ID );
            }
        }
        public int ReadBufferSize
        {
            get
            {
                return GetInt32( READBUFFERSIZE_FIELD_ID );
            }
        }
        public TimeSpan ReadTimeout
        {
            get
            {
                return new TimeSpan( GetInt64( READTIMEOUT_FIELD_ID ) );
            }
        }
        public int ReceivedBytesThreshold
        {
            get
            {
                return GetInt32( RECEIVEDBYTESTHRESHOLD_FIELD_ID );
            }
        }
        public bool RtsEnable
        {
            get
            {
                return GetBoolean( RTSENABLE_FIELD_ID );
            }
        }
        public Types.StopBits StopBits
        {
            get
            {
                return GetEnum<Types.StopBits>( STOPBITS_FIELD_ID );
            }
        }
        public int WriteBufferSize
        {
            get
            {
                return GetInt32( WRITEBUFFERSIZE_FIELD_ID );
            }
        }
        public TimeSpan WriteTimeout
        {
            get
            {
                return new TimeSpan( GetInt64( WRITETIMEOUT_FIELD_ID ) );
            }
        }
        public string PairedComPort
        {
            get
            {
                return GetString( PAIREDCOMPORT_FIELD_ID );
            }
        }
    }

    public class SimpleLineInputMessageRoutingDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  limr.[Id], \r\n" +
            "  limr.[RowVersion], \r\n" +
            "  limr.[LineInputDevice], \r\n" +
            "  limr.[Type] \r\n" +
            "FROM [LineInputMessageRoutingView] limr \r\n";

        public const string BaseViewName = "LineInputMessageRoutingView";
        public const string ViewAliasName = "limr";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int LINEINPUTDEVICE_FIELD_ID = 2;
        public const int TYPE_FIELD_ID = 3;

        public SimpleLineInputMessageRoutingDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid LineInputDevice
        {
            get
            {
                return GetGuid( LINEINPUTDEVICE_FIELD_ID );
            }
        }
        public string Type
        {
            get
            {
                return GetString( TYPE_FIELD_ID );
            }
        }
    }

    public class SimpleLineInputMessageRoutingDestinationDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  limrd.[Id], \r\n" +
            "  limrd.[RowVersion], \r\n" +
            "  limrd.[Routing], \r\n" +
            "  limrd.[Listener] \r\n" +
            "FROM [LineInputMessageRoutingDestinationView] limrd \r\n";

        public const string BaseViewName = "LineInputMessageRoutingDestinationView";
        public const string ViewAliasName = "limrd";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int ROUTING_FIELD_ID = 2;
        public const int LISTENER_FIELD_ID = 3;

        public SimpleLineInputMessageRoutingDestinationDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Routing
        {
            get
            {
                return GetGuid( ROUTING_FIELD_ID );
            }
        }
        public Guid Listener
        {
            get
            {
                return GetGuid( LISTENER_FIELD_ID );
            }
        }
    }

    public class SimpleLineInputWhiteListEntryDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  liwle.[Id], \r\n" +
            "  liwle.[RowVersion], \r\n" +
            "  liwle.[LineInputDevice], \r\n" +
            "  liwle.[HostName], \r\n" +
            "  liwle.[Port] \r\n" +
            "FROM [LineInputWhiteListEntryView] liwle \r\n";

        public const string BaseViewName = "LineInputWhiteListEntryView";
        public const string ViewAliasName = "liwle";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int LINEINPUTDEVICE_FIELD_ID = 2;
        public const int HOSTNAME_FIELD_ID = 3;
        public const int PORT_FIELD_ID = 4;

        public SimpleLineInputWhiteListEntryDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid LineInputDevice
        {
            get
            {
                return GetGuid( LINEINPUTDEVICE_FIELD_ID );
            }
        }
        public string HostName
        {
            get
            {
                return GetString( HOSTNAME_FIELD_ID );
            }
        }
        public int Port
        {
            get
            {
                return GetInt32( PORT_FIELD_ID );
            }
        }
    }

    public class SimpleLogApplicationDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  la.[Id], \r\n" +
            "  la.[RowVersion], \r\n" +
            "  la.[Name], \r\n" +
            "  la.[Description] \r\n" +
            "FROM [LogApplicationView] la \r\n";

        public const string BaseViewName = "LogApplicationView";
        public const string ViewAliasName = "la";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int NAME_FIELD_ID = 2;
        public const int DESCRIPTION_FIELD_ID = 3;

        public SimpleLogApplicationDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
        public string Description
        {
            get
            {
                return GetString( DESCRIPTION_FIELD_ID );
            }
        }
    }

    public class SimpleLogApplicationConfigurationDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  lac.[Id], \r\n" +
            "  lac.[RowVersion], \r\n" +
            "  lac.[Application], \r\n" +
            "  lac.[Timestamp], \r\n" +
            "  lac.[Finest], \r\n" +
            "  lac.[Finer], \r\n" +
            "  lac.[Fine], \r\n" +
            "  lac.[Info], \r\n" +
            "  lac.[Notice], \r\n" +
            "  lac.[Warn], \r\n" +
            "  lac.[Error], \r\n" +
            "  lac.[Severe], \r\n" +
            "  lac.[Critical], \r\n" +
            "  lac.[Alert], \r\n" +
            "  lac.[Fatal], \r\n" +
            "  lac.[Emergency] \r\n" +
            "FROM [LogApplicationConfigurationView] lac \r\n";

        public const string BaseViewName = "LogApplicationConfigurationView";
        public const string ViewAliasName = "lac";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int APPLICATION_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int FINEST_FIELD_ID = 4;
        public const int FINER_FIELD_ID = 5;
        public const int FINE_FIELD_ID = 6;
        public const int INFO_FIELD_ID = 7;
        public const int NOTICE_FIELD_ID = 8;
        public const int WARN_FIELD_ID = 9;
        public const int ERROR_FIELD_ID = 10;
        public const int SEVERE_FIELD_ID = 11;
        public const int CRITICAL_FIELD_ID = 12;
        public const int ALERT_FIELD_ID = 13;
        public const int FATAL_FIELD_ID = 14;
        public const int EMERGENCY_FIELD_ID = 15;

        public SimpleLogApplicationConfigurationDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Application
        {
            get
            {
                return GetGuid( APPLICATION_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public bool Finest
        {
            get
            {
                return GetBoolean( FINEST_FIELD_ID );
            }
        }
        public bool Finer
        {
            get
            {
                return GetBoolean( FINER_FIELD_ID );
            }
        }
        public bool Fine
        {
            get
            {
                return GetBoolean( FINE_FIELD_ID );
            }
        }
        public bool Info
        {
            get
            {
                return GetBoolean( INFO_FIELD_ID );
            }
        }
        public bool Notice
        {
            get
            {
                return GetBoolean( NOTICE_FIELD_ID );
            }
        }
        public bool Warn
        {
            get
            {
                return GetBoolean( WARN_FIELD_ID );
            }
        }
        public bool Error
        {
            get
            {
                return GetBoolean( ERROR_FIELD_ID );
            }
        }
        public bool Severe
        {
            get
            {
                return GetBoolean( SEVERE_FIELD_ID );
            }
        }
        public bool Critical
        {
            get
            {
                return GetBoolean( CRITICAL_FIELD_ID );
            }
        }
        public bool Alert
        {
            get
            {
                return GetBoolean( ALERT_FIELD_ID );
            }
        }
        public bool Fatal
        {
            get
            {
                return GetBoolean( FATAL_FIELD_ID );
            }
        }
        public bool Emergency
        {
            get
            {
                return GetBoolean( EMERGENCY_FIELD_ID );
            }
        }
    }

    public class SimpleLogHostDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  lh.[Id], \r\n" +
            "  lh.[RowVersion], \r\n" +
            "  lh.[ComputerName], \r\n" +
            "  lh.[Description] \r\n" +
            "FROM [LogHostView] lh \r\n";

        public const string BaseViewName = "LogHostView";
        public const string ViewAliasName = "lh";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int COMPUTERNAME_FIELD_ID = 2;
        public const int DESCRIPTION_FIELD_ID = 3;

        public SimpleLogHostDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public string ComputerName
        {
            get
            {
                return GetString( COMPUTERNAME_FIELD_ID );
            }
        }
        public string Description
        {
            get
            {
                return GetString( DESCRIPTION_FIELD_ID );
            }
        }
    }

    public class SimpleLogHostConfigurationDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  lhc.[Id], \r\n" +
            "  lhc.[RowVersion], \r\n" +
            "  lhc.[Host], \r\n" +
            "  lhc.[Timestamp], \r\n" +
            "  lhc.[Finest], \r\n" +
            "  lhc.[Finer], \r\n" +
            "  lhc.[Fine], \r\n" +
            "  lhc.[Info], \r\n" +
            "  lhc.[Notice], \r\n" +
            "  lhc.[Warn], \r\n" +
            "  lhc.[Error], \r\n" +
            "  lhc.[Severe], \r\n" +
            "  lhc.[Critical], \r\n" +
            "  lhc.[Alert], \r\n" +
            "  lhc.[Fatal], \r\n" +
            "  lhc.[Emergency] \r\n" +
            "FROM [LogHostConfigurationView] lhc \r\n";

        public const string BaseViewName = "LogHostConfigurationView";
        public const string ViewAliasName = "lhc";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int HOST_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int FINEST_FIELD_ID = 4;
        public const int FINER_FIELD_ID = 5;
        public const int FINE_FIELD_ID = 6;
        public const int INFO_FIELD_ID = 7;
        public const int NOTICE_FIELD_ID = 8;
        public const int WARN_FIELD_ID = 9;
        public const int ERROR_FIELD_ID = 10;
        public const int SEVERE_FIELD_ID = 11;
        public const int CRITICAL_FIELD_ID = 12;
        public const int ALERT_FIELD_ID = 13;
        public const int FATAL_FIELD_ID = 14;
        public const int EMERGENCY_FIELD_ID = 15;

        public SimpleLogHostConfigurationDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Host
        {
            get
            {
                return GetGuid( HOST_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public bool Finest
        {
            get
            {
                return GetBoolean( FINEST_FIELD_ID );
            }
        }
        public bool Finer
        {
            get
            {
                return GetBoolean( FINER_FIELD_ID );
            }
        }
        public bool Fine
        {
            get
            {
                return GetBoolean( FINE_FIELD_ID );
            }
        }
        public bool Info
        {
            get
            {
                return GetBoolean( INFO_FIELD_ID );
            }
        }
        public bool Notice
        {
            get
            {
                return GetBoolean( NOTICE_FIELD_ID );
            }
        }
        public bool Warn
        {
            get
            {
                return GetBoolean( WARN_FIELD_ID );
            }
        }
        public bool Error
        {
            get
            {
                return GetBoolean( ERROR_FIELD_ID );
            }
        }
        public bool Severe
        {
            get
            {
                return GetBoolean( SEVERE_FIELD_ID );
            }
        }
        public bool Critical
        {
            get
            {
                return GetBoolean( CRITICAL_FIELD_ID );
            }
        }
        public bool Alert
        {
            get
            {
                return GetBoolean( ALERT_FIELD_ID );
            }
        }
        public bool Fatal
        {
            get
            {
                return GetBoolean( FATAL_FIELD_ID );
            }
        }
        public bool Emergency
        {
            get
            {
                return GetBoolean( EMERGENCY_FIELD_ID );
            }
        }
    }

    public class SimpleLogLocationDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  ll.[Id], \r\n" +
            "  ll.[RowVersion], \r\n" +
            "  ll.[FileName], \r\n" +
            "  ll.[LineNumber], \r\n" +
            "  ll.[Namespace], \r\n" +
            "  ll.[ClassName], \r\n" +
            "  ll.[MethodName] \r\n" +
            "FROM [LogLocationView] ll \r\n";

        public const string BaseViewName = "LogLocationView";
        public const string ViewAliasName = "ll";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int FILENAME_FIELD_ID = 2;
        public const int LINENUMBER_FIELD_ID = 3;
        public const int NAMESPACE_FIELD_ID = 4;
        public const int CLASSNAME_FIELD_ID = 5;
        public const int METHODNAME_FIELD_ID = 6;

        public SimpleLogLocationDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public string FileName
        {
            get
            {
                return GetString( FILENAME_FIELD_ID );
            }
        }
        public int LineNumber
        {
            get
            {
                return GetInt32( LINENUMBER_FIELD_ID );
            }
        }
        public string Namespace
        {
            get
            {
                return GetString( NAMESPACE_FIELD_ID );
            }
        }
        public string ClassName
        {
            get
            {
                return GetString( CLASSNAME_FIELD_ID );
            }
        }
        public string MethodName
        {
            get
            {
                return GetString( METHODNAME_FIELD_ID );
            }
        }
    }

    public class SimpleLogProcessDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  lp.[Id], \r\n" +
            "  lp.[RowVersion], \r\n" +
            "  lp.[Application], \r\n" +
            "  lp.[Host], \r\n" +
            "  lp.[Started], \r\n" +
            "  lp.[Stopped], \r\n" +
            "  lp.[ProcessId], \r\n" +
            "  lp.[Path], \r\n" +
            "  lp.[Identity] \r\n" +
            "FROM [LogProcessView] lp \r\n";

        public const string BaseViewName = "LogProcessView";
        public const string ViewAliasName = "lp";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int APPLICATION_FIELD_ID = 2;
        public const int HOST_FIELD_ID = 3;
        public const int STARTED_FIELD_ID = 4;
        public const int STOPPED_FIELD_ID = 5;
        public const int PROCESSID_FIELD_ID = 6;
        public const int PATH_FIELD_ID = 7;
        public const int IDENTITY_FIELD_ID = 8;

        public SimpleLogProcessDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Application
        {
            get
            {
                return GetGuid( APPLICATION_FIELD_ID );
            }
        }
        public Guid Host
        {
            get
            {
                return GetGuid( HOST_FIELD_ID );
            }
        }
        public DateTime Started
        {
            get
            {
                return new DateTime( GetInt64( STARTED_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public DateTime? Stopped
        {
            get
            {
                var v = GetNullableInt64( STOPPED_FIELD_ID );
                if( v is long value )
                {
                    return new DateTime( value , DateTimeKind.Utc );
                }
                return null;
            }
        }
        public long ProcessId
        {
            get
            {
                return GetInt64( PROCESSID_FIELD_ID );
            }
        }
        public string Path
        {
            get
            {
                return GetString( PATH_FIELD_ID );
            }
        }
        public string Identity
        {
            get
            {
                return GetString( IDENTITY_FIELD_ID );
            }
        }
    }

    public class SimpleLogRecordDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  lr.[Id], \r\n" +
            "  lr.[RowVersion], \r\n" +
            "  lr.[Thread], \r\n" +
            "  lr.[SequenceNumber], \r\n" +
            "  lr.[Level], \r\n" +
            "  lr.[Timestamp], \r\n" +
            "  lr.[Depth], \r\n" +
            "  lr.[Location], \r\n" +
            "  lr.[Message], \r\n" +
            "  lr.[ExceptionString], \r\n" +
            "  lr.[PropertiesData] \r\n" +
            "FROM [LogRecordView] lr \r\n";

        public const string BaseViewName = "LogRecordView";
        public const string ViewAliasName = "lr";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int THREAD_FIELD_ID = 2;
        public const int SEQUENCENUMBER_FIELD_ID = 3;
        public const int LEVEL_FIELD_ID = 4;
        public const int TIMESTAMP_FIELD_ID = 5;
        public const int DEPTH_FIELD_ID = 6;
        public const int LOCATION_FIELD_ID = 7;
        public const int MESSAGE_FIELD_ID = 8;
        public const int EXCEPTIONSTRING_FIELD_ID = 9;
        public const int PROPERTIESDATA_FIELD_ID = 10;

        public SimpleLogRecordDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Thread
        {
            get
            {
                return GetGuid( THREAD_FIELD_ID );
            }
        }
        public long SequenceNumber
        {
            get
            {
                return GetInt64( SEQUENCENUMBER_FIELD_ID );
            }
        }
        public Types.LogLevel Level
        {
            get
            {
                return GetEnum<Types.LogLevel>( LEVEL_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public int Depth
        {
            get
            {
                return GetInt32( DEPTH_FIELD_ID );
            }
        }
        public Guid Location
        {
            get
            {
                return GetGuid( LOCATION_FIELD_ID );
            }
        }
        public string Message
        {
            get
            {
                return GetString( MESSAGE_FIELD_ID );
            }
        }
        public string ExceptionString
        {
            get
            {
                return GetString( EXCEPTIONSTRING_FIELD_ID );
            }
        }
        public byte[] PropertiesData
        {
            get
            {
                return GetBytes( PROPERTIESDATA_FIELD_ID );
            }
        }
    }

    public class SimpleLogThreadDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  lt.[Id], \r\n" +
            "  lt.[RowVersion], \r\n" +
            "  lt.[Process], \r\n" +
            "  lt.[Started], \r\n" +
            "  lt.[Stopped], \r\n" +
            "  lt.[ThreadId], \r\n" +
            "  lt.[Name] \r\n" +
            "FROM [LogThreadView] lt \r\n";

        public const string BaseViewName = "LogThreadView";
        public const string ViewAliasName = "lt";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int PROCESS_FIELD_ID = 2;
        public const int STARTED_FIELD_ID = 3;
        public const int STOPPED_FIELD_ID = 4;
        public const int THREADID_FIELD_ID = 5;
        public const int NAME_FIELD_ID = 6;

        public SimpleLogThreadDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Process
        {
            get
            {
                return GetGuid( PROCESS_FIELD_ID );
            }
        }
        public DateTime Started
        {
            get
            {
                return new DateTime( GetInt64( STARTED_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public DateTime? Stopped
        {
            get
            {
                var v = GetNullableInt64( STOPPED_FIELD_ID );
                if( v is long value )
                {
                    return new DateTime( value , DateTimeKind.Utc );
                }
                return null;
            }
        }
        public long ThreadId
        {
            get
            {
                return GetInt64( THREADID_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
    }

    public class SimpleLogTraceEntryDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  lte.[Id], \r\n" +
            "  lte.[RowVersion], \r\n" +
            "  lte.[Thread], \r\n" +
            "  lte.[SequenceNumber], \r\n" +
            "  lte.[Location], \r\n" +
            "  lte.[Depth], \r\n" +
            "  lte.[Entered], \r\n" +
            "  lte.[Ended] \r\n" +
            "FROM [LogTraceEntryView] lte \r\n";

        public const string BaseViewName = "LogTraceEntryView";
        public const string ViewAliasName = "lte";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int THREAD_FIELD_ID = 2;
        public const int SEQUENCENUMBER_FIELD_ID = 3;
        public const int LOCATION_FIELD_ID = 4;
        public const int DEPTH_FIELD_ID = 5;
        public const int ENTERED_FIELD_ID = 6;
        public const int ENDED_FIELD_ID = 7;

        public SimpleLogTraceEntryDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Thread
        {
            get
            {
                return GetGuid( THREAD_FIELD_ID );
            }
        }
        public long SequenceNumber
        {
            get
            {
                return GetInt64( SEQUENCENUMBER_FIELD_ID );
            }
        }
        public Guid Location
        {
            get
            {
                return GetGuid( LOCATION_FIELD_ID );
            }
        }
        public int Depth
        {
            get
            {
                return GetInt32( DEPTH_FIELD_ID );
            }
        }
        public DateTime Entered
        {
            get
            {
                return new DateTime( GetInt64( ENTERED_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public DateTime? Ended
        {
            get
            {
                var v = GetNullableInt64( ENDED_FIELD_ID );
                if( v is long value )
                {
                    return new DateTime( value , DateTimeKind.Utc );
                }
                return null;
            }
        }
    }

    public class SimpleMapElementDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  me.[Id], \r\n" +
            "  me.[RowVersion], \r\n" +
            "  me.[Item], \r\n" +
            "  me.[ElementType], \r\n" +
            "  me.[Latitude], \r\n" +
            "  me.[Longitude], \r\n" +
            "  me.[Angle], \r\n" +
            "  me.[Left], \r\n" +
            "  me.[Top], \r\n" +
            "  me.[Width], \r\n" +
            "  me.[Height], \r\n" +
            "  me.[Label], \r\n" +
            "  me.[Data] \r\n" +
            "FROM [MapElementView] me \r\n";

        public const string BaseViewName = "MapElementView";
        public const string ViewAliasName = "me";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int ITEM_FIELD_ID = 2;
        public const int ELEMENTTYPE_FIELD_ID = 3;
        public const int LATITUDE_FIELD_ID = 4;
        public const int LONGITUDE_FIELD_ID = 5;
        public const int ANGLE_FIELD_ID = 6;
        public const int LEFT_FIELD_ID = 7;
        public const int TOP_FIELD_ID = 8;
        public const int WIDTH_FIELD_ID = 9;
        public const int HEIGHT_FIELD_ID = 10;
        public const int LABEL_FIELD_ID = 11;
        public const int DATA_FIELD_ID = 12;

        public SimpleMapElementDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Item
        {
            get
            {
                return GetGuid( ITEM_FIELD_ID );
            }
        }
        public Types.MapElementType ElementType
        {
            get
            {
                return GetEnum<Types.MapElementType>( ELEMENTTYPE_FIELD_ID );
            }
        }
        public double Latitude
        {
            get
            {
                return GetDouble( LATITUDE_FIELD_ID );
            }
        }
        public double Longitude
        {
            get
            {
                return GetDouble( LONGITUDE_FIELD_ID );
            }
        }
        public double Angle
        {
            get
            {
                return GetDouble( ANGLE_FIELD_ID );
            }
        }
        public double Left
        {
            get
            {
                return GetDouble( LEFT_FIELD_ID );
            }
        }
        public double Top
        {
            get
            {
                return GetDouble( TOP_FIELD_ID );
            }
        }
        public double Width
        {
            get
            {
                return GetDouble( WIDTH_FIELD_ID );
            }
        }
        public double Height
        {
            get
            {
                return GetDouble( HEIGHT_FIELD_ID );
            }
        }
        public string Label
        {
            get
            {
                return GetString( LABEL_FIELD_ID );
            }
        }
        public byte[] Data
        {
            get
            {
                return GetBytes( DATA_FIELD_ID );
            }
        }
    }

    public class SimpleMapInfoDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  mi.[Id], \r\n" +
            "  mi.[RowVersion], \r\n" +
            "  mi.[Scale], \r\n" +
            "  mi.[Latitude], \r\n" +
            "  mi.[Longitude], \r\n" +
            "  mi.[NorthWestLatitude], \r\n" +
            "  mi.[NorthWestLongitude], \r\n" +
            "  mi.[SouthEastLatitude], \r\n" +
            "  mi.[SouthEastLongitude], \r\n" +
            "  mi.[Image] \r\n" +
            "FROM [MapInfoView] mi \r\n";

        public const string BaseViewName = "MapInfoView";
        public const string ViewAliasName = "mi";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int SCALE_FIELD_ID = 2;
        public const int LATITUDE_FIELD_ID = 3;
        public const int LONGITUDE_FIELD_ID = 4;
        public const int NORTHWESTLATITUDE_FIELD_ID = 5;
        public const int NORTHWESTLONGITUDE_FIELD_ID = 6;
        public const int SOUTHEASTLATITUDE_FIELD_ID = 7;
        public const int SOUTHEASTLONGITUDE_FIELD_ID = 8;
        public const int IMAGE_FIELD_ID = 9;

        public SimpleMapInfoDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public int Scale
        {
            get
            {
                return GetInt32( SCALE_FIELD_ID );
            }
        }
        public double Latitude
        {
            get
            {
                return GetDouble( LATITUDE_FIELD_ID );
            }
        }
        public double Longitude
        {
            get
            {
                return GetDouble( LONGITUDE_FIELD_ID );
            }
        }
        public double NorthWestLatitude
        {
            get
            {
                return GetDouble( NORTHWESTLATITUDE_FIELD_ID );
            }
        }
        public double NorthWestLongitude
        {
            get
            {
                return GetDouble( NORTHWESTLONGITUDE_FIELD_ID );
            }
        }
        public double SouthEastLatitude
        {
            get
            {
                return GetDouble( SOUTHEASTLATITUDE_FIELD_ID );
            }
        }
        public double SouthEastLongitude
        {
            get
            {
                return GetDouble( SOUTHEASTLONGITUDE_FIELD_ID );
            }
        }
        public byte[] Image
        {
            get
            {
                return GetBytes( IMAGE_FIELD_ID );
            }
        }
    }

    public class SimpleMapServiceOptionsDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  mso.[Id], \r\n" +
            "  mso.[RowVersion], \r\n" +
            "  mso.[Timestamp], \r\n" +
            "  mso.[IpAddress], \r\n" +
            "  mso.[Port], \r\n" +
            "  mso.[ImageScaleFactorX], \r\n" +
            "  mso.[ImageOffsetX], \r\n" +
            "  mso.[ImageScaleFactorY], \r\n" +
            "  mso.[ImageOffsetY] \r\n" +
            "FROM [MapServiceOptionsView] mso \r\n";

        public const string BaseViewName = "MapServiceOptionsView";
        public const string ViewAliasName = "mso";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TIMESTAMP_FIELD_ID = 2;
        public const int IPADDRESS_FIELD_ID = 3;
        public const int PORT_FIELD_ID = 4;
        public const int IMAGESCALEFACTORX_FIELD_ID = 5;
        public const int IMAGEOFFSETX_FIELD_ID = 6;
        public const int IMAGESCALEFACTORY_FIELD_ID = 7;
        public const int IMAGEOFFSETY_FIELD_ID = 8;

        public SimpleMapServiceOptionsDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public string IpAddress
        {
            get
            {
                return GetString( IPADDRESS_FIELD_ID );
            }
        }
        public int Port
        {
            get
            {
                return GetInt32( PORT_FIELD_ID );
            }
        }
        public double ImageScaleFactorX
        {
            get
            {
                return GetDouble( IMAGESCALEFACTORX_FIELD_ID );
            }
        }
        public double ImageOffsetX
        {
            get
            {
                return GetDouble( IMAGEOFFSETX_FIELD_ID );
            }
        }
        public double ImageScaleFactorY
        {
            get
            {
                return GetDouble( IMAGESCALEFACTORY_FIELD_ID );
            }
        }
        public double ImageOffsetY
        {
            get
            {
                return GetDouble( IMAGEOFFSETY_FIELD_ID );
            }
        }
    }

    public class SimpleMaritimeIdentificationDigitsDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  mid.[Id], \r\n" +
            "  mid.[RowVersion], \r\n" +
            "  mid.[Code], \r\n" +
            "  mid.[Country] \r\n" +
            "FROM [MaritimeIdentificationDigitsView] mid \r\n";

        public const string BaseViewName = "MaritimeIdentificationDigitsView";
        public const string ViewAliasName = "mid";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int CODE_FIELD_ID = 2;
        public const int COUNTRY_FIELD_ID = 3;

        public SimpleMaritimeIdentificationDigitsDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public int Code
        {
            get
            {
                return GetInt32( CODE_FIELD_ID );
            }
        }
        public Guid Country
        {
            get
            {
                return GetGuid( COUNTRY_FIELD_ID );
            }
        }
    }

    public class SimpleMediaProxySessionDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  mps.[Id], \r\n" +
            "  mps.[RowVersion], \r\n" +
            "  mps.[Service], \r\n" +
            "  mps.[Name], \r\n" +
            "  mps.[EnabledTimeseries] \r\n" +
            "FROM [MediaProxySessionView] mps \r\n";

        public const string BaseViewName = "MediaProxySessionView";
        public const string ViewAliasName = "mps";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int SERVICE_FIELD_ID = 2;
        public const int NAME_FIELD_ID = 3;
        public const int ENABLEDTIMESERIES_FIELD_ID = 4;

        public SimpleMediaProxySessionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Service
        {
            get
            {
                return GetGuid( SERVICE_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
        public Guid EnabledTimeseries
        {
            get
            {
                return GetGuid( ENABLEDTIMESERIES_FIELD_ID );
            }
        }
    }

    public class SimpleMediaProxySessionFileDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  mpsf.[Id], \r\n" +
            "  mpsf.[RowVersion], \r\n" +
            "  mpsf.[ProxySession], \r\n" +
            "  mpsf.[Timestamp], \r\n" +
            "  mpsf.[StreamName] \r\n" +
            "FROM [MediaProxySessionFileView] mpsf \r\n";

        public const string BaseViewName = "MediaProxySessionFileView";
        public const string ViewAliasName = "mpsf";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int PROXYSESSION_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int STREAMNAME_FIELD_ID = 4;

        public SimpleMediaProxySessionFileDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid ProxySession
        {
            get
            {
                return GetGuid( PROXYSESSION_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public string StreamName
        {
            get
            {
                return GetString( STREAMNAME_FIELD_ID );
            }
        }
    }

    public class SimpleMediaProxySessionOptionsDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  mpso.[Id], \r\n" +
            "  mpso.[RowVersion], \r\n" +
            "  mpso.[ProxySession], \r\n" +
            "  mpso.[Timestamp], \r\n" +
            "  mpso.[SourceStreamUrl], \r\n" +
            "  mpso.[StreamName], \r\n" +
            "  mpso.[Mode], \r\n" +
            "  mpso.[TunnelOverHTTPPortNumber], \r\n" +
            "  mpso.[Username], \r\n" +
            "  mpso.[Password], \r\n" +
            "  mpso.[RecorderPortNumber], \r\n" +
            "  mpso.[SessionType], \r\n" +
            "  mpso.[MaxFileTime], \r\n" +
            "  mpso.[MaxFileRetention], \r\n" +
            "  mpso.[VideoDirectory] \r\n" +
            "FROM [MediaProxySessionOptionsView] mpso \r\n";

        public const string BaseViewName = "MediaProxySessionOptionsView";
        public const string ViewAliasName = "mpso";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int PROXYSESSION_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int SOURCESTREAMURL_FIELD_ID = 4;
        public const int STREAMNAME_FIELD_ID = 5;
        public const int MODE_FIELD_ID = 6;
        public const int TUNNELOVERHTTPPORTNUMBER_FIELD_ID = 7;
        public const int USERNAME_FIELD_ID = 8;
        public const int PASSWORD_FIELD_ID = 9;
        public const int RECORDERPORTNUMBER_FIELD_ID = 10;
        public const int SESSIONTYPE_FIELD_ID = 11;
        public const int MAXFILETIME_FIELD_ID = 12;
        public const int MAXFILERETENTION_FIELD_ID = 13;
        public const int VIDEODIRECTORY_FIELD_ID = 14;

        public SimpleMediaProxySessionOptionsDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid ProxySession
        {
            get
            {
                return GetGuid( PROXYSESSION_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public string SourceStreamUrl
        {
            get
            {
                return GetString( SOURCESTREAMURL_FIELD_ID );
            }
        }
        public string StreamName
        {
            get
            {
                return GetString( STREAMNAME_FIELD_ID );
            }
        }
        public Types.MediaProxySessionMode Mode
        {
            get
            {
                return GetEnum<Types.MediaProxySessionMode>( MODE_FIELD_ID );
            }
        }
        public int TunnelOverHTTPPortNumber
        {
            get
            {
                return GetInt32( TUNNELOVERHTTPPORTNUMBER_FIELD_ID );
            }
        }
        public string Username
        {
            get
            {
                return GetString( USERNAME_FIELD_ID );
            }
        }
        public string Password
        {
            get
            {
                return GetString( PASSWORD_FIELD_ID );
            }
        }
        public int RecorderPortNumber
        {
            get
            {
                return GetInt32( RECORDERPORTNUMBER_FIELD_ID );
            }
        }
        public Types.MediaProxySessionType SessionType
        {
            get
            {
                return GetEnum<Types.MediaProxySessionType>( SESSIONTYPE_FIELD_ID );
            }
        }
        public TimeSpan MaxFileTime
        {
            get
            {
                return new TimeSpan( GetInt64( MAXFILETIME_FIELD_ID ) );
            }
        }
        public TimeSpan MaxFileRetention
        {
            get
            {
                return new TimeSpan( GetInt64( MAXFILERETENTION_FIELD_ID ) );
            }
        }
        public string VideoDirectory
        {
            get
            {
                return GetString( VIDEODIRECTORY_FIELD_ID );
            }
        }
    }

    public class SimpleMediaServiceDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  ms.[Id], \r\n" +
            "  ms.[RowVersion], \r\n" +
            "  ms.[EnabledTimeseries] \r\n" +
            "FROM [MediaServiceView] ms \r\n";

        public const string BaseViewName = "MediaServiceView";
        public const string ViewAliasName = "ms";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int ENABLEDTIMESERIES_FIELD_ID = 2;

        public SimpleMediaServiceDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid EnabledTimeseries
        {
            get
            {
                return GetGuid( ENABLEDTIMESERIES_FIELD_ID );
            }
        }
    }

    public class SimpleMediaServiceOptionsDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  mso.[Id], \r\n" +
            "  mso.[RowVersion], \r\n" +
            "  mso.[MediaService], \r\n" +
            "  mso.[Timestamp], \r\n" +
            "  mso.[RtspPortNumber], \r\n" +
            "  mso.[HttpPortNumber] \r\n" +
            "FROM [MediaServiceOptionsView] mso \r\n";

        public const string BaseViewName = "MediaServiceOptionsView";
        public const string ViewAliasName = "mso";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int MEDIASERVICE_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int RTSPPORTNUMBER_FIELD_ID = 4;
        public const int HTTPPORTNUMBER_FIELD_ID = 5;

        public SimpleMediaServiceOptionsDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid MediaService
        {
            get
            {
                return GetGuid( MEDIASERVICE_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public int RtspPortNumber
        {
            get
            {
                return GetInt32( RTSPPORTNUMBER_FIELD_ID );
            }
        }
        public int HttpPortNumber
        {
            get
            {
                return GetInt32( HTTPPORTNUMBER_FIELD_ID );
            }
        }
    }

    public class SimpleNamespaceElementDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  ne.[Id], \r\n" +
            "  ne.[EntityType], \r\n" +
            "  ne.[RowVersion], \r\n" +
            "  ne.[Namespace], \r\n" +
            "  ne.[Name], \r\n" +
            "  ne.[Description] \r\n" +
            "FROM [NamespaceElementView] ne \r\n";

        public const string BaseViewName = "NamespaceElementView";
        public const string ViewAliasName = "ne";

        public const int ID_FIELD_ID = 0;
        public const int ENTITYTYPE_FIELD_ID = 1;
        public const int ROWVERSION_FIELD_ID = 2;
        public const int NAMESPACE_FIELD_ID = 3;
        public const int NAME_FIELD_ID = 4;
        public const int DESCRIPTION_FIELD_ID = 5;

        public SimpleNamespaceElementDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public Types.Kind EntityType
        {
            get
            {
                return GetEnum<Types.Kind>( ENTITYTYPE_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Namespace
        {
            get
            {
                return GetGuid( NAMESPACE_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
        public string Description
        {
            get
            {
                return GetString( DESCRIPTION_FIELD_ID );
            }
        }
    }

    public class SimpleElementTypeDataReader : SimpleNamespaceElementDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  et.[Id], \r\n" +
            "  et.[EntityType], \r\n" +
            "  et.[RowVersion], \r\n" +
            "  et.[Namespace], \r\n" +
            "  et.[Name], \r\n" +
            "  et.[Description] \r\n" +
            "FROM [ElementTypeView] et \r\n";

        public new const string BaseViewName = "ElementTypeView";
        public new const string ViewAliasName = "et";

        public SimpleElementTypeDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleNamespaceDataReader : SimpleNamespaceElementDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  n.[Id], \r\n" +
            "  n.[EntityType], \r\n" +
            "  n.[RowVersion], \r\n" +
            "  n.[Namespace], \r\n" +
            "  n.[Name], \r\n" +
            "  n.[Description] \r\n" +
            "FROM [NamespaceView] n \r\n";

        public new const string BaseViewName = "NamespaceView";
        public new const string ViewAliasName = "n";

        public SimpleNamespaceDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleOilSpillDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  os.[Id], \r\n" +
            "  os.[RowVersion], \r\n" +
            "  os.[OilSpillDetector], \r\n" +
            "  os.[Timestamp], \r\n" +
            "  os.[OilArea], \r\n" +
            "  os.[Shape], \r\n" +
            "  os.[BSI], \r\n" +
            "  os.[Oil], \r\n" +
            "  os.[Trace] \r\n" +
            "FROM [OilSpillView] os \r\n";

        public const string BaseViewName = "OilSpillView";
        public const string ViewAliasName = "os";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int OILSPILLDETECTOR_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int OILAREA_FIELD_ID = 4;
        public const int SHAPE_FIELD_ID = 5;
        public const int BSI_FIELD_ID = 6;
        public const int OIL_FIELD_ID = 7;
        public const int TRACE_FIELD_ID = 8;

        public SimpleOilSpillDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid OilSpillDetector
        {
            get
            {
                return GetGuid( OILSPILLDETECTOR_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public double OilArea
        {
            get
            {
                return GetDouble( OILAREA_FIELD_ID );
            }
        }
        public byte[] Shape
        {
            get
            {
                return GetBytes( SHAPE_FIELD_ID );
            }
        }
        public byte[] BSI
        {
            get
            {
                return GetBytes( BSI_FIELD_ID );
            }
        }
        public byte[] Oil
        {
            get
            {
                return GetBytes( OIL_FIELD_ID );
            }
        }
        public byte[] Trace
        {
            get
            {
                return GetBytes( TRACE_FIELD_ID );
            }
        }
    }

    public class SimpleOilSpillDetectorCommandDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  osdc.[Id], \r\n" +
            "  osdc.[RowVersion], \r\n" +
            "  osdc.[OilSpillDetector], \r\n" +
            "  osdc.[Timestamp], \r\n" +
            "  osdc.[DeviceCommandSourceType], \r\n" +
            "  osdc.[DeviceCommandSourceId], \r\n" +
            "  osdc.[Reply] \r\n" +
            "FROM [OilSpillDetectorCommandView] osdc \r\n";

        public const string BaseViewName = "OilSpillDetectorCommandView";
        public const string ViewAliasName = "osdc";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int OILSPILLDETECTOR_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int DEVICECOMMANDSOURCETYPE_FIELD_ID = 4;
        public const int DEVICECOMMANDSOURCEID_FIELD_ID = 5;
        public const int REPLY_FIELD_ID = 6;

        public SimpleOilSpillDetectorCommandDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid OilSpillDetector
        {
            get
            {
                return GetGuid( OILSPILLDETECTOR_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Types.DeviceCommandSourceType DeviceCommandSourceType
        {
            get
            {
                return GetEnum<Types.DeviceCommandSourceType>( DEVICECOMMANDSOURCETYPE_FIELD_ID );
            }
        }
        public Guid DeviceCommandSourceId
        {
            get
            {
                return GetGuid( DEVICECOMMANDSOURCEID_FIELD_ID );
            }
        }
        public Guid Reply
        {
            get
            {
                return GetGuid( REPLY_FIELD_ID );
            }
        }
    }

    public class SimpleOilSpillDetectorCommandReplyDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  osdcr.[Id], \r\n" +
            "  osdcr.[RowVersion], \r\n" +
            "  osdcr.[OilSpillDetector], \r\n" +
            "  osdcr.[Timestamp], \r\n" +
            "  osdcr.[Command], \r\n" +
            "  osdcr.[Status], \r\n" +
            "  osdcr.[Message] \r\n" +
            "FROM [OilSpillDetectorCommandReplyView] osdcr \r\n";

        public const string BaseViewName = "OilSpillDetectorCommandReplyView";
        public const string ViewAliasName = "osdcr";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int OILSPILLDETECTOR_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int COMMAND_FIELD_ID = 4;
        public const int STATUS_FIELD_ID = 5;
        public const int MESSAGE_FIELD_ID = 6;

        public SimpleOilSpillDetectorCommandReplyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid OilSpillDetector
        {
            get
            {
                return GetGuid( OILSPILLDETECTOR_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Guid Command
        {
            get
            {
                return GetGuid( COMMAND_FIELD_ID );
            }
        }
        public Types.DeviceCommandReplyStatus Status
        {
            get
            {
                return GetEnum<Types.DeviceCommandReplyStatus>( STATUS_FIELD_ID );
            }
        }
        public string Message
        {
            get
            {
                return GetString( MESSAGE_FIELD_ID );
            }
        }
    }

    public class SimpleOilSpillDetectorConfigurationDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  osdc.[Id], \r\n" +
            "  osdc.[RowVersion], \r\n" +
            "  osdc.[OilSpillDetector], \r\n" +
            "  osdc.[Timestamp], \r\n" +
            "  osdc.[Range], \r\n" +
            "  osdc.[StartAngle], \r\n" +
            "  osdc.[EndAngle], \r\n" +
            "  osdc.[StartRange], \r\n" +
            "  osdc.[EndRange], \r\n" +
            "  osdc.[UpdateRate], \r\n" +
            "  osdc.[StatusSendTime], \r\n" +
            "  osdc.[DrawBorder], \r\n" +
            "  osdc.[Colors], \r\n" +
            "  osdc.[SendToServer], \r\n" +
            "  osdc.[Directory], \r\n" +
            "  osdc.[TransparentWater], \r\n" +
            "  osdc.[SavePictures], \r\n" +
            "  osdc.[SendAsTarget], \r\n" +
            "  osdc.[WriteLog], \r\n" +
            "  osdc.[TargetFilePrefix], \r\n" +
            "  osdc.[TargetMMSI], \r\n" +
            "  osdc.[Latitude], \r\n" +
            "  osdc.[Longitude], \r\n" +
            "  osdc.[TestSourceEnabled], \r\n" +
            "  osdc.[ProxyServer], \r\n" +
            "  osdc.[UseProxyServer] \r\n" +
            "FROM [OilSpillDetectorConfigurationView] osdc \r\n";

        public const string BaseViewName = "OilSpillDetectorConfigurationView";
        public const string ViewAliasName = "osdc";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int OILSPILLDETECTOR_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int RANGE_FIELD_ID = 4;
        public const int STARTANGLE_FIELD_ID = 5;
        public const int ENDANGLE_FIELD_ID = 6;
        public const int STARTRANGE_FIELD_ID = 7;
        public const int ENDRANGE_FIELD_ID = 8;
        public const int UPDATERATE_FIELD_ID = 9;
        public const int STATUSSENDTIME_FIELD_ID = 10;
        public const int DRAWBORDER_FIELD_ID = 11;
        public const int COLORS_FIELD_ID = 12;
        public const int SENDTOSERVER_FIELD_ID = 13;
        public const int DIRECTORY_FIELD_ID = 14;
        public const int TRANSPARENTWATER_FIELD_ID = 15;
        public const int SAVEPICTURES_FIELD_ID = 16;
        public const int SENDASTARGET_FIELD_ID = 17;
        public const int WRITELOG_FIELD_ID = 18;
        public const int TARGETFILEPREFIX_FIELD_ID = 19;
        public const int TARGETMMSI_FIELD_ID = 20;
        public const int LATITUDE_FIELD_ID = 21;
        public const int LONGITUDE_FIELD_ID = 22;
        public const int TESTSOURCEENABLED_FIELD_ID = 23;
        public const int PROXYSERVER_FIELD_ID = 24;
        public const int USEPROXYSERVER_FIELD_ID = 25;

        public SimpleOilSpillDetectorConfigurationDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid OilSpillDetector
        {
            get
            {
                return GetGuid( OILSPILLDETECTOR_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public double Range
        {
            get
            {
                return GetDouble( RANGE_FIELD_ID );
            }
        }
        public double StartAngle
        {
            get
            {
                return GetDouble( STARTANGLE_FIELD_ID );
            }
        }
        public double EndAngle
        {
            get
            {
                return GetDouble( ENDANGLE_FIELD_ID );
            }
        }
        public double StartRange
        {
            get
            {
                return GetDouble( STARTRANGE_FIELD_ID );
            }
        }
        public double EndRange
        {
            get
            {
                return GetDouble( ENDRANGE_FIELD_ID );
            }
        }
        public int UpdateRate
        {
            get
            {
                return GetInt32( UPDATERATE_FIELD_ID );
            }
        }
        public TimeSpan StatusSendTime
        {
            get
            {
                return new TimeSpan( GetInt64( STATUSSENDTIME_FIELD_ID ) );
            }
        }
        public bool DrawBorder
        {
            get
            {
                return GetBoolean( DRAWBORDER_FIELD_ID );
            }
        }
        public byte[] Colors
        {
            get
            {
                return GetBytes( COLORS_FIELD_ID );
            }
        }
        public bool SendToServer
        {
            get
            {
                return GetBoolean( SENDTOSERVER_FIELD_ID );
            }
        }
        public string Directory
        {
            get
            {
                return GetString( DIRECTORY_FIELD_ID );
            }
        }
        public bool TransparentWater
        {
            get
            {
                return GetBoolean( TRANSPARENTWATER_FIELD_ID );
            }
        }
        public bool SavePictures
        {
            get
            {
                return GetBoolean( SAVEPICTURES_FIELD_ID );
            }
        }
        public bool SendAsTarget
        {
            get
            {
                return GetBoolean( SENDASTARGET_FIELD_ID );
            }
        }
        public bool WriteLog
        {
            get
            {
                return GetBoolean( WRITELOG_FIELD_ID );
            }
        }
        public string TargetFilePrefix
        {
            get
            {
                return GetString( TARGETFILEPREFIX_FIELD_ID );
            }
        }
        public Guid TargetMMSI
        {
            get
            {
                return GetGuid( TARGETMMSI_FIELD_ID );
            }
        }
        public double Latitude
        {
            get
            {
                return GetDouble( LATITUDE_FIELD_ID );
            }
        }
        public double Longitude
        {
            get
            {
                return GetDouble( LONGITUDE_FIELD_ID );
            }
        }
        public bool TestSourceEnabled
        {
            get
            {
                return GetBoolean( TESTSOURCEENABLED_FIELD_ID );
            }
        }
        public string ProxyServer
        {
            get
            {
                return GetString( PROXYSERVER_FIELD_ID );
            }
        }
        public bool UseProxyServer
        {
            get
            {
                return GetBoolean( USEPROXYSERVER_FIELD_ID );
            }
        }
    }

    public class SimplePosition2DTimeseriesValueDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  p2dv.[Id], \r\n" +
            "  p2dv.[RowVersion], \r\n" +
            "  p2dv.[Timeseries], \r\n" +
            "  p2dv.[Timestamp], \r\n" +
            "  p2dv.[X], \r\n" +
            "  p2dv.[Y] \r\n" +
            "FROM [Position2DTimeseriesValueView] p2dv \r\n";

        public const string BaseViewName = "Position2DTimeseriesValueView";
        public const string ViewAliasName = "p2dv";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TIMESERIES_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int X_FIELD_ID = 4;
        public const int Y_FIELD_ID = 5;

        public SimplePosition2DTimeseriesValueDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public double? X
        {
            get
            {
                return GetNullableDouble( X_FIELD_ID );
            }
        }
        public double? Y
        {
            get
            {
                return GetNullableDouble( Y_FIELD_ID );
            }
        }
    }

    public class SimplePosition3DTimeseriesValueDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  p3dv.[Id], \r\n" +
            "  p3dv.[RowVersion], \r\n" +
            "  p3dv.[Timeseries], \r\n" +
            "  p3dv.[Timestamp], \r\n" +
            "  p3dv.[X], \r\n" +
            "  p3dv.[Y], \r\n" +
            "  p3dv.[Z] \r\n" +
            "FROM [Position3DTimeseriesValueView] p3dv \r\n";

        public const string BaseViewName = "Position3DTimeseriesValueView";
        public const string ViewAliasName = "p3dv";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TIMESERIES_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int X_FIELD_ID = 4;
        public const int Y_FIELD_ID = 5;
        public const int Z_FIELD_ID = 6;

        public SimplePosition3DTimeseriesValueDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public double? X
        {
            get
            {
                return GetNullableDouble( X_FIELD_ID );
            }
        }
        public double? Y
        {
            get
            {
                return GetNullableDouble( Y_FIELD_ID );
            }
        }
        public double? Z
        {
            get
            {
                return GetNullableDouble( Z_FIELD_ID );
            }
        }
    }

    public class SimpleProcessTrackValueResultDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  ptvr.[Id], \r\n" +
            "  ptvr.[RowVersion], \r\n" +
            "  ptvr.[CreatedNewTrack], \r\n" +
            "  ptvr.[TrackId] \r\n" +
            "FROM [ProcessTrackValueResultView] ptvr \r\n";

        public const string BaseViewName = "ProcessTrackValueResultView";
        public const string ViewAliasName = "ptvr";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int CREATEDNEWTRACK_FIELD_ID = 2;
        public const int TRACKID_FIELD_ID = 3;

        public SimpleProcessTrackValueResultDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public bool CreatedNewTrack
        {
            get
            {
                return GetBoolean( CREATEDNEWTRACK_FIELD_ID );
            }
        }
        public Guid TrackId
        {
            get
            {
                return GetGuid( TRACKID_FIELD_ID );
            }
        }
    }

    public class SimplePropertyDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  p.[Id], \r\n" +
            "  p.[EntityType], \r\n" +
            "  p.[RowVersion], \r\n" +
            "  p.[Element], \r\n" +
            "  p.[Definition] \r\n" +
            "FROM [PropertyView] p \r\n";

        public const string BaseViewName = "PropertyView";
        public const string ViewAliasName = "p";

        public const int ID_FIELD_ID = 0;
        public const int ENTITYTYPE_FIELD_ID = 1;
        public const int ROWVERSION_FIELD_ID = 2;
        public const int ELEMENT_FIELD_ID = 3;
        public const int DEFINITION_FIELD_ID = 4;

        public SimplePropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public Types.Kind EntityType
        {
            get
            {
                return GetEnum<Types.Kind>( ENTITYTYPE_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Element
        {
            get
            {
                return GetGuid( ELEMENT_FIELD_ID );
            }
        }
        public Guid Definition
        {
            get
            {
                return GetGuid( DEFINITION_FIELD_ID );
            }
        }
    }

    public class SimpleBinaryPropertyDataReader : SimplePropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  bp.[Id], \r\n" +
            "  bp.[EntityType], \r\n" +
            "  bp.[RowVersion], \r\n" +
            "  bp.[Element], \r\n" +
            "  bp.[Definition], \r\n" +
            "  bp.[Value] \r\n" +
            "FROM [BinaryPropertyView] bp \r\n";

        public new const string BaseViewName = "BinaryPropertyView";
        public new const string ViewAliasName = "bp";

        public const int VALUE_FIELD_ID = 4;

        public SimpleBinaryPropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public byte[] Value
        {
            get
            {
                return GetBytes( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleBooleanPropertyDataReader : SimplePropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  bop.[Id], \r\n" +
            "  bop.[EntityType], \r\n" +
            "  bop.[RowVersion], \r\n" +
            "  bop.[Element], \r\n" +
            "  bop.[Definition], \r\n" +
            "  bop.[Value] \r\n" +
            "FROM [BooleanPropertyView] bop \r\n";

        public new const string BaseViewName = "BooleanPropertyView";
        public new const string ViewAliasName = "bop";

        public const int VALUE_FIELD_ID = 4;

        public SimpleBooleanPropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public bool Value
        {
            get
            {
                return GetBoolean( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleBytePropertyDataReader : SimplePropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  byp.[Id], \r\n" +
            "  byp.[EntityType], \r\n" +
            "  byp.[RowVersion], \r\n" +
            "  byp.[Element], \r\n" +
            "  byp.[Definition], \r\n" +
            "  byp.[Value] \r\n" +
            "FROM [BytePropertyView] byp \r\n";

        public new const string BaseViewName = "BytePropertyView";
        public new const string ViewAliasName = "byp";

        public const int VALUE_FIELD_ID = 4;

        public SimpleBytePropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public byte Value
        {
            get
            {
                return GetByte( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleDateTimePropertyDataReader : SimplePropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  dtp.[Id], \r\n" +
            "  dtp.[EntityType], \r\n" +
            "  dtp.[RowVersion], \r\n" +
            "  dtp.[Element], \r\n" +
            "  dtp.[Definition], \r\n" +
            "  dtp.[Value] \r\n" +
            "FROM [DateTimePropertyView] dtp \r\n";

        public new const string BaseViewName = "DateTimePropertyView";
        public new const string ViewAliasName = "dtp";

        public const int VALUE_FIELD_ID = 4;

        public SimpleDateTimePropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public DateTime Value
        {
            get
            {
                return new DateTime( GetInt64( VALUE_FIELD_ID ), DateTimeKind.Utc );
            }
        }
    }

    public class SimpleDoublePropertyDataReader : SimplePropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  dp.[Id], \r\n" +
            "  dp.[EntityType], \r\n" +
            "  dp.[RowVersion], \r\n" +
            "  dp.[Element], \r\n" +
            "  dp.[Definition], \r\n" +
            "  dp.[Value] \r\n" +
            "FROM [DoublePropertyView] dp \r\n";

        public new const string BaseViewName = "DoublePropertyView";
        public new const string ViewAliasName = "dp";

        public const int VALUE_FIELD_ID = 4;

        public SimpleDoublePropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public double Value
        {
            get
            {
                return GetDouble( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleGuidPropertyDataReader : SimplePropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  gp.[Id], \r\n" +
            "  gp.[EntityType], \r\n" +
            "  gp.[RowVersion], \r\n" +
            "  gp.[Element], \r\n" +
            "  gp.[Definition], \r\n" +
            "  gp.[Value] \r\n" +
            "FROM [GuidPropertyView] gp \r\n";

        public new const string BaseViewName = "GuidPropertyView";
        public new const string ViewAliasName = "gp";

        public const int VALUE_FIELD_ID = 4;

        public SimpleGuidPropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Value
        {
            get
            {
                return GetGuid( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleInt16PropertyDataReader : SimplePropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  i16p.[Id], \r\n" +
            "  i16p.[EntityType], \r\n" +
            "  i16p.[RowVersion], \r\n" +
            "  i16p.[Element], \r\n" +
            "  i16p.[Definition], \r\n" +
            "  i16p.[Value] \r\n" +
            "FROM [Int16PropertyView] i16p \r\n";

        public new const string BaseViewName = "Int16PropertyView";
        public new const string ViewAliasName = "i16p";

        public const int VALUE_FIELD_ID = 4;

        public SimpleInt16PropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public short Value
        {
            get
            {
                return GetInt16( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleInt32PropertyDataReader : SimplePropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  i32p.[Id], \r\n" +
            "  i32p.[EntityType], \r\n" +
            "  i32p.[RowVersion], \r\n" +
            "  i32p.[Element], \r\n" +
            "  i32p.[Definition], \r\n" +
            "  i32p.[Value] \r\n" +
            "FROM [Int32PropertyView] i32p \r\n";

        public new const string BaseViewName = "Int32PropertyView";
        public new const string ViewAliasName = "i32p";

        public const int VALUE_FIELD_ID = 4;

        public SimpleInt32PropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public int Value
        {
            get
            {
                return GetInt32( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleInt64PropertyDataReader : SimplePropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  i64p.[Id], \r\n" +
            "  i64p.[EntityType], \r\n" +
            "  i64p.[RowVersion], \r\n" +
            "  i64p.[Element], \r\n" +
            "  i64p.[Definition], \r\n" +
            "  i64p.[Value] \r\n" +
            "FROM [Int64PropertyView] i64p \r\n";

        public new const string BaseViewName = "Int64PropertyView";
        public new const string ViewAliasName = "i64p";

        public const int VALUE_FIELD_ID = 4;

        public SimpleInt64PropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public long Value
        {
            get
            {
                return GetInt64( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleReferencePropertyDataReader : SimplePropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rp.[Id], \r\n" +
            "  rp.[EntityType], \r\n" +
            "  rp.[RowVersion], \r\n" +
            "  rp.[Element], \r\n" +
            "  rp.[Definition], \r\n" +
            "  rp.[Value] \r\n" +
            "FROM [ReferencePropertyView] rp \r\n";

        public new const string BaseViewName = "ReferencePropertyView";
        public new const string ViewAliasName = "rp";

        public const int VALUE_FIELD_ID = 4;

        public SimpleReferencePropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Value
        {
            get
            {
                return GetGuid( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleSBytePropertyDataReader : SimplePropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  sp.[Id], \r\n" +
            "  sp.[EntityType], \r\n" +
            "  sp.[RowVersion], \r\n" +
            "  sp.[Element], \r\n" +
            "  sp.[Definition], \r\n" +
            "  sp.[Value] \r\n" +
            "FROM [SBytePropertyView] sp \r\n";

        public new const string BaseViewName = "SBytePropertyView";
        public new const string ViewAliasName = "sp";

        public const int VALUE_FIELD_ID = 4;

        public SimpleSBytePropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public sbyte Value
        {
            get
            {
                return GetSByte( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleSinglePropertyDataReader : SimplePropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  sip.[Id], \r\n" +
            "  sip.[EntityType], \r\n" +
            "  sip.[RowVersion], \r\n" +
            "  sip.[Element], \r\n" +
            "  sip.[Definition], \r\n" +
            "  sip.[Value] \r\n" +
            "FROM [SinglePropertyView] sip \r\n";

        public new const string BaseViewName = "SinglePropertyView";
        public new const string ViewAliasName = "sip";

        public const int VALUE_FIELD_ID = 4;

        public SimpleSinglePropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public float Value
        {
            get
            {
                return GetFloat( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleStringPropertyDataReader : SimplePropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  stp.[Id], \r\n" +
            "  stp.[EntityType], \r\n" +
            "  stp.[RowVersion], \r\n" +
            "  stp.[Element], \r\n" +
            "  stp.[Definition], \r\n" +
            "  stp.[Value] \r\n" +
            "FROM [StringPropertyView] stp \r\n";

        public new const string BaseViewName = "StringPropertyView";
        public new const string ViewAliasName = "stp";

        public const int VALUE_FIELD_ID = 4;

        public SimpleStringPropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public string Value
        {
            get
            {
                return GetString( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleTimeseriesPropertyDataReader : SimplePropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  tp.[Id], \r\n" +
            "  tp.[EntityType], \r\n" +
            "  tp.[RowVersion], \r\n" +
            "  tp.[Element], \r\n" +
            "  tp.[Definition] \r\n" +
            "FROM [TimeseriesPropertyView] tp \r\n";

        public new const string BaseViewName = "TimeseriesPropertyView";
        public new const string ViewAliasName = "tp";

        public SimpleTimeseriesPropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleBinaryTimeseriesPropertyDataReader : SimpleTimeseriesPropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  btp.[Id], \r\n" +
            "  btp.[EntityType], \r\n" +
            "  btp.[RowVersion], \r\n" +
            "  btp.[Element], \r\n" +
            "  btp.[Definition], \r\n" +
            "  btp.[Timeseries] \r\n" +
            "FROM [BinaryTimeseriesPropertyView] btp \r\n";

        public new const string BaseViewName = "BinaryTimeseriesPropertyView";
        public new const string ViewAliasName = "btp";

        public const int TIMESERIES_FIELD_ID = 4;

        public SimpleBinaryTimeseriesPropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
    }

    public class SimpleBooleanTimeseriesPropertyDataReader : SimpleTimeseriesPropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  botp.[Id], \r\n" +
            "  botp.[EntityType], \r\n" +
            "  botp.[RowVersion], \r\n" +
            "  botp.[Element], \r\n" +
            "  botp.[Definition], \r\n" +
            "  botp.[Timeseries] \r\n" +
            "FROM [BooleanTimeseriesPropertyView] botp \r\n";

        public new const string BaseViewName = "BooleanTimeseriesPropertyView";
        public new const string ViewAliasName = "botp";

        public const int TIMESERIES_FIELD_ID = 4;

        public SimpleBooleanTimeseriesPropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
    }

    public class SimpleByteTimeseriesPropertyDataReader : SimpleTimeseriesPropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  bytp.[Id], \r\n" +
            "  bytp.[EntityType], \r\n" +
            "  bytp.[RowVersion], \r\n" +
            "  bytp.[Element], \r\n" +
            "  bytp.[Definition], \r\n" +
            "  bytp.[Timeseries] \r\n" +
            "FROM [ByteTimeseriesPropertyView] bytp \r\n";

        public new const string BaseViewName = "ByteTimeseriesPropertyView";
        public new const string ViewAliasName = "bytp";

        public const int TIMESERIES_FIELD_ID = 4;

        public SimpleByteTimeseriesPropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
    }

    public class SimpleDateTimeTimeseriesPropertyDataReader : SimpleTimeseriesPropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  dttp.[Id], \r\n" +
            "  dttp.[EntityType], \r\n" +
            "  dttp.[RowVersion], \r\n" +
            "  dttp.[Element], \r\n" +
            "  dttp.[Definition], \r\n" +
            "  dttp.[Timeseries] \r\n" +
            "FROM [DateTimeTimeseriesPropertyView] dttp \r\n";

        public new const string BaseViewName = "DateTimeTimeseriesPropertyView";
        public new const string ViewAliasName = "dttp";

        public const int TIMESERIES_FIELD_ID = 4;

        public SimpleDateTimeTimeseriesPropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
    }

    public class SimpleDoubleTimeseriesPropertyDataReader : SimpleTimeseriesPropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  dotp.[Id], \r\n" +
            "  dotp.[EntityType], \r\n" +
            "  dotp.[RowVersion], \r\n" +
            "  dotp.[Element], \r\n" +
            "  dotp.[Definition], \r\n" +
            "  dotp.[Timeseries] \r\n" +
            "FROM [DoubleTimeseriesPropertyView] dotp \r\n";

        public new const string BaseViewName = "DoubleTimeseriesPropertyView";
        public new const string ViewAliasName = "dotp";

        public const int TIMESERIES_FIELD_ID = 4;

        public SimpleDoubleTimeseriesPropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
    }

    public class SimpleGuidTimeseriesPropertyDataReader : SimpleTimeseriesPropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  gtp.[Id], \r\n" +
            "  gtp.[EntityType], \r\n" +
            "  gtp.[RowVersion], \r\n" +
            "  gtp.[Element], \r\n" +
            "  gtp.[Definition], \r\n" +
            "  gtp.[Timeseries] \r\n" +
            "FROM [GuidTimeseriesPropertyView] gtp \r\n";

        public new const string BaseViewName = "GuidTimeseriesPropertyView";
        public new const string ViewAliasName = "gtp";

        public const int TIMESERIES_FIELD_ID = 4;

        public SimpleGuidTimeseriesPropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
    }

    public class SimpleInt16TimeseriesPropertyDataReader : SimpleTimeseriesPropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  i16tp.[Id], \r\n" +
            "  i16tp.[EntityType], \r\n" +
            "  i16tp.[RowVersion], \r\n" +
            "  i16tp.[Element], \r\n" +
            "  i16tp.[Definition], \r\n" +
            "  i16tp.[Timeseries] \r\n" +
            "FROM [Int16TimeseriesPropertyView] i16tp \r\n";

        public new const string BaseViewName = "Int16TimeseriesPropertyView";
        public new const string ViewAliasName = "i16tp";

        public const int TIMESERIES_FIELD_ID = 4;

        public SimpleInt16TimeseriesPropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
    }

    public class SimpleInt32TimeseriesPropertyDataReader : SimpleTimeseriesPropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  i32tp.[Id], \r\n" +
            "  i32tp.[EntityType], \r\n" +
            "  i32tp.[RowVersion], \r\n" +
            "  i32tp.[Element], \r\n" +
            "  i32tp.[Definition], \r\n" +
            "  i32tp.[Timeseries] \r\n" +
            "FROM [Int32TimeseriesPropertyView] i32tp \r\n";

        public new const string BaseViewName = "Int32TimeseriesPropertyView";
        public new const string ViewAliasName = "i32tp";

        public const int TIMESERIES_FIELD_ID = 4;

        public SimpleInt32TimeseriesPropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
    }

    public class SimpleInt64TimeseriesPropertyDataReader : SimpleTimeseriesPropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  i64tp.[Id], \r\n" +
            "  i64tp.[EntityType], \r\n" +
            "  i64tp.[RowVersion], \r\n" +
            "  i64tp.[Element], \r\n" +
            "  i64tp.[Definition], \r\n" +
            "  i64tp.[Timeseries] \r\n" +
            "FROM [Int64TimeseriesPropertyView] i64tp \r\n";

        public new const string BaseViewName = "Int64TimeseriesPropertyView";
        public new const string ViewAliasName = "i64tp";

        public const int TIMESERIES_FIELD_ID = 4;

        public SimpleInt64TimeseriesPropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
    }

    public class SimpleReferenceTimeseriesPropertyDataReader : SimpleTimeseriesPropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rtp.[Id], \r\n" +
            "  rtp.[EntityType], \r\n" +
            "  rtp.[RowVersion], \r\n" +
            "  rtp.[Element], \r\n" +
            "  rtp.[Definition], \r\n" +
            "  rtp.[Timeseries] \r\n" +
            "FROM [ReferenceTimeseriesPropertyView] rtp \r\n";

        public new const string BaseViewName = "ReferenceTimeseriesPropertyView";
        public new const string ViewAliasName = "rtp";

        public const int TIMESERIES_FIELD_ID = 4;

        public SimpleReferenceTimeseriesPropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
    }

    public class SimpleSByteTimeseriesPropertyDataReader : SimpleTimeseriesPropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  sbtp.[Id], \r\n" +
            "  sbtp.[EntityType], \r\n" +
            "  sbtp.[RowVersion], \r\n" +
            "  sbtp.[Element], \r\n" +
            "  sbtp.[Definition], \r\n" +
            "  sbtp.[Timeseries] \r\n" +
            "FROM [SByteTimeseriesPropertyView] sbtp \r\n";

        public new const string BaseViewName = "SByteTimeseriesPropertyView";
        public new const string ViewAliasName = "sbtp";

        public const int TIMESERIES_FIELD_ID = 4;

        public SimpleSByteTimeseriesPropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
    }

    public class SimpleSingleTimeseriesPropertyDataReader : SimpleTimeseriesPropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  sitp.[Id], \r\n" +
            "  sitp.[EntityType], \r\n" +
            "  sitp.[RowVersion], \r\n" +
            "  sitp.[Element], \r\n" +
            "  sitp.[Definition], \r\n" +
            "  sitp.[Timeseries] \r\n" +
            "FROM [SingleTimeseriesPropertyView] sitp \r\n";

        public new const string BaseViewName = "SingleTimeseriesPropertyView";
        public new const string ViewAliasName = "sitp";

        public const int TIMESERIES_FIELD_ID = 4;

        public SimpleSingleTimeseriesPropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
    }

    public class SimpleStringTimeseriesPropertyDataReader : SimpleTimeseriesPropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  sttp.[Id], \r\n" +
            "  sttp.[EntityType], \r\n" +
            "  sttp.[RowVersion], \r\n" +
            "  sttp.[Element], \r\n" +
            "  sttp.[Definition], \r\n" +
            "  sttp.[Timeseries] \r\n" +
            "FROM [StringTimeseriesPropertyView] sttp \r\n";

        public new const string BaseViewName = "StringTimeseriesPropertyView";
        public new const string ViewAliasName = "sttp";

        public const int TIMESERIES_FIELD_ID = 4;

        public SimpleStringTimeseriesPropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
    }

    public class SimpleTimeSpanTimeseriesPropertyDataReader : SimpleTimeseriesPropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  tstp.[Id], \r\n" +
            "  tstp.[EntityType], \r\n" +
            "  tstp.[RowVersion], \r\n" +
            "  tstp.[Element], \r\n" +
            "  tstp.[Definition], \r\n" +
            "  tstp.[Timeseries] \r\n" +
            "FROM [TimeSpanTimeseriesPropertyView] tstp \r\n";

        public new const string BaseViewName = "TimeSpanTimeseriesPropertyView";
        public new const string ViewAliasName = "tstp";

        public const int TIMESERIES_FIELD_ID = 4;

        public SimpleTimeSpanTimeseriesPropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
    }

    public class SimpleUInt16TimeseriesPropertyDataReader : SimpleTimeseriesPropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  u16tp.[Id], \r\n" +
            "  u16tp.[EntityType], \r\n" +
            "  u16tp.[RowVersion], \r\n" +
            "  u16tp.[Element], \r\n" +
            "  u16tp.[Definition], \r\n" +
            "  u16tp.[Timeseries] \r\n" +
            "FROM [UInt16TimeseriesPropertyView] u16tp \r\n";

        public new const string BaseViewName = "UInt16TimeseriesPropertyView";
        public new const string ViewAliasName = "u16tp";

        public const int TIMESERIES_FIELD_ID = 4;

        public SimpleUInt16TimeseriesPropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
    }

    public class SimpleUInt32TimeseriesPropertyDataReader : SimpleTimeseriesPropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  u32tp.[Id], \r\n" +
            "  u32tp.[EntityType], \r\n" +
            "  u32tp.[RowVersion], \r\n" +
            "  u32tp.[Element], \r\n" +
            "  u32tp.[Definition], \r\n" +
            "  u32tp.[Timeseries] \r\n" +
            "FROM [UInt32TimeseriesPropertyView] u32tp \r\n";

        public new const string BaseViewName = "UInt32TimeseriesPropertyView";
        public new const string ViewAliasName = "u32tp";

        public const int TIMESERIES_FIELD_ID = 4;

        public SimpleUInt32TimeseriesPropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
    }

    public class SimpleUInt64TimeseriesPropertyDataReader : SimpleTimeseriesPropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  u64tp.[Id], \r\n" +
            "  u64tp.[EntityType], \r\n" +
            "  u64tp.[RowVersion], \r\n" +
            "  u64tp.[Element], \r\n" +
            "  u64tp.[Definition], \r\n" +
            "  u64tp.[Timeseries] \r\n" +
            "FROM [UInt64TimeseriesPropertyView] u64tp \r\n";

        public new const string BaseViewName = "UInt64TimeseriesPropertyView";
        public new const string ViewAliasName = "u64tp";

        public const int TIMESERIES_FIELD_ID = 4;

        public SimpleUInt64TimeseriesPropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
    }

    public class SimpleTimeSpanPropertyDataReader : SimplePropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  tsp.[Id], \r\n" +
            "  tsp.[EntityType], \r\n" +
            "  tsp.[RowVersion], \r\n" +
            "  tsp.[Element], \r\n" +
            "  tsp.[Definition], \r\n" +
            "  tsp.[Value] \r\n" +
            "FROM [TimeSpanPropertyView] tsp \r\n";

        public new const string BaseViewName = "TimeSpanPropertyView";
        public new const string ViewAliasName = "tsp";

        public const int VALUE_FIELD_ID = 4;

        public SimpleTimeSpanPropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public TimeSpan Value
        {
            get
            {
                return new TimeSpan( GetInt64( VALUE_FIELD_ID ) );
            }
        }
    }

    public class SimpleUInt16PropertyDataReader : SimplePropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  u16p.[Id], \r\n" +
            "  u16p.[EntityType], \r\n" +
            "  u16p.[RowVersion], \r\n" +
            "  u16p.[Element], \r\n" +
            "  u16p.[Definition], \r\n" +
            "  u16p.[Value] \r\n" +
            "FROM [UInt16PropertyView] u16p \r\n";

        public new const string BaseViewName = "UInt16PropertyView";
        public new const string ViewAliasName = "u16p";

        public const int VALUE_FIELD_ID = 4;

        public SimpleUInt16PropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public ushort Value
        {
            get
            {
                return GetUInt16( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleUInt32PropertyDataReader : SimplePropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  u32p.[Id], \r\n" +
            "  u32p.[EntityType], \r\n" +
            "  u32p.[RowVersion], \r\n" +
            "  u32p.[Element], \r\n" +
            "  u32p.[Definition], \r\n" +
            "  u32p.[Value] \r\n" +
            "FROM [UInt32PropertyView] u32p \r\n";

        public new const string BaseViewName = "UInt32PropertyView";
        public new const string ViewAliasName = "u32p";

        public const int VALUE_FIELD_ID = 4;

        public SimpleUInt32PropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public uint Value
        {
            get
            {
                return GetUInt32( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleUInt64PropertyDataReader : SimplePropertyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  u64p.[Id], \r\n" +
            "  u64p.[EntityType], \r\n" +
            "  u64p.[RowVersion], \r\n" +
            "  u64p.[Element], \r\n" +
            "  u64p.[Definition], \r\n" +
            "  u64p.[Value] \r\n" +
            "FROM [UInt64PropertyView] u64p \r\n";

        public new const string BaseViewName = "UInt64PropertyView";
        public new const string ViewAliasName = "u64p";

        public const int VALUE_FIELD_ID = 4;

        public SimpleUInt64PropertyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public long Value
        {
            get
            {
                return GetInt64( VALUE_FIELD_ID );
            }
        }
    }

    public class SimplePropertyDefinitionDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  pd.[Id], \r\n" +
            "  pd.[EntityType], \r\n" +
            "  pd.[RowVersion], \r\n" +
            "  pd.[ElementType], \r\n" +
            "  pd.[Name], \r\n" +
            "  pd.[Description] \r\n" +
            "FROM [PropertyDefinitionView] pd \r\n";

        public const string BaseViewName = "PropertyDefinitionView";
        public const string ViewAliasName = "pd";

        public const int ID_FIELD_ID = 0;
        public const int ENTITYTYPE_FIELD_ID = 1;
        public const int ROWVERSION_FIELD_ID = 2;
        public const int ELEMENTTYPE_FIELD_ID = 3;
        public const int NAME_FIELD_ID = 4;
        public const int DESCRIPTION_FIELD_ID = 5;

        public SimplePropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public Types.Kind EntityType
        {
            get
            {
                return GetEnum<Types.Kind>( ENTITYTYPE_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid ElementType
        {
            get
            {
                return GetGuid( ELEMENTTYPE_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
        public string Description
        {
            get
            {
                return GetString( DESCRIPTION_FIELD_ID );
            }
        }
    }

    public class SimpleBinaryPropertyDefinitionDataReader : SimplePropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  bpd.[Id], \r\n" +
            "  bpd.[EntityType], \r\n" +
            "  bpd.[RowVersion], \r\n" +
            "  bpd.[ElementType], \r\n" +
            "  bpd.[Name], \r\n" +
            "  bpd.[Description], \r\n" +
            "  bpd.[DefaultValue] \r\n" +
            "FROM [BinaryPropertyDefinitionView] bpd \r\n";

        public new const string BaseViewName = "BinaryPropertyDefinitionView";
        public new const string ViewAliasName = "bpd";

        public const int DEFAULTVALUE_FIELD_ID = 5;

        public SimpleBinaryPropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public byte[] DefaultValue
        {
            get
            {
                return GetBytes( DEFAULTVALUE_FIELD_ID );
            }
        }
    }

    public class SimpleBooleanPropertyDefinitionDataReader : SimplePropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  bopd.[Id], \r\n" +
            "  bopd.[EntityType], \r\n" +
            "  bopd.[RowVersion], \r\n" +
            "  bopd.[ElementType], \r\n" +
            "  bopd.[Name], \r\n" +
            "  bopd.[Description], \r\n" +
            "  bopd.[DefaultValue] \r\n" +
            "FROM [BooleanPropertyDefinitionView] bopd \r\n";

        public new const string BaseViewName = "BooleanPropertyDefinitionView";
        public new const string ViewAliasName = "bopd";

        public const int DEFAULTVALUE_FIELD_ID = 5;

        public SimpleBooleanPropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public bool DefaultValue
        {
            get
            {
                return GetBoolean( DEFAULTVALUE_FIELD_ID );
            }
        }
    }

    public class SimpleBytePropertyDefinitionDataReader : SimplePropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  bypd.[Id], \r\n" +
            "  bypd.[EntityType], \r\n" +
            "  bypd.[RowVersion], \r\n" +
            "  bypd.[ElementType], \r\n" +
            "  bypd.[Name], \r\n" +
            "  bypd.[Description], \r\n" +
            "  bypd.[DefaultValue], \r\n" +
            "  bypd.[MinValue], \r\n" +
            "  bypd.[MaxValue] \r\n" +
            "FROM [BytePropertyDefinitionView] bypd \r\n";

        public new const string BaseViewName = "BytePropertyDefinitionView";
        public new const string ViewAliasName = "bypd";

        public const int DEFAULTVALUE_FIELD_ID = 5;
        public const int MINVALUE_FIELD_ID = 6;
        public const int MAXVALUE_FIELD_ID = 7;

        public SimpleBytePropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public byte DefaultValue
        {
            get
            {
                return GetByte( DEFAULTVALUE_FIELD_ID );
            }
        }
        public byte MinValue
        {
            get
            {
                return GetByte( MINVALUE_FIELD_ID );
            }
        }
        public byte MaxValue
        {
            get
            {
                return GetByte( MAXVALUE_FIELD_ID );
            }
        }
    }

    public class SimpleDateTimePropertyDefinitionDataReader : SimplePropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  dtpd.[Id], \r\n" +
            "  dtpd.[EntityType], \r\n" +
            "  dtpd.[RowVersion], \r\n" +
            "  dtpd.[ElementType], \r\n" +
            "  dtpd.[Name], \r\n" +
            "  dtpd.[Description], \r\n" +
            "  dtpd.[DefaultValue], \r\n" +
            "  dtpd.[MinValue], \r\n" +
            "  dtpd.[MaxValue] \r\n" +
            "FROM [DateTimePropertyDefinitionView] dtpd \r\n";

        public new const string BaseViewName = "DateTimePropertyDefinitionView";
        public new const string ViewAliasName = "dtpd";

        public const int DEFAULTVALUE_FIELD_ID = 5;
        public const int MINVALUE_FIELD_ID = 6;
        public const int MAXVALUE_FIELD_ID = 7;

        public SimpleDateTimePropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public string DefaultValue
        {
            get
            {
                return GetString( DEFAULTVALUE_FIELD_ID );
            }
        }
        public string MinValue
        {
            get
            {
                return GetString( MINVALUE_FIELD_ID );
            }
        }
        public string MaxValue
        {
            get
            {
                return GetString( MAXVALUE_FIELD_ID );
            }
        }
    }

    public class SimpleDoublePropertyDefinitionDataReader : SimplePropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  dpd.[Id], \r\n" +
            "  dpd.[EntityType], \r\n" +
            "  dpd.[RowVersion], \r\n" +
            "  dpd.[ElementType], \r\n" +
            "  dpd.[Name], \r\n" +
            "  dpd.[Description], \r\n" +
            "  dpd.[DefaultValue], \r\n" +
            "  dpd.[MinValue], \r\n" +
            "  dpd.[MaxValue] \r\n" +
            "FROM [DoublePropertyDefinitionView] dpd \r\n";

        public new const string BaseViewName = "DoublePropertyDefinitionView";
        public new const string ViewAliasName = "dpd";

        public const int DEFAULTVALUE_FIELD_ID = 5;
        public const int MINVALUE_FIELD_ID = 6;
        public const int MAXVALUE_FIELD_ID = 7;

        public SimpleDoublePropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public double DefaultValue
        {
            get
            {
                return GetDouble( DEFAULTVALUE_FIELD_ID );
            }
        }
        public double MinValue
        {
            get
            {
                return GetDouble( MINVALUE_FIELD_ID );
            }
        }
        public double MaxValue
        {
            get
            {
                return GetDouble( MAXVALUE_FIELD_ID );
            }
        }
    }

    public class SimpleGuidPropertyDefinitionDataReader : SimplePropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  gpd.[Id], \r\n" +
            "  gpd.[EntityType], \r\n" +
            "  gpd.[RowVersion], \r\n" +
            "  gpd.[ElementType], \r\n" +
            "  gpd.[Name], \r\n" +
            "  gpd.[Description], \r\n" +
            "  gpd.[DefaultValue] \r\n" +
            "FROM [GuidPropertyDefinitionView] gpd \r\n";

        public new const string BaseViewName = "GuidPropertyDefinitionView";
        public new const string ViewAliasName = "gpd";

        public const int DEFAULTVALUE_FIELD_ID = 5;

        public SimpleGuidPropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid DefaultValue
        {
            get
            {
                return GetGuid( DEFAULTVALUE_FIELD_ID );
            }
        }
    }

    public class SimpleInt16PropertyDefinitionDataReader : SimplePropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  i16pd.[Id], \r\n" +
            "  i16pd.[EntityType], \r\n" +
            "  i16pd.[RowVersion], \r\n" +
            "  i16pd.[ElementType], \r\n" +
            "  i16pd.[Name], \r\n" +
            "  i16pd.[Description], \r\n" +
            "  i16pd.[DefaultValue], \r\n" +
            "  i16pd.[MinValue], \r\n" +
            "  i16pd.[MaxValue] \r\n" +
            "FROM [Int16PropertyDefinitionView] i16pd \r\n";

        public new const string BaseViewName = "Int16PropertyDefinitionView";
        public new const string ViewAliasName = "i16pd";

        public const int DEFAULTVALUE_FIELD_ID = 5;
        public const int MINVALUE_FIELD_ID = 6;
        public const int MAXVALUE_FIELD_ID = 7;

        public SimpleInt16PropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public short DefaultValue
        {
            get
            {
                return GetInt16( DEFAULTVALUE_FIELD_ID );
            }
        }
        public short MinValue
        {
            get
            {
                return GetInt16( MINVALUE_FIELD_ID );
            }
        }
        public short MaxValue
        {
            get
            {
                return GetInt16( MAXVALUE_FIELD_ID );
            }
        }
    }

    public class SimpleInt32PropertyDefinitionDataReader : SimplePropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  i32pd.[Id], \r\n" +
            "  i32pd.[EntityType], \r\n" +
            "  i32pd.[RowVersion], \r\n" +
            "  i32pd.[ElementType], \r\n" +
            "  i32pd.[Name], \r\n" +
            "  i32pd.[Description], \r\n" +
            "  i32pd.[DefaultValue], \r\n" +
            "  i32pd.[MinValue], \r\n" +
            "  i32pd.[MaxValue] \r\n" +
            "FROM [Int32PropertyDefinitionView] i32pd \r\n";

        public new const string BaseViewName = "Int32PropertyDefinitionView";
        public new const string ViewAliasName = "i32pd";

        public const int DEFAULTVALUE_FIELD_ID = 5;
        public const int MINVALUE_FIELD_ID = 6;
        public const int MAXVALUE_FIELD_ID = 7;

        public SimpleInt32PropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public int DefaultValue
        {
            get
            {
                return GetInt32( DEFAULTVALUE_FIELD_ID );
            }
        }
        public int MinValue
        {
            get
            {
                return GetInt32( MINVALUE_FIELD_ID );
            }
        }
        public int MaxValue
        {
            get
            {
                return GetInt32( MAXVALUE_FIELD_ID );
            }
        }
    }

    public class SimpleInt64PropertyDefinitionDataReader : SimplePropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  i64pd.[Id], \r\n" +
            "  i64pd.[EntityType], \r\n" +
            "  i64pd.[RowVersion], \r\n" +
            "  i64pd.[ElementType], \r\n" +
            "  i64pd.[Name], \r\n" +
            "  i64pd.[Description], \r\n" +
            "  i64pd.[DefaultValue], \r\n" +
            "  i64pd.[MinValue], \r\n" +
            "  i64pd.[MaxValue] \r\n" +
            "FROM [Int64PropertyDefinitionView] i64pd \r\n";

        public new const string BaseViewName = "Int64PropertyDefinitionView";
        public new const string ViewAliasName = "i64pd";

        public const int DEFAULTVALUE_FIELD_ID = 5;
        public const int MINVALUE_FIELD_ID = 6;
        public const int MAXVALUE_FIELD_ID = 7;

        public SimpleInt64PropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public long DefaultValue
        {
            get
            {
                return GetInt64( DEFAULTVALUE_FIELD_ID );
            }
        }
        public long MinValue
        {
            get
            {
                return GetInt64( MINVALUE_FIELD_ID );
            }
        }
        public long MaxValue
        {
            get
            {
                return GetInt64( MAXVALUE_FIELD_ID );
            }
        }
    }

    public class SimpleReferencePropertyDefinitionDataReader : SimplePropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rpd.[Id], \r\n" +
            "  rpd.[EntityType], \r\n" +
            "  rpd.[RowVersion], \r\n" +
            "  rpd.[ElementType], \r\n" +
            "  rpd.[Name], \r\n" +
            "  rpd.[Description], \r\n" +
            "  rpd.[DefaultValue], \r\n" +
            "  rpd.[ReferencedElementType] \r\n" +
            "FROM [ReferencePropertyDefinitionView] rpd \r\n";

        public new const string BaseViewName = "ReferencePropertyDefinitionView";
        public new const string ViewAliasName = "rpd";

        public const int DEFAULTVALUE_FIELD_ID = 5;
        public const int REFERENCEDELEMENTTYPE_FIELD_ID = 6;

        public SimpleReferencePropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid DefaultValue
        {
            get
            {
                return GetGuid( DEFAULTVALUE_FIELD_ID );
            }
        }
        public Guid ReferencedElementType
        {
            get
            {
                return GetGuid( REFERENCEDELEMENTTYPE_FIELD_ID );
            }
        }
    }

    public class SimpleSBytePropertyDefinitionDataReader : SimplePropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  sbpd.[Id], \r\n" +
            "  sbpd.[EntityType], \r\n" +
            "  sbpd.[RowVersion], \r\n" +
            "  sbpd.[ElementType], \r\n" +
            "  sbpd.[Name], \r\n" +
            "  sbpd.[Description], \r\n" +
            "  sbpd.[DefaultValue], \r\n" +
            "  sbpd.[MinValue], \r\n" +
            "  sbpd.[MaxValue] \r\n" +
            "FROM [SBytePropertyDefinitionView] sbpd \r\n";

        public new const string BaseViewName = "SBytePropertyDefinitionView";
        public new const string ViewAliasName = "sbpd";

        public const int DEFAULTVALUE_FIELD_ID = 5;
        public const int MINVALUE_FIELD_ID = 6;
        public const int MAXVALUE_FIELD_ID = 7;

        public SimpleSBytePropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public sbyte DefaultValue
        {
            get
            {
                return GetSByte( DEFAULTVALUE_FIELD_ID );
            }
        }
        public sbyte MinValue
        {
            get
            {
                return GetSByte( MINVALUE_FIELD_ID );
            }
        }
        public sbyte MaxValue
        {
            get
            {
                return GetSByte( MAXVALUE_FIELD_ID );
            }
        }
    }

    public class SimpleSinglePropertyDefinitionDataReader : SimplePropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  sipd.[Id], \r\n" +
            "  sipd.[EntityType], \r\n" +
            "  sipd.[RowVersion], \r\n" +
            "  sipd.[ElementType], \r\n" +
            "  sipd.[Name], \r\n" +
            "  sipd.[Description], \r\n" +
            "  sipd.[DefaultValue], \r\n" +
            "  sipd.[MinValue], \r\n" +
            "  sipd.[MaxValue] \r\n" +
            "FROM [SinglePropertyDefinitionView] sipd \r\n";

        public new const string BaseViewName = "SinglePropertyDefinitionView";
        public new const string ViewAliasName = "sipd";

        public const int DEFAULTVALUE_FIELD_ID = 5;
        public const int MINVALUE_FIELD_ID = 6;
        public const int MAXVALUE_FIELD_ID = 7;

        public SimpleSinglePropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public float DefaultValue
        {
            get
            {
                return GetFloat( DEFAULTVALUE_FIELD_ID );
            }
        }
        public float MinValue
        {
            get
            {
                return GetFloat( MINVALUE_FIELD_ID );
            }
        }
        public float MaxValue
        {
            get
            {
                return GetFloat( MAXVALUE_FIELD_ID );
            }
        }
    }

    public class SimpleStringPropertyDefinitionDataReader : SimplePropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  stpd.[Id], \r\n" +
            "  stpd.[EntityType], \r\n" +
            "  stpd.[RowVersion], \r\n" +
            "  stpd.[ElementType], \r\n" +
            "  stpd.[Name], \r\n" +
            "  stpd.[Description], \r\n" +
            "  stpd.[DefaultValue], \r\n" +
            "  stpd.[Pattern] \r\n" +
            "FROM [StringPropertyDefinitionView] stpd \r\n";

        public new const string BaseViewName = "StringPropertyDefinitionView";
        public new const string ViewAliasName = "stpd";

        public const int DEFAULTVALUE_FIELD_ID = 5;
        public const int PATTERN_FIELD_ID = 6;

        public SimpleStringPropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public string DefaultValue
        {
            get
            {
                return GetString( DEFAULTVALUE_FIELD_ID );
            }
        }
        public string Pattern
        {
            get
            {
                return GetString( PATTERN_FIELD_ID );
            }
        }
    }

    public class SimpleTimeseriesPropertyDefinitionDataReader : SimplePropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  tpd.[Id], \r\n" +
            "  tpd.[EntityType], \r\n" +
            "  tpd.[RowVersion], \r\n" +
            "  tpd.[ElementType], \r\n" +
            "  tpd.[Name], \r\n" +
            "  tpd.[Description] \r\n" +
            "FROM [TimeseriesPropertyDefinitionView] tpd \r\n";

        public new const string BaseViewName = "TimeseriesPropertyDefinitionView";
        public new const string ViewAliasName = "tpd";

        public SimpleTimeseriesPropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleBinaryTimeseriesPropertyDefinitionDataReader : SimpleTimeseriesPropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  btpd.[Id], \r\n" +
            "  btpd.[EntityType], \r\n" +
            "  btpd.[RowVersion], \r\n" +
            "  btpd.[ElementType], \r\n" +
            "  btpd.[Name], \r\n" +
            "  btpd.[Description] \r\n" +
            "FROM [BinaryTimeseriesPropertyDefinitionView] btpd \r\n";

        public new const string BaseViewName = "BinaryTimeseriesPropertyDefinitionView";
        public new const string ViewAliasName = "btpd";

        public SimpleBinaryTimeseriesPropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleBooleanTimeseriesPropertyDefinitionDataReader : SimpleTimeseriesPropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  botpd.[Id], \r\n" +
            "  botpd.[EntityType], \r\n" +
            "  botpd.[RowVersion], \r\n" +
            "  botpd.[ElementType], \r\n" +
            "  botpd.[Name], \r\n" +
            "  botpd.[Description] \r\n" +
            "FROM [BooleanTimeseriesPropertyDefinitionView] botpd \r\n";

        public new const string BaseViewName = "BooleanTimeseriesPropertyDefinitionView";
        public new const string ViewAliasName = "botpd";

        public SimpleBooleanTimeseriesPropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleByteTimeseriesPropertyDefinitionDataReader : SimpleTimeseriesPropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  bytpd.[Id], \r\n" +
            "  bytpd.[EntityType], \r\n" +
            "  bytpd.[RowVersion], \r\n" +
            "  bytpd.[ElementType], \r\n" +
            "  bytpd.[Name], \r\n" +
            "  bytpd.[Description], \r\n" +
            "  bytpd.[MinValue], \r\n" +
            "  bytpd.[MaxValue] \r\n" +
            "FROM [ByteTimeseriesPropertyDefinitionView] bytpd \r\n";

        public new const string BaseViewName = "ByteTimeseriesPropertyDefinitionView";
        public new const string ViewAliasName = "bytpd";

        public const int MINVALUE_FIELD_ID = 5;
        public const int MAXVALUE_FIELD_ID = 6;

        public SimpleByteTimeseriesPropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public byte MinValue
        {
            get
            {
                return GetByte( MINVALUE_FIELD_ID );
            }
        }
        public byte MaxValue
        {
            get
            {
                return GetByte( MAXVALUE_FIELD_ID );
            }
        }
    }

    public class SimpleDateTimeTimeseriesPropertyDefinitionDataReader : SimpleTimeseriesPropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  dttpd.[Id], \r\n" +
            "  dttpd.[EntityType], \r\n" +
            "  dttpd.[RowVersion], \r\n" +
            "  dttpd.[ElementType], \r\n" +
            "  dttpd.[Name], \r\n" +
            "  dttpd.[Description], \r\n" +
            "  dttpd.[MinValue], \r\n" +
            "  dttpd.[MaxValue] \r\n" +
            "FROM [DateTimeTimeseriesPropertyDefinitionView] dttpd \r\n";

        public new const string BaseViewName = "DateTimeTimeseriesPropertyDefinitionView";
        public new const string ViewAliasName = "dttpd";

        public const int MINVALUE_FIELD_ID = 5;
        public const int MAXVALUE_FIELD_ID = 6;

        public SimpleDateTimeTimeseriesPropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public string MinValue
        {
            get
            {
                return GetString( MINVALUE_FIELD_ID );
            }
        }
        public string MaxValue
        {
            get
            {
                return GetString( MAXVALUE_FIELD_ID );
            }
        }
    }

    public class SimpleDoubleTimeseriesPropertyDefinitionDataReader : SimpleTimeseriesPropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  dotpd.[Id], \r\n" +
            "  dotpd.[EntityType], \r\n" +
            "  dotpd.[RowVersion], \r\n" +
            "  dotpd.[ElementType], \r\n" +
            "  dotpd.[Name], \r\n" +
            "  dotpd.[Description], \r\n" +
            "  dotpd.[MinValue], \r\n" +
            "  dotpd.[MaxValue] \r\n" +
            "FROM [DoubleTimeseriesPropertyDefinitionView] dotpd \r\n";

        public new const string BaseViewName = "DoubleTimeseriesPropertyDefinitionView";
        public new const string ViewAliasName = "dotpd";

        public const int MINVALUE_FIELD_ID = 5;
        public const int MAXVALUE_FIELD_ID = 6;

        public SimpleDoubleTimeseriesPropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public double MinValue
        {
            get
            {
                return GetDouble( MINVALUE_FIELD_ID );
            }
        }
        public double MaxValue
        {
            get
            {
                return GetDouble( MAXVALUE_FIELD_ID );
            }
        }
    }

    public class SimpleGuidTimeseriesPropertyDefinitionDataReader : SimpleTimeseriesPropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  gtpd.[Id], \r\n" +
            "  gtpd.[EntityType], \r\n" +
            "  gtpd.[RowVersion], \r\n" +
            "  gtpd.[ElementType], \r\n" +
            "  gtpd.[Name], \r\n" +
            "  gtpd.[Description] \r\n" +
            "FROM [GuidTimeseriesPropertyDefinitionView] gtpd \r\n";

        public new const string BaseViewName = "GuidTimeseriesPropertyDefinitionView";
        public new const string ViewAliasName = "gtpd";

        public SimpleGuidTimeseriesPropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleInt16TimeseriesPropertyDefinitionDataReader : SimpleTimeseriesPropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  i16tpd.[Id], \r\n" +
            "  i16tpd.[EntityType], \r\n" +
            "  i16tpd.[RowVersion], \r\n" +
            "  i16tpd.[ElementType], \r\n" +
            "  i16tpd.[Name], \r\n" +
            "  i16tpd.[Description], \r\n" +
            "  i16tpd.[MinValue], \r\n" +
            "  i16tpd.[MaxValue] \r\n" +
            "FROM [Int16TimeseriesPropertyDefinitionView] i16tpd \r\n";

        public new const string BaseViewName = "Int16TimeseriesPropertyDefinitionView";
        public new const string ViewAliasName = "i16tpd";

        public const int MINVALUE_FIELD_ID = 5;
        public const int MAXVALUE_FIELD_ID = 6;

        public SimpleInt16TimeseriesPropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public short MinValue
        {
            get
            {
                return GetInt16( MINVALUE_FIELD_ID );
            }
        }
        public short MaxValue
        {
            get
            {
                return GetInt16( MAXVALUE_FIELD_ID );
            }
        }
    }

    public class SimpleInt32TimeseriesPropertyDefinitionDataReader : SimpleTimeseriesPropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  i32tpd.[Id], \r\n" +
            "  i32tpd.[EntityType], \r\n" +
            "  i32tpd.[RowVersion], \r\n" +
            "  i32tpd.[ElementType], \r\n" +
            "  i32tpd.[Name], \r\n" +
            "  i32tpd.[Description], \r\n" +
            "  i32tpd.[MinValue], \r\n" +
            "  i32tpd.[MaxValue] \r\n" +
            "FROM [Int32TimeseriesPropertyDefinitionView] i32tpd \r\n";

        public new const string BaseViewName = "Int32TimeseriesPropertyDefinitionView";
        public new const string ViewAliasName = "i32tpd";

        public const int MINVALUE_FIELD_ID = 5;
        public const int MAXVALUE_FIELD_ID = 6;

        public SimpleInt32TimeseriesPropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public int MinValue
        {
            get
            {
                return GetInt32( MINVALUE_FIELD_ID );
            }
        }
        public int MaxValue
        {
            get
            {
                return GetInt32( MAXVALUE_FIELD_ID );
            }
        }
    }

    public class SimpleInt64TimeseriesPropertyDefinitionDataReader : SimpleTimeseriesPropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  i64tpd.[Id], \r\n" +
            "  i64tpd.[EntityType], \r\n" +
            "  i64tpd.[RowVersion], \r\n" +
            "  i64tpd.[ElementType], \r\n" +
            "  i64tpd.[Name], \r\n" +
            "  i64tpd.[Description], \r\n" +
            "  i64tpd.[MinValue], \r\n" +
            "  i64tpd.[MaxValue] \r\n" +
            "FROM [Int64TimeseriesPropertyDefinitionView] i64tpd \r\n";

        public new const string BaseViewName = "Int64TimeseriesPropertyDefinitionView";
        public new const string ViewAliasName = "i64tpd";

        public const int MINVALUE_FIELD_ID = 5;
        public const int MAXVALUE_FIELD_ID = 6;

        public SimpleInt64TimeseriesPropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public long MinValue
        {
            get
            {
                return GetInt64( MINVALUE_FIELD_ID );
            }
        }
        public long MaxValue
        {
            get
            {
                return GetInt64( MAXVALUE_FIELD_ID );
            }
        }
    }

    public class SimpleReferenceTimeseriesPropertyDefinitionDataReader : SimpleTimeseriesPropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rtpd.[Id], \r\n" +
            "  rtpd.[EntityType], \r\n" +
            "  rtpd.[RowVersion], \r\n" +
            "  rtpd.[ElementType], \r\n" +
            "  rtpd.[Name], \r\n" +
            "  rtpd.[Description], \r\n" +
            "  rtpd.[ReferencedElementType] \r\n" +
            "FROM [ReferenceTimeseriesPropertyDefinitionView] rtpd \r\n";

        public new const string BaseViewName = "ReferenceTimeseriesPropertyDefinitionView";
        public new const string ViewAliasName = "rtpd";

        public const int REFERENCEDELEMENTTYPE_FIELD_ID = 5;

        public SimpleReferenceTimeseriesPropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid ReferencedElementType
        {
            get
            {
                return GetGuid( REFERENCEDELEMENTTYPE_FIELD_ID );
            }
        }
    }

    public class SimpleSByteTimeseriesPropertyDefinitionDataReader : SimpleTimeseriesPropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  sbtpd.[Id], \r\n" +
            "  sbtpd.[EntityType], \r\n" +
            "  sbtpd.[RowVersion], \r\n" +
            "  sbtpd.[ElementType], \r\n" +
            "  sbtpd.[Name], \r\n" +
            "  sbtpd.[Description], \r\n" +
            "  sbtpd.[MinValue], \r\n" +
            "  sbtpd.[MaxValue] \r\n" +
            "FROM [SByteTimeseriesPropertyDefinitionView] sbtpd \r\n";

        public new const string BaseViewName = "SByteTimeseriesPropertyDefinitionView";
        public new const string ViewAliasName = "sbtpd";

        public const int MINVALUE_FIELD_ID = 5;
        public const int MAXVALUE_FIELD_ID = 6;

        public SimpleSByteTimeseriesPropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public sbyte MinValue
        {
            get
            {
                return GetSByte( MINVALUE_FIELD_ID );
            }
        }
        public sbyte MaxValue
        {
            get
            {
                return GetSByte( MAXVALUE_FIELD_ID );
            }
        }
    }

    public class SimpleSingleTimeseriesPropertyDefinitionDataReader : SimpleTimeseriesPropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  sitpd.[Id], \r\n" +
            "  sitpd.[EntityType], \r\n" +
            "  sitpd.[RowVersion], \r\n" +
            "  sitpd.[ElementType], \r\n" +
            "  sitpd.[Name], \r\n" +
            "  sitpd.[Description], \r\n" +
            "  sitpd.[MinValue], \r\n" +
            "  sitpd.[MaxValue] \r\n" +
            "FROM [SingleTimeseriesPropertyDefinitionView] sitpd \r\n";

        public new const string BaseViewName = "SingleTimeseriesPropertyDefinitionView";
        public new const string ViewAliasName = "sitpd";

        public const int MINVALUE_FIELD_ID = 5;
        public const int MAXVALUE_FIELD_ID = 6;

        public SimpleSingleTimeseriesPropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public float MinValue
        {
            get
            {
                return GetFloat( MINVALUE_FIELD_ID );
            }
        }
        public float MaxValue
        {
            get
            {
                return GetFloat( MAXVALUE_FIELD_ID );
            }
        }
    }

    public class SimpleStringTimeseriesPropertyDefinitionDataReader : SimpleTimeseriesPropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  sttpd.[Id], \r\n" +
            "  sttpd.[EntityType], \r\n" +
            "  sttpd.[RowVersion], \r\n" +
            "  sttpd.[ElementType], \r\n" +
            "  sttpd.[Name], \r\n" +
            "  sttpd.[Description], \r\n" +
            "  sttpd.[Pattern] \r\n" +
            "FROM [StringTimeseriesPropertyDefinitionView] sttpd \r\n";

        public new const string BaseViewName = "StringTimeseriesPropertyDefinitionView";
        public new const string ViewAliasName = "sttpd";

        public const int PATTERN_FIELD_ID = 5;

        public SimpleStringTimeseriesPropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public string Pattern
        {
            get
            {
                return GetString( PATTERN_FIELD_ID );
            }
        }
    }

    public class SimpleTimeSpanTimeseriesPropertyDefinitionDataReader : SimpleTimeseriesPropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  tstpd.[Id], \r\n" +
            "  tstpd.[EntityType], \r\n" +
            "  tstpd.[RowVersion], \r\n" +
            "  tstpd.[ElementType], \r\n" +
            "  tstpd.[Name], \r\n" +
            "  tstpd.[Description], \r\n" +
            "  tstpd.[MinValue], \r\n" +
            "  tstpd.[MaxValue] \r\n" +
            "FROM [TimeSpanTimeseriesPropertyDefinitionView] tstpd \r\n";

        public new const string BaseViewName = "TimeSpanTimeseriesPropertyDefinitionView";
        public new const string ViewAliasName = "tstpd";

        public const int MINVALUE_FIELD_ID = 5;
        public const int MAXVALUE_FIELD_ID = 6;

        public SimpleTimeSpanTimeseriesPropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public TimeSpan MinValue
        {
            get
            {
                return new TimeSpan( GetInt64( MINVALUE_FIELD_ID ) );
            }
        }
        public TimeSpan MaxValue
        {
            get
            {
                return new TimeSpan( GetInt64( MAXVALUE_FIELD_ID ) );
            }
        }
    }

    public class SimpleUInt16TimeseriesPropertyDefinitionDataReader : SimpleTimeseriesPropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  u16tpd.[Id], \r\n" +
            "  u16tpd.[EntityType], \r\n" +
            "  u16tpd.[RowVersion], \r\n" +
            "  u16tpd.[ElementType], \r\n" +
            "  u16tpd.[Name], \r\n" +
            "  u16tpd.[Description], \r\n" +
            "  u16tpd.[MinValue], \r\n" +
            "  u16tpd.[MaxValue] \r\n" +
            "FROM [UInt16TimeseriesPropertyDefinitionView] u16tpd \r\n";

        public new const string BaseViewName = "UInt16TimeseriesPropertyDefinitionView";
        public new const string ViewAliasName = "u16tpd";

        public const int MINVALUE_FIELD_ID = 5;
        public const int MAXVALUE_FIELD_ID = 6;

        public SimpleUInt16TimeseriesPropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public ushort MinValue
        {
            get
            {
                return GetUInt16( MINVALUE_FIELD_ID );
            }
        }
        public ushort MaxValue
        {
            get
            {
                return GetUInt16( MAXVALUE_FIELD_ID );
            }
        }
    }

    public class SimpleUInt32TimeseriesPropertyDefinitionDataReader : SimpleTimeseriesPropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  u32tpd.[Id], \r\n" +
            "  u32tpd.[EntityType], \r\n" +
            "  u32tpd.[RowVersion], \r\n" +
            "  u32tpd.[ElementType], \r\n" +
            "  u32tpd.[Name], \r\n" +
            "  u32tpd.[Description], \r\n" +
            "  u32tpd.[MinValue], \r\n" +
            "  u32tpd.[MaxValue] \r\n" +
            "FROM [UInt32TimeseriesPropertyDefinitionView] u32tpd \r\n";

        public new const string BaseViewName = "UInt32TimeseriesPropertyDefinitionView";
        public new const string ViewAliasName = "u32tpd";

        public const int MINVALUE_FIELD_ID = 5;
        public const int MAXVALUE_FIELD_ID = 6;

        public SimpleUInt32TimeseriesPropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public uint MinValue
        {
            get
            {
                return GetUInt32( MINVALUE_FIELD_ID );
            }
        }
        public uint MaxValue
        {
            get
            {
                return GetUInt32( MAXVALUE_FIELD_ID );
            }
        }
    }

    public class SimpleUInt64TimeseriesPropertyDefinitionDataReader : SimpleTimeseriesPropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  u64tpd.[Id], \r\n" +
            "  u64tpd.[EntityType], \r\n" +
            "  u64tpd.[RowVersion], \r\n" +
            "  u64tpd.[ElementType], \r\n" +
            "  u64tpd.[Name], \r\n" +
            "  u64tpd.[Description], \r\n" +
            "  u64tpd.[MinValue], \r\n" +
            "  u64tpd.[MaxValue] \r\n" +
            "FROM [UInt64TimeseriesPropertyDefinitionView] u64tpd \r\n";

        public new const string BaseViewName = "UInt64TimeseriesPropertyDefinitionView";
        public new const string ViewAliasName = "u64tpd";

        public const int MINVALUE_FIELD_ID = 5;
        public const int MAXVALUE_FIELD_ID = 6;

        public SimpleUInt64TimeseriesPropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public long MinValue
        {
            get
            {
                return GetInt64( MINVALUE_FIELD_ID );
            }
        }
        public long MaxValue
        {
            get
            {
                return GetInt64( MAXVALUE_FIELD_ID );
            }
        }
    }

    public class SimpleTimeSpanPropertyDefinitionDataReader : SimplePropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  tspd.[Id], \r\n" +
            "  tspd.[EntityType], \r\n" +
            "  tspd.[RowVersion], \r\n" +
            "  tspd.[ElementType], \r\n" +
            "  tspd.[Name], \r\n" +
            "  tspd.[Description], \r\n" +
            "  tspd.[DefaultValue], \r\n" +
            "  tspd.[MinValue], \r\n" +
            "  tspd.[MaxValue] \r\n" +
            "FROM [TimeSpanPropertyDefinitionView] tspd \r\n";

        public new const string BaseViewName = "TimeSpanPropertyDefinitionView";
        public new const string ViewAliasName = "tspd";

        public const int DEFAULTVALUE_FIELD_ID = 5;
        public const int MINVALUE_FIELD_ID = 6;
        public const int MAXVALUE_FIELD_ID = 7;

        public SimpleTimeSpanPropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public TimeSpan DefaultValue
        {
            get
            {
                return new TimeSpan( GetInt64( DEFAULTVALUE_FIELD_ID ) );
            }
        }
        public TimeSpan MinValue
        {
            get
            {
                return new TimeSpan( GetInt64( MINVALUE_FIELD_ID ) );
            }
        }
        public TimeSpan MaxValue
        {
            get
            {
                return new TimeSpan( GetInt64( MAXVALUE_FIELD_ID ) );
            }
        }
    }

    public class SimpleUInt16PropertyDefinitionDataReader : SimplePropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  u16pd.[Id], \r\n" +
            "  u16pd.[EntityType], \r\n" +
            "  u16pd.[RowVersion], \r\n" +
            "  u16pd.[ElementType], \r\n" +
            "  u16pd.[Name], \r\n" +
            "  u16pd.[Description], \r\n" +
            "  u16pd.[DefaultValue], \r\n" +
            "  u16pd.[MinValue], \r\n" +
            "  u16pd.[MaxValue] \r\n" +
            "FROM [UInt16PropertyDefinitionView] u16pd \r\n";

        public new const string BaseViewName = "UInt16PropertyDefinitionView";
        public new const string ViewAliasName = "u16pd";

        public const int DEFAULTVALUE_FIELD_ID = 5;
        public const int MINVALUE_FIELD_ID = 6;
        public const int MAXVALUE_FIELD_ID = 7;

        public SimpleUInt16PropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public ushort DefaultValue
        {
            get
            {
                return GetUInt16( DEFAULTVALUE_FIELD_ID );
            }
        }
        public ushort MinValue
        {
            get
            {
                return GetUInt16( MINVALUE_FIELD_ID );
            }
        }
        public ushort MaxValue
        {
            get
            {
                return GetUInt16( MAXVALUE_FIELD_ID );
            }
        }
    }

    public class SimpleUInt32PropertyDefinitionDataReader : SimplePropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  u32pd.[Id], \r\n" +
            "  u32pd.[EntityType], \r\n" +
            "  u32pd.[RowVersion], \r\n" +
            "  u32pd.[ElementType], \r\n" +
            "  u32pd.[Name], \r\n" +
            "  u32pd.[Description], \r\n" +
            "  u32pd.[DefaultValue], \r\n" +
            "  u32pd.[MinValue], \r\n" +
            "  u32pd.[MaxValue] \r\n" +
            "FROM [UInt32PropertyDefinitionView] u32pd \r\n";

        public new const string BaseViewName = "UInt32PropertyDefinitionView";
        public new const string ViewAliasName = "u32pd";

        public const int DEFAULTVALUE_FIELD_ID = 5;
        public const int MINVALUE_FIELD_ID = 6;
        public const int MAXVALUE_FIELD_ID = 7;

        public SimpleUInt32PropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public uint DefaultValue
        {
            get
            {
                return GetUInt32( DEFAULTVALUE_FIELD_ID );
            }
        }
        public uint MinValue
        {
            get
            {
                return GetUInt32( MINVALUE_FIELD_ID );
            }
        }
        public uint MaxValue
        {
            get
            {
                return GetUInt32( MAXVALUE_FIELD_ID );
            }
        }
    }

    public class SimpleUInt64PropertyDefinitionDataReader : SimplePropertyDefinitionDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  u64pd.[Id], \r\n" +
            "  u64pd.[EntityType], \r\n" +
            "  u64pd.[RowVersion], \r\n" +
            "  u64pd.[ElementType], \r\n" +
            "  u64pd.[Name], \r\n" +
            "  u64pd.[Description], \r\n" +
            "  u64pd.[DefaultValue], \r\n" +
            "  u64pd.[MinValue], \r\n" +
            "  u64pd.[MaxValue] \r\n" +
            "FROM [UInt64PropertyDefinitionView] u64pd \r\n";

        public new const string BaseViewName = "UInt64PropertyDefinitionView";
        public new const string ViewAliasName = "u64pd";

        public const int DEFAULTVALUE_FIELD_ID = 5;
        public const int MINVALUE_FIELD_ID = 6;
        public const int MAXVALUE_FIELD_ID = 7;

        public SimpleUInt64PropertyDefinitionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public long DefaultValue
        {
            get
            {
                return GetInt64( DEFAULTVALUE_FIELD_ID );
            }
        }
        public long MinValue
        {
            get
            {
                return GetInt64( MINVALUE_FIELD_ID );
            }
        }
        public long MaxValue
        {
            get
            {
                return GetInt64( MAXVALUE_FIELD_ID );
            }
        }
    }

    public class SimpleRadarAlarmStatusDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  ras.[Id], \r\n" +
            "  ras.[RowVersion], \r\n" +
            "  ras.[Radar], \r\n" +
            "  ras.[Timestamp], \r\n" +
            "  ras.[Type] \r\n" +
            "FROM [RadarAlarmStatusView] ras \r\n";

        public const string BaseViewName = "RadarAlarmStatusView";
        public const string ViewAliasName = "ras";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int RADAR_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int TYPE_FIELD_ID = 4;

        public SimpleRadarAlarmStatusDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Types.AlarmState Type
        {
            get
            {
                return GetEnum<Types.AlarmState>( TYPE_FIELD_ID );
            }
        }
    }

    public class SimpleRadarCommandDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  rc.[Id], \r\n" +
            "  rc.[EntityType], \r\n" +
            "  rc.[RowVersion], \r\n" +
            "  rc.[Radar], \r\n" +
            "  rc.[Timestamp], \r\n" +
            "  rc.[DeviceCommandSourceType], \r\n" +
            "  rc.[DeviceCommandSourceId], \r\n" +
            "  rc.[Reply] \r\n" +
            "FROM [RadarCommandView] rc \r\n";

        public const string BaseViewName = "RadarCommandView";
        public const string ViewAliasName = "rc";

        public const int ID_FIELD_ID = 0;
        public const int ENTITYTYPE_FIELD_ID = 1;
        public const int ROWVERSION_FIELD_ID = 2;
        public const int RADAR_FIELD_ID = 3;
        public const int TIMESTAMP_FIELD_ID = 4;
        public const int DEVICECOMMANDSOURCETYPE_FIELD_ID = 5;
        public const int DEVICECOMMANDSOURCEID_FIELD_ID = 6;
        public const int REPLY_FIELD_ID = 7;

        public SimpleRadarCommandDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public Types.Kind EntityType
        {
            get
            {
                return GetEnum<Types.Kind>( ENTITYTYPE_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Types.DeviceCommandSourceType DeviceCommandSourceType
        {
            get
            {
                return GetEnum<Types.DeviceCommandSourceType>( DEVICECOMMANDSOURCETYPE_FIELD_ID );
            }
        }
        public Guid DeviceCommandSourceId
        {
            get
            {
                return GetGuid( DEVICECOMMANDSOURCEID_FIELD_ID );
            }
        }
        public Guid Reply
        {
            get
            {
                return GetGuid( REPLY_FIELD_ID );
            }
        }
    }

    public class SimpleRadarCommandGetStatusDataReader : SimpleRadarCommandDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rcgs.[Id], \r\n" +
            "  rcgs.[EntityType], \r\n" +
            "  rcgs.[RowVersion], \r\n" +
            "  rcgs.[Radar], \r\n" +
            "  rcgs.[Timestamp], \r\n" +
            "  rcgs.[DeviceCommandSourceType], \r\n" +
            "  rcgs.[DeviceCommandSourceId], \r\n" +
            "  rcgs.[Reply] \r\n" +
            "FROM [RadarCommandGetStatusView] rcgs \r\n";

        public new const string BaseViewName = "RadarCommandGetStatusView";
        public new const string ViewAliasName = "rcgs";

        public SimpleRadarCommandGetStatusDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleRadarCommandReplyDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  rcr.[Id], \r\n" +
            "  rcr.[EntityType], \r\n" +
            "  rcr.[RowVersion], \r\n" +
            "  rcr.[Radar], \r\n" +
            "  rcr.[Timestamp], \r\n" +
            "  rcr.[Command], \r\n" +
            "  rcr.[Status], \r\n" +
            "  rcr.[Message] \r\n" +
            "FROM [RadarCommandReplyView] rcr \r\n";

        public const string BaseViewName = "RadarCommandReplyView";
        public const string ViewAliasName = "rcr";

        public const int ID_FIELD_ID = 0;
        public const int ENTITYTYPE_FIELD_ID = 1;
        public const int ROWVERSION_FIELD_ID = 2;
        public const int RADAR_FIELD_ID = 3;
        public const int TIMESTAMP_FIELD_ID = 4;
        public const int COMMAND_FIELD_ID = 5;
        public const int STATUS_FIELD_ID = 6;
        public const int MESSAGE_FIELD_ID = 7;

        public SimpleRadarCommandReplyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public Types.Kind EntityType
        {
            get
            {
                return GetEnum<Types.Kind>( ENTITYTYPE_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Guid Command
        {
            get
            {
                return GetGuid( COMMAND_FIELD_ID );
            }
        }
        public Types.DeviceCommandReplyStatus Status
        {
            get
            {
                return GetEnum<Types.DeviceCommandReplyStatus>( STATUS_FIELD_ID );
            }
        }
        public string Message
        {
            get
            {
                return GetString( MESSAGE_FIELD_ID );
            }
        }
    }

    public class SimpleRadarCommandReplyGetStatusDataReader : SimpleRadarCommandReplyDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rcrgs.[Id], \r\n" +
            "  rcrgs.[EntityType], \r\n" +
            "  rcrgs.[RowVersion], \r\n" +
            "  rcrgs.[Radar], \r\n" +
            "  rcrgs.[Timestamp], \r\n" +
            "  rcrgs.[Command], \r\n" +
            "  rcrgs.[Status], \r\n" +
            "  rcrgs.[Message], \r\n" +
            "  rcrgs.[AzimuthCount], \r\n" +
            "  rcrgs.[TriggerCount], \r\n" +
            "  rcrgs.[RotationCount], \r\n" +
            "  rcrgs.[Pulse], \r\n" +
            "  rcrgs.[Tx] \r\n" +
            "FROM [RadarCommandReplyGetStatusView] rcrgs \r\n";

        public new const string BaseViewName = "RadarCommandReplyGetStatusView";
        public new const string ViewAliasName = "rcrgs";

        public const int AZIMUTHCOUNT_FIELD_ID = 7;
        public const int TRIGGERCOUNT_FIELD_ID = 8;
        public const int ROTATIONCOUNT_FIELD_ID = 9;
        public const int PULSE_FIELD_ID = 10;
        public const int TX_FIELD_ID = 11;

        public SimpleRadarCommandReplyGetStatusDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public int AzimuthCount
        {
            get
            {
                return GetInt32( AZIMUTHCOUNT_FIELD_ID );
            }
        }
        public int TriggerCount
        {
            get
            {
                return GetInt32( TRIGGERCOUNT_FIELD_ID );
            }
        }
        public TimeSpan RotationCount
        {
            get
            {
                return new TimeSpan( GetInt64( ROTATIONCOUNT_FIELD_ID ) );
            }
        }
        public Types.RadarPulse Pulse
        {
            get
            {
                return GetEnum<Types.RadarPulse>( PULSE_FIELD_ID );
            }
        }
        public bool Tx
        {
            get
            {
                return GetBoolean( TX_FIELD_ID );
            }
        }
    }

    public class SimpleRadarConfigurationDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  rc.[Id], \r\n" +
            "  rc.[RowVersion], \r\n" +
            "  rc.[Radar], \r\n" +
            "  rc.[Timestamp], \r\n" +
            "  rc.[RadarProtocolVersion], \r\n" +
            "  rc.[RadarIPAddress], \r\n" +
            "  rc.[RadarPort], \r\n" +
            "  rc.[RadarConfigurationPort], \r\n" +
            "  rc.[SkipMagicTimeout], \r\n" +
            "  rc.[ReadTimeout], \r\n" +
            "  rc.[SynchronizationInterval], \r\n" +
            "  rc.[TargetsRefreshRate], \r\n" +
            "  rc.[Range], \r\n" +
            "  rc.[SectorCount], \r\n" +
            "  rc.[SectorOffset], \r\n" +
            "  rc.[ImageColor], \r\n" +
            "  rc.[ImageSubstitutionColor], \r\n" +
            "  rc.[TransparentColor], \r\n" +
            "  rc.[ImageScaleFactorX], \r\n" +
            "  rc.[ImageOffsetX], \r\n" +
            "  rc.[ImageScaleFactorY], \r\n" +
            "  rc.[ImageOffsetY], \r\n" +
            "  rc.[RadarImageType], \r\n" +
            "  rc.[TrackColor], \r\n" +
            "  rc.[VectorColor], \r\n" +
            "  rc.[EnableNmea], \r\n" +
            "  rc.[NmeaReceiverIPAddress], \r\n" +
            "  rc.[NmeaReceiverPort], \r\n" +
            "  rc.[NmeaReceiverSourceId] \r\n" +
            "FROM [RadarConfigurationView] rc \r\n";

        public const string BaseViewName = "RadarConfigurationView";
        public const string ViewAliasName = "rc";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int RADAR_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int RADARPROTOCOLVERSION_FIELD_ID = 4;
        public const int RADARIPADDRESS_FIELD_ID = 5;
        public const int RADARPORT_FIELD_ID = 6;
        public const int RADARCONFIGURATIONPORT_FIELD_ID = 7;
        public const int SKIPMAGICTIMEOUT_FIELD_ID = 8;
        public const int READTIMEOUT_FIELD_ID = 9;
        public const int SYNCHRONIZATIONINTERVAL_FIELD_ID = 10;
        public const int TARGETSREFRESHRATE_FIELD_ID = 11;
        public const int RANGE_FIELD_ID = 12;
        public const int SECTORCOUNT_FIELD_ID = 13;
        public const int SECTOROFFSET_FIELD_ID = 14;
        public const int IMAGECOLOR_FIELD_ID = 15;
        public const int IMAGESUBSTITUTIONCOLOR_FIELD_ID = 16;
        public const int TRANSPARENTCOLOR_FIELD_ID = 17;
        public const int IMAGESCALEFACTORX_FIELD_ID = 18;
        public const int IMAGEOFFSETX_FIELD_ID = 19;
        public const int IMAGESCALEFACTORY_FIELD_ID = 20;
        public const int IMAGEOFFSETY_FIELD_ID = 21;
        public const int RADARIMAGETYPE_FIELD_ID = 22;
        public const int TRACKCOLOR_FIELD_ID = 23;
        public const int VECTORCOLOR_FIELD_ID = 24;
        public const int ENABLENMEA_FIELD_ID = 25;
        public const int NMEARECEIVERIPADDRESS_FIELD_ID = 26;
        public const int NMEARECEIVERPORT_FIELD_ID = 27;
        public const int NMEARECEIVERSOURCEID_FIELD_ID = 28;

        public SimpleRadarConfigurationDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public int RadarProtocolVersion
        {
            get
            {
                return GetInt32( RADARPROTOCOLVERSION_FIELD_ID );
            }
        }
        public string RadarIPAddress
        {
            get
            {
                return GetString( RADARIPADDRESS_FIELD_ID );
            }
        }
        public int RadarPort
        {
            get
            {
                return GetInt32( RADARPORT_FIELD_ID );
            }
        }
        public int RadarConfigurationPort
        {
            get
            {
                return GetInt32( RADARCONFIGURATIONPORT_FIELD_ID );
            }
        }
        public TimeSpan SkipMagicTimeout
        {
            get
            {
                return new TimeSpan( GetInt64( SKIPMAGICTIMEOUT_FIELD_ID ) );
            }
        }
        public TimeSpan ReadTimeout
        {
            get
            {
                return new TimeSpan( GetInt64( READTIMEOUT_FIELD_ID ) );
            }
        }
        public TimeSpan SynchronizationInterval
        {
            get
            {
                return new TimeSpan( GetInt64( SYNCHRONIZATIONINTERVAL_FIELD_ID ) );
            }
        }
        public int TargetsRefreshRate
        {
            get
            {
                return GetInt32( TARGETSREFRESHRATE_FIELD_ID );
            }
        }
        public int Range
        {
            get
            {
                return GetInt32( RANGE_FIELD_ID );
            }
        }
        public int SectorCount
        {
            get
            {
                return GetInt32( SECTORCOUNT_FIELD_ID );
            }
        }
        public int SectorOffset
        {
            get
            {
                return GetInt32( SECTOROFFSET_FIELD_ID );
            }
        }
        public uint ImageColor
        {
            get
            {
                return GetUInt32( IMAGECOLOR_FIELD_ID );
            }
        }
        public uint? ImageSubstitutionColor
        {
            get
            {
                return GetNullableUInt32( IMAGESUBSTITUTIONCOLOR_FIELD_ID );
            }
        }
        public uint TransparentColor
        {
            get
            {
                return GetUInt32( TRANSPARENTCOLOR_FIELD_ID );
            }
        }
        public double ImageScaleFactorX
        {
            get
            {
                return GetDouble( IMAGESCALEFACTORX_FIELD_ID );
            }
        }
        public double ImageOffsetX
        {
            get
            {
                return GetDouble( IMAGEOFFSETX_FIELD_ID );
            }
        }
        public double ImageScaleFactorY
        {
            get
            {
                return GetDouble( IMAGESCALEFACTORY_FIELD_ID );
            }
        }
        public double ImageOffsetY
        {
            get
            {
                return GetDouble( IMAGEOFFSETY_FIELD_ID );
            }
        }
        public Types.RadarImageType RadarImageType
        {
            get
            {
                return GetEnum<Types.RadarImageType>( RADARIMAGETYPE_FIELD_ID );
            }
        }
        public uint TrackColor
        {
            get
            {
                return GetUInt32( TRACKCOLOR_FIELD_ID );
            }
        }
        public uint VectorColor
        {
            get
            {
                return GetUInt32( VECTORCOLOR_FIELD_ID );
            }
        }
        public bool EnableNmea
        {
            get
            {
                return GetBoolean( ENABLENMEA_FIELD_ID );
            }
        }
        public string NmeaReceiverIPAddress
        {
            get
            {
                return GetString( NMEARECEIVERIPADDRESS_FIELD_ID );
            }
        }
        public int NmeaReceiverPort
        {
            get
            {
                return GetInt32( NMEARECEIVERPORT_FIELD_ID );
            }
        }
        public string NmeaReceiverSourceId
        {
            get
            {
                return GetString( NMEARECEIVERSOURCEID_FIELD_ID );
            }
        }
    }

    public class SimpleRadarImageDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  ri.[Id], \r\n" +
            "  ri.[RowVersion], \r\n" +
            "  ri.[Radar], \r\n" +
            "  ri.[Timestamp], \r\n" +
            "  ri.[Depth], \r\n" +
            "  ri.[Resolution], \r\n" +
            "  ri.[Range], \r\n" +
            "  ri.[Image] \r\n" +
            "FROM [RadarImageView] ri \r\n";

        public const string BaseViewName = "RadarImageView";
        public const string ViewAliasName = "ri";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int RADAR_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int DEPTH_FIELD_ID = 4;
        public const int RESOLUTION_FIELD_ID = 5;
        public const int RANGE_FIELD_ID = 6;
        public const int IMAGE_FIELD_ID = 7;

        public SimpleRadarImageDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public uint Depth
        {
            get
            {
                return GetUInt32( DEPTH_FIELD_ID );
            }
        }
        public int Resolution
        {
            get
            {
                return GetInt32( RESOLUTION_FIELD_ID );
            }
        }
        public int Range
        {
            get
            {
                return GetInt32( RANGE_FIELD_ID );
            }
        }
        public byte[] Image
        {
            get
            {
                return GetBytes( IMAGE_FIELD_ID );
            }
        }
    }

    public class SimpleRadarRawTrackTableDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  rrtt.[Id], \r\n" +
            "  rrtt.[RowVersion], \r\n" +
            "  rrtt.[Radar], \r\n" +
            "  rrtt.[Timestamp], \r\n" +
            "  rrtt.[Count], \r\n" +
            "  rrtt.[Table] \r\n" +
            "FROM [RadarRawTrackTableView] rrtt \r\n";

        public const string BaseViewName = "RadarRawTrackTableView";
        public const string ViewAliasName = "rrtt";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int RADAR_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int COUNT_FIELD_ID = 4;
        public const int TABLE_FIELD_ID = 5;

        public SimpleRadarRawTrackTableDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public int Count
        {
            get
            {
                return GetInt32( COUNT_FIELD_ID );
            }
        }
        public byte[] Table
        {
            get
            {
                return GetBytes( TABLE_FIELD_ID );
            }
        }
    }

    public class SimpleRadarStatusDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  rs.[Id], \r\n" +
            "  rs.[RowVersion], \r\n" +
            "  rs.[Radar], \r\n" +
            "  rs.[Timestamp], \r\n" +
            "  rs.[AzimuthCount], \r\n" +
            "  rs.[TriggerCount], \r\n" +
            "  rs.[RotationTime], \r\n" +
            "  rs.[Pulse], \r\n" +
            "  rs.[Tx], \r\n" +
            "  rs.[Tracking] \r\n" +
            "FROM [RadarStatusView] rs \r\n";

        public const string BaseViewName = "RadarStatusView";
        public const string ViewAliasName = "rs";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int RADAR_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int AZIMUTHCOUNT_FIELD_ID = 4;
        public const int TRIGGERCOUNT_FIELD_ID = 5;
        public const int ROTATIONTIME_FIELD_ID = 6;
        public const int PULSE_FIELD_ID = 7;
        public const int TX_FIELD_ID = 8;
        public const int TRACKING_FIELD_ID = 9;

        public SimpleRadarStatusDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public int AzimuthCount
        {
            get
            {
                return GetInt32( AZIMUTHCOUNT_FIELD_ID );
            }
        }
        public int TriggerCount
        {
            get
            {
                return GetInt32( TRIGGERCOUNT_FIELD_ID );
            }
        }
        public TimeSpan RotationTime
        {
            get
            {
                return new TimeSpan( GetInt64( ROTATIONTIME_FIELD_ID ) );
            }
        }
        public Types.RadarPulse Pulse
        {
            get
            {
                return GetEnum<Types.RadarPulse>( PULSE_FIELD_ID );
            }
        }
        public bool Tx
        {
            get
            {
                return GetBoolean( TX_FIELD_ID );
            }
        }
        public bool Tracking
        {
            get
            {
                return GetBoolean( TRACKING_FIELD_ID );
            }
        }
    }

    public class SimpleRadioCommandDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  rc.[Id], \r\n" +
            "  rc.[RowVersion], \r\n" +
            "  rc.[Radio], \r\n" +
            "  rc.[Timestamp], \r\n" +
            "  rc.[DeviceCommandSourceType], \r\n" +
            "  rc.[DeviceCommandSourceId], \r\n" +
            "  rc.[Reply] \r\n" +
            "FROM [RadioCommandView] rc \r\n";

        public const string BaseViewName = "RadioCommandView";
        public const string ViewAliasName = "rc";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int RADIO_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int DEVICECOMMANDSOURCETYPE_FIELD_ID = 4;
        public const int DEVICECOMMANDSOURCEID_FIELD_ID = 5;
        public const int REPLY_FIELD_ID = 6;

        public SimpleRadioCommandDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Radio
        {
            get
            {
                return GetGuid( RADIO_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Types.DeviceCommandSourceType DeviceCommandSourceType
        {
            get
            {
                return GetEnum<Types.DeviceCommandSourceType>( DEVICECOMMANDSOURCETYPE_FIELD_ID );
            }
        }
        public Guid DeviceCommandSourceId
        {
            get
            {
                return GetGuid( DEVICECOMMANDSOURCEID_FIELD_ID );
            }
        }
        public Guid Reply
        {
            get
            {
                return GetGuid( REPLY_FIELD_ID );
            }
        }
    }

    public class SimpleRadioCommandReplyDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  rcr.[Id], \r\n" +
            "  rcr.[RowVersion], \r\n" +
            "  rcr.[Radio], \r\n" +
            "  rcr.[Timestamp], \r\n" +
            "  rcr.[Command], \r\n" +
            "  rcr.[Status], \r\n" +
            "  rcr.[Message] \r\n" +
            "FROM [RadioCommandReplyView] rcr \r\n";

        public const string BaseViewName = "RadioCommandReplyView";
        public const string ViewAliasName = "rcr";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int RADIO_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int COMMAND_FIELD_ID = 4;
        public const int STATUS_FIELD_ID = 5;
        public const int MESSAGE_FIELD_ID = 6;

        public SimpleRadioCommandReplyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Radio
        {
            get
            {
                return GetGuid( RADIO_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Guid Command
        {
            get
            {
                return GetGuid( COMMAND_FIELD_ID );
            }
        }
        public Types.DeviceCommandReplyStatus Status
        {
            get
            {
                return GetEnum<Types.DeviceCommandReplyStatus>( STATUS_FIELD_ID );
            }
        }
        public string Message
        {
            get
            {
                return GetString( MESSAGE_FIELD_ID );
            }
        }
    }

    public class SimpleRadioConfigurationDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  rc.[Id], \r\n" +
            "  rc.[RowVersion], \r\n" +
            "  rc.[Radio], \r\n" +
            "  rc.[Timestamp], \r\n" +
            "  rc.[Longitude], \r\n" +
            "  rc.[Latitude], \r\n" +
            "  rc.[PlaybackUrl], \r\n" +
            "  rc.[RadioIPAddress], \r\n" +
            "  rc.[RadioPort], \r\n" +
            "  rc.[Ed137IPAddress], \r\n" +
            "  rc.[Ed137Port] \r\n" +
            "FROM [RadioConfigurationView] rc \r\n";

        public const string BaseViewName = "RadioConfigurationView";
        public const string ViewAliasName = "rc";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int RADIO_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int LONGITUDE_FIELD_ID = 4;
        public const int LATITUDE_FIELD_ID = 5;
        public const int PLAYBACKURL_FIELD_ID = 6;
        public const int RADIOIPADDRESS_FIELD_ID = 7;
        public const int RADIOPORT_FIELD_ID = 8;
        public const int ED137IPADDRESS_FIELD_ID = 9;
        public const int ED137PORT_FIELD_ID = 10;

        public SimpleRadioConfigurationDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Radio
        {
            get
            {
                return GetGuid( RADIO_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public double Longitude
        {
            get
            {
                return GetDouble( LONGITUDE_FIELD_ID );
            }
        }
        public double Latitude
        {
            get
            {
                return GetDouble( LATITUDE_FIELD_ID );
            }
        }
        public string PlaybackUrl
        {
            get
            {
                return GetString( PLAYBACKURL_FIELD_ID );
            }
        }
        public string RadioIPAddress
        {
            get
            {
                return GetString( RADIOIPADDRESS_FIELD_ID );
            }
        }
        public int RadioPort
        {
            get
            {
                return GetInt32( RADIOPORT_FIELD_ID );
            }
        }
        public string Ed137IPAddress
        {
            get
            {
                return GetString( ED137IPADDRESS_FIELD_ID );
            }
        }
        public int Ed137Port
        {
            get
            {
                return GetInt32( ED137PORT_FIELD_ID );
            }
        }
    }

    public class SimpleRadomeCommandDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  rc.[Id], \r\n" +
            "  rc.[RowVersion], \r\n" +
            "  rc.[Radome], \r\n" +
            "  rc.[Timestamp], \r\n" +
            "  rc.[DeviceCommandSourceType], \r\n" +
            "  rc.[DeviceCommandSourceId], \r\n" +
            "  rc.[Reply] \r\n" +
            "FROM [RadomeCommandView] rc \r\n";

        public const string BaseViewName = "RadomeCommandView";
        public const string ViewAliasName = "rc";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int RADOME_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int DEVICECOMMANDSOURCETYPE_FIELD_ID = 4;
        public const int DEVICECOMMANDSOURCEID_FIELD_ID = 5;
        public const int REPLY_FIELD_ID = 6;

        public SimpleRadomeCommandDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Radome
        {
            get
            {
                return GetGuid( RADOME_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Types.DeviceCommandSourceType DeviceCommandSourceType
        {
            get
            {
                return GetEnum<Types.DeviceCommandSourceType>( DEVICECOMMANDSOURCETYPE_FIELD_ID );
            }
        }
        public Guid DeviceCommandSourceId
        {
            get
            {
                return GetGuid( DEVICECOMMANDSOURCEID_FIELD_ID );
            }
        }
        public Guid Reply
        {
            get
            {
                return GetGuid( REPLY_FIELD_ID );
            }
        }
    }

    public class SimpleRadomeCommandReplyDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  rcr.[Id], \r\n" +
            "  rcr.[RowVersion], \r\n" +
            "  rcr.[Radome], \r\n" +
            "  rcr.[Timestamp], \r\n" +
            "  rcr.[Command], \r\n" +
            "  rcr.[Status], \r\n" +
            "  rcr.[Message] \r\n" +
            "FROM [RadomeCommandReplyView] rcr \r\n";

        public const string BaseViewName = "RadomeCommandReplyView";
        public const string ViewAliasName = "rcr";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int RADOME_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int COMMAND_FIELD_ID = 4;
        public const int STATUS_FIELD_ID = 5;
        public const int MESSAGE_FIELD_ID = 6;

        public SimpleRadomeCommandReplyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Radome
        {
            get
            {
                return GetGuid( RADOME_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Guid Command
        {
            get
            {
                return GetGuid( COMMAND_FIELD_ID );
            }
        }
        public Types.DeviceCommandReplyStatus Status
        {
            get
            {
                return GetEnum<Types.DeviceCommandReplyStatus>( STATUS_FIELD_ID );
            }
        }
        public string Message
        {
            get
            {
                return GetString( MESSAGE_FIELD_ID );
            }
        }
    }

    public class SimpleRadomeConfigurationDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  rc.[Id], \r\n" +
            "  rc.[RowVersion], \r\n" +
            "  rc.[Radome], \r\n" +
            "  rc.[Timestamp], \r\n" +
            "  rc.[Interval], \r\n" +
            "  rc.[LowPressureLimit], \r\n" +
            "  rc.[HighPressureLimit], \r\n" +
            "  rc.[LowTemperatureLimit], \r\n" +
            "  rc.[HighTemperatureLimit] \r\n" +
            "FROM [RadomeConfigurationView] rc \r\n";

        public const string BaseViewName = "RadomeConfigurationView";
        public const string ViewAliasName = "rc";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int RADOME_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int INTERVAL_FIELD_ID = 4;
        public const int LOWPRESSURELIMIT_FIELD_ID = 5;
        public const int HIGHPRESSURELIMIT_FIELD_ID = 6;
        public const int LOWTEMPERATURELIMIT_FIELD_ID = 7;
        public const int HIGHTEMPERATURELIMIT_FIELD_ID = 8;

        public SimpleRadomeConfigurationDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Radome
        {
            get
            {
                return GetGuid( RADOME_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public TimeSpan Interval
        {
            get
            {
                return new TimeSpan( GetInt64( INTERVAL_FIELD_ID ) );
            }
        }
        public double LowPressureLimit
        {
            get
            {
                return GetDouble( LOWPRESSURELIMIT_FIELD_ID );
            }
        }
        public double HighPressureLimit
        {
            get
            {
                return GetDouble( HIGHPRESSURELIMIT_FIELD_ID );
            }
        }
        public double LowTemperatureLimit
        {
            get
            {
                return GetDouble( LOWTEMPERATURELIMIT_FIELD_ID );
            }
        }
        public double HighTemperatureLimit
        {
            get
            {
                return GetDouble( HIGHTEMPERATURELIMIT_FIELD_ID );
            }
        }
    }

    public class SimpleReferenceTimeseriesValueDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  rtv.[Id], \r\n" +
            "  rtv.[RowVersion], \r\n" +
            "  rtv.[Timeseries], \r\n" +
            "  rtv.[Timestamp], \r\n" +
            "  rtv.[Value] \r\n" +
            "FROM [ReferenceTimeseriesValueView] rtv \r\n";

        public const string BaseViewName = "ReferenceTimeseriesValueView";
        public const string ViewAliasName = "rtv";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TIMESERIES_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int VALUE_FIELD_ID = 4;

        public SimpleReferenceTimeseriesValueDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Guid Value
        {
            get
            {
                return GetGuid( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleSByteTimeseriesValueDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  stv.[Id], \r\n" +
            "  stv.[RowVersion], \r\n" +
            "  stv.[Timeseries], \r\n" +
            "  stv.[Timestamp], \r\n" +
            "  stv.[Value] \r\n" +
            "FROM [SByteTimeseriesValueView] stv \r\n";

        public const string BaseViewName = "SByteTimeseriesValueView";
        public const string ViewAliasName = "stv";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TIMESERIES_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int VALUE_FIELD_ID = 4;

        public SimpleSByteTimeseriesValueDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public sbyte? Value
        {
            get
            {
                return GetNullableSByte( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleSecurityDomainDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  sd.[Id], \r\n" +
            "  sd.[RowVersion], \r\n" +
            "  sd.[Name], \r\n" +
            "  sd.[Description] \r\n" +
            "FROM [SecurityDomainView] sd \r\n";

        public const string BaseViewName = "SecurityDomainView";
        public const string ViewAliasName = "sd";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int NAME_FIELD_ID = 2;
        public const int DESCRIPTION_FIELD_ID = 3;

        public SimpleSecurityDomainDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
        public string Description
        {
            get
            {
                return GetString( DESCRIPTION_FIELD_ID );
            }
        }
    }

    public class SimpleSecurityIdentifierDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  si.[Id], \r\n" +
            "  si.[EntityType], \r\n" +
            "  si.[RowVersion], \r\n" +
            "  si.[Domain], \r\n" +
            "  si.[Identity], \r\n" +
            "  si.[Description] \r\n" +
            "FROM [SecurityIdentifierView] si \r\n";

        public const string BaseViewName = "SecurityIdentifierView";
        public const string ViewAliasName = "si";

        public const int ID_FIELD_ID = 0;
        public const int ENTITYTYPE_FIELD_ID = 1;
        public const int ROWVERSION_FIELD_ID = 2;
        public const int DOMAIN_FIELD_ID = 3;
        public const int IDENTITY_FIELD_ID = 4;
        public const int DESCRIPTION_FIELD_ID = 5;

        public SimpleSecurityIdentifierDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public Types.Kind EntityType
        {
            get
            {
                return GetEnum<Types.Kind>( ENTITYTYPE_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Domain
        {
            get
            {
                return GetGuid( DOMAIN_FIELD_ID );
            }
        }
        public string Identity
        {
            get
            {
                return GetString( IDENTITY_FIELD_ID );
            }
        }
        public string Description
        {
            get
            {
                return GetString( DESCRIPTION_FIELD_ID );
            }
        }
    }

    public class SimpleSecurityLoginDataReader : SimpleSecurityIdentifierDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  sl.[Id], \r\n" +
            "  sl.[EntityType], \r\n" +
            "  sl.[RowVersion], \r\n" +
            "  sl.[Domain], \r\n" +
            "  sl.[Identity], \r\n" +
            "  sl.[Description] \r\n" +
            "FROM [SecurityLoginView] sl \r\n";

        public new const string BaseViewName = "SecurityLoginView";
        public new const string ViewAliasName = "sl";

        public SimpleSecurityLoginDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleSecurityRoleDataReader : SimpleSecurityIdentifierDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  sr.[Id], \r\n" +
            "  sr.[EntityType], \r\n" +
            "  sr.[RowVersion], \r\n" +
            "  sr.[Domain], \r\n" +
            "  sr.[Identity], \r\n" +
            "  sr.[Description], \r\n" +
            "  sr.[Name] \r\n" +
            "FROM [SecurityRoleView] sr \r\n";

        public new const string BaseViewName = "SecurityRoleView";
        public new const string ViewAliasName = "sr";

        public const int NAME_FIELD_ID = 5;

        public SimpleSecurityRoleDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
    }

    public class SimpleSecurityIdentifierRoleLinkDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  sirl.[Id], \r\n" +
            "  sirl.[RowVersion], \r\n" +
            "  sirl.[Member], \r\n" +
            "  sirl.[Role], \r\n" +
            "  sirl.[Start], \r\n" +
            "  sirl.[End] \r\n" +
            "FROM [SecurityIdentifierRoleLinkView] sirl \r\n";

        public const string BaseViewName = "SecurityIdentifierRoleLinkView";
        public const string ViewAliasName = "sirl";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int MEMBER_FIELD_ID = 2;
        public const int ROLE_FIELD_ID = 3;
        public const int START_FIELD_ID = 4;
        public const int END_FIELD_ID = 5;

        public SimpleSecurityIdentifierRoleLinkDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Member
        {
            get
            {
                return GetGuid( MEMBER_FIELD_ID );
            }
        }
        public Guid Role
        {
            get
            {
                return GetGuid( ROLE_FIELD_ID );
            }
        }
        public DateTime Start
        {
            get
            {
                return new DateTime( GetInt64( START_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public DateTime? End
        {
            get
            {
                var v = GetNullableInt64( END_FIELD_ID );
                if( v is long value )
                {
                    return new DateTime( value , DateTimeKind.Utc );
                }
                return null;
            }
        }
    }

    public class SimpleSecurityLoginSessionDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  sls.[Id], \r\n" +
            "  sls.[RowVersion], \r\n" +
            "  sls.[Login], \r\n" +
            "  sls.[FromTime], \r\n" +
            "  sls.[ThroughTime], \r\n" +
            "  sls.[ClientSession], \r\n" +
            "  sls.[NotificationQueueName], \r\n" +
            "  sls.[MessageQueueName] \r\n" +
            "FROM [SecurityLoginSessionView] sls \r\n";

        public const string BaseViewName = "SecurityLoginSessionView";
        public const string ViewAliasName = "sls";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int LOGIN_FIELD_ID = 2;
        public const int FROMTIME_FIELD_ID = 3;
        public const int THROUGHTIME_FIELD_ID = 4;
        public const int CLIENTSESSION_FIELD_ID = 5;
        public const int NOTIFICATIONQUEUENAME_FIELD_ID = 6;
        public const int MESSAGEQUEUENAME_FIELD_ID = 7;

        public SimpleSecurityLoginSessionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Login
        {
            get
            {
                return GetGuid( LOGIN_FIELD_ID );
            }
        }
        public DateTime FromTime
        {
            get
            {
                return new DateTime( GetInt64( FROMTIME_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public DateTime? ThroughTime
        {
            get
            {
                var v = GetNullableInt64( THROUGHTIME_FIELD_ID );
                if( v is long value )
                {
                    return new DateTime( value , DateTimeKind.Utc );
                }
                return null;
            }
        }
        public Guid ClientSession
        {
            get
            {
                return GetGuid( CLIENTSESSION_FIELD_ID );
            }
        }
        public string NotificationQueueName
        {
            get
            {
                return GetString( NOTIFICATIONQUEUENAME_FIELD_ID );
            }
        }
        public string MessageQueueName
        {
            get
            {
                return GetString( MESSAGEQUEUENAME_FIELD_ID );
            }
        }
    }

    public class SimpleSecurityPermissionDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  sp.[Id], \r\n" +
            "  sp.[RowVersion], \r\n" +
            "  sp.[Identifier], \r\n" +
            "  sp.[Timestamp], \r\n" +
            "  sp.[TypeCode], \r\n" +
            "  sp.[CanCreate], \r\n" +
            "  sp.[CanRead], \r\n" +
            "  sp.[CanUpdate], \r\n" +
            "  sp.[CanDelete] \r\n" +
            "FROM [SecurityPermissionView] sp \r\n";

        public const string BaseViewName = "SecurityPermissionView";
        public const string ViewAliasName = "sp";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int IDENTIFIER_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int TYPECODE_FIELD_ID = 4;
        public const int CANCREATE_FIELD_ID = 5;
        public const int CANREAD_FIELD_ID = 6;
        public const int CANUPDATE_FIELD_ID = 7;
        public const int CANDELETE_FIELD_ID = 8;

        public SimpleSecurityPermissionDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Identifier
        {
            get
            {
                return GetGuid( IDENTIFIER_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public int TypeCode
        {
            get
            {
                return GetInt32( TYPECODE_FIELD_ID );
            }
        }
        public bool CanCreate
        {
            get
            {
                return GetBoolean( CANCREATE_FIELD_ID );
            }
        }
        public bool CanRead
        {
            get
            {
                return GetBoolean( CANREAD_FIELD_ID );
            }
        }
        public bool CanUpdate
        {
            get
            {
                return GetBoolean( CANUPDATE_FIELD_ID );
            }
        }
        public bool CanDelete
        {
            get
            {
                return GetBoolean( CANDELETE_FIELD_ID );
            }
        }
    }

    public class SimpleSingleTimeseriesValueDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  stv.[Id], \r\n" +
            "  stv.[RowVersion], \r\n" +
            "  stv.[Timeseries], \r\n" +
            "  stv.[Timestamp], \r\n" +
            "  stv.[Value] \r\n" +
            "FROM [SingleTimeseriesValueView] stv \r\n";

        public const string BaseViewName = "SingleTimeseriesValueView";
        public const string ViewAliasName = "stv";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TIMESERIES_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int VALUE_FIELD_ID = 4;

        public SimpleSingleTimeseriesValueDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public float? Value
        {
            get
            {
                return GetNullableFloat( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleStringTimeseriesValueDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  stv.[Id], \r\n" +
            "  stv.[RowVersion], \r\n" +
            "  stv.[Timeseries], \r\n" +
            "  stv.[Timestamp], \r\n" +
            "  stv.[Value] \r\n" +
            "FROM [StringTimeseriesValueView] stv \r\n";

        public const string BaseViewName = "StringTimeseriesValueView";
        public const string ViewAliasName = "stv";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TIMESERIES_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int VALUE_FIELD_ID = 4;

        public SimpleStringTimeseriesValueDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public string Value
        {
            get
            {
                return GetString( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleTimeseriesCatalogElementDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  tce.[Id], \r\n" +
            "  tce.[EntityType], \r\n" +
            "  tce.[RowVersion], \r\n" +
            "  tce.[Catalog], \r\n" +
            "  tce.[Name] \r\n" +
            "FROM [TimeseriesCatalogElementView] tce \r\n";

        public const string BaseViewName = "TimeseriesCatalogElementView";
        public const string ViewAliasName = "tce";

        public const int ID_FIELD_ID = 0;
        public const int ENTITYTYPE_FIELD_ID = 1;
        public const int ROWVERSION_FIELD_ID = 2;
        public const int CATALOG_FIELD_ID = 3;
        public const int NAME_FIELD_ID = 4;

        public SimpleTimeseriesCatalogElementDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public Types.Kind EntityType
        {
            get
            {
                return GetEnum<Types.Kind>( ENTITYTYPE_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid? Catalog
        {
            get
            {
                return GetNullableGuid( CATALOG_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
    }

    public class SimpleTimeseriesDataReader : SimpleTimeseriesCatalogElementDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  t.[Id], \r\n" +
            "  t.[EntityType], \r\n" +
            "  t.[RowVersion], \r\n" +
            "  t.[Catalog], \r\n" +
            "  t.[Name], \r\n" +
            "  t.[MaxRetention] \r\n" +
            "FROM [TimeseriesView] t \r\n";

        public new const string BaseViewName = "TimeseriesView";
        public new const string ViewAliasName = "t";

        public const int MAXRETENTION_FIELD_ID = 4;

        public SimpleTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public TimeSpan MaxRetention
        {
            get
            {
                return new TimeSpan( GetInt64( MAXRETENTION_FIELD_ID ) );
            }
        }
    }

    public class SimpleBinaryTimeseriesDataReader : SimpleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  bt.[Id], \r\n" +
            "  bt.[EntityType], \r\n" +
            "  bt.[RowVersion], \r\n" +
            "  bt.[Catalog], \r\n" +
            "  bt.[Name], \r\n" +
            "  bt.[MaxRetention] \r\n" +
            "FROM [BinaryTimeseriesView] bt \r\n";

        public new const string BaseViewName = "BinaryTimeseriesView";
        public new const string ViewAliasName = "bt";

        public SimpleBinaryTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleBooleanTimeseriesDataReader : SimpleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  bots.[Id], \r\n" +
            "  bots.[EntityType], \r\n" +
            "  bots.[RowVersion], \r\n" +
            "  bots.[Catalog], \r\n" +
            "  bots.[Name], \r\n" +
            "  bots.[MaxRetention] \r\n" +
            "FROM [BooleanTimeseriesView] bots \r\n";

        public new const string BaseViewName = "BooleanTimeseriesView";
        public new const string ViewAliasName = "bots";

        public SimpleBooleanTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleAisAidToNavigationOffPositionTimeseriesDataReader : SimpleBooleanTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  aatnopt.[Id], \r\n" +
            "  aatnopt.[EntityType], \r\n" +
            "  aatnopt.[RowVersion], \r\n" +
            "  aatnopt.[Catalog], \r\n" +
            "  aatnopt.[Name], \r\n" +
            "  aatnopt.[MaxRetention], \r\n" +
            "  aatnopt.[AidToNavigation] \r\n" +
            "FROM [AisAidToNavigationOffPositionTimeseriesView] aatnopt \r\n";

        public new const string BaseViewName = "AisAidToNavigationOffPositionTimeseriesView";
        public new const string ViewAliasName = "aatnopt";

        public const int AIDTONAVIGATION_FIELD_ID = 5;

        public SimpleAisAidToNavigationOffPositionTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid AidToNavigation
        {
            get
            {
                return GetGuid( AIDTONAVIGATION_FIELD_ID );
            }
        }
    }

    public class SimpleDeviceEnabledTimeseriesDataReader : SimpleBooleanTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  det.[Id], \r\n" +
            "  det.[EntityType], \r\n" +
            "  det.[RowVersion], \r\n" +
            "  det.[Catalog], \r\n" +
            "  det.[Name], \r\n" +
            "  det.[MaxRetention], \r\n" +
            "  det.[Device] \r\n" +
            "FROM [DeviceEnabledTimeseriesView] det \r\n";

        public new const string BaseViewName = "DeviceEnabledTimeseriesView";
        public new const string ViewAliasName = "det";

        public const int DEVICE_FIELD_ID = 5;

        public SimpleDeviceEnabledTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid? Device
        {
            get
            {
                return GetNullableGuid( DEVICE_FIELD_ID );
            }
        }
    }

    public class SimpleRadarAutomaticSensitivityTimeControlTimeseriesDataReader : SimpleBooleanTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rastct.[Id], \r\n" +
            "  rastct.[EntityType], \r\n" +
            "  rastct.[RowVersion], \r\n" +
            "  rastct.[Catalog], \r\n" +
            "  rastct.[Name], \r\n" +
            "  rastct.[MaxRetention], \r\n" +
            "  rastct.[Radar] \r\n" +
            "FROM [RadarAutomaticSensitivityTimeControlTimeseriesView] rastct \r\n";

        public new const string BaseViewName = "RadarAutomaticSensitivityTimeControlTimeseriesView";
        public new const string ViewAliasName = "rastct";

        public const int RADAR_FIELD_ID = 5;

        public SimpleRadarAutomaticSensitivityTimeControlTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
    }

    public class SimpleRadarBlankSector1TimeseriesDataReader : SimpleBooleanTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rbs1t.[Id], \r\n" +
            "  rbs1t.[EntityType], \r\n" +
            "  rbs1t.[RowVersion], \r\n" +
            "  rbs1t.[Catalog], \r\n" +
            "  rbs1t.[Name], \r\n" +
            "  rbs1t.[MaxRetention], \r\n" +
            "  rbs1t.[Radar] \r\n" +
            "FROM [RadarBlankSector1TimeseriesView] rbs1t \r\n";

        public new const string BaseViewName = "RadarBlankSector1TimeseriesView";
        public new const string ViewAliasName = "rbs1t";

        public const int RADAR_FIELD_ID = 5;

        public SimpleRadarBlankSector1TimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
    }

    public class SimpleRadarBlankSector2TimeseriesDataReader : SimpleBooleanTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rbs2t.[Id], \r\n" +
            "  rbs2t.[EntityType], \r\n" +
            "  rbs2t.[RowVersion], \r\n" +
            "  rbs2t.[Catalog], \r\n" +
            "  rbs2t.[Name], \r\n" +
            "  rbs2t.[MaxRetention], \r\n" +
            "  rbs2t.[Radar] \r\n" +
            "FROM [RadarBlankSector2TimeseriesView] rbs2t \r\n";

        public new const string BaseViewName = "RadarBlankSector2TimeseriesView";
        public new const string ViewAliasName = "rbs2t";

        public const int RADAR_FIELD_ID = 5;

        public SimpleRadarBlankSector2TimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
    }

    public class SimpleRadarEnableAutomaticFrequencyControlTimeseriesDataReader : SimpleBooleanTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  reafct.[Id], \r\n" +
            "  reafct.[EntityType], \r\n" +
            "  reafct.[RowVersion], \r\n" +
            "  reafct.[Catalog], \r\n" +
            "  reafct.[Name], \r\n" +
            "  reafct.[MaxRetention], \r\n" +
            "  reafct.[Radar] \r\n" +
            "FROM [RadarEnableAutomaticFrequencyControlTimeseriesView] reafct \r\n";

        public new const string BaseViewName = "RadarEnableAutomaticFrequencyControlTimeseriesView";
        public new const string ViewAliasName = "reafct";

        public const int RADAR_FIELD_ID = 5;

        public SimpleRadarEnableAutomaticFrequencyControlTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
    }

    public class SimpleRadarEnableFastTimeConstantTimeseriesDataReader : SimpleBooleanTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  reftct.[Id], \r\n" +
            "  reftct.[EntityType], \r\n" +
            "  reftct.[RowVersion], \r\n" +
            "  reftct.[Catalog], \r\n" +
            "  reftct.[Name], \r\n" +
            "  reftct.[MaxRetention], \r\n" +
            "  reftct.[Radar] \r\n" +
            "FROM [RadarEnableFastTimeConstantTimeseriesView] reftct \r\n";

        public new const string BaseViewName = "RadarEnableFastTimeConstantTimeseriesView";
        public new const string ViewAliasName = "reftct";

        public const int RADAR_FIELD_ID = 5;

        public SimpleRadarEnableFastTimeConstantTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
    }

    public class SimpleRadarEnableSensitivityTimeControlTimeseriesDataReader : SimpleBooleanTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  restct.[Id], \r\n" +
            "  restct.[EntityType], \r\n" +
            "  restct.[RowVersion], \r\n" +
            "  restct.[Catalog], \r\n" +
            "  restct.[Name], \r\n" +
            "  restct.[MaxRetention], \r\n" +
            "  restct.[Radar] \r\n" +
            "FROM [RadarEnableSensitivityTimeControlTimeseriesView] restct \r\n";

        public new const string BaseViewName = "RadarEnableSensitivityTimeControlTimeseriesView";
        public new const string ViewAliasName = "restct";

        public const int RADAR_FIELD_ID = 5;

        public SimpleRadarEnableSensitivityTimeControlTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
    }

    public class SimpleRadarPowerOnTimeseriesDataReader : SimpleBooleanTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rpot.[Id], \r\n" +
            "  rpot.[EntityType], \r\n" +
            "  rpot.[RowVersion], \r\n" +
            "  rpot.[Catalog], \r\n" +
            "  rpot.[Name], \r\n" +
            "  rpot.[MaxRetention], \r\n" +
            "  rpot.[Radar] \r\n" +
            "FROM [RadarPowerOnTimeseriesView] rpot \r\n";

        public new const string BaseViewName = "RadarPowerOnTimeseriesView";
        public new const string ViewAliasName = "rpot";

        public const int RADAR_FIELD_ID = 5;

        public SimpleRadarPowerOnTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
    }

    public class SimpleRadarSaveSettingsTimeseriesDataReader : SimpleBooleanTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rsst.[Id], \r\n" +
            "  rsst.[EntityType], \r\n" +
            "  rsst.[RowVersion], \r\n" +
            "  rsst.[Catalog], \r\n" +
            "  rsst.[Name], \r\n" +
            "  rsst.[MaxRetention], \r\n" +
            "  rsst.[Radar] \r\n" +
            "FROM [RadarSaveSettingsTimeseriesView] rsst \r\n";

        public new const string BaseViewName = "RadarSaveSettingsTimeseriesView";
        public new const string ViewAliasName = "rsst";

        public const int RADAR_FIELD_ID = 5;

        public SimpleRadarSaveSettingsTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
    }

    public class SimpleRadarTrackingTimeseriesDataReader : SimpleBooleanTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rtt.[Id], \r\n" +
            "  rtt.[EntityType], \r\n" +
            "  rtt.[RowVersion], \r\n" +
            "  rtt.[Catalog], \r\n" +
            "  rtt.[Name], \r\n" +
            "  rtt.[MaxRetention], \r\n" +
            "  rtt.[Radar] \r\n" +
            "FROM [RadarTrackingTimeseriesView] rtt \r\n";

        public new const string BaseViewName = "RadarTrackingTimeseriesView";
        public new const string ViewAliasName = "rtt";

        public const int RADAR_FIELD_ID = 5;

        public SimpleRadarTrackingTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
    }

    public class SimpleMediaProxySessionEnabledTimeseriesDataReader : SimpleBooleanTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  mpset.[Id], \r\n" +
            "  mpset.[EntityType], \r\n" +
            "  mpset.[RowVersion], \r\n" +
            "  mpset.[Catalog], \r\n" +
            "  mpset.[Name], \r\n" +
            "  mpset.[MaxRetention], \r\n" +
            "  mpset.[ProxySession] \r\n" +
            "FROM [MediaProxySessionEnabledTimeseriesView] mpset \r\n";

        public new const string BaseViewName = "MediaProxySessionEnabledTimeseriesView";
        public new const string ViewAliasName = "mpset";

        public const int PROXYSESSION_FIELD_ID = 5;

        public SimpleMediaProxySessionEnabledTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid ProxySession
        {
            get
            {
                return GetGuid( PROXYSESSION_FIELD_ID );
            }
        }
    }

    public class SimpleMediaServiceEnabledTimeseriesDataReader : SimpleBooleanTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  mset.[Id], \r\n" +
            "  mset.[EntityType], \r\n" +
            "  mset.[RowVersion], \r\n" +
            "  mset.[Catalog], \r\n" +
            "  mset.[Name], \r\n" +
            "  mset.[MaxRetention], \r\n" +
            "  mset.[Service] \r\n" +
            "FROM [MediaServiceEnabledTimeseriesView] mset \r\n";

        public new const string BaseViewName = "MediaServiceEnabledTimeseriesView";
        public new const string ViewAliasName = "mset";

        public const int SERVICE_FIELD_ID = 5;

        public SimpleMediaServiceEnabledTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Service
        {
            get
            {
                return GetGuid( SERVICE_FIELD_ID );
            }
        }
    }

    public class SimpleByteTimeseriesDataReader : SimpleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  byts.[Id], \r\n" +
            "  byts.[EntityType], \r\n" +
            "  byts.[RowVersion], \r\n" +
            "  byts.[Catalog], \r\n" +
            "  byts.[Name], \r\n" +
            "  byts.[MaxRetention] \r\n" +
            "FROM [ByteTimeseriesView] byts \r\n";

        public new const string BaseViewName = "ByteTimeseriesView";
        public new const string ViewAliasName = "byts";

        public SimpleByteTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleDateTimeTimeseriesDataReader : SimpleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  dtt.[Id], \r\n" +
            "  dtt.[EntityType], \r\n" +
            "  dtt.[RowVersion], \r\n" +
            "  dtt.[Catalog], \r\n" +
            "  dtt.[Name], \r\n" +
            "  dtt.[MaxRetention] \r\n" +
            "FROM [DateTimeTimeseriesView] dtt \r\n";

        public new const string BaseViewName = "DateTimeTimeseriesView";
        public new const string ViewAliasName = "dtt";

        public SimpleDateTimeTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleDoubleTimeseriesDataReader : SimpleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  dt.[Id], \r\n" +
            "  dt.[EntityType], \r\n" +
            "  dt.[RowVersion], \r\n" +
            "  dt.[Catalog], \r\n" +
            "  dt.[Name], \r\n" +
            "  dt.[MaxRetention] \r\n" +
            "FROM [DoubleTimeseriesView] dt \r\n";

        public new const string BaseViewName = "DoubleTimeseriesView";
        public new const string ViewAliasName = "dt";

        public SimpleDoubleTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleGNSSAltitudeTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  gats.[Id], \r\n" +
            "  gats.[EntityType], \r\n" +
            "  gats.[RowVersion], \r\n" +
            "  gats.[Catalog], \r\n" +
            "  gats.[Name], \r\n" +
            "  gats.[MaxRetention], \r\n" +
            "  gats.[GNSSDevice] \r\n" +
            "FROM [GNSSAltitudeTimeseriesView] gats \r\n";

        public new const string BaseViewName = "GNSSAltitudeTimeseriesView";
        public new const string ViewAliasName = "gats";

        public const int GNSSDEVICE_FIELD_ID = 5;

        public SimpleGNSSAltitudeTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid GNSSDevice
        {
            get
            {
                return GetGuid( GNSSDEVICE_FIELD_ID );
            }
        }
    }

    public class SimpleGNSSLatitudeTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  glats.[Id], \r\n" +
            "  glats.[EntityType], \r\n" +
            "  glats.[RowVersion], \r\n" +
            "  glats.[Catalog], \r\n" +
            "  glats.[Name], \r\n" +
            "  glats.[MaxRetention], \r\n" +
            "  glats.[GNSSDevice] \r\n" +
            "FROM [GNSSLatitudeTimeseriesView] glats \r\n";

        public new const string BaseViewName = "GNSSLatitudeTimeseriesView";
        public new const string ViewAliasName = "glats";

        public const int GNSSDEVICE_FIELD_ID = 5;

        public SimpleGNSSLatitudeTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid GNSSDevice
        {
            get
            {
                return GetGuid( GNSSDEVICE_FIELD_ID );
            }
        }
    }

    public class SimpleGNSSLongitudeTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  glots.[Id], \r\n" +
            "  glots.[EntityType], \r\n" +
            "  glots.[RowVersion], \r\n" +
            "  glots.[Catalog], \r\n" +
            "  glots.[Name], \r\n" +
            "  glots.[MaxRetention], \r\n" +
            "  glots.[GNSSDevice] \r\n" +
            "FROM [GNSSLongitudeTimeseriesView] glots \r\n";

        public new const string BaseViewName = "GNSSLongitudeTimeseriesView";
        public new const string ViewAliasName = "glots";

        public const int GNSSDEVICE_FIELD_ID = 5;

        public SimpleGNSSLongitudeTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid GNSSDevice
        {
            get
            {
                return GetGuid( GNSSDEVICE_FIELD_ID );
            }
        }
    }

    public class SimpleGyroCourseTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  gct.[Id], \r\n" +
            "  gct.[EntityType], \r\n" +
            "  gct.[RowVersion], \r\n" +
            "  gct.[Catalog], \r\n" +
            "  gct.[Name], \r\n" +
            "  gct.[MaxRetention], \r\n" +
            "  gct.[GyroDevice] \r\n" +
            "FROM [GyroCourseTimeseriesView] gct \r\n";

        public new const string BaseViewName = "GyroCourseTimeseriesView";
        public new const string ViewAliasName = "gct";

        public const int GYRODEVICE_FIELD_ID = 5;

        public SimpleGyroCourseTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid GyroDevice
        {
            get
            {
                return GetGuid( GYRODEVICE_FIELD_ID );
            }
        }
    }

    public class SimpleGyroHeadingMagneticNorthTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  ghmnt.[Id], \r\n" +
            "  ghmnt.[EntityType], \r\n" +
            "  ghmnt.[RowVersion], \r\n" +
            "  ghmnt.[Catalog], \r\n" +
            "  ghmnt.[Name], \r\n" +
            "  ghmnt.[MaxRetention], \r\n" +
            "  ghmnt.[GyroDevice] \r\n" +
            "FROM [GyroHeadingMagneticNorthTimeseriesView] ghmnt \r\n";

        public new const string BaseViewName = "GyroHeadingMagneticNorthTimeseriesView";
        public new const string ViewAliasName = "ghmnt";

        public const int GYRODEVICE_FIELD_ID = 5;

        public SimpleGyroHeadingMagneticNorthTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid GyroDevice
        {
            get
            {
                return GetGuid( GYRODEVICE_FIELD_ID );
            }
        }
    }

    public class SimpleGyroHeadingTrueNorthTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  ghtnt.[Id], \r\n" +
            "  ghtnt.[EntityType], \r\n" +
            "  ghtnt.[RowVersion], \r\n" +
            "  ghtnt.[Catalog], \r\n" +
            "  ghtnt.[Name], \r\n" +
            "  ghtnt.[MaxRetention], \r\n" +
            "  ghtnt.[GyroDevice] \r\n" +
            "FROM [GyroHeadingTrueNorthTimeseriesView] ghtnt \r\n";

        public new const string BaseViewName = "GyroHeadingTrueNorthTimeseriesView";
        public new const string ViewAliasName = "ghtnt";

        public const int GYRODEVICE_FIELD_ID = 5;

        public SimpleGyroHeadingTrueNorthTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid GyroDevice
        {
            get
            {
                return GetGuid( GYRODEVICE_FIELD_ID );
            }
        }
    }

    public class SimpleGyroPitchTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  gpt.[Id], \r\n" +
            "  gpt.[EntityType], \r\n" +
            "  gpt.[RowVersion], \r\n" +
            "  gpt.[Catalog], \r\n" +
            "  gpt.[Name], \r\n" +
            "  gpt.[MaxRetention], \r\n" +
            "  gpt.[GyroDevice] \r\n" +
            "FROM [GyroPitchTimeseriesView] gpt \r\n";

        public new const string BaseViewName = "GyroPitchTimeseriesView";
        public new const string ViewAliasName = "gpt";

        public const int GYRODEVICE_FIELD_ID = 5;

        public SimpleGyroPitchTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid GyroDevice
        {
            get
            {
                return GetGuid( GYRODEVICE_FIELD_ID );
            }
        }
    }

    public class SimpleGyroRateOfTurnTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  grott.[Id], \r\n" +
            "  grott.[EntityType], \r\n" +
            "  grott.[RowVersion], \r\n" +
            "  grott.[Catalog], \r\n" +
            "  grott.[Name], \r\n" +
            "  grott.[MaxRetention], \r\n" +
            "  grott.[GyroDevice] \r\n" +
            "FROM [GyroRateOfTurnTimeseriesView] grott \r\n";

        public new const string BaseViewName = "GyroRateOfTurnTimeseriesView";
        public new const string ViewAliasName = "grott";

        public const int GYRODEVICE_FIELD_ID = 5;

        public SimpleGyroRateOfTurnTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid GyroDevice
        {
            get
            {
                return GetGuid( GYRODEVICE_FIELD_ID );
            }
        }
    }

    public class SimpleGyroRollTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  grt.[Id], \r\n" +
            "  grt.[EntityType], \r\n" +
            "  grt.[RowVersion], \r\n" +
            "  grt.[Catalog], \r\n" +
            "  grt.[Name], \r\n" +
            "  grt.[MaxRetention], \r\n" +
            "  grt.[GyroDevice] \r\n" +
            "FROM [GyroRollTimeseriesView] grt \r\n";

        public new const string BaseViewName = "GyroRollTimeseriesView";
        public new const string ViewAliasName = "grt";

        public const int GYRODEVICE_FIELD_ID = 5;

        public SimpleGyroRollTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid GyroDevice
        {
            get
            {
                return GetGuid( GYRODEVICE_FIELD_ID );
            }
        }
    }

    public class SimpleGyroSpeedTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  gst.[Id], \r\n" +
            "  gst.[EntityType], \r\n" +
            "  gst.[RowVersion], \r\n" +
            "  gst.[Catalog], \r\n" +
            "  gst.[Name], \r\n" +
            "  gst.[MaxRetention], \r\n" +
            "  gst.[GyroDevice] \r\n" +
            "FROM [GyroSpeedTimeseriesView] gst \r\n";

        public new const string BaseViewName = "GyroSpeedTimeseriesView";
        public new const string ViewAliasName = "gst";

        public const int GYRODEVICE_FIELD_ID = 5;

        public SimpleGyroSpeedTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid GyroDevice
        {
            get
            {
                return GetGuid( GYRODEVICE_FIELD_ID );
            }
        }
    }

    public class SimpleRadarLatitudeTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rlats.[Id], \r\n" +
            "  rlats.[EntityType], \r\n" +
            "  rlats.[RowVersion], \r\n" +
            "  rlats.[Catalog], \r\n" +
            "  rlats.[Name], \r\n" +
            "  rlats.[MaxRetention], \r\n" +
            "  rlats.[Radar] \r\n" +
            "FROM [RadarLatitudeTimeseriesView] rlats \r\n";

        public new const string BaseViewName = "RadarLatitudeTimeseriesView";
        public new const string ViewAliasName = "rlats";

        public const int RADAR_FIELD_ID = 5;

        public SimpleRadarLatitudeTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
    }

    public class SimpleRadarLongitudeTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rlots.[Id], \r\n" +
            "  rlots.[EntityType], \r\n" +
            "  rlots.[RowVersion], \r\n" +
            "  rlots.[Catalog], \r\n" +
            "  rlots.[Name], \r\n" +
            "  rlots.[MaxRetention], \r\n" +
            "  rlots.[Radar] \r\n" +
            "FROM [RadarLongitudeTimeseriesView] rlots \r\n";

        public new const string BaseViewName = "RadarLongitudeTimeseriesView";
        public new const string ViewAliasName = "rlots";

        public const int RADAR_FIELD_ID = 5;

        public SimpleRadarLongitudeTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
    }

    public class SimpleRadomeDewPointTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rdpt.[Id], \r\n" +
            "  rdpt.[EntityType], \r\n" +
            "  rdpt.[RowVersion], \r\n" +
            "  rdpt.[Catalog], \r\n" +
            "  rdpt.[Name], \r\n" +
            "  rdpt.[MaxRetention], \r\n" +
            "  rdpt.[Radome] \r\n" +
            "FROM [RadomeDewPointTimeseriesView] rdpt \r\n";

        public new const string BaseViewName = "RadomeDewPointTimeseriesView";
        public new const string ViewAliasName = "rdpt";

        public const int RADOME_FIELD_ID = 5;

        public SimpleRadomeDewPointTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Radome
        {
            get
            {
                return GetGuid( RADOME_FIELD_ID );
            }
        }
    }

    public class SimpleRadomePressureTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rpt.[Id], \r\n" +
            "  rpt.[EntityType], \r\n" +
            "  rpt.[RowVersion], \r\n" +
            "  rpt.[Catalog], \r\n" +
            "  rpt.[Name], \r\n" +
            "  rpt.[MaxRetention], \r\n" +
            "  rpt.[Radome] \r\n" +
            "FROM [RadomePressureTimeseriesView] rpt \r\n";

        public new const string BaseViewName = "RadomePressureTimeseriesView";
        public new const string ViewAliasName = "rpt";

        public const int RADOME_FIELD_ID = 5;

        public SimpleRadomePressureTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Radome
        {
            get
            {
                return GetGuid( RADOME_FIELD_ID );
            }
        }
    }

    public class SimpleRadomeTemperatureTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rtets.[Id], \r\n" +
            "  rtets.[EntityType], \r\n" +
            "  rtets.[RowVersion], \r\n" +
            "  rtets.[Catalog], \r\n" +
            "  rtets.[Name], \r\n" +
            "  rtets.[MaxRetention], \r\n" +
            "  rtets.[Radome] \r\n" +
            "FROM [RadomeTemperatureTimeseriesView] rtets \r\n";

        public new const string BaseViewName = "RadomeTemperatureTimeseriesView";
        public new const string ViewAliasName = "rtets";

        public const int RADOME_FIELD_ID = 5;

        public SimpleRadomeTemperatureTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Radome
        {
            get
            {
                return GetGuid( RADOME_FIELD_ID );
            }
        }
    }

    public class SimpleVesselDraughtTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  vdt.[Id], \r\n" +
            "  vdt.[EntityType], \r\n" +
            "  vdt.[RowVersion], \r\n" +
            "  vdt.[Catalog], \r\n" +
            "  vdt.[Name], \r\n" +
            "  vdt.[MaxRetention], \r\n" +
            "  vdt.[Vessel] \r\n" +
            "FROM [VesselDraughtTimeseriesView] vdt \r\n";

        public new const string BaseViewName = "VesselDraughtTimeseriesView";
        public new const string ViewAliasName = "vdt";

        public const int VESSEL_FIELD_ID = 5;

        public SimpleVesselDraughtTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Vessel
        {
            get
            {
                return GetGuid( VESSEL_FIELD_ID );
            }
        }
    }

    public class SimpleViewLatitudeTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  vlats.[Id], \r\n" +
            "  vlats.[EntityType], \r\n" +
            "  vlats.[RowVersion], \r\n" +
            "  vlats.[Catalog], \r\n" +
            "  vlats.[Name], \r\n" +
            "  vlats.[MaxRetention], \r\n" +
            "  vlats.[View] \r\n" +
            "FROM [ViewLatitudeTimeseriesView] vlats \r\n";

        public new const string BaseViewName = "ViewLatitudeTimeseriesView";
        public new const string ViewAliasName = "vlats";

        public const int VIEW_FIELD_ID = 5;

        public SimpleViewLatitudeTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid View
        {
            get
            {
                return GetGuid( VIEW_FIELD_ID );
            }
        }
    }

    public class SimpleViewLongitudeTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  vlots.[Id], \r\n" +
            "  vlots.[EntityType], \r\n" +
            "  vlots.[RowVersion], \r\n" +
            "  vlots.[Catalog], \r\n" +
            "  vlots.[Name], \r\n" +
            "  vlots.[MaxRetention], \r\n" +
            "  vlots.[View] \r\n" +
            "FROM [ViewLongitudeTimeseriesView] vlots \r\n";

        public new const string BaseViewName = "ViewLongitudeTimeseriesView";
        public new const string ViewAliasName = "vlots";

        public const int VIEW_FIELD_ID = 5;

        public SimpleViewLongitudeTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid View
        {
            get
            {
                return GetGuid( VIEW_FIELD_ID );
            }
        }
    }

    public class SimpleViewZoomLevelTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  vzlt.[Id], \r\n" +
            "  vzlt.[EntityType], \r\n" +
            "  vzlt.[RowVersion], \r\n" +
            "  vzlt.[Catalog], \r\n" +
            "  vzlt.[Name], \r\n" +
            "  vzlt.[MaxRetention], \r\n" +
            "  vzlt.[View] \r\n" +
            "FROM [ViewZoomLevelTimeseriesView] vzlt \r\n";

        public new const string BaseViewName = "ViewZoomLevelTimeseriesView";
        public new const string ViewAliasName = "vzlt";

        public const int VIEW_FIELD_ID = 5;

        public SimpleViewZoomLevelTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid View
        {
            get
            {
                return GetGuid( VIEW_FIELD_ID );
            }
        }
    }

    public class SimpleWeatherStationAbsoluteHumidityTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  wsaht.[Id], \r\n" +
            "  wsaht.[EntityType], \r\n" +
            "  wsaht.[RowVersion], \r\n" +
            "  wsaht.[Catalog], \r\n" +
            "  wsaht.[Name], \r\n" +
            "  wsaht.[MaxRetention], \r\n" +
            "  wsaht.[WeatherStation] \r\n" +
            "FROM [WeatherStationAbsoluteHumidityTimeseriesView] wsaht \r\n";

        public new const string BaseViewName = "WeatherStationAbsoluteHumidityTimeseriesView";
        public new const string ViewAliasName = "wsaht";

        public const int WEATHERSTATION_FIELD_ID = 5;

        public SimpleWeatherStationAbsoluteHumidityTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid WeatherStation
        {
            get
            {
                return GetGuid( WEATHERSTATION_FIELD_ID );
            }
        }
    }

    public class SimpleWeatherStationAirTemperatureTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  wsatt.[Id], \r\n" +
            "  wsatt.[EntityType], \r\n" +
            "  wsatt.[RowVersion], \r\n" +
            "  wsatt.[Catalog], \r\n" +
            "  wsatt.[Name], \r\n" +
            "  wsatt.[MaxRetention], \r\n" +
            "  wsatt.[WeatherStation] \r\n" +
            "FROM [WeatherStationAirTemperatureTimeseriesView] wsatt \r\n";

        public new const string BaseViewName = "WeatherStationAirTemperatureTimeseriesView";
        public new const string ViewAliasName = "wsatt";

        public const int WEATHERSTATION_FIELD_ID = 5;

        public SimpleWeatherStationAirTemperatureTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid WeatherStation
        {
            get
            {
                return GetGuid( WEATHERSTATION_FIELD_ID );
            }
        }
    }

    public class SimpleWeatherStationBarometricPressureTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  wsbpt.[Id], \r\n" +
            "  wsbpt.[EntityType], \r\n" +
            "  wsbpt.[RowVersion], \r\n" +
            "  wsbpt.[Catalog], \r\n" +
            "  wsbpt.[Name], \r\n" +
            "  wsbpt.[MaxRetention], \r\n" +
            "  wsbpt.[WeatherStation] \r\n" +
            "FROM [WeatherStationBarometricPressureTimeseriesView] wsbpt \r\n";

        public new const string BaseViewName = "WeatherStationBarometricPressureTimeseriesView";
        public new const string ViewAliasName = "wsbpt";

        public const int WEATHERSTATION_FIELD_ID = 5;

        public SimpleWeatherStationBarometricPressureTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid WeatherStation
        {
            get
            {
                return GetGuid( WEATHERSTATION_FIELD_ID );
            }
        }
    }

    public class SimpleWeatherStationDewPointTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  wsdpt.[Id], \r\n" +
            "  wsdpt.[EntityType], \r\n" +
            "  wsdpt.[RowVersion], \r\n" +
            "  wsdpt.[Catalog], \r\n" +
            "  wsdpt.[Name], \r\n" +
            "  wsdpt.[MaxRetention], \r\n" +
            "  wsdpt.[WeatherStation] \r\n" +
            "FROM [WeatherStationDewPointTimeseriesView] wsdpt \r\n";

        public new const string BaseViewName = "WeatherStationDewPointTimeseriesView";
        public new const string ViewAliasName = "wsdpt";

        public const int WEATHERSTATION_FIELD_ID = 5;

        public SimpleWeatherStationDewPointTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid WeatherStation
        {
            get
            {
                return GetGuid( WEATHERSTATION_FIELD_ID );
            }
        }
    }

    public class SimpleWeatherStationRelativeHumidityTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  wsrht.[Id], \r\n" +
            "  wsrht.[EntityType], \r\n" +
            "  wsrht.[RowVersion], \r\n" +
            "  wsrht.[Catalog], \r\n" +
            "  wsrht.[Name], \r\n" +
            "  wsrht.[MaxRetention], \r\n" +
            "  wsrht.[WeatherStation] \r\n" +
            "FROM [WeatherStationRelativeHumidityTimeseriesView] wsrht \r\n";

        public new const string BaseViewName = "WeatherStationRelativeHumidityTimeseriesView";
        public new const string ViewAliasName = "wsrht";

        public const int WEATHERSTATION_FIELD_ID = 5;

        public SimpleWeatherStationRelativeHumidityTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid WeatherStation
        {
            get
            {
                return GetGuid( WEATHERSTATION_FIELD_ID );
            }
        }
    }

    public class SimpleWeatherStationWaterTemperatureTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  wswtt.[Id], \r\n" +
            "  wswtt.[EntityType], \r\n" +
            "  wswtt.[RowVersion], \r\n" +
            "  wswtt.[Catalog], \r\n" +
            "  wswtt.[Name], \r\n" +
            "  wswtt.[MaxRetention], \r\n" +
            "  wswtt.[WeatherStation] \r\n" +
            "FROM [WeatherStationWaterTemperatureTimeseriesView] wswtt \r\n";

        public new const string BaseViewName = "WeatherStationWaterTemperatureTimeseriesView";
        public new const string ViewAliasName = "wswtt";

        public const int WEATHERSTATION_FIELD_ID = 5;

        public SimpleWeatherStationWaterTemperatureTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid WeatherStation
        {
            get
            {
                return GetGuid( WEATHERSTATION_FIELD_ID );
            }
        }
    }

    public class SimpleWeatherStationWindDirectionTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  wswdt.[Id], \r\n" +
            "  wswdt.[EntityType], \r\n" +
            "  wswdt.[RowVersion], \r\n" +
            "  wswdt.[Catalog], \r\n" +
            "  wswdt.[Name], \r\n" +
            "  wswdt.[MaxRetention], \r\n" +
            "  wswdt.[WeatherStation] \r\n" +
            "FROM [WeatherStationWindDirectionTimeseriesView] wswdt \r\n";

        public new const string BaseViewName = "WeatherStationWindDirectionTimeseriesView";
        public new const string ViewAliasName = "wswdt";

        public const int WEATHERSTATION_FIELD_ID = 5;

        public SimpleWeatherStationWindDirectionTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid WeatherStation
        {
            get
            {
                return GetGuid( WEATHERSTATION_FIELD_ID );
            }
        }
    }

    public class SimpleWeatherStationWindSpeedTimeseriesDataReader : SimpleDoubleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  wswst.[Id], \r\n" +
            "  wswst.[EntityType], \r\n" +
            "  wswst.[RowVersion], \r\n" +
            "  wswst.[Catalog], \r\n" +
            "  wswst.[Name], \r\n" +
            "  wswst.[MaxRetention], \r\n" +
            "  wswst.[WeatherStation] \r\n" +
            "FROM [WeatherStationWindSpeedTimeseriesView] wswst \r\n";

        public new const string BaseViewName = "WeatherStationWindSpeedTimeseriesView";
        public new const string ViewAliasName = "wswst";

        public const int WEATHERSTATION_FIELD_ID = 5;

        public SimpleWeatherStationWindSpeedTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid WeatherStation
        {
            get
            {
                return GetGuid( WEATHERSTATION_FIELD_ID );
            }
        }
    }

    public class SimpleGeoPosition2DTimeseriesDataReader : SimpleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  gp2d.[Id], \r\n" +
            "  gp2d.[EntityType], \r\n" +
            "  gp2d.[RowVersion], \r\n" +
            "  gp2d.[Catalog], \r\n" +
            "  gp2d.[Name], \r\n" +
            "  gp2d.[MaxRetention] \r\n" +
            "FROM [GeoPosition2DTimeseriesView] gp2d \r\n";

        public new const string BaseViewName = "GeoPosition2DTimeseriesView";
        public new const string ViewAliasName = "gp2d";

        public SimpleGeoPosition2DTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleAisAidToNavigationPositionTimeseriesDataReader : SimpleGeoPosition2DTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  aatnpt.[Id], \r\n" +
            "  aatnpt.[EntityType], \r\n" +
            "  aatnpt.[RowVersion], \r\n" +
            "  aatnpt.[Catalog], \r\n" +
            "  aatnpt.[Name], \r\n" +
            "  aatnpt.[MaxRetention], \r\n" +
            "  aatnpt.[AidToNavigation] \r\n" +
            "FROM [AisAidToNavigationPositionTimeseriesView] aatnpt \r\n";

        public new const string BaseViewName = "AisAidToNavigationPositionTimeseriesView";
        public new const string ViewAliasName = "aatnpt";

        public const int AIDTONAVIGATION_FIELD_ID = 5;

        public SimpleAisAidToNavigationPositionTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid AidToNavigation
        {
            get
            {
                return GetGuid( AIDTONAVIGATION_FIELD_ID );
            }
        }
    }

    public class SimpleGeoPosition3DTimeseriesDataReader : SimpleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  gp3d.[Id], \r\n" +
            "  gp3d.[EntityType], \r\n" +
            "  gp3d.[RowVersion], \r\n" +
            "  gp3d.[Catalog], \r\n" +
            "  gp3d.[Name], \r\n" +
            "  gp3d.[MaxRetention] \r\n" +
            "FROM [GeoPosition3DTimeseriesView] gp3d \r\n";

        public new const string BaseViewName = "GeoPosition3DTimeseriesView";
        public new const string ViewAliasName = "gp3d";

        public SimpleGeoPosition3DTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleGuidTimeseriesDataReader : SimpleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  gt.[Id], \r\n" +
            "  gt.[EntityType], \r\n" +
            "  gt.[RowVersion], \r\n" +
            "  gt.[Catalog], \r\n" +
            "  gt.[Name], \r\n" +
            "  gt.[MaxRetention] \r\n" +
            "FROM [GuidTimeseriesView] gt \r\n";

        public new const string BaseViewName = "GuidTimeseriesView";
        public new const string ViewAliasName = "gt";

        public SimpleGuidTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleInt16TimeseriesDataReader : SimpleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  i16t.[Id], \r\n" +
            "  i16t.[EntityType], \r\n" +
            "  i16t.[RowVersion], \r\n" +
            "  i16t.[Catalog], \r\n" +
            "  i16t.[Name], \r\n" +
            "  i16t.[MaxRetention] \r\n" +
            "FROM [Int16TimeseriesView] i16t \r\n";

        public new const string BaseViewName = "Int16TimeseriesView";
        public new const string ViewAliasName = "i16t";

        public SimpleInt16TimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleInt32TimeseriesDataReader : SimpleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  i32t.[Id], \r\n" +
            "  i32t.[EntityType], \r\n" +
            "  i32t.[RowVersion], \r\n" +
            "  i32t.[Catalog], \r\n" +
            "  i32t.[Name], \r\n" +
            "  i32t.[MaxRetention] \r\n" +
            "FROM [Int32TimeseriesView] i32t \r\n";

        public new const string BaseViewName = "Int32TimeseriesView";
        public new const string ViewAliasName = "i32t";

        public SimpleInt32TimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleRadarAzimuthOffsetTimeseriesDataReader : SimpleInt32TimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  raot.[Id], \r\n" +
            "  raot.[EntityType], \r\n" +
            "  raot.[RowVersion], \r\n" +
            "  raot.[Catalog], \r\n" +
            "  raot.[Name], \r\n" +
            "  raot.[MaxRetention], \r\n" +
            "  raot.[Radar] \r\n" +
            "FROM [RadarAzimuthOffsetTimeseriesView] raot \r\n";

        public new const string BaseViewName = "RadarAzimuthOffsetTimeseriesView";
        public new const string ViewAliasName = "raot";

        public const int RADAR_FIELD_ID = 5;

        public SimpleRadarAzimuthOffsetTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
    }

    public class SimpleRadarFastTimeConstantLevelTimeseriesDataReader : SimpleInt32TimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rftclt.[Id], \r\n" +
            "  rftclt.[EntityType], \r\n" +
            "  rftclt.[RowVersion], \r\n" +
            "  rftclt.[Catalog], \r\n" +
            "  rftclt.[Name], \r\n" +
            "  rftclt.[MaxRetention], \r\n" +
            "  rftclt.[Radar] \r\n" +
            "FROM [RadarFastTimeConstantLevelTimeseriesView] rftclt \r\n";

        public new const string BaseViewName = "RadarFastTimeConstantLevelTimeseriesView";
        public new const string ViewAliasName = "rftclt";

        public const int RADAR_FIELD_ID = 5;

        public SimpleRadarFastTimeConstantLevelTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
    }

    public class SimpleRadarFastTimeConstantModeTimeseriesDataReader : SimpleInt32TimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rftcmt.[Id], \r\n" +
            "  rftcmt.[EntityType], \r\n" +
            "  rftcmt.[RowVersion], \r\n" +
            "  rftcmt.[Catalog], \r\n" +
            "  rftcmt.[Name], \r\n" +
            "  rftcmt.[MaxRetention], \r\n" +
            "  rftcmt.[Radar] \r\n" +
            "FROM [RadarFastTimeConstantModeTimeseriesView] rftcmt \r\n";

        public new const string BaseViewName = "RadarFastTimeConstantModeTimeseriesView";
        public new const string ViewAliasName = "rftcmt";

        public const int RADAR_FIELD_ID = 5;

        public SimpleRadarFastTimeConstantModeTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
    }

    public class SimpleRadarPulseTimeseriesDataReader : SimpleInt32TimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rapts.[Id], \r\n" +
            "  rapts.[EntityType], \r\n" +
            "  rapts.[RowVersion], \r\n" +
            "  rapts.[Catalog], \r\n" +
            "  rapts.[Name], \r\n" +
            "  rapts.[MaxRetention], \r\n" +
            "  rapts.[Radar] \r\n" +
            "FROM [RadarPulseTimeseriesView] rapts \r\n";

        public new const string BaseViewName = "RadarPulseTimeseriesView";
        public new const string ViewAliasName = "rapts";

        public const int RADAR_FIELD_ID = 5;

        public SimpleRadarPulseTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
    }

    public class SimpleRadarSector1EndTimeseriesDataReader : SimpleInt32TimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rs1et.[Id], \r\n" +
            "  rs1et.[EntityType], \r\n" +
            "  rs1et.[RowVersion], \r\n" +
            "  rs1et.[Catalog], \r\n" +
            "  rs1et.[Name], \r\n" +
            "  rs1et.[MaxRetention], \r\n" +
            "  rs1et.[Radar] \r\n" +
            "FROM [RadarSector1EndTimeseriesView] rs1et \r\n";

        public new const string BaseViewName = "RadarSector1EndTimeseriesView";
        public new const string ViewAliasName = "rs1et";

        public const int RADAR_FIELD_ID = 5;

        public SimpleRadarSector1EndTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
    }

    public class SimpleRadarSector1StartTimeseriesDataReader : SimpleInt32TimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rs1st.[Id], \r\n" +
            "  rs1st.[EntityType], \r\n" +
            "  rs1st.[RowVersion], \r\n" +
            "  rs1st.[Catalog], \r\n" +
            "  rs1st.[Name], \r\n" +
            "  rs1st.[MaxRetention], \r\n" +
            "  rs1st.[Radar] \r\n" +
            "FROM [RadarSector1StartTimeseriesView] rs1st \r\n";

        public new const string BaseViewName = "RadarSector1StartTimeseriesView";
        public new const string ViewAliasName = "rs1st";

        public const int RADAR_FIELD_ID = 5;

        public SimpleRadarSector1StartTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
    }

    public class SimpleRadarSector2EndTimeseriesDataReader : SimpleInt32TimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rs2et.[Id], \r\n" +
            "  rs2et.[EntityType], \r\n" +
            "  rs2et.[RowVersion], \r\n" +
            "  rs2et.[Catalog], \r\n" +
            "  rs2et.[Name], \r\n" +
            "  rs2et.[MaxRetention], \r\n" +
            "  rs2et.[Radar] \r\n" +
            "FROM [RadarSector2EndTimeseriesView] rs2et \r\n";

        public new const string BaseViewName = "RadarSector2EndTimeseriesView";
        public new const string ViewAliasName = "rs2et";

        public const int RADAR_FIELD_ID = 5;

        public SimpleRadarSector2EndTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
    }

    public class SimpleRadarSector2StartTimeseriesDataReader : SimpleInt32TimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rs2st.[Id], \r\n" +
            "  rs2st.[EntityType], \r\n" +
            "  rs2st.[RowVersion], \r\n" +
            "  rs2st.[Catalog], \r\n" +
            "  rs2st.[Name], \r\n" +
            "  rs2st.[MaxRetention], \r\n" +
            "  rs2st.[Radar] \r\n" +
            "FROM [RadarSector2StartTimeseriesView] rs2st \r\n";

        public new const string BaseViewName = "RadarSector2StartTimeseriesView";
        public new const string ViewAliasName = "rs2st";

        public const int RADAR_FIELD_ID = 5;

        public SimpleRadarSector2StartTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
    }

    public class SimpleRadarSensitivityTimeControlLevelTimeseriesDataReader : SimpleInt32TimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rstclt.[Id], \r\n" +
            "  rstclt.[EntityType], \r\n" +
            "  rstclt.[RowVersion], \r\n" +
            "  rstclt.[Catalog], \r\n" +
            "  rstclt.[Name], \r\n" +
            "  rstclt.[MaxRetention], \r\n" +
            "  rstclt.[Radar] \r\n" +
            "FROM [RadarSensitivityTimeControlLevelTimeseriesView] rstclt \r\n";

        public new const string BaseViewName = "RadarSensitivityTimeControlLevelTimeseriesView";
        public new const string ViewAliasName = "rstclt";

        public const int RADAR_FIELD_ID = 5;

        public SimpleRadarSensitivityTimeControlLevelTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
    }

    public class SimpleRadarTuningTimeseriesDataReader : SimpleInt32TimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  ratuts.[Id], \r\n" +
            "  ratuts.[EntityType], \r\n" +
            "  ratuts.[RowVersion], \r\n" +
            "  ratuts.[Catalog], \r\n" +
            "  ratuts.[Name], \r\n" +
            "  ratuts.[MaxRetention], \r\n" +
            "  ratuts.[Radar] \r\n" +
            "FROM [RadarTuningTimeseriesView] ratuts \r\n";

        public new const string BaseViewName = "RadarTuningTimeseriesView";
        public new const string ViewAliasName = "ratuts";

        public const int RADAR_FIELD_ID = 5;

        public SimpleRadarTuningTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Radar
        {
            get
            {
                return GetGuid( RADAR_FIELD_ID );
            }
        }
    }

    public class SimpleVesselPersonsOnBoardTimeseriesDataReader : SimpleInt32TimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  vpobt.[Id], \r\n" +
            "  vpobt.[EntityType], \r\n" +
            "  vpobt.[RowVersion], \r\n" +
            "  vpobt.[Catalog], \r\n" +
            "  vpobt.[Name], \r\n" +
            "  vpobt.[MaxRetention], \r\n" +
            "  vpobt.[Vessel] \r\n" +
            "FROM [VesselPersonsOnBoardTimeseriesView] vpobt \r\n";

        public new const string BaseViewName = "VesselPersonsOnBoardTimeseriesView";
        public new const string ViewAliasName = "vpobt";

        public const int VESSEL_FIELD_ID = 5;

        public SimpleVesselPersonsOnBoardTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Vessel
        {
            get
            {
                return GetGuid( VESSEL_FIELD_ID );
            }
        }
    }

    public class SimpleInt64TimeseriesDataReader : SimpleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  i64t.[Id], \r\n" +
            "  i64t.[EntityType], \r\n" +
            "  i64t.[RowVersion], \r\n" +
            "  i64t.[Catalog], \r\n" +
            "  i64t.[Name], \r\n" +
            "  i64t.[MaxRetention] \r\n" +
            "FROM [Int64TimeseriesView] i64t \r\n";

        public new const string BaseViewName = "Int64TimeseriesView";
        public new const string ViewAliasName = "i64t";

        public SimpleInt64TimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimplePosition2DTimeseriesDataReader : SimpleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  p2d.[Id], \r\n" +
            "  p2d.[EntityType], \r\n" +
            "  p2d.[RowVersion], \r\n" +
            "  p2d.[Catalog], \r\n" +
            "  p2d.[Name], \r\n" +
            "  p2d.[MaxRetention] \r\n" +
            "FROM [Position2DTimeseriesView] p2d \r\n";

        public new const string BaseViewName = "Position2DTimeseriesView";
        public new const string ViewAliasName = "p2d";

        public SimplePosition2DTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimplePosition3DTimeseriesDataReader : SimpleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  p3d.[Id], \r\n" +
            "  p3d.[EntityType], \r\n" +
            "  p3d.[RowVersion], \r\n" +
            "  p3d.[Catalog], \r\n" +
            "  p3d.[Name], \r\n" +
            "  p3d.[MaxRetention] \r\n" +
            "FROM [Position3DTimeseriesView] p3d \r\n";

        public new const string BaseViewName = "Position3DTimeseriesView";
        public new const string ViewAliasName = "p3d";

        public SimplePosition3DTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleReferenceTimeseriesDataReader : SimpleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rt.[Id], \r\n" +
            "  rt.[EntityType], \r\n" +
            "  rt.[RowVersion], \r\n" +
            "  rt.[Catalog], \r\n" +
            "  rt.[Name], \r\n" +
            "  rt.[MaxRetention] \r\n" +
            "FROM [ReferenceTimeseriesView] rt \r\n";

        public new const string BaseViewName = "ReferenceTimeseriesView";
        public new const string ViewAliasName = "rt";

        public SimpleReferenceTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleSByteTimeseriesDataReader : SimpleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  st.[Id], \r\n" +
            "  st.[EntityType], \r\n" +
            "  st.[RowVersion], \r\n" +
            "  st.[Catalog], \r\n" +
            "  st.[Name], \r\n" +
            "  st.[MaxRetention] \r\n" +
            "FROM [SByteTimeseriesView] st \r\n";

        public new const string BaseViewName = "SByteTimeseriesView";
        public new const string ViewAliasName = "st";

        public SimpleSByteTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleSingleTimeseriesDataReader : SimpleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  sits.[Id], \r\n" +
            "  sits.[EntityType], \r\n" +
            "  sits.[RowVersion], \r\n" +
            "  sits.[Catalog], \r\n" +
            "  sits.[Name], \r\n" +
            "  sits.[MaxRetention] \r\n" +
            "FROM [SingleTimeseriesView] sits \r\n";

        public new const string BaseViewName = "SingleTimeseriesView";
        public new const string ViewAliasName = "sits";

        public SimpleSingleTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleStringTimeseriesDataReader : SimpleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  stts.[Id], \r\n" +
            "  stts.[EntityType], \r\n" +
            "  stts.[RowVersion], \r\n" +
            "  stts.[Catalog], \r\n" +
            "  stts.[Name], \r\n" +
            "  stts.[MaxRetention] \r\n" +
            "FROM [StringTimeseriesView] stts \r\n";

        public new const string BaseViewName = "StringTimeseriesView";
        public new const string ViewAliasName = "stts";

        public SimpleStringTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleTimeSpanTimeseriesDataReader : SimpleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  tst.[Id], \r\n" +
            "  tst.[EntityType], \r\n" +
            "  tst.[RowVersion], \r\n" +
            "  tst.[Catalog], \r\n" +
            "  tst.[Name], \r\n" +
            "  tst.[MaxRetention] \r\n" +
            "FROM [TimeSpanTimeseriesView] tst \r\n";

        public new const string BaseViewName = "TimeSpanTimeseriesView";
        public new const string ViewAliasName = "tst";

        public SimpleTimeSpanTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleUInt16TimeseriesDataReader : SimpleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  u16t.[Id], \r\n" +
            "  u16t.[EntityType], \r\n" +
            "  u16t.[RowVersion], \r\n" +
            "  u16t.[Catalog], \r\n" +
            "  u16t.[Name], \r\n" +
            "  u16t.[MaxRetention] \r\n" +
            "FROM [UInt16TimeseriesView] u16t \r\n";

        public new const string BaseViewName = "UInt16TimeseriesView";
        public new const string ViewAliasName = "u16t";

        public SimpleUInt16TimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleUInt32TimeseriesDataReader : SimpleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  u32t.[Id], \r\n" +
            "  u32t.[EntityType], \r\n" +
            "  u32t.[RowVersion], \r\n" +
            "  u32t.[Catalog], \r\n" +
            "  u32t.[Name], \r\n" +
            "  u32t.[MaxRetention] \r\n" +
            "FROM [UInt32TimeseriesView] u32t \r\n";

        public new const string BaseViewName = "UInt32TimeseriesView";
        public new const string ViewAliasName = "u32t";

        public SimpleUInt32TimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleRadomeStatusTimeseriesDataReader : SimpleUInt32TimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  rst.[Id], \r\n" +
            "  rst.[EntityType], \r\n" +
            "  rst.[RowVersion], \r\n" +
            "  rst.[Catalog], \r\n" +
            "  rst.[Name], \r\n" +
            "  rst.[MaxRetention], \r\n" +
            "  rst.[Radome] \r\n" +
            "FROM [RadomeStatusTimeseriesView] rst \r\n";

        public new const string BaseViewName = "RadomeStatusTimeseriesView";
        public new const string ViewAliasName = "rst";

        public const int RADOME_FIELD_ID = 5;

        public SimpleRadomeStatusTimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Radome
        {
            get
            {
                return GetGuid( RADOME_FIELD_ID );
            }
        }
    }

    public class SimpleUInt64TimeseriesDataReader : SimpleTimeseriesDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  u64t.[Id], \r\n" +
            "  u64t.[EntityType], \r\n" +
            "  u64t.[RowVersion], \r\n" +
            "  u64t.[Catalog], \r\n" +
            "  u64t.[Name], \r\n" +
            "  u64t.[MaxRetention] \r\n" +
            "FROM [UInt64TimeseriesView] u64t \r\n";

        public new const string BaseViewName = "UInt64TimeseriesView";
        public new const string ViewAliasName = "u64t";

        public SimpleUInt64TimeseriesDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleTimeseriesCatalogDataReader : SimpleTimeseriesCatalogElementDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  tc.[Id], \r\n" +
            "  tc.[EntityType], \r\n" +
            "  tc.[RowVersion], \r\n" +
            "  tc.[Catalog], \r\n" +
            "  tc.[Name] \r\n" +
            "FROM [TimeseriesCatalogView] tc \r\n";

        public new const string BaseViewName = "TimeseriesCatalogView";
        public new const string ViewAliasName = "tc";

        public SimpleTimeseriesCatalogDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleTimeseriesInfoDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  ti.[Id], \r\n" +
            "  ti.[RowVersion], \r\n" +
            "  ti.[FirstTimestamp], \r\n" +
            "  ti.[LastTimestamp], \r\n" +
            "  ti.[Count] \r\n" +
            "FROM [TimeseriesInfoView] ti \r\n";

        public const string BaseViewName = "TimeseriesInfoView";
        public const string ViewAliasName = "ti";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int FIRSTTIMESTAMP_FIELD_ID = 2;
        public const int LASTTIMESTAMP_FIELD_ID = 3;
        public const int COUNT_FIELD_ID = 4;

        public SimpleTimeseriesInfoDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public DateTime? FirstTimestamp
        {
            get
            {
                var v = GetNullableInt64( FIRSTTIMESTAMP_FIELD_ID );
                if( v is long value )
                {
                    return new DateTime( value , DateTimeKind.Utc );
                }
                return null;
            }
        }
        public DateTime? LastTimestamp
        {
            get
            {
                var v = GetNullableInt64( LASTTIMESTAMP_FIELD_ID );
                if( v is long value )
                {
                    return new DateTime( value , DateTimeKind.Utc );
                }
                return null;
            }
        }
        public long Count
        {
            get
            {
                return GetInt64( COUNT_FIELD_ID );
            }
        }
    }

    public class SimpleTimeSpanTimeseriesValueDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  tstv.[Id], \r\n" +
            "  tstv.[RowVersion], \r\n" +
            "  tstv.[Timeseries], \r\n" +
            "  tstv.[Timestamp], \r\n" +
            "  tstv.[Value] \r\n" +
            "FROM [TimeSpanTimeseriesValueView] tstv \r\n";

        public const string BaseViewName = "TimeSpanTimeseriesValueView";
        public const string ViewAliasName = "tstv";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TIMESERIES_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int VALUE_FIELD_ID = 4;

        public SimpleTimeSpanTimeseriesValueDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public TimeSpan? Value
        {
            get
            {
                var v = GetNullableInt64( VALUE_FIELD_ID );
                if( v is long value )
                {
                    return new TimeSpan( value );
                }
                return null;
            }
        }
    }

    public class SimpleTrackableItemTrackLinkDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  titl.[Id], \r\n" +
            "  titl.[RowVersion], \r\n" +
            "  titl.[Item], \r\n" +
            "  titl.[Track], \r\n" +
            "  titl.[Start], \r\n" +
            "  titl.[End] \r\n" +
            "FROM [TrackableItemTrackLinkView] titl \r\n";

        public const string BaseViewName = "TrackableItemTrackLinkView";
        public const string ViewAliasName = "titl";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int ITEM_FIELD_ID = 2;
        public const int TRACK_FIELD_ID = 3;
        public const int START_FIELD_ID = 4;
        public const int END_FIELD_ID = 5;

        public SimpleTrackableItemTrackLinkDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Item
        {
            get
            {
                return GetGuid( ITEM_FIELD_ID );
            }
        }
        public Guid Track
        {
            get
            {
                return GetGuid( TRACK_FIELD_ID );
            }
        }
        public DateTime Start
        {
            get
            {
                return new DateTime( GetInt64( START_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public DateTime? End
        {
            get
            {
                var v = GetNullableInt64( END_FIELD_ID );
                if( v is long value )
                {
                    return new DateTime( value , DateTimeKind.Utc );
                }
                return null;
            }
        }
    }

    public class SimpleTrackBaseDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  tb.[Id], \r\n" +
            "  tb.[EntityType], \r\n" +
            "  tb.[RowVersion], \r\n" +
            "  tb.[Tracker], \r\n" +
            "  tb.[TrackNumber], \r\n" +
            "  tb.[Timestamp] \r\n" +
            "FROM [TrackBaseView] tb \r\n";

        public const string BaseViewName = "TrackBaseView";
        public const string ViewAliasName = "tb";

        public const int ID_FIELD_ID = 0;
        public const int ENTITYTYPE_FIELD_ID = 1;
        public const int ROWVERSION_FIELD_ID = 2;
        public const int TRACKER_FIELD_ID = 3;
        public const int TRACKNUMBER_FIELD_ID = 4;
        public const int TIMESTAMP_FIELD_ID = 5;

        public SimpleTrackBaseDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public Types.Kind EntityType
        {
            get
            {
                return GetEnum<Types.Kind>( ENTITYTYPE_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Tracker
        {
            get
            {
                return GetGuid( TRACKER_FIELD_ID );
            }
        }
        public long TrackNumber
        {
            get
            {
                return GetInt64( TRACKNUMBER_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
    }

    public class SimpleTrackDataReader : SimpleTrackBaseDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  t.[Id], \r\n" +
            "  t.[EntityType], \r\n" +
            "  t.[RowVersion], \r\n" +
            "  t.[Tracker], \r\n" +
            "  t.[TrackNumber], \r\n" +
            "  t.[Timestamp] \r\n" +
            "FROM [TrackView] t \r\n";

        public new const string BaseViewName = "TrackView";
        public new const string ViewAliasName = "t";

        public SimpleTrackDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleTrack3DDataReader : SimpleTrackBaseDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  t3d.[Id], \r\n" +
            "  t3d.[EntityType], \r\n" +
            "  t3d.[RowVersion], \r\n" +
            "  t3d.[Tracker], \r\n" +
            "  t3d.[TrackNumber], \r\n" +
            "  t3d.[Timestamp] \r\n" +
            "FROM [Track3DView] t3d \r\n";

        public new const string BaseViewName = "Track3DView";
        public new const string ViewAliasName = "t3d";

        public SimpleTrack3DDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

    }

    public class SimpleTrackerFilterParametersDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  tfp.[Id], \r\n" +
            "  tfp.[RowVersion], \r\n" +
            "  tfp.[Tracker], \r\n" +
            "  tfp.[Name] \r\n" +
            "FROM [TrackerFilterParametersView] tfp \r\n";

        public const string BaseViewName = "TrackerFilterParametersView";
        public const string ViewAliasName = "tfp";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TRACKER_FIELD_ID = 2;
        public const int NAME_FIELD_ID = 3;

        public SimpleTrackerFilterParametersDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Tracker
        {
            get
            {
                return GetGuid( TRACKER_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
    }

    public class SimpleTrackerFilterParametersConfigurationDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  tfpc.[Id], \r\n" +
            "  tfpc.[RowVersion], \r\n" +
            "  tfpc.[Parameters], \r\n" +
            "  tfpc.[Timestamp], \r\n" +
            "  tfpc.[UseNaivePredictor], \r\n" +
            "  tfpc.[NumberOfPoints], \r\n" +
            "  tfpc.[WindowSize], \r\n" +
            "  tfpc.[StabilizeCount], \r\n" +
            "  tfpc.[MaxBadPoints], \r\n" +
            "  tfpc.[ModelType], \r\n" +
            "  tfpc.[SigmaR], \r\n" +
            "  tfpc.[SigmaAcc], \r\n" +
            "  tfpc.[TauVel], \r\n" +
            "  tfpc.[TauAcc], \r\n" +
            "  tfpc.[DeltaRMin], \r\n" +
            "  tfpc.[DeltaVMax], \r\n" +
            "  tfpc.[DeltaAMax] \r\n" +
            "FROM [TrackerFilterParametersConfigurationView] tfpc \r\n";

        public const string BaseViewName = "TrackerFilterParametersConfigurationView";
        public const string ViewAliasName = "tfpc";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int PARAMETERS_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int USENAIVEPREDICTOR_FIELD_ID = 4;
        public const int NUMBEROFPOINTS_FIELD_ID = 5;
        public const int WINDOWSIZE_FIELD_ID = 6;
        public const int STABILIZECOUNT_FIELD_ID = 7;
        public const int MAXBADPOINTS_FIELD_ID = 8;
        public const int MODELTYPE_FIELD_ID = 9;
        public const int SIGMAR_FIELD_ID = 10;
        public const int SIGMAACC_FIELD_ID = 11;
        public const int TAUVEL_FIELD_ID = 12;
        public const int TAUACC_FIELD_ID = 13;
        public const int DELTARMIN_FIELD_ID = 14;
        public const int DELTAVMAX_FIELD_ID = 15;
        public const int DELTAAMAX_FIELD_ID = 16;

        public SimpleTrackerFilterParametersConfigurationDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Parameters
        {
            get
            {
                return GetGuid( PARAMETERS_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public bool UseNaivePredictor
        {
            get
            {
                return GetBoolean( USENAIVEPREDICTOR_FIELD_ID );
            }
        }
        public int NumberOfPoints
        {
            get
            {
                return GetInt32( NUMBEROFPOINTS_FIELD_ID );
            }
        }
        public int WindowSize
        {
            get
            {
                return GetInt32( WINDOWSIZE_FIELD_ID );
            }
        }
        public int StabilizeCount
        {
            get
            {
                return GetInt32( STABILIZECOUNT_FIELD_ID );
            }
        }
        public int MaxBadPoints
        {
            get
            {
                return GetInt32( MAXBADPOINTS_FIELD_ID );
            }
        }
        public Types.TrackerFilterModelType ModelType
        {
            get
            {
                return GetEnum<Types.TrackerFilterModelType>( MODELTYPE_FIELD_ID );
            }
        }
        public double SigmaR
        {
            get
            {
                return GetDouble( SIGMAR_FIELD_ID );
            }
        }
        public double SigmaAcc
        {
            get
            {
                return GetDouble( SIGMAACC_FIELD_ID );
            }
        }
        public double TauVel
        {
            get
            {
                return GetDouble( TAUVEL_FIELD_ID );
            }
        }
        public double TauAcc
        {
            get
            {
                return GetDouble( TAUACC_FIELD_ID );
            }
        }
        public double DeltaRMin
        {
            get
            {
                return GetDouble( DELTARMIN_FIELD_ID );
            }
        }
        public double DeltaVMax
        {
            get
            {
                return GetDouble( DELTAVMAX_FIELD_ID );
            }
        }
        public double DeltaAMax
        {
            get
            {
                return GetDouble( DELTAAMAX_FIELD_ID );
            }
        }
    }

    public class SimpleTrackInfoDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  ti.[Id], \r\n" +
            "  ti.[RowVersion], \r\n" +
            "  ti.[FirstTimestamp], \r\n" +
            "  ti.[LastTimestamp], \r\n" +
            "  ti.[Count], \r\n" +
            "  ti.[NorthWestLatitude], \r\n" +
            "  ti.[NorthWestLongitude], \r\n" +
            "  ti.[SouthEastLatitude], \r\n" +
            "  ti.[SouthEastLongitude] \r\n" +
            "FROM [TrackInfoView] ti \r\n";

        public const string BaseViewName = "TrackInfoView";
        public const string ViewAliasName = "ti";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int FIRSTTIMESTAMP_FIELD_ID = 2;
        public const int LASTTIMESTAMP_FIELD_ID = 3;
        public const int COUNT_FIELD_ID = 4;
        public const int NORTHWESTLATITUDE_FIELD_ID = 5;
        public const int NORTHWESTLONGITUDE_FIELD_ID = 6;
        public const int SOUTHEASTLATITUDE_FIELD_ID = 7;
        public const int SOUTHEASTLONGITUDE_FIELD_ID = 8;

        public SimpleTrackInfoDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public DateTime? FirstTimestamp
        {
            get
            {
                var v = GetNullableInt64( FIRSTTIMESTAMP_FIELD_ID );
                if( v is long value )
                {
                    return new DateTime( value , DateTimeKind.Utc );
                }
                return null;
            }
        }
        public DateTime? LastTimestamp
        {
            get
            {
                var v = GetNullableInt64( LASTTIMESTAMP_FIELD_ID );
                if( v is long value )
                {
                    return new DateTime( value , DateTimeKind.Utc );
                }
                return null;
            }
        }
        public long Count
        {
            get
            {
                return GetInt64( COUNT_FIELD_ID );
            }
        }
        public double? NorthWestLatitude
        {
            get
            {
                return GetNullableDouble( NORTHWESTLATITUDE_FIELD_ID );
            }
        }
        public double? NorthWestLongitude
        {
            get
            {
                return GetNullableDouble( NORTHWESTLONGITUDE_FIELD_ID );
            }
        }
        public double? SouthEastLatitude
        {
            get
            {
                return GetNullableDouble( SOUTHEASTLATITUDE_FIELD_ID );
            }
        }
        public double? SouthEastLongitude
        {
            get
            {
                return GetNullableDouble( SOUTHEASTLONGITUDE_FIELD_ID );
            }
        }
    }

    public class SimpleTrackingServiceOptionsDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  tso.[Id], \r\n" +
            "  tso.[RowVersion], \r\n" +
            "  tso.[Timestamp], \r\n" +
            "  tso.[TimerInterval], \r\n" +
            "  tso.[MaxAgeOfCurrentTrackValue], \r\n" +
            "  tso.[FalseThreshold], \r\n" +
            "  tso.[DistanceThreshold], \r\n" +
            "  tso.[DistanceUnmergeThreshold], \r\n" +
            "  tso.[UnmergeLatency], \r\n" +
            "  tso.[KalmanFiltering], \r\n" +
            "  tso.[MaxCourseDeviation], \r\n" +
            "  tso.[MaxSpeedDeviation], \r\n" +
            "  tso.[MinimumSpeedThreshold] \r\n" +
            "FROM [TrackingServiceOptionsView] tso \r\n";

        public const string BaseViewName = "TrackingServiceOptionsView";
        public const string ViewAliasName = "tso";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TIMESTAMP_FIELD_ID = 2;
        public const int TIMERINTERVAL_FIELD_ID = 3;
        public const int MAXAGEOFCURRENTTRACKVALUE_FIELD_ID = 4;
        public const int FALSETHRESHOLD_FIELD_ID = 5;
        public const int DISTANCETHRESHOLD_FIELD_ID = 6;
        public const int DISTANCEUNMERGETHRESHOLD_FIELD_ID = 7;
        public const int UNMERGELATENCY_FIELD_ID = 8;
        public const int KALMANFILTERING_FIELD_ID = 9;
        public const int MAXCOURSEDEVIATION_FIELD_ID = 10;
        public const int MAXSPEEDDEVIATION_FIELD_ID = 11;
        public const int MINIMUMSPEEDTHRESHOLD_FIELD_ID = 12;

        public SimpleTrackingServiceOptionsDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public TimeSpan TimerInterval
        {
            get
            {
                return new TimeSpan( GetInt64( TIMERINTERVAL_FIELD_ID ) );
            }
        }
        public TimeSpan MaxAgeOfCurrentTrackValue
        {
            get
            {
                return new TimeSpan( GetInt64( MAXAGEOFCURRENTTRACKVALUE_FIELD_ID ) );
            }
        }
        public double FalseThreshold
        {
            get
            {
                return GetDouble( FALSETHRESHOLD_FIELD_ID );
            }
        }
        public double DistanceThreshold
        {
            get
            {
                return GetDouble( DISTANCETHRESHOLD_FIELD_ID );
            }
        }
        public double DistanceUnmergeThreshold
        {
            get
            {
                return GetDouble( DISTANCEUNMERGETHRESHOLD_FIELD_ID );
            }
        }
        public long UnmergeLatency
        {
            get
            {
                return GetInt64( UNMERGELATENCY_FIELD_ID );
            }
        }
        public bool KalmanFiltering
        {
            get
            {
                return GetBoolean( KALMANFILTERING_FIELD_ID );
            }
        }
        public double MaxCourseDeviation
        {
            get
            {
                return GetDouble( MAXCOURSEDEVIATION_FIELD_ID );
            }
        }
        public double MaxSpeedDeviation
        {
            get
            {
                return GetDouble( MAXSPEEDDEVIATION_FIELD_ID );
            }
        }
        public double MinimumSpeedThreshold
        {
            get
            {
                return GetDouble( MINIMUMSPEEDTHRESHOLD_FIELD_ID );
            }
        }
    }

    public class SimpleTrackLinkDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  tl.[Id], \r\n" +
            "  tl.[RowVersion], \r\n" +
            "  tl.[Primary], \r\n" +
            "  tl.[Secondary], \r\n" +
            "  tl.[Start], \r\n" +
            "  tl.[End] \r\n" +
            "FROM [TrackLinkView] tl \r\n";

        public const string BaseViewName = "TrackLinkView";
        public const string ViewAliasName = "tl";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int PRIMARY_FIELD_ID = 2;
        public const int SECONDARY_FIELD_ID = 3;
        public const int START_FIELD_ID = 4;
        public const int END_FIELD_ID = 5;

        public SimpleTrackLinkDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Primary
        {
            get
            {
                return GetGuid( PRIMARY_FIELD_ID );
            }
        }
        public Guid Secondary
        {
            get
            {
                return GetGuid( SECONDARY_FIELD_ID );
            }
        }
        public DateTime Start
        {
            get
            {
                return new DateTime( GetInt64( START_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public DateTime? End
        {
            get
            {
                var v = GetNullableInt64( END_FIELD_ID );
                if( v is long value )
                {
                    return new DateTime( value , DateTimeKind.Utc );
                }
                return null;
            }
        }
    }

    public class SimpleTrackValueDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  tv.[Id], \r\n" +
            "  tv.[RowVersion], \r\n" +
            "  tv.[Track], \r\n" +
            "  tv.[Timestamp], \r\n" +
            "  tv.[Flags], \r\n" +
            "  tv.[Status], \r\n" +
            "  tv.[Latitude], \r\n" +
            "  tv.[Longitude], \r\n" +
            "  tv.[Speed], \r\n" +
            "  tv.[Course], \r\n" +
            "  tv.[Heading] \r\n" +
            "FROM [TrackValueView] tv \r\n";

        public const string BaseViewName = "TrackValueView";
        public const string ViewAliasName = "tv";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TRACK_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int FLAGS_FIELD_ID = 4;
        public const int STATUS_FIELD_ID = 5;
        public const int LATITUDE_FIELD_ID = 6;
        public const int LONGITUDE_FIELD_ID = 7;
        public const int SPEED_FIELD_ID = 8;
        public const int COURSE_FIELD_ID = 9;
        public const int HEADING_FIELD_ID = 10;

        public SimpleTrackValueDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Track
        {
            get
            {
                return GetGuid( TRACK_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Types.TrackFlags Flags
        {
            get
            {
                return GetEnum<Types.TrackFlags>( FLAGS_FIELD_ID );
            }
        }
        public Types.TrackStatus Status
        {
            get
            {
                return GetEnum<Types.TrackStatus>( STATUS_FIELD_ID );
            }
        }
        public double Latitude
        {
            get
            {
                return GetDouble( LATITUDE_FIELD_ID );
            }
        }
        public double Longitude
        {
            get
            {
                return GetDouble( LONGITUDE_FIELD_ID );
            }
        }
        public double Speed
        {
            get
            {
                return GetDouble( SPEED_FIELD_ID );
            }
        }
        public double Course
        {
            get
            {
                return GetDouble( COURSE_FIELD_ID );
            }
        }
        public double Heading
        {
            get
            {
                return GetDouble( HEADING_FIELD_ID );
            }
        }
    }

    public class SimpleTrackValue3DDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  tv3d.[Id], \r\n" +
            "  tv3d.[RowVersion], \r\n" +
            "  tv3d.[Track], \r\n" +
            "  tv3d.[Timestamp], \r\n" +
            "  tv3d.[Flags], \r\n" +
            "  tv3d.[Status], \r\n" +
            "  tv3d.[Latitude], \r\n" +
            "  tv3d.[Longitude], \r\n" +
            "  tv3d.[Altitude], \r\n" +
            "  tv3d.[Speed], \r\n" +
            "  tv3d.[Course], \r\n" +
            "  tv3d.[RateOfClimb] \r\n" +
            "FROM [TrackValue3DView] tv3d \r\n";

        public const string BaseViewName = "TrackValue3DView";
        public const string ViewAliasName = "tv3d";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TRACK_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int FLAGS_FIELD_ID = 4;
        public const int STATUS_FIELD_ID = 5;
        public const int LATITUDE_FIELD_ID = 6;
        public const int LONGITUDE_FIELD_ID = 7;
        public const int ALTITUDE_FIELD_ID = 8;
        public const int SPEED_FIELD_ID = 9;
        public const int COURSE_FIELD_ID = 10;
        public const int RATEOFCLIMB_FIELD_ID = 11;

        public SimpleTrackValue3DDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Track
        {
            get
            {
                return GetGuid( TRACK_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Types.TrackFlags3D Flags
        {
            get
            {
                return GetEnum<Types.TrackFlags3D>( FLAGS_FIELD_ID );
            }
        }
        public uint Status
        {
            get
            {
                return GetUInt32( STATUS_FIELD_ID );
            }
        }
        public double Latitude
        {
            get
            {
                return GetDouble( LATITUDE_FIELD_ID );
            }
        }
        public double Longitude
        {
            get
            {
                return GetDouble( LONGITUDE_FIELD_ID );
            }
        }
        public double Altitude
        {
            get
            {
                return GetDouble( ALTITUDE_FIELD_ID );
            }
        }
        public double Speed
        {
            get
            {
                return GetDouble( SPEED_FIELD_ID );
            }
        }
        public double Course
        {
            get
            {
                return GetDouble( COURSE_FIELD_ID );
            }
        }
        public double RateOfClimb
        {
            get
            {
                return GetDouble( RATEOFCLIMB_FIELD_ID );
            }
        }
    }

    public class SimpleUInt16TimeseriesValueDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  u16tv.[Id], \r\n" +
            "  u16tv.[RowVersion], \r\n" +
            "  u16tv.[Timeseries], \r\n" +
            "  u16tv.[Timestamp], \r\n" +
            "  u16tv.[Value] \r\n" +
            "FROM [UInt16TimeseriesValueView] u16tv \r\n";

        public const string BaseViewName = "UInt16TimeseriesValueView";
        public const string ViewAliasName = "u16tv";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TIMESERIES_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int VALUE_FIELD_ID = 4;

        public SimpleUInt16TimeseriesValueDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public ushort? Value
        {
            get
            {
                return GetNullableUInt16( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleUInt32TimeseriesValueDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  u32tv.[Id], \r\n" +
            "  u32tv.[RowVersion], \r\n" +
            "  u32tv.[Timeseries], \r\n" +
            "  u32tv.[Timestamp], \r\n" +
            "  u32tv.[Value] \r\n" +
            "FROM [UInt32TimeseriesValueView] u32tv \r\n";

        public const string BaseViewName = "UInt32TimeseriesValueView";
        public const string ViewAliasName = "u32tv";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TIMESERIES_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int VALUE_FIELD_ID = 4;

        public SimpleUInt32TimeseriesValueDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public uint? Value
        {
            get
            {
                return GetNullableUInt32( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleUInt64TimeseriesValueDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  u64tv.[Id], \r\n" +
            "  u64tv.[RowVersion], \r\n" +
            "  u64tv.[Timeseries], \r\n" +
            "  u64tv.[Timestamp], \r\n" +
            "  u64tv.[Value] \r\n" +
            "FROM [UInt64TimeseriesValueView] u64tv \r\n";

        public const string BaseViewName = "UInt64TimeseriesValueView";
        public const string ViewAliasName = "u64tv";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TIMESERIES_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int VALUE_FIELD_ID = 4;

        public SimpleUInt64TimeseriesValueDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Timeseries
        {
            get
            {
                return GetGuid( TIMESERIES_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public long? Value
        {
            get
            {
                return GetNullableInt64( VALUE_FIELD_ID );
            }
        }
    }

    public class SimpleVehicleTypeDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  vt.[Id], \r\n" +
            "  vt.[RowVersion], \r\n" +
            "  vt.[Name] \r\n" +
            "FROM [VehicleTypeView] vt \r\n";

        public const string BaseViewName = "VehicleTypeView";
        public const string ViewAliasName = "vt";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int NAME_FIELD_ID = 2;

        public SimpleVehicleTypeDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
    }

    public class SimpleVesselTypeDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  vt.[Id], \r\n" +
            "  vt.[RowVersion], \r\n" +
            "  vt.[Name], \r\n" +
            "  vt.[Code] \r\n" +
            "FROM [VesselTypeView] vt \r\n";

        public const string BaseViewName = "VesselTypeView";
        public const string ViewAliasName = "vt";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int NAME_FIELD_ID = 2;
        public const int CODE_FIELD_ID = 3;

        public SimpleVesselTypeDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
        public int Code
        {
            get
            {
                return GetInt32( CODE_FIELD_ID );
            }
        }
    }

    public class SimpleViewDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  v.[Id], \r\n" +
            "  v.[RowVersion], \r\n" +
            "  v.[Name], \r\n" +
            "  v.[LatitudeTimeseries], \r\n" +
            "  v.[LongitudeTimeseries], \r\n" +
            "  v.[ZoomLevelTimeseries] \r\n" +
            "FROM [ViewView] v \r\n";

        public const string BaseViewName = "ViewView";
        public const string ViewAliasName = "v";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int NAME_FIELD_ID = 2;
        public const int LATITUDETIMESERIES_FIELD_ID = 3;
        public const int LONGITUDETIMESERIES_FIELD_ID = 4;
        public const int ZOOMLEVELTIMESERIES_FIELD_ID = 5;

        public SimpleViewDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
        public Guid LatitudeTimeseries
        {
            get
            {
                return GetGuid( LATITUDETIMESERIES_FIELD_ID );
            }
        }
        public Guid LongitudeTimeseries
        {
            get
            {
                return GetGuid( LONGITUDETIMESERIES_FIELD_ID );
            }
        }
        public Guid ZoomLevelTimeseries
        {
            get
            {
                return GetGuid( ZOOMLEVELTIMESERIES_FIELD_ID );
            }
        }
    }

    public class SimpleViewCameraLinkDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  vcl.[Id], \r\n" +
            "  vcl.[RowVersion], \r\n" +
            "  vcl.[View], \r\n" +
            "  vcl.[Camera], \r\n" +
            "  vcl.[Start], \r\n" +
            "  vcl.[End] \r\n" +
            "FROM [ViewCameraLinkView] vcl \r\n";

        public const string BaseViewName = "ViewCameraLinkView";
        public const string ViewAliasName = "vcl";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int VIEW_FIELD_ID = 2;
        public const int CAMERA_FIELD_ID = 3;
        public const int START_FIELD_ID = 4;
        public const int END_FIELD_ID = 5;

        public SimpleViewCameraLinkDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid View
        {
            get
            {
                return GetGuid( VIEW_FIELD_ID );
            }
        }
        public Guid Camera
        {
            get
            {
                return GetGuid( CAMERA_FIELD_ID );
            }
        }
        public DateTime Start
        {
            get
            {
                return new DateTime( GetInt64( START_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public DateTime? End
        {
            get
            {
                var v = GetNullableInt64( END_FIELD_ID );
                if( v is long value )
                {
                    return new DateTime( value , DateTimeKind.Utc );
                }
                return null;
            }
        }
    }

    public class SimpleViewTrackerLinkDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  vtl.[Id], \r\n" +
            "  vtl.[RowVersion], \r\n" +
            "  vtl.[View], \r\n" +
            "  vtl.[Tracker], \r\n" +
            "  vtl.[Start], \r\n" +
            "  vtl.[End] \r\n" +
            "FROM [ViewTrackerLinkView] vtl \r\n";

        public const string BaseViewName = "ViewTrackerLinkView";
        public const string ViewAliasName = "vtl";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int VIEW_FIELD_ID = 2;
        public const int TRACKER_FIELD_ID = 3;
        public const int START_FIELD_ID = 4;
        public const int END_FIELD_ID = 5;

        public SimpleViewTrackerLinkDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid View
        {
            get
            {
                return GetGuid( VIEW_FIELD_ID );
            }
        }
        public Guid Tracker
        {
            get
            {
                return GetGuid( TRACKER_FIELD_ID );
            }
        }
        public DateTime Start
        {
            get
            {
                return new DateTime( GetInt64( START_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public DateTime? End
        {
            get
            {
                var v = GetNullableInt64( END_FIELD_ID );
                if( v is long value )
                {
                    return new DateTime( value , DateTimeKind.Utc );
                }
                return null;
            }
        }
    }

    public class SimpleWeatherStationCommandDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  wsc.[Id], \r\n" +
            "  wsc.[RowVersion], \r\n" +
            "  wsc.[WeatherStation], \r\n" +
            "  wsc.[Timestamp], \r\n" +
            "  wsc.[DeviceCommandSourceType], \r\n" +
            "  wsc.[DeviceCommandSourceId], \r\n" +
            "  wsc.[Reply] \r\n" +
            "FROM [WeatherStationCommandView] wsc \r\n";

        public const string BaseViewName = "WeatherStationCommandView";
        public const string ViewAliasName = "wsc";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int WEATHERSTATION_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int DEVICECOMMANDSOURCETYPE_FIELD_ID = 4;
        public const int DEVICECOMMANDSOURCEID_FIELD_ID = 5;
        public const int REPLY_FIELD_ID = 6;

        public SimpleWeatherStationCommandDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid WeatherStation
        {
            get
            {
                return GetGuid( WEATHERSTATION_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Types.DeviceCommandSourceType DeviceCommandSourceType
        {
            get
            {
                return GetEnum<Types.DeviceCommandSourceType>( DEVICECOMMANDSOURCETYPE_FIELD_ID );
            }
        }
        public Guid DeviceCommandSourceId
        {
            get
            {
                return GetGuid( DEVICECOMMANDSOURCEID_FIELD_ID );
            }
        }
        public Guid Reply
        {
            get
            {
                return GetGuid( REPLY_FIELD_ID );
            }
        }
    }

    public class SimpleWeatherStationCommandReplyDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  wscr.[Id], \r\n" +
            "  wscr.[RowVersion], \r\n" +
            "  wscr.[WeatherStation], \r\n" +
            "  wscr.[Timestamp], \r\n" +
            "  wscr.[Command], \r\n" +
            "  wscr.[Status], \r\n" +
            "  wscr.[Message] \r\n" +
            "FROM [WeatherStationCommandReplyView] wscr \r\n";

        public const string BaseViewName = "WeatherStationCommandReplyView";
        public const string ViewAliasName = "wscr";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int WEATHERSTATION_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int COMMAND_FIELD_ID = 4;
        public const int STATUS_FIELD_ID = 5;
        public const int MESSAGE_FIELD_ID = 6;

        public SimpleWeatherStationCommandReplyDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid WeatherStation
        {
            get
            {
                return GetGuid( WEATHERSTATION_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public Guid Command
        {
            get
            {
                return GetGuid( COMMAND_FIELD_ID );
            }
        }
        public Types.DeviceCommandReplyStatus Status
        {
            get
            {
                return GetEnum<Types.DeviceCommandReplyStatus>( STATUS_FIELD_ID );
            }
        }
        public string Message
        {
            get
            {
                return GetString( MESSAGE_FIELD_ID );
            }
        }
    }

    public class SimpleWeatherStationConfigurationDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  wsc.[Id], \r\n" +
            "  wsc.[RowVersion], \r\n" +
            "  wsc.[WeatherStation], \r\n" +
            "  wsc.[Timestamp], \r\n" +
            "  wsc.[NoDataTimeOut], \r\n" +
            "  wsc.[SendInterval], \r\n" +
            "  wsc.[Latitude], \r\n" +
            "  wsc.[Longitude], \r\n" +
            "  wsc.[GyroOffset], \r\n" +
            "  wsc.[EnableAveraging], \r\n" +
            "  wsc.[AveragingInterval] \r\n" +
            "FROM [WeatherStationConfigurationView] wsc \r\n";

        public const string BaseViewName = "WeatherStationConfigurationView";
        public const string ViewAliasName = "wsc";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int WEATHERSTATION_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;
        public const int NODATATIMEOUT_FIELD_ID = 4;
        public const int SENDINTERVAL_FIELD_ID = 5;
        public const int LATITUDE_FIELD_ID = 6;
        public const int LONGITUDE_FIELD_ID = 7;
        public const int GYROOFFSET_FIELD_ID = 8;
        public const int ENABLEAVERAGING_FIELD_ID = 9;
        public const int AVERAGINGINTERVAL_FIELD_ID = 10;

        public SimpleWeatherStationConfigurationDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid WeatherStation
        {
            get
            {
                return GetGuid( WEATHERSTATION_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public TimeSpan NoDataTimeOut
        {
            get
            {
                return new TimeSpan( GetInt64( NODATATIMEOUT_FIELD_ID ) );
            }
        }
        public TimeSpan SendInterval
        {
            get
            {
                return new TimeSpan( GetInt64( SENDINTERVAL_FIELD_ID ) );
            }
        }
        public double Latitude
        {
            get
            {
                return GetDouble( LATITUDE_FIELD_ID );
            }
        }
        public double Longitude
        {
            get
            {
                return GetDouble( LONGITUDE_FIELD_ID );
            }
        }
        public double GyroOffset
        {
            get
            {
                return GetDouble( GYROOFFSET_FIELD_ID );
            }
        }
        public bool EnableAveraging
        {
            get
            {
                return GetBoolean( ENABLEAVERAGING_FIELD_ID );
            }
        }
        public TimeSpan AveragingInterval
        {
            get
            {
                return new TimeSpan( GetInt64( AVERAGINGINTERVAL_FIELD_ID ) );
            }
        }
    }

    public class SimpleZoneDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  z.[Id], \r\n" +
            "  z.[EntityType], \r\n" +
            "  z.[RowVersion], \r\n" +
            "  z.[Name], \r\n" +
            "  z.[Longitude], \r\n" +
            "  z.[Latitude], \r\n" +
            "  z.[AlarmType], \r\n" +
            "  z.[AlarmTime], \r\n" +
            "  z.[RadarTrackMinimumLifetime], \r\n" +
            "  z.[Speed], \r\n" +
            "  z.[StrokeColor], \r\n" +
            "  z.[FillColor] \r\n" +
            "FROM [ZoneView] z \r\n";

        public const string BaseViewName = "ZoneView";
        public const string ViewAliasName = "z";

        public const int ID_FIELD_ID = 0;
        public const int ENTITYTYPE_FIELD_ID = 1;
        public const int ROWVERSION_FIELD_ID = 2;
        public const int NAME_FIELD_ID = 3;
        public const int LONGITUDE_FIELD_ID = 4;
        public const int LATITUDE_FIELD_ID = 5;
        public const int ALARMTYPE_FIELD_ID = 6;
        public const int ALARMTIME_FIELD_ID = 7;
        public const int RADARTRACKMINIMUMLIFETIME_FIELD_ID = 8;
        public const int SPEED_FIELD_ID = 9;
        public const int STROKECOLOR_FIELD_ID = 10;
        public const int FILLCOLOR_FIELD_ID = 11;

        public SimpleZoneDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public Types.Kind EntityType
        {
            get
            {
                return GetEnum<Types.Kind>( ENTITYTYPE_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public string Name
        {
            get
            {
                return GetString( NAME_FIELD_ID );
            }
        }
        public double Longitude
        {
            get
            {
                return GetDouble( LONGITUDE_FIELD_ID );
            }
        }
        public double Latitude
        {
            get
            {
                return GetDouble( LATITUDE_FIELD_ID );
            }
        }
        public Types.ZoneAlarmType AlarmType
        {
            get
            {
                return GetEnum<Types.ZoneAlarmType>( ALARMTYPE_FIELD_ID );
            }
        }
        public TimeSpan AlarmTime
        {
            get
            {
                return new TimeSpan( GetInt64( ALARMTIME_FIELD_ID ) );
            }
        }
        public TimeSpan RadarTrackMinimumLifetime
        {
            get
            {
                return new TimeSpan( GetInt64( RADARTRACKMINIMUMLIFETIME_FIELD_ID ) );
            }
        }
        public double Speed
        {
            get
            {
                return GetDouble( SPEED_FIELD_ID );
            }
        }
        public uint StrokeColor
        {
            get
            {
                return GetUInt32( STROKECOLOR_FIELD_ID );
            }
        }
        public uint FillColor
        {
            get
            {
                return GetUInt32( FILLCOLOR_FIELD_ID );
            }
        }
    }

    public class SimpleCircularZoneDataReader : SimpleZoneDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  cz.[Id], \r\n" +
            "  cz.[EntityType], \r\n" +
            "  cz.[RowVersion], \r\n" +
            "  cz.[Name], \r\n" +
            "  cz.[Longitude], \r\n" +
            "  cz.[Latitude], \r\n" +
            "  cz.[AlarmType], \r\n" +
            "  cz.[AlarmTime], \r\n" +
            "  cz.[RadarTrackMinimumLifetime], \r\n" +
            "  cz.[Speed], \r\n" +
            "  cz.[StrokeColor], \r\n" +
            "  cz.[FillColor], \r\n" +
            "  cz.[Radius] \r\n" +
            "FROM [CircularZoneView] cz \r\n";

        public new const string BaseViewName = "CircularZoneView";
        public new const string ViewAliasName = "cz";

        public const int RADIUS_FIELD_ID = 11;

        public SimpleCircularZoneDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public double Radius
        {
            get
            {
                return GetDouble( RADIUS_FIELD_ID );
            }
        }
    }

    public class SimplePolygonZoneDataReader : SimpleZoneDataReader
    {
        public new const string BaseQuery = "SELECT \r\n" +
            "  pz.[Id], \r\n" +
            "  pz.[EntityType], \r\n" +
            "  pz.[RowVersion], \r\n" +
            "  pz.[Name], \r\n" +
            "  pz.[Longitude], \r\n" +
            "  pz.[Latitude], \r\n" +
            "  pz.[AlarmType], \r\n" +
            "  pz.[AlarmTime], \r\n" +
            "  pz.[RadarTrackMinimumLifetime], \r\n" +
            "  pz.[Speed], \r\n" +
            "  pz.[StrokeColor], \r\n" +
            "  pz.[FillColor], \r\n" +
            "  pz.[Polygon] \r\n" +
            "FROM [PolygonZoneView] pz \r\n";

        public new const string BaseViewName = "PolygonZoneView";
        public new const string ViewAliasName = "pz";

        public const int POLYGON_FIELD_ID = 11;

        public SimplePolygonZoneDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public byte[] Polygon
        {
            get
            {
                return GetBytes( POLYGON_FIELD_ID );
            }
        }
    }

    public class SimpleZoneExceptionsDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  ze.[Id], \r\n" +
            "  ze.[RowVersion], \r\n" +
            "  ze.[Zone], \r\n" +
            "  ze.[Timestamp] \r\n" +
            "FROM [ZoneExceptionsView] ze \r\n";

        public const string BaseViewName = "ZoneExceptionsView";
        public const string ViewAliasName = "ze";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int ZONE_FIELD_ID = 2;
        public const int TIMESTAMP_FIELD_ID = 3;

        public SimpleZoneExceptionsDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Zone
        {
            get
            {
                return GetGuid( ZONE_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
    }

    public class SimpleZoneExceptionsVesselLinkDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  zevl.[Id], \r\n" +
            "  zevl.[RowVersion], \r\n" +
            "  zevl.[ZoneExceptions], \r\n" +
            "  zevl.[Vessel] \r\n" +
            "FROM [ZoneExceptionsVesselLinkView] zevl \r\n";

        public const string BaseViewName = "ZoneExceptionsVesselLinkView";
        public const string ViewAliasName = "zevl";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int ZONEEXCEPTIONS_FIELD_ID = 2;
        public const int VESSEL_FIELD_ID = 3;

        public SimpleZoneExceptionsVesselLinkDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid ZoneExceptions
        {
            get
            {
                return GetGuid( ZONEEXCEPTIONS_FIELD_ID );
            }
        }
        public Guid Vessel
        {
            get
            {
                return GetGuid( VESSEL_FIELD_ID );
            }
        }
    }

    public class SimpleZoneTrackAlarmDataReader : DataReaderWrapper
    {
        public const string BaseQuery = "SELECT \r\n" +
            "  zta.[Id], \r\n" +
            "  zta.[RowVersion], \r\n" +
            "  zta.[Track], \r\n" +
            "  zta.[Zone], \r\n" +
            "  zta.[RadarTrack], \r\n" +
            "  zta.[Timestamp], \r\n" +
            "  zta.[Latitude], \r\n" +
            "  zta.[Longitude], \r\n" +
            "  zta.[Speed], \r\n" +
            "  zta.[Course], \r\n" +
            "  zta.[Heading], \r\n" +
            "  zta.[EnterLatitude], \r\n" +
            "  zta.[EnterLongitude], \r\n" +
            "  zta.[LeaveLatitude], \r\n" +
            "  zta.[LeaveLongitude] \r\n" +
            "FROM [ZoneTrackAlarmView] zta \r\n";

        public const string BaseViewName = "ZoneTrackAlarmView";
        public const string ViewAliasName = "zta";

        public const int ID_FIELD_ID = 0;
        public const int ROWVERSION_FIELD_ID = 1;
        public const int TRACK_FIELD_ID = 2;
        public const int ZONE_FIELD_ID = 3;
        public const int RADARTRACK_FIELD_ID = 4;
        public const int TIMESTAMP_FIELD_ID = 5;
        public const int LATITUDE_FIELD_ID = 6;
        public const int LONGITUDE_FIELD_ID = 7;
        public const int SPEED_FIELD_ID = 8;
        public const int COURSE_FIELD_ID = 9;
        public const int HEADING_FIELD_ID = 10;
        public const int ENTERLATITUDE_FIELD_ID = 11;
        public const int ENTERLONGITUDE_FIELD_ID = 12;
        public const int LEAVELATITUDE_FIELD_ID = 13;
        public const int LEAVELONGITUDE_FIELD_ID = 14;

        public SimpleZoneTrackAlarmDataReader( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )
            : base(loggerFactory, sqlDataReader, ownsReader )
        {
        }

        public Guid Id
        {
            get
            {
                return GetGuid( ID_FIELD_ID );
            }
        }
        public long RowVersion
        {
            get
            {
                return GetInt64( ROWVERSION_FIELD_ID );
            }
        }
        public Guid Track
        {
            get
            {
                return GetGuid( TRACK_FIELD_ID );
            }
        }
        public Guid Zone
        {
            get
            {
                return GetGuid( ZONE_FIELD_ID );
            }
        }
        public Guid RadarTrack
        {
            get
            {
                return GetGuid( RADARTRACK_FIELD_ID );
            }
        }
        public DateTime Timestamp
        {
            get
            {
                return new DateTime( GetInt64( TIMESTAMP_FIELD_ID ), DateTimeKind.Utc );
            }
        }
        public double Latitude
        {
            get
            {
                return GetDouble( LATITUDE_FIELD_ID );
            }
        }
        public double Longitude
        {
            get
            {
                return GetDouble( LONGITUDE_FIELD_ID );
            }
        }
        public double Speed
        {
            get
            {
                return GetDouble( SPEED_FIELD_ID );
            }
        }
        public double? Course
        {
            get
            {
                return GetNullableDouble( COURSE_FIELD_ID );
            }
        }
        public double? Heading
        {
            get
            {
                return GetNullableDouble( HEADING_FIELD_ID );
            }
        }
        public double EnterLatitude
        {
            get
            {
                return GetDouble( ENTERLATITUDE_FIELD_ID );
            }
        }
        public double EnterLongitude
        {
            get
            {
                return GetDouble( ENTERLONGITUDE_FIELD_ID );
            }
        }
        public double? LeaveLatitude
        {
            get
            {
                return GetNullableDouble( LEAVELATITUDE_FIELD_ID );
            }
        }
        public double? LeaveLongitude
        {
            get
            {
                return GetNullableDouble( LEAVELONGITUDE_FIELD_ID );
            }
        }
    }

}
