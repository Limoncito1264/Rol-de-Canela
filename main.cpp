#include <iostream> 

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
using namespace std;

class Juego {
private:
    //Variables
    string nombre;
    sf::RenderWindow window;
    sf::VideoMode videoMode;

    //Funcion privada para inicializar la ventana
    void iniciarWindow() {
        videoMode.size = {800, 600};
        window.create(videoMode, "Videojuego", sf::Style::Titlebar | sf::Style::Close);
    }

public:
    //Constructores
    Juego() {
        this->iniciarWindow();
    }

    //Funciones

    bool running() const { //Funcion que checa si la ventana esta abierta
        return this->window.isOpen();
    }

    void pollEvents() //Consulta de evento
    {
        
        while (auto event = this->window.pollEvent()) //Diferentes acciones en caso de un evento
        {
            if (event->is<sf::Event::Closed>()) { //Si se apreta el boton de cerrar, la ventana se cierra
                this->window.close();
            }

            if (auto key = event->getIf<sf::Event::KeyPressed>()) { //Si se preciona el escape la ventana se cierra
                if (key->code == sf::Keyboard::Key::Escape)
                    this->window.close();
            }
        }
    }

    void update() //Updatear frame
    {
        this->pollEvents();
    }

    void render() //Rendereizado del juego
    {
        //Limpieza del frame antiguo
        this->window.clear(sf::Color(255, 0, 0, 255));

        //Dibujar juego

        //Desplegar frame en el juego
        this->window.display();
    }

    //Destructores

    ~Juego() {}

};


class Jugador {
protected:
    string nombre;
    int hp;
    float velocidad;
    sf::RectangleShape body;
    sf::Vector2f posicion;

public:

};

class knight : public Jugador {
private:
    
public:
    void mover () {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            posicion.y -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            posicion.x -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            posicion.y += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            posicion.x += 1;
        }
    }
};

class Mapa {
private:
    std::vector<sf::RectangleShape> tiles;
public:

};



int main (){
    //Ventana
   Juego juego;

    while (juego.running())
    {

        //Actualizacion
        juego.update();

        //Renderizado
        juego.render();

    }


    return 0;
}
