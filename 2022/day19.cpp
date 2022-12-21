#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <optional>
#include "../common/lib.h"

enum kind { ORE = 0, CLAY, OBSIDIAN, GEODE, NO_KINDS };

typedef std::array<int, NO_KINDS> Materials;
typedef std::array<int, NO_KINDS> Robots;
typedef std::array<Materials, NO_KINDS> Blueprint;

Materials maxDemandForMaterial = {0, 0, 0, 0};
Blueprint costsForRobot = { Materials{0, 0, 0, 0},
                            Materials{0, 0, 0, 0},
                            Materials{0, 0, 0, 0},
                            Materials{0, 0, 0, 0}};

bool shouldBuildRobot(kind kind, const Robots& robots) { return robots[kind] < maxDemandForMaterial[kind]; }

std::optional<Materials> canBuildRobot(kind kind, const Materials& materials) {
  Materials newMaterials = materials;
  for (int i = 0; i < NO_KINDS; i++) {
    newMaterials[i] -= costsForRobot[kind][i];
    if (newMaterials[i] < 0) return std::nullopt;
  }
  return newMaterials;
}

Materials bumpMaterials(const Materials& materials, const Robots& robots) {
  Materials newMaterials = materials;
  for (int i = 0; i < NO_KINDS; i++) newMaterials[i] += robots[i];
  return newMaterials;
}

int64_t bestGeodes(int minutesLeft, const Materials& materials, const Robots& robots) {
  if (minutesLeft == 0) return materials[GEODE];
  if (auto newMaterials = canBuildRobot(GEODE, materials)) {
    Materials bumpedMaterials = bumpMaterials(*newMaterials, robots);
    Robots newRobots = robots;
    ++newRobots[GEODE];
    return bestGeodes(minutesLeft - 1, bumpedMaterials, newRobots);
  }

  int numKindsWanted = 0;
  int numKindsPossible = 0;
  std::array<int, NO_KINDS + 1> bestGeodesForAction = {0};

  for (int i = 0; i < GEODE; ++i) {
    if (shouldBuildRobot(kind(i), robots)) {
      ++numKindsWanted;
      if (auto newMaterials = canBuildRobot(kind(i), materials)) {
        ++numKindsPossible;
        Materials bumpedMaterials = bumpMaterials(*newMaterials, robots);
        Robots newRobots = robots;
        ++newRobots[i];
        bestGeodesForAction[i] = bestGeodes(minutesLeft - 1, bumpedMaterials, newRobots);
      }
    }
  }

  if (numKindsPossible < numKindsWanted) {
    Materials bumpedMaterials = bumpMaterials(materials, robots);
    bestGeodesForAction[NO_KINDS] = bestGeodes(minutesLeft - 1, bumpedMaterials, robots);
  }

  int64_t best = 0;
  for (int i = 0; i < NO_KINDS + 1; ++i) if (bestGeodesForAction[i] > best) best = bestGeodesForAction[i];
  return best;
}

std::istream &operator>>(std::istream &is, Blueprint &b)
{
  std::string s, n, discard;
  std::getline(std::cin, s);
  for(auto c: s) switch (c) case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case ' ': n += c;
  std::istringstream ns(n);
  ns >> discard >> b[ORE][ORE] >> b[CLAY][ORE] >> b[OBSIDIAN][ORE] >> b[OBSIDIAN][CLAY] >> b[GEODE][ORE] >> b[GEODE][OBSIDIAN];
  return is;
};  

std::vector<Blueprint> readBlueprints() {
  std::vector<Blueprint> blueprints;
  while (!std::cin.eof()) {
    Blueprint bp{};
    std::cin >> bp;
    blueprints.push_back(bp);
  }
  return blueprints;
};

void setBlueprint(const Blueprint& blueprint) {
  costsForRobot = blueprint;
  for (int i = 0; i < NO_KINDS; ++i) {
    maxDemandForMaterial[i] = 0;
    for (int j = 0; j < NO_KINDS; ++j) if (costsForRobot[j][i] > maxDemandForMaterial[i]) maxDemandForMaterial[i] = costsForRobot[j][i];
  }
}

std::uintmax_t simulate(int minutes_left, std::vector<Blueprint> blueprints, bool part_2) {
  if (part_2) if (blueprints.size() > 3) blueprints.erase(blueprints.begin() + 3, blueprints.end());
  int bluePrintNo = 1;
  int64_t qualitySum = 0;
  int64_t product = 1;
  for (auto& blueprint : blueprints) {
    setBlueprint(blueprint);
    Materials materials = {0, 0, 0, 0};
    Robots robots = {1, 0, 0, 0};
    int64_t geodes = bestGeodes(minutes_left, materials, robots);
    qualitySum += (bluePrintNo++ * geodes);
    product *= geodes;
  }
  return (part_2)? product : qualitySum;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  auto blueprints = readBlueprints();
  return {simulate(24, blueprints, false), simulate(32, blueprints, true)};
}