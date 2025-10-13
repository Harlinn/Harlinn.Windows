package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadarImageObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _radar;
    private DateTime _timestamp;
    private int _depth = 0;
    private int _resolution = 0;
    private int _range = 0;
    private byte[] _image = new byte[0];

    @Override
    public int getObjectType( ) {
        return Kind.RadarImage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadarImageObject( );
    }

    public long getRowVersion( ) {
        return _rowVersion;
    }
    public void setRowVersion( long value ) {
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getRadar( ) {
        return _radar;
    }
    public void setRadar( Guid value ) {
        if( _radar != value ) {
            this._radar = value;
            onPropertyChanged( );
        }
    }

    public DateTime getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( DateTime value ) {
        if( _timestamp != value ) {
            this._timestamp = value;
            onPropertyChanged( );
        }
    }

    public int getDepth( ) {
        return _depth;
    }
    public void setDepth( int value ) {
        if( _depth != value ) {
            this._depth = value;
            onPropertyChanged( );
        }
    }

    public int getResolution( ) {
        return _resolution;
    }
    public void setResolution( int value ) {
        if( _resolution != value ) {
            this._resolution = value;
            onPropertyChanged( );
        }
    }

    public int getRange( ) {
        return _range;
    }
    public void setRange( int value ) {
        if( _range != value ) {
            this._range = value;
            onPropertyChanged( );
        }
    }

    public byte[] getImage( ) {
        return _image;
    }
    public void setImage( byte[] value ) {
        if( _image != value ) {
            this._image = value;
            onPropertyChanged( );
        }
    }


}
