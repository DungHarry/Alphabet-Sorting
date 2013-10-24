/*
 * 	Author: Dung Harry
 * 	Date created: 29th, September 2013
 * 	JDK 1.7 update 15
 * 	Operating System: Windows 7 Professional x64
 * 	
 * */

import java.util.Scanner;

public class AlphabetSorting {
	private String name[] = new String[100];
	private int numberName = 0;
	
	public AlphabetSorting() {
		this.initialize();
	}
	
	private void initialize() {
		for(int i = 0; i < this.name.length; i ++) {
			this.name[i] = new String("");
		}
	}
	
	public void enterNames() {
		Scanner scanner = new Scanner(System.in);
		String temp = new String("");
		boolean flag = true;
		
		do {
			System.out.print("Enter number of the name you wanted to sort: ");
			temp = scanner.nextLine();
			
			for(int i = 0; i < temp.length(); i ++) {
				if((temp.charAt(i) <= '0') && (temp.charAt(i) >= '9')) {
					flag = false;
				} 
			}
			
			if(!flag) {
				System.out.println("**Error: Your entering is invalid. Enter again");
			} else {
				this.numberName = Integer.parseInt(temp);
				
				if(this.numberName > 100) {
					System.out.println("**Error: Your number of names is greater than 100");
				}
			}
		} while((!flag) || (this.numberName > 100));
		
		System.out.println("Begin entering each name...");
		
		for(int i = 0; i < numberName; i ++) {
			System.out.print("Enter name " + (i + 1) + ": ");
			this.name[i] = scanner.nextLine();
		}
		
		System.out.println("Finish entering name part...");
	}
	
	private void swapNames(int firstIndex, int secondIndex) {
		String temp = new String("");
		
		temp = this.name[firstIndex];
		this.name[firstIndex] = this.name[secondIndex];
		this.name[secondIndex] = temp;
	}
	
	private int charAt(int nameIndex, int index) {
		if((index >= this.name[nameIndex].length()) || (nameIndex >= this.numberName)) {
			return 1;
		} else {
			return this.name[nameIndex].charAt(index);
		}
	}
	
	private void sortRange(int index, int head, int tail) {
		for(int i = head; i <= tail; i ++) {
			for(int j = i; j <= tail; j ++) {
				if(this.charAt(i, index) > this.charAt(j, index)) {
					int firstSum = 0, secondSum = 0;
					
					for(int m = 0; m < index; m ++) {
						firstSum += this.charAt(i, m);
						secondSum += this.charAt(j, m);
					}
					
					if(firstSum == secondSum) {
						this.swapNames(i, j);
					}
				}
			}
		}
	}
	
	private int getMaxLengthName() {
		int tmp = this.name[0].length();
		
		for(int i = 0; i < this.numberName; i ++) {
			if(this.name[i].length() > tmp) {
				tmp = this.name[i].length();
			}
		}
		
		return tmp;
	}
	
	public void sortAlphabet() {
		int maxLength = this.getMaxLengthName();
		int head, tail;
		char temp;
		
		this.sortRange(0, 0, this.numberName - 1);
		
		for(int j = 1; j < maxLength; j ++) {
			int i = 0;
			
			while(i < this.numberName) {
				head = i;
				
				temp = (char) this.charAt(i, j - 1);
				
				while(this.charAt(++ i, j - 1) == temp) {
					if(i >= this.numberName - 1) {
						i ++;
					
						break;
					}
				}
				
				tail = i - 1;
				
				this.sortRange(j, head, tail);
			}
		}
	}
	
	public void printNames() {
		for(int i = 0; i < this.numberName; i ++) {
			System.out.println("Name " + (i + 1) + ": " + this.name[i]);
		}
	}
	
	public static void main(String[] args) {
		AlphabetSorting sorter = new AlphabetSorting();
		sorter.enterNames();
		
		sorter.sortAlphabet();
		
		System.out.println("The result after sorting is: \n");
		
		sorter.printNames();
	}
}
