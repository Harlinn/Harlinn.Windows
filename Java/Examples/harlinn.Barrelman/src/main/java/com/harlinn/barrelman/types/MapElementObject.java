package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class MapElementObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _item;
    private int _elementType = MapElementType.Unknown;
    private double _latitude = 0.0;
    private double _longitude = 0.0;
    private double _angle = 0.0;
    private double _left = 0.0;
    private double _top = 0.0;
    private double _width = 0.0;
    private double _height = 0.0;
    private String _label = "";
    private byte[] _data = new byte[0];

    @Override
    public int getObjectType( ) {
        return Kind.MapElement;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new MapElementObject( );
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

    public Guid getItem( ) {
        return _item;
    }
    public void setItem( Guid value ) {
        if( !Comparer.equalsGuid( _item, value ) ) {
            _item = value;
            onPropertyChanged( );
        }
    }

    public int getElementType( ) {
        return _elementType;
    }
    public void setElementType( int value ) {
        if( !Comparer.equalsInt32( _elementType, value ) ) {
            _elementType = value;
            onPropertyChanged( );
        }
    }

    public double getLatitude( ) {
        return _latitude;
    }
    public void setLatitude( double value ) {
        if( !Comparer.equalsDouble( _latitude, value ) ) {
            _latitude = value;
            onPropertyChanged( );
        }
    }

    public double getLongitude( ) {
        return _longitude;
    }
    public void setLongitude( double value ) {
        if( !Comparer.equalsDouble( _longitude, value ) ) {
            _longitude = value;
            onPropertyChanged( );
        }
    }

    public double getAngle( ) {
        return _angle;
    }
    public void setAngle( double value ) {
        if( !Comparer.equalsDouble( _angle, value ) ) {
            _angle = value;
            onPropertyChanged( );
        }
    }

    public double getLeft( ) {
        return _left;
    }
    public void setLeft( double value ) {
        if( !Comparer.equalsDouble( _left, value ) ) {
            _left = value;
            onPropertyChanged( );
        }
    }

    public double getTop( ) {
        return _top;
    }
    public void setTop( double value ) {
        if( !Comparer.equalsDouble( _top, value ) ) {
            _top = value;
            onPropertyChanged( );
        }
    }

    public double getWidth( ) {
        return _width;
    }
    public void setWidth( double value ) {
        if( !Comparer.equalsDouble( _width, value ) ) {
            _width = value;
            onPropertyChanged( );
        }
    }

    public double getHeight( ) {
        return _height;
    }
    public void setHeight( double value ) {
        if( !Comparer.equalsDouble( _height, value ) ) {
            _height = value;
            onPropertyChanged( );
        }
    }

    public String getLabel( ) {
        return _label;
    }
    public void setLabel( String value ) {
        if( !Comparer.equalsString( _label, value ) ) {
            _label = value;
            onPropertyChanged( );
        }
    }

    public byte[] getData( ) {
        return _data;
    }
    public void setData( byte[] value ) {
        if( !Comparer.equalsUInt8Array( _data, value ) ) {
            _data = value != null ? value.clone() : value;;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _item );
        destination.writeInt32( _elementType );
        destination.writeDouble( _latitude );
        destination.writeDouble( _longitude );
        destination.writeDouble( _angle );
        destination.writeDouble( _left );
        destination.writeDouble( _top );
        destination.writeDouble( _width );
        destination.writeDouble( _height );
        destination.writeStringUtf8( _label );
        destination.writeUInt8Array( _data );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _item = source.readGuid( );
        _elementType = source.readInt32( );
        _latitude = source.readDouble( );
        _longitude = source.readDouble( );
        _angle = source.readDouble( );
        _left = source.readDouble( );
        _top = source.readDouble( );
        _width = source.readDouble( );
        _height = source.readDouble( );
        _label = source.readString( );
        _data = source.readUInt8Array( );
    }

}
