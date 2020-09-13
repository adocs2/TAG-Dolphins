// Afonso Dias de Oliveira Conceição Silva - 140055771
// Gabriel Nunes Rodrigues Fonseca - 160006597

#include "utils.hpp"
#include <set>
#include <vector>


std::set<int> intersection (std::set<int> a, std::set<int> b){
    std::set<int> result;
    for(int e : a){
        if(b.count(e))
            result.insert(e);
    }
    return result;
}

std::set<int> set_union (std::set<int> a, std::set<int> b){
    std::set<int> result;
    for(int e : a)
        result.insert(e);
    for(int e : b)
        result.insert(e);
    return result;
}

std::set<int> difference (std::set<int> a, std::set<int> b){
    std::set<int> result;
    for(int e : a){
        if(!b.count(e))
            result.insert(e);
    }
    return result;
}

bool find_in_vector(int x, std::vector<int> a){
    for(long unsigned int i = 0; i<a.size(); i++){
        if(a[i] == x) return true;
    }
    return false;
}