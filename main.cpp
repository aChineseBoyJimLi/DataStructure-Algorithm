#include "headers/pch.h"


void UnitTest(){
    srand((unsigned int)time(0));
    for(int k=0; k<100; k++){
        std::vector<int> vec;    // 待排序数组
        std::cout << k << '\t' << "排序前: ";
//        vec = {67,	42,	49,	52,	16,	21,	80,	64,	67,	67};
        for(int i=0; i<15; i++){
            int r = rand() % 300;
            std::cout << r << '\t' ;
            vec.push_back(r);
        }

        msa::heap_sort(vec);

        std::cout << "排序后: ";

        for(auto i=vec.begin(); i!=vec.end(); i++){
            std::cout << *i << '\t';
        }

        std::cout << std::endl;
    }
}

int main() {

    UnitTest();

    return 0;
}