/**************************************************************************************************/
/* Copyright (C)  SSE@USTC, 2014-2015                                                             */
/*                                                                                                */
/*  FILE NAME             :  MenuOfCommand.c                                                      */
/*  PRINCIPAL AUTHOR      :  Zhang Fuqiang                                                        */
/*  SUBSYSTEM NAME        :  MenuOfCommand                                                        */
/*  MODULE NAME           :  MenuOfCommand                                                        */
/*  LANGUAGE              :  C                                                                    */
/*  TARGET ENVIRONMENT    :  ANY                                                                  */
/*  DATE OF FIRST RELEASE :  2014/09/11                                                           */
/*  DESCRIPTION           :  This is a menu program                                               */
/**************************************************************************************************/

/*
 * Revision log:
 *
 * Created by Zhang Fuqiang, 2014/09/11
 *
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define CMD_LEN      20
#define DESC_LEN     1024
#define CMD_CHR_LEN  10
#define CMD_NUM      20

/* Define a LinkList Node */

typedef struct DataNode
{
    int  cmdNumber;
    char cmd[CMD_CHR_LEN];
    char desc[DESC_LEN];
    struct DataNode *next; 
}tDataNode;

/* get the description of an inputed command*/

void GetDESC(tDataNode *cmdNode)
{
   char chr;
   int len = 0;

   while((chr = getchar())!= '#')
    {
       cmdNode->desc[len] = chr;	
       len ++;
     
       if(len > DESC_LEN)
         {
            printf("description is too long!\n");
            break; 
         } 
    }
    cmdNode->desc[len] = '\0';
}

/* search the position of a pattern string in a List*/

int Search(char pattern[], tDataNode *cmdList)
{
   tDataNode *p = cmdList->next;

   while(p != NULL)
      {
         if(!strcmp(p->cmd,pattern))
               return p->cmdNumber;
         p = p->next;      
      }
  return -1;
}

/*  initial a command LinkList */

void Init(tDataNode *cmdList)
{
   int i = 0 ;
   int cmdLen;
   tDataNode *p = NULL;
   tDataNode *q = cmdList;

   printf("please input the number of command's call parameters(<=20)\n");
   scanf("%d",&cmdLen);
   if(cmdLen > CMD_LEN) cmdLen = CMD_LEN; 

   while(i ++ < cmdLen)
   {
       printf("please input %d parameter!\n",i);    
      
       p = (tDataNode *)malloc(sizeof(tDataNode));
       p->cmdNumber = i ;
       scanf("%s",p->cmd);
       
       if(Search(p->cmd,cmdList) != -1) 
           {
              printf("the Command %s is exist,please input another",p->cmd);
              i -- ;
              continue;  
           }   
           
       printf("please input this parameter's detail!(end with '#')\n"); 
	    
       GetDESC(p); 
       
	   p->next= q->next;    
       q->next = p;
       q = p;	    
   }
}

/*  print the name of a command */

void PrintCMD(tDataNode *cmdNode)
{
    printf("parameter %d is:\n",cmdNode->cmdNumber);
    printf("\t%s\n",cmdNode->cmd);
}

/*  print the detail information of a command*/

void PrintDESC(tDataNode *cmdNode)
{  
    printf("Detail of parameter %d below:",cmdNode->cmdNumber);
   
    printf("    %s\n",cmdNode->desc);
}

/*  output all of information include the name and */
/*  detail information of a command                */

void DisplayAll(tDataNode *cmdList)
{
    tDataNode *p = cmdList->next;   
    int no = 1;
   
    while(p != NULL)
      {
         printf("%s  ",p->cmd);
         
		 if(no == 5) 
		   {
		     printf("\n");
		     no = 0;
		   }
		   
		 no ++; 
         p = p -> next;  
      }
}
/*  display the detail information of command inputed*/

void Display(char pattern[], tDataNode *cmdList)
{
    int pos;
    char chr[] = "help";    
    tDataNode *p = cmdList->next; 
  
    if(!strcmp(pattern,chr))
       {
         DisplayAll(cmdList); 
       }
    else 
       { 
         pos = Search(pattern,cmdList);
         
        if(pos == -1)
            {
               printf("not exist\n");
               return ;      
            }    

        while(p->cmdNumber != pos)
           {
              p = p->next; 
           }  
        PrintDESC(p); 
       }
}

/* Initial the array of LinkList */

int InitArray(tDataNode cmdList[])
{
   int num;
   int i;
   int j;
   char pat[CMD_CHR_LEN];
   
   printf("please input the number of command\n");
   scanf("%d",&num);
   if(num > CMD_NUM)
    {
	  num = CMD_NUM; 
    }
    
   for(i = 0 ; i < num ; i ++)
    {
       printf("please input the %d command name\n",i+1);	
       cmdList[i].next = NULL;	
    	
	   scanf("%s",cmdList[i].cmd);	   
	   Init(&cmdList[i]);
	}     
    
	return num;
}


main()
{
    tDataNode cmdList[CMD_NUM];
    char pattern[CMD_CHR_LEN];
    char mainpattern[CMD_CHR_LEN];
    int i = 0 ;
    int num;
    
    /*  initial the HeadNode of List */

    num = InitArray(cmdList);
 
    printf("\n\n");
   
    printf("cmd->");
    
    while(1)
    {
       scanf("%s",mainpattern);
       
       for(i = 0; i < num ; i ++)
        {
        	if(!strcmp(cmdList[i].cmd,mainpattern))
        	    break;
	    }
	    
	   if(i == num)
	    {
	    	
	    	printf("not exist\ncmd->");
	    	continue;
		} 
       
       printf("%s->",mainpattern);
       
       /*  Process the funtion of this program */
       
       while(scanf("%s",pattern) != EOF)
		{
           if(!strcmp(pattern,"q"))	
		     {
			     break;
             }

           Display(pattern,&cmdList[i]);           
           printf("\n%s->",mainpattern);	 
        } 
        
        printf("cmd->");	  
    }
}

