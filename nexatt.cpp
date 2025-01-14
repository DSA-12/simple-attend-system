#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Student
{
    string name;
    int rollnumber;
    int totalcalsses = 100;
    int atend = 0;

    double getatend() const
    {
        if (totalcalsses == 0)
        {
            return 0.0;
        }
        return ((static_cast<double>(atend) / totalcalsses) * 100);
    }
};

void add(Student *&students, int &studentcount);
void mark(Student *students, int &studentcount);
void view(const Student *students, int &studentcounter);

int main()
{

    Student *students = nullptr;
    int studentcount = 0;
    char cho;

    do
    {
        cout << "\n--- Dynamic Attendance Management System ---\n";
        cout << "1. Add a New Student\n";
        cout << "2. Mark Attendance\n";
        cout << "3. View Attendance Records\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> cho;

        switch (cho)
        {
        case '1':
            add(students, studentcount);
            break;
        case '2':
            mark(students, studentcount);
            break;
        case '3':
            view(students, studentcount);
            break;
        case '4':
            cout << "Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
            break;
        }
    } while (cho != '4');

    delete[] students;

    return 0;
}

void add(Student *&students, int &studentcounter)
{

    Student *newstudent = new Student[studentcounter + 1];
    for (int i = 0; i < studentcounter; i++)
    {
        newstudent[i] = students[i];
    }
    delete[] students;

    students = newstudent;

    cout << "Enter roll number: ";
    cin >> students[studentcounter].rollnumber;

    cout << "Enter name: ";
    cin >> ws; // Clear the input buffer
    getline(cin, students[studentcounter].name);

    studentcounter++;
    cout << "Student added successfully!\n";
}

void mark(Student *students, int &studentcount)
{

    if (studentcount == 0)
    {
        cout << "No students available to mark attendance.\n";
        return;
    }

    int rollnumber;
    char sts;

    cout << " enter the roll number : ";
    cin >> rollnumber;

    bool found = false;
    for (int i = 0; i < studentcount; i++)
    {
        if (students[i].rollnumber == rollnumber)
        {
            found = true;
            cout << "Mark attendance for " << students[i].name << " (P for present, A for absent): ";
            cin >> sts;
            students[i].totalcalsses++;

            if (sts == 'p' || sts == 'P')
            {
                students[i].atend++;
            }
            cout << "Attendance marked successfully!\n";
            break;
        }
    }
    if (!found)
    {
        cout << "Student with roll number " << rollnumber << " not found.\n";
    }
}

void view(const Student *students, int &studentcounter)
{

    if (studentcounter == 0)
    {
        cout << "No students to display.\n";
        return;
    }
    cout << "\n--- Attendance Records ---\n";
    cout << left << setw(10) << "Roll No" << setw(20) << "Name"
         << setw(15) << "Total Classes" << setw(20) << "Attended Classes"
         << "Attendance %\n";

    for (int i = 0; i < studentcounter; i++)
    {
        cout << left << setw(13) << students[i].rollnumber
             << setw(20) << students[i].name
             << setw(15) << students[i].totalcalsses
             << setw(20) << students[i].atend
             << fixed << setprecision(2) << students[i].getatend() << "%\n";
    }
}
