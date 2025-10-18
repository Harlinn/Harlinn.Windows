package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class TrackerDeviceObject extends DeviceObject {

    public final int KIND = Kind.TrackerDevice;


    public TrackerDeviceObject( ) {
    }
    public TrackerDeviceObject( byte objectState, Guid id, long rowVersion, Guid host, String name, String description, Guid enabledTimeseries ) {
        super( objectState, id, rowVersion, host, name, description, enabledTimeseries );
    }


}
