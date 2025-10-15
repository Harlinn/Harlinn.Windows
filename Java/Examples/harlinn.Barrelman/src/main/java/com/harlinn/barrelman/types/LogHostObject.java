package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class LogHostObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private String _computerName = "";
    private String _description = "";

    @Override
    public int getObjectType( ) {
        return Kind.LogHost;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new LogHostObject( );
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

    public String getComputerName( ) {
        return _computerName;
    }
    public void setComputerName( String value ) {
        if( !Comparer.equalsString( _computerName, value ) ) {
            _computerName = value;
            onPropertyChanged( );
        }
    }

    public String getDescription( ) {
        return _description;
    }
    public void setDescription( String value ) {
        if( !Comparer.equalsString( _description, value ) ) {
            _description = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( LogHostObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._computerName = this._computerName;
        targetObject._description = this._description;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (LogHostObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._computerName, other._computerName ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._description, other._description ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeStringUtf8( _computerName );
        destination.writeStringUtf8( _description );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _computerName = source.readString( );
        _description = source.readString( );
    }

}
