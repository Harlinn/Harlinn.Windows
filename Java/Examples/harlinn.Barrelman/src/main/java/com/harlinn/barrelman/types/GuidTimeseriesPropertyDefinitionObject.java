package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GuidTimeseriesPropertyDefinitionObject extends TimeseriesPropertyDefinitionObject {

    public final int KIND = Kind.GuidTimeseriesPropertyDefinition;


    public GuidTimeseriesPropertyDefinitionObject( ) {
    }
    public GuidTimeseriesPropertyDefinitionObject( byte objectState, Guid id, long rowVersion, Guid elementType, String name, String description ) {
        super( objectState, id, rowVersion, elementType, name, description );
    }

    @Override
    public int getObjectType( ) {
        return Kind.GuidTimeseriesPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new GuidTimeseriesPropertyDefinitionObject( );
    }

}
