#include "j1App.h"
#include "j1Gui.h"
#include "j1Render.h"
#include "UI_Button.h"


UI_Button::UI_Button(UI_TYPE type, SDL_Rect detection_box, const UI_Image& start_image) : UI_element(type, detection_box), Button_image(start_image) {}

UI_Button::UI_Button(const UI_Button* other) : UI_element(other->element_type, other->Interactive_box), Button_image(other->Button_image)
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

	App->render->Blit((SDL_Texture*)App->gui->GetAtlas(),(Interactive_box.x - App->render->camera.x), (Interactive_box.y - App->render->camera.y), &Button_image.Image);
	
	Child_Update_Draw();

	return true;
}

bool UI_Button::Update()
{
	Check_state();

	if (state == CLICK_ELEMENT)
		Drag_element();

	return true;
}