package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class MediaServiceEnabledTimeseriesObject extends BooleanTimeseriesObject {

    private Guid _service;

    @Override
    public int getObjectType( ) {
        return Kind.MediaServiceEnabledTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new MediaServiceEnabledTimeseriesObject( );
    }

    public Guid getService( ) {
        return _service;
    }
    public void setService( Guid value ) {
        if( !Comparer.equalsNullableGuid( _service, value ) ) {
            _service = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _service );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _service = source.readNullableGuid( );
    }

}
