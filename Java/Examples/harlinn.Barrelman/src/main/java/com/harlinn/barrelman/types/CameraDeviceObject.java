package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraDeviceObject extends DeviceObject {

    public final int KIND = Kind.CameraDevice;


    public CameraDeviceObject( ) {
    }
    public CameraDeviceObject( byte objectState, Guid id, long rowVersion, Guid host, String name, String description, Guid enabledTimeseries ) {
        super( objectState, id, rowVersion, host, name, description, enabledTimeseries );
    }

    @Override
    public int getObjectType( ) {
        return Kind.CameraDevice;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraDeviceObject( );
    }

}
