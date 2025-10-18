package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class TimeseriesInfoObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.TimeseriesInfo;

    private long _rowVersion = 0;
    private DateTime _firstTimestamp;
    private DateTime _lastTimestamp;
    private long _count = 0;

    public TimeseriesInfoObject( ) {
    }
    public TimeseriesInfoObject( byte objectState, Guid id, long rowVersion, DateTime firstTimestamp, DateTime lastTimestamp, long count ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._firstTimestamp = firstTimestamp;
        this._lastTimestamp = lastTimestamp;
        this._count = count;
    }

    @Override
    public int getObjectType( ) {
        return Kind.TimeseriesInfo;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new TimeseriesInfoObject( );
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

    public DateTime getFirstTimestamp( ) {
        return _firstTimestamp;
    }
    public void setFirstTimestamp( DateTime value ) {
        if( !Comparer.equalsNullableDateTime( _firstTimestamp, value ) ) {
            _firstTimestamp = value;
            onPropertyChanged( );
        }
    }

    public DateTime getLastTimestamp( ) {
        return _lastTimestamp;
    }
    public void setLastTimestamp( DateTime value ) {
        if( !Comparer.equalsNullableDateTime( _lastTimestamp, value ) ) {
            _lastTimestamp = value;
            onPropertyChanged( );
        }
    }

    public long getCount( ) {
        return _count;
    }
    public void setCount( long value ) {
        if( !Comparer.equalsInt64( _count, value ) ) {
            _count = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( TimeseriesInfoObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._firstTimestamp = this._firstTimestamp;
        targetObject._lastTimestamp = this._lastTimestamp;
        targetObject._count = this._count;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (TimeseriesInfoObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDateTime( this._firstTimestamp, other._firstTimestamp ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDateTime( this._lastTimestamp, other._lastTimestamp ) ) {
            return false;
        }
        if( !Comparer.equalsInt64( this._count, other._count ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeNullableDateTime( _firstTimestamp );
        destination.writeNullableDateTime( _lastTimestamp );
        destination.writeInt64( _count );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _firstTimestamp = source.readNullableDateTime( );
        _lastTimestamp = source.readNullableDateTime( );
        _count = source.readInt64( );
    }

}
