#include"Time.h"
#include"Function.h"
Time::Time() {
	start_num = 0;
	pause_num = 0;

	is_pause = false;
	is_start = false;
}
Time::~Time() {

}
void Time::start() {
	is_start = true;
	is_pause = false;
	start_num = SDL_GetTicks();
}
void Time::stop() {
	is_pause = false;
	is_start = false;

}
void Time::pause() {
	if (is_start && !is_pause) {
		is_pause = true;
		pause_num = SDL_GetTicks() - start_num;

	}
}
void Time::unpause() {
	if (is_pause) {
		is_pause = false;
		start_num = SDL_GetTicks() - pause_num;
		pause_num = 0;
	}
}
int Time::get_time() {
	if (is_start) {
		if (is_pause) {
			return pause_num;
		}
		else {
			return SDL_GetTicks() - start_num;
		}
	}
}
