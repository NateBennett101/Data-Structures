
// Nate Bennett

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// This is the course class, and it should store the course information.
class Course {
public:
    Course(string courseNumber, string name, vector<string> prerequisites)
        : courseNumber(courseNumber), name(name), prerequisites(prerequisites) {}

    string getCourseNumber() const { return courseNumber; }
    string getName() const { return name; }
    vector<string> getPrerequisites() const { return prerequisites; }

private:
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

// This is the function to load data from the file into the data structure.
void loadDataStructure(const string& fileName, vector<Course>& courses) {
    //This should open the file with the given file name.
    ifstream file(fileName);
    // This if statment should check if the file was opened.
    if (file.is_open()) {
        string line;
        // This while loop should read each line from the file.
        while (getline(file, line)) {
            stringstream ss(line);
            string courseNumber, name, prereq;
            vector<string> prerequisites;
            getline(ss, courseNumber, ',');
            getline(ss, name, ',');
            while (getline(ss, prereq, ',')) {
                prerequisites.push_back(prereq);
            }
            Course course(courseNumber, name, prerequisites);
            courses.push_back(course);
        }
        // This should close the file.
        file.close();
        cout << "Data loaded successfully!" << endl;
    }
    else {
        cout << "Error loading data from file." << endl;
    }
}

// This function should print the course list in alphanumeric order.
void printCourseList(const vector<Course>& courses) {
    // This should create a vector to help store the course information.
    vector<string> courseNumbers;
    // This for loop should go through each course object in the vector of courses.
    for (const Course& course : courses) {
        courseNumbers.push_back(course.getCourseNumber());
    }
    sort(courseNumbers.begin(), courseNumbers.end());
    cout << "Course List:" << endl;
    // This for loop should go through each course number in the sorted vector.
    for (const string& courseNumber : courseNumbers) {
        for (const Course& course : courses) {
            if (course.getCourseNumber() == courseNumber) {
                cout << course.getCourseNumber() << ", " << course.getName() << endl;
                break;
            }
        }
    }
}

// This function should print the course information.
void printCourseInformation(const vector<Course>& courses) {
    string courseNumber;
    cout << "Enter course number: ";
    cin >> courseNumber;
    bool found = false;
    // This for loop should go through each course object in the vecotr of courses.
    for (const Course& course : courses) {
        if (course.getCourseNumber() == courseNumber) {
            found = true;
            cout << "Course Number: " << course.getCourseNumber() << endl;
            cout << "Course Name: " << course.getName() << endl;
            cout << "Prerequisites: ";
            vector<string> prerequisites = course.getPrerequisites();
            if (prerequisites.empty()) {
                cout << "None" << endl;
            }
            else {
                for (const string& prereq : prerequisites) {
                    cout << prereq << " ";
                }
                cout << endl;
            }
            break;
        }
    }
    if (!found) {
        cout << "Course not found." << endl;
    }
}

// This function should display the menu and get the user's choice as an input.
int getMenuChoice() {
    int choice;
    cout << "Welcome to the course planner." << endl;
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit." << endl;
    cout << "What would you like to do? ";
    cin >> choice;
    return choice;
}

// This should be the main function.
int main() {
    vector<Course> courses;
    int choice;
    while ((choice = getMenuChoice()) != 9) {
        switch (choice) {
        case 1:
        {
            string fileName;
            cout << "Enter file name: ";
            cin >> fileName;
            loadDataStructure(fileName, courses);
        }
        break;
        case 2:
            printCourseList(courses);
            break;
        case 3:
            printCourseInformation(courses);
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    cout << "Thank you for using the course planner. Goodbye!" << endl;
    return 0;
}
