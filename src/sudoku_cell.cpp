#include "sudoku_cell.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/label.hpp>
#include <sudoku_field.h>
#include <godot_cpp/classes/input.hpp>
using namespace godot;
bool changable = true;
int position;
int sector;
bool chosen = false;
void SudokuCell::_ready()
{
	set_label();
	define_sector();
}
void SudokuCell::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("on_button_pressed"), &SudokuCell::on_button_pressed);
}

SudokuCell::SudokuCell() 
{
    connect("pressed", Callable(this, "on_button_pressed"));
}

SudokuCell::~SudokuCell() 
{

}

void SudokuCell::on_button_pressed() 
{
	Array children = Object::cast_to<HFlowContainer>(get_parent())->get_children();
	for (int i = 0; i < children.size(); i++)
	{
		if (Object::cast_to<SudokuCell>(children[i]) != this)
		{
			Object::cast_to<SudokuCell>(children[i])->chosen = false;
		}
		else
		{
			chosen = true;
		}
	}
}

void SudokuCell::_process(double delta) 
{

}

void SudokuCell::set_label()
{
	Label *label = memnew(Label);
	add_child(label);
	label->set_scale(Vector2(0.3,0.3));
    label->set_size(Vector2(27,27));
	label->set_horizontal_alignment(HorizontalAlignment::HORIZONTAL_ALIGNMENT_CENTER);
	label->set_vertical_alignment(VerticalAlignment::VERTICAL_ALIGNMENT_CENTER);
}

void SudokuCell::define_sector()
{
	Array children = get_parent()->get_children();
	for (int i = 0; i < children.size(); i++)
	{
		Node *child_node = Object::cast_to<Node>(children[i]);
		if (child_node == this) 
		{
			position = i;
			break;
		}
	}
	// <3 , <6, >2, >5
	if ((position / 9 < 3) && (position % 9 < 3))
	{
		sector = 1;
	}
	else if ((position / 9 < 3) && (position % 9 < 6) && (position % 9 > 2))
	{
		sector = 2;
	}
	else if ((position / 9 < 3) && (position % 9 > 5))
	{
		sector = 3;
	}
	else if ((position / 9 > 2) && (position / 9 < 6) && (position % 9 < 3) )
	{
		sector = 4;
	}
	else if ((position / 9 > 2) && (position / 9 < 6) && (position % 9 > 2) && (position % 9 < 6))
	{
		sector = 5;
	}
	else if ((position / 9 > 2) && (position / 9 < 6) && (position % 9 > 5))
	{
		sector = 6;
	}
	else if ((position / 9 > 5) && (position % 9 < 3))
	{
		sector = 7;
	}
	else if ((position / 9 > 5) && (position % 9 > 2) && (position % 9 < 6))
	{
		sector = 8;
	}
	else if ((position / 9 > 5) && (position % 9 > 5))
	{
		sector = 9;
	}
}

void SudokuCell::check_cell()
{	
	bool error = false;
	Array children = get_parent()->get_children();
	for (int i = 0; i < children.size(); i++)
	{
		
		SudokuCell *cell = Object::cast_to<SudokuCell>(children[i]);
		if ((Object::cast_to<Label>(cell->get_child(0))->get_text() == Object::cast_to<Label>(get_child(0))->get_text()) && (Object::cast_to<Label>(get_child(0))->get_text()!="") && !(cell == this))
		{
			if (cell->sector == sector)
			{
				error = true;
			}
			else if (cell->position/9 == position/9)
			{
				error = true;
			}
			else if (cell->position%9 == position%9)
			{
				error = true;;
			}
			
		}
		
	}
	if (error && changable)
	{
		set_self_modulate(Color(1,0,0,1));
	}
	else if (changable)
	{
		set_self_modulate(Color(1,1,1,1));
	}
	else
	{
		set_self_modulate(Color(0.0,0.0,1.0,1.0));
	}
}
