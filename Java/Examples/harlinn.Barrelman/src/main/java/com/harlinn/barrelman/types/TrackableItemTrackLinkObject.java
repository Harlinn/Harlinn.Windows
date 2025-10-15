package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class TrackableItemTrackLinkObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _item;
    private Guid _track;
    private DateTime _start;
    private DateTime _end;

    @Override
    public int getObjectType( ) {
        return Kind.TrackableItemTrackLink;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new TrackableItemTrackLinkObject( );
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

    public Guid getItem( ) {
        return _item;
    }
    public void setItem( Guid value ) {
        if( !Comparer.equalsGuid( _item, value ) ) {
            _item = value;
            onPropertyChanged( );
        }
    }

    public Guid getTrack( ) {
        return _track;
    }
    public void setTrack( Guid value ) {
        if( !Comparer.equalsGuid( _track, value ) ) {
            _track = value;
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
        var targetObject = ( TrackableItemTrackLinkObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._item = this._item;
        targetObject._track = this._track;
        targetObject._start = this._start;
        targetObject._end = this._end;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (TrackableItemTrackLinkObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._item, other._item ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._track, other._track ) ) {
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
        destination.writeGuid( _item );
        destination.writeGuid( _track );
        destination.writeDateTime( _start );
        destination.writeNullableDateTime( _end );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _item = source.readGuid( );
        _track = source.readGuid( );
        _start = source.readDateTime( );
        _end = source.readNullableDateTime( );
    }

}
