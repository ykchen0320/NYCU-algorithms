#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

struct Champion {
  double x, y;
};

double calculateDistance(const Champion &c1, const Champion &c2) {
  return std::hypot(c1.x - c2.x, c1.y - c2.y);
}

double bruteForce(const std::vector<Champion> &champions, int left, int right) {
  double minDistance = std::numeric_limits<double>::infinity();
  for (int i = left; i <= right - 1; i++) {
    for (int j = i + 1; j <= right; j++) {
      minDistance =
          std::min(minDistance, calculateDistance(champions[i], champions[j]));
    }
  }
  return minDistance;
}

double closestPairInStrip(const std::vector<Champion> &champions, double d) {
  double minDistance = d;
  for (int i = 0; i < champions.size(); i++) {
    for (int j = i + 1; j < champions.size() &&
                        (champions[j].y - champions[i].y) < minDistance;
         j++) {
      minDistance =
          std::min(minDistance, calculateDistance(champions[i], champions[j]));
    }
  }
  return minDistance;
}

double findClosestPair(std::vector<Champion> &championsX,
                       std::vector<Champion> &championsY, int left, int right) {
  if (right - left <= 3) {
    return bruteForce(championsX, left, right);
  }
  int mid = left + (right - left) / 2;
  Champion midChampion = championsX[mid];
  std::vector<Champion> championsLeft, championsRight;
  for (int i = 0; i < championsY.size(); i++) {
    if (championsY[i].x <= midChampion.x) {
      championsLeft.emplace_back(championsY[i]);
    } else {
      championsRight.emplace_back(championsY[i]);
    }
  }
  double dLeft = findClosestPair(championsX, championsLeft, left, mid);
  double dRight = findClosestPair(championsX, championsRight, mid + 1, right);
  double d = std::min(dLeft, dRight);
  std::vector<Champion> stripChampions;
  for (int i = 0; i < championsY.size(); i++) {
    if (std::abs(championsY[i].x - midChampion.x) < d) {
      stripChampions.emplace_back(championsY[i]);
    }
  }
  return std::min(d, closestPairInStrip(stripChampions, d));
}

void performClosestPair() {
  int numTestCases;
  std::cin >> numTestCases;
  while (numTestCases--) {
    int numChampions;
    std::cin >> numChampions;
    std::vector<Champion> champions(numChampions);
    for (int i = 0; i < numChampions; i++) {
      Champion c;
      std::cin >> c.x >> c.y;
      champions[i] = c;
    }
    std::vector<Champion> championsX(numChampions), championsY(numChampions);
    std::copy(champions.begin(), champions.end(), championsX.begin());
    sort(championsX.begin(), championsX.end(),
         [](const Champion &c1, const Champion &c2) { return c1.x < c2.x; });
    championsY = std::move(champions);
    sort(championsY.begin(), championsY.end(),
         [](const Champion &c1, const Champion &c2) { return c1.y < c2.y; });
    double ans = findClosestPair(championsX, championsY, 0, numChampions - 1);
    std::cout << std::fixed << std::setprecision(6) << ans << std::endl;
  }
}

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  performClosestPair();
  return 0;
}
