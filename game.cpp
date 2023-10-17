#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

float object_half_size_y = 10.f;
float object_row1_half_size_x = 15;
float object_row2_half_size_x = 10;
float object_row3_half_size_x = 20;

struct objectToDraw {
	float pos_x;
	float pos_y;
	float half_size_x;
	float half_size_y;
	u32 color;
};

objectToDraw enemy1 = {-110.f, -20.f, object_row1_half_size_x, object_half_size_y, 0x0000ff};
objectToDraw enemy2 = { 0.f, -20.f, object_row1_half_size_x, object_half_size_y, 0x0000ff};
objectToDraw enemy3 = { 85.f, 0.f, object_row2_half_size_x, object_half_size_y, 0x00ff00};
objectToDraw enemy4 = { 15.f, 0.f, object_row2_half_size_x, object_half_size_y, 0x00ff00};
objectToDraw enemy5 = { -35.f, 0.f, object_row2_half_size_x, object_half_size_y, 0x00ff00};
objectToDraw enemy6 = { -110.f, 20.f, object_row3_half_size_x, object_half_size_y, 0xffff00};

objectToDraw enemyObjects[] = {enemy1, enemy2, enemy3, enemy4, enemy5, enemy6};

float player_half_size_x = 10, player_half_size_y = 10;
float player_pos_x = 0.f;
float player_pos_y = -40.f;

internal bool
colision(float p1x, float p1y, float hs1x, float p2x, float p2y, float hs2x) 
{
	return (p1x + hs1x > p2x - hs2x &&
		p1x - hs1x < p2x + hs2x &&
		p1y == p2y);
}

internal void simulate_game(Input* input, float dt)
{
	clear_screen(0x000000);

	float speed = 10.f;

	if (pressed(BUTTON_UP))
		player_pos_y += 20.f;
	if (pressed(BUTTON_DOWN))
		player_pos_y -= 20.f;
	if (pressed(BUTTON_LEFT))
		player_pos_x -= 20.f;
	if (pressed(BUTTON_RIGHT))
		player_pos_x += 20.f;

#define enemyObjSpeed(n) enemyObjects[n-1].pos_x

	enemyObjSpeed(1) += speed * 4 * dt;
	enemyObjSpeed(2) += speed * 4 * dt;
	enemyObjSpeed(3) -= speed * 3 * dt;
	enemyObjSpeed(4) -= speed * 3 * dt;
	enemyObjSpeed(5) -= speed * 3 * dt;
	enemyObjSpeed(6) += speed * 5 * dt;

	if (enemyObjects[0].pos_x > 110.f)
		enemyObjects[0].pos_x = -110.f;

	if (enemyObjects[1].pos_x > 110.f)
		enemyObjects[1].pos_x = -110.f;

	if (enemyObjects[2].pos_x < -110.f)
		enemyObjects[2].pos_x = 110.f;

	if (enemyObjects[3].pos_x < -110.f)
		enemyObjects[3].pos_x = 110.f;

	if (enemyObjects[4].pos_x < -110.f)
		enemyObjects[4].pos_x = 110.f;

	if (enemyObjects[5].pos_x > 110.f)
		enemyObjects[5].pos_x = -110.f;

#define objColision(n) player_pos_x, player_pos_y, player_half_size_x, enemyObjects[(n-1)].pos_x, enemyObjects[(n-1)].pos_y, enemyObjects[(n-1)].half_size_x

	if (colision(objColision(1)))
	{
		player_pos_x = 0.f;
		player_pos_y = -40.f;
	}
	if (colision(objColision(2)))
	{
		player_pos_x = 0.f;
		player_pos_y = -40.f;
	}
	if (colision(objColision(3)))
	{
		player_pos_x = 0.f;
		player_pos_y = -40.f;
	}
	if (colision(objColision(4)))
	{
		player_pos_x = 0.f;
		player_pos_y = -40.f;
	}
	if (colision(objColision(5)))
	{
		player_pos_x = 0.f;
		player_pos_y = -40.f;
	}
	if (colision(objColision(6)))
	{
		player_pos_x = 0.f;
		player_pos_y = -40.f;
	}

	for (int i = 0; i < sizeof(enemyObjects); i++)
	{
		draw_rect(enemyObjects[i].pos_x, enemyObjects[i].pos_y, enemyObjects[i].half_size_x, enemyObjects[i].half_size_y, enemyObjects[i].color);
	}
	
	draw_rect(player_pos_x, player_pos_y, player_half_size_x, player_half_size_y, 0xff0000);
	if (player_pos_y > 39.f)
	{
		running = false;
	}
}
