#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct complex_node{
	float real;
	float image;
	char name[30];
	struct complex_node * next=NULL;
} complex;

//函数声明
complex find_complexexisted(char * name);
bool Creatcomplex(float real, float image, char * name);
void addcomplex(complex one, complex two);
void subcomplex(complex one, complex two);
void dividcomplex(complex one, complex two);
bool cutcomplexnode(char * name);
bool freecomplex(void);
void multicomplex_print(complex one, complex two);


float real_, image_;
//指向头节点的指针
complex * header = NULL;
//指向尾节点的指针
complex * last = NULL;
//暂时存储name的指针
complex notfind; 


int main(void)
{
	char getname[30];
	char command;
	bool condition = true;
	printf("Please choose an order: \nyou can create a new complex with C\n"
		"       delete a original complex with D\n"
		"       add two complexs with A\n"
		"       sub two conplexs with S\n"
		"       multi two conplexs with M\n"
		"       divide two conplexs with I\n"
		"       clear all data with R\n"
		"       quit with Q\n");
	while (condition)
	{
		scanf("%c", &command);
		if (command == 'Q')
			break;
		switch (command)
		{
		case 'C': {
			fputs("please input the real part and the image part by order.\n", stdout);
			scanf("%f %f", &real_, &image_);
			printf("\nwhat do you want to use to store it?\n");//获取名字
			scanf("%s", getname);
			if (Creatcomplex(real_, image_, getname) == true)
				printf("you create a complex named %s successful", getname);
			break;

		}
		case 'A': {
			printf("please input two complex's name that you have defined before.");
			char inputname[2][30];
			complex num1, num2;
			scanf("%s%s", inputname[0], inputname[1]);
			num1 = find_complexexisted(inputname[0]);
			num2 = find_complexexisted(inputname[1]);
			addcomplex(num1, num2);
		} break;

		case 'S': {
			printf("please input two complex's name that you have defined before.");
			char inputname[2][30];
			complex num1, num2;
			scanf("%s%s", inputname[0], inputname[1]);
			num1 = find_complexexisted(inputname[0]);
			num2 = find_complexexisted(inputname[1]);
			subcomplex(num1, num2);
		} break;
		case 'M': {
			printf("please input two complex's name that you have defined before.");
			char inputname[2][30];
			complex num1, num2;
			scanf("%s%s", inputname[0], inputname[1]);
			num1 = find_complexexisted(inputname[0]);
			num2 = find_complexexisted(inputname[1]);
			multicomplex_print(num1, num2);
		} break;
		case 'I': {
			printf("please input two complex's name that you have defined before.");
			char inputname[2][30];
			complex num1, num2;
			scanf("%s%s", inputname[0], inputname[1]);
			num1 = find_complexexisted(inputname[0]);
			num2 = find_complexexisted(inputname[1]);
			dividcomplex(num1, num2);
		} break;
		case 'D': {
			printf("please input the complex's name that you want to delete");
			complex num1;
			scanf("%s", getname);
			cutcomplexnode(getname);
		} break;
		case 'R': {
			freecomplex();
		} break;
		}
		printf("the next order:");
	}
}


complex find_complexexisted(char * name)
{
	complex * find = header;
	
		for (int i = 0; i < 30||(find->name)[i]=='\0'&&name[i]=='\0'; i++)
		{
			if ((find->name)[i] != name[i])
				find = find->next;
		}
		return *find;

}


bool Creatcomplex(float real, float image,char * name)
{
	complex * point;
	point = (complex*)malloc(sizeof(complex));
	point->real = real;
	point->image = image;
	for(int i =0;i<30;i++)
	(point->name)[i] = name[i];
	if (header == NULL)
	{
		header = point;
		last = point;
	}
	else
	{
		last->next = point;
		last = point;
	}
	return true;
		

}
void printresult(complex result)
{
	printf("the result is: ");
	if (result.image > 0)
		printf("%.2f + %.2fi", result.real, result.image);
	else if (result.image = 0)
		printf("%.2f", result.real);
	else
		printf("%.2f - %.2fi", result.real, -result.image);
}
void addcomplex(complex one, complex two)
{
	complex result;
	result.real = one.real + two.real;
	result.image = one.image + two.image;
	printresult(result);

}
void subcomplex(complex one, complex two)
{
	two.real = -two.real;
	two.image = -two.image;
	addcomplex(one, two);
}
complex multicomplex(complex one, complex two)
{
	complex result;
	result.real = one.real*two.real + (-one.image * two.image);
	result.image = one.real*two.image + one.image* two.real;
	return result;

}
void multicomplex_print(complex one, complex two)
{
	complex result;
	result.real = one.real*two.real + (-one.image * two.image);
	result.image = one.real*two.image + one.image* two.real;
	printresult(result);

}
void dividcomplex(complex one, complex two)
{
	complex result, _two;
	_two = two;
	_two.image = -two.image;
	result.real = multicomplex(one, _two).real / multicomplex(two, _two).real;
	result.image = multicomplex(one, _two).image / multicomplex(two, _two).real;
	printresult(result);
}
bool cutcomplexnode(char * name)
{
	complex * cut;
	cut = &find_complexexisted(name);
	complex * find = header;
	while (find->next != cut)
	{
		find = find->next;
	}
	find->next = cut->next;
	free(cut);
	printf("you delete the complex successfully");
	return true;
}

bool freecomplex(void)
{
	if (header != NULL)
	{

		for (complex * line = header;header != last;header=header->next)
		{
			line = header;
			free(line);
		}
		free(header);
		return true;
	}
	else return false;
	
}