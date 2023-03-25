#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int number_of_client=0;
struct date today;
struct date last_enterd;
struct date{
   int month;
   int year;
};
struct client
{
    int account_number[16];
    int password;
    char name [10];
    char last_name[10];
    int money;
    int month;
    int year;
    int month_last_modified;
    int year_last_modified;
};
struct client all_clinent[20];
int make_four_digit_number(){
    int re=0;
    int i=0;
    srand(time(0));
    for(i=0;i<4;i++){
        re=re*10;
        re+=rand()%10;
    }
    return re;
}

int compare_accout_number(int account1[16],int account2[16]){
    int flag=1;
    for(int i=0;i<16;i++){
        if(account1[i]!=account2[i]){
            flag=0;
            break;
        }
    }
    return flag;
}

int is_account_unique(int account_number[16]){
    for(int i=0;i<number_of_client;i++){
        if(compare_accout_number(all_clinent[i].account_number,account_number)){
            return 0;
        }
    }
    return 1;
}
void make_account(){
    int i=number_of_client;
    printf("Enter yor name:");
    scanf("%s",&all_clinent[i].name);
    printf("Enter yor last name:");
    scanf("%s",&all_clinent[i].last_name);
    printf("Enter yor money:");
    int money;
    scanf("%d",&money);
    if(money<10){
        printf("minimum money for making account is 10");
        make_account();
    }
    all_clinent[i].money=money;
    while (1){  
    srand(time(0));
     for(int j=0;j<16;j++){
        all_clinent[i].account_number[j]=rand()%10;
     }
       if(is_account_unique( all_clinent[i].account_number)){
            break;
        }
    }
    
    for(int k=0;k<16;k++){
        if(k%4==0){
            printf("\n");
        }
        printf("%d",all_clinent[i].account_number[k]);
    }
    printf("\nthe password is:\n");
    all_clinent[i].password=make_four_digit_number();
    printf("%d\n", all_clinent[i].password);
    all_clinent[i].month=today.month;
    all_clinent[i].year=today.year+4;
    printf("%d/%d\n",all_clinent[i].year,all_clinent[i].month);
    number_of_client++;
    all_clinent[i].year_last_modified=today.year;
    all_clinent[i].month_last_modified=today.month;
    enterence();
}
int vlid_date(){
    if(today.month<0||today.month>12){
        return 0;
    }
    if(today.year<last_enterd.year){
        return 0;
    }
    if(today.year==last_enterd.year&&today.month<last_enterd.month){
        return 0;
    }
    last_enterd.month=today.month;
    last_enterd.year=today.year;
    return 1;
}
int get_date(){
    while (1)
    {
    printf("enter the month:\n");
    scanf("%d",&today.month);
    printf("enter the year:\n");
    scanf("%d",&today.year);
    if(vlid_date()){
        break;
    }
    }
}

struct client* find_client(int input[16]){
    for(int i=0;i<number_of_client;i++){
        if(compare_accout_number(input,all_clinent[i].account_number)){
            return (&all_clinent[i]);
            break;
        }
    }
    printf("not found!");
}

void see_money(struct client *Client){
    printf("%d\n",(*Client).money);
    banking_operation();
}
void add_money(struct client *Client){
    printf("Enter the money:\n");
    int money;
    scanf("%d",&money);
    int money2;
    money2=(*Client).money;
    money2+=money;
    (*Client).money=money2;
    banking_operation();
}
void take_money(struct client* Client){
    printf("Enter the money:\n");
    int money;
    scanf("%d",&money);
    if((*Client).money-money<10){
        printf("invlaid output!\n"); 
        take_money(Client);  
    }else{
        (*Client).money-=money;
    }
    banking_operation();
}
int check_money(struct client* Client,int money){
       if((*Client).money-money<10){
        return 1;  
    }else{
        return 0;
    }
    banking_operation();
}

int is_account_exist(int input[16]){
    for(int i=0;i<number_of_client;i++){
        if(compare_accout_number(input,all_clinent[i].account_number)){
            return 1;
        }
    }
    return 0;
}

void transfer_money(struct client* Client1){
    printf("Enter the destination account number:\n");
    char input[16];
    scanf("%s",&input);
    int account_number[16];
    for(int i=0;i<16;i++){
        int ascci=input[i];
        account_number[i]=ascci-48;
    }
    printf("Enter the money:\n");
    int money;
    scanf("%d",&money);
    if(!is_account_exist(account_number)){
        printf("wrong account number!");
        banking_operation();
    }
    printf("%s\n",(*find_client(account_number)).name);
    printf("1-continue:\n2-exit:\n");
    int operation;
    scanf("%d",&operation);
    if(operation==2){
        banking_operation();
    }
    if(operation!=1&&operation!=2){
        printf("invalid input");
        banking_operation();
    }
    if(!check_money(Client1,money)){
    (*Client1).money-=money;
    struct client* Client2=find_client(account_number);
    (*Client2).money+=money;
    }else{
        printf("there isn't enough money to transfer\n");
    }
    banking_operation();
}
void update_money(struct client* Client){
    int flag=0;
    int years=today.year-(*Client).year_last_modified;
    for(int i=0;i<years-1;i++){
        flag=1;
        int income=(*Client).money*12/100;
        (*Client).money+=income;
    }
    if(today.year==(*Client).year_last_modified||flag==1){
    if(!today.month==(*Client).year_last_modified){
    int income=(*Client).money*1/100;
    int months=(12-(*Client).month_last_modified)+today.month-1;
    (*Client).money+=income*months;
    (*Client).year_last_modified=today.year;
    (*Client).month_last_modified=today.month;}
    }
}
void update_account(struct client* Client){
    while (1)
    {
        if((*Client).year<today.year){
            (*Client).year+=4;
            (*Client).money-=1;
            printf("%d",(*Client).month);
            printf("%d",(*Client).year);
            break;
        }
        if((*Client).year==today.year&&(*Client).month<today.month){
            (*Client).year+=4;
            (*Client).money-=1;
            printf("%d",(*Client).month);
            printf("%d",(*Client).year);
            break;
        }
        break;
    }
    
}

void banking_operation(){
    printf("enter your account number:\n");
    char input[16];
    scanf("%s",&input);
    int account_number[16];
    for(int i=0;i<16;i++){
        int ascci=input[i];
        account_number[i]=ascci-48;
    }
    if(!is_account_exist(account_number)){
        printf("there is no account by this account number\n");
        banking_operation();
    }else{
    update_account(find_client(account_number));
    update_money(find_client(account_number));
    printf("choose your operation:\n1-take money\n2-add money\n3-see money\n4-transfer money\n5-exit:\n");
    int operation;
    scanf("%d",&operation);
    switch (operation)
    {
    case 1:
        take_money(find_client(account_number));
        break;
    case 2:
        add_money(find_client(account_number))  ;  
        break;
    case 3:
        see_money(find_client(account_number));
        break;
    case 4:
        transfer_money(find_client(account_number));
    case 5:
        enterence();
    }
    }
}
void enterence(){
    printf("1-make account:\n2-choose operantion:\n3-exit:\n");
    int operation;
    scanf("%d",&operation);
    if(operation==1||operation==2||operation==3){
        switch(operation){
            case 1:make_account();
                break;
            case 2:
                banking_operation();
                break;
            case 3:
                get_date();
                enterence();
        }
    }else{
        printf("invalid input!\n");
        enterence();
    }
}
int main(){
system("cls");
get_date();
enterence();
} 


