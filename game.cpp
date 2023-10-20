#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

#define backToScreenRight(n)\
if (enemyObjects[(n)].pos_x > 110.f)\
	enemyObjects[(n)].pos_x = -110.f;

#define backToScreenLeft(n)\
if (enemyObjects[(n)].pos_x < -110.f)\
	enemyObjects[(n)].pos_x = 110.f;

#define checkColision(n)\
if (colision(player_pos_x, player_pos_y, player_half_size_x, enemyObjects[(n)].pos_x, enemyObjects[(n)].pos_y, enemyObjects[(n)].half_size_x))\
{\
	player_pos_x = 0.f;\
	player_pos_y = -45.f;\
	running = false;\
};

#define addEnemyObject(i,j,k,l,n) (i), (j), object_row_half_size_x[(k-1)], object_half_size_y, (l), object_row_color[(n-1)]

int level = 1;
float speed = 10.f;
float player_half_size_x = 5, player_half_size_y = 5;
float player_pos_x = 0.f;
float player_pos_y = -45.f;
float object_half_size_y = 5.f;
float speed_gain = 1.f;
internal bool
colision(float p1x, float p1y, float hs1x, float p2x, float p2y, float hs2x) 
{
	return (p1x + hs1x > p2x - hs2x &&
		p1x - hs1x < p2x + hs2x &&
		p1y == p2y);
}

#define enemyObjSpeed(n) enemyObjects[n-1].pos_x
#define enemyObjSpeedPositive(n) enemyObjects[(n)].pos_x += speed * (enemyObjects[(n)].speed_x + speed_gain) * dt
#define enemyObjSpeedNegative(n) enemyObjects[(n)].pos_x -= speed * (enemyObjects[(n)].speed_x + speed_gain) * dt
#define objColision(n) player_pos_x, player_pos_y, player_half_size_x, enemyObjects[(n-1)].pos_x, enemyObjects[(n-1)].pos_y, enemyObjects[(n-1)].half_size_x

internal int simulate_game(Input* input, float dt, float* object_row_half_size_x, u32* object_row_color, objectToDraw* enemyObjects)
{
	clear_screen(0x000000);
	draw_number(level, 85.f, 45.f, 1.f, 0xbbffbb);

	if (pressed(BUTTON_UP))
	{
		player_pos_y += 10.f;
	}
	if (pressed(BUTTON_DOWN) && player_pos_y > -40.f)
	{
		player_pos_y -= 10.f;
	}
	if (pressed(BUTTON_LEFT) && player_pos_x > -80.f)
	{
		player_pos_x -= 10.f;
	}
	if (pressed(BUTTON_RIGHT) && player_pos_x < 80.f)
	{
		player_pos_x += 10.f;
	}
	switch (level % 2)
	{

		case(1):
		{
			{
				for (int i = 0; i < sizeof(enemyObjects); i++)
				{
					enemyObjSpeedPositive(i);
				}

				for (int i = 0; i < sizeof(enemyObjects); i++)
				{
					backToScreenRight(i);
				}

				for (int i = 0; i < sizeof(enemyObjects); i++)
				{
					checkColision(i);
				}

				for (int i = 0; i < sizeof(enemyObjects); i++)
				{
					draw_rect(enemyObjects[i].pos_x, enemyObjects[i].pos_y, enemyObjects[i].half_size_x, enemyObjects[i].half_size_y, enemyObjects[i].color);
				}

				draw_rect(player_pos_x, player_pos_y, player_half_size_x, player_half_size_y, 0xff0000);
				if (player_pos_y > 39.f)
				{
					speed_gain += 1.f;
					player_pos_x = 0.f;
					player_pos_y = -45.f;
					level++;
				}
			}
		}break;
		case(0):
		{
			{
				for (int i = 0; i < sizeof(enemyObjects); i++)
				{
					enemyObjSpeedNegative(i);
				}

				for (int i = 0; i < sizeof(enemyObjects); i++)
				{
					backToScreenLeft(i);
				}

				for (int i = 0; i < sizeof(enemyObjects); i++)
				{
					checkColision(i);
				}
				for (int i = 0; i < sizeof(enemyObjects); i++)
				{
					draw_rect(enemyObjects[i].pos_x, enemyObjects[i].pos_y, enemyObjects[i].half_size_x, enemyObjects[i].half_size_y, enemyObjects[i].color);
				}

				draw_rect(player_pos_x, player_pos_y, player_half_size_x, player_half_size_y, 0xff0000);
				if (player_pos_y > 39.f && level < 3)
				{
					player_pos_x = 0.f;
					player_pos_y = -45.f;
					level++;
				}
				if (player_pos_y > 39.f)
				{
					speed_gain += 1.f;
					player_pos_x = 0.f;
					player_pos_y = -45.f;
					level++;
				}
			}
		}break;
	}
	return level;
}
