package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ViewObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.View;

    private long _rowVersion = 0;
    private String _name = "";
    private Guid _latitudeTimeseries;
    private Guid _longitudeTimeseries;
    private Guid _zoomLevelTimeseries;

    public ViewObject( ) {
    }
    public ViewObject( byte objectState, Guid id, long rowVersion, String name, Guid latitudeTimeseries, Guid longitudeTimeseries, Guid zoomLevelTimeseries ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._name = name;
        this._latitudeTimeseries = latitudeTimeseries;
        this._longitudeTimeseries = longitudeTimeseries;
        this._zoomLevelTimeseries = zoomLevelTimeseries;
    }

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
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
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

    public Guid getLatitudeTimeseries( ) {
        return _latitudeTimeseries;
    }
    public void setLatitudeTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _latitudeTimeseries, value ) ) {
            _latitudeTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getLongitudeTimeseries( ) {
        return _longitudeTimeseries;
    }
    public void setLongitudeTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _longitudeTimeseries, value ) ) {
            _longitudeTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getZoomLevelTimeseries( ) {
        return _zoomLevelTimeseries;
    }
    public void setZoomLevelTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _zoomLevelTimeseries, value ) ) {
            _zoomLevelTimeseries = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( ViewObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._name = this._name;
        targetObject._latitudeTimeseries = this._latitudeTimeseries;
        targetObject._longitudeTimeseries = this._longitudeTimeseries;
        targetObject._zoomLevelTimeseries = this._zoomLevelTimeseries;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (ViewObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._name, other._name ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._latitudeTimeseries, other._latitudeTimeseries ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._longitudeTimeseries, other._longitudeTimeseries ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._zoomLevelTimeseries, other._zoomLevelTimeseries ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeStringUtf8( _name );
        destination.writeNullableGuid( _latitudeTimeseries );
        destination.writeNullableGuid( _longitudeTimeseries );
        destination.writeNullableGuid( _zoomLevelTimeseries );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _name = source.readString( );
        _latitudeTimeseries = source.readNullableGuid( );
        _longitudeTimeseries = source.readNullableGuid( );
        _zoomLevelTimeseries = source.readNullableGuid( );
    }

}
