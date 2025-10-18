package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class Int16TimeseriesObject extends TimeseriesObject {

    public final int KIND = Kind.Int16Timeseries;


    public Int16TimeseriesObject( ) {
    }
    public Int16TimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
    }

    @Override
    public int getObjectType( ) {
        return Kind.Int16Timeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new Int16TimeseriesObject( );
    }

}
