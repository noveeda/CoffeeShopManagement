// MAIN_H가 정의되지 않았다면 MAIN_H를 정의한다.
#ifndef MAIN_H
#define MAIN_H
#define _CRT_SECURE_NO_WARNINGS
#define WIDEN2(x) L##x
#define WIDEN(x) WIDEN2(x)

// 필요한 라이브러리와 헤더파일을 포함한다.
#include <windows.h>			// system 관련 함수 사용
#include <stdio.h>				// 입출력 관련 함수 사용
#include <stdlib.h>
#include <stdbool.h>			// true, false boolean 타입 사용
#include <string.h>				// 문자열 처리 함수 사용
#include <malloc.h>				// 힙 메모리 할당 함수 사용
#include <locale.h>				// 한국어 로케일 설정
#include <openssl/evp.h>		// SHA-256 암호화 알고리즘
#include "data.h"				// structure 정의

// 다른 파일에서 선언된 변수를 사용할 수 있게 한다.
extern menuItem* menuItemList;	// 커피 메뉴 연결리스트
extern orderNode* orderList;	// 주문 정보의 연결리스트
extern userNode* userList;		// 사용자 정보의 연결리스트
extern userNode* user;			// 로그인한 사용자 정보

// 함수 원형을 선언한다.
int passwordCheck();			// 암호 체크
void loadCoffeeMenu();			// 커피 메뉴 읽어오기
void insertCoffeeMenu(int id, const wchar_t* menuName, int price);
// 커피 메뉴를 리스트에 추가
int deleteCoffeeMenu();			// 커피 메뉴 삭제
void mainMenu();				// 메인 메뉴 선택과 처리
void showMainMenu();			// 메인 메뉴 보여주기
void showCoffeeMenuList();		// 1번 메뉴(커피 메뉴 보기)
void showCoffeeMenu();			// menuItemList의 내용 출력
int close();					// 0번 메뉴(끝내기)
void waitZeroInput();			// 0을 입력할 때까지 대기
void showSaleToday();			// 오늘의 매출 보기
void showOrderList();			// 4번 메뉴(주문 목록 확인)
void showOrders();				// orderList의 내용 출력
void saveMenuFile();			// 커피 메뉴를 파일에 저장
saleNode* addSales(saleNode* saleToday, orderNode* p);
// saleToday 리스트에 추가

// user.c 함수 원형
void showLogin();
void showSignUp();
void showUpdateUser();
void showDeleteUser();
void loadUserList();
void insertUserNode(
	int userId,
	const wchar_t* email, 
	const wchar_t* password,
	const wchar_t* phoneNumber, 
	const wchar_t* address);
bool isEmailExist(const wchar_t* email);
bool loginUser(const wchar_t* email, const wchar_t* password);
void deleteUser(int userId);
void updateUser(const wchar_t* phoneNumber, const wchar_t* address);
userNode* getUserNodeByEmail(const wchar_t* email);

// files.c
void backupUserList();

// utils.c
// wchar_t형 문자열을 sha256으로 암호화
void sha256_wchar(const wchar_t* wstr, wchar_t* output);
// 문자열 앞뒤 공백 제거
void trim(wchar_t* str);

// !MAIN_H
#endif 