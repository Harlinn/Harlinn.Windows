package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisDataLinkManagementMessageObject extends AisMessageObject {

    private int _spare = 0;
    private int _offset1 = 0;
    private int _reservedSlots1 = 0;
    private int _timeout1 = 0;
    private int _increment1 = 0;
    private Integer _offset2;
    private Integer _reservedSlots2;
    private Integer _timeout2;
    private Integer _increment2;
    private Integer _offset3;
    private Integer _reservedSlots3;
    private Integer _timeout3;
    private Integer _increment3;
    private Integer _offset4;
    private Integer _reservedSlots4;
    private Integer _timeout4;
    private Integer _increment4;

    @Override
    public int getObjectType( ) {
        return Kind.AisDataLinkManagementMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisDataLinkManagementMessageObject( );
    }

    public int getSpare( ) {
        return _spare;
    }
    public void setSpare( int value ) {
        if( !Comparer.equalsInt32( _spare, value ) ) {
            _spare = value;
            onPropertyChanged( );
        }
    }

    public int getOffset1( ) {
        return _offset1;
    }
    public void setOffset1( int value ) {
        if( !Comparer.equalsInt32( _offset1, value ) ) {
            _offset1 = value;
            onPropertyChanged( );
        }
    }

    public int getReservedSlots1( ) {
        return _reservedSlots1;
    }
    public void setReservedSlots1( int value ) {
        if( !Comparer.equalsInt32( _reservedSlots1, value ) ) {
            _reservedSlots1 = value;
            onPropertyChanged( );
        }
    }

    public int getTimeout1( ) {
        return _timeout1;
    }
    public void setTimeout1( int value ) {
        if( !Comparer.equalsInt32( _timeout1, value ) ) {
            _timeout1 = value;
            onPropertyChanged( );
        }
    }

    public int getIncrement1( ) {
        return _increment1;
    }
    public void setIncrement1( int value ) {
        if( !Comparer.equalsInt32( _increment1, value ) ) {
            _increment1 = value;
            onPropertyChanged( );
        }
    }

    public Integer getOffset2( ) {
        return _offset2;
    }
    public void setOffset2( Integer value ) {
        if( !Comparer.equalsNullableInt32( _offset2, value ) ) {
            _offset2 = value;
            onPropertyChanged( );
        }
    }

    public Integer getReservedSlots2( ) {
        return _reservedSlots2;
    }
    public void setReservedSlots2( Integer value ) {
        if( !Comparer.equalsNullableInt32( _reservedSlots2, value ) ) {
            _reservedSlots2 = value;
            onPropertyChanged( );
        }
    }

    public Integer getTimeout2( ) {
        return _timeout2;
    }
    public void setTimeout2( Integer value ) {
        if( !Comparer.equalsNullableInt32( _timeout2, value ) ) {
            _timeout2 = value;
            onPropertyChanged( );
        }
    }

    public Integer getIncrement2( ) {
        return _increment2;
    }
    public void setIncrement2( Integer value ) {
        if( !Comparer.equalsNullableInt32( _increment2, value ) ) {
            _increment2 = value;
            onPropertyChanged( );
        }
    }

    public Integer getOffset3( ) {
        return _offset3;
    }
    public void setOffset3( Integer value ) {
        if( !Comparer.equalsNullableInt32( _offset3, value ) ) {
            _offset3 = value;
            onPropertyChanged( );
        }
    }

    public Integer getReservedSlots3( ) {
        return _reservedSlots3;
    }
    public void setReservedSlots3( Integer value ) {
        if( !Comparer.equalsNullableInt32( _reservedSlots3, value ) ) {
            _reservedSlots3 = value;
            onPropertyChanged( );
        }
    }

    public Integer getTimeout3( ) {
        return _timeout3;
    }
    public void setTimeout3( Integer value ) {
        if( !Comparer.equalsNullableInt32( _timeout3, value ) ) {
            _timeout3 = value;
            onPropertyChanged( );
        }
    }

    public Integer getIncrement3( ) {
        return _increment3;
    }
    public void setIncrement3( Integer value ) {
        if( !Comparer.equalsNullableInt32( _increment3, value ) ) {
            _increment3 = value;
            onPropertyChanged( );
        }
    }

    public Integer getOffset4( ) {
        return _offset4;
    }
    public void setOffset4( Integer value ) {
        if( !Comparer.equalsNullableInt32( _offset4, value ) ) {
            _offset4 = value;
            onPropertyChanged( );
        }
    }

    public Integer getReservedSlots4( ) {
        return _reservedSlots4;
    }
    public void setReservedSlots4( Integer value ) {
        if( !Comparer.equalsNullableInt32( _reservedSlots4, value ) ) {
            _reservedSlots4 = value;
            onPropertyChanged( );
        }
    }

    public Integer getTimeout4( ) {
        return _timeout4;
    }
    public void setTimeout4( Integer value ) {
        if( !Comparer.equalsNullableInt32( _timeout4, value ) ) {
            _timeout4 = value;
            onPropertyChanged( );
        }
    }

    public Integer getIncrement4( ) {
        return _increment4;
    }
    public void setIncrement4( Integer value ) {
        if( !Comparer.equalsNullableInt32( _increment4, value ) ) {
            _increment4 = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( AisDataLinkManagementMessageObject )target;
        targetObject._spare = this._spare;
        targetObject._offset1 = this._offset1;
        targetObject._reservedSlots1 = this._reservedSlots1;
        targetObject._timeout1 = this._timeout1;
        targetObject._increment1 = this._increment1;
        targetObject._offset2 = this._offset2;
        targetObject._reservedSlots2 = this._reservedSlots2;
        targetObject._timeout2 = this._timeout2;
        targetObject._increment2 = this._increment2;
        targetObject._offset3 = this._offset3;
        targetObject._reservedSlots3 = this._reservedSlots3;
        targetObject._timeout3 = this._timeout3;
        targetObject._increment3 = this._increment3;
        targetObject._offset4 = this._offset4;
        targetObject._reservedSlots4 = this._reservedSlots4;
        targetObject._timeout4 = this._timeout4;
        targetObject._increment4 = this._increment4;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (AisDataLinkManagementMessageObject)obj;
        if( !Comparer.equalsInt32( this._spare, other._spare ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._offset1, other._offset1 ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._reservedSlots1, other._reservedSlots1 ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._timeout1, other._timeout1 ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._increment1, other._increment1 ) ) {
            return false;
        }
        if( !Comparer.equalsNullableInt32( this._offset2, other._offset2 ) ) {
            return false;
        }
        if( !Comparer.equalsNullableInt32( this._reservedSlots2, other._reservedSlots2 ) ) {
            return false;
        }
        if( !Comparer.equalsNullableInt32( this._timeout2, other._timeout2 ) ) {
            return false;
        }
        if( !Comparer.equalsNullableInt32( this._increment2, other._increment2 ) ) {
            return false;
        }
        if( !Comparer.equalsNullableInt32( this._offset3, other._offset3 ) ) {
            return false;
        }
        if( !Comparer.equalsNullableInt32( this._reservedSlots3, other._reservedSlots3 ) ) {
            return false;
        }
        if( !Comparer.equalsNullableInt32( this._timeout3, other._timeout3 ) ) {
            return false;
        }
        if( !Comparer.equalsNullableInt32( this._increment3, other._increment3 ) ) {
            return false;
        }
        if( !Comparer.equalsNullableInt32( this._offset4, other._offset4 ) ) {
            return false;
        }
        if( !Comparer.equalsNullableInt32( this._reservedSlots4, other._reservedSlots4 ) ) {
            return false;
        }
        if( !Comparer.equalsNullableInt32( this._timeout4, other._timeout4 ) ) {
            return false;
        }
        if( !Comparer.equalsNullableInt32( this._increment4, other._increment4 ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt32( _spare );
        destination.writeInt32( _offset1 );
        destination.writeInt32( _reservedSlots1 );
        destination.writeInt32( _timeout1 );
        destination.writeInt32( _increment1 );
        destination.writeNullableInt32( _offset2 );
        destination.writeNullableInt32( _reservedSlots2 );
        destination.writeNullableInt32( _timeout2 );
        destination.writeNullableInt32( _increment2 );
        destination.writeNullableInt32( _offset3 );
        destination.writeNullableInt32( _reservedSlots3 );
        destination.writeNullableInt32( _timeout3 );
        destination.writeNullableInt32( _increment3 );
        destination.writeNullableInt32( _offset4 );
        destination.writeNullableInt32( _reservedSlots4 );
        destination.writeNullableInt32( _timeout4 );
        destination.writeNullableInt32( _increment4 );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _spare = source.readInt32( );
        _offset1 = source.readInt32( );
        _reservedSlots1 = source.readInt32( );
        _timeout1 = source.readInt32( );
        _increment1 = source.readInt32( );
        _offset2 = source.readNullableInt32( );
        _reservedSlots2 = source.readNullableInt32( );
        _timeout2 = source.readNullableInt32( );
        _increment2 = source.readNullableInt32( );
        _offset3 = source.readNullableInt32( );
        _reservedSlots3 = source.readNullableInt32( );
        _timeout3 = source.readNullableInt32( );
        _increment3 = source.readNullableInt32( );
        _offset4 = source.readNullableInt32( );
        _reservedSlots4 = source.readNullableInt32( );
        _timeout4 = source.readNullableInt32( );
        _increment4 = source.readNullableInt32( );
    }

}
