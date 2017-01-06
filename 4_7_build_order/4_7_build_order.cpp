// Build Order: You are given a list of projects and a list of dependencies
// (which is a list of pairs of projects, where the second project is dependent
// on the first project). All of a project's dependencies must be built before
// the project is. Find a build order that will allow the projects to be built.
// If there is no valid build order, return an error.
// EXAMPLE
// Input:
//  Projects: a, b, c, d, e, f
//  Dependencies: (a, d), (f, b), (b, d), (f, a), (d, c)
// Output: f, e, a, b, d, c

#include "gtest/gtest.h"
#include <algorithm>
#include <exception>
#include <utility>

template <class T> struct Node {
  Node(T _data) : data(_data) {}
  T data;
  std::vector<Node *> children;
  std::vector<Node *> parents;
};

template <class T> class Graph {
public:
  Node<T> *GetNode(const T data) {
    for (const auto &node : nodes_) {
      if (node->data == data) {
        return node.get();
      }
    }
    return nullptr;
  }

  Node<T> *CreateNode(const T data) {
    nodes_.push_back(std::make_unique<Node<T>>(data));
    return nodes_.back().get();
  }

  void RemoveNode(const Node<T> &node) {
    for (auto parent : node.parents) {
      parent->children.erase(
          std::remove(parent->children.begin(), parent->children.end(), &node),
          parent->children.end());
    }
    for (auto child : node.children) {
      child->parents.erase(
          std::remove(child->parents.begin(), child->parents.end(), &node),
          child->parents.end());
    }
    nodes_.erase(std::remove_if(nodes_.begin(), nodes_.end(),
                                [&](std::unique_ptr<Node<T>> &n) {
                                  return n.get() == &node;
                                }),
                 nodes_.end());
  }

  void CreateEdge(Node<T> &a, Node<T> &b) {
    a.children.push_back(&b);
    b.parents.push_back(&a);
  }

  std::vector<Node<T> *> GetNodes() const {
    auto nodes = std::vector<Node<T> *>{};
    for (const auto &node : nodes_) {
      nodes.push_back(node.get());
    }
    return nodes;
  }

private:
  std::vector<std::unique_ptr<Node<T>>> nodes_;
};

class Project {
public:
  Project(std::string name) : name_(name) {}

  std::string name() const { return name_; }

private:
  const std::string name_;
};

bool operator==(const Project &lhs, const Project &rhs) {
  return lhs.name() == rhs.name();
}

std::ostream &operator<<(std::ostream &stream, const Project &p) {
  stream << p.name();
  return stream;
}

using Projects = std::vector<Project *>;
using Dependencies = std::vector<std::pair<Project *, Project *>>;

Graph<Project *> CreateDependencyGraph(const Projects projects,
                                       const Dependencies dependencies) {
  auto graph = Graph<Project *>();
  for (const auto project : projects) {
    graph.CreateNode(project);
  }

  for (const auto dependency : dependencies) {
    const auto start = graph.GetNode(dependency.first);
    if (!start) {
      throw std::runtime_error("Project not found: " +
                               dependency.first->name());
    }
    const auto end = graph.GetNode(dependency.second);
    if (!end) {
      throw std::runtime_error("Project not found: " +
                               dependency.second->name());
    }
    graph.CreateEdge(*start, *end);
  }

  return graph;
}

void AddNonDependent(Projects &order,
                     const std::vector<Node<Project *> *> nodes) {
  for (const auto node : nodes) {
    if (node->parents.size() == 0) {
      order.push_back(node->data);
    }
  }
}

Projects BuildOrder(Graph<Project *> &graph) {
  auto order = Projects{};

  AddNonDependent(order, graph.GetNodes());

  size_t available_project_id = 0;
  while (available_project_id < order.size()) {
    const auto current_node = graph.GetNode(order[available_project_id]);
    const auto children = current_node->children;
    graph.RemoveNode(*current_node);

    AddNonDependent(order, children);

    available_project_id++;
  }

  return order;
}

Projects BuildOrder(const Projects projects, const Dependencies dependencies) {
  auto graph = CreateDependencyGraph(projects, dependencies);
  return BuildOrder(graph);
}

TEST(build_order_test, NoProjects) {
  const auto projects = Projects{};
  const auto dependencies = Dependencies{};
  const auto expected = Projects{};
  EXPECT_EQ(BuildOrder(projects, dependencies), expected);
}

TEST(build_order_test, NoDependencies) {
  auto project_a = Project("a");
  auto project_b = Project("b");
  const auto projects = Projects{&project_a, &project_b};
  const auto dependencies = Dependencies{};
  const auto expected = Projects{&project_a, &project_b};
  EXPECT_EQ(BuildOrder(projects, dependencies), expected);
}

TEST(build_order_test, SimpleDependencies) {
  auto project_a = Project("a");
  auto project_b = Project("b");
  auto project_c = Project("c");
  auto project_d = Project("d");
  const auto projects =
      Projects{&project_a, &project_b, &project_c, &project_d};
  const auto dependencies =
      Dependencies{{&project_a, &project_b}, {&project_c, &project_d}};
  const auto expected =
      Projects{&project_a, &project_c, &project_b, &project_d};
  EXPECT_EQ(BuildOrder(projects, dependencies), expected);
}

TEST(build_order_test, ChainedDependencies) {
  auto project_a = Project("a");
  auto project_b = Project("b");
  auto project_c = Project("c");
  auto project_d = Project("d");
  const auto projects =
      Projects{&project_a, &project_b, &project_c, &project_d};
  const auto dependencies = Dependencies{{&project_a, &project_b},
                                         {&project_b, &project_c},
                                         {&project_c, &project_d}};
  const auto expected =
      Projects{&project_a, &project_b, &project_c, &project_d};
  EXPECT_EQ(BuildOrder(projects, dependencies), expected);
}

TEST(build_order_test, Complex_1) {
  auto project_a = Project("a");
  auto project_b = Project("b");
  auto project_c = Project("c");
  auto project_d = Project("d");
  auto project_e = Project("e");
  auto project_f = Project("f");
  const auto projects = Projects{&project_a, &project_b, &project_c,
                                 &project_d, &project_e, &project_f};
  const auto dependencies = Dependencies{{&project_a, &project_d},
                                         {&project_f, &project_b},
                                         {&project_b, &project_d},
                                         {&project_f, &project_a},
                                         {&project_d, &project_c}};
  const auto expected = Projects{&project_e, &project_f, &project_b,
                                 &project_a, &project_d, &project_c};
  EXPECT_EQ(BuildOrder(projects, dependencies), expected);
}

TEST(build_order_test, Complex_2) {
  auto project_a = Project("a");
  auto project_b = Project("b");
  auto project_c = Project("c");
  auto project_d = Project("d");
  auto project_e = Project("e");
  auto project_f = Project("f");
  auto project_g = Project("g");
  const auto projects = Projects{&project_a, &project_b, &project_c, &project_d,
                                 &project_e, &project_f, &project_g};
  const auto dependencies =
      Dependencies{{&project_f, &project_c}, {&project_f, &project_a},
                   {&project_f, &project_b}, {&project_c, &project_a},
                   {&project_b, &project_a}, {&project_b, &project_e},
                   {&project_a, &project_e}, {&project_d, &project_g}};
  const auto expected = Projects{&project_d, &project_f, &project_g, &project_c,
                                 &project_b, &project_a, &project_e};
  EXPECT_EQ(BuildOrder(projects, dependencies), expected);
}

TEST(build_order_test, InvalidDependencies_Cycle) {
  auto project_a = Project("a");
  auto project_b = Project("b");
  const auto projects = Projects{&project_a, &project_b};
  const auto dependencies =
      Dependencies{{&project_a, &project_b}, {&project_b, &project_a}};
  const auto expected = Projects{};
  EXPECT_EQ(BuildOrder(projects, dependencies), expected);
}

TEST(build_order_test, InvalidDependencies_MissingProject) {
  auto project_a = Project("a");
  auto project_b = Project("b");
  auto project_c = Project("c");
  const auto projects = Projects{&project_a, &project_b};
  const auto dependencies =
      Dependencies{{&project_a, &project_b}, {&project_b, &project_c}};
  ASSERT_THROW(BuildOrder(projects, dependencies), std::runtime_error);
}
