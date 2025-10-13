package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GNSSLongitudeTimeseriesObject extends DoubleTimeseriesObject {

    private Guid _gNSSDevice;

    @Override
    public int getObjectType( ) {
        return Kind.GNSSLongitudeTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new GNSSLongitudeTimeseriesObject( );
    }

    public Guid getGNSSDevice( ) {
        return _gNSSDevice;
    }
    public void setGNSSDevice( Guid value ) {
        if( _gNSSDevice != value ) {
            this._gNSSDevice = value;
            onPropertyChanged( );
        }
    }


}
