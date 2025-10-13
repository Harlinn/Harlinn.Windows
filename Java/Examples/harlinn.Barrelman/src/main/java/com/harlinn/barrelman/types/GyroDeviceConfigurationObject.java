package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GyroDeviceConfigurationObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _gyroDevice;
    private DateTime _timestamp;
    private double _defaultHeadingTrueNorth = 0.0;
    private double _defaultMagneticTrueNorth = 0.0;
    private double _headingTrueNorthOffset = 0.0;
    private double _headingMagneticNorthOffset = 0.0;
    private String _pitchTransducerName = "";
    private String _rollTransducerName = "";

    @Override
    public int getObjectType( ) {
        return Kind.GyroDeviceConfiguration;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new GyroDeviceConfigurationObject( );
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

    public Guid getGyroDevice( ) {
        return _gyroDevice;
    }
    public void setGyroDevice( Guid value ) {
        if( _gyroDevice != value ) {
            this._gyroDevice = value;
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

    public double getDefaultHeadingTrueNorth( ) {
        return _defaultHeadingTrueNorth;
    }
    public void setDefaultHeadingTrueNorth( double value ) {
        if( _defaultHeadingTrueNorth != value ) {
            this._defaultHeadingTrueNorth = value;
            onPropertyChanged( );
        }
    }

    public double getDefaultMagneticTrueNorth( ) {
        return _defaultMagneticTrueNorth;
    }
    public void setDefaultMagneticTrueNorth( double value ) {
        if( _defaultMagneticTrueNorth != value ) {
            this._defaultMagneticTrueNorth = value;
            onPropertyChanged( );
        }
    }

    public double getHeadingTrueNorthOffset( ) {
        return _headingTrueNorthOffset;
    }
    public void setHeadingTrueNorthOffset( double value ) {
        if( _headingTrueNorthOffset != value ) {
            this._headingTrueNorthOffset = value;
            onPropertyChanged( );
        }
    }

    public double getHeadingMagneticNorthOffset( ) {
        return _headingMagneticNorthOffset;
    }
    public void setHeadingMagneticNorthOffset( double value ) {
        if( _headingMagneticNorthOffset != value ) {
            this._headingMagneticNorthOffset = value;
            onPropertyChanged( );
        }
    }

    public String getPitchTransducerName( ) {
        return _pitchTransducerName;
    }
    public void setPitchTransducerName( String value ) {
        if( _pitchTransducerName != value ) {
            this._pitchTransducerName = value;
            onPropertyChanged( );
        }
    }

    public String getRollTransducerName( ) {
        return _rollTransducerName;
    }
    public void setRollTransducerName( String value ) {
        if( _rollTransducerName != value ) {
            this._rollTransducerName = value;
            onPropertyChanged( );
        }
    }


}
