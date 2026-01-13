/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GyroDeviceConfigurationObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.GyroDeviceConfiguration;

    private long _rowVersion = 0;
    private Guid _gyroDevice;
    private DateTime _timestamp;
    private double _defaultHeadingTrueNorth = 0.0;
    private double _defaultMagneticTrueNorth = 0.0;
    private double _headingTrueNorthOffset = 0.0;
    private double _headingMagneticNorthOffset = 0.0;
    private String _pitchTransducerName = "";
    private String _rollTransducerName = "";

    public GyroDeviceConfigurationObject( ) {
    }
    public GyroDeviceConfigurationObject( byte objectState, Guid id, long rowVersion, Guid gyroDevice, DateTime timestamp, double defaultHeadingTrueNorth, double defaultMagneticTrueNorth, double headingTrueNorthOffset, double headingMagneticNorthOffset, String pitchTransducerName, String rollTransducerName ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._gyroDevice = gyroDevice;
        this._timestamp = timestamp;
        this._defaultHeadingTrueNorth = defaultHeadingTrueNorth;
        this._defaultMagneticTrueNorth = defaultMagneticTrueNorth;
        this._headingTrueNorthOffset = headingTrueNorthOffset;
        this._headingMagneticNorthOffset = headingMagneticNorthOffset;
        this._pitchTransducerName = pitchTransducerName;
        this._rollTransducerName = rollTransducerName;
    }

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
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getGyroDevice( ) {
        return _gyroDevice;
    }
    public void setGyroDevice( Guid value ) {
        if( !Comparer.equalsGuid( _gyroDevice, value ) ) {
            _gyroDevice = value;
            onPropertyChanged( );
        }
    }

    public DateTime getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( DateTime value ) {
        if( !Comparer.equalsDateTime( _timestamp, value ) ) {
            _timestamp = value;
            onPropertyChanged( );
        }
    }

    public double getDefaultHeadingTrueNorth( ) {
        return _defaultHeadingTrueNorth;
    }
    public void setDefaultHeadingTrueNorth( double value ) {
        if( !Comparer.equalsDouble( _defaultHeadingTrueNorth, value ) ) {
            _defaultHeadingTrueNorth = value;
            onPropertyChanged( );
        }
    }

    public double getDefaultMagneticTrueNorth( ) {
        return _defaultMagneticTrueNorth;
    }
    public void setDefaultMagneticTrueNorth( double value ) {
        if( !Comparer.equalsDouble( _defaultMagneticTrueNorth, value ) ) {
            _defaultMagneticTrueNorth = value;
            onPropertyChanged( );
        }
    }

    public double getHeadingTrueNorthOffset( ) {
        return _headingTrueNorthOffset;
    }
    public void setHeadingTrueNorthOffset( double value ) {
        if( !Comparer.equalsDouble( _headingTrueNorthOffset, value ) ) {
            _headingTrueNorthOffset = value;
            onPropertyChanged( );
        }
    }

    public double getHeadingMagneticNorthOffset( ) {
        return _headingMagneticNorthOffset;
    }
    public void setHeadingMagneticNorthOffset( double value ) {
        if( !Comparer.equalsDouble( _headingMagneticNorthOffset, value ) ) {
            _headingMagneticNorthOffset = value;
            onPropertyChanged( );
        }
    }

    public String getPitchTransducerName( ) {
        return _pitchTransducerName;
    }
    public void setPitchTransducerName( String value ) {
        if( !Comparer.equalsString( _pitchTransducerName, value ) ) {
            _pitchTransducerName = value;
            onPropertyChanged( );
        }
    }

    public String getRollTransducerName( ) {
        return _rollTransducerName;
    }
    public void setRollTransducerName( String value ) {
        if( !Comparer.equalsString( _rollTransducerName, value ) ) {
            _rollTransducerName = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( GyroDeviceConfigurationObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._gyroDevice = this._gyroDevice;
        targetObject._timestamp = this._timestamp;
        targetObject._defaultHeadingTrueNorth = this._defaultHeadingTrueNorth;
        targetObject._defaultMagneticTrueNorth = this._defaultMagneticTrueNorth;
        targetObject._headingTrueNorthOffset = this._headingTrueNorthOffset;
        targetObject._headingMagneticNorthOffset = this._headingMagneticNorthOffset;
        targetObject._pitchTransducerName = this._pitchTransducerName;
        targetObject._rollTransducerName = this._rollTransducerName;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (GyroDeviceConfigurationObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._gyroDevice, other._gyroDevice ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._defaultHeadingTrueNorth, other._defaultHeadingTrueNorth ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._defaultMagneticTrueNorth, other._defaultMagneticTrueNorth ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._headingTrueNorthOffset, other._headingTrueNorthOffset ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._headingMagneticNorthOffset, other._headingMagneticNorthOffset ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._pitchTransducerName, other._pitchTransducerName ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._rollTransducerName, other._rollTransducerName ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _gyroDevice );
        destination.writeDateTime( _timestamp );
        destination.writeDouble( _defaultHeadingTrueNorth );
        destination.writeDouble( _defaultMagneticTrueNorth );
        destination.writeDouble( _headingTrueNorthOffset );
        destination.writeDouble( _headingMagneticNorthOffset );
        destination.writeStringUtf8( _pitchTransducerName );
        destination.writeStringUtf8( _rollTransducerName );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _gyroDevice = source.readGuid( );
        _timestamp = source.readDateTime( );
        _defaultHeadingTrueNorth = source.readDouble( );
        _defaultMagneticTrueNorth = source.readDouble( );
        _headingTrueNorthOffset = source.readDouble( );
        _headingMagneticNorthOffset = source.readDouble( );
        _pitchTransducerName = source.readString( );
        _rollTransducerName = source.readString( );
    }

}
