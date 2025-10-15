package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class LineInputDeviceConfigurationObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _lineInputDevice;
    private DateTime _timestamp;
    private boolean _storeReceivedSentences = false;
    private boolean _storeSentMessages = false;
    private boolean _storeUnsentMessages = false;
    private boolean _nMEA = false;
    private boolean _strictNMEA = false;
    private int _connectionType = LineInputDeviceConnectionType.Unknown;
    private int _udpReceivePort = 0;
    private String _udpSendHostname = "";
    private int _udpSendPort = 0;
    private String _tcpHostname = "";
    private int _tcpPort = 0;
    private boolean _useHttpLogin = false;
    private String _loginHostname = "";
    private int _loginPort = 0;
    private String _userName = "";
    private String _password = "";
    private String _comPort = "";
    private int _baudRate = 0;
    private int _dataBits = 0;
    private boolean _discardNull = false;
    private boolean _dtrEnable = false;
    private int _handshake = Handshake.None;
    private String _newLine = "";
    private int _parity = Parity.None;
    private byte _parityReplace = 0;
    private int _readBufferSize = 0;
    private TimeSpan _readTimeout;
    private int _receivedBytesThreshold = 0;
    private boolean _rtsEnable = false;
    private int _stopBits = StopBits.None;
    private int _writeBufferSize = 0;
    private TimeSpan _writeTimeout;
    private String _pairedComPort = "";

    @Override
    public int getObjectType( ) {
        return Kind.LineInputDeviceConfiguration;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new LineInputDeviceConfigurationObject( );
    }

    public long getRowVersion( ) {
        return _rowVersion;
    }
    public void setRowVersion( long value ) {
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getLineInputDevice( ) {
        return _lineInputDevice;
    }
    public void setLineInputDevice( Guid value ) {
        if( !Comparer.equalsGuid( _lineInputDevice, value ) ) {
            _lineInputDevice = value;
            onPropertyChanged( );
        }
    }

    public DateTime getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( DateTime value ) {
        if( !Comparer.equalsDateTime( _timestamp, value ) ) {
            _timestamp = value;
            onPropertyChanged( );
        }
    }

    public boolean getStoreReceivedSentences( ) {
        return _storeReceivedSentences;
    }
    public void setStoreReceivedSentences( boolean value ) {
        if( !Comparer.equalsBoolean( _storeReceivedSentences, value ) ) {
            _storeReceivedSentences = value;
            onPropertyChanged( );
        }
    }

    public boolean getStoreSentMessages( ) {
        return _storeSentMessages;
    }
    public void setStoreSentMessages( boolean value ) {
        if( !Comparer.equalsBoolean( _storeSentMessages, value ) ) {
            _storeSentMessages = value;
            onPropertyChanged( );
        }
    }

    public boolean getStoreUnsentMessages( ) {
        return _storeUnsentMessages;
    }
    public void setStoreUnsentMessages( boolean value ) {
        if( !Comparer.equalsBoolean( _storeUnsentMessages, value ) ) {
            _storeUnsentMessages = value;
            onPropertyChanged( );
        }
    }

    public boolean getNMEA( ) {
        return _nMEA;
    }
    public void setNMEA( boolean value ) {
        if( !Comparer.equalsBoolean( _nMEA, value ) ) {
            _nMEA = value;
            onPropertyChanged( );
        }
    }

    public boolean getStrictNMEA( ) {
        return _strictNMEA;
    }
    public void setStrictNMEA( boolean value ) {
        if( !Comparer.equalsBoolean( _strictNMEA, value ) ) {
            _strictNMEA = value;
            onPropertyChanged( );
        }
    }

    public int getConnectionType( ) {
        return _connectionType;
    }
    public void setConnectionType( int value ) {
        if( !Comparer.equalsInt32( _connectionType, value ) ) {
            _connectionType = value;
            onPropertyChanged( );
        }
    }

    public int getUdpReceivePort( ) {
        return _udpReceivePort;
    }
    public void setUdpReceivePort( int value ) {
        if( !Comparer.equalsInt32( _udpReceivePort, value ) ) {
            _udpReceivePort = value;
            onPropertyChanged( );
        }
    }

    public String getUdpSendHostname( ) {
        return _udpSendHostname;
    }
    public void setUdpSendHostname( String value ) {
        if( !Comparer.equalsString( _udpSendHostname, value ) ) {
            _udpSendHostname = value;
            onPropertyChanged( );
        }
    }

    public int getUdpSendPort( ) {
        return _udpSendPort;
    }
    public void setUdpSendPort( int value ) {
        if( !Comparer.equalsInt32( _udpSendPort, value ) ) {
            _udpSendPort = value;
            onPropertyChanged( );
        }
    }

    public String getTcpHostname( ) {
        return _tcpHostname;
    }
    public void setTcpHostname( String value ) {
        if( !Comparer.equalsString( _tcpHostname, value ) ) {
            _tcpHostname = value;
            onPropertyChanged( );
        }
    }

    public int getTcpPort( ) {
        return _tcpPort;
    }
    public void setTcpPort( int value ) {
        if( !Comparer.equalsInt32( _tcpPort, value ) ) {
            _tcpPort = value;
            onPropertyChanged( );
        }
    }

    public boolean getUseHttpLogin( ) {
        return _useHttpLogin;
    }
    public void setUseHttpLogin( boolean value ) {
        if( !Comparer.equalsBoolean( _useHttpLogin, value ) ) {
            _useHttpLogin = value;
            onPropertyChanged( );
        }
    }

    public String getLoginHostname( ) {
        return _loginHostname;
    }
    public void setLoginHostname( String value ) {
        if( !Comparer.equalsString( _loginHostname, value ) ) {
            _loginHostname = value;
            onPropertyChanged( );
        }
    }

    public int getLoginPort( ) {
        return _loginPort;
    }
    public void setLoginPort( int value ) {
        if( !Comparer.equalsInt32( _loginPort, value ) ) {
            _loginPort = value;
            onPropertyChanged( );
        }
    }

    public String getUserName( ) {
        return _userName;
    }
    public void setUserName( String value ) {
        if( !Comparer.equalsString( _userName, value ) ) {
            _userName = value;
            onPropertyChanged( );
        }
    }

    public String getPassword( ) {
        return _password;
    }
    public void setPassword( String value ) {
        if( !Comparer.equalsString( _password, value ) ) {
            _password = value;
            onPropertyChanged( );
        }
    }

    public String getComPort( ) {
        return _comPort;
    }
    public void setComPort( String value ) {
        if( !Comparer.equalsString( _comPort, value ) ) {
            _comPort = value;
            onPropertyChanged( );
        }
    }

    public int getBaudRate( ) {
        return _baudRate;
    }
    public void setBaudRate( int value ) {
        if( !Comparer.equalsInt32( _baudRate, value ) ) {
            _baudRate = value;
            onPropertyChanged( );
        }
    }

    public int getDataBits( ) {
        return _dataBits;
    }
    public void setDataBits( int value ) {
        if( !Comparer.equalsInt32( _dataBits, value ) ) {
            _dataBits = value;
            onPropertyChanged( );
        }
    }

    public boolean getDiscardNull( ) {
        return _discardNull;
    }
    public void setDiscardNull( boolean value ) {
        if( !Comparer.equalsBoolean( _discardNull, value ) ) {
            _discardNull = value;
            onPropertyChanged( );
        }
    }

    public boolean getDtrEnable( ) {
        return _dtrEnable;
    }
    public void setDtrEnable( boolean value ) {
        if( !Comparer.equalsBoolean( _dtrEnable, value ) ) {
            _dtrEnable = value;
            onPropertyChanged( );
        }
    }

    public int getHandshake( ) {
        return _handshake;
    }
    public void setHandshake( int value ) {
        if( !Comparer.equalsInt32( _handshake, value ) ) {
            _handshake = value;
            onPropertyChanged( );
        }
    }

    public String getNewLine( ) {
        return _newLine;
    }
    public void setNewLine( String value ) {
        if( !Comparer.equalsString( _newLine, value ) ) {
            _newLine = value;
            onPropertyChanged( );
        }
    }

    public int getParity( ) {
        return _parity;
    }
    public void setParity( int value ) {
        if( !Comparer.equalsInt32( _parity, value ) ) {
            _parity = value;
            onPropertyChanged( );
        }
    }

    public byte getParityReplace( ) {
        return _parityReplace;
    }
    public void setParityReplace( byte value ) {
        if( !Comparer.equalsUInt8( _parityReplace, value ) ) {
            _parityReplace = value;
            onPropertyChanged( );
        }
    }

    public int getReadBufferSize( ) {
        return _readBufferSize;
    }
    public void setReadBufferSize( int value ) {
        if( !Comparer.equalsInt32( _readBufferSize, value ) ) {
            _readBufferSize = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getReadTimeout( ) {
        return _readTimeout;
    }
    public void setReadTimeout( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _readTimeout, value ) ) {
            _readTimeout = value;
            onPropertyChanged( );
        }
    }

    public int getReceivedBytesThreshold( ) {
        return _receivedBytesThreshold;
    }
    public void setReceivedBytesThreshold( int value ) {
        if( !Comparer.equalsInt32( _receivedBytesThreshold, value ) ) {
            _receivedBytesThreshold = value;
            onPropertyChanged( );
        }
    }

    public boolean getRtsEnable( ) {
        return _rtsEnable;
    }
    public void setRtsEnable( boolean value ) {
        if( !Comparer.equalsBoolean( _rtsEnable, value ) ) {
            _rtsEnable = value;
            onPropertyChanged( );
        }
    }

    public int getStopBits( ) {
        return _stopBits;
    }
    public void setStopBits( int value ) {
        if( !Comparer.equalsInt32( _stopBits, value ) ) {
            _stopBits = value;
            onPropertyChanged( );
        }
    }

    public int getWriteBufferSize( ) {
        return _writeBufferSize;
    }
    public void setWriteBufferSize( int value ) {
        if( !Comparer.equalsInt32( _writeBufferSize, value ) ) {
            _writeBufferSize = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getWriteTimeout( ) {
        return _writeTimeout;
    }
    public void setWriteTimeout( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _writeTimeout, value ) ) {
            _writeTimeout = value;
            onPropertyChanged( );
        }
    }

    public String getPairedComPort( ) {
        return _pairedComPort;
    }
    public void setPairedComPort( String value ) {
        if( !Comparer.equalsString( _pairedComPort, value ) ) {
            _pairedComPort = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( LineInputDeviceConfigurationObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._lineInputDevice = this._lineInputDevice;
        targetObject._timestamp = this._timestamp;
        targetObject._storeReceivedSentences = this._storeReceivedSentences;
        targetObject._storeSentMessages = this._storeSentMessages;
        targetObject._storeUnsentMessages = this._storeUnsentMessages;
        targetObject._nMEA = this._nMEA;
        targetObject._strictNMEA = this._strictNMEA;
        targetObject._connectionType = this._connectionType;
        targetObject._udpReceivePort = this._udpReceivePort;
        targetObject._udpSendHostname = this._udpSendHostname;
        targetObject._udpSendPort = this._udpSendPort;
        targetObject._tcpHostname = this._tcpHostname;
        targetObject._tcpPort = this._tcpPort;
        targetObject._useHttpLogin = this._useHttpLogin;
        targetObject._loginHostname = this._loginHostname;
        targetObject._loginPort = this._loginPort;
        targetObject._userName = this._userName;
        targetObject._password = this._password;
        targetObject._comPort = this._comPort;
        targetObject._baudRate = this._baudRate;
        targetObject._dataBits = this._dataBits;
        targetObject._discardNull = this._discardNull;
        targetObject._dtrEnable = this._dtrEnable;
        targetObject._handshake = this._handshake;
        targetObject._newLine = this._newLine;
        targetObject._parity = this._parity;
        targetObject._parityReplace = this._parityReplace;
        targetObject._readBufferSize = this._readBufferSize;
        targetObject._readTimeout = this._readTimeout;
        targetObject._receivedBytesThreshold = this._receivedBytesThreshold;
        targetObject._rtsEnable = this._rtsEnable;
        targetObject._stopBits = this._stopBits;
        targetObject._writeBufferSize = this._writeBufferSize;
        targetObject._writeTimeout = this._writeTimeout;
        targetObject._pairedComPort = this._pairedComPort;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (LineInputDeviceConfigurationObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._lineInputDevice, other._lineInputDevice ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._storeReceivedSentences, other._storeReceivedSentences ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._storeSentMessages, other._storeSentMessages ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._storeUnsentMessages, other._storeUnsentMessages ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._nMEA, other._nMEA ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._strictNMEA, other._strictNMEA ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._connectionType, other._connectionType ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._udpReceivePort, other._udpReceivePort ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._udpSendHostname, other._udpSendHostname ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._udpSendPort, other._udpSendPort ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._tcpHostname, other._tcpHostname ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._tcpPort, other._tcpPort ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._useHttpLogin, other._useHttpLogin ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._loginHostname, other._loginHostname ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._loginPort, other._loginPort ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._userName, other._userName ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._password, other._password ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._comPort, other._comPort ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._baudRate, other._baudRate ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._dataBits, other._dataBits ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._discardNull, other._discardNull ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._dtrEnable, other._dtrEnable ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._handshake, other._handshake ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._newLine, other._newLine ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._parity, other._parity ) ) {
            return false;
        }
        if( !Comparer.equalsUInt8( this._parityReplace, other._parityReplace ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._readBufferSize, other._readBufferSize ) ) {
            return false;
        }
        if( !Comparer.equalsTimeSpan( this._readTimeout, other._readTimeout ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._receivedBytesThreshold, other._receivedBytesThreshold ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._rtsEnable, other._rtsEnable ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._stopBits, other._stopBits ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._writeBufferSize, other._writeBufferSize ) ) {
            return false;
        }
        if( !Comparer.equalsTimeSpan( this._writeTimeout, other._writeTimeout ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._pairedComPort, other._pairedComPort ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _lineInputDevice );
        destination.writeDateTime( _timestamp );
        destination.writeBoolean( _storeReceivedSentences );
        destination.writeBoolean( _storeSentMessages );
        destination.writeBoolean( _storeUnsentMessages );
        destination.writeBoolean( _nMEA );
        destination.writeBoolean( _strictNMEA );
        destination.writeInt32( _connectionType );
        destination.writeInt32( _udpReceivePort );
        destination.writeStringUtf8( _udpSendHostname );
        destination.writeInt32( _udpSendPort );
        destination.writeStringUtf8( _tcpHostname );
        destination.writeInt32( _tcpPort );
        destination.writeBoolean( _useHttpLogin );
        destination.writeStringUtf8( _loginHostname );
        destination.writeInt32( _loginPort );
        destination.writeStringUtf8( _userName );
        destination.writeStringUtf8( _password );
        destination.writeStringUtf8( _comPort );
        destination.writeInt32( _baudRate );
        destination.writeInt32( _dataBits );
        destination.writeBoolean( _discardNull );
        destination.writeBoolean( _dtrEnable );
        destination.writeInt32( _handshake );
        destination.writeStringUtf8( _newLine );
        destination.writeInt32( _parity );
        destination.writeUInt8( _parityReplace );
        destination.writeInt32( _readBufferSize );
        destination.writeTimeSpan( _readTimeout );
        destination.writeInt32( _receivedBytesThreshold );
        destination.writeBoolean( _rtsEnable );
        destination.writeInt32( _stopBits );
        destination.writeInt32( _writeBufferSize );
        destination.writeTimeSpan( _writeTimeout );
        destination.writeStringUtf8( _pairedComPort );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _lineInputDevice = source.readGuid( );
        _timestamp = source.readDateTime( );
        _storeReceivedSentences = source.readBoolean( );
        _storeSentMessages = source.readBoolean( );
        _storeUnsentMessages = source.readBoolean( );
        _nMEA = source.readBoolean( );
        _strictNMEA = source.readBoolean( );
        _connectionType = source.readInt32( );
        _udpReceivePort = source.readInt32( );
        _udpSendHostname = source.readString( );
        _udpSendPort = source.readInt32( );
        _tcpHostname = source.readString( );
        _tcpPort = source.readInt32( );
        _useHttpLogin = source.readBoolean( );
        _loginHostname = source.readString( );
        _loginPort = source.readInt32( );
        _userName = source.readString( );
        _password = source.readString( );
        _comPort = source.readString( );
        _baudRate = source.readInt32( );
        _dataBits = source.readInt32( );
        _discardNull = source.readBoolean( );
        _dtrEnable = source.readBoolean( );
        _handshake = source.readInt32( );
        _newLine = source.readString( );
        _parity = source.readInt32( );
        _parityReplace = source.readUInt8( );
        _readBufferSize = source.readInt32( );
        _readTimeout = source.readTimeSpan( );
        _receivedBytesThreshold = source.readInt32( );
        _rtsEnable = source.readBoolean( );
        _stopBits = source.readInt32( );
        _writeBufferSize = source.readInt32( );
        _writeTimeout = source.readTimeSpan( );
        _pairedComPort = source.readString( );
    }

}
