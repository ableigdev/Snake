#ifndef SNAKE_CONSTANTS_H
#define SNAKE_CONSTANTS_H

namespace helpers
{
    enum Colors { LIGHTGREEN = 10, WHITE = 15 };
    enum Direction { RIGHT = 0, UP, LEFT, DOWN };
    enum tagsOfTheGameSpace { FREE_SPACE = 0, SNAKE_BODY, WALL, FRUIT, SNAKE_HEAD, SNAKE_TAIL };
}

#endif // SNAKE_CONSTANTS_H
