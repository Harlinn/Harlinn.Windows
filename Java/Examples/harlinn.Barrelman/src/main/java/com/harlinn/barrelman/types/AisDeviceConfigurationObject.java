package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisDeviceConfigurationObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _aisDevice;
    private DateTime _timestamp;
    private boolean _filter = false;
    private double _northWestLatitude = 0.0;
    private double _northWestLongitude = 0.0;
    private double _southEastLatitude = 0.0;
    private double _southEastLongitude = 0.0;
    private String _comPort = "";
    private int _baudRate = 0;
    private String _iPAddress = "";
    private int _port = 0;
    private int _udpPort = 0;
    private boolean _authenticate = false;
    private String _userName = "";
    private String _password = "";
    private String _authenticationURL = "";
    private int _connectionType = AisDeviceConnectionType.Unknown;
    private int _sourceUpdateRate = 0;
    private String _configurationURL = "";
    private boolean _storeReceivedSentences = false;

    @Override
    public int getObjectType( ) {
        return Kind.AisDeviceConfiguration;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisDeviceConfigurationObject( );
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

    public Guid getAisDevice( ) {
        return _aisDevice;
    }
    public void setAisDevice( Guid value ) {
        if( _aisDevice != value ) {
            this._aisDevice = value;
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

    public boolean getFilter( ) {
        return _filter;
    }
    public void setFilter( boolean value ) {
        if( _filter != value ) {
            this._filter = value;
            onPropertyChanged( );
        }
    }

    public double getNorthWestLatitude( ) {
        return _northWestLatitude;
    }
    public void setNorthWestLatitude( double value ) {
        if( _northWestLatitude != value ) {
            this._northWestLatitude = value;
            onPropertyChanged( );
        }
    }

    public double getNorthWestLongitude( ) {
        return _northWestLongitude;
    }
    public void setNorthWestLongitude( double value ) {
        if( _northWestLongitude != value ) {
            this._northWestLongitude = value;
            onPropertyChanged( );
        }
    }

    public double getSouthEastLatitude( ) {
        return _southEastLatitude;
    }
    public void setSouthEastLatitude( double value ) {
        if( _southEastLatitude != value ) {
            this._southEastLatitude = value;
            onPropertyChanged( );
        }
    }

    public double getSouthEastLongitude( ) {
        return _southEastLongitude;
    }
    public void setSouthEastLongitude( double value ) {
        if( _southEastLongitude != value ) {
            this._southEastLongitude = value;
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

    public String getIPAddress( ) {
        return _iPAddress;
    }
    public void setIPAddress( String value ) {
        if( _iPAddress != value ) {
            this._iPAddress = value;
            onPropertyChanged( );
        }
    }

    public int getPort( ) {
        return _port;
    }
    public void setPort( int value ) {
        if( _port != value ) {
            this._port = value;
            onPropertyChanged( );
        }
    }

    public int getUdpPort( ) {
        return _udpPort;
    }
    public void setUdpPort( int value ) {
        if( _udpPort != value ) {
            this._udpPort = value;
            onPropertyChanged( );
        }
    }

    public boolean getAuthenticate( ) {
        return _authenticate;
    }
    public void setAuthenticate( boolean value ) {
        if( _authenticate != value ) {
            this._authenticate = value;
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

    public String getAuthenticationURL( ) {
        return _authenticationURL;
    }
    public void setAuthenticationURL( String value ) {
        if( _authenticationURL != value ) {
            this._authenticationURL = value;
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

    public int getSourceUpdateRate( ) {
        return _sourceUpdateRate;
    }
    public void setSourceUpdateRate( int value ) {
        if( _sourceUpdateRate != value ) {
            this._sourceUpdateRate = value;
            onPropertyChanged( );
        }
    }

    public String getConfigurationURL( ) {
        return _configurationURL;
    }
    public void setConfigurationURL( String value ) {
        if( _configurationURL != value ) {
            this._configurationURL = value;
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


}
