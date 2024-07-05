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
/**@file util/HUtils.h
 * @brief Class-independent utilities for HiGHS
 */
#ifndef UTIL_HIGHSUTILS_H_
#define UTIL_HIGHSUTILS_H_

#include <cassert>
#include <string>
#include <vector>

#include "lp_data/HighsOptions.h"

const HighsInt kIndexCollectionCreateOk = 0;
const HighsInt kIndexCollectionCreateIllegalInterval = 1;
const HighsInt kIndexCollectionCreateIllegalSetSize = 1;
const HighsInt kIndexCollectionCreateIllegalSetDimension = 2;
const HighsInt kIndexCollectionCreateIllegalSetOrder = 3;
const HighsInt kIndexCollectionCreateIllegalMaskSize = 1;

void highsSparseTranspose(HighsInt numRow, HighsInt numCol,
                          const std::vector<HighsInt>& Astart,
                          const std::vector<HighsInt>& Aindex,
                          const std::vector<double>& Avalue,
                          std::vector<HighsInt>& ARstart,
                          std::vector<HighsInt>& ARindex,
                          std::vector<double>& ARvalue);

struct HighsIndexCollection {
  HighsInt dimension_ = -1;
  bool is_interval_ = false;
  HighsInt from_ = -1;
  HighsInt to_ = -2;
  bool is_set_ = false;
  HighsInt set_num_entries_ = -1;
  std::vector<HighsInt> set_;
  bool is_mask_ = false;
  std::vector<HighsInt> mask_;
};

struct HighsValueDistribution {
  std::string distribution_name_;
  std::string value_name_;
  HighsInt num_count_;
  HighsInt num_zero_;
  HighsInt num_one_;
  double min_value_;
  double max_value_;
  std::vector<double> limit_;
  std::vector<HighsInt> count_;
  HighsInt sum_count_;
};

struct HighsScatterData {
  HighsInt max_num_point_;
  HighsInt num_point_;
  HighsInt last_point_;
  std::vector<double> value0_;
  std::vector<double> value1_;
  bool have_regression_coeff_;
  double linear_coeff0_;
  double linear_coeff1_;
  double linear_regression_error_;
  double log_coeff0_;
  double log_coeff1_;
  double log_regression_error_;
  HighsInt num_error_comparison_;
  HighsInt num_awful_linear_;
  HighsInt num_awful_log_;
  HighsInt num_bad_linear_;
  HighsInt num_bad_log_;
  HighsInt num_fair_linear_;
  HighsInt num_fair_log_;
  HighsInt num_better_linear_;
  HighsInt num_better_log_;
};

const double awful_regression_error = 2.0;
const double bad_regression_error = 0.2;
const double fair_regression_error = 0.02;

HIGHS_EXPORT HighsInt create(HighsIndexCollection& index_collection, const HighsInt from_col,
                const HighsInt to_col, const HighsInt dimension);

HIGHS_EXPORT HighsInt create(HighsIndexCollection& index_collection,
                const HighsInt num_set_entries, const HighsInt* set,
                const HighsInt dimension);

HIGHS_EXPORT HighsInt create(HighsIndexCollection& index_collection, const HighsInt* mask,
                const HighsInt dimension);

HIGHS_EXPORT bool ok(const HighsIndexCollection& index_collection);

HIGHS_EXPORT void limits(const HighsIndexCollection& index_collection, HighsInt& from_k,
            HighsInt& to_k);

HIGHS_EXPORT void updateOutInIndex(const HighsIndexCollection& index_collection,
                      HighsInt& out_from_ix, HighsInt& out_to_ix,
                      HighsInt& in_from_ix, HighsInt& in_to_ix,
                      HighsInt& current_set_entry);

HIGHS_EXPORT HighsInt dataSize(const HighsIndexCollection& index_collection);

HIGHS_EXPORT bool highsVarTypeUserDataNotNull(const HighsLogOptions& log_options,
                                 const HighsVarType* user_data,
                                 const std::string name);
HIGHS_EXPORT bool intUserDataNotNull(const HighsLogOptions& log_options,
                        const HighsInt* user_data, const std::string name);
HIGHS_EXPORT bool doubleUserDataNotNull(const HighsLogOptions& log_options,
                           const double* user_data, const std::string name);

HIGHS_EXPORT double getNorm2(const std::vector<double> values);

/**
 * @brief Logical check of double being +Infinity
 */
HIGHS_EXPORT bool highs_isInfinity(double val  //!< Value being tested against +Infinity
);
/**
 * @brief Returns the relative difference of two doubles
 */
HIGHS_EXPORT double highsRelativeDifference(const double v0, const double v1);

/**
 * @brief Analyse the values of a vector, assessing how many are in
 * each power of ten, and possibly analyse the distribution of
 * different values
 *
 * NB If log_options is a null pointer then printf is used
 */
HIGHS_EXPORT void analyseVectorValues(
    const HighsLogOptions* log_options,
    const std::string message,       //!< Message to be printed
    HighsInt vecDim,                 //!< Dimension of vector
    const std::vector<double>& vec,  //!< Vector of values
    bool analyseValueList = false,   //!< Possibly analyse the distribution of
                                     //!< different values in the vector
    std::string model_name =
        "Unknown"  //!< Model name to report if analysing distribution of
                   //!< different values in the vector
);

HIGHS_EXPORT void analyseVectorValues(
    const HighsLogOptions* log_options,
    const std::string message,         //!< Message to be printed
    HighsInt vecDim,                   //!< Dimension of vector
    const std::vector<HighsInt>& vec,  //!< Vector of values
    std::string model_name =
        "Unknown"  //!< Model name to report if analysing distribution of
                   //!< different values in the vector
);

HIGHS_EXPORT void analyseMatrixSparsity(
    const HighsLogOptions& log_options,
    const char* message,                  //!< Message to be printed
    HighsInt numCol,                      //!< Number of columns
    HighsInt numRow,                      //!< Number of rows
    const std::vector<HighsInt>& Astart,  //!< Matrix column starts
    const std::vector<HighsInt>& Aindex   //!< Matrix row indices
);

HIGHS_EXPORT bool initialiseValueDistribution(const std::string distribution_name,
                                 const std::string value_name,
                                 const double min_value_limit,
                                 const double max_value_limit,
                                 const double base_value_limit,
                                 HighsValueDistribution& value_distribution);

HIGHS_EXPORT bool updateValueDistribution(const double value,
                             HighsValueDistribution& value_distribution);

HIGHS_EXPORT HighsInt integerPercentage(const HighsInt of, const HighsInt in);
HIGHS_EXPORT double doublePercentage(const HighsInt of, const HighsInt in);

HIGHS_EXPORT bool logValueDistribution(const HighsLogOptions& log_options,
                          const HighsValueDistribution& value_distribution,
                          const HighsInt mu = 0);
HIGHS_EXPORT bool initialiseScatterData(const HighsInt max_num_point,
                           HighsScatterData& scatter_data);
HIGHS_EXPORT bool updateScatterData(const double value0, const double value1,
                       HighsScatterData& scatter_data);
HIGHS_EXPORT bool regressScatterData(HighsScatterData& scatter_data);
HIGHS_EXPORT bool predictFromScatterData(const HighsScatterData& scatter_data,
                            const double value0, double& predicted_value1,
                            const bool log_regression = false);
HIGHS_EXPORT bool printScatterData(std::string name, const HighsScatterData& scatter_data);
HIGHS_EXPORT void printScatterDataRegressionComparison(std::string name,
                                          const HighsScatterData& scatter_data);
HIGHS_EXPORT bool computeScatterDataRegressionError(HighsScatterData& scatter_data,
                                       const bool print = false);

HIGHS_EXPORT double nearestPowerOfTwoScale(const double value);

// If assert_condition is false then, if NDEBUG is defined message is
// printed and abort() is called, otherwise assert is called
HIGHS_EXPORT void highsAssert(const bool assert_condition, const std::string message = "");

// If pause_condition is true, then keyboard input is required. Allows
// breakpoints in VScode where optimization might prevent them.
HIGHS_EXPORT bool highsPause(const bool pause_condition, const std::string message = "");
#endif  // UTIL_HIGHSUTILS_H_
