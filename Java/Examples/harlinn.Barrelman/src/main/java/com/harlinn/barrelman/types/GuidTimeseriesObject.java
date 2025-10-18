package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GuidTimeseriesObject extends TimeseriesObject {

    public final int KIND = Kind.GuidTimeseries;


    public GuidTimeseriesObject( ) {
    }
    public GuidTimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
    }

    @Override
    public int getObjectType( ) {
        return Kind.GuidTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new GuidTimeseriesObject( );
    }

}
