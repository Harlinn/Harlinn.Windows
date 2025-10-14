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
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getRadar( ) {
        return _radar;
    }
    public void setRadar( Guid value ) {
        if( !Comparer.equalsGuid( _radar, value ) ) {
            _radar = value;
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

    public int getCount( ) {
        return _count;
    }
    public void setCount( int value ) {
        if( !Comparer.equalsInt32( _count, value ) ) {
            _count = value;
            onPropertyChanged( );
        }
    }

    public byte[] getTable( ) {
        return _table;
    }
    public void setTable( byte[] value ) {
        if( !Comparer.equalsUInt8Array( _table, value ) ) {
            _table = value != null ? value.clone() : value;;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _radar );
        destination.writeDateTime( _timestamp );
        destination.writeInt32( _count );
        destination.writeUInt8Array( _table );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _radar = source.readGuid( );
        _timestamp = source.readDateTime( );
        _count = source.readInt32( );
        _table = source.readUInt8Array( );
    }

}
