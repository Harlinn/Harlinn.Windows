package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class TrackerFilterParametersObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _tracker;
    private String _name = "";

    @Override
    public int getObjectType( ) {
        return Kind.TrackerFilterParameters;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new TrackerFilterParametersObject( );
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

    public Guid getTracker( ) {
        return _tracker;
    }
    public void setTracker( Guid value ) {
        if( _tracker != value ) {
            this._tracker = value;
            onPropertyChanged( );
        }
    }

    public String getName( ) {
        return _name;
    }
    public void setName( String value ) {
        if( _name != value ) {
            this._name = value;
            onPropertyChanged( );
        }
    }


}
