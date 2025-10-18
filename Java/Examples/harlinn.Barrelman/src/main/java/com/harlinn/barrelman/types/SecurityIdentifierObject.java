package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class SecurityIdentifierObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.SecurityIdentifier;

    private long _rowVersion = 0;
    private Guid _domain;
    private String _identity = "";
    private String _description = "";

    public SecurityIdentifierObject( ) {
    }
    public SecurityIdentifierObject( byte objectState, Guid id, long rowVersion, Guid domain, String identity, String description ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._domain = domain;
        this._identity = identity;
        this._description = description;
    }


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
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( SecurityIdentifierObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._domain = this._domain;
        targetObject._identity = this._identity;
        targetObject._description = this._description;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (SecurityIdentifierObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._domain, other._domain ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._identity, other._identity ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._description, other._description ) ) {
            return false;
        }
        return true;
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
