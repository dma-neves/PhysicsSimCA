#ifndef BUTTON
#define BUTTON

#include <stdbool.h>
#include <SFML/Graphics.h>

typedef struct _Button
{
    int x, y;
    int width, height;
    bool active;

    sfRectangleShape* rect;
} Button;

Button* createButton(int x, int y, int width, int height, sfColor color);
void destroyButton(Button* button);
void b_render(Button* button, sfRenderWindow* window);
bool over(Button* button, int x, int y);

#endif