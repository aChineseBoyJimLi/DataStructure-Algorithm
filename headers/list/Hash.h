//
// Created by jim on 19-7-20.
//

#ifndef LIST_HASH_H
#define LIST_HASH_H

#include <vector>
#include <iostream>

/*
 * Hash Table 可提供对任何有名项的存取操作和删除操作. 由于操作对象是
 * 有名项, 所以 hash table 也可被视为一种字典结构. 这种结构的用意在
 * 于提供常数时间的插入, 删除, 搜索操作. 这种表现是以统计为基础的, 不
 * 需依赖输入元素的随机性
 *
 * hash table 通过 hash function 将数值映射到相应的数组下标中, 这样
 * 我们用于存数据的数组的长度就可以小于带存储数据的长度. 这样做的问题在
 * 于会使不同的元素映射到同样的数组单元中, 这便是所谓的"碰撞". 解决碰撞
 * 的方法右很多种, 包括线性探测, 二次探测, 开链等做法.
 *
 * 除了碰撞, hash table 还有一个需要考虑的问题是 array 的成长. 欲扩充
 * 表格, 首先必须找出下一个新的而且够大的质数, 然后必须考虑表格重建的成本
 */

// 28 个质数
//enum { _num_primes = 28 };
//
//static const unsigned long _prime_list[_num_primes] =
//        {
//                53ul,         97ul,         193ul,       389ul,       769ul,
//                1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
//                49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
//                1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
//                50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
//                1610612741ul, 3221225473ul, 4294967291ul
//        };
//
//inline unsigned long __stl_next_prime(unsigned long __n)
//{
//    const unsigned long* __first = _prime_list;
//    const unsigned long* __last = _prime_list + (int)_num_primes;
//    const unsigned long* pos = lower_bound(__first, __last, __n);
//    return pos == __last ? *(__last - 1) : *pos;
//}

// 使用开链法解决碰撞问题的 hash table 的实现

class hashtable{
public:

};





#endif //LIST_HASH_H
