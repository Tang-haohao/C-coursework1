#ifndef BOOK_MANAGEMENT_GUARD__H 
#define BOOK_MANAGEMENT_GUARD__H

#include"interface.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

/*You can extend the structs (Book and BookArray) defined in this head file;
  However, you may not change the function prototypes. 
  You are also free to add additional head files and data structures as needed. 
*/


typedef struct _Book {
	    unsigned int id; //Book ID
		char *title; //book title
		char *authors; //comma separated list of authors
		unsigned int year; // year of publication
		unsigned int copies; //number of copies the library has
		struct _Book *nextbook;//定义指针域 
}Book;

typedef struct _BookArray {
	 Book* array; // pointer to array (or linked list) of struct Book.
	 unsigned int length; // number of elements in the (Book*) array 
}BookArray;

typedef Book* pbook;

//saves the database of books in the specified file
//returns 0 if books were stored correctly, or an error code otherwise
int store_books(FILE *file);

//loads the database of books from the specified file
//the file must have been generated by a previous call to store_books()
//returns 0 if books were loaded correctly, or an error code otherwise
int load_books(FILE *file);

//adds a book to the ones available to the library
//returns 0 if the book could be added, or an error code otherwise
int add_book(Book book);

//removes a book from the library
//returns 0 if the book could be successfully removed, or an error code otherwise.
int remove_book(Book book);

//finds books with a given title.
//returns a BookArray structure, where the field "array" is a newly allocated array of books, or null if no book with the 
//provided title can be found. The length of the array is also recorded in the returned structure, with 0 in case
//array is the null pointer.
BookArray find_book_by_title (const char *title);

//finds books with the given authors.
//returns a BookArray structure, where the field "array" is a newly allocated array of books, or null if no book with the 
//provided title can be found. The length of the array is also recorded in the returned structure, with 0 in case
//array is the null pointer.
BookArray find_book_by_author (const char *author);

//finds books published in the given year.
//returns a BookArray structure, where the field "array" is a newly allocated array of books, or null if no book with the 
//provided title can be found. The length of the array is also recorded in the returned structure, with 0 in case
//array is the null pointer.
BookArray find_book_by_year (unsigned int year);

//finds books published in the given ID.
void find_book_by_ID ();
//修改数目
int amend_book(); 

//查询书籍 
void search_book();
#endif
