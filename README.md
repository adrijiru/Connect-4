# Connect 4 in C 🎮
The famous game Connect 4 written in C, featuring:
- 👥 A **PvP** mode.
- 🤖 A **human** vs **bot** mode.
- A **Minimax-based AI** for decision making.
- **Colored terminal output** for a clean visual board.

## 🧩 Features
- **Two players:** P1 (🟦 blue) and P2/AI (🟥 red).
- **Dynamic board size:** Default 7x6 (`MxN`) grid, with a default winning condition of **4 in a row** (`K`).
- **Gravity simulation:** Pieces fall to the lowest available position (_yet to be animated_)
- **Victory detection:** Checks for horizontal, vertical, and both diagonal alignments.
- **Minimax algorithm:** The bot simulates possible future plays to choose the best column to play.

## 🧠 AI Logic
- It builds a **game tree** using the function `MiniMax(Node *arrel, int nivell)`.
- Each node represents a **possible board** state after a move, with a **score** associated to the board.
- The algorithm **backtracks** recursively to pass on the best possible move in each situation.
If no clear advantage is found, the AI defaults to a **central column preference**.

## 💿 Compilation & Execution
On Linux/macOS
```
gcc -o joc.c arbre.c -o ./play
./play
```
On Windows (with ANSI colors)
```
gcc -o joc.c arbre.c -o play.exe
play.exe
```
>**_NOTE:_** `system("")` is used to enable ANSI color support on some Windows terminals.

## 🕹️ How to Play
1. The program prints the current board.
2. The player selects a column number from 1 to N.
3. The piece falls to the lowest available cell.
4. The bot automatically plays its move using Minimax.
5. The game continues until a player connects 4 or the board is full (tie).

Pieces are shown as
- 🟦 Player 1
- 🟥 Player 2/AI

## 🧰 Future Imporvements
- Code optimization
- Implement difficulty levels (depth-based)
- Save and load game states.
- Highlight the 4 in-a-row sequence.
- Refreshing the screen after every turn.
- Making a menu and a visually appealing gamemplay.

## License
This project is licensed under the [CC BY-NC-ND 4.0 License](http://creativecommons.org/licenses/by-nc-nd/4.0/).  
You may read and share the code for educational purposes, but modification and commercial use are not allowed.
