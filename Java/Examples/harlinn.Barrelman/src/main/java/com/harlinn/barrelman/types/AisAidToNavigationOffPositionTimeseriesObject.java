package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisAidToNavigationOffPositionTimeseriesObject extends BooleanTimeseriesObject {

    private Guid _aidToNavigation;

    @Override
    public int getObjectType( ) {
        return Kind.AisAidToNavigationOffPositionTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisAidToNavigationOffPositionTimeseriesObject( );
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
