package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class UInt64TimeseriesPropertyObject extends TimeseriesPropertyObject {

    private Guid _timeseries;

    @Override
    public int getObjectType( ) {
        return Kind.UInt64TimeseriesProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new UInt64TimeseriesPropertyObject( );
    }

    public Guid getTimeseries( ) {
        return _timeseries;
    }
    public void setTimeseries( Guid value ) {
        if( _timeseries != value ) {
            this._timeseries = value;
            onPropertyChanged( );
        }
    }


}
