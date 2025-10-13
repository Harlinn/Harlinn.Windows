package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GuidPropertyDefinitionObject extends PropertyDefinitionObject {

    private Guid _defaultValue;

    @Override
    public int getObjectType( ) {
        return Kind.GuidPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new GuidPropertyDefinitionObject( );
    }

    public Guid getDefaultValue( ) {
        return _defaultValue;
    }
    public void setDefaultValue( Guid value ) {
        if( _defaultValue != value ) {
            this._defaultValue = value;
            onPropertyChanged( );
        }
    }


}
