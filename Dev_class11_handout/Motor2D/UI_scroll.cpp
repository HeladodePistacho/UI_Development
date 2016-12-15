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

bool UI_Scroll::Update()
{
	Check_state();

	Pos.x = Interactive_box.x;
	Pos.y = Interactive_box.y;

	if (App->gui->element_selected == this && draggable)
		Drag_element();

	Stop();
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

void UI_Scroll::Set_Stop_Box(SDL_Rect new_box)
{
	Stop_box = new_box;
	Interactive_box.x = Stop_box.x;
	Interactive_box.y = Stop_box.y;
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

}

void UI_Scroll::Move_elements()
{
	Pos.x -= Interactive_box.x;
	Pos.y -= Interactive_box.y;

	if (Pos.x || Pos.y)
	{
		int num = Camera_elements.count();
		for (int i = 0; i < num; i++)
		{
			Camera_elements[i]->Interactive_box.x += Pos.x;
			Camera_elements[i]->Interactive_box.y += Pos.y;
		}
	}
}

void UI_Scroll::Add_Camera_element(UI_element * new_item)
{
	Camera_elements.add(new_item);
}

