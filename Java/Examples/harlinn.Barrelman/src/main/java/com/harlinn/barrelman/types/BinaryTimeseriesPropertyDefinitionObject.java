package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class BinaryTimeseriesPropertyDefinitionObject extends TimeseriesPropertyDefinitionObject {

    public final int KIND = Kind.BinaryTimeseriesPropertyDefinition;


    public BinaryTimeseriesPropertyDefinitionObject( ) {
    }
    public BinaryTimeseriesPropertyDefinitionObject( byte objectState, Guid id, long rowVersion, Guid elementType, String name, String description ) {
        super( objectState, id, rowVersion, elementType, name, description );
    }

    @Override
    public int getObjectType( ) {
        return Kind.BinaryTimeseriesPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new BinaryTimeseriesPropertyDefinitionObject( );
    }

}
