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
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getRadar( ) {
        return _radar;
    }
    public void setRadar( Guid value ) {
        if( !Comparer.equalsGuid( _radar, value ) ) {
            _radar = value;
            onPropertyChanged( );
        }
    }

    public DateTime getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( DateTime value ) {
        if( !Comparer.equalsDateTime( _timestamp, value ) ) {
            _timestamp = value;
            onPropertyChanged( );
        }
    }

    public int getDepth( ) {
        return _depth;
    }
    public void setDepth( int value ) {
        if( !Comparer.equalsUInt32( _depth, value ) ) {
            _depth = value;
            onPropertyChanged( );
        }
    }

    public int getResolution( ) {
        return _resolution;
    }
    public void setResolution( int value ) {
        if( !Comparer.equalsInt32( _resolution, value ) ) {
            _resolution = value;
            onPropertyChanged( );
        }
    }

    public int getRange( ) {
        return _range;
    }
    public void setRange( int value ) {
        if( !Comparer.equalsInt32( _range, value ) ) {
            _range = value;
            onPropertyChanged( );
        }
    }

    public byte[] getImage( ) {
        return _image;
    }
    public void setImage( byte[] value ) {
        if( !Comparer.equalsUInt8Array( _image, value ) ) {
            _image = value != null ? value.clone() : value;;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _radar );
        destination.writeDateTime( _timestamp );
        destination.writeUInt32( _depth );
        destination.writeInt32( _resolution );
        destination.writeInt32( _range );
        destination.writeUInt8Array( _image );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _radar = source.readGuid( );
        _timestamp = source.readDateTime( );
        _depth = source.readUInt32( );
        _resolution = source.readInt32( );
        _range = source.readInt32( );
        _image = source.readUInt8Array( );
    }

}
