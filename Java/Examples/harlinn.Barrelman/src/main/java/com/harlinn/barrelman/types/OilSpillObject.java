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

public class OilSpillObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.OilSpill;

    private long _rowVersion = 0;
    private Guid _oilSpillDetector;
    private DateTime _timestamp;
    private double _oilArea = 0.0;
    private byte[] _shape = new byte[0];
    private byte[] _bSI = new byte[0];
    private byte[] _oil = new byte[0];
    private byte[] _trace = new byte[0];

    public OilSpillObject( ) {
    }
    public OilSpillObject( byte objectState, Guid id, long rowVersion, Guid oilSpillDetector, DateTime timestamp, double oilArea, byte[] shape, byte[] bSI, byte[] oil, byte[] trace ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._oilSpillDetector = oilSpillDetector;
        this._timestamp = timestamp;
        this._oilArea = oilArea;
        this._shape = shape;
        this._bSI = bSI;
        this._oil = oil;
        this._trace = trace;
    }

    @Override
    public int getObjectType( ) {
        return Kind.OilSpill;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new OilSpillObject( );
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

    public Guid getOilSpillDetector( ) {
        return _oilSpillDetector;
    }
    public void setOilSpillDetector( Guid value ) {
        if( !Comparer.equalsGuid( _oilSpillDetector, value ) ) {
            _oilSpillDetector = value;
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

    public double getOilArea( ) {
        return _oilArea;
    }
    public void setOilArea( double value ) {
        if( !Comparer.equalsDouble( _oilArea, value ) ) {
            _oilArea = value;
            onPropertyChanged( );
        }
    }

    public byte[] getShape( ) {
        return _shape;
    }
    public void setShape( byte[] value ) {
        if( !Comparer.equalsUInt8Array( _shape, value ) ) {
            _shape = value != null ? value.clone() : value;;
            onPropertyChanged( );
        }
    }

    public byte[] getBSI( ) {
        return _bSI;
    }
    public void setBSI( byte[] value ) {
        if( !Comparer.equalsUInt8Array( _bSI, value ) ) {
            _bSI = value != null ? value.clone() : value;;
            onPropertyChanged( );
        }
    }

    public byte[] getOil( ) {
        return _oil;
    }
    public void setOil( byte[] value ) {
        if( !Comparer.equalsUInt8Array( _oil, value ) ) {
            _oil = value != null ? value.clone() : value;;
            onPropertyChanged( );
        }
    }

    public byte[] getTrace( ) {
        return _trace;
    }
    public void setTrace( byte[] value ) {
        if( !Comparer.equalsUInt8Array( _trace, value ) ) {
            _trace = value != null ? value.clone() : value;;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( OilSpillObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._oilSpillDetector = this._oilSpillDetector;
        targetObject._timestamp = this._timestamp;
        targetObject._oilArea = this._oilArea;
        targetObject._shape = this._shape != null ? this._shape.clone() : this._shape;;
        targetObject._bSI = this._bSI != null ? this._bSI.clone() : this._bSI;;
        targetObject._oil = this._oil != null ? this._oil.clone() : this._oil;;
        targetObject._trace = this._trace != null ? this._trace.clone() : this._trace;;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (OilSpillObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._oilSpillDetector, other._oilSpillDetector ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._oilArea, other._oilArea ) ) {
            return false;
        }
        if( !Comparer.equalsUInt8Array( this._shape, other._shape ) ) {
            return false;
        }
        if( !Comparer.equalsUInt8Array( this._bSI, other._bSI ) ) {
            return false;
        }
        if( !Comparer.equalsUInt8Array( this._oil, other._oil ) ) {
            return false;
        }
        if( !Comparer.equalsUInt8Array( this._trace, other._trace ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _oilSpillDetector );
        destination.writeDateTime( _timestamp );
        destination.writeDouble( _oilArea );
        destination.writeUInt8Array( _shape );
        destination.writeUInt8Array( _bSI );
        destination.writeUInt8Array( _oil );
        destination.writeUInt8Array( _trace );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _oilSpillDetector = source.readGuid( );
        _timestamp = source.readDateTime( );
        _oilArea = source.readDouble( );
        _shape = source.readUInt8Array( );
        _bSI = source.readUInt8Array( );
        _oil = source.readUInt8Array( );
        _trace = source.readUInt8Array( );
    }

}
