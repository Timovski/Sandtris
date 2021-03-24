#include <SPI.h>
#include <Gamebuino.h>

Gamebuino gb;

void draw_pixel(int x, int y);
void draw_field_of_play();
void draw_field_of_play_border();

const int number_of_rows = 10;
const int number_of_columns = 20;

void setup()
{
	gb.begin();
	gb.titleScreen(F("Sandtris"));
	gb.pickRandomSeed();
	gb.battery.show = false;
}

struct TetriminoPixel
{
	int x;
	int y;
	bool live = false;

	TetriminoPixel()
	{
	}

	~TetriminoPixel()
	{
	}

	bool getBar()
	{
	}
};

struct FieldOfPlay
{
	bool field_of_play[12][22] = {{false}};

	FieldOfPlay()
	{
		for (int x = 0; x < 12; x++)
		{
			field_of_play[x][0] = true;
			field_of_play[x][21] = true;
		}

		for (int y = 1; y < 21; y++)
		{
			field_of_play[0][y] = true;
			field_of_play[11][y] = true;
		}
	}

	~FieldOfPlay()
	{
	}

	bool is_true(int x, int y)
	{
		return field_of_play[x][y];
	}

	void draw()
	{
		for (int x = 0; x < 12; x++)
		{
			for (int y = 0; y < 22; y++)
			{
				if (field_of_play[x][y])
				{
					draw_pixel(x, y);
				}
			}
		}
	}
} fp;

struct TetriminoMap
{
	TetriminoPixel pixels[4] = {TetriminoPixel(), TetriminoPixel(), TetriminoPixel(), TetriminoPixel()};

	bool tetrimino_map[12][22] = {{false}};

	TetriminoMap()
	{
		pixels[0].x = 5;
		pixels[0].y = 1;
		pixels[0].live = true;

		pixels[1].x = 6;
		pixels[1].y = 1;
		pixels[1].live = true;

		pixels[2].x = 7;
		pixels[2].y = 1;
		pixels[2].live = true;

		pixels[3].x = 6;
		pixels[3].y = 2;
		pixels[3].live = true;

		tetrimino_map[5][1] = true;
		tetrimino_map[6][1] = true;
		tetrimino_map[7][1] = true;
		tetrimino_map[6][2] = true;
	}

	~TetriminoMap()
	{
	}

	void move_down()
	{
		auto any_live = false;

		for (auto &pixel : pixels)
		{
			if (pixel.live)
			{
				auto i = 0;
				do
				{
					i++;
					// if the pixel below is pixel
					if (tetrimino_map[pixel.x][pixel.y + i])
						continue;

					// if the pixel below is map
					if (fp.field_of_play[pixel.x][pixel.y + i])
					{
						// make pixel part of map
						fp.field_of_play[pixel.x][pixel.y] = true;

						// remove from live pixels
						pixel.live = false;
					}
					else
						any_live = true;

					break;
				} while (true);
			}
		}

		if (!any_live)
		{
			pixels[0].x = 5;
			pixels[0].y = 1;
			pixels[0].live = true;

			pixels[1].x = 6;
			pixels[1].y = 1;
			pixels[1].live = true;

			pixels[2].x = 7;
			pixels[2].y = 1;
			pixels[2].live = true;

			pixels[3].x = 6;
			pixels[3].y = 2;
			pixels[3].live = true;

			tetrimino_map[5][1] = true;
			tetrimino_map[6][1] = true;
			tetrimino_map[7][1] = true;
			tetrimino_map[6][2] = true;
		}

		for (auto &pixel : pixels)
		{
			tetrimino_map[pixel.x][pixel.y] = false;
		}

		for (auto &pixel : pixels)
		{
			if (pixel.live)
			{
				pixel.y++;
			}
		}

		for (auto &pixel : pixels)
		{
			if (pixel.live)
			{
				tetrimino_map[pixel.x][pixel.y] = true;
			}
		}
	}

	void draw()
	{
		for (int x = 0; x < 12; x++)
		{
			for (int y = 0; y < 22; y++)
			{
				if (tetrimino_map[x][y])
				{
					draw_pixel(x, y);
				}
			}
		}
	}
} tm;

enum TetriminoShape
{
	I,
	O,
	T,
	J,
	L,
	S,
	Z
} ts;

struct Tetrimino
{
	TetriminoPixel pixels[4] = {TetriminoPixel(), TetriminoPixel(), TetriminoPixel(), TetriminoPixel()};

	Tetrimino()
	{
	}

	~Tetrimino()
	{
	}

	void get_new()
	{
		int tetrimino_type_number = rand() % 7;
		ts = static_cast<TetriminoShape>(tetrimino_type_number);
		ts = T;

		int p0x, p0y,
			p1x, p1y,
			p2x, p2y,
			p3x, p3y;

		switch (ts)
		{
		case I:
			p0x = 4, p0y = 1;
			p1x = 5, p1y = 1;
			p2x = 6, p2y = 1;
			p3x = 7, p3y = 1;
			break;
		case O:
			p0x = 5, p0y = 1;
			p1x = 6, p1y = 1;
			p2x = 5, p2y = 2;
			p3x = 6, p3y = 2;
			break;
		case T:
			p0x = 5, p0y = 1;
			p1x = 6, p1y = 1;
			p2x = 7, p2y = 1;
			p3x = 6, p3y = 2;
			break;
		case J:
			p0x = 5, p0y = 1;
			p1x = 6, p1y = 1;
			p2x = 7, p2y = 1;
			p3x = 5, p3y = 2;
			break;
		case L:
			p0x = 5, p0y = 1;
			p1x = 6, p1y = 1;
			p2x = 7, p2y = 1;
			p3x = 7, p3y = 2;
			break;
		case S:
			p0x = 6, p0y = 1;
			p1x = 7, p1y = 1;
			p2x = 5, p2y = 2;
			p3x = 6, p3y = 2;
			break;
		case Z:
			p0x = 5, p0y = 1;
			p1x = 6, p1y = 1;
			p2x = 6, p2y = 2;
			p3x = 7, p3y = 2;
			break;
		default:
			break;
		}

		pixels[0].x = p0x;
		pixels[0].y = p0y;
		pixels[0].live = true;

		pixels[1].x = p1x;
		pixels[1].y = p1y;
		pixels[1].live = true;

		pixels[2].x = p2x;
		pixels[2].y = p2y;
		pixels[2].live = true;

		pixels[3].x = p3x;
		pixels[3].y = p3y;
		pixels[3].live = true;
	}

	void move_down()
	{
		bool any_live = false;

		for (int i = 0; i < 4; i++)
		{
			//TetriminoPixel *pixel = &pixels[i];
			TetriminoPixel &pixel = pixels[i];

			if (pixel.live)
			{
				any_live = true;

				// if the pixel below is map
				if (fp.field_of_play[pixel.x][pixel.y + 1])
				{
					// make part of map
					fp.field_of_play[pixel.x][pixel.y] = true;

					// remove from live pixels
					pixel.live = false;
				}
				else
				{
					pixel.y++;
				}
			}
		}

		if (!any_live)
		{
			get_new();
		}
	}

	void draw()
	{
		for (int i = 0; i < 4; i++)
		{
			if (pixels[i].live)
			{
				draw_pixel(pixels[i].x, pixels[i].y);
			}
		}
	}
} t;

void loop()
{
	if (gb.update())
	{
		// ticks every second
		if (gb.frameCount % 20 == 0)
		{
			tm.move_down();
		}

		//	t.move_down();
		tm.draw();
		fp.draw();
	}
}

void draw_pixel(int x, int y)
{
	x = x * 2 + 2;
	y = y * 2 + 2;
	gb.display.drawRect(x, y, 2, 2);
}