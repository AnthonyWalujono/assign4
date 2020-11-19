#ifndef CPSC_350_WINDOW_H
#define CPSC_350_WINDOW_H

class Window
{
public:

	Window() : occupied(false), idle(0) {}

	bool is_open() const { return !occupied; }
	void occupy(int time_needed);
	void update();
	int idle_time() const { return idle; }

private:

	bool occupied;
	int time_needed;	// The amount of time a student still needs at the window, if occupied
	int idle;

};

#endif