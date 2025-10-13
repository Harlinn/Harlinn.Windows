package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class SecurityIdentifierObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _domain;
    private String _identity = "";
    private String _description = "";


    public long getRowVersion( ) {
        return _rowVersion;
    }
    public void setRowVersion( long value ) {
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getDomain( ) {
        return _domain;
    }
    public void setDomain( Guid value ) {
        if( _domain != value ) {
            this._domain = value;
            onPropertyChanged( );
        }
    }

    public String getIdentity( ) {
        return _identity;
    }
    public void setIdentity( String value ) {
        if( _identity != value ) {
            this._identity = value;
            onPropertyChanged( );
        }
    }

    public String getDescription( ) {
        return _description;
    }
    public void setDescription( String value ) {
        if( _description != value ) {
            this._description = value;
            onPropertyChanged( );
        }
    }


}
