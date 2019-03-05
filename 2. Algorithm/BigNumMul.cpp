#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

void Add(vector<int>& a, vector<int>& b);
void MulOneBit(vector<int>& a, int b, vector<int>& res);
void Mul(vector<int>& a, vector<int>& b, vector<int>& res);
void print(vector<int>& a);

void print(vector<int>& a) {
	int n = a.size();
	for(int i = 0; i < n; i++) {
		cout << a[i];
	}
	cout << endl;
}

void Mul(vector<int>& a, vector<int>& b, vector<int>& res) {
	int la = a.size(), lb = b.size();
	int lc = la + lb + 1;
	
	res.reserve(lc);
	for(int i=0; i < lc; i++) res[i] = 0;

	for(int j = lb - 1, k = 0; j >= 0; j--, k++) {
		vector<int> c; c.reserve(la + 1 + k);
		MulOneBit(a, b[j], c);
		for(int m = 0; m < k; m++) c.push_back(0);

		//print(c);
		Add(res, c);
	}
}

void MulOneBit(vector<int>& a, int b, vector<int>& res) {
	int la = a.size();

	int carry = 0;
	int sum = 0;
	for(int i = la - 1; i >= 0; i--) {
		sum = b * a[i] + carry;
		carry = sum / 10;
		res.push_back(sum - carry * 10);
	}

	reverse(res.begin(), res.end());
}

void Add(vector<int>& a, vector<int>& b) {
	int la = a.size(), lb = b.size();
	int carry = 0;
	int first, second, sum;
	vector<int> res;
	res.reserve(max(la, lb) + 1);

	for(int i = la - 1, j = lb - 1; i >=0 || j >= 0 || carry; i--, j--) {
		first = i >= 0 ? a[i] : 0;
		second = j >= 0 ? b[j] : 0;
		sum = first + second + carry;
		if(sum >= 10 ) {
			res.push_back(sum - 10);
			carry = 1;
		} else {
			res.push_back(sum);
			carry = 0;
		}
	}

	reverse(res.begin(), res.end());
	a = vector<int>(res);
}

int main() 
{
	vector<int> a;
	vector<int> b;

	string n, m;
	cin >> n >> m;
	a.reserve(n.length());
	b.reserve(m.length());

	for(int i=0; i<n.length(); i++) a.push_back(n[i] - '0');
	for(int i=0; i<m.length(); i++) b.push_back(m[i] - '0');

	vector<int> res;
	Mul(a, b, res);
	print(res);

	return 0;
}