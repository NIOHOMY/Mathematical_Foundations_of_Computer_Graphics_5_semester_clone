#pragma once
#include <iostream>

using namespace std;

template <typename Cell = double>
class Matrix
{
private:
	int n_nRows;
	int n_nCols;

	Cell** m_cells;
	void AllocateCells(int, int);
	void FreeCells();
public:
	Matrix() : n_nRows(0), n_nCols(0), m_cells(nullptr) {}
	Matrix(const Matrix&);
	Matrix(int, int);
	Matrix(int, int, Cell*);
	~Matrix();

	int nRows();
	int nColumns();

	void setVaue(int, int, Cell);

	Cell& operator()(int i, int j) { return m_cells[i - 1][j - 1]; }

	Matrix& operator = (const Matrix&);		// Ïåðåãðóçêà îïåðàòîðà ïðèñâàèâàíèÿ
	Matrix  operator + (const Matrix&);		// Ñëîæåíèå ìàòðèö
	Matrix  operator - (const Matrix&);		// Âû÷èòàíèå ìàòðèö
	Matrix  operator * (const Matrix&);		// Óìíîæåíèå ìàòðèö

	friend istream& operator >> <> (istream&, Matrix&);			// Перегрузка оператора >> для ввода матрицы
	friend ostream& operator << <> (ostream&, const Matrix&);	// Перегрузка оператора << для вывода матрицы
};

template <typename Cell>
Matrix<Cell>::Matrix(const Matrix<Cell>& M)
{
	AllocateCells(M.n_nRows, M.n_nCols);
	for (int i = 0; i < n_nRows; i++)
		for (int j = 0; j < n_nCols; j++)
			m_cells[i][j] = M.m_cells[i][j];
}

template <typename Cell>
Matrix<Cell>::Matrix(int n_nRows, int n_nCols)
{
	AllocateCells(n_nRows, n_nCols);
	for (int i = 0; i < n_nRows; i++)
		for (int j = 0; j < n_nCols; j++)
			m_cells[i][j] = 0;
}

template <typename Cell>
Matrix<Cell>::Matrix(int n_nRows, int n_nCols, Cell* list)
{
	AllocateCells(n_nRows, n_nCols);
	int index = 0;
	for (int i = 0; i < n_nRows; i++) {
		for (int j = 0; j < n_nCols; j++) {
			m_cells[i][j] = list[index];
			index++;
		}
	}
}


template <typename Cell>
Matrix<Cell>::~Matrix()
{
	FreeCells();
}

template <typename Cell>
Matrix<Cell>& Matrix<Cell>::operator=(const Matrix& M)
{
	if (this != &M) {
		// Очистить текущую матрицу
		FreeCells();
		// Выделить память заново
		AllocateCells(M.n_nRows, M.n_nCols);
		// Скопировать элементы
		for (int i = 0; i < n_nRows; i++) {
			for (int j = 0; j < n_nCols; j++) {
				m_cells[i][j] = M.m_cells[i][j];
			}
		}
	}
	return *this;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator+(const Matrix& M)
{
	Matrix<Cell> res(*this);
	if (n_nRows == M.n_nRows && n_nCols == M.n_nCols) {
		for (int i = 0; i < n_nRows; i++) {
			for (int j = 0; j < n_nCols; j++) {
				res.m_cells[i][j] += M.m_cells[i][j];
			}
		}
	}
	return res;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator-(const Matrix& M)
{
	Matrix<Cell> res(*this);
	if (n_nRows == M.n_nRows && n_nCols == M.n_nCols) {
		for (int i = 0; i < n_nRows; i++) {
			for (int j = 0; j < n_nCols; j++) {
				res.m_cells[i][j] -= M.m_cells[i][j];
			}
		}
	}
	return res;
}

/*
T = | a*x + b*y + c |
	| d*x + e*y + f |
	| 1             |

M = | a  b  c |
	| d  e  f |
	| 0  0  1 |

P = | x |
	| y |
	| 1 |

*/
template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator*(const Matrix& M)
{

	if (n_nCols == M.n_nRows) {
		Matrix<Cell> res(n_nRows, M.n_nCols);
		for (int i = 0; i < n_nRows; i++) {
			for (int j = 0; j < M.n_nCols; j++) {
				Cell sum = 0;
				for (int k = 0; k < n_nCols; k++) {
					sum += m_cells[i][k] * M.m_cells[k][j];
				}
				res.m_cells[i][j] = sum;
			}
		}
		return res;
	}
	else if (n_nCols == 1)
	{
		Matrix<Cell> res(n_nRows, n_nCols);
		res.m_cells[0][0]= m_cells[0][0] * M.m_cells[0][0] + M.m_cells[0][1]*m_cells[1][0]+ M.m_cells[0][2];
		res.m_cells[1][0]= m_cells[0][0] * M.m_cells[1][0] + M.m_cells[1][1]*m_cells[1][0]+ M.m_cells[1][2];
		res.m_cells[2][0]=1.0;
		return res;
	}
	else
	{
		return Matrix<Cell>(n_nRows, M.n_nCols);
	}
}


template <typename Cell>
void Matrix<Cell>::AllocateCells(int nRows, int nCols)
{
	n_nRows = nRows;
	n_nCols = nCols;

	m_cells = new Cell * [n_nRows];
	for (int i = 0; i < n_nRows; i++)
		m_cells[i] = new Cell[n_nCols];
}

template <typename Cell>
void Matrix<Cell>::FreeCells()
{
	for (int i = 0; i < n_nRows; i++)
		delete m_cells[i];
	delete m_cells;
	n_nRows = 0;
	n_nCols = 0;
}

template <typename Cell>
istream& operator >> (istream& fi, Matrix<Cell>& M)
{
	for (int i = 0; i < M.n_nRows; i++)
		for (int j = 0; j < M.n_nCols; j++)
			fi >> M.m_cells[i][j];
	return fi;
}

template <typename Cell>
ostream& operator << (ostream& fo, const Matrix<Cell>& M)
{
	for (int i = 0; i < M.n_nRows; i++)
	{
		fo << "  ";
		for (int j = 0; j < M.n_nCols; j++)
			fo << M.m_cells[i][j] << " \t";
		fo << endl;
	}
	return fo;
}

template <typename Cell>
int Matrix<Cell>::nRows()
{
	return n_nRows;
}

template <typename Cell>
int Matrix<Cell>::nColumns()
{
	return n_nCols;
}

template <typename Cell>
void Matrix<Cell>::setVaue(int i, int j, Cell value)
{
	m_cells[i][j] = value;
}
