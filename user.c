#include "main.h"

/*
* TODO:
*	로그인 페이지
*	회원가입 페이지
*	로그인 판별 로직
*	회원가입 로직
*	아이디 중복 여부 검사
*	유저id AUTO_INCREMENT 유지 v
*   
*/

//미완성
void showLogin() {
	wchar_t id[100], password[100], encryptedPassword[65];


	system("cls");
	printf("\n\t\t\t  로그인 페이지");
	printf("\n\n\t\t\tID: ");
	wscanf(L"%ls", id);
	
	printf("\n\n\t\t\tPW: ");
	wscanf(L"%ls", password);

	trim(id); // 앞뒤 공백 제거
	trim(password);

	// 로그인 수행
	if (loginUser(id, password)){
		printf("\n\n\t\t로그인 성공");
	}
	else {
		printf("\n\n\t\t로그인 실패. 없는 계정입니다.");
	}
	
	Sleep(500);
}

// 회원가입 페이지
void showSignUp() {
	int userId;
	wchar_t email[100], password[100], phoneNumber[28], address[60], encryptedPassword[65];

	while (true) {
		system("cls");
		printf("\n\t\t\t  회원가입 페이지");
		printf("\n\n\t\t\t이메일: ");
		wscanf(L"%ls", email);
		trim(email); // 앞뒤 공백 제거
		if (isEmailExist(email)) {
			printf("\n\n\t\t\t이미 존재하는 이메일입니다.");
			Sleep(2000);
			continue;
		}

		printf("\n\n\t\t\t비밀번호: ");
		wscanf(L"%ls", password);
		printf("\n\n\t\t\t전화번호: ");
		wscanf(L"%ls", phoneNumber);
		printf("\n\n\t\t\t주소: ");
		wscanf(L"%[^\n]", address);

	}
	// userId는 AUTO_INCREMENT로 설정
	userId = getMaxId() + 1;
	sha256_wchar(password, encryptedPassword);

	// userList에 삽입
	insertUserNode(userId, email, encryptedPassword, phoneNumber, address);
	// 테이블에 백업
	backupUserList();
}

// user테이블 조회
userNode* loadUserList() {
	FILE* fp;
	fp = _wfopen(L"user.csv", L"r, ccs=UTF-8");

	userNode* tmp = userList;
	wchar_t line[300], email[100], phoneNumber[28], address[60];
	char password[65];
	int userId;

	// 에러 발생시 종료
	// (파일이 없는경우 또는 경로가 잘못 지정된 경우)
	if (fp == NULL) {
		printf("Error(loadUserList): user.csv 파일 오픈 에러!");
		Sleep(1000);
		return;
	}

	// fp가 NULL을 만나기 전까지 line에 파일 안의 문자열을 받는다.
	while (fgetws(line, sizeof(line) / sizeof(wchar_t), fp) != NULL) {
		swscanf(line, L"%d,%ls,%s,%ls,%[^\n]",
			userId,
			email, 
			password,
			phoneNumber,
			address);
		insertUserNode(userId, email, password, phoneNumber, address);
	}
}

void insertUserNode(
	int userId,
	const wchar_t* email, 
	const wchar_t* password, 
	const wchar_t* phoneNumber, 
	const wchar_t* address
) 
{
	// userNode 선언 및 초기화
	userNode* newUserNode = (userNode*)malloc(sizeof(userNode));
	newUserNode->userId = userId;
	wcscpy(newUserNode->email, email);
	wcscpy(newUserNode->password, password);
	wcscpy(newUserNode->phoneNumber, phoneNumber);
	wcscpy(newUserNode->address, address);
	newUserNode->next = NULL;

	// userList에 추가
	if (userList == NULL) {
		userList = newUserNode;
	}
	else {
		userNode* tmp = userList;
		for (tmp; tmp->next; tmp = tmp->next);
		tmp->next = newUserNode;
	}
}

bool isEmailExist(const wchar_t* email) {

	for (userNode* tmp = userList; tmp; tmp = tmp->next) {
		if (wcscmp(tmp->email, email) == 0) {
			return true; // 이메일이 존재함
		}
		tmp = tmp->next;
	}
	return false; // 이메일이 존재하지 않음
}

int getMaxId() {
	userNode* tmp = userList;
	int maxId = 0;

	// 아모고토 없으면 0
	if (tmp == NULL) return maxId;

	// DB의 AUTO_INCREMENT와 유사한 기능을 구현
	for (tmp; tmp; tmp = tmp->next) {
		if (tmp->userId > maxId) {
			maxId = tmp->userId;
		}
	}

	// 있으면 제일 큰값으루
	return maxId;
}

bool loginUser(const wchar_t* email, const wchar_t* password) {
	wchar_t encryptedPassword[65];
	sha256_wchar(password, encryptedPassword); // 비밀번호 암호화

	userNode* tmp = userList;

	for (tmp; tmp; tmp = tmp->next) {

		bool idCheck = wcscmp(tmp->email, email) == 0;
		bool pwCheck = wcscmp(tmp->password, encryptedPassword) == 0;
		
		// id 비교
		if (idCheck && pwCheck) {
			return true;
		}
	}

	return false;
}