#include "UI_element.h"
#include "UI_String.h"
#include "UI_Button.h"
#include "UI_Interactive_String.h"

UI_element::UI_element(UI_TYPE type, SDL_Rect detection_box) : element_type(type), Interactive_box(detection_box) {}

UI_element::UI_element(const UI_element* other) : element_type(other->element_type), Interactive_box(other->Interactive_box){}


UI_element* UI_element::AddChild(const UI_element* new_child)
{
	UI_element* ret = nullptr;


	switch (new_child->element_type)
	{
	case UI_TYPE::IMAGE:					ret = new UI_Image((UI_Image*)new_child); break;
	case UI_TYPE::IMAGE_NOT_IN_ATLAS:		ret = new UI_Image((UI_Image*)new_child); break;
	case UI_TYPE::STRING:					ret = new UI_String((UI_String*)new_child); break;
	case UI_TYPE::BUTTON:					ret = new UI_Button((UI_Button*)new_child); break;
	case UI_TYPE::INTERACTIVE_STRING:		ret = new UI_Interactive_String((UI_Interactive_String*)new_child); break;
	}

	ret->Set_Parent(*this);
	if (ret != nullptr)
		Childs.add(ret);

	return ret;
}

UI_element* UI_element::Set_Parent(const UI_element& new_Parent)
{
	return Parent = ((UI_element*)&new_Parent);
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