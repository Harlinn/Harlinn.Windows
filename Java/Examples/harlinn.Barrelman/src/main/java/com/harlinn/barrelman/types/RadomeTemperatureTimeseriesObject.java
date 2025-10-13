package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadomeTemperatureTimeseriesObject extends DoubleTimeseriesObject {

    private Guid _radome;

    @Override
    public int getObjectType( ) {
        return Kind.RadomeTemperatureTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadomeTemperatureTimeseriesObject( );
    }

    public Guid getRadome( ) {
        return _radome;
    }
    public void setRadome( Guid value ) {
        if( _radome != value ) {
            this._radome = value;
            onPropertyChanged( );
        }
    }


}
