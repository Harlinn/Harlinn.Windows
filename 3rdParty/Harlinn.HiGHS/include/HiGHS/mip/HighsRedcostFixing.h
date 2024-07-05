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
/**@file mip/HighsRedcostFixing.h
 * @brief reduced cost fixing using the current cutoff bound
 */

#ifndef HIGHS_REDCOST_FIXING_H_
#define HIGHS_REDCOST_FIXING_H_

#include <map>
#include <vector>

#include "mip/HighsDomainChange.h"

class HighsDomain;
class HighsMipSolver;
class HighsLpRelaxation;

class HighsRedcostFixing {
  std::vector<std::multimap<double, int>> lurkingColUpper;
  std::vector<std::multimap<double, int>> lurkingColLower;

 public:
  HIGHS_EXPORT std::vector<std::pair<double, HighsDomainChange>> getLurkingBounds(
      const HighsMipSolver& mipsolver) const;

  HIGHS_EXPORT void propagateRootRedcost(const HighsMipSolver& mipsolver);

  HIGHS_EXPORT static void propagateRedCost(const HighsMipSolver& mipsolver,
                               HighsDomain& localdomain,
                               const HighsLpRelaxation& lp);

  HIGHS_EXPORT void addRootRedcost(const HighsMipSolver& mipsolver,
                      const std::vector<double>& lpredcost, double lpobjective);
};

#endif
