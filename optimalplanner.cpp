#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
using namespace cv;
#define ROWS 100
#define COLS 100
Mat img;
struct graph_node
{
	int x,y;
};
struct node
{
	graph_node data;
	node* next;
};

struct QUEUE
{
	node *front, *rear ;
};

void init(QUEUE **qP)//initializes the front and rear pointers
{
	(*qP) = (QUEUE *)malloc(sizeof(QUEUE));
	(*qP)->front=NULL;
	(*qP)->rear=NULL;
}
int isempty(QUEUE *qP)//prints 1 if the queue is emptry, else 0
{
	int k;
	if( qP->front==NULL && qP->rear==NULL)
		k=1;
	else
		k=0;
	return k;

}
void enqueue(QUEUE *qP, graph_node data)
{
	node* temp;
	temp=(node*)malloc(sizeof(node));
	temp->data=data;
	temp->next=NULL;
	if(qP->front==NULL)
		qP->front=qP->rear=temp;
	else
	{
		(qP->rear)->next=temp;
		qP->rear=temp;
	}
}
graph_node dequeue(QUEUE *qP)
{
	if (qP->front == NULL)
		printf("Queue Empty ");
	else
	{
		node* temp;
		graph_node val;
		temp = qP->front;
		val=(qP->front)->data;
		qP->front = (qP->front)->next;
		temp->next = NULL;
		if (qP->front == NULL)
			qP->rear = NULL;
		return val;
	}
}
int isvalid( int i, int j)
{
	 if(i>=0 && j>=0 && i<img.rows && j<img.cols)
		return 1;
	else
		return 0;
}	
int BFS(graph_node parent[ROWS][COLS], graph_node v)
{
	int i,j,k,l,visited[ROWS][COLS];
	float distance[ROWS][COLS];
	graph_node current,temp;

	for(i=0;i<ROWS;i++)
		for(j=0;j<COLS;j++)
		{
			parent[i][j].x=-1;
			parent[i][j].y=-1;
			visited[i][j]=0;
			distance[i][j]=0;
		}

	QUEUE *qP=NULL;
	init(&qP);
	enqueue(qP,v);
	visited[v.x][v.y]=1;
	distance[v.x][v.y]=0;
	parent[v.x][v.y].x=-1;
	parent[v.x][v.y].y=-1;
	//printf("\nBFS Traversal:");
	while(!isempty(qP))
	{
		current=dequeue(qP);
		for(k=-1;k<=1;k++)
			for(l=-1;l<=1;l++)
			{

				if(!(k==0 and l==0) && isvalid(current.x+k,current.y+l) && visited[current.x+k][current.y+l]==0 && img.at<uchar>(current.x+k,current.y+l)<100)
				{
					//cout << "hi";
					visited[current.x+k][current.y+l]=1;
					parent[current.x+k][current.y+l]=current;

					if (abs(k)==1 && abs(l)==1)
						distance[current.x+k][current.y+l]=distance[current.x][current.y]+1.4142;
					else
						distance[current.x+k][current.y+l]=distance[current.x][current.y]+1;
					//cout << distance[current.x+k][current.y+l];
					if(current.x+k == img.rows-1 && current.y+l == img.cols-1)
					{
						return distance[img.rows-1][img.cols-1];
					}
					temp.x=current.x+k;
					temp.y=current.y+l;
					enqueue(qP,temp);
				}
			}
	}
	
}

void print_path(graph_node parent[ROWS][COLS], graph_node start, graph_node end)
{
	if((start.x == end.x) && (start.y == end.y))
	{
		img.at<uchar>(end.x,end.y)=160;
		printf(" (%d,%d) ",start.x,start.y);
	}
	else if(parent[end.x][end.y].x==-1 && parent[end.x][end.y].y==-1)
		printf("\nNo path from (%d,%d) to (%d,%d) exists",start.x,start.y,end.x,end.y);
	else
	{
		print_path(parent,start,parent[end.x][end.y]);
		printf(" (%d,%d) ",end.x,end.y);
		img.at<uchar>(end.x,end.y)=160;
	}
	
}

void approx_path(graph_node parent[ROWS][COLS], graph_node start, graph_node end)
{
	int	approx_step = 5;
	graph_node approx_parent[ROWS][COLS];
	graph_node u = end, v = end;
	while(parent[v.x][v.y].x != -1 && parent[v.x][v.y].y != -1)
	{
		int i;
		for(i=0; i<approx_step; i++)
		{
			if(parent[v.x][v.y].x == -1 || parent[v.x][v.y].y == -1)
				break;
			v = parent[v.x][v.y];
		}

		approx_parent[u.x][u.y] = v;
		u = v;
	}
	print_path(approx_parent,start,end);
}

int main()
{	
	/*namedWindow("Original Image",WINDOW_NORMAL);
	img = imread("dataset/img1.jpg",0);
	imshow("Original Image",img);
	while(1)
	{
		int temp = waitKey(10);
		if(temp == 27) break;
	}*/

	graph_node start,end;

	// printf("Input start vertex: ");
	// scanf("%d",&start.x);
	// scanf("%d",&start.y);
	// printf("Input end vertex: ");
	// scanf("%d",&end.x);
	// scanf("%d",&end.y);
	start.x = 0;
	start.y = 0;
	end.x = ROWS-1;
	end.y = COLS-1;
	int dist[100000];
	int number = 100000;
	
	/*int temp = BFS(parent,start);
	approx_path(parent,start,end);
	namedWindow("Final Path",WINDOW_NORMAL);
	imshow("Final Path",img);
	while(1)
	{
		int temp = waitKey(10);
		if(temp == 27) break;
	}
	return 0;*/
	while(number>0)
	{
		graph_node parent[ROWS][COLS];
		stringstream ss;
        ss<<(100000-number);
        string s = "dataset/";
        string s1 = "img";
        string s2 = ss.str();
        string s3 = ".jpg";
        img = imread(s+s1+s2+s3,0);	
        //cout << img.rows << endl;	
		dist[100000-number]=BFS(parent,start);
		//cout << dist[ROWS*COLS-number] << endl;
		approx_path(parent,start,end);
		number--;
		printf("\n");
	}
	// print_path(parent,start,end);
	// imshow("chaljabhai",img);
	// waitKey(0);
	// return 0;
}