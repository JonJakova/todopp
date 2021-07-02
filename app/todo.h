#ifndef TODO_H

#include <iostream>
#include <vector>

struct todo
{
    std::string description;
    int importance;
    bool done;
};

void on_init(std::vector<todo> *t);
void on_exit(std::vector<todo> *t);
void mark_done(std::vector<todo> *t);
void design_number_box(int index);
void add_todo(std::vector<todo> *t, todo n);
void remove_todo(std::vector<todo> *t);
void view_list(std::vector<todo> *t);
std::string map_todo_to_string(todo &single);
todo map_string_to_todo(std::string content);
todo get_new_todo();

#endif // !TODO_H