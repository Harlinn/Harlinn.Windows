package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SecurityLoginObject extends SecurityIdentifierObject {


    @Override
    public int getObjectType( ) {
        return Kind.SecurityLogin;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new SecurityLoginObject( );
    }

}
