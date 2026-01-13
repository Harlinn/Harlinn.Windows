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

public class SpatialIndexTessellationsDataType
{
    readonly int _objectId = 0;
    readonly int _indexId = 0;
    readonly string? _tessellationScheme;
    readonly double? _boundingBoxXmin;
    readonly double? _boundingBoxYmin;
    readonly double? _boundingBoxXmax;
    readonly double? _boundingBoxYmax;
    readonly short? _level1Grid;
    readonly string? _level1GridDesc;
    readonly short? _level2Grid;
    readonly string? _level2GridDesc;
    readonly short? _level3Grid;
    readonly string? _level3GridDesc;
    readonly short? _level4Grid;
    readonly string? _level4GridDesc;
    readonly int? _cellsPerObject;

    public SpatialIndexTessellationsDataType( )
    {
    }

    public SpatialIndexTessellationsDataType(int objectId,
        int indexId,
        string? tessellationScheme,
        double? boundingBoxXmin,
        double? boundingBoxYmin,
        double? boundingBoxXmax,
        double? boundingBoxYmax,
        short? level1Grid,
        string? level1GridDesc,
        short? level2Grid,
        string? level2GridDesc,
        short? level3Grid,
        string? level3GridDesc,
        short? level4Grid,
        string? level4GridDesc,
        int? cellsPerObject)
    {
        _objectId = objectId;
        _indexId = indexId;
        _tessellationScheme = tessellationScheme;
        _boundingBoxXmin = boundingBoxXmin;
        _boundingBoxYmin = boundingBoxYmin;
        _boundingBoxXmax = boundingBoxXmax;
        _boundingBoxYmax = boundingBoxYmax;
        _level1Grid = level1Grid;
        _level1GridDesc = level1GridDesc;
        _level2Grid = level2Grid;
        _level2GridDesc = level2GridDesc;
        _level3Grid = level3Grid;
        _level3GridDesc = level3GridDesc;
        _level4Grid = level4Grid;
        _level4GridDesc = level4GridDesc;
        _cellsPerObject = cellsPerObject;
    }

    public int ObjectId => _objectId;
    public int IndexId => _indexId;
    public string? TessellationScheme => _tessellationScheme;
    public double? BoundingBoxXmin => _boundingBoxXmin;
    public double? BoundingBoxYmin => _boundingBoxYmin;
    public double? BoundingBoxXmax => _boundingBoxXmax;
    public double? BoundingBoxYmax => _boundingBoxYmax;
    public short? Level1Grid => _level1Grid;
    public string? Level1GridDesc => _level1GridDesc;
    public short? Level2Grid => _level2Grid;
    public string? Level2GridDesc => _level2GridDesc;
    public short? Level3Grid => _level3Grid;
    public string? Level3GridDesc => _level3GridDesc;
    public short? Level4Grid => _level4Grid;
    public string? Level4GridDesc => _level4GridDesc;
    public int? CellsPerObject => _cellsPerObject;
}
