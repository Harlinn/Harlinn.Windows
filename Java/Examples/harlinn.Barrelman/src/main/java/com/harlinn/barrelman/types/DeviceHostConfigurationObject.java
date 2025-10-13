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
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getHost( ) {
        return _host;
    }
    public void setHost( Guid value ) {
        if( _host != value ) {
            this._host = value;
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

    public String getHostname( ) {
        return _hostname;
    }
    public void setHostname( String value ) {
        if( _hostname != value ) {
            this._hostname = value;
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

    public String getQueueName( ) {
        return _queueName;
    }
    public void setQueueName( String value ) {
        if( _queueName != value ) {
            this._queueName = value;
            onPropertyChanged( );
        }
    }


}
