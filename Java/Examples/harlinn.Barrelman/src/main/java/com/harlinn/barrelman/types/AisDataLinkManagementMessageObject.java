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
        if( _spare != value ) {
            this._spare = value;
            onPropertyChanged( );
        }
    }

    public int getOffset1( ) {
        return _offset1;
    }
    public void setOffset1( int value ) {
        if( _offset1 != value ) {
            this._offset1 = value;
            onPropertyChanged( );
        }
    }

    public int getReservedSlots1( ) {
        return _reservedSlots1;
    }
    public void setReservedSlots1( int value ) {
        if( _reservedSlots1 != value ) {
            this._reservedSlots1 = value;
            onPropertyChanged( );
        }
    }

    public int getTimeout1( ) {
        return _timeout1;
    }
    public void setTimeout1( int value ) {
        if( _timeout1 != value ) {
            this._timeout1 = value;
            onPropertyChanged( );
        }
    }

    public int getIncrement1( ) {
        return _increment1;
    }
    public void setIncrement1( int value ) {
        if( _increment1 != value ) {
            this._increment1 = value;
            onPropertyChanged( );
        }
    }

    public Integer getOffset2( ) {
        return _offset2;
    }
    public void setOffset2( Integer value ) {
        if( _offset2 != value ) {
            this._offset2 = value;
            onPropertyChanged( );
        }
    }

    public Integer getReservedSlots2( ) {
        return _reservedSlots2;
    }
    public void setReservedSlots2( Integer value ) {
        if( _reservedSlots2 != value ) {
            this._reservedSlots2 = value;
            onPropertyChanged( );
        }
    }

    public Integer getTimeout2( ) {
        return _timeout2;
    }
    public void setTimeout2( Integer value ) {
        if( _timeout2 != value ) {
            this._timeout2 = value;
            onPropertyChanged( );
        }
    }

    public Integer getIncrement2( ) {
        return _increment2;
    }
    public void setIncrement2( Integer value ) {
        if( _increment2 != value ) {
            this._increment2 = value;
            onPropertyChanged( );
        }
    }

    public Integer getOffset3( ) {
        return _offset3;
    }
    public void setOffset3( Integer value ) {
        if( _offset3 != value ) {
            this._offset3 = value;
            onPropertyChanged( );
        }
    }

    public Integer getReservedSlots3( ) {
        return _reservedSlots3;
    }
    public void setReservedSlots3( Integer value ) {
        if( _reservedSlots3 != value ) {
            this._reservedSlots3 = value;
            onPropertyChanged( );
        }
    }

    public Integer getTimeout3( ) {
        return _timeout3;
    }
    public void setTimeout3( Integer value ) {
        if( _timeout3 != value ) {
            this._timeout3 = value;
            onPropertyChanged( );
        }
    }

    public Integer getIncrement3( ) {
        return _increment3;
    }
    public void setIncrement3( Integer value ) {
        if( _increment3 != value ) {
            this._increment3 = value;
            onPropertyChanged( );
        }
    }

    public Integer getOffset4( ) {
        return _offset4;
    }
    public void setOffset4( Integer value ) {
        if( _offset4 != value ) {
            this._offset4 = value;
            onPropertyChanged( );
        }
    }

    public Integer getReservedSlots4( ) {
        return _reservedSlots4;
    }
    public void setReservedSlots4( Integer value ) {
        if( _reservedSlots4 != value ) {
            this._reservedSlots4 = value;
            onPropertyChanged( );
        }
    }

    public Integer getTimeout4( ) {
        return _timeout4;
    }
    public void setTimeout4( Integer value ) {
        if( _timeout4 != value ) {
            this._timeout4 = value;
            onPropertyChanged( );
        }
    }

    public Integer getIncrement4( ) {
        return _increment4;
    }
    public void setIncrement4( Integer value ) {
        if( _increment4 != value ) {
            this._increment4 = value;
            onPropertyChanged( );
        }
    }


}
