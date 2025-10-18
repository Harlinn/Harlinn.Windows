package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ZoneExceptionsVesselLinkObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.ZoneExceptionsVesselLink;

    private long _rowVersion = 0;
    private Guid _zoneExceptions;
    private Guid _vessel;

    public ZoneExceptionsVesselLinkObject( ) {
    }
    public ZoneExceptionsVesselLinkObject( byte objectState, Guid id, long rowVersion, Guid zoneExceptions, Guid vessel ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._zoneExceptions = zoneExceptions;
        this._vessel = vessel;
    }

    @Override
    public int getObjectType( ) {
        return Kind.ZoneExceptionsVesselLink;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ZoneExceptionsVesselLinkObject( );
    }

    public long getRowVersion( ) {
        return _rowVersion;
    }
    public void setRowVersion( long value ) {
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getZoneExceptions( ) {
        return _zoneExceptions;
    }
    public void setZoneExceptions( Guid value ) {
        if( !Comparer.equalsGuid( _zoneExceptions, value ) ) {
            _zoneExceptions = value;
            onPropertyChanged( );
        }
    }

    public Guid getVessel( ) {
        return _vessel;
    }
    public void setVessel( Guid value ) {
        if( !Comparer.equalsGuid( _vessel, value ) ) {
            _vessel = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( ZoneExceptionsVesselLinkObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._zoneExceptions = this._zoneExceptions;
        targetObject._vessel = this._vessel;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (ZoneExceptionsVesselLinkObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._zoneExceptions, other._zoneExceptions ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._vessel, other._vessel ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _zoneExceptions );
        destination.writeGuid( _vessel );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _zoneExceptions = source.readGuid( );
        _vessel = source.readGuid( );
    }

}
