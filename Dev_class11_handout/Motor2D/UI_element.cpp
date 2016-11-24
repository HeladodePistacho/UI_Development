#include "UI_element.h"

UI_element::UI_element(iPoint pos, UI_TYPE type) : position(pos), element_type(type) {}

void UI_element::Set_Position(const iPoint& new_pos)
{
	position = new_pos;
}