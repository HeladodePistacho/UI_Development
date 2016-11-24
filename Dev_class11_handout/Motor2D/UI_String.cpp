#include "UI_String.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Fonts.h"

UI_String::UI_String(iPoint pos, UI_TYPE type, const char* new_text) : UI_element(pos, type), text(new_text) {}

const char* UI_String::Get_String() const
{
	return text;
}

bool UI_String::Update_Draw()
{
	App->render->Blit(App->font->Print(text), position.x - App->render->camera.x, position.y - App->render->camera.y);
	return true;
}