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

Button* button_init(int x, int y, int width, int height, sfColor color);
void button_destroy(Button* button);
void button_render(Button* button, sfRenderWindow* window);
bool button_over(Button* button, int x, int y);

#endif