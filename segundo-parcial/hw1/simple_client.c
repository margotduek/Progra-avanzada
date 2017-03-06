/*
    Margot Duek 
    A01021226
    Advanced Programming
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <netdb.h>

#define SERVICE_PORT 8642
#define BUFFER_SIZE 1024

void usage(char * program);
void connectToServer(char * address, char * port);
void communicationLoop(int connection_fd);
void blackjack(int connection_fd);


int main(int argc, char * argv[])
{
  printf("\n=== WELCOME TO ULTIMAMATE BLACKJACK by Margot Duek  ===\n");

  if (argc != 3)
    usage(argv[0]);

  connectToServer(argv[1], argv[2]);

  return 0;
}

// Show the user how to run this program
void usage(char * program)
{
  printf("Usage:\n%s {server_address} {port_number}\n", program);
  exit(EXIT_FAILURE);
}

// Establish a connection with the server indicated by the parameters
void connectToServer(char * address, char * port)
{
  struct addrinfo hints;
  struct addrinfo * server_info;
  int connection_fd;

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
  if ( getaddrinfo(address, port, &hints, &server_info) == -1 )
    {
      perror("ERROR: getaddrinfo");
      exit(EXIT_FAILURE);
    }

  ///// SOCKET
  // Use the information obtained by getaddrinfo
  connection_fd = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
  if ( connection_fd == -1 )
    {
      perror("ERROR: socket");
      exit(EXIT_FAILURE);
    }

  ///// CONNECT
  // Connect with the desired port
  if ( connect(connection_fd, server_info->ai_addr, server_info->ai_addrlen) == -1 )
    {
      perror("ERROR: connect");
      exit(EXIT_FAILURE);
    }

  // Release the memory of the list of addrinfo
  freeaddrinfo(server_info);

  // Establish the communication
  communicationLoop(connection_fd);

  // Close the socket
  close(connection_fd);
}

// Do the actual receiving and sending of data
void communicationLoop(int connection_fd)
{
  char buffer[BUFFER_SIZE];

  while (1)
    {

     
      
      printf("Hello! do you want to play this round? ( 1 for yes, 2 for no, empty to leave) : \n ");
      fgets(buffer, BUFFER_SIZE, stdin);

      // Finish the connection with a string containing only the '\n'
      if (strlen(buffer) == 1)
	{
	  printf("Leaving Ultimate Blackjack by Margot Duek\n");
	  break;
	}

      ///// SEND
      // Send a reply to the client
      if ( send(connection_fd, buffer, strlen(buffer)+1, 0) == -1 )
	{
	  perror("ERROR: send");
	  exit(EXIT_FAILURE);
	}

      if(*buffer == '1'){
	blackjack(connection_fd);
      }
      // Clear the buffer
      bzero(buffer, BUFFER_SIZE);

      ///// RECV
      // Read the request from the client
      if ( recv(connection_fd, buffer, BUFFER_SIZE, 0) == -1 )
	{
	  perror("ERROR: recv");
	  exit(EXIT_FAILURE);
	}
      printf("Dealer says: %s\n", buffer);
      

    }
}


void blackjack(int connection_fd){
  char buffer[BUFFER_SIZE];
  int chars_read;
  time_t t;
  const char *types [] = {"clubs", "hearts", "spades", "diamods"};
  
  /* Intializes random number generator */
  srand((unsigned) time(&t));
  const size_t types_count = sizeof(types) / sizeof(types[0]);
  
  int first = rand() % 13;
  int second = rand() % 13;
  int third = 0;
  int fourth = 0;
  char *stay;

  printf("First card : %d %s\n", first,  types[rand() % types_count]);
  printf("Second card : %d %s\n", second,  types[rand() % types_count]);

  printf("Do you want to stand(pres 1)  or bust (pres 2)?");
  scanf("%s", stay);
 
  if(*stay == '1'){
    //look_fot_the_winner();
  }else if(*stay == '2' ){
    third = rand() % 13;
    printf("Second third : %d %s\n", third,  types[rand() % types_count]);
  }else{
    printf("That is not a valid option, sorry!\n");
  }
  
}
