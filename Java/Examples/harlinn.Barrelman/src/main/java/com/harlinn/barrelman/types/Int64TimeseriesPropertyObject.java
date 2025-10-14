package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class Int64TimeseriesPropertyObject extends TimeseriesPropertyObject {

    private Guid _timeseries;

    @Override
    public int getObjectType( ) {
        return Kind.Int64TimeseriesProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new Int64TimeseriesPropertyObject( );
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
