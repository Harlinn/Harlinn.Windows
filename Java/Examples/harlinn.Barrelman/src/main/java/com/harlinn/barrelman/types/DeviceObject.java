package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class DeviceObject extends ItemObject {

    private Guid _host;
    private String _name = "";
    private String _description = "";
    private Guid _enabledTimeseries;


    public Guid getHost( ) {
        return _host;
    }
    public void setHost( Guid value ) {
        if( _host != value ) {
            this._host = value;
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

    public String getDescription( ) {
        return _description;
    }
    public void setDescription( String value ) {
        if( _description != value ) {
            this._description = value;
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
