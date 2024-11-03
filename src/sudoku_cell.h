#ifndef SUDOKU_CELL_H
#define SUDOKU_CELL_H

#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

class SudokuCell : public Button {
    GDCLASS(SudokuCell, Button)

protected:
    static void _bind_methods();

public:
    SudokuCell();
    ~SudokuCell();
	bool changable; 
	int sector;
	bool chosen;
	int position;
    void on_button_pressed();
    void _process(double delta);
	void _ready();
	void set_label();
	void define_sector();
	void check_cell();
private:
    double time_passed;
};

#endif