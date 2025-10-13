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
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getItem( ) {
        return _item;
    }
    public void setItem( Guid value ) {
        if( _item != value ) {
            this._item = value;
            onPropertyChanged( );
        }
    }

    public int getElementType( ) {
        return _elementType;
    }
    public void setElementType( int value ) {
        if( _elementType != value ) {
            this._elementType = value;
            onPropertyChanged( );
        }
    }

    public double getLatitude( ) {
        return _latitude;
    }
    public void setLatitude( double value ) {
        if( _latitude != value ) {
            this._latitude = value;
            onPropertyChanged( );
        }
    }

    public double getLongitude( ) {
        return _longitude;
    }
    public void setLongitude( double value ) {
        if( _longitude != value ) {
            this._longitude = value;
            onPropertyChanged( );
        }
    }

    public double getAngle( ) {
        return _angle;
    }
    public void setAngle( double value ) {
        if( _angle != value ) {
            this._angle = value;
            onPropertyChanged( );
        }
    }

    public double getLeft( ) {
        return _left;
    }
    public void setLeft( double value ) {
        if( _left != value ) {
            this._left = value;
            onPropertyChanged( );
        }
    }

    public double getTop( ) {
        return _top;
    }
    public void setTop( double value ) {
        if( _top != value ) {
            this._top = value;
            onPropertyChanged( );
        }
    }

    public double getWidth( ) {
        return _width;
    }
    public void setWidth( double value ) {
        if( _width != value ) {
            this._width = value;
            onPropertyChanged( );
        }
    }

    public double getHeight( ) {
        return _height;
    }
    public void setHeight( double value ) {
        if( _height != value ) {
            this._height = value;
            onPropertyChanged( );
        }
    }

    public String getLabel( ) {
        return _label;
    }
    public void setLabel( String value ) {
        if( _label != value ) {
            this._label = value;
            onPropertyChanged( );
        }
    }

    public byte[] getData( ) {
        return _data;
    }
    public void setData( byte[] value ) {
        if( _data != value ) {
            this._data = value;
            onPropertyChanged( );
        }
    }


}
