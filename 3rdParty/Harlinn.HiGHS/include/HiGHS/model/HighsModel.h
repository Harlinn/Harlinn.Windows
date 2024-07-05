/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Written and engineered 2008-2021 at the University of Edinburgh    */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/*    Authors: Julian Hall, Ivet Galabova, Qi Huangfu, Leona Gottwald    */
/*    and Michael Feldmeier                                              */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**@file model/HighsModel.h
 * @brief
 */
#ifndef MODEL_HIGHS_MODEL_H_
#define MODEL_HIGHS_MODEL_H_

#include <vector>

#include "lp_data/HighsLp.h"
#include "model/HighsHessian.h"

class HighsModel;

class HighsModel {
 public:
  HighsLp lp_;
  HighsHessian hessian_;
  HIGHS_EXPORT bool operator==(const HighsModel& model) const;
  HIGHS_EXPORT bool equalButForNames(const HighsModel& model) const;
  bool isQp() const { return (this->hessian_.dim_ != 0); }
  bool isMip() const { return this->lp_.isMip(); }
  bool isEmpty() const {
    return (this->lp_.num_col_ == 0 && this->lp_.num_row_ == 0);
  }
  bool needsMods(const double infinite_cost) const {
    return this->lp_.needsMods(infinite_cost);
  }
  bool hasMods() const { return this->lp_.hasMods(); }
  HIGHS_EXPORT bool userCostScaleOk(const HighsInt user_cost_scale,
                       const double small_matrix_value,
                       const double large_matrix_value,
                       const double infinite_cost) const;
  HIGHS_EXPORT void userCostScale(const HighsInt user_cost_scale);
  HIGHS_EXPORT void clear();
  HIGHS_EXPORT double objectiveValue(const std::vector<double>& solution) const;
  HIGHS_EXPORT void objectiveGradient(const std::vector<double>& solution,
                         std::vector<double>& gradient) const;
};

#endif
