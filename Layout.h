void LayoutMenu()
{
	system("cls");
	int c,l,C[3],L[3];
	C[0]=1; C[1]=35; C[2]=100;
	L[0]=1; L[1]=5; L[2]=30;
	for(c=C[0];c<C[2];c++)
	{
		l=L[0];
		gotoxy(c,l);
		printf("%c",205);
		l=L[1];
		gotoxy(c,l);
		printf("%c",205);
		l=L[2];
		gotoxy(c,l);
		printf("%c",205);
	}
	for(l=L[0];l<L[2];l++)
	{
		c=C[0];
		gotoxy(c,l);
		printf("%c",186);
		c=C[1];
		if(l>5)
		{
			gotoxy(c,l);
			printf("%c",186);
		}
		c=C[2];
		gotoxy(c,l);
		printf("%c",186);
	}
	c=C[0];
	l=L[0];
	gotoxy(c,l);
	printf("%c",201);
	l=L[1];
	gotoxy(c,l);
	printf("%c",204);
	l=L[2];
	gotoxy(c,l);
	printf("%c",200);
	
	
	c=C[1];
	l=L[0];
	gotoxy(c,l);
	printf("%c",205);
	l=L[1];
	gotoxy(c,l);
	printf("%c",203);
	l=L[2];
	gotoxy(c,l);
	printf("%c",202);
		
	c=C[2];
	l=L[0];
	gotoxy(c,l);
	printf("%c",187);	
	l=L[1];
	gotoxy(c,l);
	printf("%c",185);
	l=L[2];
	gotoxy(c,l);
	printf("%c",188);
	
	
	
	gotoxy(1,40);	
}
