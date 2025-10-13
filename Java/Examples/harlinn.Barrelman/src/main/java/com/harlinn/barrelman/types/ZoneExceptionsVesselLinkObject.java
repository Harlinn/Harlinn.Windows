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
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getZoneExceptions( ) {
        return _zoneExceptions;
    }
    public void setZoneExceptions( Guid value ) {
        if( _zoneExceptions != value ) {
            this._zoneExceptions = value;
            onPropertyChanged( );
        }
    }

    public Guid getVessel( ) {
        return _vessel;
    }
    public void setVessel( Guid value ) {
        if( _vessel != value ) {
            this._vessel = value;
            onPropertyChanged( );
        }
    }


}
