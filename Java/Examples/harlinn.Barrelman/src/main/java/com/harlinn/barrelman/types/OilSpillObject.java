package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class OilSpillObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _oilSpillDetector;
    private DateTime _timestamp;
    private double _oilArea = 0.0;
    private byte[] _shape = new byte[0];
    private byte[] _bSI = new byte[0];
    private byte[] _oil = new byte[0];
    private byte[] _trace = new byte[0];

    @Override
    public int getObjectType( ) {
        return Kind.OilSpill;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new OilSpillObject( );
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

    public Guid getOilSpillDetector( ) {
        return _oilSpillDetector;
    }
    public void setOilSpillDetector( Guid value ) {
        if( _oilSpillDetector != value ) {
            this._oilSpillDetector = value;
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

    public double getOilArea( ) {
        return _oilArea;
    }
    public void setOilArea( double value ) {
        if( _oilArea != value ) {
            this._oilArea = value;
            onPropertyChanged( );
        }
    }

    public byte[] getShape( ) {
        return _shape;
    }
    public void setShape( byte[] value ) {
        if( _shape != value ) {
            this._shape = value;
            onPropertyChanged( );
        }
    }

    public byte[] getBSI( ) {
        return _bSI;
    }
    public void setBSI( byte[] value ) {
        if( _bSI != value ) {
            this._bSI = value;
            onPropertyChanged( );
        }
    }

    public byte[] getOil( ) {
        return _oil;
    }
    public void setOil( byte[] value ) {
        if( _oil != value ) {
            this._oil = value;
            onPropertyChanged( );
        }
    }

    public byte[] getTrace( ) {
        return _trace;
    }
    public void setTrace( byte[] value ) {
        if( _trace != value ) {
            this._trace = value;
            onPropertyChanged( );
        }
    }


}
