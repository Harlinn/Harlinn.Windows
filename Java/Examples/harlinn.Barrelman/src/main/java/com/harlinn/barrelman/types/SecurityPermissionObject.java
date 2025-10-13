package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SecurityPermissionObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _identifier;
    private DateTime _timestamp;
    private int _typeCode = 0;
    private boolean _canCreate = false;
    private boolean _canRead = false;
    private boolean _canUpdate = false;
    private boolean _canDelete = false;

    @Override
    public int getObjectType( ) {
        return Kind.SecurityPermission;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new SecurityPermissionObject( );
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

    public Guid getIdentifier( ) {
        return _identifier;
    }
    public void setIdentifier( Guid value ) {
        if( _identifier != value ) {
            this._identifier = value;
            onPropertyChanged( );
        }
    }

    public DateTime getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( DateTime value ) {
        if( _timestamp != value ) {
            this._timestamp = value;
            onPropertyChanged( );
        }
    }

    public int getTypeCode( ) {
        return _typeCode;
    }
    public void setTypeCode( int value ) {
        if( _typeCode != value ) {
            this._typeCode = value;
            onPropertyChanged( );
        }
    }

    public boolean getCanCreate( ) {
        return _canCreate;
    }
    public void setCanCreate( boolean value ) {
        if( _canCreate != value ) {
            this._canCreate = value;
            onPropertyChanged( );
        }
    }

    public boolean getCanRead( ) {
        return _canRead;
    }
    public void setCanRead( boolean value ) {
        if( _canRead != value ) {
            this._canRead = value;
            onPropertyChanged( );
        }
    }

    public boolean getCanUpdate( ) {
        return _canUpdate;
    }
    public void setCanUpdate( boolean value ) {
        if( _canUpdate != value ) {
            this._canUpdate = value;
            onPropertyChanged( );
        }
    }

    public boolean getCanDelete( ) {
        return _canDelete;
    }
    public void setCanDelete( boolean value ) {
        if( _canDelete != value ) {
            this._canDelete = value;
            onPropertyChanged( );
        }
    }


}
