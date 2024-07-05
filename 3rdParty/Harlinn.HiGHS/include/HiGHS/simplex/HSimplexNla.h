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
/**@file simplex/HSimplexNla.h
 *
 * @brief Interface to HFactor allowing non-HFactor updates, NLA-only
 * scaling and shifting of NLA analysis below simplex level.
 */
#ifndef HSIMPLEXNLA_H_
#define HSIMPLEXNLA_H_

#include "lp_data/HighsDebug.h"
#include "simplex/HighsSimplexAnalysis.h"
#include "simplex/SimplexStruct.h"
#include "util/HFactor.h"

const HighsInt kReportItemLimit = 25;
const double kDensityForIndexing = 0.4;

struct ProductFormUpdate {
  bool valid_ = false;
  HighsInt num_row_;
  HighsInt update_count_;
  vector<HighsInt> pivot_index_;
  vector<double> pivot_value_;
  vector<HighsInt> start_;
  vector<HighsInt> index_;
  vector<double> value_;
  HIGHS_EXPORT void clear();
  HIGHS_EXPORT void setup(const HighsInt num_row, const double expected_density);
  HIGHS_EXPORT HighsInt update(HVector* aq, HighsInt* iRow);
  HIGHS_EXPORT void btran(HVector& rhs) const;
  HIGHS_EXPORT void ftran(HVector& rhs) const;
};

struct FrozenBasis {
  bool valid_ = false;
  HighsInt prev_;
  HighsInt next_;
  ProductFormUpdate update_;
  SimplexBasis basis_;
  std::vector<double> dual_edge_weight_;
  HIGHS_EXPORT void clear();
};

struct SimplexIterate {
  bool valid_ = false;
  SimplexBasis basis_;
  InvertibleRepresentation invert_;
  std::vector<double> dual_edge_weight_;
  HIGHS_EXPORT void clear();
};

class HSimplexNla {
 private:
  HIGHS_EXPORT void setup(const HighsLp* lp, HighsInt* basic_index,
             const HighsOptions* options, HighsTimer* timer,
             HighsSimplexAnalysis* analysis,
             const HighsSparseMatrix* factor_a_matrix,
             const double factor_pivot_threshold);

  HIGHS_EXPORT void setLpAndScalePointers(const HighsLp* lp);
  HIGHS_EXPORT void setBasicIndexPointers(HighsInt* basic_index);
  HIGHS_EXPORT void setPointers(const HighsLp* for_lp,
                   const HighsSparseMatrix* factor_a_matrix = NULL,
                   HighsInt* basic_index = NULL,
                   const HighsOptions* options = NULL, HighsTimer* timer = NULL,
                   HighsSimplexAnalysis* analysis = NULL);
  HIGHS_EXPORT void clear();
  HIGHS_EXPORT HighsInt invert();
  HIGHS_EXPORT void btran(HVector& rhs, const double expected_density,
             HighsTimerClock* factor_timer_clock_pointer = NULL) const;
  HIGHS_EXPORT void ftran(HVector& rhs, const double expected_density,
             HighsTimerClock* factor_timer_clock_pointer = NULL) const;
  HIGHS_EXPORT void btranInScaledSpace(
      HVector& rhs, const double expected_density,
      HighsTimerClock* factor_timer_clock_pointer = NULL) const;
  HIGHS_EXPORT void ftranInScaledSpace(
      HVector& rhs, const double expected_density,
      HighsTimerClock* factor_timer_clock_pointer = NULL) const;
  HIGHS_EXPORT void frozenBtran(HVector& rhs) const;
  HIGHS_EXPORT void frozenFtran(HVector& rhs) const;
  HIGHS_EXPORT void update(HVector* aq, HVector* ep, HighsInt* iRow, HighsInt* hint);

  HIGHS_EXPORT void frozenBasisClearAllData();
  HIGHS_EXPORT void frozenBasisClearAllUpdate();
  HIGHS_EXPORT bool frozenBasisAllDataClear();
  HIGHS_EXPORT bool frozenBasisIdValid(const HighsInt frozen_basis_id) const;
  HIGHS_EXPORT bool frozenBasisHasInvert(const HighsInt frozen_basis_id) const;
  HIGHS_EXPORT HighsInt freeze(const SimplexBasis& basis, const double col_aq_density);
  HIGHS_EXPORT void unfreeze(const HighsInt unfreeze_basis_id, SimplexBasis& basis);
  HIGHS_EXPORT void putInvert();
  HIGHS_EXPORT void getInvert();

  HIGHS_EXPORT void transformForUpdate(HVector* column, HVector* row_ep,
                          const HighsInt variable_in, const HighsInt row_out);
  HIGHS_EXPORT double variableScaleFactor(const HighsInt iVar) const;
  HIGHS_EXPORT double basicColScaleFactor(const HighsInt iCol) const;
  HIGHS_EXPORT double pivotInScaledSpace(const HVector* aq, const HighsInt variable_in,
                            const HighsInt row_out) const;
  HIGHS_EXPORT void setPivotThreshold(const double new_pivot_threshold);

  HIGHS_EXPORT void passLpPointer(const HighsLp* lp);
  HIGHS_EXPORT void passScalePointer(const HighsScale* scale);
  HIGHS_EXPORT void applyBasisMatrixColScale(HVector& rhs) const;
  HIGHS_EXPORT void applyBasisMatrixRowScale(HVector& rhs) const;
  HIGHS_EXPORT void unapplyBasisMatrixRowScale(HVector& rhs) const;
  HIGHS_EXPORT double rowEp2NormInScaledSpace(const HighsInt iRow,
                                 const HVector& row_ep) const;
  HIGHS_EXPORT void addCols(const HighsLp* updated_lp);
  HIGHS_EXPORT void addRows(const HighsLp* updated_lp, HighsInt* basic_index,
               const HighsSparseMatrix* scaled_ar_matrix);
  HIGHS_EXPORT bool sparseLoopStyle(const HighsInt count, const HighsInt dim,
                       HighsInt& to_entry) const;
  HIGHS_EXPORT void reportVector(const std::string message, const HighsInt num_index,
                    const vector<double> vector_value,
                    const vector<HighsInt> vector_index,
                    const bool force) const;
  HIGHS_EXPORT void reportArray(const std::string message, const HVector* vector,
                   const bool force = false) const;
  HIGHS_EXPORT void reportArray(const std::string message, const HighsInt offset,
                   const HVector* vector, const bool force = false) const;
  HIGHS_EXPORT void reportArraySparse(const std::string message, const HVector* vector,
                         const bool force = false) const;
  HIGHS_EXPORT void reportArraySparse(const std::string message, const HighsInt offset,
                         const HVector* vector, const bool force = false) const;
  HIGHS_EXPORT void reportPackValue(const std::string message, const HVector* vector,
                       const bool force = false) const;
  // Debug methods
  HIGHS_EXPORT HighsDebugStatus debugCheckData(const std::string message = "") const;
  HIGHS_EXPORT HighsDebugStatus debugCheckInvert(const std::string message,
                                    const HighsInt alt_debug_level = -1) const;
  HIGHS_EXPORT double debugInvertResidualError(const bool transposed,
                                  const HVector& solution,
                                  HVector& residual) const;
  HIGHS_EXPORT HighsDebugStatus debugReportInvertSolutionError(const bool transposed,
                                                  const HVector& true_solution,
                                                  const HVector& solution,
                                                  HVector& residual,
                                                  const bool force) const;
  HIGHS_EXPORT HighsDebugStatus debugReportInvertSolutionError(
      const std::string source, const bool transposed,
      const double solve_error_norm, const double residual_error_norm,
      const bool force) const;

  // References:
  //
  // Pointers:

  // Class data members
  const HighsLp* lp_;
  const HighsScale* scale_;
  HighsInt* basic_index_;
  const HighsOptions* options_;
  HighsTimer* timer_;
  HighsSimplexAnalysis* analysis_;

  HFactor factor_;

  bool report_;
  double build_synthetic_tick_;

  // Frozen basis data
  HighsInt first_frozen_basis_id_ = kNoLink;
  HighsInt last_frozen_basis_id_ = kNoLink;
  vector<FrozenBasis> frozen_basis_;
  ProductFormUpdate update_;

  // Simplex iterate data
  SimplexIterate simplex_iterate_;

  friend class HEkk;
  friend class HEkkPrimal;
  friend class HEkkDual;
};

#endif /* HSIMPLEXNLA_H_ */
