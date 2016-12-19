/*
 * =============================================================================
 *
 *       Filename: v_file_table.h
 *
 *    Description: v_file table related data structure definition.
 *
 *        Version:  1.0
 *        Created:  2016/10/19 
 *       Revision:  none
 *       Compiler:  gcc
 *
 *          Author:  Oliver <henry.jin@dmsys.com>
 *   Organization:  longsys
 *
 * =============================================================================
 */
#ifndef V_FILE_TABLE_H
#define V_FILE_TABLE_H


#ifdef __cplusplus
extern "C"{
#endif

#include "db_base.h"
#include "file_table.h"


#define  INVALID_V_FILE_ID    ((uint32_t)-1)
#define  V_FILE_TABLE_NAME  "v_file_table"

#define	MAX_FILE_NAME_LEN 	512
#define MAX_PASSWORD_LEN	32


typedef int (*real_remove)(char *path);
typedef int (*real_stat)(char *path,struct stat *st);




typedef enum
{
    V_FILE_TABLE_UPDATE_FILE_INFO    = 0x01,
    V_FILE_TABLE_UPDATE_FILE_LIST    = 0x02,
    V_FILE_TABLE_UPDATE_FILE_RENAME  = 0x03,
    V_FILE_TABLE_UPDATE_FILE_COPY	 = 0x04,
    V_FILE_TABLE_UPDATE_FILE_MOVE	 = 0x05,
    V_FILE_TABLE_UPDATE_IMAGE_INFO	 = 0x06,
    V_FILE_TABLE_UPDATE_AUDIO_INFO	 = 0x07,
    V_FILE_TABLE_UPDATE_VIDEO_INFO	 = 0x08,
    V_FILE_TABLE_UPDATE_THUM_INFO	 = 0x09,
}v_file_update_cmd_t;

typedef enum
{
    V_FILE_TABLE_QUERY_INFO    		= 0x01,
    V_FILE_TABLE_QUERY_LIST    		= 0x02,
    V_FILE_TABLE_QUERY_INFO_BY_UUID = 0x03,
    V_FILE_TABLE_QUERY_LIST_BY_UUID = 0x04,
    V_FILE_TABLE_SEARCH_QUERY_LIST  = 0x05,
    V_FILE_TABLE_QUERY_INFO_BY_PATH = 0x06,
    V_FILE_TABLE_QUERY_IMAGE_INFO	 = 0x07,
    V_FILE_TABLE_QUERY_AUDIO_INFO	 = 0x08,
    V_FILE_TABLE_QUERY_VIDEO_INFO	 = 0x09,
    V_FILE_TABLE_QUERY_THUM_INFO	 = 0x0A,
}v_file_query_cmd_t;

typedef enum
{
    V_FILE_TABLE_INSERT_INFO    		= 0x01,
    V_FILE_TABLE_INSERT_LIST    		= 0x02,
}v_file_insert_cmd_t;


typedef enum
{
    V_FILE_TABLE_DELETE_INFO    				= 0x01,
    V_FILE_TABLE_DELETE_TYPE_BY_PATH    		= 0x02,
}v_file_delete_cmd_t;


typedef enum
{
	/**
	 * �����ļ�
	 */
	ALL = 0,
	/**
	 * ��Ƶ
	 */
	VIDEO,
	/**
	 * ��Ƶ
	 */
	AUDIO,
	/**
	 * ͼƬ
	 */
	IMAGE,
	/**
	 * ͼƬ
	 */
	DOCU

} Category;
typedef enum
{
	/**
	 * ʱ������
	 */
	TIME_ASC,
	/**
	 * ʱ�併��
	 */
	TIME_DES,
	/**
	 * ��С����
	 */
	SIZE_ASC,
	/**
	 * ��С����
	 */
	SIZE_DES,
	/**
	 * ��������
	 */
	NAME_ASC,
	/**
	 * ���ֽ���
	 */
	NAME_DES,
	/**
	 * ��������
	 */
	TYPE_ASC,
	/**
	 * ���ͽ���
	 */
	TYPE_DES,
	/**
	 * ƴ������
	 */
	PINYIN_ASC,
	/**
	 * ƴ������
	 */
	PINYIN_DES
} SortType;


typedef struct
{
	/**
	 * �ļ���С
	 */
	size_t size;
	/**
	 * �ļ���
	 */
	char* name;
	/**
	 * �Ƿ����ļ�
	 */
	unsigned char is_dir;
	/**
	 * ����ʱ��
	 */
	long atime;
	/**
	 * ����ʱ��
	 */
	long ctime;
	/**
	 * �޸�ʱ��
	 */
	long mtime;

	
} FILE_ATTRIBUTE;


typedef struct
{
	/**
	 * �ļ�����
	 */
	int total;
	/**
	 * ����
	 */
	int len;

	/**
	 * authority ��Ϣ
	 */
	FILE_ATTRIBUTE file_attribute_list[];
} FILE_LIST;


typedef struct VfileTableList
{
	char		bucket_name[MAX_BUCKET_NAME_LEN];
	sqlite3*	database;
	uint8_t  	isDir;
	char		path[MAX_FILE_PATH_LEN];
	int		 	startIndex;//��ʵ�ļ�����ֵ����0��ʼ��
	int 	 	len;//��Ҫ��startIndex���ļ�����
	Category 	category;
	SortType 	sortType;	
	int 		parent_id;
	/*
	*	total file count;
	*/
	int			total;
	/**
	 * file list info
	 */
	int			file_type;
	int 		cmd;
	char 		search_str[64];
	struct dl_list head; //list head for result
}v_file_list_t;
typedef struct
{
	v_file_info_t 			v_file_info;
	char					bucket_name[MAX_BUCKET_NAME_LEN];
	v_file_insert_cmd_t  	cmd;
	real_remove			 	remove;
	real_stat				stat;
}v_file_insert_t;


typedef struct
{
	v_file_info_t 			v_file_info;
	v_file_info_t 			v_des_info;
	char					bucket_name[MAX_BUCKET_NAME_LEN];
	char					des_bucket_name[MAX_BUCKET_NAME_LEN];
	v_file_update_cmd_t 	cmd;
	real_remove			 	remove;
	real_stat				stat;
}v_file_update_t;

typedef struct
{
	v_file_list_t 		v_file_list;
	v_file_info_t 		v_file_info;
	char				bucket_name[MAX_BUCKET_NAME_LEN];
	v_file_query_cmd_t  cmd;
	real_remove			remove;
}v_file_query_t;

typedef struct
{
	v_file_info_t 		 v_file_info;
	char				 bucket_name[MAX_BUCKET_NAME_LEN];
	v_file_delete_cmd_t  cmd;
	real_remove			 remove;
}v_file_delete_t;

void register_v_file_table_ops(void);


#ifdef __cplusplus
}
#endif



#endif
