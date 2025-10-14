package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisBinaryBroadcastMessageObject extends AisMessageObject {

    private int _spare = 0;
    private int _designatedAreaCode = 0;
    private int _functionalId = 0;
    private String _data = "";

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
