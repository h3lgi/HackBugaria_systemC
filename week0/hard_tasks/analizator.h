#include <stdio.h>
#include <linux/types.h>

#define PROMISC_MODE_ON 1 //flag nerazbor4ivogo rejima
#define PROMISC_MODE_OFF 0 //flag vikliu4enia etogo rejima

struct ifparam
{
    __u32 ip; //ip adres
    __u32 mask; //maska podseti
    int mtu; //razmer mtu
    int index; // index interfeisa

} ifp;


