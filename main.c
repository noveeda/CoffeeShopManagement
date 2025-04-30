#include "main.h"

int main() {
	// 콘솔창 제목
	system("title Coffee Shop Management System");
	// 88*40크기 콘솔로 킴.
	system("mode con: cols=88 lines=40");
	// 모든 카테고리에 대해 한국어로 설정
	_wsetlocale(LC_ALL, L"kor");

	// 비밀번호가 틀리면 종료
	if (passwordCheck() == 0) {
		return 0;
	}

	loadCoffeeMenu();	// 커피 메뉴 읽어오기
	loadTodaySales();	// 오늘의 매출 읽어오기
	loadUserList();	// 사용자 정보 읽어오기
	mainMenu();
}

// 비밀번호가 맞으면 1 아니면 0을 반환한다.
int passwordCheck() {
	int password;

	printf("\n\t\t\t  커피숍 관리시스템!");
	printf("\n\n\t\t\t비밀번호를 입력하세요: ");
	scanf("%d", &password);

	if (password == 1234) {
		return 1;
	}

	printf("\n\t\t\t비밀번호가 틀립니다!\n시스템을 종료합니다!\n");
	Sleep(1000);
	return 0;
}

// menu.txt 파일에서 메뉴 정보를 읽어서 menuItemList에 저장한다.
void loadCoffeeMenu() {
	FILE* fp;	// 파일 포인터 선언
	menuItem* tmp = menuItemList;
	wchar_t line[256], menuName[30];
	int id, price;
	

	// menu.txt 파일을 읽기모드로 연다
	fp = _wfopen(L"menu.txt", L"rt, ccs=UTF-8");

	// 에러 발생시 종료
	// (파일이 없는경우 또는 경로가 잘못 지정된 경우)
	if (fp == NULL) {
		printf("Error(loadMenu): menu.txt 파일 오픈 에러!");
		return;
	}

	// fp가 NULL을 만나기 전까지 line에 파일 안의 문자열을 받는다.
	while (fgetws(line, sizeof(line) / sizeof(wchar_t), fp) != NULL) {
		/*
		* line에 받은 문자열을 다음 형식에 맞게 
		* 분해해서 각각 id, menuName, price에 값 할당한다.
		* %[^,] : 공백을 포함한 문자열을 받는다.
		*/ 
		swscanf(line, L"%d,%[^,],%d\n", &id, menuName, &price);
		insertCoffeeMenu(id, menuName, price);
	}

	//printf("%s", menuItemList->next->menuName);
}

void insertCoffeeMenu(int id, const wchar_t* menuName, int price) {
	menuItem* head;
	// 구조체 크기만큼 동적할당
	menuItem* tmp = (menuItem*)malloc(sizeof(menuItem));
	
	// 메모리 할당 후 매개변수로 받은 값을 구조체에 할당
	if (tmp != NULL) {
		tmp->id = id;
		wcscpy(tmp->menuName, menuName);
		tmp->price = price;
		tmp->next = NULL;

		//wprintf(L"%d, %ls, %d\n", tmp->id, tmp->menuName, tmp->price);
	}
	else {
		printf("메모리 할당 에러: insertCoffeeMenu\n");
		return;
	}

	// main.h에서 전역으로 깔아둔 menuItemList
	if (menuItemList == NULL) {
		/*
		* menuItemList가 비어있으면 지금 만든
		* tmp를 참조
		*/
		menuItemList = tmp;
	}
	else {
		/*
		* 안비어있으면 리스트 끝에다가
		* 만든 menuItem 이어붙이기(append)
		*/
		head = menuItemList;
		while (head->next != NULL) {
			head = head->next;
		}

		head->next = tmp;
	}
}