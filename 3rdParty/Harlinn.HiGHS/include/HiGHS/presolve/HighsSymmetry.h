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
/**@file HighsSymmetry.h
 * @brief Facilities for symmetry detection
 * @author Leona Gottwald
 */

#ifndef PRESOLVE_HIGHS_SYMMETRY_H_
#define PRESOLVE_HIGHS_SYMMETRY_H_

#include <algorithm>
#include <map>
#include <vector>

#include "lp_data/HighsLp.h"
#include "util/HighsDisjointSets.h"
#include "util/HighsHash.h"
#include "util/HighsInt.h"

/// class that is responsible for assigning distinct colors for each distinct
/// double value
class HighsMatrixColoring {
  using u32 = std::uint32_t;

  std::map<double, u32> colorMap;
  double tolerance;

 public:
  // initialize with exact 0.0 and 1.0, to not have differing results due tiny
  // numerical differences on those values
  HighsMatrixColoring(double tolerance)
      : colorMap({{0.0, 1}, {1.0, 2}, {-kHighsInf, 3}, {kHighsInf, 4}}),
        tolerance(tolerance) {}

  u32 color(double value) {
    // iterator points to smallest element in map which fulfills key >= value -
    // tolerance
    auto it = colorMap.lower_bound(value - tolerance);
    // check if there is no such element, or if this element has a key value +
    // tolerance in which case we create a new color and store it with the key
    // value
    if (it == colorMap.end() || it->first > value + tolerance)
      it = colorMap.emplace_hint(it, value, colorMap.size() + 1);
    return it->second;
  }
};

class HighsDomain;
class HighsCliqueTable;
struct HighsSymmetries;
struct StabilizerOrbits {
  std::vector<HighsInt> orbitCols;
  std::vector<HighsInt> orbitStarts;
  std::vector<HighsInt> stabilizedCols;
  const HighsSymmetries* symmetries;

  HIGHS_EXPORT HighsInt orbitalFixing(HighsDomain& domain) const;

  HIGHS_EXPORT bool isStabilized(HighsInt col) const;
};

struct HighsOrbitopeMatrix {
  enum Type {
    kFull,
    kPacking,
  };
  HighsInt rowLength;
  HighsInt numRows;
  HighsInt numSetPackingRows;
  HighsHashTable<HighsInt, HighsInt> columnToRow;
  std::vector<int8_t> rowIsSetPacking;
  std::vector<HighsInt> matrix;

  HighsInt& entry(HighsInt i, HighsInt j) {
    return matrix[i + static_cast<size_t>(j) * numRows];
  }

  const HighsInt& entry(HighsInt i, HighsInt j) const {
    return matrix[i + static_cast<size_t>(j) * numRows];
  }

  HighsInt& operator()(HighsInt i, HighsInt j) { return entry(i, j); }

  const HighsInt& operator()(HighsInt i, HighsInt j) const {
    return entry(i, j);
  }

  HIGHS_EXPORT HighsInt orbitalFixing(HighsDomain& domain) const;

  HIGHS_EXPORT void determineOrbitopeType(HighsCliqueTable& cliquetable);

  HIGHS_EXPORT HighsInt getBranchingColumn(const std::vector<double>& colLower,
                              const std::vector<double>& colUpper,
                              HighsInt col) const;

 private:
  HIGHS_EXPORT HighsInt orbitalFixingForFullOrbitope(const std::vector<HighsInt>& rows,
                                        HighsDomain& domain) const;

  HIGHS_EXPORT HighsInt orbitalFixingForPackingOrbitope(const std::vector<HighsInt>& rows,
                                           HighsDomain& domain) const;
};

struct HighsSymmetries {
  std::vector<HighsInt> permutationColumns;
  std::vector<HighsInt> permutations;
  std::vector<HighsInt> orbitPartition;
  std::vector<HighsInt> orbitSize;
  std::vector<HighsInt> columnPosition;
  std::vector<HighsInt> linkCompressionStack;
  std::vector<HighsOrbitopeMatrix> orbitopes;
  HighsHashTable<HighsInt, HighsInt> columnToOrbitope;
  HighsInt numPerms = 0;
  HighsInt numGenerators = 0;

  HIGHS_EXPORT void clear();
  HIGHS_EXPORT void mergeOrbits(HighsInt col1, HighsInt col2);
  HIGHS_EXPORT HighsInt getOrbit(HighsInt col);

  HIGHS_EXPORT HighsInt propagateOrbitopes(HighsDomain& domain) const;

  HighsInt getBranchingColumn(const std::vector<double>& colLower,
                              const std::vector<double>& colUpper,
                              HighsInt col) const {
    if (columnToOrbitope.size() == 0) return col;
    const HighsInt* orbitope = columnToOrbitope.find(col);
    if (!orbitope || orbitopes[*orbitope].numSetPackingRows == 0) return col;

    return orbitopes[*orbitope].getBranchingColumn(colLower, colUpper, col);
  }

  HIGHS_EXPORT std::shared_ptr<const StabilizerOrbits> computeStabilizerOrbits(
      const HighsDomain& localdom);
};

class HighsSymmetryDetection {
  using u64 = std::uint64_t;
  using u32 = std::uint32_t;

  const HighsLp* model;
  // compressed graph storage
  std::vector<HighsInt> Gstart;
  std::vector<HighsInt> Gend;
  std::vector<std::pair<HighsInt, HighsUInt>> Gedge;

  std::vector<std::pair<HighsInt, HighsUInt>> edgeBuffer;

  std::vector<HighsInt> currentPartition;
  std::vector<HighsInt> currentPartitionLinks;
  std::vector<HighsInt> vertexToCell;
  std::vector<HighsInt> vertexPosition;
  std::vector<HighsInt> vertexGroundSet;
  std::vector<HighsInt> orbitPartition;
  std::vector<HighsInt> orbitSize;

  std::vector<HighsInt> cellCreationStack;
  std::vector<std::uint8_t> cellInRefinementQueue;
  std::vector<HighsInt> refinementQueue;
  std::vector<HighsInt*> distinguishCands;
  std::vector<HighsInt> automorphisms;

  std::vector<HighsInt> linkCompressionStack;

  std::vector<u32> currNodeCertificate;
  std::vector<u32> firstLeaveCertificate;
  std::vector<u32> bestLeaveCertificate;
  std::vector<HighsInt> firstLeavePartition;
  std::vector<HighsInt> bestLeavePartition;

  HighsHashTable<HighsInt, u32> vertexHash;
  HighsHashTable<std::tuple<HighsInt, HighsInt, HighsUInt>> firstLeaveGraph;
  HighsHashTable<std::tuple<HighsInt, HighsInt, HighsUInt>> bestLeaveGraph;

  HighsInt firstLeavePrefixLen;
  HighsInt bestLeavePrefixLen;
  HighsInt firstPathDepth;
  HighsInt bestPathDepth;

  HighsInt numAutomorphisms;
  HighsInt numCol;
  HighsInt numRow;
  HighsInt numVertices;
  HighsInt numActiveCols;

  // node in the search tree for finding automorphisms
  struct Node {
    HighsInt stackStart;
    HighsInt certificateEnd;
    HighsInt targetCell;
    HighsInt lastDistiguished;
  };

  std::vector<Node> nodeStack;

  HIGHS_EXPORT HighsInt getCellStart(HighsInt pos);

  HIGHS_EXPORT void backtrack(HighsInt backtrackStackNewEnd, HighsInt backtrackStackEnd);
  HIGHS_EXPORT void cleanupBacktrack(HighsInt cellCreationStackPos);

  HIGHS_EXPORT void switchToNextNode(HighsInt backtrackDepth);

  HIGHS_EXPORT bool compareCurrentGraph(
      const HighsHashTable<std::tuple<HighsInt, HighsInt, HighsUInt>>&
          otherGraph,
      HighsInt& wrongCell);

  HIGHS_EXPORT void removeFixPoints();
  HIGHS_EXPORT void initializeGroundSet();
  HIGHS_EXPORT HighsHashTable<std::tuple<HighsInt, HighsInt, HighsUInt>> dumpCurrentGraph();
  HIGHS_EXPORT bool mergeOrbits(HighsInt v1, HighsInt v2);
  HIGHS_EXPORT HighsInt getOrbit(HighsInt vertex);

  HIGHS_EXPORT void initializeHashValues();
  HIGHS_EXPORT bool isomorphicToFirstLeave();
  HIGHS_EXPORT bool partitionRefinement();
  HIGHS_EXPORT bool checkStoredAutomorphism(HighsInt vertex);
  HIGHS_EXPORT u32 getVertexHash(HighsInt vertex);
  HIGHS_EXPORT HighsInt selectTargetCell();

  HIGHS_EXPORT bool updateCellMembership(HighsInt vertex, HighsInt cell,
                            bool markForRefinement = true);
  HIGHS_EXPORT bool splitCell(HighsInt cell, HighsInt splitPoint);
  HIGHS_EXPORT void markCellForRefinement(HighsInt cell);

  HIGHS_EXPORT bool distinguishVertex(HighsInt targetCell);
  HIGHS_EXPORT bool determineNextToDistinguish();
  HIGHS_EXPORT void createNode();

  HighsInt cellSize(HighsInt cell) const {
    return currentPartitionLinks[cell] - cell;
  }

  HIGHS_EXPORT bool isFromBinaryColumn(HighsInt vertex) const;

  struct ComponentData {
    HighsDisjointSets<> components;
    std::vector<HighsInt> componentStarts;
    std::vector<HighsInt> componentSets;
    std::vector<HighsInt> componentNumOrbits;
    std::vector<HighsInt> componentNumber;
    std::vector<HighsInt> permComponentStarts;
    std::vector<HighsInt> permComponents;
    std::vector<HighsInt> firstUnfixed;
    std::vector<HighsInt> numUnfixed;

    HighsInt getComponentByIndex(HighsInt compIndex) const {
      return componentNumber[compIndex];
    }
    HighsInt numComponents() const { return componentStarts.size() - 1; }
    HighsInt componentSize(HighsInt component) const {
      return componentStarts[component + 1] - componentStarts[component];
    }

    HighsInt getVertexComponent(HighsInt vertexPosition) {
      return components.getSet(vertexPosition);
    }

    HighsInt getPermuationComponent(HighsInt permIndex) {
      return components.getSet(firstUnfixed[permIndex]);
    }
  };

  HIGHS_EXPORT ComponentData computeComponentData(const HighsSymmetries& symmetries);

  HIGHS_EXPORT bool isFullOrbitope(const ComponentData& componentData, HighsInt component,
                      HighsSymmetries& symmetries);

 public:
  HIGHS_EXPORT void loadModelAsGraph(const HighsLp& model, double epsilon);

  HIGHS_EXPORT bool initializeDetection();

  HIGHS_EXPORT void run(HighsSymmetries& symmetries);
};

#endif
