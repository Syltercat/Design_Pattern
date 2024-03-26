#include <iostream>
#include <string>
using namespace std;

class Light {
public:
	void on() { cout << "on\n"; }
	void off() { cout << "off\n"; }

};

class Television {
public:
	void channel_Up() { cout << "up\n"; }
	void channel_Down() { cout << "Down\n"; }
	void subtitle_On() { cout << "subtitle On\n"; }
	void subtitle_Off() { cout << "subtitle Off\n"; }
};

int main() {
	string device = "light";
	string action = "on";

	if (device == "light") {
		Light* light = new Light();
		if (action == "on") {
			light->on();
		}
		else if (action == "off") {
			light->off();
		}
		else
			cout << "Invalid action\n";
	}
	else if (device == "television") {
		Television* television = new Television();
		if (action == "channelUp") {
			television->channel_Up();
		}
		else if (action == "channelDown") {
			television->channel_Down();
		}
		else if (action == "channelOn") {
			television->subtitle_On();
		}
		else if (action == "channelOff") {
			television->subtitle_Off();
		}
		else
			cout << "Invalid action\n";
	}
	return 0;
}