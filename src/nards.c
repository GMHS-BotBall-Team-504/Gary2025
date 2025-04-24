#include <kipr/wombat.h>
/*
NOTES:
UNITS ARE STANDARDIZED TO MILIMETERS
*/
int rm=0;
int lm=1;
int rs=0;
int ls=1;
int speed=50;
int thresh=3200;
int main()
{
    camera_load_config("green_cup");
    if (camera_open()==1)
    {
        printf("HELLO");
        camera_update();
        msleep(10);
        printf("X:%d, Y:%d", get_object_center_x(0, 0), get_object_center_y(0, 0));
         printf("HELLO");
        
    }
    else{
        printf("BOOOO");
    }
    camera_close();
    return 0;
} 


```c
#include <kipr/wombat.h>
#include <stdio.h>
/*
NOTES:
UNITS ARE STANDARDIZED TO MILIMETERS
*/
int rm=0;
int lm=1;
int rs=0;
int ls=1;
int speed=50;
int thresh=3200;
int main()
{
    camera_load_config("green_cup");
    camera_open()

    int i = 0;
    for (i = 0; i < 10; i++){
        camera_update();
        msleep(10);
    }
    printf("HELLO");
    printf("X:%d, Y:%d", get_object_center_x(0, 0), get_object_center_y(0, 0));
    camera_close();
    return 0;
} 
```