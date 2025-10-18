package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadarSensitivityTimeControlLevelTimeseriesObject extends Int32TimeseriesObject {

    public final int KIND = Kind.RadarSensitivityTimeControlLevelTimeseries;

    private Guid _radar;

    public RadarSensitivityTimeControlLevelTimeseriesObject( ) {
    }
    public RadarSensitivityTimeControlLevelTimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention, Guid radar ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
        this._radar = radar;
    }

    @Override
    public int getObjectType( ) {
        return Kind.RadarSensitivityTimeControlLevelTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadarSensitivityTimeControlLevelTimeseriesObject( );
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
        var targetObject = ( RadarSensitivityTimeControlLevelTimeseriesObject )target;
        targetObject._radar = this._radar;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (RadarSensitivityTimeControlLevelTimeseriesObject)obj;
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
