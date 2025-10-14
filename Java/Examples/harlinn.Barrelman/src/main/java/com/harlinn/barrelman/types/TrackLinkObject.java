package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class TrackLinkObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _primary;
    private Guid _secondary;
    private DateTime _start;
    private DateTime _end;

    @Override
    public int getObjectType( ) {
        return Kind.TrackLink;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new TrackLinkObject( );
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

    public Guid getPrimary( ) {
        return _primary;
    }
    public void setPrimary( Guid value ) {
        if( !Comparer.equalsGuid( _primary, value ) ) {
            _primary = value;
            onPropertyChanged( );
        }
    }

    public Guid getSecondary( ) {
        return _secondary;
    }
    public void setSecondary( Guid value ) {
        if( !Comparer.equalsGuid( _secondary, value ) ) {
            _secondary = value;
            onPropertyChanged( );
        }
    }

    public DateTime getStart( ) {
        return _start;
    }
    public void setStart( DateTime value ) {
        if( !Comparer.equalsDateTime( _start, value ) ) {
            _start = value;
            onPropertyChanged( );
        }
    }

    public DateTime getEnd( ) {
        return _end;
    }
    public void setEnd( DateTime value ) {
        if( !Comparer.equalsNullableDateTime( _end, value ) ) {
            _end = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _primary );
        destination.writeGuid( _secondary );
        destination.writeDateTime( _start );
        destination.writeNullableDateTime( _end );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _primary = source.readGuid( );
        _secondary = source.readGuid( );
        _start = source.readDateTime( );
        _end = source.readNullableDateTime( );
    }

}
