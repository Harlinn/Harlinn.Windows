package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadarSaveSettingsTimeseriesObject extends BooleanTimeseriesObject {

    private Guid _radar;

    @Override
    public int getObjectType( ) {
        return Kind.RadarSaveSettingsTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadarSaveSettingsTimeseriesObject( );
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
