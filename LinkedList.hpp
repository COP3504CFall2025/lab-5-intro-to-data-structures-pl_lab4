#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node {
        T data;
        Node* prev;
        Node* next;

		template<typename U>; //https://stackoverflow.com/questions/8967521/class-template-with-template-class-friend-whats-really-going-on-here
		friend class LinkedList;
		
		Node(){
			prev = nullptr;
			next = nullptr;
		}

        Node(const T& value){
			data = value;
			prev = nullptr;
			next = nullptr;
		}

		~Node(){
			prev = nullptr;
			next = nullptr;
		}

		T getData(){
			return data;
		}
		
		T getData() const {
    		return data;
		}
    };

template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const{
		Node<T>* curr = head;
		while (curr != nullptr) {
			cout << curr->data << endl;
			curr = curr->next;
		}
	}

	void printReverse() const{
		Node<T>* curr = tail;
		while (curr != nullptr) {
			cout << curr->data << endl;
			curr = curr->prev;
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const{
		return count;
	}
	Node<T>* getHead(){
		return head;
	}
	const Node<T>* getHead() const{
		return head;
	}
	Node<T>* getTail(){
		return tail;
	}
	const Node<T>* getTail() const{
		return tail;
	}

	// Insertion
	void addHead(const T& data){
		Node<T>* node = new Node(data);
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

	void addTail(const T& data){
		Node<T>* node = new Node(data);
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
	bool removeHead(){
		if(head == nullptr){
			return false;
		}

		Node<T>* temp = head;
    	head = head->next;

		if(head != nullptr){
			head->prev = nullptr;
		}
		else{
			tail = nullptr;
		}

		delete temp;
		--count;
		return true;
	}

	bool removeTail(){
		if(tail == nullptr){
			return false;
		}

		Node<T>* temp = tail;
    	tail = tail -> prev;

		if(tail != nullptr){
			tail -> next = nullptr;
		}
		else{
			head = nullptr;
		}

		delete temp;
		--count;
		return true;
	}

	void clear(){
		while(removeHead());
	}

	// Operators
	LinkedList& operator=(LinkedList&& other) noexcept{
		if(this == &other){
			return *this;
		}

		clear();
        head = other.head;
        tail = other.tail;
        count = other.count;
        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;

		return *this;
	}

	LinkedList& operator=(const LinkedList& rhs){
		if (this == &rhs){
			return *this;
		}

		clear();
		
		Node<T>* curr = rhs.head;
        while (curr) {
            addTail(curr->data);
            curr = curr->next;
        }
		return *this;
	}

	// Construction/Destruction
	LinkedList(){
		head = nullptr;
		tail = nullptr;
		count = 0;
	}
	
	LinkedList(const LinkedList& list) : head(nullptr), tail(nullptr), count(0) {
		Node<T>* curr = list.head;
		while (curr) {
			addTail(curr->data);
			curr = curr->next;
		}
	}

	LinkedList(LinkedList&& other) noexcept : head(other.head), tail(other.tail), count(other.count) {
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}

	~LinkedList(){
		clear();
	}

private:
	// Stores pointers to first and last nodes and count
	Node<T>* head;
	Node<T>* tail;
	unsigned int count;
};