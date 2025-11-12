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
    /// Methods of modelling evaporation from multi-layered soil to atmosphere
    /// </summary>
    public enum SoilEvapType
    {
        /// <summary>
        /// uses GAWSER approach
        /// </summary>
        SOILEVAP_GAWSER,
        /// <summary>
        /// uses Federer 1979 resistance calculations \ref Federer 1979 \cite federer1979WRR
        /// </summary>
        SOILEVAP_FEDERER,
        /// <summary>
        /// linear relation between ET and tension storage, distributed by root fraction
        /// </summary>
        SOILEVAP_ROOTFRAC,
        /// <summary>
        /// Variable Infiltration Capacity model
        /// </summary>
        SOILEVAP_VIC,
        /// <summary>
        /// linear relation between ET and tension storage
        /// </summary>
        SOILEVAP_TOPMODEL,
        /// <summary>
        /// Sequential soil evaporation method for FUSE emulation - VIC ONLY
        /// </summary>
        SOILEVAP_SEQUEN,
        /// <summary>
        /// Root weighting soil evaporation method for FUSE emulation - VIC ONLY
        /// </summary>
        SOILEVAP_ROOT,
        /// <summary>
        /// same as ROOT, but top layer constrained to be above sat_wilt
        /// </summary>
        SOILEVAP_ROOT_CONSTRAIN,
        /// <summary>
        /// Simple HBV model (Bergstrom, 1996) -linear relation between ET and tension storage, with snow correction
        /// </summary>
        SOILEVAP_HBV,
        /// <summary>
        /// HYPR model with ponded area correction (Ahmed et al, 2020)
        /// </summary>
        SOILEVAP_HYPR,
        /// <summary>
        /// UBCWM Model (Quick, 1996)
        /// </summary>
        SOILEVAP_UBC,
        /// <summary>
        /// Ontario Crop Heat Unit method
        /// </summary>
        SOILEVAP_CHU,
        /// <summary>
        /// From Probabilty Distributed Model (Moore, 1985)
        /// </summary>
        SOILEVAP_PDM,
        /// <summary>
        /// Variant of Probability Distributed Model (Moore, 1985) used in HYMOD2 (Roy et al., 2017)
        /// </summary>
        SOILEVAP_HYMOD2,
        /// <summary>
        /// GR4J model approach (Perrin et al., 2003)
        /// </summary>
        SOILEVAP_GR4J,
        /// <summary>
        /// AET a linear function of soil moisture
        /// </summary>
        SOILEVAP_LINEAR,
        /// <summary>
        /// Sacramento Soil Moisture Accounting algorithm (should only be used with SOILBAL_SACSMA)
        /// </summary>
        SOILEVAP_SACSMA,
        /// <summary>
        /// Australia Water Balance Model of Boughton (1993)
        /// </summary>
        SOILEVAP_AWBM,
        /// <summary>
        /// AET==PET
        /// </summary>
        SOILEVAP_ALL
    }
}
