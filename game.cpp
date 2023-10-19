#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

#define backToScreenRight(n)\
if (enemyObjects[(n)].pos_x > 110.f)\
	enemyObjects[(n)].pos_x = -110.f;

#define checkColision(n)\
if (colision(player_pos_x, player_pos_y, player_half_size_x, enemyObjects[(n)].pos_x, enemyObjects[(n)].pos_y, enemyObjects[(n)].half_size_x))\
{\
	player_pos_x = 0.f;\
	player_pos_y = -45.f;\
};

#define addEnemyObject(i,j,k,l) (i), (j), object_row_half_size_x[(k-1)], object_half_size_y, object_row_color[(l-1)]

int level = 1;
float speed = 10.f;
float player_half_size_x = 5, player_half_size_y = 5;
float player_pos_x = 0.f;
float player_pos_y = -45.f;
float object_half_size_y = 5.f;
float object_row_half_size_x[] = {  15.f,
									10.f,
									20.f};

u32 object_row_color[] = {  0x0000ff,
							0x00ff00,
							0xffff00 };

objectToDraw enemyObjects[] = { {addEnemyObject(-110.f,-35.f,1,1)},
								{addEnemyObject(-90.f,-25.f,2,2)},
								{addEnemyObject(-70.f,-15.f,3,3)},
								{addEnemyObject(-50.f,-5.f,1,1)},
								{addEnemyObject(-30.f,5.f,2,2)},
								{addEnemyObject(-10.f,15.f,3,3)},
								{addEnemyObject(10.f,25.f,1,1)},
								{addEnemyObject(30.f,35.f,2,2)}
							 };

internal bool
colision(float p1x, float p1y, float hs1x, float p2x, float p2y, float hs2x) 
{
	return (p1x + hs1x > p2x - hs2x &&
		p1x - hs1x < p2x + hs2x &&
		p1y == p2y);
}

#define enemyObjSpeed(n) enemyObjects[n-1].pos_x
#define objColision(n) player_pos_x, player_pos_y, player_half_size_x, enemyObjects[(n-1)].pos_x, enemyObjects[(n-1)].pos_y, enemyObjects[(n-1)].half_size_x

internal void simulate_game(Input* input, float dt/*, float* object_row_half_size_x, u32* object_row_color, objectToDraw* enemyObjects*/)
{
	clear_screen(0x000000);

	if (pressed(BUTTON_UP))
		player_pos_y += 10.f;
	if (pressed(BUTTON_DOWN) && player_pos_y > -40.f)
		player_pos_y -= 10.f;
	if (pressed(BUTTON_LEFT) && player_pos_x > -80.f)
		player_pos_x -= 10.f;
	if (pressed(BUTTON_RIGHT) && player_pos_x < 80.f)
		player_pos_x += 10.f;

	switch (level)
	{
		case(1):
		{
			enemyObjSpeed(1) += speed * 3.f * dt;
			enemyObjSpeed(2) += speed * 4.f * dt;
			enemyObjSpeed(3) += speed * 3.f * dt;
			enemyObjSpeed(4) += speed * 5.f * dt;
			enemyObjSpeed(5) += speed * 4.f * dt;
			enemyObjSpeed(6) += speed * 5.f * dt;
			enemyObjSpeed(7) += speed * 3.f * dt;
			enemyObjSpeed(8) += speed * 6.f * dt;

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
			if (player_pos_y > 39.f && level < 2)
			{
				player_pos_x = 0.f;
				player_pos_y = -45.f;
				//float pos_move = 0;
				//for (int i = 0; i < sizeof(enemyObjects); i++)
				//{
				//	enemyObjects[i].pos_x = 110.f - pos_move;
				//	pos_move += 20.f;
				//}
				//level++;
			}
		}break;
		
		case(2):
		{
			enemyObjSpeed(1) -= speed * 4.f * dt;
			enemyObjSpeed(2) -= speed * 5.f * dt;
			enemyObjSpeed(3) -= speed * 4.f * dt;
			enemyObjSpeed(4) -= speed * 6.f * dt;
			enemyObjSpeed(5) -= speed * 5.f * dt;
			enemyObjSpeed(6) -= speed * 6.f * dt;
			enemyObjSpeed(7) -= speed * 4.f * dt;
			enemyObjSpeed(8) -= speed * 7.f * dt;

			if (enemyObjects[0].pos_x < -110.f)
				enemyObjects[0].pos_x = 110.f;

			if (enemyObjects[1].pos_x < -110.f)
				enemyObjects[1].pos_x = 110.f;

			if (enemyObjects[2].pos_x < -110.f)
				enemyObjects[2].pos_x = 110.f;

			if (enemyObjects[3].pos_x < -110.f)
				enemyObjects[3].pos_x = 110.f;

			if (enemyObjects[4].pos_x < -110.f)
				enemyObjects[4].pos_x = 110.f;

			if (enemyObjects[5].pos_x < -110.f)
				enemyObjects[5].pos_x = 110.f;

			if (enemyObjects[6].pos_x < -110.f)
				enemyObjects[6].pos_x = 110.f;

			if (enemyObjects[7].pos_x < -110.f)
				enemyObjects[7].pos_x = 110.f;

			if (colision(objColision(1)))
			{
				player_pos_x = 0.f;
				player_pos_y = -45.f;
			}
			if (colision(objColision(2)))
			{
				player_pos_x = 0.f;
				player_pos_y = -45.f;
			}
			if (colision(objColision(3)))
			{
				player_pos_x = 0.f;
				player_pos_y = -45.f;
			}
			if (colision(objColision(4)))
			{
				player_pos_x = 0.f;
				player_pos_y = -45.f;
			}
			if (colision(objColision(5)))
			{
				player_pos_x = 0.f;
				player_pos_y = -45.f;
			}
			if (colision(objColision(6)))
			{
				player_pos_x = 0.f;
				player_pos_y = -45.f;
			}
			if (colision(objColision(7)))
			{
				player_pos_x = 0.f;
				player_pos_y = -45.f;
			}
			if (colision(objColision(8)))
			{
				player_pos_x = 0.f;
				player_pos_y = -45.f;
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
			if (level > 2)
				running = false;
		}
	}
}
