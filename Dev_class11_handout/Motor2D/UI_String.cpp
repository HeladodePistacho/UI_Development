#include "UI_String.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Fonts.h"

UI_String::UI_String(UI_TYPE type, SDL_Rect detection_box, const char* new_text) : UI_element(type, detection_box), text(new_text) {}

UI_String::UI_String(const UI_String* other) : UI_element(other->element_type, other->Interactive_box), text(other->text) {}

const char* UI_String::Get_String() const
{
	return text;
}

bool UI_String::Update_Draw()
{
	 App->render->Blit(App->font->Print(text), Interactive_box.x - App->render->camera.x, Interactive_box.y - App->render->camera.y);
	
	Child_Update_Draw();

	return true;
}

bool UI_String::Update()
{
	Check_state();

	return true;
}

bool UI_String::Set_String(const char* new_text)
{
	text = new_text;
	return (text != nullptr) ? true : false;
}