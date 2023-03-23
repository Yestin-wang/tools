#ifndef	SORT_HPP
#define SORT_HPP
#include <iostream>
#include <vector>
#include<time.h>
#include<algorithm>
#include <random>
template<class T>
void printVec(T val) {
    cout << val << " ";
}
template<class T>
void randData(vector<T>& a, int n, int random)    //产生n个 0-random随机数，用于创建随机数组用来作为排序前数列
{
    a.resize(n);
    srand(time(NULL));
    if (typeid(T) == typeid(char)) {
        for (int i = 0;i < n;i++) {
            a[i] = 'a' + rand() % 26;
            cout << a[i] << ",";
        }
    }
    else if (typeid(T) == typeid(int)) {
        for (int i = 0;i < n;i++)
        {
            a[i] = rand() % random;
            cout << a[i] << ",";
        }
    }
    else if (typeid(T) == typeid(double)) {
        uniform_real_distribution<double> u(-1, 1);
        default_random_engine e(time(NULL));

        for (int i = 0; i < n; i++) {
            cout << u(e) << " ";
        }

    }
    cout << endl;
}
//快速排序
//划分
template<class T>
int partition(vector<T>& nums, int low, int high, bool is_increase) {
    //令第一个数组元素为枢纽元素
    T pivot = nums[low];
    //升序排序
    if (is_increase) {
        while (low < high) {
            //从右向左找比枢纽元素小的数组元素
            while (low < high && nums[high] >= pivot)high--;
            nums[low] = nums[high];
            //从左向右找比枢纽元素大的的数组元素
            while (low < high && nums[low] <= pivot)low++;
            nums[high] = nums[low];
        }
        //枢纽元素归位
        nums[low] = pivot;
    }
    //降序排序
    else {
        while (low < high) {
            //从右向左找比枢纽元素小的数组元素
            while (low < high && nums[high] <= pivot)high--;
            nums[low] = nums[high];
            //从左向右找比枢纽元素大的的数组元素
            while (low < high && nums[low] >= pivot)low++;
            nums[high] = nums[low];
        }
        //枢纽元素归位
        nums[low] = pivot;
    }
    return low;
}
//分治
template<class T>
void qSort(vector<T>& nums, int low, int high, bool is_increase) {
    if (low < high) {
        int pivot = partition(nums, low, high, is_increase);
        qSort(nums, low, pivot - 1, is_increase);
        qSort(nums, pivot + 1, high, is_increase);
    }
    else return;
}
//冒泡排序
template<class T>
void bubbleSort(vector<T>& nums, bool is_increase) {
    bool guard = true;
    //升序排序
    if (is_increase) {
        for (int i = 0;i < nums.size() - 1;i++) {
            guard = true;
            //此时已经有i个元素已经到达了预期的位置
            for (int j = 0;j < nums.size() - (i + 1);j++) {
                if (nums[j] > nums[j + 1]) {
                    guard = false;
                    T tmp = nums[j];
                    nums[j] = nums[j + 1];
                    nums[j + 1] = tmp;
                }
            }
            if (guard)
                return;//如果一趟遍历中没有发生任何交换说明数组已经有序了
        }

    }
    //降序排序
    else {
        for (int i = 0;i < nums.size() - 1;i++) {
            guard = true;
            for (int j = 0;j < nums.size() - (i + 1);j++) {
                if (nums[j] < nums[j + 1]) {
                    guard = false;
                    T tmp = nums[j];
                    nums[j] = nums[j + 1];
                    nums[j + 1] = tmp;
                }
            }
            if (guard)
                return;
        }
    }

}
//插入排序
template<class T>
void insertSort(vector<T>& nums, bool is_increase) {
    T tmp;
    int j;
    if (is_increase) {//升序
        for (int i = 1; i < nums.size(); i++) {
            tmp = nums[i];
            //将该元素放在已排序元素的适当位置
            for (j = i; j > 0 && nums[j - 1] > tmp; j--)
                nums[j] = nums[j - 1]; //位置不合适将排序好的元素后挪
            nums[j] = tmp;
        }
    }
    else {//降序
        for (int i = 1; i < nums.size(); i++) {
            tmp = nums[i];
            for (j = i; j > 0 && nums[j - 1] < tmp; j--)
                nums[j] = nums[j - 1];
            nums[j] = tmp;
        }
    }
}
//希尔排序
template<class T>
void shellSort(vector<T>& nums, bool is_increase) {
    T tmp;
    int j;
    if (is_increase) {
        for (int step = nums.size() / 2;step;step /= 2) {//相当于将数列分为若干个子数列，进行多次插入排序
            for (int i = step;i < nums.size();i++) {
                tmp = nums[i];
                for (j = i;j >= step && nums[j - step] > tmp;j -= step) {//按照步长间隔进行插入排序
                    nums[j] = nums[j - step];
                }
                nums[j] = tmp;
            }
        }
    }
    else {
        for (int step = nums.size() / 2;step;step /= 2) {
            for (int i = step;i < nums.size();i++) {
                tmp = nums[i];
                for (j = i;j >= step && nums[j - step] < tmp;j -= step) {
                    nums[j] = nums[j - step];
                }
                nums[j] = tmp;
            }
        }
    }
}
//简单选择排序
template<class T>
void selectSort(vector<T>& nums, bool is_increase) {
    int min_index;
    int max_index;
    T tmp;
    if (is_increase) {
        //循环找到最小的元素
        for (int i = 0;i < nums.size() - 1;i++) {
            min_index = i;//min_index记录了该趟遍历过程中的最小元素的下标
            for (int j = i + 1;j < nums.size();j++) {
                //如果遍历到的元素小于记录的最小值，最小值所指下标进行更新
                if (nums[j] < nums[min_index])
                    min_index = j;
            }
            //将此趟遍历得到的结果交换到数列的前部
            tmp = nums[i];
            nums[i] = nums[min_index];
            nums[min_index] = tmp;
        }
    }
    //降序
    else {
        //循环找到最大的元素
        for (int i = 0;i < nums.size() - 1;i++) {
            max_index = i;//max_index记录了该趟遍历过程中的最大元素的下标
            for (int j = i + 1;j < nums.size();j++) {
                //如果遍历到的元素大于记录的最大值，最大值所指下标进行更新
                if (nums[j] > nums[max_index])
                    max_index = j;
            }
            //将此趟遍历得到的结果交换到数列的前部
            tmp = nums[i];
            nums[i] = nums[max_index];
            nums[max_index] = tmp;
        }
    }
}
//堆排序
template<class T>
void adjustHeap(vector<T>& heap, int root, int end, bool is_increase) {
    //end为堆尾元素下标
    //若根节点为叶子结点，返回
    if (root * 2 + 1 > end)return;
    T tmp;
    //根据父节点下标求左右孩子下标
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    int max_or_min;

    //升序，建立大根堆
    if (is_increase) {
        //比较父节点的左右子树，选取值大的结点
        if (right < end) //有两个孩子结点
            max_or_min = heap[left] > heap[right] ? left : right;
        else    //只有左孩子
            max_or_min = left;
        //调整为大根堆
        if (heap[root] < heap[max_or_min]) {
            //交换
            tmp = heap[max_or_min];
            heap[max_or_min] = heap[root];
            heap[root] = tmp;
            //交换后的结点向下也构成大根堆
            adjustHeap(heap, max_or_min, end, is_increase);
        }
    }
    //降序，建立小根堆
    else {
        //比较父节点的左右子树，选取值小的结点
        if (right < end) //有两个孩子结点
            max_or_min = heap[left] < heap[right] ? left : right;
        else    //只有左孩子
            max_or_min = left;
        //调整为小根堆
        if (heap[root] > heap[max_or_min]) {
            //交换
            tmp = heap[max_or_min];
            heap[max_or_min] = heap[root];
            heap[root] = tmp;
            //交换后的结点向下也构成小根堆
            adjustHeap(heap, max_or_min, end, is_increase);
        }
    }

}
template<class T>
void buildHeap(vector<T>& heap, int end, bool is_increase) {
    //end 为堆尾元素下标
    //获取最靠后的非叶子结点的坐标
    for (int i = (end - 1) / 2;i >= 0;i--) {
        adjustHeap(heap, i, end, is_increase);
    }
}
template<class T>
void heapSort(vector<T>& heap, bool is_increase) {
    T tmp;
    //构建堆
    buildHeap(heap, heap.size() - 1, is_increase);
    //堆顶元素与无序数列最后一个元素交换，堆顶元素加入到有序队列，构建新的堆
    for (int i = heap.size() - 1;i;i--) {
        tmp = heap[i];
        heap[i] = heap[0];
        heap[0] = tmp;
        buildHeap(heap, i - 1, is_increase);
    }
}
//归并排序
template<class T>
void merge(vector<T>& nums, int left, int right, int mid, bool is_increase) {
    //left,right都为闭区间,mid为序列中间元素下标
    vector<T> left_vec;
    vector<T> right_vec;
    //左多右少
    left_vec.resize(mid - left + 1);
    right_vec.resize(right - mid);
    for (int i = 0;i < right_vec.size();i++) {
        left_vec[i] = nums[left + i];
        right_vec[i] = nums[i + mid + 1];

    }
    left_vec[mid - left] = nums[mid];
    //两段进行归并排序
    int i = 0;
    int j = 0;
    //升序实现
    while (is_increase && i < left_vec.size() && j < right_vec.size())
        nums[left++] = left_vec[i] < right_vec[j] ? left_vec[i++] : right_vec[j++];
    //降序实现
    while (!is_increase && i < left_vec.size() && j < right_vec.size())
        nums[left++] = left_vec[i] > right_vec[j] ? left_vec[i++] : right_vec[j++];
    //归并段剩余元素处理
    while (i < left_vec.size())nums[left++] = left_vec[i++];
    while (j < right_vec.size())nums[left++] = right_vec[j++];
}

template<class T>
void mergeSort(vector<T>& nums, bool is_increase, int start, int end) {
    /*
    start:待排序列的起始下标，默认值为0
    end:待排序列的结尾下标，默认值为-1，表示排序容器所有元素
    is_increase：值为1时按升序排列，值为0时按降序排列
    */
    if (end == -1)end = nums.size() - 1;
    // 递归出口
    if (start == end)return;
    //左右分治
    int mid = (start + end) / 2;
    mergeSort(nums, is_increase, start, mid);
    mergeSort(nums, is_increase, mid + 1, end);
    merge(nums, start, end, mid, is_increase);

}
//计数排序
template<class T>
vector<T> countSort_pre(vector<T> nums, bool is_increase) {
    if (nums.size() == 0)return nums;
    if (typeid(T) != typeid(int) && typeid(T) != typeid(short) && typeid(T) != typeid(char) && typeid(T) != typeid(long)) {
        throw "计数排序只能排序整型和字符型数据";
    }
    //找最大值和最小值
    T min = nums[0], max = nums[0];
    for (auto num : nums) {
        if (num > max)max = num;
        if (num < min)min = num;
    }
    //建立计数数组
    vector<int>counting;
    vector<T>tmp;//暂存排序结果并用于返回结果
    counting.resize(max - min + 1, 0);//数组元素默认值为0
    tmp.resize(nums.size());
    //处理计数数组
    for (auto num : nums) //将待排序数列的元素值出现个数统计到计数数组中
        counting[num - min]++;
    if (is_increase) {
        for (int i = 1;i < counting.size();i++)     //升序，计数数组数值从前到后累加
            counting[i] += counting[i - 1];
        //反向从待排序数组取数，放到tmp中计数数组数值对应的下标位置，取出后计数数组中的值-1
        for (int i = nums.size() - 1;i >= 0;i--)
            tmp[--counting[nums[i] - min]] = nums[i];
    }
    else {
        for (int i = counting.size() - 2;i >= 0;i--)     //降序，计数数组数值从后向前累加
            counting[i] += counting[i + 1];
        //正向从待排序数组取数，放到tmp中计数数组数值对应的下标位置，取出后计数数组中的值-1
        for (int i = 0;i < nums.size();i++)
            tmp[--counting[nums[i] - min]] = nums[i];
    }
    return tmp;
}
template<class T>
void countSort(vector<T>& nums, bool is_increase) {
    //只接受整数和字符类型容器，否则捕获异常
    try {
        nums = countSort_pre(nums, is_increase);
    }
    catch (const char* msg) {
        cerr << msg << endl;
    }
}
//桶排序
template<class T>
void bucketSort(vector<T>& nums, int bucket_size, void (*func)(vector<T>&, bool), bool is_increase) {
    //bucket_size为桶的个数
    //(*func)为一个函数指针，指向所指向的排序方法
    if (nums.size() == 0)return;
    //确定桶大小
    T max = nums[0], min = nums[0];
    for (auto num : nums) {
        if (num > max)max = num;
        if (num < min)min = num;
    }
    int bucket_range = (max - min + 1) / bucket_size + 1;
    //待排序元素对应入桶
    vector< vector<T> > bucket(bucket_size);
    for (auto num : nums)
        bucket[(num - min) / bucket_range].push_back(num);
    //桶内元素排序
    for (int i = 0;i < bucket_size;i++)
        func(bucket[i], is_increase);
    int index = 0;
    //升序
    if (is_increase)
        for (auto arr : bucket)
            for (auto data : arr)
                nums[index++] = data;

    //降序
    else
        for (int i = bucket.size() - 1;i >= 0;i--)
            for (auto data : bucket[i])
                nums[index++] = data;

}


#endif
