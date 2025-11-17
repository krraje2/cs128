#ifndef ILLINI_BOOK_HPP
#define ILLINI_BOOK_HPP

#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "utilities.hpp"

class IlliniBook {
public:
  IlliniBook(const std::string& people_fpath,
             const std::string& relations_fpath);
  IlliniBook(const IlliniBook& rhs) = delete;
  IlliniBook& operator=(const IlliniBook& rhs) = delete;
  ~IlliniBook() = default;
  bool AreRelated(int uin_1, int uin_2) const;
  bool AreRelated(int uin_1, int uin_2, const std::string& relationship) const;
  int GetRelated(int uin_1, int uin_2) const;
  int GetRelated(int uin_1, int uin_2, const std::string& relationship) const;
  std::vector<int> GetSteps(int uin, int n) const;
  size_t CountGroups() const;
  size_t CountGroups(const std::string& relationship) const;
  size_t CountGroups(const std::vector<std::string>& relationships) const;


  // helpers
  const std::list<std::pair<int, std::string>>& GetAdjacencyList(
      int vertex) const;
  //   std::list<std::pair<int, std::string>>& GetAdjacencyList(int vertex);
  // int GetRelatedHelper1(int kUin1, int kUin2) const;
  // std::vector<int> DFS(const std::vector<int>& vals, int node) const;
  // std::vector<int> DFS(const std::vector<int>& vals,
  //                   int node,
  //                   const std::string& relationship) const;
  // std::vector<int> DFS(const std::vector<int>& vals,
  //                   int node,
  //                   const std::vector<std::string>& relationships) const;
  // std::vector<int> NotVisited(const std::vector<int>& vals) const;
  bool Contains(const std::vector<int>& vals, int node) const;
  bool Contains(const std::vector<std::string>& vals, const std::string& node) const;

// printers for debugging
// void PrintUINS();
// void PrintMap();
// void PrintAdjList();


private:
  std::vector<int> uins_;
  // std::vector<std::string> test_;
  std::map<std::pair<int, int>, std::string> relationships_;
  std::map<int, std::list<std::pair<int, std::string>>> adj_list_;
};

#endif
