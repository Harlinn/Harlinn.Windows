using System;
using System.IO;

using Harlinn.Common.Core.Net;
using Harlinn.Common.Core.Net.Data;
using Harlinn.Common.Core.Net.IO;
namespace Barrelman.Data.Types
{
    public class AircraftTypeObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        string name_ = string.Empty;
        public AircraftTypeObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AircraftType;
        }

        public override BaseData<Kind> Create()
        {
            return new AircraftTypeObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AircraftType )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AisDeviceCommandObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid aisDevice_;
        DateTime timestamp_;
        Types.DeviceCommandSourceType deviceCommandSourceType_ = Types.DeviceCommandSourceType.Unknown;
        Guid deviceCommandSourceId_;
        Guid? reply_;
        public AisDeviceCommandObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisDeviceCommand;
        }

        public override BaseData<Kind> Create()
        {
            return new AisDeviceCommandObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisDeviceCommand )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid AisDevice
        {
            get => aisDevice_;
            set
            {
                if( aisDevice_ != value )
                {
                    aisDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.DeviceCommandSourceType DeviceCommandSourceType
        {
            get => deviceCommandSourceType_;
            set
            {
                if( deviceCommandSourceType_ != value )
                {
                    deviceCommandSourceType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid DeviceCommandSourceId
        {
            get => deviceCommandSourceId_;
            set
            {
                if( deviceCommandSourceId_ != value )
                {
                    deviceCommandSourceId_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid? Reply
        {
            get => reply_;
            set
            {
                if( reply_ != value )
                {
                    reply_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AisDeviceCommandReplyObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid aisDevice_;
        DateTime timestamp_;
        Guid command_;
        Types.DeviceCommandReplyStatus status_ = Types.DeviceCommandReplyStatus.Unknown;
        string message_ = string.Empty;
        public AisDeviceCommandReplyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisDeviceCommandReply;
        }

        public override BaseData<Kind> Create()
        {
            return new AisDeviceCommandReplyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisDeviceCommandReply )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid AisDevice
        {
            get => aisDevice_;
            set
            {
                if( aisDevice_ != value )
                {
                    aisDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Command
        {
            get => command_;
            set
            {
                if( command_ != value )
                {
                    command_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.DeviceCommandReplyStatus Status
        {
            get => status_;
            set
            {
                if( status_ != value )
                {
                    status_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Message
        {
            get => message_;
            set
            {
                if( message_ != value )
                {
                    message_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AisDeviceConfigurationObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid aisDevice_;
        DateTime timestamp_;
        string userName_ = string.Empty;
        string password_ = string.Empty;
        double latitude_ = 0.0;
        double longitude_ = 0.0;
        string aisProviderLoginURL_ = string.Empty;
        string comPort_ = string.Empty;
        int baudRate_ = 0;
        bool filterByArea_ = false;
        double upperLeftCornerLatitude_ = 0.0;
        double upperLeftCornerLongitude_ = 0.0;
        double bottomRightCornerLatitude_ = 0.0;
        double bottomRightCornerLongitude_ = 0.0;
        string aisProviderIPAddress_ = string.Empty;
        int aisProviderPort_ = 0;
        bool useLogin_ = false;
        int aisProviderLoginPort_ = 0;
        bool canSendAISMessage_ = false;
        string textMessageHeader_ = string.Empty;
        string urls_ = string.Empty;
        int udpPort_ = 0;
        Types.AisDeviceConnectionType connectionType_ = Types.AisDeviceConnectionType.Unknown;
        bool enableRefreshAidToNavigationIn30sec_ = false;
        bool enableAidToNavigationFromFile_ = false;
        string aidToNavigationHeader_ = string.Empty;
        bool sendingMMSI_ = false;
        int sourceUpdateRate_ = 0;
        bool enableRefreshStayingStillTargetIn30sec_ = false;
        string excludeSendAisBaseStation_ = string.Empty;
        string excludeSendAisA_ = string.Empty;
        bool enableSendBaseStationAlarms_ = false;
        string aisWebConfig_ = string.Empty;
        bool storeReceivedSentences_ = false;
        bool storeSentMessages_ = false;
        bool storeUnsentMessages_ = false;
        public AisDeviceConfigurationObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisDeviceConfiguration;
        }

        public override BaseData<Kind> Create()
        {
            return new AisDeviceConfigurationObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisDeviceConfiguration )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid AisDevice
        {
            get => aisDevice_;
            set
            {
                if( aisDevice_ != value )
                {
                    aisDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string UserName
        {
            get => userName_;
            set
            {
                if( userName_ != value )
                {
                    userName_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Password
        {
            get => password_;
            set
            {
                if( password_ != value )
                {
                    password_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Latitude
        {
            get => latitude_;
            set
            {
                if( latitude_ != value )
                {
                    latitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Longitude
        {
            get => longitude_;
            set
            {
                if( longitude_ != value )
                {
                    longitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string AisProviderLoginURL
        {
            get => aisProviderLoginURL_;
            set
            {
                if( aisProviderLoginURL_ != value )
                {
                    aisProviderLoginURL_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string ComPort
        {
            get => comPort_;
            set
            {
                if( comPort_ != value )
                {
                    comPort_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int BaudRate
        {
            get => baudRate_;
            set
            {
                if( baudRate_ != value )
                {
                    baudRate_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool FilterByArea
        {
            get => filterByArea_;
            set
            {
                if( filterByArea_ != value )
                {
                    filterByArea_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double UpperLeftCornerLatitude
        {
            get => upperLeftCornerLatitude_;
            set
            {
                if( upperLeftCornerLatitude_ != value )
                {
                    upperLeftCornerLatitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double UpperLeftCornerLongitude
        {
            get => upperLeftCornerLongitude_;
            set
            {
                if( upperLeftCornerLongitude_ != value )
                {
                    upperLeftCornerLongitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double BottomRightCornerLatitude
        {
            get => bottomRightCornerLatitude_;
            set
            {
                if( bottomRightCornerLatitude_ != value )
                {
                    bottomRightCornerLatitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double BottomRightCornerLongitude
        {
            get => bottomRightCornerLongitude_;
            set
            {
                if( bottomRightCornerLongitude_ != value )
                {
                    bottomRightCornerLongitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string AisProviderIPAddress
        {
            get => aisProviderIPAddress_;
            set
            {
                if( aisProviderIPAddress_ != value )
                {
                    aisProviderIPAddress_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int AisProviderPort
        {
            get => aisProviderPort_;
            set
            {
                if( aisProviderPort_ != value )
                {
                    aisProviderPort_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool UseLogin
        {
            get => useLogin_;
            set
            {
                if( useLogin_ != value )
                {
                    useLogin_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int AisProviderLoginPort
        {
            get => aisProviderLoginPort_;
            set
            {
                if( aisProviderLoginPort_ != value )
                {
                    aisProviderLoginPort_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool CanSendAISMessage
        {
            get => canSendAISMessage_;
            set
            {
                if( canSendAISMessage_ != value )
                {
                    canSendAISMessage_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string TextMessageHeader
        {
            get => textMessageHeader_;
            set
            {
                if( textMessageHeader_ != value )
                {
                    textMessageHeader_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Urls
        {
            get => urls_;
            set
            {
                if( urls_ != value )
                {
                    urls_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int UdpPort
        {
            get => udpPort_;
            set
            {
                if( udpPort_ != value )
                {
                    udpPort_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.AisDeviceConnectionType ConnectionType
        {
            get => connectionType_;
            set
            {
                if( connectionType_ != value )
                {
                    connectionType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool EnableRefreshAidToNavigationIn30sec
        {
            get => enableRefreshAidToNavigationIn30sec_;
            set
            {
                if( enableRefreshAidToNavigationIn30sec_ != value )
                {
                    enableRefreshAidToNavigationIn30sec_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool EnableAidToNavigationFromFile
        {
            get => enableAidToNavigationFromFile_;
            set
            {
                if( enableAidToNavigationFromFile_ != value )
                {
                    enableAidToNavigationFromFile_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string AidToNavigationHeader
        {
            get => aidToNavigationHeader_;
            set
            {
                if( aidToNavigationHeader_ != value )
                {
                    aidToNavigationHeader_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool SendingMMSI
        {
            get => sendingMMSI_;
            set
            {
                if( sendingMMSI_ != value )
                {
                    sendingMMSI_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int SourceUpdateRate
        {
            get => sourceUpdateRate_;
            set
            {
                if( sourceUpdateRate_ != value )
                {
                    sourceUpdateRate_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool EnableRefreshStayingStillTargetIn30sec
        {
            get => enableRefreshStayingStillTargetIn30sec_;
            set
            {
                if( enableRefreshStayingStillTargetIn30sec_ != value )
                {
                    enableRefreshStayingStillTargetIn30sec_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string ExcludeSendAisBaseStation
        {
            get => excludeSendAisBaseStation_;
            set
            {
                if( excludeSendAisBaseStation_ != value )
                {
                    excludeSendAisBaseStation_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string ExcludeSendAisA
        {
            get => excludeSendAisA_;
            set
            {
                if( excludeSendAisA_ != value )
                {
                    excludeSendAisA_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool EnableSendBaseStationAlarms
        {
            get => enableSendBaseStationAlarms_;
            set
            {
                if( enableSendBaseStationAlarms_ != value )
                {
                    enableSendBaseStationAlarms_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string AisWebConfig
        {
            get => aisWebConfig_;
            set
            {
                if( aisWebConfig_ != value )
                {
                    aisWebConfig_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool StoreReceivedSentences
        {
            get => storeReceivedSentences_;
            set
            {
                if( storeReceivedSentences_ != value )
                {
                    storeReceivedSentences_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool StoreSentMessages
        {
            get => storeSentMessages_;
            set
            {
                if( storeSentMessages_ != value )
                {
                    storeSentMessages_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool StoreUnsentMessages
        {
            get => storeUnsentMessages_;
            set
            {
                if( storeUnsentMessages_ != value )
                {
                    storeUnsentMessages_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AisDeviceRawMessageObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid aisDevice_;
        DateTime timestamp_;
        bool isSent_ = false;
        string message_ = string.Empty;
        public AisDeviceRawMessageObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisDeviceRawMessage;
        }

        public override BaseData<Kind> Create()
        {
            return new AisDeviceRawMessageObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisDeviceRawMessage )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid AisDevice
        {
            get => aisDevice_;
            set
            {
                if( aisDevice_ != value )
                {
                    aisDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool IsSent
        {
            get => isSent_;
            set
            {
                if( isSent_ != value )
                {
                    isSent_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Message
        {
            get => message_;
            set
            {
                if( message_ != value )
                {
                    message_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AisDeviceRawSentenceObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid aisDevice_;
        DateTime timestamp_;
        string sentence_ = string.Empty;
        public AisDeviceRawSentenceObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisDeviceRawSentence;
        }

        public override BaseData<Kind> Create()
        {
            return new AisDeviceRawSentenceObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisDeviceRawSentence )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid AisDevice
        {
            get => aisDevice_;
            set
            {
                if( aisDevice_ != value )
                {
                    aisDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Sentence
        {
            get => sentence_;
            set
            {
                if( sentence_ != value )
                {
                    sentence_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public abstract class AisMessageObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid aisDevice_;
        DateTime receivedTimestamp_;
        long messageSequenceNumber_ = 0;
        int repeat_ = 0;
        Guid mmsi_;
        protected AisMessageObject ( )
        {
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisMessage )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid AisDevice
        {
            get => aisDevice_;
            set
            {
                if( aisDevice_ != value )
                {
                    aisDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime ReceivedTimestamp
        {
            get => receivedTimestamp_;
            set
            {
                if( receivedTimestamp_ != value )
                {
                    receivedTimestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public long MessageSequenceNumber
        {
            get => messageSequenceNumber_;
            set
            {
                if( messageSequenceNumber_ != value )
                {
                    messageSequenceNumber_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Repeat
        {
            get => repeat_;
            set
            {
                if( repeat_ != value )
                {
                    repeat_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Mmsi
        {
            get => mmsi_;
            set
            {
                if( mmsi_ != value )
                {
                    mmsi_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AidToNavigationReportMessageObject : AisMessageObject
    {
        Types.NavigationalAidType navigationalAidType_ = Types.NavigationalAidType.NotSpecified;
        string name_ = string.Empty;
        Types.PositionAccuracy positionAccuracy_ = Types.PositionAccuracy.Low;
        double longitude_ = 0.0;
        double latitude_ = 0.0;
        int dimensionToBow_ = 0;
        int dimensionToStern_ = 0;
        int dimensionToPort_ = 0;
        int dimensionToStarboard_ = 0;
        Types.PositionFixType positionFixType_ = Types.PositionFixType.Undefined1;
        int timestamp_ = 0;
        bool offPosition_ = false;
        int regionalReserved_ = 0;
        Types.Raim raim_ = Types.Raim.NotInUse;
        bool virtualAid_ = false;
        bool assigned_ = false;
        int spare_ = 0;
        string nameExtension_ = string.Empty;
        public AidToNavigationReportMessageObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AidToNavigationReportMessage;
        }

        public override BaseData<Kind> Create()
        {
            return new AidToNavigationReportMessageObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AidToNavigationReportMessage )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Types.NavigationalAidType NavigationalAidType
        {
            get => navigationalAidType_;
            set
            {
                if( navigationalAidType_ != value )
                {
                    navigationalAidType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.PositionAccuracy PositionAccuracy
        {
            get => positionAccuracy_;
            set
            {
                if( positionAccuracy_ != value )
                {
                    positionAccuracy_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Longitude
        {
            get => longitude_;
            set
            {
                if( longitude_ != value )
                {
                    longitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Latitude
        {
            get => latitude_;
            set
            {
                if( latitude_ != value )
                {
                    latitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int DimensionToBow
        {
            get => dimensionToBow_;
            set
            {
                if( dimensionToBow_ != value )
                {
                    dimensionToBow_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int DimensionToStern
        {
            get => dimensionToStern_;
            set
            {
                if( dimensionToStern_ != value )
                {
                    dimensionToStern_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int DimensionToPort
        {
            get => dimensionToPort_;
            set
            {
                if( dimensionToPort_ != value )
                {
                    dimensionToPort_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int DimensionToStarboard
        {
            get => dimensionToStarboard_;
            set
            {
                if( dimensionToStarboard_ != value )
                {
                    dimensionToStarboard_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.PositionFixType PositionFixType
        {
            get => positionFixType_;
            set
            {
                if( positionFixType_ != value )
                {
                    positionFixType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool OffPosition
        {
            get => offPosition_;
            set
            {
                if( offPosition_ != value )
                {
                    offPosition_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int RegionalReserved
        {
            get => regionalReserved_;
            set
            {
                if( regionalReserved_ != value )
                {
                    regionalReserved_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.Raim Raim
        {
            get => raim_;
            set
            {
                if( raim_ != value )
                {
                    raim_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool VirtualAid
        {
            get => virtualAid_;
            set
            {
                if( virtualAid_ != value )
                {
                    virtualAid_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Assigned
        {
            get => assigned_;
            set
            {
                if( assigned_ != value )
                {
                    assigned_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Spare
        {
            get => spare_;
            set
            {
                if( spare_ != value )
                {
                    spare_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string NameExtension
        {
            get => nameExtension_;
            set
            {
                if( nameExtension_ != value )
                {
                    nameExtension_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AisAddressedSafetyRelatedMessageObject : AisMessageObject
    {
        int sequenceNumber_ = 0;
        Guid destinationMmsi_;
        bool retransmitFlag_ = false;
        int spare_ = 0;
        string text_ = string.Empty;
        public AisAddressedSafetyRelatedMessageObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisAddressedSafetyRelatedMessage;
        }

        public override BaseData<Kind> Create()
        {
            return new AisAddressedSafetyRelatedMessageObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisAddressedSafetyRelatedMessage )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public int SequenceNumber
        {
            get => sequenceNumber_;
            set
            {
                if( sequenceNumber_ != value )
                {
                    sequenceNumber_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid DestinationMmsi
        {
            get => destinationMmsi_;
            set
            {
                if( destinationMmsi_ != value )
                {
                    destinationMmsi_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool RetransmitFlag
        {
            get => retransmitFlag_;
            set
            {
                if( retransmitFlag_ != value )
                {
                    retransmitFlag_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Spare
        {
            get => spare_;
            set
            {
                if( spare_ != value )
                {
                    spare_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Text
        {
            get => text_;
            set
            {
                if( text_ != value )
                {
                    text_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AisBaseStationReportMessageObject : AisMessageObject
    {
        DateTime timestamp_;
        Types.PositionAccuracy positionAccuracy_ = Types.PositionAccuracy.Low;
        double longitude_ = 0.0;
        double latitude_ = 0.0;
        Types.PositionFixType positionFixType_ = Types.PositionFixType.Undefined1;
        int spare_ = 0;
        Types.Raim raim_ = Types.Raim.NotInUse;
        int radioStatus_ = 0;
        public AisBaseStationReportMessageObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisBaseStationReportMessage;
        }

        public override BaseData<Kind> Create()
        {
            return new AisBaseStationReportMessageObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisBaseStationReportMessage )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.PositionAccuracy PositionAccuracy
        {
            get => positionAccuracy_;
            set
            {
                if( positionAccuracy_ != value )
                {
                    positionAccuracy_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Longitude
        {
            get => longitude_;
            set
            {
                if( longitude_ != value )
                {
                    longitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Latitude
        {
            get => latitude_;
            set
            {
                if( latitude_ != value )
                {
                    latitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.PositionFixType PositionFixType
        {
            get => positionFixType_;
            set
            {
                if( positionFixType_ != value )
                {
                    positionFixType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Spare
        {
            get => spare_;
            set
            {
                if( spare_ != value )
                {
                    spare_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.Raim Raim
        {
            get => raim_;
            set
            {
                if( raim_ != value )
                {
                    raim_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int RadioStatus
        {
            get => radioStatus_;
            set
            {
                if( radioStatus_ != value )
                {
                    radioStatus_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AisBinaryAcknowledgeMessageObject : AisMessageObject
    {
        int spare_ = 0;
        int sequenceNumber1_ = 0;
        Guid mmsi1_;
        int? sequenceNumber2_;
        Guid? mmsi2_;
        int? sequenceNumber3_;
        Guid? mmsi3_;
        int? sequenceNumber4_;
        Guid? mmsi4_;
        public AisBinaryAcknowledgeMessageObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisBinaryAcknowledgeMessage;
        }

        public override BaseData<Kind> Create()
        {
            return new AisBinaryAcknowledgeMessageObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisBinaryAcknowledgeMessage )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public int Spare
        {
            get => spare_;
            set
            {
                if( spare_ != value )
                {
                    spare_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int SequenceNumber1
        {
            get => sequenceNumber1_;
            set
            {
                if( sequenceNumber1_ != value )
                {
                    sequenceNumber1_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Mmsi1
        {
            get => mmsi1_;
            set
            {
                if( mmsi1_ != value )
                {
                    mmsi1_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int? SequenceNumber2
        {
            get => sequenceNumber2_;
            set
            {
                if( sequenceNumber2_ != value )
                {
                    sequenceNumber2_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid? Mmsi2
        {
            get => mmsi2_;
            set
            {
                if( mmsi2_ != value )
                {
                    mmsi2_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int? SequenceNumber3
        {
            get => sequenceNumber3_;
            set
            {
                if( sequenceNumber3_ != value )
                {
                    sequenceNumber3_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid? Mmsi3
        {
            get => mmsi3_;
            set
            {
                if( mmsi3_ != value )
                {
                    mmsi3_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int? SequenceNumber4
        {
            get => sequenceNumber4_;
            set
            {
                if( sequenceNumber4_ != value )
                {
                    sequenceNumber4_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid? Mmsi4
        {
            get => mmsi4_;
            set
            {
                if( mmsi4_ != value )
                {
                    mmsi4_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AisBinaryAddressedMessageObject : AisMessageObject
    {
        int sequenceNumber_ = 0;
        Guid destinationMmsi_;
        bool retransmitFlag_ = false;
        int spare_ = 0;
        int designatedAreaCode_ = 0;
        int functionalId_ = 0;
        string data_ = string.Empty;
        public AisBinaryAddressedMessageObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisBinaryAddressedMessage;
        }

        public override BaseData<Kind> Create()
        {
            return new AisBinaryAddressedMessageObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisBinaryAddressedMessage )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public int SequenceNumber
        {
            get => sequenceNumber_;
            set
            {
                if( sequenceNumber_ != value )
                {
                    sequenceNumber_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid DestinationMmsi
        {
            get => destinationMmsi_;
            set
            {
                if( destinationMmsi_ != value )
                {
                    destinationMmsi_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool RetransmitFlag
        {
            get => retransmitFlag_;
            set
            {
                if( retransmitFlag_ != value )
                {
                    retransmitFlag_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Spare
        {
            get => spare_;
            set
            {
                if( spare_ != value )
                {
                    spare_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int DesignatedAreaCode
        {
            get => designatedAreaCode_;
            set
            {
                if( designatedAreaCode_ != value )
                {
                    designatedAreaCode_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int FunctionalId
        {
            get => functionalId_;
            set
            {
                if( functionalId_ != value )
                {
                    functionalId_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Data
        {
            get => data_;
            set
            {
                if( data_ != value )
                {
                    data_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AisBinaryBroadcastMessageObject : AisMessageObject
    {
        int spare_ = 0;
        int designatedAreaCode_ = 0;
        int functionalId_ = 0;
        string data_ = string.Empty;
        public AisBinaryBroadcastMessageObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisBinaryBroadcastMessage;
        }

        public override BaseData<Kind> Create()
        {
            return new AisBinaryBroadcastMessageObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisBinaryBroadcastMessage )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public int Spare
        {
            get => spare_;
            set
            {
                if( spare_ != value )
                {
                    spare_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int DesignatedAreaCode
        {
            get => designatedAreaCode_;
            set
            {
                if( designatedAreaCode_ != value )
                {
                    designatedAreaCode_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int FunctionalId
        {
            get => functionalId_;
            set
            {
                if( functionalId_ != value )
                {
                    functionalId_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Data
        {
            get => data_;
            set
            {
                if( data_ != value )
                {
                    data_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AisDataLinkManagementMessageObject : AisMessageObject
    {
        int spare_ = 0;
        int offset1_ = 0;
        int reservedSlots1_ = 0;
        int timeout1_ = 0;
        int increment1_ = 0;
        int? offset2_;
        int? reservedSlots2_;
        int? timeout2_;
        int? increment2_;
        int? offset3_;
        int? reservedSlots3_;
        int? timeout3_;
        int? increment3_;
        int? offset4_;
        int? reservedSlots4_;
        int? timeout4_;
        int? increment4_;
        public AisDataLinkManagementMessageObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisDataLinkManagementMessage;
        }

        public override BaseData<Kind> Create()
        {
            return new AisDataLinkManagementMessageObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisDataLinkManagementMessage )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public int Spare
        {
            get => spare_;
            set
            {
                if( spare_ != value )
                {
                    spare_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Offset1
        {
            get => offset1_;
            set
            {
                if( offset1_ != value )
                {
                    offset1_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int ReservedSlots1
        {
            get => reservedSlots1_;
            set
            {
                if( reservedSlots1_ != value )
                {
                    reservedSlots1_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Timeout1
        {
            get => timeout1_;
            set
            {
                if( timeout1_ != value )
                {
                    timeout1_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Increment1
        {
            get => increment1_;
            set
            {
                if( increment1_ != value )
                {
                    increment1_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int? Offset2
        {
            get => offset2_;
            set
            {
                if( offset2_ != value )
                {
                    offset2_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int? ReservedSlots2
        {
            get => reservedSlots2_;
            set
            {
                if( reservedSlots2_ != value )
                {
                    reservedSlots2_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int? Timeout2
        {
            get => timeout2_;
            set
            {
                if( timeout2_ != value )
                {
                    timeout2_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int? Increment2
        {
            get => increment2_;
            set
            {
                if( increment2_ != value )
                {
                    increment2_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int? Offset3
        {
            get => offset3_;
            set
            {
                if( offset3_ != value )
                {
                    offset3_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int? ReservedSlots3
        {
            get => reservedSlots3_;
            set
            {
                if( reservedSlots3_ != value )
                {
                    reservedSlots3_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int? Timeout3
        {
            get => timeout3_;
            set
            {
                if( timeout3_ != value )
                {
                    timeout3_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int? Increment3
        {
            get => increment3_;
            set
            {
                if( increment3_ != value )
                {
                    increment3_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int? Offset4
        {
            get => offset4_;
            set
            {
                if( offset4_ != value )
                {
                    offset4_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int? ReservedSlots4
        {
            get => reservedSlots4_;
            set
            {
                if( reservedSlots4_ != value )
                {
                    reservedSlots4_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int? Timeout4
        {
            get => timeout4_;
            set
            {
                if( timeout4_ != value )
                {
                    timeout4_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int? Increment4
        {
            get => increment4_;
            set
            {
                if( increment4_ != value )
                {
                    increment4_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AisExtendedClassBCsPositionReportMessageObject : AisMessageObject
    {
        int reserved_ = 0;
        double speedOverGround_ = 0.0;
        Types.PositionAccuracy positionAccuracy_ = Types.PositionAccuracy.Low;
        double longitude_ = 0.0;
        double latitude_ = 0.0;
        double courseOverGround_ = 0.0;
        int? trueHeading_;
        int timestamp_ = 0;
        int regionalReserved_ = 0;
        Guid name_;
        Types.ShipType shipType_ = Types.ShipType.NotAvailable;
        int dimensionToBow_ = 0;
        int dimensionToStern_ = 0;
        int dimensionToPort_ = 0;
        int dimensionToStarboard_ = 0;
        Types.PositionFixType positionFixType_ = Types.PositionFixType.Undefined1;
        Types.Raim raim_ = Types.Raim.NotInUse;
        bool dataTerminalReady_ = false;
        bool assigned_ = false;
        int spare_ = 0;
        public AisExtendedClassBCsPositionReportMessageObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisExtendedClassBCsPositionReportMessage;
        }

        public override BaseData<Kind> Create()
        {
            return new AisExtendedClassBCsPositionReportMessageObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisExtendedClassBCsPositionReportMessage )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public int Reserved
        {
            get => reserved_;
            set
            {
                if( reserved_ != value )
                {
                    reserved_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double SpeedOverGround
        {
            get => speedOverGround_;
            set
            {
                if( speedOverGround_ != value )
                {
                    speedOverGround_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.PositionAccuracy PositionAccuracy
        {
            get => positionAccuracy_;
            set
            {
                if( positionAccuracy_ != value )
                {
                    positionAccuracy_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Longitude
        {
            get => longitude_;
            set
            {
                if( longitude_ != value )
                {
                    longitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Latitude
        {
            get => latitude_;
            set
            {
                if( latitude_ != value )
                {
                    latitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double CourseOverGround
        {
            get => courseOverGround_;
            set
            {
                if( courseOverGround_ != value )
                {
                    courseOverGround_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int? TrueHeading
        {
            get => trueHeading_;
            set
            {
                if( trueHeading_ != value )
                {
                    trueHeading_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int RegionalReserved
        {
            get => regionalReserved_;
            set
            {
                if( regionalReserved_ != value )
                {
                    regionalReserved_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.ShipType ShipType
        {
            get => shipType_;
            set
            {
                if( shipType_ != value )
                {
                    shipType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int DimensionToBow
        {
            get => dimensionToBow_;
            set
            {
                if( dimensionToBow_ != value )
                {
                    dimensionToBow_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int DimensionToStern
        {
            get => dimensionToStern_;
            set
            {
                if( dimensionToStern_ != value )
                {
                    dimensionToStern_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int DimensionToPort
        {
            get => dimensionToPort_;
            set
            {
                if( dimensionToPort_ != value )
                {
                    dimensionToPort_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int DimensionToStarboard
        {
            get => dimensionToStarboard_;
            set
            {
                if( dimensionToStarboard_ != value )
                {
                    dimensionToStarboard_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.PositionFixType PositionFixType
        {
            get => positionFixType_;
            set
            {
                if( positionFixType_ != value )
                {
                    positionFixType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.Raim Raim
        {
            get => raim_;
            set
            {
                if( raim_ != value )
                {
                    raim_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool DataTerminalReady
        {
            get => dataTerminalReady_;
            set
            {
                if( dataTerminalReady_ != value )
                {
                    dataTerminalReady_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Assigned
        {
            get => assigned_;
            set
            {
                if( assigned_ != value )
                {
                    assigned_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Spare
        {
            get => spare_;
            set
            {
                if( spare_ != value )
                {
                    spare_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AisInterrogationMessageObject : AisMessageObject
    {
        Guid interrogatedMmsi_;
        Types.AisMessageType firstMessageType_ = Types.AisMessageType.PositionReportClassA;
        int firstSlotOffset_ = 0;
        Types.AisMessageType? secondMessageType_;
        int? secondSlotOffset_;
        Guid? secondStationInterrogationMmsi_;
        Types.AisMessageType? secondStationFirstMessageType_;
        int? secondStationFirstSlotOffset_;
        public AisInterrogationMessageObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisInterrogationMessage;
        }

        public override BaseData<Kind> Create()
        {
            return new AisInterrogationMessageObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisInterrogationMessage )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid InterrogatedMmsi
        {
            get => interrogatedMmsi_;
            set
            {
                if( interrogatedMmsi_ != value )
                {
                    interrogatedMmsi_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.AisMessageType FirstMessageType
        {
            get => firstMessageType_;
            set
            {
                if( firstMessageType_ != value )
                {
                    firstMessageType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int FirstSlotOffset
        {
            get => firstSlotOffset_;
            set
            {
                if( firstSlotOffset_ != value )
                {
                    firstSlotOffset_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.AisMessageType? SecondMessageType
        {
            get => secondMessageType_;
            set
            {
                if( secondMessageType_ != value )
                {
                    secondMessageType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int? SecondSlotOffset
        {
            get => secondSlotOffset_;
            set
            {
                if( secondSlotOffset_ != value )
                {
                    secondSlotOffset_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid? SecondStationInterrogationMmsi
        {
            get => secondStationInterrogationMmsi_;
            set
            {
                if( secondStationInterrogationMmsi_ != value )
                {
                    secondStationInterrogationMmsi_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.AisMessageType? SecondStationFirstMessageType
        {
            get => secondStationFirstMessageType_;
            set
            {
                if( secondStationFirstMessageType_ != value )
                {
                    secondStationFirstMessageType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int? SecondStationFirstSlotOffset
        {
            get => secondStationFirstSlotOffset_;
            set
            {
                if( secondStationFirstSlotOffset_ != value )
                {
                    secondStationFirstSlotOffset_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public abstract class AisPositionReportClassAMessageBaseObject : AisMessageObject
    {
        Types.NavigationStatus navigationStatus_ = Types.NavigationStatus.UnderWayUsingEngine;
        int? rateOfTurn_;
        double speedOverGround_ = 0.0;
        Types.PositionAccuracy positionAccuracy_ = Types.PositionAccuracy.Low;
        double longitude_ = 0.0;
        double latitude_ = 0.0;
        double courseOverGround_ = 0.0;
        int? trueHeading_;
        int timestamp_ = 0;
        Types.ManeuverIndicator maneuverIndicator_ = Types.ManeuverIndicator.NotAvailable;
        int spare_ = 0;
        Types.Raim raim_ = Types.Raim.NotInUse;
        int radioStatus_ = 0;
        protected AisPositionReportClassAMessageBaseObject ( )
        {
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisPositionReportClassAMessageBase )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Types.NavigationStatus NavigationStatus
        {
            get => navigationStatus_;
            set
            {
                if( navigationStatus_ != value )
                {
                    navigationStatus_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int? RateOfTurn
        {
            get => rateOfTurn_;
            set
            {
                if( rateOfTurn_ != value )
                {
                    rateOfTurn_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double SpeedOverGround
        {
            get => speedOverGround_;
            set
            {
                if( speedOverGround_ != value )
                {
                    speedOverGround_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.PositionAccuracy PositionAccuracy
        {
            get => positionAccuracy_;
            set
            {
                if( positionAccuracy_ != value )
                {
                    positionAccuracy_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Longitude
        {
            get => longitude_;
            set
            {
                if( longitude_ != value )
                {
                    longitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Latitude
        {
            get => latitude_;
            set
            {
                if( latitude_ != value )
                {
                    latitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double CourseOverGround
        {
            get => courseOverGround_;
            set
            {
                if( courseOverGround_ != value )
                {
                    courseOverGround_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int? TrueHeading
        {
            get => trueHeading_;
            set
            {
                if( trueHeading_ != value )
                {
                    trueHeading_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.ManeuverIndicator ManeuverIndicator
        {
            get => maneuverIndicator_;
            set
            {
                if( maneuverIndicator_ != value )
                {
                    maneuverIndicator_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Spare
        {
            get => spare_;
            set
            {
                if( spare_ != value )
                {
                    spare_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.Raim Raim
        {
            get => raim_;
            set
            {
                if( raim_ != value )
                {
                    raim_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int RadioStatus
        {
            get => radioStatus_;
            set
            {
                if( radioStatus_ != value )
                {
                    radioStatus_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AisPositionReportClassAAssignedScheduleMessageObject : AisPositionReportClassAMessageBaseObject
    {
        public AisPositionReportClassAAssignedScheduleMessageObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisPositionReportClassAAssignedScheduleMessage;
        }

        public override BaseData<Kind> Create()
        {
            return new AisPositionReportClassAAssignedScheduleMessageObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisPositionReportClassAAssignedScheduleMessage )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class AisPositionReportClassAMessageObject : AisPositionReportClassAMessageBaseObject
    {
        public AisPositionReportClassAMessageObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisPositionReportClassAMessage;
        }

        public override BaseData<Kind> Create()
        {
            return new AisPositionReportClassAMessageObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisPositionReportClassAMessage )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class AisPositionReportClassAResponseToInterrogationMessageObject : AisPositionReportClassAMessageBaseObject
    {
        public AisPositionReportClassAResponseToInterrogationMessageObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisPositionReportClassAResponseToInterrogationMessage;
        }

        public override BaseData<Kind> Create()
        {
            return new AisPositionReportClassAResponseToInterrogationMessageObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisPositionReportClassAResponseToInterrogationMessage )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class AisPositionReportForLongRangeApplicationsMessageObject : AisMessageObject
    {
        Types.PositionAccuracy positionAccuracy_ = Types.PositionAccuracy.Low;
        Types.Raim raim_ = Types.Raim.NotInUse;
        Types.NavigationStatus navigationStatus_ = Types.NavigationStatus.UnderWayUsingEngine;
        double longitude_ = 0.0;
        double latitude_ = 0.0;
        double speedOverGround_ = 0.0;
        double courseOverGround_ = 0.0;
        Types.GnssPositionStatus gnssPositionStatus_ = Types.GnssPositionStatus.CurrentGnssPosition;
        int spare_ = 0;
        public AisPositionReportForLongRangeApplicationsMessageObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisPositionReportForLongRangeApplicationsMessage;
        }

        public override BaseData<Kind> Create()
        {
            return new AisPositionReportForLongRangeApplicationsMessageObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisPositionReportForLongRangeApplicationsMessage )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Types.PositionAccuracy PositionAccuracy
        {
            get => positionAccuracy_;
            set
            {
                if( positionAccuracy_ != value )
                {
                    positionAccuracy_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.Raim Raim
        {
            get => raim_;
            set
            {
                if( raim_ != value )
                {
                    raim_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.NavigationStatus NavigationStatus
        {
            get => navigationStatus_;
            set
            {
                if( navigationStatus_ != value )
                {
                    navigationStatus_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Longitude
        {
            get => longitude_;
            set
            {
                if( longitude_ != value )
                {
                    longitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Latitude
        {
            get => latitude_;
            set
            {
                if( latitude_ != value )
                {
                    latitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double SpeedOverGround
        {
            get => speedOverGround_;
            set
            {
                if( speedOverGround_ != value )
                {
                    speedOverGround_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double CourseOverGround
        {
            get => courseOverGround_;
            set
            {
                if( courseOverGround_ != value )
                {
                    courseOverGround_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.GnssPositionStatus GnssPositionStatus
        {
            get => gnssPositionStatus_;
            set
            {
                if( gnssPositionStatus_ != value )
                {
                    gnssPositionStatus_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Spare
        {
            get => spare_;
            set
            {
                if( spare_ != value )
                {
                    spare_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AisSafetyRelatedAcknowledgmentMessageObject : AisMessageObject
    {
        int spare_ = 0;
        int sequenceNumber1_ = 0;
        Guid mmsi1_;
        int? sequenceNumber2_;
        Guid? mmsi2_;
        int? sequenceNumber3_;
        Guid? mmsi3_;
        int? sequenceNumber4_;
        Guid? mmsi4_;
        public AisSafetyRelatedAcknowledgmentMessageObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisSafetyRelatedAcknowledgmentMessage;
        }

        public override BaseData<Kind> Create()
        {
            return new AisSafetyRelatedAcknowledgmentMessageObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisSafetyRelatedAcknowledgmentMessage )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public int Spare
        {
            get => spare_;
            set
            {
                if( spare_ != value )
                {
                    spare_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int SequenceNumber1
        {
            get => sequenceNumber1_;
            set
            {
                if( sequenceNumber1_ != value )
                {
                    sequenceNumber1_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Mmsi1
        {
            get => mmsi1_;
            set
            {
                if( mmsi1_ != value )
                {
                    mmsi1_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int? SequenceNumber2
        {
            get => sequenceNumber2_;
            set
            {
                if( sequenceNumber2_ != value )
                {
                    sequenceNumber2_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid? Mmsi2
        {
            get => mmsi2_;
            set
            {
                if( mmsi2_ != value )
                {
                    mmsi2_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int? SequenceNumber3
        {
            get => sequenceNumber3_;
            set
            {
                if( sequenceNumber3_ != value )
                {
                    sequenceNumber3_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid? Mmsi3
        {
            get => mmsi3_;
            set
            {
                if( mmsi3_ != value )
                {
                    mmsi3_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int? SequenceNumber4
        {
            get => sequenceNumber4_;
            set
            {
                if( sequenceNumber4_ != value )
                {
                    sequenceNumber4_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid? Mmsi4
        {
            get => mmsi4_;
            set
            {
                if( mmsi4_ != value )
                {
                    mmsi4_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AisStandardClassBCsPositionReportMessageObject : AisMessageObject
    {
        int reserved_ = 0;
        double speedOverGround_ = 0.0;
        Types.PositionAccuracy positionAccuracy_ = Types.PositionAccuracy.Low;
        double longitude_ = 0.0;
        double latitude_ = 0.0;
        double courseOverGround_ = 0.0;
        int? trueHeading_;
        int timestamp_ = 0;
        int regionalReserved_ = 0;
        bool isCsUnit_ = false;
        bool hasDisplay_ = false;
        bool hasDscCapability_ = false;
        bool band_ = false;
        bool canAcceptMessage22_ = false;
        bool assigned_ = false;
        Types.Raim raim_ = Types.Raim.NotInUse;
        int radioStatus_ = 0;
        public AisStandardClassBCsPositionReportMessageObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisStandardClassBCsPositionReportMessage;
        }

        public override BaseData<Kind> Create()
        {
            return new AisStandardClassBCsPositionReportMessageObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisStandardClassBCsPositionReportMessage )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public int Reserved
        {
            get => reserved_;
            set
            {
                if( reserved_ != value )
                {
                    reserved_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double SpeedOverGround
        {
            get => speedOverGround_;
            set
            {
                if( speedOverGround_ != value )
                {
                    speedOverGround_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.PositionAccuracy PositionAccuracy
        {
            get => positionAccuracy_;
            set
            {
                if( positionAccuracy_ != value )
                {
                    positionAccuracy_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Longitude
        {
            get => longitude_;
            set
            {
                if( longitude_ != value )
                {
                    longitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Latitude
        {
            get => latitude_;
            set
            {
                if( latitude_ != value )
                {
                    latitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double CourseOverGround
        {
            get => courseOverGround_;
            set
            {
                if( courseOverGround_ != value )
                {
                    courseOverGround_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int? TrueHeading
        {
            get => trueHeading_;
            set
            {
                if( trueHeading_ != value )
                {
                    trueHeading_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int RegionalReserved
        {
            get => regionalReserved_;
            set
            {
                if( regionalReserved_ != value )
                {
                    regionalReserved_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool IsCsUnit
        {
            get => isCsUnit_;
            set
            {
                if( isCsUnit_ != value )
                {
                    isCsUnit_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool HasDisplay
        {
            get => hasDisplay_;
            set
            {
                if( hasDisplay_ != value )
                {
                    hasDisplay_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool HasDscCapability
        {
            get => hasDscCapability_;
            set
            {
                if( hasDscCapability_ != value )
                {
                    hasDscCapability_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Band
        {
            get => band_;
            set
            {
                if( band_ != value )
                {
                    band_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool CanAcceptMessage22
        {
            get => canAcceptMessage22_;
            set
            {
                if( canAcceptMessage22_ != value )
                {
                    canAcceptMessage22_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Assigned
        {
            get => assigned_;
            set
            {
                if( assigned_ != value )
                {
                    assigned_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.Raim Raim
        {
            get => raim_;
            set
            {
                if( raim_ != value )
                {
                    raim_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int RadioStatus
        {
            get => radioStatus_;
            set
            {
                if( radioStatus_ != value )
                {
                    radioStatus_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AisStandardSarAircraftPositionReportMessageObject : AisMessageObject
    {
        int altitude_ = 0;
        int speedOverGround_ = 0;
        Types.PositionAccuracy positionAccuracy_ = Types.PositionAccuracy.Low;
        double longitude_ = 0.0;
        double latitude_ = 0.0;
        double courseOverGround_ = 0.0;
        int timestamp_ = 0;
        int reserved_ = 0;
        bool dataTerminalReady_ = false;
        int spare_ = 0;
        bool assigned_ = false;
        Types.Raim raim_ = Types.Raim.NotInUse;
        int radioStatus_ = 0;
        public AisStandardSarAircraftPositionReportMessageObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisStandardSarAircraftPositionReportMessage;
        }

        public override BaseData<Kind> Create()
        {
            return new AisStandardSarAircraftPositionReportMessageObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisStandardSarAircraftPositionReportMessage )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public int Altitude
        {
            get => altitude_;
            set
            {
                if( altitude_ != value )
                {
                    altitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int SpeedOverGround
        {
            get => speedOverGround_;
            set
            {
                if( speedOverGround_ != value )
                {
                    speedOverGround_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.PositionAccuracy PositionAccuracy
        {
            get => positionAccuracy_;
            set
            {
                if( positionAccuracy_ != value )
                {
                    positionAccuracy_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Longitude
        {
            get => longitude_;
            set
            {
                if( longitude_ != value )
                {
                    longitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Latitude
        {
            get => latitude_;
            set
            {
                if( latitude_ != value )
                {
                    latitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double CourseOverGround
        {
            get => courseOverGround_;
            set
            {
                if( courseOverGround_ != value )
                {
                    courseOverGround_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Reserved
        {
            get => reserved_;
            set
            {
                if( reserved_ != value )
                {
                    reserved_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool DataTerminalReady
        {
            get => dataTerminalReady_;
            set
            {
                if( dataTerminalReady_ != value )
                {
                    dataTerminalReady_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Spare
        {
            get => spare_;
            set
            {
                if( spare_ != value )
                {
                    spare_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Assigned
        {
            get => assigned_;
            set
            {
                if( assigned_ != value )
                {
                    assigned_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.Raim Raim
        {
            get => raim_;
            set
            {
                if( raim_ != value )
                {
                    raim_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int RadioStatus
        {
            get => radioStatus_;
            set
            {
                if( radioStatus_ != value )
                {
                    radioStatus_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AisStaticAndVoyageRelatedDataMessageObject : AisMessageObject
    {
        int aisVersion_ = 0;
        Guid imoNumber_;
        Guid callsign_;
        Guid shipName_;
        Types.ShipType shipType_ = Types.ShipType.NotAvailable;
        int dimensionToBow_ = 0;
        int dimensionToStern_ = 0;
        int dimensionToPort_ = 0;
        int dimensionToStarboard_ = 0;
        Types.PositionFixType positionFixType_ = Types.PositionFixType.Undefined1;
        DateTime? estimatedTimeOfArrival_;
        double draught_ = 0.0;
        string destination_ = string.Empty;
        bool dataTerminalReady_ = false;
        int spare_ = 0;
        public AisStaticAndVoyageRelatedDataMessageObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisStaticAndVoyageRelatedDataMessage;
        }

        public override BaseData<Kind> Create()
        {
            return new AisStaticAndVoyageRelatedDataMessageObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisStaticAndVoyageRelatedDataMessage )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public int AisVersion
        {
            get => aisVersion_;
            set
            {
                if( aisVersion_ != value )
                {
                    aisVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid ImoNumber
        {
            get => imoNumber_;
            set
            {
                if( imoNumber_ != value )
                {
                    imoNumber_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Callsign
        {
            get => callsign_;
            set
            {
                if( callsign_ != value )
                {
                    callsign_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid ShipName
        {
            get => shipName_;
            set
            {
                if( shipName_ != value )
                {
                    shipName_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.ShipType ShipType
        {
            get => shipType_;
            set
            {
                if( shipType_ != value )
                {
                    shipType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int DimensionToBow
        {
            get => dimensionToBow_;
            set
            {
                if( dimensionToBow_ != value )
                {
                    dimensionToBow_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int DimensionToStern
        {
            get => dimensionToStern_;
            set
            {
                if( dimensionToStern_ != value )
                {
                    dimensionToStern_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int DimensionToPort
        {
            get => dimensionToPort_;
            set
            {
                if( dimensionToPort_ != value )
                {
                    dimensionToPort_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int DimensionToStarboard
        {
            get => dimensionToStarboard_;
            set
            {
                if( dimensionToStarboard_ != value )
                {
                    dimensionToStarboard_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.PositionFixType PositionFixType
        {
            get => positionFixType_;
            set
            {
                if( positionFixType_ != value )
                {
                    positionFixType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime? EstimatedTimeOfArrival
        {
            get => estimatedTimeOfArrival_;
            set
            {
                if( estimatedTimeOfArrival_ != value )
                {
                    estimatedTimeOfArrival_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Draught
        {
            get => draught_;
            set
            {
                if( draught_ != value )
                {
                    draught_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Destination
        {
            get => destination_;
            set
            {
                if( destination_ != value )
                {
                    destination_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool DataTerminalReady
        {
            get => dataTerminalReady_;
            set
            {
                if( dataTerminalReady_ != value )
                {
                    dataTerminalReady_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Spare
        {
            get => spare_;
            set
            {
                if( spare_ != value )
                {
                    spare_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AisStaticDataReportMessageObject : AisMessageObject
    {
        int partNumber_ = 0;
        public AisStaticDataReportMessageObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisStaticDataReportMessage;
        }

        public override BaseData<Kind> Create()
        {
            return new AisStaticDataReportMessageObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisStaticDataReportMessage )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public int PartNumber
        {
            get => partNumber_;
            set
            {
                if( partNumber_ != value )
                {
                    partNumber_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AisStaticDataReportPartAMessageObject : AisStaticDataReportMessageObject
    {
        Guid shipName_;
        int spare_ = 0;
        public AisStaticDataReportPartAMessageObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisStaticDataReportPartAMessage;
        }

        public override BaseData<Kind> Create()
        {
            return new AisStaticDataReportPartAMessageObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisStaticDataReportPartAMessage )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid ShipName
        {
            get => shipName_;
            set
            {
                if( shipName_ != value )
                {
                    shipName_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Spare
        {
            get => spare_;
            set
            {
                if( spare_ != value )
                {
                    spare_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AisStaticDataReportPartBMessageObject : AisStaticDataReportMessageObject
    {
        Types.ShipType shipType_ = Types.ShipType.NotAvailable;
        string vendorId_ = string.Empty;
        int unitModelCode_ = 0;
        int serialNumber_ = 0;
        Guid callsign_;
        int dimensionToBow_ = 0;
        int dimensionToStern_ = 0;
        int dimensionToPort_ = 0;
        int dimensionToStarboard_ = 0;
        Guid? mothershipMmsi_;
        Types.PositionFixType positionFixType_ = Types.PositionFixType.Undefined1;
        int spare_ = 0;
        public AisStaticDataReportPartBMessageObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisStaticDataReportPartBMessage;
        }

        public override BaseData<Kind> Create()
        {
            return new AisStaticDataReportPartBMessageObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisStaticDataReportPartBMessage )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Types.ShipType ShipType
        {
            get => shipType_;
            set
            {
                if( shipType_ != value )
                {
                    shipType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string VendorId
        {
            get => vendorId_;
            set
            {
                if( vendorId_ != value )
                {
                    vendorId_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int UnitModelCode
        {
            get => unitModelCode_;
            set
            {
                if( unitModelCode_ != value )
                {
                    unitModelCode_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int SerialNumber
        {
            get => serialNumber_;
            set
            {
                if( serialNumber_ != value )
                {
                    serialNumber_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Callsign
        {
            get => callsign_;
            set
            {
                if( callsign_ != value )
                {
                    callsign_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int DimensionToBow
        {
            get => dimensionToBow_;
            set
            {
                if( dimensionToBow_ != value )
                {
                    dimensionToBow_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int DimensionToStern
        {
            get => dimensionToStern_;
            set
            {
                if( dimensionToStern_ != value )
                {
                    dimensionToStern_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int DimensionToPort
        {
            get => dimensionToPort_;
            set
            {
                if( dimensionToPort_ != value )
                {
                    dimensionToPort_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int DimensionToStarboard
        {
            get => dimensionToStarboard_;
            set
            {
                if( dimensionToStarboard_ != value )
                {
                    dimensionToStarboard_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid? MothershipMmsi
        {
            get => mothershipMmsi_;
            set
            {
                if( mothershipMmsi_ != value )
                {
                    mothershipMmsi_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.PositionFixType PositionFixType
        {
            get => positionFixType_;
            set
            {
                if( positionFixType_ != value )
                {
                    positionFixType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Spare
        {
            get => spare_;
            set
            {
                if( spare_ != value )
                {
                    spare_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AisUtcAndDateInquiryMessageObject : AisMessageObject
    {
        int spare1_ = 0;
        int destinationMmsi_ = 0;
        int spare2_ = 0;
        public AisUtcAndDateInquiryMessageObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisUtcAndDateInquiryMessage;
        }

        public override BaseData<Kind> Create()
        {
            return new AisUtcAndDateInquiryMessageObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisUtcAndDateInquiryMessage )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public int Spare1
        {
            get => spare1_;
            set
            {
                if( spare1_ != value )
                {
                    spare1_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int DestinationMmsi
        {
            get => destinationMmsi_;
            set
            {
                if( destinationMmsi_ != value )
                {
                    destinationMmsi_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Spare2
        {
            get => spare2_;
            set
            {
                if( spare2_ != value )
                {
                    spare2_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AisUtcAndDateResponseMessageObject : AisMessageObject
    {
        DateTime datetime_;
        Types.PositionAccuracy positionAccuracy_ = Types.PositionAccuracy.Low;
        double longitude_ = 0.0;
        double latitude_ = 0.0;
        Types.PositionFixType positionFixType_ = Types.PositionFixType.Undefined1;
        int spare_ = 0;
        Types.Raim raim_ = Types.Raim.NotInUse;
        int radioStatus_ = 0;
        public AisUtcAndDateResponseMessageObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisUtcAndDateResponseMessage;
        }

        public override BaseData<Kind> Create()
        {
            return new AisUtcAndDateResponseMessageObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisUtcAndDateResponseMessage )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public DateTime Datetime
        {
            get => datetime_;
            set
            {
                if( datetime_ != value )
                {
                    datetime_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.PositionAccuracy PositionAccuracy
        {
            get => positionAccuracy_;
            set
            {
                if( positionAccuracy_ != value )
                {
                    positionAccuracy_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Longitude
        {
            get => longitude_;
            set
            {
                if( longitude_ != value )
                {
                    longitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Latitude
        {
            get => latitude_;
            set
            {
                if( latitude_ != value )
                {
                    latitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.PositionFixType PositionFixType
        {
            get => positionFixType_;
            set
            {
                if( positionFixType_ != value )
                {
                    positionFixType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Spare
        {
            get => spare_;
            set
            {
                if( spare_ != value )
                {
                    spare_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.Raim Raim
        {
            get => raim_;
            set
            {
                if( raim_ != value )
                {
                    raim_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int RadioStatus
        {
            get => radioStatus_;
            set
            {
                if( radioStatus_ != value )
                {
                    radioStatus_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AlarmStateChangeObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid alarm_;
        DateTime timestamp_;
        Types.AlarmState state_ = Types.AlarmState.Unknown;
        public AlarmStateChangeObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AlarmStateChange;
        }

        public override BaseData<Kind> Create()
        {
            return new AlarmStateChangeObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AlarmStateChange )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Alarm
        {
            get => alarm_;
            set
            {
                if( alarm_ != value )
                {
                    alarm_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.AlarmState State
        {
            get => state_;
            set
            {
                if( state_ != value )
                {
                    state_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class BaseStationTypeObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        string name_ = string.Empty;
        public BaseStationTypeObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.BaseStationType;
        }

        public override BaseData<Kind> Create()
        {
            return new BaseStationTypeObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.BaseStationType )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class BinaryTimeseriesValueObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        byte[] value_ = Array.Empty<byte>();
        public BinaryTimeseriesValueObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.BinaryTimeseriesValue;
        }

        public override BaseData<Kind> Create()
        {
            return new BinaryTimeseriesValueObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.BinaryTimeseriesValue )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public byte[] Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class BookmarkObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid view_;
        string name_ = string.Empty;
        DateTime? timestamp_;
        double latitude_ = 0.0;
        double longitude_ = 0.0;
        double zoomLevel_ = 0.0;
        public BookmarkObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Bookmark;
        }

        public override BaseData<Kind> Create()
        {
            return new BookmarkObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Bookmark )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid View
        {
            get => view_;
            set
            {
                if( view_ != value )
                {
                    view_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime? Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Latitude
        {
            get => latitude_;
            set
            {
                if( latitude_ != value )
                {
                    latitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Longitude
        {
            get => longitude_;
            set
            {
                if( longitude_ != value )
                {
                    longitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double ZoomLevel
        {
            get => zoomLevel_;
            set
            {
                if( zoomLevel_ != value )
                {
                    zoomLevel_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class BooleanTimeseriesValueObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        bool? value_;
        public BooleanTimeseriesValueObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.BooleanTimeseriesValue;
        }

        public override BaseData<Kind> Create()
        {
            return new BooleanTimeseriesValueObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.BooleanTimeseriesValue )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool? Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class ByteTimeseriesValueObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        byte? value_;
        public ByteTimeseriesValueObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.ByteTimeseriesValue;
        }

        public override BaseData<Kind> Create()
        {
            return new ByteTimeseriesValueObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.ByteTimeseriesValue )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public byte? Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CameraCommandObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid camera_;
        DateTime timestamp_;
        Types.DeviceCommandSourceType deviceCommandSourceType_ = Types.DeviceCommandSourceType.Unknown;
        Guid deviceCommandSourceId_;
        Guid reply_;
        public CameraCommandObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CameraCommand;
        }

        public override BaseData<Kind> Create()
        {
            return new CameraCommandObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CameraCommand )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Camera
        {
            get => camera_;
            set
            {
                if( camera_ != value )
                {
                    camera_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.DeviceCommandSourceType DeviceCommandSourceType
        {
            get => deviceCommandSourceType_;
            set
            {
                if( deviceCommandSourceType_ != value )
                {
                    deviceCommandSourceType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid DeviceCommandSourceId
        {
            get => deviceCommandSourceId_;
            set
            {
                if( deviceCommandSourceId_ != value )
                {
                    deviceCommandSourceId_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Reply
        {
            get => reply_;
            set
            {
                if( reply_ != value )
                {
                    reply_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CameraCommandAbsoluteMoveObject : CameraCommandObject
    {
        Types.CameraPanTiltMode positionPanTiltMode_ = Types.CameraPanTiltMode.Unknown;
        double? panAngle_;
        double? tiltAngle_;
        Types.CameraFocalLengthMode positionFocalLengthMode_ = Types.CameraFocalLengthMode.Unknown;
        double? focalLength_;
        Types.CameraPanTiltMode speedPanTiltMode_ = Types.CameraPanTiltMode.Unknown;
        double? panSpeed_;
        double? tiltSpeed_;
        Types.CameraFocalLengthMode speedFocalLengthMode_ = Types.CameraFocalLengthMode.Unknown;
        double? zoomSpeed_;
        public CameraCommandAbsoluteMoveObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CameraCommandAbsoluteMove;
        }

        public override BaseData<Kind> Create()
        {
            return new CameraCommandAbsoluteMoveObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CameraCommandAbsoluteMove )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Types.CameraPanTiltMode PositionPanTiltMode
        {
            get => positionPanTiltMode_;
            set
            {
                if( positionPanTiltMode_ != value )
                {
                    positionPanTiltMode_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? PanAngle
        {
            get => panAngle_;
            set
            {
                if( panAngle_ != value )
                {
                    panAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? TiltAngle
        {
            get => tiltAngle_;
            set
            {
                if( tiltAngle_ != value )
                {
                    tiltAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.CameraFocalLengthMode PositionFocalLengthMode
        {
            get => positionFocalLengthMode_;
            set
            {
                if( positionFocalLengthMode_ != value )
                {
                    positionFocalLengthMode_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? FocalLength
        {
            get => focalLength_;
            set
            {
                if( focalLength_ != value )
                {
                    focalLength_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.CameraPanTiltMode SpeedPanTiltMode
        {
            get => speedPanTiltMode_;
            set
            {
                if( speedPanTiltMode_ != value )
                {
                    speedPanTiltMode_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? PanSpeed
        {
            get => panSpeed_;
            set
            {
                if( panSpeed_ != value )
                {
                    panSpeed_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? TiltSpeed
        {
            get => tiltSpeed_;
            set
            {
                if( tiltSpeed_ != value )
                {
                    tiltSpeed_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.CameraFocalLengthMode SpeedFocalLengthMode
        {
            get => speedFocalLengthMode_;
            set
            {
                if( speedFocalLengthMode_ != value )
                {
                    speedFocalLengthMode_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? ZoomSpeed
        {
            get => zoomSpeed_;
            set
            {
                if( zoomSpeed_ != value )
                {
                    zoomSpeed_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CameraCommandAdjustPanTiltZoomObject : CameraCommandObject
    {
        double? x_;
        double? y_;
        double? z_;
        public CameraCommandAdjustPanTiltZoomObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CameraCommandAdjustPanTiltZoom;
        }

        public override BaseData<Kind> Create()
        {
            return new CameraCommandAdjustPanTiltZoomObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CameraCommandAdjustPanTiltZoom )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public double? X
        {
            get => x_;
            set
            {
                if( x_ != value )
                {
                    x_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? Y
        {
            get => y_;
            set
            {
                if( y_ != value )
                {
                    y_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? Z
        {
            get => z_;
            set
            {
                if( z_ != value )
                {
                    z_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CameraCommandContinuousMoveObject : CameraCommandObject
    {
        bool normalized_ = false;
        double? panVelocity_;
        double? tiltVelocity_;
        double? zoomVelocity_;
        TimeSpan? duration_;
        public CameraCommandContinuousMoveObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CameraCommandContinuousMove;
        }

        public override BaseData<Kind> Create()
        {
            return new CameraCommandContinuousMoveObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CameraCommandContinuousMove )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public bool Normalized
        {
            get => normalized_;
            set
            {
                if( normalized_ != value )
                {
                    normalized_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? PanVelocity
        {
            get => panVelocity_;
            set
            {
                if( panVelocity_ != value )
                {
                    panVelocity_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? TiltVelocity
        {
            get => tiltVelocity_;
            set
            {
                if( tiltVelocity_ != value )
                {
                    tiltVelocity_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? ZoomVelocity
        {
            get => zoomVelocity_;
            set
            {
                if( zoomVelocity_ != value )
                {
                    zoomVelocity_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan? Duration
        {
            get => duration_;
            set
            {
                if( duration_ != value )
                {
                    duration_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CameraCommandGeoMoveObject : CameraCommandObject
    {
        double latitude_ = 0.0;
        double longitude_ = 0.0;
        double? altitude_;
        double? viewportWidth_;
        double? viewportHeight_;
        public CameraCommandGeoMoveObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CameraCommandGeoMove;
        }

        public override BaseData<Kind> Create()
        {
            return new CameraCommandGeoMoveObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CameraCommandGeoMove )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public double Latitude
        {
            get => latitude_;
            set
            {
                if( latitude_ != value )
                {
                    latitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Longitude
        {
            get => longitude_;
            set
            {
                if( longitude_ != value )
                {
                    longitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? Altitude
        {
            get => altitude_;
            set
            {
                if( altitude_ != value )
                {
                    altitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? ViewportWidth
        {
            get => viewportWidth_;
            set
            {
                if( viewportWidth_ != value )
                {
                    viewportWidth_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? ViewportHeight
        {
            get => viewportHeight_;
            set
            {
                if( viewportHeight_ != value )
                {
                    viewportHeight_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CameraCommandRelativeMoveObject : CameraCommandObject
    {
        bool normalized_ = false;
        double? panAngle_;
        double? tiltAngle_;
        double? focalLength_;
        double? panSpeed_;
        double? tiltSpeed_;
        double? zoomSpeed_;
        public CameraCommandRelativeMoveObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CameraCommandRelativeMove;
        }

        public override BaseData<Kind> Create()
        {
            return new CameraCommandRelativeMoveObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CameraCommandRelativeMove )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public bool Normalized
        {
            get => normalized_;
            set
            {
                if( normalized_ != value )
                {
                    normalized_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? PanAngle
        {
            get => panAngle_;
            set
            {
                if( panAngle_ != value )
                {
                    panAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? TiltAngle
        {
            get => tiltAngle_;
            set
            {
                if( tiltAngle_ != value )
                {
                    tiltAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? FocalLength
        {
            get => focalLength_;
            set
            {
                if( focalLength_ != value )
                {
                    focalLength_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? PanSpeed
        {
            get => panSpeed_;
            set
            {
                if( panSpeed_ != value )
                {
                    panSpeed_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? TiltSpeed
        {
            get => tiltSpeed_;
            set
            {
                if( tiltSpeed_ != value )
                {
                    tiltSpeed_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? ZoomSpeed
        {
            get => zoomSpeed_;
            set
            {
                if( zoomSpeed_ != value )
                {
                    zoomSpeed_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CameraCommandReleasePTZOwnershipObject : CameraCommandObject
    {
        public CameraCommandReleasePTZOwnershipObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CameraCommandReleasePTZOwnership;
        }

        public override BaseData<Kind> Create()
        {
            return new CameraCommandReleasePTZOwnershipObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CameraCommandReleasePTZOwnership )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class CameraCommandRequestPTZOwnershipObject : CameraCommandObject
    {
        public CameraCommandRequestPTZOwnershipObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CameraCommandRequestPTZOwnership;
        }

        public override BaseData<Kind> Create()
        {
            return new CameraCommandRequestPTZOwnershipObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CameraCommandRequestPTZOwnership )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class CameraCommandSetAutoFocusObject : CameraCommandObject
    {
        bool enabled_ = false;
        public CameraCommandSetAutoFocusObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CameraCommandSetAutoFocus;
        }

        public override BaseData<Kind> Create()
        {
            return new CameraCommandSetAutoFocusObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CameraCommandSetAutoFocus )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public bool Enabled
        {
            get => enabled_;
            set
            {
                if( enabled_ != value )
                {
                    enabled_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CameraCommandSetBlackAndWhiteObject : CameraCommandObject
    {
        bool enabled_ = false;
        public CameraCommandSetBlackAndWhiteObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CameraCommandSetBlackAndWhite;
        }

        public override BaseData<Kind> Create()
        {
            return new CameraCommandSetBlackAndWhiteObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CameraCommandSetBlackAndWhite )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public bool Enabled
        {
            get => enabled_;
            set
            {
                if( enabled_ != value )
                {
                    enabled_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CameraCommandSetFollowedObject : CameraCommandObject
    {
        Guid trackId_;
        Types.CameraFollowReason reason_ = Types.CameraFollowReason.Alarm;
        public CameraCommandSetFollowedObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CameraCommandSetFollowed;
        }

        public override BaseData<Kind> Create()
        {
            return new CameraCommandSetFollowedObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CameraCommandSetFollowed )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid TrackId
        {
            get => trackId_;
            set
            {
                if( trackId_ != value )
                {
                    trackId_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.CameraFollowReason Reason
        {
            get => reason_;
            set
            {
                if( reason_ != value )
                {
                    reason_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CameraCommandSetInfraRedLampObject : CameraCommandObject
    {
        bool enabled_ = false;
        public CameraCommandSetInfraRedLampObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CameraCommandSetInfraRedLamp;
        }

        public override BaseData<Kind> Create()
        {
            return new CameraCommandSetInfraRedLampObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CameraCommandSetInfraRedLamp )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public bool Enabled
        {
            get => enabled_;
            set
            {
                if( enabled_ != value )
                {
                    enabled_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CameraCommandSetWasherObject : CameraCommandObject
    {
        bool enabled_ = false;
        public CameraCommandSetWasherObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CameraCommandSetWasher;
        }

        public override BaseData<Kind> Create()
        {
            return new CameraCommandSetWasherObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CameraCommandSetWasher )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public bool Enabled
        {
            get => enabled_;
            set
            {
                if( enabled_ != value )
                {
                    enabled_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CameraCommandSetWiperObject : CameraCommandObject
    {
        bool enabled_ = false;
        public CameraCommandSetWiperObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CameraCommandSetWiper;
        }

        public override BaseData<Kind> Create()
        {
            return new CameraCommandSetWiperObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CameraCommandSetWiper )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public bool Enabled
        {
            get => enabled_;
            set
            {
                if( enabled_ != value )
                {
                    enabled_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CameraCommandStopObject : CameraCommandObject
    {
        bool panTilt_ = false;
        bool zoom_ = false;
        public CameraCommandStopObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CameraCommandStop;
        }

        public override BaseData<Kind> Create()
        {
            return new CameraCommandStopObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CameraCommandStop )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public bool PanTilt
        {
            get => panTilt_;
            set
            {
                if( panTilt_ != value )
                {
                    panTilt_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Zoom
        {
            get => zoom_;
            set
            {
                if( zoom_ != value )
                {
                    zoom_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CameraCommandReplyObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid camera_;
        DateTime timestamp_;
        Guid command_;
        Types.DeviceCommandReplyStatus status_ = Types.DeviceCommandReplyStatus.Unknown;
        string message_ = string.Empty;
        double panAngle_ = 0.0;
        double tiltAngle_ = 0.0;
        double focalLength_ = 0.0;
        public CameraCommandReplyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CameraCommandReply;
        }

        public override BaseData<Kind> Create()
        {
            return new CameraCommandReplyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CameraCommandReply )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Camera
        {
            get => camera_;
            set
            {
                if( camera_ != value )
                {
                    camera_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Command
        {
            get => command_;
            set
            {
                if( command_ != value )
                {
                    command_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.DeviceCommandReplyStatus Status
        {
            get => status_;
            set
            {
                if( status_ != value )
                {
                    status_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Message
        {
            get => message_;
            set
            {
                if( message_ != value )
                {
                    message_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double PanAngle
        {
            get => panAngle_;
            set
            {
                if( panAngle_ != value )
                {
                    panAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double TiltAngle
        {
            get => tiltAngle_;
            set
            {
                if( tiltAngle_ != value )
                {
                    tiltAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double FocalLength
        {
            get => focalLength_;
            set
            {
                if( focalLength_ != value )
                {
                    focalLength_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CameraConfigurationObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid camera_;
        DateTime timestamp_;
        Types.CameraControlProtocol cameraControlProtocol_ = Types.CameraControlProtocol.Unknown;
        string cameraAddress_ = string.Empty;
        int cameraPort_ = 0;
        string cameraControlAddress_ = string.Empty;
        int cameraControlPort_ = 0;
        string cameraUserName_ = string.Empty;
        string cameraPassword_ = string.Empty;
        bool useRtspUriOverride_ = false;
        string rtspUriOverride_ = string.Empty;
        double latitude_ = 0.0;
        double longitude_ = 0.0;
        double altitude_ = 0.0;
        bool useRelativePosition_ = false;
        double azimuthFromGPS_ = 0.0;
        double distanceFromGPS_ = 0.0;
        Types.CameraPanTiltMode panTiltMode_ = Types.CameraPanTiltMode.Unknown;
        double minTiltAngle_ = 0.0;
        double maxTiltAngle_ = 0.0;
        double minTiltScaleAngle_ = 0.0;
        double maxTiltScaleAngle_ = 0.0;
        bool useReverseTiltAngle_ = false;
        bool useReverseNormalizedTiltAngle_ = false;
        double minTiltVelocity_ = 0.0;
        double maxTiltVelocity_ = 0.0;
        double minTiltSpeed_ = 0.0;
        double maxTiltSpeed_ = 0.0;
        double minPanAngle_ = 0.0;
        double maxPanAngle_ = 0.0;
        double minPanScaleAngle_ = 0.0;
        double maxPanScaleAngle_ = 0.0;
        bool useReversePanAngle_ = false;
        bool useReverseNormalizedPanAngle_ = false;
        double minPanVelocity_ = 0.0;
        double maxPanVelocity_ = 0.0;
        double minPanSpeed_ = 0.0;
        double maxPanSpeed_ = 0.0;
        Types.CameraFocalLengthMode focalLengthMode_ = Types.CameraFocalLengthMode.Unknown;
        double minFocalLength_ = 0.0;
        double maxFocalLength_ = 0.0;
        double minFocalLengthScale_ = 0.0;
        double maxFocalLengthScale_ = 0.0;
        double minZoomVelocity_ = 0.0;
        double maxZoomVelocity_ = 0.0;
        double minZoomSpeed_ = 0.0;
        double maxZoomSpeed_ = 0.0;
        double imageSensorWidth_ = 0.0;
        double imageSensorHeight_ = 0.0;
        double homePanAngle_ = 0.0;
        double homeTiltAngle_ = 0.0;
        double homeFocalLength_ = 0.0;
        double panOffset_ = 0.0;
        double tiltOffset_ = 0.0;
        double aimAltitude_ = 0.0;
        double minimumTargetWidth_ = 0.0;
        TimeSpan targetLockTimeout_;
        TimeSpan updateStatusInterval_;
        TimeSpan readTimeout_;
        TimeSpan moveCommandStatusDelay_;
        string ptzProfileName_ = string.Empty;
        string ptzConfigurationToken_ = string.Empty;
        string videoSourceToken_ = string.Empty;
        public CameraConfigurationObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CameraConfiguration;
        }

        public override BaseData<Kind> Create()
        {
            return new CameraConfigurationObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CameraConfiguration )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Camera
        {
            get => camera_;
            set
            {
                if( camera_ != value )
                {
                    camera_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.CameraControlProtocol CameraControlProtocol
        {
            get => cameraControlProtocol_;
            set
            {
                if( cameraControlProtocol_ != value )
                {
                    cameraControlProtocol_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string CameraAddress
        {
            get => cameraAddress_;
            set
            {
                if( cameraAddress_ != value )
                {
                    cameraAddress_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int CameraPort
        {
            get => cameraPort_;
            set
            {
                if( cameraPort_ != value )
                {
                    cameraPort_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string CameraControlAddress
        {
            get => cameraControlAddress_;
            set
            {
                if( cameraControlAddress_ != value )
                {
                    cameraControlAddress_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int CameraControlPort
        {
            get => cameraControlPort_;
            set
            {
                if( cameraControlPort_ != value )
                {
                    cameraControlPort_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string CameraUserName
        {
            get => cameraUserName_;
            set
            {
                if( cameraUserName_ != value )
                {
                    cameraUserName_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string CameraPassword
        {
            get => cameraPassword_;
            set
            {
                if( cameraPassword_ != value )
                {
                    cameraPassword_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool UseRtspUriOverride
        {
            get => useRtspUriOverride_;
            set
            {
                if( useRtspUriOverride_ != value )
                {
                    useRtspUriOverride_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string RtspUriOverride
        {
            get => rtspUriOverride_;
            set
            {
                if( rtspUriOverride_ != value )
                {
                    rtspUriOverride_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Latitude
        {
            get => latitude_;
            set
            {
                if( latitude_ != value )
                {
                    latitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Longitude
        {
            get => longitude_;
            set
            {
                if( longitude_ != value )
                {
                    longitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Altitude
        {
            get => altitude_;
            set
            {
                if( altitude_ != value )
                {
                    altitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool UseRelativePosition
        {
            get => useRelativePosition_;
            set
            {
                if( useRelativePosition_ != value )
                {
                    useRelativePosition_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double AzimuthFromGPS
        {
            get => azimuthFromGPS_;
            set
            {
                if( azimuthFromGPS_ != value )
                {
                    azimuthFromGPS_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double DistanceFromGPS
        {
            get => distanceFromGPS_;
            set
            {
                if( distanceFromGPS_ != value )
                {
                    distanceFromGPS_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.CameraPanTiltMode PanTiltMode
        {
            get => panTiltMode_;
            set
            {
                if( panTiltMode_ != value )
                {
                    panTiltMode_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MinTiltAngle
        {
            get => minTiltAngle_;
            set
            {
                if( minTiltAngle_ != value )
                {
                    minTiltAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MaxTiltAngle
        {
            get => maxTiltAngle_;
            set
            {
                if( maxTiltAngle_ != value )
                {
                    maxTiltAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MinTiltScaleAngle
        {
            get => minTiltScaleAngle_;
            set
            {
                if( minTiltScaleAngle_ != value )
                {
                    minTiltScaleAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MaxTiltScaleAngle
        {
            get => maxTiltScaleAngle_;
            set
            {
                if( maxTiltScaleAngle_ != value )
                {
                    maxTiltScaleAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool UseReverseTiltAngle
        {
            get => useReverseTiltAngle_;
            set
            {
                if( useReverseTiltAngle_ != value )
                {
                    useReverseTiltAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool UseReverseNormalizedTiltAngle
        {
            get => useReverseNormalizedTiltAngle_;
            set
            {
                if( useReverseNormalizedTiltAngle_ != value )
                {
                    useReverseNormalizedTiltAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MinTiltVelocity
        {
            get => minTiltVelocity_;
            set
            {
                if( minTiltVelocity_ != value )
                {
                    minTiltVelocity_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MaxTiltVelocity
        {
            get => maxTiltVelocity_;
            set
            {
                if( maxTiltVelocity_ != value )
                {
                    maxTiltVelocity_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MinTiltSpeed
        {
            get => minTiltSpeed_;
            set
            {
                if( minTiltSpeed_ != value )
                {
                    minTiltSpeed_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MaxTiltSpeed
        {
            get => maxTiltSpeed_;
            set
            {
                if( maxTiltSpeed_ != value )
                {
                    maxTiltSpeed_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MinPanAngle
        {
            get => minPanAngle_;
            set
            {
                if( minPanAngle_ != value )
                {
                    minPanAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MaxPanAngle
        {
            get => maxPanAngle_;
            set
            {
                if( maxPanAngle_ != value )
                {
                    maxPanAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MinPanScaleAngle
        {
            get => minPanScaleAngle_;
            set
            {
                if( minPanScaleAngle_ != value )
                {
                    minPanScaleAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MaxPanScaleAngle
        {
            get => maxPanScaleAngle_;
            set
            {
                if( maxPanScaleAngle_ != value )
                {
                    maxPanScaleAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool UseReversePanAngle
        {
            get => useReversePanAngle_;
            set
            {
                if( useReversePanAngle_ != value )
                {
                    useReversePanAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool UseReverseNormalizedPanAngle
        {
            get => useReverseNormalizedPanAngle_;
            set
            {
                if( useReverseNormalizedPanAngle_ != value )
                {
                    useReverseNormalizedPanAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MinPanVelocity
        {
            get => minPanVelocity_;
            set
            {
                if( minPanVelocity_ != value )
                {
                    minPanVelocity_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MaxPanVelocity
        {
            get => maxPanVelocity_;
            set
            {
                if( maxPanVelocity_ != value )
                {
                    maxPanVelocity_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MinPanSpeed
        {
            get => minPanSpeed_;
            set
            {
                if( minPanSpeed_ != value )
                {
                    minPanSpeed_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MaxPanSpeed
        {
            get => maxPanSpeed_;
            set
            {
                if( maxPanSpeed_ != value )
                {
                    maxPanSpeed_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.CameraFocalLengthMode FocalLengthMode
        {
            get => focalLengthMode_;
            set
            {
                if( focalLengthMode_ != value )
                {
                    focalLengthMode_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MinFocalLength
        {
            get => minFocalLength_;
            set
            {
                if( minFocalLength_ != value )
                {
                    minFocalLength_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MaxFocalLength
        {
            get => maxFocalLength_;
            set
            {
                if( maxFocalLength_ != value )
                {
                    maxFocalLength_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MinFocalLengthScale
        {
            get => minFocalLengthScale_;
            set
            {
                if( minFocalLengthScale_ != value )
                {
                    minFocalLengthScale_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MaxFocalLengthScale
        {
            get => maxFocalLengthScale_;
            set
            {
                if( maxFocalLengthScale_ != value )
                {
                    maxFocalLengthScale_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MinZoomVelocity
        {
            get => minZoomVelocity_;
            set
            {
                if( minZoomVelocity_ != value )
                {
                    minZoomVelocity_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MaxZoomVelocity
        {
            get => maxZoomVelocity_;
            set
            {
                if( maxZoomVelocity_ != value )
                {
                    maxZoomVelocity_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MinZoomSpeed
        {
            get => minZoomSpeed_;
            set
            {
                if( minZoomSpeed_ != value )
                {
                    minZoomSpeed_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MaxZoomSpeed
        {
            get => maxZoomSpeed_;
            set
            {
                if( maxZoomSpeed_ != value )
                {
                    maxZoomSpeed_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double ImageSensorWidth
        {
            get => imageSensorWidth_;
            set
            {
                if( imageSensorWidth_ != value )
                {
                    imageSensorWidth_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double ImageSensorHeight
        {
            get => imageSensorHeight_;
            set
            {
                if( imageSensorHeight_ != value )
                {
                    imageSensorHeight_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double HomePanAngle
        {
            get => homePanAngle_;
            set
            {
                if( homePanAngle_ != value )
                {
                    homePanAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double HomeTiltAngle
        {
            get => homeTiltAngle_;
            set
            {
                if( homeTiltAngle_ != value )
                {
                    homeTiltAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double HomeFocalLength
        {
            get => homeFocalLength_;
            set
            {
                if( homeFocalLength_ != value )
                {
                    homeFocalLength_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double PanOffset
        {
            get => panOffset_;
            set
            {
                if( panOffset_ != value )
                {
                    panOffset_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double TiltOffset
        {
            get => tiltOffset_;
            set
            {
                if( tiltOffset_ != value )
                {
                    tiltOffset_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double AimAltitude
        {
            get => aimAltitude_;
            set
            {
                if( aimAltitude_ != value )
                {
                    aimAltitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MinimumTargetWidth
        {
            get => minimumTargetWidth_;
            set
            {
                if( minimumTargetWidth_ != value )
                {
                    minimumTargetWidth_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan TargetLockTimeout
        {
            get => targetLockTimeout_;
            set
            {
                if( targetLockTimeout_ != value )
                {
                    targetLockTimeout_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan UpdateStatusInterval
        {
            get => updateStatusInterval_;
            set
            {
                if( updateStatusInterval_ != value )
                {
                    updateStatusInterval_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan ReadTimeout
        {
            get => readTimeout_;
            set
            {
                if( readTimeout_ != value )
                {
                    readTimeout_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan MoveCommandStatusDelay
        {
            get => moveCommandStatusDelay_;
            set
            {
                if( moveCommandStatusDelay_ != value )
                {
                    moveCommandStatusDelay_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string PtzProfileName
        {
            get => ptzProfileName_;
            set
            {
                if( ptzProfileName_ != value )
                {
                    ptzProfileName_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string PtzConfigurationToken
        {
            get => ptzConfigurationToken_;
            set
            {
                if( ptzConfigurationToken_ != value )
                {
                    ptzConfigurationToken_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string VideoSourceToken
        {
            get => videoSourceToken_;
            set
            {
                if( videoSourceToken_ != value )
                {
                    videoSourceToken_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CameraPanCalibrationObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid camera_;
        DateTime timestamp_;
        public CameraPanCalibrationObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CameraPanCalibration;
        }

        public override BaseData<Kind> Create()
        {
            return new CameraPanCalibrationObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CameraPanCalibration )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Camera
        {
            get => camera_;
            set
            {
                if( camera_ != value )
                {
                    camera_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CameraPanCalibrationValueObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid panCalibration_;
        double panAngle_ = 0.0;
        double panOffset_ = 0.0;
        public CameraPanCalibrationValueObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CameraPanCalibrationValue;
        }

        public override BaseData<Kind> Create()
        {
            return new CameraPanCalibrationValueObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CameraPanCalibrationValue )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid PanCalibration
        {
            get => panCalibration_;
            set
            {
                if( panCalibration_ != value )
                {
                    panCalibration_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double PanAngle
        {
            get => panAngle_;
            set
            {
                if( panAngle_ != value )
                {
                    panAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double PanOffset
        {
            get => panOffset_;
            set
            {
                if( panOffset_ != value )
                {
                    panOffset_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CameraStatusObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid camera_;
        Guid track_;
        DateTime timestamp_;
        Types.CameraPanTiltMode positionPanTiltMode_ = Types.CameraPanTiltMode.Unknown;
        double panAngle_ = 0.0;
        double tiltAngle_ = 0.0;
        Types.CameraFocalLengthMode positionFocalLengthMode_ = Types.CameraFocalLengthMode.Unknown;
        double focalLength_ = 0.0;
        Types.CameraMoveStatus panTiltMoveStatus_ = Types.CameraMoveStatus.Unknown;
        Types.CameraMoveStatus zoomMoveStatus_ = Types.CameraMoveStatus.Unknown;
        Types.CameraPanTiltMode velocityPanTiltMode_ = Types.CameraPanTiltMode.Unknown;
        double? panVelocity_;
        double? tiltVelocity_;
        Types.CameraFocalLengthMode velocityFocalLengthMode_ = Types.CameraFocalLengthMode.Unknown;
        double? zoomVelocity_;
        Types.CameraFeatures activeFeatures_ = Types.CameraFeatures.None;
        string error_ = string.Empty;
        public CameraStatusObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CameraStatus;
        }

        public override BaseData<Kind> Create()
        {
            return new CameraStatusObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CameraStatus )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Camera
        {
            get => camera_;
            set
            {
                if( camera_ != value )
                {
                    camera_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Track
        {
            get => track_;
            set
            {
                if( track_ != value )
                {
                    track_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.CameraPanTiltMode PositionPanTiltMode
        {
            get => positionPanTiltMode_;
            set
            {
                if( positionPanTiltMode_ != value )
                {
                    positionPanTiltMode_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double PanAngle
        {
            get => panAngle_;
            set
            {
                if( panAngle_ != value )
                {
                    panAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double TiltAngle
        {
            get => tiltAngle_;
            set
            {
                if( tiltAngle_ != value )
                {
                    tiltAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.CameraFocalLengthMode PositionFocalLengthMode
        {
            get => positionFocalLengthMode_;
            set
            {
                if( positionFocalLengthMode_ != value )
                {
                    positionFocalLengthMode_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double FocalLength
        {
            get => focalLength_;
            set
            {
                if( focalLength_ != value )
                {
                    focalLength_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.CameraMoveStatus PanTiltMoveStatus
        {
            get => panTiltMoveStatus_;
            set
            {
                if( panTiltMoveStatus_ != value )
                {
                    panTiltMoveStatus_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.CameraMoveStatus ZoomMoveStatus
        {
            get => zoomMoveStatus_;
            set
            {
                if( zoomMoveStatus_ != value )
                {
                    zoomMoveStatus_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.CameraPanTiltMode VelocityPanTiltMode
        {
            get => velocityPanTiltMode_;
            set
            {
                if( velocityPanTiltMode_ != value )
                {
                    velocityPanTiltMode_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? PanVelocity
        {
            get => panVelocity_;
            set
            {
                if( panVelocity_ != value )
                {
                    panVelocity_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? TiltVelocity
        {
            get => tiltVelocity_;
            set
            {
                if( tiltVelocity_ != value )
                {
                    tiltVelocity_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.CameraFocalLengthMode VelocityFocalLengthMode
        {
            get => velocityFocalLengthMode_;
            set
            {
                if( velocityFocalLengthMode_ != value )
                {
                    velocityFocalLengthMode_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? ZoomVelocity
        {
            get => zoomVelocity_;
            set
            {
                if( zoomVelocity_ != value )
                {
                    zoomVelocity_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.CameraFeatures ActiveFeatures
        {
            get => activeFeatures_;
            set
            {
                if( activeFeatures_ != value )
                {
                    activeFeatures_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Error
        {
            get => error_;
            set
            {
                if( error_ != value )
                {
                    error_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CameraTiltCalibrationObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid camera_;
        DateTime timestamp_;
        public CameraTiltCalibrationObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CameraTiltCalibration;
        }

        public override BaseData<Kind> Create()
        {
            return new CameraTiltCalibrationObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CameraTiltCalibration )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Camera
        {
            get => camera_;
            set
            {
                if( camera_ != value )
                {
                    camera_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CameraTiltCalibrationValueObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid tiltCalibration_;
        double panAngle_ = 0.0;
        double tiltOffset_ = 0.0;
        public CameraTiltCalibrationValueObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CameraTiltCalibrationValue;
        }

        public override BaseData<Kind> Create()
        {
            return new CameraTiltCalibrationValueObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CameraTiltCalibrationValue )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid TiltCalibration
        {
            get => tiltCalibration_;
            set
            {
                if( tiltCalibration_ != value )
                {
                    tiltCalibration_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double PanAngle
        {
            get => panAngle_;
            set
            {
                if( panAngle_ != value )
                {
                    panAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double TiltOffset
        {
            get => tiltOffset_;
            set
            {
                if( tiltOffset_ != value )
                {
                    tiltOffset_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CameraZoomCalibrationObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid camera_;
        DateTime timestamp_;
        public CameraZoomCalibrationObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CameraZoomCalibration;
        }

        public override BaseData<Kind> Create()
        {
            return new CameraZoomCalibrationObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CameraZoomCalibration )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Camera
        {
            get => camera_;
            set
            {
                if( camera_ != value )
                {
                    camera_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CameraZoomCalibrationValueObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid zoomCalibration_;
        double focalLength_ = 0.0;
        double focalLengthOffset_ = 0.0;
        public CameraZoomCalibrationValueObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CameraZoomCalibrationValue;
        }

        public override BaseData<Kind> Create()
        {
            return new CameraZoomCalibrationValueObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CameraZoomCalibrationValue )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid ZoomCalibration
        {
            get => zoomCalibration_;
            set
            {
                if( zoomCalibration_ != value )
                {
                    zoomCalibration_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double FocalLength
        {
            get => focalLength_;
            set
            {
                if( focalLength_ != value )
                {
                    focalLength_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double FocalLengthOffset
        {
            get => focalLengthOffset_;
            set
            {
                if( focalLengthOffset_ != value )
                {
                    focalLengthOffset_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public abstract class CatalogElementObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid catalog_;
        string name_ = string.Empty;
        protected CatalogElementObject ( )
        {
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CatalogElement )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Catalog
        {
            get => catalog_;
            set
            {
                if( catalog_ != value )
                {
                    catalog_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CatalogObject : CatalogElementObject
    {
        public CatalogObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Catalog;
        }

        public override BaseData<Kind> Create()
        {
            return new CatalogObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Catalog )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class ElementObject : CatalogElementObject
    {
        Guid elementType_;
        public ElementObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Element;
        }

        public override BaseData<Kind> Create()
        {
            return new ElementObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Element )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid ElementType
        {
            get => elementType_;
            set
            {
                if( elementType_ != value )
                {
                    elementType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CollectionInfoObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        long count_ = 0;
        public CollectionInfoObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CollectionInfo;
        }

        public override BaseData<Kind> Create()
        {
            return new CollectionInfoObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CollectionInfo )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public long Count
        {
            get => count_;
            set
            {
                if( count_ != value )
                {
                    count_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CountryObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        string name_ = string.Empty;
        int code_ = 0;
        string alpha2_ = string.Empty;
        string alpha3_ = string.Empty;
        public CountryObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Country;
        }

        public override BaseData<Kind> Create()
        {
            return new CountryObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Country )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Code
        {
            get => code_;
            set
            {
                if( code_ != value )
                {
                    code_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Alpha2
        {
            get => alpha2_;
            set
            {
                if( alpha2_ != value )
                {
                    alpha2_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Alpha3
        {
            get => alpha3_;
            set
            {
                if( alpha3_ != value )
                {
                    alpha3_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CursorInfoObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        int typeCode_ = 0;
        public CursorInfoObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CursorInfo;
        }

        public override BaseData<Kind> Create()
        {
            return new CursorInfoObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CursorInfo )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int TypeCode
        {
            get => typeCode_;
            set
            {
                if( typeCode_ != value )
                {
                    typeCode_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class DateTimeTimeseriesValueObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        DateTime? value_;
        public DateTimeTimeseriesValueObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.DateTimeTimeseriesValue;
        }

        public override BaseData<Kind> Create()
        {
            return new DateTimeTimeseriesValueObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.DateTimeTimeseriesValue )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime? Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class DeviceHostObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        string name_ = string.Empty;
        public DeviceHostObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.DeviceHost;
        }

        public override BaseData<Kind> Create()
        {
            return new DeviceHostObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.DeviceHost )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class DeviceHostConfigurationObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid host_;
        DateTime timestamp_;
        string hostname_ = string.Empty;
        int port_ = 0;
        string queueName_ = string.Empty;
        public DeviceHostConfigurationObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.DeviceHostConfiguration;
        }

        public override BaseData<Kind> Create()
        {
            return new DeviceHostConfigurationObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.DeviceHostConfiguration )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Host
        {
            get => host_;
            set
            {
                if( host_ != value )
                {
                    host_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Hostname
        {
            get => hostname_;
            set
            {
                if( hostname_ != value )
                {
                    hostname_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Port
        {
            get => port_;
            set
            {
                if( port_ != value )
                {
                    port_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string QueueName
        {
            get => queueName_;
            set
            {
                if( queueName_ != value )
                {
                    queueName_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class DoubleTimeseriesValueObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        double? value_;
        public DoubleTimeseriesValueObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.DoubleTimeseriesValue;
        }

        public override BaseData<Kind> Create()
        {
            return new DoubleTimeseriesValueObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.DoubleTimeseriesValue )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class FacilityTypeObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        string name_ = string.Empty;
        public FacilityTypeObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.FacilityType;
        }

        public override BaseData<Kind> Create()
        {
            return new FacilityTypeObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.FacilityType )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class GeoPosition2DTimeseriesValueObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        double? latitude_;
        double? longitude_;
        public GeoPosition2DTimeseriesValueObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GeoPosition2DTimeseriesValue;
        }

        public override BaseData<Kind> Create()
        {
            return new GeoPosition2DTimeseriesValueObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GeoPosition2DTimeseriesValue )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? Latitude
        {
            get => latitude_;
            set
            {
                if( latitude_ != value )
                {
                    latitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? Longitude
        {
            get => longitude_;
            set
            {
                if( longitude_ != value )
                {
                    longitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class GeoPosition3DTimeseriesValueObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        double? latitude_;
        double? longitude_;
        double? altitude_;
        public GeoPosition3DTimeseriesValueObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GeoPosition3DTimeseriesValue;
        }

        public override BaseData<Kind> Create()
        {
            return new GeoPosition3DTimeseriesValueObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GeoPosition3DTimeseriesValue )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? Latitude
        {
            get => latitude_;
            set
            {
                if( latitude_ != value )
                {
                    latitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? Longitude
        {
            get => longitude_;
            set
            {
                if( longitude_ != value )
                {
                    longitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? Altitude
        {
            get => altitude_;
            set
            {
                if( altitude_ != value )
                {
                    altitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class GNSSDeviceCommandObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid gNSSDevice_;
        DateTime timestamp_;
        Types.DeviceCommandSourceType deviceCommandSourceType_ = Types.DeviceCommandSourceType.Unknown;
        Guid deviceCommandSourceId_;
        Guid reply_;
        public GNSSDeviceCommandObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GNSSDeviceCommand;
        }

        public override BaseData<Kind> Create()
        {
            return new GNSSDeviceCommandObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GNSSDeviceCommand )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid GNSSDevice
        {
            get => gNSSDevice_;
            set
            {
                if( gNSSDevice_ != value )
                {
                    gNSSDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.DeviceCommandSourceType DeviceCommandSourceType
        {
            get => deviceCommandSourceType_;
            set
            {
                if( deviceCommandSourceType_ != value )
                {
                    deviceCommandSourceType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid DeviceCommandSourceId
        {
            get => deviceCommandSourceId_;
            set
            {
                if( deviceCommandSourceId_ != value )
                {
                    deviceCommandSourceId_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Reply
        {
            get => reply_;
            set
            {
                if( reply_ != value )
                {
                    reply_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class GNSSDeviceCommandReplyObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid gNSSDevice_;
        DateTime timestamp_;
        Guid command_;
        Types.DeviceCommandReplyStatus status_ = Types.DeviceCommandReplyStatus.Unknown;
        string message_ = string.Empty;
        public GNSSDeviceCommandReplyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GNSSDeviceCommandReply;
        }

        public override BaseData<Kind> Create()
        {
            return new GNSSDeviceCommandReplyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GNSSDeviceCommandReply )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid GNSSDevice
        {
            get => gNSSDevice_;
            set
            {
                if( gNSSDevice_ != value )
                {
                    gNSSDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Command
        {
            get => command_;
            set
            {
                if( command_ != value )
                {
                    command_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.DeviceCommandReplyStatus Status
        {
            get => status_;
            set
            {
                if( status_ != value )
                {
                    status_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Message
        {
            get => message_;
            set
            {
                if( message_ != value )
                {
                    message_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class GNSSDeviceConfigurationObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid gNSSDevice_;
        DateTime timestamp_;
        double defaultLatitude_ = 0.0;
        double defaultLongitude_ = 0.0;
        double defaultAltitude_ = 0.0;
        double latitudeOffset_ = 0.0;
        double longitudeOffset_ = 0.0;
        double altitudeOffset_ = 0.0;
        public GNSSDeviceConfigurationObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GNSSDeviceConfiguration;
        }

        public override BaseData<Kind> Create()
        {
            return new GNSSDeviceConfigurationObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GNSSDeviceConfiguration )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid GNSSDevice
        {
            get => gNSSDevice_;
            set
            {
                if( gNSSDevice_ != value )
                {
                    gNSSDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double DefaultLatitude
        {
            get => defaultLatitude_;
            set
            {
                if( defaultLatitude_ != value )
                {
                    defaultLatitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double DefaultLongitude
        {
            get => defaultLongitude_;
            set
            {
                if( defaultLongitude_ != value )
                {
                    defaultLongitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double DefaultAltitude
        {
            get => defaultAltitude_;
            set
            {
                if( defaultAltitude_ != value )
                {
                    defaultAltitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double LatitudeOffset
        {
            get => latitudeOffset_;
            set
            {
                if( latitudeOffset_ != value )
                {
                    latitudeOffset_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double LongitudeOffset
        {
            get => longitudeOffset_;
            set
            {
                if( longitudeOffset_ != value )
                {
                    longitudeOffset_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double AltitudeOffset
        {
            get => altitudeOffset_;
            set
            {
                if( altitudeOffset_ != value )
                {
                    altitudeOffset_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class GuidTimeseriesValueObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        Guid? value_;
        public GuidTimeseriesValueObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GuidTimeseriesValue;
        }

        public override BaseData<Kind> Create()
        {
            return new GuidTimeseriesValueObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GuidTimeseriesValue )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid? Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class GyroDeviceCommandObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid gyroDevice_;
        DateTime timestamp_;
        Types.DeviceCommandSourceType deviceCommandSourceType_ = Types.DeviceCommandSourceType.Unknown;
        Guid deviceCommandSourceId_;
        Guid reply_;
        public GyroDeviceCommandObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GyroDeviceCommand;
        }

        public override BaseData<Kind> Create()
        {
            return new GyroDeviceCommandObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GyroDeviceCommand )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid GyroDevice
        {
            get => gyroDevice_;
            set
            {
                if( gyroDevice_ != value )
                {
                    gyroDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.DeviceCommandSourceType DeviceCommandSourceType
        {
            get => deviceCommandSourceType_;
            set
            {
                if( deviceCommandSourceType_ != value )
                {
                    deviceCommandSourceType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid DeviceCommandSourceId
        {
            get => deviceCommandSourceId_;
            set
            {
                if( deviceCommandSourceId_ != value )
                {
                    deviceCommandSourceId_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Reply
        {
            get => reply_;
            set
            {
                if( reply_ != value )
                {
                    reply_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class GyroDeviceCommandReplyObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid gyroDevice_;
        DateTime timestamp_;
        Guid command_;
        Types.DeviceCommandReplyStatus status_ = Types.DeviceCommandReplyStatus.Unknown;
        string message_ = string.Empty;
        public GyroDeviceCommandReplyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GyroDeviceCommandReply;
        }

        public override BaseData<Kind> Create()
        {
            return new GyroDeviceCommandReplyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GyroDeviceCommandReply )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid GyroDevice
        {
            get => gyroDevice_;
            set
            {
                if( gyroDevice_ != value )
                {
                    gyroDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Command
        {
            get => command_;
            set
            {
                if( command_ != value )
                {
                    command_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.DeviceCommandReplyStatus Status
        {
            get => status_;
            set
            {
                if( status_ != value )
                {
                    status_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Message
        {
            get => message_;
            set
            {
                if( message_ != value )
                {
                    message_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class GyroDeviceConfigurationObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid gyroDevice_;
        DateTime timestamp_;
        double defaultHeadingTrueNorth_ = 0.0;
        double defaultMagneticTrueNorth_ = 0.0;
        double headingTrueNorthOffset_ = 0.0;
        double headingMagneticNorthOffset_ = 0.0;
        string pitchTransducerName_ = string.Empty;
        string rollTransducerName_ = string.Empty;
        public GyroDeviceConfigurationObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GyroDeviceConfiguration;
        }

        public override BaseData<Kind> Create()
        {
            return new GyroDeviceConfigurationObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GyroDeviceConfiguration )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid GyroDevice
        {
            get => gyroDevice_;
            set
            {
                if( gyroDevice_ != value )
                {
                    gyroDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double DefaultHeadingTrueNorth
        {
            get => defaultHeadingTrueNorth_;
            set
            {
                if( defaultHeadingTrueNorth_ != value )
                {
                    defaultHeadingTrueNorth_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double DefaultMagneticTrueNorth
        {
            get => defaultMagneticTrueNorth_;
            set
            {
                if( defaultMagneticTrueNorth_ != value )
                {
                    defaultMagneticTrueNorth_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double HeadingTrueNorthOffset
        {
            get => headingTrueNorthOffset_;
            set
            {
                if( headingTrueNorthOffset_ != value )
                {
                    headingTrueNorthOffset_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double HeadingMagneticNorthOffset
        {
            get => headingMagneticNorthOffset_;
            set
            {
                if( headingMagneticNorthOffset_ != value )
                {
                    headingMagneticNorthOffset_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string PitchTransducerName
        {
            get => pitchTransducerName_;
            set
            {
                if( pitchTransducerName_ != value )
                {
                    pitchTransducerName_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string RollTransducerName
        {
            get => rollTransducerName_;
            set
            {
                if( rollTransducerName_ != value )
                {
                    rollTransducerName_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public abstract class IdentityObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        protected IdentityObject ( )
        {
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Identity )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CallsignObject : IdentityObject
    {
        string identifier_ = string.Empty;
        public CallsignObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Callsign;
        }

        public override BaseData<Kind> Create()
        {
            return new CallsignObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Callsign )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public string Identifier
        {
            get => identifier_;
            set
            {
                if( identifier_ != value )
                {
                    identifier_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class InternationalMaritimeOrganizationNumberObject : IdentityObject
    {
        long identifier_ = 0;
        public InternationalMaritimeOrganizationNumberObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.InternationalMaritimeOrganizationNumber;
        }

        public override BaseData<Kind> Create()
        {
            return new InternationalMaritimeOrganizationNumberObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.InternationalMaritimeOrganizationNumber )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long Identifier
        {
            get => identifier_;
            set
            {
                if( identifier_ != value )
                {
                    identifier_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class MaritimeMobileServiceIdentityObject : IdentityObject
    {
        long identifier_ = 0;
        public MaritimeMobileServiceIdentityObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.MaritimeMobileServiceIdentity;
        }

        public override BaseData<Kind> Create()
        {
            return new MaritimeMobileServiceIdentityObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.MaritimeMobileServiceIdentity )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long Identifier
        {
            get => identifier_;
            set
            {
                if( identifier_ != value )
                {
                    identifier_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class NameObject : IdentityObject
    {
        string text_ = string.Empty;
        public NameObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Name;
        }

        public override BaseData<Kind> Create()
        {
            return new NameObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Name )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public string Text
        {
            get => text_;
            set
            {
                if( text_ != value )
                {
                    text_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class Int16TimeseriesValueObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        short? value_;
        public Int16TimeseriesValueObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Int16TimeseriesValue;
        }

        public override BaseData<Kind> Create()
        {
            return new Int16TimeseriesValueObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Int16TimeseriesValue )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public short? Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class Int32TimeseriesValueObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        int? value_;
        public Int32TimeseriesValueObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Int32TimeseriesValue;
        }

        public override BaseData<Kind> Create()
        {
            return new Int32TimeseriesValueObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Int32TimeseriesValue )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int? Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class Int64TimeseriesValueObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        long? value_;
        public Int64TimeseriesValueObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Int64TimeseriesValue;
        }

        public override BaseData<Kind> Create()
        {
            return new Int64TimeseriesValueObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Int64TimeseriesValue )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public long? Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public abstract class ItemObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        protected ItemObject ( )
        {
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Item )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class BaseStationObject : ItemObject
    {
        string name_ = string.Empty;
        Guid type_;
        public BaseStationObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.BaseStation;
        }

        public override BaseData<Kind> Create()
        {
            return new BaseStationObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.BaseStation )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Type
        {
            get => type_;
            set
            {
                if( type_ != value )
                {
                    type_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public abstract class DeviceObject : ItemObject
    {
        Guid host_;
        string name_ = string.Empty;
        string description_ = string.Empty;
        Guid enabledTimeseries_;
        protected DeviceObject ( )
        {
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Device )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Host
        {
            get => host_;
            set
            {
                if( host_ != value )
                {
                    host_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Description
        {
            get => description_;
            set
            {
                if( description_ != value )
                {
                    description_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid EnabledTimeseries
        {
            get => enabledTimeseries_;
            set
            {
                if( enabledTimeseries_ != value )
                {
                    enabledTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CameraDeviceObject : DeviceObject
    {
        public CameraDeviceObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CameraDevice;
        }

        public override BaseData<Kind> Create()
        {
            return new CameraDeviceObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CameraDevice )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class GNSSDeviceObject : DeviceObject
    {
        Guid latitudeTimeseries_;
        Guid longitudeTimeseries_;
        Guid altitudeTimeseries_;
        public GNSSDeviceObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GNSSDevice;
        }

        public override BaseData<Kind> Create()
        {
            return new GNSSDeviceObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GNSSDevice )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid LatitudeTimeseries
        {
            get => latitudeTimeseries_;
            set
            {
                if( latitudeTimeseries_ != value )
                {
                    latitudeTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid LongitudeTimeseries
        {
            get => longitudeTimeseries_;
            set
            {
                if( longitudeTimeseries_ != value )
                {
                    longitudeTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid AltitudeTimeseries
        {
            get => altitudeTimeseries_;
            set
            {
                if( altitudeTimeseries_ != value )
                {
                    altitudeTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class GyroDeviceObject : DeviceObject
    {
        Guid headingTrueNorthTimeseries_;
        Guid headingMagneticNorthTimeseries_;
        Guid pitchTimeseries_;
        Guid rateOfTurnTimeseries_;
        Guid rollTimeseries_;
        Guid courseTimeseries_;
        Guid speedTimeseries_;
        Guid gNSSDevice_;
        public GyroDeviceObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GyroDevice;
        }

        public override BaseData<Kind> Create()
        {
            return new GyroDeviceObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GyroDevice )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid HeadingTrueNorthTimeseries
        {
            get => headingTrueNorthTimeseries_;
            set
            {
                if( headingTrueNorthTimeseries_ != value )
                {
                    headingTrueNorthTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid HeadingMagneticNorthTimeseries
        {
            get => headingMagneticNorthTimeseries_;
            set
            {
                if( headingMagneticNorthTimeseries_ != value )
                {
                    headingMagneticNorthTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid PitchTimeseries
        {
            get => pitchTimeseries_;
            set
            {
                if( pitchTimeseries_ != value )
                {
                    pitchTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid RateOfTurnTimeseries
        {
            get => rateOfTurnTimeseries_;
            set
            {
                if( rateOfTurnTimeseries_ != value )
                {
                    rateOfTurnTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid RollTimeseries
        {
            get => rollTimeseries_;
            set
            {
                if( rollTimeseries_ != value )
                {
                    rollTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid CourseTimeseries
        {
            get => courseTimeseries_;
            set
            {
                if( courseTimeseries_ != value )
                {
                    courseTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid SpeedTimeseries
        {
            get => speedTimeseries_;
            set
            {
                if( speedTimeseries_ != value )
                {
                    speedTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid GNSSDevice
        {
            get => gNSSDevice_;
            set
            {
                if( gNSSDevice_ != value )
                {
                    gNSSDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class LineInputDeviceObject : DeviceObject
    {
        public LineInputDeviceObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.LineInputDevice;
        }

        public override BaseData<Kind> Create()
        {
            return new LineInputDeviceObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.LineInputDevice )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class OilSpillDetectorDeviceObject : DeviceObject
    {
        public OilSpillDetectorDeviceObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.OilSpillDetectorDevice;
        }

        public override BaseData<Kind> Create()
        {
            return new OilSpillDetectorDeviceObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.OilSpillDetectorDevice )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class RadioDeviceObject : DeviceObject
    {
        public RadioDeviceObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadioDevice;
        }

        public override BaseData<Kind> Create()
        {
            return new RadioDeviceObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadioDevice )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class RadomeDeviceObject : DeviceObject
    {
        Guid? radar_;
        Guid pressureTimeseries_;
        Guid temperatureTimeseries_;
        Guid dewPointTimeseries_;
        Guid statusTimeseries_;
        public RadomeDeviceObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadomeDevice;
        }

        public override BaseData<Kind> Create()
        {
            return new RadomeDeviceObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadomeDevice )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid? Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid PressureTimeseries
        {
            get => pressureTimeseries_;
            set
            {
                if( pressureTimeseries_ != value )
                {
                    pressureTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid TemperatureTimeseries
        {
            get => temperatureTimeseries_;
            set
            {
                if( temperatureTimeseries_ != value )
                {
                    temperatureTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid DewPointTimeseries
        {
            get => dewPointTimeseries_;
            set
            {
                if( dewPointTimeseries_ != value )
                {
                    dewPointTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid StatusTimeseries
        {
            get => statusTimeseries_;
            set
            {
                if( statusTimeseries_ != value )
                {
                    statusTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public abstract class TrackerDeviceObject : DeviceObject
    {
        protected TrackerDeviceObject ( )
        {
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.TrackerDevice )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class AisDeviceObject : TrackerDeviceObject
    {
        public AisDeviceObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisDevice;
        }

        public override BaseData<Kind> Create()
        {
            return new AisDeviceObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisDevice )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class RadarDeviceObject : TrackerDeviceObject
    {
        Guid saveSettingsTimeseries_;
        Guid powerOnTimeseries_;
        Guid trackingOnTimeseries_;
        Guid radarPulseTimeseries_;
        Guid tuningTimeseries_;
        Guid blankSector1Timeseries_;
        Guid sector1StartTimeseries_;
        Guid sector1EndTimeseries_;
        Guid blankSector2Timeseries_;
        Guid sector2StartTimeseries_;
        Guid sector2EndTimeseries_;
        Guid enableAutomaticFrequencyControlTimeseries_;
        Guid azimuthOffsetTimeseries_;
        Guid enableSensitivityTimeControlTimeseries_;
        Guid automaticSensitivityTimeControlTimeseries_;
        Guid sensitivityTimeControlLevelTimeseries_;
        Guid enableFastTimeConstantTimeseries_;
        Guid fastTimeConstantLevelTimeseries_;
        Guid fastTimeConstantModeTimeseries_;
        Guid latitudeTimeseries_;
        Guid longitudeTimeseries_;
        Guid? radome_;
        Guid? gNSSDevice_;
        public RadarDeviceObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarDevice;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarDeviceObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarDevice )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid SaveSettingsTimeseries
        {
            get => saveSettingsTimeseries_;
            set
            {
                if( saveSettingsTimeseries_ != value )
                {
                    saveSettingsTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid PowerOnTimeseries
        {
            get => powerOnTimeseries_;
            set
            {
                if( powerOnTimeseries_ != value )
                {
                    powerOnTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid TrackingOnTimeseries
        {
            get => trackingOnTimeseries_;
            set
            {
                if( trackingOnTimeseries_ != value )
                {
                    trackingOnTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid RadarPulseTimeseries
        {
            get => radarPulseTimeseries_;
            set
            {
                if( radarPulseTimeseries_ != value )
                {
                    radarPulseTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid TuningTimeseries
        {
            get => tuningTimeseries_;
            set
            {
                if( tuningTimeseries_ != value )
                {
                    tuningTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid BlankSector1Timeseries
        {
            get => blankSector1Timeseries_;
            set
            {
                if( blankSector1Timeseries_ != value )
                {
                    blankSector1Timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Sector1StartTimeseries
        {
            get => sector1StartTimeseries_;
            set
            {
                if( sector1StartTimeseries_ != value )
                {
                    sector1StartTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Sector1EndTimeseries
        {
            get => sector1EndTimeseries_;
            set
            {
                if( sector1EndTimeseries_ != value )
                {
                    sector1EndTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid BlankSector2Timeseries
        {
            get => blankSector2Timeseries_;
            set
            {
                if( blankSector2Timeseries_ != value )
                {
                    blankSector2Timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Sector2StartTimeseries
        {
            get => sector2StartTimeseries_;
            set
            {
                if( sector2StartTimeseries_ != value )
                {
                    sector2StartTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Sector2EndTimeseries
        {
            get => sector2EndTimeseries_;
            set
            {
                if( sector2EndTimeseries_ != value )
                {
                    sector2EndTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid EnableAutomaticFrequencyControlTimeseries
        {
            get => enableAutomaticFrequencyControlTimeseries_;
            set
            {
                if( enableAutomaticFrequencyControlTimeseries_ != value )
                {
                    enableAutomaticFrequencyControlTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid AzimuthOffsetTimeseries
        {
            get => azimuthOffsetTimeseries_;
            set
            {
                if( azimuthOffsetTimeseries_ != value )
                {
                    azimuthOffsetTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid EnableSensitivityTimeControlTimeseries
        {
            get => enableSensitivityTimeControlTimeseries_;
            set
            {
                if( enableSensitivityTimeControlTimeseries_ != value )
                {
                    enableSensitivityTimeControlTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid AutomaticSensitivityTimeControlTimeseries
        {
            get => automaticSensitivityTimeControlTimeseries_;
            set
            {
                if( automaticSensitivityTimeControlTimeseries_ != value )
                {
                    automaticSensitivityTimeControlTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid SensitivityTimeControlLevelTimeseries
        {
            get => sensitivityTimeControlLevelTimeseries_;
            set
            {
                if( sensitivityTimeControlLevelTimeseries_ != value )
                {
                    sensitivityTimeControlLevelTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid EnableFastTimeConstantTimeseries
        {
            get => enableFastTimeConstantTimeseries_;
            set
            {
                if( enableFastTimeConstantTimeseries_ != value )
                {
                    enableFastTimeConstantTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid FastTimeConstantLevelTimeseries
        {
            get => fastTimeConstantLevelTimeseries_;
            set
            {
                if( fastTimeConstantLevelTimeseries_ != value )
                {
                    fastTimeConstantLevelTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid FastTimeConstantModeTimeseries
        {
            get => fastTimeConstantModeTimeseries_;
            set
            {
                if( fastTimeConstantModeTimeseries_ != value )
                {
                    fastTimeConstantModeTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid LatitudeTimeseries
        {
            get => latitudeTimeseries_;
            set
            {
                if( latitudeTimeseries_ != value )
                {
                    latitudeTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid LongitudeTimeseries
        {
            get => longitudeTimeseries_;
            set
            {
                if( longitudeTimeseries_ != value )
                {
                    longitudeTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid? Radome
        {
            get => radome_;
            set
            {
                if( radome_ != value )
                {
                    radome_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid? GNSSDevice
        {
            get => gNSSDevice_;
            set
            {
                if( gNSSDevice_ != value )
                {
                    gNSSDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class WeatherStationDeviceObject : DeviceObject
    {
        Guid barometricPressureTimeseries_;
        Guid airTemperatureTimeseries_;
        Guid waterTemperatureTimeseries_;
        Guid relativeHumidityTimeseries_;
        Guid absoluteHumidityTimeseries_;
        Guid dewPointTimeseries_;
        Guid windDirectionTimeseries_;
        Guid windSpeedTimeseries_;
        Guid gyro_;
        public WeatherStationDeviceObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.WeatherStationDevice;
        }

        public override BaseData<Kind> Create()
        {
            return new WeatherStationDeviceObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.WeatherStationDevice )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid BarometricPressureTimeseries
        {
            get => barometricPressureTimeseries_;
            set
            {
                if( barometricPressureTimeseries_ != value )
                {
                    barometricPressureTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid AirTemperatureTimeseries
        {
            get => airTemperatureTimeseries_;
            set
            {
                if( airTemperatureTimeseries_ != value )
                {
                    airTemperatureTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid WaterTemperatureTimeseries
        {
            get => waterTemperatureTimeseries_;
            set
            {
                if( waterTemperatureTimeseries_ != value )
                {
                    waterTemperatureTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid RelativeHumidityTimeseries
        {
            get => relativeHumidityTimeseries_;
            set
            {
                if( relativeHumidityTimeseries_ != value )
                {
                    relativeHumidityTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid AbsoluteHumidityTimeseries
        {
            get => absoluteHumidityTimeseries_;
            set
            {
                if( absoluteHumidityTimeseries_ != value )
                {
                    absoluteHumidityTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid DewPointTimeseries
        {
            get => dewPointTimeseries_;
            set
            {
                if( dewPointTimeseries_ != value )
                {
                    dewPointTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid WindDirectionTimeseries
        {
            get => windDirectionTimeseries_;
            set
            {
                if( windDirectionTimeseries_ != value )
                {
                    windDirectionTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid WindSpeedTimeseries
        {
            get => windSpeedTimeseries_;
            set
            {
                if( windSpeedTimeseries_ != value )
                {
                    windSpeedTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Gyro
        {
            get => gyro_;
            set
            {
                if( gyro_ != value )
                {
                    gyro_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class FacilityObject : ItemObject
    {
        string name_ = string.Empty;
        Guid type_;
        double longitude_ = 0.0;
        double latitude_ = 0.0;
        double altitude_ = 0.0;
        public FacilityObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Facility;
        }

        public override BaseData<Kind> Create()
        {
            return new FacilityObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Facility )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Type
        {
            get => type_;
            set
            {
                if( type_ != value )
                {
                    type_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Longitude
        {
            get => longitude_;
            set
            {
                if( longitude_ != value )
                {
                    longitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Latitude
        {
            get => latitude_;
            set
            {
                if( latitude_ != value )
                {
                    latitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Altitude
        {
            get => altitude_;
            set
            {
                if( altitude_ != value )
                {
                    altitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public abstract class TrackableItemObject : ItemObject
    {
        protected TrackableItemObject ( )
        {
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.TrackableItem )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class AircraftObject : TrackableItemObject
    {
        string name_ = string.Empty;
        Guid type_;
        public AircraftObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Aircraft;
        }

        public override BaseData<Kind> Create()
        {
            return new AircraftObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Aircraft )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Type
        {
            get => type_;
            set
            {
                if( type_ != value )
                {
                    type_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class AisAidToNavigationObject : TrackableItemObject
    {
        string name_ = string.Empty;
        Guid mMSI_;
        Types.NavigationalAidType navigationalAidType_ = Types.NavigationalAidType.NotSpecified;
        Guid position_;
        bool isVirtual_ = false;
        int toBow_ = 0;
        int toStern_ = 0;
        int toPort_ = 0;
        int toStarboard_ = 0;
        Guid offPositionTimeseries_;
        public AisAidToNavigationObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisAidToNavigation;
        }

        public override BaseData<Kind> Create()
        {
            return new AisAidToNavigationObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisAidToNavigation )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid MMSI
        {
            get => mMSI_;
            set
            {
                if( mMSI_ != value )
                {
                    mMSI_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.NavigationalAidType NavigationalAidType
        {
            get => navigationalAidType_;
            set
            {
                if( navigationalAidType_ != value )
                {
                    navigationalAidType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Position
        {
            get => position_;
            set
            {
                if( position_ != value )
                {
                    position_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool IsVirtual
        {
            get => isVirtual_;
            set
            {
                if( isVirtual_ != value )
                {
                    isVirtual_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int ToBow
        {
            get => toBow_;
            set
            {
                if( toBow_ != value )
                {
                    toBow_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int ToStern
        {
            get => toStern_;
            set
            {
                if( toStern_ != value )
                {
                    toStern_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int ToPort
        {
            get => toPort_;
            set
            {
                if( toPort_ != value )
                {
                    toPort_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int ToStarboard
        {
            get => toStarboard_;
            set
            {
                if( toStarboard_ != value )
                {
                    toStarboard_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid OffPositionTimeseries
        {
            get => offPositionTimeseries_;
            set
            {
                if( offPositionTimeseries_ != value )
                {
                    offPositionTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class VehicleObject : TrackableItemObject
    {
        string name_ = string.Empty;
        Guid type_;
        public VehicleObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Vehicle;
        }

        public override BaseData<Kind> Create()
        {
            return new VehicleObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Vehicle )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Type
        {
            get => type_;
            set
            {
                if( type_ != value )
                {
                    type_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class VesselObject : TrackableItemObject
    {
        string name_ = string.Empty;
        Guid type_;
        int toBow_ = 0;
        int toStern_ = 0;
        int toPort_ = 0;
        int toStarboard_ = 0;
        Guid draughtTimeseries_;
        Guid personsOnBoardTimeseries_;
        public VesselObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Vessel;
        }

        public override BaseData<Kind> Create()
        {
            return new VesselObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Vessel )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Type
        {
            get => type_;
            set
            {
                if( type_ != value )
                {
                    type_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int ToBow
        {
            get => toBow_;
            set
            {
                if( toBow_ != value )
                {
                    toBow_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int ToStern
        {
            get => toStern_;
            set
            {
                if( toStern_ != value )
                {
                    toStern_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int ToPort
        {
            get => toPort_;
            set
            {
                if( toPort_ != value )
                {
                    toPort_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int ToStarboard
        {
            get => toStarboard_;
            set
            {
                if( toStarboard_ != value )
                {
                    toStarboard_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid DraughtTimeseries
        {
            get => draughtTimeseries_;
            set
            {
                if( draughtTimeseries_ != value )
                {
                    draughtTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid PersonsOnBoardTimeseries
        {
            get => personsOnBoardTimeseries_;
            set
            {
                if( personsOnBoardTimeseries_ != value )
                {
                    personsOnBoardTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class ItemIdentityLinkObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid item_;
        Guid identity_;
        DateTime start_;
        DateTime? end_;
        public ItemIdentityLinkObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.ItemIdentityLink;
        }

        public override BaseData<Kind> Create()
        {
            return new ItemIdentityLinkObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.ItemIdentityLink )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Item
        {
            get => item_;
            set
            {
                if( item_ != value )
                {
                    item_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Identity
        {
            get => identity_;
            set
            {
                if( identity_ != value )
                {
                    identity_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Start
        {
            get => start_;
            set
            {
                if( start_ != value )
                {
                    start_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime? End
        {
            get => end_;
            set
            {
                if( end_ != value )
                {
                    end_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class ItemParentChildLinkObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid parent_;
        Guid child_;
        DateTime timestamp_;
        public ItemParentChildLinkObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.ItemParentChildLink;
        }

        public override BaseData<Kind> Create()
        {
            return new ItemParentChildLinkObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.ItemParentChildLink )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Parent
        {
            get => parent_;
            set
            {
                if( parent_ != value )
                {
                    parent_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Child
        {
            get => child_;
            set
            {
                if( child_ != value )
                {
                    child_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class LineInputDeviceCommandObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid lineInputDevice_;
        DateTime timestamp_;
        Types.DeviceCommandSourceType deviceCommandSourceType_ = Types.DeviceCommandSourceType.Unknown;
        Guid deviceCommandSourceId_;
        Guid reply_;
        public LineInputDeviceCommandObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.LineInputDeviceCommand;
        }

        public override BaseData<Kind> Create()
        {
            return new LineInputDeviceCommandObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.LineInputDeviceCommand )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid LineInputDevice
        {
            get => lineInputDevice_;
            set
            {
                if( lineInputDevice_ != value )
                {
                    lineInputDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.DeviceCommandSourceType DeviceCommandSourceType
        {
            get => deviceCommandSourceType_;
            set
            {
                if( deviceCommandSourceType_ != value )
                {
                    deviceCommandSourceType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid DeviceCommandSourceId
        {
            get => deviceCommandSourceId_;
            set
            {
                if( deviceCommandSourceId_ != value )
                {
                    deviceCommandSourceId_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Reply
        {
            get => reply_;
            set
            {
                if( reply_ != value )
                {
                    reply_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class LineInputDeviceCommandReplyObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid lineInputDevice_;
        DateTime timestamp_;
        Guid command_;
        Types.DeviceCommandReplyStatus status_ = Types.DeviceCommandReplyStatus.Unknown;
        string message_ = string.Empty;
        public LineInputDeviceCommandReplyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.LineInputDeviceCommandReply;
        }

        public override BaseData<Kind> Create()
        {
            return new LineInputDeviceCommandReplyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.LineInputDeviceCommandReply )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid LineInputDevice
        {
            get => lineInputDevice_;
            set
            {
                if( lineInputDevice_ != value )
                {
                    lineInputDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Command
        {
            get => command_;
            set
            {
                if( command_ != value )
                {
                    command_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.DeviceCommandReplyStatus Status
        {
            get => status_;
            set
            {
                if( status_ != value )
                {
                    status_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Message
        {
            get => message_;
            set
            {
                if( message_ != value )
                {
                    message_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class LineInputDeviceConfigurationObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid lineInputDevice_;
        DateTime timestamp_;
        bool storeReceivedSentences_ = false;
        bool storeSentMessages_ = false;
        bool storeUnsentMessages_ = false;
        bool nMEA_ = false;
        bool strictNMEA_ = false;
        Types.LineInputDeviceConnectionType connectionType_ = Types.LineInputDeviceConnectionType.Unknown;
        int udpReceivePort_ = 0;
        string udpSendHostname_ = string.Empty;
        int udpSendPort_ = 0;
        string tcpHostname_ = string.Empty;
        int tcpPort_ = 0;
        bool useHttpLogin_ = false;
        string loginHostname_ = string.Empty;
        int loginPort_ = 0;
        string userName_ = string.Empty;
        string password_ = string.Empty;
        string comPort_ = string.Empty;
        int baudRate_ = 0;
        int dataBits_ = 0;
        bool discardNull_ = false;
        bool dtrEnable_ = false;
        Types.Handshake handshake_ = Types.Handshake.None;
        string newLine_ = string.Empty;
        Types.Parity parity_ = Types.Parity.None;
        byte parityReplace_ = 0;
        int readBufferSize_ = 0;
        TimeSpan readTimeout_;
        int receivedBytesThreshold_ = 0;
        bool rtsEnable_ = false;
        Types.StopBits stopBits_ = Types.StopBits.None;
        int writeBufferSize_ = 0;
        TimeSpan writeTimeout_;
        string pairedComPort_ = string.Empty;
        public LineInputDeviceConfigurationObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.LineInputDeviceConfiguration;
        }

        public override BaseData<Kind> Create()
        {
            return new LineInputDeviceConfigurationObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.LineInputDeviceConfiguration )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid LineInputDevice
        {
            get => lineInputDevice_;
            set
            {
                if( lineInputDevice_ != value )
                {
                    lineInputDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool StoreReceivedSentences
        {
            get => storeReceivedSentences_;
            set
            {
                if( storeReceivedSentences_ != value )
                {
                    storeReceivedSentences_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool StoreSentMessages
        {
            get => storeSentMessages_;
            set
            {
                if( storeSentMessages_ != value )
                {
                    storeSentMessages_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool StoreUnsentMessages
        {
            get => storeUnsentMessages_;
            set
            {
                if( storeUnsentMessages_ != value )
                {
                    storeUnsentMessages_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool NMEA
        {
            get => nMEA_;
            set
            {
                if( nMEA_ != value )
                {
                    nMEA_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool StrictNMEA
        {
            get => strictNMEA_;
            set
            {
                if( strictNMEA_ != value )
                {
                    strictNMEA_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.LineInputDeviceConnectionType ConnectionType
        {
            get => connectionType_;
            set
            {
                if( connectionType_ != value )
                {
                    connectionType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int UdpReceivePort
        {
            get => udpReceivePort_;
            set
            {
                if( udpReceivePort_ != value )
                {
                    udpReceivePort_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string UdpSendHostname
        {
            get => udpSendHostname_;
            set
            {
                if( udpSendHostname_ != value )
                {
                    udpSendHostname_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int UdpSendPort
        {
            get => udpSendPort_;
            set
            {
                if( udpSendPort_ != value )
                {
                    udpSendPort_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string TcpHostname
        {
            get => tcpHostname_;
            set
            {
                if( tcpHostname_ != value )
                {
                    tcpHostname_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int TcpPort
        {
            get => tcpPort_;
            set
            {
                if( tcpPort_ != value )
                {
                    tcpPort_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool UseHttpLogin
        {
            get => useHttpLogin_;
            set
            {
                if( useHttpLogin_ != value )
                {
                    useHttpLogin_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string LoginHostname
        {
            get => loginHostname_;
            set
            {
                if( loginHostname_ != value )
                {
                    loginHostname_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int LoginPort
        {
            get => loginPort_;
            set
            {
                if( loginPort_ != value )
                {
                    loginPort_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string UserName
        {
            get => userName_;
            set
            {
                if( userName_ != value )
                {
                    userName_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Password
        {
            get => password_;
            set
            {
                if( password_ != value )
                {
                    password_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string ComPort
        {
            get => comPort_;
            set
            {
                if( comPort_ != value )
                {
                    comPort_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int BaudRate
        {
            get => baudRate_;
            set
            {
                if( baudRate_ != value )
                {
                    baudRate_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int DataBits
        {
            get => dataBits_;
            set
            {
                if( dataBits_ != value )
                {
                    dataBits_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool DiscardNull
        {
            get => discardNull_;
            set
            {
                if( discardNull_ != value )
                {
                    discardNull_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool DtrEnable
        {
            get => dtrEnable_;
            set
            {
                if( dtrEnable_ != value )
                {
                    dtrEnable_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.Handshake Handshake
        {
            get => handshake_;
            set
            {
                if( handshake_ != value )
                {
                    handshake_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string NewLine
        {
            get => newLine_;
            set
            {
                if( newLine_ != value )
                {
                    newLine_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.Parity Parity
        {
            get => parity_;
            set
            {
                if( parity_ != value )
                {
                    parity_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public byte ParityReplace
        {
            get => parityReplace_;
            set
            {
                if( parityReplace_ != value )
                {
                    parityReplace_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int ReadBufferSize
        {
            get => readBufferSize_;
            set
            {
                if( readBufferSize_ != value )
                {
                    readBufferSize_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan ReadTimeout
        {
            get => readTimeout_;
            set
            {
                if( readTimeout_ != value )
                {
                    readTimeout_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int ReceivedBytesThreshold
        {
            get => receivedBytesThreshold_;
            set
            {
                if( receivedBytesThreshold_ != value )
                {
                    receivedBytesThreshold_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool RtsEnable
        {
            get => rtsEnable_;
            set
            {
                if( rtsEnable_ != value )
                {
                    rtsEnable_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.StopBits StopBits
        {
            get => stopBits_;
            set
            {
                if( stopBits_ != value )
                {
                    stopBits_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int WriteBufferSize
        {
            get => writeBufferSize_;
            set
            {
                if( writeBufferSize_ != value )
                {
                    writeBufferSize_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan WriteTimeout
        {
            get => writeTimeout_;
            set
            {
                if( writeTimeout_ != value )
                {
                    writeTimeout_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string PairedComPort
        {
            get => pairedComPort_;
            set
            {
                if( pairedComPort_ != value )
                {
                    pairedComPort_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class LineInputMessageRoutingObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid lineInputDevice_;
        string type_ = string.Empty;
        public LineInputMessageRoutingObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.LineInputMessageRouting;
        }

        public override BaseData<Kind> Create()
        {
            return new LineInputMessageRoutingObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.LineInputMessageRouting )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid LineInputDevice
        {
            get => lineInputDevice_;
            set
            {
                if( lineInputDevice_ != value )
                {
                    lineInputDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Type
        {
            get => type_;
            set
            {
                if( type_ != value )
                {
                    type_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class LineInputMessageRoutingDestinationObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid routing_;
        Guid listener_;
        public LineInputMessageRoutingDestinationObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.LineInputMessageRoutingDestination;
        }

        public override BaseData<Kind> Create()
        {
            return new LineInputMessageRoutingDestinationObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.LineInputMessageRoutingDestination )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Routing
        {
            get => routing_;
            set
            {
                if( routing_ != value )
                {
                    routing_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Listener
        {
            get => listener_;
            set
            {
                if( listener_ != value )
                {
                    listener_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class LineInputWhiteListEntryObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid lineInputDevice_;
        string hostName_ = string.Empty;
        int port_ = 0;
        public LineInputWhiteListEntryObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.LineInputWhiteListEntry;
        }

        public override BaseData<Kind> Create()
        {
            return new LineInputWhiteListEntryObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.LineInputWhiteListEntry )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid LineInputDevice
        {
            get => lineInputDevice_;
            set
            {
                if( lineInputDevice_ != value )
                {
                    lineInputDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string HostName
        {
            get => hostName_;
            set
            {
                if( hostName_ != value )
                {
                    hostName_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Port
        {
            get => port_;
            set
            {
                if( port_ != value )
                {
                    port_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class LogApplicationObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        string name_ = string.Empty;
        string description_ = string.Empty;
        public LogApplicationObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.LogApplication;
        }

        public override BaseData<Kind> Create()
        {
            return new LogApplicationObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.LogApplication )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Description
        {
            get => description_;
            set
            {
                if( description_ != value )
                {
                    description_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class LogApplicationConfigurationObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid application_;
        DateTime timestamp_;
        bool finest_ = false;
        bool finer_ = false;
        bool fine_ = false;
        bool info_ = false;
        bool notice_ = false;
        bool warn_ = false;
        bool error_ = false;
        bool severe_ = false;
        bool critical_ = false;
        bool alert_ = false;
        bool fatal_ = false;
        bool emergency_ = false;
        public LogApplicationConfigurationObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.LogApplicationConfiguration;
        }

        public override BaseData<Kind> Create()
        {
            return new LogApplicationConfigurationObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.LogApplicationConfiguration )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Application
        {
            get => application_;
            set
            {
                if( application_ != value )
                {
                    application_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Finest
        {
            get => finest_;
            set
            {
                if( finest_ != value )
                {
                    finest_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Finer
        {
            get => finer_;
            set
            {
                if( finer_ != value )
                {
                    finer_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Fine
        {
            get => fine_;
            set
            {
                if( fine_ != value )
                {
                    fine_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Info
        {
            get => info_;
            set
            {
                if( info_ != value )
                {
                    info_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Notice
        {
            get => notice_;
            set
            {
                if( notice_ != value )
                {
                    notice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Warn
        {
            get => warn_;
            set
            {
                if( warn_ != value )
                {
                    warn_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Error
        {
            get => error_;
            set
            {
                if( error_ != value )
                {
                    error_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Severe
        {
            get => severe_;
            set
            {
                if( severe_ != value )
                {
                    severe_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Critical
        {
            get => critical_;
            set
            {
                if( critical_ != value )
                {
                    critical_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Alert
        {
            get => alert_;
            set
            {
                if( alert_ != value )
                {
                    alert_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Fatal
        {
            get => fatal_;
            set
            {
                if( fatal_ != value )
                {
                    fatal_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Emergency
        {
            get => emergency_;
            set
            {
                if( emergency_ != value )
                {
                    emergency_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class LogHostObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        string computerName_ = string.Empty;
        string description_ = string.Empty;
        public LogHostObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.LogHost;
        }

        public override BaseData<Kind> Create()
        {
            return new LogHostObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.LogHost )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string ComputerName
        {
            get => computerName_;
            set
            {
                if( computerName_ != value )
                {
                    computerName_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Description
        {
            get => description_;
            set
            {
                if( description_ != value )
                {
                    description_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class LogHostConfigurationObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid host_;
        DateTime timestamp_;
        bool finest_ = false;
        bool finer_ = false;
        bool fine_ = false;
        bool info_ = false;
        bool notice_ = false;
        bool warn_ = false;
        bool error_ = false;
        bool severe_ = false;
        bool critical_ = false;
        bool alert_ = false;
        bool fatal_ = false;
        bool emergency_ = false;
        public LogHostConfigurationObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.LogHostConfiguration;
        }

        public override BaseData<Kind> Create()
        {
            return new LogHostConfigurationObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.LogHostConfiguration )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Host
        {
            get => host_;
            set
            {
                if( host_ != value )
                {
                    host_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Finest
        {
            get => finest_;
            set
            {
                if( finest_ != value )
                {
                    finest_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Finer
        {
            get => finer_;
            set
            {
                if( finer_ != value )
                {
                    finer_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Fine
        {
            get => fine_;
            set
            {
                if( fine_ != value )
                {
                    fine_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Info
        {
            get => info_;
            set
            {
                if( info_ != value )
                {
                    info_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Notice
        {
            get => notice_;
            set
            {
                if( notice_ != value )
                {
                    notice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Warn
        {
            get => warn_;
            set
            {
                if( warn_ != value )
                {
                    warn_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Error
        {
            get => error_;
            set
            {
                if( error_ != value )
                {
                    error_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Severe
        {
            get => severe_;
            set
            {
                if( severe_ != value )
                {
                    severe_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Critical
        {
            get => critical_;
            set
            {
                if( critical_ != value )
                {
                    critical_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Alert
        {
            get => alert_;
            set
            {
                if( alert_ != value )
                {
                    alert_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Fatal
        {
            get => fatal_;
            set
            {
                if( fatal_ != value )
                {
                    fatal_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Emergency
        {
            get => emergency_;
            set
            {
                if( emergency_ != value )
                {
                    emergency_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class LogLocationObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        string fileName_ = string.Empty;
        int lineNumber_ = 0;
        string namespace_ = string.Empty;
        string className_ = string.Empty;
        string methodName_ = string.Empty;
        public LogLocationObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.LogLocation;
        }

        public override BaseData<Kind> Create()
        {
            return new LogLocationObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.LogLocation )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string FileName
        {
            get => fileName_;
            set
            {
                if( fileName_ != value )
                {
                    fileName_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int LineNumber
        {
            get => lineNumber_;
            set
            {
                if( lineNumber_ != value )
                {
                    lineNumber_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Namespace
        {
            get => namespace_;
            set
            {
                if( namespace_ != value )
                {
                    namespace_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string ClassName
        {
            get => className_;
            set
            {
                if( className_ != value )
                {
                    className_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string MethodName
        {
            get => methodName_;
            set
            {
                if( methodName_ != value )
                {
                    methodName_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class LogProcessObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid application_;
        Guid host_;
        DateTime started_;
        DateTime? stopped_;
        long processId_ = 0;
        string path_ = string.Empty;
        string identity_ = string.Empty;
        public LogProcessObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.LogProcess;
        }

        public override BaseData<Kind> Create()
        {
            return new LogProcessObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.LogProcess )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Application
        {
            get => application_;
            set
            {
                if( application_ != value )
                {
                    application_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Host
        {
            get => host_;
            set
            {
                if( host_ != value )
                {
                    host_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Started
        {
            get => started_;
            set
            {
                if( started_ != value )
                {
                    started_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime? Stopped
        {
            get => stopped_;
            set
            {
                if( stopped_ != value )
                {
                    stopped_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public long ProcessId
        {
            get => processId_;
            set
            {
                if( processId_ != value )
                {
                    processId_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Path
        {
            get => path_;
            set
            {
                if( path_ != value )
                {
                    path_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Identity
        {
            get => identity_;
            set
            {
                if( identity_ != value )
                {
                    identity_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class LogRecordObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid thread_;
        long sequenceNumber_ = 0;
        Types.LogLevel level_ = Types.LogLevel.Unknown;
        DateTime timestamp_;
        int depth_ = 0;
        Guid location_;
        string message_ = string.Empty;
        string exceptionString_ = string.Empty;
        byte[] propertiesData_ = Array.Empty<byte>();
        public LogRecordObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.LogRecord;
        }

        public override BaseData<Kind> Create()
        {
            return new LogRecordObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.LogRecord )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Thread
        {
            get => thread_;
            set
            {
                if( thread_ != value )
                {
                    thread_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public long SequenceNumber
        {
            get => sequenceNumber_;
            set
            {
                if( sequenceNumber_ != value )
                {
                    sequenceNumber_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.LogLevel Level
        {
            get => level_;
            set
            {
                if( level_ != value )
                {
                    level_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Depth
        {
            get => depth_;
            set
            {
                if( depth_ != value )
                {
                    depth_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Location
        {
            get => location_;
            set
            {
                if( location_ != value )
                {
                    location_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Message
        {
            get => message_;
            set
            {
                if( message_ != value )
                {
                    message_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string ExceptionString
        {
            get => exceptionString_;
            set
            {
                if( exceptionString_ != value )
                {
                    exceptionString_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public byte[] PropertiesData
        {
            get => propertiesData_;
            set
            {
                if( propertiesData_ != value )
                {
                    propertiesData_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class LogThreadObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid process_;
        DateTime started_;
        DateTime? stopped_;
        long threadId_ = 0;
        string name_ = string.Empty;
        public LogThreadObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.LogThread;
        }

        public override BaseData<Kind> Create()
        {
            return new LogThreadObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.LogThread )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Process
        {
            get => process_;
            set
            {
                if( process_ != value )
                {
                    process_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Started
        {
            get => started_;
            set
            {
                if( started_ != value )
                {
                    started_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime? Stopped
        {
            get => stopped_;
            set
            {
                if( stopped_ != value )
                {
                    stopped_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public long ThreadId
        {
            get => threadId_;
            set
            {
                if( threadId_ != value )
                {
                    threadId_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class LogTraceEntryObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid thread_;
        long sequenceNumber_ = 0;
        Guid location_;
        int depth_ = 0;
        DateTime entered_;
        DateTime? ended_;
        public LogTraceEntryObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.LogTraceEntry;
        }

        public override BaseData<Kind> Create()
        {
            return new LogTraceEntryObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.LogTraceEntry )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Thread
        {
            get => thread_;
            set
            {
                if( thread_ != value )
                {
                    thread_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public long SequenceNumber
        {
            get => sequenceNumber_;
            set
            {
                if( sequenceNumber_ != value )
                {
                    sequenceNumber_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Location
        {
            get => location_;
            set
            {
                if( location_ != value )
                {
                    location_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Depth
        {
            get => depth_;
            set
            {
                if( depth_ != value )
                {
                    depth_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Entered
        {
            get => entered_;
            set
            {
                if( entered_ != value )
                {
                    entered_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime? Ended
        {
            get => ended_;
            set
            {
                if( ended_ != value )
                {
                    ended_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class MapElementObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid item_;
        Types.MapElementType elementType_ = Types.MapElementType.Unknown;
        double latitude_ = 0.0;
        double longitude_ = 0.0;
        double angle_ = 0.0;
        double left_ = 0.0;
        double top_ = 0.0;
        double width_ = 0.0;
        double height_ = 0.0;
        string label_ = string.Empty;
        byte[] data_ = Array.Empty<byte>();
        public MapElementObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.MapElement;
        }

        public override BaseData<Kind> Create()
        {
            return new MapElementObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.MapElement )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Item
        {
            get => item_;
            set
            {
                if( item_ != value )
                {
                    item_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.MapElementType ElementType
        {
            get => elementType_;
            set
            {
                if( elementType_ != value )
                {
                    elementType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Latitude
        {
            get => latitude_;
            set
            {
                if( latitude_ != value )
                {
                    latitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Longitude
        {
            get => longitude_;
            set
            {
                if( longitude_ != value )
                {
                    longitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Angle
        {
            get => angle_;
            set
            {
                if( angle_ != value )
                {
                    angle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Left
        {
            get => left_;
            set
            {
                if( left_ != value )
                {
                    left_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Top
        {
            get => top_;
            set
            {
                if( top_ != value )
                {
                    top_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Width
        {
            get => width_;
            set
            {
                if( width_ != value )
                {
                    width_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Height
        {
            get => height_;
            set
            {
                if( height_ != value )
                {
                    height_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Label
        {
            get => label_;
            set
            {
                if( label_ != value )
                {
                    label_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public byte[] Data
        {
            get => data_;
            set
            {
                if( data_ != value )
                {
                    data_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class MapInfoObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        int scale_ = 0;
        double latitude_ = 0.0;
        double longitude_ = 0.0;
        double northWestLatitude_ = 0.0;
        double northWestLongitude_ = 0.0;
        double southEastLatitude_ = 0.0;
        double southEastLongitude_ = 0.0;
        byte[] image_ = Array.Empty<byte>();
        public MapInfoObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.MapInfo;
        }

        public override BaseData<Kind> Create()
        {
            return new MapInfoObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.MapInfo )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Scale
        {
            get => scale_;
            set
            {
                if( scale_ != value )
                {
                    scale_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Latitude
        {
            get => latitude_;
            set
            {
                if( latitude_ != value )
                {
                    latitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Longitude
        {
            get => longitude_;
            set
            {
                if( longitude_ != value )
                {
                    longitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double NorthWestLatitude
        {
            get => northWestLatitude_;
            set
            {
                if( northWestLatitude_ != value )
                {
                    northWestLatitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double NorthWestLongitude
        {
            get => northWestLongitude_;
            set
            {
                if( northWestLongitude_ != value )
                {
                    northWestLongitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double SouthEastLatitude
        {
            get => southEastLatitude_;
            set
            {
                if( southEastLatitude_ != value )
                {
                    southEastLatitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double SouthEastLongitude
        {
            get => southEastLongitude_;
            set
            {
                if( southEastLongitude_ != value )
                {
                    southEastLongitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public byte[] Image
        {
            get => image_;
            set
            {
                if( image_ != value )
                {
                    image_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class MapServiceOptionsObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        DateTime timestamp_;
        string ipAddress_ = string.Empty;
        int port_ = 0;
        double imageScaleFactorX_ = 0.0;
        double imageOffsetX_ = 0.0;
        double imageScaleFactorY_ = 0.0;
        double imageOffsetY_ = 0.0;
        public MapServiceOptionsObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.MapServiceOptions;
        }

        public override BaseData<Kind> Create()
        {
            return new MapServiceOptionsObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.MapServiceOptions )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string IpAddress
        {
            get => ipAddress_;
            set
            {
                if( ipAddress_ != value )
                {
                    ipAddress_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Port
        {
            get => port_;
            set
            {
                if( port_ != value )
                {
                    port_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double ImageScaleFactorX
        {
            get => imageScaleFactorX_;
            set
            {
                if( imageScaleFactorX_ != value )
                {
                    imageScaleFactorX_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double ImageOffsetX
        {
            get => imageOffsetX_;
            set
            {
                if( imageOffsetX_ != value )
                {
                    imageOffsetX_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double ImageScaleFactorY
        {
            get => imageScaleFactorY_;
            set
            {
                if( imageScaleFactorY_ != value )
                {
                    imageScaleFactorY_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double ImageOffsetY
        {
            get => imageOffsetY_;
            set
            {
                if( imageOffsetY_ != value )
                {
                    imageOffsetY_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class MaritimeIdentificationDigitsObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        int code_ = 0;
        Guid country_;
        public MaritimeIdentificationDigitsObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.MaritimeIdentificationDigits;
        }

        public override BaseData<Kind> Create()
        {
            return new MaritimeIdentificationDigitsObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.MaritimeIdentificationDigits )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Code
        {
            get => code_;
            set
            {
                if( code_ != value )
                {
                    code_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Country
        {
            get => country_;
            set
            {
                if( country_ != value )
                {
                    country_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class MediaProxySessionObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid service_;
        string name_ = string.Empty;
        Guid enabledTimeseries_;
        public MediaProxySessionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.MediaProxySession;
        }

        public override BaseData<Kind> Create()
        {
            return new MediaProxySessionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.MediaProxySession )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Service
        {
            get => service_;
            set
            {
                if( service_ != value )
                {
                    service_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid EnabledTimeseries
        {
            get => enabledTimeseries_;
            set
            {
                if( enabledTimeseries_ != value )
                {
                    enabledTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class MediaProxySessionFileObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid proxySession_;
        DateTime timestamp_;
        string streamName_ = string.Empty;
        public MediaProxySessionFileObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.MediaProxySessionFile;
        }

        public override BaseData<Kind> Create()
        {
            return new MediaProxySessionFileObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.MediaProxySessionFile )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid ProxySession
        {
            get => proxySession_;
            set
            {
                if( proxySession_ != value )
                {
                    proxySession_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string StreamName
        {
            get => streamName_;
            set
            {
                if( streamName_ != value )
                {
                    streamName_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class MediaProxySessionOptionsObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid proxySession_;
        DateTime timestamp_;
        string sourceStreamUrl_ = string.Empty;
        string streamName_ = string.Empty;
        Types.MediaProxySessionMode mode_ = Types.MediaProxySessionMode.Unknown;
        int tunnelOverHTTPPortNumber_ = 0;
        string username_ = string.Empty;
        string password_ = string.Empty;
        int recorderPortNumber_ = 0;
        Types.MediaProxySessionType sessionType_ = Types.MediaProxySessionType.Unknown;
        TimeSpan maxFileTime_;
        TimeSpan maxFileRetention_;
        string videoDirectory_ = string.Empty;
        public MediaProxySessionOptionsObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.MediaProxySessionOptions;
        }

        public override BaseData<Kind> Create()
        {
            return new MediaProxySessionOptionsObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.MediaProxySessionOptions )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid ProxySession
        {
            get => proxySession_;
            set
            {
                if( proxySession_ != value )
                {
                    proxySession_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string SourceStreamUrl
        {
            get => sourceStreamUrl_;
            set
            {
                if( sourceStreamUrl_ != value )
                {
                    sourceStreamUrl_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string StreamName
        {
            get => streamName_;
            set
            {
                if( streamName_ != value )
                {
                    streamName_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.MediaProxySessionMode Mode
        {
            get => mode_;
            set
            {
                if( mode_ != value )
                {
                    mode_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int TunnelOverHTTPPortNumber
        {
            get => tunnelOverHTTPPortNumber_;
            set
            {
                if( tunnelOverHTTPPortNumber_ != value )
                {
                    tunnelOverHTTPPortNumber_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Username
        {
            get => username_;
            set
            {
                if( username_ != value )
                {
                    username_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Password
        {
            get => password_;
            set
            {
                if( password_ != value )
                {
                    password_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int RecorderPortNumber
        {
            get => recorderPortNumber_;
            set
            {
                if( recorderPortNumber_ != value )
                {
                    recorderPortNumber_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.MediaProxySessionType SessionType
        {
            get => sessionType_;
            set
            {
                if( sessionType_ != value )
                {
                    sessionType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan MaxFileTime
        {
            get => maxFileTime_;
            set
            {
                if( maxFileTime_ != value )
                {
                    maxFileTime_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan MaxFileRetention
        {
            get => maxFileRetention_;
            set
            {
                if( maxFileRetention_ != value )
                {
                    maxFileRetention_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string VideoDirectory
        {
            get => videoDirectory_;
            set
            {
                if( videoDirectory_ != value )
                {
                    videoDirectory_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class MediaServiceObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid enabledTimeseries_;
        public MediaServiceObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.MediaService;
        }

        public override BaseData<Kind> Create()
        {
            return new MediaServiceObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.MediaService )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid EnabledTimeseries
        {
            get => enabledTimeseries_;
            set
            {
                if( enabledTimeseries_ != value )
                {
                    enabledTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class MediaServiceOptionsObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid mediaService_;
        DateTime timestamp_;
        int rtspPortNumber_ = 0;
        int httpPortNumber_ = 0;
        public MediaServiceOptionsObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.MediaServiceOptions;
        }

        public override BaseData<Kind> Create()
        {
            return new MediaServiceOptionsObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.MediaServiceOptions )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid MediaService
        {
            get => mediaService_;
            set
            {
                if( mediaService_ != value )
                {
                    mediaService_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int RtspPortNumber
        {
            get => rtspPortNumber_;
            set
            {
                if( rtspPortNumber_ != value )
                {
                    rtspPortNumber_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int HttpPortNumber
        {
            get => httpPortNumber_;
            set
            {
                if( httpPortNumber_ != value )
                {
                    httpPortNumber_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public abstract class NamespaceElementObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid namespace_;
        string name_ = string.Empty;
        string description_ = string.Empty;
        protected NamespaceElementObject ( )
        {
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.NamespaceElement )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Namespace
        {
            get => namespace_;
            set
            {
                if( namespace_ != value )
                {
                    namespace_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Description
        {
            get => description_;
            set
            {
                if( description_ != value )
                {
                    description_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class ElementTypeObject : NamespaceElementObject
    {
        public ElementTypeObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.ElementType;
        }

        public override BaseData<Kind> Create()
        {
            return new ElementTypeObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.ElementType )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class NamespaceObject : NamespaceElementObject
    {
        public NamespaceObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Namespace;
        }

        public override BaseData<Kind> Create()
        {
            return new NamespaceObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Namespace )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class OilSpillObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid oilSpillDetector_;
        DateTime timestamp_;
        double oilArea_ = 0.0;
        byte[] shape_ = Array.Empty<byte>();
        byte[] bSI_ = Array.Empty<byte>();
        byte[] oil_ = Array.Empty<byte>();
        byte[] trace_ = Array.Empty<byte>();
        public OilSpillObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.OilSpill;
        }

        public override BaseData<Kind> Create()
        {
            return new OilSpillObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.OilSpill )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid OilSpillDetector
        {
            get => oilSpillDetector_;
            set
            {
                if( oilSpillDetector_ != value )
                {
                    oilSpillDetector_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double OilArea
        {
            get => oilArea_;
            set
            {
                if( oilArea_ != value )
                {
                    oilArea_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public byte[] Shape
        {
            get => shape_;
            set
            {
                if( shape_ != value )
                {
                    shape_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public byte[] BSI
        {
            get => bSI_;
            set
            {
                if( bSI_ != value )
                {
                    bSI_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public byte[] Oil
        {
            get => oil_;
            set
            {
                if( oil_ != value )
                {
                    oil_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public byte[] Trace
        {
            get => trace_;
            set
            {
                if( trace_ != value )
                {
                    trace_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class OilSpillDetectorCommandObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid oilSpillDetector_;
        DateTime timestamp_;
        Types.DeviceCommandSourceType deviceCommandSourceType_ = Types.DeviceCommandSourceType.Unknown;
        Guid deviceCommandSourceId_;
        Guid reply_;
        public OilSpillDetectorCommandObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.OilSpillDetectorCommand;
        }

        public override BaseData<Kind> Create()
        {
            return new OilSpillDetectorCommandObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.OilSpillDetectorCommand )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid OilSpillDetector
        {
            get => oilSpillDetector_;
            set
            {
                if( oilSpillDetector_ != value )
                {
                    oilSpillDetector_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.DeviceCommandSourceType DeviceCommandSourceType
        {
            get => deviceCommandSourceType_;
            set
            {
                if( deviceCommandSourceType_ != value )
                {
                    deviceCommandSourceType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid DeviceCommandSourceId
        {
            get => deviceCommandSourceId_;
            set
            {
                if( deviceCommandSourceId_ != value )
                {
                    deviceCommandSourceId_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Reply
        {
            get => reply_;
            set
            {
                if( reply_ != value )
                {
                    reply_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class OilSpillDetectorCommandReplyObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid oilSpillDetector_;
        DateTime timestamp_;
        Guid command_;
        Types.DeviceCommandReplyStatus status_ = Types.DeviceCommandReplyStatus.Unknown;
        string message_ = string.Empty;
        public OilSpillDetectorCommandReplyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.OilSpillDetectorCommandReply;
        }

        public override BaseData<Kind> Create()
        {
            return new OilSpillDetectorCommandReplyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.OilSpillDetectorCommandReply )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid OilSpillDetector
        {
            get => oilSpillDetector_;
            set
            {
                if( oilSpillDetector_ != value )
                {
                    oilSpillDetector_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Command
        {
            get => command_;
            set
            {
                if( command_ != value )
                {
                    command_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.DeviceCommandReplyStatus Status
        {
            get => status_;
            set
            {
                if( status_ != value )
                {
                    status_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Message
        {
            get => message_;
            set
            {
                if( message_ != value )
                {
                    message_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class OilSpillDetectorConfigurationObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid oilSpillDetector_;
        DateTime timestamp_;
        double range_ = 0.0;
        double startAngle_ = 0.0;
        double endAngle_ = 0.0;
        double startRange_ = 0.0;
        double endRange_ = 0.0;
        int updateRate_ = 0;
        TimeSpan statusSendTime_;
        bool drawBorder_ = false;
        byte[] colors_ = Array.Empty<byte>();
        bool sendToServer_ = false;
        string directory_ = string.Empty;
        bool transparentWater_ = false;
        bool savePictures_ = false;
        bool sendAsTarget_ = false;
        bool writeLog_ = false;
        string targetFilePrefix_ = string.Empty;
        Guid targetMMSI_;
        double latitude_ = 0.0;
        double longitude_ = 0.0;
        bool testSourceEnabled_ = false;
        string proxyServer_ = string.Empty;
        bool useProxyServer_ = false;
        public OilSpillDetectorConfigurationObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.OilSpillDetectorConfiguration;
        }

        public override BaseData<Kind> Create()
        {
            return new OilSpillDetectorConfigurationObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.OilSpillDetectorConfiguration )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid OilSpillDetector
        {
            get => oilSpillDetector_;
            set
            {
                if( oilSpillDetector_ != value )
                {
                    oilSpillDetector_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Range
        {
            get => range_;
            set
            {
                if( range_ != value )
                {
                    range_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double StartAngle
        {
            get => startAngle_;
            set
            {
                if( startAngle_ != value )
                {
                    startAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double EndAngle
        {
            get => endAngle_;
            set
            {
                if( endAngle_ != value )
                {
                    endAngle_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double StartRange
        {
            get => startRange_;
            set
            {
                if( startRange_ != value )
                {
                    startRange_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double EndRange
        {
            get => endRange_;
            set
            {
                if( endRange_ != value )
                {
                    endRange_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int UpdateRate
        {
            get => updateRate_;
            set
            {
                if( updateRate_ != value )
                {
                    updateRate_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan StatusSendTime
        {
            get => statusSendTime_;
            set
            {
                if( statusSendTime_ != value )
                {
                    statusSendTime_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool DrawBorder
        {
            get => drawBorder_;
            set
            {
                if( drawBorder_ != value )
                {
                    drawBorder_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public byte[] Colors
        {
            get => colors_;
            set
            {
                if( colors_ != value )
                {
                    colors_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool SendToServer
        {
            get => sendToServer_;
            set
            {
                if( sendToServer_ != value )
                {
                    sendToServer_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Directory
        {
            get => directory_;
            set
            {
                if( directory_ != value )
                {
                    directory_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool TransparentWater
        {
            get => transparentWater_;
            set
            {
                if( transparentWater_ != value )
                {
                    transparentWater_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool SavePictures
        {
            get => savePictures_;
            set
            {
                if( savePictures_ != value )
                {
                    savePictures_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool SendAsTarget
        {
            get => sendAsTarget_;
            set
            {
                if( sendAsTarget_ != value )
                {
                    sendAsTarget_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool WriteLog
        {
            get => writeLog_;
            set
            {
                if( writeLog_ != value )
                {
                    writeLog_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string TargetFilePrefix
        {
            get => targetFilePrefix_;
            set
            {
                if( targetFilePrefix_ != value )
                {
                    targetFilePrefix_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid TargetMMSI
        {
            get => targetMMSI_;
            set
            {
                if( targetMMSI_ != value )
                {
                    targetMMSI_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Latitude
        {
            get => latitude_;
            set
            {
                if( latitude_ != value )
                {
                    latitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Longitude
        {
            get => longitude_;
            set
            {
                if( longitude_ != value )
                {
                    longitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool TestSourceEnabled
        {
            get => testSourceEnabled_;
            set
            {
                if( testSourceEnabled_ != value )
                {
                    testSourceEnabled_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string ProxyServer
        {
            get => proxyServer_;
            set
            {
                if( proxyServer_ != value )
                {
                    proxyServer_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool UseProxyServer
        {
            get => useProxyServer_;
            set
            {
                if( useProxyServer_ != value )
                {
                    useProxyServer_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class Position2DTimeseriesValueObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        double? x_;
        double? y_;
        public Position2DTimeseriesValueObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Position2DTimeseriesValue;
        }

        public override BaseData<Kind> Create()
        {
            return new Position2DTimeseriesValueObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Position2DTimeseriesValue )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? X
        {
            get => x_;
            set
            {
                if( x_ != value )
                {
                    x_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? Y
        {
            get => y_;
            set
            {
                if( y_ != value )
                {
                    y_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class Position3DTimeseriesValueObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        double? x_;
        double? y_;
        double? z_;
        public Position3DTimeseriesValueObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Position3DTimeseriesValue;
        }

        public override BaseData<Kind> Create()
        {
            return new Position3DTimeseriesValueObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Position3DTimeseriesValue )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? X
        {
            get => x_;
            set
            {
                if( x_ != value )
                {
                    x_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? Y
        {
            get => y_;
            set
            {
                if( y_ != value )
                {
                    y_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? Z
        {
            get => z_;
            set
            {
                if( z_ != value )
                {
                    z_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class ProcessTrackValueResultObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        bool createdNewTrack_ = false;
        Guid trackId_;
        public ProcessTrackValueResultObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.ProcessTrackValueResult;
        }

        public override BaseData<Kind> Create()
        {
            return new ProcessTrackValueResultObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.ProcessTrackValueResult )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool CreatedNewTrack
        {
            get => createdNewTrack_;
            set
            {
                if( createdNewTrack_ != value )
                {
                    createdNewTrack_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid TrackId
        {
            get => trackId_;
            set
            {
                if( trackId_ != value )
                {
                    trackId_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public abstract class PropertyObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid element_;
        Guid definition_;
        protected PropertyObject ( )
        {
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Property )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Element
        {
            get => element_;
            set
            {
                if( element_ != value )
                {
                    element_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Definition
        {
            get => definition_;
            set
            {
                if( definition_ != value )
                {
                    definition_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class BinaryPropertyObject : PropertyObject
    {
        byte[] value_ = Array.Empty<byte>();
        public BinaryPropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.BinaryProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new BinaryPropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.BinaryProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public byte[] Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class BooleanPropertyObject : PropertyObject
    {
        bool value_ = false;
        public BooleanPropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.BooleanProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new BooleanPropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.BooleanProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public bool Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class BytePropertyObject : PropertyObject
    {
        byte value_ = 0;
        public BytePropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.ByteProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new BytePropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.ByteProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public byte Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class DateTimePropertyObject : PropertyObject
    {
        DateTime value_;
        public DateTimePropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.DateTimeProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new DateTimePropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.DateTimeProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public DateTime Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class DoublePropertyObject : PropertyObject
    {
        double value_ = 0.0;
        public DoublePropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.DoubleProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new DoublePropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.DoubleProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public double Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class GuidPropertyObject : PropertyObject
    {
        Guid value_;
        public GuidPropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GuidProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new GuidPropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GuidProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class Int16PropertyObject : PropertyObject
    {
        short value_ = 0;
        public Int16PropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Int16Property;
        }

        public override BaseData<Kind> Create()
        {
            return new Int16PropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Int16Property )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public short Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class Int32PropertyObject : PropertyObject
    {
        int value_ = 0;
        public Int32PropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Int32Property;
        }

        public override BaseData<Kind> Create()
        {
            return new Int32PropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Int32Property )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public int Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class Int64PropertyObject : PropertyObject
    {
        long value_ = 0;
        public Int64PropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Int64Property;
        }

        public override BaseData<Kind> Create()
        {
            return new Int64PropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Int64Property )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class ReferencePropertyObject : PropertyObject
    {
        Guid value_;
        public ReferencePropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.ReferenceProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new ReferencePropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.ReferenceProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class SBytePropertyObject : PropertyObject
    {
        sbyte value_ = 0;
        public SBytePropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.SByteProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new SBytePropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.SByteProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public sbyte Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class SinglePropertyObject : PropertyObject
    {
        float value_ = 0.0f;
        public SinglePropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.SingleProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new SinglePropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.SingleProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public float Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class StringPropertyObject : PropertyObject
    {
        string value_ = string.Empty;
        public StringPropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.StringProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new StringPropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.StringProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public string Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public abstract class TimeseriesPropertyObject : PropertyObject
    {
        protected TimeseriesPropertyObject ( )
        {
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.TimeseriesProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class BinaryTimeseriesPropertyObject : TimeseriesPropertyObject
    {
        Guid timeseries_;
        public BinaryTimeseriesPropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.BinaryTimeseriesProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new BinaryTimeseriesPropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.BinaryTimeseriesProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class BooleanTimeseriesPropertyObject : TimeseriesPropertyObject
    {
        Guid timeseries_;
        public BooleanTimeseriesPropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.BooleanTimeseriesProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new BooleanTimeseriesPropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.BooleanTimeseriesProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class ByteTimeseriesPropertyObject : TimeseriesPropertyObject
    {
        Guid timeseries_;
        public ByteTimeseriesPropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.ByteTimeseriesProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new ByteTimeseriesPropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.ByteTimeseriesProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class DateTimeTimeseriesPropertyObject : TimeseriesPropertyObject
    {
        Guid timeseries_;
        public DateTimeTimeseriesPropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.DateTimeTimeseriesProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new DateTimeTimeseriesPropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.DateTimeTimeseriesProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class DoubleTimeseriesPropertyObject : TimeseriesPropertyObject
    {
        Guid timeseries_;
        public DoubleTimeseriesPropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.DoubleTimeseriesProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new DoubleTimeseriesPropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.DoubleTimeseriesProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class GuidTimeseriesPropertyObject : TimeseriesPropertyObject
    {
        Guid timeseries_;
        public GuidTimeseriesPropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GuidTimeseriesProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new GuidTimeseriesPropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GuidTimeseriesProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class Int16TimeseriesPropertyObject : TimeseriesPropertyObject
    {
        Guid timeseries_;
        public Int16TimeseriesPropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Int16TimeseriesProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new Int16TimeseriesPropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Int16TimeseriesProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class Int32TimeseriesPropertyObject : TimeseriesPropertyObject
    {
        Guid timeseries_;
        public Int32TimeseriesPropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Int32TimeseriesProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new Int32TimeseriesPropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Int32TimeseriesProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class Int64TimeseriesPropertyObject : TimeseriesPropertyObject
    {
        Guid timeseries_;
        public Int64TimeseriesPropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Int64TimeseriesProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new Int64TimeseriesPropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Int64TimeseriesProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class ReferenceTimeseriesPropertyObject : TimeseriesPropertyObject
    {
        Guid timeseries_;
        public ReferenceTimeseriesPropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.ReferenceTimeseriesProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new ReferenceTimeseriesPropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.ReferenceTimeseriesProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class SByteTimeseriesPropertyObject : TimeseriesPropertyObject
    {
        Guid timeseries_;
        public SByteTimeseriesPropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.SByteTimeseriesProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new SByteTimeseriesPropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.SByteTimeseriesProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class SingleTimeseriesPropertyObject : TimeseriesPropertyObject
    {
        Guid timeseries_;
        public SingleTimeseriesPropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.SingleTimeseriesProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new SingleTimeseriesPropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.SingleTimeseriesProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class StringTimeseriesPropertyObject : TimeseriesPropertyObject
    {
        Guid timeseries_;
        public StringTimeseriesPropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.StringTimeseriesProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new StringTimeseriesPropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.StringTimeseriesProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class TimeSpanTimeseriesPropertyObject : TimeseriesPropertyObject
    {
        Guid timeseries_;
        public TimeSpanTimeseriesPropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.TimeSpanTimeseriesProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new TimeSpanTimeseriesPropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.TimeSpanTimeseriesProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class UInt16TimeseriesPropertyObject : TimeseriesPropertyObject
    {
        Guid timeseries_;
        public UInt16TimeseriesPropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.UInt16TimeseriesProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new UInt16TimeseriesPropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.UInt16TimeseriesProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class UInt32TimeseriesPropertyObject : TimeseriesPropertyObject
    {
        Guid timeseries_;
        public UInt32TimeseriesPropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.UInt32TimeseriesProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new UInt32TimeseriesPropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.UInt32TimeseriesProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class UInt64TimeseriesPropertyObject : TimeseriesPropertyObject
    {
        Guid timeseries_;
        public UInt64TimeseriesPropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.UInt64TimeseriesProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new UInt64TimeseriesPropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.UInt64TimeseriesProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class TimeSpanPropertyObject : PropertyObject
    {
        TimeSpan value_;
        public TimeSpanPropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.TimeSpanProperty;
        }

        public override BaseData<Kind> Create()
        {
            return new TimeSpanPropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.TimeSpanProperty )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public TimeSpan Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class UInt16PropertyObject : PropertyObject
    {
        ushort value_ = 0;
        public UInt16PropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.UInt16Property;
        }

        public override BaseData<Kind> Create()
        {
            return new UInt16PropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.UInt16Property )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public ushort Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class UInt32PropertyObject : PropertyObject
    {
        uint value_ = 0;
        public UInt32PropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.UInt32Property;
        }

        public override BaseData<Kind> Create()
        {
            return new UInt32PropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.UInt32Property )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public uint Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class UInt64PropertyObject : PropertyObject
    {
        long value_ = 0;
        public UInt64PropertyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.UInt64Property;
        }

        public override BaseData<Kind> Create()
        {
            return new UInt64PropertyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.UInt64Property )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public abstract class PropertyDefinitionObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid elementType_;
        string name_ = string.Empty;
        string description_ = string.Empty;
        protected PropertyDefinitionObject ( )
        {
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.PropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid ElementType
        {
            get => elementType_;
            set
            {
                if( elementType_ != value )
                {
                    elementType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Description
        {
            get => description_;
            set
            {
                if( description_ != value )
                {
                    description_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class BinaryPropertyDefinitionObject : PropertyDefinitionObject
    {
        byte[] defaultValue_ = Array.Empty<byte>();
        public BinaryPropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.BinaryPropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new BinaryPropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.BinaryPropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public byte[] DefaultValue
        {
            get => defaultValue_;
            set
            {
                if( defaultValue_ != value )
                {
                    defaultValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class BooleanPropertyDefinitionObject : PropertyDefinitionObject
    {
        bool defaultValue_ = false;
        public BooleanPropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.BooleanPropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new BooleanPropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.BooleanPropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public bool DefaultValue
        {
            get => defaultValue_;
            set
            {
                if( defaultValue_ != value )
                {
                    defaultValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class BytePropertyDefinitionObject : PropertyDefinitionObject
    {
        byte defaultValue_ = 0;
        byte minValue_ = 0;
        byte maxValue_ = 0;
        public BytePropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.BytePropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new BytePropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.BytePropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public byte DefaultValue
        {
            get => defaultValue_;
            set
            {
                if( defaultValue_ != value )
                {
                    defaultValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public byte MinValue
        {
            get => minValue_;
            set
            {
                if( minValue_ != value )
                {
                    minValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public byte MaxValue
        {
            get => maxValue_;
            set
            {
                if( maxValue_ != value )
                {
                    maxValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class DateTimePropertyDefinitionObject : PropertyDefinitionObject
    {
        string defaultValue_ = string.Empty;
        string minValue_ = string.Empty;
        string maxValue_ = string.Empty;
        public DateTimePropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.DateTimePropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new DateTimePropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.DateTimePropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public string DefaultValue
        {
            get => defaultValue_;
            set
            {
                if( defaultValue_ != value )
                {
                    defaultValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string MinValue
        {
            get => minValue_;
            set
            {
                if( minValue_ != value )
                {
                    minValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string MaxValue
        {
            get => maxValue_;
            set
            {
                if( maxValue_ != value )
                {
                    maxValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class DoublePropertyDefinitionObject : PropertyDefinitionObject
    {
        double defaultValue_ = 0.0;
        double minValue_ = 0.0;
        double maxValue_ = 0.0;
        public DoublePropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.DoublePropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new DoublePropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.DoublePropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public double DefaultValue
        {
            get => defaultValue_;
            set
            {
                if( defaultValue_ != value )
                {
                    defaultValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MinValue
        {
            get => minValue_;
            set
            {
                if( minValue_ != value )
                {
                    minValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MaxValue
        {
            get => maxValue_;
            set
            {
                if( maxValue_ != value )
                {
                    maxValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class GuidPropertyDefinitionObject : PropertyDefinitionObject
    {
        Guid defaultValue_;
        public GuidPropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GuidPropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new GuidPropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GuidPropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid DefaultValue
        {
            get => defaultValue_;
            set
            {
                if( defaultValue_ != value )
                {
                    defaultValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class Int16PropertyDefinitionObject : PropertyDefinitionObject
    {
        short defaultValue_ = 0;
        short minValue_ = 0;
        short maxValue_ = 0;
        public Int16PropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Int16PropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new Int16PropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Int16PropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public short DefaultValue
        {
            get => defaultValue_;
            set
            {
                if( defaultValue_ != value )
                {
                    defaultValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public short MinValue
        {
            get => minValue_;
            set
            {
                if( minValue_ != value )
                {
                    minValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public short MaxValue
        {
            get => maxValue_;
            set
            {
                if( maxValue_ != value )
                {
                    maxValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class Int32PropertyDefinitionObject : PropertyDefinitionObject
    {
        int defaultValue_ = 0;
        int minValue_ = 0;
        int maxValue_ = 0;
        public Int32PropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Int32PropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new Int32PropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Int32PropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public int DefaultValue
        {
            get => defaultValue_;
            set
            {
                if( defaultValue_ != value )
                {
                    defaultValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int MinValue
        {
            get => minValue_;
            set
            {
                if( minValue_ != value )
                {
                    minValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int MaxValue
        {
            get => maxValue_;
            set
            {
                if( maxValue_ != value )
                {
                    maxValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class Int64PropertyDefinitionObject : PropertyDefinitionObject
    {
        long defaultValue_ = 0;
        long minValue_ = 0;
        long maxValue_ = 0;
        public Int64PropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Int64PropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new Int64PropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Int64PropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long DefaultValue
        {
            get => defaultValue_;
            set
            {
                if( defaultValue_ != value )
                {
                    defaultValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public long MinValue
        {
            get => minValue_;
            set
            {
                if( minValue_ != value )
                {
                    minValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public long MaxValue
        {
            get => maxValue_;
            set
            {
                if( maxValue_ != value )
                {
                    maxValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class ReferencePropertyDefinitionObject : PropertyDefinitionObject
    {
        Guid defaultValue_;
        Guid referencedElementType_;
        public ReferencePropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.ReferencePropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new ReferencePropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.ReferencePropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid DefaultValue
        {
            get => defaultValue_;
            set
            {
                if( defaultValue_ != value )
                {
                    defaultValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid ReferencedElementType
        {
            get => referencedElementType_;
            set
            {
                if( referencedElementType_ != value )
                {
                    referencedElementType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class SBytePropertyDefinitionObject : PropertyDefinitionObject
    {
        sbyte defaultValue_ = 0;
        sbyte minValue_ = 0;
        sbyte maxValue_ = 0;
        public SBytePropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.SBytePropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new SBytePropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.SBytePropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public sbyte DefaultValue
        {
            get => defaultValue_;
            set
            {
                if( defaultValue_ != value )
                {
                    defaultValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public sbyte MinValue
        {
            get => minValue_;
            set
            {
                if( minValue_ != value )
                {
                    minValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public sbyte MaxValue
        {
            get => maxValue_;
            set
            {
                if( maxValue_ != value )
                {
                    maxValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class SinglePropertyDefinitionObject : PropertyDefinitionObject
    {
        float defaultValue_ = 0.0f;
        float minValue_ = 0.0f;
        float maxValue_ = 0.0f;
        public SinglePropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.SinglePropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new SinglePropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.SinglePropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public float DefaultValue
        {
            get => defaultValue_;
            set
            {
                if( defaultValue_ != value )
                {
                    defaultValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public float MinValue
        {
            get => minValue_;
            set
            {
                if( minValue_ != value )
                {
                    minValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public float MaxValue
        {
            get => maxValue_;
            set
            {
                if( maxValue_ != value )
                {
                    maxValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class StringPropertyDefinitionObject : PropertyDefinitionObject
    {
        string defaultValue_ = string.Empty;
        string pattern_ = string.Empty;
        public StringPropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.StringPropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new StringPropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.StringPropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public string DefaultValue
        {
            get => defaultValue_;
            set
            {
                if( defaultValue_ != value )
                {
                    defaultValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Pattern
        {
            get => pattern_;
            set
            {
                if( pattern_ != value )
                {
                    pattern_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public abstract class TimeseriesPropertyDefinitionObject : PropertyDefinitionObject
    {
        protected TimeseriesPropertyDefinitionObject ( )
        {
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.TimeseriesPropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class BinaryTimeseriesPropertyDefinitionObject : TimeseriesPropertyDefinitionObject
    {
        public BinaryTimeseriesPropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.BinaryTimeseriesPropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new BinaryTimeseriesPropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.BinaryTimeseriesPropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class BooleanTimeseriesPropertyDefinitionObject : TimeseriesPropertyDefinitionObject
    {
        public BooleanTimeseriesPropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.BooleanTimeseriesPropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new BooleanTimeseriesPropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.BooleanTimeseriesPropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class ByteTimeseriesPropertyDefinitionObject : TimeseriesPropertyDefinitionObject
    {
        byte minValue_ = 0;
        byte maxValue_ = 0;
        public ByteTimeseriesPropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.ByteTimeseriesPropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new ByteTimeseriesPropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.ByteTimeseriesPropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public byte MinValue
        {
            get => minValue_;
            set
            {
                if( minValue_ != value )
                {
                    minValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public byte MaxValue
        {
            get => maxValue_;
            set
            {
                if( maxValue_ != value )
                {
                    maxValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class DateTimeTimeseriesPropertyDefinitionObject : TimeseriesPropertyDefinitionObject
    {
        string minValue_ = string.Empty;
        string maxValue_ = string.Empty;
        public DateTimeTimeseriesPropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.DateTimeTimeseriesPropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new DateTimeTimeseriesPropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.DateTimeTimeseriesPropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public string MinValue
        {
            get => minValue_;
            set
            {
                if( minValue_ != value )
                {
                    minValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string MaxValue
        {
            get => maxValue_;
            set
            {
                if( maxValue_ != value )
                {
                    maxValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class DoubleTimeseriesPropertyDefinitionObject : TimeseriesPropertyDefinitionObject
    {
        double minValue_ = 0.0;
        double maxValue_ = 0.0;
        public DoubleTimeseriesPropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.DoubleTimeseriesPropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new DoubleTimeseriesPropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.DoubleTimeseriesPropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public double MinValue
        {
            get => minValue_;
            set
            {
                if( minValue_ != value )
                {
                    minValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MaxValue
        {
            get => maxValue_;
            set
            {
                if( maxValue_ != value )
                {
                    maxValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class GuidTimeseriesPropertyDefinitionObject : TimeseriesPropertyDefinitionObject
    {
        public GuidTimeseriesPropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GuidTimeseriesPropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new GuidTimeseriesPropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GuidTimeseriesPropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class Int16TimeseriesPropertyDefinitionObject : TimeseriesPropertyDefinitionObject
    {
        short minValue_ = 0;
        short maxValue_ = 0;
        public Int16TimeseriesPropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Int16TimeseriesPropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new Int16TimeseriesPropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Int16TimeseriesPropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public short MinValue
        {
            get => minValue_;
            set
            {
                if( minValue_ != value )
                {
                    minValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public short MaxValue
        {
            get => maxValue_;
            set
            {
                if( maxValue_ != value )
                {
                    maxValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class Int32TimeseriesPropertyDefinitionObject : TimeseriesPropertyDefinitionObject
    {
        int minValue_ = 0;
        int maxValue_ = 0;
        public Int32TimeseriesPropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Int32TimeseriesPropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new Int32TimeseriesPropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Int32TimeseriesPropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public int MinValue
        {
            get => minValue_;
            set
            {
                if( minValue_ != value )
                {
                    minValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int MaxValue
        {
            get => maxValue_;
            set
            {
                if( maxValue_ != value )
                {
                    maxValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class Int64TimeseriesPropertyDefinitionObject : TimeseriesPropertyDefinitionObject
    {
        long minValue_ = 0;
        long maxValue_ = 0;
        public Int64TimeseriesPropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Int64TimeseriesPropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new Int64TimeseriesPropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Int64TimeseriesPropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long MinValue
        {
            get => minValue_;
            set
            {
                if( minValue_ != value )
                {
                    minValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public long MaxValue
        {
            get => maxValue_;
            set
            {
                if( maxValue_ != value )
                {
                    maxValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class ReferenceTimeseriesPropertyDefinitionObject : TimeseriesPropertyDefinitionObject
    {
        Guid referencedElementType_;
        public ReferenceTimeseriesPropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.ReferenceTimeseriesPropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new ReferenceTimeseriesPropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.ReferenceTimeseriesPropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid ReferencedElementType
        {
            get => referencedElementType_;
            set
            {
                if( referencedElementType_ != value )
                {
                    referencedElementType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class SByteTimeseriesPropertyDefinitionObject : TimeseriesPropertyDefinitionObject
    {
        sbyte minValue_ = 0;
        sbyte maxValue_ = 0;
        public SByteTimeseriesPropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.SByteTimeseriesPropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new SByteTimeseriesPropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.SByteTimeseriesPropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public sbyte MinValue
        {
            get => minValue_;
            set
            {
                if( minValue_ != value )
                {
                    minValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public sbyte MaxValue
        {
            get => maxValue_;
            set
            {
                if( maxValue_ != value )
                {
                    maxValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class SingleTimeseriesPropertyDefinitionObject : TimeseriesPropertyDefinitionObject
    {
        float minValue_ = 0.0f;
        float maxValue_ = 0.0f;
        public SingleTimeseriesPropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.SingleTimeseriesPropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new SingleTimeseriesPropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.SingleTimeseriesPropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public float MinValue
        {
            get => minValue_;
            set
            {
                if( minValue_ != value )
                {
                    minValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public float MaxValue
        {
            get => maxValue_;
            set
            {
                if( maxValue_ != value )
                {
                    maxValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class StringTimeseriesPropertyDefinitionObject : TimeseriesPropertyDefinitionObject
    {
        string pattern_ = string.Empty;
        public StringTimeseriesPropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.StringTimeseriesPropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new StringTimeseriesPropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.StringTimeseriesPropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public string Pattern
        {
            get => pattern_;
            set
            {
                if( pattern_ != value )
                {
                    pattern_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class TimeSpanTimeseriesPropertyDefinitionObject : TimeseriesPropertyDefinitionObject
    {
        TimeSpan minValue_;
        TimeSpan maxValue_;
        public TimeSpanTimeseriesPropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.TimeSpanTimeseriesPropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new TimeSpanTimeseriesPropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.TimeSpanTimeseriesPropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public TimeSpan MinValue
        {
            get => minValue_;
            set
            {
                if( minValue_ != value )
                {
                    minValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan MaxValue
        {
            get => maxValue_;
            set
            {
                if( maxValue_ != value )
                {
                    maxValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class UInt16TimeseriesPropertyDefinitionObject : TimeseriesPropertyDefinitionObject
    {
        ushort minValue_ = 0;
        ushort maxValue_ = 0;
        public UInt16TimeseriesPropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.UInt16TimeseriesPropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new UInt16TimeseriesPropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.UInt16TimeseriesPropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public ushort MinValue
        {
            get => minValue_;
            set
            {
                if( minValue_ != value )
                {
                    minValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public ushort MaxValue
        {
            get => maxValue_;
            set
            {
                if( maxValue_ != value )
                {
                    maxValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class UInt32TimeseriesPropertyDefinitionObject : TimeseriesPropertyDefinitionObject
    {
        uint minValue_ = 0;
        uint maxValue_ = 0;
        public UInt32TimeseriesPropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.UInt32TimeseriesPropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new UInt32TimeseriesPropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.UInt32TimeseriesPropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public uint MinValue
        {
            get => minValue_;
            set
            {
                if( minValue_ != value )
                {
                    minValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public uint MaxValue
        {
            get => maxValue_;
            set
            {
                if( maxValue_ != value )
                {
                    maxValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class UInt64TimeseriesPropertyDefinitionObject : TimeseriesPropertyDefinitionObject
    {
        long minValue_ = 0;
        long maxValue_ = 0;
        public UInt64TimeseriesPropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.UInt64TimeseriesPropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new UInt64TimeseriesPropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.UInt64TimeseriesPropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long MinValue
        {
            get => minValue_;
            set
            {
                if( minValue_ != value )
                {
                    minValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public long MaxValue
        {
            get => maxValue_;
            set
            {
                if( maxValue_ != value )
                {
                    maxValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class TimeSpanPropertyDefinitionObject : PropertyDefinitionObject
    {
        TimeSpan defaultValue_;
        TimeSpan minValue_;
        TimeSpan maxValue_;
        public TimeSpanPropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.TimeSpanPropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new TimeSpanPropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.TimeSpanPropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public TimeSpan DefaultValue
        {
            get => defaultValue_;
            set
            {
                if( defaultValue_ != value )
                {
                    defaultValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan MinValue
        {
            get => minValue_;
            set
            {
                if( minValue_ != value )
                {
                    minValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan MaxValue
        {
            get => maxValue_;
            set
            {
                if( maxValue_ != value )
                {
                    maxValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class UInt16PropertyDefinitionObject : PropertyDefinitionObject
    {
        ushort defaultValue_ = 0;
        ushort minValue_ = 0;
        ushort maxValue_ = 0;
        public UInt16PropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.UInt16PropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new UInt16PropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.UInt16PropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public ushort DefaultValue
        {
            get => defaultValue_;
            set
            {
                if( defaultValue_ != value )
                {
                    defaultValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public ushort MinValue
        {
            get => minValue_;
            set
            {
                if( minValue_ != value )
                {
                    minValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public ushort MaxValue
        {
            get => maxValue_;
            set
            {
                if( maxValue_ != value )
                {
                    maxValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class UInt32PropertyDefinitionObject : PropertyDefinitionObject
    {
        uint defaultValue_ = 0;
        uint minValue_ = 0;
        uint maxValue_ = 0;
        public UInt32PropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.UInt32PropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new UInt32PropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.UInt32PropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public uint DefaultValue
        {
            get => defaultValue_;
            set
            {
                if( defaultValue_ != value )
                {
                    defaultValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public uint MinValue
        {
            get => minValue_;
            set
            {
                if( minValue_ != value )
                {
                    minValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public uint MaxValue
        {
            get => maxValue_;
            set
            {
                if( maxValue_ != value )
                {
                    maxValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class UInt64PropertyDefinitionObject : PropertyDefinitionObject
    {
        long defaultValue_ = 0;
        long minValue_ = 0;
        long maxValue_ = 0;
        public UInt64PropertyDefinitionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.UInt64PropertyDefinition;
        }

        public override BaseData<Kind> Create()
        {
            return new UInt64PropertyDefinitionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.UInt64PropertyDefinition )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long DefaultValue
        {
            get => defaultValue_;
            set
            {
                if( defaultValue_ != value )
                {
                    defaultValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public long MinValue
        {
            get => minValue_;
            set
            {
                if( minValue_ != value )
                {
                    minValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public long MaxValue
        {
            get => maxValue_;
            set
            {
                if( maxValue_ != value )
                {
                    maxValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarAlarmStatusObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid radar_;
        DateTime timestamp_;
        Types.AlarmState type_ = Types.AlarmState.Unknown;
        public RadarAlarmStatusObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarAlarmStatus;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarAlarmStatusObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarAlarmStatus )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.AlarmState Type
        {
            get => type_;
            set
            {
                if( type_ != value )
                {
                    type_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarCommandObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid radar_;
        DateTime timestamp_;
        Types.DeviceCommandSourceType deviceCommandSourceType_ = Types.DeviceCommandSourceType.Unknown;
        Guid deviceCommandSourceId_;
        Guid reply_;
        public RadarCommandObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarCommand;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarCommandObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarCommand )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.DeviceCommandSourceType DeviceCommandSourceType
        {
            get => deviceCommandSourceType_;
            set
            {
                if( deviceCommandSourceType_ != value )
                {
                    deviceCommandSourceType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid DeviceCommandSourceId
        {
            get => deviceCommandSourceId_;
            set
            {
                if( deviceCommandSourceId_ != value )
                {
                    deviceCommandSourceId_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Reply
        {
            get => reply_;
            set
            {
                if( reply_ != value )
                {
                    reply_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarCommandGetStatusObject : RadarCommandObject
    {
        public RadarCommandGetStatusObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarCommandGetStatus;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarCommandGetStatusObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarCommandGetStatus )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class RadarCommandReplyObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid radar_;
        DateTime timestamp_;
        Guid command_;
        Types.DeviceCommandReplyStatus status_ = Types.DeviceCommandReplyStatus.Unknown;
        string message_ = string.Empty;
        public RadarCommandReplyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarCommandReply;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarCommandReplyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarCommandReply )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Command
        {
            get => command_;
            set
            {
                if( command_ != value )
                {
                    command_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.DeviceCommandReplyStatus Status
        {
            get => status_;
            set
            {
                if( status_ != value )
                {
                    status_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Message
        {
            get => message_;
            set
            {
                if( message_ != value )
                {
                    message_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarCommandReplyGetStatusObject : RadarCommandReplyObject
    {
        int azimuthCount_ = 0;
        int triggerCount_ = 0;
        TimeSpan rotationCount_;
        Types.RadarPulse pulse_ = Types.RadarPulse.Short;
        bool tx_ = false;
        public RadarCommandReplyGetStatusObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarCommandReplyGetStatus;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarCommandReplyGetStatusObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarCommandReplyGetStatus )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public int AzimuthCount
        {
            get => azimuthCount_;
            set
            {
                if( azimuthCount_ != value )
                {
                    azimuthCount_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int TriggerCount
        {
            get => triggerCount_;
            set
            {
                if( triggerCount_ != value )
                {
                    triggerCount_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan RotationCount
        {
            get => rotationCount_;
            set
            {
                if( rotationCount_ != value )
                {
                    rotationCount_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.RadarPulse Pulse
        {
            get => pulse_;
            set
            {
                if( pulse_ != value )
                {
                    pulse_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Tx
        {
            get => tx_;
            set
            {
                if( tx_ != value )
                {
                    tx_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarConfigurationObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid radar_;
        DateTime timestamp_;
        int radarProtocolVersion_ = 0;
        string radarIPAddress_ = string.Empty;
        int radarPort_ = 0;
        int radarConfigurationPort_ = 0;
        TimeSpan skipMagicTimeout_;
        TimeSpan readTimeout_;
        TimeSpan synchronizationInterval_;
        int targetsRefreshRate_ = 0;
        int range_ = 0;
        int sectorCount_ = 0;
        int sectorOffset_ = 0;
        uint imageColor_ = 0;
        uint? imageSubstitutionColor_;
        uint transparentColor_ = 0;
        double imageScaleFactorX_ = 0.0;
        double imageOffsetX_ = 0.0;
        double imageScaleFactorY_ = 0.0;
        double imageOffsetY_ = 0.0;
        Types.RadarImageType radarImageType_ = Types.RadarImageType.MaskedProcessed;
        uint trackColor_ = 0;
        uint vectorColor_ = 0;
        bool enableNmea_ = false;
        string nmeaReceiverIPAddress_ = string.Empty;
        int nmeaReceiverPort_ = 0;
        string nmeaReceiverSourceId_ = string.Empty;
        public RadarConfigurationObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarConfiguration;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarConfigurationObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarConfiguration )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int RadarProtocolVersion
        {
            get => radarProtocolVersion_;
            set
            {
                if( radarProtocolVersion_ != value )
                {
                    radarProtocolVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string RadarIPAddress
        {
            get => radarIPAddress_;
            set
            {
                if( radarIPAddress_ != value )
                {
                    radarIPAddress_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int RadarPort
        {
            get => radarPort_;
            set
            {
                if( radarPort_ != value )
                {
                    radarPort_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int RadarConfigurationPort
        {
            get => radarConfigurationPort_;
            set
            {
                if( radarConfigurationPort_ != value )
                {
                    radarConfigurationPort_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan SkipMagicTimeout
        {
            get => skipMagicTimeout_;
            set
            {
                if( skipMagicTimeout_ != value )
                {
                    skipMagicTimeout_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan ReadTimeout
        {
            get => readTimeout_;
            set
            {
                if( readTimeout_ != value )
                {
                    readTimeout_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan SynchronizationInterval
        {
            get => synchronizationInterval_;
            set
            {
                if( synchronizationInterval_ != value )
                {
                    synchronizationInterval_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int TargetsRefreshRate
        {
            get => targetsRefreshRate_;
            set
            {
                if( targetsRefreshRate_ != value )
                {
                    targetsRefreshRate_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Range
        {
            get => range_;
            set
            {
                if( range_ != value )
                {
                    range_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int SectorCount
        {
            get => sectorCount_;
            set
            {
                if( sectorCount_ != value )
                {
                    sectorCount_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int SectorOffset
        {
            get => sectorOffset_;
            set
            {
                if( sectorOffset_ != value )
                {
                    sectorOffset_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public uint ImageColor
        {
            get => imageColor_;
            set
            {
                if( imageColor_ != value )
                {
                    imageColor_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public uint? ImageSubstitutionColor
        {
            get => imageSubstitutionColor_;
            set
            {
                if( imageSubstitutionColor_ != value )
                {
                    imageSubstitutionColor_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public uint TransparentColor
        {
            get => transparentColor_;
            set
            {
                if( transparentColor_ != value )
                {
                    transparentColor_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double ImageScaleFactorX
        {
            get => imageScaleFactorX_;
            set
            {
                if( imageScaleFactorX_ != value )
                {
                    imageScaleFactorX_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double ImageOffsetX
        {
            get => imageOffsetX_;
            set
            {
                if( imageOffsetX_ != value )
                {
                    imageOffsetX_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double ImageScaleFactorY
        {
            get => imageScaleFactorY_;
            set
            {
                if( imageScaleFactorY_ != value )
                {
                    imageScaleFactorY_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double ImageOffsetY
        {
            get => imageOffsetY_;
            set
            {
                if( imageOffsetY_ != value )
                {
                    imageOffsetY_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.RadarImageType RadarImageType
        {
            get => radarImageType_;
            set
            {
                if( radarImageType_ != value )
                {
                    radarImageType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public uint TrackColor
        {
            get => trackColor_;
            set
            {
                if( trackColor_ != value )
                {
                    trackColor_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public uint VectorColor
        {
            get => vectorColor_;
            set
            {
                if( vectorColor_ != value )
                {
                    vectorColor_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool EnableNmea
        {
            get => enableNmea_;
            set
            {
                if( enableNmea_ != value )
                {
                    enableNmea_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string NmeaReceiverIPAddress
        {
            get => nmeaReceiverIPAddress_;
            set
            {
                if( nmeaReceiverIPAddress_ != value )
                {
                    nmeaReceiverIPAddress_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int NmeaReceiverPort
        {
            get => nmeaReceiverPort_;
            set
            {
                if( nmeaReceiverPort_ != value )
                {
                    nmeaReceiverPort_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string NmeaReceiverSourceId
        {
            get => nmeaReceiverSourceId_;
            set
            {
                if( nmeaReceiverSourceId_ != value )
                {
                    nmeaReceiverSourceId_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarImageObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid radar_;
        DateTime timestamp_;
        uint depth_ = 0;
        int resolution_ = 0;
        int range_ = 0;
        byte[] image_ = Array.Empty<byte>();
        public RadarImageObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarImage;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarImageObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarImage )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public uint Depth
        {
            get => depth_;
            set
            {
                if( depth_ != value )
                {
                    depth_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Resolution
        {
            get => resolution_;
            set
            {
                if( resolution_ != value )
                {
                    resolution_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Range
        {
            get => range_;
            set
            {
                if( range_ != value )
                {
                    range_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public byte[] Image
        {
            get => image_;
            set
            {
                if( image_ != value )
                {
                    image_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarRawTrackTableObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid radar_;
        DateTime timestamp_;
        int count_ = 0;
        byte[] table_ = Array.Empty<byte>();
        public RadarRawTrackTableObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarRawTrackTable;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarRawTrackTableObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarRawTrackTable )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Count
        {
            get => count_;
            set
            {
                if( count_ != value )
                {
                    count_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public byte[] Table
        {
            get => table_;
            set
            {
                if( table_ != value )
                {
                    table_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarStatusObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid radar_;
        DateTime timestamp_;
        int azimuthCount_ = 0;
        int triggerCount_ = 0;
        TimeSpan rotationTime_;
        Types.RadarPulse pulse_ = Types.RadarPulse.Short;
        bool tx_ = false;
        bool tracking_ = false;
        public RadarStatusObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarStatus;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarStatusObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarStatus )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int AzimuthCount
        {
            get => azimuthCount_;
            set
            {
                if( azimuthCount_ != value )
                {
                    azimuthCount_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int TriggerCount
        {
            get => triggerCount_;
            set
            {
                if( triggerCount_ != value )
                {
                    triggerCount_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan RotationTime
        {
            get => rotationTime_;
            set
            {
                if( rotationTime_ != value )
                {
                    rotationTime_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.RadarPulse Pulse
        {
            get => pulse_;
            set
            {
                if( pulse_ != value )
                {
                    pulse_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Tx
        {
            get => tx_;
            set
            {
                if( tx_ != value )
                {
                    tx_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool Tracking
        {
            get => tracking_;
            set
            {
                if( tracking_ != value )
                {
                    tracking_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadioCommandObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid radio_;
        DateTime timestamp_;
        Types.DeviceCommandSourceType deviceCommandSourceType_ = Types.DeviceCommandSourceType.Unknown;
        Guid deviceCommandSourceId_;
        Guid reply_;
        public RadioCommandObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadioCommand;
        }

        public override BaseData<Kind> Create()
        {
            return new RadioCommandObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadioCommand )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Radio
        {
            get => radio_;
            set
            {
                if( radio_ != value )
                {
                    radio_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.DeviceCommandSourceType DeviceCommandSourceType
        {
            get => deviceCommandSourceType_;
            set
            {
                if( deviceCommandSourceType_ != value )
                {
                    deviceCommandSourceType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid DeviceCommandSourceId
        {
            get => deviceCommandSourceId_;
            set
            {
                if( deviceCommandSourceId_ != value )
                {
                    deviceCommandSourceId_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Reply
        {
            get => reply_;
            set
            {
                if( reply_ != value )
                {
                    reply_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadioCommandReplyObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid radio_;
        DateTime timestamp_;
        Guid command_;
        Types.DeviceCommandReplyStatus status_ = Types.DeviceCommandReplyStatus.Unknown;
        string message_ = string.Empty;
        public RadioCommandReplyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadioCommandReply;
        }

        public override BaseData<Kind> Create()
        {
            return new RadioCommandReplyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadioCommandReply )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Radio
        {
            get => radio_;
            set
            {
                if( radio_ != value )
                {
                    radio_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Command
        {
            get => command_;
            set
            {
                if( command_ != value )
                {
                    command_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.DeviceCommandReplyStatus Status
        {
            get => status_;
            set
            {
                if( status_ != value )
                {
                    status_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Message
        {
            get => message_;
            set
            {
                if( message_ != value )
                {
                    message_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadioConfigurationObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid radio_;
        DateTime timestamp_;
        double longitude_ = 0.0;
        double latitude_ = 0.0;
        string playbackUrl_ = string.Empty;
        string radioIPAddress_ = string.Empty;
        int radioPort_ = 0;
        string ed137IPAddress_ = string.Empty;
        int ed137Port_ = 0;
        public RadioConfigurationObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadioConfiguration;
        }

        public override BaseData<Kind> Create()
        {
            return new RadioConfigurationObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadioConfiguration )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Radio
        {
            get => radio_;
            set
            {
                if( radio_ != value )
                {
                    radio_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Longitude
        {
            get => longitude_;
            set
            {
                if( longitude_ != value )
                {
                    longitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Latitude
        {
            get => latitude_;
            set
            {
                if( latitude_ != value )
                {
                    latitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string PlaybackUrl
        {
            get => playbackUrl_;
            set
            {
                if( playbackUrl_ != value )
                {
                    playbackUrl_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string RadioIPAddress
        {
            get => radioIPAddress_;
            set
            {
                if( radioIPAddress_ != value )
                {
                    radioIPAddress_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int RadioPort
        {
            get => radioPort_;
            set
            {
                if( radioPort_ != value )
                {
                    radioPort_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Ed137IPAddress
        {
            get => ed137IPAddress_;
            set
            {
                if( ed137IPAddress_ != value )
                {
                    ed137IPAddress_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Ed137Port
        {
            get => ed137Port_;
            set
            {
                if( ed137Port_ != value )
                {
                    ed137Port_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadomeCommandObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid radome_;
        DateTime timestamp_;
        Types.DeviceCommandSourceType deviceCommandSourceType_ = Types.DeviceCommandSourceType.Unknown;
        Guid deviceCommandSourceId_;
        Guid reply_;
        public RadomeCommandObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadomeCommand;
        }

        public override BaseData<Kind> Create()
        {
            return new RadomeCommandObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadomeCommand )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Radome
        {
            get => radome_;
            set
            {
                if( radome_ != value )
                {
                    radome_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.DeviceCommandSourceType DeviceCommandSourceType
        {
            get => deviceCommandSourceType_;
            set
            {
                if( deviceCommandSourceType_ != value )
                {
                    deviceCommandSourceType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid DeviceCommandSourceId
        {
            get => deviceCommandSourceId_;
            set
            {
                if( deviceCommandSourceId_ != value )
                {
                    deviceCommandSourceId_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Reply
        {
            get => reply_;
            set
            {
                if( reply_ != value )
                {
                    reply_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadomeCommandReplyObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid radome_;
        DateTime timestamp_;
        Guid command_;
        Types.DeviceCommandReplyStatus status_ = Types.DeviceCommandReplyStatus.Unknown;
        string message_ = string.Empty;
        public RadomeCommandReplyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadomeCommandReply;
        }

        public override BaseData<Kind> Create()
        {
            return new RadomeCommandReplyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadomeCommandReply )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Radome
        {
            get => radome_;
            set
            {
                if( radome_ != value )
                {
                    radome_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Command
        {
            get => command_;
            set
            {
                if( command_ != value )
                {
                    command_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.DeviceCommandReplyStatus Status
        {
            get => status_;
            set
            {
                if( status_ != value )
                {
                    status_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Message
        {
            get => message_;
            set
            {
                if( message_ != value )
                {
                    message_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadomeConfigurationObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid radome_;
        DateTime timestamp_;
        TimeSpan interval_;
        double lowPressureLimit_ = 0.0;
        double highPressureLimit_ = 0.0;
        double lowTemperatureLimit_ = 0.0;
        double highTemperatureLimit_ = 0.0;
        public RadomeConfigurationObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadomeConfiguration;
        }

        public override BaseData<Kind> Create()
        {
            return new RadomeConfigurationObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadomeConfiguration )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Radome
        {
            get => radome_;
            set
            {
                if( radome_ != value )
                {
                    radome_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan Interval
        {
            get => interval_;
            set
            {
                if( interval_ != value )
                {
                    interval_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double LowPressureLimit
        {
            get => lowPressureLimit_;
            set
            {
                if( lowPressureLimit_ != value )
                {
                    lowPressureLimit_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double HighPressureLimit
        {
            get => highPressureLimit_;
            set
            {
                if( highPressureLimit_ != value )
                {
                    highPressureLimit_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double LowTemperatureLimit
        {
            get => lowTemperatureLimit_;
            set
            {
                if( lowTemperatureLimit_ != value )
                {
                    lowTemperatureLimit_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double HighTemperatureLimit
        {
            get => highTemperatureLimit_;
            set
            {
                if( highTemperatureLimit_ != value )
                {
                    highTemperatureLimit_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class ReferenceTimeseriesValueObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        Guid value_;
        public ReferenceTimeseriesValueObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.ReferenceTimeseriesValue;
        }

        public override BaseData<Kind> Create()
        {
            return new ReferenceTimeseriesValueObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.ReferenceTimeseriesValue )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class SByteTimeseriesValueObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        sbyte? value_;
        public SByteTimeseriesValueObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.SByteTimeseriesValue;
        }

        public override BaseData<Kind> Create()
        {
            return new SByteTimeseriesValueObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.SByteTimeseriesValue )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public sbyte? Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class SecurityDomainObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        string name_ = string.Empty;
        string description_ = string.Empty;
        public SecurityDomainObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.SecurityDomain;
        }

        public override BaseData<Kind> Create()
        {
            return new SecurityDomainObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.SecurityDomain )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Description
        {
            get => description_;
            set
            {
                if( description_ != value )
                {
                    description_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public abstract class SecurityIdentifierObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid domain_;
        string identity_ = string.Empty;
        string description_ = string.Empty;
        protected SecurityIdentifierObject ( )
        {
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.SecurityIdentifier )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Domain
        {
            get => domain_;
            set
            {
                if( domain_ != value )
                {
                    domain_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Identity
        {
            get => identity_;
            set
            {
                if( identity_ != value )
                {
                    identity_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Description
        {
            get => description_;
            set
            {
                if( description_ != value )
                {
                    description_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class SecurityLoginObject : SecurityIdentifierObject
    {
        public SecurityLoginObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.SecurityLogin;
        }

        public override BaseData<Kind> Create()
        {
            return new SecurityLoginObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.SecurityLogin )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class SecurityRoleObject : SecurityIdentifierObject
    {
        string name_ = string.Empty;
        public SecurityRoleObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.SecurityRole;
        }

        public override BaseData<Kind> Create()
        {
            return new SecurityRoleObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.SecurityRole )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class SecurityIdentifierRoleLinkObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid member_;
        Guid role_;
        DateTime start_;
        DateTime? end_;
        public SecurityIdentifierRoleLinkObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.SecurityIdentifierRoleLink;
        }

        public override BaseData<Kind> Create()
        {
            return new SecurityIdentifierRoleLinkObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.SecurityIdentifierRoleLink )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Member
        {
            get => member_;
            set
            {
                if( member_ != value )
                {
                    member_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Role
        {
            get => role_;
            set
            {
                if( role_ != value )
                {
                    role_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Start
        {
            get => start_;
            set
            {
                if( start_ != value )
                {
                    start_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime? End
        {
            get => end_;
            set
            {
                if( end_ != value )
                {
                    end_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class SecurityLoginSessionObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid login_;
        DateTime fromTime_;
        DateTime? throughTime_;
        Guid clientSession_;
        string notificationQueueName_ = string.Empty;
        string messageQueueName_ = string.Empty;
        public SecurityLoginSessionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.SecurityLoginSession;
        }

        public override BaseData<Kind> Create()
        {
            return new SecurityLoginSessionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.SecurityLoginSession )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Login
        {
            get => login_;
            set
            {
                if( login_ != value )
                {
                    login_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime FromTime
        {
            get => fromTime_;
            set
            {
                if( fromTime_ != value )
                {
                    fromTime_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime? ThroughTime
        {
            get => throughTime_;
            set
            {
                if( throughTime_ != value )
                {
                    throughTime_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid ClientSession
        {
            get => clientSession_;
            set
            {
                if( clientSession_ != value )
                {
                    clientSession_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string NotificationQueueName
        {
            get => notificationQueueName_;
            set
            {
                if( notificationQueueName_ != value )
                {
                    notificationQueueName_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string MessageQueueName
        {
            get => messageQueueName_;
            set
            {
                if( messageQueueName_ != value )
                {
                    messageQueueName_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class SecurityPermissionObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid identifier_;
        DateTime timestamp_;
        int typeCode_ = 0;
        bool canCreate_ = false;
        bool canRead_ = false;
        bool canUpdate_ = false;
        bool canDelete_ = false;
        public SecurityPermissionObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.SecurityPermission;
        }

        public override BaseData<Kind> Create()
        {
            return new SecurityPermissionObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.SecurityPermission )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Identifier
        {
            get => identifier_;
            set
            {
                if( identifier_ != value )
                {
                    identifier_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int TypeCode
        {
            get => typeCode_;
            set
            {
                if( typeCode_ != value )
                {
                    typeCode_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool CanCreate
        {
            get => canCreate_;
            set
            {
                if( canCreate_ != value )
                {
                    canCreate_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool CanRead
        {
            get => canRead_;
            set
            {
                if( canRead_ != value )
                {
                    canRead_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool CanUpdate
        {
            get => canUpdate_;
            set
            {
                if( canUpdate_ != value )
                {
                    canUpdate_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool CanDelete
        {
            get => canDelete_;
            set
            {
                if( canDelete_ != value )
                {
                    canDelete_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class SingleTimeseriesValueObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        float? value_;
        public SingleTimeseriesValueObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.SingleTimeseriesValue;
        }

        public override BaseData<Kind> Create()
        {
            return new SingleTimeseriesValueObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.SingleTimeseriesValue )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public float? Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class StringTimeseriesValueObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        string value_ = string.Empty;
        public StringTimeseriesValueObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.StringTimeseriesValue;
        }

        public override BaseData<Kind> Create()
        {
            return new StringTimeseriesValueObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.StringTimeseriesValue )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public abstract class TimeseriesCatalogElementObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid? catalog_;
        string name_ = string.Empty;
        protected TimeseriesCatalogElementObject ( )
        {
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.TimeseriesCatalogElement )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid? Catalog
        {
            get => catalog_;
            set
            {
                if( catalog_ != value )
                {
                    catalog_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public abstract class TimeseriesObject : TimeseriesCatalogElementObject
    {
        TimeSpan maxRetention_;
        protected TimeseriesObject ( )
        {
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Timeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public TimeSpan MaxRetention
        {
            get => maxRetention_;
            set
            {
                if( maxRetention_ != value )
                {
                    maxRetention_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class BinaryTimeseriesObject : TimeseriesObject
    {
        public BinaryTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.BinaryTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new BinaryTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.BinaryTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class BooleanTimeseriesObject : TimeseriesObject
    {
        public BooleanTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.BooleanTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new BooleanTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.BooleanTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class AisAidToNavigationOffPositionTimeseriesObject : BooleanTimeseriesObject
    {
        Guid aidToNavigation_;
        public AisAidToNavigationOffPositionTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisAidToNavigationOffPositionTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new AisAidToNavigationOffPositionTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisAidToNavigationOffPositionTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid AidToNavigation
        {
            get => aidToNavigation_;
            set
            {
                if( aidToNavigation_ != value )
                {
                    aidToNavigation_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class DeviceEnabledTimeseriesObject : BooleanTimeseriesObject
    {
        Guid? device_;
        public DeviceEnabledTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.DeviceEnabledTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new DeviceEnabledTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.DeviceEnabledTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid? Device
        {
            get => device_;
            set
            {
                if( device_ != value )
                {
                    device_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarAutomaticSensitivityTimeControlTimeseriesObject : BooleanTimeseriesObject
    {
        Guid radar_;
        public RadarAutomaticSensitivityTimeControlTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarAutomaticSensitivityTimeControlTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarAutomaticSensitivityTimeControlTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarAutomaticSensitivityTimeControlTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarBlankSector1TimeseriesObject : BooleanTimeseriesObject
    {
        Guid radar_;
        public RadarBlankSector1TimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarBlankSector1Timeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarBlankSector1TimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarBlankSector1Timeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarBlankSector2TimeseriesObject : BooleanTimeseriesObject
    {
        Guid radar_;
        public RadarBlankSector2TimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarBlankSector2Timeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarBlankSector2TimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarBlankSector2Timeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarEnableAutomaticFrequencyControlTimeseriesObject : BooleanTimeseriesObject
    {
        Guid radar_;
        public RadarEnableAutomaticFrequencyControlTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarEnableAutomaticFrequencyControlTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarEnableAutomaticFrequencyControlTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarEnableAutomaticFrequencyControlTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarEnableFastTimeConstantTimeseriesObject : BooleanTimeseriesObject
    {
        Guid radar_;
        public RadarEnableFastTimeConstantTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarEnableFastTimeConstantTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarEnableFastTimeConstantTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarEnableFastTimeConstantTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarEnableSensitivityTimeControlTimeseriesObject : BooleanTimeseriesObject
    {
        Guid radar_;
        public RadarEnableSensitivityTimeControlTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarEnableSensitivityTimeControlTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarEnableSensitivityTimeControlTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarEnableSensitivityTimeControlTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarPowerOnTimeseriesObject : BooleanTimeseriesObject
    {
        Guid radar_;
        public RadarPowerOnTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarPowerOnTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarPowerOnTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarPowerOnTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarSaveSettingsTimeseriesObject : BooleanTimeseriesObject
    {
        Guid radar_;
        public RadarSaveSettingsTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarSaveSettingsTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarSaveSettingsTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarSaveSettingsTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarTrackingTimeseriesObject : BooleanTimeseriesObject
    {
        Guid radar_;
        public RadarTrackingTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarTrackingTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarTrackingTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarTrackingTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class MediaProxySessionEnabledTimeseriesObject : BooleanTimeseriesObject
    {
        Guid proxySession_;
        public MediaProxySessionEnabledTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.MediaProxySessionEnabledTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new MediaProxySessionEnabledTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.MediaProxySessionEnabledTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid ProxySession
        {
            get => proxySession_;
            set
            {
                if( proxySession_ != value )
                {
                    proxySession_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class MediaServiceEnabledTimeseriesObject : BooleanTimeseriesObject
    {
        Guid service_;
        public MediaServiceEnabledTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.MediaServiceEnabledTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new MediaServiceEnabledTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.MediaServiceEnabledTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Service
        {
            get => service_;
            set
            {
                if( service_ != value )
                {
                    service_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class ByteTimeseriesObject : TimeseriesObject
    {
        public ByteTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.ByteTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new ByteTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.ByteTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class DateTimeTimeseriesObject : TimeseriesObject
    {
        public DateTimeTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.DateTimeTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new DateTimeTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.DateTimeTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class DoubleTimeseriesObject : TimeseriesObject
    {
        public DoubleTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.DoubleTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new DoubleTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.DoubleTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class GNSSAltitudeTimeseriesObject : DoubleTimeseriesObject
    {
        Guid gNSSDevice_;
        public GNSSAltitudeTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GNSSAltitudeTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new GNSSAltitudeTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GNSSAltitudeTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid GNSSDevice
        {
            get => gNSSDevice_;
            set
            {
                if( gNSSDevice_ != value )
                {
                    gNSSDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class GNSSLatitudeTimeseriesObject : DoubleTimeseriesObject
    {
        Guid gNSSDevice_;
        public GNSSLatitudeTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GNSSLatitudeTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new GNSSLatitudeTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GNSSLatitudeTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid GNSSDevice
        {
            get => gNSSDevice_;
            set
            {
                if( gNSSDevice_ != value )
                {
                    gNSSDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class GNSSLongitudeTimeseriesObject : DoubleTimeseriesObject
    {
        Guid gNSSDevice_;
        public GNSSLongitudeTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GNSSLongitudeTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new GNSSLongitudeTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GNSSLongitudeTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid GNSSDevice
        {
            get => gNSSDevice_;
            set
            {
                if( gNSSDevice_ != value )
                {
                    gNSSDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class GyroCourseTimeseriesObject : DoubleTimeseriesObject
    {
        Guid gyroDevice_;
        public GyroCourseTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GyroCourseTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new GyroCourseTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GyroCourseTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid GyroDevice
        {
            get => gyroDevice_;
            set
            {
                if( gyroDevice_ != value )
                {
                    gyroDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class GyroHeadingMagneticNorthTimeseriesObject : DoubleTimeseriesObject
    {
        Guid gyroDevice_;
        public GyroHeadingMagneticNorthTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GyroHeadingMagneticNorthTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new GyroHeadingMagneticNorthTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GyroHeadingMagneticNorthTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid GyroDevice
        {
            get => gyroDevice_;
            set
            {
                if( gyroDevice_ != value )
                {
                    gyroDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class GyroHeadingTrueNorthTimeseriesObject : DoubleTimeseriesObject
    {
        Guid gyroDevice_;
        public GyroHeadingTrueNorthTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GyroHeadingTrueNorthTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new GyroHeadingTrueNorthTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GyroHeadingTrueNorthTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid GyroDevice
        {
            get => gyroDevice_;
            set
            {
                if( gyroDevice_ != value )
                {
                    gyroDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class GyroPitchTimeseriesObject : DoubleTimeseriesObject
    {
        Guid gyroDevice_;
        public GyroPitchTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GyroPitchTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new GyroPitchTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GyroPitchTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid GyroDevice
        {
            get => gyroDevice_;
            set
            {
                if( gyroDevice_ != value )
                {
                    gyroDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class GyroRateOfTurnTimeseriesObject : DoubleTimeseriesObject
    {
        Guid gyroDevice_;
        public GyroRateOfTurnTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GyroRateOfTurnTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new GyroRateOfTurnTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GyroRateOfTurnTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid GyroDevice
        {
            get => gyroDevice_;
            set
            {
                if( gyroDevice_ != value )
                {
                    gyroDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class GyroRollTimeseriesObject : DoubleTimeseriesObject
    {
        Guid gyroDevice_;
        public GyroRollTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GyroRollTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new GyroRollTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GyroRollTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid GyroDevice
        {
            get => gyroDevice_;
            set
            {
                if( gyroDevice_ != value )
                {
                    gyroDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class GyroSpeedTimeseriesObject : DoubleTimeseriesObject
    {
        Guid gyroDevice_;
        public GyroSpeedTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GyroSpeedTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new GyroSpeedTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GyroSpeedTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid GyroDevice
        {
            get => gyroDevice_;
            set
            {
                if( gyroDevice_ != value )
                {
                    gyroDevice_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarLatitudeTimeseriesObject : DoubleTimeseriesObject
    {
        Guid radar_;
        public RadarLatitudeTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarLatitudeTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarLatitudeTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarLatitudeTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarLongitudeTimeseriesObject : DoubleTimeseriesObject
    {
        Guid radar_;
        public RadarLongitudeTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarLongitudeTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarLongitudeTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarLongitudeTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadomeDewPointTimeseriesObject : DoubleTimeseriesObject
    {
        Guid radome_;
        public RadomeDewPointTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadomeDewPointTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new RadomeDewPointTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadomeDewPointTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Radome
        {
            get => radome_;
            set
            {
                if( radome_ != value )
                {
                    radome_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadomePressureTimeseriesObject : DoubleTimeseriesObject
    {
        Guid radome_;
        public RadomePressureTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadomePressureTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new RadomePressureTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadomePressureTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Radome
        {
            get => radome_;
            set
            {
                if( radome_ != value )
                {
                    radome_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadomeTemperatureTimeseriesObject : DoubleTimeseriesObject
    {
        Guid radome_;
        public RadomeTemperatureTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadomeTemperatureTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new RadomeTemperatureTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadomeTemperatureTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Radome
        {
            get => radome_;
            set
            {
                if( radome_ != value )
                {
                    radome_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class VesselDraughtTimeseriesObject : DoubleTimeseriesObject
    {
        Guid vessel_;
        public VesselDraughtTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.VesselDraughtTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new VesselDraughtTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.VesselDraughtTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Vessel
        {
            get => vessel_;
            set
            {
                if( vessel_ != value )
                {
                    vessel_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class ViewLatitudeTimeseriesObject : DoubleTimeseriesObject
    {
        Guid view_;
        public ViewLatitudeTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.ViewLatitudeTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new ViewLatitudeTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.ViewLatitudeTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid View
        {
            get => view_;
            set
            {
                if( view_ != value )
                {
                    view_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class ViewLongitudeTimeseriesObject : DoubleTimeseriesObject
    {
        Guid view_;
        public ViewLongitudeTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.ViewLongitudeTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new ViewLongitudeTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.ViewLongitudeTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid View
        {
            get => view_;
            set
            {
                if( view_ != value )
                {
                    view_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class ViewZoomLevelTimeseriesObject : DoubleTimeseriesObject
    {
        Guid view_;
        public ViewZoomLevelTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.ViewZoomLevelTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new ViewZoomLevelTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.ViewZoomLevelTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid View
        {
            get => view_;
            set
            {
                if( view_ != value )
                {
                    view_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class WeatherStationAbsoluteHumidityTimeseriesObject : DoubleTimeseriesObject
    {
        Guid weatherStation_;
        public WeatherStationAbsoluteHumidityTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.WeatherStationAbsoluteHumidityTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new WeatherStationAbsoluteHumidityTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.WeatherStationAbsoluteHumidityTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid WeatherStation
        {
            get => weatherStation_;
            set
            {
                if( weatherStation_ != value )
                {
                    weatherStation_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class WeatherStationAirTemperatureTimeseriesObject : DoubleTimeseriesObject
    {
        Guid weatherStation_;
        public WeatherStationAirTemperatureTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.WeatherStationAirTemperatureTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new WeatherStationAirTemperatureTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.WeatherStationAirTemperatureTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid WeatherStation
        {
            get => weatherStation_;
            set
            {
                if( weatherStation_ != value )
                {
                    weatherStation_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class WeatherStationBarometricPressureTimeseriesObject : DoubleTimeseriesObject
    {
        Guid weatherStation_;
        public WeatherStationBarometricPressureTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.WeatherStationBarometricPressureTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new WeatherStationBarometricPressureTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.WeatherStationBarometricPressureTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid WeatherStation
        {
            get => weatherStation_;
            set
            {
                if( weatherStation_ != value )
                {
                    weatherStation_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class WeatherStationDewPointTimeseriesObject : DoubleTimeseriesObject
    {
        Guid weatherStation_;
        public WeatherStationDewPointTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.WeatherStationDewPointTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new WeatherStationDewPointTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.WeatherStationDewPointTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid WeatherStation
        {
            get => weatherStation_;
            set
            {
                if( weatherStation_ != value )
                {
                    weatherStation_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class WeatherStationRelativeHumidityTimeseriesObject : DoubleTimeseriesObject
    {
        Guid weatherStation_;
        public WeatherStationRelativeHumidityTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.WeatherStationRelativeHumidityTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new WeatherStationRelativeHumidityTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.WeatherStationRelativeHumidityTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid WeatherStation
        {
            get => weatherStation_;
            set
            {
                if( weatherStation_ != value )
                {
                    weatherStation_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class WeatherStationWaterTemperatureTimeseriesObject : DoubleTimeseriesObject
    {
        Guid weatherStation_;
        public WeatherStationWaterTemperatureTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.WeatherStationWaterTemperatureTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new WeatherStationWaterTemperatureTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.WeatherStationWaterTemperatureTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid WeatherStation
        {
            get => weatherStation_;
            set
            {
                if( weatherStation_ != value )
                {
                    weatherStation_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class WeatherStationWindDirectionTimeseriesObject : DoubleTimeseriesObject
    {
        Guid weatherStation_;
        public WeatherStationWindDirectionTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.WeatherStationWindDirectionTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new WeatherStationWindDirectionTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.WeatherStationWindDirectionTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid WeatherStation
        {
            get => weatherStation_;
            set
            {
                if( weatherStation_ != value )
                {
                    weatherStation_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class WeatherStationWindSpeedTimeseriesObject : DoubleTimeseriesObject
    {
        Guid weatherStation_;
        public WeatherStationWindSpeedTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.WeatherStationWindSpeedTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new WeatherStationWindSpeedTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.WeatherStationWindSpeedTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid WeatherStation
        {
            get => weatherStation_;
            set
            {
                if( weatherStation_ != value )
                {
                    weatherStation_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class GeoPosition2DTimeseriesObject : TimeseriesObject
    {
        public GeoPosition2DTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GeoPosition2DTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new GeoPosition2DTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GeoPosition2DTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class AisAidToNavigationPositionTimeseriesObject : GeoPosition2DTimeseriesObject
    {
        Guid aidToNavigation_;
        public AisAidToNavigationPositionTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.AisAidToNavigationPositionTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new AisAidToNavigationPositionTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.AisAidToNavigationPositionTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid AidToNavigation
        {
            get => aidToNavigation_;
            set
            {
                if( aidToNavigation_ != value )
                {
                    aidToNavigation_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class GeoPosition3DTimeseriesObject : TimeseriesObject
    {
        public GeoPosition3DTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GeoPosition3DTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new GeoPosition3DTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GeoPosition3DTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class GuidTimeseriesObject : TimeseriesObject
    {
        public GuidTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.GuidTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new GuidTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.GuidTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class Int16TimeseriesObject : TimeseriesObject
    {
        public Int16TimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Int16Timeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new Int16TimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Int16Timeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class Int32TimeseriesObject : TimeseriesObject
    {
        public Int32TimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Int32Timeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new Int32TimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Int32Timeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class RadarAzimuthOffsetTimeseriesObject : Int32TimeseriesObject
    {
        Guid radar_;
        public RadarAzimuthOffsetTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarAzimuthOffsetTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarAzimuthOffsetTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarAzimuthOffsetTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarFastTimeConstantLevelTimeseriesObject : Int32TimeseriesObject
    {
        Guid radar_;
        public RadarFastTimeConstantLevelTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarFastTimeConstantLevelTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarFastTimeConstantLevelTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarFastTimeConstantLevelTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarFastTimeConstantModeTimeseriesObject : Int32TimeseriesObject
    {
        Guid radar_;
        public RadarFastTimeConstantModeTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarFastTimeConstantModeTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarFastTimeConstantModeTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarFastTimeConstantModeTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarPulseTimeseriesObject : Int32TimeseriesObject
    {
        Guid radar_;
        public RadarPulseTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarPulseTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarPulseTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarPulseTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarSector1EndTimeseriesObject : Int32TimeseriesObject
    {
        Guid radar_;
        public RadarSector1EndTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarSector1EndTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarSector1EndTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarSector1EndTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarSector1StartTimeseriesObject : Int32TimeseriesObject
    {
        Guid radar_;
        public RadarSector1StartTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarSector1StartTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarSector1StartTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarSector1StartTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarSector2EndTimeseriesObject : Int32TimeseriesObject
    {
        Guid radar_;
        public RadarSector2EndTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarSector2EndTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarSector2EndTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarSector2EndTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarSector2StartTimeseriesObject : Int32TimeseriesObject
    {
        Guid radar_;
        public RadarSector2StartTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarSector2StartTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarSector2StartTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarSector2StartTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarSensitivityTimeControlLevelTimeseriesObject : Int32TimeseriesObject
    {
        Guid radar_;
        public RadarSensitivityTimeControlLevelTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarSensitivityTimeControlLevelTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarSensitivityTimeControlLevelTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarSensitivityTimeControlLevelTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class RadarTuningTimeseriesObject : Int32TimeseriesObject
    {
        Guid radar_;
        public RadarTuningTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadarTuningTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new RadarTuningTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadarTuningTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Radar
        {
            get => radar_;
            set
            {
                if( radar_ != value )
                {
                    radar_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class VesselPersonsOnBoardTimeseriesObject : Int32TimeseriesObject
    {
        Guid vessel_;
        public VesselPersonsOnBoardTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.VesselPersonsOnBoardTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new VesselPersonsOnBoardTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.VesselPersonsOnBoardTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Vessel
        {
            get => vessel_;
            set
            {
                if( vessel_ != value )
                {
                    vessel_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class Int64TimeseriesObject : TimeseriesObject
    {
        public Int64TimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Int64Timeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new Int64TimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Int64Timeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class Position2DTimeseriesObject : TimeseriesObject
    {
        public Position2DTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Position2DTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new Position2DTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Position2DTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class Position3DTimeseriesObject : TimeseriesObject
    {
        public Position3DTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Position3DTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new Position3DTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Position3DTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class ReferenceTimeseriesObject : TimeseriesObject
    {
        public ReferenceTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.ReferenceTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new ReferenceTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.ReferenceTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class SByteTimeseriesObject : TimeseriesObject
    {
        public SByteTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.SByteTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new SByteTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.SByteTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class SingleTimeseriesObject : TimeseriesObject
    {
        public SingleTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.SingleTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new SingleTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.SingleTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class StringTimeseriesObject : TimeseriesObject
    {
        public StringTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.StringTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new StringTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.StringTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class TimeSpanTimeseriesObject : TimeseriesObject
    {
        public TimeSpanTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.TimeSpanTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new TimeSpanTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.TimeSpanTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class UInt16TimeseriesObject : TimeseriesObject
    {
        public UInt16TimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.UInt16Timeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new UInt16TimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.UInt16Timeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class UInt32TimeseriesObject : TimeseriesObject
    {
        public UInt32TimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.UInt32Timeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new UInt32TimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.UInt32Timeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class RadomeStatusTimeseriesObject : UInt32TimeseriesObject
    {
        Guid radome_;
        public RadomeStatusTimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.RadomeStatusTimeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new RadomeStatusTimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.RadomeStatusTimeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public Guid Radome
        {
            get => radome_;
            set
            {
                if( radome_ != value )
                {
                    radome_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class UInt64TimeseriesObject : TimeseriesObject
    {
        public UInt64TimeseriesObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.UInt64Timeseries;
        }

        public override BaseData<Kind> Create()
        {
            return new UInt64TimeseriesObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.UInt64Timeseries )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class TimeseriesCatalogObject : TimeseriesCatalogElementObject
    {
        public TimeseriesCatalogObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.TimeseriesCatalog;
        }

        public override BaseData<Kind> Create()
        {
            return new TimeseriesCatalogObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.TimeseriesCatalog )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class TimeseriesInfoObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        DateTime? firstTimestamp_;
        DateTime? lastTimestamp_;
        long count_ = 0;
        public TimeseriesInfoObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.TimeseriesInfo;
        }

        public override BaseData<Kind> Create()
        {
            return new TimeseriesInfoObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.TimeseriesInfo )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime? FirstTimestamp
        {
            get => firstTimestamp_;
            set
            {
                if( firstTimestamp_ != value )
                {
                    firstTimestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime? LastTimestamp
        {
            get => lastTimestamp_;
            set
            {
                if( lastTimestamp_ != value )
                {
                    lastTimestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public long Count
        {
            get => count_;
            set
            {
                if( count_ != value )
                {
                    count_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class TimeSpanTimeseriesValueObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        TimeSpan? value_;
        public TimeSpanTimeseriesValueObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.TimeSpanTimeseriesValue;
        }

        public override BaseData<Kind> Create()
        {
            return new TimeSpanTimeseriesValueObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.TimeSpanTimeseriesValue )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan? Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class TrackableItemTrackLinkObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid item_;
        Guid track_;
        DateTime start_;
        DateTime? end_;
        public TrackableItemTrackLinkObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.TrackableItemTrackLink;
        }

        public override BaseData<Kind> Create()
        {
            return new TrackableItemTrackLinkObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.TrackableItemTrackLink )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Item
        {
            get => item_;
            set
            {
                if( item_ != value )
                {
                    item_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Track
        {
            get => track_;
            set
            {
                if( track_ != value )
                {
                    track_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Start
        {
            get => start_;
            set
            {
                if( start_ != value )
                {
                    start_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime? End
        {
            get => end_;
            set
            {
                if( end_ != value )
                {
                    end_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public abstract class TrackBaseObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid tracker_;
        long trackNumber_ = 0;
        DateTime timestamp_;
        protected TrackBaseObject ( )
        {
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.TrackBase )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Tracker
        {
            get => tracker_;
            set
            {
                if( tracker_ != value )
                {
                    tracker_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public long TrackNumber
        {
            get => trackNumber_;
            set
            {
                if( trackNumber_ != value )
                {
                    trackNumber_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class TrackObject : TrackBaseObject
    {
        public TrackObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Track;
        }

        public override BaseData<Kind> Create()
        {
            return new TrackObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Track )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class Track3DObject : TrackBaseObject
    {
        public Track3DObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.Track3D;
        }

        public override BaseData<Kind> Create()
        {
            return new Track3DObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Track3D )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

    }
    public class TrackerFilterParametersObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid tracker_;
        string name_ = string.Empty;
        public TrackerFilterParametersObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.TrackerFilterParameters;
        }

        public override BaseData<Kind> Create()
        {
            return new TrackerFilterParametersObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.TrackerFilterParameters )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Tracker
        {
            get => tracker_;
            set
            {
                if( tracker_ != value )
                {
                    tracker_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class TrackerFilterParametersConfigurationObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid parameters_;
        DateTime timestamp_;
        bool useNaivePredictor_ = false;
        int numberOfPoints_ = 0;
        int windowSize_ = 0;
        int stabilizeCount_ = 0;
        int maxBadPoints_ = 0;
        Types.TrackerFilterModelType modelType_ = Types.TrackerFilterModelType.Unknown;
        double sigmaR_ = 0.0;
        double sigmaAcc_ = 0.0;
        double tauVel_ = 0.0;
        double tauAcc_ = 0.0;
        double deltaRMin_ = 0.0;
        double deltaVMax_ = 0.0;
        double deltaAMax_ = 0.0;
        public TrackerFilterParametersConfigurationObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.TrackerFilterParametersConfiguration;
        }

        public override BaseData<Kind> Create()
        {
            return new TrackerFilterParametersConfigurationObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.TrackerFilterParametersConfiguration )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Parameters
        {
            get => parameters_;
            set
            {
                if( parameters_ != value )
                {
                    parameters_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool UseNaivePredictor
        {
            get => useNaivePredictor_;
            set
            {
                if( useNaivePredictor_ != value )
                {
                    useNaivePredictor_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int NumberOfPoints
        {
            get => numberOfPoints_;
            set
            {
                if( numberOfPoints_ != value )
                {
                    numberOfPoints_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int WindowSize
        {
            get => windowSize_;
            set
            {
                if( windowSize_ != value )
                {
                    windowSize_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int StabilizeCount
        {
            get => stabilizeCount_;
            set
            {
                if( stabilizeCount_ != value )
                {
                    stabilizeCount_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int MaxBadPoints
        {
            get => maxBadPoints_;
            set
            {
                if( maxBadPoints_ != value )
                {
                    maxBadPoints_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.TrackerFilterModelType ModelType
        {
            get => modelType_;
            set
            {
                if( modelType_ != value )
                {
                    modelType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double SigmaR
        {
            get => sigmaR_;
            set
            {
                if( sigmaR_ != value )
                {
                    sigmaR_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double SigmaAcc
        {
            get => sigmaAcc_;
            set
            {
                if( sigmaAcc_ != value )
                {
                    sigmaAcc_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double TauVel
        {
            get => tauVel_;
            set
            {
                if( tauVel_ != value )
                {
                    tauVel_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double TauAcc
        {
            get => tauAcc_;
            set
            {
                if( tauAcc_ != value )
                {
                    tauAcc_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double DeltaRMin
        {
            get => deltaRMin_;
            set
            {
                if( deltaRMin_ != value )
                {
                    deltaRMin_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double DeltaVMax
        {
            get => deltaVMax_;
            set
            {
                if( deltaVMax_ != value )
                {
                    deltaVMax_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double DeltaAMax
        {
            get => deltaAMax_;
            set
            {
                if( deltaAMax_ != value )
                {
                    deltaAMax_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class TrackInfoObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        DateTime? firstTimestamp_;
        DateTime? lastTimestamp_;
        long count_ = 0;
        double? northWestLatitude_;
        double? northWestLongitude_;
        double? southEastLatitude_;
        double? southEastLongitude_;
        public TrackInfoObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.TrackInfo;
        }

        public override BaseData<Kind> Create()
        {
            return new TrackInfoObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.TrackInfo )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime? FirstTimestamp
        {
            get => firstTimestamp_;
            set
            {
                if( firstTimestamp_ != value )
                {
                    firstTimestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime? LastTimestamp
        {
            get => lastTimestamp_;
            set
            {
                if( lastTimestamp_ != value )
                {
                    lastTimestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public long Count
        {
            get => count_;
            set
            {
                if( count_ != value )
                {
                    count_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? NorthWestLatitude
        {
            get => northWestLatitude_;
            set
            {
                if( northWestLatitude_ != value )
                {
                    northWestLatitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? NorthWestLongitude
        {
            get => northWestLongitude_;
            set
            {
                if( northWestLongitude_ != value )
                {
                    northWestLongitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? SouthEastLatitude
        {
            get => southEastLatitude_;
            set
            {
                if( southEastLatitude_ != value )
                {
                    southEastLatitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? SouthEastLongitude
        {
            get => southEastLongitude_;
            set
            {
                if( southEastLongitude_ != value )
                {
                    southEastLongitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class TrackingServiceOptionsObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        DateTime timestamp_;
        TimeSpan timerInterval_;
        TimeSpan maxAgeOfCurrentTrackValue_;
        double falseThreshold_ = 0.0;
        double distanceThreshold_ = 0.0;
        double distanceUnmergeThreshold_ = 0.0;
        long unmergeLatency_ = 0;
        bool kalmanFiltering_ = false;
        double maxCourseDeviation_ = 0.0;
        double maxSpeedDeviation_ = 0.0;
        double minimumSpeedThreshold_ = 0.0;
        public TrackingServiceOptionsObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.TrackingServiceOptions;
        }

        public override BaseData<Kind> Create()
        {
            return new TrackingServiceOptionsObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.TrackingServiceOptions )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan TimerInterval
        {
            get => timerInterval_;
            set
            {
                if( timerInterval_ != value )
                {
                    timerInterval_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan MaxAgeOfCurrentTrackValue
        {
            get => maxAgeOfCurrentTrackValue_;
            set
            {
                if( maxAgeOfCurrentTrackValue_ != value )
                {
                    maxAgeOfCurrentTrackValue_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double FalseThreshold
        {
            get => falseThreshold_;
            set
            {
                if( falseThreshold_ != value )
                {
                    falseThreshold_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double DistanceThreshold
        {
            get => distanceThreshold_;
            set
            {
                if( distanceThreshold_ != value )
                {
                    distanceThreshold_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double DistanceUnmergeThreshold
        {
            get => distanceUnmergeThreshold_;
            set
            {
                if( distanceUnmergeThreshold_ != value )
                {
                    distanceUnmergeThreshold_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public long UnmergeLatency
        {
            get => unmergeLatency_;
            set
            {
                if( unmergeLatency_ != value )
                {
                    unmergeLatency_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool KalmanFiltering
        {
            get => kalmanFiltering_;
            set
            {
                if( kalmanFiltering_ != value )
                {
                    kalmanFiltering_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MaxCourseDeviation
        {
            get => maxCourseDeviation_;
            set
            {
                if( maxCourseDeviation_ != value )
                {
                    maxCourseDeviation_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MaxSpeedDeviation
        {
            get => maxSpeedDeviation_;
            set
            {
                if( maxSpeedDeviation_ != value )
                {
                    maxSpeedDeviation_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double MinimumSpeedThreshold
        {
            get => minimumSpeedThreshold_;
            set
            {
                if( minimumSpeedThreshold_ != value )
                {
                    minimumSpeedThreshold_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class TrackLinkObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid primary_;
        Guid secondary_;
        DateTime start_;
        DateTime? end_;
        public TrackLinkObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.TrackLink;
        }

        public override BaseData<Kind> Create()
        {
            return new TrackLinkObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.TrackLink )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Primary
        {
            get => primary_;
            set
            {
                if( primary_ != value )
                {
                    primary_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Secondary
        {
            get => secondary_;
            set
            {
                if( secondary_ != value )
                {
                    secondary_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Start
        {
            get => start_;
            set
            {
                if( start_ != value )
                {
                    start_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime? End
        {
            get => end_;
            set
            {
                if( end_ != value )
                {
                    end_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class TrackValueObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid track_;
        DateTime timestamp_;
        Types.TrackFlags flags_ = Types.TrackFlags.None;
        Types.TrackStatus status_ = Types.TrackStatus.Unknown;
        double latitude_ = 0.0;
        double longitude_ = 0.0;
        double speed_ = 0.0;
        double course_ = 0.0;
        double heading_ = 0.0;
        public TrackValueObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.TrackValue;
        }

        public override BaseData<Kind> Create()
        {
            return new TrackValueObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.TrackValue )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Track
        {
            get => track_;
            set
            {
                if( track_ != value )
                {
                    track_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.TrackFlags Flags
        {
            get => flags_;
            set
            {
                if( flags_ != value )
                {
                    flags_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.TrackStatus Status
        {
            get => status_;
            set
            {
                if( status_ != value )
                {
                    status_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Latitude
        {
            get => latitude_;
            set
            {
                if( latitude_ != value )
                {
                    latitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Longitude
        {
            get => longitude_;
            set
            {
                if( longitude_ != value )
                {
                    longitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Speed
        {
            get => speed_;
            set
            {
                if( speed_ != value )
                {
                    speed_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Course
        {
            get => course_;
            set
            {
                if( course_ != value )
                {
                    course_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Heading
        {
            get => heading_;
            set
            {
                if( heading_ != value )
                {
                    heading_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class TrackValue3DObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid track_;
        DateTime timestamp_;
        Types.TrackFlags3D flags_ = Types.TrackFlags3D.None;
        uint status_ = 0;
        double latitude_ = 0.0;
        double longitude_ = 0.0;
        double altitude_ = 0.0;
        double speed_ = 0.0;
        double course_ = 0.0;
        double rateOfClimb_ = 0.0;
        public TrackValue3DObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.TrackValue3D;
        }

        public override BaseData<Kind> Create()
        {
            return new TrackValue3DObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.TrackValue3D )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Track
        {
            get => track_;
            set
            {
                if( track_ != value )
                {
                    track_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.TrackFlags3D Flags
        {
            get => flags_;
            set
            {
                if( flags_ != value )
                {
                    flags_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public uint Status
        {
            get => status_;
            set
            {
                if( status_ != value )
                {
                    status_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Latitude
        {
            get => latitude_;
            set
            {
                if( latitude_ != value )
                {
                    latitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Longitude
        {
            get => longitude_;
            set
            {
                if( longitude_ != value )
                {
                    longitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Altitude
        {
            get => altitude_;
            set
            {
                if( altitude_ != value )
                {
                    altitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Speed
        {
            get => speed_;
            set
            {
                if( speed_ != value )
                {
                    speed_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Course
        {
            get => course_;
            set
            {
                if( course_ != value )
                {
                    course_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double RateOfClimb
        {
            get => rateOfClimb_;
            set
            {
                if( rateOfClimb_ != value )
                {
                    rateOfClimb_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class UInt16TimeseriesValueObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        ushort? value_;
        public UInt16TimeseriesValueObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.UInt16TimeseriesValue;
        }

        public override BaseData<Kind> Create()
        {
            return new UInt16TimeseriesValueObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.UInt16TimeseriesValue )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public ushort? Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class UInt32TimeseriesValueObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        uint? value_;
        public UInt32TimeseriesValueObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.UInt32TimeseriesValue;
        }

        public override BaseData<Kind> Create()
        {
            return new UInt32TimeseriesValueObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.UInt32TimeseriesValue )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public uint? Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class UInt64TimeseriesValueObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid timeseries_;
        DateTime timestamp_;
        long? value_;
        public UInt64TimeseriesValueObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.UInt64TimeseriesValue;
        }

        public override BaseData<Kind> Create()
        {
            return new UInt64TimeseriesValueObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.UInt64TimeseriesValue )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Timeseries
        {
            get => timeseries_;
            set
            {
                if( timeseries_ != value )
                {
                    timeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public long? Value
        {
            get => value_;
            set
            {
                if( value_ != value )
                {
                    value_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class VehicleTypeObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        string name_ = string.Empty;
        public VehicleTypeObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.VehicleType;
        }

        public override BaseData<Kind> Create()
        {
            return new VehicleTypeObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.VehicleType )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class VesselTypeObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        string name_ = string.Empty;
        int code_ = 0;
        public VesselTypeObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.VesselType;
        }

        public override BaseData<Kind> Create()
        {
            return new VesselTypeObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.VesselType )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public int Code
        {
            get => code_;
            set
            {
                if( code_ != value )
                {
                    code_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class ViewObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        string name_ = string.Empty;
        Guid latitudeTimeseries_;
        Guid longitudeTimeseries_;
        Guid zoomLevelTimeseries_;
        public ViewObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.View;
        }

        public override BaseData<Kind> Create()
        {
            return new ViewObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.View )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid LatitudeTimeseries
        {
            get => latitudeTimeseries_;
            set
            {
                if( latitudeTimeseries_ != value )
                {
                    latitudeTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid LongitudeTimeseries
        {
            get => longitudeTimeseries_;
            set
            {
                if( longitudeTimeseries_ != value )
                {
                    longitudeTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid ZoomLevelTimeseries
        {
            get => zoomLevelTimeseries_;
            set
            {
                if( zoomLevelTimeseries_ != value )
                {
                    zoomLevelTimeseries_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class ViewCameraLinkObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid view_;
        Guid camera_;
        DateTime start_;
        DateTime? end_;
        public ViewCameraLinkObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.ViewCameraLink;
        }

        public override BaseData<Kind> Create()
        {
            return new ViewCameraLinkObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.ViewCameraLink )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid View
        {
            get => view_;
            set
            {
                if( view_ != value )
                {
                    view_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Camera
        {
            get => camera_;
            set
            {
                if( camera_ != value )
                {
                    camera_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Start
        {
            get => start_;
            set
            {
                if( start_ != value )
                {
                    start_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime? End
        {
            get => end_;
            set
            {
                if( end_ != value )
                {
                    end_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class ViewTrackerLinkObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid view_;
        Guid tracker_;
        DateTime start_;
        DateTime? end_;
        public ViewTrackerLinkObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.ViewTrackerLink;
        }

        public override BaseData<Kind> Create()
        {
            return new ViewTrackerLinkObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.ViewTrackerLink )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid View
        {
            get => view_;
            set
            {
                if( view_ != value )
                {
                    view_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Tracker
        {
            get => tracker_;
            set
            {
                if( tracker_ != value )
                {
                    tracker_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Start
        {
            get => start_;
            set
            {
                if( start_ != value )
                {
                    start_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime? End
        {
            get => end_;
            set
            {
                if( end_ != value )
                {
                    end_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class WeatherStationCommandObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid weatherStation_;
        DateTime timestamp_;
        Types.DeviceCommandSourceType deviceCommandSourceType_ = Types.DeviceCommandSourceType.Unknown;
        Guid deviceCommandSourceId_;
        Guid reply_;
        public WeatherStationCommandObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.WeatherStationCommand;
        }

        public override BaseData<Kind> Create()
        {
            return new WeatherStationCommandObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.WeatherStationCommand )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid WeatherStation
        {
            get => weatherStation_;
            set
            {
                if( weatherStation_ != value )
                {
                    weatherStation_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.DeviceCommandSourceType DeviceCommandSourceType
        {
            get => deviceCommandSourceType_;
            set
            {
                if( deviceCommandSourceType_ != value )
                {
                    deviceCommandSourceType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid DeviceCommandSourceId
        {
            get => deviceCommandSourceId_;
            set
            {
                if( deviceCommandSourceId_ != value )
                {
                    deviceCommandSourceId_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Reply
        {
            get => reply_;
            set
            {
                if( reply_ != value )
                {
                    reply_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class WeatherStationCommandReplyObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid weatherStation_;
        DateTime timestamp_;
        Guid command_;
        Types.DeviceCommandReplyStatus status_ = Types.DeviceCommandReplyStatus.Unknown;
        string message_ = string.Empty;
        public WeatherStationCommandReplyObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.WeatherStationCommandReply;
        }

        public override BaseData<Kind> Create()
        {
            return new WeatherStationCommandReplyObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.WeatherStationCommandReply )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid WeatherStation
        {
            get => weatherStation_;
            set
            {
                if( weatherStation_ != value )
                {
                    weatherStation_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Command
        {
            get => command_;
            set
            {
                if( command_ != value )
                {
                    command_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.DeviceCommandReplyStatus Status
        {
            get => status_;
            set
            {
                if( status_ != value )
                {
                    status_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Message
        {
            get => message_;
            set
            {
                if( message_ != value )
                {
                    message_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class WeatherStationConfigurationObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid weatherStation_;
        DateTime timestamp_;
        TimeSpan noDataTimeOut_;
        TimeSpan sendInterval_;
        double latitude_ = 0.0;
        double longitude_ = 0.0;
        double gyroOffset_ = 0.0;
        bool enableAveraging_ = false;
        TimeSpan averagingInterval_;
        public WeatherStationConfigurationObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.WeatherStationConfiguration;
        }

        public override BaseData<Kind> Create()
        {
            return new WeatherStationConfigurationObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.WeatherStationConfiguration )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid WeatherStation
        {
            get => weatherStation_;
            set
            {
                if( weatherStation_ != value )
                {
                    weatherStation_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan NoDataTimeOut
        {
            get => noDataTimeOut_;
            set
            {
                if( noDataTimeOut_ != value )
                {
                    noDataTimeOut_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan SendInterval
        {
            get => sendInterval_;
            set
            {
                if( sendInterval_ != value )
                {
                    sendInterval_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Latitude
        {
            get => latitude_;
            set
            {
                if( latitude_ != value )
                {
                    latitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Longitude
        {
            get => longitude_;
            set
            {
                if( longitude_ != value )
                {
                    longitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double GyroOffset
        {
            get => gyroOffset_;
            set
            {
                if( gyroOffset_ != value )
                {
                    gyroOffset_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public bool EnableAveraging
        {
            get => enableAveraging_;
            set
            {
                if( enableAveraging_ != value )
                {
                    enableAveraging_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan AveragingInterval
        {
            get => averagingInterval_;
            set
            {
                if( averagingInterval_ != value )
                {
                    averagingInterval_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public abstract class ZoneObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        string name_ = string.Empty;
        double longitude_ = 0.0;
        double latitude_ = 0.0;
        Types.ZoneAlarmType alarmType_ = Types.ZoneAlarmType.None;
        TimeSpan alarmTime_;
        TimeSpan radarTrackMinimumLifetime_;
        double speed_ = 0.0;
        uint strokeColor_ = 0;
        uint fillColor_ = 0;
        protected ZoneObject ( )
        {
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.Zone )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public string Name
        {
            get => name_;
            set
            {
                if( name_ != value )
                {
                    name_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Longitude
        {
            get => longitude_;
            set
            {
                if( longitude_ != value )
                {
                    longitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Latitude
        {
            get => latitude_;
            set
            {
                if( latitude_ != value )
                {
                    latitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Types.ZoneAlarmType AlarmType
        {
            get => alarmType_;
            set
            {
                if( alarmType_ != value )
                {
                    alarmType_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan AlarmTime
        {
            get => alarmTime_;
            set
            {
                if( alarmTime_ != value )
                {
                    alarmTime_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public TimeSpan RadarTrackMinimumLifetime
        {
            get => radarTrackMinimumLifetime_;
            set
            {
                if( radarTrackMinimumLifetime_ != value )
                {
                    radarTrackMinimumLifetime_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Speed
        {
            get => speed_;
            set
            {
                if( speed_ != value )
                {
                    speed_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public uint StrokeColor
        {
            get => strokeColor_;
            set
            {
                if( strokeColor_ != value )
                {
                    strokeColor_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public uint FillColor
        {
            get => fillColor_;
            set
            {
                if( fillColor_ != value )
                {
                    fillColor_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class CircularZoneObject : ZoneObject
    {
        double radius_ = 0.0;
        public CircularZoneObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.CircularZone;
        }

        public override BaseData<Kind> Create()
        {
            return new CircularZoneObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.CircularZone )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public double Radius
        {
            get => radius_;
            set
            {
                if( radius_ != value )
                {
                    radius_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class PolygonZoneObject : ZoneObject
    {
        byte[] polygon_ = Array.Empty<byte>();
        public PolygonZoneObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.PolygonZone;
        }

        public override BaseData<Kind> Create()
        {
            return new PolygonZoneObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.PolygonZone )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public byte[] Polygon
        {
            get => polygon_;
            set
            {
                if( polygon_ != value )
                {
                    polygon_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class ZoneExceptionsObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid zone_;
        DateTime timestamp_;
        public ZoneExceptionsObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.ZoneExceptions;
        }

        public override BaseData<Kind> Create()
        {
            return new ZoneExceptionsObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.ZoneExceptions )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Zone
        {
            get => zone_;
            set
            {
                if( zone_ != value )
                {
                    zone_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class ZoneExceptionsVesselLinkObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid zoneExceptions_;
        Guid vessel_;
        public ZoneExceptionsVesselLinkObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.ZoneExceptionsVesselLink;
        }

        public override BaseData<Kind> Create()
        {
            return new ZoneExceptionsVesselLinkObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.ZoneExceptionsVesselLink )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid ZoneExceptions
        {
            get => zoneExceptions_;
            set
            {
                if( zoneExceptions_ != value )
                {
                    zoneExceptions_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Vessel
        {
            get => vessel_;
            set
            {
                if( vessel_ != value )
                {
                    vessel_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
    public class ZoneTrackAlarmObject : BaseDataGuid<Kind>
    {
        long rowVersion_ = 0;
        Guid track_;
        Guid zone_;
        Guid radarTrack_;
        DateTime timestamp_;
        double latitude_ = 0.0;
        double longitude_ = 0.0;
        double speed_ = 0.0;
        double? course_;
        double? heading_;
        double enterLatitude_ = 0.0;
        double enterLongitude_ = 0.0;
        double? leaveLatitude_;
        double? leaveLongitude_;
        public ZoneTrackAlarmObject ( )
        {
        }

        public override Kind GetObjectType()
        {
            return Kind.ZoneTrackAlarm;
        }

        public override BaseData<Kind> Create()
        {
            return new ZoneTrackAlarmObject( );
        }

        public override bool IsOfType(Kind objectType)
        {
            if( objectType == Kind.ZoneTrackAlarm )
            {
                return true;
            }
            return base.IsOfType( objectType );
        }

        public long RowVersion
        {
            get => rowVersion_;
            set
            {
                if( rowVersion_ != value )
                {
                    rowVersion_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Track
        {
            get => track_;
            set
            {
                if( track_ != value )
                {
                    track_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid Zone
        {
            get => zone_;
            set
            {
                if( zone_ != value )
                {
                    zone_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public Guid RadarTrack
        {
            get => radarTrack_;
            set
            {
                if( radarTrack_ != value )
                {
                    radarTrack_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public DateTime Timestamp
        {
            get => timestamp_;
            set
            {
                if( timestamp_ != value )
                {
                    timestamp_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Latitude
        {
            get => latitude_;
            set
            {
                if( latitude_ != value )
                {
                    latitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Longitude
        {
            get => longitude_;
            set
            {
                if( longitude_ != value )
                {
                    longitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double Speed
        {
            get => speed_;
            set
            {
                if( speed_ != value )
                {
                    speed_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? Course
        {
            get => course_;
            set
            {
                if( course_ != value )
                {
                    course_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? Heading
        {
            get => heading_;
            set
            {
                if( heading_ != value )
                {
                    heading_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double EnterLatitude
        {
            get => enterLatitude_;
            set
            {
                if( enterLatitude_ != value )
                {
                    enterLatitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double EnterLongitude
        {
            get => enterLongitude_;
            set
            {
                if( enterLongitude_ != value )
                {
                    enterLongitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? LeaveLatitude
        {
            get => leaveLatitude_;
            set
            {
                if( leaveLatitude_ != value )
                {
                    leaveLatitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
        public double? LeaveLongitude
        {
            get => leaveLongitude_;
            set
            {
                if( leaveLongitude_ != value )
                {
                    leaveLongitude_ = value;
                    OnPropertyChanged( );
                }
            }
        }
    }
}
