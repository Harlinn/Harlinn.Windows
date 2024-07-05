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
/**@file lp_data/HighsModelUtils.h
 * @brief Class-independent utilities for HiGHS
 */
#ifndef LP_DATA_HIGHSMODELUTILS_H_
#define LP_DATA_HIGHSMODELUTILS_H_

#include "lp_data/HighsInfo.h"
#include "model/HighsModel.h"
// #include "Highs.h"
// #include "lp_data/HighsStatus.h"
// #include "lp_data/HStruct.h"
// #include "lp_data/HighsInfo.h"
// #include "lp_data/HighsLp.h"
// #include "lp_data/HighsOptions.h"

// Analyse lower and upper bounds of a model
HIGHS_EXPORT void analyseModelBounds(const HighsLogOptions& log_options, const char* message,
                        HighsInt numBd, const std::vector<double>& lower,
                        const std::vector<double>& upper);
HIGHS_EXPORT bool hasNamesWithSpaces(const HighsLogOptions& log_options,
                        const HighsInt num_name,
                        const std::vector<std::string>& names);
HIGHS_EXPORT void writeModelBoundSolution(
    FILE* file, const bool columns, const HighsInt dim,
    const std::vector<double>& lower, const std::vector<double>& upper,
    const std::vector<std::string>& names, const bool have_primal,
    const std::vector<double>& primal, const bool have_dual,
    const std::vector<double>& dual, const bool have_basis,
    const std::vector<HighsBasisStatus>& status,
    const HighsVarType* integrality = NULL);

HIGHS_EXPORT void writeModelObjective(FILE* file, const HighsModel& model,
                         const std::vector<double>& primal_solution);

HIGHS_EXPORT void writeLpObjective(FILE* file, const HighsLp& lp,
                      const std::vector<double>& primal_solution);

HIGHS_EXPORT void writeObjectiveValue(FILE* file, const double objective_value);

HIGHS_EXPORT void writePrimalSolution(FILE* file, const HighsLp& lp,
                         const std::vector<double>& primal_solution,
                         const bool sparse = false);

HIGHS_EXPORT void writeModelSolution(FILE* file, const HighsModel& model,
                        const HighsSolution& solution, const HighsInfo& info,
                        const bool sparse = false);

HIGHS_EXPORT HighsInt maxNameLength(const HighsInt num_name,
                       const std::vector<std::string>& names);
HIGHS_EXPORT HighsStatus normaliseNames(const HighsLogOptions& log_options,
                           const std::string name_type, const HighsInt num_name,
                           std::vector<std::string>& names,
                           HighsInt& max_name_length);

HIGHS_EXPORT void writeSolutionFile(FILE* file, const HighsOptions& options,
                       const HighsModel& model, const HighsBasis& basis,
                       const HighsSolution& solution, const HighsInfo& info,
                       const HighsModelStatus model_status,
                       const HighsInt style);

HIGHS_EXPORT void writeGlpsolCostRow(FILE* file, const bool raw, const bool is_mip,
                        const HighsInt row_id, const std::string objective_name,
                        const double objective_function_value);

HIGHS_EXPORT void writeGlpsolSolution(FILE* file, const HighsOptions& options,
                         const HighsModel& model, const HighsBasis& basis,
                         const HighsSolution& solution,
                         const HighsModelStatus model_status,
                         const HighsInfo& info, const bool raw);

HIGHS_EXPORT void writeOldRawSolution(FILE* file, const HighsLp& lp, const HighsBasis& basis,
                         const HighsSolution& solution);

HIGHS_EXPORT HighsBasisStatus checkedVarHighsNonbasicStatus(
    const HighsBasisStatus ideal_status, const double lower,
    const double upper);

HIGHS_EXPORT std::string utilModelStatusToString(const HighsModelStatus model_status);

HIGHS_EXPORT std::string utilSolutionStatusToString(const HighsInt solution_status);

HIGHS_EXPORT std::string utilBasisStatusToString(const HighsBasisStatus basis_status);

HIGHS_EXPORT std::string utilBasisValidityToString(const HighsInt basis_validity);

HIGHS_EXPORT std::string utilPresolveRuleTypeToString(const HighsInt rule_type);

HIGHS_EXPORT HighsStatus highsStatusFromHighsModelStatus(HighsModelStatus model_status);

HIGHS_EXPORT std::string statusToString(const HighsBasisStatus status, const double lower,
                           const double upper);
HIGHS_EXPORT std::string typeToString(const HighsVarType type);

HIGHS_EXPORT std::string findModelObjectiveName(const HighsLp* lp,
                                   const HighsHessian* hessian = nullptr);

// bool repeatedNames(const std::vector<std::string> name);

#endif
