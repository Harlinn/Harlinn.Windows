package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ElementObject extends CatalogElementObject {

    private Guid _elementType;

    @Override
    public int getObjectType( ) {
        return Kind.Element;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ElementObject( );
    }

    public Guid getElementType( ) {
        return _elementType;
    }
    public void setElementType( Guid value ) {
        if( _elementType != value ) {
            this._elementType = value;
            onPropertyChanged( );
        }
    }


}
