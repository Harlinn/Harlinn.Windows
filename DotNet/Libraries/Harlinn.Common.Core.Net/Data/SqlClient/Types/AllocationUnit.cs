using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types
{
    public enum AllocationUnitType : byte
    {
        /// <summary>
        /// Dropped
        /// </summary>
        Dropped = 0,
        /// <summary>
        /// In-row data (all data types, except LOB data types)
        /// </summary>
        InRowData = 1,
        /// <summary>
        /// Large object (LOB) data (text, ntext, image, xml, large value types, and CLR user-defined types)
        /// </summary>
        LobsData = 2,
        /// <summary>
        /// Row-overflow data
        /// </summary>
        RowOverflowData = 3
    }

    public class AllocationUnit
    {
        readonly long _allocationUnitId;
        readonly AllocationUnitType _type;
        readonly string _typeDesc;
        readonly long _containerId;
        readonly int _dataSpaceId;
        readonly long _totalPages;
        readonly long _usedPages;
        readonly long _dataPages;

        public AllocationUnit(long allocationUnitId, byte type, string typeDesc, long containerId, int dataSpaceId, long totalPages, long usedPages, long dataPages)
        {
            _allocationUnitId = allocationUnitId;
            _type = (AllocationUnitType)type;
            _typeDesc = typeDesc;
            _containerId = containerId;
            _dataSpaceId = dataSpaceId;
            _totalPages = totalPages;
            _usedPages = usedPages;
            _dataPages = dataPages;
        }

        public long AllocationUnitId => _allocationUnitId;

        public AllocationUnitType Type => _type;

        public string TypeDesc => _typeDesc;

        public long ContainerId => _containerId;

        public int DataSpaceId => _dataSpaceId;

        public long TotalPages => _totalPages;

        public long UsedPages => _usedPages;

        public long DataPages => _dataPages;
    }
}
