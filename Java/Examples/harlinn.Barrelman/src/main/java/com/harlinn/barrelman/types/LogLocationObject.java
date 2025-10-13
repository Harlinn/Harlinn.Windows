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
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public String getFileName( ) {
        return _fileName;
    }
    public void setFileName( String value ) {
        if( _fileName != value ) {
            this._fileName = value;
            onPropertyChanged( );
        }
    }

    public int getLineNumber( ) {
        return _lineNumber;
    }
    public void setLineNumber( int value ) {
        if( _lineNumber != value ) {
            this._lineNumber = value;
            onPropertyChanged( );
        }
    }

    public String getNamespace( ) {
        return _namespace;
    }
    public void setNamespace( String value ) {
        if( _namespace != value ) {
            this._namespace = value;
            onPropertyChanged( );
        }
    }

    public String getClassName( ) {
        return _className;
    }
    public void setClassName( String value ) {
        if( _className != value ) {
            this._className = value;
            onPropertyChanged( );
        }
    }

    public String getMethodName( ) {
        return _methodName;
    }
    public void setMethodName( String value ) {
        if( _methodName != value ) {
            this._methodName = value;
            onPropertyChanged( );
        }
    }


}
