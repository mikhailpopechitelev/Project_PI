#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <QWidget>

/**
 *  @brief Класс вершины
 */
//классы вершины и ребра
class Vertices
{

public:
    //!методы получения значений вершин
    qreal get_x();
    qreal get_y();
    std::string get_m_name();
    int get_id();

    //!понтструкторы вершины
    Vertices();
    Vertices(const qreal& x, const qreal& y,const int& name, const int& id);
    Vertices(const qreal& x, const qreal& y,const std::string& m_name, const int& id);
    Vertices(const qreal& x, const qreal& y,const std::string& m_name, const int& id, const qreal& r);
    Vertices(const Vertices& other);

    //!деструктор вершины
    ~Vertices() = default;

    Vertices& operator=(const Vertices& other);

private:
    std::string m_name="";
    qreal x = 0;
    qreal y = 0;
    int id =0;
    qreal r = 0;
};

/**
 *  @brief Класс ребра
 */
class Edges
{
public:

    /**
     *  @brief функция преобразающая стоку в набор подряд идущих символов
     *  @param s строку которую нужно разбить
     *  @return стоку которую нужно было преобразовать
     */
    std::string to_str(const std::string& s);

    //!функция получения списка ребер по файлу и списка вершин
    /**
     *  @brief функция получаения списка ребер по файлу
     *  @param url сама ссылка на файл
     *  @return список ребер
     */
    std::pair<std::vector<Edges>,std::vector<Vertices>> get_ver_edges(const std::string& url);

    /**
    *  @brief функция разбивающая строку по разделителю
    *  @param s получаемая стока
    *  @param delimber разделитель
    *  @return список ребер
    */
    std::vector<std::string> split(const std::string& s, const char& delimber );

    /**
    *  @brief методы получения полей узла
    */
    Vertices get_vertices_from();
    /**
    *  @brief методы получения полей узла
    */
    Vertices get_vertices_to();

    /**
    *  @brief конструктор ребра
    */
    Edges(Vertices from, Vertices to);
    /**
    *  @brief конструктор по умолчвнию
    */
    Edges();
    /**
    *  @brief дуструктор ребра
    */
    ~Edges() = default;

private:
    //!поля ребра: откуда и куда ребро идет
    Vertices from;
    Vertices to;

};

#endif // GRAPH_H
