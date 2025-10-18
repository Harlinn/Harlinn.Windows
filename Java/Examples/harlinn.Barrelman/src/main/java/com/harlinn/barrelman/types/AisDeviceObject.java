package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisDeviceObject extends TrackerDeviceObject {

    public final int KIND = Kind.AisDevice;


    public AisDeviceObject( ) {
    }
    public AisDeviceObject( byte objectState, Guid id, long rowVersion, Guid host, String name, String description, Guid enabledTimeseries ) {
        super( objectState, id, rowVersion, host, name, description, enabledTimeseries );
    }

    @Override
    public int getObjectType( ) {
        return Kind.AisDevice;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisDeviceObject( );
    }

}
