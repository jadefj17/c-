#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 5
#define FILE_NAME "상품정보.txt"

typedef struct {
    int id;            
    char name[50];      
    int price;         
    int stock;          
    int sold;           
    int totalSales;     
} Product;

Product products[MAX_PRODUCTS];
int productCount = 0;

void saveToFile() {
    FILE* fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("파일 저장 실패!\n");
        return;
    }

    for (int i = 0; i < productCount; i++) {
        fprintf(fp, "%d %s %d %d %d %d\n",
            products[i].id, products[i].name, products[i].price,
            products[i].stock, products[i].sold, products[i].totalSales);
    }

    fclose(fp);
    printf("상품 정보가 파일에 저장되었습니다.\n");
}

void loadFromFile() {
    FILE* fp = fopen(FILE_NAME, "r");
    if (fp == NULL) return; 

    while (fscanf(fp, "%d %s %d %d %d %d",
        &products[productCount].id,
        products[productCount].name,
        &products[productCount].price,
        &products[productCount].stock,
        &products[productCount].sold,
        &products[productCount].totalSales) != EOF) {
        productCount++;
    }

    fclose(fp);
    printf("상품 정보를 파일에서 불러왔습니다.\n");
}

int findProductByID(int id) {
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id)
            return i;
    }
    return -1;
}

// 1. 입고 메뉴
void addOrUpdateProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("상품 개수 한도(5개)를 초과했습니다!\n");
        return;
    }

    int id;
    printf("상품ID 입력: ");
    scanf("%d", &id);

    int index = findProductByID(id);
    if (index != -1) {
        printf("기존 상품입니다. 입고 수량 추가.\n");
        int addQty;
        printf("추가 입고 수량: ");
        scanf("%d", &addQty);
        products[index].stock += addQty;
    }
    else {
        Product p;
        p.id = id;
        printf("상품명 입력: ");
        scanf("%s", p.name);
        printf("상품가격 입력: ");
        scanf("%d", &p.price);
        printf("입고 수량 입력: ");
        scanf("%d", &p.stock);
        p.sold = 0;
        p.totalSales = 0;
        products[productCount++] = p;
    }

    printf("입고 처리가 완료되었습니다.\n");
}

void sellProduct() {
    int id;
    printf("판매할 상품ID 입력: ");
    scanf("%d", &id);

    int index = findProductByID(id);
    if (index == -1) {
        printf("존재하지 않는 상품입니다.\n");
        return;
    }

    int qty;
    printf("판매 수량 입력: ");
    scanf("%d", &qty);

    if (qty > products[index].stock) {
        printf("재고가 부족합니다!\n");
        return;
    }

    products[index].stock -= qty;
    products[index].sold += qty;
    products[index].totalSales += qty * products[index].price;

    printf("판매 완료! 총 판매 금액: %d원\n", products[index].totalSales);
}

void viewProduct() {
    int id;
    printf("조회할 상품ID 입력: ");
    scanf("%d", &id);

    int index = findProductByID(id);
    if (index == -1) {
        printf("해당 상품이 존재하지 않습니다.\n");
        return;
    }

    Product p = products[index];
    printf("\n[상품 정보]\n");
    printf("ID: %d\n", p.id);
    printf("상품명: %s\n", p.name);
    printf("가격: %d\n", p.price);
    printf("재고: %d\n", p.stock);
    printf("판매량: %d\n", p.sold);
    printf("총 판매금액: %d\n\n", p.totalSales);
}

void viewAllProducts() {
    printf("\n===== 전체 상품 현황 =====\n");
    for (int i = 0; i < productCount; i++) {
        Product p = products[i];
        printf("[%d] %s | 가격:%d | 재고:%d | 판매:%d | 총판매금:%d\n",
            p.id, p.name, p.price, p.stock, p.sold, p.totalSales);
    }
    printf("=========================\n");
}

int main() {
    int menu;
    loadFromFile();

    while (1) {
        printf("\n[쇼핑몰 재고 관리 시스템]\n");
        printf("1. 입고\n2. 판매\n3. 개별현황\n4. 전체현황\n5. 종료\n");
        printf("메뉴 선택: ");
        scanf("%d", &menu);

        switch (menu) {
        case 1: addOrUpdateProduct(); break;
        case 2: sellProduct(); break;
        case 3: viewProduct(); break;
        case 4: viewAllProducts(); break;
        case 5:
            saveToFile();
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 선택입니다.\n");
        }
    }
}
