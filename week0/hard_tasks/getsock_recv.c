//#include <linux/socket.h>
#include <linux/sockios.h>
#include <sys/socket.h>
#include <sys/types.h>
//#include <linux/types.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <string.h>

int getsock_recv(int index)
{
    int sd; //deskriptor soketa

    struct sockaddr_ll s_ll;

    sd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if(sd<0)
        return -1;
    memset((void*)&s_ll, 0, sizeof(struct sockaddr_ll));

    //zapolnenie polei adresnoi strukturi s_ll

    s_ll.sll_family = PF_PACKET; // tip soketa
    s_ll.sll_protocol = htons(ETH_P_ALL); // tip priniamaemogo protokola
    s_ll.sll_ifindex = index; // index

    if(bind(sd, (struct sockaddr*)&s_ll, sizeof(struct sockaddr_ll)) < 0)
    {
        close(sd);
        return -1;
    }
    return sd;



}
