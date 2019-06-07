class ChessBoard {
public:
	ChessBoard();//8X8 chessboard
	ChessBoard(int);//nXn chessboard
	void findSolutions();

private:
	void putQueen(int);
	void printBoard(ostream&);
	void initializeBoard();

	const bool available;
	const int squares, norm;
	bool* colum, *leftDiagonal, *rightDiagonal;
	int* positionInRow, howMany;
};

ChessBoard::ChessBoard():
	available(true), squares(8), norm(squares - 1)
{
	initializeBoard();
}

ChessBoard::ChessBoard(int n):available(true), squares(n), norm(squares - 1)
{
	initializeBoard();
}

void ChessBoard::initializeBoard()
{
	register int i;
	colum = new bool[squares];
	leftDiagonal = new bool[squares*2 - 1];
	rightDiagonal = new bool[squares*2 - 1];

	for(i = 0; i < squares; ++i)
		positionInRow[i] = -1;
	for(i = 0; i < squares; ++i)
		colum[i] = available;
	for(i = 0; i < squares*2 - 1; ++i)
		leftDiagonal[i] = rightDiagonal[i] = available;
	howMany = 0;
}

void ChessBoard::putQueen(int n)
{
	for(int col = 0; col < squares; ++col) {
		if(colum[col] == available &&
		    leftDiagonal[row + col] == available &&
		    rightDiagonal[row - col + norm] == available) 
		{
			positionInRow[row] = col;
			colum[col] = !available;
			leftDiagonal[row+col] = !available;
			rightDiagonal[row-col+norm] = !available;

			if(row < squares -1)
				putQueen(row + 1);
			else
				printBoard(std::cout);
			colum[col] = available;
			leftDiagonal[row + col] = available;
			rightDiagonal[row - col + norm] = available;
		}
	}
}

void ChessBoard::findSolutions()
{
	putQueen(0);
	std::cout << howMany << " solutions found.\n";
}

void ChessBoard::printBoard(ostream&)
{}


