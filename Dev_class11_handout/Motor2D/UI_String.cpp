#define _CRT_SECURE_NO_WARNINGS
#include "UI_String.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Fonts.h"

UI_String::UI_String(UI_TYPE type, SDL_Rect detection_box, char* new_text, bool act, bool drag) : UI_element(type, detection_box, act, drag), text(new_text) {}

UI_String::UI_String(const UI_String* other) : UI_element(other->element_type, other->Interactive_box, other->active, other->draggable), text(other->text) {}


bool UI_String::Update_Draw()
{
	if (active)
	{
		App->render->Blit(App->font->Print(text.GetString()), Interactive_box.x - App->render->camera.x, Interactive_box.y - App->render->camera.y);
	}
	Child_Update_Draw();

	return true;
}

bool UI_String::Update()
{
	Check_state();

	return true;
}

bool UI_String::Set_String(char* new_text)
{
	text = new_text;
	return (text != nullptr) ? true : false;
}

