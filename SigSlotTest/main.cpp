#include "sigslot\sigslot.h"
#include <iostream>

using namespace sigslot;

class Light : public has_slots<>
{
public:
	void ToggleState() { std::cout << "Toggle state" << std::endl; }
	void TurnOn() { std::cout << "Turn on" << std::endl; }
	void TurnOff() { std::cout << "Turn off" << std::endl; }
};
class Switch
{
public:
	signal0<> Clicked;
};

Switch all_on, all_off;
Light lp1, lp2, lp3, lp4;

int main(int argc, char **argv)
{
	all_on.Clicked.connect(&lp1, &Light::TurnOn);
	all_on.Clicked.connect(&lp2, &Light::TurnOn);
	all_on.Clicked.connect(&lp3, &Light::TurnOn);
	all_on.Clicked.connect(&lp4, &Light::TurnOn);
	all_off.Clicked.connect(&lp1, &Light::TurnOff);
	all_off.Clicked.connect(&lp2, &Light::TurnOff);
	all_off.Clicked.connect(&lp3, &Light::TurnOff);
	all_off.Clicked.connect(&lp4, &Light::TurnOff);

	return 0;
}