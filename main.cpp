// Afonso Dias de Oliveira Conceição Silva - 140055771
// Gabriel Nunes Rodrigues Fonseca - 160006597

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include "utils.hpp"

// nome do arquivo mtx
std::string file_name = "soc-dolphins.mtx";

std::ifstream input_file;

std::string line;
bool first_valid_input = false;
// header do arquivo mtx
int height, width, edges;
double global_clustering = 0;

//Bron kerbosch sem pivoteamento seguindo o slide
void Bron_Kerbosch(std::set<int> R, std::set<int> P, std::set<int> X, std::vector<std::vector<int>> graph)
{

    if (P.empty() && X.empty())
    {
        std::cout << "Clique maximal achado entre " << R.size() << " vértices: ";
        for (int e : R)
            std::cout << e << " ";
        std::cout << std::endl;
    }

    auto it = P.begin();
    while (!P.empty())
    {

        int v = *it;
        std::set<int> temp; //temp = {v}
        temp.insert(v);

        std::set<int> Nv; //Nv = N(v)
        for (int e : graph[v])
            Nv.insert(e);

        // chamada recursiva
        Bron_Kerbosch(set_union(R, temp), intersection(P, Nv), intersection(X, Nv), graph);
        P = difference(P, temp);
        X = set_union(X, temp);

        if (!P.empty())
            it = P.begin();
    }
}

std::vector<std::vector<int>> readFileAndBuildGraph()
{

    input_file.open(file_name.c_str());

    if (input_file.fail())
    {
        std::cout << "Erro ao abrir o arquivo" << std::endl;
        exit(0);
    }
    else
    {

        //procuramos o header do arquivo
        while (!first_valid_input && getline(input_file, line))
        {

            if (line[0] != '%')
            { //pula os comentários do arquivo

                if (first_valid_input == false)
                {
                    first_valid_input = true;
                    std::stringstream stream(line);
                    stream >> height >> width >> edges;
                }
            }

            line.clear();
        }

        std::vector<std::vector<int>> graph(height + 1);
        //pegando as linhas da matriz
        while (getline(input_file, line))
        {
            int a, b;
            std::stringstream stream(line);
            stream >> a >> b;

            graph[a].push_back(b);
            graph[b].push_back(a);

            line.clear();
        }
        std::cout << std::endl;
        return graph;
    }
    return (std::vector<std::vector<int>>)0;
}

//print da lista de adjacencia
void printList(std::vector<std::vector<int>> graph)
{
    std::cout << "LISTA DE ADJACÊNCIA" << std::endl;
    int x = 0;
    for (int i = 1; i <= height; i++)
    {
        std::cout << "Vertíce " << i << ": ";
        for (unsigned int j = 0; j < graph[i].size(); j++)
        {
            std::cout << " " << i << " -> " << graph[i][j] << ", ";
            x++;
        }
        std::cout << std::endl;
    }
    //arestas divido por 2, pois o grafo não tem peso e nem direção
    std::cout << std::endl;
    std::cout << "NÚMERO TOTAL DE ARESTAS DO GRAFO:" << x / 2;
    std::cout << std::endl;
}

//print dos graus de cada vertice
void printDegree(std::vector<std::vector<int>> graph)
{
    std::cout << "GRAUS DE CADA VÉRTICE" << std::endl;
    for (int i = 1; i <= height; i++)
    {
        std::cout << "Grau de " << i << " = " << graph[i].size() << std::endl;
    }
}

//print dos cliques maximais
void printCliques(std::vector<std::vector<int>> graph)
{
    std::cout << "CLIQUES MAXIMAIS DO GRAFO" << std::endl;
    std::set<int> r;
    std::set<int> p;
    std::set<int> x;

    for (int i = 1; i <= height; i++)
    {
        p.insert(i); //criando p com todos os vértices do grafo
    }
    Bron_Kerbosch(r, p, x, graph);
}

//print do coenficiente de aglomeração
void printCoefficient(std::vector<std::vector<int>> graph)
{
    std::cout << "COEFICIENTE DE AGLOMERAÇÃO DE CADA VÉRTICE" << std::endl;
    for (int i = 1; i <= height; i++)
    { //para cada vertice (v) do grafo
        std::cout << "coeficiente de " << i << " = ";
        int t = 0;

        bool tab[height][width];
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                tab[i][j] = false;

        for (unsigned int x = 0; x < graph[i].size(); x++)
        { //para cada vertice (a) adjacente a (v)
            for (unsigned int k = 0; k < graph[i].size(); k++)
            { //para cada vertice (b) adjacente a (v)
                if (!tab[x][k] && x != k)
                { //se um triangulo ainda nao foi encontrado
                    if (find_in_vector(graph[i][x], graph[graph[i][k]]))
                    { //se a for encontrado dentre os adjacente a b
                        tab[x][k] = true;
                        tab[k][x] = true; //marcamos na tabela para avisar que ja foi encontrado
                        t++;              //um triangulo formado pelos vertices a, b e v
                    }
                }
            }
        }
        int temp = graph[i].size();
        if (temp * (temp - 1) != 0 && 2 * t != 0)
        {
            double a = 2 * t;
            double b = temp * (temp - 1);
            printf("%.3lf\n", a / b);
            global_clustering += a / b;
        }
        else
            std::cout << 0 << std::endl;
    }
}

//print do coeficiente médio
void printAverageCoefficient(std::vector<std::vector<int>> graph)
{
    global_clustering = global_clustering / height;

    std::cout << "COEFICIENTE MÉDIO DE AGLOMERAÇÃO DO GRAFO" << std::endl;
    std::cout << "Coeficiente médio = " << global_clustering << std::endl;
}

int main()
{
    system("clear");
    std::vector<std::vector<int>> graph = readFileAndBuildGraph();
    printList(graph);
    std::cout << std::endl;
    printDegree(graph);
    std::cout << std::endl;
    printCliques(graph);
    std::cout << std::endl;
    printCoefficient(graph);
    std::cout << std::endl;
    printAverageCoefficient(graph);

    input_file.close();
    return 0;
}
