#include <iostream> 

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
using namespace std;


class Jugador {
protected:
    string nombre;
    int hp;
    float velocidad;
    sf::RectangleShape shape;

    void initVariables() {
        this->velocidad = 5.f;
    }

    void initShape() {
        this->shape.setFillColor(sf::Color::Green);
        this->shape.setSize(sf::Vector2f(50.f, 50.f));
    }

public:

    Jugador(float x = 0.f, float y = 0.f) {
        this->shape.setPosition({x, y});
        this->initVariables();
        this->initShape();
    }


    void updateInput() {

        //imputs del teclado
        //Izquierda
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            this->shape.move({-this->velocidad, 0.f});
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            this->shape.move({this->velocidad, 0.f});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            this->shape.move({0.f, -this->velocidad});
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            this->shape.move({0.f, this->velocidad});
        }

    }

    void updateWindowBoundsCollision(const sf::RenderTarget* target) {

        float windowWidth = static_cast<float>(target->getSize(). x);
        float windowHeight = static_cast<float>(target->getSize(). y);

        //Izquierda
        if(this->shape.getGlobalBounds().position.x <= 0.f)
            this->shape.setPosition({0.f,this->shape.getGlobalBounds().position.y});
        //Derecha
        else if(this->shape.getGlobalBounds().position.x + this->shape.getGlobalBounds().size.x >= windowWidth)
            this->shape.setPosition({target->getSize().x - this->shape.getGlobalBounds().size.x, this->shape.getGlobalBounds().position.y});

        //Arriba
        if(this->shape.getGlobalBounds().position.y <= 0.f)
            this->shape.setPosition({this->shape.getGlobalBounds().position.x, 0.f});
        //Abajo
        else if(this->shape.getGlobalBounds().position.y + this->shape.getGlobalBounds().size.y >= windowHeight)
            this->shape.setPosition({this->shape.getGlobalBounds().position.x, target->getSize().y - this->shape.getGlobalBounds().size.y});
    }

    void update(const sf::RenderTarget* target) {

        this->updateInput();

        //limites de la ventana (colision)
        this->updateWindowBoundsCollision(target);

    }

    void render(sf::RenderTarget& target) {
        target.draw(this->shape);
    }

    ~Jugador() {}
};

class knight : public Jugador {
private:
    
public:
   
};

class Mapa {
private:
    std::vector<sf::RectangleShape> tiles;
public:

};


class Juego {
private:
    //Variables
    string nombre;
    sf::RenderWindow window;
    sf::VideoMode videoMode;

    Jugador jugador;

    //Funcion privada para inicializar la ventana
    void iniciarWindow() {
        videoMode.size = {800, 600};
        window.create(videoMode, "Videojuego", sf::Style::Titlebar | sf::Style::Close);
        window.setFramerateLimit(60);
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

        this->jugador.update(&this->window);
    }

    void render() //Rendereizado del juego
    {
        //Limpieza del frame antiguo
        this->window.clear();

        //Dibujar juego
        this->jugador.render(this->window);

        //Desplegar frame en el juego
        this->window.display();
    }

    //Destructores

    ~Juego() {}

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
