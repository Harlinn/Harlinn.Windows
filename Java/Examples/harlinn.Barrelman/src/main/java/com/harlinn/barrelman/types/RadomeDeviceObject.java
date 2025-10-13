package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadomeDeviceObject extends DeviceObject {

    private Guid _radar;
    private Guid _pressureTimeseries;
    private Guid _temperatureTimeseries;
    private Guid _dewPointTimeseries;
    private Guid _statusTimeseries;

    @Override
    public int getObjectType( ) {
        return Kind.RadomeDevice;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadomeDeviceObject( );
    }

    public Guid getRadar( ) {
        return _radar;
    }
    public void setRadar( Guid value ) {
        if( _radar != value ) {
            this._radar = value;
            onPropertyChanged( );
        }
    }

    public Guid getPressureTimeseries( ) {
        return _pressureTimeseries;
    }
    public void setPressureTimeseries( Guid value ) {
        if( _pressureTimeseries != value ) {
            this._pressureTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getTemperatureTimeseries( ) {
        return _temperatureTimeseries;
    }
    public void setTemperatureTimeseries( Guid value ) {
        if( _temperatureTimeseries != value ) {
            this._temperatureTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getDewPointTimeseries( ) {
        return _dewPointTimeseries;
    }
    public void setDewPointTimeseries( Guid value ) {
        if( _dewPointTimeseries != value ) {
            this._dewPointTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getStatusTimeseries( ) {
        return _statusTimeseries;
    }
    public void setStatusTimeseries( Guid value ) {
        if( _statusTimeseries != value ) {
            this._statusTimeseries = value;
            onPropertyChanged( );
        }
    }


}
