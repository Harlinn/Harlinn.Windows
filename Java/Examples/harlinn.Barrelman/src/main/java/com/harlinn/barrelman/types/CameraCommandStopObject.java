package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraCommandStopObject extends CameraCommandObject {

    private boolean _panTilt = false;
    private boolean _zoom = false;

    @Override
    public int getObjectType( ) {
        return Kind.CameraCommandStop;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraCommandStopObject( );
    }

    public boolean getPanTilt( ) {
        return _panTilt;
    }
    public void setPanTilt( boolean value ) {
        if( !Comparer.equalsBoolean( _panTilt, value ) ) {
            _panTilt = value;
            onPropertyChanged( );
        }
    }

    public boolean getZoom( ) {
        return _zoom;
    }
    public void setZoom( boolean value ) {
        if( !Comparer.equalsBoolean( _zoom, value ) ) {
            _zoom = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( CameraCommandStopObject )target;
        targetObject._panTilt = this._panTilt;
        targetObject._zoom = this._zoom;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (CameraCommandStopObject)obj;
        if( !Comparer.equalsBoolean( this._panTilt, other._panTilt ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._zoom, other._zoom ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeBoolean( _panTilt );
        destination.writeBoolean( _zoom );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _panTilt = source.readBoolean( );
        _zoom = source.readBoolean( );
    }

}
