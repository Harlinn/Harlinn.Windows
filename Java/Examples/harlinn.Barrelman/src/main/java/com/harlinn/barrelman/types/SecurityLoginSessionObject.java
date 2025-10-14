package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SecurityLoginSessionObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _login;
    private DateTime _fromTime;
    private DateTime _throughTime;
    private Guid _clientSession;
    private String _notificationQueueName = "";
    private String _messageQueueName = "";

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
