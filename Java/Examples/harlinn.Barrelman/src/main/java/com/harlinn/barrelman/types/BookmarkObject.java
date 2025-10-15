package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class BookmarkObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _view;
    private String _name = "";
    private DateTime _timestamp;
    private double _latitude = 0.0;
    private double _longitude = 0.0;
    private double _zoomLevel = 0.0;

    @Override
    public int getObjectType( ) {
        return Kind.Bookmark;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new BookmarkObject( );
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

    public String getName( ) {
        return _name;
    }
    public void setName( String value ) {
        if( !Comparer.equalsString( _name, value ) ) {
            _name = value;
            onPropertyChanged( );
        }
    }

    public DateTime getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( DateTime value ) {
        if( !Comparer.equalsNullableDateTime( _timestamp, value ) ) {
            _timestamp = value;
            onPropertyChanged( );
        }
    }

    public double getLatitude( ) {
        return _latitude;
    }
    public void setLatitude( double value ) {
        if( !Comparer.equalsDouble( _latitude, value ) ) {
            _latitude = value;
            onPropertyChanged( );
        }
    }

    public double getLongitude( ) {
        return _longitude;
    }
    public void setLongitude( double value ) {
        if( !Comparer.equalsDouble( _longitude, value ) ) {
            _longitude = value;
            onPropertyChanged( );
        }
    }

    public double getZoomLevel( ) {
        return _zoomLevel;
    }
    public void setZoomLevel( double value ) {
        if( !Comparer.equalsDouble( _zoomLevel, value ) ) {
            _zoomLevel = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( BookmarkObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._view = this._view;
        targetObject._name = this._name;
        targetObject._timestamp = this._timestamp;
        targetObject._latitude = this._latitude;
        targetObject._longitude = this._longitude;
        targetObject._zoomLevel = this._zoomLevel;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (BookmarkObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._view, other._view ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._name, other._name ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._latitude, other._latitude ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._longitude, other._longitude ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._zoomLevel, other._zoomLevel ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _view );
        destination.writeStringUtf8( _name );
        destination.writeNullableDateTime( _timestamp );
        destination.writeDouble( _latitude );
        destination.writeDouble( _longitude );
        destination.writeDouble( _zoomLevel );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _view = source.readGuid( );
        _name = source.readString( );
        _timestamp = source.readNullableDateTime( );
        _latitude = source.readDouble( );
        _longitude = source.readDouble( );
        _zoomLevel = source.readDouble( );
    }

}
