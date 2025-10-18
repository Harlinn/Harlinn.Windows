package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadioDeviceObject extends DeviceObject {

    public final int KIND = Kind.RadioDevice;


    public RadioDeviceObject( ) {
    }
    public RadioDeviceObject( byte objectState, Guid id, long rowVersion, Guid host, String name, String description, Guid enabledTimeseries ) {
        super( objectState, id, rowVersion, host, name, description, enabledTimeseries );
    }

    @Override
    public int getObjectType( ) {
        return Kind.RadioDevice;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadioDeviceObject( );
    }

}
