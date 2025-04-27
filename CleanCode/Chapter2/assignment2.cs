/*
    You are given an array of n numbers and q queries. For each query you have to print the floor of the expected 
    value(mean) of the subarray from L to R.

    Inputs
        First line contains two integers N and Q denoting number of array elements and number of queries.
        Next line contains N space seperated integers denoting array elements.
        Next Q lines contain two integers L and R(indices of the array).

    Output
        print a single integer denoting the answer.

    Example 
        Input
            5 3
            1 2 3 4 5
            1 3
            2 4
            2 5
        Output
            2
            3
            3
*/

using System;
using System.Numerics;

class MyClass {

    static void Main(string[] args) {
        var arrayAndQueriesSize = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
        var arrayElements = Array.ConvertAll(Console.ReadLine().Split(' '), long.Parse);
        long[] prefixSumArray = calculatePrefixSum(arrayElements, arrayAndQueriesSize[0]);
        solveQueries(prefixSumArray, arrayAndQueriesSize[1]);
    }

    static long[] calculatePrefixSum(long[] array, int arraySize){
        long[] prefixSumArray = new long[arraySize + 1];
        prefixSumArray[0] = 0;

        for (int i = 1; i <= arraySize; i++)
        {
            prefixSumArray[i] = prefixSumArray[i - 1] + array[i - 1];
        }

        return prefixSumArray;
    }

    static void solveQueries(long[] prefixSumArray, int queriesSize){
        while (queriesSize-- > 0)
        {
            var rangeIndices = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
            long subArrayMean = calculateSubarrayMean(prefixSumArray, rangeIndices);
            Console.WriteLine(subArrayMean);
        }
    }

    static long calculateSubarrayMean(long[] prefixSumArray, int[] rangeIndices){
        int leftRangeIndex = rangeIndices[0];
        int rightRangeIndex = rangeIndices[1];

        long subarraySum = prefixSumArray[rightRangeIndex] - prefixSumArray[leftRangeIndex - 1];

        return subarraySum / (rightRangeIndex - leftRangeIndex + 1);
    }
}
 
