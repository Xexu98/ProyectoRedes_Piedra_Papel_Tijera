#include "Socket.h"
#include <vector>
#include <map>
#include "ObjectInfo.h"
#include <memory>
#include <mutex>


class GameServer
{
public:
    GameServer(const char * s, const char * p);

  
    void do_messages();
    void checkCollisions();
    void createObjects();

private:
    /**
     *  Lista de clientes conectados al servidor de Chat, representados por
     *  su socket
     */
    std::map<std::string,std::unique_ptr<Socket>> clients;
    std::map<std::string,ObjectInfo > players;
    
    float initTime = 0;

   
    Socket socket;

};