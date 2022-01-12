#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int partition_first_element(std::vector<int> &a, int left, int right)
{
    int pivot = a[left];

    int i = left + 1;

    for(int j = left + 1; j <= right; j++)
    {
        if(a[j] < pivot)
        {
           std::swap(a[i], a[j]);
           i++;
        }
    }

    std::swap(a[left], a[i-1]);

    return (i - 1);
}

int comparisons = 0;

void quickSort_median_pivot(std::vector<int> &a, int left, int right)
{
    if(left < right)
    {
        // We will need n-1 number of comparisons by choosing the first element as pivot in the\
        // partiiton subroutine
        comparisons += (right - left);

        // Taking the median as pivot
        long mid = (right + left) / 2;
        long pivot_index = mid;

        if((a[left] > a[mid] && a[left] < a[right]) || (a[left] > a[right] && a[left] < a[mid]))
        {
            pivot_index = left;
        } else if((a[right] > a[mid] && a[right] < a[left]) || (a[right] > a[left] && a[right] < a[mid]))
        {
            pivot_index = right;
        }

        // Since out partition subroutine considers the first element as pivot, we need to swap
        // out desired pivot with the first element
        std::swap(a[left], a[(int)pivot_index]);

        int partitined_index = partition_first_element(a, left, right);

        quickSort_median_pivot(a, left, partitined_index - 1);
        quickSort_median_pivot(a, partitined_index + 1, right);
    }
}

void quickSort_last_pivot(std::vector<int> &a, int left, int right)
{
    if(left < right)
    {
        // We will need n-1 number of comparisons by choosing the first element as pivot in the\
        // partiiton subroutine
        comparisons += (right - left);

        // Swap the last element with the first element since we want the last element to be considered
        // as pivot
        std::swap(a[left], a[right]);

        int partitined_index = partition_first_element(a, left, right);

        quickSort_last_pivot(a, left, partitined_index - 1);
        quickSort_last_pivot(a, partitined_index + 1, right);
    }
}

void quickSort_first_pivot(std::vector<int> &a, int left, int right)
{
    if(left < right)
    {
        // We will need n-1 number of comparisons by choosing the first element as pivot in the\
        // partiiton subroutine
        comparisons += (right - left);

        int partitined_index = partition_first_element(a, left, right);

        quickSort_first_pivot(a, left, partitined_index - 1);
        quickSort_first_pivot(a, partitined_index + 1, right);
    }
}

int main()
{
    std::vector<int> inputArray;
    std::fstream inputFile("input.txt", std::ios::in);

    std::string line;

    while(std::getline(inputFile, line))
    {
        inputArray.push_back(std::atoi(line.c_str()));
    }

    quickSort_median_pivot(inputArray, 0, inputArray.size() - 1);

    // for (auto i : inputArray)
    // {
    //     std::cout << i << std::endl;
    // }
    // std::cout << std::endl;

    std::cout << comparisons << std::endl;

    return 0;
}