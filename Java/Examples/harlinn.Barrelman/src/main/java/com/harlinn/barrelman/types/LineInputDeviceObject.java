package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class LineInputDeviceObject extends DeviceObject {

    public final int KIND = Kind.LineInputDevice;


    public LineInputDeviceObject( ) {
    }
    public LineInputDeviceObject( byte objectState, Guid id, long rowVersion, Guid host, String name, String description, Guid enabledTimeseries ) {
        super( objectState, id, rowVersion, host, name, description, enabledTimeseries );
    }

    @Override
    public int getObjectType( ) {
        return Kind.LineInputDevice;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new LineInputDeviceObject( );
    }

}
