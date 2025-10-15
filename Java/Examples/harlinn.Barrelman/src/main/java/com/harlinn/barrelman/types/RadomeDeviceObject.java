package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadomeDeviceObject extends DeviceObject {

    private Guid _radar;
    private Guid _pressureTimeseries;
    private Guid _temperatureTimeseries;
    private Guid _dewPointTimeseries;
    private Guid _statusTimeseries;

    @Override
    public int getObjectType( ) {
        return Kind.RadomeDevice;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadomeDeviceObject( );
    }

    public Guid getRadar( ) {
        return _radar;
    }
    public void setRadar( Guid value ) {
        if( !Comparer.equalsNullableGuid( _radar, value ) ) {
            _radar = value;
            onPropertyChanged( );
        }
    }

    public Guid getPressureTimeseries( ) {
        return _pressureTimeseries;
    }
    public void setPressureTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _pressureTimeseries, value ) ) {
            _pressureTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getTemperatureTimeseries( ) {
        return _temperatureTimeseries;
    }
    public void setTemperatureTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _temperatureTimeseries, value ) ) {
            _temperatureTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getDewPointTimeseries( ) {
        return _dewPointTimeseries;
    }
    public void setDewPointTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _dewPointTimeseries, value ) ) {
            _dewPointTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getStatusTimeseries( ) {
        return _statusTimeseries;
    }
    public void setStatusTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _statusTimeseries, value ) ) {
            _statusTimeseries = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( RadomeDeviceObject )target;
        targetObject._radar = this._radar;
        targetObject._pressureTimeseries = this._pressureTimeseries;
        targetObject._temperatureTimeseries = this._temperatureTimeseries;
        targetObject._dewPointTimeseries = this._dewPointTimeseries;
        targetObject._statusTimeseries = this._statusTimeseries;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (RadomeDeviceObject)obj;
        if( !Comparer.equalsNullableGuid( this._radar, other._radar ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._pressureTimeseries, other._pressureTimeseries ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._temperatureTimeseries, other._temperatureTimeseries ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._dewPointTimeseries, other._dewPointTimeseries ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._statusTimeseries, other._statusTimeseries ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _radar );
        destination.writeNullableGuid( _pressureTimeseries );
        destination.writeNullableGuid( _temperatureTimeseries );
        destination.writeNullableGuid( _dewPointTimeseries );
        destination.writeNullableGuid( _statusTimeseries );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _radar = source.readNullableGuid( );
        _pressureTimeseries = source.readNullableGuid( );
        _temperatureTimeseries = source.readNullableGuid( );
        _dewPointTimeseries = source.readNullableGuid( );
        _statusTimeseries = source.readNullableGuid( );
    }

}
