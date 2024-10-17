# Space Invaders

 A C/C++ implementation with multithreading and customizable settings.

## Build

To build Space Invaders from source:

```
make
```
or
```
make -j (number of threads)
```

To build the tests from source:
```
make tests
```
To run the tests from source:
```
make test
```

## Playing / Controls

### PLEASE USE FULL SCREEN TO THE PLAY THE GAME FOR THE CORRECT RENDERING !
The controls for the game are:
- a or right to move *right*
- d or left to move *left*
- space to shoot the *normal* shot
- b to shoot the *bomb* shot
- n to shoot the *nuke* shot

## Game information

### The Tank
```
 _/^\_
/ooooo\
```
*The tank* is the players tank.

### The Alien
```
/^\
|||
|||
```
*The Alien* is one of three enemies. *The Alien* shoots  ``X`` .

### The Bomber
```
/P^P\
 |~|
```
*The Bomber* is one of three enemies. The bomber shoots  ``V`` .

### The Destroyer
```
\   /
 ---
 \V/
```
*The Destroyer* is one of three enemies. The Destroyer shoots  ``Y`` .


### Normal shot `*`
The normal shot will kill **one**  *destroyers*, *bombers* or *aliens*. The player has *three* normal shots which will be automatically renewed after the *shot cooldown* .

### Powerups
My primary goal was to make this game a realistic and playable as possible. For this reason, the *powerups* which are implemented as bombs and nukes are randomly given to the player and the player does not need to collect them .

#### Bomb `!`
The bomb will kill **three** *destroyers*, *bombers* or *aliens*. The first one is the one the bomb hits, the second one is the left neighbor if he exists and the third one is the right neighbor if he exists .

#### Nuke `$`
The nuke will kill **five** *destroyers*, *bombers* or *aliens*. The first one is the one the bomb hits, the second one is the left neighbor and the third one the the left neighbor of the left neighbor. The fourth one is the right neighbor and the fifth is the right neighbor of the right neighbor (is they exist).

### The PWall
```
 ======
||    ||
```
*The PWall* is the protection wall.

##  Settings
All configurations are managed with toml.

The configuration file will be automatically created in ``.config/spaceinvaders/config.toml``
and can be managed within the game or by modifying the toml file.

The default configuration file:
```
[Game]
bomb_chance = 'normal'
enemy_speed = 'normal'
nuke_chance = 'normal'
shot_cooldown = 2

[Pwall]
amount = 3
live = 10

[Saves]
high_score = 0
```
#### [Game]
The game section controls the game.

Where **bomb_chance** can be :
- `low`
- `normal`
- `high`

**enemy_speed** can be:
- `slow`
- `normal`
- `fast`

**nuke_chance** can be:
- ``low``
- ``normal``
- `high`

and **shot_cooldown** a number between 0 and 100 .

**Bomb chance** and **nuke chance** control the possibility for the player to receive a bomb or a nuke.
**Enemy speed** controls the speed of the enemies and by that the hardness of the game.
**Shot cooldown** controls the time in *seconds* for the player to receive a new *normal* shot.

#### [Pwall]
Pwall is the protection wall which can be configured with:
- **amount** : A number between 0 and 6 and
- **live**:  a number between 0 and 50 .

 **Amount** is the number of protection walls which will be created and **live** is the number of lives for each wall.

### Saves
Saves is just a parameter which saves the high score.

## Requirements

- g++
- ncurses
- pthread

## Resources
Toml++ v3.4.0 (header only!)

- https://github.com/marzer/tomlplusplus
