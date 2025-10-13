package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SingleTimeseriesObject extends TimeseriesObject {


    @Override
    public int getObjectType( ) {
        return Kind.SingleTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new SingleTimeseriesObject( );
    }

}
