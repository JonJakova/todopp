#include <iostream>
#include <vector>

struct todo
{
    std::string description;
    int importance;
    bool done;
};

void markDone(std::vector<todo> *t);
void designNumberBox(int index);
void addTodo(std::vector<todo> *t, todo n);
void removeTodo(std::vector<todo> *t);
void viewList(std::vector<todo> *t);
todo getNewTodo();

int main()
{
    std::vector<todo> todos;
    std::vector<todo> *todos_ptr = &todos;
    std::string command;
    std::string inNum;

    for (;;)
    {
        std::cout << "1: View List | 2: Add to List | 3: Remove from list | 4: Mark as done | 0 Close " << std::endl;

        int input;
        try
        {
            std::cin >> input;
        }
        catch (const std::exception &e)
        {
            return 0;
        }

        switch (input)
        {
        case 0:
            return 0;
        case 1:
            viewList(todos_ptr);
            break;
        case 2:
            addTodo(todos_ptr, getNewTodo());
            break;
        case 3:
            removeTodo(todos_ptr);
            break;
        case 4:
            markDone(todos_ptr);
            break;
        default:
            std::cout << "Not accepted";
            return 0;
        }
    }
}

void addTodo(std::vector<todo> *t, todo n)
{
    (*t).push_back(n);
};

void removeTodo(std::vector<todo> *t)
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

todo getNewTodo()
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

void viewList(std::vector<todo> *t)
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

            designNumberBox(i);
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

void designNumberBox(int index)
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

void markDone(std::vector<todo> *t)
{
    std::cout << "Enter number of item to mark as done." << std::endl;
    int index;
    std::cin >> index;

    (*t).at(index).done = true;
}
