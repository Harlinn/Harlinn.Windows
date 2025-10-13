package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadarSector2StartTimeseriesObject extends Int32TimeseriesObject {

    private Guid _radar;

    @Override
    public int getObjectType( ) {
        return Kind.RadarSector2StartTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadarSector2StartTimeseriesObject( );
    }

    public Guid getRadar( ) {
        return _radar;
    }
    public void setRadar( Guid value ) {
        if( _radar != value ) {
            this._radar = value;
            onPropertyChanged( );
        }
    }


}
