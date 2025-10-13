package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraCommandReleasePTZOwnershipObject extends CameraCommandObject {


    @Override
    public int getObjectType( ) {
        return Kind.CameraCommandReleasePTZOwnership;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraCommandReleasePTZOwnershipObject( );
    }

}
