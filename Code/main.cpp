#include <stdio.h>

#define MAX_TRU 100

struct TramSac {
    char maTru[10];
    char loaiSac[20];
    int thoiGianSac;
    float dienNangDaSac;
    int trangThai;
};

void xoaBoNhoDem(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void hienThiMenu(void) {
    printf("\n========== QUAN LY TRAM SAC XE DIEN ==========\n");
    printf("1. Them moi tru sac (Create)\n");
    printf("2. Hien thi danh sach (Read)\n");
    printf("3. Tim kiem tru sac (Search)\n");
    printf("4. Cap nhat thong tin (Update)\n");
    printf("5. Xoa tru sac (Delete)\n");
    printf("6. Thong ke doanh thu\n");
    printf("7. Loc tru sac qua tai (> 120 phut)\n");
    printf("0. Thoat chuong trinh\n");
    printf("==============================================\n");
    printf("Chon chuc nang (0 - 7): ");
}

int main(void) {
    struct TramSac danhSach[MAX_TRU];
    int soLuong = 0;
    int luaChon = -1;
    (void)danhSach;
    (void)soLuong;

    do {
        hienThiMenu();
        if (scanf("%d", &luaChon) != 1) {
            printf("Loi: Vui long nhap mot so nguyen tu 0 den 7!\n");
            xoaBoNhoDem();
            luaChon = -1;
            continue;
        }
        xoaBoNhoDem();

        switch (luaChon) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                printf("Chuc nang dang duoc phat trien.\n");
                break;
            case 0:
                printf("Da thoat chuong trinh.\n");
                break;
            default:
                printf("Loi: Lua chon khong hop le (0 - 7)!\n");
                break;
        }
    } while (luaChon != 0);

    return 0;
}