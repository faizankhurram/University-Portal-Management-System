#include "HelperFunctions.cpp"

template <typename T>
class LinearQueue{
private:
    int frontIndex;
    int rear;
    int capacity;
    T* queue;

public:
    LinearQueue() : frontIndex(-1), rear(-1), capacity(){
        queue = new T[capacity];
    }
    LinearQueue(int size) : frontIndex(-1), rear(-1), capacity(size){
        queue = new T[capacity];
    }

    ~LinearQueue(){
        delete[] queue;
    }

    bool isEmpty(void){
        return frontIndex == -1;
    }

    bool isFull(void){
        return rear == capacity - 1;
    }

    void push(T element){
        if (isFull()){
            cout << "Queue is full. Cannot push " << element << endl;
            return;
        }
        if (frontIndex == -1) frontIndex = 0;
        queue[++rear] = element;
    }

    T pop(void){
        if (isEmpty()){
            cout << "Queue is empty. Cannot pop." << endl;
            return T();
        }
        T element = queue[frontIndex];
        if (frontIndex == rear){
            frontIndex = rear = -1;
        } else{
            frontIndex++;
        }
        return element;
    }

    T front(void){
        if (isEmpty()){
            cout << "Queue is empty. Cannot access front." << endl;
            return T();
        }
        return queue[frontIndex];
    }

    int size(void){
        if (isEmpty()) return 0;
        return rear - frontIndex + 1;
    }

    void display(void){
        if (isEmpty()){
            cout << "Queue is empty." << endl;
            return;
        }
        cout << "Queue elements: ";
        for (int i = frontIndex; i <= rear; i++){
            cout << queue[i] << " ";
        }
        cout << endl;
    }
};