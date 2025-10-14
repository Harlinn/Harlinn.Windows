package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadarDeviceObject extends TrackerDeviceObject {

    private Guid _saveSettingsTimeseries;
    private Guid _powerOnTimeseries;
    private Guid _trackingOnTimeseries;
    private Guid _radarPulseTimeseries;
    private Guid _tuningTimeseries;
    private Guid _blankSector1Timeseries;
    private Guid _sector1StartTimeseries;
    private Guid _sector1EndTimeseries;
    private Guid _blankSector2Timeseries;
    private Guid _sector2StartTimeseries;
    private Guid _sector2EndTimeseries;
    private Guid _enableAutomaticFrequencyControlTimeseries;
    private Guid _azimuthOffsetTimeseries;
    private Guid _enableSensitivityTimeControlTimeseries;
    private Guid _automaticSensitivityTimeControlTimeseries;
    private Guid _sensitivityTimeControlLevelTimeseries;
    private Guid _enableFastTimeConstantTimeseries;
    private Guid _fastTimeConstantLevelTimeseries;
    private Guid _fastTimeConstantModeTimeseries;
    private Guid _latitudeTimeseries;
    private Guid _longitudeTimeseries;
    private Guid _radome;
    private Guid _gNSSDevice;

    @Override
    public int getObjectType( ) {
        return Kind.RadarDevice;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadarDeviceObject( );
    }

    public Guid getSaveSettingsTimeseries( ) {
        return _saveSettingsTimeseries;
    }
    public void setSaveSettingsTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _saveSettingsTimeseries, value ) ) {
            _saveSettingsTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getPowerOnTimeseries( ) {
        return _powerOnTimeseries;
    }
    public void setPowerOnTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _powerOnTimeseries, value ) ) {
            _powerOnTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getTrackingOnTimeseries( ) {
        return _trackingOnTimeseries;
    }
    public void setTrackingOnTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _trackingOnTimeseries, value ) ) {
            _trackingOnTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getRadarPulseTimeseries( ) {
        return _radarPulseTimeseries;
    }
    public void setRadarPulseTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _radarPulseTimeseries, value ) ) {
            _radarPulseTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getTuningTimeseries( ) {
        return _tuningTimeseries;
    }
    public void setTuningTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _tuningTimeseries, value ) ) {
            _tuningTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getBlankSector1Timeseries( ) {
        return _blankSector1Timeseries;
    }
    public void setBlankSector1Timeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _blankSector1Timeseries, value ) ) {
            _blankSector1Timeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getSector1StartTimeseries( ) {
        return _sector1StartTimeseries;
    }
    public void setSector1StartTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _sector1StartTimeseries, value ) ) {
            _sector1StartTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getSector1EndTimeseries( ) {
        return _sector1EndTimeseries;
    }
    public void setSector1EndTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _sector1EndTimeseries, value ) ) {
            _sector1EndTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getBlankSector2Timeseries( ) {
        return _blankSector2Timeseries;
    }
    public void setBlankSector2Timeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _blankSector2Timeseries, value ) ) {
            _blankSector2Timeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getSector2StartTimeseries( ) {
        return _sector2StartTimeseries;
    }
    public void setSector2StartTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _sector2StartTimeseries, value ) ) {
            _sector2StartTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getSector2EndTimeseries( ) {
        return _sector2EndTimeseries;
    }
    public void setSector2EndTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _sector2EndTimeseries, value ) ) {
            _sector2EndTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getEnableAutomaticFrequencyControlTimeseries( ) {
        return _enableAutomaticFrequencyControlTimeseries;
    }
    public void setEnableAutomaticFrequencyControlTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _enableAutomaticFrequencyControlTimeseries, value ) ) {
            _enableAutomaticFrequencyControlTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getAzimuthOffsetTimeseries( ) {
        return _azimuthOffsetTimeseries;
    }
    public void setAzimuthOffsetTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _azimuthOffsetTimeseries, value ) ) {
            _azimuthOffsetTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getEnableSensitivityTimeControlTimeseries( ) {
        return _enableSensitivityTimeControlTimeseries;
    }
    public void setEnableSensitivityTimeControlTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _enableSensitivityTimeControlTimeseries, value ) ) {
            _enableSensitivityTimeControlTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getAutomaticSensitivityTimeControlTimeseries( ) {
        return _automaticSensitivityTimeControlTimeseries;
    }
    public void setAutomaticSensitivityTimeControlTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _automaticSensitivityTimeControlTimeseries, value ) ) {
            _automaticSensitivityTimeControlTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getSensitivityTimeControlLevelTimeseries( ) {
        return _sensitivityTimeControlLevelTimeseries;
    }
    public void setSensitivityTimeControlLevelTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _sensitivityTimeControlLevelTimeseries, value ) ) {
            _sensitivityTimeControlLevelTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getEnableFastTimeConstantTimeseries( ) {
        return _enableFastTimeConstantTimeseries;
    }
    public void setEnableFastTimeConstantTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _enableFastTimeConstantTimeseries, value ) ) {
            _enableFastTimeConstantTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getFastTimeConstantLevelTimeseries( ) {
        return _fastTimeConstantLevelTimeseries;
    }
    public void setFastTimeConstantLevelTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _fastTimeConstantLevelTimeseries, value ) ) {
            _fastTimeConstantLevelTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getFastTimeConstantModeTimeseries( ) {
        return _fastTimeConstantModeTimeseries;
    }
    public void setFastTimeConstantModeTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _fastTimeConstantModeTimeseries, value ) ) {
            _fastTimeConstantModeTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getLatitudeTimeseries( ) {
        return _latitudeTimeseries;
    }
    public void setLatitudeTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _latitudeTimeseries, value ) ) {
            _latitudeTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getLongitudeTimeseries( ) {
        return _longitudeTimeseries;
    }
    public void setLongitudeTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _longitudeTimeseries, value ) ) {
            _longitudeTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getRadome( ) {
        return _radome;
    }
    public void setRadome( Guid value ) {
        if( !Comparer.equalsNullableGuid( _radome, value ) ) {
            _radome = value;
            onPropertyChanged( );
        }
    }

    public Guid getGNSSDevice( ) {
        return _gNSSDevice;
    }
    public void setGNSSDevice( Guid value ) {
        if( !Comparer.equalsNullableGuid( _gNSSDevice, value ) ) {
            _gNSSDevice = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _saveSettingsTimeseries );
        destination.writeNullableGuid( _powerOnTimeseries );
        destination.writeNullableGuid( _trackingOnTimeseries );
        destination.writeNullableGuid( _radarPulseTimeseries );
        destination.writeNullableGuid( _tuningTimeseries );
        destination.writeNullableGuid( _blankSector1Timeseries );
        destination.writeNullableGuid( _sector1StartTimeseries );
        destination.writeNullableGuid( _sector1EndTimeseries );
        destination.writeNullableGuid( _blankSector2Timeseries );
        destination.writeNullableGuid( _sector2StartTimeseries );
        destination.writeNullableGuid( _sector2EndTimeseries );
        destination.writeNullableGuid( _enableAutomaticFrequencyControlTimeseries );
        destination.writeNullableGuid( _azimuthOffsetTimeseries );
        destination.writeNullableGuid( _enableSensitivityTimeControlTimeseries );
        destination.writeNullableGuid( _automaticSensitivityTimeControlTimeseries );
        destination.writeNullableGuid( _sensitivityTimeControlLevelTimeseries );
        destination.writeNullableGuid( _enableFastTimeConstantTimeseries );
        destination.writeNullableGuid( _fastTimeConstantLevelTimeseries );
        destination.writeNullableGuid( _fastTimeConstantModeTimeseries );
        destination.writeNullableGuid( _latitudeTimeseries );
        destination.writeNullableGuid( _longitudeTimeseries );
        destination.writeNullableGuid( _radome );
        destination.writeNullableGuid( _gNSSDevice );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _saveSettingsTimeseries = source.readNullableGuid( );
        _powerOnTimeseries = source.readNullableGuid( );
        _trackingOnTimeseries = source.readNullableGuid( );
        _radarPulseTimeseries = source.readNullableGuid( );
        _tuningTimeseries = source.readNullableGuid( );
        _blankSector1Timeseries = source.readNullableGuid( );
        _sector1StartTimeseries = source.readNullableGuid( );
        _sector1EndTimeseries = source.readNullableGuid( );
        _blankSector2Timeseries = source.readNullableGuid( );
        _sector2StartTimeseries = source.readNullableGuid( );
        _sector2EndTimeseries = source.readNullableGuid( );
        _enableAutomaticFrequencyControlTimeseries = source.readNullableGuid( );
        _azimuthOffsetTimeseries = source.readNullableGuid( );
        _enableSensitivityTimeControlTimeseries = source.readNullableGuid( );
        _automaticSensitivityTimeControlTimeseries = source.readNullableGuid( );
        _sensitivityTimeControlLevelTimeseries = source.readNullableGuid( );
        _enableFastTimeConstantTimeseries = source.readNullableGuid( );
        _fastTimeConstantLevelTimeseries = source.readNullableGuid( );
        _fastTimeConstantModeTimeseries = source.readNullableGuid( );
        _latitudeTimeseries = source.readNullableGuid( );
        _longitudeTimeseries = source.readNullableGuid( );
        _radome = source.readNullableGuid( );
        _gNSSDevice = source.readNullableGuid( );
    }

}
