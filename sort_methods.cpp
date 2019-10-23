//插入排序：简单但效率低
//设存在N个互异元素的序列L与根据序列L以相反顺序形成的序列Lc，则L与Lc逆序数之和为 N * (N + 1) / 2；
//所以对于任意存在N个互异元素的序列的逆序数为 N * (N + 1) / 4；
//而插入排序每次交换相邻相邻元素减少一个逆序，因此需要 Ω(N²) 的时间
//
//推论：通过交换相邻元素进行排序的算法都需要 Ω(N²) 的时间
class Insertion_Sort {
	static void InsertionSort(vector<int> & arr) {
		for (int p = 1; p < arr.size(); ++p) {
			int temp = arr[p];
			int i = p;
			for (; i > 0 && arr[i - 1] > temp; --i)
				arr[i] = arr[i - 1];
			arr[i] = temp;
		}
	}
};




//希尔排序：编程简单且具有亚二次的时间界，因而成为适度的大量的数据输入的排序算法（即使对于数以万计的N）
//选取一个增量序列hn，对所有相隔hn的元素进行插入排序，且一个hk排序的文件将保持其hk排序性
//希尔排序的运行时间依赖于增量序列的选择，使用希尔排序的最坏情形运行时间是 Θ(N²)
//一个较常使用的增量序列为 hn = N / 2, hn-1  = hn / 2（但不好）
//当应用Hibbard序列：1，3，7，……，2的k次方 - 1， 此时希尔排序的最坏情形运行时间是 Θ(N的3/2次方)
class Shell_Sort {
public:
	static void ShellSort(vector<int> & arr) {
		int size = arr.size();
		for (int gap = size / 2; gap > 0; gap /= 2) {
			for (int i = gap; i < size; ++i) {
				int temp = arr[i];
				int j = i;
				for (; j >= gap && arr[j - gap] > temp; j -= gap)
					arr[j] = arr[j - gap];
				arr[j] = temp;
			}
		}
	}
};




//堆排序：以O(NlogN)时间进行排序 所用平均比较次数为2NlogN - O(loglogN) 是不稳定的排序算法
//二叉堆中单次删除操作需要O(logN)时间，而一共进行N次操作，故所用时间为O(NlogN)
//当以从小到大的顺序排序时，使用大根堆，即较大的元素位于数组前端，反之使用小根堆
class Heap_Sort {
public:
	static void HeapSort(vector<int> & arr) {
		for (int i = arr.size() / 2 - 1; i >= 0; --i)
			PrecDown(arr, i, arr.size());
		for (int j = arr.size() - 1; j > 0; --j) {
			std::swap(arr[0], arr[j]);
			PrecDown(arr, 0, j);
		}
	}

private:
	static void PrecDown(vector<int> & arr, int hole, int heapSize) {
		int child;
		auto temp = arr[hole];
		for (; LeftChild(hole) < heapSize; hole = child) {//use < but not <= , this is not the same with binary-heap
			child = LeftChild(hole);					  //after deleteMax, the value will be stored in vector[heapSize]
			if (child + 1 < heapSize && arr[child + 1] > arr[child])//so you should not reach there
				++child;
			if (arr[child] > temp)
				arr[hole] = arr[child];
			else
				break;
		}
		arr[hole] = temp;
	}


	static inline int LeftChild(int fatherIndex) {
		return 2 * fatherIndex + 1;
	}
};




//归并排序：以O(NlogN)最坏时间进行排序 使用目前流行排序算法中最小的比较次数 是稳定的排序算法
//思路：将数组划分成更小的数组，在各小数组中进行排序后合并
class Merge_Sort {
public:
	static void MergeSort(vector<int> & arr) {
		vector<int> tempArr(arr.size());
		MergeSort(arr, tempArr, 0, arr.size() - 1);
	}
private:
	static void MergeSort(vector<int> & arr, vector<int> & tempArr, int left, int right) {
		if (left < right) {
			int center = (left + right) / 2;
			MergeSort(arr, tempArr, left, center);
			MergeSort(arr, tempArr, center + 1, right);
			Merge(arr, tempArr, left, center + 1, right);
		}
	}

	static void Merge(vector<int> & arr, vector<int> & tempArr, int leftPos, int rightPos, int rightEnd) {
		int leftEnd = rightPos - 1;
		int numElements = rightEnd - leftPos + 1;
		int currentPos = leftPos;
		
		while (leftPos <= leftEnd && rightPos <= rightEnd)
			if (arr[leftPos] <= arr[rightPos])
				tempArr[currentPos++] = arr[leftPos++];
			else
				tempArr[currentPos++] = arr[rightPos++];

		while(leftPos <= leftEnd)
			tempArr[currentPos++] = arr[leftPos++];
		while (rightPos <= rightEnd)
			tempArr[currentPos++] = arr[rightPos++];

		for (int i = 0; i < numElements; ++i, --rightEnd)
			arr[rightEnd] = tempArr[rightEnd];
	}
};




//快速排序：目前实践中已知的最快排序方式，平均运行时间是O(NlogN)，最坏运行时间是O(N²)，不稳定
//步骤：选择枢纽元，将所有小于枢纽元的元素置于其前方，将所有大于枢纽元的元素置于其后方
//	    以枢纽元为界划分成两部分数组，各自递归运行，当数组长度较小时可使用插入排序
class Qucik_Sort {
private:
	static void InsertionSort(vector<int> & arr, int left, int right) {
		for (int p = left + 1; p <= right; ++p) {
			int temp = arr[p];
			int i = p;
			for (; i > 0 && arr[i - 1] > temp; --i)
				arr[i] = arr[i - 1];

			arr[i] = temp;
		}
	}

	//此函数将枢纽元置于right-1处，调用其的函数应记得将枢纽元恢复
	static int Median3(vector<int> & arr, int left, int right) {
		int center = (left + right) / 2;
		if (arr[left] > arr[center])
			std::swap(arr[left], arr[center]);
		if (arr[left] > arr[right])
			std::swap(arr[left], arr[right]);
		if (arr[center] > arr[right])
			std::swap(arr[center], arr[right]);

		std::swap(arr[center], arr[right - 1]);
		return arr[right - 1];
	}

	static void QuickSort(vector<int> & arr, int left, int right) {
		if (left + 10 <= right) {
			int pivot = Median3(arr, left, right);
			int i = left, j = right - 1;

			for (;;) {
				while(arr[++i] < pivot){}
				while(arr[--j] > pivot){}
				if (i < j)
					std::swap(arr[i], arr[j]);
				else
					break;
			}

			arr[i] = arr[right - 1];//恢复枢纽元 使该部分数组成功排序
			QuickSort(arr, left, i - 1);
			QuickSort(arr, i + 1, right);
		}
		else {
			InsertionSort(arr, left, right);
		}
	}

public:
	static void QuickSort(vector<int> & arr) {
		QuickSort(arr, 0, arr.size() - 1);
	}
};
