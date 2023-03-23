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
void randData(vector<T>& a, int n, int random)    //����n�� 0-random����������ڴ����������������Ϊ����ǰ����
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
//��������
//����
template<class T>
int partition(vector<T>& nums, int low, int high, bool is_increase) {
    //���һ������Ԫ��Ϊ��ŦԪ��
    T pivot = nums[low];
    //��������
    if (is_increase) {
        while (low < high) {
            //���������ұ���ŦԪ��С������Ԫ��
            while (low < high && nums[high] >= pivot)high--;
            nums[low] = nums[high];
            //���������ұ���ŦԪ�ش�ĵ�����Ԫ��
            while (low < high && nums[low] <= pivot)low++;
            nums[high] = nums[low];
        }
        //��ŦԪ�ع�λ
        nums[low] = pivot;
    }
    //��������
    else {
        while (low < high) {
            //���������ұ���ŦԪ��С������Ԫ��
            while (low < high && nums[high] <= pivot)high--;
            nums[low] = nums[high];
            //���������ұ���ŦԪ�ش�ĵ�����Ԫ��
            while (low < high && nums[low] >= pivot)low++;
            nums[high] = nums[low];
        }
        //��ŦԪ�ع�λ
        nums[low] = pivot;
    }
    return low;
}
//����
template<class T>
void qSort(vector<T>& nums, int low, int high, bool is_increase) {
    if (low < high) {
        int pivot = partition(nums, low, high, is_increase);
        qSort(nums, low, pivot - 1, is_increase);
        qSort(nums, pivot + 1, high, is_increase);
    }
    else return;
}
//ð������
template<class T>
void bubbleSort(vector<T>& nums, bool is_increase) {
    bool guard = true;
    //��������
    if (is_increase) {
        for (int i = 0;i < nums.size() - 1;i++) {
            guard = true;
            //��ʱ�Ѿ���i��Ԫ���Ѿ�������Ԥ�ڵ�λ��
            for (int j = 0;j < nums.size() - (i + 1);j++) {
                if (nums[j] > nums[j + 1]) {
                    guard = false;
                    T tmp = nums[j];
                    nums[j] = nums[j + 1];
                    nums[j + 1] = tmp;
                }
            }
            if (guard)
                return;//���һ�˱�����û�з����κν���˵�������Ѿ�������
        }

    }
    //��������
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
//��������
template<class T>
void insertSort(vector<T>& nums, bool is_increase) {
    T tmp;
    int j;
    if (is_increase) {//����
        for (int i = 1; i < nums.size(); i++) {
            tmp = nums[i];
            //����Ԫ�ط���������Ԫ�ص��ʵ�λ��
            for (j = i; j > 0 && nums[j - 1] > tmp; j--)
                nums[j] = nums[j - 1]; //λ�ò����ʽ�����õ�Ԫ�غ�Ų
            nums[j] = tmp;
        }
    }
    else {//����
        for (int i = 1; i < nums.size(); i++) {
            tmp = nums[i];
            for (j = i; j > 0 && nums[j - 1] < tmp; j--)
                nums[j] = nums[j - 1];
            nums[j] = tmp;
        }
    }
}
//ϣ������
template<class T>
void shellSort(vector<T>& nums, bool is_increase) {
    T tmp;
    int j;
    if (is_increase) {
        for (int step = nums.size() / 2;step;step /= 2) {//�൱�ڽ����з�Ϊ���ɸ������У����ж�β�������
            for (int i = step;i < nums.size();i++) {
                tmp = nums[i];
                for (j = i;j >= step && nums[j - step] > tmp;j -= step) {//���ղ���������в�������
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
//��ѡ������
template<class T>
void selectSort(vector<T>& nums, bool is_increase) {
    int min_index;
    int max_index;
    T tmp;
    if (is_increase) {
        //ѭ���ҵ���С��Ԫ��
        for (int i = 0;i < nums.size() - 1;i++) {
            min_index = i;//min_index��¼�˸��˱��������е���СԪ�ص��±�
            for (int j = i + 1;j < nums.size();j++) {
                //�����������Ԫ��С�ڼ�¼����Сֵ����Сֵ��ָ�±���и���
                if (nums[j] < nums[min_index])
                    min_index = j;
            }
            //�����˱����õ��Ľ�����������е�ǰ��
            tmp = nums[i];
            nums[i] = nums[min_index];
            nums[min_index] = tmp;
        }
    }
    //����
    else {
        //ѭ���ҵ�����Ԫ��
        for (int i = 0;i < nums.size() - 1;i++) {
            max_index = i;//max_index��¼�˸��˱��������е����Ԫ�ص��±�
            for (int j = i + 1;j < nums.size();j++) {
                //�����������Ԫ�ش��ڼ�¼�����ֵ�����ֵ��ָ�±���и���
                if (nums[j] > nums[max_index])
                    max_index = j;
            }
            //�����˱����õ��Ľ�����������е�ǰ��
            tmp = nums[i];
            nums[i] = nums[max_index];
            nums[max_index] = tmp;
        }
    }
}
//������
template<class T>
void adjustHeap(vector<T>& heap, int root, int end, bool is_increase) {
    //endΪ��βԪ���±�
    //�����ڵ�ΪҶ�ӽ�㣬����
    if (root * 2 + 1 > end)return;
    T tmp;
    //���ݸ��ڵ��±������Һ����±�
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    int max_or_min;

    //���򣬽��������
    if (is_increase) {
        //�Ƚϸ��ڵ������������ѡȡֵ��Ľ��
        if (right < end) //���������ӽ��
            max_or_min = heap[left] > heap[right] ? left : right;
        else    //ֻ������
            max_or_min = left;
        //����Ϊ�����
        if (heap[root] < heap[max_or_min]) {
            //����
            tmp = heap[max_or_min];
            heap[max_or_min] = heap[root];
            heap[root] = tmp;
            //������Ľ������Ҳ���ɴ����
            adjustHeap(heap, max_or_min, end, is_increase);
        }
    }
    //���򣬽���С����
    else {
        //�Ƚϸ��ڵ������������ѡȡֵС�Ľ��
        if (right < end) //���������ӽ��
            max_or_min = heap[left] < heap[right] ? left : right;
        else    //ֻ������
            max_or_min = left;
        //����ΪС����
        if (heap[root] > heap[max_or_min]) {
            //����
            tmp = heap[max_or_min];
            heap[max_or_min] = heap[root];
            heap[root] = tmp;
            //������Ľ������Ҳ����С����
            adjustHeap(heap, max_or_min, end, is_increase);
        }
    }

}
template<class T>
void buildHeap(vector<T>& heap, int end, bool is_increase) {
    //end Ϊ��βԪ���±�
    //��ȡ���ķ�Ҷ�ӽ�������
    for (int i = (end - 1) / 2;i >= 0;i--) {
        adjustHeap(heap, i, end, is_increase);
    }
}
template<class T>
void heapSort(vector<T>& heap, bool is_increase) {
    T tmp;
    //������
    buildHeap(heap, heap.size() - 1, is_increase);
    //�Ѷ�Ԫ���������������һ��Ԫ�ؽ������Ѷ�Ԫ�ؼ��뵽������У������µĶ�
    for (int i = heap.size() - 1;i;i--) {
        tmp = heap[i];
        heap[i] = heap[0];
        heap[0] = tmp;
        buildHeap(heap, i - 1, is_increase);
    }
}
//�鲢����
template<class T>
void merge(vector<T>& nums, int left, int right, int mid, bool is_increase) {
    //left,right��Ϊ������,midΪ�����м�Ԫ���±�
    vector<T> left_vec;
    vector<T> right_vec;
    //�������
    left_vec.resize(mid - left + 1);
    right_vec.resize(right - mid);
    for (int i = 0;i < right_vec.size();i++) {
        left_vec[i] = nums[left + i];
        right_vec[i] = nums[i + mid + 1];

    }
    left_vec[mid - left] = nums[mid];
    //���ν��й鲢����
    int i = 0;
    int j = 0;
    //����ʵ��
    while (is_increase && i < left_vec.size() && j < right_vec.size())
        nums[left++] = left_vec[i] < right_vec[j] ? left_vec[i++] : right_vec[j++];
    //����ʵ��
    while (!is_increase && i < left_vec.size() && j < right_vec.size())
        nums[left++] = left_vec[i] > right_vec[j] ? left_vec[i++] : right_vec[j++];
    //�鲢��ʣ��Ԫ�ش���
    while (i < left_vec.size())nums[left++] = left_vec[i++];
    while (j < right_vec.size())nums[left++] = right_vec[j++];
}

template<class T>
void mergeSort(vector<T>& nums, bool is_increase, int start, int end) {
    /*
    start:�������е���ʼ�±꣬Ĭ��ֵΪ0
    end:�������еĽ�β�±꣬Ĭ��ֵΪ-1����ʾ������������Ԫ��
    is_increase��ֵΪ1ʱ���������У�ֵΪ0ʱ����������
    */
    if (end == -1)end = nums.size() - 1;
    // �ݹ����
    if (start == end)return;
    //���ҷ���
    int mid = (start + end) / 2;
    mergeSort(nums, is_increase, start, mid);
    mergeSort(nums, is_increase, mid + 1, end);
    merge(nums, start, end, mid, is_increase);

}
//��������
template<class T>
vector<T> countSort_pre(vector<T> nums, bool is_increase) {
    if (nums.size() == 0)return nums;
    if (typeid(T) != typeid(int) && typeid(T) != typeid(short) && typeid(T) != typeid(char) && typeid(T) != typeid(long)) {
        throw "��������ֻ���������ͺ��ַ�������";
    }
    //�����ֵ����Сֵ
    T min = nums[0], max = nums[0];
    for (auto num : nums) {
        if (num > max)max = num;
        if (num < min)min = num;
    }
    //������������
    vector<int>counting;
    vector<T>tmp;//�ݴ������������ڷ��ؽ��
    counting.resize(max - min + 1, 0);//����Ԫ��Ĭ��ֵΪ0
    tmp.resize(nums.size());
    //�����������
    for (auto num : nums) //�����������е�Ԫ��ֵ���ָ���ͳ�Ƶ�����������
        counting[num - min]++;
    if (is_increase) {
        for (int i = 1;i < counting.size();i++)     //���򣬼���������ֵ��ǰ�����ۼ�
            counting[i] += counting[i - 1];
        //����Ӵ���������ȡ�����ŵ�tmp�м���������ֵ��Ӧ���±�λ�ã�ȡ������������е�ֵ-1
        for (int i = nums.size() - 1;i >= 0;i--)
            tmp[--counting[nums[i] - min]] = nums[i];
    }
    else {
        for (int i = counting.size() - 2;i >= 0;i--)     //���򣬼���������ֵ�Ӻ���ǰ�ۼ�
            counting[i] += counting[i + 1];
        //����Ӵ���������ȡ�����ŵ�tmp�м���������ֵ��Ӧ���±�λ�ã�ȡ������������е�ֵ-1
        for (int i = 0;i < nums.size();i++)
            tmp[--counting[nums[i] - min]] = nums[i];
    }
    return tmp;
}
template<class T>
void countSort(vector<T>& nums, bool is_increase) {
    //ֻ�����������ַ��������������򲶻��쳣
    try {
        nums = countSort_pre(nums, is_increase);
    }
    catch (const char* msg) {
        cerr << msg << endl;
    }
}
//Ͱ����
template<class T>
void bucketSort(vector<T>& nums, int bucket_size, void (*func)(vector<T>&, bool), bool is_increase) {
    //bucket_sizeΪͰ�ĸ���
    //(*func)Ϊһ������ָ�룬ָ����ָ������򷽷�
    if (nums.size() == 0)return;
    //ȷ��Ͱ��С
    T max = nums[0], min = nums[0];
    for (auto num : nums) {
        if (num > max)max = num;
        if (num < min)min = num;
    }
    int bucket_range = (max - min + 1) / bucket_size + 1;
    //������Ԫ�ض�Ӧ��Ͱ
    vector< vector<T> > bucket(bucket_size);
    for (auto num : nums)
        bucket[(num - min) / bucket_range].push_back(num);
    //Ͱ��Ԫ������
    for (int i = 0;i < bucket_size;i++)
        func(bucket[i], is_increase);
    int index = 0;
    //����
    if (is_increase)
        for (auto arr : bucket)
            for (auto data : arr)
                nums[index++] = data;

    //����
    else
        for (int i = bucket.size() - 1;i >= 0;i--)
            for (auto data : bucket[i])
                nums[index++] = data;

}


#endif
