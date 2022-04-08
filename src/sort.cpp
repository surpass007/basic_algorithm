#include <vector>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <assert.h>
#include <algorithm>
#include <memory>
#include <assert.h>
#include <math.h>
#include <queue>
#include "sort.h"

using namespace sort_algorithm;

void QuickSort::operator()(std::vector<int>& vec, int left, int right) {
    if (left >= right) {
        return;
    }
    int medium = Partition(vec, left, right);
    (*this)(vec, left, medium - 1);
    (*this)(vec, medium + 1, right);
}


int QuickSort::Partition(std::vector<int>& vec, int left, int right) {
    int current_index = left - 1;
    int pivot = vec[right];
    while(left < right) {
        if (vec[left] <= pivot) {
            ++current_index;
            int temp = vec[left];
            vec[left] = vec[current_index];
            vec[current_index] = temp;
        }
        left++;
    }
    int temp = vec[current_index + 1];
    vec[current_index + 1] = vec[right];
    vec[right] = temp;
    return current_index + 1;
}

void QuickSort::operator()(std::vector<int>& vec) {
    (*this)(vec, 0, vec.size() - 1);
}

void HeapSort::operator()(std::vector<int>& vec) {
    BuildHeap(vec);
    int current_size = vec.size();
    while (current_size > 0) {
        int last_node_index = current_size - 1;
        int temp = vec[0];
        vec[0] = vec[last_node_index];
        vec[last_node_index] = temp;
        current_size--;
        Heapify(vec, 0, current_size);
    }
}

void HeapSort::Heapify(std::vector<int>& vec, int root_index, int current_size) {
    int max_index = root_index;
    while (root_index < current_size) {
        int left_index = root_index * 2 + 1;
        int right_index = root_index * 2 + 2;
        if (left_index < current_size && vec[left_index] > vec[max_index]) {
            max_index = left_index;
        }
        if (right_index < current_size && vec[right_index] > vec[max_index]) {
            max_index = right_index;
        }
        if (root_index != max_index) {
            int temp = vec[max_index];
            vec[max_index] = vec[root_index];
            vec[root_index] = temp;
            root_index = max_index;
        } else {
            return;
        }
    }
    return;
}

void HeapSort::BuildHeap(std::vector<int>& vec) {
    current_size_ = vec.size();
    int last_leaf_node_index = vec.size() - 1;
    int last_non_leaf_node_index = (last_leaf_node_index - 1) / 2;
    for (int i = last_non_leaf_node_index; i >= 0; i--) {
        Heapify(vec, i, vec.size());
    }
}

int HeapSort::GetLeftChild(int index) {
    int left_index = index * 2 + 1;
    return left_index < current_size_ ? left_index : -1;
}

int HeapSort::GetRightChild(int index) {
    int right_index = index * 2 + 1;
    return right_index < current_size_ ? right_index : -1;
}

void ShellSort::operator()(std::vector<int>& vec) {
    int j;
    for (int step = vec.size() / 2; step > 0; step /= 2) {
        for (int i = step; i < vec.size(); i++) {
            int temp = vec[i];
            for (j = i - step; j >= 0; j -= step) {
                if (vec[j] <= temp) {
                    break;
                }
                vec[j + step] = vec[j];
            }
            vec[j + step] = temp;
        }
    }
}

void InsertSort::operator()(std::vector<int>& vec) {
    int nvec = vec.size();
    int i, j;
    for (i = 1; i < nvec; i++) {
        int temp = vec[i];
        for (j = i - 1; j >= 0; j--) {
            if (vec[j] <= temp) {
                break;
            }
            vec[j + 1] = vec[j]; 
        }
        vec[j + 1] = temp;
    }
}

void MergeSort::Merge(std::vector<int>& vec, int left, int mid, int right) {
    int nsize = right - left + 1;
    std::vector<int> temp(nsize, 0);
    int left_index = left;
    int right_index = mid + 1;
    int current_index = 0;
    while(left_index <= mid && right_index <= right) {
        if (vec[left_index] <= vec[right_index]) {
            temp[current_index++] = vec[left_index++];
        } else {
            temp[current_index++] = vec[right_index++];
        }
    }
    while(left_index <= mid) {
        temp[current_index++] = vec[left_index++];
    }
    while(right_index <= right) {
        temp[current_index++] = vec[right_index++];
    }

    for (int i = 0; i < nsize; i++) {
        vec[left + i] = temp[i];
    }
}

void MergeSort::MergeAndSort(std::vector<int>& vec, int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    MergeAndSort(vec, left, mid);
    MergeAndSort(vec, mid + 1, right);
    Merge(vec, left, mid, right);
}

void MergeSort::operator()(std::vector<int>& vec) {
    MergeAndSort(vec, 0, vec.size() - 1);
}

void BucketSort::operator()(std::vector<int>& vec) {
    int nsize = vec.size();
    if (!nsize) {
        return;
    }
    int max_value = *max_element(vec.begin(), vec.end());
    int min_value = *min_element(vec.begin(), vec.end());
    int unit = ceil(double(max_value - min_value) / (double)nsize);
    if (!unit) { // all values are equal
        return;
    }
    std::vector<int> buckets[nsize + 1];
    for (int i = 0; i < nsize; i++) {
        int bucket_index = (vec[i] - min_value) / unit;
        assert(bucket_index >= 0 && bucket_index <= nsize);
        buckets[bucket_index].push_back(vec[i]);
    }

    for (int i = 0; i <= nsize; i++) {
        std::sort(buckets[i].begin(), buckets[i].end());
    }

    int current_index = 0;
    for (int i = 0; i <= nsize; i++) {
        for (int j = 0; j < buckets[i].size(); j++) {
            vec[current_index++] = buckets[i][j];
        }
    }
}

void CountSort::operator()(std::vector<int>& vec) {
    int nsize = vec.size();
    if (!nsize) {
        return;
    }
    int max_value = *max_element(vec.begin(), vec.end());
    int min_value = *min_element(vec.begin(), vec.end());
    int shift = min_value;
    std::vector<int> count(max_value - shift + 1, 0);
    for (int i = 0; i < nsize; i++) {
        count[vec[i] - shift]++;
    }

    for (int i = 1; i < count.size(); i++) {
        count[i] += count[i - 1];
    }

    std::vector<int> temp(nsize, 0);
    for (int i = 0; i < nsize; i++) {
        int last_index_of_current = count[vec[i] - shift] - 1;
        temp[last_index_of_current] = vec[i];
        count[vec[i] - shift]--;
    }

    for(int i = 0; i < nsize; i++) {
        vec[i] = temp[i];
    }
}

void RadixSort::CountSort(std::vector<int>& vec, int base) {
    int nsize = vec.size();
    if (!nsize) {
        return;
    }

    int shift = *min_element(vec.begin(), vec.end());

    std::vector<int> count(10, 0);
    for (int i = 0; i < nsize; i++) {
        int digit = ((vec[i] - shift) / base) % 10;
        count[digit]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    std::vector<int> temp(nsize, 0);
    for (int i = nsize - 1; i >= 0; i--) {
        int digit = ((vec[i] - shift) / base) % 10;
        int last_index_of_current = count[digit] - 1;
        assert(last_index_of_current >= 0 && last_index_of_current < nsize);
        temp[last_index_of_current] = vec[i];
        count[digit]--;
    }
    for (int i = 0; i < nsize; i++) {
        vec[i] = temp[i];
    }
}

void RadixSort::operator()(std::vector<int>& vec) {
    int max_value = *max_element(vec.begin(), vec.end());
    for (int base = 1; max_value / base > 0; base *= 10) {
        this->CountSort(vec, base);
    }
}