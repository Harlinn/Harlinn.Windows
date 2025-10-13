package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraDeviceObject extends DeviceObject {


    @Override
    public int getObjectType( ) {
        return Kind.CameraDevice;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraDeviceObject( );
    }

}
