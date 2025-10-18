package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadomeDewPointTimeseriesObject extends DoubleTimeseriesObject {

    public final int KIND = Kind.RadomeDewPointTimeseries;

    private Guid _radome;

    public RadomeDewPointTimeseriesObject( ) {
    }
    public RadomeDewPointTimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention, Guid radome ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
        this._radome = radome;
    }

    @Override
    public int getObjectType( ) {
        return Kind.RadomeDewPointTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadomeDewPointTimeseriesObject( );
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
        var targetObject = ( RadomeDewPointTimeseriesObject )target;
        targetObject._radome = this._radome;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (RadomeDewPointTimeseriesObject)obj;
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
