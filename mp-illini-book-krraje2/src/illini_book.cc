#include "illini_book.hpp"

#include <fstream>
#include <queue>

#include "utilities.hpp"

IlliniBook::IlliniBook(const std::string& people_fpath,
                       const std::string& relations_fpath) {
  // vector of ids
  std::ifstream ifs1{people_fpath};
  for (std::string line; std::getline(ifs1, line); line = "") {
    int num = std::stoi(line);
    uins_.push_back(num);
  }
  // map of relations
  std::ifstream ifs2{relations_fpath};
  for (std::string line; std::getline(ifs2, line); line = "") {
    std::vector<std::string> vals = utilities::Split(line, ',');
    int uin1 = stoi(vals.at(0));
    int uin2 = stoi(vals.at(1));
    std::pair<int, int> uin_pair = std::pair<int, int>(uin1, uin2);
    relationships_.insert(
        std::pair<std::pair<int, int>, std::string>(uin_pair, vals.at(2)));
  }
  // adjacency list
  for (int uin : uins_) {
    std::list<std::pair<int, std::string>> neighbors;
    std::pair<int, std::string> relation;
    for (auto i = relationships_.cbegin(); i != relationships_.cend(); i++) {
      if (i->first.first == uin) {
        relation = std::pair<int, std::string>(i->first.second, i->second);
        neighbors.push_back(relation);
      } else if (i->first.second == uin) {
        relation = std::pair<int, std::string>(i->first.first, i->second);
        neighbors.push_back(relation);
      }
    }
    adj_list_.insert(
        std::pair<int, std::list<std::pair<int, std::string>>>(uin, neighbors));
  }
}

// for (std::string line; std::getline(ifs2, line); line = "") {
//   std::vector<std::string> vals = utilities::Split(line, ',');
//   int uin1 = stoi(vals.at(0));
//   int uin2 = stoi(vals.at(1));
//   if (uin1 == uin) {
//     relation = std::pair<int, std::string>(uin2, vals.at(2));
//     neighbors.push_back(relation);
//   } else if (uin2 == uin) {
//     relation = std::pair<int, std::string>(uin1, vals.at(2));
//     neighbors.push_back(relation);
//   }
// }

const std::list<std::pair<int, std::string>>& IlliniBook::GetAdjacencyList(
    int vertex) const {
  return adj_list_.find(vertex)->second;
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
  bool related = false;
  if (GetRelated(uin_1, uin_2) > 0) {
    related = true;
  }
  return related;
}
bool IlliniBook::AreRelated(int uin_1,
                            int uin_2,
                            const std::string& relationship) const {
  bool related = false;
  if (GetRelated(uin_1, uin_2, relationship) > 0) {
    related = true;
  }
  return related;
}
int IlliniBook::GetRelated(int uin_1, int uin_2) const {
  std::queue<std::pair<int, int>> q;
  q.push(std::pair<int, int>(uin_1, 0));
  std::map<int, bool> visited;
  visited[uin_1] = true;
  while (!q.empty()) {
    std::pair<int, int> node = q.front();
    int student1 = node.first;
    int dist = node.second;
    q.pop();
    if (student1 == uin_2) {
      return dist;
    }
    for (const std::pair<int, std::string>& s : GetAdjacencyList(student1)) {
      if (!visited[s.first]) {
        visited[s.first] = true;
        q.push(std::pair<int, int>(s.first, dist + 1));
      }
    }
  }
  return -1;
}

int IlliniBook::GetRelated(int uin_1,
                           int uin_2,
                           const std::string& relationship) const {
  std::queue<std::pair<int, int>> q;
  q.push(std::pair<int, int>(uin_1, 0));
  std::map<int, bool> visited;
  visited[uin_1] = true;
  while (!q.empty()) {
    std::pair<int, int> node = q.front();
    int student1 = node.first;
    int dist = node.second;
    q.pop();
    if (student1 == uin_2) {
      return dist;
    }
    for (const std::pair<int, std::string>& s : GetAdjacencyList(student1)) {
      if (!visited[s.first] && s.second == relationship) {
        visited[s.first] = true;
        q.push(std::pair<int, int>(s.first, dist + 1));
      }
    }
  }
  return -1;
}
std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
  std::vector<int> matched;
      std::queue<std::pair<int, int>> q;
      q.push(std::pair<int, int>(uin, 0));
      std::map<int, bool> visited;
      visited[uin] = true;
      while (!q.empty()) {
        std::pair<int, int> node = q.front();
        int student1 = node.first;
        int dist = node.second;
        q.pop();
        if (dist == n) {
          matched.push_back(student1);
        }
        for (const std::pair<int, std::string>& s :
             GetAdjacencyList(student1)) {
          if (!visited[s.first]) {
            visited[s.first] = true;
            q.push(std::pair<int, int>(s.first, dist + 1));
          }
        }
      }
    // if (GetRelated(student, uin) == n && !Contains(matched, student)) {
    //   matched.push_back(student);
    // }
  return matched;
}

// nvm, BFS seems to be better to debug than using DFS lol

size_t IlliniBook::CountGroups() const {
  // std::vector<int> start;
  // int origin = uins_.at(0);
  // std::vector<int> end = DFS(start, origin);
  // std::vector<int> not_visited;
  // not_visited = NotVisited(end);
  // int count = 1;
  // while (!not_visited.empty()) {
  //   int origin = not_visited.at(0);
  //   end = DFS(end, origin);
  //   not_visited = NotVisited(end);
  //   count++;
  // }
  // return count;
  std::queue<int> q;
  std::map<int, bool> visited;
  int count = 0;
  for (int student : uins_) {
    // starts a new BFS search, means a new connected component
    if (!visited[student]) {
      count++;
      q.push(student);
      visited[student] = true;
      while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (const std::pair<int, std::string>& s : GetAdjacencyList(node)) {
          if (!visited[s.first]) {
            visited[s.first] = true;
            q.push(s.first);
          }
        }
      }
    }
  }
  return count;
}

size_t IlliniBook::CountGroups(const std::string& relationship) const {
  std::queue<int> q;
  std::map<int, bool> visited;
  int count = 0;
  for (int student : uins_) {
    if (!visited[student]) {
      count++;
      q.push(student);
      visited[student] = true;
      while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (const std::pair<int, std::string>& s : GetAdjacencyList(node)) {
          if (!visited[s.first] && s.second == relationship) {
            visited[s.first] = true;
            q.push(s.first);
          }
        }
      }
    }
  }
  return count;
}

size_t IlliniBook::CountGroups(
    const std::vector<std::string>& relationships) const {
  // std::vector<int> start;
  // int origin = uins_.at(0);
  // std::vector<int> end = DFS(start, origin, relationships);
  // std::vector<int> not_visited;
  // not_visited = NotVisited(end);
  // int count = 1;
  // while (!not_visited.empty()) {
  //   int origin = not_visited.at(0);
  //   end = DFS(end, origin, relationships);
  //   not_visited = NotVisited(end);
  //   count++;
  // }
  // return count;
  std::queue<int> q;
  std::map<int, bool> visited;
  int count = 0;
  for (int student : uins_) {
    if (!visited[student]) {
      count++;
      q.push(student);
      visited[student] = true;
      while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (const std::pair<int, std::string>& s : GetAdjacencyList(node)) {
          if (!visited[s.first] && Contains(relationships, s.second)) {
            visited[s.first] = true;
            q.push(s.first);
          }
        }
      }
    }
  }
  return count;
}

// count helpers (override)
// std::vector<int> IlliniBook::DFS(const std::vector<int>& vals, int node)
// const {
//   std::vector<int> visited = vals;
//   if (Contains(visited, node)) {
//     visited.push_back(node);
//   }
//   for (const std::pair<int, std::string>& neighbor :
//   GetAdjacencyList(node)) {
//     if (Contains(visited, neighbor.first)) {
//       visited.push_back(neighbor.first);
//       return DFS(visited, neighbor.first);
//     }
//   }
//   return visited;
// }

// make sure only nodes passed in have right relationships
// std::vector<int> IlliniBook::DFS(const std::vector<int>& vals,
//                                  int node,
//                                  const std::string& relationship) const {
//   std::vector<int> visited = vals;
//   if (Contains(visited, node)) {
//     visited.push_back(node);
//   }
//   for (const std::pair<int, std::string>& neighbor :
//   GetAdjacencyList(node)) {
//     if (Contains(visited, neighbor.first) && neighbor.second ==
//     relationship) {
//       visited.push_back(neighbor.first);
//       int vertex = neighbor.first;
//       return DFS(visited, vertex, relationship);
//     }
//   }
//   return visited;
// }

// std::vector<int> IlliniBook::DFS(
//     const std::vector<int>& vals,
//     int node,
//     const std::vector<std::string>& relationships) const {
//   std::vector<int> visited = vals;
//   if (std::count(visited.begin(), visited.end(), node) == 0) {
//     visited.push_back(node);
//   }
//   for (const std::pair<int, std::string>& neighbor :
//   GetAdjacencyList(node)) {
//     if (Contains(visited, neighbor.first) &&
//         Contains(relationships, neighbor.second)) {
//       visited.push_back(neighbor.first);
//       int vertex = neighbor.first;
//       return DFS(visited, vertex, relationships);
//     }
//   }
//   return visited;
// }
// std::vector<int> IlliniBook::NotVisited(const std::vector<int>& vals) const {
//   std::vector<int> not_visited;
//   for (int n : uins_) {
//     if (Contains(vals, n)) {
//       not_visited.push_back(n);
//     }
//   }
//   return not_visited;
// }

// override
bool IlliniBook::Contains(const std::vector<int>& vals, int node) const {
  for (int n : vals) {
    if (n == node) {
      return true;
    }
  }
  return false;
}

bool IlliniBook::Contains(const std::vector<std::string>& vals,
                          const std::string& node) const {
  for (const std::string& n : vals) {
    if (n == node) {
      return true;
    }
  }
  return false;
}

// // debugging methods
// void IlliniBook::PrintUINS() {
//   std::cout << "Student IDs" << std::endl;
//   for (int student : uins_) {
//     std::cout << student << std::endl;
//   }
// }

// std::vector<int> IlliniBook::GetUINS() { return uins_; }

// void IlliniBook::PrintMap() {
//   for (auto i = relationships_.cbegin(); i != relationships_.cend(); i++) {
//     std::cout << "Student 1: " << i->first.first
//               << " Student 2: " << i->first.second
//               << " Relationship: " << i->second << std::endl;
//   }
// }
// void IlliniBook::PrintAdjList() {
//   for (int student : uins_) {
//     for (const std::pair<int, std::string>& neighbor :
//          GetAdjacencyList(student)) {
//       std::cout << "For uin: " << student << " related to: " <<
//       neighbor.first
//                 << " by: " << neighbor.second << "  ";
//     }
//   }
// }