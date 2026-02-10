# Survival CLI Game (C)

A console-based survival game written in C, focused on player progression, resource management, and persistent game state.

This project was created as a personal learning exercise after completing a university C programming course, in order to practice core programming concepts such as structures, file handling, modular design, and state management.

---

## Features

### Player System
- Custom player name
- Health (HP) and dynamic Max HP
- Experience (XP) and Level progression
- Days survived and coin management

### Level System
- Gain XP through actions
- Level increases every 20 XP
- Each level increases Max HP
- Full heal on level up

### Exploration System
Random events:
- Find coins
- Gain XP
- Take damage
- Rare events (high rewards or strong enemies)

Difficulty scales with the number of days survived.

### Rest Mechanic
- Spend coins to restore HP
- Gain small XP bonus

### Market
- Buy health potions
- Instant healing
- Resource management decisions

### Save / Load System
Game state is stored in a file and includes:
- Player name
- HP / Max HP
- Level and XP
- Coins
- Days survived

---

## Gameplay Loop

1. Explore to gather resources and XP  
2. Rest or buy potions to recover  
3. Manage coins and health carefully  
4. Level up and survive as many days as possible  

The game ends when HP reaches 0.

---

## Concepts Practiced

- C language fundamentals
- `struct` for game state management
- Modular programming using functions
- Input handling (`fgets`, `sscanf`)
- Random event systems (`rand`)
- File I/O (`fopen`, `fprintf`, `fgets`, `sscanf`)
- Game loop architecture
- Persistent state (Save/Load)

---

## How to Compile and Run

### Linux / macOS
```bash
gcc main.c -o survival
./survival
