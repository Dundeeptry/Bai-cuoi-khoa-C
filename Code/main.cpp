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

const char *layTenTrangThai(int trangThai) {
    if (trangThai == 0) return "Dang trong";
    if (trangThai == 1) return "Dang sac";
    return "Dang bao tri";
}

void inTieuDeBang(void) {
    printf("\n+------------+--------------+-----------------+-----------------+-----------------+\n");
    printf("| %-10s | %-12s | %-15s | %-15s | %-15s |\n",
           "Ma Tru", "Loai Sac", "Thoi Gian (p)", "Dien Nang (kWh)", "Trang Thai");
    printf("+------------+--------------+-----------------+-----------------+-----------------+\n");
}

void inDongBang(const struct TramSac *tru) {
    printf("| %-10s | %-12s | %-15d | %-15.3f | %-15s |\n",
           tru->maTru,
           tru->loaiSac,
           tru->thoiGianSac,
           tru->dienNangDaSac,
           layTenTrangThai(tru->trangThai));
}

void inChanBang(void) {
    printf("+------------+--------------+-----------------+-----------------+-----------------+\n");
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

void hienThiDanhSach(const struct TramSac danhSach[], int soLuong) {
    if (soLuong == 0) {
        printf("Danh sach tru sac dang trong!\n");
        return;
    }

    inTieuDeBang();
    for (int i = 0; i < soLuong; i++) {
        inDongBang(&danhSach[i]);
    }
    inChanBang();
}

void timKiemTruSac(const struct TramSac danhSach[], int soLuong) {
    if (soLuong == 0) {
        printf("Danh sach tru sac dang trong!\n");
        return;
    }

    int kieuTim = 0;
    printf("\n--- TIM KIEM TRU SAC ---\n");
    printf("1. Tim theo ma tru (maTru)\n");
    printf("2. Loc theo loai cong sac (loaiSac)\n");
    printf("Chon kieu tim kiem (1 - 2): ");
    if (scanf("%d", &kieuTim) != 1 || (kieuTim != 1 && kieuTim != 2)) {
        printf("Loi: Lua chon tim kiem khong hop le!\n");
        xoaBoNhoDem();
        return;
    }
    xoaBoNhoDem();

    char tuKhoa[64];
    if (kieuTim == 1) {
        printf("Nhap ma tru can tim (VD: TRU01): ");
        if (scanf("%63s", tuKhoa) != 1) {
            xoaBoNhoDem();
            return;
        }
        xoaBoNhoDem();

        int viTri = timViTriTheoMa(danhSach, soLuong, tuKhoa);
        if (viTri == -1) {
            printf("Khong tim thay tru sac co ma '%s'!\n", tuKhoa);
        } else {
            inTieuDeBang();
            inDongBang(&danhSach[viTri]);
            inChanBang();
        }
    } else {
        printf("Nhap loai cong sac can loc (SieuNhanh / SacNhanh / SacThuong): ");
        if (scanf("%63s", tuKhoa) != 1) {
            xoaBoNhoDem();
            return;
        }
        xoaBoNhoDem();

        if (!kiemTraLoaiSac(tuKhoa)) {
            printf("Loi: Loai cong sac khong hop le!\n");
            return;
        }

        int dem = 0;
        for (int i = 0; i < soLuong; i++) {
            if (strcmp(danhSach[i].loaiSac, tuKhoa) == 0) {
                if (dem == 0) inTieuDeBang();
                inDongBang(&danhSach[i]);
                dem++;
            }
        }
        if (dem > 0) {
            inChanBang();
            printf("-> Tim thay %d tru sac thuoc loai '%s'.\n", dem, tuKhoa);
        } else {
            printf("Khong co tru sac nao thuoc loai '%s'!\n", tuKhoa);
        }
    }
}

void capNhatTruSac(struct TramSac danhSach[], int soLuong) {
    if (soLuong == 0) {
        printf("Danh sach tru sac dang trong!\n");
        return;
    }

    char maCanSua[64];
    printf("Nhap ma tru can cap nhat (VD: TRU01): ");
    if (scanf("%63s", maCanSua) != 1) {
        xoaBoNhoDem();
        return;
    }
    xoaBoNhoDem();

    int viTri = timViTriTheoMa(danhSach, soLuong, maCanSua);
    if (viTri == -1) {
        printf("Khong tim thay tru sac co ma '%s'!\n", maCanSua);
        return;
    }

    printf("Thong tin hien tai cua tru '%s':\n", maCanSua);
    inTieuDeBang();
    inDongBang(&danhSach[viTri]);
    inChanBang();

    while (1) {
        printf("Nhap so phut cam sac moi (>= 0): ");
        if (scanf("%d", &danhSach[viTri].thoiGianSac) == 1 &&
            danhSach[viTri].thoiGianSac >= 0) {
            xoaBoNhoDem();
            break;
        }
        printf("Loi: Vui long nhap so nguyen >= 0!\n");
        xoaBoNhoDem();
    }

    while (1) {
        printf("Nhap dien nang da nap moi (kWh, >= 0): ");
        if (scanf("%f", &danhSach[viTri].dienNangDaSac) == 1 &&
            danhSach[viTri].dienNangDaSac >= 0.0f) {
            xoaBoNhoDem();
            break;
        }
        printf("Loi: Vui long nhap so thuc >= 0!\n");
        xoaBoNhoDem();
    }

    while (1) {
        printf("Nhap trang thai moi (0: Dang trong, 1: Dang sac, 2: Dang bao tri): ");
        if (scanf("%d", &danhSach[viTri].trangThai) == 1 &&
            danhSach[viTri].trangThai >= 0 && danhSach[viTri].trangThai <= 2) {
            xoaBoNhoDem();
            break;
        }
        printf("Loi: Chi nhan gia tri 0, 1 hoac 2!\n");
        xoaBoNhoDem();
    }

    printf("-> Da cap nhat thong tin tru '%s' thanh cong!\n", maCanSua);
}

void xoaTruSac(struct TramSac danhSach[], int *soLuong) {
    if (*soLuong == 0) {
        printf("Danh sach tru sac dang trong!\n");
        return;
    }

    char maCanXoa[64];
    printf("Nhap ma tru can xoa (VD: TRU01): ");
    if (scanf("%63s", maCanXoa) != 1) {
        xoaBoNhoDem();
        return;
    }
    xoaBoNhoDem();

    int viTri = timViTriTheoMa(danhSach, *soLuong, maCanXoa);
    if (viTri == -1) {
        printf("Khong tim thay tru sac co ma '%s'!\n", maCanXoa);
        return;
    }

    for (int i = viTri; i < *soLuong - 1; i++) {
        danhSach[i] = danhSach[i + 1];
    }
    (*soLuong)--;
    printf("-> Da xoa tru '%s' khoi he thong!\n", maCanXoa);
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
                hienThiDanhSach(danhSach, soLuong);
                break;
            case 3:
                timKiemTruSac(danhSach, soLuong);
                break;
            case 4:
                capNhatTruSac(danhSach, soLuong);
                break;
            case 5:
                xoaTruSac(danhSach, &soLuong);
                break;
            case 6:
            case 7:
                printf("Chuc nang dang duoc hoan thien.\n");
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