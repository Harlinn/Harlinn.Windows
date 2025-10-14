package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class TrackerFilterParametersObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _tracker;
    private String _name = "";

    @Override
    public int getObjectType( ) {
        return Kind.TrackerFilterParameters;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new TrackerFilterParametersObject( );
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

    public Guid getTracker( ) {
        return _tracker;
    }
    public void setTracker( Guid value ) {
        if( !Comparer.equalsGuid( _tracker, value ) ) {
            _tracker = value;
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



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _tracker );
        destination.writeStringUtf8( _name );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _tracker = source.readGuid( );
        _name = source.readString( );
    }

}
