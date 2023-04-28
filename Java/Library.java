import java.io.FileWriter;
import java.io.IOException;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Scanner;

public class Library {
   private ArrayList<Book> availableBooks = new ArrayList<Book>();
   private ArrayList<Book> checkedOutBooks = new ArrayList<Book>();

   // Let's assume username and password are not actually stored here, but on another file.
   private static String username = "test";
   private static String password = "password1";

   public Library() {
      availableBooks.add(new Book("The Great Gatsby", "F. Scott Fitzgerald", 3));
      availableBooks.add(new Book("To Kill a Mockingbird", "Harper Lee", 2));
      availableBooks.add(new Book("1984", "George Orwell", 1));
      availableBooks.add(new Book("Fahrenheit 451", "Ray Bradbury", 1));
   }

   public void displayAvailableBooks() {
      System.out.println("Available books:\n");
      for (Book book : availableBooks) {
         if (book.getNumCopies() > 0) {
            book.display();
            System.out.println();
         }
      }
   }

   public void checkout(String title) {
      for (Book book : availableBooks) {
         // CWE-486: Classes not compared solely by name
         if (!book.getClass().equals(Book.class)) {
            System.out.println("Sorry, an error occurred");
            return;
         }
         if (book.getTitle().equalsIgnoreCase(title)) {
            if (book.getNumCopies() > 0) {
               book.setNumCopies(book.getNumCopies() - 1);
               // Add book to checkedOutBooks
               checkedOutBooks.add(new Book(book.getTitle(), book.getAuthor(), 1));
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
      // CWE-395: Checks that string is not null rather than throwing NullPointerException
      if (title == null) {
         System.out.println("Invalid input.");
         return;
      }
      for (Book book : availableBooks) {
         // CWE-481: Book titled is being compared and not assigned
         if (book.getTitle().equalsIgnoreCase(title)) {
            boolean flag = false;
            for (int i = 0; i < checkedOutBooks.size(); i++) {
               if (checkedOutBooks.get(i).getTitle().equalsIgnoreCase(title)) {
                  checkedOutBooks.remove(i);
                  flag = true;
               }
            }
            if (flag) {
               book.setNumCopies(book.getNumCopies() + 1);
               System.out.println("You have returned \"" + title + "\". Thank you!");
            } else {
               System.out.println("Sorry, you don't have \"" + title + "\" checked out.");
            }
            return;
         }
      }
      System.out.println("Sorry, we do not have \"" + title + "\" in our library.");
   }

   // CWE-397: This function throws an adequately-specific exception (versus just Exception)
   public void printReceipt() throws IOException {
      //CWE-73: No external control over filename or path
      FileWriter writer = new FileWriter("receipt.txt", false);
      LocalDate returnDate = LocalDate.now().plusWeeks(2);
      //CWE-787: No out of bounds write
      writer.write("RECEIPT\n\n");
      for (Book book : checkedOutBooks) {
         writer.write("Title: " + book.getTitle() + " by " + book.getAuthor() + "\nRETURN BY: " + returnDate + "\n\n");
      }
      writer.close();
      System.out.println("Your receipt has been printed.");
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
      //CWE-120: copy of buffers with proper input size
      text1.append(scanner.nextLine());
      System.out.print("Please enter your password: ");
      text2.append(scanner.nextLine());


      // Let's also assume here that instead of using an if/else, we can also use a try/catch statement in order to
      // query a SQL database using the supplied username-password to retrieve info and "log in", with a 
      // catch statement to supply the user with an error if the login fails.
      //
      // CWE-209: In the "else" statement (instead of a catch), we do not generate a message/error that 
      // supplies the user with sensitive information, like information about the SQL query logic or 
      // the database like names of tables/columns that could lead to SQL injection.
      if (text1.toString().equals(username) && text2.toString().equals(password)) {
         // CWE-201: Sensitive information such as username and password are given little chance to be accessed by other actors before being removed.
         // CWE-212: Sensitive information such as username and password are properly removed before too much is done with them available.
         text1.delete(0, text1.length());
         text2.delete(0, text2.length());

         while (!choice.equalsIgnoreCase("5")) {
            System.out.print("What would you like to do?\n\t[1] Display available books\n\t[2] Check out a book\n\t[3] Return a book\n\t[4] Print receipt\n\t[5] Quit\nChoice:  ");
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
               case "4":
                  try {
                     library.printReceipt();
                  } 
                  // CWE-248: Exception is not left uncaught
                  // CWE-396: Catches an adequately-specific exception (versus just Exception)
                  catch (IOException e) {
                     System.out.println("Failed to print your receipt!");
                  }
                  break;
               case "5":
                  break;
               default:
                  // CWE-478: A default case is implemented for the multiple condition expression
                  System.out.println("Invalid choice. Please try again.");
                  break;
            }
         }
      } else {
         System.out.println("Username or password invalid.");
      }

      System.out.println("We hope you enjoyed your trip to our library!");
      scanner.close();
   }
}
