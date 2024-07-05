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
/**@file mip/HighsDebugSol.h
 * @brief Debug solution for MIP solver
 */

#ifndef HIGHS_DEBUG_SOL_H_
#define HIGHS_DEBUG_SOL_H_

class HighsDomain;
class HighsMipSolver;
class HighsLp;

#include <set>
#include <vector>

#include "mip/HighsCliqueTable.h"
#include "mip/HighsDomain.h"

#ifdef HIGHS_DEBUGSOL

#include <unordered_map>

struct HighsDebugSol {
  const HighsMipSolver* mipsolver;
  double debugSolObjective;
  std::vector<double> debugSolution;
  bool debugSolActive;
  std::unordered_map<const HighsDomain*, std::multiset<HighsDomainChange>>
      conflictingBounds;

  HIGHS_EXPORT HighsDebugSol(HighsMipSolver& mipsolver);

  HIGHS_EXPORT void newIncumbentFound();

  HIGHS_EXPORT void activate();

  HIGHS_EXPORT void shrink(const std::vector<HighsInt>& newColIndex);

  HIGHS_EXPORT void registerDomain(const HighsDomain& domain);

  HIGHS_EXPORT void boundChangeAdded(const HighsDomain& domain,
                        const HighsDomainChange& domchg,
                        bool branching = false);

  HIGHS_EXPORT void boundChangeRemoved(const HighsDomain& domain,
                          const HighsDomainChange& domchg);

  HIGHS_EXPORT void resetDomain(const HighsDomain& domain);

  HIGHS_EXPORT void nodePruned(const HighsDomain& localdomain);

  HIGHS_EXPORT void checkCut(const HighsInt* Rindex, const double* Rvalue, HighsInt Rlen,
                double rhs);

  HIGHS_EXPORT void checkRow(const HighsInt* Rindex, const double* Rvalue, HighsInt Rlen,
                double Rlower, double Rupper);

  HIGHS_EXPORT void checkRowAggregation(const HighsLp& lp, const HighsInt* Rindex,
                           const double* Rvalue, HighsInt Rlen);

  HIGHS_EXPORT void checkClique(const HighsCliqueTable::CliqueVar* clq, HighsInt clqlen);

  HIGHS_EXPORT void checkVub(HighsInt col, HighsInt vubcol, double vubcoef,
                double vubconstant) const;

  HIGHS_EXPORT void checkVlb(HighsInt col, HighsInt vlbcol, double vlbcoef,
                double vlbconstant) const;

  HIGHS_EXPORT void checkConflictReasonFrontier(
      const std::set<HighsDomain::ConflictSet::LocalDomChg>& reasonSideFrontier,
      const std::vector<HighsDomainChange>& domchgstack) const;

  HIGHS_EXPORT void checkConflictReconvergenceFrontier(
      const std::set<HighsDomain::ConflictSet::LocalDomChg>&
          reconvergenceFrontier,
      const HighsDomain::ConflictSet::LocalDomChg& reconvDomchgPos,
      const std::vector<HighsDomainChange>& domchgstack) const;
};

#else
struct HighsDebugSol {
  HighsDebugSol(HighsMipSolver&) {}

  void newIncumbentFound() const {}

  void activate() const {}

  void shrink(const std::vector<HighsInt>&) const {}

  void registerDomain(const HighsDomain&) const {}

  void boundChangeAdded(const HighsDomain&, const HighsDomainChange&,
                        bool = false) const {}

  void boundChangeRemoved(const HighsDomain&, const HighsDomainChange&) const {}

  void resetDomain(const HighsDomain&) const {}

  void nodePruned(const HighsDomain&) const {}

  void checkCut(const HighsInt*, const double*, HighsInt, double) const {}

  void checkRow(const HighsInt*, const double*, HighsInt, double,
                double) const {}

  void checkRowAggregation(const HighsLp&, const HighsInt*, const double*,
                           HighsInt) const {}

  void checkClique(const HighsCliqueTable::CliqueVar*, HighsInt) const {}

  void checkVub(HighsInt, HighsInt, double, double) const {}

  void checkVlb(HighsInt, HighsInt, double, double) const {}

  void checkConflictReasonFrontier(
      const std::set<HighsDomain::ConflictSet::LocalDomChg>&,
      const std::vector<HighsDomainChange>&) const {}

  void checkConflictReconvergenceFrontier(
      const std::set<HighsDomain::ConflictSet::LocalDomChg>&,
      const HighsDomain::ConflictSet::LocalDomChg&,
      const std::vector<HighsDomainChange>&) const {}
};
#endif

#endif
