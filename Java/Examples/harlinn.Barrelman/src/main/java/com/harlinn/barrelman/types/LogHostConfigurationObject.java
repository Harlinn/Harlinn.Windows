package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class LogHostConfigurationObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _host;
    private DateTime _timestamp;
    private boolean _finest = false;
    private boolean _finer = false;
    private boolean _fine = false;
    private boolean _info = false;
    private boolean _notice = false;
    private boolean _warn = false;
    private boolean _error = false;
    private boolean _severe = false;
    private boolean _critical = false;
    private boolean _alert = false;
    private boolean _fatal = false;
    private boolean _emergency = false;

    @Override
    public int getObjectType( ) {
        return Kind.LogHostConfiguration;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new LogHostConfigurationObject( );
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

    public Guid getHost( ) {
        return _host;
    }
    public void setHost( Guid value ) {
        if( !Comparer.equalsGuid( _host, value ) ) {
            _host = value;
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

    public boolean getFinest( ) {
        return _finest;
    }
    public void setFinest( boolean value ) {
        if( !Comparer.equalsBoolean( _finest, value ) ) {
            _finest = value;
            onPropertyChanged( );
        }
    }

    public boolean getFiner( ) {
        return _finer;
    }
    public void setFiner( boolean value ) {
        if( !Comparer.equalsBoolean( _finer, value ) ) {
            _finer = value;
            onPropertyChanged( );
        }
    }

    public boolean getFine( ) {
        return _fine;
    }
    public void setFine( boolean value ) {
        if( !Comparer.equalsBoolean( _fine, value ) ) {
            _fine = value;
            onPropertyChanged( );
        }
    }

    public boolean getInfo( ) {
        return _info;
    }
    public void setInfo( boolean value ) {
        if( !Comparer.equalsBoolean( _info, value ) ) {
            _info = value;
            onPropertyChanged( );
        }
    }

    public boolean getNotice( ) {
        return _notice;
    }
    public void setNotice( boolean value ) {
        if( !Comparer.equalsBoolean( _notice, value ) ) {
            _notice = value;
            onPropertyChanged( );
        }
    }

    public boolean getWarn( ) {
        return _warn;
    }
    public void setWarn( boolean value ) {
        if( !Comparer.equalsBoolean( _warn, value ) ) {
            _warn = value;
            onPropertyChanged( );
        }
    }

    public boolean getError( ) {
        return _error;
    }
    public void setError( boolean value ) {
        if( !Comparer.equalsBoolean( _error, value ) ) {
            _error = value;
            onPropertyChanged( );
        }
    }

    public boolean getSevere( ) {
        return _severe;
    }
    public void setSevere( boolean value ) {
        if( !Comparer.equalsBoolean( _severe, value ) ) {
            _severe = value;
            onPropertyChanged( );
        }
    }

    public boolean getCritical( ) {
        return _critical;
    }
    public void setCritical( boolean value ) {
        if( !Comparer.equalsBoolean( _critical, value ) ) {
            _critical = value;
            onPropertyChanged( );
        }
    }

    public boolean getAlert( ) {
        return _alert;
    }
    public void setAlert( boolean value ) {
        if( !Comparer.equalsBoolean( _alert, value ) ) {
            _alert = value;
            onPropertyChanged( );
        }
    }

    public boolean getFatal( ) {
        return _fatal;
    }
    public void setFatal( boolean value ) {
        if( !Comparer.equalsBoolean( _fatal, value ) ) {
            _fatal = value;
            onPropertyChanged( );
        }
    }

    public boolean getEmergency( ) {
        return _emergency;
    }
    public void setEmergency( boolean value ) {
        if( !Comparer.equalsBoolean( _emergency, value ) ) {
            _emergency = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _host );
        destination.writeDateTime( _timestamp );
        destination.writeBoolean( _finest );
        destination.writeBoolean( _finer );
        destination.writeBoolean( _fine );
        destination.writeBoolean( _info );
        destination.writeBoolean( _notice );
        destination.writeBoolean( _warn );
        destination.writeBoolean( _error );
        destination.writeBoolean( _severe );
        destination.writeBoolean( _critical );
        destination.writeBoolean( _alert );
        destination.writeBoolean( _fatal );
        destination.writeBoolean( _emergency );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _host = source.readGuid( );
        _timestamp = source.readDateTime( );
        _finest = source.readBoolean( );
        _finer = source.readBoolean( );
        _fine = source.readBoolean( );
        _info = source.readBoolean( );
        _notice = source.readBoolean( );
        _warn = source.readBoolean( );
        _error = source.readBoolean( );
        _severe = source.readBoolean( );
        _critical = source.readBoolean( );
        _alert = source.readBoolean( );
        _fatal = source.readBoolean( );
        _emergency = source.readBoolean( );
    }

}
