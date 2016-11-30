#include "j1App.h"
#include "j1Gui.h"
#include "j1Render.h"
#include "UI_Button.h"


UI_Button::UI_Button(iPoint pos, UI_TYPE type, SDL_Rect set_box, const UI_Image& start_image) : UI_element(pos, type, set_box), Button_image(start_image) {}

UI_Button::UI_Button(const UI_Button* other) : UI_element(other->position, other->element_type, other->Interactive_box), Button_image(other->Button_image)
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

bool UI_Button::Update()
{
	int x, y;
	App->input->GetMousePosition(x, y);

	if (Mouse_is_in({ x, y }))
	{
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN || App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
			state = CLICK_ELEMENT;
		else state = OVER_ELEMENT;
	}
	else state = NOTHING;

	return true;
}