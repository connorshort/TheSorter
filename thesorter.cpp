#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <utility>
#include <chrono>
#include<map>
#include<vector>

using namespace std;
using namespace std::chrono;

//Sorting Algorithms for Sort Ranker by Patrick Harris 11/30/2020
void selectionSort(int* arr, int size);
void bubbleSort(int* arr, int size);
void insertionSort(int* arr, int size);
void swap(int& x, int& y);
int partition(int* arr, int lo, int hi);
void quickSort(int* arr, int lo, int hi);
void merge(int* arr, int left, int mid, int right);
void mergeSort(int* arr, int left, int right);

void swap(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}

void selectionSort(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[minIndex], arr[i]);
    }
}

void bubbleSort(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void insertionSort(int* arr, int size) {
    for (int i = 1; i < size; i++) {
        int currentVal = arr[i];
        int j = i - 1;
        while (j >= 0 && currentVal < arr[j]) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = currentVal;
    }
}

int partition(int* arr, int lo, int hi) {
    int pivot = arr[lo];
    int up = lo;
    int down = hi;
    while (up < down) {
        for (int j = up; j < hi; j++) {
            if (arr[up] > pivot) {
                break;
            }
            up++;
        }
        for (int j = hi; j > lo; j--) {
            if (arr[down] < pivot) {
                break;
            }
            down--;
        }
        if (up < down) {
            swap(arr[up], arr[down]);
        }
    }
    swap(arr[lo], arr[down]);
    return down;
}//Sourced from lecture "Sorting-2", slide 64

void quickSort(int* arr, int lo, int hi) {//call as quickSort(arr, 0, size-1)
    if (lo < hi) {
        int pivot = partition(arr, lo, hi);
        quickSort(arr, lo, pivot - 1);
        quickSort(arr, pivot + 1, hi);
    }
}//Sourced from lecture "Sorting-2", slide 50

void merge(int* arr, int left, int mid, int right) {
    int n1 = (mid - left + 1);
    int n2 = right - mid;
    int* x = new  int[n1];
    int* y = new int[n2];
    for (int i = 0; i < n1; i++) {
        x[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        y[j] = arr[mid + 1 + j];
    }
    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (x[i] <= y[j]) {
            arr[k] = x[i];
            i++;
        }
        else {
            arr[k] = y[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = x[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = y[j];
        j++;
        k++;
    }
    delete[]x;
    delete[]y;
}//Sourced from lecture "Sorting-2", slide 50

void mergeSort(int* arr, int left, int right) {//call as mergeSort(arr, 0, size-1)
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}//Sourced from lecture "Sorting-2", slide 49



//Riley's Sorts
void heapify(int* arr, int size, int root) {
    int newRoot = root;
    int leftChild = (2 * root) + 1;
    int rightChild = (2 * root) + 2;
    if (leftChild < size && arr[leftChild]>arr[root]) {//if left Child exists and is greater than root, 
        newRoot = leftChild;
    }
    if (rightChild < size && arr[rightChild]>arr[newRoot]) {//if right Child exists and is greater than root & left
        newRoot = rightChild;
    }
    if (newRoot != root) {//if position swapped, swap vals
        swap(arr[root], arr[newRoot]);
        heapify(arr, size, newRoot);
    }

}
void heapSort(int* nums, int size)
{
    //build heap inplace
    for (int i = (size / 2) - 1; i >= 0; i--) {
        heapify(nums, size, i);
    }

    for (int i = 0; i < size; i++) {
        swap(nums[0], nums[(size - 1) - i]);
        heapify(nums, (size - 1) - i, 0);
    }
}

void shellSort(int* nums, int size)
{
    int gap, temp;
    gap = size / 2;
    while (gap > 0)
    {
        for (int i = gap; i < size; i++)
        {
            int j = i;
            temp = nums[i];
            while ((j >= gap) && (nums[j - gap] > temp))
            {
                nums[j] = nums[j - gap];
                j = j - gap;
            }
            nums[j] = temp;
        }

        if (gap == 2) {
            gap = 1;
        }
        else {
            gap = gap / 2.2;
        }
    }
    //return nums;
}

//to test if an array is sorted
bool sorted(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1])
            return false;
    }
    return true;
}

//creates a file of random numbers
void generateFile(string fileName, int amount, int min, int max) {
    ofstream output;
    output.open(fileName);
    for (int i = 0; i < amount; i++) {
        output << rand() % (max + 1) + min << "\n";
    }
}

//reads a file of random numbers into an array
int* generateArray(string fileName, int amount) {
    int* output = new int[amount];
    ifstream input;
    input.open(fileName);
    for (int i = 0; i < amount; i++) {
        input >> output[i];
    }
    return output;
}

//outputs an existing integer array into a file
void createOutput(string fileName, int amount, int* array) {
    ofstream output;
    output.open(fileName);
    for (int i = 0; i < amount; i++) {
        output << array[i] << "\n";
    }
}

//prints splashscreen
void splash() {
    cout << " .----------------.  .----------------.  .----------------.  \n";
    cout << "| .--------------. || .--------------. || .--------------. | \n";
    cout << "| |  _________   | || |  ____  ____  | || |  _________   | | \n";
    cout << "| | |  _   _  |  | || | |_   ||   _| | || | |_   ___  |  | | \n";
    cout << "| | |_/ | | \\_|  | || |   | |__| |   | || |   | |_  \\_|  | | \n";
    cout << "| |     | |      | || |   |  __  |   | || |   |  _|  _   | | \n";
    cout << "| |    _| |_     | || |  _| |  | |_  | || |  _| |___/ |  | | \n";
    cout << "| |   |_____|    | || | |____||____| | || | |_________|  | | \n";
    cout << "| |              | || |              | || |              | | \n";
    cout << "| '--------------' || '--------------' || '--------------' | \n";
    cout << " '----------------'  '----------------'  '----------------' \n";
    cout << " .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------. \n";
    cout << "| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |\n";
    cout << "| |    _______   | || |     ____     | || |  _______     | || |  _________   | || |  _________   | || |  _______     | |\n";
    cout << "| |   /  ___  |  | || |   .'    `.   | || | |_   __ \\    | || | |  _   _  |  | || | |_   ___  |  | || | |_   __ \\    | |\n";
    cout << "| |  |  (__ \\_|  | || |  /  .--.  \\  | || |   | |__) |   | || | |_/ | | \\_|  | || |   | |_  \\_|  | || |   | |__) |   | |\n";
    cout << "| |   '.___`-.   | || |  | |    | |  | || |   |  __ /    | || |     | |      | || |   |  _|  _   | || |   |  __ /    | |\n";
    cout << "| |  |`\\____) |  | || |  \\  `--'  /  | || |  _| |  \\ \\_  | || |    _| |_     | || |  _| |___/ |  | || |  _| |  \\ \\_  | |\n";
    cout << "| |  |_______.'  | || |   `.____.'   | || | |____| |___| | || |   |_____|    | || | |_________|  | || | |____| |___| | |\n";
    cout << "| |              | || |              | || |              | || |              | || |              | || |              | |\n";
    cout << "| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |\n";
    cout << " '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' \n";
    cout << "\n";
    cout << "Est. 2020\n";
    cout << "by Patrick Harris, Riley Rodriguez, and Connor Short\n";
    cout << "\n";
    cout << "VERSION: [1.0.0]\n\n\n";
}

//loading bar to add to aesthetic, can easily be disabled
void loadingBar() {
    cout << "[";
    for (int i = 1; i <= 70; i++) {
        for (int j = 0; j < i - 1; j++) {
            cout << "=";
        }
        cout << ">";
        for (int j = i; j < 70; j++) {
            cout << " ";
        }
        cout << "] INITIALIZING ";
        Sleep(1);
        for (int j = 0; j < 86; j++) {
            cout << "\b";
        }
    }
    cout << "\n\n\n";
}

//introduces the program
void intro() {
    cout << "Welcome to THE SORTER, a data sorting testing suite.\n\n";
    Sleep(1000);
}

//establishes a data set to use and returns a path to that set
pair<string, int> dataSet() {
    bool finished = false;
    string fileName;
    int amount;
    while (finished == false) {
        cout << "To start, enter \'generate\' if you want to create a random set, or enter \'test\' \nif you would like to test your own data set.\n";
        string choice;
        cin >> choice;
        cout << "\n";
        if (choice == "generate") {
            int max;
            int min;
            cout << "Enter the following values separated by spaces: The amount of numbers in your dataset, the \nminimum value, and the maximum value (ex. \'100 1 10\' for 100 values between 1 and 10)\n";
            cin >> amount;
            cin >> min;
            cin >> max;
            generateFile("random.txt", amount, min, max);
            fileName = "random.txt";
            finished = true;
        }
        else if (choice == "test") {
            cout << "Enter a path to your dataset and the number of values separated by a space \n(ex. \'data.txt 100\'):\n";
            cin >> fileName;
            cin >> amount;
            finished = true;
        }
        cout << "\n";
    }
    return make_pair(fileName, amount);
}

//provides a descriptor for a number
string descriptor(int num) {
    switch (num) {
    case 1: return "";
    case 2: return "second ";
    case 3: return "third ";
    case 4: return "fourth ";
    case 5: return "fifth ";
    case 6: return "sixth ";
    case 7: return "seventh ";
    case 8: return "eighth ";
    }
}

//the following functions time their respective sort and return the time it took, as well as outputting the sorted data if requested
long timeSelect(string fileName, int size, bool output, string results = "") {
    int* array = generateArray(fileName, size);
    auto start = high_resolution_clock::now();
    selectionSort(array, size);
    auto end = high_resolution_clock::now();
    auto time = duration_cast<milliseconds>(end - start);
    if (output) createOutput(results, size, array);
    delete[] array;
    return time.count();
}

long timeBubble(string fileName, int size, bool output, string results = "") {
    int* array = generateArray(fileName, size);
    auto start = high_resolution_clock::now();
    bubbleSort(array, size);
    auto end = high_resolution_clock::now();
    auto time = duration_cast<milliseconds>(end - start);
    if (output) createOutput(results, size, array);
    delete[] array;
    return time.count();
}

long timeInsert(string fileName, int size, bool output, string results = "") {
    int* array = generateArray(fileName, size);
    auto start = high_resolution_clock::now();
    insertionSort(array, size);
    auto end = high_resolution_clock::now();
    auto time = duration_cast<milliseconds>(end - start);
    if (output) createOutput(results, size, array);
    delete[] array;
    return time.count();
}

long timeQuick(string fileName, int size, bool output, string results = "") {
    int* array = generateArray(fileName, size);
    auto start = high_resolution_clock::now();
    quickSort(array, 0, size - 1);
    auto end = high_resolution_clock::now();
    auto time = duration_cast<milliseconds>(end - start);
    if (output) createOutput(results, size, array);
    delete[] array;
    return time.count();
}

long timeMerge(string fileName, int size, bool output, string results = "") {
    int* array = generateArray(fileName, size);
    auto start = high_resolution_clock::now();
    mergeSort(array, 0, size - 1);
    auto end = high_resolution_clock::now();
    auto time = duration_cast<milliseconds>(end - start);
    if (output) createOutput(results, size, array);
    delete[] array;
    return time.count();
}

long timeHeap(string fileName, int size, bool output, string results = "") {
    int* array = generateArray(fileName, size);
    auto start = high_resolution_clock::now();
    heapSort(array, size);
    auto end = high_resolution_clock::now();
    auto time = duration_cast<milliseconds>(end - start);
    if (output) createOutput(results, size, array);
    delete[] array;
    return time.count();
}

long timeShell(string fileName, int size, bool output, string results = "") {
    int* array = generateArray(fileName, size);
    auto start = high_resolution_clock::now();
    shellSort(array, size);
    auto end = high_resolution_clock::now();
    auto time = duration_cast<milliseconds>(end - start);
    if (output) createOutput(results, size, array);
    delete[] array;
    return time.count();

}

int main()
{
    int animations = 1;
    string sorted = "sorted.txt";
    string results = "results.txt";

    //keep track of which sorts have been conducted and their times
    bool select = false, heap = false, merge = false, quick = false, insert = false, shell = false, bubble = false;
    long selectTime = 0, heapTime = 0, mergeTime = 0, quickTime = 0, insertTime = 0, shellTime = 0, bubbleTime = 0;
    bool sortOutput = false;

    cout << "Type \'n\' or \'y\' for animations:\n";
    string input;
    cin >> input;
    if (input == "n" || input == "no animations") {
        animations = 0;
    }
    splash();
    if (animations == 1) loadingBar();
    intro();

    //establish the data file we will be using and how many elements it has
    pair<string, int> data = dataSet();
    string fileName = data.first;
    int size = data.second;

    bool testing = true;
    //main loop
    while (testing) {
        cout << "Enter a number corresponding to the type of sort you want, or 0 to exit:\n";
        cout << " |-0 EXIT\n";
        cout << " |-1 Selection Sort\n";
        cout << " |-2 Bubble Sort\n";
        cout << " |-3 Insertion Sort\n";
        cout << " |-4 Quick Sort\n";
        cout << " |-5 Merge Sort\n";
        cout << " |-6 Heap Sort\n";
        cout << " |-7 Shell Sort\n";
        cout << " |-8 Full Sorting Suite\n";
        cout << " |-9 Rank all previously conducted sorts\n";
        cout << " |-10 Graph all previously conducted sorts\n";
        int choice;
        cin >> choice;
        switch (choice) {
        case 0: {
            testing = false;
            ofstream output;
            output.open(results);
            if (select) output << "Selection Sort: " << selectTime << " milliseconds\n";
            if (bubble) output << "Bubble Sort: " << bubbleTime << " milliseconds\n";
            if (insert) output << "Insertion Sort: " << insertTime << " milliseconds\n";
            if (quick) output << "Quick Sort: " << quickTime << " milliseconds\n";
            if (merge) output << "Merge Sort: " << mergeTime << " milliseconds\n";
            if (heap) output << "Heap Sort: " << heapTime << " milliseconds\n";
            if (shell) output << "Shell Sort: " << shellTime << " milliseconds\n";
            cout << "You are now exiting the program. Remember to find your test results in results.txt and your sorted data in sorted.txt,\nas these will be overwritten in the next run.";
            cout << "\n Press enter to exit.";
            cin;
            break; }
        case 1:
            selectTime = timeSelect(fileName, size, !sortOutput, sorted);
            if (sortOutput == false) sortOutput = true;
            select = true;
            cout << "\nYour data took " << selectTime << " milliseconds to sort using a selection sort.\n\n";
            break;
        case 2:
            bubbleTime = timeBubble(fileName, size, !sortOutput, sorted);
            if (sortOutput == false) sortOutput = true;
            bubble = true;
            cout << "\nYour data took " << bubbleTime << " milliseconds to sort using a bubble sort.\n\n";
            break;
        case 3:
            insertTime = timeInsert(fileName, size, !sortOutput, sorted);
            if (sortOutput == false) sortOutput = true;
            insert = true;
            cout << "\nYour data took " << insertTime << " milliseconds to sort using an insertion sort.\n\n";
            break;
        case 4:
            quickTime = timeQuick(fileName, size, !sortOutput, sorted);
            if (sortOutput == false) sortOutput = true;
            quick = true;
            cout << "\nYour data took " << quickTime << " milliseconds to sort using an quick sort.\n\n";
            break;
        case 5:
            mergeTime = timeMerge(fileName, size, !sortOutput, sorted);
            if (sortOutput == false) sortOutput = true;
            merge = true;
            cout << "\nYour data took " << mergeTime << " milliseconds to sort using a merge sort.\n\n";
            break;
        case 6:
            heapTime = timeHeap(fileName, size, !sortOutput, sorted);
            if (sortOutput == false) sortOutput = true;
            heap = true;
            cout << "\nYour data took " << heapTime << " milliseconds to sort using a heap sort.\n\n";
            break;
        case 7:
            shellTime = timeShell(fileName, size, !sortOutput, sorted);
            if (sortOutput == false) sortOutput = true;
            shell = true;
            cout << "\nYour data took " << shellTime << " milliseconds to sort using a shell sort.\n\n";
            break;
        case 8:
            selectTime = timeSelect(fileName, size, !sortOutput, sorted);
            if (sortOutput == false) sortOutput = true;
            select = true;
            cout << "\nYour data took " << selectTime << " milliseconds to sort using a selection sort.\n\n";

            bubbleTime = timeBubble(fileName, size, !sortOutput, sorted);
            bubble = true;
            cout << "Your data took " << bubbleTime << " milliseconds to sort using a bubble sort.\n\n";

            insertTime = timeInsert(fileName, size, !sortOutput, sorted);
            insert = true;
            cout << "Your data took " << insertTime << " milliseconds to sort using an insertion sort.\n\n";

            quickTime = timeQuick(fileName, size, !sortOutput, sorted);
            quick = true;
            cout << "Your data took " << quickTime << " milliseconds to sort using an quick sort.\n\n";

            mergeTime = timeMerge(fileName, size, !sortOutput, sorted);
            merge = true;
            cout << "Your data took " << mergeTime << " milliseconds to sort using a merge sort.\n\n";

            heapTime = timeHeap(fileName, size, !sortOutput, sorted);
            heap = true;
            cout << "Your data took " << heapTime << " milliseconds to sort using a heap sort.\n\n";

            shellTime = timeShell(fileName, size, !sortOutput, sorted);
            shell = true;
            cout << "Your data took " << shellTime << " milliseconds to sort using a shell sort.\n\n";
            break;

        case 9:
        {
            map<long, vector<string>> sorts;
            if (select) sorts[selectTime].push_back("Selection Sort:");
            if (bubble) sorts[bubbleTime].push_back("Bubble Sort:   ");
            if (insert) sorts[insertTime].push_back("Insertion Sort:");
            if (quick) sorts[quickTime].push_back("Quick Sort:    ");
            if (merge) sorts[mergeTime].push_back("Merge Sort:    ");
            if (heap) sorts[heapTime].push_back("Heap Sort:     ");
            if (shell) sorts[shellTime].push_back("Shell Sort:    ");
            int count = 0;
            cout << "\n";
            for (map<long, vector<string>>::iterator i = sorts.begin(); i != sorts.end(); ++i) {
                cout << "The " << descriptor(++count) << "fastest sort was: " << i->second[0] << " with a time of: " << i->first << " milliseconds\n";
                if (i->second.size() > 1) {
                    for (int j = 1; j < i->second.size(); j++) {
                        cout << "    tied with: " << i->second[j] << i->first << " milliseconds\n";
                        count++;
                    }
                }
            }
            cout << "\n";
            break;
        }
        case 10:
        {
            map<long, vector<string>> sorts;
            if (select) sorts[selectTime].push_back("Selection Sort:");
            if (bubble) sorts[bubbleTime].push_back("Bubble Sort:   ");
            if (insert) sorts[insertTime].push_back("Insertion Sort:");
            if (quick) sorts[quickTime].push_back("Quick Sort:    ");
            if (merge) sorts[mergeTime].push_back("Merge Sort:    ");
            if (heap) sorts[heapTime].push_back("Heap Sort:     ");
            if (shell) sorts[shellTime].push_back("Shell Sort:    ");
            int count = 0;
            cout << "\n";
            map<long, vector<string>>::iterator last = sorts.end();
            last--;
            float max = (float)(last)->first;
            for (map<long, vector<string>>::iterator i = sorts.begin(); i != sorts.end(); ++i) {
                for (int j = 0; j < i->second.size(); j++) {
                    float ratio = ((float)(i->first)) / max;
                    float floatAmount = ratio * 80;
                    int amount = (int)floatAmount;
                    cout << i->second[j] << ": ";
                    for (int k = 0; k < amount; k++) {
                        cout << "=";
                        Sleep(animations * 50);
                    }
                    cout << " " << i->first << " milliseconds\n";
                }
            }
            cout << "\n";
            break;
        }
        }

    }

}

