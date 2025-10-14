package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisAidToNavigationObject extends TrackableItemObject {

    private String _name = "";
    private Guid _mMSI;
    private int _navigationalAidType = NavigationalAidType.NotSpecified;
    private Guid _position;
    private boolean _isVirtual = false;
    private int _toBow = 0;
    private int _toStern = 0;
    private int _toPort = 0;
    private int _toStarboard = 0;
    private Guid _offPositionTimeseries;

    @Override
    public int getObjectType( ) {
        return Kind.AisAidToNavigation;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisAidToNavigationObject( );
    }

    public String getName( ) {
        return _name;
    }
    public void setName( String value ) {
        if( !Comparer.equalsString( _name, value ) ) {
            _name = value;
            onPropertyChanged( );
        }
    }

    public Guid getMMSI( ) {
        return _mMSI;
    }
    public void setMMSI( Guid value ) {
        if( !Comparer.equalsNullableGuid( _mMSI, value ) ) {
            _mMSI = value;
            onPropertyChanged( );
        }
    }

    public int getNavigationalAidType( ) {
        return _navigationalAidType;
    }
    public void setNavigationalAidType( int value ) {
        if( !Comparer.equalsInt32( _navigationalAidType, value ) ) {
            _navigationalAidType = value;
            onPropertyChanged( );
        }
    }

    public Guid getPosition( ) {
        return _position;
    }
    public void setPosition( Guid value ) {
        if( !Comparer.equalsNullableGuid( _position, value ) ) {
            _position = value;
            onPropertyChanged( );
        }
    }

    public boolean getIsVirtual( ) {
        return _isVirtual;
    }
    public void setIsVirtual( boolean value ) {
        if( !Comparer.equalsBoolean( _isVirtual, value ) ) {
            _isVirtual = value;
            onPropertyChanged( );
        }
    }

    public int getToBow( ) {
        return _toBow;
    }
    public void setToBow( int value ) {
        if( !Comparer.equalsInt32( _toBow, value ) ) {
            _toBow = value;
            onPropertyChanged( );
        }
    }

    public int getToStern( ) {
        return _toStern;
    }
    public void setToStern( int value ) {
        if( !Comparer.equalsInt32( _toStern, value ) ) {
            _toStern = value;
            onPropertyChanged( );
        }
    }

    public int getToPort( ) {
        return _toPort;
    }
    public void setToPort( int value ) {
        if( !Comparer.equalsInt32( _toPort, value ) ) {
            _toPort = value;
            onPropertyChanged( );
        }
    }

    public int getToStarboard( ) {
        return _toStarboard;
    }
    public void setToStarboard( int value ) {
        if( !Comparer.equalsInt32( _toStarboard, value ) ) {
            _toStarboard = value;
            onPropertyChanged( );
        }
    }

    public Guid getOffPositionTimeseries( ) {
        return _offPositionTimeseries;
    }
    public void setOffPositionTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _offPositionTimeseries, value ) ) {
            _offPositionTimeseries = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeStringUtf8( _name );
        destination.writeNullableGuid( _mMSI );
        destination.writeInt32( _navigationalAidType );
        destination.writeNullableGuid( _position );
        destination.writeBoolean( _isVirtual );
        destination.writeInt32( _toBow );
        destination.writeInt32( _toStern );
        destination.writeInt32( _toPort );
        destination.writeInt32( _toStarboard );
        destination.writeNullableGuid( _offPositionTimeseries );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _name = source.readString( );
        _mMSI = source.readNullableGuid( );
        _navigationalAidType = source.readInt32( );
        _position = source.readNullableGuid( );
        _isVirtual = source.readBoolean( );
        _toBow = source.readInt32( );
        _toStern = source.readInt32( );
        _toPort = source.readInt32( );
        _toStarboard = source.readInt32( );
        _offPositionTimeseries = source.readNullableGuid( );
    }

}
