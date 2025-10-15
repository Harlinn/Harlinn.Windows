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
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( TrackLinkObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._primary = this._primary;
        targetObject._secondary = this._secondary;
        targetObject._start = this._start;
        targetObject._end = this._end;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (TrackLinkObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._primary, other._primary ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._secondary, other._secondary ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._start, other._start ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDateTime( this._end, other._end ) ) {
            return false;
        }
        return true;
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
