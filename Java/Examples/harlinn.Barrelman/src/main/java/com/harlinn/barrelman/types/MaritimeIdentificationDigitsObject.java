package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class MaritimeIdentificationDigitsObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private int _code = 0;
    private Guid _country;

    @Override
    public int getObjectType( ) {
        return Kind.MaritimeIdentificationDigits;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new MaritimeIdentificationDigitsObject( );
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

    public int getCode( ) {
        return _code;
    }
    public void setCode( int value ) {
        if( _code != value ) {
            this._code = value;
            onPropertyChanged( );
        }
    }

    public Guid getCountry( ) {
        return _country;
    }
    public void setCountry( Guid value ) {
        if( _country != value ) {
            this._country = value;
            onPropertyChanged( );
        }
    }


}
