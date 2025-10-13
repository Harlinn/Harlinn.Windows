package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisAidToNavigationPositionTimeseriesObject extends GeoPosition2DTimeseriesObject {

    private Guid _aidToNavigation;

    @Override
    public int getObjectType( ) {
        return Kind.AisAidToNavigationPositionTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisAidToNavigationPositionTimeseriesObject( );
    }

    public Guid getAidToNavigation( ) {
        return _aidToNavigation;
    }
    public void setAidToNavigation( Guid value ) {
        if( _aidToNavigation != value ) {
            this._aidToNavigation = value;
            onPropertyChanged( );
        }
    }


}
