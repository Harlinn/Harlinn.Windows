package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class MediaServiceObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _enabledTimeseries;

    @Override
    public int getObjectType( ) {
        return Kind.MediaService;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new MediaServiceObject( );
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

    public Guid getEnabledTimeseries( ) {
        return _enabledTimeseries;
    }
    public void setEnabledTimeseries( Guid value ) {
        if( _enabledTimeseries != value ) {
            this._enabledTimeseries = value;
            onPropertyChanged( );
        }
    }


}
