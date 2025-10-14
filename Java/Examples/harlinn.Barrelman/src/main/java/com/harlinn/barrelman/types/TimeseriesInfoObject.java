package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class TimeseriesInfoObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private DateTime _firstTimestamp;
    private DateTime _lastTimestamp;
    private long _count = 0;

    @Override
    public int getObjectType( ) {
        return Kind.TimeseriesInfo;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new TimeseriesInfoObject( );
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

    public DateTime getFirstTimestamp( ) {
        return _firstTimestamp;
    }
    public void setFirstTimestamp( DateTime value ) {
        if( !Comparer.equalsNullableDateTime( _firstTimestamp, value ) ) {
            _firstTimestamp = value;
            onPropertyChanged( );
        }
    }

    public DateTime getLastTimestamp( ) {
        return _lastTimestamp;
    }
    public void setLastTimestamp( DateTime value ) {
        if( !Comparer.equalsNullableDateTime( _lastTimestamp, value ) ) {
            _lastTimestamp = value;
            onPropertyChanged( );
        }
    }

    public long getCount( ) {
        return _count;
    }
    public void setCount( long value ) {
        if( !Comparer.equalsInt64( _count, value ) ) {
            _count = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeNullableDateTime( _firstTimestamp );
        destination.writeNullableDateTime( _lastTimestamp );
        destination.writeInt64( _count );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _firstTimestamp = source.readNullableDateTime( );
        _lastTimestamp = source.readNullableDateTime( );
        _count = source.readInt64( );
    }

}
