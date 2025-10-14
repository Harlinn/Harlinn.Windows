package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GNSSLatitudeTimeseriesObject extends DoubleTimeseriesObject {

    private Guid _gNSSDevice;

    @Override
    public int getObjectType( ) {
        return Kind.GNSSLatitudeTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new GNSSLatitudeTimeseriesObject( );
    }

    public Guid getGNSSDevice( ) {
        return _gNSSDevice;
    }
    public void setGNSSDevice( Guid value ) {
        if( !Comparer.equalsNullableGuid( _gNSSDevice, value ) ) {
            _gNSSDevice = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _gNSSDevice );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _gNSSDevice = source.readNullableGuid( );
    }

}
