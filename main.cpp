#include <iostream> 
#include <SFML/Graphics.hpp>
using namespace std;

class Juego {
private:
    string nombre;

public:



};


class Jugador {
private:
    string nombre;
    float velocidad;
    sf::RectangleShape body;
    sf::Vector2f posicion;

public:

};

class knight : public Jugador {
private:

public:
    void mover () {
        if (sf::Keyboard::isKeyPressed(W)) {
            posicion += [0,1];
        }
        if (sf::Keyboard::isKeyPressed(A)) {
            posicion += [1,0];
        }
        if (sf::Keyboard::isKeyPressed(S)) {
            posicion -= [0,1];
        }
        if (sf::Keyboard::isKeyPressed(D)) {
            posicion += [1,0];
        }
    }
}

class Mapa {
private:
    std::vector<sf::RectangleShape> tiles;
public:

};



int main (){
    sf:: RenderWindow window(sf::VideoMode({800, 600}), "Titulo");

    while (window.isOpen()) 
    {
        while (auto event = window.pollEvent()) 
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color(64, 64, 64));
        window.display();
    }

    return 0;
}
