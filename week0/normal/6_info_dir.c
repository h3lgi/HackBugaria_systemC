#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "sys/inotify.h"
#include "sys/types.h"

#define EVENT_SIZE  (sizeof (struct inotify_event))
#define BUF_LEN     (1024 * (EVENT_SIZE + 16))

int main(int argc, char **argv)
{
    
    //int inotify_init();

    int len, i = 0;
    int fdiscr;
    int watch_discr;
    char buffer[BUF_LEN];

    fdiscr = inotify_init();

    if(fdiscr < 0)
    {
        perror("inotify_init");

    }

    watch_discr = inotify_add_watch(fdiscr, "/home/oleg/code/tmp/buff", 
            IN_MODIFY | IN_CREATE | IN_DELETE );

    len = read(fdiscr, buffer, BUF_LEN);

    if (len < 0)
    {
        perror("read");
    }

    while ( i < len )
    {
        struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
        if ( event->len )
        {
           if ( event->mask & IN_CREATE ) 
           {
                if ( event->mask & IN_ISDIR ) 
                {
                    printf( "the directory %s was created.\n", event->name );       
                }
                else 
                {
                    printf( "the file %s was created.\n", event->name );
                }
            }
            else if ( event->mask & IN_DELETE ) 
            {
                if ( event->mask & IN_ISDIR )
                {
                    printf( "the directory %s was deleted.\n", event->name );       
                }
                else
                {
                    printf( "the file %s was deleted.\n", event->name );
                }
            }
            else if ( event->mask & IN_MODIFY )
            {
                if ( event->mask & IN_ISDIR ) 
                {
                    printf( "the directory %s was modified.\n", event->name );
                }
                else 
                {
                    printf( "the file %s was modified.\n", event->name );
                }
            }
        }
       i += EVENT_SIZE + event->len;
    }

    ( void ) inotify_rm_watch( fdiscr, watch_discr );
    ( void ) close( fdiscr );

    //exit( 0 );

    return 0;
}
