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
#ifndef HIGHS_DOMAIN_H_
#define HIGHS_DOMAIN_H_

#include <cstdint>
#include <deque>
#include <memory>
#include <set>
#include <vector>

#include "mip/HighsDomainChange.h"
#include "mip/HighsMipSolver.h"
#include "util/HighsCDouble.h"
#include "util/HighsRbTree.h"

class HighsCutPool;
class HighsConflictPool;
class HighsObjectiveFunction;

class HighsDomain {
 public:
  struct Reason {
    HighsInt type;
    HighsInt index;

    enum {
      kBranching = -1,
      kUnknown = -2,
      kModelRowUpper = -3,
      kModelRowLower = -4,
      kCliqueTable = -5,
      kConflictingBounds = -6,
      kObjective = -7,
    };
    static Reason branching() { return Reason{kBranching, 0}; }
    static Reason unspecified() { return Reason{kUnknown, 0}; }
    static Reason cliqueTable(HighsInt col, HighsInt val) {
      return Reason{kCliqueTable, 2 * col + val};
    }
    static Reason modelRowUpper(HighsInt row) {
      return Reason{kModelRowUpper, row};
    }
    static Reason modelRowLower(HighsInt row) {
      return Reason{kModelRowLower, row};
    }
    static Reason cut(HighsInt cutpool, HighsInt cut) {
      return Reason{cutpool, cut};
    }
    static Reason conflictingBounds(HighsInt pos) {
      return Reason{kConflictingBounds, pos};
    }
    static Reason objective() { return Reason{kObjective, 0}; }
  };

  class ConflictSet {
    friend class HighsDomain;
    HighsDomain& localdom;
    HighsDomain& globaldom;

   public:
    struct LocalDomChg {
      HighsInt pos;
      mutable HighsDomainChange domchg;

      bool operator<(const LocalDomChg& other) const { return pos < other.pos; }
    };

    HIGHS_EXPORT ConflictSet(HighsDomain& localdom);

    HIGHS_EXPORT void conflictAnalysis(HighsConflictPool& conflictPool);
    HIGHS_EXPORT void conflictAnalysis(const HighsInt* proofinds, const double* proofvals,
                          HighsInt prooflen, double proofrhs,
                          HighsConflictPool& conflictPool);

   private:
    std::set<LocalDomChg> reasonSideFrontier;
    std::set<LocalDomChg> reconvergenceFrontier;
    std::vector<std::set<LocalDomChg>::iterator> resolveQueue;
    std::vector<LocalDomChg> resolvedDomainChanges;

    struct ResolveCandidate {
      double delta;
      double baseBound;
      double prio;
      HighsInt boundPos;
      HighsInt valuePos;

      bool operator<(const ResolveCandidate& other) const {
        if (prio > other.prio) return true;
        if (other.prio > prio) return false;

        return boundPos < other.boundPos;
      }
    };

    std::vector<ResolveCandidate> resolveBuffer;

    HIGHS_EXPORT void pushQueue(std::set<LocalDomChg>::iterator domchgPos);
    HIGHS_EXPORT std::set<LocalDomChg>::iterator popQueue();
    HIGHS_EXPORT void clearQueue();
    HIGHS_EXPORT HighsInt queueSize();
    HIGHS_EXPORT bool resolvable(HighsInt domChgPos);

    HIGHS_EXPORT HighsInt resolveDepth(std::set<LocalDomChg>& frontier, HighsInt depthLevel,
                          HighsInt stopSize, HighsInt minResolve = 0,
                          bool increaseConflictScore = false);

    HIGHS_EXPORT HighsInt computeCuts(HighsInt depthLevel, HighsConflictPool& conflictPool);

    HIGHS_EXPORT bool explainInfeasibility();

    HIGHS_EXPORT bool explainInfeasibilityConflict(const HighsDomainChange* conflict,
                                      HighsInt len);

    HIGHS_EXPORT bool explainInfeasibilityLeq(const HighsInt* inds, const double* vals,
                                 HighsInt len, double rhs, double minActivity);

    HIGHS_EXPORT bool explainInfeasibilityGeq(const HighsInt* inds, const double* vals,
                                 HighsInt len, double rhs, double maxActivity);

    HIGHS_EXPORT bool explainBoundChange(const std::set<LocalDomChg>& currentFrontier,
                            LocalDomChg domchg);

    // bool explainBoundChange(HighsInt pos) {
    //   return explainBoundChange(LocalDomChg{pos,
    //   localdom.domchgstack_[pos]});
    // }

    HIGHS_EXPORT bool explainBoundChangeConflict(const LocalDomChg& domchg,
                                    const HighsDomainChange* conflict,
                                    HighsInt len);

    HIGHS_EXPORT bool explainBoundChangeLeq(const std::set<LocalDomChg>& currentFrontier,
                               const LocalDomChg& domChg, const HighsInt* inds,
                               const double* vals, HighsInt len, double rhs,
                               double minActivity);

    HIGHS_EXPORT bool explainBoundChangeGeq(const std::set<LocalDomChg>& currentFrontier,
                               const LocalDomChg& domChg, const HighsInt* inds,
                               const double* vals, HighsInt len, double rhs,
                               double maxActivity);

    HIGHS_EXPORT bool resolveLinearLeq(HighsCDouble M, double Mlower, const double* vals);

    HIGHS_EXPORT bool resolveLinearGeq(HighsCDouble M, double Mupper, const double* vals);
  };

  struct CutpoolPropagation {
    HighsInt cutpoolindex;
    HighsDomain* domain;
    HighsCutPool* cutpool;
    std::vector<HighsCDouble> activitycuts_;
    std::vector<HighsInt> activitycutsinf_;
    std::vector<uint8_t> propagatecutflags_;
    std::vector<HighsInt> propagatecutinds_;
    std::vector<double> capacityThreshold_;

    HIGHS_EXPORT CutpoolPropagation(HighsInt cutpoolindex, HighsDomain* domain,
                       HighsCutPool& cutpool);

    HIGHS_EXPORT CutpoolPropagation(const CutpoolPropagation& other);

    HIGHS_EXPORT ~CutpoolPropagation();

    HIGHS_EXPORT void recomputeCapacityThreshold(HighsInt cut);

    HIGHS_EXPORT void cutAdded(HighsInt cut, bool propagate);

    HIGHS_EXPORT void cutDeleted(HighsInt cut, bool deletedOnlyForPropagation = false);

    HIGHS_EXPORT void markPropagateCut(HighsInt cut);

    HIGHS_EXPORT void updateActivityLbChange(HighsInt col, double oldbound, double newbound);

    HIGHS_EXPORT void updateActivityUbChange(HighsInt col, double oldbound, double newbound);
  };

  struct ConflictPoolPropagation {
    HighsInt conflictpoolindex;
    HighsDomain* domain;
    HighsConflictPool* conflictpool_;
    std::vector<HighsInt> colLowerWatched_;
    std::vector<HighsInt> colUpperWatched_;
    std::vector<uint8_t> conflictFlag_;
    std::vector<HighsInt> propagateConflictInds_;

    struct WatchedLiteral {
      HighsDomainChange domchg = {0.0, -1, HighsBoundType::kLower};
      HighsInt prev = -1;
      HighsInt next = -1;
    };

    std::vector<WatchedLiteral> watchedLiterals_;

    HIGHS_EXPORT ConflictPoolPropagation(HighsInt conflictpoolindex, HighsDomain* domain,
                            HighsConflictPool& cutpool);

    HIGHS_EXPORT ConflictPoolPropagation(const ConflictPoolPropagation& other);

    HIGHS_EXPORT ~ConflictPoolPropagation();

    HIGHS_EXPORT void linkWatchedLiteral(HighsInt linkPos);

    HIGHS_EXPORT void unlinkWatchedLiteral(HighsInt linkPos);

    HIGHS_EXPORT void conflictAdded(HighsInt conflict);

    HIGHS_EXPORT void conflictDeleted(HighsInt conflict);

    HIGHS_EXPORT void markPropagateConflict(HighsInt conflict);

    HIGHS_EXPORT void updateActivityLbChange(HighsInt col, double oldbound, double newbound);

    HIGHS_EXPORT void updateActivityUbChange(HighsInt col, double oldbound, double newbound);

    HIGHS_EXPORT void propagateConflict(HighsInt conflict);
  };

 private:
  struct ObjectivePropagation {
    HighsDomain* domain = nullptr;
    const HighsObjectiveFunction* objFunc;
    const double* cost;
    HighsCDouble objectiveLower;
    HighsInt numInfObjLower;
    double capacityThreshold;
    bool isPropagated;

    struct ObjectiveContribution {
      double contribution;
      HighsInt col;
      HighsInt partition;
      highs::RbTreeLinks<HighsInt> links;
    };

    class ObjectiveContributionTree;

    std::vector<ObjectiveContribution> objectiveLowerContributions;
    std::vector<std::pair<HighsInt, HighsInt>> contributionPartitionSets;
    std::vector<double> propagationConsBuffer;
    struct PartitionCliqueData {
      double multiplier;
      HighsInt rhs;
      bool changed;
    };

    std::vector<PartitionCliqueData> partitionCliqueData;

    ObjectivePropagation() {
      objFunc = nullptr;
      cost = nullptr;
      objectiveLower = 0.0;
      numInfObjLower = 0;
      capacityThreshold = 0.0;
      isPropagated = false;
    }
    ObjectivePropagation(HighsDomain* domain);

    bool isActive() const { return domain != nullptr; }

    HIGHS_EXPORT void updateActivityLbChange(HighsInt col, double oldbound, double newbound);

    HIGHS_EXPORT void updateActivityUbChange(HighsInt col, double oldbound, double newbound);

    HIGHS_EXPORT bool shouldBePropagated() const;

    HIGHS_EXPORT void propagate();

    HIGHS_EXPORT void debugCheckObjectiveLower() const;

    // construct the proot constraint at the time when the domain change stack
    // had the given size
    HIGHS_EXPORT void getPropagationConstraint(HighsInt domchgStackSize, const double*& vals,
                                  const HighsInt*& inds, HighsInt& len,
                                  double& rhs, HighsInt domchgCol = -1);

   private:
    HIGHS_EXPORT void recomputeCapacityThreshold();
  };

  std::vector<uint8_t> changedcolsflags_;
  std::vector<HighsInt> changedcols_;

  std::vector<std::pair<HighsInt, HighsInt>> propRowNumChangedBounds_;

  std::vector<HighsDomainChange> domchgstack_;
  std::vector<Reason> domchgreason_;
  std::vector<std::pair<double, HighsInt>> prevboundval_;

  std::vector<HighsCDouble> activitymin_;
  std::vector<HighsCDouble> activitymax_;
  std::vector<HighsInt> activitymininf_;
  std::vector<HighsInt> activitymaxinf_;
  std::vector<double> capacityThreshold_;
  std::vector<uint8_t> propagateflags_;
  std::vector<HighsInt> propagateinds_;
  ObjectivePropagation objProp_;

  HighsMipSolver* mipsolver;

 private:
  std::deque<CutpoolPropagation> cutpoolpropagation;
  std::deque<ConflictPoolPropagation> conflictPoolPropagation;

  bool infeasible_ = 0;
  Reason infeasible_reason;
  HighsInt infeasible_pos;

  HIGHS_EXPORT void updateActivityLbChange(HighsInt col, double oldbound, double newbound);

  HIGHS_EXPORT void updateActivityUbChange(HighsInt col, double oldbound, double newbound);

  HIGHS_EXPORT void updateThresholdLbChange(HighsInt col, double newbound, double val,
                               double& threshold);

  HIGHS_EXPORT void updateThresholdUbChange(HighsInt col, double newbound, double val,
                               double& threshold);

  HIGHS_EXPORT void recomputeCapacityThreshold(HighsInt row);

  HIGHS_EXPORT double doChangeBound(const HighsDomainChange& boundchg);

  std::vector<HighsInt> colLowerPos_;
  std::vector<HighsInt> colUpperPos_;
  std::vector<HighsInt> branchPos_;

 public:
  std::vector<double> col_lower_;
  std::vector<double> col_upper_;

  HIGHS_EXPORT HighsDomain(HighsMipSolver& mipsolver);

  HighsDomain(const HighsDomain& other)
      : changedcolsflags_(other.changedcolsflags_),
        changedcols_(other.changedcols_),
        domchgstack_(other.domchgstack_),
        domchgreason_(other.domchgreason_),
        prevboundval_(other.prevboundval_),
        activitymin_(other.activitymin_),
        activitymax_(other.activitymax_),
        activitymininf_(other.activitymininf_),
        activitymaxinf_(other.activitymaxinf_),
        capacityThreshold_(other.capacityThreshold_),
        propagateflags_(other.propagateflags_),
        propagateinds_(other.propagateinds_),
        objProp_(other.objProp_),
        mipsolver(other.mipsolver),
        cutpoolpropagation(other.cutpoolpropagation),
        conflictPoolPropagation(other.conflictPoolPropagation),
        infeasible_(other.infeasible_),
        infeasible_reason(other.infeasible_reason),
        infeasible_pos(other.infeasible_pos),
        colLowerPos_(other.colLowerPos_),
        colUpperPos_(other.colUpperPos_),
        branchPos_(other.branchPos_),
        col_lower_(other.col_lower_),
        col_upper_(other.col_upper_) {
    for (CutpoolPropagation& cutpoolprop : cutpoolpropagation)
      cutpoolprop.domain = this;
    for (ConflictPoolPropagation& conflictprop : conflictPoolPropagation)
      conflictprop.domain = this;
    if (objProp_.domain) objProp_.domain = this;
  }

  HighsDomain& operator=(const HighsDomain& other) {
    changedcolsflags_ = other.changedcolsflags_;
    changedcols_ = other.changedcols_;
    domchgstack_ = other.domchgstack_;
    domchgreason_ = other.domchgreason_;
    prevboundval_ = other.prevboundval_;
    activitymin_ = other.activitymin_;
    activitymax_ = other.activitymax_;
    activitymininf_ = other.activitymininf_;
    activitymaxinf_ = other.activitymaxinf_;
    capacityThreshold_ = other.capacityThreshold_;
    propagateflags_ = other.propagateflags_;
    propagateinds_ = other.propagateinds_;
    objProp_ = other.objProp_;
    mipsolver = other.mipsolver;
    cutpoolpropagation = other.cutpoolpropagation;
    conflictPoolPropagation = other.conflictPoolPropagation;
    infeasible_ = other.infeasible_;
    infeasible_reason = other.infeasible_reason;
    colLowerPos_ = other.colLowerPos_;
    colUpperPos_ = other.colUpperPos_;
    branchPos_ = other.branchPos_;
    col_lower_ = other.col_lower_;
    col_upper_ = other.col_upper_;
    for (CutpoolPropagation& cutpoolprop : cutpoolpropagation)
      cutpoolprop.domain = this;
    for (ConflictPoolPropagation& conflictprop : conflictPoolPropagation)
      conflictprop.domain = this;
    if (objProp_.domain) objProp_.domain = this;
    return *this;
  }

  HIGHS_EXPORT void computeMinActivity(HighsInt start, HighsInt end, const HighsInt* ARindex,
                          const double* ARvalue, HighsInt& ninfmin,
                          HighsCDouble& activitymin);

  HIGHS_EXPORT void computeMaxActivity(HighsInt start, HighsInt end, const HighsInt* ARindex,
                          const double* ARvalue, HighsInt& ninfmax,
                          HighsCDouble& activitymax);

  HIGHS_EXPORT double adjustedUb(HighsInt col, HighsCDouble boundVal, bool& accept) const;

  HIGHS_EXPORT double adjustedLb(HighsInt col, HighsCDouble boundVal, bool& accept) const;

  HIGHS_EXPORT HighsInt propagateRowUpper(const HighsInt* Rindex, const double* Rvalue,
                             HighsInt Rlen, double Rupper,
                             const HighsCDouble& minactivity, HighsInt ninfmin,
                             HighsDomainChange* boundchgs);

  HIGHS_EXPORT HighsInt propagateRowLower(const HighsInt* Rindex, const double* Rvalue,
                             HighsInt Rlen, double Rlower,
                             const HighsCDouble& maxactivity, HighsInt ninfmax,
                             HighsDomainChange* boundchgs);

  const std::vector<HighsInt>& getChangedCols() const { return changedcols_; }

  HIGHS_EXPORT void addCutpool(HighsCutPool& cutpool);

  HIGHS_EXPORT void addConflictPool(HighsConflictPool& conflictPool);

  void clearChangedCols() {
    for (HighsInt i : changedcols_) changedcolsflags_[i] = 0;
    changedcols_.clear();
  }

  void removeContinuousChangedCols() {
    for (HighsInt i : changedcols_)
      changedcolsflags_[i] =
          mipsolver->variableType(i) != HighsVarType::kContinuous;

    changedcols_.erase(
        std::remove_if(changedcols_.begin(), changedcols_.end(),
                       [&](HighsInt i) { return !changedcolsflags_[i]; }),
        changedcols_.end());
  }

  void clearChangedCols(HighsInt start) {
    HighsInt end = changedcols_.size();
    for (HighsInt i = start; i != end; ++i)
      changedcolsflags_[changedcols_[i]] = 0;

    changedcols_.resize(start);
  }

  HIGHS_EXPORT void markPropagate(HighsInt row);

  bool isActive(const HighsDomainChange& domchg) const {
    return domchg.boundtype == HighsBoundType::kLower
               ? domchg.boundval <= col_lower_[domchg.column]
               : domchg.boundval >= col_upper_[domchg.column];
  }

  HIGHS_EXPORT void markPropagateCut(Reason reason);

  void setupObjectivePropagation() { objProp_ = ObjectivePropagation(this); }

  HIGHS_EXPORT void computeRowActivities();

  void markInfeasible(Reason reason = Reason::unspecified()) {
    infeasible_ = true;
    infeasible_pos = domchgstack_.size();
    infeasible_reason = reason;
  }

  bool infeasible() const { return infeasible_; }

  HIGHS_EXPORT void changeBound(HighsDomainChange boundchg,
                   Reason reason = Reason::branching());

  void changeBound(HighsBoundType boundtype, HighsInt col, double boundval,
                   Reason reason = Reason::branching()) {
    changeBound({boundval, col, boundtype}, reason);
  }

  void fixCol(HighsInt col, double val, Reason reason = Reason::unspecified()) {
    if (kAllowDeveloperAssert) {
      assert(infeasible_ == 0);
    }
    if (col_lower_[col] < val) {
      changeBound({val, col, HighsBoundType::kLower}, reason);
      if (infeasible_ == 0) propagate();
    }

    if (infeasible_ == 0 && col_upper_[col] > val)
      changeBound({val, col, HighsBoundType::kUpper}, reason);
  }

  HIGHS_EXPORT void backtrackToGlobal();

  HIGHS_EXPORT HighsDomainChange backtrack();

  const std::vector<HighsInt>& getBranchingPositions() const {
    return branchPos_;
  }

  const std::vector<std::pair<double, HighsInt>>& getPreviousBounds() const {
    return prevboundval_;
  }

  const std::vector<HighsDomainChange>& getDomainChangeStack() const {
    return domchgstack_;
  }

  const std::vector<Reason>& getDomainChangeReason() const {
    return domchgreason_;
  }

  double getObjectiveLowerBound() const {
    if (objProp_.isActive() && objProp_.numInfObjLower == 0)
      return double(objProp_.objectiveLower);

    return -kHighsInf;
  }

  void getCutoffConstraint(const double*& vals, const HighsInt*& inds,
                           HighsInt& len, double& rhs) {
    objProp_.getPropagationConstraint(domchgstack_.size(), vals, inds, len,
                                      rhs);
  }

  HighsInt getNumDomainChanges() const { return domchgstack_.size(); }

  bool colBoundsAreGlobal(HighsInt col) const {
    return colLowerPos_[col] == -1 && colUpperPos_[col] == -1;
  }

  HighsInt getBranchDepth() const { return branchPos_.size(); }

  std::vector<HighsDomainChange> getReducedDomainChangeStack(
      std::vector<HighsInt>& branchingPositions) const {
    std::vector<HighsDomainChange> reducedstack;
    reducedstack.reserve(domchgstack_.size());
    branchingPositions.reserve(branchPos_.size());
    for (HighsInt i = 0; i < (HighsInt)domchgstack_.size(); ++i) {
      // keep only the tightest bound change for each variable
      if ((domchgstack_[i].boundtype == HighsBoundType::kLower &&
           colLowerPos_[domchgstack_[i].column] != i) ||
          (domchgstack_[i].boundtype == HighsBoundType::kUpper &&
           colUpperPos_[domchgstack_[i].column] != i))
        continue;

      if (domchgreason_[i].type == Reason::kBranching)
        branchingPositions.push_back(reducedstack.size());
      else {
        HighsInt k = i;
        while (prevboundval_[k].second != -1) {
          k = prevboundval_[k].second;
          if (domchgreason_[k].type == Reason::kBranching) {
            branchingPositions.push_back(reducedstack.size());
            break;
          }
        }
      }

      reducedstack.push_back(domchgstack_[i]);
    }

    reducedstack.shrink_to_fit();
    return reducedstack;
  }

  HIGHS_EXPORT void setDomainChangeStack(const std::vector<HighsDomainChange>& domchgstack);

  HIGHS_EXPORT void setDomainChangeStack(const std::vector<HighsDomainChange>& domchgstack,
                            const std::vector<HighsInt>& branchingPositions);

  HIGHS_EXPORT bool propagate();

  HIGHS_EXPORT double getColLowerPos(HighsInt col, HighsInt stackpos, HighsInt& pos) const;

  HIGHS_EXPORT double getColUpperPos(HighsInt col, HighsInt stackpos, HighsInt& pos) const;

  HIGHS_EXPORT void conflictAnalysis(HighsConflictPool& conflictPool);

  HIGHS_EXPORT void conflictAnalysis(const HighsInt* proofinds, const double* proofvals,
                        HighsInt prooflen, double proofrhs,
                        HighsConflictPool& conflictPool);

  HIGHS_EXPORT void conflictAnalyzeReconvergence(const HighsDomainChange& domchg,
                                    const HighsInt* proofinds,
                                    const double* proofvals, HighsInt prooflen,
                                    double proofrhs,
                                    HighsConflictPool& conflictPool);

  HIGHS_EXPORT void tightenCoefficients(HighsInt* inds, double* vals, HighsInt len,
                           double& rhs) const;

  double getMinActivity(HighsInt row) const {
    return activitymininf_[row] == 0 ? double(activitymin_[row]) : -kHighsInf;
  }

  double getMaxActivity(HighsInt row) const {
    return activitymaxinf_[row] == 0 ? double(activitymax_[row]) : kHighsInf;
  }

  double getMinCutActivity(const HighsCutPool& cutpool, HighsInt cut) const;

  bool isBinary(HighsInt col) const {
    return mipsolver->variableType(col) != HighsVarType::kContinuous &&
           col_lower_[col] == 0.0 && col_upper_[col] == 1.0;
  }

  bool isGlobalBinary(HighsInt col) const {
    return mipsolver->variableType(col) != HighsVarType::kContinuous &&
           mipsolver->model_->col_lower_[col] == 0.0 &&
           mipsolver->model_->col_upper_[col] == 1.0;
  }

  HighsVarType variableType(HighsInt col) const {
    return mipsolver->variableType(col);
  }

  bool isFixed(HighsInt col) const {
    return col_lower_[col] == col_upper_[col];
  }

  HIGHS_EXPORT bool isFixing(const HighsDomainChange& domchg) const;

  HIGHS_EXPORT HighsDomainChange flip(const HighsDomainChange& domchg) const;

  HIGHS_EXPORT double feastol() const;

  HighsInt numModelNonzeros() const { return mipsolver->numNonzero(); }

  bool inSubmip() const { return mipsolver->submip; }
};

#endif
