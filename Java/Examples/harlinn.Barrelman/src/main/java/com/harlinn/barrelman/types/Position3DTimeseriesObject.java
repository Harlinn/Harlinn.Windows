package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class Position3DTimeseriesObject extends TimeseriesObject {

    public final int KIND = Kind.Position3DTimeseries;


    public Position3DTimeseriesObject( ) {
    }
    public Position3DTimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
    }

    @Override
    public int getObjectType( ) {
        return Kind.Position3DTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new Position3DTimeseriesObject( );
    }

}
