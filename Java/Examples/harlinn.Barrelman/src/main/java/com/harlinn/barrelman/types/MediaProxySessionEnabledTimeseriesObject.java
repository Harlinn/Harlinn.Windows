package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class MediaProxySessionEnabledTimeseriesObject extends BooleanTimeseriesObject {

    private Guid _proxySession;

    @Override
    public int getObjectType( ) {
        return Kind.MediaProxySessionEnabledTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new MediaProxySessionEnabledTimeseriesObject( );
    }

    public Guid getProxySession( ) {
        return _proxySession;
    }
    public void setProxySession( Guid value ) {
        if( !Comparer.equalsNullableGuid( _proxySession, value ) ) {
            _proxySession = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( MediaProxySessionEnabledTimeseriesObject )target;
        targetObject._proxySession = this._proxySession;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (MediaProxySessionEnabledTimeseriesObject)obj;
        if( !Comparer.equalsNullableGuid( this._proxySession, other._proxySession ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _proxySession );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _proxySession = source.readNullableGuid( );
    }

}
