#include "UI_Button.h"

UI_Button::UI_Button(iPoint pos, UI_TYPE type, SDL_Rect set_box, const UI_Image& start_image) : UI_interactive(pos, type, set_box), Button_image(start_image) {}

UI_Button::UI_Button(const UI_Button* other) : UI_interactive(other->position, other->element_type, other->Interactive_box), Button_image(other->Button_image) {}

bool UI_Button::Update_Draw()
{
	Button_image.Update_Draw();
	return true;
}