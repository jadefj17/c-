#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 100

// ��ǰ ����ü ����
typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
} Product;

Product products[MAX_PRODUCTS];
int productCount = 0;  // ��ǰ ����
int soldProducts[MAX_PRODUCTS];  // �Ǹŵ� ��ǰ ����

// ��ǰ �߰�
void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("��ǰ�� �� �̻� �߰��� �� �����ϴ�.\n");
        return;
    }

    Product newProduct;
    printf("��ǰ ID: ");
    scanf("%d", &newProduct.id);
    printf("��ǰ��: ");
    scanf("%s", newProduct.name);
    printf("����: ");
    scanf("%f", &newProduct.price);
    printf("����: ");
    scanf("%d", &newProduct.quantity);

    products[productCount] = newProduct;
    soldProducts[productCount] = 0; // �ʱ� �Ǹ� ���� 0
    productCount++;

    printf("��ǰ�� �߰��Ǿ����ϴ�.\n");
}

// ��ǰ �Ǹ�
void sellProduct() {
    int id, quantity;
    printf("�Ǹ��� ��ǰ ID: ");
    scanf("%d", &id);
    printf("�Ǹ��� ����: ");
    scanf("%d", &quantity);

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            if (products[i].quantity >= quantity) {
                products[i].quantity -= quantity;  // ��� ����
                soldProducts[i] += quantity;      // �Ǹŷ� ���
                printf("��ǰ '%s'�� %d�� �ǸŵǾ����ϴ�.\n", products[i].name, quantity);
                return;
            }
            else {
                printf("��� �����մϴ�.\n");
                return;
            }
        }
    }
    printf("�ش� ID�� ��ǰ�� ã�� �� �����ϴ�.\n");
}

// ��ǰ������ �˻��Ͽ� ��ǰ ���� ���
void searchByProductName() {
    char searchName[50];
    printf("�˻��� ��ǰ��: ");
    scanf("%s", searchName);

    int found = 0;
    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].name, searchName) == 0) {
            printf("��ǰ ID: %d, ��ǰ��: %s, ����: %.2f, ���: %d, �Ǹŵ� ����: %d\n",
                products[i].id, products[i].name, products[i].price, products[i].quantity, soldProducts[i]);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("��ǰ���� ã�� �� �����ϴ�.\n");
    }
}

// ��ǰ ��Ȳ
void viewProductStatus() {
    if (productCount == 0) {
        printf("��ϵ� ��ǰ�� �����ϴ�.\n");
        return;
    }

    printf("��ǰ ��Ȳ:\n");
    for (int i = 0; i < productCount; i++) {
        printf("ID: %d, ��ǰ��: %s, ����: %.2f, ���: %d, �Ǹŵ� ����: %d\n",
            products[i].id, products[i].name, products[i].price, products[i].quantity, soldProducts[i]);
    }
}

// �޴� ǥ�� �� ����
void menu() {
    int choice;
    while (1) {
        printf("\n--- ���θ� ��� ���� �ý��� ---\n");
        printf("1. ��ǰ �߰�\n");
        printf("2. ��ǰ �Ǹ�\n");
        printf("3. ��ǰ ��Ȳ\n");
        printf("4. ��ǰ�� �Է� (�˻�)\n");
        printf("5. ����\n");
        printf("����: ");
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
            searchByProductName();  // ��ǰ�� �˻� ��� ȣ��
            break;
        case 5:
            printf("�ý����� �����մϴ�.\n");
            return;
        default:
            printf("�߸��� �Է��Դϴ�. �ٽ� �����ϼ���.\n");
        }
    }
}

int main() {
    menu();  // �޴� ����
    return 0;
}
