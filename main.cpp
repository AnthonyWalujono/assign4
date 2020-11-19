#include <iostream>
#include <fstream>
#include "Queue.h"
#include "Window.h"
#include "Student.h"
using namespace std;

void read_input(istream& is, DoublyLinkedList<Window> &windows, Queue<Student>& waiting_line);
void print_stats(ostream& os, const DoublyLinkedList<int>& waiting_times, const DoublyLinkedList<int>& idle_times);
DoublyLinkedList<Window>::iterator get_next_open_window(const DoublyLinkedList<Window>& windows);
void update_all_windows(const DoublyLinkedList<Window>& windows);
bool are_any_windows_occupied(const DoublyLinkedList<Window>& windows);

int main(int argc, char** argv)
{
	DoublyLinkedList<Window> windows;
	Queue<Student> waiting_line;
	DoublyLinkedList<int> waiting_times;
	DoublyLinkedList<int> idle_times;

	// Validate the number of command line arguments
	if (argc != 2) {
		cout << "Incorrect tick_countber of command line arguments. Usage:" << endl;
		cout << "\tArgument1: <Input_file_name>" << endl;
		return -1;
	}

	// Attempt to open the input file
	ifstream fin(argv[1]);
	if (!fin.is_open()) {
		cout << "Unable to open input file \"" << argv[1] << "\"." << endl;
		return -2;
	}

	// Read the input file
	read_input(fin, windows, waiting_line);
	fin.close();

	// Process the arrivals
	if (!waiting_line.empty()) {

		int tick_count = 0;

		do {
			// Get the next student from the waiting line
			Student next_in_line = waiting_line.front();
			waiting_line.pop();
			int next_arrival = next_in_line.arrival_time();

			// Wait for the next open window
			auto it = get_next_open_window(windows);
			while (it == windows.end()) {
				update_all_windows(windows);
				++tick_count;
				it = get_next_open_window(windows);
			}

			// Keep updating windows until the clock reaches the next student's arrival time
			while (tick_count < next_arrival) {
				update_all_windows(windows);
				++tick_count;
			}

			// Send the student to the next open window
			next_in_line.serve(tick_count);
			idle_times.insertBack(it->idle_time());
			it->occupy(next_in_line.time_needed_at_window());
			waiting_times.insertBack(next_in_line.waiting_time());
			tick_count = next_arrival;

		} while (!waiting_line.empty());
	}

	// Calculate and print summary statistics from the waiting_times and idle_times lists
	print_stats(cout, waiting_times, idle_times);

	return 0;
}

void read_input(istream& is, DoublyLinkedList<Window>& windows, Queue<Student>& waiting_line)
{
	int num, student_count, time_needed;
	is >> num;	// First line is the number of windows

	// Create the windows
	windows.clear();
	while (num-- > 0) {
		windows.insertBack(Window());
	}

	// Populate the waiting line
	waiting_line.clear();
	while (is >> num) {	// Read the time point for the next group of students arriving
		is >> student_count;	// Read the numnber of students arriving at the current time

		// Read the number of minutes each arriving student needs at a window
		while (student_count-- > 0) {
			is >> time_needed;
			waiting_line.push(Student(num, time_needed));
		}
	}
}

void print_stats(ostream& os, const DoublyLinkedList<int>& waiting_times, const DoublyLinkedList<int>& idle_times)
{
	auto it = waiting_times.begin();
	int total = *it;
	int maxi = *it;
	int too_long_count = 0;
	if (*it > 10) {
		++too_long_count;
	}

	for (++it; it != waiting_times.end(); ++it) {
		total += *it;
		if (maxi < *it) {
			maxi = *it;
		}
		if (*it > 10) {
			++too_long_count;
		}
	}
	//Reads the stats 
	cout << "Mean wait time: " << (double)total / waiting_times.getSize() << endl;
	cout << "Maximum wait time: " << maxi << endl;
	cout << "Number of students waiting over 10 minutes: " << too_long_count << endl;

	it = idle_times.begin();
	total = *it;
	maxi = *it;
	too_long_count = 0;
	if (*it > 5) {
		++too_long_count;
	}

	for (++it; it != waiting_times.end(); ++it) {
		total += *it;
		if (maxi < *it) {
			maxi = *it;
		}
		if (*it > 5) {
			++too_long_count;
		}
	}

	cout << "Mean window idle time: " << (double)total / idle_times.getSize() << endl;
	cout << "Maximum window idle time: " << maxi << endl;
	cout << "Number of windows idle for over 5 minutes: " << too_long_count << endl;
}

DoublyLinkedList<Window>::iterator get_next_open_window(const DoublyLinkedList<Window>& windows)
{
	DoublyLinkedList<Window>::iterator it = windows.begin();
	for (; it != windows.end(); ++it) {
		if((*it).is_open()) {
			break;
		}
	}
	return it;
}

void update_all_windows(const DoublyLinkedList<Window>& windows)
{
	for (DoublyLinkedList<Window>::iterator it = windows.begin(); it != windows.end(); ++it) {
		(*it).update();
	}
}

bool are_any_windows_occupied(const DoublyLinkedList<Window>& windows)
{
	for (DoublyLinkedList<Window>::iterator it = windows.begin(); it != windows.end(); ++it) {
		if (!(*it).is_open()) {
			return true;
		}
	}
	return false;
}
