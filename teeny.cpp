#include <iostream>
#include <stdlib.h>
#include<Windows.h>
#include<string>
#include "Teeny.h"
using namespace std;
void SetColor(int value)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),value);
}
//Skeleton of class LinkedText
struct Node{
        char ch;
        Node * next;
        Node * prev;
    };
class LinkedText{
     Node*head, *tail, *cursorPos;

    int textSize,lastOption,atHead;

    public:
        LinkedText(){
            head=tail=cursorPos=NULL;
            textSize=0;lastOption=0,atHead=0;
        }
        //some suggested methods
        //All these methods (except copying) are O(1) thanks to the linked list!
        void addCharAtCursorPos(char input)//when char entered
		{
			if (textSize==0)
			{
				head = new Node;
				head->ch = input;
				head->next = nullptr;
				head->prev=head;
				tail = head;
				cursorPos = head;
				textSize++;
			}
			else if (textSize>0)
			{
				Node*temp = new Node[1];
				temp->ch = input;
				if (cursorPos == tail)
				{
					Node*temp1 = tail;
					tail = temp;
					temp->next = nullptr;
					temp->prev = temp1;
					temp1->next = temp;
					cursorPos = temp;
					textSize++;
				}
				else if (cursorPos == head && atHead==1)
				{
					Node*temp2=head;
					head = temp;
					temp->next = temp2;
					temp->prev = head;
					temp2->prev=temp;
					cursorPos = temp;
					atHead=0;
					textSize++;
				}
				else if (cursorPos == head && atHead==0)
				{
					Node*temp2=head->next;
					head->next=temp;
					temp->next = temp2;
					temp->prev = head;
					temp2->prev=temp;
					cursorPos = temp;
					textSize++;
				}
				else
				{
					Node*temp1=cursorPos->next;
					cursorPos->next=temp;
					temp->prev = cursorPos;
					temp->next= temp1;
					temp1->prev=temp;
					cursorPos = temp;
					textSize++;
				}
			}

		}
		void delCharAtCursorPos()//when bksp pressed
        {
			if (cursorPos == head)
			{
				if (textSize == 1)
				{
					head = tail = cursorPos = nullptr;
					textSize--;
				}
				else if(textSize>1)
				{
				Node*temp1=cursorPos->next;
				head = cursorPos->next;
				temp1->prev=head;
				cursorPos=temp1;
				textSize--;
				if (textSize == 0)
					head = tail = cursorPos = nullptr;

				}
				
			}
			else if(cursorPos->next==nullptr)
			{
				if (textSize == 1)
				{
					head = tail = cursorPos = nullptr;
					textSize--;
				}
				else if(textSize>1)
				{
				Node*temp1= cursorPos->prev;
				tail = temp1;
				cursorPos = temp1;
				temp1->next = nullptr;
				textSize--;
				if (textSize == 0)
					head = tail = cursorPos = nullptr;
				}
				
			}
			else
			{
				Node*temp1 = cursorPos->prev;
				Node*temp2=cursorPos->next;
				temp1->next = temp2;
				temp2->prev=temp1;
				cursorPos = temp1;
				textSize--;
			}
		
		
		}
		void moveCursorRight()//right arrow
		{
			cursorPos=cursorPos->next;
		}
        void moveCursorLeft()//left arrow
		{
			if(cursorPos==head)
			{
				atHead=1;
			}
			else
				atHead=0;
			cursorPos=cursorPos->prev;
		}
        /*the following method returns the sub-list after cutting,
        and also adjusts cursor position*/
		Node* sublist(Node * cursorpos1, Node * cursorpos2,int n,LinkedText &l1)
		{
			l1.cursorPos=l1.head;
			l1.atHead=1;
			Node*temp1=cursorpos1;
			while(temp1!=cursorpos2)
			{
				l1.addCharAtCursorPos(temp1->ch);
				temp1=temp1->next;
				if(n==0)
				  textSize--;
			}
			if(n==0)
			textSize--;
			l1.addCharAtCursorPos(cursorpos2->ch);

			return l1.head;
		}
		bool directionFounder(Node * cursorpos1, Node * cursorpos2)
		{
			Node*temp1=cursorpos1;
			while(temp1!=cursorpos2)
			{
				temp1=temp1->next;
				if(temp1==nullptr)
					return false;
			}
			return true;
		}
        Node * cutTextBetween(Node * cursorpos1, Node * cursorpos2,LinkedText &l1)
		{
			if(cursorpos1->next==nullptr && cursorpos2==head )
			{
				head=tail=cursorPos=nullptr;
				return sublist(cursorpos2,cursorpos1,0,l1);
			}
			else if(cursorpos2->next==nullptr && cursorpos1==head)
			{
					head=tail=cursorPos=nullptr;
				return sublist(cursorpos1,cursorpos2,0,l1);
			}
			else if(cursorpos1->next==nullptr)
			{
				Node*temp1=cursorpos2->prev;
				temp1->next=nullptr;
				tail=temp1;
				cursorPos=temp1;
				return sublist(cursorpos2,cursorpos1,0,l1);
			}
			else if(cursorpos2->next==nullptr)
			{
				Node*temp1=cursorpos1->prev;
				temp1->next=nullptr;
				tail=temp1;
				cursorPos=temp1;
				return sublist(cursorpos1,cursorpos2,0,l1);
			}
			else if(cursorpos1==head)
			{
					Node*temp1=cursorpos2->next;
					head=temp1;
					cursorPos=temp1;
					temp1->prev=head;
					return sublist(cursorpos1,cursorpos2,0,l1);
			}
			else if(cursorpos2==head)
			{
					Node*temp1=cursorpos1->next;
					head=temp1;
					cursorPos=temp1;
					temp1->prev=head;
					return sublist(cursorpos2,cursorpos1,0,l1);
			}
			else if(directionFounder(cursorpos1,cursorpos2))
			{
				Node*temp1=cursorpos1->prev;
				Node*temp2=cursorpos2->next;
				temp1->next=temp2;
				temp2->prev=temp1;
				cursorPos=temp1;
				return sublist(cursorpos1,cursorpos2,0,l1);
			}
			else
			{
				Node*temp1=cursorpos1->next;
				Node*temp2=cursorpos2->prev;
				temp2->next=temp1;
				temp1->prev=temp2;
				cursorPos=temp2;
				return sublist(cursorpos2,cursorpos1,0,l1);
			}
		}
        /*the following method returns the duplicated sub-list after copying,
        and also adjusts cursor position*/
        Node * copyTextBetween(Node * cursorpos1, Node * cursorpos2,LinkedText &l1)
		{
			lastOption=1;

			if(directionFounder(cursorpos1,cursorpos2))
				return sublist(cursorpos1,cursorpos2,1,l1);
			else
				return sublist(cursorpos2,cursorpos1,1,l1);
		}
		int findAndReplace(const string s1, const string s2)
		{
			Node*temp=head,*tempo,*tempo1;
			int diff=s2.length()-s1.length();
			int ind=0,count=0;
			while(temp!=nullptr)
			{
				tempo=temp;
				if(temp->ch==s1[ind])
				{
					bool change=false;
					while(temp!=nullptr && s1[ind]!='\0' && !change)
					{
						if(s1[ind]!=temp->ch)
						{
							change=true;
						}
						else
						{
							if(temp->next==nullptr)
							{
								tempo1=temp;
							}
							temp=temp->next;
							ind++;
						}
					}
					if(diff>0)
					{
						if(temp==nullptr)
							cursorPos=tempo1;
						else
							cursorPos=temp->prev;
						for(int i=0;i<diff;i++)
						{
							this->addCharAtCursorPos(' ');
						}
					}
					if(!change)
					{
						ind=0;
						temp=tempo;
						while(s2[ind]!='\0')
						{
							temp->ch=s2[ind++];
							temp=temp->next;
						}
						count++;
						if(diff<0)
						{
							cursorPos=temp;
							int pdiff=diff+10;
							pdiff=10-pdiff;
							for(int i=0;i<pdiff;i++)
							{
								this->delCharAtCursorPos();
								cursorPos=cursorPos->next;
								temp=temp->next;
							}
						}
					}
					ind=0;
				}
				else
					temp=temp->next;
			}
		 return count;
		}
        void insertTextAtCursorPos(Node * subList)
		{
			Node*temp2=subList;
			if(cursorPos==head && head!=nullptr)
			{
				this->addCharAtCursorPos(temp2->ch);
				temp2=temp2->next;
				while(temp2!=nullptr)
				{
					Node*temp=new Node;
					temp->ch=temp2->ch;
					Node*temp1=cursorPos->next;
					cursorPos->next=temp;
					temp->prev = cursorPos;
					temp->next= temp1;
					temp1->prev=temp;
					cursorPos = temp;
					textSize++;
					temp2=temp2->next;
				}
			}
			else if(cursorPos==nullptr || cursorPos!=head)
			{
				while(temp2!=nullptr)
				{
					this->addCharAtCursorPos(temp2->ch);
						temp2=temp2->next;
				}
			}
		}

        /*Method returns the number of times key occurs
        in LinkedText*/
        int findInText(const string & key)
		{
			Node*temp=head;
			int ind=0,count=0;
			while(temp!=nullptr)
			{
				if(temp->ch==key[ind])
				{
					bool change=false;
					while(temp!=nullptr && key[ind]!='\0' && !change)
					{
						if(key[ind]!=temp->ch)
						{
							change=true;
						}
						else
						{
							temp=temp->next;
							ind++;
						}
					}
					if(!change)
						count++;
					ind=0;
				}
				else
					temp=temp->next;
			}
		return count;
		}
        //You may add appropriate printing methods and other methods below
		void print()
		{
			system("cls");
			Node*temp=head;
			while(temp!=nullptr)
			{
				cout<<temp->ch;
				temp=temp->next;
			}
			temp=head;
			gotoxy(0,0);
			while(temp!=cursorPos)
			{
				moveScreenCursorRight();
				temp=temp->next;
			}
		}
        ~LinkedText()//add code
		{
			Node*temp=head,*temp1;
			while(temp!=nullptr)
			{
			temp1=temp->next;
			delete temp;
			temp=temp1;
			}
			head=tail=cursorPos=nullptr;
			textSize=0;
		}        
//delete the list


        /*The methods below will be used to keep
          the screen cursor inside the text area
          only.
        */
        inline bool textToLeft(){
            return (cursorPos!=NULL && cursorPos->prev!=NULL);
        }


        inline bool textToRight(){
            return (cursorPos!=NULL && cursorPos->next!=nullptr);
        }
		Node*currPosition()
		{
			return cursorPos;
		}
};

void Startpage()
{
	SetColor(6);
	cout<<"\t\t\n\n\tW";Sleep(200);cout<<"E";Sleep(200);cout<<"L";Sleep(200);cout<<"C";Sleep(200);cout<<"O";Sleep(200);cout<<"M";Sleep(200);cout<<"E";Sleep(200);cout<<"  T";Sleep(200);cout<<"O  ";Sleep(200);cout<<"M";Sleep(200);cout<<"Y   ";Sleep(200);cout<<"N";Sleep(200);cout<<"O";Sleep(200);cout<<"T";Sleep(200);cout<<"E";Sleep(200);cout<<"P";Sleep(200);cout<<"A";Sleep(200);cout<<"D !\n";Sleep(200);
	cout<<"\n\t\t\t Instructions for Notepad :\n"<<endl;
	Sleep(200);
	SetColor(3);
	cout<<"\t\t\t\t ==>> F1 FOR SELECTING TEXT  "<<endl;Sleep(200);
	cout<<"\t\t\t\t ==>> F2 FOR CUT"<<endl;Sleep(200);
	cout<<"\t\t\t\t ==>> F3 FOR COPY"<<endl;Sleep(200);
	cout<<"\t\t\t\t ==>> F4 FOR PRINTING"<<endl;Sleep(200);
	cout<<"\t\t\t\t ==>> F5 FOR FINDING A STRING IN THE TEXT"<<endl;Sleep(200);
	cout<<"\t\t\t\t ==>> F6 FOR FIND AND REPLACE FUNCTIONALITY"<<endl;Sleep(200);
	cout<<"\t\t\t\t ==>> INSERT KEY FOR PASTE "<<endl;Sleep(200);
	cout<<"\t\t\t\t ==>> BACKSKAPE KEY FOR DELETION"<<endl;Sleep(200);SetColor(7);
	cout<<"\t\t\t\t ==>> PRESS ENTER TO CONTINUE"<<endl;
	getch();
	system("cls");
}

int main()
{
    GetConsoleWindowDims();
    /*This starter code is capable of detecting the
      left and right arrow keys; the backspace key;
      the escape key (for quit); the F1, F2 and F3 keys;
      and the regular text keys.
      Written for CS-218 "Data Structures" BCS-3A, FAST-NU, Lahore.
    */
	Startpage();
    LinkedText text,l1;
    int key=-9,count=0,findCount=0;
	string ch,ch1;
	 Node*temp1,*temp2,*temp3;

    while(key!=ESCAPE){
          key=_getch();
          //either an arrow or function key is pressed
          if(SPECIAL_KEY(key)){
              key=_getch();//get 2nd part of code from buffer
              switch(key){
              case ARROW_LEFT:
                  if(text.textToLeft()){
                    moveScreenCursorLeft();
                    text.moveCursorLeft();
                  }
                break;
              case ARROW_RIGHT:
                  if (text.textToRight()){
                    moveScreenCursorRight();
                    text.moveCursorRight();
                  }
                break;
              case F1://start or end text selection
                 if(count==0)
				 {
					 temp1=text.currPosition();
					 count++;
				 }
				 else if(count==1)
				 {
					 temp2=text.currPosition();
					 count--;
				 }
                break;
              case F2://cut option
				  l1.~LinkedText();
				  temp3=text.cutTextBetween(temp1,temp2,l1);
				  text.print();
                break;
              case F3://copy option
				  l1.~LinkedText();
				  temp3=text.copyTextBetween(temp1,temp2,l1);
                break;
              case F5://for search
				  system("cls");
				  cout<<"Enter the String you want to Search"<<endl;
				  cin>>ch;
				  findCount=text.findInText(ch);
				  cout<<"String occurs ";SetColor(1);cout<<findCount;SetColor(7);cout<<" times in the text\nPress Enter to continue"<<endl;
				  key=getch();
				  system("cls");
				  text.print();
                break;
			  case F6: // find and replace
				  system("cls");
				  cout<<"Enter the String you want to Search"<<endl;
				  cin>>ch;
				  cout<<"Enter the String you want to Replace with"<<endl;
				  cin>>ch1;
				  findCount=text.findAndReplace(ch,ch1);
				  system("cls");
				  SetColor(1);
				  cout<<findCount;SetColor(7);cout<<" replacements done./n Press F4 to see the updated string"<<endl;
				break;
			  case F4:
				  text.print();
				break;
              case INSERT://to insert text
				  text.insertTextAtCursorPos(temp3);
				  text.print();
                break;
              };
          }else if(key==BACKSPACE){
			  text.delCharAtCursorPos();
			  text.print();
          }
		  else if(key==ESCAPE){
			  text.~LinkedText();
			  l1.~LinkedText();
			  exit(0);
          }
		  else{
              cout<<char(key);
			  text.addCharAtCursorPos(key);
				text.print();
		  }
    }
	
    return 0;
}
