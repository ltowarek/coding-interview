// Route Between Nodes: Given a directed graph, design an algorithm to find out
// whether there is a route between two nodes.

#include <queue>
#include "gtest/gtest.h"

template <class T>
struct Node {
  Node(T _data): data(_data) {}
  T data;
  std::vector<Node<T>*> children;
};

template <class T>
struct Graph {
  std::vector<std::unique_ptr<Node<T>>> nodes;
};

template <class T>
bool IsRouteBetween(const Graph<T> &graph, const Node<T> &start, const Node<T> &end) {
  if (&start == &end) {
    return true;
  }

  auto visited = std::map<const Node<T>*, bool>{};
  for (const auto &node : graph.nodes) {
    visited[node.get()] = false;
  }

  auto queue = std::queue<const Node<T>*>{};
  visited[&start] = true;
  queue.push(&start);

  while (!queue.empty()) {
    const auto *node = queue.front();
    queue.pop();
    for (const auto *child : node->children) {
      if (!visited[child]) {
        if (child == &end) {
          return true;
        } else {
          visited[child] = true;
          queue.push(child);
        }
      }
    }
    visited[node] = true;
  }

  return false;
}

TEST(route_between_nodes_test, SameNode) {
  auto graph = Graph<int>();
  graph.nodes.push_back(std::make_unique<Node<int>>(1));
  auto &start = *(graph.nodes[0].get());
  auto &end = start;

  EXPECT_TRUE(IsRouteBetween(graph, start, end));
}

TEST(route_between_nodes_test, SimpleRoute) {
  auto graph = Graph<int>();
  graph.nodes.push_back(std::make_unique<Node<int>>(1));
  graph.nodes.push_back(std::make_unique<Node<int>>(2));
  auto &start = *(graph.nodes[0].get());
  auto &end = *(graph.nodes[1].get());

  start.children.push_back(&end);

  EXPECT_TRUE(IsRouteBetween(graph, start, end));
}

TEST(route_between_nodes_test, SimpleNoRoute) {
  auto graph = Graph<int>();
  graph.nodes.push_back(std::make_unique<Node<int>>(1));
  graph.nodes.push_back(std::make_unique<Node<int>>(2));
  auto &start = *(graph.nodes[0].get());
  auto &end = *(graph.nodes[1].get());

  EXPECT_FALSE(IsRouteBetween(graph, start, end));
}

TEST(route_between_nodes_test, EndToStartNoRoute) {
  auto graph = Graph<int>();
  graph.nodes.push_back(std::make_unique<Node<int>>(1));
  graph.nodes.push_back(std::make_unique<Node<int>>(2));
  auto &start = *(graph.nodes[0].get());
  auto &end = *(graph.nodes[1].get());

  end.children.push_back(&start);

  EXPECT_FALSE(IsRouteBetween(graph, start, end));
}

TEST(route_between_nodes_test, RouteLength2) {
  auto graph = Graph<int>();
  graph.nodes.push_back(std::make_unique<Node<int>>(1));
  graph.nodes.push_back(std::make_unique<Node<int>>(2));
  graph.nodes.push_back(std::make_unique<Node<int>>(3));
  auto &start = *(graph.nodes[0].get());
  auto &end = *(graph.nodes[2].get());

  graph.nodes[0]->children.push_back(graph.nodes[1].get());
  graph.nodes[1]->children.push_back(graph.nodes[2].get());

  EXPECT_TRUE(IsRouteBetween(graph, start, end));
}

TEST(route_between_nodes_test, RouteLength4) {
  auto graph = Graph<int>();
  graph.nodes.push_back(std::make_unique<Node<int>>(1));
  graph.nodes.push_back(std::make_unique<Node<int>>(2));
  graph.nodes.push_back(std::make_unique<Node<int>>(3));
  graph.nodes.push_back(std::make_unique<Node<int>>(4));
  graph.nodes.push_back(std::make_unique<Node<int>>(5));
  auto &start = *(graph.nodes[0].get());
  auto &end = *(graph.nodes[4].get());

  graph.nodes[0]->children.push_back(graph.nodes[1].get());
  graph.nodes[1]->children.push_back(graph.nodes[2].get());
  graph.nodes[2]->children.push_back(graph.nodes[3].get());
  graph.nodes[3]->children.push_back(graph.nodes[4].get());

  EXPECT_TRUE(IsRouteBetween(graph, start, end));
}

TEST(route_between_nodes_test, RouteFromMiddle) {
  auto graph = Graph<int>();
  graph.nodes.push_back(std::make_unique<Node<int>>(1));
  graph.nodes.push_back(std::make_unique<Node<int>>(2));
  graph.nodes.push_back(std::make_unique<Node<int>>(3));
  graph.nodes.push_back(std::make_unique<Node<int>>(4));
  graph.nodes.push_back(std::make_unique<Node<int>>(5));
  auto &start = *(graph.nodes[1].get());
  auto &end = *(graph.nodes[3].get());

  graph.nodes[0]->children.push_back(graph.nodes[1].get());
  graph.nodes[1]->children.push_back(graph.nodes[2].get());
  graph.nodes[2]->children.push_back(graph.nodes[3].get());
  graph.nodes[3]->children.push_back(graph.nodes[4].get());

  EXPECT_TRUE(IsRouteBetween(graph, start, end));
}

TEST(route_between_nodes_test, RouteFromMultipleChildren) {
  auto graph = Graph<int>();
  graph.nodes.push_back(std::make_unique<Node<int>>(1));
  graph.nodes.push_back(std::make_unique<Node<int>>(2));
  graph.nodes.push_back(std::make_unique<Node<int>>(3));
  graph.nodes.push_back(std::make_unique<Node<int>>(4));
  graph.nodes.push_back(std::make_unique<Node<int>>(5));
  auto &start = *(graph.nodes[0].get());
  auto &end = *(graph.nodes[4].get());

  graph.nodes[0]->children.push_back(graph.nodes[1].get());
  graph.nodes[0]->children.push_back(graph.nodes[2].get());
  graph.nodes[0]->children.push_back(graph.nodes[3].get());
  graph.nodes[3]->children.push_back(graph.nodes[4].get());

  EXPECT_TRUE(IsRouteBetween(graph, start, end));
}

TEST(route_between_nodes_test, RouteFromMultipleChildrenWithCycle) {
  auto graph = Graph<int>();
  graph.nodes.push_back(std::make_unique<Node<int>>(1));
  graph.nodes.push_back(std::make_unique<Node<int>>(2));
  graph.nodes.push_back(std::make_unique<Node<int>>(3));
  graph.nodes.push_back(std::make_unique<Node<int>>(4));
  graph.nodes.push_back(std::make_unique<Node<int>>(5));
  auto &start = *(graph.nodes[0].get());
  auto &end = *(graph.nodes[4].get());

  graph.nodes[0]->children.push_back(graph.nodes[1].get());
  graph.nodes[0]->children.push_back(graph.nodes[1].get());
  graph.nodes[1]->children.push_back(graph.nodes[0].get());
  graph.nodes[0]->children.push_back(graph.nodes[2].get());
  graph.nodes[0]->children.push_back(graph.nodes[3].get());
  graph.nodes[3]->children.push_back(graph.nodes[4].get());

  EXPECT_TRUE(IsRouteBetween(graph, start, end));
}

TEST(route_between_nodes_test, NoRouteFromMultipleChildrenWithCycle) {
  auto graph = Graph<int>();
  graph.nodes.push_back(std::make_unique<Node<int>>(1));
  graph.nodes.push_back(std::make_unique<Node<int>>(2));
  graph.nodes.push_back(std::make_unique<Node<int>>(3));
  graph.nodes.push_back(std::make_unique<Node<int>>(4));
  graph.nodes.push_back(std::make_unique<Node<int>>(5));
  auto &start = *(graph.nodes[0].get());
  auto &end = *(graph.nodes[4].get());

  graph.nodes[4]->children.push_back(graph.nodes[0].get());
  graph.nodes[0]->children.push_back(graph.nodes[1].get());
  graph.nodes[0]->children.push_back(graph.nodes[2].get());
  graph.nodes[0]->children.push_back(graph.nodes[3].get());
  graph.nodes[3]->children.push_back(graph.nodes[0].get());

  EXPECT_FALSE(IsRouteBetween(graph, start, end));
}
