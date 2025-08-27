#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// ====== KHAI BÁO CẤU TRÚC ======
typedef struct {
    char masv[10];   // Mã sinh viên
    char hoten[50];  // Họ tên
    char lop[20];    // Lớp
    float diem;      // Điểm
} sinhvien;

// ====== HÀM HỖ TRỢ ======
// Chuyển chuỗi về chữ thường để so sánh không phân biệt hoa/thường
void toLowerCase(char *s) {
    for (int i = 0; s[i]; i++) {
        s[i] = tolower((unsigned char) s[i]);
    }
}

// ====== HÀM CẬP NHẬT ======
void capnhatsv(sinhvien ds[], int danhap,
               char ma[], char newHoten[], char newLop[], float newDiem) {
    for (int i = 0; i < danhap; i++) {
        if (strcmp(ds[i].masv, ma) == 0) { // So sánh mã SV
            if (strlen(newHoten) > 0) strcpy(ds[i].hoten, newHoten); // Nếu có nhập tên mới thì cập nhật
            if (strlen(newLop) > 0) strcpy(ds[i].lop, newLop);       // Nếu có nhập lớp mới thì cập nhật
            if (newDiem >= 0) ds[i].diem = newDiem;                  // Nếu có nhập điểm >= 0 thì cập nhật
            printf("Cap nhat thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien!\n"); // Nếu không tìm thấy
}

// ====== HÀM TÌM KIẾM THEO MÃ SV ======
int timkiemTheoMa(sinhvien ds[], int danhap, char ma[]) {
    for (int i = 0; i < danhap; i++) {
        if (strcmp(ds[i].masv, ma) == 0) { // Nếu mã trùng
            return i; // Trả về vị trí tìm thấy
        }
    }
    return -1; // Không tìm thấy
}

// ====== HÀM TÌM KIẾM THEO TÊN (không phân biệt hoa/thường) ======
int timkiemTheoTen(sinhvien ds[], int danhap, char ten[]) {
    char searchName[50];
    strcpy(searchName, ten);    // Sao chép tên cần tìm vào biến tạm
    toLowerCase(searchName);    // Chuyển tên nhập vào thành chữ thường

    for (int i = 0; i < danhap; i++) {
        char hotenTmp[50];
        strcpy(hotenTmp, ds[i].hoten); // Lấy tên SV trong danh sách
        toLowerCase(hotenTmp);         // Chuyển thành chữ thường
        if (strcmp(hotenTmp, searchName) == 0) { // So sánh
            return i; // Nếu bằng thì trả về vị trí
        }
    }
    return -1; // Không tìm thấy
}

// ====== HÀM SẮP XẾP (Bubble Sort theo điểm) ======
void sapxepsvTheoDiem(sinhvien ds[], int danhap) {
    for (int i = 0; i < danhap - 1; i++) {
        for (int j = 0; j < danhap - i - 1; j++) {
            if (ds[j].diem > ds[j+1].diem) { // So sánh điểm
                sinhvien temp = ds[j];       // Đổi chỗ nếu sai thứ tự
                ds[j] = ds[j+1];
                ds[j+1] = temp;
            }
        }
    }
    printf("Da sap xep danh sach theo diem tang dan!\n");
}

// ====== HÀM IN DANH SÁCH ======
void inds(sinhvien ds[], int danhap) {
    for (int i = 0; i < danhap; i++) {
        printf("%s | %s | %s | %.2f\n",ds[i].masv, ds[i].hoten, ds[i].lop, ds[i].diem);
    }
}

// ====== HÀM MAIN ======
int main() {
    // Khởi tạo sẵn danh sách sinh viên
    sinhvien ds[3] = {
        {"SV01", "Nguyen Van A", "CTK42", 7.5},
        {"SV02", "Le Thi B", "CTK43", 8.0},
        {"SV03", "Tran Van C", "CTK42", 6.8}
    };
    int danhap = 3; // Số SV hiện có

    printf("=== DANH SACH BAN DAU ===\n");
    inds(ds, danhap);

    // --- Tìm kiếm theo mã ---
    char ma[10];
    printf("\nNhap ma SV can tim: ");
    fgets(ma, sizeof(ma), stdin);
    ma[strcspn(ma, "\n")] = 0; // Xóa ký tự xuống dòng
    int pos = timkiemTheoMa(ds, danhap, ma);
    if (pos != -1) {
        printf("Tim thay: %s | %s | %s | %.2f\n", ds[pos].masv, ds[pos].hoten, ds[pos].lop, ds[pos].diem);
    } else {
        printf("Khong tim thay sinh vien!\n");
    }

    // --- Tìm kiếm theo tên ---
    char ten[50];
    printf("\nNhap ten SV can tim: ");
    fgets(ten, sizeof(ten), stdin);
    ten[strcspn(ten, "\n")] = 0;
    pos = timkiemTheoTen(ds, danhap, ten);
    if (pos != -1) {
        printf("Tim thay: %s | %s | %s | %.2f\n",
               ds[pos].masv, ds[pos].hoten, ds[pos].lop, ds[pos].diem);
    } else {
        printf("Khong tim thay sinh vien!\n");
    }

    // --- Sắp xếp theo điểm ---
    sapxepsvTheoDiem(ds, danhap);
    printf("\n=== DANH SACH SAU SAP XEP ===\n");
    inds(ds, danhap);

    return 0;
}

			
