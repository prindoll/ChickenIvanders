#pragma once


class Time {
public:
	Time();
	~Time();

	void start();
	void pause();
	void unpause();
	void stop();

	int get_time();

	bool get_is_pause() { return is_pause; }
	bool get_is_start() { return is_start; }

private:
	int start_num;
	int pause_num;

	bool is_pause;
	bool is_start;


};