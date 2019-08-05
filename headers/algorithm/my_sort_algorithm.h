//
// Created by jim on 19-8-5.
//

#ifndef SORT_MY_SORT_ALGORITHM_H
#define SORT_MY_SORT_ALGORITHM_H

#include <vector>
#include <list>
#include <algorithm>

// 经典的 10 个排序算法的实现, 非泛型编程, 仅实现对 int 数组从小到大排序
// 其中复杂度为 n^2 的算法略

/*              平均时间复杂度     空间复杂度       是否稳定
 * 冒泡排序           n^2             1            true
 * 插入排序           n^2             1            false
 * 选择排序           n^2             1
 * 快速排序          nlogn          nlogn
 * 归并排序          nlogn            n
 * 希尔排序          nlogn            1
 * 堆排序            nlogn         nlogn          false
 * ----------------------------------------------------------
 * 计数排序           n+k             n+k            false
 * 桶排序             n+k             n+k           true/false
 * 基数排序           k*n             n+k            true
 */

namespace msa{

    // 交换函数
    void swap(int& left, int& right){
        int temp = left;
        left = right;
        right = temp;
    }

    /****************************************************************************************
     * 比较类排序算法: 冒泡排序, 插入排序, 选择排序, 快速排序, 归并排序, 希尔排序, 堆排序
     * 通过比较来决定元素间的相对次序，由于其时间复杂度不能突破 O(nlogn) , 因此也称为非线性时间比较类排序.
     ****************************************************************************************/

    /*
     * 快速排序
     * 快速排序使用了分治的思想, 通过一趟排序将待排记录分隔成独立的两部分,
     * 其中一部分记录的关键字均比另一部分的关键字小, 则可分别对这两部分记
     * 录继续进行排序, 以达到整个序列有序
     *
     * 步骤:
     * 1. 从数组中挑选一个基准元素(pivot), 通常选择数组的第一个元素;
     * 2. 重新排序数列，所有元素比基准值小的摆放在基准前面, 所有元素比基
     *    准值大的摆在基准的后面(相同的数可以到任一边, 所以快排是一种不稳
     *    定的排序算法). 在这个分区退出之后，该基准就处于数列的中间位置.
     *    这个步骤称为分区（partition）操作;
     * 3. 递归地(recursive)把小于基准值元素的子数列和大于基准值元素的子数
     *    列排序;
     *
     * 参数解释:
     * array 输入一个数组
     * left  数组的起点下标
     * right 数组的终点下标
     *
     * 注: 在选择基准的时候, 如果原数组是一个逆序的数组, 那么选择第一个元素
     *     为基准会导致算法退化成冒泡排序. 所以建议使用随机选择一个元素作基
     *     准
     */

    void quick_sort(std::vector<int>& array, int left, int right){
        if(left >= right)
            return;

        int pivot = array[left]; // 选择数组的第一个元素作为基准元素

        // 使用挖坑法实现元素的交换, partition 操作
        int pivot_index = left; // 记录 pivot 的位置
        int l =left;    // 从数组末尾开始向前移动
        int r = right;  // 从数组头部开始向后移动

        while(r > l){
            while(r>l){
                if(array[r] < pivot){ // 如果r所指的元素比pivot小, 将r的元素填入pivot_index所指的元素中, 同时l右移
                    array[pivot_index] = array[r];
                    pivot_index = r;
                    l++;
                    break;
                }
                r--;    // 如果r所指的元素比pivot大, r左移
            }

            while(r>l){
                if(array[l] > pivot){ // 如果l所指的元素比pivot大, 将l的元素填入pivot_index所指的元素中, 同时r左移
                    array[pivot_index] = array[l];
                    pivot_index = l;
                    r--;
                    break;
                }
                l++;    // 如果l所指的元素比pivot小, l右移
            }
        }
        // 循环结束后, 将pivot的元素填入pivot_index中
        array[pivot_index] = pivot;

        // 递归
        quick_sort(array, 0, pivot_index-1);
        quick_sort(array, pivot_index+1, right);
    }

    /*
     * 归并排序
     * 归并排序是建立在归并操作上的一种有效的排序算法. 该算法是采用分治法的一个
     * 非常典型的应用。将已有序的子序列合并, 得到完全有序的序列; 即先使每个子序
     * 列有序, 再使子序列段间有序. 若将两个有序表合并成一个有序表, 称为2路归并.
     *
     * 步骤:
     * 1. 把长度为 n 的输入序列分成两个长度为 n/2 的子序列;
     * 2. 对这两个子序列分别采用归并排序;
     * 3. 将两个排序好的子序列合并成一个最终的排序序列;
     */

    std::vector<int> merge(std::vector<int> left, std::vector<int> right);
    std::vector<int> merge_sort(std::vector<int> vec) {
        int length = vec.size();
        if (length < 2) {
            return vec;
        }

        // 将数组拆分成两部分
        std::vector<int> left(vec.begin(), vec.begin() + length / 2);
        std::vector<int> right(vec.begin() + length / 2, vec.end());

        // 分别递归进行归并排序, 每次对子序列进行归并排序后, 都是一个有序序列 , 然后再合起来
        return merge(merge_sort(left), merge_sort(right));
    }
    std::vector<int> merge(std::vector<int> left, std::vector<int> right) {
        std::vector<int> res;

        // 将两个有序数组进行合并, 分别从两个序列的头部进行比较
        while (!left.empty() && !right.empty()) {
            if (left[0] < right[0]) {
                res.push_back(left.front());
                left.erase(left.begin());
            }
            else {
                res.push_back(right.front());
                right.erase(right.begin());
            }
        }

        // 把序列中剩下的元素加进合并后的序列
        while (!left.empty()) {
            res.push_back(left.front());
            left.erase(left.begin());
        }
        while (!right.empty()) {
            res.push_back(right.front());
            right.erase(right.begin());
        }
        return res;
    }

    /*
     * Shell 排序
     * Shell 排序是简单插入排序的改进版. 它与插入排序的不同
     * 之处在于, 它会有限比较距离较远的元素. 希尔排序又叫缩
     * 小增量排序.
     *
     * 基本有序: 小的关键字基本在前面，大的基本在后面，不大不小的基本在中间，像{2,1,3,6,4,7,5,8,9}这样可以称为基本有序
     * 局部有序: 同上元素的序列, {3,5,7,1,6,9,2,4,8}, 这个排序叫做局部有序
     *
     * 简单插入排序在序列较短, 而且元素基本有序的情况下, 效率是非常高的
     *
     * Shell 排序优化简单插入排序的方法就是, 缩小待排序序列的长度, 并且将子序列合并后的序列是基本有序的
     *
     * Shell 排序的做法是: 采取跳跃分割的策略: 将相距某个“增量”的记录组成一个子序列, 这样才能保证在子序列内分别进行直接插
     *                   入排序后得到的结果是基本有序而不是局部有序.
     *                   将整个序列按照相距某个“增量”进行拆分, 然后逐个对子序列进行直接插入排序, 使得得到的结果基本有序,
     *                   最后对基本有序的序列进行一次直接插入排序, 使得整个序列有序
     */

    void shell_sort(std::vector<int>& vec){
        for(int gap = vec.size() / 2; gap > 0; gap /= 2){ //拆分整个序列，元素间距为gap(也就是增量)
            for(int i = gap; i<vec.size(); i++){ //对子序列进行直接插入排序
                for(int j = i-gap; j>=0 && vec[j]>vec[j+gap]; j-=gap){
                    swap(vec[j], vec[j+gap]);
                }
            }
        }
    }

    /*
     * 堆排序
     * 堆排序的原理是利用了堆的性质
     *
     * 堆的性质:
     * 1. 堆是一棵完全二叉树, 所以可以很轻松的用数组表示;
     * 2. 堆的子节点的值都比父节点的值大
     *
     * 用数组实现的完全二叉树的性质:
     * 1. 某一个节点对应数组的下标为 i, 其左子节点的下标为 2*i+1
     * 2. 某一个节点对应数组的下标为 i, 其右子节点的下标为 2*i+2
     *
     * 堆排序的步骤:
     * 1. 根据数组建堆
     * 2. 每次取出堆的根节点
     * 3. 剩下的数组重新建堆
     * 4. 重复步骤 1-3, 直到元素全部取完
     */
    void build_max_heap(std::vector<int>& );
    void heapify(std::vector<int>&, int, int );

    void heap_sort(std::vector<int>& vec){

        // 这里实现数组的从小到达排序, 所以建个大顶堆, 具体建大顶堆还是小顶堆根据具体实现来
        build_max_heap(vec);


        /*
         * 每次取出堆的根节点
         *
         * 这个从堆中取出根节点可以分为两步:
         * 1. 将根节点和堆中最后一个节点进行交换
         * 2. 对新的根节点执行 heapfiy 操作
         */

        for(int i=vec.size()-1; i>0; i--){
            swap(vec[0], vec[i]);
            heapify(vec, 0, i-1);
        }
    }

    // 建大顶堆
    void build_max_heap(std::vector<int>& vec){
        //初始化, i 从最后一个父节点开始调整
        for(int i=vec.size()/2-1; i>=0; i--){
            heapify(vec, i, vec.size()-1);
        }
    }

    // 针对某一节点, 保证它的堆的特性, 也可以叫做 shift_down 操作, 它沿着当前位置向下移动
    void heapify(std::vector<int>& vec, int node, int end){
        // 建堆, 同样是根据建大顶堆是来实现
        int left = node * 2 + 1;   // 左子节点
        int right = node * 2 + 2;  // 右子节点
        int largest = node;         // 初始化最大值为左子节点
        if(left <= end && vec[left] > vec[largest])
            largest = left;
        if(right<= end && vec[right] > vec[largest])
            largest = right;
        if(largest != node){
            swap(vec[largest], vec[node]);
            heapify(vec, largest, end); // shift down
        }
    }



    /****************************************************************************************
     * 非比较类排序算法: 计数排序, 桶排序, 基数排序
     * 不通过比较来决定元素间的相对次序, 它可以突破基于比较排序的时间下界, 以线性时间运行, 因此也称为
     * 线性时间非比较排序.
     ****************************************************************************************/

    /*
     * 计数排序
     * 计数排序可以
     * 把每个数出现的次数值放入标有和它一样数字的容器中, 一般采用数组作为存放这些数出现次数的容器
     *
     * 计数排序的理解:
     * 1. 当出现相同数据是不能确定之前相同元素排好后的位置关系, 所以计数排序是不稳定的排序
     * 2. 计数排序容易造成空间上的浪费, 所以计数排序只适用于元素值较为集中的情况
     * 3. 计数排序无法处理浮点数的排序
     */
    void count_sort(std::vector<int>& vec){
        if(vec.empty())
            return;

        // 找到数组的最大值和最小值
        int max = vec[0];
        int min = vec[0];
        for(auto i=vec.begin(); i!=vec.end(); i++){
            if(*i > max)
                max = *i;
            if(*i < min)
                min = *i;
        }

        if(max == min)
            return;

        // 初始化容器辅助数组
        int help[max-min+1];
        for(int i=0; i<max-min+1; i++){
            help[i] = 0;
        }

        // 填充辅助数组
        for(auto i=vec.begin(); i!=vec.end(); i++){
            help[*i-min]+=1;
        }

        // 替换原始数组
        vec.clear();
        for(int i=0; i<max-min+1; i++){
            for(int j=0; j<help[i]; j++){
                vec.push_back(i+min);
            }
        }
    }

    /*
     * 桶排序
     * 桶排序是计数排序的变种, 从计数排序到桶排序的演变思想和从数组到 Hash Table 的演变思想类似
     * 桶排序解决了计数排序只能对 int 类型序列的排序, 可以对任意类型数据进行排序, 同时桶排序还优化了计数
     * 排序的空间开销
     *
     * 桶排序的理解
     * 1. 以开链的方式实现的 HashTable 一样, 都需要桶这种结构和映射这种操作
     * 2. 桶排序的高效与否决定于这个映射函数的设计
     * 3. 桶排序是非比较类的排序, 而映射到每个桶中的数据之间的排序还是需要比较, 这如何理解呢?
     */
    void bucket_sort(std::vector<int>& vec){
        if(vec.empty())
            return;

        // 找到待排序数列中的最大
        int max = vec[0];
        for(auto i=vec.begin(); i!=vec.end(); i++){
            if(*i > max)
                max = *i;
        }

        // 初始化桶
        int vecLength = vec.size();
        std::vector<std::vector<int>> buckets(vecLength+1); // 将桶的大小设为数组的长度

        // 将vec的元素映射到相应的桶中
        // 这里的映射需要保证每个元素在桶中都一个位置可以安放它, 一定要小心数组越界的问题
        // 堆排序可以优化的地方也在此处, 设置一个好的映射关系, 可以有效的降低桶的数量
        int mapValue = max / (vecLength-1);
        for(int i=0; i<vecLength; i++){
            int bucketIndex = vec[i]/mapValue;
            int vecValue = vec[i];
            buckets[bucketIndex].push_back(vecValue);
        }

        // 对每个桶中的数据进行排序
        for(int i=0; i<buckets.size(); i++){
            std::sort(buckets[i].begin(), buckets[i].end());
        }

        // 替换原始数组
        vec.clear();
        for(int i=0; i<buckets.size(); i++){
            for(auto j=buckets[i].begin(); j!=buckets[i].end(); j++){
                int vecValue = *j;
                vec.push_back(vecValue);
            }
        }
    }

    /*
     * 基数排序
     * 将整数按位数切割成不同的数字, 然后按每个位数分别比较
     * 具体做法是: 将所有待比较数值统一为同样的数位长度, 数位较短的数前面补零. 然后, 从最低位开始, 依次进行一次排序.
     * 这样从最低位排序一直到最高位排序完成以后, 数列就变成一个有序序列.
     *
     * 基数排序是桶排序的优化, 它优化了桶排序的映射关系和桶的代销, 而且每个桶内不用做排序, 这时我们的桶的大小可以固定为 10
     */
    void buckets_sort_help(std::vector<int>&, int);
    void radix_sort(std::vector<int>& vec){
        if(vec.empty())
            return;

        // 找到待排序数列中的最大
        int max = vec[0];
        for(auto i=vec.begin(); i!=vec.end(); i++){
            if(*i > max)
                max = *i;
        }

        // 根据每个数位进行排序, exp 代表数位
        for(int exp = 1; max/exp > 0; exp *= 10){
            buckets_sort_help(vec, exp);
        }

    }
    void buckets_sort_help(std::vector<int>& vec, int exp){
        std::vector<std::vector<int>> buckets(10);

        // 根据输入的数位进行桶排序
        for(auto i=vec.begin(); i!=vec.end(); i++){
            int bucketIndex = *i/exp%10;
            int vecValue = *i;
            buckets[bucketIndex].push_back(vecValue);
        }

        // 将桶中的数据输入到 vec 中
        vec.clear();
        for(int i=0; i<buckets.size(); i++){
            for(auto j=buckets[i].begin(); j!=buckets[i].end(); j++){
                int vecValue = *j;
                vec.push_back(vecValue);
            }
        }
    }

}

#endif //SORT_MY_SORT_ALGORITHM_H
