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
    public enum DiagType
    {
        DIAG_NASH_SUTCLIFFE,
        DIAG_DAILY_NSE,
        DIAG_NASH_SUTCLIFFE_DER,
        DIAG_NASH_SUTCLIFFE_RUN,
        DIAG_LOG_NASH,
        DIAG_NSE4,
        DIAG_FUZZY_NASH,
        DIAG_RMSE,
        DIAG_RMSE_DER,
        DIAG_KLING_GUPTA,
        DIAG_KGE_PRIME,
        DIAG_DAILY_KGE,
        DIAG_KLING_GUPTA_DER,
        DIAG_KLING_GUPTA_DEVIATION,
        DIAG_PCT_BIAS,
        DIAG_ABS_PCT_BIAS,
        DIAG_ABSERR,
        DIAG_ABSERR_RUN,
        DIAG_ABSMAX,
        DIAG_PDIFF,
        DIAG_PCT_PDIFF,
        DIAG_ABS_PCT_PDIFF,
        DIAG_TMVOL,
        DIAG_RCOEF,
        DIAG_NSC,
        DIAG_RSR,
        DIAG_R2,
        DIAG_MBF,
        DIAG_R4MS4E,
        DIAG_RTRMSE,
        DIAG_RABSERR,
        DIAG_PERSINDEX,
        DIAG_YEARS_OF_RECORD,
        DIAG_SPEARMAN,
        DIAG_UNRECOGNIZED
    };


}
