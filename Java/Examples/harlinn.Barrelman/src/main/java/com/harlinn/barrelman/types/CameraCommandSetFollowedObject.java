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
        if( _trackId != value ) {
            this._trackId = value;
            onPropertyChanged( );
        }
    }

    public int getReason( ) {
        return _reason;
    }
    public void setReason( int value ) {
        if( _reason != value ) {
            this._reason = value;
            onPropertyChanged( );
        }
    }


}
