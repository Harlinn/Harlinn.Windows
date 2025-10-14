package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class VesselPersonsOnBoardTimeseriesObject extends Int32TimeseriesObject {

    private Guid _vessel;

    @Override
    public int getObjectType( ) {
        return Kind.VesselPersonsOnBoardTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new VesselPersonsOnBoardTimeseriesObject( );
    }

    public Guid getVessel( ) {
        return _vessel;
    }
    public void setVessel( Guid value ) {
        if( !Comparer.equalsNullableGuid( _vessel, value ) ) {
            _vessel = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _vessel );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _vessel = source.readNullableGuid( );
    }

}
