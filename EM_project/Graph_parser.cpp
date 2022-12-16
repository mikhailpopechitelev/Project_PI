#include "graph_parser.h"


qreal Vertices::get_x(){
return x;
}

qreal Vertices::get_y() {
    return y;
};

Vertices::Vertices() {
    this->x = 0;
    this->y = 0;
    this->id =0;
};

Vertices::Vertices(const qreal& x, const qreal& y,const std::string& m_name, const int& id, const qreal& r){
    this->x = x;
    this->y = y;
    this->id =id;
    this->m_name = m_name;
    this->r = r;
}

Vertices& Vertices::operator=(const Vertices& other) {
    this->m_name = other.m_name;
    this->x = other.x;
    this->y = other.y;
    this->id = other.id;
    return *this;
};

std::string Edges::to_str(const std::string& s) {
    std::string str = "";
    for (size_t i = 1; i < s.size()-1; i++)
    {
        str += s[i];
    }
    return str;
};

/*
std::pair<std::vector<Edges>,std::vector<Vertices>> Edges::get_ver_edges(const std::string& url){
    std::pair<std::vector<Edges>,std::vector<Vertices>> final_mas;
    std::vector<Vertices> mas_verties;
    std::vector<Edges> mas_edges;


    std::string str;
    std::ifstream file(url);

    std::vector<std::string> elem;
    std::vector<std::vector<std::string>> final;
    std::vector<std::vector<std::vector<std::string>>> tmp;


    while (std::getline(file, str, '{')) {
        elem.push_back(str);
    }
    file.close();

    for (size_t i = 2; i < elem.size(); i++)
    {
        std::string str = elem[i];
        final.push_back(split(str, ','));
    }
    elem.clear();

    tmp.resize(final.size());

    for (size_t i = 0; i < final.size(); i++)
    {
        for (size_t j = 0; j < final[i].size(); j++)
        {
            tmp[i].push_back(split(final[i][j], ':'));
        }
    }

    final.clear();

    for (size_t i = 0; i < tmp.size(); i++)
    {
        if (tmp[i].size() == 8)
        {
            qreal x = stoi(tmp[i][0][1]); qreal y = stoi(tmp[i][1][1]); int name = stoi(to_str(tmp[i][2][1]));
            mas_verties.push_back(Vertices(x, y, name,i));
        }
        if (tmp[i].size() == 9)
        {
            Vertices from = mas_verties[stoi(tmp[i][0][1])]; Vertices to = mas_verties[stoi(tmp[i][1][1])];
            mas_edges.push_back(Edges(from, to));
        }
    }
    final_mas.first = mas_edges;
    final_mas.second = mas_verties;
    return final_mas;
}
*/
std::vector<std::string> Edges::split(const std::string& s, const char& delimber ) {
    std::vector<std::string> tmp;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss,item,delimber))
    {
        if (item[1] != 'e' && item[1] != 't')
        {
            tmp.push_back(item);
        }
    }
    return tmp;
}



Edges::Edges(Vertices from, Vertices to)
{
    this->from = from;
    this->to = to;
};

Edges::Edges()
{
    this->from = Vertices();
    this->to = Vertices();
};

Vertices::Vertices(const qreal& x, const qreal& y,const std::string& m_name, const int& id){
    this->m_name =m_name;
    this->x = x;
    this->y = y;
    this->id = id;
}

Vertices::Vertices(const Vertices& other){
    this->m_name = other.m_name;
    this->x = other.x;
    this->y = other.y;
    this->id = other.id;
}

std::string Vertices::get_m_name(){
    return m_name;
}


Vertices Edges::get_vertices_from(){
    return this->from;
}

Vertices Edges::get_vertices_to(){
    return this->to;
}

int Vertices::get_id(){
    return id;
}
