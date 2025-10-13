package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ItemIdentityLinkObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _item;
    private Guid _identity;
    private DateTime _start;
    private DateTime _end;

    @Override
    public int getObjectType( ) {
        return Kind.ItemIdentityLink;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ItemIdentityLinkObject( );
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

    public Guid getItem( ) {
        return _item;
    }
    public void setItem( Guid value ) {
        if( _item != value ) {
            this._item = value;
            onPropertyChanged( );
        }
    }

    public Guid getIdentity( ) {
        return _identity;
    }
    public void setIdentity( Guid value ) {
        if( _identity != value ) {
            this._identity = value;
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
