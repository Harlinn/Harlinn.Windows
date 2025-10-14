package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class WeatherStationWindDirectionTimeseriesObject extends DoubleTimeseriesObject {

    private Guid _weatherStation;

    @Override
    public int getObjectType( ) {
        return Kind.WeatherStationWindDirectionTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new WeatherStationWindDirectionTimeseriesObject( );
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
