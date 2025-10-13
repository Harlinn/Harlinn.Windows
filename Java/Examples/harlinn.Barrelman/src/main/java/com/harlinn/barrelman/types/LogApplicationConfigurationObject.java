package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class LogApplicationConfigurationObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _application;
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
        return Kind.LogApplicationConfiguration;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new LogApplicationConfigurationObject( );
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

    public Guid getApplication( ) {
        return _application;
    }
    public void setApplication( Guid value ) {
        if( _application != value ) {
            this._application = value;
            onPropertyChanged( );
        }
    }

    public DateTime getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( DateTime value ) {
        if( _timestamp != value ) {
            this._timestamp = value;
            onPropertyChanged( );
        }
    }

    public boolean getFinest( ) {
        return _finest;
    }
    public void setFinest( boolean value ) {
        if( _finest != value ) {
            this._finest = value;
            onPropertyChanged( );
        }
    }

    public boolean getFiner( ) {
        return _finer;
    }
    public void setFiner( boolean value ) {
        if( _finer != value ) {
            this._finer = value;
            onPropertyChanged( );
        }
    }

    public boolean getFine( ) {
        return _fine;
    }
    public void setFine( boolean value ) {
        if( _fine != value ) {
            this._fine = value;
            onPropertyChanged( );
        }
    }

    public boolean getInfo( ) {
        return _info;
    }
    public void setInfo( boolean value ) {
        if( _info != value ) {
            this._info = value;
            onPropertyChanged( );
        }
    }

    public boolean getNotice( ) {
        return _notice;
    }
    public void setNotice( boolean value ) {
        if( _notice != value ) {
            this._notice = value;
            onPropertyChanged( );
        }
    }

    public boolean getWarn( ) {
        return _warn;
    }
    public void setWarn( boolean value ) {
        if( _warn != value ) {
            this._warn = value;
            onPropertyChanged( );
        }
    }

    public boolean getError( ) {
        return _error;
    }
    public void setError( boolean value ) {
        if( _error != value ) {
            this._error = value;
            onPropertyChanged( );
        }
    }

    public boolean getSevere( ) {
        return _severe;
    }
    public void setSevere( boolean value ) {
        if( _severe != value ) {
            this._severe = value;
            onPropertyChanged( );
        }
    }

    public boolean getCritical( ) {
        return _critical;
    }
    public void setCritical( boolean value ) {
        if( _critical != value ) {
            this._critical = value;
            onPropertyChanged( );
        }
    }

    public boolean getAlert( ) {
        return _alert;
    }
    public void setAlert( boolean value ) {
        if( _alert != value ) {
            this._alert = value;
            onPropertyChanged( );
        }
    }

    public boolean getFatal( ) {
        return _fatal;
    }
    public void setFatal( boolean value ) {
        if( _fatal != value ) {
            this._fatal = value;
            onPropertyChanged( );
        }
    }

    public boolean getEmergency( ) {
        return _emergency;
    }
    public void setEmergency( boolean value ) {
        if( _emergency != value ) {
            this._emergency = value;
            onPropertyChanged( );
        }
    }


}
