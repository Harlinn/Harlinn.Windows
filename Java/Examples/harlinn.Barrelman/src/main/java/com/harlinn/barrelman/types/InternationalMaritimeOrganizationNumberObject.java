package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class InternationalMaritimeOrganizationNumberObject extends IdentityObject {

    private long _identifier = 0;

    @Override
    public int getObjectType( ) {
        return Kind.InternationalMaritimeOrganizationNumber;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new InternationalMaritimeOrganizationNumberObject( );
    }

    public long getIdentifier( ) {
        return _identifier;
    }
    public void setIdentifier( long value ) {
        if( _identifier != value ) {
            this._identifier = value;
            onPropertyChanged( );
        }
    }


}
