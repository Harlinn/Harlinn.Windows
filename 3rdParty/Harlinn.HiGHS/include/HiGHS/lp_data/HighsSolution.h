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
/**@file lp_data/HighsSolution.h
 * @brief Class-independent utilities for HiGHS
 */
#ifndef LP_DATA_HIGHSSOLUTION_H_
#define LP_DATA_HIGHSSOLUTION_H_

#include <string>
#include <vector>

#include "io/HighsIO.h"
#include "lp_data/HStruct.h"
#include "lp_data/HighsInfo.h"
#include "lp_data/HighsLpSolverObject.h"
#include "lp_data/HighsStatus.h"
#include "model/HighsModel.h"

class HighsLp;
struct IpxSolution;
class HighsOptions;

using std::string;

struct HighsError {
  double absolute_value;
  HighsInt absolute_index;
  double relative_value;
  HighsInt relative_index;
  void print(std::string message);
  void reset();
  void invalidate();
};

struct HighsPrimalDualErrors {
  HighsInt num_nonzero_basic_duals;
  HighsInt num_large_nonzero_basic_duals;
  double max_nonzero_basic_dual;
  double sum_nonzero_basic_duals;
  HighsInt num_off_bound_nonbasic;
  double max_off_bound_nonbasic;
  double sum_off_bound_nonbasic;
  HighsInt num_primal_residual;
  double sum_primal_residual;
  HighsInt num_dual_residual;
  double sum_dual_residual;
  HighsError max_primal_residual;
  HighsError max_primal_infeasibility;
  HighsError max_dual_residual;
  HighsError max_dual_infeasibility;
};

HIGHS_EXPORT void getKktFailures(const HighsOptions& options, const HighsModel& model,
                    const HighsSolution& solution, const HighsBasis& basis,
                    HighsInfo& highs_info);

HIGHS_EXPORT void getKktFailures(const HighsOptions& options, const HighsModel& model,
                    const HighsSolution& solution, const HighsBasis& basis,
                    HighsInfo& highs_info,
                    HighsPrimalDualErrors& primal_dual_errors,
                    const bool get_residuals = false);

HIGHS_EXPORT void getLpKktFailures(const HighsOptions& options, const HighsLp& lp,
                      const HighsSolution& solution, const HighsBasis& basis,
                      HighsInfo& highs_info);

HIGHS_EXPORT void getLpKktFailures(const HighsOptions& options, const HighsLp& lp,
                      const HighsSolution& solution, const HighsBasis& basis,
                      HighsInfo& highs_info,
                      HighsPrimalDualErrors& primal_dual_errors,
                      const bool get_residuals = false);

HIGHS_EXPORT void getKktFailures(const HighsOptions& options, const HighsLp& lp,
                    const std::vector<double>& gradient,
                    const HighsSolution& solution, const HighsBasis& basis,
                    HighsInfo& highs_info,
                    HighsPrimalDualErrors& primal_dual_errors,
                    const bool get_residuals = false);

HIGHS_EXPORT bool getVariableKktFailures(const double primal_feasibility_tolerance,
                            const double dual_feasibility_tolerance,
                            const double lower, const double upper,
                            const double value, const double dual,
                            const HighsBasisStatus* status_pointer,
                            const HighsVarType integrality,
                            double& absolute_primal_infeasibility,
                            double& relative_primal_infeasibility,
                            double& dual_infeasibility, double& value_residual);

HIGHS_EXPORT double computeObjectiveValue(const HighsLp& lp, const HighsSolution& solution);

HIGHS_EXPORT void refineBasis(const HighsLp& lp, const HighsSolution& solution,
                 HighsBasis& basis);

HIGHS_EXPORT HighsStatus ipxSolutionToHighsSolution(
    const HighsOptions& options, const HighsLp& lp,
    const std::vector<double>& rhs, const std::vector<char>& constraint_type,
    const HighsInt ipx_num_col, const HighsInt ipx_num_row,
    const std::vector<double>& ipx_x, const std::vector<double>& ipx_slack_vars,
    const std::vector<double>& ipx_y, const std::vector<double>& ipx_zl,
    const std::vector<double>& ipx_zu, const HighsModelStatus model_status,
    HighsSolution& highs_solution);

HIGHS_EXPORT HighsStatus ipxBasicSolutionToHighsBasicSolution(
    const HighsLogOptions& log_options, const HighsLp& lp,
    const std::vector<double>& rhs, const std::vector<char>& constraint_type,
    const IpxSolution& ipx_solution, HighsBasis& highs_basis,
    HighsSolution& highs_solution);

HIGHS_EXPORT HighsStatus formSimplexLpBasisAndFactorReturn(
    const HighsStatus return_status, HighsLpSolverObject& solver_object);
HIGHS_EXPORT HighsStatus formSimplexLpBasisAndFactor(
    HighsLpSolverObject& solver_object,
    const bool only_from_known_basis = false);

HIGHS_EXPORT void accommodateAlienBasis(HighsLpSolverObject& solver_object);

HIGHS_EXPORT void resetModelStatusAndHighsInfo(HighsLpSolverObject& solver_object);
HIGHS_EXPORT void resetModelStatusAndHighsInfo(HighsModelStatus& model_status,
                                  HighsInfo& highs_info);
HIGHS_EXPORT bool isBasisConsistent(const HighsLp& lp, const HighsBasis& basis);

HIGHS_EXPORT bool isPrimalSolutionRightSize(const HighsLp& lp,
                               const HighsSolution& solution);
HIGHS_EXPORT bool isDualSolutionRightSize(const HighsLp& lp, const HighsSolution& solution);
HIGHS_EXPORT bool isSolutionRightSize(const HighsLp& lp, const HighsSolution& solution);
HIGHS_EXPORT bool isBasisRightSize(const HighsLp& lp, const HighsBasis& basis);

#endif  // LP_DATA_HIGHSSOLUTION_H_
