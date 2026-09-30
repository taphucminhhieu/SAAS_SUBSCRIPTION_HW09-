#include <stdio.h>

struct UserAccount {
    int user_id;
    char username[50];
    int plan_type;
    int days_overdue;
    int active_devices;
};

int main() {
    int N;
    printf("Nhap so luong tai khoan (1 - 100): ");
    if (scanf("%d", &N) != 1 || N < 1 || N > 100) {
        printf("So luong tai khoan khong hop le!\n");
        return 1;
    }

    struct UserAccount accounts[100];
    int downgrade_count = 0;
    long long total_revenue = 0;

    for (int i = 0; i < N; i++) {
        printf("\n--- Nhap thong tin tai khoan thu %d ---\n", i + 1);
        printf("Ma tai khoan: ");
        scanf("%d", &accounts[i].user_id);
        printf("Ten tai khoan: ");
        scanf("%49s", accounts[i].username);

        do {
            printf("Loai goi (1: Free, 2: Personal, 3: Family): ");
            scanf("%d", &accounts[i].plan_type);
            if (accounts[i].plan_type < 1 || accounts[i].plan_type > 3) {
                printf("Loai goi khong hop le. Vui long nhap lai!\n");
            }
        } while (accounts[i].plan_type < 1 || accounts[i].plan_type > 3);

        do {
            printf("So ngay no cuoc (>= 0): ");
            scanf("%d", &accounts[i].days_overdue);
            printf("So thiet bi dang ket noi (>= 0): ");
            scanf("%d", &accounts[i].active_devices);
            if (accounts[i].days_overdue < 0 || accounts[i].active_devices < 0) {
                printf("Du lieu so ngay no hoac so thiet bi khong duoc am. Nhap lai!\n");
            }
        } while (accounts[i].days_overdue < 0 || accounts[i].active_devices < 0);
    }

    for (int i = 0; i < N; i++) {
        if (accounts[i].days_overdue >= 3 && accounts[i].plan_type != 1) {
            accounts[i].plan_type = 1;
            downgrade_count++;
        }
    }

    printf("\n================================ BAN BAO CAO DOI SOAT SAAS ================================\n");
    printf("%-8s | %-15s | %-10s | %-12s | %-12s | %-18s\n", "MA TK", "TEN TK", "MA GOI", "THIET BI", "NO (NGAY)", "PHI THUC THU (VND)");
    printf("------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < N; i++) {
        long long fee = 0;
        if (accounts[i].plan_type == 2) {
            fee = 120000;
            if (accounts[i].active_devices > 1) {
                fee += (long long)(accounts[i].active_devices - 1) * 30000;
            }
        } else if (accounts[i].plan_type == 3) {
            fee = 250000;
        } else {
            fee = 0;
        }

        total_revenue += fee;

        printf("%-8d | %-15s | %-10d | %-12d | %-12d | %-18lld\n",
               accounts[i].user_id,
               accounts[i].username,
               accounts[i].plan_type,
               accounts[i].active_devices,
               accounts[i].days_overdue,
               fee);
    }
    printf("==========================================================================================\n");
    printf("Tong doanh thu thuc te thu duoc trong ky: %lld VND\n", total_revenue);
    printf("Tong so tai khoan bi ha cap ve goi Free: %d\n", downgrade_count);

    return 0;
}
