#pragma once
#ifndef __HOCIENUMS_H__
#define __HOCIENUMS_H__

namespace Harlinn::OCI
{
    enum class HandleType : Int32
    {
        Unknown = 0x0000,
        /// <summary>
        /// environment handle 
        /// </summary>
        Environment = 0x0001,
        /// <summary>
        /// error handle 
        /// </summary>
        Error = 0x0002,
        /// <summary>
        /// service handle 
        /// </summary>
        ServiceContext = 0x0003,
        /// <summary>
        /// statement handle 
        /// </summary>
        Statement = 0x0004,
        /// <summary>
        /// bind handle 
        /// </summary>
        Bind = 0x0005,
        /// <summary>
        /// define handle 
        /// </summary>
        Define = 0x0006,
        /// <summary>
        /// describe handle 
        /// </summary>
        Describe = 0x0007,
        /// <summary>
        /// server handle 
        /// </summary>
        Server = 0x0008,
        /// <summary>
        /// authentication handle 
        /// </summary>
        Session = 0x0009,
        /// <summary>
        /// SessionGet auth handle 
        /// </summary>
        AuthInfo = Session,
        /// <summary>
        /// transaction handle
        /// </summary>
        Transaction = 0x000A,
        /// <summary>
        /// complex object retrieval handle 
        /// </summary>
        ComplexObject = 0x000B,
        /// <summary>
        /// security handle 
        /// </summary>
        Security = 0x000C,
        /// <summary>
        /// subscription handle 
        /// </summary>
        Subscription = 0x000D,
        /// <summary>
        /// direct path context 
        /// </summary>
        DirectPathContext = 0x000E,
        /// <summary>
        /// direct path column array 
        /// </summary>
        DirectPathColumnArray = 0x000F,
        /// <summary>
        /// direct path stream 
        /// </summary>
        DirectPathStream = 0x0010,
        /// <summary>
        /// process handle 
        /// </summary>
        Process = 0x0011,
        /// <summary>
        /// direct path function context 
        /// </summary>
        DirectPathFunctionContext = 0x0012,
        /// <summary>
        /// dp object column array 
        /// </summary>
        DirectPathFunctionColumnArray = 0x0013,
        /// <summary>
        /// access driver session
        /// </summary>
        XADSession = 0x0014,
        /// <summary>
        /// access driver table 
        /// </summary>
        XADTable = 0x0015,
        /// <summary>
        /// access driver field 
        /// </summary>
        XADField = 0x0016,
        /// <summary>
        /// access driver granule 
        /// </summary>
        XADGranule = 0x0017,
        /// <summary>
        /// access driver record 
        /// </summary>
        XADRecord = 0x0018,
        /// <summary>
        /// access driver I/O 
        /// </summary>
        XADIO = 0x0019,
        /// <summary>
        /// connection pool handle
        /// </summary>
        ConnectionPool = 0x001A,
        /// <summary>
        /// session pool handle 
        /// </summary>
        SessionPool = 0x001B,
        /// <summary>
        /// admin handle 
        /// </summary>
        Admin = 0x001C,
        /// <summary>
        /// HA event handle 
        /// </summary>
        Event = 0x001D,
        /// <summary>
        /// lob  locator 
        /// </summary>
        LOB = 0x0032,
        /// <summary>
        /// snapshot descriptor 
        /// </summary>
        SNAP = 0x0033,
        /// <summary>
        /// result set descriptor 
        /// </summary>
        RSET = 0x0034,
        /// <summary>
        /// a parameter descriptor obtained from ocigparm 
        /// </summary>
        PARAM = 0x0035,
        Parameter = 0x0035,
        /// <summary>
        /// rowid descriptor 
        /// </summary>
        ROWID = 0x0036,
        /// <summary>
        /// complex object retrieval descriptor 
        /// </summary>
        COMPLEXOBJECTCOMP = 0x0037,
        /// <summary>
        /// File Lob locator 
        /// </summary>
        FILE = 0x0038,
        /// <summary>
        /// enqueue options 
        /// </summary>
        AQENQ_OPTIONS = 0x0039,
        /// <summary>
        /// dequeue options 
        /// </summary>
        AQDEQ_OPTIONS = 0x003A,
        /// <summary>
        /// message properties 
        /// </summary>
        AQMSG_PROPERTIES = 0x003B,
        /// <summary>
        /// aq agent 
        /// </summary>
        AQAGENT = 0x003C,
        /// <summary>
        /// LOB locator
        /// </summary>
        LOCATOR = 0x003D,
        /// <summary>
        /// Interval year month 
        /// </summary>
        INTERVAL_YM = 0x003E,
        /// <summary>
        /// Interval day second 
        /// </summary>
        INTERVAL_DS = 0x003F,
        /// <summary>
        /// AQ notify descriptor 
        /// </summary>
        AQNFY_DESCRIPTOR = 0x0040,
        /// <summary>
        /// Date 
        /// </summary>
        DATE = 0x0041,
        /// <summary>
        /// Time 
        /// </summary>
        TIME = 0x0042,
        /// <summary>
        /// Time with timezone 
        /// </summary>
        TIME_TZ = 0x0043,
        /// <summary>
        /// Timestamp 
        /// </summary>
        TIMESTAMP = 0x0044,
        /// <summary>
        /// Timestamp with timezone 
        /// </summary>
        TIMESTAMP_TZ = 0x0045,
        /// <summary>
        /// Timestamp with local tz 
        /// </summary>
        TIMESTAMP_LTZ = 0x0046,
        /// <summary>
        /// user callback descriptor 
        /// </summary>
        UCB = 0x0047,
        /// <summary>
        /// server DN list descriptor 
        /// </summary>
        SRVDN = 0x0048,
        /// <summary>
        /// signature 
        /// </summary>
        SIGNATURE = 0x0049,
        /// <summary>
        /// AQ listen options 
        /// </summary>
        AQLIS_OPTIONS = 0x004B,
        /// <summary>
        /// AQ listen msg props 
        /// </summary>
        AQLIS_MSG_PROPERTIES = 0x004C,
        /// <summary>
        /// Top level change notification desc
        /// </summary>
        CHDES = 0x004D,
        /// <summary>
        /// Table change descriptor
        /// </summary>
        TABLE_CHDES = 0x004E,
        /// <summary>
        /// Row change descriptor
        /// </summary>
        ROW_CHDES = 0x004F,
        /// <summary>
        /// Query change descriptor 
        /// </summary>
        CQDES = 0x0050,
        /// <summary>
        /// LOB Share region descriptor 
        /// </summary>
        LOB_REGION = 0x0051
    };

    enum class TypeCode : UInt16
    {
        Unknown = 0x0000,
        /// <summary>
        /// Variable string Oracle SQL, that is, VARCHAR (SQLT_CHR, OCI_TYPECODE_VARCHAR)
        /// </summary>
        VarChar = 0x0001,
        /// <summary>
        /// Oracle NUMBER (SQLT_NUM, OCI_TYPECODE_NUMBER)
        /// </summary>
        Number = 0x0002,
        /// <summary>
        /// Integer (SQLT_INT, OCI_TYPECODE_INTEGER)
        /// </summary>
        Integer = 0x0003,
        /// <summary>
        /// Floating-point (SQLT_FLT, OCI_TYPECODE_FLOAT)
        /// </summary>
        Float = 0x0004,
        /// <summary>
        /// zero terminated string (SQLT_STR)
        /// </summary>
        Str = 0x0005,
        /// <summary>
        /// Number with preceding length byte
        /// </summary>
        VariableNumber = 0x0006,
        /// <summary>
        /// Decimal (SQLT_PDN, OCI_TYPECODE_DECIMAL)
        /// </summary>
        Decimal = 0x0007,
        /// <summary>
        /// Long (SQLT_PDN)
        /// </summary>
        Long = 0x0008,
        /// <summary>
        /// Variable string ANSI SQL, that is, VARCHAR2 (SQLT_VCS, OCI_TYPECODE_VARCHAR2)
        /// </summary>
        VarChar2 = 0x0009,
        /// <summary>
        /// rowid
        /// </summary>
        RowId = 0x000B,
        /// <summary>
        /// OCI_TYPECODE_DATE
        /// </summary>
        Date = 0x000C,
        /// <summary>
        /// OCI_TYPECODE_REAL
        /// </summary>
        Real = 0x0015,
        /// <summary>
        /// OCI_TYPECODE_DOUBLE
        /// </summary>
        Double = 0x0016,
        /// <summary>
        /// OCI_TYPECODE_UNSIGNED8
        /// </summary>
        Byte = 0x0017,
        /// <summary>
        /// OCI_TYPECODE_UNSIGNED16
        /// </summary>
        UInt16 = 0x0019,
        /// <summary>
        /// OCI_TYPECODE_UNSIGNED32
        /// </summary>
        UInt32 = 0x001A,
        /// <summary>
        /// OCI_TYPECODE_SIGNED8
        /// </summary>
        SByte = 0x001B,
        /// <summary>
        /// OCI_TYPECODE_SIGNED16
        /// </summary>
        Int16 = 0x001C,
        /// <summary>
        /// OCI_TYPECODE_SIGNED32
        /// </summary>
        Int32 = 0x001D,
        /// <summary>
        /// OCI_TYPECODE_PTR
        /// </summary>
        Pointer = 0x0020,
        /// <summary>
        /// OCI_TYPECODE_OPAQUE
        /// </summary>
        Opaque = 0x003A,
        /// <summary>
        /// OCI_TYPECODE_RAW
        /// </summary>
        RaW = 0x005F,
        /// <summary>
        /// OCI_TYPECODE_CHAR - Ansi Fixed Char
        /// </summary>
        Char = 0x0060,
        /// <summary>
        /// OCI_TYPECODE_BFLOAT
        /// </summary>
        BinaryFloat = 0x0064,
        /// <summary>
        /// OCI_TYPECODE_BDOUBLE
        /// </summary>
        BinaryDouble = 0x0065,
        /// <summary>
        /// OCI_TYPECODE_UROWID
        /// </summary>
        URowId = 0x0068,
        /// <summary>
        /// OCI_TYPECODE_MLSLABEL
        /// </summary>
        Label = 0x0069,
        /// <summary>
        /// OCI_TYPECODE_OBJECT
        /// </summary>
        Object = 0x006C,
        /// <summary>
        /// OCI_TYPECODE_REF
        /// </summary>
        Ref = 0x006E,
        /// <summary>
        /// OCI_TYPECODE_CLOB
        /// </summary>
        CLOB = 0x0070,
        /// <summary>
        /// OCI_TYPECODE_BLOB
        /// </summary>
        BLOB = 0x0071,
        /// <summary>
        /// OCI_TYPECODE_BFILE
        /// </summary>
        BFILE = 0x0072,
        /// <summary>
        /// OCI_TYPECODE_CFILE
        /// </summary>
        CFILE = 0x0073,
        /// <summary>
        /// OCI_TYPECODE_NAMEDCOLLECTION
        /// </summary>
        NamedCollection = 0x007A,
        /// <summary>
        /// OCI_TYPECODE_TIME
        /// </summary>
        Time = 0x00B9,
        /// <summary>
        /// OCI_TYPECODE_TIME_TZ
        /// </summary>
        TimeWithTimeZone = 0x00BA,
        /// <summary>
        /// OCI_TYPECODE_TIMESTAMP
        /// </summary>
        Timestamp = 0x00BB,
        /// <summary>
        /// OCI_TYPECODE_TIMESTAMP_TZ
        /// </summary>
        TimestampWithTimeZone = 0x00BC,
        /// <summary>
        /// OCI_TYPECODE_INTERVAL_YM
        /// </summary>
        IntervalYearToMonth = 0x00BD,
        /// <summary>
        /// OCI_TYPECODE_INTERVAL_DS
        /// </summary>
        IntervalDayToSecond = 0x00BE,
        /// <summary>
        /// OCI_TYPECODE_TIMESTAMP_LTZ
        /// </summary>
        TimestampWithLocalTimeZone = 0x00E8,
        /// <summary>
        /// OCI_TYPECODE_OCTET
        /// </summary>
        Octet = 0x00F5,
        /// <summary>
        /// OCI_TYPECODE_SMALLINT
        /// </summary>
        SmallInt = 0x00F6,
        /// <summary>
        /// OCI_TYPECODE_VARRAY
        /// </summary>
        VArray = 0x00F7,
        /// <summary>
        /// OCI_TYPECODE_TABLE
        /// </summary>
        Table = 0x00F8,
        /// <summary>
        /// OCI_TYPECODE_PLS_INTEGER
        /// </summary>
        PLSInteger = 0x010A,
        /// <summary>
        /// OCI_TYPECODE_NCHAR       
        /// </summary>
        NChar = 0x011E,
        /// <summary>
        /// OCI_TYPECODE_NVARCHAR2   
        /// </summary>
        NVarChar2 = 0x011F,
        /// <summary>
        /// OCI_TYPECODE_NCLOB 
        /// </summary>
        NCLOB = 0x0120
    };



    enum class OraType : UInt16
    {
        Undefined = 0x0000,
        /// <summary>
        /// (ORANET TYPE) character string (SQLT_CHR)
        /// </summary>
        CHR = 1,
        Char = CHR,
        ORA_CHARN = CHR,
        /// <summary>
        /// (ORANET TYPE) oracle numeric (SQLT_NUM)
        /// </summary>
        NUM = 2,
        Number = NUM,
        ORA_NUMBER = NUM,
        /// <summary>
        /// (ORANET TYPE) integer (SQLT_INT)
        /// </summary>
        INT = 3,
        ORA_SB1 = INT,
        ORA_SB2 = INT,
        ORA_SB4 = INT,
        /// <summary>
        /// (ORANET TYPE) Floating point number (SQLT_FLT)
        /// </summary>
        FLT = 4,
        ORA_FLOAT = FLT,
        /// <summary>
        /// zero terminated string (SQLT_STR)
        /// </summary>
        STR = 5,
        ORA_NULLSTR = STR,
        /// <summary>
        /// NUM with preceding length byte (SQLT_VNU)
        /// </summary>
        VNU = 6,
        ORA_VARNUM = VNU,
        /// <summary>
        /// (ORANET TYPE) Packed Decimal Numeric (SQLT_PDN)
        /// </summary>
        PDN = 7,
        /// <summary>
        /// long (SQLT_LNG)
        /// </summary>
        LNG = 8,
        ORA_LONG = LNG,
        /// <summary>
        /// Variable character string (SQLT_VCS)
        /// </summary>
        VCS = 9,
        ORA_VARCHAR = VCS,
        /// <summary>
        /// Null/empty PCC Descriptor entry (SQLT_NON)
        /// </summary>
        NON = 10,
        /// <summary>
        /// rowid (SQLT_RID)
        /// </summary>
        RID = 11,
        ORA_ROWID = RID,
        /// <summary>
        /// date in oracle format (SQLT_DAT)
        /// </summary>
        DAT = 12,
        ORA_DATE = DAT,
        /// <summary>
        /// binary in VCS format (SQLT_VBI)
        /// </summary>
        VBI = 15,
        ORA_VARRAW = VBI,
        /// <summary>
        /// Native Binary float (SQLT_BFLOAT)
        /// </summary>
        BFLOAT = 21,
        ORA_BFLOAT = BFLOAT,
        /// <summary>
        /// Native binary double (SQLT_BDOUBLE)
        /// </summary>
        BDOUBLE = 22,
        ORA_BDOUBLE = BDOUBLE,
        /// <summary>
        /// binary data(DTYBIN) (SQLT_BIN)
        /// </summary>
        BIN = 23,
        ORA_RAW = BIN,
        // long binary (SQLT_LBI)
        LBI = 24,
        ORA_LONGRAW = LBI,
        /// <summary>
        /// UInt32eger (SQLT_UIN)
        /// </summary>
        UIN = 68,
        ORA_UINT = UIN,
        /// <summary>
        /// Display sign leading separate (SQLT_SLS)
        /// </summary>
        SLS = 91,
        /// <summary>
        /// Longer longs (char) (SQLT_LVC)
        /// </summary>
        LVC = 94,
        ORA_LONGVARCHAR = LVC,
        /// <summary>
        /// Longer long binary (SQLT_LVB)
        /// </summary>
        LVB = 95,
        ORA_LONGVARRAW = LVB,
        /// <summary>
        /// Ansi fixed char (SQLT_AFC)
        /// </summary>
        AFC = 96,
        ORA_CHAR = AFC,
        // Ansi Var char (SQLT_AVC)
        AVC = 97,
        ORA_CHARZ = AVC,
        /// <summary>
        /// binary float canonical (SQLT_IBFLOAT)
        /// </summary>
        IBFLOAT = 100,
        /// <summary>
        /// binary double canonical (SQLT_IBDOUBLE)
        /// </summary>
        IBDOUBLE = 101,
        /// <summary>
        /// cursor  type (SQLT_CUR)
        /// </summary>
        CUR = 102,
        /// <summary>
        /// rowid descriptor (SQLT_RDD)
        /// </summary>
        RDD = 104,
        ORA_OCIRowid = RDD,
        /// <summary>
        /// label type (SQLT_LAB)
        /// </summary>
        LAB = 105,
        /// <summary>
        /// oslabel type (SQLT_OSL)
        /// </summary>
        OSL = 106,
        /// <summary>
        /// named object type (SQLT_NTY)
        /// </summary>
        NTY = 108,
        ORA_NDT = NTY,
        ORA_OCIXMLType = NTY,
        /// <summary>
        /// ref type (SQLT_REF)
        /// </summary>
        REF = 110,
        ORA_OCIRef = REF,
        /// <summary>
        /// character lob (SQLT_CLOB)
        /// </summary>
        CLOB = 112,
        ORA_OCICLobLocator = CLOB,
        /// <summary>
        /// binary lob (SQLT_BLOB)
        /// </summary>
        BLOB = 113,
        ORA_OCIBLobLocator = BLOB,
        /// <summary>
        /// binary file lob (SQLT_BFILEE)
        /// </summary>
        BFILEE = 114,
        ORA_OCIBFileLocator = BFILEE,
        /// <summary>
        /// character file lob (SQLT_CFILEE)
        /// </summary>
        CFILEE = 115,
        /// <summary>
        /// result set type (SQLT_RSET)
        /// </summary>
        RSET = 116,
        ORA_RESULTSET = RSET,
        /// <summary>
        /// named collection type (varray or nested table) (SQLT_NCO)
        /// </summary>
        NCO = 122,
        ORA_NCO = NCO,
        /// <summary>
        /// OCIString type (SQLT_VST)
        /// </summary>
        VST = 155,
        ORA_OCIString = VST,
        /// <summary>
        /// OCIDate type (SQLT_ODT)
        /// </summary>
        ODT = 156,
        ORA_OCIDate = ODT,
        /// <summary>
        /// ANSI Date (SQLT_DATE)
        /// </summary>
        DATE = 184,
        /// <summary>
        /// TIME (SQLT_TIME)
        /// </summary>
        TIME = 185,
        /// <summary>
        /// TIME WITH TIME ZONE (SQLT_TIME_TZ)
        /// </summary>
        TIME_TZ = 186,
        ORA_TIME_TZ = TIME_TZ,
        /// <summary>
        /// TIMESTAMP (SQLT_TIMESTAMP)
        /// </summary>
        TIMESTAMP = 187,
        ORA_TIMESTAMP = TIMESTAMP,
        /// <summary>
        /// TIMESTAMP WITH TIME ZONE (SQLT_TIMESTAMP_TZ)
        /// </summary>
        TIMESTAMP_TZ = 188,
        ORA_TIMESTAMP_TZ = TIMESTAMP_TZ,
        /// <summary>
        /// INTERVAL YEAR TO MONTH (SQLT_INTERVAL_YM)
        /// </summary>
        INTERVAL_YM = 189,
        ORA_INTERVAL_YM = INTERVAL_YM,
        /// <summary>
        /// INTERVAL DAY TO SECOND (SQLT_INTERVAL_DS)
        /// </summary>
        INTERVAL_DS = 190,
        ORA_INTERVAL_DS = INTERVAL_DS,
        /// <summary>
        /// TIMESTAMP WITH LOCAL TZ (SQLT_TIMESTAMP_LTZ)
        /// </summary>
        TIMESTAMP_LTZ = 232,
        ORA_TIMESTAMP_LTZ = TIMESTAMP_LTZ,
        /// <summary>
        /// pl/sql representation of named types (SQLT_PNTY)
        /// </summary>
        PNTY = 241,

        /// <summary>
        /// pl/sql 'record' (or %rowtype)
        /// </summary>
        REC = 250,
        /// <summary>
        /// pl/sql 'indexed table'
        /// </summary>
        TAB = 251,
        /// <summary>
        /// pl/sql 'boolean'
        /// </summary>
        BOL = 252
    };


    enum class ServerAttachMode : UInt32
    {
        Default = 0x00000000,
        /// <summary>
        /// Attach in fast path mode
        /// </summary>
        Fastpath = 0x00000010,
        /// <summary>
        /// Attach using server handle from pool
        /// </summary>
        ConnectionPool = 0x00000200,
        /// <summary>
        /// Allow bequeath connect strings
        /// </summary>
        EnableBequeath = 0x00004000

    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( ServerAttachMode, UInt32 );


    enum class AuthenticationMode : UInt32
    {
        Default = 0x00000000,
        /// <summary>
        /// migratable auth context 
        /// </summary>
        Migrate = 0x00000001,
        /// <summary>
        /// for SYSDBA authorization 
        /// </summary>
        SysDBA = 0x00000002,
        /// <summary>
        /// for SYSOPER authorization 
        /// </summary>
        SysOPER = 0x00000004,
        /// <summary>
        /// for preliminary authorization 
        /// </summary>
        Preliminary = 0x00000008,
        /// <summary>
        /// Private OCI cache mode 
        /// </summary>
        PrivateCache = 0x00000010,
        /// <summary>
        /// enable OCI Stmt Caching 
        /// </summary>
        EnableStatementCaching = 0x00000040,
        /// <summary>
        /// stateless at call boundary 
        /// </summary>
        StatelessCall = 0x00000080,
        /// <summary>
        /// stateless at txn boundary 
        /// </summary>
        StatelessTransaction = 0x00000100,
        /// <summary>
        /// stateless at user-specified pts 
        /// </summary>
        StatelessApp = 0x00000200,
        /// <summary>
        /// for SYSASM authorization 
        /// </summary>
        SysASM = 0x00008000
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( AuthenticationMode, UInt32 );

    enum class CredidentialType : Int32
    {
        Unknown = 0x00000000,
        /// <summary>
        /// database username/password 
        /// </summary>
        DatabaseServer = 0x00000001,
        /// <summary>
        /// externally provided credentials 
        /// </summary>
        External = 0x00000002,
        /// <summary>
        /// proxy authentication 
        /// </summary>
        Proxy = 0x00000003
    };


    // Transaction Start Flags
    // NOTE: OCI_TRANS_JOIN and OCI_TRANS_NOMIGRATE not supported in 8.0.X
    enum class  TransactionStartFlags : UInt32
    {
        None = 0x00000000,
        /// <summary>
        /// start a new local or global txn 
        /// </summary>
        New = 0x00000001,
        /// <summary>
        /// join an existing global txn 
        /// </summary>
        Join = 0x00000002,
        /// <summary>
        /// resume the global txn branch 
        /// </summary>
        Resume = 0x00000004,
        /// <summary>
        /// promote the local txn to global 
        /// </summary>
        Promote = 0x00000008,
        /// <summary>
        /// mask for start operation flags 
        /// </summary>
        StartMask = 0x000000ff,
        /// <summary>
        /// start a readonly txn 
        /// </summary>
        ReadOnly = 0x00000100,
        /// <summary>
        /// start a read-write txn 
        /// </summary>
        ReadWrite = 0x00000200,
        /// <summary>
        /// start a serializable txn 
        /// </summary>
        Serializable = 0x00000400,
        /// <summary>
        /// mask for start isolation flags 
        /// </summary>
        IsolationMask = 0x0000ff00,
        /// <summary>
        /// a loosely coupled branch 
        /// </summary>
        Loose = 0x00010000,
        /// <summary>
        /// a tightly coupled branch 
        /// </summary>
        Tight = 0x00020000,
        /// <summary>
        /// mask for branch type flags 
        /// </summary>
        TypeMask = 0x000f0000,
        /// <summary>
        /// non migratable transaction 
        /// </summary>
        NonMigratable = 0x00100000,
        /// <summary>
        /// separable transaction (8.1.6+) 
        /// </summary>
        Separable = 0x00200000,
        /// <summary>
        /// OTS resuming a transaction 
        /// </summary>
        OTSResume = 0x00400000,
        /// <summary>
        /// mask for other start flags 
        /// </summary>
        OtherMask = 0xfff00000
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( TransactionStartFlags, UInt32 );

    /// <summary>
    /// Transaction End Flags
    /// </summary>
    enum class TransactionEndFlags : UInt32
    {
        None = 0,
        /// <summary>
        /// force cmt-redo for local txns 
        /// </summary>
        WriteBatch = 0x00000001,
        /// <summary>
        /// no force cmt-redo 
        /// </summary>
        WriteImmediately = 0x00000002,
        /// <summary>
        /// no sync cmt-redo 
        /// </summary>
        WriteWait = 0x00000004,
        /// <summary>
        /// sync cmt-redo for local txns
        /// </summary>
        WriteNoWait = 0x00000008,
        /// <summary>
        /// use two phase commit 
        /// </summary>
        TwoPhase = 0x01000000
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( TransactionEndFlags, UInt32 );

    /// <summary>
    /// StatementType
    /// </summary>
    enum class StatementType : UInt32
    {
        /// <summary>
        /// Unknown statement
        /// </summary>
        Unknown = 0,
        /// <summary>
        /// select statement 
        /// </summary>
        Select = 1,
        /// <summary>
        /// update statement 
        /// </summary>
        Update = 2,
        /// <summary>
        /// delete statement 
        /// </summary>
        Delete = 3,
        /// <summary>
        /// Insert Statement 
        /// </summary>
        Insert = 4,
        /// <summary>
        /// create statement 
        /// </summary>
        Create = 5,
        /// <summary>
        /// drop statement 
        /// </summary>
        Drop = 6,
        /// <summary>
        /// alter statement 
        /// </summary>
        Alter = 7,
        /// <summary>
        /// begin ... (pl/sql statement)
        /// </summary>
        Begin = 8,
        /// <summary>
        /// declare .. (pl/sql statement ) 
        /// </summary>
        Declare = 9,
        /// <summary>
        /// call statement
        /// </summary>
        Call = 10,
        /// <summary>
        /// merge statement 
        /// </summary>
        Merge = 16
    };


    /// <summary>
    /// Statement States
    /// </summary>
    enum class StatementState : UInt32
    {
        /// <summary>
        /// OCI_STMT_STATE_INITIALIZED
        /// </summary>
        Initialized = 0x00000001,
        /// <summary>
        /// OCI_STMT_STATE_EXECUTED
        /// </summary>
        Executed = 0x00000002,
        /// <summary>
        /// OCI_STMT_STATE_END_OF_FETCH
        /// </summary>
        EndOfFetch = 0x00000003
    };

    enum class StatementExecuteMode : UInt32
    {
        /// <summary>
        /// Executes the statement and implicitly returns describe 
        /// information about the select list.
        /// </summary>
        Default = 0x00000000,
        /// <summary>
        /// batch the oci stmt for exec 
        /// </summary>
        BatchMode = 0x00000001,
        /// <summary>
        /// fetch exact rows specified 
        /// </summary>
        ExactFetch = 0x00000002,
        /// <summary>
        /// if result set is scrollable 
        /// </summary>
        ScrollableReadonly = 0x00000008,
        /// <summary>
        /// Use this to describe the query before execution. This mode does not execute the
        /// statement, but it does return the select-list description. To maximize performance,
        /// Oracle recommends that applications execute the statement in default mode and
        /// use the implicit describe that accompanies the execution.
        /// </summary>
        DescribeOnly = 0x00000010,
        /// <summary>
        /// When a statement is executed in this mode, the current
        /// transaction is committed after execution, if execution 
        /// completes successfully
        /// </summary>
        CommitOnSuccess = 0x00000020,
        /// <summary>
        /// non-blocking 
        /// </summary>
        NonBlocking = 0x00000040,
        /// <summary>
        /// batch errors in array dmls 
        /// </summary>
        BatchErrors = 0x00000080,
        /// <summary>
        /// only parse the statement 
        /// </summary>
        ParseOnly = 0x00000100,
        /// <summary>
        /// return OCI_SUCCESS_WITH_INFO for delete/update w/no where clause 
        /// </summary>
        ShowDMLWarnings = 0x00000400,
        /// <summary>
        /// hint to use query caching 
        /// </summary>
        ResultCache = 0x00020000,
        /// <summary>
        /// hint to bypass query caching
        /// </summary>
        NoResultCache = 0x00040000
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( StatementExecuteMode, UInt32 );

    enum class FetchOrientation : UInt16
    {
        /// <summary>
        /// refetching current position  
        /// </summary>
        Current = 0x0001,
        /// <summary>
        /// next row 
        /// </summary>
        Next = 0x0002,
        /// <summary>
        /// first row of the result set 
        /// </summary>
        First = 0x0004,
        /// <summary>
        /// the last row of the result set 
        /// </summary>
        Last = 0x0008,
        /// <summary>
        /// previous row relative to current 
        /// </summary>
        Prior = 0x0010,
        /// <summary>
        /// absolute offset from first 
        /// </summary>
        Absolute = 0x0020,
        /// <summary>
        /// offset relative to current 
        /// </summary>
        Relative = 0x0040
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( FetchOrientation, UInt16 );

    enum class PinOption : Int32
    {
        /// <summary>
        /// default pin option 
        /// </summary>
        Default = 0x00000001,
        /// <summary>
        /// pin any copy of the object 
        /// </summary>
        Any = 0x00000003,
        /// <summary>
        /// pin recent copy of the object 
        /// </summary>
        Recent = 0x00000004,
        /// <summary>
        /// pin latest copy of the object 
        /// </summary>
        Latest = 0x00000005
    };


    enum class Duration : UInt16
    {
        /// <summary>
        /// This is not being treated as other predefined durations such as
        /// Session, Call etc, because this would not have an entry in the duration
        /// table and its functionality is primitive such that only allocate, free,
        /// resize memory are allowed, but one cannot create subduration out of this
        /// </summary>
        Process = 5,
        /// <summary>
        /// next special duration 
        /// </summary>
        Next = 6,
        UserCallback = 7,

        /// <summary>
        /// default 
        /// </summary>
        Default = 8,
        /// <summary>
        /// null duration 
        /// </summary>
        Null = 9,
        /// <summary>
        /// beginning sequence of duration 
        /// </summary>
        Begin = 10,
        /// <summary>
        /// the end of user session 
        /// </summary>
        Session = 10,
        /// <summary>
        /// the end of user transaction 
        /// </summary>
        Transaction = 11,
        /// <summary>
        /// DO NOT USE : the end of user client/server call 
        /// </summary>
        Call = 12,

        Statement = 13,
        /// <summary>
        /// This is to be used only during callouts.  It is similar to that
        /// of Duration::Call, but lasts only for the duration of a callout.
        /// Its heap is from PGA
        /// </summary>
        CallOut = 14,

        /// <summary>
        /// Invalid duration 
        /// </summary>
        Invalid = 0xFFFF

    };

    enum class TypeGetOpt
    {
        Header = 0x0000,
        All = 0x0001
    };


    enum class ParameterType : Byte
    {

        /// <summary>
        /// unknown
        /// </summary>
        Unknown = 0,
        /// <summary>
        /// table
        /// </summary>
        Table = 1,
        /// <summary>
        /// view
        /// </summary>
        View = 2,
        /// <summary>
        /// procedure
        /// </summary>
        Procedure = 3,
        /// <summary>
        /// function
        /// </summary>
        Function = 4,
        /// <summary>
        /// package
        /// </summary>
        Package = 5,
        /// <summary>
        /// user-defined type
        /// </summary>
        Type = 6,
        /// <summary>
        /// synonym
        /// </summary>
        Synonym = 7,
        /// <summary>
        /// sequence
        /// </summary>
        Sequence = 8,
        /// <summary>
        /// column
        /// </summary>
        Column = 9,
        /// <summary>
        /// argument
        /// </summary>
        Argument = 10,
        /// <summary>
        /// list
        /// </summary>
        List = 11,
        /// <summary>
        /// user-defined type's attribute 
        /// </summary>
        TypeAttribute = 12,
        /// <summary>
        /// collection type's element 
        /// </summary>
        Collection = 13,
        /// <summary>
        /// user-defined type's method 
        /// </summary>
        Method = 14,
        /// <summary>
        /// user-defined type method's arg 
        /// </summary>
        MethodArgument = 15,
        /// <summary>
        /// user-defined type method's result 
        /// </summary>
        MethodResult = 16,
        /// <summary>
        /// schema 
        /// </summary>
        Schema = 17,
        /// <summary>
        /// database 
        /// </summary>
        Database = 18,
        /// <summary>
        /// rule 
        /// </summary>
        Rule = 19,
        /// <summary>
        /// rule set 
        /// </summary>
        RuleSet = 20,
        /// <summary>
        /// evaluation context 
        /// </summary>
        EvaluationContext = 21,
        /// <summary>
        /// table alias 
        /// </summary>
        TableAlias = 22,
        /// <summary>
        /// variable type 
        /// </summary>
        VariableType = 23,
        /// <summary>
        /// name value pair 
        /// </summary>
        NameValuePair = 24,
        /// <summary>
        /// Hierarchy
        /// (OCI_PTYPE_HIERARCHY)
        /// </summary>
        Hierarchy = 25,
        /// <summary>
        /// AnalyticView
        /// (OCI_PTYPE_ANALYTIC_VIEW)
        /// </summary>
        AnalyticView = 26
    };


    enum class ParameterListType : Byte
    {
        /// <summary>
        /// Unknown
        /// (OCI_LTYPE_UNK)
        /// </summary>
        Unknown = 0,
        /// <summary>
        /// Column list
        /// (OCI_LTYPE_COLUMN)
        /// </summary>
        ColumnList = 1,
        /// <summary>
        /// Procedure argument list
        /// (OCI_LTYPE_ARG_PROC)
        /// </summary>
        ProcedureArgumentList = 2,
        /// <summary>
        /// Function argument list
        /// (OCI_LTYPE_ARG_FUNC)
        /// </summary>
        FunctionArgumentList = 3,
        /// <summary>
        /// Subprogram list
        /// (OCI_LTYPE_SUBPRG)
        /// </summary>
        SubprogramList = 4,
        /// <summary>
        /// Type attribute list
        /// (OCI_LTYPE_TYPE_ATTR)
        /// </summary>
        TypeAttributeList = 5,
        /// <summary>
        /// Type method list
        /// (OCI_LTYPE_TYPE_METHOD)
        /// </summary>
        TypeMethodList  = 6,
        /// <summary>
        /// Type procedure argument list
        /// (OCI_LTYPE_TYPE_ARG_PROC)
        /// </summary>
        TypeProcedureArgumentList = 7,
        /// <summary>
        /// Type function argument list
        /// (OCI_LTYPE_TYPE_ARG_FUNC)
        /// </summary>
        TypeFunctionArgumentList = 8,
        /// <summary>
        /// Schema object list
        /// (OCI_LTYPE_SCH_OBJ)
        /// </summary>
        SchemaObjectList = 9,
        /// <summary>
        /// Database schema list
        /// (OCI_LTYPE_DB_SCH)
        /// </summary>
        DatabaseSchemaList = 10,
        /// <summary>
        /// subtype (derived) type list
        /// (OCI_LTYPE_TYPE_SUBTYPE)
        /// </summary>
        TypeSubtypeList = 11,
        /// <summary>
        /// Table alias list
        /// (OCI_LTYPE_TABLE_ALIAS)
        /// </summary>
        TableAliasList = 12,
        /// <summary>
        /// Variable type list
        /// (OCI_LTYPE_VARIABLE_TYPE)
        /// </summary>
        VariableTypeList = 13,
        /// <summary>
        /// Name value list
        /// (OCI_LTYPE_NAME_VALUE)
        /// </summary>
        NameValueList = 14,
        /// <summary>
        /// Package type list
        /// (OCI_LTYPE_PACKAGE_TYPE)
        /// </summary>
        PackageTypeList = 15
    };

    /// <summary>
    /// Type parameter mode, specifies how arguments are passed to
    /// functions and procedures
    /// </summary>
    enum class TypeParamMode : Int32
    {
        /// <summary>
        /// In (OCI_TYPEPARAM_IN)
        /// </summary>
        In = 0,
        /// <summary>
        /// Out (OCI_TYPEPARAM_OUT)
        /// </summary>
        Out,
        /// <summary>
        /// InOut (OCI_TYPEPARAM_INOUT)
        /// </summary>
        InOut, 
        /// <summary>
        /// Call by reference (implicitly in-out)
        /// (OCI_TYPEPARAM_BYREF)
        /// </summary>
        ByRef,
        /// <summary>
        /// OUT with NOCOPY modifier
        /// (OCI_TYPEPARAM_OUTNCPY)
        /// </summary>
        OutNoCopy, 
        /// <summary>
        /// IN OUT with NOCOPY modifier
        /// (OCI_TYPEPARAM_INOUTNCPY)
        /// </summary>
        InOutNoCopy
    };


    enum class DateTimeErrorFlag : UInt32
    {
        None = 0,
        /// <summary>
        /// Bad day 
        /// </summary>
        InvalidDay = 0x1,
        /// <summary>
        /// Bad Day Low/high bit (1=low)
        /// </summary>
        DayBelowValid = 0x2,
        /// <summary>
        /// Bad MOnth
        /// </summary>
        InvalidMonth = 0x4,
        /// <summary>
        /// Bad Month Low/high bit (1=low) 
        /// </summary>
        MonthBelowValid = 0x8,
        /// <summary>
        /// Bad Year
        /// </summary>
        InvalidYear = 0x10,
        /// <summary>
        /// Bad Year Low/high bit (1=low) 
        /// </summary>
        YearBelowValid = 0x20,
        /// <summary>
        /// Bad Hour 
        /// </summary>
        InvalidHour = 0x40,
        /// <summary>
        /// Bad Hour Low/high bit (1=low) 
        /// </summary>
        HourBelowValid = 0x80,
        /// <summary>
        /// Bad Minute 
        /// </summary>
        InvalidMinute = 0x100,
        /// <summary>
        /// Bad Minute Low/high bit (1=low) 
        /// </summary>
        MinuteBelowValid = 0x200,
        /// <summary>
        /// Bad Second 
        /// </summary>
        InvalidSecond = 0x400,
        /// <summary>
        /// Bad second Low/high bit (1=low)
        /// </summary>
        SecondBelowValid = 0x800,
        /// <summary>
        /// Day is one of those "missing" from 1582
        /// </summary>
        DayMissingFrom1582 = 0x1000,
        /// <summary>
        /// Year may not equal zero
        /// </summary>
        YearZero = 0x2000,
        /// <summary>
        /// Bad Timezone
        /// </summary>
        InvalidTimezone = 0x4000,
        /// <summary>
        /// Bad date format input
        /// </summary>
        InvalidFormat = 0x8000
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( DateTimeErrorFlag, UInt32 );


    enum class IntervalErrorFlag : UInt32
    {
        None = 0,
        /// <summary>
        /// Bad day 
        /// </summary>
        InvalidDay = 0x1,
        /// <summary>
        /// Bad Day Low/high bit (1=low) 
        /// </summary>
        DayBelowValid = 0x2,
        /// <summary>
        /// Bad Month 
        /// </summary>
        InvalidMonth = 0x4,
        /// <summary>
        /// Bad Month Low/high bit (1=low) 
        /// </summary>
        MonthBelowValid = 0x8,
        /// <summary>
        /// Bad Year 
        /// </summary>
        InvalidYear = 0x10,
        /// <summary>
        /// Bad Year Low/high bit (1=low) 
        /// </summary>
        YearBelowValid = 0x20,
        /// <summary>
        /// Bad Hour 
        /// </summary>
        InvalidHour = 0x40,
        /// <summary>
        /// Bad Hour Low/high bit (1=low)
        /// </summary>
        HourBelowValid = 0x80,
        /// <summary>
        /// Bad Minute
        /// </summary>
        InvalidMinute = 0x100,
        /// <summary>
        /// Bad Minute Low/high bit(1=low)
        /// </summary>
        MinuteBelowValid = 0x200,
        /// <summary>
        /// Bad Second
        /// </summary>
        InvalidSecond = 0x400,
        /// <summary>
        /// bad second Low/high bit(1=low)
        /// </summary>
        SecondBelowValid = 0x800,
        /// <summary>
        /// Bad Fractional second
        /// </summary>
        InvalidFractionalSecond = 0x1000,
        /// <summary>
        /// Bad fractional second Low/High
        /// </summary>
        FractionalSecondBelowValid = 0x2000

    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( IntervalErrorFlag, UInt32 );


    enum class EventType : UInt32
    {

        /// <summary>
        /// None
        /// </summary>
        None = 0x0,
        /// <summary>
        /// Startup database
        /// </summary>
        Startup = 0x1,
        /// <summary>
        /// Shutdown database
        /// </summary>
        Shutdown = 0x2,
        /// <summary>
        /// Startup instance
        /// </summary>
        ShutdownAny = 0x3,
        /// <summary>
        /// Drop database
        /// </summary>
        DropDatabase = 0x4,
        /// <summary>
        /// Subscription deregistered
        /// </summary>
        SubscriptionDeregistered = 0x5,
        /// <summary>
        /// Object change notification
        /// </summary>
        ObjectChanged = 0x6,
        /// <summary>
        /// query result change
        /// </summary>
        QueryResultChanged = 0x7
    };


    enum class OperationCode : UInt32
    {
        /// <summary>
        /// all rows invalidated
        /// </summary>
        AllRows = 0x1,
        /// <summary>
        /// interested in all operations 
        /// </summary>
        AllOperations = 0x0,
        /// <summary>
        /// INSERT 
        /// </summary>
        Insert = 0x2,
        /// <summary>
        /// UPDATE
        /// </summary>
        Update = 0x4,
        /// <summary>
        /// DELETE
        /// </summary>
        Delete = 0x8,
        /// <summary>
        /// ALTER
        /// </summary>
        Alter = 0x10,
        /// <summary>
        /// DROP TABLE
        /// </summary>
        Drop = 0x20,
        /// <summary>
        /// GENERIC/ UNKNOWN
        /// </summary>
        Unknown = 0x40
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( OperationCode, UInt32 );

    enum class EnvironmentMode : UInt32
    {
        Default = 0,
        /// <summary>
        /// Application in Threaded environment
        /// </summary>
        Threaded = 0x00000001,
        /// <summary>
        /// Application in object environment
        /// </summary>
        Object = 0x00000002,
        /// <summary>
        /// Application is enabled for events
        /// </summary>
        Events = 0x00000004,
        /// <summary>
        /// the application is in shared mode
        /// </summary>
        Shared = 0x00000010,
        /// <summary>
        /// The following *TWO* are only valid for OCICreateEnvironment call:
        /// No user callback called during ini
        /// </summary>
        NoUserCallbacksDuringInitialization = 0x00000040,
        /// <summary>
        /// the environment handle will not be protected by a mutex internally
        /// </summary>
        NoMutex = 0x00000080,
        /// <summary>
        /// Used for shared forms
        /// </summary>
        SharedExt = 0x00000100,
        /// <summary>
        /// all connections always blocking
        /// </summary>
        AlwaysBlocking = 0x00000400,
        /// <summary>
        /// allow  LDAP connections
        /// </summary>
        UseLDAP = 0x00001000,
        /// <summary>
        /// only register to LDAP
        /// </summary>
        RegisterLDAPOnly = 0x00002000,
        /// <summary>
        /// mode for all UTF16 metadata
        /// </summary>
        UTF16 = 0x00004000,
        /// <summary>
        /// turn on AFC blank padding when rlenp present
        /// </summary>
        AFCPadOn = 0x00008000,
        /// <summary>
        /// adopt new length semantics the new length semantics, always bytes, is used by OCIEnvNlsCreate
        /// </summary>
        NewLengthSemantics = 0x00020000,
        /// <summary>
        ///  Do not mutex stmt handle
        /// </summary>
        NoMutexStmt = 0x00040000,
        /// <summary>
        /// Mutex only the environment handle
        /// </summary>
        MutexEnvOnly = 0x00080000,
        /// <summary>
        /// suppress nls validation nls validation suppression is on 
        /// by default; use EnableNLSValidation to disable it
        /// </summary>
        SuppressNLSValidation = 0x00100000,
        /// <summary>
        /// try and acquire mutex
        /// </summary>
        MutexTry = 0x00200000,
        /// <summary>
        /// nchar literal replace on
        /// </summary>
        NCharLiteralReplaceOn = 0x00400000,
        /// <summary>
        /// nchar literal replace off
        /// </summary>
        NCharLiteralReplaceOff = 0x00800000,
        /// <summary>
        /// enable nls validation
        /// </summary>
        EnableNLSValidation = 0x01000000

    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( EnvironmentMode, UInt32 );




    enum class Attribute : UInt32
    {
        /// <summary>
        /// the OCI function code
        /// </summary>
        FNCODE = 1,
        /// <summary>
        /// is the environment initialized in object mode 
        /// </summary>
        OBJECT = 2,
        /// <summary>
        /// non blocking mode 
        /// </summary>
        NONBLOCKING_MODE = 3,
        /// <summary>
        /// the SQL verb
        /// </summary>
        SQLCODE = 4,
        /// <summary>
        /// the environment handle 
        /// </summary>
        ENV = 5,
        /// <summary>
        /// the server handle 
        /// </summary>
        SERVER = 6,
        /// <summary>
        /// the user session handle
        /// </summary>
        SESSION = 7,
        /// <summary>
        /// the transaction handle
        /// </summary>
        TRANS = 8,
        /// <summary>
        /// the rows processed so far
        /// </summary>
        ROW_COUNT = 9,
        /// <summary>
        /// the SQL verb of the statement
        /// </summary>
        SQLFNCODE = 10,
        /// <summary>
        /// sets the number of rows to prefetch
        /// </summary>
        PREFETCH_ROWS = 11,
        /// <summary>
        /// the prefetch rows of nested table
        /// </summary>
        NESTED_PREFETCH_ROWS = 12,
        /// <summary>
        /// memory limit for rows fetched
        /// </summary>
        PREFETCH_MEMORY = 13,
        /// <summary>
        /// memory limit for nested rows
        /// </summary>
        NESTED_PREFETCH_MEMORY = 14,
        /// <summary>
        /// this specifies the bind and define size in characters
        /// </summary>
        CHAR_COUNT = 15,

        /// <summary>
        /// packed decimal scale
        /// </summary>
        PDSCL = 16,
        /// <summary>
        /// fs prec for datetime data types
        /// </summary>
        FSPRECISION = PDSCL,
        /// <summary>
        /// To enable object creation with  non-NULL attributes by default, set the
        /// following to TRUE.
        /// By default, object is created with NULL attributes
        /// </summary>
        OBJECT_NEWNOTNULL = 0x00000010,
        /// <summary>
        /// packed decimal format 
        /// </summary>
        PDPRC = 17,
        /// <summary>
        /// fs prec for datetime data types 
        /// </summary>
        LFPRECISION = PDPRC,
        /// <summary>
        /// number of column in the select list
        /// </summary>
        PARAM_COUNT = 18,
        /// <summary>
        /// the rowid
        /// </summary>
        ROWID = 19,
        /// <summary>
        /// the character set value
        /// </summary>
        CHARSET = 20,
        /// <summary>
        /// NCHAR type
        /// </summary>
        NCHAR = 21,
        /// <summary>
        /// username attribute
        /// </summary>
        USERNAME = 22,
        /// <summary>
        /// password attribute
        /// </summary>
        PASSWORD = 23,
        /// <summary>
        /// statement type
        /// </summary>
        STMT_TYPE = 24,
        /// <summary>
        /// user friendly global name 
        /// </summary>
        INTERNAL_NAME = 25,
        /// <summary>
        /// the internal name for global txn
        /// </summary>
        EXTERNAL_NAME = 26,
        /// <summary>
        /// XOPEN defined global transaction id
        /// </summary>
        XID = 27,
        /// <summary>
        /// 
        /// </summary>
        TRANS_LOCK = 28,
        /// <summary>
        /// string to identify a global transaction
        /// </summary>
        TRANS_NAME = 29,
        /// <summary>
        /// memory allocated on the heap
        /// </summary>
        HEAPALLOC = 30,
        /// <summary>
        /// Character Set ID
        /// </summary>
        CHARSET_ID = 31,
        /// <summary>
        /// charset id in env 
        /// </summary>
        ENV_CHARSET_ID = CHARSET_ID,
        /// <summary>
        /// Character Set Form 
        /// </summary>
        CHARSET_FORM = 32,
        /// <summary>
        /// To enable object change detection mode, set this to TRUE
        /// </summary>
        OBJECT_DETECTCHANGE = 0x00000020,
        /// <summary>
        /// Maximumsize of data on the server  
        /// </summary>
        MAXDATA_SIZE = 33,
        /// <summary>
        /// object cache optimal size 
        /// </summary>
        CACHE_OPT_SIZE = 34,
        /// <summary>
        /// object cache maximum size percentage
        /// </summary>
        CACHE_MAX_SIZE = 35,
        /// <summary>
        /// object cache default pin option
        /// </summary>
        PINOPTION = 36,
        /// <summary>
        /// object cache default allocation duration
        /// </summary>
        ALLOC_DURATION = 37,
        /// <summary>
        /// object cache default pin duration 
        /// </summary>
        PIN_DURATION = 38,
        /// <summary>
        /// Format Descriptor object attribute
        /// </summary>
        FDO = 39,
        /// <summary>
        /// Callback to process outbind data
        /// </summary>
        POSTPROCESSING_CALLBACK = 40,
        /// <summary>
        /// Callback context to process outbind data 
        /// </summary>
        POSTPROCESSING_CONTEXT = 41,
        /// <summary>
        /// Number of rows returned in current iter - for Bind handles
        /// </summary>
        ROWS_RETURNED = 42,
        /// <summary>
        /// Failover Callback attribute
        /// </summary>
        FOCBK = 43,
        /// <summary>
        /// is the server/service context in V8 mode
        /// </summary>
        IN_V8_MODE = 44,
        /// <summary>
        /// empty lob ?
        /// </summary>
        LOBEMPTY = 45,
        /// <summary>
        /// session language handle
        /// </summary>
        SESSLANG = 46,

        /// <summary>
        /// visibility
        /// </summary>
        VISIBILITY = 47,
        /// <summary>
        /// relative message id
        /// </summary>
        RELATIVE_MSGID = 48,
        /// <summary>
        /// sequence deviation
        /// </summary>
        SEQUENCE_DEVIATION = 49,
        /// <summary>
        /// consumer name
        /// </summary>
        CONSUMER_NAME = 50,

        // complex object retrieval parameter attributes 

        COMPLEXOBJECTCOMP_TYPE = 50,
        /// <summary>
        /// dequeue mode
        /// </summary>
        DEQ_MODE = 51,
        COMPLEXOBJECTCOMP_TYPE_LEVEL = 51,
        /// <summary>
        /// navigation
        /// </summary>
        NAVIGATION = 52,
        COMPLEXOBJECT_LEVEL = 52,
        /// <summary>
        /// wait
        /// </summary>
        WAIT = 53,
        COMPLEXOBJECT_COLL_OUTOFLINE = 53,
        /// <summary>
        /// dequeue message id
        /// </summary>
        DEQ_MSGID = 54,

        /// <summary>
        /// priority
        /// </summary>
        PRIORITY = 55,
        /// <summary>
        /// delay
        /// </summary>
        DELAY = 56,
        /// <summary>
        /// expiration
        /// </summary>
        EXPIRATION = 57,
        /// <summary>
        /// correlation id
        /// </summary>
        CORRELATION = 58,
        /// <summary>
        /// # of attempts
        /// </summary>
        ATTEMPTS = 59,
        /// <summary>
        /// recipient list
        /// </summary>
        RECIPIENT_LIST = 60,
        /// <summary>
        /// exception queue name
        /// </summary>
        EXCEPTION_QUEUE = 61,
        /// <summary>
        /// enqueue time (only OCIAttrGet)
        /// </summary>
        ENQ_TIME = 62,
        /// <summary>
        /// message state (only OCIAttrGet)
        /// </summary>
        MSG_STATE = 63,
        /// <summary>
        /// agent name
        /// </summary>
        AGENT_NAME = 64,

        /// <summary>
        /// To enable sorting of the objects that belong to the same table
        /// before being flushed through OCICacheFlush.
        /// Please note that by enabling this object cache will not be flushing
        /// the objects in the same order they were dirtied 
        /// </summary>
        CACHE_ARRAYFLUSH = 0x00000040,
        /// <summary>
        /// agent address
        /// </summary>
        AGENT_ADDRESS = 65,
        /// <summary>
        /// agent protocol
        /// </summary>
        AGENT_PROTOCOL = 66,
        /// <summary>
        /// user property
        /// </summary>
        USER_PROPERTY = 67,
        /// <summary>
        /// sender id
        /// </summary>
        SENDER_ID = 68,
        /// <summary>
        /// original message id
        /// </summary>
        ORIGINAL_MSGID = 69,
        /// <summary>
        /// queue name
        /// </summary>
        QUEUE_NAME = 70,
        /// <summary>
        /// message id
        /// </summary>
        NFY_MSGID = 71,
        /// <summary>
        /// message properties
        /// </summary>
        MSG_PROP = 72,

        /// <summary>
        /// num of errs in array DML
        /// </summary>
        NUM_DML_ERRORS = 73,
        /// <summary>
        /// row offset in the array
        /// </summary>
        DML_ROW_OFFSET = 74,
        /// <summary>
        /// default date format string
        /// </summary>
        DATEFORMAT = 75,
        /// <summary>
        /// buffer address
        /// </summary>
        BUF_ADDR = 76,
        /// <summary>
        /// buffer size
        /// </summary>
        BUF_SIZE = 77,

        // For values 78 - 80, see DirPathAPI attribute section in this file 

        /// <summary>
        /// number of rows in column array
        /// </summary>
        /// <remarks>
        /// NOTE that NUM_COLS is a column array attribute too.
        /// </remarks>
        NUM_ROWS = 81,
        /// <summary>
        /// columns of column array processed so far.
        /// </summary>
        COL_COUNT = 82,
        /// <summary>
        /// str off of last row processed
        /// </summary>
        STREAM_OFFSET = 83,
        /// <summary>
        /// Shared Heap Allocation Size
        /// </summary>
        SHARED_HEAPALLOC = 84,
        /// <summary>
        /// server group name
        /// </summary>
        SERVER_GROUP = 85,
        /// <summary>
        /// migratable session attribute
        /// </summary>
        MIGSESSION = 86,
        /// <summary>
        /// Temporary LOBs
        /// </summary>
        NOCACHE = 87,
        /// <summary>
        /// Pool Size
        /// </summary>
        MEMPOOL_SIZE = 88,
        /// <summary>
        /// Instance name
        /// </summary>
        MEMPOOL_INSTNAME = 89,
        /// <summary>
        /// Application name
        /// </summary>
        MEMPOOL_APPNAME = 90,
        /// <summary>
        /// Home Directory name
        /// </summary>
        MEMPOOL_HOMENAME = 91,
        /// <summary>
        /// Pool Model (proc,thrd,both)
        /// </summary>
        MEMPOOL_MODEL = 92,
        /// <summary>
        /// Modes
        /// </summary>
        MODES = 93,
        /// <summary>
        /// name of subscription
        /// </summary>
        SUBSCR_NAME = 94,
        /// <summary>
        /// associated callback
        /// </summary>
        SUBSCR_CALLBACK = 95,
        /// <summary>
        /// associated callback context
        /// </summary>
        SUBSCR_CTX = 96,
        /// <summary>
        /// associated payload
        /// </summary>
        SUBSCR_PAYLOAD = 97,
        /// <summary>
        /// associated namespace
        /// </summary>
        SUBSCR_NAMESPACE = 98,
        /// <summary>
        /// Proxy user credentials
        /// </summary>
        PROXY_CREDENTIALS = 99,
        /// <summary>
        /// Initial client role list
        /// </summary>
        INITIAL_CLIENT_ROLES = 100,

        /// <summary>
        /// the display name Only Columns
        /// </summary>
        DISP_NAME = 100,

        /// <summary>
        /// unknown attribute
        /// </summary>
        UNK = 101,
        /// <summary>
        /// encrypted data size
        /// </summary>
        ENCC_SIZE = 101,
        /// <summary>
        /// number of columns
        /// </summary>
        NUM_COLS = 102,
        /// <summary>
        /// column is encrypted ?
        /// </summary>
        COL_ENC = 102,
        /// <summary>
        /// parameter of the column list
        /// </summary>
        LIST_COLUMNS = 103,
        /// <summary>
        /// is encrypted column salted ?
        /// </summary>
        COL_ENC_SALT = 103,
        /// <summary>
        /// DBA of the segment header
        /// </summary>
        RDBA = 104,
        /// <summary>
        /// column properties
        /// </summary>
        COL_PROPERTIES = 104,
        /// <summary>
        /// whether the table is clustered
        /// </summary>
        CLUSTERED = 105,
        /// <summary>
        /// whether the table is partitioned
        /// </summary>
        PARTITIONED = 106,
        /// <summary>
        /// whether the table is index only
        /// </summary>
        INDEX_ONLY = 107,
        /// <summary>
        /// parameter of the argument list
        /// </summary>
        LIST_ARGUMENTS = 108,
        /// <summary>
        /// parameter of the subprogram list
        /// </summary>
        LIST_SUBPROGRAMS = 109,
        /// <summary>
        /// REF to the type descriptor
        /// </summary>
        REF_TDO = 110,
        /// <summary>
        /// the database link name
        /// </summary>
        LINK = 111,
        /// <summary>
        /// minimum value
        /// </summary>
        MIN = 112,
        /// <summary>
        /// maximum value
        /// </summary>
        MAX = 113,
        /// <summary>
        /// increment value
        /// </summary>
        INCR = 114,
        /// <summary>
        /// number of sequence numbers cached
        /// </summary>
        CACHE = 115,
        /// <summary>
        /// whether the sequence is ordered
        /// </summary>
        ORDER = 116,
        /// <summary>
        /// high-water mark
        /// </summary>
        HW_MARK = 117,
        /// <summary>
        /// type's schema name
        /// </summary>
        TYPE_SCHEMA = 118,
        /// <summary>
        /// timestamp of the object
        /// </summary>
        TIMESTAMP = 119,
        /// <summary>
        /// number of sttributes
        /// </summary>
        NUM_ATTRS = 120,
        /// <summary>
        /// number of parameters
        /// </summary>
        NUM_PARAMS = 121,
        /// <summary>
        /// object id for a table or view
        /// </summary>
        OBJID = 122,
        /// <summary>
        /// type of info described by
        /// </summary>
        PTYPE = 123,
        /// <summary>
        /// parameter descriptor
        /// </summary>
        PARAM = 124,
        /// <summary>
        /// overload ID for funcs and procs
        /// </summary>
        OVERLOAD_ID = 125,
        /// <summary>
        /// table name space
        /// </summary>
        TABLESPACE = 126,
        /// <summary>
        /// TDO of a type
        /// </summary>
        TDO = 127,
        /// <summary>
        /// list type
        /// </summary>
        LTYPE = 128,
        /// <summary>
        /// Parse Error offset
        /// </summary>
        PARSE_ERROR_OFFSET = 129,
        /// <summary>
        /// whether table is temporary
        /// </summary>
        IS_TEMPORARY = 130,
        /// <summary>
        /// whether table is typed
        /// </summary>
        IS_TYPED = 131,
        /// <summary>
        /// duration of temporary table
        /// </summary>
        DURATION = 132,
        /// <summary>
        /// is invoker rights
        /// </summary>
        IS_INVOKER_RIGHTS = 133,
        /// <summary>
        /// top level schema obj name
        /// </summary>
        OBJ_NAME = 134,
        /// <summary>
        /// schema name
        /// </summary>
        OBJ_SCHEMA = 135,
        /// <summary>
        /// top level schema object id
        /// </summary>
        OBJ_ID = 136,
        /// <summary>
        /// parameter of the package type list
        /// </summary>
        LIST_PKG_TYPES = 137,

        // For values 137 - 141, see DirPathAPI attribute section in this file 

        /// <summary>
        /// transaction timeout
        /// </summary>
        TRANS_TIMEOUT = 142,
        /// <summary>
        /// state of the server handle
        /// </summary>
        SERVER_STATUS = 143,
        /// <summary>
        /// statement txt in stmt hdl
        /// </summary>
        STATEMENT = 144,

        // For value 145, see DirPathAPI attribute section in this file 

        /// <summary>
        /// dequeue condition
        /// </summary>
        DEQCOND = 146,
        /// <summary>
        /// reserved
        /// </summary>
        Reserved_2 = 147,

        /// <summary>
        /// recepient of subscription
        /// </summary>
        SUBSCR_RECPT = 148,
        /// <summary>
        /// protocol for recepient 
        /// </summary>
        SUBSCR_RECPTPROTO = 149,
        SubscriberRecepientProtocol = SUBSCR_RECPTPROTO,

        // For values 150 - 151, see DirPathAPI attribute section in this file 

        LDAP_HOST = 153,              /* LDAP host to connect to */
        LDAP_PORT = 154,              /* LDAP port to connect to */
        BIND_DN = 155,                              /* bind DN */
        LDAP_CRED = 156,       /* credentials to connect to LDAP */
        WALL_LOC = 157,               /* client wallet location */
        LDAP_AUTH = 158,           /* LDAP authentication method */
        LDAP_CTX = 159,        /* LDAP adminstration context DN */
        SERVER_DNS = 160,      /* list of registration server DNs */

        DN_COUNT = 161,             /* the number of server DNs */
        SERVER_DN = 162,                  /* server DN attribute */

        MAXCHAR_SIZE = 163,     /* max char size of data */

        CURRENT_POSITION = 164, /* for scrollable result sets*/

        /* Added to get attributes for ref cursor to statement handle */
        Reserved_3 = 165,                  /* reserved */
        Reserved_4 = 166,                  /* reserved */

        /* For value 167, see DirPathAPI attribute section in this file */

        DIGEST_ALGO = 168,          /* digest algorithm */
        CERTIFICATE = 169,               /* certificate */
        SIGNATURE_ALGO = 170,       /* signature algorithm */
        CANONICAL_ALGO = 171,    /* canonicalization algo. */
        PRIVATE_KEY = 172,               /* private key */
        DIGEST_VALUE = 173,              /* digest value */
        SIGNATURE_VAL = 174,           /* signature value */
        SIGNATURE = 175,                 /* signature */

        /* attribute for setting OCI stmt caching size in svchp */
        STMTCACHESIZE = 176,        /* size of the stm cache */
        SESSGET_FLAGS = 177, /* OCISessionGet returned flags */

        /* --------------------------- Connection Pool Attributes ------------------ */
        CONN_NOWAIT = 178,
        CONN_BUSY_COUNT = 179,
        CONN_OPEN_COUNT = 180,
        CONN_TIMEOUT = 181,
        STMT_STATE = 182,
        CONN_MIN = 183,
        CONN_MAX = 184,
        CONN_INCR = 185,

        /* For value 187, see DirPathAPI attribute section in this file */

        NUM_OPEN_STMTS = 188,     /* open stmts in session */
        Reserved_189 = 189,
        DESCRIBE_NATIVE = Reserved_189,

        BIND_COUNT = 190,   /* number of bind postions */
        HANDLE_POSITION = 191, /* pos of bind/define handle */
        Reserved_5 = 192,                 /* reserverd */
        SERVER_BUSY = 193, /* call in progress on server*/

        /* For value 194, see DirPathAPI attribute section in this file */

        /* notification presentation for recipient */
        SUBSCR_RECPTPRES = 195,
        TRANSFORMATION = 196, /* AQ message transformation */

        ROWS_FETCHED = 197, /* rows fetched in last call */

        /* --------------------------- Snapshot attributes ------------------------- */
        SCN_BASE = 198,             /* snapshot base */
        SCN_WRAP = 199,             /* snapshot wrap */

        /* --------------------------- Miscellanous attributes --------------------- */
        Reserved_6 = 200,                  /* reserved */
        READONLY_TXN = 201,           /* txn is readonly */
        Reserved_7 = 202,                  /* reserved */
        ERRONEOUS_COLUMN = 203, /* position of erroneous col */
        Reserved_8 = 204,                  /* reserved */
        ASM_VOL_SPRT = 205,     /* ASM volume supported? */

        /* For value 206, see DirPathAPI attribute section in this file */

        INST_TYPE = 207,      /* oracle instance type */
        SPOOL_STMTCACHESIZE = 208,   /*Stmt cache size of pool  */
        ENV_UTF16 = 209,     /* is env in utf16 mode? */

        /*Only Stored Procs */
        Reserved_9 = 210,                  /* reserved */
        OVERLOAD = 210,/* is this position overloaded */
        Reserved_10 = 211,                  /* reserved */
        LEVEL = 211, /* level for structured types */
        HAS_DEFAULT = 212,        /* has a default value */
        IOMODE = 213,              /* in, out inout */

        /* For values 212 and 213, see ALSO DirPathAPI attribute section in this file */

        Reserved_12 = 214,                  /* reserved */
        RADIX = 214,            /* returns a radix */
        Reserved_13 = 215,                  /* reserved */
        NUM_ARGS = 215,  /* total number of arguments */
        IS_EXTERNAL = 216, /* whether table is external */
        TYPECODE = 216,       /* object or collection */


        /* -------------------------- Statement Handle Attributes ------------------ */

        Reserved_15 = 217,                  /* reserved */
        COLLECTION_TYPECODE = 217,     /* varray or nested table */
        STMT_IS_RETURNING = 218, /* stmt has returning clause */
        VERSION = 218,      /* user assigned version */
        Reserved_16 = 219,                  /* reserved */
        IS_INCOMPLETE_TYPE = 219, /* is this an incomplete type */
        Reserved_17 = 220,                  /* reserved */
        IS_SYSTEM_TYPE = 220,              /* a system type */
        Reserved_18 = 221,                  /* reserved */
        IS_PREDEFINED_TYPE = 221,          /* a predefined type */

        /* --------------------------- session attributes ---------------------------*/
        Reserved_19 = 222,                  /* reserved */
        IS_TRANSIENT_TYPE = 222,           /* a transient type */
        Reserved_20 = 223,                  /* reserved */
        IS_SYSTEM_GENERATED_TYPE = 223,      /* system generated type */
        CURRENT_SCHEMA = 224,            /* Current Schema */
        HAS_NESTED_TABLE = 224, /* contains nested table attr */

        /* ------------------------- notification subscription ----------------------*/
        SUBSCR_QOSFLAGS = 225,                 /* QOS flags */
        HAS_LOB = 225,        /* has a lob attribute */
        SUBSCR_PAYLOADCBK = 226,          /* Payload callback */
        HAS_FILE = 226,       /* has a file attribute */
        SUBSCR_TIMEOUT = 227,                   /* Timeout */
        COLLECTION_ELEMENT = 227, /* has a collection attribute */
        SUBSCR_NAMESPACE_CTX = 228,         /* Namespace context */
        NUM_TYPE_ATTRS = 228,  /* number of attribute types */
        SUBSCR_CQ_QOSFLAGS = 229,
        /* change notification (CQ) specific QOS flags */
        LIST_TYPE_ATTRS = 229,    /* list of type attributes */
        SUBSCR_CQ_REGID = 230,
        /* change notification registration id */
        NUM_TYPE_METHODS = 230,     /* number of type methods */
        SUBSCR_NTFN_GROUPING_CLASS = 231,       /* ntfn grouping class */
        LIST_TYPE_METHODS = 231,       /* list of type methods */
        SUBSCR_NTFN_GROUPING_VALUE = 232,       /* ntfn grouping value */
        MAP_METHOD = 232,         /* map method of type */
        SUBSCR_NTFN_GROUPING_TYPE = 233,        /* ntfn grouping type */
        ORDER_METHOD = 233,       /* order method of type */
        SUBSCR_NTFN_GROUPING_START_TIME = 234,/* ntfn grp start time */
        NUM_ELEMS = 234,  /* number of elements */
        SUBSCR_NTFN_GROUPING_REPEAT_COUNT = 235, /* ntfn grp rep count */
        ENCAPSULATION = 235, /* encapsulation level */
        AQ_NTFN_GROUPING_MSGID_ARRAY = 236, /* aq grp msgid array */
        IS_SELFISH = 236,      /* method selfish */
        AQ_NTFN_GROUPING_COUNT = 237,  /* ntfns recd in grp */
        IS_VIRTUAL = 237,             /* virtual */
        IS_INLINE = 238,                     /* inline */
        IS_CONSTANT = 239,                   /* constant */
        HAS_RESULT = 240,                 /* has result */
        IS_CONSTRUCTOR = 241,                /* constructor */
        IS_DESTRUCTOR = 242,                 /* destructor */
        IS_OPERATOR = 243,                   /* operator */
        IS_MAP = 244,               /* a map method */
        IS_ORDER = 245,               /* order method */
        IS_RNDS = 246,  /* read no data state method */
        IS_RNPS = 247,      /* read no process state */
        IS_WNDS = 248, /* write no data state method */
        IS_WNPS = 249,     /* write no process state */

        DESC_PUBLIC = 250,              /* public object */

        /* Object Cache Enhancements : attributes for User Constructed Instances     */
        CACHE_CLIENT_CONTEXT = 251,
        UCI_CONSTRUCT = 252,
        UCI_DESTRUCT = 253,
        UCI_COPY = 254,
        UCI_PICKLE = 255,
        UCI_UNPICKLE = 256,
        UCI_REFRESH = 257,

        /* for type inheritance */
        IS_SUBTYPE = 258,
        SUPERTYPE_SCHEMA_NAME = 259,
        SUPERTYPE_NAME = 260,

        /* for schemas */
        LIST_OBJECTS = 261,  /* list of objects in schema */

        /* for database */
        NCHARSET_ID = 262,                /* char set id */
        ENV_NCHARSET_ID = NCHARSET_ID, /* ncharset id in env */
        LIST_SCHEMAS = 263,            /* list of schemas */
        MAX_PROC_LEN = 264,       /* max procedure length */
        MAX_COLUMN_LEN = 265,     /* max column name length */
        CURSOR_COMMIT_BEHAVIOR = 266,     /* cursor commit behavior */
        MAX_CATALOG_NAMELEN = 267,         /* catalog namelength */
        CATALOG_LOCATION = 268,           /* catalog location */
        SAVEPOINT_SUPPORT = 269,          /* savepoint support */
        NOWAIT_SUPPORT = 270,             /* nowait support */
        AUTOCOMMIT_DDL = 271,             /* autocommit DDL */
        LOCKING_MODE = 272,               /* locking mode */

        /* for externally initialized context */
        APPCTX_SIZE = 273, /* count of context to be init*/
        APPCTX_LIST = 274, /* count of context to be init*/
        APPCTX_NAME = 275, /* name  of context to be init*/
        APPCTX_ATTR = 276, /* attr  of context to be init*/
        APPCTX_VALUE = 277, /* value of context to be init*/

        /* for client id propagation */
        CLIENT_IDENTIFIER = 278,   /* value of client id to set*/

        /* for inheritance - part 2 */
        IS_FINAL_TYPE = 279,            /* is final type ? */
        IS_INSTANTIABLE_TYPE = 280,     /* is instantiable type ? */
        IS_FINAL_METHOD = 281,          /* is final method ? */
        IS_INSTANTIABLE_METHOD = 282,   /* is instantiable method ? */
        IS_OVERRIDING_METHOD = 283,     /* is overriding method ? */

        DESC_SYNBASE = 284,   /* Describe the base object */


        CHAR_USED = 285,      /* char length semantics */
        CHAR_SIZE = 286,                /* char length */

        /* SQLJ support */
        IS_JAVA_TYPE = 287, /* is java implemented type ? */

        EDITION = 288,                /* ORA_EDITION */

        /* N-Tier support */
        DISTINGUISHED_NAME = 300,        /* use DN as user name */

        BIND_ROWCBK = 301,          /* bind row callback */
        KERBEROS_TICKET = 301,    /* Kerberos ticket as cred. */
        BIND_ROWCTX = 302,  /* ctx for bind row callback */
        ORA_DEBUG_JDWP = 302,    /* ORA_DEBUG_JDWP attribute */
        SKIP_BUFFER = 303,   /* skip buffer in array ops */
        Reserved_14 = 303,                    /* reserved */

        CQ_QUERYID = 304,
        EVTCBK = 304,                /* ha callback */
        EVTCTX = 305,        /* ctx for ha callback */

        /* ------------------ User memory attributes (all handles) ----------------- */
        USER_MEMORY = 306,     /* pointer to user memory */

        /* For values 303 - 307, see ALSO DirPathAPI attribute section in this file */

        ACCESS_BANNER = 307,              /* access banner */
        AUDIT_BANNER = 308,               /* audit banner */
        SPOOL_TIMEOUT = 308,           /* session timeout */
        SPOOL_GETMODE = 309,          /* session get mode */
        SPOOL_BUSY_COUNT = 310,        /* busy session count */
        SPOOL_OPEN_COUNT = 311,        /* open session count */
        SPOOL_MIN = 312,         /* min session count */
        SPOOL_MAX = 313,         /* max session count */
        SPOOL_INCR = 314,   /* session increment count */

        /*---------------------------- For XML Types ------------------------------- */
        /* For table, view and column */
        IS_XMLTYPE = 315,         /* Is the type an XML type? */
        XMLSCHEMA_NAME = 316,               /* Name of XML Schema */
        XMLELEMENT_NAME = 317,              /* Name of XML Element */
        XMLSQLTYPSCH_NAME = 318,    /* SQL type's schema for XML Ele */
        XMLSQLTYPE_NAME = 319,     /* Name of SQL type for XML Ele */
        XMLTYPE_STORED_OBJ = 320,       /* XML type stored as object? */


        /*---------------------------- For Subtypes ------------------------------- */
        /* For type */
        HAS_SUBTYPES = 321,                    /* Has subtypes? */
        NUM_SUBTYPES = 322,               /* Number of subtypes */
        LIST_SUBTYPES = 323,                 /* List of subtypes */


        /* XML flag */
        XML_HRCHY_ENABLED = 324,               /* hierarchy enabled? */

        /* Method flag */
        IS_OVERRIDDEN_METHOD = 325,           /* Method is overridden? */


        /* For values 326 - 335, see DirPathAPI attribute section in this file */

        /*------------- Attributes for 10i Distributed Objects ----------------------*/
        OBJ_SUBS = 336, /* obj col/tab substitutable */

        /* For values 337 - 338, see DirPathAPI attribute section in this file */

        /*---------- Attributes for 10i XADFIELD (NLS language, territory -----------*/
        XADFIELD_Reserved_1 = 339,                  /* reserved */
        XADFIELD_Reserved_2 = 340,                  /* reserved */

        /*------------- Kerberos Secure Client Identifier ---------------------------*/
        KERBEROS_CID = 341, /* Kerberos db service ticket*/

        /*------------------------ Attributes for Rules objects ---------------------*/
        CONDITION = 342,            /* rule condition */
        COMMENT = 343,                   /* comment */
        VALUE = 344,             /* Anydata value */
        EVAL_CONTEXT_OWNER = 345,        /* eval context owner */
        EVAL_CONTEXT_NAME = 346,         /* eval context name */
        EVALUATION_FUNCTION = 347,        /* eval function name */
        VAR_TYPE = 348,             /* variable type */
        VAR_VALUE_FUNCTION = 349,   /* variable value function */

        XSTREAM_ACK_INTERVAL = 350,      /* XStream ack interval */
        VAR_METHOD_FUNCTION = 350, /* variable method function */
        XSTREAM_IDLE_TIMEOUT = 351,      /* XStream idle timeout */
        ACTION_CONTEXT = 351,           /* action context */
        LIST_TABLE_ALIASES = 352,     /* list of table aliases */
        LIST_VARIABLE_TYPES = 353,    /* list of variable types */
        TABLE_NAME = 356,                /* table name */

        /* For values 357 - 359, see DirPathAPI attribute section in this file */

        MESSAGE_CSCN = 360,              /* message cscn */
        MESSAGE_DSCN = 361,              /* message dscn */

        /*--------------------- Audit Session ID ------------------------------------*/
        AUDIT_SESSION_ID = 362,          /* Audit session ID */

        /*--------------------- Kerberos TGT Keys -----------------------------------*/
        KERBEROS_KEY = 363,  /* n-tier Kerberos cred key */
        KERBEROS_CID_KEY = 364,    /* SCID Kerberos cred key */


        TRANSACTION_NO = 365,         /* AQ enq txn number */

        /*----------------------- Attributes for End To End Tracing -----------------*/
        MODULE = 366,        /* module for tracing */
        ACTION = 367,        /* action for tracing */
        CLIENT_INFO = 368,               /* client info */
        COLLECT_CALL_TIME = 369,         /* collect call time */
        CALL_TIME = 370,         /* extract call time */
        ECONTEXT_ID = 371,      /* execution-id context */
        ECONTEXT_SEQ = 372,  /*execution-id sequence num */

        /*------------------------------ Session attributes -------------------------*/
        SESSION_STATE = 373,             /* session state */
#define OCI_SESSION_STATELESS  1                             /* valid states */
#define OCI_SESSION_STATEFUL   2
        SESSION_STATETYPE = 374,        /* session state type */
#define OCI_SESSION_STATELESS_DEF  0                    /* valid state types */
#define OCI_SESSION_STATELESS_CAL  1
#define OCI_SESSION_STATELESS_TXN  2
#define OCI_SESSION_STATELESS_APP  3
        SESSION_STATE_CLEARED = 376,     /* session state cleared */
        SESSION_MIGRATED = 377,       /* did session migrate */
        SESSION_PRESERVE_STATE = 388,    /* preserve session state */

        /* -------------------------- Admin Handle Attributes ---------------------- */
        ADMIN_PFILE = 389,    /* client-side param file */

        SUBSCR_PORTNO = 390,                  /* port no to listen */
        HOSTNAME = 390,               /* SYS_CONTEXT hostname */
        DBNAME = 391,                  /* SYS_CONTEXT dbname */
        INSTNAME = 392,           /* SYS_CONTEXT instance name */
        SERVICENAME = 393,            /* SYS_CONTEXT service name */
        INSTSTARTTIME = 394,      /* v$instance instance start time */
        HA_TIMESTAMP = 395,                          /* event time */
        Reserved_22 = 396,                            /* reserved */
        Reserved_23 = 397,                            /* reserved */
        Reserved_24 = 398,                            /* reserved */
        DBDOMAIN = 399,                           /* db domain */
        EVENTTYPE = 400,                          /* event type */

        HA_SOURCE = 401,

        CHNF_TABLENAMES = 401,          /* out: array of table names */
        CHNF_ROWIDS = 402,     /* in: rowids needed */
        HA_STATUS = 402,
# define OCI_HA_STATUS_DOWN          0/* valid values for HA_STATUS */
# define OCI_HA_STATUS_UP            1
        CHNF_OPERATIONS = 403,  /* in: notification operation filter */
        HA_SRVFIRST = 403,
        CHNF_CHANGELAG = 404,      /* txn lag between notifications */
        HA_SRVNEXT = 404,
        CHDES_DBNAME = 405,                     /* source database */
        TAF_ENABLED = 405,
        CHDES_NFYTYPE = 406,            /* notification type flags */
        NFY_FLAGS = 406,
        CHDES_XID = 407,     /* XID  of the transaction */
        MSG_DELIVERY_MODE = 407,            /* msg delivery mode */
        CHDES_TABLE_CHANGES = 408,/* array of table chg descriptors*/

        CHDES_TABLE_NAME = 409,    /* table name */
        CHDES_TABLE_OPFLAGS = 410,    /* table operation flags */
        CHDES_TABLE_ROW_CHANGES = 411,   /* array of changed rows   */
        CHDES_ROW_ROWID = 412,   /* rowid of changed row    */
        CHDES_ROW_OPFLAGS = 413,   /* row operation flags     */

        CHNF_REGHANDLE = 414,   /* IN: subscription handle  */
        Reserved_21 = 415,                    /* reserved */
        NETWORK_FILE_DESC = 415,   /* network file descriptor */

        PROXY_CLIENT = 416,/* client nam 4 single sess proxy */
        DB_CHARSET_ID = 416,         /* database charset ID */

        TABLE_ENC = 417,/* does table have any encrypt columns */
        DB_NCHARSET_ID = 417,              /* database ncharset ID */
        TABLE_ENC_ALG = 418,         /* Table encryption Algorithm */
        Reserved_25 = 418,                          /* reserved */
        TABLE_ENC_ALG_ID = 419, /* Internal Id of encryption Algorithm*/
        STMTCACHE_CBKCTX = 420,             /* opaque context on stmt */
        STMTCACHE_CBK = 421,          /* callback fn for stmtcache */
        CQDES_OPERATION = 422,
        Reserved_26 = 422,
        XMLTYPE_BINARY_XML = 422,       /* XML type stored as binary? */
        CQDES_TABLE_CHANGES = 423,
        FLOW_CONTROL_TIMEOUT = 423,       /* AQ: flow control timeout */
        CQDES_QUERYID = 424,
        DRIVER_NAME = 424,                    /* Driver Name */
        ENV_NLS_LANGUAGE = 424,
        CHDES_QUERIES = 425,              /* Top level change desc
        array of queries */
        CONNECTION_CLASS = 425,
        Reserved_27 = 425,                        /* reserved */
        ENV_NLS_TERRITORY = 425,
        PURITY = 426,
        Reserved_28 = 426,                       /* reserved */
        Reserved_29 = 427,                        /* reserved */
        Reserved_30 = 428,                        /* reserved */
        Reserved_31 = 429,                        /* reserved */
        Reserved_32 = 430,                        /* reserved */

        /* ----------- Reserve internal attributes for workload replay  ------------ */
        Reserved_33 = 433,
        Reserved_34 = 434,

        /* -------- Attributes for Network Session Time Out--------------------------*/
        SEND_TIMEOUT = 435,           /* NS send timeout */
        RECEIVE_TIMEOUT = 436,        /* NS receive timeout */

        Reserved_35 = 437,

        /*--------- Attributes related to LOB prefetch------------------------------ */
        DEFAULT_LOBPREFETCH_SIZE = 438,   /* default prefetch size */
        LOBPREFETCH_SIZE = 439,           /* prefetch size */
        LOBPREFETCH_LENGTH = 440, /* prefetch length & chunk */

        /*--------- Attributes related to LOB Deduplicate Regions ------------------ */
        LOB_REGION_PRIMARY = 442,         /* Primary LOB Locator */
        LOB_REGION_PRIMOFF = 443,     /* Offset into Primary LOB */
        Reserved_36 = 444,
        LOB_REGION_OFFSET = 445,               /* Region Offset */
        LOB_REGION_LENGTH = 446,   /* Region Length Bytes/Chars */
        LOB_REGION_MIME = 447,            /* Region mime type */

        /*--------------------Attribute to fetch ROWID ------------------------------*/
        FETCH_ROWID = 448,

        /* server attribute */
        Reserved_37 = 449,

        /*-------------------Attributes for OCI column security-----------------------*/
        NO_COLUMN_AUTH_WARNING = 450,
        XDS_POLICY_STATUS = 451,

        /* --------------- ip address attribute in environment handle -------------- */
        SUBSCR_IPADDR = 452,       /* ip address to listen on  */

        Reserved_40 = 453,
        Reserved_41 = 454,
        Reserved_42 = 455,
        Reserved_43 = 456,

        /* statement attribute */
        UB8_ROW_COUNT = 457,         /* ub8 value of row count */

        /* ------------- round trip callback attributes in the process  handle ----- */
        Reserved_458 = 458,                       /* reserved */
        Reserved_459 = 459,                       /* reserved */

        SPOOL_AUTH = 460,  /* Auth handle on pool handle */
        SHOW_INVISIBLE_COLUMNS = 460,  /* invisible columns support */
        INVISIBLE_COL = 461,  /* invisible columns support */

        /* support at most once transaction semantics */
        LTXID = 462,     /* logical transaction id */

        LAST_LOGON_TIME_UTC = 463, /* Last Successful Logon Time */
        IMPLICIT_RESULT_COUNT = 463,

        Reserved_464 = 464,
        Reserved_465 = 465,
        TRANSACTIONAL_TAF = 466,
        Reserved_467 = 467,

        /* SQL translation profile session attribute */
        SQL_TRANSLATION_PROFILE = 468,

        /* Per Iteration array DML rowcount attribute */
        DML_ROW_COUNT_ARRAY = 469,
        Reserved_470 = 470,

        /* session handle attribute */
        MAX_OPEN_CURSORS = 471,

        /* Can application failover and recover from this error?
        * e.g. ORA-03113 is recoverable while ORA-942 (table or view does not exist)
        * is not.
        */
        ERROR_IS_RECOVERABLE = 472,

        /* ONS specific private attribute  */
        Reserved_473 = 473,

        /* Attribute to check if ILM Write Access Tracking is enabled or not */
        ILM_TRACK_WRITE = 474,

        /* Notification subscription failure callback and context */
        SUBSCR_FAILURE_CBK = 477,
        SUBSCR_FAILURE_CTX = 478,

        /* AQ JMS properties attributes */
        AQJMS_HEADER_PROP = 479,
        AQJMS_USER_PROP = 480,
        AQJMS_PROPERTIES = 481,
        AQJMS_MSG_TYPE = 482,

        /* A SQL translation profile with FOREIGN_SQL_SYNTAX attribute is set in the
        * database session.
        */
        TRANS_PROFILE_FOREIGN = 483,

        /* is a transaction active on the session? */
        TRANSACTION_IN_PROGRESS = 484,

        /* add attribute for DBOP: DataBase OPeration */
        DBOP = 485,

        /* FAN-HA private attribute */
        Reserved_486 = 486,

        /* reserved */
        Reserved_487 = 487,

        Reserved_488 = 488,

        VARTYPE_MAXLEN_COMPAT = 489,

        /* Max Lifetime for session */
        SPOOL_MAX_LIFETIME_SESSION = 490,

        Reserved_491 = 491,

        Reserved_492 = 492,

        AUTOTUNING_ENABLED = Reserved_492,
        /* Bit Mask indicating which feature is being auto tuned */
#define OCI_AUTOTUNED_STMT_CACHE    0x00000001
        /* OCI statement caching feature is being auto tuned */

        Reserved_493 = 493,                   /* reserved */

        ITERS_PROCESSED = 494,

        BREAK_ON_NET_TIMEOUT = 495,           /* Break on timeout */

        SHARDING_KEY = 496,
        /* Sharding Key (OCIShardingKey *) attribute of OCIAuth/OCISvcCtx */
        SUPER_SHARDING_KEY = 497,
        /* Super Sharding Key (OCIShardingKey *) attribute of OCIAuth/OCISvcCtx */
        SHARDING_KEY_B64 = 498,
        /* Base64 Sharding Key: read only attribute of OCIShardingKey */
        COLLATION_ID = 499,               /* Collation ID */

        MAX_IDENTIFIER_LEN = 500,      /* max identifier length */

        FIXUP_CALLBACK = 501,
        /* session state fixup callback */

        VIRTUAL_COL = 502,

        Reserved_503 = 503,                   /* reserved */

        SQL_ID = 504,        /* SQL ID in text form */

        SHARD_HAS_WRITABLECHUNK = 505,

        SPOOL_WAIT_TIMEOUT = 506,

        Reserved_507 = 507,

        FO_TYPE = 508,             /* see OCI_FO_xxx */

        /* HCS Hierarchy and Analytic View Column Attributes */
        OLAP_ROLE = 509,  /* hier / analytic view role */
        DIMENSION_NAME = 510,     /* analytic view dim name */
        HIERARCHY_NAME = 511,    /* analytic view hier name */

        Reserved_512 = 512,                   /* reserved */
        Reserved_513 = 513,                   /* reserved */

        /*------ Attributes for DirPathAPI default support 12.2 ---------------------*/
        DIRPATH_DEFAULTS = 513,    /* how to handle defaults */
        /* Evaluate once, unless a sequence is involved, then evaluate every row.
        * Error if unsupported default value seen. This is the default. */
#define OCI_DIRPATH_DEFAULTS_DEFAULT                                 0
                        /* Evaluate once, at the start of the load. Error if unsupported default
                         * value seen. */
#define OCI_DIRPATH_DEFAULTS_EVALUATE_ONCE                           1
                         /* Evaluate every row. Error if unsupported default value seen */
#define OCI_DIRPATH_DEFAULTS_EVALUATE_EVERY_ROW                      2
/* Ignore all defaults (load NULLs) */
#define OCI_DIRPATH_DEFAULTS_IGNORE                                  3
/* Ignore unsuppored defaults (load NULLS) , evaluate supported once */
#define OCI_DIRPATH_DEFAULTS_IGNORE_UNSUPPORTED_EVALUATE_ONCE        4
/* Ignore unsuppored defaults (load NULLS), evaluate supported every row */
#define OCI_DIRPATH_DEFAULTS_IGNORE_UNSUPPORTED_EVALUATE_EVERY_ROW   5

        DIRPATH_DEF_EXP_CACHE_SIZE = 514,   /* default expr cache size */

        Reserved_515 = 515,
        Reserved_516 = 516,

        /*------ Attributes for client to server charset conversion ratio -----------*/
        MAX_CHARSET_RATIO = 517,
        MAX_NCHARSET_RATIO = 518,

        Reserved_519 = 519,

        LOB_REMOTE = 520,               /* remote lob ? */
        Reserved_521 = 521,
        Reserved_522 = 522,
        Reserved_523 = 523,
        PDBNAME = 524,                   /* PDB name */

        Reserved_524 = 524,
        Reserved_525 = 525,
        Reserved_526 = 526,
        Reserved_527 = 527,
        Reserved_528 = 528,
        Reserved_529 = 529,
        Reserved_530 = 530,

        CALL_TIMEOUT = 531,
        /*------------------- Not persisteble types ---------------------------------*/
        IS_NOT_PERSISTABLE_TYPE = 532, /* is  not persistable type   */

        Reserved_533 = 533,                   /* reserved */

        JSON_COL = 534,   /* col holding JSON */

        /*
         * OCI SODA attributes
         */
         /* OCI SODA collection and metadata atributes */
         SODA_COLL_NAME = 535,
         SODA_DESCRIPTOR = 536,
         SODA_SCHEMA = 537,
         SODA_TABLE_NAME = 538,
         SODA_VIEW_NAME = 539,
         SODA_TABLESPACE = 540,
         SODA_STORAGE_INIT_SIZE = 541,
         SODA_STORAGE_INC_PCT = 542,
         SODA_KEY_COL_NAME = 543,
         SODA_KEY_SQL_TYPE = 544,
         SODA_KEY_MAX_LEN = 545,
         SODA_KEY_ASSIGN_METHOD = 546,
         SODA_KEY_SEQ_NAME = 547,
         SODA_CTNT_COL_NAME = 548,
         SODA_CTNT_SQL_TYPE = 549,
         SODA_CTNT_MAX_LEN = 550,
         SODA_CTNT_VALIDATION = 551,
         SODA_CTNT_COMPRESS = 552,
         SODA_CTNT_CACHE = 553,
         SODA_CTNT_ENCRYPT = 554,
         SODA_CTNT_TABLESPACE = 555,
         SODA_VERSION_COL_NAME = 556,
         SODA_VERSION_METHOD = 557,
         SODA_MODTIME_COL_NAME = 558,
         SODA_MODTIME_INDEX = 559,
         SODA_CRTIME_COL_NAME = 560,
         SODA_MTYPE_COL_NAME = 561,
         SODA_READONLY = 562,

         /* OCI SODA Document attributes */
         SODA_KEY = 563,
         SODA_LASTMOD_TIMESTAMP = 564,
         SODA_CREATE_TIMESTAMP = 565,
         SODA_VERSION = 566,
         SODA_CONTENT = 567,
         SODA_JSON_CHARSET_ID = 568,
         SODA_DETECT_JSON_ENC = 569,
         SODA_MEDIA_TYPE = 571,

         /* OCI SODA Content Column's JSON storage format */
         SODA_CTNT_FORMAT = 572,

         /* 573 - 575 are free and be used in future if necessary */

         /* OCI SODA Operation Options attributes */
         SODA_FILTER = 576,
         SODA_SKIP = 577,
         SODA_LIMIT = 578,


         SPOOL_MAX_USE_SESSION = 580,
         Reserved_581 = 581,
         Reserved_582 = 582,
         Reserved_583 = 583,
         Reserved_584 = 584,

         Reserved_586 = 586,
         Reserved_587 = 587,
         Reserved_588 = 588,
         Reserved_589 = 589,

         Reserved_590 = 590,
         LOB_TYPE = 591,
         Reserved_592 = 592,

         /* OCI SODA Output Options attributes */
         SODA_DOC_COUNT = 593,

         /* Other attributes */
         Reserved_595 = 595,
         Reserved_596 = 596,
         Reserved_597 = 597,
         Reserved_598 = 598,
         Reserved_599 = 599,
         Reserved_600 = 600,

         SPOOL_MAX_PER_SHARD = 602,
         Reserved_603 = 603,
         Reserved_604 = 604,
         Reserved_605 = 605,
         Reserved_606 = 606,
         Reserved_607 = 607,
         Reserved_608 = 608,
         Reserved_609 = 609,
         Reserved_611 = 611
    };

    enum class DescribeAttribute : UInt32
    {
        /// <summary>
        /// maximum size of the data
        /// </summary>
        DATA_SIZE = 1,
        /// <summary>
        /// the SQL type of the column/argument
        /// </summary>
        DATA_TYPE = 2,
        /// <summary>
        /// the display size
        /// </summary>
        DISP_SIZE = 3,
        /// <summary>
        /// the name of the column/argument
        /// </summary>
        NAME = 4,
        /// <summary>
        /// precision if number type
        /// </summary>
        PRECISION = 5,
        /// <summary>
        /// scale if number type
        /// </summary>
        SCALE = 6,
        /// <summary>
        /// is it null ?
        /// </summary>
        IS_NULL = 7,
        /// <summary>
        /// name of the named data type or a package name for package private types
        /// </summary>
        TYPE_NAME = 8,

        /// <summary>
        /// the schema name
        /// </summary>
        SCHEMA_NAME = 9,
        /// <summary>
        /// type name if package private type
        /// </summary>
        SUB_NAME = 10,
        /// <summary>
        /// relative position of col/arg in the list of cols/args
        /// </summary>
        POSITION = 11,
        /// <summary>
        /// package name of package type
        /// </summary>
        PACKAGE_NAME = 12,
        /// <summary>
        /// column is referenced (reserved)
        /// </summary>
        REFERENCED = 13
    };

    /// <summary>
    /// Flags coresponding to the column properties
    /// </summary>
    enum class ColumnProperties : UInt64
    {
        /// <summary>
        /// OCI_ATTR_COL_PROPERTY_IS_IDENTITY
        /// </summary>
        IsIdentity = 0x0000000000000001, 
        /// <summary>
        /// OCI_ATTR_COL_PROPERTY_IS_GEN_ALWAYS
        /// </summary>
        IsGenAlways = 0x0000000000000002,
        /// <summary>
        /// OCI_ATTR_COL_PROPERTY_IS_GEN_BY_DEF_ON_NULL
        /// </summary>
        IsGenBYDefOnNull = 0x0000000000000004,
        /// <summary>
        /// OCI_ATTR_COL_PROPERTY_IS_LPART
        /// </summary>
        IsLPart = 0x0000000000000008,
        /// <summary>
        /// OCI_ATTR_COL_PROPERTY_IS_CONID
        /// </summary>
        IsConId = 0x0000000000000010
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( ColumnProperties, UInt64 );


    enum class Piece : Byte
    {
        /// <summary>
        /// there or this is the only piece (OCI_ONE_PIECE)
        /// </summary>
        One = 0,
        /// <summary>
        /// there or this is the only piece (OCI_ONE_PIECE)
        /// </summary>
        Single = 0,
        /// <summary>
        /// the first of many pieces (OCI_FIRST_PIECE)
        /// </summary>
        First = 1,
        /// <summary>
        /// the next of many pieces (OCI_NEXT_PIECE)
        /// </summary>
        Next = 2,
        /// <summary>
        /// the last piece of this column (OCI_LAST_PIECE)
        /// </summary>
        Last = 3
    };

    /// <summary>
    /// The character set form for a LOB.
    /// This value must be consistent with the type of the LOB.
    /// </summary>
    enum class CharacterSetForm : Byte
    {
        Unspecified = 0,
        /// <summary>
        /// Database character set ID for CHAR, VARCHAR2, CLOB w/o a specified set
        /// (SQLCS_IMPLICIT)
        /// </summary>
        Implicit = 1,
        /// <summary>
        /// NCHAR character set ID for NCHAR, NCHAR VARYING, NCLOB 
        /// (SQLCS_NCHAR)
        /// </summary>
        NChar = 2,
        /// <summary>
        /// for CHAR, etc, with "CHARACTER SET ..." syntax 
        /// (SQLCS_EXPLICIT)
        /// </summary>
        Explicit = 3,
        /// <summary>
        /// for PL/SQL "flexible" parameters 
        /// (SQLCS_FLEXIBLE)
        /// </summary>
        Flexible = 4,
        /// <summary>
        /// for typecheck of NULL and empty_clob() lits 
        /// (SQLCS_LIT_NULL)
        /// </summary>
        LiteralNull = 5
    };

    /// <summary>
    /// SubscriberNamespace
    /// </summary>
    enum class SubscriberNamespace : UInt32
    {
        Anonymous = 0,
        AQ = 1,
        DbChange = 2
    };

    /// <summary>
    /// SubscriberNotificationGroupingClass
    /// </summary>
    enum class SubscriberNotificationGroupingClass : Byte
    {
        None = 0,
        Time = 1
    };

    /// <summary>
    /// SubscriberNotificationGroupingType
    /// </summary>
    enum class SubscriberNotificationGroupingType : Byte
    {
        Summary = 1,
        Last = 2
    };

    /// <summary>
    /// SubscriberQOSFlags
    /// </summary>
    enum class SubscriberQOSFlags : UInt32
    {
        Reliable = 0x01,
        Payload = 0x02,
        Replicate = 0x04,
        Secure = 0x08,
        PurgeOnFirstNotification = 0x10,
        MultiInstanceCallback = 0x20,
        HAReg = 0x80,
        NonDurable = 0x100,
        AsyncronousDequeue = 0x200,
        AutoAck = 0x400,
        TxAck = 0x800
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( SubscriberQOSFlags, UInt32 );


    /// <summary>
    /// SubscriberContinousQueryQOSFlags
    /// </summary>
    enum class SubscriberContinousQueryQOSFlags : UInt32
    {
        Query = 0x01,
        BestEffort = 0x02,
        ClientQueryCaching = 0x04
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( SubscriberContinousQueryQOSFlags, UInt32 );

    /// <summary>
    /// SubscriberRecipientFormat
    /// </summary>
    enum class SubscriberRecipientFormat : UInt32
    {
        Default = 0,
        XML = 1
    };


    /// <summary>
    /// SubscriberRecipientProtocol
    /// </summary>
    enum class SubscriberRecipientProtocol : UInt32
    {
        Default = 0,
        OCI = 0,
        Mail = 1,
        Server = 2,
        Http = 3
    };

    enum class ObjectReleaseMethod : UInt16
    {
        None = 0,
        ObjectUnpin = 0x0100,
        ObjectFree = 0x0200,
        ObjectFreeForce = 0x0201,
        ObjectFreeNoNull = 0x0202,
        ObjectFreeHeader = 0x0204,
        ObjectFreeMask = 0x00FF
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( ObjectReleaseMethod, UInt16 );



    enum class NumberToIntFlags : UInt32
    {
        /// <summary>
        /// (OCI_NUMBER_UNSIGNED)
        /// </summary>
        Unsigned = 0,
        /// <summary>
        /// OCI_NUMBER_SIGNED
        /// </summary>
        Signed = 2
    };

}


#endif
