package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisSafetyRelatedAcknowledgmentMessageObject extends AisMessageObject {

    private int _spare = 0;
    private int _sequenceNumber1 = 0;
    private Guid _mmsi1;
    private Integer _sequenceNumber2;
    private Guid _mmsi2;
    private Integer _sequenceNumber3;
    private Guid _mmsi3;
    private Integer _sequenceNumber4;
    private Guid _mmsi4;

    @Override
    public int getObjectType( ) {
        return Kind.AisSafetyRelatedAcknowledgmentMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisSafetyRelatedAcknowledgmentMessageObject( );
    }

    public int getSpare( ) {
        return _spare;
    }
    public void setSpare( int value ) {
        if( _spare != value ) {
            this._spare = value;
            onPropertyChanged( );
        }
    }

    public int getSequenceNumber1( ) {
        return _sequenceNumber1;
    }
    public void setSequenceNumber1( int value ) {
        if( _sequenceNumber1 != value ) {
            this._sequenceNumber1 = value;
            onPropertyChanged( );
        }
    }

    public Guid getMmsi1( ) {
        return _mmsi1;
    }
    public void setMmsi1( Guid value ) {
        if( _mmsi1 != value ) {
            this._mmsi1 = value;
            onPropertyChanged( );
        }
    }

    public Integer getSequenceNumber2( ) {
        return _sequenceNumber2;
    }
    public void setSequenceNumber2( Integer value ) {
        if( _sequenceNumber2 != value ) {
            this._sequenceNumber2 = value;
            onPropertyChanged( );
        }
    }

    public Guid getMmsi2( ) {
        return _mmsi2;
    }
    public void setMmsi2( Guid value ) {
        if( _mmsi2 != value ) {
            this._mmsi2 = value;
            onPropertyChanged( );
        }
    }

    public Integer getSequenceNumber3( ) {
        return _sequenceNumber3;
    }
    public void setSequenceNumber3( Integer value ) {
        if( _sequenceNumber3 != value ) {
            this._sequenceNumber3 = value;
            onPropertyChanged( );
        }
    }

    public Guid getMmsi3( ) {
        return _mmsi3;
    }
    public void setMmsi3( Guid value ) {
        if( _mmsi3 != value ) {
            this._mmsi3 = value;
            onPropertyChanged( );
        }
    }

    public Integer getSequenceNumber4( ) {
        return _sequenceNumber4;
    }
    public void setSequenceNumber4( Integer value ) {
        if( _sequenceNumber4 != value ) {
            this._sequenceNumber4 = value;
            onPropertyChanged( );
        }
    }

    public Guid getMmsi4( ) {
        return _mmsi4;
    }
    public void setMmsi4( Guid value ) {
        if( _mmsi4 != value ) {
            this._mmsi4 = value;
            onPropertyChanged( );
        }
    }


}
