/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class LogHostConfigurationObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.LogHostConfiguration;

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

    public LogHostConfigurationObject( ) {
    }
    public LogHostConfigurationObject( byte objectState, Guid id, long rowVersion, Guid host, DateTime timestamp, boolean finest, boolean finer, boolean fine, boolean info, boolean notice, boolean warn, boolean error, boolean severe, boolean critical, boolean alert, boolean fatal, boolean emergency ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._host = host;
        this._timestamp = timestamp;
        this._finest = finest;
        this._finer = finer;
        this._fine = fine;
        this._info = info;
        this._notice = notice;
        this._warn = warn;
        this._error = error;
        this._severe = severe;
        this._critical = critical;
        this._alert = alert;
        this._fatal = fatal;
        this._emergency = emergency;
    }

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
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( LogHostConfigurationObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._host = this._host;
        targetObject._timestamp = this._timestamp;
        targetObject._finest = this._finest;
        targetObject._finer = this._finer;
        targetObject._fine = this._fine;
        targetObject._info = this._info;
        targetObject._notice = this._notice;
        targetObject._warn = this._warn;
        targetObject._error = this._error;
        targetObject._severe = this._severe;
        targetObject._critical = this._critical;
        targetObject._alert = this._alert;
        targetObject._fatal = this._fatal;
        targetObject._emergency = this._emergency;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (LogHostConfigurationObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._host, other._host ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._finest, other._finest ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._finer, other._finer ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._fine, other._fine ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._info, other._info ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._notice, other._notice ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._warn, other._warn ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._error, other._error ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._severe, other._severe ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._critical, other._critical ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._alert, other._alert ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._fatal, other._fatal ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._emergency, other._emergency ) ) {
            return false;
        }
        return true;
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
