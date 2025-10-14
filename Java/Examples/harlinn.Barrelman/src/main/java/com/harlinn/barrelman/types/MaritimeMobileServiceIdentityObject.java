package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class MaritimeMobileServiceIdentityObject extends IdentityObject {

    private long _identifier = 0;

    @Override
    public int getObjectType( ) {
        return Kind.MaritimeMobileServiceIdentity;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new MaritimeMobileServiceIdentityObject( );
    }

    public long getIdentifier( ) {
        return _identifier;
    }
    public void setIdentifier( long value ) {
        if( !Comparer.equalsInt64( _identifier, value ) ) {
            _identifier = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _identifier );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _identifier = source.readInt64( );
    }

}
