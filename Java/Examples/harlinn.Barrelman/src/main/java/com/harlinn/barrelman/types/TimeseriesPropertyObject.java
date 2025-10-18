package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class TimeseriesPropertyObject extends PropertyObject {

    public final int KIND = Kind.TimeseriesProperty;


    public TimeseriesPropertyObject( ) {
    }
    public TimeseriesPropertyObject( byte objectState, Guid id, long rowVersion, Guid element, Guid definition ) {
        super( objectState, id, rowVersion, element, definition );
    }


}
