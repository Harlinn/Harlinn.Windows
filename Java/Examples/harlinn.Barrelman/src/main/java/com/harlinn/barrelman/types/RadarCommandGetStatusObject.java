package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadarCommandGetStatusObject extends RadarCommandObject {


    @Override
    public int getObjectType( ) {
        return Kind.RadarCommandGetStatus;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadarCommandGetStatusObject( );
    }

}
