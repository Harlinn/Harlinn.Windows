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
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getParameters( ) {
        return _parameters;
    }
    public void setParameters( Guid value ) {
        if( _parameters != value ) {
            this._parameters = value;
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

    public boolean getUseNaivePredictor( ) {
        return _useNaivePredictor;
    }
    public void setUseNaivePredictor( boolean value ) {
        if( _useNaivePredictor != value ) {
            this._useNaivePredictor = value;
            onPropertyChanged( );
        }
    }

    public int getNumberOfPoints( ) {
        return _numberOfPoints;
    }
    public void setNumberOfPoints( int value ) {
        if( _numberOfPoints != value ) {
            this._numberOfPoints = value;
            onPropertyChanged( );
        }
    }

    public int getWindowSize( ) {
        return _windowSize;
    }
    public void setWindowSize( int value ) {
        if( _windowSize != value ) {
            this._windowSize = value;
            onPropertyChanged( );
        }
    }

    public int getStabilizeCount( ) {
        return _stabilizeCount;
    }
    public void setStabilizeCount( int value ) {
        if( _stabilizeCount != value ) {
            this._stabilizeCount = value;
            onPropertyChanged( );
        }
    }

    public int getMaxBadPoints( ) {
        return _maxBadPoints;
    }
    public void setMaxBadPoints( int value ) {
        if( _maxBadPoints != value ) {
            this._maxBadPoints = value;
            onPropertyChanged( );
        }
    }

    public int getModelType( ) {
        return _modelType;
    }
    public void setModelType( int value ) {
        if( _modelType != value ) {
            this._modelType = value;
            onPropertyChanged( );
        }
    }

    public double getSigmaR( ) {
        return _sigmaR;
    }
    public void setSigmaR( double value ) {
        if( _sigmaR != value ) {
            this._sigmaR = value;
            onPropertyChanged( );
        }
    }

    public double getSigmaAcc( ) {
        return _sigmaAcc;
    }
    public void setSigmaAcc( double value ) {
        if( _sigmaAcc != value ) {
            this._sigmaAcc = value;
            onPropertyChanged( );
        }
    }

    public double getTauVel( ) {
        return _tauVel;
    }
    public void setTauVel( double value ) {
        if( _tauVel != value ) {
            this._tauVel = value;
            onPropertyChanged( );
        }
    }

    public double getTauAcc( ) {
        return _tauAcc;
    }
    public void setTauAcc( double value ) {
        if( _tauAcc != value ) {
            this._tauAcc = value;
            onPropertyChanged( );
        }
    }

    public double getDeltaRMin( ) {
        return _deltaRMin;
    }
    public void setDeltaRMin( double value ) {
        if( _deltaRMin != value ) {
            this._deltaRMin = value;
            onPropertyChanged( );
        }
    }

    public double getDeltaVMax( ) {
        return _deltaVMax;
    }
    public void setDeltaVMax( double value ) {
        if( _deltaVMax != value ) {
            this._deltaVMax = value;
            onPropertyChanged( );
        }
    }

    public double getDeltaAMax( ) {
        return _deltaAMax;
    }
    public void setDeltaAMax( double value ) {
        if( _deltaAMax != value ) {
            this._deltaAMax = value;
            onPropertyChanged( );
        }
    }


}
