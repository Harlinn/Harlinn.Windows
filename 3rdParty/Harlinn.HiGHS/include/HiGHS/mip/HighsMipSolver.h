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
#ifndef MIP_HIGHS_MIP_SOLVER_H_
#define MIP_HIGHS_MIP_SOLVER_H_

#include "Highs.h"
#include "lp_data/HighsCallback.h"
#include "lp_data/HighsOptions.h"

struct HighsMipSolverData;
class HighsCutPool;
struct HighsPseudocostInitialization;
class HighsCliqueTable;
class HighsImplications;

class HighsMipSolver {
 public:
  HighsCallback* callback_;
  const HighsOptions* options_mip_;
  const HighsLp* model_;
  const HighsLp* orig_model_;
  HighsModelStatus modelstatus_;
  std::vector<double> solution_;
  double solution_objective_;
  double bound_violation_;
  double integrality_violation_;
  double row_violation_;
  // The following are only to return data to HiGHS, and are set in
  // HighsMipSolver::cleanupSolve
  double dual_bound_;
  double primal_bound_;
  double gap_;
  int64_t node_count_;
  int64_t total_lp_iterations_;

  FILE* improving_solution_file_;
  std::vector<HighsObjectiveSolution> saved_objective_and_solution_;

  bool submip;
  const HighsBasis* rootbasis;
  const HighsPseudocostInitialization* pscostinit;
  const HighsCliqueTable* clqtableinit;
  const HighsImplications* implicinit;

  std::unique_ptr<HighsMipSolverData> mipdata_;

  HIGHS_EXPORT void run();

  HighsInt numCol() const { return model_->num_col_; }

  HighsInt numRow() const { return model_->num_row_; }

  HighsInt numNonzero() const { return model_->a_matrix_.numNz(); }

  const double* colCost() const { return model_->col_cost_.data(); }

  double colCost(HighsInt col) const { return model_->col_cost_[col]; }

  const double* rowLower() const { return model_->row_lower_.data(); }

  double rowLower(HighsInt col) const { return model_->row_lower_[col]; }

  const double* rowUpper() const { return model_->row_upper_.data(); }

  double rowUpper(HighsInt col) const { return model_->row_upper_[col]; }

  const HighsVarType* variableType() const {
    return model_->integrality_.data();
  }

  HighsVarType variableType(HighsInt col) const {
    return model_->integrality_[col];
  }

  HIGHS_EXPORT HighsMipSolver(HighsCallback& callback, const HighsOptions& options,
                 const HighsLp& lp, const HighsSolution& solution,
                 bool submip = false);

  HIGHS_EXPORT ~HighsMipSolver();

  void setModel(const HighsLp& model) {
    model_ = &model;
    solution_objective_ = kHighsInf;
  }

  mutable HighsTimer timer_;
  HIGHS_EXPORT void cleanupSolve();

  HIGHS_EXPORT void runPresolve(const HighsInt presolve_reduction_limit);
  HIGHS_EXPORT const HighsLp& getPresolvedModel() const;
  HIGHS_EXPORT HighsPresolveStatus getPresolveStatus() const;
  HIGHS_EXPORT presolve::HighsPostsolveStack getPostsolveStack() const;

  HIGHS_EXPORT void callbackGetCutPool() const;
};

#endif
