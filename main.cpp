#include <iostream>
#include <cstdint>
#include <vector>

struct todo
{
        std::string description;
        int importance;
};

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
                std::cout << "1: View List | 2: Add to List | 3: Remove from list " << std::endl;

                int input;
                std::cin >> input;

                switch (input)
                {
                case 1:
                        viewList(todos_ptr);
                        break;
                case 2:
                        addTodo(todos_ptr, getNewTodo());
                        break;
                case 3:
                        removeTodo(todos_ptr);
                        break;
                default:
                        std::cout << "Not accepted";
                }
        }
}

void addTodo(std::vector<todo> *t, todo n)
{
        (*t).push_back(n);
};

// Doesn't seem to work for now
void removeTodo(std::vector<todo> *t)
{
        viewList(t);
        std::vector<todo> tRef = *t;
        std::cout << "Enter number to remove: ";
        int inNum;
        // Need to check for illegal input
        std::cin >> inNum;

        if (tRef.size() > inNum)
        {
                tRef.erase(tRef.begin() + inNum);
        }
};

todo getNewTodo()
{
        todo todo_n;

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
                        designNumberBox(i);
                        std::cout << "|  Importance: " << todos.at(i).importance << std::endl;
                        std::cout << "|  " << todos.at(i).description << std::endl;
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