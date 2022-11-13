#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

//классы вершины и ребра
class Vertices
{

public:
    int get_x();

    int get_y();
    int get_name();
    Vertices();
    Vertices(const int& x, const int& y,const int& name);
    ~Vertices() = default;

    Vertices& operator=(const Vertices& other);

private:
    int name = 0;
    int x = 0;
    int y = 0;
};

class Edges
{

public:
    //функция убирающая ковычки у названия
    std::string to_str(const std::string& s);

    //функция получения списка ребер по файлу и списка вершин
    std::pair<std::vector<Edges>,std::vector<Vertices>> get_ver_edges(const std::string& url);
    //функция разбивающая строку по разделителю
    std::vector<std::string> split(const std::string& s, const char& delimber );

    int get_name_from();
    int get_name_to();
    int get_x_from();
    int get_x_to();
    int get_y_from();
    int get_y_to();

    Edges(Vertices from, Vertices to);
    Edges();
    ~Edges() = default;

private:

    Vertices from;
    Vertices to;
};



#endif // GRAPH_H
