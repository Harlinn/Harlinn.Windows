package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisDeviceObject extends TrackerDeviceObject {


    @Override
    public int getObjectType( ) {
        return Kind.AisDevice;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisDeviceObject( );
    }

}
