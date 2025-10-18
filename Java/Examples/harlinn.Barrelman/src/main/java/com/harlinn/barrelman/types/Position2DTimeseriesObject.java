package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class Position2DTimeseriesObject extends TimeseriesObject {

    public final int KIND = Kind.Position2DTimeseries;


    public Position2DTimeseriesObject( ) {
    }
    public Position2DTimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
    }

    @Override
    public int getObjectType( ) {
        return Kind.Position2DTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new Position2DTimeseriesObject( );
    }

}
