#include "headers/pch.h"

void SortUnitTest(){
    srand((unsigned int)time(0));
    for(int k=0; k<100; k++){
        std::vector<int> vec;    // 待排序数组
        std::cout << k << '\t' << "排序前: ";
        for(int i=0; i<15; i++){
            int r = rand() % 300;
            std::cout << r << '\t' ;
            vec.push_back(r);
        }

        msa::heap_sort(vec);

        std::cout << "排序后: ";

        for(auto i:vec){
            std::cout << i << std::endl;
        }

        std::cout << std::endl;
    }
}

void GraphUnitTest(){
    mg::CGraph_Matrix<char> graphMatrix;
    graphMatrix.size = 8;
    graphMatrix.vertexes = {'A','B','C','D','E','F','G','H'};
    graphMatrix.matrix = {
            {0, 3, 1, INFINITE, 2, 5, INFINITE, INFINITE},
            {3, 0, INFINITE, 1, INFINITE, 2, 3, INFINITE},
            {1, INFINITE, 0, INFINITE, 6, INFINITE, INFINITE, INFINITE},
            {INFINITE, 1, INFINITE, 0, INFINITE, INFINITE, 1, 4},
            {2, INFINITE, 6, INFINITE, 0, INFINITE, INFINITE, 1},
            {5, 2, INFINITE, INFINITE, INFINITE, 0, INFINITE, INFINITE},
            {INFINITE, 3, INFINITE, 1, INFINITE, INFINITE, 0, INFINITE},
            {INFINITE, INFINITE, INFINITE, 4, 1, INFINITE, INFINITE, 0}
    };

    mg::Dijiskra(graphMatrix, 0);
}


void StringUnitTest(){
    srand((unsigned int)time(0));
    std::string names[10]{"Jim", "jack", "Mater", "Matt", "Dogg", "DM", "Jordan", "Feno", "LHY", "YYP"};
    std::vector<m_str::my_pair> vec;
    for(int i = 0; i<10; i++){
        m_str::my_pair pair;
        pair.key = rand() % 4 + 1; // 生成 [1,5) 范围的键值
        pair.val = names[rand() % 10];
        std::cout << pair.key << ":" << pair.val << std::endl;
        vec.push_back(pair);
    }
    std::cout << "排序后" << std::endl;

    m_str::IndexCountingMethod(vec, 4);

    for(auto i:vec){
        std::cout << i.key << ":" << i.val << std::endl;
    }
}

int main() {

//    GraphUnitTest();

    StringUnitTest();


    return 0;
}