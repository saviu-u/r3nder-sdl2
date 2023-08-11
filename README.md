# r3nder-sdl2
Demo project to learn some 3d concepts on the SDL2 lib


## Preview:
![Preview](doc/preview.gif)

## Description
This demo was an exploration about 3d geometry and how it can be cast into a 2d screen

## Techniques used
The math concepts used were:
- 2D projection (in the axis X and Y)
- Vector transformation with matrix

## Why won't this repo have more updates?
In my opinion, SDL has their own limitation, it is not meant to be used for 3d applications, a lot of concepts needs to be manually implemented, I used this project to learn how it could be manually done, this should not be used in any serious project aside from learning

For example, the next step for this project would be implementing faces and their render order, which to be honest, wouldn't be too hard, only calculating faces median and rendering them in order last to first, the issue would be for faces intersecting each other, it would be way more complex and I am not even sure what is the math required to calculate such thing

For my own learning, I rather move to OpenGL first, maybe in a near feature I come back to implement more things if I feel like