#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <cstring>
#include <unistd.h>


using namespace std;

int main(){
    try{
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    const char* message = "Hello, server!";
    send(clientSocket, message, strlen(message), 0);

    close(clientSocket);
    }catch(const exception& e){
        cerr << e.what();
    }
    return 0;
}