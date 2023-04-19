import java.util.ArrayList;
import java.util.Scanner;

public class Library {
   private ArrayList<Book> books = new ArrayList<Book>();

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

      System.out.println("Hello! Welcome to our library. We hope you enjoy your visit!");

      String choice = "";
      while (!choice.equalsIgnoreCase("4")) {
         System.out.print("What would you like to do?\n\t[1] Display available books\n\t[2] Check out a book\n\t[3] Return a book\n\t[4] Quit\nChoice:  ");
         choice = scanner.nextLine();
         switch (choice.toLowerCase()) {
            case "1":
               library.displayAvailableBooks();
               break; //CWE-484: Break statements are utilized in each case for the switch statement
            case "2":
               System.out.println("Enter the title of the book you want to check out: ");
               String checkoutTitle = scanner.nextLine();
               library.checkout(checkoutTitle);
               break;
            case "3":
               System.out.println("Enter the title of the book you are returning: ");
               String returnTitle = scanner.nextLine();
               library.returnBook(returnTitle);
               break;
            default:
               //CWE-478: A default case is implemented for the multiple condition expression
               System.out.println("Invalid choice. Please try again.");
               break;
         }
      }

      System.out.println("We hope you enjoyed your trip to our library!");
      scanner.close();
   }
}