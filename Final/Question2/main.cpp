#include "Student.h"
#include "IntSet.h"

#include<iostream>
#include <vector>
using namespace std;

int main(int argc,char* argv[1]) {
    if (argc < 2) {
        cerr << "Proper usage: " << argv[0] << " <input>." << endl;
        return 1;
    }

    ifstream ifs(argv[1]);
    if (!ifs.is_open()) {
        cerr << "Error: Unable to open \"" << argv[1] << "\"." << endl;
        return 1;
    }

    /*string fileName;
    cout << "File:";
    cin >> fileName;
    ifstream ifs(fileName);*/

    vector<Student*> students;
    string first_name,last_name;
    int sid;
    while(ifs>>first_name) {
        ifs >> last_name >> sid;
        students.push_back(new Student(first_name+" "+last_name,sid));
    }

    int unique_students = 0;
    int comparisons = 0;
    //variable n = number of student pointers in students vector
    // Overall runtime complexity: O(n)*O(n) = O(n^2)
    // Overall space complexity: O(1)
    for (unsigned i = 0;i < students.size();++i) { // O(n)
        bool already_counted = false; // O(1)
        for (unsigned j = 0;j < i;++j) { // O(n-1) = O(n)
            comparisons++; // O(1)
            if (*students.at(j) == *students.at(i)) {  // O(1)
                already_counted = true; // O(1)
            }
        }
        if (!already_counted) { unique_students++; } // O(1)+O(1)=O(1)
    }
    cout << "Unique students: " << unique_students << endl;
    cout << "\tComparisons made: " << comparisons << endl;

    /* Insert solution here */
    IntSet students2;
    for(unsigned int i = 0; i < students.size(); i++){
      students2.insert(students.at(i)->sid());
    }
    cout << "Unique students: " << students2.size();
    cout << endl;
    cout << "\tComparisons made: " << students2.comparisons();
    cout << endl;

    return 0;
}
