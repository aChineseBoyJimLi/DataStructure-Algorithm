//
// Created by jim on 19-8-6.
//

#ifndef DATA_STRUCTURE___ALGORITHM_MY_STRING_ALGORITHM_H
#define DATA_STRUCTURE___ALGORITHM_MY_STRING_ALGORITHM_H

#include <string>

namespace m_str{

    /***************************************************************************************************
     * 字符串排序算法
     * 有两类完全不同的字符串排序方法, 分别是低位优先和高位优先, 通过利用字符串的特殊性质, 将会比通用排序算法更加高效.
     *
     * 在分析字符串排序算法时, 字母表的大小是一个重要的因素. 这里是基于拓展的 ASCII 字符集的字符串
     * (R=256). 但也会分析来自较小字母表的字符串(例如基因序列)和来自较大字母表的字符串(例如 Unicode
     * 字母表)
     **************************************************************************************************/

    /*
     * 在理解字符串排序算法前, 需要了解索引计数法
     *
     * 键索引计数法
     * 这种方法其实就是计数排序, 同样这里的实现方法也可以用于计数排序. 我在计数排序的实现是不稳定的
     * 排序, 这里的实现方法是稳定的
     *
     * 输入一组键值对, 键值的范围 1-R, 根据键排序, 这里采用了一个稳定的计数规则
     */
    struct my_pair{
        int key;
        std::string val;
        my_pair& operator= (const my_pair& right)
        {
            this->key = right.key;
            this->val = right.val;
            return *this;
        }
    };
    void IndexCountingMethod(std::vector<my_pair>& vec, int R){

        int N = vec.size();    // 序列的长度
        std::vector<int> count(R+1, 0); // 计数序列
        std::vector<my_pair> aux(vec.size());

        // 计算出现的频率
        for(int i=0; i<N; i++)
            count[vec[i].key + 1]++; // 这里将键值加一, 再存入相应下标的位置, 这样做是有目的的

        // 将频率转换为索引
        for(int r=0; r<R; r++)
            count[r+1] += count[r];

        // 将元素分类
        for(int i=0; i<N; i++)
            aux[count[vec[i].key]++] = vec[i];

        // 填写
        for(int i=0; i<N; i++)
            vec[i] = aux[i];
    }

    /*
     * 低位优先的字符串排序(LSD)
     * 这类方法会从右到左检查键中的字符. 它将字符看作一个 256 进制的数字, 那么从右到左检查字符串
     * 就等价于先检查数字的最低位(和基数排序一样). 这种方法最适用于键的长度都相同的字符串排序应用.
     *
     * 如果字符串长度均为 W, 那就从右向左以每个位置的字符作为键, 用键索引计数法将字符串排序 W 遍,
     * 这种方法和基数排序的原理是一样的.
     *
     * 注意这里的键索引计数法需要是稳定的, 否则这种方法是行不通的
     *
     * 这里的字符串, 采用的是拓展 ASCII 码
     */

    void LSD_sort(std::vector<std::string>& vec, int w){
        int N = vec.size(); // vec 的长度
        int R = 256;
        std::vector<std::string> aux;

        // 从右到左, 根据每一个字符进行排序
        for(int d=w-1; d>=0; d--){
            // 索引计数法排序
            std::vector<int> count(R+1, 0); // 计数序列

            for(int i=0; i<N ;i++)
                count[vec[i][d] + 1] ++;
            for(int r=0; r<R; r++)
                count[r+1] += count[r];
            for(int i=0; i<N; i++)
                aux[count[vec[i][d]]++] = vec[i];
            for(int i=0; i<N; i++)
                vec[i] = aux[i];
        }
    }

    /*
     * 高位优先的字符串排序(MSD)
     * 这类方法会从左到右检查键中的字符, 首先查看的是最高位的字符. 高位优先的字符串排序的特点在于,
     * 它们不一定要检查所有的输入就能够完成排序. 高位优先的字符串排序和快速排序类似, 因为它们都会
     * 将需要排序的数组切分成独立的部分并递归地用相同的方法处理子数组来完成排序. 它们的区别支出在于
     * 高位优先的字符串排序算法在切分时仅使用键的第一个字符, 而快速排序的比较会涉及键的全部.
     *
     * 这里实现其中两种方法, 第一种方法将相同的字符的键划入同一个切分; 第二种方法则总会产生三个切分,
     * 分别对应被搜索键的第一个字符小于, 等于或大于切分键的第一个字符的情况
     */


}





#endif //DATA_STRUCTURE___ALGORITHM_MY_STRING_ALGORITHM_H
