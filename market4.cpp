#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_PRODUCTS 100

// 상품 구조체 정의
typedef struct {
    int id;
    char name[50];
    int quantity;
    int price;
} Product;

Product products[MAX_PRODUCTS];
int productCount = 0;

// 입력 유효성 함수
int getValidInt(const char* prompt) {
    char input[100];
    int value;
    while (1) {
        printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("입력이 잘못되었습니다. 다시 입력하세요.\n");
            continue;
        }
        input[strcspn(input, "\n")] = 0;
        if (strlen(input) == 0) {
            printf("입력값이 비어 있습니다. 다시 입력하세요.\n");
            continue;
        }
        int valid = 1;
        for (int i = 0; i < strlen(input); i++) {
            if (!isdigit(input[i])) {
                valid = 0;
                break;
            }
        }
        if (!valid) {
            printf("숫자만 입력 가능합니다. 다시 입력하세요.\n");
            continue;
        }
        value = atoi(input);
        return value;
    }
}

// 상품 등록 및 입고
void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("상품 갯수 초과! 더 이상 추가할 수 없습니다.\n");
        return;
    }

    int id = getValidInt("상품ID : ");
    int found = -1;

    // 상품이 이미 있는지 확인
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        // 상품이 있으면 입고량만 추가
        int qty = getValidInt("입고량 : ");
        products[found].quantity += qty;
        printf("기존 상품이 업데이트되었습니다.\n");
    }
    else {
        // 새로운 상품 등록
        Product newProduct;
        newProduct.id = id;
        printf("상품명 : ");
        scanf("%s", newProduct.name);
        getchar(); // 버퍼 정리
        newProduct.quantity = getValidInt("입고량 : ");
        newProduct.price = getValidInt("판매가격 : ");
        products[productCount++] = newProduct;
        printf("상품이 추가되었습니다.\n");
    }
}

// 판매
void sellProduct() {
    int id = getValidInt("상품ID : ");
    int found = -1;

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("해당 상품을 찾을 수 없습니다.\n");
        return;
    }

    int qty = getValidInt("판매량 : ");
    if (products[found].quantity >= qty) {
        products[found].quantity -= qty;
        printf("상품 '%s'가 %d개 판매되었습니다.\n", products[found].name, qty);
    }
    else {
        printf("재고가 부족합니다.\n");
    }
}

// 개별 현황
void viewSingleProduct() {
    int id = getValidInt("상품ID 입력 : ");
    int found = -1;

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("해당 상품을 찾을 수 없습니다.\n");
        return;
    }

    printf("상품명: %s\n", products[found].name);
    printf("가격: %d\n", products[found].price);
    printf("재고: %d\n", products[found].quantity);
}

// 전체 현황
void viewAllProducts() {
    if (productCount == 0) {
        printf("등록된 상품이 없습니다.\n");
        return;
    }

    printf("\n[전체 상품 현황]\n");
    for (int i = 0; i < productCount; i++) {
        printf("ID: %d | 상품명: %s | 가격: %d | 재고: %d\n",
            products[i].id, products[i].name, products[i].price, products[i].quantity);
    }
}

// 메뉴
void menu() {
    int choice;
    while (1) {
        printf("\n원하는 메뉴를 선택하세요. (1. 입고, 2. 판매, 3. 개별현황, 4. 전체현황, 5. 종료)\n");
        choice = getValidInt("선택: ");
        switch (choice) {
        case 1:
            printf("<< 입고메뉴실행 >>\n");
            addProduct();
            break;
        case 2:
            printf("<< 판매메뉴실행 >>\n");
            sellProduct();
            break;
        case 3:
            printf("<< 개별현황 실행 >>\n");
            viewSingleProduct();
            break;
        case 4:
            printf("<< 전체현황 실행 >>\n");
            viewAllProducts();
            break;
        case 5:
            printf("프로그램을 종료합니다.\n");
            return;
        default:
            printf("잘못된 선택입니다. 다시 입력하세요.\n");
        }
    }
}

// main 함수
int main() {
    menu();
    return 0;
}
