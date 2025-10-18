package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class UInt64TimeseriesObject extends TimeseriesObject {

    public final int KIND = Kind.UInt64Timeseries;


    public UInt64TimeseriesObject( ) {
    }
    public UInt64TimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
    }

    @Override
    public int getObjectType( ) {
        return Kind.UInt64Timeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new UInt64TimeseriesObject( );
    }

}
