package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class StringPropertyDefinitionObject extends PropertyDefinitionObject {

    private String _defaultValue = "";
    private String _pattern = "";

    @Override
    public int getObjectType( ) {
        return Kind.StringPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new StringPropertyDefinitionObject( );
    }

    public String getDefaultValue( ) {
        return _defaultValue;
    }
    public void setDefaultValue( String value ) {
        if( _defaultValue != value ) {
            this._defaultValue = value;
            onPropertyChanged( );
        }
    }

    public String getPattern( ) {
        return _pattern;
    }
    public void setPattern( String value ) {
        if( _pattern != value ) {
            this._pattern = value;
            onPropertyChanged( );
        }
    }


}
