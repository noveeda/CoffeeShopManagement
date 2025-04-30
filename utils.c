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

// wstr의 값을 sha256 암호화 처리한다.
void sha256_wchar(const wchar_t* wstr, wchar_t* output) {
    char mbstr[512];  // 변환된 멀티바이트 문자열 저장

    // wchar_t* -> char* 로 변환 (UTF-8로)
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, mbstr, sizeof(mbstr), NULL, NULL);

    // SHA-256 해시 계산 (EVP 사용)
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLen;
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();

    EVP_DigestInit_ex(ctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(ctx, mbstr, strlen(mbstr));
    EVP_DigestFinal_ex(ctx, hash, &hashLen);

    EVP_MD_CTX_free(ctx);

    // 계산 결과를 16진수 char* 문자열로 변환
    char hexStr[65];
    for (int i = 0; i < hashLen; i++) {
        sprintf(hexStr + (i * 2), "%02x", hash[i]);
    }
    hexStr[64] = '\0';  // 널 종료

    wchar_t wHexStr[65];  // 반환할 wchar_t 배열 (static: 메모리 유지)
    MultiByteToWideChar(
        CP_UTF8,    // 변환 대상 코드 페이지
        0,          // 플래그(뭐하는건지 모르겠다)
        hexStr,     // 원본 데이터
        -1,         // 변환할 문자열 길이(-1이면 자동 계산)
        wHexStr,    // 결과를 받을 버퍼
        sizeof(wHexStr) / sizeof(wchar_t) // 버퍼 크기 = 130 / 2 = 65자
    );

    wcscpy(output, wHexStr);
}