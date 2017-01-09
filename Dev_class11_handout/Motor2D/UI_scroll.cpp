#include "UI_scroll.h"
#include "j1Gui.h"
#include "j1App.h"
#include "j1Render.h"

UI_Scroll::UI_Scroll(UI_TYPE type, SDL_Rect detection_box, const UI_Image* slider, const UI_Image* slide_box, bool act, SCROLL_TYPE drag) : UI_element(type, detection_box, act, drag), Slider((UI_Image*)slider), Slide_box((UI_Image*)slide_box)
{

	Interactive_box.x = slide_box->Interactive_box.x;
	Interactive_box.y = slide_box->Interactive_box.y;
}

UI_Scroll::UI_Scroll(const UI_Scroll* other) : UI_element(other->element_type, other->Interactive_box, other->active, other->draggable), Slider(other->Slider), Slide_box(other->Slide_box)
{
	Interactive_box.x = other->Slide_box->Interactive_box.x;
	Interactive_box.y = other->Slide_box->Interactive_box.y;
}

UI_Scroll::~UI_Scroll()
{
	int num = Camera_elements.count();
	for (int i = 0; i < num; i++)
		Camera_elements.del(Camera_elements.At(i));

}

bool UI_Scroll::Update()
{
	Handle_input();

	Pos.x = Interactive_box.x;
	Pos.y = Interactive_box.y;

	//Exercise 2 The scroll slider logic 
	//[====================================================
	if (App->gui->element_selected == this && draggable)
		Drag_element();

	Stop();
	//====================================================]

	//Exercise 3 The scroll Camera logic
	Move_elements();
	
	return true;
}

bool UI_Scroll::Update_Draw()
{
	if (active)
	{	
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), Stop_box.x - App->render->camera.x, Stop_box.y - App->render->camera.y, &Slide_box->Image);
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), Interactive_box.x - App->render->camera.x, Interactive_box.y - App->render->camera.y, &Slider->Image);
		

		Child_Update_Draw();
	}

	//Exercise 3 The scroll Camera view
	SDL_RenderSetViewport(App->render->renderer, &Camera);
	p2List_item<UI_element*>* scroll_items = Camera_elements.start;
	while (scroll_items != nullptr)
	{
		scroll_items->data->Update_Draw();
		scroll_items = scroll_items->next;
	}

	SDL_RenderSetViewport(App->render->renderer, nullptr);
	

	return true;
}

bool UI_Scroll::Handle_input()
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

void UI_Scroll::Set_Stop_Box(SDL_Rect new_box)
{
	Stop_box = new_box;

	if (Parent)
	{
		Interactive_box.x = Stop_box.x;
		Interactive_box.y = Stop_box.y;
	}
	
}

void UI_Scroll::Set_Camera(SDL_Rect new_camera)
{
	Camera = new_camera;
}

void UI_Scroll::Stop()
{
	if (App->gui->element_selected == this && Interactive_box.y < Stop_box.y)
		Interactive_box.y = Stop_box.y;
	
	if (App->gui->element_selected == this && (Interactive_box.y + Interactive_box.h) > (Stop_box.y + Stop_box.h))
		Interactive_box.y = (Stop_box.y + Stop_box.h) - Interactive_box.h;

	if (App->gui->element_selected == this && Interactive_box.x < Stop_box.x)
		Interactive_box.x = Stop_box.x;

	if(App->gui->element_selected == this && (Interactive_box.x + Interactive_box.w) > (Stop_box.x + Stop_box.w))
		Interactive_box.x = (Stop_box.x + Stop_box.w) - Interactive_box.w;


}

void UI_Scroll::Move_elements()
{
	Pos.x -= Interactive_box.x;
	Pos.y -= Interactive_box.y;

	if (Pos.x || Pos.y && (Move_y || Move_x))
	{
		int num = Camera_elements.count();
		for (int i = 0; i < num; i++)
		{
			Camera_elements[i]->Interactive_box.x += (Pos.x * Move_x);
			Camera_elements[i]->Interactive_box.y += (Pos.y * Move_y);
		}
	}
}

void UI_Scroll::Add_Camera_element(UI_element * new_item)
{
	if (new_item)
	{
		Camera_elements.add(new_item);

		switch (draggable)
		{
		case Y_SCROLL:
			if ((new_item->Interactive_box.y + new_item->Interactive_box.h) > Camera.h)
			{
				float length;
				if (Camera.h < Stop_box.h)
					length = (new_item->Interactive_box.y + new_item->Interactive_box.h + (Stop_box.h - Camera.h)) / (float)Stop_box.h;
				else  length = (new_item->Interactive_box.y + new_item->Interactive_box.h) / (float)Stop_box.h;

				if (length > Move_y)
					Move_y = floor(length);
			}
			break;

		case X_SCROLL:
			if ((new_item->Interactive_box.x + new_item->Interactive_box.w) > Camera.w)
			{
				float length;
				if (Camera.w < Stop_box.w)
					length = (new_item->Interactive_box.x + new_item->Interactive_box.w + (Stop_box.w - Camera.w)) / (float)Stop_box.w;
				else  length = (new_item->Interactive_box.x + new_item->Interactive_box.w) / (float)Stop_box.w;

				if (length > Move_x)
					Move_x = floor(length);
			}
			break;

		case FREE_SCROLL:
			if ((new_item->Interactive_box.y + new_item->Interactive_box.h) > Camera.h)
			{
				float length;
				if (Camera.h < Stop_box.h)
					length = (new_item->Interactive_box.y + new_item->Interactive_box.h + (Stop_box.h - Camera.h)) / (float)Stop_box.h;
				else  length = (new_item->Interactive_box.y + new_item->Interactive_box.h) / (float)Stop_box.h;

				if (length > Move_y)
					Move_y = floor(length);
			}
			if ((new_item->Interactive_box.x + new_item->Interactive_box.w) > Camera.w)
			{
				float length;
				if (Camera.w < Stop_box.w)
					length = (new_item->Interactive_box.x + new_item->Interactive_box.w + (Stop_box.w - Camera.w)) / (float)Stop_box.w;
				else  length = (new_item->Interactive_box.x + new_item->Interactive_box.w) / (float)Stop_box.w;

				if (length > Move_x)
					Move_x = floor(length);
			}
			break;
		}
	
		

		

	}

	

}

SDL_Rect UI_Scroll::Get_Stop_Box() const
{
	return Stop_box;
}

