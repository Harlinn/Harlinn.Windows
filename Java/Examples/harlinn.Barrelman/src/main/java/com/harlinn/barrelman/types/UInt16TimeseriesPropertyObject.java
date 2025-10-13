package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class UInt16TimeseriesPropertyObject extends TimeseriesPropertyObject {

    private Guid _timeseries;

    @Override
    public int getObjectType( ) {
        return Kind.UInt16TimeseriesProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new UInt16TimeseriesPropertyObject( );
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
