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

namespace Harlinn.Hydrology
{
    /// <summary>
    /// Gridded, 3D forcings
    /// </summary>
    public class ForcingGrid
    {
        /// <summary>
        /// Forcing type, e.g. PRECIP or TEMP
        /// </summary>
        ForcingType _ForcingType;
        /// <summary>
        /// Name of NetCDF file
        /// </summary>
        string _filename;
        /// <summary>
        /// Name of forcing variable in NetCDF file
        /// </summary>
        string _varname;

        /// <summary>
        /// Names of all three dimensions as in NetCDF file [ dim_cols, dim_row, dim_time]
        /// </summary>
        string[] _DimNames = new string[3];
        /// <summary>
        /// Length of dimensions of grid [ size = (x,y,t) = (NC, NR, _ChunkSize) ]
        /// </summary>
        int[] _GridDims = new int[3];
        /// <summary>
        /// number of cells = _GridDims[0]*_GridDims[1] for 3D, _GridDims[0] otherwise
        /// </summary>
        int _nCells;

        /// <summary>
        /// number of HRUs, locally stored
        /// </summary>
        int _nHydroUnits;

        /// <summary>
        /// code (1-6) for different dimension orders (x,y,t) = 1, (y,x,t) = 2, (x,t,y) = 3, (t,x,y) = 4, (y,t,x) = 5, (t,y,x) = 6
        /// </summary>
        int _dim_order;

        /// <summary>
        /// number of time points read before upper limit of allowed storage is reached
        /// </summary>
        int _ChunkSize;
        /// <summary>
        /// number of chunks (blocks) which can be read
        /// </summary>
        int _nChunk;
        /// <summary>
        /// current chunk read and stored in _aVal
        /// </summary>
        int _iChunk;

        /// <summary>
        /// Day corresponding to local TS time 0.0 (beginning of time series)
        /// </summary>
        double _start_day;
        /// <summary>
        /// Year corresponding to local TS time 0.0 (beginning of time series)
        /// </summary>
        int _start_year;
        /// <summary>
        /// data tag (additional information for data)
        /// </summary>
        string _tag;
        /// <summary>
        /// uniform interval between data points (in days); delta t
        /// </summary>
        double _interval;
        /// <summary>
        /// number of data intervals per day (pre-calculated for speed) =1.0/_interval
        /// </summary>
        int _steps_per_day;
        /// <summary>
        /// true if forcing grid is derived from input forcings (e.g. t_ave from t_min and t_max)
        /// false if forcing grid is directly read from NetCDF file (e.g. t_min or t_max)
        /// </summary>
        bool _is_derived;
        /// <summary>
        /// Array of magnitudes of pulses (variable units)
        /// [size _ChunkSize, _nNonZeroWeightedGridCells]
        /// time steps are in model resolution (means original input data are
        /// already aggregated to match model resolution)
        /// </summary>
        double[,] _aVal;
        /// <summary>
        /// Sparse array of weights for each HRU for a list of cells
        /// Dimensions : [_nHydroUnits][_nWeights[k]] (variable)
        /// _GridWeight[k][i] is fraction of forcing for HRU k is from grid cell _GridWtCellIDs[k][i]
        /// where grid cell index l=_GridWtCellIDs[k][i] is derived by l = j * dim_cols + i
        /// where i and j are the zero-indexed column and row of cell l respectively and
        /// dim_cols is the total number of columns.
        /// Following contraint must be satisfied:
        ///       sum(_GridWeight[k][i], {i=0,_nWeights[k]-1}) = 1.0 for all HRUs k=0,...,_nHydroUnits-1
        /// </summary>
        double[][] _GridWeight;
        /// <summary>
        /// cell IDs for all non-zero grid weights for HRU k size=[_nHydroUnits][_nWeights[k]] (variable)
        /// </summary>
        int[,] _GridWtCellIDs;
        /// <summary>
        /// local cell index ic (ranging from 0 to _nNonZeroWeightedGridCells-1)) corresponding to cell ID [size: _nCells]
        /// </summary>
        int[] _CellIDToIdx;
        /// <summary>
        /// number of weights for each HRU k (size=_nHydroUnits) (each entry greater or equal to 1)
        /// </summary>
        int[] _nWeights;
        /// <summary>
        /// Number of non-zero weighted grid cells:
        /// This is effectively the number of data points which is stored from the original data.
        /// </summary>
        int _nNonZeroWeightedGridCells;
        /// <summary>
        /// indexes of non-zero weighted grid cells [size = _nNonZeroWeightedGridCells]
        /// </summary>
        int[] _IdxNonZeroGridCells;
        /// <summary>
        /// length of data grid window in each dimension (x,y,t - defaults to _GridDims)
        /// </summary>
        int[] _WinLength = new int[3];
        /// <summary>
        /// data grid window starting point (x,y,t - defaults to 0, 0, chunksize)
        /// </summary>
        int[] _WinStart = new int[3];

        /// <summary>
        /// number of pulses (total duration=(nPulses-1)*_interval)
        /// flag determining whether this is a pulse-based or
        /// piecewise-linear time series
        /// </summary>
        int _nPulses;
        bool _pulse;
        /// <summary>
        /// correction time _t_corr, i.e. distance between
        /// current chunk start day and model start day (in days)
        /// </summary>
        double _t_corr;
        /// <summary>
        /// true if input precipitation needs to be deaccumulated from cum. mm to mm/d
        /// </summary>
        bool _deaccumulate;
        /// <summary>
        /// time shift of data (fractional day by which read data should be shifted)
        /// </summary>
        double _TimeShift;
        /// <summary>
        /// linear transformation of read data: new = a*data + b
        /// </summary>
        double _LinTrans_a;
        /// <summary>
        /// linear transformation of read data: new = a*data + b
        /// </summary>
        double _LinTrans_b;
        /// <summary>
        /// true if data is period ending - subtracts additional interval *on top of _TimeShift*
        /// </summary>
        bool _period_ending;
        /// <summary>
        /// true if forcings are 3D (lat, lon, time); false if 2D (stations, time)
        /// </summary>
        bool _is_3D;

        /// <summary>
        /// correction factor for rainfall (stored with gauge, used elsewhere)
        /// </summary>
        double _rainfall_corr;
        /// <summary>
        /// correction factor for snowfall (stored with gauge, used elsewhere)
        /// </summary>
        double _snowfall_corr;
        /// <summary>
        /// correction factor for temperature (stored with gauge, used elsewhere)
        /// </summary>
        double _temperature_corr;
        /// <summary>
        /// minimum temperature threshold used to determine cloud_cover factor
        /// </summary>
        double _cloud_min_temp;
        /// <summary>
        /// maximum temparature threshold used to determine cloud_cover factor
        /// </summary>
        double _cloud_max_temp;
        /// <summary>
        /// representative average monthly temperatures [C]
        /// </summary>
        double[] _aAveTemp = new double[12];
        /// <summary>
        /// representative minimum monthly temperatures [C]
        /// </summary>
        double[] _aMinTemp = new double[12];
        /// <summary>
        /// representative maximum monthly temperatures [C]
        /// </summary>
        double[] _aMaxTemp = new double[12];
        /// <summary>
        /// representative average monthly PET [mm/d] (or monthly PET factor [mm/d/K], if MONTHLY_FACTOR is used)
        /// </summary>
        double[] _aAvePET = new double[12];

        /// <summary>
        /// variable attribute names for [0]: lat [1]: long [2]:elev [3]: station identifier
        /// </summary>
        string[] _AttVarNames = new string[4];
        /// <summary>
        /// fixed array of cell centroid latitudes, if provided (size: _IdxNonZeroGridCells)
        /// </summary>
        double[] _aLatitude;
        /// <summary>
        /// fixed array of cell centroid longitudes, if provided (size: _IdxNonZeroGridCells)
        /// </summary>
        double[] _aLongitude;
        /// <summary>
        /// fixed array of cell representative elevations, if provided (size: _IdxNonZeroGridCells)
        /// </summary>
        double[] _aElevation;
        /// <summary>
        /// fixed array of cell station/cell IDS (size:_IdxNonZeroGridCells)
        /// </summary>
        string[] _aStationIDs;

        internal ForcingType GetForcingType()
        {
            throw new NotImplementedException();
        }
    }
}
