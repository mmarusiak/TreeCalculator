// g++ -std=c++11 -o test_move test_move_semantics.cpp Tree.cpp node/*.cpp && ./test_move

#include "Tree.hpp"
#include <iostream>

void resetCounters() {
    Tree::copyCount = 0;
    Tree::moveCount = 0;
}

void printCounters(const std::string& label) {
    std::cout << label << " - Copies: " << Tree::copyCount 
              << ", Moves: " << Tree::moveCount << std::endl;
}

int main()
{
    std::cout << "===== MOVE SEMANTICS - TEST =====" << std::endl;
    
    // TEST 1: Konstruktor kopiujący
    std::cout << "\n1. Konstruktor kopiujący:" << std::endl;
    resetCounters();
    std::string formula1 = "+ 5 3";
    Tree tree1;
    tree1.loadTreeFromString(formula1);
    Tree tree2 = tree1;
    printCounters("   tree2 = tree1");
    
    // TEST 2: Konstruktor przenoszący
    std::cout << "\n2. Konstruktor przenoszący:" << std::endl;
    resetCounters();
    std::string formula2 = "+ 10 20";
    Tree tree3;
    tree3.loadTreeFromString(formula2);
    Tree tree4 = std::move(tree3);
    printCounters("   tree4 = std::move(tree3)");
    
    // TEST 3: Operator przypisania (kopia)
    std::cout << "\n3. Operator= (kopia):" << std::endl;
    resetCounters();
    std::string formula3 = "* 2 7";
    Tree tree5;
    tree5.loadTreeFromString(formula3);
    Tree tree6;
    tree6 = tree5;
    printCounters("   tree6 = tree5");
    
    // TEST 4: Operator przypisania (przeniesienie)
    std::cout << "\n4. Operator= (przeniesienie):" << std::endl;
    resetCounters();
    std::string formula4 = "/ 100 5";
    Tree tree7;
    tree7.loadTreeFromString(formula4);
    Tree tree8;
    tree8 = std::move(tree7);
    printCounters("   tree8 = std::move(tree7)");

    
    // TEST 5: Porównanie operator+ bez move vs z move
    std::cout << "\n5. Porównanie operator+ BEZ move vs Z move:" << std::endl;
    
    std::cout << "\n   5a) Bez move:" << std::endl;
    resetCounters();
    Tree a1, b1;
    a1.loadTreeFromString(formula1);
    b1.loadTreeFromString(formula2);
    Tree result1 = a1 + b1;
    printCounters("       a1 + b1");
    
    std::cout << "\n   5b) Z move:" << std::endl;
    resetCounters();
    Tree a2, b2;
    a2.loadTreeFromString(formula1);
    b2.loadTreeFromString(formula2);
    Tree result2 = std::move(a2) + std::move(b2);
    printCounters("       std::move(a2) + std::move(b2)");

    return 0;
}
