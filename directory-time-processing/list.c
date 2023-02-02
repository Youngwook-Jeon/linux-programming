// "ls -Rl" 명령어 만들기
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h> // 디렉토리 조작 함수
#include <pwd.h> // getpwuid(): uid를 이용하여 사용자의 이름 구하기
#include <grp.h> // getgrgid(): gid를 이용하여 그룹의 이름 구하기
#include <time.h> // localtime() 함수
#include <sys/stat.h>
#include <sys/types.h>

int listDir(char *arg) {
    DIR *pdir;
    struct dirent *dirt;
    struct stat statBuf;
    struct passwd *username;
    struct group *groupname;
    struct tm *t;
    int i = 0, count = 0;
    char *dirName[255], buf[255], permission[11], mtime[20];

    memset(dirName, 0, sizeof(dirName));
    memset(&dirt, 0, sizeof(dirt));
    memset(&statBuf, 0, sizeof(statBuf));

    if ((pdir = opendir(arg)) <= 0) {
        perror("opendir");
        return -1;
    }

    chdir(arg); // 프로세스의 워킹 디렉토리 변경
    getcwd(buf, 255); // 현재 디렉토리의 절대 경로를 가져와서 표시
    printf("\n%s: Directory\n", arg);

    while ((dirt = readdir(pdir)) != NULL) {
        lstat(dirt->d_name, &statBuf); // 현재 디렉토리에 대한 정보 가져오기
        // 파일 종류 검사하기
        if (S_ISDIR(statBuf.st_mode))
            permission[0] = 'd';
        else if (S_ISLNK(statBuf.st_mode))
            permission[0] = 'l';
        else if (S_ISCHR(statBuf.st_mode))
            permission[0] = 'c';
        else if (S_ISBLK(statBuf.st_mode))
            permission[0] = 'b';
        else if (S_ISSOCK(statBuf.st_mode))
            permission[0] = 's';
        else if (S_ISFIFO(statBuf.st_mode))
            permission[0] = 'P';
        else
            permission[0] = '-';

        // TODO: 권한 검사 및 서브 디렉토리 찾기
    }
    return 0;
}