
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