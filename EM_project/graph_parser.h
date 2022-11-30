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
    int get_name();
    std::string get_m_name();

    //понтструкторы вершины
    Vertices();
    Vertices(const qreal& x, const qreal& y,const int& name);
    Vertices(const qreal& x, const qreal& y,const std::string& m_name);
    Vertices(const Vertices& other);
    //деструктор вершины
    ~Vertices() = default;

    Vertices& operator=(const Vertices& other);

private:
    std::string m_name="";
    int name = 0;
    qreal x = 0;
    qreal y = 0;
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
    std::string get_name_fromm();
    std::string get_name_tom();
    int get_name_from();
    int get_name_to();
    qreal get_x_from();
    qreal get_x_to();
    qreal get_y_from();
    qreal get_y_to();

    //конструктор и деструктор ребра по вершинам
    Edges(Vertices from, Vertices to);
    Edges();
    ~Edges() = default;

private:
    //полня ребра: откуда и куда ребро идет
    Vertices from;
    Vertices to;

};


class Texts
{
private:
    std::string value ="";
    int x =0;
    int y =0;
public:
    Texts(const int& x,const int& y,const std::string& value);
    Texts();
    int get_x();
    int get_y();
    std::string get_text();

};

/*
class Graph{
    std::vector<Edges> m_edges;
    std::vector<Vertices> m_vertis;
    std::vector<Texts> m_texts;
    //std::vector<>
    Graph(const std::vector<Edges>& edges ,
          const std::vector<Vertices>& vertis,
          const std::vector<Texts>& texts
          ){
        m_edges = edges;
        m_vertis = m_vertis;
        m_texts = texts;
    }
};*/

#endif // GRAPH_H
