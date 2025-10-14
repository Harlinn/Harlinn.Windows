package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadomePressureTimeseriesObject extends DoubleTimeseriesObject {

    private Guid _radome;

    @Override
    public int getObjectType( ) {
        return Kind.RadomePressureTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadomePressureTimeseriesObject( );
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
