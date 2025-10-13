package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ProcessTrackValueResultObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private boolean _createdNewTrack = false;
    private Guid _trackId;

    @Override
    public int getObjectType( ) {
        return Kind.ProcessTrackValueResult;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ProcessTrackValueResultObject( );
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

    public boolean getCreatedNewTrack( ) {
        return _createdNewTrack;
    }
    public void setCreatedNewTrack( boolean value ) {
        if( _createdNewTrack != value ) {
            this._createdNewTrack = value;
            onPropertyChanged( );
        }
    }

    public Guid getTrackId( ) {
        return _trackId;
    }
    public void setTrackId( Guid value ) {
        if( _trackId != value ) {
            this._trackId = value;
            onPropertyChanged( );
        }
    }


}
