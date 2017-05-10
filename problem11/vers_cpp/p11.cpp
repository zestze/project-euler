/*
 * p11.cpp
 *
 * Zeke Reyna
 *
 * This function takes a grid of numbers, and finds the largest product
 * of 4 adjacent numbers (diag/vert/horiz).
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define SIZE 20
#define BUF_SIZE 2048
#define MAX_SIZE 50

using namespace std;

/*
 * xooo
 * oxoo
 * ooxo
 * ooox
 */
int diag1( int mat[][ SIZE ], int size )
{
        int row, col;
        int prod, retval;

        retval = 0;
        for( row = 0; row <= size - 4; row++ ) {
                for( col = 0; col <= size -4; col++ ) {

                        prod  = mat[row][col] * mat[row + 1][col + 1];
                        prod *= mat[row + 2][col + 2] * mat[row + 3][col + 3];

                        if( prod > retval )
                                retval = prod;
                }
        }
        return retval;
}

/*
 * ooox
 * ooxo
 * oxoo
 * xooo
 */
int diag2( int mat[][ SIZE ], int size )
{
	    int row, col;
	    int prod, retval;

	    retval = 0;
	    for( row = 0; row <= size - 4; row++ ) {
                for( col = 0; col <= size - 4; col++ ) {

                        prod  = mat[row][col + 3] * mat[row + 1][col + 2];
                        prod *= mat[row + 2][col + 1] * mat[row + 3][col];

                        if( prod > retval )
                                retval = prod;
                }
        }
	    return retval;
}

/*
 * xxxx
 */
int horiz( int mat[][ SIZE ], int size )
{
        int row, col;
        int prod, retval;

	    retval = 0;
	    for( row = 0; row <= size - 1; row++ ) {
                for( col = 0; col <= size - 4; col++ ) {

                        prod  = mat[row][col] * mat[row][col + 1];
                        prod *= mat[row][col + 2] * mat[row][col + 3];

                        if( prod > retval )
                                retval = prod;
                }
        }
	    return retval;
}

/*
 * x
 * x
 * x
 * x
 */
int vert( int mat[][ SIZE ], int size )
{
        int row, col;
	    int prod, retval;

	    retval = 0;
	    for( row = 0; row <= size - 1; row++ ) {
                for( col = 0; col <= size - 4; col++ ) {

                        prod  = mat[row][col] * mat[row][col + 1];
			            prod *= mat[row][col + 2] * mat[row][col + 3];

			            if( prod > retval )
                                retval = prod;
                }
        }
	    return retval;
}

void process_file( int mat[][SIZE], int size )
{
        int i, j;
        string line;

        ifstream infile( "../num.txt" );
        if( infile.is_open() ) {

                for( i = 0; getline( infile, line ); i++ ) {
                        istringstream iss( line );

                        for( j = 0; j < size; j++ ) {
                                string num;
                                iss >> num;
                                mat[i][j] = stoi( num );
                        }
                }
                infile.close();
        }
}

int main( int argc, char **argv )
{
        int size;
        size = SIZE; // redundant because couldn't figure out compile time
	    int mat[SIZE][SIZE]; // matrix size passing in function args
	    int largest_adj;
	    int temp;

        process_file( mat, size );

	    largest_adj = diag1( mat, size );

	    temp = diag2( mat, size );
	    if( temp > largest_adj )
                largest_adj = temp;

	    temp = horiz( mat, size );
	    if( temp > largest_adj )
                largest_adj = temp;

	    temp = vert( mat, size );
	    if( temp > largest_adj )
                largest_adj = temp;

	    cout<<"\nThe largest product of 4 adjacent numbers in a line in";
	    cout<<" num.txt is "<<largest_adj<<"\n\n";

	    return 0;
}
