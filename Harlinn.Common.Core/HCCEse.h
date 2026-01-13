#pragma once
#ifndef __HCCESENT_H__
#define __HCCESENT_H__
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
    concept DirectType = ( ( std::is_integral_v<T> && !std::is_same_v<bool, T> ) ||
        std::is_floating_point_v<T> ||
        std::is_same_v<TimeSpan, T> ||
        std::is_same_v<Currency, T> ||
        std::is_same_v<Guid, T> ||
        std::is_same_v<GUID, T> ||
        std::is_same_v<boost::uuids::uuid, T> );

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




    /// <summary>
    /// Describes the table the column types.
    /// </summary>
    enum class ColumnType
    {
        None = JET_coltypNil,
        /// <summary>
        /// A column type that allows three values: True, 
        /// False, or NULL. This type of column is one 
        /// byte in length and is a fixed size. False sorts 
        /// before True.
        /// </summary>
        Boolean = JET_coltypBit,
        /// <summary>
        /// A 1-byte unsigned integer that can take on values 
        /// between 0 (zero) and 255.
        /// </summary>
        Byte = JET_coltypUnsignedByte,
        /// <summary>
        /// A 2-byte signed integer that can take on values 
        /// between -32768 and 32767. Negative values sort 
        /// before positive values.
        /// </summary>
        Short = JET_coltypShort,
        /// <summary>
        /// A 4-byte signed integer that can take on values 
        /// between - 2147483648 and 2147483647. Negative 
        /// values sort before positive values.
        /// </summary>
        Long = JET_coltypLong,
        /// <summary>
        /// An 8-byte signed integer that can take on values 
        /// between - 9223372036854775808 and 9223372036854775807. 
        /// Negative values sort before positive values. 
        /// This column type is identical to the variant currency type. 
        /// </summary>
        Currency = JET_coltypCurrency,
        /// <summary>
        /// A single-precision (4-byte) floating point number.
        /// </summary>
        Single = JET_coltypIEEESingle,
        /// <summary>
        /// A double-precision (8-byte) floating point number.
        /// </summary>
        Double = JET_coltypIEEEDouble,
        /// <summary>
        /// A double-precision (8-byte) floating point number 
        /// that represents a date in fractional days since 
        /// the year 1900. This column type is identical to 
        /// the variant date type.
        /// </summary>
        DateTime = JET_coltypDateTime,
        /// <summary>
        /// <para>
        /// A fixed or variable length, raw binary column 
        /// that can be up to 255 bytes in length.
        /// </para>
        /// <para>
        /// This column type can be used to implement a 
        /// GUID if configured as a fixed length, 16-byte 
        /// binary column. The only caveat is that the 
        /// relative ordering of values in an index over 
        /// such a column will not match the relative 
        /// ordering of the standard registry-string 
        /// rendering of a GUID
        /// </para>
        /// </summary>
        Binary = JET_coltypBinary,
        /// <summary>
        /// <para>
        /// A fixed or variable length text column that 
        /// can be up to 255 ASCII characters in length 
        /// or 127 Unicode characters in length.
        /// </para>
        /// <para>
        /// All strings are stored as a counted number of 
        /// characters. The strings need not be null terminated. 
        /// Further, it is not necessary for the count to 
        /// include a null terminator. Finally, embedded 
        /// null characters can be stored.
        /// </para>
        /// <para>
        /// ASCII strings are always treated as case insensitive 
        /// for sorting and searching purposes. Further, only 
        /// the characters preceding the first null character 
        /// (if any) are considered for sorting and searching.
        /// </para>
        /// <para>
        /// Unicode strings use the Win32 API LCMapString to 
        /// create sort keys that are subsequently used for 
        /// sorting and searching that data. By default, 
        /// Unicode strings are considered to be in the U.S. 
        /// English locale and are sorted and searched using 
        /// the following normalization flags: 
        /// </para>
        /// <list type="bullet">
        /// <item>NORM_IGNORECASE</item>
        /// <item>NORM_IGNOREKANATYPE</item>
        /// <item>NORM_IGNOREWIDTH.</item>
        /// </list>
        /// <para>
        /// In Windows 2000, it is possible to customize these flags 
        /// per index to also include NORM_IGNORENONSPACE. In Windows XP 
        /// and later releases, it is possible to request any combination 
        /// of the following normalization flags per index: 
        /// </para>
        /// <list type="bullet">
        /// <item>LCMAP_SORTKEY</item>
        /// <item>LCMAP_BYTEREV</item>
        /// <item>NORM_IGNORECASE</item>
        /// <item>NORM_IGNORENONSPACE</item>
        /// <item>NORM_IGNORESYMBOLS</item>
        /// <item>NORM_IGNOREKANATYPE</item>
        /// <item>NORM_IGNOREWIDTH</item>
        /// <item>SORT_STRINGSORT</item>
        /// </list>
        /// <para>
        /// In all releases, it is possible to customize the locale per index. 
        /// Any locale may be used as long as the appropriate language pack has 
        /// been installed on the machine. Finally, any null characters 
        /// encountered in a Unicode string are completely ignored.
        /// </para>
        /// </summary>
        Text = JET_coltypText,
        /// <summary>
        /// A fixed or variable length, raw binary column that can be up to 
        /// 2147483647 bytes in length. This type is considered to be a Long 
        /// Value. A Long Value is special because it can be large and because 
        /// it can be accessed as a stream. This type is otherwise identical 
        /// to ColumnType::Binary.
        /// </summary>
        LongBinary = JET_coltypLongBinary,
        /// <summary>
        /// A fixed or variable length, text column that can be up to 2147483647 
        /// ASCII characters in length or 1073741823 Unicode characters in length. 
        /// This type is considered to be a Long Value. A Long Value is special 
        /// because it can be large and because it can be accessed as a stream. 
        /// This type is otherwise identical to ColumnType::Binary.
        /// </summary>
        LongText = JET_coltypLongText,
        /// <summary>
        /// This column type is obsolete.
        /// </summary>
        SLV = JET_coltypSLV,
        /// <summary>
        /// <para>
        /// A 4-byte unsigned integer that can take on values between 0 (zero) and 4294967295.
        /// </para>
        /// <para>
        /// Windows Vista and Windows Server 2008:  This column type is supported on 
        /// Windows Vista, Windows Server 2008 and later releases.
        /// </para>
        /// </summary>
        UnsignedLong = JET_coltypUnsignedLong,
        /// <summary>
        /// <para>
        /// An 8-byte signed integer that can take on values between 
        /// -9223372036854775808 and 9223372036854775807. Negative 
        /// values sort before positive values.
        /// </para>
        /// <para>
        /// Windows Vista and Windows Server 2008:  This column type is 
        /// supported on Windows Vista, Windows Server 2008 and later releases.
        /// </para>
        /// </summary>
        LongLong = JET_coltypLongLong,
        /// <summary>
        /// <para>
        /// A fixed length 16 byte binary column that natively represents the 
        /// GUID data type. GUID column values sort in the same way that those 
        /// values would sort as strings when in standard form 
        /// (i.e. {4999b5c0-7657-42d9-bdc1-4b779784e013}).
        /// </para>
        /// <para>
        /// Windows Vista and Windows Server 2008:  This column type is supported 
        /// on Windows Vista, Windows Server 2008 and later releases.
        /// </para>
        /// </summary>
        Guid = JET_coltypGUID,
        /// <summary>
        /// <para>
        /// A 2-byte unsigned integer that can take on values between 0 and 65535.
        /// </para>
        /// <para>
        /// Windows Vista and Windows Server 2008:  This column type is supported 
        /// on Windows Vista, Windows Server 2008 and later releases.
        /// </para>
        /// </summary>
        UnsignedShort = JET_coltypUnsignedShort,
        /// <summary>
        /// <para>
        /// An 8-byte unsigned integer
        /// </para>
        /// <para>
        /// This column type is supported on Windows 10 and later.
        /// </para>
        /// </summary>
        UnsignedLongLong = JET_coltypUnsignedLongLong
    };

    /// <summary>
    /// The flags that describe the column. (grbit) 
    /// </summary>
    enum class ColumnFlags : int
    {
        None = 0,
        /// <summary>
        /// <para>
        /// The column will be fixed. It will always use the same amount of space in 
        /// a row, regardless of how much data is being stored in the column. 
        /// </para>
        /// <para>
        /// Fixed cannot be combined with Tagged or used with long values ( that is 
        /// ColumnType::LongText and ColumnType::LongBinary ).
        /// </para>
        /// </summary>
        Fixed = JET_bitColumnFixed,
        /// <summary>
        /// The column will be tagged. Tagged columns do not take up any space in the 
        /// database if they do not contain data. This bit cannot be combined with Fixed
        /// </summary>
        Tagged = JET_bitColumnTagged,
        /// <summary>
        /// The column must never be set to a NULL value
        /// </summary>
        NotNULL = JET_bitColumnNotNULL,
        /// <summary>
        /// <para>
        /// The column is a version column that specifies the version of the row.
        /// The value of this column starts at zero and will be automatically 
        /// incremented for each update on the row.
        /// </para>
        /// <para>
        /// This bit can only be applied to ColumnType::Long columns. This bit 
        /// cannot be used with ColumnFlags::Autoincrement, ColumnFlags::EscrowUpdate, 
        /// or ColumnFlags::Tagged.
        /// </para>
        /// </summary>
        Version = JET_bitColumnVersion,
        /// </summary>
        /// <para>
        /// The column will automatically be incremented. 
        /// The number is an increasing number, and is guaranteed to be unique within a table. 
        /// </para>
        /// <para>
        /// The numbers, however, might not be continuous. 
        /// For example, if five rows are inserted into a table, the "autoincrement" column 
        /// could contain the values { 1, 2, 6, 7, 8 }. This bit can only be used on columns 
        /// of type ColumnType::Long or ColumnType::Currency.
        /// </para>
        /// </summary>
        Autoincrement = JET_bitColumnAutoincrement,
        /// <summary>
        /// This bit is valid only on calls to JetGetColumnInfo.
        /// </summary>
        Updatable = JET_bitColumnUpdatable,
        /// <summary>
        /// This bit is valid only on calls to JetOpenTable.
        /// </summary>
        TemporaryTableKey = JET_bitColumnTTKey,
        /// <summary>
        /// This bit is valid only on calls to JetOpenTempTable.
        /// </summary>
        TemporaryTableDescending = JET_bitColumnTTDescending,
        /// <summary>
        /// <para>
        /// The column can be multi-valued. A multi-valued column can 
        /// have zero, one, or more values associated with it. The various 
        /// values in a multi-valued column are identified by a number 
        /// called the itagSequence member.
        /// </para>
        /// <para>
        /// Multi-valued columns must be tagged columns; that is, they 
        /// cannot be fixed-length or variable-length columns.
        /// </para>
        /// </summary>
        MultiValued = JET_bitColumnMultiValued,
        /// <summary>
        /// <para>
        /// Specifies that a column is an escrow update column. An escrow 
        /// update column can be updated concurrently by different sessions 
        /// with Table::EscrowUpdate and will maintain transactional consistency. 
        /// An escrow update column must also meet the following conditions:
        /// </para>
        /// <list type="bullet">
        /// <item>
        /// Can only be created when the table is empty.
        /// </item>
        /// <item>
        /// Must be of type ColumnType::Long
        /// </item>
        /// <item>
        /// Must have a default value.
        /// </item>
        /// <item>
        /// cannot be used in conjunction with ColumnFlags::Tagged, 
        /// ColumnFlags::Version or ColumnFlags::Autoincrement.
        /// </item>
        /// </list>
        /// </summary>
        EscrowUpdate = JET_bitColumnEscrowUpdate,
        /// <summary>
        /// The column will be created in an without version information. This means 
        /// that other transactions that attempt to add a column with the same name 
        /// will fail.
        /// </summary>
        Unversioned = JET_bitColumnUnversioned,
        /// <summary>
        /// For retrieve column info of outer join where no match from the inner table.
        /// </summary>
        MaybeNull = JET_bitColumnMaybeNull,
        /// <summary>
        /// Use ColumnFlags::DeleteOnZero instead of ColumnFlags::Finalize. 
        /// ColumnFlags::Finalize indicates that a column can be finalized. 
        /// When a column that can be finalized is an escrow update column 
        /// that reaches zero, the row will be deleted. A column that can 
        /// be finalized must be an escrow update column. ColumnFlags::Finalize 
        /// cannot be used with ColumnFlags::UserDefinedDefault.
        /// </summary>
        Finalize = JET_bitColumnFinalize,
        /// <summary>
        /// The default value for a column will be provided by a callback 
        /// function. A column that has a user-defined default must be a 
        /// tagged column. Specifying ColumnFlags::UserDefinedDefault means that 
        /// defaultValueBuffer must point to a JET_USERDEFINEDDEFAULT structure, and 
        /// defaultValueBufferSize must be set to sizeof( JET_USERDEFINEDDEFAULT ).
        /// 
        /// ColumnFlags::UserDefinedDefault cannot be used in conjunction with ColumnFlags::Fixed, 
        /// ColumnFlags::NotNULL, ColumnFlags::Version, ColumnFlags::Autoincrement, ColumnFlags::Updatable, 
        /// ColumnFlags::EscrowUpdate, ColumnFlags::Finalize, ColumnFlags::DeleteOnZero, or ColumnFlags::MaybeNull.
        /// </summary>
        UserDefinedDefault = JET_bitColumnUserDefinedDefault,
        /// <summary>
        /// When the escrow-update column reaches a value of zero (after all versions are resolve),
        /// the record will be deleted. A common use for a column that can be finalized is to use
        /// it as a reference count field, and when the field reaches zero the record gets deleted.
        /// A Delete-on-zero column must be an escrow update / ColumnFlags::EscrowUpdate column.
        /// ColumnFlags::DeleteOnZero cannot be used with ColumnFlags::Finalize. ColumnFlags::DeleteOnZero
        /// cannot be used with user defined default columns.
        /// </summary>
        DeleteOnZero = JET_bitColumnDeleteOnZero,
        /// <summary>
        // The data in the column can be compressed
        /// </summary>
        Compressed = JET_bitColumnCompressed
    };
    
    HCC_DEFINE_ENUM_FLAG_OPERATORS( ColumnFlags, int );

    /// <summary>
    /// Describes a column to create in a database.
    /// </summary>
    class ColumnCreate : public JET_COLUMNCREATE_W
    {
        using Base = JET_COLUMNCREATE_W;
    public:
        ColumnCreate()
            : Base{ sizeof( JET_COLUMNCREATE_W ),0, }
        {
        }
    };


    /// <summary>
    /// Index flag values
    /// </summary>
    enum class IndexFlags : int
    {
        /// <summary>
        /// No flags are set.
        /// </summary>
        None = 0,
        /// <summary>
        /// Duplicate index entries (keys) are not allowed. This is 
        /// enforced when Table::Update is called.
        /// </summary>
        Unique = JET_bitIndexUnique,
        /// <summary>
        /// The index is a primary (clustered) index. Every table must 
        /// have exactly one primary index. If no primary index is 
        /// explicitly defined over a table, the database engine will 
        /// create its own primary index.
        /// </summary>
        Primary = JET_bitIndexPrimary,
        /// <summary>
        /// None of the columns over which the index is created can 
        /// contain a NULL value.
        /// </summary>
        DisallowNull = JET_bitIndexDisallowNull,
        /// <summary>
        /// Do not add an index entry for a row if all of the columns 
        /// being indexed are NULL.
        /// </summary>
        IgnoreNull = JET_bitIndexIgnoreNull,
        /// <summary>
        /// Do not add an index entry for a row if any of the columns 
        /// being indexed are NULL.
        /// </summary>
        IgnoreAnyNull = JET_bitIndexIgnoreAnyNull,
        /// <summary>
        /// Do not add an index entry for a row if the first column being indexed is NULL.
        /// </summary>
        IgnoreFirstNull = JET_bitIndexIgnoreFirstNull,
        /// <summary>
        /// <para>
        /// Index operations will be logged lazily.
        /// </para>
        /// <para>
        /// IndexFlags::LazyFlush does not affect the laziness of data 
        /// updates. If the indexing operation is interrupted by process 
        /// termination, Soft Recovery will still be able to able to get 
        /// the database to a consistent state, but the index might not 
        /// be present.
        /// </para>
        /// </summary>
        LazyFlush = JET_bitIndexLazyFlush,
        /// <summary>
        /// <para>
        /// Do not attempt to build the index, because all entries would 
        /// evaluate to NULL. grbit must also specify IndexFlags::IgnoreAnyNull 
        /// when IndexFlags::IndexEmpty is passed. This is a performance enhancement. 
        /// </para>
        /// <para>
        /// For example, if a new column is added to a table, an index is created 
        /// over this newly added column, and all the records in the table are 
        /// scanned even though they are not added to the index. Specifying 
        /// IndexFlags::IndexEmpty skips the scanning of the table, which could 
        /// potentially take a long time.
        /// </para>
        /// </summary>
        Empty = JET_bitIndexEmpty,
        /// <summary>
        /// Causes index creation to be visible to other transactions. Typically 
        /// a session in a transaction will not be able to see an index creation 
        /// operation in another session. This flag can be useful if another 
        /// transaction is likely to create the same index. The second index-create 
        /// will fail instead of potentially causing many unnecessary database 
        /// operations. The second transaction might not be able to use the index 
        /// immediately. The index creation operation has to complete before it 
        /// is usable. The session must not currently be in a transaction to create 
        /// an index without version information.
        /// </summary>
        Unversioned = JET_bitIndexUnversioned,
        /// <summary>
        /// Specifying this flag causes NULL values to be sorted after data for 
        /// all columns in the index.
        /// </summary>
        SortNullsHigh = JET_bitIndexSortNullsHigh,
        /// <summary>
        /// Specifying this flag affects the interpretation of the lcid/pidxunicde 
        /// union field in the JET_UNICODEINDEX structure. Setting the bit means 
        /// that the pidxunicode field actually points to a JET_UNICODEINDEX 
        /// structure. IndexFlags::Unicode is not required in order to index 
        /// Unicode data. It is only used to customize the normalization of 
        /// Unicode data.
        /// </summary>
        Unicode = JET_bitIndexUnicode,
        /// <summary>
        /// <para>
        /// Specifies that the index is a tuple index.
        /// </para>
        /// </summary>
        Tuples = JET_bitIndexTuples,
        /// <summary>
        /// Specifying this flag affects the interpretation of the cbVarSegMac/ptuplelimits 
        /// union field in the JET_INDEXCREATE structure. Setting this bit means that the 
        /// ptuplelimits field actually points to a JET_TUPLELIMITS structure to allow 
        /// custom tuple index limits (implies IndexFlags::Tuples).
        /// </summary>
        TupleLimits = JET_bitIndexTupleLimits,
        /// <summary>
        /// Specifying this flag for an index that has more than one key column that 
        /// is a multivalued column will result in an index entry being created for 
        /// each result of a cross product of all the values in those key columns. 
        /// Otherwise, the index would only have one entry for each multi-value in 
        /// the most significant key column that is a multivalued column and each 
        /// of those index entries would use the first multi-value from any other 
        /// key columns that are multivalued columns.
        /// </summary>
        CrossProduct = JET_bitIndexCrossProduct,
        /// <summary>
        /// Specifying this flag will cause the index to use the maximum key size 
        /// specified in the cbKeyMost field in the JET_INDEXCREATE structure. Otherwise, 
        /// the index will use JET_cbKeyMost (255) as its maximum key size.
        /// </summary>
        KeyMost = JET_bitIndexKeyMost,
        /// <summary>
        /// Specifying this flag will cause any update to the index that would 
        /// result in a truncated key to fail with JET_errKeyTruncated. 
        /// Otherwise, keys will be silently truncated. 
        /// </summary>
        DisallowTruncation = JET_bitIndexDisallowTruncation,
        /// <summary>
        /// Specifying this flag will cause an update the index over multiple 
        /// multivalued columns but only with values of same itagSequence.
        /// </summary>
        NestedTable = JET_bitIndexNestedTable,
        /// <summary>
        /// Index over GUID column according to .Net GUID sort order
        /// </summary>
        DotNetGuid = 0x00040000
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( IndexFlags, int );

    /// <summary>
    /// Flag values used for the grbit field of the JET_RETRIEVECOLUMN
    /// and the retrieveFlags parameter of the Table::RetrieveColumn
    /// member function.
    /// </summary>
    enum class RetrieveFlags : int
    {
        None = 0,
        /// <summary>
        /// This flag causes retrieve column to retrieve the 
        /// modified value instead of the original value. If 
        /// the value has not been modified, then the original 
        /// value is retrieved. In this way, a value that has 
        /// not yet been inserted or updated may be retrieved 
        /// during the operation of inserting or updating a record.
        /// </summary>
        Copy = JET_bitRetrieveCopy,
        /// <summary>
        /// This option is used to retrieve column values from 
        /// the index, if possible, without accessing the record. 
        /// In this way, unnecessary loading of records can be 
        /// avoided when needed data is available from index 
        /// entries themselves. In cases where the original column 
        /// value cannot be retrieved from the index, because of 
        /// irreversible transformations or data truncation, the 
        /// record will be accessed and the data retrieved as 
        /// normal. This is a performance option and should only 
        /// be specified when it is likely that the column value 
        /// can be retrieved from the index. This option should 
        /// not be specified if the current index is the clustered 
        /// index, since the index entries for the clustered, 
        /// or primary, index are the records themselves. This 
        /// bit cannot be set if FromPrimaryBookmark is also set.
        /// </summary>
        FromIndex = JET_bitRetrieveFromIndex,
        /// <summary>
        /// This option is used to retrieve column values from 
        /// the index bookmark, and may differ from the index 
        /// value when a column appears both in the primary index 
        /// and the current index. This option should not be 
        /// specified if the current index is the clustered, 
        /// or primary, index. This bit cannot be set if 
        /// FromIndex is also set.
        /// </summary>
        FromPrimaryBookmark = JET_bitRetrieveFromPrimaryBookmark,
        /// <summary>
        /// This option is used to retrieve the sequence number 
        /// of a multi-valued column value in pretinfo->itagSequence. 
        /// The itagSequence field is commonly an input for 
        /// retrieving multi-valued column values from a record. 
        /// However, when retrieving values from an index, it is 
        /// also possible to associate the index entry with a 
        /// particular sequence number and retrieve this sequence 
        /// number as well. Retrieving the sequence number can 
        /// be a costly operation and should only be done if necessary.
        /// </summary>
        Tag = JET_bitRetrieveTag,
        /// <summary>
        /// This option is used to retrieve multi-valued column 
        /// NULL values. If this option is not specified, 
        /// multi-valued column NULL values will automatically 
        /// be skipped.
        /// </summary>
        Null = JET_bitRetrieveNull,
        /// <summary>
        /// This option affects only multi-valued columns and 
        /// causes a NULL value to be returned when the requested 
        /// sequence number is 1 and there are no set values for 
        /// the column in the record.
        /// </summary>
        IgnoreDefault = JET_bitRetrieveIgnoreDefault,
        /// <summary>
        /// This flag will allow the retrieval of a tuple segment 
        /// of the index. This bit must be specified with 
        /// FromIndex.
        /// </summary>
        Tuple = JET_bitRetrieveTuple
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( RetrieveFlags, int );

    /// <summary>
    /// Flags used for the flags parameter Table::SetColumn function
    /// and for the grbit field of the JET_SETCOLUMN structure.
    /// </summary>
    enum class SetFlags : int
    {
        None = 0,
        /// <summary>
        /// This option is used to append data to a column of type 
        /// ColumnType::LongText or ColumnType::LongBinary. 
        /// The same behavior can be achieved by determining the size 
        /// of the existing long value and specifying ibLongValue in 
        /// psetinfo. However, it's simpler to use this AppendLV since 
        /// knowing the size of the existing column value is not necessary.
        /// </summary>
        AppendLV = JET_bitSetAppendLV,
        /// <summary>
        /// This option is used replace the existing long value with 
        /// the newly provided data. When this option is used, it is 
        /// as though the existing long value has been set to 0 (zero) 
        /// length prior to setting the new data.
        /// </summary>
        OverwriteLV = JET_bitSetOverwriteLV,
        /// <summary>
        /// This option is only applicable for tagged, sparse or 
        /// multi-valued columns. It causes the column to return 
        /// the default column value on subsequent retrieve column 
        /// operations. All existing column values are removed.
        /// </summary>
        RevertToDefaultValue = JET_bitSetRevertToDefaultValue,
        /// <summary>
        /// This option is used to force a long value, columns of type 
        /// ColumnType::LongText or ColumnType::LongBinary, to 
        /// be stored separately from the remainder of record data. 
        /// This occurs normally when the size of the long value 
        /// prevents it from being stored with remaining record data. 
        /// However, this option can be used to force the long value 
        /// to be stored separately. Note that long values four bytes 
        /// in size of smaller cannot be forced to be separate. 
        /// In such cases, the option is ignored.
        /// </summary>
        SeparateLV = JET_bitSetSeparateLV,
        /// <summary>
        /// This option is used to interpret the input buffer as 
        /// a integer number of bytes to set as the length of 
        /// the long value described by the given columnid and 
        /// if provided, the sequence number in psetinfo->itagSequence. 
        /// If the size given is larger than the existing column value, 
        /// the column will be extended with 0s. If the size is smaller 
        /// than the existing column value then the value will be 
        /// truncated.
        /// </summary>
        SizeLV = JET_bitSetSizeLV,
        /// <summary>
        /// This option is used to enforce that all values in a 
        /// multi-valued column are distinct. This option compares 
        /// the source column data, without any transformations, 
        /// to other existing column values and an error is 
        /// returned if a duplicate is found. If this option is given, 
        /// then AppendLV, OverwriteLV and SizeLV cannot also be given.
        /// </summary>
        UniqueMultiValues = JET_bitSetUniqueMultiValues,
        /// <summary>
        /// This option is used to enforce that all values in a 
        /// multi-valued column are distinct. This option compares 
        /// the key normalized transformation of column data, to 
        /// other similarly transformed existing column values 
        /// and an error is returned if a duplicate is found. If 
        /// this option is given, then AppendLV, OverwriteLV and 
        /// SizeLV cannot also be given.
        /// </summary>
        UniqueNormalizedMultiValues = JET_bitSetUniqueNormalizedMultiValues,
        /// <summary>
        /// This option is used to set a value to zero length. Normally, 
        /// a column value is set to NULL by passing a cbMax of 0 (zero). 
        /// However, for some types, like ColumnType::Text, a column 
        /// value can be 0 (zero) length instead of NULL, and this 
        /// option is used to differentiate between NULL and 
        /// 0 (zero) length.
        /// 
        /// Note: In general, if the column is a fixed - length column, 
        /// this bit is ignored and the column is set to NULL.However, 
        /// if the column is a fixed - length tagged column, the column 
        /// length is set to 0. When the fixed - length tagged column 
        /// is set to 0 length, attempts to retrieve the column with 
        /// will succeed, but the actual length that is returned 
        /// in the cbActual parameter is 0.
        /// </summary>
        ZeroLength = JET_bitSetZeroLength,
        /// <summary>
        /// This option is used to store the entire long value in the record.
        /// </summary>
        IntrinsicLV = JET_bitSetIntrinsicLV,
        /// <summary>
        /// This option is used to attempt data compression when storing 
        /// the data.
        /// </summary>
        Compressed = JET_bitSetCompressed,
        /// <summary>
        /// This option is used to not attempt compression when storing 
        /// the data.
        /// </summary>
        Uncompressed = JET_bitSetUncompressed
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( SetFlags, int );

    /// <summary>
    /// Info levels for retrieving column info.
    /// </summary>
    enum class ColumnInfoLevel : unsigned long
    {
        /// <summary>
        /// pvResult is interpreted as a JET_COLUMNDEF, and the 
        /// fields of the JET_COLUMNDEF structure are filled in 
        /// appropriately. JET_ColInfo and JET_ColInfoByColid 
        /// both retrieve the same information.
        /// </summary>
        Default = JET_ColInfo,
        /// <summary>
        /// pvResult is interpreted as a JET_COLUMNBASE structure. 
        /// This is similar to a JET_COLUMNDEF structure. If this 
        /// function succeeds, the structure is populated with 
        /// appropriate values. If this function fails, the 
        /// structure contains undefined data
        /// </summary>
        Base = JET_ColInfoBase,
        /// <summary>
        /// pvResult is interpreted as a JET_COLUMNDEF, except this 
        /// InfoLevel indicates that the requested column 
        /// ( szColumName) is not the string column name, but a 
        /// pointer to a JET_COLUMNID. Info and InfoByColid both 
        /// retrieve the same information.
        /// </summary>
        ByColid = JET_ColInfoByColid,
        /// <summary>
        /// pvResult is interpreted as a JET_COLUMNLIST structure. 
        /// If this function succeeds, the structure is populated 
        /// with appropriate values. A temporary table is opened 
        /// and is identified by the tableid member of 
        /// JET_COLUMNLIST. The table must be closed with 
        /// JetCloseTable. If this function fails, the structure 
        /// contains undefined data.
        /// </summary>
        List = JET_ColInfoList,
        /// <summary>
        /// pvResult is interpreted as a JET_COLUMNLIST structure. 
        /// If this function succeeds, the structure is populated 
        /// with appropriate values. A temporary table is opened 
        /// and is identified by the tableid member of JET_COLUMNLIST. 
        /// The table must be closed with JetCloseTable. If this 
        /// function fails, the structure contains undefined data.
        /// </summary>
        ListCompact = JET_ColInfoListCompact,
        /// <summary>
        /// Same as List, however the resulting table is sorted 
        /// by columnid, instead of column name.
        /// </summary>
        ListSortColumnId = JET_ColInfoListSortColumnid,
        /// <summary>
        /// Same as InfoBase, pvResult is interpreted as a 
        /// JET_COLUMNBASE, except this InfoLevel indicates that 
        /// requested column ( columName ) is not the string 
        /// column name, but a pointer to a JET_COLUMNID.
        /// </summary>
        BaseByColId = JET_ColInfoBaseByColid,
        /// <summary>
        /// Only return non-derived columns (if the table is 
        /// derived from a template). This value can be logically 
        /// or'd into the InfoLevel, when the base InfoLevel is 
        /// InfoList.
        /// </summary>
        NonDerivedColumnsOnly = JET_ColInfoGrbitNonDerivedColumnsOnly,
        /// <summary>
        /// Only return the column name and columnid of each 
        /// column. This value can be logically or'd into 
        /// the InfoLevel, when the base InfoLevel is InfoList.
        /// </summary>
        MinimalInfo = JET_ColInfoGrbitMinimalInfo,
        /// <summary>
        /// Sort returned column list by columnid (default is 
        /// to sort list by column name). This value can be logically 
        /// or'd into the InfoLevel, when the base InfoLevel is 
        /// InfoList.
        /// </summary>
        SortByColumnId = JET_ColInfoGrbitSortByColumnid
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( ColumnInfoLevel, unsigned long );

    /// <summary>
    /// Values for the option parameter of the Table::PrepareUpdate
    /// function.
    /// </summary>
    enum class PrepareUpdateOptions : unsigned long
    {
        /// <summary>
        /// This flag causes PrepareUpdate to cancel the update for this cursor.
        /// </summary>
        Cancel = JET_prepCancel,
        /// <summary>
        /// This flag causes the cursor to prepare for an insert of a new record. 
        /// All the data is initialized to the default state for the record. If 
        /// the table has an auto-increment column, then a new value is assigned 
        /// to this record regardless of whether the update ultimately succeeds, 
        /// fails or is cancelled.
        /// </summary>
        Insert = JET_prepInsert,
        /// <summary>
        /// This flag causes the cursor to prepare for an insert of a copy of 
        /// the existing record. There must be a current record if this option 
        /// is used. The initial state of the new record is copied from the 
        /// current record. Long values that are stored off-record are 
        /// virtually copied.
        /// </summary>
        Copy = JET_prepInsertCopy,
        /// <summary>
        /// This flag causes the cursor to prepare for an insert of the same 
        /// record, and a delete or the original record. It is used in cases 
        /// in which the primary key has changed.
        /// </summary>
        InsertCopyDeleteOriginal = JET_prepInsertCopyDeleteOriginal,
        /// <summary>
        /// This flag causes the cursor to prepare for a replace of the current 
        /// record. If the table has a version column, then the version column 
        /// is set to the next value in its sequence. If this update does not 
        /// complete, then the version value in the record will be unaffected. 
        /// An update lock is taken on the record to prevent other sessions 
        /// from updating this record before this session completes.
        /// </summary>
        Replace = JET_prepReplace,
        /// <summary>
        /// This flag is similar to Replace, but no lock is taken to prevent 
        /// other sessions from updating this record. Instead, this session 
        /// may receive JET_errWriteConflict when it calls Update to 
        /// complete the update.
        /// </summary>
        ReplaceNoLock = JET_prepReplaceNoLock
    };

    /// <summary>
    /// Values for the flags parameter of the Table::MakeKey member funtion.
    /// </summary>
    enum class KeyFlags : unsigned long
    {
        None = 0,
        /// <summary>
        /// <para>
        /// The search key should be constructed in such a way that any key columns that come 
        /// after the current key column are considered to be wildcards. This means that the 
        /// constructed search key can be used to match index entries that have the following:
        /// </para>
        /// <list type="bullet">
        ///    <item>The exact column values provided for this key column and all previous key columns.</item>
        ///    <item>Any column values needed for subsequent key columns.</item>
        /// </list>
        /// <para>
        /// This option should be used when building wildcard search keys to use for finding index 
        /// entries closest to the end of an index.The end of the index is the index entry that is 
        /// found when moving to the last record in that index.The end of the index is not the 
        /// same as the high end of the index, which can change depending on the sort order of 
        /// the key columns in the index.
        /// </para>
        /// <para>
        /// This option is only available on Windows XP and later releases.
        /// </para>
        /// </summary>
        FullColumnEndLimit = JET_bitFullColumnEndLimit,
        /// <summary>
        /// <para>
        /// The search key should be constructed such that any key columns that come after the 
        /// current key column should be considered to be wildcards. This means that the constructed 
        /// search key can be used to match index entries that have the following:
        /// </para>
        /// <list type="bullet">
        ///    <item>The exact column values provided for this key column and all previous key columns.</item>
        ///    <item>Any column values needed for subsequent key columns.</item>
        /// </list>
        /// <para>
        /// This option should be used when building wildcard search keys to use for finding index 
        /// entries closest to the start of an index.The start of the index is the index entry that 
        /// is found when moving to the first record in that index.The start of the index is not the 
        /// same as the low end of the index, which can change depending on the sort order of the 
        /// key columns in the index.
        /// </para>
        /// <para>
        /// This option is only available on Windows XP and later releases.
        /// </para>
        /// </summary>
        FullColumnStartLimit = JET_bitFullColumnStartLimit,

        /// <summary>
        /// If the size of the input buffer is zero and the current key column is a variable 
        /// length column, this option indicates that the input buffer contains a zero length 
        /// value. Otherwise, an input buffer size of zero would indicate a NULL value.
        /// </summary>
        KeyDataZeroLength = JET_bitKeyDataZeroLength,
        /// <summary>
        /// A new search key should be constructed. Any previously existing search key is discarded.
        /// </summary>
        NewKey = JET_bitNewKey,
        /// <summary>
        /// When this option is specified, all other options are ignored, any previously existing 
        /// search key is discarded, and the contents of the input buffer are loaded as the new search key.
        /// </summary>
        NormalizedKey = JET_bitNormalizedKey,
        /// <summary>
        /// <para>
        /// The search key should be constructed such that the current key column is considered to be 
        /// a prefix wildcard and that any key columns that come after the current key column should 
        /// be considered to be wildcards. This means that the constructed search key can be used to 
        /// match index entries that have the following:
        /// </para>
        /// <list type="bullet">
        ///    <item>The exact column values provided for this key column and all previous key columns.</item>
        ///    <item>Any column values needed for subsequent key columns.</item>
        /// </list>
        /// <para>
        /// This option should be used when building wildcard search keys to use for finding index 
        /// entries closest to the end of an index.The end of the index is the index entry that 
        /// is found when moving to the last record in that index.The end of the index is not the 
        /// same as the high end of the index, which can change depending on the sort order of 
        /// the key columns in the index.
        /// </para>
        /// <para>
        /// This option cannot be used when the current key column is not a text column or a 
        /// variable binary column.The operation will fail with JET_errInvalidgrbit if this 
        /// is attempted.
        /// </para>
        /// <para>
        /// This option is only available on Windows XP and later releases.
        /// </para>
        /// </summary>
        PartialColumnEndLimit = JET_bitPartialColumnEndLimit,
        /// <summary>
        /// <para>
        /// This option indicates that the search key should be constructed such that the current 
        /// key column is considered to be a prefix wildcard and that any key columns that come 
        /// after the current key column should be considered to be wildcards.This means that 
        /// the constructed search key can be used to match index entries that have the following:
        /// </para>
        /// <list type="bullet">
        ///    <item>The exact column values provided for this key column and all previous key columns.</item>
        ///    <item>Any column values needed for subsequent key columns.</item>
        /// </list>
        /// <para>
        /// This option should be used when building wildcard search keys to use for finding 
        /// index entries closest to the start of an index.The start of the index is the index 
        /// entry that is found when moving to the first record in that index.The start of 
        /// the index is not the same as the low end of the index, which can change depending 
        /// on the sort order of the key columns in the index.
        /// </para>
        /// <para>
        /// This option cannot be used when the current key column is not a text column or a 
        /// variable binary column.The operation will fail with JET_errInvalidgrbit if this is attempted.
        /// </para>
        /// <para>
        /// This option is only available on Windows XP and later releases.
        /// </para>
        /// </summary>
        PartialColumnStartLimit = JET_bitPartialColumnStartLimit,
        /// <summary>
        /// <para>
        /// This option indicates that the search key should be constructed such that any key 
        /// columns that come after the current key column should be considered to be wildcards.
        /// This means that the constructed search key can be used to match index entries that 
        /// have the following:
        /// </para>
        /// <list type="bullet">
        ///    <item>The exact column values provided for this key column and all previous key columns.</item>
        ///    <item>Any column values needed for subsequent key columns.</item>
        /// </list>
        /// <para>
        /// This option should be used when building wildcard search keys to use for finding 
        /// index entries closest to the end of an index.The end of the index is the index 
        /// entry that is found when moving to the last record in that index.The end of the 
        /// index is not the same as the high end of the index, which can change depending on 
        /// the sort order of the key columns in the index.
        /// </para>
        /// <para>
        /// When this option is specified in combination with JET_bitSubStrLimit and the 
        /// current key column is a text column, this option will be ignored.This behavior 
        /// is intended to allow the type of the current key column to be inferred when building 
        /// the search key.
        /// </para>
        /// <para>
        /// If you want to build a similar search key for the start of an index, a similar call 
        /// to JetMakeKey should be made for the last key column that is not a wildcard, but 
        /// with no wildcard options specified.The search key is then in an appropriate state 
        /// to use for such a search.This is analogous to using JET_bitFullColumnStartLimit, 
        /// except that the search key is not cleanly finished as it is after the use of a wildcard option.
        /// </para>
        /// <para>
        /// This option has been deprecated for Windows XP and later releases in order to address 
        /// this awkward semantic.JET_bitFullColumnStartLimit and JET_bitFullColumnEndLimit 
        /// should be used instead wherever possible.
        /// </para>
        /// </summary>
        StrLimit = JET_bitStrLimit,
        /// <summary>
        /// <para>
        /// This option indicates that the search key should be constructed such that the current 
        /// key column is considered to be a prefix wildcard and that any key columns that come 
        /// after the current key column should be considered to be wildcards.This means that 
        /// the constructed search key can be used to match index entries that have the following :
        /// </para>
        /// <list type="bullet">
        ///    <item>The exact column values provided for all previous key columns.</item>
        ///    <item>The specified column data as a prefix of their column value for the current key column.</item>
        ///    <item>Any column values for subsequent key columns.</item>
        /// </list>
        /// <para>
        /// This option should be used when building wildcard search keys to use for finding index 
        /// entries closest to the end of an index.The end of the index is the index entry that 
        /// is found when moving to the last record in that index.The end of the index is not the 
        /// same as the high end of the index, which can change depending on the sort order of 
        /// the key columns in the index.
        /// </para>
        /// <para>
        /// When this option is specified in combination with StrLimit and the current key column is 
        /// a text column, this option will take precedence. This option is ignored when the current key 
        /// column is not a text column. This behavior is intended to allow the type of the current 
        /// key column to be inferred when building the search key.
        /// </para>
        /// <para>
        /// If you want to build a similar search key for the start of an index, a similar call to 
        /// Table::MakeKey should be made for the key column that is to be the prefix wildcard, 
        /// but with that no wildcard options specified.The search key is then in an appropriate 
        /// state to use for such a search.This is analogous to using PartialColumnStartLimit, except 
        /// that the search key is not cleanly finished as it is after the use of a wildcard option.
        /// </para>
        /// <para>
        /// This option has been deprecated for Windows XP and later releases in order to address 
        /// this awkward semantic. PartialColumnStartLimit and PartialColumnEndLimit should be used 
        /// instead, when possible.
        /// </para>
        /// </summary>
        SubStrLimit = JET_bitSubStrLimit
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( KeyFlags, unsigned long );

    /// <summary>
    /// Values for the flags parameter of the Table::Seek and Table::SeekNX member functions.
    /// </summary>
    enum class SeekFlags : unsigned long
    {
        None = 0,
        /// <summary>
        /// <para>
        /// A special error code, JET_wrnUniqueKey, will be returned if it can 
        /// be cheaply determined that there is exactly one index entry that 
        /// matches the search key.
        /// </para>
        /// <para>
        /// This option is ignored unless Equal is also specified.
        /// </para>
        /// <para>
        /// This option is only available on Windows Server 2003 and later releases.
        /// </para>
        /// </summary>
        CheckUniqueness = JET_bitCheckUniqueness,
        /// <summary>
        /// <para>
        /// The cursor will be positioned at the index entry closest to the start of 
        /// the index that exactly matches the search key. The start of the index is 
        /// the index entry that is found when moving to the first record in that 
        /// index. The start of the index is not the same as the low end of the 
        /// index, which can change depending on the sort order of the key columns 
        /// in the index.
        /// </para>
        /// <para>
        /// It is not meaningful to use this option with a search key that was constructed 
        /// using Table::MakeKey using a wildcard option.
        /// </para>
        /// </summary>
        Equal = JET_bitSeekEQ,
        /// <summary>
        /// <para>
        /// The cursor will be positioned at the index entry closest to the start of the index 
        /// that is greater than or equal to an index entry that would exactly match the search 
        /// criteria. The start of the index is the index entry that is found when moving to the 
        /// first record in that index. The start of the index is not the same as the low end 
        /// of the index, which can change depending on the sort order of the key columns in 
        /// the index.
        /// </para>
        /// <para>
        /// It is not meaningful to use this option with a search key that was constructed using 
        /// Table::MakeKey using a wildcard option intended to find index entries closest 
        /// to the end of the index.
        /// </para>
        /// </summary>
        GreaterOrEqual = JET_bitSeekGE,
        /// <summary>
        /// <para>
        /// The cursor will be positioned at the index entry closest to the start of the index 
        /// that is greater than an index entry that would exactly match the search criteria. 
        /// The start of the index is the index entry that is found when moving to the first 
        /// record in that index. The start of the index is not the same as the low end of 
        /// the index, which can change depending on the sort order of the key columns in 
        /// the index.
        /// </para>
        /// <para>
        /// It is not meaningful to use this option with a search key that was constructed 
        /// using Table::MakeKey using a wildcard option intended to find index entries 
        /// closest to the start of the index.
        /// </para>
        /// </summary>
        Greater = JET_bitSeekGT,
        /// <summary>
        /// <para>
        /// The cursor will be positioned at the index entry closest to the end of the index 
        /// that is less than or equal to an index entry that would exactly match the search 
        /// criteria. The end of the index is the index entry that is found when moving to 
        /// the last record in that index. The end of the index is not the same as the high 
        /// end of the index, which can change depending on the sort order of the key columns 
        /// in the index.
        /// </para>
        /// <para>
        /// It is not meaningful to use this option with a search key that was constructed 
        /// using Table::MakeKey using a wildcard option intended to find index entries 
        /// closest to the start of the index.
        /// </para>
        /// </summary>
        LessOrEqual = JET_bitSeekLE,
        /// <summary>
        /// <para>
        /// The cursor will be positioned at the index entry closest to the end of the index 
        /// that is less than an index entry that would exactly match the search criteria. 
        /// The end of the index is the index entry that is found when moving to the last 
        /// record in that index. The end of the index is not the same as the high end of 
        /// the index, which can change depending on the sort order of the key columns in 
        /// the index.
        /// </para>
        /// <para>
        /// It is not meaningful to use this option with a search key that was constructed 
        /// using Table::MakeKey using a wildcard option intended to find index entries 
        /// closest to the end of the index.
        /// </para>
        /// </summary>
        Less = JET_bitSeekLT,
        /// <summary>
        /// <para>
        /// An index range will automatically be setup for all keys that exactly match the 
        /// search key. The resulting index range is identical to one that would have 
        /// otherwise been created by a call to Table::SetIndexRange with the 
        /// IndexRangeFlags::Inclusive and IndexRangeFlags::UpperLimit options. 
        /// </para>
        /// <para>
        /// This is a convenient method for discovering all the index entries that match 
        /// the same search criteria.
        /// </para>
        /// <para>
        /// This option is ignored unless Equal is also specified.
        /// </para>
        /// </summary>
        SetIndexRange = JET_bitSetIndexRange
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( SeekFlags, unsigned long );

    /// <summary>
    /// Values for the flags parameter of the Table::SetIndexRange member function.
    /// </summary>
    enum class IndexRangeFlags : unsigned long
    {
        None = 0,
        /// <summary>
        /// This presence or absence of this option indicates the boundary criteria 
        /// of the index range. When present, this option indicates that the limit 
        /// of the index range is inclusive. When absent, this option indicates that 
        /// the limit of the index range is exclusive. When the limit of the index 
        /// range is inclusive then any index entries exactly matching the search 
        /// criteria are included in the range.
        /// </summary>
        Inclusive = JET_bitRangeInclusive,
        /// <summary>
        /// <para>
        /// If this option is used, then the search key in the cursor represents 
        /// the search criteria for the index entry closest to the end of the index 
        /// that will match the index range. The index range will be established 
        /// between the current position of the cursor and this index entry so that 
        /// all matches can be found by walking forward on the index using Table::MoveNext 
        /// or Table::Move with JET_MoveNext or a positive offset.
        /// </para>
        /// <para>
        /// It is not meaningful to use this option with a search key that was constructed 
        /// using Table::MakeKey using a wildcard option intended to find index entries 
        /// closest to the start of the index.
        /// </para>
        /// <para>
        /// If this option is omitted, then the search key in the cursor represents the 
        /// search criteria for the index entry closest to the start of the index that 
        /// will match the index range. The index range will be established between the 
        /// current position of the cursor and this index entry so that all matches can 
        /// be found by walking backward on the index using Table::MovePrevious or 
        /// Table::Move with JET_MovePrevious or a negative offset.
        /// </para>
        /// <para>
        /// It is not meaningful to omit this option with a search key that was constructed 
        /// using Table::MakeKey using a wildcard option intended to find index entries 
        /// closest to the end of the index.
        /// </para>
        /// </summary>
        UpperLimit = JET_bitRangeUpperLimit,
        /// <summary>
        /// This option requests that the index range be removed as soon as it has been 
        /// established. All other aspects of the operation remain unchanged. This is 
        /// useful for testing for the existence of index entries that match the search 
        /// criteria.
        /// </summary>
        InstantDuration = JET_bitRangeInstantDuration,
        /// <summary>
        /// <para>
        /// This option requests that an existing index range on the cursor be canceled. 
        /// Once the index range is canceled, it will be possible to move beyond the end 
        /// of the index range using Table::Move. If an index range is not already in effect, 
        /// then Table::SetIndexRange will fail with an exception caused by 
        /// JET_errInvalidOperation.
        /// </para>
        /// <para>
        /// When this option is specified, all other options are ignored.
        /// </para>
        /// </summary>
        Remove = JET_bitRangeRemove
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( IndexRangeFlags, unsigned long );

    /// <summary>
    /// Values for the flags parameter to the Table::SetCurrentIndex member function.
    /// </summary>
    enum class SetCurrentIndexFlags : unsigned long
    {
        /// <summary>
        /// This option indicates that the cursor should be positioned on the first 
        /// entry of the specified index. If the clustered index is being selected 
        /// (primary index or sequential index) and the current index is a secondary 
        /// index then JET_bitMoveFirst is assumed. If the current index is being 
        /// selected then this option is ignored and no change to the cursor position 
        /// is made.
        /// </summary>
        MoveFirst = JET_bitMoveFirst,
        /// <summary>
        /// <para>
        /// This option indicates that the cursor should be positioned on the index 
        /// entry of the new index that corresponds to the record associated with the 
        /// index entry at the current position of the cursor on the old index.
        /// </para>
        /// <para>
        /// If the definition for the new index contains at least one multi-valued 
        /// key column then the destination index entry is ambiguous. In this case, 
        /// the specified itagSequence is used to select which multi-value of the 
        /// most significant multi-valued key column is used to position the cursor. 
        /// It is only necessary to pass a single itagSequence even in the case of 
        /// multiple multi-valued key columns because the engine only expands all 
        /// values for the most significant multi-valued key column.
        /// </para>
        /// </summary>
        NoMove = JET_bitNoMove
    };                                   

    /// <summary>
    ///  Contains the information needed to create an index
    /// </summary>
    class IndexCreate : public JET_INDEXCREATE_W
    {
        using Base = JET_INDEXCREATE_W;
    public:
        IndexCreate( )
            : Base{ sizeof( Base ),0, }
        {
        }
    };

    /// <summary>
    /// Contains the information that is necessary to create a table 
    /// populated with columns and indexes.
    /// </summary>
    class TableCreate : public JET_TABLECREATE_W
    {
        using Base = JET_TABLECREATE_W;
    public:
        TableCreate( )
            : Base{ sizeof( Base ),0, }
        {
        }
    };

    /// <summary>
    /// Defines the data that can be stored in a column.
    /// </summary>
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

    /// <summary>
    /// Holds input and output parameters for use with the 
    /// Table::RetrieveColumns function. It describe which column 
    /// value to retrieve, how to retrieve it, and where to store 
    /// the results.
    /// </summary>
    class RetrieveColumn 
    {
        JET_RETRIEVECOLUMN data_;
    public:
        constexpr RetrieveColumn()
            : data_{0,nullptr,0,0,0,0,1,0,0}
        { }

        /// <summary>
        /// Retrieves the identifier for the column to retrieve.
        /// </summary>
        /// <returns>
        /// The identifier for the column to retrieve.
        /// </returns>
        constexpr JET_COLUMNID ColumnId( ) const
        {
            return data_.columnid;
        }
        /// <summary>
        /// Sets the identifier for the column to retrieve.
        /// </summary>
        /// <param name="columnId">
        /// The identifier for the column to retrieve.
        /// </param>
        constexpr void SetColumnId( JET_COLUMNID columnId )
        {
            data_.columnid = columnId;
        }

        /// <summary>
        /// Retrieves address of the buffer that will receive the data 
        /// that is retrieved from the column value.
        /// </summary>
        /// <returns></returns>
        constexpr void* data( ) const
        {
            return data_.pvData;
        }
        /// <summary>
        /// Sets the address of the buffer that will receive the data 
        /// that is retrieved from the column value and the maximum
        /// number of bytes that can be written to this buffer.
        /// </summary>
        /// <param name="data">
        /// The address of the buffer that will receive the data 
        /// that is retrieved from the column value.
        /// </param>
        /// <param name="dataSize">
        /// The maximum number of bytes that can be written to the address
        /// provided in the data parameter.
        /// </param>
        constexpr void SetData( void* data, size_t dataSize )
        {
            data_.pvData = data;
            data_.cbData = static_cast< unsigned long >( dataSize );
        }

        /// <summary>
        /// Retrieves the maximum number of bytes that can be written to the
        /// variable bound to this RetrieveColumn object.
        /// </summary>
        /// <returns>
        /// The maximum number of bytes that can be written to the
        /// variable bound to this RetrieveColumn object.
        /// </returns>
        constexpr size_t MaxSize( ) const
        {
            return data_.cbData;
        }

        /// <summary>
        /// Retrieves the size, in bytes, of data that is retrieved by a retrieve column operation.
        /// </summary>
        /// <returns>
        /// The size, in bytes, of data that is retrieved by a retrieve column operation.
        /// </returns>
        constexpr size_t size( ) const
        {
            return data_.cbActual;
        }
        /// <summary>
        /// Retrieves the size, in bytes, of data that is retrieved by a retrieve column operation.
        /// </summary>
        /// <returns>
        /// The size, in bytes, of data that is retrieved by a retrieve column operation.
        /// </returns>
        constexpr size_t ActualSize( ) const
        {
            return data_.cbActual;
        }
        /// <summary>
        /// Retrieves the RetrieveFlags options for column retrieval. 
        /// </summary>
        /// <returns>
        /// The RetrieveFlags options for column retrieval. Zero or more values 
        /// from the RetrieveFlags enumeration. The values can be tested using the <c>&</c> operator.
        /// </returns>
        constexpr RetrieveFlags Flags( ) const
        {
            return static_cast< RetrieveFlags >( data_.grbit );
        }
        /// <summary>
        /// Sets the RetrieveFlags options for column retrieval.
        /// </summary>
        /// <param name="flags">
        /// The RetrieveFlags options for column retrieval. Zero or more values 
        /// from the RetrieveFlags enumeration. The values can be combined using the <c>|</c> operator.
        /// </param>
        constexpr void SetFlags( RetrieveFlags flags )
        {
            data_.grbit = static_cast< JET_GRBIT >( flags );
        }
        /// <summary>
        /// Retrieves the offset to the first byte to be retrieved from 
        /// a column of type of ColumnType::LongBinary or ColumnType::LongText.
        /// </summary>
        /// <returns>
        /// The offset to the first byte to be retrieved from 
        /// a column of type of ColumnType::LongBinary or ColumnType::LongText.
        /// </returns>
        constexpr UInt32 ByteOffset( ) const
        {
            return data_.ibLongValue;
        }
        /// <summary>
        /// Sets the offset to the first byte to be retrieved from 
        /// a column of type of ColumnType::LongBinary or ColumnType::LongText.
        /// </summary>
        /// <param name="byteOffset">
        /// The offset to the first byte to be retrieved from 
        /// a column of type of ColumnType::LongBinary or ColumnType::LongText.
        /// </param>
        void SetByteOffset( UInt32 byteOffset )
        {
            data_.ibLongValue = byteOffset;
        }

        /// <summary>
        /// Retrieves the sequence number of the values that are contained in a multi-valued column.
        /// </summary>
        /// <returns>
        /// The sequence number of the values that are contained in a multi-valued column. 
        /// TagSequence be 0, and then the number of instances of a multi-valued column are 
        /// returned instead of any column data. 
        /// </returns>
        constexpr UInt32 TagSequence( ) const
        {
            return data_.itagSequence;
        }
        /// <summary>
        /// Sets the sequence number of the values that are contained in a multi-valued column.
        /// </summary>
        /// <param name="tagSequence">
        /// The sequence number of the values that are contained in a multi-valued column. 
        /// TagSequence be 0, and then the number of instances of a multi-valued column are 
        /// returned instead of any column data. 
        /// </param>
        constexpr void SetTagSequence( UInt32 tagSequence )
        {
            data_.itagSequence = tagSequence;
        }

        constexpr JET_COLUMNID ColumnIdNextTagged( ) const
        {
            return data_.columnidNextTagged;
        }
        constexpr void SetColumnIdNextTagged( JET_COLUMNID columnIdNextTagged )
        {
            data_.columnidNextTagged = columnIdNextTagged;
        }

        /// <summary>
        /// Retrieves error code or warning returned from the retrieval of the column.
        /// </summary>
        /// <returns>
        /// The error code or warning returned from the retrieval of the column.
        /// </returns>
        constexpr Ese::Result Result( ) const
        {
            return static_cast< Ese::Result >( data_.err );
        }
        /// <summary>
        /// Sets the error code or warning returned from the retrieval of the column.
        /// </summary>
        /// <param name="result">
        /// The error code or warning returned from the retrieval of the column.
        /// </param>
        constexpr void SetResult( Ese::Result result )
        {
            data_.err = static_cast< JET_ERR >( result );
        }
        /// <summary>
        /// Binds this RetrieveColumn object to a column and a data buffer.
        /// </summary>
        /// <param name="columnId">
        /// The column id that this RetrieveColumn object will be bound to.
        /// </param>
        /// <param name="data">
        /// The data buffer that this RetrieveColumn object will be bound to.
        /// </param>
        /// <param name="dataSize">
        /// The size of the data buffer that this RetrieveColumn object will be bound to.
        /// </param>
        /// <param name="retrieveFlags">
        /// The RetrieveFlags options for column retrieval. Zero or more values 
        /// from the RetrieveFlags enumeration. The values can be combined using the <c>|</c> operator.
        /// </param>
        void Bind( JET_COLUMNID columnId, void* data, size_t dataSize ,RetrieveFlags retrieveFlags = RetrieveFlags::None )
        {
            data_.columnid = columnId;
            data_.pvData = data;
            data_.cbData = static_cast<unsigned long>(dataSize);
            data_.cbActual = 0;
            data_.grbit = static_cast< JET_GRBIT >( retrieveFlags );
        }

        /// <summary>
        /// Binds this RetrieveColumn object to a column and a variable.
        /// </summary>
        /// <typeparam name="DataType">
        /// Any type that matches the Ese::DirectType concept.
        /// </typeparam>
        /// <param name="columnId">
        /// The column id that this RetrieveColumn object will be bound to.
        /// </param>
        /// <param name="value">
        /// A reference to the variable that this RetrieveColumn object will be bound to.
        /// </param>
        /// <param name="retrieveFlags">
        /// The RetrieveFlags options for column retrieval. Zero or more values 
        /// from the RetrieveFlags enumeration. The values can be combined using the <c>|</c> operator.
        /// </param>
        template<DirectType DataType>
        void Bind( JET_COLUMNID columnId, DataType& value, RetrieveFlags retrieveFlags = RetrieveFlags::None )
        {
            Bind( columnId, &value, sizeof( DataType ), retrieveFlags );
        }
        /// <summary>
        /// Binds this RetrieveColumn object to a column and a Byte container.
        /// </summary>
        /// <typeparam name="SpanT">
        /// Any type that matches the SimpleByteSpanLike concept.
        /// </typeparam>
        /// <param name="columnId">
        /// The column id that this RetrieveColumn object will be bound to.
        /// </param>
        /// <param name="value">
        /// A reference to the container that this RetrieveColumn object will be bound to.
        /// </param>
        /// <param name="retrieveFlags">
        /// The RetrieveFlags options for column retrieval. Zero or more values 
        /// from the RetrieveFlags enumeration. The values can be combined using the <c>|</c> operator.
        /// </param>
        template<SimpleByteSpanLike SpanT>
        void Bind( JET_COLUMNID columnId, SpanT& value, RetrieveFlags retrieveFlags = RetrieveFlags::None )
        {
            Bind( columnId, value.data(), value.size(), retrieveFlags );
        }
    };
    static_assert( sizeof( RetrieveColumn ) == sizeof( JET_RETRIEVECOLUMN ) );

    /// <summary>
    /// Contains input and output parameters for Table::SetColumns describing 
    /// which column value to set, how to set it, and where to get the column 
    /// set data.
    /// </summary>
    class SetColumn
    {
        JET_SETCOLUMN data_;
    public:
        SetColumn()
            : data_{0, 0, 0, 0, 0, 1, 0 }
        { }

        /// <summary>
        /// Retrieves the identifier for the column to set.
        /// </summary>
        /// <returns>
        /// The identifier for the column to set.
        /// </returns>
        constexpr JET_COLUMNID ColumnId( ) const
        {
            return data_.columnid;
        }
        /// <summary>
        /// Sets the identifier for the column to set.
        /// </summary>
        /// <param name="columnId">
        /// The identifier for the column to set.
        /// </param>
        constexpr void SetColumnId( JET_COLUMNID columnId )
        {
            data_.columnid = columnId;
        }

        /// <summary>
        /// Retrieves address of the buffer that holds the data 
        /// that is assigned to the column value.
        /// </summary>
        /// <returns></returns>
        constexpr const void* data( ) const
        {
            return data_.pvData;
        }
        /// <summary>
        /// Sets the address of the buffer that holds the data 
        /// that is assigned to the column value and the 
        /// number of bytes that can be retrieved from this buffer.
        /// </summary>
        /// <param name="data">
        /// The address of the buffer that holds the data 
        /// that is assigned to the column value.
        /// </param>
        /// <param name="dataSize">
        /// The number of bytes that can be retrieved from the address
        /// provided in the data parameter.
        /// </param>
        constexpr void SetData( const void* data, size_t dataSize )
        {
            data_.pvData = data;
            data_.cbData = static_cast< unsigned long >( dataSize );
        }

        /// <summary>
        /// Retrieves the number of bytes that will be retrieved from the
        /// variable bound to this RetrieveColumn object.
        /// </summary>
        /// <returns>
        /// The number of bytes that will be retrieved from the
        /// variable bound to this RetrieveColumn object.
        /// </returns>
        constexpr size_t size( ) const
        {
            return data_.cbData;
        }

        /// <summary>
        /// Retrieves the Ese::SetFlags options for setting the column value. 
        /// </summary>
        /// <returns>
        /// The Ese::SetFlags options for setting the column value. Zero or more values 
        /// from the Ese::SetFlags enumeration. The values can be tested using the <c>&</c> operator.
        /// </returns>
        constexpr Ese::SetFlags Flags( ) const
        {
            return static_cast< Ese::SetFlags >( data_.grbit );
        }
        /// <summary>
        /// Sets the Ese::SetFlags options for setting the column value. 
        /// </summary>
        /// <param name="flags">
        /// The Ese::SetFlags options for setting the column value. Zero or more values 
        /// from the Ese::SetFlags enumeration. The values can be combined using the <c>|</c> operator.
        /// </param>
        constexpr void SetFlags( Ese::SetFlags flags )
        {
            data_.grbit = static_cast< JET_GRBIT >( flags );
        }
        /// <summary>
        /// Retrieves the offset off the first byte in the column value to be written to 
        /// for a column of type of ColumnType::LongBinary or ColumnType::LongText.
        /// </summary>
        /// <returns>
        /// The offset off the first byte in the column value to be written to 
        /// for a column of type of ColumnType::LongBinary or ColumnType::LongText.
        /// </returns>
        constexpr UInt32 ByteOffset( ) const
        {
            return data_.ibLongValue;
        }
        /// <summary>
        /// Sets the offset off the first byte in the column value to be written to 
        /// for a column of type of ColumnType::LongBinary or ColumnType::LongText.
        /// </summary>
        /// <param name="byteOffset">
        /// The offset off the first byte in the column value to be written to 
        /// for a column of type of ColumnType::LongBinary or ColumnType::LongText.
        /// </param>
        void SetByteOffset( UInt32 byteOffset )
        {
            data_.ibLongValue = byteOffset;
        }

        /// <summary>
        /// Retrieves the sequence number of value in a multi-valued column. 
        /// </summary>
        /// <returns>
        /// The sequence number of value in a multi-valued column. A 
        /// TagSequence of 0 indicates that the column value set should 
        /// be added as a new instance of a multi-valued column. 
        /// </returns>
        constexpr UInt32 TagSequence( ) const
        {
            return data_.itagSequence;
        }
        /// <summary>
        /// Sets the sequence number of value in a multi-valued column. 
        /// </summary>
        /// <param name="tagSequence">
        /// The sequence number of value in a multi-valued column. A 
        /// TagSequence of 0 indicates that the column value set should 
        /// be added as a new instance of a multi-valued column. 
        /// </param>
        constexpr void SetTagSequence( UInt32 tagSequence )
        {
            data_.itagSequence = tagSequence;
        }


        /// <summary>
        /// Retrieves error code or warning returned from the setting of the column.
        /// </summary>
        /// <returns>
        /// The error code or warning returned from the setting of the column.
        /// </returns>
        constexpr Ese::Result Result( ) const
        {
            return static_cast< Ese::Result >( data_.err );
        }
        /// <summary>
        /// Sets the error code or warning returned from the setting of the column.
        /// </summary>
        /// <param name="result">
        /// The error code or warning returned from the setting of the column.
        /// </param>
        constexpr void SetResult( Ese::Result result )
        {
            data_.err = static_cast< JET_ERR >( result );
        }

        /// <summary>
        /// Binds this SetColumn object to a column and a data buffer.
        /// </summary>
        /// <param name="columnId">
        /// The column id that this SetColumn object will be bound to.
        /// </param>
        /// <param name="data">
        /// The data buffer that this SetColumn object will be bound to.
        /// </param>
        /// <param name="dataSize">
        /// The size of the data buffer that this SetColumn object will be bound to.
        /// </param>
        /// <param name="retrieveFlags">
        /// The Ese::SetFlags options for setting the column value. Zero or more values 
        /// from the Ese::SetFlags enumeration. The values can be combined using the <c>|</c> operator.
        /// </param>
        void Bind( JET_COLUMNID columnId, const void* data, size_t dataSize, Ese::SetFlags setFlags = Ese::SetFlags::None )
        {
            data_.columnid = columnId;
            data_.pvData = data;
            data_.cbData = static_cast< unsigned long >( dataSize );
            data_.grbit = static_cast< JET_GRBIT >( setFlags );
        }

        /// <summary>
        /// Binds this SetColumn object to a column and a variable.
        /// </summary>
        /// <typeparam name="DataType">
        /// Any type that matches the Ese::DirectType concept.
        /// </typeparam>
        /// <param name="columnId">
        /// The column id that this SetColumn object will be bound to.
        /// </param>
        /// <param name="value">
        /// A const reference to the variable that this SetColumn object will be bound to.
        /// </param>
        /// <param name="setFlags">
        /// The Ese::SetFlags options for setting the column value. Zero or more values 
        /// from the Ese::SetFlags enumeration. The values can be combined using the <c>|</c> operator.
        /// </param>
        template<DirectType DataType>
        void Bind( JET_COLUMNID columnId, const DataType& value, Ese::SetFlags setFlags = Ese::SetFlags::None )
        {
            Bind( columnId, &value, sizeof( DataType ), setFlags );
        }

        /// <summary>
        /// Binds this SetColumn object to a column and a Byte container.
        /// </summary>
        /// <typeparam name="SpanT">
        /// Any type matching SimpleByteSpanLike concept.
        /// </typeparam>
        /// <param name="columnId">
        /// The column id that this SetColumn object will be bound to.
        /// </param>
        /// <param name="value">
        /// A const reference to the Byte container that this SetColumn object will be bound to.
        /// </param>
        /// <param name="setFlags">
        /// The Ese::SetFlags options for setting the column value. Zero or more values 
        /// from the Ese::SetFlags enumeration. The values can be combined using the <c>|</c> operator.
        /// </param>
        template<SimpleByteSpanLike SpanT>
        void Bind( JET_COLUMNID columnId, const SpanT& value, Ese::SetFlags setFlags = Ese::SetFlags::None )
        {
            Bind( columnId, value.data( ), value.size( ), setFlags );
        }

    };
    static_assert( sizeof( SetColumn ) == sizeof( JET_SETCOLUMN ) );

    /// <summary>
    /// Values for the grbit member of the JET_OBJECTINFO Structure
    /// </summary>
    enum class TableOptions : int
    {
        None = 0,
        /// <summary>
        /// The table can be updated.
        /// </summary>
        Updatable = JET_bitTableInfoUpdatable,
        /// <summary>
        /// The table can have bookmarks.
        /// </summary>
        Bookmark = JET_bitTableInfoBookmark,
        /// <summary>
        /// The table can be rolled back.
        /// </summary>
        Rollback = JET_bitTableInfoRollback
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( TableOptions, int );

    /// <summary>
    /// Values for the flags member of the JET_OBJECTINFO Structure
    /// </summary>
    enum class ObjectFlags : unsigned
    {
        None = 0,
        /// <summary>
        /// The table is a System Table and is for internal use only.
        /// </summary>
        System = JET_bitObjectSystem,
        /// <summary>
        /// The table inherited DDL from a template table.
        /// </summary>
        Derived = JET_bitObjectTableDerived,
        /// <summary>
        /// The DDL for the table cannot be modified.
        /// </summary>
        FixedDDL = JET_bitObjectTableFixedDDL,
        /// <summary>
        /// Used in conjunction with ObjectFlags::Template to disallow 
        /// fixed or variable columns in derived tables (so that fixed 
        /// or variable columns can be added to the template in the future).
        /// </summary>
        NoFixedVarColumnsInDerivedTables = JET_bitObjectTableNoFixedVarColumnsInDerivedTables,
        /// <summary>
        /// The table is a template table.
        /// </summary>
        Template = JET_bitObjectTableTemplate
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( ObjectFlags, unsigned );

    /// <summary>
    /// Values for flags parameter of the Table::SetSequential member function.
    /// </summary>
    enum class SequentialFlags : unsigned
    {
        None = 0,
        /// <summary>
        /// This option is used to index in the forward direction.
        /// </summary>
        PrereadForward = JET_bitPrereadForward,
        /// <summary>
        /// This option is used to index in the backward direction.
        /// </summary>
        PrereadBackward = JET_bitPrereadBackward
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( SequentialFlags, unsigned );

    /// <summary>
    /// Values for the value parameter of the Instance::SetExceptionAction static member function,
    /// or the return value from the Instance::QueryExceptionAction() static member function.
    /// </summary>
    enum class ExceptionAction : long
    {
        /// <summary>
        /// Displays message box on exception
        /// </summary>
        DisplayMessageBox = JET_ExceptionMsgBox,
        /// <summary>
        /// Do nothing on exceptions
        /// </summary>
        None = JET_ExceptionNone,
        /// <summary>
        /// Use the Windows RaiseFailFastException API to force a crash
        /// </summary>
        FailFast = JET_ExceptionFailFast
    };


    template<StringLike StringT>
    class ColumnList;

    /// <summary>
    /// <para>
    /// The Table class manages a handle to a database cursor that is used to 
    /// call to the JET API. A cursor can only be used with the session that was 
    /// used to open that cursor.
    /// </para>
    /// <para>
    /// A cursor manages the use of a table for the database engine. A cursor can do the following tasks:
    /// </para>
    /// <list type="bullet">
    ///      <item>Scan records</item>
    ///      <item>Search for records</item>
    ///      <item>Choose the effective sort order and visibility of those records</item>
    ///      <item>Create, update, or delete records</item>
    ///      <item>Modify the schema of the table</item>
    /// </list>
    /// <para>
    /// The supported functionality of the cursor might change as the status or type of 
    /// the underlying table changes. For example, a temporary table might disallow 
    /// searching for data when it is opened with certain options. 
    /// </para>
    /// <para>
    /// The cursor is always fully connected to the underlying table and interacts with 
    /// that data directly without any caching. Almost all of the core ISAM functionality 
    /// that is exposed by this database engine is works through the cursor.
    /// </para>
    /// </summary>
    class Table
    {
        friend class Database;
        JET_SESID sessionId_;
        JET_TABLEID tableId_;
    public:
        using ColumnId = JET_COLUMNID;

        /// <summary>
        /// This constructor is used to create a Table object
        /// that is not initially referencing an existing ESE table cursor.
        /// </summary>
        constexpr Table( ) noexcept
            : sessionId_( JET_sesidNil ),
              tableId_( JET_tableidNil ) 
        {
        }

        /// <summary>
        /// Used to initialize a Table object that references
        /// an ESE table cursor.
        /// </summary>
        /// <param name="sessionId"></param>
        /// <param name="tableId"></param>
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
        /// <summary>
        /// The destructor closes the ESE table cursor.
        /// </summary>
        ~Table( )
        {
            Close( );
        }

        Table( const Table& other ) = delete;

        /// <summary>
        /// Move constructor
        /// </summary>
        /// <param name="other">
        /// The Table object that is moved to the new object.
        /// </param>
        Table( Table&& other ) noexcept
            : sessionId_( other.sessionId_ ), tableId_( other.tableId_ )
        {
            other.sessionId_ = JET_sesidNil;
            other.tableId_ = JET_tableidNil;
        }
        Table& operator = ( const Table& other ) = delete;

        /// <summary>
        /// Move assignment
        /// </summary>
        /// <param name="other">
        /// The Table object that is moved to this object.
        /// </param>
        /// <returns></returns>
        Table& operator = ( Table&& other ) noexcept
        {
            std::swap(sessionId_, other.sessionId_);
            std::swap(tableId_, other.tableId_);
            return *this;
        }
        /// <summary>
        /// Returns the handle to the database table cursor
        /// </summary>
        JET_TABLEID Handle( ) const
        {
            return tableId_;
        }

        /// <summary>
        /// Checks that both sessionId_ and tableId_ are not assigned their nil values.
        /// </summary>
        /// <returns>
        /// true if neither sessionId_ and tableId_ are assigned their nil values, otherwise false.
        /// </returns>
        bool IsValid( ) const noexcept
        {
            return (sessionId_ != JET_sesidNil) && (tableId_ != JET_tableidNil);
        }

        /// <summary>
        /// Checks that both sessionId_ and tableId_ are not assigned their nil values.
        /// </summary>
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
        /// <para>
        /// MakeKey constructs search keys that are used to find a set of entries 
        /// in an index by some simple search criteria on their key column values. 
        /// </para>
        /// <para>
        /// A search key is also one of the intrinsic properties of a cursor 
        /// and is used by the Seek and SetIndexRange methods to locate index 
        /// entries matching these search criteria on the current index of that cursor. 
        /// </para>
        /// <para>
        /// A complete search key is built up in a series of MakeKey calls where each 
        /// call is used to load the column value for the next key column of the current 
        /// index of a cursor. It is also possible to load a previously constructed 
        /// search key that has been retrieved from the cursor using RetrieveKey.
        /// </para>
        /// </summary>
        /// <param name="keyData">
        /// <para>
        /// The input buffer containing the column data for the current key column of 
        /// the current index of the cursor for which the search key is being constructed.
        /// </para>
        /// <para>
        /// The data type of the column data in the input buffer must exactly 
        /// match the data type and other properties of the column definition 
        /// of the current key column. No type coercion is performed on the 
        /// column data whatsoever.
        /// </para>
        /// <para>
        /// If KeyFlags::NormalizedKey is specified in the flags parameter, the 
        /// input buffer must contain a previously constructed search key. Such 
        /// keys are obtained using a call to Table::RetrieveKey.
        /// </para>
        /// </param>
        /// <param name="keyDataLength">
        /// <para>
        /// The size in bytes of the column data provided in the input buffer.
        /// </para>
        /// <para>
        /// If KeyFlags::NormalizedKey is specified in the flags parameter, this 
        /// is the size of the search key provided in the input buffer
        /// </para>
        /// <para>
        /// If the size of the column data is zero then the contents of the input 
        /// buffer are ignored. If KeyFlags::DataZeroLength is specified in the flags 
        /// parameter and the current key column of the current index of the cursor 
        /// is a variable length column, the input column data is presumed to be a 
        /// zero length value. Otherwise, the input column data is presumed to be 
        /// a NULL value.
        /// </para>
        /// </param>
        /// <param name="flags">
        /// Zero or more values from the KeyFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        void MakeKey( const void* keyData, unsigned long keyDataLength, KeyFlags flags = KeyFlags::None ) const
        {
            auto rc = static_cast<Result>( JetMakeKey( sessionId_, tableId_, keyData, keyDataLength, static_cast<JET_GRBIT>( flags ) ) );
            RequireSuccess( rc );
        }

        /// <summary>
        /// <para>
        /// MakeKey constructs search keys that are used to find a set of entries 
        /// in an index by some simple search criteria on their key column values. 
        /// </para>
        /// <para>
        /// A search key is also one of the intrinsic properties of a cursor 
        /// and is used by the Seek and SetIndexRange methods to locate index 
        /// entries matching these search criteria on the current index of that cursor. 
        /// </para>
        /// <para>
        /// A complete search key is built up in a series of MakeKey calls where each 
        /// call is used to load the column value for the next key column of the current 
        /// index of a cursor. 
        /// </para>
        /// </summary>
        /// <typeparam name="T">
        /// <list type="bullet">
        /// <item>An integer type, except bool.</item>
        /// <item>A floating point type.</item>
        /// <item>TimeSpan</item>
        /// <item>Currency</item>
        /// <item>Guid</item>
        /// <item>GUID</item>
        /// <item>boost::uuids::uuid</item>
        /// </list>
        /// </typeparam>
        /// <param name="keyData">
        /// A const reference to a variable containing the column data for the current key column of 
        /// the current index of the cursor for which the search key is being constructed.
        /// </param>
        /// <param name="flags">
        /// Zero or more values from the KeyFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        template<DirectType T>
        void MakeKey( const T& keyData, KeyFlags flags = KeyFlags::None ) const
        {
            MakeKey( &keyData, sizeof( std::decay_t<T> ), flags );
        }

        /// <summary>
        /// <para>
        /// MakeKey constructs search keys that are used to find a set of entries 
        /// in an index by some simple search criteria on their key column values. 
        /// </para>
        /// <para>
        /// A search key is also one of the intrinsic properties of a cursor 
        /// and is used by the Seek and SetIndexRange methods to locate index 
        /// entries matching these search criteria on the current index of that cursor. 
        /// </para>
        /// <para>
        /// A complete search key is built up in a series of MakeKey calls where each 
        /// call is used to load the column value for the next key column of the current 
        /// index of a cursor. 
        /// </para>
        /// </summary>
        /// <param name="dateTime">
        /// A const reference to a DateTime containing the column data for the current key column of 
        /// the current index of the cursor for which the search key is being constructed.
        /// </param>
        /// <param name="flags">
        /// Zero or more values from the KeyFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        void MakeKey( const DateTime& dateTime, KeyFlags flags = KeyFlags::None ) const
        {
            double keyData = dateTime.ToOADate( );
            MakeKey( &keyData, sizeof( double ), flags );
        }
        void MakeKey( const std::chrono::system_clock::time_point& time_point, KeyFlags flags = KeyFlags::None ) const
        {
            DateTime dateTime( time_point );
            double keyData = dateTime.ToOADate( );
            MakeKey( &keyData, sizeof( double ), flags );
        }

        /// <summary>
        /// <para>
        /// MakeKey constructs search keys that are used to find a set of entries 
        /// in an index by some simple search criteria on their key column values. 
        /// </para>
        /// <para>
        /// A search key is also one of the intrinsic properties of a cursor 
        /// and is used by the Seek and SetIndexRange methods to locate index 
        /// entries matching these search criteria on the current index of that cursor. 
        /// </para>
        /// <para>
        /// A complete search key is built up in a series of MakeKey calls where each 
        /// call is used to load the column value for the next key column of the current 
        /// index of a cursor. 
        /// </para>
        /// </summary>
        /// <param name="dateTime">
        /// A boolean value the column data for the current key column of 
        /// the current index of the cursor for which the search key is being constructed.
        /// </param>
        /// <param name="flags">
        /// Zero or more values from the KeyFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        void MakeKey( bool value, KeyFlags flags = KeyFlags::None ) const
        {
            Byte keyData = value ? 1 : 0;
            MakeKey( &keyData, sizeof( Byte ), flags );
        }

        /// <summary>
        /// <para>
        /// MakeKey constructs search keys that are used to find a set of entries 
        /// in an index by some simple search criteria on their key column values. 
        /// </para>
        /// <para>
        /// A search key is also one of the intrinsic properties of a cursor 
        /// and is used by the Seek and SetIndexRange methods to locate index 
        /// entries matching these search criteria on the current index of that cursor. 
        /// </para>
        /// <para>
        /// A complete search key is built up in a series of MakeKey calls where each 
        /// call is used to load the column value for the next key column of the current 
        /// index of a cursor. 
        /// </para>
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the SimpleCharSpanLike concept.
        /// </typeparam>
        /// <param name="value">
        /// A const reference to a variable containing the column data for the current key column of 
        /// the current index of the cursor for which the search key is being constructed.
        /// </param>
        /// <param name="flags">
        /// Zero or more values from the KeyFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        template<SimpleCharSpanLike T>
        void MakeKey( const T& value, KeyFlags flags = KeyFlags::None ) const
        {
            using CharT = typename T::value_type;
            unsigned long keySize = static_cast<unsigned long>(value.size( ) * sizeof( CharT ));
            MakeKey( value.c_str(), keySize, flags );
        }

        /// <summary>
        /// <para>
        /// MakeKey constructs search keys that are used to find a set of entries 
        /// in an index by some simple search criteria on their key column values. 
        /// </para>
        /// <para>
        /// A search key is also one of the intrinsic properties of a cursor 
        /// and is used by the Seek and SetIndexRange methods to locate index 
        /// entries matching these search criteria on the current index of that cursor. 
        /// </para>
        /// <para>
        /// A complete search key is built up in a series of MakeKey calls where each 
        /// call is used to load the column value for the next key column of the current 
        /// index of a cursor. 
        /// </para>
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the SimpleByteSpanLike concept.
        /// </typeparam>
        /// <param name="value">
        /// A const reference to a variable containing the column data for the current key column of 
        /// the current index of the cursor for which the search key is being constructed.
        /// </param>
        /// <param name="flags">
        /// Zero or more values from the KeyFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        template<SimpleByteSpanLike T>
        void MakeKey( const T& value, KeyFlags flags = KeyFlags::None ) const
        {
            unsigned long keySize = static_cast< unsigned long >( value.size( ) );
            MakeKey( value.c_str( ), keySize, flags );
        }

        /// <summary>
        /// <para>
        /// MakeKey constructs search keys that are used to find a set of entries 
        /// in an index by some simple search criteria on their key column values. 
        /// </para>
        /// <para>
        /// A search key is also one of the intrinsic properties of a cursor 
        /// and is used by the Seek and SetIndexRange methods to locate index 
        /// entries matching these search criteria on the current index of that cursor. 
        /// </para>
        /// <para>
        /// A complete search key is built up in a series of MakeKey calls where each 
        /// call is used to load the column value for the next key column of the current 
        /// index of a cursor. 
        /// </para>
        /// </summary>
        /// <param name="value">
        /// A pointer to a zero terminated c style char string.
        /// </param>
        /// <param name="flags">
        /// Zero or more values from the KeyFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        void MakeKey( const char* value, KeyFlags flags = KeyFlags::None ) const
        {
            unsigned long keySize = static_cast<unsigned long>( strlen(value) );
            MakeKey( value, keySize, flags );
        }
        /// <summary>
        /// <para>
        /// MakeKey constructs search keys that are used to find a set of entries 
        /// in an index by some simple search criteria on their key column values. 
        /// </para>
        /// <para>
        /// A search key is also one of the intrinsic properties of a cursor 
        /// and is used by the Seek and SetIndexRange methods to locate index 
        /// entries matching these search criteria on the current index of that cursor. 
        /// </para>
        /// <para>
        /// A complete search key is built up in a series of MakeKey calls where each 
        /// call is used to load the column value for the next key column of the current 
        /// index of a cursor. 
        /// </para>
        /// </summary>
        /// <param name="value">
        /// A pointer to a zero terminated c style wchar_t string.
        /// </param>
        /// <param name="flags">
        /// Zero or more values from the KeyFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        void MakeKey( const wchar_t* value, KeyFlags flags = KeyFlags::None ) const
        {
            unsigned long keySize = static_cast<unsigned long>( wcslen( value )*sizeof(wchar_t) );
            MakeKey( value, keySize, flags );
        }

        /// <summary>
        /// Temporarily limits the set of index entries that the cursor 
        /// can walk using Table::Move to those starting from the current 
        /// index entry and ending at the index entry that matches the search 
        /// criteria specified by the search key in that cursor and the 
        /// specified bound criteria. A search key must have been previously 
        /// constructed using Table::MakeKey.
        /// </summary>
        /// <param name="flags">
        /// Zero or more values from the IndexRangeFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        void SetIndexRange( IndexRangeFlags flags = Ese::IndexRangeFlags::None ) const
        {
            auto rc = static_cast<Result>( JetSetIndexRange( sessionId_, tableId_, static_cast<JET_GRBIT>( flags ) ) );
            RequireSuccess( rc );
        }

        /// <summary>
        /// <para>
        /// Retrieves the key for the index entry at the current position of a cursor. 
        /// </para>
        /// <para>
        /// Such keys are constructed by calls to MakeKey. 
        /// </para>
        /// <para>
        /// The retrieved key can then be used to efficiently return that cursor to 
        /// the same index entry by a call to Seek
        /// </para>
        /// </summary>
        /// <param name="keyData">
        /// The output buffer that will receive the key.
        /// </param>
        /// <param name="maxKeyDataLength">
        /// The maximum size in bytes of the output buffer.
        /// </param>
        /// <param name="actualKeyDataLength">
        /// <para>
        /// Receives the actual size in bytes of the key.
        /// </para>
        /// <para>
        /// If this parameter is NULL then the actual size of the key 
        /// will not be returned.
        /// </para>
        /// <para>
        /// If the output buffer is too small, then the actual size of 
        /// the key will still be returned. That means that this number 
        /// will be larger than the size of the output buffer.
        /// </para>
        /// </param>
        /// <param name="retrieveCopyOfSearchKey">
        /// If true, the engine will return the search key for the cursor. 
        /// The search key is built up using one or more prior calls to 
        /// Table::MakeKey for the purposes of seeking to that key using 
        /// Table::Seek or setting an index range using Table::SetIndexRange.
        /// </param>
        void RetrieveKey( void* keyData, unsigned long maxKeyDataLength, unsigned long* actualKeyDataLength, bool retrieveCopyOfSearchKey = true ) const
        {
            auto rc = static_cast<Result>( JetRetrieveKey( sessionId_, tableId_, keyData, maxKeyDataLength, actualKeyDataLength, retrieveCopyOfSearchKey ? JET_bitRetrieveCopy : 0 ) );
            if ( rc != Result::Success && rc != Result::WarningBufferTruncated )
            {
                HCC_THROW( Exception, rc );
            }
        }

        /// <summary>
        /// <para>
        /// Retrieves the key for the index entry at the current position of a cursor. 
        /// </para>
        /// <para>
        /// Such keys are constructed by calls to MakeKey. 
        /// </para>
        /// <para>
        /// The retrieved key can then be used to efficiently return that cursor to 
        /// the same index entry by a call to Seek
        /// </para>
        /// </summary>
        /// <typeparam name="BinaryT">
        /// Any type that matches the BinaryLike concept.
        /// </typeparam>
        /// <param name="retrieveCopyOfSearchKey">
        /// If true, the engine will return the search key for the cursor. 
        /// The search key is built up using one or more prior calls to 
        /// Table::MakeKey for the purposes of seeking to that key using 
        /// Table::Seek or setting an index range using Table::SetIndexRange.
        /// </param>
        /// <returns>
        /// The retrieved key data.
        /// </returns>
        template<BinaryLike BinaryT>
        BinaryT RetrieveKey( bool retrieveCopyOfSearchKey = true ) const
        {
            unsigned long actualKeyDataLength = 0;
            RetrieveKey( nullptr, 0, &actualKeyDataLength, retrieveCopyOfSearchKey );
            BinaryT result;
            if ( actualKeyDataLength )
            {
                result.resize( actualKeyDataLength );
                RetrieveKey( result.data( ), result.size(), &actualKeyDataLength, retrieveCopyOfSearchKey );
            }
            return result;
        }

        /// <summary>
        /// Sets the current index of a cursor. The current 
        /// index of a cursor defines which records in a 
        /// table are visible to that cursor and the order 
        /// in which they appear by selecting the set of index 
        /// entries to use to expose those records.
        /// </summary>
        /// <param name="indexName">
        /// <para>
        /// Pointer to a zero terminated string that contains 
        /// the name of the index to be selected for the cursor.
        /// </para>
        /// <para>
        /// If this parameter is nullptr or an empty string then 
        /// the clustered index will be selected. If a primary 
        /// index is defined for the table then that index will be 
        /// selected because it is the same as the clustered index. 
        /// If no primary index is defined for the table then the 
        /// sequential index will be selected. The sequential 
        /// index has no index definition.
        /// </para>
        /// </param>
        void SetCurrentIndex( const wchar_t* indexName ) const
        {
            auto rc = static_cast<Result>( JetSetCurrentIndexW( sessionId_, tableId_, indexName ) );
            RequireSuccess( rc );
        }
        /// <summary>
        /// Sets the current index of a cursor. The current 
        /// index of a cursor defines which records in a 
        /// table are visible to that cursor and the order 
        /// in which they appear by selecting the set of index 
        /// entries to use to expose those records.
        /// </summary>
        /// <param name="indexName">
        /// <para>
        /// Pointer to a zero terminated string that contains 
        /// the name of the index to be selected for the cursor.
        /// </para>
        /// <para>
        /// If this parameter is nullptr or an empty string then 
        /// the clustered index will be selected. If a primary 
        /// index is defined for the table then that index will be 
        /// selected because it is the same as the clustered index. 
        /// If no primary index is defined for the table then the 
        /// sequential index will be selected. The sequential 
        /// index has no index definition.
        /// </para>
        /// </param>
        void SetCurrentIndex( const char* indexName ) const
        {
            auto rc = static_cast<Result>( JetSetCurrentIndexA( sessionId_, tableId_, indexName ) );
            RequireSuccess( rc );
        }

        /// <summary>
        /// Sets the current index of a cursor. The current 
        /// index of a cursor defines which records in a 
        /// table are visible to that cursor and the order 
        /// in which they appear by selecting the set of index 
        /// entries to use to expose those records.
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <param name="indexName">
        /// <para>
        /// Pointer to a zero terminated string that contains 
        /// the name of the index to be selected for the cursor.
        /// </para>
        /// <para>
        /// If this parameter is an empty string then 
        /// the clustered index will be selected. If a primary 
        /// index is defined for the table then that index will be 
        /// selected because it is the same as the clustered index. 
        /// If no primary index is defined for the table then the 
        /// sequential index will be selected. The sequential 
        /// index has no index definition.
        /// </para>
        /// </param>
        template<SimpleStringLike T>
        void SetCurrentIndex( const T& indexName ) const
        {
            using CharT = typename T::value_type;
            auto namePtr = indexName.size( ) != 0 ? indexName.c_str( ) : static_cast< const CharT* >( 0 );
            SetCurrentIndex( namePtr );
        }

        /// <summary>
        /// Sets the current index of a cursor that defines which 
        /// records in a table are visible to that cursor and the 
        /// order in which they appear by selecting the set of 
        /// index entries to use to expose those records.
        /// </summary>
        /// <param name="indexName">
        /// If this parameter is nullptr or an empty string then 
        /// the clustered index will be selected. If a primary 
        /// index is defined for the table then that index will be 
        /// selected because it is the same as the clustered index. 
        /// If no primary index is defined for the table then the 
        /// sequential index will be selected. The sequential 
        /// index has no index definition.
        /// </param>
        /// <param name="flags">
        /// A value from the SetCurrentIndexFlags enumeration.
        /// </param>
        /// <returns>
        /// Returns false when a secondary index is being selected with 
        /// flags set to SetCurrentIndexFlags::NoMove and there is no 
        /// index entry in the new index that corresponds to the record 
        /// associated with the index entry at the current position of 
        /// the cursor on the old index.
        /// </returns>
        bool SetCurrentIndex( const wchar_t* indexName, SetCurrentIndexFlags flags ) const
        {
            
            auto rc = static_cast<Result>( JetSetCurrentIndex2W( sessionId_, tableId_, indexName, static_cast<JET_GRBIT>( flags ) ) );
            if ( rc != Result::Success && rc != Result::ErrorNoCurrentRecord )
            {
                HCC_THROW( Exception, rc );
            }
            return rc != Result::ErrorNoCurrentRecord;
        }
        /// <summary>
        /// Sets the current index of a cursor that defines which 
        /// records in a table are visible to that cursor and the 
        /// order in which they appear by selecting the set of 
        /// index entries to use to expose those records.
        /// </summary>
        /// <param name="indexName">
        /// If this parameter is nullptr or an empty string then 
        /// the clustered index will be selected. If a primary 
        /// index is defined for the table then that index will be 
        /// selected because it is the same as the clustered index. 
        /// If no primary index is defined for the table then the 
        /// sequential index will be selected. The sequential 
        /// index has no index definition.
        /// </param>
        /// <param name="flags">
        /// A value from the SetCurrentIndexFlags enumeration.
        /// </param>
        /// <returns>
        /// Returns false when a secondary index is being selected with 
        /// flags set to SetCurrentIndexFlags::NoMove and there is no 
        /// index entry in the new index that corresponds to the record 
        /// associated with the index entry at the current position of 
        /// the cursor on the old index.
        /// </returns>
        bool SetCurrentIndex( const char* indexName, SetCurrentIndexFlags flags ) const
        {
            auto rc = static_cast<Result>( JetSetCurrentIndex2A( sessionId_, tableId_, indexName, static_cast<JET_GRBIT>( flags ) ) );
            if ( rc != Result::Success && rc != Result::ErrorNoCurrentRecord )
            {
                HCC_THROW( Exception, rc );
            }
            return rc != Result::ErrorNoCurrentRecord;
        }
        /// <summary>
        /// Sets the current index of a cursor. The current 
        /// index of a cursor defines which records in a 
        /// table are visible to that cursor and the order 
        /// in which they appear by selecting the set of index 
        /// entries to use to expose those records.
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <param name="indexName">
        /// <para>
        /// Pointer to a zero terminated string that contains 
        /// the name of the index to be selected for the cursor.
        /// </para>
        /// <para>
        /// If this parameter is an empty string then 
        /// the clustered index will be selected. If a primary 
        /// index is defined for the table then that index will be 
        /// selected because it is the same as the clustered index. 
        /// If no primary index is defined for the table then the 
        /// sequential index will be selected. The sequential 
        /// index has no index definition.
        /// </para>
        /// </param>
        /// <param name="flags">
        /// A value from the SetCurrentIndexFlags enumeration.
        /// </param>
        /// <returns>
        /// Returns false when a secondary index is being selected with 
        /// flags set to SetCurrentIndexFlags::NoMove and there is no 
        /// index entry in the new index that corresponds to the record 
        /// associated with the index entry at the current position of 
        /// the cursor on the old index.
        /// </returns>
        template<SimpleStringLike T>
        bool SetCurrentIndex( const T& indexName, SetCurrentIndexFlags flags ) const
        {
            using CharT = typename T::value_type;
            auto namePtr = indexName.size( ) != 0 ? indexName.c_str( ) : static_cast< const CharT* >( 0 );
            return SetCurrentIndex( namePtr, flags );
        }

        /// <summary>
        /// Sets the current index of a cursor. The current index of a 
        /// cursor defines which records in a table are visible to that 
        /// cursor and the order in which they appear by selecting the 
        /// set of index entries to use to expose those records.
        /// </summary>
        /// <param name="indexName">
        /// If this parameter is nullptr or an empty string then 
        /// the clustered index will be selected. If a primary 
        /// index is defined for the table then that index will be 
        /// selected because it is the same as the clustered index. 
        /// If no primary index is defined for the table then the 
        /// sequential index will be selected. The sequential 
        /// index has no index definition.
        /// </param>
        /// <param name="flags">
        /// A value from the SetCurrentIndexFlags enumeration.
        /// </param>
        /// <param name="itagSequence">
        /// <para>
        /// Sequence number of the multi-valued column value which 
        /// will be used to position the cursor on the new index.
        /// </para>
        /// <para>
        /// This parameter is only used in conjunction with 
        /// SetCurrentIndexFlags::NoMove.
        /// </para>
        /// </param>
        /// <returns>
        /// Returns false when a secondary index is being selected with 
        /// flags set to SetCurrentIndexFlags::NoMove and there is no 
        /// index entry in the new index that corresponds to the record 
        /// associated with the index entry at the current position of 
        /// the cursor on the old index.
        /// </returns>
        bool SetCurrentIndex( const wchar_t* indexName, SetCurrentIndexFlags flags, unsigned long itagSequence ) const
        {
            auto rc = static_cast< Result >( JetSetCurrentIndex3W( sessionId_, tableId_, indexName, static_cast< JET_GRBIT >( flags ), itagSequence ) );
            if ( rc != Result::Success && rc != Result::ErrorNoCurrentRecord )
            {
                HCC_THROW( Exception, rc );
            }
            return rc != Result::ErrorNoCurrentRecord;
        }

        /// <summary>
        /// Sets the current index of a cursor. The current index of a 
        /// cursor defines which records in a table are visible to that 
        /// cursor and the order in which they appear by selecting the 
        /// set of index entries to use to expose those records.
        /// </summary>
        /// <param name="indexName">
        /// If this parameter is nullptr or an empty string then 
        /// the clustered index will be selected. If a primary 
        /// index is defined for the table then that index will be 
        /// selected because it is the same as the clustered index. 
        /// If no primary index is defined for the table then the 
        /// sequential index will be selected. The sequential 
        /// index has no index definition.
        /// </param>
        /// <param name="flags">
        /// A value from the SetCurrentIndexFlags enumeration.
        /// </param>
        /// <param name="itagSequence">
        /// <para>
        /// Sequence number of the multi-valued column value which 
        /// will be used to position the cursor on the new index.
        /// </para>
        /// <para>
        /// This parameter is only used in conjunction with 
        /// SetCurrentIndexFlags::NoMove.
        /// </para>
        /// </param>
        /// <returns>
        /// Returns false when a secondary index is being selected with 
        /// flags set to SetCurrentIndexFlags::NoMove and there is no 
        /// index entry in the new index that corresponds to the record 
        /// associated with the index entry at the current position of 
        /// the cursor on the old index.
        /// </returns>
        bool SetCurrentIndex( const char* indexName, SetCurrentIndexFlags flags, unsigned long itagSequence ) const
        {
            auto rc = static_cast< Result >( JetSetCurrentIndex3A( sessionId_, tableId_, indexName, static_cast< JET_GRBIT >( flags ), itagSequence ) );
            if ( rc != Result::Success && rc != Result::ErrorNoCurrentRecord )
            {
                HCC_THROW( Exception, rc );
            }
            return rc != Result::ErrorNoCurrentRecord;
        }

        /// <summary>
        /// Sets the current index of a cursor. The current index of a 
        /// cursor defines which records in a table are visible to that 
        /// cursor and the order in which they appear by selecting the 
        /// set of index entries to use to expose those records.
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <param name="indexName">
        /// If this parameter is nullptr or an empty string then 
        /// the clustered index will be selected. If a primary 
        /// index is defined for the table then that index will be 
        /// selected because it is the same as the clustered index. 
        /// If no primary index is defined for the table then the 
        /// sequential index will be selected. The sequential 
        /// index has no index definition.
        /// </param>
        /// <param name="flags">
        /// A value from the SetCurrentIndexFlags enumeration.
        /// </param>
        /// <param name="itagSequence">
        /// <para>
        /// Sequence number of the multi-valued column value which 
        /// will be used to position the cursor on the new index.
        /// </para>
        /// <para>
        /// This parameter is only used in conjunction with 
        /// SetCurrentIndexFlags::NoMove.
        /// </para>
        /// </param>
        /// <returns>
        /// Returns false when a secondary index is being selected with 
        /// flags set to SetCurrentIndexFlags::NoMove and there is no 
        /// index entry in the new index that corresponds to the record 
        /// associated with the index entry at the current position of 
        /// the cursor on the old index.
        /// </returns>
        template<SimpleStringLike T>
        bool SetCurrentIndex( const T& indexName, SetCurrentIndexFlags flags, unsigned long itagSequence ) const
        {
            return SetCurrentIndex( indexName.c_str(), flags, itagSequence );
        }


        /// <summary>
        /// Efficiently positions a cursor to an index entry that matches the 
        /// search criteria specified by the search key in that cursor and the 
        /// specified inequality. A search key must have been previously 
        /// constructed using Table::MakeKey.
        /// </summary>
        /// <param name="flags">
        /// Zero or more values from the SeekFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// Returns one of the following values from the Ese::Result enumeration:
        /// <list type="bullet">
        /// <item>
        /// Result::Success: The operation completed successfully, which means 
        /// that an index entry was found that exactly matched the search criteria.
        /// </item>
        /// <item>
        /// Result::WarningUniqueKey: Exactly one index entry was found that exactly 
        /// matched the search criteria. This value will only be returned if 
        /// SeekFlags::CheckUniqueness was specified and it was cheap to determine 
        /// that the matching index entry was the only index entry that exactly 
        /// matches the search criteria.
        /// </item>
        /// <item>
        /// Result::WarningSeekNotEqual: An index entry was found that matched the 
        /// search criteria. However, that index entry was not an exact match.
        /// </item>
        /// <item>
        /// Result::ErrorRecordNotFound: No index entry was found that matched 
        /// the search criteria.
        /// </item>
        /// <list>
        /// </returns>
        /// <remarks>
        /// <para>
        /// On success, the cursor will be positioned at an index entry that 
        /// matches the search criteria. If a record has been prepared for update, 
        /// then that update will be canceled. If an index range is in effect, 
        /// that index range will be canceled. If a search key has been constructed 
        /// for the cursor, then that search key will be deleted. No change to the 
        /// database state will occur. When multiple index entries have the same 
        /// value, the entry closest to the start of the index is always selected.
        /// </para>
        /// <para>
        /// On failure, the position of the cursor will remain unchanged unless 
        /// Result::ErrorRecordNotFound was returned. In that case, the cursor 
        /// will be positioned where the index entry that matched the search criteria 
        /// specified by the search key in that cursor and the specified inequality 
        /// would have been. The cursor can be moved relative to that position 
        /// but is still not on a valid index entry. If a record has been prepared for 
        /// update, then that update will be canceled. If an index range is in effect, 
        /// that index range will be canceled. If a search key has been constructed 
        /// for the cursor, then that search key will be deleted. No change to the 
        /// database state will occur.
        /// </para>
        /// </remarks>
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

        /// <summary>
        /// Retrieves the bookmark for the record that is associated with the 
        /// index entry at the current position of a cursor. This bookmark can 
        /// then be used to reposition that cursor back to the same record using 
        /// Table::GoToBookmark.
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the BinaryLike concept.
        /// </typeparam>
        /// <param name="result">
        /// A reference to a variable that receives the bookmark.
        /// </param>
        template<BinaryLike T>
        void GetBookmark( T& result ) const
        {
            unsigned char buffer[2048];
            unsigned long actualSize = 0;
            result.clear( );
            auto rc = static_cast<Result>( JetGetBookmark( sessionId_, tableId_, buffer, sizeof( buffer ), &actualSize ) );
            if ( rc == Result::ErrorBufferTooSmall )
            {
                result.resize( actualSize );
                rc = static_cast<Result>( JetGetBookmark( sessionId_, tableId_, result.data( ), actualSize, &actualSize ) );
                RequireSuccess( rc );
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
            }
        }

        /// <summary>
        /// Positions the cursor to an index entry for the record that is 
        /// associated with the specified bookmark. The bookmark can be 
        /// used with any index defined over a table. The bookmark for a 
        /// record can be retrieved using Table::GetBookmark.
        /// </summary>
        /// <typeparam name="T">
        /// A type that matches the SimpleByteSpanLike concept.
        /// </typeparam>
        /// <param name="bookmark">
        /// A const reference to the variable containing the bookmark to go to.
        /// </param>
        /// <returns>
        /// true if the cursor was positioned on the bookmark, otherwise 
        /// false.
        /// </returns>
        template<SimpleByteSpanLike T>
        bool GotoBookmark( const T& bookmark ) const
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

        /// <summary>
        /// Positions a cursor at the start or end of an index 
        /// and traverses the entries in that index either forward 
        /// or backward. It is also possible to move the cursor forward 
        /// or backward on the current index by a specified number of 
        /// index entries. Another approach is to artificially limit 
        /// the index entries that can be enumerated using Move by 
        /// setting up an index range on the cursor using Table::SetIndexRange.
        /// </summary>
        /// <param name="offset">
        /// <para>
        /// An arbitrary offset that indicates the desired movement of 
        /// the cursor on the current index.
        /// </para>
        /// <para>
        /// In addition to standard offsets, this parameter can also be set 
        /// with one of the following options:
        /// </para>
        /// <list>
        /// <item>
        /// <para>
        /// JET_MoveFirst: Moves the cursor to the first index entry in the 
        /// index (if one exists). This resets any index range set with 
        /// Table::SetIndexRange.
        /// </para>
        /// <para>
        /// Note: The literal value of -2147483648 is used to denote this 
        /// option. Do not use this value as an ordinary offset or unintended 
        /// behavior may result.
        /// </para>
        /// </item>
        /// <item>
        /// <para>
        /// JET_MoveLast: Moves the cursor to the last index entry in the index (if one exists). 
        /// This resets any index range set with Table::SetIndexRange.
        /// </para>
        /// <para>
        /// Note: The literal value of 2147483647 is used to denote this option. 
        /// Do not use this value as an ordinary offset or unintended behavior 
        /// may result.
        /// </para>
        /// </item>
        /// <item>
        /// JET_MoveNext: Moves the cursor to the next index entry in the index (if one exists). 
        /// This value is exactly equal to an ordinary offset of +1. It respects 
        /// index ranges set with Table::SetIndexRange.
        /// </item>
        /// <item>
        /// JET_MovePrevious: Moves the cursor to the previous index entry in the index (if one exists). 
        /// This value is exactly equal to an ordinary offset of -1. 
        /// It respects index ranges set with Table::SetIndexRange.
        /// </item>
        /// <item>
        /// 0: The cursor remains at the current logical position and the existence 
        /// of the index entry that corresponds to that logical position will be tested.
        /// </item>
        /// <list>
        /// </param>
        /// <param name="moveKeyNE">
        /// Moves the cursor forward or backward by the number of index 
        /// entries required to skip the requested number of index key 
        /// values encountered in the index. This has the effect of 
        /// collapsing index entries with duplicate key values into 
        /// a single index entry. Ordinarily, an offset will move the 
        /// cursor by the specified number of index entries regardless 
        /// of their key values.
        /// </param>
        /// <returns>
        /// true if the cursor is positioned on a record after the call.
        /// </returns>
        bool Move( long offset, bool moveKeyNE = false) const
        {
            auto rc = static_cast<Result>( JetMove( sessionId_, tableId_, offset, moveKeyNE? JET_bitMoveKeyNE : 0 ) );
            if ( rc != Result::Success && rc != Result::ErrorNoCurrentRecord )
            {
                HCC_THROW( Exception, rc );
            }
            return rc == Result::Success;
        }
        /// <summary>
        /// Moves the cursor to the first index entry in the 
        /// index (if one exists). This resets any index range set with 
        /// Table::SetIndexRange.
        /// </summary>
        /// <returns>
        /// true if the cursor is positioned on a record after the call.
        /// </returns>
        bool MoveFirst( ) const
        {
            return Move( JET_MoveFirst );
        }
        
        /// <summary>
        /// Moves the cursor to the next index entry in the index (if one exists). 
        /// This value is exactly equal to an ordinary offset of +1. It respects 
        /// index ranges set with Table::SetIndexRange.
        /// </summary>
        /// <returns>
        /// true if the cursor is positioned on a record after the call.
        /// </returns>
        bool MoveNext( ) const
        {
            return Move( JET_MoveNext );
        }

        /// <summary>
        /// Moves the cursor to the previous index entry in the index (if one exists). 
        /// This value is exactly equal to an ordinary offset of -1. 
        /// It respects index ranges set with Table::SetIndexRange.
        /// </summary>
        /// <returns>
        /// true if the cursor is positioned on a record after the call.
        /// </returns>
        bool MovePrevious( ) const
        {
            return Move( JET_MovePrevious );
        }

        /// <summary>
        /// Moves the cursor to the last index entry in the index (if one exists). 
        /// This resets any index range set with Table::SetIndexRange.
        /// </summary>
        /// <returns>
        /// true if the cursor is positioned on a record after the call.
        /// </returns>
        bool MoveLast( ) const
        {
            return Move( JET_MoveLast );
        }

        /// <summary>
        /// The cursor remains at the current logical position and the existence 
        /// of the index entry that corresponds to that logical position will be tested.
        /// </summary>
        /// <returns>
        /// true if the cursor is positioned on a record.
        /// </returns>
        bool IsPositioned( ) const
        {
            return Move( 0 );
        }

        /// <summary>
        /// Retrieves a single column value from the current record. The record is 
        /// that record associated with the index entry at the current position of 
        /// the cursor. Alternatively, this function can retrieve a column from 
        /// a record being created in the cursor copy buffer. This function can 
        /// also retrieve column data from an index entry that references the current 
        /// record. In addition to retrieving the actual column value, 
        /// Table::RetrieveColumn can also be used to retrieve the size of a column, 
        /// before retrieving the column data itself so that application buffers can 
        /// be sized appropriately.
        /// </summary>
        /// <param name="columnId">
        /// <para>
        /// The column id of the column to retrieve.
        /// </para>
        /// <para>
        /// A columnId value of 0 (zero) can be given which does not itself refer to 
        /// any individual column. When columnId 0 (zero) is given, all tagged columns, 
        /// sparse, and multi-valued columns are treated as a single column. This 
        /// facilitates retrieving all sparse columns that are present in a record.
        /// </para>
        /// </param>
        /// <param name="dataBuffer">
        /// The output buffer that receives the column value.
        /// </param>
        /// <param name="dataBufferSize">
        /// The maximum size, in bytes, of the output buffer.
        /// </param>
        /// <param name="actualDataSize">
        /// <para>
        /// Receives the actual size, in bytes, of the column value.
        /// </para>
        /// <para>
        /// If this parameter is nullptr, then the actual size of the column value 
        /// will not be returned.
        /// </para>
        /// </param>
        /// <param name="retrieveFlags">
        /// Zero or more values from the RetrieveFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        /// <param name="pretinfo">
        /// <para>
        /// If pretinfo is give as nullptr then the function behaves as though an 
        /// itagSequence of 1 and an ibLongValue of 0 (zero) were given. This causes 
        /// column retrieval to retrieve the first value of a multi-valued column, 
        /// and to retrieve long data at offset 0 (zero).
        /// </para>
        /// <para>
        /// This parameter is used to provide one or more of the following:
        /// </para>
        /// <list type="bullet">
        /// <item>
        /// ibLongValue: Gives a binary offset into a long column value when 
        /// retrieving a portion of a column value.
        /// </item>
        /// <item>
        /// itagSequence: Gives the sequence number of the desired multi-valued 
        /// column value. Note that this field is only set if the RetrieveFlags::Tag 
        /// is specified. Otherwise, it is unmodified.
        /// </item>
        /// <item>
        /// columnidNextTagged: Returns the column ID of the returned column value 
        /// when retrieving all tagged, sparse and multi-valued, columns using 
        /// passing columnId of 0 (zero).
        /// </item>
        /// </list>
        /// </param>
        /// <returns>
        /// <para>
        /// The function returns one of the following values from the Ese::Result enumeration:
        /// </para>
        /// <list type="bullet">
        /// <item>
        /// Result::Success: The operation completed successfully.
        /// </item>
        /// <item>
        /// Result::WarningBufferTruncated: The entire column value could not be 
        /// retrieved because the given buffer is smaller than the size of the column.
        /// </item>
        /// <item>
        /// Result::WarningColumnNull: The column value retrieved is NULL.
        /// </item>
        /// </list>
        /// <para>
        /// On success, the column value for the given column, is copied into the given 
        /// buffer. If Less than all of the column value is copied then the warning 
        /// Result::WarningBufferTruncated is returned  If the actualDataSize was given, 
        /// the actual size of the column value is returned. Note that NULL values have 
        /// 0 (zero) length and will thus set the returned size to 0 (zero). If the 
        /// column retrieved was a multi-valued column, and pretinfo was given, and 
        /// RetrieveFlags::Tag must be set as an option in retrieveFlags, then the 
        /// sequence number of the column value is returned in pretinfo->itagSequence.
        /// </para>
        /// <para>
        /// On failure, the cursor location is left unchanged and no data is copied 
        /// into the provided buffer.
        /// </para>
        /// </returns>
        /// <remarks>
        /// <para>
        /// This call is used just once to retrieve data of fixed or known size for 
        /// non-multi-valued columns. However, when column data is of unknown size, 
        /// this call is typically used twice. It is called first to determine the 
        /// size of the data so it can allocate the necessary storage space. Then, the 
        /// same call is made again to retrieve the column data. When the actual 
        /// number of values is unknown, because a column is multi-valued, the call 
        /// is typically used three times. First to get the number of values and then 
        /// twice more to allocate storage and retrieve the actual data.
        /// </para>
        /// <para>
        /// Retrieving all the values for a multi-valued column can be done by repeatedly 
        /// calling this function with a pretinfo->itagSequence value beginning at 1 and 
        /// increasing on each subsequent call. The last column value is known to be 
        /// retrieved when a Result::WarningColumnNull is returned from the function. Note that 
        /// this method cannot be done if the multi-value column has explicit NULL values set 
        /// in its value sequence, since these values would be skipped. If an application 
        /// desires to retrieve all multi-valued column values, including those explicitly set 
        /// to NULL, then Table::RetrieveColumns must be used instead of Table::RetrieveColumn. 
        /// Note that this function does not return the number of values for a multi-valued 
        /// function when an itagSequence value of 0 (zero) is given. Only Table::RetrieveColumns 
        /// will return the number of values of a column value when an itagSequence value of 0 
        /// (zero) is passed.
        /// </para>
        /// <para>
        /// If this function is called at transaction level 0 (zero), for example, the calling 
        /// session is not itself in a transaction, then a transaction is opened and closed 
        /// within the function. The purpose of this is to return consistent results in the 
        /// case that a long value spans database pages. Note that the transaction is 
        /// released between function calls and a series of calls to this function when the 
        /// session is not in a transaction may return data updated after the first call to 
        /// this function.
        /// </para>
        /// <para>
        /// The default column value will be retrieved when the column has not been set 
        /// explicitly to another value, unless the RetrieveFlags::IgnoreDefault option is 
        /// set in retrieveFlags.
        /// </para>
        /// <para>
        /// Retrieving the autoincrement column value from the copy buffer prior to insert is 
        /// a common means of identifying a record uniquely for linkage when inserting normalized 
        /// data into multiple tables. The autoincrement value is allocated when the insert 
        /// operation begins and can be retrieved from the copy buffer at any time until the 
        /// update is complete.
        /// </para>
        /// <para>
        /// When retrieving all tagged, multi-valued, and sparse columns, by setting columnId to 
        /// 0 (zero), columns are retrieved in column id order from lowest column id to highest 
        /// column id. The same order of column values is returned each time column values are 
        /// retrieved. The order is deterministic.
        /// </para>
        /// </remarks>
        Ese::Result RetrieveColumn( JET_COLUMNID columnId, void* dataBuffer, unsigned long dataBufferSize, unsigned long* actualDataSize, RetrieveFlags retrieveFlags, JET_RETINFO* pretinfo = nullptr ) const
        {
            auto rc = static_cast< Result >( JetRetrieveColumn( sessionId_, tableId_, columnId, dataBuffer, dataBufferSize, actualDataSize, static_cast< int >( retrieveFlags ), pretinfo ) );
            if ( rc != Result::Success &&
                rc != Result::WarningBufferTruncated &&
                rc != Result::WarningColumnNull )
            {
                HCC_THROW( Exception, rc );
            }
            return rc;
        }

        /// <summary>
        /// Retrieves the size of the data stored in
        /// a multi-valued column.
        /// </summary>
        /// <param name="columnId">
        /// The column id of the column to retrieve.
        /// </param>
        /// <param name="itagSequence">
        /// The itagSequence number of the value to 
        /// retrieve the size of.
        /// </param>
        /// <param name="retrieveFlags">
        /// Zero or more values from the RetrieveFlags enumeration. The values can be
        /// combined using the <c>|</c> operator. Must include RetrieveFlags::Tag.
        /// </param>
        /// <returns>
        /// The size of the value identified by columnId and itagSequence.
        /// </returns>
        unsigned long RetrieveColumnSize( JET_COLUMNID columnId, int itagSequence, RetrieveFlags retrieveFlags = RetrieveFlags::Tag ) const
        {
            JET_RETINFO retinfo = { sizeof( JET_RETINFO ), 0, static_cast<ULONG>( itagSequence ), 0 };
            unsigned long dataSize = 0;
            Byte buffer[ 1 ] = {};
            auto rc = RetrieveColumn( columnId, buffer, 1, &dataSize, retrieveFlags, &retinfo );
            if ( rc == Result::WarningColumnNull )
            {
                return 0;
            }
            return dataSize;
        }

        /// <summary>
        /// Retrieves the size of the data stored in
        /// a column.
        /// </summary>
        /// <param name="columnId">
        /// The column id of the column to retrieve.
        /// </param>
        /// <param name="retrieveFlags">
        /// Zero or more values from the RetrieveFlags enumeration. The values can be
        /// combined using the <c>|</c> operator. Must not include RetrieveFlags::Tag.
        /// </param>
        /// <returns>
        /// The size of the data stored in the column identified by columnId.
        /// </returns>
        unsigned long RetrieveColumnSize( JET_COLUMNID columnId, RetrieveFlags retrieveFlags = RetrieveFlags::None ) const
        {
            unsigned long dataSize = 0;
            auto rc = RetrieveColumn( columnId, nullptr, 0, &dataSize, retrieveFlags , nullptr );
            if ( rc == Result::WarningColumnNull )
            {
                return 0;
            }
            return dataSize;
        }

        /// <summary>
        /// Tests if the data stored in
        /// a column in NULL.
        /// </summary>
        /// <param name="columnId">
        /// The column id of the column to retrieve.
        /// </param>
        /// <param name="retrieveFlags">
        /// Zero or more values from the RetrieveFlags enumeration. The values can be
        /// combined using the <c>|</c> operator. Must not include RetrieveFlags::Tag.
        /// </param>
        /// <returns>
        /// The size of the value identified by columnId and itagSequence.
        /// </returns>
        bool IsDBNull(JET_COLUMNID columnId, RetrieveFlags retrieveFlags = RetrieveFlags::None) const
        {
            unsigned long dataSize = 0;
            Byte buffer[ 1 ] = {};
            auto rc = RetrieveColumn(columnId, buffer, 1, &dataSize, retrieveFlags );
            return rc == Result::WarningColumnNull;
        }


        

        /// <summary>
        /// <para>
        /// Retrieves multiple column values from the current record in a single operation. 
        /// An array of JET_RETRIEVECOLUMN structures or Ese::RetrieveColumn objects is used 
        /// to describe the set of column values to be retrieved, and to describe output 
        /// buffers for each column value to be retrieved.
        /// </para>
        /// <para>
        /// Retrieving multiple column values using RetrieveColumns is usually significantly
        /// faster than retrieving the data for individual columns using Table::RetrieveColumn.
        /// </para>
        /// </summary>
        /// <typeparam name="RetrieveColumnT">
        /// JET_RETRIEVECOLUMN, Ese::RetrieveColumn, or a type
        /// derived from either them with the same size as JET_RETRIEVECOLUMN.
        /// </typeparam>
        /// <param name="retrieveColumns">
        /// A pointer to an array of one or more JET_RETRIEVECOLUMN structures or 
        /// Ese::RetrieveColumn objects. Each object provides descriptions of which 
        /// column value to retrieve and where to store returned data.
        /// </param>
        /// <param name="columnCount">
        /// The number of elements in the array given by retrieveColumns.
        /// </param>
        /// <returns>
        /// <para>
        /// One of the following values from the Ese::Result enumeration.
        /// </para>
        /// <list type="bullet">
        /// <item>
        /// Ese::Result::Success: The operation completed successfully.
        /// </item>
        /// <item>
        /// Ese::Result::WarningBufferTruncated: The entire column value could 
        /// not be retrieved because the given buffer is smaller than the size of the column.
        /// </item>
        /// </list>
        /// </returns>
        template<typename RetrieveColumnT>
            requires ( std::is_base_of_v< JET_RETRIEVECOLUMN, RetrieveColumnT> || std::is_base_of_v< Ese::RetrieveColumn, RetrieveColumnT> ) &&
                ( sizeof( RetrieveColumnT ) == sizeof( JET_RETRIEVECOLUMN ) )
        Ese::Result RetrieveColumns( RetrieveColumnT* retrieveColumns, unsigned long columnCount ) const
        {
            auto rc = static_cast<Result>( JetRetrieveColumns( sessionId_, tableId_, reinterpret_cast< JET_RETRIEVECOLUMN* >( retrieveColumns ), columnCount ) );
            if ( rc != Result::Success &&
                rc != Result::WarningBufferTruncated )
            {
                HCC_THROW( Exception, rc );
            }
            return rc;
        }
        /// <summary>
        /// Retrieves multiple column values from the current record in a single operation. 
        /// An array of JET_RETRIEVECOLUMN structures or Ese::RetrieveColumn objects is used 
        /// to describe the set of column values to be retrieved, and to describe output 
        /// buffers for each column value to be retrieved.
        /// </summary>
        /// <typeparam name="SpanT">
        /// Any type that matches the SimpleSpanLike concept
        /// with a value_type of JET_RETRIEVECOLUMN, Ese::RetrieveColumn, or a type
        /// derived from either them with the same size as JET_RETRIEVECOLUMN.
        /// </typeparam>
        /// <param name="retrieveColumns">
        /// A reference to a container of one or more JET_RETRIEVECOLUMN structures or 
        /// Ese::RetrieveColumn objects. Each object provides descriptions of which 
        /// column value to retrieve and where to store returned data.
        /// </param>
        /// <returns>
        /// <para>
        /// One of the following values from the Ese::Result enumeration.
        /// </para>
        /// <list type="bullet">
        /// <item>
        /// Ese::Result::Success: The operation completed successfully.
        /// </item>
        /// <item>
        /// Ese::Result::WarningBufferTruncated: The entire column value could 
        /// not be retrieved because the given buffer is smaller than the size of the column.
        /// </item>
        /// </list>
        /// </returns>
        /// <remarks>
        /// <code>
        /// void ReadSensorPoint( const Ese::Table& table, SensorPoint& sensorPoint ) const
        /// {
        ///     Int64 timestamp = 0;
        ///     std::array<Ese::RetrieveColumn, 3> retrieveColumns;
        ///     retrieveColumns[ 0 ].Bind( timestampColumnId_, timestamp );
        ///     retrieveColumns[ 1 ].Bind( flagsColumnId_, sensorPoint.Flags );
        ///     retrieveColumns[ 2 ].Bind( valueColumnId_, sensorPoint.Value );
        ///     table.RetrieveColumns( retrieveColumns );
        ///     sensorPoint.Timestamp = DateTime( timestamp );
        /// }
        /// </code>
        /// </remarks>
        template<SimpleSpanLike SpanT>
            requires (std::is_base_of_v< JET_RETRIEVECOLUMN, typename SpanT::value_type> || std::is_base_of_v< Ese::RetrieveColumn, typename SpanT::value_type>) &&
            (sizeof( typename SpanT::value_type ) == sizeof( JET_RETRIEVECOLUMN ))
        Ese::Result RetrieveColumns( SpanT& retrieveColumns ) const
        {
            return RetrieveColumns( reinterpret_cast< JET_RETRIEVECOLUMN* >(retrieveColumns.data()), static_cast<unsigned long>(retrieveColumns.size()) );
        }


        /// <summary>
        /// Modifies a single column value in a modified record to be 
        /// inserted or to update the current record. It can overwrite an 
        /// existing value, add a new value to a sequence of values in a 
        /// multi-valued column, remove a value from a sequence of values 
        /// in a multi-valued column, or update all or part of a long 
        /// value, a column of type ColumnType::LongBinary or ColumnType::LongText.
        /// </summary>
        /// <param name="columnId">
        /// The JET_COLUMNID of the column to be modified.
        /// </param>
        /// <param name="dataBuffer">
        /// Input buffer containing data to store in the column.
        /// </param>
        /// <param name="dataBufferSize">
        /// Size in bytes of the input buffer.
        /// </param>
        /// <param name="flags">
        /// Zero or more values from the SetFlags enumeration. The values can be
        /// combined using the <c>|</c> operator. Use SetFlags::None to specify
        /// that no flags from the SetFlags enumeration will be set.
        /// </param>
        /// <param name="psetinfo">
        /// <para>
        /// Pointer to optional input parameters that can be set for this function using the JET_SETINFO structure.
        /// </para>
        /// <para>
        /// If psetinfo is given as nullotr then the function behaves as though 
        /// an itagSequence of 1 and an ibLongValue of 0 (zero) were given. This 
        /// causes column set to set the first value of a multi-valued column, 
        /// and to set long data beginning at offset 0 (zero).
        /// </para>
        /// <para>
        /// The following options can be set for this parameter:
        /// </para>
        /// <list type="bullet">
        /// <item>
        /// ibLongValue: Binary offset into a long column value where set data should begin.
        /// </item>
        /// <item>
        /// itagSequence: Sequence number of the desired multi-valued column value to set. 
        /// If itagSequence is set to 0 (zero), then the value provided should be appended 
        /// to then end of the sequence of multi-valued values. If the sequence number 
        /// provided is greater than the last existing multi-valued value, then again the given 
        /// value is appended to the end of the sequence of values. If the sequence number 
        /// corresponds to an existing value then that value is replaced with the given value.
        /// </item>
        /// </list>
        /// </param>
        void SetColumn( JET_COLUMNID columnId, const void* dataBuffer, unsigned long dataBufferSize, SetFlags flags, JET_SETINFO* psetinfo ) const
        {
            auto rc = static_cast< Result >( JetSetColumn( sessionId_, tableId_, columnId, dataBuffer, dataBufferSize, static_cast< int >( flags ), psetinfo ) );
            RequireSuccess( rc );
        }

        /// <summary>
        /// Set multiple column values in a single operation. An array of 
        /// JET_SETCOLUMN structures, or Ese::SetColumn objects, is used to 
        /// describe the set of column values to be set, and to describe 
        /// input buffers for each column value to be set.
        /// </summary>
        /// <typeparam name="SetColumnT">
        /// Either JET_SETCOLUMN or Ese::SetColumn, or a type derived
        /// from either of them with the same size as JET_SETCOLUMN.
        /// </typeparam>
        /// <param name="setColumns">
        /// A pointer to an array of one or more JET_SETCOLUMN structures or 
        /// Ese::SetColumn objects. Each object provides descriptions of 
        /// which column value to set and from where to get the column data 
        /// to set.
        /// </param>
        /// <param name="count">
        /// The number of elements in the array given by setColumns.
        /// </param>
        template<typename SetColumnT>
            requires ( std::is_base_of_v< JET_SETCOLUMN, SetColumnT> || std::is_base_of_v< Ese::SetColumn, SetColumnT> ) &&
                ( sizeof( SetColumnT ) == sizeof( JET_SETCOLUMN ) )
        void SetColumns( SetColumnT* setColumns, unsigned long count ) const
        {
            auto rc = static_cast<Result>( JetSetColumns( sessionId_, tableId_, reinterpret_cast< JET_SETCOLUMN* >( setColumns ), count ) );
            RequireSuccess( rc );
        }

        /// <summary>
        /// Set multiple column values in a single operation. An array of 
        /// JET_SETCOLUMN structures, or Ese::SetColumn objects, is used to 
        /// describe the set of column values to be set, and to describe 
        /// input buffers for each column value to be set.
        /// </summary>
        /// <typeparam name="SpanT">
        /// Any type that matches the SimpleSpanLike concept
        /// with a value_type of JET_SETCOLUMN, Ese::SetColumn, or a type
        /// derived from either them with the same size as JET_SETCOLUMN.
        /// </typeparam>
        /// <param name="setColumns">
        /// A const reference to a container of one or more JET_SETCOLUMN structures or 
        /// Ese::SetColumn objects. Each object provides descriptions of 
        /// which column value to set and from where to get the column data 
        /// to set.
        /// </param>
        template<SimpleSpanLike SpanT>
            requires (std::is_base_of_v< JET_SETCOLUMN, typename SpanT::value_type> || std::is_base_of_v< Ese::SetColumn, typename SpanT::value_type>) &&
                (sizeof( typename SpanT::value_type ) == sizeof( JET_SETCOLUMN ))
        void SetColumns( SpanT& setColumns ) const
        {
            return SetColumns( setColumns.data(), static_cast<unsigned long>( setColumns.size()) );
        }

        /// <summary>
        /// Retrieves information about a table column.
        /// </summary>
        /// <param name="columnName">
        /// The name of the column to fetch information for.
        /// </param>
        /// <param name="resultData">
        /// Pointer to a buffer that will receive the information. The type 
        /// of the buffer is dependent on columnInfoFlags. The caller must 
        /// be configured to align the buffer appropriately.
        /// </param>
        /// <param name="resultDataSize">
        /// The size, in bytes, of the buffer that was passed in resultData.
        /// </param>
        /// <param name="columnInfoFlags">
        /// A value from the ColumnInfoLevel enumeration.
        /// </param>
        void GetTableColumnInfo( const wchar_t* columnName, void* resultData, unsigned long resultDataSize, ColumnInfoLevel columnInfoFlags ) const
        {
            auto rc = static_cast<Result>( JetGetTableColumnInfoW( sessionId_, tableId_, columnName, resultData, resultDataSize, static_cast<unsigned long>(columnInfoFlags) ) );
            RequireSuccess( rc );
        }

        /// <summary>
        /// Retrieves information about a table column.
        /// </summary>
        /// <param name="columnName">
        /// The name of the column to fetch information for.
        /// </param>
        /// <param name="resultData">
        /// Pointer to a buffer that will receive the information. The type 
        /// of the buffer is dependent on columnInfoFlags. The caller must 
        /// be configured to align the buffer appropriately.
        /// </param>
        /// <param name="resultDataSize">
        /// The size, in bytes, of the buffer that was passed in resultData.
        /// </param>
        /// <param name="columnInfoFlags">
        /// A value from the ColumnInfoLevel enumeration.
        /// </param>
        void GetTableColumnInfo( const char* columnName, void* resultData, unsigned long resultDataSize, ColumnInfoLevel columnInfoFlags ) const
        {
            auto rc = static_cast<Result>( JetGetTableColumnInfoA( sessionId_, tableId_, columnName, resultData, resultDataSize, static_cast<unsigned long>( columnInfoFlags ) ) );
            RequireSuccess( rc );
        }

        /// <summary>
        /// Retrieves information about a table column.
        /// </summary>
        /// <param name="columnName">
        /// The name of the column to fetch information for.
        /// </param>
        /// <typeparam name="StringT">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <param name="resultData">
        /// Pointer to a buffer that will receive the information. The type 
        /// of the buffer is dependent on columnInfoFlags. The caller must 
        /// be configured to align the buffer appropriately.
        /// </param>
        /// <param name="resultDataSize">
        /// The size, in bytes, of the buffer that was passed in resultData.
        /// </param>
        /// <param name="columnInfoFlags">
        /// A value from the ColumnInfoLevel enumeration.
        /// </param>
        template<SimpleStringLike StringT>
        void GetTableColumnInfo( const StringT& columnName, void* resultData, unsigned long resultDataSize, ColumnInfoLevel columnInfoFlags ) const
        {
            auto rc = GetTableColumnInfo( columnName.c_str(), resultData, resultDataSize, columnInfoFlags );
            RequireSuccess( rc );
        }

        /// <summary>
        /// Retrieves information about a table column.
        /// </summary>
        /// <param name="columnName">
        /// The name of the column to fetch information for.
        /// </param>
        /// <param name="data">
        /// A reference to a JET_COLUMNDEF object.
        /// </param>
        void GetTableColumnInfo( const wchar_t* columnName, JET_COLUMNDEF& data ) const
        {
            GetTableColumnInfo( columnName, &data, sizeof( JET_COLUMNDEF ), ColumnInfoLevel::Default );
        }

        /// <summary>
        /// Retrieves information about a table column.
        /// </summary>
        /// <param name="columnName">
        /// The name of the column to fetch information for.
        /// </param>
        /// <param name="data">
        /// A reference to a JET_COLUMNBASE_W object.
        /// </param>
        void GetTableColumnInfo( const wchar_t* columnName, JET_COLUMNBASE_W& data ) const
        {
            GetTableColumnInfo( columnName, &data, sizeof( JET_COLUMNBASE_W ), ColumnInfoLevel::Base );
        }

        /// <summary>
        /// Retrieves information about a table column.
        /// </summary>
        /// <param name="columnName">
        /// The name of the column to fetch information for.
        /// </param>
        /// <param name="data">
        /// A reference to a JET_COLUMNLIST object. A temporary table 
        /// is opened and is identified by the tableid member of 
        /// JET_COLUMNLIST. The table must be closed with JetCloseTable. 
        /// If this function fails, the structure contains undefined data.
        /// </param>
        void GetTableColumnInfo( const wchar_t* columnName, JET_COLUMNLIST& data ) const
        {
            GetTableColumnInfo( columnName, &data, sizeof( JET_COLUMNLIST ), ColumnInfoLevel::List );
        }

        /// <summary>
        /// Retrieves information about a table column.
        /// </summary>
        /// <param name="columnName">
        /// The name of the column to fetch information for.
        /// </param>
        /// <param name="data">
        /// A reference to a JET_COLUMNDEF object.
        /// </param>
        void GetTableColumnInfo( const char* columnName, JET_COLUMNDEF& data ) const
        {
            GetTableColumnInfo( columnName, &data, sizeof( JET_COLUMNDEF ), ColumnInfoLevel::Default );
        }

        /// <summary>
        /// Retrieves information about a table column.
        /// </summary>
        /// <param name="columnName">
        /// The name of the column to fetch information for.
        /// </param>
        /// <param name="data">
        /// A reference to a JET_COLUMNBASE_A object.
        /// </param>
        void GetTableColumnInfo( const char* columnName, JET_COLUMNBASE_A& data ) const
        {
            GetTableColumnInfo( columnName, &data, sizeof( JET_COLUMNBASE_A ), ColumnInfoLevel::Base );
        }

        /// <summary>
        /// Retrieves information about a table column.
        /// </summary>
        /// <param name="columnName">
        /// The name of the column to fetch information for.
        /// </param>
        /// <param name="data">
        /// A reference to a JET_COLUMNLIST object. A temporary table 
        /// is opened and is identified by the tableid member of 
        /// JET_COLUMNLIST. The table must be closed with JetCloseTable. 
        /// If this function fails, the structure contains undefined data.
        /// </param>
        void GetTableColumnInfo( const char* columnName, JET_COLUMNLIST& data ) const
        {
            GetTableColumnInfo( columnName, &data, sizeof( JET_COLUMNLIST ), ColumnInfoLevel::List );
        }

        /// <summary>
        /// Retrieves information about a table column.
        /// </summary>
        /// <typeparam name="StringT">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <param name="columnName">
        /// The name of the column to fetch information for.
        /// </param>
        /// <param name="data">
        /// A reference to a JET_COLUMNDEF object.
        /// </param>
        template<SimpleStringLike StringT>
        void GetTableColumnInfo( const StringT& columnName, JET_COLUMNDEF& data ) const
        {
            GetTableColumnInfo( columnName, &data, sizeof( JET_COLUMNDEF ), ColumnInfoLevel::Default );
        }

        /// <summary>
        /// Retrieves information about a table column.
        /// </summary>
        /// <typeparam name="ColumnBaseT">
        /// Either JET_COLUMNBASE_W or JET_COLUMNBASE_A.
        /// </typeparam>
        /// <typeparam name="StringT">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <param name="columnName">
        /// The name of the column to fetch information for.
        /// </param>
        /// <param name="data">
        /// A reference to a JET_COLUMNBASE_W or JET_COLUMNBASE_A object.
        /// </param>
        template<SimpleStringLike StringT, typename ColumnBaseT>
            requires (SimpleWideStringLike<StringT> && std::is_same_v<ColumnBaseT, JET_COLUMNBASE_W> ) ||
                    ( SimpleAnsiStringLike<StringT> && std::is_same_v<ColumnBaseT, JET_COLUMNBASE_A> )
        void GetTableColumnInfo( const StringT& columnName, ColumnBaseT& data ) const
        {
            GetTableColumnInfo( columnName, &data, sizeof( JET_COLUMNBASE_A ), ColumnInfoLevel::Base );
        }

        /// <summary>
        /// Retrieves information about a table column.
        /// </summary>
        /// <typeparam name="StringT">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <param name="columnName">
        /// The name of the column to fetch information for.
        /// </param>
        /// <param name="data">
        /// A reference to a JET_COLUMNLIST object. A temporary table 
        /// is opened and is identified by the tableid member of 
        /// JET_COLUMNLIST. The table must be closed with JetCloseTable. 
        /// If this function fails, the structure contains undefined data.
        /// </param>
        template<SimpleStringLike StringT>
        void GetTableColumnInfo( const StringT& columnName, JET_COLUMNLIST& data ) const
        {
            GetTableColumnInfo( columnName, &data, sizeof( JET_COLUMNLIST ), ColumnInfoLevel::List );
        }

        /// <summary>
        /// Retrieves information about the columns of a table.
        /// </summary>
        /// <typeparam name="StringT">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <returns>
        /// A ColumnList<StringT> providing access to information
        /// about the columns of the table.
        /// </returns>
        template<StringLike StringT>
        ColumnList<StringT> GetColumns( ) const;

        /// <summary>
        /// The PrepareUpdate function is the first operation in performing 
        /// an update, for the purposes of inserting a new record or replacing 
        /// an existing record with new values. Updates are done by calling 
        /// Table::PrepareUpdate, then calling Table::SetColumn or 
        /// Table::SetColumns zero or more times and finally by calling 
        /// Table::Store to complete the operation. Table::PrepareUpdate and 
        /// Table::Store set the boundaries for an update operation and are 
        /// important in having only the final update state of a record entered 
        /// into indexes. This is both more efficient, but also required in cases 
        /// where data must match a valid state through more than on set column 
        /// operation.
        /// </summary>
        /// <param name="option">
        /// A value from the PrepareUpdateOptions enumeration.
        /// </param>
        void PrepareUpdate( PrepareUpdateOptions option ) const
        {
            auto rc = static_cast<Result>( JetPrepareUpdate( sessionId_, tableId_, static_cast<unsigned long>( option ) ) );
            RequireSuccess( rc );
        }

        /// <summary>
        /// Cancels the current update for this cursor
        /// </summary>
        void Cancel( ) const
        {
            PrepareUpdate( PrepareUpdateOptions::Cancel );
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
            PrepareUpdate( PrepareUpdateOptions::Copy );
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
            PrepareUpdate( PrepareUpdateOptions::Insert );
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
            PrepareUpdate( PrepareUpdateOptions::Replace );
        }

        /// <summary>
        /// Prepares the cursor for an insert of the same record, 
        /// and a delete or the original record. It is used in cases 
        /// in which the primary key has changed.
        /// </summary>
        void InsertCopyDeleteOriginal( ) const
        {
            PrepareUpdate( PrepareUpdateOptions::InsertCopyDeleteOriginal );
        }

        /// <summary>
        /// Performs an update operation including inserting a new 
        /// row into a table or updating an existing row
        /// </summary>
        void Store( ) const
        {
            auto rc = static_cast<Result>( JetUpdate( sessionId_, tableId_, nullptr, 0, nullptr ) );
            RequireSuccess( rc );
        }

        /// <summary>
        /// Performs an atomic addition operation on one column. This function allows 
        /// multiple sessions to update the same record concurrently without conflicts.
        /// </summary>
        /// <param name="columnId">
        /// <para>
        /// The column id of the column to be updated.
        /// </para>
        /// <para>
        /// This column must have a column type of ColumnType::Long with 
        /// the ColumnFlags::EscrowUpdate bit set.
        /// </para>
        /// </param>
        /// <param name="addendum">
        /// The addend for the column.
        /// </param>
        /// <param name="escrowNoRollback">
        /// If true, then even if the session performing the escrow update has its transaction 
        /// rollback this update will not be undone, otherwise false. Note that as the log records may not be 
        /// flushed to disk, recent escrow updates done with this flag may be lost if there is a crash. 
        /// </param>
        /// <returns></returns>
        Int32 EscrowUpdate(__in JET_COLUMNID columnId, Int32 addendum, __in bool escrowNoRollback = false )
        {
            Int32 oldValue = 0;
            unsigned long bytesRetrieved = 0;
            auto rc = static_cast< Result >( JetEscrowUpdate( sessionId_, tableId_, columnId, &addendum, sizeof( addendum ),&oldValue, sizeof( oldValue ),&bytesRetrieved, escrowNoRollback? JET_bitEscrowNoRollback : 0) );
            RequireSuccess( rc );
            return oldValue;
        }

        /// <summary>
        /// Deletes the current record in a table
        /// </summary>
        void Delete( ) const
        {
            auto rc = static_cast<Result>( JetDelete( sessionId_, tableId_ ) );
            RequireSuccess( rc );
        }

        /// <summary>
        /// The SetSequential function notifies the database engine that the 
        /// application is scanning the entire current index that contains a 
        /// given cursor. Consequently, the methods that are used to access 
        /// the index data will be tuned to make this scenario as fast as possible.
        /// </summary>
        /// <param name="flags">
        /// A value from the SequentialFlags enumeration.
        /// </param>
        void SetSequential( SequentialFlags flags = SequentialFlags::PrereadForward ) const
        {
            auto rc = static_cast<Result>( JetSetTableSequential( sessionId_, tableId_, static_cast<JET_GRBIT>( flags ) ) );
            RequireSuccess( rc );
        }




        /// <summary>
        /// Retrieves the column id for the column identified by the columnName
        /// argument.
        /// </summary>
        /// <typeparam name="T">
        /// Either char or wchar_t
        /// </typeparam>
        /// <param name="columnName">
        /// The name of the column to retrieve the column id for.
        /// </param>
        /// <returns>
        /// The requested column id.
        /// </returns>
        template<ApiCharType T>
        JET_COLUMNID GetColumnId( const T* columnName )
        {
            JET_COLUMNDEF columnDef = { sizeof( JET_COLUMNDEF ), 0, };
            GetTableColumnInfo( columnName, columnDef );
            return columnDef.columnid;
        }

        /// <summary>
        /// Retrieves the column id for the column identified by the columnName
        /// argument.
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <param name="columnName">
        /// The name of the column to retrieve the column id for.
        /// </param>
        /// <returns>
        /// The requested column id.
        /// </returns>
        template<SimpleStringLike T>
        JET_COLUMNID GetColumnId( const T& columnName )
        {
            return GetColumnId( columnName.c_str() );
        }

        /// <summary>
        /// Adds a new column to an existing table in an ESE database.
        /// </summary>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="columnDef">
        /// A const reference to a JET_COLUMNDEF structure.
        /// </param>
        /// <param name="defaultValueBuffer">
        /// <para>
        /// A pointer to a buffer that contains the default value for the column. The 
        /// length of the buffer is defaultValueBufferSize. If there is no default, 
        /// set defaultValueBuffer to nullptr and defaultValueBufferSize to zero. Default 
        /// values cannot be larger than JET_cbColumnMost bytes for fixed columns or 
        /// JET_cbLVDefaultValueMost bytes for long values. If a default value is larger 
        /// than that, it will be silently truncated.
        /// </para>
        /// <para>
        /// If the grbit field of the JET_COLUMNDEF structure has ColumnFlags::UserDefinedDefault 
        /// set, defaultValueBuffer will be interpreted as a pointer to a JET_USERDEFINEDDEFAULT 
        /// structure.
        /// </para>
        /// </param>
        /// <param name="defaultValueBufferSize">
        /// The size, in bytes, of the buffer that is specified in defaultValueBuffer.
        /// </param>
        /// <returns>
        /// The identifier of the newly created column.
        /// </returns>
        JET_COLUMNID AddColumn( const wchar_t* columnName, const JET_COLUMNDEF& columnDef, const void* defaultValueBuffer = nullptr, unsigned long defaultValueBufferSize = 0 ) const
        {
            
            JET_COLUMNID result = 0;
            auto rc = static_cast<Result>( JetAddColumnW( sessionId_, tableId_, columnName, &columnDef, defaultValueBuffer, defaultValueBufferSize, &result ) );
            RequireSuccess( rc );
            return result;
        }

        /// <summary>
        /// Adds a new column to an existing table in an ESE database.
        /// </summary>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="columnDef">
        /// A const reference to a JET_COLUMNDEF structure.
        /// </param>
        /// <param name="defaultValueBuffer">
        /// <para>
        /// A pointer to a buffer that contains the default value for the column. The 
        /// length of the buffer is defaultValueBufferSize. If there is no default, 
        /// set defaultValueBuffer to nullptr and defaultValueBufferSize to zero. Default 
        /// values cannot be larger than JET_cbColumnMost bytes for fixed columns or 
        /// JET_cbLVDefaultValueMost bytes for long values. If a default value is larger 
        /// than that, it will be silently truncated.
        /// </para>
        /// <para>
        /// If the grbit field of the JET_COLUMNDEF structure has ColumnFlags::UserDefinedDefault 
        /// set, defaultValueBuffer will be interpreted as a pointer to a JET_USERDEFINEDDEFAULT 
        /// structure.
        /// </para>
        /// </param>
        /// <param name="defaultValueBufferSize">
        /// The size, in bytes, of the buffer that is specified in defaultValueBuffer.
        /// </param>
        /// <returns>
        /// The identifier of the newly created column.
        /// </returns>
        JET_COLUMNID AddColumn( const char* columnName, const JET_COLUMNDEF& columnDef, const void* defaultValueBuffer = nullptr, unsigned long defaultValueBufferSize = 0 ) const
        {
            JET_COLUMNID result = 0;
            auto rc = static_cast<Result>( JetAddColumnA( sessionId_, tableId_, columnName, &columnDef, defaultValueBuffer, defaultValueBufferSize, &result ) );
            RequireSuccess( rc );
            return result;
        }

        /// <summary>
        /// Adds a new column to an existing table in an ESE database.
        /// </summary>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="columnDef">
        /// A const reference to a JET_COLUMNDEF structure.
        /// </param>
        /// <param name="defaultValueBuffer">
        /// <para>
        /// A pointer to a buffer that contains the default value for the column. The 
        /// length of the buffer is defaultValueBufferSize. If there is no default, 
        /// set defaultValueBuffer to nullptr and defaultValueBufferSize to zero. Default 
        /// values cannot be larger than JET_cbColumnMost bytes for fixed columns or 
        /// JET_cbLVDefaultValueMost bytes for long values. If a default value is larger 
        /// than that, it will be silently truncated.
        /// </para>
        /// <para>
        /// If the grbit field of the JET_COLUMNDEF structure has ColumnFlags::UserDefinedDefault 
        /// set, defaultValueBuffer will be interpreted as a pointer to a JET_USERDEFINEDDEFAULT 
        /// structure.
        /// </para>
        /// </param>
        /// <param name="defaultValueBufferSize">
        /// The size, in bytes, of the buffer that is specified in defaultValueBuffer.
        /// </param>
        /// <returns>
        /// The identifier of the newly created column.
        /// </returns>
        template<SimpleStringLike T>
        JET_COLUMNID AddColumn( const T& columnName, const JET_COLUMNDEF& columnDef, const void* defaultValueBuffer = nullptr, unsigned long defaultValueBufferSize = 0 ) const
        {
            return AddColumn( columnName.c_str(), columnDef, defaultValueBuffer, defaultValueBufferSize );
        }

        /// <summary>
        /// Adds a boolean column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The identifier of the newly created column.
        /// </returns>
        template<SimpleStringLike T>
        JET_COLUMNID AddBoolean( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Boolean, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds a boolean column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Either char or wchar_t.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The identifier of the newly created column.
        /// </returns>
        template<ApiCharType T>
        JET_COLUMNID AddBoolean( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Boolean, flags );
            return AddColumn( columnName, columnDef );
        }

        /// <summary>
        /// Adds a SByte column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The identifier of the newly created column.
        /// </returns>
        template<SimpleStringLike T>
        JET_COLUMNID AddSByte( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Byte, flags );
            return AddColumn( columnName, columnDef );
        }

        /// <summary>
        /// Adds a SByte column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Either char or wchar_t.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The identifier of the newly created column.
        /// </returns>
        template<ApiCharType T>
        JET_COLUMNID AddSByte( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Byte, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds a Byte column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<SimpleStringLike T>
        JET_COLUMNID AddByte( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Byte, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds a Byte column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Either char or wchar_t.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<ApiCharType T>
        JET_COLUMNID AddByte( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Byte, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds an Int16 column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<SimpleStringLike T>
        JET_COLUMNID AddInt16( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Short, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds an Int16 column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Either char or wchar_t.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<ApiCharType T>
        JET_COLUMNID AddInt16( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Short, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds an UInt16 column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<SimpleStringLike T>
        JET_COLUMNID AddUInt16( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::UnsignedShort, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds an UInt16 column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Either char or wchar_t.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<ApiCharType T>
        JET_COLUMNID AddUInt16( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::UnsignedShort, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds an Int32 column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<SimpleStringLike T>
        JET_COLUMNID AddInt32( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Long, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds an Int32 column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Either char or wchar_t.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<ApiCharType T>
        JET_COLUMNID AddInt32( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Long, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds an UInt32 column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<SimpleStringLike T>
        JET_COLUMNID AddUInt32( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::UnsignedLong, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds an UInt32 column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Either char or wchar_t.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<ApiCharType T>
        JET_COLUMNID AddUInt32( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::UnsignedLong, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds an Int64 column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<SimpleStringLike T>
        JET_COLUMNID AddInt64( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::LongLong, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds an Int64 column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Either char or wchar_t.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<ApiCharType T>
        JET_COLUMNID AddInt64( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::LongLong, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds an UInt64 column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<SimpleStringLike T>
        JET_COLUMNID AddUInt64( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::UnsignedLongLong, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds an UInt64 column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Either char or wchar_t.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<ApiCharType T>
        JET_COLUMNID AddUInt64( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::UnsignedLongLong, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds an single precision floating point column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<SimpleStringLike T>
        JET_COLUMNID AddSingle( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Single, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds an single precision floating point column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Either char or wchar_t.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<ApiCharType T>
        JET_COLUMNID AddSingle( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Single, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds an double precision floating point column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<SimpleStringLike T>
        JET_COLUMNID AddDouble( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Double, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds an double precision floating point column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Either char or wchar_t.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<ApiCharType T>
        JET_COLUMNID AddDouble( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Double, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds an Currency column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<SimpleStringLike T>
        JET_COLUMNID AddCurrency( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Currency, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds an Currency column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Either char or wchar_t.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<ApiCharType T>
        JET_COLUMNID AddCurrency( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Currency, flags );
            return AddColumn( columnName, columnDef );
        }

        /// <summary>
        /// <para>
        /// Adds an TimeSpan column to the table.
        /// </para>
        /// <para>
        /// ESE doesn't have a TimeSpan/duration type, this is an alias for 
        /// an Int64 column.
        /// </para>
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<SimpleStringLike T>
        JET_COLUMNID AddTimeSpan( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::LongLong, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// <para>
        /// Adds an TimeSpan column to the table.
        /// </para>
        /// <para>
        /// ESE doesn't have a TimeSpan/duration type, this is an alias for 
        /// an Int64 column.
        /// </para>
        /// </summary>
        /// <typeparam name="T">
        /// Either char or wchar_t.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<ApiCharType T>
        JET_COLUMNID AddTimeSpan( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::LongLong, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds an DateTime column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<SimpleStringLike T>
        JET_COLUMNID AddDateTime( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::DateTime, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds an DateTime column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Either char or wchar_t.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<ApiCharType T>
        JET_COLUMNID AddDateTime( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::DateTime, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds an Guid/uuid column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<SimpleStringLike T>
        JET_COLUMNID AddGuid( const T& columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Guid, sizeof(GUID) ,flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds an Guid/uuid column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Either char or wchar_t.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<ApiCharType T>
        JET_COLUMNID AddGuid( const T* columnName, ColumnFlags flags = ColumnFlags::Fixed | ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Guid, flags );
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds an text column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Either char or wchar_t.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="maxSize"></param>
        /// <param name="codePage"></param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<ApiCharType T>
        JET_COLUMNID AddText( const T* columnName, unsigned long maxSize = 127, short codePage = 1200, ColumnFlags flags = ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Text, maxSize, flags );
            if ( maxSize > 127 )
            {
                columnDef.coltyp = static_cast<JET_COLTYP>( ColumnType::LongText );
            }
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds an text column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="maxSize"></param>
        /// <param name="codePage"></param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<SimpleStringLike T>
        JET_COLUMNID AddText( const T& columnName, unsigned long maxSize = 127, short codePage = 1200, ColumnFlags flags = ColumnFlags::NotNULL ) const
        {
            return AddText( columnName.c_str( ), maxSize, codePage, flags );
        }
        /// <summary>
        /// Adds an binary column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Either char or wchar_t.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="maxSize"></param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<ApiCharType T>
        JET_COLUMNID AddBinary( const T* columnName, unsigned long maxSize = 255, ColumnFlags flags = ColumnFlags::NotNULL ) const
        {
            ColumnDefinition columnDef( ColumnType::Binary, maxSize, flags );
            if ( maxSize > 255 )
            {
                columnDef.coltyp = static_cast<JET_COLTYP>( ColumnType::LongBinary );
            }
            return AddColumn( columnName, columnDef );
        }
        /// <summary>
        /// Adds an binary column to the table.
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the SimpleStringLike concept.
        /// </typeparam>
        /// <param name="columnName">
        /// <para>
        /// The name of the column to add. The name must meet the following criteria:
        /// </para>
        /// <list>
        /// <item>
        /// It must be fewer than JET_cbNameMost characters in length, not including the terminating NULL.
        /// </item>
        /// <item>
        /// It must contain characters only from the following sets: 0 through 9, 
        /// A through Z, a through z, and all other punctuation except for exclamation 
        /// point (!), comma (,), opening bracket ([), and closing bracket (]) � that is, 
        /// ASCII characters 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It cannot begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="maxSize"></param>
        /// <param name="flags">
        /// One or more values from the ColumnFlags enumeration. 
        /// The values can be combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column id of the newly created column.
        /// </returns>
        template<SimpleStringLike T>
        JET_COLUMNID AddBinary( const AnsiString& columnName, unsigned long maxSize = 255, ColumnFlags flags = ColumnFlags::NotNULL ) const
        {
            return AddBinary( columnName.c_str( ), maxSize, flags );
        }

        
        /// <summary>
        /// Sets the column identified by columnId to NULL.
        /// </summary>
        /// <param name="columnid">
        /// The column id.
        /// </param>
        void SetNull( JET_COLUMNID columnid ) const
        {
            SetColumn( columnid, 0, 0, SetFlags::None, nullptr );
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
        /// <summary>
        /// Reads the column value from the column identified by columnId,
        /// returning true if the column contained a value, or false.
        /// if the column is NULL.
        /// </summary>
        /// <typeparam name="T">
        /// Any type matching the DirectType concept.
        /// </typeparam>
        /// <param name="columnId">
        /// The column id identifying the column.
        /// </param>
        /// <param name="value">
        /// A reference to a variable that will be assigned
        /// the value of the column.
        /// </param>
        /// <param name="retrieveFlags">
        /// Zero or more values from the RetrieveFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// true if a value was retried from the column, or false if the column is NULL.
        /// </returns>
        template<DirectType T>
        bool Read( JET_COLUMNID columnId, T& value, RetrieveFlags retrieveFlags = RetrieveFlags::None ) const
        {
            constexpr unsigned long DataSize = sizeof( std::decay_t<T> );
            unsigned long actualDataSize;
            auto rc = RetrieveColumn( columnId, &value, DataSize, &actualDataSize, retrieveFlags, nullptr );
            return CheckReadResult( rc );
        }

        /// <summary>
        /// Reads a bool value from the column identified by columnId,
        /// returning true if the column contained a value, or false.
        /// if the column is NULL.
        /// </summary>
        /// <param name="columnId">
        /// The column id identifying the column.
        /// </param>
        /// <param name="value">
        /// A reference to a bool variable that will be assigned
        /// the value of the column.
        /// </param>
        /// <param name="retrieveFlags">
        /// Zero or more values from the RetrieveFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// true if a value was retried from the column, or false if the column is NULL.
        /// </returns>
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
        /// <summary>
        /// Reads a DateTime value from the column identified by columnId,
        /// returning true if the column contained a value, or false.
        /// if the column is NULL.
        /// </summary>
        /// <param name="columnId">
        /// The column id identifying the column.
        /// </param>
        /// <param name="value">
        /// A reference to a DateTime variable that will be assigned
        /// the value of the column.
        /// </param>
        /// <param name="retrieveFlags">
        /// Zero or more values from the RetrieveFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// true if a value was retried from the column, or false if the column is NULL.
        /// </returns>
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

        /// <summary>
        /// Reads a std::chrono::system_clock::time_point value from the column identified by columnId,
        /// returning true if the column contained a value, or false.
        /// if the column is NULL.
        /// </summary>
        /// <param name="columnId">
        /// The column id identifying the column.
        /// </param>
        /// <param name="value">
        /// A reference to a std::chrono::system_clock::time_point variable that will be assigned
        /// the value of the column.
        /// </param>
        /// <param name="retrieveFlags">
        /// Zero or more values from the RetrieveFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// true if a value was retried from the column, or false if the column is NULL.
        /// </returns>
        bool Read( JET_COLUMNID columnId, std::chrono::system_clock::time_point& value, RetrieveFlags retrieveFlags = RetrieveFlags::None ) const
        {
            DateTime dateTime;
            auto result = Read( columnId, dateTime, retrieveFlags );
            if ( result )
            {
                value = dateTime.ToTimePoint( );
            }
            return result;
        }


        /// <summary>
        /// Reads a text value from the column identified by columnId,
        /// returning true if the column contained a value, or false.
        /// if the column is NULL.
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the StringLike concept.
        /// </typeparam>
        /// <param name="columnId">
        /// The column id identifying the column.
        /// </param>
        /// <param name="value">
        /// A reference to a string type variable that will be assigned
        /// the value of the column.
        /// </param>
        /// <param name="retrieveFlags">
        /// Zero or more values from the RetrieveFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// true if a value was retried from the column, or false if the column is NULL.
        /// </returns>
        template<StringLike T>
        bool Read( JET_COLUMNID columnId, T& value, RetrieveFlags retrieveFlags = RetrieveFlags::None ) const
        {
            using CharT = typename T::value_type;
            constexpr unsigned long BufferSize = 256;
            CharT buffer[BufferSize];
            unsigned long actualDataSize;
            auto rc = RetrieveColumn( columnId, buffer, BufferSize * sizeof( CharT ), &actualDataSize, retrieveFlags, nullptr );
            if ( rc == Result::WarningColumnNull )
            {
                return false;
            }

            if ( rc == Result::Success )
            {
                value.resize( actualDataSize / sizeof( CharT ) );
                memcpy( value.data( ), buffer, actualDataSize );
                return true;
            }
            else if ( rc == Result::WarningBufferTruncated )
            {
                unsigned long newDataSize;
                value.resize( actualDataSize / sizeof( CharT ) );
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

        /// <summary>
        /// Reads a binary value from the column identified by columnId,
        /// returning true if the column contained a value, or false.
        /// if the column is NULL.
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the StringLike concept.
        /// </typeparam>
        /// <param name="columnId">
        /// The column id identifying the column.
        /// </param>
        /// <param name="value">
        /// A reference to a container type variable that will be assigned
        /// the value of the column.
        /// </param>
        /// <param name="retrieveFlags">
        /// Zero or more values from the RetrieveFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// true if a value was retried from the column, or false if the column is NULL.
        /// </returns>
        template<BinaryLike T>
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

        /// <summary>
        /// Reads a binary value, into a IO::MemoryStream, from the column identified by columnId,
        /// returning true if the column contained a value, or false.
        /// if the column is NULL.
        /// </summary>
        /// <param name="columnId">
        /// The column id identifying the column.
        /// </param>
        /// <param name="value">
        /// A reference to a IO::MemoryStream that will be assigned
        /// the value of the column.
        /// </param>
        /// <param name="retrieveFlags">
        /// Zero or more values from the RetrieveFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// true if a value was retried from the column, or false if the column is NULL.
        /// </returns>
        bool Read( JET_COLUMNID columnId, IO::MemoryStream& value, RetrieveFlags retrieveFlags = RetrieveFlags::None ) const
        {
            unsigned long dataSize = RetrieveColumnSize( columnId, retrieveFlags );
            if ( dataSize )
            {
                value.SetSize( dataSize );
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

        /// <summary>
        /// Reads the column value from the column identified by columnId,
        /// returning std::optional<T>.
        /// </summary>
        /// <typeparam name="T">
        /// Any type for which there exists a Read overload.
        /// </typeparam>
        /// <param name="columnId">
        /// The column id identifying the column.
        /// </param>
        /// <param name="flags">
        /// Zero or more values from the RetrieveFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// The column value.
        /// </returns>
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
        /// <summary>
        /// Sets the value of a column identified by column id.
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the DirectType concept.
        /// </typeparam>
        /// <param name="columnid">
        /// The column id identifying the column.
        /// </param>
        /// <param name="value">
        /// A const reference to the variable holding the value
        /// to assign to the column.
        /// </param>
        /// <param name="flags">
        /// Zero or more values from the SetFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        template<DirectType T>
        void SetColumn( JET_COLUMNID columnid, const T& value, SetFlags flags = SetFlags::None ) const
        {
            SetColumn( columnid, &value, sizeof( std::decay_t<T> ), flags, nullptr );
        }

        /// <summary>
        /// Sets the DateTime value of a column identified by column id.
        /// </summary>
        /// <typeparam name="T">
        /// DateTime
        /// </typeparam>
        /// <param name="columnid">
        /// The column id identifying the column.
        /// </param>
        /// <param name="value">
        /// A const reference to the variable holding the value
        /// to assign to the column.
        /// </param>
        /// <param name="flags">
        /// Zero or more values from the SetFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        template<typename T>
            requires std::is_same_v<DateTime, T>
        void SetColumn( JET_COLUMNID columnid, const T& value, SetFlags flags = SetFlags::None ) const
        {
            auto data = value.ToOADate( );
            SetColumn( columnid, &data, sizeof( double ), flags, nullptr );
        }

        /// <summary>
        /// Sets the std::chrono::system_clock::time_point value of a column identified by column id.
        /// </summary>
        /// <typeparam name="T">
        /// std::chrono::system_clock::time_point
        /// </typeparam>
        /// <param name="columnid">
        /// The column id identifying the column.
        /// </param>
        /// <param name="value">
        /// A const reference to the variable holding the value
        /// to assign to the column.
        /// </param>
        /// <param name="flags">
        /// Zero or more values from the SetFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        template<typename T>
            requires std::is_same_v<std::chrono::system_clock::time_point, T>
        void SetColumn( JET_COLUMNID columnid, const T& value, SetFlags flags = SetFlags::None ) const
        {
            DateTime dateTime( value );
            auto data = dateTime.ToOADate( );
            SetColumn( columnid, &data, sizeof( double ), flags, nullptr );
        }
        /// <summary>
        /// Sets the bool value of a column identified by column id.
        /// </summary>
        /// <typeparam name="T">
        /// bool
        /// </typeparam>
        /// <param name="columnid">
        /// The column id identifying the column.
        /// </param>
        /// <param name="value">
        /// The bool value to assign to the column.
        /// </param>
        /// <param name="flags">
        /// Zero or more values from the SetFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        template<typename T>
            requires std::is_same_v<bool, T>
        void SetColumn( JET_COLUMNID columnid, T value, SetFlags flags = SetFlags::None ) const
        {
            Byte data = value ? 1 : 0;
            SetColumn( columnid, (const void*)&data, 1UL, flags, static_cast<JET_SETINFO*>(nullptr) );
        }

        /// <summary>
        /// Sets the text value of a column identified by column id.
        /// </summary>
        /// <typeparam name="T">
        /// Any string container that matches the SimpleCharSpanLike concept.
        /// </typeparam>
        /// <param name="columnId">
        /// The column id identifying the column.
        /// </param>
        /// <param name="text">
        /// A const reference to the string container holding the value
        /// to assign to the column.
        /// </param>
        /// <param name="flags">
        /// Zero or more values from the SetFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        template<SimpleCharSpanLike T>
        void SetColumn( JET_COLUMNID columnId, const T& text, SetFlags flags = SetFlags::None ) const
        {
            using CharT = typename T::value_type;
            DWORD length = static_cast<unsigned long>( text.size( ) * sizeof( CharT ) );
            if ( !length )
            {
                flags |= SetFlags::ZeroLength;
            }
            SetColumn( columnId, text.c_str( ), length, flags, nullptr );
        }
        /// <summary>
        /// Sets the binary value of a column identified by column id.
        /// </summary>
        /// <typeparam name="T">
        /// Any type that matches the SimpleByteSpanLike concept.
        /// </typeparam>
        /// <param name="columnId">
        /// The column id identifying the column.
        /// </param>
        /// <param name="value">
        /// A const reference to the binary container holding the value
        /// to assign to the column.
        /// </param>
        /// <param name="flags">
        /// Zero or more values from the SetFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        template<SimpleByteSpanLike T>
        void SetColumn( JET_COLUMNID columnId, const T& value, SetFlags flags = SetFlags::None ) const
        {
            DWORD length = static_cast<unsigned long>( value.size( ) );
            if ( !length )
            {
                flags |= SetFlags::ZeroLength;
            }
            SetColumn( columnId, value.data( ), length, flags, nullptr );
        }

        /// <summary>
        /// Reads binary data from a column of type ColumnType::LongBinary.
        /// </summary>
        /// <param name="columnId">
        /// The column id identifying the column.
        /// </param>
        /// <param name="data">
        /// A pointer to a buffer that will receive the data retrieved
        /// from the column.
        /// </param>
        /// <param name="dataSize">
        /// The size of the buffer provided for the data parameter.
        /// </param>
        /// <param name="columnOffset">
        /// The offset, in bytes, into the column value where the function will start reading from.
        /// </param>
        /// <param name="actualDataSize">
        /// A reference to a variable that receives the actual number of bytes retrieved by the function.
        /// </param>
        /// <param name="retrieveFlags">
        /// Zero or more values from the RetrieveFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        /// <returns>
        /// <list type="bullet">
        /// <item>
        /// Result::Success: The operation completed successfully.
        /// </item>
        /// <item>
        /// Result::WarningBufferTruncated: The entire column value could not be 
        /// retrieved because the given buffer is smaller than the size of the column.
        /// </item>
        /// <item>
        /// Result::WarningColumnNull: The column value retrieved is NULL.
        /// </item>
        /// </list>
        /// </returns>
        Ese::Result ReadBinary( JET_COLUMNID columnId, void* data, unsigned long dataSize, unsigned long columnOffset, unsigned long& actualDataSize, RetrieveFlags retrieveFlags = RetrieveFlags::None ) const
        {
            
            JET_RETINFO retinfo = { sizeof( JET_RETINFO ), static_cast< ULONG >( columnOffset ), 0, 0 };
            auto rc = RetrieveColumn( columnId, data, dataSize, &actualDataSize, retrieveFlags, &retinfo );
            return rc;
        }

        /// <summary>
        /// Writes binary data to a column of type ColumnType::LongBinary.
        /// </summary>
        /// <param name="columnid">
        /// The column id identifying the column.
        /// </param>
        /// <param name="data">
        /// A pointer to a buffer that contains the data that will be written
        /// to the column.
        /// </param>
        /// <param name="dataSize">
        /// The size of the buffer provided for the data parameter.
        /// </param>
        /// <param name="columnOffset">
        /// The offset, in bytes, into the column value where the function will start writing to.
        /// </param>
        /// <param name="flags">
        /// Zero or more values from the SetFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        void WriteBinary( JET_COLUMNID columnid, const void* data, unsigned long dataSize, unsigned long columnOffset, SetFlags flags = SetFlags::None ) const
        {
            JET_SETINFO setinfo = { sizeof( JET_SETINFO ), static_cast< ULONG >( columnOffset ), 0 };
            SetColumn( columnid, data, dataSize, flags, &setinfo );
        }

        /// <summary>
        /// Creates an index for the table.
        /// </summary>
        /// <param name="indexName">
        /// <para>
        /// A pointer to a null-terminated string that specifies the name of the index to be created.
        /// </para>
        /// <para>
        /// The index name must conform to the following guidelines:
        /// </para>
        /// <list>
        /// <item>
        /// It must contain fewer characters than JET_cbNameMost, not including the terminating null character.
        /// </item>
        /// <item>
        /// It must contain only characters from the following categories: 0 through 9, A through Z, a through z, 
        /// and all punctuation characters except for "!" (exclamation point), "," (comma), 
        /// "[" (opening bracket), and "]" (closing bracket) � that is, the ASCII characters 
        /// 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It must not begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="indexFlags">
        /// Zero or more values from the IndexFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        /// <param name="keyString">
        /// A pointer to a double null-terminated string of null-delimited tokens.
        /// </param>
        /// <param name="keyStringLength">
        /// The length, in charactes, of the keyString parameter, including the two terminating null characters.
        /// </param>
        /// <param name="density">
        /// The percentage density of the initial index B+ tree.
        /// </param>
        void CreateIndex( const wchar_t* indexName, IndexFlags indexFlags, const wchar_t* keyString, unsigned long	keyStringLength, unsigned long density = 95 ) const
        {
            auto rc = static_cast<Result>( JetCreateIndexW( sessionId_, tableId_, indexName, static_cast<JET_GRBIT>( indexFlags ), keyString, keyStringLength*sizeof( wchar_t ), density ) );
            RequireSuccess( rc );
        }
        /// <summary>
        /// Creates an index for the table.
        /// </summary>
        /// <param name="indexName">
        /// <para>
        /// A pointer to a null-terminated string that specifies the name of the index to be created.
        /// </para>
        /// <para>
        /// The index name must conform to the following guidelines:
        /// </para>
        /// <list>
        /// <item>
        /// It must contain fewer characters than JET_cbNameMost, not including the terminating null character.
        /// </item>
        /// <item>
        /// It must contain only characters from the following categories: 0 through 9, A through Z, a through z, 
        /// and all punctuation characters except for "!" (exclamation point), "," (comma), 
        /// "[" (opening bracket), and "]" (closing bracket) � that is, the ASCII characters 
        /// 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It must not begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="indexFlags">
        /// Zero or more values from the IndexFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        /// <param name="keyString">
        /// A pointer to a double null-terminated string of null-delimited tokens.
        /// </param>
        /// <param name="keyStringLength">
        /// The length, in charactes, of the keyString parameter, including the two terminating null characters.
        /// </param>
        /// <param name="density">
        /// The percentage density of the initial index B+ tree.
        /// </param>
        void CreateIndex( const char* indexName, IndexFlags indexFlags, const char* keyString, unsigned long keyStringLength, unsigned long density = 95 ) const
        {
            auto rc = static_cast<Result>( JetCreateIndexA( sessionId_, tableId_, indexName, static_cast<JET_GRBIT>( indexFlags ), keyString, keyStringLength, density ) );
            RequireSuccess( rc );
        }
        
        /// <summary>
        /// Creates an index for the table.
        /// </summary>
        /// <param name="indexName">
        /// <para>
        /// A string that specifies the name of the index to be created.
        /// </para>
        /// <para>
        /// The index name must conform to the following guidelines:
        /// </para>
        /// <list>
        /// <item>
        /// It must contain fewer characters than JET_cbNameMost, not including the terminating null character.
        /// </item>
        /// <item>
        /// It must contain only characters from the following categories: 0 through 9, A through Z, a through z, 
        /// and all punctuation characters except for "!" (exclamation point), "," (comma), 
        /// "[" (opening bracket), and "]" (closing bracket) � that is, the ASCII characters 
        /// 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It must not begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="indexFlags">
        /// Zero or more values from the IndexFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        /// <param name="keyString">
        /// A pointer to a double null-terminated string of null-delimited tokens.
        /// </param>
        /// <param name="keyStringLength">
        /// The length, in charactes, of the keyString parameter, including the two terminating null characters.
        /// </param>
        /// <param name="density">
        /// The percentage density of the initial index B+ tree.
        /// </param>
        template<SimpleStringLike T>
        void CreateIndex( const T& indexName, IndexFlags indexFlags, const typename T::value_type* keyString, unsigned long keyStringLength, unsigned long density = 95 ) const
        {
            using CharT = typename T::value_type;
            CreateIndex( indexName.c_str( ), indexFlags, keyString, (keyStringLength+1)*sizeof( CharT ), density );
        }

        /// <summary>
        /// Creates an index for the table.
        /// </summary>
        /// <param name="indexName">
        /// <para>
        /// A string that specifies the name of the index to be created.
        /// </para>
        /// <para>
        /// The index name must conform to the following guidelines:
        /// </para>
        /// <list>
        /// <item>
        /// It must contain fewer characters than JET_cbNameMost, not including the terminating null character.
        /// </item>
        /// <item>
        /// It must contain only characters from the following categories: 0 through 9, A through Z, a through z, 
        /// and all punctuation characters except for "!" (exclamation point), "," (comma), 
        /// "[" (opening bracket), and "]" (closing bracket) � that is, the ASCII characters 
        /// 0x20, 0x22 through 0x2d, 0x2f through 0x5a, 0x5c, and 0x5d through 0x7f.
        /// </item>
        /// <item>
        /// It must not begin with a space.
        /// </item>
        /// <item>
        /// It must contain at least one non-space character.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="indexFlags">
        /// Zero or more values from the IndexFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        /// <param name="keyString">
        /// A double null-terminated string of null-delimited tokens.
        /// </param>
        /// <param name="density">
        /// The percentage density of the initial index B+ tree.
        /// </param>
        template<SimpleStringLike T, SimpleCharSpanLike SpanT>
            requires std::is_same_v<typename T::value_type, typename SpanT::value_type >
        void CreateIndex( const T& indexName, IndexFlags indexFlags, const SpanT& keyString, unsigned long density = 95 ) const
        {
            using CharTy = typename T::value_type;
            CreateIndex( indexName.c_str( ), indexFlags, keyString.data(), ( keyString.size() + 1 ), density );
        }



        /// <summary>
        /// Closes an open table in a database. The table may be a temporary table or a normal table.
        /// </summary>
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

    template<StringLike StringT = WideString>
    class Tables : public SystemTable
    {
        typedef SystemTable Base;
        JET_OBJECTLIST objectList_;
    public:
        using StringType = StringT;

        Tables( JET_SESID sessionId, const JET_OBJECTLIST& objectList )
            : Base( sessionId, objectList.tableid ), objectList_( objectList )
        {
        }

        StringType ContainerName() const
        {
            StringType result;
            if ( Read( objectList_.columnidcontainername, result ) )
            {
                return std::move( result );
            }
            return {};
        }

        StringType ObjectName() const
        {
            StringType result;
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

    /// <summary>
    /// A system table that provides information about the columns of a table.
    /// </summary>
    /// <typeparam name="StringT"></typeparam>
    template<StringLike StringT>
    class ColumnList : public SystemTable
    {
        typedef SystemTable Base;
        JET_COLUMNLIST columnList_;
    public:
        using StringType = StringT;
        ColumnList( JET_SESID sessionId, const JET_COLUMNLIST& columnList )
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
        StringType ColumnName() const
        {
            StringType result;
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
        StringType BaseTableName() const
        {
            StringType result;
            if ( Read( columnList_.columnidBaseTableName, result ) )
            {
                return std::move( result );
            }
            return {};
        }
        StringType BaseColumnName() const
        {
            StringType result;
            if ( Read( columnList_.columnidBaseColumnName, result ) )
            {
                return std::move( result );
            }
            return {};
        }
        StringType DefinitionName() const
        {
            StringType result;
            if ( Read( columnList_.columnidDefinitionName, result ) )
            {
                return std::move( result );
            }
            return {};
        }
    };

    template<StringLike StringT>
    inline ColumnList<StringT> Table::GetColumns( ) const
    {
        JET_COLUMNLIST columnList = { sizeof( JET_COLUMNLIST ), 0, };
        GetTableColumnInfo( ( const typename StringT::value_type* )nullptr, &columnList, sizeof( JET_COLUMNLIST ), ColumnInfoLevel::List );
        ColumnList<StringT> result( sessionId_, columnList );
        return result;
    }
    


    /// <summary>
    /// Flags for the Database::OpenTable function.
    /// </summary>
    enum class OpenTableFlags : int
    {
        None = 0,
        /// <summary>
        /// The table cannot be opened for read-access by another database session.
        /// </summary>
        DenyRead = JET_bitTableDenyRead,
        /// <summary>
        /// The table cannot be opened for write-access by another database session.
        /// </summary>
        DenyWrite = JET_bitTableDenyWrite,
        /// <summary>
        /// Do not cache the pages for this table.
        /// </summary>
        NoCache = JET_bitTableNoCache,
        /// <summary>
        /// Allows DDL modification on tables flagged as FixedDDL. This option must 
        /// be used with the DenyRead option.
        /// </summary>
        PermitDDL = JET_bitTablePermitDDL,
        /// <summary>
        /// Provides a hint that the table is probably not in the buffer cache, 
        /// and that pre-reading may be beneficial to performance.
        /// </summary>
        Preread = JET_bitTablePreread,
        /// <summary>
        /// Requests read-only access to the table.
        /// </summary>
        ReadOnly = JET_bitTableReadOnly,
        /// <summary>
        /// Attempt to opportunely read physically adjacent leaf pages using larger physical IOs
        /// </summary>
        OpportuneRead = JET_bitTableOpportuneRead,
        /// <summary>
        /// The table should be very aggressively prefetched from disk because the 
        /// application will be scanning it sequentially.
        /// </summary>
        Sequential = JET_bitTableSequential,
        /// <summary>
        /// Requests write-access to the table.
        /// </summary>
        Updatable = JET_bitTableUpdatable
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( OpenTableFlags, int );

    /// <summary>
    /// Flags for the Session::CommitTransaction function
    /// </summary>
    enum class TransactionFlags : int
    {
        None = 0,
        /// <summary>
        /// <para>
        /// The transaction is committed normally but this API does not wait for the 
        /// transaction to be flushed to the transaction log file before returning to 
        /// the caller. This drastically reduces the duration of a commit operation at 
        /// the cost of durability. Any transaction that is not flushed to the log before 
        /// a crash will be automatically aborted during crash recovery during the next 
        /// call to Instance::InitializeInstance( ).
        /// </para>
        /// <para>
        /// If WaitLast or WaitAll are specified, this option is ignored.
        /// </para>
        /// <para>
        /// If the call to Session::CommitTransaction does not match the first call to 
        /// Session::BeginTransaction for this session, this option is ignored. This is 
        /// because the final action that occurs on the outermost save point is the 
        /// determining factor in whether the entire transaction is actually committed to disk.
        /// </para>
        /// </summary>
        CommitLazyFlush = JET_bitCommitLazyFlush,
        /// <summary>
        /// <para>
        /// All transactions previously committed by any session that have not yet been 
        /// flushed to the transaction log file will be flushed immediately. 
        /// Session::CommitTransaction will wait until the transactions have been flushed 
        /// before returning to the caller.
        /// </para>
        /// <para>
        /// This option may be used even if the session is not currently in a transaction.
        /// </para>
        /// <para>
        /// This option cannot be used in combination with any other option.
        /// </para>
        /// </summary>
        WaitAll = JET_bitWaitAllLevel0Commit,
        /// <summary>
        /// <para>
        /// If the session has previously committed any transactions and they have not yet 
        /// been flushed to the transaction log file, they should be flushed immediately. 
        /// Session::CommitTransaction will wait until the transactions have been flushed 
        /// before returning to the caller. This is useful if the application has previously 
        /// committed several transactions using CommitLazyFlush and now wants to flush 
        /// all of them to disk.
        /// </para>
        /// <para>
        /// This option may be used even if the session is not currently in a transaction.
        /// </para>
        /// <para>
        /// This option may be used even if the session is not currently in a transaction.
        /// </para>
        /// </summary>
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

    /// <summary>
    /// Manages the handle to an Extensible Storage Engine database,
    /// providing an API that exposes the operations that can be 
    /// performed on the database.
    /// </summary>
    class Database
    {
        JET_SESID sessionId_;
        JET_DBID databaseId_;
    public:
        /// <summary>
        /// Constructs a Database object that is not connected
        /// to an Extensible Storage Engine database.
        /// </summary>
        constexpr Database( ) noexcept
            : sessionId_( JET_sesidNil ), databaseId_( JET_dbidNil )
        {
        }

        /// <summary>
        /// Constructs a Database object that is connected
        /// to an Extensible Storage Engine database.
        /// </summary>
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

        /// <summary>
        /// Copy construction is not allowed.
        /// </summary>
        Database( const Database& other ) = delete;
        /// <summary>
        /// Move constructor, taking ownership of the
        /// handles from the other database object.
        /// </summary>
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

        /// <summary>
        /// Copy assignment is not allowed.
        /// </summary>
        Database& operator = ( const Database& other ) = delete;
        /// <summary>
        /// Move assignment implemented by swapping
        /// handles wit the argument database object.
        /// </summary>
        Database& operator = ( Database&& other ) noexcept
        {
            std::swap( sessionId_,other.sessionId_);
            std::swap( databaseId_, other.databaseId_ );
            return *this;
        }

        /// <summary>
        /// Returns the handle of the session that was used to
        /// open or create the database.
        /// </summary>
        /// <returns></returns>
        JET_SESID SessionHandle() const
        {
            return sessionId_;
        }

        /// <summary>
        /// The raw database handle.
        /// </summary>
        /// <returns>
        /// The raw database handle.
        /// </returns>
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

        /// <summary>
        /// A Database object where the session handle is not equal to JET_sesidNil 
        /// and the database handle is not equal to JET_dbidNil is considered to
        /// be a valid Database object.
        /// </summary>
        /// <returns>
        /// true if this Database object is valid, otherwise false.
        /// </returns>
        constexpr bool IsValid( ) const noexcept
        {
            return sessionId_ != JET_sesidNil && databaseId_ != JET_dbidNil;
        }
        /// <summary>
        /// A Database object where the session handle is not equal to JET_sesidNil 
        /// and the database handle is not equal to JET_dbidNil is considered to
        /// be a valid Database object.
        /// </summary>
        constexpr explicit operator bool( ) const noexcept
        {
            return IsValid( );
        }

        /// <summary>
        /// Closes a database.
        /// </summary>
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

        /// <summary>
        /// Opens a cursor on a previously created table.
        /// </summary>
        /// <param name="tablename">
        /// The name of the table to open.
        /// </param>
        /// <param name="parameters">
        /// Deprecated. Set to nullptr.
        /// </param>
        /// <param name="parametersSize">
        /// Deprecated. Set to 0.
        /// </param>
        /// <param name="flags">
        /// Zero or more values from the OpenTableFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        /// <param name="tableId">
        /// On success, points to the identifier of the table. On failure, the contents for tableId are undefined.
        /// </param>
        /// <returns>
        /// A value from the Ese::Result enumeration.
        /// </returns>
        Result OpenTable( const wchar_t* tablename, const void* parameters, unsigned long parametersSize, OpenTableFlags flags, JET_TABLEID* tableId ) const
        {
            auto rc = static_cast<Result>( JetOpenTableW( sessionId_, databaseId_, tablename, parameters, parametersSize, static_cast<JET_GRBIT>(flags), tableId ) );
            return rc;
        }
        /// <summary>
        /// Opens a cursor on a previously created table.
        /// </summary>
        /// <param name="tablename">
        /// The name of the table to open.
        /// </param>
        /// <param name="parameters">
        /// Deprecated. Set to nullptr.
        /// </param>
        /// <param name="parametersSize">
        /// Deprecated. Set to 0.
        /// </param>
        /// <param name="flags">
        /// Zero or more values from the OpenTableFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        /// <param name="tableId">
        /// On success, points to the identifier of the table. On failure, the contents for tableId are undefined.
        /// </param>
        /// <returns>
        /// A value from the Ese::Result enumeration.
        /// </returns>
        Result OpenTable( const char* tablename, const void* parameters, unsigned long parametersSize, OpenTableFlags flags, JET_TABLEID* tableId ) const
        {
            auto rc = static_cast<Result>( JetOpenTableA( sessionId_, databaseId_, tablename, parameters, parametersSize, static_cast<JET_GRBIT>( flags ), tableId ) );
            return rc;
        }

        /// <summary>
        /// Opens a cursor on a previously created table.
        /// </summary>
        /// <typeparam name="T">
        /// Ese::Table or a type derived from Ese::Table.
        /// </typeparam>
        /// <typeparam name="C">
        /// char or wchar_t.
        /// </typeparam>
        /// <param name="tableName">
        /// The name of the table to open.
        /// </param>
        /// <param name="flags">
        /// Zero or more values from the OpenTableFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        /// <param name="noexception">
        /// If true this function will not throw an exception if table
        /// identified by tableName is not found in the database and 
        /// return an invalid Table object.
        /// </param>
        /// <returns>
        /// A Table object representing the table in the database.
        /// </returns>
        /// <remarks>
        /// Derived classes should implement OnTableOpened( ) which
        /// is called just after constructing the Table, or Table derived
        /// object. This is an opportunity for Table derived objects to
        /// retrieve the column ids for the table.
        /// </remarks>
        template<TableType T = Table, ApiCharType C>
        [[nodiscard]] T OpenTable( const C* tableName, 
                                    OpenTableFlags flags = OpenTableFlags::Updatable, 
                                    bool noexception = false ) const
        {
            JET_TABLEID tableId = 0;
            auto rc = OpenTable( tableName, nullptr, 0, flags, &tableId );
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

        /// <summary>
        /// Opens a cursor on a previously created table.
        /// </summary>
        /// <typeparam name="T">
        /// Ese::Table or a type derived from Ese::Table.
        /// </typeparam>
        /// <typeparam name="C">
        /// char or wchar_t.
        /// </typeparam>
        /// <param name="tableName">
        /// The name of the table to open.
        /// </param>
        /// <param name="flags">
        /// Zero or more values from the OpenTableFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        /// <param name="noexception">
        /// If true this function will not throw an exception if table
        /// identified by tableName is not found in the database and 
        /// return an invalid Table object.
        /// </param>
        /// <returns>
        /// A Table object representing the table in the database.
        /// </returns>
        /// <remarks>
        /// Derived classes should implement OnTableOpened( ) which
        /// is called just after constructing the Table, or Table derived
        /// object. This is an opportunity for Table derived objects to
        /// retrieve the column ids for the table.
        /// </ramarks>
        template<TableType T = Table, SimpleStringLike S>
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
        template<TableType T = Table, ApiCharType C>
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
        template<TableType T = Table, SimpleStringLike S>
        [[nodiscard]] T CreateTable( const S& tablename, unsigned long initialNumberOfPages = 1, unsigned long density = 0 ) const
        {
            return CreateTable<T>( tablename.c_str( ), initialNumberOfPages, density );
        }

        /// <summary>
        /// Retrieves an Tables&lt;StringT&gt; that can be used to
        /// enumerate the tables in the database.
        /// </summary>
        /// <typeparam name="StringT"></typeparam>
        /// <returns></returns>
        template<StringLike StringT = WideString>
        [[nodiscard]] Tables<StringT> GetTables() const
        {
            JET_OBJECTLIST objectList = { sizeof(JET_OBJECTLIST), 0, };
            if constexpr ( std::is_same_v<wchar_t, typename StringT::value_type> )
            {
                auto rc = static_cast< Ese::Result >( JetGetObjectInfoW( sessionId_, databaseId_, JET_objtypTable, nullptr, nullptr, &objectList, sizeof( JET_OBJECTLIST ), JET_ObjInfoListNoStats ) );
                RequireSuccess( rc );
            }
            else
            {
                auto rc = static_cast< Ese::Result >( JetGetObjectInfoA( sessionId_, databaseId_, JET_objtypTable, nullptr, nullptr, &objectList, sizeof( JET_OBJECTLIST ), JET_ObjInfoListNoStats ) );
                RequireSuccess( rc );
            }
            Tables<StringT> result( sessionId_, objectList);
            return result;
        }

        /// <summary>
        /// Deletes a table in a database.
        /// </summary>
        /// <param name="tableName">
        /// The name of the table to delete.
        /// </param>
        void DeleteTable( const wchar_t* tableName )
        {
            auto rc = static_cast<Ese::Result>( JetDeleteTableW( sessionId_, databaseId_, tableName ));
            RequireSuccess( rc );
        }
        /// <summary>
        /// Deletes a table in a database.
        /// </summary>
        /// <param name="tableName">
        /// The name of the table to delete.
        /// </param>
        void DeleteTable( const char* tableName )
        {
            auto rc = static_cast<Ese::Result>( JetDeleteTableA( sessionId_, databaseId_, tableName ) );
            RequireSuccess( rc );
        }

        /// <summary>
        /// Deletes a table in a database.
        /// </summary>
        /// <param name="tableName">
        /// The name of the table to delete.
        /// </param>
        template<SimpleStringLike T>
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
        /// <summary>
        /// Retrieves information about a table in the database.
        /// </summary>
        /// <param name="objectName">
        /// The name of the table.
        /// </param>
        /// <returns>
        /// The ObjectInfo object for the requeste table.
        /// </returns>
        [[nodiscard]] ObjectInfo GetTableInfo( const wchar_t* objectName ) const
        {
            ObjectInfo result;
            auto rc = static_cast<Ese::Result>( JetGetObjectInfoW( sessionId_, databaseId_, JET_objtypTable, nullptr, objectName, &result, sizeof( ObjectInfo ), JET_ObjInfoNoStats ) );
            RequireSuccess( rc );
            return result;
        }
        /// <summary>
        /// Retrieves information about a table in the database.
        /// </summary>
        /// <param name="objectName">
        /// The name of the table.
        /// </param>
        /// <returns>
        /// The ObjectInfo object for the requeste table.
        /// </returns>
        [[nodiscard]] ObjectInfo GetTableInfo( const char* objectName ) const
        {
            ObjectInfo result;
            auto rc = static_cast<Ese::Result>( JetGetObjectInfoA( sessionId_, databaseId_, JET_objtypTable, nullptr, objectName, &result, sizeof( ObjectInfo ), JET_ObjInfoNoStats ) );
            RequireSuccess( rc );
            return result;
        }
        /// <summary>
        /// Retrieves information about a table in the database.
        /// </summary>
        /// <param name="objectName">
        /// The name of the table.
        /// </param>
        /// <returns>
        /// The ObjectInfo object for the requeste table.
        /// </returns>
        template<SimpleStringLike S>
        [[nodiscard]] ObjectInfo GetTableInfo( const S& objectName ) const
        {
            return GetTableInfo( objectName.c_str( ) );
        }

        /// <summary>
        /// Test if a table exists in the database.
        /// </summary>
        /// <param name="objectName">
        /// The name of the table.
        /// </param>
        /// <returns>
        /// true if the table exists.
        /// </returns>
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
        /// <summary>
        /// Test if a table exists in the database.
        /// </summary>
        /// <param name="objectName">
        /// The name of the table.
        /// </param>
        /// <returns>
        /// true if the table exists.
        /// </returns>
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
        /// <summary>
        /// Test if a table exists in the database.
        /// </summary>
        /// <param name="objectName">
        /// The name of the table.
        /// </param>
        /// <returns>
        /// true if the table exists.
        /// </returns>
        template<SimpleStringLike S>
        [[nodiscard]] bool TableExists( const S& objectName ) const
        {
            return TableExists( objectName.c_str() );
        }


    };


    /// <summary>
    /// A Transaction object for a Session. Will automatically roll back
    /// the current transaction if it is not explicitly commited through
    /// this object.
    /// </summary>
    class Transaction 
    {
        const Session* session_;
    public:
        Transaction( )
            : session_( nullptr )
        {
        }

        /// <summary>
        /// Called from Session::StartTransaction
        /// </summary>
        /// <param name="session">
        /// The Session creating this object.
        /// </param>
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
        /// <summary>
        /// Commits the transaction.
        /// </summary>
        /// <param name="flags">
        /// Zero or more values from the TransactionFlags enumeration. The values can be
        /// combined using the <c>|</c> operator.
        /// </param>
        HCC_EXPORT void Commit( TransactionFlags flags = TransactionFlags::None );
        /// <summary>
        /// Rolls back the transaction.
        /// </summary>
        /// <param name="rollbackAll">
        /// This option requests that all changes made to the state of the database during 
        /// all save points be undone. As a result, the session will exit the transaction.
        /// </param>
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

        template<WideStringLike StringT>
        StringT GetSystemStringParameter( unsigned long paramId ) const
        {
            wchar_t buffer[1024] = { 0, };

            auto rc = static_cast<Result>( JetGetSystemParameterW( instance_, sessionId_, paramId, nullptr, buffer, sizeof( buffer ) ) );
            RequireSuccess( rc );
            return StringT( buffer );
        }
        template<AnsiStringLike StringT>
        StringT GetSystemStringParameter( unsigned long paramId ) const
        {
            char buffer[ 1024 ] = { 0, };

            auto rc = static_cast< Result >( JetGetSystemParameterA( instance_, sessionId_, paramId, nullptr, buffer, sizeof( buffer ) ) );
            RequireSuccess( rc );
            return StringT( buffer );
        }

        void SetSystemParameter( unsigned long paramId, unsigned long long value )
        {
            auto rc = static_cast<Result>( JetSetSystemParameterW( &instance_, sessionId_, paramId, static_cast<JET_API_PTR>( value ), nullptr ) );
            RequireSuccess( rc );
        }

        template<SimpleWideStringLike StringT>
        void SetSystemParameter( unsigned long paramId, const StringT& value )
        {
            auto rc = static_cast<Result>( JetSetSystemParameterW( &instance_, sessionId_, paramId, 0, value.c_str( ) ) );
            RequireSuccess( rc );
        }
        template<SimpleAnsiStringLike StringT>
        void SetSystemParameter( unsigned long paramId, const StringT& value )
        {
            auto rc = static_cast< Result >( JetSetSystemParameterA( &instance_, sessionId_, paramId, 0, value.c_str( ) ) );
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
        template<DatabaseType T=Database, SimpleWideStringLike StringT>
        [[nodiscard]] T CreateDatabase(const StringT& filename, CreateDatabaseFlags flags, unsigned long maxDatabaseSizeInNumberOfPages = 0) const
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
        template<DatabaseType T = Database, SimpleAnsiStringLike StringT>
        [[nodiscard]] T CreateDatabase( const StringT& filename, CreateDatabaseFlags flags, unsigned long maxDatabaseSizeInNumberOfPages = 0 ) const
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
        template<SimpleWideStringLike StringT>
        void AttachDatabase( const StringT& filename, AttachDatabaseFlags flags = AttachDatabaseFlags::None, unsigned long maxDatabaseSizeInNumberOfPages = 0 ) const
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
        template<SimpleAnsiStringLike StringT>
        void AttachDatabase( const StringT& filename, AttachDatabaseFlags flags = AttachDatabaseFlags::None, unsigned long maxDatabaseSizeInNumberOfPages = 0 ) const
        {
            auto rc = static_cast<Result>( JetAttachDatabase2A( sessionId_, filename.c_str( ), maxDatabaseSizeInNumberOfPages, (int)flags ) );
            RequireNotError( rc );
        }

        template<SimpleWideStringLike StringT>
        void DetachDatabase(const StringT& filename, DetachDatabaseFlags flags) const
        {
            auto rc = static_cast<Result>( JetDetachDatabase2W( sessionId_, filename.c_str( ), ( int )flags ));
            RequireSuccess( rc );
        }

        template<SimpleWideStringLike StringT>
        bool DetachDatabaseNX( const StringT& filename, DetachDatabaseFlags flags ) const
        {
            auto rc = static_cast< Result >( JetDetachDatabase2W( sessionId_, filename.c_str( ), ( int )flags ) );
            return rc == Result::Success;
        }

        template<SimpleAnsiStringLike StringT>
        void DetachDatabase( const StringT& filename, DetachDatabaseFlags flags ) const
        {
            auto rc = static_cast< Result >( JetDetachDatabase2A( sessionId_, filename.c_str( ), ( int )flags ) );
            RequireSuccess( rc );
        }

        template<SimpleAnsiStringLike StringT>
        bool DetachDatabaseNX( const StringT& filename, DetachDatabaseFlags flags ) const
        {
            auto rc = static_cast< Result >( JetDetachDatabase2A( sessionId_, filename.c_str( ), ( int )flags ) );
            return rc == Result::Success;
        }


        void DetachAll(DetachDatabaseFlags flags = DetachDatabaseFlags::None ) const
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
        template<DatabaseType T = Database, SimpleWideStringLike StringT>
        [[nodiscard]] T OpenDatabase( const StringT& filename, OpenDatabaseFlags flags = OpenDatabaseFlags::None ) const
        {
            wchar_t connect[1024] = { 0, };
            JET_DBID databaseId = 0;
            auto rc = static_cast<Result>( JetOpenDatabaseW( sessionId_, filename.c_str( ), connect, &databaseId, ( int )flags ) );
            RequireSuccess( rc );
            T result( sessionId_, databaseId );
            result.OnDatabaseOpened( );
            return result;
        }

        template<DatabaseType T = Database, SimpleAnsiStringLike StringT>
        [[nodiscard]] T OpenDatabase( const StringT& filename, OpenDatabaseFlags flags = OpenDatabaseFlags::None ) const
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

    /// <summary>
    /// An instance of the database engine for use in a single process.
    /// </summary>
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

        template<SimpleWideStringLike StringT1, SimpleWideStringLike StringT2 = WideString>
        Instance(const StringT1& instanceName, const StringT2& displayName = StringT2(), InitFlags initFlags = InitFlags::None)
            : instance_(JET_instanceNil), initialized_(false), initFlags_(initFlags)
        {
            JET_INSTANCE instance = 0;
            auto rc = static_cast<Result>( JetCreateInstance2W( &instance, instanceName.c_str( ), displayName.empty()? instanceName.c_str( ) :  displayName.c_str( ), 0 ));
            RequireSuccess( rc );
            instance_ = instance;
        }

        template<SimpleAnsiStringLike StringT1, SimpleAnsiStringLike StringT2 = AnsiString>
        Instance( const StringT1& instanceName, const StringT2& displayName = StringT2( ), InitFlags initFlags = InitFlags::None )
            : instance_( JET_instanceNil ), initialized_( false ), initFlags_( initFlags )
        {
            JET_INSTANCE instance = 0;
            auto rc = static_cast< Result >( JetCreateInstance2A( &instance, instanceName.c_str( ), displayName.empty( ) ? instanceName.c_str( ) : displayName.c_str( ), 0 ) );
            RequireSuccess( rc );
            instance_ = instance;
        }

        Instance( const wchar_t* instanceName, const wchar_t* displayName = nullptr, InitFlags initFlags = InitFlags::None )
            : instance_( JET_instanceNil ), initialized_( false ), initFlags_( initFlags )
        {
            JET_INSTANCE instance = 0;
            auto rc = static_cast< Result >( JetCreateInstance2W( &instance, instanceName, displayName != nullptr && displayName[0] ? instanceName : displayName, 0 ) );
            RequireSuccess( rc );
            instance_ = instance;
        }
        Instance( const char* instanceName, const char* displayName = nullptr, InitFlags initFlags = InitFlags::None )
            : instance_( JET_instanceNil ), initialized_( false ), initFlags_( initFlags )
        {
            JET_INSTANCE instance = 0;
            auto rc = static_cast< Result >( JetCreateInstance2A( &instance, instanceName, displayName != nullptr && displayName[ 0 ] ? instanceName : displayName, 0 ) );
            RequireSuccess( rc );
            instance_ = instance;
        }


        inline Instance( const InstanceOptions& instanceOptions );

        Instance( const Instance& other ) = delete;
        Instance( Instance&& other ) noexcept
            : instance_( other.instance_ ), initialized_( other.initialized_ ), initFlags_(other.initFlags_)
        {
            other.instance_ = JET_instanceNil;
            other.initialized_ = false;
            other.initFlags_ = InitFlags::None;
        }
        Instance& operator = ( const Instance& other ) = delete;
        Instance& operator = ( Instance&& other ) noexcept
        {
            std::swap(instance_, other.instance_);
            std::swap(initialized_, other.initialized_);
            std::swap(initFlags_, other.initFlags_);
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

        Result Backup( const wchar_t* backupPath, BackupFlags backupFlags, JET_PFNSTATUS statusCallbackFunction = nullptr ) const
        {
            auto rc = static_cast< Result >( JetBackupInstanceW( instance_, backupPath, static_cast< unsigned long >( backupFlags ), statusCallbackFunction ) );
            RequireNotError( rc );
            return rc;
        }
        Result Backup( const char* backupPath, BackupFlags backupFlags, JET_PFNSTATUS statusCallbackFunction = nullptr ) const
        {
            auto rc = static_cast< Result >( JetBackupInstanceA( instance_, backupPath, static_cast< unsigned long >( backupFlags ), statusCallbackFunction ) );
            RequireNotError( rc );
            return rc;
        }

        template<SimpleStringLike StringT>
        Result Backup( const StringT& backupPath, BackupFlags backupFlags, JET_PFNSTATUS statusCallbackFunction = nullptr ) const
        {
            return Backup( backupPath.c_str(), backupFlags, statusCallbackFunction );
        }

        Result Restore( const wchar_t* backupPath, const wchar_t* destinationPath, JET_PFNSTATUS statusCallbackFunction = nullptr ) const
        {
            auto rc = static_cast< Result >( JetRestoreInstanceW( instance_, backupPath, destinationPath, statusCallbackFunction ) );
            RequireNotError( rc );
            return rc;
        }
        Result Restore( const char* backupPath, const char* destinationPath, JET_PFNSTATUS statusCallbackFunction = nullptr ) const
        {
            auto rc = static_cast< Result >( JetRestoreInstanceA( instance_, backupPath, destinationPath, statusCallbackFunction ) );
            RequireNotError( rc );
            return rc;
        }


        template<SimpleStringLike StringT1, SimpleStringLike StringT2>
            requires std::is_same_v<typename StringT1::value_type, typename StringT2::value_type>
        Result Restore( const StringT1& backupPath, const StringT2& destinationPath, JET_PFNSTATUS statusCallbackFunction = nullptr ) const
        {
            return Restore( backupPath.c_str(), destinationPath.c_str( ), statusCallbackFunction );
        }

        Result Restore( const wchar_t* backupPath, JET_PFNSTATUS statusCallbackFunction = nullptr ) const
        {
            auto rc = static_cast< Result >( JetRestoreInstanceW( instance_, backupPath, nullptr, statusCallbackFunction ) );
            RequireNotError( rc );
            return rc;
        }
        Result Restore( const char* backupPath, JET_PFNSTATUS statusCallbackFunction = nullptr ) const
        {
            auto rc = static_cast< Result >( JetRestoreInstanceA( instance_, backupPath, nullptr, statusCallbackFunction ) );
            RequireNotError( rc );
            return rc;
        }


        template<SimpleStringLike StringT>
        Result Restore( const StringT& backupPath, JET_PFNSTATUS statusCallbackFunction = nullptr ) const
        {
            return Restore( backupPath.c_str(), statusCallbackFunction );
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

        template<WideStringLike StringT>
        StringT GetSystemStringParameter(unsigned long paramId) const
        {
            wchar_t buffer[1024] = { 0, };
            auto rc = static_cast<Result>( JetGetSystemParameterW( instance_, JET_sesidNil, paramId, nullptr, buffer, sizeof( buffer ) ));
            RequireSuccess( rc );
            return StringT(buffer);
        }
        template<AnsiStringLike StringT>
        StringT GetSystemStringParameter( unsigned long paramId ) const
        {
            char buffer[ 1024 ] = { 0, };
            auto rc = static_cast< Result >( JetGetSystemParameterA( instance_, JET_sesidNil, paramId, nullptr, buffer, sizeof( buffer ) ) );
            RequireSuccess( rc );
            return StringT( buffer );
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

        void SetSystemParameter( unsigned long paramId, const wchar_t* value ) const
        {
            auto rc = static_cast< Result >( JetSetSystemParameterW( const_cast< JET_INSTANCE* >( &instance_ ), JET_sesidNil, paramId, 0, value ) );
            RequireSuccess( rc );
        }
        void SetSystemParameter( unsigned long paramId, const char* value ) const
        {
            auto rc = static_cast< Result >( JetSetSystemParameterA( const_cast< JET_INSTANCE* >( &instance_ ), JET_sesidNil, paramId, 0, value ) );
            RequireSuccess( rc );
        }

        template<SimpleStringLike StringT>
        void SetSystemParameter(unsigned long paramId, const StringT& value) const
        {
            SetSystemParameter( paramId, value.c_str( ) );
        }

    public:

        // The full path to each database is persisted in the transaction logs at run time. 
        // Ordinarily, these databases must remain at the original location for transaction 
        // replay to function correctly. This can be used to force crash recovery or a restore 
        // operation to look for the databases referenced in the transaction log in the 
        // specified folder
        template<StringLike StringT>
        StringT QueryAlternateDatabaseRecoveryPath() const
        {
            auto result = GetSystemStringParameter<StringT>(JET_paramAlternateDatabaseRecoveryPath);
            return result;
        }

        // The full path to each database is persisted in the transaction logs at run time. 
        // Ordinarily, these databases must remain at the original location for transaction 
        // replay to function correctly. This can be used to force crash recovery or a restore 
        // operation to look for the databases referenced in the transaction log in the 
        // specified folder
        template<StringLike StringT>
        void SetAlternateDatabaseRecoveryPath( const StringT& value ) const
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
        // Valid range: 0 � 2147483647
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
        template<StringLike StringT>
        StringT QueryBaseName() const
        {
            auto result = GetSystemStringParameter<StringT>(JET_paramBaseName);
            return result;
        }

        template<SimpleStringLike StringT>
        void SetBaseName(const StringT& value) const
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
        template<StringLike StringT>
        StringT QueryLogFilePath() const
        {
            auto result = GetSystemStringParameter<StringT>(JET_paramLogFilePath);
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
        template<SimpleStringLike StringT>
        void SetLogFilePath(const StringT& value) const
        {
            SetSystemParameter(JET_paramLogFilePath, value);
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

        template<StringLike StringT>
        StringT QueryRecovery() const
        {
            auto result = GetSystemStringParameter<StringT>(JET_paramRecovery);
            return result;
        }

        template<SimpleStringLike StringT>
        void SetRecovery(const StringT& value) const
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
        template<StringLike StringT>
        StringT QuerySystemPath() const
        {
            auto result = GetSystemStringParameter<StringT>(JET_paramSystemPath);
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
        template<SimpleStringLike StringT>
        void SetSystemPath(const StringT& value) const
        {
            SetSystemParameter(JET_paramSystemPath, value);
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

    HCC_EXPORT WideString ToWideString( Ese::ColumnInfoLevel value );
    HCC_EXPORT WideString ToWideString( Ese::ColumnInfoLevel value, const WideString& defaultResult );

    inline AnsiString ToAnsiString( Ese::ColumnInfoLevel value )
    {
        return ToAnsiString( ToWideString( value ) );
    }
    inline AnsiString ToAnsiString( Ese::ColumnInfoLevel value, const AnsiString& defaultResult )
    {
        return ToAnsiString( ToWideString( value, ToWideString( defaultResult ) ) );
    }
    namespace Ese
    {
        HCC_EXPORT Ese::ColumnInfoLevel ParseColumnInfoFlags( const WideString& str );
        HCC_EXPORT Ese::ColumnInfoLevel ParseColumnInfoFlags( const WideString& str, Ese::ColumnInfoLevel defaultResult );
        HCC_EXPORT bool TryParseColumnInfoFlags( const WideString& str, Ese::ColumnInfoLevel& value );

        inline Ese::ColumnInfoLevel ParseColumnInfoFlags( const AnsiString& str )
        {
            return ParseColumnInfoFlags( ToWideString( str ) );
        }
        inline Ese::ColumnInfoLevel ParseColumnInfoFlags( const AnsiString& str, Ese::ColumnInfoLevel defaultResult )
        {
            return ParseColumnInfoFlags( ToWideString( str ), defaultResult );
        }
        inline bool TryParseColumnInfoFlags( const AnsiString& str, Ese::ColumnInfoLevel& value )
        {
            return TryParseColumnInfoFlags( ToWideString( str ), value );
        }

    }
    template<typename StringT>
        requires std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString>
    inline bool TryParse( const StringT& str, Ese::ColumnInfoLevel& value )
    {
        return Ese::TryParseColumnInfoFlags( str, value );
    }

    template<typename T, typename StringT>
        requires std::is_same_v<Ese::ColumnInfoLevel, T> && ( std::is_same_v<StringT, WideString> || std::is_same_v<StringT, AnsiString> )
    inline T Parse( const WideString& str )
    {
        return Ese::ParseColumnInfoFlags( str );
    }

    template<typename T, typename CharT>
        requires std::is_same_v<Ese::ColumnInfoLevel, T> && ( std::is_same_v<CharT, wchar_t> || std::is_same_v<CharT, char> )
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
            auto format( EnumT value, FormatContext& ctx ) const
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
    struct formatter<Harlinn::Common::Core::Ese::ColumnInfoLevel, CharT> : public Harlinn::Common::Core::Internal::EseFormatterImpl<Harlinn::Common::Core::Ese::ColumnInfoLevel, CharT>
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
