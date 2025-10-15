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
        if( !Comparer.equalsNullableGuid( _radome, value ) ) {
            _radome = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( RadomeTemperatureTimeseriesObject )target;
        targetObject._radome = this._radome;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (RadomeTemperatureTimeseriesObject)obj;
        if( !Comparer.equalsNullableGuid( this._radome, other._radome ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _radome );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _radome = source.readNullableGuid( );
    }

}
