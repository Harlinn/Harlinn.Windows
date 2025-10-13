package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class Int16TimeseriesValueObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _timeseries;
    private DateTime _timestamp;
    private Short _value;

    @Override
    public int getObjectType( ) {
        return Kind.Int16TimeseriesValue;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new Int16TimeseriesValueObject( );
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

    public Short getValue( ) {
        return _value;
    }
    public void setValue( Short value ) {
        if( _value != value ) {
            this._value = value;
            onPropertyChanged( );
        }
    }


}
