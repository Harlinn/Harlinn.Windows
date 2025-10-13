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
        if( _polygon != value ) {
            this._polygon = value;
            onPropertyChanged( );
        }
    }


}
