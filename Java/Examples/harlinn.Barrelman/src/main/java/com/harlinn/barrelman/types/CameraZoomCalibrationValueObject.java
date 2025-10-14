package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraZoomCalibrationValueObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _zoomCalibration;
    private double _focalLength = 0.0;
    private double _focalLengthOffset = 0.0;

    @Override
    public int getObjectType( ) {
        return Kind.CameraZoomCalibrationValue;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraZoomCalibrationValueObject( );
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

    public Guid getZoomCalibration( ) {
        return _zoomCalibration;
    }
    public void setZoomCalibration( Guid value ) {
        if( !Comparer.equalsGuid( _zoomCalibration, value ) ) {
            _zoomCalibration = value;
            onPropertyChanged( );
        }
    }

    public double getFocalLength( ) {
        return _focalLength;
    }
    public void setFocalLength( double value ) {
        if( !Comparer.equalsDouble( _focalLength, value ) ) {
            _focalLength = value;
            onPropertyChanged( );
        }
    }

    public double getFocalLengthOffset( ) {
        return _focalLengthOffset;
    }
    public void setFocalLengthOffset( double value ) {
        if( !Comparer.equalsDouble( _focalLengthOffset, value ) ) {
            _focalLengthOffset = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _zoomCalibration );
        destination.writeDouble( _focalLength );
        destination.writeDouble( _focalLengthOffset );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _zoomCalibration = source.readGuid( );
        _focalLength = source.readDouble( );
        _focalLengthOffset = source.readDouble( );
    }

}
