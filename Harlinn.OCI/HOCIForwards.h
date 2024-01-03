#pragma once
#ifndef __HOCIFORWARDS_H__
#define __HOCIFORWARDS_H__
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

#include <HODef.h>
#include <HOCIConstants.h>

#pragma pack(push,8)


using OCIColl = struct OCIColl;
using OCIArray = OCIColl;
using OCITable = OCIColl;
using OCIIter = struct OCIIter;
using OCIRaw = struct OCIRaw;
using OCIRef = struct OCIRef;
using OCIString = struct OCIString;
using OCIDate = struct OCIDate;
using OCIType = struct OCIType;
using OCIEnv = struct OCIEnv;
using OCIError = struct OCIError;
using OCISvcCtx = struct OCISvcCtx;
using OCIStmt = struct OCIStmt;
using OCIBind = struct OCIBind;
using OCIDefine = struct OCIDefine;
using OCIDescribe = struct OCIDescribe;
using OCIServer = struct OCIServer;
using OCISession = struct OCISession;
using OCIComplexObject = struct OCIComplexObject;
using OCITrans = struct OCITrans;
using OCISecurity = struct OCISecurity;
using OCISubscription = struct OCISubscription;
using OCICPool = struct OCICPool;
using OCISPool = struct OCISPool;
using OCIAuthInfo = struct OCIAuthInfo;
using OCIAdmin = struct OCIAdmin;
using OCIEvent = struct OCIEvent;
using OCISnapshot = struct OCISnapshot;
using OCIResult = struct OCIResult;
using OCILobLocator = struct OCILobLocator;
using OCILobRegion = struct OCILobRegion;
using OCIParam = struct OCIParam;
using OCIComplexObjectComp = struct OCIComplexObjectComp;
using OCIRowid = struct OCIRowid;
using OCIDateTime = struct OCIDateTime;
using OCIInterval = struct OCIInterval;
using OCINumber = struct OCINumber;
using OCIUcb = struct OCIUcb;
using OCIServerDNs = struct OCIServerDNs;
using OCIShardingKey = struct OCIShardingKey;
using OCIShardInst = struct OCIShardInst;
using OCIAQEnqOptions = struct OCIAQEnqOptions;
using OCIAQDeqOptions = struct OCIAQDeqOptions;
using OCIAQMsgProperties = struct OCIAQMsgProperties;
using OCIAQAgent = struct OCIAQAgent;
using OCIAQNfyDescriptor = struct OCIAQNfyDescriptor;
using OCIAQSignature = struct OCIAQSignature;
using OCIAQListenOpts = struct OCIAQListenOpts;
using OCIAQLisMsgProps = struct OCIAQLisMsgProps;
using OCIAQJmsgProperties = struct OCIAQJmsgProperties;
using OCIClobLocator = struct OCILobLocator;
using OCIBlobLocator = struct OCILobLocator;
using OCIBFileLocator = struct OCILobLocator;
using OCISodaColl = struct OCISodaColl;
using OCISodaDoc = struct OCISodaDoc;
using OCISodaDocCursor = struct OCISodaDocCursor;
using OCISodaOperationOptions = struct OCISodaOperationOptions;
using OCISodaOutputOptions = struct OCISodaOutputOptions;
using OCISodaMetadata = struct OCISodaMetadata;
using OCISodaCollCursor = struct OCISodaCollCursor;

using CallbackLobRead = Harlinn::OCI::Int32( * )( void* context, const void* bufp, Harlinn::OCI::UInt32 len, Harlinn::OCI::Byte piece );
using CallbackLobWrite = Harlinn::OCI::Int32( * )( void* context, void* bufp, Harlinn::OCI::UInt32* lenp, Harlinn::OCI::Byte* piece );
using CallbackLobGetDeduplicateRegions = Harlinn::OCI::Int32( * )( void* context, OCILobRegion* regions, Harlinn::OCI::UInt32 count, Harlinn::OCI::Byte piece, OCILobRegion** changed_reg, Harlinn::OCI::UInt32* changed_count );

using CallbackLobRead2 = Harlinn::OCI::Int32( * )( void* context, const void* bufp, Harlinn::OCI::UInt64 len, Harlinn::OCI::Piece piece, void** changed_bufpp, Harlinn::OCI::UInt64* changed_lenp );
using CallbackLobWrite2 = Harlinn::OCI::Int32( * )( void* context, void* bufp, Harlinn::OCI::UInt64* lenp, Harlinn::OCI::Piece* piece, void** changed_bufpp, Harlinn::OCI::UInt64* changed_lenp );


namespace Harlinn::OCI
{
    class HandleBase;
    class ErrorHandle;
    class Environment;
    class Server;
    class Session;
    class ServiceContext;
    class TransactionHandle;
    class Describe;
    class Subscription;
    class Statement;
    class BindBase;
    class Bind;
    class ArrayBind;
    class Define;
    class ArrayDefine;

    class CStringBind;
    class CStringArrayBind;
    class CStringDefine;
    class CStringArrayDefine;

    class GuidBind;
    class GuidArrayBind;
    class GuidDefine;
    class GuidArrayDefine;

    class DataReader;
    class Descriptor;
    class ParameterDescriptor;
    class TableDescriptor;
    class ViewDescriptor;
    class ColumnDescriptor;
    class ProcedureDescriptor;
    class FunctionDescriptor;
    class PackageDescriptor;
    class TypeDescriptor;
    class SynonymDescriptor;
    class SequenceDescriptor;
    class ArgumentDescriptor;
    class ListDescriptor;
    class TypeAttributeDescriptor;
    class CollectionDescriptor;
    class MethodDescriptor;
    class MethodArgumentDescriptor;
    class MethodResultDescriptor;
    class SchemaDescriptor;
    class DatabaseDescriptor;
    class RuleDescriptor;
    class RuleSetDescriptor;
    class EvaluationContextDescriptor;
    class TableAliasDescriptor;
    class VariableTypeDescriptor;
    class NameValuePairDescriptor;
    class Ref;
    class Object;
    class Type;
    class Collection;
    class Table;
    class Iterator;

    template < typename BT, OCI::OraType externalType, typename IT = BT >
    class SimpleBind;
    template < typename BT, OCI::OraType externalType, typename IT = BT >
    class SimpleArrayBind;

    /// <summary>
    /// BooleanBind
    /// </summary>
    using BooleanBind = SimpleBind < bool, OCI::OraType::INT, Byte >;
    /// <summary>
    /// BooleanArrayBind
    /// </summary>
    using BooleanArrayBind = SimpleArrayBind < SByte, OCI::OraType::INT, Byte >;

    /// <summary>
    /// SByteBind
    /// </summary>
    using SByteBind = SimpleBind < SByte, OCI::OraType::INT >;
    /// <summary>
    /// SByteArrayBind
    /// </summary>
    using SByteArrayBind = SimpleArrayBind < SByte, OCI::OraType::INT >;
    /// <summary>
    /// ByteBind
    /// </summary>
    using ByteBind = SimpleBind < Byte, OCI::OraType::UIN >;
    /// <summary>
    /// ByteArrayBind
    /// </summary>
    using ByteArrayBind = SimpleArrayBind < Byte, OCI::OraType::UIN >;
    /// <summary>
    /// Int16Bind
    /// </summary>
    using Int16Bind = SimpleBind < Int16, OCI::OraType::INT >;
    /// <summary>
    /// Int16ArrayBind
    /// </summary>
    using Int16ArrayBind = SimpleArrayBind < Int16, OCI::OraType::INT >;

    /// <summary>
    /// UInt16Bind
    /// </summary>
    using UInt16Bind = SimpleBind < UInt16, OCI::OraType::UIN >;

    /// <summary>
    /// UInt16ArrayBind
    /// </summary>
    using UInt16ArrayBind = SimpleArrayBind < UInt16, OCI::OraType::UIN >;

    /// <summary>
    /// Int32Bind
    /// </summary>
    using Int32Bind = SimpleBind < Int32, OCI::OraType::INT >;

    /// <summary>
    /// Int32ArrayBind
    /// </summary>
    using Int32ArrayBind = SimpleArrayBind < Int32, OCI::OraType::INT >;
    /// <summary>
    /// UInt32Bind
    /// </summary>
    using UInt32Bind = SimpleBind < UInt32, OCI::OraType::UIN >;
    /// <summary>
    /// UInt32ArrayBind
    /// </summary>
    using UInt32ArrayBind = SimpleArrayBind < UInt32, OCI::OraType::UIN >;
    /// <summary>
    /// Int64Bind
    /// </summary>
    using Int64Bind = SimpleBind < Int64, OCI::OraType::INT >;
    /// <summary>
    /// Int64ArrayBind
    /// </summary>
    using Int64ArrayBind = SimpleArrayBind < Int64, OCI::OraType::INT >;
    /// <summary>
    /// UInt64Bind
    /// </summary>
    using UInt64Bind = SimpleBind < UInt64, OCI::OraType::UIN >;
    /// <summary>
    /// UInt64ArrayBind
    /// </summary>
    using UInt64ArrayBind = SimpleArrayBind < UInt64, OCI::OraType::UIN >;
    /// <summary>
    /// SingleBind
    /// </summary>
    using SingleBind = SimpleBind < float, OCI::OraType::BFLOAT >;
    /// <summary>
    /// SingleArrayBind
    /// </summary>
    using SingleArrayBind = SimpleArrayBind < float, OCI::OraType::BFLOAT >;
    /// <summary>
    /// DoubleBind
    /// </summary>
    using DoubleBind = SimpleBind < double, OCI::OraType::BDOUBLE >;
    /// <summary>
    /// DoubleArrayBind
    /// </summary>
    using DoubleArrayBind = SimpleArrayBind < double, OCI::OraType::BDOUBLE >;

    template<OCI::HandleType handleType, OCI::OraType externalType>
    class TimestampBaseBind;

    template<OCI::HandleType handleType, OCI::OraType externalType>
    class TimestampBaseArrayBind;

    /// <summary>
    /// TimestampBind
    /// </summary>
    using TimestampBind = TimestampBaseBind<OCI::HandleType::TIMESTAMP, OCI::OraType::TIMESTAMP>;
    /// <summary>
    /// TimestampTZBind
    /// </summary>
    using TimestampTZBind = TimestampBaseBind<OCI::HandleType::TIMESTAMP_TZ, OCI::OraType::TIMESTAMP_TZ>;
    /// <summary>
    /// TimestampLTZBind
    /// </summary>
    using TimestampLTZBind = TimestampBaseBind<OCI::HandleType::TIMESTAMP_LTZ, OCI::OraType::TIMESTAMP_LTZ>;

    /// <summary>
    /// TimestampArrayBind
    /// </summary>
    using TimestampArrayBind = TimestampBaseArrayBind<OCI::HandleType::TIMESTAMP, OCI::OraType::TIMESTAMP>;
    /// <summary>
    /// TimestampTZArrayBind
    /// </summary>
    using TimestampTZArrayBind = TimestampBaseArrayBind<OCI::HandleType::TIMESTAMP_TZ, OCI::OraType::TIMESTAMP_TZ>;
    /// <summary>
    /// TimestampLTZArrayBind
    /// </summary>
    using TimestampLTZArrayBind = TimestampBaseArrayBind<OCI::HandleType::TIMESTAMP_LTZ, OCI::OraType::TIMESTAMP_LTZ>;



    template < typename BT, OCI::OraType externalType >
    class SimpleDefine;

    template < typename BT, OCI::OraType externalType >
    class SimpleArrayDefine;

    /// <summary>
    /// BooleanDefine
    /// </summary>
    using BooleanDefine = SimpleDefine < SByte, OCI::OraType::INT >;
    /// <summary>
    /// BooleanArrayDefine
    /// </summary>
    using BooleanArrayDefine = SimpleArrayDefine < SByte, OCI::OraType::INT >;

    /// <summary>
    /// SByteDefine
    /// </summary>
    using SByteDefine = SimpleDefine < SByte, OCI::OraType::INT >;
    /// <summary>
    /// SByteArrayDefine
    /// </summary>
    using SByteArrayDefine = SimpleArrayDefine < SByte, OCI::OraType::INT >;
    /// <summary>
    /// ByteDefine
    /// </summary>
    using ByteDefine = SimpleDefine < Byte, OCI::OraType::UIN >;
    /// <summary>
    /// ByteArrayDefine
    /// </summary>
    using ByteArrayDefine = SimpleArrayDefine < Byte, OCI::OraType::UIN >;

    /// <summary>
    /// Int16Define
    /// </summary>
    using Int16Define = SimpleDefine < Int16, OCI::OraType::INT >;

    /// <summary>
    /// Int16ArrayDefine
    /// </summary>
    using Int16ArrayDefine = SimpleArrayDefine < Int16, OCI::OraType::INT >;

    /// <summary>
    /// UInt16Define
    /// </summary>
    using UInt16Define = SimpleDefine < UInt16, OCI::OraType::UIN >;

    /// <summary>
    /// UInt16ArrayDefine
    /// </summary>
    using UInt16ArrayDefine = SimpleArrayDefine < UInt16, OCI::OraType::UIN >;

    /// <summary>
    /// Int32Define
    /// </summary>
    using Int32Define = SimpleDefine < Int32, OCI::OraType::INT >;

    /// <summary>
    /// Int32ArrayDefine
    /// </summary>
    using Int32ArrayDefine = SimpleArrayDefine < Int32, OCI::OraType::INT >;
    /// <summary>
    /// UInt32Define
    /// </summary>
    using UInt32Define = SimpleDefine < UInt32, OCI::OraType::UIN >;

    /// <summary>
    /// UInt32ArrayDefine
    /// </summary>
    using UInt32ArrayDefine = SimpleArrayDefine < UInt32, OCI::OraType::UIN >;
    /// <summary>
    /// Int64Define
    /// </summary>
    using Int64Define = SimpleDefine < Int64, OCI::OraType::INT >;

    /// <summary>
    /// Int64ArrayDefine
    /// </summary>
    using Int64ArrayDefine = SimpleArrayDefine < Int64, OCI::OraType::INT >;
    /// <summary>
    /// UInt64Define
    /// </summary>
    using UInt64Define = SimpleDefine < UInt64, OCI::OraType::UIN >;

    /// <summary>
    /// UInt64ArrayDefine
    /// </summary>
    using UInt64ArrayDefine = SimpleArrayDefine < UInt64, OCI::OraType::UIN >;
    /// <summary>
    /// SingleDefine
    /// </summary>
    using SingleDefine = SimpleDefine < Single, OCI::OraType::BFLOAT >;


    /// <summary>
    /// SingleArrayDefine
    /// </summary>
    using SingleArrayDefine = SimpleArrayDefine < Single, OCI::OraType::BFLOAT >;
    /// <summary>
    /// DoubleDefine
    /// </summary>
    using DoubleDefine = SimpleDefine < Double, OCI::OraType::BDOUBLE >;
    /// <summary>
    /// DoubleArrayDefine
    /// </summary>
    using DoubleArrayDefine = SimpleArrayDefine < Double, OCI::OraType::BDOUBLE >;


    template<OCI::HandleType descriptorType, OCI::OraType oracleType>
    class TimestampBaseDefine;

    template<OCI::HandleType descriptorType, OCI::OraType oracleType>
    class TimestampBaseArrayDefine;

    /// <summary>
    /// TimeStampDefine
    /// </summary>
    using TimestampDefine = TimestampBaseDefine<OCI::HandleType::TIMESTAMP, OraType::TIMESTAMP>;
    /// <summary>
    /// TimeStampTZDefine
    /// </summary>
    using TimestampTZDefine = TimestampBaseDefine<OCI::HandleType::TIMESTAMP_TZ, OraType::TIMESTAMP_TZ>;
    /// <summary>
    /// TimestampLTZDefine
    /// </summary>
    using TimestampLTZDefine = TimestampBaseDefine<OCI::HandleType::TIMESTAMP_LTZ, OraType::TIMESTAMP_LTZ>;

    /// <summary>
    /// TimestampArrayDefine
    /// </summary>
    using TimestampArrayDefine = TimestampBaseArrayDefine<OCI::HandleType::TIMESTAMP, OraType::TIMESTAMP>;
    /// <summary>
    /// TimestampTZArrayDefine
    /// </summary>
    using TimestampTZArrayDefine = TimestampBaseArrayDefine<OCI::HandleType::TIMESTAMP_TZ, OraType::TIMESTAMP_TZ>;
    /// <summary>
    /// TimestampLTZArrayDefine
    /// </summary>
    using TimestampLTZArrayDefine = TimestampBaseArrayDefine<OCI::HandleType::TIMESTAMP_LTZ, OraType::TIMESTAMP_LTZ>;


    template<OCI::HandleType descriptorType, OCI::OraType oracleType>
    class IntervalBaseDefine;

    template<OCI::HandleType descriptorType, OCI::OraType oracleType>
    class IntervalBaseArrayDefine;


    /// <summary>
    /// IntervalDSDefine
    /// </summary>
    using IntervalDSDefine = IntervalBaseDefine<OCI::HandleType::INTERVAL_DS, OraType::INTERVAL_DS>;
    /// <summary>
    /// IntervalYMDefine
    /// </summary>
    using IntervalYMDefine = IntervalBaseDefine<OCI::HandleType::INTERVAL_YM, OraType::INTERVAL_YM>;

    /// <summary>
    /// IntervalDSArrayDefine
    /// </summary>
    using IntervalDSArrayDefine = IntervalBaseArrayDefine<OCI::HandleType::INTERVAL_DS, OraType::INTERVAL_DS>;
    /// <summary>
    /// IntervalYMDefine
    /// </summary>
    using IntervalYMArrayDefine = IntervalBaseArrayDefine<OCI::HandleType::INTERVAL_YM, OraType::INTERVAL_YM>;

    namespace Metadata
    {
        class MetadataObject;
        class ArgumentOrResult;
        class Argument;
        class Result;
        class ProcedureOrFunction;
        class Procedure;
        class Function;
        class SchemaObject;
        class Column;
        class TableOrView;
        class Table;
        class View;
        class TypeObject;
        class TypeAttribute;
        class Type;
        class Package;
        class Synonym;
        class Sequence;
        class Schema;
        class Database;
    }

}

#endif