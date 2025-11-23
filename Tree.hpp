#ifndef Tree_H
#define Tree_H

#include "node/ANode.hpp"
#include <string>
#include <vector>
#include <map>

// ordered/unordered - tablica mieszajaca/drzewo

class Tree {
    ANode* root;
    std::string& formulaFromArgs(const std::vector<std::string>& args);

  public:
    bool initialized;

    ~Tree(){
      delete root;
    }
    void loadTreeFromString(std::string& input);
    std::string toString();
    const std::vector<std::string>& getVars() const;
    double calculateTree(std::map<std::string, double>& vars, bool& success);

    Tree& operator+=(const Tree& other);
};

#endif
