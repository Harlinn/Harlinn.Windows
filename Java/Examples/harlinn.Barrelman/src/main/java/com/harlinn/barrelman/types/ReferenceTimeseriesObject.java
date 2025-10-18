package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ReferenceTimeseriesObject extends TimeseriesObject {

    public final int KIND = Kind.ReferenceTimeseries;


    public ReferenceTimeseriesObject( ) {
    }
    public ReferenceTimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
    }

    @Override
    public int getObjectType( ) {
        return Kind.ReferenceTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ReferenceTimeseriesObject( );
    }

}
