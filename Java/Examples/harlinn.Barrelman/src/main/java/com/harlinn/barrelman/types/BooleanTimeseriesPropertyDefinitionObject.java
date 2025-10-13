package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class BooleanTimeseriesPropertyDefinitionObject extends TimeseriesPropertyDefinitionObject {


    @Override
    public int getObjectType( ) {
        return Kind.BooleanTimeseriesPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new BooleanTimeseriesPropertyDefinitionObject( );
    }

}
