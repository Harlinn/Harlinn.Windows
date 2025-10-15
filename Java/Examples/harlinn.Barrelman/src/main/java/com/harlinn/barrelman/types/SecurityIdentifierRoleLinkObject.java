package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SecurityIdentifierRoleLinkObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _member;
    private Guid _role;
    private DateTime _start;
    private DateTime _end;

    @Override
    public int getObjectType( ) {
        return Kind.SecurityIdentifierRoleLink;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new SecurityIdentifierRoleLinkObject( );
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

    public Guid getMember( ) {
        return _member;
    }
    public void setMember( Guid value ) {
        if( !Comparer.equalsGuid( _member, value ) ) {
            _member = value;
            onPropertyChanged( );
        }
    }

    public Guid getRole( ) {
        return _role;
    }
    public void setRole( Guid value ) {
        if( !Comparer.equalsGuid( _role, value ) ) {
            _role = value;
            onPropertyChanged( );
        }
    }

    public DateTime getStart( ) {
        return _start;
    }
    public void setStart( DateTime value ) {
        if( !Comparer.equalsDateTime( _start, value ) ) {
            _start = value;
            onPropertyChanged( );
        }
    }

    public DateTime getEnd( ) {
        return _end;
    }
    public void setEnd( DateTime value ) {
        if( !Comparer.equalsNullableDateTime( _end, value ) ) {
            _end = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( SecurityIdentifierRoleLinkObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._member = this._member;
        targetObject._role = this._role;
        targetObject._start = this._start;
        targetObject._end = this._end;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (SecurityIdentifierRoleLinkObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._member, other._member ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._role, other._role ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._start, other._start ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDateTime( this._end, other._end ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _member );
        destination.writeGuid( _role );
        destination.writeDateTime( _start );
        destination.writeNullableDateTime( _end );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _member = source.readGuid( );
        _role = source.readGuid( );
        _start = source.readDateTime( );
        _end = source.readNullableDateTime( );
    }

}
