#include <SPI.h>
#include <Gamebuino.h>

Gamebuino gb;

void setup()
{
    gb.begin();
    gb.titleScreen(F("Sandtris"));
    gb.battery.show = false;
}

void loop()
{
    if (gb.update())
    {
        // ticks every second
        if (gb.frameCount % 20 == 0)
        {
        }

        gb.display.drawRect(2, 2, 24, 44);
        gb.display.drawRect(3, 3, 22, 42);
    }
}
