#include "app/todo.cpp"

int main()
{
    std::vector<todo> todos;
    std::vector<todo>* const todos_ptr = &todos;
    std::string command;
    std::string inNum;
    on_init(todos_ptr);

    for (;;)
    {
        std::cout << "1: View List | 2: Add to List | 3: Remove from list | 4: Mark as done/undone | 0 Close " << std::endl;

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
            on_exit(todos_ptr);
            return 0;
        case 1:
            view_list(todos_ptr);
            break;
        case 2:
            add_todo(todos_ptr, get_new_todo());
            break;
        case 3:
            remove_todo(todos_ptr);
            break;
        case 4:
            mark_done(todos_ptr);
            break;
        default:
            std::cout << "Not accepted";
            return 0;
        }
    }
}
