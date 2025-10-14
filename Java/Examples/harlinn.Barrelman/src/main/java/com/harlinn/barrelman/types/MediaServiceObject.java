package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class MediaServiceObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _enabledTimeseries;

    @Override
    public int getObjectType( ) {
        return Kind.MediaService;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new MediaServiceObject( );
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

    public Guid getEnabledTimeseries( ) {
        return _enabledTimeseries;
    }
    public void setEnabledTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _enabledTimeseries, value ) ) {
            _enabledTimeseries = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeNullableGuid( _enabledTimeseries );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _enabledTimeseries = source.readNullableGuid( );
    }

}
