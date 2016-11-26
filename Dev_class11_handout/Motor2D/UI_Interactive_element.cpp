#include "UI_interactive_element.h"


UI_interactive::UI_interactive(iPoint pos, UI_TYPE type, SDL_Rect set_box) : UI_element(pos, type), Interactive_box(set_box) {}

bool UI_interactive::Mouse_is_in(const iPoint& mouse_pos)
{
	return ((mouse_pos.x > Interactive_box.x) && (mouse_pos.x <= (Interactive_box.x + Interactive_box.w)) && (mouse_pos.y > Interactive_box.y) && (mouse_pos.y <= (Interactive_box.y + Interactive_box.h)));
}