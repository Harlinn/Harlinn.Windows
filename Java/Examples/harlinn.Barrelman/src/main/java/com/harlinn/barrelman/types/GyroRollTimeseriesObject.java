package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GyroRollTimeseriesObject extends DoubleTimeseriesObject {

    public final int KIND = Kind.GyroRollTimeseries;

    private Guid _gyroDevice;

    public GyroRollTimeseriesObject( ) {
    }
    public GyroRollTimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention, Guid gyroDevice ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
        this._gyroDevice = gyroDevice;
    }

    @Override
    public int getObjectType( ) {
        return Kind.GyroRollTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new GyroRollTimeseriesObject( );
    }

    public Guid getGyroDevice( ) {
        return _gyroDevice;
    }
    public void setGyroDevice( Guid value ) {
        if( !Comparer.equalsNullableGuid( _gyroDevice, value ) ) {
            _gyroDevice = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( GyroRollTimeseriesObject )target;
        targetObject._gyroDevice = this._gyroDevice;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (GyroRollTimeseriesObject)obj;
        if( !Comparer.equalsNullableGuid( this._gyroDevice, other._gyroDevice ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _gyroDevice );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _gyroDevice = source.readNullableGuid( );
    }

}
