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
        if( !Comparer.equalsNullableGuid( _aidToNavigation, value ) ) {
            _aidToNavigation = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _aidToNavigation );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _aidToNavigation = source.readNullableGuid( );
    }

}
