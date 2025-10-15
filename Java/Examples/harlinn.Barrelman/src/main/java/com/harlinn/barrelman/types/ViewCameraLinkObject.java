package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ViewCameraLinkObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _view;
    private Guid _camera;
    private DateTime _start;
    private DateTime _end;

    @Override
    public int getObjectType( ) {
        return Kind.ViewCameraLink;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ViewCameraLinkObject( );
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

    public Guid getCamera( ) {
        return _camera;
    }
    public void setCamera( Guid value ) {
        if( !Comparer.equalsGuid( _camera, value ) ) {
            _camera = value;
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
        var targetObject = ( ViewCameraLinkObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._view = this._view;
        targetObject._camera = this._camera;
        targetObject._start = this._start;
        targetObject._end = this._end;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (ViewCameraLinkObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._view, other._view ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._camera, other._camera ) ) {
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
        destination.writeGuid( _camera );
        destination.writeDateTime( _start );
        destination.writeNullableDateTime( _end );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _view = source.readGuid( );
        _camera = source.readGuid( );
        _start = source.readDateTime( );
        _end = source.readNullableDateTime( );
    }

}
