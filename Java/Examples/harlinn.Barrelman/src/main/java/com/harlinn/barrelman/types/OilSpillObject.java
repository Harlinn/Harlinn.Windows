package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class OilSpillObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _oilSpillDetector;
    private DateTime _timestamp;
    private double _oilArea = 0.0;
    private byte[] _shape = new byte[0];
    private byte[] _bSI = new byte[0];
    private byte[] _oil = new byte[0];
    private byte[] _trace = new byte[0];

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
