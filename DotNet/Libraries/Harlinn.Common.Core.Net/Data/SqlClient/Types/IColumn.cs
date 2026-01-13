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

using System.Data.SqlTypes;
using System.Reflection.Metadata;
using System.Security.Principal;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types
{
    public interface ITyped
    {
        /// <summary>
        /// ID of the object to which this column belongs
        /// </summary>
        public int ObjectId { get; }

        /// <summary>
        /// Name of the column. Is unique within the object.
        /// </summary>
        public string Name { get; }

        /// <summary>
        /// ID of the system type of the column.
        /// </summary>
        public byte SystemTypeId { get; }

        /// <summary>
        /// ID of the system type of the column.
        /// </summary>
        public SystemType SystemType { get; }

        /// <summary>
        /// ID of the type of the column as defined by the user.
        /// </summary>
        public int UserTypeId { get; }

        /// <summary>
        /// Maximum length (in bytes) of the column.
        /// <para>
        /// -1 = Column data type is varchar(max), nvarchar(max), varbinary(max), or xml.
        /// </para>
        /// <para>
        /// For text, ntext, and image columns, the max_length value is 16 
        /// (representing the 16-byte pointer only) or the value set by 
        /// sp_tableoption 'text in row'.
        /// </para>
        /// </summary>
        public short MaxLength { get; }

        /// <summary>
        /// Precision of the column if numeric-based; otherwise, 0.
        /// </summary>
        public byte Precision { get; }

        /// <summary>
        /// Scale of column if numeric-based; otherwise, 0.
        /// </summary>
        public byte Scale { get; }

        /// <summary>
        /// true if the column allows nulls; otherwise, false.
        /// </summary>
        public bool IsNullable { get; }

        public string TypeName { get; }

    }

    public interface IColumn : ITyped
    {
        

        /// <summary>
        /// ID of the column. Is unique within the object. Column IDs might not be sequential.
        /// </summary>
        public int ColumnId { get; }
        

        /// <summary>
        /// Name of the collation of the column if character-based; otherwise null.
        /// </summary>
        public string? CollationName { get; }

        

        /// <summary>
        /// Gets a value indicating whether the column value is padded with ANSI spaces to match its defined length.
        /// </summary>
        public bool IsAnsiPadded { get; }

        /// <summary>
        /// Column is a declared ROWGUIDCOL
        /// </summary>
        public bool IsRowguidcol { get; }

        /// <summary>
        /// Column has identity values
        /// </summary>
        public bool IsIdentity { get; }

        public bool IsComputed { get; }

        public bool IsFilestream { get; }

        public bool IsReplicated { get; }

        public bool IsNonSqlSubscribed { get; }

        public bool IsMergePublished { get; }

        public bool IsDtsReplicated { get; }

        public bool IsXmlDocument { get; }

        public int XmlCollectionId { get; }

        public int DefaultObjectId { get; }

        public int RuleObjectId { get; }

        public bool IsSparse { get; }

        public bool IsColumnSet { get; }

        public byte GeneratedAlwaysType { get; }

        public string GeneratedAlwaysTypeDesc { get; }

        public int? EncryptionType { get; }

        public string? EncryptionTypeDesc { get; }

        public string? EncryptionAlgorithmName { get; }

        public int? ColumnEncryptionKeyId { get; }

        public string? ColumnEncryptionKeyDatabaseName { get; }

        public bool IsHidden { get; }

        public bool IsMasked { get; }

        public int? GraphType { get; }

        public string? GraphTypeDesc { get; }

        
    }
}