/*
Margot Duek 
A01021226
Advanced programming 

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

// Include libraries for sockets
#include <netdb.h>
#include <arpa/inet.h>

#define SERVICE_PORT 8642
#define MAX_QUEUE 5
#define BUFFER_SIZE 1024

void usage(char * program);
void startServer(char * port);
void waitForConnections(int server_fd);
void communicationLoop(int connection_fd, char *client_presentation, int client_address_sin_port);
void blackjack(int connection_fd, char *client_presentation, int client_address_sin_port);


int main(int argc, char * argv[])
{
  printf("\n=== DEALER ===\n");

  if (argc != 2)
    usage(argv[0]);

  startServer(argv[1]);

  return 0;
}

// Show the user how to run this program
void usage(char * program)
{
  printf("Usage:\n%s {port_number}\n", program);
  exit(EXIT_FAILURE);
}

// Initialize the server to be ready for connections
void startServer(char * port)
{
  struct addrinfo hints;
  struct addrinfo * server_info;
  int server_fd;

  // Prepare the information to determine the local address
  // Clear all fields
  bzero(&hints, sizeof hints);
  // Use internet sockets with IPv4
  hints.ai_family = AF_INET;
  // Use connected sockets
  hints.ai_socktype = SOCK_STREAM;
  // Determine the ip of this machine automatically
  hints.ai_flags = AI_PASSIVE;

  ///// GETADDRINFO
  // Get the actual address of this computer
  if ( getaddrinfo(NULL, port, &hints, &server_info) == -1 )
    {
      perror("ERROR: getaddrinfo");
      exit(EXIT_FAILURE);
    }

  ///// SOCKET
  // Use the information obtained by getaddrinfo
  server_fd = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
  if ( server_fd == -1 )
    {
      perror("ERROR: socket");
      exit(EXIT_FAILURE);
    }

  ///// BIND
  // Connect with the desired port
  if ( bind(server_fd, server_info->ai_addr, server_info->ai_addrlen) == -1 )
    {
      perror("ERROR: bind");
      exit(EXIT_FAILURE);
    }

  // Release the memory of the list of addrinfo
  freeaddrinfo(server_info);

  ///// LISTEN
  // Prepare for connections
  if ( listen(server_fd, MAX_QUEUE) == -1 )
    {
      perror("ERROR: listen");
      exit(EXIT_FAILURE);
    }  
	  
  printf("Server ready and waiting!\n");
  // Stand by to receive connections from the clients
  waitForConnections(server_fd);

  // Close the socket
  close(server_fd);
}

// Stand by for connections by the clients
void waitForConnections(int server_fd)
{
  struct sockaddr_in client_address;
  socklen_t client_address_size;
  char client_presentation[INET_ADDRSTRLEN];
  int connection_fd;

  int pid,new;
  static int counter=0;  

  // Loop to wait for client connections
  while (1)
    {
      ///// ACCEPT
      // Receive incomming connections
      // Get the size of the structure where the address of the client will be stored
      client_address_size = sizeof client_address;
      // Receive the data from the client and open a new socket connection
      connection_fd = accept(server_fd, (struct sockaddr *) &client_address, &client_address_size);

      /*
	We make the fork so that every time someone else tryes to play the game they can 
	if there is an error, we close the connection 
	Otherwise, we have avarible named counter, that one counts the number of the proces that connected to the server 
       */
      if ((pid = fork()) == -1){
	close(connection_fd);
	continue;
      }
      else if(pid > 0){
	close(connection_fd);
	counter++;
	continue;
      }
      else if(pid == 0)
	{
	  char buf[100];

	  counter++;
	  snprintf(buf, sizeof buf, "hi %d", counter);

	  // Identify the client
	  // Get the ip address from the structure filled by accept
	  inet_ntop(client_address.sin_family, &client_address.sin_addr, client_presentation, sizeof client_presentation);
	  printf("Received connection from: %s : %d\n", client_presentation, client_address.sin_port);

	  // Establish the communication
	  communicationLoop(connection_fd, client_presentation, client_address.sin_port );
	  break;  
	}
          
      if ( connection_fd == -1 )
	{
	  perror("ERROR: accept");
	  exit(EXIT_FAILURE);
	}
    }
}

// Do the actual receiving and sending of data
void communicationLoop(int connection_fd, char *client_presentation, int client_address_sin_port){
  char buffer[BUFFER_SIZE];
  int message_counter = 0;
  int chars_read;

  while (1){
    // Clear the buffer
    bzero(buffer, BUFFER_SIZE);

    ///// RECV
    // Read the request from the client
    chars_read = recv(connection_fd, buffer, BUFFER_SIZE, 0);
    // Error when reading
    if ( chars_read == -1 ){
      perror("ERROR: recv");
      exit(EXIT_FAILURE);
    }
    // Connection finished
    if ( chars_read == 0 ){
      printf("Client disconnected\n");
      break;
    }

    message_counter++;
    printf("The client %d message #%d: %s\n", client_address_sin_port, message_counter, buffer);

    // Pretend to take some time to attend the request
    //sleep(3);

    if(*buffer == '1'){
     
      blackjack(connection_fd,  client_presentation, client_address_sin_port);
    }else if(*buffer == '2'){
      sprintf(buffer, "That is sad :( ! I hope next round you can join us!");
      //sprintf(buffer, "Reply to message #%d\n", message_counter);
      ///// SEND
      // Send a reply to the client
      if ( send(connection_fd, buffer, strlen(buffer)+1, 0) == -1 ){
	perror("ERROR: send");
	exit(EXIT_FAILURE);
      }      
    }
    else{
      sprintf(buffer, "That is not a valid option, sorry! ");
      //sprintf(buffer, "Reply to message #%d\n", message_counter);
      ///// SEND
      // Send a reply to the client
      if ( send(connection_fd, buffer, strlen(buffer)+1, 0) == -1 ){
	perror("ERROR: send");
	exit(EXIT_FAILURE);
      }      
    }    
  }
}

void blackjack(int connection_fd, char *client_presentation, int client_address_sin_port){
  char buffer[BUFFER_SIZE];
  int message_counter = 0;
  int chars_read;
  const char *types [] = {"clubs", "hearts", "spades", "diamods"};
  time_t t;
  int dealer = 0;
  int client;

  srand((unsigned) time(&t));
  const size_t types_count = sizeof(types) / sizeof(types[0]);  

  int first =1 + rand() % 10;
  int second = 1 + rand() % 10;
  int third =1 + rand() % 10;
  int fourth = 1 + rand() % 10;

  bzero(buffer, BUFFER_SIZE);
  sprintf(buffer, " You choosed to play blackjack, please bet your inicial fee! (5 changotickets)\n \n\n Fisrt card : %d %s \n Second card : %d %s \n ", first,  types[rand() % types_count], second,  types[rand() % types_count]);
  //sprintf(buffer, "Reply to message #%d\n", message_counter);
  ///// SEND
  // Send a reply to the client
  if ( send(connection_fd, buffer, strlen(buffer)+1, 0) == -1 ){
    perror("ERROR: send");
    exit(EXIT_FAILURE);
  }

  bzero(buffer, BUFFER_SIZE);
  ///// RECV
  // Read the request from the client
  chars_read = recv(connection_fd, buffer, BUFFER_SIZE, 0);
  // Error when reading
  if ( chars_read == -1 ){
    perror("ERROR: recv");
    exit(EXIT_FAILURE);
  }

  client = first + second;
    
  dealer = 15 +rand() % 15;
    
  if(dealer > 21 || client > dealer || client == 21){
    sprintf(buffer,"Congratulations! you won! Dealer got %d, you got %d", dealer, client);
  }else if(client > 21 || dealer > client){
    sprintf(buffer,"Sorry ... you lose!Dealer got %d you got %d", dealer, client);
  }
  ///// SEND
  // Send a reply to the client
  if ( send(connection_fd, buffer, strlen(buffer)+1, 0) == -1 ){
    perror("ERROR: send");
    exit(EXIT_FAILURE);
  }
    
}




