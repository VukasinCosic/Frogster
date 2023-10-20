struct Button_State {
	bool is_down;
	bool changed;
};

enum {
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,

	BUTTON_COUNT, // Should be the last item
};

struct Input {
	Button_State buttons[BUTTON_COUNT];
};

struct objectToDraw {
	float pos_x;
	float pos_y;
	float half_size_x;
	float half_size_y;
	float speed_x;
	u32 color;
};