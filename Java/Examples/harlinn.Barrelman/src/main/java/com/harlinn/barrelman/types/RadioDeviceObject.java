package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadioDeviceObject extends DeviceObject {


    @Override
    public int getObjectType( ) {
        return Kind.RadioDevice;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadioDeviceObject( );
    }

}
