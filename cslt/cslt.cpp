#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

using namespace std;

struct STAFF {
    char id[10];
    char fullname[100];
    short sex;
    float salary;
    char DoB[15];
};

int getStaff(FILE*, STAFF&);

int getAllStaff(FILE*, STAFF*);

void outputStaff(FILE*, STAFF);

void outputAllStaff(FILE* , STAFF*, int);

STAFF longest_name_highest_salary(STAFF*, int);

int getStaff(FILE* fI, STAFF& staff) {
    char gender[10];

    if (fscanf(fI, "%[^-]-%[^-]-%[^-]-%f-%s\n", staff.id, staff.fullname, gender, &staff.salary, staff.DoB) == 5) {
        if (strcmp(gender, "nam") == 0)
            staff.sex = 1;
        else
            staff.sex = 0;

        return 1;
    }
    return 0;
}

int getAllStaff(FILE* fI, STAFF* staff) {
    int n = 0;
    while (getStaff(fI, staff[n])) {
        n++;
    }
    return n;
}

void outputStaff(FILE* fO, STAFF s) {
    char nam[] = "nam";
    char nu[] = "nu";
    fprintf(fO, "%s-%s-%s-%.1f-%s\n", s.id, s.fullname, (s.sex ? nam : nu), s.salary, s.DoB);
}

void outputAllStaff(FILE* fO, STAFF* staff, int n) {
    for (int i = 0; i < n; i++) {
        outputStaff(fO, staff[i]);
    }
}

STAFF longest_name_highest_salary(STAFF* staff, int n) {
    int max_name_length = -1;
    float max_salary = -1.0f;
    STAFF result;
    for (int i = 0; i < n; i++) {
        int name_length = (int)strlen(staff[i].fullname);
        if (name_length > max_name_length) {
            max_name_length = name_length;
            max_salary = staff[i].salary;
            result = staff[i];
        } else if (name_length == max_name_length) {
            if (staff[i].salary > max_salary) {
                max_salary = staff[i].salary;
                result = staff[i];
            }
        }
    }
    return result;
}

int main() {
    FILE* fI = fopen("INPUT.TXT", "r");
    if (fI == NULL) {
        printf("Error: Could not open INPUT.TXT\n");
        return 1;
    }

    STAFF staff[100];
    int n = getAllStaff(fI, staff);
    fclose(fI);

    outputAllStaff(stdout, staff, n);

    FILE* fO = fopen("OUTPUT.TXT", "w");
    if (fO == NULL) {
        printf("Error: Could not open OUTPUT.TXT\n");
        return 1;
    }
    outputStaff(fO, longest_name_highest_salary(staff, n));
    fclose(fO);

    return 0;
}