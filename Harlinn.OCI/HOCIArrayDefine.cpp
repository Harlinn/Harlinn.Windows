#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    void ArrayDefine::DefineByPos( UInt32 positon, OraType dataType, void* dataAddress, Int64 dataSize, UInt32* returnLengths, UInt16* returnCodes, UInt32 mode )
    {
        Base::DefineByPos( positon, dataType, dataAddress, dataSize, indicator_.data( ), returnLengths, returnCodes, mode );
    }

    std::unique_ptr<ArrayDefine> ArrayDefine::CreateDefine( const OCI::Statement& statement, size_t defineSize, const ColumnDescriptor& columnDescriptor, UInt32 positon )
    {
        auto dataType = columnDescriptor.DataType( );
        switch ( dataType )
        {
            case OraType::DAT:
            case OraType::ODT:
            {
                auto result = std::make_unique<DateArrayDefine>( statement, defineSize );
                result->Initialize( positon );
                return result;
            }
            break;
            case OraType::TIMESTAMP:
            {
                auto result = std::make_unique<TimestampArrayDefine>( statement, defineSize );
                result->Initialize( positon );
                return result;
            }
            break;
            case OraType::TIMESTAMP_TZ:
            {
                auto result = std::make_unique<TimestampTZArrayDefine>( statement, defineSize );
                result->Initialize( positon );
                return result;
            }
            break;
            case OraType::TIMESTAMP_LTZ:
            {
                auto result = std::make_unique<TimestampLTZArrayDefine>( statement, defineSize );
                result->Initialize( positon );
                return result;
            }
            break;
            case OraType::INTERVAL_DS:
            {
                auto result = std::make_unique<IntervalDSArrayDefine>( statement, defineSize );
                result->Initialize( positon );
                return result;
            }
            break;
            case OraType::INTERVAL_YM:
            {
                auto result = std::make_unique<IntervalYMArrayDefine>( statement, defineSize );
                result->Initialize( positon );
                return result;
            }
            break;
            case OraType::CLOB:
            {
                auto characterSetForm = columnDescriptor.CharacterSetForm( );
                if ( characterSetForm == OCI::CharacterSetForm::NChar )
                {
                    auto result = std::make_unique<NCLOBArrayDefine>( statement, defineSize );
                    result->Initialize( positon );
                    return result;
                }
                else
                {
                    auto result = std::make_unique<CLOBArrayDefine>( statement, defineSize );
                    result->Initialize( positon );
                    return result;
                }
            }
            break;
            case OraType::BLOB:
            {
                auto result = std::make_unique<BLOBArrayDefine>( statement, defineSize );
                result->Initialize( positon );
                return result;
            }
            break;
            case OraType::BFILEE:
            {
                auto result = std::make_unique<BFileArrayDefine>( statement, defineSize );
                result->Initialize( positon );
                return result;
            }
            break;
            case OraType::CFILEE:
            {
                auto result = std::make_unique<CFileArrayDefine>( statement, defineSize );
                result->Initialize( positon );
                return result;
            }
            break;
            case OCI::OraType::VBI:
            {
                auto result = std::make_unique<VarBinaryArrayDefine>( statement, defineSize, columnDescriptor );
                result->Initialize( positon );
                return result;
            }
            break;
            case OCI::OraType::BIN:
            {
                auto result = std::make_unique<BinaryArrayDefine>( statement, defineSize, columnDescriptor );
                result->Initialize( positon );
                return result;
            }
            break;
            case OraType::IBFLOAT:
            {
                auto result = std::make_unique<SingleArrayDefine>( statement, defineSize );
                result->Initialize( positon );
                return result;
            }
            break;
            case OraType::IBDOUBLE:
            {
                auto result = std::make_unique<DoubleArrayDefine>( statement, defineSize );
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
                    auto result = std::make_unique<SByteArrayDefine>( statement, defineSize );
                    result->Initialize( positon );
                    return result;
                }
                else if ( scale == 0 && precision <= Int16MaxPrecision )
                {
                    auto result = std::make_unique<Int16ArrayDefine>( statement, defineSize );
                    result->Initialize( positon );
                    return result;
                }
                else if ( scale == 0 && precision <= Int32MaxPrecision )
                {
                    auto result = std::make_unique<Int32ArrayDefine>( statement, defineSize );
                    result->Initialize( positon );
                    return result;
                }
                else if ( scale == 0 && precision <= Int64MaxPrecision )
                {
                    auto result = std::make_unique<Int64ArrayDefine>( statement, defineSize );
                    result->Initialize( positon );
                    return result;
                }
                else if ( scale == -127 && columnDescriptor.Precision( ) != 0 )
                {
                    auto result = std::make_unique<DoubleArrayDefine>( statement, defineSize );
                    result->Initialize( positon );
                    return result;
                }
                else
                {
                    auto result = std::make_unique<VarNumberArrayDefine>( statement, defineSize );
                    result->Initialize( positon );
                    return result;
                }
            }
            break;
            default:
            {
                auto result = std::make_unique<CStringArrayDefine>( statement, defineSize, columnDescriptor );
                result->Initialize( positon );
                return result;
            }
            break;
        }
        return std::unique_ptr<ArrayDefine>( );
    }


    //void ArrayDefine::WriteTo( size_t index, IO::BinaryWriter& writer ) const
    //{
    //    HCC_THROW( NotImplementedException );
    //}

    //void ArrayDefine::WriteNullableTo( size_t index, IO::BinaryWriter& writer ) const
    //{
    //    HCC_THROW( NotImplementedException );
    //}


    bool ArrayDefine::AsBoolean( size_t index ) const
    {
        HCC_THROW( NotImplementedException );
    }

    Byte ArrayDefine::AsByte( size_t index ) const
    {
        HCC_THROW( NotImplementedException );
    }

    SByte ArrayDefine::AsSByte( size_t index ) const
    {
        HCC_THROW( NotImplementedException );
    }

    std::vector<Byte> ArrayDefine::AsBytes( size_t index ) const
    {
        HCC_THROW( NotImplementedException );
    }

    short ArrayDefine::AsInt16( size_t index ) const
    {
        HCC_THROW( NotImplementedException );
    }

    UInt16 ArrayDefine::AsUInt16( size_t index ) const
    {
        HCC_THROW( NotImplementedException );
    }

    Int32 ArrayDefine::AsInt32( size_t index ) const
    {
        HCC_THROW( NotImplementedException );
    }

    UInt32 ArrayDefine::AsUInt32( size_t index ) const
    {
        HCC_THROW( NotImplementedException );
    }

    long long ArrayDefine::AsInt64( size_t index ) const
    {
        HCC_THROW( NotImplementedException );
    }

    UInt64 ArrayDefine::AsUInt64( size_t index ) const
    {
        HCC_THROW( NotImplementedException );
    }

    float ArrayDefine::AsSingle( size_t index ) const
    {
        HCC_THROW( NotImplementedException );
    }

    double ArrayDefine::AsDouble( size_t index ) const
    {
        HCC_THROW( NotImplementedException );
    }

    DateTime ArrayDefine::AsDateTime( size_t index ) const
    {
        HCC_THROW( NotImplementedException );
    }

    TimeSpan ArrayDefine::AsTimeSpan( size_t index ) const
    {
        HCC_THROW( NotImplementedException );
    }

    std::wstring ArrayDefine::AsString( size_t index ) const
    {
        HCC_THROW( NotImplementedException );
    }

    Guid ArrayDefine::AsGuid( size_t index ) const
    {
        HCC_THROW( NotImplementedException );
    }

    OCI::Object* ArrayDefine::AsObject( size_t index ) const
    {
        HCC_THROW( NotImplementedException );
    }

    OCI::Collection* ArrayDefine::AsCollection( size_t index ) const
    {
        HCC_THROW( NotImplementedException );
    }

    LobStream ArrayDefine::AsStream( size_t index ) const
    {
        HCC_THROW( NotImplementedException );
    }


}