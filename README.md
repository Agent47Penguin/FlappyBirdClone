# FlappyBirdClone
This is my attempt at recreating the 2013 hit mobile game Flappy Bird in C using the library Raylib.

## Why?
I've decided to take on the [20 Games Challenge](https://20_games_challenge.gitlab.io/challenge/), this is my first submission. Outside of the challenge, I thought it would be a great opportunity to revisit the beautiful programming language know as C.

## Current Features
- Main Menu
  - Navigation
  - Start
  - Exit 
- Main Game
  - Gravity
  - Collision
  - *Score*
  - *Endless Obstacles*

## Future Features
- May port to CPP for sanity and maintainability reasons
- Main Game
  - ~~Obstacles~~
  - ~~Score~~
  - ~~Time (?)~~
- End Screen
  - Final Score
  - Restart Game Button
  - Track Highscore in .txt file
- The hope at the end is to use Raylib's WASM to make the game browser-friendly

## How to Use
1) Clone the repository to your local machine.
2) Install MinGW (If you haven't already)
3) Open CMD and point it to the repo on your system.
4) Run ``make``, and then ``make run``
5) voila
