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

using Microsoft.Data.SqlClient;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Logging.Abstractions;
using Microsoft.SqlServer.Types;
using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlTypes;
using System.Diagnostics.CodeAnalysis;
using System.Runtime.CompilerServices;

namespace Harlinn.Common.Core.Net.Data.SqlClient
{

    public class DataReaderWrapper : IDataReader
    {
        private ILogger _logger;
        private SqlDataReader _reader;
        private bool _isDisposed;
        private bool _ownsReader;

        public DataReaderWrapper([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        {
            _logger = loggerFactory.CreateLogger<DataReaderWrapper>();
            _reader = sqlDataReader;
            _ownsReader = ownsReader;
        }

        public DataReaderWrapper([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        {
            _logger = NullLogger<DataReaderWrapper>.Instance;
            _reader = sqlDataReader;
            _ownsReader = ownsReader;
        }

        public DataReaderWrapper([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        {
            _logger = logger;
            _reader = sqlDataReader;
            _ownsReader = ownsReader;
        }


        #region IDisposable Members
        public void Dispose()
        {
            try
            {
                if (!_isDisposed)
                {
                    _isDisposed = true;

                    OnDispose();
                }
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }
        protected virtual void OnDispose()
        {
            try
            {
                DisposeDataReader();
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }
        protected virtual void DisposeDataReader()
        {
            try
            {
                if ((_reader != null) && (OwnsReader))
                {
                    SqlDataReader sqlDataReader = _reader;
                    _reader = null;
                    try
                    {
                        if (sqlDataReader.IsClosed == false)
                        {
                            sqlDataReader.Close();
                        }
                    }
                    finally
                    {
                        sqlDataReader.Dispose();
                    }
                }
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }
        #endregion


        protected void LogException([DisallowNull] Exception exc, [CallerMemberName] string methodName = "")
        {
            string exceptionMessageText = exc.Message;
            string messageText = string.Format("Exception in {0} - {1}", methodName, exceptionMessageText);
            
            _logger.LogError( exc,messageText );
#if DEBUG
            if (System.Diagnostics.Debugger.IsAttached)
            {
                System.Diagnostics.Debugger.Log(1, "Exception", messageText);
                System.Diagnostics.Debugger.Break();
            }
#endif
        }
        
        public virtual int GetTypeCode()
        {
            return 0;
        }


        protected bool OwnsReader  { get => _ownsReader; set => _ownsReader = value; }

        protected void SetDataReader([DisallowNull] SqlDataReader reader, bool ownsReader = true)
        {
            _reader = reader;
            _ownsReader = ownsReader;
        }


        #region IDataReader Members

        public void Close()
        {
            try
            {
                _reader.Close();
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        int IDataReader.Depth
        {
            get
            {
                try
                {
                    return _reader.Depth;
                }
                catch (Exception exc)
                {
                    LogException(exc);
                    throw;
                }
            }
        }

        public DataTable GetSchemaTable()
        {
            try
            {
                return _reader.GetSchemaTable();
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public bool IsClosed
        {
            get
            {
                try
                {
                    return _reader.IsClosed;
                }
                catch (Exception exc)
                {
                    LogException(exc);
                    throw;
                }
            }
        }

        public bool NextResult()
        {
            try
            {
                return _reader.NextResult();
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public bool Read()
        {
            try
            {
                return _reader.Read();
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public int RecordsAffected
        {
            get
            {
                try
                {
                    return _reader.RecordsAffected;
                }
                catch (Exception exc)
                {
                    LogException(exc);
                    throw;
                }
            }
        }

        #endregion


        #region IDataRecord Members

        public int FieldCount
        {
            get
            {
                try
                {
                    return _reader.FieldCount;
                }
                catch (Exception exc)
                {
                    LogException(exc);
                    throw;
                }
            }
        }

        public bool GetBoolean(int i)
        {
            try
            {
                return _reader.GetBoolean(i);
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public bool? GetNullableBoolean(int i)
        {
            if (!IsDBNull(i))
            {
                return GetBoolean(i);
            }
            return null;
        }

        public sbyte GetSByte(int i)
        {
            try
            {
                return unchecked((sbyte)_reader.GetByte(i));
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public sbyte? GetNullableSByte(int i)
        {
            if (!IsDBNull(i))
            {
                return GetSByte(i);
            }
            return null;
        }

        public byte GetByte(int i)
        {
            try
            {
                return _reader.GetByte(i);
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }
        public byte? GetNullableByte(int i)
        {
            if (!IsDBNull(i))
            {
                return GetByte(i);
            }
            return null;
        }


        public long GetBytes(int i, long fieldOffset, byte[] buffer, int bufferOffset, int length)
        {
            try
            {
                return _reader.GetBytes(i, fieldOffset, buffer, bufferOffset, length);
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public byte[] GetBytes(int i)
        {
            try
            {
                var sqlBinary = _reader.GetSqlBinary(i);
                if(sqlBinary != null)
                {
                    return sqlBinary.Value;
                }
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
            return Array.Empty<byte>();
        }

        public byte[]? GetNullableBytes(int i)
        {
            if (!IsDBNull(i))
            {
                return GetBytes(i);
            }
            return null;
        }


        public char GetChar(int i)
        {
            try
            {
                return _reader.GetChar(i);
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public char? GetNullableChar(int i)
        {
            if (!IsDBNull(i))
            {
                return GetChar(i);
            }
            return null;
        }


        public long GetChars(int i, long fieldoffset, char[] buffer, int bufferoffset, int length)
        {
            try
            {
                return _reader.GetChars(i, fieldoffset, buffer, bufferoffset, length);
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public short GetInt16(int i)
        {
            try
            {
                return _reader.GetInt16(i);
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public short? GetNullableInt16(int i)
        {
            if (!IsDBNull(i))
            {
                return GetInt16(i);
            }
            return null;
        }

        public ushort GetUInt16(int i)
        {
            try
            {
                return unchecked((ushort)GetInt32(i));
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public ushort? GetNullableUInt16(int i)
        {
            if (!IsDBNull(i))
            {
                return GetUInt16(i);
            }
            return null;
        }


        public int GetInt32(int i)
        {
            try
            {
                return _reader.GetInt32(i);
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public int? GetNullableInt32(int i)
        {
            if (!IsDBNull(i))
            {
                return GetInt32(i);
            }
            return null;
        }

        public uint GetUInt32(int i)
        {
            try
            {
                return (uint)_reader.GetDecimal(i);
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public uint? GetNullableUInt32(int i)
        {
            if (!IsDBNull(i))
            {
                return GetUInt32(i);
            }
            return null;
        }

        public long GetInt64(int i)
        {
            try
            {
                return _reader.GetInt64(i);
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public long? GetNullableInt64(int i)
        {
            if (!IsDBNull(i))
            {
                return GetInt64(i);
            }
            return null;
        }

        public ulong GetUInt64(int i)
        {
            try
            {
                return (ulong)_reader.GetDecimal(i);
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public ulong? GetNullableUInt64(int i)
        {
            if (!IsDBNull(i))
            {
                return GetUInt64(i);
            }
            return null;
        }

        public T GetEnum<T>(int i) where T : struct, System.Enum
        {
            var enumType = typeof(T);
            var enumIntegerType = Enum.GetUnderlyingType(enumType);
            if (enumIntegerType == typeof(int))
            {
                var value = GetInt32( i );
                return (T)Enum.ToObject(typeof(T), value);
            }
            else if (enumIntegerType == typeof(uint))
            {
                var value = GetUInt32(i);
                return (T)Enum.ToObject(typeof(T), value);
            }
            else if (enumIntegerType == typeof(sbyte))
            {
                var value = GetSByte(i);
                return (T)Enum.ToObject(typeof(T), value);
            }
            else if (enumIntegerType == typeof(byte))
            {
                var value = GetByte(i);
                return (T)Enum.ToObject(typeof(T), value);
            }
            else if (enumIntegerType == typeof(short))
            {
                var value = GetInt16(i);
                return (T)Enum.ToObject(typeof(T), value);
            }
            else if (enumIntegerType == typeof(ushort))
            {
                var value = GetUInt16(i);
                return (T)Enum.ToObject(typeof(T), value);
            }
            else if (enumIntegerType == typeof(long))
            {
                var value = GetInt64(i);
                return (T)Enum.ToObject(typeof(T), value);
            }
            else if (enumIntegerType == typeof(ulong))
            {
                var value = GetUInt64(i);
                return (T)Enum.ToObject(typeof(T), value);
            }
            return default;
        }

        public T? GetNullableEnum<T>(int i) where T : struct, System.Enum
        {
            if (!IsDBNull(i))
            {
                return GetEnum<T>(i);
            }
            return null;
        }

        public float GetFloat(int i)
        {
            try
            {
                return _reader.GetFloat(i);
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public float? GetNullableFloat(int i)
        {
            if (!IsDBNull(i))
            {
                return GetFloat(i);
            }
            return null;
        }

        public float GetSingle(int i)
        {
            try
            {
                return _reader.GetFloat(i);
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public float? GetNullableSingle(int i)
        {
            if (!IsDBNull(i))
            {
                return GetSingle(i);
            }
            return null;
        }

        public double GetDouble(int i)
        {
            try
            {
                return _reader.GetDouble(i);
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public double? GetNullableDouble(int i)
        {
            if (!IsDBNull(i))
            {
                return GetDouble(i);
            }
            return null;
        }

        public decimal GetDecimal(int i)
        {
            try
            {
                return _reader.GetDecimal(i);
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }


        public decimal? GetNullableDecimal(int i)
        {
            if (!IsDBNull(i))
            {
                return GetDecimal(i);
            }
            return null;
        }

        public DateTime GetDateTime(int i)
        {
            try
            {
                return _reader.GetDateTime(i);
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public DateTime? GetNullableDateTime(int i)
        {
            if (!IsDBNull(i))
            {
                return GetDateTime(i);
            }
            return null;
        }


        public TimeSpan GetTimeSpan(int i)
        {
            try
            {
                return new TimeSpan(_reader.GetInt64(i));
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public TimeSpan? GetNullableTimeSpan(int i)
        {
            if (!IsDBNull(i))
            {
                return GetTimeSpan(i);
            }
            return null;
        }

        public string GetString(int i)
        {
            try
            {
                return _reader.GetString(i);
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public string? GetNullableString(int i)
        {
            if (!IsDBNull(i))
            {
                return GetString(i);
            }
            return null;
        }

        public Guid GetGuid(int i)
        {
            try
            {
                return _reader.GetGuid(i);
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }


        public Guid? GetNullableGuid(int i)
        {
            if (!IsDBNull(i))
            {
                return GetGuid(i);
            }
            return null;
        }

        public IDataReader GetData(int i)
        {
            try
            {
                return _reader.GetData(i);
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }

        }

        public string GetDataTypeName(int i)
        {
            try
            {
                return _reader.GetDataTypeName(i);
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public Type GetFieldType(int i)
        {
            try
            {
                return _reader.GetFieldType(i);
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public string GetName(int i)
        {
            try
            {
                return _reader.GetName(i);
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }

        }

        public int GetOrdinal(string name)
        {
            try
            {
                return _reader.GetOrdinal(name);
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        




        public object GetValue(int i)
        {
            try
            {
                return _reader.GetValue(i);
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public object? GetNullableValue(int i)
        {
            try
            {
                if (!IsDBNull(i))
                {
                    return _reader.GetValue(i);
                }
                return null;
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public int GetValues(object[] values)
        {
            try
            {
                return _reader.GetValues(values);
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public bool IsDBNull(int i)
        {
            try
            {
                return _reader.IsDBNull(i);
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public object this[string name]
        {
            get
            {
                try
                {
                    return _reader[name];
                }
                catch (Exception exc)
                {
                    LogException(exc);
                    throw;
                }
            }
        }

        public object this[int i]
        {
            get
            {
                try
                {
                    return _reader[i];
                }
                catch (Exception exc)
                {
                    LogException(exc);
                    throw;
                }
            }
        }

        #endregion

        public long GetTimestamp(int i)
        {
            try
            {
                long result = GetInt64( i );
                return result;
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public long? GetNullableTimestamp(int i)
        {
            if (!IsDBNull(i))
            {
                return GetTimestamp(i);
            }
            return null;
        }


        public byte[] GetBinary(int i)
        {
            try
            {
                byte[] result = null;
                if (_reader.IsDBNull(i) == false)
                {
                    result = _reader.GetSqlBinary(i).Value;
                }
                return result;
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public byte[] GetNullableBinary(int i)
        {
            try
            {
                byte[] result = null;
                if (_reader.IsDBNull(i) == false)
                {
                    result = _reader.GetSqlBinary(i).Value;
                }
                return result;
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public SqlHierarchyId GetSqlHierarchyId(int i)
        {
            try
            {
                var result = (SqlHierarchyId)_reader.GetSqlValue(i);
                return result;
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public SqlHierarchyId? GetNullableSqlHierarchyId(int i)
        {
            try
            {
                if (IsDBNull(i))
                {
                    return null;
                }
                var result = (SqlHierarchyId)_reader.GetSqlValue(i);
                return result;
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public SqlGeography GetSqlGeography(int i)
        {
            try
            {
                var result = (SqlGeography)_reader.GetSqlValue(i);
                return result;
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public SqlGeography? GetNullableSqlGeography(int i)
        {
            try
            {
                if (IsDBNull(i))
                {
                    return null;
                }
                var result = (SqlGeography)_reader.GetSqlValue(i);
                return result;
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public SqlGeometry GetSqlGeometry(int i)
        {
            try
            {
                var result = (SqlGeometry)_reader.GetSqlValue(i);
                return result;
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public SqlGeometry? GetNullableSqlGeometry(int i)
        {
            try
            {
                if (IsDBNull(i))
                {
                    return null;
                }
                var result = (SqlGeometry)_reader.GetSqlValue(i);
                return result;
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public SqlXml GetSqlXml(int i)
        {
            try
            {
                var result = _reader.GetSqlXml(i);
                return result;
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }

        public SqlXml? GetNullableSqlXml(int i)
        {
            try
            {
                if (IsDBNull(i))
                {
                    return null;
                }
                var result = _reader.GetSqlXml(i);
                return result;
            }
            catch (Exception exc)
            {
                LogException(exc);
                throw;
            }
        }


    }
}
