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
        if( !Comparer.equalsNullableGuid( _headingTrueNorthTimeseries, value ) ) {
            _headingTrueNorthTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getHeadingMagneticNorthTimeseries( ) {
        return _headingMagneticNorthTimeseries;
    }
    public void setHeadingMagneticNorthTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _headingMagneticNorthTimeseries, value ) ) {
            _headingMagneticNorthTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getPitchTimeseries( ) {
        return _pitchTimeseries;
    }
    public void setPitchTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _pitchTimeseries, value ) ) {
            _pitchTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getRateOfTurnTimeseries( ) {
        return _rateOfTurnTimeseries;
    }
    public void setRateOfTurnTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _rateOfTurnTimeseries, value ) ) {
            _rateOfTurnTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getRollTimeseries( ) {
        return _rollTimeseries;
    }
    public void setRollTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _rollTimeseries, value ) ) {
            _rollTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getCourseTimeseries( ) {
        return _courseTimeseries;
    }
    public void setCourseTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _courseTimeseries, value ) ) {
            _courseTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getSpeedTimeseries( ) {
        return _speedTimeseries;
    }
    public void setSpeedTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _speedTimeseries, value ) ) {
            _speedTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getGNSSDevice( ) {
        return _gNSSDevice;
    }
    public void setGNSSDevice( Guid value ) {
        if( !Comparer.equalsNullableGuid( _gNSSDevice, value ) ) {
            _gNSSDevice = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _headingTrueNorthTimeseries );
        destination.writeNullableGuid( _headingMagneticNorthTimeseries );
        destination.writeNullableGuid( _pitchTimeseries );
        destination.writeNullableGuid( _rateOfTurnTimeseries );
        destination.writeNullableGuid( _rollTimeseries );
        destination.writeNullableGuid( _courseTimeseries );
        destination.writeNullableGuid( _speedTimeseries );
        destination.writeNullableGuid( _gNSSDevice );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _headingTrueNorthTimeseries = source.readNullableGuid( );
        _headingMagneticNorthTimeseries = source.readNullableGuid( );
        _pitchTimeseries = source.readNullableGuid( );
        _rateOfTurnTimeseries = source.readNullableGuid( );
        _rollTimeseries = source.readNullableGuid( );
        _courseTimeseries = source.readNullableGuid( );
        _speedTimeseries = source.readNullableGuid( );
        _gNSSDevice = source.readNullableGuid( );
    }

}
