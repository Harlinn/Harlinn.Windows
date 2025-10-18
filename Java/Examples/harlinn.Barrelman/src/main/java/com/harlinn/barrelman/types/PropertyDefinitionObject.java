package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class PropertyDefinitionObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.PropertyDefinition;

    private long _rowVersion = 0;
    private Guid _elementType;
    private String _name = "";
    private String _description = "";

    public PropertyDefinitionObject( ) {
    }
    public PropertyDefinitionObject( byte objectState, Guid id, long rowVersion, Guid elementType, String name, String description ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._elementType = elementType;
        this._name = name;
        this._description = description;
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

    public Guid getElementType( ) {
        return _elementType;
    }
    public void setElementType( Guid value ) {
        if( !Comparer.equalsGuid( _elementType, value ) ) {
            _elementType = value;
            onPropertyChanged( );
        }
    }

    public String getName( ) {
        return _name;
    }
    public void setName( String value ) {
        if( !Comparer.equalsString( _name, value ) ) {
            _name = value;
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
        var targetObject = ( PropertyDefinitionObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._elementType = this._elementType;
        targetObject._name = this._name;
        targetObject._description = this._description;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (PropertyDefinitionObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._elementType, other._elementType ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._name, other._name ) ) {
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
        destination.writeGuid( _elementType );
        destination.writeStringUtf8( _name );
        destination.writeStringUtf8( _description );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _elementType = source.readGuid( );
        _name = source.readString( );
        _description = source.readString( );
    }

}
