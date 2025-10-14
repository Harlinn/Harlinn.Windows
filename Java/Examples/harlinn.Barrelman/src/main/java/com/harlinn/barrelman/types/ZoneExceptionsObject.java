package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ZoneExceptionsObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _zone;
    private DateTime _timestamp;

    @Override
    public int getObjectType( ) {
        return Kind.ZoneExceptions;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ZoneExceptionsObject( );
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

    public Guid getZone( ) {
        return _zone;
    }
    public void setZone( Guid value ) {
        if( !Comparer.equalsGuid( _zone, value ) ) {
            _zone = value;
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



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _zone );
        destination.writeDateTime( _timestamp );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _zone = source.readGuid( );
        _timestamp = source.readDateTime( );
    }

}
