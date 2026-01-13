/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadarImageObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.RadarImage;

    private long _rowVersion = 0;
    private Guid _radar;
    private DateTime _timestamp;
    private int _depth = 0;
    private int _resolution = 0;
    private int _range = 0;
    private byte[] _image = new byte[0];

    public RadarImageObject( ) {
    }
    public RadarImageObject( byte objectState, Guid id, long rowVersion, Guid radar, DateTime timestamp, int depth, int resolution, int range, byte[] image ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._radar = radar;
        this._timestamp = timestamp;
        this._depth = depth;
        this._resolution = resolution;
        this._range = range;
        this._image = image;
    }

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
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( RadarImageObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._radar = this._radar;
        targetObject._timestamp = this._timestamp;
        targetObject._depth = this._depth;
        targetObject._resolution = this._resolution;
        targetObject._range = this._range;
        targetObject._image = this._image != null ? this._image.clone() : this._image;;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (RadarImageObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._radar, other._radar ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsUInt32( this._depth, other._depth ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._resolution, other._resolution ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._range, other._range ) ) {
            return false;
        }
        if( !Comparer.equalsUInt8Array( this._image, other._image ) ) {
            return false;
        }
        return true;
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
