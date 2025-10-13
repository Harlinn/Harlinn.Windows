package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GeoPosition2DTimeseriesObject extends TimeseriesObject {


    @Override
    public int getObjectType( ) {
        return Kind.GeoPosition2DTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new GeoPosition2DTimeseriesObject( );
    }

}
