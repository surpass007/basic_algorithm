#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include "sort.h"

using namespace sort_algorithm;

template<typename T>
void PrintVector(std::vector<T>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

void LayerTranverse(std::vector<int>& vec) {
    size_t i = 0;
    int layer_count = 1;
    int total = 0;
    int space_count = 1;
    while (total < vec.size()) {
        total += layer_count;
        space_count *= 2;
        layer_count *= 2;
    }
   // cout << "space_count:" << space_count << endl;
    space_count /= 2;
    layer_count = 1;
    while (i < vec.size()) {
        int current_layer_count = layer_count;
        layer_count *= 2;
        while(i < vec.size() && current_layer_count) {
            for (int j = 0; j < space_count; j++) {
                std::cout << " ";
            }
            std::cout << vec[i];
            i++;
            current_layer_count--;
        }
       // cout << "space_count:" << space_count << endl;
        space_count /= 2;
        std::cout << std::endl;
    }
}

const int kLoop = 1000;
const int kUpperBound = 1000;
const int kNelement = 100;

void BenchMark(std::map<std::string, sort_algorithm::SortBase*>& m) {
    srand(time(0));
    std::vector<int> vec1;
    std::vector<int> vec2;
    SortBase* sb;
    vec1.resize(kNelement);
    vec2.resize(kNelement);
    for (const auto& it : m) {
        sb = it.second;
        int total_num = 0;
        int correct_num = 0;
        for (int k = 0; k < kLoop; k++) {
            for (int i = 0; i < kNelement; i++) {
                int element = rand() % kUpperBound - 500;
                vec1[i] = element;
                vec2[i] = element;
            }

            total_num++;
            std::sort(vec1.begin(), vec1.end());
            (*sb)(vec2);

            if (vec1 == vec2) {
                correct_num++;
            }
        }
        std::cout << it.first << " total_num:" << total_num << " corrent_num:" << correct_num << std::endl;
    }
}

int main() {
    HeapSort hs =  HeapSort();
    QuickSort qs =  QuickSort();
    InsertSort is =  InsertSort();
    ShellSort ss =  ShellSort();
    MergeSort ms =  MergeSort();
    BucketSort bs =  BucketSort();
    CountSort cs = CountSort();
    RadixSort rs = RadixSort();

    std::map<std::string, sort_algorithm::SortBase*> m = {
        {
            "heap_sort",
            &hs
        },
        {
            "quic_sort",
            &qs
        },
        {
            "insert_sort",
            &is
        },
        {
            "shell_sort",
            &ss
        },
        {
            "merge_sort",
            &ms
        },
        {
            "bucket_sort",
            &bs
        },
        {
            "count_sort",
            &cs
        },
        {
            "radix_sort",
            &rs
        }
    };

    BenchMark(m);
    return 0;
}