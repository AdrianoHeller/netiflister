#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>

#define ERROR -1
#define SUCCESS 0

int main(int argc, char* argv[]){
    // pointer to receive list of addresses
    struct ifaddrs* addresses;
    /** function to populate addresses pointer
     * if case treat exception
     **/
    if(getifaddrs(&addresses) == -1){
        printf("Getifaddress call failed\n");
        return ERROR;
    };
    // pointer to receive addresses from list
    struct ifaddrs* address = addresses;

    while(address){
      // loop through addresses with pointer
      int family = address->ifa_addr->sa_family;
        // filter the adapter data by inet type
        if(family == AF_INET || family == AF_INET6){
            printf("%s\t",address->ifa_name);
            printf("%s\t", family == AF_INET ? "IPv4" : "IPv6");
        // string to receive interface name
        char ap[100];
        // filter size by ternary type operation
        const int family_size = family == AF_INET ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);
        // get interfaces names by sending item info
        getnameinfo(address->ifa_addr,family_size,ap,sizeof(ap),0,0,NI_NUMERICHOST);

        printf("\t%s\n",ap);

        };
        // goto next item
        address = address->ifa_next;
    };
    // free memory allocated
    freeifaddrs(addresses);

    return SUCCESS;
};