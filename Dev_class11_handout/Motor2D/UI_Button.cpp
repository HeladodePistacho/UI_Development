#include "j1App.h"
#include "j1Gui.h"
#include "j1Render.h"
#include "UI_Button.h"


UI_Button::UI_Button(UI_TYPE type, SDL_Rect detection_box, const UI_Image& start_image, bool act, SCROLL_TYPE drag) : UI_element(type, detection_box, act, drag), Button_image(start_image)
{
	Button_image.active = true;
}

UI_Button::UI_Button(const UI_Button* other) : UI_element(other->element_type, other->Interactive_box, other->active, other->draggable), Button_image(other->Button_image)
{
	Button_image.active = true;
}

void UI_Button::Change_image_to(const UI_Image& new_image)
{
	Button_image.active = false;
	Button_image = new_image;
	Button_image.active = true;
}

bool UI_Button::Update_Draw()
{

	if (active)
	{
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), (Interactive_box.x - App->render->camera.x), (Interactive_box.y - App->render->camera.y), &Button_image.Image);

		Child_Update_Draw();
	}
	return true;
}

bool UI_Button::Handle_input()
{
	int x, y;
	App->input->GetMousePosition(x, y);

	if (this->Mouse_is_in({ x, y }))
	{
		my_module->On_GUI_Callback(this, MOUSE_IN);
		state = OVER_ELEMENT;
	}
	else
	{
		my_module->On_GUI_Callback(this, MOUSE_OUT);
		state = NOTHING;
	}
	
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if(this->Mouse_is_in({ x, y }))
		{
			my_module->On_GUI_Callback(this, LEFT_MOUSE_DOWN);
			App->gui->element_selected = this;
			App->gui->focus_element = this;
			state = CLICK_ELEMENT;
		}
		else
		{
			App->gui->element_selected = nullptr;
			App->gui->focus_element = nullptr;
			state = NOTHING;
		}
	}
	
	if (App->gui->element_selected == nullptr) return true;

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		my_module->On_GUI_Callback(this, LEFT_MOUSE_REPEAT);
		state = CLICK_ELEMENT;
	}
	

	return true;
}

bool UI_Button::Update()
{
	Check_state();

	if (App->gui->element_selected == this && draggable)
		Drag_element();

	Child_Update();

	Handle_input();

	return true;
}