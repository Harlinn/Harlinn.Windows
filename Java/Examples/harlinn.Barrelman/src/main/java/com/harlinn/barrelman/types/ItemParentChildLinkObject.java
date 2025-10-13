package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ItemParentChildLinkObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _parent;
    private Guid _child;
    private DateTime _timestamp;

    @Override
    public int getObjectType( ) {
        return Kind.ItemParentChildLink;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ItemParentChildLinkObject( );
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

    public Guid getParent( ) {
        return _parent;
    }
    public void setParent( Guid value ) {
        if( _parent != value ) {
            this._parent = value;
            onPropertyChanged( );
        }
    }

    public Guid getChild( ) {
        return _child;
    }
    public void setChild( Guid value ) {
        if( _child != value ) {
            this._child = value;
            onPropertyChanged( );
        }
    }

    public DateTime getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( DateTime value ) {
        if( _timestamp != value ) {
            this._timestamp = value;
            onPropertyChanged( );
        }
    }


}
