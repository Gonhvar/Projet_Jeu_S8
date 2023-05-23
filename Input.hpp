#ifndef INPUT_HPP
#define INPUT_HPP

#include "Sprite.hpp"
#include "Mc.hpp"

class Input : public Sprite {
protected:
	int mouseX;
	int mouseY;

	float dashValue;

	Mc* _mc;

public:
	/* CONSTRUCTEURS ET DESTRUCTEURS */
	Input();

	virtual ~Input() override {};
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */
	void update();

	void get_keypress();
	void doKeyDown(SDL_KeyboardEvent& event);
	void doKeyUp(SDL_KeyboardEvent& event);
	void mousePress(SDL_MouseButtonEvent& b);
};

#endif