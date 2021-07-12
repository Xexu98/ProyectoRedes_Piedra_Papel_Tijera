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
    void compruebaResultados();

private:
    /**
     *  Lista de clientes conectados al servidor de Chat, representados por
     *  su socket
     */
    bool elegidoC1=false;
    bool elegidoC2=false;
    Message c1,c2;
    std::string nickC1,nickC2;
    std::map<std::string,std::unique_ptr<Socket>> clients;
    std::map<std::string,ObjectInfo > players;
    
    float initTime = 0;

   
    Socket socket;

};