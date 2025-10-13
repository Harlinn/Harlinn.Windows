package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class TimeseriesCatalogElementObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _catalog;
    private String _name = "";


    public long getRowVersion( ) {
        return _rowVersion;
    }
    public void setRowVersion( long value ) {
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getCatalog( ) {
        return _catalog;
    }
    public void setCatalog( Guid value ) {
        if( _catalog != value ) {
            this._catalog = value;
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


}
