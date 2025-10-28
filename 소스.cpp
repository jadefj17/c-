#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 5
#define FILE_NAME "��ǰ����.txt"

typedef struct {
    int id;             // ��ǰ ID
    char name[50];      // ��ǰ��
    int price;          // ��ǰ ����
    int stock;          // �԰� ����
    int sold;           // �Ǹ� ����
    int totalSales;     // �� �Ǹ� �ݾ�
} Product;

Product products[MAX_PRODUCTS];
int productCount = 0;

// ���� ����
void saveToFile() {
    FILE* fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("���� ���� ����!\n");
        return;
    }

    for (int i = 0; i < productCount; i++) {
        fprintf(fp, "%d %s %d %d %d %d\n",
            products[i].id, products[i].name, products[i].price,
            products[i].stock, products[i].sold, products[i].totalSales);
    }

    fclose(fp);
    printf("��ǰ ������ ���Ͽ� ����Ǿ����ϴ�.\n");
}

// ���� �ҷ�����
void loadFromFile() {
    FILE* fp = fopen(FILE_NAME, "r");
    if (fp == NULL) return; // ���� ������ ����

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
    printf("��ǰ ������ ���Ͽ��� �ҷ��Խ��ϴ�.\n");
}

// ��ǰ �˻�
int findProductByID(int id) {
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id)
            return i;
    }
    return -1;
}

// 1. �԰� �޴�
void addOrUpdateProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("��ǰ ���� �ѵ�(5��)�� �ʰ��߽��ϴ�!\n");
        return;
    }

    int id;
    printf("��ǰID �Է�: ");
    scanf("%d", &id);

    int index = findProductByID(id);
    if (index != -1) {
        printf("���� ��ǰ�Դϴ�. �԰� ���� �߰�.\n");
        int addQty;
        printf("�߰� �԰� ����: ");
        scanf("%d", &addQty);
        products[index].stock += addQty;
    }
    else {
        Product p;
        p.id = id;
        printf("��ǰ�� �Է�: ");
        scanf("%s", p.name);
        printf("��ǰ���� �Է�: ");
        scanf("%d", &p.price);
        printf("�԰� ���� �Է�: ");
        scanf("%d", &p.stock);
        p.sold = 0;
        p.totalSales = 0;
        products[productCount++] = p;
    }

    printf("�԰� ó���� �Ϸ�Ǿ����ϴ�.\n");
}

// 2. �Ǹ� �޴�
void sellProduct() {
    int id;
    printf("�Ǹ��� ��ǰID �Է�: ");
    scanf("%d", &id);

    int index = findProductByID(id);
    if (index == -1) {
        printf("�������� �ʴ� ��ǰ�Դϴ�.\n");
        return;
    }

    int qty;
    printf("�Ǹ� ���� �Է�: ");
    scanf("%d", &qty);

    if (qty > products[index].stock) {
        printf("��� �����մϴ�!\n");
        return;
    }

    products[index].stock -= qty;
    products[index].sold += qty;
    products[index].totalSales += qty * products[index].price;

    printf("�Ǹ� �Ϸ�! �� �Ǹ� �ݾ�: %d��\n", products[index].totalSales);
}

// 3. ���� ��ǰ ��ȸ
void viewProduct() {
    int id;
    printf("��ȸ�� ��ǰID �Է�: ");
    scanf("%d", &id);

    int index = findProductByID(id);
    if (index == -1) {
        printf("�ش� ��ǰ�� �������� �ʽ��ϴ�.\n");
        return;
    }

    Product p = products[index];
    printf("\n[��ǰ ����]\n");
    printf("ID: %d\n", p.id);
    printf("��ǰ��: %s\n", p.name);
    printf("����: %d\n", p.price);
    printf("���: %d\n", p.stock);
    printf("�Ǹŷ�: %d\n", p.sold);
    printf("�� �Ǹűݾ�: %d\n\n", p.totalSales);
}

// 4. ��ü ��ǰ ��Ȳ
void viewAllProducts() {
    printf("\n===== ��ü ��ǰ ��Ȳ =====\n");
    for (int i = 0; i < productCount; i++) {
        Product p = products[i];
        printf("[%d] %s | ����:%d | ���:%d | �Ǹ�:%d | ���Ǹű�:%d\n",
            p.id, p.name, p.price, p.stock, p.sold, p.totalSales);
    }
    printf("=========================\n");
}

int main() {
    int menu;
    loadFromFile();

    while (1) {
        printf("\n[���θ� ��� ���� �ý���]\n");
        printf("1. �԰�\n2. �Ǹ�\n3. ������Ȳ\n4. ��ü��Ȳ\n5. ����\n");
        printf("�޴� ����: ");
        scanf("%d", &menu);

        switch (menu) {
        case 1: addOrUpdateProduct(); break;
        case 2: sellProduct(); break;
        case 3: viewProduct(); break;
        case 4: viewAllProducts(); break;
        case 5:
            saveToFile();
            printf("���α׷��� �����մϴ�.\n");
            return 0;
        default:
            printf("�߸��� �����Դϴ�.\n");
        }
    }
}
