/**
 * �����ļ������ӿ�
 */
#ifndef _BFAVFS_H_
#define _BFAVFS_H_
//open��read��write��seek��close�ȡ�
//copy��move��stat��rename


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include "cloud_errno.h"
#include "db_table.h"
#include "rfsvfs.h"
#include "list.h"

typedef struct _BucketObject{
	char 		bucket_name[MAX_BUCKET_NAME_LEN];
	char 		path[MAX_FILE_PATH_LEN];
	char 		file_uuid[MAX_FILE_UUID_LEN];
	struct dl_list *head;
	int 		file_type;
	long long 	offset;
}BucketObject;


typedef struct _VFILE{
	void	*token;
	char	mode[8];
	FILE 	*fp;
	char 	*srcPath;
	char	*realPath;
	size_t 	offset;
	size_t 	length;
	char	uuid[MAX_FILE_UUID_LEN];
	BucketObject *bobject;
}VFILE;

BucketObject *build_bucket_object(char *path,void *token);


/**
 * ͨ���ļ�·����ȡ��ǰĿ¼�µ��ļ��б�
 * param:
 * dirPath Ŀ¼·��
 * startIndex ��ʵ�ļ�����ֵ����0��ʼ��
 * count ��Ҫ��startIndex���ļ�����
 * category ��ȡ��Щ����ļ�
 * sortType ����ʽ
 */
ERROR_CODE_VFS bfavfs_get_file_list(char* dirPath,v_file_list_t *vlist,void *token);



/**
 * open��read��write��seek��close �⼸�������Ƿ���Ҫ�ϲ��ȽϺã����� put��get��
 * �ô�������ͳһ���ơ�
 * ��������ԭ���ļ���д������ͳһ��
 */


/**
 * ��ĳ�ַ�ʽ���ļ�
 * param��
 * path���ļ�·��
 * mode����ģʽ
 * ��r�� ��ֻ����ʽ���ļ������ļ�������ڡ�
��r+�� �Կɶ�д��ʽ���ļ������ļ�������ڡ�
��rb+�� ��д��һ���������ļ��������д���ݣ��ļ�������ڡ�
��w�� ��ֻд�ļ������ļ��������ļ�������Ϊ0�������ļ����ݻ���ʧ�����ļ��������������ļ���
��w+�� �򿪿ɶ�д�ļ������ļ��������ļ�������Ϊ�㣬�����ļ����ݻ���ʧ�����ļ��������������ļ���
��a�� �Ը��ӵķ�ʽ��ֻд�ļ������ļ������ڣ���Ὠ�����ļ�������ļ����ڣ�д������ݻᱻ�ӵ��ļ�β�����ļ�ԭ�ȵ����ݻᱻ��������EOF��������
��a+�� �Ը��ӷ�ʽ�򿪿ɶ�д���ļ������ļ������ڣ���Ὠ�����ļ�������ļ����ڣ�д������ݻᱻ�ӵ��ļ�β�󣬼��ļ�ԭ�ȵ����ݻᱻ������ ��ԭ����EOF����������
��wb�� ֻд�򿪻��½�һ���������ļ���ֻ����д���ݡ�
��wb+�� ��д�򿪻���һ���������ļ����������д
��wx�� �����ı��ļ�,ֻ����д������.[C11]
��wbx�� ����һ���������ļ�,ֻ����д������.[C11]
��w+x�� ����һ���ı��ļ�,�����д.[C11]
��wb+x�� ����һ���������ļ�,�����д.[C11]
��w+bx�� ��"wb+x"��ͬ[C11]
��rt�� ֻ����һ���ı��ļ���ֻ���������
������wt�� ֻд�򿪻���һ���ı��ļ���ֻ����д����
������at�� ׷�Ӵ�һ���ı��ļ��������ļ�ĩβд����
������rb�� ֻ����һ���������ļ���ֻ���������
������wb�� ֻд�򿪻���һ���������ļ���ֻ����д����
������ab�� ׷�Ӵ�һ���������ļ��������ļ�ĩβд����
������rt+�� ��д��һ���ı��ļ����������д
������wt+�� ��д�򿪻���һ���ı��ļ��������д
������at+�� ��д��һ���ı��ļ���������������ļ�ĩ׷������
������rb+�� ��д��һ���������ļ����������д
������ab+�� ��д��һ���������ļ���������������ļ�ĩ׷������
 *
 * token����¼ʱ���ص�token
 */
VFILE* bfavfs_fopen(const char * path,const char * mode,void *token);

/**
 * �ļ���ȡ����
 */
size_t bfavfs_fread( void *buffer, size_t size, size_t count, VFILE *vf);

/**
 * �ļ�д����
 */
size_t bfavfs_fwrite(const void* buffer, size_t size, size_t count, VFILE* vf);

/**
 * �ļ�ָ��ƫ��
 * fromwhere��ƫ����ʼλ�ã��ļ�ͷ0(SEEK_SET)����ǰλ��1(SEEK_CUR)���ļ�β2(SEEK_END)��Ϊ��׼��ƫ��offset��ָ��ƫ���������ֽڵ�λ�á�
 */
int bfavfs_fseek(VFILE *vf, long offset, int fromwhere);


/**
 * ��ȡ�ļ�����
 */
int bfavfs_fstat(const char * path,struct stat *st,void *token);


/**
 * �ж��ļ��Ƿ��Ѷ���
 * �ļ�δ��������0
 * �ļ���������1
 */
int bfavfs_feof(VFILE* vf);

/**
 * ɾ��Ŀ¼�������ļ�
 
 */
int bfavfs_remove_type(char* path,int file_type,void * token);


/**
 * ͨ��UUID �ж��ļ��Ƿ����
 */
int bfavfs_exist(const char *uuid,void *token);

/**
 *ͨ��UUID list �ж��ļ��Ƿ����
 */
int bfavfs_list_exist(struct dl_list *head,void *token);

/**
 * �����ļ�����
 */
int bfavfs_fsetattr(const char *path,void *token);


/**
 * ͨ���ļ�·����ȡ��ǰĿ¼�µ��ļ��б�
 * param:
 * dirPath Ŀ¼·��
 * startIndex ��ʵ�ļ�����ֵ����0��ʼ��
 * count ��Ҫ��startIndex���ļ�����
 * category ��ȡ��Щ����ļ�
 * sortType ����ʽ
 */
ERROR_CODE_VFS _bfavfs_get_file_list(BucketObject* sObject,v_file_list_t *vlist,void * token);

VFILE* _bfavfs_fopen(BucketObject* sObject,const char * mode,void * token);

int _bfavfs_fclose( VFILE *vf,void* token);

/**
 * ��ȡ�ļ�����
 */
int _bfavfs_fstat(BucketObject* sObject,struct stat *st,void *token);

/**
 *ͨ��UUID �ж��ļ��Ƿ����
 */
int _bfavfs_exist(BucketObject* sObject,void *token);

/**
 * ��Ͱ����
 */
int _bfavfs_fcopy(BucketObject* sObject,BucketObject* dObject,void * token);


/**
 * ��Ͱ�ƶ�
 */
int _bfavfs_fmove(BucketObject* sObject,BucketObject* dObject,void * token);

/**
 * �ļ�������
 */
int _bfavfs_frename(BucketObject* sObject,BucketObject* dObject,void * token);

/**
 * ɾ��Ŀ¼�������ļ�
 
 */
int _bfavfs_remove(BucketObject* sObject,void * token);


/**
 * �����ļ���
 
 */
int _bfavfs_mkdir(BucketObject* sObject,void * token);

/**
 * �����ļ�����
 */
int _bfavfs_fsetattr(BucketObject* sObject,void *token);


/**
 *����fd�Ǹý��̴������ļ��������� �����ɹ�ִ��ʱ������0��ʧ�ܷ���-1��errno����Ϊ���µ�ĳ��ֵ
EBADF�� �ļ���������Ч
EIO �� ��д�Ĺ����з�������
EROFS, EINVAL���ļ����ڵ��ļ�ϵͳ��֧��ͬ��
 */
int _bfavfs_fsync( VFILE *vf,void* token);

/**
 *ftruncate()�Ὣ����fdָ�����ļ���С��Ϊ����lengthָ���Ĵ�С��
��������fdΪ�Ѵ򿪵��ļ������ʣ����ұ�������д��ģʽ�򿪵��ļ���
�������ԭ�����ļ���С�Ȳ���length���򳬹��Ĳ��ֻᱻɾȥ��
 *��������ֵ:ִ�гɹ��򷵻�0��ʧ�ܷ���-1������ԭ�����errno��
 */
int _bfavfs_ftruncate( VFILE *vf,off_t length,void* token);


/**
 *fallocate�Ĺ�����Ϊ�ļ�Ԥ��������ռ䡣
 *����ֵ:ִ�гɹ��򷵻�0��ʧ�ܷ���-1������ԭ�����errno��
 */
int _bfavfs_fallocate( VFILE *vf, int mode, off_t offset, off_t len,void* token);

/**
 *link()�Բ���newpath ָ��������������һ���µ�����(Ӳ����)������oldpath ��ָ�����Ѵ����ļ�. �������newpath ָ��������Ϊһ�Ѵ��ڵ��ļ��򲻻Ὠ������.
 *����ֵ���ɹ��򷵻�0, ʧ�ܷ���-1, ����ԭ�����errno.
 */
int _bfavfs_link( BucketObject* oObject, BucketObject* nObject,void* token);

/**
 *readlink()�Ὣ����path �ķ����������ݴ浽����buf ��ָ���ڴ�ռ�, ���ص����ݲ�����NULL���ַ�����β, ���Ὣ�ַ������ַ�������. ������bufsiz С�ڷ������ӵ����ݳ���, ���������ݻᱻ�ض�.
 *����ֵ��ִ�гɹ��򴫷���������ָ���ļ�·���ַ���, ʧ���򷵻�-1, ����������errno.
 */
int _bfavfs_readlink( BucketObject* rObject,char * buf, size_t bufsiz,void* token);

/**
 *symlink()�Բ���newpath ָ��������������һ���µ�����(��������)������oldpath ��ָ�����Ѵ����ļ�. ����oldpath ָ�����ļ���һ��Ҫ����, �������newpath ָ��������Ϊһ�Ѵ��ڵ��ļ��򲻻Ὠ������.
 *����ֵ���ɹ��򷵻�0, ʧ�ܷ���-1, ����ԭ�����errno.
 */
int _bfavfs_symlink( BucketObject* oObject, BucketObject* nObject,void* token);
//����futimensat�����ͨ���ƶ�һ���ļ��ľ���·�����޸��ļ���ʱ�����ԣ�����ʱfd���������ԡ�
int _bfavfs_utimensat( BucketObject* rObject,const struct timespec times[2], int flag,void* token);

#endif

