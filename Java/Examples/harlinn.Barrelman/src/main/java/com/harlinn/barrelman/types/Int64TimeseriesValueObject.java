package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class Int64TimeseriesValueObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.Int64TimeseriesValue;

    private long _rowVersion = 0;
    private Guid _timeseries;
    private DateTime _timestamp;
    private Long _value;

    public Int64TimeseriesValueObject( ) {
    }
    public Int64TimeseriesValueObject( byte objectState, Guid id, long rowVersion, Guid timeseries, DateTime timestamp, Long value ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._timeseries = timeseries;
        this._timestamp = timestamp;
        this._value = value;
    }

    @Override
    public int getObjectType( ) {
        return Kind.Int64TimeseriesValue;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new Int64TimeseriesValueObject( );
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

    public Guid getTimeseries( ) {
        return _timeseries;
    }
    public void setTimeseries( Guid value ) {
        if( !Comparer.equalsGuid( _timeseries, value ) ) {
            _timeseries = value;
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

    public Long getValue( ) {
        return _value;
    }
    public void setValue( Long value ) {
        if( !Comparer.equalsNullableInt64( _value, value ) ) {
            _value = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( Int64TimeseriesValueObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._timeseries = this._timeseries;
        targetObject._timestamp = this._timestamp;
        targetObject._value = this._value;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (Int64TimeseriesValueObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._timeseries, other._timeseries ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsNullableInt64( this._value, other._value ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _timeseries );
        destination.writeDateTime( _timestamp );
        destination.writeNullableInt64( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _timeseries = source.readGuid( );
        _timestamp = source.readDateTime( );
        _value = source.readNullableInt64( );
    }

}
