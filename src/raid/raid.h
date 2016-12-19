/*
 * =============================================================================
 *
 *       Filename: raid.h
 *
 *    Description:  raid manage.
 *
 *        Version:  1.0
 *        Created:  2016/12/19 17:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Oliver (), 515296288jf@163.com
 *   Organization:  
 *
 * =============================================================================
 */

#ifndef _RAID_H_
#define _RAID_H_
#include "bash.h"

#ifdef __cplusplus
extern "C"{
#endif

void (*onProgressChange)(int progress, int total,void *con);

typedef struct raid_info{
	int current_mode;//current mode: 1 single mode,2 double mode
	int disk_loc;//disk location :1 disk1,2 disk2 
	long long total_size;
	long long free_size;
}p_raid_info;
/*******************************************************************************
 * Description:
 *    get raid info;
 * Parameters:
 * 	current_mode: [OUT] current mode;
 *	disk_loc:[OUT] disk location;
 *    disk_info:[OUT] total_size,free_size;
 * Returns:
 *   <0:error,0:succ
 *******************************************************************************/
int raid_get_disk_info(_Out_ p_raid_info *raid_info);

/*******************************************************************************
 * Description:
 *    检测指定盘位磁盘是否正确安装;
 * Parameters:
 *	disk_loc:[IN] disk location;
 * Returns:
 *   <0:error,0:succ
 *******************************************************************************/
int raid_check_disk_status(_In_ int disk_loc);

/*******************************************************************************
 * Description:
 *    init new disk,include raid create and format;
 * Parameters:
 *	disk_loc:[IN] disk location;
 *    onProgressChange:[OUT] progress,total;
 * Returns:
 *   <0:error,0:succ
 *******************************************************************************/
int raid_new_disk_init(_In_ int disk_loc,void *conn,_Out_ void (*onProgressChange)(int progress, int total,void *conn));


/*******************************************************************************
 * Description:
 *    disk data rebuild;
 * Parameters:
 *	disk_loc:[IN] disk location;
 *    onProgressChange:[OUT] progress,total;
 * Returns:
 *   <0:error,0:succ
 *******************************************************************************/
int raid_disk_rebuild(_In_ int disk_loc,void *conn,_Out_ void (*onProgressChange)(int progress, int total,void *conn));


#ifdef __cplusplus
}
#endif

#endif


