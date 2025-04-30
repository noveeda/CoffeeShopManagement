#include "main.h"

// 메뉴 z`리스트의 헤드 포인터
menuItem* menuItemList;

void mainMenu() {
	int choice;
	int s = 0;

	while (true) {
		showMainMenu();
		s = scanf("%d", &choice);

		switch (choice) {
		case 1:
			showCoffeeMenuList();
			break;
		case 2: // 주문(주문시 로그인 되있다면, 로그인 id 명기)
			order();
			break;
		case 3:
			deleteOrder();
			break;
		case 4:
			showOrderList();
			break;
		case 5:
			showSaleToday();
			break;
		case 6:
			if (addCoffeeMenu() == 1) {
				saveMenuFile();
			}
			break;
		case 7:
			if (deleteCoffeeMenu() == 1)
				saveMenuFile();
			break;
		case 8:
			backup();
			break;
		// 회원가입(이메일id,비밀번호,전화번호,주소_스페이스가능)
		case 9:
			showSignUp();
			break;
		// 회원전체 목록보고
		case 10:
			showUserList();
			break;
		// 회원정보 수정
		case 11:
			showUpdateUser();
			break;

		// 회원정보 삭제
		case 12:
			showDeleteUser();
			break;

		// 회원 로그인
		case 13:
			showLogin();
			break;
		
		case 0:
			if (close()) {
				return;
			}
			break;
		default:
			break;
		}
	}
}

// 메인 메뉴 출력
void showMainMenu() {
	system("cls");
	printf("\n\t\t\t\t=== 메인 메뉴 ===\n\n");
	printf("\t\t\t 1. 커피 메뉴 보기\n\n");
	printf("\t\t\t 2. 주문\n\n");
	printf("\t\t\t 3. 주문 취소\n\n");
	printf("\t\t\t 4. 주문 목록 확인\n\n");
	printf("\t\t\t 5. 오늘의 매출\n\n");
	printf("\t\t\t 6. 커피 메뉴 추가하기\n\n");
	printf("\t\t\t 7. 커피 메뉴 삭제하기\n\n");
	printf("\t\t\t 8. 데이터 저장\n\n");
	printf("\t\t\t 9. 회원가입\n\n");
	printf("\t\t\t 10. 회원전체 목록보고\n\n");
	printf("\t\t\t 11. 회원정보 수정\n\n");
	printf("\t\t\t 12. 회원정보 삭제\n\n");
	printf("\t\t\t 13. 회원 로그인\n\n");
	printf("\t\t\t 0. 끝내기\n\n");
	if (user) 
		wprintf(L"\t\t\t현재 사용자: %ls\n\n", user->email);
	else
		wprintf(L"\t\t\t현재 사용자: (null)\n\n");

	printf("\t\t\t메뉴를 선택해주세요(1~0): ");
}

void showCoffeeMenuList() {
	system("cls");

	printf("\n\t\t\t\t\t===(1) 커피 메뉴 보기===\n");
	showCoffeeMenu();

	waitZeroInput();
}

void showCoffeeMenu() {
	menuItem* tmp = menuItemList;

	printf("\n\t\t");
	printf("-----------------------------------------------------------------");
	printf("\n\t\t");
	printf("번호\t\t음료이름\t\t\t가격");
	printf("\n\t\t");
	printf("-----------------------------------------------------------------");
	

	while (tmp != NULL) {

		printf("\n\t\t");
		wprintf(L"%d\t\t%-22ls\t%d", tmp->id, tmp->menuName, tmp->price);
		printf("\n\t\t");
		printf("-----------------------------------------------------------------");

		tmp = tmp->next;
	}
}

int close() {
	char confirm[2];
	

	printf("\n\t\t\t시스템을 종료합니다...\n");
	printf("\n\t\t\t데이터를 저장했는지 확인하세요!\n");
	printf("\n\t\t\t지금 종료하시겠습니까?(y/n): ");
	
	scanf("%s", confirm);
	if (!strcmp(confirm, "y")) {
		return 1;
	}
	else {
		return 0;
	}
}

// 0 입력 전까지 화면 유지
void waitZeroInput() {
	int c = 1;

	printf("\n\n\t\t메인 메뉴로 돌아가려면 0을 누르세요:");
	while (c != 0) {
		scanf("%d", &c);
	}
}