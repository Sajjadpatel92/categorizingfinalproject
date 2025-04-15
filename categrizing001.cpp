#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
    Node* head;
public:
    LinkedList() : head(nullptr) {}

    void insertEnd(int val) {
        Node* newNode = new Node(val);
        if (!head) head = newNode;
        else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
        cout << "Inserted " << val << " at the end."<<endl;
    }

    void deleteValue(int val) {
        if (!head) {
            cout << "List is empty."<<endl;
            return;
        }
        if (head->data == val) {
            Node* del = head;
            head = head->next;
            delete del;
            cout << "Deleted " << val << "."<<endl;
            return;
        }
        Node* temp = head;
        while (temp->next && temp->next->data != val)
            temp = temp->next;
        if (temp->next) {
            Node* del = temp->next;
            temp->next = temp->next->next;
            delete del;
            cout << "Deleted " << val << "."<<endl;
        } else cout << "Value not found."<<endl;
    }

    void reverse() {
        Node* prev = nullptr;
        Node* current = head;
        while (current) {
            Node* nextNode = current->next;
            current->next = prev;
            prev = current;
            current = nextNode;
        }
        head = prev;
        cout << "Linked list reversed."<<endl;
    }

    void display() {
        if (!head) {
            cout << "List is empty."<<endl;
            return;
        }
        cout << "List: ";
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    ~LinkedList() {
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};


void merge(vector<int>& a, int l, int m, int r) {
    vector<int> L(a.begin() + l, a.begin() + m + 1);
    vector<int> R(a.begin() + m + 1, a.begin() + r + 1);
    int i = 0, j = 0, k = l;
    while (i < L.size() && j < R.size())
        a[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < L.size()) a[k++] = L[i++];
    while (j < R.size()) a[k++] = R[j++];
}

void mergeSort(vector<int>& a, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(a, l, m);
    mergeSort(a, m + 1, r);
    merge(a, l, m, r);
}


int partition(vector<int>& a, int low, int high) {
    int pivot = a[high], i = low - 1;
    for (int j = low; j < high; ++j)
        if (a[j] < pivot) swap(a[++i], a[j]);
    swap(a[i + 1], a[high]);
    return i + 1;
}

void quickSort(vector<int>& a, int low, int high) {
    if (low < high) {
        int p = partition(a, low, high);
        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
    }
}


int binarySearch(const vector<int>& a, int target) {
    int low = 0, high = a.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (a[mid] == target) return mid;
        else if (a[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}


bool isSorted(const vector<int>& a) {
    return is_sorted(a.begin(), a.end());
}


int main() {
    LinkedList list;
    vector<int> array;
    int choice;

    do {
        
        cout << "\n|------------ Menu -----------|\n";
        cout << "|1. Insert into Linked List   |\n";
        cout << "|2. Delete from Linked List   |\n";
        cout << "|3. Reverse Linked List       |\n";
        cout << "|4. Display Linked List       |\n";
        cout << "|5. Enter Array               |\n";
        cout << "|6. Sort Array (Choose Method)|\n";
        cout << "|7. Binary Search in Array    |\n";
        cout << "|8. Display Array             |\n";
        cout << "|0. Exit                      |\n";
        cout << "|Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int val;
                cout << "| Enter value to insert: ";
                cin >> val;
                list.insertEnd(val);
                break;
            }
            case 2: {
                int val;
                cout << "| Enter value to delete: ";
                cin >> val;
                list.deleteValue(val);
                break;
            }
            case 3:
                list.reverse();
                break;
            case 4:
                list.display();
                break;
            case 5: {
                int n;
                cout << "| Enter size of array:  | ";
                cin >> n;
                array.resize(n);
                cout << "Enter array elements:\n";
                for (int i = 0; i < n; ++i) cin >> array[i];
                break;
            }
            case 6: {
                if (array.empty()) {
                    cout << "Array is empty.\n";
                    break;
                }
                int sortChoice;
                cout << "1. Merge Sort\n2. Quick Sort\nChoose sort method: ";
                cin >> sortChoice;
                if (sortChoice == 1) {
                    mergeSort(array, 0, array.size() - 1);
                    cout << "Array sorted using Merge Sort.\n";
                }
                else if (sortChoice == 2) {
                    quickSort(array, 0, array.size() - 1);
                    cout << "Array sorted using Quick Sort.\n";
                }
                else {
                    cout << "Invalid sort choice.\n";
                    break;
                }
            
                // Show the sorted array
                cout << "| Sorted Array: ";
                for (int x : array) cout << x << " ";
                cout << endl;
            
                break;
            }
            
            case 7: {
                if (!isSorted(array)) {
                    cout << "| Array is not sorted. Please sort it before searching.\n";
                    break;
                }
                int key;
                cout << "|Enter value to search: ";
                cin >> key;
                int res = binarySearch(array, key);
                if (res != -1) cout << "Found at index: " << res << endl;
                else cout << "Not found.\n";
                break;
            }
            case 8:
                cout << "Array: ";
                for (int x : array) cout << x << " ";
                cout << endl;
                break;
            case 0:
                cout << "Exit.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}