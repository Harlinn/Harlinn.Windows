package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GuidTimeseriesObject extends TimeseriesObject {


    @Override
    public int getObjectType( ) {
        return Kind.GuidTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new GuidTimeseriesObject( );
    }

}
