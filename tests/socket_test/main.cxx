// socket test
// connects to specified server and port, sends string 'hello', and waits to
// receive three bytes
//
// to use, start a server with: netcat -l -p 11111
// run test program: ./main localhost 11111
// netcat will receive 'hello'.  Type 'hi' as response in netcat and hit enter.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

//-----------------------------------------------------------------------------
int CreateSocket()
{
  int sock = socket(AF_INET, SOCK_STREAM, 0);

  // optional: turns off socket buffering (nagles algorithm)
  int on = 1;
  if (setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&on, sizeof(on)))
    {
    return -1;
    }

  return sock;
}

//-----------------------------------------------------------------------------
void CloseSocket(int sock)
{
  if (sock < 0)
    {
    return;
    }
  close(sock);
}

//-----------------------------------------------------------------------------
int Connect(int socketdescriptor, const char* hostName, int port)
{

  if (socketdescriptor < 0)
    {
    return -1;
    }

  struct hostent* hp;
  hp = gethostbyname(hostName);
  if (!hp)
    {
    unsigned long addr = inet_addr(hostName);
    hp = gethostbyaddr((char *)&addr, sizeof(addr), AF_INET);
    }

  if (!hp)
    {
    printf("Could not determine host.\n");
    return -1;
    }

  struct sockaddr_in name;
  name.sin_family = AF_INET;
  memcpy(&name.sin_addr, hp->h_addr, hp->h_length);
  name.sin_port = htons(port);

  return connect(socketdescriptor, reinterpret_cast<sockaddr*>(&name), 
    sizeof(name));
}

//-----------------------------------------------------------------------------
int Send(int socketdescriptor, const void* data, int length)
{
  if (socketdescriptor < 0)
    {
    return 0;
    }

  if (length == 0)
    {
    // nothing to send.
    return 1;
    }

  const char* buffer = reinterpret_cast<const char*>(data);
  int total = 0;
  do
    {
    int flags;

    // disabling, since not present on SUN.
    // flags = MSG_NOSIGNAL; //disable signal on Unix boxes.
    flags = 0;

    int n = send(socketdescriptor, buffer+total, length-total, flags);
    if(n < 0)
      {
      printf("Socket Error: Send failed.\n");
      return 0;
      }
    total += n;
    } while(total < length);
  return 1;
}

//-----------------------------------------------------------------------------
int Receive(int socketdescriptor, void* data, int length)
{
  if (socketdescriptor < 0)
    {
    return 0;
    }

  char* buffer = reinterpret_cast<char*>(data);
  int total = 0;
  do
    {

    int n = recv(socketdescriptor, buffer+total, length-total, 0);
    if(n < 1)
      {

      // a recv may be interrupted by a signal.  In this case we should
      // retry.
      int errorNumber = errno;
      if (errorNumber == EINTR) continue;

      printf("Socket Error: Receive failed.\n");
      return 0;
      }
    total += n;
    } while(total < length);
  return total;
}

int main(int argc, char* argv[]) {

  if (argc < 3)
    {
    printf("Usage: %s host port\n", argv[0]);
    return 1;
    }

  char* host = argv[1];
  int port = atoi(argv[2]);

  int SocketDescriptor = CreateSocket();
  if (!SocketDescriptor)
    {
    printf("Failed to create socket descriptor.\n");
    return 1;
    }

  if (Connect(SocketDescriptor, host, port) == -1)
    {
    CloseSocket(SocketDescriptor);
    printf("Failed to connect to server.\n");
    return 1;
    }

  Send(SocketDescriptor, "hello\n", 6);

  char buffer[255];
  Receive(SocketDescriptor, buffer, 3);
  buffer[2] = 0;
 
  printf("Received: %s\n", buffer);

  return 0;
}
