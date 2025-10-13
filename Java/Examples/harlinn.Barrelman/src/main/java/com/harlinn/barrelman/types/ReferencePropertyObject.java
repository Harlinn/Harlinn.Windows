package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ReferencePropertyObject extends PropertyObject {

    private Guid _value;

    @Override
    public int getObjectType( ) {
        return Kind.ReferenceProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ReferencePropertyObject( );
    }

    public Guid getValue( ) {
        return _value;
    }
    public void setValue( Guid value ) {
        if( _value != value ) {
            this._value = value;
            onPropertyChanged( );
        }
    }


}
