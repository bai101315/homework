#include<iostream>
#include<algorithm>
#include<cstring>
#include<unordered_map>
#include<stack>

using namespace std;
const int N = 20, M = 500, inf = 0x3f3f3f3f;
int n = 10, m;//n表示节点数，即景点数
int g[M][M];
int dist[M];
int pre[N][N];
bool st[M];
unordered_map<int, string>map;
void inputPoint();


void input();
int dijikstra(int x);
void floyd();
void dijistra_func();
void folyd1_func();
void folyd2_func();
void printDistance();
void chage();
void find(int, int);





int  main()
{
	input();


	while (1)
	{

		cout << "**********1,输出景点信息************************************" << endl;
		cout << "**********2,输出景点距离************************************" << endl;
		cout << "**********3,修改两个景点距离，并且重新输出景点距离**********" << endl;
		cout << "**********4,求出两点距离的最短路径，并输出途径的地点********" << endl;
		cout << "**********5,输出任意一点与其他各点的最短路径****************" << endl;
		cout << "**********6,退出********************************************" << endl;
		cout << endl;
		cout << "请输入序号:" << endl;
		int cnt = 0;
		cin >> cnt;
		switch (cnt)
		{
		case 1:
			inputPoint();
			break;
		case 2:
			printDistance();
			break;
		case 3:
			chage();
			break;
		case 4:
			folyd1_func();
			break;
		case 5:
			folyd2_func();
			break;
		case 6:
			exit(0);
			break;
		default:
			cout << "输入错误，请重新输入" << endl;
		}
		system("pause");
		system("cls");

	}




	return 0;
}

void chage()
{
	cout << "1，沈航南体育场" << " ";
	cout << "2,沈航南区食堂" << " ";
	cout << "3,大学活动中心" << " ";
	cout << "4,沈航北区宿舍" << " ";
	cout << "5,沈航北体育场" << endl;
	cout << "6,沈航教学楼  " << " ";
	cout << "7,沈航图书场馆" << " ";
	cout << "8,经济管理学院" << " ";
	cout << "9,工程训练中心" << " ";
	cout << "10,设计艺术学院" << " ";
	cout << endl;

	int x, y, w;
	cout << "请输入您需要改变的序号: ";
	cin >> x >> y;
	cout << endl;

	if ((x > 0 && x < 10) && (y > 0 && y < 10))
	{
		cout << "请输入您需要改变的距离: ";
		cin >> w;
		if (w > 0 && w < inf)
		{
			g[x][y] = g[y][x] = w;
			printDistance();
		}
		else
		{
			cout << "您输入的距离有误，请重新输入" << endl;
		}
	}
	else
	{
		cout << "您输入的信息有误，请重新输入" << endl;
	}



}
void inputPoint()
{
	for (auto res : map)
	{
		cout << res.second << "  ";
	}
	cout << endl;
}
void printDistance()
{
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			if (g[i][j] != 0 && g[i][j] != inf)
			{
				auto pos = map.find(i);
				auto end = map.find(j);
				cout << (*pos).second << "  到  " << (*end).second << "的距离为： " << g[i][j] << endl;
			}
		}
	}

}



void input()
{
	map.insert(pair<int, string>(1, "沈航南体育场"));
	map.insert(pair<int, string>(2, "沈航南区食堂"));
	map.insert(pair<int, string>(3, "大学活动中心"));
	map.insert(pair<int, string>(4, "沈航北区宿舍"));
	map.insert(pair<int, string>(5, "沈航北体育场"));
	map.insert(pair<int, string>(6, "沈航教学楼  "));
	map.insert(pair<int, string>(7, "沈航图书场馆"));
	map.insert(pair<int, string>(8, "经济管理学院"));
	map.insert(pair<int, string>(9, "工程训练中心"));
	map.insert(pair<int, string>(10, "设计艺术学院"));


	memset(g, 0x3f, sizeof g);

	g[1][2] = g[2][1] = 1;
	g[1][6] = g[6][1] = 5;
	g[6][7] = g[7][6] = 4;
	g[7][10] = g[10][7] = 3;
	g[1][8] = g[8][1] = 12;
	g[8][9] = g[9][8] = 4;
	g[9][10] = g[10][9] = 2;
	g[2][3] = g[3][2] = 2;
	g[3][4] = g[4][3] = 3;
	g[4][5] = g[5][4] = 2;
	g[5][10] = g[10][5] = 7;
	g[6][8] = g[8][6] = 10;


	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			if (i == j) g[i][j] = 0;
			pre[i][j] = j;
		}


}



//任意场所到达所有场所的最短距离
void folyd1_func()
{
	input();
	cout << "1，沈航南体育场" << " ";
	cout << "2,沈航南区食堂" << " ";
	cout << "3,大学活动中心" << " ";
	cout << "4,沈航北区宿舍" << " ";
	cout << "5,沈航北体育场" << endl;
	cout << "6,沈航教学楼  " << " ";
	cout << "7,沈航图书场馆" << " ";
	cout << "8,经济管理学院" << " ";
	cout << "9,工程训练中心" << " ";
	cout << "10,设计艺术学院" << " ";
	cout << endl;

	int x = 0; int y = 0;
	cout << "请输入起点和终点：" << endl;
	cin >> x >> y;
	floyd();
	if (g[x][y] > inf / 2)
		cout << "不能到达该点" << endl;
	else
	{
		auto pos = map.find(x);
		auto end1 = map.find(y);
		cout << (*pos).second << "  到  " << (*end1).second << "的距离为：" << g[x][y] << endl;

		cout << (*pos).second << "  到  " << (*end1).second << "的路径为：";
		find(x, y);
		cout << y;
	}
}
void folyd2_func()
{
	input();
	cout << "1,沈航南体育场" << " ";
	cout << "2,沈航南区食堂" << " ";
	cout << "3,大学活动中心" << " ";
	cout << "4,沈航北区宿舍" << " ";
	cout << "5,沈航北体育场" << endl;
	cout << "6,沈航教学楼  " << " ";
	cout << "7,沈航图书场馆" << " ";
	cout << "8,经济管理学院" << " ";
	cout << "9,工程训练中心" << " ";
	cout << "10,设计艺术学院" << " ";
	cout << endl;
	cout << "请输入您需要查询的景点编号";

	int m;
	cin >> m;
	floyd();
	auto pos = map.find(m);
	for (int i = 1; i <= 10; i++)
	{
		if (i == m)
			continue;

		auto end = map.find(i);
		cout << (*pos).second << "  到  " << (*end).second << "的距离为:" << g[m][i] << endl;
	}


}


void find(int x, int y)
{
	int u = x, v = y;
	while (u != v)
	{
		printf("%d ", u);
		u = pre[u][v];
	}
}


void floyd()
{
	for (int k = 1; k <= n; k++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				int tmp = g[i][k] + g[k][j];
				//存储路径
				if (g[i][j] > tmp)
				{
					g[i][j] = g[i][k] + g[k][j];
					pre[i][j] = pre[i][k];
				}
			}
		}
	}
}




