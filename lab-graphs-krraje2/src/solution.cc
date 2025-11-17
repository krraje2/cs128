#include "solution.hpp"

#include <iostream>
#include <map>
#include <queue>

Solution::Solution(
    const std::vector<std::pair<std::string, std::string>>& prerequisites) {
  for (const std::pair<std::string, std::string>& val : prerequisites) {
    if (adj_.count(val.first) > 0) {
      adj_[val.first].push_back(val.second);
    } else {
      std::list<std::string> list;
      list.push_back(val.second);
      adj_.insert(
          std::pair<std::string, std::list<std::string>>(val.first, list));
    }
  }
}

int Solution::Solve(const std::string& start, const std::string& dest) {
  std::queue<std::pair<std::string, int>> q;
  q.push(std::pair<std::string, int>(start, 0));
  std::map<std::string, bool> visited;
  visited[start] = true;
  while (!q.empty()) {
    std::pair<std::string, int> node = q.front();
    std::string course = node.first;
    int dist = node.second;
    q.pop();
    if (course == dest) {
      return dist;
    }
    if (VertexInGraph(course)) {
      for (const std::string& c : GetAdjacencyList(course)) {
        if (!visited[c]) {
          visited[c] = true; 
          q.push(std::pair<std::string, int>(c, dist + 1));
        }
      }
    }
  }
  return -1;
}

/////////////////////////////////////////////////////////////////////////////
// Provide function definitions (uncomment to use!)                          //
/////////////////////////////////////////////////////////////////////////////

void Solution::AddVertex(const std::string& vertex) {
  if (VertexInGraph(vertex))
    throw std::runtime_error("vertex already in graph.");
  adj_.insert(std::pair<std::string, std::list<std::string>>());
}

std::list<std::string>& Solution::GetAdjacencyList(const std::string& vertex) {
  return adj_.find(vertex)->second;
}

bool Solution::VertexInGraph(const std::string vertex) {
  if (adj_.find(vertex) != adj_.end())
    return true;
  else
    return false;
}

std::ostream& operator<<(std::ostream& os, const Solution& sol) {
  os << "Contents:" << std::endl;

  for (const auto& pair : sol.adj_) {
    os << "  " << pair.first << ": [ ";

    for (const auto& list_entry : pair.second) {
      os << list_entry << " ";
    }

    os << "]" << std::endl;
  }

  return os;
}