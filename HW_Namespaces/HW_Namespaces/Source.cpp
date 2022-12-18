#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

const char ALPHABET[] = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";

string generateRandomName(int nameLength) {
	string res;
	for (int i = 0; i < nameLength; i++)
		res += ALPHABET[rand() % (sizeof(ALPHABET) - 1)];
	return res;
}

vector<int> generateRandomPoints(int amount) {
	vector<int> res;
	for (int i = 0; i < amount; i++)
		res.push_back(rand() % 10);
	return res;
}

void printStudents(multimap<string, int> st) {
	int k = 0;
	for (multimap<string, int>::iterator it = st.begin(); it != st.end(); it++) {
		if (k % 10 == 0)
			cout << it->first << endl;
		cout << it->second << " ";
		if (k % 10 == 9)
			cout << endl;
		k++;
	}
}


int countSumOfPoints(pair<multimap<string, int>::iterator, multimap<string, int>::iterator> student, multimap<string, int> students) {
	int sum = 0;
	for (auto it = student.first; it != student.second; ++it)
		sum += it->second;
	return sum;
	
}




int main() {
	multimap<string, int> students;
	for (int i = 0; i < 4; i++) {
		string lastName = generateRandomName(5);
		vector<int> points = generateRandomPoints(10);
		for (int i = 0; i < 10; i++)
			students.emplace(lastName, points[i]);
	}
	
	printStudents(students);
	
	cout << "Enter the last name of the student for whom you want to calculate the amount of points" << endl;
	string lastName;
	cin >> lastName;
	
	pair<multimap<string, int>::iterator, multimap<string, int>::iterator>  student = students.equal_range(lastName);
	if (student.first != students.end())
		cout << "Sum of points = " << countSumOfPoints(student, students) << endl;
	else
		cout << "Student with this last name has not been found" << endl;
	
	return 0;
}

