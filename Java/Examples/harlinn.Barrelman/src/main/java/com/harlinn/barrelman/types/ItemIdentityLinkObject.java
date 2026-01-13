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

public class ItemIdentityLinkObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.ItemIdentityLink;

    private long _rowVersion = 0;
    private Guid _item;
    private Guid _identity;
    private DateTime _start;
    private DateTime _end;

    public ItemIdentityLinkObject( ) {
    }
    public ItemIdentityLinkObject( byte objectState, Guid id, long rowVersion, Guid item, Guid identity, DateTime start, DateTime end ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._item = item;
        this._identity = identity;
        this._start = start;
        this._end = end;
    }

    @Override
    public int getObjectType( ) {
        return Kind.ItemIdentityLink;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ItemIdentityLinkObject( );
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

    public Guid getItem( ) {
        return _item;
    }
    public void setItem( Guid value ) {
        if( !Comparer.equalsGuid( _item, value ) ) {
            _item = value;
            onPropertyChanged( );
        }
    }

    public Guid getIdentity( ) {
        return _identity;
    }
    public void setIdentity( Guid value ) {
        if( !Comparer.equalsGuid( _identity, value ) ) {
            _identity = value;
            onPropertyChanged( );
        }
    }

    public DateTime getStart( ) {
        return _start;
    }
    public void setStart( DateTime value ) {
        if( !Comparer.equalsDateTime( _start, value ) ) {
            _start = value;
            onPropertyChanged( );
        }
    }

    public DateTime getEnd( ) {
        return _end;
    }
    public void setEnd( DateTime value ) {
        if( !Comparer.equalsNullableDateTime( _end, value ) ) {
            _end = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( ItemIdentityLinkObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._item = this._item;
        targetObject._identity = this._identity;
        targetObject._start = this._start;
        targetObject._end = this._end;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (ItemIdentityLinkObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._item, other._item ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._identity, other._identity ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._start, other._start ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDateTime( this._end, other._end ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _item );
        destination.writeGuid( _identity );
        destination.writeDateTime( _start );
        destination.writeNullableDateTime( _end );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _item = source.readGuid( );
        _identity = source.readGuid( );
        _start = source.readDateTime( );
        _end = source.readNullableDateTime( );
    }

}
