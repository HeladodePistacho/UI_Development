#include "UI_scroll.h"
#include "j1Gui.h"
#include "j1App.h"
#include "j1Render.h"

UI_Scroll::UI_Scroll(UI_TYPE type, SDL_Rect detection_box, const UI_Image* slider, const UI_Image* slide_box, bool act, SCROLL_TYPE drag) : UI_element(type, detection_box, act, drag), Slider((UI_Image*)slider), Slide_box((UI_Image*)slide_box)
{
	Slider->active = true;
	Slider->Interactive_box.x = detection_box.x;
	Slider->Interactive_box.y = detection_box.y;

}

UI_Scroll::UI_Scroll(const UI_Scroll* other) : UI_element(other->element_type, other->Interactive_box, other->active, other->draggable), Slider(other->Slider), Slide_box(other->Slide_box)
{
	Slider->active = true;
	Slider->Interactive_box.x = other->Interactive_box.x;
	Slider->Interactive_box.y = other->Interactive_box.y;
	
}

bool UI_Scroll::Update()
{
	Check_state();

	if (App->gui->element_selected == this && draggable)
		Drag_element();

	Slide();

	return true;
}

bool UI_Scroll::Update_Draw()
{
	if (active)
	{	
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), Interactive_box.x - App->render->camera.x, Interactive_box.y - App->render->camera.y, &Slide_box->Image);
		Slider->Update_Draw();

		Child_Update_Draw();
	}

	return true;
}

void UI_Scroll::Slide()
{
	if (App->gui->element_selected == Slider && Slider->Interactive_box.y < Interactive_box.y)
		Slider->Interactive_box.y = Interactive_box.y;
	

	if (App->gui->element_selected == Slider && (Slider->Interactive_box.y + Slider->Interactive_box.h) > (Interactive_box.y + Interactive_box.h))
		Slider->Interactive_box.y = (Interactive_box.y + Interactive_box.h) - Slider->Interactive_box.h;
	

}