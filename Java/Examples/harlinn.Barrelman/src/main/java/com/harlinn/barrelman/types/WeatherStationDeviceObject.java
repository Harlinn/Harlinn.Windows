/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class WeatherStationDeviceObject extends DeviceObject {

    public final int KIND = Kind.WeatherStationDevice;

    private Guid _barometricPressureTimeseries;
    private Guid _airTemperatureTimeseries;
    private Guid _waterTemperatureTimeseries;
    private Guid _relativeHumidityTimeseries;
    private Guid _absoluteHumidityTimeseries;
    private Guid _dewPointTimeseries;
    private Guid _windDirectionTimeseries;
    private Guid _windSpeedTimeseries;
    private Guid _gyro;

    public WeatherStationDeviceObject( ) {
    }
    public WeatherStationDeviceObject( byte objectState, Guid id, long rowVersion, Guid host, String name, String description, Guid enabledTimeseries, Guid barometricPressureTimeseries, Guid airTemperatureTimeseries, Guid waterTemperatureTimeseries, Guid relativeHumidityTimeseries, Guid absoluteHumidityTimeseries, Guid dewPointTimeseries, Guid windDirectionTimeseries, Guid windSpeedTimeseries, Guid gyro ) {
        super( objectState, id, rowVersion, host, name, description, enabledTimeseries );
        this._barometricPressureTimeseries = barometricPressureTimeseries;
        this._airTemperatureTimeseries = airTemperatureTimeseries;
        this._waterTemperatureTimeseries = waterTemperatureTimeseries;
        this._relativeHumidityTimeseries = relativeHumidityTimeseries;
        this._absoluteHumidityTimeseries = absoluteHumidityTimeseries;
        this._dewPointTimeseries = dewPointTimeseries;
        this._windDirectionTimeseries = windDirectionTimeseries;
        this._windSpeedTimeseries = windSpeedTimeseries;
        this._gyro = gyro;
    }

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
        if( !Comparer.equalsNullableGuid( _barometricPressureTimeseries, value ) ) {
            _barometricPressureTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getAirTemperatureTimeseries( ) {
        return _airTemperatureTimeseries;
    }
    public void setAirTemperatureTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _airTemperatureTimeseries, value ) ) {
            _airTemperatureTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getWaterTemperatureTimeseries( ) {
        return _waterTemperatureTimeseries;
    }
    public void setWaterTemperatureTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _waterTemperatureTimeseries, value ) ) {
            _waterTemperatureTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getRelativeHumidityTimeseries( ) {
        return _relativeHumidityTimeseries;
    }
    public void setRelativeHumidityTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _relativeHumidityTimeseries, value ) ) {
            _relativeHumidityTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getAbsoluteHumidityTimeseries( ) {
        return _absoluteHumidityTimeseries;
    }
    public void setAbsoluteHumidityTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _absoluteHumidityTimeseries, value ) ) {
            _absoluteHumidityTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getDewPointTimeseries( ) {
        return _dewPointTimeseries;
    }
    public void setDewPointTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _dewPointTimeseries, value ) ) {
            _dewPointTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getWindDirectionTimeseries( ) {
        return _windDirectionTimeseries;
    }
    public void setWindDirectionTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _windDirectionTimeseries, value ) ) {
            _windDirectionTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getWindSpeedTimeseries( ) {
        return _windSpeedTimeseries;
    }
    public void setWindSpeedTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _windSpeedTimeseries, value ) ) {
            _windSpeedTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getGyro( ) {
        return _gyro;
    }
    public void setGyro( Guid value ) {
        if( !Comparer.equalsNullableGuid( _gyro, value ) ) {
            _gyro = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( WeatherStationDeviceObject )target;
        targetObject._barometricPressureTimeseries = this._barometricPressureTimeseries;
        targetObject._airTemperatureTimeseries = this._airTemperatureTimeseries;
        targetObject._waterTemperatureTimeseries = this._waterTemperatureTimeseries;
        targetObject._relativeHumidityTimeseries = this._relativeHumidityTimeseries;
        targetObject._absoluteHumidityTimeseries = this._absoluteHumidityTimeseries;
        targetObject._dewPointTimeseries = this._dewPointTimeseries;
        targetObject._windDirectionTimeseries = this._windDirectionTimeseries;
        targetObject._windSpeedTimeseries = this._windSpeedTimeseries;
        targetObject._gyro = this._gyro;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (WeatherStationDeviceObject)obj;
        if( !Comparer.equalsNullableGuid( this._barometricPressureTimeseries, other._barometricPressureTimeseries ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._airTemperatureTimeseries, other._airTemperatureTimeseries ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._waterTemperatureTimeseries, other._waterTemperatureTimeseries ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._relativeHumidityTimeseries, other._relativeHumidityTimeseries ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._absoluteHumidityTimeseries, other._absoluteHumidityTimeseries ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._dewPointTimeseries, other._dewPointTimeseries ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._windDirectionTimeseries, other._windDirectionTimeseries ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._windSpeedTimeseries, other._windSpeedTimeseries ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._gyro, other._gyro ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _barometricPressureTimeseries );
        destination.writeNullableGuid( _airTemperatureTimeseries );
        destination.writeNullableGuid( _waterTemperatureTimeseries );
        destination.writeNullableGuid( _relativeHumidityTimeseries );
        destination.writeNullableGuid( _absoluteHumidityTimeseries );
        destination.writeNullableGuid( _dewPointTimeseries );
        destination.writeNullableGuid( _windDirectionTimeseries );
        destination.writeNullableGuid( _windSpeedTimeseries );
        destination.writeNullableGuid( _gyro );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _barometricPressureTimeseries = source.readNullableGuid( );
        _airTemperatureTimeseries = source.readNullableGuid( );
        _waterTemperatureTimeseries = source.readNullableGuid( );
        _relativeHumidityTimeseries = source.readNullableGuid( );
        _absoluteHumidityTimeseries = source.readNullableGuid( );
        _dewPointTimeseries = source.readNullableGuid( );
        _windDirectionTimeseries = source.readNullableGuid( );
        _windSpeedTimeseries = source.readNullableGuid( );
        _gyro = source.readNullableGuid( );
    }

}
