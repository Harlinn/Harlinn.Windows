package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class Int16TimeseriesObject extends TimeseriesObject {


    @Override
    public int getObjectType( ) {
        return Kind.Int16Timeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new Int16TimeseriesObject( );
    }

}
