package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SecurityRoleObject extends SecurityIdentifierObject {

    private String _name = "";

    @Override
    public int getObjectType( ) {
        return Kind.SecurityRole;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new SecurityRoleObject( );
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


}
