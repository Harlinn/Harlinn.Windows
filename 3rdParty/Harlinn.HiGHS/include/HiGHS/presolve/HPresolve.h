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
/**@file presolve/HPresolve.h
 * @brief
 */
#ifndef PRESOLVE_HIGHS_PRESOLVE_H_
#define PRESOLVE_HIGHS_PRESOLVE_H_
#include <cassert>
#include <cmath>
#include <list>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>

#include "lp_data/HConst.h"
#include "lp_data/HStruct.h"
#include "lp_data/HighsLp.h"
#include "lp_data/HighsOptions.h"
#include "mip/HighsMipSolver.h"
#include "presolve/HPresolveAnalysis.h"
#include "util/HighsCDouble.h"
#include "util/HighsHash.h"
#include "util/HighsLinearSumBounds.h"
#include "util/HighsMatrixSlice.h"

namespace presolve {

class HighsPostsolveStack;

class HPresolve {
  // pointer to model and options that where presolved
  HighsLp* model;
  const HighsOptions* options;
  HighsTimer* timer;
  HighsMipSolver* mipsolver = nullptr;
  double primal_feastol;
  HighsInt run_clock = -1;

  // triplet storage
  std::vector<double> Avalue;
  std::vector<HighsInt> Arow;
  std::vector<HighsInt> Acol;

  // linked list links for column based links for each nonzero
  std::vector<HighsInt> colhead;
  std::vector<HighsInt> Anext;
  std::vector<HighsInt> Aprev;

  // splay tree links for row based iteration and nonzero lookup
  std::vector<HighsInt> rowroot;
  std::vector<HighsInt> ARleft;
  std::vector<HighsInt> ARright;

  // length of rows and columns
  std::vector<HighsInt> rowsize;
  std::vector<HighsInt> rowsizeInteger;
  std::vector<HighsInt> rowsizeImplInt;
  std::vector<HighsInt> colsize;

  // vector to store the nonzero positions of a row
  std::vector<HighsInt> rowpositions;

  // stack to reuse free slots
  std::vector<HighsInt> freeslots;

  // vectors holding implied bounds on primal and dual variables as well as
  // their origins
  std::vector<double> implColLower;
  std::vector<double> implColUpper;
  std::vector<HighsInt> colLowerSource;
  std::vector<HighsInt> colUpperSource;
  std::vector<double> rowDualLower;
  std::vector<double> rowDualUpper;
  std::vector<double> implRowDualLower;
  std::vector<double> implRowDualUpper;
  std::vector<HighsInt> rowDualLowerSource;
  std::vector<HighsInt> rowDualUpperSource;
  std::vector<std::set<HighsInt>> colImplSourceByRow;
  std::vector<std::set<HighsInt>> implRowDualSourceByCol;

  // implied bounds on values of primal and dual rows computed from the bounds
  // of primal and dual variables
  HighsLinearSumBounds impliedRowBounds;
  HighsLinearSumBounds impliedDualRowBounds;

  std::vector<HighsInt> changedRowIndices;
  std::vector<uint8_t> changedRowFlag;
  std::vector<HighsInt> changedColIndices;
  std::vector<uint8_t> changedColFlag;

  std::vector<std::pair<HighsInt, HighsInt>> substitutionOpportunities;

  // set with the sizes and indices of equation rows sorted by the size and a
  // vector to access there iterator positions in the set by index for quick
  // removal
  std::set<std::pair<HighsInt, HighsInt>> equations;
  std::vector<std::set<std::pair<HighsInt, HighsInt>>::iterator> eqiters;

  bool shrinkProblemEnabled;
  size_t reductionLimit;

  // vectors storing singleton rows and columns
  std::vector<HighsInt> singletonRows;
  std::vector<HighsInt> singletonColumns;

  // flags to mark rows/columns as deleted
  std::vector<uint8_t> rowDeleted;
  std::vector<uint8_t> colDeleted;

  std::vector<uint16_t> numProbes;

  int64_t probingContingent;
  HighsInt probingNumDelCol;
  HighsInt numProbed;

  // counters for number of deleted rows and columns
  HighsInt numDeletedRows;
  HighsInt numDeletedCols;

  // store old problem sizes to compute percentage reductions in
  // presolve loop
  HighsInt oldNumCol;
  HighsInt oldNumRow;
  bool probingEarlyAbort;

  enum class Result {
    kOk,
    kPrimalInfeasible,
    kDualInfeasible,
    kStopped,
  };
  HighsPresolveStatus presolve_status_;
  HPresolveAnalysis analysis_;

  // private functions for different shared functionality and matrix
  // modification

  HIGHS_EXPORT void link(HighsInt pos);

  HIGHS_EXPORT void unlink(HighsInt pos);

  HIGHS_EXPORT void markChangedRow(HighsInt row);

  HIGHS_EXPORT void markChangedCol(HighsInt col);

  HIGHS_EXPORT double getMaxAbsColVal(HighsInt col) const;

  HIGHS_EXPORT double getMaxAbsRowVal(HighsInt row) const;

  HIGHS_EXPORT void updateColImpliedBounds(HighsInt row, HighsInt col, double val);

  HIGHS_EXPORT void recomputeColImpliedBounds(HighsInt row);

  HIGHS_EXPORT void recomputeRowDualImpliedBounds(HighsInt col);

  HIGHS_EXPORT void updateRowDualImpliedBounds(HighsInt row, HighsInt col, double val);

  HIGHS_EXPORT bool rowCoefficientsIntegral(HighsInt row, double scale) const;

  HIGHS_EXPORT bool isImpliedFree(HighsInt col) const;

  HIGHS_EXPORT bool isDualImpliedFree(HighsInt row) const;

  HIGHS_EXPORT void dualImpliedFreeGetRhsAndRowType(HighsInt row, double& rhs,
                                       HighsPostsolveStack::RowType& rowType,
                                       bool relaxRowDualBounds = false);

  HIGHS_EXPORT bool isImpliedIntegral(HighsInt col);

  HIGHS_EXPORT bool isImpliedInteger(HighsInt col);

  HIGHS_EXPORT bool isLowerImplied(HighsInt col) const;

  HIGHS_EXPORT bool isUpperImplied(HighsInt col) const;

  HIGHS_EXPORT HighsInt countFillin(HighsInt row);

  HIGHS_EXPORT bool checkFillin(HighsHashTable<HighsInt, HighsInt>& fillinCache,
                   HighsInt row, HighsInt col);

  HIGHS_EXPORT void reinsertEquation(HighsInt row);

#ifndef NDEBUG
  HIGHS_EXPORT void debugPrintRow(HighsPostsolveStack& postsolve_stack, HighsInt row);
#endif

  HIGHS_EXPORT HighsInt findNonzero(HighsInt row, HighsInt col);

  HIGHS_EXPORT bool okFromCSC(const std::vector<double>& Aval,
                 const std::vector<HighsInt>& Aindex,
                 const std::vector<HighsInt>& Astart);

  HIGHS_EXPORT bool okFromCSR(const std::vector<double>& ARval,
                 const std::vector<HighsInt>& ARindex,
                 const std::vector<HighsInt>& ARstart);

  HIGHS_EXPORT void toCSC(std::vector<double>& Aval, std::vector<HighsInt>& Aindex,
             std::vector<HighsInt>& Astart);

  HIGHS_EXPORT void toCSR(std::vector<double>& ARval, std::vector<HighsInt>& ARindex,
             std::vector<HighsInt>& ARstart);

  HIGHS_EXPORT void storeRow(HighsInt row);

  HIGHS_EXPORT HighsTripletPositionSlice getStoredRow() const;

  HIGHS_EXPORT HighsTripletListSlice getColumnVector(HighsInt col) const;

  HIGHS_EXPORT HighsTripletTreeSlicePreOrder getRowVector(HighsInt row) const;

  HIGHS_EXPORT HighsTripletTreeSliceInOrder getSortedRowVector(HighsInt row) const;

  HIGHS_EXPORT void markRowDeleted(HighsInt row);

  HIGHS_EXPORT void markColDeleted(HighsInt col);

  HIGHS_EXPORT void fixColToLower(HighsPostsolveStack& postsolve_stack, HighsInt col);

  HIGHS_EXPORT void fixColToUpper(HighsPostsolveStack& postsolve_stack, HighsInt col);

  HIGHS_EXPORT void fixColToZero(HighsPostsolveStack& postsolve_stack, HighsInt col);

  HIGHS_EXPORT void transformColumn(HighsPostsolveStack& postsolve_stack, HighsInt col,
                       double scale, double constant);

  HIGHS_EXPORT void scaleRow(HighsInt row, double scale, bool integral = false);

  HIGHS_EXPORT void scaleStoredRow(HighsInt row, double scale, bool integral = false);

  HIGHS_EXPORT void substitute(HighsInt row, HighsInt col, double rhs);

  HIGHS_EXPORT void changeColUpper(HighsInt col, double newUpper);

  HIGHS_EXPORT void changeColLower(HighsInt col, double newLower);

  HIGHS_EXPORT void changeRowDualUpper(HighsInt row, double newUpper);

  HIGHS_EXPORT void changeRowDualLower(HighsInt row, double newLower);

  HIGHS_EXPORT void changeImplColUpper(HighsInt col, double newUpper, HighsInt originRow);

  HIGHS_EXPORT void changeImplColLower(HighsInt col, double newLower, HighsInt originRow);

  HIGHS_EXPORT void changeImplRowDualUpper(HighsInt row, double newUpper,
                              HighsInt originCol);

  HIGHS_EXPORT void changeImplRowDualLower(HighsInt row, double newLower,
                              HighsInt originCol);

  HIGHS_EXPORT void scaleMIP(HighsPostsolveStack& postsolve_stack);

  HIGHS_EXPORT Result applyConflictGraphSubstitutions(HighsPostsolveStack& postsolve_stack);

  HIGHS_EXPORT Result fastPresolveLoop(HighsPostsolveStack& postsolve_stack);

  HIGHS_EXPORT Result presolve(HighsPostsolveStack& postsolve_stack);

  HIGHS_EXPORT Result checkLimits(HighsPostsolveStack& postsolve_stack);

  HIGHS_EXPORT void storeCurrentProblemSize();

  HIGHS_EXPORT double problemSizeReduction();

 public:
  // for LP presolve
  HIGHS_EXPORT bool okSetInput(HighsLp& model_, const HighsOptions& options_,
                  const HighsInt presolve_reduction_limit,
                  HighsTimer* timer = nullptr);

  // for MIP presolve
  HIGHS_EXPORT bool okSetInput(HighsMipSolver& mipsolver,
                  const HighsInt presolve_reduction_limit);

  void setReductionLimit(size_t reductionLimit) {
    this->reductionLimit = reductionLimit;
  }

  HighsInt numNonzeros() const { return int(Avalue.size() - freeslots.size()); }

  HIGHS_EXPORT void shrinkProblem(HighsPostsolveStack& postsolve_stack);

  HIGHS_EXPORT void addToMatrix(const HighsInt row, const HighsInt col, const double val);

  HIGHS_EXPORT Result runProbing(HighsPostsolveStack& postsolve_stack);

  HIGHS_EXPORT Result dominatedColumns(HighsPostsolveStack& postsolve_stack);

  HIGHS_EXPORT Result doubletonEq(HighsPostsolveStack& postsolve_stack, HighsInt row,
                     HighsPostsolveStack::RowType rowType);

  HIGHS_EXPORT Result singletonRow(HighsPostsolveStack& postsolve_stack, HighsInt row);

  HIGHS_EXPORT Result emptyCol(HighsPostsolveStack& postsolve_stack, HighsInt col);

  HIGHS_EXPORT Result singletonCol(HighsPostsolveStack& postsolve_stack, HighsInt col);

  HIGHS_EXPORT Result rowPresolve(HighsPostsolveStack& postsolve_stack, HighsInt row);

  HIGHS_EXPORT Result colPresolve(HighsPostsolveStack& postsolve_stack, HighsInt col);

  HIGHS_EXPORT Result initialRowAndColPresolve(HighsPostsolveStack& postsolve_stack);

  HIGHS_EXPORT HighsModelStatus run(HighsPostsolveStack& postsolve_stack);

  HIGHS_EXPORT void computeIntermediateMatrix(std::vector<HighsInt>& flagRow,
                                 std::vector<HighsInt>& flagCol,
                                 size_t& numreductions);

  HIGHS_EXPORT void substitute(HighsInt substcol, HighsInt staycol, double offset,
                  double scale);

  HIGHS_EXPORT void removeFixedCol(HighsInt col);

  HIGHS_EXPORT void removeRow(HighsInt row);

  HIGHS_EXPORT Result removeDependentEquations(HighsPostsolveStack& postsolve_stack);

  HIGHS_EXPORT Result removeDependentFreeCols(HighsPostsolveStack& postsolve_stack);

  HIGHS_EXPORT Result aggregator(HighsPostsolveStack& postsolve_stack);

  HIGHS_EXPORT Result removeRowSingletons(HighsPostsolveStack& postsolve_stack);

  HIGHS_EXPORT Result presolveColSingletons(HighsPostsolveStack& postsolve_stack);

  HIGHS_EXPORT Result presolveChangedRows(HighsPostsolveStack& postsolve_stack);

  HIGHS_EXPORT Result presolveChangedCols(HighsPostsolveStack& postsolve_stack);

  HIGHS_EXPORT Result removeDoubletonEquations(HighsPostsolveStack& postsolve_stack);

  HIGHS_EXPORT HighsInt strengthenInequalities();

  HIGHS_EXPORT HighsInt detectImpliedIntegers();

  HIGHS_EXPORT Result detectParallelRowsAndCols(HighsPostsolveStack& postsolve_stack);

  HIGHS_EXPORT Result sparsify(HighsPostsolveStack& postsolve_stack);

  HIGHS_EXPORT void setRelaxedImpliedBounds();

  const HighsPresolveLog& getPresolveLog() const {
    return analysis_.presolve_log_;
  }

  HighsPresolveStatus getPresolveStatus() const { return presolve_status_; }

  HIGHS_EXPORT HighsInt debugGetCheckCol() const;
  HIGHS_EXPORT HighsInt debugGetCheckRow() const;

  // Not currently called
  HIGHS_EXPORT static void debug(const HighsLp& lp, const HighsOptions& options);
};

}  // namespace presolve
#endif
