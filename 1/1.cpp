#include<iostream>
using namespace std;

struct Node {
	int data;
	Node* next;
};
struct LinkedList {
	Node* head;
	Node* tail;
};

Node* createNode(int x) {
	Node* nn = new Node;
	nn->data = x;
	nn->next = NULL;
	return nn;
}
void createLinkedList(LinkedList& list) {
	list.head = NULL;
	list.tail = NULL;
}

void add(LinkedList& list, int x) {
	Node* newNode = createNode(x);
	if (list.head == nullptr) {
		list.head = newNode;
		list.tail = newNode;
	}
	else {
		list.tail->next = newNode;
		list.tail = newNode;
	}
}
void removeDuplicated(LinkedList& list) {
	if (list.head == nullptr) {
		return;
	}
	Node* cur = list.head;
	while (cur != nullptr && cur->next != nullptr) {
		if (cur->data == cur->next->data) {
			Node* duplicate = cur->next;
			cur->next = cur->next->next;
			delete duplicate;
		}
		else {
			cur = cur->next;
		}
	}
}
void removeKthFromEnd(LinkedList& list, int k) {
	if (list.head == nullptr) return;

	Node* fast = list.head;
	Node* slow = list.head;

	for (int i = 0; i < k; ++i) {
		if (fast == nullptr) return; // k is larger than the length of the list
		fast = fast->next;
	}

	if (fast == nullptr) {
		Node* toDelete = list.head;
		list.head = list.head->next;
		delete toDelete;
		return;
	}

	while (fast->next != nullptr) {
		fast = fast->next;
		slow = slow->next;
	}

	Node* toDelete = slow->next;
	slow->next = slow->next->next;
	delete toDelete;
}

bool isSymmetric(LinkedList list) {
	if (list.head == nullptr) return true;

	Node* slow = list.head;
	Node* fast = list.head;
	Node* prev = nullptr;
	Node* next = nullptr;

	while (fast != nullptr && fast->next != nullptr) {
		fast = fast->next->next;

		next = slow->next;
		slow->next = prev;
		prev = slow;
		slow = next;
	}

	Node* secondHalf = (fast == nullptr) ? slow : slow->next;
	Node* firstHalf = prev;

	while (secondHalf != nullptr) {
		if (firstHalf->data != secondHalf->data) return false;
		firstHalf = firstHalf->next;
		secondHalf = secondHalf->next;
	}

	return true;
}
void printList(LinkedList list) {
	Node* tmp = list.head;
	while (tmp != nullptr) {
		cout << tmp->data << " ";
		tmp = tmp->next;
	}
	cout << endl;
}

int main() {
	int x, n, k;
	LinkedList list;
	createLinkedList(list);
	cout << "The number of elements in the list: ";
	cin >> n;
	cout << "Please add the elemets to the list: " << endl;
	for (int i = 0; i < n; i++) {
		cin >> x;

		add(list, x);
	}
	cout << "List: ";
	printList(list);
	cout << "After removing 4th node from end: ";
	cout << "Enter the k position to remove from end: ";
	cin >> k;
	while (k > n) {
		cout << "Please enter a valid position: ";
		cin >> k;
	}
	removeKthFromEnd(list, k);
	printList(list);
	if (isSymmetric(list)) {
		cout << "List is symmetric" << endl;
	}
	else {
		cout << "List is not symmetric" << endl;
	}
	return 0;
}

