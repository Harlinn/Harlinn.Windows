package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class MediaProxySessionObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _service;
    private String _name = "";
    private Guid _enabledTimeseries;

    @Override
    public int getObjectType( ) {
        return Kind.MediaProxySession;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new MediaProxySessionObject( );
    }

    public long getRowVersion( ) {
        return _rowVersion;
    }
    public void setRowVersion( long value ) {
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getService( ) {
        return _service;
    }
    public void setService( Guid value ) {
        if( !Comparer.equalsGuid( _service, value ) ) {
            _service = value;
            onPropertyChanged( );
        }
    }

    public String getName( ) {
        return _name;
    }
    public void setName( String value ) {
        if( !Comparer.equalsString( _name, value ) ) {
            _name = value;
            onPropertyChanged( );
        }
    }

    public Guid getEnabledTimeseries( ) {
        return _enabledTimeseries;
    }
    public void setEnabledTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _enabledTimeseries, value ) ) {
            _enabledTimeseries = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( MediaProxySessionObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._service = this._service;
        targetObject._name = this._name;
        targetObject._enabledTimeseries = this._enabledTimeseries;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (MediaProxySessionObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._service, other._service ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._name, other._name ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._enabledTimeseries, other._enabledTimeseries ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _service );
        destination.writeStringUtf8( _name );
        destination.writeNullableGuid( _enabledTimeseries );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _service = source.readGuid( );
        _name = source.readString( );
        _enabledTimeseries = source.readNullableGuid( );
    }

}
