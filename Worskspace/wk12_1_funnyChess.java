package test;

//author Sean Adam Holland R00162740
public class Bishops {

	static int matrixSize;

	static int solutionNo = 1;
	static String solution = "";


	public boolean isSafe(String board[][], int pos)
	{
		int i, j;

		//System.out.println("row: "+pos/2+" column: "+pos%2);
		// Check upper diagonal on left side
		for (i = pos / matrixSize, j = pos % matrixSize; i >= 0 && j >= 0; i--, j--)
			if ((board[i][j]).equals(new String("B")))
				return false;

		// Check lower diagonal on left side
		for (i = pos / matrixSize, j = pos % matrixSize; j >= 0 && i < matrixSize; i++, j--)
			if (board[i][j].equals(new String("B")))
				return false;

		// Check upper diagonal on right side
		for (i = pos / matrixSize, j = pos % matrixSize; i >= 0 && j < matrixSize; i--, j++)
			if (board[i][j].equals(new String("B")))
				return false;

		// Check lower diagonal on right side
		for (i = pos / matrixSize, j = pos % matrixSize; i < matrixSize && j < matrixSize; i++, j++)
			if (board[i][j].equals(new String("B")))
				return false;

		return true;
	}

	/* recursive function
	to solve N bishop problem */
	public boolean solveNumBishops(String board[][], int pos, int numBishop)
	{
		/* base case: If all bishops are placed
		then return true */
		if (numBishop == 0)
		{
			saveSolution(board);
			return true;
		}


		boolean res = false;
		for (int i = pos; i < matrixSize * matrixSize; i++)
		{
			//System.out.println("row: "+i/N+" column: "+i%N);
		   //check if bishop can be placed on position i
			if (isSafe(board, i))
			{
				//place bishop on position i
				board[i / matrixSize][i % matrixSize] = "B";

				// Make result true if any placement  
				res = solveNumBishops(board, i + 1, --numBishop) || res;

				/* If placing bishop in position i
				doesn't lead to a solution, then
				remove bishop from i*/
				board[i / matrixSize][i % matrixSize] = "*"; // BACKTRACK  
				numBishop++;

			}
		}

		//If bishop can not be place in any position in i then return false
		return res;
	}

	//print solution 
	public void saveSolution(String board[][])
	{
		//System.out.println(solutionNo++ +":\n");
		solution += solutionNo++ + ":\n\n";
		for (int i = 0; i < matrixSize; i++)
		{
			for (int j = 0; j < matrixSize; j++)
				//System.out.print(board[i][j]+" ");
				solution += board[i][j] + " ";
			// System.out.println("\n");  
			solution += "\n";
		}
		solution += "\n";
	}


	public void startNumBishop(int size)
	{
		if (size < 1)
			System.out.println("Solution does not exist");
		else {
			matrixSize = size;
			String board[][] = new String[matrixSize][matrixSize];
			for (int i = 0; i < board.length; i++)  // initialize the matrix to *
				for (int z = 0; z < board.length; z++)
					board[i][z] = "*";


			int bishop = matrixSize;
			if (solveNumBishops(board, 0, bishop) == false)
			{
				System.out.println("Solution does not exist");

			}
			else
				System.out.println(solution);

		}
	}


	public static void main(String args[])
	{
		Bishops test = new Bishops();
		test.startNumBishop(4);

	}
}