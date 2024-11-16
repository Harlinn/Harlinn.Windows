/*
   Copyright 2024 Espen Harlinn

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

#include "pch.h"
#include "HCCEse.h"


namespace Harlinn::Common::Core::Ese
{
    namespace
    {
        __declspec( thread ) wchar_t messagebuffer[ 4096 ] = { 0, };

        WideString GetEseError( JET_ERR rc )
        {
            wchar_t* buffer = messagebuffer;
            JetGetSystemParameterW( JET_instanceNil, JET_sesidNil, JET_paramErrorToString, ( JET_API_PTR* )&rc, buffer, 4096 );
            auto result = Format( L"ESENT error {}: {}\n", rc, buffer );
            return result;
        }
    }

    Exception::Exception( JET_ERR rc )
        : Base( GetEseError( rc ) )
    {

    }

    Exception::Exception( Result rc )
        : Base( GetEseError( static_cast< JET_ERR >( rc ) ) )
    {

    }

    WideString Exception::GetErrorMessage( JET_ERR rc )
    {
        return GetEseError( rc );
    }

    WideString Exception::GetErrorMessage( Result rc )
    {
        return GetEseError( static_cast< JET_ERR >( rc ) );
    }

    HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( Exception )
    
}

namespace Harlinn::Common::Core
{
    namespace
    {
        using ColumnType = Ese::ColumnType;
        class ColumnTypeConverter : public Enum<ColumnType>
        {
        public:
            using Base = Enum<ColumnType>;
            ColumnTypeConverter( )
            {
                Add( WideString(L"None"), ColumnType::None );
                Add( WideString(L"Boolean"), ColumnType::Boolean );
                Add( WideString(L"Byte"), ColumnType::Byte );
                Add( WideString(L"Short"), ColumnType::Short );
                Add( WideString(L"Long"), ColumnType::Long );
                Add( WideString(L"Currency"), ColumnType::Currency );
                Add( WideString(L"Single"), ColumnType::Single );
                Add( WideString(L"Double"), ColumnType::Double );
                Add( WideString(L"DateTime"), ColumnType::DateTime );
                Add( WideString(L"Binary"), ColumnType::Binary );
                Add( WideString(L"Text"), ColumnType::Text );
                Add( WideString(L"LongBinary"), ColumnType::LongBinary );
                Add( WideString(L"LongText"), ColumnType::LongText );
                Add( WideString(L"SLV"), ColumnType::SLV );
                Add( WideString(L"UnsignedLong"), ColumnType::UnsignedLong );
                Add( WideString(L"LongLong"), ColumnType::LongLong );
                Add( WideString(L"Guid"), ColumnType::Guid );
                Add( WideString(L"UnsignedShort"), ColumnType::UnsignedShort );
                Add( WideString(L"UnsignedLongLong"), ColumnType::UnsignedLongLong );
            }
        };

        ColumnTypeConverter columnTypeConverter;
    }

    WideString ToWideString( ColumnType value )
    {
        return columnTypeConverter.ToString( value );
    }
    WideString ToWideString( ColumnType value, const WideString& defaultResult )
    {
        return columnTypeConverter.ToString( value, defaultResult );
    }
    namespace Ese
    {
        ColumnType ParseColumnType( const WideString& str )
        {
            return columnTypeConverter.Parse( str );
        }

        ColumnType ParseColumnType( const WideString& str, ColumnType defaultResult )
        {
            return columnTypeConverter.Parse( str, defaultResult );
        }

        bool TryParseColumnType( const WideString& str, ColumnType& value )
        {
            return columnTypeConverter.TryParse( str, value );
        }
    }

    namespace
    {
        using ColumnFlags = Ese::ColumnFlags;
        class ColumnFlagsConverter : public Flags<ColumnFlags>
        {
        public:
            using Base = Flags<ColumnFlags>;
            ColumnFlagsConverter( )
            {
                Add( WideString(L"None"), ColumnFlags::None );
                Add( WideString(L"Fixed"), ColumnFlags::Fixed );
                Add( WideString(L"Tagged"), ColumnFlags::Tagged );
                Add( WideString(L"NotNULL"), ColumnFlags::NotNULL );
                Add( WideString(L"Version"), ColumnFlags::Version );
                Add( WideString(L"Autoincrement"), ColumnFlags::Autoincrement );
                Add( WideString(L"Updatable"), ColumnFlags::Updatable );
                Add( WideString(L"TemporaryTableKey"), ColumnFlags::TemporaryTableKey );
                Add( WideString(L"TemporaryTableDescending"), ColumnFlags::TemporaryTableDescending );
                Add( WideString(L"MultiValued"), ColumnFlags::MultiValued );
                Add( WideString(L"EscrowUpdate"), ColumnFlags::EscrowUpdate );
                Add( WideString(L"Unversioned"), ColumnFlags::Unversioned );
                Add( WideString(L"Finalize"), ColumnFlags::Finalize );
                Add( WideString(L"UserDefinedDefault"), ColumnFlags::UserDefinedDefault );
                Add( WideString(L"DeleteOnZero"), ColumnFlags::DeleteOnZero );
                Add( WideString(L"Compressed"), ColumnFlags::Compressed );
            }
        };
        ColumnFlagsConverter columnFlagsConverter;
    }


    WideString ToWideString( ColumnFlags value )
    {
        return columnFlagsConverter.ToString( value );
    }
    WideString ToWideString( ColumnFlags value, const WideString& defaultResult )
    {
        return columnFlagsConverter.ToString( value, defaultResult );
    }
    namespace Ese
    {
        ColumnFlags ParseColumnFlags( const WideString& str )
        {
            return columnFlagsConverter.Parse( str );
        }

        ColumnFlags ParseColumnFlags( const WideString& str, ColumnFlags defaultResult )
        {
            return columnFlagsConverter.Parse( str, defaultResult );
        }

        bool TryParseColumnFlags( const WideString& str, ColumnFlags& value )
        {
            return columnFlagsConverter.TryParse( str, value );
        }
    }

    namespace
    {
        using IndexFlags = Ese::IndexFlags;
        class IndexFlagsConverter : public Flags<IndexFlags>
        {
        public:
            using Base = Flags<IndexFlags>;
            IndexFlagsConverter( )
            {
                Add( WideString(L"None"), IndexFlags::None );
                Add( WideString(L"Unique"), IndexFlags::Unique );
                Add( WideString(L"Primary"), IndexFlags::Primary );
                Add( WideString(L"DisallowNull"), IndexFlags::DisallowNull );
                Add( WideString(L"IgnoreNull"), IndexFlags::IgnoreNull );
                Add( WideString(L"IgnoreAnyNull"), IndexFlags::IgnoreAnyNull );
                Add( WideString(L"IgnoreFirstNull"), IndexFlags::IgnoreFirstNull );
                Add( WideString(L"LazyFlush"), IndexFlags::LazyFlush );
                Add( WideString(L"Empty"), IndexFlags::Empty );
                Add( WideString(L"Unversioned"), IndexFlags::Unversioned );
                Add( WideString(L"SortNullsHigh"), IndexFlags::SortNullsHigh );
                Add( WideString(L"Unicode"), IndexFlags::Unicode );
                Add( WideString(L"Tuples"), IndexFlags::Tuples );
                Add( WideString(L"TupleLimits"), IndexFlags::TupleLimits );
                Add( WideString(L"CrossProduct"), IndexFlags::CrossProduct );
                Add( WideString(L"KeyMost"), IndexFlags::KeyMost );
                Add( WideString(L"DisallowTruncation"), IndexFlags::DisallowTruncation );
                Add( WideString(L"NestedTable"), IndexFlags::NestedTable );
                Add( WideString(L"DotNetGuid"), IndexFlags::DotNetGuid );
            }
        };
        IndexFlagsConverter indexFlagsConverter;
    }


    WideString ToWideString( IndexFlags value )
    {
        return indexFlagsConverter.ToString( value );
    }
    WideString ToWideString( IndexFlags value, const WideString& defaultResult )
    {
        return indexFlagsConverter.ToString( value, defaultResult );
    }
    namespace Ese
    {
        IndexFlags ParseIndexFlags( const WideString& str )
        {
            return indexFlagsConverter.Parse( str );
        }
        IndexFlags ParseIndexFlags( const WideString& str, IndexFlags defaultResult )
        {
            return indexFlagsConverter.Parse( str, defaultResult );
        }
        bool TryParseIndexFlags( const WideString& str, IndexFlags& value )
        {
            return indexFlagsConverter.TryParse( str, value );
        }
    }

    namespace
    {
        using RetrieveFlags = Ese::RetrieveFlags;
        class RetrieveFlagsConverter : public Flags<RetrieveFlags>
        {
        public:
            using Base = Flags<RetrieveFlags>;
            RetrieveFlagsConverter( )
            {
                Add( WideString(L"None"), RetrieveFlags::None );
                Add( WideString(L"Copy"), RetrieveFlags::Copy );
                Add( WideString(L"FromIndex"), RetrieveFlags::FromIndex );
                Add( WideString(L"FromPrimaryBookmark"), RetrieveFlags::FromPrimaryBookmark );
                Add( WideString(L"Tag"), RetrieveFlags::Tag );
                Add( WideString(L"Null"), RetrieveFlags::Null );
                Add( WideString(L"IgnoreDefault"), RetrieveFlags::IgnoreDefault );
                Add( WideString(L"Tuple"), RetrieveFlags::Tuple );
            }
        };
        RetrieveFlagsConverter retrieveFlagsConverter;
    }

    WideString ToWideString( RetrieveFlags value )
    {
        return retrieveFlagsConverter.ToString( value );
    }
    WideString ToWideString( RetrieveFlags value, const WideString& defaultResult )
    {
        return retrieveFlagsConverter.ToString( value, defaultResult );
    }
    namespace Ese
    {
        RetrieveFlags ParseRetrieveFlags( const WideString& str )
        {
            return retrieveFlagsConverter.Parse( str );
        }
        RetrieveFlags ParseRetrieveFlags( const WideString& str, RetrieveFlags defaultResult )
        {
            return retrieveFlagsConverter.Parse( str, defaultResult );
        }
        bool TryParseRetrieveFlags( const WideString& str, RetrieveFlags& value )
        {
            return retrieveFlagsConverter.TryParse( str, value );
        }
    }


    namespace
    {
        using SetFlags = Ese::SetFlags;
        class SetFlagsConverter : public Flags<SetFlags>
        {
        public:
            using Base = Flags<SetFlags>;
            SetFlagsConverter( )
            {
                Add( WideString(L"None"), SetFlags::None );
                Add( WideString(L"AppendLV"), SetFlags::AppendLV );
                Add( WideString(L"OverwriteLV"), SetFlags::OverwriteLV );
                Add( WideString(L"RevertToDefaultValue"), SetFlags::RevertToDefaultValue );
                Add( WideString(L"SeparateLV"), SetFlags::SeparateLV );
                Add( WideString(L"SizeLV"), SetFlags::SizeLV );
                Add( WideString(L"UniqueMultiValues"), SetFlags::UniqueMultiValues );
                Add( WideString(L"UniqueNormalizedMultiValues"), SetFlags::UniqueNormalizedMultiValues );
                Add( WideString(L"ZeroLength"), SetFlags::ZeroLength );
                Add( WideString(L"IntrinsicLV"), SetFlags::IntrinsicLV );
                Add( WideString(L"Compressed"), SetFlags::Compressed );
                Add( WideString(L"Uncompressed"), SetFlags::Uncompressed );
            }
        };
        SetFlagsConverter setFlagsConverter;
    }

    WideString ToWideString( SetFlags value )
    {
        return setFlagsConverter.ToString( value );
    }
    WideString ToWideString( SetFlags value, const WideString& defaultResult )
    {
        return setFlagsConverter.ToString( value, defaultResult );
    }
    namespace Ese
    {
        SetFlags ParseSetFlags( const WideString& str )
        {
            return setFlagsConverter.Parse( str );
        }
        SetFlags ParseSetFlags( const WideString& str, SetFlags defaultResult )
        {
            return setFlagsConverter.Parse( str, defaultResult );
        }
        bool TryParseSetFlags( const WideString& str, SetFlags& value )
        {
            return setFlagsConverter.TryParse( str, value );
        }
    }

    namespace
    {
        using ColumnInfoFlags = Ese::ColumnInfoFlags;
        class ColumnInfoFlagsConverter : public Flags<ColumnInfoFlags>
        {
        public:
            using Base = Flags<ColumnInfoFlags>;
            ColumnInfoFlagsConverter( )
            {
                Add( L"Default", ColumnInfoFlags::Default );
                Add( L"Base", ColumnInfoFlags::Base );
                Add( L"ByColid", ColumnInfoFlags::ByColid );
                Add( L"List", ColumnInfoFlags::List );
                Add( L"ListCompact", ColumnInfoFlags::ListCompact );
                Add( L"ListSortColumnId", ColumnInfoFlags::ListSortColumnId );
                Add( L"BaseByColId", ColumnInfoFlags::BaseByColId );
                Add( L"NonDerivedColumnsOnly", ColumnInfoFlags::NonDerivedColumnsOnly );
                Add( L"MinimalInfo", ColumnInfoFlags::MinimalInfo );
                Add( L"SortByColumnId", ColumnInfoFlags::SortByColumnId );
            }
        };
        ColumnInfoFlagsConverter columnInfoFlagsConverter;
    }

    WideString ToWideString( Ese::ColumnInfoFlags value )
    {
        return columnInfoFlagsConverter.ToString( value );
    }
    WideString ToWideString( Ese::ColumnInfoFlags value, const WideString& defaultResult )
    {
        return columnInfoFlagsConverter.ToString( value, defaultResult );
    }
    namespace Ese
    {
        Ese::ColumnInfoFlags ParseColumnInfoFlags( const WideString& str )
        {
            return columnInfoFlagsConverter.Parse( str );
        }
        Ese::ColumnInfoFlags ParseColumnInfoFlags( const WideString& str, Ese::ColumnInfoFlags defaultResult )
        {
            return columnInfoFlagsConverter.Parse( str, defaultResult );
        }
        bool TryParseColumnInfoFlags( const WideString& str, Ese::ColumnInfoFlags& value )
        {
            return columnInfoFlagsConverter.TryParse( str, value );
        }
    }

    namespace
    {
        using PrepareUpdateOptions = Ese::PrepareUpdateOptions;
        class PrepareUpdateOptionsConverter : public Enum<PrepareUpdateOptions>
        {
        public:
            PrepareUpdateOptionsConverter( )
            {
                Add( L"Cancel", PrepareUpdateOptions::Cancel );
                Add( L"Insert", PrepareUpdateOptions::Insert );
                Add( L"Copy", PrepareUpdateOptions::Copy );
                Add( L"InsertCopyDeleteOriginal", PrepareUpdateOptions::InsertCopyDeleteOriginal );
                Add( L"Replace", PrepareUpdateOptions::Replace );
                Add( L"ReplaceNoLock", PrepareUpdateOptions::ReplaceNoLock );
            }
        };
        PrepareUpdateOptionsConverter prepareUpdateOptionsConverter;
    }

    WideString ToWideString( Ese::PrepareUpdateOptions value )
    {
        return prepareUpdateOptionsConverter.ToString( value );
    }
    WideString ToWideString( Ese::PrepareUpdateOptions value, const WideString& defaultResult )
    {
        return prepareUpdateOptionsConverter.ToString( value, defaultResult );
    }

    namespace Ese
    {
        Ese::PrepareUpdateOptions ParsePrepareUpdateOptions( const WideString& str )
        {
            return prepareUpdateOptionsConverter.Parse( str );
        }

        Ese::PrepareUpdateOptions ParsePrepareUpdateOptions( const WideString& str, Ese::PrepareUpdateOptions defaultResult )
        {
            return prepareUpdateOptionsConverter.Parse( str, defaultResult );
        }

        bool TryParsePrepareUpdateOptions( const WideString& str, Ese::PrepareUpdateOptions& value )
        {
            return prepareUpdateOptionsConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // KeyFlags
    // =========================================================================
    namespace
    {
        using KeyFlags = Ese::KeyFlags;
        class KeyFlagsConverter : public Flags<KeyFlags>
        {
        public:
            KeyFlagsConverter( )
            {
                Add( L"None", KeyFlags::None );
                Add( L"FullColumnEndLimit", KeyFlags::FullColumnEndLimit );
                Add( L"FullColumnStartLimit", KeyFlags::FullColumnStartLimit );
                Add( L"KeyDataZeroLength", KeyFlags::KeyDataZeroLength );
                Add( L"NewKey", KeyFlags::NewKey );
                Add( L"NormalizedKey", KeyFlags::NormalizedKey );
                Add( L"PartialColumnEndLimit", KeyFlags::PartialColumnEndLimit );
                Add( L"PartialColumnStartLimit", KeyFlags::PartialColumnStartLimit );
                Add( L"StrLimit", KeyFlags::StrLimit );
                Add( L"SubStrLimit", KeyFlags::SubStrLimit );
            }
        };
        KeyFlagsConverter keyFlagsConverter;
    }

    WideString ToWideString( Ese::KeyFlags value )
    {
        return keyFlagsConverter.ToString( value );
    }
    WideString ToWideString( Ese::KeyFlags value, const WideString& defaultResult )
    {
        return keyFlagsConverter.ToString( value, defaultResult );
    }

    namespace Ese
    {
        Ese::KeyFlags ParseKeyFlags( const WideString& str )
        {
            return keyFlagsConverter.Parse( str );
        }

        Ese::KeyFlags ParseKeyFlags( const WideString& str, Ese::KeyFlags defaultResult )
        {
            return keyFlagsConverter.Parse( str, defaultResult );
        }

        bool TryParseKeyFlags( const WideString& str, Ese::KeyFlags& value )
        {
            return keyFlagsConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // SeekFlags
    // =========================================================================
    namespace
    {
        using SeekFlags = Ese::SeekFlags;
        class SeekFlagsConverter : public Flags<SeekFlags>
        {
        public:
            SeekFlagsConverter( )
            {
                Add( L"None", SeekFlags::None );
                Add( L"CheckUniqueness", SeekFlags::CheckUniqueness );
                Add( L"Equal", SeekFlags::Equal );
                Add( L"GreaterOrEqual", SeekFlags::GreaterOrEqual );
                Add( L"Greater", SeekFlags::Greater );
                Add( L"LessOrEqual", SeekFlags::LessOrEqual );
                Add( L"Less", SeekFlags::Less );
                Add( L"SetIndexRange", SeekFlags::SetIndexRange );
            }
        };
        SeekFlagsConverter seekFlagsConverter;
    }

    WideString ToWideString( Ese::SeekFlags value )
    {
        return seekFlagsConverter.ToString( value );
    }
    WideString ToWideString( Ese::SeekFlags value, const WideString& defaultResult )
    {
        return seekFlagsConverter.ToString( value, defaultResult );
    }

    namespace Ese
    {
        Ese::SeekFlags ParseSeekFlags( const WideString& str )
        {
            return seekFlagsConverter.Parse( str );
        }

        Ese::SeekFlags ParseSeekFlags( const WideString& str, Ese::SeekFlags defaultResult )
        {
            return seekFlagsConverter.Parse( str, defaultResult );
        }

        bool TryParseSeekFlags( const WideString& str, Ese::SeekFlags& value )
        {
            return seekFlagsConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // IndexRangeFlags
    // =========================================================================
    namespace
    {
        using IndexRangeFlags = Ese::IndexRangeFlags;
        class IndexRangeFlagsConverter : public Flags<IndexRangeFlags>
        {
        public:
            IndexRangeFlagsConverter( )
            {
                Add( L"None", IndexRangeFlags::None );
                Add( L"Inclusive", IndexRangeFlags::Inclusive );
                Add( L"UpperLimit", IndexRangeFlags::UpperLimit );
                Add( L"InstantDuration", IndexRangeFlags::InstantDuration );
                Add( L"Remove", IndexRangeFlags::Remove );
            }
        };
        IndexRangeFlagsConverter indexRangeFlagsConverter;
    }

    WideString ToWideString( Ese::IndexRangeFlags value )
    {
        return indexRangeFlagsConverter.ToString( value );
    }
    WideString ToWideString( Ese::IndexRangeFlags value, const WideString& defaultResult )
    {
        return indexRangeFlagsConverter.ToString( value, defaultResult );
    }

    namespace Ese
    {
        Ese::IndexRangeFlags ParseIndexRangeFlags( const WideString& str )
        {
            return indexRangeFlagsConverter.Parse( str );
        }

        Ese::IndexRangeFlags ParseIndexRangeFlags( const WideString& str, Ese::IndexRangeFlags defaultResult )
        {
            return indexRangeFlagsConverter.Parse( str, defaultResult );
        }

        bool TryParseIndexRangeFlags( const WideString& str, Ese::IndexRangeFlags& value )
        {
            return indexRangeFlagsConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // SetCurrentIndexFlags
    // =========================================================================
    namespace
    {
        using SetCurrentIndexFlags = Ese::SetCurrentIndexFlags;
        class SetCurrentIndexFlagsConverter : public Flags<SetCurrentIndexFlags>
        {
        public:
            SetCurrentIndexFlagsConverter( )
            {
                Add( L"MoveFirst", SetCurrentIndexFlags::MoveFirst );
                Add( L"NoMove", SetCurrentIndexFlags::NoMove );
            }
        };
        SetCurrentIndexFlagsConverter setCurrentIndexFlagsConverter;
    }

    WideString ToWideString( Ese::SetCurrentIndexFlags value )
    {
        return setCurrentIndexFlagsConverter.ToString( value );
    }
    WideString ToWideString( Ese::SetCurrentIndexFlags value, const WideString& defaultResult )
    {
        return setCurrentIndexFlagsConverter.ToString( value, defaultResult );
    }

    namespace Ese
    {
        Ese::SetCurrentIndexFlags ParseSetCurrentIndexFlags( const WideString& str )
        {
            return setCurrentIndexFlagsConverter.Parse( str );
        }

        Ese::SetCurrentIndexFlags ParseSetCurrentIndexFlags( const WideString& str, Ese::SetCurrentIndexFlags defaultResult )
        {
            return setCurrentIndexFlagsConverter.Parse( str, defaultResult );
        }

        bool TryParseSetCurrentIndexFlags( const WideString& str, Ese::SetCurrentIndexFlags& value )
        {
            return setCurrentIndexFlagsConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // TableOptions
    // =========================================================================
    namespace
    {
        using TableOptions = Ese::TableOptions;
        class TableOptionsConverter : public Flags<TableOptions>
        {
        public:
            TableOptionsConverter( )
            {
                Add( L"None", TableOptions::None );
                Add( L"Updatable", TableOptions::Updatable );
                Add( L"Bookmark", TableOptions::Bookmark );
                Add( L"Rollback", TableOptions::Rollback );
            }
        };
        TableOptionsConverter tableOptionsConverter;
    }

    WideString ToWideString( Ese::TableOptions value )
    {
        return tableOptionsConverter.ToString( value );
    }
    WideString ToWideString( Ese::TableOptions value, const WideString& defaultResult )
    {
        return tableOptionsConverter.ToString( value, defaultResult );
    }

    namespace Ese
    {
        Ese::TableOptions ParseTableOptions( const WideString& str )
        {
            return tableOptionsConverter.Parse( str );
        }

        Ese::TableOptions ParseTableOptions( const WideString& str, Ese::TableOptions defaultResult )
        {
            return tableOptionsConverter.Parse( str, defaultResult );
        }

        bool TryParseTableOptions( const WideString& str, Ese::TableOptions& value )
        {
            return tableOptionsConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // ObjectFlags
    // =========================================================================
    namespace
    {
        using ObjectFlags = Ese::ObjectFlags;
        class ObjectFlagsConverter : public Flags<ObjectFlags>
        {
        public:
            ObjectFlagsConverter( )
            {
                Add( L"None", ObjectFlags::None );
                Add( L"System", ObjectFlags::System );
                Add( L"Derived", ObjectFlags::Derived );
                Add( L"FixedDDL", ObjectFlags::FixedDDL );
                Add( L"NoFixedVarColumnsInDerivedTables", ObjectFlags::NoFixedVarColumnsInDerivedTables );
                Add( L"Template", ObjectFlags::Template );
            }
        };
        ObjectFlagsConverter objectFlagsConverter;
    }

    WideString ToWideString( Ese::ObjectFlags value )
    {
        return objectFlagsConverter.ToString( value );
    }
    WideString ToWideString( Ese::ObjectFlags value, const WideString& defaultResult )
    {
        return objectFlagsConverter.ToString( value, defaultResult );
    }

    namespace Ese
    {
        Ese::ObjectFlags ParseObjectFlags( const WideString& str )
        {
            return objectFlagsConverter.Parse( str );
        }

        Ese::ObjectFlags ParseObjectFlags( const WideString& str, Ese::ObjectFlags defaultResult )
        {
            return objectFlagsConverter.Parse( str, defaultResult );
        }

        bool TryParseObjectFlags( const WideString& str, Ese::ObjectFlags& value )
        {
            return objectFlagsConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // SequentialFlags
    // =========================================================================
    namespace
    {
        using SequentialFlags = Ese::SequentialFlags;
        class SequentialFlagsConverter : public Flags<SequentialFlags>
        {
        public:
            SequentialFlagsConverter( )
            {
                Add( L"None", SequentialFlags::None );
                Add( L"PrereadForward", SequentialFlags::PrereadForward );
                Add( L"PrereadBackward", SequentialFlags::PrereadBackward );
            }
        };
        SequentialFlagsConverter sequentialFlagsConverter;
    }

    WideString ToWideString( Ese::SequentialFlags value )
    {
        return sequentialFlagsConverter.ToString( value );
    }
    WideString ToWideString( Ese::SequentialFlags value, const WideString& defaultResult )
    {
        return sequentialFlagsConverter.ToString( value, defaultResult );
    }

    namespace Ese
    {
        Ese::SequentialFlags ParseSequentialFlags( const WideString& str )
        {
            return sequentialFlagsConverter.Parse( str );
        }

        Ese::SequentialFlags ParseSequentialFlags( const WideString& str, Ese::SequentialFlags defaultResult )
        {
            return sequentialFlagsConverter.Parse( str, defaultResult );
        }

        bool TryParseSequentialFlags( const WideString& str, Ese::SequentialFlags& value )
        {
            return sequentialFlagsConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // ExceptionAction
    // =========================================================================
    namespace
    {
        using ExceptionAction = Ese::ExceptionAction;
        class ExceptionActionConverter : public Enum<ExceptionAction>
        {
        public:
            ExceptionActionConverter( )
            {
                Add( L"DisplayMessageBox", ExceptionAction::DisplayMessageBox );
                Add( L"None", ExceptionAction::None );
                Add( L"FailFast", ExceptionAction::FailFast );
            }
        };
        ExceptionActionConverter exceptionActionConverter;
    }

    WideString ToWideString( Ese::ExceptionAction value )
    {
        return exceptionActionConverter.ToString( value );
    }
    WideString ToWideString( Ese::ExceptionAction value, const WideString& defaultResult )
    {
        return exceptionActionConverter.ToString( value, defaultResult );
    }

    namespace Ese
    {
        Ese::ExceptionAction ParseExceptionAction( const WideString& str )
        {
            return exceptionActionConverter.Parse( str );
        }

        Ese::ExceptionAction ParseExceptionAction( const WideString& str, Ese::ExceptionAction defaultResult )
        {
            return exceptionActionConverter.Parse( str, defaultResult );
        }

        bool TryParseExceptionAction( const WideString& str, Ese::ExceptionAction& value )
        {
            return exceptionActionConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // OpenTableFlags
    // =========================================================================
    namespace
    {
        using OpenTableFlags = Ese::OpenTableFlags;
        class OpenTableFlagsConverter : public Flags<OpenTableFlags>
        {
        public:
            OpenTableFlagsConverter( )
            {
                Add( L"None", OpenTableFlags::None );
                Add( L"DenyRead", OpenTableFlags::DenyRead );
                Add( L"DenyWrite", OpenTableFlags::DenyWrite );
                Add( L"NoCache", OpenTableFlags::NoCache );
                Add( L"PermitDDL", OpenTableFlags::PermitDDL );
                Add( L"Preread", OpenTableFlags::Preread );
                Add( L"ReadOnly", OpenTableFlags::ReadOnly );
                Add( L"OpportuneRead", OpenTableFlags::OpportuneRead );
                Add( L"Sequential", OpenTableFlags::Sequential );
                Add( L"Updatable", OpenTableFlags::Updatable );
            }
        };
        OpenTableFlagsConverter openTableFlagsConverter;
    }

    WideString ToWideString( Ese::OpenTableFlags value )
    {
        return openTableFlagsConverter.ToString( value );
    }
    WideString ToWideString( Ese::OpenTableFlags value, const WideString& defaultResult )
    {
        return openTableFlagsConverter.ToString( value, defaultResult );
    }

    namespace Ese
    {
        Ese::OpenTableFlags ParseOpenTableFlags( const WideString& str )
        {
            return openTableFlagsConverter.Parse( str );
        }

        Ese::OpenTableFlags ParseOpenTableFlags( const WideString& str, Ese::OpenTableFlags defaultResult )
        {
            return openTableFlagsConverter.Parse( str, defaultResult );
        }

        bool TryParseOpenTableFlags( const WideString& str, Ese::OpenTableFlags& value )
        {
            return openTableFlagsConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // TransactionFlags
    // =========================================================================
    namespace
    {
        using TransactionFlags = Ese::TransactionFlags;
        class TransactionFlagsConverter : public Flags<TransactionFlags>
        {
        public:
            TransactionFlagsConverter( )
            {
                Add( L"None", TransactionFlags::None );
                Add( L"CommitLazyFlush", TransactionFlags::CommitLazyFlush );
                Add( L"WaitAll", TransactionFlags::WaitAll );
                Add( L"WaitLast", TransactionFlags::WaitLast );
            }
        };
        TransactionFlagsConverter transactionFlagsConverter;
    }

    WideString ToWideString( Ese::TransactionFlags value )
    {
        return transactionFlagsConverter.ToString( value );
    }
    WideString ToWideString( Ese::TransactionFlags value, const WideString& defaultResult )
    {
        return transactionFlagsConverter.ToString( value, defaultResult );
    }

    namespace Ese
    {
        Ese::TransactionFlags ParseTransactionFlags( const WideString& str )
        {
            return transactionFlagsConverter.Parse( str );
        }

        Ese::TransactionFlags ParseTransactionFlags( const WideString& str, Ese::TransactionFlags defaultResult )
        {
            return transactionFlagsConverter.Parse( str, defaultResult );
        }

        bool TryParseTransactionFlags( const WideString& str, Ese::TransactionFlags& value )
        {
            return transactionFlagsConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // AttachDatabaseFlags
    // =========================================================================
    namespace
    {
        using AttachDatabaseFlags = Ese::AttachDatabaseFlags;
        class AttachDatabaseFlagsConverter : public Flags<AttachDatabaseFlags>
        {
        public:
            AttachDatabaseFlagsConverter( )
            {
                Add( L"None", AttachDatabaseFlags::None );
                Add( L"DeleteCorruptIndexes", AttachDatabaseFlags::DeleteCorruptIndexes );
                Add( L"DeleteUnicodeIndexes", AttachDatabaseFlags::DeleteUnicodeIndexes );
                Add( L"ReadOnly", AttachDatabaseFlags::ReadOnly );
                Add( L"Upgrade", AttachDatabaseFlags::Upgrade );
            }
        };
        AttachDatabaseFlagsConverter attachDatabaseFlagsConverter;
    }

    WideString ToWideString( Ese::AttachDatabaseFlags value )
    {
        return attachDatabaseFlagsConverter.ToString( value );
    }
    WideString ToWideString( Ese::AttachDatabaseFlags value, const WideString& defaultResult )
    {
        return attachDatabaseFlagsConverter.ToString( value, defaultResult );
    }

    namespace Ese
    {
        Ese::AttachDatabaseFlags ParseAttachDatabaseFlags( const WideString& str )
        {
            return attachDatabaseFlagsConverter.Parse( str );
        }

        Ese::AttachDatabaseFlags ParseAttachDatabaseFlags( const WideString& str, Ese::AttachDatabaseFlags defaultResult )
        {
            return attachDatabaseFlagsConverter.Parse( str, defaultResult );
        }

        bool TryParseAttachDatabaseFlags( const WideString& str, Ese::AttachDatabaseFlags& value )
        {
            return attachDatabaseFlagsConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // DetachDatabaseFlags
    // =========================================================================
    namespace
    {
        using DetachDatabaseFlags = Ese::DetachDatabaseFlags;
        class DetachDatabaseFlagsConverter : public Flags<DetachDatabaseFlags>
        {
        public:
            DetachDatabaseFlagsConverter( )
            {
                Add( L"None", DetachDatabaseFlags::None );
                Add( L"ForceCloseAndDetach", DetachDatabaseFlags::ForceCloseAndDetach );
                Add( L"ForceDetach", DetachDatabaseFlags::ForceDetach );
            }
        };
        DetachDatabaseFlagsConverter detachDatabaseFlagsConverter;
    }

    WideString ToWideString( Ese::DetachDatabaseFlags value )
    {
        return detachDatabaseFlagsConverter.ToString( value );
    }
    WideString ToWideString( Ese::DetachDatabaseFlags value, const WideString& defaultResult )
    {
        return detachDatabaseFlagsConverter.ToString( value, defaultResult );
    }

    namespace Ese
    {
        Ese::DetachDatabaseFlags ParseDetachDatabaseFlags( const WideString& str )
        {
            return detachDatabaseFlagsConverter.Parse( str );
        }

        Ese::DetachDatabaseFlags ParseDetachDatabaseFlags( const WideString& str, Ese::DetachDatabaseFlags defaultResult )
        {
            return detachDatabaseFlagsConverter.Parse( str, defaultResult );
        }

        bool TryParseDetachDatabaseFlags( const WideString& str, Ese::DetachDatabaseFlags& value )
        {
            return detachDatabaseFlagsConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // CreateDatabaseFlags
    // =========================================================================
    namespace
    {
        using CreateDatabaseFlags = Ese::CreateDatabaseFlags;
        class CreateDatabaseFlagsConverter : public Flags<CreateDatabaseFlags>
        {
        public:
            CreateDatabaseFlagsConverter( )
            {
                Add( L"None", CreateDatabaseFlags::None );
                Add( L"OverwriteExisting", CreateDatabaseFlags::OverwriteExisting );
                Add( L"RecoveryOff", CreateDatabaseFlags::RecoveryOff );
                Add( L"ShadowingOff", CreateDatabaseFlags::ShadowingOff );
            }
        };
        CreateDatabaseFlagsConverter createDatabaseFlagsConverter;
    }

    WideString ToWideString( Ese::CreateDatabaseFlags value )
    {
        return createDatabaseFlagsConverter.ToString( value );
    }
    WideString ToWideString( Ese::CreateDatabaseFlags value, const WideString& defaultResult )
    {
        return createDatabaseFlagsConverter.ToString( value, defaultResult );
    }

    namespace Ese
    {
        Ese::CreateDatabaseFlags ParseCreateDatabaseFlags( const WideString& str )
        {
            return createDatabaseFlagsConverter.Parse( str );
        }

        Ese::CreateDatabaseFlags ParseCreateDatabaseFlags( const WideString& str, Ese::CreateDatabaseFlags defaultResult )
        {
            return createDatabaseFlagsConverter.Parse( str, defaultResult );
        }

        bool TryParseCreateDatabaseFlags( const WideString& str, Ese::CreateDatabaseFlags& value )
        {
            return createDatabaseFlagsConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // OpenDatabaseFlags
    // =========================================================================
    namespace
    {
        using OpenDatabaseFlags = Ese::OpenDatabaseFlags;
        class OpenDatabaseFlagsConverter : public Flags<OpenDatabaseFlags>
        {
        public:
            OpenDatabaseFlagsConverter( )
            {
                Add( L"None", OpenDatabaseFlags::None );
                Add( L"Exclusive", OpenDatabaseFlags::Exclusive );
                Add( L"ReadOnly", OpenDatabaseFlags::ReadOnly );
            }
        };
        OpenDatabaseFlagsConverter openDatabaseFlagsConverter;
    }

    WideString ToWideString( Ese::OpenDatabaseFlags value )
    {
        return openDatabaseFlagsConverter.ToString( value );
    }
    WideString ToWideString( Ese::OpenDatabaseFlags value, const WideString& defaultResult )
    {
        return openDatabaseFlagsConverter.ToString( value, defaultResult );
    }

    namespace Ese
    {
        Ese::OpenDatabaseFlags ParseOpenDatabaseFlags( const WideString& str )
        {
            return openDatabaseFlagsConverter.Parse( str );
        }

        Ese::OpenDatabaseFlags ParseOpenDatabaseFlags( const WideString& str, Ese::OpenDatabaseFlags defaultResult )
        {
            return openDatabaseFlagsConverter.Parse( str, defaultResult );
        }

        bool TryParseOpenDatabaseFlags( const WideString& str, Ese::OpenDatabaseFlags& value )
        {
            return openDatabaseFlagsConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // InitFlags
    // =========================================================================
    namespace
    {
        using InitFlags = Ese::InitFlags;
        class InitFlagsConverter : public Flags<InitFlags>
        {
        public:
            InitFlagsConverter( )
            {
                Add( L"None", InitFlags::None );
                Add( L"ReplayIgnoreMissingDB", InitFlags::ReplayIgnoreMissingDB );
                Add( L"RecoveryWithoutUndo", InitFlags::RecoveryWithoutUndo );
                Add( L"TruncateLogsAfterRecovery", InitFlags::TruncateLogsAfterRecovery );
                Add( L"ReplayMissingMapEntryDB", InitFlags::ReplayMissingMapEntryDB );
                Add( L"LogStreamMustExist", InitFlags::LogStreamMustExist );
                Add( L"ReplayIgnoreLostLogs", InitFlags::ReplayIgnoreLostLogs );
                Add( L"KeepDbAttachedAtEndOfRecovery", InitFlags::KeepDbAttachedAtEndOfRecovery );
            }
        };
        InitFlagsConverter initFlagsConverter;
    }

    WideString ToWideString( Ese::InitFlags value )
    {
        return initFlagsConverter.ToString( value );
    }
    WideString ToWideString( Ese::InitFlags value, const WideString& defaultResult )
    {
        return initFlagsConverter.ToString( value, defaultResult );
    }

    namespace Ese
    {
        Ese::InitFlags ParseInitFlags( const WideString& str )
        {
            return initFlagsConverter.Parse( str );
        }

        Ese::InitFlags ParseInitFlags( const WideString& str, Ese::InitFlags defaultResult )
        {
            return initFlagsConverter.Parse( str, defaultResult );
        }

        bool TryParseInitFlags( const WideString& str, Ese::InitFlags& value )
        {
            return initFlagsConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // OnlineDefragFlags
    // =========================================================================
    namespace
    {
        using OnlineDefragFlags = Ese::OnlineDefragFlags;
        class OnlineDefragFlagsConverter : public Flags<OnlineDefragFlags>
        {
        public:
            OnlineDefragFlagsConverter( )
            {
                Add( L"All", OnlineDefragFlags::All );
                Add( L"Disable", OnlineDefragFlags::Disable );
                Add( L"Databases", OnlineDefragFlags::Databases );
                Add( L"SpaceTrees", OnlineDefragFlags::SpaceTrees );
            }
        };
        OnlineDefragFlagsConverter onlineDefragFlagsConverter;
    }

    WideString ToWideString( Ese::OnlineDefragFlags value )
    {
        return onlineDefragFlagsConverter.ToString( value );
    }
    WideString ToWideString( Ese::OnlineDefragFlags value, const WideString& defaultResult )
    {
        return onlineDefragFlagsConverter.ToString( value, defaultResult );
    }

    namespace Ese
    {
        Ese::OnlineDefragFlags ParseOnlineDefragFlags( const WideString& str )
        {
            return onlineDefragFlagsConverter.Parse( str );
        }

        Ese::OnlineDefragFlags ParseOnlineDefragFlags( const WideString& str, Ese::OnlineDefragFlags defaultResult )
        {
            return onlineDefragFlagsConverter.Parse( str, defaultResult );
        }

        bool TryParseOnlineDefragFlags( const WideString& str, Ese::OnlineDefragFlags& value )
        {
            return onlineDefragFlagsConverter.TryParse( str, value );
        }
    }

    // =========================================================================
    // BackupFlags
    // =========================================================================
    namespace
    {
        using BackupFlags = Ese::BackupFlags;
        class BackupFlagsConverter : public Flags<BackupFlags>
        {
        public:
            BackupFlagsConverter( )
            {
                Add( L"None", BackupFlags::None );
                Add( L"Atomic", BackupFlags::Atomic );
                Add( L"Incremental", BackupFlags::Incremental );
                Add( L"Snapshot", BackupFlags::Snapshot );
            }
        };
        BackupFlagsConverter backupFlagsConverter;
    }

    WideString ToWideString( Ese::BackupFlags value )
    {
        return backupFlagsConverter.ToString( value );
    }
    WideString ToWideString( Ese::BackupFlags value, const WideString& defaultResult )
    {
        return backupFlagsConverter.ToString( value, defaultResult );
    }

    namespace Ese
    {
        Ese::BackupFlags ParseBackupFlags( const WideString& str )
        {
            return backupFlagsConverter.Parse( str );
        }

        Ese::BackupFlags ParseBackupFlags( const WideString& str, Ese::BackupFlags defaultResult )
        {
            return backupFlagsConverter.Parse( str, defaultResult );
        }

        bool TryParseBackupFlags( const WideString& str, Ese::BackupFlags& value )
        {
            return backupFlagsConverter.TryParse( str, value );
        }
    }



}
