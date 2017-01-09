#include "j1Textures.h"
#include "UI_Text_Box.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Gui.h"

UI_Text_Box::UI_Text_Box(UI_TYPE type, SDL_Rect detection_box, char* new_text, const UI_Image* start_image, bool act, SCROLL_TYPE drag) : UI_element(type, detection_box, act, drag),text(UI_TYPE::STRING, detection_box, new_text), background(start_image) {}

UI_Text_Box::UI_Text_Box(const UI_Text_Box* other) : UI_element(other->element_type, other->Interactive_box, other->active, other->draggable), text(other->text), background(other->background) {}

bool UI_Text_Box::Update()
{
	
	Handle_input();

	Text_management();

	Child_Update();

	return true;
}

bool UI_Text_Box::Update_Draw()
{
	if (active)
	{
		//App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), (Interactive_box.x - App->render->camera.x), (Interactive_box.y - App->render->camera.y), &background->Image);
		App->render->Blit(text.text_texture, (Interactive_box.x - App->render->camera.x), (Interactive_box.y - App->render->camera.y));
		Child_Update();

		if (SDL_IsTextInputActive())
			App->render->DrawQuad({ cursor_pos, Interactive_box.y, 1, height }, 255, 255, 255);
		
	}

	return true;
}

const char* UI_Text_Box::get_string_pos(int cursor)
{
	return text.text.Get_Char(cursor, cursor);
}

void UI_Text_Box::Insert_Char(int position, const char * new_char)
{
	text.text.Insert_Char(position, new_char);
	App->tex->UnLoad(text.text_texture);
	text.text_texture = App->font->Print(text.text.GetString());
}

void UI_Text_Box::Delete_Char(int position)
{
	text.text.Erase_Char(position);
	App->tex->UnLoad(text.text_texture);
	text.text_texture = App->font->Print(text.text.GetString());
}

bool UI_Text_Box::Handle_input()
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
		if (this->Mouse_is_in({ x, y }))
		{
			my_module->On_GUI_Callback(this, LEFT_MOUSE_DOWN);
			App->gui->element_selected = this;
			App->gui->focus_element = this;

			cursor_virtual_pos = text.text.Length() - 1;
			int width;
			App->font->CalcSize(text.text.GetString(), width, height);
			cursor_pos = width + Interactive_box.x;
			SDL_StartTextInput();

			state = CLICK_ELEMENT;
		}
		else
		{
			App->gui->element_selected = nullptr;
			App->gui->focus_element = nullptr;
			SDL_StopTextInput();
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

void UI_Text_Box::Text_management()
{
	if (SDL_IsTextInputActive())
	{
		if (App->gui->element_selected == this)
		{

			if (App->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN)
			{
				int width;
				App->font->CalcSize(get_string_pos(cursor_virtual_pos), width, height);

				Delete_Char(cursor_virtual_pos);

				if (cursor_virtual_pos >= 0)
				{
					cursor_pos -= width;
					cursor_virtual_pos--;
				}
			}

			if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
			{
				int width;
				App->font->CalcSize(get_string_pos(cursor_virtual_pos), width, height);
				if (cursor_virtual_pos >= 0)
				{
					cursor_pos -= width;
					cursor_virtual_pos--;
				}
			}

			if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
			{
				int width;
				App->font->CalcSize(get_string_pos(cursor_virtual_pos + 1), width, height);
				if (cursor_virtual_pos < (int)(text.text.Length() - 1))
				{
					cursor_pos += width;
					cursor_virtual_pos++;
				}
			}

		}
	}
}

void UI_Text_Box::text_box_state()
{
	int x, y;
	App->input->GetMousePosition(x, y);

	if(App->gui->focus_element != this || App->gui->element_selected == nullptr)
	{ 
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		{
			if (Mouse_is_in({ x, y }))
			{
				App->gui->element_selected = this;
				cursor_virtual_pos = text.text.Length() - 1;
				int width;
				App->font->CalcSize(text.text.GetString(), width, height);
				cursor_pos = width + Interactive_box.x;
				SDL_StartTextInput();
				state = CLICK_ELEMENT;
			}
			else
			{
				App->gui->element_selected = nullptr;
				SDL_StopTextInput();
				state = NOTHING;
			}
		}
	}	
	else
	{
		if (state == OVER_ELEMENT)
		{
			cursor_virtual_pos = text.text.Length() - 1;
			int width;
			App->font->CalcSize(text.text.GetString(), width, height);
			cursor_pos = width + Interactive_box.x;
			SDL_StartTextInput();
			state = CLICK_ELEMENT;
		}

		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		{
			if (!Mouse_is_in({ x, y }))
			{
				App->gui->element_selected = nullptr;
				SDL_StopTextInput();
				state = NOTHING;
			}
		}
	}
}