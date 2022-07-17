# Minesweeper AI
Text-based minesweeper game made with a game solver AI made in C. Custom algorithm designed and implemented for AI solve. A recursive search function is used to create the board and unveil tiles such that all following adjacent tiles which do not contain mines are revealed. 

# AI Version 1 - Demo @ http://tpcg.io/KJWPKV
For each numbered tile, all adjacent tiles are read; the amount of unrevealed and already flagged tiles are recorded. If the # of adjacent mines (# on the cell) - the # of adjacent flags set by the AI is equal to 0, it is known that all other empty adjacent tiles are "safe" and can be checked. If the # of adjacent mines - the # of adjacent flags set by the AI is equal to the # of empty adjacent tiles, it is known that those empty tiles are mines and must be flagged.

The AI uses a recursive search and conquer algorithm which continously iterates through every tile AND all revealed tiles until a full iteration is completed where a move cannot be safely made. In this case, a random non revealed tile is picked, which may cause the AI to lose, however this is impossible to avoid due to the inherit randomness of Minesweeper.
