package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class StringTimeseriesObject extends TimeseriesObject {


    @Override
    public int getObjectType( ) {
        return Kind.StringTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new StringTimeseriesObject( );
    }

}
