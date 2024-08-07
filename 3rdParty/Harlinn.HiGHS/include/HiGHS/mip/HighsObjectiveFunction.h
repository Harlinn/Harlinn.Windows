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
#ifndef HIGHS_OBJECTIVE_FUNCTION_H_
#define HIGHS_OBJECTIVE_FUNCTION_H_

#include <algorithm>
#include <cassert>
#include <vector>

#include "util/HighsInt.h"

class HighsCliqueTable;
class HighsDomain;
class HighsLp;
class HighsMipSolver;

class HighsObjectiveFunction {
  const HighsLp* model;
  double objIntScale;
  HighsInt numIntegral;
  HighsInt numBinary;
  std::vector<HighsInt> objectiveNonzeros;
  std::vector<double> objectiveVals;
  std::vector<HighsInt> cliquePartitionStart;
  std::vector<HighsInt> colToPartition;

 public:
  HIGHS_EXPORT HighsObjectiveFunction(const HighsMipSolver& mipsolver);

  HIGHS_EXPORT void setupCliquePartition(const HighsDomain& globaldom,
                            HighsCliqueTable& cliqueTable);

  HIGHS_EXPORT void checkIntegrality(double epsilon);

  /// returns the vector of column indices with nonzero objective value
  /// They will be ordered so that binary columns come first
  const std::vector<HighsInt>& getObjectiveNonzeros() const {
    return objectiveNonzeros;
  }

  const std::vector<double>& getObjectiveValuesPacked() const {
    return objectiveVals;
  }

  HighsInt getNumBinariesInObjective() const { return numBinary; }

  const std::vector<HighsInt>& getCliquePartitionStarts() const {
    return cliquePartitionStart;
  }

  HighsInt getNumCliquePartitions() const {
    return cliquePartitionStart.size() - 1;
  }

  HighsInt getColCliquePartition(HighsInt col) const {
    return colToPartition[col];
  }

  double integralScale() const { return objIntScale; }

  bool isIntegral() const { return objIntScale != 0.0; }

  bool isZero() const { return objectiveNonzeros.empty(); }
};

#endif
