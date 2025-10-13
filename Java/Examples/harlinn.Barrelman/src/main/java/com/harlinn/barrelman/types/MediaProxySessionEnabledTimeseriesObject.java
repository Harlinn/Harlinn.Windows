package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class MediaProxySessionEnabledTimeseriesObject extends BooleanTimeseriesObject {

    private Guid _proxySession;

    @Override
    public int getObjectType( ) {
        return Kind.MediaProxySessionEnabledTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new MediaProxySessionEnabledTimeseriesObject( );
    }

    public Guid getProxySession( ) {
        return _proxySession;
    }
    public void setProxySession( Guid value ) {
        if( _proxySession != value ) {
            this._proxySession = value;
            onPropertyChanged( );
        }
    }


}
