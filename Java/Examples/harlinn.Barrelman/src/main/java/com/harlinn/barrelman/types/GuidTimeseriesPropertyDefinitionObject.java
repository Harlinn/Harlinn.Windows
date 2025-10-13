package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GuidTimeseriesPropertyDefinitionObject extends TimeseriesPropertyDefinitionObject {


    @Override
    public int getObjectType( ) {
        return Kind.GuidTimeseriesPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new GuidTimeseriesPropertyDefinitionObject( );
    }

}
