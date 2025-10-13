package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadarRawTrackTableObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _radar;
    private DateTime _timestamp;
    private int _count = 0;
    private byte[] _table = new byte[0];

    @Override
    public int getObjectType( ) {
        return Kind.RadarRawTrackTable;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadarRawTrackTableObject( );
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

    public Guid getRadar( ) {
        return _radar;
    }
    public void setRadar( Guid value ) {
        if( _radar != value ) {
            this._radar = value;
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

    public int getCount( ) {
        return _count;
    }
    public void setCount( int value ) {
        if( _count != value ) {
            this._count = value;
            onPropertyChanged( );
        }
    }

    public byte[] getTable( ) {
        return _table;
    }
    public void setTable( byte[] value ) {
        if( _table != value ) {
            this._table = value;
            onPropertyChanged( );
        }
    }


}
