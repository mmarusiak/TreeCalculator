#include "Tree.hpp"
#include <sstream>
#include <string>

// Inicjalizacja zmiennych statycznych
int Tree::copyCount = 0;
int Tree::moveCount = 0;

namespace {

    // Recursive helper to print node and its children
    void printNode(const ANode* node, const std::string& prefix, bool isLast, std::stringstream& ss) {
        if (!node) return;

        ss << prefix;

        ss << (isLast ? "└──" : "├──");
        ss << node->toString() << "\n";

        // New prefix for children
        std::string childPrefix = prefix + (isLast ? "    " : "│   ");

        // Iterate over children
        for (size_t i = 0; i < node->getChildren().size(); ++i) {
            printNode(node->getChildren()[i], childPrefix, i == node->getChildren().size() - 1, ss);
        }
    }

    void preorderWalkFormula(const ANode* node, std::string& string)
    {
        string += " " + node->toString();
        for(int i = 0; i < node->getChildren().size(); ++ i) preorderWalkFormula(node->getChildren()[i], string);
    }
}

// Konstruktor domyślny
Tree::Tree() : root(nullptr), initialized(false)
{
}

// Destruktor
Tree::~Tree()
{
    delete root;
}

// Konstruktor kopiujący - deep clone
Tree::Tree(const Tree& other) : initialized(other.initialized)
{
    ++copyCount;
    if (other.root) {
        root = other.root->clone();
    } else {
        root = nullptr;
    }
}

// Konstruktor przenoszący
Tree::Tree(Tree&& other) noexcept : root(other.root), initialized(other.initialized)
{
    ++moveCount;
    other.root = nullptr;
    other.initialized = false;
}

// Operator przypisania (kopia)
Tree& Tree::operator=(const Tree& other)
{
    ++copyCount;
    if (this != &other) {
        delete root;
        initialized = other.initialized;
        if (other.root) {
            root = other.root->clone();
        } else {
            root = nullptr;
        }
    }
    return *this;
}

// Operator przypisania (przeniesienie)
Tree& Tree::operator=(Tree&& other) noexcept
{
    ++moveCount;
    if (this != &other) {
        delete root;
        root = other.root;
        initialized = other.initialized;
        other.root = nullptr;
        other.initialized = false;
    }
    return *this;
}

void Tree::loadTreeFromString(const std::string& input)
{
    int offset = 0;
    root = ANode::parseFromString(input, offset);
    initialized = true;
}

const std::vector<std::string>& Tree::getVars() const
{
    static const std::vector<std::string> emptyVec;
    if (!initialized) return emptyVec;
    return root->getVars();
}


std::string Tree::toString() {
    std::stringstream ss;
    printNode(root, "", true, ss);  // root is considered last at top level
    std::string outcome = ss.str() + "\n";
    preorderWalkFormula(root, outcome);
    return outcome;
}

double Tree::calculateTree(std::map<std::string, double>& vars, bool& success)
{
    return (*root)(vars, success);
}

Tree& Tree::operator+=(Tree& other)
{
    if (!initialized)
    {
        root = other.root;
        initialized = true;
    }
    else if (root->getChildren().size() == 0)
        root = other.root;
    else root->replaceLeaf(*(other.root));

    // nie chcemy przy zwalnianiu drzewa zwalniać roota!
    other.root = nullptr;
    
    return *this;
}

// Operator+ zwraca wynik przez wartość
Tree Tree::operator+(const Tree& other) const
{
    Tree result(*this);  // kopia this
    result += const_cast<Tree&>(other);
    return result;
}

// Move-optimized wersja - gdy other jest rvalue
Tree Tree::operator+(Tree&& other) const
{
    Tree result(*this);  // kopia this
    result += other;
    return result;  // RVO/move
}