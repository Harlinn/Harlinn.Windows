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

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisDeviceConfigurationObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.AisDeviceConfiguration;

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

    public AisDeviceConfigurationObject( ) {
    }
    public AisDeviceConfigurationObject( byte objectState, Guid id, long rowVersion, Guid aisDevice, DateTime timestamp, boolean filter, double northWestLatitude, double northWestLongitude, double southEastLatitude, double southEastLongitude, String comPort, int baudRate, String iPAddress, int port, int udpPort, boolean authenticate, String userName, String password, String authenticationURL, int connectionType, int sourceUpdateRate, String configurationURL, boolean storeReceivedSentences ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._aisDevice = aisDevice;
        this._timestamp = timestamp;
        this._filter = filter;
        this._northWestLatitude = northWestLatitude;
        this._northWestLongitude = northWestLongitude;
        this._southEastLatitude = southEastLatitude;
        this._southEastLongitude = southEastLongitude;
        this._comPort = comPort;
        this._baudRate = baudRate;
        this._iPAddress = iPAddress;
        this._port = port;
        this._udpPort = udpPort;
        this._authenticate = authenticate;
        this._userName = userName;
        this._password = password;
        this._authenticationURL = authenticationURL;
        this._connectionType = connectionType;
        this._sourceUpdateRate = sourceUpdateRate;
        this._configurationURL = configurationURL;
        this._storeReceivedSentences = storeReceivedSentences;
    }

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
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getAisDevice( ) {
        return _aisDevice;
    }
    public void setAisDevice( Guid value ) {
        if( !Comparer.equalsGuid( _aisDevice, value ) ) {
            _aisDevice = value;
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

    public boolean getFilter( ) {
        return _filter;
    }
    public void setFilter( boolean value ) {
        if( !Comparer.equalsBoolean( _filter, value ) ) {
            _filter = value;
            onPropertyChanged( );
        }
    }

    public double getNorthWestLatitude( ) {
        return _northWestLatitude;
    }
    public void setNorthWestLatitude( double value ) {
        if( !Comparer.equalsDouble( _northWestLatitude, value ) ) {
            _northWestLatitude = value;
            onPropertyChanged( );
        }
    }

    public double getNorthWestLongitude( ) {
        return _northWestLongitude;
    }
    public void setNorthWestLongitude( double value ) {
        if( !Comparer.equalsDouble( _northWestLongitude, value ) ) {
            _northWestLongitude = value;
            onPropertyChanged( );
        }
    }

    public double getSouthEastLatitude( ) {
        return _southEastLatitude;
    }
    public void setSouthEastLatitude( double value ) {
        if( !Comparer.equalsDouble( _southEastLatitude, value ) ) {
            _southEastLatitude = value;
            onPropertyChanged( );
        }
    }

    public double getSouthEastLongitude( ) {
        return _southEastLongitude;
    }
    public void setSouthEastLongitude( double value ) {
        if( !Comparer.equalsDouble( _southEastLongitude, value ) ) {
            _southEastLongitude = value;
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

    public String getIPAddress( ) {
        return _iPAddress;
    }
    public void setIPAddress( String value ) {
        if( !Comparer.equalsString( _iPAddress, value ) ) {
            _iPAddress = value;
            onPropertyChanged( );
        }
    }

    public int getPort( ) {
        return _port;
    }
    public void setPort( int value ) {
        if( !Comparer.equalsInt32( _port, value ) ) {
            _port = value;
            onPropertyChanged( );
        }
    }

    public int getUdpPort( ) {
        return _udpPort;
    }
    public void setUdpPort( int value ) {
        if( !Comparer.equalsInt32( _udpPort, value ) ) {
            _udpPort = value;
            onPropertyChanged( );
        }
    }

    public boolean getAuthenticate( ) {
        return _authenticate;
    }
    public void setAuthenticate( boolean value ) {
        if( !Comparer.equalsBoolean( _authenticate, value ) ) {
            _authenticate = value;
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

    public String getAuthenticationURL( ) {
        return _authenticationURL;
    }
    public void setAuthenticationURL( String value ) {
        if( !Comparer.equalsString( _authenticationURL, value ) ) {
            _authenticationURL = value;
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

    public int getSourceUpdateRate( ) {
        return _sourceUpdateRate;
    }
    public void setSourceUpdateRate( int value ) {
        if( !Comparer.equalsInt32( _sourceUpdateRate, value ) ) {
            _sourceUpdateRate = value;
            onPropertyChanged( );
        }
    }

    public String getConfigurationURL( ) {
        return _configurationURL;
    }
    public void setConfigurationURL( String value ) {
        if( !Comparer.equalsString( _configurationURL, value ) ) {
            _configurationURL = value;
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



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( AisDeviceConfigurationObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._aisDevice = this._aisDevice;
        targetObject._timestamp = this._timestamp;
        targetObject._filter = this._filter;
        targetObject._northWestLatitude = this._northWestLatitude;
        targetObject._northWestLongitude = this._northWestLongitude;
        targetObject._southEastLatitude = this._southEastLatitude;
        targetObject._southEastLongitude = this._southEastLongitude;
        targetObject._comPort = this._comPort;
        targetObject._baudRate = this._baudRate;
        targetObject._iPAddress = this._iPAddress;
        targetObject._port = this._port;
        targetObject._udpPort = this._udpPort;
        targetObject._authenticate = this._authenticate;
        targetObject._userName = this._userName;
        targetObject._password = this._password;
        targetObject._authenticationURL = this._authenticationURL;
        targetObject._connectionType = this._connectionType;
        targetObject._sourceUpdateRate = this._sourceUpdateRate;
        targetObject._configurationURL = this._configurationURL;
        targetObject._storeReceivedSentences = this._storeReceivedSentences;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (AisDeviceConfigurationObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._aisDevice, other._aisDevice ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._filter, other._filter ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._northWestLatitude, other._northWestLatitude ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._northWestLongitude, other._northWestLongitude ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._southEastLatitude, other._southEastLatitude ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._southEastLongitude, other._southEastLongitude ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._comPort, other._comPort ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._baudRate, other._baudRate ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._iPAddress, other._iPAddress ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._port, other._port ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._udpPort, other._udpPort ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._authenticate, other._authenticate ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._userName, other._userName ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._password, other._password ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._authenticationURL, other._authenticationURL ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._connectionType, other._connectionType ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._sourceUpdateRate, other._sourceUpdateRate ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._configurationURL, other._configurationURL ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._storeReceivedSentences, other._storeReceivedSentences ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _aisDevice );
        destination.writeDateTime( _timestamp );
        destination.writeBoolean( _filter );
        destination.writeDouble( _northWestLatitude );
        destination.writeDouble( _northWestLongitude );
        destination.writeDouble( _southEastLatitude );
        destination.writeDouble( _southEastLongitude );
        destination.writeStringUtf8( _comPort );
        destination.writeInt32( _baudRate );
        destination.writeStringUtf8( _iPAddress );
        destination.writeInt32( _port );
        destination.writeInt32( _udpPort );
        destination.writeBoolean( _authenticate );
        destination.writeStringUtf8( _userName );
        destination.writeStringUtf8( _password );
        destination.writeStringUtf8( _authenticationURL );
        destination.writeInt32( _connectionType );
        destination.writeInt32( _sourceUpdateRate );
        destination.writeStringUtf8( _configurationURL );
        destination.writeBoolean( _storeReceivedSentences );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _aisDevice = source.readGuid( );
        _timestamp = source.readDateTime( );
        _filter = source.readBoolean( );
        _northWestLatitude = source.readDouble( );
        _northWestLongitude = source.readDouble( );
        _southEastLatitude = source.readDouble( );
        _southEastLongitude = source.readDouble( );
        _comPort = source.readString( );
        _baudRate = source.readInt32( );
        _iPAddress = source.readString( );
        _port = source.readInt32( );
        _udpPort = source.readInt32( );
        _authenticate = source.readBoolean( );
        _userName = source.readString( );
        _password = source.readString( );
        _authenticationURL = source.readString( );
        _connectionType = source.readInt32( );
        _sourceUpdateRate = source.readInt32( );
        _configurationURL = source.readString( );
        _storeReceivedSentences = source.readBoolean( );
    }

}
