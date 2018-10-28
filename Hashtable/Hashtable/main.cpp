#include <iostream>
#include <list>
#include<iomanip>
#include<math.h>
using namespace std;


template<typename K, typename V>

class Node {
private:
	K key;
	V value;
	Node *next;
public:
	Node(K key, V value) {
		this->key = key;
		this->value = value;
		next = NULL;
	}

	void setNext(Node* next) {
		this->next = next;
	}

	Node getnext() {
		return next;
	}
};

template<typename K, typename V>

class Hash {
	Node<K, V> *arr;
	Node<K, V> *temp;
	int size;
	int collisions = 0;
	int numdata = 0;



public:

	void setsize(int tSize) {
		size = tSize;

		arr = calloc(size, sizeof(Node))
		if (arr == NULL) {
			perror("calloc arr");
			exit(EXIT_FAILURE);
		}
	}

	int modTable(K key) {
		return key % size;
	}

	int midSquare(K key) {
		int squareK = key * key;
		int a = 1;
		int b = 1;
		int powerA = 0;
		int powerB = 0;

		while (squareK >= a) {
			a *= 2;
			powerA++;
		}

		while (size >= b) {
			b *= 2;
			powerB++;
		}

		double power = (double)(powerA - powerB) / 2;
		int inm = pow(2, round(power));

		return (squareK / inm) % size;
	}


	void openAddressing(K key, V value, int type) {
		int calc;
		numdata++;

		if (type = 1)
			calc = modTable(key);
		else
			calc = midSquare(key);

		Node<K, V> *curr = new Node<K, V>(key, value);

		while (arr[calc] != NULL) {
			collisions++;
			calc++;
			if (calc = size)
				calc = 0;
		}
		arr[calc] = curr;

		cout <<  "#" << value << " Key = " << key << "Calculation: " << calc << " Load factor = " << loadFactor() << " Collisions = " << collisions << endl;

	}



	void separateChaining(K key, V value, int type) {
		int calc;
		numdata++;

		if (type = 1)
			calc = modTable(key);
		else
			calc = midSquare(key);

		Node<K, V> *curr = new Node<K, V>(key, value);

		if (arr[calc] == NULL)
			arr[calc] == curr;
		else {
			collisions++;
			temp = arr[calc];

			while (temp->getnext() != NULL){
				collisions++;
				temp = temp->getnext();
			}

			temp->getnext() = curr;
		}

		
		cout << "#" << value << " Key = " << key << "Calculation: " << calc << " Load factor = " << loadFactor() << " Collisions = " << collisions << endl;
	}

	double loadFactor() {
		return (double)numdata / size;
	}

	void display() {
	
		cout << " Load factor = " << loadFactor() << endl;
		cout << " Collisions =" << collisions << endl;
	}

	void reset() {

		for (int i = 0; i < size; i++) {
			arr[i] = NULL;
		}
		collisions = 0;
		numdata = 0;
	}



};


int main() {
	int size[3];

	cout << "Open Addressing using Key Mod Table Size" << endl;
	cout << "Enter 3 different sizes (press enter after every size): ";
	cin >> size[0];
	cout << ", ";
	cin >> size[1];
	cout << ", ";
	cin >> size[2];
	cout << "\n\n";

	Hash<int, int> *hash = new Hash<int, int>;


	for (int i = 1; i <= size[i-1]; i++) {
		hash->setsize(size[i - 1]);
		cout << "Size: " << size[i - 1] << endl;
		hash->openAddressing(round(rand() *size[i-1]*3), i, 1);
		hash->display();
		hash->reset();
		cout << endl;
	}
	
	

	cout << "Open Addressing using Mid Sqaure" << endl;
	cout << "Enter 3 different sizes (press enter after every size): ";
	cin >> size[0];
	cout << ", ";
	cin >> size[1];
	cout << ", ";
	cin >> size[2];
	cout << "\n\n";


	for (int i = 1; i <= size[i - 1]; i++) {
		hash->setsize(size[i - 1]);
		cout << "Size: " << size[i - 1] << endl;
		hash->openAddressing(round(rand() *size[i - 1] * 3), i, 2);
		hash->display();
		hash->reset();
		cout << endl;
	}

	
	

	return 0;
}