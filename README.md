# CFG Engine - Formal Languages and Automata Theory

> Vlad-Andrei MINCIUNESCU - 151 (2024 - 2025) <br>
> Faculty of Mathematics and Informatics <br>
> University of Bucharest

## Description


This small application offers a fully-functional CFG (Context-Free Grammar) Engine, which I found very helpful for better understanding of Formal Languages and Automata Theory.
- <b>Programming language:</b> C++ 20
- <b>Concepts:</b> OOP, FLA Theory, Data Structures
- <b>How to run?</b>
  - There is required a compiler which supports C++ 20 (ex: GCC via MinGW)
  - Clone the repository and open the project in CLion or your preferred IDE
  - Ensure that the CMakeLists.txt is configured as in this repository
  - Build and run! Feel free to explore and modify the main source!

## Features

Each defined CFG object has well-defined functionalities:

- #### Programatic defitinion:
> ```
> CFG = (V, Σ, R, S)
> - V - Non-terminals
> - Σ - Terminals
> - R - Production rules
> - S - Start symbol: S
> ```

- #### Definition visualizer [Preview]
> ```
> Non-terminal: {C, D, S}
> Terminals: {a, b, c}
> Productions:
> | C -> c D
> | D ->
> | S -> a S b C
> | S ->
> Start symbol: S
>  ```

- #### Definition validator

- #### Compatible string generator 

- #### String derivation visualizer [Preview]
```
S -> aSb -> aaSbb -> aaεbb -> aabb
```

- #### Compatible string recognizer

## Implementation

### Engine 

Browse: [HEADER](./include/Engine.h) / [SRC](./src/Engine.cpp)
- Singleton application object, referenced through instances
- CFG configuration updater [see <i>setCurrentCFG()</i>]
- Holds routes to described functionalities

### CFG

Browse: [HEADER](./include/CFG.h) / [SRC](./src/CFG.cpp) 
