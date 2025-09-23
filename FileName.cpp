#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 100

// 상품 구조체 정의
typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
} Product;

Product products[MAX_PRODUCTS];
int productCount = 0;  // 상품 개수
int soldProducts[MAX_PRODUCTS];  // 판매된 상품 수량

// 상품 추가
void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("상품을 더 이상 추가할 수 없습니다.\n");
        return;
    }

    Product newProduct;
    printf("상품 ID: ");
    scanf("%d", &newProduct.id);
    printf("상품명: ");
    scanf("%s", newProduct.name);
    printf("가격: ");
    scanf("%f", &newProduct.price);
    printf("수량: ");
    scanf("%d", &newProduct.quantity);

    products[productCount] = newProduct;
    soldProducts[productCount] = 0; // 초기 판매 수량 0
    productCount++;

    printf("상품이 추가되었습니다.\n");
}

// 상품 판매
void sellProduct() {
    int id, quantity;
    printf("판매할 상품 ID: ");
    scanf("%d", &id);
    printf("판매할 수량: ");
    scanf("%d", &quantity);

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            if (products[i].quantity >= quantity) {
                products[i].quantity -= quantity;  // 재고 차감
                soldProducts[i] += quantity;      // 판매량 기록
                printf("상품 '%s'가 %d개 판매되었습니다.\n", products[i].name, quantity);
                return;
            }
            else {
                printf("재고가 부족합니다.\n");
                return;
            }
        }
    }
    printf("해당 ID의 상품을 찾을 수 없습니다.\n");
}

// 상품명으로 검색하여 상품 정보 출력
void searchByProductName() {
    char searchName[50];
    printf("검색할 상품명: ");
    scanf("%s", searchName);

    int found = 0;
    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].name, searchName) == 0) {
            printf("상품 ID: %d, 상품명: %s, 가격: %.2f, 재고: %d, 판매된 수량: %d\n",
                products[i].id, products[i].name, products[i].price, products[i].quantity, soldProducts[i]);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("상품명을 찾을 수 없습니다.\n");
    }
}

// 상품 현황
void viewProductStatus() {
    if (productCount == 0) {
        printf("등록된 상품이 없습니다.\n");
        return;
    }

    printf("상품 현황:\n");
    for (int i = 0; i < productCount; i++) {
        printf("ID: %d, 상품명: %s, 가격: %.2f, 재고: %d, 판매된 수량: %d\n",
            products[i].id, products[i].name, products[i].price, products[i].quantity, soldProducts[i]);
    }
}

// 메뉴 표시 및 선택
void menu() {
    int choice;
    while (1) {
        printf("\n--- 쇼핑몰 재고 관리 시스템 ---\n");
        printf("1. 상품 추가\n");
        printf("2. 상품 판매\n");
        printf("3. 상품 현황\n");
        printf("4. 상품명 입력 (검색)\n");
        printf("5. 종료\n");
        printf("선택: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addProduct();
            break;
        case 2:
            sellProduct();
            break;
        case 3:
            viewProductStatus();
            break;
        case 4:
            searchByProductName();  // 상품명 검색 기능 호출
            break;
        case 5:
            printf("시스템을 종료합니다.\n");
            return;
        default:
            printf("잘못된 입력입니다. 다시 선택하세요.\n");
        }
    }
}

int main() {
    menu();  // 메뉴 실행
    return 0;
}
