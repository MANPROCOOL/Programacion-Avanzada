#include "sort.hpp"
#include <algorithm>

void sort(int v[], int &size){
    std::sort(v, v + size);
}

void sort(std::vector<int> v){
    std::sort(v.begin(), v.end());
}
