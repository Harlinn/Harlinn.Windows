package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class MediaServiceEnabledTimeseriesObject extends BooleanTimeseriesObject {

    public final int KIND = Kind.MediaServiceEnabledTimeseries;

    private Guid _service;

    public MediaServiceEnabledTimeseriesObject( ) {
    }
    public MediaServiceEnabledTimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention, Guid service ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
        this._service = service;
    }

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
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( MediaServiceEnabledTimeseriesObject )target;
        targetObject._service = this._service;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (MediaServiceEnabledTimeseriesObject)obj;
        if( !Comparer.equalsNullableGuid( this._service, other._service ) ) {
            return false;
        }
        return true;
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
