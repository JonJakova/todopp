#ifndef PERSIST_H

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sstream>
#include <vector>

inline bool does_file_exist(const std::string &file_name)
{
    struct stat buffer;
    return (stat(file_name.c_str(), &buffer) == 0);
};

inline void write_to_file(const std::string &file_name, const std::string &content)
{
    std::ofstream writer(file_name, std::ofstream::out);
    writer << content << std::endl;
    writer.close();
}

inline void write_all_to_file(const std::string &file_name, const std::vector<std::string> &content)
{
    std::ofstream writer(file_name, std::ofstream::out);
    for (auto &&i : content)
    {
        writer << i << std::endl;
    }
    writer.close();
}

inline std::vector<std::string> read_file_content(const std::string &file_name)
{
    std::ifstream reader(file_name, std::ifstream::in);
    std::vector<std::string> unformatted_todos;
    std::string line;

    while (std::getline(reader, line))
    {
        std::istringstream iss(line);
        unformatted_todos.push_back(line);
    }

    reader.close();
    return unformatted_todos;
}

#endif // !PERSIST_H