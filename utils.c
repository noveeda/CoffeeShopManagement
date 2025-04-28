#include "main.h"

void trim(wchar_t* str) {
    wchar_t* start = str;
    wchar_t* end;

    // 앞쪽 공백을 다 건너뜀
    while (iswspace(*start)) {
        start++;
    }

    // 역참조로 문자열이 전부 공백일 경우 첫 문자를 널문자로 바꿔줌
    if (*start == L'\0') {
        str[0] = L'\0';
        return;
    }

    // 문자열 시작주소 + 널문자 전까지의 길이
    // = 문자열의 끝 주소
    end = start + wcslen(start) - 1;

    // 후위에서 전위로 이동하면서 공백은 다 널문자로 변환
    while (end > start && iswspace(*end)) {
        *end = L'\0';
        end--;
    }

    // str의 시작 위치를 첫 문자 위치로 변경해준다.
    if (start != str) {
        wchar_t* dst = str;
        while (*dst++ != L'\0');

        start = dst;
    }
}

void sha256_wchar(const wchar_t* wstr, char outputBuffer[65]) {
    char mbstr[512];  // 변환된 멀티바이트 문자열 저장

    // wchar_t* -> char* 로 변환 (UTF-8로)
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, mbstr, sizeof(mbstr), NULL, NULL);

    // SHA-256 계산
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;

    SHA256_Init(&sha256);
    SHA256_Update(&sha256, mbstr, strlen(mbstr));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[64] = 0;  // 널 종료
}