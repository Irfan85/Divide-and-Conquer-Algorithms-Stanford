#include <iostream>
#include <fstream>
#include <string>
#include <vector>

long inverseCount = 0;

void mergeAndCount(std::vector<int> &a, int begin, int mid, int end)
{
    int leftArraySize = mid - begin + 1;
    std::vector<int> left(leftArraySize);

    int rightArraySize = end - mid;
    std::vector<int> right(rightArraySize);

    for(int i = 0; i < left.size(); i++)
    {
        left[i] = a[begin + i];
    }

    for(int i = 0; i < right.size(); i++)
    {
        right[i] = a[mid + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = begin;

    while (i < left.size() && j < right.size())
    {
        if(left[i] <= right[j])
        {
            a[k] = left[i];
            i++;
        } 
        else
        {
            a[k] = right[j];
            j++;

            inverseCount += (left.size() - i);
        }

        k++;
    }

    while (i < left.size())
    {
        a[k] = left[i];
        i++;
        k++;
    }

    while (j < right.size())
    {
        a[k] = right[j];
        j++;
        k++;
    }
}

void mergeSortAndCountInverse(std::vector<int> &a, int begin, int end)
{
    if(begin >= end)
    {
        return;
    }

    int mid = (begin + end) / 2;

    mergeSortAndCountInverse(a, begin, mid);
    mergeSortAndCountInverse(a, mid + 1, end);

    mergeAndCount(a, begin, mid, end);

}

int main()
{
    std::vector<int> inputArray;
    std::ifstream inputFile("input.txt", std::ios::in);

    std::string line;

    while (std::getline(inputFile, line))
    {
        inputArray.push_back(std::atoi(line.c_str()));
    }

    mergeSortAndCountInverse(inputArray, 0, inputArray.size() - 1);

    std::cout << inverseCount << std::endl;
    
    std::cout << std::endl;

    // for(auto i : inputArray)
    // {
    //     std::cout << i << std::endl;
    // }

    return 0;
}