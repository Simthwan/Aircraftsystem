#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define LEN 14
#define SEATS 12

typedef struct
{
	int seat_id;
	bool status;
	char last[LEN];
	char first[LEN];
} plane;

void init(plane *pl, plane *ps[]);
int show_airline_menu(void);
int get_first(void);
void airline(int choice, plane *pl, plane *ps[]);
int getmenu(int choice);
int openings(const plane pl[], int n);
void show_empty_seats(const plane pl[], int n);
void makelist(const plane pl[], char *str, int kind);
void list_assign(plane *ps[], int n);
void sort(plane *array[], int n);
void assign_seat(plane pl[], int n);
char *s_gets(char *st, int n);
void delete_seat(plane pl[], int n);
void show_seats(const plane pl[]);
void confirm_seat(const plane pl[]);
void eatline(void);

int main(void)
{
	int ch;
	plane airline_102[SEATS];
	plane airline_311[SEATS];
	plane airline_444[SEATS];
	plane airline_519[SEATS];
	plane *ps_102[SEATS];
	plane *ps_311[SEATS];
	plane *ps_444[SEATS];
	plane *ps_519[SEATS];

	init(airline_102, ps_102); //初始化座位的状态以及指针的指向
	init(airline_311, ps_311);
	init(airline_444, ps_444);
	init(airline_519, ps_519);
	while ((ch = show_airline_menu()) != 'q') {
		putchar('\n');
		switch (ch) {
		case 'a': {
			airline(ch, airline_102, ps_102);
			break;
		}
		case 'b': {
			airline(ch, airline_311, ps_311);
			break;
		}
		case 'c': {
			airline(ch, airline_444, ps_444);
			break;
		}
		case 'd': {
			airline(ch, airline_519, ps_519);
			break;
		}
		}
		putchar('\n');
	}
	puts("Bye from Colossus Airlines!");
	return 0;
}

void init(plane *pl, plane *ps[]) //初始话结构体的值
{
	int i;
	for (i = 0; i < SEATS; i++) {
		ps[i] = &pl[i];
	}
	for (i = 0; i < SEATS; i++) {
		pl[i].status = false;
		pl[i].seat_id = i + 1;
	}
}

int show_airline_menu(void)
{
	int ch;
	puts("There are some airlines for you to choose.");
	puts("a) Airline 102.");
	puts("b) Airline 311.");
	puts("c) Airline 444.");
	puts("d) Airline 519.");
	puts("q) Quit the program.");
	printf("Please you enter to choose: ");
	ch = get_first();
	while (strchr("abcdq", ch) == NULL) {
		printf("Please enter a, b, c, d or q:");
		ch = get_first();
	}
	return ch;
}

int get_first(void)
{
	int ch;
	do {
		ch = tolower(getchar());
	} while (isspace(ch)); //跳过开头空格
	eatline(); //清行；清理输入最后的换行符

	return ch;
}

void airline(int choice, plane *pl, plane *ps[])
{
	int ch;
	while ((ch = getmenu(choice)) != 'f') {
		switch (ch)
		{
		case 'a': {
			printf("There are %d empty seats.\n", openings(pl , SEATS));
			break;
		}
		case 'b': {
			show_empty_seats(pl, SEATS);
			break;
		}
		case 'c': {
			list_assign(ps, SEATS);
			break;
		}
		case 'd': {
			assign_seat(pl, SEATS);
			break;
		}
		case 'e': {
			delete_seat(pl, SEATS);
			break;
		}
		case 'g': {
			confirm_seat(pl);
		}
		}
		putchar('\n');
	}
}

int getmenu(int choice)
{
	int ch;
	if (choice == 'a') {
		printf("The airline 102 is being processed.\n");
	}
	else if (choice == 'b') {
		printf("The airline 311 is being processed.\n");
	}
	else if (choice == 'c') {
		printf("The airline 444 is being processed.\n");
	}
	else if (choice == 'd') {
		printf("The airline 519 is being processed.\n");
	}
	puts("To choose a function,enter its letter label:");
	puts("a) Show number of empty seats");
	puts("b) Show list of empty seats");
	puts("c) Show alphabetical list of seat");
	puts("d) Assign a customer to a seat");
	puts("e) Delete a seat assignment");
	puts("f) Quit");
	puts("g) Confirm seat assignment");
	printf("Please you enter to choose:");
	while (ch = get_first(), strchr("abcdefg", ch) == NULL) { //判断ch是否在abcdefg当中
		printf("Please enter a,b,c,d,e,f or g: ");
	}
	//ch=get_first();
	//if(strchr("abcdef", ch)== NULL){
	//printf("Invalid data! Please you choose again: ");} 之所以用while循环可以保证第二次输错时也能得到提醒
	return ch;
}

int openings(const plane pl[], int n) //显示空座位的数量;
{
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (pl[i].status == false) {
			count++;
		}
	}
	return count;
}

void show_empty_seats(const plane pl[], int n) //显示空座位信息;
{
	char seating[3 * SEATS];
	if (openings(pl, n) == 0) {
		puts("All seats are assigned");
	}
	else {
		makelist(pl, seating, false);
		printf("The following seats are available: ");
		puts(seating);
	}
}

void makelist(const plane pl[], char *str, int kind) //为分配和删除座位提供当前处理的座位数
{
	int seat;
	char temp[LEN];

	*str = '\0'; //清空str中的内容;
	for (seat = 0; seat < SEATS; seat++) {
		if (pl[seat].status == kind) {
			sprintf(temp, "%d ", pl[seat].seat_id); //将seat_id存入temp中
			strcat(str, temp);//将temp中的seat_id追加到str中
		}
	}
}

void list_assign(plane *ps[], int n) //显示按照字母序列排序后的座位表;
{
	int i;
	if (openings(*ps, n) == SEATS) {
		puts("All seats are empty.");
	}
	else {
		sort(ps, n);
		for (i = 0; i < SEATS; i++) {
			if (ps[i]->status == true) {
				printf("Seat %d: %s,%s\n", ps[i]->seat_id, ps[i]->last, ps[i]->first);
			}
		}
	}
}

void sort(plane *array[], int n) //按照ASCII码进行座位排序；传入为二级指针
{
	int i, j;
	plane *temp;
	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - 1 - i; j++) {
			if (strcmp(array[j + 1]->last, array[j]->last) < 0) {
				temp = array[j + 1];
				array[j + 1] = array[j];
				array[j] = temp;
			}
		}
	}
}

void assign_seat(plane pl[], int n)  //分配空余座位
{
	int ch, seat, flag;
	char list[3 * SEATS];
	if (openings(pl, n) == false) {
		puts("All seats are assigned.Can't assign again!");
	}
	else {
		makelist(pl, list, false);
		printf("Available seats: %s\n", list);
		printf("Which seat do you want? Please you enter from the lists:");
		do {
			while (scanf_s("%d", &seat) != 1) {
				eatline();
				printf("Seats: %s\n", list);
				printf("Enter a number from the lists: ");
			}
			if (seat<1 || seat>SEATS || pl[seat - 1].status == true) {
				printf("Seats: %s\n", list);
				printf("Enter a number from the lists: ");
				flag = 1;
			}
			else {
				flag = 0;
			}
		} while (flag == 1); //本循环判断并处理用户的错误输入
		eatline();
		puts("Enter first name:");
		s_gets(pl[seat - 1].first, LEN);
		puts("Enter last name:");
		s_gets(pl[seat - 1].last, LEN);
		printf("%s %s assigned to seat %d.\n", pl[seat - 1].first, pl[seat - 1].last, seat);

		printf("Enter a to accept assigment,c to cancel it:");
		ch = get_first();
		while (strchr("ac", ch) == NULL) {
			printf("Please enter a or c:");
			ch = get_first();
		}
		if (ch == 'a') {
			pl[seat - 1].status = true;
			puts("Passenger assigned to seat.");
		}
		else if (ch == 'c') {
			puts("Passenger not assigned.");
		}
	}
}

char *s_gets(char *st, int n)
{
	char *ret_val;
	char *find;

	ret_val = fgets(st, n, stdin);
	if (ret_val) {
		find = strchr(st, '\n');
		if (find) {
			*find = '\0';
		}
		else {
			while (getchar() != '\n')
				continue;
		}
	}
	return ret_val;
}

void delete_seat(plane pl[], int n) //删除已分配的座位;
{
	int ch, seat, flag;
	char list[3 * SEATS];

	if (openings(pl, n) == SEATS)
	{
		puts("All seats already are empty. Can't delete!");
	}
	else {
		show_seats(pl);
		makelist(pl, list, true);
		printf("Enter the number of the seat to be deleted: ");
		do {
			while (scanf_s("%d", &seat) != 1) {
				eatline();
				printf("Seats: %s\n", list);
				printf("Enter a number from the lists:");
			}
			if (seat<1 || seat>SEATS || pl[seat - 1].status == false) {
				printf("Seats:%s\n", list);
				printf("Enter a number from this list:");
				flag = 1;
			}
			else {
				flag = 0;
			}
		} while (flag == 1); //防止乱输入
		eatline();
		printf("%s %s to be canceled for seat %d.\n", pl[seat - 1].first, pl[seat - 1].last, seat);
		printf("Enter d to delete assignment,a to abort: ");
		ch = get_first();
		while (strchr("da", ch) == NULL) {
			printf("Please enter d or a: ");
			ch = get_first();
		}
		if (ch == 'd') {
			pl[seat - 1].status = false;
			puts("Passenger dropped.");
		}
		else if (ch == 'a') {
			puts("Passenger retained.");
		}
	}
}

void show_seats(const plane pl[]) //显示已分配的座位;
{
	int i;

	puts("Seats currently taken:");
	for (i = 0; i < SEATS; i++) {
		if (pl[i].status == true) {
			printf("Seat %d:%s,%s\n", pl[i].seat_id, pl[i].last, pl[i].first);
		}
	}
}

void confirm_seat(const plane pl[]) //确认座位分配;
{
	int i;
	puts("Seats assignment lists:");
	for (i = 0; i < SEATS; i++) {
		if (pl[i].status == true) {
			printf("Seat %-2d: assigned.\n", pl[i].seat_id);
		}
		else {
			printf("Seat %-2d: unassigned.\n", pl[i].seat_id);
		}
	}
}

void eatline(void)
{
	while (getchar() != '\n')
		continue;
}