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
