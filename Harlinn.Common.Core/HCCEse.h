#pragma once
#ifndef __HCCESENT_H__
#define __HCCESENT_H__

#include <HCCString.h>
#include <HCCDateTime.h>
#include <HCCCurrency.h>
#include <HCCGuid.h>
#include <HCCIO.h>
#include <HCCException.h>
#include <HCCLogging.h>
#include <HCCFlags.h>
#include <HCCEseResult.h>

#pragma comment(lib,"esent.lib") 

namespace Harlinn::Common::Core::Ese
{


    class Column;
    class Table;
    class Database;
    class Session;
    class Instance;
    class InstanceOptions;
    class DatabaseOptions;

    class Exception : public Core::Exception
    {
    public:
        using Base = Core::Exception;

        HCC_EXPORT Exception( JET_ERR rc );
        HCC_EXPORT Exception( Ese::Result rc );
        HCC_EXPORT static WideString GetErrorMessage( JET_ERR rc );
        HCC_EXPORT static WideString GetErrorMessage( Ese::Result rc );

        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS(Exception);
    };

    inline bool RequireSuccess( Result rc )
    {
        if ( rc == Result::Success )
        {
            return true;
        }
        else
        {
            HCC_THROW( Exception, rc );
        }
    }
    inline bool RequireNotError( Result rc )
    {
        if ( rc >= Result::Success )
        {
            return true;
        }
        else
        {
            HCC_THROW( Exception, rc );
        }
    }

    template<typename T>
    concept StringType = ( std::is_same_v<AnsiString, T> || std::is_same_v<WideString, T> );

    template<typename T>
    concept CharType = ( std::is_same_v<char, T> || std::is_same_v<wchar_t, T> );

    template<typename T>
    concept BinaryVectorType = ( std::is_same_v< std::vector<char>, T> ||
        std::is_same_v< std::vector<unsigned char>, T> ||
        std::is_same_v< std::vector<signed char>, T> );


    template<typename T>
    concept DirectType = ( ( std::is_integral_v<T> && !std::is_same_v<bool, T> ) ||
        std::is_floating_point_v<T> ||
        std::is_same_v<TimeSpan, T> ||
        std::is_same_v<Currency, T> ||
        std::is_same_v<Guid, T> );

    template<typename T>
    concept TableType = (std::is_base_of_v<Table, T> && 
        std::is_constructible_v<T, JET_SESID, JET_TABLEID> &&
        std::is_nothrow_default_constructible_v<T> &&
        std::is_move_assignable_v<T> && 
        std::is_move_constructible_v<T> &&
        !std::is_copy_assignable_v<T> &&
        !std::is_copy_constructible_v<T> );

    template<typename T>
    concept DatabaseType = ( std::is_base_of_v<Database, T> &&
        std::is_constructible_v<T, JET_SESID, JET_DBID> &&
        std::is_nothrow_default_constructible_v<T> &&
        std::is_move_assignable_v<T> &&
        std::is_move_constructible_v<T> &&
        !std::is_copy_assignable_v<T> &&
        !std::is_copy_constructible_v<T> );




    // Describes the column types that can be found in a table
    enum class ColumnType
    {
        None = JET_coltypNil,
        // True, False, or NULL 
        Boolean = JET_coltypBit,
        // 1-byte integer, unsigned 
        Byte = JET_coltypUnsignedByte,
        // 2-byte integer, signed 
        Short = JET_coltypShort,
        // 4-byte integer, signed 
        Long = JET_coltypLong,
        // 8 byte integer, signed 
        Currency = JET_coltypCurrency,
        // 4-byte IEEE single precision 
        Single = JET_coltypIEEESingle,
        // 8-byte IEEE double precision
        Double = JET_coltypIEEEDouble,
        // Integral date, fractional time
        DateTime = JET_coltypDateTime,
        // Binary data, < 255 bytes 
        Binary = JET_coltypBinary,
        // ANSI text, case insensitive, < 255 bytes 
        Text = JET_coltypText,
        // Binary data, long value 
        LongBinary = JET_coltypLongBinary,
        // ANSI text, long value 
        LongText = JET_coltypLongText,
        // SLV's
        SLV = JET_coltypSLV,
        // 4-byte unsigned integer
        UnsignedLong = JET_coltypUnsignedLong,
        // 8-byte signed integer 
        LongLong = JET_coltypLongLong,
        // 16-byte globally unique identifier 
        Guid = JET_coltypGUID,
        // 2-byte unsigned integer 
        UnsignedShort = JET_coltypUnsignedShort,
        // 8-byte unsigned integer
        UnsignedLongLong = JET_coltypUnsignedLongLong
    };


    enum class ColumnFlags : int
    {
        None = 0,
        // The column will be fixed.It will always use the same amount of space in 
        // a row, regardless of how much data is being stored in the column. 
        //
        // Fixed cannot be combined with Tagged or used with long values ( that is 
        // ColumnType::LongText and ColumnType::LongBinary ).
        Fixed = JET_bitColumnFixed,
        // The column will be tagged. Tagged columns do not take up any space in the 
        // database if they do not contain data. This bit cannot be combined with Fixed
        Tagged = JET_bitColumnTagged,
        // The column must never be set to a NULL value
        NotNULL = JET_bitColumnNotNULL,
        // The column is a version column that specifies the version of the row.
        // The value of this column starts at zero and will be automatically 
        // incremented for each update on the row.
        Version = JET_bitColumnVersion,
        // The column will automatically be incremented. 
        // The number is an increasing number, and is guaranteed to be unique within a table. 
        //
        // The numbers, however, might not be continuous. 
        // For example, if five rows are inserted into a table, the "autoincrement" column 
        // could contain the values { 1, 2, 6, 7, 8 }. This bit can only be used on columns 
        // of type ColumnType::Long or ColumnType::Currency.
        Autoincrement = JET_bitColumnAutoincrement,
        Updatable = JET_bitColumnUpdatable,
        TemporaryTableKey = JET_bitColumnTTKey,
        TemporaryTableDescending = JET_bitColumnTTDescending,
        MultiValued = JET_bitColumnMultiValued,
        EscrowUpdate = JET_bitColumnEscrowUpdate,
        Unversioned = JET_bitColumnUnversioned,
        Finalize = JET_bitColumnFinalize,
        UserDefinedDefault = JET_bitColumnUserDefinedDefault,
        // When the escrow-update column reaches a value of zero (after all versions are resolve),
        // the record will be deleted. A common use for a column that can be finalized is to use
        // it as a reference count field, and when the field reaches zero the record gets deleted.
        // A Delete-on-zero column must be an escrow update / JET_bitColumnEscrowUpdate column.
        // JET_bitColumnDeleteOnZero cannot be used with JET_bitColumnFinalize. JET_bitColumnDeleteOnZero
        // cannot be used with user defined default columns.
        DeleteOnZero = JET_bitColumnDeleteOnZero,

        // data in the column can be compressed
        Compressed = JET_bitColumnCompressed
    };
    
    HCC_DEFINE_ENUM_FLAG_OPERATORS( ColumnFlags, int );

    class ColumnCreate : public JET_COLUMNCREATE_W
    {
        using Base = JET_COLUMNCREATE_W;
    public:
        ColumnCreate()
            : Base{ sizeof( JET_COLUMNCREATE_W ),0, }
        {
        }
    };



    enum class IndexFlags : int
    {
        None = 0,
        Unique = JET_bitIndexUnique,
        Primary = JET_bitIndexPrimary,
        DisallowNull = JET_bitIndexDisallowNull,
        IgnoreNull = JET_bitIndexIgnoreNull,
        IgnoreAnyNull = JET_bitIndexIgnoreAnyNull,
        IgnoreFirstNull = JET_bitIndexIgnoreFirstNull,
        LazyFlush = JET_bitIndexLazyFlush,
        // don't attempt to build index, because all entries 
        // would evaluate to NULL (MUST also specify JET_bitIgnoreAnyNull)
        Empty = JET_bitIndexEmpty,
        Unversioned = JET_bitIndexUnversioned,
        // NULL sorts after data for all columns in the index
        SortNullsHigh = JET_bitIndexSortNullsHigh,
        // LCID field of JET_INDEXCREATE actually points 
        // to a JET_UNICODEINDEX struct to allow user-defined 
        // LCMapString() flags
        Unicode = JET_bitIndexUnicode,
        // index on substring tuples (text columns only)
        Tuples = JET_bitIndexTuples,
        // cbVarSegMac field of JET_INDEXCREATE actually 
        // points to a JET_TUPLELIMITS struct to allow 
        // custom tuple index limits (implies JET_bitIndexTuples)
        TupleLimits = JET_bitIndexTupleLimits,
        // index over multiple multi-valued columns 
        // has full cross product
        CrossProduct = JET_bitIndexCrossProduct,
        // custom index key size set instead of 
        // default of 255 bytes
        KeyMost = JET_bitIndexKeyMost,
        // fail update rather than truncate index keys
        DisallowTruncation = JET_bitIndexDisallowTruncation,
        // index over multiple multi-valued columns but 
        // only with values of same itagSequence
        NestedTable = JET_bitIndexNestedTable,
        // index over GUID column according to .Net GUID sort order
        DotNetGuid = 0x00040000
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( IndexFlags, int );


    enum class RetrieveFlags : int
    {
        None = 0,
        // This flag causes retrieve column to retrieve the 
        // modified value instead of the original value. If 
        // the value has not been modified, then the original 
        // value is retrieved. In this way, a value that has 
        // not yet been inserted or updated may be retrieved 
        // during the operation of inserting or updating a record.
        Copy = JET_bitRetrieveCopy,
        // This option is used to retrieve column values from 
        // the index, if possible, without accessing the record. 
        // In this way, unnecessary loading of records can be 
        // avoided when needed data is available from index 
        // entries themselves. In cases where the original column 
        // value cannot be retrieved from the index, because of 
        // irreversible transformations or data truncation, the 
        // record will be accessed and the data retrieved as 
        // normal. This is a performance option and should only 
        // be specified when it is likely that the column value 
        // can be retrieved from the index. This option should 
        // not be specified if the current index is the clustered 
        // index, since the index entries for the clustered, 
        // or primary, index are the records themselves. This 
        // bit cannot be set if FromPrimaryBookmark is also set.
        FromIndex = JET_bitRetrieveFromIndex,
        // This option is used to retrieve column values from 
        // the index bookmark, and may differ from the index 
        // value when a column appears both in the primary index 
        // and the current index. This option should not be 
        // specified if the current index is the clustered, 
        // or primary, index. This bit cannot be set if 
        // FromIndex is also set.
        FromPrimaryBookmark = JET_bitRetrieveFromPrimaryBookmark,
        // This option is used to retrieve the sequence number 
        // of a multi-valued column value in pretinfo->itagSequence. 
        // The itagSequence field is commonly an input for 
        // retrieving multi-valued column values from a record. 
        // However, when retrieving values from an index, it is 
        // also possible to associate the index entry with a 
        // particular sequence number and retrieve this sequence 
        // number as well. Retrieving the sequence number can 
        // be a costly operation and should only be done if necessary.
        Tag = JET_bitRetrieveTag,
        // This option is used to retrieve multi-valued column 
        // NULL values. If this option is not specified, 
        // multi-valued column NULL values will automatically 
        // be skipped.
        Null = JET_bitRetrieveNull,
        // This option affects only multi-valued columns and 
        // causes a NULL value to be returned when the requested 
        // sequence number is 1 and there are no set values for 
        // the column in the record.
        IgnoreDefault = JET_bitRetrieveIgnoreDefault,
        // This flag will allow the retrieval of a tuple segment 
        // of the index. This bit must be specified with 
        // FromIndex.
        Tuple = JET_bitRetrieveTuple
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( RetrieveFlags, int );

    enum class SetFlags : int
    {
        None = 0,
        // This option is used to append data to a column of type 
        // ColumnType::LongText or ColumnType::LongBinary. 
        // The same behavior can be achieved by determining the size 
        // of the existing long value and specifying ibLongValue in 
        // psetinfo. However, it's simpler to use this AppendLV since 
        // knowing the size of the existing column value is not necessary.
        AppendLV = JET_bitSetAppendLV,
        // This option is used replace the existing long value with 
        // the newly provided data. When this option is used, it is 
        // as though the existing long value has been set to 0 (zero) 
        // length prior to setting the new data.
        OverwriteLV = JET_bitSetOverwriteLV,
        // This option is only applicable for tagged, sparse or 
        // multi-valued columns. It causes the column to return 
        // the default column value on subsequent retrieve column 
        // operations. All existing column values are removed.
        RevertToDefaultValue = JET_bitSetRevertToDefaultValue,
        // This option is used to force a long value, columns of type 
        // ColumnType::LongText or ColumnType::LongBinary, to 
        // be stored separately from the remainder of record data. 
        // This occurs normally when the size of the long value 
        // prevents it from being stored with remaining record data. 
        // However, this option can be used to force the long value 
        // to be stored separately. Note that long values four bytes 
        // in size of smaller cannot be forced to be separate. 
        // In such cases, the option is ignored.
        SeparateLV = JET_bitSetSeparateLV,
        // This option is used to interpret the input buffer as 
        // a integer number of bytes to set as the length of 
        // the long value described by the given columnid and 
        // if provided, the sequence number in psetinfo->itagSequence. 
        // If the size given is larger than the existing column value, 
        // the column will be extended with 0s. If the size is smaller 
        // than the existing column value then the value will be 
        // truncated.
        SizeLV = JET_bitSetSizeLV,
        // This option is used to enforce that all values in a 
        // multi-valued column are distinct. This option compares 
        // the source column data, without any transformations, 
        // to other existing column values and an error is 
        // returned if a duplicate is found. If this option is given, 
        // then AppendLV, OverwriteLV and SizeLV cannot also be given.
        UniqueMultiValues = JET_bitSetUniqueMultiValues,
        // This option is used to enforce that all values in a 
        // multi-valued column are distinct. This option compares 
        // the key normalized transformation of column data, to 
        // other similarly transformed existing column values 
        // and an error is returned if a duplicate is found. If 
        // this option is given, then AppendLV, OverwriteLV and 
        // SizeLV cannot also be given.
        UniqueNormalizedMultiValues = JET_bitSetUniqueNormalizedMultiValues,
        // This option is used to set a value to zero length. Normally, 
        // a column value is set to NULL by passing a cbMax of 0 (zero). 
        // However, for some types, like ColumnType::Text, a column 
        // value can be 0 (zero) length instead of NULL, and this 
        // option is used to differentiate between NULL and 
        // 0 (zero) length.
        // 
        // Note: In general, if the column is a fixed - length column, 
        // this bit is ignored and the column is set to NULL.However, 
        // if the column is a fixed - length tagged column, the column 
        // length is set to 0. When the fixed - length tagged column 
        // is set to 0 length, attempts to retrieve the column with 
        // will succeed, but the actual length that is returned 
        // in the cbActual parameter is 0.
        ZeroLength = JET_bitSetZeroLength,
        // This option is used to store the entire long value in the record.
        IntrinsicLV = JET_bitSetIntrinsicLV,
        // This option is used to attempt data compression when storing 
        // the data.
        Compressed = JET_bitSetCompressed,
        // This option is used to not attempt compression when storing 
        // the data.
        Uncompressed = JET_bitSetUncompressed
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( SetFlags, int );

    /// <summary>
    /// Info levels for retrieving column info.
    /// </summary>
    enum class ColumnInfoFlags : unsigned long
    {
        // pvResult is interpreted as a JET_COLUMNDEF, and the 
        // fields of the JET_COLUMNDEF structure are filled in 
        // appropriately. JET_ColInfo and JET_ColInfoByColid 
        // both retrieve the same information.
        Default = JET_ColInfo,
        // pvResult is interpreted as a JET_COLUMNBASE structure. 
        // This is similar to a JET_COLUMNDEF structure. If this 
        // function succeeds, the structure is populated with 
        // appropriate values. If this function fails, the 
        // structure contains undefined data
        Base = JET_ColInfoBase,
        // pvResult is interpreted as a JET_COLUMNDEF, except this 
        // InfoLevel indicates that the requested column 
        // ( szColumName) is not the string column name, but a 
        // pointer to a JET_COLUMNID. Info and InfoByColid both 
        // retrieve the same information.
        ByColid = JET_ColInfoByColid,
        // pvResult is interpreted as a JET_COLUMNLIST structure. 
        // If this function succeeds, the structure is populated 
        // with appropriate values. A temporary table is opened 
        // and is identified by the tableid member of 
        // JET_COLUMNLIST. The table must be closed with 
        // JetCloseTable. If this function fails, the structure 
        // contains undefined data.
        List = JET_ColInfoList,
        // pvResult is interpreted as a JET_COLUMNLIST structure. 
        // If this function succeeds, the structure is populated 
        // with appropriate values. A temporary table is opened 
        // and is identified by the tableid member of JET_COLUMNLIST. 
        // The table must be closed with JetCloseTable. If this 
        // function fails, the structure contains undefined data.
        ListCompact = JET_ColInfoListCompact,
        // Same as List, however the resulting table is sorted 
        // by columnid, instead of column name.
        ListSortColumnId = JET_ColInfoListSortColumnid,
        // Same as InfoBase, pvResult is interpreted as a 
        // JET_COLUMNBASE, except this InfoLevel indicates that 
        // requested column ( theColumName ) is not the string 
        // column name, but a pointer to a JET_COLUMNID.
        BaseByColId = JET_ColInfoBaseByColid,
        // Only return non-derived columns (if the table is 
        // derived from a template). This value can be logically 
        // or'd into the InfoLevel, when the base InfoLevel is 
        // InfoList.
        NonDerivedColumnsOnly = JET_ColInfoGrbitNonDerivedColumnsOnly,
        // Only return the column name and columnid of each 
        // column. This value can be logically or'd into 
        // the InfoLevel, when the base InfoLevel is InfoList.
        MinimalInfo = JET_ColInfoGrbitMinimalInfo,
        // Sort returned column list by columnid (default is 
        // to sort list by column name). This value can be logically 
        // or'd into the InfoLevel, when the base InfoLevel is 
        // InfoList.
        SortByColumnId = JET_ColInfoGrbitSortByColumnid
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( ColumnInfoFlags, unsigned long );


    enum class PrepareUpdateOptions : unsigned long
    {
        //This flag causes PrepareUpdate to cancel the update for this cursor.
        Cancel = JET_prepCancel,
        // This flag causes the cursor to prepare for an insert of a new record. 
        // All the data is initialized to the default state for the record. If 
        // the table has an auto-increment column, then a new value is assigned 
        // to this record regardless of whether the update ultimately succeeds, 
        // fails or is cancelled.
        Insert = JET_prepInsert,
        // This flag causes the cursor to prepare for an insert of a copy of 
        // the existing record. There must be a current record if this option 
        // is used. The initial state of the new record is copied from the 
        // current record. Long values that are stored off-record are 
        // virtually copied.
        Copy = JET_prepInsertCopy,
        // This flag causes the cursor to prepare for an insert of the same 
        // record, and a delete or the original record. It is used in cases 
        // in which the primary key has changed.
        InsertCopyDeleteOriginal = JET_prepInsertCopyDeleteOriginal,
        // This flag causes the cursor to prepare for a replace of the current 
        // record. If the table has a version column, then the version column 
        // is set to the next value in its sequence. If this update does not 
        // complete, then the version value in the record will be unaffected. 
        // An update lock is taken on the record to prevent other sessions 
        // from updating this record before this session completes.
        Replace = JET_prepReplace,
        // This flag is similar to Replace, but no lock is taken to prevent 
        // other sessions from updating this record. Instead, this session 
        // may receive JET_errWriteConflict when it calls Update to 
        // complete the update.
        ReplaceNoLock = JET_prepReplaceNoLock
    };


    enum class KeyFlags : unsigned long
    {
        None = 0,
        // The search key should be constructed in such a way that any key columns that come 
        // after the current key column are considered to be wildcards. This means that the 
        // constructed search key can be used to match index entries that have the following:
        //
        //    * The exact column values provided for this key column and all previous key columns.
        //    * Any column values needed for subsequent key columns.
        //
        // This option should be used when building wildcard search keys to use for finding index 
        // entries closest to the end of an index.The end of the index is the index entry that is 
        // found when moving to the last record in that index.The end of the index is not the 
        // same as the high end of the index, which can change depending on the sort order of 
        // the key columns in the index.
        //
        // This option is only available on Windows XP and later releases.
        FullColumnEndLimit = JET_bitFullColumnEndLimit,

        // The search key should be constructed such that any key columns that come after the 
        // current key column should be considered to be wildcards. This means that the constructed 
        // search key can be used to match index entries that have the following:
        //
        //    * The exact column values provided for this key column and all previous key columns.
        //    * Any column values needed for subsequent key columns.
        //
        // This option should be used when building wildcard search keys to use for finding index 
        // entries closest to the start of an index.The start of the index is the index entry that 
        // is found when moving to the first record in that index.The start of the index is not the 
        // same as the low end of the index, which can change depending on the sort order of the 
        // key columns in the index.
        //
        // This option is only available on Windows XP and later releases.
        FullColumnStartLimit = JET_bitFullColumnStartLimit,

        // If the size of the input buffer is zero and the current key column is a variable 
        // length column, this option indicates that the input buffer contains a zero length 
        // value. Otherwise, an input buffer size of zero would indicate a NULL value.
        KeyDataZeroLength = JET_bitKeyDataZeroLength,

        // A new search key should be constructed. Any previously existing search key is discarded.
        NewKey = JET_bitNewKey,

        // When this option is specified, all other options are ignored, any previously existing 
        // search key is discarded, and the contents of the input buffer are loaded as the new search key.
        NormalizedKey = JET_bitNormalizedKey,

        // The search key should be constructed such that the current key column is considered to be 
        // a prefix wildcard and that any key columns that come after the current key column should 
        // be considered to be wildcards. This means that the constructed search key can be used to 
        // match index entries that have the following:
        //
        //    * The exact column values provided for this key column and all previous key columns.
        //    * Any column values needed for subsequent key columns.
        //
        // This option should be used when building wildcard search keys to use for finding index 
        // entries closest to the end of an index.The end of the index is the index entry that 
        // is found when moving to the last record in that index.The end of the index is not the 
        // same as the high end of the index, which can change depending on the sort order of 
        // the key columns in the index.
        //
        // This option cannot be used when the current key column is not a text column or a 
        // variable binary column.The operation will fail with JET_errInvalidgrbit if this 
        // is attempted.
        //
        // This option is only available on Windows XP and later releases.
        PartialColumnEndLimit = JET_bitPartialColumnEndLimit,

        // This option indicates that the search key should be constructed such that the current 
        // key column is considered to be a prefix wildcard and that any key columns that come 
        // after the current key column should be considered to be wildcards.This means that 
        // the constructed search key can be used to match index entries that have the following:
        //
        //    * The exact column values provided for this key column and all previous key columns.
        //    * Any column values needed for subsequent key columns.
        //
        // This option should be used when building wildcard search keys to use for finding 
        // index entries closest to the start of an index.The start of the index is the index 
        // entry that is found when moving to the first record in that index.The start of 
        // the index is not the same as the low end of the index, which can change depending 
        // on the sort order of the key columns in the index.
        //
        // This option cannot be used when the current key column is not a text column or a 
        // variable binary column.The operation will fail with JET_errInvalidgrbit if this is attempted.
        //
        // This option is only available on Windows XP and later releases.
        PartialColumnStartLimit = JET_bitPartialColumnStartLimit,

        // This option indicates that the search key should be constructed such that any key 
        // columns that come after the current key column should be considered to be wildcards.
        // This means that the constructed search key can be used to match index entries that 
        // have the following:
        //
        //    * The exact column values provided for this key column and all previous key columns.
        //    * Any column values needed for subsequent key columns.
        //
        // This option should be used when building wildcard search keys to use for finding 
        // index entries closest to the end of an index.The end of the index is the index 
        // entry that is found when moving to the last record in that index.The end of the 
        // index is not the same as the high end of the index, which can change depending on 
        // the sort order of the key columns in the index.
        //
        // When this option is specified in combination with JET_bitSubStrLimit and the 
        // current key column is a text column, this option will be ignored.This behavior 
        // is intended to allow the type of the current key column to be inferred when building 
        // the search key.
        //
        // If you want to build a similar search key for the start of an index, a similar call 
        // to JetMakeKey should be made for the last key column that is not a wildcard, but 
        // with no wildcard options specified.The search key is then in an appropriate state 
        // to use for such a search.This is analogous to using JET_bitFullColumnStartLimit, 
        // except that the search key is not cleanly finished as it is after the use of a wildcard option.
        //
        // This option has been deprecated for Windows XP and later releases in order to address 
        // this awkward semantic.JET_bitFullColumnStartLimit and JET_bitFullColumnEndLimit 
        // should be used instead wherever possible.
        StrLimit = JET_bitStrLimit,

        // This option indicates that the search key should be constructed such that the current 
        // key column is considered to be a prefix wildcard and that any key columns that come 
        // after the current key column should be considered to be wildcards.This means that 
        // the constructed search key can be used to match index entries that have the following :
        // 
        //    * The exact column values provided for all previous key columns.
        //    * The specified column data as a prefix of their column value for the current key column.
        //    * Any column values for subsequent key columns.
        // 
        // This option should be used when building wildcard search keys to use for finding index 
        // entries closest to the end of an index.The end of the index is the index entry that 
        // is found when moving to the last record in that index.The end of the index is not the 
        // same as the high end of the index, which can change depending on the sort order of 
        // the key columns in the index.
        //
        // When this option is specified in combination with StrLimit and the current key column is 
        // a text column, this option will take precedence. This option is ignored when the current key 
        // column is not a text column. This behavior is intended to allow the type of the current 
        // key column to be inferred when building the search key.
        //
        // If you want to build a similar search key for the start of an index, a similar call to 
        // Table::MakeKey should be made for the key column that is to be the prefix wildcard, 
        // but with that no wildcard options specified.The search key is then in an appropriate 
        // state to use for such a search.This is analogous to using PartialColumnStartLimit, except 
        // that the search key is not cleanly finished as it is after the use of a wildcard option.
        //
        // This option has been deprecated for Windows XP and later releases in order to address 
        // this awkward semantic. PartialColumnStartLimit and PartialColumnEndLimit should be used 
        // instead, when possible.
        SubStrLimit = JET_bitSubStrLimit
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( KeyFlags, unsigned long );

    enum class SeekFlags : unsigned long
    {
        None = 0,
        // A special error code, JET_wrnUniqueKey, will be returned if it can 
        // be cheaply determined that there is exactly one index entry that 
        // matches the search key.
        //
        // This option is ignored unless Equal is also specified.
        //
        // This option is only available on Windows Server 2003 and later releases.
        CheckUniqueness = JET_bitCheckUniqueness,

        // The cursor will be positioned at the index entry closest to the start of 
        // the index that exactly matches the search key. The start of the index is 
        // the index entry that is found when moving to the first record in that 
        // index. The start of the index is not the same as the low end of the 
        // index, which can change depending on the sort order of the key columns 
        // in the index.
        // 
        // It is not meaningful to use this option with a search key that was constructed 
        // using Table::MakeKey using a wildcard option.
        Equal = JET_bitSeekEQ,

        // The cursor will be positioned at the index entry closest to the start of the index 
        // that is greater than or equal to an index entry that would exactly match the search 
        // criteria. The start of the index is the index entry that is found when moving to the 
        // first record in that index. The start of the index is not the same as the low end 
        // of the index, which can change depending on the sort order of the key columns in 
        // the index.
        //
        // It is not meaningful to use this option with a search key that was constructed using 
        // Table::MakeKey using a wildcard option intended to find index entries closest 
        // to the end of the index.
        GreaterOrEqual = JET_bitSeekGE,

        // The cursor will be positioned at the index entry closest to the start of the index 
        // that is greater than an index entry that would exactly match the search criteria. 
        // The start of the index is the index entry that is found when moving to the first 
        // record in that index. The start of the index is not the same as the low end of 
        // the index, which can change depending on the sort order of the key columns in 
        // the index.
        //
        // It is not meaningful to use this option with a search key that was constructed 
        // using Table::MakeKey using a wildcard option intended to find index entries 
        // closest to the start of the index.
        Greater = JET_bitSeekGT,

        // The cursor will be positioned at the index entry closest to the end of the index 
        // that is less than or equal to an index entry that would exactly match the search 
        // criteria. The end of the index is the index entry that is found when moving to 
        // the last record in that index. The end of the index is not the same as the high 
        // end of the index, which can change depending on the sort order of the key columns 
        // in the index.
        //
        // It is not meaningful to use this option with a search key that was constructed 
        // using Table::MakeKey using a wildcard option intended to find index entries 
        // closest to the start of the index.
        LessOrEqual = JET_bitSeekLE,

        // The cursor will be positioned at the index entry closest to the end of the index 
        // that is less than an index entry that would exactly match the search criteria. 
        // The end of the index is the index entry that is found when moving to the last 
        // record in that index. The end of the index is not the same as the high end of 
        // the index, which can change depending on the sort order of the key columns in 
        // the index.
        //
        // It is not meaningful to use this option with a search key that was constructed 
        // using Table::MakeKey using a wildcard option intended to find index entries 
        // closest to the end of the index.
        Less = JET_bitSeekLT,

        // An index range will automatically be setup for all keys that exactly match the 
        // search key. The resulting index range is identical to one that would have 
        // otherwise been created by a call to Table::SetIndexRange with the 
        // JET_bitRangeInclusive and JET_bitRangeUpperLimit options. 
        // See JetSetIndexRange for more information.
        //
        // This is a convenient method for discovering all the index entries that match 
        // the same search criteria.
        //
        // This option is ignored unless Equal is also specified.
        SetIndexRange = JET_bitSetIndexRange
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( SeekFlags, unsigned long );

    enum class IndexRangeFlags : unsigned long
    {
        None = 0,
        Inclusive = JET_bitRangeInclusive,
        UpperLimit = JET_bitRangeUpperLimit,
        InstantDuration = JET_bitRangeInstantDuration,
        Remove = JET_bitRangeRemove
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( IndexRangeFlags, unsigned long );

    enum class SetCurrentIndexFlags : unsigned long
    {
        // This option indicates that the cursor should be positioned on the first 
        // entry of the specified index. If the clustered index is being selected 
        // (primary index or sequential index) and the current index is a secondary 
        // index then JET_bitMoveFirst is assumed. If the current index is being 
        // selected then this option is ignored and no change to the cursor position 
        // is made.
        MoveFirst = JET_bitMoveFirst,
        // This option indicates that the cursor should be positioned on the index 
        // entry of the new index that corresponds to the record associated with the 
        // index entry at the current position of the cursor on the old index.
        NoMove = JET_bitNoMove
    };                                   


    class IndexCreate : public JET_INDEXCREATE_W
    {
        using Base = JET_INDEXCREATE_W;
    public:
        IndexCreate( )
            : Base{ sizeof( Base ),0, }
        {
        }
    };

    class TableCreate : public JET_TABLECREATE_W
    {
        using Base = JET_TABLECREATE_W;
    public:
        TableCreate( )
            : Base{ sizeof( Base ),0, }
        {
        }
    };



    class ColumnId
    {
        JET_COLUMNID column_;
    public:
        ColumnId( )
            : column_(0)
        { }

        ColumnId( JET_COLUMNID value )
            : column_( value )
        {
        }

        ColumnId& operator = ( JET_COLUMNID value )
        {
            column_ = value;
            return *this;
        }

        JET_COLUMNID Value( ) const
        {
            return column_;
        }
    };


    class ColumnDefinition : public JET_COLUMNDEF
    {
        using Base = JET_COLUMNDEF;
    public:
        constexpr ColumnDefinition( )
            : Base{ sizeof( Base ),0, }
        {
        }
        constexpr ColumnDefinition(ColumnType columnType, ColumnFlags columnFlags )
            : Base{ sizeof( Base ),0, static_cast<JET_COLTYP>( columnType ), 0,0,0,0,0, static_cast<JET_GRBIT>( columnFlags ) }
        {
        }

        constexpr ColumnDefinition( ColumnType columnType, unsigned long maxColumnSize, ColumnFlags columnFlags )
            : Base{ sizeof( Base ),0, static_cast<JET_COLTYP>( columnType ), 0,0,0,0,maxColumnSize, static_cast<JET_GRBIT>( columnFlags ) }
        {
        }

        constexpr ColumnDefinition(ColumnType columnType, unsigned short codePage ,unsigned long maxColumnSize, ColumnFlags columnFlags)
            : Base{ sizeof(Base),0, static_cast<JET_COLTYP>(columnType), 0,0,codePage,0,maxColumnSize, static_cast<JET_GRBIT>(columnFlags) }
        {
        }


    };


    enum class TableOptions : int
    {
        None = 0,
        Updatable = JET_bitTableInfoUpdatable,
        Bookmark = JET_bitTableInfoBookmark,
        Rollback = JET_bitTableInfoRollback
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( TableOptions, int );

    enum class ObjectFlags : unsigned
    {
        None = 0,
        // The table is a System Table and is for internal use only.
        System = JET_bitObjectSystem,
        // The table inherited DDL from a template table
        Derived = JET_bitObjectTableDerived,
        // The DDL for the table cannot be modified
        FixedDDL = JET_bitObjectTableFixedDDL,
        // Used in conjunction with JET_bitObjectTableTemplate to 
        // disallow fixed or variable columns in derived tables 
        // (so that fixed or variable columns can be added to 
        // the template in the future).
        NoFixedVarColumnsInDerivedTables = JET_bitObjectTableNoFixedVarColumnsInDerivedTables,
        // The table is a template table.
        Template = JET_bitObjectTableTemplate
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( ObjectFlags, unsigned );


    enum class SequentialFlags : unsigned
    {
        None = 0,
        PrereadForward = JET_bitPrereadForward,
        PrereadBackward = JET_bitPrereadBackward
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( SequentialFlags, unsigned );

    enum class ExceptionAction : long
    {
        // Displays message box on exception
        DisplayMessageBox = JET_ExceptionMsgBox,
        // Do nothing on exceptions
        None = JET_ExceptionNone,
        // Use the Windows RaiseFailFastException API to force a crash
        FailFast = JET_ExceptionFailFast
    };


    class Columns;

    /// <summary>
    /// The Table class manages a handle to a database cursor that is used to 
    /// call to the JET API. A cursor can only be used with the session that was 
    /// used to open that cursor.
    ///
    /// A cursor manages the use of a table for the database engine. A cursor can do the following tasks:
    ///      Scan records
    ///      Search for records
    ///      Choose the effective sort order and visibility of those records
    ///      Create, update, or delete records
    ///      Modify the schema of the table
    ///
    /// The supported functionality of the cursor might change as the status or type of 
    /// the underlying table changes. For example, a temporary table might disallow 
    /// searching for data when it is opened with certain options. 
    ///
    /// The cursor is always fully connected to the underlying table and interacts with 
    /// that data directly without any caching. Almost all of the core ISAM functionality 
    /// that is exposed by this database engine is works through the cursor.
    /// </summary>
    class Table
    {
        friend class Database;
        JET_SESID sessionId_;
        JET_TABLEID tableId_;
    public:
        using ColumnId = JET_COLUMNID;

        constexpr Table( ) noexcept
            : sessionId_( JET_sesidNil ),
              tableId_( JET_tableidNil ) 
        {
        }

        Table( JET_SESID sessionId, JET_TABLEID tableId )
            : sessionId_( sessionId ), tableId_( tableId )
        {
            if ( sessionId_ == JET_sesidNil )
            {
                throw ArgumentException( "Invalid session handle" );
            }
            if ( tableId_ == JET_tableidNil )
            {
                throw ArgumentException( "Invalid table handle" );
            }
        }
        ~Table( )
        {
            Close( );
        }

        Table( const Table& other ) = delete;

        Table( Table&& other ) noexcept
            : sessionId_( other.sessionId_ ), tableId_( other.tableId_ )
        {
            other.sessionId_ = JET_sesidNil;
            other.tableId_ = JET_tableidNil;
        }
        Table& operator = ( const Table& other ) = delete;

        Table& operator = ( Table&& other ) noexcept
        {
            if ( &other != this )
            {
                if ( tableId_ != JET_tableidNil )
                {
                    JetCloseTable( this->sessionId_, tableId_ );
                }
                sessionId_ = other.sessionId_;
                tableId_ = other.tableId_;

                other.sessionId_ = JET_sesidNil;
                other.tableId_ = JET_tableidNil;
            }
            return *this;
        }
        /// <summary>
        /// Returns the handle to the database table cursor
        /// </summary>
        JET_TABLEID Handle( ) const
        {
            return tableId_;
        }

        bool IsValid( ) const noexcept
        {
            return (sessionId_ != JET_sesidNil) && (tableId_ != JET_tableidNil);
        }

        explicit operator bool( ) const noexcept
        {
            return IsValid( );
        }

        /// <summary>
        /// Returns the handle to the session used to create or 
        /// open the table cursor
        /// </summary>
        JET_SESID SessionHandle( ) const
        {
            return sessionId_;
        }
    public:
        /// <summary>
        /// This function is called from Database::OpenTable
        /// allowing derived types to perform additional
        /// operations after the object is fully created.
        /// </summary>
        void OnTableOpened( )
        {
        }
        /// <summary>
        /// This function is called from Database::CreateTable
        /// allowing derived types to perform additional
        /// operations after the object is fully created.
        /// </summary>
        void OnTableCreated( )
        {
        }
    public:

        /// <summary>
        /// MakeKey constructs search keys that is used to find a set of entries 
        /// in an index by some simple search criteria on their key column values. 
        ///
        /// A search key is also one of the intrinsic properties of a cursor 
        /// and is used by the Seek and SetIndexRange methods to locate index 
        /// entries matching these search criteria on the current index of that cursor. 
        ///
        /// A complete search key is built up in a series of MakeKey calls where each 
        /// call is used to load the column value for the next key column of the current 
        /// index of a cursor. It is also possible to load a previously constructed 
        /// search key that has been retrieved from the cursor using RetrieveKey.
        /// </summary>
        void MakeKey( const void* keyData, unsigned long keyDataLength, KeyFlags flags = KeyFlags::None ) const
        {
            auto rc = static_cast<Result>( JetMakeKey( sessionId_, tableId_, keyData, keyDataLength, static_cast<JET_GRBIT>( flags ) ) );
            RequireSuccess( rc );
        }

        template<DirectType T>
        void MakeKey( const T& keyData, KeyFlags flags = KeyFlags::None ) const
        {
            MakeKey( &keyData, sizeof( std::decay_t<T> ), flags );
        }

        void MakeKey( const DateTime& dateTime, KeyFlags flags = KeyFlags::None ) const
        {
            double keyData = dateTime.ToOADate( );
            MakeKey( &keyData, sizeof( double ), flags );
        }
        template<typename T>
            requires std::is_same_v<bool,T>
        void MakeKey( T value, KeyFlags flags = KeyFlags::None ) const
        {
            Byte keyData = value ? 1 : 0;
            MakeKey( &keyData, sizeof( Byte ), flags );
        }

        template<StringType T>
        void MakeKey( const T& value, KeyFlags flags = KeyFlags::None ) const
        {
            using CharT = typename T::value_type;
            unsigned long keySize = static_cast<unsigned long>(value.length( ) * sizeof( CharT ));
            MakeKey( value.c_str(), keySize, flags );
        }

        void MakeKey( const char* value, KeyFlags flags = KeyFlags::None ) const
        {
            unsigned long keySize = static_cast<unsigned long>( strlen(value) );
            MakeKey( value, keySize, flags );
        }
        void MakeKey( const wchar_t* value, KeyFlags flags = KeyFlags::None ) const
        {
            unsigned long keySize = static_cast<unsigned long>( wcslen( value )*sizeof(wchar_t) );
            MakeKey( value, keySize, flags );
        }


        void SetIndexRange( IndexRangeFlags flags = Ese::IndexRangeFlags::None ) const
        {
            auto rc = static_cast<Result>( JetSetIndexRange( sessionId_, tableId_, static_cast<JET_GRBIT>( flags ) ) );
            RequireSuccess( rc );
        }




        /// <summary>
        /// Retrieves the key for the index entry at the current position of a cursor. 
        ///
        /// Such keys are constructed by calls to MakeKey. 
        ///
        /// The retrieved key can then be used to efficiently return that cursor to 
        /// the same index entry by a call to Seek
        /// </summary>
        void RetrieveKey( void* keyData, unsigned long maxKeyDataLength, unsigned long* actualKeyDataLength, bool retrieveCopyOfSearchKey = true ) const
        {
            auto rc = static_cast<Result>( JetRetrieveKey( sessionId_, tableId_, keyData, maxKeyDataLength, actualKeyDataLength, retrieveCopyOfSearchKey ? JET_bitRetrieveCopy : 0 ) );
            if ( rc != Result::Success && rc != Result::WarningBufferTruncated )
            {
                HCC_THROW( Exception, rc );
            }
        }


        void SetCurrentIndex( const wchar_t* indexName ) const
        {
            auto rc = static_cast<Result>( JetSetCurrentIndexW( sessionId_, tableId_, indexName ) );
            RequireSuccess( rc );
        }
        void SetCurrentIndex( const char* indexName ) const
        {
            auto rc = static_cast<Result>( JetSetCurrentIndexA( sessionId_, tableId_, indexName ) );
            RequireSuccess( rc );
        }

        template<StringType T>
        void SetCurrentIndex( const T& indexName ) const
        {
            SetCurrentIndex( indexName.c_str( ) );
        }

        void SetCurrentIndex( const wchar_t* indexName, SetCurrentIndexFlags flags ) const
        {
            auto rc = static_cast<Result>( JetSetCurrentIndex2W( sessionId_, tableId_, indexName, static_cast<JET_GRBIT>( flags ) ) );
            if ( rc != Result::Success && rc != Result::ErrorNoCurrentRecord )
            {
                HCC_THROW( Exception, rc );
            }
        }
        void SetCurrentIndex( const char* indexName, SetCurrentIndexFlags flags ) const
        {
            auto rc = static_cast<Result>( JetSetCurrentIndex2A( sessionId_, tableId_, indexName, static_cast<JET_GRBIT>( flags ) ) );
            if ( rc != Result::Success && rc != Result::ErrorNoCurrentRecord )
            {
                HCC_THROW( Exception, rc );
            }
        }


        Ese::Result Seek( SeekFlags flags ) const
        {
            auto rc = static_cast<Result>( JetSeek( sessionId_, tableId_, static_cast<JET_GRBIT>( flags ) ) );
            if ( rc != Result::Success &&
                rc != Result::WarningUniqueKey &&
                rc != Result::WarningSeekNotEqual &&
                rc != Result::ErrorRecordNotFound )
            {
                HCC_THROW( Exception, rc );
            }
            return rc;
        }

        Ese::Result SeekNX( SeekFlags flags ) const
        {
            auto rc = static_cast<Result>( JetSeek( sessionId_, tableId_, static_cast<JET_GRBIT>( flags ) ) );
            return rc;
        }

        bool GetBookmark( std::vector<unsigned char>& result ) const
        {
            unsigned char buffer[2048];
            unsigned long actualSize = 0;
            result.clear( );
            auto rc = static_cast<Result>( JetGetBookmark( sessionId_, tableId_, buffer, sizeof( buffer ), &actualSize ) );
            if ( rc == Result::ErrorBufferTooSmall )
            {
                result.resize( actualSize );
                rc = static_cast<Result>( JetGetBookmark( sessionId_, tableId_, result.data( ), actualSize, &actualSize ) );
                return RequireSuccess( rc );
            }
            else
            {
                if ( rc == Result::ErrorNoCurrentRecord )
                {
                    return false;
                }
                RequireSuccess( rc );
                result.resize( actualSize );
                memcpy( result.data( ), buffer, actualSize );
                return true;
            }
        }

        bool GotoBookmark( const std::vector<unsigned char>& bookmark ) const
        {
            if ( bookmark.size( ) )
            {
                auto rc = static_cast<Result>( JetGotoBookmark( sessionId_, tableId_, const_cast<unsigned char*>( bookmark.data( ) ), static_cast<unsigned long>( bookmark.size( ) ) ) );
                if ( rc == Result::ErrorNoCurrentRecord || rc == Result::ErrorRecordDeleted )
                {
                    return false;
                }
                return RequireSuccess( rc );
            }
            else
            {
                return false;
            }
        }

        bool Move( long offset ) const
        {
            auto rc = static_cast<Result>( JetMove( sessionId_, tableId_, offset, 0 ) );
            if ( rc != Result::Success && rc != Result::ErrorNoCurrentRecord )
            {
                HCC_THROW( Exception, rc );
            }
            return rc == Result::Success;
        }

        bool MoveFirst( ) const
        {
            return Move( JET_MoveFirst );
        }

        bool MoveNext( ) const
        {
            return Move( JET_MoveNext );
        }

        bool MovePrevious( ) const
        {
            return Move( JET_MovePrevious );
        }

        bool MoveLast( ) const
        {
            return Move( JET_MoveLast );
        }

        unsigned long RetrieveColumnSize( JET_COLUMNID columnId, int itagSequence, RetrieveFlags retrieveFlags = RetrieveFlags::None ) const
        {
            JET_RETINFO retinfo = { sizeof( JET_RETINFO ), 0, static_cast<ULONG>( itagSequence ), 0 };
            unsigned long dataSize = 0;
            Byte buffer[ 1 ] = {};
            auto rc = static_cast<Result>( JetRetrieveColumn( sessionId_, tableId_, columnId, buffer, 1, &dataSize, static_cast<int>(retrieveFlags), &retinfo ) );
            if ( rc == Result::WarningColumnNull )
            {
                return 0;
            }
            else if ( rc != Result::Success && rc != Result::WarningBufferTruncated )
            {
                HCC_THROW( Exception, rc );
            }
            return dataSize;
        }

        unsigned long RetrieveColumnSize( JET_COLUMNID columnId, RetrieveFlags retrieveFlags = RetrieveFlags::None ) const
        {
            unsigned long dataSize = 0;
            auto rc = static_cast< Result >( JetRetrieveColumn( sessionId_, tableId_, columnId, nullptr, 0, &dataSize, static_cast< int >( retrieveFlags ), nullptr ) );
            if ( rc == Result::WarningColumnNull )
            {
                return 0;
            }
            else if ( rc != Result::Success && rc != Result::WarningBufferTruncated )
            {
                HCC_THROW( Exception, rc );
            }
            return dataSize;
        }


        bool IsDBNull(JET_COLUMNID columnId, int itagSequence = 0, RetrieveFlags retrieveFlags = RetrieveFlags::None) const
        {
            JET_RETINFO retinfo = { sizeof(JET_RETINFO), 0, static_cast<ULONG>(itagSequence), 0 };
            unsigned long dataSize = 0;
            Byte buffer[ 1 ] = {};
            auto rc = static_cast<Result>(JetRetrieveColumn(sessionId_, tableId_, columnId, buffer, 1, &dataSize, static_cast<int>(retrieveFlags), &retinfo));
            if (rc == Result::WarningColumnNull)
            {
                return true;
            }
            else if (rc != Result::Success && rc != Result::WarningBufferTruncated)
            {
                HCC_THROW(Exception, rc);
            }
            return false;
        }


        Ese::Result RetrieveColumn( JET_COLUMNID columnId, void* dataBuffer, unsigned long dataBufferSize, unsigned long* actualDataSize, RetrieveFlags retrieveFlags, JET_RETINFO* pretinfo ) const
        { 
            auto rc = static_cast<Result>( JetRetrieveColumn( sessionId_, tableId_, columnId, dataBuffer, dataBufferSize, actualDataSize, static_cast<int>(retrieveFlags), pretinfo ) );
            return rc;
        }

        Ese::Result SetColumn( JET_COLUMNID columnId, const void* dataBuffer, unsigned long dataBufferSize, SetFlags flags, JET_SETINFO* psetinfo ) const
        {
            auto rc = static_cast<Result>( JetSetColumn( sessionId_, tableId_, columnId, dataBuffer, dataBufferSize, static_cast<int>(flags), psetinfo ) );
            return rc;
        }

        Ese::Result RetrieveColumns( JET_RETRIEVECOLUMN* retrieveColumns, unsigned long columnCount ) const
        {
            auto rc = static_cast<Result>( JetRetrieveColumns( sessionId_, tableId_, retrieveColumns, columnCount ) );
            return rc;
        }

        Ese::Result SetColumns( JET_SETCOLUMN* setColumns, unsigned long count ) const
        {
            auto rc = static_cast<Result>( JetSetColumns( sessionId_, tableId_, setColumns, count ) );
            return rc;
        }

        Ese::Result GetTableColumnInfo( const wchar_t* columnName, void* pvResult, unsigned long cbMax = sizeof( JET_COLUMNDEF ), ColumnInfoFlags columnInfoFlags = ColumnInfoFlags::Default ) const
        {
            auto rc = static_cast<Result>( JetGetTableColumnInfoW( sessionId_, tableId_, columnName, pvResult, cbMax, static_cast<unsigned long>(columnInfoFlags) ) );
            return rc;
        }

        Ese::Result GetTableColumnInfo( const char* columnName, void* pvResult, unsigned long cbMax = sizeof( JET_COLUMNDEF ), ColumnInfoFlags columnInfoFlags = ColumnInfoFlags::Default ) const
        {
            auto rc = static_cast<Result>( JetGetTableColumnInfoA( sessionId_, tableId_, columnName, pvResult, cbMax, static_cast<unsigned long>( columnInfoFlags ) ) );
            return rc;
        }

        Ese::Result PrepareUpdate( PrepareUpdateOptions option ) const
        {
            auto rc = static_cast<Result>( JetPrepareUpdate( sessionId_, tableId_, static_cast<unsigned long>( option ) ) );
            return rc;
        }

        /// <summary>
        /// Cancels the current update for this cursor
        /// </summary>
        void Cancel( ) const
        {
            auto rc = PrepareUpdate( PrepareUpdateOptions::Cancel );
            RequireSuccess( rc );
        }

        /// <summary>
        /// Prepares the cursor for an insert of a copy of 
        /// the existing record. There must be a current record if this option 
        /// is used. The initial state of the new record is copied from the 
        /// current record. Long values that are stored off-record are 
        /// virtually copied.
        /// </summary>
        void Copy( ) const
        {
            auto rc = PrepareUpdate( PrepareUpdateOptions::Copy );
            RequireSuccess( rc );
        }

        /// <summary>
        /// Prepares the cursor for an insert of a new record. 
        /// All the data is initialized to the default state for the record. If 
        /// the table has an auto-increment column, then a new value is assigned 
        /// to this record regardless of whether the update ultimately succeeds, 
        /// fails or is cancelled.
        /// </summary>
        void Insert( ) const
        {
            auto rc = PrepareUpdate( PrepareUpdateOptions::Insert );
            RequireSuccess( rc );
        }

        /// <summary>
        /// Prepares the cursor for a replace of the current 
        /// record. If the table has a version column, then the version column 
        /// is set to the next value in its sequence. If this update does not 
        /// complete, then the version value in the record will be unaffected. 
        /// An update lock is taken on the record to prevent other sessions 
        /// from updating this record before this session completes.
        /// </summary>
        void Replace( ) const
        {
            auto rc = PrepareUpdate( PrepareUpdateOptions::Replace );
            RequireSuccess( rc );
        }

        /// <summary>
        /// Prepares the cursor for an insert of the same record, 
        /// and a delete or the original record. It is used in cases 
        /// in which the primary key has changed.
        /// </summary>
        void InsertCopyDeleteOriginal( ) const
        {
            auto rc = PrepareUpdate( PrepareUpdateOptions::InsertCopyDeleteOriginal );
            RequireSuccess( rc );
        }

        /// <summary>
        /// Performs an update operation including inserting a new 
        /// row into a table or updating an existing row
        /// </summary>
        void Update( ) const
        {
            auto rc = static_cast<Result>( JetUpdate( sessionId_, tableId_, nullptr, 0, nullptr ) );
            RequireSuccess( rc );
        }

        /// <summary>
        /// Deletes the current record in a table
        /// </summary>
        void Delete( ) const
        {
            auto rc = static_cast<Result>( JetDelete( sessionId_, tableId_ ) );
            RequireSuccess( rc );
        }

        void SetSequential( SequentialFlags flags = SequentialFlags::PrereadForward ) const
        {
            auto rc = static_cast<Result>( JetSetTableSequential( sessionId_, tableId_, static_cast<JET_GRBIT>( flags ) ) );
            RequireSuccess( rc );
        }





        template<CharType T>
        JET_COLUMNID GetColumnId( const T* columnName )
        {
            JET_COLUMNDEF columnDef = { sizeof( JET_COLUMNDEF ), 0, };
            GetTableColumnInfo( columnName, &columnDef );
            return columnDef.columnid;
        }
        template<StringType T>
        JET_COLUMNID GetColumnId( const T& columnName )
        {
            return GetColumnId( columnName.c_str() );
        }

        JET_COLUMNID AddColumn( const wchar_t* columnName, const JET_COLUMNDEF& columnDef, const void* defaultValueBuffer = nullptr, unsigned long defaultValueBufferSize = 0 ) const
        {
            JET_COLUMNID result = 0;
            auto rc = static_cast<Result>( JetAddColumnW( sessionId_, tableId_, columnName, &columnDef, defaultValueBuffer, defaultValueBufferSize, &result ) );
            RequireSuccess( rc );
            return result;
        }
        JET_COLUMNID AddColumn( const char* columnName, const JET_COLUMNDEF& columnDef, const void* defaultValueBuffer = nullptr, unsigned long defaultValueBufferSize = 0 ) const
        {
            JET_COLUMNID result = 0;
            auto rc = static_cast<Result>( JetAddColumnA( sessionId_, tableId_, columnName, &columnDef, defaultValueBuffer, defaultValueBufferSize, &result ) );
            RequireSuccess( rc );
            return result;
        }

        template<StringType T>
        JET_COLUMNID AddColumn( const T& columnName, const JET_COLUMNDEF& columnDef, const void* defaultValueBuffer = nullptr, unsigned long defaultValueBufferSize = 0 ) const
        {
            return AddColumn( columnName.c_str(), columnDef, defaultValueBuffer, defaultValueBufferSize );
        }

        template<StringType T>
        JET_COLUMNID AddBoolean( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Boolean, flags );
            return AddColumn( columnName, columnDef );
        }
        template<CharType T>
        JET_COLUMNID AddBoolean( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Boolean, flags );
            return AddColumn( columnName, columnDef );
        }

        template<StringType T>
        JET_COLUMNID AddSByte( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Byte, flags );
            return AddColumn( columnName, columnDef );
        }
        template<CharType T>
        JET_COLUMNID AddSByte( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Byte, flags );
            return AddColumn( columnName, columnDef );
        }
        template<StringType T>
        JET_COLUMNID AddByte( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Byte, flags );
            return AddColumn( columnName, columnDef );
        }
        template<CharType T>
        JET_COLUMNID AddByte( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Byte, flags );
            return AddColumn( columnName, columnDef );
        }
        template<StringType T>
        JET_COLUMNID AddInt16( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Short, flags );
            return AddColumn( columnName, columnDef );
        }
        template<CharType T>
        JET_COLUMNID AddInt16( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Short, flags );
            return AddColumn( columnName, columnDef );
        }
        template<StringType T>
        JET_COLUMNID AddUInt16( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::UnsignedShort, flags );
            return AddColumn( columnName, columnDef );
        }
        template<CharType T>
        JET_COLUMNID AddUInt16( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::UnsignedShort, flags );
            return AddColumn( columnName, columnDef );
        }
        template<StringType T>
        JET_COLUMNID AddInt32( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Long, flags );
            return AddColumn( columnName, columnDef );
        }
        template<CharType T>
        JET_COLUMNID AddInt32( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Long, flags );
            return AddColumn( columnName, columnDef );
        }
        template<StringType T>
        JET_COLUMNID AddUInt32( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::UnsignedLong, flags );
            return AddColumn( columnName, columnDef );
        }
        template<CharType T>
        JET_COLUMNID AddUInt32( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::UnsignedLong, flags );
            return AddColumn( columnName, columnDef );
        }
        template<StringType T>
        JET_COLUMNID AddInt64( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::LongLong, flags );
            return AddColumn( columnName, columnDef );
        }
        template<CharType T>
        JET_COLUMNID AddInt64( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::LongLong, flags );
            return AddColumn( columnName, columnDef );
        }
        template<StringType T>
        JET_COLUMNID AddUInt64( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::UnsignedLongLong, flags );
            return AddColumn( columnName, columnDef );
        }
        template<CharType T>
        JET_COLUMNID AddUInt64( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::UnsignedLongLong, flags );
            return AddColumn( columnName, columnDef );
        }
        template<StringType T>
        JET_COLUMNID AddSingle( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Single, flags );
            return AddColumn( columnName, columnDef );
        }
        template<CharType T>
        JET_COLUMNID AddSingle( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Single, flags );
            return AddColumn( columnName, columnDef );
        }
        template<StringType T>
        JET_COLUMNID AddDouble( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Double, flags );
            return AddColumn( columnName, columnDef );
        }
        template<CharType T>
        JET_COLUMNID AddDouble( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Double, flags );
            return AddColumn( columnName, columnDef );
        }

        template<StringType T>
        JET_COLUMNID AddCurrency( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Currency, flags );
            return AddColumn( columnName, columnDef );
        }
        template<CharType T>
        JET_COLUMNID AddCurrency( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Currency, flags );
            return AddColumn( columnName, columnDef );
        }

        template<StringType T>
        JET_COLUMNID AddTimeSpan( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::LongLong, flags );
            return AddColumn( columnName, columnDef );
        }
        template<CharType T>
        JET_COLUMNID AddTimeSpan( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::LongLong, flags );
            return AddColumn( columnName, columnDef );
        }
        template<StringType T>
        JET_COLUMNID AddDateTime( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::DateTime, flags );
            return AddColumn( columnName, columnDef );
        }
        template<CharType T>
        JET_COLUMNID AddDateTime( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::DateTime, flags );
            return AddColumn( columnName, columnDef );
        }
        template<StringType T>
        JET_COLUMNID AddGuid( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Guid, sizeof(GUID) ,flags );
            return AddColumn( columnName, columnDef );
        }
        template<CharType T>
        JET_COLUMNID AddGuid( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Guid, flags );
            return AddColumn( columnName, columnDef );
        }
        template<CharType T>
        JET_COLUMNID AddText( const T* columnName, unsigned long maxSize = 127, short codePage = 1200, ColumnFlags flags = ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Text, maxSize, flags );
            if ( maxSize > 127 )
            {
                columnDef.coltyp = static_cast<JET_COLTYP>( ColumnType::LongText );
            }
            return AddColumn( columnName, columnDef );
        }
        template<StringType T>
        JET_COLUMNID AddText( const T& columnName, unsigned long maxSize = 127, short codePage = 1200, ColumnFlags flags = ColumnFlags::NotNULL ) const
        {
            return AddText( columnName.c_str( ), maxSize, codePage, flags );
        }
        template<CharType T>
        JET_COLUMNID AddBinary( const T* columnName, unsigned long maxSize = 255, ColumnFlags flags = ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Binary, maxSize, flags );
            if ( maxSize > 255 )
            {
                columnDef.coltyp = static_cast<JET_COLTYP>( ColumnType::LongBinary );
            }
            return AddColumn( columnName, columnDef );
        }
        template<StringType T>
        JET_COLUMNID AddBinary( const AnsiString& columnName, unsigned long maxSize = 255, ColumnFlags flags = ColumnFlags::NotNULL ) const
        {
            return AddBinary( columnName.c_str( ), maxSize, flags );
        }

        Columns GetColumns( ) const;

        void SetNull( JET_COLUMNID columnid ) const
        {
            auto rc = SetColumn( columnid, 0, 0, SetFlags::None, nullptr );
            RequireSuccess( rc );
        }

    private:
        static bool CheckReadResult( Result rc )
        {
            if ( rc == Result::Success )
            {
                return true;
            }
            else if ( rc == Result::WarningColumnNull )
            {
                return false;
            }
            else
            {
                HCC_THROW( Exception, rc );
            }
        }
        
    public:
        template<DirectType T>
        bool Read( JET_COLUMNID columnId, T& value, RetrieveFlags retrieveFlags = RetrieveFlags::None ) const
        {
            constexpr unsigned long DataSize = sizeof( std::decay_t<T> );
            unsigned long actualDataSize;
            auto rc = RetrieveColumn( columnId, &value, DataSize, &actualDataSize, retrieveFlags, nullptr );
            return CheckReadResult( rc );
        }


        bool Read( JET_COLUMNID columnId, bool& value, RetrieveFlags retrieveFlags = RetrieveFlags::None ) const
        {
            constexpr unsigned long DataSize = 1;
            Byte data;
            unsigned long actualDataSize;
            auto rc = RetrieveColumn( columnId, &data, DataSize, &actualDataSize, retrieveFlags, nullptr );
            if ( rc == Result::Success )
            {
                value = data != 0;
                return true;
            }
            return CheckReadResult( rc );
        }

        bool Read( JET_COLUMNID columnId, DateTime& value, RetrieveFlags retrieveFlags = RetrieveFlags::None ) const
        {
            constexpr unsigned long DataSize = sizeof(double);
            unsigned long actualDataSize;
            double data;
            auto rc = RetrieveColumn( columnId, &data, DataSize, &actualDataSize, retrieveFlags, nullptr );
            if ( rc == Result::Success )
            {
                value = DateTime::FromOADate(data);
                return true;
            }
            return CheckReadResult( rc );
        }


        template<StringType T>
        bool Read( JET_COLUMNID columnId, T& value, RetrieveFlags retrieveFlags = RetrieveFlags::None ) const
        {
            using CharType = typename T::value_type;
            constexpr unsigned long BufferSize = 256;
            CharType buffer[BufferSize];
            unsigned long actualDataSize;
            auto rc = RetrieveColumn( columnId, buffer, BufferSize * sizeof( CharType ), &actualDataSize, retrieveFlags, nullptr );
            if ( rc == Result::WarningColumnNull )
            {
                return false;
            }

            if ( rc == Result::Success )
            {
                value.resize( actualDataSize / sizeof( CharType ) );
                memcpy( value.data( ), buffer, actualDataSize );
                return true;
            }
            else if ( rc == Result::WarningBufferTruncated )
            {
                unsigned long newDataSize;
                value.resize( actualDataSize / sizeof( CharType ) );
                rc = RetrieveColumn( columnId, value.data(), actualDataSize, &newDataSize, retrieveFlags, nullptr );
                if ( rc == Result::WarningBufferTruncated )
                {
                    throw InvalidOperationException( "Buffer size changed" );
                }
                return RequireSuccess( rc );
            }
            RequireSuccess( rc );
            return false;
        }
        /*
        template<BinaryVectorType T>
        bool Read( JET_COLUMNID columnId, T& value, RetrieveFlags retrieveFlags = RetrieveFlags::None ) const
        {
            unsigned long dataSize = RetrieveColumnSize( columnId, retrieveFlags );
            if ( dataSize )
            {
                value.resize( dataSize );
                unsigned long actualDataSize;
                auto rc = RetrieveColumn( columnId, value.data( ), dataSize, &actualDataSize, retrieveFlags, nullptr );
                return RequireSuccess( rc );
            }
            else
            {
                return false;
            }
        }
        */

        template<BinaryVectorType T>
        bool Read( JET_COLUMNID columnId, T& value, RetrieveFlags retrieveFlags = RetrieveFlags::None ) const
        {
            using ByteType = typename T::value_type;
            constexpr unsigned long BufferSize = 32*1024;
            ByteType buffer[ BufferSize ];
            unsigned long actualDataSize;
            auto rc = RetrieveColumn( columnId, buffer, BufferSize, &actualDataSize, retrieveFlags, nullptr );
            if ( rc == Result::WarningColumnNull )
            {
                return false;
            }

            if ( rc == Result::Success )
            {
                value.resize( actualDataSize );
                memcpy( value.data( ), buffer, actualDataSize );
                return true;
            }
            else if ( rc == Result::WarningBufferTruncated )
            {
                unsigned long newDataSize;
                value.resize( actualDataSize );
                rc = RetrieveColumn( columnId, value.data( ), actualDataSize, &newDataSize, retrieveFlags, nullptr );
                if ( rc == Result::WarningBufferTruncated )
                {
                    throw InvalidOperationException( "Buffer size changed" );
                }
                return RequireSuccess( rc );
            }
            RequireSuccess( rc );
            return false;
        }

        bool Read( JET_COLUMNID columnId, IO::MemoryStream& value, RetrieveFlags retrieveFlags = RetrieveFlags::None ) const
        {
            unsigned long dataSize = RetrieveColumnSize( columnId, retrieveFlags );
            if ( dataSize )
            {
                value.SetCapacity( dataSize );
                value.SetPosition( 0 );
                unsigned long actualDataSize;
                auto rc = RetrieveColumn( columnId, value.Buffer( ), dataSize, &actualDataSize, retrieveFlags, nullptr );
                return RequireSuccess( rc );
            }
            else
            {
                return false;
            }
        }


        template<typename T>
        std::optional<T> As( JET_COLUMNID columnId, RetrieveFlags flags = RetrieveFlags::None ) const
        {
            T data;
            if ( Read( columnId, data, flags ) )
            {
                return std::optional<T>( std::move( data ) );
            }
            else
            {
                return std::optional<T>( );
            }
        }

        template<DirectType T>
        void SetColumn( JET_COLUMNID columnid, const T& value, SetFlags flags = SetFlags::None ) const
        {
            auto rc = SetColumn( columnid, &value, sizeof( std::decay_t<T> ), flags, nullptr );
            RequireSuccess( rc );
        }
        template<typename T>
            requires std::is_same_v<DateTime, T>
        void SetColumn( JET_COLUMNID columnid, const T& value, SetFlags flags = SetFlags::None ) const
        {
            auto data = value.ToOADate( );
            auto rc = SetColumn( columnid, &data, sizeof( double ), flags, nullptr );
            RequireSuccess( rc );
        }

        template<typename T>
            requires std::is_same_v<bool, T>
        void SetColumn( JET_COLUMNID columnid, T value, SetFlags flags = SetFlags::None ) const
        {
            Byte data = value ? 1 : 0;
            auto rc = SetColumn( columnid, (const void*)&data, 1UL, flags, static_cast<JET_SETINFO*>(nullptr) );
            RequireSuccess( rc );
        }

        
        template<StringType T>
        void SetColumn( JET_COLUMNID columnId, const T& text, SetFlags flags = SetFlags::None ) const
        {
            using CharT = typename T::value_type;
            DWORD length = static_cast<unsigned long>( text.length( ) * sizeof( CharT ) );
            if ( !length )
            {
                flags |= SetFlags::ZeroLength;
            }
            auto rc = SetColumn( columnId, text.c_str( ), length, flags, nullptr );
            RequireSuccess( rc );
        }
        template<BinaryVectorType T>
        void SetColumn( JET_COLUMNID columnId, const T& value, SetFlags flags = SetFlags::None ) const
        {
            DWORD length = static_cast<unsigned long>( value.size( ) );
            if ( !length )
            {
                flags |= SetFlags::ZeroLength;
            }
            auto rc = SetColumn( columnId, value.data( ), length, flags, nullptr );
            RequireSuccess( rc );
        }

        Ese::Result ReadBinary( JET_COLUMNID columnId, void* data, unsigned long dataSize, unsigned long& actualDataSize, RetrieveFlags retrieveFlags = RetrieveFlags::None, JET_RETINFO* retinfo = nullptr ) const
        {
            auto rc = RetrieveColumn( columnId, data, dataSize, &actualDataSize, retrieveFlags, nullptr );
            return rc;
        }
        void WriteBinary( JET_COLUMNID columnid, void* data, unsigned long dataSize, SetFlags flags = SetFlags::None ) const
        {
            auto rc = SetColumn( columnid, data, dataSize, flags, nullptr );
            RequireSuccess( rc );
        }

        void CreateIndex( const wchar_t* indexName, IndexFlags indexFlags, const wchar_t* keyString, unsigned long	keyStringLength, unsigned long density = 95 ) const
        {
            auto rc = static_cast<Result>( JetCreateIndexW( sessionId_, tableId_, indexName, static_cast<JET_GRBIT>( indexFlags ), keyString, keyStringLength, density ) );
            RequireSuccess( rc );
        }
        void CreateIndex( const char* indexName, IndexFlags indexFlags, const char* keyString, unsigned long keyStringLength, unsigned long density = 95 ) const
        {
            auto rc = static_cast<Result>( JetCreateIndexA( sessionId_, tableId_, indexName, static_cast<JET_GRBIT>( indexFlags ), keyString, keyStringLength, density ) );
            RequireSuccess( rc );
        }
        template<StringType T>
        void CreateIndex( const T& indexName, IndexFlags indexFlags, const typename T::value_type* keyString, unsigned long keyStringLength, unsigned long density = 95 ) const
        {
            using CharType = typename T::value_type;
            CreateIndex( indexName.c_str( ), indexFlags, keyString, (keyStringLength+1)*sizeof( CharType ), density );
        }



        void Close( )
        {
            if ( tableId_ != JET_tableidNil )
            {
                auto rc = static_cast<Result>( JetCloseTable( this->sessionId_, tableId_ ) );
                RequireSuccess( rc );
                tableId_ = JET_tableidNil;
            }
        }
    };


    class SystemTable : public Table
    {
        typedef Table Base;
    public:
        SystemTable( JET_SESID sessionId, JET_TABLEID tableId )
            : Base( sessionId, tableId )
        {
        }
    };

    class Tables : public SystemTable
    {
        typedef SystemTable Base;
        JET_OBJECTLIST objectList_;
    public:

        Tables( JET_SESID sessionId, const JET_OBJECTLIST& objectList )
            : Base( sessionId, objectList.tableid ), objectList_( objectList )
        {
        }

        WideString ContainerName() const
        {
            WideString result;
            if ( Read( objectList_.columnidcontainername, result ) )
            {
                return std::move( result );
            }
            return {};
        }

        WideString ObjectName() const
        {
            WideString result;
            if ( Read( objectList_.columnidobjectname, result ) )
            {
                return std::move( result );
            }
            return {};
        }

        TableOptions Options() const
        {
            Int32 value;
            if (Read( objectList_.columnidgrbit, value ))
            {
                return static_cast<TableOptions>( value );
            }
            return TableOptions::None;
        }

        ObjectFlags Flags() const
        {
            Int32 value;
            if ( Read( objectList_.columnidflags, value ) )
            {
                return static_cast<ObjectFlags>( value );
            }
            return ObjectFlags::None;
        }

        unsigned long NumberOfRecords()
        {
            unsigned long value;
            if ( Read( objectList_.columnidcRecord, value ) )
            {
                return value;
            }
            return 0;
        }

        unsigned long NumberOfPages()
        {
            unsigned long value;
            if ( Read( objectList_.columnidcPage, value ) )
            {
                return value;
            }
            return 0;
        }
    };

    class Columns : public SystemTable
    {
        typedef SystemTable Base;
        JET_COLUMNLIST columnList_;
    public:
        Columns( JET_SESID sessionId, const JET_COLUMNLIST& columnList )
            : Base( sessionId, columnList.tableid ), columnList_( columnList )
        {
        }

        unsigned long Count() const
        {
            return columnList_.cRecord;
        }
        int PresentationOrder() const
        {
            int value;
            if ( Read( columnList_.columnidPresentationOrder, value ) )
            {
                return value;
            }
            return -1;
        }
        WideString ColumnName() const
        {
            WideString result;
            if ( Read( columnList_.columnidcolumnname, result ) )
            {
                return std::move( result );
            }
            return {};
        }
        JET_COLUMNID ColumnId() const
        {
            JET_COLUMNID value;
            if ( Read( columnList_.columnidcolumnid, value ) )
            {
                return value;
            }
            return 0;
        }
        ColumnType Type() const
        {
            Int32 value;
            if ( Read( columnList_.columnidcoltyp, value ) )
            {
                return static_cast<ColumnType>(value);
            }
            return ColumnType::None;
        }
        short Country() const
        {
            short value;
            if ( Read( columnList_.columnidCountry, value ) )
            {
                return value;
            }
            return 0;
        }
        short LangId() const
        {
            short value;
            if ( Read( columnList_.columnidLangid, value ) )
            {
                return value;
            }
            return 0;
        }
        short CodePage() const
        {
            short value;
            if ( Read( columnList_.columnidCp, value ) )
            {
                return value;
            }
            return 0;
        }
        short Collate() const
        {
            short value;
            if ( Read( columnList_.columnidCollate, value ) )
            {
                return value;
            }
            return 0;
        }
        int Size() const
        {
            int value;
            if ( Read( columnList_.columnidcbMax, value ) )
            {
                return value;
            }
            return 0;
        }

        ColumnFlags Flags() const
        {
            int value;
            if ( Read( columnList_.columnidgrbit, value ) )
            {
                return static_cast<ColumnFlags>(value);
            }
            return ColumnFlags::None;
        }
        std::vector<Byte> Default() const
        {
            std::vector<Byte> result;
            if ( Read( columnList_.columnidDefault, result ) )
            {
                return std::move( result );
            }
            return result;
        }
        WideString BaseTableName() const
        {
            WideString result;
            if ( Read( columnList_.columnidBaseTableName, result ) )
            {
                return std::move( result );
            }
            return {};
        }
        WideString BaseColumnName() const
        {
            WideString result;
            if ( Read( columnList_.columnidBaseColumnName, result ) )
            {
                return std::move( result );
            }
            return {};
        }
        WideString DefinitionName() const
        {
            WideString result;
            if ( Read( columnList_.columnidDefinitionName, result ) )
            {
                return std::move( result );
            }
            return {};
        }
    };

    inline Columns Table::GetColumns( ) const
    {
        JET_COLUMNLIST columnList = { sizeof( JET_COLUMNLIST ), 0, };
        auto rc = GetTableColumnInfo( ( char* )nullptr, &columnList, sizeof( JET_COLUMNLIST ), ColumnInfoFlags::List );
        RequireSuccess( rc );
        Columns result( sessionId_, columnList );
        return result;
    }
    



    enum class OpenTableFlags : int
    {
        None = 0,
        DenyRead = JET_bitTableDenyRead,
        DenyWrite = JET_bitTableDenyWrite,
        NoCache = JET_bitTableNoCache,
        PermitDDL = JET_bitTablePermitDDL,
        Preread = JET_bitTablePreread,
        ReadOnly = JET_bitTableReadOnly,
        OpportuneRead = JET_bitTableOpportuneRead,
        Sequential = JET_bitTableSequential,
        
        Updatable = JET_bitTableUpdatable
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( OpenTableFlags, int );

    enum class TransactionFlags : int
    {
        None = 0,
        CommitLazyFlush = JET_bitCommitLazyFlush,
        WaitAll = JET_bitWaitAllLevel0Commit,
        WaitLast = JET_bitWaitLastLevel0Commit
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( TransactionFlags, int );


    struct ObjectInfo : public JET_OBJECTINFO
    {
        using Base = JET_OBJECTINFO;

        ObjectInfo()
            : Base{static_cast<unsigned long>( sizeof( JET_OBJECTINFO ) ),}
        { }

    };


    class Database
    {
        JET_SESID sessionId_;
        JET_DBID databaseId_;
    public:
        constexpr Database( ) noexcept
            : sessionId_( JET_sesidNil ), databaseId_( JET_dbidNil )
        {
        }

        Database( JET_SESID sessionId, JET_DBID databaseId )
            : sessionId_( sessionId ), databaseId_( databaseId )
        {
            if ( sessionId_ == JET_sesidNil )
            {
                throw ArgumentException( "Invalid session handle" );
            }
            if ( databaseId == JET_dbidNil )
            {
                throw ArgumentException( "Invalid database handle" );
            }
        }

        Database( const Database& other ) = delete;
        Database( Database&& other ) noexcept
            : sessionId_( other.sessionId_ ), databaseId_( other.databaseId_ )
        {
            other.sessionId_ = JET_sesidNil;
            other.databaseId_ = JET_dbidNil;
        }

        ~Database( )
        {
            if ( databaseId_ != JET_dbidNil )
            {
                JetCloseDatabase( sessionId_, databaseId_, 0 );
            }
        }

        Database& operator = ( const Database& other ) = delete;
        Database& operator = ( Database&& other ) noexcept
        {
            if ( &other != this )
            {
                if ( databaseId_ != JET_dbidNil )
                {
                    JetCloseDatabase( sessionId_, databaseId_, 0 );
                }
                sessionId_ = other.sessionId_;
                databaseId_ = other.databaseId_;
                other.sessionId_ = JET_sesidNil;
                other.databaseId_ = JET_dbidNil;
            }
            return *this;
        }


        JET_SESID SessionHandle() const
        {
            return sessionId_;
        }


        JET_DBID Handle() const
        {
            return databaseId_;
        }

        void OnDatabaseCreated( )
        {
        }
        void OnDatabaseOpened( )
        {
        }

        constexpr bool IsValid( ) const noexcept
        {
            return sessionId_ != JET_sesidNil && databaseId_ != JET_dbidNil;
        }

        constexpr explicit operator bool( ) const noexcept
        {
            return IsValid( );
        }


        void Close( )
        {
            if ( databaseId_ != JET_dbidNil )
            {
                auto rc = static_cast<Ese::Result>( JetCloseDatabase( sessionId_, databaseId_, 0 ) );
                RequireSuccess( rc );
                sessionId_ = JET_sesidNil;
                databaseId_ = JET_dbidNil;
            }
        }

        Result OpenTable( const wchar_t* tablename, const void* parameters, unsigned long parametersSize, OpenTableFlags flags, JET_TABLEID* tableId ) const
        {
            auto rc = static_cast<Result>( JetOpenTableW( sessionId_, databaseId_, tablename, parameters, parametersSize, static_cast<JET_GRBIT>(flags), tableId ) );
            return rc;
        }
        Result OpenTable( const char* tablename, const void* parameters, unsigned long parametersSize, OpenTableFlags flags, JET_TABLEID* tableId ) const
        {
            auto rc = static_cast<Result>( JetOpenTableA( sessionId_, databaseId_, tablename, parameters, parametersSize, static_cast<JET_GRBIT>( flags ), tableId ) );
            return rc;
        }

        template<TableType T = Table, CharType C>
        [[nodiscard]] T OpenTable( const C* tablename, 
                                    OpenTableFlags flags = OpenTableFlags::Updatable, 
                                    bool noexception = false ) const
        {
            JET_TABLEID tableId = 0;
            auto rc = OpenTable( tablename, nullptr, 0, flags, &tableId );
            if ( rc != Result::Success )
            {
                if ( rc == Result::ErrorObjectNotFound && noexception )
                {
                    return T( );
                }
                HCC_THROW( Exception, rc );
            }
            T result( sessionId_, tableId );
            result.OnTableOpened( );
            return result;
        }

        template<TableType T = Table, StringType S>
        [[nodiscard]] T OpenTable( const S& tablename, OpenTableFlags flags = OpenTableFlags::Updatable, bool noexception = false ) const
        {
            return OpenTable( tablename.c_str(), flags, noexception );
        }


        Result CreateTable( const wchar_t* tablename, unsigned long initialNumberOfPages, unsigned long density, JET_TABLEID* tableId ) const
        {
            auto rc = static_cast<Result>( JetCreateTableW( sessionId_, databaseId_, tablename, initialNumberOfPages, density, tableId ) );
            return rc;
        }
        Result CreateTable( const char* tablename, unsigned long initialNumberOfPages, unsigned long density, JET_TABLEID* tableId ) const
        {
            auto rc = static_cast<Result>( JetCreateTableA( sessionId_, databaseId_, tablename, initialNumberOfPages, density, tableId ) );
            return rc;
        }

        /// <summary>
        /// Creates an empty table in the database
        /// </summary>
        /// <typeparam name="T">Table, or a type move assignable type derived from Table</typeparam>
        /// <param name="tablename">The name of the table to create</param>
        /// <param name="initialNumberOfPages">The initial number of database pages to allocate for the table. Specifying a number larger than one can reduce fragmentation if many rows are inserted into this table</param>
        /// <param name="density">The table density, in percentage points. The number must be either 0 or in the range of 20 through 100. Passing 0 means that the default value should be used. The default is 80</param>
        /// <returns>A Table instance, or an instance of a type derived from Table, for the newly created database table.</returns>
        template<TableType T = Table, CharType C>
        [[nodiscard]] T CreateTable(const C* tablename, 
                                    unsigned long initialNumberOfPages = 1, 
                                    unsigned long density = 0) const
        {
            JET_TABLEID tableId = 0;
            auto rc = CreateTable( tablename, initialNumberOfPages, density, &tableId );
            RequireSuccess( rc );
            T result( sessionId_, tableId );
            result.OnTableCreated( );
            return result;
        }

        /// <summary>
        /// Creates an empty table in the database
        /// </summary>
        /// <typeparam name="T">Table, or a type move assignable type derived from Table</typeparam>
        /// <param name="tablename">The name of the table to create</param>
        /// <param name="initialNumberOfPages">The initial number of database pages to allocate for the table. Specifying a number larger than one can reduce fragmentation if many rows are inserted into this table</param>
        /// <param name="density">The table density, in percentage points. The number must be either 0 or in the range of 20 through 100. Passing 0 means that the default value should be used. The default is 80</param>
        /// <returns>A Table instance, or an instance of a type derived from Table, for the newly created database table.</returns>
        template<TableType T = Table, StringType S>
        [[nodiscard]] T CreateTable( const S& tablename, unsigned long initialNumberOfPages = 1, unsigned long density = 0 ) const
        {
            return CreateTable( tablename.c_str( ), initialNumberOfPages, density );
        }


        [[nodiscard]] Tables GetTables() const
        {
            JET_OBJECTLIST objectList = { sizeof(JET_OBJECTLIST), 0, };
            auto rc = static_cast<Ese::Result>( JetGetObjectInfoW( sessionId_, databaseId_, JET_objtypTable, nullptr, nullptr, &objectList, sizeof( JET_OBJECTLIST ), JET_ObjInfoListNoStats ));
            RequireSuccess( rc );
            Tables result( sessionId_, objectList);
            return result;
        }

        void DeleteTable( const wchar_t* tableName )
        {
            auto rc = static_cast<Ese::Result>( JetDeleteTableW( sessionId_, databaseId_, tableName ));
            RequireSuccess( rc );
        }
        void DeleteTable( const char* tableName )
        {
            auto rc = static_cast<Ese::Result>( JetDeleteTableA( sessionId_, databaseId_, tableName ) );
            RequireSuccess( rc );
        }

        template<StringType T>
        void DeleteTable( const T& tableName )
        {
            DeleteTable( tableName.c_str( ) );
        }
        
    protected:
        void BeginTransaction( ) const
        {
            auto rc = static_cast<Ese::Result>( JetBeginTransaction( sessionId_ ) );
            RequireSuccess( rc );
        }
        void CommitTransaction( TransactionFlags flags = TransactionFlags::None ) const
        {
            auto rc = static_cast<Result>( JetCommitTransaction( sessionId_, (int)flags ) );
            if ( rc != Result::Success && rc != Result::ErrorNotInTransaction )
            {
                HCC_THROW( Exception, rc );
            }
        }

    public:
        [[nodiscard]] ObjectInfo GetTableInfo( const wchar_t* objectName ) const
        {
            ObjectInfo result;
            auto rc = static_cast<Ese::Result>( JetGetObjectInfoW( sessionId_, databaseId_, JET_objtypTable, nullptr, objectName, &result, sizeof( ObjectInfo ), JET_ObjInfoNoStats ) );
            RequireSuccess( rc );
            return result;
        }
        [[nodiscard]] ObjectInfo GetTableInfo( const char* objectName ) const
        {
            ObjectInfo result;
            auto rc = static_cast<Ese::Result>( JetGetObjectInfoA( sessionId_, databaseId_, JET_objtypTable, nullptr, objectName, &result, sizeof( ObjectInfo ), JET_ObjInfoNoStats ) );
            RequireSuccess( rc );
            return result;
        }
        template<StringType S>
        [[nodiscard]] ObjectInfo GetTableInfo( const S& objectName ) const
        {
            return GetTableInfo( objectName.c_str( ) );
        }

        [[nodiscard]] bool TableExists( const wchar_t* objectName ) const
        {
            ObjectInfo result;
            auto rc = static_cast<Ese::Result>( JetGetObjectInfoW( sessionId_, databaseId_, JET_objtypTable, nullptr, objectName, &result, sizeof( ObjectInfo ), JET_ObjInfoNoStats ) );
            if ( rc != Result::Success && rc != Result::ErrorInvalidName )
            {
                HCC_THROW( Exception, rc );
            }
            return rc != Result::ErrorInvalidName;
        }
        [[nodiscard]] bool TableExists( const char* objectName ) const
        {
            ObjectInfo result;
            auto rc = static_cast<Ese::Result>( JetGetObjectInfoA( sessionId_, databaseId_, JET_objtypTable, nullptr, objectName, &result, sizeof( ObjectInfo ), JET_ObjInfoNoStats ) );
            if ( rc != Result::Success && rc != Result::ErrorInvalidName )
            {
                HCC_THROW( Exception, rc );
            }
            return rc != Result::ErrorInvalidName;
        }
        template<StringType S>
        [[nodiscard]] bool TableExists( const S& objectName ) const
        {
            return TableExists( objectName.c_str() );
        }


    };


    // ------------------------------------------------------------------------
    // Transaction
    // ------------------------------------------------------------------------
    class Transaction 
    {
        const Session* session_;
    public:
        Transaction( )
            : session_( nullptr )
        {
        }

        explicit Transaction( const Session* session )
            : session_( session )
        {
        }
        HCC_EXPORT ~Transaction( );

        Transaction( const Transaction& other ) = delete;
        Transaction( Transaction&& other ) noexcept
            : session_( other.session_ )
        {
            other.session_ = nullptr;
        }
        Transaction& operator = ( const Transaction& other ) = delete;
        Transaction& operator = ( Transaction&& other )
        {
            if ( &other != this )
            {
                if ( session_ )
                {
                    Rollback( );
                }
                session_ = other.session_;
                other.session_ = nullptr;
            }
            return *this;
        }

        const Session& Session( ) const
        {
            return *session_;
        }
        HCC_EXPORT void Commit( TransactionFlags flags = TransactionFlags::None );
        HCC_EXPORT void Rollback( bool rollbackAll = false );
    };



    enum class AttachDatabaseFlags : int
    {
        None = 0,
        DeleteCorruptIndexes = JET_bitDbDeleteCorruptIndexes,
        DeleteUnicodeIndexes = JET_bitDbDeleteUnicodeIndexes,
        ReadOnly = JET_bitDbReadOnly,
        Upgrade = JET_bitDbUpgrade
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( AttachDatabaseFlags, int );

    enum class DetachDatabaseFlags : int
    {
        None = 0,
        ForceCloseAndDetach = JET_bitForceCloseAndDetach,
        ForceDetach = JET_bitForceDetach
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( DetachDatabaseFlags, int );

    /// <summary>
    /// Options for creating and attaching a new database.
    /// </summary>
    enum class CreateDatabaseFlags : int
    {
        None = 0,
        /// <summary>
        /// If a database already exists, it will be overwritten
        /// </summary>
        OverwriteExisting = JET_bitDbOverwriteExisting,
        /// <summary>
        /// Turns off logging. Setting this bit loses the ability 
        /// to replay log files and recover the database to a 
        /// consistent usable state after a catastrophic event
        /// </summary>
        RecoveryOff = JET_bitDbRecoveryOff,
        /// <summary>
        /// Disables the duplication of some internal database structures (shadowing). 
        /// The duplication of these structures is done for resiliency, so setting 
        /// ShadowingOff will remove this resiliency.
        /// </summary>
        ShadowingOff = JET_bitDbShadowingOff
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( CreateDatabaseFlags, int );

    enum class OpenDatabaseFlags : int
    {
        None = 0,
        Exclusive = JET_bitDbExclusive,
        ReadOnly = JET_bitDbReadOnly
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( OpenDatabaseFlags, int );


    class Session
    {
        JET_INSTANCE instance_;
        JET_SESID sessionId_;
    public:
        constexpr Session( ) noexcept
            : instance_(JET_instanceNil), sessionId_( JET_sesidNil )
        {
        }

        explicit Session( JET_INSTANCE instance, JET_SESID sessionId)
            : instance_( instance ), sessionId_( sessionId )
        {
        }

        ~Session( )
        {
            End( );
        }

        Session( const Session& other ) = delete;
        Session( Session&& other ) noexcept
            : instance_( other.instance_ ), sessionId_( other.sessionId_ )
        {
            other.instance_ = JET_instanceNil;
            other.sessionId_ = JET_sesidNil;
        }
        Session& operator = ( const Session& other ) = delete;
        Session& operator = ( Session&& other ) noexcept
        {
            if ( &other != this )
            {
                if ( sessionId_ != JET_sesidNil )
                {
                    JetEndSession( sessionId_, 0 );
                }
                instance_ = other.instance_;
                sessionId_ = other.sessionId_;
                other.instance_ = JET_instanceNil;
                other.sessionId_ = JET_sesidNil;
            }
            return *this;
        }

        JET_SESID Handle() const
        {
            return sessionId_;
        }

        /// <summary>
        /// Checks that the session is valid
        /// </summary>
        /// <returns>true if the session and instance handles are not nil</returns>
        constexpr bool IsValid( ) const noexcept
        {
            return instance_ != JET_instanceNil && sessionId_ != JET_sesidNil;
        }

        constexpr explicit operator bool( ) const noexcept
        {
            return IsValid( );
        }

    private:
        unsigned long long GetSystemNumericParameter( unsigned long paramId ) const
        {
            JET_API_PTR result = 0;
            auto rc = static_cast<Result>( JetGetSystemParameterW( instance_, sessionId_, paramId, &result, nullptr, 0 ) );
            RequireSuccess( rc );
            return result;
        }

        void GetSystemStringParameter( unsigned long paramId, JET_PWSTR szParam, unsigned long cbMax ) const
        {
            auto rc = static_cast<Result>( JetGetSystemParameterW( instance_, sessionId_, paramId, nullptr, szParam, cbMax ) );
            RequireSuccess( rc );
        }

        WideString GetSystemStringParameter( unsigned long paramId ) const
        {
            wchar_t buffer[1024] = { 0, };

            auto rc = static_cast<Result>( JetGetSystemParameterW( instance_, sessionId_, paramId, nullptr, buffer, sizeof( buffer ) ) );
            RequireSuccess( rc );
            return WideString( buffer );
        }

        void SetSystemParameter( unsigned long paramId, unsigned long long value )
        {
            auto rc = static_cast<Result>( JetSetSystemParameterW( &instance_, sessionId_, paramId, static_cast<JET_API_PTR>( value ), nullptr ) );
            RequireSuccess( rc );
        }

        void SetSystemParameter( unsigned long paramId, const WideString& value )
        {
            auto rc = static_cast<Result>( JetSetSystemParameterW( &instance_, sessionId_, paramId, 0, value.c_str( ) ) );
            RequireSuccess( rc );
        }

    public:
        bool SetContext( JET_API_PTR context ) const
        {
            auto rc = static_cast<Result>( JetSetSessionContext( sessionId_, context ) );
            if ( rc != Result::ErrorSessionContextAlreadySet )
            {
                RequireNotError( rc );
            }
            return rc != Result::ErrorSessionContextAlreadySet;
        }

        void ResetContext( ) const
        {
            auto rc = static_cast<Result>( JetResetSessionContext( sessionId_ ) );
            RequireNotError( rc );
        }


    
        TimeSpan QuerySnapshotTimeout() const
        {
            auto result = static_cast<double>( GetSystemNumericParameter(JET_paramOSSnapshotTimeout) );
            return TimeSpan::FromMilliseconds(result);
        }

        void SetSnapshotTimeout(const TimeSpan& value)
        {
            unsigned long long v = static_cast<unsigned long long>(value.TotalMilliseconds());
            SetSystemParameter(JET_paramOSSnapshotTimeout, v );
        }



        void End()
        {
            if ( sessionId_ != JET_sesidNil )
            {
                auto rc = static_cast<Ese::Result >( JetEndSession( sessionId_, 0 ) );
                RequireSuccess( rc );
                sessionId_ = JET_sesidNil;
            }
        }


        [[nodiscard]] Transaction StartTransaction( ) const
        {
            BeginTransaction( );
            Transaction result( this );
            return result;
        }

        void BeginTransaction() const
        {
            auto rc = static_cast<Ese::Result>( JetBeginTransaction( sessionId_ ) );
            RequireSuccess( rc );
        }

        void CommitTransaction(TransactionFlags flags = TransactionFlags::None ) const
        {
            auto rc = static_cast<Result>( JetCommitTransaction( sessionId_, ( int )flags ) );
            if ( rc != Result::Success && rc != Result::ErrorNotInTransaction )
            {
                HCC_THROW( Exception, rc );
            }
        }

        void Rollback(bool all = false) const
        {
            auto rc = static_cast<Result>( JetRollback( sessionId_, all ? JET_bitRollbackAll : 0 ));
            if (rc != Result::Success && rc != Result::ErrorNotInTransaction )
            {
                HCC_THROW( Exception, rc );
            }
        }

        /// <summary>
        /// Creates and attaches a database file to be used with the database 
        /// engine with a maximum database size specified.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="filename">The name of the database to be created</param>
        /// <param name="flags">Flags control how the database is created and attached to the engine.</param>
        /// <param name="maxDatabaseSizeInNumberOfPages">The maximum size, in database pages, for the database.</param>
        /// <returns>The Database object for the database.</returns>
        template<DatabaseType T=Database>
        [[nodiscard]] T CreateDatabase(const WideString& filename, CreateDatabaseFlags flags, unsigned long maxDatabaseSizeInNumberOfPages = 0) const
        {
            JET_DBID databaseId = 0;
            auto rc = static_cast<Result>( JetCreateDatabase2W( sessionId_, filename.c_str( ), maxDatabaseSizeInNumberOfPages, &databaseId, ( int )flags ) );
            RequireSuccess( rc );
            T result( sessionId_, databaseId );
            result.OnDatabaseCreated( );
            return result;
        }

        /// <summary>
        /// Creates and attaches a database file to be used with the database 
        /// engine with a maximum database size specified.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="filename">The name of the database to be created</param>
        /// <param name="flags">Flags control how the database is created and attached to the engine.</param>
        /// <param name="maxDatabaseSizeInNumberOfPages">The maximum size, in database pages, for the database.</param>
        /// <returns>The Database object for the database.</returns>
        template<DatabaseType T = Database>
        [[nodiscard]] T CreateDatabase( const AnsiString& filename, CreateDatabaseFlags flags, unsigned long maxDatabaseSizeInNumberOfPages = 0 ) const
        {
            JET_DBID databaseId = 0;
            auto rc = static_cast<Result>( JetCreateDatabase2A( sessionId_, filename.c_str( ), maxDatabaseSizeInNumberOfPages, &databaseId, (int)flags ) );
            RequireSuccess( rc );
            T result( sessionId_, databaseId );
            result.OnDatabaseCreated( );
            return result;
        }

        /// <summary>
        /// Attaches a database file for use with a database instance and 
        /// specifies a maximum size for that database. In order to use the 
        /// database, it will need to be subsequently opened with OpenDatabase.
        /// </summary>
        /// <param name="filename">The name of the database to attach</param>
        /// <param name="flags">Options to be used for this call</param>
        /// <param name="maxDatabaseSizeInNumberOfPages">The maximum size, in database pages, for database. The default, 0, means that there is no maximum enforced by the database engine</param>
        void AttachDatabase( const WideString& filename, AttachDatabaseFlags flags = AttachDatabaseFlags::None, unsigned long maxDatabaseSizeInNumberOfPages = 0 ) const
        {
            auto rc = static_cast<Result>( JetAttachDatabase2W( sessionId_, filename.c_str( ), maxDatabaseSizeInNumberOfPages, ( int )flags ) );
            RequireNotError( rc );
        }
        /// <summary>
        /// Attaches a database file for use with a database instance and 
        /// specifies a maximum size for that database. In order to use the 
        /// database, it will need to be subsequently opened with OpenDatabase.
        /// </summary>
        /// <param name="filename">The name of the database to attach</param>
        /// <param name="flags">Options to be used for this call</param>
        /// <param name="maxDatabaseSizeInNumberOfPages">The maximum size, in database pages, for database. The default, 0, means that there is no maximum enforced by the database engine</param>
        void AttachDatabase( const AnsiString& filename, AttachDatabaseFlags flags = AttachDatabaseFlags::None, unsigned long maxDatabaseSizeInNumberOfPages = 0 ) const
        {
            auto rc = static_cast<Result>( JetAttachDatabase2A( sessionId_, filename.c_str( ), maxDatabaseSizeInNumberOfPages, (int)flags ) );
            RequireNotError( rc );
        }

        void DetachDatabase(const WideString& filename, DetachDatabaseFlags flags) const
        {
            auto rc = static_cast<Result>( JetDetachDatabase2W( sessionId_, filename.c_str( ), ( int )flags ));
            RequireSuccess( rc );
        }

        void DetachAll(DetachDatabaseFlags flags) const
        {
            auto rc = static_cast<Result>( JetDetachDatabase2W( sessionId_, nullptr, ( int )flags ));
            RequireSuccess( rc );
        }

        /// <summary>
        /// Opens a previously attached database.
        /// </summary>
        /// <typeparam name="T">Database, or a move assignable type derived from Database</typeparam>
        /// <param name="filename">The name of the database to open</param>
        /// <param name="flags">Options controlling how the database is opened.</param>
        /// <returns></returns>
        template<DatabaseType T = Database>
        [[nodiscard]] T OpenDatabase( const WideString& filename, OpenDatabaseFlags flags = OpenDatabaseFlags::None ) const
        {
            wchar_t connect[1024] = { 0, };
            JET_DBID databaseId = 0;
            auto rc = static_cast<Result>( JetOpenDatabaseW( sessionId_, filename.c_str( ), connect, &databaseId, ( int )flags ) );
            RequireSuccess( rc );
            T result( sessionId_, databaseId );
            result.OnDatabaseOpened( );
            return result;
        }

        template<DatabaseType T = Database>
        [[nodiscard]] T OpenDatabase( const AnsiString& filename, OpenDatabaseFlags flags = OpenDatabaseFlags::None ) const
        {
            char connect[1024] = { 0, };
            JET_DBID databaseId = 0;
            auto rc = static_cast<Result>( JetOpenDatabaseA( sessionId_, filename.c_str( ), connect, &databaseId, ( int )flags ) );
            RequireSuccess( rc );
            T result( sessionId_, databaseId );
            result.OnDatabaseOpened( );
            return result;
        }

        Session Clone() const
        {
            JET_SESID sessionId = 0;
            auto rc = static_cast<Result>( JetDupSession( sessionId_, &sessionId ));
            RequireSuccess( rc );
            Session result(instance_, sessionId );
            return result;
        }

    };

    // ------------------------------------------------------------------------
    // Transaction
    // ------------------------------------------------------------------------
    inline Transaction::~Transaction( )
    {
        if ( session_ )
        {
            session_->Rollback( );
        }
    }

    inline void Transaction::Commit( TransactionFlags flags )
    {
        if ( session_ )
        {
            auto session = session_;
            session_ = nullptr;
            session->CommitTransaction( flags );
        }
    }
    inline void Transaction::Rollback( bool rollbackAll )
    {
        if ( session_ )
        {
            auto session = session_;
            session_ = nullptr;
            session->Rollback( rollbackAll );
        }
    }


    enum class InitFlags : int
    {
        None = 0,
        /// <summary>
        /// Ignore missing databases during recovery. This is a very 
        /// dangerous option and may irrevocably produce an inconsistent 
        /// database if improperly used. Normal ESE usage does not 
        /// typically require this dangerous option.
        /// </summary>
        ReplayIgnoreMissingDB = JET_bitReplayIgnoreMissingDB,
        /// <summary>
        /// Perform recovery, but halt at the Undo phase
        /// </summary>
        RecoveryWithoutUndo = JET_bitRecoveryWithoutUndo,
        /// <summary>
        /// On successful soft recovery, truncate log files
        /// </summary>
        TruncateLogsAfterRecovery = JET_bitTruncateLogsAfterRecovery,
        /// <summary>
        /// Missing database map entry default to same location
        /// </summary>
        ReplayMissingMapEntryDB = JET_bitReplayMissingMapEntryDB,
        /// <summary>
        /// transaction logs must exist in the logfile directory 
        /// (ie. cannot auto-start a new log stream)
        /// </summary>
        LogStreamMustExist = JET_bitLogStreamMustExist,
        /// <summary>
        /// Ignore logs lost from the end of the log stream
        /// </summary>
        ReplayIgnoreLostLogs = JET_bitReplayIgnoreLostLogs,
        /// <summary>
        /// allows db to remain attached at the end of recovery(for faster transition to running state)
        /// </summary>
        KeepDbAttachedAtEndOfRecovery = 0x00001000
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( InitFlags, int );

    enum class OnlineDefragFlags : unsigned
    {
        //	disable online defrag
        Disable = JET_OnlineDefragDisable,
        //	enable online defrag for everything (must be 1 for backward compatibility)
        AllOBSOLETE = JET_OnlineDefragAllOBSOLETE,
        //	enable online defrag of databases
        Databases = JET_OnlineDefragDatabases,
        //	enable online defrag of space trees
        SpaceTrees = JET_OnlineDefragSpaceTrees,
        //	enable online defrag for everything
        All = JET_OnlineDefragAll
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( OnlineDefragFlags, unsigned );


    enum class BackupFlags : unsigned
    {
        None,
        // Creates a full backup of the database. This allows the preservation 
        // of an existing backup in the same directory if the new backup fails.
        Atomic = JET_bitBackupAtomic,
        // Creates an incremental backup as opposed to a full backup. This 
        // means that only the log files created since the last full or 
        // incremental backup will be backed up.
        Incremental = JET_bitBackupIncremental,
        Snapshot = JET_bitBackupSnapshot

    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( BackupFlags, unsigned );


    class Instance
    {
        JET_INSTANCE instance_;
        mutable bool initialized_;
        InitFlags initFlags_;
    public:
        boost::signals2::signal<void( const Instance* instance )> BeforeInit;
        boost::signals2::signal<void( const Instance* instance )> AfterInit;
        Instance(  ) noexcept
            : instance_( JET_instanceNil ), initialized_( false ), initFlags_( InitFlags::None )
        {
        }

        Instance(const WideString& instanceName, const WideString& displayName = WideString(), InitFlags initFlags = InitFlags::None)
            : instance_(JET_instanceNil), initialized_(false), initFlags_(initFlags)
        {
            JET_INSTANCE instance = 0;
            auto rc = static_cast<Result>( JetCreateInstance2W( &instance, instanceName.c_str( ), displayName.empty()? instanceName.c_str( ) :  displayName.c_str( ), 0 ));
            RequireSuccess( rc );
            instance_ = instance;
        }


        inline Instance( const InstanceOptions& instanceOptions );

        Instance( const AnsiString& instanceName, const AnsiString& displayName = AnsiString( ), InitFlags initFlags = InitFlags::None )
            : instance_( JET_instanceNil ), initialized_( false ), initFlags_( initFlags )
        {
            JET_INSTANCE instance = 0;
            auto rc = static_cast<Result>( JetCreateInstance2A( &instance, instanceName.c_str( ), displayName.empty( ) ? instanceName.c_str( ) : displayName.c_str( ), 0 ) );
            RequireSuccess( rc );
            instance_ = instance;
        }

        Instance( const Instance& other ) = delete;
        Instance( Instance&& other )
            : instance_( other.instance_ ), initialized_( other.initialized_ ), initFlags_(other.initFlags_)
        {
            other.instance_ = JET_instanceNil;
            other.initialized_ = false;
            other.initFlags_ = InitFlags::None;
        }
        Instance& operator = ( const Instance& other ) = delete;
        Instance& operator = ( Instance&& other )
        {
            if ( &other != this )
            {
                if ( instance_ != JET_instanceNil )
                {
                    JetTerm2( instance_, JET_bitTermComplete );
                }
                instance_ = other.instance_; 
                initialized_ = other.initialized_; 
                initFlags_ = other.initFlags_;
                other.instance_ = JET_instanceNil;
                other.initialized_ = false;
                other.initFlags_ = InitFlags::None;
            }
            return *this;
        }


        ~Instance()
        {
            if (instance_ != JET_instanceNil)
            {
                JetTerm2(instance_, JET_bitTermComplete);
            }
        }

        JET_INSTANCE Handle() const
        {
            return instance_;
        }

        constexpr bool IsValid( ) const noexcept
        {
            return instance_ != JET_instanceNil;
        }

        constexpr explicit operator bool( ) const noexcept
        {
            return IsValid( );
        }

    private:
        void InitializeInstance( ) const
        {
            BeforeInit( this );
            if ( initFlags_ != InitFlags::None )
            {
                auto rc = static_cast<Result>( JetInit2( const_cast<JET_INSTANCE*>(&instance_), static_cast<JET_GRBIT>(initFlags_)));
                RequireSuccess( rc );
            }
            else
            {
                auto rc = static_cast<Result>( JetInit(const_cast<JET_INSTANCE*>(&instance_) ) );
                RequireSuccess( rc );
            }
            AfterInit( this );
            initialized_ = true;
        }
    public:

        /// <summary>
        /// Starts a session and initializes and returns a new Session object for the handle
        /// </summary>
        /// <remarks>
        /// Sessions control all access to the database and are used to control the scope of 
        /// transactions. The session can be used to begin, commit, or abort transactions. 
        /// The session is also used to attach, create, or open a database. The session is 
        /// used as the context for all DDL and DML operations. To increase concurrency 
        /// and parallel access to the database, multiple sessions can be begun.
        /// </remarks>
        [[nodiscard]] Session BeginSession() const
        {
            if (!initialized_)
            {
                InitializeInstance( );
            }
            JET_SESID sessionId = 0;
            auto rc = static_cast<Result>( JetBeginSessionW( instance_, &sessionId, nullptr, nullptr ));
            RequireSuccess( rc );
            Session result( instance_, sessionId );
            return result;
        }

        Result Backup( const WideString& backupPath, BackupFlags backupFlags, JET_PFNSTATUS statusCallbackFunction = nullptr ) const
        {
            auto rc = static_cast<Result>( JetBackupInstanceW( instance_, backupPath.c_str( ), static_cast< unsigned long >( backupFlags ), statusCallbackFunction ) );
            RequireNotError( rc );
            return rc;
        }


        Result Restore( const WideString& backupPath, const WideString& destinationPath, JET_PFNSTATUS statusCallbackFunction = nullptr ) const
        {
            auto rc = static_cast<Result>( JetRestoreInstanceW( instance_, backupPath.c_str( ), destinationPath.c_str(), statusCallbackFunction ) );
            RequireNotError( rc );
            return rc;
        }

        Result Restore( const WideString& backupPath, JET_PFNSTATUS statusCallbackFunction = nullptr ) const
        {
            auto rc = static_cast<Result>( JetRestoreInstanceW( instance_, backupPath.c_str( ), nullptr, statusCallbackFunction ) );
            RequireNotError( rc );
            return rc;
        }



    private:
        unsigned long long GetSystemNumericParameter(unsigned long paramId) const
        {
            JET_API_PTR result = 0;
            auto rc = static_cast<Result>( JetGetSystemParameterW( instance_, JET_sesidNil, paramId, &result, nullptr, 0 ));
            RequireSuccess( rc );
            return result;
        }

        static unsigned long long GetGlobalSystemNumericParameter(unsigned long paramId)
        {
            JET_API_PTR result = 0;
            auto rc = static_cast<Result>( JetGetSystemParameterW( NULL, JET_sesidNil, paramId, &result, nullptr, 0 ));
            RequireSuccess( rc );
            return result;
        }

        void GetSystemStringParameter(unsigned long paramId, JET_PWSTR szParam, unsigned long cbMax) const
        {
            auto rc = static_cast<Result>( JetGetSystemParameterW( instance_, JET_sesidNil, paramId, nullptr, szParam, cbMax ));
            RequireSuccess( rc );
        }

        WideString GetSystemStringParameter(unsigned long paramId) const
        {
            wchar_t buffer[1024] = { 0, };
            auto rc = static_cast<Result>( JetGetSystemParameterW( instance_, JET_sesidNil, paramId, nullptr, buffer, sizeof( buffer ) ));
            RequireSuccess( rc );
            return WideString(buffer);
        }

        void SetSystemParameter(unsigned long paramId, unsigned long long value) const
        {
            auto rc = static_cast<Result>( JetSetSystemParameterW( const_cast<JET_INSTANCE*>(&instance_), JET_sesidNil, paramId, static_cast<JET_API_PTR>(value), nullptr));
            RequireSuccess( rc );
        }

        static void SetGlobalSystemParameter(unsigned long paramId, unsigned long long value)
        {
            auto rc = static_cast<Result>( JetSetSystemParameterW( NULL, JET_sesidNil, paramId, static_cast<JET_API_PTR>( value ), nullptr ));
            RequireSuccess( rc );
        }

        void SetSystemParameter(unsigned long paramId, const WideString& value) const
        {
            auto rc = static_cast<Result>( JetSetSystemParameterW(const_cast<JET_INSTANCE*>(&instance_), JET_sesidNil, paramId, 0, value.c_str( ) ));
            RequireSuccess( rc );
        }
        void SetSystemParameter( unsigned long paramId, const AnsiString& value ) const
        {
            auto rc = static_cast<Result>( JetSetSystemParameterA(const_cast<JET_INSTANCE*>(&instance_), JET_sesidNil, paramId, 0, value.c_str( ) ) );
            RequireSuccess( rc );
        }

    public:

        // The full path to each database is persisted in the transaction logs at run time. 
        // Ordinarily, these databases must remain at the original location for transaction 
        // replay to function correctly. This can be used to force crash recovery or a restore 
        // operation to look for the databases referenced in the transaction log in the 
        // specified folder
        WideString QueryAlternateDatabaseRecoveryPath() const
        {
            auto result = GetSystemStringParameter(JET_paramAlternateDatabaseRecoveryPath);
            return result;
        }

        // The full path to each database is persisted in the transaction logs at run time. 
        // Ordinarily, these databases must remain at the original location for transaction 
        // replay to function correctly. This can be used to force crash recovery or a restore 
        // operation to look for the databases referenced in the transaction log in the 
        // specified folder
        void SetAlternateDatabaseRecoveryPath( const WideString& value ) const
        {
            SetSystemParameter(JET_paramAlternateDatabaseRecoveryPath, value);
        }


        // Controls the outcome of JetInit when the database engine is configured to start 
        // using transaction log files on disk that are of a different size than what is 
        // configured.Normally, JetInit will successfully recover the databases but will 
        // fail with JET_errLogFileSizeMismatchDatabasesConsistent to indicate that the 
        // log file size is misconfigured.However, when this parameter is set to true then 
        // the database engine will silently delete all the old log files, start a new set 
        // of transaction log files using the configured log file size, and return JET_errSuccess.
        //
        // This is useful when the application wishes to transparently change its transaction log 
        // file size yet still work transparently in upgrade and restore scenarios.
        bool QueryCleanupMismatchedLogFiles() const
        {
            auto result = GetSystemNumericParameter(JET_paramCleanupMismatchedLogFiles);
            return result != FALSE;
        }

        // Controls the outcome of JetInit when the database engine is configured to start 
        // using transaction log files on disk that are of a different size than what is 
        // configured.Normally, JetInit will successfully recover the databases but will 
        // fail with JET_errLogFileSizeMismatchDatabasesConsistent to indicate that the 
        // log file size is misconfigured.However, when this parameter is set to true then 
        // the database engine will silently delete all the old log files, start a new set 
        // of transaction log files using the configured log file size, and return JET_errSuccess.
        //
        // This is useful when the application wishes to transparently change its transaction log 
        // file size yet still work transparently in upgrade and restore scenarios.
        void SetCleanupMismatchedLogFiles(bool value) const
        {
            SetSystemParameter(JET_paramCleanupMismatchedLogFiles, value ? TRUE : FALSE);
        }

        // When this setting is true, then any transaction log files found on disk that are not 
        // part of the current sequence of log files will be deleted by JetInit.This may be 
        // used to automatically clean up extraneous log files after a restore operation.
        bool QueryDeleteOutOfRangeLogs() const
        {
            auto result = GetSystemNumericParameter(JET_paramDeleteOutOfRangeLogs);
            return result != FALSE;
        }

        // When this setting is true, then any transaction log files found on disk that are not 
        // part of the current sequence of log files will be deleted by JetInit.This may be 
        // used to automatically clean up extraneous log files after a restore operation.
        void SetDeleteOutOfRangeLogs(bool value) const
        {
            SetSystemParameter(JET_paramDeleteOutOfRangeLogs, value ? TRUE : FALSE);
        }


        TimeSpan QuerySnapshotTimeout() const
        {
            auto result = static_cast<double>( GetSystemNumericParameter(JET_paramOSSnapshotTimeout) );
            return TimeSpan::FromMilliseconds(result);
        }

        void SetSnapshotTimeout(const TimeSpan& value) const
        {
            unsigned long long v = static_cast<unsigned long long>(value.TotalMilliseconds());
            SetSystemParameter(JET_paramOSSnapshotTimeout, v );
        }


        bool QueryZeroDatabaseDuringBackup() const
        {
            auto result = GetSystemNumericParameter(JET_paramZeroDatabaseDuringBackup);
            return result != FALSE;
        }

        void SetZeroDatabaseDuringBackup(bool value) const
        {
            SetSystemParameter(JET_paramZeroDatabaseDuringBackup, value ? TRUE : FALSE);
        }

        static long QueryDatabasePageSize()
        {
            auto result = static_cast<long>(GetGlobalSystemNumericParameter(JET_paramDatabasePageSize));
            return result;
        }

        static void SetDatabasePageSize(long value)
        {
            SetGlobalSystemParameter(JET_paramDatabasePageSize, static_cast<unsigned long long>(value));
        }

        long QueryDbExtensionSize() const
        {
            auto result = static_cast<long>(GetSystemNumericParameter(JET_paramDbExtensionSize));
            return result;
        }

        void SetDbExtensionSize(long value) const
        {
            SetSystemParameter(JET_paramDbExtensionSize, static_cast<unsigned long long>(value));
        }

        static bool QueryEnableIndexChecking()
        {
            auto result = GetGlobalSystemNumericParameter(JET_paramEnableIndexChecking);
            return result != FALSE;
        }

        static void SetEnableIndexChecking(bool value)
        {
            SetGlobalSystemParameter(JET_paramEnableIndexChecking, value ? TRUE : FALSE);
        }

        bool QueryEnableIndexCleanup() const
        {
            auto result = GetSystemNumericParameter(JET_paramEnableIndexCleanup);
            return result != FALSE;
        }

        void SetEnableIndexCleanup(bool value) const
        {
            SetSystemParameter(JET_paramEnableIndexCleanup, value ? TRUE : FALSE);
        }

        static bool QueryOneDatabasePerSession()
        {
            auto result = GetGlobalSystemNumericParameter(JET_paramOneDatabasePerSession);
            return result != FALSE;
        }

        static void SetOneDatabasePerSession(bool value)
        {
            SetGlobalSystemParameter(JET_paramOneDatabasePerSession, value ? TRUE : FALSE);
        }


        OnlineDefragFlags QueryEnableOnlineDefrag() const
        {
            auto result = static_cast<OnlineDefragFlags>( GetSystemNumericParameter(JET_paramEnableOnlineDefrag) );
            return result;
        }

        void SetEnableOnlineDefrag(OnlineDefragFlags value) const
        {
            SetSystemParameter(JET_paramEnableOnlineDefrag, static_cast<unsigned>( value ));
        }


        long QueryPageFragment() const
        {
            auto result = static_cast<long>(GetSystemNumericParameter(JET_paramPageFragment));
            return result;
        }

        void SetPageFragment(long value) const
        {
            SetSystemParameter(JET_paramPageFragment, static_cast<unsigned long long>(value));
        }

        long QueryRecordUpgradeDirtyLevel() const
        {
            auto result = static_cast<long>(GetSystemNumericParameter(JET_paramRecordUpgradeDirtyLevel));
            return result;
        }

        void SetRecordUpgradeDirtyLevel(long value) const
        {
            SetSystemParameter(JET_paramRecordUpgradeDirtyLevel, static_cast<unsigned long long>(value));
        }


        long QueryWaypointLatency() const
        {
            auto result = static_cast<long>(GetSystemNumericParameter(JET_paramWaypointLatency));
            return result;
        }

        void SetWaypointLatency(long value) const
        {
            SetSystemParameter(JET_paramWaypointLatency, static_cast<unsigned long long>(value));
        }

        bool QueryDefragmentSequentialBTrees() const
        {
            auto result = GetSystemNumericParameter(JET_paramDefragmentSequentialBTrees);
            return result != FALSE;
        }

        void SetDefragmentSequentialBTrees(bool value) const
        {
            SetSystemParameter(JET_paramDefragmentSequentialBTrees, value ? TRUE : FALSE);
        }

        long QueryDefragmentSequentialBTreesDensityCheckFrequency() const
        {
            auto result = static_cast<long>(GetSystemNumericParameter(JET_paramDefragmentSequentialBTreesDensityCheckFrequency));
            return result;
        }

        void SetDefragmentSequentialBTreesDensityCheckFrequency(long value) const
        {
            SetSystemParameter(JET_paramDefragmentSequentialBTreesDensityCheckFrequency, static_cast<unsigned long long>(value));
        }

        TimeSpan QueryIOThrottlingTimeQuanta() const
        {
            auto result = GetSystemNumericParameter(JET_paramIOThrottlingTimeQuanta);
            return TimeSpan::FromMilliseconds(static_cast<double>(result));
        }

        void SetIOThrottlingTimeQuanta(const TimeSpan& value) const
        {
            unsigned long long v = static_cast<unsigned long long>(value.TotalMilliseconds());
            SetSystemParameter(JET_paramIOThrottlingTimeQuanta, v);
        }

        TimeSpan QueryAccessDeniedRetryPeriod() const
        {
            auto result = GetSystemNumericParameter(JET_paramAccessDeniedRetryPeriod);
            return TimeSpan::FromMilliseconds(static_cast<double>(result));
        }

        void SetAccessDeniedRetryPeriod(const TimeSpan& value) const
        {
            unsigned long long v = static_cast<unsigned long long>(value.TotalMilliseconds());
            SetSystemParameter(JET_paramAccessDeniedRetryPeriod, v);
        }

        /// <summary>
        /// When this parameter is set to true then any folder that is missing 
        /// in a file system path in use by the database engine will be silently 
        /// created. Otherwise, the operation that uses the missing file system 
        /// path will throw an Ese::Exception for Result::ErrorInvalidPath
        /// </summary>
        /// <returns>true if parameter is set</returns>
        bool QueryCreatePathIfNotExist() const
        {
            auto result = GetSystemNumericParameter(JET_paramCreatePathIfNotExist);
            return result != FALSE;
        }

        /// <summary>
        /// When this parameter is set to true then any folder that is missing 
        /// in a file system path in use by the database engine will be silently 
        /// created. Otherwise, the operation that uses the missing file system 
        /// path will throw an Ese::Exception for Result::ErrorInvalidPath
        /// </summary>
        /// <param name="value">value to assign to the CreatePathIfNotExist parameter</param>
        void SetCreatePathIfNotExist(bool value = true) const
        {
            SetSystemParameter(JET_paramCreatePathIfNotExist, value ? TRUE : FALSE);
        }


        static bool QueryEnableFileCache()
        {
            auto result = GetGlobalSystemNumericParameter(JET_paramEnableFileCache);
            return result != FALSE;
        }

        static void SetEnableFileCache(bool value)
        {
            SetGlobalSystemParameter(JET_paramEnableFileCache, value ? TRUE : FALSE);
        }

        bool QueryIOPriorityLow() const
        {
            auto result = GetSystemNumericParameter(JET_paramIOPriority);
            return result != FALSE;
        }

        void SetIOPriorityLow(bool value) const
        {
            SetSystemParameter(JET_paramIOPriority, value ? TRUE : FALSE);
        }

        static unsigned QueryOutstandingIOMax()
        {
            auto result = GetGlobalSystemNumericParameter(JET_paramOutstandingIOMax);
            return static_cast<unsigned>(result);
        }

        static void SetOutstandingIOMax(unsigned value)
        {
            SetGlobalSystemParameter(JET_paramOutstandingIOMax, value);
        }

        unsigned long long QueryMaxCoalesceReadSize() const
        {
            auto result = GetSystemNumericParameter(JET_paramMaxCoalesceReadSize);
            return result;
        }

        void SetMaxCoalesceReadSize(unsigned long long value) const
        {
            SetSystemParameter(JET_paramMaxCoalesceReadSize, value);
        }

        unsigned long long QueryMaxCoalesceWriteSize() const
        {
            auto result = GetSystemNumericParameter(JET_paramMaxCoalesceWriteSize);
            return result;
        }

        void SetMaxCoalesceWriteSize(unsigned long long value) const
        {
            SetSystemParameter(JET_paramMaxCoalesceWriteSize, value);
        }

        unsigned long long QueryMaxCoalesceReadGapSize() const
        {
            auto result = GetSystemNumericParameter(JET_paramMaxCoalesceReadGapSize);
            return result;
        }

        void SetMaxCoalesceReadGapSize(unsigned long long value) const
        {
            SetSystemParameter(JET_paramMaxCoalesceReadGapSize, value);
        }

        unsigned long long QueryMaxCoalesceWriteGapSize() const
        {
            auto result = GetSystemNumericParameter(JET_paramMaxCoalesceWriteGapSize);
            return result;
        }

        void SetMaxCoalesceWriteGapSize(unsigned long long value) const
        {
            SetSystemParameter(JET_paramMaxCoalesceWriteGapSize, value);
        }

        bool QueryDisableCallbacks() const
        {
            auto result = GetSystemNumericParameter(JET_paramDisableCallbacks);
            return result != FALSE;
        }

        void SetDisableCallbacks(bool value) const
        {
            SetSystemParameter(JET_paramDisableCallbacks, value ? TRUE : FALSE);
        }

        bool QueryEnablePersistedCallbacks() const
        {
            auto result = GetSystemNumericParameter(JET_paramEnablePersistedCallbacks);
            return result != FALSE;
        }

        void SetEnablePersistedCallbacks(bool value) const
        {
            SetSystemParameter(JET_paramEnablePersistedCallbacks, value ? TRUE : FALSE);
        }

        JET_CALLBACK* QueryRuntimeCallback() const
        {
            auto result = (JET_CALLBACK*)GetSystemNumericParameter(JET_paramRuntimeCallback);
            return result;
        }

        void SetRuntimeCallback(JET_CALLBACK* value) const
        {
            SetSystemParameter(JET_paramRuntimeCallback, reinterpret_cast<unsigned long long>(value));
        }

        static Int32 QueryBatchIOBufferMax( )
        {
            auto result = GetGlobalSystemNumericParameter( JET_paramBatchIOBufferMax );
            return static_cast< Int32 >( result );
        }
        static void SetBatchIOBufferMax( Int32 value )
        {
            SetGlobalSystemParameter( JET_paramBatchIOBufferMax, static_cast<UInt64>(value) );
        }
        


        unsigned long long QueryCacheSize() const
        {
            auto result = GetSystemNumericParameter(JET_paramCacheSize);
            return result;
        }

        void SetCacheSize(unsigned long long value) const
        {
            SetSystemParameter(JET_paramCacheSize, value);
        }

        unsigned long long QueryCacheSizeMin() const
        {
            auto result = GetSystemNumericParameter(JET_paramCacheSizeMin);
            return result;
        }

        void SetCacheSizeMin(unsigned long long value) const
        {
            SetSystemParameter(JET_paramCacheSizeMin, value);
        }

        unsigned long long QueryCacheSizeMax() const
        {
            auto result = GetSystemNumericParameter(JET_paramCacheSizeMax);
            return result;
        }

        void SetCacheSizeMax(unsigned long long value) const
        {
            SetSystemParameter(JET_paramCacheSizeMax, value);
        }

        unsigned long long QueryCheckpointDepthMax() const
        {
            auto result = GetSystemNumericParameter(JET_paramCheckpointDepthMax);
            return result;
        }

        void SetCheckpointDepthMax(unsigned long long value) const
        {
            SetSystemParameter(JET_paramCheckpointDepthMax, value);
        }


        unsigned long long QueryCheckpointIOMax() const
        {
            auto result = GetSystemNumericParameter(JET_paramCheckpointIOMax);
            return result;
        }

        void SetCheckpointIOMax(unsigned long long value) const
        {
            SetSystemParameter(JET_paramCheckpointIOMax, value);
        }

        static bool QueryEnableViewCache( )
        {
            auto result = GetGlobalSystemNumericParameter( JET_paramEnableViewCache );
            return result != FALSE;
        }

        static void SetEnableViewCache( bool value )
        {
            SetGlobalSystemParameter( JET_paramEnableViewCache, value ? TRUE : FALSE );
        }


        static TimeSpan QueryLRUKCorrInterval()
        {
            auto result = TimeSpan( GetGlobalSystemNumericParameter(JET_paramLRUKCorrInterval) * TimeSpan::TicksPerMicrosecond );
            return result;
        }

        static void SetLRUKCorrInterval( TimeSpan value)
        {
            SetGlobalSystemParameter(JET_paramLRUKCorrInterval, static_cast<UInt64>(value.ToMicroseconds() / TimeSpan::TicksPerMicrosecond ));
        }

        static unsigned long long QueryLRUKHistoryMax()
        {
            auto result = GetGlobalSystemNumericParameter(JET_paramLRUKHistoryMax);
            return result;
        }

        static void SetLRUKHistoryMax(unsigned long long value)
        {
            SetGlobalSystemParameter(JET_paramLRUKHistoryMax, value);
        }

        static unsigned long long QueryLRUKPolicy()
        {
            auto result = GetGlobalSystemNumericParameter(JET_paramLRUKPolicy);
            return result;
        }

        static void SetLRUKPolicy(unsigned long long value)
        {
            SetGlobalSystemParameter(JET_paramLRUKPolicy, value);
        }


        static TimeSpan QueryLRUKTimeout()
        {
            auto result = GetGlobalSystemNumericParameter(JET_paramLRUKTimeout);
            return TimeSpan::FromSeconds(static_cast<double>(result));
        }

        static void SetLRUKTimeout(const TimeSpan& value)
        {
            auto v = static_cast<unsigned long long>(value.ToSeconds());
            SetGlobalSystemParameter(JET_paramLRUKTimeout, v);
        }


        unsigned long long QueryStartFlushThreshold() const
        {
            auto result = GetSystemNumericParameter(JET_paramStartFlushThreshold);
            return result;
        }

        void SetStartFlushThreshold(unsigned long long value) const
        {
            SetSystemParameter(JET_paramStartFlushThreshold, value);
        }

        unsigned long long QueryStopFlushThreshold() const
        {
            auto result = GetSystemNumericParameter(JET_paramStopFlushThreshold);
            return result;
        }

        void SetStopFlushThreshold(unsigned long long value) const
        {
            SetSystemParameter(JET_paramStopFlushThreshold, value);
        }

        /// <summary>
        /// This setting controls what happens when an exception is thrown by the database engine 
        /// or code that is called by the database engine. When set to ExceptionAction::DisplayMessageBox, 
        /// any exception will be thrown to the Windows unhandled exception filter.This will result in the 
        /// exception being handled as an application failure.The intent is to prevent application code from 
        /// erroneously trying to catch and ignore an exception generated by the database engine.This cannot 
        /// be allowed because database corruption could occur.If the application wishes to properly handle 
        /// these exceptions then the protection can be disabled by setting this parameter to ExceptionAction::None.
        /// </summary>
        static ExceptionAction QueryExceptionAction( )
        {
            auto result = static_cast<Ese::ExceptionAction>( GetGlobalSystemNumericParameter( JET_paramExceptionAction ));
            return result;
        }

        /// <summary>
        /// This setting controls what happens when an exception is thrown by the database engine 
        /// or code that is called by the database engine. When set to ExceptionAction::DisplayMessageBox, 
        /// any exception will be thrown to the Windows unhandled exception filter.This will result in the 
        /// exception being handled as an application failure.The intent is to prevent application code from 
        /// erroneously trying to catch and ignore an exception generated by the database engine.This cannot 
        /// be allowed because database corruption could occur.If the application wishes to properly handle 
        /// these exceptions then the protection can be disabled by setting this parameter to ExceptionAction::None.
        /// </summary>
        static void SetExceptionAction( Ese::ExceptionAction value )
        {
            SetGlobalSystemParameter( JET_paramExceptionAction, static_cast<unsigned long long>(value) );
        }

        // This setting controls the size (in bytes) of an eventlog message cache that 
        // will hold eventlog messages emitted by the database engine while the eventlog 
        // service is stopped. These cached messages will be flushed to the eventlog when 
        // the service becomes operational. 
        //
        // Valid range: 0 – 2147483647
        //
        // Any messages that overflow the cache will be dropped.
        static unsigned long long QueryEventLogCacheSize( )
        {
            auto result = GetGlobalSystemNumericParameter( JET_paramEventLogCache );
            return result;
        }

        static void SetEventLogCacheSize( size_t numberOfBytes )
        {
            SetGlobalSystemParameter( JET_paramEventLogCache, static_cast<unsigned long long>( numberOfBytes ) );
        }


        /// <summary>
        /// This parameter sets the three letter prefix used for many of the files used by the 
        /// database engine. For example, the checkpoint file is called EDB.CHK by default 
        /// because EDB is the default base name. The base name can be used to easily 
        /// distinguish between sets of files that belong to different instances or 
        /// to different applications.
        /// </summary>
        WideString QueryBaseName() const
        {
            auto result = GetSystemStringParameter(JET_paramBaseName);
            return result;
        }

        void SetBaseName(const WideString& value) const
        {
            SetSystemParameter(JET_paramBaseName, value);
        }

        /// <summary>
        /// This parameter configures how transaction log files are managed by the database engine.
        /// </summary>
        /// <remarks>
        /// When circular logging is off, all transaction log files that are generated are retained 
        /// on disk until they are no longer needed because a full backup of the database has been 
        /// performed. In this mode, it is possible to restore from an older backup and play forward 
        /// through all the retained transaction log files such that no data is lost as a result of 
        /// the disaster that forced the restore. Regular full backups are required to prevent the 
        /// disk from filling up with transaction log files.
        /// 
        /// When circular logging is on, only transaction log files that are younger than the current 
        /// checkpoint are retained on disk.The benefit of this mode is that backups are not required 
        /// to retire old transaction log files.The tradeoff is that a zero data loss restore is no 
        /// longer possible.
        /// </remarks>
        /// <returns>The current value of the CircularLog parameter</returns>
        bool QueryCircularLog() const
        {
            auto result = GetSystemNumericParameter(JET_paramCircularLog);
            return result != FALSE;
        }

        /// <summary>
        /// This parameter configures how transaction log files are managed by the database engine.
        /// </summary>
        /// <remarks>
        /// When circular logging is off, all transaction log files that are generated are retained 
        /// on disk until they are no longer needed because a full backup of the database has been 
        /// performed. In this mode, it is possible to restore from an older backup and play forward 
        /// through all the retained transaction log files such that no data is lost as a result of 
        /// the disaster that forced the restore. Regular full backups are required to prevent the 
        /// disk from filling up with transaction log files.
        /// 
        /// When circular logging is on, only transaction log files that are younger than the current 
        /// checkpoint are retained on disk.The benefit of this mode is that backups are not required 
        /// to retire old transaction log files.The tradeoff is that a zero data loss restore is no 
        /// longer possible.
        /// </remarks>
        /// <param name="value">The new value to assign to the CircularLog parameter</param>
        void SetCircularLog(bool value = true) const
        {
            SetSystemParameter(JET_paramCircularLog, value ? TRUE : FALSE);
        }

        TransactionFlags QueryCommitDefault() const
        {
            auto result = static_cast<TransactionFlags> (GetSystemNumericParameter(JET_paramCommitDefault));
            return result;
        }

        void SetCommitDefault(TransactionFlags value) const
        {
            SetSystemParameter(JET_paramCommitDefault, (unsigned long long)value);
        }

        bool QueryDeleteOldLogs() const
        {
            auto result = GetSystemNumericParameter(JET_paramDeleteOldLogs);
            return result != FALSE;
        }

        void SetDeleteOldLogs(bool value) const
        {
            SetSystemParameter(JET_paramDeleteOldLogs, value ? TRUE : FALSE);
        }

        bool QueryIgnoreLogVersion() const
        {
            auto result = GetSystemNumericParameter(JET_paramIgnoreLogVersion);
            return result != FALSE;
        }

        void SetIgnoreLogVersion(bool value) const
        {
            SetSystemParameter(JET_paramIgnoreLogVersion, value ? TRUE : FALSE);
        }

        bool QueryLegacyFileNames() const
        {
            auto result = GetSystemNumericParameter(JET_paramLegacyFileNames);
            return result == JET_bitESE98FileNames;
        }

        void SetLegacyFileNames(bool value) const
        {
            SetSystemParameter(JET_paramLegacyFileNames, value ? JET_bitESE98FileNames : 0);
        }

        unsigned long long QueryLogBuffers() const
        {
            auto result = GetSystemNumericParameter(JET_paramLogBuffers);
            return result;
        }

        void SetLogBuffers(unsigned long long value) const
        {
            SetSystemParameter(JET_paramLogBuffers, value);
        }

        unsigned long long QueryLogCheckpointPeriod() const
        {
            auto result = GetSystemNumericParameter(JET_paramLogCheckpointPeriod);
            return result;
        }

        void SetLogCheckpointPeriod(unsigned long long value) const
        {
            SetSystemParameter(JET_paramLogCheckpointPeriod, value);
        }

        bool QueryLogFileCreateAsynch() const
        {
            auto result = GetSystemNumericParameter(JET_paramLogFileCreateAsynch);
            return result != FALSE;
        }

        void SetLogFileCreateAsynch(bool value) const
        {
            SetSystemParameter(JET_paramLogFileCreateAsynch, value ? TRUE : FALSE);
        }

        /// <summary>
        /// This parameter indicates the relative or absolute file system path of the 
        /// folder that will contain the transaction logs for the instance.
        /// </summary>
        /// <remarks>
        /// The path must be terminated with a backslash character, which indicates 
        /// that the target path is a folder. The transaction log files contain the 
        /// information required to bring the database files to a consistent state 
        /// after a crash. They are typically named EDB*.LOG. The contents of the 
        /// transaction log files are just as important (if not more so) than the 
        /// database files themselves. Every effort should be made to protect them.
        /// 
        /// There will also be additional reserve log files named RES1.LOGand RES2.LOG 
        /// stored along with the ordinary log files.The contents of these files 
        /// are not important as their only purpose is to reserve disk space to allow 
        /// the engine to shut down gracefully in a low disk scenario.These will 
        /// also be a temporary log file typically named EDBTMP.LOG in this same folder.
        /// The contents of this file are not important either.This file is a new 
        /// log file being prepared for use.
        /// 
        /// The properties of the host volume of the transaction log files and their 
        /// placement relative to the other files used by the database engine can 
        /// dramatically impact performance.
        /// 
        /// Note:If a relative path is specified then it will be relative to the 
        /// current working directory of the process that hosts the application 
        /// that is using the database engine.
        /// </remarks>
        /// <returns>The current value of the LogFilePath parameter</returns>
        WideString QueryLogFilePath() const
        {
            auto result = GetSystemStringParameter(JET_paramLogFilePath);
            return result;
        }

        /// <summary>
        /// This parameter indicates the relative or absolute file system path of the 
        /// folder that will contain the transaction logs for the instance.
        /// </summary>
        /// <remarks>
        /// The path must be terminated with a backslash character, which indicates 
        /// that the target path is a folder. The transaction log files contain the 
        /// information required to bring the database files to a consistent state 
        /// after a crash. They are typically named EDB*.LOG. The contents of the 
        /// transaction log files are just as important (if not more so) than the 
        /// database files themselves. Every effort should be made to protect them.
        /// 
        /// There will also be additional reserve log files named RES1.LOGand RES2.LOG 
        /// stored along with the ordinary log files.The contents of these files 
        /// are not important as their only purpose is to reserve disk space to allow 
        /// the engine to shut down gracefully in a low disk scenario.These will 
        /// also be a temporary log file typically named EDBTMP.LOG in this same folder.
        /// The contents of this file are not important either.This file is a new 
        /// log file being prepared for use.
        /// 
        /// The properties of the host volume of the transaction log files and their 
        /// placement relative to the other files used by the database engine can 
        /// dramatically impact performance.
        /// 
        /// Note:If a relative path is specified then it will be relative to the 
        /// current working directory of the process that hosts the application 
        /// that is using the database engine.
        /// </remarks>
        /// <param name="value">The value to assign to the LogFilePath parameter</param>
        void SetLogFilePath(const WideString& value) const
        {
            SetSystemParameter(JET_paramLogFilePath, value);
        }
        void SetLogFilePath( const AnsiString& value ) const
        {
            SetSystemParameter( JET_paramLogFilePath, value );
        }

        unsigned long long QueryLogFileSize() const
        {
            auto result = GetSystemNumericParameter(JET_paramLogFileSize);
            return result;
        }

        void SetLogFileSize(unsigned long long value) const
        {
            SetSystemParameter(JET_paramLogFileSize, value);
        }

        unsigned long long QueryLogWaitingUserMax() const
        {
            auto result = GetSystemNumericParameter(JET_paramLogWaitingUserMax);
            return result;
        }

        void SetLogWaitingUserMax(unsigned long long value) const
        {
            SetSystemParameter(JET_paramLogWaitingUserMax, value);
        }


        WideString QueryRecovery() const
        {
            auto result = GetSystemStringParameter(JET_paramRecovery);
            return result;
        }

        void SetRecovery(const WideString& value) const
        {
            SetSystemParameter(JET_paramRecovery, value);
        }

        /// <summary>
        /// This parameter indicates the relative or absolute file system path of 
        /// the folder that will contain the checkpoint file for the instance. 
        /// The path must be terminated with a backslash character, which indicates 
        /// that the target path is a folder. The checkpoint file is a simple file 
        /// maintained per instance that remembers the oldest transaction log file 
        /// that must be replayed to bring all databases in that instance to a 
        /// consistent state after a crash. The checkpoint file is typically 
        /// named EDB.CHK.
        /// 
        /// If a relative path is specified then it will be relative to the current 
        /// working directory of the process that hosts the application that is using 
        /// the database engine.
        /// </summary>
        /// <returns>The current value of the SystemPath parameter</returns>
        WideString QuerySystemPath() const
        {
            auto result = GetSystemStringParameter(JET_paramSystemPath);
            return result;
        }

        /// <summary>
        /// This parameter indicates the relative or absolute file system path of 
        /// the folder that will contain the checkpoint file for the instance. 
        /// The path must be terminated with a backslash character, which indicates 
        /// that the target path is a folder. The checkpoint file is a simple file 
        /// maintained per instance that remembers the oldest transaction log file 
        /// that must be replayed to bring all databases in that instance to a 
        /// consistent state after a crash. The checkpoint file is typically 
        /// named EDB.CHK.
        /// 
        /// If a relative path is specified then it will be relative to the current 
        /// working directory of the process that hosts the application that is using 
        /// the database engine.
        /// </summary>
        /// <param name="value">The new value to assign to the SystemPath parameter</param>
        void SetSystemPath(const WideString& value) const
        {
            SetSystemParameter(JET_paramSystemPath, value);
        }
        void SetSystemPath( const AnsiString& value ) const
        {
            SetSystemParameter( JET_paramSystemPath, value );
        }

        /// <summary>
        /// This setting controls the number of B+ Tree resources cached by the 
        /// instance after the tables they represent have been closed by the 
        /// application.
        ///
        /// Large values for this setting will cause the database engine to use more 
        /// memory but will increase the speed with which a large number of tables 
        /// can be opened randomly by the application.This is useful for applications 
        /// that have a schema with a very large number of tables.
        /// </summary>
        /// <returns>The current value of the CachedClosedTables parameter</returns>
        unsigned long long QueryNumberOfCachedClosedTables( ) const
        {
            auto result = GetSystemNumericParameter( JET_paramCachedClosedTables );
            return result;
        }
        /// <summary>
        /// This setting controls the number of B+ Tree resources cached by the 
        /// instance after the tables they represent have been closed by the 
        /// application.
        ///
        /// Large values for this setting will cause the database engine to use more 
        /// memory but will increase the speed with which a large number of tables 
        /// can be opened randomly by the application.This is useful for applications 
        /// that have a schema with a very large number of tables.
        /// </summary>
        /// <param name="value">The new value to assign to the CachedClosedTables parameter</param>
        void SetNumberOfCachedClosedTables( size_t value ) const
        {
            SetSystemParameter( JET_paramCachedClosedTables, value );
        }

        // This parameter can be used to prevent the database engine from publishing data 
        // about its performance to Windows. This can be done to reduce the service thread 
        // activity of the database engine.
        static bool QueryMonitoringPerformance( )
        {
            auto result = GetGlobalSystemNumericParameter( JET_paramDisablePerfmon );
            return result == FALSE;
        }
        static void SetMonitoringPerformance( bool value )
        {
            SetGlobalSystemParameter( JET_paramDisablePerfmon, value ? FALSE : TRUE );
        }

        // This seting allows applications that operate in multi-instance mode to pre-allocate 
        // memory for version pages in a global pool. 
        //
        // This is useful in case the application wishes to guarantee that transactions 
        // of a certain size can succeed later on even if memory becomes scarce.
        static unsigned long long QueryGlobalMinimumVersionPageCount( )
        {
            auto result = GetGlobalSystemNumericParameter( JET_paramGlobalMinVerPages );
            return result;
        }
        static void SetGlobalMinimumVersionPageCount( size_t value )
        {
            SetGlobalSystemParameter( JET_paramGlobalMinVerPages, value );
        }

        // This setting reserves the requested number of cursor resources for use by 
        // an instance. A cursor resource directly corresponds to a JET_TABLEID data type. 
        //
        // This setting will affect how many cursors can be used at the same time. A cursor 
        // resource cannot be shared by different sessions so this parameter must be set to 
        // a large enough value so that each session can use as many cursors as are required.
        unsigned long long QueryMaxCursorCount( ) const
        {
            auto result = GetSystemNumericParameter( JET_paramMaxCursors );
            return result;
        }
        void SetMaxCursorCount( size_t value ) const
        {
            SetSystemParameter( JET_paramMaxCursors, value );
        }


        // This setting controls the maximum number of instances that can be created in 
        // a single process
        static unsigned long long QueryMaximumInstanceCount( )
        {
            auto result = GetGlobalSystemNumericParameter( JET_paramMaxInstances );
            return result;
        }
        static void SetMaximumInstanceCount( size_t value )
        {
            SetGlobalSystemParameter( JET_paramMaxInstances, value );
        }

        // This setting reserves the requested number of B+ Tree resources for use by an instance. 
        // This setting will affect how many tables can be used at the same time. This parameter 
        // needs to be set relative to the physical schema of the databases in use by the database 
        // engine, so this setting is not as straightforward as it could be.
        //
        // In general, you will need two resources plus one resource per secondary index per 
        // table in concurrent use by the application.
        unsigned long long QueryMaxOpenTableCount( ) const
        {
            auto result = GetSystemNumericParameter( JET_paramMaxOpenTables );
            return result;
        }
        void SetMaxOpenTableCount( size_t value ) const
        {
            SetSystemParameter( JET_paramMaxOpenTables, value );
        }

        /// <summary>
        /// <para>
        /// This parameter attempts to keep the number of B+ Tree resources in use below the specified threshold.
        /// </para>
        /// <para>
        /// 
        /// </para>
        /// </summary>
        /// <returns></returns>
        unsigned long long QueryPreferredMaxOpenTables( ) const
        {
            auto result = GetSystemNumericParameter( JET_paramPreferredMaxOpenTables );
            return result;
        }
        void SetPreferredMaxOpenTables( size_t value ) const
        {
            SetSystemParameter( JET_paramPreferredMaxOpenTables, value );
        }


        // This setting reserves the requested number of session resources for use by an instance. 
        // A session resource directly corresponds to a JET_SESID data type. This setting will affect 
        // how many sessions can be used at the same time.
        unsigned long long QueryMaxSessionCount( ) const
        {
            auto result = GetSystemNumericParameter( JET_paramMaxSessions );
            return result;
        }
        void SetMaxSessionCount( size_t value ) const
        {
            SetSystemParameter( JET_paramMaxSessions, value );
        }

        // This setting reserves the requested number of temporary table resources for use by an instance. 
        // This setting will affect how many temporary tables can be used at the same time.
        //
        // If this is set to zero then no temporary database will be created and any activity 
        // that requires use of the temporary database will fail. This setting can be useful to 
        // avoid the I/O required to create the temporary database if it is known that it will 
        // not be used.
        //
        // Note: The use of a temporary table also requires a cursor resource
        unsigned long long QueryMaxTemporaryTableCount( ) const
        {
            auto result = GetSystemNumericParameter( JET_paramMaxTemporaryTables );
            return result;
        }
        void SetMaxTemporaryTableCount( size_t value ) const
        {
            SetSystemParameter( JET_paramMaxTemporaryTables, value );
        }

        // This parameter reserves the requested number of version store pages for use by an instance. 
        // The version store holds a live record of all the different versions of each record or index 
        // entry in the database that can be seen by all active transactions. These versions are used 
        // to support the multi-versioned concurrency control in use by the database engine to support 
        // transactions using snapshot isolation. This setting will affect how many updates can be held 
        // in memory at a time. This in turn will affect either the maximum number of updates a single 
        // transaction can perform, the maximum duration a transaction can be held open, the maximum 
        // concurrent load of updating transactions on the system, or a combination of these.
        //
        // Each version store page as configured by this parameter defaults to 16KB in size.
        //
        // Note: This is by far the most common resource to be exhausted by the database engine.
        // Careful attention must be paid to the setting of the system parameter and to the 
        // transactional load of the application to avoid exhausting this resource under normal operation.
        // When this resource is exhausted, updates to the database will be rejected with 
        // JET_errVersionStoreOutOfMemory.To release some of these resources, the oldest outstanding 
        // transaction must be aborted.
        unsigned long long QueryMaxVersionPageCount( ) const
        {
            auto result = GetSystemNumericParameter( JET_paramMaxVerPages );
            return result;
        }
        void SetMaxVersionPageCount( size_t value ) const
        {
            SetSystemParameter( JET_paramMaxVerPages, value );
        }

        // This setting controls the size of a special cache used to accelerate the lookup of 
        // B+ Tree child page pointers in the database page cache.
        //
        // The size of the cache is in bytes.
        unsigned long long QueryPageHintCacheSize( ) const
        {
            auto result = GetSystemNumericParameter( JET_paramPageHintCacheSize );
            return result;
        }
        void SetPageHintCacheSize( size_t value ) const
        {
            SetSystemParameter( JET_paramPageHintCacheSize, value );
        }
    };

}

namespace Harlinn::Common::Core
{
    HCC_EXPORT WideString ToWideString( Ese::ColumnType value );
    HCC_EXPORT WideString ToWideString( Ese::ColumnType value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Ese::ColumnType value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Ese::ColumnType value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Ese
    {
        HCC_EXPORT Ese::ColumnType ParseColumnType( const WideString& str );
        HCC_EXPORT Ese::ColumnType ParseColumnType( const WideString& str, Ese::ColumnType defaultResult );
        HCC_EXPORT bool TryParseColumnType( const WideString& str, Ese::ColumnType& value );

        inline Ese::ColumnType ParseColumnType( const AnsiString& str )
        {
            return ParseColumnType( ToWideString( str ) );
        }
        inline Ese::ColumnType ParseColumnType( const AnsiString& str, Ese::ColumnType defaultResult )
        {
            return ParseColumnType( ToWideString( str ), defaultResult );
        }
        inline bool TryParseColumnType( const AnsiString& str, Ese::ColumnType& value )
        {
            return TryParseColumnType( ToWideString( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT,WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Ese::ColumnType& value )
    {
        return Ese::TryParseColumnType( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Ese::ColumnType, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Ese::ParseColumnType( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Ese::ColumnType, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Ese::ParseColumnType( str );
    }
    

    HCC_EXPORT WideString ToWideString( Ese::ColumnFlags value );
    HCC_EXPORT WideString ToWideString( Ese::ColumnFlags value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Ese::ColumnFlags value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Ese::ColumnFlags value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Ese
    {
        HCC_EXPORT Ese::ColumnFlags ParseColumnFlags( const WideString& str );
        HCC_EXPORT Ese::ColumnFlags ParseColumnFlags( const WideString& str, Ese::ColumnFlags defaultResult );
        HCC_EXPORT bool TryParseColumnFlags( const WideString& str, Ese::ColumnFlags& value );

        inline Ese::ColumnFlags ParseColumnFlags( const AnsiString& str )
        {
            return ParseColumnFlags( ToWideString( str ) );
        }
        inline Ese::ColumnFlags ParseColumnFlags( const AnsiString& str, Ese::ColumnFlags defaultResult )
        {
            return ParseColumnFlags( ToWideString( str ), defaultResult );
        }
        inline bool TryParseColumnType( const AnsiString& str, Ese::ColumnFlags& value )
        {
            return TryParseColumnFlags( ToWideString( str ), value );
        }
    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Ese::ColumnFlags& value )
    {
        return Ese::TryParseColumnFlags( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Ese::ColumnFlags, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Ese::ParseColumnFlags( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Ese::ColumnFlags, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Ese::ParseColumnFlags( str );
    }

    HCC_EXPORT WideString ToWideString( Ese::IndexFlags value );
    HCC_EXPORT WideString ToWideString( Ese::IndexFlags value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Ese::IndexFlags value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Ese::IndexFlags value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Ese
    {
        HCC_EXPORT Ese::IndexFlags ParseIndexFlags( const WideString& str );
        HCC_EXPORT Ese::IndexFlags ParseIndexFlags( const WideString& str, Ese::IndexFlags defaultResult );
        HCC_EXPORT bool TryParseIndexFlags( const WideString& str, Ese::IndexFlags& value );

        inline Ese::IndexFlags ParseIndexFlags( const AnsiString& str )
        {
            return ParseIndexFlags( ToWideString( str ) );
        }
        inline Ese::IndexFlags ParseIndexFlags( const AnsiString& str, Ese::IndexFlags defaultResult )
        {
            return ParseIndexFlags( ToWideString( str ), defaultResult );
        }
        inline bool TryParseIndexFlags( const AnsiString& str, Ese::IndexFlags& value )
        {
            return TryParseIndexFlags( ToWideString( str ), value );
        }

    }

    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Ese::IndexFlags& value )
    {
        return Ese::TryParseIndexFlags( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Ese::IndexFlags, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Ese::ParseIndexFlags( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Ese::IndexFlags, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Ese::ParseIndexFlags( str );
    }

    HCC_EXPORT WideString ToWideString( Ese::RetrieveFlags value );
    HCC_EXPORT WideString ToWideString( Ese::RetrieveFlags value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Ese::RetrieveFlags value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Ese::RetrieveFlags value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Ese
    {
        HCC_EXPORT Ese::RetrieveFlags ParseRetrieveFlags( const WideString& str );
        HCC_EXPORT Ese::RetrieveFlags ParseRetrieveFlags( const WideString& str, Ese::RetrieveFlags defaultResult );
        HCC_EXPORT bool TryParseRetrieveFlags( const WideString& str, Ese::RetrieveFlags& value );

        inline Ese::RetrieveFlags ParseRetrieveFlags( const AnsiString& str )
        {
            return ParseRetrieveFlags( ToWideString( str ) );
        }
        inline Ese::RetrieveFlags ParseRetrieveFlags( const AnsiString& str, Ese::RetrieveFlags defaultResult )
        {
            return ParseRetrieveFlags( ToWideString( str ), defaultResult );
        }
        inline bool TryParseRetrieveFlags( const AnsiString& str, Ese::RetrieveFlags& value )
        {
            return TryParseRetrieveFlags( ToWideString( str ), value );
        }
    }

    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Ese::RetrieveFlags& value )
    {
        return Ese::TryParseRetrieveFlags( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Ese::RetrieveFlags, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Ese::ParseRetrieveFlags( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Ese::RetrieveFlags, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Ese::ParseRetrieveFlags( str );
    }

    HCC_EXPORT WideString ToWideString( Ese::SetFlags value );
    HCC_EXPORT WideString ToWideString( Ese::SetFlags value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Ese::SetFlags value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Ese::SetFlags value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Ese
    {
        HCC_EXPORT Ese::SetFlags ParseSetFlags( const WideString& str );
        HCC_EXPORT Ese::SetFlags ParseSetFlags( const WideString& str, Ese::SetFlags defaultResult );
        HCC_EXPORT bool TryParseSetFlags( const WideString& str, Ese::SetFlags& value );

        inline Ese::SetFlags ParseSetFlags( const AnsiString& str )
        {
            return ParseSetFlags( ToWideString( str ) );
        }
        inline Ese::SetFlags ParseSetFlags( const AnsiString& str, Ese::SetFlags defaultResult )
        {
            return ParseSetFlags( ToWideString( str ), defaultResult );
        }
        inline bool TryParseSetFlags( const AnsiString& str, Ese::SetFlags& value )
        {
            return TryParseSetFlags( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Ese::SetFlags& value )
    {
        return Ese::TryParseSetFlags( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Ese::SetFlags, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Ese::ParseSetFlags( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Ese::SetFlags, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Ese::ParseSetFlags( str );
    }

    HCC_EXPORT WideString ToWideString( Ese::ColumnInfoFlags value );
    HCC_EXPORT WideString ToWideString( Ese::ColumnInfoFlags value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Ese::ColumnInfoFlags value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Ese::ColumnInfoFlags value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }
    namespace Ese
    {
        HCC_EXPORT Ese::ColumnInfoFlags ParseColumnInfoFlags( const WideString& str );
        HCC_EXPORT Ese::ColumnInfoFlags ParseColumnInfoFlags( const WideString& str, Ese::ColumnInfoFlags defaultResult );
        HCC_EXPORT bool TryParseColumnInfoFlags( const WideString& str, Ese::ColumnInfoFlags& value );

        inline Ese::ColumnInfoFlags ParseColumnInfoFlags( const AnsiString& str )
        {
            return ParseColumnInfoFlags( ToWideString( str ) );
        }
        inline Ese::ColumnInfoFlags ParseColumnInfoFlags( const AnsiString& str, Ese::ColumnInfoFlags defaultResult )
        {
            return ParseColumnInfoFlags( ToWideString( str ), defaultResult );
        }
        inline bool TryParseColumnInfoFlags( const AnsiString& str, Ese::ColumnInfoFlags& value )
        {
            return TryParseColumnInfoFlags( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Ese::ColumnInfoFlags& value )
    {
        return Ese::TryParseColumnInfoFlags( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Ese::ColumnInfoFlags, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Ese::ParseColumnInfoFlags( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Ese::ColumnInfoFlags, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Ese::ParseColumnInfoFlags( str );
    }


    HCC_EXPORT WideString ToWideString( Ese::PrepareUpdateOptions value );
    HCC_EXPORT WideString ToWideString( Ese::PrepareUpdateOptions value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Ese::PrepareUpdateOptions value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Ese::PrepareUpdateOptions value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Ese
    {
        HCC_EXPORT Ese::PrepareUpdateOptions ParsePrepareUpdateOptions( const WideString& str );
        HCC_EXPORT Ese::PrepareUpdateOptions ParsePrepareUpdateOptions( const WideString& str, Ese::PrepareUpdateOptions defaultResult );
        HCC_EXPORT bool TryParsePrepareUpdateOptions( const WideString& str, Ese::PrepareUpdateOptions& value );

        inline Ese::PrepareUpdateOptions ParsePrepareUpdateOptions( const AnsiString& str )
        {
            return ParsePrepareUpdateOptions( ToWideString( str ) );
        }
        inline Ese::PrepareUpdateOptions ParsePrepareUpdateOptions( const AnsiString& str, Ese::PrepareUpdateOptions defaultResult )
        {
            return ParsePrepareUpdateOptions( ToWideString( str ), defaultResult );
        }
        inline bool TryParsePrepareUpdateOptions( const AnsiString& str, Ese::PrepareUpdateOptions& value )
        {
            return TryParsePrepareUpdateOptions( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Ese::PrepareUpdateOptions& value )
    {
        return Ese::TryParsePrepareUpdateOptions( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Ese::PrepareUpdateOptions, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Ese::ParsePrepareUpdateOptions( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Ese::PrepareUpdateOptions, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Ese::ParsePrepareUpdateOptions( str );
    }

    // =========================================================================
    // KeyFlags
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Ese::KeyFlags value );
    HCC_EXPORT WideString ToWideString( Ese::KeyFlags value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Ese::KeyFlags value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Ese::KeyFlags value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Ese
    {
        HCC_EXPORT Ese::KeyFlags ParseKeyFlags( const WideString& str );
        HCC_EXPORT Ese::KeyFlags ParseKeyFlags( const WideString& str, Ese::KeyFlags defaultResult );
        HCC_EXPORT bool TryParseKeyFlags( const WideString& str, Ese::KeyFlags& value );

        inline Ese::KeyFlags ParseKeyFlags( const AnsiString& str )
        {
            return ParseKeyFlags( ToWideString( str ) );
        }
        inline Ese::KeyFlags ParseKeyFlags( const AnsiString& str, Ese::KeyFlags defaultResult )
        {
            return ParseKeyFlags( ToWideString( str ), defaultResult );
        }
        inline bool TryParseKeyFlags( const AnsiString& str, Ese::KeyFlags& value )
        {
            return TryParseKeyFlags( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Ese::KeyFlags& value )
    {
        return Ese::TryParseKeyFlags( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Ese::KeyFlags, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Ese::ParseKeyFlags( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Ese::KeyFlags, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Ese::ParseKeyFlags( str );
    }

    // =========================================================================
    // SeekFlags
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Ese::SeekFlags value );
    HCC_EXPORT WideString ToWideString( Ese::SeekFlags value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Ese::SeekFlags value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Ese::SeekFlags value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Ese
    {
        HCC_EXPORT Ese::SeekFlags ParseSeekFlags( const WideString& str );
        HCC_EXPORT Ese::SeekFlags ParseSeekFlags( const WideString& str, Ese::SeekFlags defaultResult );
        HCC_EXPORT bool TryParseSeekFlags( const WideString& str, Ese::SeekFlags& value );

        inline Ese::SeekFlags ParseSeekFlags( const AnsiString& str )
        {
            return ParseSeekFlags( ToWideString( str ) );
        }
        inline Ese::SeekFlags ParseSeekFlags( const AnsiString& str, Ese::SeekFlags defaultResult )
        {
            return ParseSeekFlags( ToWideString( str ), defaultResult );
        }
        inline bool TryParseSeekFlags( const AnsiString& str, Ese::SeekFlags& value )
        {
            return TryParseSeekFlags( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Ese::SeekFlags& value )
    {
        return Ese::TryParseSeekFlags( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Ese::SeekFlags, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Ese::ParseSeekFlags( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Ese::SeekFlags, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Ese::ParseSeekFlags( str );
    }


    // =========================================================================
    // IndexRangeFlags
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Ese::IndexRangeFlags value );
    HCC_EXPORT WideString ToWideString( Ese::IndexRangeFlags value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Ese::IndexRangeFlags value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Ese::IndexRangeFlags value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Ese
    {
        HCC_EXPORT Ese::IndexRangeFlags ParseIndexRangeFlags( const WideString& str );
        HCC_EXPORT Ese::IndexRangeFlags ParseIndexRangeFlags( const WideString& str, Ese::IndexRangeFlags defaultResult );
        HCC_EXPORT bool TryParseIndexRangeFlags( const WideString& str, Ese::IndexRangeFlags& value );

        inline Ese::IndexRangeFlags ParseIndexRangeFlags( const AnsiString& str )
        {
            return ParseIndexRangeFlags( ToWideString( str ) );
        }
        inline Ese::IndexRangeFlags ParseIndexRangeFlags( const AnsiString& str, Ese::IndexRangeFlags defaultResult )
        {
            return ParseIndexRangeFlags( ToWideString( str ), defaultResult );
        }
        inline bool TryParseIndexRangeFlags( const AnsiString& str, Ese::IndexRangeFlags& value )
        {
            return TryParseIndexRangeFlags( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Ese::IndexRangeFlags& value )
    {
        return Ese::TryParseIndexRangeFlags( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Ese::IndexRangeFlags, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Ese::ParseIndexRangeFlags( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Ese::IndexRangeFlags, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Ese::ParseIndexRangeFlags( str );
    }

    // =========================================================================
    // SetCurrentIndexFlags
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Ese::SetCurrentIndexFlags value );
    HCC_EXPORT WideString ToWideString( Ese::SetCurrentIndexFlags value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Ese::SetCurrentIndexFlags value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Ese::SetCurrentIndexFlags value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Ese
    {
        HCC_EXPORT Ese::SetCurrentIndexFlags ParseSetCurrentIndexFlags( const WideString& str );
        HCC_EXPORT Ese::SetCurrentIndexFlags ParseSetCurrentIndexFlags( const WideString& str, Ese::SetCurrentIndexFlags defaultResult );
        HCC_EXPORT bool TryParseSetCurrentIndexFlags( const WideString& str, Ese::SetCurrentIndexFlags& value );

        inline Ese::SetCurrentIndexFlags ParseSetCurrentIndexFlags( const AnsiString& str )
        {
            return ParseSetCurrentIndexFlags( ToWideString( str ) );
        }
        inline Ese::SetCurrentIndexFlags ParseSetCurrentIndexFlags( const AnsiString& str, Ese::SetCurrentIndexFlags defaultResult )
        {
            return ParseSetCurrentIndexFlags( ToWideString( str ), defaultResult );
        }
        inline bool TryParseSetCurrentIndexFlags( const AnsiString& str, Ese::SetCurrentIndexFlags& value )
        {
            return TryParseSetCurrentIndexFlags( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Ese::SetCurrentIndexFlags& value )
    {
        return Ese::TryParseSetCurrentIndexFlags( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Ese::SetCurrentIndexFlags, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Ese::ParseSetCurrentIndexFlags( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Ese::SetCurrentIndexFlags, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Ese::ParseSetCurrentIndexFlags( str );
    }

    // =========================================================================
    // TableOptions
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Ese::TableOptions value );
    HCC_EXPORT WideString ToWideString( Ese::TableOptions value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Ese::TableOptions value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Ese::TableOptions value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Ese
    {
        HCC_EXPORT Ese::TableOptions ParseTableOptions( const WideString& str );
        HCC_EXPORT Ese::TableOptions ParseTableOptions( const WideString& str, Ese::TableOptions defaultResult );
        HCC_EXPORT bool TryParseTableOptions( const WideString& str, Ese::TableOptions& value );

        inline Ese::TableOptions ParseTableOptions( const AnsiString& str )
        {
            return ParseTableOptions( ToWideString( str ) );
        }
        inline Ese::TableOptions ParseTableOptions( const AnsiString& str, Ese::TableOptions defaultResult )
        {
            return ParseTableOptions( ToWideString( str ), defaultResult );
        }
        inline bool TryParseTableOptions( const AnsiString& str, Ese::TableOptions& value )
        {
            return TryParseTableOptions( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Ese::TableOptions& value )
    {
        return Ese::TryParseTableOptions( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Ese::TableOptions, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Ese::ParseTableOptions( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Ese::TableOptions, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Ese::ParseTableOptions( str );
    }

    // =========================================================================
    // ObjectFlags
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Ese::ObjectFlags value );
    HCC_EXPORT WideString ToWideString( Ese::ObjectFlags value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Ese::ObjectFlags value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Ese::ObjectFlags value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Ese
    {
        HCC_EXPORT Ese::ObjectFlags ParseObjectFlags( const WideString& str );
        HCC_EXPORT Ese::ObjectFlags ParseObjectFlags( const WideString& str, Ese::ObjectFlags defaultResult );
        HCC_EXPORT bool TryParseObjectFlags( const WideString& str, Ese::ObjectFlags& value );

        inline Ese::ObjectFlags ParseObjectFlags( const AnsiString& str )
        {
            return ParseObjectFlags( ToWideString( str ) );
        }
        inline Ese::ObjectFlags ParseObjectFlags( const AnsiString& str, Ese::ObjectFlags defaultResult )
        {
            return ParseObjectFlags( ToWideString( str ), defaultResult );
        }
        inline bool TryParseObjectFlags( const AnsiString& str, Ese::ObjectFlags& value )
        {
            return TryParseObjectFlags( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Ese::ObjectFlags& value )
    {
        return Ese::TryParseObjectFlags( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Ese::ObjectFlags, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Ese::ParseObjectFlags( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Ese::ObjectFlags, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Ese::ParseObjectFlags( str );
    }

    // =========================================================================
    // SequentialFlags
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Ese::SequentialFlags value );
    HCC_EXPORT WideString ToWideString( Ese::SequentialFlags value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Ese::SequentialFlags value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Ese::SequentialFlags value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Ese
    {
        HCC_EXPORT Ese::SequentialFlags ParseSequentialFlags( const WideString& str );
        HCC_EXPORT Ese::SequentialFlags ParseSequentialFlags( const WideString& str, Ese::SequentialFlags defaultResult );
        HCC_EXPORT bool TryParseSequentialFlags( const WideString& str, Ese::SequentialFlags& value );

        inline Ese::SequentialFlags ParseSequentialFlags( const AnsiString& str )
        {
            return ParseSequentialFlags( ToWideString( str ) );
        }
        inline Ese::SequentialFlags ParseSequentialFlags( const AnsiString& str, Ese::SequentialFlags defaultResult )
        {
            return ParseSequentialFlags( ToWideString( str ), defaultResult );
        }
        inline bool TryParseSequentialFlags( const AnsiString& str, Ese::SequentialFlags& value )
        {
            return TryParseSequentialFlags( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Ese::SequentialFlags& value )
    {
        return Ese::TryParseSequentialFlags( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Ese::SequentialFlags, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Ese::ParseSequentialFlags( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Ese::SequentialFlags, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Ese::ParseSequentialFlags( str );
    }


    // =========================================================================
    // ExceptionAction
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Ese::ExceptionAction value );
    HCC_EXPORT WideString ToWideString( Ese::ExceptionAction value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Ese::ExceptionAction value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Ese::ExceptionAction value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Ese
    {
        HCC_EXPORT Ese::ExceptionAction ParseExceptionAction( const WideString& str );
        HCC_EXPORT Ese::ExceptionAction ParseExceptionAction( const WideString& str, Ese::ExceptionAction defaultResult );
        HCC_EXPORT bool TryParseExceptionAction( const WideString& str, Ese::ExceptionAction& value );

        inline Ese::ExceptionAction ParseExceptionAction( const AnsiString& str )
        {
            return ParseExceptionAction( ToWideString( str ) );
        }
        inline Ese::ExceptionAction ParseExceptionAction( const AnsiString& str, Ese::ExceptionAction defaultResult )
        {
            return ParseExceptionAction( ToWideString( str ), defaultResult );
        }
        inline bool TryParseExceptionAction( const AnsiString& str, Ese::ExceptionAction& value )
        {
            return TryParseExceptionAction( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Ese::ExceptionAction& value )
    {
        return Ese::TryParseExceptionAction( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Ese::ExceptionAction, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Ese::ParseExceptionAction( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Ese::ExceptionAction, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Ese::ParseExceptionAction( str );
    }


    // =========================================================================
    // OpenTableFlags
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Ese::OpenTableFlags value );
    HCC_EXPORT WideString ToWideString( Ese::OpenTableFlags value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Ese::OpenTableFlags value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Ese::OpenTableFlags value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Ese
    {
        HCC_EXPORT Ese::OpenTableFlags ParseOpenTableFlags( const WideString& str );
        HCC_EXPORT Ese::OpenTableFlags ParseOpenTableFlags( const WideString& str, Ese::OpenTableFlags defaultResult );
        HCC_EXPORT bool TryParseOpenTableFlags( const WideString& str, Ese::OpenTableFlags& value );

        inline Ese::OpenTableFlags ParseOpenTableFlags( const AnsiString& str )
        {
            return ParseOpenTableFlags( ToWideString( str ) );
        }
        inline Ese::OpenTableFlags ParseOpenTableFlags( const AnsiString& str, Ese::OpenTableFlags defaultResult )
        {
            return ParseOpenTableFlags( ToWideString( str ), defaultResult );
        }
        inline bool TryParseOpenTableFlags( const AnsiString& str, Ese::OpenTableFlags& value )
        {
            return TryParseOpenTableFlags( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Ese::OpenTableFlags& value )
    {
        return Ese::TryParseOpenTableFlags( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Ese::OpenTableFlags, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Ese::ParseOpenTableFlags( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Ese::OpenTableFlags, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Ese::ParseOpenTableFlags( str );
    }

    // =========================================================================
    // TransactionFlags
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Ese::TransactionFlags value );
    HCC_EXPORT WideString ToWideString( Ese::TransactionFlags value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Ese::TransactionFlags value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Ese::TransactionFlags value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Ese
    {
        HCC_EXPORT Ese::TransactionFlags ParseTransactionFlags( const WideString& str );
        HCC_EXPORT Ese::TransactionFlags ParseTransactionFlags( const WideString& str, Ese::TransactionFlags defaultResult );
        HCC_EXPORT bool TryParseTransactionFlags( const WideString& str, Ese::TransactionFlags& value );

        inline Ese::TransactionFlags ParseTransactionFlags( const AnsiString& str )
        {
            return ParseTransactionFlags( ToWideString( str ) );
        }
        inline Ese::TransactionFlags ParseTransactionFlags( const AnsiString& str, Ese::TransactionFlags defaultResult )
        {
            return ParseTransactionFlags( ToWideString( str ), defaultResult );
        }
        inline bool TryParseTransactionFlags( const AnsiString& str, Ese::TransactionFlags& value )
        {
            return TryParseTransactionFlags( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Ese::TransactionFlags& value )
    {
        return Ese::TryParseTransactionFlags( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Ese::TransactionFlags, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Ese::ParseTransactionFlags( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Ese::TransactionFlags, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Ese::ParseTransactionFlags( str );
    }

    // =========================================================================
    // AttachDatabaseFlags
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Ese::AttachDatabaseFlags value );
    HCC_EXPORT WideString ToWideString( Ese::AttachDatabaseFlags value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Ese::AttachDatabaseFlags value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Ese::AttachDatabaseFlags value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Ese
    {
        HCC_EXPORT Ese::AttachDatabaseFlags ParseAttachDatabaseFlags( const WideString& str );
        HCC_EXPORT Ese::AttachDatabaseFlags ParseAttachDatabaseFlags( const WideString& str, Ese::AttachDatabaseFlags defaultResult );
        HCC_EXPORT bool TryParseAttachDatabaseFlags( const WideString& str, Ese::AttachDatabaseFlags& value );

        inline Ese::AttachDatabaseFlags ParseAttachDatabaseFlags( const AnsiString& str )
        {
            return ParseAttachDatabaseFlags( ToWideString( str ) );
        }
        inline Ese::AttachDatabaseFlags ParseAttachDatabaseFlags( const AnsiString& str, Ese::AttachDatabaseFlags defaultResult )
        {
            return ParseAttachDatabaseFlags( ToWideString( str ), defaultResult );
        }
        inline bool TryParseAttachDatabaseFlags( const AnsiString& str, Ese::AttachDatabaseFlags& value )
        {
            return TryParseAttachDatabaseFlags( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Ese::AttachDatabaseFlags& value )
    {
        return Ese::TryParseAttachDatabaseFlags( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Ese::AttachDatabaseFlags, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Ese::ParseAttachDatabaseFlags( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Ese::AttachDatabaseFlags, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Ese::ParseAttachDatabaseFlags( str );
    }

    // =========================================================================
    // DetachDatabaseFlags
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Ese::DetachDatabaseFlags value );
    HCC_EXPORT WideString ToWideString( Ese::DetachDatabaseFlags value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Ese::DetachDatabaseFlags value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Ese::DetachDatabaseFlags value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Ese
    {
        HCC_EXPORT Ese::DetachDatabaseFlags ParseDetachDatabaseFlags( const WideString& str );
        HCC_EXPORT Ese::DetachDatabaseFlags ParseDetachDatabaseFlags( const WideString& str, Ese::DetachDatabaseFlags defaultResult );
        HCC_EXPORT bool TryParseDetachDatabaseFlags( const WideString& str, Ese::DetachDatabaseFlags& value );

        inline Ese::DetachDatabaseFlags ParseDetachDatabaseFlags( const AnsiString& str )
        {
            return ParseDetachDatabaseFlags( ToWideString( str ) );
        }
        inline Ese::DetachDatabaseFlags ParseDetachDatabaseFlags( const AnsiString& str, Ese::DetachDatabaseFlags defaultResult )
        {
            return ParseDetachDatabaseFlags( ToWideString( str ), defaultResult );
        }
        inline bool TryParseDetachDatabaseFlags( const AnsiString& str, Ese::DetachDatabaseFlags& value )
        {
            return TryParseDetachDatabaseFlags( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Ese::DetachDatabaseFlags& value )
    {
        return Ese::TryParseDetachDatabaseFlags( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Ese::DetachDatabaseFlags, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Ese::ParseDetachDatabaseFlags( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Ese::DetachDatabaseFlags, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Ese::ParseDetachDatabaseFlags( str );
    }

    // =========================================================================
    // CreateDatabaseFlags
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Ese::CreateDatabaseFlags value );
    HCC_EXPORT WideString ToWideString( Ese::CreateDatabaseFlags value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Ese::CreateDatabaseFlags value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Ese::CreateDatabaseFlags value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Ese
    {
        HCC_EXPORT Ese::CreateDatabaseFlags ParseCreateDatabaseFlags( const WideString& str );
        HCC_EXPORT Ese::CreateDatabaseFlags ParseCreateDatabaseFlags( const WideString& str, Ese::CreateDatabaseFlags defaultResult );
        HCC_EXPORT bool TryParseCreateDatabaseFlags( const WideString& str, Ese::CreateDatabaseFlags& value );

        inline Ese::CreateDatabaseFlags ParseCreateDatabaseFlags( const AnsiString& str )
        {
            return ParseCreateDatabaseFlags( ToWideString( str ) );
        }
        inline Ese::CreateDatabaseFlags ParseCreateDatabaseFlags( const AnsiString& str, Ese::CreateDatabaseFlags defaultResult )
        {
            return ParseCreateDatabaseFlags( ToWideString( str ), defaultResult );
        }
        inline bool TryParseCreateDatabaseFlags( const AnsiString& str, Ese::CreateDatabaseFlags& value )
        {
            return TryParseCreateDatabaseFlags( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Ese::CreateDatabaseFlags& value )
    {
        return Ese::TryParseCreateDatabaseFlags( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Ese::CreateDatabaseFlags, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Ese::ParseCreateDatabaseFlags( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Ese::CreateDatabaseFlags, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Ese::ParseCreateDatabaseFlags( str );
    }

    // =========================================================================
    // OpenDatabaseFlags
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Ese::OpenDatabaseFlags value );
    HCC_EXPORT WideString ToWideString( Ese::OpenDatabaseFlags value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Ese::OpenDatabaseFlags value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Ese::OpenDatabaseFlags value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Ese
    {
        HCC_EXPORT Ese::OpenDatabaseFlags ParseOpenDatabaseFlags( const WideString& str );
        HCC_EXPORT Ese::OpenDatabaseFlags ParseOpenDatabaseFlags( const WideString& str, Ese::OpenDatabaseFlags defaultResult );
        HCC_EXPORT bool TryParseOpenDatabaseFlags( const WideString& str, Ese::OpenDatabaseFlags& value );

        inline Ese::OpenDatabaseFlags ParseOpenDatabaseFlags( const AnsiString& str )
        {
            return ParseOpenDatabaseFlags( ToWideString( str ) );
        }
        inline Ese::OpenDatabaseFlags ParseOpenDatabaseFlags( const AnsiString& str, Ese::OpenDatabaseFlags defaultResult )
        {
            return ParseOpenDatabaseFlags( ToWideString( str ), defaultResult );
        }
        inline bool TryParseOpenDatabaseFlags( const AnsiString& str, Ese::OpenDatabaseFlags& value )
        {
            return TryParseOpenDatabaseFlags( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Ese::OpenDatabaseFlags& value )
    {
        return Ese::TryParseOpenDatabaseFlags( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Ese::OpenDatabaseFlags, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Ese::ParseOpenDatabaseFlags( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Ese::OpenDatabaseFlags, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Ese::ParseOpenDatabaseFlags( str );
    }

    // =========================================================================
    // InitFlags
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Ese::InitFlags value );
    HCC_EXPORT WideString ToWideString( Ese::InitFlags value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Ese::InitFlags value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Ese::InitFlags value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Ese
    {
        HCC_EXPORT Ese::InitFlags ParseInitFlags( const WideString& str );
        HCC_EXPORT Ese::InitFlags ParseInitFlags( const WideString& str, Ese::InitFlags defaultResult );
        HCC_EXPORT bool TryParseInitFlags( const WideString& str, Ese::InitFlags& value );

        inline Ese::InitFlags ParseInitFlags( const AnsiString& str )
        {
            return ParseInitFlags( ToWideString( str ) );
        }
        inline Ese::InitFlags ParseInitFlags( const AnsiString& str, Ese::InitFlags defaultResult )
        {
            return ParseInitFlags( ToWideString( str ), defaultResult );
        }
        inline bool TryParseInitFlags( const AnsiString& str, Ese::InitFlags& value )
        {
            return TryParseInitFlags( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Ese::InitFlags& value )
    {
        return Ese::TryParseInitFlags( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Ese::InitFlags, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Ese::ParseInitFlags( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Ese::InitFlags, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Ese::ParseInitFlags( str );
    }

    // =========================================================================
    // OnlineDefragFlags
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Ese::OnlineDefragFlags value );
    HCC_EXPORT WideString ToWideString( Ese::OnlineDefragFlags value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Ese::OnlineDefragFlags value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Ese::OnlineDefragFlags value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Ese
    {
        HCC_EXPORT Ese::OnlineDefragFlags ParseOnlineDefragFlags( const WideString& str );
        HCC_EXPORT Ese::OnlineDefragFlags ParseOnlineDefragFlags( const WideString& str, Ese::OnlineDefragFlags defaultResult );
        HCC_EXPORT bool TryParseOnlineDefragFlags( const WideString& str, Ese::OnlineDefragFlags& value );

        inline Ese::OnlineDefragFlags ParseOnlineDefragFlags( const AnsiString& str )
        {
            return ParseOnlineDefragFlags( ToWideString( str ) );
        }
        inline Ese::OnlineDefragFlags ParseOnlineDefragFlags( const AnsiString& str, Ese::OnlineDefragFlags defaultResult )
        {
            return ParseOnlineDefragFlags( ToWideString( str ), defaultResult );
        }
        inline bool TryParseOnlineDefragFlags( const AnsiString& str, Ese::OnlineDefragFlags& value )
        {
            return TryParseOnlineDefragFlags( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Ese::OnlineDefragFlags& value )
    {
        return Ese::TryParseOnlineDefragFlags( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Ese::OnlineDefragFlags, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Ese::ParseOnlineDefragFlags( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Ese::OnlineDefragFlags, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Ese::ParseOnlineDefragFlags( str );
    }

    // =========================================================================
    // BackupFlags
    // =========================================================================
    HCC_EXPORT WideString ToWideString( Ese::BackupFlags value );
    HCC_EXPORT WideString ToWideString( Ese::BackupFlags value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Ese::BackupFlags value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Ese::BackupFlags value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }

    namespace Ese
    {
        HCC_EXPORT Ese::BackupFlags ParseBackupFlags( const WideString& str );
        HCC_EXPORT Ese::BackupFlags ParseBackupFlags( const WideString& str, Ese::BackupFlags defaultResult );
        HCC_EXPORT bool TryParseBackupFlags( const WideString& str, Ese::BackupFlags& value );

        inline Ese::BackupFlags ParseBackupFlags( const AnsiString& str )
        {
            return ParseBackupFlags( ToWideString( str ) );
        }
        inline Ese::BackupFlags ParseBackupFlags( const AnsiString& str, Ese::BackupFlags defaultResult )
        {
            return ParseBackupFlags( ToWideString( str ), defaultResult );
        }
        inline bool TryParseBackupFlags( const AnsiString& str, Ese::BackupFlags& value )
        {
            return TryParseBackupFlags( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Ese::BackupFlags& value )
    {
        return Ese::TryParseBackupFlags( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Ese::BackupFlags, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Ese::ParseBackupFlags( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Ese::BackupFlags, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
    inline T Parse( const CharT* str )
    {
        return Ese::ParseBackupFlags( str );
    }

    namespace Internal
    {
        // =========================================================================
        // EseFormatterImpl
        // =========================================================================
        template<typename EnumT, typename CharT>
        struct EseFormatterImpl
        {
            std::formatter<std::basic_string_view<CharT>, CharT> viewFormatter;
            constexpr auto parse( std::basic_format_parse_context<CharT>& ctx )
            {
                return viewFormatter.parse( ctx );
            }

            template <typename FormatContext>
            auto format( EnumT value, FormatContext& ctx )
            {
                if constexpr ( sizeof( CharT ) == 2 )
                {
                    auto str = ToWideString( value );
                    std::basic_string_view<CharT> view( str.data( ), str.size( ) );
                    return viewFormatter.format( view, ctx );
                }
                else
                {
                    auto str = ToAnsiString( value );
                    std::basic_string_view<CharT> view( str.data( ), str.size( ) );
                    return viewFormatter.format( view, ctx );
                }
            }
        };
    }
}

namespace std
{
    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Ese::ColumnType, CharT> : public Harlinn::Common::Core::Internal::EseFormatterImpl<Harlinn::Common::Core::Ese::ColumnType,CharT>
    {
    };

    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Ese::ColumnFlags, CharT> : public Harlinn::Common::Core::Internal::EseFormatterImpl<Harlinn::Common::Core::Ese::ColumnFlags, CharT>
    {
    };

    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Ese::IndexFlags, CharT> : public Harlinn::Common::Core::Internal::EseFormatterImpl<Harlinn::Common::Core::Ese::IndexFlags, CharT>
    {
    };

    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Ese::RetrieveFlags, CharT> : public Harlinn::Common::Core::Internal::EseFormatterImpl<Harlinn::Common::Core::Ese::RetrieveFlags, CharT>
    {
    };

    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Ese::SetFlags, CharT> : public Harlinn::Common::Core::Internal::EseFormatterImpl<Harlinn::Common::Core::Ese::SetFlags, CharT>
    {
    };

    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Ese::ColumnInfoFlags, CharT> : public Harlinn::Common::Core::Internal::EseFormatterImpl<Harlinn::Common::Core::Ese::ColumnInfoFlags, CharT>
    {
    };

    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Ese::PrepareUpdateOptions, CharT> : public Harlinn::Common::Core::Internal::EseFormatterImpl<Harlinn::Common::Core::Ese::PrepareUpdateOptions, CharT>
    {
    };

    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Ese::KeyFlags, CharT> : public Harlinn::Common::Core::Internal::EseFormatterImpl<Harlinn::Common::Core::Ese::KeyFlags, CharT>
    {
    };

    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Ese::SeekFlags, CharT> : public Harlinn::Common::Core::Internal::EseFormatterImpl<Harlinn::Common::Core::Ese::SeekFlags, CharT>
    {
    };

    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Ese::IndexRangeFlags, CharT> : public Harlinn::Common::Core::Internal::EseFormatterImpl<Harlinn::Common::Core::Ese::IndexRangeFlags, CharT>
    {
    };
    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Ese::SetCurrentIndexFlags, CharT> : public Harlinn::Common::Core::Internal::EseFormatterImpl<Harlinn::Common::Core::Ese::SetCurrentIndexFlags, CharT>
    {
    };
    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Ese::TableOptions, CharT> : public Harlinn::Common::Core::Internal::EseFormatterImpl<Harlinn::Common::Core::Ese::TableOptions, CharT>
    {
    };
    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Ese::ObjectFlags, CharT> : public Harlinn::Common::Core::Internal::EseFormatterImpl<Harlinn::Common::Core::Ese::ObjectFlags, CharT>
    {
    };
    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Ese::SequentialFlags, CharT> : public Harlinn::Common::Core::Internal::EseFormatterImpl<Harlinn::Common::Core::Ese::SequentialFlags, CharT>
    {
    };
    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Ese::ExceptionAction, CharT> : public Harlinn::Common::Core::Internal::EseFormatterImpl<Harlinn::Common::Core::Ese::ExceptionAction, CharT>
    {
    };
    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Ese::OpenTableFlags, CharT> : public Harlinn::Common::Core::Internal::EseFormatterImpl<Harlinn::Common::Core::Ese::OpenTableFlags, CharT>
    {
    };
    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Ese::TransactionFlags, CharT> : public Harlinn::Common::Core::Internal::EseFormatterImpl<Harlinn::Common::Core::Ese::TransactionFlags, CharT>
    {
    };
    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Ese::AttachDatabaseFlags, CharT> : public Harlinn::Common::Core::Internal::EseFormatterImpl<Harlinn::Common::Core::Ese::AttachDatabaseFlags, CharT>
    {
    };
    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Ese::DetachDatabaseFlags, CharT> : public Harlinn::Common::Core::Internal::EseFormatterImpl<Harlinn::Common::Core::Ese::DetachDatabaseFlags, CharT>
    {
    };
    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Ese::CreateDatabaseFlags, CharT> : public Harlinn::Common::Core::Internal::EseFormatterImpl<Harlinn::Common::Core::Ese::CreateDatabaseFlags, CharT>
    {
    };
    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Ese::OpenDatabaseFlags, CharT> : public Harlinn::Common::Core::Internal::EseFormatterImpl<Harlinn::Common::Core::Ese::OpenDatabaseFlags, CharT>
    {
    };
    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Ese::InitFlags, CharT> : public Harlinn::Common::Core::Internal::EseFormatterImpl<Harlinn::Common::Core::Ese::InitFlags, CharT>
    {
    };
    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Ese::OnlineDefragFlags, CharT> : public Harlinn::Common::Core::Internal::EseFormatterImpl<Harlinn::Common::Core::Ese::OnlineDefragFlags, CharT>
    {
    };
    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Ese::BackupFlags, CharT> : public Harlinn::Common::Core::Internal::EseFormatterImpl<Harlinn::Common::Core::Ese::BackupFlags, CharT>
    {
    };

}

#endif
