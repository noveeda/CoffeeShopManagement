#include "main.h"

orderNode* orderList = NULL;
static int orderNo = 0; // order.c내에서만 접근 가능한 전역 정적 변수

// menuItemList에서 menuId에 해당하는 메뉴를 가져옴
wchar_t* getMenuName(int menuId) {
	menuItem* ptr;

	for (ptr = menuItemList; ptr; ptr = ptr->next) {
		if (ptr->id == menuId) {
			return ptr->menuName;
		}
	}
	printf("해당 메뉴가 없습니다!");
	return NULL;
}

bool isInMenu(int menuId) {
	menuItem* ptr;

	for (ptr = menuItemList; ptr; ptr = ptr->next) {
		if (ptr->id == menuId) {
			return true;
		}
	}
	return false;
}

orderNode* insertOrderList(int menuId, int quantity, int price) {
	// New Order Instantiate
	orderNode* tmp = (orderNode*)malloc(sizeof(orderNode));
	orderNode* ptr;

	tmp->orderId = ++orderNo;
	tmp->menuId = menuId;
	tmp->price = price;
	tmp->sales = quantity;
	wcscpy(tmp->menuName, getMenuName(menuId));
	tmp->next = NULL;

	if (orderList == NULL) {
		orderList = tmp;
	}
	else {
		// NULL 전(마지막 요소)까지 이동
		for (ptr = orderList; ptr->next; ptr = ptr->next) {}
		
		// 마지막 요소 뒤에 이어붙임
		ptr->next = tmp;
	}

	return orderList;
}

int getPrice(int menuId) {
	menuItem* ptr;

	for (ptr = menuItemList; ptr; ptr = ptr->next) {
		if (ptr->id == menuId)
			return ptr->price;
	}
	printf("해당 메뉴가 없습니다!");
	return 0;
}

int addOrder(int menuId, int quantity) {
	int price = getPrice(menuId);

	orderList = insertOrderList(menuId, quantity, price);
	return quantity * price;
}

orderNode* addThisOrder(orderNode* thisOrder, int menuId, int quantity, int price) {
	orderNode* tmp = NULL, * ptr;

	tmp = (orderNode*)malloc(sizeof(orderNode));
	tmp->menuId = menuId;
	wcscpy(tmp->menuName, getMenuName(menuId));
	tmp->sales = quantity;
	tmp->price = price;
	tmp->next = NULL;

	if (thisOrder == NULL)
		return tmp;
	else {
		for (ptr = thisOrder; ptr->next; ptr = ptr->next) {}
		ptr->next = tmp;

		return thisOrder;
	}
}

void printOrder(orderNode* thisOrder) {
	orderNode* tmp = NULL;

	int totalPrice = 0;

	if (thisOrder != NULL) {
		printf("\n\n\t\t\t\t=== 주문 목록 ===\n");
		printf("\n\t\t");
		printf("-----------------------------------------------------------------");
		printf("\n\t\t번호\t\t음료이름\t\t     수량\t   가격");
		printf("\n\t\t");
		printf("-----------------------------------------------------------------");
		for (tmp = thisOrder; tmp; tmp = tmp->next) {
			wprintf(L"\n\t\t%d\t\t%ls\t\t\t%d\t%7d",
				tmp->menuId,
				getMenuName(tmp->menuId),
				tmp->sales,
				tmp->price);
			totalPrice += tmp->price;
		}

		printf("\n\t\t-----------------------------------------------------------------");
		printf("\n\t\t총액\t\t\t\t\t\t\t%7d", totalPrice);
		printf("\n\t\t-----------------------------------------------------------------");
		
	}
}

void order() {
	menuItem* tmp = menuItemList;
	orderNode* thisOrder = NULL;
	int menuId, quantity, price;

	while (true) {
		system("cls");
		printf("\n\t\t\t\t=== (2) 주문 메뉴 ===\n");
		if (user)
			wprintf(L"\t\t사용자 ID: %d\n", user->userId);
		showCoffeeMenu();
		printOrder(thisOrder);

		printf("\n\n\t\t\t 주문할 메뉴를 입력하세요(주문 종료 = 0): ");
		getchar();
		scanf("%d", &menuId);
			
		if (menuId == 0)
			return;

		if (isInMenu(menuId) == false) {
			printf("\n\t\t\t해당 메뉴가 없습니다!");
			Sleep(1000);
			continue;
		}

		printf("\t\t\t 수량을 입력하세요: ");
		getchar();
		scanf("%d", &quantity);
		price = addOrder(menuId, quantity);
		thisOrder = addThisOrder(thisOrder, menuId, quantity, price);
	}
}

void deleteOrder() {
	orderNode* tmp = orderList;
	int id;

	while (true) {
		system("cls");
		printf("\n\n\t\t\t\t=== (3) 주문 취소 ===\n");
		showOrders();

		printf("\n\n\t\t");
		printf("취소할 주문의 번호 입력(메뉴로 돌아가려면 0): ");
		scanf("%d", &id);

		if (id == 0 || orderList == NULL) {
			return;
		}

		orderNode* freeTarget = NULL;
		if (orderList->orderId == id) {
			freeTarget = orderList;
			orderList = orderList->next;
			printf("\n\n\t\t주문 번호 %d이(가) 취소되었습니다.", id);
			Sleep(2000);
		}
		else {
			while (tmp->next) {
				// 메모리 누수 위험 해결
				if (tmp->next->orderId == id) {
					freeTarget = tmp->next;
					printf("\n\n\t\t주문번호 %d이(가) 취소되었습니다.", id);
					tmp->next = tmp->next->next;
					Sleep(2000);
					break;

				}
				tmp = tmp->next;
			}
		}

		free(freeTarget); // 메모리 해제
	}
}

void showOrderList() {
	system("cls");

	printf("\n\n\t\t\t\t=== (4) 주문 목록 ===\n");
	showOrders();
	waitZeroInput();

}

void showOrders() {
	
	orderNode* tmp = (orderNode*)malloc(sizeof(orderNode));
	orderNode* prev = tmp;
	orderNode* curr = orderList;
	prev->next = curr;
	orderNode* freeTarget = NULL;
	int totalPrice = 0;

	printf("\n\t\t");
	printf("---------------------------------------------------------");
	printf("\n\t\t주문번호\t음료이름\t       수량\t   가격");
	printf("\n\t\t");
	printf("---------------------------------------------------------");
	while (curr != NULL) {
		// 이미 주문된 메뉴가 삭제되었을 경우를 위한 예외 처리
		if (isInMenu(curr->menuId) == false) {
			freeTarget = curr;
			curr = curr->next;
			prev->next = curr;
		}
		else {
			wprintf(L"\n\t\t%d\t\t%ls\t\t%3d\t%7d",
				curr->orderId, getMenuName(curr->menuId),
				curr->sales, curr->price * curr->sales);
			totalPrice += curr->price * curr->sales;
			prev = curr;
			curr = curr->next;
		}
	}
	printf("\n\t\t---------------------------------------------------------");
	printf("\n\t\t총액\t\t\t\t\t\t%7d", totalPrice);
	printf("\n\t\t---------------------------------------------------------");

	// 이미 주문된 메뉴가 삭제되었을 경우를 위한 예외 처리
	free(freeTarget);
	free(tmp);
}