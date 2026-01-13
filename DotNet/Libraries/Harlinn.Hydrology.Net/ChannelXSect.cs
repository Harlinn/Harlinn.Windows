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

using System.Linq;
using System.Xml.Linq;
using static Harlinn.Hydrology.Common;
using static Harlinn.Hydrology.Constants;
using static Harlinn.Mathematics.Net.Common;
using static System.Math;

namespace Harlinn.Hydrology
{
    /// <summary>
    /// river/stream channel cross section with associated rating curve
    /// </summary>
    public class ChannelXSect
    {
        Model _model;

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
        double[] _aX = Array.Empty<double>();
        /// <summary>
        /// bottom channel elevation at survey pts (size nSurveyPts)[m above arbitrary datum]
        /// </summary>
        double[] _aElev = Array.Empty<double>();
        /// <summary>
        /// Mannings roughness for each segment (between aX[i] and aX[i+1]) (size: nSurveyPts-1)
        /// </summary>
        double[] _aMann = Array.Empty<double>();
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
        double[] _aQ = Array.Empty<double>();
        /// <summary>
        /// Rating curve for stage elevation [m]
        /// </summary>
        double[] _aStage = Array.Empty<double>();
        /// <summary>
        /// Rating curve for top width [m]
        /// </summary>
        double[] _aTopWidth = Array.Empty<double>();
        /// <summary>
        /// Rating curve for X-sectional area [m2]
        /// </summary>
        double[] _aXArea = Array.Empty<double>();
        /// <summary>
        /// Rating curve for wetted perimeter [m]
        /// </summary>
        double[] _aPerim = Array.Empty<double>();

        

        ChannelXSect(Model model, string name)
        {
            _model = model;
            _name = name;
            model.AddChannelXSect(this);
        }

        /// <summary>
        /// Constructor implementation if channel profile is specified from survey data
        /// </summary>
        /// <param name="model">
        /// Model instance
        /// </param>
        /// <param name="name">
        /// Name of the channel cross section
        /// </param>
        /// <param name="NumSurveyPts">
        /// number of survey points taken in data
        /// </param>
        /// <param name="X">
        /// Array of coordinates of survey points
        /// </param>
        /// <param name="Elev">
        /// Array of elevations of riverbed at survey points
        /// </param>
        /// <param name="ManningsN">
        /// Mannings roughness for each segment (effective size: NumSurveyPts-1)
        /// </param>
        /// <param name="slope">
        /// Riverbed slope
        /// </param>
        /// <exception cref="ArgumentOutOfRangeException"></exception>
        public ChannelXSect(Model model, string name, int NumSurveyPts, double[] X, double[] Elev, double[] ManningsN, double slope)
            : this(model, name)
        {
            _nSurveyPts = NumSurveyPts;
            _aX = new double[_nSurveyPts];
            _aElev = new double[_nSurveyPts];
            _aMann = new double[_nSurveyPts];
            _min_mannings = ALMOST_INF;
            for (int i = 0; i < _nSurveyPts; i++)
            {
                _aX[i] = X[i];
                _aElev[i] = Elev[i];
                _aMann[i] = ManningsN[i];
                _min_mannings = Min(_min_mannings, _aMann[i]);
                //check for valid mannings n
                if (_aMann[i] < 0)
                {
                    throw new ArgumentOutOfRangeException(nameof(ManningsN), $"Constructor: invalid mannings _aMann[{i}]: {_aMann[i]}.");
                }
            }
            _min_stage_elev = _aElev[0];
            for (int i = 1; i < _nSurveyPts; i++)
            {
                _min_stage_elev = Min(_min_stage_elev, _aElev[i]);
            }
            _nPoints = 20; //Default

            _bedslope = slope;
            if (_bedslope <= 0.0)
            {
                throw new ArgumentOutOfRangeException(nameof(slope), $"CChannelXSect Constructor: channel profile bedslope must be greater than zero. Provided value: {_bedslope}.");
            }

            GenerateRatingCurvesFromProfile(); 

        }

        /// <summary>
        /// Channel profile is specified from rating curves
        /// </summary>
        /// <param name="model">
        /// Model instance
        /// </param>
        /// <param name="name">
        /// Name of the channel cross section
        /// </param>
        /// <param name="array_size">
        /// number of survey points taken in data
        /// </param>
        /// <param name="flow">
        /// Array of flow rates corresponding to stages, in cms [size:array_size]
        /// </param>
        /// <param name="stage">
        /// Array of stage elevations, in meters [size:array_size]
        /// </param>
        /// <param name="width">
        /// Array of channel top widths corresponding to stages, in m [size:array_size]
        /// </param>
        /// <param name="area">
        /// Array of channel x-sectional areas corresponding to stages, in m2 [size:array_size]
        /// </param>
        /// <param name="perim">
        /// Array of channel wetted perimeters corresponding to stages, in m [size:array_size]
        /// </param>
        /// <param name="slope">
        /// Riverbed slope
        /// </param>
        /// <exception cref="ArgumentOutOfRangeException"></exception>
        public ChannelXSect(Model model, string name,
                             int array_size,
                             double[] flow,
                             double[] stage,
                             double[] width,
                             double[] area,
                             double[] perim,
                             double slope)
            : this(model, name)
        {
            if (slope <= 0.0)
            {
                throw new ArgumentOutOfRangeException(nameof(slope), $"CChannelXSect Constructor: channel profile bedslope must be greater than zero. Provided value: {slope}.");
            }

            _nPoints = array_size;
            _aQ = new double[_nPoints];
            _aStage = new double[_nPoints];
            _aTopWidth = new double[_nPoints];
            _aXArea = new double[_nPoints];
            _aPerim = new double[_nPoints];
            for (int i = 0; i < _nPoints; i++)
            {
                _aQ[i] = flow[i];
                _aStage[i] = stage[i];
                _aTopWidth[i] = width[i];
                _aXArea[i] = area[i];
                _aPerim[i] = perim[i];
            }
            _min_stage_elev = _aStage[0];
            for (int i = 1; i < _nPoints; i++)
            {
                _min_stage_elev = Min(_min_stage_elev, _aStage[i]);
            }
            _bedslope = slope;
            _min_mannings = 0.01;
        }

        /// <summary>
        /// channel is a simple trapezoid
        /// </summary>
        /// <param name="model">
        /// Model instance
        /// </param>
        /// <param name="name">
        /// Channel name
        /// </param>
        /// <param name="bottom_w">
        /// Bottom wall length [m]
        /// </param>
        /// <param name="sidewall_ratio">
        /// Trapezoid wall ratio (0 for vertical walls, 1 for 45 deg angle, etc.)
        /// </param>
        /// <param name="bottom_elev">
        /// Elevation of riverbed [m]
        /// </param>
        /// <param name="mannings_n">
        /// Mannings roughness
        /// </param>
        /// <param name="slope">
        /// Riverbed slope
        /// </param>
        /// <exception cref="ArgumentOutOfRangeException"></exception>
        public ChannelXSect(Model model, string name,
                             double bottom_w,
                             double sidewall_ratio,
                             double bottom_elev,
                             double mannings_n,
                             double slope)
            : this(model, name)
        {
            if (slope <= 0.0)
            {
                throw new ArgumentOutOfRangeException(nameof(slope), $"CChannelXSect Constructor: channel profile bedslope must be greater than zero. Provided value: {slope}.");
            }
            if (mannings_n <= 0.0)
            {
                throw new ArgumentOutOfRangeException(nameof(mannings_n), $"CChannelXSect Constructor: Manning's n must be greater than zero. Provided value: {mannings_n}.");
            }

            _bedslope = slope;
            _min_mannings = mannings_n;

            _nPoints = 50;
            _aQ = new double[_nPoints];
            _aStage = new double[_nPoints];
            _aTopWidth = new double[_nPoints];
            _aXArea = new double[_nPoints];
            _aPerim = new double[_nPoints];
            double dh = 0.1;//m -to 5 m
            double h;
            for (int i = 0; i < _nPoints; i++)
            {
                h = i * dh;
                if (i == _nPoints - 1) { h = 20; }//m
                _aStage[i] = bottom_elev + h;
                _aTopWidth[i] = bottom_w + 2.0 * sidewall_ratio * h;
                _aXArea[i] = (bottom_w + sidewall_ratio) * h;
                _aPerim[i] = bottom_w + 2 * Sqrt(h * h * (1 + sidewall_ratio * sidewall_ratio));
                _aQ[i] = Sqrt(_bedslope) * _aXArea[i] * Pow(_aXArea[i] / _aPerim[i], 2.0 / 3.0) / _min_mannings;
            }
            _min_stage_elev = _aStage[0];
        }

        /// <summary>
        /// channel is a circular pipe
        /// </summary>
        /// <param name="model">
        /// Model instance
        /// </param>
        /// <param name="name">
        /// Channel name
        /// </param>
        /// <param name="diameter">
        /// diameter [m]
        /// </param>
        /// <param name="bottom_elev">
        /// Elevation of riverbed [m]
        /// </param>
        /// <param name="mannings_n">
        /// Mannings roughness
        /// </param>
        /// <param name="slope">
        /// Riverbed slope
        /// </param>
        /// <exception cref="ArgumentOutOfRangeException"></exception>
        public ChannelXSect(Model model, string name,
                              double diameter,
                              double bottom_elev,
                              double mannings_n,
                              double slope)
            : this(model, name)
        {
            if (slope <= 0.0)
            {
                throw new ArgumentOutOfRangeException(nameof(slope), $"CChannelXSect Constructor: channel profile bedslope must be greater than zero. Provided value: {slope}.");
            }
            if (mannings_n <= 0.0)
            {
                throw new ArgumentOutOfRangeException(nameof(mannings_n), $"CChannelXSect Constructor: Manning's n must be greater than zero. Provided value: {mannings_n}.");
            }
            _bedslope = slope;
            _min_mannings = mannings_n;

            _nPoints = 30;
            _aQ = new double[_nPoints];
            _aStage = new double[_nPoints];
            _aTopWidth = new double[_nPoints];
            _aXArea = new double[_nPoints];
            _aPerim = new double[_nPoints];
            double dh = diameter / (_nPoints - 1);
            double h, theta;
            double r = diameter / 2;
            for (int i = 0; i < _nPoints; i++)
            {
                h = i * dh;
                theta = 2.0 * Acos((r - h) / r);
                _aStage[i] = bottom_elev + h;
                _aTopWidth[i] = Sqrt((r - h / 2.0) * h * 8.0);
                _aXArea[i] = r * r * (theta - Sin(theta)) / 2.0;
                _aPerim[i] = r * theta;
                _aQ[i] = Sqrt(_bedslope) * _aXArea[i] * Pow(_aXArea[i] / _aPerim[i], 2.0 / 3.0) / _min_mannings;
                if (_aPerim[i] == 0) { _aQ[i] = 0.0; }
            }
            _min_stage_elev = bottom_elev;
            _is_closed_channel = true;
        }

        /// <summary>
        /// nickname for XSect
        /// </summary>
        public string Name => _name;

        /// <summary>
        /// slope of river channel
        /// </summary>
        public double Bedslope => _bedslope;

        /// <summary>
        /// true for closed channels/conduits
        /// </summary>
        public bool IsClosedChannel => _is_closed_channel;
        /// <summary>
        /// # of survey points, _nSurveyPts=0 if rating curve not generated from surveyed data
        /// </summary>
        public int NumSurveyPts => _nSurveyPts;
        /// <summary>
        /// survey points in local coordinates [m]
        /// </summary>
        public double[] X => _aX;
        /// <summary>
        /// bottom channel elevation at survey pts (size nSurveyPts)[m above arbitrary datum]
        /// </summary>
        public double[] Elevation => _aElev;
        /// <summary>
        /// Mannings roughness for each segment (between aX[i] and aX[i+1]) (size: nSurveyPts-1)
        /// </summary>
        public double[] ManningsRoughness => _aMann;
        /// <summary>
        /// minimum roughness coefficient for all segments
        /// </summary>
        public double MinMannings => _min_mannings;
        /// <summary>
        /// minimum elevation of channel profile
        /// </summary>
        public double MinStageElevation => _min_stage_elev;

        /// <summary>
        /// number of points on rating curves
        /// </summary>
        public int NumPoints => FlowRates.Length;
        /// <summary>
        /// Rating curve for flow rates [m3/s]
        /// </summary>
        public double[] FlowRates => _aQ;
        /// <summary>
        /// Rating curve for stage elevation [m]
        /// </summary>
        public double[] StageElevation => _aStage;
        /// <summary>
        /// Rating curve for top width [m]
        /// </summary>
        public double[] TopWidth => _aTopWidth;
        /// <summary>
        /// Rating curve for X-sectional area [m2]
        /// </summary>
        public double[] XArea => _aXArea;
        /// <summary>
        /// Rating curve for wetted perimeter [m]
        /// </summary>
        public double[] WettedPerimeter => _aPerim;

        /// <summary>
        /// Returns Cross-section name
        /// </summary>
        /// <returns>The Cross-section name</returns>
        public string GetName()
        {
            return _name;
        }

        /// <summary>
        /// Returns minimum mannings along channel.
        /// </summary>
        /// <returns>The minimum mannings along channel.</returns>
        public double GetMinMannings() 
        { 
            return _min_mannings; 
        }

        /// <summary>
        /// Returns the number of survey points
        /// </summary>
        /// <returns>
        /// The number of survey points
        /// </returns>
        public double GetNPoints() 
        { 
            return _nPoints; 
        }

        public double GetBedslope() { return _bedslope;}

        public double GetAQAt(int i) { return _aQ[i];}

        public double GetAStageAt(int i) { return _aStage[i];}

        public double GetATopWidthAt(int i) { return _aTopWidth[i];}

        public double GetAXAreaAt(int i) { return _aXArea[i] ;}

        public double GetAPerimAt(int i) { return _aPerim[i];}

        /// <summary>
        /// Returns Top width of channel [m]
        /// </summary>
        /// <param name="Q">
        /// Profile flowrate [m3/s]
        /// </param>
        /// <param name="SB_slope"></param>
        /// <param name="SB_n"></param>
        /// <returns></returns>
        public double GetTopWidth(double Q,double SB_slope,double SB_n)
        {
            GetFlowCorrections(SB_slope, SB_n, out var junk, out var Q_mult);
            return InterpolateCurve(Q / Q_mult, _aQ, _aTopWidth, true);
        }

        /// <summary>
        /// Returns cross-sectional area of channel [m]
        /// </summary>
        /// <param name="Q">
        /// Profile area
        /// </param>
        /// <param name="SB_slope"></param>
        /// <param name="SB_n"></param>
        /// <returns></returns>
        public double GetArea(double Q,double SB_slope,double SB_n)
        {
            GetFlowCorrections(SB_slope, SB_n, out var junk, out var Q_mult);
            return InterpolateCurve(Q / Q_mult, _aQ, _aXArea, true);
        }

        /// <summary>
        /// Returns stage elevation at a point [m]
        /// </summary>
        /// <param name="Q">
        /// Profile flowrate [m3/s]
        /// </param>
        /// <param name="SB_slope"></param>
        /// <param name="SB_n"></param>
        /// <returns></returns>
        public double GetStageElev(double Q,double SB_slope,double SB_n)
        {
            GetFlowCorrections(SB_slope, SB_n, out var junk, out var Q_mult);
            return InterpolateCurve(Q / Q_mult, _aQ, _aStage, true);
        }


        /// <summary>
        /// Returns channel depth at a point [m]
        /// </summary>
        /// <remarks>
        /// subtracts stage elevation at the specified discharge by the lowest elevation given
        /// </remarks>
        /// <param name="Q">
        /// Profile flowrate [m3/s]
        /// </param>
        /// <param name="SB_slope"></param>
        /// <param name="SB_n"></param>
        /// <returns>
        /// channel depth at specified flowrate
        /// </returns>
        public double GetDepth(double Q, double SB_slope, double SB_n)
        {
            return (GetStageElev(Q, SB_slope, SB_n) - _min_stage_elev);
        }

        /// <summary>
        /// Returns Wetted perimeter of channel [m]
        /// </summary>
        /// <param name="Q">
        /// Profile flowrate [m3/s]
        /// </param>
        /// <param name="SB_slope"></param>
        /// <param name="SB_n"></param>
        /// <returns>
        /// Wetted perimeter of channel at specified flowrate
        /// </returns>
        public double GetWettedPerim(double Q,double SB_slope,double SB_n)
        {
            GetFlowCorrections(SB_slope, SB_n, out var junk, out var Q_mult);
            return InterpolateCurve(Q / Q_mult, _aQ, _aPerim, true);
        }

        /// <summary>
        /// Returns correction terms for subbasin-specific slope and manning's n
        /// </summary>
        /// <param name="SB_slope">
        /// subbasin local slope (or AUTO_COMPUTE if channel slope should be used)
        /// </param>
        /// <param name="SB_n">
        /// subbasin local Manning's n (or AUTO_COMPUTE if channel n should be used)
        /// </param>
        /// <param name="slope_mult">
        /// correction multiplier for slope (S_actual = mult * S_channel)
        /// </param>
        /// <param name="Q_mult">
        /// correction multiplier for flow (Q_actual = mult * Q_channel)
        /// </param>
        public void GetFlowCorrections(double SB_slope, double SB_n, out double slope_mult, out double Q_mult)
        {
            slope_mult = 1.0;
            Q_mult = 1.0;
            if (SB_slope != AUTO_COMPUTE)
            {
                slope_mult = (SB_slope / _bedslope);
                // Mannings formula correction
                Q_mult = Pow(SB_slope / _bedslope, 0.5); 
            }
            if (SB_n != AUTO_COMPUTE)
            {
                Q_mult *= (_min_mannings / SB_n);
            }
        }

        /// <summary>
        /// Returns celerity of channel at reference flow [m/s]
        /// </summary>
        /// <param name="Q">
        /// flowrate [m3/s]
        /// </param>
        /// <param name="SB_slope"></param>
        /// <param name="SB_n"></param>
        /// <returns>
        /// Celerity of channel corresponding to flowrate [m/s]
        /// </returns>
        /// <exception cref="InvalidOperationException"></exception>
        public double GetCelerity(double Q, double SB_slope,double SB_n)
        {
            if(_aQ == null || _aQ.Length == 0)
            {
                throw new InvalidOperationException("GetCelerity: Rating curves not yet generated");
            }
            
            GetFlowCorrections(SB_slope, SB_n, out var junk, out var Q_mult);
            if ((_is_closed_channel) && (Q > Q_mult * _aQ[_nPoints - 1]))
            {
                throw new InvalidOperationException("CChannelXSect::GetCelerity: reference flowrate exceeds closed channel maximum. Conduit area is too small");
            }
            if (Q < 0) 
            { 
                return 0.0; 
            }
            int i = 0; 
            while ((Q > Q_mult * _aQ[i + 1]) && (i < (_nPoints - 2))) 
            { 
                i++; 
            }
            return Q_mult * (_aQ[i + 1] - _aQ[i]) / (_aXArea[i + 1] - _aXArea[i]);
        }

        /// <summary>
        /// Returns diffusivity of channel [m/s]
        /// </summary>
        /// <param name="Q">Channel flowrate [m3/s]</param>
        /// <param name="SB_slope">Slope of riverbed [m/m]</param>
        /// <param name="SB_n"></param>
        /// <returns>Diffusivity of channel at specified flowrate and slope [m3/s]</returns>
        /// <exception cref="ArgumentOutOfRangeException"></exception>
        public double GetDiffusivity(double Q, double SB_slope, double SB_n)
        {
            if (Q <= 0)
            {
                throw new ArgumentOutOfRangeException(nameof(Q), "GetDiffusivity: Invalid channel flowrate");
            }

            /// diffusivity from Roberson et al. 1995, Hydraulic Engineering
            GetFlowCorrections(SB_slope, SB_n, out var slope_mult, out var Q_mult);
            return 0.5 * (Q) / GetTopWidth(Q, SB_slope, SB_n) / (slope_mult * _bedslope);
        }

        public void CheckReferenceFlow(double Qref,double SB_slope,double SB_n,long SBID)
        {
            string warn;
            GetFlowCorrections(SB_slope, SB_n, out var junk, out var Q_mult);
            if ((Qref > Q_mult * _aQ[_nPoints - 1]))
            {
                warn = $"CheckReferenceFlow: reference flow exceeds channel maximum flow in subbasin {SBID}. Need to specify larger range of stages in channel profile.";
                Runtime.WriteWarning(warn, ExitCode.BAD_DATA);
            }
        }

        /// <summary>
        /// Returns varous properties from profile, given "elev"
        /// </summary>
        /// <param name="elev">
        /// Profile elevation [m]
        /// </param>
        /// <param name="Q">
        /// [out] Flowrate [m3/s]
        /// </param>
        /// <param name="w">
        /// [out] Top width [m]
        /// </param>
        /// <param name="A">
        /// [out] Cross sectional area [m2]
        /// </param>
        /// <param name="P">
        /// Wetted perimeter [m]
        /// </param>
        public void GetPropsFromProfile(double elev, out double Q, out double w, out double A, out double P)
        {
            double zl, zu; //upper and lower bottom elevation for surveyed channel segment
            double dx;    //length of surveyed channel segment
            double Ai, Pi, wi;
            double n_eff;
            A = 0; P = 0; Q = 0; w = 0; n_eff = 0;
            for (int i = 0; i < _nSurveyPts - 1; i++)
            {
                zl = Min(_aElev[i], _aElev[i + 1]);
                zu = Max(_aElev[i], _aElev[i + 1]);
                dx = Abs(_aX[i + 1] - _aX[i]);
                if ((elev <= zl) || (dx == 0))//dry part of reach, ignored
                {
                    Ai = 0;
                    Pi = 0;
                    wi = 0;
                }
                else if (elev >= zu) //fully wet part of profile
                {
                    wi = dx;
                    Ai = ((elev - zu) * dx + 0.5 * dx * (zu - zl)); //trapezoidal section
                    Pi = Sqrt(dx * dx + (zu - zl) * (zu - zl));
                    if ((i > 0) && (_aElev[i - 1] > _aElev[i]) && (_aX[i - 1] == _aX[i])) //handles straight adjacent sides (left)
                    {
                        if (elev <= _aElev[i - 1]) { Pi += (elev - _aElev[i]); }
                        else { Pi += (_aElev[i - 1] - _aElev[i]); }
                    }
                    if ((i < (_nSurveyPts - 2)) && (_aElev[i + 2] > _aElev[i + 1]) && (_aX[i + 2] == _aX[i + 1])) //handles straight adjacent sides (right)
                    {
                        if (elev <= _aElev[i + 2]) { Pi += (elev - _aElev[i + 1]); }
                        else { Pi += (_aElev[i + 2] - _aElev[i + 1]); }
                    }
                    if (i == 0) { Pi += (elev - _aElev[i]); }
                    if (i == _nSurveyPts - 2) { Pi += (elev - _aElev[i + 1]); }
                }
                else  //partially wet part of profile (includes riverbank)
                {
                    double ddx = (elev - zl) / (zu - zl) * dx; //width of wetted portion
                    if ((zu - zl) < REAL_SMALL) { ddx = 0.0; }//essentially flat reach, elev=zu=zl
                    Ai = 0.5 * (elev - zl) * ddx; //triangular section
                    Pi = Sqrt(ddx * ddx + (elev - zl) * (elev - zl));
                    wi = ddx;
                }
                A += Ai;
                P += Pi;
                w += wi;
                //using Mannings equation to calculate Q
                if (Ai > 0)
                {
                    Q += Pow(_bedslope, 0.5) * Ai * Pow(Ai / Pi, 2.0 / 3.0) / _aMann[i];
                }
                n_eff += Ai / _aMann[i]; //area weighted 1/n
            }
        }

        private void GenerateRatingCurvesFromProfile()
        {
            if(_aElev == null || _aElev.Length == 0)
            {
                throw new InvalidOperationException("GenerateRatingCurvesFromProfile: bad profile array");
            }

            _aQ = new double[_nPoints];
            _aStage = new double[_nPoints];
            _aTopWidth = new double[_nPoints];
            _aXArea = new double[_nPoints];
            _aPerim = new double[_nPoints];
            
            double maxe = _aElev[0];
            double mine = _aElev[0];
            for (int j = 0; j < _nSurveyPts; j++)
            {
                maxe = Max(maxe, _aElev[j]);
                mine = Min(mine, _aElev[j]);
            }
            if((maxe - mine) < REAL_SMALL)
            {
                throw new InvalidOperationException("GenerateRatingCurvesFromProfile: profile survey points all have same elevation");
            }

            double dz = (maxe - mine) / ((int)(_nPoints) - 1.0);

            int i = 0;
            for (double z = mine; z < maxe + 0.5 * dz; z += dz)
            {
                _aStage[i] = z;
                GetPropsFromProfile(z, out var Q, out var TopWidth, out var XArea, out var Perim);
                _aQ[i] = Q;
                _aTopWidth[i] = TopWidth;
                _aXArea[i] = XArea;
                _aPerim[i] = Perim;
                i++;
            }
        }



    }
}
