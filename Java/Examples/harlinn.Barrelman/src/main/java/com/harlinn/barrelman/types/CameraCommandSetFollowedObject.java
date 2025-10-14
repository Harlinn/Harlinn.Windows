package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraCommandSetFollowedObject extends CameraCommandObject {

    private Guid _trackId;
    private int _reason = CameraFollowReason.Alarm;

    @Override
    public int getObjectType( ) {
        return Kind.CameraCommandSetFollowed;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraCommandSetFollowedObject( );
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

    public int getReason( ) {
        return _reason;
    }
    public void setReason( int value ) {
        if( !Comparer.equalsInt32( _reason, value ) ) {
            _reason = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeGuid( _trackId );
        destination.writeInt32( _reason );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _trackId = source.readGuid( );
        _reason = source.readInt32( );
    }

}
