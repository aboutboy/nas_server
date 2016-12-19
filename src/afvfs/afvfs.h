/**
 * �߼�����ģ��
 * v 0.0.2
 */
#ifndef _AFVFS_H_
#define _AFVFS_H_

//#include "errorvfs.h"
#include "db_table.h"
#include "media_manage.h"

typedef struct
{
	/**
	 * �û���
	 */
	char* username;
	
	/**
	 * ʹ���������߼���
	 */
	long used;

	/**
	 * ���������߼���
	 */
	long total;

//	/**
//	 * ����ʹ������
//	 */
//	long used_physical;
//
//	/**
//	 * ����������
//	 */
//	long total_physical;

	uint8_t isAdmin;

} VFS_USER_INFO;


typedef image_info_t IMAGE_MEDIA_INFO;
typedef audio_info_t AUDIO_MEDIA_INFO;
typedef video_info_t VIDEO_MEDIA_INFO;
/**
 * ��ȡ�û��б���Ϣ
 */
ERROR_CODE_VFS afvfs_get_user_list(VFS_USER_INFO** user_info,const char * token);

/**
 * ��ȡý���ļ�С�ߴ�����ͼ.��������ͼ��Ҫ�����б��������ʽչʾ��
 */
ERROR_CODE_VFS afvfs_get_thumbnail_small(const char *path,FILE **fp,const char * token);

/**
 * ��ȡý���ļ��еȳߴ�����ͼ.��������ͼ��Ҫ�����ƶ��豸��С���豸�ڴ�ͼ���ʱչʾ��ͼƬ��
 */
ERROR_CODE_VFS afvfs_get_thumbnail_median(const char *path,FILE **fp,const char * token);


/**
 * ��ȡͼƬý���ļ���Ϣ
 */
ERROR_CODE_VFS afvfs_get_image_media_info(const char *path,IMAGE_MEDIA_INFO * image_media_info,const char * token);
/**
 * ��ȡ��Ƶý���ļ���Ϣ
 */
ERROR_CODE_VFS afvfs_get_audio_media_info(const char *path,AUDIO_MEDIA_INFO * audio_media_info,const char * token);
/**
 * ��ȡ��Ƶý���ļ���Ϣ
 */
ERROR_CODE_VFS afvfs_get_video_media_info(const char *path,VIDEO_MEDIA_INFO * video_media_info,const char * token);




////////////// ý���ļ�������///////////////////

/**
 * �����ļ�������ʱ���ص���ע��Ļص��������ύ���ϲ����������
 */
ERROR_CODE_VFS afvfs_set_on_new_file_handler(const char *new_file_real_path,
										const int meida_type,
										ON_NEW_FILE_HANDLE func,
										unsigned int pri);


/**
 * ��ȡһ��δʹ�õ��ļ�·�������Ի�ȡ��Ҫ��������ͼ��ü��������Ƶ��Ŀ��·����
 * �߼�ģ���ȡ����ʵ�ļ�·����ʱ����Ҫ�Ը�·�����б�ǣ���������ļ�û����ɻ����ʧ�ܵ�ʱ����Ҫ
 * ���������·�������������ļ���
 */
ERROR_CODE_VFS afvfs_get_new_file_path(char pathBuf[32]);


/**
 * ����ý���ļ�����ͼ.��������ͼ��Ҫ�����б��������ʽչʾ��
 */
ERROR_CODE_VFS afvfs_set_thumbnail_small(const char *real_path,const char *thumbnail_real_path);

/**
 * ����ý���ļ��е�����ͼ.��������ͼ��Ҫ�����ƶ��豸��С���豸�ڴ�ͼ���ʱչʾ��ͼƬ��
 */
ERROR_CODE_VFS afvfs_set_thumbnail_median(const char *real_path,const char *thumbnail_real_path);


/**
 * ����ͼƬý���ļ���Ϣ
 */
ERROR_CODE_VFS afvfs_set_image_media_info(const char *real_path,IMAGE_MEDIA_INFO * image_media_info);
/**
 * ������Ƶý���ļ���Ϣ
 */
ERROR_CODE_VFS afvfs_set_audio_media_info(const char *real_path,AUDIO_MEDIA_INFO * audio_media_info);
/**
 * ������Ƶý���ļ���Ϣ
 */
ERROR_CODE_VFS afvfs_set_video_media_info(const char *real_path,VIDEO_MEDIA_INFO * video_media_info);




#endif

