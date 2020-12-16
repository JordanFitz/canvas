#include "Canvas.hpp"

constexpr float PI = 3.14159f;

struct Data
{
    float rotation = 0,
        distance = 0,
        maxDistance = 50,
        radius = 300,
        rotationInterval = .01f,
        distanceInterval = .55f;

    uint8_t points = 5,
        pointMod = 2;
    
    std::string color = "rgba(255, 255, 255, 0.5)";

    sf::Vector2u centerScreen;

    bool direction = false;
};

Data data;

void update(Canvas::Canvas& canvas)
{
    data.centerScreen = sf::Vector2u(canvas.width() / 2, canvas.height() / 2);

    float addition = data.rotationInterval;

    data.rotation += fmod(data.rotationInterval, (2.0f * PI));

    if (!data.direction)
    {
        data.distance += data.distanceInterval;

        if (data.distance >= data.maxDistance)
        {
            data.direction = true;
        }
    }
    else
    {
        data.distance -= data.distanceInterval;

        if (data.distance <= -data.maxDistance)
        {
            data.direction = false;
        }
    }
}

void render(Canvas::Canvas& canvas)
{
    auto& context = canvas.getContext();

    context.clearRect();

    const float interval = (2.0f * PI) / static_cast<float>(data.points * data.pointMod);

    context.strokeStyle(data.color);
    context.beginPath();

    for (uint8_t i = 0; i < data.points * data.pointMod; i++)
    {
        const float angle = static_cast<float>(i) * interval + data.rotation;

        float x = static_cast<float>(data.centerScreen.x),
            y = static_cast<float>(data.centerScreen.y);

        if (i % data.pointMod == 0)
        {
            x += data.radius * cos(angle);
            y += data.radius * sin(angle);
        }
        else
        {
            x += (data.radius + data.distance) * cos(angle);
            y += (data.radius + data.distance) * sin(angle);
        }

        if (i == 0)
        {
            context.moveTo(x, y);
        }
        else
        {
            context.lineTo(x, y);
        }
    }

    context.closePath();
    context.stroke();
}

int main(int argc, char** argv)
{
    Canvas::Canvas canvas;

    canvas.backgroundColor("#020203");

    canvas.width(1280);
    canvas.height(720);

    canvas.hookUpdate(&update);
    canvas.hookRender(&render);

    canvas.addEventListener("wheel", [](const Canvas::Event& event) {
        const auto& wheel = dynamic_cast<const Canvas::WheelEvent&>(event);
    }); 

    canvas.addEventListener("mousemove", [](const Canvas::Event& event) {
        const auto& mouse = dynamic_cast<const Canvas::MouseEvent&>(event);
        printf("%d, %d\n", mouse.button(), mouse.buttons());
        printf("%d,%d\n", mouse.clientX(), mouse.clientY());
        printf("%d,%d\n", mouse.screenX(), mouse.screenY());
        printf(
            "alt: %s, ctrl: %s, shift: %s, meta: %s\n",
            mouse.altKey() ? "true" : "false",
            mouse.ctrlKey() ? "true" : "false",
            mouse.shiftKey() ? "true" : "false",
            mouse.metaKey() ? "true" : "false"
        );
    });

    return canvas.initialize();
}
