#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

struct Node {
  int key;
  Node *left = nullptr;
  Node *right = nullptr;
};

void printOBST(Node *root) {
  if (!root) return;
  std::queue<Node *> queue1;
  queue1.push(root);
  std::vector<int> results;
  while (!queue1.empty()) {
    Node *node1 = queue1.front();
    queue1.pop();
    if (node1) {
      results.emplace_back(node1->key);
      queue1.push(node1->left);
      queue1.push(node1->right);
    } else {
      results.emplace_back(-1);
    }
  }
  while (results[results.size() - 1] == -1) {
    results.pop_back();
  }
  for (int i = 0; i < results.size(); i++) {
    if (i) std::cout << " ";
    std::cout << results[i];
  }
  std::cout << std::endl;
}

Node *createOBST(std::vector<int> &keys, std::vector<std::vector<int>> &roots,
                 int i, int j) {
  if (i > j) return nullptr;
  int root = roots[i][j];
  Node *node = new Node();
  node->key = keys[root];
  node->left = createOBST(keys, roots, i, root - 1);
  node->right = createOBST(keys, roots, root + 1, j);
  return node;
}

void runOBST(int &n, std::vector<int> &keys, std::vector<int> &frequencies,
             std::vector<std::vector<int>> &costs,
             std::vector<std::vector<int>> &roots) {
  std::vector<int> prefixSum(n + 1);
  for (int i = 0; i < n; i++) {
    costs[i][i] = frequencies[i];
    roots[i][i] = i;
    prefixSum[i + 1] = prefixSum[i] + frequencies[i];
  }
  for (int length = 2; length <= n; length++) {
    for (int i = 0; i <= n - length; i++) {
      int j = i + length - 1;
      costs[i][j] = std::numeric_limits<int>::max();
      int start = std::min(roots[i][j - 1], roots[i + 1][j]);
      int end = std::max(roots[i][j - 1], roots[i + 1][j]);
      for (int root = start; root <= end; root++) {
        int leftCost = root == i ? 0 : costs[i][root - 1];
        int rightCost = root == j ? 0 : costs[root + 1][j];
        int totalCost = leftCost + rightCost + prefixSum[j + 1] - prefixSum[i];
        if (totalCost < costs[i][j]) {
          costs[i][j] = totalCost;
          roots[i][j] = root;
        }
      }
    }
  }
  Node *rootNode = createOBST(keys, roots, 0, n - 1);
  printOBST(rootNode);
}

void performOBST() {
  int T;
  std::cin >> T;
  while (T--) {
    int N;
    std::cin >> N;
    std::vector<int> keys(N), frequencies(N);
    for (int i = 0; i < N; i++) {
      std::cin >> keys[i];
    }
    for (int i = 0; i < N; i++) {
      std::cin >> frequencies[i];
    }
    std::vector<std::vector<int>> costs(N, std::vector<int>(N));
    std::vector<std::vector<int>> roots(N, std::vector<int>(N, -1));
    runOBST(N, keys, frequencies, costs, roots);
  }
}

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  performOBST();
  return 0;
}
