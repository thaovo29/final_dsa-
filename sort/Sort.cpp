#include "Sort.h"

void swap(int& a, int& b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void SelectionSort(int* a, int n) {
    for (int i = 0; i < n - 1; i++) {
        int max = i;
        for (int j = i + 1; j < n; j++)
            if (a[max] < a[j])
                max = j;
        swap(a[i], a[max]);
    }
}


void InsertionSort(int* a, int n)
{
    for (int i = 1; i < n; i++)
    {
        int v = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > v)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = v;
    }
}

void BubbleSort(int* a, int n)
{
    for (int i = 1; i < n; i++)
    {
        bool haveSwap = false;
        for (int j = 0; j < n - i; j++)
            if (a[j + 1] < a[j])
            {
                swap(a[j], a[j + 1]);
                haveSwap = true;
            }
        if (haveSwap == false)
            break;
    }
}


void shakerSort(int* a, int n)
{
    int Left = 0;
    int Right = n - 1;
    int k = 0;
    while (Left < Right)
    {
        for (int i = Left; i < Right; i++)
        {
            if (a[i] > a[i + 1])
            {
                swap(a[i], a[i + 1]);
                k = i;
            }
        }
        Right = k;
        for (int i = Right; i > Left; i--)
        {
            if (a[i] < a[i - 1])
            {
                swap(a[i], a[i - 1]);
                k = i;
            }
        }
        Left = k;
    }
}
//https://codelearn.io/learning/data-structure-and-algorithms/856660
void shellSort(int* a, int n) {
    int interval, i, j, temp;
    for (interval = n / 2; interval > 0; interval /= 2) {
        for (i = interval; i < n; i++) {
            temp = a[i];
            for (j = i; j >= interval && a[j - interval] > temp; j -= interval) {
                a[j] = a[j - interval];
            }
            a[j] = temp;
        }
    }
}



void heapRebuild(int* a, int pos, int n)
{

    while (2 * pos + 1 < n)
    {
        int j = 2 * pos + 1;
        if (j < n - 1)
            if (a[j] < a[j + 1])
                j = j + 1;
        if (a[pos] >= a[j])
            return;
        swap(a[pos], a[j]);
        pos = j;
    }
}
void heapConstruct(int* a, int n)
{
    for (int i = (n - 1) / 2; i >= 0; i--)
        heapRebuild(a, i, n);
}
void HeapSort(int* a, int n)
{
    heapConstruct(a, n);
    int r = n - 1;
    while (r > 0)
    {
        swap(a[0], a[r]);
        heapRebuild(a, 0, r);
        r--;
    }
}

void merge(int* a, int first, int mid, int last)
{
    int n1 = mid - first + 1;
    int n2 = last - mid;
    int* L = new int[n1];
    int* R = new int[n2];
    for (int i = 0; i < n1; i++)
        L[i] = a[first + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[mid + j + 1];
    int i = 0;
    int j = 0;
    int k = first;
    while (i < n1 && j < n2)
        a[k++] = (L[i] < R[j]) ? L[i++] : R[j++];

    while (j < n2)
        a[k++] = R[j++];
    while (i < n1)
        a[k++] = L[i++];
    delete[] L;
    delete[] R;
}
void mergeSort(int* a, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}


int Partition(int* a, int left, int right)
{
    int p = a[left + (right - left) / 2];
    int i = left;
    int j = right + 1;
    do
    {
        do
            i++;
        while (a[i] < p);
        do
            j--;
        while (a[j] > p);
        swap(a[i], a[j]);

    } while (i < j);
    swap(a[i], a[j]);
    swap(a[left], a[j]);
    return j;
}

void QuickSort(int* a, int left, int right)
{
    if (left < right)
    {
        int s = Partition(a, left, right);
        QuickSort(a, left, s - 1);
        QuickSort(a, s + 1, right);
    }
}

void CountingSort(int* a, int n)
{
    int* count = new int[n];
    for (int i = 0; i < n; i++)
        count[i] = 0;
    int* b = new int[n];
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] < a[j])
                count[j]++;
            else
                count[i]++;
    for (int i = 0; i < n; i++)
        b[count[i]] = a[i];
    for (int i = 0; i < n; i++)
        a[i] = b[i];
    delete[] b;
    delete[] count;
}

void radixSort(int* a, int n)
{
    int* b = new int[n];
    int m = a[0], exp = 1;

    for (int i = 0; i < n; i++)
        if (a[i] > m)
            m = a[i];

    while (m / exp > 0)
    {
        int bucket[10] = { 0 };
        for (int i = 0; i < n; i++)
            bucket[a[i] / exp % 10]++;
        for (int i = 1; i < 10; i++)
            bucket[i] += bucket[i - 1];
        for (int i = n - 1; i >= 0; i--)
            b[--bucket[a[i] / exp % 10]] = a[i];
        for (int i = 0; i < n; i++)
            a[i] = b[i];
        exp *= 10;
    }
    delete[] b;
}

void FlashSort(int* a, int n) {
    int minVal = a[0];
    int max = a[0];
    int m = int(0.45 * n);
    int* l = new int[m];
    for (int i = 0; i < m; i++)
        l[i] = 0;
    for (int i = 1; i < n; i++)
    {
        if (a[i] < minVal)
            minVal = a[i];
        if (a[i] > max)
            max = a[i];
    }
    if (max == minVal)
        return;
    double c1 = (double)(m - 1) / (max - minVal);
    for (int i = 0; i < n; i++)
    {
        int k = int(c1 * (a[i] - minVal));
        ++l[k];
    }
    for (int i = 1; i < m; i++)
        l[i] += l[i - 1];
    swap(max, a[0]);
    int nmove = 0;
    int j = 0;
    int k = m - 1;
    int t = 0;
    int flash;
    while (nmove < n - 1)
    {
        while (j > l[k] - 1)
        {
            j++;
            k = int(c1 * (a[j] - minVal));
        }
        flash = a[j];
        if (k < 0) break;

        while (j != l[k])
        {
            k = int(c1 * (flash - minVal));
            int hold = a[t = --l[k]];
            a[t] = flash;
            flash = hold;
            ++nmove;
        }
    }
    delete[] l;
    InsertionSort(a, n);
}

void print(int a[], int n)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

    