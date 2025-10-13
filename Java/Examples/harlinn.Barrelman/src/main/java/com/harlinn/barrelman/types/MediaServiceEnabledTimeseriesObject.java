package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class MediaServiceEnabledTimeseriesObject extends BooleanTimeseriesObject {

    private Guid _service;

    @Override
    public int getObjectType( ) {
        return Kind.MediaServiceEnabledTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new MediaServiceEnabledTimeseriesObject( );
    }

    public Guid getService( ) {
        return _service;
    }
    public void setService( Guid value ) {
        if( _service != value ) {
            this._service = value;
            onPropertyChanged( );
        }
    }


}
