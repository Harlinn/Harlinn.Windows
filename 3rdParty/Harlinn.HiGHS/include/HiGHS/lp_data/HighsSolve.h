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
/**@file lp_data/HighsSolve.h
 * @brief Class-independent utilities for HiGHS
 */
#ifndef LP_DATA_HIGHSSOLVE_H_
#define LP_DATA_HIGHSSOLVE_H_

#include "lp_data/HighsModelUtils.h"
HIGHS_EXPORT HighsStatus solveLp(HighsLpSolverObject& solver_object, const string message);
HIGHS_EXPORT HighsStatus solveUnconstrainedLp(HighsLpSolverObject& solver_object);
HIGHS_EXPORT HighsStatus solveUnconstrainedLp(const HighsOptions& options, const HighsLp& lp,
                                 HighsModelStatus& model_status,
                                 HighsInfo& highs_info, HighsSolution& solution,
                                 HighsBasis& basis);
HIGHS_EXPORT void assessExcessiveBoundCost(const HighsLogOptions log_options,
                              const HighsModel& model);
#endif  // LP_DATA_HIGHSSOLVE_H_
