package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class BaseStationTypeObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private String _name = "";

    @Override
    public int getObjectType( ) {
        return Kind.BaseStationType;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new BaseStationTypeObject( );
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
