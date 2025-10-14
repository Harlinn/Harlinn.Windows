package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadarBlankSector1TimeseriesObject extends BooleanTimeseriesObject {

    private Guid _radar;

    @Override
    public int getObjectType( ) {
        return Kind.RadarBlankSector1Timeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadarBlankSector1TimeseriesObject( );
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
