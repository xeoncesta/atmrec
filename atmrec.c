#include<avr/io.h>
#include<util/delay.h>
#include<string.h>
//#include<fstream.h>

int ref=0;
float amt[4];
float balance;
struct child
{
char name[80],state[20];
float age,balance1;

};
child first={"Amitesh","N.Delhi",20,10000000};
void lock()
{
lcd();
DDRD=0xff;
while(1)
{PORTD=0x01;}

}
void info(char card)
{

if((strncmp(arr,card,12))==0)
   {  lcd();
      ofstream myfile;
	  myfile.open("A.txt",ios::app);
      myfile<<first.name;
	  myfile<<first.state;
	  myfile<<first.age;
	  string("Enter amt(max:20k) ");
      for(int k=0;k<5;k++)
	  {amt=UDR;}
	  balance=balance-amt;
      myfile<<amt;
	  
	  myfile.close();
   } 


}

void infodisplay (char card)
{
char name[80],state[20];
float age,amt;

if((strncmp(arr,card,12))==0)
    { lcd();
       ifstream datafile;
	   datafile.open("A.txt");
	   while(!datafile.eof())
	   { cmd(0x80);
         datafile.get(name);
		 data(name);
         _delay_ms(4000);
	   datafile.get(state);
		 data(state);
         _delay_ms(4000);
	  
	   datafile>>age;
	     data(age);
	     _delay_ms(4000);
	  
	  cmd(0xc0);
	  datafile>>amt;
	     data(amt);
	     _delay_ms(4000);
	  
	   datafile.close(); 
	   }
     
    }


}

void cmd(char c)
{
PORTB=c;
PORTC=0x04;
_delay_ms(10);
PORTC=0x00;

}
void data(char c)
{
PORTB=c;
PORTC=0x05;
_delay_ms(10);
PORTC=0x01;


}

void lcd()
{

cmd(0x38);
_delay_ms(10);
cmd(0x01);
_delay_ms(10);
cmd(0x0e);
_delay_ms(10);
cmd(0x80);
_delay_ms(10);

}

void string(unsigned char *p)
{
while(*p!='\0')
{data(*p);
p++;}
}


void num(unsigned int p)
{
unsigned int k,w,b=1;
k=p;
while(k>=10)
{
b=b*10;
k=k/10;
}
while(b>0)
{
w=p/b;
p=p%b;
b=b/10;
data(w+48);

}


}
char x;
unsigned char arr[12];
unsigned char card[12]="986867268600";

void main()
{
//DDRD=0x00;
DDRC=0xff;
DDRB=0xff;
UBRRL=51;
UCSRB=(1<<TXEN)|(1<<RXEN);
UCSRC=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
lcd();
cmd(0x80);
string("Welcome To HCL CDC  Banking System ");
_delay_ms(8000);

while(1)
{
lcd();


string("PLZ SCAN....");
cmd(0xc0);

for(int i=0;i<12;i++)
{
while((UCSRA&(1<<RXC))==0);
{
x=UDR;
arr[i]=x;
data(x);
string("*");
}
}

if((strncmp(arr,card,12))==0)
{
cmd(0x80);
string("CARD ACCEPTED");
info(card);


}
else
{
cmd(0x80);
string("WRONG CARD");
ref++;


}
_delay_ms(8000);
if(ref>=3)
   {
    string("security lockdown");
    _delay_ms(8000);
	lock();
	}
}


}
