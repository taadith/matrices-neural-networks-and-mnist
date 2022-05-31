use std::io;
use std::io::Write;
use std::ops::{Add, Sub, Mul};

#[derive(Debug)]
struct Matrix {
	rows: usize,
	cols: usize,
	entries: Vec<f64>,
}

impl Matrix {
	fn get_entries(&self) -> Vec<f64> {
		self.entries.clone()
	}
	
	fn new(r: usize, c: usize) -> Matrix {
		Matrix {
			rows : r,
			cols : c,
			entries : vec![1f64;r*c],
		}
	}
	
	//Pre-Condition: check that index <= rows and > 0
	fn row_vector(&self,row: usize) -> Matrix {
		if row <= 0 || row > self.rows {
			panic!("Invalid input value for row parameter: {}",row);
		}
		Matrix {
			rows: 1,
			cols: self.cols,
			entries: {
				let start_index = (row-1)*(self.rows);
				let end_index = start_index + self.cols;
				self.entries[start_index..end_index].to_vec()
			}
		}
	}
	
	//Pre-Condition: check that col > cols and <= 0
	fn col_vector(&self, col: usize) -> Matrix {
		if col <= 0 || col > self.cols {
			panic!("Invalid input value for col parameter: {}",col);
		}
		Matrix {
			rows: self.rows,
			cols: 1,
			entries: {
				let start_index = col - 1;
				let mut v: Vec<f64> = Vec::new();
				for i in 0..self.rows {
					v.push(self.entries[start_index + (i*self.cols)]);
				}
				let v = v;
				v
			}
		}
	}
	
	fn print(&self) {
		println!("Rows: {}, Columns: {}",self.rows,self.cols);
		let entries = Matrix::get_entries(&self);
		let mut index = 0;
		for _i in 0..self.rows {
			for _j in 0..self.cols {
				print!("{} ", &entries[index]);
				io::stdout().flush().unwrap();
				index += 1;
			}
			println!();
		}
		println!();
	}
	
	fn copy(&self) -> Matrix {
		Matrix {
			rows: self.rows,
			cols: self.cols,
			entries: self.entries.clone(),
		}
	}
	
	/*
	fn save_to_file(...) {...}
	fn load_from_file(...) {...}
	*/
}

 
impl Add for Matrix {
	type Output = Self;
	
	fn add(self, other: Self) -> Self {
		if self.rows != other.rows || self.cols != other.cols {
			panic!("Matrix addition isn't possible because of a dimension mismatch: {}x{} vs {}x{}",self.rows,self.cols,other.rows,other.cols);
		}
		Self {
			rows: self.rows,
			cols: self.cols,
			entries: {
				let mut sum_of_entries: Vec<f64> = Vec::new();
				for i in 0..(self.rows*self.cols) {
					sum_of_entries.push(self.entries[i] + self.entries[i]);
				}
				let sum_of_entries = sum_of_entries;
				sum_of_entries
			}
		}
	}
}

impl Sub for Matrix {
	type Output = Self;
	
	fn sub(self, other: Self) -> Self {
		if self.rows != other.rows || self.cols != other.cols {
			panic!("Matrix addition isn't possible because of a dimension mismatch: {}x{} vs {}x{}",self.rows,self.cols,other.rows,other.cols);
		}
		Self {
			rows: self.rows,
			cols: self.cols,
			entries: {
				let mut diff_of_entries: Vec<f64> = Vec::new();
				for i in 0..(self.rows*self.cols) {
					diff_of_entries.push(self.entries[i] - &other.entries[i]);
				}
				let diff_of_entries = diff_of_entries;
				diff_of_entries
			}
		}
	}
}

impl Mul<Matrix> for f64 {
	type Output = Matrix;
	
	fn mul(self, mut other: Matrix) -> Matrix {
		Matrix {
			rows: other.rows,
			cols: other.cols,
			entries: {
				for i in 0..(other.rows*other.cols) {
					other.entries[i] = other.entries[i] * self;
				}
				other.entries
			}
		}
	}
}

impl Mul<f64> for Matrix {
	type Output = Matrix;
	
	fn mul(mut self, other: f64) -> Matrix {
		Matrix {
			rows: self.rows,
			cols: self.cols,
			entries: {
				for i in 0..(self.rows*self.cols) {
					self.entries[i] = self.entries[i] * other;
				}
				self.entries
			}
		}
	}
}

impl Mul for Matrix {
	type Output = Self;
	
	fn mul(self, other: Self) -> Self {
		if self.cols != other.rows {
			panic!("Matrix multiplication isn't possible because of a dimension mismatch: cols of LHS ({}) doesn't match rows of RHS ({})",self.cols,other.rows);
		}
		Self {
			rows: self.rows,
			cols: other.cols,
			entries: {
				let mut new_entries: Vec<f64> = vec![0.0;self.rows*other.cols];
				let mut index = 0;
				for i in 0..(self.rows) { //[0,1]
					let some_row_of_lhs = self.row_vector(i+1); //gets row
					
					for j in 0..(other.cols) { //[0,1,2,3]
						let some_col_of_rhs = other.col_vector(j+1); //gets col
						
						for k in 0..(self.cols) {
							new_entries[index] += some_col_of_rhs.entries[k] * some_row_of_lhs.entries[k];
						}
						index += 1;
					}
				}
				let new_entries = new_entries;
				new_entries
			}
		}
	}
}

fn main() {
	let a = Matrix::new(2,3);
	println!("Matrix A:");
	a.print();
	
	
	let b = Matrix::new(3,4);
	println!("Matrix B:");
	b.print();
	
	let c = a.copy() * b.copy();
	println!("Matrix: C:");
	c.print();
	
}
