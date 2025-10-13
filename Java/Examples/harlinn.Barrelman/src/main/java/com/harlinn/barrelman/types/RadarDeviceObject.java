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
        if( _saveSettingsTimeseries != value ) {
            this._saveSettingsTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getPowerOnTimeseries( ) {
        return _powerOnTimeseries;
    }
    public void setPowerOnTimeseries( Guid value ) {
        if( _powerOnTimeseries != value ) {
            this._powerOnTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getTrackingOnTimeseries( ) {
        return _trackingOnTimeseries;
    }
    public void setTrackingOnTimeseries( Guid value ) {
        if( _trackingOnTimeseries != value ) {
            this._trackingOnTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getRadarPulseTimeseries( ) {
        return _radarPulseTimeseries;
    }
    public void setRadarPulseTimeseries( Guid value ) {
        if( _radarPulseTimeseries != value ) {
            this._radarPulseTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getTuningTimeseries( ) {
        return _tuningTimeseries;
    }
    public void setTuningTimeseries( Guid value ) {
        if( _tuningTimeseries != value ) {
            this._tuningTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getBlankSector1Timeseries( ) {
        return _blankSector1Timeseries;
    }
    public void setBlankSector1Timeseries( Guid value ) {
        if( _blankSector1Timeseries != value ) {
            this._blankSector1Timeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getSector1StartTimeseries( ) {
        return _sector1StartTimeseries;
    }
    public void setSector1StartTimeseries( Guid value ) {
        if( _sector1StartTimeseries != value ) {
            this._sector1StartTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getSector1EndTimeseries( ) {
        return _sector1EndTimeseries;
    }
    public void setSector1EndTimeseries( Guid value ) {
        if( _sector1EndTimeseries != value ) {
            this._sector1EndTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getBlankSector2Timeseries( ) {
        return _blankSector2Timeseries;
    }
    public void setBlankSector2Timeseries( Guid value ) {
        if( _blankSector2Timeseries != value ) {
            this._blankSector2Timeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getSector2StartTimeseries( ) {
        return _sector2StartTimeseries;
    }
    public void setSector2StartTimeseries( Guid value ) {
        if( _sector2StartTimeseries != value ) {
            this._sector2StartTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getSector2EndTimeseries( ) {
        return _sector2EndTimeseries;
    }
    public void setSector2EndTimeseries( Guid value ) {
        if( _sector2EndTimeseries != value ) {
            this._sector2EndTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getEnableAutomaticFrequencyControlTimeseries( ) {
        return _enableAutomaticFrequencyControlTimeseries;
    }
    public void setEnableAutomaticFrequencyControlTimeseries( Guid value ) {
        if( _enableAutomaticFrequencyControlTimeseries != value ) {
            this._enableAutomaticFrequencyControlTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getAzimuthOffsetTimeseries( ) {
        return _azimuthOffsetTimeseries;
    }
    public void setAzimuthOffsetTimeseries( Guid value ) {
        if( _azimuthOffsetTimeseries != value ) {
            this._azimuthOffsetTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getEnableSensitivityTimeControlTimeseries( ) {
        return _enableSensitivityTimeControlTimeseries;
    }
    public void setEnableSensitivityTimeControlTimeseries( Guid value ) {
        if( _enableSensitivityTimeControlTimeseries != value ) {
            this._enableSensitivityTimeControlTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getAutomaticSensitivityTimeControlTimeseries( ) {
        return _automaticSensitivityTimeControlTimeseries;
    }
    public void setAutomaticSensitivityTimeControlTimeseries( Guid value ) {
        if( _automaticSensitivityTimeControlTimeseries != value ) {
            this._automaticSensitivityTimeControlTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getSensitivityTimeControlLevelTimeseries( ) {
        return _sensitivityTimeControlLevelTimeseries;
    }
    public void setSensitivityTimeControlLevelTimeseries( Guid value ) {
        if( _sensitivityTimeControlLevelTimeseries != value ) {
            this._sensitivityTimeControlLevelTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getEnableFastTimeConstantTimeseries( ) {
        return _enableFastTimeConstantTimeseries;
    }
    public void setEnableFastTimeConstantTimeseries( Guid value ) {
        if( _enableFastTimeConstantTimeseries != value ) {
            this._enableFastTimeConstantTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getFastTimeConstantLevelTimeseries( ) {
        return _fastTimeConstantLevelTimeseries;
    }
    public void setFastTimeConstantLevelTimeseries( Guid value ) {
        if( _fastTimeConstantLevelTimeseries != value ) {
            this._fastTimeConstantLevelTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getFastTimeConstantModeTimeseries( ) {
        return _fastTimeConstantModeTimeseries;
    }
    public void setFastTimeConstantModeTimeseries( Guid value ) {
        if( _fastTimeConstantModeTimeseries != value ) {
            this._fastTimeConstantModeTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getLatitudeTimeseries( ) {
        return _latitudeTimeseries;
    }
    public void setLatitudeTimeseries( Guid value ) {
        if( _latitudeTimeseries != value ) {
            this._latitudeTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getLongitudeTimeseries( ) {
        return _longitudeTimeseries;
    }
    public void setLongitudeTimeseries( Guid value ) {
        if( _longitudeTimeseries != value ) {
            this._longitudeTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getRadome( ) {
        return _radome;
    }
    public void setRadome( Guid value ) {
        if( _radome != value ) {
            this._radome = value;
            onPropertyChanged( );
        }
    }

    public Guid getGNSSDevice( ) {
        return _gNSSDevice;
    }
    public void setGNSSDevice( Guid value ) {
        if( _gNSSDevice != value ) {
            this._gNSSDevice = value;
            onPropertyChanged( );
        }
    }


}
