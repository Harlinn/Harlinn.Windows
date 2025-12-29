using Harlinn.MSSql.Tool.Output;

namespace Harlinn.MSSql.Tool.CodeGenerators.CSharp
{
    public class CSharpSqlDataReaderExtensionsGenerator : CodeWriter
    {
        public CSharpSqlDataReaderExtensionsGenerator(Context context) 
            : base(context)
        {
        }

        public void Run()
        {
            var databaseReaderNamespace = CSharpHelper.GetDatabaseReaderNamespace(Context);

            WriteLine("""
            using System;
            using System.Data;
            using System.Data.Common;
            using System.Data.SqlTypes;
            using System.Collections.Generic;
            using Microsoft.Data.SqlClient;
            using Microsoft.SqlServer.Types;
            """);
            WriteLine();
            WriteLine($"namespace {databaseReaderNamespace}");
            WriteLine("""
            {
                public static class SqlDataReaderExtensions
                {
                    public static bool? GetNullableBoolean(this SqlDataReader reader, int ordinal)
                    {
                        if (reader.IsDBNull(ordinal))
                        {
                            return null;
                        }
                        return reader.GetBoolean(ordinal);
                    }

                    public static byte? GetNullableByte(this SqlDataReader reader, int ordinal)
                    {
                        if (reader.IsDBNull(ordinal))
                        {
                            return null;
                        }                
                        return reader.GetByte(ordinal);
                    }

                    public static sbyte? GetNullableSByte(this SqlDataReader reader, int ordinal)
                    {
                        if (reader.IsDBNull(ordinal))
                        {
                            return null;
                        }
                        return unchecked((sbyte)reader.GetByte(ordinal));
                    }

                    public static sbyte GetSByte(this SqlDataReader reader, int ordinal)
                    {
                        return unchecked((sbyte)reader.GetByte(ordinal));
                    }

                    public static short? GetNullableInt16(this SqlDataReader reader, int ordinal)
                    {
                        if (reader.IsDBNull(ordinal))
                        {
                            return null;
                        }
                        return reader.GetInt16(ordinal);
                    }

                    public static ushort? GetNullableUInt16(this SqlDataReader reader, int ordinal)
                    {
                        if (reader.IsDBNull(ordinal))
                        {
                            return null;
                        }                             
                        return unchecked((ushort)reader.GetInt16(ordinal));
                    }

                    public static ushort GetUInt16(this SqlDataReader reader, int ordinal)
                    {
                        return unchecked((ushort)reader.GetInt16(ordinal));
                    }

                    public static int? GetNullableInt32(this SqlDataReader reader, int ordinal)
                    {
                        if (reader.IsDBNull(ordinal))
                        {
                            return null;
                        }
                        return reader.GetInt32(ordinal);
                    }

                    public static uint? GetNullableUInt32(this SqlDataReader reader, int ordinal)
                    {
                        if (reader.IsDBNull(ordinal))
                        {
                            return null;
                        }
                        return unchecked((uint)reader.GetInt32(ordinal));
                    }

                    public static uint GetUInt32(this SqlDataReader reader, int ordinal)
                    {
                        return unchecked((uint)reader.GetInt32(ordinal));
                    }


                    public static long? GetNullableInt64(this SqlDataReader reader, int ordinal)
                    {
                        if (reader.IsDBNull(ordinal))
                        {
                            return null;
                        }
                        return reader.GetInt64(ordinal);
                    }

                    public static ulong? GetNullableUInt64(this SqlDataReader reader, int ordinal)
                    {
                        if (reader.IsDBNull(ordinal))
                        {
                            return null;
                        }
                        return unchecked((ulong)reader.GetInt64(ordinal));
                    }

                    public static ulong GetUInt64(this SqlDataReader reader, int ordinal)
                    {
                        return unchecked((ulong)reader.GetInt64(ordinal));
                    }

                    public static float? GetNullableSingle(this SqlDataReader reader, int ordinal)
                    {
                        if (reader.IsDBNull(ordinal))
                        {
                            return null;
                        }
                        return reader.GetFloat(ordinal);
                    }

                    public static float GetSingle(this SqlDataReader reader, int ordinal)
                    {
                        return reader.GetFloat(ordinal);
                    }

                    public static double? GetNullableDouble(this SqlDataReader reader, int ordinal)
                    {
                        if (reader.IsDBNull(ordinal))
                        {
                            return null;
                        }
                        return reader.GetDouble(ordinal);
                    }

                    public static decimal? GetNullableDecimal(this SqlDataReader reader, int ordinal)
                    {
                        if (reader.IsDBNull(ordinal))
                        {
                            return null;
                        }
                        return reader.GetDecimal(ordinal);
                    }

                    public static DateTime? GetNullableDateTime(this SqlDataReader reader, int ordinal)
                    {
                        if (reader.IsDBNull(ordinal))
                        {
                            return null;
                        }
                        return reader.GetDateTime(ordinal);
                    }

                    public static TimeSpan? GetNullableTimeSpan(this SqlDataReader reader, int ordinal)
                    {
                        if (reader.IsDBNull(ordinal))
                        {
                            return null;
                        }
                        return new TimeSpan( reader.GetInt64(ordinal) );
                    }

                    public static TimeSpan GetTimeSpan(this SqlDataReader reader, int ordinal)
                    {
                        return new TimeSpan(reader.GetInt64(ordinal));
                    }

                    public static Guid? GetNullableGuid(this SqlDataReader reader, int ordinal)
                    {
                        if (reader.IsDBNull(ordinal))
                        {
                            return null;
                        }
                        return reader.GetGuid(ordinal);
                    }

                    public static string? GetNullableString(this SqlDataReader reader, int ordinal)
                    {
                        if (reader.IsDBNull(ordinal))
                        {
                            return null;
                        }
                        return reader.GetString(ordinal);
                    }

                    public static byte[]? GetNullableBinary(this SqlDataReader reader, int ordinal)
                    {
                        if (reader.IsDBNull(ordinal))
                        {
                            return null;
                        }
                        return reader.GetSqlBytes(ordinal).Value;
                    }

                    public static byte[] GetBinary(this SqlDataReader reader, int ordinal)
                    {
                        return reader.GetSqlBytes(ordinal).Value;
                    }

                    public static SqlHierarchyId GetSqlHierarchyId(this SqlDataReader reader, int i)
                    {
                        var result = (SqlHierarchyId)reader.GetSqlValue(i);
                        return result;
                    }

                    public static SqlHierarchyId? GetNullableSqlHierarchyId(this SqlDataReader reader, int i)
                    {
                        if (reader.IsDBNull(i))
                        {
                            return null;
                        }
                        var result = (SqlHierarchyId)reader.GetSqlValue(i);
                        return result;
                    }

                    public static SqlGeography GetSqlGeography(this SqlDataReader reader, int i)
                    {
                        var result = (SqlGeography)reader.GetSqlValue(i);
                        return result;
                    }

                    public static SqlGeography? GetNullableSqlGeography(this SqlDataReader reader, int i)
                    {
                        if (reader.IsDBNull(i))
                        {
                            return null;
                        }
                        var result = (SqlGeography)reader.GetSqlValue(i);
                        return result;
                    }

                    public static SqlGeometry GetSqlGeometry(this SqlDataReader reader, int i)
                    {
                        var result = (SqlGeometry)reader.GetSqlValue(i);
                        return result;
                    }

                    public static SqlGeometry? GetNullableSqlGeometry(this SqlDataReader reader, int i)
                    {
                        if (reader.IsDBNull(i))
                        {
                            return null;
                        }
                        var result = (SqlGeometry)reader.GetSqlValue(i);
                        return result;
                    }

                    public static SqlXml GetSqlXml(this SqlDataReader reader, int i)
                    {
                        var result = reader.GetSqlXml(i);
                        return result;
                    }

                    public static SqlXml? GetNullableSqlXml(this SqlDataReader reader, int i)
                    {
                        if (reader.IsDBNull(i))
                        {
                            return null;
                        }
                        var result = reader.GetSqlXml(i);
                        return result;
                    }

                }
            }
            """);
        }
    }


}
