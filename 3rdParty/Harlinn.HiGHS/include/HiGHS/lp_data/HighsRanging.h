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
/**@file lp_data/HighsRanging.h
 * @brief
 */
#ifndef LP_DATA_HIGHS_RANGING_H_
#define LP_DATA_HIGHS_RANGING_H_

#include <vector>

#include "lp_data/HighsLpSolverObject.h"

struct HighsRangingRecord {
  std::vector<double> value_;
  std::vector<double> objective_;
  std::vector<HighsInt> in_var_;
  std::vector<HighsInt> ou_var_;
};

struct HighsRanging {
  bool valid = false;
  HighsRangingRecord col_cost_up;
  HighsRangingRecord col_cost_dn;
  HighsRangingRecord col_bound_up;
  HighsRangingRecord col_bound_dn;
  HighsRangingRecord row_bound_up;
  HighsRangingRecord row_bound_dn;
  HIGHS_EXPORT void invalidate();
  HIGHS_EXPORT void clear();
};

HIGHS_EXPORT HighsStatus getRangingData(HighsRanging& ranging,
                           HighsLpSolverObject& solver_object);
HIGHS_EXPORT void writeRangingFile(FILE* file, const HighsLp& lp,
                      const double objective_function_value,
                      const HighsBasis& basis, const HighsSolution& solution,
                      const HighsRanging& ranging, const HighsInt style);
#endif
