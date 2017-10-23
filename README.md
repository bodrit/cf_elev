## Build

- clang 3.3+
- gcc 4.9+

git clone --recursive --branch=master https://github.com/igorous/cf_elev.git

cmake . && make

## Run

./bin/elevator MAX_FLOOR FLOOR_HEIGHT ELEVATOR_MOVE_SPEED DOORS_TIME_GAP
---------------------------------------------------------------------------
MAX_FLOOR: integer, from interval [5, 20]"                                 
FLOOR_HEIGHT: positive float, meters"                                      
ELEVATOR_MOVE_SPEED: positive float, meters/sec"                           
DOORS_TIME_GAP: positive float, time between doors opening and closing, sec

After launching elevator daemon you can insert floor number. It doesn't matter
if elevator was called inside or outside of elevator.


## Algo
- If no calls: poll
- If got single call from floor N: go to floor N, on every floor check if got call from this floor
while running
- If got multiple calls - pick closest floor and run as if it's single call from that floor


## Sources
- main.cpp - launches elevator daemon in detached thread and waits for input in main thread
- config.h/config.cpp - config checking logic separated from main elevator class
- blocking_set.h - mutexed map for elevator daemon
- elevator.h/elevator.cpp - main class
- util.h/util.cpp - small utility funcs


## Optional
- tests - few test cases for travis testing mainly
- .travis.yml - travis config (just to try travis)
