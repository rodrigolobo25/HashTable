#include <iostream>
#include <list>
#include<iomanip>
#include <ctime>
#include <vector>
#include<math.h>
using namespace std;


class Node {
private:
	int key;
	int value;
	Node *next;
public:
	Node(int key, int value) {
		this->key = key;
		this->value = value;
		next = NULL;
	}

	void setNext(Node* next) {
		this->next = next;
	}

	Node* getnext() {
		return next;
	}

	int getkey() {
		return key;
	}

	void setkey(int key) {
		this->key = key;
	}
};


class Hash {
	vector <Node> arr;
	Node *temp;
	int size;
	int collisions = 0;
	int numdata = 0;



public:

	void setsize(int tSize) {
		size = tSize;
		Node p(NULL, NULL);
		for (int i = 0; i < size; i++) {
			arr.push_back(p);
		}
	}

	int modTable(int key) {
		return key % size;
	}

	int midSquare(int key) {
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


	void openAddressing(int key, int value, int type) {
		int calc;
		numdata++;

		if (type = 1)
			calc = modTable(key);
		else
			calc = midSquare(key);

		Node curr(key, value);

		while (arr[calc].getkey() != NULL) {
			collisions++;
			calc++;
			if (calc == size)
				calc = 0;
		}
		arr[calc] = curr;

		cout <<  "#" << value << " Key = " << key << " Calculation: " << calc << " Load factor = " << loadFactor() << " Collisions = " << collisions << endl;

	}



	void separateChaining(int key, int value, int type) {
		int calc;
		numdata++;

		if (type = 1)
			calc = modTable(key);
		else
			calc = midSquare(key);

		Node curr(key, value);

		if (arr[calc].getkey() == NULL)
			arr[calc] = curr;
		else {
			collisions++;
			temp = &arr[calc];

			while (temp->getnext() != NULL){
				collisions++;
				temp = temp->getnext();
			}

			temp->setNext(&curr);
		}

		
		cout << "#" << value << " Key = " << key << " Calculation: " << calc << " Load factor = " << loadFactor() << " Collisions = " << collisions << endl;
	}

	double loadFactor() {
		return (double)numdata / size;
	}

	void display() {
	
		cout << "Load factor = " << loadFactor() << endl;
		cout << "Collisions =" << collisions << endl;
	}

	void reset() {

		for (int i = 0; i < size; i++) {
			arr[i].setNext(NULL);
			arr[i].setkey(NULL);
			arr[i].setNext(NULL);
		}
		collisions = 0;
		numdata = 0;
	}



};


int main() {
	int size[3];
	Hash *hash = new Hash;
	srand((unsigned)time(0));

	cout << "Open Addressing using Key Mod Table Size" << endl;
	cout << "Enter 3 different sizes (press enter after every size): \n";
	cin >> size[0];
	cin >> size[1];
	cin >> size[2];
	cout << "\n\n";


	for (int j = 0; j<3; j++) {
		hash->setsize(size[j]);
		cout << "Size: " << size[j] << endl;
		for (int i = 1; i <= size[j]; i++) {
			hash->openAddressing(rand()%(size[j]*3+1), i, 1);
		}	
		hash->display();
		hash->reset();
		cout << endl;
	}
	
	

	cout << "Open Addressing using Mid Square" << endl;
	cout << "Enter 3 different sizes (press enter after every size): \n";
	cin >> size[0];
	cin >> size[1];
	cin >> size[2];
	cout << "\n\n";

	for (int j = 0; j < 3; j++) {
		hash->setsize(size[j]);
		cout << "Size: " << size[j] << endl;
		for (int i = 1; i <= size[i - 1]; i++)
			hash->openAddressing(rand() % (size[j] * 3 + 1), i, 2);
		hash->display();
		hash->reset();
		cout << endl;
	}


	cout << "Separate Chaining using Key Mod Table Size" << endl;
	cout << "Enter 3 different sizes (press enter after every size): \n";
	cin >> size[0];
	cin >> size[1];
	cin >> size[2];
	cout << "\n\n";

	for (int j = 0; j < 3; j++) {
		hash->setsize(size[j]);
		cout << "Size: " << size[j] << endl;
		for (int i = 1; i <= size[i - 1]; i++)
			hash->separateChaining(rand() % (size[j] * 3 + 1), i, 1);
		hash->display();
		hash->reset();
		cout << endl;
	}
	
	
	cout << "Separate Chaining using Mid Square" << endl;
	cout << "Enter 3 different sizes (press enter after every size): \n";
	cin >> size[0];
	cin >> size[1];
	cin >> size[2];
	cout << "\n\n";

	for (int j = 0; j < 3; j++) {
		hash->setsize(size[j]);
		cout << "Size: " << size[j] << endl;
		for (int i = 1; i <= size[i - 1]; i++)
			hash->separateChaining(rand() % (size[j] * 3 + 1), i, 2);
		hash->display();
		hash->reset();
		cout << endl;
	}

	return 0;
}