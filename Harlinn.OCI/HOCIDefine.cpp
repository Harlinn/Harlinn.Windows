#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{

    void Define::DefineByPos( UInt32 positon, OraType dataType, void* dataAddress, Int64 dataSize, UInt32* rowLengths, UInt16* rowReturnCodes, UInt32 mode )
    {
        Base::DefineByPos( positon, dataType, dataAddress, dataSize, &indicator_, rowLengths, rowReturnCodes, mode );
    }


    std::unique_ptr<Define> Define::CreateDefine( const OCI::Statement& statement, const ColumnDescriptor& columnDescriptor, UInt32 positon )
    {
        auto dataType = columnDescriptor.DataType( );
        switch ( dataType )
        {
            case OraType::DAT:
            case OraType::ODT:
            {
                auto result = std::make_unique<DateDefine>( statement );
                result->Initialize( positon );
                return result;
            }
            break;
            case OraType::TIMESTAMP:
            {
                auto result = std::make_unique<TimestampDefine>( statement );
                result->Initialize( positon );
                return result;
            }
            break;
            case OraType::TIMESTAMP_TZ:
            {
                auto result = std::make_unique<TimestampTZDefine>( statement );
                result->Initialize( positon );
                return result;
            }
            break;
            case OraType::TIMESTAMP_LTZ:
            {
                auto result = std::make_unique<TimestampLTZDefine>( statement );
                result->Initialize( positon );
                return result;
            }
            break;
            case OraType::INTERVAL_DS:
            {
                auto result = std::make_unique<IntervalDSDefine>( statement );
                result->Initialize( positon );
                return result;
            }
            break;
            case OraType::INTERVAL_YM:
            {
                auto result = std::make_unique<IntervalYMDefine>( statement );
                result->Initialize( positon );
                return result;
            }
            break;
            case OraType::CLOB:
            {
                auto characterSetForm = columnDescriptor.CharacterSetForm( );
                if ( characterSetForm == OCI::CharacterSetForm::NChar )
                {
                    auto result = std::make_unique<NCLOBDefine>( statement );
                    result->Initialize( positon );
                    return result;
                }
                else
                {
                    auto result = std::make_unique<CLOBDefine>( statement );
                    result->Initialize( positon );
                    return result;
                }
            }
            break;
            case OraType::BLOB:
            {
                auto result = std::make_unique<BLOBDefine>( statement );
                result->Initialize( positon );
                return result;
            }
            break;
            case OraType::BFILEE:
            {
                auto result = std::make_unique<BFileDefine>( statement );
                result->Initialize( positon );
                return result;
            }
            break;
            case OraType::CFILEE:
            {
                auto result = std::make_unique<CFileDefine>( statement );
                result->Initialize( positon );
                return result;
            }
            break;
            case OCI::OraType::VBI:
            {
                auto result = std::make_unique<VarBinaryDefine>( statement, columnDescriptor );
                result->Initialize( positon );
                return result;
            }
            break;
            case OCI::OraType::BIN:
            {
                auto result = std::make_unique<BinaryDefine>( statement, columnDescriptor );
                result->Initialize( positon );
                return result;
            }
            break;
            case OraType::IBFLOAT:
            {
                auto result = std::make_unique<SingleDefine>( statement );
                result->Initialize( positon );
                return result;
            }
            break;
            case OraType::IBDOUBLE:
            {
                auto result = std::make_unique<DoubleDefine>( statement );
                result->Initialize( positon );
                return result;
            }
            break;
            case OraType::NUM:
            case OraType::INT:
            case OraType::FLT:
            case OraType::VNU:
            case OraType::PDN:
            case OraType::BFLOAT:
            case OraType::BDOUBLE:
            case OraType::UIN:
            {
                auto scale = columnDescriptor.Scale( );
                auto precision = columnDescriptor.Precision( );
                if ( scale == 0 && precision <= Int8MaxPrecision )
                {
                    auto result = std::make_unique<SByteDefine>( statement );
                    result->Initialize( positon );
                    return result;
                }
                else if ( scale == 0 && precision <= Int16MaxPrecision )
                {
                    auto result = std::make_unique<Int16Define>( statement );
                    result->Initialize( positon );
                    return result;
                }
                else if ( scale == 0 && precision <= Int32MaxPrecision )
                {
                    auto result = std::make_unique<Int32Define>( statement );
                    result->Initialize( positon );
                    return result;
                }
                else if ( scale == 0 && precision <= Int64MaxPrecision )
                {
                    auto result = std::make_unique<Int64Define>( statement );
                    result->Initialize( positon );
                    return result;
                }
                else if ( scale == -127 && columnDescriptor.Precision( ) != 0 )
                {
                    auto result = std::make_unique<DoubleDefine>( statement );
                    result->Initialize( positon );
                    return result;
                }
                else
                {
                    auto result = std::make_unique<VarNumberDefine>( statement );
                    result->Initialize( positon );
                    return result;
                }
            }
            break;
            default:
            {
                auto result = std::make_unique<CStringDefine>( statement, columnDescriptor );
                result->Initialize( positon );
                return result;
            }
            break;
        }
        return std::unique_ptr<Define>( );
    }

    
    //void Define::WriteTo( IO::BinaryWriter& writer ) const
    //{
    //    HCC_THROW( NotImplementedException );
    //}

    //void Define::WriteNullableTo( IO::BinaryWriter& writer ) const
    //{
    //    HCC_THROW( NotImplementedException );
    //}


    bool Define::AsBoolean( ) const
    {
        HCC_THROW( NotImplementedException );
    }
    Byte Define::AsByte( ) const
    {
        HCC_THROW( NotImplementedException );
    }
    SByte Define::AsSByte( ) const
    {
        HCC_THROW( NotImplementedException );
    }
    std::vector<Byte> Define::AsBytes( ) const
    {
        HCC_THROW( NotImplementedException );
    }
    short Define::AsInt16( ) const
    {
        HCC_THROW( NotImplementedException );
    }
    UInt16 Define::AsUInt16( ) const
    {
        HCC_THROW( NotImplementedException );
    }
    Int32 Define::AsInt32( ) const
    {
        HCC_THROW( NotImplementedException );
    }
    UInt32 Define::AsUInt32( ) const
    {
        HCC_THROW( NotImplementedException );
    }
    long long Define::AsInt64( ) const
    {
        HCC_THROW( NotImplementedException );
    }
    UInt64 Define::AsUInt64( ) const
    {
        HCC_THROW( NotImplementedException );
    }
    float Define::AsSingle( ) const
    {
        HCC_THROW( NotImplementedException );
    }
    double Define::AsDouble( ) const
    {
        HCC_THROW( NotImplementedException );
    }
    DateTime Define::AsDateTime( ) const
    {
        HCC_THROW( NotImplementedException );
    }
    TimeSpan Define::AsTimeSpan( ) const
    {
        HCC_THROW( NotImplementedException );
    }
    std::wstring Define::AsString( ) const
    {
        HCC_THROW( NotImplementedException );
    }

    Guid Define::AsGuid( ) const
    {
        HCC_THROW( NotImplementedException );
    }

    OCI::Object* Define::AsObject( ) const
    {
        HCC_THROW( NotImplementedException );
    }

    OCI::Collection* Define::AsCollection( ) const
    {
        HCC_THROW( NotImplementedException );
    }

    LobStream Define::AsStream( ) const
    {
        HCC_THROW( NotImplementedException );
    }
}