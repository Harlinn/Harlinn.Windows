package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ReferenceTimeseriesObject extends TimeseriesObject {


    @Override
    public int getObjectType( ) {
        return Kind.ReferenceTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ReferenceTimeseriesObject( );
    }

}
