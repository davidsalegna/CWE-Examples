public class Book {
    private String title;
    private String author;
    private int numCopies;
 
    public Book(String title, String author, int numCopies) {
       this.title = title;
       this.author = author;
       this.numCopies = numCopies;
    }
 
    public String getTitle() {
       return title;
    }
 
    public String getAuthor() {
       return author;
    }
 
    public int getNumCopies() {
       return numCopies;
    }
 
    public void setNumCopies(int numCopies) {
       this.numCopies = numCopies;
    }
 
    public void display() {
       System.out.println("Title: " + title);
       System.out.println("Author: " + author);
       System.out.println("Copies available: " + numCopies);
    }
 }
 
