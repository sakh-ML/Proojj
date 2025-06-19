#include <sys/socket.h>
#include <sys/types.h>


int main(){

int my_socket = socket(AF_INET, SOCK_STREAM, 0);

if(my_socket == -1){
	return -1;
}
struct sockadrr_in my_addr;
memset(my_addr.sa_data, );

if(bind(my_socket, ))

	return 0;
}
