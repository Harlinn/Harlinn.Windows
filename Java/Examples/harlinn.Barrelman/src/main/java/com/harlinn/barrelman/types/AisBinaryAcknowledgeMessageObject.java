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

public class AisBinaryAcknowledgeMessageObject extends AisMessageObject {

    public final int KIND = Kind.AisBinaryAcknowledgeMessage;

    private int _spare = 0;
    private int _sequenceNumber1 = 0;
    private Guid _mmsi1;
    private Integer _sequenceNumber2;
    private Guid _mmsi2;
    private Integer _sequenceNumber3;
    private Guid _mmsi3;
    private Integer _sequenceNumber4;
    private Guid _mmsi4;

    public AisBinaryAcknowledgeMessageObject( ) {
    }
    public AisBinaryAcknowledgeMessageObject( byte objectState, Guid id, long rowVersion, Guid aisDevice, DateTime receivedTimestamp, long messageSequenceNumber, int repeat, Guid mmsi, int spare, int sequenceNumber1, Guid mmsi1, Integer sequenceNumber2, Guid mmsi2, Integer sequenceNumber3, Guid mmsi3, Integer sequenceNumber4, Guid mmsi4 ) {
        super( objectState, id, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi );
        this._spare = spare;
        this._sequenceNumber1 = sequenceNumber1;
        this._mmsi1 = mmsi1;
        this._sequenceNumber2 = sequenceNumber2;
        this._mmsi2 = mmsi2;
        this._sequenceNumber3 = sequenceNumber3;
        this._mmsi3 = mmsi3;
        this._sequenceNumber4 = sequenceNumber4;
        this._mmsi4 = mmsi4;
    }

    @Override
    public int getObjectType( ) {
        return Kind.AisBinaryAcknowledgeMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisBinaryAcknowledgeMessageObject( );
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

    public int getSequenceNumber1( ) {
        return _sequenceNumber1;
    }
    public void setSequenceNumber1( int value ) {
        if( !Comparer.equalsInt32( _sequenceNumber1, value ) ) {
            _sequenceNumber1 = value;
            onPropertyChanged( );
        }
    }

    public Guid getMmsi1( ) {
        return _mmsi1;
    }
    public void setMmsi1( Guid value ) {
        if( !Comparer.equalsNullableGuid( _mmsi1, value ) ) {
            _mmsi1 = value;
            onPropertyChanged( );
        }
    }

    public Integer getSequenceNumber2( ) {
        return _sequenceNumber2;
    }
    public void setSequenceNumber2( Integer value ) {
        if( !Comparer.equalsNullableInt32( _sequenceNumber2, value ) ) {
            _sequenceNumber2 = value;
            onPropertyChanged( );
        }
    }

    public Guid getMmsi2( ) {
        return _mmsi2;
    }
    public void setMmsi2( Guid value ) {
        if( !Comparer.equalsNullableGuid( _mmsi2, value ) ) {
            _mmsi2 = value;
            onPropertyChanged( );
        }
    }

    public Integer getSequenceNumber3( ) {
        return _sequenceNumber3;
    }
    public void setSequenceNumber3( Integer value ) {
        if( !Comparer.equalsNullableInt32( _sequenceNumber3, value ) ) {
            _sequenceNumber3 = value;
            onPropertyChanged( );
        }
    }

    public Guid getMmsi3( ) {
        return _mmsi3;
    }
    public void setMmsi3( Guid value ) {
        if( !Comparer.equalsNullableGuid( _mmsi3, value ) ) {
            _mmsi3 = value;
            onPropertyChanged( );
        }
    }

    public Integer getSequenceNumber4( ) {
        return _sequenceNumber4;
    }
    public void setSequenceNumber4( Integer value ) {
        if( !Comparer.equalsNullableInt32( _sequenceNumber4, value ) ) {
            _sequenceNumber4 = value;
            onPropertyChanged( );
        }
    }

    public Guid getMmsi4( ) {
        return _mmsi4;
    }
    public void setMmsi4( Guid value ) {
        if( !Comparer.equalsNullableGuid( _mmsi4, value ) ) {
            _mmsi4 = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( AisBinaryAcknowledgeMessageObject )target;
        targetObject._spare = this._spare;
        targetObject._sequenceNumber1 = this._sequenceNumber1;
        targetObject._mmsi1 = this._mmsi1;
        targetObject._sequenceNumber2 = this._sequenceNumber2;
        targetObject._mmsi2 = this._mmsi2;
        targetObject._sequenceNumber3 = this._sequenceNumber3;
        targetObject._mmsi3 = this._mmsi3;
        targetObject._sequenceNumber4 = this._sequenceNumber4;
        targetObject._mmsi4 = this._mmsi4;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (AisBinaryAcknowledgeMessageObject)obj;
        if( !Comparer.equalsInt32( this._spare, other._spare ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._sequenceNumber1, other._sequenceNumber1 ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._mmsi1, other._mmsi1 ) ) {
            return false;
        }
        if( !Comparer.equalsNullableInt32( this._sequenceNumber2, other._sequenceNumber2 ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._mmsi2, other._mmsi2 ) ) {
            return false;
        }
        if( !Comparer.equalsNullableInt32( this._sequenceNumber3, other._sequenceNumber3 ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._mmsi3, other._mmsi3 ) ) {
            return false;
        }
        if( !Comparer.equalsNullableInt32( this._sequenceNumber4, other._sequenceNumber4 ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._mmsi4, other._mmsi4 ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt32( _spare );
        destination.writeInt32( _sequenceNumber1 );
        destination.writeNullableGuid( _mmsi1 );
        destination.writeNullableInt32( _sequenceNumber2 );
        destination.writeNullableGuid( _mmsi2 );
        destination.writeNullableInt32( _sequenceNumber3 );
        destination.writeNullableGuid( _mmsi3 );
        destination.writeNullableInt32( _sequenceNumber4 );
        destination.writeNullableGuid( _mmsi4 );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _spare = source.readInt32( );
        _sequenceNumber1 = source.readInt32( );
        _mmsi1 = source.readNullableGuid( );
        _sequenceNumber2 = source.readNullableInt32( );
        _mmsi2 = source.readNullableGuid( );
        _sequenceNumber3 = source.readNullableInt32( );
        _mmsi3 = source.readNullableGuid( );
        _sequenceNumber4 = source.readNullableInt32( );
        _mmsi4 = source.readNullableGuid( );
    }

}
