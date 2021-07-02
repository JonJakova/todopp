#include "todo.h"
#include "../common/persist.h"

//todo Move file to home dir
void on_init(std::vector<todo> *t)
{
    std::string file_path = ".todo.bup";
    if (!does_file_exist(file_path))
    {
        return;
    }
    for (auto &&unmapped : read_file_content(file_path))
    {
        (*t).push_back(map_string_to_todo(unmapped));
    }
}

void on_exit(std::vector<todo> *t)
{
    std::string file_path = ".todo.bup";
    std::vector<std::string> mapped;
    for (auto &&todo : (*t))
    {
        mapped.push_back(map_todo_to_string(todo));
    }
    write_all_to_file(file_path, mapped);
}

void add_todo(std::vector<todo> *t, todo n)
{
    (*t).push_back(n);
};

void remove_todo(std::vector<todo> *t)
{
    std::cout << "Enter number to remove: ";
    int inNum;
    // Need to check for illegal input
    std::cin >> inNum;
    if ((*t).size() > inNum)
    {
        (*t).erase((*t).begin() + inNum);
    }
};

todo get_new_todo()
{
    todo todo_n;
    todo_n.done = false;

    std::cout << "Enter description" << std::endl;
    std::cin >> todo_n.description;

    std::cout << "Enter importance (Number)" << std::endl;
    std::string importance;

uImp:
    std::cin >> importance;
    try
    {
        todo_n.importance = std::stoi(importance);
    }
    catch (const std::exception &e)
    {
        std::cout << "Enter importance (Number)" << std::endl;
        goto uImp;
    }

    return todo_n;
};

void view_list(std::vector<todo> *t)
{
    std::vector<todo> todos = *t;
    if (todos.size() == 0)
    {
        std::cout << "Nothing to do..." << std::endl;
    }
    else
    {
        std::cout << " +++++++++++++++++++++++++++++++++++++++++ " << std::endl;
        for (int i = 0; i < todos.size(); i++)
        {
            std::string status = "Not yet";
            if (todos.at(i).done)
            {
                status = "Completed";
            }

            design_number_box(i);
            std::cout << "|  Importance: " << todos.at(i).importance << std::endl;
            std::cout << "|  " << todos.at(i).description << std::endl;
            std::cout << "|  Done: " << status << std::endl;
            if (todos.size() > i + 1)
            {
                std::cout << "-----------------------------------------" << std::endl;
            }
        };
        std::cout << " +++++++++++++++++++++++++++++++++++++++++ " << std::endl;
    }
};

void design_number_box(int index)
{
    int origin = index;
    unsigned int number_of_digits = 0;
    do
    {
        ++number_of_digits;
        index /= 10;
    } while (index);

    std::cout << " ";

    for (unsigned int i = 0; i < number_of_digits; i++)
    {
        std::cout << "---";
    }

    std::cout << std::endl
              << "| " << origin << " |" << std::endl
              << " ";

    for (unsigned int i = 0; i < number_of_digits; i++)
    {
        std::cout << "---";
    }
    std::cout << " " << std::endl;
}

void mark_done(std::vector<todo> *t)
{
    std::cout << "Enter number of item to mark as done." << std::endl;
    int index;
    std::cin >> index;

    (*t).at(index).done = true;
}

//todo Preserve order
std::string map_todo_to_string(todo &single)
{
    std::string content;
    content.append(single.description);
    content.append(";;");
    content.append(std::to_string(single.importance));
    content.append(";;");
    content.append(single.done ? std::to_string(1) : std::to_string(0));
    return content;
}

// This code here sucks (like the rest of this program but we don't talk about that)
todo map_string_to_todo(std::string content)
{
    todo converted;
    converted.description = content.substr(0, content.find(";;"));
    content.erase(0, content.find(";;") + 2);
    converted.importance = stoi(content.substr(0, content.find(";;")));
    content.erase(0, content.find(";;") + 2);
    if (!content.compare("1"))
    {
        converted.done = true;
    }
    else
    {
        converted.done = false;
    }
    return converted;
}