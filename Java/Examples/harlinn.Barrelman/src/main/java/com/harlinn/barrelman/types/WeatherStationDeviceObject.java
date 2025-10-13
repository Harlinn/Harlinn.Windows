package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class WeatherStationDeviceObject extends DeviceObject {

    private Guid _barometricPressureTimeseries;
    private Guid _airTemperatureTimeseries;
    private Guid _waterTemperatureTimeseries;
    private Guid _relativeHumidityTimeseries;
    private Guid _absoluteHumidityTimeseries;
    private Guid _dewPointTimeseries;
    private Guid _windDirectionTimeseries;
    private Guid _windSpeedTimeseries;
    private Guid _gyro;

    @Override
    public int getObjectType( ) {
        return Kind.WeatherStationDevice;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new WeatherStationDeviceObject( );
    }

    public Guid getBarometricPressureTimeseries( ) {
        return _barometricPressureTimeseries;
    }
    public void setBarometricPressureTimeseries( Guid value ) {
        if( _barometricPressureTimeseries != value ) {
            this._barometricPressureTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getAirTemperatureTimeseries( ) {
        return _airTemperatureTimeseries;
    }
    public void setAirTemperatureTimeseries( Guid value ) {
        if( _airTemperatureTimeseries != value ) {
            this._airTemperatureTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getWaterTemperatureTimeseries( ) {
        return _waterTemperatureTimeseries;
    }
    public void setWaterTemperatureTimeseries( Guid value ) {
        if( _waterTemperatureTimeseries != value ) {
            this._waterTemperatureTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getRelativeHumidityTimeseries( ) {
        return _relativeHumidityTimeseries;
    }
    public void setRelativeHumidityTimeseries( Guid value ) {
        if( _relativeHumidityTimeseries != value ) {
            this._relativeHumidityTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getAbsoluteHumidityTimeseries( ) {
        return _absoluteHumidityTimeseries;
    }
    public void setAbsoluteHumidityTimeseries( Guid value ) {
        if( _absoluteHumidityTimeseries != value ) {
            this._absoluteHumidityTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getDewPointTimeseries( ) {
        return _dewPointTimeseries;
    }
    public void setDewPointTimeseries( Guid value ) {
        if( _dewPointTimeseries != value ) {
            this._dewPointTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getWindDirectionTimeseries( ) {
        return _windDirectionTimeseries;
    }
    public void setWindDirectionTimeseries( Guid value ) {
        if( _windDirectionTimeseries != value ) {
            this._windDirectionTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getWindSpeedTimeseries( ) {
        return _windSpeedTimeseries;
    }
    public void setWindSpeedTimeseries( Guid value ) {
        if( _windSpeedTimeseries != value ) {
            this._windSpeedTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getGyro( ) {
        return _gyro;
    }
    public void setGyro( Guid value ) {
        if( _gyro != value ) {
            this._gyro = value;
            onPropertyChanged( );
        }
    }


}
