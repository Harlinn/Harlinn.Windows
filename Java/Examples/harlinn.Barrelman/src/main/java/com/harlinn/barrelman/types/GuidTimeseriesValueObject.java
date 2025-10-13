package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GuidTimeseriesValueObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _timeseries;
    private DateTime _timestamp;
    private Guid _value;

    @Override
    public int getObjectType( ) {
        return Kind.GuidTimeseriesValue;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new GuidTimeseriesValueObject( );
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

    public Guid getTimeseries( ) {
        return _timeseries;
    }
    public void setTimeseries( Guid value ) {
        if( _timeseries != value ) {
            this._timeseries = value;
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

    public Guid getValue( ) {
        return _value;
    }
    public void setValue( Guid value ) {
        if( _value != value ) {
            this._value = value;
            onPropertyChanged( );
        }
    }


}
