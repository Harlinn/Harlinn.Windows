package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisBinaryBroadcastMessageObject extends AisMessageObject {

    public final int KIND = Kind.AisBinaryBroadcastMessage;

    private int _spare = 0;
    private int _designatedAreaCode = 0;
    private int _functionalId = 0;
    private String _data = "";

    public AisBinaryBroadcastMessageObject( ) {
    }
    public AisBinaryBroadcastMessageObject( byte objectState, Guid id, long rowVersion, Guid aisDevice, DateTime receivedTimestamp, long messageSequenceNumber, int repeat, Guid mmsi, int spare, int designatedAreaCode, int functionalId, String data ) {
        super( objectState, id, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi );
        this._spare = spare;
        this._designatedAreaCode = designatedAreaCode;
        this._functionalId = functionalId;
        this._data = data;
    }

    @Override
    public int getObjectType( ) {
        return Kind.AisBinaryBroadcastMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisBinaryBroadcastMessageObject( );
    }

    public int getSpare( ) {
        return _spare;
    }
    public void setSpare( int value ) {
        if( !Comparer.equalsInt32( _spare, value ) ) {
            _spare = value;
            onPropertyChanged( );
        }
    }

    public int getDesignatedAreaCode( ) {
        return _designatedAreaCode;
    }
    public void setDesignatedAreaCode( int value ) {
        if( !Comparer.equalsInt32( _designatedAreaCode, value ) ) {
            _designatedAreaCode = value;
            onPropertyChanged( );
        }
    }

    public int getFunctionalId( ) {
        return _functionalId;
    }
    public void setFunctionalId( int value ) {
        if( !Comparer.equalsInt32( _functionalId, value ) ) {
            _functionalId = value;
            onPropertyChanged( );
        }
    }

    public String getData( ) {
        return _data;
    }
    public void setData( String value ) {
        if( !Comparer.equalsString( _data, value ) ) {
            _data = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( AisBinaryBroadcastMessageObject )target;
        targetObject._spare = this._spare;
        targetObject._designatedAreaCode = this._designatedAreaCode;
        targetObject._functionalId = this._functionalId;
        targetObject._data = this._data;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (AisBinaryBroadcastMessageObject)obj;
        if( !Comparer.equalsInt32( this._spare, other._spare ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._designatedAreaCode, other._designatedAreaCode ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._functionalId, other._functionalId ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._data, other._data ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt32( _spare );
        destination.writeInt32( _designatedAreaCode );
        destination.writeInt32( _functionalId );
        destination.writeStringUtf8( _data );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _spare = source.readInt32( );
        _designatedAreaCode = source.readInt32( );
        _functionalId = source.readInt32( );
        _data = source.readString( );
    }

}
