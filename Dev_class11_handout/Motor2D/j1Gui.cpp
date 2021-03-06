#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "UI_Text_Box.h"
#include "UI_scroll.h"
#include "UI_Image.h"
#include "UI_Interactive_String.h"
#include "UI_String.h"
#include "UI_Button.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());
	Other_images.add(App->tex->Load("gui/login_background.png"));


	return true;

}

// Update all guis
bool j1Gui::PreUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN)
		Go_Next_Tab();

	int num_screens = Screen_elements.count();
	if (num_screens)
	{
		for(int i = 0; i < num_screens; i++)
			Screen_elements[i]->Update();
		
		
	}

	
	return true;
}

bool j1Gui::Update()
{
	
	

	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	
	int num_screens = Screen_elements.count();
	if (num_screens)
	{
		for (int i = 0; i < num_screens; i++)
			Screen_elements[i]->Update_Draw();
	}

	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	for (int i = 0; i < Screen_elements.count(); i++)
		Screen_elements.del(Screen_elements.At(i));
	
	Screen_elements.clear();

	return true;
}

UI_element * j1Gui::CreateScreen(UI_element * new_element)
{
	UI_element* ret = new UI_element(*new_element);

	if (ret)
		Screen_elements.add(ret);

	return ret;
}

UI_element* j1Gui::Add_element(UI_TYPE TYPE, j1Module* element_module)
{
	UI_element* ret = nullptr;

	switch (TYPE)
	{
	case UNDEFINED:
		ret = new UI_element(TYPE, element_module);
		break;
	case IMAGE:
		ret = new UI_Image(TYPE, element_module);
		break;
	case STRING:
		ret = new UI_String(TYPE, element_module);
		break;
	case BUTTON:
		ret = new UI_Button(TYPE, element_module);
		break;
	case TEXT_BOX:
		ret = new UI_Text_Box(TYPE, element_module);
		break;
	case SCROLL:
		ret = new UI_Scroll(TYPE, element_module);
		break;
	
	}

	return ret;
}

// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

const SDL_Texture* j1Gui::Get_Other_Textures(uint id) const
{
	if(id < Other_images.count())
		return Other_images[id];

	return nullptr;	
}

int j1Gui::AddTexture(SDL_Texture * new_text)
{
	if(new_text)
		Other_images.add(new_text);

	return Other_images.find(new_text);
}

int j1Gui::Get_tabs() const
{
	return num_of_tabs;
}

void j1Gui::Actualize_tabs()
{
	num_of_tabs++;
}

void j1Gui::Go_Next_Tab()
{
	if (focus_element != nullptr)
	{
		p2List_item<UI_element*>* screens = Screen_elements.start;
		while (screens)
		{
			Look_for(screens->data);
			screens = screens->next;
		}

	}

}

void j1Gui::Look_for(const UI_element* looked_element)
{
	int childs_num = looked_element->Childs.count();

	p2List_item<UI_element*>* childs_looker = looked_element->Childs.start;

	while (childs_looker)
	{
		if (focus_element->tab_order < num_of_tabs)
		{
			if (childs_looker->data->tab_order == focus_element->tab_order + 1)
			{
				element_selected = childs_looker->data;
				focus_element = childs_looker->data;
				childs_looker->data->state = INTERACTIVE_STATE::OVER_ELEMENT;
				break;
			}
		}
		else
		{
			if(childs_looker->data->tab_order == 1)
			{
				element_selected = childs_looker->data;
				focus_element = childs_looker->data;
				childs_looker->data->state = INTERACTIVE_STATE::OVER_ELEMENT;
				break;
			}
		}

		childs_looker = childs_looker->next;
	}

	if (childs_looker == nullptr)
	{
		for (int i = 0; i < childs_num; i++)
			Look_for(looked_element->Childs[i]);
	
	}


}

// class Gui ---------------------------------------------------


