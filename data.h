// 커피 메뉴를 저장하는 구조체
typedef struct menuItem {
	int id;				// 메뉴 번호
	wchar_t menuName[30];	// 메뉴 이름
	int price;			// 단가
	struct menuItem* next;
}menuItem;

// 주문 정보를 저장하는 구조체
typedef struct orderNode {
	int orderId;			// 주문 번호
	int menuId;				// 메뉴 번호
	wchar_t menuName[30];		// 메뉴 이름
	int price;				// 단가
	int sales;				// 판매량
	struct orderNode* next;
}orderNode;

// 매출 정보를 저장하는 구조체(커피 메뉴별로 저장)
typedef struct saleNode {
	int menuId;				// 메뉴 번호
	wchar_t menuName[30];		// 메뉴 이름
	int price;				// 단가
	int sales;				// 판매량
	struct saleNode* next;
}saleNode;

typedef struct userNode {
	int userId;
	wchar_t email[100];
	wchar_t password[65];
	wchar_t phoneNumber[28]; // 전화번호 11자리 + 하이픈 2자리 + 널문자 1개
	wchar_t address[60];
	struct userNode* next;
}userNode;