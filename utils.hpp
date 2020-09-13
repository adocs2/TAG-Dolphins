// Afonso Dias de Oliveira Conceição Silva - 140055771
// Gabriel Nunes Rodrigues Fonseca - 160006597

#ifndef __UTILS__H__
#define __UTILS__H__

#include <set>
#include <vector>


//intersecao entre um set A e um B
std::set<int> intersection (std::set<int> a, std::set<int> b);

//uniao entre um set A e um B
std::set<int> set_union (std::set<int> a, std::set<int> b);

//diferenca entre um set A e um B
std::set<int> difference (std::set<int> a, std::set<int> b);

//encontra um elemento x em um vector
bool find_in_vector(int x, std::vector<int> a);

#endif