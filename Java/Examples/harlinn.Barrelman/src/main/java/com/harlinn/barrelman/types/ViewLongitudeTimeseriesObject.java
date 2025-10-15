package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ViewLongitudeTimeseriesObject extends DoubleTimeseriesObject {

    private Guid _view;

    @Override
    public int getObjectType( ) {
        return Kind.ViewLongitudeTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ViewLongitudeTimeseriesObject( );
    }

    public Guid getView( ) {
        return _view;
    }
    public void setView( Guid value ) {
        if( !Comparer.equalsNullableGuid( _view, value ) ) {
            _view = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( ViewLongitudeTimeseriesObject )target;
        targetObject._view = this._view;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (ViewLongitudeTimeseriesObject)obj;
        if( !Comparer.equalsNullableGuid( this._view, other._view ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _view );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _view = source.readNullableGuid( );
    }

}
