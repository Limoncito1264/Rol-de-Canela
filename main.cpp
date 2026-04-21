#include <iostream> 
#include <memory>
#include <vector>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <optional>

using namespace sf;

enum class GameState 
{
    Menu,
    NuevoJuego,
    Continuar,
    Jefes,
    Jefe1,
    Jefe2,
    Jefe3,
    Salir
};

class Boton
{
private:
    Text texto;
    RectangleShape figura;
    Color colorHover;
    Color colorNormal;

public:
    Boton(const String& text, Vector2f tamanio, Vector2f posicion, Color color, const Font& fuente) : texto(fuente), figura(tamanio), colorNormal(color) 
    {
        figura.setPosition(posicion);
        figura.setFillColor(color);
        texto.setString(text);
        texto.setPosition(posicion);

        colorHover = Color(
            color.r + 50,
            color.g + 50,
            color.b + 50
        );
        colorNormal = color;
    }

    void draw(RenderWindow& window)
    {
        window.draw(figura);
        window.draw(texto);
    }

    void hover(Vector2f posMouse)
    {
        if (figura.getGlobalBounds().contains(posMouse)) //getGlobalBounds te dice el area del boton, y contains te dice si el mouse esta adentro de esa area
        {
            figura.setFillColor(colorHover); // hover
        }
        else {
            figura.setFillColor(colorNormal); // normal
        }
    }

    bool clic(Vector2f mousePos)
    {
        return figura.getGlobalBounds().contains(mousePos);
    }
};

class Menu
{
private:
    Boton btnContinuar;
    Boton btnNuevo;
    Boton btnJefes;
    Boton btnSalir;

public:
    Menu(const Font& fuente)
        : btnContinuar("Continuar", { 200,50 }, { 100,100 }, Color::Blue, fuente),
        btnNuevo("Nueva partida", { 200,50 }, { 100,200 }, Color::Blue, fuente),
        btnJefes("Jefes", { 200,50 }, { 100,300 }, Color::Blue, fuente),
        btnSalir("Salir", { 200,50 }, { 100,400 }, Color::Blue, fuente)
    {}
    void actualizacion(RenderWindow& window)
    {
        Vector2i mousePixel = Mouse::getPosition(window);
        Vector2f mouse = window.mapPixelToCoords(mousePixel);

        btnContinuar.hover(mouse);
        btnNuevo.hover(mouse);
        btnJefes.hover(mouse);
        btnSalir.hover(mouse);
    }
    GameState handleEvent(const Event& event, const RenderWindow& window)
    {
        if (event.is<Event::MouseButtonPressed>()) {
            Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));

            if (btnNuevo.clic(mouse))
                return GameState::NuevoJuego;
            if (btnContinuar.clic(mouse))
                return GameState::Continuar;
            if (btnJefes.clic(mouse))
                return GameState::Jefes;
            if (btnSalir.clic(mouse))
                return GameState::Salir;
        }
        return GameState::Menu;
    }
    void dibujar(RenderWindow& window)
    {
        btnContinuar.draw(window); 
        btnNuevo.draw(window); 
        btnJefes.draw(window); 
        btnSalir.draw(window);
    }
};

class Jefes
{
private:
    Boton btnJefe1;
    Boton btnJefe2;
    Boton btnJefe3;
    Boton btnVolver;
public:
    Jefes(const Font& fuente):
        btnJefe1("Jefe 1", { 200,50 }, { 100,100 }, Color::Blue, fuente),
        btnJefe2("Jefe 2", { 200,50 }, { 100,200 }, Color::Blue, fuente),
        btnJefe3("Jefe 3", { 200,50 }, { 100,300 }, Color::Blue, fuente),
        btnVolver("Volver", { 200,50 }, { 100,400 }, Color::Blue, fuente)
    {}
    void actualizacion(RenderWindow& window)
    {
        Vector2i mousePixel = Mouse::getPosition(window);
        Vector2f mouse = window.mapPixelToCoords(mousePixel);

        btnJefe1.hover(mouse);
        btnJefe2.hover(mouse);
        btnJefe3.hover(mouse);
        btnVolver.hover(mouse);
    }
    GameState handleEvent(const Event& event, const RenderWindow& window)
    {
        if (event.is<Event::MouseButtonPressed>()) {
            Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));

            if (btnJefe1.clic(mouse))
                return GameState::Jefe1;
            if (btnJefe2.clic(mouse))
                return GameState::Jefe2;
            if (btnJefe3.clic(mouse))
                return GameState::Jefe3;
            if (btnVolver.clic(mouse))
                return GameState::Menu;
        }
        return GameState::Jefes; 
    }
    void dibujar(RenderWindow& window)
    {
        btnJefe1.draw(window);
        btnJefe2.draw(window);
        btnJefe3.draw(window);
        btnVolver.draw(window);
    }
};

class Jugador {
protected:
    std::string nombre;
    int hp;
    float velocidad;
    Texture texturaUp;
    Texture texturaDown;
    Texture texturaLeft;
    Texture texturaRight;
    Sprite sprite;

    Vector2f posicionAnterior;

    void initVariables() {
        this->velocidad = 10.f;
    }

    float escalaBase = 0.15f;

    void cambiarVista(const Texture& nuevaTextura) {
        this->sprite.setTexture(nuevaTextura, true);

        Vector2u sizeRef = this->texturaDown.getSize();
        Vector2u sizeNueva = nuevaTextura.getSize();

        float factorX = (static_cast<float>(sizeRef.x) / sizeNueva.x) * escalaBase;
        float factorY = (static_cast<float>(sizeRef.y) / sizeNueva.y) * escalaBase;

        this->sprite.setScale({factorX, factorY});
    }



public:

    Jugador(float x = 0.f, float y = 0.f) : sprite(texturaDown) {
        this->initVariables();

        if(!this->texturaUp.loadFromFile("jugador_w.png") || !this->texturaDown.loadFromFile("jugador_s.png") || !this->texturaLeft.loadFromFile("jugador_a.png") || !this->texturaRight.loadFromFile("jugador_d.png")) {
            std::cout << "Error cargando imagen " << std::endl;
        }

        this->cambiarVista(this->texturaDown);

        this->sprite.setPosition(Vector2f(x, y));

    }

    void regresarPosicion() {
        sprite.setPosition(posicionAnterior);
    }


    void updateInput() {
        posicionAnterior = sprite.getPosition();
        //imputs del teclado
        //Izquierda
        if(Keyboard::isKeyPressed(Keyboard::Key::A)) {
            this->cambiarVista(this->texturaLeft);
            this->sprite.move({-this->velocidad, 0.f});
        }
        else if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
            this->cambiarVista(this->texturaRight);
            this->sprite.move({this->velocidad, 0.f});
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
            this->cambiarVista(this->texturaUp);
            this->sprite.move({0.f, -this->velocidad});
        }
        else if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
            this->cambiarVista(this->texturaDown);
            this->sprite.move({0.f, this->velocidad});
        }

    }

    void updateWindowBoundsCollision(const RenderTarget* target) {

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

    FloatRect getBounds() const {
        return this->sprite.getGlobalBounds();
    }


    void update(const RenderTarget& target) {

        this->updateInput();

        //limites de la ventana (colision)
        this->updateWindowBoundsCollision(&target);

    }

    void render(RenderTarget& target) {
        target.draw(this->sprite);
    }

    ~Jugador() {}
};

class Objeto {
protected:
    const Texture& textura;
    Sprite sprite;

public:

    Objeto(const Texture& textura, Vector2f posicion) : textura(textura), sprite(textura) {
        
        this->sprite.setPosition(posicion);
        this->sprite.setScale(Vector2f(0.5f, 0.5f));

    }

    FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }


    void render(RenderTarget& target) {
        target.draw(sprite);
    }


};

class knight : public Jugador {
private:
    /*
    atributos hp, danio, forma, posicion
    */
public:
   void mover() { //Mover arriba izquierda y derecha
       
   }
    void ataca () { //Atacar izquierda, derecha, arriba y abajo
        
    }

};

class Mapa {
private:
    std::vector<RectangleShape> tiles;
public:

};


class Juego {
private:
    //Variables
    std::string nombre;
    RenderWindow* window; //Puntero
    VideoMode videoMode;

    Texture fondoTex;
    Sprite fondo;

    std::map<std::string, Texture> texturas;

    Jugador jugador;
    std::vector<std::unique_ptr<Objeto>> objetos;



    //Funcion privada para inicializar la ventana a 60 frames
    void iniciarWindow() {
        this->window->setFramerateLimit(60);
    }

public:
    //Constructores
    Juego(RenderWindow* win) : fondo(fondoTex) {
        this->window = win;
        iniciarWindow();

        if (!this->fondoTex.loadFromFile("suelo.png")) {
            std::cout << "Error cargando imagen " << std::endl;
        } 

        this->fondo.setTexture(this->fondoTex, true);

        if (!this->texturas["estanteria"].loadFromFile("estanteria.png")) {
            std::cout << "Error cargando estanteria " << std::endl;
        }

        this->objetos.push_back(std::make_unique<Objeto>(this->texturas["estanteria"], Vector2f(700.f, 0.f)));
        this->objetos.push_back(std::make_unique<Objeto>(this->texturas["estanteria"], Vector2f(500.f, 0.f)));
    }

    //Funciones

    bool running() const { //Funcion que checa si la ventana esta abierta
        return this->window->isOpen();
    }

    void update() //Updatear frame
    {

        this->jugador.update(*this->window);

        for (auto& obj : objetos) {
            if (jugador.getBounds().findIntersection(obj->getBounds())) {
                jugador.regresarPosicion();
            }
        }


    }

    void render() //Rendereizado del juego
    {
        //Dibujar fondo
        this->window->draw(this->fondo);

        //Dibujar juego
        for (auto& obj : objetos) {
            obj->render(*this->window);
        }
        this->jugador.render(*this->window);
    }

    //Destructores

    ~Juego() {}

};

int main () {

    //ventana
    RenderWindow ventana(VideoMode({1000, 600}), "Proyecto", Style::Titlebar | Style::Close);

    Font fuente;
    if (!fuente.openFromFile("Ldfcomicsans-jj7l.ttf")) {
        return -1;
    }


    Menu menu(fuente);
    Jefes jefes(fuente); 
    Juego juego(&ventana);

    GameState Estado = GameState::Menu;

    //loop del juego
    while (ventana.isOpen())
    {
       //eventos
       while (const std::optional evento = ventana.pollEvent())
       {
            if (evento->is<Event::Closed>())
                ventana.close();


            if (const auto* keyPressed = evento->getIf<Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Escape)
                    ventana.close();
            }


            if (Estado == GameState::Menu)
                Estado = menu.handleEvent(*evento, ventana);
            else if (Estado == GameState::Jefes) 
                Estado = jefes.handleEvent(*evento, ventana);
        }

        if (Estado == GameState::Jefe1)
            juego.update();

       //Actualización
       if (Estado == GameState::Menu)
       {
           menu.actualizacion(ventana);
       }
       else if (Estado == GameState::Salir)
       {
           ventana.close();
       }
       else if (Estado == GameState::Jefes)
       {
           jefes.actualizacion(ventana);
       }

       //Renderizacion
       ventana.clear();

        if (Estado == GameState::Menu)
        {
            menu.dibujar(ventana);
        }
        else if (Estado == GameState::NuevoJuego)
        {
            // aquí iría el juego
        }
        else if (Estado == GameState::Jefes)
        {
            jefes.dibujar(ventana);
        }
        else if (Estado == GameState::Jefe1)
        {
            juego.render();
        }

       ventana.display();
    }

    return 0;
}
