#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define max 1000

typedef struct {
    char masv[10];
    char hoten[50];
    char lop[50];
    float diem;
    char gioitinh[10];
} sinhvien;

int checkTrungMSSV(char *ma, sinhvien ds[], int danhap) {
    for (int i = 0; i < danhap; i++) {
        if (strcmp(ds[i].masv, ma) == 0) {
            return 1; // trùng
        }
    }
    return 0;
}

int laSo(char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (!isdigit(s[i])) return 0;
    }
    return 1;
}

void clearBuffer() {
    while (getchar() != '\n');
}

void themsv(sinhvien ds[], int *danhap) {
    if (*danhap >= max) {
        printf("Khong the nhap them!\n");
        return;
    }

    sinhvien sv;

    while (1) {
        printf("Nhap ma SV (chi duoc nhap so, khong trung): ");
        fgets(sv.masv, sizeof(sv.masv), stdin);
        sv.masv[strcspn(sv.masv, "\n")] = 0;

        if (!laSo(sv.masv)) {
            printf("Ma SV chi duoc phep la so!\n");
            continue;
        }

        if (checkTrungMSSV(sv.masv, ds, *danhap)) {
            printf("Ma SV da ton tai!\n");
            continue;
        }

        break;
    }

    printf("Nhap ho ten: ");
    fgets(sv.hoten, sizeof(sv.hoten), stdin);
    sv.hoten[strcspn(sv.hoten, "\n")] = 0;

    // Nhập giới tính và kiểm tra hợp lệ
    while (1) {
        printf("Gioi tinh (nam/nu): ");
        fgets(sv.gioitinh, sizeof(sv.gioitinh), stdin);
        sv.gioitinh[strcspn(sv.gioitinh, "\n")] = 0;

        if (strcmp(sv.gioitinh, "nam") == 0 || strcmp(sv.gioitinh, "nu") == 0) {
            break;
        } else {
            printf("Gioi tinh chi duoc nhap 'nam' hoac 'nu'. Vui long nhap lai.\n");
        }
    }

    printf("Nhap lop: ");
    fgets(sv.lop, sizeof(sv.lop), stdin);
    sv.lop[strcspn(sv.lop, "\n")] = 0;

    while (1) {
        printf("Nhap diem (1.0 - 4.0): ");
        if (scanf("%f", &sv.diem) != 1) {
            printf("Vui long nhap so!\n");
            clearBuffer();
            continue;
        }

        if (sv.diem < 1.0 || sv.diem > 4.0) {
            printf("Diem phai trong khoang 1.0 - 4.0!\n");
            continue;
        }

        clearBuffer();
        break;
    }

    ds[*danhap] = sv;
    (*danhap)++;
    printf("Da them sinh vien!\n");
}

void hienthisv(sinhvien ds[], int danhap) {
    printf("\n%-10s %-25s %-10s %-20s %-5s\n", "MaSV", "Ho ten", "Gioi tinh", "Lop", "Diem");
    printf("-------------------------------------------------------------------------------------\n");
    for (int i = 0; i < danhap; i++) {
        printf("%-10s %-25s %-10s %-20s %-5.2f\n",
               ds[i].masv, ds[i].hoten, ds[i].gioitinh, ds[i].lop, ds[i].diem);
    }
}

void xoasv(sinhvien ds[], int *danhap) {
    char ma[10];
    printf("Nhap ma SV can xoa: ");
    fgets(ma, sizeof(ma), stdin);
    ma[strcspn(ma, "\n")] = 0;

    for (int i = 0; i < *danhap; i++) {
        if (strcmp(ds[i].masv, ma) == 0) {printf("Tim thay: %s - %s - %s - %.2f\n", ds[i].masv, ds[i].hoten, ds[i].lop, ds[i].diem);
            char confirm;
            printf("Ban co chac chan muon xoa? (y/n): ");
            scanf(" %c", &confirm);
            clearBuffer();

            if (confirm == 'y' || confirm == 'Y') {
                for (int j = i; j < *danhap - 1; j++) {
                    ds[j] = ds[j + 1];
                }
                (*danhap)--;
                printf("Xoa thanh cong!\n");
            } else {
                printf("Huy thao tac xoa!\n");
            }
            return;
        }
    }
    printf("Khong tim thay de xoa!\n");
}

void capnhatsv(sinhvien ds[], int danhap) {
    char ma[10], buffer[100];
    printf("Nhap ma SV can cap nhat: ");
    fgets(ma, sizeof(ma), stdin);
    ma[strcspn(ma, "\n")] = 0;

    for (int i = 0; i < danhap; i++) {
        if (strcmp(ds[i].masv, ma) == 0) {
            printf("Thong tin hien tai:\n");
            printf("MaSV: %s | Ho ten: %s | Lop: %s | Diem: %.2f\n",
                   ds[i].masv, ds[i].hoten, ds[i].lop, ds[i].diem);

            printf("Nhap ho ten moi (Enter de giu nguyen): ");
            fgets(buffer, sizeof(buffer), stdin);
            if (buffer[0] != '\n') {
                buffer[strcspn(buffer, "\n")] = 0;
                strcpy(ds[i].hoten, buffer);
            }

            printf("Nhap lop moi (Enter de giu nguyen): ");
            fgets(buffer, sizeof(buffer), stdin);
            if (buffer[0] != '\n') {
                buffer[strcspn(buffer, "\n")] = 0;
                strcpy(ds[i].lop, buffer);
            }

            printf("Nhap diem moi (Enter de giu nguyen): ");
            fgets(buffer, sizeof(buffer), stdin);
            if (buffer[0] != '\n') {
                float new_diem = atof(buffer);
                if (new_diem >= 1.0 && new_diem <= 4.0) {
                    ds[i].diem = new_diem;
                } else {
                    printf("Diem khong hop le, giu nguyen diem cu.\n");
                }
            }

            printf("Cap nhat thanh cong!\n");
            return;
        }
    }

    printf("Khong tim thay sinh vien!\n");
}

void ghitep(sinhvien ds[], int danhap) {
    FILE *f = fopen("sinhvien.txt", "w");
    if (!f) {
        printf("Khong the mo tep de ghi.\n");
        return;
    }
    for (int i = 0; i < danhap; i++) {
        fprintf(f, "%s|%s|%s|%s|%.2f\n",
                ds[i].masv, ds[i].hoten, ds[i].gioitinh, ds[i].lop, ds[i].diem);
    }
    fclose(f);
    printf("Da ghi du lieu vao file.\n");
}

void doctep(sinhvien ds[], int *danhap) {
    FILE *f = fopen("sinhvien.txt", "r");
    if (!f) {
        printf("Khong tim thay tep, bat dau voi danh sach rong.\n");
        return;
    }

    *danhap = 0;
    while (fscanf(f, "%9[^|]|%49[^|]|%9[^|]|%49[^|]|%f\n",
                  ds[*danhap].masv, ds[*danhap].hoten, ds[*danhap].gioitinh,
                  ds[*danhap].lop, &ds[*danhap].diem) == 5) {
        (*danhap)++;
    if (*danhap >= max) break;
    }

    fclose(f);
    printf("Da doc du lieu tu tep, hien co %d sinh vien.\n", *danhap);
}

void FindSV(sinhvien ds[], int danhap) {
    int choice;
    char key[50];
    int found = 0;

    printf("===== Tim Kiem Sinh Vien =====\n");
    printf("1. Theo ma so sinh vien\n");
    printf("2. Theo ho ten\n");
    printf("Nhap lua chon: ");
    scanf("%d", &choice);
    clearBuffer();

    if (choice == 1) {
        printf("Nhap ma SV: ");
        fgets(key, sizeof(key), stdin);
        key[strcspn(key, "\n")] = 0;

        for (int i = 0; i < danhap; i++) {
            if (strcmp(ds[i].masv, key) == 0) {
                printf("Ma SV: %s | HoTen: %s | GioiTinh: %s | Lop: %s | Diem: %.2f\n",
                       ds[i].masv, ds[i].hoten, ds[i].gioitinh, ds[i].lop, ds[i].diem);
                found = 1;
            }
        }
    } else if (choice == 2) {
        printf("Nhap ho ten: ");
        fgets(key, sizeof(key), stdin);
        key[strcspn(key, "\n")] = 0;

        for (int i = 0; i < danhap; i++) {
            if (strcasecmp(ds[i].hoten, key) == 0) {
                printf("Ma SV: %s | HoTen: %s | GioiTinh: %s | Lop: %s | Diem: %.2f\n",
                       ds[i].masv, ds[i].hoten, ds[i].gioitinh, ds[i].lop, ds[i].diem);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("Khong tim thay sinh vien!\n");
    }
}

void sapxep(sinhvien ds[], int danhap) {
    int choice;
    printf("1. Sap xep theo Ma SV (A-Z)\n");
    printf("2. Sap xep theo Ten (A-Z)\n");
    printf("3. Sap xep theo Diem (Giam dan)\n");
    printf("Nhap lua chon: ");
    scanf("%d", &choice);
    clearBuffer();

    for (int i = 0; i < danhap - 1; i++) {
        for (int j = i + 1; j < danhap; j++) {
            int cmp = 0;
            if (choice == 1) {
                cmp = strcmp(ds[i].masv, ds[j].masv) > 0;
            } else if (choice == 2) {
                cmp = strcasecmp(ds[i].hoten, ds[j].hoten) > 0;
            } else if (choice == 3) {
                cmp = ds[i].diem < ds[j].diem;
            }

            if (cmp) {
                sinhvien temp = ds[i];
                ds[i] = ds[j];
                ds[j] = temp;
            }
        }
    }

    printf("Da sap xep!\n");
    hienthisv(ds, danhap);
}

int main() {
    int choice, danhap = 0;
    sinhvien ds[max];

    doctep(ds, &danhap);

    do {
        printf("\n===== CHUONG TRINH QUAN LY SINH VIEN =====\n");
        printf("1. Them sinh vien\n");
        printf("2. Hien thi danh sach\n");
        printf("3. Xoa sinh vien\n");
        printf("4. Cap nhat thong tin\n");
        printf("5. Tim kiem\n");
        printf("6. Sap xep\n");
        printf("0. Thoat\n");
        printf("===========================================\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        clearBuffer();

        switch (choice) {
            case 1: {
                int n;
      printf("Nhap so sinh vien muon them: ");
                scanf("%d", &n);
                clearBuffer();
                for (int i = 0; i < n; i++) {
                    themsv(ds, &danhap);
                }
                ghitep(ds, danhap);
                break;
            }
            case 2:
                hienthisv(ds, danhap);
                break;
            case 3: {
                int n;
                printf("Nhap so sinh vien muon xoa: ");
                scanf("%d", &n);
                clearBuffer();
                for (int i = 0; i < n; i++) {
                    xoasv(ds, &danhap);
                }
                ghitep(ds, danhap);
                break;
            }
            case 4:
                capnhatsv(ds, danhap);
                ghitep(ds, danhap);
                break;
            case 5:
                FindSV(ds, danhap);
                break;
            case 6:
                sapxep(ds, danhap);
                ghitep(ds, danhap);
                break;
            case 0:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 0);

    return 0;
}              