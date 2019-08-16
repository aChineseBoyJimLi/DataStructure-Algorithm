cmake_minimum_required(VERSION 3.14)
project(DataStructure_Algorithm)

set(CMAKE_CXX_STANDARD 14)

include_directories(headers)
include_directories(headers/algorithm)
include_directories(headers/graph)
include_directories(headers/list)
include_directories(headers/tree)

add_executable(DataStructure_Algorithm
        headers/algorithm/my_sort_algorithm.h
        headers/algorithm/my_string_algorithm.h
        headers/algorithm/my_dp_algorithm.h
        headers/graph/my_graph.h
        headers/list/Hash.h
        headers/list/hash_fun.h
        headers/tree/AVLTree.h
        headers/tree/BinarySearchTree.h
        headers/tree/BinaryTree.h
        headers/tree/Heap.h
        headers/tree/HuffmanCodingTree.h
        headers/tree/RedBlackTree.h
        headers/tree/Tree_ADT.h
        headers/pch.h
        main.cpp)
