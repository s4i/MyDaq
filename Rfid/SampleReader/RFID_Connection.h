#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 10001

class RFID_Connection{
    public:
        int sock,ret;
        struct sockaddr_in server_addr;
        struct hostent *server_host;
        unsigned int addr;
        RFID_Connection();
        ~RFID_Connection();

        int CreateSocket(char *);
        int AcceptConnection(int );
};
