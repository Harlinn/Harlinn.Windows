package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class TimeSpanTimeseriesObject extends TimeseriesObject {

    public final int KIND = Kind.TimeSpanTimeseries;


    public TimeSpanTimeseriesObject( ) {
    }
    public TimeSpanTimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
    }

    @Override
    public int getObjectType( ) {
        return Kind.TimeSpanTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new TimeSpanTimeseriesObject( );
    }

}
