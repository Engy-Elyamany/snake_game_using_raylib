# 🐍Snake Game

my main goal from this project was to put my C knowledge in use and solidfy it along the way. And that did become true through:
- Using structs to attribute properties like dimension, position and speed to the snake 
- Using enums to handle multiple game states
- Effeciently Implementing the game logic through multiple collections of loops , conditionals and arrays
- Using static and extern modifiers to handle different variables through the implementation
- Practicing a clean project structure :
    - (snake_game.h) : for all the macros,typedefs and function declarations.
    - (snake_game.c) : for the actual implementation of the game logic.
    -    (main.c)    : Our entry point for the execution.

It has been an interesting few days to actually learn Raylib from scratch and have the abiliy to do all of these cool stuff with it 

🚀 You can take a look at the logic i used throughout the implementation from [DEV_LOG.md](https://github.com/Engy-Elyamany/snake_game_using_raylib/blob/main/DEV_LOG.md), I also used it as my daily to-do list and a study-log 

https://github.com/user-attachments/assets/4c07ce58-00be-4a39-95f8-32df1f2b6d61



## 📃Features
- Classic Snake gameplay mechanics
- Grid-based movement system
- Multiple game states (Start, Play, Pause, Game Over)
- Responsive controls
- Food collision detection
- Wall collision detection
- Self-collision detection

## 🎮Controls
- **Arrow Keys**: Change snake direction
- **ENTER**: Start game/restart after game over
- **P**: Pause game during play
- **ESC**: Exit game (from Game Over screen)

## 🎯Game Mechanics
- Snake moves at a fixed speed (adjustable via frame counter)
- Each food eaten increases snake length and score
- Game ends if snake hits walls or itself
- Food spawns randomly but never on snake body

## 📚Resources
- [Raylib Cheat sheet](https://www.raylib.com/cheatsheet/cheatsheet.html)
- [Official Raylib examples Repo](https://github.com/raysan5/raylib/tree/master/examples)

## 🔆Area of improvement
- Add multiple levels with diverse play field designs
- Add sprites and custome graphics
- Add sound effects 
- Snake's speed increases with higher score
- Compare with highest score 

## 🛹Try it for yourself
    UNZIP this folder and click on the .exe file 
   [Source Code ZIP](https://github.com/Engy-Elyamany/snake_game_using_raylib/blob/main/snake_game_disrtribution.rar)
