// screen.cpp

#include <cassert>

#include "galba.h"

#define SFML_STATIC
#include "SFML/Graphics.hpp"

// Source:
// - https://github.com/dhepper/font8x8
//
// license: 
// - Public Domain
//
constexpr unsigned char font8x8_basic[][8] =
{
   { 0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00},   // U+0021 (!)
   { 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0022 (")
   { 0x36, 0x36, 0x7F, 0x36, 0x7F, 0x36, 0x36, 0x00},   // U+0023 (#)
   { 0x0C, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x0C, 0x00},   // U+0024 ($)
   { 0x00, 0x63, 0x33, 0x18, 0x0C, 0x66, 0x63, 0x00},   // U+0025 (%)
   { 0x1C, 0x36, 0x1C, 0x6E, 0x3B, 0x33, 0x6E, 0x00},   // U+0026 (&)
   { 0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0027 (')
   { 0x18, 0x0C, 0x06, 0x06, 0x06, 0x0C, 0x18, 0x00},   // U+0028 (()
   { 0x06, 0x0C, 0x18, 0x18, 0x18, 0x0C, 0x06, 0x00},   // U+0029 ())
   { 0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00},   // U+002A (*)
   { 0x00, 0x0C, 0x0C, 0x3F, 0x0C, 0x0C, 0x00, 0x00},   // U+002B (+)
   { 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x06},   // U+002C (,)
   { 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00},   // U+002D (-)
   { 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00},   // U+002E (.)
   { 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00},   // U+002F (/)
   { 0x3E, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x3E, 0x00},   // U+0030 (0)
   { 0x0C, 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x3F, 0x00},   // U+0031 (1)
   { 0x1E, 0x33, 0x30, 0x1C, 0x06, 0x33, 0x3F, 0x00},   // U+0032 (2)
   { 0x1E, 0x33, 0x30, 0x1C, 0x30, 0x33, 0x1E, 0x00},   // U+0033 (3)
   { 0x38, 0x3C, 0x36, 0x33, 0x7F, 0x30, 0x78, 0x00},   // U+0034 (4)
   { 0x3F, 0x03, 0x1F, 0x30, 0x30, 0x33, 0x1E, 0x00},   // U+0035 (5)
   { 0x1C, 0x06, 0x03, 0x1F, 0x33, 0x33, 0x1E, 0x00},   // U+0036 (6)
   { 0x3F, 0x33, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x00},   // U+0037 (7)
   { 0x1E, 0x33, 0x33, 0x1E, 0x33, 0x33, 0x1E, 0x00},   // U+0038 (8)
   { 0x1E, 0x33, 0x33, 0x3E, 0x30, 0x18, 0x0E, 0x00},   // U+0039 (9)
   { 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x00},   // U+003A (:)
   { 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x06},   // U+003B (//)
   { 0x18, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x18, 0x00},   // U+003C (<)
   { 0x00, 0x00, 0x3F, 0x00, 0x00, 0x3F, 0x00, 0x00},   // U+003D (=)
   { 0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 0x00},   // U+003E (>)
   { 0x1E, 0x33, 0x30, 0x18, 0x0C, 0x00, 0x0C, 0x00},   // U+003F (?)
   { 0x3E, 0x63, 0x7B, 0x7B, 0x7B, 0x03, 0x1E, 0x00},   // U+0040 (@)
   { 0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00},   // U+0041 (A)
   { 0x3F, 0x66, 0x66, 0x3E, 0x66, 0x66, 0x3F, 0x00},   // U+0042 (B)
   { 0x3C, 0x66, 0x03, 0x03, 0x03, 0x66, 0x3C, 0x00},   // U+0043 (C)
   { 0x1F, 0x36, 0x66, 0x66, 0x66, 0x36, 0x1F, 0x00},   // U+0044 (D)
   { 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x46, 0x7F, 0x00},   // U+0045 (E)
   { 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x06, 0x0F, 0x00},   // U+0046 (F)
   { 0x3C, 0x66, 0x03, 0x03, 0x73, 0x66, 0x7C, 0x00},   // U+0047 (G)
   { 0x33, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x33, 0x00},   // U+0048 (H)
   { 0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},   // U+0049 (I)
   { 0x78, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E, 0x00},   // U+004A (J)
   { 0x67, 0x66, 0x36, 0x1E, 0x36, 0x66, 0x67, 0x00},   // U+004B (K)
   { 0x0F, 0x06, 0x06, 0x06, 0x46, 0x66, 0x7F, 0x00},   // U+004C (L)
   { 0x63, 0x77, 0x7F, 0x7F, 0x6B, 0x63, 0x63, 0x00},   // U+004D (M)
   { 0x63, 0x67, 0x6F, 0x7B, 0x73, 0x63, 0x63, 0x00},   // U+004E (N)
   { 0x1C, 0x36, 0x63, 0x63, 0x63, 0x36, 0x1C, 0x00},   // U+004F (O)
   { 0x3F, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x0F, 0x00},   // U+0050 (P)
   { 0x1E, 0x33, 0x33, 0x33, 0x3B, 0x1E, 0x38, 0x00},   // U+0051 (Q)
   { 0x3F, 0x66, 0x66, 0x3E, 0x36, 0x66, 0x67, 0x00},   // U+0052 (R)
   { 0x1E, 0x33, 0x07, 0x0E, 0x38, 0x33, 0x1E, 0x00},   // U+0053 (S)
   { 0x3F, 0x2D, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},   // U+0054 (T)
   { 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3F, 0x00},   // U+0055 (U)
   { 0x33, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00},   // U+0056 (V)
   { 0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 0x00},   // U+0057 (W)
   { 0x63, 0x63, 0x36, 0x1C, 0x1C, 0x36, 0x63, 0x00},   // U+0058 (X)
   { 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x0C, 0x1E, 0x00},   // U+0059 (Y)
   { 0x7F, 0x63, 0x31, 0x18, 0x4C, 0x66, 0x7F, 0x00},   // U+005A (Z)
   { 0x1E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x1E, 0x00},   // U+005B ([)
   { 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40, 0x00},   // U+005C (\)
   { 0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1E, 0x00},   // U+005D (])
   { 0x08, 0x1C, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00},   // U+005E (^)
   { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF},   // U+005F (_)
   { 0x0C, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0060 (`)
   { 0x00, 0x00, 0x1E, 0x30, 0x3E, 0x33, 0x6E, 0x00},   // U+0061 (a)
   { 0x07, 0x06, 0x06, 0x3E, 0x66, 0x66, 0x3B, 0x00},   // U+0062 (b)
   { 0x00, 0x00, 0x1E, 0x33, 0x03, 0x33, 0x1E, 0x00},   // U+0063 (c)
   { 0x38, 0x30, 0x30, 0x3e, 0x33, 0x33, 0x6E, 0x00},   // U+0064 (d)
   { 0x00, 0x00, 0x1E, 0x33, 0x3f, 0x03, 0x1E, 0x00},   // U+0065 (e)
   { 0x1C, 0x36, 0x06, 0x0f, 0x06, 0x06, 0x0F, 0x00},   // U+0066 (f)
   { 0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x1F},   // U+0067 (g)
   { 0x07, 0x06, 0x36, 0x6E, 0x66, 0x66, 0x67, 0x00},   // U+0068 (h)
   { 0x0C, 0x00, 0x0E, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},   // U+0069 (i)
   { 0x30, 0x00, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E},   // U+006A (j)
   { 0x07, 0x06, 0x66, 0x36, 0x1E, 0x36, 0x67, 0x00},   // U+006B (k)
   { 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},   // U+006C (l)
   { 0x00, 0x00, 0x33, 0x7F, 0x7F, 0x6B, 0x63, 0x00},   // U+006D (m)
   { 0x00, 0x00, 0x1F, 0x33, 0x33, 0x33, 0x33, 0x00},   // U+006E (n)
   { 0x00, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00},   // U+006F (o)
   { 0x00, 0x00, 0x3B, 0x66, 0x66, 0x3E, 0x06, 0x0F},   // U+0070 (p)
   { 0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x78},   // U+0071 (q)
   { 0x00, 0x00, 0x3B, 0x6E, 0x66, 0x06, 0x0F, 0x00},   // U+0072 (r)
   { 0x00, 0x00, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x00},   // U+0073 (s)
   { 0x08, 0x0C, 0x3E, 0x0C, 0x0C, 0x2C, 0x18, 0x00},   // U+0074 (t)
   { 0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x6E, 0x00},   // U+0075 (u)
   { 0x00, 0x00, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00},   // U+0076 (v)
   { 0x00, 0x00, 0x63, 0x6B, 0x7F, 0x7F, 0x36, 0x00},   // U+0077 (w)
   { 0x00, 0x00, 0x63, 0x36, 0x1C, 0x36, 0x63, 0x00},   // U+0078 (x)
   { 0x00, 0x00, 0x33, 0x33, 0x33, 0x3E, 0x30, 0x1F},   // U+0079 (y)
   { 0x00, 0x00, 0x3F, 0x19, 0x0C, 0x26, 0x3F, 0x00},   // U+007A (z)
   { 0x38, 0x0C, 0x0C, 0x07, 0x0C, 0x0C, 0x38, 0x00},   // U+007B ({)
   { 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00},   // U+007C (|)
   { 0x07, 0x0C, 0x0C, 0x38, 0x0C, 0x0C, 0x07, 0x00},   // U+007D (})
   { 0x6E, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+007E (~)
   { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+007F
};

struct Context {
    sf::Color clear_color = sf::Color{ 0x00, 0x00, 0x00 };

    sf::RenderWindow*  window;
    sf::Texture* font_texture; // Leaking this texture

    bool prev_mouse_buttons[sf::Mouse::ButtonCount];
    bool      mouse_buttons[sf::Mouse::ButtonCount];

    bool prev_keys[sf::Keyboard::KeyCount];
    bool      keys[sf::Keyboard::KeyCount];

    ~Context() {
        delete window;
        window = nullptr;
    }
};

Context context = {};

void initialize(unsigned int window_width, unsigned int window_height, const std::string& title) {
    if (context.window)
    {
        return;
    }

    context.window = new sf::RenderWindow({ window_width, window_height }, title);
    context.window->setFramerateLimit(60);

    const int glyph_atlas_columns = 16;
    const int glyph_atlas_rows = 8;
    const int glyph_count = (sizeof(font8x8_basic) / sizeof(font8x8_basic[0]));

    sf::Image image;
    image.create(128, 128, sf::Color(0, 0, 0, 0));
    for (int glyph = 0; glyph < glyph_count; glyph++)
    {
        const int glyph_x = glyph % glyph_atlas_columns * 8;
        const int glyph_y = glyph / glyph_atlas_columns * 8;
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                if (font8x8_basic[glyph][y] & 1 << x)
                {
                    image.setPixel(glyph_x + x, glyph_y + y, sf::Color(0xff, 0xff, 0xff, 0xff));
                }
            }
        }
    }

    context.font_texture = new sf::Texture();

    context.font_texture->loadFromImage(image);
    context.font_texture->setSmooth(false);
    context.font_texture->setRepeated(false);
}

bool is_window_open()
{   
    if (!context.window)
    {
        return false;
    }

    memcpy(context.prev_mouse_buttons, context.mouse_buttons, sizeof(context.mouse_buttons));
    memcpy(context.prev_keys, context.keys, sizeof(context.keys));

    sf::Event event;
    while (context.window->pollEvent(event))
    {
	    switch (event.type) 
        {
            case sf::Event::EventType::MouseButtonPressed:
            {
                context.mouse_buttons[event.mouseButton.button] = true;
            } break;
            case sf::Event::EventType::MouseButtonReleased:
            {
                context.mouse_buttons[event.mouseButton.button] = false;
            } break;

            case sf::Event::EventType::KeyPressed:
            {
                context.keys[event.key.code] = true;
            } break;
            case sf::Event::EventType::KeyReleased:
            {
                context.keys[event.key.code] = false;
            } break;

            case sf::Event::EventType::Resized:
            {
                auto view_size = sf::Vector2f{ (float)event.size.width, (float)event.size.height };
                context.window->setView(sf::View(view_size * 0.5f, view_size));
            } break;
            case sf::Event::EventType::Closed:
            {
                context.window->close();
            } break;
	    }
    }

	return context.window->isOpen();
}

int get_window_width()
{
    if (context.window)
    {
        return context.window->getSize().x;
    }
    return 0;
}

int get_window_height()
{
    if (context.window)
    {
        return context.window->getSize().y;
    }
    return 0;
}

void set_window_title(const std::string& title) {
    if (context.window)
    {
        context.window->setTitle(title);
    }
}

float random_float_01() {
    return rand() / static_cast<float>(RAND_MAX);
}

float random_float_in_range(float min, float max) {
    return random_float_01() * (max - min) + min;
}

int random_int_in_range(int min, int max) {
    return rand() % (max - min) + min;
}

static sf::Keyboard::Key key_to_sfml_key(Key key) {
    switch (key)
    {
        case Key::Left:   return sf::Keyboard::Left;
        case Key::Right:  return sf::Keyboard::Right;
        case Key::Up:     return sf::Keyboard::Up;
        case Key::Down:   return sf::Keyboard::Down;
        case Key::Space:  return sf::Keyboard::Space;
        case Key::Escape: return sf::Keyboard::Escape;
    }

    assert(false);
    return sf::Keyboard::KeyCount;
}

bool is_key_held_down(Key key)
{
    sf::Keyboard::Key code = key_to_sfml_key(key);
    return context.keys[code];
}

bool is_key_pressed(Key key) {
    sf::Keyboard::Key code = key_to_sfml_key(key);
    return !context.prev_keys[code] && context.keys[code];
}

bool is_key_released(Key key) {
    sf::Keyboard::Key code = key_to_sfml_key(key);
    return context.prev_keys[code] && !context.keys[code];
}

int get_mouse_x()
{
    return sf::Mouse::getPosition(*context.window).x;
}

int get_mouse_y()
{
    return sf::Mouse::getPosition(*context.window).y;
}

static sf::Mouse::Button button_to_sfml_button(Button button) {
    switch (button) {
    case Button::Left:  return sf::Mouse::Button::Left;
    case Button::Right: return sf::Mouse::Button::Right;
    }

    assert(false);
    return sf::Mouse::Button::Right;
}

bool is_button_held_down(Button button)
{
    auto sf_button = button_to_sfml_button(button);
    return context.mouse_buttons[sf_button];
}

bool is_button_pressed(Button button) {
    auto sf_button = button_to_sfml_button(button);
    return !context.prev_mouse_buttons[sf_button] && context.mouse_buttons[sf_button];
}

bool is_button_released(Button button) {
    auto sf_button = button_to_sfml_button(button);
    return context.prev_mouse_buttons[sf_button] && !context.mouse_buttons[sf_button];
}


void set_clear_color(unsigned char r, unsigned char g, unsigned char b)
{
    context.clear_color.r = r;
    context.clear_color.g = g;
    context.clear_color.b = b;
}

void set_clear_color(Color color)
{
    set_clear_color(color.r, color.g, color.b);
}

void clear_window()
{
    if (context.window)
    {
        context.window->clear(context.clear_color);
    }
}

void draw_pixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    if (!context.window)
    {
        return;
    }

    sf::RectangleShape shape({ 1,1 });
    shape.setFillColor(sf::Color(r, g, b, a));
    sf::RenderStates rs;
    rs.transform.translate({ float(x), float(y) });
    context.window->draw(shape, rs);
}

void draw_pixel(int x, int y, Color color)
{
    draw_pixel(x, y, color.r, color.g, color.b, color.a);
}

void draw_pixel(int x, int y)
{
    draw_pixel(x, y, white);
}

void draw_rectangle(int x, int y, int width, int height, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    if (!context.window)
    {
        return;
    }

    sf::RectangleShape shape({ float(width), float(height) });
    shape.setFillColor(sf::Color(r, g, b, a));
    sf::RenderStates rs;
    rs.transform.translate({ float(x), float(y) });
    context.window->draw(shape, rs);
}

void draw_rectangle(int x, int y, int width, int height, Color color)
{
    draw_rectangle(x, y, width, height, color.r, color.g, color.b, color.a);
}

void draw_rectangle(int x, int y, int width, int height)
{
    draw_rectangle(x, y, width, height, white);
}

void draw_circle(int center_x, int center_y, int radius, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    if (!context.window)
    {
        return;
    }

#pragma warning(push)
#pragma warning(disable: 26451)
    sf::CircleShape shape((float) radius, 5 + radius);
#pragma warning(pop)

    shape.setOrigin((float) radius, (float) radius);
    shape.setFillColor(sf::Color(r, g, b, a));
    sf::RenderStates rs;
    rs.transform.translate({ (float) center_x, (float) center_y });
    context.window->draw(shape, rs);
}

void draw_circle(int center_x, int center_y, int radius, Color color)
{
    draw_circle(center_x, center_y, radius, color.r, color.g, color.b, color.a);
}

void draw_circle(int center_x, int center_y, int radius)
{
    draw_circle(center_x, center_y, radius, white);
}

void draw_text(int ox, int oy, unsigned char r, unsigned char g, unsigned char b, unsigned char a, const std::string& text)
{
    if (!context.window)
    {
        return;
    }

    const float uvst = 8.0f;
    const int text_scale = 2;
    const int character_width = 8 * text_scale;
    const int line_feed_height = 10 * text_scale;
    const int first_valid_character = (int)'!';
    const int last_valid_character = (int)'~';
    const int invalid_character = (int)'?' - first_valid_character;

    sf::Color color(r, g, b, a);
    std::vector<sf::Vertex> vertices;
    vertices.reserve(6 * text.length());

    int x = ox;
    int y = oy;
    for (size_t index = 0; index < text.length(); index++) 
    {
        int character = (int)text[index];
        if (character == (int)(' ')) 
        {
            x += character_width;
            continue;
        }
        else if (character == (int)('\n')) 
        {
            x  = ox;
            y += line_feed_height;
            continue;
        }

        int character_index = character - first_valid_character;
        if (character_index < 0 || character_index >= last_valid_character) 
        {
            character_index = invalid_character;
        }

        float u = (character_index % 16) * uvst;
        float v = (character_index / 16) * uvst;
        float s = u + uvst;
        float t = v + uvst;

        sf::Vertex quad[6] = 
        {
            { { float(x                  ), float(y                  ) }, color, { u, v } },
            { { float(x + character_width), float(y                  ) }, color, { s, v } },
            { { float(x + character_width), float(y + character_width) }, color, { s, t } },
            { { float(x + character_width), float(y + character_width) }, color, { s, t } },
            { { float(x                  ), float(y + character_width) }, color, { u, t } },
            { { float(x                  ), float(y                  ) }, color, { u, v } },
        };

        for (auto &vert : quad) 
        {
            vertices.push_back(vert);
        }
       
        x += character_width;
   }

    context.window->draw(vertices.data(), vertices.size(), sf::Triangles, sf::RenderStates(context.font_texture));
}

void draw_text(int ox, int oy, Color color, const std::string& text)
{
    draw_text(ox, oy, color.r, color.g, color.b, color.a, text);
}

void display()
{
    if (!context.window)
    {
        return;
    }

    context.window->display();
}

extern int main(int, char **);
extern "C" int __stdcall WinMain(struct HINSTANCE__ *, struct HINSTANCE__ *, char *, int)
{
	return main(__argc, __argv);
}
