#pragma once

namespace SortLib {
	template <typename T>
	void BubbleSort(T arr[], int size);

	template <typename T>
	void InsertionSort(T arr[], int size);

	template <typename T>
	void SelectionSort(T arr[], int size);

	template <typename T>
	void ExchangeSort(T arr[], int size);

	template <typename T>
	void RadixSort(T arr[], int size);

	template <typename T>
	void BucketSort(T arr[], int size);

	template <typename T>
	void CountingSort(T arr[], int size);

	template <typename T>
	void MergeSort(T arr[], int size);

	template <typename T>
	void QuickSort(T arr[], int size);
}
