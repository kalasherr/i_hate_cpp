#include "sudoku_field.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/input.hpp>
#include <sudoku_cell.h>
#include <algorithm> 
#include <random>
#include <chrono>
using namespace godot;
int SudokuField::x1 = 1;
int SudokuField::x2 = 2;
int SudokuField::x3 = 3;
int SudokuField::x4 = 4;
int SudokuField::x5 = 5;
int SudokuField::x6 = 6;
int SudokuField::x7 = 7;
int SudokuField::x8 = 8;
int SudokuField::x9 = 9;
int SudokuField::counter = -1;
int SudokuField::field[9][9] ={
        {x1,x4,x3,x2,x8,x5,x9,x6,x7},
        {x8,x5,x2,x6,x9,x7,x4,x3,x1},
        {x6,x9,x7,x3,x4,x1,x2,x8,x5},
        {x2,x3,x6,x7,x1,x4,x8,x5,x9},
        {x4,x8,x1,x9,x5,x6,x3,x7,x2},
        {x9,x7,x5,x8,x2,x3,x6,x1,x4},
        {x7,x2,x9,x1,x3,x8,x5,x4,x6},
        {x5,x6,x8,x4,x7,x2,x1,x9,x3},
        {x3,x1,x4,x5,x6,x9,x7,x2,x8}
    };

void SudokuField::_ready()
{
    HFlowContainer *cell_containter = memnew(HFlowContainer);
    cell_containter->set_size(Vector2(104,104));
    cell_containter->set_custom_minimum_size(Vector2(104,104));
	add_child(cell_containter);

	
    shuffle_sudoku(field);
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            SudokuCell *cell = memnew(SudokuCell);
            get_child(0)->add_child(cell);
            double changable = UtilityFunctions::randf_range(0.0,1.0);
            if (changable > 0.5)
            {
                cell->changable = false;
                Label *label_child = Object::cast_to<Label>(cell->get_child(0));
                if (label_child != nullptr) 
                {
                label_child->set_text(UtilityFunctions::str(field[i][j]));
                } 
            }
            
        }
    }
}

int SudokuField::return_next_cell()
{
    counter++;
    return field[counter/9][counter%9];
}
void SudokuField::_bind_methods() 
{

}

SudokuField::SudokuField() 
{
   
}

SudokuField::~SudokuField() 
{
    
}


void SudokuField::_process(double delta) 
{
    // bool checked;
    // for (int i = 0; i < get_children().size(); i++)
    // {
    //     if (Object::cast_to<Label>(Object::cast_to<SudokuCell>(get_children()[i]) ->get_child(0))->get_text() == "")
    //     {
    //         checked = false;
    //     }
    //     else
    //     {
    //         continue;
    //     }
    // }
    // if (checked == false)
    // {
        
    // }
    // else
    // {
    //     if (SceneTree *tree = get_tree()) 
    //     {
    //         tree->quit();
    //     }
    // }
    SudokuCell *chosen_cell;
    for (int i = 0; i < Object::cast_to<HFlowContainer>(get_child(0))->get_children().size(); i++)
    {
        if (Object::cast_to<SudokuCell>(Object::cast_to<HFlowContainer>(get_child(0))->get_child(i))->chosen == true)
        {
            chosen_cell = Object::cast_to<SudokuCell>(Object::cast_to<HFlowContainer>(get_child(0))->get_child(i));
        }
    }
    if (true)
    {
        if (Input::get_singleton()->is_action_just_pressed("0"))
		{
			Label *label = Object::cast_to<Label>(chosen_cell->get_child(0));
			label->set_text("");
		}
        if (Input::get_singleton()->is_action_just_pressed("1"))
		{
			Label *label = Object::cast_to<Label>(chosen_cell->get_child(0));
			label->set_text("1");
		}
        if (Input::get_singleton()->is_action_just_pressed("2"))
		{
			Label *label = Object::cast_to<Label>(chosen_cell->get_child(0));
			label->set_text("2");
		}
        if (Input::get_singleton()->is_action_just_pressed("3"))
		{
			Label *label = Object::cast_to<Label>(chosen_cell->get_child(0));
			label->set_text("3");
		}
        if (Input::get_singleton()->is_action_just_pressed("4"))
		{
			Label *label = Object::cast_to<Label>(chosen_cell->get_child(0));
			label->set_text("4");
		}
	    if (Input::get_singleton()->is_action_just_pressed("5"))
		{
			Label *label = Object::cast_to<Label>(chosen_cell->get_child(0));
			label->set_text("5");
		}
	    if (Input::get_singleton()->is_action_just_pressed("6"))
		{
			Label *label = Object::cast_to<Label>(chosen_cell->get_child(0));
			label->set_text("6");
		}
	    if (Input::get_singleton()->is_action_just_pressed("7"))
		{
			Label *label = Object::cast_to<Label>(chosen_cell->get_child(0));
			label->set_text("7");
		}
	    if (Input::get_singleton()->is_action_just_pressed("8"))
		{
			Label *label = Object::cast_to<Label>(chosen_cell->get_child(0));
			label->set_text("8");
		}
	    if (Input::get_singleton()->is_action_just_pressed("9"))
		{
			Label *label = Object::cast_to<Label>(chosen_cell->get_child(0));
			label->set_text("9");
		}
    }
    
    if (Object::cast_to<HFlowContainer>(get_child(0))->get_children().size() == 81)
    {
        check_field();
    }
    
}

void SudokuField::shuffle_rows(int array[9][9]) 
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);

    for (int i = 0; i < 3; ++i) 
    {
        std::array<int, 3> row_indices = {i * 3, i * 3 + 1, i * 3 + 2};
        std::shuffle(row_indices.begin(), row_indices.end(), rng);

        int temp[3][9];
        for (int j = 0; j < 3; ++j) 
        {
            for (int k = 0; k < 9; ++k) 
            {
                temp[j][k] = array[row_indices[j]][k];
            }
        }

        for (int j = 0; j < 3; ++j) 
        {
            for (int k = 0; k < 9; ++k) 
            {
                array[i * 3 + j][k] = temp[j][k];
            }
        }
    }
}

void SudokuField::shuffle_columns(int array[9][9]) 
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);


    for (int i = 0; i < 3; ++i) 
    {
        std::array<int, 3> col_indices = {i * 3, i * 3 + 1, i * 3 + 2};
        std::shuffle(col_indices.begin(), col_indices.end(), rng);

        int temp[9][3];
        for (int j = 0; j < 9; ++j) 
        {
            for (int k = 0; k < 3; ++k) 
            {
                temp[j][k] = array[j][col_indices[k]];
            }
        }

        for (int j = 0; j < 9; ++j) 
        {
            for (int k = 0; k < 3; ++k) 
            {
                array[j][i * 3 + k] = temp[j][k];
            }
        }
    }
}

void SudokuField::shuffle_groups(int array[9][9]) 
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);

    std::array<int, 3> row_groups = {0, 1, 2};
    std::shuffle(row_groups.begin(), row_groups.end(), rng);

    int temp_rows[9][9];
    for (int i = 0; i < 3; ++i) 
    {
        for (int j = 0; j < 3; ++j) 
        {
            for (int k = 0; k < 9; ++k) 
            {
                temp_rows[i * 3 + j][k] = array[row_groups[i] * 3 + j][k];
            }
        }
    }
    std::copy(&temp_rows[0][0], &temp_rows[0][0] + 9 * 9, &array[0][0]);

    std::array<int, 3> col_groups = {0, 1, 2};
    std::shuffle(col_groups.begin(), col_groups.end(), rng);

    int temp_cols[9][9];
    for (int i = 0; i < 3; ++i) 
    {
        for (int j = 0; j < 9; ++j) 
        {
            for (int k = 0; k < 3; ++k) 
            {
                temp_cols[j][i * 3 + k] = array[j][col_groups[i] * 3 + k];
            }
        }
    }
    std::copy(&temp_cols[0][0], &temp_cols[0][0] + 9 * 9, &array[0][0]);
}

void SudokuField::shuffle_sudoku(int array[9][9]) 
{
    shuffle_rows(array);
    shuffle_columns(array);
    shuffle_groups(array);
}

void SudokuField::check_field()
{
    Array array = Object::cast_to<HFlowContainer>(get_child(0))->get_children();
    for (int i = 0; i < array.size(); i++)
    {
        Object::cast_to<SudokuCell>(array[i])->check_cell();
    }
}