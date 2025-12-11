# Komendy do kompilacji

## Test jednostkowe (22 testy)

Kompilacja:
```bash
clang++ -std=c++11 -g test_main.cpp node/ANode.cpp node/NumberNode.cpp node/OperatorNode.cpp node/VarNode.cpp Tree.cpp templates/Error.cpp templates/TreeBuilder.cpp -o full_test
```

Uruchomienie:
```bash
./full_test
```

Wynik: Wszystkie 22 testy przechodzą.

## Przykłady

Kompilacja:
```bash
clang++ -std=c++11 test_examples_main.cpp templates/Error.cpp templates/TreeBuilder.cpp node/ANode.cpp node/NumberNode.cpp node/OperatorNode.cpp node/VarNode.cpp Tree.cpp -o examples
```

Uruchomienie:
```bash
./examples
```

## Program główny

Kompilacja:
```bash
clang++ -std=c++11 main.cpp ConsoleParser.cpp Tree.cpp node/ANode.cpp node/NumberNode.cpp node/OperatorNode.cpp node/VarNode.cpp templates/Error.cpp -o main
```

Uruchomienie:
```bash
./main
```

## Opcje kompilacji

- `-std=c++11` - standard C++11
- `-Wall` - włącz wszystkie ostrzeżenia
- `-Wextra` - dodatkowe ostrzeżenia
- `-g` - symbole debugowania
