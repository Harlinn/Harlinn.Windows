package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class LogTraceEntryObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _thread;
    private long _sequenceNumber = 0;
    private Guid _location;
    private int _depth = 0;
    private DateTime _entered;
    private DateTime _ended;

    @Override
    public int getObjectType( ) {
        return Kind.LogTraceEntry;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new LogTraceEntryObject( );
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

    public Guid getThread( ) {
        return _thread;
    }
    public void setThread( Guid value ) {
        if( !Comparer.equalsGuid( _thread, value ) ) {
            _thread = value;
            onPropertyChanged( );
        }
    }

    public long getSequenceNumber( ) {
        return _sequenceNumber;
    }
    public void setSequenceNumber( long value ) {
        if( !Comparer.equalsInt64( _sequenceNumber, value ) ) {
            _sequenceNumber = value;
            onPropertyChanged( );
        }
    }

    public Guid getLocation( ) {
        return _location;
    }
    public void setLocation( Guid value ) {
        if( !Comparer.equalsGuid( _location, value ) ) {
            _location = value;
            onPropertyChanged( );
        }
    }

    public int getDepth( ) {
        return _depth;
    }
    public void setDepth( int value ) {
        if( !Comparer.equalsInt32( _depth, value ) ) {
            _depth = value;
            onPropertyChanged( );
        }
    }

    public DateTime getEntered( ) {
        return _entered;
    }
    public void setEntered( DateTime value ) {
        if( !Comparer.equalsDateTime( _entered, value ) ) {
            _entered = value;
            onPropertyChanged( );
        }
    }

    public DateTime getEnded( ) {
        return _ended;
    }
    public void setEnded( DateTime value ) {
        if( !Comparer.equalsNullableDateTime( _ended, value ) ) {
            _ended = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _thread );
        destination.writeInt64( _sequenceNumber );
        destination.writeGuid( _location );
        destination.writeInt32( _depth );
        destination.writeDateTime( _entered );
        destination.writeNullableDateTime( _ended );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _thread = source.readGuid( );
        _sequenceNumber = source.readInt64( );
        _location = source.readGuid( );
        _depth = source.readInt32( );
        _entered = source.readDateTime( );
        _ended = source.readNullableDateTime( );
    }

}
