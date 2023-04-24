import java.util.ArrayList;
import java.util.Scanner;

public class Library {
   private ArrayList<Book> books = new ArrayList<Book>();
   // Let's assume username and password are not actually stored here, but on another file.
   private static String username = "test";
   private static String password = "password1";

   public Library() {
      books.add(new Book("The Great Gatsby", "F. Scott Fitzgerald", 3));
      books.add(new Book("To Kill a Mockingbird", "Harper Lee", 2));
      books.add(new Book("1984", "George Orwell", 1));
      books.add(new Book("Fahrenheit 451", "Ray Bradbury", 1));
   }

   public void displayAvailableBooks() {
      System.out.println("Available books:");
      for (Book book : books) {
         if (book.getNumCopies() > 0) {
            book.display();
         }
      }
   }

   public void checkout(String title) {
      for (Book book : books) {
         // CWE-486: Classes not compared solely by name
         if (!book.getClass().equals(Book.class)) {
            System.out.println("Sorry, an error occurred");
            return;
         }
         if (book.getTitle().equalsIgnoreCase(title)) {
            if (book.getNumCopies() > 0) {
               book.setNumCopies(book.getNumCopies() - 1);
               System.out.println("You have checked out \"" + title + "\". Enjoy!");
            } else {
               System.out.println("Sorry, there are no copies of \"" + title + "\" available.");
            }
            return;
         }
      }
      System.out.println("Sorry, we do not have \"" + title + "\" in our library.");
   }

   public void returnBook(String title) {
      for (Book book : books) {
         // CWE-481: Book titled is being compared and not assigned
         if (book.getTitle().equalsIgnoreCase(title)) {
            book.setNumCopies(book.getNumCopies() + 1);
            System.out.println("You have returned \"" + title + "\". Thank you!");
            return;
         }
      }
      System.out.println("Sorry, we do not have \"" + title + "\" in our library.");
   }

   public static void main(String[] args) {
      Library library = new Library();
      Scanner scanner = new Scanner(System.in);
      String choice = "";
      String title;
      StringBuffer text1 = new StringBuffer("");
      StringBuffer text2 = new StringBuffer("");

      System.out.println("Hello! Welcome to our library. We hope you enjoy your visit!");
      System.out.print("Please enter your username: ");
      text1.append(scanner.nextLine());
      System.out.print("Please enter your password: ");
      text2.append(scanner.nextLine());

      if (text1.toString().equals(username) && text2.toString().equals(password))
      {
         // CWE-201: Sensitive information such as username and password are given little chance to be accessed by other actors before being removed.
         // CWE-212: Sensitive information such as username and password are properly removed before too much is done with them available.
         text1.delete(0, text1.length());
         text2.delete(0, text2.length());

         while (!choice.equalsIgnoreCase("4"))
         {
            System.out.print("What would you like to do?\n\t[1] Display available books\n\t[2] Check out a book\n\t[3] Return a book\n\t[4] Quit\nChoice:  ");
            choice = scanner.nextLine();
            switch (choice.toLowerCase()) {
               case "1":
                  library.displayAvailableBooks();
                  break; // CWE-484: Break statements are utilized in each case for the switch statement
               case "2":
                  System.out.println("Enter the title of the book you want to check out: ");
                  title = scanner.nextLine();
                  library.checkout(title);
                  break;
               case "3":
                  System.out.println("Enter the title of the book you are returning: ");
                  title = scanner.nextLine();
                  library.returnBook(title);
                  break;
               default:
                  // CWE-478: A default case is implemented for the multiple condition expression
                  System.out.println("Invalid choice. Please try again.");
                  break;
            }
         }
      }
      else
      {
         System.out.println("Username or password invalid.");
      }

      System.out.println("We hope you enjoyed your trip to our library!");
      scanner.close();
   }
}