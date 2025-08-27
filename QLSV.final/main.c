#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
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
            return 1; // trung
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

void themsv(sinhvien ds[], int *danhap) {
    if (*danhap >= max) {
        printf("Khong the nhap them!\n");
        return;
    }
    sinhvien sv;
    while (1) {
        printf("Nhap ma SV (chi duoc nhap so, khong trung): ");
        fflush(stdin);
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
    printf("Nhap ho ten: "); fflush(stdin); fgets(sv.hoten, sizeof(sv.hoten), stdin); sv.hoten[strcspn(sv.hoten, "\n")] = 0;
    printf("Gioi tinh: "); fflush(stdin); fgets(sv.gioitinh, sizeof(sv.gioitinh), stdin); sv.gioitinh[strcspn(sv.gioitinh, "\n")] = 0;if (strcmp(sv.gioitinh, "nam") != 0 && strcmp(sv.gioitinh, "nu") != 0){printf("loi\n");return;}
    printf("Nhap lop: "); fflush(stdin); fgets(sv.lop, sizeof(sv.lop), stdin); sv.lop[strcspn(sv.lop, "\n")] = 0;
    while (1) {
        printf("Nhap diem (1.0 - 4.0): ");
        if (scanf("%f", &sv.diem) != 1) {
            printf("Vui long nhap so!\n");
            while (getchar() != '\n'); // clear buffer
            continue;
        }
        if (sv.diem < 1.0 || sv.diem > 4.0) {
            printf("Diem phai trong khoang 1.0 - 4.0!\n");
            continue;
        }
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
    printf("Nhap ma SV can xoa: "); fflush(stdin); fgets(ma, sizeof(ma), stdin); ma[strcspn(ma, "\n")] = 0;
    for (int i = 0; i < *danhap; i++) {
        if (strcmp(ds[i].masv, ma) == 0) {
            printf("Tim thay: %s - %s - %s - %.2f\n", ds[i].masv, ds[i].hoten, ds[i].lop, ds[i].diem);
            char confirm;
            printf("Ban co chac chan muon xoa? (y/n): ");
            fflush(stdin);
            scanf("%c", &confirm);

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
    char ma[10];
    char buffer[100];
    printf("Nhap ma SV can cap nhat: "); fflush(stdin); fgets(ma, sizeof(ma), stdin); ma[strcspn(ma, "\n")] = 0;
    for (int i = 0; i < danhap; i++) {
        if (strcmp(ds[i].masv, ma) == 0) {
            printf("Thong tin hien tai:\n");
            printf("MaSV: %s | Ho ten: %s | Lop: %s | Diem: %.2f\n",
                   ds[i].masv, ds[i].hoten, ds[i].lop, ds[i].diem);

            printf("Nhap ho ten moi (Enter de giu nguyen): ");
            fflush(stdin);
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
                ds[i].diem = atof(buffer);
            }

            printf("Cap nhat thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien!\n");
}

void ghitep(sinhvien ds[], int danhap) {
    FILE *f = fopen("sinhvien.txt", "w");
    if (f == NULL) {
        printf("Khong the mo tep de ghi\n");
        return;
    }
    for (int i = 0; i < danhap; i++) {
        fprintf(f, "%s|%s|%s|%s|%.2f\n",
                ds[i].masv, ds[i].hoten, ds[i].gioitinh, ds[i].lop, ds[i].diem);
    }
    fclose(f);
    printf("Da ghi du lieu vao file\n");
}

void doctep(sinhvien ds[], int *danhap) {
    FILE *f = fopen("sinhvien.txt", "r");
    if (f == NULL) {
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
    printf("=====Tim Kiem Sinh Vien=====\n");
    printf("1. Tim kiem bang ma so sinh vien\n");
    printf("2. Tim kiem bang ho ten\n");
    printf("==============================\n");
    printf("Nhap lua chon: ");
    scanf("%d", &choice);
    getchar();
    if (choice == 1) {
        printf("Nhap ma so sinh vien can tim: ");
        fgets(key, sizeof(key), stdin);
        key[strcspn(key, "\n")] = 0;
        for (int i = 0; i < danhap; i++) {
            if (strcmp(ds[i].masv, key) == 0) {
                printf("Da tim thay sinh vien !!!\n");
                printf("Ma SV: %s | HoTen: %s | GioiTinh: %s | Lop: %s | Diem: %.2f\n",
                       ds[i].masv, ds[i].hoten, ds[i].gioitinh, ds[i].lop, ds[i].diem);
                found = 1;
            }
        }
        if (!found) {
            printf("Khong tim thay voi MSSV: %s\n", key);
        }
    }
    if (choice == 2) {
        printf("Nhap ho ten can tim: ");
        fgets(key, sizeof(key), stdin);
        key[strcspn(key, "\n")] = 0;
        for (int i = 0; i < danhap; i++) {
            if (strcasecmp(ds[i].hoten, key) == 0) {
                printf("Da tim thay sinh vien !!!\n");
                printf("Ma SV: %s | HoTen: %s | GioiTinh: %s | Lop: %s | Diem: %.2f\n",
                       ds[i].masv, ds[i].hoten, ds[i].gioitinh, ds[i].lop, ds[i].diem);
                found = 1;
            }
        }
        if (!found) {
            printf("Khong tim thay sinh vien voi ho ten: %s\n", key);
        }
    }
}

void sapxep(sinhvien ds[], int danhap) {
    int choice;
    printf("===== SAP XEP SINH VIEN =====\n");
    printf("1. Sap xep theo Ma SV (A -> Z)\n");
    printf("2. Sap xep theo Ho ten (A -> Z)\n");
    printf("3. Sap xep theo Diem (Cao -> Thap)\n");
    printf("Nhap lua chon: ");
    scanf("%d", &choice);

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

    printf("Da sap xep xong!\n");
    hienthisv(ds, danhap);
}

int main() {
    int choice;
    int danhap = 0;
    sinhvien ds[max];

    doctep(ds, &danhap);

    do {
        printf("\n\033[1;31m===== CHUONG TRINH QUAN LY SINH VIEN =====\033[0m\n");
        printf("1. Them sinh vien\n");
        printf("2. Hien thi danh sach sinh vien\n");
        printf("3. Xoa sinh vien\n");
        printf("4. Cap nhat thong tin sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("6. Sap xep sinh vien\n");
        printf("0. Thoat\n");
        printf("==========================================\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:{
                int n;
                printf("Ban muon nhap bao nhiu sinh vien ");
                scanf("%d",&n);
                for(int i=0;i<n;i++)
                {
                    themsv(ds, &danhap);
                }
                ghitep(ds, danhap);
                break;}
            case 2:
                hienthisv(ds, danhap);
                break;
            case 3:{
                int n;
                printf("ban muon xoa bao nhiu sinh vien ");
                scanf("%d",&n);
                for(int i=0;i<n;i++)
                {xoasv(ds, &danhap);}
                ghitep(ds, danhap);
                break;}
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
                printf("Lua chon khong hop le! Vui long nhap lai.\n");
        }
    } while (choice != 0);

    return 0;
}
