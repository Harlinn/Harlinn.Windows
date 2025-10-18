package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class OilSpillDetectorCommandObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.OilSpillDetectorCommand;

    private long _rowVersion = 0;
    private Guid _oilSpillDetector;
    private DateTime _timestamp;
    private int _deviceCommandSourceType = DeviceCommandSourceType.Unknown;
    private Guid _deviceCommandSourceId;
    private Guid _reply;

    public OilSpillDetectorCommandObject( ) {
    }
    public OilSpillDetectorCommandObject( byte objectState, Guid id, long rowVersion, Guid oilSpillDetector, DateTime timestamp, int deviceCommandSourceType, Guid deviceCommandSourceId, Guid reply ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._oilSpillDetector = oilSpillDetector;
        this._timestamp = timestamp;
        this._deviceCommandSourceType = deviceCommandSourceType;
        this._deviceCommandSourceId = deviceCommandSourceId;
        this._reply = reply;
    }

    @Override
    public int getObjectType( ) {
        return Kind.OilSpillDetectorCommand;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new OilSpillDetectorCommandObject( );
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

    public Guid getOilSpillDetector( ) {
        return _oilSpillDetector;
    }
    public void setOilSpillDetector( Guid value ) {
        if( !Comparer.equalsGuid( _oilSpillDetector, value ) ) {
            _oilSpillDetector = value;
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
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( OilSpillDetectorCommandObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._oilSpillDetector = this._oilSpillDetector;
        targetObject._timestamp = this._timestamp;
        targetObject._deviceCommandSourceType = this._deviceCommandSourceType;
        targetObject._deviceCommandSourceId = this._deviceCommandSourceId;
        targetObject._reply = this._reply;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (OilSpillDetectorCommandObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._oilSpillDetector, other._oilSpillDetector ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._deviceCommandSourceType, other._deviceCommandSourceType ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._deviceCommandSourceId, other._deviceCommandSourceId ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._reply, other._reply ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _oilSpillDetector );
        destination.writeDateTime( _timestamp );
        destination.writeInt32( _deviceCommandSourceType );
        destination.writeGuid( _deviceCommandSourceId );
        destination.writeNullableGuid( _reply );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _oilSpillDetector = source.readGuid( );
        _timestamp = source.readDateTime( );
        _deviceCommandSourceType = source.readInt32( );
        _deviceCommandSourceId = source.readGuid( );
        _reply = source.readNullableGuid( );
    }

}
