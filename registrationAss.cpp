//
// Created by Khant Min on 1/23/2023.
//
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#define SIZE 8

struct Db{
    int age;
    char name[20];
    char email[30];
    char password[20];
};
struct Db info[SIZE];
struct Db dataAsign;

void userOption();
void registration();
void insertingData();
void emailValidation();
void recordingAllDataOnFile();

void login();
void loadingAllDataFromFile();
void myStrCmp(char userInputChar[40]);
void passChecking(char pass[20], int userIndex);
int charCounting(char toCount[40]);
void userActionSector();

int uOp=0;
int eFound=-1;
int pFound=-1;
int globalIndex=0;
int eValid=-1;
char eForm[10];


int main(){

    userOption();

    return 0;
}


void userOption(){
    printf("1. registration\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    scanf("%d",&uOp);
    if (uOp==1){
        insertingData();
    } else if(uOp==2){
        login();
    } else if(uOp==3){
        exit(1);
    } else{
        printf("invalid option\n");
        userOption();
    }
}

void login() {
    char lEmail[30];
    char password[20];

    loadingAllDataFromFile();

    printf("This is Login Form\n");
    printf("Enter your Email to Login:");
    scanf(" %[^\n]",&lEmail);

    eFound=-1;
    myStrCmp(lEmail);

    printf("Enter your Password:");
    scanf(" %[^\n]",&password);

    pFound=-1;
    passChecking(password,eFound);

    if (eFound != -1 && pFound == 1){
        userActionSector();
    } else {
        printf("Invalid Email\n");
        login();
    }


}

void loadingAllDataFromFile(){
    FILE *fptr = fopen("KM.txt","r");
    if (fptr==NULL){
        printf("Error Loading Data");
    }else {
        for (int i = 0; i < SIZE; i++) {

            fscanf(fptr,"%d%s%s%s",&info[i].age,&info[i].name,&info[i].email,&info[i].password);
            if (info[i].name[0]=="\0"){
                break;
            }
            globalIndex++;
        }
    }
}

void myStrCmp(char userInputChar[50]){

    int sameCount=0;
    int second = charCounting(userInputChar);

    for (int i = 0; i < globalIndex; i++) {
        int first = charCounting(info[i].email);
        if (second==first){
            for (int j = 0; j < second; j++) {
                if(info[i].email[j] !=userInputChar[j]){
                    break;
                } else{
                    sameCount++;
                }
            }
        }
        if(second == sameCount){
            eFound=i;
            break;
        }
    }

}

void passChecking(char pass[50], int userIndex){
    int passCount= charCounting(pass);
    int infoPassCount = charCounting(info[userIndex].password);

    int sameCount=0;
    if(passCount==infoPassCount){
        for(int i=0; i<passCount ;i++){
            if(pass[i]== info[userIndex].password[i]){
                sameCount++;
            } else {
                break;
            }
        }
    }
    if(infoPassCount==sameCount){
        pFound=1;
    }
}

int charCounting(char toCount[50]){
    int charCount=0;
    for(int i=0; i<50; i++){
        if( toCount[i]=='\0'){
            break;
        } else {
            charCount++;
        }
    }
    return charCount;
}

void userActionSector(){
    int userAction=0;
    printf("Welcome Sir: %s\n",info[eFound].name);
    printf("press 1 to user action sector\n");
    printf("press 2 for home\n");
    printf("print 3 to exit\n");
    scanf("%d",&userAction);

    if(userAction==1){
        printf("this is your action sector:\n");
    } else if( userAction == 2){
        login();
    } else if(userAction == 3){
        exit(1);
    } else{
        printf("Invalid Option");
        userActionSector();
    }
}


void insertingData(){
    printf("Enter Your Age :");
    scanf("%d",&dataAsign.age);
    printf("Enter Your Name :");
    scanf(" %[^\n]",&dataAsign.name);
    printf("Enter Your Email: ");
    scanf(" %[^\n]",&dataAsign.email);
    printf("Enter Your Password :");
    scanf(" %[^\n]",&dataAsign.password);

    eValid=-1;
    emailValidation();
    loadingAllDataFromFile();
    eFound=-1;
    myStrCmp(dataAsign.email);


    if (eValid != -1 && eFound== -1){
        recordingAllDataOnFile();
        userOption();
    } else {
        printf("email already taken or invalid\n");
        insertingData();
    }

};

void emailValidation(){
    int validCount=0;
    strcpy(eForm,"@gmail.com");

    int inputELength= charCounting(dataAsign.email);
    for (int i = 0; i < inputELength; ++i) {

        if(dataAsign.email[i]==eForm[0]){
            int k=i;
            for (int j = 0; j < 10; j++) {
                if(dataAsign.email[k]==eForm[j]){
                    k++;
                    validCount++;
                } else{
                    break;
                }
            }
        }
    }

    if(validCount==10){
        eValid=1;
    }

}

void recordingAllDataOnFile(){
    FILE *fptr = fopen("KM.txt","a");

    if (fptr==NULL){
        printf("Error recording Data.");
    } else{
        fprintf(fptr,"%d %s %s %s %c",dataAsign.age,dataAsign.name,dataAsign.email,dataAsign.password,'\n');
        printf("Saving Data Completed");
    }
    fclose(fptr);
}