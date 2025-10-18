package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SecurityLoginSessionObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.SecurityLoginSession;

    private long _rowVersion = 0;
    private Guid _login;
    private DateTime _fromTime;
    private DateTime _throughTime;
    private Guid _clientSession;
    private String _notificationQueueName = "";
    private String _messageQueueName = "";

    public SecurityLoginSessionObject( ) {
    }
    public SecurityLoginSessionObject( byte objectState, Guid id, long rowVersion, Guid login, DateTime fromTime, DateTime throughTime, Guid clientSession, String notificationQueueName, String messageQueueName ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._login = login;
        this._fromTime = fromTime;
        this._throughTime = throughTime;
        this._clientSession = clientSession;
        this._notificationQueueName = notificationQueueName;
        this._messageQueueName = messageQueueName;
    }

    @Override
    public int getObjectType( ) {
        return Kind.SecurityLoginSession;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new SecurityLoginSessionObject( );
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

    public Guid getLogin( ) {
        return _login;
    }
    public void setLogin( Guid value ) {
        if( !Comparer.equalsGuid( _login, value ) ) {
            _login = value;
            onPropertyChanged( );
        }
    }

    public DateTime getFromTime( ) {
        return _fromTime;
    }
    public void setFromTime( DateTime value ) {
        if( !Comparer.equalsDateTime( _fromTime, value ) ) {
            _fromTime = value;
            onPropertyChanged( );
        }
    }

    public DateTime getThroughTime( ) {
        return _throughTime;
    }
    public void setThroughTime( DateTime value ) {
        if( !Comparer.equalsNullableDateTime( _throughTime, value ) ) {
            _throughTime = value;
            onPropertyChanged( );
        }
    }

    public Guid getClientSession( ) {
        return _clientSession;
    }
    public void setClientSession( Guid value ) {
        if( !Comparer.equalsGuid( _clientSession, value ) ) {
            _clientSession = value;
            onPropertyChanged( );
        }
    }

    public String getNotificationQueueName( ) {
        return _notificationQueueName;
    }
    public void setNotificationQueueName( String value ) {
        if( !Comparer.equalsString( _notificationQueueName, value ) ) {
            _notificationQueueName = value;
            onPropertyChanged( );
        }
    }

    public String getMessageQueueName( ) {
        return _messageQueueName;
    }
    public void setMessageQueueName( String value ) {
        if( !Comparer.equalsString( _messageQueueName, value ) ) {
            _messageQueueName = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( SecurityLoginSessionObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._login = this._login;
        targetObject._fromTime = this._fromTime;
        targetObject._throughTime = this._throughTime;
        targetObject._clientSession = this._clientSession;
        targetObject._notificationQueueName = this._notificationQueueName;
        targetObject._messageQueueName = this._messageQueueName;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (SecurityLoginSessionObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._login, other._login ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._fromTime, other._fromTime ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDateTime( this._throughTime, other._throughTime ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._clientSession, other._clientSession ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._notificationQueueName, other._notificationQueueName ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._messageQueueName, other._messageQueueName ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _login );
        destination.writeDateTime( _fromTime );
        destination.writeNullableDateTime( _throughTime );
        destination.writeGuid( _clientSession );
        destination.writeStringUtf8( _notificationQueueName );
        destination.writeStringUtf8( _messageQueueName );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _login = source.readGuid( );
        _fromTime = source.readDateTime( );
        _throughTime = source.readNullableDateTime( );
        _clientSession = source.readGuid( );
        _notificationQueueName = source.readString( );
        _messageQueueName = source.readString( );
    }

}
