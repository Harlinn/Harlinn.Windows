package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ByteTimeseriesObject extends TimeseriesObject {


    @Override
    public int getObjectType( ) {
        return Kind.ByteTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ByteTimeseriesObject( );
    }

}
