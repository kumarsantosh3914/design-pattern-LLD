/**
 * Student data:
 * - RollNo: (alphanumeric and unique)
 * - name: (string)
 * - marks: (float)
 * - rank: (not unique, can be same for multiple students)
 */

/**
 * Tasks:
 * - write a class and functions to:
 * 1. Retrieve all students for a given rank.
 * 2. Retrieve a student by their roll number.
 */

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;

class Student {
public:
    string rollNo;
    string name;
    float marks;
    int rank;

public:

    Student() = default; // Default constructor
    // Constructor
    Student(string r, string n, float m, int rk) : rollNo(r), name(n), marks(m), rank(rk) {}
};

class StudentManager {
private:
    unordered_map<int, vector<Student>> rankMap; // Maps rank to students
    unordered_map<string, Student> rollNoMap; // Maps roll number to student

public:
    void addStudent(const Student& student) {
        // Add student to rank map
        rankMap[student.rank].push_back(student);
        // Add student to roll number map
        rollNoMap[student.rollNo] = student;
    }

    Student* getStudentByRollNo(const string& rollNo) {
        auto it = rollNoMap.find(rollNo);
        if (it != rollNoMap.end()) {
            return &(it->second); // Return the student if found
        }
        return nullptr; // Return nullopt if not found
    }

    // retrieve all students for a given rank
    vector<Student> getStudentByRank(int rank) {
        auto it = rankMap.find(rank);
        if (it != rankMap.end()) {
            return it->second; // Return the vector of students for the given rank
        }
        return {}; // Return an empty vector if no students found for the rank
    }
};

int main() {
    StudentManager manager;

    manager.addStudent(Student("R001", "Alice", 85.5, 1));
    manager.addStudent(Student("R002", "Bob", 90.0, 1));
    manager.addStudent(Student("R003", "Charlie", 78.0, 2));
    manager.addStudent(Student("R004", "David", 88.0, 2));

    // retrieve by roll number
    Student* student = manager.getStudentByRollNo("R002");
    if (student != nullptr) {
        cout << "Student found: " << student->name << endl;
    } else {
        cout << "Student not found." << endl;
    }

    // retrieve by rank
    auto topRankers = manager.getStudentByRank(2);
    cout << "Students with rank 1:" << endl;
    for (const auto& student : topRankers) {
        cout << "Roll No: " << student.rollNo << ", Name: " << student.name << ", Marks: " << student.marks << endl;
    }
    return 0;
}