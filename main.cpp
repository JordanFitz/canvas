#define _USE_MATH_DEFINES
#include "Canvas.hpp"
//#include "Image.hpp"
//#include "TextMetrics.hpp"

void update(Canvas& canvas)
{
    
}

//void render(Canvas* canvas)
//{
//    canvas->clearRect();
//
//    canvas->fillStyle("#0F0");
//    canvas->fillRect(10, 10, 210, 210);
//
//    canvas->fillStyle("#fff");
//    canvas->fillRect(10, 10, 100, 100);
//
//    canvas->fillStyle("RGB(24, 24, 255)");
//    canvas->fillRect(15, 15, 90, 90);
//
//    canvas->drawImage(image, 120, 10, 100, 100);
//    canvas->drawImage(image, 10, 120, 100, 100);
//    canvas->drawImage(image, 150, 230, 100, 100, 120, 120, 100, 100);
//
//    canvas->lineWidth(2);
//    canvas->strokeStyle("rgba(255, 0, 0, 0.5)");
//    canvas->strokeRect(10, 10, 210, 210);
//
//    canvas->fillStyle("indianred");
//    canvas->fillText("Text test", 10, 220);
//
//    canvas->lineWidth(2);
//    canvas->strokeStyle("lime");
//    canvas->strokeRect(10, 230, canvas->measureText("Text test").width, 45);
//
//    canvas->lineWidth(5);
//
//    /*canvas->beginPath();
//    canvas->moveTo(250, 250);
//    canvas->lineTo(350, 150);
//    canvas->lineTo(450, 250);
//    canvas->lineTo(350, 350);
//    canvas->closePath();
//
//    canvas->stroke();
//
//    canvas->strokeStyle("#0ff");
//    canvas->beginPath();
//    canvas->moveTo(275, 275);
//    canvas->lineTo(375, 175);
//    canvas->lineTo(475, 275);
//    canvas->lineTo(375, 375);
//    canvas->closePath();
//
//    canvas->stroke();*/
//
//    canvas->fillStyle("#0f0");
//    float m = 100;
//    float x = 450, y = 250;
//    canvas->beginPath();
//    canvas->moveTo(x+m*cos(l),y+m*sin(l));
//    canvas->lineTo(x+m*cos(l+PI_2),y+m*sin(l+PI_2));
//    canvas->lineTo(x+m*cos(l+2*PI_2),y+m*sin(l+2*PI_2));
//    canvas->lineTo(x+m*cos(l+3*PI_2),y+m*sin(l+3*PI_2));
//    canvas->closePath();
//    canvas->stroke();
//    l += 0.001;
//}

void render(Canvas& canvas)
{
    canvas.clearRect();

    canvas.lineWidth(10);
    canvas.beginPath();
    canvas.arc(50, 50, 25, M_PI, 2*M_PI);
    canvas.stroke();

    /*canvas.strokeStyle("darksalmon");
    canvas.fillStyle(canvas.strokeStyle());
    canvas.lineWidth(10);
    canvas.lineJoin("miter");
    canvas.strokeRect(75, 140, 150, 110);
    canvas.fillRect(130, 190, 40, 60);
    canvas.beginPath();
    canvas.moveTo(50, 140);
    canvas.lineTo(150, 60);
    canvas.lineTo(250, 140);
    canvas.closePath();
    canvas.stroke();

    canvas.lineWidth(1);
    canvas.strokeStyle("#09f");
    canvas.beginPath();
    canvas.moveTo(10, 10);
    canvas.lineTo(140, 10);
    canvas.moveTo(10, 140);
    canvas.lineTo(140, 140);
    canvas.stroke();

    canvas.strokeStyle("black");
    canvas.lineWidth(15);

    const char* lineCap[] = {"butt", "round", "square"};
    for (uint8_t i = 0; i < 3; i++) {
        canvas.lineCap(lineCap[i]);
        canvas.beginPath();
        canvas.moveTo(25 + i * 50, 10);
        canvas.lineTo(25 + i * 50, 140);
        canvas.stroke();
    }*/
}

int main(int argc, char** argv)
{
    Canvas canvas;

    /*image.src("W:\\pictures\\test4.jpg");
    canvas.loadFont("Arial", "W:\\dev\\canvas\\arial.ttf");
    canvas.font("underline 45px Arial");*/

    /*canvas.addEventListener("keypress", [](const sf::Event& event) {
        
    });*/

    //canvas.lineJoin("round");

    canvas.width(800);
    canvas.height(600);

    canvas.hookUpdate(&update);
    canvas.hookRender(&render);

    canvas.initialize();

    return 0;
}
