#include "UI_Image.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"

UI_Image::UI_Image(iPoint pos, UI_TYPE type, SDL_Rect img_size) : UI_element(pos, type), Image(img_size) {}

bool UI_Image::Update_Draw()
{
	App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), position.x - App->render->camera.x, position.y - App->render->camera.y, &Image);
	return true;
}