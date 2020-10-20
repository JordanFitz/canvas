#include <string>
#include <iostream>
#include <map>
#include "Canvas.hpp"
#include "Image.hpp"

Image image;

void update(Canvas* canvas)
{
    
}

void render(Canvas* canvas)
{
    canvas->fillStyle("#0F0");
    canvas->fillRect(10, 10, 210, 210);
    canvas->fillStyle("#fff");
    canvas->fillRect(10, 10, 100, 100);
    canvas->fillStyle("RGB(24, 24, 255)");
    canvas->fillRect(15, 15, 90, 90);
    canvas->drawImage(image, 120, 10, 100, 100);
    canvas->drawImage(image, 10, 120, 100, 100);
    canvas->drawImage(image, 150, 230, 100, 100, 120, 120, 100, 100);
    canvas->strokeStyle("rgba(255, 0, 0, 0.5)");
    canvas->lineWidth(2);
    canvas->strokeRect(10, 10, 210, 210);
}

int main(int argc, char** argv)
{
    image.src("W:\\pictures\\test4.jpg");
    Canvas canvas;

    canvas.width(800);
    canvas.height(600);

    canvas.hookUpdate(&update);
    canvas.hookRender(&render);

    canvas.initialize();
}