package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class Position3DTimeseriesObject extends TimeseriesObject {


    @Override
    public int getObjectType( ) {
        return Kind.Position3DTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new Position3DTimeseriesObject( );
    }

}
