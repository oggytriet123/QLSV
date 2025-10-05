#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

struct Node {
    char maSV[20];
    char hoTen[50];
    char lop[20];
    float diem;
    Node* next;
};

// Tạo sinh viên mới
Node* taoNode(const char ma[], const char ten[], const char lop[], float d) {
    Node* sv = new Node;
    strcpy(sv->maSV, ma);
    strcpy(sv->hoTen, ten);
    strcpy(sv->lop, lop);
    sv->diem = d;
    sv->next = NULL;
    return sv;
}

// 1. Thêm sinh viên
void themSinhVien(Node*& head) {
    char ma[20], ten[50], lop[20];
    float diem;
    printf("Nhap ma SV: ");
    scanf("%s", ma);
    getchar();
    printf("Nhap ho ten: ");
    fgets(ten, sizeof(ten), stdin);
    ten[strcspn(ten, "\n")] = '\0';
    printf("Nhap lop: ");
    scanf("%s", lop);
    printf("Nhap diem: ");
    scanf("%f", &diem);

    Node* sv = taoNode(ma, ten, lop, diem);
    if (head == NULL)
        head = sv;
    else {
        Node* temp;
        for (temp = head; temp->next != NULL; temp = temp->next);
        temp->next = sv;
    }
    printf("Da them sinh vien thanh cong!\n");
}

// 2. Hiển thị danh sách
void hienThi(Node* head) {
    if (head == NULL) {
        printf("Danh sach rong.\n");
        return;
    }
    printf("\n=== DANH SACH SINH VIEN ===\n");
    int stt = 1;
    for (Node* temp = head; temp != NULL; temp = temp->next) {
        printf("%d. MaSV: %s | Ho ten: %s | Lop: %s | Diem: %.2f\n",
               stt++, temp->maSV, temp->hoTen, temp->lop, temp->diem);
    }
}

// 3. Tìm kiếm sinh viên theo mã
void timKiem(Node* head) {
    char ma[20];
    printf("Nhap ma SV can tim: ");
    scanf("%s", ma);
    for (Node* temp = head; temp != NULL; temp = temp->next) {
        if (strcmp(temp->maSV, ma) == 0) {
            printf("Tim thay: %s | Lop: %s | Diem: %.2f\n", temp->hoTen, temp->lop, temp->diem);
            return;
        }
    }
    printf("Khong tim thay sinh vien.\n");
}

// 4. Xóa sinh viên
void xoaSinhVien(Node*& head) {
    char ma[20];
    printf("Nhap ma SV can xoa: ");
    scanf("%s", ma);

    if (head == NULL) return;
    if (strcmp(head->maSV, ma) == 0) {
        Node* temp = head;
        head = head->next;
        delete temp;
        printf("Da xoa sinh vien.\n");
        return;
    }

    for (Node* cur = head; cur->next != NULL; cur = cur->next) {
        if (strcmp(cur->next->maSV, ma) == 0) {
            Node* temp = cur->next;
            cur->next = temp->next;
            delete temp;
            printf("Da xoa sinh vien.\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien de xoa.\n");
}

// 5. Cập nhật sinh viên
void capNhat(Node* head) {
    char ma[20];
    printf("Nhap ma SV can cap nhat: ");
    scanf("%s", ma);

    for (Node* temp = head; temp != NULL; temp = temp->next) {
        if (strcmp(temp->maSV, ma) == 0) {
            getchar();
            printf("Nhap ten moi: ");
            fgets(temp->hoTen, sizeof(temp->hoTen), stdin);
            temp->hoTen[strcspn(temp->hoTen, "\n")] = '\0';
            printf("Nhap lop moi: ");
            scanf("%s", temp->lop);
            printf("Nhap diem moi: ");
            scanf("%f", &temp->diem);
            printf("Da cap nhat thong tin sinh vien.\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien.\n");
}

// 6. Sắp xếp danh sách theo điểm
void sapXep(Node*& head) {
    if (head == NULL) return;
    for (Node* i = head; i != NULL; i = i->next) {
        for (Node* j = i->next; j != NULL; j = j->next) {
            if (i->diem > j->diem) {
                swap(i->diem, j->diem);
                char tmpMa[20], tmpTen[50], tmpLop[20];
                strcpy(tmpMa, i->maSV);
                strcpy(tmpTen, i->hoTen);
                strcpy(tmpLop, i->lop);
                strcpy(i->maSV, j->maSV);
                strcpy(i->hoTen, j->hoTen);
                strcpy(i->lop, j->lop);
                strcpy(j->maSV, tmpMa);
                strcpy(j->hoTen, tmpTen);
                strcpy(j->lop, tmpLop);
            }
        }
    }
    printf("Da sap xep danh sach theo diem tang dan.\n");
}

// 7. Lưu danh sách vào file
void luuFile(Node* head, const char* tenFile) {
    FILE* f = fopen(tenFile, "w");
    if (f == NULL) {
        printf("Khong mo duoc file!\n");
        return;
    }
    for (Node* temp = head; temp != NULL; temp = temp->next) {
        fprintf(f, "%s|%s|%s|%.2f\n", temp->maSV, temp->hoTen, temp->lop, temp->diem);
    }
    fclose(f);
    printf("Da luu danh sach vao file %s\n", tenFile);
}

// 8. Đọc danh sách từ file
void docFile(Node*& head, const char* tenFile) {
    FILE* f = fopen(tenFile, "r");
    if (f == NULL) return;
    char ma[20], ten[50], lop[20];
    float diem;
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%f\n", ma, ten, lop, &diem) == 4) {
        Node* sv = taoNode(ma, ten, lop, diem);
        if (head == NULL)
            head = sv;
        else {
            Node* temp;
            for (temp = head; temp->next != NULL; temp = temp->next);
            temp->next = sv;
        }
    }
    fclose(f);
    printf("Da doc danh sach tu file %s\n", tenFile);
}

// Menu
void menu() {
    printf("\n====== CHUONG TRINH QUAN LY SINH VIEN ======\n");
    printf("1. Them sinh vien\n");
    printf("2. Hien thi danh sach\n");
    printf("3. Tim kiem sinh vien\n");
    printf("4. Xoa sinh vien\n");
    printf("5. Cap nhat thong tin\n");
    printf("6. Sap xep theo diem\n");
    printf("7. Luu danh sach vao file\n");
    printf("0. Thoat\n");
    printf("===========================================\n");
}

int main() {
    Node* head = NULL;
    const char* fileName = "sinhvien.txt";
    int chon;
    docFile(head, fileName);
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
            case 7: luuFile(head, fileName); break;
            case 0:
                luuFile(head, fileName);
                printf("Thoat chuong trinh.\n");
                break;
            default: printf("Lua chon khong hop le.\n");
        }
    } while (chon != 0);
    return 0;
}
