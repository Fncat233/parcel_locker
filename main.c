#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define p_id data.id
#define p_type data.type
#define p_state data.state
#define p_phone data.phone
#define p_number data.number

#define PERSON_HEAD printf("%-10s%-10s%-10s%-15s%-10s\n", "格口编号", "格口类型", "格口状态", "取件人号码", "取件码")
#define PERSON_DATA printf("%-10s%-10s%-10s%-15s%-10d\n", node->data.id, node->data.type, node->data.state, node->data.phone, node->data.number)
#define STRCMP_DATA ((strcmp(node->p_type, type) == 0 && strcmp(node->p_state, "EMPTY") == 0) || node->p_number == number)
#define STRCMP_LOGIN strcmp(name, "1111") == 0 && strcmp(password, "0000") == 0
#define SRAND srand((unsigned)time(NULL))
#define RANDOM rand() % 899999 + 100000
#define IsEmpty(x) (x->next == NULL)

typedef struct Person
{
    char *id;
    char *type;
    char *state;
    char *phone;
    int number;
} Person;

typedef Person Node_Data;

typedef struct node
{
    Node_Data data;
    struct node *next;
} list, *pointer;

//创建头结点
pointer InitList()
{
    pointer head = (pointer)malloc(sizeof(list));
    head->next = NULL;
    return head;
}

//创建结点
pointer CreateNode(char *id, char *type, char *state, char *phone, int number)
{
    pointer node = (pointer)malloc(sizeof(list));
    node->p_id = id;
    node->p_type = type;
    node->p_state = state;
    node->p_phone = phone;
    node->p_number = number;
    node->next = NULL;
    return node;
}

//插入数据
void InsertList(pointer list, char *id, char *type, char *state, char *phone, int number)
{
    pointer node = CreateNode(id, type, state, phone, number);
    node->next = list->next;
    list->next = node;
}

//打印数据
void PrintList(pointer list)
{
    if (IsEmpty(list))
    {
        printf("链表为空无法打印！\n");
        system("pause");
    }
    pointer node = list->next;
    PERSON_HEAD;
    while (node)
    {
        PERSON_DATA;
        node = node->next;
    }
}

//定位
pointer Locate(pointer list, char *type, int number)
{
    pointer node = list->next;
    while (node)
    {
        if (STRCMP_DATA)
            break;
        node = node->next;
    }
    return node;
}

//派送
void Send(pointer list)
{
    pointer node = (pointer)NULL;
    char *type = (char *)malloc(sizeof(char) * 20);
    char *phone = (char *)malloc(sizeof(char) * 20);
    fflush(stdin);
    printf("请输入需要的格口类型（L/M/S）:");
    gets(type);
    if (node = Locate(list, type, 1)) 
    {
        printf("请输入收件人手机号码:");
        gets(phone);
        node->p_phone = phone;
        SRAND;
        node->p_number = RANDOM;
        node->p_state = "FULL";
        printf("派送成功！\n");
    }
    else
        printf("此类型快递格已满！");
        return;
}

//取快递
void get(pointer list)
{
    pointer node = list->next;
    int number;
    printf("请输入取件码：");
    scanf("%d", &number);
    while (node)
    {
        if (node->p_number == number)
        {
            node->p_state = "EMPTY";
            node->p_phone = "";
            node->p_number = 0;
            break;
        }
        node = node->next;
    }
    printf(node ? "快递已取出！" : "取件码错误, 未找到该快递！");
}

//快递员登录
int Login()
{
    char *name = (char *)malloc(sizeof(char) * 20);
    char *password = (char *)malloc(sizeof(char) * 20);
    fflush(stdin);
    printf("请输入用户名：");
    gets(name);
    printf("请输入密码：");
    gets(password);
    if (STRCMP_LOGIN)
        return 1;
    else
        return 0;
}
//主界面
void Sshow()
{
    printf("\n");
    printf("\t\t----------功能选项----------\n");
    printf("\t\t|       1.快递员登陆        |\n");
    printf("\t\t|       2.取快递            |\n");
    printf("\t\t|       0.退出              |\n");
    printf("\t\t----------------------------\n");
    printf("请输入0-2：");
}

//快递员界面S
void Tshow(pointer list)
{
    int in = 1;
    int option = 0;
    while (in)
    {
        fflush(stdin);
        printf("\n");
        printf("\t\t----------功能选项----------\n");
        printf("\t\t|       1.查看格口          |\n");
        printf("\t\t|       2.派送快递          |\n");
        printf("\t\t|       0.返回上一层        |\n");
        printf("\t\t----------------------------\n");
        printf("请输入0-2：");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            PrintList(list);
            break;
        case 2:
            Send(list);
            break;
        case 0:
            in = 0;
            break;
        default:
            printf("输入错误，请输入0-2！");
            break;
        }
    }
}

int main()
{
    pointer singleList = InitList();
    int in = 1;
    int option = 0;
    InsertList(singleList, "SIXTH", "L", "FULL", "13126004545", 147369);
    InsertList(singleList, "FIFTH", "L", "FULL", "15641631130", 156489);
    InsertList(singleList, "FOURTH", "M", "EMPTY", "", 0);
    InsertList(singleList, "THIRD", "M", "EMPTY", "", 0);
    InsertList(singleList, "SECOND", "S", "FULL", "13126005656", 123456);
    InsertList(singleList, "FIRST", "S", "EMPTY", "", 0);

    while (in)
    {
        Sshow();
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            if (Login())
            {
                printf("登录成功");
                Tshow(singleList);
            }
            else
                printf("登录失败");
            break;
        case 2:
            get(singleList);
            break;
        case 0:
            in = 0;
            break;
        default:
            printf("输入错误，请输入0-2");
            break;
        }
    }

    free(singleList);
    system("pause");
    return 0;
}
