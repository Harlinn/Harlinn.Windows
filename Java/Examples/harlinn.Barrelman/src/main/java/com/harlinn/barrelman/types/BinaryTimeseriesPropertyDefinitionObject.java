package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class BinaryTimeseriesPropertyDefinitionObject extends TimeseriesPropertyDefinitionObject {


    @Override
    public int getObjectType( ) {
        return Kind.BinaryTimeseriesPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new BinaryTimeseriesPropertyDefinitionObject( );
    }

}
