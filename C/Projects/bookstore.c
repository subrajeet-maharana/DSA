#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void insert(FILE *fp);
void delete(FILE *fp);
void display(FILE *fp);
void modify(FILE *fp);
void list(FILE *fp);
void booksold(FILE *fp);
int search(FILE *fp, char *name);
struct {
    char name[50];
    int ncopies;
    float cost;
}book;
int main(void){
    int choice;
    FILE *fp;
    fp=fopen("books","rb+");
    if(fp==NULL){
        fp=fopen("books","wb+");
        if(fp==NULL){
            puts("Error in opening the file\n");
            exit(1);
        }
    }
    while(1){
        printf("\n1.Insert a new record\n2. Delete a record\n3. Display a record\n4. Modify an existing record\n5. List all records\n6. Book sold\n7. Exit\nEnter your choice\n");
        scanf("%d",&choice);
        switch(choice){
            case 1: 
                insert(fp);
                break;
            case 2: 
                delete(fp);
                break;
            case 3: 
                display(fp);
                break;
            case 4:
                modify(fp);
                break;
            case 5:
                list(fp);
                break;
            case 6:
                booksold(fp);
                break;
            case 7:
                fclose(fp);
                exit(1);
            default:
                printf("Wrong Choice");
        }
    }
    return 0;
}
void insert(FILE *fp){
    fseek(fp,0,2);
    printf("Enter the name of the book: \n");
    scanf("%s",book.name);
    printf("Enter the number of copies: \n");
    scanf("%d",&book.ncopies);
    printf("Enter the cost of the book: \n");
    scanf("%f",&book.cost);
    fwrite(&book,sizeof(book),1,fp);
}
void delete(FILE *fp){
    FILE *fptemp;
    char name[20];
    printf("Enter the book name to delete from the database: \n");
    scanf("%s",name);
    if(search(fp,name)==0){
        return;
    }
    fptemp=fopen("tempfile","wb");
    rewind(fp);
    while(fread(&book,sizeof(book),1,fp)==1){
        if(strcmp(name,book.name)!=0){
            fwrite(&book,sizeof(book),1,fptemp);
        }
    }
    fclose(fp);
    fclose(fptemp);
    remove("books");
    rename("tempfile","books");
    printf("\nRecord deleted....\n");
    fp=fopen("books","rb+");
}
void modify(FILE *fp){
    char name[50];
    long size=sizeof(book);
    printf("Enter the name of the book to be modified: \n");
    scanf("%s",name);
    if(search(fp,name)==1){
        printf("Enter the new data for the book. \nEnter the book name: \n");
        scanf("%s",book.name);
        printf("Enter the number of copies: \n");
        scanf("%d",book.ncopies);
        printf("Enter the cost of the book: \n");
        scanf("%f",book.cost);
        fseek(fp,-size,1);
        fwrite(&book,sizeof(book),1,fp);
        printf("Record modified successfully.\n");
    }
}
void booksold(FILE *fp){
    char name[50];
    long size=sizeof(book);
    printf("Enter the name of the book to be sold: \n");
    scanf("%s",name);
    if(search(fp,name)==1){
        if(book.ncopies>0){
            book.ncopies--;
            fseek(fp,-size,1);
            fwrite(&book,sizeof(book),1,fp);
            printf("One book sold\n");
            printf("Now number of copies = %d",book.ncopies);
        }
        else {
            printf("Out of stock\n");
        }
    }
}
void display(FILE *fp){
    char name[50];
    printf("Enter the name of the book: \n");
    scanf("%s",name);
    if(search(fp,name)==1){
        printf("Name: %s\n",book.name);
        printf("Number of Copies: %d\n",book.ncopies);
        printf("Cost: %f\n",book.cost);
    }
}
int search(FILE *fp,char *name){
    unsigned flag=0;
    rewind(fp);
    while(fread(&book,sizeof(book),1,fp)==1){
        if(strcmp(name,book.name)==0){
            flag=1;
            break;
        }
    }
    if(flag==0){
        printf("Book not found\n");
    }
    return flag;
}
void list(FILE *fp){
    rewind(fp);
    printf("\nNames\tCopies\tCost\n\n");
    while(fread(&book,sizeof(book),1,fp)==1){
        printf("%s\t",book.name);
        printf("%d\t",book.ncopies);
        printf("%f\n",book.cost);
    }
    printf("\n");
}