#pragma once

/*
	Content:

	# Window Utilities
	# Misc
	# Random
	# Input
	# Rendering

*/

#include <string>

enum class Button
{
	Left,
	Right,
};

enum class Key
{
	Left,
	Right,
	Up,
	Down,
	Space,
	Escape,
	Return,
};

struct Color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a = 255;
};

constexpr Color black   = Color{ 0,     0,   0, 255 };
constexpr Color white   = Color{ 255, 255, 255, 255 };
constexpr Color red     = Color{ 255,   0,   0, 255 };
constexpr Color green   = Color{   0, 255,   0, 255 };
constexpr Color blue    = Color{   0,   0, 255, 255 };
constexpr Color cyan    = Color{   0, 255, 255, 255 };
constexpr Color magenta = Color{ 255,   0, 255, 255 };
constexpr Color yellow  = Color{ 255, 255,   0, 255 };

// ############################
// #     Window Utilities     #
// ############################

/* 
	Creates a window of size "window_width" by "window_height" with "title" as the title.
	It also initializes baked-in resources like the font that will be used by the draw_text() function.
*/
void initialize(unsigned int window_width, unsigned int window_height, const std::string& title);

bool is_window_open();
int  get_window_width();
int  get_window_height();
void set_window_title(const std::string& title); // Don't call this every frame, call it after initializing before the main loop.

// ###############
// #     Misc    #
// ###############

constexpr inline int floor_to_int(float value) { return static_cast<int>(value); }
constexpr inline int round_to_int(float value) { return floor_to_int(value + 0.5f); }

// ##################
// #     Random     #
// ##################

// Returns a random floating point number in the range [0, 1[
float random_float_01();

// Returns a random floating point number in the range [min, max[
float random_float_in_range(float min, float max);

// Returns a random integer in the range [min, max[
int random_int_in_range(int min, int max);

// #################
// #     Input     #
// #################

bool is_key_held_down(Key key);
bool is_key_pressed(Key key);  // This will return true only during the frame when the key was pressed.
bool is_key_released(Key key); // This will return true only during the frame when the key was released.

int get_mouse_x();
int get_mouse_y();
bool is_button_held_down(Button button);
bool is_button_pressed(Button button);  // This will return true only during the frame when the button was pressed.
bool is_button_released(Button button); // This will return true only during the frame when the button was released.

// #####################
// #     Rendering     #
// #####################

// Fills the window with the clear_color, you can change it with set_clear_color()
void clear_window(); 

/*
	IMPORTANT: display() is a very important function, it needs to be called at the end of every frame.
	Roughly speaking, it swaps the image currently displayed inside the window with the one that has been rendered
	during the current frame using the draw_*() functions. 

	Every draw_*() function and clear_window() will change an off-screen image that will then be
	displayed in the window by calling this function. 
*/
void display();

void set_clear_color(unsigned char r, unsigned char g, unsigned char b);
void set_clear_color(Color color);

// This uses white as the color.
void draw_pixel(int x, int y);

void draw_pixel(int x, int y, Color color);
void draw_pixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);

// This uses white as the color.
void draw_rectangle(int top_left_x, int top_left_y, int width, int height);

void draw_rectangle(int top_left_x, int top_left_y, int width, int height, Color color);
void draw_rectangle(int top_left_x, int top_left_y, int width, int height, unsigned char r, unsigned char g, unsigned char b, unsigned char a);

// This uses white as the color.
void draw_circle(int center_x, int center_y, int radius);

void draw_circle(int center_x, int center_y, int radius, Color color);
void draw_circle(int center_x, int center_y, int radius, unsigned char r, unsigned char g, unsigned char b, unsigned char a);

void draw_text(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a, const std::string& text);
void draw_text(int x, int y, Color color, const std::string& text);


/*
*	Notes for whoever wants to extend/reuse this:
*
*	This is mostly a wrapper around SFML, the objective is to simplify the API for SFML. (And extensively reduce the capabilities)
*   If you make your own version of this consider that here we're allowing for only one window by keeping a pointer to it in the Context. (see galba.cpp)
*	This practice however goes against the design of SFML, the correct use would be to create a window in the main() function and use RAII to manage itself.
*	The reason for discouraging having globals (that have a destructor) is because SFML has gloabals itself and the call order of the distructors
*	is not well defined in C++.
*
*	We decided to implement it this way nonetheless because we want the API to be as simple as possible; involving RAII would
*	require knowing the concept of class, constructor, destructor and scope (and others). Which users of this codebase likely don't know yet.
*
*	Filippo Crocchini, 08/2022
*/