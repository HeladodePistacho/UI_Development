#include "UI_Image.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"

UI_Image::UI_Image(iPoint pos, UI_TYPE type, SDL_Rect img_size,bool print, int new_id) : UI_element(pos, type), Image(img_size), printable(print), id(new_id) {}

UI_Image::UI_Image(const UI_Image* other) : UI_element(other->position, other->element_type), Image(other->Image), printable(other->printable), id(other->id) {}

bool UI_Image::Update_Draw()
{
	if (printable)
	{
		if (element_type == IMAGE)
			App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), position.x - App->render->camera.x, position.y - App->render->camera.y, &Image);

		else App->render->Blit((SDL_Texture*)App->gui->Get_Other_Textures(id), position.x - App->render->camera.x, position.y - App->render->camera.y, &Image);
	}
	return true;
}