package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class BinaryTimeseriesObject extends TimeseriesObject {

    public final int KIND = Kind.BinaryTimeseries;


    public BinaryTimeseriesObject( ) {
    }
    public BinaryTimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
    }

    @Override
    public int getObjectType( ) {
        return Kind.BinaryTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new BinaryTimeseriesObject( );
    }

}
