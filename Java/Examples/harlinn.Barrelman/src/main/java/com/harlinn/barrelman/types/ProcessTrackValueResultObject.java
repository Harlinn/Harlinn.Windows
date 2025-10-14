package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ProcessTrackValueResultObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private boolean _createdNewTrack = false;
    private Guid _trackId;

    @Override
    public int getObjectType( ) {
        return Kind.ProcessTrackValueResult;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ProcessTrackValueResultObject( );
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

    public boolean getCreatedNewTrack( ) {
        return _createdNewTrack;
    }
    public void setCreatedNewTrack( boolean value ) {
        if( !Comparer.equalsBoolean( _createdNewTrack, value ) ) {
            _createdNewTrack = value;
            onPropertyChanged( );
        }
    }

    public Guid getTrackId( ) {
        return _trackId;
    }
    public void setTrackId( Guid value ) {
        if( !Comparer.equalsGuid( _trackId, value ) ) {
            _trackId = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeBoolean( _createdNewTrack );
        destination.writeGuid( _trackId );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _createdNewTrack = source.readBoolean( );
        _trackId = source.readGuid( );
    }

}
