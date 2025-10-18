package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GyroDeviceObject extends DeviceObject {

    public final int KIND = Kind.GyroDevice;

    private Guid _headingTrueNorthTimeseries;
    private Guid _headingMagneticNorthTimeseries;
    private Guid _pitchTimeseries;
    private Guid _rateOfTurnTimeseries;
    private Guid _rollTimeseries;
    private Guid _courseTimeseries;
    private Guid _speedTimeseries;
    private Guid _gNSSDevice;

    public GyroDeviceObject( ) {
    }
    public GyroDeviceObject( byte objectState, Guid id, long rowVersion, Guid host, String name, String description, Guid enabledTimeseries, Guid headingTrueNorthTimeseries, Guid headingMagneticNorthTimeseries, Guid pitchTimeseries, Guid rateOfTurnTimeseries, Guid rollTimeseries, Guid courseTimeseries, Guid speedTimeseries, Guid gNSSDevice ) {
        super( objectState, id, rowVersion, host, name, description, enabledTimeseries );
        this._headingTrueNorthTimeseries = headingTrueNorthTimeseries;
        this._headingMagneticNorthTimeseries = headingMagneticNorthTimeseries;
        this._pitchTimeseries = pitchTimeseries;
        this._rateOfTurnTimeseries = rateOfTurnTimeseries;
        this._rollTimeseries = rollTimeseries;
        this._courseTimeseries = courseTimeseries;
        this._speedTimeseries = speedTimeseries;
        this._gNSSDevice = gNSSDevice;
    }

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
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( GyroDeviceObject )target;
        targetObject._headingTrueNorthTimeseries = this._headingTrueNorthTimeseries;
        targetObject._headingMagneticNorthTimeseries = this._headingMagneticNorthTimeseries;
        targetObject._pitchTimeseries = this._pitchTimeseries;
        targetObject._rateOfTurnTimeseries = this._rateOfTurnTimeseries;
        targetObject._rollTimeseries = this._rollTimeseries;
        targetObject._courseTimeseries = this._courseTimeseries;
        targetObject._speedTimeseries = this._speedTimeseries;
        targetObject._gNSSDevice = this._gNSSDevice;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (GyroDeviceObject)obj;
        if( !Comparer.equalsNullableGuid( this._headingTrueNorthTimeseries, other._headingTrueNorthTimeseries ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._headingMagneticNorthTimeseries, other._headingMagneticNorthTimeseries ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._pitchTimeseries, other._pitchTimeseries ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._rateOfTurnTimeseries, other._rateOfTurnTimeseries ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._rollTimeseries, other._rollTimeseries ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._courseTimeseries, other._courseTimeseries ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._speedTimeseries, other._speedTimeseries ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._gNSSDevice, other._gNSSDevice ) ) {
            return false;
        }
        return true;
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
