package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class WeatherStationWindDirectionTimeseriesObject extends DoubleTimeseriesObject {

    public final int KIND = Kind.WeatherStationWindDirectionTimeseries;

    private Guid _weatherStation;

    public WeatherStationWindDirectionTimeseriesObject( ) {
    }
    public WeatherStationWindDirectionTimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention, Guid weatherStation ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
        this._weatherStation = weatherStation;
    }

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
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( WeatherStationWindDirectionTimeseriesObject )target;
        targetObject._weatherStation = this._weatherStation;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (WeatherStationWindDirectionTimeseriesObject)obj;
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
