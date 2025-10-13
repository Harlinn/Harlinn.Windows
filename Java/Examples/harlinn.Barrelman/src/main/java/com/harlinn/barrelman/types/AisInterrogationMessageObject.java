package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisInterrogationMessageObject extends AisMessageObject {

    private Guid _interrogatedMmsi;
    private int _firstMessageType = AisMessageType.PositionReportClassA;
    private int _firstSlotOffset = 0;
    private Integer _secondMessageType;
    private Integer _secondSlotOffset;
    private Guid _secondStationInterrogationMmsi;
    private Integer _secondStationFirstMessageType;
    private Integer _secondStationFirstSlotOffset;

    @Override
    public int getObjectType( ) {
        return Kind.AisInterrogationMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisInterrogationMessageObject( );
    }

    public Guid getInterrogatedMmsi( ) {
        return _interrogatedMmsi;
    }
    public void setInterrogatedMmsi( Guid value ) {
        if( _interrogatedMmsi != value ) {
            this._interrogatedMmsi = value;
            onPropertyChanged( );
        }
    }

    public int getFirstMessageType( ) {
        return _firstMessageType;
    }
    public void setFirstMessageType( int value ) {
        if( _firstMessageType != value ) {
            this._firstMessageType = value;
            onPropertyChanged( );
        }
    }

    public int getFirstSlotOffset( ) {
        return _firstSlotOffset;
    }
    public void setFirstSlotOffset( int value ) {
        if( _firstSlotOffset != value ) {
            this._firstSlotOffset = value;
            onPropertyChanged( );
        }
    }

    public Integer getSecondMessageType( ) {
        return _secondMessageType;
    }
    public void setSecondMessageType( Integer value ) {
        if( _secondMessageType != value ) {
            this._secondMessageType = value;
            onPropertyChanged( );
        }
    }

    public Integer getSecondSlotOffset( ) {
        return _secondSlotOffset;
    }
    public void setSecondSlotOffset( Integer value ) {
        if( _secondSlotOffset != value ) {
            this._secondSlotOffset = value;
            onPropertyChanged( );
        }
    }

    public Guid getSecondStationInterrogationMmsi( ) {
        return _secondStationInterrogationMmsi;
    }
    public void setSecondStationInterrogationMmsi( Guid value ) {
        if( _secondStationInterrogationMmsi != value ) {
            this._secondStationInterrogationMmsi = value;
            onPropertyChanged( );
        }
    }

    public Integer getSecondStationFirstMessageType( ) {
        return _secondStationFirstMessageType;
    }
    public void setSecondStationFirstMessageType( Integer value ) {
        if( _secondStationFirstMessageType != value ) {
            this._secondStationFirstMessageType = value;
            onPropertyChanged( );
        }
    }

    public Integer getSecondStationFirstSlotOffset( ) {
        return _secondStationFirstSlotOffset;
    }
    public void setSecondStationFirstSlotOffset( Integer value ) {
        if( _secondStationFirstSlotOffset != value ) {
            this._secondStationFirstSlotOffset = value;
            onPropertyChanged( );
        }
    }


}
