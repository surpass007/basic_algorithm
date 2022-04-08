#ifndef SRC_SORT_H_
#define SRC_SORT_H_

namespace sort_algorithm {
    class SortBase {
        public:
            virtual void operator()(std::vector<int>& vec) = 0;
            
            virtual ~SortBase() {}
    };


    class HeapSort : public SortBase {
        public:
            void operator()(std::vector<int>& vec) override;

            void Heapify(std::vector<int>& vec, int root_index, int current_size);

            void BuildHeap(std::vector<int>& vec);

            int GetLeftChild(int index);

            int GetRightChild(int index);

            virtual ~HeapSort() {}

        private:
            int current_size_;
            int capacity_;
    };

    class QuickSort : public SortBase {
        public:
            void operator()(std::vector<int>& vec) override;

            int Partition(std::vector<int>& vec, int left, int right);

            void operator()(std::vector<int>& vec, int left, int right);

            virtual ~QuickSort() {}
    };

    class ShellSort : public SortBase {
        public:
            void operator()(std::vector<int>& vec) override;

            virtual ~ShellSort() {}
    };

    class InsertSort : public SortBase {
        public:
            void operator()(std::vector<int>& vec) override;

            virtual ~InsertSort() {}
    };

    class MergeSort : public SortBase {
        public:
            void operator()(std::vector<int>& vec) override;

            void Merge(std::vector<int>& vec, int left, int mid, int right);

            void MergeAndSort(std::vector<int>& vec, int left, int right);

            virtual ~MergeSort() {}
    };

    class BucketSort : public SortBase {
        public:
            void operator()(std::vector<int>& vec) override;

            virtual ~BucketSort() {}
    };

    class CountSort : public SortBase {
        public:
            void operator()(std::vector<int>& vec) override;

            virtual ~CountSort() {}
    };

    class RadixSort : public SortBase {
        public:
            void operator()(std::vector<int>& vec) override;

            void CountSort(std::vector<int>& vec, int base);

            virtual ~RadixSort() {}
    };
} // sort_algorithm

#endif // SRC_SORT_H_