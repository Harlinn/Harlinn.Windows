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

public class SpatialReferenceSystemsDataType
{
    readonly int? _spatialReferenceId;
    readonly string? _authorityName;
    readonly int? _authorizedSpatialReferenceId;
    readonly string? _wellKnownText;
    readonly string? _unitOfMeasure;
    readonly double? _unitConversionFactor;

    public SpatialReferenceSystemsDataType( )
    {
    }

    public SpatialReferenceSystemsDataType(int? spatialReferenceId,
        string? authorityName,
        int? authorizedSpatialReferenceId,
        string? wellKnownText,
        string? unitOfMeasure,
        double? unitConversionFactor)
    {
        _spatialReferenceId = spatialReferenceId;
        _authorityName = authorityName;
        _authorizedSpatialReferenceId = authorizedSpatialReferenceId;
        _wellKnownText = wellKnownText;
        _unitOfMeasure = unitOfMeasure;
        _unitConversionFactor = unitConversionFactor;
    }

    public int? SpatialReferenceId => _spatialReferenceId;
    public string? AuthorityName => _authorityName;
    public int? AuthorizedSpatialReferenceId => _authorizedSpatialReferenceId;
    public string? WellKnownText => _wellKnownText;
    public string? UnitOfMeasure => _unitOfMeasure;
    public double? UnitConversionFactor => _unitConversionFactor;
}
