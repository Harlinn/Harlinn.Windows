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
/**@file simplex/HEkkPrimal.h
 * @brief Phase 2 primal simplex solver for HiGHS
 */
#ifndef SIMPLEX_HEKKPRIMAL_H_
#define SIMPLEX_HEKKPRIMAL_H_

#include <utility>

#include "simplex/HEkk.h"
#include "util/HSet.h"

using std::pair;

const SimplexAlgorithm algorithm = SimplexAlgorithm::kPrimal;

/**
 * @brief Primal simplex solver for HiGHS
 */

class HEkkPrimal {
 public:
  HEkkPrimal(HEkk& simplex) : ekk_instance_(simplex) { initialiseInstance(); }
  /**
   * @brief Solve a model instance
   */
  HIGHS_EXPORT HighsStatus solve(const bool force_phase2 = false);

 private:
  /**
   * @brief Initialise a primal simplex instance
   */
  HIGHS_EXPORT void initialiseInstance();
  /**
   * @brief Initialise a primal simplex solve
   */
  HIGHS_EXPORT void initialiseSolve();
  HIGHS_EXPORT void solvePhase1();
  HIGHS_EXPORT void solvePhase2();
  HIGHS_EXPORT void cleanup();
  HIGHS_EXPORT void rebuild();

  HIGHS_EXPORT void iterate();
  HIGHS_EXPORT void chuzc();
  HIGHS_EXPORT void chooseColumn(const bool hyper_sparse = false);
  HIGHS_EXPORT bool useVariableIn();
  HIGHS_EXPORT void phase1ChooseRow();
  HIGHS_EXPORT void chooseRow();

  HIGHS_EXPORT void considerBoundSwap();
  HIGHS_EXPORT void assessPivot();

  HIGHS_EXPORT void update();

  HIGHS_EXPORT void updateDual();

  HIGHS_EXPORT void hyperChooseColumn();
  HIGHS_EXPORT void hyperChooseColumnStart();
  HIGHS_EXPORT void hyperChooseColumnClear();
  HIGHS_EXPORT void hyperChooseColumnChangedInfeasibility(const double infeasibility,
                                             const HighsInt iCol);
  HIGHS_EXPORT void hyperChooseColumnBasicFeasibilityChange();
  HIGHS_EXPORT void hyperChooseColumnDualChange();

  HIGHS_EXPORT void phase1ComputeDual();
  HIGHS_EXPORT void phase1UpdatePrimal();
  HIGHS_EXPORT void basicFeasibilityChangeBtran();
  HIGHS_EXPORT void basicFeasibilityChangePrice();
  HIGHS_EXPORT void basicFeasibilityChangeUpdateDual();

  HIGHS_EXPORT void phase2UpdatePrimal(const bool initialise = false);

  HIGHS_EXPORT void considerInfeasibleValueIn();

  HIGHS_EXPORT void initialiseDevexFramework();
  HIGHS_EXPORT void updateDevex();
  HIGHS_EXPORT void computePrimalSteepestEdgeWeights();
  HIGHS_EXPORT double computePrimalSteepestEdgeWeight(const HighsInt iVar,
                                         HVector& local_col_aq);
  HIGHS_EXPORT void updatePrimalSteepestEdgeWeights();
  HIGHS_EXPORT void updateDualSteepestEdgeWeights();
  HIGHS_EXPORT void updateFtranDSE(HVector& col_steepest_edge);
  HIGHS_EXPORT void updateBtranPSE(HVector& col_steepest_edge);

  HIGHS_EXPORT void updateVerify();

  HIGHS_EXPORT void iterationAnalysisData();
  HIGHS_EXPORT void iterationAnalysis();
  HIGHS_EXPORT void localReportIterHeader();
  HIGHS_EXPORT void localReportIter(const bool header = false);
  HIGHS_EXPORT void reportRebuild(const HighsInt reason_for_rebuild = -1);
  HIGHS_EXPORT void getNonbasicFreeColumnSet();
  HIGHS_EXPORT void removeNonbasicFreeColumn();
  HIGHS_EXPORT void adjustPerturbedEquationOut();
  HIGHS_EXPORT void getBasicPrimalInfeasibility();
  HIGHS_EXPORT bool correctPrimal(const bool initialise = false);
  HIGHS_EXPORT void shiftBound(const bool lower, const HighsInt iVar, const double value,
                  const double random_value, double& bound, double& shift,
                  const bool report = false);
  HIGHS_EXPORT void savePrimalRay();
  HIGHS_EXPORT HighsDebugStatus debugPrimalSimplex(const std::string message,
                                      const bool initialise = false);
  HIGHS_EXPORT HighsDebugStatus debugPrimalSteepestEdgeWeights(const std::string message);
  HIGHS_EXPORT HighsDebugStatus debugPrimalSteepestEdgeWeights(
      const HighsInt alt_debug_level = -1);

  HIGHS_EXPORT bool isBadBasisChange();

  // References:
  HEkk& ekk_instance_;

  // Pointers:
  HighsSimplexAnalysis* analysis;

  // Class data members
  HighsInt num_col;
  HighsInt num_row;
  HighsInt num_tot;
  HighsInt solve_phase;
  EdgeWeightMode edge_weight_mode;
  double primal_feasibility_tolerance;
  double dual_feasibility_tolerance;
  double objective_target;
  HighsInt rebuild_reason;
  // Pivot related
  HighsInt variable_in;
  HighsInt move_in;
  HighsInt row_out;
  HighsInt variable_out;
  HighsInt move_out;
  double theta_dual;
  double theta_primal;
  double value_in;
  double alpha_col;
  double alpha_row;
  double numericalTrouble;

  HighsInt num_flip_since_rebuild;
  // Primal phase 1 tools
  vector<pair<double, int> > ph1SorterR;
  vector<pair<double, int> > ph1SorterT;
  // Edge weights
  // Edge weight
  vector<double> edge_weight_;
  HighsInt num_devex_iterations_;
  HighsInt num_bad_devex_weight_;
  vector<HighsInt> devex_index_;
  // Nonbasic free column data.
  HighsInt num_free_col;
  HSet nonbasic_free_col_set;
  // Hyper-sparse CHUZC data
  bool use_hyper_chuzc = false;
  bool initialise_hyper_chuzc;
  bool done_next_chuzc;
  const HighsInt max_num_hyper_chuzc_candidates = 50;
  HighsInt num_hyper_chuzc_candidates;
  vector<HighsInt> hyper_chuzc_candidate;
  vector<double> hyper_chuzc_measure;
  HSet hyper_chuzc_candidate_set;
  double max_hyper_chuzc_non_candidate_measure;
  double max_changed_measure_value;
  HighsInt max_changed_measure_column;
  const bool report_hyper_chuzc = false;
  // Solve buffer
  HVector row_ep;
  HVector row_ap;
  HVector col_aq;
  HVector col_basic_feasibility_change;
  HVector row_basic_feasibility_change;
  HVector col_steepest_edge;
  HighsRandom random_;  // Just for checking PSE weights

  double max_max_local_primal_infeasibility_;
  double max_max_ignored_violation_;
  double max_max_primal_correction_;
  HighsInt last_header_iteration_count_;

  const HighsInt primal_correction_strategy =
      kSimplexPrimalCorrectionStrategyAlways;
  double debug_max_relative_primal_steepest_edge_weight_error = 0;

  const HighsInt check_iter = 9999999;
  const HighsInt check_column = -2133;
};

#endif /* SIMPLEX_HEKKPRIMAL_H_ */
