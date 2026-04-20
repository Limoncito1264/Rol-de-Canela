#include <iostream> 
#include <memory>
#include <vector>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
using namespace std;


class Jugador {
protected:
    string nombre;
    int hp;
    float velocidad;
    sf::Texture texturaUp;
    sf::Texture texturaDown;
    sf::Texture texturaLeft;
    sf::Texture texturaRight;
    sf::Sprite sprite;

    sf::Vector2f posicionAnterior;

    void initVariables() {
        this->velocidad = 10.f;
    }

    float escalaBase = 0.2f;

    void cambiarVista(const sf::Texture& nuevaTextura) {
        this->sprite.setTexture(nuevaTextura, true);

        sf::Vector2u sizeRef = this->texturaDown.getSize();
        sf::Vector2u sizeNueva = nuevaTextura.getSize();

        float factorX = (static_cast<float>(sizeRef.x) / sizeNueva.x) * escalaBase;
        float factorY = (static_cast<float>(sizeRef.y) / sizeNueva.y) * escalaBase;

        this->sprite.setScale({factorX, factorY});
    }



public:

    Jugador(float x = 0.f, float y = 0.f) : sprite(texturaDown) {
        this->initVariables();

        if(!this->texturaUp.loadFromFile("jugador_w.png") || !this->texturaDown.loadFromFile("jugador_s.png") || !this->texturaLeft.loadFromFile("jugador_a.png") || !this->texturaRight.loadFromFile("jugador_d.png")) {
            cout << "Error cargando imagen " << endl;
        }

        this->cambiarVista(this->texturaDown);

        this->sprite.setPosition(sf::Vector2f(x, y));

    }

    void regresarPosicion() {
        sprite.setPosition(posicionAnterior);
    }


    void updateInput() {
        posicionAnterior = sprite.getPosition();
        //imputs del teclado
        //Izquierda
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            this->cambiarVista(this->texturaLeft);
            this->sprite.move({-this->velocidad, 0.f});
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            this->cambiarVista(this->texturaRight);
            this->sprite.move({this->velocidad, 0.f});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            this->cambiarVista(this->texturaUp);
            this->sprite.move({0.f, -this->velocidad});
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            this->cambiarVista(this->texturaDown);
            this->sprite.move({0.f, this->velocidad});
        }

    }

    void updateWindowBoundsCollision(const sf::RenderTarget* target) {

        float windowWidth = static_cast<float>(target->getSize(). x);
        float windowHeight = static_cast<float>(target->getSize(). y);

        //Izquierda
        if(this->sprite.getGlobalBounds().position.x <= 0.f)
            this->sprite.setPosition({0.f,this->sprite.getGlobalBounds().position.y});
        //Derecha
        else if(this->sprite.getGlobalBounds().position.x + this->sprite.getGlobalBounds().size.x >= windowWidth)
            this->sprite.setPosition({target->getSize().x - this->sprite.getGlobalBounds().size.x, this->sprite.getGlobalBounds().position.y});

        //Arriba
        if(this->sprite.getGlobalBounds().position.y <= 0.f)
            this->sprite.setPosition({this->sprite.getGlobalBounds().position.x, 0.f});
        //Abajo
        else if(this->sprite.getGlobalBounds().position.y + this->sprite.getGlobalBounds().size.y >= windowHeight)
            this->sprite.setPosition({this->sprite.getGlobalBounds().position.x, target->getSize().y - this->sprite.getGlobalBounds().size.y});
    }

    sf::FloatRect getBounds() const {
        return this->sprite.getGlobalBounds();
    }


    void update(const sf::RenderTarget* target) {

        this->updateInput();

        //limites de la ventana (colision)
        this->updateWindowBoundsCollision(target);

    }

    void render(sf::RenderTarget& target) {
        target.draw(this->sprite);
    }

    ~Jugador() {}
};

class Objeto {
protected:
    const sf::Texture& textura;
    sf::Sprite sprite;

public:

    Objeto(const sf::Texture& textura, sf::Vector2f posicion) : textura(textura), sprite(textura) {
        
        this->sprite.setPosition(posicion);
        this->sprite.setScale(sf::Vector2f(0.5f, 0.5f));

    }

    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }


    void render(sf::RenderTarget& target) {
        target.draw(sprite);
    }


};

class knight : public Jugador {
private:
    /*
    atributos hp, danio, forma, posicion
    */
public:
   mover() { //Mover arriba izquierda y derecha
       
   }
    ataca () { //Atacar izquierda, derecha, arriba y abajo
        
    }

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

    sf::Texture fondoTex;
    sf::Sprite fondo;

    map<string, sf::Texture> texturas;

    Jugador jugador;
    vector<unique_ptr<Objeto>> objetos;



    //Funcion privada para inicializar la ventana
    void iniciarWindow() {
        videoMode = sf::VideoMode({1280, 720});
        window.create(videoMode, "Videojuego", sf::Style::Titlebar | sf::Style::Close);
        window.setFramerateLimit(60);
    }

public:
    //Constructores
    Juego() : fondo(fondoTex) {
        this->iniciarWindow();

        if (!this->fondoTex.loadFromFile("suelo.png")) {
            cout << "Error cargando imagen " << endl;
        } 

        this->fondo.setTexture(this->fondoTex, true);

        if (!this->texturas["estanteria"].loadFromFile("estanteria.png")) {
            cout << "Error cargando estanteria " << endl;
        }

        this->objetos.push_back(std::make_unique<Objeto>(this->texturas["estanteria"], sf::Vector2f(700.f, 0.f)));
        this->objetos.push_back(std::make_unique<Objeto>(this->texturas["estanteria"], sf::Vector2f(500.f, 0.f)));
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

        for (auto& obj : objetos) {
            if (jugador.getBounds().findIntersection(obj->getBounds())) {
                jugador.regresarPosicion();
            }
        }


    }

    void render() //Rendereizado del juego
    {
        //Limpieza del frame antiguo
        this->window.clear();

        //Dibujar fondo
        this->window.draw(this->fondo);

        //Dibujar juego
        for (auto& obj : objetos) {
            obj->render(this->window);
        }
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
