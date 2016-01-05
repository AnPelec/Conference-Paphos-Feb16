import java.io.*;
import java.util.*;

public class Matrix {
	
	int N, M;  /// rows, columns
	static int[][] matrix;
	
	public Matrix(int N, int M) {
		matrix = new int[N][M];
		for (int i=0; i<N; i++) {
			for (int j=0; j<M; j++) {
				this.matrix[i][j] = 0;
			}
		}
	}
	
	public Matrix(int N, int M, int[][] elem) {
		matrix = new int[N][M];
		this.N = N;
		this.M = M;
		for (int i=0; i<N; i++) {
			for (int j=0; j<M; j++) {
				this.matrix[i][j] = elem[i][j];
			}
		}
	}
	
	public int getN() {
		return this.N;
	}
	
	public int getM() {
		return this.M;
	}
	
	public int getElement(int i, int j) {
		return this.matrix[i][j];
	}
	
	public Matrix Add(Matrix matrix2) {
		Matrix retVal = new Matrix(this.N, this.M);
		for (int i=0; i<N; i++) {
			for (int j=0; j<M; j++) {
				System.out.println("yoloooo" + this.matrix[i][j]);
				retVal.matrix[i][j] = this.matrix[i][j] + matrix2.matrix[i][j];
			}
		}
		return retVal;
	}
	
	public Matrix Multiply(Matrix matrix2) {
		int K = matrix2.getM();
		Matrix retVal = new Matrix(this.N, K);
		for (int i=0; i<N; i++) {
			for (int j=0; j<K; j++) {
				for (int k=0; k<M; k++) {
					retVal.matrix[i][j] += this.matrix[i][k]*matrix2.getElement(k, j);
				}
			}
		}
		return retVal;
	}
	
}