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
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getMember( ) {
        return _member;
    }
    public void setMember( Guid value ) {
        if( _member != value ) {
            this._member = value;
            onPropertyChanged( );
        }
    }

    public Guid getRole( ) {
        return _role;
    }
    public void setRole( Guid value ) {
        if( _role != value ) {
            this._role = value;
            onPropertyChanged( );
        }
    }

    public DateTime getStart( ) {
        return _start;
    }
    public void setStart( DateTime value ) {
        if( _start != value ) {
            this._start = value;
            onPropertyChanged( );
        }
    }

    public DateTime getEnd( ) {
        return _end;
    }
    public void setEnd( DateTime value ) {
        if( _end != value ) {
            this._end = value;
            onPropertyChanged( );
        }
    }


}
