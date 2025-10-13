package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CountryObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private String _name = "";
    private int _code = 0;
    private String _alpha2 = "";
    private String _alpha3 = "";

    @Override
    public int getObjectType( ) {
        return Kind.Country;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CountryObject( );
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

    public int getCode( ) {
        return _code;
    }
    public void setCode( int value ) {
        if( _code != value ) {
            this._code = value;
            onPropertyChanged( );
        }
    }

    public String getAlpha2( ) {
        return _alpha2;
    }
    public void setAlpha2( String value ) {
        if( _alpha2 != value ) {
            this._alpha2 = value;
            onPropertyChanged( );
        }
    }

    public String getAlpha3( ) {
        return _alpha3;
    }
    public void setAlpha3( String value ) {
        if( _alpha3 != value ) {
            this._alpha3 = value;
            onPropertyChanged( );
        }
    }


}
