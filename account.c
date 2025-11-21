#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
//==========================================
//load Accounts method
Account* loadAccounts(const char *filename){
   //-------------
   //open the file
   FILE *fp=fopen(filename,"r+");
   //check
   if (fp == NULL) {
      printf("Sorry, Can't open accounts file\n");
      return NULL;}
   //-------------
   Account *head = NULL;
   Account *tail = NULL;
   int id, age, admin;
   char user[20], pass[20];
   //read a line
   while (fscanf(fp, "%d %s %d %s %d", &id, user, &age, pass, &admin) == 5) {
      Account *newA = (Account*)malloc(sizeof(Account));
      
      newA->accountID = id;
      strcpy(newA->username, user);
      newA->age = age;
      strcpy(newA->password, pass);
      decryptPassword(newA->password);
      newA->isAdmin = admin;
      newA->next = NULL;

      if (!head)
         head = tail = newA;
      else{
         tail->next = newA;
         tail = newA;}
   }//while
   //close the file
    fclose(fp);
    return head;
}//end load
//==========================================
//save Accounts method
void saveAccounts(Account *head, const char *filename){
   FILE *fp=fopen(filename,"w");
   //check
   if (fp == NULL) {
      printf("Sorry, Can't save the file\n");
      return;}
     
   Account *curr = head;
   char temp[20];
   while (curr !=NULL) {
      strcpy(temp, curr->password);
      encryptPassword(temp);
      fprintf(fp, "%d %s %d %s %d\n", curr->accountID, curr->username, curr->age, temp, curr->isAdmin);
      curr = curr->next;}
   
   //close the file
   fclose(fp);
}//end save
//==========================================
//register Account method
Account* registerAccount(Account *head, char *username, int age, char *password){
   //the user must be 18 or older
   if (age < 18) {
      printf("Age must be 18 or older to register\n");
      return head;}
   //------------------------
   //loop through the list to count existing accounts and check for duplicate usernames  
   Account *curr = head;
   int count=0;//for the ID
   while (curr != NULL) {
      if (strcmp(curr->username, username) == 0) {//If a matching username is found, do not register the account
         printf("Username already exists, Please choose another one\n");
         return head;}
      count++;
      curr = curr->next;
    }
   int newID = count+1;
   //-----------------------
   //create new account node
   Account *newA = (Account*) malloc(sizeof(Account));
   newA->accountID = newID;
   strcpy(newA->username, username);
   newA->age = age;
   strcpy(newA->password, password);
   newA->isAdmin =0;
   //if the list is empty, this new account becomes the head
   if(head==NULL) return newA;
   curr= head;
   while(curr->next!=NULL) curr = curr->next;
   curr->next = newA;
   return head;
}//end
//==========================================
//login method
Account* login (Account *head, char *username, char *password){
   Account *curr = head;
   while(curr != NULL) {
      if(strcmp(curr->username, username) == 0 && strcmp(curr->password, password) == 0) 
         return curr;//login successful
      curr = curr->next;
    }
    return NULL;//not found
}//end login method
//==========================================
//encrypt Password method
void encryptPassword(char *password) {
    for(int i = 0; password[i] != '\0'; i++)
        password[i] += 3; //Caesar +3
}
//==========================================
//decrypt Password method
void decryptPassword(char *password) {
    for(int i = 0; password[i] != '\0'; i++)
        password[i] -= 3; //Caesar -3
}
