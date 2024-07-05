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
#ifndef HIGHS_SEARCH_H_
#define HIGHS_SEARCH_H_

#include <cstdint>
#include <queue>
#include <vector>

#include "mip/HighsConflictPool.h"
#include "mip/HighsDomain.h"
#include "mip/HighsLpRelaxation.h"
#include "mip/HighsMipSolver.h"
#include "mip/HighsNodeQueue.h"
#include "mip/HighsPseudocost.h"
#include "mip/HighsSeparation.h"
#include "presolve/HighsSymmetry.h"
#include "util/HighsHash.h"

class HighsMipSolver;
class HighsImplications;
class HighsCliqueTable;

class HighsSearch {
  HighsMipSolver& mipsolver;
  HighsLpRelaxation* lp;
  HighsDomain localdom;
  HighsPseudocost& pseudocost;
  HighsRandom random;
  int64_t nnodes;
  int64_t lpiterations;
  int64_t heurlpiterations;
  int64_t sblpiterations;
  double upper_limit;
  HighsCDouble treeweight;
  std::vector<HighsInt> inds;
  std::vector<double> vals;
  HighsInt depthoffset;
  bool inbranching;
  bool inheuristic;
  bool countTreeWeight;

 public:
  enum class ChildSelectionRule {
    kUp,
    kDown,
    kRootSol,
    kObj,
    kRandom,
    kBestCost,
    kWorstCost,
    kDisjunction,
    kHybridInferenceCost,
  };

  enum class NodeResult {
    kBoundExceeding,
    kDomainInfeasible,
    kLpInfeasible,
    kBranched,
    kSubOptimal,
    kOpen,
  };

 private:
  ChildSelectionRule childselrule;

  struct NodeData {
    double lower_bound;
    double estimate;
    double branching_point;
    // we store the lp objective separately to the lower bound since the lower
    // bound could be above the LP objective when cuts age out or below when the
    // LP is unscaled dual infeasible and it is not set. We still want to use
    // the objective for pseudocost updates and tiebreaking of best bound node
    // selection
    double lp_objective;
    double other_child_lb;
    std::shared_ptr<const HighsBasis> nodeBasis;
    std::shared_ptr<const StabilizerOrbits> stabilizerOrbits;
    HighsDomainChange branchingdecision;
    HighsInt domgchgStackPos;
    uint8_t skipDepthCount;
    uint8_t opensubtrees;

    NodeData(double parentlb = -kHighsInf, double parentestimate = -kHighsInf,
             std::shared_ptr<const HighsBasis> parentBasis = nullptr,
             std::shared_ptr<const StabilizerOrbits> stabilizerOrbits = nullptr)
        : lower_bound(parentlb),
          estimate(parentestimate),
          branching_point(0.0),
          lp_objective(-kHighsInf),
          other_child_lb(parentlb),
          nodeBasis(std::move(parentBasis)),
          stabilizerOrbits(std::move(stabilizerOrbits)),
          branchingdecision{0.0, -1, HighsBoundType::kLower},
          domgchgStackPos(-1),
          skipDepthCount(0),
          opensubtrees(2) {}
  };

  enum ReliableFlags {
    kUpReliable = 1,
    kDownReliable = 2,
    kReliable = kDownReliable | kUpReliable,
  };

  std::vector<double> subrootsol;
  std::vector<NodeData> nodestack;
  HighsHashTable<HighsInt, int> reliableatnode;

  int branchingVarReliableAtNodeFlags(HighsInt col) const {
    auto it = reliableatnode.find(col);
    if (it == nullptr) return 0;
    return *it;
  }

  bool branchingVarReliableAtNode(HighsInt col) const {
    auto it = reliableatnode.find(col);
    if (it == nullptr || *it != kReliable) return false;

    return true;
  }

  void markBranchingVarUpReliableAtNode(HighsInt col) {
    reliableatnode[col] |= kUpReliable;
  }

  void markBranchingVarDownReliableAtNode(HighsInt col) {
    reliableatnode[col] |= kDownReliable;
  }

  HIGHS_EXPORT bool orbitsValidInChildNode(const HighsDomainChange& branchChg) const;

 public:
  HIGHS_EXPORT HighsSearch(HighsMipSolver& mipsolver, HighsPseudocost& pseudocost);

  HIGHS_EXPORT void setRINSNeighbourhood(const std::vector<double>& basesol,
                            const std::vector<double>& relaxsol);

  HIGHS_EXPORT void setRENSNeighbourhood(const std::vector<double>& lpsol);

  HIGHS_EXPORT double getCutoffBound() const;

  void setLpRelaxation(HighsLpRelaxation* lp) { this->lp = lp; }

  HIGHS_EXPORT double checkSol(const std::vector<double>& sol, bool& integerfeasible) const;

  HIGHS_EXPORT void createNewNode();

  HIGHS_EXPORT void cutoffNode();

  HIGHS_EXPORT void branchDownwards(HighsInt col, double newub, double branchpoint);

  HIGHS_EXPORT void branchUpwards(HighsInt col, double newlb, double branchpoint);

  HIGHS_EXPORT void setMinReliable(HighsInt minreliable);

  void setHeuristic(bool inheuristic) {
    this->inheuristic = inheuristic;
    if (inheuristic) childselrule = ChildSelectionRule::kHybridInferenceCost;
  }

  HIGHS_EXPORT void addBoundExceedingConflict();

  HIGHS_EXPORT void resetLocalDomain();

  HIGHS_EXPORT int64_t getHeuristicLpIterations() const;

  HIGHS_EXPORT int64_t getTotalLpIterations() const;

  HIGHS_EXPORT int64_t getLocalLpIterations() const;

  HIGHS_EXPORT int64_t getLocalNodes() const;

  HIGHS_EXPORT int64_t getStrongBranchingLpIterations() const;

  bool hasNode() const { return !nodestack.empty(); }

  bool currentNodePruned() const { return nodestack.back().opensubtrees == 0; }

  double getCurrentEstimate() const { return nodestack.back().estimate; }

  double getCurrentLowerBound() const { return nodestack.back().lower_bound; }

  HighsInt getCurrentDepth() const { return nodestack.size() + depthoffset; }

  HIGHS_EXPORT void openNodesToQueue(HighsNodeQueue& nodequeue);

  HIGHS_EXPORT void currentNodeToQueue(HighsNodeQueue& nodequeue);

  HIGHS_EXPORT void flushStatistics();

  HIGHS_EXPORT void installNode(HighsNodeQueue::OpenNode&& node);

  HIGHS_EXPORT void addInfeasibleConflict();

  HIGHS_EXPORT HighsInt selectBranchingCandidate(int64_t maxSbIters, double& downNodeLb,
                                    double& upNodeLb);

  HIGHS_EXPORT void evalUnreliableBranchCands();

  HIGHS_EXPORT const NodeData* getParentNodeData() const;

  HIGHS_EXPORT NodeResult evaluateNode();

  HIGHS_EXPORT NodeResult branch();

  /// backtrack one level in DFS manner
  HIGHS_EXPORT bool backtrack(bool recoverBasis = true);

  /// backtrack an unspecified amount of depth level until the next
  /// node that seems worthwhile to continue the plunge. Put unpromising nodes
  /// to the node queue
  HIGHS_EXPORT bool backtrackPlunge(HighsNodeQueue& nodequeue);

  /// for heuristics. Will discard nodes above targetDepth regardless of their
  /// status
  HIGHS_EXPORT bool backtrackUntilDepth(HighsInt targetDepth);

  HIGHS_EXPORT void printDisplayLine(char first, bool header = false);

  HIGHS_EXPORT NodeResult dive();

  HighsDomain& getLocalDomain() { return localdom; }

  const HighsDomain& getLocalDomain() const { return localdom; }

  HighsPseudocost& getPseudoCost() { return pseudocost; }

  const HighsPseudocost& getPseudoCost() const { return pseudocost; }

  HIGHS_EXPORT void solveDepthFirst(int64_t maxbacktracks = 1);
};

#endif
