#include<iostream>
// 국민대 소융대 컴퓨터공학부 20133235 양성호
struct node
{
	int val;
	int neighbors;
};

using namespace std;

class HidatoPuzzleSolver
{
public:
	HidatoPuzzleSolver()
	{
		dx[0] = -1; dx[1] = 0; dx[2] = 1; dx[3] = -1; dx[4] = 1; dx[5] = -1; dx[6] = 0; dx[7] = 1;
		dy[0] = -1; dy[1] = -1; dy[2] = -1; dy[3] = 0; dy[4] = 0; dy[5] = 1; dy[6] = 1; dy[7] = 1;
	}

	void solve(int** puzz, int p_row,int p_col)
	{
		
		col = p_col; row = p_row;
		int len = col * row, c = 0; max = 0;
		arr = new node[len]; memset(arr, 0, len * sizeof(node));
		weHave = new bool[len + 1]; memset(weHave, 0, len + 1);

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {

				if (puzz[i][j] == -1) { arr[c++].val = -1; continue; }
				arr[c].val = puzz[i][j];
				if (arr[c].val > 0) weHave[arr[c].val] = true;
				if (max < arr[c].val) max = arr[c].val;
				c++;

			}
		}
		solveIt(); c = 0;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (puzz[i][j] == 0)
					puzz[i][j] = arr[c].val;	
				c++;

			}
		}
		delete[] arr;
		delete[] weHave;
	}

private:
	bool search(int x, int y, int w)
	{
		if (w == max) return true;

		node* n = &arr[x + y * col];
		n->neighbors = getNeighbors(x, y);
		if (weHave[w])
		{
			for (int d = 0; d < 8; d++)
			{
				if (n->neighbors & (1 << d))
				{		
					int a = x + dx[d], b = y + dy[d];
					if (arr[a + b * col].val == w)
						if (search(a, b, w + 1)) return true;
				}
			}
			return false;
		}

		for (int d = 0; d < 8; d++)
		{
			if (n->neighbors & (1 << d))
			{
				int a = x + dx[d], b = y + dy[d];
				if (arr[a + b * col].val == 0)
				{
					arr[a + b * col].val = w;
					if (search(a, b, w + 1)) return true;
					arr[a + b * col].val = 0;
				}
			}
		}
		return false;
	}

	int getNeighbors(int x, int y)
	{
		int c = 0; int m = -1, a, b;
		for (int yy = -1; yy < 2; yy++) {
			for (int xx = -1; xx < 2; xx++)
			{
				if (!yy && !xx) continue;
				m++; a = x + xx, b = y + yy;
				if (a < 0 || b < 0 || a >= col || b >= row) continue;
				if (arr[a + b * col].val > -1) c |= (1 << m);
			}
		}
		
		return c;
	}

	void solveIt()
	{
		int x, y; findStart(x, y);
		search(x, y, 0);
	}

	void findStart(int& x, int& y)
	{
		for (int b = 0; b < row; b++)
			for (int a = 0; a < col; a++)
				if (arr[a + col * b].val == 1) { 
					x = a; 
					y = b; 
					return; 
				}
		x = y = -1;
	}

	int col, row, max, dx[8], dy[8];
	node* arr;
	bool* weHave;
};


int main()
{
	FILE* in = fopen("input.txt", "r");
	FILE* out = fopen("output.txt", "w");
	int testcase;
	int num = 1;
	fscanf(in, "%d", &testcase);
	
	fprintf(out, "%d\n", testcase);
	
	while (testcase--) {
		int row, col; 
		fscanf(in, "%d %d", &col, &row);
		int** puzz = new int*[row];
		
		for (int i = 0; i < row; i++) {
			puzz[i] = new int[col];
			for (int j = 0; j < col; j++) {
				fscanf(in, "%d", &puzz[i][j]);
			}
		}
		HidatoPuzzleSolver s; 
		s.solve(puzz, row, col);

		fprintf(out, "%d %d\n", col, row);
		
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++)
				fprintf(out, "%d\t", puzz[i][j]);

			fprintf(out, "\n");
		}
		for (int i = 0; i < row; i++)
			delete[] puzz[i];
		delete puzz;
		printf("%d. HidatoPuzzle solved\n", num);
		num++;
	}
	
	fclose(in);
	fclose(out);
	return 0;
}
