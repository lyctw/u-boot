#include <common.h>
#include <env.h>
#include <stdio.h>
#include <linux/string.h>

#define     DEFUALTDTB  "k510.dtb"

/**
 * @brief Set the cmd 
 * 
 * @param str eg: k510-dualcam.dtb
 * @return  if return -1, it means something wrong
 */
int set_bootcmd(const char *str)
{
    char *cmd = NULL;
    char buf[150] = {0};
    char *pos = buf;
    char *p;
    int ret = 0;

	if(!str){
		return -1;
    }

    cmd = env_get("bootcmd");
    if(!cmd)
        return -1;

    p = strstr(cmd, DEFUALTDTB);
    if(!p)
    {
        printf("there is no '%s' in cmd, use default dtb to start\n",DEFUALTDTB);
        return 0;
    }

    strncpy(pos, cmd, (p-cmd));
    strncpy(pos+(p-cmd), str, strlen(str));
    strncpy(pos+(p-cmd+strlen(str)), p+8, strlen(p+8));

    printf("******Yourself bootcmd is '%s' \n",buf);
    
    ret = env_set("bootcmd",buf);

    if(ret)
    {
        printf("bootcmd set failed!\n");
        return -1;
    }
    return 0;
}















