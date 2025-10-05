#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

struct SinhVien {
    char maSV[20];
    char hoTen[50];
    float diem;
    SinhVien* next;
};
// Tạo sinh viên
SinhVien* taoSinhVien(const char ma[], const char ten[], float d) {
    SinhVien* sv = new SinhVien;
    strcpy(sv->maSV, ma);
    strcpy(sv->hoTen, ten);
    sv->diem = d;
    sv->next = NULL;
    return sv;
}
//  1. Thêm sinh viên 
void themSinhVien(SinhVien*& head) {
    char ma[20], ten[50];
    float diem;
    printf("Nhap ma SV: ");
    scanf("%s", ma);
    getchar(); // bỏ ký tự enter
    printf("Nhap ho ten: ");
    fgets(ten, sizeof(ten), stdin);
    ten[strcspn(ten, "\n")] = '\0'; // xóa ký tự xuống dòng
    printf("Nhap diem: ");
    scanf("%f", &diem);
    SinhVien* sv = taoSinhVien(ma, ten, diem);
    if (head == NULL) {
        head = sv;
    } else {
        SinhVien* temp;
        for (temp = head; temp->next != NULL; temp = temp->next);
        temp->next = sv;
    }
    printf("Da them sinh vien thanh cong.\n");
}
//  2. Hiển thị danh sách 
void hienThi(SinhVien* head) {
    if (head == NULL) {
        printf("Danh sach rong.\n");
        return;
    }
    printf("=== DANH SACH SINH VIEN ===\n");
    int stt = 1;
    for (SinhVien* temp = head; temp != NULL; temp = temp->next) {
        printf("%d. MaSV: %s | Ho ten: %s | Diem: %.2f\n", stt, temp->maSV, temp->hoTen, temp->diem);
        stt++;
    }
}
//  3. Tìm kiếm sinh viên 
void timKiem(SinhVien* head) {
    char ma[20];
    printf("Nhap ma SV can tim: ");
    scanf("%s", ma);
    for (SinhVien* temp = head; temp != NULL; temp = temp->next) {
        if (strcmp(temp->maSV, ma) == 0) {
            printf("Tim thay sinh vien: %s, diem: %.2f\n", temp->hoTen, temp->diem);
            return;
        }
    }
    printf("Khong tim thay sinh vien.\n");
}
//  4. Xóa sinh viên 
void xoaSinhVien(SinhVien*& head) {
    char ma[20];
    printf("Nhap ma SV can xoa: ");
    scanf("%s", ma);
    if (head == NULL) return;
    if (strcmp(head->maSV, ma) == 0) {
        SinhVien* temp = head;
        head = head->next;
        delete temp;
        printf("Da xoa sinh vien.\n");
        return;
    }
    for (SinhVien* cur = head; cur->next != NULL; cur = cur->next) {
        if (strcmp(cur->next->maSV, ma) == 0) {
            SinhVien* temp = cur->next;
            cur->next = temp->next;
            delete temp;
            printf("Da xoa sinh vien.\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien de xoa.\n");
}
//  5. Cập nhật sinh viên 
void capNhat(SinhVien* head) {
    char ma[20];
    printf("Nhap ma SV can cap nhat: ");
    scanf("%s", ma);
    for (SinhVien* temp = head; temp != NULL; temp = temp->next) {
        if (strcmp(temp->maSV, ma) == 0) {
            getchar(); // bỏ ký tự enter
            printf("Nhap ten moi: ");
            fgets(temp->hoTen, sizeof(temp->hoTen), stdin);
            temp->hoTen[strcspn(temp->hoTen, "\n")] = '\0';
            printf("Nhap diem moi: ");
            scanf("%f", &temp->diem);
            printf("Da cap nhat thong tin.\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien.\n");
}
// 6. Sắp xếp theo điểm 
void sapXep(SinhVien*& head) {
    if (head == NULL) return;
    for (SinhVien* i = head; i != NULL; i = i->next) {
        for (SinhVien* j = i->next; j != NULL; j = j->next) {
            if (i->diem > j->diem) {
                float tmpD = i->diem;
                i->diem = j->diem;
                j->diem = tmpD;
                char tmpMa[20], tmpTen[50];
                strcpy(tmpMa, i->maSV);
                strcpy(tmpTen, i->hoTen);
                strcpy(i->maSV, j->maSV);
                strcpy(i->hoTen, j->hoTen);
                strcpy(j->maSV, tmpMa);
                strcpy(j->hoTen, tmpTen);
            }
        }
    }
    printf("Da sap xep danh sach theo diem tang dan.\n");
}
// HÀM MENU 
void menu() {
    printf("\n CHUONG TRINH QUAN LY SINH VIEN \n");
    printf("1. Them sinh vien\n");
    printf("2. Hien thi danh sach\n");
    printf("3. Tim kiem sinh vien\n");
    printf("4. Xoa sinh vien\n");
    printf("5. Cap nhat thong tin\n");
    printf("6. Sap xep theo diem\n");
    printf("0. Thoat\n");
}

//  HÀM CHÍNH 
int main() {
    SinhVien* head = NULL;
    int chon;
    do {
        menu();
        printf("Nhap lua chon: ");
        scanf("%d", &chon);
        switch (chon) {
            case 1: themSinhVien(head); break;
            case 2: hienThi(head); break;
            case 3: timKiem(head); break;
            case 4: xoaSinhVien(head); break;
            case 5: capNhat(head); break;
            case 6: sapXep(head); break;
            case 0: printf("Thoat chuong trinh.\n"); break;
            default: printf("Lua chon khong hop le.\n");
        }
    } while (chon != 0);

    return 0;
}