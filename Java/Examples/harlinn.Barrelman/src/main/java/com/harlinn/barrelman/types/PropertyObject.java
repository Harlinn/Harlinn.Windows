package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class PropertyObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _element;
    private Guid _definition;


    public long getRowVersion( ) {
        return _rowVersion;
    }
    public void setRowVersion( long value ) {
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getElement( ) {
        return _element;
    }
    public void setElement( Guid value ) {
        if( !Comparer.equalsGuid( _element, value ) ) {
            _element = value;
            onPropertyChanged( );
        }
    }

    public Guid getDefinition( ) {
        return _definition;
    }
    public void setDefinition( Guid value ) {
        if( !Comparer.equalsGuid( _definition, value ) ) {
            _definition = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( PropertyObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._element = this._element;
        targetObject._definition = this._definition;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (PropertyObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._element, other._element ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._definition, other._definition ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _element );
        destination.writeGuid( _definition );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _element = source.readGuid( );
        _definition = source.readGuid( );
    }

}
