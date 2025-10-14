package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class PolygonZoneObject extends ZoneObject {

    private byte[] _polygon = new byte[0];

    @Override
    public int getObjectType( ) {
        return Kind.PolygonZone;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new PolygonZoneObject( );
    }

    public byte[] getPolygon( ) {
        return _polygon;
    }
    public void setPolygon( byte[] value ) {
        if( !Comparer.equalsUInt8Array( _polygon, value ) ) {
            _polygon = value != null ? value.clone() : value;;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeUInt8Array( _polygon );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _polygon = source.readUInt8Array( );
    }

}
