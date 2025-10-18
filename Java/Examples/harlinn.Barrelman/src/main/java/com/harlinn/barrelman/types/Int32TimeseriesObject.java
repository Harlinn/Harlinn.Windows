package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class Int32TimeseriesObject extends TimeseriesObject {

    public final int KIND = Kind.Int32Timeseries;


    public Int32TimeseriesObject( ) {
    }
    public Int32TimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
    }

    @Override
    public int getObjectType( ) {
        return Kind.Int32Timeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new Int32TimeseriesObject( );
    }

}
