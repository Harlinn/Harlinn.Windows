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
        if( _view != value ) {
            this._view = value;
            onPropertyChanged( );
        }
    }


}
