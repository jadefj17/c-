#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 5  

typedef struct {
    int id;         
    char name[50];  
    int price;     
    int stock;      
} Product;

void addProduct(Product products[], int* count);
void listProducts(Product products[], int count);
void sellProduct(Product products[], int count);
void displayMenu();

int main() {
    Product products[MAX_PRODUCTS];
    int productCount = 0;
    int choice;

    while (1) {
        displayMenu();
        printf("메뉴를 선택하세요: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addProduct(products, &productCount);
            break;
        case 2:
            listProducts(products, productCount);
            break;
        case 3:
            sellProduct(products, productCount);
            break;
        case 4:
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }
    }

    return 0;
}

void displayMenu() {
    printf("\n===== 쇼핑몰 관리 시스템 =====\n");
    printf("1. 상품 등록\n");
    printf("2. 상품 목록 보기\n");
    printf("3. 판매 처리\n");
    printf("4. 종료\n");
}

void addProduct(Product products[], int* count) {
    if (*count >= MAX_PRODUCTS) {
        printf("더 이상 상품을 추가할 수 없습니다.\n");
        return;
    }

    Product newProduct;
    newProduct.id = *count + 1;

    printf("상품 이름: ");
    getchar();  
    fgets(newProduct.name, sizeof(newProduct.name), stdin);
    newProduct.name[strcspn(newProduct.name, "\n")] = 0;  

    printf("상품 가격: ");
    scanf("%d", &newProduct.price);

    printf("상품 재고 수량: ");
    scanf("%d", &newProduct.stock);

    products[*count] = newProduct;
    (*count)++;
    printf("상품이 등록되었습니다.\n");
}

void listProducts(Product products[], int count) {
    if (count == 0) {
        printf("등록된 상품이 없습니다.\n");
        return;
    }

    printf("\n===== 상품 목록 =====\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d, 이름: %s, 가격: %d, 재고: %d\n",
            products[i].id, products[i].name,
            products[i].price, products[i].stock);
    }
}

void sellProduct(Product products[], int count) {
    int productId, quantity;

    if (count == 0) {
        printf("판매할 상품이 없습니다.\n");
        return;
    }

    printf("판매할 상품 ID를 입력하세요: ");
    scanf("%d", &productId);

    if (productId < 1 || productId > count) {
        printf("잘못된 상품 ID입니다. 다시 시도하세요.\n");
        return;
    }

    printf("판매 수량을 입력하세요: ");
    scanf("%d", &quantity);

    if (quantity > products[productId - 1].stock) {
        printf("재고가 부족합니다. 현재 재고: %d\n", products[productId - 1].stock);
        return;
    }

    products[productId - 1].stock -= quantity;
    printf("%d개 상품이 판매되었습니다. 남은 재고: %d\n", quantity, products[productId - 1].stock);
}
