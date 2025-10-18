package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadarAzimuthOffsetTimeseriesObject extends Int32TimeseriesObject {

    public final int KIND = Kind.RadarAzimuthOffsetTimeseries;

    private Guid _radar;

    public RadarAzimuthOffsetTimeseriesObject( ) {
    }
    public RadarAzimuthOffsetTimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention, Guid radar ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
        this._radar = radar;
    }

    @Override
    public int getObjectType( ) {
        return Kind.RadarAzimuthOffsetTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadarAzimuthOffsetTimeseriesObject( );
    }

    public Guid getRadar( ) {
        return _radar;
    }
    public void setRadar( Guid value ) {
        if( !Comparer.equalsNullableGuid( _radar, value ) ) {
            _radar = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( RadarAzimuthOffsetTimeseriesObject )target;
        targetObject._radar = this._radar;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (RadarAzimuthOffsetTimeseriesObject)obj;
        if( !Comparer.equalsNullableGuid( this._radar, other._radar ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _radar );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _radar = source.readNullableGuid( );
    }

}
