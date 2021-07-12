
#include "SDLApp.h"
#include "ObjectInfo.h"
#include <map>
#include "Socket.h"
#include "Button.h"

class Game
{
private:
 
    //Lista con la informacion de los otros jugadores
    std::map<std::string, ObjectInfo> jugadores;

    //Referencia a la App de SDL para gestionar el pintado, la ventana etc
    SDLApp *app = nullptr;
    //Textura de fondo
    SDLTexture *background = nullptr;
    //SOcket para comunicarnos con el servidor
    Socket socket;

    Button* bPapel=nullptr;
    Button* bTijeras=nullptr;
    Button* bPiedra=nullptr;
    bool waitingResult=false;
    //booleano para determinar si hemos perdido o no
    bool isRunning = true;

public:
    Game(const char *s, const char *p, const char *n);
    ~Game();

    void render() const;
    void initGame();
    void net_thread();
    void input_thread();
    void run();
};