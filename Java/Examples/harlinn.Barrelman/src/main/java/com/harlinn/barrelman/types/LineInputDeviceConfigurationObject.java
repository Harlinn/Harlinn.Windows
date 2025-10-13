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
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getLineInputDevice( ) {
        return _lineInputDevice;
    }
    public void setLineInputDevice( Guid value ) {
        if( _lineInputDevice != value ) {
            this._lineInputDevice = value;
            onPropertyChanged( );
        }
    }

    public DateTime getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( DateTime value ) {
        if( _timestamp != value ) {
            this._timestamp = value;
            onPropertyChanged( );
        }
    }

    public boolean getStoreReceivedSentences( ) {
        return _storeReceivedSentences;
    }
    public void setStoreReceivedSentences( boolean value ) {
        if( _storeReceivedSentences != value ) {
            this._storeReceivedSentences = value;
            onPropertyChanged( );
        }
    }

    public boolean getStoreSentMessages( ) {
        return _storeSentMessages;
    }
    public void setStoreSentMessages( boolean value ) {
        if( _storeSentMessages != value ) {
            this._storeSentMessages = value;
            onPropertyChanged( );
        }
    }

    public boolean getStoreUnsentMessages( ) {
        return _storeUnsentMessages;
    }
    public void setStoreUnsentMessages( boolean value ) {
        if( _storeUnsentMessages != value ) {
            this._storeUnsentMessages = value;
            onPropertyChanged( );
        }
    }

    public boolean getNMEA( ) {
        return _nMEA;
    }
    public void setNMEA( boolean value ) {
        if( _nMEA != value ) {
            this._nMEA = value;
            onPropertyChanged( );
        }
    }

    public boolean getStrictNMEA( ) {
        return _strictNMEA;
    }
    public void setStrictNMEA( boolean value ) {
        if( _strictNMEA != value ) {
            this._strictNMEA = value;
            onPropertyChanged( );
        }
    }

    public int getConnectionType( ) {
        return _connectionType;
    }
    public void setConnectionType( int value ) {
        if( _connectionType != value ) {
            this._connectionType = value;
            onPropertyChanged( );
        }
    }

    public int getUdpReceivePort( ) {
        return _udpReceivePort;
    }
    public void setUdpReceivePort( int value ) {
        if( _udpReceivePort != value ) {
            this._udpReceivePort = value;
            onPropertyChanged( );
        }
    }

    public String getUdpSendHostname( ) {
        return _udpSendHostname;
    }
    public void setUdpSendHostname( String value ) {
        if( _udpSendHostname != value ) {
            this._udpSendHostname = value;
            onPropertyChanged( );
        }
    }

    public int getUdpSendPort( ) {
        return _udpSendPort;
    }
    public void setUdpSendPort( int value ) {
        if( _udpSendPort != value ) {
            this._udpSendPort = value;
            onPropertyChanged( );
        }
    }

    public String getTcpHostname( ) {
        return _tcpHostname;
    }
    public void setTcpHostname( String value ) {
        if( _tcpHostname != value ) {
            this._tcpHostname = value;
            onPropertyChanged( );
        }
    }

    public int getTcpPort( ) {
        return _tcpPort;
    }
    public void setTcpPort( int value ) {
        if( _tcpPort != value ) {
            this._tcpPort = value;
            onPropertyChanged( );
        }
    }

    public boolean getUseHttpLogin( ) {
        return _useHttpLogin;
    }
    public void setUseHttpLogin( boolean value ) {
        if( _useHttpLogin != value ) {
            this._useHttpLogin = value;
            onPropertyChanged( );
        }
    }

    public String getLoginHostname( ) {
        return _loginHostname;
    }
    public void setLoginHostname( String value ) {
        if( _loginHostname != value ) {
            this._loginHostname = value;
            onPropertyChanged( );
        }
    }

    public int getLoginPort( ) {
        return _loginPort;
    }
    public void setLoginPort( int value ) {
        if( _loginPort != value ) {
            this._loginPort = value;
            onPropertyChanged( );
        }
    }

    public String getUserName( ) {
        return _userName;
    }
    public void setUserName( String value ) {
        if( _userName != value ) {
            this._userName = value;
            onPropertyChanged( );
        }
    }

    public String getPassword( ) {
        return _password;
    }
    public void setPassword( String value ) {
        if( _password != value ) {
            this._password = value;
            onPropertyChanged( );
        }
    }

    public String getComPort( ) {
        return _comPort;
    }
    public void setComPort( String value ) {
        if( _comPort != value ) {
            this._comPort = value;
            onPropertyChanged( );
        }
    }

    public int getBaudRate( ) {
        return _baudRate;
    }
    public void setBaudRate( int value ) {
        if( _baudRate != value ) {
            this._baudRate = value;
            onPropertyChanged( );
        }
    }

    public int getDataBits( ) {
        return _dataBits;
    }
    public void setDataBits( int value ) {
        if( _dataBits != value ) {
            this._dataBits = value;
            onPropertyChanged( );
        }
    }

    public boolean getDiscardNull( ) {
        return _discardNull;
    }
    public void setDiscardNull( boolean value ) {
        if( _discardNull != value ) {
            this._discardNull = value;
            onPropertyChanged( );
        }
    }

    public boolean getDtrEnable( ) {
        return _dtrEnable;
    }
    public void setDtrEnable( boolean value ) {
        if( _dtrEnable != value ) {
            this._dtrEnable = value;
            onPropertyChanged( );
        }
    }

    public int getHandshake( ) {
        return _handshake;
    }
    public void setHandshake( int value ) {
        if( _handshake != value ) {
            this._handshake = value;
            onPropertyChanged( );
        }
    }

    public String getNewLine( ) {
        return _newLine;
    }
    public void setNewLine( String value ) {
        if( _newLine != value ) {
            this._newLine = value;
            onPropertyChanged( );
        }
    }

    public int getParity( ) {
        return _parity;
    }
    public void setParity( int value ) {
        if( _parity != value ) {
            this._parity = value;
            onPropertyChanged( );
        }
    }

    public byte getParityReplace( ) {
        return _parityReplace;
    }
    public void setParityReplace( byte value ) {
        if( _parityReplace != value ) {
            this._parityReplace = value;
            onPropertyChanged( );
        }
    }

    public int getReadBufferSize( ) {
        return _readBufferSize;
    }
    public void setReadBufferSize( int value ) {
        if( _readBufferSize != value ) {
            this._readBufferSize = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getReadTimeout( ) {
        return _readTimeout;
    }
    public void setReadTimeout( TimeSpan value ) {
        if( _readTimeout != value ) {
            this._readTimeout = value;
            onPropertyChanged( );
        }
    }

    public int getReceivedBytesThreshold( ) {
        return _receivedBytesThreshold;
    }
    public void setReceivedBytesThreshold( int value ) {
        if( _receivedBytesThreshold != value ) {
            this._receivedBytesThreshold = value;
            onPropertyChanged( );
        }
    }

    public boolean getRtsEnable( ) {
        return _rtsEnable;
    }
    public void setRtsEnable( boolean value ) {
        if( _rtsEnable != value ) {
            this._rtsEnable = value;
            onPropertyChanged( );
        }
    }

    public int getStopBits( ) {
        return _stopBits;
    }
    public void setStopBits( int value ) {
        if( _stopBits != value ) {
            this._stopBits = value;
            onPropertyChanged( );
        }
    }

    public int getWriteBufferSize( ) {
        return _writeBufferSize;
    }
    public void setWriteBufferSize( int value ) {
        if( _writeBufferSize != value ) {
            this._writeBufferSize = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getWriteTimeout( ) {
        return _writeTimeout;
    }
    public void setWriteTimeout( TimeSpan value ) {
        if( _writeTimeout != value ) {
            this._writeTimeout = value;
            onPropertyChanged( );
        }
    }

    public String getPairedComPort( ) {
        return _pairedComPort;
    }
    public void setPairedComPort( String value ) {
        if( _pairedComPort != value ) {
            this._pairedComPort = value;
            onPropertyChanged( );
        }
    }


}
