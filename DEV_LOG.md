# Snake Game Dev Log
## Game Logic

### movement and player control
- The player controls the direction of movement of the snake through keyboard keys (UP, DOWN, LEFT, RIGHT)
- 180-deg Movement must be prevented (the snake can't move left while it moves right)
- Keys must be "pressed" (not held down) to change direction - uses IsKeyPressed() instead of IsKeyDown()
- Each key set the speed position :
    - KEY_RIGHT => speed {x,0}
    - KEY_DOWN => speed {0,y}
- Then for each 6 frames, the snake uses the stored speed coordinates to actually move
- The snake moves every 6 frames to prevent the snake to move very fast.

### The snake's body 
- snake is an array of structs each struct stores rectangle properties and speed
- the body of the snake is segments. Which needs to be intialized first off
- we store the position of each segment in snake_prev_pos[] and then uses it 
- when head moves to its next position, the following segment takes the previous position of the head
- What if you have 3 segments?
    - Segment 1 moves to where the head was
    - Segment 2 moves to where segment 1 was
    - Segment 3 moves to where segment 2 was

### Randomize Food
- we choose rows and columns randomly through GetRandomValue()
- then convert them into pixels and assign them to the coordinates of the food rectangle
- For the result to appear as Food position randomized but fitting completely into grid cells
- The food must not intersect with the snake's body :
    - check if the new coordinates of the food equals any coordinates of the body 
    - if true, generate new random coordinates and check starting from the head again.
    - else,proceed to the next segment to check
    - After the whole length is checked, flag a valid_food_position : true

### Collision between snake and food 
- we use CheckCollisionRecs(), to determine if the food and the snake[0]'s head collided or not
- When collision happens:
    -  we set the valid_food_position flag to 0 to indicate the need for the next valid position
    -  Then increment the length of the snake.
    -  each new segment is placed exactly where the previous tail segment was using the updated length.

### Losing the game
- We Lose the game when:
    1. The snake eates itself
        - check if the head coordinates would intersects with any segment of the body
        - if true, indicate game over
    2. The snake hit a border of the play fiels 
        - check head's coordinates with play field's coordinates



<br/>

## TO DO
- [x] make the tail bend 
- [x] start the game running 
- [x] collision logic 
- [x] drawing the length of the snake 
- [x] When are you losing the game?
- [x] Game states
- [x] food position shouldn't intersect with the snake's tail 
- [x] Scoring system, highest score,... etc
- [x] Adjust play field all the controls,...etc
- [x] all the controls(p=>pause , ENTER => play , ESC => Exist,...etc)
- [x] Organize the code more clearly


### [ Tuesday 24-6-2025  03:03 ] :
1. Drew grid lines.
2. grid-based movement of the player
3. Successfully made the food exactly on the cell, but it disappears suddenly ?!!
![Snake2025-06-2506-11-14-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/721a3121-9585-4763-a028-a39996417b62)


### [ Wednesday 25-6-2025  03:20 ] :
1. fixed that randomly disappearing food from yesterday
2. Improved key controls (changed IsKeyDown to IsKeyPressed)
3. implemented player movement with speed 
4. implemented the body logic but there's still a problem with drawing the tail??!
![Snake2025-06-2603-16-17-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/3d3dbb3a-3103-4701-995f-8b35a0d67e35)


### [ Thursday 26-6-2025  03:10 ] :
1. Now the tail shows (only needed to intialize the body segments)
2. allowe movement only in one direction (the snake can't move left while it moves right) AKA reversal or 180-deg turn. Acomplished that through checking if the speed in the desired direction is zero
3. Updated Randomized food logic (now the food will not appear on the sanke's tail (on a position where the snake has segments))
![Snake2025-06-2704-03-09-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/ad144ffd-ff7d-4fda-8398-b1d84c1d131c)


### [ Friday 27-6-2025  05:30 ] :
1. modified screen width and added padding around the play field
2. An overdue task that should have been done earlier : organized the code more clearly
3. implemented losing logic
4. Handeled different states of the game 
5. Initial try on colors
6. a weird bug keeps on happening on first collision, still trying to figure it out !!!


### [ Friday 27-6-2025  03:00 ] :
1. Changed Colors of the game
2. Solved the glitch that was happening with the first collision
3. improved the text on different state screens







