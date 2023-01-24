// 표준 입출력 라이브러리를 이용하여 copy.c와 동일한 프로그램 작성하기
#include <stdio.h>

int main(int argc, char **argv) {
    int n;
    FILE *in, *out;
    char buf[BUFSIZ];

    if (argc != 3) {
        fprintf(stderr, "Usage: fcopy file1 file2\n");
        return -1;
    }

    // 복사 원본 파일을 읽기 모드로 엶
    if ((in = fopen(argv[1], "r")) == NULL) {
        perror(argv[1]);
        return -1;
    }

    // 복사 결과 파일을 쓰기 모드(새로운 파일 생성|기존 파일 내용지움)로 엶
    if ((out = fopen(argv[2], "w")) == NULL) {
        perror(argv[2]);
        return -1;
    }

    while ((n = fread(buf, sizeof(char), BUFSIZ, in)) > 0) {
        fwrite(buf, sizeof(char), n, out);
    }

    fclose(out);
    fclose(in);

    return 0;
}