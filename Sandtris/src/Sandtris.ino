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
        gb.display.println(F("Hello Sandtris!"));

        int count;

        count = gb.frameCount;

        gb.display.println(count);
    }
}
