#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include<math.h>
#include<string.h>
#define max 100//g�ng max=100
int danhap=0;//s? l�?ng sinh vi�n �? nh?p
typedef struct{
    char masv[10];
    char hoten[50];
    char lop[50];
    float diem;
    char gioitinh[10];
} sinhvien;
sinhvien ds[max];//m?ng l�u sinh vi�n v?i max l� 100 h?c sinh
void themsv()
{
    if(danhap>=max){
        printf("khong the nhap them");
        return;}
    sinhvien sv;
    printf("Nhap ma SV: "); fflush(stdin); fgets(sv.masv,sizeof(sv.masv),stdin); sv.masv[strcspn(sv.masv,"\n")] = 0;//fflush �? x�a b? nh? �?m tr�nh b? d�nh d? li?u t? l?n nh?p trc
    printf("Nhap ho ten: "); fflush(stdin); fgets(sv.hoten,sizeof(sv.hoten),stdin); sv.hoten[strcspn(sv.hoten,"\n")] = 0;
    printf("Gioi tinh: "); fflush(stdin); fgets(sv.gioitinh,sizeof(sv.gioitinh),stdin); sv.gioitinh[strcspn(sv.gioitinh,"\n")] = 0;
    printf("Nhap lop: "); fflush(stdin); fgets(sv.lop,sizeof(sv.lop),stdin); sv.lop[strcspn(sv.lop,"\n")] = 0;
    printf("Nhap diem: "); scanf("%f", &sv.diem);
    ds[danhap++]=sv;
    printf("da them sinh vien");
}
void hienthisv()
{
    printf("\n%-10s %-25s %-10s %-10s %-5s\n", "MaSV", "Ho ten","Gioi tinh", "Lop", "Diem");//t?o b?ng �? hi?n danh s�ch v?i 4 c?t c�ch �?u c�n tr�i
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < danhap; i++) {
        printf("%-10s %-25s %-10s %-10s %-5.2f\n", //t?i sao l?i d�ng 10 25 10 v� 5 th? do e tham kh?o c�ch �? t?o b?ng tr�n m?ng
               ds[i].masv, ds[i].hoten,ds[i].gioitinh, ds[i].lop, ds[i].diem);
    }
}
void xoasv()
{
    char ma[10];
    printf("Nhap ma SV can xoa: "); fflush(stdin); fgets(ma,sizeof(ma),stdin); ma[strcspn(ma,"\n")] = 0;//nh?p m? sv mu?n x�a
     for (int i = 0; i < danhap; i++) {
        if (strcmp(ds[i].masv, ma) == 0) {
            printf("Tim thay: %s - %s - %s - %.2f\n",ds[i].masv, ds[i].hoten, ds[i].lop, ds[i].diem);//in th�ng tin sv mu?n x�a
            char confirm;
            printf("Ban co chac chan muon xoa? (y/n): ");//x�c th?c r?ng ng�?i d�ng c� th?c s? mu?n x�a sv n�y kh�ng
            fflush(stdin);
            scanf("%c", &confirm);

            if (confirm == 'y' || confirm == 'Y') {
                for (int j = i; j < danhap - 1; j++) {
                    ds[j] = ds[j+1];//d?ch c�c ph?n t? kh�ng c?n x�a sang b�n tr�i v� x�a sv mu?n x�a
                }
                danhap--;
                printf("Xoa thanh cong!\n");
            } else {
                printf("Huy thao tac xoa!\n");//ghi nh?n m?i k? t? kh�c y v� Y l� h?y
            }
            return;
        }
    }
    printf("Khong tim thay de xoa!\n");//n?u ko g?p return c� ngh?a l� ko t?m th?y sv
}
void capnhatsv() {//kh�ng th? thay �?i m? sv v? l� key
    char ma[10];
    char buffer[100];
    printf("Nhap ma SV can cap nhat: "); fflush(stdin); fgets(ma,sizeof(ma),stdin); ma[strcspn(ma,"\n")] = 0;//nh?p m? sv
    for (int i = 0; i < danhap; i++) {
        if (strcmp(ds[i].masv, ma) == 0) {
            printf("Thong tin hien tai:\n");
            printf("MaSV: %s | Ho ten: %s | Lop: %s | Diem: %.2f\n", 
                   ds[i].masv, ds[i].hoten, ds[i].lop, ds[i].diem);//ki?m tra l?i th�ng tin trc khi c?p nh?t
            printf("Nhap ho ten moi (Enter de giu nguyen): ");//nh?p t�n 
            fflush(stdin);
            fgets(buffer, sizeof(buffer), stdin);//nh?p t�n m?i d�ng d�ng fgets �? tr�nh l?i tr�n b? nh? v� nh?n bi?t enter d? h�n
            if (buffer[0] != '\n') {//n?u buffer[0] th? s? gi? nguy�n t�n c?
                buffer[strcspn(buffer, "\n")] = 0; //x�a \n
                strcpy(ds[i].hoten, buffer);// c?p nh?t t�n m?i
            }
            printf("Nhap lop moi (Enter de giu nguyen): ");//nh?p l?p 
            fgets(buffer, sizeof(buffer), stdin);
            if (buffer[0] != '\n') {
                buffer[strcspn(buffer, "\n")] = 0;
                strcpy(ds[i].lop, buffer);
            }
            printf("Nhap diem moi (Enter de giu nguyen): ");//c?p nh?t �i?m
            fgets(buffer, sizeof(buffer), stdin);
            if (buffer[0] != '\n') {
                ds[i].diem = atof(buffer);  // chuy?n chu?i sang s? th?c
            }

            printf("Cap nhat thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien!\n");
}
void ghitep() {
	FILE *f = fopen("sinhvien.txt","w");
	if(f == NULL) {
		printf("Khong the mo tep de ghi");
		return;
}
	for (int i =0; i < danhap;i++) {
		fprintf(f,"%s|%s|%s|%s|%.2f\n",
					ds[i].masv,ds[i].hoten,ds[i].gioitinh,ds[i].lop,ds[i].diem);
		}
	fclose(f);
	printf("Da ghi du lieu vao file");
}
void doctep() {
    FILE *f = fopen("sinhvien.txt", "r");
    if (f == NULL) {
        printf("Khong tim thay tep, bat dau voi danh sach rong.\n");
        return;
    }
    danhap = 0;
    while (fscanf(f, "%9[^|]|%49[^|]|%49[^|]|%9[^|]|%f\n",
                  ds[danhap].masv, ds[danhap].hoten, ds[danhap].gioitinh, 
                  ds[danhap].lop, &ds[danhap].diem) == 5) {
        danhap++;;
        if (danhap >= max) break;
    }
    fclose(f);
    printf("Da doc du lieu tu tep, hien co %d sinh vien.\n", danhap);
}
void FindSV(sinhvien ds[],int danhap) {
	int choice;
	char key[50];
	int found = 0;
	printf("=====Tim Kiem Sinh Vien=====\n");
	printf("1.Tim kiem bang ma so sinh vien\n");
	printf("2.Tim kiem bang ho ten\n");
	printf("==============================\n");
	printf("Nhap lua chon: ");
	scanf("%d",&choice);
	getchar();
	if (choice == 1) {
		printf("Nhap ma so sinh vien can tim: ");
		gets(key);
		for (int i =0;i < danhap;i++) {
			if (strcmp(ds[i].masv,key) == 0) {
				printf("Da tim thay sinh vien !!!\n");
				printf("Ma SV: %s| HoTen: %s| GioiTinh: %s| Lop: %s| Diem: %.2f \n",
						ds[i].masv,ds[i].hoten,ds[i].gioitinh,ds[i].lop,ds[i].diem);
				
			}
		}
	}
}
int main() {
    int choice;
    doctep();
    do {
        printf("\n===== CHUONG TRINH QUAN LY SINH VIEN =====\n");
        printf("1. Them sinh vien\n");
        printf("2. Hien thi danh sach sinh vien\n");
        printf("3. Xoa sinh vien\n");
        printf("4. Cap nhat thong tin sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("0. Thoat\n");
        printf("==========================================\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                themsv();
                ghitep();
                break;
            case 2:
                hienthisv();
                break;
            case 3:
                xoasv();
                ghitep();
                break;
            case 4:
                capnhatsv();
                ghitep();
                break;
            case 5:
            	FindSV(ds,danhap);
            	ghitep();
            	break;
            	
            case 0:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le! Vui long nhap lai.\n");
        }
    } while(choice != 0);

    return 0;
}
