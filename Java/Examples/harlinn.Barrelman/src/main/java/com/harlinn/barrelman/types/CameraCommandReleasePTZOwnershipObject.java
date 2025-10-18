package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraCommandReleasePTZOwnershipObject extends CameraCommandObject {

    public final int KIND = Kind.CameraCommandReleasePTZOwnership;


    public CameraCommandReleasePTZOwnershipObject( ) {
    }
    public CameraCommandReleasePTZOwnershipObject( byte objectState, Guid id, long rowVersion, Guid camera, DateTime timestamp, int deviceCommandSourceType, Guid deviceCommandSourceId, Guid reply ) {
        super( objectState, id, rowVersion, camera, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply );
    }

    @Override
    public int getObjectType( ) {
        return Kind.CameraCommandReleasePTZOwnership;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraCommandReleasePTZOwnershipObject( );
    }

}
