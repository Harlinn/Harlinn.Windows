package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class NameObject extends IdentityObject {

    private String _text = "";

    @Override
    public int getObjectType( ) {
        return Kind.Name;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new NameObject( );
    }

    public String getText( ) {
        return _text;
    }
    public void setText( String value ) {
        if( _text != value ) {
            this._text = value;
            onPropertyChanged( );
        }
    }


}
