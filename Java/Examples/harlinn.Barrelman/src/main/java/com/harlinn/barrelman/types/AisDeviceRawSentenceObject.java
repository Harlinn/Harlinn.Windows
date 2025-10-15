package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisDeviceRawSentenceObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _aisDevice;
    private DateTime _timestamp;
    private String _sentence = "";

    @Override
    public int getObjectType( ) {
        return Kind.AisDeviceRawSentence;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisDeviceRawSentenceObject( );
    }

    public long getRowVersion( ) {
        return _rowVersion;
    }
    public void setRowVersion( long value ) {
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getAisDevice( ) {
        return _aisDevice;
    }
    public void setAisDevice( Guid value ) {
        if( !Comparer.equalsGuid( _aisDevice, value ) ) {
            _aisDevice = value;
            onPropertyChanged( );
        }
    }

    public DateTime getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( DateTime value ) {
        if( !Comparer.equalsDateTime( _timestamp, value ) ) {
            _timestamp = value;
            onPropertyChanged( );
        }
    }

    public String getSentence( ) {
        return _sentence;
    }
    public void setSentence( String value ) {
        if( !Comparer.equalsString( _sentence, value ) ) {
            _sentence = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( AisDeviceRawSentenceObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._aisDevice = this._aisDevice;
        targetObject._timestamp = this._timestamp;
        targetObject._sentence = this._sentence;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (AisDeviceRawSentenceObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._aisDevice, other._aisDevice ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._sentence, other._sentence ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _aisDevice );
        destination.writeDateTime( _timestamp );
        destination.writeStringUtf8( _sentence );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _aisDevice = source.readGuid( );
        _timestamp = source.readDateTime( );
        _sentence = source.readString( );
    }

}
