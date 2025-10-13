package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class WeatherStationDewPointTimeseriesObject extends DoubleTimeseriesObject {

    private Guid _weatherStation;

    @Override
    public int getObjectType( ) {
        return Kind.WeatherStationDewPointTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new WeatherStationDewPointTimeseriesObject( );
    }

    public Guid getWeatherStation( ) {
        return _weatherStation;
    }
    public void setWeatherStation( Guid value ) {
        if( _weatherStation != value ) {
            this._weatherStation = value;
            onPropertyChanged( );
        }
    }


}
