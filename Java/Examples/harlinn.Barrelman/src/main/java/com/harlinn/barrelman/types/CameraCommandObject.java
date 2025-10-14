package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraCommandObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _camera;
    private DateTime _timestamp;
    private int _deviceCommandSourceType = DeviceCommandSourceType.Unknown;
    private Guid _deviceCommandSourceId;
    private Guid _reply;

    @Override
    public int getObjectType( ) {
        return Kind.CameraCommand;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraCommandObject( );
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

    public Guid getCamera( ) {
        return _camera;
    }
    public void setCamera( Guid value ) {
        if( !Comparer.equalsGuid( _camera, value ) ) {
            _camera = value;
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

    public int getDeviceCommandSourceType( ) {
        return _deviceCommandSourceType;
    }
    public void setDeviceCommandSourceType( int value ) {
        if( !Comparer.equalsInt32( _deviceCommandSourceType, value ) ) {
            _deviceCommandSourceType = value;
            onPropertyChanged( );
        }
    }

    public Guid getDeviceCommandSourceId( ) {
        return _deviceCommandSourceId;
    }
    public void setDeviceCommandSourceId( Guid value ) {
        if( !Comparer.equalsGuid( _deviceCommandSourceId, value ) ) {
            _deviceCommandSourceId = value;
            onPropertyChanged( );
        }
    }

    public Guid getReply( ) {
        return _reply;
    }
    public void setReply( Guid value ) {
        if( !Comparer.equalsNullableGuid( _reply, value ) ) {
            _reply = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _camera );
        destination.writeDateTime( _timestamp );
        destination.writeInt32( _deviceCommandSourceType );
        destination.writeGuid( _deviceCommandSourceId );
        destination.writeNullableGuid( _reply );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _camera = source.readGuid( );
        _timestamp = source.readDateTime( );
        _deviceCommandSourceType = source.readInt32( );
        _deviceCommandSourceId = source.readGuid( );
        _reply = source.readNullableGuid( );
    }

}
