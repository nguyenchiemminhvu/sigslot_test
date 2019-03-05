#include "sigslot\sigslot.h"
#include <iostream>

using namespace sigslot;

class Window
{
public:
	Window() { }
	void SetSize(int width, int height)
	{
		Resized(width, height);
	}

public: // signals
	signal2<int, int> Resized;
};

class WindowMoniter : public has_slots<>
{
public: // slots
	void OnResize(int width, int height)
	{
		std::cout << "Window resized to " << width << " x " << height << std::endl;
	}
};

int main(int argc, char **argv)
{
	Window w;
	WindowMoniter m;
	w.Resized.connect(&m, &WindowMoniter::OnResize);
	w.SetSize(1024, 768);

	return 0;
}