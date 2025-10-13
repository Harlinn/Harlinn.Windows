package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class TimeSpanTimeseriesObject extends TimeseriesObject {


    @Override
    public int getObjectType( ) {
        return Kind.TimeSpanTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new TimeSpanTimeseriesObject( );
    }

}
