#define _CRT_SECURE_NO_WARNINGS
#include "j1Console.h"
#include "j1App.h"
#include "j1Gui.h"
#include "j1Fonts.h"
#include "UI_Image.h"
#include "p2Log.h"
#include "j1Render.h"

//--------------CONSOLE-------------------
//----------------------------------------

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
	App->font->CalcSize("Set", width, height, App->font->default);

	Input_text = new UI_Text_Box(UI_TYPE::TEXT_BOX, { console_screen.x, (console_screen.y + console_screen.h), console_screen.w, height }, "", nullptr);
	Input_text->setmodule(this);

	LOG("Desactivating console");
	active = false;

	return true;
}

bool j1Console::Start()
{
	
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

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		Camera_management();
		Text_management();
	}

	return true;
}

bool j1Console::PostUpdate()
{
	App->render->DrawQuad(console_screen, Background.r, Background.g, Background.b, Background.a);
	App->render->DrawQuad(Input_text->Interactive_box, 0, 0, 255, Background.a);

	//Change viewport
	SDL_RenderSetViewport(App->render->renderer, &console_screen);

	for (int i = 0; i < num_of_labels; i++)
		App->render->Blit(Labels[i]->text_texture, Labels[i]->Interactive_box.x - App->render->camera.x, (Labels[i]->Interactive_box.y));
				
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

command* j1Console::Add_Command(const char * comm, j1Module * callback, uint min_arg, uint max_args)
{
	command* new_command = new command(comm, callback, min_arg, max_args);

	if (new_command)
		Commands_List.PushBack(new_command);

	return new_command;
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
	
	for (; labels_loaded < num_of_labels; labels_loaded++)
	{
		Labels[labels_loaded]->Load_text_texture();

		if(labels_loaded > 0)
			Labels[labels_loaded]->Interactive_box.y = Labels[labels_loaded - 1]->Interactive_box.y + height;
	}
	
	
}

void j1Console::Load_Update_labels()
{
	if (num_of_labels != labels_loaded)
		Load_labels();
}

void j1Console::Camera_management()
{
	int last_label = (Labels[num_of_labels - 1]->Interactive_box.y);

	if (last_label > console_screen.h)
	{
		for (int i = 0; i < num_of_labels; i++)
			Labels[i]->Interactive_box.y += console_screen.y - last_label;
	}
}

void j1Console::Text_management()
{
	int len = strlen(Input_text->text.text.GetString());
	char* temp = new char(len);

	//Check if there are spaces before text
	int  bookmark = 0;
	for (; bookmark < len; bookmark++)
	{
		if (*(Input_text->text.text.GetString() + bookmark) != ' ')
			break;

		else continue;
	}

	//Check if is a command
	if (*(Input_text->text.text.GetString() + bookmark) == '/')
	{
		for (int i = 0; bookmark < len; bookmark++)
		{
			if (*(Input_text->text.text.GetString() + bookmark + 1) != ' ')
			{
				*(temp + i) = *(Input_text->text.text.GetString() + bookmark + 1);
				i++;
			}
			else break;
		}

		if (command* temp_com = Command_management(temp))
		{
			int argument_start = bookmark + 1;

			for (int i = strlen(temp); i < len; i++)
				*(temp + i) = *(Input_text->text.text.GetString() + ++bookmark);
			
			Argument_management(temp, argument_start, temp_com);
			
		}
		else return;
	}
		

	delete[] temp;
}

void j1Console::Argument_management(const char* Input_text, int bookmark, command* this_command)
{
	int* args = new int(this_command->max_arguments);
	int args_count = 0;

	for (args_count; bookmark < strlen(Input_text); bookmark++)
	{
		if (*(Input_text + bookmark) == ' ')
			continue;
		else
		{
			if (args_count <= this_command->max_arguments)
			{
				*(args + args_count) = atoi((Input_text + bookmark));
				args_count++;
			}
			else
			{
				LOG("ERROR: Too much arguments");
				return;
			}
		}
	}

	if (args_count < this_command->min_arguments)
		LOG("ERROR: More arguments needed");
	else
	{
		this_command->my_module->On_Console_Callback(this_command, args);
	}

	delete[] args;
}

command* j1Console::Command_management(const char* Input_command)
{
	
	int num_of_commands = Commands_List.Count();
	for (int i = 0; i < num_of_commands; i++)
	{
		if (strcmp(Input_command, Commands_List[i]->name) != 0)
			continue;
		else return Commands_List[i];
			
	}
	
	LOG("ERROR: command does not exist");
	return nullptr;
}

//---------------COMAND-------------------
//----------------------------------------

command::command(const char* new_com, j1Module* callback, unsigned int min_args, unsigned int max_args) : name(new_com), my_module(callback), min_arguments(min_args), max_arguments(max_args) {}
