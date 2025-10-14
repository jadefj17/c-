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
        printf("�޴��� �����ϼ���: ");
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
            printf("���α׷��� �����մϴ�.\n");
            return 0;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
        }
    }

    return 0;
}

void displayMenu() {
    printf("\n===== ���θ� ���� �ý��� =====\n");
    printf("1. ��ǰ ���\n");
    printf("2. ��ǰ ��� ����\n");
    printf("3. �Ǹ� ó��\n");
    printf("4. ����\n");
}

void addProduct(Product products[], int* count) {
    if (*count >= MAX_PRODUCTS) {
        printf("�� �̻� ��ǰ�� �߰��� �� �����ϴ�.\n");
        return;
    }

    Product newProduct;
    newProduct.id = *count + 1;

    printf("��ǰ �̸�: ");
    getchar();  
    fgets(newProduct.name, sizeof(newProduct.name), stdin);
    newProduct.name[strcspn(newProduct.name, "\n")] = 0;  

    printf("��ǰ ����: ");
    scanf("%d", &newProduct.price);

    printf("��ǰ ��� ����: ");
    scanf("%d", &newProduct.stock);

    products[*count] = newProduct;
    (*count)++;
    printf("��ǰ�� ��ϵǾ����ϴ�.\n");
}

void listProducts(Product products[], int count) {
    if (count == 0) {
        printf("��ϵ� ��ǰ�� �����ϴ�.\n");
        return;
    }

    printf("\n===== ��ǰ ��� =====\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d, �̸�: %s, ����: %d, ���: %d\n",
            products[i].id, products[i].name,
            products[i].price, products[i].stock);
    }
}

void sellProduct(Product products[], int count) {
    int productId, quantity;

    if (count == 0) {
        printf("�Ǹ��� ��ǰ�� �����ϴ�.\n");
        return;
    }

    printf("�Ǹ��� ��ǰ ID�� �Է��ϼ���: ");
    scanf("%d", &productId);

    if (productId < 1 || productId > count) {
        printf("�߸��� ��ǰ ID�Դϴ�. �ٽ� �õ��ϼ���.\n");
        return;
    }

    printf("�Ǹ� ������ �Է��ϼ���: ");
    scanf("%d", &quantity);

    if (quantity > products[productId - 1].stock) {
        printf("��� �����մϴ�. ���� ���: %d\n", products[productId - 1].stock);
        return;
    }

    products[productId - 1].stock -= quantity;
    printf("%d�� ��ǰ�� �ǸŵǾ����ϴ�. ���� ���: %d\n", quantity, products[productId - 1].stock);
}
