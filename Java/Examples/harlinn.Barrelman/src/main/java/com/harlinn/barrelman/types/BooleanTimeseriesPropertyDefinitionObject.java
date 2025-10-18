package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class BooleanTimeseriesPropertyDefinitionObject extends TimeseriesPropertyDefinitionObject {

    public final int KIND = Kind.BooleanTimeseriesPropertyDefinition;


    public BooleanTimeseriesPropertyDefinitionObject( ) {
    }
    public BooleanTimeseriesPropertyDefinitionObject( byte objectState, Guid id, long rowVersion, Guid elementType, String name, String description ) {
        super( objectState, id, rowVersion, elementType, name, description );
    }

    @Override
    public int getObjectType( ) {
        return Kind.BooleanTimeseriesPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new BooleanTimeseriesPropertyDefinitionObject( );
    }

}
