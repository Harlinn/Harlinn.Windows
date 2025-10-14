package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class DeviceHostConfigurationObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _host;
    private DateTime _timestamp;
    private String _hostname = "";
    private int _port = 0;
    private String _queueName = "";

    @Override
    public int getObjectType( ) {
        return Kind.DeviceHostConfiguration;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new DeviceHostConfigurationObject( );
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

    public Guid getHost( ) {
        return _host;
    }
    public void setHost( Guid value ) {
        if( !Comparer.equalsGuid( _host, value ) ) {
            _host = value;
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

    public String getHostname( ) {
        return _hostname;
    }
    public void setHostname( String value ) {
        if( !Comparer.equalsString( _hostname, value ) ) {
            _hostname = value;
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

    public String getQueueName( ) {
        return _queueName;
    }
    public void setQueueName( String value ) {
        if( !Comparer.equalsString( _queueName, value ) ) {
            _queueName = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _host );
        destination.writeDateTime( _timestamp );
        destination.writeStringUtf8( _hostname );
        destination.writeInt32( _port );
        destination.writeStringUtf8( _queueName );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _host = source.readGuid( );
        _timestamp = source.readDateTime( );
        _hostname = source.readString( );
        _port = source.readInt32( );
        _queueName = source.readString( );
    }

}
