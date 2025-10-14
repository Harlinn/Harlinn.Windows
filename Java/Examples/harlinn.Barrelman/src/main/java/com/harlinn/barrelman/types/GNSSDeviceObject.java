package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GNSSDeviceObject extends DeviceObject {

    private Guid _latitudeTimeseries;
    private Guid _longitudeTimeseries;
    private Guid _altitudeTimeseries;

    @Override
    public int getObjectType( ) {
        return Kind.GNSSDevice;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new GNSSDeviceObject( );
    }

    public Guid getLatitudeTimeseries( ) {
        return _latitudeTimeseries;
    }
    public void setLatitudeTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _latitudeTimeseries, value ) ) {
            _latitudeTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getLongitudeTimeseries( ) {
        return _longitudeTimeseries;
    }
    public void setLongitudeTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _longitudeTimeseries, value ) ) {
            _longitudeTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getAltitudeTimeseries( ) {
        return _altitudeTimeseries;
    }
    public void setAltitudeTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _altitudeTimeseries, value ) ) {
            _altitudeTimeseries = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _latitudeTimeseries );
        destination.writeNullableGuid( _longitudeTimeseries );
        destination.writeNullableGuid( _altitudeTimeseries );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _latitudeTimeseries = source.readNullableGuid( );
        _longitudeTimeseries = source.readNullableGuid( );
        _altitudeTimeseries = source.readNullableGuid( );
    }

}
