package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ViewLatitudeTimeseriesObject extends DoubleTimeseriesObject {

    private Guid _view;

    @Override
    public int getObjectType( ) {
        return Kind.ViewLatitudeTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ViewLatitudeTimeseriesObject( );
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
        var targetObject = ( ViewLatitudeTimeseriesObject )target;
        targetObject._view = this._view;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (ViewLatitudeTimeseriesObject)obj;
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
