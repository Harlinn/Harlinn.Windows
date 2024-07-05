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
/**@file util/HighsLinearSumBounds.h
 * @brief Data structure to compute and update bounds on a linear sum of
 * variables with finite or infinite bounds
 */

#ifndef HIGHS_LINEAR_SUM_BOUNDS_H_
#define HIGHS_LINEAR_SUM_BOUNDS_H_

#include <vector>

#include "lp_data/HConst.h"
#include "util/HighsCDouble.h"

class HighsLinearSumBounds {
  std::vector<HighsCDouble> sumLowerOrig;
  std::vector<HighsCDouble> sumUpperOrig;
  std::vector<HighsInt> numInfSumLowerOrig;
  std::vector<HighsInt> numInfSumUpperOrig;
  std::vector<HighsCDouble> sumLower;
  std::vector<HighsCDouble> sumUpper;
  std::vector<HighsInt> numInfSumLower;
  std::vector<HighsInt> numInfSumUpper;
  const double* varLower;
  const double* varUpper;
  const double* implVarLower;
  const double* implVarUpper;
  const HighsInt* implVarLowerSource;
  const HighsInt* implVarUpperSource;

 public:
  void setNumSums(HighsInt numSums) {
    numInfSumLower.resize(numSums);
    numInfSumUpper.resize(numSums);
    sumLower.resize(numSums);
    sumUpper.resize(numSums);
    numInfSumLowerOrig.resize(numSums);
    numInfSumUpperOrig.resize(numSums);
    sumLowerOrig.resize(numSums);
    sumUpperOrig.resize(numSums);
  }

  void setBoundArrays(const double* varLower, const double* varUpper,
                      const double* implVarLower, const double* implVarUpper,
                      const HighsInt* implVarLowerSource,
                      const HighsInt* implVarUpperSource) {
    this->varLower = varLower;
    this->varUpper = varUpper;
    this->implVarLower = implVarLower;
    this->implVarUpper = implVarUpper;
    this->implVarLowerSource = implVarLowerSource;
    this->implVarUpperSource = implVarUpperSource;
  }

  void sumScaled(HighsInt sum, double scale) {
    sumLowerOrig[sum] *= scale;
    sumUpperOrig[sum] *= scale;
    sumLower[sum] *= scale;
    sumUpper[sum] *= scale;

    if (scale < 0) {
      std::swap(sumLower[sum], sumUpper[sum]);
      std::swap(sumLowerOrig[sum], sumUpperOrig[sum]);
      std::swap(numInfSumLower[sum], numInfSumUpper[sum]);
      std::swap(numInfSumLowerOrig[sum], numInfSumUpperOrig[sum]);
    }
  }

  HIGHS_EXPORT void add(HighsInt sum, HighsInt var, double coefficient);

  HIGHS_EXPORT void remove(HighsInt sum, HighsInt var, double coefficient);

  HIGHS_EXPORT void updatedVarUpper(HighsInt sum, HighsInt var, double coefficient,
                       double oldVarUpper);

  HIGHS_EXPORT void updatedVarLower(HighsInt sum, HighsInt var, double coefficient,
                       double oldVarLower);

  HIGHS_EXPORT void updatedImplVarUpper(HighsInt sum, HighsInt var, double coefficient,
                           double oldImplVarUpper,
                           HighsInt oldImplVarUpperSource);

  HIGHS_EXPORT void updatedImplVarLower(HighsInt sum, HighsInt var, double coefficient,
                           double oldImplVarLower,
                           HighsInt oldImplVarLowerSource);

  HIGHS_EXPORT double getResidualSumLower(HighsInt sum, HighsInt var,
                             double coefficient) const;

  HIGHS_EXPORT double getResidualSumUpper(HighsInt sum, HighsInt var,
                             double coefficient) const;

  HIGHS_EXPORT double getResidualSumLowerOrig(HighsInt sum, HighsInt var,
                                 double coefficient) const;

  HIGHS_EXPORT double getResidualSumUpperOrig(HighsInt sum, HighsInt var,
                                 double coefficient) const;

  double getSumLowerOrig(HighsInt sum) const {
    return numInfSumLowerOrig[sum] == 0 ? double(sumLowerOrig[sum])
                                        : -kHighsInf;
  }

  double getSumUpperOrig(HighsInt sum) const {
    return numInfSumUpperOrig[sum] == 0 ? double(sumUpperOrig[sum]) : kHighsInf;
  }

  double getSumLower(HighsInt sum) const {
    return numInfSumLower[sum] == 0 ? double(sumLower[sum]) : -kHighsInf;
  }

  double getSumUpper(HighsInt sum) const {
    return numInfSumUpper[sum] == 0 ? double(sumUpper[sum]) : kHighsInf;
  }

  double getSumLower(HighsInt sum, double offset) const {
    return numInfSumLower[sum] == 0 ? double(sumLower[sum] + offset)
                                    : -kHighsInf;
  }

  double getSumUpper(HighsInt sum, double offset) const {
    return numInfSumUpper[sum] == 0 ? double(sumUpper[sum] + offset)
                                    : kHighsInf;
  }

  double getSumLower(HighsInt sum, HighsCDouble offset) const {
    return numInfSumLower[sum] == 0 ? double(sumLower[sum] + offset)
                                    : -kHighsInf;
  }

  double getSumUpper(HighsInt sum, HighsCDouble offset) const {
    return numInfSumUpper[sum] == 0 ? double(sumUpper[sum] + offset)
                                    : kHighsInf;
  }

  HighsInt getNumInfSumLower(HighsInt sum) const { return numInfSumLower[sum]; }

  HighsInt getNumInfSumUpper(HighsInt sum) const { return numInfSumUpper[sum]; }

  HighsInt getNumInfSumLowerOrig(HighsInt sum) const {
    return numInfSumLowerOrig[sum];
  }

  HighsInt getNumInfSumUpperOrig(HighsInt sum) const {
    return numInfSumUpperOrig[sum];
  }

  HIGHS_EXPORT void shrink(const std::vector<HighsInt>& newIndices, HighsInt newSize);
};

#endif
