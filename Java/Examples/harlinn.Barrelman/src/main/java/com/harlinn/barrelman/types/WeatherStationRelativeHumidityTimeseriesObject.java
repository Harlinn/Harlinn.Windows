package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class WeatherStationRelativeHumidityTimeseriesObject extends DoubleTimeseriesObject {

    private Guid _weatherStation;

    @Override
    public int getObjectType( ) {
        return Kind.WeatherStationRelativeHumidityTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new WeatherStationRelativeHumidityTimeseriesObject( );
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
