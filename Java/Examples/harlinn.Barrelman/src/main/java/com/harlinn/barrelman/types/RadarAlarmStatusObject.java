package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadarAlarmStatusObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.RadarAlarmStatus;

    private long _rowVersion = 0;
    private Guid _radar;
    private DateTime _timestamp;
    private int _type = AlarmState.Unknown;

    public RadarAlarmStatusObject( ) {
    }
    public RadarAlarmStatusObject( byte objectState, Guid id, long rowVersion, Guid radar, DateTime timestamp, int type ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._radar = radar;
        this._timestamp = timestamp;
        this._type = type;
    }

    @Override
    public int getObjectType( ) {
        return Kind.RadarAlarmStatus;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadarAlarmStatusObject( );
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

    public Guid getRadar( ) {
        return _radar;
    }
    public void setRadar( Guid value ) {
        if( !Comparer.equalsGuid( _radar, value ) ) {
            _radar = value;
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

    public int getType( ) {
        return _type;
    }
    public void setType( int value ) {
        if( !Comparer.equalsInt32( _type, value ) ) {
            _type = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( RadarAlarmStatusObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._radar = this._radar;
        targetObject._timestamp = this._timestamp;
        targetObject._type = this._type;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (RadarAlarmStatusObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._radar, other._radar ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._type, other._type ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _radar );
        destination.writeDateTime( _timestamp );
        destination.writeInt32( _type );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _radar = source.readGuid( );
        _timestamp = source.readDateTime( );
        _type = source.readInt32( );
    }

}
