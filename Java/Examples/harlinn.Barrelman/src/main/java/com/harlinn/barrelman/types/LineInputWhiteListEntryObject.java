package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class LineInputWhiteListEntryObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _lineInputDevice;
    private String _hostName = "";
    private int _port = 0;

    @Override
    public int getObjectType( ) {
        return Kind.LineInputWhiteListEntry;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new LineInputWhiteListEntryObject( );
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

    public Guid getLineInputDevice( ) {
        return _lineInputDevice;
    }
    public void setLineInputDevice( Guid value ) {
        if( !Comparer.equalsGuid( _lineInputDevice, value ) ) {
            _lineInputDevice = value;
            onPropertyChanged( );
        }
    }

    public String getHostName( ) {
        return _hostName;
    }
    public void setHostName( String value ) {
        if( !Comparer.equalsString( _hostName, value ) ) {
            _hostName = value;
            onPropertyChanged( );
        }
    }

    public int getPort( ) {
        return _port;
    }
    public void setPort( int value ) {
        if( !Comparer.equalsInt32( _port, value ) ) {
            _port = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _lineInputDevice );
        destination.writeStringUtf8( _hostName );
        destination.writeInt32( _port );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _lineInputDevice = source.readGuid( );
        _hostName = source.readString( );
        _port = source.readInt32( );
    }

}
