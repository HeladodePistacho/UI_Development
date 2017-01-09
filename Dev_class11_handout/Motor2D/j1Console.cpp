#include "j1Console.h"
#include "j1App.h"
#include "j1Gui.h"
#include "j1Fonts.h"
#include "UI_Image.h"
#include "p2Log.h"
#include "j1Render.h"


j1Console::j1Console()
{
	name.create("console");
}

bool j1Console::Awake(pugi::xml_node& config)
{
	LOG("Setting Console features");
	
	console_screen.x = config.child("Position").attribute("x").as_int();
	console_screen.y = config.child("Position").attribute("y").as_int();
	console_screen.w = config.child("Size").attribute("width").as_int();
	console_screen.h = config.child("Size").attribute("height").as_int();

	Background.r = config.child("Color").attribute("r").as_int();
	Background.g = config.child("Color").attribute("g").as_int();
	Background.b = config.child("Color").attribute("b").as_int();
	Background.a = config.child("Color").attribute("a").as_int();

	LOG("Setting console text box");

	int width;
	App->font->CalcSize("Set", width, height, Console_font);

	Input_text = new UI_Text_Box(UI_TYPE::TEXT_BOX, { console_screen.x, (console_screen.y + console_screen.h), console_screen.w, height }, "", nullptr);
	Input_text->setmodule(this);

	LOG("Desactivating console");
	active = false;

	return true;
}

bool j1Console::Start()
{
	Load_labels();
	
	return true;
}

bool j1Console::Update(float dt)
{
	Load_Update_labels();
	Input_text->Update();
	Input_text->Handle_input();

	check_state();

	if (state == MOUSE_OVER)
		drag_console();

	return true;
}

bool j1Console::PostUpdate()
{
	App->render->DrawQuad(console_screen, Background.r, Background.g, Background.b, Background.a);
	App->render->DrawQuad(Input_text->Interactive_box, 0, 0, 255, Background.a);

	//Change viewport
	SDL_RenderSetViewport(App->render->renderer, &console_screen);

	int salto_de_linea = 0;
	for (int i = 0; i < num_of_labels; i++)
	{
		Labels[i]->Draw_console(salto_de_linea);
		salto_de_linea += height;
	}
	SDL_RenderSetViewport(App->render->renderer, nullptr);




	Input_text->Update_Draw();
	return true;
}

bool j1Console::CleanUp()
{
	delete Input_text;
	return true;
}

void j1Console::Active_console()
{
	if (App->console->active)
	{
		App->console->active = false;
		SDL_StopTextInput();
	}
	else
	{
		App->console->active = true;
		App->gui->element_selected = Input_text;
		SDL_StartTextInput();
	}
}

void j1Console::Add_Label(const char * new_text)
{
	UI_String* new_label = new UI_String(UI_TYPE::STRING, { 0,0,0,0 }, (char*)new_text);
	
	if (new_label)
		Labels.PushBack(new_label);

	num_of_labels++;
}



void j1Console::check_state()
{
	int x, y;
	App->input->GetMousePosition(x, y);

	if (((x > console_screen.x) && (x <= (console_screen.x + console_screen.w)) && (y > console_screen.y) && (y <= (console_screen.y + console_screen.h))))
		state = MOUSE_OVER;
	else state = MOUSE_NOT_OVER;
	
}

void j1Console::drag_console()
{
	int y;
	App->input->GetMouseWheel(y);

	for(int i = 0; i < num_of_labels; i++)
		Labels[i]->Interactive_box.y += y;

}

void j1Console::Load_labels()
{
	
	for (int i = labels_loaded; i < num_of_labels; i++)
	{
		Labels[i]->Load_text_texture();
		labels_loaded++;
	}
	
}

void j1Console::Load_Update_labels()
{
	if (num_of_labels != labels_loaded)
		Load_labels();
}

