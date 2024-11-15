#ifndef SUDOKU_FIELD_H
#define SUDOKU_FIELD_H

#include <godot_cpp/classes/center_container.hpp>
#include <godot_cpp/classes/h_flow_container.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

class SudokuField : public CenterContainer {
    GDCLASS(SudokuField, CenterContainer)

protected:
    static void _bind_methods();

public:
    SudokuField();
    ~SudokuField();
    static int x1;
    static int x2;
    static int x3;
    static int x4;
    static int x5;
    static int x6;
    static int x7;
    static int x8;
    static int x9;
    static int counter;
    static int field[9][9];
    void on_button_pressed();
    void _process(double delta);
	void _ready();
    void shuffle_field();
    void shuffle();
    int return_next_cell();
    void shuffle_rows(int array[9][9]);
    void shuffle_columns(int array[9][9]);
    void shuffle_groups(int array[9][9]);
    void shuffle_sudoku(int array[9][9]);
    void check_field();
    void shuffle_x();

private:
    double time_passed;
};

#endif