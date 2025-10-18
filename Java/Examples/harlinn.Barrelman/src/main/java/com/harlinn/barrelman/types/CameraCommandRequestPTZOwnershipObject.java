package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraCommandRequestPTZOwnershipObject extends CameraCommandObject {

    public final int KIND = Kind.CameraCommandRequestPTZOwnership;


    public CameraCommandRequestPTZOwnershipObject( ) {
    }
    public CameraCommandRequestPTZOwnershipObject( byte objectState, Guid id, long rowVersion, Guid camera, DateTime timestamp, int deviceCommandSourceType, Guid deviceCommandSourceId, Guid reply ) {
        super( objectState, id, rowVersion, camera, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply );
    }

    @Override
    public int getObjectType( ) {
        return Kind.CameraCommandRequestPTZOwnership;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraCommandRequestPTZOwnershipObject( );
    }

}
