#ifndef __SEQUENCES_H__
#define __SEQUENCES_H__
#include <string>

using namespace std;

class Solution {
public:
	Solution()
	{
		dp_ = NULL;
		row_ = 0;
		col_ = 0;
	}

	~Solution()
	{
		Uninit();
	}

	void Init(int row, int col)
	{
		Uninit();
		dp_ = new int*[row];
		for (size_t i = 0; i < row; i++)
		{
			dp_[i] = new int[col];
		}

		row_ = row;
		col_ = col;
	}

	void Uninit()
	{
		for (size_t i = 0; i < row_; i++)
		{
			delete[] dp_[i];
		}

		delete[] dp_;

		row_ = col_ = 0;
	}

	int numDistinct(string s, string t) 
	{		
		if (s == "" || t == "") {
			return 0;
		}
		if (s.length() < t.length()) {
			return 0;
		}

		Init(s.length()+1, t.length()+1);

		dp_[0][0] = 1;
		for (int i = 0; i < row_; i++)
		{
			dp_[i][0] = 1;              //from non-empty to empty string, there is 1 solution
		}

		for (int j = 1; j < col_; j++)
		{
			dp_[0][j] = 0;              //from empty to non-empty string, there is no solution
		}

		for (int i = 1; i < row_; i++)
			for (int j = 1; j < col_; j++)
			{
				if (s[i-1] != t[j-1])
				{
					dp_[i][j] = dp_[i - 1][j];  //now we have to abandon last charater in s, then re-caculate
				}
				else
				{
					dp_[i][j] = dp_[i - 1][j] + dp_[i - 1][j - 1]; //in this case, soluton will be divided into 2, one:we keep the last charater in s, so we abandon this 
																   //character in both strings; two:we abandon this last character, this would lead us to solution one
				}
			}

		return dp_[row_-1][col_-1];
	};

private:
	int **dp_;
	int row_;
	int col_;
};
#endif
