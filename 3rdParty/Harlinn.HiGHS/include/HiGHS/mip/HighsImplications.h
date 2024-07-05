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
#ifndef HIGHS_IMPLICATIONS_H_
#define HIGHS_IMPLICATIONS_H_

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

#include "mip/HighsDomain.h"
#include "mip/HighsDomainChange.h"
#include "util/HighsHashTree.h"

class HighsCliqueTable;
class HighsLpRelaxation;

class HighsImplications {
  HighsInt nextCleanupCall;

  struct Implics {
    std::vector<HighsDomainChange> implics;
    bool computed = false;
  };
  std::vector<Implics> implications;
  int64_t numImplications;

  HIGHS_EXPORT bool computeImplications(HighsInt col, bool val);

 public:
  struct VarBound {
    double coef;
    double constant;

    double minValue() const { return constant + std::min(coef, 0.0); }
    double maxValue() const { return constant + std::max(coef, 0.0); }
  };

 private:
  std::vector<HighsHashTree<HighsInt, VarBound>> vubs;
  std::vector<HighsHashTree<HighsInt, VarBound>> vlbs;

 public:
  const HighsMipSolver& mipsolver;
  std::vector<HighsSubstitution> substitutions;
  std::vector<uint8_t> colsubstituted;
  HighsImplications(const HighsMipSolver& mipsolver) : mipsolver(mipsolver) {
    HighsInt numcol = mipsolver.numCol();
    implications.resize(2 * static_cast<size_t>(numcol));
    colsubstituted.resize(numcol);
    vubs.resize(numcol);
    vlbs.resize(numcol);
    nextCleanupCall = mipsolver.numNonzero();
    numImplications = 0;
  }

  void reset() {
    colsubstituted.clear();
    colsubstituted.shrink_to_fit();
    implications.clear();
    implications.shrink_to_fit();

    HighsInt numcol = mipsolver.numCol();
    implications.resize(2 * static_cast<size_t>(numcol));
    colsubstituted.resize(numcol);
    numImplications = 0;
    vubs.clear();
    vubs.shrink_to_fit();
    vubs.resize(numcol);
    vlbs.clear();
    vlbs.shrink_to_fit();
    vlbs.resize(numcol);

    nextCleanupCall = mipsolver.numNonzero();
  }

  HighsInt getNumImplications() const { return numImplications; }

  const std::vector<HighsDomainChange>& getImplications(HighsInt col, bool val,
                                                        bool& infeasible) {
    HighsInt loc = 2 * col + val;
    if (!implications[loc].computed)
      infeasible = computeImplications(col, val);
    else
      infeasible = false;

    assert(implications[loc].computed);

    return implications[loc].implics;
  }

  bool implicationsCached(HighsInt col, bool val) {
    HighsInt loc = 2 * col + val;
    return implications[loc].computed;
  }

  HIGHS_EXPORT void addVUB(HighsInt col, HighsInt vubcol, double vubcoef,
              double vubconstant);

  HIGHS_EXPORT void addVLB(HighsInt col, HighsInt vlbcol, double vlbcoef,
              double vlbconstant);

  void columnTransformed(HighsInt col, double scale, double constant) {
    if (scale < 0) std::swap(vubs[col], vlbs[col]);

    auto transformVbd = [&](HighsInt, VarBound& vbd) {
      vbd.constant -= constant;
      vbd.constant /= scale;
      vbd.coef /= scale;
    };

    vlbs[col].for_each(transformVbd);
    vubs[col].for_each(transformVbd);
  }

  HIGHS_EXPORT std::pair<HighsInt, VarBound> getBestVub(HighsInt col,
                                           const HighsSolution& lpSolution,
                                           double& bestUb) const;

  HIGHS_EXPORT std::pair<HighsInt, VarBound> getBestVlb(HighsInt col,
                                           const HighsSolution& lpSolution,
                                           double& bestLb) const;

  HIGHS_EXPORT bool runProbing(HighsInt col, HighsInt& numReductions);

  HIGHS_EXPORT void rebuild(HighsInt ncols, const std::vector<HighsInt>& cIndex,
               const std::vector<HighsInt>& rIndex);

  HIGHS_EXPORT void buildFrom(const HighsImplications& init);

  HIGHS_EXPORT void separateImpliedBounds(const HighsLpRelaxation& lpRelaxation,
                             const std::vector<double>& sol,
                             HighsCutPool& cutpool, double feastol);

  HIGHS_EXPORT void cleanupVarbounds(HighsInt col);
};

#endif
