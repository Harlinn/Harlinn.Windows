package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GeoPosition3DTimeseriesObject extends TimeseriesObject {

    public final int KIND = Kind.GeoPosition3DTimeseries;


    public GeoPosition3DTimeseriesObject( ) {
    }
    public GeoPosition3DTimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
    }

    @Override
    public int getObjectType( ) {
        return Kind.GeoPosition3DTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new GeoPosition3DTimeseriesObject( );
    }

}
