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

#ifndef HIGHS_MIP_SOLVER_DATA_H_
#define HIGHS_MIP_SOLVER_DATA_H_

#include <vector>

#include "mip/HighsCliqueTable.h"
#include "mip/HighsConflictPool.h"
#include "mip/HighsCutPool.h"
#include "mip/HighsDebugSol.h"
#include "mip/HighsDomain.h"
#include "mip/HighsImplications.h"
#include "mip/HighsLpRelaxation.h"
#include "mip/HighsNodeQueue.h"
#include "mip/HighsObjectiveFunction.h"
#include "mip/HighsPrimalHeuristics.h"
#include "mip/HighsPseudocost.h"
#include "mip/HighsRedcostFixing.h"
#include "mip/HighsSearch.h"
#include "mip/HighsSeparation.h"
#include "parallel/HighsParallel.h"
#include "presolve/HighsPostsolveStack.h"
#include "presolve/HighsSymmetry.h"
#include "util/HighsTimer.h"

struct HighsMipSolverData {
  HighsMipSolver& mipsolver;
  HighsCutPool cutpool;
  HighsConflictPool conflictPool;
  HighsDomain domain;
  HighsLpRelaxation lp;
  HighsPseudocost pseudocost;
  HighsCliqueTable cliquetable;
  HighsImplications implications;
  HighsPrimalHeuristics heuristics;
  HighsRedcostFixing redcostfixing;
  HighsObjectiveFunction objectiveFunction;
  presolve::HighsPostsolveStack postSolveStack;
  HighsPresolveStatus presolve_status;
  HighsLp presolvedModel;
  bool cliquesExtracted;
  bool rowMatrixSet;
  bool analyticCenterComputed;
  HighsModelStatus analyticCenterStatus;
  bool detectSymmetries;
  HighsInt numRestarts;
  HighsInt numRestartsRoot;
  HighsInt numCliqueEntriesAfterPresolve;
  HighsInt numCliqueEntriesAfterFirstPresolve;

  std::vector<HighsInt> ARstart_;
  std::vector<HighsInt> ARindex_;
  std::vector<double> ARvalue_;
  std::vector<double> maxAbsRowCoef;
  std::vector<uint8_t> rowintegral;
  std::vector<HighsInt> uplocks;
  std::vector<HighsInt> downlocks;
  std::vector<HighsInt> integer_cols;
  std::vector<HighsInt> implint_cols;
  std::vector<HighsInt> integral_cols;
  std::vector<HighsInt> continuous_cols;

  HighsSymmetries symmetries;
  std::shared_ptr<const StabilizerOrbits> globalOrbits;

  double feastol;
  double epsilon;
  double heuristic_effort;
  int64_t dispfreq;
  std::vector<double> analyticCenter;
  std::vector<double> firstlpsol;
  std::vector<double> rootlpsol;
  double firstlpsolobj;
  HighsBasis firstrootbasis;
  double rootlpsolobj;
  HighsInt numintegercols;
  HighsInt maxTreeSizeLog2;

  HighsCDouble pruned_treeweight;
  double avgrootlpiters;
  double last_disptime;
  int64_t firstrootlpiters;
  int64_t num_nodes;
  int64_t num_leaves;
  int64_t num_leaves_before_run;
  int64_t num_nodes_before_run;
  int64_t total_lp_iterations;
  int64_t heuristic_lp_iterations;
  int64_t sepa_lp_iterations;
  int64_t sb_lp_iterations;
  int64_t total_lp_iterations_before_run;
  int64_t heuristic_lp_iterations_before_run;
  int64_t sepa_lp_iterations_before_run;
  int64_t sb_lp_iterations_before_run;
  int64_t num_disp_lines;

  HighsInt numImprovingSols;
  double lower_bound;
  double upper_bound;
  double upper_limit;
  double optimality_limit;
  std::vector<double> incumbent;

  HighsNodeQueue nodequeue;

  HighsDebugSol debugSolution;

  HighsMipSolverData(HighsMipSolver& mipsolver)
      : mipsolver(mipsolver),
        cutpool(mipsolver.numCol(), mipsolver.options_mip_->mip_pool_age_limit,
                mipsolver.options_mip_->mip_pool_soft_limit),
        conflictPool(5 * mipsolver.options_mip_->mip_pool_age_limit,
                     mipsolver.options_mip_->mip_pool_soft_limit),
        domain(mipsolver),
        lp(mipsolver),
        pseudocost(),
        cliquetable(mipsolver.numCol()),
        implications(mipsolver),
        heuristics(mipsolver),
        objectiveFunction(mipsolver),
        presolve_status(HighsPresolveStatus::kNotSet),
        cliquesExtracted(false),
        rowMatrixSet(false),
        analyticCenterComputed(false),
        analyticCenterStatus(HighsModelStatus::kNotset),
        detectSymmetries(false),
        numRestarts(0),
        numRestartsRoot(0),
        numCliqueEntriesAfterPresolve(0),
        numCliqueEntriesAfterFirstPresolve(0),
        feastol(0.0),
        epsilon(0.0),
        heuristic_effort(0.0),
        dispfreq(0),
        firstlpsolobj(-kHighsInf),
        rootlpsolobj(-kHighsInf),
        numintegercols(0),
        maxTreeSizeLog2(0),
        pruned_treeweight(0),
        avgrootlpiters(0.0),
        last_disptime(0.0),
        firstrootlpiters(0),
        num_nodes(0),
        num_leaves(0),
        num_leaves_before_run(0),
        num_nodes_before_run(0),
        total_lp_iterations(0),
        heuristic_lp_iterations(0),
        sepa_lp_iterations(0),
        sb_lp_iterations(0),
        total_lp_iterations_before_run(0),
        heuristic_lp_iterations_before_run(0),
        sepa_lp_iterations_before_run(0),
        sb_lp_iterations_before_run(0),
        num_disp_lines(0),
        numImprovingSols(0),
        lower_bound(-kHighsInf),
        upper_bound(kHighsInf),
        upper_limit(kHighsInf),
        optimality_limit(kHighsInf),
        debugSolution(mipsolver) {
    domain.addCutpool(cutpool);
    domain.addConflictPool(conflictPool);
  }

  HIGHS_EXPORT void startAnalyticCenterComputation(
      const highs::parallel::TaskGroup& taskGroup);
  HIGHS_EXPORT void finishAnalyticCenterComputation(
      const highs::parallel::TaskGroup& taskGroup);

  struct SymmetryDetectionData {
    HighsSymmetryDetection symDetection;
    HighsSymmetries symmetries;
    double detectionTime = 0.0;
  };

  HIGHS_EXPORT void startSymmetryDetection(const highs::parallel::TaskGroup& taskGroup,
                              std::unique_ptr<SymmetryDetectionData>& symData);
  HIGHS_EXPORT void finishSymmetryDetection(const highs::parallel::TaskGroup& taskGroup,
                               std::unique_ptr<SymmetryDetectionData>& symData);

  HIGHS_EXPORT double computeNewUpperLimit(double upper_bound, double mip_abs_gap,
                              double mip_rel_gap) const;
  HIGHS_EXPORT bool moreHeuristicsAllowed() const;
  HIGHS_EXPORT void removeFixedIndices();
  HIGHS_EXPORT void init();
  HIGHS_EXPORT void basisTransfer();
  HIGHS_EXPORT void checkObjIntegrality();
  HIGHS_EXPORT void runPresolve(const HighsInt presolve_reduction_limit);
  HIGHS_EXPORT void setupDomainPropagation();
  HIGHS_EXPORT void saveReportMipSolution(const double new_upper_limit = -kHighsInf);
  HIGHS_EXPORT void runSetup();
  HIGHS_EXPORT double transformNewIntegerFeasibleSolution(
      const std::vector<double>& sol,
      const bool possibly_store_as_new_incumbent = true);
  HIGHS_EXPORT double percentageInactiveIntegers() const;
  HIGHS_EXPORT void performRestart();
  HIGHS_EXPORT bool checkSolution(const std::vector<double>& solution) const;
  HIGHS_EXPORT bool trySolution(const std::vector<double>& solution, char source = ' ');
  HIGHS_EXPORT bool rootSeparationRound(HighsSeparation& sepa, HighsInt& ncuts,
                           HighsLpRelaxation::Status& status);
  HIGHS_EXPORT HighsLpRelaxation::Status evaluateRootLp();
  HIGHS_EXPORT void evaluateRootNode();
  HIGHS_EXPORT bool addIncumbent(const std::vector<double>& sol, double solobj, char source);

  HIGHS_EXPORT const std::vector<double>& getSolution() const;

  HIGHS_EXPORT void printDisplayLine(char first = ' ');

  void getRow(HighsInt row, HighsInt& rowlen, const HighsInt*& rowinds,
              const double*& rowvals) const {
    HighsInt start = ARstart_[row];
    rowlen = ARstart_[row + 1] - start;
    rowinds = ARindex_.data() + start;
    rowvals = ARvalue_.data() + start;
  }

  HIGHS_EXPORT bool checkLimits(int64_t nodeOffset = 0) const;
  HIGHS_EXPORT void limitsToBounds(double& dual_bound, double& primal_bound,
                      double& mip_rel_gap) const;
  HIGHS_EXPORT bool interruptFromCallbackWithData(const int callback_type,
                                     const double mipsolver_objective_value,
                                     const std::string message = "") const;
};

#endif
