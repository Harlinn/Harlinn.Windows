package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class BinaryTimeseriesPropertyObject extends TimeseriesPropertyObject {

    private Guid _timeseries;

    @Override
    public int getObjectType( ) {
        return Kind.BinaryTimeseriesProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new BinaryTimeseriesPropertyObject( );
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
