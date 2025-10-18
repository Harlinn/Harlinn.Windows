package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class UInt32TimeseriesObject extends TimeseriesObject {

    public final int KIND = Kind.UInt32Timeseries;


    public UInt32TimeseriesObject( ) {
    }
    public UInt32TimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
    }

    @Override
    public int getObjectType( ) {
        return Kind.UInt32Timeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new UInt32TimeseriesObject( );
    }

}
