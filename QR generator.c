#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 150


//prototype for the defined functions

char hashed(int inputch,int shift);
int rotate(int ch,int rotate);
int qrsquare (int rows,int colour1,int colour2,int k,int l);
int printchar (int decimal,int k,int l,int colour1);


int main(int argc, char *argv[])
{
    //checking for the correct command line from the user

    int x,go;

        if (argc==1){
            x=40;
            go=1;
        }else if (argc==3){
            if(strcmp(argv[1],"-c")==0){

                //making the color to lower casr
                for(int i = 0; argv[2][i] != '\0'; i++){
                    argv[2][i]=tolower(argv[2][i]);
                }
                if(strcmp(argv[2],"black")==0){
                    x=40;
                    go=1;

                }else if(strcmp(argv[2],"red")==0){
                    x=41;
                    go=1;

                }else if(strcmp(argv[2],"green")==0){
                    x=42;
                    go=1;

                }else if(strcmp(argv[2],"yellow")==0){
                    x=43;
                    go=1;

                }else if(strcmp(argv[2],"blue")==0){
                    x=44;
                    go=1;

                }else if(strcmp(argv[2],"magenta")==0){
                    x=45;
                    go=1;

                }else if(strcmp(argv[2],"cyan")==0){
                    x=46;
                    go=1;
                }else{
                    go=0;
                    printf("Invalid argument for color.\n");
                    printf("usage :\n");
                    printf("%s -c [black|red|green|blue|magenta|cyan]\n",argv[0]);
                    printf("%s -h for the help about the program\n",argv[0]);
                    }
            }else{
                go=0;
                printf("Incorrect usage of arguments.\n");
                printf("usage :\n");
                printf("%s -c [black|red|green|blue|magenta|cyan]\n",argv[0]);
                printf("%s -h for the help about the program\n",argv[0]);
                }
    }else if (argc ==2) {
        if(strcmp(argv[1],"-h")==0){
            go=0;
            printf("usage :\n");
            printf("%s -c [black|red|green|blue|magenta|cyan]\n",argv[0]);
            printf("%s -h for the help about the program\n",argv[0]);
        }
        else {
            go=0;
            printf("Incorrect usage of arguments.\n");
            printf("usage :\n");
            printf("%s -c [black|red|green|blue|magenta|cyan]\n",argv[0]);
            printf("%s -h for the help about the program\n",argv[0]);
            }
    }else {
        go=0;
        printf("Incorrect usage of arguments.\n");
        printf("usage :\n");
        printf("%s -c [black|red|green|blue|magenta|cyan]\n",argv[0]);
        printf("%s -h for the help about the program\n",argv[0]);
    }

//if the commmand is correct, continue the program
if (go==1){

    //initialing variables
    int len,size,framesize,gogo;
    unsigned char input[MAX];
    int inputch;
    unsigned char hash[MAX];
    unsigned char output[MAX];

    //taking the input from the user
    printf("Enter the URL: ");
    scanf("%s",input);

    //finding the string length of the input
    len = strlen((char*)input) ;
    inputch=input[0];
    //defining the fist character of the hashed string
    hash[0]=50+len;
    

    //checking whether the input string is within the relevant string length
    if (len<4){
	printf("String is too short. Not supported by available QR versions\n");
	gogo=0;
    }else if (len>121){
	printf("String is too long. Not supported by available QR versions\n");
	gogo=0;
    }else{
	gogo=1;
    }


    //continuing the program if the string length is correct
    if (gogo==1){
	//clearing the console
	printf("\033[2J");

    //declaring size of the hashed string and frame size according to the string length of the user input
    if (len<21){
        size=24;
        framesize=20;

    }if (len>20){
        size=132;
        framesize=38;
    }

    //creating a new string with the relevant shifting
    int shift=0;
    int index=1;
    while (index<size){
    //rotating to the number of inputcharacters
        for (int j =0;j<len;j++){

            inputch=input[j];
            hash[index]=hashed(inputch,shift);
            index++;
        }
        shift++;
    }

    //creating the hashed string after reversing accordingly
    int first=0;
    int last=(size-1);
    for(int i=0;i<size;i++){
        if (i<len+1){
            output[i]=hash[first];

            first++;
        }else{
            output[i]=hash[last];
            last--;
            }
        }

       //printing the main frame
        qrsquare(framesize,47,x,1,1);
        qrsquare(6,x,47,2,3);
        qrsquare(4,47,x,3,5);
        qrsquare(6,x,47,2,((framesize*2)-13));
        qrsquare(4,47,x,3,((framesize*2)-11));
        qrsquare(6,x,47,(framesize-6),3);
        qrsquare(4,47,x,(framesize-5),5);



        int start;int end; int k; int cons; int columns; int rows;
        int letters=0;
        while (letters<size){

           //declaring the values to the variables accordingly
           if (size==24){
                if (letters==0){
                start=0;end=16;k=8;cons=15;columns=4;rows=4;
                }if(letters==16){
                start=16;end=20;k=2;cons=15;columns=2;rows=2;
                }if(letters==20){
                start=20;end=24;k=8;cons=3;columns=2;rows=2;
                }
            }
            if (size==132){
                if (letters==0){
                start=0;end=100;k=8;cons=15;columns=10;rows=10;
                }if(letters==100){
                start=100;end=116;k=2;cons=15;columns=8;rows=2;
                }if(letters==116){
                start=116;end=132;k=8;cons=3;columns=2;rows=8;
                }
            }

        //printing the qr for each character of the hashed string
        while (start<end){
        for(int i=0; i<rows; i++){
        int l=cons;
        for(int j=0; j<columns; j++){
            //moving the cursor to the correct place
            printf("\033[%d;%dH",k,l);
            printchar (output[letters],k,l,x);
            l=l+6;
            start++;
            letters++;
        }
        k=k+3;
        }
        }
        }

        //finally moving the cursor away
        printf("\033[40;1H");


}
}
        return 0;
}

//to shift the character accordingly
char hashed (int inputchar,int shift){
    int hashch;
    if (shift>0){
        hashch=rotate(inputchar,shift);
    }else{
        hashch=inputchar;
        }
    return hashch;
}

//to rotate the cursor accordingly
int rotate (int ch, int shift){
    for (int count=0;count<shift;count++){
        ch=ch+1;
    }

    return ch;

}

//printing a square to print the qr frame
int qrsquare(int r,int colour1,int colour2,int k,int l)
{
    for(int i=1; i<=r; i++)
    {
        printf("\033[%d;%dH",k,l);
        for(int j=1; j<=r; j++)
        {
            if( i==1 || i==r || j==1 || j==r)
            {
                printf("\033[0;%dm",colour1); //Set the background color to the color given color
                printf("  "); //print the space
                printf("\033[0m");
            }
            else
            {
                printf("\033[0;%dm",colour2); //Set the background color to the color given color
                printf("  "); //print the space
                printf("\033[0m");
                }
        }
        k++;
    }

    return 0;
}

//print the qr for each character
int printchar (int decimal,int k,int l,int colour1){

    //converting the ascii of each character to binary
    int p,q;
    char binary[9];
    int count=9;
    while (decimal != 0){
        count--;
        binary[count]=decimal%2;
        decimal=decimal/2;

    }
    while (count !=0){
        count--;
        binary[count]=0;
    }

    //print the qr for each character according to their binary
        p=k;
        q=l;
          int count1=0;
            while(count1<9){
                for (int r=1;r<=3;r++){
                        q=l;
                    for(int c=0;c<3;c++){
                    printf("\033[%d;%dH",p,q);


                    if (binary[count1]==1){
                        printf("\033[0;%dm",colour1);
                        printf("  ");
                        printf("\033[0m");
                    }if (binary[count1]==0){
                        printf("\033[0;47m");
                        printf("  ");
                        printf("\033[0m");
                }

               q=q+2;
                count1++;
            }
            p++;
        }
     }

return 0;
}



