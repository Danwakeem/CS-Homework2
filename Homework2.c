/*****************
Name: Dan Jarvis
Class: CSCE 1040
Date: 09/23/2013
*****************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "stack.h"

void popTable(int **table, char *exp, int *rowNum, char *caps)
{
   int i, state;
   int check;
   int fin, ini, tmp, tmp2;
   int fin2, ini2;


   for(i = 0; i < strlen(exp); i++)
   {
       if(isupper(exp[i]) != 0)
       {
          for(check = 0; check < strlen(caps); check++)
          {
	     if(exp[i] == caps[check])
             {
	        table[state][check] = state + 1;
                push(state++);
                push(state++);
             }
           }
       } 
       else
       {
          switch(exp[i])
          {
             case ';' :
                fin = pop();
                tmp = pop();
                tmp2 = pop();
                table[tmp2][strlen(caps)] = tmp;
	        ini = pop();
	        push(ini);
                push(fin);
                break;
             case '*' : 
                fin = pop();
	        ini2 = state;
	        fin2 = ini2 + 1;
	        ini = pop();
	        table[ini2][strlen(caps)] = ini;
	        table[ini2][strlen(caps) + 1] = fin2;
	        table[fin][strlen(caps)] = ini;
	        table[fin][strlen(caps) + 1] = fin2;
	        push(ini2);
	        push(fin2);
		state = state + 2;
                break;
             case '+' :
	        fin = pop();
	        ini2 = state;
	        fin2 = ini2 + 1;
	        ini = pop();
	        tmp2 = pop();
	        tmp = pop();
	        table[ini2][strlen(caps)] = ini;
	        table[ini2][strlen(caps) + 1] = tmp;
	        table[fin][strlen(caps)] = fin2;
   	        table[tmp2][strlen(caps)] = fin2;
		push(ini2);
		push(fin2);
		state = state + 2;
	        break;
          }
      }
   }

}
/**********************************************************************/
/**********************************************************************/
void onlyRegExp(char* buff)
{
   int i, j = 0;
   char isReg[60+1];
   char check;
   char rev[100+1];

   for(i = 0; i < strlen(buff); i++)
      pushChar(buff[i]);

   for(i = 0; i < strlen(buff); i++)
   {
      check = popChar();
      if (isupper(check) != 0)
         isReg[j++] = check;
      else
      {
         switch(check)
         {
	  case '*': isReg[j++] = check; break;
	  case '+': isReg[j++] = check; break;
	  case ';': isReg[j++] = check; break;
         }
      }
   }
   j = strlen(isReg);
   rev[j--] = '\0';

   for(i = 0; i < strlen(isReg); i++)
      rev[j--] = isReg[i];

   memset(buff, '\0', sizeof(buff));
   strcpy(buff,rev);
}

/**********************************************************************/
/**********************************************************************/
char* ridSpaces(char *buff)
{
   int i, j = 0;
   char noSpace[300+1];   

   memset(noSpace, '\0', sizeof(noSpace));

   for(i = 0; i < strlen(buff); i++)
   {
      //checks to see if there is a space
      if(isspace(buff[j]) == 0)
         noSpace[i] = buff[j];
      else
      {
         //moves to the next space
         while(isspace(buff[j]) != 0)
            j++;
         noSpace[i] = buff[j];
      }
      j++;

   }
   //copy the new string with no spaces to buff to be passed back to the original function
   //even though it is a pointer
   memset(buff, '\0', sizeof(buff));
   strcpy(buff,noSpace);
 
   return buff;
}

/***********************************************************************/
/***********************************************************************/
char* getCaps(char *exp, char *tmp)
{
   int i, j = 0;
   char up[300+1];
   int check = 0, newPos = 1;
   char new[100+1];

   memset(up, '\0', sizeof(up));

   //This loop finds all of the upper case numbers and puts them into one string
   for(i = 0; i < strlen(exp); i++)
   {
      if(isupper(exp[j]) != 0)
         up[i] = exp[j];
      else
      {
         while(isupper(exp[j]) == 0 && exp[j] != '\0')
            j++;

         up[i] = exp[j];
      }
      j++;
   }

   //sets the first char of new to the same as the first char in up
   new[0] = up[0];

   //Figures out if there are duplicates of the letters
   for(i = 0; i < strlen(up); i++)
   {
      for(j = 0; j < strlen(new); j++)
      {
         if(up[i] != new[j])
	    check = 0;
         else 
	 { 
	    check = 1;
	    break;
         }
      }
      if(check != 1)
      {
         new[newPos] = up[i];
         check = 0;
         newPos++;
      }
   }
   //returns tmp which contains the first instance of every capital letter
   strcpy(tmp, new);

   return tmp;
}

/***********************************************************************/
/***********************************************************************/
void printHeader(char *tmp)
{
   int i, j;

   printf("\n\n");
   printf("Sat#|");
   for(i = 0; i < strlen(tmp); i++)
      printf("%2c|" ,tmp[i]);
   printf(" E| E| E|\n");
}
/***********************************************************************/
/***********************************************************************/
int main()
{
   char buff[300+1];
   char expression[300+1];
   char tmp[300+1];
   int i = 0, j;
   int **nfaTable;
   int rowNum = 0;
   int columns;
   int c;
   
   //Repats for five strings entered by the user
   while (i < 5)
   {
      printf("Please input a string: \n");
      fgets(buff, sizeof(buff), stdin);
      //trimming the new line off the end of fgets because it is included
      buff[strlen(buff) - 1] = '\0';

      //calls function to get rid of spaces
      strcpy(tmp,ridSpaces(buff)); 

      onlyRegExp(tmp);

      //cpy replaces what is in expression while cat adds the string on to the end
      if(i == 0)
         strcpy(expression,tmp);
      else
         strcat(expression,tmp);

      //resetting buff to NULL that way I don't have any issues when the program loops back around
      memset(buff, '\0', sizeof(buff));
      i++;

   }
   //Get the first instance of the capital letters
   memset(tmp, '\0', sizeof(tmp));
   getCaps(expression, tmp);

   //printing the results
   printf("\n%s\n\n" ,tmp);
   printf("%s\n" ,expression);

   //determining column size and a start for row size
   rowNum = strlen(tmp) * 2;
   columns = strlen(tmp) + 3;

   //determining the rest of the row size
   for(i = 0; i < strlen(expression); i++)
   {
      switch(expression[i])
      {
         case '*' : rowNum = rowNum + 2; break;
         case '+' : rowNum = rowNum + 2; break;
      }
   }   

   //allocating memory for the nubmer of rows
   nfaTable = malloc(rowNum * sizeof(int *));

   //allocating memory for columns in each row
   for(i = 0; i < rowNum; i++)
      nfaTable[i] = malloc(columns * sizeof(int));

   //initializing each element in the 2D array
   for(i = 0; i < rowNum; i++)
   {
      for(j = 0; j < columns; j++)
         nfaTable[i][j] = 0;
   }

   //populating the nfaTable
   popTable(nfaTable, expression, &rowNum, tmp);

   //I dont know why but I just wanted to give the columns a smaller name (c)
   c = strlen(tmp) + 3; 

   //printing out the nfaTable
   printHeader(tmp);
   for(i = 0; i < rowNum; i++)
   {
      for(j = 0; j < c; j++)
      {
         if(j == 0)
	    printf("%3d %3d", i ,nfaTable[i][j]);   
         else
            printf("%3d" ,nfaTable[i][j]);
      }
      printf("\n");
   }

   return 0;
}
