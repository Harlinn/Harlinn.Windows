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
/**@file util/HighsSparseMatrix.h
 * @brief
 */
#ifndef LP_DATA_HIGHS_SPARSE_MATRIX_H_
#define LP_DATA_HIGHS_SPARSE_MATRIX_H_

#include <vector>

#include "lp_data/HConst.h"
#include "lp_data/HStruct.h"  //For  HighsScale
#include "lp_data/HighsStatus.h"
#include "simplex/SimplexStruct.h"  //For SimplexScale until scaling is HighsScale
#include "util/HVector.h"
#include "util/HVectorBase.h"
#include "util/HighsSparseVectorSum.h"
#include "util/HighsUtils.h"

const double kHyperPriceDensity = 0.1;
const HighsInt kDebugReportOff = -2;
const HighsInt kDebugReportAll = -1;

class HighsSparseMatrix {
 public:
  HighsSparseMatrix() { clear(); }
  MatrixFormat format_;
  HighsInt num_col_;
  HighsInt num_row_;
  std::vector<HighsInt> start_;
  std::vector<HighsInt> p_end_;
  std::vector<HighsInt> index_;
  std::vector<double> value_;

  HIGHS_EXPORT bool operator==(const HighsSparseMatrix& matrix) const;
  HIGHS_EXPORT void clear();
  HIGHS_EXPORT void exactResize();
  bool formatOk() const { return (this->isColwise() || this->isRowwise()); };
  HIGHS_EXPORT bool isRowwise() const;
  HIGHS_EXPORT bool isColwise() const;
  HIGHS_EXPORT HighsInt numNz() const;
  HIGHS_EXPORT void range(double& min_value, double& max_value) const;
  HIGHS_EXPORT void setFormat(const MatrixFormat desired_format);
  HIGHS_EXPORT void ensureColwise();
  HIGHS_EXPORT void ensureRowwise();

  HIGHS_EXPORT void addVec(const HighsInt num_nz, const HighsInt* index, const double* value,
              const double multiple = 1);
  HIGHS_EXPORT void addCols(const HighsSparseMatrix new_cols,
               const int8_t* in_partition = NULL);
  HIGHS_EXPORT void addRows(const HighsSparseMatrix new_rows,
               const int8_t* in_partition = NULL);
  HIGHS_EXPORT void getRow(const HighsInt iRow, HighsInt& num_nz, HighsInt* index,
              double* value) const;
  HIGHS_EXPORT void getCol(const HighsInt iCol, HighsInt& num_nz, HighsInt* index,
              double* value) const;
  HIGHS_EXPORT void deleteCols(const HighsIndexCollection& index_collection);
  HIGHS_EXPORT void deleteRows(const HighsIndexCollection& index_collection);
  HIGHS_EXPORT HighsStatus assessDimensions(const HighsLogOptions& log_options,
                               const std::string matrix_name);
  HIGHS_EXPORT HighsStatus assess(const HighsLogOptions& log_options,
                     const std::string matrix_name,
                     const double small_matrix_value,
                     const double large_matrix_value);
  HIGHS_EXPORT void assessSmallValues(const HighsLogOptions& log_options,
                         const double small_matrix_value);
  HIGHS_EXPORT bool hasLargeValue(const double large_matrix_value);
  HIGHS_EXPORT void considerColScaling(const HighsInt max_scale_factor_exponent,
                          double* col_scale);
  HIGHS_EXPORT void considerRowScaling(const HighsInt max_scale_factor_exponent,
                          double* row_scale);
  HIGHS_EXPORT void scaleCol(const HighsInt col, const double colScale);
  HIGHS_EXPORT void scaleRow(const HighsInt row, const double rowScale);
  HIGHS_EXPORT void applyScale(const HighsScale& scale);
  HIGHS_EXPORT void applyRowScale(const HighsScale& scale);
  HIGHS_EXPORT void applyColScale(const HighsScale& scale);
  HIGHS_EXPORT void unapplyScale(const HighsScale& scale);
  HIGHS_EXPORT void createSlice(const HighsSparseMatrix& matrix, const HighsInt from_col,
                   const HighsInt to_col);
  HIGHS_EXPORT void createColwise(const HighsSparseMatrix& matrix);
  HIGHS_EXPORT void createRowwise(const HighsSparseMatrix& matrix);
  HIGHS_EXPORT void alphaProductPlusY(const double alpha, const std::vector<double>& x,
                         std::vector<double>& y,
                         const bool transpose = false) const;
  HIGHS_EXPORT void product(vector<double>& result, const vector<double>& x) const;
  HIGHS_EXPORT void productTranspose(vector<double>& result, const vector<double>& x) const;
  HIGHS_EXPORT void productQuad(vector<double>& result, const vector<double>& x,
                   const HighsInt debug_report = kDebugReportOff) const;
  HIGHS_EXPORT void productTransposeQuad(
      vector<double>& result_value, vector<HighsInt>& result_index,
      const HVector& x, const HighsInt debug_report = kDebugReportOff) const;
  // Methods for PRICE, including the creation and updating of the
  // partitioned row-wise matrix
  HIGHS_EXPORT void createRowwisePartitioned(const HighsSparseMatrix& matrix,
                                const int8_t* in_partition = NULL);
  HIGHS_EXPORT bool debugPartitionOk(const int8_t* in_partition) const;
  HIGHS_EXPORT void priceByColumn(const bool quad_precision, HVector& result,
                     const HVector& column,
                     const HighsInt debug_report = kDebugReportOff) const;
  HIGHS_EXPORT void priceByRow(const bool quad_precision, HVector& result,
                  const HVector& column,
                  const HighsInt debug_report = kDebugReportOff) const;
  HIGHS_EXPORT void priceByRowWithSwitch(
      const bool quad_precision, HVector& result, const HVector& column,
      const double expected_density, const HighsInt from_index,
      const double switch_density,
      const HighsInt debug_report = kDebugReportOff) const;
  HIGHS_EXPORT void update(const HighsInt var_in, const HighsInt var_out,
              const HighsSparseMatrix& matrix);
  double computeDot(const HVector& column, const HighsInt use_col) const {
    return computeDot(column.array, use_col);
  }

  HIGHS_EXPORT double computeDot(const std::vector<double>& array,
                    const HighsInt use_col) const;
  HIGHS_EXPORT void collectAj(HVector& column, const HighsInt use_col,
                 const double multiplier) const;

 private:
  HIGHS_EXPORT void priceByRowDenseResult(
      std::vector<double>& result, const HVector& column,
      const HighsInt from_index,
      const HighsInt debug_report = kDebugReportOff) const;
  HIGHS_EXPORT void priceByRowDenseResult(
      std::vector<HighsCDouble>& result, const HVector& column,
      const HighsInt from_index,
      const HighsInt debug_report = kDebugReportOff) const;
  HIGHS_EXPORT void debugReportRowPrice(const HighsInt iRow, const double multiplier,
                           const HighsInt to_iEl,
                           const vector<double>& result) const;
  HIGHS_EXPORT void debugReportRowPrice(const HighsInt iRow, const double multiplier,
                           const HighsInt to_iEl,
                           const vector<HighsCDouble>& result) const;
  HIGHS_EXPORT void debugReportRowPrice(const HighsInt iRow, const double multiplier,
                           const HighsInt to_iEl,
                           HighsSparseVectorSum& sum) const;
};

#endif
