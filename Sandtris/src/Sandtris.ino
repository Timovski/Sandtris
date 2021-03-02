#include <SPI.h>
#include <Gamebuino.h>

Gamebuino gb;

void draw_pixel(int8_t x, int8_t y);
void draw_field_of_play();

bool field_of_play[10][20] = {{false}};

void setup()
{
	gb.begin();
	gb.titleScreen(F("Sandtris"));
	gb.pickRandomSeed();
	gb.battery.show = false;
}

int8_t x_pos = 0;
int8_t y_pos = 0;

void loop()
{
	if (gb.update())
	{
		// ticks every second
		if (gb.frameCount % 20 == 0)
		{
			x_pos++;
			y_pos++;
		}

		draw_pixel(x_pos, y_pos);
		draw_field_of_play();
	}
}

void draw_pixel(const int8_t x, const int8_t y)
{
	const int8_t x_coordinate = x * 2 + 4;
	const int8_t y_coordinate = y * 2 + 4;
	gb.display.drawRect(x_coordinate, y_coordinate, 2, 2);
}

void draw_field_of_play()
{
	gb.display.drawRect(2, 2, 24, 44);
	gb.display.drawRect(3, 3, 22, 42);
}