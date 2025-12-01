#include <stdio.h>
#include <string.h>

struct MenuItem {
    char name[50];
    int price;
};
struct MenuItem menuItems[] = {
    {"Pizza", 199},
    {"Burger", 99},
    {"Biryani", 249},
    {"Coke", 39}
};
int menuSize = 4;
struct CartItem {
    char name[50];
    int price;
    int quantity;
};
struct CartItem cart[20];
int cartCount = 0;

int findItem(char item[]) {
    for (int i = 0; i < cartCount; i++) {
        if (strcmp(cart[i].name, item) == 0) {
            return i;
        }
    }
    return -1;
}
void addItemToCart(int itemIndex, int qty) {
    if (qty <= 0) {
        printf("\nEnter a valid quantity!\n");
        return;
    }

    int index = findItem(menuItems[itemIndex].name);

    if (index != -1) {
        cart[index].quantity += qty;
    } else {
        strcpy(cart[cartCount].name, menuItems[itemIndex].name);
        cart[cartCount].price = menuItems[itemIndex].price;
        cart[cartCount].quantity = qty;
        cartCount++;
    }

    printf("\nItem added to cart!\n");
}
void viewCart() {
    if (cartCount == 0) {
        printf("\nCart is empty!\n");
        return;
    }
    printf("\n========== YOUR CART ==========\n");
    int totalPrice = 0;
    for (int i = 0; i < cartCount; i++) {
        int itemPrice = cart[i].price * cart[i].quantity;
        printf("%d. %s x%d = Rs.%d\n",
               i + 1,
               cart[i].name,
               cart[i].quantity,
               itemPrice);
        totalPrice += itemPrice;
    }
    printf("================================\n");
    printf("Subtotal: Rs.%d\n\n", totalPrice);
}
void cancelItem() {
    viewCart();
    if (cartCount == 0) return;

    int num;
    printf("\nEnter item number to remove: ");
    scanf("%d", &num);

    if (num < 1 || num > cartCount) {
        printf("Invalid number!\n");
        return;
    }

    for (int i = num - 1; i < cartCount - 1; i++) {
        cart[i] = cart[i + 1];
    }
    cartCount--;

    printf("Item removed successfully!\n");
}
void checkout() {
    if (cartCount == 0) {
        printf("\nCart is empty! Add items first.\n");
        return;
    }
    float total = 0;
    printf("\n========== BILL ==========\n");
    for (int i = 0; i < cartCount; i++) {
        int itemTotal = cart[i].price * cart[i].quantity;
        printf("%s x%d = Rs.%d\n", cart[i].name, cart[i].quantity, itemTotal);
        total += itemTotal;
    }
    float handling = 20;
    float delivery = 80;
    float gst = total * 0.05;
    float grandTotal = total + handling + delivery + gst;
    printf("\nItems Total       : Rs.%.2f\n", total);
    printf("Handling Charges  : Rs.%.2f\n", handling);
    printf("Delivery Charges  : Rs.%.2f\n", delivery);
    printf("GST (5%%)          : Rs.%.2f\n", gst);
    printf("===========================\n");
    printf("Grand Total       : Rs.%.2f\n", grandTotal);
    int c;
    printf("\n1. Order Now\n");
    printf("2. Exit to Menu\n");
    printf("Enter your choice: ");
    scanf("%d", &c);
    if (c == 1) {
        printf("\nOrder successfully completed!\n");
        FILE *fp = fopen("userdata.txt", "a");
        if (fp != NULL) {
            fprintf(fp, "\n----- ORDER DETAILS -----\n");
            fprintf(fp, "Total Amount: Rs.%.2f\n", grandTotal);
            for (int i = 0; i < cartCount; i++) {
                fprintf(fp, "%s x%d\n", cart[i].name, cart[i].quantity);
            }
            fprintf(fp, "------------------------\n");
            fclose(fp);
        }
        cartCount = 0;
    } else {
        printf("\nReturning to menu...\n");
    }
}
void menu() {
    int choice, qty;
    while (1) {
        printf("\n========== MENU ==========\n");
        for (int i = 0; i < menuSize; i++) {
            printf("%d. %s - Rs.%d\n", i + 1, menuItems[i].name, menuItems[i].price);
        }
        printf("5. View Cart\n");
        printf("6. Remove Item\n");
        printf("7. Checkout\n");
        printf("8. Exit\n");
        printf("==========================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice >= 1 && choice <= menuSize) {
            printf("Enter quantity: ");
            scanf("%d", &qty);
            addItemToCart(choice - 1, qty);
        } else if (choice == 5) {
            viewCart();
        } else if (choice == 6) {
            cancelItem();
        } else if (choice == 7) {
            checkout();
        } else if (choice == 8) {
            printf("\nThank you! Goodbye!\n");
            return;
        } else {
            printf("Invalid choice!\n");
        }
    }
}

int main() {
    char regPhone[20], regEmail[50], regUser[50], regPass[50], regAddress[100];
    char loginEmail[50], loginPass[50];
    FILE *fp;
    printf("\n===== HUNGER HUB - FOOD ORDERING SYSTEM =====\n");
    
    printf("\n----- REGISTRATION -----\n");
    printf("Enter Phone Number: ");
    scanf("%s", regPhone);
    printf("Enter Email: ");
    scanf("%s", regEmail);
    printf("Enter Username: ");
    scanf("%s", regUser);
    printf("Enter Password: ");
    scanf("%s", regPass);
    printf("Enter Address: ");
    scanf(" %[^\n]", regAddress);
    printf("\nRegistration Successful!\n");
    
    printf("\n----- LOGIN -----\n");
    printf("Enter Email: ");
    scanf("%s", loginEmail);
    printf("Enter Password: ");
    scanf("%s", loginPass);
    if (strcmp(loginEmail, regEmail) == 0 && strcmp(loginPass, regPass) == 0) {
        printf("\nLogin Successful!\n");
      
        fp = fopen("userdata.txt", "a");
        if (fp == NULL) {
            printf("Error saving user info!\n");
        } else {
            fprintf(fp, "-----------------------------\n");
            fprintf(fp, "Username: %s\nPhone: %s\nAddress: %s\nEmail: %s\n",
                    regUser, regPhone, regAddress, regEmail);
            fprintf(fp, "-----------------------------\n\n");
            fclose(fp);
            printf("User info saved successfully!\n");
        }
        printf("\nWelcome, %s!\n", regUser);
        menu();
    } else {
        printf("\nLogin Failed! Invalid Email or Password.\n");
    }
    return 0;
}

