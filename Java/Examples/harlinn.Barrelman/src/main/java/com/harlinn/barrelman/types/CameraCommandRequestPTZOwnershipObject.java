package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraCommandRequestPTZOwnershipObject extends CameraCommandObject {


    @Override
    public int getObjectType( ) {
        return Kind.CameraCommandRequestPTZOwnership;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraCommandRequestPTZOwnershipObject( );
    }

}
