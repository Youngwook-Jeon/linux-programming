// 하나의 파일의 내용을 다른 파일로 복사하기
#include <unistd.h> // UNIX 표준 시스템 콜
#include <fcntl.h>
#include <stdio.h> // perror()
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
    int n, in, out;
    char buf[1024];

    // 커맨드라인 인수로 복사할 파일명이 없을 경우 에러 출력하고 종료
    if (argc < 3) {
        write(2, "Usage : copy file1 file2\n", 25);
        return -1;
    }

    if ((in = open(argv[1], O_RDONLY)) < 0) {
        perror(argv[1]);
        return -1;
    }

    // 복사할 결과 파일을 쓰기 모드(새로운 파일 생성 | 기존 파일 내용 지움)로 엶
    if ((out = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR)) < 0) {
        perror(argv[2]);
        return -1;
    }

    // 원본 파일 내용을 읽어서 복사할 파일에 씀
    while((n = read(in, buf, sizeof(buf))) > 0) {
        write(out, buf, n);
    }

    // 열린 파일 닫기
    close(out);
    close(in);

    return 0;
}