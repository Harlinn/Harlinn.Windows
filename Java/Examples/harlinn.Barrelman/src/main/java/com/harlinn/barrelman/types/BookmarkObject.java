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
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getView( ) {
        return _view;
    }
    public void setView( Guid value ) {
        if( _view != value ) {
            this._view = value;
            onPropertyChanged( );
        }
    }

    public String getName( ) {
        return _name;
    }
    public void setName( String value ) {
        if( _name != value ) {
            this._name = value;
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

    public double getLatitude( ) {
        return _latitude;
    }
    public void setLatitude( double value ) {
        if( _latitude != value ) {
            this._latitude = value;
            onPropertyChanged( );
        }
    }

    public double getLongitude( ) {
        return _longitude;
    }
    public void setLongitude( double value ) {
        if( _longitude != value ) {
            this._longitude = value;
            onPropertyChanged( );
        }
    }

    public double getZoomLevel( ) {
        return _zoomLevel;
    }
    public void setZoomLevel( double value ) {
        if( _zoomLevel != value ) {
            this._zoomLevel = value;
            onPropertyChanged( );
        }
    }


}
