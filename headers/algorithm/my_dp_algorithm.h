//
// Created by jim on 19-8-11.
//

#ifndef DATASTRUCTURE_ALGORITHM_MY_DP_ALGORITHM_H
#define DATASTRUCTURE_ALGORITHM_MY_DP_ALGORITHM_H

#include <unordered_map>

// 动态规划问题总结
/*
 * 动态规划问题包含三个重要概念
 * 1. 最优子结构:
 * 2. 边界: 如果一个问题没有边界, 将永远无法得到结果
 * 3. 状态转移公式: 动态规划的核心, 决定了问题的每个阶段和下一个阶段的关系
 *
 * 动态规划的优化
 * 1. 在分解动态规划问题后, 产生的子结构可能会被重复计算, 所以可以创建一个 HashMap 存储计算过的子结构, 这种算法叫备忘录算法
 * 2. 自顶向下的动态规划问题可以通过递归实现, 但空间复杂度较大, 所以可以通过自底向上的方式, 通过迭代方式实现动态规划, 减小空间复杂度
 *
 * 动态规划的特点
 * 特点一: 在应用动态规划之前要分析能否把大问题分解成小问题, 分解后的每个小问题也存在最优解. 如果把小问题的最优解组合起来能够得到整个问题的最优解,
 *        那么我们可以应用动态规划解决这个问题
 * 特点二: 我们想要得到整个问题的最优解 f(n), 那么要同样用最优化的方法得到子问题 f(i) 和 f(n-i) 的最优解. 也就是说整体问题的最优解是依赖各个子问
 *        题的最优解
 * 特点三: 我们把大问题分解成若干个小问题, 这些小问题之间还有相互重叠的更小的子问题
 * 特点四: 由于子问题在分解大问题的过程中重复出现, 为了避免重复求解子问题, 我们可以用从下往上的顺序计算小问题的最优解并存储下来, 再以此为基础求取大
 *        问题的最优解. 从上往下分析问题, 从下往上求解问题
 */

namespace dp{
    /*
     * 台阶问题
     * 有一座高度是 N 级台阶的楼梯，从下往上走，每跨一步只能向上1级或者2级台阶。要求用程序来求出一共有多少种走法。
     *
     * 最优子结构: F(N), F(N-1), F(N-2)
     * 边界: F(1)=1, F(2)=2
     * 状态转移公式: F(N) = F(N-1) + F(N-2)
     *
     * 注: 此题比较特殊, 最后的结果是个斐波拉契数列
     */

    // 简单递归, 自顶向下, 时间复杂度 O(2^N), 空间复杂度 O(2^N)
    int StepProblemRecursive(int N){
        if(N < 1)
            return 0;
        if(N == 1)
            return 1;
        if(N == 2)
            return 2;
        return StepProblemRecursive(N-1) + StepProblemRecursive(N-2);
    }

    // 备忘录算法, 自顶向下, 时间复杂度 O(n), 空间复杂度 O(n)
    int StepProblemMemo(int N, std::unordered_map<int, int>& hashMap){
        if(N < 1)
            return 0;
        if(N == 1)
            return 1;
        if(N == 2)
            return 2;
        if(hashMap.find(N) != hashMap.end()){
            return hashMap[N];
        }
        else{
            int steps = StepProblemMemo(N-1, hashMap) + StepProblemMemo(N-2, hashMap);
            hashMap[N] = steps;
            return steps;
        }
    }

    // 动态规划, 循环实现, 自底向上, 时间复杂度 O(n), 空间复杂度 O(1)
    int StepProblemLoop(int N){
        if(N < 1)
            return 0;
        if(N == 1)
            return 1;
        if(N == 2)
            return 2;

        int a = 1;
        int b = 2;
        int temp = 0;
        for(int i = 3; i<=N; ++i){
            temp = a + b;
            a = b;
            b = temp;
        }

        return temp;
    }

    /*
     * 剪绳子
     * 给你一根长度为 n 的绳子, 请把绳子剪成 m 段(m n 都是整数, n>1 并且 m>1), 每段绳子的长度记为 k[0], k[1], ... k[m].
     * 请问 k[0]*k[1]* ... * k[m], 可能的最大乘积是多少? 例如, 当绳子的长度是 8 时, 我们把它剪成长度分别为 2, 3, 3 的三
     * 段, 此时得到的最大乘积是 18
     *
     * 最优子结构:
     * 边界: f(2) = 1, f(3) = 2 ( 其中, k[1] = 1, k[2] = 2, k[3] = 3)
     * 状态转移公式: f(m) = max(f(i) * f(m-i)), 0 < i <= n/2 + 1
     */
    // 简单递归, 自顶向下, 时间复杂度 O(n^2)
    int CutRopeProblemRecursive(int N){
        if(N < 1)
            return 0;

        if(N==1)
            return 1;

        if(N == 2)
            return 2;

        if(N==3)
            return 3;

        int max = 0;
        for(int i=1; i <= N/2; ++i){
            int temp = CutRopeProblemRecursive(i)*CutRopeProblemRecursive(N-i);
            if( temp > max){
                max = temp;
            }
        }
        return max;
    }

    // 动态规划, 自底向上
    int CutRopeProblemLoop(int N){
        if(N < 2)
            return 0;
        if(N == 2)
            return 1;
        if(N == 3)
            return 2;

        std::vector<int> k(N+1);
        k[0] = 0;
        k[1] = 1;
        k[2] = 2;
        k[3] = 3;

        int max = 0;

        for(int j=4; j<N; ++j){
            for(int i=1; i<N/2; ++i){
                int temp = k[j]*k[j-i];
                if(temp > max)
                    max = temp;
            }
            k[j] = max;
        }
        return  k[N];
    }


    /*
     * 背包问题
     * 在 N 件物品取出若干件放在容量为W的背包里, 每件物品的体积为W1, W2……Wn(Wi为整数), 与之相对应的价值为P1,P2……Pn(Pi为整数),
     * 求背包能够容纳的最大价值
     *
     *
     */
}

#endif //DATASTRUCTURE_ALGORITHM_MY_DP_ALGORITHM_H
