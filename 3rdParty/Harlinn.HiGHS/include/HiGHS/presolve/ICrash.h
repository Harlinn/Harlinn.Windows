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
/**@file presolve/ICrash.h
 * @brief
 * @author Julian Hall, Ivet Galabova, Qi Huangfu and Michael Feldmeier
 */
#ifndef PRESOLVE_QUADRATIC_CRASH_H_
#define PRESOLVE_QUADRATIC_CRASH_H_

#include <vector>

#include "io/HighsIO.h"
#include "lp_data/HStruct.h"
#include "lp_data/HighsLp.h"
#include "lp_data/HighsOptions.h"
#include "lp_data/HighsStatus.h"

enum class ICrashStrategy {
  kPenalty,
  kAdmm,
  kICA,
  kUpdatePenalty,
  kUpdateAdmm
};

struct ICrashIterationDetails {
  int num;
  double weight;
  double lambda_norm_2;

  double lp_objective;
  double quadratic_objective;
  double residual_norm_2;

  double time;
};

struct ICrashInfo {
  int num_iterations;

  double final_lp_objective;
  double final_quadratic_objective;
  double final_residual_norm_2;

  double starting_weight;
  double final_weight;

  std::vector<ICrashIterationDetails> details;
  std::vector<double> x_values;

  double total_time;
};

struct ICrashOptions {
  bool dualize;
  ICrashStrategy strategy;
  double starting_weight;
  HighsInt iterations;
  HighsInt approximate_minimization_iterations;
  bool exact;
  bool breakpoints;  // gets ignored if exact is set to true
  HighsLogOptions log_options;
};

struct Quadratic {
  const HighsLp lp;
  const ICrashOptions options;
  std::vector<ICrashIterationDetails> details;

  HighsSolution xk;

  double lp_objective;
  double quadratic_objective;
  std::vector<double> residual;
  double residual_norm_2;

  double mu;
  std::vector<double> lambda;

  Quadratic(HighsLp lp_, ICrashOptions options_)
      : lp(lp_),
        options(options_),
        lp_objective(0.0),
        quadratic_objective(0.0),
        residual_norm_2(0.0),
        mu(0.0) {}
};

// Functions: Call.
HIGHS_EXPORT HighsStatus callICrash(const HighsLp& lp, const ICrashOptions& options,
                       ICrashInfo& result);

// Functions: Options.
HIGHS_EXPORT bool checkOptions(const HighsLp& lp, const ICrashOptions options);
HIGHS_EXPORT Quadratic parseOptions(const HighsLp& lp, const ICrashOptions options);
HIGHS_EXPORT bool parseICrashStrategy(const std::string& strategy,
                         ICrashStrategy& icrash_strategy);
HIGHS_EXPORT std::string ICrashtrategyToString(const ICrashStrategy strategy);

// Functions: Crash.
HIGHS_EXPORT bool initialize(Quadratic& idata, const ICrashOptions& options);
HIGHS_EXPORT void update(Quadratic& idata);
HIGHS_EXPORT void updateParameters(Quadratic& idata, const ICrashOptions& options,
                      const int iteration);
HIGHS_EXPORT bool solveSubproblem(Quadratic& idata, const ICrashOptions& options);

// Functions: Util.
HIGHS_EXPORT double getQuadraticObjective(const Quadratic& idata);
HIGHS_EXPORT ICrashIterationDetails fillDetails(const int num, const Quadratic& idata);
HIGHS_EXPORT void fillICrashInfo(const int n_iterations, ICrashInfo& result);
HIGHS_EXPORT void reportSubproblem(const ICrashOptions options, const Quadratic& idata,
                      const int iteration);
HIGHS_EXPORT void reportOptions(const ICrashOptions& options);

HIGHS_EXPORT bool callCrossover(const HighsLp& lp, const HighsOptions& options,
                   const std::vector<double>& x_values, HighsSolution& solution,
                   HighsBasis& basis, HighsCallback& callback);

#endif
