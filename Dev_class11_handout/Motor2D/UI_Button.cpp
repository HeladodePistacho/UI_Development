#include "UI_Button.h"
#include "j1App.h"
#include "j1Gui.h"
#include "j1Render.h"

UI_Button::UI_Button(iPoint pos, UI_TYPE type, SDL_Rect set_box, const UI_Image& start_image) : UI_interactive(pos, type, set_box), Button_image(start_image) {}

UI_Button::UI_Button(const UI_Button* other) : UI_interactive(other->position, other->element_type, other->Interactive_box), Button_image(other->Button_image) 
{
	Button_image.printable = true;
}

void UI_Button::Change_image_to(const UI_Image& new_image)
{
	Button_image.printable = false;
	Button_image = new_image;
	Button_image.printable = true;
}

bool UI_Button::Update_Draw()
{
	App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), position.x - App->render->camera.x, position.y - App->render->camera.y, &Button_image.Image);
	return true;
}