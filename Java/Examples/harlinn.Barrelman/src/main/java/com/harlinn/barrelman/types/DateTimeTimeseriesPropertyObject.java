package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class DateTimeTimeseriesPropertyObject extends TimeseriesPropertyObject {

    public final int KIND = Kind.DateTimeTimeseriesProperty;

    private Guid _timeseries;

    public DateTimeTimeseriesPropertyObject( ) {
    }
    public DateTimeTimeseriesPropertyObject( byte objectState, Guid id, long rowVersion, Guid element, Guid definition, Guid timeseries ) {
        super( objectState, id, rowVersion, element, definition );
        this._timeseries = timeseries;
    }

    @Override
    public int getObjectType( ) {
        return Kind.DateTimeTimeseriesProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new DateTimeTimeseriesPropertyObject( );
    }

    public Guid getTimeseries( ) {
        return _timeseries;
    }
    public void setTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _timeseries, value ) ) {
            _timeseries = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( DateTimeTimeseriesPropertyObject )target;
        targetObject._timeseries = this._timeseries;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (DateTimeTimeseriesPropertyObject)obj;
        if( !Comparer.equalsNullableGuid( this._timeseries, other._timeseries ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _timeseries );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _timeseries = source.readNullableGuid( );
    }

}
