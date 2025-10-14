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
