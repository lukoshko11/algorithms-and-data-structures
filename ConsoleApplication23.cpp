#include <iostream>
#include <chrono>
#include <limits>
#include "sspisok.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>



using namespace std;
using namespace chrono;

map <string, int> weight = { {"+", 1 },
                             {"-", 1 },
                             {"*", 2 },
                             {"/", 2 },
                             {"^", 3},
                             {"(", 0 },
                             {")", 0 },
                             {"sin", 4},
                             {"cos",4},
                             {" ", -1},
};
const string operations[] = {
    "*", "/", "-", "+", "^",
    "(", ")",
    "sin", "cos"
};
int checking() {
    int a;
    while (true)
    {
        cin >> a;
        if (std::cin.fail())
        {
            cout << "Invalid input\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue;
        }
        break;
    }
    return a;
}
char checking1() {
    char a;
    while (true)
    {
        cin >> a;
        if (std::cin.fail())
        {
            cout << "Invalid input\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue;
        }
        break;
    }
    return a;
}

struct Stack {
    string value;
    Stack* next = NULL;
};
struct Node {
    int data;
    Node* next;
    Node* pred;
};

class DynArray {
private:
    unsigned size = 0;
    unsigned capacity = 10;
    int* array = new int[capacity];
public:

    DynArray();
    explicit DynArray(unsigned size, int value = 0);
    explicit DynArray(unsigned, const int*);
    ~DynArray();

    DynArray& operator= (const DynArray&);
    friend std::ostream& operator<< (std::ostream&, DynArray&);
    int* operator[] (int);

    int* get(int);
    int find(int);
    void resize(unsigned);
    void append(int);
    void insert(unsigned, int);
    void remove(unsigned);
    [[nodiscard]] unsigned getSize() const;
    [[nodiscard]] unsigned getCapacity() const;
    [[nodiscard]] bool isEmpty() const;
};


void printList(Node* head) {
    cout << "List: ";
    while (head) {
        cout << head->data << " ";
        head = head->next;
    }
}
void deleteList(Node*& list) {
    Node* Next;
    while (list)
    {
        Next = list->next;
        delete list;
        list = Next;
    }
}

Node* createList(unsigned size) {
    Node* head = nullptr,
        * tail = nullptr;

    //srand(time(nullptr));
    for (int i = 0; i < size; i++) {
        head = new Node;
        head->data = rand() % 100;
        head->next = tail;
        if (tail) {
            tail->pred = head;
        }
        tail = head;
    }
    if (size != 0) head->pred = nullptr;

    return head;
}
Node* createListFromInput() {
    Node* head = nullptr;
    Node* tail = nullptr;
    int input;
    while (true) {
        input = checking();


        if (input == 0) return head;

        auto* curr = new struct Node;
        curr->data = input;

        curr->next = nullptr;
        if (tail) {
            tail->next = curr;
            curr->pred = tail;
        }
        else {
            curr->pred = nullptr;
            head = curr;
        }
        tail = curr;
    }
}
Node* getItemByIndex(Node* head, int index) {
    if (!head) {
        cout << "List is empty\n";
        return nullptr;
    }

    for (int i = 0; i < index; ++i) {
        if (!head->next) {
            cout << "Index out of range\n";
            return nullptr;
        }
        head = head->next;
    }

    return head;
}

Node* listofValue(Node* Head, unsigned int index) {
    int id = 0;
    while (id != index) {
        Head = Head->next;
        id++;
    }
    return Head;
}
Node* getItemByValue(struct Node* head, int value) {
    if (!head) {
        cout << "List is empty\n";
        return nullptr;
    }


    while (head) {
        if (head->data == value) break;

        if (!head->next) {
            cout << "Item not found\n";
            return nullptr;
        }
        head = head->next;
    }

    return head;
}

bool insertItem(Node*& head) {
    int index, value;
    cout << " Input index:\n ";
    index = checking();
    cout << " Input value:\n ";
    value = checking();

    struct Node* point = getItemByIndex(head, index);
    if (!point) return false;

    auto* newNode = new struct Node;
    newNode->data = value;
    newNode->pred = point->pred;
    newNode->next = point;
    if (newNode->pred) newNode->pred->next = newNode;
    if (newNode->next) newNode->next->pred = newNode;

    if (index == 0) head = newNode;

    return true;
}


void inputList1(Node*& list, int& length) {
    cout << "Print the input type (1 - random, 2 - ourselves): ";
    int input = checking();
    int size;
    string stringList;
    if (input == 1) {
        cout << " Input size: \n";
        size = checking();
        if (size <= 0) {
            cout << "Invalid input.\n";
            inputList1(list, length);
        }
        length = size;
        list = createList(length);

    }
    else if (input == 2) {
        cout << " Input list: \n";
        list = createListFromInput();

    }
    else {
        cout << "Invalid input.\n";
        inputList1(list, length);
    }


}

void deleteItem(struct Node*& head) {
    int index;
    cout << " Input index:\n ";
    index = checking();
    if (!head) return;

    struct Node* found = getItemByIndex(head, index - 1);
    if (!found) return;


    found->pred ? found->pred->next = found->next : head = found->next;
    found->next ? found->next->pred = found->pred : nullptr;
    delete found;

}
void deleteItemByValue(struct Node*& head) {
    int value;
    cout << " Input value:\n ";
    value = checking();

    if (!head) return;


    struct Node* point = getItemByValue(head, value);
    if (!point) return;


    point->pred ? point->pred->next = point->next : head = point->next;
    point->next ? point->next->pred = point->pred : nullptr;
    delete point;

}
pair<Node*, Node*> find(Node*& head, int index1, int index2)
{
    Node* curr1 = nullptr;
    Node* curr2 = nullptr;
    Node* temp = head;


    while (temp != nullptr) {
        if (temp->data == index1)
            curr1 = temp;
        else if (temp->data == index2)
            curr2 = temp;
        temp = temp->next;
    }
    return make_pair(curr1, curr2);
}

void swapByIndex(Node*& list, int length) {
    int index1, index2;
    cout << " Input 2 indexes you wanna change:";
    index1 = checking();
    index2 = checking();
    if (!((index1 >= 1 && index1 <= length) && (index2 >= 1 && index2 <= length))) {
        cout << "Wrong input!\n";
        return;
    }
    if (index1 == index2) return;
    index1--; index2--;
    if (index1 > index2) {
        swap(index1, index2);
    }

    Node* curr1 = listofValue(list, index1);
    Node* curr2 = listofValue(list, index2);
    if (curr1->pred != nullptr) {
        curr1->pred->next = curr2;
    }
    else {
        list = curr2;
    }
    if (curr1->next != curr2) {
        curr1->next->pred = curr2;
    }
    if (curr2->pred != curr1) {
        curr2->pred->next = curr1;
    }
    if (curr2->next != nullptr) {
        curr2->next->pred = curr1;
    }
    if (curr1->next == curr2) {
        curr2->pred = curr1->pred;
        curr1->pred = curr2;
        curr1->next = curr2->next;
        curr2->next = curr1;

        return;
    }
    Node* nope = curr1->pred;
    curr1->pred = curr2->pred;
    curr2->pred = nope;
    nope = curr1->next;
    curr1->next = curr2->next;
    curr2->next = nope;

}
void getValue(Node*& list, int length) {
    cout << " Choose the parameter to search:\n" <<
        "  1. by value\n"
        "  2. by index\n";
    int type, value, index, cnt = 0;
    bool flag = false;
    Node* head = list;
    type = checking();

    switch (type) {
    case 1:
        cout << "Input value:";
        value = checking();

        while (head) {
            if (head->data == value) {
                flag = true;
                index = cnt;
                break;
            }
            head = head->next;
            cnt++;
        }
        if (flag) {
            cout << "Element - " << value << " found (index - " << index << ")" << "\n";
        }
        else {
            cout << "Element - " << value << "does not exist in the list." << "\n";
        }

        break;
    case 2:
        cout << " Input index:";
        index = checking();
        while (!(index >= 1 && index <= length)) {
            cout << "Wrong input!\n";
            index = checking();
        }
        head = listofValue(list, index - 1);
        cout << "Value with index " << index << " - " << head->data << "\n";

        break;
    default:
        cout << "Wrong input!\n";
        break;
    }
}
void inputList2(Node*& list, int& length) {
    cout << " Choose an action:\n";
    int inputType = 0;
    if (length > 0) {
        cout << "  1. Add value\n" <<
            "  2. Get element\n" <<
            "  3. Change the elements\n" <<
            "  4. Delete value\n";
        inputType = checking();

    }
    else {
        cout <<
            "  1. Add value\n" <<
            "  2. Get element\n" <<
            "  3. Change the elements\n";
        inputType = checking();
    }
    switch (inputType) {
    case 1: {
        if (!insertItem(list))
            break;

        cout << "Item inserted successful. \n ";
        break;
    }

    case 2: {
        getValue(list, length);
        break;
    }
    case 3: {
        swapByIndex(list, length);
        break;
    }
    case 4: {
        cout << " Choose the parameter to search:\n";
        cout << "  1. Index\n";
        cout << "  2. Value\n";
        int input;
        input = checking();
        if (input != 2 && input != 1) {
            cout << "Wrong input!\n";
            return;
        }
        if (input == 1) {
            deleteItem(list);
        }
        else {
            deleteItemByValue(list);

        }
        break;
    }
    }
}

bool contains(string s, string substr, size_t at) {
    for (size_t i = at; i < s.size() && (i - at) < substr.size(); i++)
        if (s[i] != substr[i - at])
            return false;
    return true;
}

void push(Stack*& head, string value) {
    Stack* tmp = new Stack;
    tmp->value = value;
    if (head == NULL) {
        head = tmp;
        tmp->next = NULL;
    }
    else {
        if (head->value == "") {
            head->value = value;
            return;
        }
        tmp->next = head;
        head = tmp;
    }
}

string pop(Stack*& head) {
    Stack* prev = NULL;
    string value;
    if (head == NULL) {
        exit(-1);
    }
    prev = head;
    value = prev->value;
    head = head->next;
    free(prev);
    return value;
}

string top(Stack*& head) {
    if (head == NULL) {
        cout << "Stack is empty";
        return "";
    }
    return head->value;
}


string printStack(Stack* head) {
    string res = "";
    while (!(head == NULL)) {
        res += head->value;
        res += " ";
        head = head->next;
    }
    return res;
}

int sizeStack(Stack* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

void deleteStack(Stack*& head) {
    while (head) {
        Stack* stack = head;
        head = head->next;
        delete stack;
    }
}

bool isOperation(const string& str, map <string, int> map_) {
    auto res = map_.find(str);
    return !(res == map_.end());
}

bool checkWeight(Stack*& stack, const string& str, map <string, int> map_) {
    auto res = map_.at(str);
    auto res1 = map_.at(top(stack));
    if (res1 >= res) return true;
    else return false;
}

string vecToString(vector<string> v) {
    string result_s;
    for (string& tok : v)
        result_s += tok + ' ';
    return result_s;
}

double calculation(double value1, double value2, string operation) {
    switch (operation[0]) {
    case '+':
        return value1 + value2;
    case '-':
        return value1 - value2;
    case '*':
        return value1 * value2;
    case '/':
        return value1 / value2;
    case '^':
        return pow(value1, value2);
    case 's':
        return sin(value1);
    case 'c':
        return cos(value1);

    default:
        break;
    }
}

vector<string> newString(string str) {
    vector<string> temp;
    string str1 = "";
    for (char i : str) {
        string symvol(1, i);
        if (isOperation(symvol, weight)) {
            if (str1 != " " && str1 != "") temp.push_back(str1);
            str1 = i;
            if (str1 != " " && str1 != "") temp.push_back(str1);
            str1 = "";
        }
        else if (i >= '0' && i <= '9') {
            str1 += i;
        }
        else {
            temp.clear();
            return temp;
        }
    }
    if (str1 != "" && str1 != " ") temp.push_back(str1);
    return temp;
}
vector<string> tokenize(string text) {
    vector<string> tokens;
    text.erase(std::remove(text.begin(), text.end(), ' '), text.end());

    string current = "";
    for (size_t i = 0; i < text.size(); i++) {
        current.clear();
        if (isdigit(text[i])) {
            current += text[i];
            for (i++; i < text.size() && (isdigit(text[i]) || text[i] == '.'); i++) current += text[i];
            tokens.push_back(current);
            if (i < text.size() && (isalpha(text[i]) || text[i] == '(')) tokens.push_back("*");
            i--;
            continue;
        }
        bool matched = false;
        for (auto& op : operations) {
            if (contains(text, op, i)) {
                i += op.size() - 1;
                tokens.push_back(op);
                matched = true;
                break;
            }
        }
        if (!matched)
            throw std::runtime_error("Invalid characters in line");
    }
    return tokens;
}

vector<string> polishNotation(Stack*& stack, string str, string& res) {
    vector<string> result;
    vector<string> temp = tokenize(str);

    for (int i = 0; i < temp.size(); i++) {
        if (isOperation(temp[i], weight)) {
            if (temp[i] == "(") {
                push(stack, temp[i]);
                continue;
            }
            if (temp[i] == ")") {
                while (top(stack) != "(" && !(stack == NULL)) {
                    result.push_back(pop(stack));
                }
                pop(stack);
            }
            else {
                if (!((stack == NULL) || !checkWeight(stack, temp[i], weight))) {
                    while (stack && checkWeight(stack, temp[i], weight)) {
                        result.push_back(pop(stack));
                    }
                }
                push(stack, temp[i]);
            }
        }
        else {
            result.push_back(temp[i]);
        }

        res += "Стек выхода:" + vecToString(result) + " Стек операций:" + printStack(stack) + "\n";
    }
    while (!(stack == NULL)) {
        result.push_back(pop(stack));
    }
    return result;
}

string calculation(Stack*& stack, vector<string> str) {
    for (int i = 0; i < str.size(); i++) {
        if (isOperation(str[i], weight)) {
            if (str[i] == "sin" || str[i] == "cos") {
                double x = calculation(atof(pop(stack).c_str()), 0, str[i]);
                push(stack, to_string(x));
            }
            else {
                if (sizeStack(stack) < 2) return "Ошибка!";
                double x = calculation(atof(pop(stack).c_str()), atof(pop(stack).c_str()), str[i]);
                push(stack, to_string(x));
            }
        }
        else {
            push(stack, str[i]);
        }
    }
    if (sizeStack(stack) == 1) return pop(stack);
    else {
        return "Ошибка!";
    }
}


int dai_chislo() {
    int value = 0;
    cin >> value;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

void vivod_spiska(spisok* list) {
    if (list) {
        for (int i = 0; i < list->length; i++)
            cout << get_spisok(list, i)->data << " ";
    }
    else
        cout << "spisok is not exist\n";
}

void sluchayniy_spisok(spisok*& list, unsigned n) {
    list = sozdat_spisok();
    list->length = n;

    node* prev = new node;
    prev->data = rand() % 100;
    list->head = prev;
    if (n != 0) {
        n--;
        while (n--) {
            node* curr = new node;
            curr->data = rand() % 100;
            prev->next = curr;
            curr->prev = prev;
            prev = curr;
        }
    }
}

void svoy_spisok(spisok*& list) {
    cout << "input numbers\n";
    list = sozdat_spisok();

    int val;
    node* prev = 0;
    bool flag = true;
    while (flag) {
        cin >> val;
        if (cin.fail())
            break;

        if (list->length == 0) {
            prev = new node;
            prev->data = val;
            list->head = prev;
        }
        else {
            node* curr = new node;
            curr->data = val;
            curr->prev = prev;
            if (prev)
                prev->next = curr;
            prev = curr;
        }
        list->length++;
        if (!val) {
            flag = false;
        }
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
};

template <typename NumType>

bool inputNumber(NumType& variable, bool isSpaceSep = false, bool isUnsigned = false) {
    std::cin >> variable;
    if (cin.fail() || (isUnsigned && variable < 0) || (isSpaceSep && cin.peek() != '\n')) {
        cout << "Invalid input\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return false;
    }
    return true;
}


DynArray::DynArray() = default;
DynArray::DynArray(unsigned n, int value) {
    size = n;
    capacity = size * 2;
    array = new int[capacity];
    for (unsigned i = 0; i < size; ++i)
        array[i] = value;
}

DynArray::DynArray(unsigned n, const int* values) {
    size = n;
    capacity = size * 2;
    array = new int[capacity];
    for (unsigned i = 0; i < size; ++i)
        array[i] = values[i];
}

DynArray::~DynArray() {
    delete[] array;
}


DynArray& DynArray::operator= (const DynArray& rhs) {

    if (this == &rhs) return *this;

    delete[] array;

    size = rhs.size;
    capacity = rhs.capacity;
    array = new int[capacity];
    for (int i = 0; i < size; ++i)
        array[i] = rhs.array[i];

    return *this;
}

std::ostream& operator<< (std::ostream& os, DynArray& arr) {
    for (int i = 0; i < arr.getSize(); ++i)
        cout << *arr[i] << ' ';
    return os;
}

int* DynArray::operator[] (int index) {
    return get(index);
}

int* DynArray::get(int index) {
    if (isEmpty()) {
        cout << "IndexError: The array is empty\n";
        return nullptr;
    }
    else if (abs(index) > getSize()) {
        cout << "IndexError: Index out of range\n";
        return nullptr;
    }
    else if (index < 0) {
        index = int(getSize()) + index;
    }

    return &array[index];
}

int DynArray::find(int value) {
    for (int i = 0; i < getSize(); ++i)
        if (array[i] == value) return i;
    return -1;
}

void DynArray::resize(unsigned newSize) {
    if (newSize == size)
        return;

    if (newSize < size) {
        size = newSize;
        if (size < capacity / 2)
            capacity /= 2;
        return;
    }

    if (newSize > capacity) {
        capacity *= 2;

        int* newArray = new int[capacity];
        for (unsigned i = 0; i < size; ++i)
            newArray[i] = array[i];

        delete[] array;
        array = newArray;
    }

    for (unsigned i = size; i < newSize; ++i)
        array[i] = 0;

    size = newSize;
}


void DynArray::append(int value) {
    resize(size + 1);
    array[size - 1] = value;
}

void DynArray::insert(unsigned index, int value) {
    if (index >= size) {
        cout << "IndexError: Index out of range\n";
        return;
    }

    resize(size + 1);
    for (unsigned i = size - 1; i > index; --i)
        array[i] = array[i - 1];

    array[index] = value;
}

void DynArray::remove(unsigned index) {
    if (index >= size) {
        cout << "IndexError: Index out of range\n";
        return;
    }

    for (unsigned i = index; i < size - 1; ++i)
        array[i] = array[i + 1];
    resize(size - 1);
}

unsigned DynArray::getSize() const {
    return size;
}

unsigned DynArray::getCapacity() const {
    return capacity;
}

bool DynArray::isEmpty() const {
    return size == 0;
}
int list() {
    Node* list = nullptr;
    int enter = 1, length = 0;

    while (enter) {

        inputList1(list, length);

        while (list == nullptr) {
            cout << "The list is empty.\n";
            inputList1(list, length);
        }

        printList(list);
        cout << "\n";
        cout << "\nDo you want to repeat it? (0 - no, 1 - yes): ";

        enter = checking();
    }
    enter = 1;
    while (enter) {

        while (list == nullptr) {
            cout << "The list is empty.\n";
            inputList1(list, length);
        }

        inputList2(list, length);
        printList(list);
        cout << "\n";
        cout << "\nDo you want to repeat it? (0 - no, 1 - yes): ";

        enter = checking();
    }

    deleteList(list);
    return 0;
}

int main() {
    setlocale(LC_ALL, "Russian");

    Stack* stack = new Stack;
    string str1, value,
        res = "";
    vector<string> polishStr;
    bool flag = true;

    while (flag) {
        ifstream file("ttext.txt");
        if (file.is_open()) {
            while (getline(file, str1)) {
                res += "Выражение:" + str1 + "\n";
                str1.erase(remove_if(str1.begin(), str1.end(), ::isspace), str1.end());
                deleteStack(stack);
                polishStr = polishNotation(stack, str1, res);
                deleteStack(stack);
                value = calculation(stack, polishStr);
                res += "ОПН: " + vecToString(polishStr);
                res += "\nОтвет: " + value + "\n\n";
            }
        }
        file.close();
        flag = false;
    }
    flag = true;
    while (flag) {
        ofstream outputFile("result.txt", ios::out | ios::trunc);
        if (outputFile.is_open()) {
            outputFile << res;
        }
        outputFile.close();
        flag = false;
    }
    cout << res;
    system("pause");


    bool dish = true;
    spisok* list = 0;
    while (dish) {
        vivod_spiska(list);
        cout << "\tВыбрать опцию: \n";
        cout << "0. Выход\n";
        cout << "1. Заполнить рандомными числами\n";
        cout << "2. Ввод данных\n";
        cout << "3. Вставка\n";
        cout << "4. Удалить элементы по индексу из списка\n";
        cout << "5. Удалить элементы по значению из списка\n";
        cout << "6. Поменять местами значения по индексу в списке\n";

        int choice = dai_chislo();
        cout << endl;
        switch (choice) {
        case 0:
            dish = false;
            break;
        case 1: {
            if (list)
                ochistit_spisok(list);
            cout << "input amount n: ";
            int n = dai_chislo();
            auto t1 = steady_clock::now();
            sluchayniy_spisok(list, n);
            auto t2 = steady_clock::now();
            auto list_t = duration_cast<nanoseconds>(t2 - t1);
            cout << "Done in " << list_t.count() << " nanos.\n";
        }
              break;
        case 2:
            if (list)
                ochistit_spisok(list);

            svoy_spisok(list);
            break;
        case 3: {
            if (!list) {
                cout << "you need a list\n";
                break;
            }

            cout << "input inedx and value: ";
            int i = dai_chislo();
            int v = dai_chislo();
            auto t1 = steady_clock::now();
            insert_spisok(list, i, v);
            auto t2 = steady_clock::now();
            auto list_t = duration_cast<nanoseconds>(t2 - t1);
            cout << "Inserted in " << list_t.count() << " nanos.\n";
        }
              break;
        case 4: {
            if (!list) {
                cout << "you need a list\n";
                break;
            }
            if (list->length == 0) {
                cout << "list has no elements!\n";
                break;
            }
            cout << "input index: ";
            int i = dai_chislo();
            auto t1 = steady_clock::now();
            delete_spisok(list, i);
            auto t2 = steady_clock::now();
            auto list_t = duration_cast<nanoseconds>(t2 - t1);
            cout << "Deleted in " << list_t.count() << " nanos." << endl;
        }
              break;
        case 5: {
            if (!list) {
                cout << "you need a list\n";
                break;
            }
            if (list->length == 0) {
                cout << "list has no elements!\n";
                break;
            }
            cout << "input value: ";
            int v = dai_chislo();
            auto t1 = steady_clock::now();
            node* prev = list->head;
            int nodeindex = 0;
            while (prev) {
                if (prev->data == v)
                    break;
                nodeindex++;
                prev = prev->next;
            }

            if (nodeindex < list->length)
                delete_spisok(list, nodeindex);
            auto t2 = steady_clock::now();
            auto list_t = duration_cast<nanoseconds>(t2 - t1);
            if (nodeindex == -1) {
                cout << "Not exist" << endl;
            }
            else {
                cout << "It was deleted was in " << list_t.count() << " nanos.\n";
            }
        }
              break;
        case 6: {
            if (!list) {
                cout << "you need a list\n";
                break;
            }

            cout << "input two indexes: ";
            int n1 = dai_chislo();
            int n2 = dai_chislo();
            if (n1 == n2)
                cout << "Identical indexes\n";
            else {
                auto t1 = steady_clock::now();
                change_spisok(list, n1, n2);
                auto t2 = steady_clock::now();
                auto list_t = duration_cast<nanoseconds>(t2 - t1);
                cout << "Changed was in " << list_t.count() << " nanos." << endl;
            }
        }
              break;
        default:
            cout << "option not exist\n";
            break;
        }
    }
    if (list) {
        ochistit_spisok(list);
    }

    dish = true;
    while (dish) {
        char input;
        DynArray arr;

        while (true) {
            cout << "Выбрать опцию:\n";
            cout << "1: Создать динамический массив\n";
            cout << "2: Вывод динамического массива\n";
            cout << "3: Найти элемент\n";
            cout << "4: Добавить новый элемент\n";
            cout << "5: Удалить элемент\n";
            cout << "0: Выход\n";

            input = checking1();
            if (input == '0') break;

            switch (input) {

            case '1': {
                // Get values;
                int size;
                cout << "Enter the size of the array:\n>> ";
                size = checking();
                int* values = new int[size]();
                cout << "Enter " << size << " elements separated by space:\n>> ";
                for (int i = 0; i < size; i++)
                    if (!(cin >> values[i])) {
                        cout << "Invalid input";
                        return 0;
                    }
                // Reassign the array
                arr = DynArray(size, values);
                cout << "Created array: " << arr << endl;
                break;
            }

            case '2': {
                std::cout << arr << "(size = " << arr.getSize() << ", capacity = " << arr.getCapacity() << ")\n";
                break;
            }
            case '3': {
                int choice;
                cout << " Choose the parameter to search:\n";
                cout << "  1. Index\n";
                cout << "  2. Value\n";

                if (!inputNumber(choice, true, true)) break;

                if (choice == 1) {
                    int index;
                    std::cout << "Enter the index:\n ";
                    if (!inputNumber(index, true, true)) break;

                    int* value = arr[index];
                    if (value) std::cout << "Element " << *value << " found\n";
                    else std::cout << "Element not found\n";
                }
                else if (choice == 2) {
                    int value;
                    std::cout << "Enter the value:\n ";
                    if (!inputNumber(value, true, true)) break;

                    int index = arr.find(value);
                    if (index != -1) std::cout << "Element found. Index: " << index << std::endl;
                    else std::cout << "Element not found\n";
                }
                else {
                    std::cout << "InputError: Unknown command '" << choice << "'\n";
                }

                break;
            }
            case '4': {
                int choice;
                cout << " Choose the parameter to search:\n";
                cout << "  1. push back\n";
                cout << "  2. insert by index\n";

                if (!inputNumber(choice, true, true)) break;

                if (choice != 1 && choice != 2) {
                    std::cout << "InputError: Unknown command '" << choice << "'\n";
                    break;
                }

                int value;
                cout << "Enter the value:\n ";
                if (!inputNumber(value, true, false)) break;

                if (choice == 1) {
                    arr.append(value);
                }
                else {
                    unsigned index;
                    cout << "Enter the index:\n ";
                    if (!inputNumber(index, true, true)) break;
                    arr.insert(index, value);
                }

                cout << "Updated array: " << arr << std::endl;

                break;
            }

            case '5': {
                unsigned index;
                cout << "Enter index of existing element:\n ";
                if (!inputNumber(index, true, true)) break;

                arr.remove(index);

                cout << "Updated array: " << arr << std::endl;

                break;
            }
            default: {
                cout << "Runtime error. Unknown command\n";
            }
                   break;
            }
        }
        return 0;
    }
    return 0;


}