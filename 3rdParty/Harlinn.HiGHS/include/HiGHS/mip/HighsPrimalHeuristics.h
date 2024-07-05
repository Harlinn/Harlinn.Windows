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
#ifndef HIGHS_PRIMAL_HEURISTICS_H_
#define HIGHS_PRIMAL_HEURISTICS_H_

#include <vector>

#include "lp_data/HStruct.h"
#include "lp_data/HighsLp.h"
#include "util/HighsRandom.h"

class HighsMipSolver;

class HighsPrimalHeuristics {
 private:
  HighsMipSolver& mipsolver;
  size_t lp_iterations;

  double successObservations;
  HighsInt numSuccessObservations;
  double infeasObservations;
  HighsInt numInfeasObservations;

  HighsRandom randgen;

  std::vector<HighsInt> intcols;

 public:
  HIGHS_EXPORT HighsPrimalHeuristics(HighsMipSolver& mipsolver);

  HIGHS_EXPORT void setupIntCols();

  HIGHS_EXPORT bool solveSubMip(const HighsLp& lp, const HighsBasis& basis,
                   double fixingRate, std::vector<double> colLower,
                   std::vector<double> colUpper, HighsInt maxleaves,
                   HighsInt maxnodes, HighsInt stallnodes);

  HIGHS_EXPORT double determineTargetFixingRate();

  HIGHS_EXPORT void rootReducedCost();

  HIGHS_EXPORT void RENS(const std::vector<double>& relaxationsol);

  HIGHS_EXPORT void RINS(const std::vector<double>& relaxationsol);

  HIGHS_EXPORT void feasibilityPump();

  HIGHS_EXPORT void centralRounding();

  HIGHS_EXPORT void flushStatistics();

  HIGHS_EXPORT bool tryRoundedPoint(const std::vector<double>& point, char source);

  HIGHS_EXPORT bool linesearchRounding(const std::vector<double>& point1,
                          const std::vector<double>& point2, char source);

  HIGHS_EXPORT void randomizedRounding(const std::vector<double>& relaxationsol);
};

#endif
