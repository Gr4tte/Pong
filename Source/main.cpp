#include "galba.h"

const unsigned STAGE_WIDTH = 1080;
const unsigned STAGE_HEIGHT = 720;
const float FLOAT_MARGIN = 5.0f;

float clampValue(float value, float min, float max) {
	if (value < min) {
		return min;
	}
	else if (value > max) {
		return max;
	}
	else {
		return value;
	}
}

struct Paddle {
	float x;
	float y;
	float width;
	float height;
	float velocity;
	Key up_key;
	Key down_key;

	Paddle(float x = 0.0f, float y = 0.0f, float width = 20.0f, float height = 100.0f, Key up_key = Key::Up, Key down_key = Key::Down)
		:x(x), y(y), width(width), height(height), up_key(up_key), down_key(down_key) {
		velocity = 0.0f;
	};

	void Move() {
		if (is_key_held_down(up_key) && !is_key_held_down(down_key)) {
			velocity = -5.0f;
		}
		else if (is_key_held_down(down_key) && !is_key_held_down(up_key)) {
			velocity = 5.0f;
		}
		else {
			velocity = 0.0f;
		}

		y = clampValue(y + velocity, 0, STAGE_HEIGHT - height);
	};

	void Draw()
	{
		draw_rectangle(
			round_to_int(x),
			round_to_int(y),
			round_to_int(width),
			round_to_int(height)
		);
	};
};

struct Ball {
	float x;
	float y;
	float width;
	float height;
	float velocity_x;
	float velocity_y;
	bool is_in_stage;

	Ball(float x = 0.0f, float y = 0.0f, float width = 20.0f, float height = 20.0f, float velocity_x = 0.0f, float velocity_y = 0.0f)
		:x(x), y(y), width(width), height(height), velocity_x(velocity_x), velocity_y(velocity_y) {
		is_in_stage = true;
	};

	void Move() {
		x += velocity_x;
		y += velocity_y;

		if (x + width > STAGE_WIDTH || x < 0) {
			is_in_stage = false;
		}

		if (y + height > STAGE_HEIGHT || y < 0) {
			velocity_y *= -1.0f;
		}

		x = clampValue(x, 0, STAGE_WIDTH);
		y = clampValue(y, 0, STAGE_HEIGHT);
	};

	void Reset(bool set_velocity = true) {
		x = (STAGE_WIDTH / 2.0f) - (width / 2.0f);
		y = (STAGE_HEIGHT / 2.0f) - (height / 2.0f);
		is_in_stage = true;

		if (set_velocity) {
			velocity_x = 6.0f; // random_float_in_range(3.0f, 6.0f);
			velocity_x *= static_cast<float>((random_int_in_range(0, 99) % 2) * 2 - 1);

			velocity_y = random_float_in_range(0.0f, 5.0f);
			velocity_y *= static_cast<float>((random_int_in_range(0, 99) % 2) * 2 - 1);
		}
		else {
			velocity_x = 0.0f;
			velocity_y = 0.0f;
		}
	}

	void Draw() {
		draw_rectangle(
			round_to_int(x),
			round_to_int(y),
			round_to_int(width),
			round_to_int(height)
		);
	};
};

bool checkOverlap(Paddle paddle, Ball ball)
{
	return !(paddle.x + paddle.width < ball.x || paddle.y + paddle.height < ball.y || paddle.x > ball.x + ball.width || paddle.y > ball.y + ball.height);
}

Paddle left_paddle;
Paddle right_paddle;
Ball ball;

unsigned score_left = 0;
unsigned score_right = 0;

void init()
{
	initialize(STAGE_WIDTH, STAGE_HEIGHT, "Window");

	left_paddle.x = 20.0f;
	left_paddle.y = (STAGE_HEIGHT / 2.0f) - (left_paddle.height / 2.0f);
	left_paddle.up_key = Key::Up;
	left_paddle.down_key = Key::Down;

	right_paddle.x = STAGE_WIDTH - 20.0f - right_paddle.width;
	right_paddle.y = (STAGE_HEIGHT / 2.0f) - (right_paddle.height / 2.0f);
	right_paddle.up_key = Key::Left;
	right_paddle.down_key = Key::Right;

	ball.Reset(false);

	score_left = 0;
	score_right = 0;
}

void update()
{
	left_paddle.Move();
	right_paddle.Move();
	ball.Move();

	if (checkOverlap(left_paddle, ball) && ball.x + FLOAT_MARGIN > left_paddle.x + left_paddle.width) {
		ball.velocity_x *= -1.0f;
		ball.velocity_y -= left_paddle.velocity * random_float_in_range(0.25f, 0.75f);
	}
	else if (checkOverlap(right_paddle, ball) && ball.x + ball.width - FLOAT_MARGIN < right_paddle.x) {
		ball.velocity_x *= -1.0f;
		ball.velocity_y -= right_paddle.velocity * random_float_in_range(0.25f, 0.75f);
	}

	if (!ball.is_in_stage) {
		if (ball.x < STAGE_WIDTH / 2) {
			score_right++;
		}
		else {
			score_left++;
		}

		ball.Reset();
	}

	if (ball.velocity_x == 0.0f && ball.velocity_y == 0.0f && is_key_pressed(Key::Space)) {
		ball.Reset();
	}
	else if (is_key_pressed(Key::Escape))
	{
		ball.Reset(false);
	}
}

void render()
{
	left_paddle.Draw();
	right_paddle.Draw();
	ball.Draw();

	draw_text(STAGE_WIDTH / 2 - 100, 50, white, std::to_string(score_left));
	draw_text(STAGE_WIDTH / 2 + 100, 50, white, std::to_string(score_right));

}

int main(int argc, char** argv)
{
	init();

	while (is_window_open())
	{
		clear_window();

		update();

		render();

		display();
	}

	return 0;
}