#include <ctype.h>
#include <stdio.h>
#include <string.h>

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

int timViTriTheoMa(const struct TramSac danhSach[], int soLuong, const char *maTru) {
    for (int i = 0; i < soLuong; i++) {
        if (strcmp(danhSach[i].maTru, maTru) == 0) {
            return i;
        }
    }
    return -1;
}

int kiemTraMaTru(const char *maTru) {
    size_t len = strlen(maTru);
    if (len < 4 || len > 9 || strncmp(maTru, "TRU", 3) != 0) {
        return 0;
    }
    for (size_t i = 3; i < len; i++) {
        if (!isdigit((unsigned char)maTru[i])) {
            return 0;
        }
    }
    return 1;
}

int kiemTraLoaiSac(const char *loaiSac) {
    return strcmp(loaiSac, "SieuNhanh") == 0 ||
           strcmp(loaiSac, "SacNhanh") == 0 ||
           strcmp(loaiSac, "SacThuong") == 0;
}

void themTruSac(struct TramSac danhSach[], int *soLuong) {
    if (*soLuong >= MAX_TRU) {
        printf("Danh sach da day (%d tru)!\n", MAX_TRU);
        return;
    }

    int soTruCanThem = 0;
    while (1) {
        printf("Nhap so luong tru sac muon them (1 - %d): ", MAX_TRU - *soLuong);
        if (scanf("%d", &soTruCanThem) == 1 && soTruCanThem >= 1 &&
            *soLuong + soTruCanThem <= MAX_TRU) {
            xoaBoNhoDem();
            break;
        }
        printf("Loi: So luong khong hop le!\n");
        xoaBoNhoDem();
    }

    for (int i = 0; i < soTruCanThem; i++) {
        struct TramSac truMoi;
        printf("\n--- Nhap thong tin tru sac thu %d ---\n", i + 1);

        while (1) {
            char buffer[64];
            printf("Ma tru (VD: TRU01): ");
            if (scanf("%63s", buffer) == 1) {
                xoaBoNhoDem();
                if (!kiemTraMaTru(buffer)) {
                    printf("Loi: Ma tru phai bat dau bang 'TRU', theo sau la cac chu so (toi da 9 ky tu)!\n");
                    continue;
                }
                if (timViTriTheoMa(danhSach, *soLuong, buffer) != -1) {
                    printf("Loi: Ma tru '%s' da ton tai!\n", buffer);
                    continue;
                }
                strcpy(truMoi.maTru, buffer);
                break;
            }
            xoaBoNhoDem();
        }

        while (1) {
            char buffer[64];
            printf("Loai cong sac (SieuNhanh / SacNhanh / SacThuong): ");
            if (scanf("%63s", buffer) == 1) {
                xoaBoNhoDem();
                if (kiemTraLoaiSac(buffer)) {
                    strcpy(truMoi.loaiSac, buffer);
                    break;
                }
            } else {
                xoaBoNhoDem();
            }
            printf("Loi: Chi chap nhan 'SieuNhanh', 'SacNhanh' hoac 'SacThuong'!\n");
        }

        while (1) {
            printf("So phut da cam sac (>= 0): ");
            if (scanf("%d", &truMoi.thoiGianSac) == 1 && truMoi.thoiGianSac >= 0) {
                xoaBoNhoDem();
                break;
            }
            printf("Loi: Vui long nhap so nguyen >= 0!\n");
            xoaBoNhoDem();
        }

        while (1) {
            printf("Dien nang da nap (kWh, >= 0): ");
            if (scanf("%f", &truMoi.dienNangDaSac) == 1 && truMoi.dienNangDaSac >= 0.0f) {
                xoaBoNhoDem();
                break;
            }
            printf("Loi: Vui long nhap so thuc >= 0!\n");
            xoaBoNhoDem();
        }

        while (1) {
            printf("Trang thai (0: Dang trong, 1: Dang sac, 2: Dang bao tri): ");
            if (scanf("%d", &truMoi.trangThai) == 1 &&
                truMoi.trangThai >= 0 && truMoi.trangThai <= 2) {
                xoaBoNhoDem();
                break;
            }
            printf("Loi: Chi nhan gia tri 0, 1 hoac 2!\n");
            xoaBoNhoDem();
        }

        danhSach[*soLuong] = truMoi;
        (*soLuong)++;
        printf("-> Da them tru '%s' thanh cong!\n", truMoi.maTru);
    }
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
                themTruSac(danhSach, &soLuong);
                break;
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