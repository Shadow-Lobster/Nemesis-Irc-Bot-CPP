#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netdb.h>
#include "functions.h"
#include <regex>


void logOutgoing() {

}
int main() {
        int connected = 0; // Used to loop the program

        const std::string server = "irc.evilcorp.ga"; // network address
        const int port = 6667; // server port
        std::string nick = "Nemesis"; // NICK
        std::string user = "Nemesis 0 * cppBot"; // USER
        std::string channels = "#shadowcave,#cult,#bots"; //sepeate channels by comma(,)
        std::string owner = "@Man.With.Claws"; //owner of the bots, host name if set by services is preferable along with nick.
        std::string usermodes = "+B";
        /** Structs that hold the socket information **/

        struct sockaddr_in addr;
        struct hostent *host;

        /** Get an ip address from the network to connect to **/
        host = gethostbyname(server.c_str());

        /** Fill the members of the socket structs required to connect **/
        addr.sin_addr.s_addr = *(unsigned long*)host->h_addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons((unsigned short)port);
        int sockd = socket(AF_INET, SOCK_STREAM, 0);

        std::string nick_Raw = "NICK " + nick + "\r\n"; //NICK raw
        std::string user_Raw = "USER " + user + "\r\n"; //USER raw
        std::string join_Raw = "JOIN " + channels + "\r\n"; //JOIN channel raw
        std::string usermodes_Raw = "MODE " + nick + " " + usermodes + "\r\n";

        /** Connect to address **/
        connect(sockd, (struct sockaddr *)&addr, sizeof(addr));


        std::cout << "Connecting to: " << server << std::endl;

        char sockbuff[4096]; // array to hold the incoming socket data
        recv(sockd, sockbuff, 4096, 0);
        std::cout << sockbuff << std::endl;
        /** if received reply from server reply NICK and USER to server **/
        if(strstr(sockbuff, "NOTICE * :*** Looking up your hostname") != NULL) {
          send(sockd, nick_Raw.c_str(), nick_Raw.size(), 0); // Converts nick string to c-array and sends it to server
          std::cout << "sent: " << nick << " to server" << std::endl;
          send(sockd, user_Raw.c_str(), user_Raw.size(), 0); // Converts user string to c-array and sends it to server
          std::cout << "sent: " << user << " to server" << std::endl;
        }

        while (connected < 1) {
          memset(&sockbuff, '\0', sizeof(sockbuff)); // make sure sockbuff[] is empty
          recv(sockd, sockbuff, 4096, 0); // Recieve all the data from server to sockbuff[]
          std::string buffer = sockbuff; //converting sockbuff to string
          std::cout << sockbuff << std::endl;


          /** reply to ping when server requests **/
          if(strstr(sockbuff, "PING :") != NULL) {
            std::string pong = "PONG :" + buffer.substr(6,-1);
            send(sockd, pong.c_str(), pong.size(), 0);
            std::cout << pong << std::endl;
          }

                /** join channel/channels upon successfull connect and set usermodes and other stuffs **/
          if(strstr(sockbuff, " :End of message of the day") != NULL) {
            std::string channel;
            send(sockd, join_Raw.c_str(), join_Raw.size(), 0);
            send(sockd, usermodes_Raw.c_str(), usermodes_Raw.size(), 0);
          }

/*        std::string quit_Msg = "successfull";
          std::string quit_Raw = "QUIT " + quit_Msg + "\r\n";
          if(std::regex_match(buffer, std::regex(".*")))
            send(sockd, quit_Raw.c_str(), quit_Raw.size(), 0);
*/
        logIncoming(sockbuff); //logs every buffer
        }
        return 0;
}
