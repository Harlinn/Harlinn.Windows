package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class LogLocationObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private String _fileName = "";
    private int _lineNumber = 0;
    private String _namespace = "";
    private String _className = "";
    private String _methodName = "";

    @Override
    public int getObjectType( ) {
        return Kind.LogLocation;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new LogLocationObject( );
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

    public String getFileName( ) {
        return _fileName;
    }
    public void setFileName( String value ) {
        if( !Comparer.equalsString( _fileName, value ) ) {
            _fileName = value;
            onPropertyChanged( );
        }
    }

    public int getLineNumber( ) {
        return _lineNumber;
    }
    public void setLineNumber( int value ) {
        if( !Comparer.equalsInt32( _lineNumber, value ) ) {
            _lineNumber = value;
            onPropertyChanged( );
        }
    }

    public String getNamespace( ) {
        return _namespace;
    }
    public void setNamespace( String value ) {
        if( !Comparer.equalsString( _namespace, value ) ) {
            _namespace = value;
            onPropertyChanged( );
        }
    }

    public String getClassName( ) {
        return _className;
    }
    public void setClassName( String value ) {
        if( !Comparer.equalsString( _className, value ) ) {
            _className = value;
            onPropertyChanged( );
        }
    }

    public String getMethodName( ) {
        return _methodName;
    }
    public void setMethodName( String value ) {
        if( !Comparer.equalsString( _methodName, value ) ) {
            _methodName = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeStringUtf8( _fileName );
        destination.writeInt32( _lineNumber );
        destination.writeStringUtf8( _namespace );
        destination.writeStringUtf8( _className );
        destination.writeStringUtf8( _methodName );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _fileName = source.readString( );
        _lineNumber = source.readInt32( );
        _namespace = source.readString( );
        _className = source.readString( );
        _methodName = source.readString( );
    }

}
