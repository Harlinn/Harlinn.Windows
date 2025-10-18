package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class FacilityObject extends ItemObject {

    public final int KIND = Kind.Facility;

    private String _name = "";
    private Guid _type;
    private double _longitude = 0.0;
    private double _latitude = 0.0;
    private double _altitude = 0.0;

    public FacilityObject( ) {
    }
    public FacilityObject( byte objectState, Guid id, long rowVersion, String name, Guid type, double longitude, double latitude, double altitude ) {
        super( objectState, id, rowVersion );
        this._name = name;
        this._type = type;
        this._longitude = longitude;
        this._latitude = latitude;
        this._altitude = altitude;
    }

    @Override
    public int getObjectType( ) {
        return Kind.Facility;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new FacilityObject( );
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

    public Guid getType( ) {
        return _type;
    }
    public void setType( Guid value ) {
        if( !Comparer.equalsNullableGuid( _type, value ) ) {
            _type = value;
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

    public double getLatitude( ) {
        return _latitude;
    }
    public void setLatitude( double value ) {
        if( !Comparer.equalsDouble( _latitude, value ) ) {
            _latitude = value;
            onPropertyChanged( );
        }
    }

    public double getAltitude( ) {
        return _altitude;
    }
    public void setAltitude( double value ) {
        if( !Comparer.equalsDouble( _altitude, value ) ) {
            _altitude = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( FacilityObject )target;
        targetObject._name = this._name;
        targetObject._type = this._type;
        targetObject._longitude = this._longitude;
        targetObject._latitude = this._latitude;
        targetObject._altitude = this._altitude;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (FacilityObject)obj;
        if( !Comparer.equalsString( this._name, other._name ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._type, other._type ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._longitude, other._longitude ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._latitude, other._latitude ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._altitude, other._altitude ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeStringUtf8( _name );
        destination.writeNullableGuid( _type );
        destination.writeDouble( _longitude );
        destination.writeDouble( _latitude );
        destination.writeDouble( _altitude );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _name = source.readString( );
        _type = source.readNullableGuid( );
        _longitude = source.readDouble( );
        _latitude = source.readDouble( );
        _altitude = source.readDouble( );
    }

}
