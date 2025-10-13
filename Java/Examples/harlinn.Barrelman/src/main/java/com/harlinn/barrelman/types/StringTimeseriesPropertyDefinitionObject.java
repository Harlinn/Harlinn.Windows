package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class StringTimeseriesPropertyDefinitionObject extends TimeseriesPropertyDefinitionObject {

    private String _pattern = "";

    @Override
    public int getObjectType( ) {
        return Kind.StringTimeseriesPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new StringTimeseriesPropertyDefinitionObject( );
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
