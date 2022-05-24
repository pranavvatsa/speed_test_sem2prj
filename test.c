# include <stdio.h>

main ()
{
    FILE *fp = fopen("lines.txt", "r");
    if (fp == NULL) return -1;
    else printf("file open success\n");
   
    char a[5000],c;
    //memset (a, '\0', 5000);
    int j=0;

    while ((c = fgetc(fp)) != EOF)
    {
        a[j]=c;
        j++;
    }
    fclose(fp);
    //char a[]="This is a test text to check your speed!";
    //int n=length(a);
    printf("%s",a);
}

