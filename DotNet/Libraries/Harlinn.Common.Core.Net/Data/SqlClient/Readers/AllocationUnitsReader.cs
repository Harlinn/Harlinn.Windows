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

using Harlinn.Common.Core.Net.Data.SqlClient.Types;
using Microsoft.Data.SqlClient;
using Microsoft.Extensions.Logging;
using System.Diagnostics.CodeAnalysis;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers
{
    public class AllocationUnitsReader : DataReaderWrapper
    {
        public const string Sql = """
            SELECT sau.[allocation_unit_id]
                ,sau.[type]
                ,sau.[type_desc]
                ,sau.[container_id]
                ,sau.[data_space_id]
                ,sau.[total_pages]
                ,sau.[used_pages]
                ,sau.[data_pages]
            FROM [sys].[allocation_units] sau
            """;

        public const int AllocationUnitIdOrdinal = 0;
        public const int TypeOrdinal = 1;
        public const int TypeDescOrdinal = 2;
        public const int ContainerIdOrdinal = 3;
        public const int DataSpaceIdOrdinal = 4;
        public const int TotalPagesOrdinal = 5;
        public const int UsedPagesOrdinal = 6;
        public const int DataPagesOrdinal = 7;

        public AllocationUnitsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public AllocationUnitsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public AllocationUnitsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(logger, sqlDataReader, ownsReader)
        {
        }

        public int GetAllocationUnitId()
        {
            return GetInt32(AllocationUnitIdOrdinal);
        }
        public byte GetAllocationUnitType()
        {
            return GetByte(TypeOrdinal);
        }

        public string GetAllocationUnitTypeDesc()
        {
            return GetString(TypeDescOrdinal);
        }

        public long GetContainerId()
        {
            return GetInt64(ContainerIdOrdinal);
        }

        public int GetDataSpaceId()
        {
            return GetInt32(DataSpaceIdOrdinal);
        }

        public long GetTotalPages()
        {
            return GetInt64(TotalPagesOrdinal);
        }

        public long GetUsedPages()
        {
            return GetInt64(UsedPagesOrdinal);
        }

        public long GetDataPages()
        {
            return GetInt64(DataPagesOrdinal);
        }


        
        public AllocationUnit GetAllocationUnit()
        {
            var allocationUnitId = GetAllocationUnitId();
            var type = GetAllocationUnitType();
            var typeDesc = GetAllocationUnitTypeDesc();
            var containerId = GetContainerId();
            var dataSpaceId = GetDataSpaceId();
            var totalPages = GetTotalPages();
            var usedPages = GetUsedPages();
            var dataPages = GetDataPages();
            return new AllocationUnit(allocationUnitId, type, typeDesc, containerId, dataSpaceId, totalPages, usedPages, dataPages);
        }

        public IReadOnlyList<AllocationUnit> GetAllocationUnits()
        {
            var allocationUnits = new List<AllocationUnit>();
            while (Read())
            {
                allocationUnits.Add(GetAllocationUnit());
            }
            return allocationUnits;
        }
        

    }

}
