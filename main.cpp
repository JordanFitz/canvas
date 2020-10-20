#include <string>
#include <iostream>
#include <map>
#include "Canvas.hpp"

void update(Canvas* canvas)
{
    
}

void render(Canvas* canvas)
{
    canvas->fillStyle("#fff");
    canvas->fillRect(10, 10, 100, 100);
    canvas->fillStyle("RGB(24, 24, 255)");
    canvas->fillRect(15, 15, 90, 90);
}

int main(int argc, char** argv)
{
    Canvas canvas;

    canvas.width(800);
    canvas.height(600);

    canvas.hookUpdate(&update);
    canvas.hookRender(&render);

    canvas.initialize();
}