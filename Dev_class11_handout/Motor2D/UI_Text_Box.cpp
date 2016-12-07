#include "UI_Text_Box.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Gui.h"

UI_Text_Box::UI_Text_Box(UI_TYPE type, SDL_Rect detection_box, const char* new_text, const UI_Image& start_image, bool act, bool drag) : UI_element(type, detection_box, act, drag),text(UI_TYPE::STRING, detection_box, new_text), background(start_image) {}

UI_Text_Box::UI_Text_Box(const UI_Text_Box* other) : UI_element(other->element_type, other->Interactive_box, other->active, other->draggable), text(other->text), background(other->background) {}

bool UI_Text_Box::Update()
{
	text_box_state();
	
	Child_Update();

	return true;
}

bool UI_Text_Box::Update_Draw()
{
	if (active)
	{
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), (Interactive_box.x - App->render->camera.x), (Interactive_box.y - App->render->camera.y), &background.Image);
		text.Update_Draw();
		Child_Update();
	}

	return true;
}

void UI_Text_Box::text_box_state()
{
	int x, y;
	App->input->GetMousePosition(x, y);

	
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if (Mouse_is_in({ x, y }))
		{
			App->gui->element_selected = this;
			state = CLICK_ELEMENT;
		}
		else
		{
			App->gui->element_selected = nullptr;
			state = NOTHING;
		}
		
	}
}