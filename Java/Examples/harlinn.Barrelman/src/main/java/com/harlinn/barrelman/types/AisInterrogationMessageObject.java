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
        if( !Comparer.equalsNullableGuid( _interrogatedMmsi, value ) ) {
            _interrogatedMmsi = value;
            onPropertyChanged( );
        }
    }

    public int getFirstMessageType( ) {
        return _firstMessageType;
    }
    public void setFirstMessageType( int value ) {
        if( !Comparer.equalsInt32( _firstMessageType, value ) ) {
            _firstMessageType = value;
            onPropertyChanged( );
        }
    }

    public int getFirstSlotOffset( ) {
        return _firstSlotOffset;
    }
    public void setFirstSlotOffset( int value ) {
        if( !Comparer.equalsInt32( _firstSlotOffset, value ) ) {
            _firstSlotOffset = value;
            onPropertyChanged( );
        }
    }

    public Integer getSecondMessageType( ) {
        return _secondMessageType;
    }
    public void setSecondMessageType( Integer value ) {
        if( !Comparer.equalsNullableInt32( _secondMessageType, value ) ) {
            _secondMessageType = value;
            onPropertyChanged( );
        }
    }

    public Integer getSecondSlotOffset( ) {
        return _secondSlotOffset;
    }
    public void setSecondSlotOffset( Integer value ) {
        if( !Comparer.equalsNullableInt32( _secondSlotOffset, value ) ) {
            _secondSlotOffset = value;
            onPropertyChanged( );
        }
    }

    public Guid getSecondStationInterrogationMmsi( ) {
        return _secondStationInterrogationMmsi;
    }
    public void setSecondStationInterrogationMmsi( Guid value ) {
        if( !Comparer.equalsNullableGuid( _secondStationInterrogationMmsi, value ) ) {
            _secondStationInterrogationMmsi = value;
            onPropertyChanged( );
        }
    }

    public Integer getSecondStationFirstMessageType( ) {
        return _secondStationFirstMessageType;
    }
    public void setSecondStationFirstMessageType( Integer value ) {
        if( !Comparer.equalsNullableInt32( _secondStationFirstMessageType, value ) ) {
            _secondStationFirstMessageType = value;
            onPropertyChanged( );
        }
    }

    public Integer getSecondStationFirstSlotOffset( ) {
        return _secondStationFirstSlotOffset;
    }
    public void setSecondStationFirstSlotOffset( Integer value ) {
        if( !Comparer.equalsNullableInt32( _secondStationFirstSlotOffset, value ) ) {
            _secondStationFirstSlotOffset = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( AisInterrogationMessageObject )target;
        targetObject._interrogatedMmsi = this._interrogatedMmsi;
        targetObject._firstMessageType = this._firstMessageType;
        targetObject._firstSlotOffset = this._firstSlotOffset;
        targetObject._secondMessageType = this._secondMessageType;
        targetObject._secondSlotOffset = this._secondSlotOffset;
        targetObject._secondStationInterrogationMmsi = this._secondStationInterrogationMmsi;
        targetObject._secondStationFirstMessageType = this._secondStationFirstMessageType;
        targetObject._secondStationFirstSlotOffset = this._secondStationFirstSlotOffset;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (AisInterrogationMessageObject)obj;
        if( !Comparer.equalsNullableGuid( this._interrogatedMmsi, other._interrogatedMmsi ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._firstMessageType, other._firstMessageType ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._firstSlotOffset, other._firstSlotOffset ) ) {
            return false;
        }
        if( !Comparer.equalsNullableInt32( this._secondMessageType, other._secondMessageType ) ) {
            return false;
        }
        if( !Comparer.equalsNullableInt32( this._secondSlotOffset, other._secondSlotOffset ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._secondStationInterrogationMmsi, other._secondStationInterrogationMmsi ) ) {
            return false;
        }
        if( !Comparer.equalsNullableInt32( this._secondStationFirstMessageType, other._secondStationFirstMessageType ) ) {
            return false;
        }
        if( !Comparer.equalsNullableInt32( this._secondStationFirstSlotOffset, other._secondStationFirstSlotOffset ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _interrogatedMmsi );
        destination.writeInt32( _firstMessageType );
        destination.writeInt32( _firstSlotOffset );
        destination.writeNullableInt32( _secondMessageType );
        destination.writeNullableInt32( _secondSlotOffset );
        destination.writeNullableGuid( _secondStationInterrogationMmsi );
        destination.writeNullableInt32( _secondStationFirstMessageType );
        destination.writeNullableInt32( _secondStationFirstSlotOffset );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _interrogatedMmsi = source.readNullableGuid( );
        _firstMessageType = source.readInt32( );
        _firstSlotOffset = source.readInt32( );
        _secondMessageType = source.readNullableInt32( );
        _secondSlotOffset = source.readNullableInt32( );
        _secondStationInterrogationMmsi = source.readNullableGuid( );
        _secondStationFirstMessageType = source.readNullableInt32( );
        _secondStationFirstSlotOffset = source.readNullableInt32( );
    }

}
