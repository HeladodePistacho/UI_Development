#include "UI_Text_Box.h"

UI_Text_Box::UI_Text_Box(UI_TYPE type, SDL_Rect detection_box, const char* new_text, const UI_Image& start_image, bool act, bool drag) : UI_element(type, detection_box, act, drag),text(UI_TYPE::STRING, detection_box, new_text), background(start_image) {}

UI_Text_Box::UI_Text_Box(const UI_Text_Box* other) : UI_element(other->element_type, other->Interactive_box, other->active, other->draggable), text(other->text), background(other->background) {}

bool UI_Text_Box::Update()
{
	return true;
}

bool UI_Text_Box::Update_Draw()
{
	return true;
}
