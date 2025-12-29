/*
   Copyright 2024-2025 Espen Harlinn

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

using System.ComponentModel;
using System.Numerics;
using System.Xml.Serialization;
using SchemaTypes = Harlinn.Common.Core.Net.Data.SqlClient.Types;

namespace Harlinn.MSSql.Tool.Input.Types
{
    public abstract class ResultSetColumn
    {
        string? _name;
        string? _column;
        bool _isNullable;

        protected ResultSetColumn()
        {
        }

        protected ResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn)
        {
            _name = resultSetColumn.Name;
            _isNullable = resultSetColumn.IsNullable;
        }

        [XmlIgnore]
        public abstract ResultSetColumnType ColumnType { get; }
        [XmlAttribute, DefaultValue(null)]
        public string? Name { get => _name; set => _name = value; }
        [XmlAttribute, DefaultValue(null)]
        public string? Column { get => _column; set => _column = value; }
        [XmlAttribute, DefaultValue(false)]
        public bool IsNullable { get => _isNullable; set => _isNullable = value; }
    }

    public abstract class ValueResultSetColumn<T> : ResultSetColumn where T : struct
    {
        protected ValueResultSetColumn()
        {
        }

        protected ValueResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn) 
            : base(resultSetColumn)
        {
        }
    }

    public abstract class RangeResultSetColumn<T> : ValueResultSetColumn<T> where T : struct, IComparable<T>, IMinMaxValue<T>
    {
        protected RangeResultSetColumn()
        {
        }

        protected RangeResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn) 
            : base(resultSetColumn)
        {
        }
    }

    public abstract class NumberResultSetColumn<T> : RangeResultSetColumn<T> where T : struct, IComparable<T>, IMinMaxValue<T>, INumber<T>
    {
        protected NumberResultSetColumn()
        {
        }

        protected NumberResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn) 
            : base(resultSetColumn)
        {
        }
    }

    public abstract class NumericResultSetColumn<T> : RangeResultSetColumn<T> where T : struct, IComparable<T>, IMinMaxValue<T>, INumber<T>
    {
        protected NumericResultSetColumn()
        {
        }

        protected NumericResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn) 
            : base(resultSetColumn)
        {
        }
    }

    public abstract class IntegerResultSetColumn<T> : RangeResultSetColumn<T> where T : struct, IComparable<T>, IMinMaxValue<T>, INumber<T>
    {
        protected IntegerResultSetColumn()
        {
        }

        protected IntegerResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn) 
            : base(resultSetColumn)
        {
        }
    }


    public class BooleanResultSetColumn : ValueResultSetColumn<bool>
    {
        public BooleanResultSetColumn()
        {
        }
        public BooleanResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn) 
            : base(resultSetColumn)
        {
        }
        public override ResultSetColumnType ColumnType => ResultSetColumnType.Boolean;
    }

    public class ByteResultSetColumn : IntegerResultSetColumn<byte>
    {
        public ByteResultSetColumn()
        {
        }
        public ByteResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn) 
            : base(resultSetColumn)
        {
        }
        public override ResultSetColumnType ColumnType => ResultSetColumnType.Byte;
    }

    public class SByteResultSetColumn : IntegerResultSetColumn<sbyte>
    {
        public SByteResultSetColumn()
        {
        }
        public SByteResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn)
            : base(resultSetColumn)
        {
        }
        public override ResultSetColumnType ColumnType => ResultSetColumnType.SByte;
    }

    public class CharResultSetColumn : ValueResultSetColumn<char>
    {
        public CharResultSetColumn()
        {
        }
        public CharResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn)
            : base(resultSetColumn)
        {
        }
        public override ResultSetColumnType ColumnType => ResultSetColumnType.Char;
    }

    public class Int16ResultSetColumn : IntegerResultSetColumn<short>
    {
        public Int16ResultSetColumn()
        {
        }
        public Int16ResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn)
            : base(resultSetColumn)
        {
        }
        public override ResultSetColumnType ColumnType => ResultSetColumnType.Int16;
    }

    public class UInt16ResultSetColumn : IntegerResultSetColumn<ushort>
    {
        public UInt16ResultSetColumn()
        {
        }
        public UInt16ResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn)
            : base(resultSetColumn)
        {
        }
        public override ResultSetColumnType ColumnType => ResultSetColumnType.UInt16;
    }

    public class Int32ResultSetColumn : IntegerResultSetColumn<int>
    {
        public Int32ResultSetColumn()
        {
        }
        public Int32ResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn)
            : base(resultSetColumn)
        {
        }
        public override ResultSetColumnType ColumnType => ResultSetColumnType.Int32;
    }

    public class UInt32ResultSetColumn : IntegerResultSetColumn<uint>
    {
        public UInt32ResultSetColumn()
        {
        }
        public UInt32ResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn)
            : base(resultSetColumn)
        {
        }
        public override ResultSetColumnType ColumnType => ResultSetColumnType.UInt32;
    }

    public class Int64ResultSetColumn : IntegerResultSetColumn<long>
    {
        public Int64ResultSetColumn()
        {
        }
        public Int64ResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn)
            : base(resultSetColumn)
        {
        }
        public override ResultSetColumnType ColumnType => ResultSetColumnType.Int64;
    }

    public class UInt64ResultSetColumn : IntegerResultSetColumn<ulong>
    {
        public UInt64ResultSetColumn()
        {
        }
        public UInt64ResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn)
            : base(resultSetColumn)
        {
        }
        public override ResultSetColumnType ColumnType => ResultSetColumnType.UInt64;
    }

    public class SingleResultSetColumn : NumericResultSetColumn<float>
    {
        public SingleResultSetColumn()
        {
        }
        public SingleResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn)
            : base(resultSetColumn)
        {
        }
        public override ResultSetColumnType ColumnType => ResultSetColumnType.Single;
    }

    public class DoubleResultSetColumn : NumericResultSetColumn<double>
    {
        public DoubleResultSetColumn()
        {
        }
        public DoubleResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn)
            : base(resultSetColumn)
        {
        }
        public override ResultSetColumnType ColumnType => ResultSetColumnType.Double;
    }

    public class DecimalResultSetColumn : NumericResultSetColumn<decimal>
    {
        public DecimalResultSetColumn()
        {
        }
        public DecimalResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn)
            : base(resultSetColumn)
        {
        }
        public override ResultSetColumnType ColumnType => ResultSetColumnType.Decimal;
    }

    public class DateTimeResultSetColumn : ValueResultSetColumn<DateTime>
    {
        public DateTimeResultSetColumn()
        {
        }
        public DateTimeResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn)
            : base(resultSetColumn)
        {
        }
        public override ResultSetColumnType ColumnType => ResultSetColumnType.DateTime;
    }

    public class TimeSpanResultSetColumn : ValueResultSetColumn<TimeSpan>
    {
        public TimeSpanResultSetColumn()
        {
        }
        public TimeSpanResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn)
            : base(resultSetColumn)
        {
        }
        public override ResultSetColumnType ColumnType => ResultSetColumnType.TimeSpan;
    }

    public class GuidResultSetColumn : ValueResultSetColumn<Guid>
    {
        public GuidResultSetColumn()
        {
        }
        public GuidResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn)
            : base(resultSetColumn)
        {
        }
        public override ResultSetColumnType ColumnType => ResultSetColumnType.Guid;
    }

    public class StringResultSetColumn : ResultSetColumn
    {
        public StringResultSetColumn()
        {
        }
        public StringResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn)
            : base(resultSetColumn)
        {
        }
        public override ResultSetColumnType ColumnType => ResultSetColumnType.String;
    }

    public class BinaryResultSetColumn : ResultSetColumn
    {
        public BinaryResultSetColumn()
        {
        }
        public BinaryResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn)
            : base(resultSetColumn)
        {
        }
        public override ResultSetColumnType ColumnType => ResultSetColumnType.Binary;
    }

    public class SqlVariantResultSetColumn : ResultSetColumn
    {
        public SqlVariantResultSetColumn()
        {
        }
        public SqlVariantResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn)
            : base(resultSetColumn)
        {
        }
        public override ResultSetColumnType ColumnType => ResultSetColumnType.SqlVariant;
    }

    public class HierarchyIdResultSetColumn : ResultSetColumn
    {
        public HierarchyIdResultSetColumn()
        {
        }
        public HierarchyIdResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn)
            : base(resultSetColumn)
        {
        }
        public override ResultSetColumnType ColumnType => ResultSetColumnType.HierarchyId;
    }

    public class GeometryResultSetColumn : ResultSetColumn
    {
        public GeometryResultSetColumn()
        {
        }
        public GeometryResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn)
            : base(resultSetColumn)
        {
        }
        public override ResultSetColumnType ColumnType => ResultSetColumnType.Geometry;
    }

    public class GeographyResultSetColumn : ResultSetColumn
    {
        public GeographyResultSetColumn()
        {
        }
        public GeographyResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn)
            : base(resultSetColumn)
        {
        }
        public override ResultSetColumnType ColumnType => ResultSetColumnType.Geography;
    }

    public class XmlResultSetColumn : ResultSetColumn
    {
        public XmlResultSetColumn()
        {
        }
        public XmlResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn)
            : base(resultSetColumn)
        {
        }
        public override ResultSetColumnType ColumnType => ResultSetColumnType.Xml;
    }

    public abstract class TypedResultSetColumn : ResultSetColumn
    {
        public TypedResultSetColumn()
        {
        }
        public TypedResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn)
            : base(resultSetColumn)
        {
        }
    }

    public class ObjectResultSetColumn : TypedResultSetColumn
    {
        public ObjectResultSetColumn()
        {
        }
        public ObjectResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn)
            : base(resultSetColumn)
        {
        }
        public override ResultSetColumnType ColumnType => ResultSetColumnType.Object;
    }

    public class EnumResultSetColumn : TypedResultSetColumn
    {
        public EnumResultSetColumn()
        {
        }
        public EnumResultSetColumn(SchemaTypes.ResultSetColumn resultSetColumn)
            : base(resultSetColumn)
        {
        }
        public override ResultSetColumnType ColumnType => ResultSetColumnType.Enum;
    }





    }