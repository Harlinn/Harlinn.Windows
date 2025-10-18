package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ZoneExceptionsObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.ZoneExceptions;

    private long _rowVersion = 0;
    private Guid _zone;
    private DateTime _timestamp;

    public ZoneExceptionsObject( ) {
    }
    public ZoneExceptionsObject( byte objectState, Guid id, long rowVersion, Guid zone, DateTime timestamp ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._zone = zone;
        this._timestamp = timestamp;
    }

    @Override
    public int getObjectType( ) {
        return Kind.ZoneExceptions;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ZoneExceptionsObject( );
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

    public Guid getZone( ) {
        return _zone;
    }
    public void setZone( Guid value ) {
        if( !Comparer.equalsGuid( _zone, value ) ) {
            _zone = value;
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



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( ZoneExceptionsObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._zone = this._zone;
        targetObject._timestamp = this._timestamp;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (ZoneExceptionsObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._zone, other._zone ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _zone );
        destination.writeDateTime( _timestamp );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _zone = source.readGuid( );
        _timestamp = source.readDateTime( );
    }

}
