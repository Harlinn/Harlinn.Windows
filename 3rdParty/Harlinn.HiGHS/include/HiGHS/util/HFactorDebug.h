/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Written and engineered 2008-2024 by Julian Hall, Ivet Galabova,    */
/*    Leona Gottwald and Michael Feldmeier                               */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**@file util/HFactorDebug.h
 * @brief
 */
#ifndef UTIL_HFACTORDEBUG_H_
#define UTIL_HFACTORDEBUG_H_

#include <vector>

#include "lp_data/HighsOptions.h"

using std::vector;

HIGHS_EXPORT void debugReportRankDeficiency(
    const HighsInt call_id, const HighsInt highs_debug_level,
    const HighsLogOptions& log_options, const HighsInt num_row,
    const vector<HighsInt>& permute, const vector<HighsInt>& iwork,
    const HighsInt* basic_index, const HighsInt rank_deficiency,
    const vector<HighsInt>& row_with_no_pivot,
    const vector<HighsInt>& col_with_no_pivot);

HIGHS_EXPORT void debugReportRankDeficientASM(
    const HighsInt highs_debug_level, const HighsLogOptions& log_options,
    const HighsInt num_row, const vector<HighsInt>& mc_start,
    const vector<HighsInt>& mc_count_a, const vector<HighsInt>& mc_index,
    const vector<double>& mc_value, const vector<HighsInt>& iwork,
    const HighsInt rank_deficiency, const vector<HighsInt>& col_with_no_pivot,
    const vector<HighsInt>& row_with_no_pivot);

HIGHS_EXPORT void debugReportMarkSingC(const HighsInt call_id,
                          const HighsInt highs_debug_level,
                          const HighsLogOptions& log_options,
                          const HighsInt num_row, const vector<HighsInt>& iwork,
                          const HighsInt* basic_index);

HIGHS_EXPORT void debugLogRankDeficiency(const HighsInt highs_debug_level,
                            const HighsLogOptions& log_options,
                            const HighsInt rank_deficiency,
                            const HighsInt basis_matrix_num_el,
                            const HighsInt invert_num_el,
                            const HighsInt& kernel_dim,
                            const HighsInt kernel_num_el, const HighsInt nwork);

HIGHS_EXPORT void debugPivotValueAnalysis(const HighsInt highs_debug_level,
                             const HighsLogOptions& log_options,
                             const HighsInt num_row,
                             const vector<double>& u_pivot_value);

#endif  // UTIL_HFACTORDEBUG_H_
