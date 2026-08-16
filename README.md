# Checkers

A console-based checkers game written in C++, built around a small class hierarchy (`Board`, `Piece`, `Man`, `King`, `Player`, `Pos`).

Based on [robeng1/checkers](https://github.com/robeng1/checkers).

## Features

- Configurable board size, from 7x7 up to 16x16.
- Two-player hot-seat mode, with named players.
- Diagonal moves, single-piece captures, and promotion to king.
- Text-based board rendering after every move.
- One-move undo — take back the last move and replay that turn.

> **Note:** A one-player mode is selectable in spirit (the code structure suggests it was meant to support playing against the computer), but no computer opponent is implemented, so in practice the game is always played by two people at the same console.

## Building

Any C++ compiler that supports C++11 or later will do. For example, with g++:

```sh
g++ -o checkers *.cpp
```

## Running

```sh
./checkers
```

You'll be prompted for:

1. The number of rows (7–16).
2. The number of columns (7–16).
3. Player 1's name.
4. Player 2's name.

Values outside the accepted range default to 8.

## How to Play

The board is displayed with **columns labeled with letters** along the bottom and **rows labeled with digits (and letters `A`–`F` once the row count exceeds 9)** along the left edge.

- Player 1 is **white**, shown as `w` (or `W` once promoted).
- Player 2 is **red**, shown as `r` (or `R` once promoted).

On your turn, you'll be asked for a `FROM` and a `TO` square. Enter each as two characters — **column letter followed by row** — for example `C2`.

### Moving

Every piece moves one square diagonally.

### Capturing

If the square you're moving to is occupied by an opponent's piece, you jump over it and land on the square beyond, capturing that piece — as long as the landing square is empty. If the landing square is itself occupied by another opponent's piece, no capture happens; you simply swap places with the piece you tried to jump.

### Kings

A piece that reaches the far row on the opponent's side is promoted to a king (shown in uppercase). Kings move along the full diagonal rather than one square at a time, and may jump a single opposing piece anywhere along that diagonal.

### Undo

Instead of entering a `FROM` coordinate, type `UNDO` to take back the previous move — the board reverts to its state before that move, and the same player goes again. The prompt reminds you this is available (`FROM (If you want to undo, enter 'UNDO')`) on any turn after the first, except immediately after an undo. Only the single most recent move is kept, so `UNDO` can't be chained to step back further than one move.

### Winning

A player wins by capturing 8 of the opponent's pieces.

## Known Limitations

- `org/rules.txt` (the original rules text distributed with the base project) states the game ends after 10 captures, but the current implementation ends the game at 8 — the code, not the text file, reflects actual behavior.
- The one-player mode has no AI opponent.
- The screen-clearing call (`system("cls")`) targets Windows consoles; on other platforms the screen simply won't clear between turns.
- Undo only remembers one move back; it can't be used repeatedly to step through the whole game history.
