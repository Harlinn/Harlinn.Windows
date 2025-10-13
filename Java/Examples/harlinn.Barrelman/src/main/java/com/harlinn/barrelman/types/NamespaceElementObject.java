package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class NamespaceElementObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _namespace;
    private String _name = "";
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

    public Guid getNamespace( ) {
        return _namespace;
    }
    public void setNamespace( Guid value ) {
        if( _namespace != value ) {
            this._namespace = value;
            onPropertyChanged( );
        }
    }

    public String getName( ) {
        return _name;
    }
    public void setName( String value ) {
        if( _name != value ) {
            this._name = value;
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
