package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class VehicleObject extends TrackableItemObject {

    public final int KIND = Kind.Vehicle;

    private String _name = "";
    private Guid _type;

    public VehicleObject( ) {
    }
    public VehicleObject( byte objectState, Guid id, long rowVersion, String name, Guid type ) {
        super( objectState, id, rowVersion );
        this._name = name;
        this._type = type;
    }

    @Override
    public int getObjectType( ) {
        return Kind.Vehicle;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new VehicleObject( );
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



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( VehicleObject )target;
        targetObject._name = this._name;
        targetObject._type = this._type;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (VehicleObject)obj;
        if( !Comparer.equalsString( this._name, other._name ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._type, other._type ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeStringUtf8( _name );
        destination.writeNullableGuid( _type );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _name = source.readString( );
        _type = source.readNullableGuid( );
    }

}
