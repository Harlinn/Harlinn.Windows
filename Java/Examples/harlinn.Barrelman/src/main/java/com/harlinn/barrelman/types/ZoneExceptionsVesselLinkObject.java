package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ZoneExceptionsVesselLinkObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _zoneExceptions;
    private Guid _vessel;

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
