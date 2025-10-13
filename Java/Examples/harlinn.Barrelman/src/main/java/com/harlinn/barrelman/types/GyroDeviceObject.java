package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GyroDeviceObject extends DeviceObject {

    private Guid _headingTrueNorthTimeseries;
    private Guid _headingMagneticNorthTimeseries;
    private Guid _pitchTimeseries;
    private Guid _rateOfTurnTimeseries;
    private Guid _rollTimeseries;
    private Guid _courseTimeseries;
    private Guid _speedTimeseries;
    private Guid _gNSSDevice;

    @Override
    public int getObjectType( ) {
        return Kind.GyroDevice;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new GyroDeviceObject( );
    }

    public Guid getHeadingTrueNorthTimeseries( ) {
        return _headingTrueNorthTimeseries;
    }
    public void setHeadingTrueNorthTimeseries( Guid value ) {
        if( _headingTrueNorthTimeseries != value ) {
            this._headingTrueNorthTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getHeadingMagneticNorthTimeseries( ) {
        return _headingMagneticNorthTimeseries;
    }
    public void setHeadingMagneticNorthTimeseries( Guid value ) {
        if( _headingMagneticNorthTimeseries != value ) {
            this._headingMagneticNorthTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getPitchTimeseries( ) {
        return _pitchTimeseries;
    }
    public void setPitchTimeseries( Guid value ) {
        if( _pitchTimeseries != value ) {
            this._pitchTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getRateOfTurnTimeseries( ) {
        return _rateOfTurnTimeseries;
    }
    public void setRateOfTurnTimeseries( Guid value ) {
        if( _rateOfTurnTimeseries != value ) {
            this._rateOfTurnTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getRollTimeseries( ) {
        return _rollTimeseries;
    }
    public void setRollTimeseries( Guid value ) {
        if( _rollTimeseries != value ) {
            this._rollTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getCourseTimeseries( ) {
        return _courseTimeseries;
    }
    public void setCourseTimeseries( Guid value ) {
        if( _courseTimeseries != value ) {
            this._courseTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getSpeedTimeseries( ) {
        return _speedTimeseries;
    }
    public void setSpeedTimeseries( Guid value ) {
        if( _speedTimeseries != value ) {
            this._speedTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getGNSSDevice( ) {
        return _gNSSDevice;
    }
    public void setGNSSDevice( Guid value ) {
        if( _gNSSDevice != value ) {
            this._gNSSDevice = value;
            onPropertyChanged( );
        }
    }


}
