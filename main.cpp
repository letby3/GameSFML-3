#include <iostream>
#include <SFML/Graphics.hpp>
#include <dos.h>
#include <bits/stdc++.h>
#include <string>
#include <stdio.h>
#include <windows.h>

using namespace std;
using namespace sf;

int mass[92][8], chess[8];
int index = 0;

namespace patch
{
	    template < typename T > std::string to_string( const T& n )
	    {
		    std::ostringstream stm ;
		    stm << n ;
		    return stm.str() ;
	    }
}

int check() {
	if (!index)
		return 1;
	if (chess[index] > 7) {
		chess[index] = 0;
		index--;
		return 0;
	}
	for (int i = 0; i < index; i++) {
		if (chess[index] == chess[i] || abs(chess[index] - chess[i]) == (index - i))
			return 0;
	}
	return 1;
}

void dogma() {
	int it = 0;
	do {
		if (check()) {
			if (index == 7) {
				for (int i = 0; i < 8; i++) {
					mass[it][i] = chess[i];
				}
				it++;
				chess[index]++;
			}
			else {
				index++;
			}
		}
		else {
			chess[index]++;
		}
	} while (chess[0] < 8);
}


int main() {
	dogma();
	int n = -1;
	
	RenderWindow window(VideoMode(496, 520), "ChessProblem");

	Font font;
	font.loadFromFile("CalibriL.ttf");
	Text numDogma("", font, 15), idDogma("", font, 15);
	numDogma.setFillColor(Color::Black);
	idDogma.setFillColor(Color::Black);
	idDogma.setPosition(24, 496);
	numDogma.setPosition(345, 496);

	Image ctIm, ferzIm;
	ctIm.loadFromFile("ChessTable.jpg");
	ferzIm.loadFromFile("ferz.png");
	ferzIm.createMaskFromColor(Color(255, 255, 255));

	Texture ctTe, ferzTe;
	ctTe.loadFromImage(ctIm);
	ferzTe.loadFromImage(ferzIm);

	Sprite ctSp, ferzSp[8];
	ctSp.setTexture(ctTe);
	ctSp.setPosition(0,0);

	for (int i = 0; i < 8;i++) {
		ferzSp[i].setTexture(ferzTe);
		ferzSp[i].setPosition(32, 30);
		//int(32 + mass[n][i] * 55), int(30 + i * 55)
	}

	while (window.isOpen())
	{
		sf::Event event;

		
		numDogma.setString(patch::to_string(n));
		string s = "";
		for (int i = 0; i < 8; i++) {
			s += (char)(97 + mass[(n < 0 ? 0 : n)][i]) + patch::to_string(8 - i) + ", ";
		}
		idDogma.setString(s);

		window.clear();
		window.draw(ctSp);
		for(int i = 0;i < 8;i++)
			window.draw(ferzSp[i]);
		window.draw(numDogma);
		window.draw(idDogma);
		window.display();

		while (1 == 1) {
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				Sleep(150);
				n++;
				n = (n > 91 ? 91 : n);
				for (int i = 0; i < 8; i++)
					ferzSp[i].setPosition(int(32 + mass[n][i] * 55), int(30 + i * 55));
				break;
			}
			
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				Sleep(150);
				n--;
				n = (n < 0 ? 0 : n);
				for (int i = 0; i < 8; i++)
					ferzSp[i].setPosition(int(32 + mass[n][i] * 55), int(30 + i * 55));
				break;
			}
		}
		cout << n << endl;
	}


	return 0;
}

