package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class TrackerFilterParametersConfigurationObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _parameters;
    private DateTime _timestamp;
    private boolean _useNaivePredictor = false;
    private int _numberOfPoints = 0;
    private int _windowSize = 0;
    private int _stabilizeCount = 0;
    private int _maxBadPoints = 0;
    private int _modelType = TrackerFilterModelType.Unknown;
    private double _sigmaR = 0.0;
    private double _sigmaAcc = 0.0;
    private double _tauVel = 0.0;
    private double _tauAcc = 0.0;
    private double _deltaRMin = 0.0;
    private double _deltaVMax = 0.0;
    private double _deltaAMax = 0.0;

    @Override
    public int getObjectType( ) {
        return Kind.TrackerFilterParametersConfiguration;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new TrackerFilterParametersConfigurationObject( );
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

    public Guid getParameters( ) {
        return _parameters;
    }
    public void setParameters( Guid value ) {
        if( !Comparer.equalsGuid( _parameters, value ) ) {
            _parameters = value;
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

    public boolean getUseNaivePredictor( ) {
        return _useNaivePredictor;
    }
    public void setUseNaivePredictor( boolean value ) {
        if( !Comparer.equalsBoolean( _useNaivePredictor, value ) ) {
            _useNaivePredictor = value;
            onPropertyChanged( );
        }
    }

    public int getNumberOfPoints( ) {
        return _numberOfPoints;
    }
    public void setNumberOfPoints( int value ) {
        if( !Comparer.equalsInt32( _numberOfPoints, value ) ) {
            _numberOfPoints = value;
            onPropertyChanged( );
        }
    }

    public int getWindowSize( ) {
        return _windowSize;
    }
    public void setWindowSize( int value ) {
        if( !Comparer.equalsInt32( _windowSize, value ) ) {
            _windowSize = value;
            onPropertyChanged( );
        }
    }

    public int getStabilizeCount( ) {
        return _stabilizeCount;
    }
    public void setStabilizeCount( int value ) {
        if( !Comparer.equalsInt32( _stabilizeCount, value ) ) {
            _stabilizeCount = value;
            onPropertyChanged( );
        }
    }

    public int getMaxBadPoints( ) {
        return _maxBadPoints;
    }
    public void setMaxBadPoints( int value ) {
        if( !Comparer.equalsInt32( _maxBadPoints, value ) ) {
            _maxBadPoints = value;
            onPropertyChanged( );
        }
    }

    public int getModelType( ) {
        return _modelType;
    }
    public void setModelType( int value ) {
        if( !Comparer.equalsInt32( _modelType, value ) ) {
            _modelType = value;
            onPropertyChanged( );
        }
    }

    public double getSigmaR( ) {
        return _sigmaR;
    }
    public void setSigmaR( double value ) {
        if( !Comparer.equalsDouble( _sigmaR, value ) ) {
            _sigmaR = value;
            onPropertyChanged( );
        }
    }

    public double getSigmaAcc( ) {
        return _sigmaAcc;
    }
    public void setSigmaAcc( double value ) {
        if( !Comparer.equalsDouble( _sigmaAcc, value ) ) {
            _sigmaAcc = value;
            onPropertyChanged( );
        }
    }

    public double getTauVel( ) {
        return _tauVel;
    }
    public void setTauVel( double value ) {
        if( !Comparer.equalsDouble( _tauVel, value ) ) {
            _tauVel = value;
            onPropertyChanged( );
        }
    }

    public double getTauAcc( ) {
        return _tauAcc;
    }
    public void setTauAcc( double value ) {
        if( !Comparer.equalsDouble( _tauAcc, value ) ) {
            _tauAcc = value;
            onPropertyChanged( );
        }
    }

    public double getDeltaRMin( ) {
        return _deltaRMin;
    }
    public void setDeltaRMin( double value ) {
        if( !Comparer.equalsDouble( _deltaRMin, value ) ) {
            _deltaRMin = value;
            onPropertyChanged( );
        }
    }

    public double getDeltaVMax( ) {
        return _deltaVMax;
    }
    public void setDeltaVMax( double value ) {
        if( !Comparer.equalsDouble( _deltaVMax, value ) ) {
            _deltaVMax = value;
            onPropertyChanged( );
        }
    }

    public double getDeltaAMax( ) {
        return _deltaAMax;
    }
    public void setDeltaAMax( double value ) {
        if( !Comparer.equalsDouble( _deltaAMax, value ) ) {
            _deltaAMax = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( TrackerFilterParametersConfigurationObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._parameters = this._parameters;
        targetObject._timestamp = this._timestamp;
        targetObject._useNaivePredictor = this._useNaivePredictor;
        targetObject._numberOfPoints = this._numberOfPoints;
        targetObject._windowSize = this._windowSize;
        targetObject._stabilizeCount = this._stabilizeCount;
        targetObject._maxBadPoints = this._maxBadPoints;
        targetObject._modelType = this._modelType;
        targetObject._sigmaR = this._sigmaR;
        targetObject._sigmaAcc = this._sigmaAcc;
        targetObject._tauVel = this._tauVel;
        targetObject._tauAcc = this._tauAcc;
        targetObject._deltaRMin = this._deltaRMin;
        targetObject._deltaVMax = this._deltaVMax;
        targetObject._deltaAMax = this._deltaAMax;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (TrackerFilterParametersConfigurationObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._parameters, other._parameters ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._useNaivePredictor, other._useNaivePredictor ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._numberOfPoints, other._numberOfPoints ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._windowSize, other._windowSize ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._stabilizeCount, other._stabilizeCount ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._maxBadPoints, other._maxBadPoints ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._modelType, other._modelType ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._sigmaR, other._sigmaR ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._sigmaAcc, other._sigmaAcc ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._tauVel, other._tauVel ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._tauAcc, other._tauAcc ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._deltaRMin, other._deltaRMin ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._deltaVMax, other._deltaVMax ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._deltaAMax, other._deltaAMax ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _parameters );
        destination.writeDateTime( _timestamp );
        destination.writeBoolean( _useNaivePredictor );
        destination.writeInt32( _numberOfPoints );
        destination.writeInt32( _windowSize );
        destination.writeInt32( _stabilizeCount );
        destination.writeInt32( _maxBadPoints );
        destination.writeInt32( _modelType );
        destination.writeDouble( _sigmaR );
        destination.writeDouble( _sigmaAcc );
        destination.writeDouble( _tauVel );
        destination.writeDouble( _tauAcc );
        destination.writeDouble( _deltaRMin );
        destination.writeDouble( _deltaVMax );
        destination.writeDouble( _deltaAMax );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _parameters = source.readGuid( );
        _timestamp = source.readDateTime( );
        _useNaivePredictor = source.readBoolean( );
        _numberOfPoints = source.readInt32( );
        _windowSize = source.readInt32( );
        _stabilizeCount = source.readInt32( );
        _maxBadPoints = source.readInt32( );
        _modelType = source.readInt32( );
        _sigmaR = source.readDouble( );
        _sigmaAcc = source.readDouble( );
        _tauVel = source.readDouble( );
        _tauAcc = source.readDouble( );
        _deltaRMin = source.readDouble( );
        _deltaVMax = source.readDouble( );
        _deltaAMax = source.readDouble( );
    }

}
