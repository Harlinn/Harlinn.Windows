package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GNSSAltitudeTimeseriesObject extends DoubleTimeseriesObject {

    public final int KIND = Kind.GNSSAltitudeTimeseries;

    private Guid _gNSSDevice;

    public GNSSAltitudeTimeseriesObject( ) {
    }
    public GNSSAltitudeTimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention, Guid gNSSDevice ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
        this._gNSSDevice = gNSSDevice;
    }

    @Override
    public int getObjectType( ) {
        return Kind.GNSSAltitudeTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new GNSSAltitudeTimeseriesObject( );
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
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( GNSSAltitudeTimeseriesObject )target;
        targetObject._gNSSDevice = this._gNSSDevice;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (GNSSAltitudeTimeseriesObject)obj;
        if( !Comparer.equalsNullableGuid( this._gNSSDevice, other._gNSSDevice ) ) {
            return false;
        }
        return true;
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
