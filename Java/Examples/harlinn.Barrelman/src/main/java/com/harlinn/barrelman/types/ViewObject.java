package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ViewObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private String _name = "";
    private Guid _latitudeTimeseries;
    private Guid _longitudeTimeseries;
    private Guid _zoomLevelTimeseries;

    @Override
    public int getObjectType( ) {
        return Kind.View;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ViewObject( );
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

    public String getName( ) {
        return _name;
    }
    public void setName( String value ) {
        if( _name != value ) {
            this._name = value;
            onPropertyChanged( );
        }
    }

    public Guid getLatitudeTimeseries( ) {
        return _latitudeTimeseries;
    }
    public void setLatitudeTimeseries( Guid value ) {
        if( _latitudeTimeseries != value ) {
            this._latitudeTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getLongitudeTimeseries( ) {
        return _longitudeTimeseries;
    }
    public void setLongitudeTimeseries( Guid value ) {
        if( _longitudeTimeseries != value ) {
            this._longitudeTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getZoomLevelTimeseries( ) {
        return _zoomLevelTimeseries;
    }
    public void setZoomLevelTimeseries( Guid value ) {
        if( _zoomLevelTimeseries != value ) {
            this._zoomLevelTimeseries = value;
            onPropertyChanged( );
        }
    }


}
