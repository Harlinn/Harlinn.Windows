package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class SecurityIdentifierObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _domain;
    private String _identity = "";
    private String _description = "";


    public long getRowVersion( ) {
        return _rowVersion;
    }
    public void setRowVersion( long value ) {
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getDomain( ) {
        return _domain;
    }
    public void setDomain( Guid value ) {
        if( !Comparer.equalsGuid( _domain, value ) ) {
            _domain = value;
            onPropertyChanged( );
        }
    }

    public String getIdentity( ) {
        return _identity;
    }
    public void setIdentity( String value ) {
        if( !Comparer.equalsString( _identity, value ) ) {
            _identity = value;
            onPropertyChanged( );
        }
    }

    public String getDescription( ) {
        return _description;
    }
    public void setDescription( String value ) {
        if( !Comparer.equalsString( _description, value ) ) {
            _description = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _domain );
        destination.writeStringUtf8( _identity );
        destination.writeStringUtf8( _description );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _domain = source.readGuid( );
        _identity = source.readString( );
        _description = source.readString( );
    }

}
