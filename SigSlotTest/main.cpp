#include "sigslot\sigslot.h"
#include <iostream>

#define EXAMPLE_SWITCH_AND_LIGHT_BASIC			1
#define EXAMPLE_SWITCH_AND_LIGHT_NEW			2
#define EXAMPLE_ARGUMENT_TYPES					3
#define EXAMPLE_CONNECTING_SIGNALS_WITH_SLOTS	4
#define EXAMPLE_EMITTING_SIGNALS				5

#define EXAMPLE									1

#if EXAMPLE == EXAMPLE_SWITCH_AND_LIGHT_BASIC

class Light
{
public:
	void ToggleState() { std::cout << "Toggle state" << std::endl; }
	void TurnOn() { std::cout << "Turn on" << std::endl; }
	void TurnOff() { std::cout << "Turn off" << std::endl; }
};

class Switch
{
public:
	virtual void Clicked() = 0;
};

class ToggleSwitch : public Switch
{
public:
	ToggleSwitch(Light& lp)
		: m_lp(lp)
	{
	}
	virtual void Clicked()
	{
		m_lp.ToggleState();
	}
private:
	Light& m_lp;
};

int main(int argc, char **argv)
{
	Light lp1, lp2;
	ToggleSwitch tsw1(lp1), tsw2(lp2);

	tsw1.Clicked();
	tsw2.Clicked();

	return 0;
}

#elif EXAMPLE == EXAMPLE_SWITCH_AND_LIGHT_NEW

class Light : public sigslot::has_slots<>
{
public:
	void ToggleState() { std::cout << "Toggle state" << std::endl; }
	void TurnOn() { std::cout << "Turn on" << std::endl; }
	void TurnOff() { std::cout << "Turn off" << std::endl; }
};

class Switch
{
public:
	sigslot::signal0<> Clicked;
};

int main(int argc, char **argv)
{
	/**/
	Switch sw1, sw2;
	Light lp1, lp2;
	sw1.Clicked.connect(&lp1, &Light::ToggleState);
	sw2.Clicked.connect(&lp2, &Light::ToggleState);
	/**/

	/*
	Switch all_on, all_off;
	Light lp1, lp2, lp3, lp4;
	all_on.Clicked.connect(&lp1, &Light::TurnOn);
	all_on.Clicked.connect(&lp2, &Light::TurnOn);
	all_on.Clicked.connect(&lp3, &Light::TurnOn);
	all_on.Clicked.connect(&lp4, &Light::TurnOn);
	all_off.Clicked.connect(&lp1, &Light::TurnOff);
	all_off.Clicked.connect(&lp2, &Light::TurnOff);
	all_off.Clicked.connect(&lp3, &Light::TurnOff);
	all_off.Clicked.connect(&lp4, &Light::TurnOff);
	/**/

	return 0;
}

#elif EXAMPLE == EXAMPLE_ARGUMENT_TYPES

int main(int argc, char **argv)
{
	sigslot::signal0<>											sig0;
	sigslot::signal1<int>										sig1;
	sigslot::signal2<int, int>									sig2;
	sigslot::signal3<int, int, int>								sig3;
	sigslot::signal4<int, int, int, int>						sig4;
	sigslot::signal5<int, int, int, int, int>					sig5;
	sigslot::signal6<int, int, int, int, int, int>				sig6;
	sigslot::signal7<int, int, int, int, int, int, int>			sig7;
	sigslot::signal8<int, int, int, int, int, int, int, int>	sig8;

	return 0;
}

#elif EXAMPLE == EXAMPLE_CONNECTING_SIGNALS_WITH_SLOTS

class Slots : public sigslot::has_slots<>
{
public:
	void Slot0() {}
	void Slot1(bool) {}
	void Slot2(bool, char) {}
	void Slot3(bool, char, int) {}
	void Slot4(bool, char, int, float) {}
	void Slot5(bool, char, int, float, double) {}
	void Slot6(bool, char, int, float, double, char*) {}
	void Slot7(bool, char, int, float, double, char*, std::string) {}
	void Slot8(bool, char, int, float, double, char*, std::string, Slots) {}
};

int main()
{
	Slots mySlot;

	sigslot::signal0<>																sig0;
	sigslot::signal1<bool>															sig1;
	sigslot::signal2<bool, char>													sig2;
	sigslot::signal3<bool, char, int>												sig3;
	sigslot::signal4<bool, char, int, float>										sig4;
	sigslot::signal5<bool, char, int, float, double>								sig5;
	sigslot::signal6<bool, char, int, float, double, char*>							sig6;
	sigslot::signal7<bool, char, int, float, double, char*, std::string>			sig7;
	sigslot::signal8<bool, char, int, float, double, char*, std::string, Slots>		sig8;

	sig0.connect(&mySlot, &Slots::Slot0);
	sig1.connect(&mySlot, &Slots::Slot1);
	sig2.connect(&mySlot, &Slots::Slot2);
	sig3.connect(&mySlot, &Slots::Slot3);
	sig4.connect(&mySlot, &Slots::Slot4);
	sig5.connect(&mySlot, &Slots::Slot5);
	sig6.connect(&mySlot, &Slots::Slot6);
	sig7.connect(&mySlot, &Slots::Slot7);
	sig8.connect(&mySlot, &Slots::Slot8);

	return 0;
}

#elif EXAMPLE == EXAMPLE_EMITTING_SIGNALS

class Window
{
public: // signals
	sigslot::signal2<int, int> Resized;

public:
	Window() { }
	void SetSize(int width, int height)
	{
		Resized(width, height); // emit signal
	}
};

class WindowEventHandler : public sigslot::has_slots<>
{
public: // slots
	void OnResize(int width, int height)
	{
		std::cout << "Window size changed: " << width << " x " << height << std::endl;
	}
};

int main()
{
	Window w;
	WindowEventHandler eventHandler;
	
	w.Resized.connect(&eventHandler, &WindowEventHandler::OnResize);

	// changing window's size
	w.SetSize(1024, 768);
	w.SetSize(1900, 1080);
	w.SetSize(1366, 768);

	return 0;
}

#endif