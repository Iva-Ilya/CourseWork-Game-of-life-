#include <iostream>
#include <fstream>

#ifdef _WIN32
#include "windows.h"
void super_sleep(unsigned int seconds)
{
	Sleep(1000 * seconds);
}
#endif

// �������-�������� 2� ������� �������
std::string** create_array(int rows, int cols)
{
	std::string** any_Array = new std::string * [rows]; // ������ ������ ���������� (int*). ��� ������ ����� ����� ��� int**
	for (int i = 0; i < rows; i++)
	{
		any_Array[i] = new std::string[cols]; // ��� ������ ������ ������� arr ������ ������ ����� ����� � ����� ��������� �� ����� ��������� ������ � ��� ������
	}

	return any_Array;
}

// �������-��������� ������ 2� ������� ������� "-"
void fill_two_dim_array(std::string** any_Array, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			any_Array[i][j] = "-";
		}
	}
}

// ������� - �������� � ���������� 2� ������� ������� "*" �� ����� in.txt
std::string** create_fill_old_Array_cells(int *rows, int *cols) // std::string** old_Array
{
	std::ifstream fin("in.txt");														// ������� ���� C:\in.txt �� ������
	int r, c, i, j;
	while (!fin.is_open()) {
		std::cout << "File in.txt not open" << "\n";
		break;
	}
	fin >> *rows;
	fin >> *cols;

	std::string** any_Array = new std::string * [*rows];								// ������ ������ ���������� (string*). ��� ������ ����� ����� ��� string**
	for (int i = 0; i < *rows; i++)
	{
		any_Array[i] = new std::string[*cols];											// ��� ������ ������ ������� arr ������ ������ ����� ����� � ����� ��������� �� ����� ��������� ������ � ��� ������
	}

	fill_two_dim_array(any_Array, *rows,*cols);											// ���������� ������� ������� "-". 

	while (!fin.eof())																	// ���������� ������� ������� "*". ������� - ���� �������� �� �������� �� �����
	{
		fin >> i;
		fin >> j;
		any_Array[i][j] = "*";
	}
	fin.close();																		// ��������� �������� ��������									
	return any_Array;
} 

// ���������� ������� 2� ������� ������� "*"											// Only for debug
//void fill_old_Array_cells(std::string** old_Array)
//{
//	old_Array[2][3] = "*";
//	old_Array[2][4] = "*";
//	old_Array[3][4] = "*";
//	old_Array[3][5] = "*";
//	old_Array[3][6] = "*";
//	old_Array[3][7] = "*";
//	old_Array[5][0] = "*";
//	old_Array[5][1] = "*";
//	old_Array[5][2] = "*";
//	old_Array[6][2] = "*";
//}

// �������-������� ����� ������ � ����� 2� ������ �������
int count_alive_cells(std::string** any_Array, int rows, int cols)
{
	int alive_cells = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (any_Array[i][j] == "*")
			{
				(alive_cells)++;
			}
		}
	}
	return alive_cells;
}

// �������- ������� ����� ������ �� ����� �������
int condition_origin_of_life_outermost_cells(std::string** old_Array, int rows, int cols, int r, int c)
{
	int count = 0;
	// ������� ����� ������ ������ ������� ����� ������
	if ((r == 0) && (c == 0))
	{
		for (int i = 0; i <= 1; i++)
		{
			for (int j = 0; j <= 1; j++)
			{
				if (old_Array[i][j] == "*")
				{
					count++;
				}
			}
		}
	}

	// ������� ����� ������ ������ ������ ����� ������
	else if ((r == rows - 1) && (c == 0))
	{
		for (int i = r - 2; i <= r - 1; i++)
		{
			for (int j = 0; j <= 1; j++)
			{
				if (old_Array[i][j] == "*")
				{
					count++;
				}
			}
		}
	}
	// ������� ����� ������ ������ ������� ������ ������
	else if ((r == 0) && (c == cols - 1))
	{
		for (int i = 0; i <= 1; i++)
		{
			for (int j = c - 2; j <= c - 1; j++)
			{
				if (old_Array[i][j] == "*")
				{
					count++;
				}
			}
		}
	}
	// ������� ����� ������ ������ ������ ������ ������
	else if ((r == rows - 1) && (c == cols - 1))
	{
		for (int i = r - 2; i <= r - 1; i++)
		{
			for (int j = c - 2; j <= c - 1; j++)
			{
				if (old_Array[i][j] == "*")
				{
					count++;
				}
			}
		}
	}
	// ������� ����� ������ ������ ������ ������ �������
	else if ((r != 0 || (rows - 1)) && (c == 0))
	{
		for (int i = r - 1; i <= r + 1; i++)
		{
			for (int j = c; j <= c + 1; j++)
			{
				if (old_Array[i][j] == "*")
				{
					count++;
				}
			}
		}
	}
	// ������� ����� ������ ������ ������ ������� �������
	else if ((r != 0 || (rows - 1)) && (c == cols - 1))
	{
		for (int i = r - 1; i <= r + 1; i++)
		{
			for (int j = c - 2; j <= c - 1; j++)
			{
				if (old_Array[i][j] == "*")
				{
					count++;
				}
			}
		}
	}
	// ������� ����� ������ ������ ������ ������� ������
	else if ((c != 0 || (cols - 1)) && (r == 0))
	{
		for (int i = r; i <= r + 1; i++)
		{
			for (int j = c - 1; j <= c + 1; j++)
			{
				if (old_Array[i][j] == "*")
				{
					count++;
				}
			}
		}
	}
	// ������� ����� ������ ������ ������ ������ ������
	else if ((c != 0 || (cols - 1)) && (r == rows - 1))
	{
		for (int i = r - 2; i <= r; i++)
		{
			for (int j = c - 1; j <= c + 1; j++)
			{
				if (old_Array[i][j] == "*")
				{
					count++;
				}
			}
		}
	}
	else if ((r != 0 && r != rows - 1) && (c != 0 && c != cols - 1)) // (rows != 0 && rows != rows-1) && (cols != 0 && cols != cols-1)
	{
		for (int i = r - 1; i <= r + 1; i++)			
		{
			for (int j = c - 1; j <= c + 1; j++)
			{
				if (old_Array[i][j] == "*")
				{
					count++;
				}
			}
		}
	}
	return count;
}

// �������-���������� �������� ������� ������� �������
void fill_second_array_for_first_array(std::string** old_Array, std::string** new_Array, int rows, int cols)
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			old_Array[i][j] = new_Array[i][j];
		}
	}
}

// ������� ������ ������ ������� � �������
void print_two_dim_array(std::string** old_Array, int rows, int cols)
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			std::cout << old_Array[i][j] << ' ';
		}
		std::cout << "\n";
	}
}

// �������-������� ������ ��� ������ �������
void delete_two_dim_array(std::string** old_Array, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		delete[] old_Array[i]; // ������� ������ ��������� ��������
	}
	delete[] old_Array; // ������� ��������������� ������ ����������
}


int main(int argc, char** argv)
{
	setlocale(LC_CTYPE, "rus");

	// ����-����� 
	std::cout << "\n����-����� " << "\n\n";

	int rows, cols;
	int numb_gen = 1, alive_cells = 0;
	/*std::cout << "������� ���������� �����: ";													// Only for debug
	std::cin >> rows;
	std::cout << "������� ���������� ��������: ";
	std::cin >> cols;*/
	std::string** old_Array = create_fill_old_Array_cells(&rows, &cols);							// �������� ������� �������. ���������� ������� ������� "-". ���������� ������� ������� "*". ��������� ������������ ������.												
	int alive_cells_first_Arr = count_alive_cells(old_Array, rows, cols);							// ������� ���������� "*" � ������ �������.
	print_two_dim_array(old_Array, rows, cols);														// ����� ������� ������� � �������
	std::cout << "Generation: " << numb_gen << ". Alive cells: " << alive_cells_first_Arr << "\n";
	super_sleep(2);

	int stop_bit_1_prev = 0;
	int stop_bit_2_prev = 0;
	int stop_bit_3_prev = 0;
	int stop_bit_4_prev = 0;
	std::string error;

	std::string** new_Array = create_array(rows, cols);												// �������� ������� �������. ��������� ������������ ������.
	fill_two_dim_array(new_Array, rows, cols);														// ���������� ������� ������� "-".

	while (true)
	{
		int stop_bit_1 = 0;
		int stop_bit_2 = 0;
		int stop_bit_3 = 0;
		int stop_bit_4 = 0;
		numb_gen++;

		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				int count = condition_origin_of_life_outermost_cells(old_Array, rows, cols, r, c);

				if (old_Array[r][c] == "-" && count < 3)
				{
					stop_bit_1++;
				}
				else if (old_Array[r][c] == "-" && count == 3)
				{
					new_Array[r][c] = "*";
					stop_bit_2++;
				}
				else if (old_Array[r][c] == "*" && (count < (2 + 1) || count >(3 + 1)))
				{
					new_Array[r][c] = "-";
					stop_bit_3++;
				}
				else if (old_Array[r][c] == "*" && (count == (2 + 1) || count == (3 + 1)))
				{
					new_Array[r][c] = "*";
					stop_bit_4++;
				}
			}
		}

		int alive_cells_second = count_alive_cells(new_Array, rows, cols);									// ������� ���������� "*" � ������ �������.
		
		if (alive_cells_second == 0)																		// �������� �������, ��� ��� ������ � ������ ������� �������.
		{
			error = "All cells are dead. Game over";
			break;
		}
		if (alive_cells_first_Arr == (rows * cols))															// �������� �������, ��� ��� ������ � ������ ������� �����.
		{
			error = "All cells are dead. Game over";
			break;
		}
		if (stop_bit_1_prev == stop_bit_1 && stop_bit_2_prev == stop_bit_2 && stop_bit_3_prev == stop_bit_3 && stop_bit_4_prev == stop_bit_4)
		{
			error = "The world has stagneted. Game over";
			break;
		}

		stop_bit_1_prev = stop_bit_1;
		stop_bit_2_prev = stop_bit_2;
		stop_bit_3_prev = stop_bit_3;
		stop_bit_4_prev = stop_bit_4;

		fill_second_array_for_first_array(old_Array, new_Array, rows, cols);								// ���������� �������� ������� ������� �������.
		print_two_dim_array(new_Array, rows, cols);															// ����� ������� ������� � �������.
		std::cout << "Generation: " << numb_gen << ". Alive cells: " << alive_cells_second << "\n";
		super_sleep(2);
	}
	std::cout << error << "\n";
	delete_two_dim_array(new_Array, rows, cols);													// �������� ������� �������. ������������ ������������ ������.
	delete_two_dim_array(old_Array, rows, cols);													// �������� ������� �������. ������������ ������������ ������.

	return 0;
}