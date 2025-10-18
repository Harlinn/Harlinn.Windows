package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class TimeseriesPropertyDefinitionObject extends PropertyDefinitionObject {

    public final int KIND = Kind.TimeseriesPropertyDefinition;


    public TimeseriesPropertyDefinitionObject( ) {
    }
    public TimeseriesPropertyDefinitionObject( byte objectState, Guid id, long rowVersion, Guid elementType, String name, String description ) {
        super( objectState, id, rowVersion, elementType, name, description );
    }


}
