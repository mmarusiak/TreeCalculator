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
    static int copyCount;    // licznik kopii
    static int moveCount;    // licznik przesunięć

    Tree();
    ~Tree();
    
    // Konstruktor kopiujący
    Tree(const Tree& other);
    
    // Konstruktor przenoszący
    Tree(Tree&& other) noexcept;
    
    // Operator przypisania (kopia)
    Tree& operator=(const Tree& other);
    
    // Operator przypisania (przeniesienie)
    Tree& operator=(Tree&& other) noexcept;
    
    void loadTreeFromString(const std::string& input);
    std::string toString();
    const std::vector<std::string>& getVars() const;
    double calculateTree(std::map<std::string, double>& vars, bool& success);

    Tree& operator+=(Tree& other);
    
    // Operator+ zwraca przez wartość
    Tree operator+(const Tree& other) const;
    
    // Move-optimized wersja operator+
    Tree operator+(Tree&& other) const;
};

#endif
