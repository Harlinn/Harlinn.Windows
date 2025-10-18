package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GeoPosition2DTimeseriesObject extends TimeseriesObject {

    public final int KIND = Kind.GeoPosition2DTimeseries;


    public GeoPosition2DTimeseriesObject( ) {
    }
    public GeoPosition2DTimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
    }

    @Override
    public int getObjectType( ) {
        return Kind.GeoPosition2DTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new GeoPosition2DTimeseriesObject( );
    }

}
