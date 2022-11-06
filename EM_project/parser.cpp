#include "parser.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>

Parser::Parser()
{

}

class vertex{

public:
    char* name;
    std::vector<vertex> edges;
    int x;
    int y;
};


std::vector<vertex> vertexes;


void Parser::decode(char* name)
{
    FILE *f;

    int flag = 0;
    int tmp;

    if(f = fopen(name, "r"))
    {
        while(1)
        {
            if(feof(f)) break;
        }

        fscanf(f, "%c", &tmp);

        fclose(f);
    }
    else{
        printf("error\n");
    }
}

