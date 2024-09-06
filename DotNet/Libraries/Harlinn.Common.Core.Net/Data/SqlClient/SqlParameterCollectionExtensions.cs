﻿using System;
using System.Collections.Generic;
using System.Data;
using System.Diagnostics.CodeAnalysis;
using Microsoft.Data.SqlClient;

namespace Harlinn.Common.Core.Net.Data.SqlClient
{
    /// <summary>
    /// Useful extensions to the SqlParameterCollection class.
    /// </summary>
    public static class SqlParameterCollectionExtensions
    {
        public static SqlParameter AddBoolean([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, bool? value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.Bit);
            parameter.Value = (value is bool v) ? v : DBNull.Value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }
        public static SqlParameter AddBoolean([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, bool value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.Bit);
            parameter.Value = value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }


        public static SqlParameter AddSByte([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, sbyte? value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.TinyInt);
            parameter.Value = (value is sbyte v) ? unchecked((byte)v) : DBNull.Value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }
        public static SqlParameter AddSByte([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, sbyte value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.TinyInt);
            parameter.Value = unchecked((byte)value);
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }


        public static SqlParameter AddByte([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, byte? value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.TinyInt);
            parameter.Value = (value is byte v) ? v : DBNull.Value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }
        public static SqlParameter AddByte([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, byte value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.TinyInt);
            parameter.Value = value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }

        public static SqlParameter AddInt16([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, short? value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.SmallInt);
            parameter.Value = (value is short v) ? v : DBNull.Value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }
        public static SqlParameter AddInt16([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, short value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.SmallInt);
            parameter.Value = value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }

        public static SqlParameter AddUInt16([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, ushort? value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.SmallInt);
            parameter.Value = (value is ushort v) ? unchecked((short)v) : DBNull.Value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }
        public static SqlParameter AddUInt16([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, ushort value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.SmallInt);
            parameter.Value = unchecked((short)value);
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }


        public static SqlParameter AddInt32([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, int? value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.Int);
            parameter.Value = (value is int v) ? v : DBNull.Value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }
        public static SqlParameter AddInt32([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, int value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.Int);
            parameter.Value = value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }

        public static SqlParameter AddUInt32([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, uint? value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.Int);
            parameter.Value = (value is uint v) ? unchecked((int)v) : DBNull.Value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }
        public static SqlParameter AddUInt32([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, uint value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.Int);
            parameter.Value = unchecked((int)value);
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }

        public static SqlParameter AddInt64([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, long? value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.BigInt);
            parameter.Value = (value is long v) ? v : DBNull.Value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }
        public static SqlParameter AddInt64([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, long value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.BigInt);
            parameter.Value = value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }


        public static SqlParameter AddUInt64([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, ulong? value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.BigInt);
            parameter.Value = (value is ulong v) ? unchecked((long)v) : DBNull.Value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }
        public static SqlParameter AddUInt64([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, ulong value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.BigInt);
            parameter.Value = unchecked(value);
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }


        public static SqlParameter AddSingle([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, float? value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.Real);
            parameter.Value = (value is float v) ? v : DBNull.Value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }
        public static SqlParameter AddSingle([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, float value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.Real);
            parameter.Value = value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }


        public static SqlParameter AddDouble([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, double? value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.Float);
            parameter.Value = (value is double v) ? v : DBNull.Value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }
        public static SqlParameter AddDouble([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, double value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.Float);
            parameter.Value = value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }



        public static SqlParameter AddDateTime([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, DateTime? value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.DateTime2);
            parameter.Value = (value is DateTime v) ? v : DBNull.Value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }
        public static SqlParameter AddDateTime([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, DateTime value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.DateTime2);
            parameter.Value = value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }

        public static SqlParameter AddDateTimeOffset([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, DateTimeOffset? value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.DateTimeOffset);
            parameter.Value = (value is DateTimeOffset v) ? v : DBNull.Value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }
        public static SqlParameter AddDateTimeOffset([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, DateTimeOffset value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.DateTimeOffset);
            parameter.Value = value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }

        public static SqlParameter AddTimeSpan([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, TimeSpan? value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.BigInt);
            parameter.Value = (value is TimeSpan v) ? v : DBNull.Value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }
        public static SqlParameter AddTimeSpan([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, TimeSpan value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.BigInt);
            parameter.Value = value.Ticks;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }

        public static SqlParameter AddGuid([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, Guid? value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.UniqueIdentifier);
            parameter.Value = (value is Guid v) ? v : DBNull.Value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }
        public static SqlParameter AddGuid([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, Guid value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.UniqueIdentifier);
            parameter.Value = value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }

        public static SqlParameter AddReference([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, Guid? value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.UniqueIdentifier);
            parameter.Value = (value is Guid v) ? v : DBNull.Value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }
        public static SqlParameter AddReference([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, Guid value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.UniqueIdentifier);
            parameter.Value = value != Guid.Empty ? (object)value : DBNull.Value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }


        public static SqlParameter AddEnum<T>([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, T? value, ParameterDirection parameterDirection = ParameterDirection.Input) where T : struct, Enum
        {
            var enumType = typeof(T);
            var enumIntegerType = Enum.GetUnderlyingType(enumType);

            SqlDbType sqlDbType = SqlDbType.Int;
            if(enumIntegerType != typeof(int) || enumIntegerType != typeof(uint))
            {
                if (enumIntegerType == typeof(sbyte) || enumIntegerType == typeof(byte))
                {
                    sqlDbType = SqlDbType.TinyInt;
                }
                else if (enumIntegerType == typeof(short) || enumIntegerType == typeof(ushort))
                {
                    sqlDbType = SqlDbType.SmallInt;
                }
                else if (enumIntegerType == typeof(long) || enumIntegerType == typeof(ulong))
                {
                    sqlDbType = SqlDbType.BigInt;
                }
            }

            SqlParameter parameter = new SqlParameter(parameterName, sqlDbType);
            if (value is T v)
            {
                parameter.Value = v;
            }
            else
            {
                parameter.Value = DBNull.Value;
            }
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }

        public static SqlParameter AddEnum<T>([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, T value, ParameterDirection parameterDirection = ParameterDirection.Input) where T : struct, Enum
        {
            var enumType = typeof(T);
            var enumIntegerType = Enum.GetUnderlyingType(enumType);

            SqlDbType sqlDbType = SqlDbType.Int;
            if (enumIntegerType != typeof(int) || enumIntegerType != typeof(uint))
            {
                if (enumIntegerType == typeof(sbyte) || enumIntegerType == typeof(byte))
                {
                    sqlDbType = SqlDbType.TinyInt;
                }
                else if (enumIntegerType == typeof(short) || enumIntegerType == typeof(ushort))
                {
                    sqlDbType = SqlDbType.SmallInt;
                }
                else if (enumIntegerType == typeof(long) || enumIntegerType == typeof(ulong))
                {
                    sqlDbType = SqlDbType.BigInt;
                }
            }
            SqlParameter parameter = new SqlParameter(parameterName, sqlDbType);
            parameter.Value = value;
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }


        public static SqlParameter AddChar([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, string value, int size, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.Char, size);
            if (value != null)
            {
                parameter.Value = value;
            }
            else
            {
                parameter.Value = DBNull.Value;
            }
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }
        public static SqlParameter AddNChar([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, string value, int size, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.NChar, size);
            if (value != null)
            {
                parameter.Value = value;
            }
            else
            {
                parameter.Value = DBNull.Value;
            }
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }
        public static SqlParameter AddVarChar([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, string value, int size, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            var parameterType = size <= 8000 ? SqlDbType.VarChar : SqlDbType.Text;

            SqlParameter parameter = new SqlParameter(parameterName, parameterType, size <= 8000 ? size : -1);
            if (value != null)
            {
                parameter.Value = value;
            }
            else
            {
                parameter.Value = DBNull.Value;
            }
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }
        public static SqlParameter AddNVarChar([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, string value, int size, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            var parameterType = size <= 4000 ? SqlDbType.NVarChar : SqlDbType.NText;

            SqlParameter parameter = new SqlParameter(parameterName, SqlDbType.NVarChar, size <= 4000 ? size : -1);
            if (value != null)
            {
                parameter.Value = value;
            }
            else
            {
                parameter.Value = DBNull.Value;
            }
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }

        public static SqlParameter AddBinary([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, byte[] value, int size, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            var parameterType = size <= 8000 ? SqlDbType.Binary : SqlDbType.VarBinary;

            SqlParameter parameter = new SqlParameter(parameterName, parameterType, size <= 8000 ? size : -1);
            if (value != null)
            {
                parameter.Value = value;
            }
            else
            {
                parameter.Value = DBNull.Value;
            }
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }
        public static SqlParameter AddBinary([DisallowNull] this SqlParameterCollection self, [DisallowNull] string parameterName, byte[] value, ParameterDirection parameterDirection = ParameterDirection.Input)
        {
            var parameterType = SqlDbType.VarBinary;

            SqlParameter parameter = new SqlParameter(parameterName, parameterType, -1);
            if (value != null)
            {
                parameter.Value = value;
            }
            else
            {
                parameter.Value = DBNull.Value;
            }
            parameter.Direction = parameterDirection;
            return self.Add(parameter);
        }
    }
}
