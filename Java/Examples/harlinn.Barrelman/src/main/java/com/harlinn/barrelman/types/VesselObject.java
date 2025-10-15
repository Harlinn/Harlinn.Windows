package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class VesselObject extends TrackableItemObject {

    private String _name = "";
    private Guid _type;
    private int _toBow = 0;
    private int _toStern = 0;
    private int _toPort = 0;
    private int _toStarboard = 0;
    private Guid _draughtTimeseries;
    private Guid _personsOnBoardTimeseries;

    @Override
    public int getObjectType( ) {
        return Kind.Vessel;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new VesselObject( );
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

    public int getToBow( ) {
        return _toBow;
    }
    public void setToBow( int value ) {
        if( !Comparer.equalsInt32( _toBow, value ) ) {
            _toBow = value;
            onPropertyChanged( );
        }
    }

    public int getToStern( ) {
        return _toStern;
    }
    public void setToStern( int value ) {
        if( !Comparer.equalsInt32( _toStern, value ) ) {
            _toStern = value;
            onPropertyChanged( );
        }
    }

    public int getToPort( ) {
        return _toPort;
    }
    public void setToPort( int value ) {
        if( !Comparer.equalsInt32( _toPort, value ) ) {
            _toPort = value;
            onPropertyChanged( );
        }
    }

    public int getToStarboard( ) {
        return _toStarboard;
    }
    public void setToStarboard( int value ) {
        if( !Comparer.equalsInt32( _toStarboard, value ) ) {
            _toStarboard = value;
            onPropertyChanged( );
        }
    }

    public Guid getDraughtTimeseries( ) {
        return _draughtTimeseries;
    }
    public void setDraughtTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _draughtTimeseries, value ) ) {
            _draughtTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getPersonsOnBoardTimeseries( ) {
        return _personsOnBoardTimeseries;
    }
    public void setPersonsOnBoardTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _personsOnBoardTimeseries, value ) ) {
            _personsOnBoardTimeseries = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( VesselObject )target;
        targetObject._name = this._name;
        targetObject._type = this._type;
        targetObject._toBow = this._toBow;
        targetObject._toStern = this._toStern;
        targetObject._toPort = this._toPort;
        targetObject._toStarboard = this._toStarboard;
        targetObject._draughtTimeseries = this._draughtTimeseries;
        targetObject._personsOnBoardTimeseries = this._personsOnBoardTimeseries;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (VesselObject)obj;
        if( !Comparer.equalsString( this._name, other._name ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._type, other._type ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._toBow, other._toBow ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._toStern, other._toStern ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._toPort, other._toPort ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._toStarboard, other._toStarboard ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._draughtTimeseries, other._draughtTimeseries ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._personsOnBoardTimeseries, other._personsOnBoardTimeseries ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeStringUtf8( _name );
        destination.writeNullableGuid( _type );
        destination.writeInt32( _toBow );
        destination.writeInt32( _toStern );
        destination.writeInt32( _toPort );
        destination.writeInt32( _toStarboard );
        destination.writeNullableGuid( _draughtTimeseries );
        destination.writeNullableGuid( _personsOnBoardTimeseries );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _name = source.readString( );
        _type = source.readNullableGuid( );
        _toBow = source.readInt32( );
        _toStern = source.readInt32( );
        _toPort = source.readInt32( );
        _toStarboard = source.readInt32( );
        _draughtTimeseries = source.readNullableGuid( );
        _personsOnBoardTimeseries = source.readNullableGuid( );
    }

}
