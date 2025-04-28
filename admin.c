#include "main.h"

void showSaleToday() {
	system("cls");
	printf("\n\t\t\t\t=== (5) 오늘의 매출 ===\n");
	printf("\n\t\t\t오늘 현재까지 매출 : %d원\n", totalSales());
	waitZeroInput();
}

int totalSales() {
	orderNode* ptr;
	int totalSales = 0;

	for (ptr = orderList; ptr; ptr = ptr->next) {
		totalSales += (int)(ptr->price * ptr->sales);
	}

	return totalSales;
}

int addCoffeeMenu() {
	int id, price;
	wchar_t menuName[30] = L"";

	system("cls");
	printf("\n\t\t\t\t=== (6) 새로운 메뉴 추가 ===\n");
	showCoffeeMenu();

	printf("\n\n\t\t추가할 메뉴의 번호 입력(메뉴로 돌아가려면 0): ");
	scanf("%d", &id);

	if (id == 0) {
		return 0;
	}

	if (isInMenu(id)) {
		printf("\n\n\t\t이미 해당 번호에 메뉴가 존재합니다!");
		Sleep(2000);
		return 0;
	}

	getchar();
	printf("\n\t\t추가할 메뉴의 이름 입력 : ");
	wscanf(L"%[^\n]ls", menuName);
	
	printf("\n\t\t추가할 메뉴의 가격 입력 : ");
	wscanf(L"%d", &price);

	insertCoffeeMenu(id, menuName, price);
	return 1;
}

int deleteCoffeeMenu() {
	int id, result;

	system("cls");
	printf("\n\t\t\t\t=== (7) 커피 메뉴 삭제 ===\n");
	showCoffeeMenu();

	printf("\n\n\t\t삭제할 메뉴 번호 입력(메인 메뉴로 돌아가려면 0):");
	scanf("%d", &id);
	if (id == 0)
		return 0;

	result = deleteMenuList(id);

	system("cls");
	printf("\n\t\t\t\t=== (7) 메뉴 삭제 ===\n");
	showCoffeeMenu();

	if (result == 1)
		printf("\n\n\t\t%d번 메뉴가 삭제되었습니다.", id);
	waitZeroInput();

	return 1;
}

int deleteMenuList(int id) {
	menuItem* tmp = menuItemList;

	if (tmp->id == id) {
		menuItemList = tmp->next;
	}
	else {
		while (tmp->next != NULL && tmp->next->id != id) {
			tmp = tmp->next;
		}

		if (tmp->next == NULL) {
			printf("\n\n\t\t\t입력된 번호의 메뉴가 없습니다!");
			Sleep(1000);
			return 0;
		}
		else {
			tmp->next = tmp->next->next;

			return 1;
		}
	}
}