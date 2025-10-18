package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SecurityLoginObject extends SecurityIdentifierObject {

    public final int KIND = Kind.SecurityLogin;


    public SecurityLoginObject( ) {
    }
    public SecurityLoginObject( byte objectState, Guid id, long rowVersion, Guid domain, String identity, String description ) {
        super( objectState, id, rowVersion, domain, identity, description );
    }

    @Override
    public int getObjectType( ) {
        return Kind.SecurityLogin;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new SecurityLoginObject( );
    }

}
