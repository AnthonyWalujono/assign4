#ifndef CPSC_350_STUDENT_H
#define CPSC_350_STUDENT_H

class Student
{
public:

	Student(int arrival, int time_needed) : arrival(arrival), time_needed(time_needed), waiting(0) {}

	int arrival_time() const { return arrival; }
	int time_needed_at_window() const { return time_needed; }
	int waiting_time() const { return waiting; }

	void serve(int time_point) { waiting = time_point - arrival; }

private:

	int arrival;
	int time_needed;
	int waiting;
};

#endif