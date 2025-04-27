#include <iostream>
#include <vector>

void bubbleSort(std::vector<int> &arr)
{
    int size = arr.size();
    for (int i = 0; i < size; i++)
    {
        bool isSwapped = false;
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
                isSwapped = true;
            }
        }
        if (!isSwapped)
        {
            return;
        }
    }
}

void selectionSort(std::vector<int> &arr)
{
    int size = arr.size();
    for (int i = 0; i < size - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
    }
}

void insertionSort(std::vector<int> &arr)
{
    int size = arr.size();
    for (int i = 1; i < size; i++)
    {
        int currentValue = arr[i];
        int j = i;
        while (j > 0 && currentValue < arr[j - 1])
        {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = currentValue;
    }
}

int main()
{
    std::vector<int> arr = {4, 2, 1, 4, 5, 6, 3, 8};
    // bubbleSort(arr);
    // selectionSort(arr);
    insertionSort(arr);
    for (int num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}