package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CircularZoneObject extends ZoneObject {

    public final int KIND = Kind.CircularZone;

    private double _radius = 0.0;

    public CircularZoneObject( ) {
    }
    public CircularZoneObject( byte objectState, Guid id, long rowVersion, String name, double longitude, double latitude, int alarmType, TimeSpan alarmTime, TimeSpan radarTrackMinimumLifetime, double speed, int strokeColor, int fillColor, double radius ) {
        super( objectState, id, rowVersion, name, longitude, latitude, alarmType, alarmTime, radarTrackMinimumLifetime, speed, strokeColor, fillColor );
        this._radius = radius;
    }

    @Override
    public int getObjectType( ) {
        return Kind.CircularZone;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CircularZoneObject( );
    }

    public double getRadius( ) {
        return _radius;
    }
    public void setRadius( double value ) {
        if( !Comparer.equalsDouble( _radius, value ) ) {
            _radius = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( CircularZoneObject )target;
        targetObject._radius = this._radius;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (CircularZoneObject)obj;
        if( !Comparer.equalsDouble( this._radius, other._radius ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeDouble( _radius );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _radius = source.readDouble( );
    }

}
