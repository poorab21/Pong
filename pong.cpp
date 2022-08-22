#include<iostream>
#include<stdlib.h>
#include<conio.h>
enum eDir{
	stop=0,
	left=1,
	upleft=2,
	downleft=3,
	right=4,
	upright=5,
	downright=6,
};
class ball{
	private:
		int x;
		int y;
		int originalX;
		int originalY;
		eDir direction;
	public:
		ball(const int x,const int y)
		{
			this->originalX=x;
			this->originalY=y;
			this->x=x;
			this->y=y;
			this->direction=stop;
		}
		void reset()
		{
			this->x=this->originalX;
			this->y=this->originalY;
			this->direction=stop;
		}
		void changeDirection(const eDir direction)
		{
			this->direction=direction;
		}
		int getX()const
		{
			return this->x;
		}
		int getY()const
		{
			return this->y;
		}
		eDir getDirection()const
		{
			return this->direction;
		}
		void randomDirection()
		{
			this->direction=(eDir)((rand()%6)+1);
		}
		void move()
		{
			switch(this->direction)
			{
				case left:x--;
				break;
				case right:x++;
				break;
				case upleft:
				         x--;
				         y--;
				break;
				case upright:
					     y--;
					     x++;
				break;
				case downleft:
					     y++;
					     x--;
				break;
				case downright:
					     y++;
					     x++;
			}
		}
		friend std::ostream& operator <<(std::ostream& out,const ball& b)
		{
			out<<"["<<b.x<<","<<b.y<<"]"<<"["<<b.direction<<"]"<<std::endl;
			return out;
		}
};
class paddle{
	private:
		int x;
		int y;
		int a;
		int b;
		int originalX;
		int originalY;
	public:
		paddle()
		{
			this->x=0;
			this->y=0;
			this->originalX=0;
			this->originalY=0;
			this->a=0;
			this->b=0;
		}
		paddle(const int x,const int y)
		{
			this->x=x;
			this->y=y;
			this->originalX=x;
			this->originalY=y;
		}
		int getA()const
		{
			return this->a;
		}
		void setA(const int a)
		{
			this->a=a;
		}
		void setB(const int b)
		{
			this->b=b;
		}
		void reset()
		{
			this->x=this->originalX;
			this->y=this->originalY;
		}
		int getX()const
		{
			return this->x;
		}
		int getY()const
		{
			return this->y;
		}
		void movement2()
		{
			switch(this->b)
			{
				case 1:y--;
				break;
				case 2:y++;
				break;
			}
		}
		friend std::ostream& operator <<(std::ostream& out,paddle& p)
		{
			out<<"["<<p.x<<","<<p.y<<"]"<<std::endl;
			return out;
		}
};
class game{
	private:
		int height;
		int width;
		int score1;
		int score2;
		char up1;
		char up2;
		char down1;
		char down2;
		bool status;
		ball *b;
		paddle *player1;
		paddle *player2;
	public:
		game(const int width,const int height)
		{
			this->height=height;
			this->width=width;
			up1='u';
			down1='d';
			up2='o';
			down2='l';
			score1=0;
			score2=0;
			this->status=false;
			b=new ball(width/2,height/2);
			player1=new paddle(1,(height/2)-3);
			player2=new paddle(width-2,(height/2)-3);
		}
		~game()
		{
			delete b;
			delete player1;
			delete player2;
		}
		void scoreUp(const paddle *p)
		{
			if(p==player1)
			{
				score1++;
			}
			else if(p==player2)
			{
				score2++;
			}
			b->reset();
			player1->reset();
			player2->reset();
		}
		void draw()
		{
			for(int i=0;i<(this->width);i++)
			{
				std::cout<<"\xB2";
			}
			for(int i=0;i<height;i++)
			{
				for(int j=0;j<width;j++)
				{
					int ballx=b->getX();
					int bally=b->getY();
					int player1x=player1->getX();
					int player1y=player1->getY();
					int player2x=player2->getX();
					int player2y=player2->getY();
					if(j==0 || j==width-1)
					{
						std::cout<<"\xB2";
					}
					else if(j==player1x && i==player1y)
					{
						std::cout<<"\xDB";
					}
					else if(j==player1x && i==player1y+1)
					{
						std::cout<<"\xDB";
					}
					else if(j==player1x && i==player1y+2)
					{
						std::cout<<"\xDB";
					}
					else if(j==player1x && i==player1y+3)
					{
						std::cout<<"\xDB";
					}
					else if(ballx==j && bally==i)
					{
						std::cout<<"O";
					}
					else
					{
						std::cout<<" ";
					}
				}
				std::cout<<std::endl;
			}
			for(int i=0;i<(this->width);i++)
			{
				std::cout<<"\xB2";
			}
		}
		void input()
		{
		int ballx=b->getX();
		int bally=b->getY();
		int player1x=player1->getX();
		int player1y=player1->getY();
		int player2x=player2->getX();
		int player2y=player2->getY();
        if(kbhit())
        {
			if (getch()==this->up2 && player2y>0)
			{
				player2->setB(1);
			}
			else if(getch()==this->down2 && player2y<(this->height))
			{
				player2->setB(2);
			}
        }
		if(b->getDirection()==stop)
		{
			b->randomDirection();
		}
		if(kbhit()=='q')
		{
			status=true;
		}
		player2->movement2();
		}
		void logic()
		{
		int ballx=b->getX();
		int bally=b->getY();
		int player1x=player1->getX();
		int player1y=player1->getY();

		if(ballx==player1x+1)
		{
			if(bally==player1y || bally==player1y+1 || bally==player1y+2 || bally==player1y+3)
			{
				b->changeDirection((eDir)((rand()%3)+4));
			}
		}

		if(ballx==width-1)
        {
            b->changeDirection(b->getDirection()==downright?downleft:upleft);
        }
		if(bally==(this->height-1))
		{
			b->changeDirection(b->getDirection()==downright?upright:upleft);
		}
		if(bally==1)
		{
			b->changeDirection(b->getDirection()==upright?downright:downleft);
		}
		}
		void ball_Move()
		{
		    b->move();
		}
		void run()
		{
			while(this->status==false)
			{
				draw();
				input();
				logic();
				ball_Move();
				system("cls");
			}
		}
};
int main()
{
	game g(40,20);
	g.run();
}

