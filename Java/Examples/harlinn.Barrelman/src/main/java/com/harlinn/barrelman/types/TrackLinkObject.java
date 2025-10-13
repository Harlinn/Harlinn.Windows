package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class TrackLinkObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _primary;
    private Guid _secondary;
    private DateTime _start;
    private DateTime _end;

    @Override
    public int getObjectType( ) {
        return Kind.TrackLink;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new TrackLinkObject( );
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

    public Guid getPrimary( ) {
        return _primary;
    }
    public void setPrimary( Guid value ) {
        if( _primary != value ) {
            this._primary = value;
            onPropertyChanged( );
        }
    }

    public Guid getSecondary( ) {
        return _secondary;
    }
    public void setSecondary( Guid value ) {
        if( _secondary != value ) {
            this._secondary = value;
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
