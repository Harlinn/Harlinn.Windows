package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadarCommandGetStatusObject extends RadarCommandObject {

    public final int KIND = Kind.RadarCommandGetStatus;


    public RadarCommandGetStatusObject( ) {
    }
    public RadarCommandGetStatusObject( byte objectState, Guid id, long rowVersion, Guid radar, DateTime timestamp, int deviceCommandSourceType, Guid deviceCommandSourceId, Guid reply ) {
        super( objectState, id, rowVersion, radar, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply );
    }

    @Override
    public int getObjectType( ) {
        return Kind.RadarCommandGetStatus;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadarCommandGetStatusObject( );
    }

}
