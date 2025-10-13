package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CallsignObject extends IdentityObject {

    private String _identifier = "";

    @Override
    public int getObjectType( ) {
        return Kind.Callsign;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CallsignObject( );
    }

    public String getIdentifier( ) {
        return _identifier;
    }
    public void setIdentifier( String value ) {
        if( _identifier != value ) {
            this._identifier = value;
            onPropertyChanged( );
        }
    }


}
