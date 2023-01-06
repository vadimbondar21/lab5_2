#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//=======================================================================================
//Прототипи
double func(double x);
int files(double x, int N, double delta,char group_name[6], char student_name[13]);
void print_binary(char  group_name[6], char student_name[13]);

//=======================================================================================
//Тіло функції
int main()
{
    char  group_name[6]={0}, student_name[13]={0};
    double x1, x2, delta;
    int N;
    FILE* fp_input = fopen ("Input.txt", "r");//відкриваємо вхідний файл
    if (fp_input==NULL)
    {
        printf("Error! File cannot be opened");//не  можемо відкрити файл
    }
    else
    {
        fscanf(fp_input, "%lf %lf %d %lf %s %s", &x1, &x2, &N, &delta, group_name, student_name);
        fclose(fp_input);
        if(N==0)
        {
            N = ((x2 - x1) / delta) + 1;
        }
        else if( delta!=((x2 - x1) / (N - 1)))
        {
            delta = (x2 - x1) / (N - 1);
        }
        int checking=0;
        checking=files(x1,N,delta, group_name,student_name);
        if(checking==1)
        {
            print_binary( group_name,student_name);
        }
    }




    return(0);
}
//==========================================================================================================
//Реалізація
double func(double x)
{
    return pow(x,3)/30-4*pow(x,2)+50;//повертаємо це значення в функцію
}
//створюємо та записуємо інформацію в текстову таблицю та бінарний файл
int files(double x, int N, double delta,char  group_name[6], char student_name[13])
{
    FILE* input_table = fopen ("OutputTable.txt", "w");
    FILE* bina = fopen ("OutBinary.bin", "w+b");
    if (input_table==NULL || bina==NULL)
    {
        printf("Error! File cannot be opened");//не можемо відкрити файл
        return(0);
    }
    else
    {
        fwrite(&N, sizeof(int), 1, bina);
        fprintf(input_table, "N\tx\tf(x)\n");
        for(int i=0;i<N;i++)
        {
            fprintf(input_table,"%2d\t",i+1);
            fprintf(input_table,"%.2lf\t",x);
            fprintf(input_table,"%.2lf\n",func(x));

            //---------------------------------
            fwrite(&x, sizeof(double), 1, bina);
            double b;
            b=func(x);
            fwrite(&b,sizeof(double),1, bina);
            x+=delta;
        }
        fprintf(input_table, "%s", group_name);
        fprintf(input_table, "\n%s",student_name);
        free(group_name);
        free(student_name);
        fclose(input_table);
        fclose(bina);
        return(1);
    }
}
//читаємо та відображаємо значення з бінарного файлу
void print_binary(char  group_name[6],char student_name[13])
{
    int N=0;
    double Num=0;
    FILE* bina = fopen("OutBinary.bin", "r+b");
    if (bina==NULL)
    {
         printf("Error, the binary file don't exist");//Помилка, бінарний файл не існує
    }
    else//виводимо інформацію з бінарного файлу на екран
    {
    printf("\n****************************");
    printf("\n*  N   *   X    *   F(X)   *");
    printf("\n****************************\n");
        fread(&N, sizeof(int), 1, bina);
        for(int i=0; i<N; i++)
        {
            printf("%2d\t|",i+1);
            fread(&Num, sizeof(double), 1, bina);
            printf("%.2lf\t|", Num);
            fread(&Num, sizeof(double), 1, bina);
            printf("%.2lf", Num);
            printf("\n");
        }
        printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
        printf("%s",group_name);
        printf("\n%s",student_name);
        free(group_name);
        free(student_name);
        fclose(bina);
    }
}
