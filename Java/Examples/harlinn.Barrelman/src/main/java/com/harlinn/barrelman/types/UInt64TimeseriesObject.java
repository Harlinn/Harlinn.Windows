package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class UInt64TimeseriesObject extends TimeseriesObject {


    @Override
    public int getObjectType( ) {
        return Kind.UInt64Timeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new UInt64TimeseriesObject( );
    }

}
