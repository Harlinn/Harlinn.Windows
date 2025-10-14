package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class DeviceObject extends ItemObject {

    private Guid _host;
    private String _name = "";
    private String _description = "";
    private Guid _enabledTimeseries;


    public Guid getHost( ) {
        return _host;
    }
    public void setHost( Guid value ) {
        if( !Comparer.equalsGuid( _host, value ) ) {
            _host = value;
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

    public String getDescription( ) {
        return _description;
    }
    public void setDescription( String value ) {
        if( !Comparer.equalsString( _description, value ) ) {
            _description = value;
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
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeGuid( _host );
        destination.writeStringUtf8( _name );
        destination.writeStringUtf8( _description );
        destination.writeNullableGuid( _enabledTimeseries );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _host = source.readGuid( );
        _name = source.readString( );
        _description = source.readString( );
        _enabledTimeseries = source.readNullableGuid( );
    }

}
