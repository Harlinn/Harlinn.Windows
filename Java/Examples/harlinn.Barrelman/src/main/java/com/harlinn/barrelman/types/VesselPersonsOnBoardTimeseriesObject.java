package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class VesselPersonsOnBoardTimeseriesObject extends Int32TimeseriesObject {

    private Guid _vessel;

    @Override
    public int getObjectType( ) {
        return Kind.VesselPersonsOnBoardTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new VesselPersonsOnBoardTimeseriesObject( );
    }

    public Guid getVessel( ) {
        return _vessel;
    }
    public void setVessel( Guid value ) {
        if( _vessel != value ) {
            this._vessel = value;
            onPropertyChanged( );
        }
    }


}
