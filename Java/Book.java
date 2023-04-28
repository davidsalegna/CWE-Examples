import java.util.Objects;

// CWE-767: Proper class accessors and mutators (get/set methods) are appropriately created (and used in library)
// in order to properly retrieve the private variables for title, author, and numCopies here, and properly modify 
// numCopies when needed. 
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

   // CWE-581: BOTH equals and hashcode methods are defined.
   // This can help avoid bugs and issues when comparing and sorting using equals or hashcode with collections.
   @Override
   public boolean equals(Object obj) {
      if (obj == null) {
         return false;
      }
      if (getClass() != obj.getClass()) {
         return false;
      }
      final Book other = (Book) obj;
      if (!Objects.equals(this.title, other.title)) {
         return false;
      }
      if (!Objects.equals(this.author, other.author)) {
         return false;
      }
      return true;
   }
   @Override
   public int hashCode() {
      int hash = 7;
      hash = 59 * hash + Objects.hashCode(this.title);
      hash = 59 * hash + Objects.hashCode(this.author);
      return hash;
   }
}