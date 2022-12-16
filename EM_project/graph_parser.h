#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <QWidget>

//классы вершины и ребра
class Vertices
{

public:
    //методы получения значений вершин
    qreal get_x();
    qreal get_y();
    std::string get_m_name();
    int get_id();

    //понтструкторы вершины
    Vertices();
    Vertices(const qreal& x, const qreal& y,const int& name, const int& id);
    Vertices(const qreal& x, const qreal& y,const std::string& m_name, const int& id);
    Vertices(const qreal& x, const qreal& y,const std::string& m_name, const int& id, const qreal& r);
    Vertices(const Vertices& other);
    //деструктор вершины
    ~Vertices() = default;

    Vertices& operator=(const Vertices& other);

private:
    std::string m_name="";
    qreal x = 0;
    qreal y = 0;
    int id =0;
    qreal r = 0;
};

//класс ребра
class Edges
{
public:

    //функция убирающая ковычки у названия
    std::string to_str(const std::string& s);

    //функция получения списка ребер по файлу и списка вершин
    std::pair<std::vector<Edges>,std::vector<Vertices>> get_ver_edges(const std::string& url);

    //функция разбивающая строку по разделителю
    std::vector<std::string> split(const std::string& s, const char& delimber );

    //методы получения полей ребра
    Vertices get_vertices_from();
    Vertices get_vertices_to();

    //конструктор и деструктор ребра по вершинам
    Edges(Vertices from, Vertices to);
    Edges();
    ~Edges() = default;

private:
    //полня ребра: откуда и куда ребро идет
    Vertices from;
    Vertices to;

};

#endif // GRAPH_H
