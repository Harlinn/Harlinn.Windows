package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class VesselDraughtTimeseriesObject extends DoubleTimeseriesObject {

    public final int KIND = Kind.VesselDraughtTimeseries;

    private Guid _vessel;

    public VesselDraughtTimeseriesObject( ) {
    }
    public VesselDraughtTimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention, Guid vessel ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
        this._vessel = vessel;
    }

    @Override
    public int getObjectType( ) {
        return Kind.VesselDraughtTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new VesselDraughtTimeseriesObject( );
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
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( VesselDraughtTimeseriesObject )target;
        targetObject._vessel = this._vessel;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (VesselDraughtTimeseriesObject)obj;
        if( !Comparer.equalsNullableGuid( this._vessel, other._vessel ) ) {
            return false;
        }
        return true;
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
