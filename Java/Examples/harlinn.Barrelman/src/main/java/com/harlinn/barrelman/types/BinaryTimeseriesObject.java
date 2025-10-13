package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class BinaryTimeseriesObject extends TimeseriesObject {


    @Override
    public int getObjectType( ) {
        return Kind.BinaryTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new BinaryTimeseriesObject( );
    }

}
