#include "UI_Image.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"

UI_Image::UI_Image(UI_TYPE type, SDL_Rect detection_box, SDL_Rect img_size,bool print, int new_id) : UI_element(type, detection_box), Image(img_size), printable(print), id(new_id) {}

UI_Image::UI_Image(const UI_Image* other) : UI_element(other->element_type, other->Interactive_box), Image(other->Image), printable(other->printable), id(other->id) {}

bool UI_Image::Update_Draw()
{
	if (printable)
	{
		if (element_type == IMAGE)
			App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), Interactive_box.x - App->render->camera.x, Interactive_box.y - App->render->camera.y, &Image);

		else App->render->Blit((SDL_Texture*)App->gui->Get_Other_Textures(id), Interactive_box.x - App->render->camera.x, Interactive_box.y - App->render->camera.y, &Image);
	}

	Child_Update_Draw();

	return true;
}

bool UI_Image::Update()
{
	Check_state();

	if (state == CLICK_ELEMENT)
		Drag_element();

	Child_Update();

	return true;
}