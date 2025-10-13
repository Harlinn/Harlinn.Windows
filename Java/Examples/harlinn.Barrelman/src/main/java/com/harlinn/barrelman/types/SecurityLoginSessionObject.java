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
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getLogin( ) {
        return _login;
    }
    public void setLogin( Guid value ) {
        if( _login != value ) {
            this._login = value;
            onPropertyChanged( );
        }
    }

    public DateTime getFromTime( ) {
        return _fromTime;
    }
    public void setFromTime( DateTime value ) {
        if( _fromTime != value ) {
            this._fromTime = value;
            onPropertyChanged( );
        }
    }

    public DateTime getThroughTime( ) {
        return _throughTime;
    }
    public void setThroughTime( DateTime value ) {
        if( _throughTime != value ) {
            this._throughTime = value;
            onPropertyChanged( );
        }
    }

    public Guid getClientSession( ) {
        return _clientSession;
    }
    public void setClientSession( Guid value ) {
        if( _clientSession != value ) {
            this._clientSession = value;
            onPropertyChanged( );
        }
    }

    public String getNotificationQueueName( ) {
        return _notificationQueueName;
    }
    public void setNotificationQueueName( String value ) {
        if( _notificationQueueName != value ) {
            this._notificationQueueName = value;
            onPropertyChanged( );
        }
    }

    public String getMessageQueueName( ) {
        return _messageQueueName;
    }
    public void setMessageQueueName( String value ) {
        if( _messageQueueName != value ) {
            this._messageQueueName = value;
            onPropertyChanged( );
        }
    }


}
