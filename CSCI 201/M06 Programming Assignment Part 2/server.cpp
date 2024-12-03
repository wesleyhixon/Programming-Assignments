#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <map>

using namespace std;

// Map of abbreviations to long names
map<string, string> stateMap{
    {"AL", "Alabama"},
    {"AK", "Alaska"},
    {"AZ", "Arizona"},
    {"AR", "Arkansas"},
    {"CA", "California"},
    {"CO", "Colorado"},
    {"CT", "Connecticut"},
    {"DE", "Delaware"},
    {"FL", "Florida"},
    {"GA", "Georgia"},
    {"HI", "Hawaii"},
    {"ID", "Idaho"},
    {"IL", "Illinois"},
    {"IN", "Indiana"},
    {"IA", "Iowa"},
    {"KS", "Kansas"},
    {"KY", "Kentucky"},
    {"LA", "Louisiana"},
    {"ME", "Maine"},
    {"MD", "Maryland"},
    {"MA", "Massachusetts"},
    {"MI", "Michigan"},
    {"MN", "Minnesota"},
    {"MS", "Mississippi"},
    {"MO", "Missouri"},
    {"MT", "Montana"},
    {"NE", "Nebraska"},
    {"NV", "Nevada"},
    {"NH", "New Hampshire"},
    {"NJ", "New Jersey"},
    {"NM", "New Mexico"},
    {"NY", "New York"},
    {"NC", "North Carolina"},
    {"ND", "North Dakota"},
    {"OH", "Ohio"},
    {"OK", "Oklahoma"},
    {"OR", "Oregon"},
    {"PA", "Pennsylvania"},
    {"RI", "Rhode Island"},
    {"SC", "South Carolina"},
    {"SD", "South Dakota"},
    {"TN", "Tennessee"},
    {"TX", "Texas"},
    {"UT", "Utah"},
    {"VT", "Vermont"},
    {"VA", "Virginia"},
    {"WA", "Washington"},
    {"WV", "West Virginia"},
    {"WI", "Wisconsin"},
    {"WY", "Wyoming"}
};

int main(){
    // Create socket for server
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    
    // Create address for socket
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8000);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Bind address to socket
    bind(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    // Wait for connection on socket
    listen(sock, 5);

    // Runs indefinitely
    while(true){
        // Accepts new connection
        int clientSocket = accept(sock, nullptr, nullptr);
        
        // Receive message from client
        char buffer[1024] = {0};
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

        if(bytesReceived < 0){
            cerr << "Message not received" << endl;
        }

        // Outputting message from client
        cout << "Message from client: " << buffer << endl;


        string abbreviationString(buffer);
        string longName;

        // Finding long name for abbreviation
        for(auto itr = stateMap.begin(); itr != stateMap.end(); itr++){
            if(itr->first == buffer){
                longName = itr->second;
                break;
            }
            else{
                longName = "Abbreviation not found!";
            }
        }


        string message = "Here is your abbreviation in long form: " + longName;


        // Converting message to cstring and sending to client
        int messageSent = send(clientSocket, message.c_str(), message.length(), 0);

        if(messageSent < 0){
            cerr << "Message not sent" << endl;
        }

        // Closing socket
        close(clientSocket);
    }
}