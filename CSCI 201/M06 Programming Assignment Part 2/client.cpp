#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include <array>
#include <cstring>
#include <algorithm>
#include <arpa/inet.h>

using namespace std;

int main(){

    // Array of state abbreviations
    array<string, 50> stateAbbreviations = {
        "AL", "AK", "AZ", "AR", "CA", "CO", "CT", "DE", "FL", "GA", "HI", "ID", "IL", "IN", "IA", "KS", "KY", "LA", "ME", "MD", "MA", "MI", "MN", "MS", "MO", "MT", "NE", "NV", "NH", "NJ", "NM", "NY", "NC", "ND", "OH", "OK", "OR", "PA", "RI", "SC", "SD", "TN", "TX", "UT", "VT", "VA", "WA", "WV", "WI", "WY"
    };

    // Getting abbreviation
    string abbreviation;
    cout << "Please enter a state abbreviation: ";
    bool valid = false;
    while(!valid){
        try{
            // Get input
            cin >> abbreviation;
            if(!cin) throw(runtime_error("Please enter a valid 2-letter state abbreviation"));

            // Convert abbreviation to uppercase
            transform(abbreviation.begin(), abbreviation.end(),abbreviation.begin(), ::toupper);

            // Checking against list of abbreviations
            for(int i = 0; i < 50; i++){
                if(abbreviation == stateAbbreviations[i]){
                    valid = true;
                }
            }
            // If invalid
            if(!valid) throw(runtime_error("Please enter a valid 2-letter state abbreviation"));
        }catch(const exception& e){
            cerr << e.what() << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    // Client code
    try{
        // Creating new socket
        int sock = socket(AF_INET, SOCK_STREAM, 0);

        if(sock < 0){
            throw(runtime_error("Failure to create socket."));
        }
        
        // Building server address
        sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(8000);

        // Get IP address for server
        valid = false;
        while(!valid){
            string address;
            cout << "Please enter the server IPv4 address. Enter 127.0.0.1 for localhost: ";
            cin >> address;

            // Throws error if fails to set server IPv4 address
            if(inet_pton(AF_INET, address.c_str(), &serverAddress.sin_addr) <= 0){
                cerr << "Invalid IP address. Please try again." << endl;
                continue;
            }
            valid = true;
        }

        // Attempt to connect to server
        int connectionStatus = connect(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

        if(connectionStatus < 0){
            throw(runtime_error("Failure to connect."));
        }

        // Convert abbreviation to cstring and send to server
        const char* message = abbreviation.c_str();
        int messageSent = send(sock, message, abbreviation.size(), 0);

        if(messageSent < 0){
            throw(runtime_error("Message failed to send."));
        }

        // Recieving message from server
        char buffer[1024] = {0};
        int bytesRead = recv(sock, buffer, sizeof(buffer), 0);

        if(bytesRead < 0){
            throw(runtime_error("Error receiving message."));
        }
        if(bytesRead == 0){
            throw(runtime_error("No message received."));
            
        }

        // Outputting message
        cout << "Message from server: " << endl << buffer << endl;
        cout << "Exiting..." << endl;

        message = "QUIT";

        int messageSent = send(sock, message, sizeof(message), 0);
        if(messageSent < 0){
            cerr << "Failed to send exiting message to server." << endl;
        }
        // Closing connection and exiting
        close(sock);
    }catch(const exception& e){
        cerr << e.what();
        return -1;
    }
    return 0;
}