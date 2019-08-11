//
// Created by jim on 19-8-1.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <vector>
#include <queue>
#include <iostream>
#include <set>
#include <list>
#include <unordered_set>
#include <algorithm>

#define INFINITE 1000

/*
 * 图是一个用线或边连接在一起的顶点或节点的集合, 严格说, 图
 * 是有限集 V 和 E 的有序对, 即 G=(V, E), 其中 V 的元素称
 * 为顶点, E 的元素称为边. 每一条边连接两个不同的定点
 *
 * 按有无方向图分两种:
 * 1. 有向图
 * 2. 无向图
 *
 * 按有无权值图分两种:
 * 1. 有权图
 * 2. 无权图
 *
 * 图的两种表示方式:
 * 1. 邻接矩阵的形式
 * 2. 邻接表的形式
 *
 * 图的算法:
 *  遍历算法:
 *      1. 深度优先遍历
 *      2. 广度优先遍历
 *  路径算法:
 *      1. Dijiskra 算法
 *      2. Floyd 算法
 *      3. A* 算法
 *  最小生成树算法
 *      1. Kruskal 算法
 *      2. Prime 算法
 *  拓扑排序算法
 */


/*
 *      E---A---B---D
 *       \  | \/
 *        \ | /\
 *          C   F
 *
 */

namespace mg{

    template<typename vertexType>
    struct CGraph_Matrix{

        std::vector<vertexType> vertexes;       // 顶点集
        std::vector<std::vector<int>> matrix;   // 邻接矩阵
        size_t size;                            // 顶点数

        CGraph_Matrix():size(0){}

        // 返回某一节点第一个邻接节点的下标
        int begin(int ver)
        {
            for(int i=0; i<size; i++){
                if(matrix[ver][i] != INFINITE)
                    return i;
            }
            return -1;
        }

        // 下一个邻接节点的下标
        int next(int ver, int n){
            if(n > size)
                return -1; // 没有下一个邻接点
            for(int i=n+1; i<size; i++){
                if(matrix[ver][i] != INFINITE)
                    return i;
            }
            return -1;
        }
    };


    // 广度优先遍历, 默认从第一个顶点开始遍历
    /*
     * 广度优先遍历和树的层级遍历本质是一样的, 因为树也是一种特殊的图, 广度优先遍历用一个
     * 队列存储已经遍历了的元素, 并用一个数组记录某一节点是否已经遍历
     */
    template<typename vertexType>
    void BFS(CGraph_Matrix<vertexType> graph){
        if(graph.size <= 0)
            return;

        std::queue<int> vertex_queue; // 顶点遍历队列, 存储的是顶点在图中顶点集的下标
        std::vector<bool> hasVisit;   // 存储某个顶点是否被访问过
        for(int i=0; i<graph.size; i++)
            hasVisit.push_back(false);

        // 访问第一个节点
        vertex_queue.push(0);
        hasVisit[0] = true;

        while(!vertex_queue.empty()){
            int curr_vertex = vertex_queue.front();
            int i = graph.begin(curr_vertex);
            while(i!=-1){
                if(!hasVisit[i]){
                    vertex_queue.push(i);
                    hasVisit[i] = true;
                    i = graph.next(curr_vertex, i);
                }
                else{
                    i = graph.next(curr_vertex, i);
                }
            }
            std::cout << graph.vertexes[curr_vertex] << std::endl;
            vertex_queue.pop();
        }
    }


    // 深度优先遍历, 默认从第一个顶点开始遍历
    /*
     * 深度优先遍历和树的前序遍历本质是一样的, 因为树也是一种特殊的图, 广度优先遍历用递归实现,
     * 同样用一个数组存储某一个节点是否已经遍历
     */
    template<typename vertexType>
    void DFSHelp(CGraph_Matrix<vertexType> graph, std::vector<bool>& hasVisit, int ver){
        std::cout << graph.vertexes[ver] << std::endl;
        hasVisit[ver] = true;
        int i = graph.begin(ver);
        while(i!=-1){
            if(!hasVisit[i]){
                DFSHelp(graph, hasVisit, i);
                i = graph.next(ver, i);
            }
            else
                i = graph.next(ver, i);
        }
    }

    template<typename vertexType>
    void DFS(CGraph_Matrix<vertexType> graph){
        if(graph.size <= 0)
            return;

        std::vector<bool> hasVisit;   // 存储某个顶点是否被访问过
        for(int i=0; i<graph.size; i++){
            hasVisit.push_back(false);
        }

        DFSHelp(graph, hasVisit, 0);
    }


    // Dijiskra 算法
    /*
     * Dijkstra(迪杰斯特拉)算法是典型的单源最短路径算法, 用于计算一个节点到其他所有节点的最短路径.
     * 主要特点是以起始点为中心向外层层扩展, 直到扩展到终点为止. Dijkstra算法是很有代表性的最短路
     * 径算法.
     *
     * Dijiskra 是动态规划思想的典型案例
     * 从一个点出发, 找到与该点联通的所有点的最短路径.
     * 我们把问题细分,
     */
    template<typename vertexType>
    void Dijiskra(CGraph_Matrix<vertexType> graph, int vertex){
        int dist[graph.size];   // 存储最短路径的集合
        bool s[graph.size];     // 判断某一点是否已加入最短路径集

        // 初始化
        for(int i=0; i<graph.size; i++){
            dist[i] = graph.matrix[vertex][i];
            s[i] = false;
        }
        // 将该点设置到最短路径集当中
        dist[vertex] = 0;
        s[vertex] = true;


        for(int i=0; i<graph.size; i++ ){
            int MIN = INFINITE;
            int flag = vertex;

            // 找到邻接点中距离最短的路径
            for(int j=0; j<graph.size; j++){
                if(!s[j] && dist[j]>0 && dist[j]<MIN  ){
                    flag = j;  // 保存当前邻接点中距离最小的点的号码
                    MIN = dist[j]; // 从当前邻接点中找到最近的距离
                }
            }
            s[flag] = true;

            // 找到经过最近邻接点所能达到的最短路径
            for(int j=0; j<graph.size; j++){
                if(graph.matrix[flag][j] > 0 && dist[flag] + graph.matrix[flag][j] < dist[j]  ){
                    dist[j] = dist[flag] + graph.matrix[flag][j];
                }
            }
        }

        // 打印最短路径
        for(int i=0; i<graph.size; i++){
            std::cout << dist[i] << "\t";
        }

        std::cout << std::endl;

    }


    /*
     * Floyd 算法
     * Floyd-Warshall算法（Floyd-Warshall algorithm）是解决任意两点间的最短路径的一种算法,
     * 可以正确处理有向图或负权的最短路径问题, 同时也被用于计算有向图的传递闭包. Floyd-Warshall
     * 算法的时间复杂度为O(N^3), 空间复杂度为O(N^2), 注意 Floyd 算法不适用于有环图
     *
     * Floyd 算法是动态规划思想的典型运用
     * 我们自顶向下的分析, 从任意节点 A 到任意节点 B 的最短路径不外乎2 种可能, 1 是直接从 A 到 B,
     * 2 是从 A 经过若干个节点 X 到 B. 所以, 我们假设 dist(AB) 为节点 A 到 B 的最短路径的距离,
     * 对于每一个节点 X, 我们检查 dist(AX) + dist(XB) < dist(AB) 是否成立, 如果成立, 证明从 A
     * 到 X 再到 B 的路径比 A 直接到 B 的路径短, 我们便设置 dist(AB) = dist(AX) + dist(XB),
     * 这样依赖, 当我们遍历完所有节点 X, dist(AB) 中记录的便是 A 到 B 的最短路径的距离
     *
     * 自底向上编码, 首先任意两点间的最短路径可以初始化为原图的矩阵
     *
     */
    template<typename vertexType>
    void Floyd(CGraph_Matrix<vertexType> graph){

        // 初始化最短路径矩阵
        int dist[graph.size][graph.size];
        for(int i=0; i<graph.size; i++){
            for(int j=0; j<graph.size; j++){
                dist[i][j] = graph.matrix[i][j];
            }
        }

        // 寻找最短路径
        // 这里中转节点 k 写在最外层循环是为了避免有环图所引发的错误
        for(int k=0; k<graph.size; k++){ // 表示中转节点 k
            for(int i=0; i<graph.size; i++){ // 所有从 i 到 k 距离最短的路径
                for(int j=0; j<graph.size; j++){ // 所有从 k 到 j 最短的路径
                    if(dist[i][k] + dist[k][j] < dist[i][j]){ // 如果经过 k, ij更短, 更新 ij 的最短距离
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        // 打印最短路径
        for(int i=0; i<graph.size; i++){
            for(int j=0; j<graph.size; j++){
                std::cout << dist[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }

    /*
     * 最小生成树
     * 一个简单的模型, 在一块木板上钉上一些钉子并用一些细绳连接起来, 假设每一个钉子都经由一根或多根细绳连接起来.
     * 现在我们一根一根拿走细绳, 直到用最少的细绳将所有钉子连接起来. 这个模型的背后思想就是最小生成树.
     *
     * 正式的表述法是，给定一个无方向的带权图G=(V，E), 最小生成树为集合T, T是以最小代价连接V中所有顶点所用边E
     * 的最小集合, 即所有边的权值之和最小. 集合T中的边能形成一颗树, 这是因为每个顶点都能向上找到它的一个父节点
     * (根结点除外)
     */

    /*
     * Prime 算法
     * Prim算法是一种产生最小生成树的方法, 它运用了贪心的思想, 而贪心算法成立需要证明, 证明在后面给出
     * Prim算法从任意一个顶点开始, 每次选择一个与当前顶点最近的一个顶点, 并将两个顶点之间的边加入到树中.
     *
     * Prime 算法证明:
     *
     */
    template<typename vertexType>
    void Prime(CGraph_Matrix<vertexType> graph){

        // 用一个与输入图一样大小的二维矩阵表示输出的最小支撑树
        int tree[graph.size][graph.size];
//        for(int i=0; i<graph.size; i++){
//            for(int j=0; j<graph.size; j++){
//                if(i==j){
//                    tree[i][j] = 0;
//                    continue;
//                }
//                tree[i][j] = INFINITE;
//            }
//        }
        int sum = 0;

        // 顶点的访问情况, visit 对应的下标对应图的顶点集的下表, visit 中的 bool 值判断该顶点是否访问过
        std::vector<bool> visit;
        for(int i=0; i<graph.size; i++){ // 初始化 visit
            visit.push_back(false);
        }

        int dist[graph.size]; // 存储 curr 顶点的所有邻接点的距离

        // 默认从第一个顶点开始计算最小支撑树, 初始顶点的选择并不影响最终的结果
        int curr = 0;
        visit[curr] = true;

        // 初始化 dist
        for(int i=0; i<graph.size; i++)
            dist[i] = graph.matrix[curr][i];

        // 遍历表中的每一个节点
        for(int i=1; i<graph.size; i++){
            int min = INFINITE;
            for(int j=1; j<graph.size; j++){
                if(!visit[j] && dist[j] < min){
                    min = dist[j];
                    curr = j;
                }
            }
            sum += min;
            visit[curr] = true;

            // 从当前顶点开始搜寻到下一个代价最小的顶点, 更新 dist 数组
            for(int j=1; j<graph.size; j++){
                if(!visit[j] && dist[j] > graph.matrix[curr][j]){
                    dist[j] = graph.matrix[curr][j];
                }
            }
        }
        std::cout << "最小支撑树的代价为: " << sum << std::endl;
    }


    /*
     * Kruskal 算法
     * Kruskal 算法是一种求加权连通图的最小生成树的算法, 基本思路是按照权值从小到大的顺序选择n-1条边，并保证这n-1条边不构成回路
     * 具体做法是: 首先构造一个只含n个顶点的森林，然后依权值从小到大从连通网中选择边加入到森林中，并使森林中不产生回路，直至森林变成一棵树为止
     *
     * Kruskal 算法同样运用了贪心的思想, 证明在下面给出
     *
     * 算法步骤：
     * 1.新建图G，G中拥有原图中相同的节点，但没有边；
     * 2.将原图中所有的边按权值从小到大排序；
     * 3.从权值最小的边开始，如果这条边连接的两个节点于图G中不在同一个连通分量中，则添加这条边到图G中；
     * 4.重复3，直至图G中所有的节点都在同一个连通分量中
     *
     * Kruskal 算法证明:
     * 这样的步骤保证了选取的每条边都是桥，因此图G构成一个树;
     *
     * 为什么这一定是最小生成树呢？关键还是步骤3中对边的选取。算法中总共选取了n-1条边，每条边在选取的当时，都是连接两个不同的连通分量的权值最小
     * 的边;
     *
     * 要证明这条边一定属于最小生成树，可以用反证法：如果这条边不在最小生成树中，它连接的两个连通分量最终还是要连起来的，通过其他的连法，那么另
     * 一种连法与这条边一定构成了环，而环中一定有一条权值大于这条边的边，用这条边将其替换掉，图仍旧保持连通，但总权值减小了。也就是说，如果不选取
     * 这条边，最后构成的生成树的总权值一定不会是最小的
     */
    template<typename vertexType>
    void Kruskal(CGraph_Matrix<vertexType> graph){
        
    }


    /*
     * A* 算法
     * A* 算法是一种求解静态网格图最短路径最有效的直接搜索方法.
     *
     * 在运用 A* 算法解决问题时, 我们把搜寻的区域划分成网格, 简化搜索区域
     *
     * A* 算法相对于广度优先搜索算法, 除了考虑中间某个点同出发点的距离外, 还考虑这个点同目标点的距离,
     * 这就是 A* 算法比广度优先算法智能的地方, 也就是所谓的启发式搜索.
     *
     * 从起点 S 到终点 E 的距离, 可以表示为两段距离之和, 即 dist(SM) + dist(ME), 可以写成: f(M)=
     * g(M)+h(M)
     *
     * 我们扩展到 M 点的时候, S->M 的距离就已经知道, 所以 g(M) 是已知的. 但是 M 到 E 的距离我们还不知
     * 道. 但是 M 到 E 的距离我们还不知道. 如果我们能用某种公式, 能大概预测一下这个距离, 而这个预测的值
     * 又比较精确, 我们是不是就能很精确的知道每一个即将扩展的点是否是最优的解路径上的点
     *
     * 所以, 关键问题, 就是如何计算这个 h(M) 的值.
     *
     * 在估计 h(M) 的时候有两个问题要去解决:
     * 1. 这个估算函数 h(M) 怎么样去计算
     * 2. 对于不同的估算函数 h(M) 来讲, 对于我们的搜索结果会有什么样的影响
     *
     * 这个估算函数 h(M) 怎么样去计算?
     * 常见的距离计算公式有这么几种:
     * 1. 曼哈顿距离: 其实就是 横向格子数 + 纵向格子数
     * 2. 欧式距离: 其实就是两点间的直线距离 sqrt((x1-x2)^2 + (y1-y2)^2)
     *
     * 不同估算函数对结果的影响?
     * 1. 当估算的距离 h 完全等于实际距离 h(M) 时, 也就是每次扩展的那个点我们都准确的知道, 如果选他以后,
     * 我们的路径距离是多少, 这样我们就不用乱选了, 每次都选最小的那个, 一路下去, 肯定就是最优解的解, 而且
     * 基本不用扩展其他的点
     * 2. 如果估算距离 h 小于实际距离 h(M) 时, 我们到最后一定能找到一条最短路径(如果存在另外一条更短的评
     * 估路径, 就会选择更小的那个), 但是有可能会经过很多无效的点. 极端情况下, 当 h==0的时候, 最终的距离函
     * 数就变成: f(M) = g(M) + h(M) -> f(M) = g(M) + 0 -> f(M) = g(M), 这就会退化为广度优先遍历, 因
     * 为它只考虑和起始点的距离关系, 毫无启发可言
     * 3. 如果估算距离 h 大于实际距离 h(M) 时, 有可能很快找到一条通往目的地的路径, 但是却不一定是最优的解
     *
     * 因此, A* 算法最后留给我们的, 就是在时间和距离上需要考虑的一个平衡. 如果要求最短路径, 则一定选择 h 小
     * 于等于实际距离; 如果不一定求最优解, 而是要速度快, 则可以选择 h 大于等于实际距离
     */

    /*
     * A* 算法的实现
     * 实现 A* 算法需要引入一个公式和两个集合
     * 公式: F = G + H
     *       G 代表从起点走到当前格子的成本, 也就是走了多少步
     *       H 代表不考虑障碍的情况下, 从当前格子到目标距离还有多远
     *
     * 集合: openList 存储可达的格子集合
     *       closeList 存储已达格子集合
     *
     * round 1
     * 第一步: 把起点放入 openList
     * 第二步: 找出 openList 中 F 值最小的方格, 即唯一的方格起点作为当前节点, 并把当前格移出 openList, 放入
     *        closeList. 代表这个格子已达并检查过了
     * 第三步: 找出当前格上下左右所有可达的格子, 看它们是否在 openList 中. 如果不在, 加入 openList, 计算出相
     *        应的 G, H, F 值, 并把当前格子作为它们的父亲节点
     *
     * round 2
     * 第一步: 找出 openList 中 F 值最小的方格, 设为当前方格, 并把它移出 openList, 放入 clostList
     *
     */

    // 针对 A* 算法设计的网格节点的数据结构结构
    struct GridNode{
        int i; // 在网格中的 i 坐标
        int j; // 在网格中的 j 坐标
        int f;
        int g;
        int h;
        GridNode* parent;
    };

    // 用于简化搜索区的网格
    const int MAXLENGTH = 15; // 建立一个 15*15 的正方形网格搜索区
    class Grid{
    private:
        GridNode _grid[MAXLENGTH][MAXLENGTH]; // 网格搜索区
        int origin[2];          // 起点
        int destination[2];     // 终点
        std::unordered_set<GridNode*> obstacles; // 障碍区

    private:
        bool findHelp(std::list<GridNode*> list, GridNode* node);   // 在 list 中是否存在某一点, 有就返回true, 没有返回false
        int distHelp(int iBegin, int jBegin, int iEnd, int jEnd);   // 曼哈顿距离公式
        GridNode* findMinusF(std::list<GridNode*> list);            // 找到 F 最小的节点
        bool IsObstacle(int i, int j);                              // 判断某一点是否是障碍, 如果是返回 true, 如果不是返回 false
        void calculateHelp(GridNode* pNode);                        // 计算 f, g, h 的值

    public:
        Grid();
        void SetObstacles(int i, int j);    // 设置障碍
        void SetOrigin(int i, int j);       // 设置起点
        void SetDestination(int i, int j);  // 设置终点
        void AStar();                       // A* 算法寻找最短路径
    };

    // 在 list 中是否存在某一点, 有就返回true, 没有返回false
    bool Grid::findHelp(std::list<GridNode*> list, GridNode* node){
        return std::find(list.begin(), list.end(), node) != list.end();
    }

    // 曼哈顿距离公式
    int Grid::distHelp(int iBegin, int jBegin, int iEnd, int jEnd){
        return abs(iBegin - iEnd) + abs(jBegin-jEnd);
    }

    // 找到 F 最小的节点
    GridNode* Grid::findMinusF(std::list<GridNode*> list){
        auto minNode = list.begin();
        for(auto i = list.begin(); i!=list.end(); i++){
            if((*i)->f < (*minNode)->f){
                minNode = i;
            }
        }
        return *minNode;
    }

    // 判断某一点是否是障碍, 如果是返回 true, 如果不是返回 false
    bool Grid::IsObstacle(int i, int j){
        return obstacles.find(&_grid[i][j]) != obstacles.end();
    }

    // 默认构造函数
    Grid::Grid(){
        // 初始化起点和终点
        for(int i=0; i<2 ;i++){
            origin[i] = 0;
            destination[i] = 0;
        }

        // 初始化网格
        for(int i=0; i<MAXLENGTH; i++){
            for(int j=0; j<MAXLENGTH; j++){
                _grid[i][j].i = i;
                _grid[i][j].j = j;
                _grid[i][j].g = 0;
                _grid[i][j].h = 0;
                _grid[i][j].f = 0;
                _grid[i][j].parent = nullptr;
            }
        }
    }

    // 设置障碍
    void Grid::SetObstacles(int i, int j){
        obstacles.insert(&_grid[i][j]);
    }

    // 设置起点
    void Grid::SetOrigin(int i, int j){
        origin[0] = i;
        origin[1] = j;
    }

    // 设置终点
    void Grid::SetDestination(int i, int j){
        destination[0] = i;
        destination[1] = j;
    }

    // 辅助计算 f, g, h
    void Grid::calculateHelp(GridNode* pNode){
        if(pNode->parent == nullptr){
            pNode->g = 0;
        }
        else{
            pNode->g = pNode->parent->g + 1;
        }
        pNode->h = distHelp(pNode->i, pNode->j, destination[0], destination[1]);
        pNode->f = pNode->g + pNode->h;
    }

    // A* 算法寻找最短路径
    void Grid::AStar(){
        std::list<GridNode*> openList;
        std::list<GridNode*> closeList;
        GridNode* currNode = nullptr; // 表示当前节点

        // 计算起点的g, h, f
        calculateHelp(&_grid[origin[0]][origin[1]]);
        openList.push_back(&_grid[origin[0]][origin[1]]);

        while(!openList.empty()){
            if(!findHelp(openList, &_grid[destination[0]][destination[1]])){
                currNode = findMinusF(openList); // 找到 f 值最小的节点
                int tmp_i = currNode->i, tmp_j = currNode-> j;

                openList.erase(std::find(openList.begin(), openList.end(), currNode));  // 从 openList 中移出当前节点
                closeList.push_back(currNode);  // 加入 closeList

                // 判断 currNode 上面的一个节点是不是可以加入 openList
                // 所选的新节点不能超过网格范围, 不是障碍节点, 不在 openList 中, 不在 closeList 中
                if( tmp_i<MAXLENGTH && tmp_j+1<MAXLENGTH && !IsObstacle(tmp_i, tmp_j+1)
                    && !findHelp(closeList, &_grid[tmp_i][tmp_j+1])
                    && !findHelp(openList, &_grid[tmp_i][tmp_j+1]))
                {
                    _grid[tmp_i][tmp_j+1].parent = currNode;    // 设置加入openList的父节点
                    calculateHelp(&_grid[tmp_i][tmp_j+1]);      // 计算该节点的 f, g, h
                    openList.push_back(&_grid[tmp_i][tmp_j+1]); // 将该节点加入 openList
                }
                // 判断 currNode 下面一个节点是不是可以加入 openList
                if( tmp_i<MAXLENGTH && tmp_j-1<MAXLENGTH && !IsObstacle(tmp_i, tmp_j-1)
                    && !findHelp(closeList, &_grid[tmp_i][tmp_j-1])
                    && !findHelp(openList, &_grid[tmp_i][tmp_j-1]))
                {
                    _grid[tmp_i][tmp_j-1].parent = currNode;
                    calculateHelp(&_grid[tmp_i][tmp_j-1]);
                    openList.push_back(&_grid[tmp_i][tmp_j-1]);
                }
                // 判断 currNode 左面一个节点是不是可以加入 openList
                if( tmp_i-1<MAXLENGTH && tmp_j<MAXLENGTH && !IsObstacle(tmp_i-1, tmp_j)
                    && !findHelp(closeList, &_grid[tmp_i-1][tmp_j])
                    && !findHelp(openList, &_grid[tmp_i-1][tmp_j]))
                {
                    _grid[tmp_i-1][tmp_j].parent = currNode;
                    calculateHelp(&_grid[tmp_i-1][tmp_j]);
                    openList.push_back(&_grid[tmp_i-1][tmp_j]);
                }
                // 判断 currNode 右面一个节点是不是可以加入 openList
                if( tmp_i+1<MAXLENGTH && tmp_j<MAXLENGTH && !IsObstacle(tmp_i+1, tmp_j)
                    && !findHelp(closeList, &_grid[tmp_i+1][tmp_j])
                    && !findHelp(openList, &_grid[tmp_i+1][tmp_j]))
                {
                    _grid[tmp_i+1][tmp_j].parent = currNode;
                    calculateHelp(&_grid[tmp_i+1][tmp_j]);
                    openList.push_back(&_grid[tmp_i+1][tmp_j]);
                }

            }
            else{
                // 打印最短路径
                currNode = &_grid[destination[0]][destination[1]];
                while(currNode->parent != nullptr){
                    std::cout << currNode->i << ":" << currNode->j << std::endl;
                    currNode = currNode->parent;
                }
                std::cout << currNode->i << ":" << currNode->j << std::endl; // 打印起点
                return;
            }


        }

        std::cout << "没有找到最短路径" << std::endl;
        return;
    }



}



#endif //GRAPH_GRAPH_H
