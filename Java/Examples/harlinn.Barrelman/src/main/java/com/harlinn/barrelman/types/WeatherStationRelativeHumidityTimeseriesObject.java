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

public class WeatherStationRelativeHumidityTimeseriesObject extends DoubleTimeseriesObject {

    public final int KIND = Kind.WeatherStationRelativeHumidityTimeseries;

    private Guid _weatherStation;

    public WeatherStationRelativeHumidityTimeseriesObject( ) {
    }
    public WeatherStationRelativeHumidityTimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention, Guid weatherStation ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
        this._weatherStation = weatherStation;
    }

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
        if( !Comparer.equalsNullableGuid( _weatherStation, value ) ) {
            _weatherStation = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( WeatherStationRelativeHumidityTimeseriesObject )target;
        targetObject._weatherStation = this._weatherStation;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (WeatherStationRelativeHumidityTimeseriesObject)obj;
        if( !Comparer.equalsNullableGuid( this._weatherStation, other._weatherStation ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _weatherStation );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _weatherStation = source.readNullableGuid( );
    }

}
