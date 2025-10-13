package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ReferencePropertyDefinitionObject extends PropertyDefinitionObject {

    private Guid _defaultValue;
    private Guid _referencedElementType;

    @Override
    public int getObjectType( ) {
        return Kind.ReferencePropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ReferencePropertyDefinitionObject( );
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

    public Guid getReferencedElementType( ) {
        return _referencedElementType;
    }
    public void setReferencedElementType( Guid value ) {
        if( _referencedElementType != value ) {
            this._referencedElementType = value;
            onPropertyChanged( );
        }
    }


}
