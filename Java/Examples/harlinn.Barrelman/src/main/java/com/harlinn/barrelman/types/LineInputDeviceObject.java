package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class LineInputDeviceObject extends DeviceObject {


    @Override
    public int getObjectType( ) {
        return Kind.LineInputDevice;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new LineInputDeviceObject( );
    }

}
