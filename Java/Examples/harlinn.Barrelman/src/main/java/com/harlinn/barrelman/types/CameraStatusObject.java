package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraStatusObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.CameraStatus;

    private long _rowVersion = 0;
    private Guid _camera;
    private Guid _track;
    private DateTime _timestamp;
    private int _positionPanTiltMode = CameraPanTiltMode.Unknown;
    private double _panAngle = 0.0;
    private double _tiltAngle = 0.0;
    private int _positionFocalLengthMode = CameraFocalLengthMode.Unknown;
    private double _focalLength = 0.0;
    private int _panTiltMoveStatus = CameraMoveStatus.Unknown;
    private int _zoomMoveStatus = CameraMoveStatus.Unknown;
    private int _velocityPanTiltMode = CameraPanTiltMode.Unknown;
    private Double _panVelocity;
    private Double _tiltVelocity;
    private int _velocityFocalLengthMode = CameraFocalLengthMode.Unknown;
    private Double _zoomVelocity;
    private int _activeFeatures = CameraFeatures.None;
    private String _error = "";

    public CameraStatusObject( ) {
    }
    public CameraStatusObject( byte objectState, Guid id, long rowVersion, Guid camera, Guid track, DateTime timestamp, int positionPanTiltMode, double panAngle, double tiltAngle, int positionFocalLengthMode, double focalLength, int panTiltMoveStatus, int zoomMoveStatus, int velocityPanTiltMode, Double panVelocity, Double tiltVelocity, int velocityFocalLengthMode, Double zoomVelocity, int activeFeatures, String error ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._camera = camera;
        this._track = track;
        this._timestamp = timestamp;
        this._positionPanTiltMode = positionPanTiltMode;
        this._panAngle = panAngle;
        this._tiltAngle = tiltAngle;
        this._positionFocalLengthMode = positionFocalLengthMode;
        this._focalLength = focalLength;
        this._panTiltMoveStatus = panTiltMoveStatus;
        this._zoomMoveStatus = zoomMoveStatus;
        this._velocityPanTiltMode = velocityPanTiltMode;
        this._panVelocity = panVelocity;
        this._tiltVelocity = tiltVelocity;
        this._velocityFocalLengthMode = velocityFocalLengthMode;
        this._zoomVelocity = zoomVelocity;
        this._activeFeatures = activeFeatures;
        this._error = error;
    }

    @Override
    public int getObjectType( ) {
        return Kind.CameraStatus;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraStatusObject( );
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

    public Guid getCamera( ) {
        return _camera;
    }
    public void setCamera( Guid value ) {
        if( !Comparer.equalsGuid( _camera, value ) ) {
            _camera = value;
            onPropertyChanged( );
        }
    }

    public Guid getTrack( ) {
        return _track;
    }
    public void setTrack( Guid value ) {
        if( !Comparer.equalsNullableGuid( _track, value ) ) {
            _track = value;
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

    public int getPositionPanTiltMode( ) {
        return _positionPanTiltMode;
    }
    public void setPositionPanTiltMode( int value ) {
        if( !Comparer.equalsInt32( _positionPanTiltMode, value ) ) {
            _positionPanTiltMode = value;
            onPropertyChanged( );
        }
    }

    public double getPanAngle( ) {
        return _panAngle;
    }
    public void setPanAngle( double value ) {
        if( !Comparer.equalsDouble( _panAngle, value ) ) {
            _panAngle = value;
            onPropertyChanged( );
        }
    }

    public double getTiltAngle( ) {
        return _tiltAngle;
    }
    public void setTiltAngle( double value ) {
        if( !Comparer.equalsDouble( _tiltAngle, value ) ) {
            _tiltAngle = value;
            onPropertyChanged( );
        }
    }

    public int getPositionFocalLengthMode( ) {
        return _positionFocalLengthMode;
    }
    public void setPositionFocalLengthMode( int value ) {
        if( !Comparer.equalsInt32( _positionFocalLengthMode, value ) ) {
            _positionFocalLengthMode = value;
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

    public int getPanTiltMoveStatus( ) {
        return _panTiltMoveStatus;
    }
    public void setPanTiltMoveStatus( int value ) {
        if( !Comparer.equalsInt32( _panTiltMoveStatus, value ) ) {
            _panTiltMoveStatus = value;
            onPropertyChanged( );
        }
    }

    public int getZoomMoveStatus( ) {
        return _zoomMoveStatus;
    }
    public void setZoomMoveStatus( int value ) {
        if( !Comparer.equalsInt32( _zoomMoveStatus, value ) ) {
            _zoomMoveStatus = value;
            onPropertyChanged( );
        }
    }

    public int getVelocityPanTiltMode( ) {
        return _velocityPanTiltMode;
    }
    public void setVelocityPanTiltMode( int value ) {
        if( !Comparer.equalsInt32( _velocityPanTiltMode, value ) ) {
            _velocityPanTiltMode = value;
            onPropertyChanged( );
        }
    }

    public Double getPanVelocity( ) {
        return _panVelocity;
    }
    public void setPanVelocity( Double value ) {
        if( !Comparer.equalsNullableDouble( _panVelocity, value ) ) {
            _panVelocity = value;
            onPropertyChanged( );
        }
    }

    public Double getTiltVelocity( ) {
        return _tiltVelocity;
    }
    public void setTiltVelocity( Double value ) {
        if( !Comparer.equalsNullableDouble( _tiltVelocity, value ) ) {
            _tiltVelocity = value;
            onPropertyChanged( );
        }
    }

    public int getVelocityFocalLengthMode( ) {
        return _velocityFocalLengthMode;
    }
    public void setVelocityFocalLengthMode( int value ) {
        if( !Comparer.equalsInt32( _velocityFocalLengthMode, value ) ) {
            _velocityFocalLengthMode = value;
            onPropertyChanged( );
        }
    }

    public Double getZoomVelocity( ) {
        return _zoomVelocity;
    }
    public void setZoomVelocity( Double value ) {
        if( !Comparer.equalsNullableDouble( _zoomVelocity, value ) ) {
            _zoomVelocity = value;
            onPropertyChanged( );
        }
    }

    public int getActiveFeatures( ) {
        return _activeFeatures;
    }
    public void setActiveFeatures( int value ) {
        if( !Comparer.equalsInt32( _activeFeatures, value ) ) {
            _activeFeatures = value;
            onPropertyChanged( );
        }
    }

    public String getError( ) {
        return _error;
    }
    public void setError( String value ) {
        if( !Comparer.equalsString( _error, value ) ) {
            _error = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( CameraStatusObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._camera = this._camera;
        targetObject._track = this._track;
        targetObject._timestamp = this._timestamp;
        targetObject._positionPanTiltMode = this._positionPanTiltMode;
        targetObject._panAngle = this._panAngle;
        targetObject._tiltAngle = this._tiltAngle;
        targetObject._positionFocalLengthMode = this._positionFocalLengthMode;
        targetObject._focalLength = this._focalLength;
        targetObject._panTiltMoveStatus = this._panTiltMoveStatus;
        targetObject._zoomMoveStatus = this._zoomMoveStatus;
        targetObject._velocityPanTiltMode = this._velocityPanTiltMode;
        targetObject._panVelocity = this._panVelocity;
        targetObject._tiltVelocity = this._tiltVelocity;
        targetObject._velocityFocalLengthMode = this._velocityFocalLengthMode;
        targetObject._zoomVelocity = this._zoomVelocity;
        targetObject._activeFeatures = this._activeFeatures;
        targetObject._error = this._error;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (CameraStatusObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._camera, other._camera ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._track, other._track ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._positionPanTiltMode, other._positionPanTiltMode ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._panAngle, other._panAngle ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._tiltAngle, other._tiltAngle ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._positionFocalLengthMode, other._positionFocalLengthMode ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._focalLength, other._focalLength ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._panTiltMoveStatus, other._panTiltMoveStatus ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._zoomMoveStatus, other._zoomMoveStatus ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._velocityPanTiltMode, other._velocityPanTiltMode ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._panVelocity, other._panVelocity ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._tiltVelocity, other._tiltVelocity ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._velocityFocalLengthMode, other._velocityFocalLengthMode ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._zoomVelocity, other._zoomVelocity ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._activeFeatures, other._activeFeatures ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._error, other._error ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _camera );
        destination.writeNullableGuid( _track );
        destination.writeDateTime( _timestamp );
        destination.writeInt32( _positionPanTiltMode );
        destination.writeDouble( _panAngle );
        destination.writeDouble( _tiltAngle );
        destination.writeInt32( _positionFocalLengthMode );
        destination.writeDouble( _focalLength );
        destination.writeInt32( _panTiltMoveStatus );
        destination.writeInt32( _zoomMoveStatus );
        destination.writeInt32( _velocityPanTiltMode );
        destination.writeNullableDouble( _panVelocity );
        destination.writeNullableDouble( _tiltVelocity );
        destination.writeInt32( _velocityFocalLengthMode );
        destination.writeNullableDouble( _zoomVelocity );
        destination.writeInt32( _activeFeatures );
        destination.writeStringUtf8( _error );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _camera = source.readGuid( );
        _track = source.readNullableGuid( );
        _timestamp = source.readDateTime( );
        _positionPanTiltMode = source.readInt32( );
        _panAngle = source.readDouble( );
        _tiltAngle = source.readDouble( );
        _positionFocalLengthMode = source.readInt32( );
        _focalLength = source.readDouble( );
        _panTiltMoveStatus = source.readInt32( );
        _zoomMoveStatus = source.readInt32( );
        _velocityPanTiltMode = source.readInt32( );
        _panVelocity = source.readNullableDouble( );
        _tiltVelocity = source.readNullableDouble( );
        _velocityFocalLengthMode = source.readInt32( );
        _zoomVelocity = source.readNullableDouble( );
        _activeFeatures = source.readInt32( );
        _error = source.readString( );
    }

}
