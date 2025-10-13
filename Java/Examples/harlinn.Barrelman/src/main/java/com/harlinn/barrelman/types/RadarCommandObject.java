package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadarCommandObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _radar;
    private DateTime _timestamp;
    private int _deviceCommandSourceType = DeviceCommandSourceType.Unknown;
    private Guid _deviceCommandSourceId;
    private Guid _reply;

    @Override
    public int getObjectType( ) {
        return Kind.RadarCommand;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadarCommandObject( );
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

    public Guid getRadar( ) {
        return _radar;
    }
    public void setRadar( Guid value ) {
        if( _radar != value ) {
            this._radar = value;
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

    public int getDeviceCommandSourceType( ) {
        return _deviceCommandSourceType;
    }
    public void setDeviceCommandSourceType( int value ) {
        if( _deviceCommandSourceType != value ) {
            this._deviceCommandSourceType = value;
            onPropertyChanged( );
        }
    }

    public Guid getDeviceCommandSourceId( ) {
        return _deviceCommandSourceId;
    }
    public void setDeviceCommandSourceId( Guid value ) {
        if( _deviceCommandSourceId != value ) {
            this._deviceCommandSourceId = value;
            onPropertyChanged( );
        }
    }

    public Guid getReply( ) {
        return _reply;
    }
    public void setReply( Guid value ) {
        if( _reply != value ) {
            this._reply = value;
            onPropertyChanged( );
        }
    }


}
