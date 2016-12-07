#include "UI_element.h"
#include "UI_String.h"
#include "UI_Text_Box.h"
#include "UI_Button.h"
#include "j1Gui.h"
#include "j1App.h"

UI_element::UI_element(UI_TYPE type, SDL_Rect detection_box, bool act, bool drag) : element_type(type), Interactive_box(detection_box), active(act), draggable(drag)
{

}

UI_element::UI_element(const UI_element* other) : element_type(other->element_type), Interactive_box(other->Interactive_box), active(other->active), draggable(other->draggable){}

UI_element* UI_element::AddChild(const UI_element* new_child)
{
	UI_element* ret = nullptr;

	switch (new_child->element_type)
	{
	case UI_TYPE::IMAGE:					ret = new UI_Image((UI_Image*)new_child); break;
	case UI_TYPE::IMAGE_NOT_IN_ATLAS:		ret = new UI_Image((UI_Image*)new_child); break;
	case UI_TYPE::STRING:					ret = new UI_String((UI_String*)new_child); break;
	case UI_TYPE::BUTTON:					ret = new UI_Button((UI_Button*)new_child); break;
	case UI_TYPE::TEXT_BOX:					ret = new UI_Text_Box((UI_Text_Box*)new_child); break;
	}

	ret->Set_Parent(this);

	if (ret != nullptr)
		Childs.add(ret);

	return ret;
}

const UI_element* UI_element::Set_Parent(const UI_element* new_Parent)
{
	Parent = new_Parent;
	Interactive_box.x += Parent->Interactive_box.x;
	Interactive_box.y += Parent->Interactive_box.y;
	layer += Parent->layer;

	return Parent;
}

bool UI_element::Update()
{
	int number_of_childs = Childs.count();

	for (int i = 0; i < number_of_childs; i++)
		Childs[i]->Update();

	return true;
}

bool UI_element::Update_Draw()
{
	int number_of_childs = Childs.count();

	for (int i = 0; i < number_of_childs; i++)
		Childs[i]->Update_Draw();

	return true;
}

bool UI_element::Mouse_is_in(const iPoint& mouse_pos)
{
	return ((mouse_pos.x > Interactive_box.x) && (mouse_pos.x <= (Interactive_box.x + Interactive_box.w)) && (mouse_pos.y > Interactive_box.y) && (mouse_pos.y <= (Interactive_box.y + Interactive_box.h)));
}

void UI_element::Child_Update_Draw()
{
	int childs_number = Childs.count();
	for (int i = 0; i < childs_number; i++)
		Childs[i]->Update_Draw();
}

void UI_element::Child_Update()
{
	int childs_number = Childs.count();
	for (int i = 0; i < childs_number; i++)
		Childs[i]->Update();
}

void UI_element::Check_state()
{
	int x, y;
	App->input->GetMousePosition(x, y);

	if (App->gui->element_selected == nullptr)
	{
		if (Mouse_is_in({ x, y }))
		{
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN || App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
			{
				if(get_higher_child() != nullptr)
					state = OVER_ELEMENT;

				else
				{
					App->gui->element_selected = this;
					state = CLICK_ELEMENT;
				}

			}
			else state = OVER_ELEMENT;
		}
		else state = NOTHING;
	}
	else 
	{
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
			App->gui->element_selected = nullptr;
	}
	

}

void UI_element::Drag_element()
{

	int x = 0, y = 0;
	App->input->GetMouseMotion(x, y);

	Interactive_box.x += x;
	Interactive_box.y += y;

	int childs_number = Childs.count();

	for (int i = 0; i < childs_number; i++)
		Childs[i]->Drag_element();
}


UI_element* UI_element::get_higher_child()
{
	UI_element* temp = nullptr;
	int childs_number = Childs.count();

	if (childs_number)
	{

		for (int i = 0; i < childs_number; i++)
		{
			if (Childs[i]->state == OVER_ELEMENT && Childs[i]->layer >= this->layer)
			{
				temp = Childs[i];
				App->gui->element_selected = temp;
			}
		}

		
	}

	return temp;
}