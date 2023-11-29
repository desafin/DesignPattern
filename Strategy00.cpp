#include <iostream>

class SortStrategy {
public:
	virtual void sort(int arr[], int size) = 0;
	virtual ~SortStrategy() {}
};

class BubbleSort : public SortStrategy {
public:
	void sort(int arr[], int size) override {
		std::cout << "Bubble Sort\n";
	}
};

class QuickSort : public SortStrategy {
public:
	void sort(int arr[], int size) override {
		std::cout << "Quick Sort\n";
	}
};

class Sorter {
private:
	SortStrategy* strategy;

public:
	Sorter(SortStrategy* strat) : strategy(strat) {}

	void setStrategy(SortStrategy* strat) {
		strategy = strat;
	}

	void performSort(int arr[], int size) {
		strategy->sort(arr, size);
	}
};


int main()
{
	int arr[] = { 4, 2, 7, 1, 5 };
	int size = sizeof(arr) / sizeof(arr[0]);

	BubbleSort bubb1eSort;
	QuickSort quickSort;

	Sorter sorter(&bubb1eSort); // Bubb1eSort로 정렬 설정
	sorter.performSort(arr, size);

	// 결과 출력 흑은 다음 정렬 진행
	sorter.setStrategy(&quickSort);
	sorter.performSort(arr, size);

	return 0;
}
