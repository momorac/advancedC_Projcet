#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COUNT 100 // 최대 저장될 수 있는 연락처 개수 정의
int num_info = 0;     // 현재 저장된 연락처 개수 저장할 변수

typedef struct contact_info
{
    char name[21];         // 이름 : 널문자 제외 최대 20byte - 중복 불허
    char phone_number[16]; // 전화번호 : 하이픈 제외 최대 15byte
    char birth[9];         // 생일 : YYYYMMDD 8byte
} INFO;

// 1 : 각 사람 정보 등록하기 (매개변수 : 정보를 저장할 구조체 배열 주소)
void regist_info(INFO *infos);

// 2 : 등록된 전체 사람 정보 보여주기
void show_all(INFO *infos);

// 3 : 이름으로 연락처 검색해서 삭제하기
void delete_info(INFO *infos);

// 4 : 특정 Month 입력받아 해당하는 달에 태어난 사람 보여주기
void find_by_birth(INFO *infos);

// 저장된 연락처 정보들 사전순서로 정렬
void sort_infos(INFO *infos);

// 메뉴 인터페이스 출력
void print_menu();

/*
 * Interface - Menu (in console)
 * -----------------
 * 1. Registration
 * 2. ShowAll
 * 3. Delete
 * 4. FindByBirth
 * 5. Exit
 * -----------------
 *  -> 5가 입력되기 전까지 반복
 */

int main(int argc, char const *argv[])
{
    // 연락처 정보 저장할 구조체 infos 배열 선언 및 동적할당
    INFO *infos = NULL;
    infos = (INFO *)malloc(num_info * sizeof(INFO));

    int input;   // 사용자에게 메뉴 입력받을 변수
    int run = 1; // while문에서 반복 제어할 변수

    while (run)
    {
        print_menu();
        scanf("%d", &input);

        switch (input)
        {
        case 1:
            // 최대저장개수 초과 시
            if (num_info >= MAX_COUNT)
            {
                printf("OVERFLOW\n");
                break;
            }
            // 저장 가능 시
            getchar();
            num_info++;
            infos = (INFO *)realloc(infos, num_info * sizeof(INFO)); // 메모리 추가로 동적할당받기
            regist_info(infos);
            break;

        case 2:
            show_all(infos);
            break;
        case 3:
            if (num_info == 0)
                printf("NO MEMBER\n");
            else
                delete_info(infos);
            break;
        case 4:
            find_by_birth(infos);
            break;
        case 5:
            run = 0;
            break;
        }
    }

    return 0;
}

void regist_info(INFO *infos)
{
    char tmp[21]; // 문자열 입력받을 버퍼
    INFO *p = infos + num_info - 1;

    // 이름 입력받아 저장하기
    printf("Name:");
    scanf("%s", tmp);
    strcpy(p->name, tmp);
    getchar();

    // 전화번호 입력받아 저장하기
    printf("Phone_number:");
    scanf("%s", tmp);
    strcpy(p->phone_number, tmp);
    getchar();

    // 생년월일 입력받아 저장하기
    printf("Birth:");
    scanf("%s", tmp);
    strcpy(p->birth, tmp);
    getchar();

    sort_infos(infos);
    printf("<<%d>>\n", num_info);
}
void show_all(INFO *infos)
{
    for (int i = 0; i < num_info; i++)
        printf("%s %s %s\n", infos[i].name, infos[i].phone_number, infos[i].birth);
}
void delete_info(INFO *infos)
{
    printf("Name:");
    char tmp[21];
    scanf("%s", tmp);

    for (int i = 0; i < num_info; i++)
    {
        if (strcmp(tmp, infos[i].name) == 0)
        {
            num_info--;
            for (int j = i; j < num_info; j++)
                infos[j] = infos[j + 1];
            infos = (INFO *)realloc(infos, num_info * sizeof(INFO));
        }
    }
}
void find_by_birth(INFO *infos)
{
    printf("Birth:");
    int birth;
    scanf("%d", &birth);
    // 태어난 달을 정수로 입력받아서 두 자리 문자열로 맞추어 파싱하기

    char tmp[3];
    if (birth < 10)
    {
        tmp[0] = '0';
        tmp[1] = '0' + birth;
        tmp[2] = '\0';
    }
    else
    {
        tmp[0] = '0' + (birth / 10);
        tmp[1] = '0' + (birth % 10);
        tmp[2] = '\0';
    }

    for (int i = 0; i < num_info; i++)
    {
        if (strncmp(tmp, (infos[i].birth) + 4, 2) == 0)
            printf("%s %s %s\n", infos[i].name, infos[i].phone_number, infos[i].birth);
    }
}

void sort_infos(INFO *infos)
{
    for (int i = 0; i < num_info - 1; i++)
    {
        for (int j = i + 1; j < num_info; j++)
        {
            if (strcmp(infos[j].name, infos[i].name) < 0)
            {
                INFO tmpinfo = infos[i];
                infos[i] = infos[j];
                infos[j] = tmpinfo;
            }
        }
    }
}

void print_menu()
{
    printf("*****Menu*****\n");
    printf("<1.Registration><2.ShowAll><3.Delete><4.FindByBirth><5.Exit>\n");
    printf("Enter_the_menu_number:");
}