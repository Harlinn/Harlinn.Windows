package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ViewTrackerLinkObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.ViewTrackerLink;

    private long _rowVersion = 0;
    private Guid _view;
    private Guid _tracker;
    private DateTime _start;
    private DateTime _end;

    public ViewTrackerLinkObject( ) {
    }
    public ViewTrackerLinkObject( byte objectState, Guid id, long rowVersion, Guid view, Guid tracker, DateTime start, DateTime end ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._view = view;
        this._tracker = tracker;
        this._start = start;
        this._end = end;
    }

    @Override
    public int getObjectType( ) {
        return Kind.ViewTrackerLink;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ViewTrackerLinkObject( );
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

    public Guid getView( ) {
        return _view;
    }
    public void setView( Guid value ) {
        if( !Comparer.equalsGuid( _view, value ) ) {
            _view = value;
            onPropertyChanged( );
        }
    }

    public Guid getTracker( ) {
        return _tracker;
    }
    public void setTracker( Guid value ) {
        if( !Comparer.equalsGuid( _tracker, value ) ) {
            _tracker = value;
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
        var targetObject = ( ViewTrackerLinkObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._view = this._view;
        targetObject._tracker = this._tracker;
        targetObject._start = this._start;
        targetObject._end = this._end;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (ViewTrackerLinkObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._view, other._view ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._tracker, other._tracker ) ) {
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
        destination.writeGuid( _view );
        destination.writeGuid( _tracker );
        destination.writeDateTime( _start );
        destination.writeNullableDateTime( _end );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _view = source.readGuid( );
        _tracker = source.readGuid( );
        _start = source.readDateTime( );
        _end = source.readNullableDateTime( );
    }

}
