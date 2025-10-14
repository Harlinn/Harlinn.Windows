package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GuidPropertyDefinitionObject extends PropertyDefinitionObject {

    private Guid _defaultValue;

    @Override
    public int getObjectType( ) {
        return Kind.GuidPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new GuidPropertyDefinitionObject( );
    }

    public Guid getDefaultValue( ) {
        return _defaultValue;
    }
    public void setDefaultValue( Guid value ) {
        if( !Comparer.equalsGuid( _defaultValue, value ) ) {
            _defaultValue = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeGuid( _defaultValue );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _defaultValue = source.readGuid( );
    }

}
