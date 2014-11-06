#include <sys/socket.h>
#include <linux/sockios.h>
#include <linux/ioctl.h>
//#include <linux/if.h>
#include <net/if.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include "analizator.h"

int getifconf(__u8 *intf, struct ifparam *ifp, int mode)
{
    int fd;
    struct sockaddr_in s;
    struct ifreq ifr; //vzial iz linux/if.h

    memset((void *)&ifr, 0, sizeof(struct ifreq));
    if((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0);
        return (-1);

    sprintf(ifr.ifr_name, "%s", intf);

    //proverka flaga rejima esli on 0 to nujno otkliu4iti 

    if(!mode) goto setmode;

    //opredelenie ip setevogo ustroistva

    if(ioctl(fd, SIOCGIFADDR, &ifr) < 0)
    {
        perror("ioctl SIOCGIFADDR");
        return -1;
    }

    memset((void*)&s, 0, sizeof(struct sockaddr_in));
    memcpy((void*)&s, (void*)&ifr.ifr_addr, sizeof(struct sockaddr));
    memcpy((void*)&ifp->ip, (void*)&s.sin_addr.s_addr, sizeof(__u32));

    //opredelenie maski podseti 

    if(ioctl(fd, SIOCGIFNETMASK, &ifr) < 0) 
    {
        perror("ioctl SIOCGIFNETMASK");
        return -1;
    }
    memset((void *)&s, 0, sizeof(struct sockaddr_in));
    memcpy((void *)&s, (void *)&ifr.ifr_netmask, sizeof(struct sockaddr));
    memcpy((void *)&ifp->mask, (void *)&s.sin_addr.s_addr, sizeof(u_long));

   //opredelenie mtu

    if(ioctl(fd, SIOCGIFMTU, &ifr) < 0)
    {
        perror("ioctl SIOCGIFMTU");
        return -1;
    }
    ifp->mtu = ifr.ifr_mtu;

   //index interfeisa

    if(ioctl(fd, SIOCGIFINDEX, &ifr) < 0)
    {
        perror("ioctl SIOCGIFINDEX");
        return -1;
    }
    ifp->index = ifr.ifr_ifindex;

    //utanovka v zadanii rejim 

setmode:

    //plu4enie zna4enia flagov 
    if(ioctl(fd, SIOCGIFFLAGS, &ifr) < 0) 
    {
        perror("ioctl SIOCGIFFLAGS");
        close(fd);
       return -1;
    }

    //v zavisimosti ot tretego parametra ustanavlivaiu flag 

    if(mode) 
        ifr.ifr_flags |= IFF_PROMISC;
    else 
        ifr.ifr_flags &= ~(IFF_PROMISC);
    
    //ustanovka v novie zna4enia flagov

    if(ioctl(fd, SIOCSIFFLAGS, &ifr) < 0)
    {
        perror("ioctl SIOCSIFFLAGS");
        close(fd);
        return -1;
    }
    return 0;

}
