#pragma once
#include <iostream>
using namespace std;



template <typename T>
class LinkedList {
private:
	struct Node {
        T data;
        Node* prev;
        Node* next;
		
		Node(){
			prev = nullptr;
			next = nullptr;
		}
        Node(const T& value){
			data = value;
			prev = nullptr;
			next = nullptr;
		}
    };
public:
	// Behaviors
	void PrintForward() const{
		Node* curr = head;
		while (curr != nullptr) {
			cout << curr->data << endl;
			curr = curr->next;
		}
	}
	void PrintReverse() const{
		Node* curr = tail;
		while (curr != nullptr) {
			cout << curr->data << endl;
			curr = curr->prev;
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const{
		return count;
	}
	Node* getHead(){
		return head;
	}
	const Node* getHead() const{
		return head;
	}
	Node* getTail(){
		return tail;
	}
	const Node* getTail() const{
		return tail;
	}

	// Insertion
	void AddHead(const T& data){
		Node* node = new Node(data);
		node -> next = head;
		if(head != nullptr){
			head->prev = node;
		} 
		else{
			tail = node;
		}
		head = node;
    	++count;
	}
	void AddTail(const T& data){
		Node* node = new Node(data);
		node -> prev = tail;
		if(tail != nullptr){
			tail->next = node;
		} 
		else{
			head = node;
		}
		tail = node;
    	++count;
	}

	// Removal
	bool RemoveHead(){
		if(head == nullptr){
			return false;
		}

		Node* temp = head;
    	head = head->next;

		if(head != nullptr){
			head->prev = nullptr;
		}

		delete temp;
		--count;
		return true;
	}
	bool RemoveTail(){
		if(tail == nullptr){
			return false;
		}

		Node* temp = tail;
    	tail = tail -> prev;

		if(tail != nullptr){
			tail -> next = nullptr;
		}

		delete temp;
		--count;
		return true;
	}

	void Clear(){
		while(removeHead());
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept{
		if(this == &other){
			return *this;
		}

		Clear();
        head = other.head;
        tail = other.tail;
        count = other.count;
        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;

		return *this;
	}

	LinkedList<T>& operator=(const LinkedList<T>& rhs){
		if (this == &rhs){
			return *this;
		}

		Clear();
		Node* curr = rhs.head;
        while (curr) {
            addTail(curr->data);
            curr = curr->next;
        }

		return *this;
	}

	// Construction/Destruction
	LinkedList(): head(nullptr), tail(nullptr), count(0) {}
	
	LinkedList(const LinkedList<T>& list) : head(nullptr), tail(nullptr), count(0) {
    Node* curr = list.head;
    while (curr) {
        addTail(curr->data);
        curr = curr->next;
    }
}

	LinkedList(LinkedList<T>&& other) noexcept : head(other.head), tail(other.tail), count(other.count) {
    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;
}

	~LinkedList(){
		Clear();
	}

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;
};