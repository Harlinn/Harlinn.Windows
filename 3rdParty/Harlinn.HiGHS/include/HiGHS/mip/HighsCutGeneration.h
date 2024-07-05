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
/**@file mip/HighsCutGeneration.h
 * @brief Class that generates cuts from single row relaxations
 *
 *
 */

#ifndef MIP_HIGHS_CUT_GENERATION_H_
#define MIP_HIGHS_CUT_GENERATION_H_

#include <cstdint>
#include <vector>

#include "util/HighsCDouble.h"
#include "util/HighsInt.h"
#include "util/HighsRandom.h"

class HighsLpRelaxation;
class HighsTransformedLp;
class HighsCutPool;
class HighsDomain;

/// Helper class to compute single-row relaxations from the current LP
/// relaxation by substituting bounds and aggregating rows
class HighsCutGeneration {
 private:
  const HighsLpRelaxation& lpRelaxation;
  HighsCutPool& cutpool;
  HighsRandom randgen;
  std::vector<HighsInt> cover;
  HighsCDouble coverweight;
  HighsCDouble lambda;
  std::vector<double> upper;
  std::vector<double> solval;
  std::vector<uint8_t> complementation;
  std::vector<uint8_t> isintegral;
  const double feastol;
  const double epsilon;

  double* vals;
  HighsInt* inds;
  HighsCDouble rhs;
  bool integralSupport;
  bool integralCoefficients;
  HighsInt rowlen;
  double initialScale;

  std::vector<HighsInt> integerinds;
  std::vector<double> deltas;

  HIGHS_EXPORT bool determineCover(bool lpSol = true);

  HIGHS_EXPORT void separateLiftedKnapsackCover();

  HIGHS_EXPORT bool separateLiftedMixedBinaryCover();

  HIGHS_EXPORT bool separateLiftedMixedIntegerCover();

  HIGHS_EXPORT bool cmirCutGenerationHeuristic(double minEfficacy,
                                  bool onlyInitialCMIRScale = false);

  HIGHS_EXPORT bool postprocessCut();

  HIGHS_EXPORT bool preprocessBaseInequality(bool& hasUnboundedInts, bool& hasGeneralInts,
                                bool& hasContinuous);

 public:
  HIGHS_EXPORT HighsCutGeneration(const HighsLpRelaxation& lpRelaxation,
                     HighsCutPool& cutpool);

  /// separates the LP solution for the given single row relaxation
  HIGHS_EXPORT bool generateCut(HighsTransformedLp& transLp, std::vector<HighsInt>& inds,
                   std::vector<double>& vals, double& rhs,
                   bool onlyInitialCMIRScale = false);

  /// generate a conflict from the given proof constraint which cuts of the
  /// given local domain
  HIGHS_EXPORT bool generateConflict(HighsDomain& localdom, std::vector<HighsInt>& proofinds,
                        std::vector<double>& proofvals, double& proofrhs);

  /// applies postprocessing to an externally generated cut and adds it to the
  /// cutpool if it is violated enough
  HIGHS_EXPORT bool finalizeAndAddCut(std::vector<HighsInt>& inds, std::vector<double>& vals,
                         double& rhs);
};

#endif
