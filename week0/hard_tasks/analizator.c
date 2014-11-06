#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <sys/socket.h>
#include <linux/if_ether.h>
#include <netinet/if_ether.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include "analizator.h"

//#interface eth0

__u8 buff[ETH_FRAME_LEN];

void mode_off()
{
    if(getifconf("eth0", &ifp, PROMISC_MODE_OFF) < 0)
    {
        perror("getifconf");
        exit(-1);
    }

    return;

}

int main()

{
	printf("sjjsjsj %s\n", "a");
    __u32 num = 0;
    int eth0_if, rec = 0, ihl = 0;
    struct iphdr ip; // struktura dlia ip
    struct tcphdr tcp; // tcp zagolovok
    struct ethhdr eth; // zagolovok  ethernet kadra
    static struct sigaction act;
	printf("sshshshsh\n");
    if(getifconf("wlp3s0", &ifp, PROMISC_MODE_ON) < 0) 
    {
       perror("getifconf");
       return -1;
    }
	printf("aloha");
    printf("IP address -> %s\n",inet_ntoa(ifp.ip));
    printf("Mask -> %s\n",inet_ntoa(ifp.mask));
    printf("MTU -> %d\n", ifp.mtu);
    printf("index -> %d\n", ifp.index);

	printf("4 %s", "ss");
    //polu4enie diskriptora paketnogo soketa
    if((eth0_if = getsock_recv(ifp.index)) < 0) 
    {
        perror("getsock_recv");
        return -1;
    }
	printf("5 %s", "ss");

    //opredelenie novogo obrabt4ika signala SIGINT funcia mode_off
    act.sa_handler = mode_off;
    sigfillset(&(act.sa_mask));
    sigaction(SIGINT, &act, NULL);

    //cikkl slejenia paketov
    for(;;) 
    {
        memset(buff, 0, ETH_FRAME_LEN);
        
	printf("1 %s", "ss");

        rec = recvfrom(eth0_if, (char *)buff, ifp.mtu + 18, 0, NULL, NULL);
        if(rec < 0 || rec > ETH_FRAME_LEN)
        {
            perror("recvfrom");
            return -1;
        }
        memcpy((void *)&eth, buff, ETH_HLEN);
        memcpy((void *)&ip, buff + ETH_HLEN, sizeof(struct iphdr));
        if((ip.version) != 4) 
            continue;
        memcpy((void *)&tcp, buff + ETH_HLEN + ip.ihl * 4, sizeof(struct tcphdr));

    //MAC adresa otpraviteiai polu4atelia
        printf("\n%u\n", num++);
        printf("%.2x:%.2x:%.2x:%.2x:%.2x:%.2x\t->\t",
        eth.h_source[0],eth.h_source[1],eth.h_source[2],
        eth.h_source[3],eth.h_source[4],eth.h_source[5]);

        printf("%.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",
        eth.h_dest[0],eth.h_dest[1],eth.h_dest[2],
        eth.h_dest[3],eth.h_dest[4],eth.h_dest[5]);

        printf("length of header - %d, ", (ip.ihl * 4));
        printf("length of packet - %d\n", ntohs(ip.tot_len));
        
        //esi protokol TCP otobrajaiu adresa i porti otpravitelia i polu4ateei
        if(ip.protocol == IPPROTO_TCP) 
        {
            printf("%s (%d)\t->\t",inet_ntoa(ip.saddr), ntohs(tcp.source));
            printf("%s (%d)\n",inet_ntoa(ip.daddr), ntohs(tcp.dest));
            printf("TCP packet\n");
        }
    }
    return 0;


}
