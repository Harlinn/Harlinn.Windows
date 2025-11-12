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
    /// river/stream channel cross section with associated rating curve
    /// </summary>
    public class ChannelXSect
    {
        /// <summary>
        /// nickname for XSect
        /// </summary>
        string _name;

        /// <summary>
        /// slope of river channel
        /// </summary>
        double _bedslope;

        /// <summary>
        /// true for closed channels/conduits
        /// </summary>
        bool _is_closed_channel;
        /// <summary>
        /// # of survey points, _nSurveyPts=0 if rating curve not generated from surveyed data
        /// </summary>
        int _nSurveyPts;
        /// <summary>
        /// survey points in local coordinates [m]
        /// </summary>
        double[] _aX;
        /// <summary>
        /// bottom channel elevation at survey pts (size nSurveyPts)[m above arbitrary datum]
        /// </summary>
        double[] _aElev;
        /// <summary>
        /// Mannings roughness for each segment (between aX[i] and aX[i+1]) (size: nSurveyPts-1)
        /// </summary>
        double[] _aMann;
        /// <summary>
        /// minimum roughness coefficient for all segments
        /// </summary>
        double _min_mannings;
        /// <summary>
        /// minimum elevation of channel profile
        /// </summary>
        double _min_stage_elev;

        /// <summary>
        /// number of points on rating curves
        /// </summary>
        int _nPoints;
        /// <summary>
        /// Rating curve for flow rates [m3/s]
        /// </summary>
        double[] _aQ;
        /// <summary>
        /// Rating curve for stage elevation [m]
        /// </summary>
        double[] _aStage;
        /// <summary>
        /// Rating curve for top width [m]
        /// </summary>
        double[] _aTopWidth;
        /// <summary>
        /// Rating curve for X-sectional area [m2]
        /// </summary>
        double[] _aXArea;
        /// <summary>
        /// Rating curve for wetted perimeter [m]
        /// </summary>
        double[] _aPerim;

    }
}
