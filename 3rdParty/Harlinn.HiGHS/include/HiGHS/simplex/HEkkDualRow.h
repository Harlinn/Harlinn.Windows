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
/**@file simplex/HEkkDualRow.h
 * @brief Dual simplex ratio test for HiGHS
 */
#ifndef SIMPLEX_HEKKDUALROW_H_
#define SIMPLEX_HEKKDUALROW_H_

#include <set>
#include <vector>

#include "simplex/HEkk.h"
#include "util/HVector.h"

const double kInitialTotalChange = 1e-12;
const double kInitialRemainTheta = 1e100;
const double kMaxSelectTheta = 1e18;

/**
 * @brief Dual simplex ratio test for HiGHS
 *
 * Performs the dual bound-flipping ratio test and some update
 * dual/flip tasks
 */
class HEkkDualRow {
 public:
  HEkkDualRow(HEkk& simplex) : ekk_instance_(simplex) {}

  /**
   * @brief Calls setupSlice to set up the packed indices and values for
   * the dual ratio test
   */
  HIGHS_EXPORT void setup();

  /**
   * @brief Set up the packed indices and values for the dual ratio test
   *
   * Done either for the whole pivotal row (see HEkkDualRow::setup), or
   * just for a slice (see HEkkDual::initSlice)
   */
  HIGHS_EXPORT void setupSlice(HighsInt size  //!< Dimension of slice
  );
  /**
   * @brief Clear the packed data by zeroing packCount and workCount
   */
  HIGHS_EXPORT void clear();

  /**
   * @brief Pack the indices and values for the row.
   *
   * Offset of numCol is used when packing row_ep
   */
  HIGHS_EXPORT void chooseMakepack(const HVector* row,    //!< Row to be packed
                      const HighsInt offset  //!< Offset for indices
  );
  /**
   * @brief Determine the possible variables - candidates for CHUZC
   *
   * TODO: Check with Qi what this is doing
   */
  HIGHS_EXPORT void choosePossible();

  /**
   * @brief Join pack of possible candidates in this row with possible
   * candidates in otherRow
   */
  HIGHS_EXPORT void chooseJoinpack(
      const HEkkDualRow* otherRow  //!< Other row to join with this
  );
  /**
   * @brief Chooses the entering variable via BFRT and EXPAND
   *
   * Can fail when there are excessive dual values due to EXPAND
   * perturbation not being relatively too small, returns positive if
   * dual unboundedness is suspected
   */
  HIGHS_EXPORT HighsInt chooseFinal();

  /**
   * @brief Identifies the groups of degenerate nodes in BFRT after a
   * heap sort of ratios
   */
  HIGHS_EXPORT bool chooseFinalWorkGroupQuad();
  HIGHS_EXPORT bool quadChooseFinalWorkGroupQuad();
  HIGHS_EXPORT bool chooseFinalWorkGroupHeap();

  HIGHS_EXPORT void chooseFinalLargeAlpha(
      HighsInt& breakIndex, HighsInt& breakGroup, HighsInt pass_workCount,
      const std::vector<std::pair<HighsInt, double>>& pass_workData,
      const std::vector<HighsInt>& pass_workGroup);

  HIGHS_EXPORT void reportWorkDataAndGroup(
      const std::string message, const HighsInt reportWorkCount,
      const std::vector<std::pair<HighsInt, double>>& reportWorkData,
      const std::vector<HighsInt>& reportWorkGroup);
  HIGHS_EXPORT bool compareWorkDataAndGroup();

  /**
   * @brief Update bounds when flips have occurred, and accumulate the
   * RHS for the FTRAN required to update the primal values after BFRT
   */
  HIGHS_EXPORT void updateFlip(HVector* bfrtColumn  //!< RHS for FTRAN BFRT
  );
  /**
   * @brief Update the dual values
   */
  HIGHS_EXPORT void updateDual(
      double theta  //!< Multiple of pivotal row to add HighsInt to duals
                    //      HighsInt variable_out  //!< Index of leaving column
  );
  /**
   * @brief Create a list of nonbasic free columns
   */
  HIGHS_EXPORT void createFreelist();

  /**
   * @brief Set a value of nonbasicMove for all free columns to
   * prevent their dual values from being changed
   */
  HIGHS_EXPORT void createFreemove(HVector* row_ep  //!< Row of \f$B^{-1}\f$ to be used to
                                       //!< compute pivotal row entry
  );
  /**
   * @brief Reset the nonbasicMove values for free columns
   */
  HIGHS_EXPORT void deleteFreemove();

  /**
   * @brief Delete the list of nonbasic free columns
   */
  HIGHS_EXPORT void deleteFreelist(
      HighsInt iColumn  //!< Index of column to remove from Freelist
  );

  /**
   * @brief Compute (contribution to) the Devex weight
   */
  HIGHS_EXPORT void computeDevexWeight(const HighsInt slice = -1);

  HIGHS_EXPORT HighsInt debugFindInWorkData(
      const HighsInt iCol, const HighsInt count,
      const std::vector<std::pair<HighsInt, double>>& workData_);
  HIGHS_EXPORT HighsInt debugChooseColumnInfeasibilities() const;
  HIGHS_EXPORT void debugReportBfrtVar(
      const HighsInt ix,
      const std::vector<std::pair<HighsInt, double>>& pass_workData) const;
  // References:
  HEkk& ekk_instance_;

  HighsInt workSize = -1;  //!< Size of the HEkkDualRow slice: Initialise it
                           //!< here to avoid compiler warning
  const HighsInt* workNumTotPermutation =
      nullptr;  //!< Pointer to ekk_instance_.numTotPermutation();
  const int8_t* workMove =
      nullptr;  //!< Pointer to ekk_instance_.basis_.nonbasicMove_;
  const double* workDual =
      nullptr;  //!< Pointer to ekk_instance_.info_.workDual_;
  const double* workRange =
      nullptr;  //!< Pointer to ekk_instance_.info_.workRange_;
  const HighsInt* work_devex_index =
      nullptr;  //!< Pointer to
                //!< ekk_instance_.info_.devex_index_;

  // Freelist:
  std::set<HighsInt> freeList;  //!< Freelist itself

  // packed data:
  HighsInt packCount = 0;           //!< number of packed indices/values
  std::vector<HighsInt> packIndex;  //!< Packed indices
  std::vector<double> packValue;    //!< Packed values

  // (Local) value of computed weight
  double computed_edge_weight = 0.;

  double workDelta = 0.;   //!< Local copy of dual.delta_primal
  double workAlpha = 0.;   //!< Original copy of pivotal computed row-wise
  double workTheta = 0.;   //!< Original copy of dual step workDual[workPivot] /
                           //!< workAlpha;
  HighsInt workPivot = 0;  //!< Index of the column entering the basis
  HighsInt workCount = 0;  //!< Number of BFRT flips

  std::vector<std::pair<HighsInt, double>>
      workData;  //!< Index-Value pairs for ratio test
  std::vector<HighsInt>
      workGroup;  //!< Pointers into workData for degenerate nodes in BFRT

  // Independent identifiers for heap-based sort in BFRT
  HighsInt alt_workCount = 0;
  std::vector<std::pair<HighsInt, double>> original_workData;
  std::vector<std::pair<HighsInt, double>> sorted_workData;
  std::vector<HighsInt> alt_workGroup;

  HighsSimplexAnalysis* analysis = nullptr;
};

#endif /* SIMPLEX_HEKKDUALROW_H_ */
