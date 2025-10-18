package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class OilSpillDetectorDeviceObject extends DeviceObject {

    public final int KIND = Kind.OilSpillDetectorDevice;


    public OilSpillDetectorDeviceObject( ) {
    }
    public OilSpillDetectorDeviceObject( byte objectState, Guid id, long rowVersion, Guid host, String name, String description, Guid enabledTimeseries ) {
        super( objectState, id, rowVersion, host, name, description, enabledTimeseries );
    }

    @Override
    public int getObjectType( ) {
        return Kind.OilSpillDetectorDevice;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new OilSpillDetectorDeviceObject( );
    }

}
