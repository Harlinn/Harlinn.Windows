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
