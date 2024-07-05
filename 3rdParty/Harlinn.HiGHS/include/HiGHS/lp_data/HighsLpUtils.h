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
/**@file lp_data/HighsLpUtils.h
 * @brief Class-independent utilities for HiGHS
 */
#ifndef LP_DATA_HIGHSLPUTILS_H_
#define LP_DATA_HIGHSLPUTILS_H_

#include <vector>

#include "lp_data/HConst.h"
#include "lp_data/HighsInfo.h"
#include "lp_data/HighsLp.h"
#include "lp_data/HighsStatus.h"
#include "util/HighsUtils.h"

// class HighsLp;
struct SimplexScale;
struct HighsBasis;
struct HighsSolution;
class HighsOptions;

using std::vector;

HIGHS_EXPORT void writeBasisFile(FILE*& file, const HighsBasis& basis);

HIGHS_EXPORT HighsStatus readBasisFile(const HighsLogOptions& log_options, HighsBasis& basis,
                          const std::string filename);
HIGHS_EXPORT HighsStatus readBasisStream(const HighsLogOptions& log_options,
                            HighsBasis& basis, std::ifstream& in_file);

// Methods taking HighsLp as an argument
HIGHS_EXPORT HighsStatus assessLp(HighsLp& lp, const HighsOptions& options);

HIGHS_EXPORT bool lpDimensionsOk(std::string message, const HighsLp& lp,
                    const HighsLogOptions& log_options);

HIGHS_EXPORT HighsStatus assessCosts(const HighsOptions& options, const HighsInt ml_col_os,
                        const HighsIndexCollection& index_collection,
                        vector<double>& cost, bool& has_infinite_cost,
                        const double infinite_cost);

HIGHS_EXPORT HighsStatus assessBounds(const HighsOptions& options, const char* type,
                         const HighsInt ml_ix_os,
                         const HighsIndexCollection& index_collection,
                         vector<double>& lower, vector<double>& upper,
                         const double infinite_bound,
                         const HighsVarType* integrality = nullptr);

HIGHS_EXPORT HighsStatus cleanBounds(const HighsOptions& options, HighsLp& lp);

HIGHS_EXPORT bool boundScaleOk(const std::vector<double>& lower,
                  const std::vector<double>& upper, const HighsInt bound_scale,
                  const double infinite_bound);

HIGHS_EXPORT bool costScaleOk(const std::vector<double>& cost, const HighsInt cost_scale,
                 const double infinite_cost);

HIGHS_EXPORT HighsStatus assessSemiVariables(HighsLp& lp, const HighsOptions& options,
                                bool& made_semi_variable_mods);
HIGHS_EXPORT void relaxSemiVariables(HighsLp& lp, bool& made_semi_variable_mods);

HIGHS_EXPORT bool activeModifiedUpperBounds(const HighsOptions& options, const HighsLp& lp,
                               const std::vector<double> col_value);

HIGHS_EXPORT bool considerScaling(const HighsOptions& options, HighsLp& lp);
HIGHS_EXPORT void scaleLp(const HighsOptions& options, HighsLp& lp,
             const bool force_scaling = false);
HIGHS_EXPORT bool equilibrationScaleMatrix(const HighsOptions& options, HighsLp& lp,
                              const HighsInt use_scale_strategy);
HIGHS_EXPORT bool maxValueScaleMatrix(const HighsOptions& options, HighsLp& lp,
                         const HighsInt use_scale_strategy);

HIGHS_EXPORT HighsStatus applyScalingToLpCol(HighsLp& lp, const HighsInt col,
                                const double colScale);

HIGHS_EXPORT HighsStatus applyScalingToLpRow(HighsLp& lp, const HighsInt row,
                                const double rowScale);

HIGHS_EXPORT void unscaleSolution(HighsSolution& solution, const HighsScale& scale);

HIGHS_EXPORT void appendColsToLpVectors(HighsLp& lp, const HighsInt num_new_col,
                           const vector<double>& colCost,
                           const vector<double>& colLower,
                           const vector<double>& colUpper);

HIGHS_EXPORT void appendRowsToLpVectors(HighsLp& lp, const HighsInt num_new_row,
                           const vector<double>& rowLower,
                           const vector<double>& rowUpper);

HIGHS_EXPORT void deleteScale(vector<double>& scale,
                 const HighsIndexCollection& index_collection);

HIGHS_EXPORT void changeLpMatrixCoefficient(HighsLp& lp, const HighsInt row,
                               const HighsInt col, const double new_value,
                               const bool zero_new_value);

HIGHS_EXPORT void changeLpIntegrality(HighsLp& lp,
                         const HighsIndexCollection& index_collection,
                         const vector<HighsVarType>& new_integrality);

HIGHS_EXPORT void changeLpCosts(HighsLp& lp, const HighsIndexCollection& index_collection,
                   const vector<double>& new_col_cost,
                   const double infinite_cost);

HIGHS_EXPORT void changeLpColBounds(HighsLp& lp,
                       const HighsIndexCollection& index_collection,
                       const vector<double>& new_col_lower,
                       const vector<double>& new_col_upper);

HIGHS_EXPORT void changeLpRowBounds(HighsLp& lp,
                       const HighsIndexCollection& index_collection,
                       const vector<double>& new_row_lower,
                       const vector<double>& new_row_upper);

HIGHS_EXPORT void changeBounds(vector<double>& lower, vector<double>& upper,
                  const HighsIndexCollection& index_collection,
                  const vector<double>& new_lower,
                  const vector<double>& new_upper);

/**
 * @brief Report the data of an LP
 */
HIGHS_EXPORT void reportLp(const HighsLogOptions& log_options,
              const HighsLp& lp,  //!< LP whose data are to be reported
              const HighsLogType report_level = HighsLogType::kInfo
              //!< INFO => scalar [dimensions];
              //!< DETAILED => vector[costs/bounds];
              //!< VERBOSE => vector+matrix
);
/**
 * @brief Report the brief data of an LP
 */
HIGHS_EXPORT void reportLpBrief(const HighsLogOptions& log_options,
                   const HighsLp& lp  //!< LP whose data are to be reported
);
/**
 * @brief Report the data of an LP
 */
HIGHS_EXPORT void reportLpDimensions(const HighsLogOptions& log_options,
                        const HighsLp& lp  //!< LP whose data are to be reported
);
/**
 * @brief Report the data of an LP
 */
HIGHS_EXPORT void reportLpObjSense(const HighsLogOptions& log_options,
                      const HighsLp& lp  //!< LP whose data are to be reported
);
/**
 * @brief Report the data of an LP
 */
HIGHS_EXPORT void reportLpColVectors(const HighsLogOptions& log_options,
                        const HighsLp& lp  //!< LP whose data are to be reported
);
/**
 * @brief Report the data of an LP
 */
HIGHS_EXPORT void reportLpRowVectors(const HighsLogOptions& log_options,
                        const HighsLp& lp  //!< LP whose data are to be reported
);
/**
 * @brief Report the data of an LP
 */
HIGHS_EXPORT void reportLpColMatrix(const HighsLogOptions& log_options,
                       const HighsLp& lp  //!< LP whose data are to be reported
);

HIGHS_EXPORT void reportMatrix(const HighsLogOptions& log_options, const std::string message,
                  const HighsInt num_col, const HighsInt num_nz,
                  const HighsInt* start, const HighsInt* index,
                  const double* value);

// Get the number of integer-valued columns in the LP
HIGHS_EXPORT HighsInt getNumInt(const HighsLp& lp);

// Get the costs for a contiguous set of columns
HIGHS_EXPORT void getLpCosts(const HighsLp& lp, const HighsInt from_col,
                const HighsInt to_col, double* XcolCost);

// Get the bounds for a contiguous set of columns
HIGHS_EXPORT void getLpColBounds(const HighsLp& lp, const HighsInt from_col,
                    const HighsInt to_col, double* XcolLower,
                    double* XcolUpper);

// Get the bounds for a contiguous set of rows
HIGHS_EXPORT void getLpRowBounds(const HighsLp& lp, const HighsInt from_row,
                    const HighsInt to_row, double* XrowLower,
                    double* XrowUpper);

HIGHS_EXPORT void getLpMatrixCoefficient(const HighsLp& lp, const HighsInt row,
                            const HighsInt col, double* val);
// Analyse the data in an LP problem
HIGHS_EXPORT void analyseLp(const HighsLogOptions& log_options, const HighsLp& lp);

HIGHS_EXPORT HighsStatus readSolutionFile(const std::string filename,
                             const HighsOptions& options, const HighsLp& lp,
                             HighsBasis& basis, HighsSolution& solution,
                             const HighsInt style);

HIGHS_EXPORT HighsStatus readSolutionFileErrorReturn(std::ifstream& in_file);
HIGHS_EXPORT HighsStatus readSolutionFileReturn(const HighsStatus status,
                                   HighsSolution& solution, HighsBasis& basis,
                                   const HighsSolution& read_solution,
                                   const HighsBasis& read_basis,
                                   std::ifstream& in_file);
HIGHS_EXPORT bool readSolutionFileIgnoreLineOk(std::ifstream& in_file);
HIGHS_EXPORT bool readSolutionFileKeywordLineOk(std::string& keyword,
                                   std::ifstream& in_file);
HIGHS_EXPORT bool readSolutionFileHashKeywordIntLineOk(std::string& keyword, HighsInt& value,
                                          std::ifstream& in_file);
HIGHS_EXPORT bool readSolutionFileIdDoubleLineOk(double& value, std::ifstream& in_file);
HIGHS_EXPORT bool readSolutionFileIdDoubleIntLineOk(double& value, HighsInt& index,
                                       std::ifstream& in_file);

HIGHS_EXPORT void assessColPrimalSolution(const HighsOptions& options, const double primal,
                             const double lower, const double upper,
                             const HighsVarType type, double& col_infeasibility,
                             double& integer_infeasibility);

HIGHS_EXPORT HighsStatus assessLpPrimalSolution(const HighsOptions& options,
                                   const HighsLp& lp,
                                   const HighsSolution& solution, bool& valid,
                                   bool& integral, bool& feasible);

HIGHS_EXPORT HighsStatus calculateRowValuesQuad(const HighsLp& lp,
                                   const std::vector<double>& col_value,
                                   std::vector<double>& row_value,
                                   const HighsInt report_row = -1);
HIGHS_EXPORT HighsStatus calculateRowValuesQuad(const HighsLp& lp, HighsSolution& solution,
                                   const HighsInt report_row = -1);

HIGHS_EXPORT HighsStatus calculateColDualsQuad(const HighsLp& lp, HighsSolution& solution);

HIGHS_EXPORT bool isColDataNull(const HighsLogOptions& log_options,
                   const double* usr_col_cost, const double* usr_col_lower,
                   const double* usr_col_upper);
HIGHS_EXPORT bool isRowDataNull(const HighsLogOptions& log_options,
                   const double* usr_row_lower, const double* usr_row_upper);
HIGHS_EXPORT bool isMatrixDataNull(const HighsLogOptions& log_options,
                      const HighsInt* usr_matrix_start,
                      const HighsInt* usr_matrix_index,
                      const double* usr_matrix_value);

HIGHS_EXPORT void reportPresolveReductions(const HighsLogOptions& log_options,
                              const HighsLp& lp, const HighsLp& presolve_lp);

HIGHS_EXPORT void reportPresolveReductions(const HighsLogOptions& log_options,
                              const HighsLp& lp, const bool presolve_to_empty);

HIGHS_EXPORT bool isLessInfeasibleDSECandidate(const HighsLogOptions& log_options,
                                  const HighsLp& lp);

HIGHS_EXPORT HighsLp withoutSemiVariables(const HighsLp& lp, HighsSolution& solution,
                             const double primal_feasibility_tolerance);

HIGHS_EXPORT void removeRowsOfCountOne(const HighsLogOptions& log_options, HighsLp& lp);

#endif  // LP_DATA_HIGHSLPUTILS_H_
