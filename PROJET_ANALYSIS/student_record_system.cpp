
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>   // std::sort, std::transform
#include <iomanip>     // std::setw, std::fixed, std::setprecision
#include <limits>      // std::numeric_limits
#include <cctype>      // std::tolower

using namespace std;

// ============================================================
//  DATA MODEL
// ============================================================

/*
 * Student struct
 * Space: O(1) per instance – three primitive/fixed-size fields.
 *   id    : 4 bytes  (int)
 *   gpa   : 8 bytes  (double)
 *   name  : heap-allocated but bounded; treated O(1) in analysis.
 */
struct Student {
    int    id;
    string name;
    double gpa;

    // Convenience constructor
    // RAM cost: 3 assignments = O(1)
    Student(int i, const string& n, double g)
        : id(i), name(n), gpa(g) {}
};

// ============================================================
//  UTILITY HELPERS
// ============================================================

/*
 * toLowerStr – convert a string to lowercase for case-insensitive compare.
 * RAM Model : one loop of length k (k = string length).
 * Time      : O(k) — treated O(1) because name length is bounded by a constant.
 */
string toLowerStr(const string& s) {
    string result = s;
    // Each iteration: one tolower call = O(1) under RAM model
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

/*
 * printHeader – prints a formatted table header.
 * Time  : O(1) — fixed number of output statements.
 * Space : O(1) — no extra memory allocated.
 */
void printHeader() {
    cout << "\n"
         << string(55, '=') << "\n"
         << setw(8)  << left  << "  ID"
         << setw(22) << left  << "  Name"
         << setw(10) << right << "GPA  "
         << "\n"
         << string(55, '-') << "\n";
}

/*
 * printStudent – prints one student row.
 * Time  : O(1) — fixed fields, one output operation.
 * Space : O(1).
 */
void printStudent(const Student& s) {
    cout << setw(8)  << left  << ("  " + to_string(s.id))
         << setw(22) << left  << ("  " + s.name)
         << setw(8)  << right << fixed << setprecision(2) << s.gpa
         << "\n";
}

// ============================================================
//  CORE OPERATIONS
// ============================================================

/*
 * addStudent
 * ----------
 * Appends a new Student to the vector.
 *
 * RAM Model : 3 reads (id, name, gpa), 1 push_back write → 4 operations.
 *
 * Time Complexity : O(1) amortised.
 *   - vector::push_back is O(1) amortised because the vector doubles its
 *     capacity when full (geometric growth), spreading reallocation cost
 *     over many insertions.
 *   - Worst-case single call (reallocation): O(n) — copies all elements.
 *     But amortised over n insertions the total cost is O(n), so per-call O(1).
 *
 * Space Complexity : O(1) auxiliary (no extra data structures created).
 *   - The vector itself grows by one element on the heap — accounted for
 *     in the overall O(n) storage of the system.
 */
void addStudent(vector<Student>& students) {
    int    id;
    string name;
    double gpa;

    cout << "\n  Enter Student ID   : ";
    cin  >> id;                              // O(1) read

    // Check for duplicate ID — O(n) scan
    // RAM cost: n comparisons in the worst case
    for (const auto& s : students) {         // O(n)
        if (s.id == id) {                    // O(1) comparison
            cout << "  [Error] ID " << id << " already exists.\n";
            return;
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "  Enter Student Name : ";
    getline(cin, name);                      // O(1) — bounded name length

    cout << "  Enter GPA (0.0–4.0): ";
    cin  >> gpa;                             // O(1) read

    if (gpa < 0.0 || gpa > 4.0) {
        cout << "  [Error] GPA must be between 0.0 and 4.0.\n";
        return;
    }

    students.push_back(Student(id, name, gpa));  // O(1) amortised
    cout << "  [OK] Student added successfully.\n";
}

/*
 * displayAll
 * ----------
 * Prints every student in the vector.
 *
 * RAM Model : visits each of the n elements once → n read operations.
 *
 * Time Complexity : O(n)
 *   - One pass over the vector; each printStudent call is O(1).
 *   - Total: n × O(1) = O(n).
 *
 * Space Complexity : O(1) auxiliary — no extra storage beyond loop variable.
 */
void displayAll(const vector<Student>& students) {
    if (students.empty()) {
        cout << "\n  No records found.\n";
        return;
    }

    printHeader();                           // O(1)
    for (const auto& s : students) {        // O(n) iterations
        printStudent(s);                     // O(1) per call
    }
    cout << string(55, '=') << "\n";
    cout << "  Total records: " << students.size() << "\n";
}

/*
 * searchByID
 * ----------
 * Linear search for a student matching the given ID.
 *
 * RAM Model : up to n comparisons (one per element).
 *
 * Time Complexity
 *   Best case    O(1)  — target is the first element.
 *   Average case O(n/2) = O(n) — target found halfway through.
 *   Worst case   O(n)  — target is last or absent.
 *
 * Space Complexity : O(1) — only a loop counter and a flag variable.
 */
void searchByID(const vector<Student>& students) {
    int target;
    cout << "\n  Enter Student ID to search: ";
    cin  >> target;                          // O(1)

    bool found = false;
    printHeader();

    for (const auto& s : students) {        // O(n) — linear scan
        if (s.id == target) {               // O(1) comparison
            printStudent(s);                // O(1)
            found = true;
            break;                          // early exit: best case O(1)
        }
    }

    if (!found)
        cout << "  [Not Found] No student with ID " << target << ".\n";

    cout << string(55, '=') << "\n";
}

/*
 * searchByName
 * ------------
 * Case-insensitive linear search by name substring.
 *
 * RAM Model : n string comparisons, each bounded O(1) → n RAM operations.
 *
 * Time Complexity : O(n)  — same reasoning as searchByID.
 *   (String comparison is O(k) for length k, but k is bounded by a constant
 *    max-name-length, so it collapses to O(1) per iteration.)
 *
 * Space Complexity : O(1) auxiliary — two temporary lowercase strings created
 *   per iteration, but each is O(1) size.
 */
void searchByName(const vector<Student>& students) {
    string target;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n  Enter Name (or part of name) to search: ";
    getline(cin, target);                    // O(1)

    string lowerTarget = toLowerStr(target); // O(1) — bounded length

    bool found = false;
    printHeader();

    for (const auto& s : students) {             // O(n)
        string lowerName = toLowerStr(s.name);   // O(1)
        if (lowerName.find(lowerTarget) != string::npos) { // O(1)
            printStudent(s);                     // O(1)
            found = true;
        }
    }

    if (!found)
        cout << "  [Not Found] No student matching \"" << target << "\".\n";

    cout << string(55, '=') << "\n";
}

/*
 * deleteStudent
 * -------------
 * Finds a student by ID and removes them from the vector.
 *
 * RAM Model
 *   Phase 1 (find)   : up to n comparisons → n operations.
 *   Phase 2 (erase)  : vector::erase shifts up to n−1 elements → n−1 operations.
 *   Total            : ≤ 2n − 1 operations → O(n).
 *
 * Time Complexity : O(n)
 *   - Linear search     O(n)
 *   - vector::erase     O(n) — shifts remaining elements left.
 *   Combined            O(n) + O(n) = O(n).
 *
 * Space Complexity : O(1) auxiliary — iterator variable only.
 */
void deleteStudent(vector<Student>& students) {
    int target;
    cout << "\n  Enter Student ID to delete: ";
    cin  >> target;                          // O(1)

    // Linear search for matching ID — O(n)
    for (auto it = students.begin(); it != students.end(); ++it) { // O(n)
        if (it->id == target) {              // O(1) comparison
            students.erase(it);              // O(n) — shifts elements
            cout << "  [OK] Student with ID " << target << " deleted.\n";
            return;
        }
    }

    cout << "  [Not Found] No student with ID " << target << ".\n";
}

/*
 * sortByGPA / sortByName / sortByID
 * -----------------------------------
 * All three use std::sort, which implements introsort:
 *   - Begins as quicksort (average O(n log n)).
 *   - Switches to heapsort when recursion depth exceeds 2·log n
 *     (guarantees O(n log n) worst case).
 *   - Switches to insertion sort for small partitions (≤ 16 elements).
 *
 * RAM Model : comparisons dominate; introsort performs
 *   at most c·n·log n comparisons for a small constant c.
 *
 * Time Complexity (all three sorts)
 *   Best case    O(n log n)  — introsort has no O(n) best case unlike quicksort.
 *   Average case O(n log n)
 *   Worst case   O(n log n)  — heapsort fallback prevents O(n²).
 *
 * Space Complexity : O(log n) auxiliary
 *   - std::sort is in-place; the call stack depth for introsort is O(log n).
 *   - No additional array or data structure is allocated.
 */

void sortByGPA(vector<Student>& students) {
    // Lambda comparator: two O(1) field accesses per comparison.
    sort(students.begin(), students.end(),          // O(n log n)
         [](const Student& a, const Student& b) {
             return a.gpa > b.gpa;                  // descending GPA
         });
    cout << "  [OK] Sorted by GPA (highest first).\n";
    displayAll(students);                           // O(n)
}

void sortByName(vector<Student>& students) {
    sort(students.begin(), students.end(),          // O(n log n)
         [](const Student& a, const Student& b) {
             return a.name < b.name;                // ascending alphabetical
         });
    cout << "  [OK] Sorted by Name (A → Z).\n";
    displayAll(students);                           // O(n)
}

void sortByID(vector<Student>& students) {
    sort(students.begin(), students.end(),          // O(n log n)
         [](const Student& a, const Student& b) {
             return a.id < b.id;                    // ascending ID
         });
    cout << "  [OK] Sorted by ID (ascending).\n";
    displayAll(students);                           // O(n)
}

/*
 * displayStats
 * ------------
 * Computes min GPA, max GPA, average GPA, and total count.
 *
 * RAM Model : 3 operations per element (compare min, compare max, add to sum)
 *   + 1 final division → 3n + 1 total RAM operations.
 *
 * Time Complexity : O(n) — single pass over the vector.
 *
 * Space Complexity : O(1) — three scalar accumulators (minGPA, maxGPA, sum).
 */
void displayStats(const vector<Student>& students) {
    if (students.empty()) {
        cout << "\n  No records to compute statistics.\n";
        return;
    }

    double minGPA = students[0].gpa;    // O(1)
    double maxGPA = students[0].gpa;    // O(1)
    double sum    = 0.0;

    for (const auto& s : students) {   // O(n) — single pass
        if (s.gpa < minGPA) minGPA = s.gpa;   // O(1)
        if (s.gpa > maxGPA) maxGPA = s.gpa;   // O(1)
        sum += s.gpa;                          // O(1)
    }

    double avg = sum / students.size();        // O(1) division

    cout << "\n" << string(55, '=') << "\n";
    cout << "  STATISTICS\n";
    cout << string(55, '-') << "\n";
    cout << "  Total Students : " << students.size()                   << "\n";
    cout << "  Highest GPA    : " << fixed << setprecision(2) << maxGPA << "\n";
    cout << "  Lowest GPA     : " << fixed << setprecision(2) << minGPA << "\n";
    cout << "  Average GPA    : " << fixed << setprecision(2) << avg    << "\n";
    cout << string(55, '=') << "\n";
}

// ============================================================
//  MENU & ENTRY POINT
// ============================================================

/*
 * displayMenu
 * Time  : O(1) — fixed output.
 * Space : O(1).
 */
void displayMenu() {
    cout << "\n" << string(55, '=') << "\n";
    cout << "      STUDENT RECORD MANAGEMENT SYSTEM\n";
    cout << string(55, '=') << "\n";
    cout << "  [1]  Add Student\n";
    cout << "  [2]  Display All Students\n";
    cout << "  [3]  Search by ID\n";
    cout << "  [4]  Search by Name\n";
    cout << "  [5]  Delete Student\n";
    cout << "  [6]  Sort by GPA\n";
    cout << "  [7]  Sort by Name\n";
    cout << "  [8]  Sort by ID\n";
    cout << "  [9]  View Statistics\n";
    cout << "  [0]  Exit\n";
    cout << string(55, '-') << "\n";
    cout << "  Enter choice: ";
}

/*
 * main
 * ----
 * Drives the program with a menu loop.
 *
 * RAM Model : the loop body executes one menu read (O(1)) then dispatches
 *   to the chosen operation.  The number of loop iterations is unbounded
 *   (user-controlled), so the overall runtime of the program is
 *   O(iterations × cost_of_chosen_operation).
 *
 * Space Complexity of main : O(n) dominated by the students vector.
 *   - vector<Student> students : O(n) on the heap.
 *   - choice (int)             : O(1) on the stack.
 */
int main() {
    /*
     * vector<Student> students
     * -------------------------
     * RAM Model : declaring a vector = 1 allocation operation (O(1)).
     * Space     : O(1) at declaration; grows to O(n) as students are added.
     *
     * A vector stores:
     *   - Pointer to heap array  : O(1)
     *   - size (current count)   : O(1)
     *   - capacity               : O(1)
     * The heap array holds n Student objects → O(n) total.
     */
    vector<Student> students;

    // Pre-load sample data so the system is not empty at startup.
    // Each push_back is O(1) amortised; 5 calls total = O(1).
    students.push_back(Student(1001, "Yousaf",  3.85));
    students.push_back(Student(1002, "Sadeem",      2.90));
    students.push_back(Student(1003, "Ali Hassan",    3.50));
    students.push_back(Student(1004, "Muhammad Ali",    3.10));
    students.push_back(Student(1005, "Junaid Khan",   3.95));

    int choice;

    // Main event loop — runs until user enters 0.
    // Each iteration: O(1) menu read + O(f(n)) for the chosen operation.
    do {
        displayMenu();                       // O(1)
        cin >> choice;                       // O(1) read

        switch (choice) {
            case 1:  addStudent(students);      break; // O(n) [includes dup check]
            case 2:  displayAll(students);      break; // O(n)
            case 3:  searchByID(students);      break; // O(n)
            case 4:  searchByName(students);    break; // O(n)
            case 5:  deleteStudent(students);   break; // O(n)
            case 6:  sortByGPA(students);       break; // O(n log n)
            case 7:  sortByName(students);      break; // O(n log n)
            case 8:  sortByID(students);        break; // O(n log n)
            case 9:  displayStats(students);    break; // O(n)
            case 0:  cout << "\n  Goodbye!\n"; break;
            default: cout << "\n  [Error] Invalid choice. Try again.\n";
        }

        // Clear any leftover characters in stdin after numeric input.
        if (choice != 4)                     // searchByName calls ignore itself
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (choice != 0);

    /*
     * On return from main the vector destructor runs — O(n) to free n objects.
     * This is part of program teardown and not counted in algorithmic analysis.
     */
    return 0;
}
