#include "Tree.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    std::string formula = "";
    std::cout << "Podaj dzialanie w Notacji Polskiej: ";
    std::getline(std::cin, formula);

    while (formula.empty())      // skip empty line if needed
        std::getline(std::cin, formula);


    Tree myTree;
    myTree.loadTreeFromString(formula);
    std::map<std::string, double> vars;
    vars["aVar"] = 3.14;
    bool success = true;
    std::cout << myTree.toString() << " : " << myTree.calculateTree(vars, success) << " " << success << std::endl;
    return 0;
}
