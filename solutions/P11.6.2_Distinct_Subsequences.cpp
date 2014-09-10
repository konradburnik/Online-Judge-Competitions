#include <string>
#include <map>
#include <iostream>

using namespace std;

typedef map<int, map<int, int> > matrix;

matrix sol;

int main()
{
 string A, B;

 cin >> A >> B;

 int N = A.size();
 int M = B.size();

 if( N < M ) swap(A, B);

/*
  Solution DP, distinct subsequences

  Count the number of distinct occurences of B as a subsequence of A, for example
  A = "rabbbit"
  B = "rabbit"

  solution: 3
*/

 for ( int i=0; i<N; i++) sol[i][0] = sol[i-1][0] + (A[i] == B[0]);
 for ( int i=0; i<M; i++) sol[0][i] = (i>0) ? 0 : 1;

 for (int i = 1; i<N; i++)
    for( int j = 1; j<M; j++ ) {
            if( A[i] == B[j] )
                sol[i][j] = sol[i-1][j-1] + sol[i-1][j];
            else
                sol[i][j] = sol[i-1][j];

    }

 cout <<  sol[N-1][M-1] << endl;

 return 0;
}
