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
/**@file simplex/HEkk.h
 * @brief Primal simplex solver for HiGHS
 */
#ifndef SIMPLEX_HEKK_H_
#define SIMPLEX_HEKK_H_

#include "lp_data/HighsCallback.h"
#include "simplex/HSimplexNla.h"
#include "simplex/HighsSimplexAnalysis.h"
#include "util/HSet.h"
#include "util/HighsHash.h"
#include "util/HighsRandom.h"

class HighsLpSolverObject;

class HEkk {
 public:
  HEkk()
      : callback_(nullptr),
        options_(nullptr),
        timer_(nullptr),
        lp_name_(""),
        model_status_(HighsModelStatus::kNotset),
        simplex_in_scaled_space_(false),
        cost_scale_(1.0),
        cost_perturbation_base_(0.0),
        cost_perturbation_max_abs_cost_(0.0),
        iteration_count_(0),
        dual_simplex_cleanup_level_(0),
        dual_simplex_phase1_cleanup_level_(0),
        previous_iteration_cycling_detected(-kHighsIInf),
        solve_bailout_(false),
        called_return_from_solve_(false),
        exit_algorithm_(SimplexAlgorithm::kNone),
        return_primal_solution_status_(0),
        return_dual_solution_status_(0),
        original_num_col_(0),
        original_num_row_(0),
        original_num_nz_(0),
        original_offset_(0.0),
        edge_weight_error_(0.0),
        build_synthetic_tick_(0.0),
        total_synthetic_tick_(0.0),
        debug_solve_call_num_(0),
        debug_basis_id_(0),
        time_report_(false),
        debug_initial_build_synthetic_tick_(0),
        debug_solve_report_(false),
        debug_iteration_report_(false),
        debug_basis_report_(false),
        debug_dual_feasible(false),
        debug_max_relative_dual_steepest_edge_weight_error(0) {}
  /**
   * @brief Interface to simplex solvers
   */
  HIGHS_EXPORT void clear();
  HIGHS_EXPORT void clearEkkLp();
  HIGHS_EXPORT void clearEkkData();
  HIGHS_EXPORT void clearEkkDualize();
  HIGHS_EXPORT void clearEkkDualEdgeWeightData();
  HIGHS_EXPORT void clearEkkPointers();
  HIGHS_EXPORT void clearEkkDataInfo();
  HIGHS_EXPORT void clearEkkControlInfo();
  HIGHS_EXPORT void clearEkkNlaInfo();
  HIGHS_EXPORT void clearEkkAllStatus();
  HIGHS_EXPORT void clearEkkDataStatus();
  HIGHS_EXPORT void clearNlaStatus();
  HIGHS_EXPORT void clearNlaInvertStatus();

  HIGHS_EXPORT void invalidate();
  HIGHS_EXPORT void invalidateBasisMatrix();
  HIGHS_EXPORT void invalidateBasis();
  HIGHS_EXPORT void invalidateBasisArtifacts();

  HIGHS_EXPORT void updateStatus(LpAction action);
  HIGHS_EXPORT void setNlaPointersForLpAndScale(const HighsLp& lp);
  HIGHS_EXPORT void setNlaPointersForTrans(const HighsLp& lp);
  HIGHS_EXPORT void setNlaRefactorInfo();
  HIGHS_EXPORT void clearHotStart();
  HIGHS_EXPORT void btran(HVector& rhs, const double expected_density);
  HIGHS_EXPORT void ftran(HVector& rhs, const double expected_density);

  HIGHS_EXPORT void moveLp(HighsLpSolverObject& solver_object);
  HIGHS_EXPORT void setPointers(HighsCallback* callback, HighsOptions* options,
                   HighsTimer* timer);
  HIGHS_EXPORT HighsSparseMatrix* getScaledAMatrixPointer();
  HIGHS_EXPORT HighsScale* getScalePointer();

  HIGHS_EXPORT void initialiseEkk();
  HIGHS_EXPORT HighsStatus dualize();
  HIGHS_EXPORT HighsStatus undualize();
  HIGHS_EXPORT HighsStatus permute();
  HIGHS_EXPORT HighsStatus unpermute();
  HIGHS_EXPORT HighsStatus solve(const bool force_phase2 = false);
  HIGHS_EXPORT HighsStatus setBasis();
  HIGHS_EXPORT HighsStatus setBasis(const HighsBasis& highs_basis);

  HIGHS_EXPORT void freezeBasis(HighsInt& frozen_basis_id);
  HIGHS_EXPORT HighsStatus unfreezeBasis(const HighsInt frozen_basis_id);
  HIGHS_EXPORT HighsStatus frozenBasisAllDataClear();

  HIGHS_EXPORT void putIterate();
  HIGHS_EXPORT HighsStatus getIterate();

  HIGHS_EXPORT void addCols(const HighsLp& lp, const HighsSparseMatrix& scaled_a_matrix);
  HIGHS_EXPORT void addRows(const HighsLp& lp, const HighsSparseMatrix& scaled_ar_matrix);
  HIGHS_EXPORT void deleteCols(const HighsIndexCollection& index_collection);
  HIGHS_EXPORT void deleteRows(const HighsIndexCollection& index_collection);
  HIGHS_EXPORT void unscaleSimplex(const HighsLp& incumbent_lp);
  HIGHS_EXPORT double factorSolveError();

  HIGHS_EXPORT bool proofOfPrimalInfeasibility();
  HIGHS_EXPORT bool proofOfPrimalInfeasibility(HVector& row_ep, const HighsInt move_out,
                                  const HighsInt row_out);

  HIGHS_EXPORT double getValueScale(const HighsInt count, const vector<double>& value);
  HIGHS_EXPORT double getMaxAbsRowValue(HighsInt row);

  HIGHS_EXPORT void unitBtranIterativeRefinement(const HighsInt row_out, HVector& row_ep);
  HIGHS_EXPORT void unitBtranResidual(const HighsInt row_out, const HVector& row_ep,
                         HVector& residual, double& residual_norm);

  HIGHS_EXPORT HighsSolution getSolution();
  HIGHS_EXPORT HighsBasis getHighsBasis(HighsLp& use_lp) const;

  const SimplexBasis& getSimplexBasis() { return basis_; }

  HIGHS_EXPORT HighsStatus initialiseSimplexLpBasisAndFactor(
      const bool only_from_known_basis = false);
  HIGHS_EXPORT void handleRankDeficiency();
  HIGHS_EXPORT void initialisePartitionedRowwiseMatrix();
  HIGHS_EXPORT bool lpFactorRowCompatible();
  HIGHS_EXPORT bool lpFactorRowCompatible(HighsInt expectedNumRow);

  // Interface methods
  HIGHS_EXPORT void appendColsToVectors(const HighsInt num_new_col,
                           const vector<double>& colCost,
                           const vector<double>& colLower,
                           const vector<double>& colUpper);
  HIGHS_EXPORT void appendRowsToVectors(const HighsInt num_new_row,
                           const vector<double>& rowLower,
                           const vector<double>& rowUpper);

  // Make this private later
  HIGHS_EXPORT void chooseSimplexStrategyThreads(const HighsOptions& options,
                                    HighsSimplexInfo& info);
  // Debug methods
  HIGHS_EXPORT void debugInitialise();
  HIGHS_EXPORT void debugReportInitialBasis();
  HIGHS_EXPORT void debugReporting(
      const HighsInt save_mod_recover,
      const HighsInt log_dev_level_ = kHighsLogDevLevelDetailed);
  HIGHS_EXPORT void timeReporting(const HighsInt save_mod_recover);
  HIGHS_EXPORT HighsDebugStatus debugRetainedDataOk(const HighsLp& lp) const;
  HIGHS_EXPORT HighsDebugStatus debugNlaCheckInvert(
      const std::string message, const HighsInt alt_debug_level = -1) const;
  HIGHS_EXPORT bool debugNlaScalingOk(const HighsLp& lp) const;

  // Data members
  HighsCallback* callback_;
  HighsOptions* options_;
  HighsTimer* timer_;
  HighsSimplexAnalysis analysis_;

  HighsLp lp_;
  std::string lp_name_;
  HighsSimplexStatus status_;
  HighsSimplexInfo info_;
  HighsModelStatus model_status_;
  SimplexBasis basis_;
  HighsHashTable<uint64_t> visited_basis_;
  HighsRandom random_;
  std::vector<double> dual_edge_weight_;
  std::vector<double> scattered_dual_edge_weight_;

  bool simplex_in_scaled_space_;
  HighsSparseMatrix ar_matrix_;
  HighsSparseMatrix scaled_a_matrix_;
  HSimplexNla simplex_nla_;
  HotStart hot_start_;

  double cost_scale_;
  double cost_perturbation_base_;
  double cost_perturbation_max_abs_cost_;
  HighsInt iteration_count_;
  HighsInt dual_simplex_cleanup_level_;
  HighsInt dual_simplex_phase1_cleanup_level_;

  HighsInt previous_iteration_cycling_detected;

  bool solve_bailout_;
  bool called_return_from_solve_;
  SimplexAlgorithm exit_algorithm_;
  HighsInt return_primal_solution_status_;
  HighsInt return_dual_solution_status_;

  // Data to be retained after proving primal infeasibility
  vector<HighsInt> proof_index_;
  vector<double> proof_value_;

  // Data to be retained when dualizing
  HighsInt original_num_col_;
  HighsInt original_num_row_;
  HighsInt original_num_nz_;
  double original_offset_;
  vector<double> original_col_cost_;
  vector<double> original_col_lower_;
  vector<double> original_col_upper_;
  vector<double> original_row_lower_;
  vector<double> original_row_upper_;
  //
  // The upper_bound_col vector accumulates the indices of boxed
  // variables, whose upper bounds are treated as additional
  // constraints.
  //
  // The upper_bound_row vector accumulates the indices of boxed
  // constraints, whose upper bounds are treated as additional
  // constraints.
  vector<HighsInt> upper_bound_col_;
  vector<HighsInt> upper_bound_row_;

  double edge_weight_error_;

  double build_synthetic_tick_;
  double total_synthetic_tick_;
  HighsInt debug_solve_call_num_;
  HighsInt debug_basis_id_;
  bool time_report_;
  HighsInt debug_initial_build_synthetic_tick_;
  bool debug_solve_report_;
  bool debug_iteration_report_;
  bool debug_basis_report_;
  bool debug_dual_feasible;
  double debug_max_relative_dual_steepest_edge_weight_error;

  std::vector<HighsSimplexBadBasisChangeRecord> bad_basis_change_;

 private:
  HIGHS_EXPORT bool isUnconstrainedLp();
  HIGHS_EXPORT void initialiseForSolve();
  HIGHS_EXPORT void setSimplexOptions();
  HIGHS_EXPORT void updateSimplexOptions();
  HIGHS_EXPORT void initialiseSimplexLpRandomVectors();
  HIGHS_EXPORT void setNonbasicMove();
  HIGHS_EXPORT bool getNonsingularInverse(const HighsInt solve_phase = 0);
  HIGHS_EXPORT bool getBacktrackingBasis();
  HIGHS_EXPORT void putBacktrackingBasis();
  HIGHS_EXPORT void putBacktrackingBasis(
      const vector<HighsInt>& basicIndex_before_compute_factor);
  HIGHS_EXPORT void computePrimalObjectiveValue();
  HIGHS_EXPORT void computeDualObjectiveValue(const HighsInt phase = 2);
  HIGHS_EXPORT bool rebuildRefactor(HighsInt rebuild_reason);
  HIGHS_EXPORT HighsInt computeFactor();
  HIGHS_EXPORT void computeDualSteepestEdgeWeights(const bool initial = false);
  HIGHS_EXPORT double computeDualSteepestEdgeWeight(const HighsInt iRow, HVector& row_ep);
  HIGHS_EXPORT void updateDualSteepestEdgeWeights(const HighsInt row_out,
                                     const HighsInt variable_in,
                                     const HVector* column,
                                     const double new_pivotal_edge_weight,
                                     const double Kai,
                                     const double* dual_steepest_edge_array);
  HIGHS_EXPORT void updateDualDevexWeights(const HVector* column,
                              const double new_pivotal_edge_weight);
  HIGHS_EXPORT void resetSyntheticClock();
  HIGHS_EXPORT void allocateWorkAndBaseArrays();
  HIGHS_EXPORT void initialiseCost(const SimplexAlgorithm algorithm,
                      const HighsInt solve_phase, const bool perturb = false);
  HIGHS_EXPORT void initialiseBound(const SimplexAlgorithm algorithm,
                       const HighsInt solve_phase, const bool perturb = false);
  HIGHS_EXPORT void initialiseLpColCost();
  HIGHS_EXPORT void initialiseLpRowCost();
  HIGHS_EXPORT void initialiseLpColBound();
  HIGHS_EXPORT void initialiseLpRowBound();
  HIGHS_EXPORT void initialiseNonbasicValueAndMove();
  HIGHS_EXPORT void pivotColumnFtran(const HighsInt iCol, HVector& col_aq);
  HIGHS_EXPORT void unitBtran(const HighsInt iRow, HVector& row_ep);
  HIGHS_EXPORT void fullBtran(HVector& buffer);
  HIGHS_EXPORT void choosePriceTechnique(const HighsInt price_strategy,
                            const double row_ep_density, bool& use_col_price,
                            bool& use_row_price_w_switch);
  HIGHS_EXPORT void tableauRowPrice(const bool quad_precision, const HVector& row_ep,
                       HVector& row_ap,
                       const HighsInt debug_report = kDebugReportOff);
  HIGHS_EXPORT void fullPrice(const HVector& full_col, HVector& full_row);
  HIGHS_EXPORT void computePrimal();
  HIGHS_EXPORT void computeDual();
  HIGHS_EXPORT double computeDualForTableauColumn(const HighsInt iVar,
                                     const HVector& tableau_column);
  HIGHS_EXPORT bool reinvertOnNumericalTrouble(const std::string method_name,
                                  double& numerical_trouble_measure,
                                  const double alpha_from_col,
                                  const double alpha_from_row,
                                  const double numerical_trouble_tolerance);

  HIGHS_EXPORT void flipBound(const HighsInt iCol);
  HIGHS_EXPORT void updateFactor(HVector* column, HVector* row_ep, HighsInt* iRow,
                    HighsInt* hint);

  HIGHS_EXPORT void transformForUpdate(HVector* column, HVector* row_ep,
                          const HighsInt variable_in, HighsInt* row_out);

  HIGHS_EXPORT void updatePivots(const HighsInt variable_in, const HighsInt row_out,
                    const HighsInt move_out);
  HIGHS_EXPORT bool isBadBasisChange(const SimplexAlgorithm algorithm,
                        const HighsInt variable_in, const HighsInt row_out,
                        const HighsInt rebuild_reason);
  HIGHS_EXPORT void updateMatrix(const HighsInt variable_in, const HighsInt variable_out);

  HIGHS_EXPORT void computeInfeasibilitiesForReporting(
      const SimplexAlgorithm algorithm,
      const HighsInt solve_phase = kSolvePhase2);
  HIGHS_EXPORT void computeSimplexInfeasible();
  HIGHS_EXPORT void computeSimplexPrimalInfeasible();
  HIGHS_EXPORT void computeSimplexDualInfeasible();
  HIGHS_EXPORT void computeSimplexLpDualInfeasible();

  HIGHS_EXPORT void invalidatePrimalInfeasibilityRecord();
  HIGHS_EXPORT void invalidatePrimalMaxSumInfeasibilityRecord();
  HIGHS_EXPORT void invalidateDualInfeasibilityRecord();
  HIGHS_EXPORT void invalidateDualMaxSumInfeasibilityRecord();
  HIGHS_EXPORT bool bailout();
  HIGHS_EXPORT HighsStatus returnFromEkkSolve(const HighsStatus return_status);
  HIGHS_EXPORT HighsStatus returnFromSolve(const HighsStatus return_status);

  HIGHS_EXPORT double computeBasisCondition();
  HIGHS_EXPORT void initialiseAnalysis();
  HIGHS_EXPORT std::string rebuildReason(const HighsInt rebuild_reason);

  HIGHS_EXPORT void clearBadBasisChange(
      const BadBasisChangeReason reason = BadBasisChangeReason::kAll);
  HIGHS_EXPORT void updateBadBasisChange(const HVector& col_aq, double theta_primal);

  HIGHS_EXPORT HighsInt addBadBasisChange(const HighsInt row_out,
                             const HighsInt variable_out,
                             const HighsInt variable_in,
                             const BadBasisChangeReason reason,
                             const bool taboo = false);
  HIGHS_EXPORT void clearBadBasisChangeTabooFlag();
  HIGHS_EXPORT bool tabooBadBasisChange();
  HIGHS_EXPORT void applyTabooRowOut(vector<double>& values, const double overwrite_with);
  HIGHS_EXPORT void unapplyTabooRowOut(vector<double>& values);
  HIGHS_EXPORT void applyTabooVariableIn(vector<double>& values,
                            const double overwrite_with);
  HIGHS_EXPORT void unapplyTabooVariableIn(vector<double>& values);
  HIGHS_EXPORT bool logicalBasis() const;
  // Methods in HEkkControl
  HIGHS_EXPORT void initialiseControl();
  HIGHS_EXPORT void assessDSEWeightError(const double computed_edge_weight,
                            const double updated_edge_weight);
  HIGHS_EXPORT void updateOperationResultDensity(const double local_density,
                                    double& density);
  HIGHS_EXPORT bool switchToDevex();

  // private debug methods
  HIGHS_EXPORT HighsDebugStatus debugSimplex(const std::string message,
                                const SimplexAlgorithm algorithm,
                                const HighsInt phase,
                                const bool initialise = false) const;
  HIGHS_EXPORT void debugReportReinvertOnNumericalTrouble(
      const std::string method_name, const double numerical_trouble_measure,
      const double alpha_from_col, const double alpha_from_row,
      const double numerical_trouble_tolerance, const bool reinvert) const;

  HIGHS_EXPORT HighsDebugStatus debugUpdatedDual(const double updated_dual,
                                    const double computed_dual) const;

  HIGHS_EXPORT HighsDebugStatus debugBasisCorrect(const HighsLp* lp = NULL) const;
  HIGHS_EXPORT HighsDebugStatus debugBasisConsistent() const;
  HIGHS_EXPORT HighsDebugStatus debugNonbasicFlagConsistent() const;
  HIGHS_EXPORT HighsDebugStatus debugNonbasicMove(const HighsLp* lp = NULL) const;
  HIGHS_EXPORT HighsDebugStatus debugOkForSolve(const SimplexAlgorithm algorithm,
                                   const HighsInt phase) const;
  HIGHS_EXPORT bool debugWorkArraysOk(const SimplexAlgorithm algorithm,
                         const HighsInt phase) const;
  HIGHS_EXPORT bool debugOneNonbasicMoveVsWorkArraysOk(const HighsInt var) const;

  HIGHS_EXPORT HighsDebugStatus debugNonbasicFreeColumnSet(
      const HighsInt num_free_col, const HSet nonbasic_free_col_set) const;
  HIGHS_EXPORT HighsDebugStatus debugRowMatrix() const;
  HIGHS_EXPORT HighsDebugStatus devDebugDualSteepestEdgeWeights(const std::string message);
  HIGHS_EXPORT HighsDebugStatus debugDualSteepestEdgeWeights(
      const HighsInt alt_debug_level = -1);
  HIGHS_EXPORT HighsDebugStatus debugSimplexDualInfeasible(const std::string message,
                                              const bool force_report = false);
  HIGHS_EXPORT HighsDebugStatus debugComputeDual(const bool initialise = false) const;

  friend class HEkkPrimal;
  friend class HEkkDual;
  friend class HEkkDualRow;
  friend class HEkkDualRHS;  // For  HEkkDualRHS::assessOptimality
};

#endif /* SIMPLEX_HEKK_H_ */
