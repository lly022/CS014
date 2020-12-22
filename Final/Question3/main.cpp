#include "Patient.h"

#include <iostream>
#include <utility>

#include <queue>
#include <stack>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

using namespace std;

// Describe any additional functions that are needed for part III

int main(int argc,char* argv[]) {
    if (argc < 2) {
        cerr << "Proper usage: " << argv[0] << " <patients_file>." << endl;
        return 1;
    }

    ifstream ifs(argv[1]);
    if (!ifs.is_open()) {
        cerr << "Error: Unable to open " << argv[1] << endl;
        return 1;
    }

    //string file;
    //cout << "input file: ";
    //cin >> file;
    //ifstream ifs(file);

    //??? intake_times;  // Part I, what data structure should be used here and why? (implement)
    // A set should be used here because the hospital us to organize and store patients based off of their intake time. 
    //A set allows us to have that structure that is sorted, which I said before, is what the hospital wants. 
    //Also, a set is like a BST(binary search tree). Because of this, searching (and therefore inserting ) for the id and 
    //intake time  will take a logarithmic runtime or O(logn) compared to other search runtimes of other data strucutres 
    //which may be longer. 
    set<pair<int, int> > intake_times;

    //??? patients; // Part II, what data structure should be used here and why? (implement)
    //An unordered_map should be used here to store the patients and the hash values that are a result of the patient's id. 
   //With an unordered_map, there is no need for the data to be sorted. As a result, there is a constant time O(1) runtime, 
   //or close to constant O(1) runtime in order to get a patient with his/her id. 
    unordered_map<int, Patient*> patients;

    //??? patient_urgencies; // Part III, what data structure should be used here and why? (comments only)
    // A set should be used here. It should be a set of pairs. The first element of the pair should be the number of the urgency (0,1,2),
   // and the second element of the pair should be a pointer to the patient. A set should be used because it allows us to have a data 
   //structure with an order (the hospital wants a loose order) based on the urgency of the patients.  Also, a set is like a 
   //BST(binary search tree). Because of this, searching (and therefore inserting) for the id, intake time, and urgency will take a 
   //logarithmic runtime or O(logn) compared to other search runtimes of other data strucutres which may be longer. To add the patients 
   //to the set, I would use the insert() operation and there will be a patient pointer as the parameter. Using the patient pointer, 
   //I can get the patient's urgency level. The insert() operation from the set STL will then sort the patients for me by urgency. 
   //The run time of this operation would be O(1). 

    string first_name, last_name;
    int intake_time,urgency,id;
    
    // Overall runtime complexity: O(logn) , n = number of patients
    // Overall space complexity: O(n), n = number of patients
    while (ifs >> id) {
        ifs >> first_name >> last_name >> intake_time >> urgency; // O(1)
        Patient *patient_record = new Patient(id,first_name + " " + last_name); // O(1)
        patient_record->urgency(urgency); // O(1)

        intake_times.insert(make_pair(intake_time,id)); //O(logn)
        patients.insert(make_pair(id,patient_record)); //O(1)
        // patient_urgencies.insert(patient_record) //O(logn)
    }

    // Output Patients sorted by oldest intake_time (smallest) to newest intake_time (largest) (Implement)
    cout << "Sorted by intake times: " << endl;
    set<pair<int, int>>::iterator i;
    for(i = intake_times.begin(); i!= intake_times.end(); i++){
      cout << *(patients[i->second]) << endl;
    }

    // Output Patients ID's sorted by most urgent to least urgent
    // In commenst describe how this would work. 
    //I would declare a set of pairs. The first element of the pair is the urgency number (0,1,2) and the second 
   //element is a patient pointer. I would then declare an iterator for a set of pairs. Using that iterator, I would then 
   //make a for loop going through the set, but backwards (from end of set to the beginning of it, going from high->medium->low urgency).
   // Since a set already gives us order, I would then output patients' IDs using the patient pointer of the second element of the pair. 
    return 0;
}
