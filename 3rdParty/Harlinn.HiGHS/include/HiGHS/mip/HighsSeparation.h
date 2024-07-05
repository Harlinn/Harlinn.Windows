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
#ifndef HIGHS_SEPARATION_H_
#define HIGHS_SEPARATION_H_

#include <cstdint>
#include <vector>

#include "mip/HighsCutPool.h"
#include "mip/HighsLpRelaxation.h"
#include "mip/HighsSeparator.h"

class HighsMipSolver;
class HighsImplications;
class HighsCliqueTable;

class HighsSeparation {
 public:
  HIGHS_EXPORT HighsInt separationRound(HighsDomain& propdomain,
                           HighsLpRelaxation::Status& status);

  HIGHS_EXPORT void separate(HighsDomain& propdomain);

  void setLpRelaxation(HighsLpRelaxation* lp) { this->lp = lp; }

  HIGHS_EXPORT HighsSeparation(const HighsMipSolver& mipsolver);

 private:
  HighsInt implBoundClock;
  HighsInt cliqueClock;
  std::vector<std::unique_ptr<HighsSeparator>> separators;
  HighsCutSet cutset;
  HighsLpRelaxation* lp;
};

#endif
