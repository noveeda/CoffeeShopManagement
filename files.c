#include "main.h"

void saveMenuFile() {
	FILE* fp;
	menuItem* tmp = menuItemList;

	fp = _wfopen(L"menu.txt", L"wt, ccs=UTF-8");

	if (fp == NULL) {
		printf("Error(saveMenuFile): menu.txt 파일 오픈 에러!");
		return;
	}

	while (tmp != NULL) {
		//fprintf(fp, "%d,%s,%d\n", tmp->id, tmp->menuName, tmp->price);
		fwprintf(fp, L"%d,%ls,%d\n", tmp->id, tmp->menuName, tmp->price);
		tmp = tmp->next;
	}

	fclose(fp);	// 파일 포인터 해제
	printf("\n\t\t메뉴가 파일에 저장되었습니다.");
	Sleep(2000);
}

void loadTodaySales() {
	FILE* fp;
	wchar_t date[40] = WIDEN(__DATE__);
	wcscat(date, L".csv");
	fp = _wfopen(date, L"r, ccs=UTF-8");

	if (fp == NULL) {
		printf("\n\t\t저장된 오늘의 매출자료는 없습니다.\n");
		waitZeroInput();
		return;
	}

	wchar_t line[80];
	int menuId, price, sales, total;
	wchar_t menuName[30];
	int savedCount = 0;
	int savedTotal = 0;

	while (fgetws(line, sizeof(line) / sizeof(wchar_t), fp) != NULL) {
		swscanf(line, L"%d,%[^,],%d,%d,%d",
			&menuId, menuName, &price, &sales, &total);
		savedCount++;
		savedTotal += total;
		addOrder(menuId, sales);

	}
	printf("\n\t\t파일에 저장된 %d건, 총 %d원의 매출 자료를 읽어왔습니다.",
		savedCount, savedTotal);
	waitZeroInput();
}

void backup() {
	saleNode* saleToday = NULL;	// saleNode는 메뉴별로 매출액을 저장
	saleNode* p;
	wchar_t date[40] = WIDEN(__DATE__);
	orderNode* ptr;
	int totalSaleToday = 0;

	wcscat(date, L".csv");
	FILE* fp;
	fp = _wfopen(date, L"w, ccs=UTF-8");
	if (fp == NULL) {
		printf("파일 오픈 에러\n");
		return;
	}

	for (ptr = orderList; ptr; ptr = ptr->next) {
		saleToday = addSales(saleToday, ptr);
	}

	for (p = saleToday; p; p = p->next) {
		fwprintf(fp, L"%d,%ls,%d,%d,%d\n", 
			p->menuId, 
			p->menuName, 
			p->price, 
			p->sales, 
			p->price * p->sales);
		totalSaleToday += p->price * p->sales;
	}

	fclose(fp);
	wprintf("\n\n\t\t\t%ls : 총매출 = %d", date, totalSaleToday);
	wprintf("\n\n\t\t\tBackup Successful...");
	waitZeroInput();
}

void backupUserList() {
	userNode* ptr;

	FILE* fp;

	// 열고
	fp = _wfopen(L"users.csv", L"w, ccs=UTF-8");
	if (fp == NULL) {
		printf("Error(backupUserList): 파일 오픈 에러\n");
		return;
	}

	// 수정하고
	for (ptr = userList; ptr; ptr = ptr->next) {
		//%[^\n]는 read용 포맷이라 write에선 의미가 없다(
		/*fwprintf(fp, L"%d,%ls,%ls,%ls,%[^\n]",*/
		fwprintf(fp, L"%d,%ls,%ls,%ls,%ls\n",
			ptr->userId,
			ptr->email,
			ptr->password,
			ptr->phoneNumber,
			ptr->address);
	}

	// 닫는다
	fclose(fp);
	wprintf("\n\n\t\t\tuser 테이블 백업이 성공적으로 수행됐습니다");
}

saleNode* addSales(saleNode* saleToday, orderNode* p) {
	saleNode* ptr, * tmp;

	// csv 파일에 이미 저장된 메뉴면 더한다.
	for (ptr = saleToday; ptr; ptr = ptr->next) {
		if (ptr->menuId == p->menuId) {
			ptr->sales += p->sales;
			return saleToday;
		}
	}

	// 파일에 없는 메뉴면 saleNode 생성
	tmp = (saleNode*)malloc(sizeof(saleNode));
	tmp->menuId = p->menuId;
	wcscpy(tmp->menuName, p->menuName);
	tmp->price = p->price;
	tmp->sales = p->sales;
	tmp->next = NULL;

	if (saleToday == NULL) {
		saleToday = tmp;
	}
	else {
		for (ptr = saleToday; ptr->next; ptr = ptr->next);

		ptr->next = tmp;
	}

	return saleToday;
}