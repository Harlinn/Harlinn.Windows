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
namespace Harlinn.Hydrology
{
    /// <summary>
    /// Data abstraction for a stack of soil horizons
    /// </summary>
    public class SoilProfile
    {
        /// <summary>
        /// nickname for profile
        /// </summary>
        string _tag;
        /// <summary>
        /// Array of soil horizones making up profile
        /// </summary>
        readonly List<SoilClass> _soilClasses = new();
        /// <summary>
        /// Array of Thickness of horizons [m]
        /// </summary>
        readonly List<double> _thicknesses = new();

        public SoilProfile(string tag)
        {
            _tag = tag;
        }

        public string Tag { get => _tag; set => _tag = value; }
        public int NumHorizons => _soilClasses.Count;
        public int GetNumHorizons( ) => _soilClasses.Count;

        public IReadOnlyList<SoilClass> SoilClasses => _soilClasses;

        public IReadOnlyList<double> Thicknesses => _thicknesses;

        public void AddSoilLayer(SoilClass soilClass, double thickness)
        {
            _soilClasses.Add(soilClass);
            _thicknesses.Add(thickness);
        }

        public SoilClass GetSoilClass(int index)
        {
            return _soilClasses[index];
        }

        public string GetSoilTag(int index)
        {
            return _soilClasses[index].Tag;
        }

        public double GetThickness(int index)
        {
            return _thicknesses[index];
        }


    }
}
