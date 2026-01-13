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
using System;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types;

public class ExternalFileFormatsDataType
{
    readonly int _fileFormatId = 0;
    readonly string _name = string.Empty;
    readonly string _formatType = string.Empty;
    readonly string? _fieldTerminator;
    readonly string? _stringDelimiter;
    readonly string? _dateFormat;
    readonly bool? _useTypeDefault;
    readonly string? _serdeMethod;
    readonly string? _rowTerminator;
    readonly string? _encoding;
    readonly string? _dataCompression;
    readonly int? _firstRow;

    public ExternalFileFormatsDataType( )
    {
    }

    public ExternalFileFormatsDataType(int fileFormatId,
        string name,
        string formatType,
        string? fieldTerminator,
        string? stringDelimiter,
        string? dateFormat,
        bool? useTypeDefault,
        string? serdeMethod,
        string? rowTerminator,
        string? encoding,
        string? dataCompression,
        int? firstRow)
    {
        _fileFormatId = fileFormatId;
        _name = name;
        _formatType = formatType;
        _fieldTerminator = fieldTerminator;
        _stringDelimiter = stringDelimiter;
        _dateFormat = dateFormat;
        _useTypeDefault = useTypeDefault;
        _serdeMethod = serdeMethod;
        _rowTerminator = rowTerminator;
        _encoding = encoding;
        _dataCompression = dataCompression;
        _firstRow = firstRow;
    }

    public int FileFormatId => _fileFormatId;
    public string Name => _name;
    public string FormatType => _formatType;
    public string? FieldTerminator => _fieldTerminator;
    public string? StringDelimiter => _stringDelimiter;
    public string? DateFormat => _dateFormat;
    public bool? UseTypeDefault => _useTypeDefault;
    public string? SerdeMethod => _serdeMethod;
    public string? RowTerminator => _rowTerminator;
    public string? Encoding => _encoding;
    public string? DataCompression => _dataCompression;
    public int? FirstRow => _firstRow;
}
